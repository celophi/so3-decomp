#!/usr/bin/env python3
"""Compile one C or C++ unit with the pinned MWCC candidate and assembly placeholders."""

import argparse
import json
import os
from pathlib import Path
import subprocess
import sys

from tools.so3.build.compiler_probe import COMPILERS, CONFIG, verify_compiler
from tools.so3.build.assembly import assembly_inputs, assemble
from tools.so3.build.rodata_ownership import owned_rodata_sections
from tools.so3.build.subsegments import configured_rodata_groups
from tools.so3.build.text_order import merge_rodata_sections, normalize_symbol_aliases, order_text_sections, symbol_addresses, symbol_aliases, unit_range


def unit_flags(config, unit):
    """Return the working flags plus any flags configured for one source unit."""
    extra = [entry['flags'] for entry in config.get('unit_flags', []) if Path(entry['source']) == Path(unit)]
    if len(extra) > 1:
        raise ValueError(f'{unit} has more than one unit_flags entry')
    return [*config['working_flags'], *(extra[0] if extra else [])]


def deferred(flags):
    """Whether -inline selects deferred code generation."""
    return any(a == '-inline' and 'deferred' in b.split(',') for a, b in zip(flags, flags[1:]))


def module_of(unit):
    parts = Path(unit).parts
    return parts[2] if parts[:2] == ('src', 'overlays') else 'main'


def symbol_map(unit):
    """The Splat symbol map for the module that owns a source unit."""
    path = Path('config/symbols') / f'{module_of(unit)}_symbol_addrs.txt'
    return symbol_addresses(path) if path.is_file() else {}


def thunk_map(unit):
    """Original addresses of the kept copies of MWCC this-adjusting thunks."""
    path = Path('config/thunks') / f'{module_of(unit)}_thunk_addrs.txt'
    return symbol_addresses(path) if path.is_file() else {}


def external_copies(unit):
    """Inline-function copies whose kept copy is outside every available image."""
    path = Path('config/copies') / f'{module_of(unit)}_external_copies.txt'
    if not path.is_file():
        return set()
    lines = (line.split('//', 1)[0].strip() for line in path.read_text().splitlines())
    return {line for line in lines if line}


def overlay_config(unit):
    """The owning overlay's Splat configuration, or None for main sources."""
    module = module_of(unit)
    if module == 'main':
        return None
    import yaml
    return yaml.safe_load((Path('config/overlays') / f'{module}.yaml').read_text())


def overlay_range(unit):
    """The unit's VRAM range, or None for main sources."""
    config = overlay_config(unit)
    return unit_range(config, unit) if config else None


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
    os.environ['MWCIncludes'] = ''
    args.output.parent.mkdir(parents=True, exist_ok=True)
    temporary = args.output.with_suffix(args.output.suffix + '.tmp')
    unit = args.unit or args.source
    selected = unit_flags(config, unit)
    flags = ['-DSO3_ASM_PROCESSOR', f'-I{args.source.parent}', '-Iinclude',
             *selected, '-lang', languages[args.source.suffix]]
    config = overlay_config(unit)
    groups = configured_rodata_groups(config, unit) if config else []
    # Pure C scaffolds have no compiler-generated code or metadata. Deferred
    # units and C++ still use the compiler's section ordering and copy handling.
    assembly = (assembly_inputs(args.source)
                if not args.skip_asm and languages[args.source.suffix] == 'c'
                and not deferred(selected) and not groups else None)
    try:
        if assembly:
            assemble(assembly, args.macros, temporary)
        elif args.skip_asm:
            # include_asm.h expands the placeholders to nothing. Keep these
            # objects separate so copied assembly cannot inflate progress.
            subprocess.run(['wibo', str(compiler / 'mwccps2.exe'), '-c', *flags,
                            '-o', str(temporary), str(args.source)], check=True)
        else:
            # Installed at a hash-pinned revision, with dockerfiles/patches/mwccgap.patch applied.
            sys.path.insert(0, '/opt/mwccgap')
            from mwccgap.mwccgap import process_c_file
            process_c_file(
                args.source, temporary,
                # mwccgap's second pass uses a temporary .c file, even for C++.
                flags,
                mwcc_path=compiler / 'mwccps2.exe', use_wibo=True,
                as_path='mips-ps2-decompals-as', as_march='r5900', as_mabi='eabi',
                as_flags=['-no-pad-sections'], macro_inc_path=args.macros,
                temp_dir=args.output.parent,
            )
        # Deferred codegen reverses C functions but not mwccgap's asm stubs, so
        # deferred units are put back in address order. Every C++ unit keeps
        # only the thunk copies the original linker kept inside it.
        if deferred(selected) or languages[args.source.suffix] == 'c++':
            temporary.write_bytes(order_text_sections(
                temporary.read_bytes(), symbol_map(unit), thunk_map(unit),
                overlay_range(unit), reorder=deferred(selected), external=external_copies(unit)))
        # Preserve separate native islands when a unit owns noncontiguous tables.
        # Other units retain the original single-section jump-table comparison.
        if groups:
            data, _ = owned_rodata_sections(temporary.read_bytes(), groups)
        else:
            data = merge_rodata_sections(temporary.read_bytes())
        temporary.write_bytes(data)
        aliases_path = Path('config/symbols') / f'{module_of(unit)}_symbol_addrs.txt'
        if aliases_path.is_file():
            temporary.write_bytes(normalize_symbol_aliases(temporary.read_bytes(), symbol_aliases(aliases_path)))
        temporary.replace(args.output)
    finally:
        temporary.unlink(missing_ok=True)


if __name__ == '__main__':
    main()
