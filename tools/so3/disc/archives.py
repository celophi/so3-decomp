"""Readers for the three kinds of container I've found on the discs.

Each reader only lists what's inside a container: where each member starts and
ends. It never copies anything out. Every offset is checked against the
container's own size, so a member can never reach outside it. If a container
doesn't look exactly like the ones I've seen, I stop instead of guessing.

- PACK is a directory followed by its members, back to back.
- ZLS is a chain of wrappers, each with a link forward to the next and back to
  the one before, ending with a DNE wrapper.
- IOPRP is the image the game uses to replace the PS2's IOP modules (the
  code for its input/output processor). It starts with a ROMDIR directory.
"""

import struct

from ..formats import require

# PACK: "PACK", a version, and a member count, then an (offset, tag) pair for
# each member. A member runs until the next one starts, and the last one runs
# to the end of the container.
PACK_MAGIC = b'PACK'
PACK_HEADER = struct.Struct('<4sHH')
PACK_ENTRY = struct.Struct('<II')

# ZLS: each wrapper is "ZLS\0", the payload size, the distance back to the
# previous wrapper, and the distance forward to the next one, then the payload.
ZLS_MAGIC = b'ZLS\0'
ZLS_END = b'DNE\0'
ZLS_WRAPPER = struct.Struct('<4sIII')

# IOPRP: the ROMDIR is a list of 16-byte entries (a name, the size of the
# member's extra info, and the member's size), ending with an all-zero entry.
# The first two entries describe RESET and the ROMDIR itself, and the members
# follow one another, each starting on a 16-byte boundary.
ROMDIR_ENTRY = struct.Struct('<10sHI')
RESET_NAME = b'RESET\0\0\0\0\0'
ROMDIR_NAME = b'ROMDIR\0\0\0\0'
ROMDIR_ALIGNMENT = 16
# The smallest directory: RESET, ROMDIR, and the end marker.
ROMDIR_MIN_SIZE = 3 * ROMDIR_ENTRY.size
# The extra info for every member is kept together in this member.
EXTINFO = 'EXTINFO'


def pack_entries(data):
    """List the members of a PACK whose members are stored inside it.

    Some files start with PACK but are really an index into some other file,
    with offsets that point outside this one. Those fail here, which is how
    inventory.py knows to leave them alone.
    """
    require(len(data) >= PACK_HEADER.size and data[:len(PACK_MAGIC)] == PACK_MAGIC, 'invalid PACK header')
    _, version, count = PACK_HEADER.unpack_from(data)
    require(version == 0, 'unsupported PACK version')
    directory_end = PACK_HEADER.size + count * PACK_ENTRY.size
    require(directory_end <= len(data), 'PACK directory exceeds container')
    entries = [PACK_ENTRY.unpack_from(data, PACK_HEADER.size + index * PACK_ENTRY.size) for index in range(count)]
    starts = [offset for offset, _ in entries] + [len(data)]
    require(all(directory_end <= start <= end <= len(data) for start, end in zip(starts, starts[1:])),
            'PACK offsets are not bounded inline members (possible external index)')
    return [{'index': index, 'offset': start, 'end': end, 'tag': tag}
            for index, ((start, tag), end) in enumerate(zip(entries, starts[1:]))]


def zls_entries(data):
    """Follow a ZLS chain to its DNE wrapper and list each payload.

    Every wrapper's link back has to match the step I took to reach it, so a
    broken chain gets caught.
    """
    offset = previous_step = 0
    result = []
    while True:
        require(offset + ZLS_WRAPPER.size <= len(data), 'truncated ZLS wrapper')
        magic, size, back, step = ZLS_WRAPPER.unpack_from(data, offset)
        require(back == previous_step, 'incorrect ZLS backward stride')
        if magic == ZLS_END:
            require(size == step == 0, 'invalid ZLS terminator')
            return result
        require(magic == ZLS_MAGIC, 'invalid ZLS signature')
        payload = offset + ZLS_WRAPPER.size
        require(0 < size <= len(data) - payload, 'ZLS payload exceeds container')
        require(step >= ZLS_WRAPPER.size + size and offset + step + ZLS_WRAPPER.size <= len(data),
                'invalid ZLS forward stride')
        result.append({'index': len(result), 'offset': payload, 'end': payload + size, 'wrapper_offset': offset})
        previous_step = step
        offset += step


def align(value, alignment):
    return (value + alignment - 1) & ~(alignment - 1)


def ioprp_entries(data):
    """List the members of an IOPRP image, using the ROMDIR at its start."""
    reset = data[:len(RESET_NAME)]
    romdir = data[ROMDIR_ENTRY.size:ROMDIR_ENTRY.size + len(ROMDIR_NAME)]
    require(len(data) >= ROMDIR_MIN_SIZE and reset == RESET_NAME and romdir == ROMDIR_NAME,
            'unsupported IOPRP ROMDIR placement')
    # The ROMDIR entry's size is the size of the directory itself.
    directory_size = ROMDIR_ENTRY.unpack_from(data, ROMDIR_ENTRY.size)[2]
    require(ROMDIR_MIN_SIZE <= directory_size <= len(data) and directory_size % ROMDIR_ENTRY.size == 0,
            'invalid IOPRP directory size')
    result = []
    offset = extinfo_total = 0
    terminated = False
    for position in range(0, directory_size, ROMDIR_ENTRY.size):
        raw_name, extinfo_size, size = ROMDIR_ENTRY.unpack_from(data, position)
        if raw_name == bytes(len(raw_name)):
            # The end marker, and everything after it in the directory, has to be zero.
            require(extinfo_size == size == 0 and not any(data[position:directory_size]), 'invalid ROMDIR terminator')
            terminated = True
            break
        name = raw_name.split(b'\0', 1)[0].decode('ascii')
        require(name and all(character.isalnum() or character == '_' for character in name), 'invalid IOPRP member name')
        require(offset + size <= len(data), 'IOPRP member exceeds image')
        require(name not in {entry['name'] for entry in result}, 'duplicate IOPRP member')
        result.append({'name': name, 'offset': offset, 'end': offset + size, 'extinfo_size': extinfo_size})
        offset += align(size, ROMDIR_ALIGNMENT)
        extinfo_total += extinfo_size
    require(terminated, 'unterminated IOPRP directory')
    # RESET takes no space, and the ROMDIR member is the directory I just read.
    require(result[0]['end'] == 0 and result[1]['offset'] == 0 and result[1]['end'] == directory_size,
            'incorrect ROMDIR self extent')
    extinfo = next((entry for entry in result if entry['name'] == EXTINFO), None)
    require(extinfo is not None and extinfo['end'] - extinfo['offset'] == extinfo_total,
            'IOPRP extended information size mismatch')
    return result
