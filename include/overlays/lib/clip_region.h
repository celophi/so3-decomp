#ifndef SO3_OVERLAYS_LIB_CLIP_REGION_H
#define SO3_OVERLAYS_LIB_CLIP_REGION_H

#include "overlays/lib/text_004CD3A0.h"

#ifdef __cplusplus
/** Partial 0xC0-byte transform that clips drawing to a screen rectangle, with vtable D_171DD0 in main data. */
class LibClipRegion : public LibTransformOwner, public DmaSubmission
{
public:
    /** @brief Initialize the region. */
    LibClipRegion();

    /** @brief Delete the packet and destroy the region. */
    virtual ~LibClipRegion();

    /**
     * @brief Send the region's packet on DMA channel 1 (VIF1).
     * @param channel DMA channel; unused.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the region's packet.
     * @param channel DMA channel; unused.
     */
    virtual void complete_dma(u32 channel);

    /** @brief Queue this object's DMA submission on the VIF1 queue. */
    virtual void render();

    /** @brief Use the region's own draw bucket. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Return a bounding sphere that covers everything.
     * @return Sphere at the origin with a huge radius.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Rebuild the packet: set the scissor to the display's, or to the region's rectangle when it has no
     *        display, then record the packet's size and address.
     * @param matrix View matrix; unused.
     * @param context Packet building context; unused.
     */
    virtual void build_packet(const void* matrix, void* context);

    LibCameraContext* display;
    LibPacketBuffer* packet;
    u32 packet_quadwords;
    u32 packet_address;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
    u8 default_bucket;
    u8 unkb5[0xB];
};
#endif

#endif
