#ifndef SO3_OVERLAYS_0002_01_TEXT_004BD360_H
#define SO3_OVERLAYS_0002_01_TEXT_004BD360_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Evaluate a VU0 polynomial approximation of a trigonometric function.
 *
 * Inferred to be the cosine: Field's ring builder uses it for the height of a
 * point measured from the pole.
 * @param angle Angle in radians.
 * @return The approximated value.
 */
float func_004CC3E0(float angle);

/**
 * @brief Evaluate a VU0 polynomial approximation of a trigonometric function.
 *
 * Inferred to be the sine, the partner of func_004CC3E0.
 * @param angle Angle in radians.
 * @return The approximated value.
 */
float func_004CC690(float angle);

#ifdef __cplusplus
}
#endif

#endif
