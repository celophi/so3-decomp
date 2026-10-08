"""Readers for the game's own file formats: the resource table, SLZ/SLE blocks, and code headers.

Most of the game's data isn't in the disc's filesystem. It sits behind a
resource table near the start of the disc, and a lot of it is compressed (SLZ)
or compressed and encrypted (SLE). This module reads those, plus the headers of
the two kinds of code module I find: ELF files and MWo3 overlays. The
filesystem itself is pycdlib's job.

Every reader checks sizes and offsets before it trusts them, and raises
FormatError the moment something doesn't look like the discs I support.
"""

from dataclasses import dataclass
import struct

from tools.so3.build.elf import (
    E_ENTRY, E_PHENTSIZE, E_TYPE, ELF32_LITTLE_ENDIAN, ELF_HEADER_SIZE, EM_MIPS, PROGRAM_HEADER, PT_LOAD,
    SECTION_HEADER, SHT_NOBITS, ProgramHeader, SectionHeader,
)

SECTOR_SIZE = 0x800

# The resource table is 2 MiB into the disc. It has 0x1800 slots, stored as
# three arrays of 32-bit words one after another: each resource's first
# sector, its sector count, and a word the game uses at runtime. The words are
# scrambled with a rolling key that starts from TABLE_SEED, and the first word
# holds TABLE_SIGNATURE instead of the table's own sector.
TABLE_OFFSET = 0x200000
TABLE_SLOTS = 0x1800
TABLE_ARRAYS = 3
TABLE_SIZE = TABLE_SLOTS * TABLE_ARRAYS * 4
TABLE_SIGNATURE = 0x27D51556
TABLE_SEED = 0x13578642
WORD_MASK = 0xFFFFFFFF

# The PS2 has 32 MiB of main memory, so nothing the game decodes can be bigger.
# Anything that claims to be needs a closer look.
MAX_DECODED_SIZE = 32 * 1024 * 1024

# Every overlay file starts with a 64-byte MWo3 header. Its last 32 bytes hold
# the overlay's name, and the code and data come right after it.
OVERLAY_HEADER_SIZE = 0x40
OVERLAY_NAME_OFFSET = 0x20
OVERLAY_MAGIC = b"MWo3"
# After the magic: the id, load address, code, data, and bss sizes, then the static initializer range.
OVERLAY_FIELDS = struct.Struct("<7I")
ADDRESS_LIMIT = 1 << 32

# An IOP module's .iopmod section ends with the module's name, after 26 bytes
# of addresses and sizes.
IOPMOD_NAME_OFFSET = 26

# Every SLZ or SLE block starts with a 16-byte header: "SLZ" or "SLE", the
# compression type, the compressed size, the decoded size, and how far ahead
# the next block in the chain starts (0 for the last one).
BLOCK_HEADER = struct.Struct("<3sBIII")
BLOCK_MAGICS = (b"SLZ", b"SLE")
SLE_KEY_SIZE = 16

# Compression types. The three LZ types use a flag bit per item to say whether
# it's a literal or a back reference. A back reference is a 16-bit token: a
# 12-bit distance back into the output and a 4-bit length code.
STORED = 0  # Not compressed at all.
LZ_BYTES = 1  # Byte-sized items. A distance of 0 marks the end.
LZ_RUNS = 2  # Like LZ_BYTES, but length code 15 means a run of one repeated byte. Ends at the declared size.
LZ_WORDS = 3  # 16-bit items, otherwise like LZ_BYTES.
DISTANCE_MASK = 0xFFF
LENGTH_SHIFT = 12
RUN_CODE = 15
# A back reference always copies at least this many items.
MIN_MATCH = {LZ_BYTES: 3, LZ_RUNS: 3, LZ_WORDS: 2}
# Runs come in two forms. A long run has its count in the token's low 8 bits
# and the repeated byte after it. A short run has its count in bits 8-11 and
# the byte in the low 8 bits.
LONG_RUN_LIMIT = 0x100
LONG_RUN_MIN = 19
SHORT_RUN_MIN = 3

# The first bytes of the other formats classify() knows.
SIMPLE_MAGICS = (b"PACK", b"ZLS", b"TIM2")


class FormatError(ValueError):
    """Input does not satisfy the supported format's invariants."""


def require(condition: bool, message: str) -> None:
    if not condition:
        raise FormatError(message)


def classify(data: bytes) -> str:
    """Name a file's format from its first few bytes, or 'unknown'.

    SLZ and SLE get their compression type added, like SLZ3.
    """
    if data.startswith(ELF32_LITTLE_ENDIAN[:4]):
        return "ELF"
    if data.startswith(OVERLAY_MAGIC):
        return "MWo3"
    if len(data) >= 4 and data[:3] in BLOCK_MAGICS:
        return data[:3].decode("ascii") + str(data[3])
    for magic in SIMPLE_MAGICS:
        if data.startswith(magic):
            return magic.decode("ascii")
    return "unknown"


def unscramble_table(words: list) -> None:
    """Undo the rolling-key scrambling on the table's words, in place."""
    key = TABLE_SEED
    for index in range(TABLE_SLOTS):
        words[index] ^= key
        key = (key ^ (key << 1)) & WORD_MASK
        words[TABLE_SLOTS + index] ^= key
        key = (key ^ ~TABLE_SEED) & WORD_MASK
        words[2 * TABLE_SLOTS + index] ^= key
        key = (key ^ (key << 2) ^ TABLE_SEED) & WORD_MASK


def read_table(raw: bytes, disc_size: int) -> list[dict]:
    """Read the resource table into one entry for each slot that's in use.

    The entries can't reach past the end of the disc or overlap each other,
    and entry 0 has to be the table itself.
    """
    require(len(raw) == TABLE_SIZE, "truncated resource table")
    words = list(struct.unpack(f"<{TABLE_SLOTS * TABLE_ARRAYS}I", raw))
    require(words[0] == TABLE_SIGNATURE, "unexpected resource table signature")
    unscramble_table(words)
    # The signature sits where the table's own first sector would be.
    words[0] = TABLE_OFFSET // SECTOR_SIZE
    entries = []
    for index in range(TABLE_SLOTS):
        sector, sectors, runtime = (words[index + TABLE_SLOTS * array] for array in range(TABLE_ARRAYS))
        if not (sector or sectors or runtime):
            continue
        offset, size = sector * SECTOR_SIZE, sectors * SECTOR_SIZE
        if sectors:
            require(offset + size <= disc_size, f"resource {index} exceeds disc bounds")
        entries.append({
            "index": index,
            "lba": sector,
            "offset": offset,
            "sectors": sectors,
            "allocated_size": size,
            "runtime_word": runtime,
        })
    extents = sorted((entry["offset"], entry["offset"] + entry["allocated_size"], entry["index"])
                     for entry in entries if entry["sectors"])
    for previous, current in zip(extents, extents[1:]):
        require(previous[1] <= current[0], f"resources {previous[2]} and {current[2]} overlap")
    require(entries and entries[0]["index"] == 0 and entries[0]["allocated_size"] == TABLE_SIZE,
            "unexpected table self-allocation")
    return entries


@dataclass(frozen=True)
class Block:
    """One decoded block of an SLZ/SLE chain."""
    offset: int
    encoding: str
    compressed_size: int
    next_offset: int
    data: bytes


def expand(payload: bytes, kind: int, expected: int) -> bytes:
    """Decompress one block's payload into exactly `expected` bytes."""
    require(0 <= expected <= MAX_DECODED_SIZE, "decoded size exceeds supported limit")
    if kind == STORED:
        require(len(payload) == expected, "stored block size mismatch")
        return payload
    require(kind in (LZ_BYTES, LZ_RUNS, LZ_WORDS), f"unsupported compression type {kind}")
    output = bytearray()
    position = 0

    def take(count: int) -> bytes:
        nonlocal position
        require(position + count <= len(payload), "truncated compressed stream")
        chunk = payload[position:position + count]
        position += count
        return chunk

    def append(chunk: bytes) -> None:
        require(len(output) + len(chunk) <= expected, "decoded output exceeds declared size")
        output.extend(chunk)

    def copy(distance: int, count: int) -> None:
        require(0 < distance <= len(output), "invalid backreference distance")
        require(len(output) + count <= expected, "backreference exceeds declared size")
        # A copy can be longer than its distance, overlapping what it's
        # writing. Repeating the copied bytes gives the same result.
        pattern = output[-distance:]
        if count <= distance:
            output.extend(pattern[:count])
        else:
            output.extend((pattern * ((count + distance - 1) // distance))[:count])

    flags = remaining = 0
    unit = 2 if kind == LZ_WORDS else 1
    while True:
        if kind == LZ_RUNS and len(output) == expected:
            break
        # The flags for the next items come in one unit, a bit per item.
        if remaining == 0:
            flags = int.from_bytes(take(unit), "little")
            remaining = unit * 8
        literal = flags & 1
        flags >>= 1
        remaining -= 1
        if literal:
            append(take(unit))
            continue
        token = int.from_bytes(take(2), "little")
        distance, length_code = token & DISTANCE_MASK, token >> LENGTH_SHIFT
        if kind == LZ_RUNS and length_code == RUN_CODE:
            if distance < LONG_RUN_LIMIT:
                value, count = take(1), distance + LONG_RUN_MIN
            else:
                value, count = bytes([distance & 0xFF]), (distance >> 8) + SHORT_RUN_MIN
            require(len(output) + count <= expected, "run exceeds declared size")
            output.extend(value * count)
        elif kind in (LZ_BYTES, LZ_WORDS) and distance == 0:
            break
        else:
            copy(distance * unit, (length_code + MIN_MATCH[kind]) * unit)
    require(len(output) == expected, "decoded output is shorter than declared size")
    require(position == len(payload), "unconsumed compressed bytes")
    return bytes(output)


def decrypt_sle(payload: bytes, key: bytes) -> bytes:
    """Undo SLE's encryption: subtract 3 * (position + 1) from each byte, then XOR it with the key."""
    return bytes(((value - 3 * (index + 1)) & 0xFF) ^ key[index % SLE_KEY_SIZE]
                 for index, value in enumerate(payload))


def decode_chain(data: bytes, key: bytes):
    """Decode every block in an SLZ/SLE chain, yielding each one.

    A chain is often followed by padding up to its allocation, which is fine.
    """
    require(len(key) == SLE_KEY_SIZE, "SLE key must contain 16 bytes")
    offset = 0
    while True:
        require(offset + BLOCK_HEADER.size <= len(data), "truncated block header")
        magic, kind, compressed, decoded, advance = BLOCK_HEADER.unpack_from(data, offset)
        require(magic in BLOCK_MAGICS, "unexpected block signature")
        start = offset + BLOCK_HEADER.size
        end = start + compressed
        require(end <= len(data), "compressed payload exceeds allocation")
        require(decoded <= MAX_DECODED_SIZE, "decoded size exceeds supported limit")
        require(kind <= LZ_WORDS, f"unsupported compression type {kind}")
        if advance:
            require(advance >= BLOCK_HEADER.size + compressed, "overlapping block chain")
            require(offset + advance + BLOCK_HEADER.size <= len(data), "block chain exceeds allocation")
        payload = data[start:end]
        if magic == b"SLE":
            payload = decrypt_sle(payload, key)
        yield Block(offset, magic.decode("ascii") + str(kind), compressed, advance, expand(payload, kind, decoded))
        if advance == 0:
            break
        offset += advance


def overlay_info(data: bytes) -> dict:
    """Read an MWo3 overlay's header."""
    require(len(data) >= OVERLAY_HEADER_SIZE and data[:len(OVERLAY_MAGIC)] == OVERLAY_MAGIC, "invalid MWo3 header")
    ident, address, text, initialized, bss, init_start, init_end = OVERLAY_FIELDS.unpack_from(data, len(OVERLAY_MAGIC))
    require(OVERLAY_HEADER_SIZE + text + initialized <= len(data), "overlay sections exceed file")
    require(address + len(data) + bss <= ADDRESS_LIMIT, "overlay address range overflows")
    # The static initializers (constructors for C++ globals) are either absent or inside the overlay.
    require((init_start == init_end == 0) or address <= init_start <= init_end <= address + len(data),
            "invalid overlay initializer range")
    name = data[OVERLAY_NAME_OFFSET:OVERLAY_HEADER_SIZE].split(b"\0", 1)[0].decode("ascii", errors="backslashreplace")
    return {
        "format": "MWo3", "overlay_id": ident, "name": name,
        "load_address": address, "text_size": text, "data_size": initialized,
        "bss_size": bss, "static_init_start": init_start, "static_init_end": init_end,
    }


def section_bytes(data: bytes, section: SectionHeader) -> bytes:
    return data[section.offset:section.offset + section.size]


def ascii_text(raw: bytes) -> str:
    return raw.decode("ascii", errors="backslashreplace")


def elf_info(data: bytes) -> dict:
    """Read the parts of an ELF file's headers the manifests record.

    That's the load segments and the section list, plus the IOP module name
    and the compiler's comments when the file has them.
    """
    require(len(data) >= ELF_HEADER_SIZE and data[:len(ELF32_LITTLE_ENDIAN)] == ELF32_LITTLE_ENDIAN,
            "expected little-endian ELF32")
    elf_type, machine = struct.unpack_from("<HH", data, E_TYPE)
    require(machine == EM_MIPS, "expected MIPS ELF")
    entry, program_offset, section_offset, flags = struct.unpack_from("<4I", data, E_ENTRY)
    program_size, program_count, section_size, section_count, names_index = struct.unpack_from("<5H", data, E_PHENTSIZE)
    require(program_count == 0 or (program_size >= PROGRAM_HEADER.size
                                   and program_offset + program_size * program_count <= len(data)),
            "invalid ELF program header table")
    require(section_count == 0 or (section_size >= SECTION_HEADER.size
                                   and section_offset + section_size * section_count <= len(data)),
            "invalid ELF section header table")
    loads = []
    for index in range(program_count):
        segment = ProgramHeader(*PROGRAM_HEADER.unpack_from(data, program_offset + index * program_size))
        require(segment.offset + segment.file_size <= len(data), "ELF segment exceeds file")
        if segment.type == PT_LOAD:
            require(segment.file_size <= segment.memory_size, "ELF load segment exceeds memory size")
            loads.append({"offset": segment.offset, "address": segment.address, "file_size": segment.file_size,
                          "memory_size": segment.memory_size, "flags": segment.flags,
                          "alignment": segment.alignment})
    headers = [SectionHeader(*SECTION_HEADER.unpack_from(data, section_offset + index * section_size))
               for index in range(section_count)]
    for header in headers:
        if header.type != SHT_NOBITS:
            require(header.offset + header.size <= len(data), "ELF section exceeds file")
    names = b""
    if headers:
        require(names_index < len(headers), "invalid ELF section name table")
        names = section_bytes(data, headers[names_index])
    sections = []
    result = {"format": "ELF", "elf_type": elf_type, "machine": machine,
              "entry_address": entry, "flags": flags, "load_segments": loads,
              "sections": sections}
    for header in headers:
        name = ascii_text(names[header.name:].split(b"\0", 1)[0])
        sections.append({"name": name, "type": header.type, "address": header.address,
                         "offset": header.offset, "size": header.size})
        if name == ".iopmod" and header.size > IOPMOD_NAME_OFFSET:
            raw = data[header.offset + IOPMOD_NAME_OFFSET:header.offset + header.size].split(b"\0", 1)[0]
            result["iop_module_name"] = ascii_text(raw)
        if name == ".comment":
            result["comments"] = [ascii_text(text) for text in section_bytes(data, header).split(b"\0") if text]
    return result
