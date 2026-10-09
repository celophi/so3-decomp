#ifndef SO3_MAIN_RESIDENT_0013A4C0_H
#define SO3_MAIN_RESIDENT_0013A4C0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Copy bytes between memory ranges.
 * @param destination Destination range.
 * @param source Source range.
 * @param size Number of bytes to copy.
 * @return Destination pointer.
 */
void* func_0013A4C0(void* destination, const void* source, u32 size);

/**
 * @brief Fill a destination range with the low byte of a value.
 * @param destination First byte of the destination range.
 * @param value Value whose low byte fills the range.
 * @param size Number of bytes to fill.
 * @return The original destination pointer.
 */
void* func_0013A678(void* destination, s32 value, u32 size);

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
 * @brief Format text into a null-terminated destination buffer.
 * @param destination Buffer receiving the formatted text.
 * @param format Printf-style format string.
 * @return Result returned by the resident formatter.
 */
s32 func_0013C4F0(char* destination, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif
