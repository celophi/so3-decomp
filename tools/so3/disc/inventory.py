#!/usr/bin/env python3
"""Audit known SO3 container trees and extract code found inside the IOPRP image."""

import argparse
from collections import Counter
import json
from pathlib import Path
import sys
from tempfile import TemporaryDirectory

from tools.so3.disc.extract import CONFIG, ROOT, digest, hash_file, read_at, save, extract_visible
from tools.so3.disc.archives import ioprp_entries, pack_entries, zls_entries
from tools.so3.formats import (FormatError, TABLE_OFFSET, TABLE_SIZE, MAX_DECODED_SIZE,
                         classify, decode_chain, elf_info, overlay_info, read_table, require)


class Audit:
    def __init__(self, destination, key):
        self.destination = destination
        self.key = key
        self.nodes = []
        self.modules = []
        self.unresolved = []
        self.expanded_size = 0

    def visit(self, data, location, depth=0):
        require(depth <= 16, 'container nesting exceeds supported limit')
        require(len(self.nodes) < 200000, 'container entry count exceeds supported limit')
        kind = classify(data)
        node = {'location': location, 'format': kind, 'size': len(data), 'sha256': digest(data)}
        self.nodes.append(node)
        if kind in ('ELF', 'MWo3'):
            info = elf_info(data) if kind == 'ELF' else overlay_info(data)
            suffix = 'elf' if kind == 'ELF' else 'bin'
            stored = save(self.destination, f'modules/{location}.{suffix}', data)
            self.modules.append({**stored, 'location': location, **info})
        elif kind == 'PACK':
            # Some PACK-shaped records are external offset tables. Keep them explicit;
            # never chase their offsets outside the containing member.
            try:
                entries = pack_entries(data)
            except FormatError as error:
                self.unresolved.append({'location': location, 'format': kind, 'reason': str(error)})
                return
            node['entries'] = entries
            for entry in entries:
                self.visit(data[entry['offset']:entry['end']],
                           f'{location}/pack-{entry["index"]:04d}', depth + 1)
        elif kind == 'ZLS':
            entries = zls_entries(data)
            node['entries'] = entries
            for entry in entries:
                self.visit(data[entry['offset']:entry['end']],
                           f'{location}/zls-{entry["index"]:02d}', depth + 1)
        elif kind.startswith(('SLZ', 'SLE')):
            for i, block in enumerate(decode_chain(data, self.key)):
                self.expanded_size += len(block.data)
                require(self.expanded_size <= 8 * 1024**3, 'decoded audit size exceeds supported limit')
                self.visit(block.data, f'{location}/block-{i:02d}', depth + 1)


def audit(iso, destination, profile):
    require(not destination.exists() and not destination.is_symlink(),
            'output exists; choose a new --output directory')
    require(iso.stat().st_size == profile['iso_size'], 'disc size mismatch')
    print('Verifying complete ISO SHA-256...', flush=True)
    require(hash_file(iso) == profile['iso_sha256'], 'unsupported or modified ISO')
    destination.parent.mkdir(parents=True, exist_ok=True)
    with TemporaryDirectory(prefix='.so3-inventory-', dir=destination.parent) as temporary:
        staging = Path(temporary) / 'output'
        staging.mkdir()
        state = Audit(staging, bytes.fromhex(profile['sle_key']))
        _, boot = extract_visible(iso, staging, profile)
        state.visit(boot, 'iso/boot')
        rom = (staging / 'iso/IOPRP271.IMG').read_bytes()
        rom_entries = ioprp_entries(rom)
        for entry in rom_entries:
            if entry['name'] not in ('RESET', 'ROMDIR', 'EXTINFO'):
                state.visit(rom[entry['offset']:entry['end']], f'ioprp/{entry["name"]}')
        top_level = []
        with iso.open('rb') as stream:
            table = read_at(stream, TABLE_OFFSET, TABLE_SIZE)
            require(digest(table) == profile['table_sha256'], 'table hash mismatch')
            resources = read_table(table, profile['iso_size'])
            require(sum(bool(e['sectors']) for e in resources) == profile['populated_entries'],
                    'resource table entry count mismatch')
            for entry in resources:
                if not entry['allocated_size'] or entry['index'] == 0:
                    continue
                prefix = read_at(stream, entry['offset'], min(16, entry['allocated_size']))
                kind = classify(prefix)
                top_level.append({'resource': entry['index'], 'format': kind,
                                  'size': entry['allocated_size']})
                if kind in ('PACK', 'ZLS', 'MWo3') or kind.startswith(('SLZ', 'SLE')):
                    require(entry['allocated_size'] <= MAX_DECODED_SIZE, 'container allocation exceeds limit')
                    data = read_at(stream, entry['offset'], entry['allocated_size'])
                    state.visit(data, f'resource-{entry["index"]:04d}')
                elif kind == 'ELF':
                    data = read_at(stream, entry['offset'], entry['allocated_size'])
                    require(data[:len(boot)] == boot, 'unrecognized top-level ELF; extend the inventory')
                if entry['index'] % 500 == 0:
                    print(f'Audited through resource {entry["index"]}; {len(state.nodes)} container nodes', flush=True)
        formats = Counter(n['format'] for n in state.nodes)
        report = {'schema_version': 1,
                  'disc_sha256': profile['iso_sha256'],
                  'scope': 'Known inline PACK, SLZ/SLE, ZLS chains and IOPRP ROMDIR; opaque leaves and external PACK indices remain unresolved.',
                  'summary': {'nodes': len(state.nodes), 'code_modules': len(state.modules),
                              'module_formats': dict(sorted(Counter(m['format'] for m in state.modules).items())),
                              'node_formats': dict(sorted(formats.items())),
                              'unresolved_containers': len(state.unresolved),
                              'top_level_formats': dict(sorted(Counter(e['format'] for e in top_level).items()))},
                  'ioprp_directory': rom_entries, 'modules': state.modules,
                  'unresolved_containers': state.unresolved, 'top_level': top_level,
                  'nodes': state.nodes}
        (staging / 'report.json').write_text(json.dumps(report, indent=2) + '\n')
        require(not destination.exists() and not destination.is_symlink(),
                'output appeared during audit; choose a new --output directory')
        staging.rename(destination)
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('iso', type=Path)
    parser.add_argument('--output', type=Path, help='new directory; default build/inventory/<version>')
    args = parser.parse_args()
    try:
        profiles = json.loads(CONFIG.read_text())['versions']
        candidates = [(name, p) for name, p in profiles.items() if p['iso_size'] == args.iso.stat().st_size]
        require(len(candidates) == 1, 'unsupported disc size')
        name, profile = candidates[0]
        destination = args.output or ROOT / 'build/inventory' / name
        report = audit(args.iso, destination, profile)
        print(json.dumps(report['summary'], sort_keys=True))
        print(f'Inventory report: {destination}/report.json')
        return 0
    except (OSError, ValueError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
