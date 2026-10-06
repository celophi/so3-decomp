"""Read so3mclib message banks; see ../README.md for the layout.

Message bytes contain glyph indices and commands, not ASCII or Shift-JIS.
Keep those values intact until the associated font mapping is understood.
The bank initialization and key lookup are visible in 00465610 and 00465340;
command parameter lengths below follow the byte traversal in 00465100.
"""

from dataclasses import asdict, dataclass
import struct

from tools.so3.formats import FormatError, require


HEADER_SIZE = 0x44
INDEX_ENTRY = struct.Struct("<II")  # Message key, offset relative to message data.
SUPPORTED_SIGNATURES = (
    b"so3mclib 1.75",
    b"so3mclib 1.80i",
    b"so3mclib 1.81i",
)
EXTENDED_CODE_FLAG = 0x80
COMMAND_FLAG = 0x4000

# These commands consume parameters in 00465100. Their meanings are unresolved.
BYTE_PARAMETERS = {
    0x4002, 0x4008, 0x4012, 0x4013, 0x401A,
    0x401D, 0x4020, 0x4021, 0x4022, 0x4023,
}
WORD_PARAMETERS = {
    0x4005, 0x4006, 0x400A, 0x400C, 0x400E,
    0x4014, 0x4015, 0x401E,
}
STRING_PARAMETERS = {0x4011, 0x401C}


class UnsupportedMessageBank(FormatError):
    """The signature is recognized, but its version has not been validated."""


@dataclass(frozen=True)
class MessageBankHeader:
    """Known header fields, retaining offset-based names for unknown data."""

    signature: str
    index_offset: int
    message_data_offset: int
    unknown_offset_18: int
    unknown_offset_1c: int
    unknown_words_20_to_38: tuple[int, ...]
    entry_count: int
    file_size: int

    @classmethod
    def read(cls, data: bytes) -> "MessageBankHeader":
        require(len(data) >= HEADER_SIZE, "truncated message bank header")
        signature = data[:16].rstrip(b"\0")
        if signature not in SUPPORTED_SIGNATURES:
            raise UnsupportedMessageBank(f"unsupported so3mclib signature: {signature!r}")

        index_offset, message_offset, offset_18, offset_1c = struct.unpack_from("<4I", data, 0x10)
        entry_count, file_size = struct.unpack_from("<II", data, 0x3C)
        header = cls(
            signature=signature.decode("ascii"),
            index_offset=index_offset,
            message_data_offset=message_offset,
            unknown_offset_18=offset_18,
            unknown_offset_1c=offset_1c,
            unknown_words_20_to_38=struct.unpack_from("<7I", data, 0x20),
            entry_count=entry_count,
            file_size=file_size,
        )
        header._validate(len(data))
        return header

    def _validate(self, available_size: int) -> None:
        require(HEADER_SIZE <= self.file_size <= available_size, "message bank size exceeds file")

        # Font-only banks observed in the ZLS resource have no message index.
        is_font_only = (
            self.entry_count == 0
            and self.index_offset == 0
            and self.message_data_offset == 0
        )
        if not is_font_only:
            index_end = self.index_offset + self.entry_count * INDEX_ENTRY.size
            require(
                HEADER_SIZE <= self.index_offset <= index_end <= self.message_data_offset <= self.file_size,
                "message bank index overlaps the header or message data",
            )

        auxiliary_start = max(HEADER_SIZE, self.message_data_offset)
        for offset in (self.unknown_offset_18, self.unknown_offset_1c):
            if offset == 0:
                continue
            require(
                auxiliary_start <= offset <= self.file_size,
                "message bank auxiliary offset exceeds message region",
            )

    @property
    def message_end(self) -> int:
        """Messages must stop before an auxiliary section or the end of the bank."""
        end = self.file_size
        for offset in (self.unknown_offset_18, self.unknown_offset_1c):
            if offset:
                end = min(end, offset)
        return end


@dataclass(frozen=True)
class MessageIndexEntry:
    key: int
    relative_offset: int


def read_message_index(
    data: bytes,
    header: MessageBankHeader,
) -> tuple[list[MessageIndexEntry], int]:
    """Read the sorted keys; message offsets may repeat or point backwards."""
    index_end = header.index_offset + header.entry_count * INDEX_ENTRY.size
    index_data = data[header.index_offset:index_end]
    entries = []
    previous_key = None
    for key, relative_offset in INDEX_ENTRY.iter_unpack(index_data):
        if previous_key is not None:
            require(previous_key < key, "message keys are not strictly increasing")
        entries.append(MessageIndexEntry(key=key, relative_offset=relative_offset))
        previous_key = key

    message_end = header.message_end
    for entry in entries:
        file_offset = header.message_data_offset + entry.relative_offset
        require(
            file_offset < message_end,
            f"message key {entry.key:#x} points outside message data",
        )
    return entries, message_end


def _read_command_parameters(
    data: bytes,
    code: int,
    start: int,
    end: int,
) -> tuple[bytes, int]:
    """Consume parameters before checking for the next message terminator."""
    position = start
    if code in BYTE_PARAMETERS:
        position += 1
    elif code in WORD_PARAMETERS:
        position += 4
    elif code in STRING_PARAMETERS:
        terminator = data.find(b"\0", start, end)
        require(terminator >= 0, "unterminated message command parameter")
        position = terminator + 1

    # Unknown commands consume no parameters in 00465100.
    require(position <= end, f"truncated parameters for command {code:#x}")
    return data[start:position], position


def read_message(
    data: bytes,
    start: int = 0,
    end: int | None = None,
) -> tuple[list[dict], int]:
    """Return glyph runs/control tokens and the size including the terminator.

    Only a zero first byte ends a message. Command parameters can contain zeros,
    so they must be read according to the command's size before continuing.
    """
    if end is None:
        end = len(data)
    require(0 <= start <= end <= len(data), "invalid message bounds")

    tokens = []
    position = start
    while position < end:
        first = data[position]
        position += 1
        if first == 0:
            return tokens, position - start

        code = first
        if first & EXTENDED_CODE_FLAG:
            require(position < end, "truncated two-byte message code")
            code = (first & 0x7F) | (data[position] << 7)
            position += 1

        if code & COMMAND_FLAG:
            parameters, position = _read_command_parameters(data, code, position, end)
            tokens.append({
                "command": f"0x{code:04X}",
                "parameters_hex": parameters.hex(),
            })
        else:
            if not tokens or "glyphs" not in tokens[-1]:
                tokens.append({"glyphs": []})
            tokens[-1]["glyphs"].append(code)

    raise ValueError("unterminated message")


def parse_message_bank(data: bytes) -> dict:
    """Export header fields, indexed messages, original bytes, and numeric tokens."""
    header = MessageBankHeader.read(data)
    entries, message_end = read_message_index(data, header)
    messages = []
    for entry in entries:
        start = header.message_data_offset + entry.relative_offset
        try:
            tokens, size = read_message(data, start, message_end)
        except ValueError as error:
            raise ValueError(f"message key {entry.key:#x}: {error}") from error

        # Entries have no lengths. A key can point to another message's suffix,
        # so we read through its terminator instead of stopping at the next key.
        messages.append({
            "key": entry.key,
            "key_hex": f"0x{entry.key:X}",
            "relative_offset": entry.relative_offset,
            "file_offset": start,
            "size": size,
            "raw_hex": data[start:start + size].hex(),
            "tokens": tokens,
        })

    return {
        "header": asdict(header),
        "messages": messages,
        "text_encoding": "glyph indices; Unicode/font mapping unresolved",
    }
