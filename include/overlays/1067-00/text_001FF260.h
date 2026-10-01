#ifndef SO3_OVERLAYS_1067_00_TEXT_001FF260_H
#define SO3_OVERLAYS_1067_00_TEXT_001FF260_H

#include "types.h"
#include "overlays/1067-00/text_001FD860.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear a matching object pointer when the word flag is set.
 * @param object Receiver containing the pointer and flags.
 * @param value Object pointer to compare.
 */
void func_001FF4A0(FieldFlaggedPointerA0* object, void* value);

/**
 * @brief Run the update helper and clear flag 0x10.
 * @param object Receiver to update.
 */
void func_001FF2C0(u8* object);

/**
 * @brief Run the update helper and conditionally copy the saved vector.
 * @param object Receiver to update.
 * @param value Value passed to the update helper.
 * @param flags Update options.
 */
void func_001FF300(u8* object, void* value, u32 flags);

/**
 * @brief Restore saved vectors and select the pending index.
 * @param object Receiver to update.
 */
void func_001FF400(u8* object);

/**
 * @brief Save the vector and active index.
 * @param object Receiver to update.
 */
void func_001FF460(u8* object);

/**
 * @brief Test the receiver through its state helper, flags, and byte.
 * @param object Receiver to test.
 * @return One when either first test passes; otherwise the stored byte.
 */
s32 func_001FF4D0(u8* object);

/**
 * @brief Store a selected object and update its active flag.
 * @param object Receiver to update.
 * @param value Selected object.
 * @param option Option passed to the selection helper.
 */
void func_001FF530(FieldFlaggedPointerA0* object, void* value, u32 option);

/**
 * @brief Set a float target and its change rate.
 * @param object Receiver to update.
 * @param first Target value.
 * @param second Duration used for the rate.
 */
void func_001FF630(u8* object, float first, float second);

/**
 * @brief Store a word at offset 0x3B4.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_00200110(u8* object, u32 value);

/**
 * @brief Test the word at offset 0xC.
 * @param object Receiver to test.
 * @return True when the word is nonzero.
 */
bool func_002006D0(u8* object);

/**
 * @brief Read the word at offset 0x88.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002006E0(u8* object);

#ifdef __cplusplus
}
#endif

#endif
