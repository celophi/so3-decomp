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

#endif
