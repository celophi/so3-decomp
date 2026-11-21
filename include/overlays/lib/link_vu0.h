#ifndef SO3_OVERLAYS_LIB_LINK_VU0_H
#define SO3_OVERLAYS_LIB_LINK_VU0_H

/**
 * @brief Load vf2.
 * @param vector Aligned source.
 * @see lqc2 in Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf). Lib's link solvers from 0x425490 keep
 *      their constants there.
 */
static inline void vu0_load_vf2(const void* vector)
{
    asm __volatile__("lqc2 $vf2, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Put a float in vf7.x.
 * @param value Value.
 * @see qmtc2 in Sony's EE/VU manual. Lib's link solvers from 0x425490.
 */
static inline void vu0_set_vf7(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf7\n" : : "r"(value) : "memory");
}

/**
 * @brief Scale vf3.x by vf2.w.
 * @see Lib's link solver at 0x425B40.
 */
static inline void vu0_link_scale_vf3(void)
{
    asm __volatile__("vmulw.x $vf3, $vf3, $vf2w\n");
}

/**
 * @brief Leave the correction (vf1 times vf3.x) in vf10 and minus the weight in vf7.x in vf13.w.
 * @see Lib's link solver at 0x425B40.
 */
static inline void vu0_link_correction(void)
{
    asm __volatile__(
        "vmulx.xyz  $vf10, $vf1, $vf3x\n"
        "vsubx.w    $vf13, $vf0, $vf7x\n");
}

/**
 * @brief Move two free points apart along the correction in vf10: the first by -vf7.x of it (stored), the second
 *        by vf7.x (left in vf6 for vu0_store_vf6).
 * @param first Aligned first point, updated in place.
 * @param second Aligned second point.
 * @see Lib's link solver at 0x425B40.
 */
static inline void vu0_link_move_pair(void* first, const void* second)
{
    asm __volatile__(
        "lqc2       $vf5, 0x0(%0)\n"
        "lqc2       $vf6, 0x0(%1)\n"
        "vaddax.xyz $ACC, $vf5, $vf0x\n"
        "vmaddw.xyz $vf5, $vf10, $vf13w\n"
        "vaddax.xyz $ACC, $vf6, $vf0x\n"
        "vmaddx.xyz $vf6, $vf10, $vf7x\n"
        "sqc2       $vf5, 0x0(%0)\n"
        :
        : "r"(first), "r"(second)
        : "memory");
}

/**
 * @brief Store vf6.
 * @param vector Aligned destination.
 * @see vu0_link_move_pair.
 */
static inline void vu0_store_vf6(void* vector)
{
    asm __volatile__("sqc2 $vf6, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Load vf5.
 * @param vector Aligned source.
 * @see Lib's link solver at 0x425B40.
 */
static inline void vu0_load_vf5(const void* vector)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Start a sum with vf5 in ACC.
 * @see Lib's link solver at 0x425B40.
 */
static inline void vu0_link_accumulate_vf5(void)
{
    asm __volatile__("vmulaw.xyzw $ACC, $vf5, $vf0w\n");
}

/**
 * @brief Finish vf5 as ACC plus the correction in vf10 times vf2.z.
 * @see vu0_link_accumulate_vf5.
 */
static inline void vu0_link_add_scaled_z(void)
{
    asm __volatile__("vmaddz.xyz $vf5, $vf10, $vf2z\n");
}

/**
 * @brief Start dividing one by the weight in vf7.x.
 * @see Lib's link solver at 0x425B40.
 */
static inline void vu0_link_start_reciprocal(void)
{
    asm __volatile__("vdiv $Q, $vf0w, $vf7x\n");
}

/**
 * @brief Finish vf5 as ACC plus the correction in vf10 times the reciprocal in Q.
 * @see vu0_link_start_reciprocal.
 */
static inline void vu0_link_add_divided(void)
{
    asm __volatile__(
        "vwaitq\n"
        "vmaddq.xyz $vf5, $vf10, $Q\n");
}

/**
 * @brief Store vf5.
 * @param vector Aligned destination.
 * @see Lib's link solver at 0x425B40.
 */
static inline void vu0_store_vf5(void* vector)
{
    asm __volatile__("sqc2 $vf5, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Move a point by the matrix the caller left in vf24-vf27 into vf1.
 * @param point Aligned point.
 * @see Lib's shape pair tests from 0x425C90, which run inside a pass that loaded the other shape's inverse there.
 */
static inline void vu0_shape_point_to_local(const void* point)
{
    asm __volatile__(
        "lqc2       $vf1, 0x0(%0)\n"
        "vmulax.xyzw $ACC, $vf24, $vf1x\n"
        "vmadday.xyzw $ACC, $vf25, $vf1y\n"
        "vmaddaz.xyzw $ACC, $vf26, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf27, $vf0w\n"
        :
        : "r"(point)
        : "memory");
}

/**
 * @brief Put two radii in vf3.x and vf4.x and scale the local point in vf1 per axis by their sum over
 *        (second + scale * first).
 * @param first First radius (vf3.x).
 * @param second Second radius (vf4.x).
 * @param scale Aligned per-axis scale.
 * @see Lib's sphere-capsule test at 0x425C90.
 */
static inline void vu0_shape_scale_local_point(float first, float second, const void* scale)
{
    u32 scratch;

    asm __volatile__(
        "mfc1       %0, %1\n"
        "nop\n"
        "qmtc2.ni   %0, $vf3\n"
        "mfc1       %0, %2\n"
        "nop\n"
        "qmtc2.ni   %0, $vf4\n"
        "lqc2       $vf5, 0x0(%3)\n"
        "vadd.x     $vf6, $vf3, $vf4\n"
        "vaddax.xyzw $ACC, $vf0, $vf4x\n"
        "vmaddx.xyz $vf5, $vf5, $vf3x\n"
        "vdiv       $Q, $vf6x, $vf5x\n"
        "vwaitq\n"
        "vmulq.x    $vf1, $vf1, $Q\n"
        "vnop\n"
        "vnop\n"
        "vdiv       $Q, $vf6x, $vf5y\n"
        "vwaitq\n"
        "vmulq.y    $vf1, $vf1, $Q\n"
        "vnop\n"
        "vnop\n"
        "vdiv       $Q, $vf6x, $vf5z\n"
        "vwaitq\n"
        "vmulq.z    $vf1, $vf1, $Q\n"
        : "=r"(scratch)
        : "f"(first), "f"(second), "r"(scale)
        : "memory");
}

/**
 * @brief Store vf1.
 * @param vector Aligned destination.
 * @see vu0_shape_point_to_local.
 */
static inline void vu0_store_vf1(void* vector)
{
    asm __volatile__("sqc2 $vf1, 0x0(%0)\n" : : "r"(vector) : "memory");
}

/**
 * @brief Load a segment (start in vf1, axis in vf2) and a fraction along it (vf3.x), leave in vf10 the offset from
 *        a point to the segment point at that fraction, and start the reciprocal square root of its length squared.
 * @param start Aligned segment start.
 * @param axis Aligned segment axis.
 * @param fraction Fraction along the axis.
 * @param point Aligned point.
 * @see Lib's shape pair tests from 0x425C90.
 */
static inline void vu0_segment_point_offset(const LibVector4* start, const LibVector4* axis, float fraction,
                                            const void* point)
{
    u32 scratch;

    asm __volatile__(
        "lqc2       $vf1, 0x0(%1)\n"
        "lqc2       $vf2, 0x0(%2)\n"
        "mfc1       %0, %3\n"
        "nop\n"
        "qmtc2.ni   %0, $vf3\n"
        "lqc2       $vf4, 0x0(%4)\n"
        "vaddax.xyz $ACC, $vf1, $vf0x\n"
        "vmaddax.xyz $ACC, $vf2, $vf3x\n"
        "vmsubw.xyz $vf10, $vf4, $vf0w\n"
        "vmul.xyz   $vf11, $vf10, $vf10\n"
        "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
        "vadday.x   $ACC, $vf11, $vf11y\n"
        "vmaddz.x   $vf12, $vf31, $vf11z\n"
        "vrsqrt     $Q, $vf0w, $vf12x\n"
        : "=r"(scratch)
        : "r"(start), "r"(axis), "f"(fraction), "r"(point)
        : "memory");
}

/**
 * @brief Transform a point by the matrix the caller left in vf24-vf27 (rows), into vf1.
 * @param point Aligned point.
 * @see LibClass172F30::func_004284F0; the shape tests that call it load the other shape's matrix first.
 */
static inline void vu0_point_through_vf24(const LibVector4* point)
{
    asm __volatile__(
        "lqc2       $vf1, 0x0(%0)\n"
        "vmulax.xyzw $ACC, $vf24, $vf1x\n"
        "vmadday.xyzw $ACC, $vf25, $vf1y\n"
        "vmaddaz.xyzw $ACC, $vf26, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf27, $vf0w\n"
        :
        : "r"(point)
        : "memory");
}

/**
 * @brief Transform a segment by the matrix the caller left in vf24-vf27 (rows): the start, with translation, into
 *        vf1 and the axis, without, into vf2.
 * @param segment Aligned segment: start, then axis.
 * @see LibClass172FC0::func_004284F0; the shape tests that call it load the other shape's matrix first.
 */
static inline void vu0_segment_through_vf24(const LibVector4* segment)
{
    asm __volatile__(
        "lqc2       $vf1, 0x0(%0)\n"
        "lqc2       $vf2, 0x10(%0)\n"
        "vmulax.xyzw $ACC, $vf24, $vf1x\n"
        "vmadday.xyzw $ACC, $vf25, $vf1y\n"
        "vmaddaz.xyzw $ACC, $vf26, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf27, $vf0w\n"
        "vmulax.xyzw $ACC, $vf24, $vf2x\n"
        "vmadday.xyzw $ACC, $vf25, $vf2y\n"
        "vmaddz.xyzw $vf2, $vf26, $vf2z\n"
        :
        : "r"(segment)
        : "memory");
}

/**
 * @brief Scale vf1 per axis by (own + other radius) / (own radius + scale * other radius).
 * @param other_radius Other shape's radius.
 * @param own_radius This shape's radius.
 * @param scale Aligned per-axis scale of the other shape.
 * @see vu0_segment_through_vf24.
 */
static inline void vu0_scale_by_radii(float other_radius, float own_radius, const LibVector4* scale)
{
    u32 scratch;

    asm __volatile__(
        "mfc1       %0, %1\n"
        "nop\n"
        "qmtc2.ni   %0, $vf3\n"
        "mfc1       %0, %2\n"
        "nop\n"
        "qmtc2.ni   %0, $vf4\n"
        "lqc2       $vf5, 0x0(%3)\n"
        "vadd.x     $vf6, $vf3, $vf4\n"
        "vaddax.xyzw $ACC, $vf0, $vf4x\n"
        "vmaddx.xyz $vf5, $vf5, $vf3x\n"
        "vdiv       $Q, $vf6x, $vf5x\n"
        "vwaitq\n"
        "vmulq.x    $vf1, $vf1, $Q\n"
        "vnop\n"
        "vnop\n"
        "vdiv       $Q, $vf6x, $vf5y\n"
        "vwaitq\n"
        "vmulq.y    $vf1, $vf1, $Q\n"
        "vnop\n"
        "vnop\n"
        "vdiv       $Q, $vf6x, $vf5z\n"
        "vwaitq\n"
        "vmulq.z    $vf1, $vf1, $Q\n"
        : "=&r"(scratch)
        : "f"(other_radius), "f"(own_radius), "r"(scale)
        : "memory");
}

/**
 * @brief Store vf1 and vf2 as a segment.
 * @param segment Aligned destination: start, then axis.
 */
static inline void vu0_store_segment(LibVector4* segment)
{
    asm __volatile__(
        "sqc2       $vf1, 0x0(%0)\n"
        "sqc2       $vf2, 0x10(%0)\n"
        :
        : "r"(segment)
        : "memory");
}

/**
 * @brief Start the offset between the closest points of two segments and its reciprocal length: vf11 = (second start +
 *        second axis * second fraction) - (first start + first axis * first fraction), Q = 1 / |vf11|.
 * @param first_start Aligned start of the first segment.
 * @param first_axis Aligned axis of the first segment.
 * @param first_fraction Fraction along the first segment.
 * @param second_start Aligned start of the second segment.
 * @param second_axis Aligned axis of the second segment.
 * @param second_fraction Fraction along the second segment.
 * @see vu0_segment_point_offset, the segment-to-point form; LibClass172FC0::func_004284E0.
 */
static inline void vu0_segment_segment_offset(const LibVector4* first_start, const LibVector4* first_axis,
                                              float first_fraction, const LibVector4* second_start,
                                              const LibVector4* second_axis, float second_fraction)
{
    u32 scratch;

    asm __volatile__(
        "lqc2       $vf4, 0x0(%4)\n"
        "lqc2       $vf5, 0x0(%5)\n"
        "mfc1       %0, %6\n"
        "nop\n"
        "qmtc2.ni   %0, $vf6\n"
        "lqc2       $vf1, 0x0(%2)\n"
        "lqc2       $vf2, 0x0(%1)\n"
        "mfc1       %0, %3\n"
        "nop\n"
        "qmtc2.ni   %0, $vf3\n"
        "vaddax.xyz $ACC, $vf4, $vf0x\n"
        "vmaddax.xyz $ACC, $vf5, $vf6x\n"
        "vmsubaw.xyz $ACC, $vf1, $vf0w\n"
        "vmsubx.xyz $vf11, $vf2, $vf3x\n"
        "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
        "vmul.xyz   $vf13, $vf11, $vf11\n"
        "vadday.x   $ACC, $vf13, $vf13y\n"
        "vmaddz.x   $vf14, $vf31, $vf13z\n"
        "vrsqrt     $Q, $vf0w, $vf14x\n"
        : "=&r"(scratch)
        : "r"(first_axis), "r"(first_start), "f"(first_fraction), "r"(second_start), "r"(second_axis), "f"(second_fraction)
        : "memory");
}

/**
 * @brief Store the offset vu0_segment_segment_offset left in vf11, normalised.
 * @param direction Aligned destination.
 * @see vu0_segment_segment_offset.
 */
static inline void vu0_store_unit_segment_offset(void* direction)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyz  $vf15, $vf11, $Q\n"
        "sqc2       $vf15, 0x0(%0)\n"
        :
        : "r"(direction)
        : "memory");
}

/**
 * @brief Store the offset vu0_segment_point_offset left in vf10, normalised.
 * @param direction Aligned destination.
 * @see vu0_segment_point_offset.
 */
static inline void vu0_store_unit_offset(void* direction)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyz  $vf13, $vf10, $Q\n"
        "sqc2       $vf13, 0x0(%0)\n"
        :
        : "r"(direction)
        : "memory");
}

/**
 * @brief Leave in vf11 the offset between the points at two fractions along two segments (the first's minus the
 *        second's), and start the reciprocal square root of its length squared.
 * @param segment Aligned first segment: start, then axis.
 * @param fraction Fraction along the first segment.
 * @param point Aligned start of the second segment.
 * @param axis Aligned axis of the second segment.
 * @param other_fraction Fraction along the second segment.
 * @see Lib's capsule-capsule test at 0x4260C0.
 */
static inline void vu0_segment_pair_offset(const LibVector4* segment, float fraction, const void* point,
                                           const void* axis, float other_fraction)
{
    u32 scratch;

    asm __volatile__(
        "lqc2       $vf4, 0x0(%4)\n"
        "lqc2       $vf5, 0x0(%5)\n"
        "mfc1       %0, %6\n"
        "nop\n"
        "qmtc2.ni   %0, $vf6\n"
        "lqc2       $vf1, 0x0(%1)\n"
        "lqc2       $vf2, 0x0(%2)\n"
        "mfc1       %0, %3\n"
        "nop\n"
        "qmtc2.ni   %0, $vf3\n"
        "vaddax.xyz $ACC, $vf4, $vf0x\n"
        "vmaddax.xyz $ACC, $vf5, $vf6x\n"
        "vmsubaw.xyz $ACC, $vf1, $vf0w\n"
        "vmsubx.xyz $vf11, $vf2, $vf3x\n"
        "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
        "vmul.xyz   $vf13, $vf11, $vf11\n"
        "vadday.x   $ACC, $vf13, $vf13y\n"
        "vmaddz.x   $vf14, $vf31, $vf13z\n"
        "vrsqrt     $Q, $vf0w, $vf14x\n"
        : "=r"(scratch)
        : "r"(point), "r"(axis), "f"(other_fraction), "r"(segment), "r"(segment + 1), "f"(fraction)
        : "memory");
}

/**
 * @brief Store the offset vu0_segment_pair_offset left in vf11, normalised.
 * @param direction Aligned destination.
 * @see vu0_segment_pair_offset.
 */
static inline void vu0_store_unit_pair_offset(void* direction)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyz  $vf15, $vf11, $Q\n"
        "sqc2       $vf15, 0x0(%0)\n"
        :
        : "r"(direction)
        : "memory");
}

/**
 * @brief Start a node's step: ACC = position (vf16), the step in vf17.x, its square in vf23.x, the solver constants
 *        in vf18 and the velocity in vf22.
 * @param position Aligned position.
 * @param step Time step.
 * @param constants Aligned solver constants.
 * @param velocity Aligned velocity.
 * @see Lib's node step at 0x4264F0.
 */
static inline void vu0_link_step_start(const void* position, float step, const void* constants, const void* velocity)
{
    u32 scratch;

    asm __volatile__(
        "lqc2       $vf16, 0x0(%1)\n"
        "mfc1       %0, %2\n"
        "nop\n"
        "qmtc2.ni   %0, $vf17\n"
        "lqc2       $vf18, 0x0(%3)\n"
        "lqc2       $vf22, 0x0(%4)\n"
        "vaddax.xyzw $ACC, $vf16, $vf0x\n"
        "vmul.x     $vf23, $vf17, $vf17\n"
        : "=r"(scratch)
        : "r"(position), "f"(step), "r"(constants), "r"(velocity)
        : "memory");
}

/**
 * @brief Add gravity (constants y times the step squared) to ACC.y.
 * @see vu0_link_step_start.
 */
static inline void vu0_link_step_gravity(void)
{
    asm __volatile__("vmaddax.y $ACC, $vf18, $vf23x\n");
}

/**
 * @brief Add a force times the step to ACC.
 * @param force Aligned force.
 * @see vu0_link_step_start.
 */
static inline void vu0_link_step_force(const void* force)
{
    asm __volatile__(
        "lqc2       $vf24, 0x0(%0)\n"
        "vmaddax.xyz $ACC, $vf24, $vf17x\n"
        :
        : "r"(force)
        : "memory");
}

/**
 * @brief Take the velocity times damping times the step off ACC.
 * @param damping Damping factor.
 * @see vu0_link_step_start.
 */
static inline void vu0_link_step_damping(float damping)
{
    u32 scratch;

    asm __volatile__(
        "mfc1       %0, %1\n"
        "nop\n"
        "qmtc2.ni   %0, $vf19\n"
        "vmul.x     $vf20, $vf19, $vf17\n"
        "vmsubax.xyz $ACC, $vf22, $vf20x\n"
        : "=r"(scratch)
        : "f"(damping));
}

/**
 * @brief Finish the step: vf16 = ACC + velocity times the step.
 * @see vu0_link_step_start.
 */
static inline void vu0_link_step_finish(void)
{
    asm __volatile__("vmaddx.xyz $vf16, $vf22, $vf17x\n");
}

/**
 * @brief Load two node positions: the second into vf11, the first into vf10.
 * @param second Aligned second position.
 * @param first Aligned first position.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370.
 */
static inline void vu0_link_load_ends(const void* second, const void* first)
{
    asm __volatile__(
        "lqc2       $vf11, 0x0(%0)\n"
        "lqc2       $vf10, 0x0(%1)\n"
        :
        : "r"(second), "r"(first)
        : "memory");
}

/**
 * @brief vf20 = vf11 - vf10.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_span_vf20(void)
{
    asm __volatile__("vsub.xyz $vf20, $vf11, $vf10\n");
}

/**
 * @brief vf31 = (1, 1, 1, 1).
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_ones_vf31(void)
{
    asm __volatile__("vmaxw.xyzw $vf31, $vf0, $vf0w\n");
}

/**
 * @brief vf21 = vf20 squared per component.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_square_vf20(void)
{
    asm __volatile__("vmul.xyz $vf21, $vf20, $vf20\n");
}

/**
 * @brief ACC.x = vf21.x + vf21.y.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_sum_start_vf21(void)
{
    asm __volatile__("vadday.x $ACC, $vf21, $vf21y\n");
}

/**
 * @brief vf22.x = ACC.x + vf21.z.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_sum_finish_vf21(void)
{
    asm __volatile__("vmaddz.x $vf22, $vf31, $vf21z\n");
}

/**
 * @brief Start the square root of vf22.x.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_sqrt_vf22(void)
{
    asm __volatile__("vsqrt $Q, $vf22x\n");
}

/**
 * @brief vf24.x = Q (the length).
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_length_vf24(void)
{
    asm __volatile__(
        "vwaitq\n"
        "vaddq.x    $vf24, $vf0, $Q\n"
        "vnop\n");
}

/**
 * @brief Start dividing one by vf24.x.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_reciprocal_vf24(void)
{
    asm __volatile__("vdiv $Q, $vf0w, $vf24x\n");
}

/**
 * @brief Wait for Q.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_wait_q(void)
{
    asm __volatile__("vwaitq\n");
}

/**
 * @brief vf24 = vf20 times Q (the unit span).
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_unit_vf24(void)
{
    asm __volatile__("vmulq.xyz $vf24, $vf20, $Q\n");
}

/**
 * @brief ACC = vf10.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_accumulate_vf10(void)
{
    asm __volatile__("vmulaw.xyz $ACC, $vf10, $vf0w\n");
}

/**
 * @brief ACC = vf11.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_accumulate_vf11(void)
{
    asm __volatile__("vmulaw.xyz $ACC, $vf11, $vf0w\n");
}

/**
 * @brief vf10 = ACC + vf24 times vf22.x.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_push_vf10_vf22(void)
{
    asm __volatile__("vmaddx.xyz $vf10, $vf24, $vf22x\n");
}

/**
 * @brief vf11 = ACC - vf24 times vf22.x.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_pull_vf11_vf22(void)
{
    asm __volatile__("vmsubx.xyz $vf11, $vf24, $vf22x\n");
}

/**
 * @brief vf11 = ACC - vf24 times vf23.x.
 * @see Lib's distance constraints at 0x4261E0 and 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_pull_vf11_vf23(void)
{
    asm __volatile__("vmsubx.xyz $vf11, $vf24, $vf23x\n");
}

/**
 * @brief Put a float in vf22.x.
 * @param value Value.
 * @see Lib's distance constraints at 0x4261E0.
 */
static inline void vu0_set_vf22(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf22\n" : : "r"(value));
}

/**
 * @brief Put a float in vf23.x.
 * @param value Value.
 * @see Lib's distance constraints at 0x4261E0.
 */
static inline void vu0_set_vf23(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf23\n" : : "r"(value));
}

/**
 * @brief vf23 = vf11 - vf10.
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_span_vf23(void)
{
    asm __volatile__("vsub.xyz $vf23, $vf11, $vf10\n");
}

/**
 * @brief vf24 = vf23 squared per component.
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_square_vf23(void)
{
    asm __volatile__("vmul.xyz $vf24, $vf23, $vf23\n");
}

/**
 * @brief vf25.xyz = (1, 1, 1).
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_ones_vf25(void)
{
    asm __volatile__("vaddw.xyz $vf25, $vf0, $vf0w\n");
}

/**
 * @brief ACC.x = vf24.x + vf24.y.
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_sum_start_vf24(void)
{
    asm __volatile__("vadday.x $ACC, $vf24, $vf24y\n");
}

/**
 * @brief vf24.x = ACC.x + vf24.z.
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_sum_finish_vf24(void)
{
    asm __volatile__("vmaddz.x $vf24, $vf25, $vf24z\n");
}

/**
 * @brief Start the square root of vf24.x.
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_sqrt_vf24(void)
{
    asm __volatile__("vsqrt $Q, $vf24x\n");
}

/**
 * @brief vf23 = vf23 times Q (the unit span).
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_unit_vf23(void)
{
    asm __volatile__("vmulq.xyz $vf23, $vf23, $Q\n");
}

/**
 * @brief vf10 = ACC + vf23 times vf13.x.
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_push_vf10_vf13(void)
{
    asm __volatile__("vmaddx.xyz $vf10, $vf23, $vf13x\n");
}

/**
 * @brief vf11 = ACC - vf23 times vf13.x.
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_pull_vf11_vf13(void)
{
    asm __volatile__("vmsubx.xyz $vf11, $vf23, $vf13x\n");
}

/**
 * @brief vf11 = ACC - vf23 times vf14.x.
 * @see Lib's distance constraint at 0x426370; no memory clobber, so loads can move between them.
 */
static inline void vu0_link_pull_vf11_vf14(void)
{
    asm __volatile__("vmsubx.xyz $vf11, $vf23, $vf14x\n");
}

/**
 * @brief Put a float in vf13.x.
 * @param value Value.
 * @see Lib's distance constraint at 0x426370.
 */
static inline void vu0_set_vf13(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf13\n" : : "r"(value));
}

/**
 * @brief Put a float in vf14.x.
 * @param value Value.
 * @see Lib's distance constraint at 0x426370.
 */
static inline void vu0_set_vf14(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf14\n" : : "r"(value));
}

/**
 * @brief Load a particle position into vf10 and a field centre into vf11.
 * @param position Aligned particle position.
 * @param centre Aligned field centre.
 * @see Lib's radial field at 0x425490.
 */
static inline void vu0_field_load_points(const void* position, const void* centre)
{
    asm __volatile__(
        "lqc2       $vf10, 0x0(%0)\n"
        "lqc2       $vf11, 0x0(%1)\n"
        :
        : "r"(position), "r"(centre)
        : "memory");
}

/**
 * @brief Put a float in vf12.x.
 * @param value Value.
 * @see Lib's radial field at 0x425490.
 */
static inline void vu0_set_vf12(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf12\n" : : "r"(value));
}

/**
 * @brief vf20 = vf10 - vf11, then the x/z swirl: x' = -z (with the old x kept in vf21.x).
 * @see Lib's radial field at 0x425490.
 */
static inline void vu0_field_swirl_start(void)
{
    asm __volatile__(
        "vsub.xyz   $vf20, $vf10, $vf11\n"
        "vadd.x     $vf21, $vf0, $vf20\n"
        "vsubz.x    $vf20, $vf0, $vf20z\n");
}

/**
 * @brief Finish the swirl: z' = old x.
 * @see vu0_field_swirl_start.
 */
static inline void vu0_field_swirl_finish(void)
{
    asm __volatile__("vaddx.z $vf20, $vf0, $vf21x\n");
}

/**
 * @brief vf20 = vf10 - vf11.
 * @see Lib's radial field at 0x425490.
 */
static inline void vu0_field_offset(void)
{
    asm __volatile__("vsub.xyz $vf20, $vf10, $vf11\n");
}

/**
 * @brief Start the field falloff: Q = 1 / |vf20|, vf23.x = |vf20|^2 + vf12.x^2 (vf12.x squared in place).
 * @see Lib's radial field at 0x425490.
 */
static inline void vu0_field_falloff(void)
{
    asm __volatile__(
        "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
        "vmul.x     $vf12, $vf12, $vf12\n"
        "vmul.xyz   $vf21, $vf20, $vf20\n"
        "vadday.x   $ACC, $vf21, $vf21y\n"
        "vmaddz.x   $vf22, $vf31, $vf21z\n"
        "vrsqrt     $Q, $vf0w, $vf22x\n"
        "vadd.x     $vf23, $vf22, $vf12\n");
}

/**
 * @brief Put a float in vf13.x.
 * @param value Value.
 * @see Lib's radial field at 0x425490.
 */
static inline void vu0_set_vf13_x(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf13\n" : : "r"(value) : "memory");
}

/**
 * @brief Store the push: the unit offset times vf13.x times vf12.x / vf23.x, with w = 1.
 * @param output Aligned destination.
 * @see vu0_field_falloff.
 */
static inline void vu0_field_store_push(void* output)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyz  $vf24, $vf20, $Q\n"
        "vnop\n"
        "vnop\n"
        "vdiv       $Q, $vf12x, $vf23x\n"
        "vmulx.xyz  $vf25, $vf24, $vf13x\n"
        "vmulw.w    $vf25, $vf0, $vf0w\n"
        "vwaitq\n"
        "vmulq.xyz  $vf25, $vf25, $Q\n"
        "sqc2       $vf25, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief Move a point by a matrix (w included) and store it.
 * @param point Aligned point.
 * @param matrix Aligned four-row matrix.
 * @param output Aligned destination.
 * @see Lib's field at 0x425600.
 */
static inline void vu0_field_to_local(const void* point, const void* matrix, void* output)
{
    asm __volatile__(
        "lqc2       $vf5, 0x0(%0)\n"
        "lqc2       $vf1, 0x0(%1)\n"
        "lqc2       $vf2, 0x10(%1)\n"
        "lqc2       $vf3, 0x20(%1)\n"
        "lqc2       $vf4, 0x30(%1)\n"
        "vmulax.xyzw $ACC, $vf1, $vf5x\n"
        "vmadday.xyzw $ACC, $vf2, $vf5y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf5z\n"
        "vmaddw.xyzw $vf5, $vf4, $vf5w\n"
        "sqc2       $vf5, 0x0(%2)\n"
        :
        : "r"(point), "r"(matrix), "r"(output)
        : "memory");
}

/**
 * @brief Store a vector's length squared in x of the destination.
 * @param vector Aligned vector.
 * @param output Aligned destination.
 * @see Lib's field at 0x425600.
 */
static inline void vu0_field_length_squared(const void* vector, void* output)
{
    asm __volatile__(
        "lqc2       $vf24, 0x0(%0)\n"
        "vmul.xyz   $vf24, $vf24, $vf24\n"
        "vaddw.xyz  $vf25, $vf0, $vf0w\n"
        "vadday.x   $ACC, $vf24, $vf24y\n"
        "vmaddz.x   $vf24, $vf25, $vf24z\n"
        "sqc2       $vf24, 0x0(%1)\n"
        :
        : "r"(vector), "r"(output)
        : "memory");
}

/**
 * @brief Move a segment (start and the axis in the next quadword) by the matrix the caller left in vf24-vf27: the
 *        start into vf1 (with translation), the axis into vf2.
 * @param segment Aligned segment: start, then axis.
 * @see Lib's capsule-capsule test at 0x425E10.
 */
static inline void vu0_shape_segment_to_local(const void* segment)
{
    asm __volatile__(
        "lqc2       $vf1, 0x0(%0)\n"
        "lqc2       $vf2, 0x10(%0)\n"
        "vmulax.xyzw $ACC, $vf24, $vf1x\n"
        "vmadday.xyzw $ACC, $vf25, $vf1y\n"
        "vmaddaz.xyzw $ACC, $vf26, $vf1z\n"
        "vmaddw.xyzw $vf1, $vf27, $vf0w\n"
        "vmulax.xyzw $ACC, $vf24, $vf2x\n"
        "vmadday.xyzw $ACC, $vf25, $vf2y\n"
        "vmaddz.xyzw $vf2, $vf26, $vf2z\n"
        :
        : "r"(segment)
        : "memory");
}

/**
 * @brief Store vf1 and vf2 to consecutive quadwords.
 * @param vectors Aligned destination for two quadwords.
 * @see vu0_shape_segment_to_local.
 */
static inline void vu0_store_vf1_vf2(void* vectors)
{
    asm __volatile__(
        "sqc2 $vf1, 0x0(%0)\n"
        "sqc2 $vf2, 0x10(%0)\n"
        :
        : "r"(vectors)
        : "memory");
}

/**
 * @brief Store the distance between two points in out.x.
 * @param first 16-byte aligned first point.
 * @param second 16-byte aligned second point.
 * @param out 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); Lib's link setup at 0x428670.
 */
static inline void vu0_link_distance(const void* first, const void* second, void* out)
{
    asm __volatile__(
        "lqc2      $vf24, 0x0(%0)\n"
        "lqc2      $vf25, 0x0(%1)\n"
        "vsub.xyz  $vf24, $vf24, $vf25\n"
        "vmul.xyz  $vf24, $vf24, $vf24\n"
        "vaddw.xyz $vf25, $vf0, $vf0w\n"
        "vadday.x  $ACC, $vf24, $vf24y\n"
        "vmaddz.x  $vf24, $vf25, $vf24z\n"
        "vsqrt     $Q, $vf24x\n"
        "vwaitq\n"
        "vaddq.x   $vf24, $vf0, $Q\n"
        "sqc2      $vf24, 0x0(%2)\n"
        :
        : "r"(first), "r"(second), "r"(out)
        : "memory");
}

#endif
