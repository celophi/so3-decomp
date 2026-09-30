#ifndef SO3_OVERLAYS_1070_00_TEXT_002D55D0_H
#define SO3_OVERLAYS_1070_00_TEXT_002D55D0_H

#include "types.h"

/** Common reset prefix containing two halfwords and two words at offset 0x10. */
typedef struct FieldResetState10
{
    u8 unk00[0x10];
    s16 unk10;
    s16 unk12;
    u32 unk14;
    u32 unk18;
} FieldResetState10;

/** Partial reset receiver with two halfwords and two words at offset 0x04. */
typedef struct FieldResetState04
{
    u8 unk00[4];
    u16 unk04;
    u16 unk06;
    u32 unk08;
    u32 unk0c;
} FieldResetState04;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear two halfwords and two words beginning at offset 0x10.
 * @param object Receiver to reset.
 */
void func_002D6630(FieldResetState10* object);

/**
 * @brief Clear two halfwords and two words beginning at offset 0x10.
 * @param object Receiver to reset.
 */
void func_002D6690(FieldResetState10* object);

/**
 * @brief Clear two halfwords and two words beginning at offset 0x04.
 * @param object Receiver to reset.
 */
void func_002D66F0(FieldResetState04* object);

#ifdef __cplusplus
}
#endif

#endif
