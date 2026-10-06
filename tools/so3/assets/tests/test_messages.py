"""Message bank layouts, glyph streams, and command parameter boundaries."""

import struct
import unittest

from tools.so3.assets.src.messages import parse_message_bank, read_message
from tools.so3.assets.tests.fixtures import message_bank


class MessageTests(unittest.TestCase):
    def test_older_observed_bank_signature_uses_same_index_layout(self):
        data = bytearray(message_bank([(5, 0)], b"\x01\0"))
        data[:16] = b"so3mclib 1.75".ljust(16, b"\0")
        self.assertEqual(parse_message_bank(data)["messages"][0]["raw_hex"], "0100")

    def test_font_only_bank_has_no_messages(self):
        data = bytearray(message_bank([], bytes(256)))
        struct.pack_into("<4I", data, 0x10, 0, 0, 0x80, 0x100)
        self.assertEqual(parse_message_bank(data)["messages"], [])

    def test_key_order_differs_from_message_order_and_shared_offsets(self):
        data = message_bank([(5, 2), (6, 0), (7, 2)], b"\x01\0\x02\0")
        bank = parse_message_bank(data)
        self.assertEqual(bank["header"]["entry_count"], 3)
        self.assertEqual([m["raw_hex"] for m in bank["messages"]], ["0200", "0100", "0200"])
        self.assertEqual(bank["messages"][0]["tokens"], [{"glyphs": [2]}])
        self.assertEqual(
            bank["messages"][0]["file_offset"],
            bank["messages"][2]["file_offset"],
        )

    def test_command_parameters_with_zero_bytes_and_two_byte_glyphs(self):
        # Glyphs 1 and 232, command 0x400A with four bytes, glyph 2, terminator.
        data = bytes.fromhex("01 e8 01 8a 80 00 00 80 3f 02 00")
        tokens, size = read_message(data)
        self.assertEqual(size, len(data))
        self.assertEqual(tokens, [
            {"glyphs": [1, 232]},
            {"command": "0x400A", "parameters_hex": "0000803f"},
            {"glyphs": [2]},
        ])

    def test_byte_string_and_unknown_command_traversal(self):
        # A byte parameter, a terminated string, an unknown command, and a glyph.
        data = bytes.fromhex("82 80 00 91 80") + b"name\0" + bytes.fromhex("ff 80 01 00")
        tokens, _ = read_message(data)
        self.assertEqual(tokens[0]["parameters_hex"], "00")
        self.assertEqual(tokens[1]["parameters_hex"], "6e616d6500")
        self.assertEqual(tokens[2], {"command": "0x407F", "parameters_hex": ""})
        self.assertEqual(tokens[-1], {"glyphs": [1]})

    def test_malformed_header_index_and_offsets(self):
        valid = message_bank([(5, 0)], b"\x01\0")
        cases = [
            ("truncated header", valid[:63]),
            ("unsorted keys", message_bank([(6, 0), (5, 0)], b"\x01\0")),
            ("message outside bank", message_bank([(5, 20)], b"\x01\0")),
        ]
        header_changes = [
            ("index inside header", 0x10, 4),
            ("data overlaps index", 0x14, 0x80),
            ("auxiliary table outside bank", 0x18, 100_000),
            ("index count exceeds bank", 0x3C, 100_000),
            ("declared size exceeds data", 0x40, 100_000),
        ]
        for name, offset, value in header_changes:
            data = bytearray(valid)
            struct.pack_into("<I", data, offset, value)
            cases.append((name, data))
        for name, data in cases:
            with self.subTest(case=name), self.assertRaises(ValueError):
                parse_message_bank(data)

    def test_message_boundary_and_truncated_parameters(self):
        truncated_messages = [
            ("missing terminator", b"\x01"),
            ("missing second code byte", b"\x80"),
            ("missing byte parameter", bytes.fromhex("82 80")),
            ("short word parameter", bytes.fromhex("8a 80 00")),
            ("unterminated string parameter", bytes.fromhex("91 80") + b"name"),
        ]
        for name, payload in truncated_messages:
            with self.subTest(case=name), self.assertRaisesRegex(ValueError, "message key 0x5"):
                parse_message_bank(message_bank([(5, 0)], payload))
        # The index has no lengths; two keys can refer to a string and its suffix.
        bank = parse_message_bank(message_bank([(5, 0), (6, 1)], b"\x01\x02\0"))
        self.assertEqual([m["raw_hex"] for m in bank["messages"]], ["010200", "0200"])

    def test_auxiliary_tables_bound_messages_and_allocation_padding_is_allowed(self):
        data = bytearray(message_bank([(5, 0)], b"\x01\0AUX"))
        message_offset = struct.unpack_from("<I", data, 0x14)[0]
        struct.pack_into("<I", data, 0x18, message_offset + 2)
        bank = parse_message_bank(bytes(data) + bytes(128))
        self.assertEqual(bank["messages"][0]["raw_hex"], "0100")
        data[message_offset + 1] = 2
        with self.assertRaises(ValueError):
            parse_message_bank(data)


if __name__ == "__main__":
    unittest.main()
