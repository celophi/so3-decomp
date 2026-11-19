#ifndef SO3_OVERLAYS_LIB_MORPH_VU0_H
#define SO3_OVERLAYS_LIB_MORPH_VU0_H

/**
 * @brief Load the morph weights into vf5 for the microprogram at 0x340.
 * @param weights 16-byte aligned weights.
 * @see LibClass1789C0::func_slot10 in Lib (0x4A9600).
 */
static inline void vu0_morph_load_weights(const void* weights)
{
    asm __volatile__("lqc2       $vf5, 0x0(%0)\n" : : "r"(weights) : "memory");
}

/**
 * @brief Load a vertex's vector and value into vf1/vf2 and the record entry's two deltas into vf3/vf4.
 * @param vector 16-byte aligned vertex vector.
 * @param value 16-byte aligned vertex value.
 * @param entry 16-byte aligned record entry.
 * @see vu0_morph_load_weights.
 */
static inline void vu0_morph_load(const void* vector, const void* value, const void* entry)
{
    asm __volatile__(
        "lqc2       $vf1, 0x0(%0)\n"
        "lqc2       $vf2, 0x0(%1)\n"
        "lqc2       $vf3, 0x0(%2)\n"
        "lqc2       $vf4, 0x10(%2)\n"
        :
        : "r"(vector), "r"(value), "r"(entry)
        : "memory");
}

/**
 * @brief Start the morph microprogram at 0x340 after a load.
 * @see vu0_morph_load.
 */
static inline void vu0_morph_start_after_load(void)
{
    asm __volatile__(
        "nop\n"
        "vcallms    0x340\n");
}

/**
 * @brief Start the morph microprogram at 0x340.
 * @see vu0_morph_load.
 */
static inline void vu0_morph_start(void)
{
    asm __volatile__("vcallms    0x340\n");
}

/**
 * @brief Wait for the morph microprogram.
 * @see vu0_morph_start.
 */
static inline void vu0_morph_wait(void)
{
    asm __volatile__("cfc2.i     $9, $vi0\n" : : : "$9");
}

/**
 * @brief Wait for the morph microprogram and store its vector (vf12) and value (vf13).
 * @param vector 16-byte aligned destination vector.
 * @param value 16-byte aligned destination value.
 * @see vu0_morph_start.
 */
static inline void vu0_morph_store(void* vector, void* value)
{
    asm __volatile__(
        "cfc2.i     $9, $vi0\n"
        "sqc2       $vf12, 0x0(%0)\n"
        "sqc2       $vf13, 0x0(%1)\n"
        :
        : "r"(vector), "r"(value)
        : "$9", "memory");
}

#endif
