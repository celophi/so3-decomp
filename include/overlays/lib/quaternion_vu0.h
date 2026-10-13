#ifndef SO3_OVERLAYS_LIB_QUATERNION_VU0_H
#define SO3_OVERLAYS_LIB_QUATERNION_VU0_H

#include "overlays/lib/vector.h"

/**
 * @brief Form first * weights.x - second * weights.y in vf16.
 * @param first First quaternion.
 * @param second Second quaternion.
 * @param weights Aligned weights in x and y; z and w are ignored.
 */
static inline void vu0_quaternion_linear_negative(const FieldVec4B* first, const FieldVec4B* second, const FieldVec4A* weights)
{
    asm __volatile__(
        "lqc2       $vf14, 0x0(%0)\n"
        "lqc2       $vf15, 0x0(%1)\n"
        "lqc2       $vf13, 0x0(%2)\n"
        "vmulay.xyzw $ACC, $vf15, $vf13y\n"
        "vmsubx.xyzw $vf16, $vf14, $vf13x\n"
        :
        : "r"(first), "r"(second), "r"(weights)
        : "memory");
}

/**
 * @brief Form first * weights.x + second * weights.y in vf16.
 * @param first First quaternion.
 * @param second Second quaternion.
 * @param weights Aligned weights in x and y; z and w are ignored.
 */
static inline void vu0_quaternion_linear_positive(const FieldVec4B* first, const FieldVec4B* second, const FieldVec4A* weights)
{
    asm __volatile__(
        "lqc2       $vf14, 0x0(%0)\n"
        "lqc2       $vf15, 0x0(%1)\n"
        "lqc2       $vf13, 0x0(%2)\n"
        "vmulay.xyzw $ACC, $vf15, $vf13y\n"
        "vmaddx.xyzw $vf16, $vf14, $vf13x\n"
        :
        : "r"(first), "r"(second), "r"(weights)
        : "memory");
}

/**
 * @brief Combine opposite-hemisphere quaternions using the weights already in vf13.
 * @param first First quaternion.
 * @param second Second quaternion.
 */
static inline void vu0_quaternion_spherical_negative(const FieldVec4B* first, const FieldVec4B* second)
{
    asm __volatile__(
        "vdiv       $Q, $vf0w, $vf13z\n"
        "lqc2       $vf14, 0x0(%0)\n"
        "lqc2       $vf15, 0x0(%1)\n"
        "vmulay.xyzw $ACC, $vf15, $vf13y\n"
        "vmsubx.xyzw $vf16, $vf14, $vf13x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf16, $vf16, $Q\n"
        :
        : "r"(first), "r"(second)
        : "memory");
}

/**
 * @brief Combine same-hemisphere quaternions using the weights already in vf13.
 * @param first First quaternion.
 * @param second Second quaternion.
 */
static inline void vu0_quaternion_spherical_positive(const FieldVec4B* first, const FieldVec4B* second)
{
    asm __volatile__(
        "vdiv       $Q, $vf0w, $vf13z\n"
        "lqc2       $vf14, 0x0(%0)\n"
        "lqc2       $vf15, 0x0(%1)\n"
        "vmulay.xyzw $ACC, $vf15, $vf13y\n"
        "vmaddx.xyzw $vf16, $vf14, $vf13x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf16, $vf16, $Q\n"
        :
        : "r"(first), "r"(second)
        : "memory");
}


/**
 * @brief Wait for VU0 trigonometry, then combine same-hemisphere quaternions.
 * @param first First quaternion.
 * @param second Second quaternion.
 */
static inline void vu0_quaternion_spherical_positive_wait(const FieldVec4B* first, const FieldVec4B* second)
{
    asm __volatile__(
        "cfc2.i     $zero, $vi0\n"
        "vdiv       $Q, $vf0w, $vf13z\n"
        "lqc2       $vf15, 0x0(%1)\n"
        "lqc2       $vf14, 0x0(%0)\n"
        "vmulay.xyzw $ACC, $vf15, $vf13y\n"
        "vmaddx.xyzw $vf16, $vf14, $vf13x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf16, $vf16, $Q\n"
        :
        : "r"(first), "r"(second)
        : "memory");
}

/**
 * @brief Wait for VU0 trigonometry, then combine opposite-hemisphere quaternions.
 * @param first First quaternion.
 * @param second Second quaternion.
 */
static inline void vu0_quaternion_spherical_negative_wait(const FieldVec4B* first, const FieldVec4B* second)
{
    asm __volatile__(
        "cfc2.i     $zero, $vi0\n"
        "vdiv       $Q, $vf0w, $vf13z\n"
        "lqc2       $vf15, 0x0(%1)\n"
        "lqc2       $vf14, 0x0(%0)\n"
        "vmulay.xyzw $ACC, $vf15, $vf13y\n"
        "vmsubx.xyzw $vf16, $vf14, $vf13x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf16, $vf16, $Q\n"
        :
        : "r"(first), "r"(second)
        : "memory");
}

/**
 * @brief Start the reciprocal square root of the quaternion norm in vf16.
 */
static inline void vu0_quaternion_norm_begin()
{
    asm __volatile__(
        "vmul.xyzw  $vf17, $vf16, $vf16\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vadday.x   $ACC, $vf17, $vf17y\n"
        "vmaddaz.x  $ACC, $vf31, $vf17z\n"
        "vmaddw.x   $vf17, $vf31, $vf17w\n"
        "vrsqrt     $Q, $vf0w, $vf17x\n"
        :
        :
        : "memory");
}

/**
 * @brief Finish normalizing vf16 and store all four quaternion components.
 * @param output Aligned destination quaternion.
 */
static inline void vu0_quaternion_norm_finish(FieldVec4B* output)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyzw $vf16, $vf16, $Q\n"
        "sqc2       $vf16, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief Replace the first quaternion with its Hamilton product with the second.
 * @param first Aligned left-hand quaternion and destination.
 * @param second Aligned right-hand quaternion; may alias first.
 */
static inline void vu0_quaternion_multiply_assign(FieldVec4B* first, const FieldVec4B* second)
{
    asm __volatile__(
        "lqc2       $vf1, 0x0(%0)\n"
        "lqc2       $vf2, 0x0(%1)\n"
        "vmaxw.xyzw $vf5, $vf0, $vf0w\n"
        "vopmula.xyz $ACC, $vf1, $vf2\n"
        "vopmsub.xyz $vf3, $vf2, $vf1\n"
        "vmul.xyzw  $vf4, $vf1, $vf2\n"
        "vmulaw.xyz $ACC, $vf2, $vf1w\n"
        "vmaddaw.xyz $ACC, $vf1, $vf2w\n"
        "vmaddw.xyz $vf1, $vf3, $vf0w\n"
        "vsubaz.w   $ACC, $vf4, $vf4z\n"
        "vmsubay.w  $ACC, $vf5, $vf4y\n"
        "vmsubx.w   $vf1, $vf5, $vf4x\n"
        "sqc2       $vf1, 0x0(%0)\n"
        :
        : "r"(first), "r"(second)
        : "memory");
}

#endif
