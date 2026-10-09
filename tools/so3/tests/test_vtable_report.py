"""Comparing compiled vtables with the game's."""

import json
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import unittest
from unittest.mock import patch

from tools.so3.build.elf import R_MIPS_32, STT_FUNC, STT_SECTION, SYMBOL
from tools.so3.build.vtable_report import build_report, check_vtable, linked_symbols, resolver, thunk_map, vtable_images


class FakeImage:
    """The game's bytes at one address."""

    def __init__(self, address, data):
        self.address, self.data = address, data

    def read(self, address, size):
        if address == self.address and size <= len(self.data):
            return self.data[:size]
        return None


def words(*values):
    return b''.join(value.to_bytes(4, 'little') for value in values)


# Two functions the linked module knows, and one that's still assembly.
SYMBOLS = ({'first__3FooFv': 0x1000, 'second__3FooFv': 0x1010},
           {0x1000: 'first__3FooFv', 0x1010: 'second__3FooFv', 0x1020: 'func_00001020'})


def vtable(*slots, size=16):
    return {'name': '__vt__3Foo', 'address': 0x500, 'bytes': bytes(size).hex(),
            'slots': [[offset, R_MIPS_32, target] for offset, target in slots]}


def check(compiled, game):
    images = {'main': FakeImage(0x500, game), 'mod': FakeImage(0, b''), 'lib': FakeImage(0, b'')}
    return check_vtable(compiled, 'mod', SYMBOLS, images)


class VtableCheckTests(unittest.TestCase):
    def test_same_functions_match(self):
        compiled = vtable((8, 'first__3FooFv'), (12, 'second__3FooFv'))
        self.assertEqual(check(compiled, words(0, 0, 0x1000, 0x1010)), ('match', []))

    def test_swapped_functions_are_wrong(self):
        compiled = vtable((8, 'first__3FooFv'), (12, 'second__3FooFv'))
        status, slots = check(compiled, words(0, 0, 0x1010, 0x1000))
        self.assertEqual(status, 'wrong')
        self.assertEqual([(s['offset'], s['ours'], s['game']) for s in slots],
                         [(8, 'first__3FooFv', 'second__3FooFv'), (12, 'second__3FooFv', 'first__3FooFv')])

    def test_slots_that_cant_be_filled_in_yet_are_incomplete(self):
        compiled = vtable((8, 'unknown__3FooFv'), (12, 'first__3FooFv'), size=20)
        status, slots = check(compiled, words(0, 0, 0x1010, 0x1020, 0x1000))
        self.assertEqual(status, 'incomplete')
        self.assertEqual([(s['offset'], s['why']) for s in slots],
                         [(8, 'no address'), (12, 'not decompiled'), (16, 'declared only')])

    def test_a_wrong_slot_outweighs_incomplete_ones(self):
        compiled = vtable((8, 'unknown__3FooFv'), (12, 'second__3FooFv'))
        self.assertEqual(check(compiled, words(0, 0, 0x1000, 0x1000))[0], 'wrong')

    def test_address_outside_every_image(self):
        compiled = dict(vtable((8, 'first__3FooFv')), address=0x900)
        self.assertEqual(check(compiled, words(0, 0, 0x1000, 0)), ('outside', []))

    def test_an_unavailable_resident_image_is_not_used(self):
        compiled = vtable((8, 'first__3FooFv'), (12, 'second__3FooFv'))
        images = {'main': FakeImage(0x500, words(0, 0, 0x1010, 0x1000)),
                  'mod': FakeImage(0, b'')}
        self.assertEqual(check_vtable(compiled, 'mod', SYMBOLS, images, ['mod']), ('outside', []))

    def test_a_table_in_the_selected_overlay_is_still_checked(self):
        compiled = vtable((8, 'first__3FooFv'), (12, 'second__3FooFv'))
        images = {'main': FakeImage(0x500, words(0, 0, 0x1010, 0x1000)),
                  'mod': FakeImage(0x500, words(0, 0, 0x1000, 0x1010))}
        self.assertEqual(check_vtable(compiled, 'mod', SYMBOLS, images, ['mod']), ('match', []))
        images['mod'] = images['main']
        self.assertEqual(check_vtable(compiled, 'mod', SYMBOLS, images, ['mod'])[0], 'wrong')

    def test_an_unknown_game_address_is_still_wrong(self):
        compiled = vtable((8, 'first__3FooFv'))
        self.assertEqual(check(compiled, words(0, 0, 0x1234, 0))[0], 'wrong')


class SymbolLookupTests(unittest.TestCase):
    def test_thunk_maps_are_specific_to_the_module(self):
        name = '@32@func_003EEBE0__15LibObject178660Fv'
        with TemporaryDirectory() as folder:
            path = Path(folder)
            (path / 'cequip_thunk_addrs.txt').write_text(f'{name} = 0x00412FB0;\n')
            (path / 'citemcreation_thunk_addrs.txt').write_text(f'{name} = 0x0036F380;\n')
            with patch('tools.so3.build.vtable_report.THUNK_MAPS', path):
                self.assertEqual(thunk_map('cequip'), {name: 0x412FB0})
                self.assertEqual(thunk_map('citemcreation'), {name: 0x36F380})
                self.assertEqual(thunk_map('missing'), {})

    def test_known_thunks_are_checked_and_unknown_thunks_stay_incomplete(self):
        name = '@4@first__3FooFv'
        linked = {'mod': ({}, {})}
        with patch('tools.so3.build.vtable_report.symbol_map', return_value={}), \
             patch('tools.so3.build.vtable_report.thunk_map', return_value={name: 0x1000}):
            symbols = resolver('mod', linked, {name: 0x2000})
        images = {'main': FakeImage(0x500, words(0, 0, 0x1000, 0)),
                  'mod': FakeImage(0, b''), 'lib': FakeImage(0, b'')}
        self.assertEqual(check_vtable(vtable((8, name)), 'mod', symbols, images), ('match', []))
        images['main'] = FakeImage(0x500, words(0, 0, 0x1004, 0))
        self.assertEqual(check_vtable(vtable((8, name)), 'mod', symbols, images)[0], 'wrong')
        compiled = dict(vtable((8, name)), bytes=words(0, 0, 4, 0).hex())
        self.assertEqual(check_vtable(compiled, 'mod', symbols, images), ('match', []))
        status, slots = check_vtable(vtable((8, '@8@first__3FooFv')), 'mod', symbols, images)
        self.assertEqual(status, 'incomplete')
        self.assertEqual(slots[0]['why'], 'no address')

    def test_linked_thunk_addresses_take_precedence_over_the_map(self):
        name = '@4@first__3FooFv'
        linked = {'mod': ({name: 0x1000}, {0x1000: name})}
        with patch('tools.so3.build.vtable_report.symbol_map', return_value={}), \
             patch('tools.so3.build.vtable_report.thunk_map', return_value={name: 0x2000}):
            self.assertEqual(resolver('mod', linked, {})[0][name], 0x1000)

    def test_section_labels_are_not_function_names(self):
        strings = b'\0.mwcats_func_00001000\0func_00001000\0'
        symbols = b''.join(SYMBOL.pack(label, 0x1000, 8, kind, 0, 1)
                           for label, kind in [(1, STT_SECTION), (23, STT_FUNC)])
        headers = [SimpleNamespace(type=2, offset=0, size=len(symbols), link=1),
                   SimpleNamespace(type=3, offset=len(symbols))]
        with patch('tools.so3.build.vtable_report.section_headers', return_value=headers):
            names, addresses = linked_symbols(symbols + strings)
        self.assertIn('.mwcats_func_00001000', names)
        self.assertEqual(addresses, {0x1000: 'func_00001000'})

    def test_local_and_shared_maps_name_missing_linked_functions(self):
        linked = {'main': ({}, {}), 'lib': ({}, {}),
                  'mod': ({'func_00001000': 0x1000}, {0x1000: 'func_00001000'})}
        maps = {'main': {'resident__3FooFv': 0x800},
                'lib': {'shared__3FooFv': 0x900}, 'mod': {'method__3FooFv': 0x1000}}
        with patch('tools.so3.build.vtable_report.symbol_map', side_effect=lambda name: maps[name]):
            names, addresses = resolver('mod', linked, {'other_overlay': 0x1000})
        self.assertEqual(names['method__3FooFv'], 0x1000)
        self.assertEqual(addresses, {0x800: 'resident__3FooFv', 0x900: 'shared__3FooFv',
                                     0x1000: 'method__3FooFv'})


class ReferenceImageTests(unittest.TestCase):
    def test_config_selects_available_reference_images(self):
        with TemporaryDirectory() as folder:
            path = Path(folder) / 'mod.yaml'
            path.write_text('vtable_images: [mod]\n')
            with patch('tools.so3.build.vtable_report.config_path', return_value=path):
                self.assertEqual(vtable_images('mod'), ['mod'])
            path.write_text('{}\n')
            with patch('tools.so3.build.vtable_report.config_path', return_value=path):
                self.assertEqual(vtable_images('mod'), ['main', 'mod', 'lib'])

    def test_invalid_image_names_are_rejected(self):
        with TemporaryDirectory() as folder:
            path = Path(folder) / 'mod.yaml'
            path.write_text('vtable_images: [missing]\n')
            with patch('tools.so3.build.vtable_report.config_path',
                       side_effect=lambda name: Path(folder) / f'{name}.yaml'):
                with self.assertRaisesRegex(ValueError, 'unknown vtable image missing'):
                    vtable_images('mod')
            path.write_text('vtable_images: main\n')
            with patch('tools.so3.build.vtable_report.config_path', return_value=path):
                with self.assertRaisesRegex(ValueError, 'must be a list'):
                    vtable_images('mod')

    def test_report_distinguishes_an_unavailable_reference(self):
        with TemporaryDirectory() as folder:
            record = Path(folder) / 'record.json'
            record.write_text(json.dumps({'source': 'src/mod.cpp', 'vtables': [vtable()]}))
            images = {'main': FakeImage(0x500, words(0, 0, 0x1000, 0x1010)),
                      'mod': FakeImage(0, b''), 'lib': FakeImage(0, b'')}
            with patch('tools.so3.build.vtable_report.module_of_record', return_value=('mod', Path(folder))), \
                 patch('tools.so3.build.vtable_report.linked_symbols', return_value=({}, {})), \
                 patch('tools.so3.build.vtable_report.every_map', return_value={}), \
                 patch('tools.so3.build.vtable_report.symbol_map', return_value={}), \
                 patch('tools.so3.build.vtable_report.vtable_images', return_value=['mod']), \
                 patch('tools.so3.build.vtable_report.image_for', side_effect=lambda name, _: images[name]), \
                 patch.object(Path, 'read_bytes', return_value=b''):
                report = build_report([record])
            self.assertEqual(len(report['outside']), 1)
            self.assertEqual(report['outside'][0]['why'], 'reference image unavailable')
            self.assertEqual(report['wrong'], [])


if __name__ == '__main__':
    unittest.main()
