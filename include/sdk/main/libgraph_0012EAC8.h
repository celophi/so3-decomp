#ifndef SO3_SDK_MAIN_LIBGRAPH_0012EAC8_H
#define SO3_SDK_MAIN_LIBGRAPH_0012EAC8_H

#include "types.h"

#define SCE_GS_NOINTERLACE 0
#define SCE_GS_INTERLACE 1
#define SCE_GS_FIELD 0
#define SCE_GS_FRAME 1
#define SCE_GS_NTSC 2
#define SCE_GS_DTV480P 0x50

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset the GS and set the video output mode.
 * @param mode 0 for a full reset, 1 to reset without changing the display settings.
 * @param inter SCE_GS_INTERLACE or SCE_GS_NOINTERLACE.
 * @param omode Output mode, such as SCE_GS_NTSC or SCE_GS_DTV480P.
 * @param ffmode SCE_GS_FIELD or SCE_GS_FRAME.
 * @see Sony, libgraph reference, sceGsResetGraph.
 */
void sceGsResetGraph(s16 mode, s16 inter, s16 omode, s16 ffmode);

/** @brief Reset GS path 1 to 3 transfers (VIF1, GIF and VU1). */
void sceGsResetPath(void);

/** GS image transfer packet: GIF tags and transfer registers, 16-byte aligned. */
typedef struct GsLoadImage
{
    u8 data[0x60];
} __attribute__((aligned(16))) GsLoadImage;

/**
 * @brief Build an image transfer packet.
 * @param image Packet to fill.
 * @param buffer_pointer Destination VRAM address in 64-word units.
 * @param buffer_width Destination width in 64-pixel units.
 * @param pixel_format Destination pixel format.
 * @param x Destination x.
 * @param y Destination y.
 * @param width Width in pixels.
 * @param height Height in pixels.
 */
void sceGsSetDefLoadImage(GsLoadImage* image, s16 buffer_pointer, s16 buffer_width, s16 pixel_format, s16 x, s16 y,
                          s16 width, s16 height);

/** @brief Send an image to VRAM. @param image Transfer packet. @param source 16-byte aligned pixels. @return Zero. */
s32 sceGsExecLoadImage(GsLoadImage* image, void* source);

#ifdef __cplusplus
}
#endif

#endif
