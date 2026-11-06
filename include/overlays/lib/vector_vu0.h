#ifndef SO3_OVERLAYS_LIB_VECTOR_VU0_H
#define SO3_OVERLAYS_LIB_VECTOR_VU0_H

#include "overlays/lib/text_003E68C0.h"
/**
 * @brief Store the xyz dot product of point minus origin with direction in output.x.
 * @param output Aligned vector receiving the result in x.
 * @param point Aligned point vector.
 * @param direction Aligned vector supplying the dot-product coefficients.
 * @param origin Aligned vector subtracted from point.
 */
static inline void vu0_dot_offset_xyz(LibVector4* output, const LibVector4* point, const LibVector4* direction, const LibVector4* origin)
{
    asm __volatile__(
        "lqc2       $vf16, 0x0(%1)\n"
        "lqc2       $vf17, 0x0(%2)\n"
        "lqc2       $vf18, 0x0(%3)\n"
        "vsub.xyz   $vf19, $vf16, $vf18\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vmul.xyz   $vf20, $vf19, $vf17\n"
        "vadday.x   $ACC, $vf20, $vf20y\n"
        "vmaddz.x   $vf16, $vf31, $vf20z\n"
        "sqc2       $vf16, 0x0(%0)\n"
        :
        : "r"(output), "r"(point), "r"(direction), "r"(origin)
        : "memory");
}

/**
 * @brief Blend four consecutive vectors by four weights into vf12.
 *
 * vf12 becomes weights.x * first[0] + weights.y * first[1] + weights.z * second[0] + weights.w * second[1].
 * @param weights Aligned weights.
 * @param first Aligned pair of vectors taking the x and y weights.
 * @param second Aligned pair of vectors taking the z and w weights.
 * @see sceVu0ApplyMatrix in Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf).
 */
static inline void vu0_blend_four(const void* weights, const void* first, const void* second)
{
    asm __volatile__(
        "lqc2       $vf12, 0x0(%0)\n"
        "lqc2       $vf13, 0x0(%1)\n"
        "lqc2       $vf14, 0x10(%1)\n"
        "lqc2       $vf15, 0x0(%2)\n"
        "lqc2       $vf16, 0x10(%2)\n"
        "vmulax.xyzw $ACC, $vf13, $vf12x\n"
        "vmadday.xyzw $ACC, $vf14, $vf12y\n"
        "vmaddaz.xyzw $ACC, $vf15, $vf12z\n"
        "vmaddw.xyzw $vf12, $vf16, $vf12w\n"
        :
        : "r"(weights), "r"(first), "r"(second)
        : "memory");
}

/**
 * @brief Store vf12.
 * @param output Aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf).
 */
static inline void vu0_store_vf12(void* output)
{
    asm __volatile__(
        "sqc2       $vf12, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

#endif
