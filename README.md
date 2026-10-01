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
expected hashes are in [config/versions.json](config/versions.json).

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
