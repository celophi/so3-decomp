"""Readable previews must preserve unknown glyphs and control commands."""

import json
from pathlib import Path
import struct
from tempfile import TemporaryDirectory
import unittest

from tools.so3.assets.src.containers import AssetExtractor
from tools.so3.assets.src.messages import parse_message_bank
from tools.so3.assets.src.text import US_DISC1_SHARED_FONT, mapping_for_disc, text_preview
from tools.so3.assets.tests.fixtures import message_bank
from tools.so3.tests.test_extraction import KEY


class TextPreviewTests(unittest.TestCase):
    def test_known_latin_characters_and_spaces(self):
        tokens = [{"glyphs": [1, 10, 14, 39, 40, 65, 232, 233, 11, 12, 13]}]
        result = text_preview(tokens, US_DISC1_SHARED_FONT, uses_shared_font=True)
        self.assertEqual(result["text_preview"], "09AZaz  -.'")
        self.assertTrue(result["text_complete"])
        self.assertEqual(result["unmapped_glyphs"], [])

    def test_unknown_and_bank_specific_glyphs_remain_visible(self):
        tokens = [{"glyphs": [16, 66, 301, 66, 28]}]
        result = text_preview(tokens, US_DISC1_SHARED_FONT, uses_shared_font=True)
        self.assertEqual(result["text_preview"], "C<glyph:0x42><glyph:0x12d><glyph:0x42>O")
        self.assertFalse(result["text_complete"])
        self.assertEqual(result["unmapped_glyphs"], [66, 301])

    def test_local_font_does_not_inherit_shared_character_names(self):
        result = text_preview(
            [{"glyphs": [16, 28]}],
            US_DISC1_SHARED_FONT,
            uses_shared_font=False,
        )
        self.assertEqual(result["text_preview"], "<glyph:0x10><glyph:0x1c>")
        self.assertFalse(result["text_complete"])

    def test_commands_keep_their_position_and_raw_parameters(self):
        tokens = [
            {"glyphs": [14]},
            {"command": "0x4002", "parameters_hex": "00"},
            {"glyphs": [15]},
        ]
        result = text_preview(tokens, US_DISC1_SHARED_FONT, uses_shared_font=True)
        self.assertEqual(result["text_preview"], "A<command:0x4002:00>B")
        self.assertFalse(result["text_complete"])
        self.assertEqual(result["unmapped_glyphs"], [])

    def test_parser_adds_preview_without_changing_raw_fields(self):
        data = bytearray(message_bank([(0x3458, 0)], bytes.fromhex("10 1c 1c 18 00")))
        struct.pack_into("<I", data, 0x38, 301)
        original = parse_message_bank(data)["messages"][0]
        bank = parse_message_bank(data, US_DISC1_SHARED_FONT)
        message = bank["messages"][0]
        self.assertEqual(message["text_preview"], "COOK")
        self.assertTrue(message["text_complete"])
        for field, value in original.items():
            self.assertEqual(message[field], value)
        self.assertEqual(bank["text_mapping"]["name"], "us-disc1-shared-font")

    def test_extraction_writes_the_text_preview_to_messages_json(self):
        data = bytearray(message_bank([(5, 0)], bytes.fromhex("0e 0f 00")))
        struct.pack_into("<I", data, 0x38, 301)
        with TemporaryDirectory() as folder:
            root = Path(folder)
            extractor = AssetExtractor(root, KEY, glyph_mapping=US_DISC1_SHARED_FONT)
            extractor.visit(data, "0001")
            path = root / extractor.nodes[0]["messages_path"]
            message = json.loads(path.read_text())["messages"][0]
            self.assertEqual(message["text_preview"], "AB")
            self.assertTrue(message["text_complete"])

    def test_unverified_discs_do_not_get_a_mapping(self):
        self.assertIs(mapping_for_disc({"serial": "SLUS-20488"}), US_DISC1_SHARED_FONT)
        self.assertIsNone(mapping_for_disc({"serial": "SLUS-20891"}))
        self.assertIsNone(mapping_for_disc({"serial": "SYNTHETIC"}))


if __name__ == "__main__":
    unittest.main()
