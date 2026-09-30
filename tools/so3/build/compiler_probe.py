#!/usr/bin/env python3
"""Fetch hash-pinned CodeWarrior candidates and compare reconstructed boot probes."""

import argparse
import io
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
import tarfile
import tempfile
import urllib.request

from tools.so3.build.boot import ROOT, original_boot, sha256
from tools.so3.formats import elf_info, require

CONFIG = ROOT / 'config/compilers.json'
COMPILERS = ROOT / 'build/compilers'
RESULTS = ROOT / 'build/compiler-probes'


def verify_compiler(record, directory):
    for name, expected in record['files'].items():
        require(sha256((directory / name).read_bytes()) == expected,
                f"Compiler file hash mismatch: {record['id']}/{name}")


def setup(record):
    directory = COMPILERS / record['id']
    if directory.exists():
        verify_compiler(record, directory)
        print(f"Verified {record['id']}")
        return
    COMPILERS.mkdir(parents=True, exist_ok=True)
    print(f"Downloading {record['id']}", flush=True)
    with urllib.request.urlopen(record['url'], timeout=60) as response:
        archive = response.read()
    require(sha256(archive) == record['archive_sha256'],
            f"Archive hash mismatch: {record['id']}")
    # Only copy the explicitly pinned regular files; never extract archive paths.
    with tempfile.TemporaryDirectory(dir=COMPILERS) as temporary:
        staging = Path(temporary) / 'compiler'
        staging.mkdir()
        with tarfile.open(fileobj=io.BytesIO(archive)) as tar:
            for name in record['files']:
                require(Path(name).name == name, 'Compiler files must have flat names')
                member = tar.getmember(name)
                require(member.isfile(), f'Expected a regular file: {name}')
                with tar.extractfile(member) as source:
                    (staging / name).write_bytes(source.read())
        verify_compiler(record, staging)
        staging.rename(directory)


def object_functions(data):
    """Read function bytes by section index, including duplicate .text names."""
    info = elf_info(data)
    require(info['elf_type'] == 1, 'Expected a relocatable ELF object')
    shoff = struct.unpack_from('<I', data, 32)[0]
    shsize, count = struct.unpack_from('<HH', data, 46)
    headers = [struct.unpack_from('<10I', data, shoff + i * shsize) for i in range(count)]
    functions = {}
    for table in headers:
        if table[1] != 2:  # SHT_SYMTAB
            continue
        require(table[9] == 16 and table[5] % 16 == 0 and table[6] < count,
                'Invalid ELF symbol table')
        names = headers[table[6]]
        strings = data[names[4]:names[4] + names[5]]
        for offset in range(table[4], table[4] + table[5], 16):
            name, value, size, attributes, _, section = struct.unpack_from('<IIIBBH', data, offset)
            if attributes & 15 != 2:  # STT_FUNC
                continue
            require(0 < section < count, 'Invalid function section')
            header = headers[section]
            require(header[1] == 1 and value + size <= header[5], 'Function exceeds section')
            require(name < len(strings), 'Invalid function name')
            symbol = strings[name:].split(b'\0', 1)[0].decode('ascii')
            # These probes are deliberately relocation-free. Never mask fixups.
            for relocation in headers:
                if relocation[1] not in (4, 9) or relocation[7] != section:
                    continue
                entry_size = 12 if relocation[1] == 4 else 8
                require(relocation[9] == entry_size and relocation[5] % entry_size == 0,
                        'Invalid relocation table')
                for pos in range(relocation[4], relocation[4] + relocation[5], entry_size):
                    address = struct.unpack_from('<I', data, pos)[0]
                    require(not value <= address < value + size,
                            f'Unresolved relocation in probe {symbol}')
            require(symbol not in functions, f'Duplicate function symbol: {symbol}')
            functions[symbol] = data[header[4] + value:header[4] + value + size]
    return info.get('comments', []), functions


def reference_probes(config):
    data = original_boot()
    loads = elf_info(data)['load_segments']
    expected = {}
    for probe in config['probes']:
        address, size = probe['address'], probe['size']
        segment = next((load for load in loads if load['address'] <= address
                        and address + size <= load['address'] + load['file_size']), None)
        require(segment is not None, f"Probe outside loaded data: {probe['symbol']}")
        offset = segment['offset'] + address - segment['address']
        raw = data[offset:offset + size]
        require(sha256(raw) == probe['sha256'], f"Target probe hash mismatch: {probe['symbol']}")
        expected[probe['symbol']] = raw
    return data, expected


def check(config, records, matrix):
    original, expected = reference_probes(config)
    RESULTS.mkdir(parents=True, exist_ok=True)
    report = {'schema_version': 1, 'status': config['status'], 'boot_sha256': sha256(original),
              'source_sha256': sha256((ROOT / config['source']).read_bytes()),
              'comparison': 'Exact complete function bytes and lengths; no relocation masking.',
              'results': []}
    flags_to_check = config['matrix_flags'] if matrix else [config['working_flags']]
    for record in records:
        compiler = COMPILERS / record['id']
        verify_compiler(record, compiler)
        version = subprocess.run(['wibo', str(compiler / 'mwccps2.exe'), '-version'],
                                 capture_output=True, text=True, check=True)
        for flags in flags_to_check:
            name = record['id'] + '-' + '-'.join(flags).replace(',', '-')
            output = RESULTS / (name + '.o')
            command = ['wibo', str(compiler / 'mwccps2.exe'), '-c', *flags,
                       '-o', str(output), config['source']]
            subprocess.run(command, check=True, capture_output=True, text=True)
            comments, functions = object_functions(output.read_bytes())
            comparisons = []
            for probe in config['probes']:
                symbol = probe['symbol']
                require(symbol in functions, f'Missing compiled probe: {symbol}')
                actual, target = functions[symbol], expected[symbol]
                comparisons.append({'symbol': symbol, 'address': probe['address'],
                                    'expected_size': len(target), 'actual_size': len(actual),
                                    'expected_sha256': sha256(target), 'actual_sha256': sha256(actual),
                                    'match': actual == target})
            matched = sum(item['match'] for item in comparisons)
            report['results'].append({'candidate': record['id'], 'flags': flags,
                                      'compiler_sha256': record['files']['mwccps2.exe'],
                                      'version': (version.stdout + version.stderr).strip(),
                                      'object_comments': comments, 'matched': matched,
                                      'probes': comparisons})
            if not matrix or matched == len(expected):
                print(f"{record['id']} {' '.join(flags)}: {matched}/{len(expected)} exact probes", flush=True)
    report['all_matching_configurations'] = [
        {'candidate': row['candidate'], 'flags': row['flags']} for row in report['results']
        if row['matched'] == len(expected)]
    path = RESULTS / ('matrix.json' if matrix else 'report.json')
    path.write_text(json.dumps(report, indent=2) + '\n')
    print(f'Report: {path.relative_to(ROOT)}')
    require(bool(report['all_matching_configurations']), 'No tested configuration matches all probes')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=('setup', 'check'))
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument('--all', action='store_true', help='All candidates and optimization settings')
    selection.add_argument('--candidate', help='Candidate ID from config/compilers.json')
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        config = json.loads(CONFIG.read_text())
        selected = args.candidate or config['working_candidate']
        records = [r for r in config['candidates'] if args.all or r['id'] == selected]
        require(bool(records), f'Unknown compiler candidate: {selected}')
        if args.command == 'setup':
            for record in records:
                setup(record)
        else:
            check(config, records, args.all)
        return 0
    except (OSError, ValueError, KeyError, tarfile.TarError, subprocess.CalledProcessError) as error:
        print(f'error: {error}', file=sys.stderr)
        if isinstance(error, subprocess.CalledProcessError):
            print((error.stdout or '') + (error.stderr or ''), file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
