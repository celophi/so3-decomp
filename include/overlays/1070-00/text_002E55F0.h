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

#ifdef __cplusplus
}
#endif

#endif
