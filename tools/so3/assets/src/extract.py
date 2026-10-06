"""Extract SO3 resource trees and indexed message banks from a verified disc."""

import argparse
from collections import Counter
import json
from pathlib import Path
import sys
from tempfile import TemporaryDirectory
from typing import BinaryIO

from tools.so3 import ROOT
from tools.so3.assets.src.containers import AssetExtractor, write_json
from tools.so3.disc.extract import CONFIG, digest, hash_file, read_at
from tools.so3.formats import FormatError, TABLE_OFFSET, TABLE_SIZE, read_table, require


def extract_assets(
    iso: Path,
    destination: Path,
    profile: dict,
    resources: list[int] | None = None,
) -> dict:
    """Extract into a temporary directory and move it into place on success."""
    require(
        not destination.exists() and not destination.is_symlink(),
        "output already exists; choose a new --output directory",
    )
    _verify_disc(iso, profile)
    selection = None if resources is None else set(resources)
    destination.parent.mkdir(parents=True, exist_ok=True)

    # Keeping the temporary files beside the destination lets us rename the
    # completed directory. An exception removes the unfinished extraction.
    with TemporaryDirectory(prefix=".so3-assets-", dir=destination.parent) as temporary:
        staging = Path(temporary) / "output"
        staging.mkdir()
        extractor = AssetExtractor(staging, bytes.fromhex(profile["sle_key"]))
        with iso.open("rb") as stream:
            entries = _read_resource_table(stream, staging, profile, selection)
            _extract_selected_resources(stream, extractor, entries, selection)

        report = _build_manifest(profile, extractor.nodes, selection)
        write_json(staging / "manifest.json", report)
        require(
            not destination.exists() and not destination.is_symlink(),
            "output appeared during extraction",
        )
        staging.rename(destination)

    return report


def _verify_disc(iso: Path, profile: dict) -> None:
    require(iso.stat().st_size == profile["iso_size"], "disc size mismatch")
    print("Verifying complete ISO SHA-256...", file=sys.stderr, flush=True)
    require(hash_file(iso) == profile["iso_sha256"], "unsupported or modified ISO")


def _read_resource_table(
    stream: BinaryIO,
    destination: Path,
    profile: dict,
    selection: set[int] | None,
) -> list[dict]:
    raw_table = read_at(stream, TABLE_OFFSET, TABLE_SIZE)
    require(digest(raw_table) == profile["table_sha256"], "resource table hash mismatch")
    entries = read_table(raw_table, profile["iso_size"])
    allocated_indices = {entry["index"] for entry in entries if entry["sectors"]}
    require(
        len(allocated_indices) == profile["populated_entries"],
        "resource table entry count mismatch",
    )
    if selection is not None:
        missing_indices = sorted(selection - allocated_indices)
        require(
            not missing_indices,
            f"requested resources have no physical extent: {missing_indices}",
        )

    (destination / "resource-table.bin").write_bytes(raw_table)
    write_json(destination / "resource-table.json", entries)
    return entries


def _extract_selected_resources(
    stream: BinaryIO,
    extractor: AssetExtractor,
    entries: list[dict],
    selection: set[int] | None,
) -> None:
    for entry in entries:
        index = entry["index"]
        # Slot zero is the table, which was saved separately above.
        if index == 0 or not entry["sectors"]:
            continue
        if selection is not None and index not in selection:
            continue

        try:
            extractor.extract_resource(stream, entry)
        except ValueError as error:
            raise FormatError(f"resource {index}: {error}") from error

        if index % 100 == 0:
            print(
                f"Extracted through resource {index}; {len(extractor.nodes)} nodes",
                file=sys.stderr,
                flush=True,
            )


def _build_manifest(profile: dict, nodes: list[dict], selection: set[int] | None) -> dict:
    format_counts = Counter(node["format"] for node in nodes)
    message_banks = 0
    unresolved_containers = 0
    for node in nodes:
        if "messages_path" in node:
            message_banks += 1
        if node["status"] == "unresolved":
            unresolved_containers += 1

    return {
        "schema_version": 1,
        "disc": {
            "serial": profile["serial"],
            "disc": profile["disc"],
            "region": profile["region"],
            "revision": profile["revision"],
            "iso_sha256": profile["iso_sha256"],
        },
        "selection": "all" if selection is None else sorted(selection),
        "resource_table": "resource-table.json",
        "summary": {
            "nodes": len(nodes),
            "formats": dict(sorted(format_counts.items())),
            "message_banks": message_banks,
            "unresolved_containers": unresolved_containers,
        },
        "nodes": nodes,
    }


def resource_number(value: str) -> int:
    """Accept a decimal or explicitly hexadecimal disc resource index."""
    base = 16 if value.lower().startswith("0x") else 10
    try:
        number = int(value, base)
        if number < 0:
            raise ValueError
        return number
    except ValueError as error:
        raise argparse.ArgumentTypeError(
            "resource must be a nonnegative decimal or hexadecimal index"
        ) from error


def _select_profile(iso: Path, requested_version: str | None) -> tuple[str, dict]:
    profiles = json.loads(CONFIG.read_text(encoding="utf-8"))["versions"]
    disc_size = iso.stat().st_size
    candidates = []
    for name, profile in profiles.items():
        if requested_version is not None and name != requested_version:
            continue
        if profile["iso_size"] == disc_size:
            candidates.append((name, profile))

    require(len(candidates) == 1, "unrecognized disc size or wrong --version")
    return candidates[0]


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("iso", type=Path, help="unmodified supported US disc ISO")
    parser.add_argument("--version", choices=("us-disc1", "us-disc2"))
    parser.add_argument(
        "--output",
        type=Path,
        help="new directory; default assets/<version> at repository root",
    )
    parser.add_argument(
        "--resource",
        action="append",
        type=resource_number,
        help="extract only this disc resource index; repeat to select several (not a message key)",
    )
    args = parser.parse_args(argv)
    try:
        name, profile = _select_profile(args.iso, args.version)
        destination = args.output or ROOT / "assets" / name
        report = extract_assets(args.iso, destination, profile, args.resource)
        print(f"Extracted assets to {destination}")
        print(json.dumps(report["summary"], sort_keys=True))
        return 0
    except (OSError, ValueError) as error:
        print(f"Asset extraction failed: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
