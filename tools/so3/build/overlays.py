#!/usr/bin/env python3
"""Split, reassemble, and verify the US MWo3 overlays independently."""

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from tools.so3 import ROOT
from tools.so3.formats import overlay_info, require

BUILD = Path('build/overlays')
CONFIGS = Path('config/overlays')


def load_config(path):
    import yaml
    config = yaml.safe_load(path.read_text())
    original = Path(config['options']['target_path']).read_bytes()
    require(hashlib.sha256(original).hexdigest() == config['sha256'],
            f'{path}: original overlay SHA-256 mismatch; extract the supported disc again')
    require(hashlib.sha1(original).hexdigest() == config['sha1'], f'{path}: SHA-1 mismatch')
    info = overlay_info(original)
    require(config['segments'][-1] == [len(original)], f'{path}: incorrect file end')
    require(len(original) == 0x40 + info['text_size'] + info['data_size'],
            f'{path}: unexpected overlay file layout')
    for segment in config['segments'][:-1]:
        if isinstance(segment, dict):
            require(segment['vram'] == info['load_address'] + segment['start'],
                    f'{path}: segment does not map to its runtime address')
    return config, original


def verify(ident, config, original, output=None):
    out = BUILD / ident
    path = output or out / 'rebuilt.bin'
    rebuilt = path.read_bytes()
    checksum = hashlib.sha256(rebuilt).hexdigest()
    if rebuilt != original:
        first = next((i for i, (a, b) in enumerate(zip(original, rebuilt)) if a != b),
                     min(len(original), len(rebuilt)))
        raise ValueError(f'{ident}: rebuild differs at file offset 0x{first:X}; '
                         f'expected {len(original)} bytes, got {len(rebuilt)}; SHA-256 {checksum}')
    discs = ['us-disc1']
    second = Path(config['options']['target_path'].replace('/us-disc1/', '/us-disc2/'))
    if second.exists():
        require(second.read_bytes() == original, f'{ident}: extracted Disc 2 overlay differs')
        discs.append('us-disc2')
    report = {'overlay': ident, 'size': len(rebuilt), 'sha256': checksum,
              'matches_original': True, 'compared_discs': discs,
              'scope': 'C/C++/assembly scaffold; MWo3 header, data, and unmapped VU contents retained.'}
    if output is None:
        (out / 'verify.json').write_text(json.dumps(report, indent=2) + '\n')
    print(f'Overlay {ident} matches: {len(rebuilt)} bytes; SHA-256 {checksum}', flush=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('split', 'build', 'verify', 'run-splat'))
    parser.add_argument('--overlay', help='resource-block ID, e.g. 0002-01')
    parser.add_argument('--output', type=Path, help='alternate rebuilt file for verify --overlay')
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        require(args.overlay is None or re.fullmatch(r'\d{4}-\d{2}', args.overlay), 'invalid overlay ID')
        require(args.output is None or (args.command == 'verify' and args.overlay),
                '--output requires verify --overlay')
        require(args.command != 'run-splat' or args.overlay, 'run-splat requires --overlay')
        paths = [CONFIGS / f'{args.overlay}.yaml'] if args.overlay else sorted(CONFIGS.glob('*.yaml'))
        require(bool(paths), 'no overlay configurations found')
        configs = [(path, *load_config(path)) for path in paths]
        if args.command == 'run-splat':
            subprocess.run([sys.executable, '-m', 'splat', 'split', str(paths[0])], check=True)
        elif args.command == 'verify':
            for path, config, original in configs:
                verify(path.stem, config, original, args.output)
        else:
            from tools.so3.build.driver import run
            run([(path, config) for path, config, _ in configs], args.command)
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
