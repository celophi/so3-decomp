# Asset extractor proof of concept

The goal is to build an extractor for all of the game's data. Right now, this
is a proof of concept, and we're starting with `citemcreation`. We need to
understand the data those functions use before we can give the functions and
types useful names. That gives us a concrete first target while we build out
the extractor and document the formats along the way.

On US disc 1, resource 75 contains the `citemcreation` code overlay, and
resource 95 contains message banks with keys it uses, including `0x3458` and
`0x3584`. That gives us a starting point for connecting the data to the code.
We can extract those resources, parse the message structure, and show some
readable labels using the shared font in resource 8. For example, the glyph
codes for `0x3458` decode to `COOK`. The character mapping is still partial,
so messages can also contain markers for glyphs we haven't identified yet.

The resource and container readers already handle data across the disc. As we
work through more of the game, we'll add parsers for the formats we identify.
For now, data we don't understand is kept as raw bytes so we can come back to
it later. This document covers how to run the current tool, the layouts it can
parse, and the fields we still need to figure out.

## Running the extractor

Start with either supported, unmodified US disc:

```sh
make extract-assets ISO="/path/to/disc.iso"
```

By default, the files go into `assets/us-disc1/` or `assets/us-disc2/` at the
repository root. Git ignores `/assets/`. The output directory must not already
exist, and it only appears once extraction finishes successfully. If you want
to run it again, choose a new directory or move the previous extraction first.

You can also extract specific resources and choose where they go:

```sh
make extract-assets ISO="/path/to/disc.iso" RESOURCES="75 95" OUTPUT=assets/messages
python -m tools.so3.assets.src.extract /path/to/disc.iso --resource 95 --output assets/messages
```

`RESOURCES` takes **disc resource indices**. For example, `95` selects resource
95; it doesn't select a message with that key. Decimal and `0x` hexadecimal
indices both work. Leaving this option out extracts every resource that has
space allocated on the disc, including code and data we don't understand yet.
Expect this to use several GB. Resource zero is the resource table itself,
which gets saved separately on every run.

The extractor checks the complete ISO hash, table hash, and allocation bounds
against `config/manifests/versions.json`. The parser tests use generated test
data, so `make test` doesn't need any game binaries.

## Output

- `resource-table.bin`: the original encoded disc table.
- `resource-table.json`: its decoded allocation records, including runtime-only slots.
- `manifest.json`: extracted nodes, their hashes, formats, parents, and offsets.
- `resources/0095/data.bin`: the original resource allocation, including padding.
- `resources/0095/block-0000/data.bin`: a decompressed child.
- `resources/0095/block-0000/messages.json`: a parsed message bank.

Files inside PACK and ZLS containers go into `pack-NNNN` and `zls-NNNN`
directories. We keep the original container as well, so you can compare an
extracted file with the bytes it came from.

Offsets in `manifest.json` are relative to the file's immediate parent. When
the relationship is `decompressed`, that offset points to the compressed
payload in the parent. The child file contains the decoded bytes. To find a
top-level resource's disc offset and allocation size, use `resource-table.json`.

If we don't recognize a payload, it stays as `data.bin` with `status: opaque`.
Some PACK tables don't describe files inside the current container, and some
message-bank versions haven't been validated. Those get `status: unresolved`
and a reason. The extractor doesn't follow their offsets outside the data it
has available.

Malformed supported compression, ZLS chains, or message banks stop extraction
with an error identifying the resource or message key. A failed run doesn't
leave a partial output directory.

## Disc resource table

All numeric fields are little-endian. The resource table starts at byte offset
`0x200000` in the ISO, takes up `0x12000` bytes, and has `0x1800` slots. There
are three separate arrays. To read a slot, take the value at that index from
each array:

| Table offset | Contents | Element size |
| --- | --- | --- |
| `0x00000` | Encoded sector addresses | 4 bytes |
| `0x06000` | Encoded allocation sizes in sectors | 4 bytes |
| `0x0C000` | Encoded runtime words, meaning unresolved | 4 bytes |

`read_table` in `tools/so3/formats.py` decodes these arrays using the XOR key
progression we've identified. The first word is the signature `0x27D51556`,
so the reader reconstructs the table's own sector address. Each sector is
`0x800` bytes, which gives us:

```text
byte_offset     = sector_address * 0x800
allocated_bytes = sector_count   * 0x800
```

Some slots are only used at runtime and don't have any space allocated on the
disc. For slots that do, the allocation must fit inside the ISO and must not
overlap another allocation.

## Containers

The extractor uses the existing compression and archive readers. These check
that the declared sizes and offsets stay inside the containing data.

### SLZ and SLE blocks

| Header offset | Field | Size |
| --- | --- | --- |
| `0x00` | `SLZ` or `SLE` signature | 3 bytes |
| `0x03` | Compression kind, 0 through 3 | 1 byte |
| `0x04` | Compressed payload size | 4 bytes |
| `0x08` | Decoded size | 4 bytes |
| `0x0C` | Next-header displacement from this header; zero ends the chain | 4 bytes |
| `0x10` | Payload | Declared compressed size |

Kind zero stores the data without compression. The other kinds use the existing
LZ decoder. SLE also has an obfuscation step, which the reader reverses with the
key configured for that release before decompressing. Padding at the end of a
disc allocation isn't part of the compressed payload.

### Inline PACK

| Offset | Field | Size |
| --- | --- | --- |
| `0x00` | `PACK` | 4 bytes |
| `0x04` | Observed version, zero | 2 bytes |
| `0x06` | Member count | 2 bytes |
| `0x08` | Directory: member offset followed by an unresolved tag | 8 bytes per member |

Offsets are measured from the start of the PACK. Each member ends where the
next one starts, and the last member ends at the end of the containing buffer.
The offsets must come after the directory and must not decrease, though two
members can have the same offset.

Some tables have a PACK header but use offsets outside the containing data.
We don't have enough information to resolve those yet, so the extractor keeps
the original table and marks it unresolved.

### ZLS wrapper chain

Each sixteen-byte wrapper contains `ZLS\0`, the payload size, the distance to
the previous wrapper, and the distance to the next wrapper, in that order.
These distances are measured between wrapper starts, and the reader checks
them in both directions. `DNE\0` ends the chain with a zero payload size and
zero distance to the next wrapper. The payload can itself contain an SLZ/SLE
block or another supported container.

## so3mclib message banks

We currently support `so3mclib 1.75`, `so3mclib 1.80i`, and `so3mclib 1.81i`.
Their signatures are padded with zeros to sixteen bytes, and they share the
header and key-index layout shown below. Offsets are measured from the start
of the bank.

The game gives us two useful places to check this layout. `00465610` sets up
the runtime pointers from the header's offsets and counts. `00465340` searches
the key index and adds the selected message offset to the message-data pointer.
That means a pointer in the running game and an offset in the file are different
values, even when they refer to the same data.

| Header offset | Field | Size |
| --- | --- | --- |
| `0x00` | Signature/version | 16 bytes |
| `0x10` | Key-index offset | 4 bytes |
| `0x14` | Message-data offset | 4 bytes |
| `0x18` | Auxiliary table offset; role unresolved | 4 bytes |
| `0x1C` | Auxiliary table offset; role unresolved | 4 bytes |
| `0x20`-`0x38` | Seven metadata words; meanings unresolved | 4 bytes each |
| `0x3C` | Key-index entry count | 4 bytes |
| `0x40` | Declared bank size, observed in decoded banks | 4 bytes |

The key index contains eight-byte entries:

```text
u32 key
u32 offset_from_message_data
```

Font-only banks can have zero entries and zero offsets for the key index and
message data. The extractor still keeps their auxiliary sections, but there
won't be any messages in the exported list.

The keys are in increasing order, with no duplicates. The message offsets
don't follow the same rule. Multiple keys can point to the same data, and a
later key can point to an earlier offset.

This matters because the entries don't include a message length. We can't just
subtract one offset from the next and call that the size. Instead, the parser
reads each message through its terminator, stopping with an error if it reaches
an auxiliary table or the end of the bank first. Header words and auxiliary
data we don't understand keep their original values and bytes.

### Message stream

`00465100` shows how the game walks through a message:

- A zero first byte ends the message.
- A first byte below `0x80` is a one-byte code.
- Otherwise, consume a second byte and compute
  `(first & 0x7F) | (second << 7)`.
- Codes with bit `0x4000` set are commands; other codes are glyph indices.
- Command parameters can contain zeros and must be consumed before looking
  for the message terminator.

The parser keeps each command's numeric code and raw parameter bytes. These are
the parameter lengths handled by `00465100`; the command codes below are hex:

| Commands | Parameter bytes consumed by `00465100` |
| --- | --- |
| `4002`, `4008`, `4012`, `4013`, `401A`, `401D`, `4020`-`4023` | 1 |
| `4005`, `4006`, `400A`, `400C`, `400E`, `4014`, `4015`, `401E` | 4 |
| `4011`, `401C` | Through an embedded zero terminator |
| Other command codes | No parameters in this traversal |

`messages.json` includes each key, its offsets, the bytes through the message
terminator, and the glyph runs and control tokens found in those bytes.

For verified US disc 1 banks that use the shared font, `messages.json` also
includes `text_preview`, `text_complete`, and `unmapped_glyphs`. Known characters
are decoded; unmapped glyphs and commands remain visible markers. Raw bytes
and tokens are retained. `text_mapping` identifies the partial mapping and its
source font bank. We haven't checked the shared font on US disc 2 yet, so that
disc still exports the numeric tokens without a text preview.

For example, a known label can appear as `COOK`. An unknown glyph appears as
`<glyph:0x12d>`, and a command appears as `<command:0x4002:00>`. The preview
is complete only when every glyph is mapped and there are no commands whose
effect on the displayed text still needs to be understood. We keep these
markers so an incomplete decode doesn't quietly turn into a plausible string.

The initial mapping covers digits, Latin letters, a few punctuation marks, and
the two space codes. These characters were identified from the extracted font
bitmaps. The renderer in `004645F0` uses one-based message codes, selects the
shared font for codes 1 through 300 when the bank's shared-font flag is set,
and selects the bank's own glyphs for codes 301 and above. The latter still
need separate mappings, as do banks that use their own font for every code.

For the current `citemcreation` work, the next step is to expand the character
mapping, identify the commands, and follow the message keys back to their callers.
We also need to identify which banks get loaded into which runtime slots.
That should give us better evidence for naming the functions and types than
the numeric keys alone.
