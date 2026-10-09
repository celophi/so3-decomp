#ifndef SO3_SDK_MAIN_LIBC_0013CA60_H
#define SO3_SDK_MAIN_LIBC_0013CA60_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Count the bytes in a null-terminated string (newlib strlen).
 * @param string The string.
 * @return Its length, not counting the terminator.
 */
u32 strlen(const char* string);

#ifdef __cplusplus
}
#endif

#endif
