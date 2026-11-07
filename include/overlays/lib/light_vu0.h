#ifndef SO3_OVERLAYS_LIB_LIGHT_VU0_H
#define SO3_OVERLAYS_LIB_LIGHT_VU0_H

/**
 * @brief Load a normal and a light's factors for vu0_light_scale_normal.
 * @param normal 16-byte aligned normal, into vf19.
 * @param factors 16-byte aligned factors (x, y and w are used), into vf20.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); Lib's light with vtable D_1737E0 (0x434300).
 */
static inline void vu0_light_load_normal(const void* normal, const void* factors)
{
    asm __volatile__(
        "lqc2      $vf19, 0x0(%0)\n"
        "lqc2      $vf20, 0x0(%1)\n"
        :
        : "r"(normal), "r"(factors)
        : "memory");
}

/**
 * @brief Store normal * w * (|normal| * x + y) per component, from what vu0_light_load_normal loaded.
 * @param out 16-byte aligned destination; only xyz is written by the arithmetic.
 * @see vu0_light_load_normal.
 */
static inline void vu0_light_scale_normal(void* out)
{
    asm __volatile__(
        "vabs.xyz  $vf22, $vf19\n"
        "vmulw.xyz $vf19, $vf19, $vf20w\n"
        "vadday.xyz $ACC, $vf0, $vf20y\n"
        "vmaddx.xyz $vf22, $vf22, $vf20x\n"
        "vmul.xyz  $vf19, $vf19, $vf22\n"
        "sqc2      $vf19, 0x0(%0)\n"
        :
        : "r"(out)
        : "memory");
}

/**
 * @brief Load a point, a light position and the light's factors for vu0_light_point_vector.
 * @param point 16-byte aligned point being lit, into vf19.
 * @param position 16-byte aligned light position, into vf20.
 * @param factors 16-byte aligned factors (x and w are used), into vf21.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); Lib's light with vtable D_173750 (0x4341F0).
 */
static inline void vu0_light_load_point(const void* point, const void* position, const void* factors)
{
    asm __volatile__(
        "lqc2      $vf19, 0x0(%0)\n"
        "lqc2      $vf20, 0x0(%1)\n"
        "lqc2      $vf21, 0x0(%2)\n"
        :
        : "r"(point), "r"(position), "r"(factors)
        : "memory");
}

/**
 * @brief Store the vector from the point to the light, times x over (squared distance + w) to the power 1.5.
 * @param out 16-byte aligned destination; only xyz is written by the arithmetic.
 * @see vu0_light_load_point.
 */
static inline void vu0_light_point_vector(void* out)
{
    asm __volatile__(
        "vsub.xyz  $vf22, $vf20, $vf19\n"
        "vmul.xyz  $vf23, $vf22, $vf22\n"
        "vaddw.xyz $vf24, $vf0, $vf0w\n"
        "vadday.x  $ACC, $vf23, $vf23y\n"
        "vmaddaw.x $ACC, $vf24, $vf21w\n"
        "vmaddz.x  $vf23, $vf24, $vf23z\n"
        "vrsqrt    $Q, $vf0w, $vf23x\n"
        "vmulx.xyz $vf22, $vf22, $vf21x\n"
        "vwaitq\n"
        "vmulq.xyz $vf22, $vf22, $Q\n"
        "vmulq.xyz $vf22, $vf22, $Q\n"
        "vmulq.xyz $vf22, $vf22, $Q\n"
        "sqc2      $vf22, 0x0(%0)\n"
        :
        : "r"(out)
        : "memory");
}

/**
 * @brief Transform a direction by a matrix's first three rows, as vu0_transform_emission_direction does.
 *
 * Same instructions as that helper, but the lights' copy lists the direction first among the asm inputs, which
 * gives its addresses different registers.
 * @param matrix 16-byte aligned matrix.
 * @param input 16-byte aligned direction.
 * @param output 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); Lib's lights with vtables D_173870 (0x4344D0)
 * and D_173900 (0x434720).
 */
static inline void vu0_light_transform_direction(const void* matrix, const void* input, void* output)
{
    asm __volatile__(
        "lqc2      $vf4, 0x0(%0)\n"
        "lqc2      $vf1, 0x0(%1)\n"
        "lqc2      $vf2, 0x10(%1)\n"
        "lqc2      $vf3, 0x20(%1)\n"
        "vmulax.xyzw $ACC, $vf1, $vf4x\n"
        "vmadday.xyzw $ACC, $vf2, $vf4y\n"
        "vmaddz.xyzw $vf4, $vf3, $vf4z\n"
        "sqc2      $vf4, 0x0(%2)\n"
        :
        : "r"(input), "r"(matrix), "r"(output)
        : "memory");
}

/**
 * @brief Normalise the xyz of a matrix's first three rows in place.
 * @param matrix 16-byte aligned matrix; rows 0 to 2 are loaded into vf1-vf3 and stay there afterwards.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); Lib's light with vtable D_173900 (0x434720) and
 * its scene's light pass (0x43CE80).
 */
static inline void vu0_normalize_rows_xyz(void* matrix)
{
    asm __volatile__(
        "lqc2      $vf1, 0x0(%0)\n"
        "lqc2      $vf2, 0x10(%0)\n"
        "lqc2      $vf3, 0x20(%0)\n"
        "vmul.xyz  $vf6, $vf1, $vf1\n"
        "vaddw.xyz $vf31, $vf0, $vf0w\n"
        "vmul.xyz  $vf7, $vf2, $vf2\n"
        "vmul.xyz  $vf8, $vf3, $vf3\n"
        "vadday.x  $ACC, $vf6, $vf6y\n"
        "vmaddz.x  $vf9, $vf31, $vf6z\n"
        "vaddax.y  $ACC, $vf7, $vf7x\n"
        "vmaddz.y  $vf9, $vf31, $vf7z\n"
        "vadday.z  $ACC, $vf8, $vf8y\n"
        "vrsqrt    $Q, $vf0w, $vf9x\n"
        "vmaddx.z  $vf9, $vf31, $vf8x\n"
        "vwaitq\n"
        "vrsqrt    $Q, $vf0w, $vf9y\n"
        "vmulq.xyz $vf1, $vf1, $Q\n"
        "vwaitq\n"
        "vrsqrt    $Q, $vf0w, $vf9z\n"
        "vmulq.xyz $vf2, $vf2, $Q\n"
        "vwaitq\n"
        "vmulq.xyz $vf3, $vf3, $Q\n"
        "sqc2      $vf1, 0x0(%0)\n"
        "sqc2      $vf2, 0x10(%0)\n"
        "sqc2      $vf3, 0x20(%0)\n"
        :
        : "r"(matrix)
        : "memory");
}

/**
 * @brief Start normalising the xyz of vf1: square its length and begin the reciprocal square root in Q.
 *
 * Load vf1 with vu0_load_vf1 first and finish with vu0_light_store_normalized_vf1; the game does other work while
 * the division runs.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); Lib's light with vtable D_173630 (0x433EF0).
 */
static inline void vu0_light_start_normalize_vf1(void)
{
    asm __volatile__(
        "vmul.xyz  $vf2, $vf1, $vf1\n"
        "vaddw.xyz $vf31, $vf0, $vf0w\n"
        "vadday.x  $ACC, $vf2, $vf2y\n"
        "vmaddz.x  $vf2, $vf31, $vf2z\n"
        "vrsqrt    $Q, $vf0w, $vf2x\n");
}

/**
 * @brief Wait for the reciprocal square root, scale vf1's xyz by it and store vf1.
 * @param out 16-byte aligned destination.
 * @see vu0_light_start_normalize_vf1.
 */
static inline void vu0_light_store_normalized_vf1(void* out)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyz $vf1, $vf1, $Q\n"
        "sqc2      $vf1, 0x0(%0)\n"
        :
        : "r"(out)
        : "memory");
}

/**
 * @brief Load a spotlight's frame: position into vf20, direction into vf21, and cone cosine and sine into vf22.
 * @param frame 16-byte aligned frame from lib_spot_light_get_frame (three vectors).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibLightList::assign_spot_lights (0x4E7830).
 */
static inline void vu0_spot_light_load(const void* frame)
{
    asm __volatile__(
        "lqc2      $vf20, 0x0(%0)\n"
        "lqc2      $vf21, 0x10(%0)\n"
        "lqc2      $vf22, 0x20(%0)\n"
        :
        : "r"(frame)
        : "memory");
}

/**
 * @brief Measure a bounding sphere against the loaded spotlight.
 *
 * Leaves the squared distance from the light to the sphere's centre in vf26.x and the squared radius in vf26.w,
 * the centre's distance along the light's direction in vf30.y, the squared cone cosine in vf29.x, and one in vf31.
 * @param sphere 16-byte aligned bounding sphere (centre in xyz, radius in w).
 * @see vu0_spot_light_load.
 */
static inline void vu0_spot_light_measure(const void* sphere)
{
    asm __volatile__(
        "lqc2      $vf23, 0x0(%0)\n"
        "vsub.xyz  $vf24, $vf23, $vf20\n"
        "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
        "vmul.w    $vf26, $vf23, $vf23\n"
        "vmul.xyz  $vf26, $vf24, $vf24\n"
        "vmul.xyz  $vf27, $vf24, $vf21\n"
        "vadday.x  $ACC, $vf26, $vf26y\n"
        "vmaddz.x  $vf26, $vf31, $vf26z\n"
        "vmul.x    $vf29, $vf22, $vf22\n"
        "vaddax.y  $ACC, $vf27, $vf27x\n"
        "vmaddz.y  $vf30, $vf31, $vf27z\n"
        :
        : "r"(sphere)
        : "memory");
}

/**
 * @brief Store vf26: the squared distance in x and the squared radius in w.
 * @param out 16-byte aligned destination.
 * @see vu0_spot_light_measure.
 */
static inline void vu0_spot_light_store_distance(void* out)
{
    asm __volatile__(
        "sqc2      $vf26, 0x0(%0)\n"
        :
        : "r"(out)
        : "memory");
}

/**
 * @brief Square the distance along the direction into vf29.y and scale the squared distance by the squared cone
 * cosine into vf30.x.
 * @see vu0_spot_light_measure.
 */
static inline void vu0_spot_light_axis_terms()
{
    asm __volatile__(
        "vmul.y    $vf29, $vf30, $vf30\n"
        "vmul.x    $vf30, $vf29, $vf26\n"
        :
        :
        : "memory");
}

/**
 * @brief Store vf29 and vf30 (the squared and plain distance along the direction in y, the scaled distance in x).
 * @param out 16-byte aligned destination for two vectors.
 * @see vu0_spot_light_axis_terms.
 */
static inline void vu0_spot_light_store_axis_terms(void* out)
{
    asm __volatile__(
        "sqc2      $vf29, 0x0(%0)\n"
        "sqc2      $vf30, 0x10(%0)\n"
        :
        : "r"(out)
        : "memory");
}

/**
 * @brief Test the sphere against the cone's edge: vf28.y is the sphere centre's offset past the edge (distance along
 * the direction times the cosine plus the distance off the axis times the sine) and vf29.y its square less the squared
 * distance plus the squared radius.
 * @see vu0_spot_light_measure.
 */
static inline void vu0_spot_light_edge_terms()
{
    asm __volatile__(
        "vsuby.x   $vf28, $vf26, $vf29y\n"
        "vabs.x    $vf28, $vf28\n"
        "vsqrt     $Q, $vf28x\n"
        "vmulax.y  $ACC, $vf30, $vf22x\n"
        "vwaitq\n"
        "vmaddq.y  $vf28, $vf22, $Q\n"
        "vmula.y   $ACC, $vf28, $vf28\n"
        "vmsubax.y $ACC, $vf31, $vf26x\n"
        "vmaddw.y  $vf29, $vf31, $vf26w\n"
        :
        :
        : "memory");
}

/**
 * @brief Store vf28 and vf29, the edge terms in y.
 * @param out 16-byte aligned destination for two vectors.
 * @see vu0_spot_light_edge_terms.
 */
static inline void vu0_spot_light_store_edge_terms(void* out)
{
    asm __volatile__(
        "sqc2      $vf28, 0x0(%0)\n"
        "sqc2      $vf29, 0x10(%0)\n"
        :
        : "r"(out)
        : "memory");
}

#endif
