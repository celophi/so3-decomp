#ifndef SO3_OVERLAYS_1070_00_TEXT_002B4F20_H
#define SO3_OVERLAYS_1070_00_TEXT_002B4F20_H

#include "types.h"

/** Partial receiver containing the adjacent floating-point fields at 0x30 and 0x34. */
typedef struct FieldFloatPair30
{
    u8 unk00[0x30];
    float unk30;
    float unk34;
} FieldFloatPair30;

/** Partial receiver with an active byte and four signed values. */
typedef struct FieldFourValueState48
{
    u8 unk00[0x44];
    u8 unk44;
    u8 unk45[3];
    s32 unk48;
    s32 unk4c;
    s32 unk50;
    s32 unk54;
} FieldFourValueState48;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the adjacent floating-point values at offsets 0x30 and 0x34.
 * @param object Receiver to update.
 * @param first Value for offset 0x30.
 * @param second Value for offset 0x34.
 */
void func_002B6BC0(FieldFloatPair30* object, float first, float second);

/**
 * @brief Set the active byte and four adjacent signed values.
 * @param object Receiver to update.
 * @param first Value for offset 0x48.
 * @param second Value for offset 0x4C.
 * @param third Value for offset 0x50.
 * @param fourth Value for offset 0x54.
 */
void func_002B5CB0(FieldFourValueState48* object, s32 first, s32 second, s32 third, s32 fourth);

#ifdef __cplusplus
}
#endif

#endif
