#ifndef SO3_OVERLAYS_BOOT_TEXT_001FF0A0_H
#define SO3_OVERLAYS_BOOT_TEXT_001FF0A0_H

#include "types.h"

typedef struct N50Owner94_001FF9E0 N50Owner94_001FF9E0;

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
 * @brief Clear the byte at offset 0x64 and run the cleanup helper.
 * @param object Object containing the byte.
 */
void func_001FF9E0(void* object);

/**
 * @brief Run the cleanup helper on the supplied object.
 * @param object Input object.
 */
void func_4D00B0(void* object);

/**
 * @brief Forward to the cleanup routine for the containing object.
 * @param object Embedded object at offset 0x90.
 */
void func_002050D0(void* object);

/** Set the active flag and forward the optional child pointer. */
void func_001FFA00(N50Owner94_001FF9E0* object);

#ifdef __cplusplus
}
#endif

#endif
