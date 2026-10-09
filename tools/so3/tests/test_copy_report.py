"""Sorting the per-object copy records into the build's copy report."""

from pathlib import Path
import tempfile
import unittest

from tools.so3.build.copy_report import build_report, summary


def record(source, unit_range, moved=(), dropped=()):
    return {'source': source, 'range': list(unit_range), 'module_range': [0x0, 0x1000],
            'moved': [dict(zip(('function', 'address', 'after_in_compiler', 'after_in_game'), m)) for m in moved],
            'dropped': [{'function': f, 'kept_at': a} for f, a in dropped]}


class CopyReportTests(unittest.TestCase):
    def test_each_kind_of_copy_lands_in_its_list(self):
        with tempfile.TemporaryDirectory() as directory:
            later = Path(directory) / 'src/overlays/mod/later.cpp'
            later.parent.mkdir(parents=True)
            later.write_text('INCLUDE_ASM("asm/later", placeholder_copy);\n')
            records = [
                record(str(Path(directory) / 'src/overlays/mod/early.cpp'), (0x100, 0x200),
                       moved=[('moved_copy', 0x180, 'first', None)],
                       dropped=[('earlier_copy', 0x80), ('later_copy', 0x300),
                                ('placeholder_copy', 0x40), ('lib_copy', 0x4000), ('outside_copy', None)]),
                record(str(later), (0x200, 0x400)),
            ]
            report = build_report(records)
        self.assertEqual([e['function'] for e in report['moved']], ['moved_copy'])
        self.assertEqual([e['function'] for e in report['kept_later']], ['later_copy'])
        self.assertEqual([e['function'] for e in report['kept_by_placeholder']], ['placeholder_copy'])
        self.assertEqual([e['function'] for e in report['kept_in_another_module']], ['lib_copy'])
        self.assertEqual([e['function'] for e in report['kept_outside']], ['outside_copy'])
        self.assertEqual(report['dropped'], 5)
        self.assertIn('1 moved into place in 1 files; 5 dropped', summary(report))

    def test_no_records_means_nothing_to_do(self):
        report = build_report([])
        self.assertEqual(report['dropped'], 0)
        self.assertFalse(any(report[key] for key in ('moved', 'kept_later', 'kept_by_placeholder',
                                                     'kept_in_another_module', 'kept_outside')))


if __name__ == '__main__':
    unittest.main()
