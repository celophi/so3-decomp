# How the Field C++ code was compiled

This note explains, in plain terms, what I found out about how the US Field
overlay (`1067-00`) was built. The short version:

- The first original source file in Field covers addresses `0x1DD400` to
  `0x1DED80`.
- That file was compiled with two inlining settings that change where its
  functions end up. With them, I can rebuild its functions exactly.
- The original build turned RTTI off and left C++ exceptions on. I've switched
  the project to `-RTTI off` to match.

## Why the file boundaries matter

A compiler turns each source file into an object file. Inside it, the
functions sit in a particular order. The linker then glues all the object
files together into one program.

To rebuild the game byte for byte, getting each function right isn't enough.
The functions also have to come out in the same order, from the same files.
My source units (like `text_001DD3C0`) are just provisional chunks of about
64 KiB. They don't follow the original files, and for most C code that
doesn't matter yet.

C++ is different. The compiler places some functions for you, such as copies
of small functions and compiler-made helpers. Where they land depends on which
file they came from. So before I can add real C++ classes, I need to know
where each original file started and ended.

## Clue 1: the class tables live in the main program

Every C++ class with virtual functions has a table of function pointers
called a vtable. Field's vtables aren't in the Field overlay at all. They sit
in the main executable's data, starting around `0x14FE30`, and point into
Field's code.

That tells me the original build linked everything into one big program and
then cut the overlays out afterwards. Exception tables work the same way.
There's a merged exception index in the main program at `0x1970E0` to
`0x1B5FC8`, with 10,558 entries, and it covers overlay functions too.

Two compiler settings follow from this:

- **RTTI was off.** With RTTI on, the compiler puts a pointer to type
  information in the first word of each vtable. In the game that word is
  always zero, and there are no type-information records. With `-RTTI off`,
  my compiler output has the same zero word.
- **Exceptions were on.** The exception entries my compiler already produces
  for matched functions are identical to the game's, for all 8 functions I
  checked. So the current flags stay as they are here. Some other CodeWarrior
  projects turn exceptions off; this one didn't.

For comparison, other CodeWarrior decompilations (the Metroid Prime project)
also build with `-RTTI off`. Projects using decomp-toolkit, such as Twilight
Princess, write real C++ classes and record the compiler's mangled names in
their symbol files. I'm doing the same.

## Clue 2: a destructor that shouldn't have been copied

`func_001DD4A0` is a destructor. Inside it, the compiler pasted in a full
copy of another destructor, `func_001DD7E0`, instead of calling it. Copying a
small function into its caller like this is called inlining.

The strange part is that `func_001DD7E0` sits at a higher address, so it
comes later in the output. With CodeWarrior's normal settings, an ordinary
function is only inlined when it's marked `inline`. Even with automatic
inlining on, it can only be inlined if it appears earlier in the file. Either
way, the order in the game shouldn't happen.

I tested every explanation I could think of against all 15 CodeWarrior PS2
versions I have. They all behave the same way in these tests:

| Idea | Why it doesn't fit |
| --- | --- |
| The destructors were marked `inline` | Their copies would land next to other copies or at the end of the file, not where they are in the game |
| The linker kept duplicate copies | Every small function in Field is referenced; there are no leftover duplicates |
| Automatic inlining for the whole program | Six functions I already matched would change, because they'd swallow the small functions they call |
| A different compiler version | All 15 versions produce the same order |

## Automatic inlining plus reverse order

CodeWarrior has an option called deferred inlining. The compiler reads the
whole file first, then writes its functions out, and it writes them in
reverse order. Combined with automatic inlining (`-inline auto,deferred`),
it can inline a function no matter where it appears in the file.

I wrote a small test file shaped like this part of Field and compiled it with
those settings. The output order and the code match the game:

| Address | Function | What it is |
| --- | --- | --- |
| `0x1DD410` | `func_001DD410` | empty virtual function |
| `0x1DD4A0` | `func_001DD4A0` | destructor that inlines the next ones |
| `0x1DD7B0` | `func_001DD7B0` | virtual function that deletes the object |
| `0x1DD7E0` | `func_001DD7E0` | destructor of the class behind vtable `D_150070` |
| `0x1DEC40` | `func_001DEC40` | destructor of a class derived from it |
| `0x1DECD0` | `func_001DECD0` | base class destructor (vtable `D_150060`) |
| `0x1DED30` | `func_001DED30` | root class destructor (vtable `D_150050`) |

All seven come out in this order. The six that correspond to real game code
are byte for byte identical, apart from addresses the linker fills in. The
last function ends at `0x1DED7C`, so the next file starts at `0x1DED80`.

This also means the original source for this file was written in reverse:
the root destructor at the top, and the functions near `0x1DD400` at the
bottom.

My source for this file stays in address order anyway, like every other
unit. Most of it is still `INCLUDE_ASM` placeholders, and the tool that fills
those in (mwccgap) uses `asm` stub functions. CodeWarrior writes `asm`
functions out straight away, even in deferred mode, so a half-finished file
would come out in a mix of two orders whichever way I wrote it. To avoid
that, `tools/so3/build/text_order.py` puts a deferred unit's functions back in
original address order after compiling. It only changes the order, not the
code. Linking the unit on its own gives the same 6,592 bytes as the game with
either source order.

The setting was per file, not for the whole game. The file that starts at
`0x1DF3E0` doesn't inline its small helpers, so it wasn't built with
automatic inlining. `#pragma auto_inline on` plus `#pragma defer_codegen on`
at the top of a file gives exactly the same result as the command-line
option.

## Changes

- The compiler flags now include `-RTTI off`. Every function I've matched so
  far still matches with it.
- `text_001DD3C0` is split at `0x1DED80`. Everything from there on moved to
  a new unit, `text_001DED80`.
- `config/compilers.json` has a `unit_flags` list, and `text_001DD3C0` uses
  `-inline auto,deferred`. All matched functions still match.
- The first real classes are in: `FieldClass150050`, `FieldClass150060` and
  `FieldClass150070` (named after their vtable addresses until I know their
  real names). Their three destructors and four virtual functions match, and
  the functions' exception entries match the game's. Linking
  `text_001DD3C0` on its own still gives the same bytes as the game.
- `FieldClass14FE30` (vtable `D_14FE30`) has three bases and a member, so
  the compiler makes small "thunk" functions that adjust `this` for its
  secondary bases. Every file that uses the class gets its own copy of each
  thunk, and the original linker kept only one: the copies in the game sit at
  `0x1E1530` to `0x1E1588`, at the end of the next file. `config/thunks.*.txt`
  records where each kept copy is, and the build drops every other copy.
  With that, its destructor (`func_001DD4A0`) matches and both files still
  link to the game's bytes.

## TODO

- Where the next file ends. `0x1DF3E0` is my best guess, because a new family
  of classes starts there, but I haven't proved it yet.
- What the 64 zero bytes at the start of Field's code (`0x1DD3C0`) are. They
  look like padding, not a function.
- The exact original compiler version. The tests here don't tell the 15
  versions apart.

