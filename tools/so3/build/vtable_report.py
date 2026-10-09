#!/usr/bin/env python3
"""Check the vtables I compile against the game's.

A vtable is the list of function addresses a C++ class uses for its virtual
functions. The game keeps Field's vtables in the main program, so the build
throws the compiled ones away and uses the game's, and nothing else would
notice a class with its virtual functions in the wrong order. compile.py saves
each compiled vtable, and this script fills in its function addresses from the
linked module and compares it with the game's bytes. It writes
build/vtable-report.json and prints a one-line summary.
"""

import argparse
import json
from pathlib import Path
import re

import yaml

from tools.so3.build.elf import R_MIPS_32, SYMBOL, section_headers
from tools.so3.build.text_order import symbol_addresses

MAIN_CONFIG = Path('config/main.us.yaml')
OVERLAY_CONFIGS = Path('config/overlays')
SYMBOL_MAPS = Path('config/symbols')
SHARED_MODULE = 'lib'  # Lib stays loaded alongside the other overlays.
# A function that only has its address for a name, which means it's still assembly.
ADDRESS_NAME = re.compile(r'func_[0-9A-F]+')


def module_of_record(path):
    """The module a record belongs to, and its build folder, from the record's path."""
    parts = Path(path).parts
    output = Path(*parts[:parts.index('src')])
    return ('main' if parts[1] == 'main' else parts[2]), output


def linked_symbols(data):
    """{name: address} for every symbol the linked module defines, and the reverse."""
    headers = section_headers(data)
    symtab = next(h for h in headers if h.type == 2)
    strings = data[headers[symtab.link].offset:]
    by_name, by_address = {}, {}
    for offset in range(symtab.offset, symtab.offset + symtab.size, SYMBOL.size):
        label, value, _, _, _, section = SYMBOL.unpack_from(data, offset)
        name = strings[label:].split(b'\0', 1)[0].decode()
        if section and name:
            by_name[name] = value
            by_address.setdefault(value, name)
    return by_name, by_address


class Image:
    """A module's original file, read by address."""

    def __init__(self, config_path):
        config = yaml.safe_load(config_path.read_text())
        self.data = Path(config['options']['target_path']).read_bytes()
        # Everything after the first fixed address is one continuous block.
        first = next(s for s in config['segments'] if isinstance(s, dict) and 'vram' in s)
        self.base = first['vram'] - first['start']
        self.start = first['vram']
        self.end = self.base + len(self.data)

    def read(self, address, size):
        if self.start <= address and address + size <= self.end:
            return self.data[address - self.base:address - self.base + size]
        return None


def symbol_map(module):
    path = SYMBOL_MAPS / f'{module}_symbol_addrs.txt'
    return symbol_addresses(path) if path.is_file() else {}


def every_map():
    """Each name's address from all the symbol maps, leaving out names they disagree on."""
    found, conflicts = {}, set()
    for path in sorted(SYMBOL_MAPS.glob('*_symbol_addrs.txt')):
        for name, address in symbol_addresses(path).items():
            if found.setdefault(name, address) != address:
                conflicts.add(name)
    return {name: address for name, address in found.items() if name not in conflicts}


def resolver(module, linked, maps):
    """Where to look up a slot's function: the module's link, its symbol map, main, Lib, then any map.

    A function can be missing from the module's own link when it's still an
    assembly placeholder under its address name, or when it lives in another
    module. The symbol maps know it by its real name.
    """
    names = {}
    for table in reversed([linked[module][0], symbol_map(module), linked.get('main', ({},))[0],
                           linked.get(SHARED_MODULE, ({},))[0], maps]):
        names.update(table)
    addresses = {}
    for table in [maps, linked.get(SHARED_MODULE, ({}, {}))[1], linked.get('main', ({}, {}))[1], linked[module][1]]:
        addresses.update(table)
    return names, addresses


def image_for(module, cache):
    if module not in cache:
        path = MAIN_CONFIG if module == 'main' else OVERLAY_CONFIGS / f'{module}.yaml'
        cache[module] = Image(path)
    return cache[module]


def check_vtable(vtable, module, symbols, images):
    """Compare one compiled vtable with the game's. Returns (status, slots).

    The status is `match`, `wrong` when a slot points at a different function
    than the game's, `incomplete` when the only differences are slots I can't
    fill in yet, or `outside` when the game's address isn't in any image. A
    slot can't be filled in yet when my source only declares the function (the
    compiler leaves a zero), when the function has no known address, or when
    the game's slot is a function that's still assembly, so my class doesn't
    override it yet.
    """
    compiled = bytearray.fromhex(vtable['bytes'])
    original = None
    for name in dict.fromkeys(['main', module, SHARED_MODULE]):
        original = image_for(name, images).read(vtable['address'], len(compiled))
        if original is not None:
            break
    if original is None:
        return 'outside', []
    by_name, by_address = symbols
    slots = {offset: target for offset, _, target in vtable['slots']}
    unknown = set()
    for offset, kind, target in vtable['slots']:
        if kind != R_MIPS_32 or target not in by_name:
            unknown.add(offset)
            continue
        addend = int.from_bytes(compiled[offset:offset + 4], 'little')
        compiled[offset:offset + 4] = ((by_name[target] + addend) & 0xFFFFFFFF).to_bytes(4, 'little')
    wrong, unchecked = [], []
    for offset in range(0, len(compiled), 4):
        ours = int.from_bytes(compiled[offset:offset + 4], 'little')
        game = int.from_bytes(original[offset:offset + 4], 'little')
        game_name = by_address.get(game, f'0x{game:08X}')
        slot = {'offset': offset, 'ours': slots.get(offset, f'0x{ours:08X}'), 'game': game_name}
        if offset in unknown:
            unchecked.append({**slot, 'why': 'no address'})
        elif ours == game:
            continue
        elif offset not in slots and ours == 0:
            unchecked.append({**slot, 'ours': None, 'why': 'declared only'})
        elif ADDRESS_NAME.fullmatch(game_name):
            unchecked.append({**slot, 'why': 'not decompiled'})
        else:
            wrong.append(slot)
    if wrong:
        return 'wrong', wrong
    if unchecked:
        return 'incomplete', unchecked
    return 'match', []


def build_report(record_paths):
    report = {'match': [], 'wrong': [], 'incomplete': [], 'outside': []}
    images, linked, resolvers = {}, {}, {}
    maps = every_map()
    for name, folder in (('main', Path('build/main')), (SHARED_MODULE, Path(f'build/overlays/{SHARED_MODULE}'))):
        linked[name] = linked_symbols((folder / 'linked.elf').read_bytes())
    for path in record_paths:
        record = json.loads(Path(path).read_text())
        if not record['vtables']:
            continue
        module, output = module_of_record(path)
        if module not in resolvers:
            linked.setdefault(module, linked_symbols((output / 'linked.elf').read_bytes()))
            resolvers[module] = resolver(module, linked, maps)
        for vtable in record['vtables']:
            status, details = check_vtable(vtable, module, resolvers[module], images)
            entry = {'source': record['source'], 'vtable': vtable['name'], 'address': vtable['address']}
            if details:
                entry['slots'] = details
            report[status].append(entry)
    for entries in report.values():
        entries.sort(key=lambda entry: (entry['source'], entry['vtable']))
    return report


def summary(report):
    checked = sum(len(entries) for entries in report.values())
    return (f"Vtables: {checked} compiled, {len(report['match'])} match the game's, "
            f"{len(report['wrong'])} point a slot at the wrong function, "
            f"{len(report['incomplete'])} are incomplete, {len(report['outside'])} outside every image")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('records', nargs='*', type=Path, help="compile.py's .vtables.json files")
    parser.add_argument('--output', required=True, type=Path)
    args = parser.parse_args()
    report = build_report(args.records)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=1) + '\n')
    print(summary(report))


if __name__ == '__main__':
    main()
