"""Check how a jump table anchor picks the compiler's table."""

from types import SimpleNamespace
import unittest

from tools.so3.build.rodata_ownership import referenced_table


def fixture():
    """A function at .text 0..0x100 that refers to the table in section 4 first, then section 2."""
    symbols = [SimpleNamespace(name='', section=0),
               SimpleNamespace(name='function', section=1, value=0, size=0x100),
               SimpleNamespace(name='@2', section=2, value=0),
               SimpleNamespace(name='@4', section=4, value=0)]
    relocations = {1: [(0x40, None, 3), (0x44, None, 3), (0x90, None, 2), (0x94, None, 2)]}
    return SimpleNamespace(symbols=symbols, relocations=relocations), symbols[1]


class ReferencedTableTests(unittest.TestCase):
    def test_one_table_is_required_without_an_index(self):
        obj, function = fixture()
        with self.assertRaises(ValueError):
            referenced_table(obj, function, {2, 4})
        self.assertEqual(referenced_table(obj, function, {2}).name, '@2')

    def test_index_follows_the_order_of_first_reference(self):
        obj, function = fixture()
        self.assertEqual(referenced_table(obj, function, {2, 4}, 0).name, '@4')
        self.assertEqual(referenced_table(obj, function, {2, 4}, 1).name, '@2')
        with self.assertRaises(ValueError):
            referenced_table(obj, function, {2, 4}, 2)


if __name__ == '__main__':
    unittest.main()
