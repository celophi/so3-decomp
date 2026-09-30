#ifndef SO3_OVERLAYS_1070_00_TEXT_00254730_H
#define SO3_OVERLAYS_1070_00_TEXT_00254730_H

#include "types.h"

/** Partial receiver whose word flags include a mirrored bit in a flag byte. */
typedef struct FieldMirroredFlags
{
    u8 unk00[0x1DC];
    u32 unk1dc;
    u8 unk1e0[0x16];
    u8 unk1f6_0 : 1;
    u8 unk1f6_1 : 1;
    u8 unk1f6_2_7 : 6;
} FieldMirroredFlags;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store the word flags and mirror bit one into the flag byte.
 * @param object Receiver to update.
 * @param value Word flags to store.
 */
void func_0025BB70(FieldMirroredFlags* object, u32 value);

#ifdef __cplusplus
}
#endif

#endif
