# Research

## Compiler

I think SO3 was built with CodeWarrior for PS2. I'm using **3.0 build 52
(July 22, 2003)** with these flags for now:

```text
-O3,p -RTTI off -inline level=4
```

That gets matching code from the functions I've worked on, but I haven't
pinned down the exact original version yet.

I compared 15 compiler versions using five small functions from the main
executable. Builds 38, 50, and 52 all matched with both `-O3,p` and `-O4,p`.
Those tests only cover 272 bytes, so they don't give me enough to choose
between them. `-O3,p` is the current choice for optimizing for speed.

The C++ code in Field gives me a better idea of the other settings:

- `-RTTI off` disables runtime type information. Field's virtual function
  tables have empty type-information pointers, which agrees with this setting.
- `-inline level=4` lets the compiler copy small functions into their callers
  four levels deep. Some destructors need that extra level to match. Another
  function matches at level 4 but fails at level 8, so simply turning it up
  further doesn't help.
- C++ exceptions appear to have been enabled. The exception records produced
  for the functions I've checked match the game's, so I'm leaving them on.

There's one awkward detail: the main executable contains the string
`MW MIPS C Compiler (2.4.1.01)`, while the three matching compiler builds write
`3.0.0`. Several older releases write the same `2.4.1.01` string. It could
have come from an older library or linker, but I don't know yet.

I'm using PS2 GNU binutils to assemble and link the rebuild. I haven't
identified the original linker. Field's class and exception tables live in
the main executable even though they refer to overlay code, which suggests
the original build linked the code together before separating the overlays.

The next useful step is to compare more complex functions across the three
remaining candidates, especially C++ and floating-point code. The SDK
libraries and IOP code may have used different tools too.

The compiler versions and current flags are in
[config/manifests/compilers.json](../config/manifests/compilers.json). `make compiler-probe` checks
the current candidate; `make compiler-matrix` runs the full comparison.

## Field and Battle modules

The disc has two copies of both the Field and Battle programs:

| Module | Name in its header | Load address |
| --- | --- | --- |
| `1067-00` | `y` | `0x1DD380` |
| `3454-00` | `i` | `0x1DD380` |
| `1070-00` | `Field.bin` | `0x1E2B00` |
| `3253-00` | `BattleMain.ovl` | `0x1E2B00` |

I think the game only uses the first two. `boot.bin` loads archive entry 1067,
Field 1067 loads Battle 3454, and Battle 3454 goes back to 1067. I couldn't
find anything that loads 1070 or 3253, either by entry number or by name, so
they look like leftovers from an older build. Both discs carry the same copies.

I haven't confirmed this while the game is running, and something could still
compute those entry numbers. If it holds up, the two unused modules are 3.28 MB
of the 8.59 MB of code that progress currently counts.


## Sony SDK in Lib.bin

`0002-01` (`Lib.bin` in its header) is mostly tri-Ace code shared by the
other modules: C++ classes with CodeWarrior vtables and exception records,
the memory card save code (it uses `So3Sys.ico`, `So3Btl.ico` and `icon.sys`),
and character data. It also contains Sony's MPEG decoder library, `libmpeg`,
and the IPU library it runs on, `libipu`.

The game was linked against SDK 2.7. Sony libraries carry version tags, and
every tag in the executable and in `Lib.bin` matches the 2.7.2 runtime:
`libcdvd`, `libdbc`, `libkernl`, `libmc` and `libpad2` are 2710; `libdma`,
`libgraph` and `libipu` are 2700.

Certain:

- `libmpeg` and `libipu` occupy **0x3E6900-0x3EEB50** in `Lib.bin`. I compared
  every linked member of the 2.7.2 `libmpeg.a` and `libipu.a` with the original
  module, masking relocated fields. Each member's whole `.text` matches
  contiguously, in archive order, with only zero padding for 8-byte function
  alignment between members: mpc.o, csc.o, bit.o, pack.o, mpeg.o, init.o,
  defhandler.o, libipu.o, ipuinit.o.
- All 404 internal calls land on the matched functions, and all 53 address
  references to data land on the matched data sections: `.data` at
  0x4EB700-0x4EB980, `.rodata` (the decoder strings) at 0x501780-0x501C8B,
  and `mpc.o`'s `.bss` at 0x507A00.
- `etc.o` (`_zeroBlockRAW16`) isn't linked. No other 2.7.2 library appears in
  `Lib.bin`. As a control, SDK 3.0's `libmpeg` matches only 17 of 127
  functions.
- The 149 functions carry their Sony names in the symbol map. The two static
  `setD4_CHCR` functions (one each in `libipu.o` and `ipuinit.o`) keep their
  addresses, `func_003EE598` and `func_003EE8B0`, because the name isn't unique.
  The range is split into `src/overlays/0002-01/sdk/libmpeg_003E6900.c` and
  `libipu_003EE520.c` and excluded from progress through
  `config/manifests/sdk-functions.json`. An earlier C version of
  `sceMpegDelete` was returned to assembly.

Ratchet & Clank's decomp reached the same library independently: all 32
decoder strings here, including Sony's typos ("modion type", "picure",
"sutructure"), are in its `libmpeg` too.

Not settled yet:

- `mpeg.o`'s only data is the 16-byte tag `PsIIlibmpeg 2700`, and it isn't in
  `Lib.bin`; zeros fill that spot before `var.o`'s data. I think the linker
  dropped it because nothing references it, but I haven't proved that.
- The library calls 11 functions in the executable. The reference objects
  name them `AddDmacHandler2`, `RemoveDmacHandler`, `DisableDmac`,
  `EnableDmac`, `FlushCache`, `DIntr`, `EIntr`, `scePrintf`, `__muldi3`,
  `memset` and `sprintf`. Those names come from relocations, not from matching
  the executable's code, so I haven't applied them. The syscall pattern labels
  agree for `FlushCache` and `RemoveDmacHandler`. For 0x121A80 the pattern
  label says `AddDmacHandler`, while `libipu` calls it `AddDmacHandler2`.
- `text_004095C0` also programs the IPU (around 0x416724-0x41832C) without
  being part of either library. It is probably the game's own movie code.
