#ifndef SO3_OVERLAYS_0075_00_TEXT_00358440_H
#define SO3_OVERLAYS_0075_00_TEXT_00358440_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035AF70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035AF80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003641F0(void* object);

/**
 * @brief Write the byte at offset 0x12C.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_0035C3F0(void* object, u8 value);

/**
 * @brief Read the word at offset 0x24.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_00366040(void* object);

/**
 * @brief Set the nested object's float value and active flag if present.
 * @param object Object holding the nested pointer.
 */
void func_0035E2D0(u8* object);

#ifdef __cplusplus
}
#endif

#endif
