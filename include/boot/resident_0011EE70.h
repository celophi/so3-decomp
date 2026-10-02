#ifndef SO3_BOOT_RESIDENT_0011EE70_H
#define SO3_BOOT_RESIDENT_0011EE70_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read the byte at offset 0x25 of an object.
 * @param object Object to read; the field context passes its object at offset 0x24.
 * @return The byte at offset 0x25.
 */
u8 func_0011F9D0(void* object);

#ifdef __cplusplus
}
#endif

#endif
