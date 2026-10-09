# Research

## Toolchain

This is what I think the game was built with:

| Part | Tool |
| --- | --- |
| Compiler | CodeWarrior for PS2 (MWCC), version 3.0 build 38, from March 7, 2003 |
| Linker | MWLDPS2, the linker that comes with CodeWarrior |
| CodeWarrior release | Something after R3.04, most likely R3.5 or R3.51 |
| Console libraries | Sony's SDK 2.7 (my copy is 2.7.2) |
| C library | newlib, built with GCC, from a Sony toolchain I haven't identified |

The compiler versions and current flags are in
[config/manifests/compilers.json](../config/manifests/compilers.json).
`make compiler-probe` checks the current version, and `make compiler-matrix`
compares all of them.

### Compiler

These are the flags:

```text
-O3,p -RTTI off -inline level=4
```

Builds 38, 50 and 52 all match five small functions from the main program,
with both `-O3,p` and `-O4,p`. That's only 272 bytes, so it doesn't tell them
apart. Jump tables do. When a switch statement's lowest case isn't 0, the code
subtracts it before looking up the table of addresses to jump to. The game
always does that with `addi` (64 tables, and none use `addiu`). Builds from
before May 2003 write `addi` and later ones write `addiu`, and build 38 is the
only one of those older builds that matches the rest of the game's code too.
Apart from that one instruction, every file in the project compiles the same
with builds 38 and 52.

The other settings come from Field's C++ code:

- `-RTTI off` turns off runtime type information. Field's virtual function
  tables have empty type-information pointers, which agrees with this setting.
- `-inline level=4` lets the compiler copy small functions into their callers
  four levels deep. Some destructors need that to match, and one function
  matches at level 4 but not at level 8.
- C++ exceptions are on. The exception records for the functions I've checked
  match the game's.

One file needs more. A destructor in Field's `text_001E6C50` sits on a chain of
six classes, and the game copies all five base destructors into it. Level 4
stops one short, so that file gets `-inline level=5` through the `unit_flags`
list in the compiler config. My guess is that the original files weren't all
built with the same settings, but one file isn't much to go on.

I haven't compared bigger C++ or floating-point functions across versions yet,
and the IOP code may have used different tools.

### Linker

The main program's `.comment` section says `MW MIPS C Compiler (2.4.1.01)`,
even though the compiler is version 3.0. The linker writes that string, not
the compiler, and MWLDPS2 writes exactly those bytes.

Field's class and exception tables are in the main program even though they
refer to overlay code. So I think the main program and its overlays were
linked together and split up afterwards.

### CodeWarrior release

CodeWarrior's C++ runtime library (`MSLGCC_PS2`) is linked into the main
program, from 0x142A40 to 0x143B80. It's the C++ support code: `new` and
`delete`, building and destroying arrays of objects, and exceptions. 27 of its
31 functions match the runtime from CodeWarrior for PS2 R3.04 exactly. Three
more are newer versions of R3.04 functions, and one isn't in R3.04 at all.
Earlier releases match less.

R3.04 comes with compiler build 22, from September 2002, and the game's
compiler is build 38, from March 2003. So the game used a release after
R3.04, most likely R3.5 or R3.51.

### C library

CodeWarrior for PS2 doesn't have its own C library. It uses the one from
Sony's GCC toolchain, which is where the "GCC" in `MSLGCC` comes from. The
game's C library is newlib built with GCC. Its functions sit on 8-byte
boundaries, and CodeWarrior always puts functions on 16-byte boundaries.

Ten small functions in it (`strcmp`, `strlen`, `memcmp` and a few others)
match the newlib from SDK 2.7.2 exactly. The rest don't, and `abort` is 8 bytes
longer in the game, so it's a different build of newlib.

## The main program

| Address | What it is | Matched |
| --- | --- | --- |
| 0x100000 to 0x121940 | Startup code and the game's own code | |
| 0x121940 to 0x131D18 | Sony's `libkernl` (the kernel library), `libdma`, `libmc`, `libpad2`, `libdbc`, `libgraph` and `libcdvd` | Exactly |
| 0x131D18 to 0x13F3E0 | The C library (`memset`, `sprintf`, `malloc` and so on) | 10 functions |
| 0x13F3E0 to 0x1428C8 | A math library | No |
| 0x1428C8 to 0x142A40 | Sony's `libvib` | Exactly |
| 0x142A40 to 0x143B80 | CodeWarrior's C++ runtime | 27 of 31 functions |

Everything except the game's own code is library code. It sits in
`src/sdk/main` as assembly placeholders and doesn't count toward progress.
Each piece is listed in
[config/manifests/sdk-functions.json](../config/manifests/sdk-functions.json)
with a hash of each function and the reason I think it's library code, and the
build checks it.

Library functions have their real names where they match exactly. Anything
that's an assumption has `_guess` in its name and needs more research:

- The C library and math library are `libc_guess_...` and `libm_guess_...`.
- Two small pieces between the `libgraph` objects (at 0x12FD10 and 0x12FF78)
  are `libgraph_guess_...`. They're probably more of `libgraph`, but they don't
  match my copy.
- `__malloc_lock_guess` and `__malloc_unlock_guess` are two empty functions
  the memory allocator calls on the way in and out. That's what newlib's
  versions look like in a build without threads.
- Two of the C++ runtime functions are newer versions of R3.04's
  (`default_new_handler_guess__3stdFv` and `__throw_catch_compare_guess`). A
  third could be either of two R3.04 functions, so it keeps its address name.

The overlays call a function at 0x1330D8 that I've named `__throw`. It's called
the way CodeWarrior calls `__throw`, but it's in the C library and doesn't look
like CodeWarrior's `__throw`, so that name needs a second look.

## Linking

Every module links with MWLDPS2 and comes out identical to the game's. Splat
writes linker scripts for GNU ld, so
[tools/so3/build/lcf.py](../tools/so3/build/lcf.py) translates them into
MWLDPS2's own kind, called a linker command file (`.lcf`).

What MWLDPS2 needs:

- Everything in a module goes in one output section. With more than one, it
  writes a broken result.
- The command file names objects by their file name only, not their path.
- It refuses the `NON_MATCHING` marker symbols splat adds to every assembly
  function, so the configs turn them off.
- It refuses the empty `.text`, `.data` and `.bss` sections GNU as adds to
  everything it assembles, so the build takes those out.
- The C++ exception tables have to be placed somewhere. In the game they're in
  the main program, so for now they go in a separate area that doesn't end up
  in the image.
- Alignment can only go up. Library code built with GCC sits on 8-byte
  boundaries, so it has to stay assembled. If it goes through CodeWarrior,
  every function gets padded out to 16 bytes.
- A branch back to the start of its own function comes out one instruction
  off when GNU as assembled it. The only one in the game was a tiny wait loop
  in Lib at 0x4D99B0, which is decompiled now. Its four `nop`s come from the
  compiler: the PS2's processor has a bug with very short loops, and
  CodeWarrior pads them out to avoid it.

When a file uses an inline function (one written in a header so it can be
pasted into the code that calls it), the compiler also writes a normal copy of
it into that file, right after the first function that needs it. The original
linker kept one copy of each. My build drops the others, using the symbol maps
to find which copy the game kept, and it drops each copy's bookkeeping with it
(an entry in the exception tables and a small `.mwcats` record). MWLDPS2 keeps
the order the compiler wrote, so when a kept copy lands in the wrong place, my
source is different from the original.

Some things are still open:

- Lib's files that are still all assembly have to stay assembled. If they go
  through CodeWarrior, Lib's code comes out too long, and I haven't worked out
  why.
- Linking the main program and its overlays together, the way the original
  seems to have been built, would put Field's class and exception tables back
  where they belong. That needs a lot more of the main program's data worked
  out first. 1070 will probably have to stay its own link, since it seems to
  have been built against an older main program (see below).

## Sony libraries in Lib.bin

`Lib.bin` (`lib`) is a module the rest of the game shares. Most of it is
tri-Ace's own code, but near the start there's a block of Sony code: the
library the game uses to play its videos (`libmpeg`) and the one it uses to
drive the PS2's video decoding hardware (`libipu`).

The game was built with version 2.7 of Sony's SDK. Sony's libraries carry a
version tag, and every tag in the game matches my 2.7.2 copy. The code matches
exactly from 0x3E6900 to 0x3EEB50, with its data in the right places too. SDK
3.0's version doesn't match, so the version matters. Those functions have
their Sony names and don't count toward progress.

A few things I'm not sure about yet:

- One small piece of the library's data, its own version tag, is missing from
  the game. I think the linker left it out because nothing uses it.
- The library calls 11 functions in the main program. Eight of them are Sony's
  and have their names there now (`FlushCache`, `scePrintf` and so on). The
  other three are in the C library.
- Some other code in `Lib.bin` uses the video hardware too. It's probably the
  game's own movie code.

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

These four keep their archive entry numbers because their header names can't be
trusted. The other modules are named after their headers (`boot`, `lib`, `citem`
and so on), and the main executable is `main`.

I haven't confirmed this while the game is running, and something could still
compute those entry numbers. If it holds up, the two unused modules are 3.28 MB
of the 8.59 MB of code that progress currently counts.

## Field 1070's missing destructor copies

Three destructors in 1070 match now, but the build wouldn't accept them at
first. From what I can tell, when a destructor is written inline (in a header,
so it can be pasted into other functions), the compiler also writes a normal
copy of it into every file that uses the class, because the class's vtable
needs something to point at. The original linker kept just one of those copies.
My build tries to do the same, so it needs to know where the game's copy is.

I couldn't find it for these three. As far as I can see, nothing in 1070 uses
those base classes apart from the destructors themselves and the code that
creates the objects, and I didn't find them in any other module on the disc
either.

My guess is that it's because 1070 looks like a leftover from an older build.
Its vtables seem to belong to a version of the main program that isn't on the
disc, and the main program I do have has something unrelated at those
addresses. Two of the base destructors call into what looks like an older
Lib, so maybe the copies were in there. I could be wrong about that.

For now I've listed the three copies in
[config/copies/1070-00_external_copies.txt](../config/copies/1070-00_external_copies.txt),
and the build drops them without giving them an address. The file still links
to the game's bytes. I'd like to come back to this once I understand it
better.

## Field 1070's rodata

I ran into this while matching a big factory function in 1070. It uses
switch statements, and the compiler turns those into jump tables (lists of
addresses it jumps through). Those tables go into rodata (read-only data),
and in 1070 all of the data was one big blob. So the compiled tables would
have ended up after the code instead of where the game has them.

I did something similar for 1067 before, giving each code file its own
rodata. That doesn't seem to fit 1070, though. As far as I can tell, 1070's
code files aren't the original files at all. They're all almost exactly
64 KB, so I think they're just slices. The rodata looks mixed up between
neighbouring slices too. For example, some `"progparticles.h"` strings this
factory uses sit in the middle of the next slice's data.

So for now I've moved 1070's data into its code section like 1067, but it's
still mostly kept as raw bytes. Only the factory's four jump tables come
from compiled code. The rebuilt module is still identical to the game's. I'm
also not sure exactly where the data ends and the rodata starts. 0x325830 is
my best guess because of the padding before it.

I'd like to come back to this once I've worked out where 1070's real files
start and end. Then it could work the same way as 1067.
