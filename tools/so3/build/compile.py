#!/usr/bin/env python3
"""Compile one game source file into an object the build can link.

Most source files are still a mix of decompiled functions and INCLUDE_ASM
placeholders for the ones I haven't done yet. This script turns any of them
into an object file with the pinned Metrowerks compiler (MWCC):

- A C file that only has placeholders doesn't need the compiler at all, so I
  assemble its functions directly.
- Everything else goes through mwccgap, which compiles the file and then swaps
  the original assembly in for each placeholder.
- With --skip-asm the placeholders compile to nothing. objdiff uses those
  objects to measure progress, so copied assembly can't count as decompiled.

Afterwards I clean up the object so it lines up with the original layout. That
part is explained next to each step below.
"""

import argparse
import json
import os
from pathlib import Path
import subprocess
import sys

from tools.so3.build.compiler_probe import COMPILERS, CONFIG, verify_compiler
from tools.so3.build.assembly import ASSEMBLER, ASSEMBLER_ABI, ASSEMBLER_CPU, ASSEMBLER_FLAGS, assembly_inputs, assemble
from tools.so3.build.rodata_ownership import owned_rodata_sections
from tools.so3.build.subsegments import configured_rodata_groups
from tools.so3.build.text_order import merge_rodata_sections, normalize_symbol_aliases, order_text_sections, symbol_addresses, symbol_aliases, unit_range

LANGUAGES = {'.c': 'c', '.cpp': 'c++'}

# Per-module configuration, each named after the module (e.g. citemcreation).
SYMBOL_MAPS = Path('config/symbols')
THUNK_MAPS = Path('config/thunks')
EXTERNAL_COPY_LISTS = Path('config/copies')
OVERLAY_CONFIGS = Path('config/overlays')

# include/include_asm.h refuses to compile unless this is defined, so game
# sources can only be built through this script.
ASM_PROCESSOR_DEFINE = '-DSO3_ASM_PROCESSOR'

COMPILER_EXE = 'mwccps2.exe'

# The dev image installs mwccgap here with dockerfiles/patches/mwccgap.patch applied.
MWCCGAP_DIR = '/opt/mwccgap'


def unit_flags(config, unit):
    """Return the working flags plus any flags configured for one source unit."""
    extra = [entry['flags'] for entry in config.get('unit_flags', []) if Path(entry['source']) == Path(unit)]
    if len(extra) > 1:
        raise ValueError(f'{unit} has more than one unit_flags entry')
    return [*config['working_flags'], *(extra[0] if extra else [])]


def deferred(flags):
    """Whether the flags turn on deferred code generation (`-inline ...,deferred`)."""
    return any(flag == '-inline' and 'deferred' in value.split(',') for flag, value in zip(flags, flags[1:]))


def module_of(unit):
    """The module a source file belongs to: its overlay folder, or 'main'."""
    parts = Path(unit).parts
    return parts[2] if parts[:2] == ('src', 'overlays') else 'main'


def symbol_map_path(unit):
    return SYMBOL_MAPS / f'{module_of(unit)}_symbol_addrs.txt'


def symbol_map(unit):
    """The Splat symbol map for the module that owns a source unit."""
    path = symbol_map_path(unit)
    return symbol_addresses(path) if path.is_file() else {}


def thunk_map(unit):
    """Original addresses of the copies of MWCC's this-adjusting thunks that the game kept."""
    path = THUNK_MAPS / f'{module_of(unit)}_thunk_addrs.txt'
    return symbol_addresses(path) if path.is_file() else {}


def external_copies(unit):
    """Inline-function copies whose kept copy isn't in any image we have (one name per line, // comments)."""
    path = EXTERNAL_COPY_LISTS / f'{module_of(unit)}_external_copies.txt'
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
    return yaml.safe_load((OVERLAY_CONFIGS / f'{module}.yaml').read_text())


def overlay_range(unit):
    """The unit's VRAM range, or None for main sources."""
    config = overlay_config(unit)
    return unit_range(config, unit) if config else None


def working_compiler(config):
    """Find the compiler I'm currently using, and check that it's the one I expect."""
    compiler = next(entry for entry in config['candidates'] if entry['id'] == config['working_candidate'])
    path = COMPILERS / compiler['id']
    verify_compiler(compiler, path)
    return path / COMPILER_EXE


def compile_with_mwccgap(source, output, flags, compiler, macros):
    sys.path.insert(0, MWCCGAP_DIR)
    from mwccgap.mwccgap import process_c_file
    # mwccgap writes its second pass to a temporary .c file even for C++, so I
    # keep those files next to the output instead of in the source tree.
    process_c_file(
        source, output, flags,
        mwcc_path=compiler, use_wibo=True,
        as_path=ASSEMBLER, as_march=ASSEMBLER_CPU, as_mabi=ASSEMBLER_ABI,
        as_flags=ASSEMBLER_FLAGS, macro_inc_path=macros,
        temp_dir=output.parent,
    )


def match_original_layout(path, unit, unit_options, language, rodata_groups):
    """Rewrite the object's sections so they line up with the original game."""
    data = path.read_bytes()

    # With deferred code generation MWCC writes C functions in reverse order,
    # but mwccgap's assembly stubs stay where they are, so I sort the functions
    # back into address order. For C++ this also drops the extra copies of
    # thunks and inline functions that the original linker didn't keep here.
    if deferred(unit_options) or language == 'c++':
        data = order_text_sections(data, symbol_map(unit), thunk_map(unit), overlay_range(unit),
                                   reorder=deferred(unit_options), external=external_copies(unit))

    # MWCC gives every jump table its own .rodata section. Usually I merge them
    # into one so objdiff can compare them, but a few units own tables that sit
    # in separate places in the original, and those keep their own sections.
    if rodata_groups:
        data, _ = owned_rodata_sections(data, rodata_groups)
    else:
        data = merge_rodata_sections(data)

    # Rename references that use an alias so they match the symbol map's name.
    aliases = symbol_map_path(unit)
    if aliases.is_file():
        data = normalize_symbol_aliases(data, symbol_aliases(aliases))

    path.write_bytes(data)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('source', type=Path)
    parser.add_argument('output', type=Path)
    parser.add_argument('--macros', required=True, type=Path)
    parser.add_argument('--skip-asm', action='store_true',
                        help='compile only C/C++ for objdiff progress reporting')
    parser.add_argument('--unit', type=Path,
                        help='production source whose unit_flags apply (default: the source itself)')
    args = parser.parse_args()
    if args.source.suffix not in LANGUAGES:
        parser.error('source must use .c (C) or .cpp (C++)')
    language = LANGUAGES[args.source.suffix]

    compilers = json.loads(CONFIG.read_text())
    compiler = working_compiler(compilers)
    # MWCC also searches the folders in MWCIncludes. I clear it so it only
    # sees the include paths I pass.
    os.environ['MWCIncludes'] = ''

    unit = args.unit or args.source
    unit_options = unit_flags(compilers, unit)
    flags = [ASM_PROCESSOR_DEFINE, f'-I{args.source.parent}', '-Iinclude', *unit_options, '-lang', language]

    # A probe built with --unit only has some of the unit's functions, so it
    # can't own the unit's separately placed jump tables.
    overlay = overlay_config(unit)
    whole_unit = Path(unit).resolve() == args.source.resolve()
    rodata_groups = configured_rodata_groups(overlay, unit) if overlay and whole_unit else []

    # Only a C file with nothing but placeholders can skip the compiler.
    # Deferred units and C++ still need the compiler's section order and copies.
    assembly = None
    if not args.skip_asm and language == 'c' and not deferred(unit_options) and not rodata_groups:
        assembly = assembly_inputs(args.source)

    args.output.parent.mkdir(parents=True, exist_ok=True)
    # Write to a temporary file first so a failed step never leaves a half-made object behind.
    temporary = args.output.with_suffix(args.output.suffix + '.tmp')
    try:
        if assembly:
            assemble(assembly, args.macros, temporary)
        elif args.skip_asm:
            subprocess.run(['wibo', str(compiler), '-c', *flags, '-o', str(temporary), str(args.source)], check=True)
        else:
            compile_with_mwccgap(args.source, temporary, flags, compiler, args.macros)
        match_original_layout(temporary, unit, unit_options, language, rodata_groups)
        temporary.replace(args.output)
    finally:
        temporary.unlink(missing_ok=True)


if __name__ == '__main__':
    main()
