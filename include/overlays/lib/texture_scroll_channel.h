#ifndef SO3_OVERLAYS_LIB_TEXTURE_SCROLL_CHANNEL_H
#define SO3_OVERLAYS_LIB_TEXTURE_SCROLL_CHANNEL_H

#include "overlays/lib/render_channel.h"

/** VIF and GS block-transfer template. */
struct LibTextureTransferPacket
{
    u32 vif_unpack[4];

    u64 gif_tag;

    u64 gif_registers;

    u64 buffer;

    u64 buffer_register;

    u64 position;

    u64 position_register;

    u64 region_size;

    u64 size_register;

    u64 direction;

    u64 direction_register;

    u64 texture_flush;

    u64 texture_flush_register;

    u32 vif_call;

    u32 unk74;

    u32 unk78;

    u32 vif_flush;

    u8 unk80[0x10];
} __attribute__((aligned(16)));

/** Channel that scrolls a texture region through up to four wrapped copies. */
class LibTextureScrollChannel : public LibRenderChannel
{
public:
    enum
    {
        TRANSFER_COUNT = 4
    };

    /** @brief Initialize four inactive texture-transfer templates. */
    LibTextureScrollChannel();

    /** @brief Destroy the channel and its intrusive-link base. */
    virtual ~LibTextureScrollChannel();

    /**
     * @brief Prepare texture-copy rectangles and buffer formats for the owner.
     * @param owner Rendering object that owns the channel.
     * @param program_address VU program entry point stored in the transfer commands.
     */
    virtual void prepare_packets(LibTransform* owner, u32 program_address);

    /**
     * @brief Append DMA references for the active texture transfers.
     * @param packet Packet cursor with room for up to four DMA tags.
     * @return Packet cursor after the appended tags.
     */
    virtual void* append_packets(void* packet);

    u8 unk48[0x38];

    LibTextureTransferPacket transfers[TRANSFER_COUNT];

    u8 unk2c0[0x30];

    s32 x_offset;

    s32 y_offset;

    float scale;

    u8 transfer_enabled[TRANSFER_COUNT];

    u8 mode;

    u8 unk301[0xF];
};

#endif
