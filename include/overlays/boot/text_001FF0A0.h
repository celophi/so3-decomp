#ifndef SO3_OVERLAYS_BOOT_TEXT_001FF0A0_H
#define SO3_OVERLAYS_BOOT_TEXT_001FF0A0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_002050C0(void* object);

/**
 * @brief Clear the byte at offset 0x60.
 * @param object Object containing the byte.
 */
void func_001FF9D0(void* object);

/**
 * @brief Forward to the cleanup routine for the containing object.
 * @param object Embedded object at offset 0x90.
 */
void func_002050D0(void* object);

#ifdef __cplusplus
}
#endif

#endif
