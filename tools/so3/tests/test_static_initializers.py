"""Tests for renaming the static initializer symbols, using small made-up objects."""

import struct
import unittest

from tools.so3.build.elf import SECTION_HEADER, SYMBOL, Symbol, section_headers
from tools.so3.build.static_initializers import trim_static_initializer_names

PADDED = b'__sinit_init.cpp' + b' ' * 97


def object_with_initializer(initializer=PADDED, chain=b'@503', chain_size=12):
    """A made-up object with an initializer, a destructor record and one other symbol."""
    names = b'\0.init\0.bss\0.strtab\0.symtab\0.shstrtab\0'
    strings = b'\0' + initializer + b'\0' + chain + b'\0g_boot_program\0'
    chain_label = 2 + len(initializer)
    object_label = chain_label + len(chain) + 1
    symbols = bytes(16)
    symbols += SYMBOL.pack(1, 0, 0xBC, 0x02, 0, 1)
    symbols += SYMBOL.pack(chain_label, 0, chain_size, 0x01, 0, 2)
    symbols += SYMBOL.pack(object_label, 0, 0x44, 0x11, 0, 2)
    parts = [('.init', 1, b'CODE'), ('.bss', 8, b''), ('.strtab', 3, strings), ('.symtab', 2, symbols),
             ('.shstrtab', 3, names)]
    data = bytearray(52)
    headers = [bytes(40)]
    for name, kind, payload in parts:
        offset = len(data)
        data.extend(payload)
        link, info, entry_size = (3, 1, 16) if kind == 2 else (0, 0, 0)
        size = 0x60 if kind == 8 else len(payload)
        headers.append(SECTION_HEADER.pack(names.index(name.encode() + b'\0'), kind, 0, 0, offset, size,
                                           link, info, 1, entry_size))
    table = len(data)
    data.extend(b''.join(headers))
    struct.pack_into('<16sHHIIIIIHHHHHH', data, 0, b'\x7fELF\x01\x01\x01' + bytes(9),
                     1, 8, 1, 0, 0, table, 0, 52, 32, 0, 40, len(headers), 5)
    return bytes(data)


def symbol_names(data):
    headers = section_headers(data)
    table = headers[4]
    strings = data[headers[3].offset:headers[3].offset + headers[3].size]
    names = []
    for offset in range(table.offset + 16, table.offset + table.size, 16):
        symbol = Symbol(*SYMBOL.unpack_from(data, offset))
        names.append(strings[symbol.name:].split(b'\0', 1)[0])
    return names


class StaticInitializerTests(unittest.TestCase):
    def test_initializer_padding_is_trimmed(self):
        names = symbol_names(trim_static_initializer_names(object_with_initializer()))
        self.assertEqual(names[0], b'__sinit_init.cpp')

    def test_destructor_chain_is_named_after_the_initializer(self):
        names = symbol_names(trim_static_initializer_names(object_with_initializer()))
        self.assertEqual(names[1], b'__sinit_init.cpp_destructor_chain')

    def test_other_symbols_and_code_keep_their_names_and_bytes(self):
        original = object_with_initializer()
        result = trim_static_initializer_names(original)
        self.assertEqual(symbol_names(result)[2], b'g_boot_program')
        init = section_headers(original)[1]
        self.assertEqual(result[init.offset:init.offset + init.size], b'CODE')

    def test_record_of_another_size_is_left_alone(self):
        names = symbol_names(trim_static_initializer_names(object_with_initializer(chain_size=8)))
        self.assertEqual(names[1], b'@503')

    def test_object_without_an_initializer_is_unchanged(self):
        original = object_with_initializer(initializer=b'update')
        self.assertEqual(trim_static_initializer_names(original), original)


if __name__ == '__main__':
    unittest.main()
