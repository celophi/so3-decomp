#!/usr/bin/env python3
"""List the places where text_order.py still has to fix up C++ copies.

The compiler puts a copy of each inline function into every file that uses it,
and the game kept only one. text_order.py drops the extra copies and moves
misplaced ones. Each time it does, compile.py writes it down, and this script
gathers those into build/copy-report.json:

- `moved`: a copy had to be moved, so that file's source differs.
- `kept_later`: MWLDPS2 would keep the wrong copy on its own.
- `kept_by_placeholder`: the kept copy is still assembly.
- `kept_in_another_module`, `kept_outside`: the kept copy is elsewhere.

When the first three are empty, the linker can handle the copies itself.
"""

import argparse
from collections import defaultdict
import json
from pathlib import Path
import re

from tools.so3.build.compile import module_of

# INCLUDE_ASM("folder", name);
INCLUDE_ASM = re.compile(r'INCLUDE_ASM\("[^"\n]+",\s*([\w.$@]+)\);')


def placeholders(sources):
    """Every function each module's sources still pull in as assembly, by module."""
    names = defaultdict(set)
    for source in sources:
        path = Path(source)
        if path.is_file():
            names[module_of(source)].update(INCLUDE_ASM.findall(path.read_text()))
    return names


def build_report(records):
    """Sort the per-object records into the report's lists."""
    report = {'moved': [], 'kept_later': [], 'kept_by_placeholder': [], 'kept_in_another_module': [],
              'kept_outside': []}
    assembly = placeholders(record['source'] for record in records)
    dropped = 0
    for record in records:
        source = record['source']
        for copy in record['moved']:
            report['moved'].append({'source': source, **copy})
        for copy in record['dropped']:
            dropped += 1
            entry = {'source': source, **copy}
            if copy['kept_at'] is None:
                report['kept_outside'].append(entry)
                continue
            start, end = record['module_range']
            if not start <= copy['kept_at'] < end:
                report['kept_in_another_module'].append(entry)
                continue
            if copy['function'] in assembly[module_of(source)]:
                report['kept_by_placeholder'].append(entry)
            if copy['kept_at'] >= record['range'][1]:
                report['kept_later'].append(entry)
    for entries in report.values():
        entries.sort(key=lambda entry: (entry['source'], entry['function']))
    report['dropped'] = dropped
    return report


def summary(report):
    files = len({entry['source'] for entry in report['moved']})
    return (f"C++ copies: {len(report['moved'])} moved into place in {files} files; "
            f"{report['dropped']} dropped, of which {len(report['kept_later'])} are kept in a later file, "
            f"{len(report['kept_by_placeholder'])} by a placeholder, "
            f"{len(report['kept_in_another_module'])} in another module and "
            f"{len(report['kept_outside'])} outside every image")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('records', nargs='*', type=Path, help="compile.py's .copies.json files")
    parser.add_argument('--output', required=True, type=Path)
    args = parser.parse_args()
    report = build_report([json.loads(path.read_text()) for path in args.records])
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=1) + '\n')
    print(summary(report))


if __name__ == '__main__':
    main()
