#!/usr/bin/env python3
"""Pull the game's code out of a disc image, and list everything else on it.

Run it with `make extract ISO=/path/disc.iso`. It only accepts the disc
releases in config/manifests/versions.json, and checks the whole image's hash
before it starts.

A disc has two kinds of files. The few visible files in the ISO9660
filesystem (like the main executable, SLUS_204.88) I copy out as they are. The
game keeps nearly everything else outside the filesystem, behind a resource
table 2 MiB into the disc. A lot of those resources are compressed (SLZ) or
compressed and encrypted (SLE). I decode each of those, and save every code
module I find, either an ELF or an MWo3 overlay, under modules/. Everything
else only gets listed in the manifest, apart from a few decoded resources
whose hashes the version profile checks.

The result goes to disc/<version>/ with a manifest.json describing all of it.
Everything is built in a staging folder first, so a failed run never leaves a
half-finished extraction behind.
"""

import argparse
from collections import Counter
import hashlib
from importlib.metadata import version as package_version
from io import BytesIO
import json
from pathlib import Path, PurePosixPath
import sys
from tempfile import TemporaryDirectory

from tools.so3 import ROOT
from tools.so3.formats import (
    FormatError, TABLE_OFFSET, TABLE_SIZE, TABLE_SLOTS, SECTOR_SIZE,
    classify, decode_chain, elf_info, overlay_info, read_table, require,
)

CONFIG = ROOT / "config/manifests/versions.json"
DISC_FOLDER = ROOT / "disc"
DISC_RELEASES = ("us-disc1", "us-disc2")
MANIFEST_SCHEMA_VERSION = 1
EXTRACTOR_VERSION = 1
SCOPE = "visible files and top-level code modules; nested PACK/ZLS archives are inventoried only"
# The profile fields copied into the manifest to say which disc it came from.
DISC_FIELDS = ("serial", "disc", "region", "revision", "iso_size", "iso_sha256")

HASH_CHUNK_SIZE = 8 * 1024 * 1024
# The visible files are small. Anything bigger means this isn't the disc I expect.
MAX_VISIBLE_FILE_SIZE = 32 * 1024 * 1024
# classify() only needs the first few bytes of a resource to recognise it.
HEADER_PEEK_SIZE = 16
PROGRESS_EVERY = 100

CODE_FORMATS = ("ELF", "MWo3")
COMPRESSED_FORMATS = ("SLZ", "SLE")
TABLE_RESOURCE = 0  # The resource table lists itself as resource 0.
TABLE_FILE = "resources/0000.bin"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def hash_file(path: Path) -> str:
    """Hash a file a piece at a time, so a whole disc image never has to fit in memory."""
    checksum = hashlib.sha256()
    with path.open("rb") as stream:
        while chunk := stream.read(HASH_CHUNK_SIZE):
            checksum.update(chunk)
    return checksum.hexdigest()


def read_at(stream, offset: int, count: int) -> bytes:
    stream.seek(offset)
    result = stream.read(count)
    require(len(result) == count, f"short read at disc offset {offset:#x}")
    return result


def save(root: Path, relative: str, data: bytes) -> dict:
    """Write a file under root, and return the record the manifest keeps for it."""
    path = root / relative
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    return {"path": relative, "size": len(data), "sha256": digest(data)}


def log(message: str) -> None:
    print(message, file=sys.stderr, flush=True)


def module_info(kind: str, data: bytes) -> dict:
    """Read a code module's header, for an ELF or an MWo3 overlay."""
    return elf_info(data) if kind == "ELF" else overlay_info(data)


def module_extension(kind: str) -> str:
    return "elf" if kind == "ELF" else "bin"


def is_compressed(kind: str) -> bool:
    # classify() adds the compression type to the name, like SLZ1 or SLE3.
    return kind.startswith(COMPRESSED_FORMATS)


def output_path(iso_name: str) -> str:
    """Turn an ISO path like /SLUS_204.88;1 into the path I save it at, like iso/SLUS_204.88."""
    # ISO9660 adds a version number after a semicolon, which I drop.
    components = tuple(part.rsplit(";", 1)[0] for part in PurePosixPath(iso_name).parts[1:])
    require(all(part not in ("", ".", "..") and "\\" not in part for part in components),
            "unsafe ISO filename")
    return "iso/" + "/".join(components)


def extract_visible(iso_path: Path, destination: Path, profile: dict) -> tuple[list, bytes]:
    """Copy out every file in the disc's filesystem, and return their records and the main executable."""
    try:
        import pycdlib
    except ImportError as error:
        raise FormatError("pycdlib is required; install requirements.txt in a virtual environment") from error
    image = pycdlib.PyCdlib()
    try:
        image.open(str(iso_path))
    except pycdlib.pycdlibexception.PyCdlibException as error:
        raise FormatError(f"cannot read ISO9660 filesystem: {error}") from error
    try:
        iso_names = sorted(str(PurePosixPath(folder) / name)
                           for folder, _, files in image.walk(iso_path="/") for name in files)
        output = []
        boot = None
        seen = set()
        for iso_name in iso_names:
            relative = output_path(iso_name)
            require(relative not in seen, "colliding ISO filenames")
            seen.add(relative)
            record = image.get_record(iso_path=iso_name)
            require(record.data_length <= MAX_VISIBLE_FILE_SIZE, "unexpectedly large visible file")
            buffer = BytesIO()
            image.get_file_from_iso_fp(buffer, iso_path=iso_name)
            data = buffer.getvalue()
            require(len(data) == record.data_length, "ISO file length mismatch")
            item = save(destination, relative, data)
            item.update({"iso_path": iso_name, "offset": record.extent_location() * SECTOR_SIZE})
            output.append(item)
            if relative == "iso/" + profile["boot_file"]:
                require(item["sha256"] == profile["boot_sha256"], "boot executable hash mismatch")
                item["module"] = elf_info(data)
                boot = data
        require(boot is not None, "expected boot executable is absent")
        return output, boot
    except pycdlib.pycdlibexception.PyCdlibException as error:
        raise FormatError(f"cannot extract ISO9660 filesystem: {error}") from error
    finally:
        image.close()


class ResourceInventory:
    """Walk the resource table, saving the code it finds along the way.

    Each table entry gets filled in with what I found, and goes into the
    manifest as it is.
    """

    def __init__(self, destination: Path, profile: dict, boot: bytes, modules: list):
        self.destination = destination
        self.profile = profile
        self.boot = boot
        self.modules = modules
        self.key = bytes.fromhex(profile["sle_key"])
        # A few decoded blocks whose hashes the profile pins, keyed like "1067/0" (resource/block).
        self.expected = profile.get("decoded_checks", {})
        self.verified_checks = set()
        self.compressed_count = 0
        self.decoded_count = 0

    def visit(self, stream, entry: dict, raw_table: bytes) -> None:
        index, size = entry["index"], entry["allocated_size"]
        if not size:
            entry["status"] = "no_physical_extent"
            return
        header = read_at(stream, entry["offset"], min(HEADER_PEEK_SIZE, size))
        kind = classify(header)
        entry.update({"format": kind, "header_hex": header.hex(), "status": "inventoried"})
        if index == TABLE_RESOURCE:
            entry.update({"format": "resource_table", "status": "saved",
                          "raw": {"path": TABLE_FILE, "size": TABLE_SIZE, "sha256": digest(raw_table)}})
            return
        if kind not in CODE_FORMATS and not is_compressed(kind):
            return
        raw = read_at(stream, entry["offset"], size)
        entry["sha256"] = digest(raw)
        if is_compressed(kind):
            keep = self.decode(entry, raw)
        elif kind == "ELF" and raw[:len(self.boot)] == self.boot:
            # Another copy of the main executable, padded out to its allocation.
            entry["alias_of"] = "iso/" + self.profile["boot_file"]
            keep = True
        else:
            relative = f"modules/{index:04d}-raw.bin"
            self.modules.append({**save(self.destination, relative, raw), "resource": index,
                                 "includes_allocation_padding": True, **module_info(kind, raw)})
            keep = True
        if keep:
            entry["raw"] = save(self.destination, f"resources/{index:04d}.bin", raw)
        if self.compressed_count and self.compressed_count % PROGRESS_EVERY == 0 and is_compressed(kind):
            log(f"Validated {self.compressed_count} compressed resources; found {len(self.modules)} code modules")

    def decode(self, entry: dict, raw: bytes) -> bool:
        """Decode every block of a compressed resource. Returns whether any block was worth saving."""
        index = entry["index"]
        self.compressed_count += 1
        entry["blocks"] = []
        keep = False
        for block_index, block in enumerate(decode_chain(raw, self.key)):
            self.decoded_count += 1
            kind = classify(block.data)
            checksum = digest(block.data)
            check_id = f"{index}/{block_index}"
            if check_id in self.expected:
                require(checksum == self.expected[check_id], f"decoded hash mismatch for {check_id}")
                self.verified_checks.add(check_id)
            block_info = {
                "index": block_index, "offset": block.offset,
                "encoding": block.encoding, "compressed_size": block.compressed_size,
                "next_offset": block.next_offset, "decoded_size": len(block.data),
                "sha256": checksum, "format": kind,
            }
            if kind in CODE_FORMATS:
                relative = f"modules/{index:04d}-{block_index:02d}.{module_extension(kind)}"
                stored = save(self.destination, relative, block.data)
                block_info["path"] = relative
                self.modules.append({**stored, "resource": index, "block": block_index, **module_info(kind, block.data)})
                keep = True
            elif check_id in self.expected:
                relative = f"checks/{index:04d}-{block_index:02d}.bin"
                save(self.destination, relative, block.data)
                block_info["path"] = relative
                keep = True
            entry["blocks"].append(block_info)
        entry["status"] = "decoded"
        return keep


def read_resource_table(stream, destination: Path, profile: dict) -> tuple[bytes, list]:
    """Read and check the resource table, save a copy, and return it with its entries."""
    raw_table = read_at(stream, TABLE_OFFSET, TABLE_SIZE)
    require(digest(raw_table) == profile["table_sha256"], "resource table hash mismatch")
    entries = read_table(raw_table, profile["iso_size"])
    populated = sum(bool(entry["sectors"]) for entry in entries)
    require(populated == profile["populated_entries"], "resource table entry count mismatch")
    save(destination, TABLE_FILE, raw_table)
    return raw_table, entries


def build_inventory(iso_path: Path, destination: Path, profile: dict) -> dict:
    """Extract everything into destination, and return the manifest describing it."""
    files, boot = extract_visible(iso_path, destination, profile)
    modules = [{"path": "iso/" + profile["boot_file"], "source": "iso9660",
                "size": len(boot), "sha256": digest(boot), **elf_info(boot)}]
    inventory = ResourceInventory(destination, profile, boot, modules)
    with iso_path.open("rb") as stream:
        raw_table, entries = read_resource_table(stream, destination, profile)
        for entry in entries:
            try:
                inventory.visit(stream, entry, raw_table)
            except FormatError as error:
                raise FormatError(f"resource {entry['index']}: {error}") from error
    require(inventory.verified_checks == set(inventory.expected), "one or more required decoded resources were not found")
    populated = sum(bool(entry["sectors"]) for entry in entries)
    return {
        "schema_version": MANIFEST_SCHEMA_VERSION,
        "extractor_version": EXTRACTOR_VERSION,
        "pycdlib_version": package_version("pycdlib"),
        "disc": {field: profile[field] for field in DISC_FIELDS},
        "profile_sha256": digest(json.dumps(profile, sort_keys=True, separators=(",", ":")).encode()),
        "scope": SCOPE,
        "table": {"offset": TABLE_OFFSET, "slots": TABLE_SLOTS, "populated_entries": populated,
                  "sha256": digest(raw_table)},
        "summary": {"visible_files": len(files), "compressed_resources": inventory.compressed_count,
                    "decoded_blocks": inventory.decoded_count, "code_modules": len(modules),
                    "module_formats": dict(sorted(Counter(module["format"] for module in modules).items()))},
        "verified_decoded_checks": sorted(inventory.verified_checks),
        "files": files,
        "modules": modules,
        "resources": entries,
    }


def check_disc(iso_path: Path, profile: dict) -> None:
    require(iso_path.stat().st_size == profile["iso_size"], "disc size mismatch")
    log("Verifying complete ISO SHA-256...")
    checksum = hash_file(iso_path)
    require(checksum == profile["iso_sha256"], f"unsupported or modified ISO: SHA-256 {checksum}")


def extract(iso_path: Path, destination: Path, profile: dict) -> dict:
    """Check the disc, extract it into a new destination folder, and return the manifest."""
    require(not destination.exists() and not destination.is_symlink(),
            f"output already exists: {destination}; choose a new --output directory")
    check_disc(iso_path, profile)
    destination.parent.mkdir(parents=True, exist_ok=True)
    with TemporaryDirectory(prefix=".so3-extract-", dir=destination.parent) as staging:
        root = Path(staging) / "output"
        root.mkdir()
        manifest = build_inventory(iso_path, root, profile)
        (root / "manifest.json").write_text(
            json.dumps(manifest, indent=2) + "\n", encoding="utf-8", newline="\n")
        require(not destination.exists() and not destination.is_symlink(), "output appeared during extraction")
        root.rename(destination)
    return manifest


def find_profile(iso_path: Path, version=None) -> tuple[str, dict]:
    """Work out which supported release a disc image is from its size."""
    profiles = json.loads(CONFIG.read_text(encoding="utf-8"))["versions"]
    size = iso_path.stat().st_size
    candidates = [(name, profile) for name, profile in profiles.items()
                  if profile["iso_size"] == size and (version is None or version == name)]
    problem = "unrecognized disc size or wrong --version" if version else "unrecognized disc size"
    require(len(candidates) == 1, f"{problem}; supported inputs are in config/manifests/versions.json")
    return candidates[0]


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("iso", type=Path, help="path to an unmodified supported US disc ISO")
    parser.add_argument("--version", choices=DISC_RELEASES, help="require this release")
    parser.add_argument("--output", type=Path, help="new output directory (default: disc/<version>)")
    args = parser.parse_args(argv)
    try:
        name, profile = find_profile(args.iso, args.version)
        destination = args.output if args.output is not None else DISC_FOLDER / name
        manifest = extract(args.iso, destination, profile)
        print(f"Extracted {name} to {destination}")
        print(json.dumps(manifest["summary"], sort_keys=True))
        return 0
    except (FormatError, OSError) as error:
        print(f"Extraction failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
