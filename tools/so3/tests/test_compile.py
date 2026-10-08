"""Per-unit compiler flag selection; no compiler required."""

import unittest

from tools.so3.build.compile import deferred, external_copies, symbol_map, unit_flags


CONFIG = {
    'working_flags': ['-O3,p', '-RTTI', 'off'],
    'unit_flags': [
        {'source': 'src/overlays/1067-00/text_001DD3C0.cpp', 'flags': ['-inline', 'auto,deferred']},
    ],
}


class UnitFlagsTests(unittest.TestCase):
    def test_configured_unit_appends_its_flags(self):
        self.assertEqual(unit_flags(CONFIG, 'src/overlays/1067-00/text_001DD3C0.cpp'),
                         ['-O3,p', '-RTTI', 'off', '-inline', 'auto,deferred'])

    def test_other_units_use_working_flags(self):
        self.assertEqual(unit_flags(CONFIG, 'src/overlays/1067-00/text_001DED80.cpp'), ['-O3,p', '-RTTI', 'off'])

    def test_missing_table_uses_working_flags(self):
        self.assertEqual(unit_flags({'working_flags': ['-O3,p']}, 'src/a.cpp'), ['-O3,p'])

    def test_duplicate_entries_are_rejected(self):
        config = {'working_flags': [], 'unit_flags': [{'source': 'src/a.cpp', 'flags': []}] * 2}
        with self.assertRaises(ValueError):
            unit_flags(config, 'src/a.cpp')

    def test_deferred_is_read_from_the_inline_option(self):
        self.assertTrue(deferred(['-O3,p', '-inline', 'auto,deferred']))
        self.assertTrue(deferred(['-inline', 'deferred']))
        self.assertFalse(deferred(['-inline', 'auto']))
        self.assertFalse(deferred(['-O3,p', 'deferred']))

    def test_symbol_map_follows_the_overlay_directory(self):
        self.assertIn('__dl__FPv', symbol_map('src/overlays/1067-00/text_001DD3C0.cpp'))

    def test_external_copies_skip_comments(self):
        copies = external_copies('src/overlays/1070-00/text_00294DA0.cpp')
        self.assertIn('__dt__16FieldClass17A810Fv', copies)
        self.assertFalse(any(name.startswith('//') or ' ' in name for name in copies))

    def test_modules_without_external_copies_have_none(self):
        self.assertEqual(external_copies('src/overlays/cconfig/text.cpp'), set())


if __name__ == '__main__':
    unittest.main()
