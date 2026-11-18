#ifndef SO3_VU0_H
#define SO3_VU0_H

#include "types.h"

/**
 * @brief Write the squared length of a vector's xyz part to out.x.
 * @param v 16-byte aligned source vector.
 * @param out 16-byte aligned destination.
 * @see njScalor in Code Veronica X (https://github.com/AshfordFamily/recvx-decomp,
 *      src/ps2/veronica/prog/ps2_NaMatrix.c), without its square root.
 */
static inline void vu0_length_squared_xyz(const void* v, void* out)
{
    asm __volatile__(
        "lqc2      $vf24, 0(%0)\n"
        "vmul.xyz  $vf24, $vf24, $vf24\n"
        "vaddw.xyz $vf25, $vf0, $vf0w\n"
        "vadday.x  $ACC, $vf24, $vf24y\n"
        "vmaddz.x  $vf24, $vf25, $vf24z\n"
        "sqc2      $vf24, 0(%1)\n"
        :
        : "r"(v), "r"(out)
        : "memory");
}

/**
 * @brief Write the length of a vector's xyz part to out.x.
 *
 * The source operand has to come first to get the original register order.
 * @param out 16-byte aligned destination.
 * @param v 16-byte aligned source vector.
 * @see njScalor in Code Veronica X (https://github.com/AshfordFamily/recvx-decomp,
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
 * @brief Multiply two vectors component by component.
 * @param out 16-byte aligned destination.
 * @param left 16-byte aligned vector.
 * @param right 16-byte aligned vector.
 * @see Vu0MulVectorXYZW in Fatal Frame (https://github.com/Mikompilation/Himuro,
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
 * @brief Load a 4x4 matrix into vf1-vf4.
 *
 * Callers then run Lib's func_004336E0 once per vector.
 * @param matrix 16-byte aligned matrix.
 * @see shMulMatrix in Silent Hill 2 (https://github.com/dreamingmoths/memory-of-alessa,
 *      SH2_common/sh_vu0.c).
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
 * @brief Load a vector into vf1.
 *
 * This is separate from vu0_extend_bounds_vf1 because the game loads vf1 early
 * and extends the bounds later.
 * @param vector 16-byte aligned vector.
 * @see parappa2 also keeps values in VU registers between asm statements
 *      (https://github.com/parappadev/parappa2, src/prlib/model.cpp).
 */
static inline void vu0_load_vf1(const void* vector)
{
    asm __volatile__("lqc2 $vf1, 0(%0)" : : "r"(vector) : "memory");
}

/**
 * @brief Load a vector into vf15 for vu0_dot_rows_vf15.
 * @param vector 16-byte aligned vector.
 * @see func_004336E0 and func_00433730 in Lib.
 */
static inline void vu0_load_vf15(const void* vector)
{
    asm __volatile__("lqc2 $vf15, 0x0(%0)" : : "r"(vector) : "memory");
}

/**
 * @brief Dot each matrix row in vf1-vf4 with the vector in vf15 and store the four results.
 *
 * vf6 is set to (1, 1, 1) so the multiply-adds sum the products; the result
 * is built in vf5.
 * @param result 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf).
 * @see func_004336E0 and func_00433730 in Lib; about 120 more copies in Lib and the field and battle modules.
 */
static inline void vu0_dot_rows_vf15(void* result)
{
    asm __volatile__("vaddw.xyz   $vf6, $vf0, $vf0w\n"
                     "vmul.xyzw   $vf11, $vf1, $vf15\n"
                     "vmul.xyzw   $vf12, $vf2, $vf15\n"
                     "vmul.xyzw   $vf13, $vf3, $vf15\n"
                     "vmul.xyzw   $vf14, $vf4, $vf15\n"
                     "vadday.x    $ACC, $vf11, $vf11y\n"
                     "vmaddaz.x   $ACC, $vf6, $vf11z\n"
                     "vmaddw.x    $vf5, $vf6, $vf11w\n"
                     "vaddax.y    $ACC, $vf12, $vf12x\n"
                     "vmaddaz.y   $ACC, $vf6, $vf12z\n"
                     "vmaddw.y    $vf5, $vf6, $vf12w\n"
                     "vadday.z    $ACC, $vf13, $vf13y\n"
                     "vmaddax.z   $ACC, $vf6, $vf13x\n"
                     "vmaddw.z    $vf5, $vf6, $vf13w\n"
                     "vadday.w    $ACC, $vf14, $vf14y\n"
                     "vmaddaz.w   $ACC, $vf0, $vf14z\n"
                     "vmaddx.w    $vf5, $vf0, $vf14x\n"
                     "sqc2        $vf5, 0x0(%0)" : : "r"(result) : "memory");
}

/**
 * @brief Dot each row of a matrix with a vector and store the four results.
 *
 * Like vu0_dot_rows_vf15, but the rows are loaded into vf11-vf14 and multiplied in place, and the ones go
 * in vf31.
 * @param matrix 16-byte aligned 4x4 matrix rows.
 * @param vector 16-byte aligned vector.
 * @param result 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf).
 * @see LibClass1748D0::get_bounding_sphere in Lib; about 120 copies in Lib and the field and battle modules.
 */
static inline void vu0_dot_matrix_rows(const void* matrix, const void* vector, void* result)
{
    asm __volatile__("lqc2        $vf15, 0x0(%1)\n"
                     "lqc2        $vf11, 0x0(%0)\n"
                     "lqc2        $vf12, 0x10(%0)\n"
                     "lqc2        $vf13, 0x20(%0)\n"
                     "lqc2        $vf14, 0x30(%0)\n"
                     "vaddw.xyz   $vf31, $vf0, $vf0w\n"
                     "vmul.xyzw   $vf11, $vf11, $vf15\n"
                     "vmul.xyzw   $vf12, $vf12, $vf15\n"
                     "vmul.xyzw   $vf13, $vf13, $vf15\n"
                     "vmul.xyzw   $vf14, $vf14, $vf15\n"
                     "vadday.x    $ACC, $vf11, $vf11y\n"
                     "vmaddaz.x   $ACC, $vf31, $vf11z\n"
                     "vmaddw.x    $vf5, $vf31, $vf11w\n"
                     "vaddax.y    $ACC, $vf12, $vf12x\n"
                     "vmaddaz.y   $ACC, $vf31, $vf12z\n"
                     "vmaddw.y    $vf5, $vf31, $vf12w\n"
                     "vadday.z    $ACC, $vf13, $vf13y\n"
                     "vmaddax.z   $ACC, $vf31, $vf13x\n"
                     "vmaddw.z    $vf5, $vf31, $vf13w\n"
                     "vadday.w    $ACC, $vf14, $vf14y\n"
                     "vmaddaz.w   $ACC, $vf0, $vf14z\n"
                     "vmaddx.w    $vf5, $vf0, $vf14x\n"
                     "sqc2        $vf5, 0x0(%2)" : : "r"(matrix), "r"(vector), "r"(result) : "memory");
}

/**
 * @brief Grow the vf26 (min) and vf27 (max) bounds to include vf1.
 * @see Area 51 builds bounding boxes the same way (https://github.com/ProjectDreamland/area51,
 *      Support/CollisionMgr/PolyCache.cpp).
 */
static inline void vu0_extend_bounds_vf1(void)
{
    asm __volatile__("vmini.xyz $vf26, $vf26, $vf1\n"
                     "vmax.xyz $vf27, $vf27, $vf1");
}

/**
 * @brief Multiply a vector by a 4x4 matrix.
 *
 * All four components are used, so set w to one for a point.
 * @param matrix 16-byte aligned matrix.
 * @param vector 16-byte aligned vector.
 * @param out 16-byte aligned destination.
 * @see sceVu0ApplyMatrix in Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf).
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
 * @brief Load a vector into vf5 and start microprogram 0.
 *
 * TODO: Work out what program 0 does. So far I've only seen it give a screen position.
 *
 * It won't match without the two nops. Sony's manual says they aren't needed,
 * so I think they were just in the original helper.
 * @param vector 16-byte aligned vector.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 */
static inline void vu0_start_microprogram_vf5(const void* vector)
{
    asm __volatile__("lqc2 $vf5, 0(%0)\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0" : : "r"(vector) : "memory");
}

/**
 * @brief Load a vector into vf5 and start the microprogram at 0x670.
 *
 * The program normalizes the quaternion and leaves it in vf6. Lib starts it
 * from 16 places, all with this one nop.
 * @param vector 16-byte aligned vector.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 */
static inline void vu0_start_microprogram_670_vf5(const void* vector)
{
    asm __volatile__("lqc2 $vf5, 0(%0)\n"
                     "nop\n"
                     "vcallms 0x670" : : "r"(vector) : "memory");
}

/**
 * @brief Load a vector into vf5 and start the microprogram at 0x1B0.
 *
 * Lib's level-selection controller runs it on its position right after
 * vu0_start_microprogram_1f0_vf5_vf8 has loaded the camera's view matrix, then
 * reads the view-space position back from vf6. That's the only site I've
 * found, and it has two nops like the 0x1F0 start.
 * @param vector 16-byte aligned vector.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 * @see LibLodController::update in Lib.
 */
static inline void vu0_start_microprogram_1b0_vf5(const void* vector)
{
    asm __volatile__("lqc2 $vf5, 0(%0)\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0x1B0" : : "r"(vector) : "memory");
}

/**
 * @brief Load two matrices into vf1-vf4 and vf5-vf8 and start the microprogram at 0x250.
 *
 * The program leaves the product of the two in vf1-vf4.
 * @param left 16-byte aligned left factor.
 * @param right 16-byte aligned right factor.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 * @see func_004CF7C0 in Lib.
 */
static inline void vu0_start_microprogram_250_vf1_vf8(const void* left, const void* right)
{
    asm __volatile__("lqc2 $vf1, 0x0(%0)\n"
                     "lqc2 $vf2, 0x10(%0)\n"
                     "lqc2 $vf3, 0x20(%0)\n"
                     "lqc2 $vf4, 0x30(%0)\n"
                     "lqc2 $vf5, 0x0(%1)\n"
                     "lqc2 $vf6, 0x10(%1)\n"
                     "lqc2 $vf7, 0x20(%1)\n"
                     "lqc2 $vf8, 0x30(%1)\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0x250" : : "r"(left), "r"(right) : "memory");
}

/**
 * @brief Load a matrix into vf1-vf4 and start the microprogram at 0x2D0.
 *
 * The program leaves its result matrix in vf1-vf4. I haven't worked out what
 * it computes yet; about 50 places in Lib and the field modules run it.
 * @param matrix 16-byte aligned matrix.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 * @see func_004CF580 in Lib; func_0020A9D0 in 1067-00.
 */
static inline void vu0_start_microprogram_2d0_vf1_vf4(const void* matrix)
{
    asm __volatile__("lqc2 $vf1, 0x0(%0)\n"
                     "lqc2 $vf2, 0x10(%0)\n"
                     "lqc2 $vf3, 0x20(%0)\n"
                     "lqc2 $vf4, 0x30(%0)\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0x2D0" : : "r"(matrix) : "memory");
}

/**
 * @brief Load a quaternion into vf5 and start the microprogram at 0x720.
 *
 * The program leaves the quaternion's rotation matrix in vf8-vf11. Every site
 * has this one nop.
 * @param quaternion 16-byte aligned quaternion.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 * @see func_004CE930 in Lib; func_0020A9D0 in 1067-00.
 */
static inline void vu0_start_microprogram_720_vf5(const void* quaternion)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)\n"
                     "nop\n"
                     "vcallms 0x720" : : "r"(quaternion) : "memory");
}

/**
 * @brief Store vf1-vf4 as a matrix.
 * @param matrix 16-byte aligned destination.
 * @see vu0_start_microprogram_250_vf1_vf8 and vu0_start_microprogram_2d0_vf1_vf4.
 */
static inline void vu0_store_vf1_vf4(void* matrix)
{
    asm __volatile__("sqc2 $vf1, 0x0(%0)\n"
                     "sqc2 $vf2, 0x10(%0)\n"
                     "sqc2 $vf3, 0x20(%0)\n"
                     "sqc2 $vf4, 0x30(%0)" : : "r"(matrix) : "memory");
}

/**
 * @brief Store vf8-vf11 as a matrix.
 * @param matrix 16-byte aligned destination.
 * @see vu0_start_microprogram_720_vf5.
 */
static inline void vu0_store_vf8_vf11(void* matrix)
{
    asm __volatile__("sqc2 $vf8, 0x0(%0)\n"
                     "sqc2 $vf9, 0x10(%0)\n"
                     "sqc2 $vf10, 0x20(%0)\n"
                     "sqc2 $vf11, 0x30(%0)" : : "r"(matrix) : "memory");
}

/**
 * @brief Load a matrix into vf5-vf8 and start the microprogram at 0x1F0.
 *
 * Lib loads the camera's view-projection matrix this way before it uses
 * microprogram 0 for screen positions, so I think 0x1F0 keeps the matrix for
 * program 0. Every site has the same two nops.
 * @param matrix 16-byte aligned matrix.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 * @see func_004D3780, func_004D4010, LibClass178F30::update (0x4DB190), func_0044A5F0, func_004D5870, func_004E1670 and
 *      LibCamera::update_projection in Lib, func_0020E9B0, resolve_field_object_display_position and
 *      func_0028BD20 in 1067-00, and func_00230A20 and func_00288830 in 1070-00.
 */
static inline void vu0_start_microprogram_1f0_vf5_vf8(const void* matrix)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)\n"
                     "lqc2 $vf6, 0x10(%0)\n"
                     "lqc2 $vf7, 0x20(%0)\n"
                     "lqc2 $vf8, 0x30(%0)\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0x1F0" : : "r"(matrix) : "memory");
}

/**
 * @brief Run microprogram 0 on a vector in place, from vf1 to vf3.
 *
 * Main calls this once, right after loading boot's microcode, so it's a
 * different program 0 from the one vu0_start_microprogram_vf5 starts.
 * @param vector 16-byte aligned vector.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
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
 * @brief Wait for the running microprogram to finish.
 *
 * The game always reads into t1 here, so I've hard-coded it.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf).
 */
static inline void vu0_wait_microprogram(void)
{
    asm __volatile__("cfc2.i $t1, $vi0" : : : "$t1", "memory");
}

/**
 * @brief Load a matrix's first three rows into vf12-vf14 and start the microprogram at 0x7F0.
 *
 * The program leaves the scale of each row in vf6 (x, y and z). Lib compares it
 * with one to tell an unscaled matrix from a scaled one.
 * @param matrix 16-byte aligned matrix.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6). Lib starts it the same way in
 *      func_004D9E70 and func_0045F2B0, and 1067-00 in func_00222D20.
 */
static inline void vu0_start_microprogram_7f0_rows(const void* matrix)
{
    asm __volatile__("lqc2 $vf12, 0x0(%0)\n"
                     "lqc2 $vf13, 0x10(%0)\n"
                     "lqc2 $vf14, 0x20(%0)\n"
                     "nop\n"
                     "vcallms 0x7F0" : : "r"(matrix) : "memory");
}

/**
 * @brief Turn the row scales the microprogram at 0x7F0 left in vf6 into their distance from one.
 *
 * Read the result with vu0_read_vf6.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf). Lib's func_004D9E70 uses it to tell an
 *      unscaled transform from a scaled one.
 */
static inline void vu0_scale_error_vf6(void)
{
    asm __volatile__("vsubw.xyz  $vf6, $vf6, $vf0w\n"
                     "vabs.xyz   $vf6, $vf6");
}

/**
 * @brief Store vf6, where microprogram 0 leaves its result.
 * @param result 16-byte aligned destination.
 * @see vu0_start_microprogram_vf5.
 */
static inline void vu0_read_vf6(void* result)
{
    asm __volatile__("sqc2 $vf6, 0(%0)" : : "r"(result) : "memory");
}

/**
 * @brief Start decoding a rotation stored as three signed halfwords.
 *
 * Unpacks x, y and z, then starts the square root for w. The same code turns
 * up all over the game with the same registers, so I think it was a shared
 * macro.
 *
 * TODO: The integer half is asm because I couldn't get MWCC to build a 128-bit
 * value in C. I want to look at this again.
 * @param packed Three signed halfwords: x, y and z.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf). Lib has
 *      another copy at 0x42A4E0.
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
 * @brief Finish vu0_decode_short_quaternion and store the rotation.
 * @param out 16-byte aligned destination.
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
