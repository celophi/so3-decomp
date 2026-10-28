"""Give MWCC's static initializer symbols names the symbol map can match.

A C++ file that defines a global object with a constructor, like boot's
`BootProgram g_boot_program;`, gets a function that MWCC writes for it:
`__sinit_<file>`. It builds the object and registers its destructor with
__register_global_object, passing a 12-byte record in .bss that links the
object into the list of things to destroy.

Two of those names get in the way of objdiff, which pairs functions by name:

- MWCC pads `__sinit_<file>` (and its `.p__sinit_` and `@EX@__sinit_`
  helpers) with spaces to 113 characters. A symbol map line can't hold spaces,
  so I trim them, e.g. to `__sinit_init.cpp`.
- The 12-byte record is called `@<number>`, and the number changes between
  builds. I name it after the initializer instead, e.g.
  `__sinit_init.cpp_destructor_chain`, with `..._chain2` and so on if a file
  has more than one.

Only names change. The code, data and relocations stay as they are, so this
can't affect the built image. Objects without an initializer come back as is.
"""

import re
import struct

from tools.so3.build.elf import (SECTION_HEADER, SHT_NOBITS, SHT_SYMTAB, STT_FUNC, SYMBOL, Symbol,
                                 section_headers, section_table, symbol_type)

INITIALIZER_PREFIX = b'__sinit_'

# The record __register_global_object links into its list: the next record,
# the destructor and the object.
DESTRUCTOR_CHAIN_SIZE = 12

# MWCC's name for a compiler-made local, like `@503`.
COMPILER_LOCAL = re.compile(rb'@\d+')


def read_symbols(data, table, strings):
    """Each symbol in a symbol table: where its entry is, the symbol, and its name."""
    for offset in range(table.offset, table.offset + table.size, table.entry_size):
        symbol = Symbol(*SYMBOL.unpack_from(data, offset))
        yield offset, symbol, strings[symbol.name:].split(b'\0', 1)[0]


def initializer_name(symbols):
    """The trimmed name of the file's initializer function, or None if it has none."""
    for _, symbol, name in symbols:
        if name.startswith(INITIALIZER_PREFIX) and symbol_type(symbol.info) == STT_FUNC:
            return name.rstrip(b' ')
    return None


def is_destructor_chain(symbol, name, headers):
    """Whether a symbol is one of MWCC's unnamed 12-byte records in .bss."""
    in_bss = 0 < symbol.section < len(headers) and headers[symbol.section].type == SHT_NOBITS
    return in_bss and symbol.size == DESTRUCTOR_CHAIN_SIZE and COMPILER_LOCAL.fullmatch(name) is not None


def new_names(symbols, headers):
    """The names to give this table's initializer symbols, keyed by where each entry is."""
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
    """Return the object with its static initializer symbols renamed (see the module docstring)."""
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

        # I add the new names to the end of a copy of the string table, point
        # each symbol at its new name (a symbol entry starts with its name's
        # offset), then put the bigger table at the end of the file.
        for offset, name in renames.items():
            struct.pack_into('<I', out, offset, len(strings))
            strings.extend(name + b'\0')
        moved = strings_header._replace(offset=len(out), size=len(strings))
        out.extend(strings)
        SECTION_HEADER.pack_into(out, header_table + table.link * header_size, *moved)
    return bytes(out)
