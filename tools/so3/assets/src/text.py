"""Partial character mappings for fonts whose glyphs have been inspected."""

from dataclasses import dataclass


SHARED_FONT_CODE_LIMIT = 300
SPACE_CODES = (0xE8, 0xE9)


@dataclass(frozen=True)
class GlyphMapping:
    name: str
    source: str
    characters: dict[int, str]


def _us_disc1_characters() -> dict[int, str]:
    # The shared font in resource 8 stores these glyphs in this order.
    # Message codes are one-based; bitmap indices are zero-based.
    characters = {}
    latin_glyphs = "0123456789-.'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    for code, character in enumerate(latin_glyphs, start=1):
        characters[code] = character

    # 004645F0 treats both space codes as non-drawing glyphs. Their bitmaps
    # are blank. The parentheses were identified from the same font sheet.
    for code in SPACE_CODES:
        characters[code] = " "
    characters[244] = ")"
    characters[263] = "("
    return characters


US_DISC1_SHARED_FONT = GlyphMapping(
    name="us-disc1-shared-font",
    source="resources/0008/zls-0002/block-0000/data.bin",
    characters=_us_disc1_characters(),
)


def mapping_for_disc(profile: dict) -> GlyphMapping | None:
    """Use a mapping only for a disc whose shared font has been checked."""
    if profile["serial"] == "SLUS-20488":
        return US_DISC1_SHARED_FONT
    return None


def text_preview(tokens: list[dict], mapping: GlyphMapping, uses_shared_font: bool) -> dict:
    """Show known characters without hiding unknown glyphs or control commands."""
    parts = []
    unmapped_glyphs = set()
    complete = True
    for token in tokens:
        if "command" in token:
            command = token["command"]
            parameters = token["parameters_hex"]
            parts.append(f"<command:{command}:{parameters}>")
            complete = False
            continue

        for code in token["glyphs"]:
            character = None
            if uses_shared_font and code <= SHARED_FONT_CODE_LIMIT:
                character = mapping.characters.get(code)
            if character is None:
                parts.append(f"<glyph:{code:#x}>")
                unmapped_glyphs.add(code)
                complete = False
            else:
                parts.append(character)

    return {
        "text_preview": "".join(parts),
        "text_complete": complete,
        "unmapped_glyphs": sorted(unmapped_glyphs),
    }
