#ifndef SO3_OVERLAYS_LIB_SEGMENT_VU0_H
#define SO3_OVERLAYS_LIB_SEGMENT_VU0_H

/**
 * @brief Start projecting a point onto a segment: vf10 = point - start, vf3 = axis, vf14.x = |axis|^2, vf31 = ones.
 * @param point Aligned point.
 * @param start Aligned segment start.
 * @param axis Aligned segment axis.
 * @see Lib's point-segment distance at 0x4CA180.
 */
static inline void vu0_segment_project_start(const void* point, const void* start, const void* axis)
{
    asm __volatile__(
        "lqc2       $vf1, 0x0(%0)\n"
        "lqc2       $vf2, 0x0(%1)\n"
        "lqc2       $vf3, 0x0(%2)\n"
        "vsub.xyz   $vf10, $vf1, $vf2\n"
        "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
        "vmul.xyz   $vf13, $vf3, $vf3\n"
        "vmul.xyz   $vf11, $vf10, $vf3\n"
        "vadday.x   $ACC, $vf13, $vf13y\n"
        "vmaddz.x   $vf14, $vf31, $vf13z\n"
        :
        : "r"(point), "r"(start), "r"(axis)
        : "memory");
}

/**
 * @brief Store dot(point - start, axis) (vf12.x) in x of the destination.
 * @param output Aligned destination.
 * @see vu0_segment_project_start.
 */
static inline void vu0_segment_store_dot(void* output)
{
    asm __volatile__(
        "vadday.x   $ACC, $vf11, $vf11y\n"
        "vmaddz.x   $vf12, $vf31, $vf11z\n"
        "sqc2       $vf12, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief vf16 = vf10 squared per component (the offset from the start).
 * @see vu0_segment_project_start.
 */
static inline void vu0_segment_square_start_offset(void)
{
    asm __volatile__("vmul.xyz $vf16, $vf10, $vf10\n");
}

/**
 * @brief Start dividing the dot product by |axis|^2 and store |axis|^2 (vf14) for the comparison.
 * @param output Aligned destination.
 * @see vu0_segment_project_start.
 */
static inline void vu0_segment_start_fraction(void* output)
{
    asm __volatile__(
        "vdiv       $Q, $vf12x, $vf14x\n"
        "sqc2       $vf14, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief vf15 = offset from the segment's end (vf10 - vf3).
 * @see vu0_segment_project_start.
 */
static inline void vu0_segment_end_offset(void)
{
    asm __volatile__("vsub.xyz $vf15, $vf10, $vf3\n");
}

/**
 * @brief vf15 = offset from the projected point; store the fraction (Q) in x of the destination.
 * @param output Aligned destination.
 * @see vu0_segment_start_fraction.
 */
static inline void vu0_segment_inner_offset(void* output)
{
    asm __volatile__(
        "vaddax.xyz $ACC, $vf10, $vf0x\n"
        "vwaitq\n"
        "vaddq.x    $vf12, $vf0, $Q\n"
        "vmsubq.xyz $vf15, $vf3, $Q\n"
        "sqc2       $vf12, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief vf16 = vf15 squared per component.
 * @see vu0_segment_inner_offset.
 */
static inline void vu0_segment_square_offset(void)
{
    asm __volatile__("vmul.xyz $vf16, $vf15, $vf15\n");
}

/**
 * @brief Store the squared length of the offset (vf17.x = sum of vf16) in x of the destination.
 * @param output Aligned destination.
 * @see vu0_segment_square_offset.
 */
static inline void vu0_segment_store_distance(void* output)
{
    asm __volatile__(
        "vadday.x   $ACC, $vf16, $vf16y\n"
        "vmaddz.x   $vf17, $vf31, $vf16z\n"
        "sqc2       $vf17, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

#endif
