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

/** Bytes in one VRAM page. */
#define GS_VRAM_PAGE_BYTES (GS_VRAM_PAGE_WORDS * 4)

/** Pixels in one unit of a buffer width (FBW, TBW, DBW). */
#define GS_BUFFER_WIDTH_PIXELS 64

/** Words of VRAM (4 MB). */
#define GS_VRAM_WORDS 0x100000

/** GS pixel formats. */
enum
{
    GS_PSMCT32 = 0x00,
    GS_PSMCT24 = 0x01,
    GS_PSMCT16 = 0x02,
    GS_PSMCT16S = 0x0A,
    GS_PSMZ24 = 0x31,
    GS_PSMZ16 = 0x32,
    GS_PSMZ16S = 0x3A
};

/** TEST depth test methods. */
enum
{
    GS_DEPTH_TEST_GEQUAL = 2
};

/** Centre of the GS primitive coordinate space, in whole pixels. */
#define GS_COORDINATE_CENTRE 0x800

/** Registers a GIF tag's register list can name. */
enum
{
    GIF_REGISTER_PRIM = 0x0,
    GIF_REGISTER_RGBAQ = 0x1,
    GIF_REGISTER_ST = 0x2,
    GIF_REGISTER_UV = 0x3,
    GIF_REGISTER_XYZF2 = 0x4,
    GIF_REGISTER_XYZ2 = 0x5,
    GIF_REGISTER_AD = 0xE
};

/** GS register addresses, as written in A+D form. */
enum
{
    GS_REGISTER_PRIM = 0x00,
    GS_REGISTER_RGBAQ = 0x01,
    GS_REGISTER_TEX0_1 = 0x06,
    GS_REGISTER_TEX0_2 = 0x07,
    GS_REGISTER_CLAMP_1 = 0x08,
    GS_REGISTER_CLAMP_2 = 0x09,
    GS_REGISTER_TEX1_2 = 0x15,
    GS_REGISTER_PRMODECONT = 0x1A,
    GS_REGISTER_TEXCLUT = 0x1C,
    GS_REGISTER_TEXA = 0x3B,
    GS_REGISTER_TEXFLUSH = 0x3F,
    GS_REGISTER_ALPHA_1 = 0x42,
    GS_REGISTER_ALPHA_2 = 0x43,
    GS_REGISTER_TEST_2 = 0x48,
    GS_REGISTER_PABE = 0x49,
    GS_REGISTER_FBA_2 = 0x4B,
    GS_REGISTER_BITBLTBUF = 0x50,
    GS_REGISTER_TRXPOS = 0x51,
    GS_REGISTER_TRXREG = 0x52,
    GS_REGISTER_TRXDIR = 0x53
};

/** Largest 24-bit depth; with the GEQUAL depth test Lib sets, nothing draws in front of it. */
#define GS_DEPTH_NEAREST 0xFFFFFF

/** ALPHA value for the usual (Cs - Cd) * As + Cd blend. */
#define GS_ALPHA_NORMAL 0x44

/** One GS register write in A+D form: the value, then the register address. */
typedef struct GsRegisterValue
{
    u64 data;
    u64 address;
} GsRegisterValue;

/** GIF tag PRE bit: the tag's PRIM field is written to the PRIM register. */
#define GIF_TAG_PRE ((u64)1 << 46)

/** GIF tag PRIM field. */
#define GIF_TAG_PRIM(prim) ((u64)(prim) << 47)

/** TEX0 fields. TBW is an int shift; the rest are 64-bit. */
#define GS_TEX0_TBW(width) ((width) << 14)
#define GS_TEX0_PSM(psm) ((u64)(psm) << 20)
#define GS_TEX0_TW(width_log2) ((u64)(width_log2) << 26)
#define GS_TEX0_TH(height_log2) ((u64)(height_log2) << 30)
#define GS_TEX0_TCC ((u64)1 << 34)

/** PRIM primitive type field and the triangle fan type. */
#define GS_PRIM_TYPE_MASK 0x7
#define GS_PRIM_TRIANGLE_FAN 5

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

/** ZBUF_1/ZBUF_2: the depth buffer a drawing context uses. */
typedef struct GsZbuf
{
    /** Base address in 2048-word pages. */
    u64 base_pointer : 9;
    u64 : 15;
    u64 pixel_format : 4;
    u64 : 4;
    /** Depth values aren't written. */
    u64 mask : 1;
    u64 : 31;
} GsZbuf;

/** One drawing context's registers in A+D form, in the order libgraph's sceGsSetDefDrawEnv fills them. */
typedef struct GsDrawContext
{
    GsFrame frame;
    u64 frame_address;
    GsZbuf depth_buffer;
    u64 depth_buffer_address;
    u64 offset;
    u64 offset_address;
    GsScissor scissor;
    u64 scissor_address;
    u64 primitive_mode;
    u64 primitive_mode_address;
    u64 color_clamp;
    u64 color_clamp_address;
    u64 dither;
    u64 dither_address;
    GsTest test;
    u64 test_address;
} GsDrawContext;

/*
 * The display registers below use libgraph's 32-bit fields, so a display
 * environment is only word aligned and is copied a word at a time.
 */

/** PMODE: which read circuits are shown and how they're blended. */
typedef struct GsPmode
{
    u32 circuit1 : 1;
    u32 circuit2 : 1;
    u32 crt_mode : 3;
    /** Blend with alpha below instead of circuit 1's pixel alpha. */
    u32 fixed_alpha : 1;
    /** Output circuit 2's alpha instead of circuit 1's. */
    u32 alpha_output : 1;
    /** Blend circuit 1 with the background colour instead of circuit 2. */
    u32 blend_background : 1;
    u32 alpha : 8;
    u32 : 16;
    u32 : 32;
} GsPmode;

/** SMODE2: interlace settings. */
typedef struct GsSmode2
{
    u32 interlace : 1;
    u32 field_mode : 1;
    u32 power_mode : 2;
    u32 : 28;
    u32 : 32;
} GsSmode2;

/** DISPFB1/DISPFB2: the frame buffer a read circuit shows. */
typedef struct GsDisplayFrame
{
    /** Base address in 2048-word pages. */
    u32 base_pointer : 9;
    /** Width in 64-pixel units. */
    u32 buffer_width : 6;
    u32 pixel_format : 5;
    u32 : 12;
    u32 x : 11;
    u32 y : 11;
    u32 : 10;
} GsDisplayFrame;

/** DISPLAY1/DISPLAY2: where a read circuit's picture sits on the screen, and its size. */
typedef struct GsDisplay
{
    u32 x : 12;
    u32 y : 11;
    u32 magnify_x : 4;
    u32 magnify_y : 2;
    u32 : 3;
    u32 width : 12;
    u32 height : 11;
    u32 : 9;
} GsDisplay;

/** DISPLAY's DY field (picture top, in lines) on the 64-bit register value. */
#define GS_DISPLAY_Y_SHIFT 12
#define GS_DISPLAY_Y_MASK (0x7FF << GS_DISPLAY_Y_SHIFT)

/** BGCOLOR: the colour blended where circuit 2 isn't shown. */
typedef struct GsBackgroundColor
{
    u32 red : 8;
    u32 green : 8;
    u32 blue : 8;
    u32 : 8;
    u32 : 32;
} GsBackgroundColor;

/** One display setup, in the order libgraph's sceGsPutDispEnv writes it to the GS. */
typedef struct GsDisplayEnvironment
{
    GsPmode pmode;
    GsSmode2 smode2;
    GsDisplayFrame framebuffer;
    GsDisplay display;
    GsBackgroundColor background_color;
} GsDisplayEnvironment;

/** DISPFB1: the frame buffer read circuit 1 shows. */
#define GS_DISPFB1 (*(volatile u64*)0x12000070)

/** DISPLAY1: where read circuit 1's picture sits on the screen. */
#define GS_DISPLAY1 (*(volatile u64*)0x12000080)

/** DISPFB2: the frame buffer read circuit 2 shows. */
#define GS_DISPFB2 (*(volatile u64*)0x12000090)

/** DISPLAY2: where read circuit 2's picture sits on the screen. */
#define GS_DISPLAY2 (*(volatile u64*)0x120000A0)

#endif
