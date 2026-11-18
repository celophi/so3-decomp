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

    /** @brief Delete the packet and destroy the region. */
    virtual ~LibClipRegion();

    /**
     * @brief Send the region's packet on DMA channel 1 (VIF1).
     * @param value Notification value; unused.
     */
    virtual void on_packet_notify(u32 value);

    /**
     * @brief Finish the region's packet.
     * @param value Notification value; unused.
     */
    virtual void on_packet_complete(u32 value);

    LibCameraContext* display;
    LibPacketBuffer* packet;
    u32 packet_quadwords;
    u32 packet_address;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
    u8 unkb4[0xC];
};
#endif

#endif
