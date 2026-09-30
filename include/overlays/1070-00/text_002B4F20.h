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

#ifdef __cplusplus
}
#endif

#endif
