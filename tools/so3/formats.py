"""Bounded readers for SO3's resource table, SLZ/SLE blocks, and code headers.

Format references and their limitations are recorded in docs/extraction.md.
ISO9660 is handled separately by pycdlib.
"""

from dataclasses import dataclass
import struct


SECTOR_SIZE = 0x800
TABLE_OFFSET = 0x200000
TABLE_SLOTS = 0x1800
TABLE_SIZE = TABLE_SLOTS * 12
TABLE_SIGNATURE = 0x27D51556
TABLE_SEED = 0x13578642
# A resource larger than the EE address space needs explicit investigation.
MAX_DECODED_SIZE = 32 * 1024 * 1024


class FormatError(ValueError):
    """Input does not satisfy the supported format's invariants."""


def require(condition: bool, message: str) -> None:
    if not condition:
        raise FormatError(message)


def classify(data: bytes) -> str:
    if data.startswith(b"\x7fELF"):
        return "ELF"
    if data.startswith(b"MWo3"):
        return "MWo3"
    if len(data) >= 4 and data[:3] in (b"SLZ", b"SLE"):
        return data[:3].decode("ascii") + str(data[3])
    for magic in (b"PACK", b"ZLS", b"TIM2"):
        if data.startswith(magic):
            return magic.decode("ascii")
    return "unknown"


def read_table(raw: bytes, disc_size: int) -> list[dict]:
    require(len(raw) == TABLE_SIZE, "truncated resource table")
    words = list(struct.unpack(f"<{TABLE_SLOTS * 3}I", raw))
    require(words[0] == TABLE_SIGNATURE, "unexpected resource table signature")
    key = TABLE_SEED
    for index in range(TABLE_SLOTS):
        words[index] ^= key
        key = (key ^ (key << 1)) & 0xFFFFFFFF
        words[TABLE_SLOTS + index] ^= key
        key = (key ^ ~TABLE_SEED) & 0xFFFFFFFF
        words[2 * TABLE_SLOTS + index] ^= key
        key = (key ^ (key << 2) ^ TABLE_SEED) & 0xFFFFFFFF
    # The signature occupies the slot that would otherwise encode this LBA.
    words[0] = TABLE_OFFSET // SECTOR_SIZE
    entries = []
    for index in range(TABLE_SLOTS):
        lba, sectors, runtime = (words[index + TABLE_SLOTS * n] for n in range(3))
        if not (lba or sectors or runtime):
            continue
        offset, size = lba * SECTOR_SIZE, sectors * SECTOR_SIZE
        if sectors:
            require(offset + size <= disc_size, f"resource {index} exceeds disc bounds")
        entries.append({
            "index": index,
            "lba": lba,
            "offset": offset,
            "sectors": sectors,
            "allocated_size": size,
            "runtime_word": runtime,
        })
    extents = sorted((e["offset"], e["offset"] + e["allocated_size"], e["index"])
                     for e in entries if e["sectors"])
    for previous, current in zip(extents, extents[1:]):
        require(previous[1] <= current[0],
                f"resources {previous[2]} and {current[2]} overlap")
    require(entries and entries[0]["index"] == 0
            and entries[0]["allocated_size"] == TABLE_SIZE,
            "unexpected table self-allocation")
    return entries


@dataclass(frozen=True)
class Block:
    offset: int
    encoding: str
    compressed_size: int
    next_offset: int
    data: bytes


def _expand(payload: bytes, kind: int, expected: int) -> bytes:
    require(0 <= expected <= MAX_DECODED_SIZE, "decoded size exceeds supported limit")
    if kind == 0:
        require(len(payload) == expected, "stored block size mismatch")
        return payload
    require(kind in (1, 2, 3), f"unsupported compression type {kind}")
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
        # Repeating the available suffix handles overlapping LZ copies.
        pattern = output[-distance:]
        if count <= distance:
            output.extend(pattern[:count])
        else:
            output.extend((pattern * ((count + distance - 1) // distance))[:count])

    flags = remaining = 0
    unit = 2 if kind == 3 else 1
    while True:
        if kind == 2 and len(output) == expected:
            break
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
        distance, length_code = token & 0xFFF, token >> 12
        if kind == 2 and length_code == 15:
            if distance < 0x100:
                value, count = take(1), distance + 19
            else:
                value, count = bytes([distance & 0xFF]), (distance >> 8) + 3
            require(len(output) + count <= expected, "run exceeds declared size")
            output.extend(value * count)
        elif kind in (1, 3) and distance == 0:
            break
        else:
            count = (length_code + (2 if kind == 3 else 3)) * unit
            copy(distance * unit, count)
    require(len(output) == expected, "decoded output is shorter than declared size")
    require(position == len(payload), "unconsumed compressed bytes")
    return bytes(output)


def decode_chain(data: bytes, key: bytes):
    """Yield completely validated blocks, allowing allocation/alignment padding."""
    require(len(key) == 16, "SLE key must contain 16 bytes")
    offset = 0
    while True:
        require(offset + 16 <= len(data), "truncated block header")
        magic, kind = data[offset:offset + 3], data[offset + 3]
        require(magic in (b"SLZ", b"SLE"), "unexpected block signature")
        compressed, decoded, advance = struct.unpack_from("<III", data, offset + 4)
        end = offset + 16 + compressed
        require(end <= len(data), "compressed payload exceeds allocation")
        require(decoded <= MAX_DECODED_SIZE, "decoded size exceeds supported limit")
        require(kind <= 3, f"unsupported compression type {kind}")
        if advance:
            require(advance >= 16 + compressed, "overlapping block chain")
            require(offset + advance + 16 <= len(data), "block chain exceeds allocation")
        payload = data[offset + 16:end]
        if magic == b"SLE":
            payload = bytes(((value - 3 * (index + 1)) & 0xFF) ^ key[index % 16]
                            for index, value in enumerate(payload))
        yield Block(offset, magic.decode("ascii") + str(kind), compressed,
                    advance, _expand(payload, kind, decoded))
        if advance == 0:
            break
        offset += advance


def overlay_info(data: bytes) -> dict:
    require(len(data) >= 0x40 and data[:4] == b"MWo3", "invalid MWo3 header")
    ident, address, text, initialized, bss, init_start, init_end = struct.unpack_from("<7I", data, 4)
    require(0x40 + text + initialized <= len(data), "overlay sections exceed file")
    require(address + len(data) + bss <= 0x100000000, "overlay address range overflows")
    require((init_start == init_end == 0)
            or address <= init_start <= init_end <= address + len(data),
            "invalid overlay initializer range")
    name = data[0x20:0x40].split(b"\0", 1)[0].decode("ascii", errors="backslashreplace")
    return {
        "format": "MWo3", "overlay_id": ident, "name": name,
        "load_address": address, "text_size": text, "data_size": initialized,
        "bss_size": bss, "static_init_start": init_start, "static_init_end": init_end,
    }


def elf_info(data: bytes) -> dict:
    require(len(data) >= 52 and data[:7] == b"\x7fELF\x01\x01\x01", "expected little-endian ELF32")
    elf_type, machine = struct.unpack_from("<HH", data, 16)
    require(machine == 8, "expected MIPS ELF")
    entry, phoff, shoff, flags = struct.unpack_from("<4I", data, 24)
    phsize, phcount, shsize, shcount, names_index = struct.unpack_from("<5H", data, 42)
    require(phcount == 0 or (phsize >= 32 and phoff + phsize * phcount <= len(data)),
            "invalid ELF program header table")
    require(shcount == 0 or (shsize >= 40 and shoff + shsize * shcount <= len(data)),
            "invalid ELF section header table")
    loads = []
    for index in range(phcount):
        kind, start, vaddr, _, filesz, memsz, permissions, alignment = struct.unpack_from(
            "<8I", data, phoff + index * phsize)
        require(start + filesz <= len(data), "ELF segment exceeds file")
        if kind == 1:
            require(filesz <= memsz, "ELF load segment exceeds memory size")
            loads.append({"offset": start, "address": vaddr, "file_size": filesz,
                          "memory_size": memsz, "flags": permissions, "alignment": alignment})
    headers = [struct.unpack_from("<10I", data, shoff + index * shsize)
               for index in range(shcount)]
    for header in headers:
        if header[1] != 8:  # SHT_NOBITS has no file contents.
            require(header[4] + header[5] <= len(data), "ELF section exceeds file")
    names = b""
    if headers:
        require(names_index < len(headers), "invalid ELF section name table")
        header = headers[names_index]
        names = data[header[4]:header[4] + header[5]]
    sections = []
    result = {"format": "ELF", "elf_type": elf_type, "machine": machine,
              "entry_address": entry, "flags": flags, "load_segments": loads,
              "sections": sections}
    for header in headers:
        name = names[header[0]:].split(b"\0", 1)[0].decode("ascii", errors="backslashreplace")
        sections.append({"name": name, "type": header[1], "address": header[3],
                         "offset": header[4], "size": header[5]})
        if name == ".iopmod" and header[5] >= 27:
            raw = data[header[4] + 26:header[4] + header[5]].split(b"\0", 1)[0]
            result["iop_module_name"] = raw.decode("ascii", errors="backslashreplace")
        if name == ".comment":
            result["comments"] = [s.decode("ascii", errors="backslashreplace")
                                  for s in data[header[4]:header[4] + header[5]].split(b"\0") if s]
    return result
