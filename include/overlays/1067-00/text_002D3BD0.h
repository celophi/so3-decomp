#ifndef SO3_OVERLAYS_1067_00_TEXT_002D3BD0_H
#define SO3_OVERLAYS_1067_00_TEXT_002D3BD0_H

#include "types.h"
#include "overlays/1067-00/text_002CEAF0.h"

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"
#else
typedef struct FieldListObject FieldListObject;
#endif

/** Partial state receiver with a byte flag at offset 0x28. */
typedef struct FieldState2D5060
{
    u8 unk00[0x28];
    u8 unk28;
} FieldState2D5060;

/** Partial list node with a next link and attached Field object. */
typedef struct FieldLinkedAttached2D4A30
{
    u8 unk00[0x08];
    struct FieldLinkedAttached2D4A30* next;
    u8 unk0c[0x34];
    FieldListObject* unk40;
} FieldLinkedAttached2D4A30;

typedef struct FieldReset2D4160 FieldReset2D4160;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Detach the object and queue it for disposal.
 * @param object Callback receiver.
 */
void func_002D3BE0(FieldListObject* object);

/**
 * @brief Clear three receiver fields after releasing attached resources.
 * @param object Receiver to reset.
 */
void func_002D4160(FieldReset2D4160* object);

/**
 * @brief Return the built-in DTT resource data.
 * @param object Callback receiver; unused.
 * @param raw_index Resource slot index; unused.
 * @return Address of the embedded DTT data.
 */
void* field_get_builtin_resource_data(void* object, u32 raw_index);

/**
 * @brief Clear attached objects in a circular list.
 * @param list Sentinel node of the list.
 */
void func_002D4A30(FieldLinkedAttached2D4A30* list);

/**
 * @brief Detach and dispose of the attached object, then clear the pointer.
 * @param object Receiver with the attached object at offset 0x40.
 */
void func_002D47A0(void* object);

/**
 * @brief Detach the object and queue it for disposal.
 * @param object Callback receiver.
 */
void func_002D4D50(FieldListObject* object);

/**
 * @brief Set the byte flag at offset 0x28.
 * @param object State receiver.
 */
void func_002D5060(FieldState2D5060* object);

/**
 * @brief Attach an allocation to an empty buffer slot and store its aligned address.
 * @param object Receiver containing the three buffer slots.
 * @param allocation Allocation to attach.
 * @param size Allocation size; must be positive.
 * @param index Slot index from zero to two.
 * @return One when attached, or zero when rejected.
 */
u8 field_attach_buffer_slot(FieldBufferSlots* object, void* allocation, s32 size, s32 index);

/**
 * @brief Read the stored size for a buffer slot.
 * @param object Receiver containing the buffer slots.
 * @param index Slot index from zero to two; the caller supplies a valid index.
 * @return The stored signed size.
 */
s32 field_get_buffer_slot_size(const FieldBufferSlots* object, s32 index);

/**
 * @brief Read the aligned pointer for a buffer slot.
 * @param object Receiver containing the buffer slots.
 * @param index Slot index from zero to two; the caller supplies a valid index.
 * @return The stored aligned pointer.
 */
void* field_get_aligned_buffer_slot(const FieldBufferSlots* object, s32 index);

/**
 * @brief Find an indexed record in the attached resource chain.
 * @param object Receiver containing the resource allocation.
 * @param index Zero-based record index.
 * @return The requested record, or null if unavailable.
 */
FieldResourceRecord* field_find_resource_record(const FieldBufferSlots* object, s32 index);

/**
 * @brief Store the chain size, then attach its allocation if the slot is empty.
 * The size is written even when the allocation cannot be attached.
 * @param object Receiver containing the resource allocation.
 * @param allocation Allocation to attach.
 * @param size Allocation size to store.
 * @return One when attached, or zero when rejected.
 */
u8 field_attach_resource_chain(FieldBufferSlots* object, void* allocation, s32 size);

/**
 * @brief Read an allocation pointer aligned upward to 128 bytes.
 * @param object Receiver containing the allocation table.
 * @param raw_index Allocation slot index; only its low eight bits are used.
 * @return The aligned pointer, or null when the normalized index is 64 or greater.
 */
void* field_get_aligned_allocation(const FieldBufferSlots* object, u32 raw_index);

/**
 * @brief Queue an attached allocation and clear its slot.
 * @param object Receiver containing the allocation table.
 * @param index Allocation slot index.
 * @return One when the slot was cleared, or zero when it was empty or invalid.
 */
u8 field_queue_allocation_release(FieldBufferSlots* object, u8 index);

/**
 * @brief Attach a non-null allocation to an empty allocation slot.
 * @param object Receiver containing the allocation table.
 * @param allocation Allocation to attach.
 * @param index Allocation slot index.
 * @return One when attached, or zero when rejected.
 */
u8 field_attach_allocation(FieldBufferSlots* object, void* allocation, u8 index);

#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 14.
 */
s32 func_002D3BD0(FieldListObject* object);
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002D4D40(FieldListObject* object);
#endif

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D3C10(void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
    s32 func_002D4B30(s32 resource_index, s32 flag);
}
#endif

#endif
