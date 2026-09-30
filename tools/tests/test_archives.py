"""Archive bounds and nested discovery tests using synthetic data only."""

from pathlib import Path
import struct
import sys
from tempfile import TemporaryDirectory
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from inventory import Audit
from so3.archives import ioprp_entries, pack_entries, zls_entries
from so3.formats import FormatError


def pack(*members):
    offset = 8 + len(members) * 8
    directory = bytearray(b'PACK' + struct.pack('<HH', 0, len(members)))
    for member in members:
        directory.extend(struct.pack('<II', offset, 0x1000))
        offset += len(member)
    return bytes(directory) + b''.join(members)


def zls(payload):
    stride = (16 + len(payload) + 127) & ~127
    return (b'ZLS\0' + struct.pack('<III', len(payload), 0, stride) + payload
            + bytes(stride - 16 - len(payload)) + b'DNE\0' + struct.pack('<III', 0, stride, 0))


def ioprp():
    def entry(name, ext, size):
        return struct.pack('<10sHI', name.encode(), ext, size)
    directory = (entry('RESET', 8, 0) + entry('ROMDIR', 0, 80)
                 + entry('EXTINFO', 0, 8) + entry('CODE', 0, 5) + bytes(16))
    return directory + bytes(16) + b'CODE!'


class ArchiveTests(unittest.TestCase):
    def test_pack_member_bounds_and_tags(self):
        data = pack(b'one', b'two')
        entries = pack_entries(data)
        self.assertEqual([data[e['offset']:e['end']] for e in entries], [b'one', b'two'])
        self.assertEqual([e['tag'] for e in entries], [0x1000, 0x1000])

    def test_pack_rejects_directory_overlap_backwards_and_external_offsets(self):
        for offset in (0, 26, 1000):
            data = bytearray(pack(b'a', b'b'))
            struct.pack_into('<I', data, 8, offset)
            with self.subTest(offset=offset), self.assertRaises(FormatError):
                pack_entries(data)
        with self.assertRaises(FormatError):
            pack_entries(b'PACK\0\0\x02\0')

    def test_zls_terminator_and_payload(self):
        data = zls(b'payload')
        entries = zls_entries(data)
        self.assertEqual(len(entries), 1)
        self.assertEqual(data[entries[0]['offset']:entries[0]['end']], b'payload')

    def test_zls_rejects_bad_strides_and_missing_terminator(self):
        valid = zls(b'payload')
        for where, value in ((12, 0), (12, 16), (12, 4096), (136, 64)):
            data = bytearray(valid)
            struct.pack_into('<I', data, where, value)
            with self.subTest(where=where, value=value), self.assertRaises(FormatError):
                zls_entries(data)
        with self.assertRaises(FormatError):
            zls_entries(valid[:-16])

    def test_ioprp_alignment_and_unpadded_last_member(self):
        data = ioprp()
        entry = ioprp_entries(data)[-1]
        self.assertEqual(entry['offset'], 96)
        self.assertEqual(data[entry['offset']:entry['end']], b'CODE!')

    def test_ioprp_rejects_member_overflow_and_extinfo_mismatch(self):
        for where, value in ((60, 1000), (44, 9)):
            data = bytearray(ioprp())
            struct.pack_into('<I', data, where, value)
            with self.subTest(where=where), self.assertRaises(FormatError):
                ioprp_entries(data)

    def test_nested_code_discovery_continues_after_unresolved_pack(self):
        overlay = b'MWo3' + struct.pack('<7I', 1, 0x200000, 8, 0, 0, 0, 0) + bytes(32) + bytes(8)
        stored = b'SLZ\0' + struct.pack('<III', len(overlay), len(overlay), 0) + overlay
        external_index = b'PACK' + struct.pack('<HHII', 0, 1, 0x10000, 0)
        data = pack(external_index, zls(stored))
        with TemporaryDirectory() as temporary:
            root = Path(temporary)
            audit = Audit(root, bytes(16))
            audit.visit(data, 'synthetic')
            self.assertEqual(len(audit.unresolved), 1)
            self.assertEqual(len(audit.modules), 1)
            self.assertEqual((root / audit.modules[0]['path']).read_bytes(), overlay)
            self.assertEqual(audit.modules[0]['load_address'], 0x200000)


if __name__ == '__main__':
    unittest.main()
