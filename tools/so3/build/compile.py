#!/usr/bin/env python3
"""Compile one C or C++ unit with the pinned MWCC candidate and assembly placeholders."""

import argparse
import json
import os
from pathlib import Path
import subprocess
import sys

from tools.so3.build.compiler_probe import COMPILERS, CONFIG, verify_compiler
from tools.so3.build.text_order import order_text_sections, symbol_addresses


def unit_flags(config, unit):
    """Return the working flags plus any flags configured for one source unit."""
    extra = [entry['flags'] for entry in config.get('unit_flags', []) if Path(entry['source']) == Path(unit)]
    if len(extra) > 1:
        raise ValueError(f'{unit} has more than one unit_flags entry')
    return [*config['working_flags'], *(extra[0] if extra else [])]


def deferred(flags):
    """Whether -inline selects deferred code generation."""
    return any(a == '-inline' and 'deferred' in b.split(',') for a, b in zip(flags, flags[1:]))


def symbol_map(unit):
    """The Splat symbol map for the module that owns a source unit."""
    parts = Path(unit).parts
    module = parts[2] if parts[:2] == ('src', 'overlays') else 'boot'
    path = Path('config') / f'symbols.{module}.txt'
    return symbol_addresses(path) if path.is_file() else {}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('output', type=Path)
    parser.add_argument('--macros', required=True, type=Path)
    parser.add_argument('--skip-asm', action='store_true',
                        help='compile only C/C++ for objdiff progress reporting')
    parser.add_argument('--unit', type=Path,
                        help='production source whose unit_flags apply (default: the source itself)')
    args = parser.parse_args()
    languages = {'.c': 'c', '.cpp': 'c++'}
    if args.source.suffix not in languages:
        parser.error('source must use .c (C) or .cpp (C++)')
    config = json.loads(CONFIG.read_text())
    record = next(r for r in config['candidates'] if r['id'] == config['working_candidate'])
    compiler = COMPILERS / record['id']
    verify_compiler(record, compiler)
    # Installed at a hash-pinned revision, with dockerfiles/mwccgap.patch applied.
    sys.path.insert(0, '/opt/mwccgap')
    from mwccgap.mwccgap import process_c_file
    os.environ['MWCIncludes'] = ''
    args.output.parent.mkdir(parents=True, exist_ok=True)
    temporary = args.output.with_suffix(args.output.suffix + '.tmp')
    unit = args.unit or args.source
    selected = unit_flags(config, unit)
    flags = ['-DSO3_ASM_PROCESSOR', f'-I{args.source.parent}', '-Iinclude',
             *selected, '-lang', languages[args.source.suffix]]
    try:
        if args.skip_asm:
            # include_asm.h expands the placeholders to nothing. Keep these
            # objects separate so copied assembly cannot inflate progress.
            subprocess.run(['wibo', str(compiler / 'mwccps2.exe'), '-c', *flags,
                            '-o', str(temporary), str(args.source)], check=True)
        else:
            process_c_file(
                args.source, temporary,
                # mwccgap's second pass uses a temporary .c file, even for C++.
                flags,
                mwcc_path=compiler / 'mwccps2.exe', use_wibo=True,
                as_path='mips-ps2-decompals-as', as_march='r5900', as_mabi='eabi',
                as_flags=['-no-pad-sections'], macro_inc_path=args.macros,
                temp_dir=args.output.parent,
            )
        if deferred(selected):
            # Deferred codegen reverses C functions but not mwccgap's asm stubs;
            # restore the original layout by function address.
            temporary.write_bytes(order_text_sections(temporary.read_bytes(), symbol_map(unit)))
        temporary.replace(args.output)
    finally:
        temporary.unlink(missing_ok=True)


if __name__ == '__main__':
    main()
