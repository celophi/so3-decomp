# Research

## Compiler

I think SO3 was built with CodeWarrior for PS2. I'm using **3.0 build 38
(March 7, 2003)** with these flags for now:

```text
-O3,p -RTTI off -inline level=4
```

That gets matching code from the functions I've worked on, but I'm not
completely sure it's the exact original version yet.

I compared 15 compiler versions using five small functions from the main
executable. Builds 38, 50, and 52 all matched with both `-O3,p` and `-O4,p`.
Those tests only cover 272 bytes, so they couldn't tell those three apart.
`-O3,p` is the current choice for optimizing for speed.

I was using build 52 until I got stuck on two small functions in the item
creation menu. Both are switch statements, and the compiler turns those into
jump tables (lists of addresses it jumps through). When the first case isn't
0, the code subtracts the lowest case before it looks in the table. The game
does that subtraction with an `addi` instruction, but build 52 always writes
`addiu`. They do the same thing here, so it came down to that one instruction.
The disassembler even marks the game's `addi` as handwritten, because it
doesn't expect a compiler to write it.

I couldn't find any way to write the source that got build 52 to use `addi`,
so I tried the same switch on every version I have. The builds from before
May 2003 write `addi`, and the later ones write `addiu`. Then I looked through
the whole game. Every jump table like this uses `addi` (64 of them), and none
use `addiu`. The ones I'd already matched all start at case 0, so they never
needed the subtraction, which I think is why this didn't show up sooner.

I also compiled all of the project's source files with builds 38 and 52, and
apart from this they came out the same. So switching doesn't change anything
that already matched, and it gets those functions unstuck. The other older
builds that write `addi` produce quite different code elsewhere, so build 38
is the only one I have that fits both. There could still be a build I don't
have that fits too.

The C++ code in Field gives me a better idea of the other settings:

- `-RTTI off` disables runtime type information. Field's virtual function
  tables have empty type-information pointers, which agrees with this setting.
- `-inline level=4` lets the compiler copy small functions into their callers
  four levels deep. Some destructors need that extra level to match. Another
  function matches at level 4 but fails at level 8, so simply turning it up
  further doesn't help.
- C++ exceptions appear to have been enabled. The exception records produced
  for the functions I've checked match the game's, so I'm leaving them on.

Level 4 isn't enough everywhere, though. One destructor in Field's
`text_001E6C50` sits on a chain of six classes, and the game copies all five
base destructors into it. Level 4 stops one short and calls the last one
instead. So that file gets `-inline level=5` on its own, through the
`unit_flags` list in the compiler config. Everything else in the file matches
at both levels. My guess is that the original files weren't all built with the
same settings, but one file isn't much to go on yet.

There's one awkward detail: the main executable contains the string
`MW MIPS C Compiler (2.4.1.01)`, while the three matching compiler builds write
`3.0.0`. Several older releases write the same `2.4.1.01` string. It could
have come from an older library or linker, but I don't know yet.

I'm using PS2 GNU binutils to assemble the rebuild and to link most of it. I
think the original linker was CodeWarrior's own, MWLDPS2, and I'm starting to
move the build over to it (see Linking below). Field's class and exception
tables live in the main executable even though they refer to overlay code,
which suggests the original build linked the code together before separating
the overlays.

I'd still like to compare more complex functions, especially C++ and
floating-point code, in case something else separates the builds. The SDK
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

These four keep their archive entry numbers because their header names can't be
trusted. The other modules are named after their headers (`boot`, `lib`, `citem`
and so on), and the main executable is `main`.

I haven't confirmed this while the game is running, and something could still
compute those entry numbers. If it holds up, the two unused modules are 3.28 MB
of the 8.59 MB of code that progress currently counts.

## Field 1070's missing destructor copies

I'm still getting my head around some of this, but this
is what I think is going on rather than something I've proven.

Three destructors in 1070 match now, but the build wouldn't accept them at
first. From what I can tell, when a destructor is written inline (in a header,
so it can be pasted into other functions), the compiler also writes a normal
copy of it into every file that uses the class, because the class's vtable
needs something to point at. The original linker seems to have kept just one of those copies. 
My build tries to do the same, so it needs to know where the game's copy is.

I couldn't find it for these three. As far as I can see, nothing in 1070 uses
those base classes apart from the destructors themselves and the code that
creates the objects, and I didn't find them in any other module on the disc
either.

My guess is that it's because 1070 looks like a leftover from an older build (?).
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

## Linking

Up to now I've linked everything with GNU ld, which is what splat sets
projects up for. I'm moving the build over to MWLDPS2, the linker that comes
with CodeWarrior, since that's most likely what the game was built with. Other
CodeWarrior decomps do the same, like Monster Hunter and Persona 3 on PS2, and
most of the GameCube ones.

The main reason is C++. When a file uses an inline function (one written in a
header so it can be pasted into the code that calls it), the compiler also
leaves a normal copy of it in that file, and the linker is meant to keep just
one. GNU ld doesn't know how to do that with CodeWarrior's objects, so my build
has been doing it by hand, by looking up where the game kept each copy.

I hoped the original linker would also put those copies in the right order.
It doesn't. I tried it, and MWLDPS2 keeps whatever order the compiler wrote.
From what I can tell, the compiler writes a copy right after the first
function that needs it, so when a copy ends up in the wrong place, it's my
source that's different, not the linker. Most of the time the function that
needs it is still assembly, so that should sort itself out as I decompile
more. In one case it meant a file boundary was wrong: the destructor at
0x20D9A0 really belongs to the file before it, so that file now starts at
0x20DA30.

So far 11 of the 16 link with MWLDPS2, and they all still come out identical
to the game's. That's Battle (both copies), `boot`, and every menu overlay
except item creation. Splat only writes linker
scripts for GNU ld, so the build translates splat's script into MWLDPS2's own
kind, a linker command file (`.lcf`), with
[tools/so3/build/lcf.py](../tools/so3/build/lcf.py). Everything else still uses
GNU ld for now, and the modules that use MWLDPS2 are listed in
[config/manifests/linker.json](../config/manifests/linker.json).

A few things I learned about MWLDPS2 on the way:

- Everything has to go in one output section. When I gave each part its own,
  it wrote a broken result.
- The command file names objects by their file name only, not their path.
- It refuses the `NON_MATCHING` marker symbols splat adds to every assembly
  function, so those modules' configs turn them off.
- It also refuses the empty `.text`, `.data` and `.bss` sections GNU as adds to
  everything it assembles, so the build takes those out afterwards. GNU ld
  doesn't care either way.
- It wants the C++ exception tables placed somewhere, even though they aren't
  part of the overlays. In the game they're in the main program. For now they
  go in a separate area that doesn't end up in the image.

Field (both copies), item creation, Lib and the main program are still on GNU
ld. For Field and item creation, the problem is the C++ copies my build drops.
It drops just the code, but each copy also has some bookkeeping (an entry in
the exception tables and a few other small records) that still points at it.
GNU ld throws those away without looking, but MWLDPS2 still checks them. The
original linker would have dropped each copy together with its bookkeeping, so
that's what I need to do too.

Lib isn't on MWLDPS2 yet because of one instruction. There's a tiny wait loop
at 0x4D99B0 that's still assembly, and it branches back to its own start. GNU
as leaves the linker a note to fill in that branch, and the two linkers read
the note differently, so MWLDPS2 lands one instruction off. It's the only
branch like that in the whole game, so I just need to decide how to deal with
it.

I was also worried about alignment, since GNU ld can lower it and MWLDPS2
can't. Lib links fine as long as its files that are still all assembly stay
assembled the way they are now. When I tried sending those through CodeWarrior
instead, Lib's code came out too long, and I haven't worked out why yet.

The bigger goal is linking the main program and its overlays together in one
go, the way the original seems to have been built. That would put Field's
class tables back where they belong and let the build check them, instead of
throwing the compiled ones away like it does now. I'll need a lot more of the
main program's data worked out first. 1070 will probably have to stay its own
link either way, since it seems to have been built against an older main
program (see above).

## Sony libraries in Lib.bin

`Lib.bin` (`lib`) is a module the rest of the game shares. Most of it is
tri-Ace's own code, but near the start there's a block of Sony code: the
library the game uses to play its videos (`libmpeg`) and the one it uses to
drive the PS2's video decoding hardware (`libipu`).

The game was built with version 2.7 of Sony's SDK. Sony's libraries carry a
version tag, and every tag I found in the game matches my 2.7.2 copy.

I compared that copy with the original module, and the code matches exactly
from 0x3E6900 to 0x3EEB50, with its data in the right places too. SDK 3.0's
version doesn't match, so the version matters. The Ratchet & Clank decomp
found the same library, down to the typos in Sony's error messages ("picure",
"sutructure").

Since this isn't tri-Ace's code, I've given those functions their Sony names
and taken them out of the progress count. They stay in the build as the
original assembly.

A few things I'm not sure about yet:

- One small piece of the library's data, its own version tag, is missing from
  the game. I think the linker left it out because nothing uses it.
- The library calls 11 functions in the main executable. I know what Sony
  calls them, but I haven't checked the executable's code against the SDK
  yet, so I haven't named them.
- Some other code in `Lib.bin` uses the video hardware too. It's probably the
  game's own movie code.

The next step is to check the main executable against the same SDK.
