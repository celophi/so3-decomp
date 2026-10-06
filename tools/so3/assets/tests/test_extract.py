"""Extraction output, resource selection, and cleanup after failures."""

import json
from pathlib import Path
from tempfile import TemporaryDirectory
import unittest

from tools.so3.assets.src.containers import AssetExtractor
from tools.so3.assets.src.extract import extract_assets, main, resource_number
from tools.so3.assets.tests.fixtures import create_disc_fixture
from tools.so3.disc.extract import hash_file
from tools.so3.formats import FormatError
from tools.so3.tests.test_extraction import KEY


class AssetTests(unittest.TestCase):
    def test_nested_assets_are_saved_and_manifest_is_repeatable(self):
        with TemporaryDirectory() as folder:
            root = Path(folder)
            iso, profile, bank = create_disc_fixture(root)
            first = extract_assets(iso, root / "first", profile)
            second = extract_assets(iso, root / "second", profile)
            self.assertEqual(first, second)
            self.assertEqual(first["summary"]["message_banks"], 1)
            self.assertEqual(first["summary"]["unresolved_containers"], 1)
            node = next(
                node for node in first["nodes"] if node["format"] == "so3mclib"
            )
            self.assertEqual(node["relationship"], "decompressed")
            self.assertEqual((root / "first" / node["path"]).read_bytes(), bank)
            listing = json.loads((root / "first" / node["messages_path"]).read_text())
            self.assertEqual(listing["messages"][0]["key"], 0x3458)
            self.assertNotIn(str(root), json.dumps(first))
            self.assertEqual(hash_file(iso), profile["iso_sha256"])
            with self.assertRaisesRegex(FormatError, "output already exists"):
                extract_assets(iso, root / "first", profile)

    def test_unknown_or_runtime_only_selection_has_no_output(self):
        with TemporaryDirectory() as folder:
            root = Path(folder)
            iso, profile, _ = create_disc_fixture(root)
            for selection in ([2], [999]):
                with self.subTest(selection=selection):
                    with self.assertRaisesRegex(FormatError, "no physical extent"):
                        extract_assets(iso, root / "out", profile, selection)
                self.assertFalse((root / "out").exists())

    def test_wrong_hash_and_malformed_stream_publish_no_partial_output(self):
        with TemporaryDirectory() as folder:
            root = Path(folder)
            iso, profile, _ = create_disc_fixture(root, malformed=True)
            with self.assertRaisesRegex(FormatError, "resource 1"):
                extract_assets(iso, root / "out", profile)
            self.assertFalse((root / "out").exists())
            self.assertEqual(list(root.glob(".so3-assets-*")), [])
            profile["iso_sha256"] = "0" * 64
            with self.assertRaisesRegex(FormatError, "modified ISO"):
                extract_assets(iso, root / "out", profile)

    def test_selection_leaves_other_resources_out(self):
        with TemporaryDirectory() as folder:
            root = Path(folder)
            iso, profile, _ = create_disc_fixture(root)
            report = extract_assets(iso, root / "out", profile, [0])
            self.assertEqual(report["selection"], [0])
            self.assertEqual(report["nodes"], [])
            self.assertTrue((root / "out/resource-table.json").is_file())

    def test_unknown_leaf_is_saved_without_guessing_its_format(self):
        with TemporaryDirectory() as folder:
            extractor = AssetExtractor(Path(folder), KEY)
            extractor.visit(b"opaque", "0001")
            self.assertEqual(extractor.nodes[0]["status"], "opaque")
            self.assertEqual((Path(folder) / extractor.nodes[0]["path"]).read_bytes(), b"opaque")

    def test_unvalidated_bank_version_is_preserved_as_unresolved(self):
        with TemporaryDirectory() as folder:
            extractor = AssetExtractor(Path(folder), KEY)
            data = b"so3mclib 9.99".ljust(128, b"\0")
            extractor.visit(data, "0001")
            self.assertEqual(extractor.nodes[0]["status"], "unresolved")
            self.assertEqual((Path(folder) / extractor.nodes[0]["path"]).read_bytes(), data)

    def test_resource_numbers_and_missing_input_error(self):
        self.assertEqual(resource_number("0095"), 95)
        self.assertEqual(resource_number("0x5f"), 95)
        self.assertEqual(main(["/nonexistent/so3.iso"]), 1)


if __name__ == "__main__":
    unittest.main()
