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

from dataclasses import dataclass, field
import re
import struct
from pathlib import Path

from tools.so3.build.subsegments import segment_start, subsegment_parts

ADDRESS_NAME = re.compile(r'func_([0-9A-F]{8})')
SYMBOL_LINE = re.compile(r'^(\S+) = (0x[0-9A-Fa-f]+);', re.M)
SHN_LORESERVE = 0xFF00
STB_MULTIDEF = 13  # MWCC's binding for thunks and inline-function copies
DISCARDED = b'.discarded'
# Metrowerks' per-function bookkeeping: a small .mwcats record and an exception
# index entry (.exceptix) for each function. MWLDPS2 reads these even when they
# aren't placed, so a dropped copy's own records can't keep pointing at it.
BOOKKEEPING_SECTIONS = ('.mwcats', '.exceptix')


@dataclass
class MovedCopy:
    """A kept copy that had to be moved to where the game has it.

    The compiler writes a copy right after the first function that needs it,
    so a copy in the wrong place means the source is different from the
    original. `after_in_compiler` and `after_in_game` name the function it
    followed in each (None when it came first).
    """
    function: str
    address: int
    after_in_compiler: str | None
    after_in_game: str | None


@dataclass
class DroppedCopy:
    """A copy that was dropped because the game kept one somewhere else.

    `kept_at` is the address of the copy the game kept, or None when it isn't
    in any image we have.
    """
    function: str
    kept_at: int | None


@dataclass
class CopyReport:
    """What order_text_sections did with one object's copies."""
    moved: list = field(default_factory=list)
    dropped: list = field(default_factory=list)


def unit_range(config, unit):
    """Return (start, end) VRAM of a source unit from its Splat configuration."""
    stem = Path(unit).stem
    segments = config['segments']
    for i, segment in enumerate(segments):
        if not isinstance(segment, dict) or segment.get('type') != 'code':
            continue
        subs = segment['subsegments']
        for j, sub in enumerate(subs):
            start, kind, name = subsegment_parts(sub)
            if kind not in ('c', 'cpp') or name != stem:
                continue
            following = segment_start(subs[j + 1]) if j + 1 < len(subs) else segment_start(segments[i + 1])
            return (segment['vram'] + start - segment['start'], segment['vram'] + following - segment['start'])
    raise ValueError(f'{unit} is not a code subsegment')


def symbol_addresses(path):
    """Read name = address entries from a Splat symbol map."""
    return {m.group(1): int(m.group(2), 16) for m in SYMBOL_LINE.finditer(Path(path).read_text())}


def symbol_aliases(path):
    """Use Splat's last name for explicitly permitted same-address function aliases."""
    groups = {}
    for line in Path(path).read_text().splitlines():
        match = SYMBOL_LINE.match(line)
        if match and re.search(r'\btype:func\b', line):
            allowed = bool(re.search(r'\ballow_duplicated:true\b', line, re.I))
            groups.setdefault(int(match.group(2), 16), []).append((match.group(1), allowed))
    return {name: entries[-1][0] for entries in groups.values()
            if len(entries) > 1 and all(allowed for _, allowed in entries)
            for name, _ in entries[:-1]}


def normalize_symbol_aliases(data, aliases):
    """Rename undefined imports only; preserve code, definitions and relocation indices."""
    if not aliases:
        return data
    shoff = struct.unpack_from('<I', data, 32)[0]
    stride, count = struct.unpack_from('<HH', data, 46)
    out = bytearray(data)
    for i in range(count):
        table = struct.unpack_from('<10I', data, shoff + i * stride)
        if table[1] != 2:
            continue
        strings_header = list(struct.unpack_from('<10I', data, shoff + table[6] * stride))
        strings = bytearray(data[strings_header[4]:strings_header[4] + strings_header[5]])
        changed = False
        for offset in range(table[4], table[4] + table[5], table[9]):
            label, _, _, info, _, index = struct.unpack_from('<IIIBBH', data, offset)
            name = strings[label:].split(b'\0', 1)[0].decode()
            if index == 0 and info >> 4 and name in aliases:
                target = aliases[name].encode() + b'\0'
                position = strings.find(target)
                if position < 0:
                    position = len(strings)
                    strings.extend(target)
                struct.pack_into('<I', out, offset, position)
                changed = True
        if changed:
            strings_header[4], strings_header[5] = len(out), len(strings)
            out.extend(strings)
            struct.pack_into('<10I', out, shoff + table[6] * stride, *strings_header)
    return bytes(out)


def order_text_sections(data, addresses, thunks=None, keep=None, reorder=True, external=None, report=None):
    """Return ELF32 little-endian object bytes with .text headers sorted by function address.

    thunks maps compiler thunk names to the original address of their kept copy;
    keep is the unit's (start, end) VRAM range, outside which thunk copies are
    discarded. external names inline-function copies whose kept copy is
    outside every available image; they are always discarded. With
    reorder=False only copy selection and resident vtable references are
    processed. If report (a CopyReport) is given, the copies that were moved
    or dropped are added to it.
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
    function_names = {}
    dropped_copies = []
    for offset in symbols:
        label, _, _, info, _, index = struct.unpack_from('<IIIBBH', data, offset)
        if info & 15 != 2 or index not in texts:
            continue
        symbol = symbol_strings[label:].split(b'\0', 1)[0].decode()
        function_names[index] = symbol
        match = ADDRESS_NAME.fullmatch(symbol)
        if symbol.startswith('@') or info >> 4 >= STB_MULTIDEF:
            # Thunks and out-of-line copies of inline functions are emitted in
            # every unit that needs them; keep the copy the original linker kept.
            if symbol in external:
                copies.add(index)
                dropped.add(index)
                dropped_copies.append(DroppedCopy(symbol, None))
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
                dropped_copies.append(DroppedCopy(symbol, address))
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
        return order_text_sections(data, addresses, thunks, keep, reorder=True, external=external, report=report)
    if report is not None:
        report.dropped += dropped_copies
    if dropped:
        data = discard_sections(data, dropped)
        headers = [list(struct.unpack_from('<10I', data, shoff + i * size)) for i in range(count)]
        texts = [i for i in texts if i not in dropped]
    if keep is not None:
        # Overlay vtables live in retained resident data, not these generated
        # sections. Nothing places the generated ones, and MWLDPS2 refuses a
        # definition in a section it doesn't place, so they become references.
        vtables = {i for i, h in enumerate(headers) if name(h) == '.vtables'}
        data = undefine_symbols(data, vtables, addresses)
    if not reorder:
        return data

    # Each .text moves together with its own relocation sections, which stay
    # right after it, the way the compiler wrote them.
    relocations = {t: [i for i, h in enumerate(headers) if h[1] in (4, 9) and h[7] == t] for t in texts}
    members = sorted(i for t in texts for i in [t, *relocations[t]])
    in_game_order = sorted(texts, key=lambda i: key[i])
    ordered = [i for t in in_game_order for i in [t, *relocations[t]]]
    if report is not None:
        report.moved += moved_copies(texts, in_game_order, copies, function_names, key)
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


def moved_copies(compiler_order, game_order, copies, function_names, addresses):
    """The kept copies whose neighbour before them changes between the two orders."""
    def before(order, index):
        position = order.index(index)
        return function_names.get(order[position - 1]) if position else None

    moved = []
    for index in compiler_order:
        if index in copies and before(compiler_order, index) != before(game_order, index):
            moved.append(MovedCopy(function_names[index], addresses[index],
                                   before(compiler_order, index), before(game_order, index)))
    return moved


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
    out = release_bookkeeping(bytes(out), indices)
    return undefine_symbols(out, indices)


def release_bookkeeping(data, indices):
    """Cut a dropped copy's own bookkeeping loose from it.

    The original linker dropped each copy together with its .mwcats record and
    exception index entry. Here those records stay in the object, but every
    function has its own small relocation table for each of them, so I empty
    the tables that point at a dropped copy. (Turning the entries into
    R_MIPS_NONE made MWLDPS2 crash.) Nothing moves.
    """
    shoff = struct.unpack_from('<I', data, 32)[0]
    size, count, names_index = struct.unpack_from('<HHH', data, 46)
    headers = [struct.unpack_from('<10I', data, shoff + i * size) for i in range(count)]
    names = headers[names_index]
    strings = data[names[4]:names[4] + names[5]]

    def name(header):
        return strings[header[0]:].split(b'\0', 1)[0].decode()

    symtab = next(h for h in headers if h[1] == 2)
    dropped = {number for number, offset in enumerate(range(symtab[4], symtab[4] + symtab[5], symtab[9]))
               if struct.unpack_from('<H', data, offset + 14)[0] in indices}
    out = bytearray(data)
    for number, header in enumerate(headers):
        # SHT_REL tables whose target (sh_info) is a bookkeeping section.
        if header[1] != 9 or name(headers[header[7]]) not in BOOKKEEPING_SECTIONS:
            continue
        targets = {struct.unpack_from('<I', data, position + 4)[0] >> 8
                   for position in range(header[4], header[4] + header[5], 8)}
        if targets & dropped:
            emptied = list(header)
            emptied[5] = 0  # sh_size
            struct.pack_into('<10I', out, shoff + number * size, *emptied)
    return bytes(out)


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
