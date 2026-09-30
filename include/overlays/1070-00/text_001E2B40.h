#ifndef SO3_OVERLAYS_1070_00_TEXT_001E2B40_H
#define SO3_OVERLAYS_1070_00_TEXT_001E2B40_H

#include "types.h"

/** Partial receiver used by the connected byte-dimension and float-pair setters. */
typedef struct FieldDimensionState
{
    u8 unk00[0xF0];
    u8 unkf0;
    u8 unkf1;
    u8 unkf2[10];
    float unkfc;
    float unk100;
    u8 unk104[8];
    u16 unk10c;
} FieldDimensionState;

/** Partial receiver whose state byte is at offset 0xAD. */
typedef struct FieldByteStateAD
{
    u8 unk00[0xAD];
    u8 unkad;
} FieldByteStateAD;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the adjacent floating-point values at offsets 0xFC and 0x100.
 * @param object Receiver to update.
 * @param first Value for offset 0xFC.
 * @param second Value for offset 0x100.
 */
void func_001ED580(FieldDimensionState* object, float first, float second);

/**
 * @brief Store two byte dimensions and their product minus one.
 * @param object Receiver to update.
 * @param first Value whose low byte supplies the first dimension.
 * @param second Value whose low byte supplies the second dimension.
 */
void func_001ED5A0(FieldDimensionState* object, s32 first, s32 second);

/**
 * @brief Set the state byte at offset 0xAD.
 * @param object Receiver to update.
 * @param value Byte to store.
 */
void func_001ED5C0(FieldByteStateAD* object, u8 value);

#ifdef __cplusplus
}
#endif

#endif
