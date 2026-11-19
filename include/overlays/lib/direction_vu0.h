#ifndef SO3_OVERLAYS_LIB_DIRECTION_VU0_H
#define SO3_OVERLAYS_LIB_DIRECTION_VU0_H

/**
 * @brief Transform two points by a matrix and start normalising both.
 *
 * Leaves the transformed points in vf10 and vf11, their squared lengths in
 * vf13.x and vf15.x, ones in vf31, and the first reciprocal square root running.
 * @param matrix Aligned 4x4 matrix; the points' w is taken as one.
 * @param first Aligned first point.
 * @param second Aligned second point.
 * @see lib_solve_ik_chain; func_00426650 and LibClass173050::update in Lib run the same sequence.
 */
static inline void vu0_direction_pair_begin(const void* matrix, const void* first, const void* second)
{
    asm __volatile__(
        "lqc2       $vf1, 0x00(%0)\n"
        "lqc2       $vf2, 0x10(%0)\n"
        "lqc2       $vf3, 0x20(%0)\n"
        "lqc2       $vf4, 0x30(%0)\n"
        "lqc2       $vf5, 0x0(%1)\n"
        "lqc2       $vf6, 0x0(%2)\n"
        "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
        "vmulax.xyzw $ACC, $vf1, $vf5x\n"
        "vmadday.xyzw $ACC, $vf2, $vf5y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf5z\n"
        "vmaddw.xyzw $vf10, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf1, $vf6x\n"
        "vmadday.xyzw $ACC, $vf2, $vf6y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf6z\n"
        "vmul.xyz   $vf12, $vf10, $vf10\n"
        "vmaddw.xyzw $vf11, $vf4, $vf0w\n"
        "vadday.x   $ACC, $vf12, $vf12y\n"
        "vmaddz.x   $vf13, $vf31, $vf12z\n"
        "vmul.xyz   $vf14, $vf11, $vf11\n"
        "vrsqrt     $Q, $vf0w, $vf13x\n"
        "vadday.x   $ACC, $vf14, $vf14y\n"
        "vmaddz.x   $vf15, $vf31, $vf14z\n"
        :
        : "r"(matrix), "r"(first), "r"(second)
        : "memory");
}

/**
 * @brief Finish normalising the pair from vu0_direction_pair_begin and compare them.
 *
 * Leaves the dot product of the unit directions in vf19.x and their cross
 * product in vf20.
 * @see lib_solve_ik_chain; func_00426650 and LibClass173050::update in Lib run it with an extra vf30
 *      setup interleaved.
 */
static inline void vu0_direction_pair_dot_cross()
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyz  $vf16, $vf10, $Q\n"
        "vnop\n"
        "vnop\n"
        "vrsqrt     $Q, $vf0w, $vf15x\n"
        "vmr32.xyz  $vf18, $vf16\n"
        "vmr32.xyz  $vf19, $vf18\n"
        "vwaitq\n"
        "vmulq.xyz  $vf17, $vf11, $Q\n"
        "vmula.x    $ACC, $vf16, $vf17\n"
        "vmadday.x  $ACC, $vf18, $vf17y\n"
        "vmaddz.x   $vf19, $vf19, $vf17z\n"
        "vopmula.xyz $ACC, $vf17, $vf16\n"
        "vopmsub.xyz $vf20, $vf16, $vf17\n"
        :
        :
        : "memory");
}

/**
 * @brief Store the dot product left by vu0_direction_pair_dot_cross.
 * @param output Aligned vector receiving the dot product in x.
 * @see lib_solve_ik_chain; func_00426650 and LibClass173050::update in Lib store vf19 the same way.
 */
static inline void vu0_direction_pair_store_dot(void* output)
{
    asm __volatile__(
        "sqc2       $vf19, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief Store the unit vector of the cross product left in vf20.
 *
 * Needs the ones that vu0_direction_pair_begin leaves in vf31.
 * @param output Aligned vector receiving the unit axis in xyz.
 * @see lib_solve_ik_chain. func_00426650 and LibClass173050::update in Lib scale the same vf20
 *      cross product into their rotation axis.
 */
static inline void vu0_store_unit_cross(void* output)
{
    asm __volatile__(
        "vmul.xyz   $vf10, $vf20, $vf20\n"
        "vadday.x   $ACC, $vf10, $vf10y\n"
        "vmaddz.x   $vf11, $vf31, $vf10z\n"
        "vrsqrt     $Q, $vf0w, $vf11x\n"
        "vwaitq\n"
        "vmulq.xyz  $vf12, $vf20, $Q\n"
        "sqc2       $vf12, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief Put a float in vf29.x.
 * @param value Value.
 * @see Lib's link solver at 0x426650, which keeps one half there.
 */
static inline void vu0_set_vf29(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf29\n" : : "r"(value));
}

/**
 * @brief vu0_direction_pair_dot_cross, also setting vf30.w to two for vu0_direction_pair_store_dot_half.
 * @see vu0_direction_pair_dot_cross; Lib's link solver at 0x426650.
 */
static inline void vu0_direction_pair_dot_cross_half()
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyz  $vf16, $vf10, $Q\n"
        "vnop\n"
        "vnop\n"
        "vrsqrt     $Q, $vf0w, $vf15x\n"
        "vmr32.xyz  $vf18, $vf16\n"
        "vadd.w     $vf30, $vf0, $vf0\n"
        "vmr32.xyz  $vf19, $vf18\n"
        "vwaitq\n"
        "vmulq.xyz  $vf17, $vf11, $Q\n"
        "vmula.x    $ACC, $vf16, $vf17\n"
        "vmadday.x  $ACC, $vf18, $vf17y\n"
        "vmaddz.x   $vf19, $vf19, $vf17z\n"
        "vopmula.xyz $ACC, $vf17, $vf16\n"
        "vopmsub.xyz $vf20, $vf16, $vf17\n"
        :
        :
        : "memory");
}

/**
 * @brief Store the dot product (vf19) and put 2 + 2 * dot, four times the squared cosine of the half angle, in vf21.x.
 * @param output 16-byte aligned destination for vf19.
 * @see vu0_direction_pair_dot_cross_half.
 */
static inline void vu0_direction_pair_store_dot_half(void* output)
{
    asm __volatile__(
        "sqc2       $vf19, 0x0(%0)\n"
        "vaddaw.x   $ACC, $vf0, $vf30w\n"
        "vmaddw.x   $vf21, $vf19, $vf30w\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief Start the square root of vf21.x.
 * @see vu0_direction_pair_store_rotation.
 */
static inline void vu0_direction_pair_start_half_angle()
{
    asm __volatile__("vsqrt      $Q, $vf21x\n");
}

/**
 * @brief Store the rotation between the two directions: the cross product (vf20) over twice the half-angle cosine,
 *        with that cosine (scaled by vf29.x) in w.
 * @param output 16-byte aligned destination quaternion.
 * @see vu0_direction_pair_start_half_angle.
 */
static inline void vu0_direction_pair_store_rotation(void* output)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.w    $vf22, $vf0, $Q\n"
        "vnop\n"
        "vnop\n"
        "vdiv       $Q, $vf0w, $vf22w\n"
        "vmulx.w    $vf22, $vf22, $vf29x\n"
        "vwaitq\n"
        "vmulq.xyz  $vf22, $vf20, $Q\n"
        "sqc2       $vf22, 0x0(%0)\n"
        :
        : "r"(output)
        : "memory");
}

#endif
