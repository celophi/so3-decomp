#ifndef SO3_SDK_MAIN_LIBGRAPH_0012EAC8_H
#define SO3_SDK_MAIN_LIBGRAPH_0012EAC8_H

#include "types.h"
#include "gs.h"

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

/**
 * @brief Fill a display environment with the defaults for a frame buffer of the given size.
 * @param environment Environment to fill.
 * @param pixel_format Frame buffer pixel format.
 * @param width Width in pixels.
 * @param height Height in pixels.
 * @param x Horizontal offset of the picture.
 * @param y Vertical offset of the picture.
 * @see Sony, libgraph reference, sceGsSetDefDispEnv.
 */
void sceGsSetDefDispEnv(GsDisplayEnvironment* environment, s16 pixel_format, s16 width, s16 height, s16 x, s16 y);

/**
 * @brief Write a display environment to the GS's privileged registers.
 * @param environment Environment to write.
 * @see Sony, libgraph reference, sceGsPutDispEnv.
 */
void sceGsPutDispEnv(GsDisplayEnvironment* environment);

/**
 * @brief Fill a context-1 drawing context with the defaults for a draw buffer of the given size.
 * @param context Context to fill.
 * @param pixel_format Frame buffer pixel format.
 * @param width Width in pixels.
 * @param height Height in pixels.
 * @param depth_test Depth test method, or 0 for none.
 * @param depth_format Depth buffer pixel format.
 * @return Quadwords the context takes.
 * @see Sony, libgraph reference, sceGsSetDefDrawEnv.
 */
s32 sceGsSetDefDrawEnv(GsDrawContext* context, s16 pixel_format, s16 width, s16 height, s16 depth_test,
                       s16 depth_format);

/**
 * @brief The context-2 version of sceGsSetDefDrawEnv.
 * @param context Context to fill.
 * @param pixel_format Frame buffer pixel format.
 * @param width Width in pixels.
 * @param height Height in pixels.
 * @param depth_test Depth test method, or 0 for none.
 * @param depth_format Depth buffer pixel format.
 * @return Quadwords the context takes.
 * @see Sony, libgraph reference, sceGsSetDefDrawEnv2.
 */
s32 sceGsSetDefDrawEnv2(GsDrawContext* context, s16 pixel_format, s16 width, s16 height, s16 depth_test,
                        s16 depth_format);

/**
 * @brief Send a drawing environment that starts with a GIF tag to the GS through path 3.
 * @param tag The environment's GIF tag.
 * @return Zero.
 * @see Sony, libgraph reference, sceGsPutDrawEnv.
 */
s32 sceGsPutDrawEnv(GsGifTag* tag);

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

/** GS image read-back packet: VIF codes, GIF tag and transfer registers, 16-byte aligned. */
typedef struct GsStoreImage
{
    u8 data[0x70];
} __attribute__((aligned(16))) GsStoreImage;

/**
 * @brief Build a packet that copies a VRAM rectangle back to main memory.
 * @param image Packet to fill.
 * @param buffer_pointer Source VRAM address in 64-word units.
 * @param buffer_width Source width in 64-pixel units.
 * @param pixel_format Source pixel format.
 * @param x Source x.
 * @param y Source y.
 * @param width Width in pixels.
 * @param height Height in pixels.
 */
void sceGsSetDefStoreImage(GsStoreImage* image, s16 buffer_pointer, s16 buffer_width, s16 pixel_format, s16 x, s16 y,
                           s16 width, s16 height);

/**
 * @brief Set a context-1 drawing environment's XYOFFSET so its scissor area is centred, half a pixel lower on odd
 *        fields.
 * @param draw Drawing environment (its FRAME_1 register).
 * @param center_x Centre x in whole pixels.
 * @param center_y Centre y in whole pixels.
 * @param half_offset Nonzero for the half-pixel offset.
 * @see Sony, libgraph reference, sceGsSetHalfOffset.
 */
void sceGsSetHalfOffset(void* draw, s16 center_x, s16 center_y, s16 half_offset);

/**
 * @brief The context-2 version of sceGsSetHalfOffset.
 * @param draw Drawing environment (its FRAME_2 register).
 * @param center_x Centre x in whole pixels.
 * @param center_y Centre y in whole pixels.
 * @param half_offset Nonzero for the half-pixel offset.
 * @see Sony, libgraph reference, sceGsSetHalfOffset2.
 */
void sceGsSetHalfOffset2(void* draw, s16 center_x, s16 center_y, s16 half_offset);

/** @brief Send an image to VRAM. @param image Transfer packet. @param source 16-byte aligned pixels. @return Zero. */
s32 sceGsExecLoadImage(GsLoadImage* image, void* source);

#ifdef __cplusplus
}
#endif

#endif
