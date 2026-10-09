"""Check that only complete assembly scaffolds bypass the C compiler, and that assembled objects get tidied."""

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

from tools.so3.build.assembly import (ASSEMBLER, ASSEMBLER_ABI, ASSEMBLER_CPU, ASSEMBLER_FLAGS, LITTLE_ENDIAN,
                                      assembly_inputs, drop_empty_sections)
from tools.so3.build.elf import section_headers, section_names


class AssemblySourceTests(unittest.TestCase):
    def read(self, content):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'unit.c'
            source.write_text(content)
            return assembly_inputs(source)

    def test_comments_and_whitespace_preserve_requested_order(self):
        source = ('/* unfinished work */\n  #include "include_asm.h"\n'
                  '// int ignored(void) { return 1; }\n'
                  'INCLUDE_ASM("build/unit", second);\n'
                  '/* between entries */ INCLUDE_ASM ( "build/unit", first );\n')
        self.assertEqual(self.read(source), [Path('build/unit/second.s'), Path('build/unit/first.s')])

    def test_real_code_and_other_preprocessor_input_require_compilation(self):
        scaffold = '#include "include_asm.h"\nINCLUDE_ASM("build/unit", first);\n'
        for content in (
            'int real(void) { return 1; }\n',
            'extern int imported(void);\n',
            '#include "local.h"\n',
            '#define ENABLED 1\n',
            '#if ENABLED\nINCLUDE_ASM("build/unit", second);\n#endif\n',
            'INCLUDE_RODATA("build/unit", data);\n',
            '/* unfinished comment',
        ):
            with self.subTest(content=content):
                self.assertIsNone(self.read(scaffold + content))

    def test_empty_units_and_missing_headers_stay_on_compiler_path(self):
        for content in ('', '#include "include_asm.h"\n',
                        'INCLUDE_ASM("build/unit", first);\n'):
            with self.subTest(content=content):
                self.assertIsNone(self.read(content))

    def test_escaped_or_commented_paths_are_not_reinterpreted(self):
        source = '#include "include_asm.h"\nINCLUDE_ASM("build//unit", first);\n'
        self.assertEqual(self.read(source), [Path('build/unit/first.s')])
        self.assertIsNone(self.read(source.replace('build//unit', 'build\\unit')))


@unittest.skipUnless(shutil.which(ASSEMBLER), 'requires development binutils')
class EmptySectionTests(unittest.TestCase):
    def sections(self, path):
        data = path.read_bytes()
        headers = section_headers(data)
        return {name: header.size for name, header in zip(section_names(data, headers), headers)}

    def test_only_empty_default_sections_are_removed(self):
        with tempfile.TemporaryDirectory() as directory:
            source, output = Path(directory) / 'data.s', Path(directory) / 'data.o'
            # Like a data piece: something in .rodata, nothing in .text, .data or .bss.
            source.write_text('.section .rodata, "a"\n.word 1, 2\n')
            subprocess.run([ASSEMBLER, LITTLE_ENDIAN, f'-march={ASSEMBLER_CPU}', f'-mabi={ASSEMBLER_ABI}',
                            *ASSEMBLER_FLAGS, '-o', str(output), str(source)], check=True)
            self.assertIn('.data', self.sections(output))
            drop_empty_sections(output)
            sections = self.sections(output)
            self.assertNotIn('.text', sections)
            self.assertNotIn('.data', sections)
            self.assertNotIn('.bss', sections)
            self.assertNotIn('.pdr', sections)
            self.assertEqual(sections['.rodata'], 8)


if __name__ == '__main__':
    unittest.main()
