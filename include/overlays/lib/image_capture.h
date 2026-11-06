#ifndef SO3_OVERLAYS_LIB_IMAGE_CAPTURE_H
#define SO3_OVERLAYS_LIB_IMAGE_CAPTURE_H

#include "types.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "overlays/lib/text_004CD3A0.h"
#include "main/resident_0010A0E0.h"

/**
 * Partial 0x210-byte object that copies a rectangle of VRAM back to main memory, with vtable D_1735A0 in main data.
 * It keeps two store packets and alternates between them. Lib's store thread does the copy once a packet has run.
 */
class LibImageCapture : public LibTransformOwner, public DmaSubmission
{
public:
    /** @brief Construct the capture. */
    LibImageCapture();

    /** @brief Destroy the capture. */
    virtual ~LibImageCapture();

    /** @brief Queue the capture's DMA, or hand it to the packet queue when unk65 is set. */
    virtual void render();

    /** @brief Use the capture's own draw bucket. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Pick the waiting packet to store, if there is one.
     * @param matrix Matrix supplied by the caller; unused.
     * @param context Opaque caller context; unused.
     */
    virtual void build_packet(const void* matrix, void* context);

    /** @brief Mark the packet being stored as done and finish the capture. */
    virtual void on_store_complete();

    /**
     * @brief Hand the packet being stored to the store thread and wake it.
     * @param channel DMA channel number.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Let the store thread know the store packet's transfer is over.
     * @param channel DMA channel number.
     */
    virtual void complete_dma(u32 channel);

    /** Draw bucket the capture uses (9). */
    u8 default_draw_bucket;

    /** Which of the two store packets is the newest. */
    u8 current;

    /** Which store packet is being stored. */
    u8 storing;

    /** Per packet: set once its copy has arrived. */
    u8 stored[2];

    /** A copy is waiting to be sent. */
    u8 pending;

    u8 unk9a[0x46];
    GsStoreImage packets[2];
    u8 unk1c0[0x40];

    /** Per packet: where its copy goes. */
    void* destinations[2];

    u8 unk208[8];
};

/** Lib's VRAM store thread (vtable D_173580 in main data); one is shared by every capture. Partial. */
struct LibImageStoreThread
{
    u8 unk00[0x10];

    /** Store packet to run, as an uncached address. */
    GsStoreImage* packet;

    /** Where the pixels go. */
    void* destination;

    LibImageCapture* capture;

    /** Signalled when the store packet's transfer is over. */
    s32 semaphore;

    u8 unk20[4];

    /** Set when the thread couldn't be woken. */
    u8 wake_failed;
};

extern LibImageStoreThread D_005081D0;

extern "C"
{
    /**
     * @brief Queue a copy of a VRAM rectangle into memory, in the next of the capture's two store packets.
     * @param capture Capture object.
     * @param destination Memory the pixels are copied to.
     * @param base_pointer Source buffer address in 64-word blocks.
     * @param buffer_width Source buffer width in 64-pixel units.
     * @param pixel_format Source pixel format.
     * @param x Left edge of the rectangle.
     * @param y Top edge of the rectangle.
     * @param width Rectangle width.
     * @param height Rectangle height.
     */
    void lib_image_capture_store(LibImageCapture* capture, void* destination, s16 base_pointer, s16 buffer_width,
                                 s16 pixel_format, s16 x, s16 y, s16 width, s16 height);

    /**
     * @brief Packet-queue handler for a capture that render handed over: let queued packets start, then queue the
     *        capture's DMA.
     * @param capture Capture object.
     */
    void func_004332F0(LibImageCapture* capture);
}

#endif
