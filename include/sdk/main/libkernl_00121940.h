#ifndef SO3_SDK_MAIN_LIBKERNL_00121940_H
#define SO3_SDK_MAIN_LIBKERNL_00121940_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief EE kernel syscall 100: write back or invalidate the caches (libkernl FlushCache).
 * @param mode Cache operation selector.
 */
void FlushCache(s32 mode);

#ifdef __cplusplus
}
#endif

#endif
