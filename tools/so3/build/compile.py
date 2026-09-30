#!/usr/bin/env python3
"""Compile one C or C++ unit with the pinned MWCC candidate and assembly placeholders."""

import argparse
import json
import os
from pathlib import Path
import subprocess
import sys

from tools.so3.build.compiler_probe import COMPILERS, CONFIG, verify_compiler


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('output', type=Path)
    parser.add_argument('--macros', required=True, type=Path)
    parser.add_argument('--skip-asm', action='store_true',
                        help='compile only C/C++ for objdiff progress reporting')
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
    flags = ['-DSO3_ASM_PROCESSOR', f'-I{args.source.parent}', '-Iinclude',
             *config['working_flags'], '-lang', languages[args.source.suffix]]
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
        temporary.replace(args.output)
    finally:
        temporary.unlink(missing_ok=True)


if __name__ == '__main__':
    main()
