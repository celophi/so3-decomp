"""Check that splat's linker scripts turn into MWLDPS2 command files that link the right bytes."""

import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

from tools.so3.build.compiler_probe import COMPILER_EXE, COMPILERS, CONFIG, LINKER_EXE, working_candidate
from tools.so3.build.driver import BINARY_ARCHITECTURE, BINARY_OBJECT_FORMAT, BINUTILS_PREFIX, MWLDPS2_FLAGS
from tools.so3.build.flat_image import image
from tools.so3.build.lcf import absolute_definitions, absolute_symbols, command_file, parse_linker_script, symbol_definitions
from tools.so3.formats import FormatError

# Each line splat writes inside a section, and what it should become.
LINE_TRANSLATIONS = [
    ('build/mod/src/code.c.o(.text);', 'code.c.o (.text)'),
    ('build/mod/src/code.c.o(.rodata.00001200);', 'code.c.o (.rodata.00001200)'),
    ('. = ALIGN(., 16);', '. = ALIGN(0x10);'),
    ('. += 0x10;', '. = . + 0x10;'),
]

# Each kind of section header, and the lines it should start with.
HEADER_TRANSLATIONS = [
    ('.text 0x1010 : AT(text_ROM_START) SUBALIGN(16)', ['. = 0x1010;', 'ALIGNALL(16);']),
    ('.text 0x1010 : AT(text_ROM_START)', ['. = 0x1010;']),
    ('.data : AT(data_ROM_START) SUBALIGN(4)', ['ALIGNALL(4);']),
    ('.text_bss (NOLOAD) : SUBALIGN(16)', ['ALIGNALL(16);']),
]

# splat's bookkeeping, which should leave nothing behind.
BOOKKEEPING_LINES = [
    'HIDDEN(__romPos = 0);',
    'text_ROM_START = __romPos;',
    'text_VRAM = ADDR(.text);',
    'text_DATA_START = .;',
    'text_DATA_SIZE = ABSOLUTE(text_DATA_END - text_DATA_START);',
    '__romPos += SIZEOF(.text);',
    '__romPos = ALIGN(__romPos, 16);',
    'FILL(0x00000000);',
]


def splat_script(*lines, header='.text : AT(text_ROM_START)', before=()):
    """A splat script with the given lines in one section.

    An empty section at 0x1000 comes first, because the command file has to
    start from a fixed address, so every converted body starts `. = 0x1000;`.
    """
    top = ''.join(f'    {line}\n' for line in before)
    body = ''.join(f'        {line}\n' for line in lines)
    return (f'SECTIONS\n{{\n{top}    .start 0x1000 : AT(0)\n    {{\n    }}\n'
            f'    {header}\n    {{\n{body}    }}\n'
            f'    /DISCARD/ :\n    {{\n        *(*);\n    }}\n}}\n')


def converted(script, symbols=()):
    sections, gp = parse_linker_script(script)
    return command_file(sections, gp, list(symbols))


def section_body(script):
    """The command file lines for the script's sections, after the entry point and without comments."""
    lines = [line.strip() for line in converted(script).splitlines()]
    body = lines[lines.index('__start = .;') + 1:lines.index('} > module')]
    return [line for line in body if not line.startswith('#')]


class TranslationTests(unittest.TestCase):
    def test_lines_inside_a_section(self):
        for splat_line, expected in LINE_TRANSLATIONS:
            with self.subTest(splat_line):
                self.assertEqual(section_body(splat_script(splat_line)), ['. = 0x1000;', expected])

    def test_section_headers(self):
        for header, expected in HEADER_TRANSLATIONS:
            with self.subTest(header):
                body = section_body(splat_script('code.c.o(.text);', header=header))
                self.assertEqual(body, ['. = 0x1000;', *expected, 'code.c.o (.text)'])

    def test_bookkeeping_is_left_out(self):
        self.assertEqual(section_body(splat_script(*BOOKKEEPING_LINES)), ['. = 0x1000;'])

    def test_whole_file_layout(self):
        script = splat_script('code.c.o(.text);', before=['_gp = 0x1BDFF0;'])
        lines = [line.strip() for line in converted(script, ['func_2000 = 0x2000;']).splitlines()]
        self.assertIn('module (RWX) : ORIGIN = 0x1000, LENGTH = 0', lines)
        self.assertIn('elsewhere (RWX) : ORIGIN = 0x10000000, LENGTH = 0', lines)
        self.assertEqual(lines[lines.index('.module : {') + 1], '__start = .;')
        # The gp value and the symbol addresses end the module's region.
        end = lines.index('} > module')
        self.assertEqual(lines[end - 2:end], ['_gp = 0x1BDFF0;', 'func_2000 = 0x2000;'])
        # Then every object's exception tables go elsewhere.
        self.assertEqual(lines[end + 1:], ['.elsewhere : {', 'code.c.o (.exceptix)', 'code.c.o (.exception)',
                                           '} > elsewhere', '}'])


class FileStartTests(unittest.TestCase):
    def test_sections_before_the_first_fixed_address_get_their_own_region(self):
        # Like the main program: its ELF header has no address, then the code is at 0x100000.
        script = ('SECTIONS\n{\n    .elf_header : AT(elf_header_ROM_START) SUBALIGN(4)\n    {\n'
                  '        build/main/bin/elf_header.bin.o(.data);\n    }\n'
                  '    .resident 0x100000 : AT(resident_ROM_START) SUBALIGN(4)\n    {\n'
                  '        build/main/src/code.c.o(.text);\n    }\n}\n')
        lines = [line.strip() for line in converted(script).splitlines()]
        self.assertIn('file_start (RWX) : ORIGIN = 0x0, LENGTH = 0', lines)
        self.assertIn('module (RWX) : ORIGIN = 0x100000, LENGTH = 0', lines)
        start = lines.index('.file_start : {')
        self.assertEqual(lines[start + 1:start + 5], ['# .elf_header', 'ALIGNALL(4);', 'elf_header.bin.o (.data)',
                                                      '} > file_start'])
        self.assertEqual(lines[start + 5:start + 9], ['.module : {', '__start = .;', '# .resident', '. = 0x100000;'])

    def test_overlays_keep_a_single_region(self):
        self.assertNotIn('file_start', converted(splat_script('code.c.o(.text);')))


class RefusalTests(unittest.TestCase):
    def test_unknown_lines_stop_the_conversion(self):
        for line in ('KEEP(*(.init));', 'build/mod/a.o(.text) build/mod/b.o(.text);', 'INCLUDE other.ld'):
            with self.subTest(line), self.assertRaisesRegex(ValueError, 'no MWLDPS2 equivalent'):
                converted(splat_script(line))

    def test_objects_with_the_same_file_name(self):
        script = splat_script('build/one/code.c.o(.text);', 'build/two/code.c.o(.data);')
        with self.assertRaisesRegex(FormatError, 'share a file name'):
            converted(script)

    def test_symbol_scripts_must_be_plain_addresses(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'symbols.ld'
            path.write_text('func_2000 = 0x2000;\n\nD_3000 = 0x3000;\n')
            self.assertEqual(symbol_definitions([path]), ['func_2000 = 0x2000;', 'D_3000 = 0x3000;'])
            path.write_text('func_2000 = func_1000 + 4;\n')
            with self.assertRaisesRegex(FormatError, 'not a plain symbol address'):
                symbol_definitions([path])


class AbsoluteSymbolTests(unittest.TestCase):
    def test_only_symbols_marked_absolute_are_taken(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'symbols.txt'
            path.write_text('__dl__FPv = 0x00100D60; // type:func absolute:True\n'
                            '__vt__16FieldClass16AB90 = 0x0016AB90; // absolute:True\n'
                            'local = 0x00294DA0; // type:func\n'
                            'other = 0x00295000; // absolute:False\n'
                            '// ignored = 0x00100000; // absolute:True\n')
            self.assertEqual(absolute_symbols([path]),
                             {'__dl__FPv': 0x100D60, '__vt__16FieldClass16AB90': 0x16AB90})
            self.assertEqual(absolute_definitions([path]),
                             ['__dl__FPv = 0x100D60;', '__vt__16FieldClass16AB90 = 0x16AB90;'])

    def test_maps_that_disagree_are_refused(self):
        with tempfile.TemporaryDirectory() as directory:
            first, second = Path(directory) / 'first.txt', Path(directory) / 'second.txt'
            first.write_text('resident = 0x00100000; // absolute:True\n')
            second.write_text('resident = 0x00100004; // absolute:True\n')
            with self.assertRaisesRegex(FormatError, 'conflicting'):
                absolute_symbols([first, second])


def compiler_folder():
    return COMPILERS / working_candidate(json.loads(CONFIG.read_text()))['id']


# A tiny module, laid out like the real overlays: a header, then the code and
# its read-only data, then a data block. It's written out in full, the way
# splat writes it.
TINY_MODULE = """SECTIONS
{
    .text 0x1000 : AT(0) SUBALIGN(4)
    {
        header.bin.o(.data);
        code.c.o(.text);
        . = ALIGN(., 16);
        code.c.o(.rodata);
        . = ALIGN(., 16);
        data.bin.o(.data);
    }
    /DISCARD/ :
    {
        *(*);
    }
}
"""
HEADER = b'MWo3' + bytes(12)
DATA = bytes(range(16))
CODE = ('extern int D_3000;\n'
        'static const int table[4] = {1, 2, 3, 4};\n'
        'int entry(int index) { return table[index] + D_3000; }\n')
# D_3000 lives outside the module, like the main program's data an overlay uses.
SYMBOL_MAP = 'D_3000 = 0x00003000; // absolute:True\n'
OBJECTS = ('header.bin.o', 'code.c.o', 'data.bin.o')
TABLE = b''.join(value.to_bytes(4, 'little') for value in (1, 2, 3, 4))


@unittest.skipUnless(shutil.which(f'{BINUTILS_PREFIX}objcopy') and shutil.which('wibo')
                     and (compiler_folder() / LINKER_EXE).exists(),
                     'requires development binutils, wibo and the downloaded compiler')
class LinkTests(unittest.TestCase):
    """Link a tiny module with MWLDPS2 and check where everything landed."""

    def run_tool(self, *command):
        result = subprocess.run(command, capture_output=True, text=True, cwd=self.work)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def build_objects(self):
        # The same way driver.py builds them: blobs wrapped by objcopy, and the
        # code compiled with MWCC.
        (self.work / 'header.bin').write_bytes(HEADER)
        (self.work / 'data.bin').write_bytes(DATA)
        for name in ('header', 'data'):
            self.run_tool(f'{BINUTILS_PREFIX}objcopy', '-I', 'binary', '-O', BINARY_OBJECT_FORMAT,
                          '-B', BINARY_ARCHITECTURE, f'{name}.bin', f'{name}.bin.o')
        (self.work / 'code.c').write_text(CODE)
        self.run_tool('wibo', str(compiler_folder() / COMPILER_EXE), '-c', '-O3,p', '-o', 'code.c.o', 'code.c')

    def link(self):
        (self.work / 'symbols.txt').write_text(SYMBOL_MAP)
        symbols = absolute_definitions([self.work / 'symbols.txt'])
        (self.work / 'layout.lcf').write_text(converted(TINY_MODULE, symbols))
        self.run_tool('wibo', str(compiler_folder() / LINKER_EXE), *MWLDPS2_FLAGS.split(),
                      '-o', 'mw.elf', 'layout.lcf', *OBJECTS)
        # The module's regions, like the build writes them.
        return image((self.work / 'mw.elf').read_bytes())

    def test_everything_lands_where_the_script_says(self):
        with tempfile.TemporaryDirectory() as directory:
            self.work = Path(directory)
            self.build_objects()
            result = self.link()
            # The header comes first, and the data block ends the module on a
            # 16-byte boundary.
            self.assertTrue(result.startswith(HEADER))
            self.assertTrue(result.endswith(DATA))
            self.assertEqual((len(result) - len(DATA)) % 16, 0)
            # The read-only table follows the code, on a 16-byte boundary.
            table = result.index(TABLE)
            self.assertEqual(table % 16, 0)
            self.assertGreater(table, len(HEADER))
            # The code found D_3000 at the address the symbol map gives.
            code = result[len(HEADER):table]
            words = [int.from_bytes(code[i:i + 4], 'little') for i in range(0, len(code), 4)]
            self.assertIn(0x3000, [word & 0xFFFF for word in words])


if __name__ == '__main__':
    unittest.main()
