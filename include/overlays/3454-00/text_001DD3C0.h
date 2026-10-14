#ifndef SO3_OVERLAYS_3454_00_TEXT_001DD3C0_H
#define SO3_OVERLAYS_3454_00_TEXT_001DD3C0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Return the fixed value 0. */
s32 func_001DD400(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001DD4C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EA190(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EC6F0(void* object);

/** Return the word at receiver offset 0xD58. */
u32 func_001E8DD0(const void* object);


/** Store the word at receiver offset 0x70. */
void func_001DE6B0(void* object, u32 value);

/** Set the ready byte and copy one 128-bit value into receiver slot 0. */
void func_001E0CB0(void* object, const unsigned __int128* value);

#ifdef __cplusplus
}
#endif

#endif
