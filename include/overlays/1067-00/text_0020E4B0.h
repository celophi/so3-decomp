#ifndef SO3_OVERLAYS_1067_00_TEXT_0020E4B0_H
#define SO3_OVERLAYS_1067_00_TEXT_0020E4B0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ResidentContextObject38;

/**
 * @brief Configure the Field effect's byte parameters and scalar values.
 * @param state Field context owning the effect.
 * @param flag First parameter, stored as a byte.
 * @param amount Second parameter, stored as a byte.
 * @param value First scalar value.
 * @param duration Second scalar value.
 */
void func_0020F110(struct ResidentContextObject38* state, u32 flag, u32 amount, float value, float duration);

/**
 * @brief Find the script's coordinate record and copy its position and condition words.
 * @param state Script owner.
 * @param offset Byte offset into the script, rounded down to a word boundary.
 * @param position Receives three coordinates converted from signed integers.
 * @param word Receives the record's first word.
 * @param packed Receives its packed condition flags.
 * @return One when a coordinate record is found, otherwise zero.
 */
s32 func_0020EF90(struct ResidentContextObject38* state, u32 offset, float* position, u32* word, u32* packed);

/**
 * @brief Return whether the current field context has a nonzero word at offset 0x50.
 * @param object Receiver or first argument; unused.
 * @return Nonzero if the context word is nonzero.
 */
s32 func_0020E4C0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0020E4E0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0020E4F0(void* object);

#ifdef __cplusplus
}
#endif

#endif
