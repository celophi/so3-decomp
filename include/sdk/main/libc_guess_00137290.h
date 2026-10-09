#ifndef SO3_SDK_MAIN_LIBC_GUESS_00137290_H
#define SO3_SDK_MAIN_LIBC_GUESS_00137290_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Allocate a buffer from the current resident heap with the requested alignment.
 * @param alignment Buffer alignment in bytes.
 * @param size Requested buffer size in bytes.
 * @return Allocated buffer, or null when allocation fails.
 */
void* func_00139700(u32 alignment, u32 size);

/**
 * @brief Allocate a buffer from the resident heap.
 * @param size Requested buffer size in bytes.
 * @return Allocated buffer, or null when allocation fails.
 */
void* func_00139900(u32 size);

/**
 * @brief Release a resident heap allocation.
 * @param ptr Allocation to release.
 */
void func_00139928(void* ptr);

#ifdef __cplusplus
}
#endif

#endif
