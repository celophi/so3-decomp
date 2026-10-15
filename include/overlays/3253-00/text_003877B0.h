#ifndef SO3_OVERLAYS_3253_00_TEXT_003877B0_H
#define SO3_OVERLAYS_3253_00_TEXT_003877B0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
void func_0038AA70(void* object);
#endif

/** Return bits 0 and 2 when the byte fields at offsets 0x38 and 0x39 are set. */
u32 func_00393BA0(const u8* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0038E590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0038E6C0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0038E6D0(void* object);

/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_0038E6E0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0038E6F0(void* object);

/**
 * @brief Clear the first 16 bytes of the vector.
 * @param value Vector to clear.
 */
void func_00391120(void* value);

/**
 * @brief Return whether the receiver's word at offset 0x14 is nonzero.
 * @param receiver Object containing the word.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_00391A70(void* receiver);

/**
 * @brief Initialize the record's leading fields and pointer at offset 0x0C.
 * @param arg0 Record to initialize.
 * @return The initialized record.
 */
void* func_00391C10(void* arg0);

/**
 * @brief Return whether the receiver's word at offset 0x14 is nonzero.
 * @param receiver Object containing the word.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_00395840(void* receiver);

/**
 * @brief Initialize the record's leading fields and pointer at offset 0x0C.
 * @param arg0 Record to initialize.
 * @return The initialized record.
 */
void* func_00395AE0(void* arg0);

/** Return the floating-point value 1.0f. */
float func_0038E490(void* object);

/** Return the first pointer argument unchanged. */
void* func_00395920(void* value);

#ifdef __cplusplus
}
#endif

#endif
