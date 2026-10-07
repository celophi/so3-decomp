"""Check that only complete assembly scaffolds bypass the C compiler."""

from pathlib import Path
import tempfile
import unittest

from tools.so3.build.assembly import assembly_inputs


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


if __name__ == '__main__':
    unittest.main()
