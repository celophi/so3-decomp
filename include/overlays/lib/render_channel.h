#ifndef SO3_OVERLAYS_LIB_RENDER_CHANNEL_H
#define SO3_OVERLAYS_LIB_RENDER_CHANNEL_H

#include "overlays/lib/text_003E68C0.h"

#ifdef __cplusplus
class LibTransform;

/** Intrusive rendering channel with packet and indexed-entry hooks. */
class LibRenderChannel : public LibClass171E90
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

    /** @brief Destroy the channel and its intrusive-link base. */
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

    u32 unk0c;

    u32 unk10;

    u32 unk14;

    u32 unk18;

    u32 unk1c;

    u32 unk20;

    u32 unk24;

    /** Packed GS TEX0 value used as the source of channel transfers. */
    u64 source_tex0;

    /** Packed GS TEX0 value used as the destination of channel transfers. */
    u64 destination_tex0;

    u32 unk38;

    u32 unk3c;

    u8 unk40;

    u8 unk41;
};

#endif

#endif
