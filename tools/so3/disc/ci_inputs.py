#!/usr/bin/env python3
"""Package the game files CI needs into a private image, or turn it back into ISOs.

CI has to build and verify against the original game files, but those can't go
in the repository. So I put them in a private container image instead, built
from dockerfiles/ci-inputs.dockerfile.

- `stage` (or `make ci-inputs`) prepares that image's build context: the
  extracted main executable and overlays the build reads, plus both complete
  discs cut into 128 MiB parts.
- `restore` joins the parts from an image back into the two ISOs, and checks
  they're identical to the originals.

Both commands build their output in a temporary folder and only move it into
place once everything checks out.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import sys
import tempfile

from tools.so3.build.main import ORIGINAL, ROOT, VERSIONS, original_main
from tools.so3.build.overlays import CONFIGS, load_config
from tools.so3.formats import require

# Each disc is copied in 128 MiB parts, and both discs fit in 35 parts. Each
# COPY in the dockerfile takes one part from each disc, which keeps every image
# layer near 256 MiB, small enough to upload to GHCR before it times out.
PART_SIZE = 128 * 1024 * 1024
MAX_PARTS = 35
COPY_CHUNK_SIZE = 8 * 1024 * 1024

DISCS = ('us-disc1', 'us-disc2')
# Everything the build reads comes from disc 1's extraction.
EXTRACTED_DISC = Path('disc/us-disc1')
STAGE_OUTPUT = Path('build/ci-inputs')
RESTORE_OUTPUT = Path('build/restored-isos')


def part_count(profile, part_size):
    return (profile['iso_size'] + part_size - 1) // part_size


def part_name(ident, index):
    return f'{ident}.iso.part{index:03}'


def split_iso(source, output, ident, profile, part_size=PART_SIZE):
    """Cut a disc image into parts, each in its own numbered folder, and check its hash as I go."""
    require(source.stat().st_size == profile['iso_size'], f'{source}: ISO size mismatch')
    require(part_count(profile, part_size) <= MAX_PARTS, 'ISO exceeds the part count in dockerfiles/ci-inputs.dockerfile')
    checksum, size, index = hashlib.sha256(), 0, 0
    with source.open('rb') as original:
        while chunk := original.read(part_size):
            require(index < MAX_PARTS, f'{source}: ISO grew while copying')
            # parts/<index>/iso/ is what the dockerfile's COPY for that layer picks up.
            target = output / f'{index:03}' / 'iso' / part_name(ident, index)
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(chunk)
            checksum.update(chunk)
            size += len(chunk)
            index += 1
    require(size == profile['iso_size'], f'{source}: ISO size changed while copying')
    require(checksum.hexdigest() == profile['iso_sha256'], f'{source}: ISO SHA-256 mismatch')


def join_iso(source, target, ident, profile, part_size=PART_SIZE):
    """Join a disc's parts back into one image, and check it's identical to the original."""
    parts = [source / part_name(ident, index) for index in range(part_count(profile, part_size))]
    require(sorted(source.glob(f'{ident}.iso.part*')) == parts, f'{ident}: missing or unexpected ISO parts')
    checksum = hashlib.sha256()
    remaining = profile['iso_size']
    # 'x' refuses to overwrite a file that's already there.
    with target.open('xb') as restored:
        for part in parts:
            size = min(part_size, remaining)
            require(part.stat().st_size == size, f'{part}: incorrect part size')
            with part.open('rb') as stream:
                while chunk := stream.read(COPY_CHUNK_SIZE):
                    restored.write(chunk)
                    checksum.update(chunk)
            remaining -= size
    require(target.stat().st_size == profile['iso_size'], f'{ident}: restored ISO size mismatch')
    require(checksum.hexdigest() == profile['iso_sha256'], f'{ident}: restored ISO SHA-256 mismatch')


def extracted_inputs():
    """The extracted files the build reads, as {path: bytes}, each checked against its expected hash."""
    inputs = {ORIGINAL: original_main()}
    for path in sorted(CONFIGS.glob('*.yaml')):
        config, data = load_config(path)
        target = Path(config['options']['target_path'])
        require(target.parts[:2] == EXTRACTED_DISC.parts and '..' not in target.parts,
                f'{path}: expected a path under {EXTRACTED_DISC}')
        require(target not in inputs, f'duplicate CI input: {target}')
        inputs[target] = data
    require(len(inputs) > 1, 'no overlay configurations found')
    return inputs


def disc_profiles():
    return json.loads((ROOT / VERSIONS).read_text())['versions']


def stage(output, disc1, disc2):
    """Write the CI image's build context to output."""
    require(not output.exists(), f'{output} already exists; choose a new --output directory')
    inputs = extracted_inputs()
    profiles = disc_profiles()
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = Path(tempfile.mkdtemp(prefix='.ci-inputs-', dir=output.parent))
    try:
        for path, data in inputs.items():
            target = temporary / path
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_bytes(data)
        checksums = []
        for ident, source in zip(DISCS, (disc1, disc2)):
            print(f'Splitting and verifying {ident}...', flush=True)
            split_iso(source, temporary / 'parts', ident, profiles[ident])
            checksums.append(f'{profiles[ident]["iso_sha256"]}  {ident}.iso')
        # In the format sha256sum -c reads, so the restored discs are easy to check by hand.
        (temporary / 'SHA256SUMS').write_text('\n'.join(checksums) + '\n')
        temporary.rename(output)
    finally:
        if temporary.exists():
            shutil.rmtree(temporary)
    print(f'Staged both complete discs and {len(inputs)} extracted files in {output}')


def restore(source, output):
    """Join both discs from the parts in source, and write them to output."""
    require(not output.exists(), f'{output} already exists; choose a new --output directory')
    profiles = disc_profiles()
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = Path(tempfile.mkdtemp(prefix='.restored-isos-', dir=output.parent))
    try:
        for ident in DISCS:
            join_iso(source, temporary / f'{ident}.iso', ident, profiles[ident])
            print(f'Restored and verified {ident}', flush=True)
        temporary.rename(output)
    finally:
        if temporary.exists():
            shutil.rmtree(temporary)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    commands = parser.add_subparsers(dest='command', required=True)
    staging = commands.add_parser('stage', help='prepare a new image build context')
    staging.add_argument('--output', type=Path, default=STAGE_OUTPUT)
    staging.add_argument('--disc1', type=Path, required=True)
    staging.add_argument('--disc2', type=Path, required=True)
    restoring = commands.add_parser('restore', help='restore and hash-check both complete ISOs')
    restoring.add_argument('--input', type=Path, required=True)
    restoring.add_argument('--output', type=Path, default=RESTORE_OUTPUT)
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
