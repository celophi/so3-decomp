#ifndef SO3_MAIN_RESIDENT_001001E0_H
#define SO3_MAIN_RESIDENT_001001E0_H

#include "types.h"

#ifdef __cplusplus
/**
 * @brief Allocate memory from the current heap, or from the default allocator when none is set.
 * @param size Number of bytes to allocate.
 * @param unused Second argument passed by callers; the resident implementation ignores it.
 * @return The allocated memory.
 */
void* operator new(u32 size, s32 unused);

/**
 * @brief Allocate array memory from the current heap, or from the default allocator when none is set.
 * @param size Number of bytes to allocate.
 * @param unused Second argument passed by callers; the resident implementation ignores it.
 * @return The allocated memory.
 */
void* operator new[](u32 size, s32 unused);

extern "C" {
#endif

/** Store a byte in the global at address 0x001B6420. */
void func_00100A40(u8 value);

/**
 * @brief Allocate memory from the current heap, or from the default allocator when none is set.
 * @param size Number of bytes to allocate.
 * @param unused Second argument passed by callers; ignored by the resident implementation.
 * @return The allocated memory.
 */
void* func_00100AC0(u32 size, s32 unused);

/**
 * @brief Replace the heap used by operator new and operator new[].
 * @param heap Heap to use, or null for the default allocator.
 * @return The previous heap.
 */
void* resident_exchange_allocation_heap(void* heap);

/**
 * @brief Read the heap used by operator new and operator new[].
 * @return The current heap, or null for the default allocator.
 */
void* resident_get_allocation_heap(void);

struct FieldRuntimeRoot;

/**
 * @brief Dispatch the loaded resource buffer through the resident runtime.
 * @param root Resident runtime root.
 * @param destination Loaded resource buffer.
 * @param type Resource type.
 * @param size Resource payload size.
 */
void func_001011B0(struct FieldRuntimeRoot* root, void* destination, s32 type, u32 size);

void func_00100AB0(void* object);

#ifdef __cplusplus
}
#endif

#endif
