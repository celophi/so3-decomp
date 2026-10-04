"""Ordering .text sections by original address, on synthetic objects."""

import struct
import shutil
import subprocess
import tempfile
from pathlib import Path
import unittest

from tools.so3.build.compiler_probe import object_functions
from tools.so3.build.text_order import merge_rodata_sections, order_text_sections, unit_range
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


class RodataMergeTests(unittest.TestCase):
    def test_tables_are_laid_out_as_the_linker_would(self):
        data = merge_rodata_sections(rodata_fixture())
        header = section(data, 2)
        self.assertEqual((section_name(data, 2), header[5], header[8]), ('.rodata', 0x38, 16))
        self.assertEqual(payload(data, 2), b'A' * 0x18 + bytes(8) + b'B' * 0x18)

    def test_symbols_move_to_the_merged_section(self):
        data = merge_rodata_sections(rodata_fixture())
        self.assertEqual(rodata_symbol(data, 2)[1], 0x20)
        self.assertEqual(rodata_symbol(data, 2)[5], 2)
        self.assertEqual(rodata_symbol(data, 1), rodata_symbol(rodata_fixture(), 1))
        self.assertEqual(rodata_symbol(data, 4), rodata_symbol(rodata_fixture(), 4))

    def test_table_relocations_follow_their_table(self):
        data = merge_rodata_sections(rodata_fixture())
        header = section(data, 3)
        self.assertEqual(header[7], 2)
        entries = [struct.unpack_from('<II', data, header[4] + i)[0] for i in range(0, header[5], 8)]
        self.assertEqual(entries, [4, 0x28])

    def test_emptied_sections_are_discarded(self):
        data = merge_rodata_sections(rodata_fixture())
        for index in (4, 5):
            self.assertEqual((section_name(data, index), section(data, index)[5]), ('.discarded', 0))

    def test_single_rodata_object_is_unchanged(self):
        original = object_fixture()
        self.assertEqual(merge_rodata_sections(original), original)

    def test_relocation_to_a_merged_section_symbol_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'merged .rodata section symbol'):
            merge_rodata_sections(rodata_fixture(section_symbol=True))

    @unittest.skipUnless(shutil.which('mips-ps2-decompals-ld'), 'requires the project linker')
    def test_linked_bytes_are_unchanged(self):
        def link(data, root, label):
            (root / f'{label}.o').write_bytes(data)
            subprocess.run(['mips-ps2-decompals-ld', '-EL', '-T', str(root / 'link.ld'), str(root / f'{label}.o'),
                            '-o', str(root / f'{label}.elf')], check=True, capture_output=True)
            for name in ('text', 'rodata'):
                subprocess.run(['mips-ps2-decompals-objcopy', '-O', 'binary', f'--only-section=.{name}',
                                str(root / f'{label}.elf'), str(root / f'{label}.{name}')], check=True)
            return [(root / f'{label}.{name}').read_bytes() for name in ('text', 'rodata')]
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'link.ld').write_text('SECTIONS { .text 0x1000 : { *(.text) } .rodata 0x2000 : { *(.rodata) } '
                                          '/DISCARD/ : { *(*) } }')
            before = link(rodata_fixture(), root, 'before')
            after = link(merge_rodata_sections(rodata_fixture()), root, 'after')
            self.assertEqual(after, before)
            self.assertEqual(before[0], struct.pack('<I', 0x2020))


def rodata_fixture(section_symbol=False):
    """A function and two 0x18-byte, 16-aligned tables, each relocated to the function.

    Sections: 1 .text (reads table B), 2/3 table A and its relocations, 4/5 table B
    and its relocations, then .symtab, .strtab, .shstrtab, .rel.text.
    """
    names = b'\0.text\0.rodata\0.rel.rodata\0.symtab\0.strtab\0.shstrtab\0.rel.text\0'
    strings = b'\0tableA\0tableB\0func\0'
    symbols = bytes(16)
    symbols += struct.pack('<IIIBBH', 1, 0, 0x18, 0x01, 0, 2)
    symbols += struct.pack('<IIIBBH', 8, 0, 0x18, 0x01, 0, 4)
    symbols += struct.pack('<IIIBBH', 15, 0, 4, 0x12, 0, 1)
    symbols += struct.pack('<IIIBBH', 0, 0, 0, 0x03, 0, 4)
    target = (4 << 8 | 2) if section_symbol else (2 << 8 | 2)
    parts = [('.text', 1, 6, bytes(4), 0, 0, 4, 0),
             ('.rodata', 1, 2, b'A' * 0x18, 0, 0, 16, 0),
             ('.rel.rodata', 9, 0, struct.pack('<II', 4, 3 << 8 | 2), 6, 2, 4, 8),
             ('.rodata', 1, 2, b'B' * 0x18, 0, 0, 16, 0),
             ('.rel.rodata', 9, 0, struct.pack('<II', 8, 3 << 8 | 2), 6, 4, 4, 8),
             ('.symtab', 2, 0, symbols, 7, 4, 4, 16),
             ('.strtab', 3, 0, strings, 0, 0, 1, 0),
             ('.shstrtab', 3, 0, names, 0, 0, 1, 0),
             ('.rel.text', 9, 0, struct.pack('<II', 0, target), 6, 1, 4, 8)]
    data = bytearray(52)
    headers = [bytes(40)]
    for name, kind, flags, body, link, info, align, entry in parts:
        data.extend(bytes(-len(data) % 16))
        offset = len(data)
        data.extend(body)
        headers.append(struct.pack('<10I', names.index(name.encode() + b'\0'), kind, flags, 0, offset, len(body),
                                   link, info, align, entry))
    table = len(data)
    data.extend(b''.join(headers))
    struct.pack_into('<16sHHIIIIIHHHHHH', data, 0, b'\x7fELF\x01\x01\x01' + bytes(9),
                     1, 8, 1, 0, 0, table, 0, 52, 32, 0, 40, len(headers), 8)
    return bytes(data)


def section(data, index):
    shoff = struct.unpack_from('<I', data, 32)[0]
    return struct.unpack_from('<10I', data, shoff + index * 40)


def section_name(data, index):
    names = section(data, struct.unpack_from('<H', data, 50)[0])
    strings = data[names[4]:names[4] + names[5]]
    return strings[section(data, index)[0]:].split(b'\0')[0].decode()


def rodata_symbol(data, index):
    symtab = section(data, 6)
    return struct.unpack_from('<IIIBBH', data, symtab[4] + index * 16)


def payload(data, index):
    header = section(data, index)
    return data[header[4]:header[4] + header[5]]


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
