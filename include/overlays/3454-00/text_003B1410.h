#ifndef SO3_OVERLAYS_3454_00_TEXT_003B1410_H
#define SO3_OVERLAYS_3454_00_TEXT_003B1410_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the fixed value -1.
 * @param object Receiver or first argument; unused.
 * @return Always -1.
 */
s32 func_003B5DF0(void* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the word.
 * @return Nonzero if the word is set.
 */
s32 func_003B7630(u8* object);

/**
 * @brief Test whether the word at offset 0x14 is nonzero.
 * @param object Object containing the word.
 * @return Nonzero if the word is set.
 */
s32 func_003BD7A0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the word.
 * @return The stored word.
 */
u32 func_003B7BE0(u8* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Object containing the word.
 * @return The stored word.
 */
u32 func_003BDC70(u8* object);

/**
 * @brief Read an entry from the optional word table.
 * @param object Object containing the table pointer at offset 0x54.
 * @param index Table entry index.
 * @return The selected word, or zero when the table is absent.
 */
u32 func_003B5C90(u8* object, u8 index);

/**
 * @brief Initialize an indexed entry.
 * @param object Object containing the entry array pointer at offset 0x14.
 * @param index Entry index.
 */
void func_003BD9A0(u8* object, u32 index);

#ifdef __cplusplus
}
#endif

#endif
