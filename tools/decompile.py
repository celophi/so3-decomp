#!/usr/bin/env python3
"""Generate an m2c draft from one verified Splat function in its matching workspace."""

import argparse
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tarfile

from analysis_tools import ROOT, LOCK, checked_file, sha256
from boot import original_boot
from build import full_asm_path
from identify_sdk import functions
from overlays import load_config
from so3.sdk import code_units


def m2c_entry():
    revision = json.loads(LOCK.read_text())['m2c_revision']
    archive = checked_file(f'tools/m2c/{revision}.tar.gz')
    # Check the extracted Python sources too; the archive alone does not pin execution.
    with tarfile.open(archive) as source:
        for member in source.getmembers():
            if member.isfile():
                path = archive.parent / member.name
                if not path.is_file() or path.read_bytes() != source.extractfile(member).read():
                    raise ValueError(f'{path}: changed; run make m2c')
    return archive.parent / f'm2c-{revision}/m2c.py', revision


def function_input(config, original, name):
    found = []
    for unit in code_units(config):
        assembly = full_asm_path(config['options'], Path(unit['source']))
        if not assembly.is_file():
            raise ValueError(f'{assembly}: missing; run make split')
        text = assembly.read_text()
        if f'glabel {name}\n' not in text:
            continue
        matches = [f for f, _ in functions(assembly, original, unit['start'], unit['end'],
                                          unit['base']) if f['name'] == name]
        if len(matches) != 1:
            raise ValueError(f'{assembly}: ambiguous or missing function extent: {name}')
        # Exclude alignment padding after endlabel, but retain labels and delay slots.
        match = re.search(rf'^nonmatching {re.escape(name)}, 0x[0-9a-fA-F]+$.*?'
                          rf'^endlabel {re.escape(name)}$', text, re.M | re.S)
        if match is None:
            raise ValueError(f'{assembly}: cannot extract {name}')
        found.append(({**matches[0], 'source': unit['source'], 'assembly': str(assembly)},
                      '.set noat\n.set noreorder\n' + match[0] + '\n'))
    if len(found) != 1:
        raise ValueError(f'expected one configured function named {name}; found {len(found)}')
    return found[0]


def reserve_run(function, module):
    parent = ROOT / 'working/matching' / function / module / 'm2c'
    parent.mkdir(parents=True, exist_ok=True)
    for i in range(1, 10000):
        out = parent / f'run-{i:03d}'
        try:
            out.mkdir()
            return out
        except FileExistsError:
            continue
    raise ValueError(f'{parent}: too many runs')


def decompile(module, function, context=None, language=None):
    if not re.fullmatch(r'boot|[0-9]{4}-[0-9]{2}', module):
        raise ValueError('module must be boot or an overlay ID such as 1070-00')
    if not re.fullmatch(r'[A-Za-z_][\w.$]*', function):
        raise ValueError('invalid function name')
    if module == 'boot':
        import yaml
        config = yaml.safe_load((ROOT / 'config/boot.us.yaml').read_text())
        original = original_boot()
    else:
        config, original = load_config(Path('config/overlays') / (module + '.yaml'))
    identity, assembly = function_input(config, original, function)
    entry, revision = m2c_entry()
    context_bytes = context.read_bytes() if context else None
    language = language or ('c++' if identity['source'].endswith('.cpp') else 'c')
    if language not in ('c', 'c++'):
        raise ValueError('language must be c or c++')
    target = 'mipsee-mwcc-' + language
    out = reserve_run(function, module)
    (out / 'target.s').write_text(assembly)
    command = [sys.executable, str(entry), '--target', target, '--no-cache']
    if context_bytes is not None:
        (out / 'context.h').write_bytes(context_bytes)
        command.extend(['--context', str(out / 'context.h')])
    command.append(str(out / 'target.s'))
    result = subprocess.run(command, capture_output=True, text=True)
    suffix = 'cpp' if language == 'c++' else 'c'
    (out / f'draft.{suffix}').write_text(result.stdout)
    (out / 'stderr.txt').write_text(result.stderr)
    metadata = {**identity, 'module': module, 'binary': config['options']['target_path'],
                'binary_sha256': sha256(original), 'm2c_revision': revision, 'target': target,
                'assembly_sha256': sha256(assembly.encode()),
                'context_sha256': sha256(context_bytes) if context_bytes is not None else None,
                'command': command, 'exit_code': result.returncode,
                'status': 'draft' if result.returncode == 0 else 'failed'}
    (out / 'run.json').write_text(json.dumps(metadata, indent=2) + '\n')
    print(out.relative_to(ROOT))
    if result.returncode:
        raise ValueError(f'm2c failed; see {out.relative_to(ROOT)} for output and stderr')
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('module', help='boot or an overlay ID, e.g. 1070-00')
    parser.add_argument('function', help='exact Splat symbol name')
    parser.add_argument('--context', type=Path, help='preprocessed C declarations and types')
    parser.add_argument('--language', choices=('c', 'c++'), help='override the configured source language')
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        decompile(args.module, args.function, args.context, args.language)
        return 0
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
