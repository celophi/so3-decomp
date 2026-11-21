#ifndef SO3_OVERLAYS_LIB_RENDER_CHANNEL_H
#define SO3_OVERLAYS_LIB_RENDER_CHANNEL_H

#include "overlays/lib/text_003E68C0.h"

#ifdef __cplusplus
class LibTransform;

/** Intrusive rendering channel with packet and indexed-entry hooks. */
class LibRenderChannel : public LibListSentinel
{
public:
    /** @brief Clear the links and initial channel state. */
    LibRenderChannel()
    {
        unk18 = 0;
        unk14 = 0;
        unk10 = 0;
        unk0c = 0;
        unk20 = 0;
        unk1c = 0;
        unk41 = 0;
    }

    virtual ~LibRenderChannel()
    {
    }

    /** @brief Default channel update that performs no work. */
    virtual void update();

    /**
     * @brief Prepare the channel's packets for the current owner state.
     * @param owner Rendering object that owns the channel.
     * @param program_address VU program entry point stored in the transfer commands.
     */
    virtual void prepare_packets(LibTransform* owner, u32 program_address);

    /**
     * @brief Append the channel's packets to a packet chain.
     * @param packet Current packet cursor.
     * @return Packet cursor after the channel's packets; unchanged in the base.
     */
    virtual void* append_packets(void* packet);

    /**
     * @brief Report the number of indexed entries supplied by the channel.
     * @return Entry count, or zero in the base channel.
     */
    virtual s32 get_entry_count();

    /**
     * @brief Read an indexed entry from the channel.
     * @param index Entry index supplied by the caller.
     * @return Entry pointer, or null in the base channel.
     */
    virtual void* get_entry(s32 index);

    /**
     * @brief Set the four values at unk0c.
     * @param x Value for unk0c.
     * @param y Value for unk10.
     * @param width Value for unk14.
     * @param height Value for unk18.
     */
    void set_rect(u32 x, u32 y, u32 width, u32 height)
    {
        unk0c = x;
        unk10 = y;
        unk14 = width;
        unk18 = height;
    }

    /**
     * @brief Set the two values at unk1c.
     * @param x Value for unk1c.
     * @param y Value for unk20.
     */
    void set_point(u32 x, u32 y)
    {
        unk1c = x;
        unk20 = y;
    }

    u32 unk0c;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 unk20;
    u32 unk24;
    u64 source_tex0;
    u64 destination_tex0;
    u32 unk38;
    u32 unk3c;
    u8 unk40;
    u8 unk41;
};

#endif

#endif
