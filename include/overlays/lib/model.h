#ifndef SO3_OVERLAYS_LIB_MODEL_H
#define SO3_OVERLAYS_LIB_MODEL_H

#include "types.h"
#include "gs.h"
#include "overlays/lib/blend_transform.h"
#include "overlays/lib/counted_list.h"
#include "overlays/lib/render_buffer.h"
#include "main/resident_0010A0E0.h"

/** Partial header at the start of a mesh resource's payload. */
struct LibMeshHeader
{
    u8 unk00[4];
    u32 unk04;
    u32 unk08;

    /** Bounding sphere centre. */
    float sphere_center[3];

    /** Bounding sphere radius. */
    float sphere_radius;

    /** Corners of the mesh's bounding box. */
    float box_min[3];
    float box_max[3];

    /** Parts the packets hold. */
    s32 part_count;

    u32 unk38;
    u8 unk3c;
    u8 unk3d[3];
    s32 unk40;
    u8 unk44[0xC];

    /** Bits the model sets in the resident flag word while it's alive. */
    u32 resident_mask;

    u16 unk54;
};

/** Packet sets a model can build for a payload override. */
#define LIB_MODEL_PACKET_SET_COUNT 2

/** Partial transform with color factors and GS state, with vtable D_174310 in main data. */
class LibColorModel : public LibBlendTransform
{
public:
    /** @brief Initialize the color state. */
    LibColorModel();

    /** @brief Destroy the model. */
    virtual ~LibColorModel();

    /** @brief Detach and queue the model. */
    virtual void destroy();

    /** @brief Advance the model. */
    virtual void update();

    /**
     * @brief Fade the model near the camera. Below one it blends with the value as alpha, otherwise opaque.
     * @param value Distance in front of the camera over the fade range, clamped to one.
     * @param mode Two from Lib's caller.
     * @return Whether the value is negative.
     */
    virtual s32 set_fade_alpha(float value, float mode);

    /** @brief Unlink this copy from its original's copies and queue it for release. */
    virtual void release_clone();

    /**
     * @brief Link a copy to this model as the last of its clones.
     * @param copy Copy to link.
     */
    void add_clone(LibColorModel* copy);

    /**
     * @brief Store the blend mode and flag the color state for an update.
     * @param mode Blend mode.
     */
    virtual void set_blend_mode(u8 mode)
    {
        blend_mode = mode;
        color_dirty = 1;
    }

    /** @brief Store the component product of the base color factor and the modulation. */
    virtual void update_combined_color_factor();

    /**
     * @brief Store the color modulation, then recompute the combined color factor.
     * @param key Caller's key; unused here.
     * @param modulation Color modulation to store.
     */
    virtual void set_color_modulation(s32 key, const LibVector4* modulation)
    {
        copy_vector(&color_modulation, modulation);
        update_combined_color_factor();
    }

    /**
     * @brief Read the color modulation.
     * @return Color modulation.
     */
    virtual const LibVector4* get_color_modulation() const
    {
        return &color_modulation;
    }

    /**
     * @brief Turn fogging on or off.
     * @param enabled Nonzero for fog.
     */
    virtual void set_fog_enabled(u8 enabled);

    /**
     * @brief Copy another model's color state, blend mode and offset transform.
     * @param source Model to copy.
     */
    virtual void copy_color_state(const LibColorModel* source);

    u8 unk220[0x340];
    LibVector4 base_color_factor;
    LibVector4 color_modulation;
    LibVector4 combined_color_factor;

    /** Light groups in the low byte and the bits of the spotlights that reach the model above them. */
    u32 light_mask;

    /** Model this one was cloned from, or null. */
    LibColorModel* original;

    /** Next clone of the same original. */
    LibColorModel* next_clone;

    u8 unk59c;
    u8 unk59d_0 : 1;
    u8 unk59d_1 : 1;

    /** Set while the model draws with fog. */
    u8 fog_enabled : 1;

    /** Set when the color state must be rebuilt. */
    u8 color_dirty : 1;

    u8 unk59d_4_7 : 4;
    u8 unk59e[2];
};

/** Partial 0x90-byte list member of every LibModelBase, with vtable D_177A20 in main data. */
class LibClass177A20 : public LibListReceiver
{
public:
    /** @brief Initialize the list. */
    LibClass177A20();

    /** @brief Destroy the list. */
    virtual ~LibClass177A20();

    /**
     * @brief Test whether any entry in the list is listed.
     * @return Nonzero when one is.
     */
    u8 has_listed_entry();

    /**
     * @brief Hand the list's payload to a model, in one packet set or both.
     * @param model Model to give the payload to.
     * @return Nonzero on success.
     */
    s32 apply_payload(class LibModel* model);

    /**
     * @brief Make the model draw one packet set's payload.
     * @param set Packet set to select; only set zero when the list has a single payload.
     * @return The previously selected set, or -1 when the set isn't available.
     */
    s32 select_payload_set(u8 set);

    /** @brief Once the list is empty, detach it, clear the model's payload and free the payload buffers. */
    void release_model();

    /**
     * @brief Allocate a packet set's payload buffer for the model's payload, then build the payload in it.
     * @param set Packet set; set one is skipped when the list has a single payload.
     */
    void allocate_payload(s32 set);

    /**
     * @brief Test whether the list has the payloads it needs.
     * @return Whether it has.
     */
    bool has_payload() const
    {
        if (unk8d_0)
        {
            return payload_buffers[0] != 0;
        }

        return payload_buffers[0] != 0 && payload_buffers[1] != 0;
    }

    u8 unk14[0x40];

    /** Model the payloads are drawn by. */
    class LibModel* model;

    u8 unk58[4];
    void* unk5c;
    void* unk60;
    u8 unk64[4];
    void* unk68;
    void* unk6c;
    void* unk70;

    /** Buffer each packet set's payload is built in. */
    void* payload_buffers[LIB_MODEL_PACKET_SET_COUNT];

    /** Payload handed to the model for each packet set. */
    void* payloads[LIB_MODEL_PACKET_SET_COUNT];

    u8 unk84[6];

    /** Packet set last selected. */
    u8 payload_set;

    u8 unk8b[2];
    u8 unk8d_0 : 1;
    u8 unk8d_1_7 : 7;
    u8 unk8e[2];
};

/** Partial bit array whose words are owned or borrowed, with vtable D_177A10 in main data; its data comes before the vptr. */
class LibResourceBitset
{
public:
    u32 bit_count;
    u32 word_count;
    u32* words;

    /** Nonzero when words is borrowed and must not be freed. */
    u8 words_are_borrowed;

    u8 unk0d[3];

    /** @brief Start with no words. */
    LibResourceBitset() : words(0), words_are_borrowed(0)
    {
    }

    /** @brief Release the word buffer when it is owned by this object. */
    virtual ~LibResourceBitset()
    {
        if (!words_are_borrowed)
        {
            delete[] words;
        }
    }
};

/** Partial entry of a LibClass177A20 list, with vtable D_1779F0 in main data. */
class LibClass1779F0 : public LibListSentinel
{
public:
    /** @brief Start unattached, with no data. */
    LibClass1779F0();

    /** @brief Leave the list, then free the data unless it's borrowed. */
    virtual ~LibClass1779F0();

    /**
     * @brief Use data the entry doesn't own.
     * @param value Borrowed data.
     */
    virtual void set_borrowed_data(void* value);

    virtual void func_slot10() = 0;

    /**
     * @brief Return the entry's type code.
     * @return Zero for the base entry.
     */
    virtual s32 func_slot14();

    virtual s32 func_slot18();

    /**
     * @brief Add the entry to a model's child list, binding the list to the model first.
     * @param model Model whose children list to join.
     * @param links Display list passed on to the list's binding.
     */
    void attach(class LibModel* model, LibUpdateList* links);

    /** Nonzero when data is borrowed and must not be freed. */
    u8 data_is_borrowed;

    u8 listed;
    u8 unk0e;
    u8 unk0f;

    /** List the entry is in, or null. */
    LibClass177A20* list;

    void* data;
    u8 unk18;
    u8 unk19;
    u8 unk1a[2];
    LibResourceBitset bits;
};

/** Partial model base that draws a mesh resource, with vtable D_178D10 in main data. */
class LibModelBase : public LibColorModel
{
public:
    /** @brief Start with no resource. */
    LibModelBase() : owns_resource(0), unk5a1(1), resource(0), unk638(0)
    {
    }

    /** @brief Release the resource when owned, then destroy the model. */
    virtual ~LibModelBase();

    /** @brief Unregister the resource when owned, then destroy the model through its base. */
    virtual void destroy()
    {
        if (owns_resource != 0 && resource != 0)
        {
            resource->unregister();
        }

        LibColorModel::destroy();
    }

    /** @brief Advance the model. */
    virtual void update();

    /**
     * @brief Turn fogging on or off, in the resource's primitives too.
     * @param enabled Nonzero for fog.
     */
    virtual void set_fog_enabled(u8 enabled);

    /**
     * @brief Draw the resource with a payload override.
     * @param payload Payload to draw instead of the resource's own.
     * @param set Packet set the payload goes in.
     */
    virtual void load_payload(void* payload, u8 set);

    /**
     * @brief Switch to a payload override.
     * @param payload Payload to draw instead of the resource's own.
     * @param set Packet set the payload goes in.
     */
    virtual void select_payload(void* payload, u8 set);

    /** @brief Go back to the resource's own payload. */
    virtual void clear_payload();

    /**
     * @brief Draw a resource, and take the resident flag bits its mesh asks for.
     * @param mesh Resource to draw.
     * @return One.
     */
    s32 set_resource(LibResourceBuffer* mesh);

    /**
     * @brief Draw a draw buffer: own it as the resource and hand it the model's render channels.
     * @param buffer Draw buffer to attach.
     * @return One.
     */
    s32 attach_draw_buffer(LibDrawBuffer* buffer);

    /**
     * @brief Test whether the model's draw packet has been built; the base has none.
     * @return Nonzero when it has.
     */
    virtual s32 has_packet();

    /**
     * @brief Return the list of the model's render channels; the base has none.
     * @return List, or null.
     */
    virtual LibListReceiver* get_render_channels();

    /** Nonzero when destroy unregisters the resource. */
    u8 owns_resource;

    u8 unk5a1;
    u8 unk5a2[2];

    /** Child objects, such as the face's morph targets. */
    LibClass177A20 children;

    /** Resource the model draws: a mesh, or a draw buffer. */
    LibResourceBuffer* resource;

    u32 unk638;
    u8 unk63c[4];
};

/** Partial 0x80-byte texture upload block in a model's upload table. */
struct LibTextureUpload
{
    u32 unk00[3];

    /** VIF UNPACK code for the block. */
    u32 unpack;

    u64 gif_tag;
    u64 gif_registers;
    GsRegisterValue bitbltbuf;
    GsRegisterValue trxpos;
    GsRegisterValue trxreg;
    GsRegisterValue trxdir;

    /** VIF MSCALF code that starts the upload microprogram. */
    u32 mscal;

    u8 unk64[0x1C];
};

/** Values a model writes into one of its part records. */
struct LibModelPartSetting
{
    u32 first_value;
    u32 second_value;

    /** Bit 0 applies first_value, bit 1 second_value. */
    u8 flags;

    u8 unk09[3];
};

/** Chain of DMA tags that calls a model's packets. */
struct LibModelPacketChain
{
    u64 tags[3][2];
};

/** Partial 0x820-byte Lib model with vtable D_177820 in main data. */
class LibModel : public LibModelBase, public DmaSubmission
{
public:
    /** @brief Construct an empty model. */
    LibModel();

    /** @brief Release the packets and channels, then destroy the model. */
    virtual ~LibModel();

    /** @brief Advance the model. */
    virtual void update();

    /** @brief Queue the model's packet chain. */
    virtual void render();

    /** @brief Pick the draw bucket from the draw flags, blend mode and mesh. */
    virtual void set_default_draw_bucket();

    /**
     * @brief Give the centre for Lib's oriented-box visibility test, from the mesh, when the model is unscaled.
     * @param output Receives the centre in local space.
     * @return Nonzero when a centre was written.
     */
    virtual s32 get_box_cull_center(void* output);

    /**
     * @brief Return the bounding sphere from the mesh, with the radius scaled by the model.
     * @return Bounding sphere (centre in xyz, radius in w).
     */
    virtual const LibVector4* get_bounding_sphere();

    /**
     * @brief Build the draw packet for a matrix.
     * @param matrix Matrix supplied by the caller.
     * @param context Opaque caller context.
     */
    virtual void build_packet(const void* matrix, void* context);

    /**
     * @brief Make a copy of the model built from this one and linked to it.
     * @return The copy, or null when it couldn't be built.
     */
    virtual LibTransformOwner* clone();

    /**
     * @brief Turn fogging on or off, in the model's part packets too.
     * @param enabled Nonzero for fog.
     */
    virtual void set_fog_enabled(u8 enabled);

    /**
     * @brief Build the packet set for a payload override, then draw it.
     * @param payload Payload to draw instead of the resource's own.
     * @param set Packet set the payload goes in.
     */
    virtual void load_payload(void* payload, u8 set);

    /**
     * @brief Switch to a payload override, or back to the resource's own with a set of two or more.
     * @param payload Payload to draw instead of the resource's own.
     * @param set Packet set to draw.
     */
    virtual void select_payload(void* payload, u8 set);

    /** @brief Go back to the resource's own payload and release the override packets. */
    virtual void clear_payload();

    /**
     * @brief Test whether the model's draw packet has been built.
     * @return Nonzero when it has.
     */
    virtual s32 has_packet()
    {
        return packet != 0;
    }

    /**
     * @brief Return the list of the model's render channels.
     * @return List.
     */
    virtual LibListReceiver* get_render_channels()
    {
        return &render_channels;
    }

    /**
     * @brief Size of the extra packet block chained in before the draw packet; this model has none.
     * @return Size in quadwords.
     */
    virtual s32 get_before_packet_size()
    {
        return 0;
    }

    /**
     * @brief Size of the extra packet block chained in after the draw packet; this model has none.
     * @return Size in quadwords.
     */
    virtual s32 get_after_packet_size()
    {
        return 0;
    }

    /**
     * @brief Fill the block before the draw packet.
     * @param block Block address (uncached).
     * @return End of what was written.
     */
    virtual s32 build_before_packet(s32 block)
    {
        return block;
    }

    /**
     * @brief Fill the block after the draw packet.
     * @param block Block address (uncached).
     * @return End of what was written.
     */
    virtual s32 build_after_packet(s32 block)
    {
        return block;
    }

    /**
     * @brief Put one of the model's textures in VRAM when the model supplies its own textures; this model doesn't.
     * @return VRAM address, or zero to skip the texture.
     */
    virtual s32 place_texture()
    {
        return 0;
    }

    /**
     * @brief Swap a texture record while drawing when the model supplies its own textures; this model doesn't.
     * @return Replacement record, or zero to keep the original.
     */
    virtual s32 replace_texture()
    {
        return 0;
    }

    /**
     * @brief Start the VIF1 chain DMA of the model's packet.
     * @param channel DMA channel number.
     */
    virtual void submit_dma(u32 channel);

    /**
     * @brief Finish the model's transfer.
     * @param channel DMA channel number.
     */
    virtual void complete_dma(u32 channel);

    /**
     * @brief Return which of the model's packet sets is in use.
     * @return Packet set index.
     */
    virtual u8 get_packet_set()
    {
        return packet_set;
    }

    /**
     * @brief Build this model from another model.
     * @param links Display list the model draws through, or null.
     * @param source Model to copy.
     * @return Nonzero on success.
     */
    virtual s32 build_from(LibUpdateList* links, LibModel* source);

    /** @brief Allocate and fill the model's packets from its mesh. */
    virtual void build_packets();

    /** @brief Update each render channel when the mesh asks for it. */
    void update_render_channels();

    /** @brief Write the pending part settings into the part records' GIF tags, then free them. */
    void apply_part_settings();

    /**
     * @brief Test whether any part of the mesh blends with an ALPHA setting weighted by destination alpha.
     * @return Nonzero when one does.
     */
    s32 func_004A2870();

    /** @brief Virtual slot 0xF0. */
    virtual void func_slotF0();

    /**
     * @brief Extra quadwords to reserve in the model's draw packet; this model needs none.
     * @return Quadword count.
     */
    virtual s32 get_extra_packet_size()
    {
        return 0;
    }

    u8 unk644[0xC];
    u64 chain[5][2];
    LibModelPacketChain packet_chains[LIB_MODEL_PACKET_SET_COUNT];
    void* base_packet;

    /** The model's draw packet. */
    void* packet;

    /** Packets built for a payload override, one per packet set. */
    void* override_packets[LIB_MODEL_PACKET_SET_COUNT];

    u32 unk710;
    void* before_packet;
    void* after_packet;
    LibTextureUpload* texture_uploads;
    void* unk720;
    /** Part table: the part records after a 0x40-byte header. */
    void* parts;
    u8 unk728[0x20];
    u8 unk748[0x20];
    void* unk768;
    void* unk76c;

    /** Settings apply_part_settings writes into the part records, unk774 of them; freed afterwards. */
    LibModelPartSetting* unk770;

    s32 unk774;
    s32 unk778;
    u32 unk77c;
    u32 unk780;
    u8 unk784[4];
    u16 before_packet_size;
    u16 after_packet_size;
    u8* payload;
    u8 unk790;
    u8 unk791;
    u8 draw_bucket_choice;
    u8 unk793;

    /** Which packet set Lib builds and draws. */
    u8 packet_set;

    u8 unk795;
    u8 unk796;
    u8 unk797_0 : 1;
    u8 unk797_1 : 1;
    u8 unk797_2 : 1;

    /** Set while a payload override is selected. */
    u8 uses_payload_override : 1;

    u8 unk797_4 : 1;
    u8 unk797_5 : 1;
    u8 unk797_6 : 1;
    u8 unk797_7 : 1;
    u8 unk798_0 : 1;

    /** Set when get_box_cull_center may give a centre. */
    u8 box_cull_enabled : 1;

    u8 unk798_2 : 1;
    u8 unk798_3_7 : 5;
    u8 unk799[3];

    /** The model's render channels. */
    LibListReceiver render_channels;

    LibVector4 bounding_sphere;
    float unk7c0;
    float unk7c4;
    u32 unk7c8[6];
    u32 unk7e0;
    u8 unk7e4[0x34];

    /** Model this one was built from. */
    LibModel* source;

    u8 unk81c[4];
};

#endif
