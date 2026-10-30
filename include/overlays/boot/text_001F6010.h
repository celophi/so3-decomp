#ifndef SO3_OVERLAYS_BOOT_TEXT_001F6010_H
#define SO3_OVERLAYS_BOOT_TEXT_001F6010_H

#include "types.h"
#include "overlays/boot/text_001DD3C0.h"

/** Settings record initialized before calls to the resident rendering interface. */
typedef struct BootDrawSettings
{
    /** GS PRIM bits: 0xC is a Gouraud-shaded triangle strip; 0x5C adds texture mapping and alpha blending. */
    u16 prim;

    u8 unk02;

    /** Which of the draw buffer's textures to draw with; the palette quad uses 1. */
    u8 texture_index;

    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    float unk08;
    float unk0C;
    float unk10;
    float unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
} BootDrawSettings;

#ifdef __cplusplus
/** GIF tag: the tag word and the register list, four bits per register. */
struct BootGifTag
{
    u64 tag;

    union
    {
        u64 registers;

        struct
        {
            u64 register0 : 4;
            u64 register1 : 4;
            u64 register2 : 4;
            u64 register3 : 4;
            u64 unused : 48;
        } fields;
    };
};

/** One fade strip's packet: upload the strip's image to VRAM, then draw it as a textured sprite. */
struct BootFadeStripPacket
{
    u64 transfer_dma;

    /** Upper half of the DMA tag; left unwritten, as the tag doesn't transfer it. */
    u64 transfer_dma_high;

    BootGifTag transfer_tag;
    u64 bitbltbuf;
    u64 bitbltbuf_register;
    u64 trxpos;
    u64 trxpos_register;
    u64 trxreg;
    u64 trxreg_register;
    u64 trxdir;
    u64 trxdir_register;
    u64 image_tag;

    /** REGS half of the IMAGE-mode GIF tag; unused, so left unwritten. */
    u64 image_tag_registers;

    u64 image_dma;
    u64 image_dma_high;
    u64 draw_dma;
    u64 draw_dma_high;
    BootGifTag draw_tag;
    u64 texflush;
    u64 texflush_register;
    u64 tex0;
    u64 tex0_register;
    u64 prim;
    u64 prim_register;
    u64 rgbaq;
    u64 rgbaq_register;
    BootGifTag sprite_tag;
    u64 uv0;
    u64 xyz0;
    u64 uv1;
    u64 xyz1;
};

/** VRAM area request passed to func_4D93A0. */
struct BootVramRequest
{
    s16 width;
    s16 height;
    s32 size;
    u8 unk08[4];

    /** GS pixel storage mode (1 is PSMCT24). */
    s16 psm;

    /** Texture width as a power of two (TEX0's TW). */
    u8 width_log2;

    /** Texture height as a power of two (TEX0's TH). */
    u8 height_log2;
};

extern "C" {
#endif

/**
 * @brief Initialize the settings record to its default values.
 * @param settings Settings record to initialize.
 */
void init_draw_settings(BootDrawSettings* settings);

/**
 * @brief Build an image's quad from a rectangle of its texture and a rectangle of its palette, and queue the
 * model for drawing.
 * @param image Image to build.
 * @param x Left edge of the texture rectangle, in texels.
 * @param y Top edge of the texture rectangle.
 * @param width Rectangle width, which is also the quad's width.
 * @param height Rectangle height, which is also the quad's height.
 * @param palette_x Left edge of the palette rectangle.
 * @param palette_y Top edge of the palette rectangle.
 * @param palette_width Palette rectangle width.
 * @param palette_height Palette rectangle height.
 * @param color Vertex color.
 * @param depth Z position of the quad.
 */
void image_set_rectangle_with_palette(BootImage* image, s32 x, s32 y, s32 width, s32 height, s32 palette_x, s32 palette_y, s32 palette_width,
                                      s32 palette_height, u32 color, s32 depth);

/**
 * @brief Encode a saved record and seal it with a fresh checksum; a damaged record is wiped instead.
 * @param record Record to seal; an already sealed record is left alone.
 */
void seal_record(BootSealedRecord* record);

/**
 * @brief Draw a progress bar: a dark border, the bar outline and a fill proportional to done / total.
 * @param bar Progress bar to draw.
 * @param done Completed amount; clamped to total.
 * @param total Total amount.
 */
void progress_bar_draw(BootProgressBar* bar, s32 done, s32 total);

/**
 * @brief Recreate the bar's draw buffer and model, then draw it empty and show it.
 * @param bar Progress bar.
 * @param width Bar width.
 * @param height Bar height.
 * @param color Bar color.
 * @param mode Draw mode.
 */
void progress_bar_reset(BootProgressBar* bar, s32 width, s32 height, u32 color, s32 mode);

#ifdef __cplusplus
}
#endif

#endif
