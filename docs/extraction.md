# Extracting the game

A normal ISO extractor only shows three files on these discs: the boot
executable, `SYSTEM.CNF`, and `IOPRP271.IMG`. Most of SO3's resources are reached
through a hidden allocation table. Reading that table and decoding its compressed
blocks provides the overlays used by the build.

The extractor uses pycdlib for the visible ISO filesystem and project code for
the SO3 formats. It checks the input and decoded output as it goes, so a bad
extraction doesn't quietly become the reference for a matching function.

## Running extraction

With the development image built, run these from the host:

```sh
make extract ISO="/path/to/disc1.iso"
make extract ISO="/path/to/disc2.iso"
```

Each command mounts the selected ISO read-only and writes into `disc/<version>/`.
`make shell` only mounts the checkout, so use the host Make command to provide
an ISO outside it. The image itself contains no game files.

If you just want to run the extraction tools without Docker, use Python 3.10 or
newer with virtual environment support:

```sh
python3 -m venv .venv
.venv/bin/python -m pip install --require-hashes -r requirements.txt
.venv/bin/python -m tools.so3.disc.extract "/path/to/disc1.iso"
.venv/bin/python -m tools.so3.disc.extract "/path/to/disc2.iso"
```

Both routes use the same extractor. It checks the entire ISO hash on every run
and doesn't modify the image. Output is written into a temporary directory and
moved into place after the checks pass. If something fails, that temporary
output is removed; where possible, the error identifies the affected resource.
An existing destination is never overwritten.

## Supported discs

[config/versions.json](../config/versions.json) contains profiles for the two
supported North American revision 1.00 images:

| Profile | Disc size in bytes | Boot executable | Populated table entries |
| --- | ---: | --- | ---: |
| `us-disc1` | 4,658,429,952 | `SLUS_204.88` | 5,883 |
| `us-disc2` | 4,658,692,096 | `SLUS_208.91` | 5,716 |

Each profile records the full-disc SHA-256, size, boot and table hashes,
populated entry count, SLE key, and selected decoded reference hashes. These
identify the images I've checked. A different dump with the same release
label may still have different bytes and will fail verification. Adding another
image means adding a reviewed profile and checking its extracted results.

## Output

| Path under `disc/<version>/` | Contents |
| --- | --- |
| `iso/` | The three files exposed by ISO9660 |
| `resources/` | The hidden table and original allocations containing recovered code or reference samples |
| `modules/` | Decoded ELF and MWo3 modules, named by resource and block index |
| `checks/` | Decoded samples used to validate extraction |
| `manifest.json` | Disc identity, resource inventory, hashes, and module metadata |

The manifest keeps the original module names, but those names aren't used as
output paths. ELF files are saved whole, including any symbols and debugging
sections. A hidden allocation that contains the visible boot ELF points back
to that file in the manifest to avoid counting it twice.

The normal extraction pass handles top-level resources. It records nested
`PACK`, `ZLS`, and unknown blocks without recursively opening them. A separate
inventory tool follows the supported nested formats:

```sh
make inventory ISO="/path/to/disc1.iso"
make inventory ISO="/path/to/disc2.iso"
```

That tool checks the full ISO hash too. It writes reports and recovered code
under `build/inventory/<version>/`, leaving the extraction tree alone. The
[overlay notes](overlays.md#nested-archive-audit) explain what it found and what
is still unresolved. Neither tool extracts every asset or rebuilds a disc image.

## The visible filesystem

[pycdlib](https://clalancette.github.io/pycdlib/) handles ISO9660 traversal,
directory records, and file extraction. Version 1.21.0 and its wheel and source
archive hashes are pinned in [requirements.txt](../requirements.txt).

Output filenames drop the ISO version suffix, such as `;1`. The manifest still
records the original ISO path and byte offset. Unsafe names and collisions are
rejected rather than used as filesystem paths.

## The hidden resource table

The table starts at `0x200000`, has signature `0x27D51556`, and contains three
parallel arrays of 6,144 little-endian 32-bit words. They hold logical block
addresses, sector counts, and a word related to runtime behavior. Decoding uses
the seed `0x13578642`. Once decoded, entry zero's LBA points to the table itself.

Sectors are `0x800` bytes. The reader uses ordinary Python integers for physical
offsets and lengths, including offsets above 4 GiB. Every populated allocation
must fit inside the ISO and must not overlap another allocation. The populated
entry count includes the table's own allocation.

I haven't confirmed the meaning of every runtime word yet. The manifest
keeps it as `runtime_word`; overlay load addresses come from the `MWo3` headers.
Using one as the other would turn an assumption into a memory map.

## Compression and encryption

SLZ and SLE blocks start with a 16-byte header: a three-byte signature, one-byte
type, compressed payload length, decoded length, and relative offset to the next
block. A zero next-block offset ends the chain.

| Type | Decoding |
| --- | --- |
| 0 | Stored bytes |
| 1 | Byte literals and LZ backreferences; a zero-distance token ends the stream |
| 2 | Byte literals, LZ backreferences, and repeated-byte runs; stops at the declared output size |
| 3 | Halfword literals and LZ backreferences; a zero-distance token ends the stream |

SLE first transforms the compressed payload, then uses the same decoder:

```text
plain[i] = ((cipher[i] - 3 * (i + 1)) & 0xff) XOR key[i % 16]
```

The key is in each release profile. The key documented for PAL also decoded the
three top-level SLE entries on both supported US discs. Resource `1068/0`
reproduced the published reference SHA-256 for its 9,008-byte `PACK` output.
The extractor can use that verified key without recovering one at runtime.

The decoder checks input and output bounds, backreference distances, complete
payload consumption, declared output size, and forward movement through block
chains. Gaps between blocks and padding at the end of an allocation are kept
separate from the compressed payload. Unsupported types and outputs larger than
32 MiB produce an error.

Every top-level SLZ/SLE resource is decoded and recorded, including assets.
Allocations containing an ELF, an `MWo3` overlay, or a configured reference sample
are saved. Other decoded blocks are hashed and inventoried without writing all
of their contents to disk.

## Module metadata

For ELFs, the manifest records entry addresses, load segments, section names and
sizes, compiler comments when available, and IOP module names. For Metrowerks
overlays it records the ID, original name, load address, text/data/BSS sizes,
and initializer range.

These records describe the recovered modules. They don't establish that every
code-bearing resource has been found. Unknown containers and unresolved archive
references still need investigation, and extracted code is still original input
rather than reconstructed source.

## Checking repeatability

Manifests have deterministic ordering and contain no timestamps or absolute host
paths. They record the extraction schema, extractor and pycdlib versions, and
a hash of the release profile. Files and decoded blocks use SHA-256 hashes.

To repeat an extraction, choose a new ignored output directory and compare it
with the first one:

```sh
make extract ISO="/path/to/disc1.iso" OUTPUT=disc/recheck-us-disc1
diff -qr disc/us-disc1 disc/recheck-us-disc1
```

You can check the native Python path against the container in the same way:

```sh
.venv/bin/python -m tools.so3.disc.extract "/path/to/disc1.iso" \
  --output disc/native-us-disc1
diff -qr disc/us-disc1 disc/native-us-disc1
```

Repeat for Disc 2 with its image and `us-disc2` directories. Inventory also
accepts `OUTPUT=` if you want to repeat an audit without replacing an old report.

Run the tool tests with `make test`, or use the native environment:

```sh
.venv/bin/python -m unittest discover -s tools/so3/tests -v
```

The tests use synthetic ISO files and compressed streams, so they don't need
original game data. They cover all four compression types, SLE, overlapping LZ
copies, repeated-byte runs, chains, offsets above 4 GiB, malformed input, hash
rejection, existing output directories, and cleanup after failure. Compiler
integration tests also need the development image and `make compilers`; they
are skipped when those tools aren't available.

## Initial disc validation

Both supported discs passed extraction on 2026-09-29. Each produced three visible
files and 28 discovered code modules: one boot ELF, 12 IOP modules, and 15 MWo3
overlays. All 28 module hashes agree between the discs. Each pass decoded 1,640
top-level compressed resources into 2,861 blocks, checking full payload
consumption and declared output size for every block.

Repeated extractions produced identical trees, including the manifests. Each
tree had 50 files. The pinned container reproduced those same files from the
native extraction on both discs, with output owned by the invoking user.

The recursive audit then found 16 more IOP ELFs inside `IOPRP271.IMG`, bringing
the inventory to 44 modules per disc. It found the same 15 EE overlays and
recorded 28 unresolved PACK records along with opaque resources. Those remaining
formats leave code discovery unfinished.

## References

- [pycdlib API](https://clalancette.github.io/pycdlib/pycdlib-api.html) and [filesystem traversal](https://clalancette.github.io/pycdlib/example-walking-iso-filesystem.html).
- [SO3 hidden resource table](https://github.com/Starocean101/Star-Ocean-3-ps2-research-toolkit/blob/2db566d92070c55b537a270010123c3f606b74a8/docs/disc-layout/HIDDEN_RESOURCE_TABLE.md).
- [SLZ/SLE research](https://github.com/Starocean101/Star-Ocean-3-ps2-research-toolkit/blob/2db566d92070c55b537a270010123c3f606b74a8/docs/compression/SLZ_AND_SLE.md) and [key recovery](https://github.com/Starocean101/Star-Ocean-3-ps2-research-toolkit/blob/2db566d92070c55b537a270010123c3f606b74a8/docs/key-recovery/SLE_KEY_RECOVERY.md).
- [Metrowerks overlay header discussion](https://github.com/chaoticgd/ghidra-emotionengine-reloaded/issues/57).

The SO3 readers here implement the observed formats. The research toolkit was
used as a reference; its implementation hasn't been copied into this project.
