#include "include_asm.h"
#include "main/func_0011EE00.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/1067-00/text_00202240.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_0021FB80.h"

struct FieldReset2D4160
{
    u8 unk00[0x3C0];
    s32 unk3C0;
    s32 unk3C4;
    s32 unk3C8;
};

/** Partial receiver with an attached Field object at offset 0x40. */
typedef struct FieldAttached2D47A0
{
    u8 unk00[0x40];
    FieldListObject* unk40;
} FieldAttached2D47A0;

extern u8 D_30EC10[];

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 14.
 */
s32 func_002D3BD0(FieldListObject* object)
{
    return 14;
}

void func_002D3BE0(FieldListObject* object)
{
    lib_object_detach_owner(object);
    resident_enqueue_object(g_resident_release_queues, object);
}

void func_002D3C10(void* object)
{
}

/**
 * @brief Read the stored size for a buffer slot.
 * @param object Receiver containing the buffer slots.
 * @param index Slot index from zero to two; the caller supplies a valid index.
 * @return The stored signed size.
 */
s32 field_get_buffer_slot_size(const FieldBufferSlots* object, s32 index)
{
    return object->buffer_sizes[index];
}

/**
 * @brief Read the aligned pointer for a buffer slot.
 * @param object Receiver containing the buffer slots.
 * @param index Slot index from zero to two; the caller supplies a valid index.
 * @return The stored aligned pointer.
 */
void* field_get_aligned_buffer_slot(const FieldBufferSlots* object, s32 index)
{
    return object->aligned_buffers[index];
}

/**
 * @brief Attach an allocation to an empty buffer slot and store its aligned address.
 * @param object Receiver containing the three buffer slots.
 * @param allocation Allocation to attach.
 * @param size Allocation size; must be positive.
 * @param index Slot index from zero to two.
 * @return One when attached, or zero when rejected.
 */
u8 field_attach_buffer_slot(FieldBufferSlots* object, void* allocation, s32 size, s32 index)
{
    if (index < 0)
    {
        return 0;
    }

    if (index > 2)
    {
        return 0;
    }

    if (size <= 0)
    {
        return 0;
    }

    if (object->buffer_allocations[index] != 0)
    {
        return 0;
    }

    void*& buffer = object->buffer_allocations[index];
    object->buffer_sizes[index] = size;
    buffer = allocation;
    object->aligned_buffers[index] = (void*)(((u32)buffer + 127) & ~0x7F);
    return 1;
}

/**
 * @brief Find an indexed record in the attached resource chain.
 * @param object Receiver containing the resource allocation.
 * @param index Zero-based record index.
 * @return The requested record, or null if unavailable.
 */
FieldResourceRecord* field_find_resource_record(const FieldBufferSlots* object, s32 index)
{
    if (index < 0)
    {
        return 0;
    }

    if (object->block_chain_allocation == 0)
    {
        return 0;
    }

    FieldResourceRecord* record = (FieldResourceRecord*)(((u32)object->block_chain_allocation + 127) & ~0x7F);

    for (s32 position = 0; ; position++)
    {
        if (position == index)
        {
            return record;
        }

        record = record->next_offset == 0 ? 0 : (FieldResourceRecord*)((u8*)record + record->next_offset);

        if (record == 0)
        {
            break;
        }
    }

    return 0;
}

/**
 * @brief Store the chain size, then attach its allocation if the slot is empty.
 * The size is written even when the allocation cannot be attached.
 * @param object Receiver containing the resource allocation.
 * @param allocation Allocation to attach.
 * @param size Allocation size to store.
 * @return One when attached, or zero when rejected.
 */
u8 field_attach_resource_chain(FieldBufferSlots* object, void* allocation, s32 size)
{
    object->block_chain_size = size;

    if (object->block_chain_size <= 0)
    {
        return 0;
    }

    if (object->block_chain_allocation != 0)
    {
        return 0;
    }

    object->block_chain_allocation = allocation;
    return 1;
}

/**
 * @brief Read an allocation pointer aligned upward to 128 bytes.
 * @param object Receiver containing the allocation table.
 * @param raw_index Allocation slot index; only its low eight bits are used.
 * @return The aligned pointer, or null when the normalized index is 64 or greater.
 */
void* field_get_aligned_allocation(const FieldBufferSlots* object, u32 raw_index)
{
    u8 index = (u8)raw_index;

    if (index >= 64)
    {
        return 0;
    }

    return (void*)(((u32)object->allocations[index] + 127) & ~0x7F);
}

/**
 * @brief Queue an attached allocation and clear its slot.
 * @param object Receiver containing the allocation table.
 * @param index Allocation slot index.
 * @return One when the slot was cleared, or zero when it was empty or invalid.
 */
u8 field_queue_allocation_release(FieldBufferSlots* object, u8 index)
{
    if (index < 0)
    {
        return 0;
    }

    if (index >= 64)
    {
        return 0;
    }

    void* allocation = object->allocations[index];

    if (allocation == 0)
    {
        return 0;
    }

    resident_queue_allocation_release(g_resident_release_queues, allocation);
    object->allocations[index] = 0;
    return 1;
}

/**
 * @brief Attach a non-null allocation to an empty allocation slot.
 * @param object Receiver containing the allocation table.
 * @param allocation Allocation to attach.
 * @param index Allocation slot index.
 * @return One when attached, or zero when rejected.
 */
u8 field_attach_allocation(FieldBufferSlots* object, void* allocation, u8 index)
{
    if (allocation == 0)
    {
        return 0;
    }

    if (index < 0)
    {
        return 0;
    }

    if (index >= 64)
    {
        return 0;
    }

    if (object->allocations[index] != 0)
    {
        return 0;
    }

    object->allocations[index] = allocation;
    return 1;
}

/**
 * @brief Return the built-in DTT resource data.
 * @param object Callback receiver; unused.
 * @param raw_index Resource slot index; unused.
 * @return Address of the embedded DTT data.
 */
void* field_get_builtin_resource_data(void* object, u32 raw_index)
{
    return D_30EC10;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D3EC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4030);

/** Partial FieldClass150EB0 with vtable D_15B130 in main data. */
class FieldClass15B130 : public FieldClass150EB0
{
public:
    /** @brief Release through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);
    /** @brief Destroy the object. */
    virtual ~FieldClass15B130();
};

FieldClass15B130::~FieldClass15B130()
{
}

void func_002D4160(FieldReset2D4160* object)
{
    func_00202840(object);
    object->unk3C0 = 0;
    object->unk3C8 = 0;
    object->unk3C4 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4190);

void func_002D47A0(void* receiver)
{
    FieldAttached2D47A0* object = (FieldAttached2D47A0*)receiver;
    if (object->unk40 != 0)
    {
        lib_object_detach_owner(object->unk40);
        object->unk40->func_001DD7B0();
        object->unk40 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D47F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4930);

void func_002D4A30(FieldLinkedAttached2D4A30* list)
{
    FieldLinkedAttached2D4A30* current = list;
    for (;;)
    {
        current = current->next;
        if (list == current)
        {
            break;
        }
        if (current->unk40 == 0)
        {
            continue;
        }
        lib_object_detach_owner(current->unk40);
        current->unk40->func_001DD7B0();
        current->unk40 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4AA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4B30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4CA0);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002D4D40(FieldListObject* object)
{
    return 9;
}

void func_002D4D50(FieldListObject* object)
{
    lib_object_detach_owner(object);
    resident_enqueue_object(g_resident_release_queues, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D4D80);

void func_002D5060(FieldState2D5060* object)
{
    object->unk28 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D5070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D3BD0", func_002D5250);
