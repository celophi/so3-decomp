#ifndef SO3_OVERLAYS_1067_00_TEXT_00272360_H
#define SO3_OVERLAYS_1067_00_TEXT_00272360_H

#include "types.h"
#include "overlays/1067-00/curve.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Compute coefficients for the owner's component curve.
 * @param object Component-curve owner.
 */
void func_002723E0(FieldClass1514F8* object);

/**
 * @brief Append a pair of components to the owner's vector array.
 * @param object Component-curve owner.
 * @param first First component.
 * @param second Second component.
 * @return Index of the appended pair.
 */
s32 func_00272950(FieldClass1514F8* object, float first, float second);

/**
 * @brief Evaluate the curve at a floating-point position.
 * @param curve Curve records and count.
 * @param position Input position.
 * @return Interpolated value, or zero when the curve has fewer than two points.
 */
float func_00272820(FieldClass1514F8* curve, float position);

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
