#!/usr/bin/env python3
"""Verify and split the shared US boot ELF for the C/assembly scaffold."""

import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

from tools.so3 import ROOT

ORIGINAL = Path('disc/us-disc1/iso/SLUS_204.88')
REBUILT = Path('build/boot/SLUS_204.88')


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def expected_hash():
    profiles = json.loads((ROOT / 'config/versions.json').read_text())['versions']
    return profiles['us-disc1']['boot_sha256']


def original_boot():
    data = (ROOT / ORIGINAL).read_bytes()
    if sha256(data) != expected_hash():
        raise ValueError('Original boot ELF hash mismatch; extract the supported Disc 1 again.')
    return data


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('split', 'verify'))
    parser.add_argument('--output', type=Path, default=REBUILT)
    parser.add_argument('--report', type=Path)
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        original = original_boot()
        if args.command == 'split':
            subprocess.run([sys.executable, '-m', 'splat', 'split', 'config/boot.us.yaml'], check=True)
            return 0
        rebuilt = args.output.read_bytes()
        digest = sha256(rebuilt)
        if rebuilt != original:
            first = next((i for i, (a, b) in enumerate(zip(original, rebuilt)) if a != b),
                         min(len(original), len(rebuilt)))
            raise ValueError(f'Boot rebuild differs at file offset 0x{first:X}; '
                             f'expected {len(original)} bytes, got {len(rebuilt)}; SHA-256 {digest}')
        report = {'size': len(rebuilt), 'sha256': digest, 'matches_original': True,
                  'scope': 'C/assembly scaffold; resident data/VU region and ELF metadata retained.'}
        if args.report:
            args.report.write_text(json.dumps(report, indent=2) + '\n')
        print(f'Boot ELF matches: {len(rebuilt)} bytes; SHA-256 {digest}')
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
