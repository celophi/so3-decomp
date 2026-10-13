#include "include_asm.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/text_004BD360.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_data.h"

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


/** Partial resource controller with an intrusive list and a secondary queued-object interface. */
class LibResourceController : public LibClass178A70, public LibClass171EA0
{
public:
    /** @brief Destroy the resource controller and its interfaces. */
    virtual ~LibResourceController();
    /** @brief Report the resource-controller kind. @return Kind eleven. */
    virtual s32 func_003EEBC0();
    /** @brief Enqueue the controller's secondary interface for resident processing. */
    virtual void func_003EF740();
    /** @brief Process the controller's resource entries. */
    virtual void func_003EEBD0();
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A06B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A06E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A07A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A07E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0820);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A08A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A08B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A08C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A08F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0A70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0C40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0C50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0C60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A0C70);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2230);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A22B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A22C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A29D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A2EF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3560);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A36F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A37C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A39C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3A30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3EC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A3F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A40E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A42A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A43C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A4510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A4550);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A4570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A45A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A4710);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A4ED0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A59C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A59D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A5E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A62D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A6D00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A6D10);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A87F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8810);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A88A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A88B0);

/** @brief Destroy the controller and its inherited transform state. */
LibLodController::~LibLodController()
{
}

/**
 * @brief Return the level-selection controller's kind identifier.
 * @return Kind nine.
 */
s32 LibLodController::func_003EEBC0()
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
    LibClass178EA0::func_004D9F40(source);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8DD0);

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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A8FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9000);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A90E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9120);

/** @brief Enqueue the controller's secondary object interface for resident processing. */
void LibResourceController::func_003EF740()
{
    resident_enqueue_object(D_001B65F4, static_cast<LibClass171EA0*>(this));
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9230);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004A9770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AA410);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AA420);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AAFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB1F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB2D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0049B820", func_004AB700);
