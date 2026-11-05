#ifndef SO3_OVERLAYS_LIB_IMAGE_CAPTURE_H
#define SO3_OVERLAYS_LIB_IMAGE_CAPTURE_H

#include "types.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "overlays/lib/text_004CD3A0.h"

/**
 * Partial 0x210-byte object that copies a rectangle of VRAM back to main memory, with vtable D_1735A0 in main data.
 * It keeps two store packets and alternates between them.
 */
class LibImageCapture : public LibTransformOwner, public LibDmaCallbacks
{
public:
    /** @brief Construct the capture. */
    LibImageCapture();

    u8 unk94;

    /** Which of the two store packets is the newest. */
    u8 current;

    u8 unk96;

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
}

#endif
