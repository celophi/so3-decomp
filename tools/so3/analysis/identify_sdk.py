#!/usr/bin/env python3
"""Scan named PS2 patterns and recover surviving IOP symbols without Ghidra."""

import argparse
from collections import Counter, defaultdict
import json
import os
from pathlib import Path
import re
import subprocess
import xml.etree.ElementTree as ET

from tools.so3.analysis.analysis_tools import ROOT, checked_file, sha256
from tools.so3.build.boot import original_boot
from tools.so3.build.overlays import load_config
from tools.so3.disc.archives import ioprp_entries

PATTERNS = 'tools/ghidra-emotionengine-reloaded/r5900_LE_patterns.xml'
STDUMP = ROOT / 'tools/ccc/ccc_v2.1_linux-musl/stdump'
OUT = Path('working/sdk-identification')
HEADER = re.compile(r'^nonmatching ([\w.$]+), (0x[\da-fA-F]+)$')
INSTRUCTION = re.compile(r'^\s*/\* ([\da-fA-F]+) ([\da-fA-F]+) ([\da-fA-F]{8}) \*/')


def named_patterns(path):
    """Only accept fully specified named byte patterns; generic prologues are irrelevant."""
    result = defaultdict(list)
    for pattern in ET.parse(path).getroot().findall('pattern'):
        label = pattern.find('funcstart')
        if label is None or 'label' not in label.attrib:
            continue
        nodes = pattern.findall('data')
        if len(nodes) != 1 or not nodes[0].text:
            raise ValueError('unsupported named pattern structure')
        tokens = nodes[0].text.split()
        if not all(re.fullmatch(r'0x(?:[\da-fA-F]{2})+', token) for token in tokens):
            raise ValueError(f'non-exact named pattern: {label.attrib["label"]}')
        raw = bytes.fromhex(''.join(token[2:] for token in tokens))
        result[raw].append(label.attrib['label'])
    return {raw: sorted(set(names)) for raw, names in result.items()}


def functions(path, original, start, end, base):
    pending = None
    active = None
    raw = bytearray()
    offset = None
    for line in path.read_text().splitlines():
        header = HEADER.fullmatch(line)
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
        elif active and (ins := INSTRUCTION.match(line)):
            off, pc = int(ins[1], 16), int(ins[2], 16)
            data = bytes.fromhex(ins[3])
            if offset is None:
                offset = off
            if not (start <= off < end and off + 4 <= end and pc == base + off
                    and off == offset + len(raw) and original[off:off+4] == data):
                raise ValueError(f'{path}: stale bytes or invalid instruction mapping')
            raw.extend(data)
    if active or pending:
        raise ValueError(f'{path}: incomplete function')


def scan(output):
    import yaml
    patterns = named_patterns(checked_file(PATTERNS))
    boot = Path('config/boot.us.yaml')
    configs = [(boot, yaml.safe_load(boot.read_text()), original_boot())]
    configs += [(p, *load_config(p)) for p in sorted(Path('config/overlays').glob('*.yaml'))]
    matches, counts = [], {}
    for path, config, original in configs:
        module = 'boot' if path == boot else path.stem
        options, segments = config['options'], config['segments']
        counts[module] = 0
        for index, segment in enumerate(segments[:-1]):
            if not isinstance(segment, dict) or segment['type'] != 'code':
                continue
            following = segments[index+1]
            end = following[0] if isinstance(following, list) else following['start']
            subs = segment['subsegments']
            for i, (offset, kind, stem) in enumerate(subs):
                asm = Path(options['asm_path']) / (stem + '.s')
                limit = subs[i+1][0] if i+1 < len(subs) else end
                for function, raw in functions(asm, original, offset, limit,
                                               segment['vram'] - segment['start']):
                    counts[module] += 1
                    if raw not in patterns:
                        continue
                    matches.append({**function, 'module': module, 'aliases': patterns[raw],
                                    'binary': options['target_path'], 'binary_sha256': sha256(original),
                                    'source': str(Path(options['src_path']) / (stem + '.' + kind)),
                                    'asm': str(asm)})
    data = {'schema_version': 1, 'patterns': PATTERNS,
            'patterns_sha256': sha256(checked_file(PATTERNS).read_bytes()),
            'named_patterns': sum(map(len, patterns.values())), 'unique_patterns': len(patterns),
            'scanned_functions': counts, 'matches': sorted(matches, key=lambda f: (f['module'], f['offset']))}
    output.mkdir(parents=True, exist_ok=True)
    (output / 'scan.json').write_text(json.dumps(data, indent=2) + '\n')
    print(f'Scanned {sum(counts.values()):,} functions; {len(matches)} exact full-function matches.')
    print(dict(Counter(f['module'] for f in matches)))
    return data


def recover_symbols(output):
    # Verify the executable against the pinned archive, not a possibly edited local binary.
    import zipfile
    archive = checked_file('tools/ccc/ccc_v2.1_linux-musl.zip')
    with zipfile.ZipFile(archive) as z:
        if STDUMP.read_bytes() != z.read('ccc_v2.1_linux-musl/stdump'):
            raise ValueError('stdump changed; run python -m tools.so3.analysis.analysis_tools')
    output.mkdir(parents=True, exist_ok=True)
    manifest = json.loads(Path('disc/us-disc1/manifest.json').read_text())
    results = []
    modules = [{**m, 'input': str(Path('disc/us-disc1') / m['path'])}
               for m in manifest['modules'] if m['format'] == 'ELF']
    image = next(f for f in manifest['files'] if f['path'] == 'iso/IOPRP271.IMG')
    image_path = Path('disc/us-disc1') / image['path']
    raw_image = image_path.read_bytes()
    if sha256(raw_image) != image['sha256']:
        raise ValueError('IOPRP image hash mismatch')
    nested = output / 'ioprp'
    nested.mkdir(parents=True, exist_ok=True)
    for entry in ioprp_entries(raw_image):
        raw = raw_image[entry['offset']:entry['end']]
        if not raw.startswith(b'\x7fELF'):
            continue
        path = nested / (entry['name'] + '.elf')
        path.write_bytes(raw)
        modules.append({'input': str(path), 'sha256': sha256(raw),
                        'origin': {'image': str(image_path), 'image_sha256': image['sha256'],
                                   'offset': entry['offset'], 'end': entry['end']}})
    for module in modules:
        path = Path(module['input'])
        raw = path.read_bytes()
        if sha256(raw) != module['sha256']:
            raise ValueError(f'{path}: extraction hash mismatch')
        ident = path.stem
        target = output / (ident + '.json')
        result = subprocess.run([str(STDUMP), 'json', '--output', str(target), str(path)],
                                capture_output=True, text=True)
        (output / (ident + '.log')).write_text(result.stdout + result.stderr)
        if result.returncode:
            raise ValueError(f'CCC failed for {path}; see {output / (ident + ".log")}')
        data = json.loads(target.read_text())
        results.append({'path': str(path), 'sha256': module['sha256'], 'output': str(target),
                        'functions': len(data['functions']), 'types': len(data['data_types']),
                        'globals': len(data['global_variables']), 'labels': len(data['labels']),
                        'source_files': [f.get('name') for f in data['source_files']],
                        **({'origin': module['origin']} if 'origin' in module else {})})
    (output / 'summary.json').write_text(json.dumps(results, indent=2) + '\n')
    print(f'CCC processed {len(results)} ELF files; '
          f'{sum(r["functions"] for r in results)} function records recovered.')
    return results


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('scan', 'symbols'))
    parser.add_argument('--output', type=Path, default=OUT)
    args = parser.parse_args()
    os.chdir(ROOT)
    if args.command == 'scan':
        scan(args.output)
    else:
        recover_symbols(args.output / 'symbols')


if __name__ == '__main__':
    main()
