"""Build a C file straight from its assembly when there's no C in it yet.

A lot of the C files are still nothing but INCLUDE_ASM placeholders for
functions I haven't decompiled. Running those through the compiler would only
hand the same assembly back, so compile.py asks this module first. If the file
really is just placeholders, I assemble the functions' .s files myself in the
same order and skip the compiler.

This also tidies up everything GNU as builds. It always adds .text, .data and
.bss sections, even when there's nothing in them, and MWLDPS2 (the original
linker) refuses empty ones, so I take those out. GNU ld doesn't care either
way. The build runs `python -m tools.so3.build.assembly OBJECT` after
assembling each data piece for the same reason.
"""

import argparse
import json
from pathlib import Path
import re
import subprocess
import tempfile

from tools.so3.build.elf import section_headers, section_names

# compile.py hands the same settings to mwccgap, so both paths assemble the
# same way. mwccgap adds -EL by itself.
ASSEMBLER = 'mips-ps2-decompals-as'
ASSEMBLER_CPU = 'r5900'  # The PS2's main CPU (the Emotion Engine).
ASSEMBLER_ABI = 'eabi'
# -mno-pdr leaves out the .pdr debugging section, which GNU ld throws away
# and MWLDPS2 refuses.
ASSEMBLER_FLAGS = ['-no-pad-sections', '-mno-pdr']
LITTLE_ENDIAN = '-EL'
OBJCOPY = 'mips-ps2-decompals-objcopy'
# The sections GNU as adds to every object, whether or not they hold anything.
DEFAULT_SECTIONS = ('.text', '.data', '.bss')

# The header that defines INCLUDE_ASM. A placeholder-only file has to include it.
PLACEHOLDER_HEADER = 'include_asm.h'

# The only things a placeholder-only file may contain: whitespace, comments,
# the placeholder header on its own line, and INCLUDE_ASM("folder", name);
# statements. I scan the file with this one token at a time. Anything it
# doesn't recognise means there's real code and the file needs the compiler.
SOURCE_TOKEN = re.compile(
    r'\s+|/\*.*?\*/|//[^\n]*|'
    rf'(?P<header>#[ \t]*include[ \t]+"{re.escape(PLACEHOLDER_HEADER)}"[ \t]*(?=\r?$))|'
    r'INCLUDE_ASM\s*\(\s*"(?P<folder>[^"\\\r\n]+)"\s*,\s*(?P<name>[\w.$]+)\s*\)\s*;',
    re.MULTILINE | re.DOTALL,
)


def starts_line(content, position):
    """Whether only whitespace comes before this position on its line."""
    line_start = content.rfind('\n', 0, position) + 1
    return not content[line_start:position].strip()


def assembly_inputs(source):
    """Return the .s files a placeholder-only source needs, in order.

    Returns None when the file has anything else in it, like declarations,
    other headers, or #if blocks. Those files go through the compiler as usual.
    """
    content = source.read_text()
    files = []
    has_header = False
    position = 0
    while position < len(content):
        token = SOURCE_TOKEN.match(content, position)
        if token is None:
            return None
        if token.group('header'):
            if not starts_line(content, position):
                return None
            has_header = True
        elif token.group('folder'):
            files.append(Path(token.group('folder')) / f"{token.group('name')}.s")
        position = token.end()
    return files if has_header and files else None


def gas_string(path):
    """Quote a path for an .include line.

    The assembler reads the same backslash escapes as JSON. I keep non-ASCII
    characters as they are because it doesn't understand \\u escapes.
    """
    return json.dumps(str(path.resolve()), ensure_ascii=False)


def assemble(files, macros, output):
    """Assemble the functions in source order into one object.

    Each function's .s file is assembled whole, so its relocations stay the
    same as in the original.
    """
    with tempfile.NamedTemporaryFile(mode='w', suffix='.s', dir=output.parent) as wrapper:
        # The function bodies don't say which section they belong to, so the
        # wrapper puts them all in .text ("ax" means loaded and executable).
        wrapper.write(f'.include {gas_string(macros)}\n')
        wrapper.write('.section .text, "ax"\n')
        for path in files:
            wrapper.write(f'.include {gas_string(path)}\n')
        wrapper.flush()
        subprocess.run([
            ASSEMBLER, LITTLE_ENDIAN, f'-march={ASSEMBLER_CPU}', f'-mabi={ASSEMBLER_ABI}', *ASSEMBLER_FLAGS,
            # Lets the macro file find anything it includes next to it.
            '-I', str(macros.parent),
            '-o', str(output), wrapper.name,
        ], check=True)
    drop_empty_sections(output)


def drop_empty_sections(path):
    """Take out the default sections GNU as added to an object but left empty."""
    data = Path(path).read_bytes()
    headers = section_headers(data)
    empty = [name for name, header in zip(section_names(data, headers), headers)
             if name in DEFAULT_SECTIONS and header.size == 0]
    if empty:
        removals = [option for name in empty for option in ('--remove-section', name)]
        subprocess.run([OBJCOPY, *removals, str(path)], check=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('objects', nargs='+', type=Path, help='objects GNU as just built')
    for path in parser.parse_args().objects:
        drop_empty_sections(path)


if __name__ == '__main__':
    main()
