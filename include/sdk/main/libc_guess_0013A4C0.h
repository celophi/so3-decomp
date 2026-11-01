#ifndef SO3_SDK_MAIN_LIBC_GUESS_0013A4C0_H
#define SO3_SDK_MAIN_LIBC_GUESS_0013A4C0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Accept the allocator lock request without locking.
 * @param lock Allocator lock context.
 */
void __malloc_lock_guess(void* lock);
/**
 * @brief Accept the allocator unlock request without unlocking.
 * @param lock Allocator lock context.
 */
void __malloc_unlock_guess(void* lock);

/**
 * @brief Copy bytes between memory ranges.
 * @param destination Destination range.
 * @param source Source range.
 * @param size Number of bytes to copy.
 * @return Destination pointer.
 */
void* memcpy_guess(void* destination, const void* source, u32 size);

/**
 * @brief Fill a destination range with the low byte of a value.
 * @param destination First byte of the destination range.
 * @param value Value whose low byte fills the range.
 * @param size Number of bytes to fill.
 * @return The original destination pointer.
 */
void* memset_guess(void* destination, s32 value, u32 size);

/**
 * @brief Resize an allocation through the default C allocator.
 * @param memory Allocation to resize, or null to allocate a new block.
 * @param size Requested payload size in bytes.
 * @return Resized allocation base, or null when allocation fails.
 */
void* func_0013B858(void* memory, u32 size);

/**
 * @brief Format text into a null-terminated destination buffer.
 * @param destination Buffer receiving the formatted text.
 * @param format Printf-style format string.
 * @return Result returned by the resident formatter.
 */
s32 sprintf_guess(char* destination, const char* format, ...);

/**
 * @brief Print formatted text to standard output (newlib printf).
 * @param format printf format string.
 * @return Number of characters written, or a negative value on error.
 */
s32 printf(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif
