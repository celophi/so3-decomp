"""Ordering .text sections by original address, on synthetic objects."""

import struct
import unittest

from tools.so3.build.compiler_probe import object_functions
from tools.so3.build.text_order import order_text_sections, unit_range
from tools.so3.tests.test_compiler_probe import object_fixture


def text_payloads(data):
    shoff = struct.unpack_from('<I', data, 32)[0]
    count = struct.unpack_from('<H', data, 48)[0]
    headers = [struct.unpack_from('<10I', data, shoff + i * 40) for i in range(count)]
    names = headers[struct.unpack_from('<H', data, 50)[0]]
    strings = data[names[4]:names[4] + names[5]]
    return [data[h[4]:h[4] + h[5]] for h in headers if strings[h[0]:].startswith(b'.text\0')]


def relocation_target(data):
    shoff = struct.unpack_from('<I', data, 32)[0]
    count = struct.unpack_from('<H', data, 48)[0]
    return [struct.unpack_from('<10I', data, shoff + i * 40)[7] for i in range(count)
            if struct.unpack_from('<10I', data, shoff + i * 40)[1] == 9][0]


class TextOrderTests(unittest.TestCase):
    def test_sections_follow_function_addresses(self):
        data = order_text_sections(object_fixture(), {'first': 0x200, 'second': 0x100})
        self.assertEqual(text_payloads(data), [b'BBBB', b'AAAA'])
        self.assertEqual(object_functions(data)[1], {'first': b'AAAA', 'second': b'BBBB'})

    def test_relocations_keep_their_function(self):
        data = order_text_sections(object_fixture(relocated=True), {'first': 0x200, 'second': 0x100})
        self.assertEqual(text_payloads(data), [b'BBBB', b'AAAA'])
        self.assertEqual(relocation_target(data), 2)

    def test_relocation_sections_follow_their_text(self):
        data = order_text_sections(object_fixture(relocated=True), {'first': 0x200, 'second': 0x100})
        shoff = struct.unpack_from('<I', data, 32)[0]
        count = struct.unpack_from('<H', data, 48)[0]
        for i in range(count):
            header = struct.unpack_from('<10I', data, shoff + i * 40)
            if header[1] == 9:
                self.assertLess(header[7], i)

    def test_sorted_object_is_unchanged(self):
        original = object_fixture()
        self.assertEqual(order_text_sections(original, {'first': 0x100, 'second': 0x200}), original)

    def test_unknown_function_address_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'no original address for second'):
            order_text_sections(object_fixture(), {'first': 0x100})


    def test_thunk_outside_the_unit_is_discarded(self):
        data = order_text_sections(thunk_fixture(), {}, {'@8@fir': 0x300}, keep=(0x100, 0x200), reorder=False)
        self.assertEqual(section_names(data), ['.text', '.discarded'])

    def test_thunk_inside_the_unit_is_kept_and_ordered(self):
        data = order_text_sections(thunk_fixture(), {'first': 0x180}, {'@8@fir': 0x100}, keep=(0x100, 0x200))
        self.assertEqual(text_payloads(data), [b'TTTT', b'AAAA'])

    def test_unmapped_thunk_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'thunk @8@fir is not in the thunk map'):
            order_text_sections(thunk_fixture(), {}, {}, keep=(0x100, 0x200), reorder=False)

    def test_unit_range_uses_the_next_subsegment(self):
        config = {'segments': [{'name': 'header', 'type': 'bin', 'start': 0},
                               {'name': 'text', 'type': 'code', 'start': 0x40, 'vram': 0x1000,
                                'subsegments': [[0x40, 'cpp', 'a'], [0x80, 'cpp', 'b']]},
                               [0x100, 'bin', 'data'], [0x200]]}
        self.assertEqual(unit_range(config, 'src/x/a.cpp'), (0x1000, 0x1040))
        self.assertEqual(unit_range(config, 'src/x/b.cpp'), (0x1040, 0x10C0))

    def test_inline_copy_outside_the_unit_is_discarded(self):
        data = order_text_sections(multidef_fixture(), {'second': 0x300}, {}, keep=(0x100, 0x200), reorder=False)
        self.assertEqual(section_names(data), ['.text', '.discarded'])

    def test_kept_inline_copy_puts_the_unit_in_address_order(self):
        data = order_text_sections(multidef_fixture(), {'first': 0x180, 'second': 0x100}, {},
                                   keep=(0x100, 0x200), reorder=False)
        self.assertEqual(text_payloads(data), [b'BBBB', b'AAAA'])

    def test_unmapped_inline_copy_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'multiply-defined function second is not in the symbol map'):
            order_text_sections(multidef_fixture(), {}, {}, keep=(0x100, 0x200), reorder=False)


def multidef_fixture():
    """first (AAAA) and a multiply-defined copy named second (BBBB)."""
    data = bytearray(object_fixture())
    shoff = struct.unpack_from('<I', data, 32)[0]
    symtab = struct.unpack_from('<10I', data, shoff + 4 * 40)
    info = symtab[4] + 2 * 16 + 12
    data[info] = (13 << 4) | 2
    return bytes(data)


def thunk_fixture():
    """Two .text sections: first (AAAA) and its thunk @8@fir (TTTT)."""
    data = bytearray(object_fixture())
    first = data.index(b'\0first\0second\0')
    data[first:first + 14] = b'\0first\0@8@fir\0'
    return bytes(data).replace(b'BBBB', b'TTTT')


def section_names(data):
    shoff = struct.unpack_from('<I', data, 32)[0]
    count, names_index = struct.unpack_from('<HH', data, 48)
    headers = [struct.unpack_from('<10I', data, shoff + i * 40) for i in range(count)]
    strings = data[headers[names_index][4]:headers[names_index][4] + headers[names_index][5]]
    return [strings[h[0]:].split(b'\0')[0].decode() for h in headers[1:3]]


if __name__ == '__main__':
    unittest.main()
