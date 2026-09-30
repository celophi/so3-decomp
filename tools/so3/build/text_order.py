"""Reorder an object's per-function .text sections by original address.

CodeWarrior's deferred code generation writes a unit's C functions in reverse
source order, but mwccgap's INCLUDE_ASM stubs are `asm` functions, which the
compiler emits immediately. A partly decompiled deferred unit therefore mixes
two orders. Linkers place input sections in section-header order, so sorting
the .text headers (each with its own relocation sections) by each function's
original address restores the layout. Section contents, symbols and
relocations are unchanged apart from section indices.
"""

import re
import struct
from pathlib import Path

ADDRESS_NAME = re.compile(r'func_([0-9A-F]{8})')
SYMBOL_LINE = re.compile(r'^(\S+) = (0x[0-9A-Fa-f]+);', re.M)
SHN_LORESERVE = 0xFF00


def symbol_addresses(path):
    """Read name = address entries from a Splat symbol map."""
    return {m.group(1): int(m.group(2), 16) for m in SYMBOL_LINE.finditer(Path(path).read_text())}


def order_text_sections(data, addresses):
    """Return ELF32 little-endian object bytes with .text headers sorted by function address."""
    if data[:6] != b'\x7fELF\x01\x01':
        raise ValueError('expected a little-endian ELF32 object')
    shoff = struct.unpack_from('<I', data, 32)[0]
    size, count, names_index = struct.unpack_from('<HHH', data, 46)
    headers = [list(struct.unpack_from('<10I', data, shoff + i * size)) for i in range(count)]
    names = headers[names_index]
    strings = data[names[4]:names[4] + names[5]]

    def name(header):
        return strings[header[0]:].split(b'\0', 1)[0].decode()

    symtab_index = next(i for i, h in enumerate(headers) if h[1] == 2)
    symtab = headers[symtab_index]
    symbol_strings = data[headers[symtab[6]][4]:headers[symtab[6]][4] + headers[symtab[6]][5]]
    symbols = range(symtab[4], symtab[4] + symtab[5], symtab[9])

    texts = [i for i, h in enumerate(headers) if name(h) == '.text']
    key = {}
    for offset in symbols:
        label, _, _, info, _, index = struct.unpack_from('<IIIBBH', data, offset)
        if info & 15 != 2 or index not in texts:
            continue
        symbol = symbol_strings[label:].split(b'\0', 1)[0].decode()
        match = ADDRESS_NAME.fullmatch(symbol)
        address = int(match.group(1), 16) if match else addresses.get(symbol)
        if address is None:
            raise ValueError(f'no original address for {symbol}')
        if index in key and key[index] != address:
            raise ValueError(f'.text section {index} holds more than one function')
        key[index] = address
    missing = [i for i in texts if i not in key]
    if missing:
        raise ValueError(f'.text sections without a function symbol: {missing}')

    # GNU ld's ELF reader creates a relocation section's target when it reaches
    # that relocation section, so each .text moves together with its own
    # relocation sections and keeps them after it.
    relocations = {t: [i for i, h in enumerate(headers) if h[1] in (4, 9) and h[7] == t] for t in texts}
    members = sorted(i for t in texts for i in [t, *relocations[t]])
    ordered = [i for t in sorted(texts, key=lambda i: key[i]) for i in [t, *relocations[t]]]
    remap = {old: old for old in range(count)}
    remap.update(zip(ordered, members))  # old index -> new index
    if all(old == new for old, new in remap.items()):
        return data
    out = bytearray(data)
    new_headers = [None] * count
    for old, header in enumerate(headers):
        new_headers[remap[old]] = header
    for header in new_headers:
        if header[1] in (4, 9):  # SHT_RELA / SHT_REL: sh_info is the target section
            header[7] = remap[header[7]]
        if 0 < header[6] < count:
            header[6] = remap[header[6]]
    for i, header in enumerate(new_headers):
        struct.pack_into('<10I', out, shoff + i * size, *header)
    struct.pack_into('<H', out, 50, remap[names_index])
    for offset in symbols:
        index = struct.unpack_from('<H', data, offset + 14)[0]
        if 0 < index < SHN_LORESERVE:
            struct.pack_into('<H', out, offset + 14, remap[index])
    return bytes(out)
