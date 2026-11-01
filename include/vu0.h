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
 * @brief Multiply a four-component vector by a 4x4 matrix through vf1-vf5.
 *
 * All four components take part, so a point needs w set to one first.
 * @param matrix 16-byte aligned matrix of four rows.
 * @param vector 16-byte aligned source vector.
 * @param out 16-byte aligned destination vector.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf), sceVu0ApplyMatrix
 *      in the libvu0 reference. Lib's vu0_transform_emission_point is the same
 *      sequence with an implicit w of one (overlays/lib/emission_vu0.h).
 */
static inline void vu0_apply_matrix(const void* matrix, const void* vector, void* out)
{
    asm __volatile__(
        "lqc2      $vf5, 0x0(%1)\n"
        "lqc2      $vf1, 0x0(%0)\n"
        "lqc2      $vf2, 0x10(%0)\n"
        "lqc2      $vf3, 0x20(%0)\n"
        "lqc2      $vf4, 0x30(%0)\n"
        "vmulax.xyzw $ACC, $vf1, $vf5x\n"
        "vmadday.xyzw $ACC, $vf2, $vf5y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf5z\n"
        "vmaddw.xyzw $vf5, $vf4, $vf5w\n"
        "sqc2      $vf5, 0x0(%2)\n"
        :
        : "r"(matrix), "r"(vector), "r"(out)
        : "memory");
}

/**
 * @brief Load a vector into vf5 and start VU0 microprogram 0.
 *
 * TODO: Work out what program 0 does; I've only seen it give a screen position.
 *
 * All 58 places that load vf5 and start program 0 have these two nops in
 * between, and I couldn't get a match without them. Sony's manual says
 * VCALLMS can follow the LQC2 straight away, so my guess is they were in the
 * original helper rather than something the hardware needs.
 * @param vector Pointer to a 16-byte aligned vector.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 *      Lib's func_004239C0 uses the same sequence.
 */
static inline void vu0_start_microprogram_vf5(const void* vector)
{
    asm __volatile__("lqc2 $vf5, 0(%0)\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0" : : "r"(vector) : "memory");
}

/**
 * @brief Run VU0 microprogram 0 on a vector in place: load it into vf1, start the program, wait, and store vf3.
 *
 * Main uses this once, right after uploading boot's VU0 microcode, so program 0 here isn't the one
 * vu0_start_microprogram_vf5 starts. The load and the store share one address register, so the original kept the
 * whole sequence in one asm statement; the wait reads into t1 like vu0_wait_microprogram.
 * @param vector Pointer to a 16-byte aligned vector.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6). Main's main().
 */
static inline void vu0_run_microprogram_vf1_vf3(void* vector)
{
    asm __volatile__("lqc2 $vf1, 0(%0)\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0\n"
                     "nop\n"
                     "nop\n"
                     "cfc2.i $t1, $vi0\n"
                     "sqc2 $vf3, 0(%0)" : : "r"(vector) : "$t1", "memory");
}

/**
 * @brief Wait for the running VU0 microprogram to finish.
 *
 * This reads vi0 with the interlocking cfc2.i and throws the value away. All
 * 163 of these waits in the game read into t1, so I've hard-coded it and
 * marked it clobbered.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf).
 */
static inline void vu0_wait_microprogram(void)
{
    asm __volatile__("cfc2.i $t1, $vi0" : : : "$t1", "memory");
}

/**
 * @brief Store vf6.
 *
 * The 43 places that start program 0 and read its result straight away all
 * read vf6.
 * @param result Pointer to a 16-byte aligned destination.
 * @see vu0_start_microprogram_vf5.
 */
static inline void vu0_read_vf6(void* result)
{
    asm __volatile__("sqc2 $vf6, 0(%0)" : : "r"(result) : "memory");
}

/**
 * @brief Start decoding a keyframe rotation stored as three signed halfwords.
 *
 * Packs x, y and z into one 128-bit register, converts them to floats with 15
 * fraction bits, and starts the square root of 1 - x² - y² - z² for w. The
 * same sequence, with the same fixed GPRs t0, t1, t2 and t7, appears in five
 * modules, so I think it's a shared engine macro. The GPR half only builds
 * the qmtc2 operand, and it has to stay asm: MWCC rejects 128-bit shifts
 * ("illegal data size"), so pcpyld can't be written in C. Finish it with
 * vu0_store_decoded_quaternion.
 * @param packed Three signed halfwords: x, y and z.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf), and SO3's
 *      own copies at lib 0x42A4E0, 1067-00 0x2BBE30, 1070-00 0x2DABA0,
 *      3253-00 0x222DA0 and 3454-00 0x21B030.
 */
static inline void vu0_decode_short_quaternion(const void* packed)
{
    asm __volatile__(
        "lh        $8, 0(%0)\n"
        "ori       $15, $0, 0xffff\n"
        "lh        $9, 2(%0)\n"
        "dsll      $15, $15, 16\n"
        "lh        $10, 4(%0)\n"
        "ori       $15, $15, 0xffff\n"
        "dsll32    $9, $9, 0\n"
        "pcpyld    $10, $10, $0\n"
        "and       $8, $8, $15\n"
        "or        $8, $8, $9\n"
        "daddu     $10, $8, $0\n"
        "qmtc2.ni  $10, $vf1\n"
        "vitof15.xyz $vf1, $vf1\n"
        "vmul.xyz  $vf3, $vf1, $vf1\n"
        "vaddw.xyz $vf31, $vf0, $vf0w\n"
        "vaddaw.x  $ACC, $vf0, $vf0w\n"
        "vmsuba.x  $ACC, $vf31, $vf3\n"
        "vmsubay.x $ACC, $vf31, $vf3y\n"
        "vmsubz.x  $vf5, $vf31, $vf3z\n"
        "vsqrt     $Q, $vf5x\n"
        :
        : "r"(packed)
        : "$8", "$9", "$10", "$15");
}

/**
 * @brief Finish vu0_decode_short_quaternion: put the square root in w and store the rotation.
 * @param out 16-byte aligned destination; all four words are written.
 * @see vu0_decode_short_quaternion.
 */
static inline void vu0_store_decoded_quaternion(void* out)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.w   $vf1, $vf0, $Q\n"
        "sqc2      $vf1, 0(%0)\n"
        :
        : "r"(out)
        : "memory");
}

#endif
