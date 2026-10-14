#ifndef SO3_OVERLAYS_3253_00_TEXT_003A77E0_H
#define SO3_OVERLAYS_3253_00_TEXT_003A77E0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the word at offset 0x210 in the object referenced at offset 0.
 * @param receiver Object containing the reference.
 * @return The referenced object's word.
 */
u32 func_003A9A60(void* receiver);

/**
 * @brief Return the fixed value -1.
 * @param object Receiver or first argument; unused.
 * @return Always -1.
 */
s32 func_003B0D20(void* object);

/**
 * @brief Return whether the receiver's word at offset 0x14 is nonzero.
 * @param receiver Object containing the word.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_003B26B0(void* receiver);

/**
 * @brief Return the receiver's word at offset 0x1C.
 * @param receiver Object containing the word.
 * @return The word.
 */
u32 func_003B2C10(void* receiver);

#ifdef __cplusplus
}
#endif

#endif
