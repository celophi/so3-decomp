"""Validate reviewed SDK exclusions against split ranges and original bytes."""

import hashlib
import json
from pathlib import Path
import re

MANIFEST = Path('config/manifests/sdk-functions.json')
INCLUDE = re.compile(r'INCLUDE_ASM\("([^"\n]+)",\s*([\w.$]+)\);')


def code_units(config):
    segments, options = config['segments'], config['options']
    for index, segment in enumerate(segments[:-1]):
        if not isinstance(segment, dict) or segment['type'] != 'code':
            continue
        following = segments[index+1]
        end = following[0] if isinstance(following, list) else following['start']
        subs = segment['subsegments']
        for i, (start, kind, name) in enumerate(subs):
            if kind not in ('c', 'cpp'):
                continue
            yield {'source': str(Path(options['src_path']) / (name + '.' + kind)),
                   'start': start, 'end': subs[i+1][0] if i+1 < len(subs) else end,
                   'base': segment['vram'] - segment['start'],
                   'asm': str(Path(options['asm_path']) / 'nonmatchings' / name)}


def sdk_path(source):
    """SDK units live in src/sdk/ (boot) or src/overlays/<module>/sdk/."""
    parts = Path(source).parts
    return Path(source).is_relative_to('src/sdk') or (len(parts) > 3 and parts[:2] == ('src', 'overlays') and parts[3] == 'sdk')


def validate_sdk_units(configs, manifest=None):
    """Fail closed: a directory name alone never authorizes a progress exclusion."""
    if manifest is None:
        manifest = json.loads(MANIFEST.read_text())
    known = {}
    selected = {"boot" if path.name == "boot.us.yaml" else path.stem for path, _ in configs}
    for path, config in configs:
        module = 'boot' if path.name == 'boot.us.yaml' else path.stem
        for unit in code_units(config):
            if sdk_path(unit['source']):
                if unit['source'] in known:
                    raise ValueError('duplicate SDK source path')
                known[unit['source']] = (module, unit, config['options']['target_path'])
    accepted = set()
    originals = {}
    for unit in manifest['units']:
        if unit['module'] not in selected:
            continue
        source = unit['source']
        if source not in known or source in accepted:
            raise ValueError(f'{source}: unconfigured or duplicate SDK exclusion')
        module, split, binary = known[source]
        if (module, split['start'], split['end'], binary) != (
                unit['module'], unit['start'], unit['end'], unit['binary']):
            raise ValueError(f'{source}: SDK split range changed')
        if binary not in originals:
            originals[binary] = Path(binary).read_bytes()
        raw = originals[binary]
        if hashlib.sha256(raw).hexdigest() != unit['binary_sha256']:
            raise ValueError(f'{source}: SDK original hash mismatch')
        cursor = unit['start']
        names = []
        for function in unit['functions']:
            offset, size = function['offset'], function['size']
            if (offset != cursor or size <= 0 or size % 4 or
                    function['address'] != offset + split['base'] or
                    offset + size > unit['end']):
                raise ValueError(f'{source}: SDK functions do not cover the unit exactly')
            if hashlib.sha256(raw[offset:offset+size]).hexdigest() != function['sha256']:
                raise ValueError(f'{source}: SDK function hash mismatch')
            names.append(function['name'])
            cursor += size
        if cursor != unit['end'] or len(set(names)) != len(names):
            raise ValueError(f'{source}: incomplete or duplicate SDK function coverage')
        text = Path(source).read_text()
        includes = INCLUDE.findall(text)
        remainder = INCLUDE.sub('', text).replace('#include "include_asm.h"', '').strip()
        if remainder or includes != [(split['asm'], name) for name in names]:
            raise ValueError(f'{source}: SDK source must retain exactly the reviewed INCLUDE_ASM functions')
        accepted.add(source)
    if accepted != set(known):
        raise ValueError(f'unreviewed SDK units: {sorted(set(known) - accepted)}')
    return accepted
