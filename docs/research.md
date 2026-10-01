# Compiler research

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
