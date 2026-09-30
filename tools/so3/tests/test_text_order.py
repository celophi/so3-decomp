"""Ordering .text sections by original address, on synthetic objects."""

import struct
import unittest

from tools.so3.build.compiler_probe import object_functions
from tools.so3.build.text_order import order_text_sections
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


if __name__ == '__main__':
    unittest.main()
