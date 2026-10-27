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
 * @see Code Veronica X (CodeWarrior) computes the same xyz length with
 *      vmul/vsqrt/vwaitq/vaddq in njScalor
 *      (https://github.com/AshfordFamily/recvx-decomp,
 *      src/ps2/veronica/prog/ps2_NaMatrix.c).
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
 * @see Fatal Frame's Vu0MulVectorXYZW uses the same vf12/vf13 loads and
 *      vmul.xyzw (https://github.com/Mikompilation/Himuro,
 *      src/graphics/graph3d/libsg.h).
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

/**
 * @brief Load the four rows of a 4x4 matrix into vf1-vf4.
 *
 * The rows stay in place for the Lib transform func_004336E0, which callers
 * then run once per vector.
 * @param matrix 16-byte aligned matrix of four rows.
 * @see Fatal Frame does the same thing with vf4-vf7 (Vu0LoadMatrix in
 *      https://github.com/Mikompilation/Himuro, src/graphics/graph3d/libsg.h).
 * @see Silent Hill 2 loads vf1-vf4 the same way in shMulMatrix
 *      (https://github.com/dreamingmoths/memory-of-alessa, SH2_common/sh_vu0.c).
 */
static inline void vu0_load_matrix(const void* matrix)
{
    asm __volatile__(
        "lqc2      $vf1, 0x0(%0)\n"
        "lqc2      $vf2, 0x10(%0)\n"
        "lqc2      $vf3, 0x20(%0)\n"
        "lqc2      $vf4, 0x30(%0)\n"
        :
        : "r"(matrix)
        : "memory");
}

/**
 * @brief Load a four-component vector into vf1.
 *
 * Kept separate from vu0_extend_bounds_vf1 because the game loads vf1 as
 * soon as the vector is stored and extends the bounds later. The memory
 * clobber keeps that store before this load, since the asm only sees the
 * pointer.
 * @param vector Pointer to a 16-byte aligned vector.
 * @see parappa2 likewise leaves values in fixed VU registers between separate
 *      asm statements (https://github.com/parappadev/parappa2,
 *      src/prlib/model.cpp).
 */
static inline void vu0_load_vf1(const void* vector)
{
    asm __volatile__("lqc2 $vf1, 0(%0)" : : "r"(vector) : "memory");
}

/**
 * @brief Extend the vf26 (min) / vf27 (max) XYZ bounds with vf1.
 *
 * The caller has already set up vf26/vf27. The game also uses this pair with
 * vf4 as the source, so the register is part of the name.
 * @see Area 51 accumulates a bounding box the same way
 *      (https://github.com/ProjectDreamland/area51,
 *      Support/CollisionMgr/PolyCache.cpp).
 */
static inline void vu0_extend_bounds_vf1(void)
{
    asm __volatile__("vmini.xyz $vf26, $vf26, $vf1\n"
                     "vmax.xyz $vf27, $vf27, $vf1");
}

/**
 * @brief Start VU0 microprogram 0 on a vector in vf5.
 *
 * The program projects vf5 through the matrices the caller has set up and
 * leaves the result in vf6. It runs while the caller carries on, so finish
 * with vu0_wait_microprogram, then vu0_read_vf6. The two nops are in every
 * copy of this sequence in the game.
 * @param vector Pointer to a 16-byte aligned vector.
 * @see Sony's EE/VU manual describes VCALLMS starting a VU0 microprogram
 *      straight after an LQC2 (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 *      The game repeats this exact sequence in about 40 functions, such as
 *      lib func_004239C0.
 */
static inline void vu0_start_microprogram_vf5(const void* vector)
{
    asm __volatile__("lqc2 $vf5, 0(%0)\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0" : : "r"(vector) : "memory");
}

/**
 * @brief Wait for the running VU0 microprogram to finish.
 *
 * Reads vi0 with the interlocking cfc2.i and throws the value away. The game
 * always reads it into t1, so t1 is clobbered.
 * @see Sony's EE/VU manual, CFC2 with the I bit
 *      (https://docs.alexrp.com/mips/ee_vu.pdf).
 */
static inline void vu0_wait_microprogram(void)
{
    asm __volatile__("cfc2.i $t1, $vi0" : : : "$t1", "memory");
}

/**
 * @brief Store vf6, where VU0 microprogram 0 leaves its result.
 * @param result Pointer to a 16-byte aligned destination.
 * @see vu0_start_microprogram_vf5.
 */
static inline void vu0_read_vf6(void* result)
{
    asm __volatile__("sqc2 $vf6, 0(%0)" : : "r"(result) : "memory");
}

#endif
