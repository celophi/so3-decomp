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

/**
 * @brief Move a sphere by the matrix the caller left in vf1-vf4, scale its radius by vf5.x, and leave in vf10.w how
 *        far inside it a point is (radius squared minus distance squared).
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param point Aligned point.
 * @see Lib's sphere tests at 0x45BE60 and nearby, which run inside a pass that loaded vf1-vf5.
 */
static inline void vu0_sphere_point_margin(const void* sphere, const void* point)
{
    asm __volatile__(
        "lqc2       $vf10, 0x0(%0)\n"
        "lqc2       $vf6, 0x0(%1)\n"
        "vmulax.xyzw $ACC, $vf1, $vf10x\n"
        "vmadday.xyzw $ACC, $vf2, $vf10y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf10z\n"
        "vmaddw.xyzw $vf11, $vf4, $vf0w\n"
        "vmulx.w    $vf10, $vf10, $vf5x\n"
        "vsub.xyz   $vf12, $vf11, $vf6\n"
        "vmul.w     $vf10, $vf10, $vf10\n"
        "vmul.xyz   $vf12, $vf12, $vf12\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vadday.x   $ACC, $vf12, $vf12y\n"
        "vmaddz.x   $vf13, $vf31, $vf12z\n"
        "vsubx.w    $vf10, $vf10, $vf13x\n"
        :
        : "r"(sphere), "r"(point)
        : "memory");
}

/**
 * @brief Store vf10.
 * @param vector Aligned destination.
 * @see vu0_sphere_point_margin.
 */
static inline void vu0_store_vf10(void* vector)
{
    asm __volatile__("sqc2 $vf10, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Move two spheres by the matrices the caller left in vf1-vf4 and vf5-vf8, scale their radii by vf9.x and
 *        vf9.y, and leave in vf11.x their centre distance squared minus their radius sum squared.
 * @param first Aligned first sphere: centre in xyz, radius in w.
 * @param second Aligned second sphere.
 * @see Lib's sphere tests at 0x45E980 and nearby, which run inside a pass that loaded vf1-vf9.
 */
static inline void vu0_sphere_sphere_gap(const void* first, const void* second)
{
    asm __volatile__(
        "lqc2       $vf10, 0x0(%0)\n"
        "lqc2       $vf11, 0x0(%1)\n"
        "vmulax.xyzw $ACC, $vf1, $vf10x\n"
        "vmadday.xyzw $ACC, $vf2, $vf10y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf10z\n"
        "vmaddw.xyzw $vf13, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf5, $vf11x\n"
        "vmadday.xyzw $ACC, $vf6, $vf11y\n"
        "vmaddaz.xyzw $ACC, $vf7, $vf11z\n"
        "vmaddw.xyzw $vf14, $vf8, $vf0w\n"
        "vmulx.w    $vf10, $vf10, $vf9x\n"
        "vmuly.w    $vf11, $vf11, $vf9y\n"
        "vsub.xyz   $vf13, $vf13, $vf14\n"
        "vadd.w     $vf10, $vf10, $vf11\n"
        "vmul.xyz   $vf13, $vf13, $vf13\n"
        "vaddw.x    $vf14, $vf0, $vf0w\n"
        "vmul.w     $vf10, $vf10, $vf10\n"
        "vmulax.x   $ACC, $vf14, $vf13x\n"
        "vmadday.x  $ACC, $vf14, $vf13y\n"
        "vmsubaw.x  $ACC, $vf14, $vf10w\n"
        "vmaddz.x   $vf11, $vf14, $vf13z\n"
        :
        : "r"(first), "r"(second)
        : "memory");
}

/**
 * @brief Store vf11.
 * @param vector Aligned destination.
 * @see vu0_sphere_sphere_gap.
 */
static inline void vu0_store_vf11(void* vector)
{
    asm __volatile__("sqc2 $vf11, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Move a sphere by the matrix the caller left in vf1-vf4, scale its radius by vf5.x, and leave in vf10.w the
 *        distance squared from its centre to a ray (from its origin on) minus the radius squared.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param origin Aligned ray origin.
 * @param direction Aligned unit ray direction.
 * @see Lib's sphere tests at 0x45CB40 and nearby, which run inside a pass that loaded vf1-vf5.
 */
static inline void vu0_sphere_ray_gap(const void* sphere, const void* origin, const void* direction)
{
    asm __volatile__(
        "lqc2       $vf10, 0x0(%0)\n"
        "lqc2       $vf6, 0x0(%1)\n"
        "lqc2       $vf7, 0x0(%2)\n"
        "vmulax.xyzw $ACC, $vf1, $vf10x\n"
        "vmadday.xyzw $ACC, $vf2, $vf10y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf10z\n"
        "vmaddw.xyzw $vf11, $vf4, $vf0w\n"
        "vmulx.w    $vf10, $vf10, $vf5x\n"
        "vsub.xyz   $vf12, $vf11, $vf6\n"
        "vmul.w     $vf10, $vf10, $vf10\n"
        "vmul.xyz   $vf13, $vf12, $vf7\n"
        "vmulax.w   $ACC, $vf0, $vf13x\n"
        "vmadday.w  $ACC, $vf0, $vf13y\n"
        "vmaddz.w   $vf13, $vf0, $vf13z\n"
        "vmaxx.w    $vf13, $vf13, $vf0x\n"
        "vmulw.xyz  $vf14, $vf7, $vf13w\n"
        "vsub.xyz   $vf14, $vf12, $vf14\n"
        "vmul.xyz   $vf13, $vf14, $vf14\n"
        "vmulax.w   $ACC, $vf0, $vf13x\n"
        "vmadday.w  $ACC, $vf0, $vf13y\n"
        "vmaddz.w   $vf13, $vf0, $vf13z\n"
        "vsub.w     $vf10, $vf13, $vf10\n"
        :
        : "r"(sphere), "r"(origin), "r"(direction)
        : "memory");
}

/**
 * @brief Move a point by a matrix into vf14 and scale a box's half extents by vf5.x into vf30.
 * @param point Aligned point.
 * @param matrix Aligned four-row matrix.
 * @param half_extents Aligned half extents in xyz.
 * @see Lib's box test at 0x45BD50, which runs inside a pass that loaded vf5.
 */
static inline void vu0_box_point_local(const void* point, const void* matrix, const void* half_extents)
{
    asm __volatile__(
        "lqc2       $vf12, 0x0(%0)\n"
        "lqc2       $vf16, 0x0(%1)\n"
        "lqc2       $vf17, 0x10(%1)\n"
        "lqc2       $vf18, 0x20(%1)\n"
        "lqc2       $vf19, 0x30(%1)\n"
        "lqc2       $vf30, 0x0(%2)\n"
        "vmulax.xyzw $ACC, $vf16, $vf12x\n"
        "vmadday.xyzw $ACC, $vf17, $vf12y\n"
        "vmaddaz.xyzw $ACC, $vf18, $vf12z\n"
        "vmaddw.xyzw $vf14, $vf19, $vf0w\n"
        "vmulx.xyz  $vf30, $vf30, $vf5x\n"
        :
        : "r"(point), "r"(matrix), "r"(half_extents)
        : "memory");
}

/**
 * @brief Store vf14.
 * @param vector Aligned destination.
 * @see vu0_box_point_local.
 */
static inline void vu0_store_vf14(void* vector)
{
    asm __volatile__("sqc2 $vf14, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Store vf30.
 * @param vector Aligned destination.
 * @see vu0_box_point_local.
 */
static inline void vu0_store_vf30(void* vector)
{
    asm __volatile__("sqc2 $vf30, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Save vf6 and vf8 to a two-quadword block.
 * @param registers Aligned block of two quadwords.
 * @see Lib's shape test at 0x45BED0, which rebuilds the camera transform in the middle of a pass.
 */
static inline void vu0_save_vf6_vf8(void* registers)
{
    asm __volatile__(
        "sqc2 $vf6, 0x0(%0)\n"
        "sqc2 $vf8, 0x10(%0)\n"
        :
        : "r"(registers)
        : "memory");
}

/**
 * @brief Load vf6 and vf8 back from a block vu0_save_vf6_vf8 filled.
 * @param registers Aligned block of two quadwords.
 * @see vu0_save_vf6_vf8.
 */
static inline void vu0_restore_vf6_vf8(const void* registers)
{
    asm __volatile__(
        "lqc2 $vf6, 0x0(%0)\n"
        "lqc2 $vf8, 0x10(%0)\n"
        :
        : "r"(registers)
        : "memory");
}

/**
 * @brief Save vf1-vf5 (a pass's matrix and scale) to a five-quadword block.
 * @param registers Aligned block of five quadwords.
 * @see Lib's shape tree test at 0x45BFB0, which loads its own matrix and puts the caller's back when it fails.
 */
static inline void vu0_save_vf1_vf5(void* registers)
{
    asm __volatile__(
        "sqc2 $vf1, 0x0(%0)\n"
        "sqc2 $vf2, 0x10(%0)\n"
        "sqc2 $vf3, 0x20(%0)\n"
        "sqc2 $vf4, 0x30(%0)\n"
        "sqc2 $vf5, 0x40(%0)\n"
        :
        : "r"(registers)
        : "memory");
}

/**
 * @brief Load vf1-vf5 back from a block vu0_save_vf1_vf5 filled.
 * @param registers Aligned block of five quadwords.
 * @see vu0_save_vf1_vf5.
 */
static inline void vu0_restore_vf1_vf5(const void* registers)
{
    asm __volatile__(
        "lqc2 $vf1, 0x0(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "lqc2 $vf4, 0x30(%0)\n"
        "lqc2 $vf5, 0x40(%0)\n"
        :
        : "r"(registers)
        : "memory");
}

/**
 * @brief Load a scale into vf5 and a matrix into vf1-vf4, then run vu0_sphere_point_margin's test on a sphere.
 * @param matrix Aligned four-row matrix.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param scale Aligned scale in x.
 * @param point Aligned point.
 * @see vu0_sphere_point_margin; Lib's shape tree test at 0x45BFB0 checks the bounding sphere this way.
 */
static inline void vu0_sphere_point_margin_with(const void* matrix, const void* sphere, const void* scale,
                                                const void* point)
{
    asm __volatile__(
        "lqc2       $vf5, 0x0(%2)\n"
        "lqc2       $vf10, 0x0(%1)\n"
        "lqc2       $vf1, 0x0(%0)\n"
        "lqc2       $vf2, 0x10(%0)\n"
        "lqc2       $vf3, 0x20(%0)\n"
        "lqc2       $vf4, 0x30(%0)\n"
        "lqc2       $vf6, 0x0(%3)\n"
        "vmulax.xyzw $ACC, $vf1, $vf10x\n"
        "vmadday.xyzw $ACC, $vf2, $vf10y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf10z\n"
        "vmaddw.xyzw $vf11, $vf4, $vf0w\n"
        "vmulx.w    $vf10, $vf10, $vf5x\n"
        "vsub.xyz   $vf12, $vf11, $vf6\n"
        "vmul.w     $vf10, $vf10, $vf10\n"
        "vmul.xyz   $vf12, $vf12, $vf12\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vadday.x   $ACC, $vf12, $vf12y\n"
        "vmaddz.x   $vf13, $vf31, $vf12z\n"
        "vsubx.w    $vf10, $vf10, $vf13x\n"
        :
        : "r"(matrix), "r"(sphere), "r"(scale), "r"(point)
        : "memory");
}

/**
 * @brief Save vf1-vf9 (a two-matrix pass's matrices and scales) to a nine-quadword block.
 * @param registers Aligned block of nine quadwords.
 * @see Lib's shape tree test at 0x45D140, which loads its own matrix and puts the caller's back when it fails.
 */
static inline void vu0_save_vf1_vf9(void* registers)
{
    asm __volatile__(
        "sqc2 $vf1, 0x0(%0)\n"
        "sqc2 $vf2, 0x10(%0)\n"
        "sqc2 $vf3, 0x20(%0)\n"
        "sqc2 $vf4, 0x30(%0)\n"
        "sqc2 $vf5, 0x40(%0)\n"
        "sqc2 $vf6, 0x50(%0)\n"
        "sqc2 $vf7, 0x60(%0)\n"
        "sqc2 $vf8, 0x70(%0)\n"
        "sqc2 $vf9, 0x80(%0)\n"
        :
        : "r"(registers)
        : "memory");
}

/**
 * @brief Load vf1-vf9 back from a block vu0_save_vf1_vf9 filled.
 * @param registers Aligned block of nine quadwords.
 * @see vu0_save_vf1_vf9.
 */
static inline void vu0_restore_vf1_vf9(const void* registers)
{
    asm __volatile__(
        "lqc2 $vf1, 0x0(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "lqc2 $vf4, 0x30(%0)\n"
        "lqc2 $vf5, 0x40(%0)\n"
        "lqc2 $vf6, 0x50(%0)\n"
        "lqc2 $vf7, 0x60(%0)\n"
        "lqc2 $vf8, 0x70(%0)\n"
        "lqc2 $vf9, 0x80(%0)\n"
        :
        : "r"(registers)
        : "memory");
}

/**
 * @brief Load two matrices into vf1-vf4 and vf5-vf8 and two scales into vf9, then leave in vf12.x the centre
 *        distance squared minus the radius sum squared of two spheres moved and scaled by them.
 * @param first Aligned first sphere: centre in xyz, radius in w.
 * @param scale Aligned scales: x for the first sphere, y for the second.
 * @param first_matrix Aligned matrix for the first sphere.
 * @param second Aligned second sphere.
 * @param second_matrix Aligned matrix for the second sphere.
 * @see vu0_sphere_sphere_gap; Lib's shape tree test at 0x45D140 checks the bounding sphere this way.
 */
static inline void vu0_sphere_sphere_gap_with(const void* first, const void* scale, const void* first_matrix,
                                              const void* second, const void* second_matrix)
{
    asm __volatile__(
        "lqc2       $vf9, 0x0(%4)\n"
        "lqc2       $vf10, 0x0(%2)\n"
        "lqc2       $vf11, 0x0(%3)\n"
        "lqc2       $vf1, 0x0(%0)\n"
        "lqc2       $vf2, 0x10(%0)\n"
        "vmulx.w    $vf10, $vf10, $vf9x\n"
        "vmuly.w    $vf11, $vf11, $vf9y\n"
        "lqc2       $vf3, 0x20(%0)\n"
        "lqc2       $vf4, 0x30(%0)\n"
        "lqc2       $vf5, 0x0(%1)\n"
        "lqc2       $vf6, 0x10(%1)\n"
        "lqc2       $vf7, 0x20(%1)\n"
        "lqc2       $vf8, 0x30(%1)\n"
        "vmulax.xyzw $ACC, $vf1, $vf10x\n"
        "vmadday.xyzw $ACC, $vf2, $vf10y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf10z\n"
        "vmaddw.xyzw $vf12, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf5, $vf11x\n"
        "vmadday.xyzw $ACC, $vf6, $vf11y\n"
        "vmaddaz.xyzw $ACC, $vf7, $vf11z\n"
        "vmaddw.xyzw $vf13, $vf8, $vf0w\n"
        "vsub.xyz   $vf12, $vf12, $vf13\n"
        "vadd.w     $vf10, $vf10, $vf11\n"
        "vmul.xyz   $vf12, $vf12, $vf12\n"
        "vaddw.x    $vf13, $vf0, $vf0w\n"
        "vmul.w     $vf10, $vf10, $vf10\n"
        "vmulax.x   $ACC, $vf13, $vf12x\n"
        "vmadday.x  $ACC, $vf13, $vf12y\n"
        "vmsubaw.x  $ACC, $vf13, $vf10w\n"
        "vmaddz.x   $vf12, $vf13, $vf12z\n"
        :
        : "r"(first_matrix), "r"(second_matrix), "r"(first), "r"(second), "r"(scale)
        : "memory");
}

/**
 * @brief Start a ray-box separating axis test: move the box centre by vf1-vf4, then test the box's x axis.
 *
 * Leaves the ray (origin in vf8, direction in vf9) relative to the centre in vf7, the half extents in vf14, and in
 * vf24.x and vf25.x the axis distance minus the half extent and the distance times the direction.
 * @param centre Aligned box centre.
 * @param origin Aligned ray origin.
 * @param direction Aligned ray direction.
 * @param half_extents Aligned half extents in xyz.
 * @see Lib's ray-box test at 0x45C910, which runs inside a pass that loaded vf1-vf4.
 */
static inline void vu0_box_ray_axis_x(const void* centre, const void* origin, const void* direction,
                                      const void* half_extents)
{
    asm __volatile__("lqc2 $vf6, 0x0(%0)\n" : : "r"(centre) : "memory");
    asm __volatile__(
        "vmulax.xyzw $ACC, $vf1, $vf6x\n"
        "vmadday.xyzw $ACC, $vf2, $vf6y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf6z\n"
        "vmaddw.xyzw $vf6, $vf4, $vf0w\n"
        "lqc2       $vf8, 0x0(%0)\n"
        "lqc2       $vf9, 0x0(%1)\n"
        "lqc2       $vf14, 0x0(%2)\n"
        "vsub.xyz   $vf7, $vf8, $vf6\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vmul.xyz   $vf20, $vf9, $vf1\n"
        "vmul.xyz   $vf21, $vf7, $vf1\n"
        "vmul.xyz   $vf22, $vf9, $vf2\n"
        "vmul.xyz   $vf29, $vf7, $vf2\n"
        "vadday.x   $ACC, $vf20, $vf20y\n"
        "vmaddz.x   $vf10, $vf31, $vf20z\n"
        "vadday.x   $ACC, $vf21, $vf21y\n"
        "vmaddz.x   $vf12, $vf31, $vf21z\n"
        "vaddax.y   $ACC, $vf22, $vf22x\n"
        "vabs.x     $vf11, $vf10\n"
        "vmaddz.y   $vf10, $vf31, $vf22z\n"
        "vabs.x     $vf13, $vf12\n"
        "vaddax.y   $ACC, $vf29, $vf29x\n"
        "vmaddz.y   $vf12, $vf31, $vf29z\n"
        "vmul.x     $vf25, $vf12, $vf10\n"
        "vsub.x     $vf24, $vf13, $vf14\n"
        :
        : "r"(origin), "r"(direction), "r"(half_extents)
        : "memory");
}

/**
 * @brief Test the box's y axis, leaving the results in vf24.y and vf25.y.
 * @see vu0_box_ray_axis_x.
 */
static inline void vu0_box_ray_axis_y(void)
{
    asm __volatile__(
        "vabs.y     $vf11, $vf10\n"
        "vmul.xyz   $vf20, $vf9, $vf3\n"
        "vabs.y     $vf13, $vf12\n"
        "vmul.xyz   $vf21, $vf7, $vf3\n"
        "vaddax.z   $ACC, $vf20, $vf20x\n"
        "vmul.y     $vf25, $vf12, $vf10\n"
        "vsub.y     $vf24, $vf13, $vf14\n"
        "vmaddy.z   $vf10, $vf31, $vf20y\n"
        "vaddax.z   $ACC, $vf21, $vf21x\n"
        "vmaddy.z   $vf12, $vf31, $vf21y\n");
}

/**
 * @brief Test the box's z axis, leaving the results in vf24.z and vf25.z, and start the first cross axis.
 * @see vu0_box_ray_axis_x.
 */
static inline void vu0_box_ray_axis_z(void)
{
    asm __volatile__(
        "vabs.z     $vf11, $vf10\n"
        "vopmula.xyz $ACC, $vf9, $vf7\n"
        "vabs.z     $vf13, $vf12\n"
        "vopmsub.xyz $vf15, $vf7, $vf9\n"
        "vmul.xyz   $vf20, $vf15, $vf1\n"
        "vmul.z     $vf25, $vf12, $vf10\n"
        "vsub.z     $vf24, $vf13, $vf14\n"
        "vadday.x   $ACC, $vf20, $vf20y\n"
        "vmaddz.x   $vf20, $vf31, $vf20z\n");
}

/**
 * @brief Test the cross axis of the ray and the box's x axis, leaving the result in vf24.y.
 * @see vu0_box_ray_axis_x.
 */
static inline void vu0_box_ray_cross_x(void)
{
    asm __volatile__(
        "vabs.x     $vf16, $vf20\n"
        "vmul.xyz   $vf21, $vf15, $vf2\n"
        "vmulaz.y   $ACC, $vf11, $vf14z\n"
        "vmaddaz.y  $ACC, $vf14, $vf11z\n"
        "vmsubx.y   $vf24, $vf31, $vf16x\n"
        "vaddax.y   $ACC, $vf21, $vf21x\n"
        "vmaddz.y   $vf21, $vf31, $vf21z\n");
}

/**
 * @brief Test the cross axis of the ray and the box's y axis, leaving the result in vf24.x.
 * @see vu0_box_ray_axis_x.
 */
static inline void vu0_box_ray_cross_y(void)
{
    asm __volatile__(
        "vabs.y     $vf16, $vf21\n"
        "vmul.xyz   $vf22, $vf15, $vf3\n"
        "vmulaz.x   $ACC, $vf11, $vf14z\n"
        "vmaddaz.x  $ACC, $vf14, $vf11z\n"
        "vmsuby.x   $vf24, $vf31, $vf16y\n"
        "vaddax.z   $ACC, $vf22, $vf22x\n"
        "vmaddy.z   $vf22, $vf31, $vf22y\n");
}

/**
 * @brief Test the cross axis of the ray and the box's z axis, leaving the result in vf24.x.
 * @see vu0_box_ray_axis_x.
 */
static inline void vu0_box_ray_cross_z(void)
{
    asm __volatile__(
        "vabs.z     $vf16, $vf22\n"
        "vnop\n"
        "vmulay.x   $ACC, $vf11, $vf14y\n"
        "vmadday.x  $ACC, $vf14, $vf11y\n"
        "vmsubz.x   $vf24, $vf31, $vf16z\n");
}

/**
 * @brief Store vf24 and vf25 to a two-quadword block.
 * @param vectors Aligned block of two quadwords.
 * @see vu0_box_ray_axis_x.
 */
static inline void vu0_store_vf24_vf25(void* vectors)
{
    asm __volatile__(
        "sqc2 $vf24, 0x0(%0)\n"
        "sqc2 $vf25, 0x10(%0)\n"
        :
        : "r"(vectors)
        : "memory");
}

/**
 * @brief Store vf24.
 * @param vector Aligned destination.
 * @see vu0_box_ray_cross_x.
 */
static inline void vu0_store_vf24(void* vector)
{
    asm __volatile__("sqc2 $vf24, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Load a scale into vf5 and a matrix into vf1-vf4, then leave in vf10.w the distance squared from a moved and
 *        scaled sphere's centre to a ray (from its origin on) minus the radius squared.
 *
 * Unlike vu0_sphere_ray_gap, the direction need not be a unit vector.
 * @param matrix Aligned four-row matrix.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param scale Aligned scale in x.
 * @param origin Aligned ray origin.
 * @param direction Aligned ray direction.
 * @see Lib's shape tree test at 0x45CBE0, which checks the bounding sphere this way.
 */
static inline void vu0_sphere_ray_gap_with(const void* matrix, const void* sphere, const void* scale,
                                           const void* origin, const void* direction)
{
    asm __volatile__(
        "lqc2       $vf5, 0x0(%4)\n"
        "lqc2       $vf10, 0x0(%1)\n"
        "lqc2       $vf1, 0x0(%0)\n"
        "lqc2       $vf2, 0x10(%0)\n"
        "lqc2       $vf3, 0x20(%0)\n"
        "lqc2       $vf4, 0x30(%0)\n"
        "lqc2       $vf6, 0x0(%3)\n"
        "lqc2       $vf7, 0x0(%2)\n"
        "vmulax.xyzw $ACC, $vf1, $vf10x\n"
        "vmadday.xyzw $ACC, $vf2, $vf10y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf10z\n"
        "vmaddw.xyzw $vf11, $vf4, $vf0w\n"
        "vmul.xyz   $vf20, $vf7, $vf7\n"
        "vmulx.w    $vf10, $vf10, $vf5x\n"
        "vsub.xyz   $vf12, $vf11, $vf6\n"
        "vmul.w     $vf10, $vf10, $vf10\n"
        "vmulax.w   $ACC, $vf0, $vf20x\n"
        "vmadday.w  $ACC, $vf0, $vf20y\n"
        "vmaddz.w   $vf20, $vf0, $vf20z\n"
        "vmul.xyz   $vf13, $vf12, $vf7\n"
        "vmulax.w   $ACC, $vf0, $vf13x\n"
        "vmadday.w  $ACC, $vf0, $vf13y\n"
        "vdiv       $Q, $vf0w, $vf20w\n"
        "vmaddz.w   $vf13, $vf0, $vf13z\n"
        "vmaxx.w    $vf13, $vf13, $vf0x\n"
        "vwaitq\n"
        "vmulq.w    $vf13, $vf13, $Q\n"
        "vmulw.xyz  $vf14, $vf7, $vf13w\n"
        "vsub.xyz   $vf14, $vf12, $vf14\n"
        "vmul.xyz   $vf13, $vf14, $vf14\n"
        "vmulax.w   $ACC, $vf0, $vf13x\n"
        "vmadday.w  $ACC, $vf0, $vf13y\n"
        "vmaddz.w   $vf13, $vf0, $vf13z\n"
        "vsub.w     $vf10, $vf13, $vf10\n"
        :
        : "r"(matrix), "r"(sphere), "r"(direction), "r"(origin), "r"(scale)
        : "memory");
}

/**
 * @brief Load a matrix into vf16-vf19.
 * @param matrix Aligned four-row matrix.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_load_vf16_vf19(const void* matrix)
{
    asm __volatile__(
        "lqc2 $vf16, 0x0(%0)\n"
        "lqc2 $vf17, 0x10(%0)\n"
        "lqc2 $vf18, 0x20(%0)\n"
        "lqc2 $vf19, 0x30(%0)\n"
        :
        : "r"(matrix)
        : "memory");
}

/**
 * @brief Load vf13.
 * @param vector Aligned source.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_load_vf13(const void* vector)
{
    asm __volatile__("lqc2 $vf13, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Load vf16.
 * @param vector Aligned source.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_load_vf16(const void* vector)
{
    asm __volatile__("lqc2 $vf16, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Move the sphere in vf13 by the matrix in vf1-vf4 into vf14.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_move_vf13_by_vf1(void)
{
    asm __volatile__(
        "vmulax.xyzw $ACC, $vf1, $vf13x\n"
        "vmadday.xyzw $ACC, $vf2, $vf13y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf13z\n"
        "vmaddw.xyzw $vf14, $vf4, $vf0w\n");
}

/**
 * @brief Move the sphere in vf13 by the matrix in vf5-vf8 into vf14.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_move_vf13_by_vf5(void)
{
    asm __volatile__(
        "vmulax.xyzw $ACC, $vf5, $vf13x\n"
        "vmadday.xyzw $ACC, $vf6, $vf13y\n"
        "vmaddaz.xyzw $ACC, $vf7, $vf13z\n"
        "vmaddw.xyzw $vf14, $vf8, $vf0w\n");
}

/**
 * @brief Scale the radius in vf13.w by vf9.x.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_scale_vf13_radius_x(void)
{
    asm __volatile__("vmulx.w $vf13, $vf13, $vf9x\n");
}

/**
 * @brief Scale the radius in vf13.w by vf9.y.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_scale_vf13_radius_y(void)
{
    asm __volatile__("vmuly.w $vf13, $vf13, $vf9y\n");
}

/**
 * @brief Move the sphere centre in vf14 into the space of the matrix in vf16-vf19, and leave in vf14.w its radius
 *        squared scaled by the matrix's largest axis length.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_sphere_into_box_space(void)
{
    asm __volatile__(
        "vmula.xyz  $ACC, $vf16, $vf16\n"
        "vmadda.xyz $ACC, $vf17, $vf17\n"
        "vmadd.xyz  $vf15, $vf18, $vf18\n"
        "vmaxy.x    $vf15, $vf15, $vf15y\n"
        "vmul.w     $vf13, $vf13, $vf13\n"
        "vmaxz.x    $vf15, $vf15, $vf15z\n"
        "vsqrt      $Q, $vf15x\n"
        "vmulax.xyzw $ACC, $vf16, $vf14x\n"
        "vmadday.xyzw $ACC, $vf17, $vf14y\n"
        "vmaddaz.xyzw $ACC, $vf18, $vf14z\n"
        "vmaddw.xyz $vf14, $vf19, $vf0w\n"
        "vwaitq\n"
        "vmulq.w    $vf14, $vf13, $Q\n");
}

/**
 * @brief Scale the half extents in vf16 by vf9.x.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_scale_vf16_x(void)
{
    asm __volatile__("vmulx.xyz $vf16, $vf16, $vf9x\n");
}

/**
 * @brief Scale the half extents in vf16 by vf9.y.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_scale_vf16_y(void)
{
    asm __volatile__("vmuly.xyz $vf16, $vf16, $vf9y\n");
}

/**
 * @brief Leave a box's largest corner (centre in vf15 plus half extents in vf16) in vf17 and its smallest in vf18.
 * @see Lib's box-sphere test at 0x45E240.
 */
static inline void vu0_box_corners(void)
{
    asm __volatile__(
        "vadd.xyz   $vf17, $vf15, $vf16\n"
        "vsub.xyz   $vf18, $vf15, $vf16\n");
}

/**
 * @brief Store vf17 and vf18.
 * @param largest Aligned destination for vf17.
 * @param smallest Aligned destination for vf18.
 * @see vu0_box_corners.
 */
static inline void vu0_store_box_corners(void* largest, void* smallest)
{
    asm __volatile__(
        "sqc2 $vf17, 0x0(%1)\n"
        "sqc2 $vf18, 0x0(%0)\n"
        :
        : "r"(smallest), "r"(largest)
        : "memory");
}

/**
 * @brief Move a sphere by the matrix in vf1-vf4, grow its radius to vf5.x times it plus vf5.y, and set up where the
 *        segment from one point to another enters and leaves it.
 *
 * Leaves the discriminant in vf14.x, half the segment length squared's reciprocal in Q, and the terms
 * vu0_segment_sphere_fractions needs in vf12 and vf15.
 * @param sphere Aligned sphere: centre in xyz, radius in w.
 * @param start Aligned segment start.
 * @param end Aligned segment end.
 * @see Lib's segment tests at 0x45B740, which run inside a pass that loaded vf1-vf5.
 */
static inline void vu0_segment_sphere_setup(const void* sphere, const void* start, const void* end)
{
    asm __volatile__(
        "lqc2       $vf6, 0x0(%0)\n"
        "lqc2       $vf9, 0x0(%1)\n"
        "lqc2       $vf10, 0x0(%2)\n"
        "vsubw.xyz  $vf29, $vf0, $vf0w\n"
        "vmulax.xyzw $ACC, $vf1, $vf6x\n"
        "vmadday.xyzw $ACC, $vf2, $vf6y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf6z\n"
        "vmaddw.xyzw $vf7, $vf4, $vf0w\n"
        "vmulax.w   $ACC, $vf6, $vf5x\n"
        "vmaddy.w   $vf7, $vf0, $vf5y\n"
        "vsub.xyz   $vf8, $vf10, $vf9\n"
        "vsub.xyz   $vf20, $vf9, $vf7\n"
        "vmul.xyz   $vf22, $vf9, $vf7\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vmul.xyz   $vf23, $vf7, $vf7\n"
        "vmul.w     $vf7, $vf7, $vf7\n"
        "vmul.xyz   $vf11, $vf8, $vf8\n"
        "vmul.xyz   $vf21, $vf8, $vf20\n"
        "vadday.x   $ACC, $vf22, $vf22y\n"
        "vmaddz.x   $vf22, $vf31, $vf22z\n"
        "vadday.x   $ACC, $vf11, $vf11y\n"
        "vadd.xyz   $vf21, $vf21, $vf21\n"
        "vmaddz.x   $vf11, $vf31, $vf11z\n"
        "vadd.x     $vf22, $vf22, $vf22\n"
        "vmul.xyz   $vf24, $vf9, $vf9\n"
        "vadday.x   $ACC, $vf21, $vf21y\n"
        "vadd.x     $vf15, $vf11, $vf11\n"
        "vmaddz.x   $vf12, $vf31, $vf21z\n"
        "vadday.x   $ACC, $vf23, $vf23y\n"
        "vmaddaz.x  $ACC, $vf31, $vf23z\n"
        "vdiv       $Q, $vf0w, $vf15x\n"
        "vmaddax.x  $ACC, $vf31, $vf24x\n"
        "vmadday.x  $ACC, $vf31, $vf24y\n"
        "vmaddaz.x  $ACC, $vf31, $vf24z\n"
        "vmsubax.x  $ACC, $vf31, $vf22x\n"
        "vmsubw.x   $vf13, $vf31, $vf7w\n"
        "vmula.x    $ACC, $vf12, $vf12\n"
        "vmsuba.x   $ACC, $vf13, $vf11\n"
        "vmsuba.x   $ACC, $vf13, $vf11\n"
        "vmsuba.x   $ACC, $vf13, $vf11\n"
        "vmsub.x    $vf14, $vf13, $vf11\n"
        "vmulq.x    $vf15, $vf29, $Q\n"
        :
        : "r"(sphere), "r"(start), "r"(end)
        : "memory");
}

/**
 * @brief Start the square root of the discriminant vu0_segment_sphere_setup left in vf14.x and store vf14.
 * @param discriminant Aligned destination.
 * @see vu0_segment_sphere_setup.
 */
static inline void vu0_segment_sphere_store_discriminant(void* discriminant)
{
    asm __volatile__(
        "vsqrt      $Q, $vf14x\n"
        "sqc2       $vf14, 0x0(%0)\n"
        :
        : "r"(discriminant)
        : "memory");
}

/**
 * @brief Store the fractions along the segment where it enters and leaves the sphere, in x of each destination.
 * @param leave Aligned destination for the larger fraction.
 * @param enter Aligned destination for the smaller fraction.
 * @see vu0_segment_sphere_setup.
 */
static inline void vu0_segment_sphere_fractions(void* leave, void* enter)
{
    asm __volatile__(
        "vmula.x    $ACC, $vf15, $vf12\n"
        "vmaddq.x   $vf17, $vf15, $Q\n"
        "vmula.x    $ACC, $vf15, $vf12\n"
        "vmsubq.x   $vf18, $vf15, $Q\n"
        "sqc2       $vf17, 0x0(%0)\n"
        "sqc2       $vf18, 0x0(%1)\n"
        :
        : "r"(leave), "r"(enter)
        : "memory");
}

/**
 * @brief Move a box centre by the matrix in vf1-vf4 and leave a ray's origin relative to it in vf10, with the origin
 *        in vf12 and the direction in vf11.
 * @param origin Aligned ray origin.
 * @param centre Aligned box centre.
 * @param direction Aligned ray direction.
 * @see Lib's ray-box test at 0x45C420, which runs inside a pass that loaded vf1-vf4.
 */
static inline void vu0_box_ray_offset(const void* origin, const void* centre, const void* direction)
{
    asm __volatile__(
        "lqc2       $vf12, 0x0(%0)\n"
        "lqc2       $vf15, 0x0(%1)\n"
        "lqc2       $vf11, 0x0(%2)\n"
        "vmulax.xyzw $ACC, $vf1, $vf15x\n"
        "vmadday.xyzw $ACC, $vf2, $vf15y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf15z\n"
        "vmaddw.xyzw $vf15, $vf4, $vf0w\n"
        "vsub.xyz   $vf10, $vf12, $vf15\n"
        :
        : "r"(origin), "r"(centre), "r"(direction)
        : "memory");
}

/**
 * @brief Project the ray offset in vf10 and direction in vf11 onto the box axes in vf1-vf3, into vf14 and vf13.
 * @see vu0_box_ray_offset.
 */
static inline void vu0_box_ray_project(void)
{
    asm __volatile__(
        "vmul.xyz   $vf20, $vf10, $vf1\n"
        "vmul.xyz   $vf21, $vf10, $vf2\n"
        "vmul.xyz   $vf22, $vf10, $vf3\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vadday.x   $ACC, $vf20, $vf20y\n"
        "vmaddz.x   $vf14, $vf31, $vf20z\n"
        "vaddax.y   $ACC, $vf21, $vf21x\n"
        "vmaddz.y   $vf14, $vf31, $vf21z\n"
        "vmul.xyz   $vf20, $vf11, $vf1\n"
        "vaddax.z   $ACC, $vf22, $vf22x\n"
        "vmaddy.z   $vf14, $vf31, $vf22y\n"
        "vmul.xyz   $vf21, $vf11, $vf2\n"
        "vmul.xyz   $vf22, $vf11, $vf3\n"
        "vadday.x   $ACC, $vf20, $vf20y\n"
        "vmaddz.x   $vf13, $vf31, $vf20z\n"
        "vaddax.y   $ACC, $vf21, $vf21x\n"
        "vmaddz.y   $vf13, $vf31, $vf21z\n"
        "vaddax.z   $ACC, $vf22, $vf22x\n"
        "vmaddy.z   $vf13, $vf31, $vf22y\n");
}

/**
 * @brief Store the projected ray offset (vf14) and direction (vf13).
 * @param offset Aligned destination for the offset.
 * @param direction Aligned destination for the direction.
 * @see vu0_box_ray_project.
 */
static inline void vu0_store_box_ray_projection(void* offset, void* direction)
{
    asm __volatile__(
        "sqc2 $vf14, 0x0(%0)\n"
        "sqc2 $vf13, 0x0(%1)\n"
        :
        : "r"(offset), "r"(direction)
        : "memory");
}

/**
 * @brief Leave in vf20 and vf21 the points along the ray (origin vf12, direction vf11) at the fractions in vf16.x
 *        and vf16.y.
 * @see vu0_box_ray_offset.
 */
static inline void vu0_ray_points_at_fractions(void)
{
    asm __volatile__(
        "vmulaw.xyz $ACC, $vf12, $vf0w\n"
        "vmaddx.xyz $vf20, $vf11, $vf16x\n"
        "vmulaw.xyz $ACC, $vf12, $vf0w\n"
        "vmaddy.xyz $vf21, $vf11, $vf16y\n");
}

/**
 * @brief Leave in vf20 the point along the ray (origin vf12, direction vf11) at the fraction in vf16.y.
 * @see vu0_box_ray_offset.
 */
static inline void vu0_ray_point_at_far_fraction(void)
{
    asm __volatile__(
        "vmulaw.xyz $ACC, $vf12, $vf0w\n"
        "vmaddy.xyz $vf20, $vf11, $vf16y\n");
}

/**
 * @brief Store vf20.
 * @param vector Aligned destination.
 * @see vu0_ray_points_at_fractions.
 */
static inline void vu0_store_vf20(void* vector)
{
    asm __volatile__("sqc2 $vf20, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Store vf20 and vf21 to consecutive quadwords.
 * @param vectors Aligned destination for two quadwords.
 * @see vu0_ray_points_at_fractions.
 */
static inline void vu0_store_vf20_vf21(void* vectors)
{
    asm __volatile__(
        "sqc2 $vf20, 0x0(%0)\n"
        "sqc2 $vf21, 0x10(%0)\n"
        :
        : "r"(vectors)
        : "memory");
}

/**
 * @brief Move a sphere by the matrix in vf1-vf4 and set up where a ray (from its origin on) meets it.
 *
 * Leaves the discriminant in vf18.x, the projection terms in vf15 and vf22, the reciprocal of the direction length
 * squared in vf19.x, the origin in vf12 and the direction in vf14.
 * @param origin Aligned ray origin.
 * @param direction Aligned ray direction.
 * @see Lib's ray-sphere test at 0x45C770, which loads the sphere with vu0_load_vf10 first.
 */
static inline void vu0_ray_sphere_setup(const void* origin, const void* direction)
{
    asm __volatile__(
        "vmulax.xyzw $ACC, $vf1, $vf10x\n"
        "vmadday.xyzw $ACC, $vf2, $vf10y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf10z\n"
        "vmaddw.xyzw $vf11, $vf4, $vf0w\n"
        "vmul.w     $vf10, $vf10, $vf10\n"
        "lqc2       $vf12, 0x0(%0)\n"
        "lqc2       $vf14, 0x0(%1)\n"
        "vsub.xyz   $vf13, $vf12, $vf11\n"
        "vmul.xyz   $vf23, $vf14, $vf14\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vsubw.xyz  $vf30, $vf0, $vf0w\n"
        "vmul.xyz   $vf24, $vf14, $vf13\n"
        "vmul.xyz   $vf25, $vf13, $vf13\n"
        "vadday.x   $ACC, $vf23, $vf23y\n"
        "vmaddz.x   $vf15, $vf31, $vf23z\n"
        "vadday.x   $ACC, $vf24, $vf24y\n"
        "vmaddz.x   $vf16, $vf31, $vf24z\n"
        "vadday.x   $ACC, $vf25, $vf25y\n"
        "vdiv       $Q, $vf0w, $vf15x\n"
        "vmaddaz.x  $ACC, $vf31, $vf25z\n"
        "vmsubw.x   $vf17, $vf31, $vf10w\n"
        "vmul.x     $vf22, $vf16, $vf30\n"
        "vnop\n"
        "vmula.x    $ACC, $vf16, $vf16\n"
        "vmsub.x    $vf18, $vf15, $vf17\n"
        "vaddq.x    $vf19, $vf0, $Q\n"
        :
        : "r"(origin), "r"(direction)
        : "memory");
}

/**
 * @brief Load vf10.
 * @param vector Aligned source.
 * @see vu0_ray_sphere_setup.
 */
static inline void vu0_load_vf10(const void* vector)
{
    asm __volatile__("lqc2 $vf10, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Store the discriminant vu0_ray_sphere_setup left in vf18 and start its square root.
 *
 * TODO: The game computes the root's address too but never stores to it; I've kept that as an unused operand.
 * @param root Unused.
 * @param discriminant Aligned destination for vf18.
 * @see vu0_ray_sphere_setup.
 */
static inline void vu0_ray_sphere_store_discriminant(void* root, void* discriminant)
{
    asm __volatile__(
        "sqc2       $vf18, 0x0(%1)\n"
        "vsqrt      $Q, $vf18x\n"
        :
        : "r"(root), "r"(discriminant)
        : "memory");
}

/**
 * @brief Leave the fractions where the ray enters and leaves the sphere in vf20.x and vf21.x.
 * @see vu0_ray_sphere_setup.
 */
static inline void vu0_ray_sphere_fractions(void)
{
    asm __volatile__(
        "vwaitq\n"
        "vsubq.x    $vf20, $vf22, $Q\n"
        "vaddq.x    $vf21, $vf22, $Q\n"
        "vnop\n"
        "vnop\n"
        "vmul.x     $vf20, $vf20, $vf19\n"
        "vmul.x     $vf21, $vf21, $vf19\n");
}

/**
 * @brief Store the fractions vu0_ray_sphere_fractions left in vf20 and vf21.
 * @param enter Aligned destination for vf20.
 * @param leave Aligned destination for vf21.
 * @see vu0_ray_sphere_fractions.
 */
static inline void vu0_store_ray_sphere_fractions(void* enter, void* leave)
{
    asm __volatile__(
        "sqc2 $vf20, 0x0(%0)\n"
        "sqc2 $vf21, 0x0(%1)\n"
        :
        : "r"(enter), "r"(leave)
        : "memory");
}

/**
 * @brief Leave in vf23 and vf24 the points along the ray (origin vf12, direction vf14) at the fractions in vf20.x and
 *        vf21.x.
 * @see vu0_ray_sphere_fractions.
 */
static inline void vu0_ray_sphere_points(void)
{
    asm __volatile__(
        "vmulaw.xyz $ACC, $vf12, $vf0w\n"
        "vmaddx.xyz $vf23, $vf14, $vf20x\n"
        "vmulaw.xyz $ACC, $vf12, $vf0w\n"
        "vmaddx.xyz $vf24, $vf14, $vf21x\n");
}

/**
 * @brief Leave in vf23 the point along the ray (origin vf12, direction vf14) at the fraction in vf20.x.
 * @see vu0_ray_sphere_fractions.
 */
static inline void vu0_ray_sphere_enter_point(void)
{
    asm __volatile__(
        "vmulaw.xyz $ACC, $vf12, $vf0w\n"
        "vmaddx.xyz $vf23, $vf14, $vf20x\n");
}

/**
 * @brief For a ray that grazes the sphere, leave the touching point in vf23 and its fraction in vf20.x.
 * @see vu0_ray_sphere_setup.
 */
static inline void vu0_ray_sphere_touch(void)
{
    asm __volatile__(
        "vdiv       $Q, $vf22x, $vf15x\n"
        "vwaitq\n"
        "vmulaw.xyz $ACC, $vf12, $vf0w\n"
        "vmaddq.xyz $vf23, $vf14, $Q\n"
        "vaddq.x    $vf20, $vf0, $Q\n");
}

/**
 * @brief Store vf23.
 * @param vector Aligned destination.
 * @see vu0_ray_sphere_points.
 */
static inline void vu0_store_vf23(void* vector)
{
    asm __volatile__("sqc2 $vf23, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Store vf23 and vf24 to consecutive quadwords.
 * @param vectors Aligned destination for two quadwords.
 * @see vu0_ray_sphere_points.
 */
static inline void vu0_store_vf23_vf24(void* vectors)
{
    asm __volatile__(
        "sqc2 $vf23, 0x0(%0)\n"
        "sqc2 $vf24, 0x10(%0)\n"
        :
        : "r"(vectors)
        : "memory");
}

/**
 * @brief Load a scale into vf5 and a matrix into vf1-vf4.
 * @param matrix Aligned four-row matrix.
 * @param scale Aligned scale.
 * @see Lib's segment tree test at 0x45B920, which loads them before calling its sphere test.
 */
static inline void vu0_load_matrix_and_scale(const void* matrix, const void* scale)
{
    asm __volatile__(
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf1, 0x0(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "lqc2 $vf4, 0x30(%0)\n"
        :
        : "r"(matrix), "r"(scale)
        : "memory");
}

/**
 * @brief Move a box centre by the matrix in vf1-vf4, leave a segment's start relative to it in vf10, and grow the
 *        half extents by vf5.y into vf17.
 *
 * Leaves the start in vf12 and the end in vf11.
 * @param centre Aligned box centre.
 * @param start Aligned segment start.
 * @param end Aligned segment end.
 * @param half_extents Aligned half extents in xyz.
 * @see Lib's segment-box test at 0x45B360, which runs inside a pass that loaded vf1-vf5.
 */
static inline void vu0_box_segment_offset(const void* centre, const void* start, const void* end,
                                          const void* half_extents)
{
    asm __volatile__(
        "lqc2       $vf15, 0x0(%0)\n"
        "lqc2       $vf12, 0x0(%1)\n"
        "lqc2       $vf11, 0x0(%2)\n"
        "lqc2       $vf17, 0x0(%3)\n"
        "vmulax.xyzw $ACC, $vf1, $vf15x\n"
        "vmadday.xyzw $ACC, $vf2, $vf15y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf15z\n"
        "vmaddw.xyzw $vf15, $vf4, $vf0w\n"
        "vsub.xyz   $vf10, $vf12, $vf15\n"
        "vaddy.xyz  $vf17, $vf17, $vf5y\n"
        :
        : "r"(centre), "r"(start), "r"(end), "r"(half_extents)
        : "memory");
}

/**
 * @brief Store vf17.
 * @param vector Aligned destination.
 * @see vu0_box_segment_offset.
 */
static inline void vu0_store_vf17(void* vector)
{
    asm __volatile__("sqc2 $vf17, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Turn the segment end in vf11 into the segment's direction from its start in vf12.
 * @see vu0_box_segment_offset.
 */
static inline void vu0_segment_direction(void)
{
    asm __volatile__("vsub.xyz $vf11, $vf11, $vf12\n");
}

/**
 * @brief Load a segment's start into vf12 and its direction to the end into vf15, with two fractions along it in
 *        vf14.x and vf14.y.
 * @param fractions Aligned fractions.
 * @param start Aligned segment start.
 * @param end Aligned segment end.
 * @see Lib's hit point lookup at 0x45DCC0.
 */
static inline void vu0_segment_load(const void* fractions, const void* start, const void* end)
{
    asm __volatile__(
        "lqc2       $vf14, 0x0(%0)\n"
        "lqc2       $vf12, 0x0(%1)\n"
        "lqc2       $vf13, 0x0(%2)\n"
        "vsub.xyz   $vf15, $vf13, $vf12\n"
        :
        : "r"(fractions), "r"(start), "r"(end)
        : "memory");
}

/**
 * @brief Leave in vf16 the point along the segment from vu0_segment_load at the fraction in vf14.x.
 * @see vu0_segment_load.
 */
static inline void vu0_segment_point_x(void)
{
    asm __volatile__(
        "vmulaw.xyz $ACC, $vf12, $vf0w\n"
        "vmaddx.xyz $vf16, $vf15, $vf14x\n");
}

/**
 * @brief Leave in vf16 the point along the segment from vu0_segment_load at the fraction in vf14.y.
 * @see vu0_segment_load.
 */
static inline void vu0_segment_point_y(void)
{
    asm __volatile__(
        "vmulaw.xyz $ACC, $vf12, $vf0w\n"
        "vmaddy.xyz $vf16, $vf15, $vf14y\n");
}

/**
 * @brief Store vf16.
 * @param vector Aligned destination.
 * @see vu0_segment_point_x.
 */
static inline void vu0_store_vf16(void* vector)
{
    asm __volatile__("sqc2 $vf16, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Move two boxes' centres and half extents by their matrices: the first by the matrix it loads into vf1-vf4,
 *        the second by the one it loads into vf5-vf8. Leaves the centres in vf9 and vf10 and the extents' absolute
 *        values in vf11 and vf12.
 * @param first_extents Aligned half extents of the first box.
 * @param second_extents Aligned half extents of the second box.
 * @param first_centre Aligned centre of the first box.
 * @param first_matrix Aligned matrix of the first box.
 * @param second_centre Aligned centre of the second box.
 * @param second_matrix Aligned matrix of the second box.
 * @see Lib's hit point lookup at 0x45DCC0.
 */
static inline void vu0_move_box_pair(const void* first_extents, const void* second_extents, const void* first_centre,
                                     const void* first_matrix, const void* second_centre, const void* second_matrix)
{
    asm __volatile__(
        "lqc2       $vf11, 0x0(%1)\n"
        "lqc2       $vf12, 0x0(%2)\n"
        "lqc2       $vf9, 0x0(%0)\n"
        "lqc2       $vf1, 0x0(%3)\n"
        "lqc2       $vf2, 0x10(%3)\n"
        "lqc2       $vf3, 0x20(%3)\n"
        "lqc2       $vf4, 0x30(%3)\n"
        "lqc2       $vf10, 0x0(%4)\n"
        "lqc2       $vf5, 0x0(%5)\n"
        "lqc2       $vf6, 0x10(%5)\n"
        "lqc2       $vf7, 0x20(%5)\n"
        "lqc2       $vf8, 0x30(%5)\n"
        "vmulax.xyzw $ACC, $vf1, $vf11x\n"
        "vmadday.xyzw $ACC, $vf2, $vf11y\n"
        "vmaddz.xyzw $vf11, $vf3, $vf11z\n"
        "vmulax.xyzw $ACC, $vf5, $vf12x\n"
        "vmadday.xyzw $ACC, $vf6, $vf12y\n"
        "vmaddz.xyzw $vf12, $vf7, $vf12z\n"
        "vabs.xyz   $vf11, $vf11\n"
        "vmulax.xyzw $ACC, $vf1, $vf9x\n"
        "vmadday.xyzw $ACC, $vf2, $vf9y\n"
        "vabs.xyz   $vf12, $vf12\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf9z\n"
        "vmaddw.xyzw $vf9, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf5, $vf10x\n"
        "vmadday.xyzw $ACC, $vf6, $vf10y\n"
        "vmaddaz.xyzw $ACC, $vf7, $vf10z\n"
        "vmaddw.xyzw $vf10, $vf8, $vf0w\n"
        :
        : "r"(first_centre), "r"(first_extents), "r"(second_extents), "r"(first_matrix), "r"(second_centre), "r"(second_matrix)
        : "memory");
}

/**
 * @brief Store the centres and half extents vu0_move_box_pair left in vf9-vf12.
 * @param first_centre Aligned destination for vf9.
 * @param second_centre Aligned destination for vf10.
 * @param first_extents Aligned destination for vf11.
 * @param second_extents Aligned destination for vf12.
 * @see vu0_move_box_pair.
 */
static inline void vu0_store_box_pair(void* first_centre, void* second_centre, void* first_extents,
                                      void* second_extents)
{
    asm __volatile__(
        "sqc2 $vf9, 0x0(%0)\n"
        "sqc2 $vf10, 0x0(%1)\n"
        "sqc2 $vf11, 0x0(%2)\n"
        "sqc2 $vf12, 0x0(%3)\n"
        :
        : "r"(first_centre), "r"(second_centre), "r"(first_extents), "r"(second_extents)
        : "memory");
}

/**
 * @brief Start a box-box separating axis test: move both boxes by the matrices in vf1-vf4 and vf5-vf8, scale their
 *        half extents by vf9.x and vf9.y, and test the first box's x axis.
 *
 * Each stage leaves the projected centre distance in vf18 and the summed projected extents in vf20.
 * @param first_centre Aligned centre of the first box.
 * @param first_extents Aligned half extents of the first box.
 * @param second_centre Aligned centre of the second box.
 * @param second_extents Aligned half extents of the second box.
 * @see Lib's box-box test at 0x45E400, which runs inside a pass that loaded vf1-vf9.
 */
static inline void vu0_box_box_axis_1(const void* first_centre, const void* first_extents, const void* second_centre,
                                      const void* second_extents)
{
    asm __volatile__(
        "lqc2       $vf10, 0x0(%0)\n"
        "lqc2       $vf11, 0x0(%2)\n"
        "vmulax.xyzw $ACC, $vf1, $vf10x\n"
        "vmadday.xyzw $ACC, $vf2, $vf10y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf10z\n"
        "vmaddw.xyzw $vf13, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf5, $vf11x\n"
        "vmadday.xyzw $ACC, $vf6, $vf11y\n"
        "vmaddaz.xyzw $ACC, $vf7, $vf11z\n"
        "vmaddw.xyzw $vf14, $vf8, $vf0w\n"
        "vsub.xyz   $vf16, $vf14, $vf13\n"
        "lqc2       $vf24, 0x0(%1)\n"
        "lqc2       $vf25, 0x0(%3)\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vmulx.xyz  $vf24, $vf24, $vf9x\n"
        "vmuly.xyz  $vf25, $vf25, $vf9y\n"
        "vmul.xyz   $vf26, $vf1, $vf5\n"
        "vmul.xyz   $vf27, $vf1, $vf6\n"
        "vmul.xyz   $vf28, $vf1, $vf7\n"
        "vmul.xyz   $vf29, $vf1, $vf16\n"
        "vmulax.x   $ACC, $vf31, $vf26x\n"
        "vmadday.x  $ACC, $vf31, $vf26y\n"
        "vmaddz.x   $vf13, $vf31, $vf26z\n"
        "vmulax.y   $ACC, $vf31, $vf27x\n"
        "vmadday.y  $ACC, $vf31, $vf27y\n"
        "vmaddz.y   $vf13, $vf31, $vf27z\n"
        "vmulax.z   $ACC, $vf31, $vf28x\n"
        "vmadday.z  $ACC, $vf31, $vf28y\n"
        "vmaddz.z   $vf13, $vf31, $vf28z\n"
        "vmulax.x   $ACC, $vf31, $vf29x\n"
        "vmadday.x  $ACC, $vf31, $vf29y\n"
        "vmaddz.x   $vf17, $vf31, $vf29z\n"
        "vmul.xyz   $vf26, $vf2, $vf5\n"
        "vmul.xyz   $vf27, $vf2, $vf6\n"
        "vabs.xyz   $vf21, $vf13\n"
        "vabs.xyz   $vf18, $vf17\n"
        "vmul.xyz   $vf28, $vf2, $vf7\n"
        "vmul.xyz   $vf29, $vf2, $vf16\n"
        "vmul.xyz   $vf30, $vf25, $vf21\n"
        "vmulax.x   $ACC, $vf31, $vf26x\n"
        "vmadday.x  $ACC, $vf31, $vf26y\n"
        "vmaddz.x   $vf14, $vf31, $vf26z\n"
        "vmulax.x   $ACC, $vf31, $vf30x\n"
        "vmadday.x  $ACC, $vf31, $vf30y\n"
        "vmadda.x   $ACC, $vf31, $vf24\n"
        "vmaddz.x   $vf20, $vf31, $vf30z\n"
        "vmulax.y   $ACC, $vf31, $vf27x\n"
        "vmadday.y  $ACC, $vf31, $vf27y\n"
        "vmaddz.y   $vf14, $vf31, $vf27z\n"
        :
        : "r"(first_centre), "r"(first_extents), "r"(second_centre), "r"(second_extents)
        : "memory");
}

/**
 * @brief Box-box separating axis test stage 2: the first box's y axis.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_2(void)
{
    asm __volatile__(
        "vmulax.z   $ACC, $vf31, $vf28x\n"
        "vmadday.z  $ACC, $vf31, $vf28y\n"
        "vmaddz.z   $vf14, $vf31, $vf28z\n"
        "vmulax.y   $ACC, $vf31, $vf29x\n"
        "vmadday.y  $ACC, $vf31, $vf29y\n"
        "vmaddz.y   $vf17, $vf31, $vf29z\n"
        "vmul.xyz   $vf26, $vf3, $vf5\n"
        "vmul.xyz   $vf27, $vf3, $vf6\n"
        "vabs.xyz   $vf22, $vf14\n"
        "vabs.xyz   $vf18, $vf17\n"
        "vmul.xyz   $vf28, $vf3, $vf7\n"
        "vmul.xyz   $vf29, $vf3, $vf16\n"
        "vmul.xyz   $vf30, $vf25, $vf22\n"
        "vmulax.x   $ACC, $vf31, $vf26x\n"
        "vmadday.x  $ACC, $vf31, $vf26y\n"
        "vmaddz.x   $vf15, $vf31, $vf26z\n"
        "vmulax.y   $ACC, $vf31, $vf30x\n"
        "vmadday.y  $ACC, $vf31, $vf30y\n"
        "vmadda.y   $ACC, $vf31, $vf24\n"
        "vmaddz.y   $vf20, $vf31, $vf30z\n"
        "vmulax.y   $ACC, $vf31, $vf27x\n"
        "vmadday.y  $ACC, $vf31, $vf27y\n"
        "vmaddz.y   $vf15, $vf31, $vf27z\n");
}

/**
 * @brief Box-box separating axis test stage 3: the first box's z axis.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_3(void)
{
    asm __volatile__(
        "vmulax.z   $ACC, $vf31, $vf28x\n"
        "vmadday.z  $ACC, $vf31, $vf28y\n"
        "vmaddz.z   $vf15, $vf31, $vf28z\n"
        "vmulax.z   $ACC, $vf31, $vf29x\n"
        "vmadday.z  $ACC, $vf31, $vf29y\n"
        "vmaddz.z   $vf17, $vf31, $vf29z\n"
        "vmul.xyz   $vf26, $vf5, $vf16\n"
        "vmul.xyz   $vf27, $vf6, $vf16\n"
        "vabs.xyz   $vf23, $vf15\n"
        "vabs.xyz   $vf18, $vf17\n"
        "vmul.xyz   $vf28, $vf7, $vf16\n"
        "vmul.xyz   $vf30, $vf25, $vf23\n"
        "vmulax.z   $ACC, $vf31, $vf30x\n"
        "vmadday.z  $ACC, $vf31, $vf30y\n"
        "vmadda.z   $ACC, $vf31, $vf24\n"
        "vmaddz.z   $vf20, $vf31, $vf30z\n");
}

/**
 * @brief Box-box separating axis test stage 4: the second box's three axes.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_4(void)
{
    asm __volatile__(
        "vmulax.x   $ACC, $vf31, $vf26x\n"
        "vmadday.x  $ACC, $vf31, $vf26y\n"
        "vmaddz.x   $vf18, $vf31, $vf26z\n"
        "vmulax.y   $ACC, $vf31, $vf27x\n"
        "vmadday.y  $ACC, $vf31, $vf27y\n"
        "vmaddz.y   $vf18, $vf31, $vf27z\n"
        "vmulax.z   $ACC, $vf31, $vf28x\n"
        "vmadday.z  $ACC, $vf31, $vf28y\n"
        "vmaddz.z   $vf18, $vf31, $vf28z\n"
        "vabs.xyz   $vf18, $vf18\n"
        "vmulax.x   $ACC, $vf21, $vf24x\n"
        "vmadday.x  $ACC, $vf22, $vf24y\n"
        "vmadda.x   $ACC, $vf31, $vf25\n"
        "vmaddz.x   $vf20, $vf23, $vf24z\n"
        "vmulax.y   $ACC, $vf21, $vf24x\n"
        "vmadday.y  $ACC, $vf22, $vf24y\n"
        "vmadda.y   $ACC, $vf31, $vf25\n"
        "vmaddz.y   $vf20, $vf23, $vf24z\n"
        "vmulax.z   $ACC, $vf21, $vf24x\n"
        "vmadday.z  $ACC, $vf22, $vf24y\n"
        "vmadda.z   $ACC, $vf31, $vf25\n"
        "vmaddz.z   $vf20, $vf23, $vf24z\n");
}

/**
 * @brief Box-box separating axis test stage 5: cross axis 1.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_5(void)
{
    asm __volatile__(
        "vmulaz.x   $ACC, $vf14, $vf17z\n"
        "vmsuby.x   $vf26, $vf15, $vf17y\n"
        "vmulay.x   $ACC, $vf23, $vf24y\n"
        "vmaddz.x   $vf27, $vf22, $vf24z\n"
        "vmulaz.y   $ACC, $vf25, $vf21z\n"
        "vmaddz.y   $vf28, $vf22, $vf25z\n"
        "vabs.x     $vf18, $vf26\n"
        "vmulaz.y   $ACC, $vf14, $vf17z\n"
        "vmsuby.y   $vf26, $vf15, $vf17y\n"
        "vaddy.x    $vf20, $vf27, $vf28y\n");
}

/**
 * @brief Box-box separating axis test stage 6: cross axis 2.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_6(void)
{
    asm __volatile__(
        "vmulay.y   $ACC, $vf23, $vf24y\n"
        "vmaddz.y   $vf27, $vf22, $vf24z\n"
        "vmulax.z   $ACC, $vf21, $vf25x\n"
        "vmaddx.z   $vf28, $vf25, $vf21x\n"
        "vabs.xyz   $vf18, $vf26\n"
        "vmulaz.z   $ACC, $vf14, $vf17z\n"
        "vmsuby.z   $vf26, $vf15, $vf17y\n"
        "vaddz.y    $vf20, $vf27, $vf28z\n");
}

/**
 * @brief Box-box separating axis test stage 7: cross axis 3.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_7(void)
{
    asm __volatile__(
        "vmulay.z   $ACC, $vf23, $vf24y\n"
        "vmaddz.z   $vf27, $vf22, $vf24z\n"
        "vmulax.y   $ACC, $vf21, $vf25x\n"
        "vmaddx.y   $vf28, $vf25, $vf21x\n"
        "vabs.xyz   $vf18, $vf26\n"
        "vmulax.x   $ACC, $vf15, $vf17x\n"
        "vmsubz.x   $vf26, $vf13, $vf17z\n"
        "vaddy.z    $vf20, $vf27, $vf28y\n");
}

/**
 * @brief Box-box separating axis test stage 8: cross axis 4.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_8(void)
{
    asm __volatile__(
        "vmulax.x   $ACC, $vf23, $vf24x\n"
        "vmaddz.x   $vf27, $vf21, $vf24z\n"
        "vmulaz.y   $ACC, $vf25, $vf22z\n"
        "vmaddz.y   $vf28, $vf22, $vf25z\n"
        "vabs.xyz   $vf18, $vf26\n"
        "vmulax.y   $ACC, $vf15, $vf17x\n"
        "vmsubz.y   $vf26, $vf13, $vf17z\n"
        "vaddy.x    $vf20, $vf27, $vf28y\n");
}

/**
 * @brief Box-box separating axis test stage 9: cross axis 5.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_9(void)
{
    asm __volatile__(
        "vmulax.y   $ACC, $vf23, $vf24x\n"
        "vmaddz.y   $vf27, $vf21, $vf24z\n"
        "vmulaz.x   $ACC, $vf25, $vf22z\n"
        "vmaddz.x   $vf28, $vf22, $vf25z\n"
        "vabs.xyz   $vf18, $vf26\n"
        "vmulax.z   $ACC, $vf15, $vf17x\n"
        "vmsubz.z   $vf26, $vf13, $vf17z\n"
        "vaddx.y    $vf20, $vf27, $vf28x\n");
}

/**
 * @brief Box-box separating axis test stage 10: cross axis 6.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_10(void)
{
    asm __volatile__(
        "vmulax.z   $ACC, $vf23, $vf24x\n"
        "vmaddz.z   $vf27, $vf21, $vf24z\n"
        "vmulay.x   $ACC, $vf25, $vf22y\n"
        "vmaddy.x   $vf28, $vf22, $vf25y\n"
        "vabs.xyz   $vf18, $vf26\n"
        "vmulay.x   $ACC, $vf13, $vf17y\n"
        "vmsubx.x   $vf26, $vf14, $vf17x\n"
        "vaddx.z    $vf20, $vf27, $vf28x\n");
}

/**
 * @brief Box-box separating axis test stage 11: cross axis 7.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_11(void)
{
    asm __volatile__(
        "vmulax.x   $ACC, $vf22, $vf24x\n"
        "vmaddy.x   $vf27, $vf21, $vf24y\n"
        "vmulaz.y   $ACC, $vf25, $vf23z\n"
        "vmaddz.y   $vf28, $vf23, $vf25z\n"
        "vabs.xyz   $vf18, $vf26\n"
        "vmulay.y   $ACC, $vf13, $vf17y\n"
        "vmsubx.y   $vf26, $vf14, $vf17x\n"
        "vaddy.x    $vf20, $vf27, $vf28y\n");
}

/**
 * @brief Box-box separating axis test stage 12: cross axis 8.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_12(void)
{
    asm __volatile__(
        "vmulax.y   $ACC, $vf22, $vf24x\n"
        "vmaddy.y   $vf27, $vf21, $vf24y\n"
        "vmulaz.x   $ACC, $vf25, $vf23z\n"
        "vmaddz.x   $vf28, $vf23, $vf25z\n"
        "vabs.xyz   $vf18, $vf26\n"
        "vmulay.z   $ACC, $vf13, $vf17y\n"
        "vmsubx.z   $vf26, $vf14, $vf17x\n"
        "vaddx.y    $vf20, $vf27, $vf28x\n");
}

/**
 * @brief Box-box separating axis test stage 13: cross axis 9.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_box_box_axis_13(void)
{
    asm __volatile__(
        "vmulax.z   $ACC, $vf22, $vf24x\n"
        "vmaddy.z   $vf27, $vf21, $vf24y\n"
        "vmulay.x   $ACC, $vf25, $vf23y\n"
        "vmaddy.x   $vf28, $vf23, $vf25y\n"
        "vabs.xyz   $vf18, $vf26\n"
        "vaddx.z    $vf20, $vf27, $vf28x\n");
}

/**
 * @brief Store a box-box stage's projected distance (vf18) and summed extents (vf20).
 * @param distance Aligned destination for vf18.
 * @param extent Aligned destination for vf20.
 * @see vu0_box_box_axis_1.
 */
static inline void vu0_store_box_box_axis(void* distance, void* extent)
{
    asm __volatile__(
        "sqc2 $vf18, 0x0(%0)\n"
        "sqc2 $vf20, 0x0(%1)\n"
        :
        : "r"(distance), "r"(extent)
        : "memory");
}

/**
 * @brief Load two matrices into vf1-vf4 and vf5-vf8 and their scales into vf9.
 * @param first_matrix Aligned matrix of the first shape.
 * @param second_matrix Aligned matrix of the second shape.
 * @param scales Aligned scales: x for the first shape, y for the second.
 * @see Lib's two-shape pass setup at 0x45F2B0.
 */
static inline void vu0_load_shape_pair(const void* first_matrix, const void* second_matrix, const void* scales)
{
    asm __volatile__(
        "lqc2 $vf1, 0x0(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "lqc2 $vf4, 0x30(%0)\n"
        "lqc2 $vf5, 0x0(%1)\n"
        "lqc2 $vf6, 0x10(%1)\n"
        "lqc2 $vf7, 0x20(%1)\n"
        "lqc2 $vf8, 0x30(%1)\n"
        "lqc2 $vf9, 0x0(%2)\n"
        :
        : "r"(first_matrix), "r"(second_matrix), "r"(scales)
        : "memory");
}

#endif
