"""Small helpers for reading the subsegments in a Splat config.

A Splat config splits each code segment into subsegments, one for each piece
of the file (a source unit's .text, its .rodata, a block of data, and so on).
They come in two shapes. Most are a short list:

    - [0x27280, databin, data_0036F600]

and the ones that need extra options are a dictionary:

    - start: 0x27300
      type: .rodata
      name: text_003483C0
      linker_section: .rodata.0036F680

The helpers here read either shape, so the rest of the build doesn't have to care.
"""

from pathlib import Path


def subsegment_parts(segment):
    """Return the start, type, and name of a subsegment in either shape."""
    if isinstance(segment, dict):
        return segment['start'], segment['type'], segment.get('name')
    if isinstance(segment, list) and len(segment) == 3:
        return tuple(segment)
    raise ValueError('expected a named Splat subsegment')


def segment_start(segment):
    return segment['start'] if isinstance(segment, dict) else segment[0]


def subsegment_end(subsegments, index, next_segment):
    """Where a subsegment ends: at the next one's start, or the next segment's for the last one."""
    following = subsegments[index + 1] if index + 1 < len(subsegments) else next_segment
    return segment_start(following)


def configured_rodata_groups(config, unit):
    """Read the jump table islands a source unit owns from the config.

    These are the unit's .rodata subsegments with `rodata_anchors`. See
    rodata_ownership.py for what they're for. Each comes back as a group with
    its linker section, original address, size, and anchors. A unit with no
    anchors at all returns an empty list, but if any of its islands has them,
    every one has to.
    """
    name = Path(unit).relative_to(config['options']['src_path']).with_suffix('').as_posix()
    groups = []
    segments = config['segments']
    # The last segment only marks where the file ends.
    for number, segment in enumerate(segments[:-1]):
        if not isinstance(segment, dict) or segment.get('type') != 'code':
            continue
        subsegments = segment['subsegments']
        owned = [(index, subsegment) for index, subsegment in enumerate(subsegments)
                 if subsegment_parts(subsegment)[1:] == ('.rodata', name)]
        if not any(isinstance(subsegment, dict) and 'rodata_anchors' in subsegment for _, subsegment in owned):
            continue
        for index, subsegment in owned:
            if not isinstance(subsegment, dict) or not subsegment.get('rodata_anchors'):
                raise ValueError(f'{unit}: all owned rodata islands need function anchors')
            # The island needs its own section name, and linker_section_order
            # tells Splat to place it along with the rest of the .rodata.
            selector = subsegment.get('linker_section', '')
            if not selector.startswith('.rodata.') or subsegment.get('linker_section_order') != '.rodata':
                raise ValueError(f'{unit}: an owned rodata island needs a distinct linker selector')
            size = subsegment_end(subsegments, index, segments[number + 1]) - subsegment['start']
            if size <= 0:
                raise ValueError(f'{unit}: invalid native rodata island extent')
            # Subsegment starts are file offsets, so this turns one into the address the game loads it at.
            address = segment['vram'] + subsegment['start'] - segment['start']
            groups.append({'section': selector, 'address': address, 'size': size,
                           'anchors': subsegment['rodata_anchors']})
    if len({group['section'] for group in groups}) != len(groups):
        raise ValueError(f'{unit}: duplicate native rodata island selector')
    return groups
