#ifndef SO3_OVERLAYS_1067_00_TEXT_0025E420_H
#define SO3_OVERLAYS_1067_00_TEXT_0025E420_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Write the output pair for positive or NaN input.
 * @param object Unused interface argument.
 * @param value Input whose float at offset 4 is tested.
 * @param zero_output Receives zero when the test passes; otherwise unchanged.
 * @param small_output Receives 0.05 when the test passes; otherwise unchanged.
 * @return One for positive or NaN input, otherwise zero.
 */
s32 func_0025E840(void* object, const void* value, float* zero_output, float* small_output);


typedef struct FieldObject153CB0 FieldObject153CB0;

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 16.
 */
s32 func_0025E910(FieldObject153CB0* object);


#ifdef __cplusplus
}
#endif

#endif
