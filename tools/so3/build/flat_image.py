#!/usr/bin/env python3
"""Write a module's image from what MWLDPS2 linked.

MWLDPS2 writes an ELF file with one section for each memory region in the
command file (see lcf.py). The image is the module's regions back to back, in
address order, which is how they sit in the game's file. The `elsewhere`
region holds things that don't belong in the module, like the exception
tables, so it's left out.

For an overlay that's just one region. The main program has two: its ELF
header at address 0, then its code.
"""

import argparse
from pathlib import Path

from tools.so3.build.elf import SHF_ALLOC, SHT_PROGBITS, section_headers, section_names
from tools.so3.build.lcf import ELSEWHERE_REGION


def image(data):
    """The module's regions from a linked ELF file, back to back in address order."""
    headers = section_headers(data)
    regions = [header for name, header in zip(section_names(data, headers), headers)
               if header.type == SHT_PROGBITS and header.flags & SHF_ALLOC and name != ELSEWHERE_REGION]
    return b''.join(data[header.offset:header.offset + header.size]
                    for header in sorted(regions, key=lambda header: header.address))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('elf', type=Path, help="MWLDPS2's linked output")
    parser.add_argument('output', type=Path)
    args = parser.parse_args()
    args.output.write_bytes(image(args.elf.read_bytes()))


if __name__ == '__main__':
    main()
