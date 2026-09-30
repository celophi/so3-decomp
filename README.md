# Star Ocean 3 decompilation

Matching decompilation of **Star Ocean: Till the End of Time** for PS2, targeting
the North American release.

The boot executable and 15 EE overlays currently rebuild byte for byte.

## Docker environment

The build uses Docker on x86_64 Linux. You'll need Make and kernel support for
32-bit x86 programs to run CodeWarrior through wibo.

```sh
make image
make shell
```

The image is defined in [dockerfiles/dev.dockerfile](dockerfiles/dev.dockerfile).
`make shell` mounts the checkout at `/so3` and runs as your user and group.

To extract and build, run these from the host:

```sh
make extract ISO="/path/to/disc1.iso"
make build
make test
```

The build uses US revision 1.00 Disc 1 (`SLUS-20488`). Disc 2 (`SLUS-20891`) is
also supported by the extractor. Image hashes are in
[config/versions.json](config/versions.json). You'll need your own disc images.

`make build` downloads the compiler if needed, runs Splat, and verifies the
outputs. The first build takes a few minutes. `make verify` checks existing
outputs without rebuilding, and `make split` runs Splat on its own.

## Repository layout

| Directory | Contents |
| --- | --- |
| `src/` | C and C++ source files |
| `src/sdk/` | Identified SDK assembly placeholders; excluded from objdiff progress |
| `include/` | Headers |
| `config/` | Disc hashes, compiler candidates, symbols, and Splat layouts |
| `tools/` | Extraction, build scripts, compiler probes, and tests |
| `dockerfiles/` | Development image, dependency locks, and patches |
| `docs/` | Format and toolchain notes |
| `disc/` | Extracted game files; ignored by Git |
| `build/` | Generated assembly, compiler downloads, rebuilds, and reports; ignored by Git |

## Compiler candidate

I'm using **CodeWarrior PS2 3.0 build 52** (July 22, 2003) with `-O3,p` for now.
Builds 38 and 50 also match the five resident-code probes, as does `-O4,p` on
all three. I haven't pinned down the exact original compiler and flags yet.

```sh
make compiler-probe    # Check the current candidate
make compiler-matrix   # Compare all 15 candidates and 10 optimization settings
```

Versions and hashes are in [config/compilers.json](config/compilers.json).
Compiler binaries are downloaded separately into `build/compilers/`.
The [toolchain notes](docs/toolchain.md#compiler-findings) cover the comparisons
and C++ settings in more detail.

## Tools

| Tool | Version | Use |
| --- | --- | --- |
| Python | 3.12.14 | Project scripts |
| pycdlib | 1.21.0 | ISO9660 extraction |
| Splat | 0.50.0 | Splitting and disassembly |
| PS2 binutils | decompals v0.10 | Assembly and linking |
| wibo | 1.2.0 | Running CodeWarrior on Linux |
| mwccgap | `147598b36b198f267e80adbe04dd5804d070dbb3` + local patch | Assembly inclusion in C/C++ objects |
| Ninja | 1.13.2 | Build execution |
| objdiff CLI | 3.8.2 | Object comparison |

The Dockerfile pins the base image and downloaded tools. Python dependencies
and hashes are kept under `dockerfiles/` and in `requirements.txt`.

More detail is in the [extraction](docs/extraction.md),
[toolchain](docs/toolchain.md), and [overlay](docs/overlays.md) notes.

SDK identification uses optional local tools, without Ghidra:

```sh
make sdk-scan       # Compare complete functions with named PS2 syscall patterns
make sdk-symbols    # Recover surviving ELF symbols with CCC
```

These commands download pinned tools under `tools/` and add their directories to
`.git/info/exclude`. Downloads are listed in [config/analysis-tools.json](config/analysis-tools.json).
Results go under `working/sdk-identification/`. Reviewed exclusions are recorded
in [config/sdk-functions.json](config/sdk-functions.json); SDK units still build
and pass the same binary checks. The scanner currently covers syscall wrappers,
not every SDK or compiler runtime function.
