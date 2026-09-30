#ifndef SO3_OVERLAYS_1067_00_TEXT_002CEAF0_H
#define SO3_OVERLAYS_1067_00_TEXT_002CEAF0_H

#include "types.h"

/** Partial receiver containing 64 allocations and three aligned buffer slots. */
typedef struct FieldBufferSlots
{
    u8 unk00[0x14];
    void* unk14[64];
    void* unk114;
    s32 unk118;
    void* unk11c[3];
    void* unk128[3];
    s32 unk134[3];
} FieldBufferSlots;

/** Partial header of a resource record linked by a byte offset. */
typedef struct FieldResourceRecord
{
    u8 unk00[0xC];
    u32 next_offset;
} FieldResourceRecord;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Run the receiver's virtual cleanup and release its object at offset 0x78.
 * @param object Receiver to clean up.
 */
void func_002DDA70(void* object);

/**
 * @brief Release the receiver's object at offset 0x8C and allocation at offset 0xA0.
 * @param object Receiver to clean up.
 */
void func_002DCD20(void* object);

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
 * @brief Attach a non-null allocation to an empty allocation slot.
 * @param object Receiver containing the allocation table.
 * @param allocation Allocation to attach.
 * @param index Allocation slot index.
 * @return One when attached, or zero when rejected.
 */
u8 func_002D3E40(FieldBufferSlots* object, void* allocation, u8 index);

#ifdef __cplusplus
}
#endif

#endif
