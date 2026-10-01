#ifndef SO3_OVERLAYS_1067_00_TEXT_002D3BD0_H
#define SO3_OVERLAYS_1067_00_TEXT_002D3BD0_H

#include "types.h"
#include "overlays/1067-00/text_002CEAF0.h"

#include "overlays/1067-00/text_001DD3C0.h"

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
    FieldClass150070* unk40;
} FieldLinkedAttached2D4A30;

struct FieldReset2D4160;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Detach the object and queue it for disposal.
 * @param object Callback receiver.
 */
void func_002D3BE0(FieldClass150070* object);

/**
 * @brief Clear three receiver fields after releasing attached resources.
 * @param object Receiver to reset.
 */
void func_002D4160(FieldReset2D4160* object);

/**
 * @brief Return the overlay data area at D_30EC10.
 * @param object Callback receiver; unused.
 * @return Address of the overlay data area.
 */
void* func_002D3EB0(void* object);

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
void func_002D4D50(FieldClass150070* object);

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
u8 func_002D3C40(FieldBufferSlots* object, void* allocation, s32 size, s32 index);

/**
 * @brief Read the stored size for a buffer slot.
 * @param object Receiver containing the buffer slots.
 * @param index Slot index.
 * @return The stored signed size.
 */
s32 func_002D3C20(const FieldBufferSlots* object, s32 index);

/**
 * @brief Read the aligned pointer for a buffer slot.
 * @param object Receiver containing the buffer slots.
 * @param index Slot index.
 * @return The stored aligned pointer.
 */
void* func_002D3C30(const FieldBufferSlots* object, s32 index);

/**
 * @brief Find an indexed record in the attached resource chain.
 * @param object Receiver containing the resource allocation.
 * @param index Zero-based record index.
 * @return The requested record, or null if unavailable.
 */
FieldResourceRecord* func_002D3CC0(const FieldBufferSlots* object, s32 index);

/**
 * @brief Store the resource size and attach an allocation if the slot is empty.
 * @param object Receiver containing the resource allocation.
 * @param allocation Allocation to attach.
 * @param size Allocation size to store.
 * @return One when attached, or zero when rejected.
 */
u8 func_002D3D40(FieldBufferSlots* object, void* allocation, s32 size);

/**
 * @brief Read an allocation pointer aligned upward to 128 bytes.
 * @param object Receiver containing the allocation table.
 * @param index Allocation slot index.
 * @return The aligned pointer, or null for an out-of-range index.
 */
void* func_002D3D80(const FieldBufferSlots* object, u8 index);

/**
 * @brief Queue an attached allocation and clear its slot.
 * @param object Receiver containing the allocation table.
 * @param index Allocation slot index.
 * @return One when the slot was cleared, or zero when it was empty or invalid.
 */
u8 func_002D3DC0(FieldBufferSlots* object, u8 index);

/**
 * @brief Attach a non-null allocation to an empty allocation slot.
 * @param object Receiver containing the allocation table.
 * @param allocation Allocation to attach.
 * @param index Allocation slot index.
 * @return One when attached, or zero when rejected.
 */
u8 func_002D3E40(FieldBufferSlots* object, void* allocation, u8 index);

#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 14.
 */
s32 func_002D3BD0(FieldClass150070* object);
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002D4D40(FieldClass150070* object);
#endif

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D3C10(void* object);

#ifdef __cplusplus
}
#endif

#endif
