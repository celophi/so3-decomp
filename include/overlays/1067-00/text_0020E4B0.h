#ifndef SO3_OVERLAYS_1067_00_TEXT_0020E4B0_H
#define SO3_OVERLAYS_1067_00_TEXT_0020E4B0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ResidentContextObject38;

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
