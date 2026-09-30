#ifndef SO3_OVERLAYS_1070_00_TEXT_002E55F0_H
#define SO3_OVERLAYS_1070_00_TEXT_002E55F0_H

#include "types.h"

/** Partial receiver whose flag byte is at offset 0x70. */
typedef struct FieldByteFlags70
{
    u8 unk00[0x70];
    u8 unk70_0_1 : 2;
    u8 unk70_2 : 1;
    u8 unk70_3_7 : 5;
} FieldByteFlags70;

/** Partial reset prefix with an opaque word and four halfwords. */
typedef struct FieldResetState40
{
    u8 unk00[0x40];
    u32 unk40;
    u8 unk44[4];
    u16 unk48;
    u8 unk4a[2];
    s16 unk4c;
    s16 unk4e;
    s16 unk50;
} FieldResetState40;

/** Partial receiver with three allocations, aligned pointers and sizes. */
typedef struct FieldBufferSlots
{
    u8 unk00[0x11C];
    void* unk11c[3];
    void* unk128[3];
    s32 unk134[3];
} FieldBufferSlots;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set bit two of the flag byte at offset 0x70.
 * @param object Receiver to update.
 */
void func_002F2080(FieldByteFlags70* object);

/**
 * @brief Clear a word and halfword, and set three halfwords to minus one.
 * @param object Receiver to reset.
 */
void func_002F43F0(FieldResetState40* object);

/**
 * @brief Read the size of an indexed buffer slot.
 * @param object Receiver containing the slots.
 * @param index Slot index, from 0 through 2.
 * @return The stored buffer size.
 */
s32 func_002EBA80(const FieldBufferSlots* object, s32 index);

/**
 * @brief Read the aligned pointer of an indexed buffer slot.
 * @param object Receiver containing the slots.
 * @param index Slot index, from 0 through 2.
 * @return The stored aligned buffer pointer.
 */
void* func_002EBA90(const FieldBufferSlots* object, s32 index);

#ifdef __cplusplus
}
#endif

#endif
