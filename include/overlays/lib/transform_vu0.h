#ifndef SO3_OVERLAYS_LIB_TRANSFORM_VU0_H
#define SO3_OVERLAYS_LIB_TRANSFORM_VU0_H

/**
 * @brief Load the transform's scale into vf17.
 * @param scale Aligned scale vector.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf). Lib uses these in
 *      LibTransform::update_transform_matrix, func_004DA730, func_004DAB50 and lib_rebuild_offset_transform.
 */
static inline void vu0_load_scale_vf17(const void* scale)
{
    asm __volatile__("lqc2 $vf17, 0x0(%0)" : : "r"(scale) : "memory");
}

/**
 * @brief Load the transform's rotation quaternion into vf5.
 * @param rotation Aligned quaternion.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_load_rotation_vf5(const void* rotation)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)" : : "r"(rotation) : "memory");
}

/**
 * @brief Load the transform's translation into vf16.
 * @param translation Aligned translation vector.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_load_translation_vf16(const void* translation)
{
    asm __volatile__("lqc2 $vf16, 0x0(%0)" : : "r"(translation) : "memory");
}

/**
 * @brief Start the microprogram at 0x728, which builds the rotation rows in vf8-vf10 from vf5 and vf16.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_start_microprogram_728(void)
{
    asm __volatile__("nop\n"
                     "vcallms 0x728" : : : "memory");
}

/**
 * @brief Load the first three rows of a matrix into vf1-vf3.
 * @param matrix Aligned matrix.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_load_rows_vf1_vf3(const void* matrix)
{
    asm __volatile__("lqc2 $vf1, 0x0(%0)\n"
                     "lqc2 $vf2, 0x10(%0)\n"
                     "lqc2 $vf3, 0x20(%0)" : : "r"(matrix) : "memory");
}

/**
 * @brief Start the microprogram at 0xAE8, which combines the rows in vf1-vf3 with the rotation.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_start_microprogram_ae8(void)
{
    asm __volatile__("vcallms 0xAE8" : : : "memory");
}

/**
 * @brief Start the microprogram at 0x830 and scale the rows in vf1-vf3 by vf17.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_start_microprogram_830_scale_rows(void)
{
    asm __volatile__("nop\n"
                     "vcallms 0x830\n"
                     "vmul.xyzw $vf1, $vf1, $vf17\n"
                     "vmul.xyzw $vf2, $vf2, $vf17\n"
                     "vmul.xyzw $vf3, $vf3, $vf17" : : : "memory");
}

/**
 * @brief Scale the rotation rows in vf8-vf10 by vf17 into vf1-vf3.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_scale_rotation_rows(void)
{
    asm __volatile__("vmul.xyzw $vf1, $vf17, $vf8\n"
                     "vmul.xyzw $vf2, $vf17, $vf9\n"
                     "vmul.xyzw $vf3, $vf17, $vf10" : : : "memory");
}

/**
 * @brief Load a matrix into vf5-vf7 and vf4.
 * @param matrix Aligned matrix.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_load_matrix_vf5_vf7_vf4(const void* matrix)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)\n"
                     "lqc2 $vf6, 0x10(%0)\n"
                     "lqc2 $vf7, 0x20(%0)\n"
                     "lqc2 $vf4, 0x30(%0)" : : "r"(matrix) : "memory");
}

/**
 * @brief Load a matrix into vf5-vf8.
 * @param matrix Aligned matrix.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_load_matrix_vf5_vf8(const void* matrix)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)\n"
                     "lqc2 $vf6, 0x10(%0)\n"
                     "lqc2 $vf7, 0x20(%0)\n"
                     "lqc2 $vf8, 0x30(%0)" : : "r"(matrix) : "memory");
}

/**
 * @brief Multiply the rows in vf1-vf3 by the matrix in vf5-vf7 and vf4, and store both results.
 * @param base Aligned matrix receiving vf1-vf3 and the identity row.
 * @param result Aligned matrix receiving the product, with vf4 as its last row.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_multiply_store_vf4(void* base, void* result)
{
    asm __volatile__("vmulax.xyzw $ACC, $vf5, $vf1x\n"
                     "vmadday.xyzw $ACC, $vf6, $vf1y\n"
                     "vmaddaz.xyzw $ACC, $vf7, $vf1z\n"
                     "vmaddw.xyzw $vf9, $vf4, $vf1w\n"
                     "vmulax.xyzw $ACC, $vf5, $vf2x\n"
                     "vmadday.xyzw $ACC, $vf6, $vf2y\n"
                     "vmaddaz.xyzw $ACC, $vf7, $vf2z\n"
                     "vmaddw.xyzw $vf10, $vf4, $vf2w\n"
                     "vmulax.xyzw $ACC, $vf5, $vf3x\n"
                     "vmadday.xyzw $ACC, $vf6, $vf3y\n"
                     "vmaddaz.xyzw $ACC, $vf7, $vf3z\n"
                     "vmaddw.xyzw $vf11, $vf4, $vf3w\n"
                     "sqc2 $vf1, 0x0(%0)\n"
                     "sqc2 $vf2, 0x10(%0)\n"
                     "sqc2 $vf3, 0x20(%0)\n"
                     "sqc2 $vf0, 0x30(%0)\n"
                     "sqc2 $vf9, 0x0(%1)\n"
                     "sqc2 $vf10, 0x10(%1)\n"
                     "sqc2 $vf11, 0x20(%1)\n"
                     "sqc2 $vf4, 0x30(%1)" : : "r"(base), "r"(result) : "memory");
}

/**
 * @brief Multiply the rows in vf1-vf3 by the matrix in vf5-vf8, and store both results.
 * @param base Aligned matrix receiving vf1-vf3 and the identity row.
 * @param result Aligned matrix receiving the product, with vf8 as its last row.
 * @see vu0_load_scale_vf17.
 */
static inline void vu0_multiply_store_vf8(void* base, void* result)
{
    asm __volatile__("vmulax.xyzw $ACC, $vf5, $vf1x\n"
                     "vmadday.xyzw $ACC, $vf6, $vf1y\n"
                     "vmaddaz.xyzw $ACC, $vf7, $vf1z\n"
                     "vmaddw.xyzw $vf9, $vf8, $vf1w\n"
                     "vmulax.xyzw $ACC, $vf5, $vf2x\n"
                     "vmadday.xyzw $ACC, $vf6, $vf2y\n"
                     "vmaddaz.xyzw $ACC, $vf7, $vf2z\n"
                     "vmaddw.xyzw $vf10, $vf8, $vf2w\n"
                     "vmulax.xyzw $ACC, $vf5, $vf3x\n"
                     "vmadday.xyzw $ACC, $vf6, $vf3y\n"
                     "vmaddaz.xyzw $ACC, $vf7, $vf3z\n"
                     "vmaddw.xyzw $vf11, $vf8, $vf3w\n"
                     "sqc2 $vf1, 0x0(%0)\n"
                     "sqc2 $vf2, 0x10(%0)\n"
                     "sqc2 $vf3, 0x20(%0)\n"
                     "sqc2 $vf0, 0x30(%0)\n"
                     "sqc2 $vf9, 0x0(%1)\n"
                     "sqc2 $vf10, 0x10(%1)\n"
                     "sqc2 $vf11, 0x20(%1)\n"
                     "sqc2 $vf8, 0x30(%1)" : : "r"(base), "r"(result) : "memory");
}

#endif
