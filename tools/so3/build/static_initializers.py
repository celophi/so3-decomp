"""Rename MWCC's static initializer symbols so the symbol map can match them.

When a C++ file has a global object with a constructor, MWCC writes a
`__sinit_<file>` function (a static initializer) that builds it. It pads that
name with spaces, which a symbol map can't hold, so I trim them. It also makes
a small record in .bss for the object's destructor, named `@` and a number that
changes from build to build. I name it after the initializer instead, like
`__sinit_init.cpp_destructor_chain`.

Only the names change, so the built image comes out the same.
"""

import re
import struct

from tools.so3.build.elf import (SECTION_HEADER, SHT_NOBITS, SHT_SYMTAB, STT_FUNC, SYMBOL, Symbol,
                                 section_headers, section_table, symbol_type)

INITIALIZER_PREFIX = b'__sinit_'

# I think the record holds the next record, the destructor and the object.
DESTRUCTOR_CHAIN_SIZE = 12

# How MWCC names things it made up itself, like `@503`.
COMPILER_LOCAL = re.compile(rb'@\d+')


def read_symbols(data, table, strings):
    """Go through a symbol table, giving each entry's offset, its symbol and its name."""
    for offset in range(table.offset, table.offset + table.size, table.entry_size):
        symbol = Symbol(*SYMBOL.unpack_from(data, offset))
        yield offset, symbol, strings[symbol.name:].split(b'\0', 1)[0]


def initializer_name(symbols):
    """The file's `__sinit_` function name without the spaces, or None if there isn't one."""
    for _, symbol, name in symbols:
        if name.startswith(INITIALIZER_PREFIX) and symbol_type(symbol.info) == STT_FUNC:
            return name.rstrip(b' ')
    return None


def is_destructor_chain(symbol, name, headers):
    """Whether this looks like one of the destructor records in .bss."""
    in_bss = 0 < symbol.section < len(headers) and headers[symbol.section].type == SHT_NOBITS
    return in_bss and symbol.size == DESTRUCTOR_CHAIN_SIZE and COMPILER_LOCAL.fullmatch(name) is not None


def new_names(symbols, headers):
    """The new name for each symbol I want to rename, by its entry's offset."""
    initializer = initializer_name(symbols)
    if initializer is None:
        return {}

    names = {}
    chains = 0
    for offset, symbol, name in symbols:
        if INITIALIZER_PREFIX in name and name.endswith(b' '):
            names[offset] = name.rstrip(b' ')
        elif is_destructor_chain(symbol, name, headers):
            chains += 1
            suffix = str(chains).encode() if chains > 1 else b''
            names[offset] = initializer + b'_destructor_chain' + suffix
    return names


def trim_static_initializer_names(data):
    """Return a copy of the object with its static initializer symbols renamed."""
    headers = section_headers(data)
    header_table, header_size, _, _ = section_table(data)
    out = bytearray(data)
    for table in headers:
        if table.type != SHT_SYMTAB:
            continue

        strings_header = headers[table.link]
        strings = bytearray(data[strings_header.offset:strings_header.offset + strings_header.size])
        renames = new_names(list(read_symbols(data, table, strings)), headers)
        if not renames:
            continue

        # The string table can't grow where it is, so I copy it, add the new
        # names on the end and move it to the end of the file. A symbol finds
        # its name by offset, so I just point the renamed ones at the new names.
        for offset, name in renames.items():
            struct.pack_into('<I', out, offset, len(strings))
            strings.extend(name + b'\0')
        moved = strings_header._replace(offset=len(out), size=len(strings))
        out.extend(strings)
        SECTION_HEADER.pack_into(out, header_table + table.link * header_size, *moved)
    return bytes(out)
