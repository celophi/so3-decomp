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
