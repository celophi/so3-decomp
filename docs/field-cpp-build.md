# How the Field C++ code was compiled

This note explains, in plain terms, what I found out about how the US Field
overlay (`1067-00`) was built. The short version:

- The first original source file in Field covers addresses `0x1DD400` to
  `0x1DED80`.
- Its base-class destructors are small inline functions in a header. The
  compiler pastes them into other destructors and also leaves one copy of
  each in the file. With that, I can rebuild its functions exactly.
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

A destructor in a different file, `func_001E5030`, pastes in the same code.
The compiler can only inline code it can see while compiling that file, so
these destructors must be written in a header as inline functions.

When a class's destructor is inline, the compiler still leaves one normal
copy of it in the file, because the class's vtable needs an address for it:

- The copy of `FieldClass150070`'s destructor goes right after that class's
  first non-inline virtual function. That's exactly what the game shows:
  `func_001DD7E0` follows `func_001DD7B0`.
- The copies of the two base destructors (`FieldClass150060` and
  `FieldClass150050`) go at the very end of the file, which is where
  `func_001DECD0` and `func_001DED30` are. The last one ends at `0x1DED7C`, so
  the next file starts at `0x1DED80`.

Every other file that uses these classes gets its own copies too, and the
original linker kept only one of each. The build does the same: a unit keeps
a copy only if the game's copy lives inside that unit, and drops the rest.

One detail my compiler gets wrong on its own: it writes the two base
destructor copies in the opposite order to the game. So for any file that
keeps such copies, `tools/so3/build/text_order.py` puts the functions back in
the game's address order after compiling. It only changes the order, not the
code, and linking the file on its own gives the same 6,592 bytes as the game.

I first thought this file needed special inlining settings (automatic
inlining with reversed output). That also fit the order, but the inline
destructors explain everything without them, and the file matches with the
normal settings, so I dropped that idea.

## Changes

- The compiler flags now include `-RTTI off`. Every function I've matched so
  far still matches with it.
- `text_001DD3C0` is split at `0x1DED80`. Everything from there on moved to
  a new unit, `text_001DED80`.
- `config/compilers.json` has a `unit_flags` list for files that need extra
  compiler settings. None do yet.
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
- Globals in the main program that Field reads through the `$gp` register now
  have names. Splat only names addresses it considers valid, so the 1067
  YAML marks the small block `0x1B6000` to `0x1B7000` as valid. All 92 such
  globals now get names like `D_001B65F4`, and ordinary `extern` declarations
  compile to the same gp-relative loads.
- For a class with several bases, the compiler lays out its vtable like this:
  first the main base's slots, then one block for each other base, and last
  the class's own new functions and its overrides of the other bases'
  functions. Knowing that, I could work out the base classes'
  sizes from where they sit in the game's vtables. With the corrected layout,
  `FieldClass150120`'s destructor (`func_001E5030`) and another
  `FieldClass14FE30` function (`func_001DD490`) now match, and all four
  affected files still link to the game's bytes.

## More file boundaries from thunks

Thunks always come after every other function in a file. So wherever the game
has a run of thunks, the next function starts a new original source file.
Field has 121 thunks in 46 runs. I used them to split Field's provisional
units at 45 boundaries, going from 22 units to 65. Every unit still links to
the game's exact bytes on its own, and the same 637 functions match before
and after. Files that don't contain any classes with multiple bases leave no
thunks behind, so some units still hold more than one original file.

## How to add a Field class

These are the steps and rules I follow when I turn Field functions into class
methods.

**Names.** I don't know the real class names, so each class is named after its
vtable address, like `FieldClass150120`. A method I can't name yet keeps the
name of the first function that fills its vtable slot, like `func_001DF3D0`.
Other classes that override that slot use the same name, because in C++ an
override must have the same name as the function it replaces. The compiler
turns those names into mangled ones, such as `__dt__16FieldClass150120Fv`, and
only the config files use them. The source keeps the readable names.

**Config files.** For each new class I add:

- The vtable and every method's address to `config/symbols.1067-00.txt`, by
  mangled name.
- Each thunk the class needs to `config/thunks.1067-00.txt`, with the
  address of the copy the game kept. The build stops with an error if a thunk
  is missing, so I can't forget one.
- Any code that points into the middle of a vtable to
  `config/relocs.1067-00.txt`, as the vtable plus an offset (for example
  `__vt__16FieldClass150120` + `0x1C`). A class with more than one base
  keeps the vtables for its other bases inside its main vtable, so the game's
  code points at those spots.

**Working out the layout.** The vtable tells me more than the order of the
functions:

- It starts with two zero words, then one slot per virtual function.
- For a class with several bases, the main base's slots come first, then a
  block for each other base, then the class's own new functions and its
  overrides of the other bases' functions.
- A thunk's name gives the offset of the base it adjusts for. `@120@...`
  means that base starts at `0x78` (120) in the object. The gaps between
  those offsets give the size of each base class.
- The functions around the vtable show which methods were inline. A
  destructor that another file pastes in has to be inline in a header.

**Things the compiler does that matter for matching:**

- Calling a base class's method moves `this` to that base without checking
  for null. A `static_cast` to the base pointer adds a null check. When a
  function needs a base's address without that check, I bind a reference to
  the base (`FieldClass150070& base = *this;`) and take its address.
- A destructor takes a hidden flag. The compiler passes `-1` when it destroys
  a member, `0` when it destroys a base, and calls `operator delete` when the
  flag is positive.
- Global `operator delete` is `__dl__FPv` at `0x100B40`, and `operator
  delete[]` is `__dla__FPv` at `0x100BE0`. `delete[]` on an array of plain
  bytes calls `__dla__FPv` directly. A class with its own `operator delete`
  calls it by the class's mangled name, like
  `__dl__14LibClass178DD0FPv`.
- A 16-byte value copied with the R5900's 128-bit loads and stores has to be
  `unsigned __int128`. A struct of four floats marked 16-byte aligned doesn't
  get those instructions.

**Checking it.** A class change can move other functions, so after each change
I recompile every file that uses the header and link each changed file on its
own at its original address. Every function that matched before has to still
match, and the linked file has to come out identical to the game's bytes.

## TODO

- Why the game's two base destructor copies are in the opposite order to my
  compiler's output.
- What the 64 zero bytes at the start of Field's code (`0x1DD3C0`) are. They
  look like padding, not a function.
- The exact original compiler version. The tests here don't tell the 15
  versions apart.

