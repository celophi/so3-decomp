#ifndef SO3_OVERLAYS_1067_00_TEXT_00272360_H
#define SO3_OVERLAYS_1067_00_TEXT_00272360_H

#include "types.h"

typedef struct FieldObject154EF0 FieldObject154EF0;
typedef struct FieldCurve FieldCurve;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 4.
 */
s32 func_002729C0(FieldObject154EF0* object);

/**
 * @brief Evaluate the curve at a floating-point position.
 * @param curve Curve records and count.
 * @param position Input position.
 * @return Interpolated value, or zero when the curve has fewer than two points.
 */
float func_00272820(FieldCurve* curve, float position);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002729A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002729B0(void* object);

/**
 * @brief Return the fixed value 300.
 * @param object Receiver or first argument; unused.
 * @return Always 300.
 */
s32 func_00272A40(void* object);

/**
 * @brief Return the fixed value -1.
 * @param object Receiver or first argument; unused.
 * @return Always -1.
 */
s32 func_00272D60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00272DD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00272DE0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00272F90(void* object);

#ifdef __cplusplus
}
#endif

#endif
