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

/**
 * @brief Load a sphere centre, a point on a plane and the plane's normal into vf1, vf2 and vf3.
 * @param centre Aligned sphere centre.
 * @param point Aligned point on the plane.
 * @param normal Aligned plane normal.
 * @see lqc2 in Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf). Lib's shape push-out at 0x425AC0.
 */
static inline void vu0_shape_load_plane(const void* centre, const void* point, const void* normal)
{
    asm __volatile__(
        "lqc2 $vf1, 0x00(%0)\n"
        "lqc2 $vf2, 0x00(%1)\n"
        "lqc2 $vf3, 0x00(%2)\n"
        :
        : "r"(centre), "r"(point), "r"(normal)
        : "memory");
}

/**
 * @brief Load a sphere radius into vf4.
 * @param radius Radius.
 * @see qmtc2 in Sony's EE/VU manual. Lib's shape push-out at 0x425AC0.
 */
static inline void vu0_shape_set_radius(float radius)
{
    asm __volatile__("qmtc2.ni %0, $vf4\n" : : "r"(radius) : "memory");
}

/**
 * @brief Store how far the sphere in vf1/vf4 reaches past the plane in vf2/vf3, as the x of vf12.
 * @param distance Aligned 16-byte slot receiving vf12; x is the signed distance minus the radius.
 * @see vadda/vmadd in Sony's EE/VU manual. Lib's shape push-out at 0x425AC0.
 */
static inline void vu0_shape_plane_distance(void* distance)
{
    asm __volatile__(
        "vsub.xyz $vf10, $vf1, $vf2\n"
        "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
        "vmul.xyz $vf11, $vf10, $vf3\n"
        "vadday.x $ACC, $vf11, $vf11y\n"
        "vmaddz.x $vf12, $vf31, $vf11z\n"
        "vsub.x $vf12, $vf12, $vf4\n"
        "sqc2 $vf12, 0x00(%0)\n"
        :
        : "r"(distance)
        : "memory");
}

/**
 * @brief Move the sphere centre in vf1 back along the plane normal in vf3 by the distance in vf12.
 * @param output Aligned output for the moved centre.
 * @see vmsub in Sony's EE/VU manual. Lib's shape push-out at 0x425AC0.
 */
static inline void vu0_shape_push_out(void* output)
{
    asm __volatile__(
        "vaddax.xyz $ACC, $vf1, $vf0x\n"
        "vmsubx.xyz $vf1, $vf3, $vf12x\n"
        "sqc2 $vf1, 0x00(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief Load a segment's start point and axis into vf1 and vf2.
 * @param point Aligned start point.
 * @param axis Aligned axis; the segment runs from point to point + axis.
 * @see lqc2 in Sony's EE/VU manual. Lib's sphere-against-segment test at 0x425FC0.
 */
static inline void vu0_shape_load_segment(const void* point, const void* axis)
{
    asm __volatile__(
        "lqc2 $vf1, 0x00(%0)\n"
        "lqc2 $vf2, 0x00(%1)\n"
        :
        : "r"(point), "r"(axis)
        : "memory");
}

/**
 * @brief Load a segment parameter into vf3.
 * @param parameter Position along the segment, 0 at its start and 1 at its end.
 * @see qmtc2 in Sony's EE/VU manual. Lib's sphere-against-segment test at 0x425FC0.
 */
static inline void vu0_shape_set_parameter(float parameter)
{
    asm __volatile__("qmtc2.ni %0, $vf3\n" : : "r"(parameter) : "memory");
}

/**
 * @brief Put the offset from a point to the segment point at the parameter in vf10 and start computing the
 *        reciprocal of its length into Q.
 * @param position Aligned point.
 * @see vrsqrt in Sony's EE/VU manual. Lib's sphere-against-segment test at 0x425FC0.
 */
static inline void vu0_shape_segment_offset(const void* position)
{
    asm __volatile__(
        "lqc2 $vf4, 0x00(%0)\n"
        "vaddax.xyz $ACC, $vf1, $vf0x\n"
        "vmaddax.xyz $ACC, $vf2, $vf3x\n"
        "vmsubw.xyz $vf10, $vf4, $vf0w\n"
        "vmul.xyz $vf11, $vf10, $vf10\n"
        "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
        "vadday.x $ACC, $vf11, $vf11y\n"
        "vmaddz.x $vf12, $vf31, $vf11z\n"
        "vrsqrt $Q, $vf0w, $vf12x\n"
        :
        : "r"(position)
        : "memory");
}

/**
 * @brief Store the offset in vf10 scaled to unit length by Q.
 * @param output Aligned output.
 * @see vwaitq in Sony's EE/VU manual. Lib's sphere-against-segment test at 0x425FC0.
 */
static inline void vu0_shape_store_unit_offset(void* output)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyz $vf13, $vf10, $Q\n"
        "sqc2 $vf13, 0x00(%0)\n"
        :
        : "r"(output)
        : "memory");
}

#endif
