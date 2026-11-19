#ifndef SO3_OVERLAYS_LIB_TRIG_VU0_H
#define SO3_OVERLAYS_LIB_TRIG_VU0_H

#include "overlays/lib/text_003E68C0.h"

/**
 * @brief Load the shared angle, reduction constants, and sine coefficients.
 * @param table Aligned 64-byte table.
 */
static inline void vu0_sincos_load(const void* table)
{
    asm __volatile__(
        "lqc2       $vf12, 0x0(%0)\n"
        "lqc2       $vf13, 0x10(%0)\n"
        "lqc2       $vf18, 0x20(%0)\n"
        "lqc2       $vf20, 0x30(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Reduce cosine and sine arguments by pi and store their half-turn quotients.
 * @param quadrants Aligned 16-byte quotient scratch.
 */
static inline void vu0_sincos_reduce(void* quadrants)
{
    asm __volatile__(
        "vsubw.z    $vf13, $vf18, $vf13w\n"
        "vmuly.zw   $vf14, $vf13, $vf12y\n"
        "vaddw.z    $vf31, $vf0, $vf0w\n"
        "vmul.w     $vf31, $vf0, $vf0\n"
        "vftoi0.zw  $vf17, $vf14\n"
        "vmula.zw   $ACC, $vf13, $vf31\n"
        "vitof0.zw  $vf15, $vf17\n"
        "sqc2       $vf17, 0x0(%0)\n"
        "vmsubx.zw  $vf16, $vf15, $vf12x\n"
        :
        : "r"(quadrants)
        : "memory");
}

/**
 * @brief Square the two reduced trigonometric arguments.
 */
static inline void vu0_sincos_square()
{
    asm __volatile__(
        "vmul.zw   $vf15, $vf16, $vf16\n"
        :
        :
        : "memory");
}

/**
 * @brief Evaluate both sine-polynomial lanes with their stored signs.
 * @param table Aligned table containing cosine and sine signs.
 */
static inline void vu0_sincos_evaluate(const void* table)
{
    asm __volatile__(
        "vmulay.zw  $ACC, $vf15, $vf20y\n"
        "vmaddx.zw  $vf14, $vf31, $vf20x\n"
        "lqc2       $vf19, 0x10(%0)\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddy.zw  $vf14, $vf31, $vf13y\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddx.zw  $vf14, $vf31, $vf13x\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddw.zw  $vf14, $vf31, $vf12w\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddz.zw  $vf14, $vf31, $vf12z\n"
        "vmul.zw    $vf16, $vf16, $vf19\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddw.zw  $vf14, $vf31, $vf0w\n"
        "vmul.zw    $vf13, $vf14, $vf16\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Store the cosine and sine lanes together with the retained coefficient lanes.
 * @param output Aligned 16-byte destination.
 */
static inline void vu0_sincos_store(LibVector4* output)
{
    asm __volatile__(
        "sqc2      $vf13, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief Start the degree-nine sine/cosine evaluation and load the sign lanes.
 * @param table Aligned shared coefficient and scratch table.
 * @see vu0_sincos_evaluate_degree9, which does this and vu0_sincos_finish_to_table's arithmetic in one block; lib's
 *      tangent at 0x4CC070 reloads the table address between the two halves.
 */
static inline void vu0_sincos_begin_evaluate_degree9(const void* table)
{
    asm __volatile__(
        "vmulay.zw  $ACC, $vf15, $vf13y\n"
        "vmaddx.zw  $vf14, $vf31, $vf13x\n"
        "lqc2       $vf19, 0x10(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Finish the degree-nine sine/cosine evaluation and store the pair back into the shared table's second
 *        quadword (cosine at 0x18, sine at 0x1C).
 * @param table Aligned shared coefficient and scratch table.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); vu0_sincos_begin_evaluate_degree9.
 */
static inline void vu0_sincos_finish_to_table(void* table)
{
    asm __volatile__(
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddw.zw  $vf14, $vf31, $vf12w\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddz.zw  $vf14, $vf31, $vf12z\n"
        "vmul.zw    $vf16, $vf16, $vf19\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddw.zw  $vf14, $vf31, $vf0w\n"
        "vmul.zw    $vf13, $vf14, $vf16\n"
        "sqc2       $vf13, 0x10(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Load the angle, reduction constants, and degree-nine coefficients.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_sincos_load_degree9(const void* table)
{
    asm __volatile__(
        "lqc2       $vf12, 0x0(%0)\n"
        "lqc2       $vf13, 0x10(%0)\n"
        "lqc2       $vf18, 0x20(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Evaluate the paired degree-nine polynomial with the stored signs.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_sincos_evaluate_degree9(const void* table)
{
    asm __volatile__(
        "vmulay.zw  $ACC, $vf15, $vf13y\n"
        "vmaddx.zw  $vf14, $vf31, $vf13x\n"
        "lqc2       $vf19, 0x10(%0)\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddw.zw  $vf14, $vf31, $vf12w\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddz.zw  $vf14, $vf31, $vf12z\n"
        "vmul.zw    $vf16, $vf16, $vf19\n"
        "vmula.zw   $ACC, $vf14, $vf15\n"
        "vmaddw.zw  $vf14, $vf31, $vf0w\n"
        "vmul.zw    $vf13, $vf14, $vf16\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Load the scalar cosine angle, constants, and degree-thirteen coefficients.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_cosine_load(const void* table)
{
    asm __volatile__(
        "lqc2       $vf12, 0x0(%0)\n"
        "lqc2       $vf13, 0x10(%0)\n"
        "lqc2       $vf18, 0x20(%0)\n"
        "lqc2       $vf17, 0x30(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Reduce the complementary cosine argument and store its half-turn quotient.
 * @param quotient Aligned 16-byte quotient scratch.
 */
static inline void vu0_cosine_reduce(void* quotient)
{
    asm __volatile__(
        "vsub.w     $vf13, $vf18, $vf13\n"
        "vmuly.w    $vf14, $vf13, $vf12y\n"
        "vftoi0.w   $vf17, $vf14\n"
        "vmula.w    $ACC, $vf0, $vf13\n"
        "vitof0.w   $vf15, $vf17\n"
        "sqc2       $vf17, 0x0(%0)\n"
        "vmsubx.w   $vf16, $vf15, $vf12x\n"
        :
        : "r"(quotient)
        : "memory");
}

/**
 * @brief Start the degree-thirteen cosine polynomial and load its sign.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_cosine_begin_evaluate(const void* table)
{
    asm __volatile__(
        "vmulay.w   $ACC, $vf15, $vf17y\n"
        "vmaddx.w   $vf14, $vf0, $vf17x\n"
        "lqc2       $vf19, 0x10(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Finish the scalar sine polynomial and store the result in the table.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_trig_finish_evaluate(const void* table)
{
    asm __volatile__(
        "vmula.w    $ACC, $vf14, $vf15\n"
        "vmaddy.w   $vf14, $vf0, $vf13y\n"
        "vmula.w    $ACC, $vf14, $vf15\n"
        "vmaddx.w   $vf14, $vf0, $vf13x\n"
        "vmula.w    $ACC, $vf14, $vf15\n"
        "vmaddw.w   $vf14, $vf0, $vf12w\n"
        "vmula.w    $ACC, $vf14, $vf15\n"
        "vmaddz.w   $vf14, $vf0, $vf12z\n"
        "vmulz.w    $vf16, $vf16, $vf19z\n"
        "vmula.w    $ACC, $vf14, $vf15\n"
        "vmadd.w    $vf14, $vf0, $vf0\n"
        "vmul.w     $vf13, $vf14, $vf16\n"
        "sqc2       $vf13, 0x10(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Square the reduced scalar argument.
 */
static inline void vu0_trig_square_scalar()
{
    asm __volatile__(
        "vmul.w    $vf15, $vf16, $vf16\n"
        :
        :
        : "memory");
}

/**
 * @brief Load the scalar sine angle, constants, and degree-thirteen coefficients.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_sine_load(const void* table)
{
    asm __volatile__(
        "lqc2       $vf12, 0x0(%0)\n"
        "lqc2       $vf13, 0x10(%0)\n"
        "lqc2       $vf18, 0x30(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Reduce the sine argument and store its half-turn quotient.
 * @param quotient Aligned 16-byte quotient scratch.
 */
static inline void vu0_sine_reduce(void* quotient)
{
    asm __volatile__(
        "vmuly.w    $vf14, $vf13, $vf12y\n"
        "vftoi0.w   $vf17, $vf14\n"
        "vmula.w    $ACC, $vf0, $vf13\n"
        "vitof0.w   $vf15, $vf17\n"
        "sqc2       $vf17, 0x0(%0)\n"
        "vmsubx.w   $vf16, $vf15, $vf12x\n"
        :
        : "r"(quotient)
        : "memory");
}

/**
 * @brief Start the degree-thirteen sine polynomial and load its sign.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_sine_begin_evaluate(const void* table)
{
    asm __volatile__(
        "vmulay.w   $ACC, $vf15, $vf18y\n"
        "vmaddx.w   $vf14, $vf0, $vf18x\n"
        "lqc2       $vf19, 0x10(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Load the scalar angle, reduction constants, and degree-nine sine coefficients.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_sine_load_degree9(const void* table)
{
    asm __volatile__(
        "lqc2       $vf12, 0x0(%0)\n"
        "lqc2       $vf13, 0x10(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Start the scalar degree-nine sine polynomial and load its sign.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_trig_begin_evaluate_degree9(const void* table)
{
    asm __volatile__(
        "vmulay.w   $ACC, $vf15, $vf13y\n"
        "vmaddx.w   $vf14, $vf0, $vf13x\n"
        "lqc2       $vf19, 0x10(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Finish the scalar degree-nine sine polynomial and store its result.
 * @param table Aligned shared coefficient and scratch table.
 */
static inline void vu0_trig_finish_evaluate_degree9(const void* table)
{
    asm __volatile__(
        "vmula.w    $ACC, $vf14, $vf15\n"
        "vmaddw.w   $vf14, $vf0, $vf12w\n"
        "vmula.w    $ACC, $vf14, $vf15\n"
        "vmaddz.w   $vf14, $vf0, $vf12z\n"
        "vmulz.w    $vf16, $vf16, $vf19z\n"
        "vmula.w    $ACC, $vf14, $vf15\n"
        "vmadd.w    $vf14, $vf0, $vf0\n"
        "vmul.w     $vf13, $vf14, $vf16\n"
        "sqc2       $vf13, 0x10(%0)\n"
        :
        : "r"(table)
        : "memory");
}

/**
 * @brief Load three angles into vf20 for the sine microprograms.
 * @param angles Aligned angles in x, y and z.
 * @see Lib's three-angle sines at 0x4CD2C0 (slerp weights) and 0x4CA090.
 */
static inline void vu0_sines_load(const void* angles)
{
    asm __volatile__("lqc2 $vf20, 0x0(%0)\n" : : "r"(angles) : "memory");
}

/**
 * @brief Start the angle reduction microprogram (0x9E8); it leaves the half-turn counts in vf17.
 * @see Lib's three-angle sines at 0x4CD2C0 (slerp weights) and 0x4CA090.
 */
static inline void vu0_sines_reduce()
{
    asm __volatile__("vcallms 0x9E8\n" : : : "memory");
}

/**
 * @brief Wait for the reduction and store its half-turn counts.
 * @param counts Aligned four-word destination.
 * @see Lib's three-angle sines at 0x4CD2C0 (slerp weights) and 0x4CA090.
 */
static inline void vu0_sines_store_counts(void* counts)
{
    asm __volatile__(
        "cfc2.i     $t1, $vi0\n"
        "sqc2       $vf17, 0x0(%0)\n"
        :
        : "r"(counts)
        : "t1", "memory");
}

/**
 * @brief Start the polynomial microprogram (0xA18) on the reduced angles.
 * @see Lib's three-angle sines at 0x4CD2C0 (slerp weights) and 0x4CA090.
 */
static inline void vu0_sines_evaluate()
{
    asm __volatile__("vcallms 0xA18\n" : : : "memory");
}

/**
 * @brief Load the per-angle signs into vf19, wait, and start the microprogram (0xA78) that applies them; the sines
 *        end up in vf13.
 * @param signs Aligned signs (one or minus one) in x, y and z.
 * @see Lib's three-angle sines at 0x4CD2C0 (slerp weights) and 0x4CA090.
 */
static inline void vu0_sines_apply_signs(const void* signs)
{
    asm __volatile__(
        "lqc2       $vf19, 0x0(%0)\n"
        "cfc2.i     $t1, $vi0\n"
        "nop\n"
        "vcallms    0xA78\n"
        :
        : "r"(signs)
        : "t1", "memory");
}

/**
 * @brief Wait for the sine microprograms and store the sines from vf13.
 * @param sines Aligned destination.
 * @see Lib's three-angle sines at 0x4CA090.
 */
static inline void vu0_sines_store(void* sines)
{
    asm __volatile__(
        "cfc2.i     $t1, $vi0\n"
        "sqc2       $vf13, 0x0(%0)\n"
        :
        : "r"(sines)
        : "t1", "memory");
}

#endif
