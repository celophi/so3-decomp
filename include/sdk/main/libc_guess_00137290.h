#ifndef SO3_SDK_MAIN_LIBC_GUESS_00137290_H
#define SO3_SDK_MAIN_LIBC_GUESS_00137290_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef s32 (*func_001393C8_callback_t)(void*);

/**
 * @brief Process one entry passed to the resident traversal.
 * @param entry Entry to process.
 * @return Callback result.
 */
s32 func_001387A0(void* entry);

/**
 * @brief Traverse an object with a callback.
 * @param object Object to traverse.
 * @param callback Entry callback.
 * @return Traversal result.
 */
s32 func_001393C8(void* object, func_001393C8_callback_t callback);

/**
 * @brief Run the traversal with func_001387A0 as its callback.
 * @param object Object passed to the traversal.
 * @return The traversal result.
 */
s32 func_00138A50(void* object);


/**
 * @brief Return the address of D_0014EC80.
 * @return Pointer to D_0014EC80.
 */
u8* func_001394E8(void);

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
