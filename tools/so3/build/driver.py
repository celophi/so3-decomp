#!/usr/bin/env python3
"""Write the ninja build file and run the build.

This is what `make build` (and `python -m tools.so3.build`) runs. The game is
split into modules: the main executable, plus the overlays (code the game
loads as it needs it). Each module has a Splat config in config/, and from
those I write build/build.ninja. For every module it:

1. splits the original binary into assembly, data, and C/C++ files,
2. compiles or assembles every piece into an object,
3. links the objects back into one image, and
4. checks that the image matches the original byte for byte.

I also write objdiff.json, which tells objdiff (the progress tool) which of my
objects to compare with which original ones.

The commands:

- `split` only runs Splat.
- `build` builds and verifies every module.
- `objdiff-objects` builds the objects objdiff compares, without linking.
- `report` does both, then writes build/progress/report.json.
"""

import argparse
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from tools.so3.build.assembly import ASSEMBLER_ABI, ASSEMBLER_CPU, ASSEMBLER_FLAGS, LITTLE_ENDIAN
from tools.so3.build.compile import MWCCGAP_DIR, module_lists, thunk_map_path
from tools.so3.build.compiler_probe import COMPILERS, CONFIG, setup, working_candidate
from tools.so3.build.main import MAIN_CONFIG, ROOT, VERSIONS, original_main
from tools.so3.build.overlays import CONFIGS, load_config
from tools.so3.build.sdk import MANIFEST as SDK_MANIFEST, code_units, validate_sdk_units
from tools.so3.build.subsegments import subsegment_parts
from tools.so3.build.text_order import symbol_addresses
from tools.so3.formats import require

BUILD_FILE = Path('build/build.ninja')
OBJDIFF_CONFIG = Path('objdiff.json')
PROGRESS_OBJECTS = Path('build/progress')
PROGRESS_REPORT = PROGRESS_OBJECTS / 'report.json'
MAIN_EXECUTABLE = 'SLUS_204.88'  # The main executable's file name on the disc.
OVERLAY_IMAGE = 'rebuilt.bin'

# Every binutils tool has this prefix in the dev image, like mips-ps2-decompals-ld.
BINUTILS_PREFIX = 'mips-ps2-decompals-'
# objcopy settings that wrap a raw .bin file in an object the linker accepts.
BINARY_OBJECT_FORMAT = 'elf32-littlemips'
BINARY_ARCHITECTURE = 'mips:5900'

# How many Splat runs and compiles ninja can have going at once. Compiles get
# one per CPU, up to this many.
SPLIT_JOBS = 2
MAX_COMPILE_JOBS = 8

# This older MWCC can't list the headers a file includes (it has no -gccdep).
# So every C/C++ object depends on every project header instead, which rebuilds
# more than it needs to but never misses a change.
HEADER_FOLDERS = ('include', 'src')
HEADER_SUFFIXES = ('.h', '.hpp', '.inc')

OBJDIFF_VERSION = '3.8.2'

# The scripts and inputs each step reads. If one changes, ninja reruns the step.
SPLIT_INPUTS = ['tools/so3/build/driver.py', 'tools/so3/__init__.py', 'tools/so3/formats.py',
                'tools/so3/build/sdk.py', 'tools/so3/build/subsegments.py', str(SDK_MANIFEST)]
MAIN_SPLIT_INPUTS = ['tools/so3/build/main.py', str(VERSIONS)]
OVERLAY_SPLIT_INPUTS = ['tools/so3/build/overlays.py']
COMPILE_INPUTS = ['tools/so3/build/compile.py', 'tools/so3/build/compiler_probe.py',
                  'tools/so3/build/assembly.py', 'tools/so3/build/text_order.py',
                  'tools/so3/build/rodata_ownership.py', 'tools/so3/build/subsegments.py',
                  'tools/so3/__init__.py', 'config/manifests/compilers.json',
                  f'{MWCCGAP_DIR}/mwccgap/mwccgap.py']
ABSOLUTE_SYMBOL_INPUTS = ['tools/so3/build/linker_symbols.py', 'tools/so3/build/text_order.py']

# INCLUDE_ASM and INCLUDE_RODATA placeholders, which pull in a .s file by folder and name.
ASM_INCLUDE = re.compile(r'INCLUDE_(?:ASM|RODATA)\("([^"\n]+)",\s*([\w.$]+)\)')


def asm_inputs(source):
    """The .s files a C/C++ source pulls in through its placeholders."""
    if not source.exists():
        return []
    return [Path(folder) / f'{name}.s' for folder, name in ASM_INCLUDE.findall(source.read_text())]


def pieces(config):
    """List every file that becomes an object in a module, with the rule that builds it.

    They come back in the order the module's segments list them, which is the
    order the linker puts them in.
    """
    options = config['options']
    result = []
    # The last segment only marks where the module ends.
    for segment in config['segments'][:-1]:
        if isinstance(segment, list):
            require(len(segment) == 3 and segment[1] == 'bin', 'expected a bin segment')
            result.append((Path(options['asset_path']) / f'{segment[2]}.bin', 'binary_object'))
        elif segment['type'] == 'bin':
            result.append((Path(options['asset_path']) / f"{segment['name']}.bin", 'binary_object'))
        else:
            require(segment['type'] == 'code', 'expected a code segment')
            for subsegment in segment['subsegments']:
                _, kind, name = subsegment_parts(subsegment)
                if kind == 'pad':
                    continue  # The linker script writes the padding, so there's no object.
                if kind.startswith('.'):
                    continue  # A section of another unit's object, so no new object either.
                if kind in ('databin', 'rodatabin'):
                    # Splat writes asm/data/<name>.s, which pulls the extracted bytes in with .incbin.
                    result.append((Path(options['asm_path']) / 'data' / f'{name}.s', 'assemble'))
                    continue
                require(kind in ('asm', 'c', 'cpp') and isinstance(name, str),
                        'expected a named asm/c/cpp subsegment')
                if kind == 'asm':
                    result.append((Path(options['asm_path']) / f'{name}.s', 'assemble'))
                else:
                    result.append((Path(options['src_path']) / f'{name}.{kind}', 'compile'))
    return result


def full_asm_path(options, source):
    """The whole-unit assembly Splat writes for a C/C++ source, before any of it was decompiled."""
    relative = source.relative_to(options['src_path']).with_suffix('.s')
    return Path(options['asm_path']) / relative


def thunk_symbol_mappings(config, source, thunks):
    """Pair native assembly labels with the compiler thunks kept in this unit.

    The original assembly calls these func_<address>, but my object uses MWCC's
    own thunk names. objdiff needs this table to pair them up.
    """
    unit = next((unit for unit in code_units(config) if unit['source'] == str(source)), None)
    if unit is None:
        return {}
    start, end = unit['base'] + unit['start'], unit['base'] + unit['end']
    return {f'func_{address:08X}': name for name, address in thunks.items()
            if start <= address < end}


def ninja_rules():
    """The top of build.ninja: one rule for each kind of step."""
    compile_jobs = min(os.cpu_count() or 2, MAX_COMPILE_JOBS)
    assembler_flags = ' '.join([LITTLE_ENDIAN, f'-march={ASSEMBLER_CPU}', f'-mabi={ASSEMBLER_ABI}', *ASSEMBLER_FLAGS])
    return [
        '# Generated by tools/so3/build/driver.py from config/*.yaml and config/overlays/*.yaml.',
        'ninja_required_version = 1.3', 'builddir = build',
        f'binutils = {BINUTILS_PREFIX}',
        'pool split_pool', f'  depth = {SPLIT_JOBS}',
        'pool compile_pool', f'  depth = {compile_jobs}',
        'rule split', '  command = $split_command',
        '  description = SPLIT $module', '  pool = split_pool', '  restat = 1',
        'rule compile', '  command = python -m tools.so3.build.compile $in $out --macros $macro',
        '  description = COMPILE $in', '  pool = compile_pool',
        'rule compile_progress',
        '  command = python -m tools.so3.build.compile $in $out --macros $macro --skip-asm',
        '  description = PROGRESS $in', '  pool = compile_pool',
        'rule assemble',
        f'  command = ${{binutils}}as {assembler_flags} -I $include -o $out $in',
        '  description = AS $in',
        'rule binary_object',
        f'  command = ${{binutils}}objcopy -I binary -O {BINARY_OBJECT_FORMAT} -B {BINARY_ARCHITECTURE} $in $out',
        '  description = BIN $in',
        'rule absolute_symbols',
        '  command = python -m tools.so3.build.linker_symbols --output $out $in',
        '  description = SYMS $out',
        'rule link',
        f'  command = ${{binutils}}ld {LITTLE_ENDIAN} -T $layout -T $functions -T $symbols $absolute_symbols -o $out',
        '  description = LD $out',
        'rule binary_image', '  command = ${binutils}objcopy -O binary $in $out',
        '  description = IMAGE $out',
        'rule verify', '  command = $verify_command', '  description = VERIFY $module', '',
    ]


def working_compiler_files():
    record = working_candidate(json.loads(CONFIG.read_text()))
    folder = COMPILERS.relative_to(ROOT) / record['id']
    return [str(folder / name) for name in record['files']]


def project_headers():
    return sorted(str(path) for folder in HEADER_FOLDERS for path in Path(folder).rglob('*')
                  if path.suffix in HEADER_SUFFIXES)


def write_if_changed(path, content):
    """Only touch the file when it changes, so ninja doesn't think everything is out of date."""
    if not path.exists() or path.read_text() != content:
        path.write_text(content)


class Module:
    """The paths and settings one module's part of the build needs."""

    def __init__(self, path, config):
        self.config_path = path
        self.config = config
        self.options = options = config['options']
        self.is_main = path.name == MAIN_CONFIG.name
        self.name = 'main' if self.is_main else path.stem
        self.output = Path(options['build_path'])
        self.layout = options['ld_script_path']
        self.undefined_functions = options['undefined_funcs_auto_path']
        self.undefined_symbols = options['undefined_syms_auto_path']
        self.symbol_maps = options.get('symbol_addrs_path', [])
        self.absolute_symbols = self.output / 'absolute_symbols.ld' if self.symbol_maps else None
        self.include = options['generated_asm_macros_directory']
        self.macros = f'{self.include}/macro.inc'
        self.target = options['target_path']
        self.image = self.output / (MAIN_EXECUTABLE if self.is_main else OVERLAY_IMAGE)
        self.units = pieces(config)
        thunk_path = thunk_map_path(self.name)
        self.thunks = symbol_addresses(thunk_path) if thunk_path.is_file() else {}

    def split_outputs(self):
        """Everything Splat writes for this module."""
        compiled = [source for source, rule in self.units if rule == 'compile']
        outputs = [self.layout, self.undefined_functions, self.undefined_symbols, self.macros]
        outputs += [str(source) for source, _ in self.units]
        outputs += [str(assembly) for source in compiled for assembly in asm_inputs(source)]
        outputs += [str(full_asm_path(self.options, source)) for source in compiled]
        return list(dict.fromkeys(outputs))

    def split_inputs(self):
        inputs = [str(self.config_path), *SPLIT_INPUTS]
        inputs += self.symbol_maps + self.options.get('reloc_addrs_path', [])
        inputs += MAIN_SPLIT_INPUTS if self.is_main else OVERLAY_SPLIT_INPUTS
        return inputs

    def split_command(self):
        if self.is_main:
            return 'python -m tools.so3.build.main split'
        return f'python -m tools.so3.build.overlays run-splat --overlay {self.name}'

    def verify_command(self):
        if self.is_main:
            return f'python -m tools.so3.build.main verify --output {self.image} --report {self.output}/verify.json'
        return f'python -m tools.so3.build.overlays verify --overlay {self.name}'

    def compile_inputs(self, source, headers, compiler_files):
        """Everything a C/C++ object depends on besides the source itself."""
        # compile.py reads the module's symbol lists to put sections in the original order.
        lists = [str(path) for path in module_lists(self.name)]
        if not self.is_main:
            lists.append(str(self.config_path))
        return [self.macros, *(str(path) for path in asm_inputs(source)), *headers, *compiler_files,
                *COMPILE_INPUTS, *lists]

    def object_path(self, source, rule):
        # Compiled objects go under the build folder. Splat's assembly is
        # already under build/, so its objects sit next to it.
        return f'{self.output / source}.o' if rule == 'compile' else f'{source}.o'


def module_rules(module, headers, compiler_files, sdk_sources):
    """Write one module's build steps.

    Returns the ninja lines, plus the objdiff units and progress objects for
    every piece that isn't SDK code (the console's own library, which isn't
    part of the game's progress).
    """
    lines = []
    if module.absolute_symbols:
        lines += [f'build {module.absolute_symbols}: absolute_symbols {" ".join(module.symbol_maps)} | '
                  f'{" ".join(ABSOLUTE_SYMBOL_INPUTS)}']
    lines += [f'build {" ".join(module.split_outputs())}: split {module.target} | {" ".join(module.split_inputs())}',
              f'  split_command = {module.split_command()}', f'  module = {module.name}']

    objects, report_units, progress_objects = [], [], []
    for source, rule in module.units:
        target = module.object_path(source, rule)
        objects.append(target)
        inputs = []
        if rule == 'assemble':
            inputs = [module.macros]
        elif rule == 'compile':
            inputs = module.compile_inputs(source, headers, compiler_files)
        lines += [f'build {target}: {rule} {source}' + (f' | {" ".join(inputs)}' if inputs else '')]
        if rule == 'assemble':
            lines += [f'  include = {module.include}']
        elif rule == 'compile':
            lines += [f'  macro = {module.macros}']
        if str(source) in sdk_sources:
            continue

        metadata = {'progress_categories': [module.name], 'complete': False}
        unit = {'name': f'{module.name}/{source.stem}', 'target_path': target, 'metadata': metadata}
        if rule == 'compile':
            # objdiff compares Splat's assembly for the whole unit (the target)
            # with the same source compiled without any placeholders (the base).
            full_asm = full_asm_path(module.options, source)
            target = f'{full_asm}.o'
            base = f'{PROGRESS_OBJECTS / source}.o'
            lines += [f'build {target}: assemble {full_asm} | {module.macros}',
                      f'  include = {module.include}',
                      f'build {base}: compile_progress {source} | {" ".join(inputs)}',
                      f'  macro = {module.macros}']
            unit.update(target_path=target, base_path=base)
            mappings = thunk_symbol_mappings(module.config, source, module.thunks)
            if mappings:
                unit['symbol_mappings'] = mappings
            metadata.update(source_path=str(source), complete=not asm_inputs(source))
            progress_objects.append(base)
        else:
            # Assembly and binary pieces have no source, but objdiff still counts
            # them, so the totals cover the whole module.
            metadata['auto_generated'] = True
        report_units.append(unit)
        progress_objects.append(unit['target_path'])

    absolute = f' -T {module.absolute_symbols}' if module.absolute_symbols else ''
    link_inputs = [module.layout, module.undefined_functions, module.undefined_symbols]
    if module.absolute_symbols:
        link_inputs.append(str(module.absolute_symbols))
    lines += [f'build {module.output}/linked.elf: link {" ".join(objects)} | {" ".join(link_inputs)}',
              f'  layout = {module.layout}', f'  functions = {module.undefined_functions}',
              f'  symbols = {module.undefined_symbols}', f'  absolute_symbols ={absolute}',
              f'build {module.image}: binary_image {module.output}/linked.elf',
              f'build {module.output}/verify.json: verify {module.image} | '
              f'{module.target} {" ".join(module.split_inputs())}',
              f'  verify_command = {module.verify_command()}', f'  module = {module.name}', '']
    return lines, report_units, progress_objects


def configure(configs):
    """Write build/build.ninja and objdiff.json for every module."""
    sdk_sources = validate_sdk_units(configs)
    compiler_files = working_compiler_files()
    headers = project_headers()
    lines = ninja_rules()
    split_outputs, verify_outputs, progress_objects = [], [], []
    report_units, categories = [], []
    for path, config in configs:
        module = Module(path, config)
        module_lines, units, objects = module_rules(module, headers, compiler_files, sdk_sources)
        lines += module_lines
        report_units += units
        progress_objects += objects
        categories.append({'id': module.name, 'name': 'Main' if module.is_main else module.name})
        split_outputs += module.split_outputs()
        verify_outputs.append(f'{module.output}/verify.json')
    lines += [f'build split: phony {" ".join(split_outputs)}',
              f'build all: phony {" ".join(verify_outputs)}',
              f'build objdiff-objects: phony {" ".join(progress_objects)}', 'default all', '']
    BUILD_FILE.parent.mkdir(parents=True, exist_ok=True)
    write_if_changed(BUILD_FILE, '\n'.join(lines))

    objdiff = {
        '$schema': f'https://raw.githubusercontent.com/encounter/objdiff/v{OBJDIFF_VERSION}/config.schema.json',
        'min_version': OBJDIFF_VERSION,
        # Objects are built explicitly with make objdiff-objects or make report.
        'build_target': False, 'build_base': False,
        'units': report_units, 'progress_categories': categories,
    }
    write_if_changed(OBJDIFF_CONFIG, json.dumps(objdiff, indent=2) + '\n')


def ninja(target):
    subprocess.run(['ninja', '-f', str(BUILD_FILE), target], check=True)


def run(configs, command):
    if command != 'split':
        setup(working_candidate(json.loads(CONFIG.read_text())))
    configure(configs)
    ninja('split')
    # The first split creates the C/C++ files. Configuring again reads their
    # INCLUDE_ASM paths into the build, so missing assembly gets regenerated and
    # editing a source triggers a compile.
    configure(configs)
    if command in ('build', 'report'):
        ninja('all')
    if command in ('objdiff-objects', 'report'):
        ninja('objdiff-objects')
    if command == 'report':
        # Write to a temporary file first, so an interrupted run never leaves a half-written report.
        temporary = PROGRESS_REPORT.with_suffix('.json.tmp')
        subprocess.run(['objdiff-cli', 'report', 'generate', '-o', str(temporary)], check=True)
        temporary.replace(PROGRESS_REPORT)


def main():
    import yaml
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('command', choices=('split', 'build', 'objdiff-objects', 'report'))
    args = parser.parse_args()
    os.chdir(ROOT)
    try:
        # This checks the original main executable is there and is the version I expect.
        original_main()
        configs = [(MAIN_CONFIG, yaml.safe_load(MAIN_CONFIG.read_text()))]
        configs += [(path, load_config(path)[0]) for path in sorted(CONFIGS.glob('*.yaml'))]
        run(configs, args.command)
    except (OSError, ValueError, subprocess.CalledProcessError) as error:
        print(f'error: {error}', file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
