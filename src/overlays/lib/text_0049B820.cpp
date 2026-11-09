#include "overlays/lib/palette_blend_channel.h"
#include "include_asm.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_data.h"
#include "main/func_0011EE00.h"
#include "main/resident_00101260.h"
#include "overlays/lib/model.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "ee.h"
#include "clamp.h"
#include "gs.h"
#include "vu0.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libc_guess_00137290.h"

/** FGE as it sits in the upper word of a GIF tag's first doubleword. */
#define GIF_TAG_HIGH_PRIM_FGE ((u32)(GIF_TAG_PRIM(GS_PRIM_FGE) >> 32))

/** ABE as it sits in the upper word of a GIF tag's first doubleword. */
#define GIF_TAG_HIGH_PRIM_ABE ((u32)(GIF_TAG_PRIM(GS_PRIM_ABE) >> 32))

/** Byte size of each part record in the model's part table. */
#define LIB_MODEL_PART_SIZE 0xF0

/** Partial part record in the model's part table: the upper tag words of its GIF tags, written uncached. */
struct LibModelPart
{
    u8 unk00[0x20];
    u32 unk20;
    u8 unk24[0x40];
    u32 first_tag_high;
    u8 unk68[0xC];
    u32 second_tag_high;
    u8 unk78[0xC];

    /** Nonzero when the part has the second pair of GIF tags. */
    u32 unk84;

    u8 unk88[8];
    u32 unk90;
    u8 unk94[8];
    u32 unk9c;
    u8 unka0[0x24];
    u32 third_tag_high;
    u8 unkc8[0xC];
    u32 fourth_tag_high;
    u8 unkd8[0x18];
};

/** Partial part record in a mesh resource; the model's copy of its part starts at 0x40. */
struct LibMeshPartRecord
{
    u8 unk00[0x14];
    u16 unk14;
    u8 unk16[0x2A];
    LibModelPart part;
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

/** Bytes a payload buffer gets on top of the model's payload size. */
#define LIB_PAYLOAD_BUFFER_EXTRA 0x80

/** Heap model packets come from when set; otherwise they're malloc'd. */
extern "C" void* D_001B659C;

/** Heap payload buffers come from when set; otherwise they're malloc'd. */
extern "C" void* D_001B65A8;

/** Resident hit-test flags; bit 0 is set when a hit-test node is removed. */
extern "C" u8 D_001B65D0;

/** VU1 microprogram that uploads a model's textures. */
extern "C" u8 D_678[];

/**
 * @brief Fill the model's part table from its mesh.
 * @param model Model whose parts table to fill.
 */
extern "C" void func_004A7C20(LibModel* model);

/**
 * @brief Bind a child list to a model and add it to a display list.
 * @param list List to bind.
 * @param model Model the list's payloads are drawn by.
 * @param links Display list the list is added to.
 */
extern "C" void func_004AB360(LibClass177A20* list, LibModel* model, LibUpdateList* links);

/**
 * @brief Point a resource's record cursor at its first part record.
 * @param resource Resource to rewind.
 */
extern "C" void func_004D5C10(LibResourceBuffer* resource);

/**
 * @brief Return the record at a resource's cursor and move the cursor to the next one.
 * @param resource Resource to read.
 * @return The record, or null at the end.
 */
extern "C" void* func_004D5AC0(LibResourceBuffer* resource);

/**
 * @brief Return the size of the payload a model draws.
 * @param model Model to measure.
 * @return Size in bytes.
 */
extern "C" u32 func_004D5F50(LibModel* model);

/**
 * @brief Build a packet set's payload in its buffer.
 * @param list List whose payload to build.
 * @param set Packet set.
 */
extern "C" void func_004AAFF0(LibClass177A20* list, s32 set);

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

/**
 * @brief Copy another grid's size, emission settings and storage settings.
 * @param source Grid to copy.
 */
void LibClass177090::copy_settings(const LibClass173A40* source)
{
    const LibClass177090* other = static_cast<const LibClass177090*>(source);

    unk0c = other->unk0c;
    unk10 = other->unk10;
    resize(unk0c, unk10);
    unk28 = other->unk28;
    unk30 = other->unk30;
    unk34 = other->unk34;
    unk38 = other->unk38;
    unk48 = other->unk48;
    unk4c = other->unk4c;
    unk4d = other->unk4d;
    unk4e = other->unk4e;
    unk4f = other->unk4f;
    unk50 = other->unk50;
    unk54 = other->unk54;
    unk55 = other->unk55;
    unk3c = other->unk3c;
    unka0 = other->unka0;
    unka4 = other->unka4;
    unkb8 = other->unkb8;
    unkbc = other->unkbc;
    unkc0 = other->unkc0;
    unkc4 = other->unkc4;
    unkc8 = other->unkc8;
    // TODO: The copy marks its own storage borrowed by storing the same pointers back. I think this was
    // an inline setter given unkb0 and unkb4, but every helper form I tried loads them in the other order.
    u8* first = unkb0;
    FieldVec4A* second = unkb4;
    unkc9 = 1;
    unkb0 = first;
    unkb4 = second;
    unkc4 = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049ED80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A02D0);

/** @brief Free the storage unless it's borrowed, then destroy the grid. */
LibClass177090::~LibClass177090()
{
    if (!unkc9)
    {
        delete[] unkb0;
        delete[] unkb4;
    }
}

/** @brief Start with no storage. */
LibClass177090::LibClass177090()
{
    unkc8 = 0;
    unkc9 = 0;
    unkb8 = 0;
    unkbc = 0;
    unkb0 = 0;
    unkb4 = 0;
}

/** @brief Start with no storage. */
LibClass174120::LibClass174120()
{
    unkc8 = 0;
    unkc9 = 0;
    unkb8 = 0;
    unkbc = 0;
    unkb0 = 0;
    unkb4 = 0;
}

/**
 * @brief Copy another grid's size and emission settings.
 * @param source Grid to copy.
 */
void LibClass176FC0::copy_settings(const LibClass173A40* source)
{
    const LibClass176FC0* other = static_cast<const LibClass176FC0*>(source);

    unk0c = other->unk0c;
    unk10 = other->unk10;
    resize(unk0c, unk10);
    unk28 = other->unk28;
    unk30 = other->unk30;
    unk34 = other->unk34;
    unk38 = other->unk38;
    unk48 = other->unk48;
    unk4c = other->unk4c;
    unk4d = other->unk4d;
    unk4e = other->unk4e;
    unk4f = other->unk4f;
    unk50 = other->unk50;
    unk54 = other->unk54;
    unk55 = other->unk55;
    unk3c = other->unk3c;
    unka0 = other->unka0;
    unka4 = other->unka4;
}

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

/**
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass1771A0::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

/**
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass177270::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

/**
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass177340::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

/**
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass177410::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

/**
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass1774E0::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

/**
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass1775B0::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

/**
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass177680::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

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

/** @brief Start with no storage. */
LibClass174240::LibClass174240()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1c = 0;
    unk20 = 0;
    unk24 = 0;
}

/** @brief Start with no storage. */
LibClass177750::LibClass177750()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1c = 0;
    unk20 = 0;
    unk24 = 0;
}

/** @brief Release the cells, the bit set and the secondary elements. */
LibClass177750::~LibClass177750()
{
    delete[] unk18;
    delete unk1c;
    delete[] unk24;
}

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

/**
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass177750::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

float func_004A22B0(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A22C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2370);

/**
 * @brief Test whether any part of the mesh blends with an ALPHA setting weighted by destination alpha.
 *
 * As I read them, 0x54, 0x58 and 0x52 are ALPHA register values with C = Ad: plain, additive and subtractive
 * blending.
 * @return Nonzero when one does.
 */
s32 LibModel::func_004A2870()
{
    if (resource == 0)
    {
        return 0;
    }

    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(resource));
    s32 count = mesh->part_count;
    func_004D5C10(resource);

    for (s32 index = 0; index < count; index++)
    {
        LibMeshPartRecord* record =
            reinterpret_cast<LibMeshPartRecord*>(reinterpret_cast<u32>(func_004D5AC0(resource)) | UNCACHED_SEGMENT);

        if (record->unk14 & 1)
        {
            LibModelPart* part = reinterpret_cast<LibModelPart*>(reinterpret_cast<u32>(&record->part) | UNCACHED_SEGMENT);

            if (part->unk20 == 0x54 || part->unk20 == 0x58 || part->unk20 == 0x52)
            {
                return 1;
            }

            if (part->unk9c != 0 && (part->unk90 == 0x54 || part->unk90 == 0x58 || part->unk90 == 0x52))
            {
                return 1;
            }
        }
    }

    return 0;
}

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

/** @brief Write the pending part settings into the part records' GIF tags, then free them. */
void LibModel::apply_part_settings()
{
    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(resource));
    s32 part_count = mesh->part_count;
    u8** table;

    if (unk768 != 0)
    {
        table = reinterpret_cast<u8**>(static_cast<u8*>(unk768) + part_count * 12);
    }
    else
    {
        table = reinterpret_cast<u8**>(static_cast<u8*>(unk76c) + part_count * 12);
    }

    s32 count = unk774;

    for (s32 index = 0; index < count; index++)
    {
        LibModelPartSetting* setting = &unk770[index];
        LibModelPart* part = reinterpret_cast<LibModelPart*>(
            reinterpret_cast<u32>(reinterpret_cast<u8**>(table[index + unk778])[1]) | EE_UNCACHED_ACCELERATED);

        if (setting->flags & 1)
        {
            part->unk20 = setting->first_value;
            part->first_tag_high &= ~GIF_TAG_HIGH_PRIM_ABE;
            part->second_tag_high &= ~GIF_TAG_HIGH_PRIM_ABE;
        }

        if (setting->flags & 2)
        {
            part->unk90 = setting->second_value;
            part->third_tag_high &= ~GIF_TAG_HIGH_PRIM_ABE;
            part->fourth_tag_high &= ~GIF_TAG_HIGH_PRIM_ABE;
        }
    }

    delete unk770;
    unk770 = 0;
}

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

/**
 * @brief Look up an image's texture and record a hit for a slot, raising a user-owned texture's priority.
 * @param image Image header whose name and ID identify the texture.
 * @param slot Slot whose last hit is recorded.
 * @param user Object that would own the texture; unused.
 * @return Zero on a hit or for an 'MlPs' image, one when the texture still has to be loaded.
 */
s32 LibTextureCache::func_004A6D20(const LibImageHeader* image, s32 slot, LibTextureUser* user)
{
    u32 index = next[0];
    u32 id = image->id;
    u32 tag = *reinterpret_cast<const u32*>(image->name);

    while (index != 0)
    {
        if (blocks[index].id == id && entries[index].tag == tag)
        {
            blocks[index].stamp = stamp;

            if (entries[index].user == 0)
            {
                if (next[0] != index)
                {
                    move_to_front(index);
                }

                slot_entries[slot] = index;
                return 0;
            }
            else
            {
                s32 priority = entries[index].user->priority;

                if (next[0] != index && priority >= LIB_TEXTURE_PRIORITY_KEEP)
                {
                    move_to_front(index);
                }

                slot_entries[slot] = index;
                priority++;
                priority = clamp_high(priority, LIB_TEXTURE_PRIORITY_MAX);
                entries[index].user->priority = priority;
                return 0;
            }
        }

        index = next[index];
    }

    if (tag == LIB_TEXTURE_TAG_MLPS)
    {
        return 0;
    }

    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A6EA0);

/** @brief Clear the cache's stamp, the stamp of every block stamped 1, and the CLUT use flags. */
void LibTextureCache::clear_stamps()
{
    stamp = 0;

    for (u32 index = blocks[0].next_block; index != 0; index = blocks[index].next_block)
    {
        if (blocks[index].stamp == 1)
        {
            blocks[index].stamp = 0;
        }
    }

    unsigned __int128* flags = reinterpret_cast<unsigned __int128*>(clut_used);
    s32 count = clut_count / 16;

    for (s32 index = 0; index < count; index++)
    {
        *flags++ = 0;
    }
}

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

/** @brief Update each render channel when the mesh asks for it. */
void LibModel::update_render_channels()
{
    if (payload != 0 && reinterpret_cast<LibMeshHeader*>(payload)->unk08 != 0)
    {
        LibListSentinel* node = &render_channels.sentinel;

        for (;;)
        {
            node = node->next;

            if (&render_channels.sentinel == node)
            {
                break;
            }

            static_cast<LibRenderChannel*>(node)->update();
        }
    }
}

/** @brief Advance the model; while the resource's first state bit is set, count unk793 up to four and set unk795. */
void LibModel::update()
{
    if (D_001B65D0 & 1)
    {
        unk780 = 0;
    }

    if (resource != 0 && (resource->unk01 & 1) && unk793 < 4)
    {
        unk793++;
        unk795 = 1;
    }

    LibModelBase::update();
}

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

/** @brief Destroy the list receiver and its sentinel. */
inline LibListReceiver::~LibListReceiver()
{
}

/** @brief Release the channels and packets, then destroy the model. */
LibModel::~LibModel()
{
    LibListSentinel* next = render_channels.sentinel.next;

    for (;;)
    {
        if (&render_channels.sentinel == next)
        {
            break;
        }

        LibRenderChannel* channel = static_cast<LibRenderChannel*>(next);
        next = next->next;
        render_channels.unlink(channel);
        delete channel;
    }

    delete packet;
    delete override_packets[0];
    delete override_packets[1];
    delete base_packet;
    delete texture_uploads;
    delete unk768;
    delete unk76c;
    delete unk770;
    delete unk720;
    delete before_packet;
    delete after_packet;
}

/** @brief Construct an empty model. */
LibModel::LibModel()
    : base_packet(0), packet(0), texture_uploads(0), unk720(0), parts(0), unk768(0), unk76c(0), unk770(0), unk77c(0),
      unk780(0), payload(0), unk790(0), unk791(0), draw_bucket_choice(0), unk793(0), packet_set(0), unk795(0),
      unk796(0), unk797_0(0), unk797_1(0), unk797_2(0), uses_payload_override(0), unk797_5(0), unk797_6(0),
      unk797_7(0), unk798_0(0), unk798_2(0)
{
    source = 0;
    set_type_id(0x100);
    unk5a1 = 0;
    packet_chains[0].tags[2][0] = DMA_TAG_ID_END;
    packet_chains[1].tags[2][0] = DMA_TAG_ID_END;
    override_packets[0] = 0;
    override_packets[1] = 0;
    unk7c0 = 1.0f;
    unk7c4 = 1.0f;
    unk7c8[0] = 0;
    unk7c8[1] = 0;
    unk7c8[2] = 0;
    unk7c8[3] = 0;
    unk7c8[4] = 0;
    unk7c8[5] = 0;

    for (s32 index = 0; index < 0x20; index++)
    {
        unk748[index] = 0;
    }

    unk7e0 = 0;
    before_packet = 0;
    after_packet = 0;
    box_cull_enabled = 0;
    FlushCache(0);
}

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

/** @brief Destroy the object. */
LibClass177940::~LibClass177940()
{
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Thirteen.
 */
s32 LibClass177940::get_default_list_kind()
{
    return 13;
}

/** @brief Draw the renderer's frame and wait for its packets, between two calls on the resident sound. */
void LibClass177940::update()
{
    renderer->func_004D2C70();
    frame_start_time = TIMER0_COUNT;
    func_0010F250(func_00101270(resident_get_system()), 1);
    renderer->func_004D44D0(0);
    resident_sync_gs_path(g_input_system, 0, 0);
    func_0010ECF0(func_00101270(resident_get_system()));
}

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

/** @brief Show the objects of the level the camera distance falls in and hide the previous level's. */
void LibLodController::update()
{
    LibCamera* camera = static_cast<LibCamera*>(static_cast<LibDisplayManager*>(display_manager)->current_display);

    if (camera == 0)
    {
        return;
    }

    LibVector4 view;
    vu0_start_microprogram_1f0_vf5_vf8(&camera->view_matrix);
    vu0_start_microprogram_1b0_vf5(&translation);
    vu0_wait_microprogram();
    vu0_read_vf6(&view);
    float distance;

    if (view.z <= 1.0f)
    {
        distance = 8.0f;
    }
    else
    {
        distance = 640.0f / view.z;
    }

    s32 level = 0;

    for (s32 index = 0; index < level_count; index++)
    {
        if (range_minimums[index] <= distance && !(range_maximums[index] <= distance))
        {
            level = index;
            break;
        }
    }

    if (active_level != level)
    {
        if (active_level >= 0)
        {
            for (s32 index = level_boundaries[active_level]; index < level_boundaries[active_level + 1]; index++)
            {
                if (index >= object_count)
                {
                    break;
                }

                LibTransformOwner* object = static_cast<LibTransformOwner*>(objects[index]);
            object->draw_flags |= LIB_DRAW_FLAG_0008;
            }
        }

        for (s32 index = level_boundaries[level]; index < level_boundaries[level + 1]; index++)
        {
            if (index >= object_count)
            {
                break;
            }

            LibTransformOwner* object = static_cast<LibTransformOwner*>(objects[index]);
            object->draw_flags &= ~LIB_DRAW_FLAG_0008;
        }
    }

    active_level = level;
}

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

/**
 * @brief Return the entry's type code.
 * @return Zero for the base entry.
 */
s32 LibClass1779F0::func_slot14()
{
    return 0;
}

/**
 * @brief Add the entry to a model's child list, binding the list to the model first.
 * @param model Model whose children list to join.
 * @param links Display list passed on to the list's binding.
 */
void LibClass1779F0::attach(LibModel* model, LibUpdateList* links)
{
    LibClass177A20* children = &model->children;
    list = children;
    func_004AB360(children, model, links);
    children->append(this);
}

/** @brief Leave the list, then free the data unless it's borrowed. */
LibClass1779F0::~LibClass1779F0()
{
    if (list != 0)
    {
        list->unlink(this);
        list->release_model();
        list = 0;
    }

    if (!data_is_borrowed)
    {
        delete data;
    }
}

/** @brief Start unattached, with no data. */
LibClass1779F0::LibClass1779F0()
{
    data_is_borrowed = 0;
    data = 0;
    list = 0;
    listed = 1;
    unk18 = 1;
    unk19 = 0;
    unk0f = 0;
}

s32 func_004A8FF0(void* object)
{
    return 11;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9000);

/**
 * @brief Make the model draw one packet set's payload.
 * @param set Packet set to select; only set zero when the list has a single payload.
 * @return The previously selected set, or -1 when the set isn't available.
 */
s32 LibClass177A20::select_payload_set(u8 set)
{
    if (set && unk8d_0)
    {
        return -1;
    }

    s32 previous = payload_set;
    payload_set = set;
    model->select_payload(payloads[payload_set], payload_set);
    return previous;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", has_listed_entry__14LibClass177A20Fv);

/**
 * @brief Hand the list's payload to a model, in one packet set or both.
 * @param model Model to give the payload to.
 * @return Nonzero on success.
 */
s32 LibClass177A20::apply_payload(LibModel* model)
{
    if (unk8d_0)
    {
        if (payload_buffers[0] == 0)
        {
            return 0;
        }

        model->load_payload(payloads[0], 0);
    }
    else
    {
        if (payload_buffers[0] == 0 || payload_buffers[1] == 0)
        {
            return 0;
        }

        for (s32 set = 0; set < LIB_MODEL_PACKET_SET_COUNT; set++)
        {
            model->load_payload(payloads[set], set);
        }
    }

    return 1;
}

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

/**
 * @brief Allocate a packet set's payload buffer for the model's payload, then build the payload in it.
 * @param set Packet set; set one is skipped when the list has a single payload.
 */
void LibClass177A20::allocate_payload(s32 set)
{
    if (unk8d_0 && set == 1)
    {
        return;
    }

    if (D_001B65A8 != 0)
    {
        if (payload_buffers[set] != 0)
        {
            resident_heap_release(payload_buffers[set]);
        }

        payload_buffers[set] = resident_heap_allocate(D_001B65A8, func_004D5F50(model) + LIB_PAYLOAD_BUFFER_EXTRA);
    }
    else
    {
        free_guess(payload_buffers[set]);
        payload_buffers[set] = malloc_guess(func_004D5F50(model) + LIB_PAYLOAD_BUFFER_EXTRA);
    }

    if (payload_buffers[set] != 0)
    {
        FlushCache(0);
        func_004AAFF0(this, set);
    }
}

/** @brief Once the list is empty, detach it, clear the model's payload and free the payload buffers. */
void LibClass177A20::release_model()
{
    if (model != 0 && node_count == 0)
    {
        lib_object_detach_owner(unk14);
        model->clear_payload();
        model = 0;
        delete unk5c;
        delete unk60;
        delete unk68;
        delete unk6c;
        delete unk70;
        unk5c = 0;
        unk60 = 0;
        unk68 = 0;
        unk6c = 0;
        unk70 = 0;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB700);
