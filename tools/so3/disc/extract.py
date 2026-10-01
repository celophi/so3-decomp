#!/usr/bin/env python3
"""Extract verified SO3 code inputs and inventory the hidden disc resources."""

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


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def hash_file(path: Path) -> str:
    checksum = hashlib.sha256()
    with path.open("rb") as stream:
        while chunk := stream.read(8 * 1024 * 1024):
            checksum.update(chunk)
    return checksum.hexdigest()


def read_at(stream, offset: int, count: int) -> bytes:
    stream.seek(offset)
    result = stream.read(count)
    require(len(result) == count, f"short read at disc offset {offset:#x}")
    return result


def save(root: Path, relative: str, data: bytes) -> dict:
    path = root / relative
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    return {"path": relative, "size": len(data), "sha256": digest(data)}


def log(message: str) -> None:
    print(message, file=sys.stderr, flush=True)


def extract_visible(iso_path: Path, destination: Path, profile: dict) -> tuple[list, bytes]:
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
        paths = sorted(str(PurePosixPath(folder) / name)
                       for folder, _, files in image.walk(iso_path="/") for name in files)
        output = []
        boot = None
        seen = set()
        for iso_name in paths:
            components = PurePosixPath(iso_name).parts[1:]
            components = tuple(part.rsplit(";", 1)[0] for part in components)
            require(all(part not in ("", ".", "..") and "\\" not in part for part in components),
                    "unsafe ISO filename")
            relative = "iso/" + "/".join(components)
            require(relative not in seen, "colliding ISO filenames")
            seen.add(relative)
            record = image.get_record(iso_path=iso_name)
            require(record.data_length <= 32 * 1024 * 1024, "unexpectedly large visible file")
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


def build_inventory(iso_path: Path, destination: Path, profile: dict) -> dict:
    files, boot = extract_visible(iso_path, destination, profile)
    modules = [{"path": "iso/" + profile["boot_file"], "source": "iso9660",
                "size": len(boot), "sha256": digest(boot), **elf_info(boot)}]
    expected = profile.get("decoded_checks", {})
    verified_checks = set()
    decoded_count = compressed_count = 0
    key = bytes.fromhex(profile["sle_key"])
    with iso_path.open("rb") as stream:
        raw_table = read_at(stream, TABLE_OFFSET, TABLE_SIZE)
        require(digest(raw_table) == profile["table_sha256"], "resource table hash mismatch")
        entries = read_table(raw_table, profile["iso_size"])
        populated = sum(bool(entry["sectors"]) for entry in entries)
        require(populated == profile["populated_entries"], "resource table entry count mismatch")
        save(destination, "resources/0000.bin", raw_table)
        for entry in entries:
            index, size = entry["index"], entry["allocated_size"]
            if not size:
                entry["status"] = "no_physical_extent"
                continue
            try:
                header = read_at(stream, entry["offset"], min(16, size))
                kind = classify(header)
                entry.update({"format": kind, "header_hex": header.hex(), "status": "inventoried"})
                if index == 0:
                    entry.update({"format": "resource_table", "status": "saved",
                                  "raw": {"path": "resources/0000.bin", "size": TABLE_SIZE,
                                          "sha256": digest(raw_table)}})
                    continue
                if kind not in ("ELF", "MWo3") and not kind.startswith(("SLZ", "SLE")):
                    continue
                raw = read_at(stream, entry["offset"], size)
                entry["sha256"] = digest(raw)
                keep = False
                if kind.startswith(("SLZ", "SLE")):
                    compressed_count += 1
                    entry["blocks"] = []
                    for block_index, block in enumerate(decode_chain(raw, key)):
                        decoded_count += 1
                        decoded_kind = classify(block.data)
                        checksum = digest(block.data)
                        check_id = f"{index}/{block_index}"
                        if check_id in expected:
                            require(checksum == expected[check_id], f"decoded hash mismatch for {check_id}")
                            verified_checks.add(check_id)
                        block_info = {
                            "index": block_index, "offset": block.offset,
                            "encoding": block.encoding, "compressed_size": block.compressed_size,
                            "next_offset": block.next_offset, "decoded_size": len(block.data),
                            "sha256": checksum, "format": decoded_kind,
                        }
                        if decoded_kind in ("ELF", "MWo3"):
                            info = elf_info(block.data) if decoded_kind == "ELF" else overlay_info(block.data)
                            extension = "elf" if decoded_kind == "ELF" else "bin"
                            relative = f"modules/{index:04d}-{block_index:02d}.{extension}"
                            stored = save(destination, relative, block.data)
                            block_info["path"] = relative
                            modules.append({**stored, "resource": index, "block": block_index, **info})
                            keep = True
                        elif check_id in expected:
                            relative = f"checks/{index:04d}-{block_index:02d}.bin"
                            save(destination, relative, block.data)
                            block_info["path"] = relative
                            keep = True
                        entry["blocks"].append(block_info)
                    entry["status"] = "decoded"
                elif kind == "ELF" and raw[:len(boot)] == boot:
                    entry["alias_of"] = "iso/" + profile["boot_file"]
                    keep = True
                else:
                    info = elf_info(raw) if kind == "ELF" else overlay_info(raw)
                    relative = f"modules/{index:04d}-raw.bin"
                    modules.append({**save(destination, relative, raw), "resource": index,
                                    "includes_allocation_padding": True, **info})
                    keep = True
                if keep:
                    entry["raw"] = save(destination, f"resources/{index:04d}.bin", raw)
                if compressed_count and compressed_count % 100 == 0 and kind.startswith(("SLZ", "SLE")):
                    log(f"Validated {compressed_count} compressed resources; found {len(modules)} code modules")
            except FormatError as error:
                raise FormatError(f"resource {index}: {error}") from error
    require(verified_checks == set(expected), "one or more required decoded resources were not found")
    return {
        "schema_version": 1,
        "extractor_version": 1,
        "pycdlib_version": package_version("pycdlib"),
        "disc": {field: profile[field] for field in ("serial", "disc", "region", "revision", "iso_size", "iso_sha256")},
        "profile_sha256": digest(json.dumps(profile, sort_keys=True, separators=(",", ":")).encode()),
        "scope": "visible files and top-level code modules; nested PACK/ZLS archives are inventoried only",
        "table": {"offset": TABLE_OFFSET, "slots": TABLE_SLOTS, "populated_entries": populated,
                  "sha256": digest(raw_table)},
        "summary": {"visible_files": len(files), "compressed_resources": compressed_count,
                    "decoded_blocks": decoded_count, "code_modules": len(modules),
                    "module_formats": dict(sorted(Counter(m["format"] for m in modules).items()))},
        "verified_decoded_checks": sorted(verified_checks),
        "files": files,
        "modules": modules,
        "resources": entries,
    }


def extract(iso_path: Path, destination: Path, profile: dict) -> dict:
    require(not destination.exists() and not destination.is_symlink(),
            f"output already exists: {destination}; choose a new --output directory")
    require(iso_path.stat().st_size == profile["iso_size"], "disc size mismatch")
    log("Verifying complete ISO SHA-256...")
    checksum = hash_file(iso_path)
    require(checksum == profile["iso_sha256"], f"unsupported or modified ISO: SHA-256 {checksum}")
    destination.parent.mkdir(parents=True, exist_ok=True)
    # Publish only a completed extraction; failed runs leave no partial output.
    with TemporaryDirectory(prefix=".so3-extract-", dir=destination.parent) as staging:
        root = Path(staging) / "output"
        root.mkdir()
        manifest = build_inventory(iso_path, root, profile)
        (root / "manifest.json").write_text(
            json.dumps(manifest, indent=2) + "\n", encoding="utf-8", newline="\n")
        require(not destination.exists() and not destination.is_symlink(), "output appeared during extraction")
        root.rename(destination)
    return manifest


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("iso", type=Path, help="path to an unmodified supported US disc ISO")
    parser.add_argument("--version", choices=("us-disc1", "us-disc2"), help="require this release")
    parser.add_argument("--output", type=Path, help="new output directory (default: disc/<version>)")
    args = parser.parse_args(argv)
    try:
        profiles = json.loads(CONFIG.read_text(encoding="utf-8"))["versions"]
        size = args.iso.stat().st_size
        candidates = [(name, profile) for name, profile in profiles.items()
                      if profile["iso_size"] == size and (args.version is None or args.version == name)]
        require(len(candidates) == 1, "unrecognized disc size or wrong --version; supported inputs are in config/manifests/versions.json")
        name, profile = candidates[0]
        destination = args.output if args.output is not None else ROOT / "disc" / name
        manifest = extract(args.iso, destination, profile)
        print(f"Extracted {name} to {destination}")
        print(json.dumps(manifest["summary"], sort_keys=True))
        return 0
    except (FormatError, OSError) as error:
        print(f"Extraction failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
