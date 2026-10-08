#!/usr/bin/env python3
"""Split the main executable with Splat, and check the rebuilt one matches.

The main executable (SLUS_204.88 on disc 1) is the game's resident code: it
stays loaded the whole time, and the overlays load on top of it. driver.py runs
this for the main module:

- `split` checks the original is the version I support, then runs Splat on
  config/main.us.yaml.
- `verify` compares the linked executable with the original byte for byte and
  writes a short report.

Other scripts import original_main() from here too, so they all read the same
checked copy.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

from tools.so3 import ROOT

ORIGINAL = Path('disc/us-disc1/iso/SLUS_204.88')
REBUILT = Path('build/main/SLUS_204.88')
MAIN_CONFIG = Path('config/main.us.yaml')

# Every supported disc's hashes are in this manifest. The main executable is on disc 1.
VERSIONS = Path('config/manifests/versions.json')
DISC = 'us-disc1'

# What a match covers. Some of the executable isn't rebuilt from source yet and
# is still copied from the original, so the report says which parts.
VERIFY_SCOPE = 'C/assembly scaffold; resident data/VU region and ELF metadata retained.'


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def expected_hash():
    versions = json.loads((ROOT / VERSIONS).read_text())['versions']
    return versions[DISC]['boot_sha256']


def original_main():
    """Read the original main executable, after checking it's the version I support."""
    data = (ROOT / ORIGINAL).read_bytes()
    if sha256(data) != expected_hash():
        raise ValueError('Original main executable hash mismatch; extract the supported Disc 1 again.')
    return data


def first_difference(original, rebuilt):
    """The first offset where two files differ. If one is a prefix of the other, it's where the shorter one ends."""
    return next((offset for offset, (a, b) in enumerate(zip(original, rebuilt)) if a != b),
                min(len(original), len(rebuilt)))


def split():
    subprocess.run([sys.executable, '-m', 'splat', 'split', str(MAIN_CONFIG)], check=True)


def verify(original, output, report_path):
    """Fail unless the rebuilt executable matches the original, then write the report."""
    rebuilt = output.read_bytes()
    digest = sha256(rebuilt)
    if rebuilt != original:
        raise ValueError(f'Main executable rebuild differs at file offset 0x{first_difference(original, rebuilt):X}; '
                         f'expected {len(original)} bytes, got {len(rebuilt)}; SHA-256 {digest}')
    if report_path:
        report = {'size': len(rebuilt), 'sha256': digest, 'matches_original': True, 'scope': VERIFY_SCOPE}
        report_path.write_text(json.dumps(report, indent=2) + '\n')
    print(f'Main executable matches: {len(rebuilt)} bytes; SHA-256 {digest}')


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('command', choices=('split', 'verify'))
    parser.add_argument('--output', type=Path, default=REBUILT)
    parser.add_argument('--report', type=Path)
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        original = original_main()
        if args.command == 'split':
            split()
        else:
            verify(original, args.output, args.report)
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
