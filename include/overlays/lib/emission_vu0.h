#ifndef SO3_OVERLAYS_LIB_EMISSION_VU0_H
#define SO3_OVERLAYS_LIB_EMISSION_VU0_H

/**
 * @brief Transform a point using four matrix rows and an implicit fourth component of one.
 * @param matrix Aligned four-row transformation matrix.
 * @param input Aligned source point.
 * @param output Aligned destination vector.
 */
static inline void vu0_transform_emission_point(const void* matrix, const void* input, void* output)
{
    asm __volatile__(
        "lqc2 $vf5, 0x00(%1)\n"
        "lqc2 $vf1, 0x00(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "lqc2 $vf4, 0x30(%0)\n"
        "vmulax.xyzw $ACC, $vf1, $vf5x\n"
        "vmadday.xyzw $ACC, $vf2, $vf5y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf5z\n"
        "vmaddw.xyzw $vf5, $vf4, $vf0w\n"
        "sqc2 $vf5, 0x00(%2)\n"
        :
        : "r"(matrix), "r"(input), "r"(output)
        : "memory");
}

/**
 * @brief Transform a direction using three matrix rows.
 * @param matrix Aligned four-row transformation matrix.
 * @param input Aligned source direction.
 * @param output Aligned destination vector.
 */
static inline void vu0_transform_emission_direction(const void* matrix, const void* input, void* output)
{
    asm __volatile__(
        "lqc2 $vf4, 0x00(%1)\n"
        "lqc2 $vf1, 0x00(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "vmulax.xyzw $ACC, $vf1, $vf4x\n"
        "vmadday.xyzw $ACC, $vf2, $vf4y\n"
        "vmaddz.xyzw $vf4, $vf3, $vf4z\n"
        "sqc2 $vf4, 0x00(%2)\n"
        :
        : "r"(matrix), "r"(input), "r"(output)
        : "memory");
}

/**
 * @brief Save the VU0 emitter registers preserved around nested emission.
 * @param output Aligned storage for vf18 and vf29.
 */
static inline void vu0_save_emission_state(void* output)
{
    asm __volatile__(
        "sqc2 $vf18, 0x00(%0)\n"
        "sqc2 $vf29, 0x10(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief Restore the VU0 emitter registers after nested emission.
 * @param input Aligned saved vf18 and vf29 values.
 */
static inline void vu0_restore_emission_state(const void* input)
{
    asm __volatile__(
        "lqc2 $vf18, 0x00(%0)\n"
        "lqc2 $vf29, 0x10(%0)\n"
        :
        : "r"(input)
        : "memory");
}

/**
 * @brief Clear the VU0 emission accumulators.
 */
static inline void vu0_reset_emission_state()
{
    asm __volatile__(
        "vmove.xyz $vf17, $vf0\n"
        "vmulx.xyzw $vf30, $vf0, $vf0x\n"
        :
        :
        : "memory");
}

/**
 * @brief Restore the current emission time step in VU0.
 * @param value Time step to load into vf5.
 */
static inline void vu0_set_emission_delta(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf5\n" : : "r"(value) : "memory");
}

#endif
