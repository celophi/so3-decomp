"""Small synthetic disc and message banks; no original game data is needed."""

from pathlib import Path
import struct

from tools.so3.disc.extract import digest, hash_file
from tools.so3.formats import SECTOR_SIZE, TABLE_OFFSET
from tools.so3.tests.test_archives import pack, zls
from tools.so3.tests.test_extraction import KEY, block, table


def message_bank(rows: list[tuple[int, int]], payload: bytes) -> bytes:
    """Build a bank from (key, message offset) pairs and an encoded message stream."""
    index_offset = 0x80
    data_offset = index_offset + len(rows) * 8
    file_size = data_offset + len(payload)
    header = bytearray(index_offset)
    header[:16] = b"so3mclib 1.81i".ljust(16, b"\0")
    struct.pack_into("<4I", header, 0x10, index_offset, data_offset, 0, 0)
    struct.pack_into("<II", header, 0x3C, len(rows), file_size)

    index = bytearray()
    for key, message_offset in rows:
        index.extend(struct.pack("<II", key, message_offset))
    return bytes(header + index) + payload


def create_disc_fixture(root: Path, malformed: bool = False) -> tuple[Path, dict, bytes]:
    """Put a nested message bank and an unresolved PACK index in resource one."""
    bank = message_bank([(0x3458, 0)], b"\x01\0")
    encoded = block(0, bank, len(bank), encrypted=True)
    if malformed:
        encoded = block(2, b"\x00\x01\x00", 3)

    external_index = b"PACK" + struct.pack("<HHII", 0, 1, 0x10000, 0)
    resource = pack(zls(encoded), b"opaque-data", external_index)
    resource_sector = 1060
    raw_table = table([
        (1, resource_sector, 1, 0),
        (2, 0, 0, 15),  # Runtime-only slot, with no disc allocation.
    ])
    iso = root / "synthetic.iso"
    with iso.open("wb") as stream:
        stream.seek(TABLE_OFFSET)
        stream.write(raw_table)
        stream.seek(resource_sector * SECTOR_SIZE)
        stream.write(resource.ljust(SECTOR_SIZE, b"\0"))

    profile = {
        "serial": "SYNTHETIC",
        "disc": 1,
        "region": "test",
        "revision": "test",
        "iso_size": iso.stat().st_size,
        "iso_sha256": hash_file(iso),
        "table_sha256": digest(raw_table),
        "populated_entries": 2,
        "sle_key": KEY.hex(),
    }
    return iso, profile, bank
