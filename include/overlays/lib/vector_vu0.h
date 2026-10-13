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

#endif
