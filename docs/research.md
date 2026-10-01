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

