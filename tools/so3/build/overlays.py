#!/usr/bin/env python3
"""Split, build, and verify the overlays on their own.

Overlays are the code the game loads as it needs it, on top of the main
executable. Each one is an MWo3 file (Metrowerks' overlay format) with a
Splat config in config/overlays/, named after the overlay, like 1067-00.yaml.

Before anything runs I check that the original overlay is the version I
support and that its config lines up with the file's header.

- `split` and `build` do the same as the full build, just for the overlays.
- `verify` compares each rebuilt overlay with the original byte for byte.
- `run-splat` runs Splat for one overlay. driver.py uses it for the split step.

--overlay picks a single overlay instead of all of them.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from tools.so3 import ROOT
from tools.so3.build.main import first_difference, sha256
from tools.so3.formats import OVERLAY_HEADER_SIZE, overlay_info, require

BUILD = Path('build/overlays')
CONFIGS = Path('config/overlays')
REBUILT = 'rebuilt.bin'
REPORT = 'verify.json'

# Overlay names are short folder-like names, like lib or 1067-00. Checking the
# name keeps --overlay from pointing outside config/overlays/.
OVERLAY_NAME = re.compile(r'[a-z0-9]+(?:-[0-9]{2})?')

# The overlays are extracted from disc 1. When disc 2 has been extracted too,
# verify also checks that its copy is identical.
DISC = 'us-disc1'
SECOND_DISC = 'us-disc2'

# What a match covers. Some of each overlay isn't rebuilt from source yet and
# is still copied from the original, so the report says which parts.
VERIFY_SCOPE = 'C/C++/assembly scaffold; MWo3 header, data, and unmapped VU contents retained.'


def load_config(path):
    """Load an overlay's Splat config and its original file, after checking they agree."""
    import yaml
    config = yaml.safe_load(path.read_text())
    original = Path(config['options']['target_path']).read_bytes()
    require(sha256(original) == config['sha256'],
            f'{path}: original overlay SHA-256 mismatch; extract the supported disc again')
    require(hashlib.sha1(original).hexdigest() == config['sha1'], f'{path}: SHA-1 mismatch')
    info = overlay_info(original)
    # Splat's last segment is just the file's end offset.
    require(config['segments'][-1] == [len(original)], f'{path}: incorrect file end')
    require(len(original) == OVERLAY_HEADER_SIZE + info['text_size'] + info['data_size'],
            f'{path}: unexpected overlay file layout')
    # Every code segment's address has to match where the header says the overlay loads.
    for segment in config['segments'][:-1]:
        if isinstance(segment, dict):
            require(segment['vram'] == info['load_address'] + segment['start'],
                    f'{path}: segment does not map to its runtime address')
    return config, original


def compared_discs(name, config, original):
    """The discs whose copy of this overlay is known to match."""
    discs = [DISC]
    second = Path(config['options']['target_path'].replace(f'/{DISC}/', f'/{SECOND_DISC}/'))
    if second.exists():
        require(second.read_bytes() == original, f'{name}: extracted Disc 2 overlay differs')
        discs.append(SECOND_DISC)
    return discs


def verify(name, config, original, output=None):
    """Fail unless the rebuilt overlay matches the original, then write its report.

    With an `output` file I only check that file and skip the report, since the
    report belongs to the normal build output.
    """
    folder = BUILD / name
    rebuilt = (output or folder / REBUILT).read_bytes()
    checksum = sha256(rebuilt)
    if rebuilt != original:
        raise ValueError(f'{name}: rebuild differs at file offset 0x{first_difference(original, rebuilt):X}; '
                         f'expected {len(original)} bytes, got {len(rebuilt)}; SHA-256 {checksum}')
    report = {'overlay': name, 'size': len(rebuilt), 'sha256': checksum,
              'matches_original': True, 'compared_discs': compared_discs(name, config, original),
              'scope': VERIFY_SCOPE}
    if output is None:
        (folder / REPORT).write_text(json.dumps(report, indent=2) + '\n')
    print(f'Overlay {name} matches: {len(rebuilt)} bytes; SHA-256 {checksum}', flush=True)


def check_arguments(args):
    require(args.overlay is None or OVERLAY_NAME.fullmatch(args.overlay), 'invalid overlay name')
    require(args.output is None or (args.command == 'verify' and args.overlay),
            '--output requires verify --overlay')
    require(args.command != 'run-splat' or args.overlay, 'run-splat requires --overlay')


def selected_configs(overlay):
    paths = [CONFIGS / f'{overlay}.yaml'] if overlay else sorted(CONFIGS.glob('*.yaml'))
    require(bool(paths), 'no overlay configurations found')
    return paths


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('command', choices=('split', 'build', 'verify', 'run-splat'))
    parser.add_argument('--overlay', help='overlay name, e.g. lib or 1067-00')
    parser.add_argument('--output', type=Path, help='alternate rebuilt file for verify --overlay')
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        check_arguments(args)
        paths = selected_configs(args.overlay)
        configs = [(path, *load_config(path)) for path in paths]
        if args.command == 'run-splat':
            subprocess.run([sys.executable, '-m', 'splat', 'split', str(paths[0])], check=True)
        elif args.command == 'verify':
            for path, config, original in configs:
                verify(path.stem, config, original, args.output)
        else:
            # Imported here because driver.py imports this module too.
            from tools.so3.build.driver import run
            run([(path, config) for path, config, _ in configs], args.command)
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
