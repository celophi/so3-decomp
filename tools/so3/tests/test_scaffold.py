"""Exercise local relocations and actual C/C++ through the pinned assembly processor."""

import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

from tools.so3 import ROOT
from tools.so3.build.driver import asm_inputs

CONFIG = json.loads((ROOT / 'config/manifests/compilers.json').read_text())
COMPILER = ROOT / 'build/compilers' / CONFIG['working_candidate'] / 'mwccps2.exe'
AVAILABLE = COMPILER.exists() and Path('/opt/mwccgap').exists() and shutil.which('mips-ps2-decompals-as')


class SourceDependencyTests(unittest.TestCase):
    def test_missing_source_then_two_assembly_dependencies(self):
        with tempfile.TemporaryDirectory() as directory:
            for extension in ('.c', '.cpp'):
                source = Path(directory) / ('unit' + extension)
                self.assertEqual(asm_inputs(source), [])
                source.write_text('INCLUDE_ASM("build/unit", first);\n'
                                  'INCLUDE_RODATA("build/unit", table);\n')
                self.assertEqual(asm_inputs(source), [Path('build/unit/first.s'), Path('build/unit/table.s')])

    def test_unsupported_language_is_rejected_before_compiling(self):
        result = subprocess.run([sys.executable, '-m', 'tools.so3.build.compile', 'unit.cc', 'unused.o',
                                 '--macros', 'unused.inc'], cwd=ROOT, capture_output=True, text=True)
        self.assertEqual(result.returncode, 2)
        self.assertIn('source must use .c (C) or .cpp (C++)', result.stderr)


@unittest.skipUnless(AVAILABLE, 'requires the development image and make compilers')
class ScaffoldIntegrationTests(unittest.TestCase):
    def run_tool(self, *args):
        result = subprocess.run(args, cwd=ROOT, capture_output=True, text=True,
                                env={**os.environ, 'MWCIncludes': ''})
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return result

    def test_mixed_c_and_repeated_local_section_relocations(self):
        self.check_mixed_unit(cpp=False)

    def test_cpp_classes_and_c_assembly_linkage(self):
        self.check_mixed_unit(cpp=True)

    def test_assembly_only_unit_keeps_calls_and_local_relocations(self):
        with tempfile.TemporaryDirectory() as directory:
            work = Path(directory)
            macros = work / 'macro.inc'
            macros.write_text('.macro glabel name\n.globl \\name\n.type \\name, @function\n\\name:\n.endm\n')
            first = ('.set noat\n.set noreorder\nglabel first\n'
                     'lui $t0, %hi(.Lfirst)\naddiu $t0, $t0, %lo(.Lfirst)\n'
                     'jal second\nnop\n.Lfirst:\njr $ra\nnop\n')
            second = '.set noreorder\nglabel second\njr $ra\naddiu $v0, $zero, 9\n'
            (work / 'first.s').write_text(first)
            (work / 'second.s').write_text(second)
            source = work / 'unit.c'
            source.write_text('#include "include_asm.h"\n'
                              f'INCLUDE_ASM("{work}", first);\n'
                              f'INCLUDE_ASM("{work}", second);\n')
            fast = work / 'fast.o'
            self.run_tool(sys.executable, '-m', 'tools.so3.build.compile', str(source), str(fast),
                          '--macros', str(macros))
            # A declaration keeps the same bodies on the original compiler path.
            source.write_text(source.read_text() + 'extern int first(void);\n')
            compiled = work / 'compiled.o'
            self.run_tool(sys.executable, '-m', 'tools.so3.build.compile', str(source), str(compiled),
                          '--macros', str(macros))

            def link(obj):
                layout = work / 'layout.ld'
                layout.write_text(f'SECTIONS {{ .text 0x100000 : SUBALIGN(4) {{ {obj}(.text) }} '
                                  '/DISCARD/ : { *(*) } }')
                elf, binary = work / 'linked.elf', work / 'linked.bin'
                self.run_tool('mips-ps2-decompals-ld', '-EL', '-T', str(layout), '-o', str(elf))
                self.run_tool('mips-ps2-decompals-objcopy', '-O', 'binary', str(elf), str(binary))
                return binary.read_bytes()

            self.assertEqual(link(fast), link(compiled))
            source.write_text(source.read_text().replace('extern int first(void);\n', ''))
            expected = link(fast)
            (work / 'second.s').write_text(second.replace('zero, 9', 'zero, 10'))
            self.run_tool(sys.executable, '-m', 'tools.so3.build.compile', str(source), str(fast),
                          '--macros', str(macros))
            self.assertNotEqual(link(fast), expected)
            previous = fast.read_bytes()
            (work / 'second.s').unlink()
            failure = subprocess.run([sys.executable, '-m', 'tools.so3.build.compile',
                                      str(source), str(fast), '--macros', str(macros)],
                                     cwd=ROOT, capture_output=True)
            self.assertNotEqual(failure.returncode, 0)
            self.assertEqual(fast.read_bytes(), previous)

    def test_progress_report_counts_only_compiled_functions(self):
        with tempfile.TemporaryDirectory() as directory:
            work = Path(directory)
            source, target, base = work / 'unit.c', work / 'target.o', work / 'base.o'
            real = 'int real(void) { return 9; }\n'
            pending = 'int pending(void) { return 10; }\n'
            source.write_text(real + pending)
            self.run_tool('wibo', str(COMPILER), '-c', *CONFIG['working_flags'],
                          '-lang', 'c', '-o', str(target), str(source))
            (work / 'objdiff.json').write_text(json.dumps({
                'build_target': False, 'build_base': False,
                'units': [{'name': 'unit', 'target_path': 'target.o', 'base_path': 'base.o'}],
            }))
            for matched in range(3):
                source.write_text('#include "include_asm.h"\n' +
                                  (real if matched >= 1 else 'INCLUDE_ASM("unused", real);\n') +
                                  (pending if matched >= 2 else 'INCLUDE_ASM("unused", pending);\n'))
                self.run_tool(sys.executable, '-m', 'tools.so3.build.compile', str(source), str(base),
                              '--macros', str(work / 'unused.inc'), '--skip-asm')
                self.run_tool('objdiff-cli', 'report', 'generate', '-p', str(work),
                              '-o', str(work / 'report.json'))
                report = json.loads((work / 'report.json').read_text())['measures']
                self.assertEqual(report['total_functions'], 2)
                self.assertEqual(report.get('matched_functions', 0), matched)
                self.assertGreater(int(report['total_code']), 0)
                self.assertEqual(report.get('matched_code_percent', 0), matched * 50)

    def check_mixed_unit(self, cpp):
        with tempfile.TemporaryDirectory() as directory:
            work = Path(directory)
            macros = work / 'macro.inc'
            macros.write_text('.macro glabel name\n.globl \\name\n.type \\name, @function\n\\name:\n.endm\n')
            bodies = []
            for name, target in [('first', 'second'), ('second', 'real')]:
                body = f'''.set noat
.set noreorder
glabel {name}
    lui $t0, %hi(.L{name})
    addiu $t0, $t0, %lo(.L{name})
    jal {target}
    nop
    j .L{name}
    nop
.L{name}:
    jr $ra
    nop
'''
                (work / f'{name}.s').write_text(body)
                bodies.append(body)
            (work / 'local.h').write_text('#define RESULT 9\n')
            extension = '.cpp' if cpp else '.c'
            source = work / ('mixed' + extension)
            prefix = ('#include "include_asm.h"\n#include "local.h"\n'
                      f'INCLUDE_ASM("{work}", first);\n'
                      f'INCLUDE_ASM("{work}", second);\n')
            body = 'extern int first(void);\nint real(void) { return first() + RESULT; }\n'
            support_objects = []
            if cpp:
                # A shared header must give C/C++ callers and assembly the same names.
                (work / 'interface.h').write_text('''#ifdef __cplusplus
extern "C" {
#endif
int first(void);
int real(void);
int c_increment(int value);
#ifdef __cplusplus
}
#endif
''')
                (work / 'value.hpp').write_text('''class Value {
public:
    Value(int value);
    int get() const;
    int get(int extra) const;
private:
    int value_;
};
''')
                body = '''#include "interface.h"
#include "value.hpp"
Value::Value(int value) : value_(value) {}
int Value::get() const { return value_; }
int Value::get(int extra) const { return value_ + extra; }
int real(void) {
    Value value(first());
    return c_increment(value.get() + value.get(RESULT));
}
'''
                support = work / 'support.c'
                support.write_text('#include "interface.h"\nint c_increment(int value) { return value + 1; }\n')
                support_objects = [work / 'support.o']
                self.run_tool(sys.executable, '-m', 'tools.so3.build.compile', str(support), str(support_objects[0]),
                              '--macros', str(macros))
            source.write_text(prefix + body)
            reference_source = work / ('real' + extension)
            reference_source.write_text('#include "local.h"\n' + body)
            mixed, real = work / 'mixed.o', work / 'real.o'
            self.run_tool(sys.executable, '-m', 'tools.so3.build.compile', str(source), str(mixed), '--macros', str(macros))
            # Compile the reference directly, without the assembly processor.
            self.run_tool('wibo', str(COMPILER), '-c', *CONFIG['working_flags'],
                          '-lang', 'c++' if cpp else 'c', f'-I{work}', '-o', str(real), str(reference_source))
            if cpp:
                symbols = self.run_tool('mips-ps2-decompals-nm', '--defined-only', str(mixed)).stdout
                self.assertEqual(sum('Value' in line for line in symbols.splitlines()), 3)
                for symbol in ('first', 'second', 'real'):
                    self.assertRegex(symbols, rf'(?m) T {symbol}$')
                self.assertNotIn('mwccgap_', symbols)
            assembly = work / 'reference.s'
            assembly.write_text(macros.read_text() + ''.join(bodies))
            asm_object = work / 'reference.o'
            self.run_tool('mips-ps2-decompals-as', '-EL', '-march=r5900', '-mabi=eabi',
                          '-no-pad-sections', '-o', str(asm_object), str(assembly))

            def link(objects, name):
                script = work / f'{name}.ld'
                entries = ' '.join(f'{obj}(.text)' for obj in objects + support_objects)
                script.write_text(f'SECTIONS {{ .text 0x100000 : SUBALIGN(4) {{ {entries} }} /DISCARD/ : {{ *(*) }} }}')
                elf, binary = work / f'{name}.elf', work / f'{name}.bin'
                self.run_tool('mips-ps2-decompals-ld', '-EL', '-T', str(script), '-o', str(elf))
                self.run_tool('mips-ps2-decompals-objcopy', '-O', 'binary', str(elf), str(binary))
                return binary.read_bytes()

            expected = link([asm_object, real], 'reference')
            self.assertEqual(link([mixed], 'mixed'), expected)
            # The report object contains real C/C++ only, including its relocations.
            # Compare against direct MWCC output so dropping all code cannot pass.
            progress = work / 'progress.o'
            self.run_tool(sys.executable, '-m', 'tools.so3.build.compile', str(source), str(progress),
                          '--macros', str(macros), '--skip-asm')
            progress_symbols = self.run_tool('mips-ps2-decompals-nm', '--defined-only', str(progress)).stdout
            self.assertNotRegex(progress_symbols, r'(?m) T (first|second)$')
            self.assertRegex(progress_symbols, r'(?m) T real$')
            if cpp:
                self.assertEqual(sum('Value' in line for line in progress_symbols.splitlines()), 3)
            self.assertEqual(link([asm_object, progress], 'progress'), expected)
            # Real source changes must affect the final image.
            source.write_text(prefix + body.replace('RESULT', '10'))
            self.run_tool(sys.executable, '-m', 'tools.so3.build.compile', str(source), str(mixed), '--macros', str(macros))
            self.assertNotEqual(link([mixed], 'changed'), expected)
            old_object = mixed.read_bytes()
            source.write_text(prefix + 'this is invalid source;\n')
            failure = subprocess.run([sys.executable, '-m', 'tools.so3.build.compile', str(source), str(mixed),
                                      '--macros', str(macros)], cwd=ROOT, capture_output=True)
            self.assertNotEqual(failure.returncode, 0)
            self.assertEqual(mixed.read_bytes(), old_object)


if __name__ == '__main__':
    unittest.main()
