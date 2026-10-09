#!/usr/bin/env python3
"""Download the candidate compilers and check which ones can build the game.

I don't know exactly which CodeWarrior compiler (MWCC) build or flags the game
was made with. config/manifests/compilers.json lists the builds I'm
considering, each pinned by hash, plus a few small functions from the main
executable that I use to test them. I call those functions probes, and their
source is in tools/so3/build/probes/main.c.

- `setup` downloads a compiler and checks every file against its hash. The
  build runs this for the working compiler before it compiles anything.
- `check` compiles the probes with the working compiler and flags, and
  compares each function byte for byte with the original. With --all it tries
  every candidate at every optimisation level. That's how I narrowed down the
  working one.

Reports go to build/compiler-probes/. The probes don't call or reference
anything outside themselves, so there are no relocations to mask and the
comparison can be exact.
"""

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

from tools.so3.build.main import ROOT, original_main, sha256
from tools.so3.build.elf import (ET_REL, REL, SHT_PROGBITS, SHT_REL, SHT_RELA, SHT_SYMTAB, STT_FUNC, SYMBOL,
                                 Symbol, section_headers, symbol_type)
from tools.so3.formats import elf_info, require

CONFIG = ROOT / 'config/manifests/compilers.json'
COMPILERS = ROOT / 'build/compilers'
RESULTS = ROOT / 'build/compiler-probes'
REPORT = RESULTS / 'report.json'
MATRIX_REPORT = RESULTS / 'matrix.json'
REPORT_SCHEMA_VERSION = 1

COMPILER_EXE = 'mwccps2.exe'
LINKER_EXE = 'mwldps2.exe'
DOWNLOAD_TIMEOUT_SECONDS = 60

# A RELA entry has an extra addend word on the end of a REL entry.
RELOCATION_SIZE = {SHT_REL: REL.size, SHT_RELA: REL.size + 4}


def working_candidate(config):
    """The manifest entry for the compiler the build uses."""
    return next(record for record in config['candidates'] if record['id'] == config['working_candidate'])


def verify_compiler(record, directory):
    """Check every file of a compiler against the hashes in the manifest."""
    for name, expected in record['files'].items():
        require(sha256((directory / name).read_bytes()) == expected,
                f"Compiler file hash mismatch: {record['id']}/{name}")


def setup(record):
    """Download and unpack one compiler, unless it's already here and intact."""
    directory = COMPILERS / record['id']
    if directory.exists():
        verify_compiler(record, directory)
        print(f"Verified {record['id']}")
        return
    COMPILERS.mkdir(parents=True, exist_ok=True)
    print(f"Downloading {record['id']}", flush=True)
    with urllib.request.urlopen(record['url'], timeout=DOWNLOAD_TIMEOUT_SECONDS) as response:
        archive = response.read()
    require(sha256(archive) == record['archive_sha256'],
            f"Archive hash mismatch: {record['id']}")
    # I only copy out the files the manifest names, instead of extracting the
    # whole archive, so a strange path inside it can't write anywhere else.
    # Everything gets checked in a staging folder first, so a failed download
    # never leaves a half-finished compiler behind.
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


def symbols(data, table):
    for offset in range(table.offset, table.offset + table.size, SYMBOL.size):
        yield Symbol(*SYMBOL.unpack_from(data, offset))


def require_no_relocations(data, headers, function, name):
    """Fail if anything inside the function still needs a relocation.

    A relocation means those bytes aren't final until link time, so comparing
    them with the original wouldn't tell me anything.
    """
    for table in headers:
        # A relocation table's sh_info is the section it applies to.
        if table.type not in RELOCATION_SIZE or table.info != function.section:
            continue
        entry_size = RELOCATION_SIZE[table.type]
        require(table.entry_size == entry_size and table.size % entry_size == 0,
                'Invalid relocation table')
        for entry in range(table.offset, table.offset + table.size, entry_size):
            address = struct.unpack_from('<I', data, entry)[0]
            require(not function.value <= address < function.value + function.size,
                    f'Unresolved relocation in probe {name}')


def object_functions(data):
    """Return an object's .comment strings and the bytes of each function in it.

    MWCC can put each function in its own section, and they're all called
    .text. So I find each function through its symbol's section index instead
    of by section name.
    """
    info = elf_info(data)
    require(info['elf_type'] == ET_REL, 'Expected a relocatable ELF object')
    headers = section_headers(data)
    functions = {}
    for table in headers:
        if table.type != SHT_SYMTAB:
            continue
        require(table.entry_size == SYMBOL.size and table.size % SYMBOL.size == 0 and table.link < len(headers),
                'Invalid ELF symbol table')
        # A symbol table's sh_link is the string table that holds its names.
        names = headers[table.link]
        strings = data[names.offset:names.offset + names.size]
        for symbol in symbols(data, table):
            if symbol_type(symbol.info) != STT_FUNC:
                continue
            require(0 < symbol.section < len(headers), 'Invalid function section')
            section = headers[symbol.section]
            require(section.type == SHT_PROGBITS and symbol.value + symbol.size <= section.size,
                    'Function exceeds section')
            require(symbol.name < len(strings), 'Invalid function name')
            name = strings[symbol.name:].split(b'\0', 1)[0].decode('ascii')
            require_no_relocations(data, headers, symbol, name)
            require(name not in functions, f'Duplicate function symbol: {name}')
            start = section.offset + symbol.value
            functions[name] = data[start:start + symbol.size]
    return info.get('comments', []), functions


def reference_probes(config):
    """Read each probe function's original bytes out of the main executable."""
    data = original_main()
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


def compiler_version(compiler):
    version = subprocess.run(['wibo', str(compiler / COMPILER_EXE), '-version'],
                             capture_output=True, text=True, check=True)
    return (version.stdout + version.stderr).strip()


def compile_probes(compiler, flags, source, output):
    subprocess.run(['wibo', str(compiler / COMPILER_EXE), '-c', *flags, '-o', str(output), source],
                   check=True, capture_output=True, text=True)


def object_name(record, flags):
    """A file name for one compiler and set of flags, like mwcps2-3.0b38-030307--O3-p."""
    return record['id'] + '-' + '-'.join(flags).replace(',', '-').replace('=', '-')


def compare_probes(probes, expected, functions):
    comparisons = []
    for probe in probes:
        symbol = probe['symbol']
        require(symbol in functions, f'Missing compiled probe: {symbol}')
        actual, target = functions[symbol], expected[symbol]
        comparisons.append({'symbol': symbol, 'address': probe['address'],
                            'expected_size': len(target), 'actual_size': len(actual),
                            'expected_sha256': sha256(target), 'actual_sha256': sha256(actual),
                            'match': actual == target})
    return comparisons


def check(config, records, matrix):
    """Compile the probes with each compiler and write a report of what matched.

    Fails if no compiler and flags match every probe.
    """
    original, expected = reference_probes(config)
    RESULTS.mkdir(parents=True, exist_ok=True)
    report = {'schema_version': REPORT_SCHEMA_VERSION, 'status': config['status'], 'boot_sha256': sha256(original),
              'source_sha256': sha256((ROOT / config['source']).read_bytes()),
              'comparison': 'Exact complete function bytes and lengths; no relocation masking.',
              'results': []}
    flags_to_check = config['matrix_flags'] if matrix else [config['working_flags']]
    for record in records:
        compiler = COMPILERS / record['id']
        verify_compiler(record, compiler)
        version = compiler_version(compiler)
        for flags in flags_to_check:
            output = RESULTS / f'{object_name(record, flags)}.o'
            compile_probes(compiler, flags, config['source'], output)
            comments, functions = object_functions(output.read_bytes())
            comparisons = compare_probes(config['probes'], expected, functions)
            matched = sum(item['match'] for item in comparisons)
            report['results'].append({'candidate': record['id'], 'flags': flags,
                                      'compiler_sha256': record['files'][COMPILER_EXE],
                                      'version': version,
                                      'object_comments': comments, 'matched': matched,
                                      'probes': comparisons})
            # The full matrix is long, so it only prints the ones that match.
            if not matrix or matched == len(expected):
                print(f"{record['id']} {' '.join(flags)}: {matched}/{len(expected)} exact probes", flush=True)
    report['all_matching_configurations'] = [
        {'candidate': row['candidate'], 'flags': row['flags']} for row in report['results']
        if row['matched'] == len(expected)]
    path = MATRIX_REPORT if matrix else REPORT
    path.write_text(json.dumps(report, indent=2) + '\n')
    print(f'Report: {path.relative_to(ROOT)}')
    require(bool(report['all_matching_configurations']), 'No tested configuration matches all probes')


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('command', choices=('setup', 'check'))
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument('--all', action='store_true', help='All candidates and optimization settings')
    selection.add_argument('--candidate', help='Candidate ID from config/manifests/compilers.json')
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        config = json.loads(CONFIG.read_text())
        selected = args.candidate or config['working_candidate']
        records = [record for record in config['candidates'] if args.all or record['id'] == selected]
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
