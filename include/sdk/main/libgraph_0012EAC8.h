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

#ifdef __cplusplus
}
#endif

#endif
