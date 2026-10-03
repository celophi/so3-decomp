# SO3 Decompilation

I'm working on a matching decompilation of **Star Ocean: Till the End of Time**
for PS2, starting with the North American release. The goal is to write C and
C++ that compile back to the same bytes as the original game.

The main executable and 15 overlays (code the game loads as needed) already
rebuild byte for byte. Most of that is still the original assembly, but I'm
replacing functions with matching source as I work through them. There's a
lot left to do.

## Building

You'll need Docker, Make, and x86_64 Linux with support for 32-bit x86 programs.
You'll also need your own US revision 1.00 Disc 1 image (`SLUS-20488`). The
expected hashes are in [config/manifests/versions.json](config/manifests/versions.json).

Run these from the repository root:

```sh
make image
make extract ISO="/path/to/disc1.iso"
make build
```

The build downloads the compiler and checks the rebuilt files against the
originals. The first run takes a few minutes. Game files and generated output
stay in the ignored `disc/` and `build/` folders.

Use `make test` to run the tool tests, `make shell` to open the development
container, or `make help` for the other commands.

My current compiler findings are in [docs/research.md](docs/research.md).

## Reverse-engineering provenance

This project was created independently by analyzing the publicly released retail version of Star Ocean: Till the End of Time and reconstructing its behavior and machine code through disassembly, decompilation, binary comparison, runtime analysis, and publicly available technical documentation and tools.

No leaked or otherwise non-public *Star Ocean: Till the End of Time* source code, debug symbol files, internal symbol maps, developer documentation, or other confidential materials from tri-Ace or Square Enix have been used in the creation of this project.

Function names, variable names, data structures, translation-unit boundaries, and other source-level details are reconstructed or inferred from the retail binaries and observed behavior unless otherwise documented. They should not be assumed to be the names or organization used by the original developers.

This repository will **never** include leaked source code, private debug symbols, confidential documentation, or other non-public materials from the original game's development.

## Legal

See [LICENSE](LICENSE) and [THIRD_PARTY_NOTICES](THIRD_PARTY_NOTICES.md) for licensing details.

The MIT License applies to original material authored for this project to the extent that the contributors hold the rights necessary to license that material. It does not grant rights to preexisting copyrighted material originating from the original game or from third-party SDKs, libraries, or development software.

This repository is an independent reverse-engineering and preservation project. It is not affiliated with or endorsed by Square Enix, tri-Ace, Sony, or any other rights holder.

No original game executable, overlay binaries, artwork, audio, or other copyrighted game data should be committed to this repository. You must supply required data from your own legally obtained copy of the game.

*Star Ocean: Till the End of Time* and related names and assets are the property of their respective owners.

## Thanks

Thanks to tri-Ace and everyone who worked on *Star Ocean: Till the End of Time*. Hopefully this project helps preserve that work and gives other people a chance to explore it too.

## Tools and acknowledgements

This project builds on tools and research from the wider decompilation community, including:

- [splat](https://github.com/ethteck/splat)
- [spimdisasm](https://github.com/Decompollaborate/spimdisasm)
- [rabbitizer](https://github.com/Decompollaborate/rabbitizer)
- [binutils-mips-ps2-decompals](https://github.com/decompals/binutils-mips-ps2-decompals)
- [mwccgap](https://github.com/mkst/mwccgap)
- [wibo](https://github.com/decompals/wibo)
- [objdiff](https://github.com/encounter/objdiff)
- [decomp-permuter](https://github.com/simonlindholm/decomp-permuter)
- [m2c](https://github.com/matt-kempster/m2c)
- [Ghidra](https://github.com/NationalSecurityAgency/ghidra)
- [ghidra-emotionengine-reloaded](https://github.com/chaoticgd/ghidra-emotionengine-reloaded)
- [ccc](https://github.com/chaoticgd/ccc)
- [decomp.me](https://decomp.me) and its [compiler collection](https://github.com/decompme/compilers)
