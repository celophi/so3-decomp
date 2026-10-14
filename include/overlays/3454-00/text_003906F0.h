#ifndef SO3_OVERLAYS_3454_00_TEXT_003906F0_H
#define SO3_OVERLAYS_3454_00_TEXT_003906F0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Return whether the receiver's word at offset 0x14 is nonzero. */
s32 func_00397FC0(void* receiver);

/** Return whether the receiver's word at offset 0x14 is nonzero. */
s32 func_0039BFF0(void* receiver);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00394D60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00394E90(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00394EA0(void* object);

/**
 * @brief Return the fixed value 5.
 * @param object Receiver or first argument; unused.
 * @return Always 5.
 */
s32 func_00394EB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00394EC0(void* object);

/** Return the floating-point value 1.0f. */
float func_00394C70(void* object);

/** Return the first pointer argument unchanged. */
void* func_0039C0D0(void* value);

#ifdef __cplusplus
}
#endif

#endif
