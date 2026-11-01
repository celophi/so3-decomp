#ifndef SO3_SDK_MAIN_LIBC_GUESS_00131D18_H
#define SO3_SDK_MAIN_LIBC_GUESS_00131D18_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Do nothing. */
void func_00132598(void);

/**
 * @brief Read a signed halfword at object offset 6.
 * @param object Object to read.
 * @return The halfword value.
 */
s16 func_001329D8(const void* object);

/**
 * @brief Read a signed halfword at object offset 4.
 * @param object Object to read.
 * @return The halfword value.
 */
s16 func_001329E0(const void* object);

/** @brief Do nothing. */
void func_00132DA0(void);

/**
 * @brief Run the exit handlers and end the program (newlib exit).
 * @param status Exit status.
 */
void exit(s32 status);

#ifdef __cplusplus
}
#endif

#endif
