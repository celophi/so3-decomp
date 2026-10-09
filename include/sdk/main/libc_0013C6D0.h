#ifndef SO3_SDK_MAIN_LIBC_0013C6D0_H
#define SO3_SDK_MAIN_LIBC_0013C6D0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Compare two null-terminated strings (newlib strcmp).
 * @param left First string.
 * @param right Second string.
 * @return Zero for equal strings, otherwise the differing byte values subtracted.
 */
s32 strcmp(const char* left, const char* right);

#ifdef __cplusplus
}
#endif

#endif
