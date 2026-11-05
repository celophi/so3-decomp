#ifndef SO3_GS_H
#define SO3_GS_H

#include "types.h"

/*
 * GS (Graphics Synthesizer) register layouts as the game stores them: one
 * 64-bit word per register, written to the GS in A+D form (data, then the
 * register address). Field positions are from the GS User's Manual.
 */

/** Words in one VRAM block, the unit texture and transfer addresses use. */
#define GS_VRAM_BLOCK_WORDS 64

/** Words in one VRAM page, the unit frame buffer addresses use. */
#define GS_VRAM_PAGE_WORDS 2048

/** Pixels in one unit of a buffer width (FBW, TBW, DBW). */
#define GS_BUFFER_WIDTH_PIXELS 64

/** Words of VRAM (4 MB). */
#define GS_VRAM_WORDS 0x100000

/** GS pixel formats. */
enum
{
    GS_PSMCT32 = 0x00,
    GS_PSMCT24 = 0x01
};

/** Centre of the GS primitive coordinate space, in whole pixels. */
#define GS_COORDINATE_CENTRE 0x800

/** Registers a GIF tag's register list can name. */
enum
{
    GIF_REGISTER_PRIM = 0x0,
    GIF_REGISTER_RGBAQ = 0x1,
    GIF_REGISTER_UV = 0x3,
    GIF_REGISTER_XYZ2 = 0x5,
    GIF_REGISTER_AD = 0xE
};

/** GS register addresses, as written in A+D form. */
enum
{
    GS_REGISTER_PRIM = 0x00,
    GS_REGISTER_RGBAQ = 0x01,
    GS_REGISTER_TEX0_2 = 0x07,
    GS_REGISTER_TEXFLUSH = 0x3F,
    GS_REGISTER_ALPHA_1 = 0x42,
    GS_REGISTER_ALPHA_2 = 0x43,
    GS_REGISTER_BITBLTBUF = 0x50,
    GS_REGISTER_TRXPOS = 0x51,
    GS_REGISTER_TRXREG = 0x52,
    GS_REGISTER_TRXDIR = 0x53
};

/** GIF tag EOP bit: this is the transfer's last tag. */
#define GIF_TAG_EOP 0x8000

/** GIF tag NREG field: how many registers each loop writes. */
#define GIF_TAG_NREG(count) ((u64)(count) << 60)

/** GIF tag: the tag word and the register list, four bits per register. */
typedef struct GsGifTag
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
            u64 register4 : 4;
            u64 register5 : 4;
            u64 unused : 40;
        } fields;
    };
} GsGifTag;

/**
 * @brief Clear a whole GIF tag, tag word and register list, with one 128-bit store.
 * @param tag Tag to clear.
 * @see Sony's libgraph clears tags the same way with SCE_GIF_CLEAR_TAG.
 */
static inline void gs_clear_gif_tag(GsGifTag* tag)
{
    *(unsigned __int128*)tag = 0;
}

/** FRAME_1/FRAME_2: the frame buffer a drawing context writes to. */
typedef struct GsFrame
{
    /** Base address in 2048-word pages. */
    u64 base_pointer : 9;
    u64 : 7;
    /** Width in 64-pixel units. */
    u64 buffer_width : 6;
    u64 : 2;
    u64 pixel_format : 6;
    u64 : 2;
    /** Bits that drawing doesn't write. */
    u64 draw_mask : 32;
} GsFrame;

/** SCISSOR_1/SCISSOR_2: the inclusive pixel rectangle drawing is clipped to. */
typedef struct GsScissor
{
    u64 x0 : 11;
    u64 : 5;
    u64 x1 : 11;
    u64 : 5;
    u64 y0 : 11;
    u64 : 5;
    u64 y1 : 11;
    u64 : 5;
} GsScissor;

/** TEST_1/TEST_2: the alpha, destination alpha and depth tests. */
typedef struct GsTest
{
    u64 alpha_test : 1;
    u64 alpha_method : 3;
    u64 alpha_reference : 8;
    u64 alpha_fail : 2;
    u64 destination_alpha_test : 1;
    u64 destination_alpha_mode : 1;
    u64 depth_test : 1;
    u64 depth_method : 2;
    u64 : 45;
} GsTest;

#endif
