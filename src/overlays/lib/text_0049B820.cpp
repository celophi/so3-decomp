#include "overlays/lib/palette_blend_channel.h"
#include "overlays/lib/texture_scroll_channel.h"
#include "include_asm.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_data.h"
#include "overlays/lib/model.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "ee.h"
#include "clamp.h"
#include "gs.h"
#include "vu0.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libc_guess_00137290.h"
#include "overlays/lib/grid_emission.h"
#include "overlays/lib/grid_frame_vu0.h"
#include "overlays/lib/emission_vu0.h"
#include "overlays/lib/morph_vu0.h"

/** ABE as it sits in the upper word of a GIF tag's first doubleword. */
#define GIF_TAG_HIGH_PRIM_ABE ((u32)(GIF_TAG_PRIM(GS_PRIM_ABE) >> 32))



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



#define LIB_MODEL_UNSCALED_MIN 0.999f
#define LIB_MODEL_UNSCALED_MAX 1.001f

#define LIB_MODEL_PACKET_HEADER_SIZE 0x40
#define LIB_MODEL_PACKET_FIXED_QWORDS 19
#define LIB_MODEL_PART_QWORDS 5
#define LIB_MODEL_BASE_FIXED_QWORDS 32
#define LIB_MODEL_BASE_QWORDS_PER_ITEM 10
#define LIB_MODEL_EXTRA_BLOCK_QWORDS 9
#define LIB_MODEL_TABLE_HEADER_QWORDS 8
#define LIB_PAYLOAD_BUFFER_EXTRA 0x80

/** Heap model packets come from when set; otherwise they're malloc'd. */
extern "C" void* D_001B659C;

/** Heap payload buffers come from when set; otherwise they're malloc'd. */
extern "C" void* D_001B65A8;

extern "C" u8 D_001B65A0;

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

/**
 * @brief Copy another grid's size, emission settings, frame data and the two words at 0xB0: the settings copy of
 *        LibClass175900 (vtable slot 0xB4, also inherited by LibClass175830).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
extern "C" void func_0049DA60(LibGridEmitterB0* object, const LibGridEmitterB0* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->primary_emitter = other->primary_emitter;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->primary_emission_flags = other->primary_emission_flags;
    object->primary_emission_count = other->primary_emission_count;
    object->secondary_emitter = other->secondary_emitter;
    object->secondary_emission_flags = other->secondary_emission_flags;
    object->secondary_emission_count = other->secondary_emission_count;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
    object->unkb0 = other->unkb0;
    object->unkb4 = other->unkb4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049DB40);

struct LibColliderList;

/**
 * @brief Move a grid's colliders with the transform it emits from.
 * @param list Colliders.
 * @param source Transform.
 */
extern "C" void func_0043CCE0(LibColliderList* list, LibTransform* source);

/**
 * @brief Update a grid's force from the transform it emits from.
 * @param force Force record; its vector is at 0x10.
 * @param source Transform.
 */
extern "C" void func_004349D0(void* force, LibTransform* source);

/**
 * @brief Start a grid's emission pass: reset its cursor, copy the source's transposed transform, update its colliders
 *        and force, and load the force, frame time and color limit into VU0.
 * @param object Grid.
 * @param source Transform the grid emits from.
 */
extern "C" void func_0049E270(LibGridEmitterB0* object, LibTransform* source)
{
    object->index = 0;
    object->unk60.packed = reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[0];
    object->unk70.packed = reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[1];
    object->unk80.packed = reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[2];
    object->unk90.packed = reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[3];

    if (object->unkb4)
    {
        func_0043CCE0(static_cast<LibColliderList*>(object->unkb4), source);
    }

    if (object->unkb0)
    {
        func_004349D0(object->unkb0, source);
        vu0_load_grid_force(static_cast<u8*>(object->unkb0) + 0x10);
    }
    else
    {
        vu0_clear_grid_force();
    }

    vu0_clear_grid_vf10();
    vu0_set_emission_delta(g_frame_seconds);

    FieldVec4A limit(255.0f, 255.0f, 255.0f, 255.0f);
    vu0_clear_grid_vf30();
    vu0_load_grid_color_limit(&limit);
}

/**
 * @brief Copy another grid's size, emission settings, frame data and the two words at 0xB0: the settings copy of
 *        LibClass175760 (vtable slot 0xB4, also inherited by LibClass175690).
 * @param object Grid to update.
 * @param other Grid to copy.
 */
extern "C" void func_0049E360(LibGridEmitterB0* object, const LibGridEmitterB0* other)
{
    object->cell_count = other->cell_count;
    object->columns = other->columns;
    object->resize(object->cell_count, object->columns);
    object->unk28 = other->unk28;
    object->unk30 = other->unk30;
    object->unk34 = other->unk34;
    object->unk38 = other->unk38;
    object->primary_emitter = other->primary_emitter;
    object->unk4C = other->unk4C;
    object->unk4D = other->unk4D;
    object->primary_emission_flags = other->primary_emission_flags;
    object->primary_emission_count = other->primary_emission_count;
    object->secondary_emitter = other->secondary_emitter;
    object->secondary_emission_flags = other->secondary_emission_flags;
    object->secondary_emission_count = other->secondary_emission_count;
    object->unk3C = other->unk3C;
    object->frame_header = other->frame_header;
    object->frame_records = other->frame_records;
    object->unkb0 = other->unkb0;
    object->unkb4 = other->unkb4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_0049E440);

/**
 * @brief Start a grid's emission pass: reset its cursor, copy the source's transposed transform, update its colliders
 *        and force, and load the force, frame time and color limit into VU0.
 * @param object Grid.
 * @param source Transform the grid emits from.
 */
extern "C" void func_0049EB80(LibGridEmitterB0* object, LibTransform* source)
{
    object->index = 0;
    object->unk60.packed = reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[0];
    object->unk70.packed = reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[1];
    object->unk80.packed = reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[2];
    object->unk90.packed = reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[3];

    if (object->unkb4)
    {
        func_0043CCE0(static_cast<LibColliderList*>(object->unkb4), source);
    }

    if (object->unkb0)
    {
        func_004349D0(object->unkb0, source);
        vu0_load_grid_force(static_cast<u8*>(object->unkb0) + 0x10);
    }
    else
    {
        vu0_clear_grid_force();
    }

    vu0_clear_grid_vf10();
    vu0_set_emission_delta(g_frame_seconds);

    FieldVec4A limit(255.0f, 255.0f, 255.0f, 255.0f);
    vu0_clear_grid_vf30();
    vu0_load_grid_color_limit(&limit);
}

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

/**
 * @brief Start the grid's emission pass: reset its cursor, copy the source's transposed transform, update its
 *        colliders and force, and load the force, frame time and color limit into VU0.
 * @param object Grid.
 * @param source Transform the grid emits from.
 */
extern "C" void func_004A02D0(LibClass177090* object, LibTransform* source)
{
    object->unk2c = 0;
    *reinterpret_cast<unsigned __int128*>(&object->unk60[0]) =
        reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[0];
    *reinterpret_cast<unsigned __int128*>(&object->unk60[1]) =
        reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[1];
    *reinterpret_cast<unsigned __int128*>(&object->unk60[2]) =
        reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[2];
    *reinterpret_cast<unsigned __int128*>(&object->unk60[3]) =
        reinterpret_cast<const unsigned __int128*>(&source->transposed_transform)[3];

    if (object->unkbc)
    {
        func_0043CCE0(static_cast<LibColliderList*>(object->unkbc), source);
    }

    if (object->unkb8)
    {
        func_004349D0(object->unkb8, source);
        vu0_load_grid_force_vf18(static_cast<u8*>(object->unkb8) + 0x10);
    }
    else
    {
        vu0_clear_grid_force_vf18();
    }

    vu0_clear_grid_vf17();
    vu0_set_emission_delta(g_frame_seconds);

    FieldVec4A limit(255.0f, 255.0f, 255.0f, 255.0f);
    vu0_clear_grid_vf30();
    vu0_load_grid_color_limit(&limit);
}

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

/**
 * @brief Emit entries through the grid's primary linked emitter.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A08F0(LibGridEmitter* grid, const LibVector4* position, const LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_primary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's secondary linked emitter, if it has one.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set; its fourth component receives the grid's unk3C.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A0A70(LibGridEmitter* grid, const LibVector4* position, LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_secondary(grid, position, first_offset, second_offset, color_scale);
}

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

/**
 * @brief Emit entries through the grid's primary linked emitter.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A0C80(LibGridEmitter* grid, const LibVector4* position, const LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_primary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's secondary linked emitter, if it has one.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set; its fourth component receives the grid's unk3C.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A0E00(LibGridEmitter* grid, const LibVector4* position, LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_secondary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's primary linked emitter.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A0FD0(LibGridEmitter* grid, const LibVector4* position, const LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_primary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's secondary linked emitter, if it has one.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set; its fourth component receives the grid's unk3C.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A1150(LibGridEmitter* grid, const LibVector4* position, LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_secondary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's primary linked emitter.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A1320(LibGridEmitter* grid, const LibVector4* position, const LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_primary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's secondary linked emitter, if it has one.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set; its fourth component receives the grid's unk3C.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A14A0(LibGridEmitter* grid, const LibVector4* position, LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_secondary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's primary linked emitter.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A1670(LibGridEmitter* grid, const LibVector4* position, const LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_primary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's secondary linked emitter, if it has one.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set; its fourth component receives the grid's unk3C.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A17F0(LibGridEmitter* grid, const LibVector4* position, LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_secondary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's primary linked emitter.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A19C0(LibGridEmitter* grid, const LibVector4* position, const LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_primary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's secondary linked emitter, if it has one.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set; its fourth component receives the grid's unk3C.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A1B40(LibGridEmitter* grid, const LibVector4* position, LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_secondary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's primary linked emitter.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A1D10(LibGridEmitter* grid, const LibVector4* position, const LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_primary(grid, position, first_offset, second_offset, color_scale);
}

/**
 * @brief Emit entries through the grid's secondary linked emitter, if it has one.
 * @param grid Grid.
 * @param position Position transformed when the position flag is set.
 * @param first_offset First offset, transformed when its flag is set; its fourth component receives the grid's unk3C.
 * @param second_offset Second offset, transformed when its flag is set.
 * @param color_scale Color multiplier used when its flag is set.
 */
extern "C" void func_004A1E90(LibGridEmitter* grid, const LibVector4* position, LibVector4* first_offset,
                              const LibVector4* second_offset, const LibVector4* color_scale)
{
    lib_grid_emit_secondary(grid, position, first_offset, second_offset, color_scale);
}

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

/**
 * @brief Set bit 0 of the model's object kind, unless its mesh has flag 0x1 or 0x2, it's a clone, or it follows
 *        or faces the camera or has draw flag 0x20.
 * @param model Model.
 */
extern "C" void func_004A22C0(LibModelBase* model)
{
    if (model->resource)
    {
        u16 flags = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(model->resource))->unk54;

        if (flags & 0x1)
        {
            return;
        }

        if (flags & 0x2)
        {
            return;
        }
    }

    if (model->original)
    {
        return;
    }

    u16 draw_flags = model->draw_flags;

    if (draw_flags & LIB_DRAW_FLAG_0020)
    {
        return;
    }

    if (draw_flags & LIB_DRAW_FOLLOW_CAMERA)
    {
        return;
    }

    if (draw_flags & (LIB_DRAW_FACE_CAMERA_X | LIB_DRAW_FACE_CAMERA_Y | LIB_DRAW_FACE_CAMERA_Z))
    {
        return;
    }

    model->object_kind |= 1;
}

/**
 * @brief Clear the first of a part record's four marker slots that holds 0x2E, through the uncached segment.
 * @param record Part record.
 */
static inline void lib_clear_part_marker(void* record)
{
    LibMeshPartRecord* uncached = reinterpret_cast<LibMeshPartRecord*>(reinterpret_cast<u32>(record) | UNCACHED_SEGMENT);

    for (s32 i = 0; i < 4; i++)
    {
        if (uncached->unk2c[i] == 0x2E)
        {
            uncached->unk2c[i] = 0;
            break;
        }
    }
}

/**
 * @brief Clear the 0x2E part markers of a model flagged for it, in every payload it draws, and reset its state.
 * @param object Model.
 */
void func_004A2370(void* object)
{
    LibModel* model = static_cast<LibModel*>(object);

    if (!model->unk797_7)
    {
        return;
    }

    if (model->uses_payload_override && !model->children.has_payload())
    {
        return;
    }

    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(model->resource));

    if (mesh->unk56 < 4)
    {
        s32 count = mesh->part_count;

        if (model->unk768 != 0)
        {
            void*** table = reinterpret_cast<void***>(static_cast<u8*>(model->unk768) + count * 12);

            for (s32 i = 0; i < count; i++)
            {
                lib_clear_part_marker(*table[i]);
            }
        }

        if (model->uses_payload_override)
        {
            func_004D5BB0(model->resource);

            for (s32 i = 0; i < count; i++)
            {
                lib_clear_part_marker(func_004D5A90(model->resource));
            }

            s32 set = model->children.select_payload_set(0);
            func_004D5C10(model->resource);

            for (s32 i = 0; i < count; i++)
            {
                lib_clear_part_marker(func_004D5AC0(model->resource));
            }

            reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(model->resource))->unk54 &= ~2;

            if (model->children.select_payload_set(1) >= 0)
            {
                func_004D5C10(model->resource);

                for (s32 i = 0; i < count; i++)
                {
                    lib_clear_part_marker(func_004D5AC0(model->resource));
                }

                reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(model->resource))->unk54 &= ~2;
            }

            model->children.select_payload_set(set);
        }
        else
        {
            func_004D5C10(model->resource);

            for (s32 i = 0; i < count; i++)
            {
                lib_clear_part_marker(func_004D5AC0(model->resource));
            }
        }

        model->resource->unk01 |= 1;
        model->unk780 = 0;
        reinterpret_cast<LibMeshHeader*>(lib_resource_payload(model->resource))->unk54 &= ~2;
        model->unk797_7 = 0;
        model->unk796 = 0;
        model->unk59d_0 = 1;
        model->object_kind &= ~1;
    }
}

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

/**
 * @brief Write 0x2E into the first empty one of a part record's four marker slots, through the uncached segment.
 * @param record Part record.
 */
static inline void lib_set_part_marker(void* record)
{
    LibMeshPartRecord* uncached = reinterpret_cast<LibMeshPartRecord*>(reinterpret_cast<u32>(record) | UNCACHED_SEGMENT);

    for (s32 i = 0; i < 4; i++)
    {
        if (uncached->unk2c[i] == 0)
        {
            uncached->unk2c[i] = 0x2E;
            break;
        }
    }
}

/**
 * @brief Write the 0x2E part markers of a model that doesn't have them yet, in every payload it draws, and flag it.
 * @param object Model.
 * @return One when the markers were written, zero when the model was skipped.
 */
s32 func_004A29D0(void* object)
{
    LibModel* model = static_cast<LibModel*>(object);

    if (model->unk797_7)
    {
        return 0;
    }

    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(model->resource));

    if (mesh->unk54 & 2)
    {
        return 0;
    }

    if (mesh->unk56 >= 4)
    {
        return 0;
    }

    if (model->uses_payload_override && !model->children.has_payload())
    {
        return 0;
    }

    s32 count = mesh->part_count;

    if (model->unk768 != 0)
    {
        void*** table = reinterpret_cast<void***>(static_cast<u8*>(model->unk768) + count * 12);

        for (s32 i = 0; i < count; i++)
        {
            lib_set_part_marker(*table[i]);
        }
    }

    if (model->uses_payload_override)
    {
        func_004D5BB0(model->resource);

        for (s32 i = 0; i < count; i++)
        {
            lib_set_part_marker(func_004D5A90(model->resource));
        }

        s32 set = model->children.select_payload_set(0);
        func_004D5C10(model->resource);

        for (s32 i = 0; i < count; i++)
        {
            lib_set_part_marker(func_004D5AC0(model->resource));
        }

        reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(model->resource))->unk54 |= 2;

        if (model->children.select_payload_set(1) >= 0)
        {
            func_004D5C10(model->resource);

            for (s32 i = 0; i < count; i++)
            {
                lib_set_part_marker(func_004D5AC0(model->resource));
            }

            reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(model->resource))->unk54 |= 2;
        }

        model->children.select_payload_set(set);
    }
    else
    {
        func_004D5C10(model->resource);

        for (s32 i = 0; i < count; i++)
        {
            lib_set_part_marker(func_004D5AC0(model->resource));
        }
    }

    reinterpret_cast<LibMeshHeader*>(lib_resource_payload(model->resource))->unk54 |= 2;
    model->unk797_7 = 1;
    model->unk780 = 0;
    model->unk796 = 0;
    model->unk59d_0 = 1;
    model->object_kind &= ~1;
    return 1;
}

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

/** Image sequence channel description in a mesh. */
struct LibImageSequenceEntry
{
    u8 unk00[8];
    s32 texture;
    u32 unk0c;
};

/** Texture scroll channel description in a mesh. */
struct LibTextureScrollEntry
{
    u8 unk00[8];
    s32 texture;
    u32 unk0c;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 unk20;
    u32 mode;
    u32 unk28;
    float scale;
};

/** Palette blend channel description in a mesh, followed by its colours and palette indices. */
struct LibPaletteBlendEntry
{
    u8 unk00[8];
    s32 texture;
    u32 unk0c;
    float blend;
    s32 entry_count;
    u32 colors_offset;
    u32 size;
};

/** Count-prefixed list of channel descriptions in a mesh. */
struct LibMeshChannelTable
{
    s32 count;
    u8 entries[1];
};

/**
 * @brief Return a model's mesh header.
 * @param model Model.
 * @return The resource's payload as a mesh header, or null when the resource has no data.
 */
static inline LibMeshHeader* lib_model_mesh(LibModel* model)
{
    return reinterpret_cast<LibMeshHeader*>(lib_resource_payload(model->resource));
}

/**
 * @brief Clear the per-texture channel flags and create the mesh's image sequence, texture scroll and palette blend
 *        channels, stopping at the first one that can't be allocated.
 */
void LibModel::create_render_channels()
{
    if (resource == 0)
    {
        return;
    }

    s32 i;

    for (i = 0; i < 0x20; i++)
    {
        unk748[i] = 0;
    }

    LibMeshHeader* mesh = lib_model_mesh(this);

    if (mesh->image_sequences_offset != 0)
    {
        LibMeshChannelTable* table = reinterpret_cast<LibMeshChannelTable*>(reinterpret_cast<u8*>(mesh) + mesh->image_sequences_offset);
        LibImageSequenceEntry* entry = reinterpret_cast<LibImageSequenceEntry*>(table->entries);

        for (s32 i = 0; i < table->count; i++, entry++)
        {
            LibImageSequenceChannel* channel = new (0) LibImageSequenceChannel;

            if (channel == 0)
            {
                return;
            }

            channel->resource = resource;
            channel->unk38 = entry->texture;

            if (channel->load_resource())
            {
                channel->unk3c = entry->unk0c;
                render_channels.append(channel);
            }
            else
            {
                delete channel;
            }
        }
    }

    if (mesh->texture_scrolls_offset != 0)
    {
        LibMeshChannelTable* table = reinterpret_cast<LibMeshChannelTable*>(reinterpret_cast<u8*>(mesh) + mesh->texture_scrolls_offset);
        LibTextureScrollEntry* entry = reinterpret_cast<LibTextureScrollEntry*>(table->entries);

        for (s32 i = 0; i < table->count; i++, entry++)
        {
            LibTextureScrollChannel* channel = new (0) LibTextureScrollChannel;

            if (channel == 0)
            {
                return;
            }

            unk748[entry->texture] = 1;
            channel->unk41 = i + 1;
            channel->unk38 = entry->texture;
            channel->set_rect(entry->unk0c, entry->unk10, entry->unk14, entry->unk18);
            channel->set_point(entry->unk1c, entry->unk20);
            channel->unk3c = entry->unk28;
            channel->mode = entry->mode;
            channel->scale = entry->scale;
            render_channels.append(channel);
        }
    }

    if (mesh->palette_blends_offset != 0)
    {
        LibMeshChannelTable* table = reinterpret_cast<LibMeshChannelTable*>(reinterpret_cast<u8*>(mesh) + mesh->palette_blends_offset);
        LibPaletteBlendEntry* entry = reinterpret_cast<LibPaletteBlendEntry*>(table->entries);

        for (s32 i = 0; i < table->count; i++)
        {
            LibPaletteBlendChannel* channel = new (0) LibPaletteBlendChannel;

            if (channel == 0)
            {
                return;
            }

            unk748[entry->texture] |= 2;
            channel->unk41 = i + 1;
            channel->unk38 = entry->texture;
            channel->unk3c = entry->unk0c;
            channel->resource = resource;
            channel->blend = entry->blend;

            if (channel->load_resource(this))
            {
                const LibVector4* colors = reinterpret_cast<const LibVector4*>(reinterpret_cast<u8*>(entry) + entry->colors_offset);
                s32 count = entry->entry_count;
                channel->entry_count = count;
                const LibVector4* end = colors + count;
                channel->palette_indices = reinterpret_cast<const u8*>(end + count);
                channel->start_colors = colors;
                channel->end_colors = end;
                render_channels.append(channel);
            }
            else
            {
                delete channel;
            }

            entry = reinterpret_cast<LibPaletteBlendEntry*>(reinterpret_cast<u8*>(entry) + entry->size);
        }
    }
}

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

/**
 * @brief Draw a payload override with a packet set, building that set's override packet the first time.
 * @param payload Payload to draw instead of the resource's own.
 * @param set Packet set to draw.
 */
void LibModel::load_payload(void* payload, u8 set)
{
    uses_payload_override = 1;
    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(resource));
    s32 part_count = mesh->part_count;

    if (override_packets[set] == 0)
    {
        s32 size = part_count * LIB_MODEL_PART_QWORDS + LIB_MODEL_PACKET_FIXED_QWORDS;
        delete override_packets[set];

        if (D_001B659C != 0)
        {
            override_packets[set] = resident_heap_allocate(D_001B659C, size * 16);
        }
        else
        {
            override_packets[set] = malloc_guess(size * 16);
        }

        u64* call_tag = &packet_chains[set].tags[1][0];

        if (override_packets[set] == 0)
        {
            return;
        }

        *call_tag = DMA_TAG(0, DMA_TAG_ID_CALL, static_cast<u8*>(override_packets[set]) + LIB_MODEL_PACKET_HEADER_SIZE);
        FlushCache(0);

        if (unk793 < 4)
        {
            unk793 += 2;
        }

        unk795 = 1;
    }

    LibModelBase::load_payload(payload, set);
}

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", get_bounding_sphere__8LibModelFv);

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

/**
 * @brief Finish the model's packet once its DMA is done.
 * @param channel DMA channel; unused.
 */
void LibModel::complete_dma(u32 channel)
{
    lib_finish_packet(this);
}

/** @brief Queue the model's DMA submission on the VIF1 queue. */
void LibModel::render()
{
    resident_dma_queue_push(g_vif1_dma_queue, this);
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

/** Partial view of the model's draw packet at unk220, written through the uncached accelerated segment. */
typedef struct LibModelPacketHeader
{
    u8 unk00[0xA0];
    unsigned __int128 transform[4];
    u8 unke0[0x24];
    s32 unk104;
    u8 unk108[4];
    s32 unk10c;
    u8 unk110[8];
    float unk118;
    s32 unk11c;
    u64 unk120;
    u8 unk128[8];
    u64 test;
    u8 unk138[0x118];
    s32 unk250;
    s32 unk254;
    u8 unk258[0x50];
    s32 unk2a8;
} LibModelPacketHeader;

/**
 * @brief Run the model's per-packet step that build_packet skips after unk797_2 was set.
 * @param model Model.
 * @param context Opaque caller context.
 */
extern "C" void func_004A59D0(LibModel* model, void* context);

/**
 * @brief Count what a mesh with unk54 set adds to the packet.
 * @param model Model.
 * @return The count build_packet passes on to func_004A62D0.
 */
extern "C" s32 func_004A76D0(LibModel* model);

/**
 * @brief Refresh the model's packet header from its flags and the camera's TEST register.
 * @param model Model.
 * @param camera Camera.
 */
extern "C" void func_004A7AC0(LibModel* model, const LibCamera* camera);

/**
 * @brief Copy the mesh's parts into the model's part table.
 * @param model Model whose resource holds the mesh.
 */
extern "C" void func_004A7D50(LibModel* model);

/**
 * @brief Write the packet data for a mesh with unk38 set or with a count from func_004A76D0.
 * @param model Model.
 * @param count Value func_004A76D0 returned for the mesh, or zero.
 */
extern "C" void func_004A62D0(LibModel* model, s32 count);

/**
 * @brief Write the model's parts for one pass.
 * @param model Model.
 * @param matrix Camera the model is drawn with.
 * @param first Nonzero for the pass of a mesh without unk3c.
 * @return Zero when the parts couldn't be written and the packets have to go.
 */
extern "C" s32 func_004A4710(LibModel* model, const void* matrix, s32 first);

/**
 * @brief Build the model's packet: rebuild the packets when the mesh changed, refresh the packet header from the
 *        model's state, then write the parts.
 * @param matrix Camera the model is drawn with.
 * @param context Opaque caller context.
 */
void LibModel::build_packet(const void* matrix, void* context)
{
    if (resource == 0)
    {
        return;
    }

    if (source != 0)
    {
        void* payload_override = resource->payload_override;
        select_payload(payload_override, source->get_packet_set());
    }

    LibModelPacketHeader* header = (LibModelPacketHeader*)((u32)unk220 | EE_UNCACHED_ACCELERATED);
    const unsigned __int128* from = reinterpret_cast<const unsigned __int128*>(&transform);

    if (unk5a1)
    {
        unk5a1 = 0;
    }
    else
    {
        unsigned __int128* to = header->transform;

        *to++ = *from++;
        *to++ = *from++;
        *to++ = *from++;
        *to++ = *from++;
    }

    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(resource));

    // TODO: The game keeps a jump at the end of this arm for something set here and never read; the flag is a guess.
    bool rebuilt = false;

    if (packet == 0)
    {
        build_packets();
        unk791 = 1;

        if (packet == 0)
        {
            unk63 = 0;
            return;
        }

        rebuilt = true;
    }
    else
    {
        s32 parts = mesh->part_count;

        if (unk77c != parts)
        {
            build_packets();

            if (packet == 0)
            {
                unk63 = 0;
                return;
            }
        }
    }

    payload = reinterpret_cast<u8*>(mesh);

    if (!unk797_2)
    {
        func_004A59D0(this, context);
    }

    unk797_2 = 0;

    if (unk59d_0)
    {
        func_004A7AC0(this, static_cast<const LibCamera*>(matrix));
    }

    s32 count = 0;

    if (mesh->unk54 != 0)
    {
        count = func_004A76D0(this);
    }

    u8 fogged = fog_enabled ? (u8)(unk67 ? true : false) : 0;
    header->unk10c = fogged;
    u8 blended = blend_mode ? true : false;
    header->unk2a8 = blended;
    u8 depth_blended = (mesh->unk3d[0] || (draw_flags & 0x800)) ? 0 : (u8)(blend_mode ? true : false);
    header->unk104 = depth_blended;

    if (unk797_1)
    {
        func_004A7D50(this);
        unk797_1 = 0;
    }

    if (mesh->unk38 != 0 || count != 0)
    {
        func_004A62D0(this, count);
    }

    if (draw_bucket_choice)
    {
        if (mesh->unk3c == 0)
        {
            if (unk793 < 4)
            {
                unk793++;
                unk795 = 1;
            }

            if (!func_004A4710(this, matrix, 1))
            {
                delete packet;
                packet = 0;
                delete base_packet;
                base_packet = 0;
                lib_finish_packet(this);
                return;
            }
        }
        else if (blend_mode && !func_004A4710(this, matrix, 0))
        {
            delete packet;
            packet = 0;
            delete base_packet;
            base_packet = 0;
            lib_finish_packet(this);
            return;
        }
    }

    if (unk211 && !blend_mode)
    {
        unk211 = 0;

        if (unk770)
        {
            apply_part_settings();
        }

        delete unk768;
        unk768 = 0;
        delete unk76c;
        unk76c = 0;
    }

    func_slotF0(count, matrix);
    ee_sync();
    unk63 = 1;
}

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

/**
 * @brief Find an image's CLUT and record a hit for a slot; on a miss, claim the next free CLUT for it.
 * @param image Image header whose name and ID identify the CLUT.
 * @param slot Slot whose CLUT is recorded.
 * @param want_address Nonzero to return the CLUT's VRAM address on a hit.
 * @return The CLUT's VRAM word address (always on a miss), or 0 on a hit without want_address or when every CLUT
 *         is in use.
 */
u32 LibTextureCache::func_004A6EA0(const LibImageHeader* image, s32 slot, u8 want_address)
{
    s32 count = clut_count;
    u32 tag = *reinterpret_cast<const u32*>(image->name);
    u32 id = image->id;
    LibTextureClut* table = cluts;
    s32 i;

    for (i = 0; i < count; i++)
    {
        if (id == table[i].id && tag == table[i].tag)
        {
            clut_used[i] = stamp;
            clut_slot_entries[slot] = i;
            return want_address == 0 ? 0 : clut_address + i * 0x100;
        }
    }

    for (i = 0; i < count; i++)
    {
        if (!clut_used[next_clut])
        {
            break;
        }

        next_clut = (next_clut + 1) & (clut_count - 1);
    }

    if (i == clut_count)
    {
        return 0;
    }

    u32 address = clut_address + next_clut * 0x100;
    table[next_clut].id = id;
    table[next_clut].tag = tag;
    table[next_clut].tex0 = (((u64)address & ~0x3F) << 31) | ((u64)image->palette_format << 51);
    clut_used[next_clut] = stamp;
    clut_slot_entries[slot] = next_clut;
    next_clut = (next_clut + 1) & (clut_count - 1);
    return address;
}

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

/**
 * @brief Get the buffer width to record for a texture; with LIB_TEXTURE_FLAG_DOUBLE_WIDTH, 8-bit and 4-bit textures
 * get twice their width.
 * @param request Texture being loaded.
 * @param flags Loader flags.
 * @return Buffer width in pixels.
 */
static inline s32 lib_texture_buffer_width(const LibTextureRequest* request, u16 flags)
{
    s32 width = request->width;

    if (flags & LIB_TEXTURE_FLAG_DOUBLE_WIDTH)
    {
        switch (request->psm)
        {
        case GS_PSMT4:
            return width * 2;

        case GS_PSMT8:
            return width * 2;

        case GS_PSMCT16:
        case GS_PSMCT16S:
        default:
            return width;
        }
    }

    return width;
}

/**
 * @brief Load a texture the cache missed: claim a free block large enough for it, releasing unstamped textures from
 * the least recently used end when there is none, and record the texture in it.
 * @param cache Cache to add the texture to.
 * @param request Texture to load.
 * @param tag Request tag.
 * @param id Texture ID.
 * @param slot Slot whose last hit is recorded.
 * @param flags Loader flags (LIB_TEXTURE_FLAG_*).
 * @param user Object that owns the texture, or null.
 * @return VRAM word address of the texture, 0 when no spare block record is left, or 1 when no block is large
 *         enough.
 */
extern "C" u32 func_004A7100(LibTextureCache* cache, LibTextureRequest* request, u32 tag, u32 id, s32 slot, s32 flags,
                             LibTextureUser* user)
{
    u32 index;
    s32 need;

    if (request->psm == GS_PSMCT24)
    {
        need = (request->size / 3 + GS_VRAM_PAGE_WORDS - 1) & ~(GS_VRAM_PAGE_WORDS - 1);
    }
    else
    {
        need = (request->size / 4 + GS_VRAM_PAGE_WORDS - 1) & ~(GS_VRAM_PAGE_WORDS - 1);
    }

    u32 found = 0;

    for (index = cache->blocks[0].next_block; index != 0; index = cache->blocks[index].next_block)
    {
        if (cache->blocks[index].state == LIB_TEXTURE_BLOCK_FREE && cache->blocks[index].size >= need)
        {
            found = index;
            break;
        }
    }

    if (found == 0)
    {
        for (index = cache->previous[0]; index != 0;)
        {
            u32 older = cache->previous[index];

            if (cache->blocks[index].stamp == 0)
            {
                s32 size = cache->blocks[index].size;
                cache->previous[cache->next[index]] = older;
                cache->next[cache->previous[index]] = cache->next[index];
                u32 before = cache->blocks[index].previous_block;
                u32 after = cache->blocks[index].next_block;

                if (cache->blocks[before].state == LIB_TEXTURE_BLOCK_FREE)
                {
                    cache->blocks[index].state = LIB_TEXTURE_BLOCK_UNUSED;
                    size += cache->blocks[before].size;
                    cache->blocks[before].size = size;
                    cache->blocks[after].previous_block = before;
                    cache->blocks[before].next_block = after;
                    index = before;
                }

                if (cache->blocks[after].state == LIB_TEXTURE_BLOCK_FREE)
                {
                    cache->blocks[after].state = LIB_TEXTURE_BLOCK_UNUSED;
                    size += cache->blocks[after].size;
                    cache->blocks[index].size = size;
                    cache->blocks[index].next_block = cache->blocks[after].next_block;
                    cache->blocks[cache->blocks[after].next_block].previous_block = index;
                }

                cache->blocks[index].state = LIB_TEXTURE_BLOCK_FREE;

                if (size >= need)
                {
                    found = index;
                    break;
                }
            }

            index = older;
        }
    }

    u32 address;

    if (found != 0)
    {
        address = cache->blocks[found].address;

        if (cache->blocks[found].size - need != 0)
        {
            s32 tries;

            for (tries = 0; tries < LIB_TEXTURE_CACHE_ENTRY_COUNT; tries++)
            {
                if (cache->blocks[cache->unk04].state == LIB_TEXTURE_BLOCK_UNUSED)
                {
                    break;
                }

                cache->unk04 = (cache->unk04 + 1) & 0xFF;
            }

            if (tries == LIB_TEXTURE_CACHE_ENTRY_COUNT)
            {
                return 0;
            }

            u32 spare = cache->unk04;
            cache->unk04 = (spare + 1) & 0xFF;
            cache->blocks[spare].address = cache->blocks[found].address + need;
            cache->blocks[spare].size = cache->blocks[found].size - need;
            cache->blocks[spare].state = LIB_TEXTURE_BLOCK_FREE;
            cache->blocks[found].size = need;
            cache->blocks[cache->blocks[found].next_block].previous_block = spare;
            cache->blocks[spare].next_block = cache->blocks[found].next_block;
            cache->blocks[found].next_block = spare;
            cache->blocks[spare].previous_block = found;
        }

        cache->blocks[found].state = LIB_TEXTURE_BLOCK_USED;
        cache->blocks[found].stamp = cache->stamp;
        cache->blocks[found].id = id;

        if (user != 0 && user->priority >= LIB_TEXTURE_PRIORITY_RECENT)
        {
            cache->next[found] = cache->next[0];
            cache->previous[found] = 0;
            cache->previous[cache->next[0]] = found;
            cache->next[0] = found;
        }
        else
        {
            cache->next[found] = 0;
            cache->previous[found] = cache->previous[0];
            cache->next[cache->previous[0]] = found;
            cache->previous[0] = found;
        }
    }
    else
    {
        return 1;
    }

    s32 width = lib_texture_buffer_width(request, flags);

    cache->entries[found].tag = tag;
    cache->entries[found].tex0 = (u32)((address / GS_VRAM_BLOCK_WORDS) | ((width & ~(GS_BUFFER_WIDTH_PIXELS - 1)) << 8)
                                       | (request->psm << 20))
        | GS_TEX0_TW(request->width_log2) | GS_TEX0_TH(request->height_log2);
    cache->entries[found].user = user;

    if (user != 0)
    {
        s32 priority = user->priority;
        priority -= 2;
        priority = clamp_low(priority, LIB_TEXTURE_PRIORITY_MIN);
        user->priority = priority;
    }

    cache->slot_entries[slot] = found;
    return address;
}

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
    if (g_hit_test_restart & 1)
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


/**
 * @brief Return the camera's TEST register value with the model's destination alpha test applied.
 * @param model Model.
 * @param camera Camera.
 * @return TEST register value.
 */
static inline u32 lib_model_test_register(const LibModel* model, const LibCamera* camera)
{
    u32 test = camera->test;
    u32 date = model->unk59c != 0 ? 0x4000 : 0;
    u32 datm = model->unk59c == 2 ? 0x8000 : 0;

    return datm | (date | (test & ~0xC000));
}

/**
 * @brief Refresh the model's packet header from its flags and the camera's TEST register.
 * @param model Model.
 * @param camera Camera.
 */
extern "C" void func_004A7AC0(LibModel* model, const LibCamera* camera)
{
    LibModelPacketHeader* header = (LibModelPacketHeader*)((u32)model->unk220 | EE_UNCACHED_ACCELERATED);

    model->unk59d_0 = 0;

    if (model->unk797_0)
    {
        header->unk118 = -1.0f;
        header->unk11c = 1;
    }
    else
    {
        header->unk118 = 1.0f;
        header->unk11c = 0;
    }

    header->unk120 = model->unk59d_1;

    if (model->unk798_2)
    {
        header->test = (lib_model_test_register(model, camera) & ~0x60000) | 0x20000;
    }
    else
    {
        header->test = lib_model_test_register(model, camera);
    }

    if (model->unk638)
    {
        header->unk250 = 0x190;
        header->unk254 = 0x210;
    }
    else
    {
        header->unk250 = 0x220;
        header->unk254 = 0x2D0;
    }
}

/**
 * @brief Number the mesh's parts in their uncached view and copy each into the model's part table.
 * @param model Model whose resource holds the mesh.
 */
extern "C" void func_004A7C20(LibModel* model)
{
    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(model->resource));
    s32* items = reinterpret_cast<s32*>(reinterpret_cast<u8*>(mesh) + mesh->unk38);
    s32 count;
    s32* offsets = items + 1;

    if (mesh->unk38 == 0)
    {
        return;
    }

    count = *items;

    for (s32 i = 0; i < count; i++)
    {
        LibModelPart* source = reinterpret_cast<LibModelPart*>((u32)(reinterpret_cast<u8*>(mesh) + *offsets * 16) | UNCACHED_SEGMENT);
        source->slot = i + 1;
        unsigned __int128* to = reinterpret_cast<unsigned __int128*>(static_cast<LibModelPart*>(model->parts) + i);
        unsigned __int128* from = reinterpret_cast<unsigned __int128*>(source);

        for (s32 j = 0; j < sizeof(LibModelPart) / 16; j++)
        {
            *to++ = *from++;
        }

        offsets++;
    }
}

/**
 * @brief Number the mesh's parts in their uncached view and copy each into the model's part table through its uncached
 * view.
 * @param model Model whose resource holds the mesh.
 */
extern "C" void func_004A7D50(LibModel* model)
{
    LibMeshHeader* mesh = reinterpret_cast<LibMeshHeader*>(lib_resource_payload(model->resource));
    s32* items = reinterpret_cast<s32*>(reinterpret_cast<u8*>(mesh) + mesh->unk38);
    s32 count;
    s32* offsets = items + 1;

    if (mesh->unk38 == 0)
    {
        return;
    }

    count = *items;

    for (s32 i = 0; i < count; i++)
    {
        LibModelPart* source = reinterpret_cast<LibModelPart*>((u32)(reinterpret_cast<u8*>(mesh) + *offsets * 16) | UNCACHED_SEGMENT);
        source->slot = i + 1;
        unsigned __int128* to = reinterpret_cast<unsigned __int128*>((u32)(static_cast<LibModelPart*>(model->parts) + i) | UNCACHED_SEGMENT);
        unsigned __int128* from = reinterpret_cast<unsigned __int128*>(source);

        for (s32 j = 0; j < sizeof(LibModelPart) / 16; j++)
        {
            *to++ = *from++;
        }

        offsets++;
    }
}

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
    resident_sound_update(resident_system_get_sound(resident_get_system()), 1);
    renderer->func_004D44D0(0);
    resident_sync_gs_path(g_input_system, 0, 0);
    resident_sound_wake_stream(resident_system_get_sound(resident_get_system()));
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

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Eleven.
 */
s32 LibClass177A20::get_default_list_kind()
{
    return 11;
}

// TODO: The target's list walk isn't rotated (it jumps to the test first); this only matches with loop
// rotation off.
#pragma push
#pragma opt_rotateloops off

/**
 * @brief Test whether any entry in the list has type flag 0x40.
 * @param list Entry list.
 * @return 1 when one has.
 */
extern "C" s32 func_004A9000(LibClass177A20* list)
{
    LibListSentinel* node = list->sentinel.next;

    while (&list->sentinel != node)
    {
        if (static_cast<LibClass1779F0*>(node)->func_slot14() & 0x40)
        {
            return 1;
        }

        node = node->next;
    }

    return 0;
}

#pragma pop

/**
 * @brief Make the model draw one packet set's payload.
 * @param set Packet set to select; only set zero when the list has a single payload.
 * @return The previously selected set, or -1 when the set isn't available.
 */
s32 LibClass177A20::select_payload_set(s32 set)
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

// TODO: The target's list walk isn't rotated (it jumps to the test first); this only matches with loop
// rotation off.
#pragma push
#pragma opt_rotateloops off

/**
 * @brief Test whether any entry in the list is listed.
 * @return Nonzero when one is.
 */
u8 LibClass177A20::has_listed_entry()
{
    LibListSentinel* node = sentinel.next;

    while (&sentinel != node)
    {
        if (static_cast<LibClass1779F0*>(node)->listed)
        {
            return 1;
        }

        node = node->next;
    }

    return 0;
}

#pragma pop

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

/** @brief Queue the list for deferred destruction. */
void LibClass177A20::destroy()
{
    resident_enqueue_object(g_resident_release_queues, static_cast<LibListObject*>(this));
}

/**
 * @brief Complete the queued DMA transfer; the list does nothing.
 * @param channel DMA channel number.
 */
void LibClass177A20::complete_dma(u32 channel)
{
}

/**
 * @brief Start the queued DMA transfer; the list does nothing.
 * @param channel DMA channel number.
 */
void LibClass177A20::submit_dma(u32 channel)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9240);

/** One vertex change of a morph record: two deltas, the second's w holding the vertex index. */
struct LibMorphRecordEntry
{
    LibVector4 delta;
    float delta2[3];
    s32 vertex;
};

/** Morph record: entry count, byte size to the next record, then the entries. */
struct LibMorphRecord
{
    s32 count;
    u8 unk04[4];
    s32 size;
    u8 unk0c[4];
    LibMorphRecordEntry entries[1];
};

/**
 * @brief Run the morph microprogram on each vertex of the current record, writing the outputs' vectors and values
 *        in place, then step to the next record. The loop overlaps each vertex's load with the previous one's result.
 * @param output Output to update.
 * @param index Bit index; unused.
 */
void LibClass1789C0::func_slot10(LibEntryOutput* output, s32 index)
{
    LibMorphRecord* record = (LibMorphRecord*)cursor;
    LibMorphRecordEntry* entry = record->entries;
    LibVector4* vectors = output->vectors;
    ee_prefetch(entry);
    LibClass173490Entry* values = output->values;
    vu0_morph_load_weights(&clamped_weight);
    s32 vertex = entry->vertex;
    LibVector4* vector = &vectors[vertex];
    LibClass173490Entry* value = &values[vertex];
    vu0_morph_load(vector, value, entry);
    vu0_morph_start_after_load();
    s32 count = ((LibMorphRecord*)cursor)->count;

    if (count == 1)
    {
        vu0_morph_wait();
        vu0_morph_start_after_load();
        vu0_morph_store(vector, value);
        cursor += ((LibMorphRecord*)cursor)->size;
        return;
    }

    entry++;
    vertex = entry->vertex;
    LibVector4* next_vector = &vectors[vertex];
    LibClass173490Entry* next_value = &values[vertex];
    LibVector4* last_vector;
    LibClass173490Entry* last_value;
    s32 i = 1;
    vu0_morph_load(next_vector, next_value, entry);
    i++;
    vu0_morph_start();

    while (i < count)
    {
        entry++;
        last_value = next_value;
        last_vector = next_vector;
        vertex = entry->vertex;
        ee_prefetch_ahead(entry);
        next_vector = &vectors[vertex];
        next_value = &values[vertex];
        vu0_morph_load(next_vector, next_value, entry);
        i++;
        vu0_morph_store(vector, value);
        vector = last_vector;
        value = last_value;
        vu0_morph_start();
    }

    vu0_morph_store(vector, value);

    if (count > 1)
    {
        vu0_morph_start();
        vu0_morph_store(next_vector, next_value);
    }

    cursor += ((LibMorphRecord*)cursor)->size;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", update__14LibClass177A20Fv);

/**
 * @brief Test whether the model's draw packet has been built; the base has none.
 * @return Zero.
 */
s32 LibModelBase::has_packet()
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AA420);

/**
 * @brief Build a packet set's payload in its buffer: align the buffer to 128 bytes, copy the model's resource payload
 *        into it through the uncached segment, then hand it to the model.
 * @param list List whose payload to build.
 * @param set Packet set.
 */
extern "C" void func_004AAFF0(LibClass177A20* list, s32 set)
{
    list->payloads[set] = reinterpret_cast<void*>((reinterpret_cast<u32>(list->payload_buffers[set]) + 127) & ~127);
    const unsigned __int128* source = reinterpret_cast<const unsigned __int128*>(
        list->model->resource != 0 ? func_004D5B50(list->model->resource) : 0);
    unsigned __int128* dest = reinterpret_cast<unsigned __int128*>(reinterpret_cast<u32>(list->payloads[set]) | EE_UNCACHED_ACCELERATED);
    s32 size = func_004D5F50(list->model);
    s32 blocks = size / 128;

    for (s32 i = 0; i < blocks; i++)
    {
        dest[0] = source[0];
        dest[1] = source[1];
        dest[2] = source[2];
        dest[3] = source[3];
        dest[4] = source[4];
        dest[5] = source[5];
        dest[6] = source[6];
        dest[7] = source[7];
        source += 8;
        dest += 8;
    }

    s32 rest = (size - blocks * 128) / 16;

    for (s32 i = 0; i < rest; i++)
    {
        *dest++ = *source++;
    }

    list->model->load_payload(list->payloads[set], set);
    list->model->select_payload(list->payloads[set], set);
}

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
        detach_owner();
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

/**
 * @brief Attach a list to a model: add it to the links, size its two bitsets to the model's parts (clearing the
 *        first), and allocate its five per-part buffers, all or none.
 * @param list List with no model yet.
 * @param model Model to attach.
 * @param links List to add the list to.
 */
extern "C" void func_004AB360(LibClass177A20* list, LibModel* model, LibUpdateList* links)
{
    if (list->model)
    {
        return;
    }

    links->append_node(static_cast<LibListObject*>(list), LibUpdateList::DEFAULT_NODE_KIND);
    list->model = model;
    u32 count = reinterpret_cast<LibMeshHeader*>(lib_resource_active_payload(list->model->resource))->part_count;

    if (!list->unk2c.words_are_borrowed)
    {
        delete[] list->unk2c.words;
    }

    list->unk2c.bit_count = count;
    s32 words = (count + 31) / 32;
    list->unk2c.word_count = words;
    list->unk2c.words = new (0) u32[list->unk2c.word_count];
    list->unk2c.words_are_borrowed = 0;

    s32 word_count = list->unk2c.word_count;

    for (s32 i = 0; i < word_count; i++)
    {
        list->unk2c.words[i] = 0;
    }

    if (!list->unk40.words_are_borrowed)
    {
        delete[] list->unk40.words;
    }

    list->unk40.bit_count = count;
    list->unk40.word_count = words;
    list->unk40.words = new (0) u32[list->unk40.word_count];
    list->unk40.words_are_borrowed = 0;
    delete list->unk5c;
    delete list->unk60;
    delete list->unk68;
    delete list->unk6c;
    delete list->unk70;

    if (D_001B65A8)
    {
        u32 size = (count * 0x10 + 0x10 + count * 2) * 0x10;
        list->unk5c = resident_heap_allocate(D_001B65A8, size);
        list->unk60 = resident_heap_allocate(D_001B65A8, size);
        size = (count + 2) * 0x10;
        list->unk68 = resident_heap_allocate(D_001B65A8, size);
        list->unk6c = resident_heap_allocate(D_001B65A8, size);
        list->unk70 = resident_heap_allocate(D_001B65A8, (count + 1) * 0x58);
    }
    else
    {
        u32 size = (count * 0x10 + 0x10 + count * 2) * 0x10;
        list->unk5c = malloc_guess(size);
        list->unk60 = malloc_guess(size);
        size = (count + 2) * 0x10;
        list->unk68 = malloc_guess(size);
        list->unk6c = malloc_guess(size);
        list->unk70 = malloc_guess((count + 1) * 0x58);
    }

    FlushCache(0);

    if (!list->unk5c || !list->unk60 || !list->unk68 || !list->unk6c || !list->unk70)
    {
        delete list->unk5c;
        delete list->unk60;
        delete list->unk68;
        delete list->unk6c;
        delete list->unk70;
        list->unk5c = 0;
        list->unk60 = 0;
        list->unk68 = 0;
        list->unk6c = 0;
        list->unk70 = 0;
        return;
    }
}

/** @brief Release the model and the payload buffers, then destroy the list. */
LibClass177A20::~LibClass177A20()
{
    if (model != 0)
    {
        release_model();
    }

    resident_queue_allocation_release(g_resident_release_queues, payload_buffers[0]);
    payload_buffers[0] = 0;
    resident_queue_allocation_release(g_resident_release_queues, payload_buffers[1]);
    payload_buffers[1] = 0;
    delete unk70;
    unk70 = 0;
    delete unk5c;
    unk5c = 0;
    delete unk60;
    unk60 = 0;
    delete unk68;
    unk68 = 0;
    delete unk6c;
    unk6c = 0;
}

/** @brief Initialize the list. */
LibClass177A20::LibClass177A20()
{
    model = 0;
    payload_buffers[0] = 0;
    payload_buffers[1] = 0;
    unk58 = 0;
    unk5c = 0;
    unk60 = 0;
    unk68 = 0;
    unk6c = 0;
    unk70 = 0;
    unk84 = 0;
    unk8d_1 = 1;
    unk8c = 0;
    unk8d_0 = D_001B65A0;
    unk89 = 0;
    payload_set = 0;
    unk88 = 0;
    // TODO: The game masks one zero for both of these bits, as if they came from the same variable; I don't
    // know what it was.
    u8 off = 0;
    unk8d_2 = off;
    unk8d_3 = off;
}
