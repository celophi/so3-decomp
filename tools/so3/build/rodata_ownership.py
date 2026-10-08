"""Keep jump tables in the separate places the original put them.

MWCC puts each switch statement's jump table (the list of code addresses the
switch jumps through) in its own .rodata section. Usually compile.py merges
them all into one, the way the original has them. In a few units though, the
original keeps the tables in separate islands, with other data in between.
I describe those islands in the overlay's Splat config with `rodata_anchors`:
the function that uses each table, plus the table's offset and size inside the
island. subsegments.py reads them for compile.py.

For each island I merge just its tables into one section, named after the
island's linker_section (like .rodata.0036F6C0). The linker script then places
it at the original address.

I'm strict about it. Before changing anything I check that the compiler's
tables really are the ones the config describes. Each one is used by exactly
one function, has the configured size, lands at the configured offset once
alignment is applied, and only jumps into its own function. If anything doesn't
add up I stop instead of guessing. The config never gives table bytes or the
compiler's label names, so a wrong config can't make something look like it
matches.
"""

import re
import struct

from tools.so3.build.elf import (
    E_TYPE, ELF32_LITTLE_ENDIAN, ELF_HEADER_SIZE, EM_MIPS, ET_REL, R_MIPS_32, R_MIPS_HI16, R_MIPS_LO16, REL,
    SECTION_HEADER, SHF_ALLOC, SHN_ABS, SHN_COMMON, SHT_DYNSYM, SHT_NOBITS, SHT_NULL, SHT_PROGBITS, SHT_REL,
    SHT_RELA, SHT_STRTAB, SHT_SYMTAB, SHT_SYMTAB_SHNDX, STT_FUNC, STT_SECTION, SYMBOL, SectionHeader, Symbol,
    relocation_symbol, relocation_type, section_headers, section_table, symbol_type,
)
from tools.so3.build.text_order import merge_rodata_sections
from tools.so3.formats import require

# The section name an island gets, like .rodata.0036F6C0.
ISLAND_SECTION = re.compile(r'\.rodata\.[A-Za-z0-9_.-]+')
# Every jump table entry is one 32-bit code address.
WORD = 4
# Addresses are 32 bits, so nothing can end past this.
ADDRESS_LIMIT = 1 << 32


class CompiledObject:
    """An MWCC object, checked well enough that the rest of this module can trust what it reads."""

    def __init__(self, data):
        self.data = data
        require(len(data) >= ELF_HEADER_SIZE and data[:len(ELF32_LITTLE_ENDIAN)] == ELF32_LITTLE_ENDIAN,
                'expected a little-endian ELF32 object')
        require(struct.unpack_from('<HH', data, E_TYPE) == (ET_REL, EM_MIPS), 'expected a MIPS relocatable object')
        offset, entry_size, count, names_index = section_table(data)
        require(entry_size == SECTION_HEADER.size and count and 0 < names_index < count and
                offset >= ELF_HEADER_SIZE and offset + count * entry_size <= len(data), 'invalid ELF section table')
        self.headers = headers = section_headers(data)
        for index, header in enumerate(headers):
            require(header.type not in (SHT_RELA, SHT_DYNSYM, SHT_SYMTAB_SHNDX),
                    'RELA, dynamic or extended symbol tables are unsupported')
            require(not header.size or header.type == SHT_NOBITS or header.offset + header.size <= len(data),
                    f'section payload outside object: {index}')
            require(not header.alignment or header.alignment & (header.alignment - 1) == 0,
                    f'invalid section alignment: {index}')
        require(headers[names_index].type == SHT_STRTAB, 'section names are not a string table')
        self.section_names = [self.string(headers[names_index], header.name) for header in headers]
        self.symbol_table, self.symbols = self.read_symbols()
        self.relocations = self.read_relocations()

    def payload(self, header):
        return self.data[header.offset:header.offset + header.size]

    def string(self, strings, offset):
        """Read a name from a string table section."""
        blob = self.payload(strings)
        require(offset < len(blob) and b'\0' in blob[offset:], 'invalid ELF string offset')
        try:
            return blob[offset:blob.index(b'\0', offset)].decode('utf-8')
        except UnicodeDecodeError as error:
            raise ValueError('invalid ELF string encoding') from error

    def read_symbols(self):
        """Return the symbol table's index and its symbols, with their names filled in."""
        headers = self.headers
        tables = [index for index, header in enumerate(headers) if header.type == SHT_SYMTAB]
        require(len(tables) == 1, 'owned jump tables require exactly one symbol table')
        table = headers[tables[0]]
        # A symbol table's sh_link is the string table that holds its names.
        require(table.entry_size == SYMBOL.size and table.size % SYMBOL.size == 0 and 0 < table.link < len(headers)
                and headers[table.link].type == SHT_STRTAB, 'invalid ELF symbol table')
        symbols = []
        for fields in SYMBOL.iter_unpack(self.payload(table)):
            symbol = Symbol(*fields)
            symbols.append(symbol._replace(name=self.string(headers[table.link], symbol.name)))
        for symbol in symbols:
            require(symbol.section < len(headers) or symbol.section in (SHN_ABS, SHN_COMMON),
                    'symbol section index outside object')
        return tables[0], symbols

    def read_relocations(self):
        """Every section's relocations, as {section: [(offset, type, symbol index)]}."""
        relocations = {index: [] for index in range(len(self.headers))}
        for index, header in enumerate(self.headers):
            if header.type != SHT_REL:
                continue
            # A relocation section's sh_link is its symbol table, and sh_info is the section it applies to.
            require(header.link == self.symbol_table and 0 < header.info < len(self.headers) and
                    header.entry_size in (0, REL.size) and header.size % REL.size == 0,
                    f'invalid REL section: {index}')
            target = self.headers[header.info]
            require(target.type not in (SHT_NULL, SHT_NOBITS), 'REL target must contain actual bytes')
            for offset, info in REL.iter_unpack(self.payload(header)):
                require(relocation_symbol(info) < len(self.symbols), 'REL symbol index outside symbol table')
                # The relocations I check here all write one word. Other kinds
                # are text_order.py's business, so I only make sure they stay
                # inside their section.
                require(offset + WORD <= target.size, 'REL write outside target section')
                relocations[header.info].append((offset, relocation_type(info), relocation_symbol(info)))
        return relocations

    def word(self, header, offset):
        return struct.unpack_from('<I', self.payload(header), offset)[0]


def rename_sections(data, names):
    """Return a copy of the object with some sections renamed, given {section index: new name}.

    Any new names go into a fresh copy of the section names table, added to the
    end of the file, so nothing else has to move.
    """
    output = bytearray(data)
    offset, entry_size, count, names_index = section_table(data)
    names_header = SectionHeader(*SECTION_HEADER.unpack_from(data, offset + names_index * entry_size))
    strings = bytearray(data[names_header.offset:names_header.offset + names_header.size])
    for index, name in names.items():
        require(0 <= index < count, 'section rename index outside object')
        encoded = name.encode() + b'\0'
        position = strings.find(encoded)
        if position < 0:
            position = len(strings)
            strings.extend(encoded)
        # sh_name is the first field of a section header.
        struct.pack_into('<I', output, offset + index * entry_size, position)
    names_header = names_header._replace(offset=len(output), size=len(strings))
    output.extend(strings)
    SECTION_HEADER.pack_into(output, offset + names_index * entry_size, *names_header)
    return bytes(output)


def config_integer(value, message):
    """Check a number from the config fits in 32 bits."""
    require(type(value) is int and 0 <= value < ADDRESS_LIMIT, message)
    return value


def signed_low_half(word):
    """The low 16 bits of an instruction, read as signed the way addiu and loads use them."""
    low = word & 0xFFFF
    return low - 0x10000 if low >= 0x8000 else low


def owning_function(obj, name):
    """Find the one function the config says uses a table."""
    functions = [symbol for symbol in obj.symbols
                 if symbol.name == name and 0 < symbol.section < len(obj.headers) and symbol_type(symbol.info) == STT_FUNC]
    require(len(functions) == 1, f'rodata owner is not one defined function: {name}')
    function = functions[0]
    require(obj.section_names[function.section] == '.text' and function.size > 0 and
            function.value + function.size <= obj.headers[function.section].size, 'invalid owning function extent')
    return function


def referenced_table(obj, function, tables):
    """The one jump table a function's code refers to."""
    start, end = function.value, function.value + function.size
    targets = {symbol for offset, _, symbol in obj.relocations[function.section]
               if start <= offset < end and obj.symbols[symbol].section in tables}
    require(len(targets) == 1, f'rodata owner has ambiguous compiler table references: {function.name}')
    return obj.symbols[targets.pop()]


def anchored_table(obj, anchor, island_size, tables, owners):
    """Match one configured anchor to the compiler's table and claim it in `owners`."""
    size = config_integer(anchor['size'], 'invalid native table size')
    offset = config_integer(anchor['offset'], 'invalid native table offset')
    name = anchor['function']
    seen = {function.name for function, _ in owners.values()}
    require(name not in seen and size > 0 and size % WORD == 0 and offset % WORD == 0 and offset + size <= island_size,
            'invalid or repeated native table anchor')
    function = owning_function(obj, name)
    table = referenced_table(obj, function, tables)
    index = table.section
    # The table symbol has to be its whole section, and the configured size.
    require(index not in owners and table.value == 0 and table.size == obj.headers[index].size == size,
            f'compiler table extent or ownership differs: {name}')
    owners[index] = (function, table)
    return dict(function=name, compiler_symbol=table.name, section=index, size=table.size, native_offset=offset)


def check_island_layout(obj, address, size, entries):
    """Check that the tables, laid out with the compiler's alignment, land at their configured offsets.

    That's what the linker will do when it merges them, so if this works out
    the island comes out the same as the original.
    """
    sections = [entry['section'] for entry in entries]
    require(sections == sorted(sections), 'compiler table order differs from native ownership')
    cursor = 0
    for entry in entries:
        alignment = max(obj.headers[entry['section']].alignment, 1)
        require(address % alignment == 0, 'native island address violates compiler alignment')
        cursor = (cursor + alignment - 1) // alignment * alignment
        require(cursor == entry['native_offset'], 'compiler alignment does not reproduce native table offset')
        cursor += entry['size']
    require(cursor == size, 'compiler tables do not cover configured native island')


def match_island(obj, group, tables, islands, owners):
    """Match one configured island to the compiler's tables."""
    selector = group['section']
    require(isinstance(selector, str) and ISLAND_SECTION.fullmatch(selector) and
            selector not in {island['section'] for island in islands} and selector not in obj.section_names,
            'owned linker selector is invalid or already exists')
    address = config_integer(group['address'], 'invalid native island address')
    size = config_integer(group['size'], 'invalid native island extent')
    require(size > 0 and address + size <= ADDRESS_LIMIT and group['anchors'], 'empty or overflowing native island')
    entries = [anchored_table(obj, anchor, size, tables, owners) for anchor in group['anchors']]
    check_island_layout(obj, address, size, entries)
    return dict(section=selector, address=address, size=size, tables=entries)


def check_table_contents(obj, owners):
    """Check every entry of every owned table jumps somewhere inside the function that owns it."""
    for index, (function, _) in owners.items():
        header = obj.headers[index]
        for symbol in obj.symbols:
            if symbol.section == index:
                require(symbol.value <= header.size and symbol.size <= header.size - symbol.value,
                        'table alias extends outside its compiler section')
        records = obj.relocations[index]
        require(len(records) == header.size // WORD and {offset for offset, _, _ in records} == set(range(0, header.size, WORD)),
                'jump table must have one relocation for each word')
        for offset, kind, target_index in records:
            target = obj.symbols[target_index]
            require(offset % WORD == 0 and kind == R_MIPS_32 and target.section == function.section,
                    'jump table destination is not in its owning function')
            # Each entry is the target symbol's address plus the word already stored there.
            destination = target.value + obj.word(header, offset)
            require(destination % WORD == 0 and function.value <= destination and
                    destination + WORD <= function.value + function.size,
                    'jump table destination lies outside its owning function')


def check_references_to_tables(obj, owners):
    """Check nothing else in the object points past the end of an owned table.

    Once the tables move, a reference that reached from one table into the
    next would point at the wrong thing.
    """
    for index, records in obj.relocations.items():
        # A lui (HI16) is followed by its addiu or load (LO16). I keep the high
        # halves until the matching low half shows up, then add them together.
        pending = {}
        for offset, kind, target_index in records:
            target = obj.symbols[target_index]
            if target.section not in owners:
                continue
            require(symbol_type(target.info) != STT_SECTION, 'references to owned section symbols are unsupported')
            require(offset % WORD == 0, 'unaligned relocation to an owned table')
            word = obj.word(obj.headers[index], offset)
            extent = obj.headers[target.section].size
            if kind == R_MIPS_HI16:
                pending.setdefault(target_index, []).append(word & 0xFFFF)
                continue
            if kind == R_MIPS_LO16:
                require(target_index in pending, 'owned table LO16 has no preceding matching HI16')
                addends = [(high << 16) + signed_low_half(word) for high in pending.pop(target_index)]
            elif kind == R_MIPS_32:
                addends = [word]
            else:
                raise ValueError('unsupported relocation to an owned table')
            for addend in addends:
                require(0 <= target.value + addend < extent, 'relocation effective target crosses compiler table boundary')
        require(not pending, 'owned table HI16 has no matching LO16')


def group_islands(data, rodata_sections, islands):
    """Merge each island's tables into one section with the island's name."""
    # First I rename every .rodata section out of the way, empty ones too,
    # because merge_rodata_sections merges into the first section called
    # .rodata, even when it's empty.
    data = rename_sections(data, {index: f'.rodata.pending.{index}' for index in rodata_sections})
    for island in islands:
        # Then for each island, only its tables are called .rodata while they get merged.
        sections = [entry['section'] for entry in island['tables']]
        data = rename_sections(data, {index: '.rodata' for index in sections})
        data = merge_rodata_sections(data)
        data = rename_sections(data, {sections[0]: island['section']})
    return data


def owned_rodata_sections(data, groups):
    """Merge the compiler's jump tables island by island, as the config describes.

    `groups` comes from subsegments.configured_rodata_groups. Returns the new
    object and what I matched in each island.
    """
    obj = CompiledObject(data)
    rodata_sections = [index for index, name in enumerate(obj.section_names) if name == '.rodata']
    require(all(obj.headers[index].type == SHT_PROGBITS and obj.headers[index].flags == SHF_ALLOC
                for index in rodata_sections), 'ordinary rodata must be allocatable readonly PROGBITS')
    tables = {index for index in rodata_sections if obj.headers[index].size}
    islands, owners = [], {}
    for group in groups:
        islands.append(match_island(obj, group, tables, islands, owners))
    spans = sorted((island['address'], island['address'] + island['size']) for island in islands)
    require(all(end <= start for (_, end), (start, _) in zip(spans, spans[1:])), 'native data islands overlap')
    require(set(owners) == tables, 'compiler rodata is not completely covered by native ownership')
    check_table_contents(obj, owners)
    check_references_to_tables(obj, owners)
    return group_islands(data, rodata_sections, islands), islands
