#include "overlays/lib/palette_blend_channel.h"
#include "include_asm.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_data.h"
#include "main/func_0011EE00.h"
#include "overlays/lib/model.h"
#include "ee.h"
#include "gs.h"
#include "vu0.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libc_guess_00137290.h"

/** FGE as it sits in the upper word of a GIF tag's first doubleword. */
#define GIF_TAG_HIGH_PRIM_FGE ((u32)(GIF_TAG_PRIM(GS_PRIM_FGE) >> 32))

/** Byte size of each part record in the model's part table. */
#define LIB_MODEL_PART_SIZE 0xF0

/** Partial part record in the model's part table: the upper tag words of its GIF tags, written uncached. */
struct LibModelPart
{
    u8 unk00[0x64];
    u32 first_tag_high;
    u8 unk68[0xC];
    u32 second_tag_high;
    u8 unk78[0xC];

    /** Nonzero when the part has the second pair of GIF tags. */
    u32 unk84;

    u8 unk88[0x3C];
    u32 third_tag_high;
    u8 unkc8[0xC];
    u32 fourth_tag_high;
    u8 unkd8[0x18];
};

/**
 * @brief Return a part record through the uncached accelerated segment.
 * @param parts Part table.
 * @param index Part index.
 * @return The part.
 */
static inline LibModelPart* lib_model_uncached_part(void* parts, s32 index)
{
    return reinterpret_cast<LibModelPart*>(
        reinterpret_cast<u32>(static_cast<u8*>(parts) + index * LIB_MODEL_PART_SIZE) | EE_UNCACHED_ACCELERATED);
}

/** List kind of models that need the late update pass. */
#define LIB_LIST_KIND_LATE_MODEL 9


/** Scales within this of one count as unscaled. */
#define LIB_MODEL_UNSCALED_MIN 0.999f
#define LIB_MODEL_UNSCALED_MAX 1.001f

/** Partial oriented box Lib tests against the view. */
struct LibCullBox
{
    LibVector4 center;
    u8 unk10[0x30];
    LibVector4 half_extents;
};

/** Bytes in front of the DMA data in each of a model's packets. */
#define LIB_MODEL_PACKET_HEADER_SIZE 0x40

/** Fixed quadwords of a model packet, and the quadwords each part adds. */
#define LIB_MODEL_PACKET_FIXED_QWORDS 19
#define LIB_MODEL_PART_QWORDS 5

/** Fixed quadwords of the base packet, and the quadwords each part-table item adds. */
#define LIB_MODEL_BASE_FIXED_QWORDS 32
#define LIB_MODEL_BASE_QWORDS_PER_ITEM 10

/** Quadwords a before or after packet adds to its own size. */
#define LIB_MODEL_EXTRA_BLOCK_QWORDS 9

/** Header quadwords of the part table. */
#define LIB_MODEL_TABLE_HEADER_QWORDS 8

/** Heap model packets come from when set; otherwise they're malloc'd. */
extern "C" void* D_001B659C;

/** VU1 microprogram that uploads a model's textures. */
extern "C" u8 D_678[];

/**
 * @brief Fill the model's part table from its mesh.
 * @param model Model whose parts table to fill.
 */
extern "C" void func_004A7C20(LibModel* model);

/** Partial word-array owner with its native virtual pointer after the data fields. */
class LibResourceBitset
{
public:
    u8 unk00[8];
    u32* words;
    u8 words_are_borrowed;
    u8 unk0d[3];

    /** @brief Release an owned word buffer. */
    virtual ~LibResourceBitset();
};

/**
 * @brief Add three components to a copied vector, preserving the fourth.
 * @param value Vector to copy.
 * @param offset Components to add.
 * @return Offset vector with the original fourth component.
 */
static inline FieldVec4B lib_lod_add_position_offset(const FieldVec4B& value, const FieldVec4A& offset)
{
    FieldVec4B result(value);
    return result.add(offset);
}

/**
 * @brief Forward an aligned vector to the inherited position setter.
 * @param object Controller receiver.
 * @param position New position.
 */
static inline void lib_lod_set_position(LibLodController* object, const FieldVec4B& position)
{
    object->copy_translation(reinterpret_cast<const LibVector4*>(&position));
}

typedef struct FourQuadwordCopyTargetOwnertext_0049B820
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0x30];
    unsigned __int128 values60[4];
} FourQuadwordCopyTargetOwnertext_0049B820;
typedef struct FourQuadwordCopySourceOwnertext_0049B820
{
    u8 pad00[0x150];
    unsigned __int128 values150[4];
} FourQuadwordCopySourceOwnertext_0049B820;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049B820);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049BD70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049C3E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049CA60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049D260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049DA60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049DB40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049E270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049E360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049E440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049EB80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049EC70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049ED80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A02D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A03C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A04F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0550);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A05E0);

void func_004A06B0(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0049B820* receiver = static_cast<FourQuadwordCopyTargetOwnertext_0049B820*>(object);
    const FourQuadwordCopySourceOwnertext_0049B820* values = static_cast<const FourQuadwordCopySourceOwnertext_0049B820*>(source);
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A06E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A07A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A07E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0820);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0860);

void func_004A08A0(void* object)
{
}

s32 func_004A08B0(void* object)
{
    return 1;
}

typedef struct MappedEntry004A08C0
{
    u8 unk00[0x140];
} MappedEntry004A08C0;

typedef struct MappedOwner004A08C0
{
    u8 unk00[0x14];
    MappedEntry004A08C0* entries;
} MappedOwner004A08C0;

extern "C" void* func_004A08C0(const void* object, s32 index)
{
    const MappedOwner004A08C0* owner = (const MappedOwner004A08C0*)object;
    MappedEntry004A08C0* item = &owner->entries[index];
    void* result = item;
    if (item != 0)
    {
        result = (u8*)item + 0x140;
    }
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A08F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0A70);

void func_004A0C40(void* object)
{
}

s32 func_004A0C50(void* object)
{
    return 0;
}

void func_004A0C60(void* object)
{
}

s32 func_004A0C70(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0E00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0FD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A1150);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A1320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A14A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A1670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A17F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A19C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A1B40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A1D10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A1E90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A20C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2120);

float func_004A2200(void* object)
{
    return 1.0f;
}

float func_004A2210(void* object)
{
    return 1.0f;
}

float func_004A2220(void* object)
{
    return 1.0f;
}

float func_004A2230(void* object)
{
    return 1.0f;
}

float func_004A2240(void* object)
{
    return 1.0f;
}

float func_004A2250(void* object)
{
    return 1.0f;
}

float func_004A2260(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2270);

float func_004A22B0(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A22C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A29D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2EF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3140);

/**
 * @brief Turn fogging on or off, in the model's part packets too.
 * @param enabled Nonzero for fog.
 */
void LibModel::set_fog_enabled(u8 enabled)
{
    if (fog_enabled != enabled && parts != 0 && resource != 0)
    {
        u8* mesh = lib_resource_payload(resource);
        s32 count = *reinterpret_cast<s32*>(mesh + reinterpret_cast<LibMeshHeader*>(mesh)->unk38);

        if (enabled)
        {
            for (s32 index = 0; index < count; index++)
            {
                LibModelPart* part = lib_model_uncached_part(parts, index);
                part->first_tag_high |= GIF_TAG_HIGH_PRIM_FGE;
                part->second_tag_high |= GIF_TAG_HIGH_PRIM_FGE;

                if (part->unk84 != 0)
                {
                    part->third_tag_high |= GIF_TAG_HIGH_PRIM_FGE;
                    part->fourth_tag_high |= GIF_TAG_HIGH_PRIM_FGE;
                }
            }
        }
        else
        {
            for (s32 index = 0; index < count; index++)
            {
                LibModelPart* part = lib_model_uncached_part(parts, index);
                part->first_tag_high &= ~GIF_TAG_HIGH_PRIM_FGE;
                part->second_tag_high &= ~GIF_TAG_HIGH_PRIM_FGE;

                if (part->unk84 != 0)
                {
                    part->third_tag_high &= ~GIF_TAG_HIGH_PRIM_FGE;
                    part->fourth_tag_high &= ~GIF_TAG_HIGH_PRIM_FGE;
                }
            }
        }
    }

    LibModelBase::set_fog_enabled(enabled);
}

/**
 * @brief Make a copy of the model built from this one and linked to it.
 * @return The copy, or null when it couldn't be built.
 */
LibTransformOwner* LibModel::clone()
{
    LibModel* copy = new (0) LibModel;

    if (copy == 0)
    {
        return 0;
    }

    if (!copy->build_from(0, this))
    {
        delete copy;
        return 0;
    }

    add_clone(copy);
    lib_object_set_list_kind(this, LIB_LIST_KIND_LATE_MODEL);
    return copy;
}

/**
 * @brief Add draw flags and move the model to the late list.
 * @param model Model to update.
 * @param flags Flags to add.
 */
static inline void lib_model_add_draw_flags(LibTransformOwner* model, u16 flags)
{
    model->draw_flags |= flags;
    lib_object_set_list_kind(model, LIB_LIST_KIND_LATE_MODEL);
}

/**
 * @brief Build this model from another model.
 * @param links Display list the model draws through, or null.
 * @param source Model to copy.
 * @return Nonzero on success.
 */
s32 LibModel::build_from(LibUpdateList* links, LibModel* source)
{
    u8 listed;
    LibClass177A20* list = &source->children;
    listed = list->has_listed_entry();

    if (listed && !list->has_payload())
    {
        return 0;
    }

    set_resource(source->resource);
    unk638 = source->unk638;

    if (links != 0)
    {
        links->append_node(this, LibUpdateList::DEFAULT_NODE_KIND);

        if (source->draw_flags & LIB_DRAW_FOLLOW_CAMERA)
        {
            lib_model_add_draw_flags(this, LIB_DRAW_FOLLOW_CAMERA);
        }

        if (source->draw_flags & LIB_DRAW_FACE_CAMERA_X)
        {
            lib_model_add_draw_flags(this, LIB_DRAW_FACE_CAMERA_X);
        }

        if (source->draw_flags & LIB_DRAW_FACE_CAMERA_Y)
        {
            lib_model_add_draw_flags(this, LIB_DRAW_FACE_CAMERA_Y);
        }

        if (source->draw_flags & LIB_DRAW_FACE_CAMERA_Z)
        {
            lib_model_add_draw_flags(this, LIB_DRAW_FACE_CAMERA_Z);
        }
    }

    unk797_5 = source->unk797_5;
    LibColorModel::copy_color_state(source);

    if (static_cast<s32>(list->node_count) > 0 && listed)
    {
        build_packets();

        if (packet != 0)
        {
            list->apply_payload(this);
            this->source = source;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3A30);

/** @brief Destroy the channel; its palette, source colors and indices are borrowed. */
LibPaletteBlendChannel::~LibPaletteBlendChannel()
{
}

/** @brief Go back to the resource's own payload and release the override packets. */
void LibModel::clear_payload()
{
    LibModelBase::clear_payload();
    uses_payload_override = 0;

    for (s32 index = 0; index < LIB_MODEL_PACKET_SET_COUNT; index++)
    {
        resident_queue_allocation_release(g_resident_release_queues, override_packets[index]);
        override_packets[index] = 0;
    }
}

/**
 * @brief Switch to a payload override, or back to the resource's own with a set of two or more.
 * @param payload Payload to draw instead of the resource's own.
 * @param set Packet set to draw.
 */
void LibModel::select_payload(void* payload, u8 set)
{
    if (set > LIB_MODEL_PACKET_SET_COUNT - 1)
    {
        uses_payload_override = 0;
        LibModelBase::clear_payload();
    }
    else
    {
        uses_payload_override = 1;
        LibModelBase::select_payload(payload, set);
        packet_set = set;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3F50);

/**
 * @brief Give the centre for Lib's oriented-box visibility test, from the mesh, when the model is unscaled.
 * @param output Receives the box's centre and half extents in local space.
 * @return Nonzero when a centre was written.
 */
s32 LibModel::get_box_cull_center(void* output)
{
    LibVector4 extent;
    LibVector4 scale;

    if (resource == 0)
    {
        return 0;
    }

    if (!box_cull_enabled)
    {
        return 0;
    }

    vu0_start_microprogram_7f0_rows(&transform);
    vu0_wait_microprogram();
    vu0_read_vf6(&scale);

    float x = scale.x;
    float y = scale.y;
    float z = scale.z;

    if (!(x >= LIB_MODEL_UNSCALED_MIN && x <= LIB_MODEL_UNSCALED_MAX && y >= LIB_MODEL_UNSCALED_MIN &&
          y <= LIB_MODEL_UNSCALED_MAX && z >= LIB_MODEL_UNSCALED_MIN && z <= LIB_MODEL_UNSCALED_MAX))
    {
        return 0;
    }

    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(resource));
    LibCullBox* box = static_cast<LibCullBox*>(output);
    extent.x = 0.5f * (mesh->box_max[0] - mesh->box_min[0]);
    extent.y = 0.5f * (mesh->box_max[1] - mesh->box_min[1]);
    extent.z = 0.5f * (mesh->box_max[2] - mesh->box_min[2]);
    extent.w = 1.0f;
    copy_vector(&box->half_extents, &extent);
    extent.x += mesh->box_min[0];
    extent.y += mesh->box_min[1];
    extent.z += mesh->box_min[2];
    copy_vector(&box->center, &extent);
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A42A0);

/** @brief Pick the draw bucket from the draw flags, blend mode and mesh. */
void LibModel::set_default_draw_bucket()
{
    if (draw_flags & 0x1000)
    {
        draw_bucket = draw_bucket_choice = 7;
        return;
    }

    if (color_dirty)
    {
        draw_bucket_choice = 0;

        if (blend_mode)
        {
            draw_bucket_choice = 2;
        }

        LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(resource));

        if (mesh != 0)
        {
            color_dirty = 0;

            if (mesh->unk54 & 1)
            {
                draw_bucket_choice = 8;
            }
            else if (mesh->unk04 != 0)
            {
                draw_bucket_choice = 2;

                u8 kind = mesh->unk3c;

                if (kind == 2)
                {
                    draw_bucket_choice = 1;
                }
                else if (kind == 4)
                {
                    draw_bucket_choice = 6;
                }
                else if (kind == 3)
                {
                    draw_bucket_choice = 3;
                }
                else if (kind == 5)
                {
                    draw_bucket_choice = 8;
                }
                else if (kind == 6)
                {
                    draw_bucket_choice = 9;
                }
            }
        }
    }

    draw_bucket = draw_bucket_choice;
}

void func_004A4510(void* receiver)
{
    u8* object = (u8*)receiver;
    *(u8*)(object + 0x64) = 1;
    *(volatile u32*)0x10009020 = 0;
    *(volatile u32*)0x10009030 = *(u32*)(object + 0x710);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x105;
}

/** Forward the receiver to lib_finish_packet. */
void func_004A4550(void* object)
{
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

/** Queue the DMA submission embedded at offset 0x640 when present. */
s32 func_004A4570(void* object)
{
    DmaSubmission* submission = reinterpret_cast<DmaSubmission*>(object);
    if (object != 0)
    {
        submission = (DmaSubmission*)((u8*)submission + 0x640);
    }
    return func_00114100(g_vif1_dma_queue, submission);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A45A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A4710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A4ED0);

/**
 * @brief Append the channel's packets to a packet chain.
 * @param packet Current packet cursor.
 * @return The packet cursor, unchanged by the base channel.
 */
void* LibRenderChannel::append_packets(void* packet)
{
    return packet;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A59D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A5E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A62D0);

/**
 * @brief Default packet preparation that performs no work.
 * @param owner Rendering object that owns the channel.
 * @param program_address VU program entry point stored in the transfer commands.
 */
void LibRenderChannel::prepare_packets(LibTransform* owner, u32 program_address)
{
}

/** @brief Default channel update that performs no work. */
void LibRenderChannel::update()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A6D20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A6EA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7100);

/**
 * @brief Release a texture's block back to the free area, merging it with free neighbours.
 * @param index Cache index of the texture.
 */
void LibTextureCache::release_block(u32 index)
{
    u32 size = blocks[index].size;
    previous[next[index]] = previous[index];
    next[previous[index]] = next[index];
    u32 before = blocks[index].previous_block;
    u32 after = blocks[index].next_block;

    if (blocks[before].state == LIB_TEXTURE_BLOCK_FREE)
    {
        blocks[index].state = LIB_TEXTURE_BLOCK_UNUSED;
        size += blocks[before].size;
        blocks[before].size = size;
        blocks[after].previous_block = before;
        blocks[before].next_block = after;
        index = before;
    }

    if (blocks[after].state == LIB_TEXTURE_BLOCK_FREE)
    {
        blocks[after].state = LIB_TEXTURE_BLOCK_UNUSED;
        blocks[index].size = size + blocks[after].size;
        blocks[index].next_block = blocks[after].next_block;
        blocks[blocks[after].next_block].previous_block = index;
    }

    blocks[index].state = LIB_TEXTURE_BLOCK_FREE;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A75F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A76D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7D50);

/** @brief Allocate and fill the model's packets from its mesh. */
void LibModel::build_packets()
{
    if (resource == 0)
    {
        return;
    }

    u8* data = payload = lib_resource_payload(resource);
    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(data);
    s32 part_count = mesh->part_count;

    if (uses_payload_override && packet != 0)
    {
        return;
    }

    if (unk793 < 4)
    {
        unk793++;
    }

    delete packet;
    s32 size = part_count * LIB_MODEL_PART_QWORDS + LIB_MODEL_PACKET_FIXED_QWORDS + get_extra_packet_size();

    if (D_001B659C != 0)
    {
        packet = resident_heap_allocate(D_001B659C, size * 16);
    }
    else
    {
        packet = malloc_guess(size * 16);
    }

    if (packet == 0)
    {
        return;
    }

    s32 item_count;
    s32 base_size;

    s32* items = reinterpret_cast<s32*>(data + mesh->unk38);

    if (mesh->unk38 != 0)
    {
        item_count = *items;
        base_size = item_count * LIB_MODEL_BASE_QWORDS_PER_ITEM + LIB_MODEL_BASE_FIXED_QWORDS;
    }
    else
    {
        base_size = LIB_MODEL_BASE_FIXED_QWORDS;
    }

    delete base_packet;

    if (D_001B659C != 0)
    {
        base_packet = resident_heap_allocate(D_001B659C, base_size * 16);
    }
    else
    {
        base_packet = malloc_guess(base_size * 16);
    }

    if (base_packet != 0)
    {
        packet_chains[0].tags[0][0] = DMA_TAG(0, DMA_TAG_ID_CALL, static_cast<u8*>(base_packet) + LIB_MODEL_PACKET_HEADER_SIZE);
        packet_chains[1].tags[0][0] = DMA_TAG(0, DMA_TAG_ID_CALL, static_cast<u8*>(base_packet) + LIB_MODEL_PACKET_HEADER_SIZE);

        if (mesh->unk38 != 0)
        {
            delete unk720;
            if (D_001B659C != 0)
            {
                unk720 = resident_heap_allocate(D_001B659C,
                    (static_cast<u32>(item_count * LIB_MODEL_PART_SIZE) / 16 + LIB_MODEL_TABLE_HEADER_QWORDS) * 16);
            }
            else
            {
                unk720 = malloc_guess((static_cast<u32>(item_count * LIB_MODEL_PART_SIZE) / 16 + LIB_MODEL_TABLE_HEADER_QWORDS) * 16);
            }

            if (unk720 == 0)
            {
                goto failed;
            }

            parts = static_cast<u8*>(unk720) + LIB_MODEL_PACKET_HEADER_SIZE;
            func_004A7C20(this);
        }

        delete texture_uploads;

        if (D_001B659C != 0)
        {
            texture_uploads = static_cast<LibTextureUpload*>(
                resident_heap_allocate(D_001B659C, (mesh->unk40 * 2 + 8) * sizeof(LibTextureUpload)));
        }
        else
        {
            texture_uploads = static_cast<LibTextureUpload*>(malloc_guess((mesh->unk40 * 2 + 8) * sizeof(LibTextureUpload)));
        }

        if (texture_uploads != 0)
        {
            for (s32 texture = 0; texture < mesh->unk40 + 1; texture++)
            {
                for (s32 slot = 1; slot <= 2; slot++)
                {
                    s32 index = texture * 2 + slot;
                    *reinterpret_cast<unsigned __int128*>(&texture_uploads[index]) = 0;
                    *reinterpret_cast<unsigned __int128*>(&texture_uploads[index].mscal) = 0;
                    texture_uploads[index].unpack = VIF_UNPACK(VIF_UNPACK_V4_32, 5, 0x60);
                    texture_uploads[index].mscal = VIF_MSCALF(reinterpret_cast<u32>(D_678) >> 3);
                    texture_uploads[index].gif_tag = 4 | GIF_TAG_EOP | GIF_TAG_NREG(1);
                    texture_uploads[index].gif_registers = GIF_REGISTER_AD;
                    texture_uploads[index].trxpos.data = 0;
                    texture_uploads[index].trxpos.address = GS_REGISTER_TRXPOS;
                    texture_uploads[index].trxdir.data = 0;
                    texture_uploads[index].trxdir.address = GS_REGISTER_TRXDIR;
                }
            }

            for (s32 index = 0; index < 0x20; index++)
            {
                unk728[index] = 0;
            }

            s32 count = 0;
            *reinterpret_cast<u64*>(&chain[count]) = DMA_TAG(0, DMA_TAG_ID_CALL, static_cast<u8*>(base_packet) + LIB_MODEL_PACKET_HEADER_SIZE);
            count++;
            before_packet_size = get_before_packet_size();

            if (before_packet_size != 0)
            {
                delete before_packet;

                if (D_001B659C != 0)
                {
                    before_packet = resident_heap_allocate(D_001B659C, (before_packet_size + LIB_MODEL_EXTRA_BLOCK_QWORDS) * 16);
                }
                else
                {
                    before_packet = malloc_guess((before_packet_size + LIB_MODEL_EXTRA_BLOCK_QWORDS) * 16);
                }

                if (before_packet == 0)
                {
                    goto failed;
                }

                *reinterpret_cast<u64*>(&chain[count]) = DMA_TAG(0, DMA_TAG_ID_CALL, static_cast<u8*>(before_packet) + LIB_MODEL_PACKET_HEADER_SIZE);
                count++;
            }

            *reinterpret_cast<u64*>(&chain[count]) = DMA_TAG(0, DMA_TAG_ID_CALL, static_cast<u8*>(packet) + LIB_MODEL_PACKET_HEADER_SIZE);
            count++;
            after_packet_size = get_after_packet_size();

            if (after_packet_size != 0)
            {
                delete after_packet;

                if (D_001B659C != 0)
                {
                    after_packet = resident_heap_allocate(D_001B659C, (after_packet_size + LIB_MODEL_EXTRA_BLOCK_QWORDS) * 16);
                }
                else
                {
                    after_packet = malloc_guess((after_packet_size + LIB_MODEL_EXTRA_BLOCK_QWORDS) * 16);
                }

                if (after_packet == 0)
                {
                    goto failed;
                }

                *reinterpret_cast<u64*>(&chain[count]) = DMA_TAG(0, DMA_TAG_ID_CALL, static_cast<u8*>(after_packet) + LIB_MODEL_PACKET_HEADER_SIZE);
                count++;
            }

            *reinterpret_cast<u64*>(&chain[count]) = DMA_TAG_ID_END;
            FlushCache(0);
            unk77c = part_count;
            return;
        }
    }

failed:
    delete packet;
    packet = 0;
    delete base_packet;
    base_packet = 0;
    delete unk720;
    unk720 = 0;
    delete unk720;
    unk720 = 0;
    delete before_packet;
    before_packet = 0;
    delete after_packet;
    after_packet = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", __ct__8LibModelFv);

/**
 * @brief Report the base channel's empty entry set.
 * @return Zero.
 */
s32 LibRenderChannel::get_entry_count()
{
    return 0;
}

/**
 * @brief Provide the base channel's empty entry lookup.
 * @param index Entry index; unused in the base channel.
 * @return Null.
 */
void* LibRenderChannel::get_entry(s32 index)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8810);

s32 func_004A88A0(void* object)
{
    return 13;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A88B0);

/** @brief Destroy the controller and its inherited transform state. */
LibLodController::~LibLodController()
{
}

/**
 * @brief Return the level-selection controller's kind identifier.
 * @return Kind nine.
 */
s32 LibLodController::get_default_list_kind()
{
    return 9;
}

/**
 * @brief Copy level-selection state and inherited transform state.
 * @param source Source controller.
 */
void LibLodController::copy_state(const LibLodController* source)
{
    s32 index;
    position_offset_applied = source->position_offset_applied;
    object_count = source->object_count;
    for (index = 0; index < LIB_LOD_LEVEL_CAPACITY; index++)
    {
        level_boundaries[index] = source->level_boundaries[index];
        range_minimums[index] = source->range_minimums[index];
        range_maximums[index] = source->range_maximums[index];
    }
    level_count = source->level_count;
    active_level = source->active_level;
    display_manager = source->display_manager;
    for (index = 0; index < LIB_LOD_OBJECT_CAPACITY; index++)
    {
        objects[index] = source->objects[index];
    }
    position_offset = source->position_offset;
    LibTransform::copy_offset_transform_state(source);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8B10);

/**
 * @brief Append a handle when the collection has fewer than sixty-four entries.
 * @param collection Destination collection.
 * @param object Handle to append.
 */
void lib_append_entry_handle(LibEntryHandleCollection* collection, void* object)
{
    if (collection->object_count < LIB_LOD_OBJECT_CAPACITY)
    {
        collection->objects[collection->object_count++] = object;
    }
}

/**
 * @brief Store and apply an offset to the controller's position.
 * @param offset Position offset.
 */
void LibLodController::apply_position_offset(const FieldVec4A& offset)
{
    position_offset = offset;
    lib_lod_set_position(this, lib_lod_add_position_offset(*reinterpret_cast<const FieldVec4B*>(&translation), offset));
    position_offset_applied = 1;
}

/** @brief Initialize the controller's offset flag, object count, and selected level. */
LibLodController::LibLodController()
{
    type_id = 6;
    position_offset_applied = 0;
    object_count = 0;
    active_level = -1;
}

s32 func_004A8DD0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8DE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8E30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8F10);

/** @brief Release the word buffer when it is owned by this object. */
LibResourceBitset::~LibResourceBitset()
{
    if (!words_are_borrowed)
    {
        delete[] words;
    }
}

s32 func_004A8FF0(void* object)
{
    return 11;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", has_listed_entry__14LibClass177A20Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", apply_payload__14LibClass177A20FP8LibModel);

/**
 * @brief Queue the object's receiver for deferred destruction.
 * @param object Object containing the receiver at offset 0x14, or null.
 */
extern "C" void lib_queue_object_release(void* object)
{
    u8* receiver = static_cast<u8*>(object);

    if (object != 0)
    {
        receiver += 0x14;
    }

    resident_enqueue_object(g_resident_release_queues, receiver);
}

void func_004A9220(void* object)
{
}

void func_004A9230(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9770);

s32 func_004AA410(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AA420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AAFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB1F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB2D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB700);
