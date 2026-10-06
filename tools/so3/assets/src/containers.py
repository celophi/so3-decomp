"""Save resource trees while expanding the container formats we understand."""

import json
from pathlib import Path
from typing import BinaryIO

from tools.so3.assets.src.messages import UnsupportedMessageBank, parse_message_bank
from tools.so3.disc.archives import pack_entries, zls_entries
from tools.so3.disc.extract import hash_file, read_at, save
from tools.so3.formats import (
    FormatError,
    MAX_DECODED_SIZE,
    classify,
    decode_chain,
    require,
)


MAX_DEPTH = 16
MAX_NODES = 200_000
MAX_EXPANDED_BYTES = 8 * 1024**3
COPY_CHUNK_SIZE = 1024**2
BLOCK_HEADER_SIZE = 16


def asset_format(data: bytes) -> str:
    if data.startswith(b"so3mclib "):
        return "so3mclib"
    return classify(data)


def write_json(path: Path, value: dict | list) -> None:
    path.write_text(json.dumps(value, indent=2) + "\n", encoding="utf-8")


class AssetExtractor:
    """Keep original bytes and record how each extracted child relates to its parent."""

    def __init__(self, destination: Path, key: bytes):
        self.destination = destination
        self.sle_key = key
        self.nodes: list[dict] = []
        self.expanded_bytes = 0

    def extract_resource(self, stream: BinaryIO, entry: dict) -> None:
        """Read one disc allocation, streaming large unknown resources to disk."""
        location = f'{entry["index"]:04d}'
        size = entry["allocated_size"]
        header = read_at(stream, entry["offset"], min(BLOCK_HEADER_SIZE, size))
        kind = asset_format(header)

        if size > MAX_DECODED_SIZE:
            require(kind == "unknown", f"{kind} allocation exceeds supported limit")
            self._copy_opaque_resource(stream, entry, location)
            return

        data = read_at(stream, entry["offset"], size)
        self.visit(data, location)

    def visit(
        self,
        data: bytes,
        location: str,
        *,
        parent: str | None = None,
        offset: int | None = None,
        depth: int = 0,
        relationship: str = "slice",
    ) -> None:
        """Save a payload, then inspect any children inside a supported container."""
        require(depth <= MAX_DEPTH, "asset nesting exceeds supported limit")
        require(len(self.nodes) < MAX_NODES, "asset node count exceeds supported limit")

        kind = asset_format(data)
        stored = save(self.destination, f"resources/{location}/data.bin", data)
        node = {
            **stored,
            "location": location,
            "format": kind,
            "parent": parent,
            "offset_in_parent": offset,
            "status": "opaque",
            "relationship": relationship if parent is not None else "disc-resource",
        }
        self.nodes.append(node)

        if kind == "so3mclib":
            self._extract_messages(data, node)
        elif kind == "PACK":
            self._expand_pack(data, node, depth)
        elif kind == "ZLS":
            entries = zls_entries(data)
            self._extract_members(data, node, entries, "zls", depth)
        elif kind.startswith(("SLZ", "SLE")):
            self._expand_compressed_blocks(data, node, depth)

    def _extract_messages(self, data: bytes, node: dict) -> None:
        location = node["location"]
        try:
            bank = parse_message_bank(data)
        except UnsupportedMessageBank as error:
            node.update(status="unresolved", reason=str(error))
            return
        except ValueError as error:
            raise FormatError(f"bank {location}: {error}") from error

        relative_path = f"resources/{location}/messages.json"
        write_json(self.destination / relative_path, bank)
        node.update(
            status="parsed",
            messages_path=relative_path,
            message_count=len(bank["messages"]),
        )

    def _expand_pack(self, data: bytes, node: dict, depth: int) -> None:
        try:
            entries = pack_entries(data)
        except FormatError as error:
            # External index tables also start with PACK. Keep them for later
            # rather than interpreting their offsets as files in this buffer.
            node.update(status="unresolved", reason=str(error))
            return

        self._extract_members(data, node, entries, "pack", depth)

    def _extract_members(
        self,
        data: bytes,
        node: dict,
        entries: list[dict],
        prefix: str,
        depth: int,
    ) -> None:
        node.update(status="expanded", entries=entries)
        location = node["location"]
        for entry in entries:
            member_data = data[entry["offset"]:entry["end"]]
            member_location = f'{location}/{prefix}-{entry["index"]:04d}'
            self.visit(
                member_data,
                member_location,
                parent=location,
                offset=entry["offset"],
                depth=depth + 1,
            )

    def _expand_compressed_blocks(self, data: bytes, node: dict, depth: int) -> None:
        node.update(status="expanded", blocks=[])
        location = node["location"]
        for index, block in enumerate(decode_chain(data, self.sle_key)):
            self.expanded_bytes += len(block.data)
            require(
                self.expanded_bytes <= MAX_EXPANDED_BYTES,
                "expanded asset size exceeds supported limit",
            )
            node["blocks"].append({
                "index": index,
                "header_offset": block.offset,
                "encoding": block.encoding,
                "compressed_size": block.compressed_size,
                "decoded_size": len(block.data),
                "next_offset": block.next_offset,
            })
            self.visit(
                block.data,
                f"{location}/block-{index:04d}",
                parent=location,
                offset=block.offset + BLOCK_HEADER_SIZE,
                depth=depth + 1,
                relationship="decompressed",
            )

    def _copy_opaque_resource(self, stream: BinaryIO, entry: dict, location: str) -> None:
        # Audio and other large unknown files don't need to fit in memory.
        require(len(self.nodes) < MAX_NODES, "asset node count exceeds supported limit")
        relative_path = f"resources/{location}/data.bin"
        path = self.destination / relative_path
        path.parent.mkdir(parents=True)
        stream.seek(entry["offset"])
        remaining = entry["allocated_size"]
        with path.open("wb") as output:
            while remaining:
                chunk = stream.read(min(remaining, COPY_CHUNK_SIZE))
                require(bool(chunk), "truncated opaque resource")
                output.write(chunk)
                remaining -= len(chunk)

        self.nodes.append({
            "path": relative_path,
            "location": location,
            "size": entry["allocated_size"],
            "sha256": hash_file(path),
            "format": "unknown",
            "parent": None,
            "offset_in_parent": None,
            "status": "opaque",
            "relationship": "disc-resource",
        })
