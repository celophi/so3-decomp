#ifndef SO3_MAIN_RESIDENT_0012F0F8_H
#define SO3_MAIN_RESIDENT_0012F0F8_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00132598(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00132DA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0013A738(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0013A740(void* object);

/**
 * @brief Fill a destination range with the low byte of a value.
 * @param destination First byte of the destination range.
 * @param value Value whose low byte fills the range.
 * @param size Number of bytes to fill.
 * @return The original destination pointer.
 */
void* func_0013A678(void* destination, s32 value, u32 size);

/**
 * @brief Copy bytes between memory ranges.
 * @param destination Destination range.
 * @param source Source range.
 * @param size Number of bytes to copy.
 * @return Destination pointer.
 */
void* func_0013A4C0(void* destination, const void* source, u32 size);

/** @brief Compare two null-terminated strings. @param left First string. @param right Second string. @return Zero for equal strings, otherwise the differing byte values subtracted. */
s32 func_0013C800(const char* left, const char* right);

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
