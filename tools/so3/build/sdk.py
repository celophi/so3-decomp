"""Check that the SDK code I've set aside really is SDK code.

Some of the game's code isn't the game's own. It's Sony's console libraries
(the SDK), like the kernel syscall wrappers, plus the C library and the
compiler's C++ runtime that got linked in. I don't decompile those, and they
don't count toward progress. They stay as INCLUDE_ASM placeholders in src/sdk/
for the main executable, or src/overlays/<module>/sdk/ for an overlay.

Leaving code out of progress is easy to abuse by accident, so a file being in
an sdk folder isn't enough. Every SDK unit has to be listed in
config/manifests/sdk-functions.json, with its range and a hash of each function.
tools/so3/analysis/identify_sdk.py finds candidates by matching functions
against known SDK byte patterns, and they go in the manifest once I've
reviewed them. Each entry says why I think it's library code. A few are
assumptions I haven't matched to a library yet, and their unit names end in
_guess. On every build I check that:

- every SDK unit in the configs is in the manifest, and the other way around,
- its range hasn't moved, and its functions still cover it exactly,
- each function's bytes in the original still have the reviewed hash,
- and the source is still nothing but the placeholders for those functions.
"""

import hashlib
import json
from pathlib import Path
import re

from tools.so3.build.assembly import PLACEHOLDER_HEADER
from tools.so3.build.main import module_name
from tools.so3.build.subsegments import subsegment_end, subsegment_parts

MANIFEST = Path('config/manifests/sdk-functions.json')
INCLUDE = re.compile(r'INCLUDE_ASM\("([^"\n]+)",\s*([\w.$]+)\);')
INCLUDE_PLACEHOLDER_HEADER = f'#include "{PLACEHOLDER_HEADER}"'

MAIN_SDK_FOLDER = Path('src/sdk')
OVERLAY_SOURCES = ('src', 'overlays')  # Overlay sources are in src/overlays/<module>/...
SDK_FOLDER_NAME = 'sdk'

INSTRUCTION_SIZE = 4  # Every function is a whole number of 4-byte instructions.


def code_units(config):
    """List every C/C++ unit in a Splat config, with its range and assembly folder.

    `start` and `end` are file offsets, and adding `base` to one gives its
    address once loaded.
    """
    segments, options = config['segments'], config['options']
    # The last segment only marks where the file ends.
    for number, segment in enumerate(segments[:-1]):
        if not isinstance(segment, dict) or segment['type'] != 'code':
            continue
        subsegments = segment['subsegments']
        for index, subsegment in enumerate(subsegments):
            start, kind, name = subsegment_parts(subsegment)
            if kind not in ('c', 'cpp'):
                continue
            yield {'source': str(Path(options['src_path']) / f'{name}.{kind}'),
                   'start': start, 'end': subsegment_end(subsegments, index, segments[number + 1]),
                   'base': segment['vram'] - segment['start'],
                   'asm': str(Path(options['asm_path']) / 'nonmatchings' / name)}


def sdk_path(source):
    """Whether a source is in an SDK folder: src/sdk/ or src/overlays/<module>/sdk/."""
    parts = Path(source).parts
    in_overlay_sdk = len(parts) > 3 and parts[:2] == OVERLAY_SOURCES and parts[3] == SDK_FOLDER_NAME
    return Path(source).is_relative_to(MAIN_SDK_FOLDER) or in_overlay_sdk


def configured_sdk_units(configs):
    """Find every unit in an SDK folder, as {source: (module, unit, original binary path)}."""
    found = {}
    for path, config in configs:
        for unit in code_units(config):
            if sdk_path(unit['source']):
                if unit['source'] in found:
                    raise ValueError('duplicate SDK source path')
                found[unit['source']] = (module_name(path), unit, config['options']['target_path'])
    return found


def check_functions(reviewed, split, original):
    """Check the reviewed functions cover the unit exactly and still have their hashes.

    Returns their names in order.
    """
    source = reviewed['source']
    cursor = reviewed['start']
    names = []
    for function in reviewed['functions']:
        offset, size = function['offset'], function['size']
        if (offset != cursor or size <= 0 or size % INSTRUCTION_SIZE or
                function['address'] != offset + split['base'] or
                offset + size > reviewed['end']):
            raise ValueError(f'{source}: SDK functions do not cover the unit exactly')
        if hashlib.sha256(original[offset:offset + size]).hexdigest() != function['sha256']:
            raise ValueError(f'{source}: SDK function hash mismatch')
        names.append(function['name'])
        cursor += size
    if cursor != reviewed['end'] or len(set(names)) != len(names):
        raise ValueError(f'{source}: incomplete or duplicate SDK function coverage')
    return names


def check_source(source, folder, names):
    """Check the source is only the placeholder header and one INCLUDE_ASM per function, in order."""
    text = Path(source).read_text()
    includes = INCLUDE.findall(text)
    remainder = INCLUDE.sub('', text).replace(INCLUDE_PLACEHOLDER_HEADER, '').strip()
    if remainder or includes != [(folder, name) for name in names]:
        raise ValueError(f'{source}: SDK source must retain exactly the reviewed INCLUDE_ASM functions')


def validate_sdk_units(configs, manifest=None):
    """Check every SDK unit in these configs against the manifest, and return their sources.

    Only the manifest can leave a unit out of progress. Being in an sdk folder
    on its own is never enough, so anything that doesn't check out fails the
    build.
    """
    if manifest is None:
        manifest = json.loads(MANIFEST.read_text())
    found = configured_sdk_units(configs)
    selected = {module_name(path) for path, _ in configs}
    accepted = set()
    originals = {}
    for reviewed in manifest['units']:
        # A build of just the overlays doesn't need the main executable's entries.
        if reviewed['module'] not in selected:
            continue
        source = reviewed['source']
        if source not in found or source in accepted:
            raise ValueError(f'{source}: unconfigured or duplicate SDK exclusion')
        module, split, binary = found[source]
        if (module, split['start'], split['end'], binary) != (
                reviewed['module'], reviewed['start'], reviewed['end'], reviewed['binary']):
            raise ValueError(f'{source}: SDK split range changed')
        if binary not in originals:
            originals[binary] = Path(binary).read_bytes()
        original = originals[binary]
        if hashlib.sha256(original).hexdigest() != reviewed['binary_sha256']:
            raise ValueError(f'{source}: SDK original hash mismatch')
        names = check_functions(reviewed, split, original)
        check_source(source, split['asm'], names)
        accepted.add(source)
    if accepted != set(found):
        raise ValueError(f'unreviewed SDK units: {sorted(set(found) - accepted)}')
    return accepted
