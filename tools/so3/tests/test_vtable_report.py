"""Comparing compiled vtables with the game's."""

import unittest

from tools.so3.build.elf import R_MIPS_32
from tools.so3.build.vtable_report import check_vtable


class FakeImage:
    """The game's bytes at one address."""

    def __init__(self, address, data):
        self.address, self.data = address, data

    def read(self, address, size):
        if address == self.address and size <= len(self.data):
            return self.data[:size]
        return None


def words(*values):
    return b''.join(value.to_bytes(4, 'little') for value in values)


# Two functions the linked module knows, and one that's still assembly.
SYMBOLS = ({'first__3FooFv': 0x1000, 'second__3FooFv': 0x1010},
           {0x1000: 'first__3FooFv', 0x1010: 'second__3FooFv', 0x1020: 'func_00001020'})


def vtable(*slots, size=16):
    return {'name': '__vt__3Foo', 'address': 0x500, 'bytes': bytes(size).hex(),
            'slots': [[offset, R_MIPS_32, target] for offset, target in slots]}


def check(compiled, game):
    images = {'main': FakeImage(0x500, game), 'mod': FakeImage(0, b''), 'lib': FakeImage(0, b'')}
    return check_vtable(compiled, 'mod', SYMBOLS, images)


class VtableCheckTests(unittest.TestCase):
    def test_same_functions_match(self):
        compiled = vtable((8, 'first__3FooFv'), (12, 'second__3FooFv'))
        self.assertEqual(check(compiled, words(0, 0, 0x1000, 0x1010)), ('match', []))

    def test_swapped_functions_are_wrong(self):
        compiled = vtable((8, 'first__3FooFv'), (12, 'second__3FooFv'))
        status, slots = check(compiled, words(0, 0, 0x1010, 0x1000))
        self.assertEqual(status, 'wrong')
        self.assertEqual([(s['offset'], s['ours'], s['game']) for s in slots],
                         [(8, 'first__3FooFv', 'second__3FooFv'), (12, 'second__3FooFv', 'first__3FooFv')])

    def test_slots_that_cant_be_filled_in_yet_are_incomplete(self):
        compiled = vtable((8, 'unknown__3FooFv'), (12, 'first__3FooFv'), size=20)
        status, slots = check(compiled, words(0, 0, 0x1010, 0x1020, 0x1000))
        self.assertEqual(status, 'incomplete')
        self.assertEqual([(s['offset'], s['why']) for s in slots],
                         [(8, 'no address'), (12, 'not decompiled'), (16, 'declared only')])

    def test_a_wrong_slot_outweighs_incomplete_ones(self):
        compiled = vtable((8, 'unknown__3FooFv'), (12, 'second__3FooFv'))
        self.assertEqual(check(compiled, words(0, 0, 0x1000, 0x1000))[0], 'wrong')

    def test_address_outside_every_image(self):
        compiled = dict(vtable((8, 'first__3FooFv')), address=0x900)
        self.assertEqual(check(compiled, words(0, 0, 0x1000, 0)), ('outside', []))


if __name__ == '__main__':
    unittest.main()
