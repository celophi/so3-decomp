"""Keep resident symbol mappings available after Splat suppresses their definitions."""

from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest

from tools.so3.build.linker_symbols import absolute_symbols


class AbsoluteSymbolTests(unittest.TestCase):
    def test_only_explicit_absolute_addresses_are_exported(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'symbols.txt'
            path.write_text('__dl__FPv = 0x00100D60; // type:func absolute:True\n'
                            '__vt__16FieldClass16AB90 = 0x0016AB90; // absolute:True\n'
                            'local = 0x00294DA0; // type:func\n'
                            'other = 0x00295000; // absolute:False\n'
                            '// ignored = 0x00100000; // absolute:True\n')
            self.assertEqual(absolute_symbols([path]),
                             {'__dl__FPv': 0x100D60, '__vt__16FieldClass16AB90': 0x16AB90})

    def test_conflicting_maps_are_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            first, second = Path(directory) / 'first.txt', Path(directory) / 'second.txt'
            first.write_text('resident = 0x00100000; // absolute:True\n')
            second.write_text('resident = 0x00100004; // absolute:True\n')
            with self.assertRaisesRegex(ValueError, 'conflicting'):
                absolute_symbols([first, second])

    @unittest.skipUnless(shutil.which('mips-ps2-decompals-as'), 'requires development binutils')
    def test_resident_vtable_and_delete_relocations_link_to_original_addresses(self):
        with tempfile.TemporaryDirectory() as directory:
            work = Path(directory)
            source, obj = work / 'probe.s', work / 'probe.o'
            script, elf, binary = work / 'probe.ld', work / 'probe.elf', work / 'probe.bin'
            source.write_text('.set noreorder\n.text\n.globl probe\nprobe:\n'
                              'lui $v0, %hi(__vt__16FieldClass16AB90)\n'
                              'addiu $v0, $v0, %lo(__vt__16FieldClass16AB90)\n'
                              'jal __dl__FPv\nnop\n')
            maps = work / 'symbols.txt'
            maps.write_text('__vt__16FieldClass16AB90 = 0x0016AB90; // absolute:True\n'
                            '__dl__FPv = 0x00100D60; // type:func absolute:True\n')
            symbols = absolute_symbols([maps])
            script.write_text('SECTIONS { .text 0x00294DA0 : { *(.text) } '
                              '/DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) } }\n'
                              + ''.join(f'{name} = 0x{address:X};\n' for name, address in symbols.items()))
            subprocess.run(['mips-ps2-decompals-as', '-EL', '-march=r5900', '-mabi=eabi',
                            '-no-pad-sections', '-o', str(obj), str(source)], check=True, capture_output=True)
            subprocess.run(['mips-ps2-decompals-ld', '-EL', '-T', str(script),
                            '-o', str(elf), str(obj)], check=True, capture_output=True)
            subprocess.run(['mips-ps2-decompals-objcopy', '-O', 'binary', str(elf), str(binary)],
                           check=True, capture_output=True)
            self.assertEqual(struct.unpack('<4I', binary.read_bytes()[:16]),
                             (0x3C020017, 0x2442AB90, 0x0C040358, 0))


if __name__ == '__main__':
    unittest.main()
