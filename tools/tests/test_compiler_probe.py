"""Synthetic Metrowerks-style ELF objects; no game or compiler inputs required."""

from pathlib import Path
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from compiler_probe import object_functions
from so3.formats import FormatError


def object_fixture(relocated=False, oversize=False):
    names = b'\0.text\0.strtab\0.symtab\0.shstrtab\0.rel.text\0'
    strings = b'\0first\0second\0'
    symbols = bytes(16)
    symbols += struct.pack('<IIIBBH', 1, 0, 8 if oversize else 4, 0x12, 0, 1)
    symbols += struct.pack('<IIIBBH', 7, 0, 4, 0x12, 0, 2)
    parts = [('.text', 1, b'AAAA', 0, 0, 0), ('.text', 1, b'BBBB', 0, 0, 0),
             ('.strtab', 3, strings, 0, 0, 0), ('.symtab', 2, symbols, 3, 1, 16),
             ('.shstrtab', 3, names, 0, 0, 0)]
    if relocated:
        parts.append(('.rel.text', 9, struct.pack('<II', 0, 0x102), 4, 1, 8))
    data = bytearray(52)
    headers = [bytes(40)]
    for name, kind, payload, link, info, entry_size in parts:
        offset = len(data)
        data.extend(payload)
        headers.append(struct.pack('<10I', names.index(name.encode() + b'\0'), kind,
                                   0, 0, offset, len(payload), link, info, 1, entry_size))
    table = len(data)
    data.extend(b''.join(headers))
    struct.pack_into('<16sHHIIIIIHHHHHH', data, 0, b'\x7fELF\x01\x01\x01' + bytes(9),
                     1, 8, 1, 0, 0, table, 0, 52, 32, 0, 40, len(headers), 5)
    return bytes(data)


class CompilerObjectTests(unittest.TestCase):
    def test_duplicate_text_sections_use_symbol_section_indices(self):
        _, functions = object_functions(object_fixture())
        self.assertEqual(functions, {'first': b'AAAA', 'second': b'BBBB'})

    def test_unresolved_code_relocations_are_rejected(self):
        with self.assertRaisesRegex(FormatError, 'Unresolved relocation'):
            object_functions(object_fixture(relocated=True))

    def test_function_cannot_read_into_another_section(self):
        with self.assertRaisesRegex(FormatError, 'Function exceeds section'):
            object_functions(object_fixture(oversize=True))


if __name__ == '__main__':
    unittest.main()
