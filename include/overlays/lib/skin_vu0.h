#ifndef SO3_OVERLAYS_LIB_SKIN_VU0_H
#define SO3_OVERLAYS_LIB_SKIN_VU0_H

/**
 * @brief Load the model's inverse root matrix into vf28-vf31 for the skinning microprogram at 0x898.
 * @param matrix 16-byte aligned matrix.
 * @see Lib's skinning matrix builder at 0x4ABAC0.
 */
static inline void vu0_skin_load_root(const void* matrix)
{
    asm __volatile__(
        "lqc2       $vf28, 0x0(%0)\n"
        "lqc2       $vf29, 0x10(%0)\n"
        "lqc2       $vf30, 0x20(%0)\n"
        "lqc2       $vf31, 0x30(%0)\n"
        :
        : "r"(matrix)
        : "memory");
}

/**
 * @brief Load a bone's matrix into vf9-vf12 and its bind matrix into vf13-vf16.
 * @param bone 16-byte aligned bone matrix.
 * @param bind 16-byte aligned bind matrix.
 * @see vu0_skin_load_root.
 */
static inline void vu0_skin_load_bone(const void* bone, const void* bind)
{
    asm __volatile__(
        "lqc2       $vf9, 0x0(%0)\n"
        "lqc2       $vf10, 0x10(%0)\n"
        "lqc2       $vf11, 0x20(%0)\n"
        "lqc2       $vf12, 0x30(%0)\n"
        "lqc2       $vf13, 0x0(%1)\n"
        "lqc2       $vf14, 0x10(%1)\n"
        "lqc2       $vf15, 0x20(%1)\n"
        "lqc2       $vf16, 0x30(%1)\n"
        :
        : "r"(bone), "r"(bind)
        : "memory");
}

/**
 * @brief Start the skinning microprogram at 0x898 on the loaded bone.
 * @see vu0_skin_load_bone.
 */
static inline void vu0_skin_start(void)
{
    asm __volatile__(
        "nop\n"
        "vcallms    0x898\n");
}

/**
 * @brief Wait for the previous bone's result and store vf1-vf4, with the wait's flags discarded.
 * @param output 16-byte aligned destination matrix.
 * @see vu0_skin_start.
 */
static inline void vu0_skin_store_previous(void* output)
{
    asm __volatile__(
        "cfc2.i     $0, $vi0\n"
        "sqc2       $vf1, 0x0(%0)\n"
        "sqc2       $vf2, 0x10(%0)\n"
        "sqc2       $vf3, 0x20(%0)\n"
        "sqc2       $vf4, 0x30(%0)\n"
        :
        : "r"(output)
        : "memory");
}

/**
 * @brief Wait for the last bone's result and store vf1-vf4.
 * @param output 16-byte aligned destination matrix.
 * @see vu0_skin_start.
 */
static inline void vu0_skin_store_last(void* output)
{
    asm __volatile__(
        "cfc2.i     $9, $vi0\n"
        "sqc2       $vf1, 0x0(%0)\n"
        "sqc2       $vf2, 0x10(%0)\n"
        "sqc2       $vf3, 0x20(%0)\n"
        "sqc2       $vf4, 0x30(%0)\n"
        :
        : "r"(output)
        : "$9", "memory");
}

#endif
