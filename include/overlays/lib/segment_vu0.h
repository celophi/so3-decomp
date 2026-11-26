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

/**
 * @brief Load two segments (start, axis) and compute in VU0 the dot products of the closest-point system: vf10 = start offset, vf12 = first axis squared, vf14 = minus the axes' dot, vf16 = second axis squared, vf18 = offset . first axis, vf20 = offset squared, vf21 = |determinant|; vf30 is -1 and vf31 is 1.
 * @param first First segment's start.
 * @param second Second segment's start.
 * @param first_axis First segment's axis.
 * @param second_axis Second segment's axis.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CA270 in Lib.
 */
static inline void vu0_segment_pair_dots(const void* first, const void* second, const void* first_axis, const void* second_axis)
{
    asm __volatile__("lqc2 $vf1, 0x0(%0)\n"
                     "lqc2 $vf2, 0x0(%1)\n"
                     "lqc2 $vf3, 0x0(%2)\n"
                     "lqc2 $vf4, 0x0(%3)\n"
                     "vsub.xyz $vf10, $vf1, $vf2\n"
                     "vmul.xyz $vf11, $vf3, $vf3\n"
                     "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
                     "vsubw.xyz $vf30, $vf0, $vf0w\n"
                     "vmul.xyz $vf13, $vf3, $vf4\n"
                     "vadday.x $ACC, $vf11, $vf11y\n"
                     "vmaddz.x $vf12, $vf31, $vf11z\n"
                     "vmul.xyz $vf15, $vf4, $vf4\n"
                     "vadday.x $ACC, $vf13, $vf13y\n"
                     "vmaddz.x $vf14, $vf31, $vf13z\n"
                     "vmul.xyz $vf17, $vf10, $vf3\n"
                     "vadday.x $ACC, $vf15, $vf15y\n"
                     "vmaddz.x $vf16, $vf31, $vf15z\n"
                     "vmul.xyz $vf19, $vf10, $vf10\n"
                     "vmul.x $vf14, $vf14, $vf30\n"
                     "vadday.x $ACC, $vf17, $vf17y\n"
                     "vmaddz.x $vf18, $vf31, $vf17z\n"
                     "vmula.x $ACC, $vf12, $vf16\n"
                     "vmsub.x $vf21, $vf14, $vf14\n"
                     "vadday.x $ACC, $vf19, $vf19y\n"
                     "vmaddz.x $vf20, $vf31, $vf19z\n"
                     "vabs.x $vf21, $vf21" : : "r"(first), "r"(second), "r"(first_axis), "r"(second_axis) : "memory");
}

/**
 * @brief Store the start offset (vf10) and set vf29 to minus the second axis.
 * @param offset 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CA270 in Lib.
 */
static inline void vu0_segment_pair_store_offset(void* offset)
{
    asm __volatile__("vmulx.xyz $vf29, $vf4, $vf30x\n"
                     "sqc2 $vf10, 0x0(%0)" : : "r"(offset) : "memory");
}

/**
 * @brief Start the offset . (minus second axis) product in vf22.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CA270 in Lib.
 */
static inline void vu0_segment_pair_offset_second()
{
    asm __volatile__("vmul.xyz $vf22, $vf10, $vf29");
}

/**
 * @brief Finish vf23 = minus offset . second axis, then the unscaled fractions vf24 (first) and vf25 (second).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_004CA270 in Lib.
 */
static inline void vu0_segment_pair_solve()
{
    asm __volatile__("vadday.x $ACC, $vf22, $vf22y\n"
                     "vmaddz.x $vf23, $vf31, $vf22z\n"
                     "vmula.x $ACC, $vf14, $vf18\n"
                     "vmsub.x $vf25, $vf12, $vf23\n"
                     "vmula.x $ACC, $vf14, $vf23\n"
                     "vmsub.x $vf24, $vf16, $vf18");
}

/**
 * @brief Read vf12.x.
 * @return The value.
 * @see vu0_segment_pair_dots.
 */
static inline float vu0_read_vf12_x()
{
    float value;
    asm __volatile__("qmfc2.ni %0, $vf12" : "=r"(value));
    return value;
}

/**
 * @brief Read vf14.x.
 * @return The value.
 * @see vu0_segment_pair_dots.
 */
static inline float vu0_read_vf14_x()
{
    float value;
    asm __volatile__("qmfc2.ni %0, $vf14" : "=r"(value));
    return value;
}

/**
 * @brief Read vf16.x.
 * @return The value.
 * @see vu0_segment_pair_dots.
 */
static inline float vu0_read_vf16_x()
{
    float value;
    asm __volatile__("qmfc2.ni %0, $vf16" : "=r"(value));
    return value;
}

/**
 * @brief Read vf18.x.
 * @return The value.
 * @see vu0_segment_pair_dots.
 */
static inline float vu0_read_vf18_x()
{
    float value;
    asm __volatile__("qmfc2.ni %0, $vf18" : "=r"(value));
    return value;
}

/**
 * @brief Read vf20.x.
 * @return The value.
 * @see vu0_segment_pair_dots.
 */
static inline float vu0_read_vf20_x()
{
    float value;
    asm __volatile__("qmfc2.ni %0, $vf20" : "=r"(value));
    return value;
}

/**
 * @brief Read vf21.x.
 * @return The value.
 * @see vu0_segment_pair_dots.
 */
static inline float vu0_read_vf21_x()
{
    float value;
    asm __volatile__("qmfc2.ni %0, $vf21" : "=r"(value));
    return value;
}

/**
 * @brief Read vf23.x.
 * @return The value.
 * @see vu0_segment_pair_dots.
 */
static inline float vu0_read_vf23_x()
{
    float value;
    asm __volatile__("qmfc2.ni %0, $vf23" : "=r"(value));
    return value;
}

/**
 * @brief Read vf24.x.
 * @return The value.
 * @see vu0_segment_pair_dots.
 */
static inline float vu0_read_vf24_x()
{
    float value;
    asm __volatile__("qmfc2.ni %0, $vf24" : "=r"(value));
    return value;
}

/**
 * @brief Read vf25.x.
 * @return The value.
 * @see vu0_segment_pair_dots.
 */
static inline float vu0_read_vf25_x()
{
    float value;
    asm __volatile__("qmfc2.ni %0, $vf25" : "=r"(value));
    return value;
}

#endif
