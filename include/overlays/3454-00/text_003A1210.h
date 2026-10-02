#ifndef SO3_OVERLAYS_3454_00_TEXT_003A1210_H
#define SO3_OVERLAYS_3454_00_TEXT_003A1210_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the object pointer.
 * @param object Pointer to return.
 * @return The object pointer.
 */
void* func_003A1960(void* object);

/**
 * @brief Return the object pointer.
 * @param object Pointer to return.
 * @return The object pointer.
 */
void* func_003A1970(void* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the word.
 * @return Nonzero if the word is set.
 */
s32 func_003A4A70(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the word.
 * @return The stored word.
 */
u32 func_003A4FE0(u8* object);

/**
 * @brief Collect two byte flags into a word.
 * @param object Object containing the flags at offsets 0x3C and 0x3D.
 * @return Bit 0 for the first flag and bit 2 for the second.
 */
u32 func_003AA8A0(u8* object);

/**
 * @brief Read a byte value from the optional nested item.
 * @param object Object containing the item pointer at offset 0x920.
 * @return The item value, or zero when absent.
 */
u32 func_003AA980(u8* object);

/**
 * @brief Update the optional nested item.
 * @param object Object containing the item pointer at offset 0x920.
 */
void func_003AA9B0(u8* object);

/**
 * @brief Set the optional nested item float from a scaled value.
 * @param object Object containing the nested item and scale.
 * @param value Value divided by the scale before storing.
 */
void func_003AA9E0(u8* object, float value);

/**
 * @brief Call the handler when the first status bit is clear.
 * @param object Object containing the status halfword at offset 0x6A.
 */
void func_003AAA10(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the word.
 * @return Nonzero if the word is set.
 */
s32 func_003AB950(u8* object);

/**
 * @brief Read a word from the object table at offset 0x220.
 * @param object Object containing the table pointer.
 * @return The stored word.
 */
u32 func_003AF360(void* object);

#ifdef __cplusplus
}
#endif

#endif
