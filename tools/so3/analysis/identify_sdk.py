#!/usr/bin/env python3
"""Find Sony SDK code in the game, and recover names from the disc's IOP modules.

This is how I find SDK code (Sony's console libraries) without opening Ghidra.
It has two commands, and both write to working/sdk-identification/:

- `scan` compares every function in every module with the named byte patterns
  from ghidra-emotionengine-reloaded. Only a whole function that matches a
  pattern exactly counts. The matches are candidates for
  config/manifests/sdk-functions.json, which I review before adding (see
  tools/so3/build/sdk.py).
- `symbols` looks at the IOP modules instead. The IOP is the PS2's second
  processor, which handles input and output. Its modules are separate ELF
  files on the disc, and some still have their debugging symbols. CCC's
  stdump reads those into JSON, with function names, types, and globals.

`make analysis-tools` downloads the pinned patterns and CCC first.
"""

import argparse
from collections import Counter, defaultdict
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import xml.etree.ElementTree as ET
import zipfile

from tools.so3.analysis.analysis_tools import ROOT, checked_file, sha256
from tools.so3.build.main import module_name
from tools.so3.build.overlays import load_module, module_configs
from tools.so3.build.subsegments import subsegment_end, subsegment_parts
from tools.so3.disc.archives import ioprp_entries

PATTERNS = 'tools/ghidra-emotionengine-reloaded/r5900_LE_patterns.xml'
CCC_ARCHIVE = 'tools/ccc/ccc_v2.1_linux-musl.zip'
STDUMP_IN_ARCHIVE = 'ccc_v2.1_linux-musl/stdump'
STDUMP = ROOT / 'tools/ccc' / STDUMP_IN_ARCHIVE
OUTPUT = Path('working/sdk-identification')
SCAN_SCHEMA_VERSION = 1

DISC = Path('disc/us-disc1')
DISC_MANIFEST = DISC / 'manifest.json'
# The image that bundles the replacement IOP modules the game loads at boot.
IOP_IMAGE = 'iso/IOPRP271.IMG'
ELF_MAGIC = b'\x7fELF'

INSTRUCTION_SIZE = 4

# The lines of a function in Splat's assembly that I need:
#     nonmatching func_00101270, 0x8
#     glabel func_00101270
#     /* 000670 00101270 0800E003 */  jr $ra
#     endlabel func_00101270
# The comment in front of each instruction is its file offset, address, and the
# instruction word itself.
FUNCTION_HEADER = re.compile(r'^nonmatching ([\w.$]+), (0x[\da-fA-F]+)$')
INSTRUCTION = re.compile(r'^\s*/\* ([\da-fA-F]+) ([\da-fA-F]+) ([\da-fA-F]{8}) \*/')
# A pattern byte written out in full, like 0x27bdfff0. Patterns with wildcards are skipped.
EXACT_BYTES = re.compile(r'0x(?:[\da-fA-F]{2})+')


def named_patterns(path):
    """Read the patterns that name a function and spell out every byte, as {bytes: [names]}.

    The file also has generic patterns, like common function starts, that don't
    say which function they are. Those don't help here, so I skip them.
    """
    result = defaultdict(list)
    for pattern in ET.parse(path).getroot().findall('pattern'):
        label = pattern.find('funcstart')
        if label is None or 'label' not in label.attrib:
            continue
        nodes = pattern.findall('data')
        if len(nodes) != 1 or not nodes[0].text:
            raise ValueError('unsupported named pattern structure')
        tokens = nodes[0].text.split()
        if not all(EXACT_BYTES.fullmatch(token) for token in tokens):
            raise ValueError(f'non-exact named pattern: {label.attrib["label"]}')
        raw = bytes.fromhex(''.join(token[2:] for token in tokens))
        result[raw].append(label.attrib['label'])
    return {raw: sorted(set(names)) for raw, names in result.items()}


def functions(path, original, start, end, base):
    """Read every function in one of Splat's assembly files, checked against the original.

    Yields each function's details and bytes. Every instruction has to sit
    inside start..end, be at the address the comment says, and still have the
    same bytes as the original. If not, the assembly is out of date.
    """
    pending = None  # Seen the nonmatching line, waiting for glabel.
    active = None  # Inside a function, as (name, size).
    raw = bytearray()
    offset = None
    for line in path.read_text().splitlines():
        header = FUNCTION_HEADER.fullmatch(line)
        if header:
            if active or pending:
                raise ValueError(f'{path}: nested function')
            pending = (header[1], int(header[2], 16))
        elif line.startswith('glabel ') and pending:
            if line.split()[1] != pending[0]:
                raise ValueError(f'{path}: inconsistent function label')
            active, pending = pending, None
            raw, offset = bytearray(), None
        elif line.startswith('endlabel ') and active:
            if line.split()[1] != active[0] or len(raw) != active[1] or offset is None:
                raise ValueError(f'{path}: inconsistent function extent')
            yield {'name': active[0], 'offset': offset, 'address': base + offset,
                   'size': len(raw), 'sha256': sha256(raw)}, bytes(raw)
            active = None
        elif active and (instruction := INSTRUCTION.match(line)):
            position, address = int(instruction[1], 16), int(instruction[2], 16)
            data = bytes.fromhex(instruction[3])
            if offset is None:
                offset = position
            if not (start <= position < end and position + INSTRUCTION_SIZE <= end and address == base + position
                    and position == offset + len(raw) and original[position:position + INSTRUCTION_SIZE] == data):
                raise ValueError(f'{path}: stale bytes or invalid instruction mapping')
            raw.extend(data)
    if active or pending:
        raise ValueError(f'{path}: incomplete function')


def module_functions(config, original):
    """Every function in a module's code, with the unit it's in."""
    options, segments = config['options'], config['segments']
    # The last segment only marks where the file ends.
    for number, segment in enumerate(segments[:-1]):
        if not isinstance(segment, dict) or segment['type'] != 'code':
            continue
        subsegments = segment['subsegments']
        for index, subsegment in enumerate(subsegments):
            offset, kind, name = subsegment_parts(subsegment)
            if kind not in ('asm', 'c', 'cpp'):
                continue  # Padding, data, and rodata have no functions in them.
            assembly = Path(options['asm_path']) / f'{name}.s'
            end = subsegment_end(subsegments, index, segments[number + 1])
            base = segment['vram'] - segment['start']
            for function, raw in functions(assembly, original, offset, end, base):
                yield function, raw, {'source': str(Path(options['src_path']) / f'{name}.{kind}'),
                                      'asm': str(assembly)}


def scan(output):
    """Match every function against the named patterns and write scan.json."""
    patterns = named_patterns(checked_file(PATTERNS))
    matches, counts = [], {}
    for path in module_configs():
        config, original = load_module(path)
        module = module_name(path)
        counts[module] = 0
        for function, raw, unit in module_functions(config, original):
            counts[module] += 1
            if raw not in patterns:
                continue
            matches.append({**function, 'module': module, 'aliases': patterns[raw],
                            'binary': config['options']['target_path'], 'binary_sha256': sha256(original),
                            **unit})
    data = {'schema_version': SCAN_SCHEMA_VERSION, 'patterns': PATTERNS,
            'patterns_sha256': sha256(checked_file(PATTERNS).read_bytes()),
            'named_patterns': sum(map(len, patterns.values())), 'unique_patterns': len(patterns),
            'scanned_functions': counts,
            'matches': sorted(matches, key=lambda function: (function['module'], function['offset']))}
    output.mkdir(parents=True, exist_ok=True)
    (output / 'scan.json').write_text(json.dumps(data, indent=2) + '\n')
    print(f'Scanned {sum(counts.values()):,} functions; {len(matches)} exact full-function matches.')
    print(dict(Counter(function['module'] for function in matches)))
    return data


def check_stdump():
    """Check stdump against the pinned archive, not just whatever is in tools/ccc/ now."""
    archive = checked_file(CCC_ARCHIVE)
    with zipfile.ZipFile(archive) as contents:
        if STDUMP.read_bytes() != contents.read(STDUMP_IN_ARCHIVE):
            raise ValueError('stdump changed; run python -m tools.so3.analysis.analysis_tools')


def iop_modules(output):
    """List every IOP module to read, each with the hash it should have.

    That's the ELF modules the disc extraction found, plus the ones inside the
    IOP image, which I write out to output/ioprp/ first.
    """
    manifest = json.loads(DISC_MANIFEST.read_text())
    modules = [{**module, 'input': str(DISC / module['path'])}
               for module in manifest['modules'] if module['format'] == 'ELF']
    image = next(entry for entry in manifest['files'] if entry['path'] == IOP_IMAGE)
    image_path = DISC / image['path']
    raw_image = image_path.read_bytes()
    if sha256(raw_image) != image['sha256']:
        raise ValueError('IOPRP image hash mismatch')
    nested = output / 'ioprp'
    nested.mkdir(parents=True, exist_ok=True)
    for entry in ioprp_entries(raw_image):
        raw = raw_image[entry['offset']:entry['end']]
        if not raw.startswith(ELF_MAGIC):
            continue
        path = nested / f"{entry['name']}.elf"
        path.write_bytes(raw)
        modules.append({'input': str(path), 'sha256': sha256(raw),
                        'origin': {'image': str(image_path), 'image_sha256': image['sha256'],
                                   'offset': entry['offset'], 'end': entry['end']}})
    return modules


def dump_symbols(module, output):
    """Run stdump on one module and summarise what it found."""
    path = Path(module['input'])
    if sha256(path.read_bytes()) != module['sha256']:
        raise ValueError(f'{path}: extraction hash mismatch')
    target = output / f'{path.stem}.json'
    log = output / f'{path.stem}.log'
    result = subprocess.run([str(STDUMP), 'json', '--output', str(target), str(path)],
                            capture_output=True, text=True)
    log.write_text(result.stdout + result.stderr)
    if result.returncode:
        raise ValueError(f'CCC failed for {path}; see {log}')
    data = json.loads(target.read_text())
    return {'path': str(path), 'sha256': module['sha256'], 'output': str(target),
            'functions': len(data['functions']), 'types': len(data['data_types']),
            'globals': len(data['global_variables']), 'labels': len(data['labels']),
            'source_files': [source.get('name') for source in data['source_files']],
            **({'origin': module['origin']} if 'origin' in module else {})}


def recover_symbols(output):
    """Dump the symbols of every IOP module and write summary.json."""
    check_stdump()
    output.mkdir(parents=True, exist_ok=True)
    results = [dump_symbols(module, output) for module in iop_modules(output)]
    (output / 'summary.json').write_text(json.dumps(results, indent=2) + '\n')
    print(f'CCC processed {len(results)} ELF files; '
          f'{sum(result["functions"] for result in results)} function records recovered.')
    return results


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('command', choices=('scan', 'symbols'))
    parser.add_argument('--output', type=Path, default=OUTPUT)
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        if args.command == 'scan':
            scan(args.output)
        else:
            recover_symbols(args.output / 'symbols')
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
