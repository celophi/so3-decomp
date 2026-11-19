#ifndef SO3_OVERLAYS_LIB_GRID_FRAME_VU0_H
#define SO3_OVERLAYS_LIB_GRID_FRAME_VU0_H

/**
 * @brief Load the frame time step into vf3.
 * @param value Time step in seconds.
 * @see The emitter-grid frame-vector updates in Lib and Field (1067-00 field_update_grid_frame_vectors).
 */
static inline void vu0_set_grid_frame_delta(float value)
{
    asm __volatile__("qmtc2.ni %0, $vf3\n" : : "r"(value) : "memory");
}

/**
 * @brief Load an animated vector into vf1 and its rate into vf2.
 * @param value Aligned current vector.
 * @param rate Aligned rate vector.
 * @see The emitter-grid frame-vector updates in Lib and Field (1067-00 field_update_grid_frame_vectors).
 */
static inline void vu0_load_grid_frame_vectors(const void* value, const void* rate)
{
    asm __volatile__(
        "lqc2 $vf1, 0x0(%0)\n"
        "lqc2 $vf2, 0x0(%1)\n"
        : : "r"(value), "r"(rate) : "memory");
}

/**
 * @brief Add the rate times the time step to the first three components of vf1.
 * @see The emitter-grid frame-vector updates in Lib and Field (1067-00 field_update_grid_frame_vectors).
 */
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
 * @see The emitter-grid frame-vector updates in Lib and Field (1067-00 field_update_grid_frame_vectors).
 */
static inline void vu0_store_grid_frame_vector(void* output)
{
    asm __volatile__("sqc2 $vf1, 0x0(%0)\n" : : "r"(output) : "memory");
}

/**
 * @brief Load a grid's per-frame force vector into vf9.
 * @param force Aligned force vector.
 * @see The grid emission setup slots in Lib (0x49E270, 0x49EB80) and Field (1067-00 func_002ABD90).
 */
static inline void vu0_load_grid_force(const void* force)
{
    asm __volatile__("lqc2 $vf9, 0x0(%0)\n" : : "r"(force) : "memory");
}

/**
 * @brief Clear vf9's xyz when the grid has no force.
 * @see The grid emission setup slots in Lib (0x49E270, 0x49EB80) and Field (1067-00 func_002ABD90).
 */
static inline void vu0_clear_grid_force()
{
    asm __volatile__("vmove.xyz $vf9, $vf0\n" : : : "memory");
}

/**
 * @brief Clear vf10's xyz.
 * @see The grid emission setup slots in Lib (0x49E270, 0x49EB80) and Field (1067-00 func_002ABD90).
 */
static inline void vu0_clear_grid_vf10()
{
    asm __volatile__("vmove.xyz $vf10, $vf0\n" : : : "memory");
}

/**
 * @brief Clear vf30.
 * @see The grid emission setup slots in Lib (0x49E270, 0x49EB80) and Field (1067-00 func_002ABD90).
 */
static inline void vu0_clear_grid_vf30()
{
    asm __volatile__("vmulx.xyzw $vf30, $vf0, $vf0x\n" : : : "memory");
}

/**
 * @brief Load the grid's color limit into vf29.
 * @param limit Aligned color limit.
 * @see The grid emission setup slots in Lib (0x49E270, 0x49EB80) and Field (1067-00 func_002ABD90).
 */
static inline void vu0_load_grid_color_limit(const void* limit)
{
    asm __volatile__("lqc2 $vf29, 0x0(%0)\n" : : "r"(limit) : "memory");
}

/**
 * @brief Load a grid's per-frame force vector into vf18 (the grids whose emitters keep it there).
 * @param force Aligned force vector.
 * @see The grid emission setup slot in Lib 0x4A02D0 (LibClass177090).
 */
static inline void vu0_load_grid_force_vf18(const void* force)
{
    asm __volatile__("lqc2 $vf18, 0x0(%0)\n" : : "r"(force) : "memory");
}

/**
 * @brief Clear vf18's xyz when the grid has no force.
 * @see The grid emission setup slot in Lib 0x4A02D0 (LibClass177090).
 */
static inline void vu0_clear_grid_force_vf18()
{
    asm __volatile__("vmove.xyz $vf18, $vf0\n" : : : "memory");
}

/**
 * @brief Clear vf17's xyz.
 * @see The grid emission setup slot in Lib 0x4A02D0 (LibClass177090).
 */
static inline void vu0_clear_grid_vf17()
{
    asm __volatile__("vmove.xyz $vf17, $vf0\n" : : : "memory");
}

#endif
