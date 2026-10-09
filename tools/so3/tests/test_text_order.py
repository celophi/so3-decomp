"""Ordering .text sections by original address, on synthetic objects."""

import struct
import shutil
import subprocess
import tempfile
from pathlib import Path
import unittest

from tools.so3.build.compiler_probe import object_functions
from tools.so3.build.text_order import (CopyReport, DroppedCopy, MovedCopy, normalize_symbol_aliases,
                                        order_text_sections, symbol_aliases, unit_range)
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
    def test_only_explicit_same_address_aliases_are_selected(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'symbols.txt'
            path.write_text('first = 0x100; // type:func allow_duplicated:True\n'
                            'second = 0x100; // type:func allow_duplicated:true\n'
                            'unmarked = 0x200; // type:func\n'
                            'marked = 0x200; // type:func allow_duplicated:true\n')
            self.assertEqual(symbol_aliases(path), {'first': 'second'})

    def test_defined_functions_are_not_renamed_as_aliases(self):
        original = object_fixture(relocated=True)
        self.assertEqual(normalize_symbol_aliases(original, {'first': 'second'}), original)

    def test_import_alias_preserves_payloads_and_relocation_indices(self):
        original = bytearray(object_fixture(relocated=True))
        shoff = struct.unpack_from('<I', original, 32)[0]
        table = struct.unpack_from('<10I', original, shoff + 4 * 40)
        struct.pack_into('<H', original, table[4] + 16 + 14, 0)
        result = normalize_symbol_aliases(bytes(original), {'first': 'heap_release'})
        self.assertEqual(text_payloads(result), text_payloads(original))
        relocation = struct.unpack_from('<10I', original, shoff + 6 * 40)
        self.assertEqual(result[relocation[4]:relocation[4] + relocation[5]],
                         original[relocation[4]:relocation[4] + relocation[5]])
        strings = struct.unpack_from('<10I', result, shoff + 3 * 40)
        label = struct.unpack_from('<I', result, table[4] + 16)[0]
        self.assertEqual(result[strings[4] + label:].split(b'\0', 1)[0], b'heap_release')
        second = struct.unpack_from('<IIIBBH', result, table[4] + 32)
        self.assertEqual(second[5], 2)
        self.assertEqual(result[strings[4] + second[0]:].split(b'\0', 1)[0], b'second')

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

    def test_report_lists_a_kept_copy_that_had_to_move(self):
        report = CopyReport()
        order_text_sections(multidef_fixture(), {'first': 0x180, 'second': 0x100}, {},
                            keep=(0x100, 0x200), reorder=False, report=report)
        self.assertEqual(report.moved, [MovedCopy('second', 0x100, 'first', None)])
        self.assertEqual(report.dropped, [])

    def test_report_lists_dropped_copies_once(self):
        report = CopyReport()
        order_text_sections(two_copy_fixture(), {'first': 0x180}, {}, keep=(0x100, 0x200),
                            reorder=False, external={'second'}, report=report)
        self.assertEqual(report.dropped, [DroppedCopy('second', None)])
        report = CopyReport()
        order_text_sections(multidef_fixture(), {'second': 0x300}, {}, keep=(0x100, 0x200),
                            reorder=False, report=report)
        self.assertEqual(report.dropped, [DroppedCopy('second', 0x300)])
        self.assertEqual(report.moved, [])

    def test_unmapped_inline_copy_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'multiply-defined function second is not in the symbol map'):
            order_text_sections(multidef_fixture(), {}, {}, keep=(0x100, 0x200), reorder=False)

    def test_external_inline_copy_is_discarded_without_an_address(self):
        data = order_text_sections(multidef_fixture(), {}, {}, keep=(0x100, 0x200), reorder=False,
                                   external={'second'})
        self.assertEqual(section_names(data), ['.text', '.discarded'])
        self.assertEqual(symbol_record(data, 2)[1:], (0, 0, 0x12, 0, 0))

    def test_external_inline_copy_is_left_out_of_the_order(self):
        data = order_text_sections(multidef_fixture(), {'first': 0x180}, {}, keep=(0x100, 0x200),
                                   external={'second'})
        self.assertEqual(section_names(data), ['.text', '.discarded'])
        self.assertEqual(text_payloads(data), [b'AAAA'])

    def test_external_copy_beside_a_kept_copy_is_still_discarded(self):
        data = order_text_sections(two_copy_fixture(), {'first': 0x180}, {}, keep=(0x100, 0x200),
                                   reorder=False, external={'second'})
        self.assertEqual(section_names(data), ['.text', '.discarded'])
        self.assertEqual(text_payloads(data), [b'AAAA'])

    def test_external_copy_with_an_address_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'external copies also have a symbol map address: second'):
            order_text_sections(multidef_fixture(), {'second': 0x180}, {}, keep=(0x100, 0x200),
                                reorder=False, external={'second'})

    def test_discarded_inline_copy_becomes_an_external_reference(self):
        original = multidef_fixture()
        data = order_text_sections(original, {'second': 0x300}, keep=(0x100, 0x200), reorder=False)
        self.assertEqual(symbol_record(data, 2)[1:], (0, 0, 0x12, 0, 0))
        self.assertEqual(symbol_record(data, 1), symbol_record(original, 1))

    def test_discarded_thunk_becomes_an_external_reference(self):
        data = order_text_sections(thunk_fixture(), {}, {'@8@fir': 0x300},
                                   keep=(0x100, 0x200), reorder=False)
        self.assertEqual(symbol_record(data, 2)[1:], (0, 0, 0x12, 0, 0))

    def test_resident_vtable_definition_becomes_an_external_reference(self):
        data = order_text_sections(vtable_fixture(), {'second': 0x80}, keep=(0x100, 0x200), reorder=False)
        self.assertEqual(section_names(data), ['.text', '.vtables'])
        self.assertEqual(symbol_record(data, 2)[1:], (0, 0, 0x11, 0, 0))

    def test_unmapped_vtable_is_unchanged(self):
        original = vtable_fixture()
        self.assertEqual(order_text_sections(original, {}, keep=(0x100, 0x200), reorder=False), original)

    def test_vtable_without_overlay_scope_is_unchanged(self):
        original = vtable_fixture()
        self.assertEqual(order_text_sections(original, {}, reorder=False), original)

    @unittest.skipUnless(shutil.which('mips-ps2-decompals-ld'), 'requires the project linker')
    def test_cross_unit_copy_reference_links_to_retained_definition(self):
        owner = order_text_sections(multidef_fixture(), {'first': 0x100, 'second': 0x180},
                                    keep=(0x100, 0x200), reorder=False)
        consumer = bytearray(object_fixture(relocated=True))
        consumer[:] = consumer.replace(b'first', b'third')
        shoff = struct.unpack_from('<I', consumer, 32)[0]
        symtab = struct.unpack_from('<10I', consumer, shoff + 4 * 40)
        consumer[symtab[4] + 2 * 16 + 12] = 0xD2
        reloc = struct.unpack_from('<10I', consumer, shoff + 6 * 40)
        struct.pack_into('<II', consumer, reloc[4], 0, 0x202)
        text = struct.unpack_from('<10I', consumer, shoff + 40)
        consumer[text[4]:text[4] + 4] = bytes(4)
        consumer = order_text_sections(bytes(consumer), {'second': 0x180},
                                       keep=(0x200, 0x300), reorder=False)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'owner.o').write_bytes(owner)
            (root / 'consumer.o').write_bytes(consumer)
            (root / 'link.ld').write_text('SECTIONS { .text 0x1000 : { *(.text) } /DISCARD/ : { *(*) } }')
            subprocess.run(['mips-ps2-decompals-ld', '-EL', '-T', str(root / 'link.ld'),
                            str(root / 'owner.o'), str(root / 'consumer.o'), '-o', str(root / 'linked.elf')],
                           check=True, capture_output=True)
            payloads = text_payloads((root / 'linked.elf').read_bytes())
            self.assertEqual(payloads, [b'AAAABBBB' + struct.pack('<I', 0x1004)])


def symbol_record(data, index):
    shoff = struct.unpack_from('<I', data, 32)[0]
    symtab = struct.unpack_from('<10I', data, shoff + 4 * 40)
    return struct.unpack_from('<IIIBBH', data, symtab[4] + index * 16)


def vtable_fixture():
    data = bytearray(multidef_fixture())
    shoff = struct.unpack_from('<I', data, 32)[0]
    names = list(struct.unpack_from('<10I', data, shoff + 5 * 40))
    strings = data[names[4]:names[4] + names[5]]
    position = len(strings)
    strings += b'.vtables\0'
    names[4], names[5] = len(data), len(strings)
    data.extend(strings)
    struct.pack_into('<10I', data, shoff + 5 * 40, *names)
    struct.pack_into('<I', data, shoff + 2 * 40, position)
    symtab = struct.unpack_from('<10I', data, shoff + 4 * 40)
    data[symtab[4] + 2 * 16 + 12] = 0xD1
    return bytes(data)


def multidef_fixture():
    """first (AAAA) and a multiply-defined copy named second (BBBB)."""
    data = bytearray(object_fixture())
    shoff = struct.unpack_from('<I', data, 32)[0]
    symtab = struct.unpack_from('<10I', data, shoff + 4 * 40)
    info = symtab[4] + 2 * 16 + 12
    data[info] = (13 << 4) | 2
    return bytes(data)


def two_copy_fixture():
    """Multiply-defined copies first (AAAA) and second (BBBB)."""
    data = bytearray(multidef_fixture())
    shoff = struct.unpack_from('<I', data, 32)[0]
    symtab = struct.unpack_from('<10I', data, shoff + 4 * 40)
    data[symtab[4] + 1 * 16 + 12] = (13 << 4) | 2
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
