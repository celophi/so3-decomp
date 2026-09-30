"""Keep draft generation tied to original bytes and preserve matching experiments."""

import copy
from pathlib import Path
import sys
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import decompile
from test_sdk import directory


class DecompileTests(unittest.TestCase):
    def fixture(self):
        raw = bytes.fromhex('0800e0030000000000000000')
        assembly = Path('asm/unit.s')
        assembly.parent.mkdir()
        assembly.write_text('nonmatching func_1000, 0x8\nglabel func_1000\n'
                            '/* 000000 00001000 0800E003 */ jr $ra\n'
                            '/* 000004 00001004 00000000 */ nop\nendlabel func_1000\n'
                            '/* 000008 00001008 00000000 */ nop\n')
        config = {'options': {'src_path': 'src', 'asm_path': 'asm'},
                  'segments': [{'type': 'code', 'start': 0, 'vram': 0x1000,
                                'subsegments': [[0, 'cpp', 'unit']]}, [12]]}
        return config, raw

    def test_exact_extent_excludes_padding_and_requires_original_bytes(self):
        with directory():
            config, raw = self.fixture()
            identity, text = decompile.function_input(config, raw, 'func_1000')
            self.assertEqual((identity['address'], identity['size']), (0x1000, 8))
            self.assertEqual(identity['source'], 'src/unit.cpp')
            self.assertNotIn('00001008', text)
            self.assertIn('00001004', text)  # Keep the branch delay slot.
            with self.assertRaisesRegex(ValueError, 'stale bytes'):
                decompile.function_input(config, bytes(len(raw)), 'func_1000')

    def test_missing_or_ambiguous_function_is_rejected(self):
        with directory():
            config, raw = self.fixture()
            with self.assertRaisesRegex(ValueError, 'found 0'):
                decompile.function_input(config, raw, 'func_2000')
            duplicate = copy.deepcopy(config['segments'][0])
            duplicate.update(start=12, vram=0x100C, subsegments=[[12, 'cpp', 'other']])
            text = Path('asm/unit.s').read_text()
            text = text.replace('000000 00001000', '00000C 0000100C')
            text = text.replace('000004 00001004', '000010 00001010')
            text = text.replace('000008 00001008', '000014 00001014')
            Path('asm/other.s').write_text(text)
            config['segments'].insert(1, duplicate)
            config['segments'][-1] = [24]
            raw += raw
            with self.assertRaisesRegex(ValueError, 'found 2'):
                decompile.function_input(config, raw, 'func_1000')

    def test_reruns_preserve_existing_drafts(self):
        with directory() as root, patch.object(decompile, 'ROOT', root):
            first = decompile.reserve_run('func_1000', 'boot')
            (first / 'draft.c').write_text('my edited candidate')
            second = decompile.reserve_run('func_1000', 'boot')
            self.assertNotEqual(first, second)
            self.assertEqual((first / 'draft.c').read_text(), 'my edited candidate')
            self.assertEqual(list(second.iterdir()), [])

    def test_cli_identifiers_cannot_escape_workspace(self):
        for module, name in [('../boot', 'func_1000'), ('boot', '../../draft')]:
            with self.subTest(module=module, name=name), self.assertRaises(ValueError):
                decompile.decompile(module, name)
