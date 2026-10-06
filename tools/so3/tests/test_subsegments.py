"""Check ownership boundaries shared by the build and progress graph."""

import copy
from pathlib import Path
import unittest
import yaml

from tools.so3.build.driver import pieces
from tools.so3.build.sdk import code_units
from tools.so3.build.subsegments import configured_rodata_groups
from tools.so3.build.text_order import unit_range


class SubsegmentTests(unittest.TestCase):
    def fixture(self):
        return {'options': {'src_path': 'src', 'asm_path': 'asm', 'asset_path': 'bin'},
                'segments': [{'type': 'code', 'start': 0, 'vram': 0x1000,
                              'subsegments': [[0, 'cpp', 'unit'], [0x40, 'pad', 'tail'],
                                              [0x50, 'rodatabin', 'gap'],
                                              {'start': 0x60, 'type': '.rodata', 'name': 'unit',
                                               'linker_section': '.rodata.00001060', 'linker_section_order': '.rodata',
                                               'rodata_anchors': [{'function': 'function', 'offset': 0, 'size': 8}]},
                                              [0x68, 'rodatabin', 'remaining']]}, [0x80]]}

    def test_dictionary_units_preserve_text_boundary_and_retained_data(self):
        config = self.fixture()
        self.assertEqual(unit_range(config, 'src/unit.cpp'), (0x1000, 0x1040))
        self.assertEqual([(str(path), rule) for path, rule in pieces(config)],
                         [('src/unit.cpp', 'compile'), ('asm/data/gap.s', 'assemble'),
                          ('asm/data/remaining.s', 'assemble')])
        expected = list(code_units(config))
        config['segments'][0]['subsegments'][0] = {'start': 0, 'type': 'cpp', 'name': 'unit'}
        self.assertEqual(list(code_units(config)), expected)
        self.assertEqual(unit_range(config, 'src/unit.cpp'), (0x1000, 0x1040))
        self.assertEqual(configured_rodata_groups(config, 'src/unit.cpp'),
                         [{'section': '.rodata.00001060', 'address': 0x1060, 'size': 8,
                           'anchors': [{'function': 'function', 'offset': 0, 'size': 8}]}])

    def test_partial_island_ownership_is_rejected(self):
        config = self.fixture()
        config['segments'][0]['subsegments'].append([0x70, '.rodata', 'unit'])
        with self.assertRaisesRegex(ValueError, 'all owned rodata islands'):
            configured_rodata_groups(config, 'src/unit.cpp')

    def test_invalid_native_extents_and_ambiguous_selectors_are_rejected(self):
        for change in ('extent', 'selector', 'order', 'duplicate'):
            config = self.fixture()
            island = config['segments'][0]['subsegments'][3]
            if change == 'extent':
                island['start'] = 0x68
            elif change == 'selector':
                island['linker_section'] = '.rodata'
            elif change == 'order':
                island['linker_section_order'] = '.text'
            else:
                second = copy.deepcopy(island)
                second['start'] = 0x70
                config['segments'][0]['subsegments'].append(second)
            with self.subTest(change=change), self.assertRaises(ValueError):
                configured_rodata_groups(config, 'src/unit.cpp')

    def test_current_configurations_accept_dictionary_equivalents(self):
        paths = [Path('config/main.us.yaml'), *sorted(Path('config/overlays').glob('*.yaml'))]
        for path in paths:
            original = yaml.safe_load(path.read_text())
            converted = copy.deepcopy(original)
            for segment in converted['segments']:
                if isinstance(segment, dict) and segment.get('type') == 'code':
                    segment['subsegments'] = [dict(start=sub[0], type=sub[1], name=sub[2])
                                              if isinstance(sub, list) else sub for sub in segment['subsegments']]
            with self.subTest(path=path):
                self.assertEqual(list(code_units(converted)), list(code_units(original)))
                self.assertEqual(pieces(converted), pieces(original))
                for unit in code_units(original):
                    try:
                        expected = unit_range(original, unit['source'])
                    except ValueError:
                        with self.assertRaises(ValueError):
                            unit_range(converted, unit['source'])
                    else:
                        self.assertEqual(unit_range(converted, unit['source']), expected)


if __name__ == '__main__':
    unittest.main()
