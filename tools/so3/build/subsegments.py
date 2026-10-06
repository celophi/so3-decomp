"""Read list and dictionary subsegments from Splat configurations."""

from pathlib import Path


def subsegment_parts(segment):
    """Return the start, type and name without discarding dictionary options."""
    if isinstance(segment, dict):
        return segment['start'], segment['type'], segment.get('name')
    if isinstance(segment, list) and len(segment) == 3:
        return tuple(segment)
    raise ValueError('expected a named Splat subsegment')


def segment_start(segment):
    return segment['start'] if isinstance(segment, dict) else segment[0]


def configured_rodata_groups(config, unit):
    """Recover one source unit's explicitly owned native jump-table islands."""
    name = Path(unit).relative_to(config['options']['src_path']).with_suffix('').as_posix()
    groups = []
    for number, segment in enumerate(config['segments'][:-1]):
        if not isinstance(segment, dict) or segment.get('type') != 'code':
            continue
        subs = segment['subsegments']
        owned = [(i, sub) for i, sub in enumerate(subs)
                 if subsegment_parts(sub)[1:] == ('.rodata', name)]
        if not any(isinstance(sub, dict) and 'rodata_anchors' in sub for _, sub in owned):
            continue
        for index, sub in owned:
            if not isinstance(sub, dict) or not sub.get('rodata_anchors'):
                raise ValueError(f'{unit}: all owned rodata islands need function anchors')
            selector = sub.get('linker_section', '')
            if not selector.startswith('.rodata.') or sub.get('linker_section_order') != '.rodata':
                raise ValueError(f'{unit}: an owned rodata island needs a distinct linker selector')
            end = segment_start(subs[index + 1]) if index + 1 < len(subs) else segment_start(config['segments'][number + 1])
            size = end - sub['start']
            if size <= 0:
                raise ValueError(f'{unit}: invalid native rodata island extent')
            groups.append({'section': selector, 'address': segment['vram'] + sub['start'] - segment['start'],
                           'size': size, 'anchors': sub['rodata_anchors']})
    if len({group['section'] for group in groups}) != len(groups):
        raise ValueError(f'{unit}: duplicate native rodata island selector')
    return groups
