"""Large opaque resources must be copied in bounded reads without losing bytes."""

from io import BytesIO
from pathlib import Path
from tempfile import TemporaryDirectory
import unittest
from unittest.mock import Mock, patch

from tools.so3.assets.src.containers import AssetExtractor
from tools.so3.disc.extract import digest
from tools.so3.formats import FormatError
from tools.so3.tests.test_extraction import KEY


class StreamingResourceTests(unittest.TestCase):
    def test_streaming_preserves_bytes_offsets_and_hashes(self):
        padding = b"unused prefix"
        payload = b"opaque audio data" * 10
        entry = {
            "index": 1,
            "offset": len(padding),
            "allocated_size": len(payload),
        }
        stream = Mock(wraps=BytesIO(padding + payload))
        with TemporaryDirectory() as folder:
            root = Path(folder)
            extractor = AssetExtractor(root, KEY)
            # Exercise the large-resource path without a multi-megabyte fixture.
            with patch("tools.so3.assets.src.containers.MAX_DECODED_SIZE", 16):
                with patch("tools.so3.assets.src.containers.COPY_CHUNK_SIZE", 7):
                    extractor.extract_resource(stream, entry)

            node = extractor.nodes[0]
            self.assertEqual((root / node["path"]).read_bytes(), payload)
            self.assertEqual(node["size"], len(payload))
            self.assertEqual(node["sha256"], digest(payload))
            self.assertEqual(node["relationship"], "disc-resource")
            self.assertIsNone(node["offset_in_parent"])
            # The first read identifies the format; remaining reads copy chunks.
            read_sizes = [call.args[0] for call in stream.read.call_args_list]
            self.assertEqual(read_sizes[0], 16)
            self.assertTrue(all(0 < size <= 7 for size in read_sizes[1:]))

    def test_truncated_stream_does_not_register_a_complete_resource(self):
        payload = b"opaque audio data" * 2
        entry = {"index": 1, "offset": 0, "allocated_size": len(payload) + 10}
        with TemporaryDirectory() as folder:
            extractor = AssetExtractor(Path(folder), KEY)
            with patch("tools.so3.assets.src.containers.MAX_DECODED_SIZE", 16):
                with self.assertRaisesRegex(FormatError, "truncated opaque resource"):
                    extractor.extract_resource(BytesIO(payload), entry)
            self.assertEqual(extractor.nodes, [])

    def test_streaming_obeys_the_same_node_limit_as_small_resources(self):
        payload = b"opaque audio data" * 2
        entry = {"index": 1, "offset": 0, "allocated_size": len(payload)}
        with TemporaryDirectory() as folder:
            root = Path(folder)
            extractor = AssetExtractor(root, KEY)
            with patch("tools.so3.assets.src.containers.MAX_DECODED_SIZE", 16):
                with patch("tools.so3.assets.src.containers.MAX_NODES", 0):
                    with self.assertRaisesRegex(FormatError, "node count"):
                        extractor.extract_resource(BytesIO(payload), entry)
            self.assertEqual(list(root.iterdir()), [])


if __name__ == "__main__":
    unittest.main()
