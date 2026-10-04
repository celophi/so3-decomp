#ifndef SO3_OVERLAYS_LIB_TEXT_00429B00_H
#define SO3_OVERLAYS_LIB_TEXT_00429B00_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Multiply a vector by the 4x4 matrix whose rows are already loaded in vf1-vf4.
 *
 * Callers load the rows once with vu0_load_matrix and then transform several
 * vectors. Each result component is the dot product of one row with the vector.
 * @param vector 16-byte aligned source vector.
 * @param result 16-byte aligned destination; may equal vector.
 */
void func_004336E0(const void* vector, void* result);

/**
 * @brief Load a 4x4 matrix into vf1-vf4, then multiply a vector by it as func_004336E0 does.
 * @param matrix 16-byte aligned matrix of four rows.
 * @param vector 16-byte aligned source vector.
 * @param result 16-byte aligned destination.
 */
void func_00433730(const void* matrix, const void* vector, void* result);

/**
 * @brief Allocate an aligned buffer by selecting among temporary allocations.
 * @param size Requested buffer size in bytes.
 * @param alignment Buffer alignment in bytes.
 * @return Selected allocated buffer, or null when allocation fails.
 */
void* func_00433880(u32 size, u32 alignment);

/** @brief Allocate and release temporary blocks before a buffer allocation. */
void func_00433AA0(void);

#ifdef __cplusplus
}
#endif

#endif
