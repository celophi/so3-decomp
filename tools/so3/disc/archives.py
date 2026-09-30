"""Bounded readers for the container layouts observed on the supported SO3 discs."""

import struct

from ..formats import require


def pack_entries(data):
    """Return offset/end/tag entries for an inline PACK, excluding index-only variants."""
    require(len(data) >= 8 and data[:4] == b'PACK', 'invalid PACK header')
    version, count = struct.unpack_from('<HH', data, 4)
    require(version == 0, 'unsupported PACK version')
    table_end = 8 + count * 8
    require(table_end <= len(data), 'PACK directory exceeds container')
    entries = [struct.unpack_from('<II', data, 8 + i * 8) for i in range(count)]
    offsets = [offset for offset, _ in entries] + [len(data)]
    require(all(table_end <= start <= end <= len(data)
                for start, end in zip(offsets, offsets[1:])),
            'PACK offsets are not bounded inline members (possible external index)')
    return [{'index': i, 'offset': start, 'end': end, 'tag': tag}
            for i, ((start, tag), end) in enumerate(zip(entries, offsets[1:]))]


def zls_entries(data):
    """Read the forward/backward ZLS wrapper chain through its DNE terminator."""
    offset = previous_stride = 0
    result = []
    while True:
        require(offset + 16 <= len(data), 'truncated ZLS wrapper')
        magic = data[offset:offset + 4]
        size, previous, advance = struct.unpack_from('<III', data, offset + 4)
        require(previous == previous_stride, 'incorrect ZLS backward stride')
        if magic == b'DNE\0':
            require(size == advance == 0, 'invalid ZLS terminator')
            return result
        require(magic == b'ZLS\0', 'invalid ZLS signature')
        require(0 < size <= len(data) - offset - 16, 'ZLS payload exceeds container')
        require(advance >= 16 + size and offset + advance + 16 <= len(data),
                'invalid ZLS forward stride')
        result.append({'index': len(result), 'offset': offset + 16,
                       'end': offset + 16 + size, 'wrapper_offset': offset})
        previous_stride = advance
        offset += advance


def ioprp_entries(data):
    """Read the supported IOPRP image's ROMDIR at offset zero, with 16-byte file alignment."""
    require(len(data) >= 48 and data[:10] == b'RESET\0\0\0\0\0'
            and data[16:26] == b'ROMDIR\0\0\0\0', 'unsupported IOPRP ROMDIR placement')
    directory_size = struct.unpack_from('<I', data, 28)[0]
    require(48 <= directory_size <= len(data) and directory_size % 16 == 0,
            'invalid IOPRP directory size')
    result = []
    offset = ext_size = 0
    terminated = False
    for pos in range(0, directory_size, 16):
        raw_name, ext, size = struct.unpack_from('<10sHI', data, pos)
        if raw_name == bytes(10):
            require(ext == size == 0 and not any(data[pos:directory_size]), 'invalid ROMDIR terminator')
            terminated = True
            break
        name = raw_name.split(b'\0', 1)[0].decode('ascii')
        require(name and all(c.isalnum() or c == '_' for c in name), 'invalid IOPRP member name')
        require(offset + size <= len(data), 'IOPRP member exceeds image')
        require(name not in {e['name'] for e in result}, 'duplicate IOPRP member')
        result.append({'name': name, 'offset': offset, 'end': offset + size,
                       'extinfo_size': ext})
        offset += (size + 15) & ~15
        ext_size += ext
    require(terminated, 'unterminated IOPRP directory')
    require(result[0]['end'] == 0 and result[1]['offset'] == 0
            and result[1]['end'] == directory_size, 'incorrect ROMDIR self extent')
    extinfo = next((e for e in result if e['name'] == 'EXTINFO'), None)
    require(extinfo is not None and extinfo['end'] - extinfo['offset'] == ext_size,
            'IOPRP extended information size mismatch')
    return result
