#ifndef SO3_OVERLAYS_LIB_SHAPE_VU0_H
#define SO3_OVERLAYS_LIB_SHAPE_VU0_H

/**
 * @brief Transform a point and a direction in place by one matrix: the point uses all four rows, the direction
 * only the first three.
 * @param matrix Aligned four-row matrix.
 * @param point Aligned point, transformed in place.
 * @param direction Aligned direction, transformed in place.
 * @see sceVu0ApplyMatrix in Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf). Lib does this for
 *      LibClass172FC0 at 0x425290.
 */
static inline void vu0_transform_point_and_direction(const void* matrix, void* point, void* direction)
{
    asm __volatile__(
        "lqc2 $vf1, 0x00(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "lqc2 $vf4, 0x30(%0)\n"
        "lqc2 $vf5, 0x00(%1)\n"
        "lqc2 $vf6, 0x00(%2)\n"
        "vmulax.xyzw $ACC, $vf1, $vf5x\n"
        "vmadday.xyzw $ACC, $vf2, $vf5y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf5z\n"
        "vmaddw.xyzw $vf5, $vf4, $vf5w\n"
        "vmulax.xyzw $ACC, $vf1, $vf6x\n"
        "vmadday.xyzw $ACC, $vf2, $vf6y\n"
        "vmaddz.xyzw $vf6, $vf3, $vf6z\n"
        "sqc2 $vf5, 0x00(%1)\n"
        "sqc2 $vf6, 0x00(%2)\n"
        :
        : "r"(matrix), "r"(point), "r"(direction)
        : "memory");
}

#endif
