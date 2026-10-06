"""Preserve explicit native ownership of whole compiler-generated jump tables."""
import re
import struct
from tools.so3.build.text_order import merge_rodata_sections


def _require(condition, message):
    if not condition:
        raise ValueError(message)


def _elf(data):
    _require(len(data) >= 52 and data[:7] == b'\x7fELF\x01\x01\x01',
             'expected a little-endian ELF32 object')
    _require(struct.unpack_from('<HH', data, 16) == (1, 8), 'expected a MIPS relocatable object')
    offset = struct.unpack_from('<I', data, 32)[0]
    stride, count, names_index = struct.unpack_from('<HHH', data, 46)
    _require(stride == 40 and count and 0 < names_index < count and
             offset >= 52 and offset + count * stride <= len(data), 'invalid ELF section table')
    headers = [list(struct.unpack_from('<10I', data, offset + i * stride)) for i in range(count)]
    for i, h in enumerate(headers):
        _require(h[1] not in (4, 11, 18), 'RELA, dynamic or extended symbol tables are unsupported')
        _require(not h[5] or h[1] == 8 or h[4] + h[5] <= len(data), f'section payload outside object: {i}')
        _require(not h[8] or h[8] & (h[8] - 1) == 0, f'invalid section alignment: {i}')
    payload = lambda h: data[h[4]:h[4] + h[5]]
    _require(headers[names_index][1] == 3, 'section names are not a string table')
    strings = payload(headers[names_index])

    def string(blob, value):
        _require(value < len(blob) and b'\0' in blob[value:], 'invalid ELF string offset')
        try:
            return blob[value:blob.index(b'\0', value)].decode('utf-8')
        except UnicodeDecodeError as error:
            raise ValueError('invalid ELF string encoding') from error

    name = lambda index: string(strings, headers[index][0])
    for i in range(count):
        name(i)
    tables = [i for i, h in enumerate(headers) if h[1] == 2]
    _require(len(tables) == 1, 'owned jump tables require exactly one symbol table')
    table_index = tables[0]
    table = headers[table_index]
    _require(table[9] == 16 and table[5] % 16 == 0 and 0 < table[6] < count and
             headers[table[6]][1] == 3, 'invalid ELF symbol table')
    labels = payload(headers[table[6]])
    symbols = [dict(name=string(labels, z[0]), value=z[1], size=z[2], info=z[3], index=z[5])
               for z in struct.iter_unpack('<IIIBBH', payload(table))]
    for symbol in symbols:
        _require(symbol['index'] < count or symbol['index'] in (0xfff1, 0xfff2), 'symbol section index outside object')
    for i, h in enumerate(headers):
        if h[1] != 9:
            continue
        _require(h[6] == table_index and 0 < h[7] < count and h[9] in (0, 8) and
                 h[5] % 8 == 0, f'invalid REL section: {i}')
        target = headers[h[7]]
        _require(target[1] not in (0, 8), 'REL target must contain actual bytes')
        for at, relocation in struct.iter_unpack('<II', payload(h)):
            _require(relocation >> 8 < len(symbols), 'REL symbol index outside symbol table')
            # This adapter handles word-sized MIPS relocation records. Unsupported
            # kinds elsewhere remain the responsibility of the existing pipeline.
            _require(at + 4 <= target[5], 'REL write outside target section')
    return headers, payload, name, symbols


def _rename_sections(data, names):
    output = bytearray(data)
    offset = struct.unpack_from('<I', data, 32)[0]
    stride, count, names_index = struct.unpack_from('<HHH', data, 46)
    header = list(struct.unpack_from('<10I', data, offset + names_index * stride))
    strings = bytearray(data[header[4]:header[4] + header[5]])
    for index, name in names.items():
        _require(0 <= index < count, 'section rename index outside object')
        value = strings.find(name.encode() + b'\0')
        if value < 0:
            value = len(strings)
            strings.extend(name.encode() + b'\0')
        struct.pack_into('<I', output, offset + index * stride, value)
    header[4], header[5] = len(output), len(strings)
    output.extend(strings)
    struct.pack_into('<10I', output, offset + names_index * stride, *header)
    return bytes(output)


def _integer(value, message):
    _require(type(value) is int and 0 <= value <= 0xffffffff, message)
    return value


def _relocations(headers, payload):
    return {i: [(offset, info & 255, info >> 8) for h in headers if h[1] == 9 and h[7] == i
                for offset, info in struct.iter_unpack('<II', payload(h))] for i in range(len(headers))}


def _check_table_references(headers, payload, symbols, relocations, owners):
    for index, (function, table) in owners.items():
        extent = headers[index][5]
        for symbol in symbols:
            if symbol['index'] == index:
                _require(symbol['value'] <= extent and symbol['size'] <= extent - symbol['value'],
                         'table alias extends outside its compiler section')
        records = relocations[index]
        _require(len(records) == extent // 4 and {o for o, _, _ in records} == set(range(0, extent, 4)),
                 'jump table must have one relocation for each word')
        for offset, kind, target_index in records:
            target = symbols[target_index]
            _require(offset % 4 == 0 and kind == 2 and target['index'] == function['index'],
                     'jump table destination is not in its owning function')
            addend = struct.unpack_from('<I', payload(headers[index]), offset)[0]
            destination = target['value'] + addend
            _require(destination % 4 == 0 and function['value'] <= destination and
                     destination + 4 <= function['value'] + function['size'],
                     'jump table destination lies outside its owning function')
    for index, records in relocations.items():
        pending = {}
        for offset, kind, target_index in records:
            target = symbols[target_index]
            if target['index'] not in owners:
                continue
            _require(target['info'] & 15 != 3, 'references to owned section symbols are unsupported')
            _require(offset % 4 == 0, 'unaligned relocation to an owned table')
            word = struct.unpack_from('<I', payload(headers[index]), offset)[0]
            extent = headers[target['index']][5]
            if kind == 5:
                pending.setdefault(target_index, []).append(word & 0xffff)
                continue
            if kind == 6:
                low = word & 0xffff
                low = low if low < 0x8000 else low - 0x10000
                _require(target_index in pending, 'owned table LO16 has no preceding matching HI16')
                addends = [(high << 16) + low for high in pending.pop(target_index)]
            elif kind == 2:
                addends = [word]
            else:
                raise ValueError('unsupported relocation to an owned table')
            for addend in addends:
                _require(0 <= target['value'] + addend < extent,
                         'relocation effective target crosses compiler table boundary')
        _require(not pending, 'owned table HI16 has no matching LO16')


def owned_rodata_sections(data, groups):
    """Merge whole compiler tables only within configured native data islands.

    Groups supply unique linker selectors, native addresses/extents and stable
    owning function anchors. Actual compiler symbols, section order, alignment,
    table destinations and incoming relocation addends are independently checked.
    No compiler label names, offsets or synthesized table payloads are supplied.
    """
    headers, payload, name, symbols = _elf(data)
    ordinary = {i for i, h in enumerate(headers) if name(i) == '.rodata'}
    _require(all(headers[i][1] == 1 and headers[i][2] == 2 for i in ordinary),
             'ordinary rodata must be allocatable readonly PROGBITS')
    rodata = {i for i in ordinary if headers[i][5]}
    relocations = _relocations(headers, payload)
    claimed, selectors, functions_seen = set(), set(), set()
    recovered, spans, owners = [], [], {}
    for group in groups:
        selector = group['section']
        _require(isinstance(selector, str) and re.fullmatch(r'\.rodata\.[A-Za-z0-9_.-]+', selector) and
                 selector not in selectors and all(name(i) != selector for i in range(len(headers))),
                 'owned linker selector is invalid or already exists')
        selectors.add(selector)
        address = _integer(group['address'], 'invalid native island address')
        size = _integer(group['size'], 'invalid native island extent')
        _require(size > 0 and address + size <= 0x100000000 and group['anchors'], 'empty or overflowing native island')
        spans.append((address, address + size))
        sections, tables = [], []
        for anchor in group['anchors']:
            anchor_size = _integer(anchor['size'], 'invalid native table size')
            native_offset = _integer(anchor['offset'], 'invalid native table offset')
            function_name = anchor['function']
            _require(function_name not in functions_seen and anchor_size > 0 and anchor_size % 4 == 0 and
                     native_offset % 4 == 0 and native_offset + anchor_size <= size,
                     'invalid or repeated native table anchor')
            functions_seen.add(function_name)
            functions = [s for s in symbols if s['name'] == function_name and 0 < s['index'] < len(headers) and s['info'] & 15 == 2]
            _require(len(functions) == 1, f'rodata owner is not one defined function: {function_name}')
            function = functions[0]
            _require(name(function['index']) == '.text' and function['size'] > 0 and
                     function['value'] + function['size'] <= headers[function['index']][5], 'invalid owning function extent')
            targets = {target for at, _, target in relocations[function['index']]
                       if function['value'] <= at < function['value'] + function['size'] and symbols[target]['index'] in rodata}
            _require(len(targets) == 1, f'rodata owner has ambiguous compiler table references: {function_name}')
            table = symbols[targets.pop()]
            index = table['index']
            _require(index not in claimed and table['value'] == 0 and table['size'] == headers[index][5] == anchor_size,
                     f'compiler table extent or ownership differs: {function_name}')
            claimed.add(index)
            sections.append(index)
            owners[index] = (function, table)
            tables.append(dict(function=function_name, compiler_symbol=table['name'], section=index,
                               size=table['size'], native_offset=native_offset))
        _require(sections == sorted(sections), 'compiler table order differs from native ownership')
        cursor = 0
        for table in tables:
            alignment = max(headers[table['section']][8], 1)
            _require(address % alignment == 0, 'native island address violates compiler alignment')
            cursor = (cursor + alignment - 1) // alignment * alignment
            _require(cursor == table['native_offset'], 'compiler alignment does not reproduce native table offset')
            cursor += table['size']
        _require(cursor == size, 'compiler tables do not cover configured native island')
        recovered.append(dict(section=selector, address=address, size=cursor, tables=tables))
    _require(all(a[1] <= b[0] for a, b in zip(sorted(spans), sorted(spans)[1:])), 'native data islands overlap')
    _require(claimed == rodata, 'compiler rodata is not completely covered by native ownership')
    _check_table_references(headers, payload, symbols, relocations, owners)
    # Hide empty ordinary headers too: the existing merge selects its first
    # .rodata header, even when that header has no payload.
    data = _rename_sections(data, {i: f'.rodata.pending.{i}' for i in ordinary})
    for group in recovered:
        selected = [t['section'] for t in group['tables']]
        data = _rename_sections(data, {i: '.rodata' for i in selected})
        data = merge_rodata_sections(data)
        data = _rename_sections(data, {selected[0]: group['section']})
    return data, recovered
