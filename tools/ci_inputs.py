#!/usr/bin/env python3
"""Stage both discs for the private CI image, or restore complete ISOs from it."""

import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile

from boot import ORIGINAL, ROOT, original_boot
from overlays import CONFIGS, load_config
from so3.formats import require

# Both supported DVDs fit in 35 parts each. Each Docker COPY combines one
# part per disc, keeping layers near 256 MiB to fit GHCR's upload timeout.
PART_SIZE = 128 * 1024 * 1024
MAX_PARTS = 35


def split_iso(source, output, ident, profile, part_size=PART_SIZE):
    require(source.stat().st_size == profile['iso_size'], f'{source}: ISO size mismatch')
    require((profile['iso_size'] + part_size - 1) // part_size <= MAX_PARTS,
            'ISO exceeds the part count in dockerfiles/ci-inputs.dockerfile')
    checksum, size, index = hashlib.sha256(), 0, 0
    with source.open('rb') as original:
        while chunk := original.read(part_size):
            require(index < MAX_PARTS, f'{source}: ISO grew while copying')
            target = output / f'{index:03}' / 'iso' / f'{ident}.iso.part{index:03}'
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(chunk)
            checksum.update(chunk)
            size += len(chunk)
            index += 1
    require(size == profile['iso_size'], f'{source}: ISO size changed while copying')
    require(checksum.hexdigest() == profile['iso_sha256'], f'{source}: ISO SHA-256 mismatch')


def join_iso(source, target, ident, profile, part_size=PART_SIZE):
    count = (profile['iso_size'] + part_size - 1) // part_size
    parts = [source / f'{ident}.iso.part{i:03}' for i in range(count)]
    require(sorted(source.glob(f'{ident}.iso.part*')) == parts,
            f'{ident}: missing or unexpected ISO parts')
    checksum = hashlib.sha256()
    remaining = profile['iso_size']
    with target.open('xb') as restored:
        for part in parts:
            size = min(part_size, remaining)
            require(part.stat().st_size == size, f'{part}: incorrect part size')
            with part.open('rb') as stream:
                while chunk := stream.read(8 * 1024 * 1024):
                    restored.write(chunk)
                    checksum.update(chunk)
            remaining -= size
    require(target.stat().st_size == profile['iso_size'], f'{ident}: restored ISO size mismatch')
    require(checksum.hexdigest() == profile['iso_sha256'], f'{ident}: restored ISO SHA-256 mismatch')


def stage(output, disc1, disc2):
    require(not output.exists(), f'{output} already exists; choose a new --output directory')
    inputs = {ORIGINAL: original_boot()}
    for path in sorted(CONFIGS.glob('*.yaml')):
        config, data = load_config(path)
        target = Path(config['options']['target_path'])
        require(target.parts[:2] == ('disc', 'us-disc1') and '..' not in target.parts,
                f'{path}: expected a path under disc/us-disc1')
        require(target not in inputs, f'duplicate CI input: {target}')
        inputs[target] = data
    require(len(inputs) > 1, 'no overlay configurations found')
    profiles = json.loads((ROOT / 'config/versions.json').read_text())['versions']
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = Path(tempfile.mkdtemp(prefix='.ci-inputs-', dir=output.parent))
    try:
        for path, data in inputs.items():
            target = temporary / path
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(data)
        checksums = []
        for ident, source in [('us-disc1', disc1), ('us-disc2', disc2)]:
            print(f'Splitting and verifying {ident}...', flush=True)
            split_iso(source, temporary / 'parts', ident, profiles[ident])
            checksums.append(f'{profiles[ident]["iso_sha256"]}  {ident}.iso')
        (temporary / 'SHA256SUMS').write_text('\n'.join(checksums) + '\n')
        temporary.rename(output)
    finally:
        if temporary.exists():
            shutil.rmtree(temporary)
    print(f'Staged both complete discs and {len(inputs)} extracted files in {output}')


def restore(source, output):
    require(not output.exists(), f'{output} already exists; choose a new --output directory')
    profiles = json.loads((ROOT / 'config/versions.json').read_text())['versions']
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = Path(tempfile.mkdtemp(prefix='.restored-isos-', dir=output.parent))
    try:
        for ident in ('us-disc1', 'us-disc2'):
            join_iso(source, temporary / f'{ident}.iso', ident, profiles[ident])
            print(f'Restored and verified {ident}', flush=True)
        temporary.rename(output)
    finally:
        if temporary.exists():
            shutil.rmtree(temporary)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest='command', required=True)
    staging = commands.add_parser('stage', help='prepare a new image build context')
    staging.add_argument('--output', type=Path, default=Path('build/ci-inputs'))
    staging.add_argument('--disc1', type=Path, required=True)
    staging.add_argument('--disc2', type=Path, required=True)
    restoring = commands.add_parser('restore', help='restore and hash-check both complete ISOs')
    restoring.add_argument('--input', type=Path, required=True)
    restoring.add_argument('--output', type=Path, default=Path('build/restored-isos'))
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        if args.command == 'stage':
            stage(args.output, args.disc1, args.disc2)
        else:
            restore(args.input, args.output)
    except (OSError, ValueError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
