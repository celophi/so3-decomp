#!/usr/bin/env python3
"""Look inside every container on a disc and find all the code hiding in them.

extract.py only goes one level deep: it decodes each resource and saves the
code it finds there. Some resources hold more containers, though, like a PACK
of ZLS chains of compressed blocks. This follows all of them down (see
archives.py for the formats), along with the members of the IOPRP image, and
saves every code module it finds wherever it was.

Run it with `make inventory ISO=/path/disc.iso`. The result goes to
build/inventory/<version>/, with a report.json listing every container it
visited, every module it found, and the containers it couldn't open.
"""

import argparse
from collections import Counter
import json
from pathlib import Path
import sys
from tempfile import TemporaryDirectory

from tools.so3.disc.archives import ioprp_entries, pack_entries, zls_entries
from tools.so3.disc.extract import (
    CODE_FORMATS, HEADER_PEEK_SIZE, ROOT, check_disc, digest, extract_visible, find_profile, is_compressed,
    module_extension, module_info, read_at, save,
)
from tools.so3.formats import (FormatError, TABLE_OFFSET, TABLE_SIZE, MAX_DECODED_SIZE,
                               classify, decode_chain, read_table, require)

OUTPUT = ROOT / 'build/inventory'
REPORT_SCHEMA_VERSION = 1
SCOPE = ('Known inline PACK, SLZ/SLE, ZLS chains and IOPRP ROMDIR; opaque leaves and external PACK '
         'indices remain unresolved.')
IOP_IMAGE = 'iso/IOPRP271.IMG'
# These IOPRP members are the image's own bookkeeping, not modules.
IOPRP_BOOKKEEPING = ('RESET', 'ROMDIR', 'EXTINFO')
# Top-level resources worth opening: containers, compressed blocks (checked
# separately), and overlays, which are code themselves.
VISITED_FORMATS = ('PACK', 'ZLS', 'MWo3')

# Limits, so a broken or hostile container can't make the audit run forever or fill the disk.
MAX_DEPTH = 16
MAX_NODES = 200_000
MAX_EXPANDED_SIZE = 8 * 1024**3
PROGRESS_EVERY = 500


class Audit:
    """Visit containers recursively, recording each one and saving the code inside."""

    def __init__(self, destination, key):
        self.destination = destination
        self.key = key
        self.nodes = []
        self.modules = []
        self.unresolved = []
        self.expanded_size = 0

    def visit(self, data, location, depth=0):
        """Record one container or file at `location` (like resource-0075/block-00/pack-0003), then open it."""
        require(depth <= MAX_DEPTH, 'container nesting exceeds supported limit')
        require(len(self.nodes) < MAX_NODES, 'container entry count exceeds supported limit')
        kind = classify(data)
        node = {'location': location, 'format': kind, 'size': len(data), 'sha256': digest(data)}
        self.nodes.append(node)
        if kind in CODE_FORMATS:
            stored = save(self.destination, f'modules/{location}.{module_extension(kind)}', data)
            self.modules.append({**stored, 'location': location, **module_info(kind, data)})
        elif kind == 'PACK':
            # Some files that start with PACK are really an index into another
            # file. I write those down as unresolved and never follow their
            # offsets outside the member I'm in.
            try:
                entries = pack_entries(data)
            except FormatError as error:
                self.unresolved.append({'location': location, 'format': kind, 'reason': str(error)})
                return
            node['entries'] = entries
            for entry in entries:
                self.visit(data[entry['offset']:entry['end']], f'{location}/pack-{entry["index"]:04d}', depth + 1)
        elif kind == 'ZLS':
            entries = zls_entries(data)
            node['entries'] = entries
            for entry in entries:
                self.visit(data[entry['offset']:entry['end']], f'{location}/zls-{entry["index"]:02d}', depth + 1)
        elif is_compressed(kind):
            for index, block in enumerate(decode_chain(data, self.key)):
                self.expanded_size += len(block.data)
                require(self.expanded_size <= MAX_EXPANDED_SIZE, 'decoded audit size exceeds supported limit')
                self.visit(block.data, f'{location}/block-{index:02d}', depth + 1)


def visit_ioprp(state, staging):
    """Visit every module in the IOPRP image, which extract_visible has already copied out."""
    rom = (staging / IOP_IMAGE).read_bytes()
    entries = ioprp_entries(rom)
    for entry in entries:
        if entry['name'] not in IOPRP_BOOKKEEPING:
            state.visit(rom[entry['offset']:entry['end']], f'ioprp/{entry["name"]}')
    return entries


def visit_resources(state, iso, profile, boot):
    """Visit every resource in the table that could hold code, and list each one's format."""
    top_level = []
    with iso.open('rb') as stream:
        table = read_at(stream, TABLE_OFFSET, TABLE_SIZE)
        require(digest(table) == profile['table_sha256'], 'table hash mismatch')
        resources = read_table(table, profile['iso_size'])
        require(sum(bool(entry['sectors']) for entry in resources) == profile['populated_entries'],
                'resource table entry count mismatch')
        for entry in resources:
            # Skip empty entries, and resource 0, which is the table itself.
            if not entry['allocated_size'] or entry['index'] == 0:
                continue
            size = entry['allocated_size']
            kind = classify(read_at(stream, entry['offset'], min(HEADER_PEEK_SIZE, size)))
            top_level.append({'resource': entry['index'], 'format': kind, 'size': size})
            if kind in VISITED_FORMATS or is_compressed(kind):
                require(size <= MAX_DECODED_SIZE, 'container allocation exceeds limit')
                state.visit(read_at(stream, entry['offset'], size), f'resource-{entry["index"]:04d}')
            elif kind == 'ELF':
                # The only top-level ELF I know of is a copy of the main executable.
                data = read_at(stream, entry['offset'], size)
                require(data[:len(boot)] == boot, 'unrecognized top-level ELF; extend the inventory')
            if entry['index'] % PROGRESS_EVERY == 0:
                print(f'Audited through resource {entry["index"]}; {len(state.nodes)} container nodes', flush=True)
    return top_level


def sorted_counts(items):
    return dict(sorted(Counter(items).items()))


def audit(iso, destination, profile):
    """Check the disc, audit everything on it into a new destination folder, and return the report."""
    require(not destination.exists() and not destination.is_symlink(),
            'output exists; choose a new --output directory')
    check_disc(iso, profile)
    destination.parent.mkdir(parents=True, exist_ok=True)
    # Everything is built in a staging folder first, so a failed run leaves nothing behind.
    with TemporaryDirectory(prefix='.so3-inventory-', dir=destination.parent) as temporary:
        staging = Path(temporary) / 'output'
        staging.mkdir()
        state = Audit(staging, bytes.fromhex(profile['sle_key']))
        _, boot = extract_visible(iso, staging, profile)
        state.visit(boot, 'iso/boot')
        rom_entries = visit_ioprp(state, staging)
        top_level = visit_resources(state, iso, profile, boot)
        report = {'schema_version': REPORT_SCHEMA_VERSION,
                  'disc_sha256': profile['iso_sha256'],
                  'scope': SCOPE,
                  'summary': {'nodes': len(state.nodes), 'code_modules': len(state.modules),
                              'module_formats': sorted_counts(module['format'] for module in state.modules),
                              'node_formats': sorted_counts(node['format'] for node in state.nodes),
                              'unresolved_containers': len(state.unresolved),
                              'top_level_formats': sorted_counts(entry['format'] for entry in top_level)},
                  'ioprp_directory': rom_entries, 'modules': state.modules,
                  'unresolved_containers': state.unresolved, 'top_level': top_level,
                  'nodes': state.nodes}
        (staging / 'report.json').write_text(json.dumps(report, indent=2) + '\n')
        require(not destination.exists() and not destination.is_symlink(),
                'output appeared during audit; choose a new --output directory')
        staging.rename(destination)
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('iso', type=Path)
    parser.add_argument('--output', type=Path, help='new directory; default build/inventory/<version>')
    args = parser.parse_args()
    try:
        name, profile = find_profile(args.iso)
        destination = args.output or OUTPUT / name
        report = audit(args.iso, destination, profile)
        print(json.dumps(report['summary'], sort_keys=True))
        print(f'Inventory report: {destination}/report.json')
        return 0
    except (OSError, ValueError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
