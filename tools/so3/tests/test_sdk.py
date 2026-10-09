"""Protect the boundary between preserved SDK bytes and measured game code."""

from contextlib import contextmanager
import copy
import hashlib
import json
import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from tools.so3 import ROOT
from tools.so3.build import driver as build
from tools.so3.analysis.identify_sdk import functions, named_patterns
from tools.so3.build.sdk import validate_sdk_units


@contextmanager
def directory():
    old = Path.cwd()
    with tempfile.TemporaryDirectory() as temporary:
        os.chdir(temporary)
        try:
            yield Path(temporary)
        finally:
            os.chdir(old)


class SdkTests(unittest.TestCase):
    def fixture(self):
        raw = bytes.fromhex('010003240c0000000800e00300000000')
        Path('original.bin').write_bytes(raw)
        source = Path('src/sdk/main/calls.c')
        source.parent.mkdir(parents=True)
        source.write_text('#include "include_asm.h"\nINCLUDE_ASM("asm/nonmatchings/sdk/main/calls", func_1000);\n')
        unit = {'module': 'main', 'source': str(source), 'binary': 'original.bin',
                'binary_sha256': hashlib.sha256(raw).hexdigest(), 'start': 0, 'end': 16,
                'functions': [{'name': 'func_1000', 'offset': 0, 'address': 0x1000,
                               'size': 16, 'sha256': hashlib.sha256(raw).hexdigest()}]}
        config = {'options': {'src_path': 'src', 'asm_path': 'asm', 'target_path': 'original.bin'},
                  'segments': [{'type': 'code', 'start': 0, 'vram': 0x1000,
                                'subsegments': [[0, 'c', 'sdk/main/calls']]}, [16]]}
        return [(Path('config/main.us.yaml'), config)], {'units': [unit]}

    def test_exclusion_requires_exact_reviewed_coverage_and_unchanged_bytes(self):
        with directory():
            configs, manifest = self.fixture()
            self.assertEqual(validate_sdk_units(configs, manifest), {'src/sdk/main/calls.c'})
            for change in ('missing_function', 'short_function', 'wrong_address', 'wrong_hash'):
                bad = copy.deepcopy(manifest)
                f = bad['units'][0]['functions'][0]
                if change == 'missing_function':
                    bad['units'][0]['functions'] = []
                elif change == 'short_function':
                    f['size'] = 12
                elif change == 'wrong_address':
                    f['address'] += 4
                else:
                    f['sha256'] = '0' * 64
                with self.subTest(change=change), self.assertRaises(ValueError):
                    validate_sdk_units(configs, bad)
            Path('original.bin').write_bytes(bytes(16))
            with self.assertRaisesRegex(ValueError, 'original hash'):
                validate_sdk_units(configs, manifest)

    def test_folder_alone_cannot_exclude_code_and_source_cannot_gain_code(self):
        with directory():
            configs, manifest = self.fixture()
            with self.assertRaisesRegex(ValueError, 'unreviewed'):
                validate_sdk_units(configs, {'units': []})
            source = Path('src/sdk/main/calls.c')
            source.write_text(source.read_text() + 'int game_function(void) { return 3; }\n')
            with self.assertRaisesRegex(ValueError, 'exactly the reviewed'):
                validate_sdk_units(configs, manifest)

    def test_overlay_sdk_directory_is_recognised_only_under_its_module(self):
        from tools.so3.build.sdk import sdk_path
        self.assertTrue(sdk_path('src/sdk/main/calls.c'))
        self.assertTrue(sdk_path('src/overlays/lib/sdk/libmpeg_003E6900.c'))
        self.assertFalse(sdk_path('src/overlays/lib/text_003E68C0.c'))
        self.assertFalse(sdk_path('src/overlays/sdk/calls.c'))

    def test_other_modules_can_build_independently(self):
        with directory():
            configs, manifest = self.fixture()
            config = copy.deepcopy(configs[0][1])
            config['segments'][0]['subsegments'][0][2] = 'game'
            self.assertEqual(validate_sdk_units([(Path('boot.yaml'), config)], manifest), set())

    def test_patterns_keep_aliases_and_reject_wildcards(self):
        with directory():
            path = Path('patterns.xml')
            path.write_text('<patternlist><pattern><data>0x0102 0x0304</data><funcstart label="first"/></pattern>'
                            '<pattern><data>0x01020304</data><funcstart label="second"/></pattern></patternlist>')
            self.assertEqual(named_patterns(path), {bytes([1, 2, 3, 4]): ['first', 'second']})
            path.write_text('<patternlist><pattern><data>0x01..</data><funcstart label="unsafe"/></pattern></patternlist>')
            with self.assertRaisesRegex(ValueError, 'non-exact'):
                named_patterns(path)

    def test_scan_rejects_stale_bytes_and_incomplete_function_extent(self):
        with directory():
            path = Path('unit.s')
            source = ('nonmatching func_1000, 0x8\nglabel func_1000\n'
                      '/* 000000 00001000 0800E003 */ jr $ra\n'
                      '/* 000004 00001004 00000000 */ nop\nendlabel func_1000\n')
            raw = bytes.fromhex('0800e00300000000')
            path.write_text(source)
            self.assertEqual(list(functions(path, raw, 0, 8, 0x1000))[0][1], raw)
            with self.assertRaises(ValueError):
                list(functions(path, bytes(8), 0, 8, 0x1000))
            path.write_text(source.replace('0x8', '0x4'))
            with self.assertRaises(ValueError):
                list(functions(path, raw, 0, 8, 0x1000))

    def test_build_keeps_sdk_objects_but_omits_comparison_objects(self):
        with directory():
            configs, manifest = self.fixture()
            options = configs[0][1]['options']
            options.update(asset_path='bin', build_path='build/main', ld_script_path='main.ld',
                           undefined_funcs_auto_path='funcs.ld', undefined_syms_auto_path='syms.ld',
                           generated_asm_macros_directory='include')
            configs[0][1]['segments'][0]['subsegments'].append([16, 'c', 'main/game'])
            configs[0][1]['segments'][-1] = [24]
            raw = Path('original.bin').read_bytes() + bytes(8)
            Path('original.bin').write_bytes(raw)
            manifest['units'][0]['binary_sha256'] = hashlib.sha256(raw).hexdigest()
            Path('config/manifests').mkdir(parents=True)
            Path('config/manifests/sdk-functions.json').write_text(json.dumps(manifest))
            Path('src/main').mkdir()
            Path('src/main/game.c').write_text('int game(void) { return 0; }\n')
            with patch.object(build, 'CONFIG', ROOT / 'config/manifests/compilers.json'):
                build.configure(configs)
            ninja = Path('build/build.ninja').read_text()
            report = json.loads(Path('objdiff.json').read_text())
            self.assertIn('build build/main/src/sdk/main/calls.c.o: compile src/sdk/main/calls.c', ninja)
            link = next(line for line in ninja.splitlines() if line.startswith('build build/main/linked.elf:'))
            self.assertIn(' build/main/src/sdk/main/calls.c.o', link)
            self.assertNotIn('build/progress/src/sdk', ninja)
            self.assertIn('asm/main/game.s.o: assemble asm/main/game.s', ninja)
            self.assertEqual([u['metadata']['source_path'] for u in report['units']], ['src/main/game.c'])


if __name__ == '__main__':
    unittest.main()
