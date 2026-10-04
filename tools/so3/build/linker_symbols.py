"""Export explicit absolute Splat symbols for the linker."""

import argparse
from pathlib import Path
import re

from tools.so3.build.text_order import SYMBOL_LINE

ABSOLUTE = re.compile(r'\babsolute\s*:\s*True\b')


def absolute_symbols(paths):
    """Collect resident addresses that Splat treats as already defined."""
    result = {}
    for path in paths:
        for line in Path(path).read_text().splitlines():
            match = SYMBOL_LINE.match(line)
            if not match or not ABSOLUTE.search(line.partition('//')[2]):
                continue
            name, address = match.group(1), int(match.group(2), 16)
            if name in result and result[name] != address:
                raise ValueError(f'{name}: conflicting absolute symbol addresses')
            result[name] = address
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', required=True, type=Path)
    parser.add_argument('maps', nargs='+', type=Path)
    args = parser.parse_args()
    symbols = absolute_symbols(args.maps)
    content = ''.join(f'{name} = 0x{address:X};\n' for name, address in sorted(symbols.items()))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(content)


if __name__ == '__main__':
    main()
