#ifndef SO3_OVERLAYS_1067_00_TEXT_0028E530_H
#define SO3_OVERLAYS_1067_00_TEXT_0028E530_H

#include "types.h"
#include "main/resident_data.h"

typedef struct FieldObject157160 FieldObject157160;

/** Partial receiver with a byte field at offset 0x2F0. */
typedef struct FieldState2F0
{
    u8 unk00[0x2F0];
    u8 unk2F0;
} FieldState2F0;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Apply a packed mode, flags, and three floats to the receiver.
 * @param object Receiver to update.
 * @param index Selected index, or -1.
 * @param mode Mode byte.
 * @param flags Flag byte.
 * @param x First float.
 * @param y Second float.
 * @param z Third float.
 */
void func_0028F5B0(void* object, s32 index, u8 mode, u8 flags, float x, float y, float z);

/**
 * @brief Apply five float values to the receiver.
 * @param object Receiver to update.
 * @param first First float.
 * @param second Second float.
 * @param third Third float.
 * @param fourth Fourth float.
 * @param fifth Fifth float.
 */
void func_0028F710(void* object, float first, float second, float third, float fourth, float fifth);

/**
 * @brief Return whether either of two nested state words is nonzero.
 * @param object Holder of the field context.
 * @return One if either word is nonzero, or zero if the nested state is absent or both words are zero.
 */
s32 func_00291080(const ResidentContextRef* object);

/**
 * @brief Compute a scaled value from the resident word, with a minimum of 0x400.
 * @return Scaled value, or 0x400 when the calculation is smaller.
 */
s32 func_002910D0(void);

/**
 * @brief Return whether the current field context's nested word at offset 0x5D4 is nonzero.
 * @param object Receiver or first argument; unused.
 * @return One if the nested word is nonzero, otherwise zero.
 */
s32 func_00291110(void* object);

/**
 * @brief Set the receiver byte at offset 0x2F0 to one.
 * @param object Receiver containing the byte field.
 */
void func_002911D0(FieldState2F0* object);

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 3.
 */
s32 func_00291410(FieldObject157160* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00291B60(void* object);

#ifdef __cplusplus
}
#endif

#endif
