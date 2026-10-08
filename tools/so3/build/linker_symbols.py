"""Write the symbols marked absolute in the symbol maps as a linker script.

Some symbols a module uses live outside it at a fixed address, mostly in the
main executable, which stays loaded while the overlays run. In the symbol maps
I mark those with `absolute:True` in the line's comment, like:

    __dl__FPv = 0x00100D60; // type:func absolute:True

That tells Splat the symbol already exists, so it doesn't define one. The
linker still needs the address though, so this script collects them into a
small linker script with one `name = 0xADDRESS;` line each. driver.py adds that
script to the module's link with -T.
"""

import argparse
from pathlib import Path
import re

from tools.so3.build.text_order import SYMBOL_LINE

# The flag lives in the comment after //, among Splat's other attributes.
ABSOLUTE_FLAG = re.compile(r'\babsolute\s*:\s*True\b')


def absolute_symbols(paths):
    """Collect every symbol marked absolute across the maps, by name.

    A symbol can show up in more than one map, but it has to have the same
    address in each.
    """
    result = {}
    for path in paths:
        for line in Path(path).read_text().splitlines():
            match = SYMBOL_LINE.match(line)
            _, _, comment = line.partition('//')
            if not match or not ABSOLUTE_FLAG.search(comment):
                continue
            name, address = match.group(1), int(match.group(2), 16)
            if name in result and result[name] != address:
                raise ValueError(f'{name}: conflicting absolute symbol addresses')
            result[name] = address
    return result


def linker_script(symbols):
    return ''.join(f'{name} = 0x{address:X};\n' for name, address in sorted(symbols.items()))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--output', required=True, type=Path)
    parser.add_argument('maps', nargs='+', type=Path)
    args = parser.parse_args()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(linker_script(absolute_symbols(args.maps)))


if __name__ == '__main__':
    main()
