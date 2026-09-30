#ifndef SO3_OVERLAYS_1070_00_TEXT_00223F90_H
#define SO3_OVERLAYS_1070_00_TEXT_00223F90_H

#include "overlays/1070-00/text_00284BF0.h"

/** Partial receiver with a word value and adjacent state byte. */
typedef struct FieldWordByteState30
{
    u8 unk00[0x30];
    u32 unk30;
    u8 unk34;
} FieldWordByteState30;

/** Partial receiver with three state bytes and four float values. */
typedef struct FieldFloatResetState1C
{
    u8 unk00[0x1C];
    u8 unk1c;
    u8 unk1d;
    u8 unk1e;
    u8 unk1f;
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
} FieldFloatResetState1C;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the four vector components.
 * @param vector Destination vector.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 * @return The destination vector.
 */
FieldVector* func_00229DF0(FieldVector* vector, float x, float y, float z, float w);

/**
 * @brief Set the word at offset 0x30 and its adjacent state byte.
 * @param object Receiver to update.
 * @param value Word to store.
 * @param state State byte to store.
 */
void func_002279E0(FieldWordByteState30* object, u32 value, u8 state);

/**
 * @brief Clear three state bytes and four float values.
 * @param object Receiver to reset.
 */
void func_002286C0(FieldFloatResetState1C* object);

#ifdef __cplusplus
}
#endif

#endif
