#ifndef SO3_OVERLAYS_LIB_SCRATCHPAD_TEXTURE_CACHE_H
#define SO3_OVERLAYS_LIB_SCRATCHPAD_TEXTURE_CACHE_H

#include "ee.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "sdk/main/libkernl_00121940.h"

#ifdef __cplusplus
/**
 * @brief Copy the texture cache back from the scratchpad to its main-memory home when the renderer moved it there,
 *        point g_texture_cache at it again and wait for the transfer before restarting the channel 8 queue.
 * @param renderer Renderer that owns the cache copy.
 */
static inline void lib_restore_texture_cache(LibRenderer* renderer)
{
    if (renderer->unk40cf)
    {
        func_004D9030(renderer->unk40d4, g_texture_cache);
        renderer->unk40cf = 0;
        g_texture_cache = renderer->unk40d4;
        ee_wait_dma_condition();
        EnableDmac(D_001B6604->channel);
    }
}
#endif

#endif
