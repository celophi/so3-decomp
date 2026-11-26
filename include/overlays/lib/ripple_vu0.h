#ifndef SO3_OVERLAYS_LIB_RIPPLE_VU0_H
#define SO3_OVERLAYS_LIB_RIPPLE_VU0_H

/**
 * @brief Set vf31's x, y and z to one (vf0's w).
 *
 * Microprogram 0x9B0 reads it when it normalizes the ripple grid's normals.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibClass174C20::func_slot1C (0x452750) in Lib.
 */
static inline void vu0_set_vf31_one(void)
{
    asm __volatile__("vaddw.xyz $vf31, $vf0, $vf0w" : : : "memory");
}

/**
 * @brief Load a vector into vf1 and start the microprogram at 0x9B0, which leaves its normal in vf3.
 * @param vector 16-byte aligned vector.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6); LibClass174C20::func_slot1C in Lib.
 */
static inline void vu0_start_microprogram_9b0_vf1(const void* vector)
{
    asm __volatile__("lqc2 $vf1, 0x0(%0)\n"
                     "nop\n"
                     "vcallms 0x9B0" : : "r"(vector) : "memory");
}

/**
 * @brief Load the next vector into vf1, store the running program's vf3, then start the microprogram at 0x9B0
 *        again.
 *
 * The game always writes vi0 first and reads into t1 here, so both are hard-coded.
 * @param vector 16-byte aligned next vector.
 * @param result 16-byte aligned destination of the previous normal.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6); LibClass174C20::func_slot1C in Lib.
 */
static inline void vu0_restart_microprogram_9b0_vf1(const void* vector, void* result)
{
    asm __volatile__("ctc2.i $zero, $vi0\n"
                     "lqc2 $vf1, 0x0(%0)\n"
                     "cfc2.i $t1, $vi0\n"
                     "sqc2 $vf3, 0x0(%1)\n"
                     "nop\n"
                     "vcallms 0x9B0" : : "r"(vector), "r"(result) : "$t1", "memory");
}

/**
 * @brief Wait for the running microprogram and store vf3.
 * @param result 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibClass174C20::func_slot1C in Lib.
 */
static inline void vu0_wait_store_vf3(void* result)
{
    asm __volatile__("cfc2.i $t1, $vi0\n"
                     "sqc2 $vf3, 0x0(%0)" : : "r"(result) : "$t1", "memory");
}

/**
 * @brief Load the spread weights: vf10.x = step, vf11.x = 4 * step.
 * @param step Spread step for this frame.
 * @param step4 Four times the step.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibClass173490::func_slot1C (0x42E240) in Lib.
 */
static inline void vu0_ripple_set_steps(float step, float step4)
{
    asm __volatile__(
        "qmtc2.ni %0, $vf10\n"
        "qmtc2.ni %1, $vf11\n"
        :
        : "r"(step), "r"(step4));
}

/**
 * @brief Load the first two heights of a row: vf3 = left[0], vf4 = left[1].
 * @param left Aligned height cell left of the first spread cell.
 * @see vu0_ripple_set_steps.
 */
static inline void vu0_ripple_load_row(const void* left)
{
    asm __volatile__(
        "lqc2 $vf3, 0x0(%0)\n"
        "lqc2 $vf4, 0x10(%0)\n"
        :
        : "r"(left)
        : "memory");
}

/**
 * @brief Move the row window one cell right: vf2 = vf3, vf3 = vf4, vf4 = left[1].
 * @param left Aligned height cell left of the next one to load.
 * @see vu0_ripple_set_steps.
 */
static inline void vu0_ripple_rotate(const void* left)
{
    asm __volatile__(
        "vmulw.xyzw $vf2, $vf3, $vf0w\n"
        "vmulw.xyzw $vf3, $vf4, $vf0w\n"
        "lqc2       $vf4, 0x10(%0)\n"
        :
        : "r"(left)
        : "memory");
}

/**
 * @brief vf15 = velocity + step * (left + right + up + down) - 4 * step * centre.
 * @param velocity Aligned velocity cell.
 * @param up Aligned height cell one row up.
 * @param down Aligned height cell one row down.
 * @see vu0_ripple_set_steps.
 */
static inline void vu0_ripple_spread(const void* velocity, const void* up, const void* down)
{
    asm __volatile__(
        "pref       0, 0x40(%0)\n"
        "lqc2       $vf5, 0x0(%1)\n"
        "lqc2       $vf6, 0x0(%2)\n"
        "lqc2       $vf7, 0x0(%0)\n"
        "pref       0, 0x40(%2)\n"
        "vmulax.xyzw $ACC, $vf2, $vf10x\n"
        "vmaddax.xyz $ACC, $vf4, $vf10x\n"
        "vmaddax.xyz $ACC, $vf5, $vf10x\n"
        "vmaddax.xyz $ACC, $vf6, $vf10x\n"
        "vmsubax.xyz $ACC, $vf3, $vf11x\n"
        "vmaddw.xyz $vf15, $vf7, $vf0w\n"
        :
        : "r"(velocity), "r"(up), "r"(down)
        : "memory");
}

/**
 * @brief vf9 = step * (left + right + up + down) - 4 * step * centre, vf7 = velocity, vf8.x = the cell's weight.
 * @param velocity Aligned velocity cell.
 * @param up Aligned height cell one row up.
 * @param down Aligned height cell one row down.
 * @param weight Mask weight of the cell (float bits).
 * @see vu0_ripple_weight_spread.
 */
static inline void vu0_ripple_spread_masked(const void* velocity, const void* up, const void* down, u32 weight)
{
    asm __volatile__(
        "pref       0, 0x40(%0)\n"
        "lqc2       $vf5, 0x0(%1)\n"
        "lqc2       $vf6, 0x0(%2)\n"
        "lqc2       $vf7, 0x0(%0)\n"
        "qmtc2.ni   %3, $vf8\n"
        "pref       0, 0x40(%2)\n"
        "vmulax.xyzw $ACC, $vf2, $vf10x\n"
        "vmaddax.xyz $ACC, $vf4, $vf10x\n"
        "vmaddax.xyz $ACC, $vf5, $vf10x\n"
        "vmaddax.xyz $ACC, $vf6, $vf10x\n"
        "vmsubx.xyz $vf9, $vf3, $vf11x\n"
        :
        : "r"(velocity), "r"(up), "r"(down), "r"(weight)
        : "memory");
}

/**
 * @brief vf15 = weight * (velocity + spread), from vu0_ripple_spread_masked's vf7, vf8 and vf9.
 * @see vu0_ripple_spread_masked.
 */
static inline void vu0_ripple_weight_spread(void)
{
    asm __volatile__(
        "vmulax.xyzw $ACC, $vf7, $vf8x\n"
        "vmaddx.xyzw $vf15, $vf9, $vf8x\n");
}

/**
 * @brief Store the new velocity (vf15).
 * @param velocity Aligned velocity cell.
 * @see vu0_ripple_spread.
 */
static inline void vu0_ripple_store_velocity(void* velocity)
{
    asm __volatile__("sqc2 $vf15, 0x0(%0)\n" : : "r"(velocity) : "memory");
}

/**
 * @brief Load the frame time into vf1.x for the height integration.
 * @param seconds Frame time.
 * @see vu0_ripple_integrate.
 */
static inline void vu0_ripple_set_frame(float seconds)
{
    asm __volatile__("qmtc2.ni %0, $vf1\n" : : "r"(seconds));
}

/**
 * @brief Load a height (vf2) and its velocity (vf3).
 * @param height Aligned height cell.
 * @param velocity Aligned velocity cell.
 * @see vu0_ripple_integrate.
 */
static inline void vu0_ripple_load_cell(const void* height, const void* velocity)
{
    asm __volatile__(
        "lqc2 $vf2, 0x0(%0)\n"
        "lqc2 $vf3, 0x0(%1)\n"
        :
        : "r"(height), "r"(velocity)
        : "memory");
}

/**
 * @brief vf2 = height + velocity * frame time.
 * @see vu0_ripple_load_cell.
 */
static inline void vu0_ripple_integrate(void)
{
    asm __volatile__(
        "vmulaw.xyzw $ACC, $vf2, $vf0w\n"
        "vmaddx.xyzw $vf2, $vf3, $vf1x\n");
}

/**
 * @brief Store the integrated height (vf2).
 * @param height Aligned height cell.
 * @see vu0_ripple_integrate.
 */
static inline void vu0_ripple_store_height(void* height)
{
    asm __volatile__("sqc2 $vf2, 0x0(%0)\n" : : "r"(height) : "memory");
}

#endif
