#ifndef SO3_OVERLAYS_LIB_BOX_CULL_VU0_H
#define SO3_OVERLAYS_LIB_BOX_CULL_VU0_H

#include "types.h"

/**
 * @brief Step 0 of the box/volume separating-axis test (from `lqc2 $vf6, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @param p1 Aligned operand 1.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step0(const void* p0, const void* p1)
{
    asm __volatile__(
                     "lqc2 $vf6, 0x0(%0)\n"
                     "lqc2 $vf7, 0x0(%1)\n"
                     : : "r"(p0), "r"(p1) : "memory");
}

/**
 * @brief Step 1 of the box/volume separating-axis test (from `lqc2 $vf1, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @param p1 Aligned operand 1.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step1(const void* p0, const void* p1)
{
    asm __volatile__(
                     "lqc2 $vf1, 0x0(%0)\n"
                     "lqc2 $vf2, 0x10(%0)\n"
                     "lqc2 $vf3, 0x20(%0)\n"
                     "lqc2 $vf4, 0x0(%1)\n"
                     "vsub.xyz $vf5, $vf6, $vf7\n"
                     : : "r"(p0), "r"(p1) : "memory");
}

/**
 * @brief Step 2 of the box/volume separating-axis test (from `lqc2 $vf6, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step2(const void* p0)
{
    asm __volatile__(
                     "lqc2 $vf6, 0x0(%0)\n"
                     "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
                     "vsubw.xyzw $vf30, $vf0, $vf0w\n"
                     : : "r"(p0) : "memory");
}

/**
 * @brief Step 3 of the box/volume separating-axis test (from `vmul.xyz $vf29, $vf5, $vf6`).
 * @param p0 Aligned operand 0.
 * @param p1 Aligned operand 1.
 * @param p2 Aligned operand 2.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step3(const void* p0, const void* p1, const void* p2)
{
    asm __volatile__(
                     "vmul.xyz $vf29, $vf5, $vf6\n"
                     "vmul.xyz $vf27, $vf3, $vf6\n"
                     "vmul.xyz $vf28, $vf2, $vf6\n"
                     "vadday.z $ACC, $vf29, $vf29y\n"
                     "vmaddx.z $vf7, $vf31, $vf29x\n"
                     "vmul.xyz $vf29, $vf1, $vf6\n"
                     "vadday.z $ACC, $vf27, $vf27y\n"
                     "vmaddx.z $vf8, $vf31, $vf27x\n"
                     "vaddax.y $ACC, $vf28, $vf28x\n"
                     "vmaddz.y $vf8, $vf31, $vf28z\n"
                     "vadday.x $ACC, $vf29, $vf29y\n"
                     "vmaddz.x $vf8, $vf31, $vf29z\n"
                     "sqc2 $vf7, 0x0(%0)\n"
                     "vabs.xyz $vf29, $vf8\n"
                     "lqc2 $vf6, 0x0(%1)\n"
                     "vmul.xyz $vf28, $vf4, $vf29\n"
                     "lqc2 $vf10, 0x0(%2)\n"
                     "vadday.x $ACC, $vf28, $vf28y\n"
                     "vmaddz.x $vf27, $vf31, $vf28z\n"
                     "sqc2 $vf27, 0x10(%0)\n"
                     : : "r"(p0), "r"(p1), "r"(p2) : "memory");
}

/**
 * @brief Step 4 of the box/volume separating-axis test (from `vmul.xyz $vf29, $vf1, $vf6`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step4()
{
    asm __volatile__(
                     "vmul.xyz $vf29, $vf1, $vf6\n"
                     "vmul.xyz $vf28, $vf2, $vf6\n"
                     "vmul.xyz $vf27, $vf3, $vf6\n"
                     "vadday.x $ACC, $vf29, $vf29y\n"
                     "vmaddz.x $vf9, $vf31, $vf29z\n"
                     "vaddax.y $ACC, $vf28, $vf28x\n"
                     "vmaddz.y $vf9, $vf31, $vf28z\n"
                     "vadday.z $ACC, $vf27, $vf27y\n"
                     "vmaddx.z $vf9, $vf31, $vf27x\n"
                     "vmul.xyz $vf29, $vf5, $vf6\n"
                     "vmulx.xyz $vf11, $vf8, $vf10x\n"
                     "vmulz.xyz $vf12, $vf9, $vf10z\n"
                     "vsub.xyz $vf13, $vf12, $vf11\n"
                     "vadday.x $ACC, $vf29, $vf29y\n"
                     "vmaddz.x $vf7, $vf31, $vf29z\n"
                     "vabs.xyz $vf28, $vf13\n"
                     "vmul.xyz $vf27, $vf28, $vf4\n"
                     "vmulz.x $vf14, $vf7, $vf10z\n"
                     "vmulx.z $vf15, $vf7, $vf10x\n"
                     "vadday.x $ACC, $vf27, $vf27y\n"
                     "vmaddz.x $vf27, $vf31, $vf27z\n"
                     "vsubz.x $vf28, $vf14, $vf15z\n"
                     : :  );
}

/**
 * @brief Step 5 of the box/volume separating-axis test (from `sqc2 $vf27, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step5(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf27, 0x0(%0)\n"
                     "sqc2 $vf28, 0x10(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 6 of the box/volume separating-axis test (from `vadd.xyz $vf16, $vf12, $vf11`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step6()
{
    asm __volatile__(
                     "vadd.xyz $vf16, $vf12, $vf11\n"
                     "vabs.xyz $vf29, $vf16\n"
                     "vmul.xyz $vf28, $vf29, $vf4\n"
                     "vadday.x $ACC, $vf28, $vf28y\n"
                     "vmaddz.x $vf27, $vf31, $vf28z\n"
                     "vmula.x $ACC, $vf30, $vf14\n"
                     "vmaddz.x $vf28, $vf30, $vf15z\n"
                     : :  );
}

/**
 * @brief Step 7 of the box/volume separating-axis test (from `sqc2 $vf27, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step7(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf27, 0x0(%0)\n"
                     "sqc2 $vf28, 0x10(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 8 of the box/volume separating-axis test (from `lqc2 $vf6, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step8(const void* p0)
{
    asm __volatile__(
                     "lqc2 $vf6, 0x0(%0)\n"
                     "vmul.xyz $vf29, $vf1, $vf6\n"
                     "vmul.xyz $vf28, $vf2, $vf6\n"
                     "vmul.xyz $vf27, $vf3, $vf6\n"
                     "vadday.x $ACC, $vf29, $vf29y\n"
                     "vmaddz.x $vf17, $vf31, $vf29z\n"
                     "vaddax.y $ACC, $vf28, $vf28x\n"
                     "vmaddz.y $vf17, $vf31, $vf28z\n"
                     "vadday.z $ACC, $vf27, $vf27y\n"
                     "vmaddx.z $vf17, $vf31, $vf27x\n"
                     "vmuly.xyz $vf18, $vf8, $vf10y\n"
                     "vmulz.xyz $vf19, $vf17, $vf10z\n"
                     "vsub.xyz $vf20, $vf19, $vf18\n"
                     "vmul.xyz $vf29, $vf5, $vf6\n"
                     "vabs.xyz $vf28, $vf20\n"
                     "vaddax.y $ACC, $vf29, $vf29x\n"
                     "vmaddz.y $vf7, $vf31, $vf29z\n"
                     "vmul.xyz $vf27, $vf28, $vf4\n"
                     "vmulz.y $vf14, $vf7, $vf10z\n"
                     "vmuly.z $vf21, $vf7, $vf10y\n"
                     "vadday.x $ACC, $vf27, $vf27y\n"
                     "vmaddz.x $vf27, $vf31, $vf27z\n"
                     "vsubz.y $vf28, $vf14, $vf21z\n"
                     : : "r"(p0) : "memory");
}

/**
 * @brief Step 9 of the box/volume separating-axis test (from `sqc2 $vf27, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step9(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf27, 0x0(%0)\n"
                     "sqc2 $vf28, 0x10(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 10 of the box/volume separating-axis test (from `vadd.xyz $vf22, $vf19, $vf18`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step10()
{
    asm __volatile__(
                     "vadd.xyz $vf22, $vf19, $vf18\n"
                     "vabs.xyz $vf29, $vf22\n"
                     "vmul.xyz $vf28, $vf29, $vf4\n"
                     "vmulay.x $ACC, $vf30, $vf14y\n"
                     "vmaddz.x $vf29, $vf30, $vf21z\n"
                     "vadday.x $ACC, $vf28, $vf28y\n"
                     "vmaddz.x $vf27, $vf31, $vf28z\n"
                     : :  );
}

/**
 * @brief Step 11 of the box/volume separating-axis test (from `sqc2 $vf29, 0x10(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step11(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x10(%0)\n"
                     "sqc2 $vf27, 0x0(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 12 of the box/volume separating-axis test (from `vabs.xyz $vf29, $vf9`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step12()
{
    asm __volatile__(
                     "vabs.xyz $vf29, $vf9\n"
                     "vabs.xyz $vf28, $vf17\n"
                     "vmulz.xyz $vf23, $vf8, $vf10z\n"
                     "vmulax.xyz $ACC, $vf29, $vf10x\n"
                     "vmaddy.xyz $vf27, $vf28, $vf10y\n"
                     "vmulax.xyz $ACC, $vf9, $vf7x\n"
                     "vmadday.xyz $ACC, $vf17, $vf7y\n"
                     "vmaddz.xyz $vf28, $vf8, $vf7z\n"
                     "vsub.xyz $vf29, $vf23, $vf27\n"
                     "vadd.xyz $vf27, $vf23, $vf27\n"
                     : :  );
}

/**
 * @brief Step 13 of the box/volume separating-axis test (from `sqc2 $vf28, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step13(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf28, 0x0(%0)\n"
                     "sqc2 $vf29, 0x10(%0)\n"
                     "sqc2 $vf27, 0x20(%0)\n"
                     "sqc2 $vf4, 0x30(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 14 of the box/volume separating-axis test (from `vabs.xyz $vf29, $vf8`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step14()
{
    asm __volatile__(
                     "vabs.xyz $vf29, $vf8\n"
                     "vmuly.xyz $vf29, $vf29, $vf10y\n"
                     "vsub.xyz $vf28, $vf19, $vf29\n"
                     "vadd.xyz $vf27, $vf19, $vf29\n"
                     "vmulaz.xyz $ACC, $vf17, $vf7z\n"
                     "vmsuby.xyz $vf29, $vf8, $vf7y\n"
                     : :  );
}

/**
 * @brief Step 15 of the box/volume separating-axis test (from `sqc2 $vf29, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step15(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x0(%0)\n"
                     "sqc2 $vf28, 0x10(%0)\n"
                     "sqc2 $vf27, 0x20(%0)\n"
                     "vmulax.xyz $ACC, $vf17, $vf8x\n"
                     "vmsubx.xyz $vf29, $vf8, $vf17x\n"
                     "vmulay.xyz $ACC, $vf17, $vf8y\n"
                     "vmsuby.xyz $vf28, $vf8, $vf17y\n"
                     "vmulaz.xyz $ACC, $vf17, $vf8z\n"
                     "vmsubz.xyz $vf27, $vf8, $vf17z\n"
                     "vabs.xyz $vf29, $vf29\n"
                     "vabs.xyz $vf28, $vf28\n"
                     "vabs.xyz $vf27, $vf27\n"
                     "vmul.xyz $vf29, $vf29, $vf4\n"
                     "vmul.xyz $vf28, $vf28, $vf4\n"
                     "vmul.xyz $vf27, $vf27, $vf4\n"
                     "vadday.x $ACC, $vf29, $vf29y\n"
                     "vmaddz.x $vf29, $vf31, $vf29z\n"
                     "vaddax.y $ACC, $vf28, $vf28x\n"
                     "vmaddz.y $vf29, $vf31, $vf28z\n"
                     "vadday.z $ACC, $vf27, $vf27y\n"
                     "vmaddx.z $vf29, $vf31, $vf27x\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 16 of the box/volume separating-axis test (from `sqc2 $vf29, 0x30(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step16(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x30(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 17 of the box/volume separating-axis test (from `vabs.xyz $vf29, $vf8`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step17()
{
    asm __volatile__(
                     "vabs.xyz $vf29, $vf8\n"
                     "vmulx.xyz $vf28, $vf29, $vf10x\n"
                     "vmula.xyz $ACC, $vf30, $vf12\n"
                     "vmsubw.xyz $vf29, $vf28, $vf0w\n"
                     "vsub.xyz $vf28, $vf28, $vf12\n"
                     "vmulax.xyz $ACC, $vf8, $vf7x\n"
                     "vmsubz.xyz $vf27, $vf9, $vf7z\n"
                     : :  );
}

/**
 * @brief Step 18 of the box/volume separating-axis test (from `sqc2 $vf29, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step18(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x0(%0)\n"
                     "sqc2 $vf28, 0x10(%0)\n"
                     "sqc2 $vf27, 0x20(%0)\n"
                     "vmulax.xyz $ACC, $vf9, $vf8x\n"
                     "vmsubx.xyz $vf29, $vf8, $vf9x\n"
                     "vmulay.xyz $ACC, $vf9, $vf8y\n"
                     "vmsuby.xyz $vf28, $vf8, $vf9y\n"
                     "vmulaz.xyz $ACC, $vf9, $vf8z\n"
                     "vmsubz.xyz $vf27, $vf8, $vf9z\n"
                     "vabs.xyz $vf29, $vf29\n"
                     "vabs.xyz $vf28, $vf28\n"
                     "vabs.xyz $vf27, $vf27\n"
                     "vmul.xyz $vf29, $vf29, $vf4\n"
                     "vmul.xyz $vf28, $vf28, $vf4\n"
                     "vmul.xyz $vf27, $vf27, $vf4\n"
                     "vadday.x $ACC, $vf29, $vf29y\n"
                     "vmaddz.x $vf29, $vf31, $vf29z\n"
                     "vaddax.y $ACC, $vf28, $vf28x\n"
                     "vmaddz.y $vf29, $vf31, $vf28z\n"
                     "vadday.z $ACC, $vf27, $vf27y\n"
                     "vmaddx.z $vf29, $vf31, $vf27x\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 19 of the box/volume separating-axis test (from `sqc2 $vf29, 0x30(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step19(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x30(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 20 of the box/volume separating-axis test (from `vmulx.xyz $vf24, $vf17, $vf10x`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step20()
{
    asm __volatile__(
                     "vmulx.xyz $vf24, $vf17, $vf10x\n"
                     "vmuly.xyz $vf25, $vf9, $vf10y\n"
                     "vadd.xyz $vf26, $vf24, $vf25\n"
                     "vsub.xyz $vf23, $vf24, $vf25\n"
                     "vabs.xyz $vf29, $vf20\n"
                     "vabs.xyz $vf28, $vf13\n"
                     "vmulax.xyz $ACC, $vf29, $vf10x\n"
                     "vmaddy.xyz $vf27, $vf28, $vf10y\n"
                     "vmulz.xyz $vf28, $vf23, $vf10z\n"
                     "vsub.xyz $vf29, $vf28, $vf27\n"
                     "vadd.xyz $vf28, $vf28, $vf27\n"
                     "vmulay.xyz $ACC, $vf13, $vf7y\n"
                     "vmsubax.xyz $ACC, $vf20, $vf7x\n"
                     "vmaddz.xyz $vf27, $vf23, $vf7z\n"
                     : :  );
}

/**
 * @brief Step 21 of the box/volume separating-axis test (from `sqc2 $vf29, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step21(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x0(%0)\n"
                     "sqc2 $vf28, 0x10(%0)\n"
                     "sqc2 $vf27, 0x20(%0)\n"
                     "vmulax.xyz $ACC, $vf13, $vf17x\n"
                     "vmsubax.xyz $ACC, $vf20, $vf9x\n"
                     "vmaddx.xyz $vf29, $vf23, $vf8x\n"
                     "vmulay.xyz $ACC, $vf13, $vf17y\n"
                     "vmsubay.xyz $ACC, $vf20, $vf9y\n"
                     "vmaddy.xyz $vf28, $vf23, $vf8y\n"
                     "vmulaz.xyz $ACC, $vf13, $vf17z\n"
                     "vmsubaz.xyz $ACC, $vf20, $vf9z\n"
                     "vmaddz.xyz $vf27, $vf23, $vf8z\n"
                     "vabs.xyz $vf29, $vf29\n"
                     "vabs.xyz $vf28, $vf28\n"
                     "vabs.xyz $vf27, $vf27\n"
                     "vmulax.xyz $ACC, $vf29, $vf4x\n"
                     "vmadday.xyz $ACC, $vf28, $vf4y\n"
                     "vmaddz.xyz $vf29, $vf27, $vf4z\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 22 of the box/volume separating-axis test (from `sqc2 $vf29, 0x30(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step22(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x30(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 23 of the box/volume separating-axis test (from `vabs.xyz $vf29, $vf22`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step23()
{
    asm __volatile__(
                     "vabs.xyz $vf29, $vf22\n"
                     "vabs.xyz $vf28, $vf13\n"
                     "vmulax.xyz $ACC, $vf29, $vf10x\n"
                     "vmaddy.xyz $vf29, $vf28, $vf10y\n"
                     "vmulz.xyz $vf27, $vf26, $vf10z\n"
                     "vsub.xyz $vf28, $vf27, $vf29\n"
                     "vadd.xyz $vf27, $vf27, $vf29\n"
                     "vmulay.xyz $ACC, $vf13, $vf7y\n"
                     "vmsubax.xyz $ACC, $vf22, $vf7x\n"
                     "vmaddz.xyz $vf29, $vf26, $vf7z\n"
                     : :  );
}

/**
 * @brief Step 24 of the box/volume separating-axis test (from `sqc2 $vf28, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step24(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf28, 0x0(%0)\n"
                     "sqc2 $vf27, 0x10(%0)\n"
                     "sqc2 $vf29, 0x20(%0)\n"
                     "vmulax.xyz $ACC, $vf13, $vf17x\n"
                     "vmsubax.xyz $ACC, $vf22, $vf9x\n"
                     "vmaddx.xyz $vf29, $vf26, $vf8x\n"
                     "vmulay.xyz $ACC, $vf13, $vf17y\n"
                     "vmsubay.xyz $ACC, $vf22, $vf9y\n"
                     "vmaddy.xyz $vf28, $vf26, $vf8y\n"
                     "vmulaz.xyz $ACC, $vf13, $vf17z\n"
                     "vmsubaz.xyz $ACC, $vf22, $vf9z\n"
                     "vmaddz.xyz $vf27, $vf26, $vf8z\n"
                     "vabs.xyz $vf29, $vf29\n"
                     "vabs.xyz $vf28, $vf28\n"
                     "vabs.xyz $vf27, $vf27\n"
                     "vmulax.xyz $ACC, $vf29, $vf4x\n"
                     "vmadday.xyz $ACC, $vf28, $vf4y\n"
                     "vmaddz.xyz $vf29, $vf27, $vf4z\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 25 of the box/volume separating-axis test (from `sqc2 $vf29, 0x30(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step25(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x30(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 26 of the box/volume separating-axis test (from `vabs.xyz $vf29, $vf20`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step26()
{
    asm __volatile__(
                     "vabs.xyz $vf29, $vf20\n"
                     "vabs.xyz $vf28, $vf16\n"
                     "vmulax.xyz $ACC, $vf29, $vf10x\n"
                     "vmaddy.xyz $vf29, $vf28, $vf10y\n"
                     "vmulax.xyz $ACC, $vf0, $vf0x\n"
                     "vmsubz.xyz $vf27, $vf26, $vf10z\n"
                     "vsub.xyz $vf28, $vf27, $vf29\n"
                     "vadd.xyz $vf27, $vf27, $vf29\n"
                     "vmulay.xyz $ACC, $vf16, $vf7y\n"
                     "vmsubax.xyz $ACC, $vf20, $vf7x\n"
                     "vmsubz.xyz $vf29, $vf26, $vf7z\n"
                     : :  );
}

/**
 * @brief Step 27 of the box/volume separating-axis test (from `sqc2 $vf28, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step27(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf28, 0x0(%0)\n"
                     "sqc2 $vf27, 0x10(%0)\n"
                     "sqc2 $vf29, 0x20(%0)\n"
                     "vmulax.xyz $ACC, $vf16, $vf17x\n"
                     "vmsubax.xyz $ACC, $vf20, $vf9x\n"
                     "vmsubx.xyz $vf29, $vf26, $vf8x\n"
                     "vmulay.xyz $ACC, $vf16, $vf17y\n"
                     "vmsubay.xyz $ACC, $vf20, $vf9y\n"
                     "vmsuby.xyz $vf28, $vf26, $vf8y\n"
                     "vmulaz.xyz $ACC, $vf16, $vf17z\n"
                     "vmsubaz.xyz $ACC, $vf20, $vf9z\n"
                     "vmsubz.xyz $vf27, $vf26, $vf8z\n"
                     "vabs.xyz $vf29, $vf29\n"
                     "vabs.xyz $vf28, $vf28\n"
                     "vabs.xyz $vf27, $vf27\n"
                     "vmulax.xyz $ACC, $vf29, $vf4x\n"
                     "vmadday.xyz $ACC, $vf28, $vf4y\n"
                     "vmaddz.xyz $vf29, $vf27, $vf4z\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 28 of the box/volume separating-axis test (from `sqc2 $vf29, 0x30(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step28(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x30(%0)\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 29 of the box/volume separating-axis test (from `vabs.xyz $vf29, $vf22`).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step29()
{
    asm __volatile__(
                     "vabs.xyz $vf29, $vf22\n"
                     "vabs.xyz $vf28, $vf16\n"
                     "vmulax.xyz $ACC, $vf29, $vf10x\n"
                     "vmaddy.xyz $vf29, $vf28, $vf10y\n"
                     "vmulax.xyz $ACC, $vf0, $vf0x\n"
                     "vmsubz.xyz $vf27, $vf23, $vf10z\n"
                     "vsub.xyz $vf28, $vf27, $vf29\n"
                     "vadd.xyz $vf27, $vf27, $vf29\n"
                     "vmulay.xyz $ACC, $vf16, $vf7y\n"
                     "vmsubax.xyz $ACC, $vf22, $vf7x\n"
                     "vmsubz.xyz $vf29, $vf23, $vf7z\n"
                     : :  );
}

/**
 * @brief Step 30 of the box/volume separating-axis test (from `sqc2 $vf28, 0x0(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step30(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf28, 0x0(%0)\n"
                     "sqc2 $vf27, 0x10(%0)\n"
                     "sqc2 $vf29, 0x20(%0)\n"
                     "vmulax.xyz $ACC, $vf16, $vf17x\n"
                     "vmsubax.xyz $ACC, $vf22, $vf9x\n"
                     "vmsubx.xyz $vf29, $vf23, $vf8x\n"
                     "vmulay.xyz $ACC, $vf16, $vf17y\n"
                     "vmsubay.xyz $ACC, $vf22, $vf9y\n"
                     "vmsuby.xyz $vf28, $vf23, $vf8y\n"
                     "vmulaz.xyz $ACC, $vf16, $vf17z\n"
                     "vmsubaz.xyz $ACC, $vf22, $vf9z\n"
                     "vmsubz.xyz $vf27, $vf23, $vf8z\n"
                     "vabs.xyz $vf29, $vf29\n"
                     "vabs.xyz $vf28, $vf28\n"
                     "vabs.xyz $vf27, $vf27\n"
                     "vmulax.xyz $ACC, $vf29, $vf4x\n"
                     "vmadday.xyz $ACC, $vf28, $vf4y\n"
                     "vmaddz.xyz $vf29, $vf27, $vf4z\n"
                     : : "r"(p0) );
}

/**
 * @brief Step 31 of the box/volume separating-axis test (from `sqc2 $vf29, 0x30(%0)`).
 * @param p0 Aligned operand 0.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CAB20 in Lib.
 */
static inline void vu0_box_cull_step31(const void* p0)
{
    asm __volatile__(
                     "sqc2 $vf29, 0x30(%0)\n"
                     : : "r"(p0) );
}

#endif
