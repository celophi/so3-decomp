"""Full discs must survive image packaging without missing or altered bytes."""

import hashlib
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from ci_inputs import split_iso, join_iso


class DiscImageTests(unittest.TestCase):
    def test_round_trip_including_a_partial_last_part(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            data = bytes(range(256)) * 4096 + b'last sector'
            source, target = root / 'original.iso', root / 'restored.iso'
            source.write_bytes(data)
            profile = {'iso_size': len(data), 'iso_sha256': hashlib.sha256(data).hexdigest()}
            split_iso(source, root / 'layers', 'disc', profile, part_size=65536)
            parts = root / 'parts'
            parts.mkdir()
            for part in (root / 'layers').glob('*/iso/*'):
                shutil.copyfile(part, parts / part.name)
            join_iso(parts, target, 'disc', profile, part_size=65536)
            self.assertEqual(target.read_bytes(), data)
            self.assertEqual(source.read_bytes(), data)
            target.unlink()
            part = parts / 'disc.iso.part001'
            part.write_bytes(b'x' * part.stat().st_size)
            with self.assertRaisesRegex(ValueError, 'SHA-256 mismatch'):
                join_iso(parts, target, 'disc', profile, part_size=65536)
            target.unlink()
            part.unlink()
            with self.assertRaisesRegex(ValueError, 'missing or unexpected'):
                join_iso(parts, target, 'disc', profile, part_size=65536)

    def test_rejects_wrong_disc_and_truncated_image(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / 'original.iso'
            source.write_bytes(b'disc one')
            profile = {'iso_size': 8, 'iso_sha256': hashlib.sha256(b'disc two').hexdigest()}
            with self.assertRaisesRegex(ValueError, 'SHA-256 mismatch'):
                split_iso(source, root / 'parts', 'disc', profile, part_size=4)
            source.write_bytes(b'disc')
            with self.assertRaisesRegex(ValueError, 'size mismatch'):
                split_iso(source, root / 'parts', 'disc', profile, part_size=4)


if __name__ == '__main__':
    unittest.main()
