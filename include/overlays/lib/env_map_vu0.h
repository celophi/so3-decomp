#ifndef SO3_OVERLAYS_LIB_ENV_MAP_VU0_H
#define SO3_OVERLAYS_LIB_ENV_MAP_VU0_H

/**
 * @brief Load the camera position into vf1 and a rotation's first three rows into vf2-vf4, then clear vf25.
 * @param position 16-byte aligned camera position.
 * @param rotation 16-byte aligned rotation matrix.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibClass174C70::func_slot10 in Lib.
 */
static inline void vu0_load_env_map_basis(const void* position, const void* rotation)
{
    asm __volatile__("lqc2 $vf1, 0x0(%0)\n"
                     "lqc2 $vf2, 0x0(%1)\n"
                     "lqc2 $vf3, 0x10(%1)\n"
                     "lqc2 $vf4, 0x20(%1)\n"
                     "qmtc2.ni $zero, $vf25" : : "r"(position), "r"(rotation) : "memory");
}

/**
 * @brief Load a vertex and its normal into vf6 and vf7 and start the microprogram at 0x3B0, which leaves the
 *        vertex's environment map coordinates in vf25.
 * @param vector 16-byte aligned vertex.
 * @param normal 16-byte aligned normal.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6); LibClass174C70::func_slot10 in Lib.
 */
static inline void vu0_start_env_map(const void* vector, const void* normal)
{
    asm __volatile__("lqc2 $vf6, 0x0(%0)\n"
                     "lqc2 $vf7, 0x0(%1)\n"
                     "nop\n"
                     "vcallms 0x3B0" : : "r"(vector), "r"(normal) : "memory");
}

/**
 * @brief Store the running program's vf25, then start the microprogram at 0x3B0 on the next vertex.
 *
 * The game always reads into t1 here, so I've hard-coded it.
 * @param result 16-byte aligned destination of the previous coordinates.
 * @param vector 16-byte aligned next vertex.
 * @param normal 16-byte aligned next normal.
 * @see vu0_start_env_map.
 */
static inline void vu0_restart_env_map(void* result, const void* vector, const void* normal)
{
    asm __volatile__("cfc2.i $t1, $vi0\n"
                     "sqc2 $vf25, 0x0(%0)\n"
                     "lqc2 $vf6, 0x0(%1)\n"
                     "lqc2 $vf7, 0x0(%2)\n"
                     "nop\n"
                     "vcallms 0x3B0" : : "r"(result), "r"(vector), "r"(normal) : "$t1", "memory");
}

/**
 * @brief Wait for the running microprogram and store vf25.
 * @param result 16-byte aligned destination.
 * @see vu0_start_env_map.
 */
static inline void vu0_wait_store_vf25(void* result)
{
    asm __volatile__("cfc2.i $t1, $vi0\n"
                     "sqc2 $vf25, 0x0(%0)" : : "r"(result) : "$t1", "memory");
}

/**
 * @brief vu0_load_env_map_basis, then put a parameter in vf29 for microprogram 0x5B0.
 * @param position 16-byte aligned camera position.
 * @param rotation 16-byte aligned rotation matrix.
 * @param parameter Word for vf29.
 * @see LibClass174CB0::func_slot10 in Lib.
 */
static inline void vu0_load_env_map_basis_vf29(const void* position, const void* rotation, u32 parameter)
{
    asm __volatile__("lqc2 $vf1, 0x0(%0)\n"
                     "lqc2 $vf2, 0x0(%1)\n"
                     "lqc2 $vf3, 0x10(%1)\n"
                     "lqc2 $vf4, 0x20(%1)\n"
                     "qmtc2.ni $zero, $vf25\n"
                     "qmtc2.ni %2, $vf29" : : "r"(position), "r"(rotation), "r"(parameter) : "memory");
}

/**
 * @brief vu0_start_env_map with the microprogram at 0x5B0, which also reads vf29.
 * @param vector 16-byte aligned vertex.
 * @param normal 16-byte aligned normal.
 * @see LibClass174CB0::func_slot10 in Lib.
 */
static inline void vu0_start_env_map_5b0(const void* vector, const void* normal)
{
    asm __volatile__("lqc2 $vf6, 0x0(%0)\n"
                     "lqc2 $vf7, 0x0(%1)\n"
                     "nop\n"
                     "vcallms 0x5B0" : : "r"(vector), "r"(normal) : "memory");
}

/**
 * @brief vu0_restart_env_map with the microprogram at 0x5B0.
 * @param result 16-byte aligned destination of the previous coordinates.
 * @param vector 16-byte aligned next vertex.
 * @param normal 16-byte aligned next normal.
 * @see LibClass174CB0::func_slot10 in Lib.
 */
static inline void vu0_restart_env_map_5b0(void* result, const void* vector, const void* normal)
{
    asm __volatile__("cfc2.i $t1, $vi0\n"
                     "sqc2 $vf25, 0x0(%0)\n"
                     "lqc2 $vf6, 0x0(%1)\n"
                     "lqc2 $vf7, 0x0(%2)\n"
                     "nop\n"
                     "vcallms 0x5B0" : : "r"(result), "r"(vector), "r"(normal) : "$t1", "memory");
}

#endif
