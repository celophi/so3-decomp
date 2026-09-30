#ifndef SO3_OVERLAYS_1070_00_TEXT_00294DA0_H
#define SO3_OVERLAYS_1070_00_TEXT_00294DA0_H

#include "types.h"

/** Partial receiver with six float values and two control flags. */
typedef struct FieldFloatRangeState20
{
    u8 unk00[0x20];
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    float unk34;
    u8 unk38_0 : 1;
    u8 unk38_1 : 1;
    u8 unk38_2_7 : 6;
} FieldFloatRangeState20;

/** Partial embedded receiver containing two words with unknown meanings. */
typedef struct FieldInitialWordPair
{
    u32 unk00;
    s32 unk04;
} FieldInitialWordPair;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the float range and reset its progress and control flags.
 * @param object Receiver to initialize.
 * @param first Initial float value.
 * @param second Final float value.
 * @param third Float limit for progress.
 */
void func_00296310(FieldFloatRangeState20* object, float first, float second, float third);

/**
 * @brief Initialize the two observed words of an embedded receiver.
 * @param object Embedded receiver to initialize.
 * @return The supplied receiver.
 */
FieldInitialWordPair* func_00297E10(FieldInitialWordPair* object);

#ifdef __cplusplus
}
#endif

#endif
