#ifndef SO3_OVERLAYS_LIB_IMAGE_MODEL_H
#define SO3_OVERLAYS_LIB_IMAGE_MODEL_H

#include "types.h"
#include "gs.h"
#include "overlays/lib/model.h"
#include "overlays/lib/emission.h"
#include "overlays/lib/particle_grid.h"

#ifdef __cplusplus
/** GS state an image entry carries: texture registers and the blend register. */
struct LibImageSetupPacket
{
    float unk00[3];
    u32 unpack;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u64 texture_tag;

    union
    {
        u64 texture_registers;

        struct
        {
            u64 register0 : 4;
            u64 unused : 60;
        } texture_register_fields;
    };

    u64 texture_data;
    u64 texture_address;
    u64 texture_2_data;
    u64 texture_2_address;
    u64 alpha_tag;

    union
    {
        u64 alpha_registers;

        struct
        {
            u64 register0 : 4;
            u64 unused : 60;
        } alpha_register_fields;
    };

    u64 alpha_data;
    u64 alpha_address;
    u64 unk70;
    u64 unk78;
    u64 unk80;
    u64 unk88;
    u64 unk90;
    u64 unk98;
};

/** Partial packet an image model draws with. */
struct LibImagePacket
{
    u8 unk00[0xC];
    u32 unpack;
    u64 gif_tag;
    u64 gif_registers;
    u32 alpha;
    u32 unk24;
    u32 alpha_address;
    u32 unk2c;
    u8 unk30[0x24];
    float unk54;
    u8 unk58[8];

    union
    {
        u64 primitive_tag;
        u32 primitive_tag_words[2];
    };

    u64 primitive_registers;
    u8 unk70[0x80];
};

/** Partial image entry of a FISP chunk. */
struct LibImageEntry
{
    u8 unk00;
    u8 flag_count;
    u8 unk02;
    u8 unk03[5];
    u16 width;
    u16 height;
    u8 flags[4];
    LibImageSetupPacket setup;
    u8 unkb0[0x10];
    u8 pixels[1];
};

#define LIB_IMAGE_SET_CHUNK_MAGIC 0x50534946

/** Payload of a FISP chunk: a count, then the offset of each image entry from the payload. */
struct LibImageSet
{
    u32 count;
    u32 offsets[1];
};

/** Partial 0xAF0-byte image model, with vtable D_1751A0 in main data. */
class LibObject1751A0 : public LibColorModel, public DmaSubmission, public LibRenderResource, public LibClass173A28
{
public:
    /** @brief Start without an image, with an open bounding box and two texture upload records. */
    LibObject1751A0();

    /** @brief Let go of the shared object, unregister the image and free the buffers. */
    virtual ~LibObject1751A0();

    /**
     * @brief Report the model's list kind.
     * @return Seven.
     */
    virtual s32 get_default_list_kind();

    /** @brief Release the textures, then detach and queue the model. */
    virtual void destroy();

    /** @brief Advance the model. */
    virtual void update();

    /** @brief Queue the model's DMA submission. */
    virtual void render();

    /** @brief Pick the draw bucket from the blend and image state. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Give the centre of the image's bounding box.
     * @param output Receives the half extent at 0x40 and the centre at 0x0.
     * @return Nonzero when the shared object is ready and a centre was written.
     */
    virtual s32 get_box_cull_center(void* output);

    /**
     * @brief Transform the bounding sphere's centre into world space.
     * @return Bounding sphere in world space.
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Build the model's packet.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Make a copy of this model that stays linked to it.
     * @return The copy, or null.
     */
    virtual LibTransformOwner* clone();

    /**
     * @brief Turn fogging on or off in the model's packet.
     * @param enabled Nonzero for fog.
     */
    virtual void set_fog_enabled(u8 enabled);

    /**
     * @brief Start the model's DMA transfer.
     * @param channel DMA channel number.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the model's packet.
     * @param channel DMA channel number.
     */
    virtual void complete_dma(u32 channel);

    /**
     * @brief Copy another model's image state.
     * @param source Model to copy.
     */
    virtual void copy_image_state(LibObject1751A0* source);

    /**
     * @brief Return the image record while an image is set.
     * @return The record, or null.
     */
    virtual void* get_data();

    /**
     * @brief Resolve an offset; this model has none.
     * @param offset Offset to resolve.
     * @return Null.
     */
    virtual void* resolve_offset(const u32* offset);

    /**
     * @brief Point the model at one image of a resource's FISP chunk.
     * @param resource First chunk of the resource.
     * @param index Image index in the FISP chunk; past the count, nothing changes.
     */
    void set_image(LibResourceChunkHeader* resource, u32 index);

    /** @brief Clear the image and reset the texture state. */
    void clear_image();

    /**
     * @brief Point the setup packet at the renderer's first pass target: find its image once, look it up in the
     *        texture cache, and copy its TEX0 (and its CLUT's, for the indexed formats) into the packet.
     */
    void func_004683E0();

    /**
     * @brief Set the primitive the model draws, its blend mode and the packet values that go with them.
     * @param primitive Primitive kind, 0 to 6.
     * @param value Value stored in the packet and at unkade.
     * @param blend Blend mode; nonzero also turns alpha blending on in the primitive.
     * @param unk54 Value stored in the packet at 0x54.
     */
    void set_primitive(s32 primitive, u8 value, s32 blend, float unk54);

    /** @brief Size and allocate the packet buffers for the grid, and point the DMA chains at them. */
    void allocate_packets();

    /**
     * @brief Take the next free grid cell, searching round from the one handed out last, and place it.
     * @param position Position copied into the cell.
     * @param cell Receives the cell.
     * @param value Receives the grid's value for the cell when not null.
     * @return The cell index, or -1 when every cell is used.
     */
    s32 claim_cell(const LibVector4* position, LibClass174228** cell, s32* value);

    /**
     * @brief Take the next phase of a shared counter that cycles through a period.
     * @param period Period length; zero leaves the counter alone.
     */
    void set_phase_period(u8 period);

    /** @brief Reset texture upload records one and two to upload nothing yet. */
    void reset_texture_uploads()
    {
        for (s32 i = 1; i <= 2; i++)
        {
            *reinterpret_cast<unsigned __int128*>(&texture_uploads[i]) = 0;
            *reinterpret_cast<unsigned __int128*>(&texture_uploads[i].mscal) = 0;
            texture_uploads[i].unpack = VIF_UNPACK(VIF_UNPACK_V4_32, 5, 0x60);
            texture_uploads[i].mscal = VIF_MSCALF(reinterpret_cast<u32>(D_678) >> 3);
            texture_uploads[i].gif_tag = 4 | GIF_TAG_EOP | GIF_TAG_NREG(1);
            texture_uploads[i].gif_registers = GIF_REGISTER_AD;
            texture_uploads[i].trxpos.data = 0;
            texture_uploads[i].trxpos.address = GS_REGISTER_TRXPOS;
            texture_uploads[i].trxdir.data = 0;
            texture_uploads[i].trxdir.address = GS_REGISTER_TRXDIR;
        }
    }

    /**
     * @brief Hold a shared object and add to its reference count.
     * @param object Shared object to hold.
     */
    void hold_reference(LibGridBase* object)
    {
        holds_reference = 1;
        reference = object;
        object->user_count++;
    }

    /** @brief Let go of the shared object, destroying it when this was its last holder, and clear it. */
    void release_reference()
    {
        LibGridBase* held = reference;

        if (held)
        {
            if (holds_reference)
            {
                if (held->user_count > 0)
                {
                    held->user_count--;
                }
            }
            else if (held->user_count > 0)
            {
                if (--held->user_count == 0)
                {
                    delete held;
                }
            }
        }

        holds_reference = 0;
        reference = 0;
    }

    LibModelPacketChain chains[2];
    u32 chain_address;
    LibImagePacket* packet;
    LibImageEntry* image;
    u8 unk61c[4];
    s32 unk620;
    s16 unk624;
    u8 unk626[0x1A];
    s32 unk640;
    u8 unk644[4];
    void* unk648;
    u8 unk64c[0xA4];
    LibImageSetupPacket setup;
    u8 unk790[0xA0];
    LibTextureUpload texture_uploads[3];
    u8 unk9b0[0x80];
    LibVector4 box_min;
    LibVector4 box_max;
    LibVector4 bounding_sphere;
    LibVector4 world_bounding_sphere;
    u8 unka70[0x10];
    LibGridBase* reference;
    u8* unka84;
    u8* unka88;
    u8* unka8c;
    u8* unka90;
    u8* unka94;
    s32 unka98;
    s32 unka9c;
    float diagonal;
    float unkaa4;
    float unkaa8;
    s32 unkaac;
    u8 unkab0[8];
    s32 next_cell;
    float unkabc;
    float unkac0;
    float unkac4;
    u32 unkac8;
    u32 unkacc;
    s32 user_count;
    LibObject1751A0* source;
    u8 phase;
    u8 phase_period;
    u8 unkada;
    u8 unkadb;
    u8 holds_reference;
    u8 unkadd;
    u8 unkade;
    u8 unkadf;
    u8 unkae0;
    u8 kind;
    u8 unkae2;
    u8 unkae3;
    u8 unkae4;
    u8 registered;
    u8 unkae6;
    u8 copied;
};
#endif

#endif
