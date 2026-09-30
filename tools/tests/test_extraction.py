"""Synthetic fixtures only; no original game data is needed for these tests."""

from io import BytesIO
import json
from pathlib import Path
import struct
import sys
from tempfile import TemporaryDirectory
import unittest

import pycdlib

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import extract
from so3.formats import (
    FormatError, MAX_DECODED_SIZE, SECTOR_SIZE, TABLE_OFFSET, TABLE_SEED,
    TABLE_SIGNATURE, TABLE_SIZE, TABLE_SLOTS, decode_chain, elf_info,
    overlay_info, read_table,
)


KEY = bytes(range(16))


def block(kind, payload, expected, advance=0, encrypted=False):
    if encrypted:
        payload = bytes(((value ^ KEY[i % 16]) + 3 * (i + 1)) & 255
                        for i, value in enumerate(payload))
    return (b"SLE" if encrypted else b"SLZ") + bytes([kind]) + struct.pack(
        "<III", len(payload), expected, advance) + payload


def table(rows):
    words = [0] * (TABLE_SLOTS * 3)
    words[TABLE_SLOTS] = TABLE_SIZE // SECTOR_SIZE
    words[2 * TABLE_SLOTS] = 1
    for index, lba, sectors, runtime in rows:
        words[index] = lba
        words[TABLE_SLOTS + index] = sectors
        words[2 * TABLE_SLOTS + index] = runtime
    key = TABLE_SEED
    for index in range(TABLE_SLOTS):
        words[index] ^= key
        key = (key ^ (key << 1)) & 0xFFFFFFFF
        words[TABLE_SLOTS + index] ^= key
        key = (key ^ ~TABLE_SEED) & 0xFFFFFFFF
        words[2 * TABLE_SLOTS + index] ^= key
        key = (key ^ (key << 2) ^ TABLE_SEED) & 0xFFFFFFFF
    words[0] = TABLE_SIGNATURE
    return struct.pack(f"<{len(words)}I", *words)


def elf():
    return b"\x7fELF\x01\x01\x01" + bytes(9) + struct.pack(
        "<HHIIIIIHHHHHH", 2, 8, 1, 0x100000, 0, 0, 0x20924000,
        52, 32, 0, 40, 0, 0)


def overlay():
    header = b"MWo3" + struct.pack("<7I", 7, 0x200000, 4, 4, 16, 0, 0)
    return header + b"sample.bin".ljust(32, b"\0") + b"CODEDATA"


class CompressionTests(unittest.TestCase):
    def decode(self, value):
        return list(decode_chain(value, KEY))[0].data

    def test_all_compression_types_and_overlapping_copies(self):
        fixtures = [
            (0, b"stored", b"stored"),
            (1, b"\x03AB\x02\x30\x00\x00", b"ABABABAB"),
            (2, b"\x03AB\x02\x30", b"ABABABAB"),
            (3, b"\x03\x00ABCD\x02\x10\x00\x00", b"ABCDABCDAB"),
        ]
        for kind, payload, expected in fixtures:
            for encrypted in (False, True):
                with self.subTest(kind=kind, encrypted=encrypted):
                    self.assertEqual(self.decode(block(kind, payload, len(expected), encrypted=encrypted)), expected)

    def test_type2_run_lengths_and_new_control_byte(self):
        self.assertEqual(self.decode(block(2, b"\x00\x41\xf1", 4)), b"AAAA")
        self.assertEqual(self.decode(block(2, b"\x00\x00\xf0Z", 19)), b"Z" * 19)
        self.assertEqual(self.decode(block(2, b"\xffabcdefgh\x01i", 9)), b"abcdefghi")

    def test_chains_and_allocation_padding(self):
        data = block(0, b"first", 5, advance=32) + bytes(11) + block(0, b"second", 6) + bytes(10)
        blocks = list(decode_chain(data, KEY))
        self.assertEqual([b.data for b in blocks], [b"first", b"second"])
        self.assertEqual([b.offset for b in blocks], [0, 32])

    def test_malformed_streams_are_rejected(self):
        fixtures = {
            "header": b"SLZ",
            "payload": block(0, b"abc", 3)[:-1],
            "type": block(4, b"", 0),
            "output_limit": block(2, b"", MAX_DECODED_SIZE + 1),
            "bad_distance": block(2, b"\x00\x01\x00", 3),
            "zero_distance": block(2, b"\x00\x00\x00", 3),
            "overflow": block(2, b"\x00\x41\xf1", 3),
            "underflow": block(1, b"\x00\x00\x00", 3),
            "trailing_payload": block(2, b"\x01Ax", 1),
            "missing_terminator": block(1, b"\x01A", 1),
            "stored_size": block(0, b"AB", 1),
            "chain_overlap": block(0, b"AB", 2, advance=16) + bytes(20),
            "chain_outside": block(0, b"AB", 2, advance=200),
            "wrong_key": block(2, b"\x00\x41\xf1", 4, encrypted=True),
        }
        for name, value in fixtures.items():
            with self.subTest(name=name), self.assertRaises(FormatError):
                list(decode_chain(value, bytes(16) if name == "wrong_key" else KEY))
        with self.assertRaises(FormatError):
            list(decode_chain(block(0, b"", 0), b"bad"))


class TableTests(unittest.TestCase):
    def test_large_offsets_and_runtime_only_slots(self):
        raw = table([(1, 0x210000, 1, 0), (2, 0, 0, 15)])
        entries = read_table(raw, 5 * 1024**3)
        self.assertEqual(entries[1]["offset"], 0x108000000)
        self.assertEqual(entries[2]["runtime_word"], 15)
        self.assertEqual(entries[2]["allocated_size"], 0)

    def test_bad_signature_truncation_bounds_and_overlaps(self):
        valid = table([])
        cases = [valid[:-1], bytes(4) + valid[4:],
                 table([(1, 0x2000, 1, 0)]),
                 table([(1, 1060, 2, 0), (2, 1061, 1, 0)])]
        for raw in cases:
            with self.subTest(prefix=raw[:4]), self.assertRaises(FormatError):
                read_table(raw, 4 * 1024**2)


class ModuleTests(unittest.TestCase):
    def test_module_metadata(self):
        self.assertEqual(elf_info(elf())["entry_address"], 0x100000)
        result = overlay_info(overlay())
        self.assertEqual(result["name"], "sample.bin")
        self.assertEqual(result["load_address"], 0x200000)
        self.assertEqual(result["bss_size"], 16)

    def test_invalid_headers(self):
        bad_elf = bytearray(elf())
        struct.pack_into("<I", bad_elf, 32, 0xFFFFFF00)
        struct.pack_into("<H", bad_elf, 48, 2)
        bad_overlay = bytearray(overlay())
        struct.pack_into("<I", bad_overlay, 12, 0xFFFFFFFF)
        for reader, value in [(elf_info, bad_elf), (elf_info, b"\x7fELF"),
                              (overlay_info, bad_overlay), (overlay_info, overlay()[:-1]),
                              (overlay_info, b"MWo3")]:
            with self.assertRaises(FormatError):
                reader(value)


class ExtractionTests(unittest.TestCase):
    def fixture(self, root, malformed=False):
        iso_path = root / "synthetic.iso"
        image = pycdlib.PyCdlib()
        image.new(vol_ident="SO3TEST")
        image.add_fp(BytesIO(elf()), len(elf()), iso_path="/SLUS_204.88;1")
        image.add_fp(BytesIO(b"synthetic config\n"), 17, iso_path="/SYSTEM.CNF;1")
        image.write(str(iso_path))
        image.close()
        encoded = block(0, overlay(), len(overlay()), encrypted=True)
        if malformed:
            encoded = block(2, b"\x00\x01\x00", 3)
        raw_table = table([(1, 1060, 1, 0)])
        with iso_path.open("r+b") as stream:
            stream.seek(TABLE_OFFSET)
            stream.write(raw_table)
            stream.write(encoded.ljust(SECTOR_SIZE, b"\0"))
        profile = {
            "serial": "SYNTHETIC", "disc": 1, "region": "test", "revision": "test",
            "iso_size": iso_path.stat().st_size, "iso_sha256": extract.hash_file(iso_path),
            "boot_file": "SLUS_204.88", "boot_sha256": extract.digest(elf()),
            "table_sha256": extract.digest(raw_table), "populated_entries": 2,
            "sle_key": KEY.hex(), "decoded_checks": {} if malformed else {"1/0": extract.digest(overlay())},
        }
        return iso_path, profile

    def test_pycdlib_extraction_is_repeatable(self):
        with TemporaryDirectory() as folder:
            root = Path(folder)
            iso, profile = self.fixture(root)
            first, second = root / "first", root / "second"
            a = extract.extract(iso, first, profile)
            b = extract.extract(iso, second, profile)
            self.assertEqual(a, b)
            files_a = {p.relative_to(first): p.read_bytes() for p in first.rglob("*") if p.is_file()}
            files_b = {p.relative_to(second): p.read_bytes() for p in second.rglob("*") if p.is_file()}
            self.assertEqual(files_a, files_b)
            self.assertEqual(a["summary"]["code_modules"], 2)
            self.assertEqual((first / "modules/0001-00.bin").read_bytes(), overlay())
            self.assertEqual(extract.hash_file(iso), profile["iso_sha256"])
            self.assertNotIn(str(root), json.dumps(a))
            with self.assertRaisesRegex(FormatError, "output already exists"):
                extract.extract(iso, first, profile)

    def test_wrong_hash_fails_before_output(self):
        with TemporaryDirectory() as folder:
            root = Path(folder)
            iso, profile = self.fixture(root)
            profile["iso_sha256"] = "0" * 64
            with self.assertRaisesRegex(FormatError, "unsupported or modified"):
                extract.extract(iso, root / "result", profile)
            self.assertFalse((root / "result").exists())

    def test_bad_iso_has_a_readable_error(self):
        with TemporaryDirectory() as folder:
            root = Path(folder)
            iso, profile = self.fixture(root)
            with iso.open("r+b") as stream:
                stream.seek(16 * SECTOR_SIZE)
                stream.write(bytes(SECTOR_SIZE))
            profile["iso_sha256"] = extract.hash_file(iso)
            with self.assertRaisesRegex(FormatError, "ISO9660"):
                extract.extract(iso, root / "result", profile)
            self.assertFalse((root / "result").exists())
            self.assertEqual(list(root.glob(".so3-extract-*")), [])

    def test_decode_failure_removes_partial_output(self):
        with TemporaryDirectory() as folder:
            root = Path(folder)
            iso, profile = self.fixture(root, malformed=True)
            with self.assertRaisesRegex(FormatError, "resource 1"):
                extract.extract(iso, root / "result", profile)
            self.assertFalse((root / "result").exists())
            self.assertEqual(list(root.glob(".so3-extract-*")), [])


if __name__ == "__main__":
    unittest.main()
