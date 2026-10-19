#include "overlays/lib/palette_blend_channel.h"
#include "include_asm.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/text_004DD440.h"
#include "main/resident_0010A0E0.h"

extern "C" void func_004D00B0(void* object);
extern "C" ResidentReleaseQueues* D_001B65F4;

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
    object->func_003EF770(reinterpret_cast<const LibVector4*>(&position));
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3560);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A36F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A37C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3A30);

/** @brief Destroy the channel; its palette, source colors and indices are borrowed. */
LibPaletteBlendChannel::~LibPaletteBlendChannel()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3EC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A40E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A42A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A43C0);

void func_004A4510(void* receiver)
{
    u8* object = (u8*)receiver;
    *(u8*)(object + 0x64) = 1;
    *(volatile u32*)0x10009020 = 0;
    *(volatile u32*)0x10009030 = *(u32*)(object + 0x710);
    *(volatile u32*)0x1000E010 = 2;
    *(volatile u32*)0x10009000 = 0x105;
}

/** Forward the receiver to func_004D00B0. */
void func_004A4550(void* object)
{
    func_004D00B0(object);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A75F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A76D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7AC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7D50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A7E80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A85B0);

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
    LibTransform::copy_transform_state(source);
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
    lib_lod_set_position(this, lib_lod_add_position_offset(*reinterpret_cast<const FieldVec4B*>(&unk20), offset));
    position_offset_applied = 1;
}

/** @brief Initialize the controller's offset flag, object count, and selected level. */
LibLodController::LibLodController()
{
    unk6c = 6;
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A90E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9120);

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

    resident_enqueue_object(D_001B65F4, receiver);
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
