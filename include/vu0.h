#ifndef SO3_VU0_H
#define SO3_VU0_H

#include "types.h"

/*
 * VU0 macro-mode helpers. The game's math code runs these sequences inline
 * with fixed VU registers; the compiler cannot produce COP2 instructions from
 * C. See docs/coding-standards.md, "Exception: VU0 macro-mode helpers".
 */

/**
 * @brief Write the length of a vector's xyz part to the x component of out.
 *
 * Uses vf24 and vf25: the squared components are summed through ACC with a
 * vector of ones, then square-rooted through Q. The source operand comes
 * first, which gives the original register choice (source a3, result a2).
 * @param out 16-byte aligned destination; all four words are written.
 * @param v 16-byte aligned source vector.
 */
static inline void vu0_length_xyz(void* out, const void* v)
{
    asm __volatile__(
        "lqc2      $vf24, 0(%0)\n"
        "vmul.xyz  $vf24, $vf24, $vf24\n"
        "vaddw.xyz $vf25, $vf0, $vf0w\n"
        "vadday.x  $ACC, $vf24, $vf24y\n"
        "vmaddz.x  $vf24, $vf25, $vf24z\n"
        "vsqrt     $Q, $vf24x\n"
        "vwaitq\n"
        "vaddq.x   $vf24, $vf0, $Q\n"
        "sqc2      $vf24, 0(%1)\n"
        :
        : "r"(v), "r"(out)
        : "memory");
}

/**
 * @brief Multiply all four components of two vectors through vf12 and vf13.
 * @param out 16-byte aligned destination; all four words are written.
 * @param left 16-byte aligned first source vector.
 * @param right 16-byte aligned second source vector.
 */
static inline void vu0_multiply_xyzw(void* out, const void* left, const void* right)
{
    asm __volatile__(
        "lqc2      $vf12, 0(%0)\n"
        "lqc2      $vf13, 0(%1)\n"
        "vmul.xyzw $vf12, $vf12, $vf13\n"
        "sqc2      $vf12, 0(%2)\n"
        :
        : "r"(left), "r"(right), "r"(out)
        : "memory");
}

#endif
