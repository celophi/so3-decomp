#ifndef SO3_OVERLAYS_LIB_QUATERNION_INLINES_H
#define SO3_OVERLAYS_LIB_QUATERNION_INLINES_H

#include "overlays/lib/vector.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/text_004BD360.h"
#include "vu0.h"

/**
 * @brief Normalize a quaternion in place.
 * @param quaternion Quaternion to normalize.
 */
static inline void normalize_quaternion(FieldVec4B* quaternion)
{
    vu0_start_microprogram_670_vf5(quaternion);
    vu0_wait_microprogram();
    vu0_read_vf6(quaternion);
}

/**
 * @brief Build the unit quaternion for a rotation about an axis.
 * @param output Receives the quaternion.
 * @param axis_angle Axis in x, y and z, angle in radians in w.
 */
static inline void quaternion_from_axis_angle(FieldVec4B* output, const LibVector4* axis_angle)
{
    LibVector4 pair;

    lib_compute_sine_cosine_pair(&pair, 0.5f * axis_angle->w);
    float sine = pair.w;

    output->w = pair.z;
    output->x = axis_angle->x * sine;
    output->y = axis_angle->y * sine;
    output->z = axis_angle->z * sine;
    vu0_start_microprogram_670_vf5(output);
    vu0_wait_microprogram();
    vu0_read_vf6(output);
}

/**
 * @brief Compose two rotations.
 * @param left Rotation applied second.
 * @param right Rotation applied first.
 * @return Quaternion product left * right.
 */
static inline FieldVec4B multiply_rotations(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B result;
    result.x = left.w * right.x + right.w * left.x + left.y * right.z - left.z * right.y;
    result.y = left.w * right.y + right.w * left.y + left.z * right.x - left.x * right.z;
    result.z = left.w * right.z + right.w * left.z + left.x * right.y - left.y * right.x;
    result.w = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;
    return result;
}

#endif
