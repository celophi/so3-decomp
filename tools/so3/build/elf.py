"""The parts of the ELF format the build scripts need to read MWCC's objects.

MWCC writes 32-bit little-endian MIPS ELF objects. A few of the build scripts
read or rewrite them directly, so they share the names here instead of each
using bare numbers. I kept the names from the ELF spec, so they're easy to look
up: https://refspecs.linuxfoundation.org/elf/gabi4+/contents.html
"""

from collections import namedtuple
import struct

# The ELF header.
ELF_HEADER_SIZE = 52
ELF32_LITTLE_ENDIAN = b'\x7fELF\x01\x01\x01'  # The magic, then 32-bit, little-endian, version 1.
E_TYPE = 16  # Where the header keeps the file type, then the machine.
E_SHOFF = 32  # Where it keeps the section header table's offset.
E_SHENTSIZE = 46  # Where it keeps one section header's size, then their count and the names section.
ET_REL = 1  # A relocatable object (a .o file), not a linked program.
EM_MIPS = 8

# Section types.
SHT_NULL = 0
SHT_PROGBITS = 1  # A section with real contents, like .text or .rodata.
SHT_SYMTAB = 2
SHT_STRTAB = 3
SHT_RELA = 4
SHT_NOBITS = 8  # Takes up memory but has no bytes in the file, like .bss.
SHT_REL = 9
SHT_DYNSYM = 11
SHT_SYMTAB_SHNDX = 18
SHF_ALLOC = 2  # The section is loaded into memory.

# Special section indexes a symbol can have instead of a real section.
SHN_ABS = 0xFFF1
SHN_COMMON = 0xFFF2

# Symbol types, kept in the low four bits of st_info.
STT_FUNC = 2
STT_SECTION = 3
SYMBOL_TYPE_MASK = 0xF

# The MIPS relocation types MWCC uses for data and jump tables.
R_MIPS_32 = 2  # A whole 32-bit address.
R_MIPS_HI16 = 5  # The high half of an address, for lui.
R_MIPS_LO16 = 6  # The low half, for addiu or a load.

SECTION_HEADER = struct.Struct('<10I')
SYMBOL = struct.Struct('<IIIBBH')
REL = struct.Struct('<II')

SectionHeader = namedtuple('SectionHeader', 'name type flags address offset size link info alignment entry_size')
Symbol = namedtuple('Symbol', 'name value size info other section')


def section_table(data):
    """Where the section headers are: (offset, size of one header, count, index of the names section)."""
    offset = struct.unpack_from('<I', data, E_SHOFF)[0]
    entry_size, count, names_index = struct.unpack_from('<HHH', data, E_SHENTSIZE)
    return offset, entry_size, count, names_index


def section_headers(data):
    offset, entry_size, count, _ = section_table(data)
    return [SectionHeader(*SECTION_HEADER.unpack_from(data, offset + index * entry_size)) for index in range(count)]


def symbol_type(info):
    return info & SYMBOL_TYPE_MASK


def relocation_type(info):
    """A REL entry's r_info packs the relocation type in the low byte and the symbol index above it."""
    return info & 0xFF


def relocation_symbol(info):
    return info >> 8
