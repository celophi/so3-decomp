#ifndef SO3_OVERLAYS_LIB_LOOK_AT_TRANSFORM_INLINES_H
#define SO3_OVERLAYS_LIB_LOOK_AT_TRANSFORM_INLINES_H

#include "overlays/lib/text_004CD3A0.h"

#ifdef __cplusplus
/** @brief Initialize the transform without a look-at target or roll. */
inline LibLookAtTransform::LibLookAtTransform()
{
    look_at_target = 0;
    roll_angle = 0.0f;
}
#endif

#endif
