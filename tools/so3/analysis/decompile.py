#!/usr/bin/env python3
"""Make a first C or C++ draft of one function with m2c.

m2c is a decompiler: it reads a function's assembly and writes C that does
roughly the same thing. The draft almost never matches straight away, but it's
a much better start than a blank file. Run it with `make decompile`:

    make decompile MODULE=1070-00 FUNCTION=func_00288650 [CONTEXT=working/context.h] [LANGUAGE=c++]

I take the function out of Splat's assembly for its unit, after checking every
instruction against the original, and give it to the pinned m2c. Each run gets
a new folder, working/matching/<function>/<module>/m2c/run-001 and so on, so
a rerun never overwrites a draft I've already started editing. The folder has:

- target.s, the assembly m2c read,
- draft.c or draft.cpp, and m2c's stderr.txt,
- context.h, if I passed one with the types and declarations m2c should know,
- run.json, which records exactly what went in, so the draft can be traced back.
"""

import argparse
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tarfile

from tools.so3.analysis.analysis_tools import LOCK, ROOT, checked_file, sha256
from tools.so3.analysis.identify_sdk import functions
from tools.so3.build.driver import full_asm_path
from tools.so3.build.main import MAIN_CONFIG
from tools.so3.build.overlays import CONFIGS, OVERLAY_NAME, load_module
from tools.so3.build.sdk import code_units

MATCHING = Path('working/matching')
MAX_RUNS = 9999  # Runs are numbered from run-001.

# m2c's target names the CPU, the compiler, and the language.
M2C_TARGET = 'mipsee-mwcc-{language}'
SOURCE_SUFFIXES = {'c': 'c', 'c++': 'cpp'}

# Splat's assembly sets these at the top of the file. A single function cut out
# of it needs them too: $at is used like any other register, and branch delay
# slots are written out as they are.
ASSEMBLY_PRELUDE = '.set noat\n.set noreorder\n'

FUNCTION_NAME = re.compile(r'[A-Za-z_][\w.$]*')


def m2c_entry():
    """Find the pinned m2c, and check nobody has edited its extracted files."""
    revision = json.loads(LOCK.read_text())['m2c_revision']
    archive = checked_file(f'tools/m2c/{revision}.tar.gz')
    # The archive's hash alone doesn't pin what actually runs, so I compare
    # every extracted file with the archive too.
    with tarfile.open(archive) as source:
        for member in source.getmembers():
            if member.isfile():
                path = archive.parent / member.name
                if not path.is_file() or path.read_bytes() != source.extractfile(member).read():
                    raise ValueError(f'{path}: changed; run make m2c')
    return archive.parent / f'm2c-{revision}/m2c.py', revision


def function_input(config, original, name):
    """Find a function in the module and cut its assembly out of Splat's output.

    Returns its details (address, size, hash, source file) and the assembly
    to give m2c. The name has to match exactly one function in the module.
    """
    found = []
    for unit in code_units(config):
        assembly = full_asm_path(config['options'], Path(unit['source']))
        if not assembly.is_file():
            raise ValueError(f'{assembly}: missing; run make split')
        text = assembly.read_text()
        if f'glabel {name}\n' not in text:
            continue
        # Reading the unit through identify_sdk.functions checks every
        # instruction against the original bytes.
        matches = [function for function, _ in functions(assembly, original, unit['start'], unit['end'], unit['base'])
                   if function['name'] == name]
        if len(matches) != 1:
            raise ValueError(f'{assembly}: ambiguous or missing function extent: {name}')
        # Stop at endlabel, so the alignment padding after the function is left
        # out but the last delay slot stays in.
        match = re.search(rf'^nonmatching {re.escape(name)}, 0x[0-9a-fA-F]+$.*?'
                          rf'^endlabel {re.escape(name)}$', text, re.M | re.S)
        if match is None:
            raise ValueError(f'{assembly}: cannot extract {name}')
        found.append(({**matches[0], 'source': unit['source'], 'assembly': str(assembly)},
                      ASSEMBLY_PRELUDE + match[0] + '\n'))
    if len(found) != 1:
        raise ValueError(f'expected one configured function named {name}; found {len(found)}')
    return found[0]


def reserve_run(function, module):
    """Create the next free run-NNN folder for this function."""
    parent = ROOT / MATCHING / function / module / 'm2c'
    parent.mkdir(parents=True, exist_ok=True)
    for number in range(1, MAX_RUNS + 1):
        folder = parent / f'run-{number:03d}'
        try:
            # mkdir fails if the folder exists, so two runs at once can't take the same number.
            folder.mkdir()
            return folder
        except FileExistsError:
            continue
    raise ValueError(f'{parent}: too many runs')


def module_config_path(module):
    return MAIN_CONFIG if module == 'main' else CONFIGS / f'{module}.yaml'


def check_names(module, function):
    if not OVERLAY_NAME.fullmatch(module):
        raise ValueError('module must be main or an overlay name such as lib or 1070-00')
    if not FUNCTION_NAME.fullmatch(function):
        raise ValueError('invalid function name')


def m2c_command(entry, target, folder, has_context):
    command = [sys.executable, str(entry), '--target', target, '--no-cache']
    if has_context:
        command += ['--context', str(folder / 'context.h')]
    return [*command, str(folder / 'target.s')]


def decompile(module, function, context=None, language=None):
    """Write an m2c draft of one function into a new run folder, and return the folder."""
    check_names(module, function)
    config, original = load_module(ROOT / module_config_path(module))
    identity, assembly = function_input(config, original, function)
    entry, revision = m2c_entry()
    context_bytes = context.read_bytes() if context else None
    # Unless I say otherwise, the draft is in the same language as the function's source file.
    language = language or ('c++' if identity['source'].endswith('.cpp') else 'c')
    if language not in SOURCE_SUFFIXES:
        raise ValueError('language must be c or c++')
    target = M2C_TARGET.format(language=language)

    folder = reserve_run(function, module)
    (folder / 'target.s').write_text(assembly)
    if context_bytes is not None:
        (folder / 'context.h').write_bytes(context_bytes)
    command = m2c_command(entry, target, folder, context_bytes is not None)
    result = subprocess.run(command, capture_output=True, text=True)
    (folder / f'draft.{SOURCE_SUFFIXES[language]}').write_text(result.stdout)
    (folder / 'stderr.txt').write_text(result.stderr)
    metadata = {**identity, 'module': module, 'binary': config['options']['target_path'],
                'binary_sha256': sha256(original), 'm2c_revision': revision, 'target': target,
                'assembly_sha256': sha256(assembly.encode()),
                'context_sha256': sha256(context_bytes) if context_bytes is not None else None,
                'command': command, 'exit_code': result.returncode,
                'status': 'draft' if result.returncode == 0 else 'failed'}
    (folder / 'run.json').write_text(json.dumps(metadata, indent=2) + '\n')
    print(folder.relative_to(ROOT))
    if result.returncode:
        raise ValueError(f'm2c failed; see {folder.relative_to(ROOT)} for output and stderr')
    return folder


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('module', help='main or an overlay name, e.g. lib or 1070-00')
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
