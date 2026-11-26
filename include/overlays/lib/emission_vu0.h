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

/**
 * @brief vu0_transform_emission_direction with the direction's address taken first, which the colouring of some
 *        callers needs.
 * @param matrix Aligned four-row transformation matrix.
 * @param input Aligned source direction.
 * @param output Aligned destination vector.
 * @see vu0_transform_emission_direction; LibClass173990::emit_entries in Lib (0x435840).
 */
static inline void vu0_transform_emission_direction_input_first(const void* matrix, const void* input, void* output)
{
    asm __volatile__(
        "lqc2 $vf4, 0x00(%0)\n"
        "lqc2 $vf1, 0x00(%1)\n"
        "lqc2 $vf2, 0x10(%1)\n"
        "lqc2 $vf3, 0x20(%1)\n"
        "vmulax.xyzw $ACC, $vf1, $vf4x\n"
        "vmadday.xyzw $ACC, $vf2, $vf4y\n"
        "vmaddz.xyzw $vf4, $vf3, $vf4z\n"
        "sqc2 $vf4, 0x00(%2)\n"
        :
        : "r"(input), "r"(matrix), "r"(output)
        : "memory");
}

/**
 * @brief vu0_transform_emission_direction with the destination as the second asm operand.
 * @param matrix Aligned four-row transformation matrix.
 * @param output Aligned destination vector.
 * @param input Aligned source direction.
 * @see vu0_transform_emission_direction; LibClass173990::emit_entries in Lib (0x435840).
 */
static inline void vu0_transform_emission_direction_output_first(const void* matrix, void* output, const void* input)
{
    // TODO: Same instructions as vu0_transform_emission_direction; only the operand order differs, which moves the
    // addresses between registers. Check whether the original had a separate helper.
    asm __volatile__(
        "lqc2 $vf4, 0x00(%2)\n"
        "lqc2 $vf1, 0x00(%0)\n"
        "lqc2 $vf2, 0x10(%0)\n"
        "lqc2 $vf3, 0x20(%0)\n"
        "vmulax.xyzw $ACC, $vf1, $vf4x\n"
        "vmadday.xyzw $ACC, $vf2, $vf4y\n"
        "vmaddz.xyzw $vf4, $vf3, $vf4z\n"
        "sqc2 $vf4, 0x00(%1)\n"
        :
        : "r"(matrix), "r"(output), "r"(input)
        : "memory");
}

/**
 * @brief Clamp each component of a color between zero and the x component of a limit vector.
 * @param color Aligned color, clamped in place.
 * @param limit Aligned vector whose x component is the upper bound.
 * @see VMAXx and VMINIx in Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf);
 *      LibClass173990::emit_entries in Lib (0x435840).
 */
static inline void vu0_clamp_emission_color(void* color, const void* limit)
{
    asm __volatile__(
        "lqc2 $vf1, 0x00(%0)\n"
        "lqc2 $vf2, 0x00(%1)\n"
        "vmaxx.xyzw $vf1, $vf1, $vf0x\n"
        "vminix.xyzw $vf1, $vf1, $vf2x\n"
        "sqc2 $vf1, 0x00(%0)\n"
        :
        : "r"(color), "r"(limit)
        : "memory");
}

#endif
