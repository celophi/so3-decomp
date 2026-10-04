"""Reorder an object's per-function .text sections by original address.

CodeWarrior's deferred code generation writes a unit's C functions in reverse
source order, but mwccgap's INCLUDE_ASM stubs are `asm` functions, which the
compiler emits immediately. A partly decompiled deferred unit therefore mixes
two orders. Linkers place input sections in section-header order, so sorting
the .text headers (each with its own relocation sections) by each function's
original address restores the layout. Section contents, symbols and
relocations are unchanged apart from section indices.

MWCC also emits this-adjusting thunks (`@<offset>@<function>`) and
out-of-line copies of inline functions as multiply-defined copies in every
unit that needs them. The original linker kept one copy of each. The thunk
map (thunks) and symbol map (addresses) record where each kept copy is; a unit
keeps its copy only when that address is inside the unit, and the other
copies are renamed out of `.text` so the overlay link discards them. Their
public symbols become undefined references to the kept copies. Mapped vtables
are supplied by resident data; their generated definitions likewise become
references before the overlay linker discards their sections.

Some kept copies are outside every image we have (1070-00 was linked against
an older resident program). Those are listed by name as external copies and
always discarded, without inventing an address.
"""

import re
import struct
from pathlib import Path

ADDRESS_NAME = re.compile(r'func_([0-9A-F]{8})')
SYMBOL_LINE = re.compile(r'^(\S+) = (0x[0-9A-Fa-f]+);', re.M)
SHN_LORESERVE = 0xFF00
STB_MULTIDEF = 13  # MWCC's binding for thunks and inline-function copies
DISCARDED = b'.discarded'


def unit_range(config, unit):
    """Return (start, end) VRAM of a source unit from its Splat configuration."""
    stem = Path(unit).stem
    segments = config['segments']
    for i, segment in enumerate(segments):
        if not isinstance(segment, dict) or segment.get('type') != 'code':
            continue
        subs = segment['subsegments']
        for j, sub in enumerate(subs):
            if sub[2] != stem:
                continue
            following = subs[j + 1][0] if j + 1 < len(subs) else segment_start(segments[i + 1])
            return (segment['vram'] + sub[0] - segment['start'], segment['vram'] + following - segment['start'])
    raise ValueError(f'{unit} is not a code subsegment')


def segment_start(segment):
    return segment['start'] if isinstance(segment, dict) else segment[0]


def symbol_addresses(path):
    """Read name = address entries from a Splat symbol map."""
    return {m.group(1): int(m.group(2), 16) for m in SYMBOL_LINE.finditer(Path(path).read_text())}


def order_text_sections(data, addresses, thunks=None, keep=None, reorder=True, external=None):
    """Return ELF32 little-endian object bytes with .text headers sorted by function address.

    thunks maps compiler thunk names to the original address of their kept copy;
    keep is the unit's (start, end) VRAM range, outside which thunk copies are
    discarded. external names inline-function copies whose kept copy is
    outside every available image; they are always discarded. With
    reorder=False only copy selection and resident vtable references are
    processed.
    """
    thunks = thunks or {}
    external = set(external or ())
    both = sorted(external & set(addresses))
    if both:
        raise ValueError(f'external copies also have a symbol map address: {", ".join(both)}')
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
    dropped = set()
    copies = set()
    for offset in symbols:
        label, _, _, info, _, index = struct.unpack_from('<IIIBBH', data, offset)
        if info & 15 != 2 or index not in texts:
            continue
        symbol = symbol_strings[label:].split(b'\0', 1)[0].decode()
        match = ADDRESS_NAME.fullmatch(symbol)
        if symbol.startswith('@') or info >> 4 >= STB_MULTIDEF:
            # Thunks and out-of-line copies of inline functions are emitted in
            # every unit that needs them; keep the copy the original linker kept.
            if symbol in external:
                copies.add(index)
                dropped.add(index)
                continue
            address = thunks.get(symbol) if symbol.startswith('@') else (
                int(match.group(1), 16) if match else addresses.get(symbol))
            if address is None:
                kind = 'thunk' if symbol.startswith('@') else 'multiply-defined function'
                source = 'thunk map' if symbol.startswith('@') else 'symbol map'
                raise ValueError(f'{kind} {symbol} is not in the {source}')
            copies.add(index)
            if keep is not None and not keep[0] <= address < keep[1]:
                dropped.add(index)
        elif not reorder:
            continue
        else:
            address = int(match.group(1), 16) if match else addresses.get(symbol)
        if address is None:
            raise ValueError(f'no original address for {symbol}')
        if index in key and key[index] != address:
            raise ValueError(f'.text section {index} holds more than one function')
        key[index] = address
    missing = [i for i in texts if i not in key and i not in dropped]
    if reorder and missing:
        raise ValueError(f'.text sections without a function symbol: {missing}')
    kept_copies = [i for i in copies if i not in dropped]
    if not reorder and kept_copies:
        # Where the compiler and the original linker placed kept copies
        # differs (for example the order of inline destructor copies), so any
        # unit that keeps one is placed in original address order.
        return order_text_sections(data, addresses, thunks, keep, reorder=True, external=external)
    if dropped:
        data = discard_sections(data, dropped)
        headers = [list(struct.unpack_from('<10I', data, shoff + i * size)) for i in range(count)]
        texts = [i for i in texts if i not in dropped]
    if keep is not None:
        # Overlay vtables live in retained resident data, not these generated
        # sections. GNU ld diagnoses duplicate definitions before /DISCARD/.
        vtables = {i for i, h in enumerate(headers) if name(h) == '.vtables'}
        data = undefine_symbols(data, vtables, addresses)
    if not reorder:
        return data

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


def merge_rodata_sections(data):
    """Merge an object's .rodata sections into its first one, in section order.

    MWCC gives each jump table its own .rodata section. The linker lays them out
    one after another (each at its own alignment), so merging them in the same
    order and spacing doesn't change the linked bytes. It lets objdiff find each
    table at the same offset as in the original's single .rodata section. Each
    table's relocations move with it; the emptied sections are renamed out of the
    way and discarded by the link.
    """
    if data[:6] != b'\x7fELF\x01\x01':
        raise ValueError('expected a little-endian ELF32 object')
    shoff = struct.unpack_from('<I', data, 32)[0]
    size, count, names_index = struct.unpack_from('<HHH', data, 46)
    headers = [list(struct.unpack_from('<10I', data, shoff + i * size)) for i in range(count)]
    strings = data[headers[names_index][4]:headers[names_index][4] + headers[names_index][5]]

    def name(header):
        return strings[header[0]:].split(b'\0', 1)[0].decode()

    rodata = [i for i, h in enumerate(headers) if name(h) == '.rodata' and h[1] == 1]
    if len(rodata) < 2:
        return data
    first = rodata[0]
    offsets, merged, alignment = {}, bytearray(), 1
    for index in rodata:
        header = headers[index]
        align = max(header[8], 1)
        merged.extend(bytes(-len(merged) % align))
        offsets[index] = len(merged)
        merged.extend(data[header[4]:header[4] + header[5]])
        alignment = max(alignment, align)

    relocations = {i: [j for j, h in enumerate(headers) if h[1] in (4, 9) and h[7] == i] for i in rodata}
    sections = [j for i in rodata for j in relocations[i]]
    kinds = {(headers[j][1], headers[j][6]) for j in sections}
    if len(kinds) > 1 or any(len(relocations[i]) > 1 for i in rodata):
        raise ValueError('.rodata relocation sections differ in kind or symbol table')
    entries = bytearray()
    for index in rodata:
        for j in relocations[index]:
            header = headers[j]
            step = header[9] or (8 if header[1] == 9 else 12)
            for position in range(header[4], header[4] + header[5], step):
                offset = struct.unpack_from('<I', data, position)[0]
                entries.extend(struct.pack('<I', offset + offsets[index]))
                entries.extend(data[position + 4:position + step])

    symtab_index = next(i for i, h in enumerate(headers) if h[1] == 2)
    symtab = headers[symtab_index]
    moved = set(rodata[1:])
    section_symbols = set()
    out = bytearray(data)
    for position in range(symtab[4], symtab[4] + symtab[5], symtab[9]):
        label, value, length, info, other, index = struct.unpack_from('<IIIBBH', data, position)
        if index not in moved:
            continue
        if info & 15 == 3:  # STT_SECTION: left on its emptied section, must stay unused
            section_symbols.add((position - symtab[4]) // symtab[9])
            continue
        struct.pack_into('<IIIBBH', out, position, label, value + offsets[index], length, info, other, first)
    for j, header in enumerate(headers):
        if header[1] in (4, 9):
            step = header[9] or (8 if header[1] == 9 else 12)
            for position in range(header[4], header[4] + header[5], step):
                if struct.unpack_from('<I', data, position + 4)[0] >> 8 in section_symbols:
                    raise ValueError('a relocation refers to a merged .rodata section symbol')

    def append(blob, align):
        out.extend(bytes(-len(out) % align))
        position = len(out)
        out.extend(blob)
        return position

    headers[first][4], headers[first][5], headers[first][8] = append(merged, 16), len(merged), alignment
    if sections:
        kept = sections[0]
        headers[kept][4], headers[kept][5], headers[kept][7] = append(entries, 4), len(entries), first
    names = headers[names_index]
    position = strings.find(DISCARDED + b'\0')
    if position < 0:
        position = len(strings)
        names[4], names[5] = append(strings + DISCARDED + b'\0', 1), len(strings) + len(DISCARDED) + 1
    for index in rodata[1:] + sections[1:]:
        headers[index][0], headers[index][5] = position, 0
    for i, header in enumerate(headers):
        struct.pack_into('<10I', out, shoff + i * size, *header)
    return bytes(out)


def discard_sections(data, indices):
    """Rename sections so the overlay link script's /DISCARD/ rule drops them."""
    shoff = struct.unpack_from('<I', data, 32)[0]
    size, _, names_index = struct.unpack_from('<HHH', data, 46)
    names = list(struct.unpack_from('<10I', data, shoff + names_index * size))
    strings = data[names[4]:names[4] + names[5]]
    out = bytearray(data)
    position = strings.find(DISCARDED + b'\0')
    if position < 0:
        position = len(strings)
        strings += DISCARDED + b'\0'
        names[4], names[5] = len(out), len(strings)
        out.extend(strings)
        struct.pack_into('<10I', out, shoff + names_index * size, *names)
    for index in indices:
        struct.pack_into('<I', out, shoff + index * size, position)
    return undefine_symbols(bytes(out), indices)


def undefine_symbols(data, indices, mapped=None):
    """Make public definitions in discarded sections resolve to their retained owners.

    Symbol indices and relocation records stay unchanged. Local section symbols
    remain local; they are used by metadata that is discarded with the section.
    If mapped is supplied, only symbols with known resident addresses change.
    """
    if not indices:
        return data
    shoff = struct.unpack_from('<I', data, 32)[0]
    size, count = struct.unpack_from('<HH', data, 46)
    out = bytearray(data)
    for i in range(count):
        header = struct.unpack_from('<10I', data, shoff + i * size)
        if header[1] != 2:
            continue
        strings_header = struct.unpack_from('<10I', data, shoff + header[6] * size)
        strings = data[strings_header[4]:strings_header[4] + strings_header[5]]
        for offset in range(header[4], header[4] + header[5], header[9]):
            label, value, length, info, other, index = struct.unpack_from('<IIIBBH', data, offset)
            symbol = strings[label:].split(b'\0', 1)[0].decode()
            if index in indices and info >> 4 and (mapped is None or symbol in mapped):
                # MWCC's multiply-defined binding is not a GNU weak symbol.
                # Use a normal external reference, including for thunk copies.
                struct.pack_into('<IIIBBH', out, offset, label, 0, 0, 0x10 | (info & 15), other, 0)
    return bytes(out)
