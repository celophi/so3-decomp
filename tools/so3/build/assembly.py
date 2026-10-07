"""Assemble source units that contain only assembly placeholders."""

import json
from pathlib import Path
import re
import subprocess
import tempfile


SOURCE_TOKEN = re.compile(
    r'\s+|/\*.*?\*/|//[^\n]*|'
    r'(?P<header>#[ \t]*include[ \t]+"include_asm.h"[ \t]*(?=\r?$))|'
    r'INCLUDE_ASM\s*\(\s*"(?P<folder>[^"\\\r\n]+)"\s*,\s*(?P<name>[\w.$]+)\s*\)\s*;',
    re.MULTILINE | re.DOTALL,
)


def assembly_inputs(source):
    """Return ordered assembly files, or None if the unit needs the compiler.

    Only the standard placeholder header, comments, and INCLUDE_ASM statements
    are accepted. Declarations, other headers, and preprocessor branches keep
    the unit on its normal compiler path.
    """
    content = source.read_text()
    files = []
    header = False
    position = 0
    while position < len(content):
        token = SOURCE_TOKEN.match(content, position)
        if token is None:
            return None
        if token.group('header'):
            if content[content.rfind('\n', 0, position) + 1:position].strip():
                return None
            header = True
        elif token.group('folder'):
            files.append(Path(token.group('folder')) / (token.group('name') + '.s'))
        position = token.end()
    return files if header and files else None


def assemble(files, macros, output):
    """Assemble the requested bodies in source order, keeping their relocations."""
    quote = lambda path: json.dumps(str(path.resolve()), ensure_ascii=False)
    with tempfile.NamedTemporaryFile(mode='w', suffix='.s', dir=output.parent) as source:
        source.write(f'.include {quote(macros)}\n.section .text, "ax"\n')
        for path in files:
            source.write(f'.include {quote(path)}\n')
        source.flush()
        subprocess.run(['mips-ps2-decompals-as', '-EL', '-march=r5900', '-mabi=eabi',
                        '-no-pad-sections', '-I', str(macros.parent),
                        '-o', str(output), source.name], check=True)
