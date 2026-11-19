#ifndef SO3_OVERLAYS_LIB_COLLIDER_VU0_H
#define SO3_OVERLAYS_LIB_COLLIDER_VU0_H

/**
 * @brief Save vf15-vf18 to a four-quadword block.
 * @param registers Aligned block of four quadwords.
 * @see Lib's sphere collider at 0x43BEB0, which uses them as scratch inside a particle pass.
 */
static inline void vu0_save_vf15_vf18(void* registers)
{
    asm __volatile__(
        "sqc2 $vf15, 0x0(%0)\n"
        "sqc2 $vf16, 0x10(%0)\n"
        "sqc2 $vf17, 0x20(%0)\n"
        "sqc2 $vf18, 0x30(%0)\n"
        :
        : "r"(registers)
        : "memory");
}

/**
 * @brief Load vf15-vf18 back from a block vu0_save_vf15_vf18 filled.
 * @param registers Aligned block of four quadwords.
 * @see vu0_save_vf15_vf18.
 */
static inline void vu0_restore_vf15_vf18(const void* registers)
{
    asm __volatile__(
        "lqc2 $vf15, 0x0(%0)\n"
        "lqc2 $vf16, 0x10(%0)\n"
        "lqc2 $vf17, 0x20(%0)\n"
        "lqc2 $vf18, 0x30(%0)\n"
        :
        : "r"(registers)
        : "memory");
}

/**
 * @brief Load a particle step and a sphere centre: previous position into vf15, current into vf16, centre into vf17.
 * @param previous Aligned previous position.
 * @param position Aligned current position.
 * @param centre Aligned sphere centre, w = 0.5.
 * @see Lib's sphere collider at 0x43BEB0.
 */
static inline void vu0_sphere_step_load(const void* previous, const void* position, const void* centre)
{
    asm __volatile__(
        "lqc2       $vf15, 0x0(%0)\n"
        "lqc2       $vf16, 0x0(%1)\n"
        "lqc2       $vf17, 0x0(%2)\n"
        :
        : "r"(previous), "r"(position), "r"(centre)
        : "memory");
}

/**
 * @brief Measure the step against the sphere: x and y of the result get the squared distances of the previous and
 *        current positions from the centre; vf22 keeps the midpoint offset (scaled by the centre's w) and vf23 its
 *        square.
 * @param distances Aligned destination.
 * @see vu0_sphere_step_load.
 */
static inline void vu0_sphere_step_distances(void* distances)
{
    asm __volatile__(
        "vsub.xyz   $vf18, $vf15, $vf17\n"
        "vsub.xyz   $vf19, $vf16, $vf17\n"
        "vadd.xyz   $vf22, $vf18, $vf19\n"
        "vmul.xyz   $vf20, $vf18, $vf18\n"
        "vmul.xyz   $vf21, $vf19, $vf19\n"
        "vaddw.xyz  $vf31, $vf0, $vf0w\n"
        "vmulw.xyz  $vf22, $vf22, $vf17w\n"
        "vadday.x   $ACC, $vf20, $vf20y\n"
        "vmaddz.x   $vf20, $vf31, $vf20z\n"
        "vaddax.y   $ACC, $vf21, $vf21x\n"
        "vmul.xyz   $vf23, $vf22, $vf22\n"
        "vmaddz.y   $vf20, $vf31, $vf21z\n"
        "sqc2       $vf20, 0x0(%0)\n"
        :
        : "r"(distances)
        : "memory");
}

/**
 * @brief Load the radius (x of a vector) into vf21 and start the reciprocal length of the midpoint offset.
 * @param radius Aligned vector with the radius in x.
 * @see Lib's sphere collider at 0x43BEB0.
 */
static inline void vu0_sphere_normal_start(const void* radius)
{
    asm __volatile__(
        "lqc2       $vf21, 0x0(%0)\n"
        "vadday.x   $ACC, $vf23, $vf23y\n"
        "vmaddz.x   $vf23, $vf31, $vf23z\n"
        "vrsqrt     $Q, $vf0w, $vf23x\n"
        :
        : "r"(radius)
        : "memory");
}

/**
 * @brief Load the bounce terms into vf24, the particle velocity into vf25 and the sphere's velocity into vf19.
 * @param terms Aligned bounce terms: x restitution sign, y scale, z friction.
 * @param velocity Aligned particle velocity.
 * @param sphere_velocity Aligned sphere velocity.
 * @see Lib's sphere collider at 0x43BEB0.
 */
static inline void vu0_sphere_load_bounce(const void* terms, const void* velocity, const void* sphere_velocity)
{
    asm __volatile__(
        "lqc2       $vf24, 0x0(%0)\n"
        "lqc2       $vf25, 0x0(%1)\n"
        "lqc2       $vf19, 0x0(%2)\n"
        :
        : "r"(terms), "r"(velocity), "r"(sphere_velocity)
        : "memory");
}

/**
 * @brief Finish the bounce: store the unit normal, the point on the sphere and the reflected velocity.
 * @param normal Aligned destination for the normal.
 * @param position Aligned destination for the corrected position.
 * @param velocity Aligned destination for the new velocity.
 * @see Lib's sphere collider at 0x43BEB0.
 */
static inline void vu0_sphere_bounce(void* normal, void* position, void* velocity)
{
    asm __volatile__(
        "vwaitq\n"
        "vmulq.xyz  $vf22, $vf22, $Q\n"
        "sqc2       $vf22, 0x0(%0)\n"
        "vadda.xyz  $ACC, $vf0, $vf17\n"
        "vmaddx.xyz $vf23, $vf22, $vf21x\n"
        "sqc2       $vf23, 0x0(%1)\n"
        "vmul.xyz   $vf19, $vf19, $vf22\n"
        "vmulx.xyz  $vf15, $vf25, $vf24x\n"
        "vmul.xyz   $vf16, $vf15, $vf22\n"
        "vadday.x   $ACC, $vf16, $vf16y\n"
        "vmaddz.x   $vf16, $vf31, $vf16z\n"
        "vadday.x   $ACC, $vf19, $vf19y\n"
        "vmaddaw.x  $ACC, $vf16, $vf0w\n"
        "vmaddz.x   $vf16, $vf31, $vf19z\n"
        "vmuly.x    $vf16, $vf16, $vf24y\n"
        "vmulx.xyz  $vf17, $vf22, $vf16x\n"
        "vadd.xyz   $vf18, $vf17, $vf25\n"
        "vadda.xyz  $ACC, $vf0, $vf17\n"
        "vmaddz.xyz $vf18, $vf18, $vf24z\n"
        "sqc2       $vf18, 0x0(%2)\n"
        :
        : "r"(normal), "r"(position), "r"(velocity)
        : "memory");
}

#endif
