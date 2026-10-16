#ifndef SO3_OVERLAYS_1067_00_GRID_FRAME_VU0_H
#define SO3_OVERLAYS_1067_00_GRID_FRAME_VU0_H

/**
 * @brief Load the frame time step into vf3.
 * @param value Time step in seconds.
 */
static inline void vu0_set_grid_frame_delta(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf3\n" : : "r"(value) : "memory");
}

/**
 * @brief Load an animated vector into vf1 and its rate into vf2.
 * @param value Aligned current vector.
 * @param rate Aligned rate vector.
 */
static inline void vu0_load_grid_frame_vectors(const void* value, const void* rate)
{
    asm __volatile__(
        "lqc2 $vf1, 0x0(%0)\n"
        "lqc2 $vf2, 0x0(%1)\n"
        : : "r"(value), "r"(rate) : "memory");
}

/** @brief Add the rate times the time step to the first three components of vf1. */
static inline void vu0_advance_grid_frame_vector()
{
    asm __volatile__(
        "vadda.xyz $ACC, $vf0, $vf1\n"
        "vmaddx.xyz $vf1, $vf2, $vf3x\n"
        : : : "memory");
}

/**
 * @brief Store the updated vector from vf1.
 * @param output Aligned destination.
 */
static inline void vu0_store_grid_frame_vector(void* output)
{
    asm __volatile__("sqc2 $vf1, 0x0(%0)\n" : : "r"(output) : "memory");
}

#endif
