#ifndef SO3_OVERLAYS_1070_00_TEXT_002649B0_H
#define SO3_OVERLAYS_1070_00_TEXT_002649B0_H

#include "overlays/1070-00/text_00254730.h"

/** Partial receiver containing a scalar interpolation state. */
typedef struct FieldFloatTransition330
{
    u8 unk00[0x330];
    float unk330;
    float unk334;
    float unk338;
    float unk33c;
} FieldFloatTransition330;

/** Partial owner of a keyed float state and its packed key. */
typedef struct FieldKeyedFloatOwner3A0
{
    u8 unk00[0x3A0];
    FieldKeyedFloatState98* unk3a0;
    float unk3a4;
    u8 unk3a8[4];
    u32 unk3ac;
    u8 unk3b0[0xB];
    u8 unk3bb_0_1 : 2;
    u8 unk3bb_2 : 1;
    u8 unk3bb_3_7 : 5;
} FieldKeyedFloatOwner3A0;

/** Partial receiver combining an owner key with two key fragments. */
typedef struct FieldPackedKeySource
{
    u8 unk00[8];
    FieldKeyedFloatOwner3A0* unk08;
    u16* unk0c;
    u8 unk10[4];
    u32 unk14;
} FieldPackedKeySource;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Combine the owner key with the halfword and word key fragments.
 * @param object Receiver containing the owner and key fragments.
 * @return The combined packed key.
 */
u32 func_0026F810(FieldPackedKeySource* object);

/**
 * @brief Clear the owner scalar and reset the attached keyed float state.
 * @param object Owner containing the optional keyed float state.
 */
void func_0026FB50(FieldKeyedFloatOwner3A0* object);

/**
 * @brief Set a scalar immediately or configure its linear transition.
 * @param object Receiver containing the scalar transition state.
 * @param value Target scalar value.
 * @param duration Transition interval; zero updates immediately.
 */
void func_00273EA0(FieldFloatTransition330* object, float value, float duration);

#ifdef __cplusplus
}
#endif

#endif
