# Overlays and code inventory

The boot executable is only part of SO3's EE code. I've recovered 15 Metrowerks
`MWo3` overlays from the supported US discs, including Field, Battle, library,
and menu code. Together they account for 9,045,632 bytes of original files.
Each one has a Splat configuration, editable source placeholders, and a rebuild
that matches the original byte for byte.

Different overlays can load at the same address, so each gets its own source
and build directory. An address by itself isn't enough to identify a function
across the whole game.

## Building an overlay

After building the development image and extracting Disc 1:

```sh
make split
make build
make verify
```

Those commands cover boot and all configured overlays. For a single overlay,
open `make shell` and run:

```sh
python tools/overlays.py split --overlay 0002-01
python tools/overlays.py build --overlay 0002-01
python tools/overlays.py verify --overlay 0002-01
```

`split` generates files. `build` also compiles, assembles, links, and verifies
them. The original overlay hash and layout are checked before Splat runs or a
rebuild is compared. Verification covers the entire file, including retained
data, and checks the Disc 2 copy when it's available.

| Path | Contents |
| --- | --- |
| `config/overlays/<id>.yaml` | Original hashes and Splat layout |
| `src/overlays/<id>/text*.c`, `text*.cpp` | Main-code placeholders and future source matches |
| `src/overlays/<id>/init.c`, `init.cpp` | Initializer placeholders, where present |
| `build/overlays/<id>/asm/nonmatchings/<unit>/` | Generated assembly for individual functions |
| `build/overlays/<id>/bin/` | Original headers, data, initializer pointers, and unresolved payloads |
| `build/overlays/<id>/overlay.ld` | Generated linker layout |
| `build/overlays/<id>/rebuilt.bin` | Complete rebuilt MWo3 file |
| `build/overlays/<id>/verify.json` | Size, SHA-256, and comparison results |

[tools/build.py](../tools/build.py) generates `build/build.ninja` from the layouts
and source files. The build uses the pinned CodeWarrior candidate, mwccgap, and
PS2 binutils. No bytes are patched after linking to make a comparison pass.
Generated files stay under ignored `build/`.

Source files and tracked YAML define the split. Splat preserves existing
C/C++ files, but generated assembly can be overwritten. A change to a function
grouping needs corresponding changes in both the source and configuration.
Functions are replaced one at a time, with the complete overlay checked after
each build.

Field and Battle currently use `.cpp`; the other overlays use `.c`. That choice
is provisional, and the extensions don't establish the original language of
every function. C++ definitions that keep an address-based assembly name need
`extern "C"` linkage. The toolchain guide covers
[C++ support](toolchain.md#c-support) and
[replacing a placeholder](toolchain.md#replacing-a-placeholder).

## Overlay inventory

The IDs here identify resource/block positions. They aren't the ID field inside
the MWo3 header, which some files reuse. `y` and `i` are the names stored in
those headers; I haven't identified what they refer to yet.

| Resource/block | Header name | Runtime base | File bytes |
| --- | --- | --- | ---: |
| `0002-00` | `boot.bin` | `0x001DD380` | 166,528 |
| `0002-01` | `Lib.bin` | `0x003E6880` | 1,184,128 |
| `0067-00` | `cequip.bin` | `0x00348380` | 39,936 |
| `0068-00` | `cstatus.bin` | `0x00348380` | 37,504 |
| `0069-00` | `cskill.bin` | `0x00348380` | 117,632 |
| `0070-00` | `citem.bin` | `0x00348380` | 51,712 |
| `0071-00` | `cconfig.bin` | `0x00348380` | 43,904 |
| `0072-00` | `cmc.bin` | `0x00348380` | 77,952 |
| `0073-00` | `ctactics.bin` | `0x00348380` | 40,448 |
| `0074-00` | `cshop.bin` | `0x00348380` | 40,064 |
| `0075-00` | `citemcreation.bin` | `0x00348380` | 161,536 |
| `1067-00` | `y` | `0x001DD380` | 1,365,376 |
| `1070-00` | `Field.bin` | `0x001E2B00` | 1,449,344 |
| `3253-00` | `BattleMain.ovl` | `0x001E2B00` | 2,135,424 |
| `3454-00` | `i` | `0x001DD380` | 2,134,144 |

## File and runtime mapping

The 64-byte MWo3 header is part of the loaded file. To map a file offset to a
runtime address, add it directly to the header's load address:

```text
runtime_address = load_address + file_offset
```

The initializer pointers provide a useful check. `boot.bin` puts its initializer
list at `0x00205DC0`, which maps to file offset `0x28A40`. The word there points
to code at `0x00205D00`, or file offset `0x28980`. If you subtract the header
from this mapping, the list moves past the end of the file.

All recovered overlays satisfy:

```text
file_size = 0x40 + text_size + data_size
```

The header's text and data labels don't fully separate code from data. Six overlays have executable initializer routines
near the end of the declared data area. The configurations split those into
separate code regions:

| Overlay | Initializer code file range, end exclusive |
| --- | --- |
| `0002-00` | `0x28980` to `0x28A40` |
| `0002-01` | `0x120B00` to `0x1210D0` |
| `1067-00` | `0x14D500` to `0x14D540` |
| `1070-00` | `0x161D00` to `0x161D40` |
| `3253-00` | `0x208000` to `0x209520` |
| `3454-00` | `0x207A80` to `0x209030` |

These ranges start at the lowest initializer pointer and end at the initializer
list, with instruction inspection supporting the boundaries. In `Lib.bin`,
the main EE region ends at file offset `0x103780`; the following VU/data payload
is kept with the data. The other main splits follow the header's text end.

The 21 code regions are divided into 138 source files: 84 C and 54 C++. They
reference assembly covering 8,467,744 input bytes, including padding and raw
words. That byte count includes padding and raw data alongside instructions;
it doesn't measure unique code. Splat keeps instructions it can't represent as `.word`, and
internal data and VU boundaries still need to be separated.

BSS sizes remain in the original headers. BSS has no file bytes and isn't
emitted into a rebuilt overlay. The build uses the resident GP value
`0x001BDFF0`, but I haven't established the original compiler and linker
configuration for every module. Source groupings and function labels remain
working boundaries until more evidence turns up.

## Nested archive audit

The extraction pass finds top-level code. To look through supported nested
containers and the IOP reboot image, run:

```sh
make inventory ISO="/path/to/disc1.iso"
make inventory ISO="/path/to/disc2.iso"
```

The audit checks the full ISO hash and writes to `build/inventory/<version>/`.
`report.json` records module hashes, where each module was found, container
entries, opaque leaves, and unresolved containers. Recovered code is saved
alongside it. Use a new `OUTPUT=` directory for a repeat run; the tool won't
replace an existing report or modify the normal extraction tree.

The readers handle the layouts observed on these discs:

- Inline PACK directories have a version/count pair followed by offset/tag
  entries. Each member must fit inside the containing buffer. Tags are recorded
  as found because their meanings aren't all known.
- Some PACK records point outside their own buffers and appear to reference
  external data. They're recorded as unresolved, and the audit continues with
  the other members of the parent container.
- Resource 8 has four ZLS wrappers around SLZ2 streams. The reader checks payload
  size, forward and backward strides, and the `DNE\0` terminator.
- `IOPRP271.IMG` has a ROMDIR at offset zero and files aligned to 16 bytes. The
  reader checks directory bounds, file extents, and extended-information lengths.

The IOPRP directory supplies 16 IOP ELF modules beyond the 12 found in the
top-level pass: SYSMEM, LOADCORE, SIFCMD, SIFMAN, THREADMAN, IOMAN, MODLOAD,
FILEIO, CDVDMAN, CDVDFSV, LOADFILE, TIMEMANI, ROMDRV, EESYNC, SYSCLIB, and STDIO.
They've been extracted and inventoried, but aren't split or rebuilt yet.

Both supported discs completed the audit on 2026-09-29. Each traversal recorded
38,554 nodes, parsed 1,703 inline PACK directories, and examined 619 additional
SLZ/SLE containers. The resulting inventory has 44 code modules: one boot ELF,
15 MWo3 overlays, and 28 IOP ELFs. Their paths and hashes agree across the discs.
No additional EE overlays were found in the supported nested containers.

There are still 28 unresolved PACK records, all below resource 3455. Their
offsets fall outside their small member buffers, which is consistent with
external index tables, but the referenced data and tag meanings haven't been
established. There are also opaque leaves and unknown top-level resources.
I can't rule out more code just because those bytes don't have a recognized
module signature. The empty overlay slots in the boot ELF don't settle that
question either.

## Verification and remaining work

The boot and all 15 overlay rebuilds pass a complete byte comparison against
the originals. Verification checks include rejecting a one-byte change at
offset `0x80` in a copied overlay and rejecting a modified original before
Splat runs. The archive tests exercise bounds, ZLS chaining, IOPRP alignment,
and continued code discovery after unresolved PACK members. The
[toolchain checks](toolchain.md#checks-so-far) cover source compilation and
assembly regeneration.

The full-file comparison checks each function replacement. Original data
and unresolved VU payloads are still retained. Recompression, disc rebuilding,
and emulator testing haven't been implemented, and unknown archive formats
still need investigation before the code inventory can be considered complete.
