#ifndef SO3_OVERLAYS_LIB_CLIP_REGION_H
#define SO3_OVERLAYS_LIB_CLIP_REGION_H

#include "overlays/lib/text_004CD3A0.h"

#ifdef __cplusplus
/** Partial 0xC0-byte transform that clips drawing to a screen rectangle, with vtable D_171DD0 in main data. */
class LibClipRegion : public LibTransformOwner, public LibDmaCallbacks
{
public:
    /** @brief Initialize the region. */
    LibClipRegion();

    /** @brief Destroy the region. */
    virtual ~LibClipRegion();

    LibCameraContext* display;
    void* unk98;
    u8 unk9c[8];
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
    u8 unkb4[0xC];
};
#endif

#endif
