#ifndef SO3_OVERLAYS_LIB_BOUNDING_SPHERE_VU0_H
#define SO3_OVERLAYS_LIB_BOUNDING_SPHERE_VU0_H

/**
 * @brief Load a matrix's first three rows into vf12-vf14 and start the microprogram at 0xAA0, which leaves the
 *        length of each row in vf6.
 * @param matrix 16-byte aligned matrix.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6); LibModel::get_bounding_sphere in Lib.
 */
static inline void vu0_start_row_scale(const void* matrix)
{
    asm __volatile__("lqc2 $vf12, 0x0(%0)\n"
                     "lqc2 $vf13, 0x10(%0)\n"
                     "lqc2 $vf14, 0x20(%0)\n"
                     "nop\n"
                     "vcallms 0xAA0" : : "r"(matrix) : "memory");
}

/**
 * @brief Transpose a 16-byte aligned 4x4 matrix into t8, t3, t2 and t0 for vu0_transform_by_transposed.
 *
 * The rows stay in those registers until vu0_transform_by_transposed moves them to VU0, so nothing in between may
 * use them.
 * @param matrix Aligned matrix.
 * @see EE Core Instruction Set Manual (PEXTLW, PEXTUW, PCPYLD, PCPYUD, LQ); LibModel::get_bounding_sphere in Lib.
 */
static inline void ee_transpose_matrix_to_registers(const void* matrix)
{
    // TODO: Two asm blocks sharing hard-coded registers is fragile; the game keeps the rows there across C code.
    asm __volatile__("lq $t8, 0x0(%0)\n"
                     "lq $t3, 0x10(%0)\n"
                     "lq $t2, 0x20(%0)\n"
                     "lq $t0, 0x30(%0)\n"
                     "pextlw $t4, $t3, $t8\n"
                     "pextuw $t5, $t3, $t8\n"
                     "pextlw $t6, $t0, $t2\n"
                     "pextuw $t7, $t0, $t2\n"
                     "pcpyld $t8, $t6, $t4\n"
                     "pcpyud $t3, $t4, $t6\n"
                     "pcpyld $t2, $t7, $t5\n"
                     "pcpyud $t0, $t5, $t7"
                     :
                     : "r"(matrix)
                     : "$t0", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "memory");
}

/**
 * @brief Move the rows ee_transpose_matrix_to_registers left in t8, t3, t2 and t0 to vf12-vf15 and transform a
 *        point by them; w keeps the point's own w.
 * @param point 16-byte aligned point.
 * @param out 16-byte aligned result.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibModel::get_bounding_sphere in Lib.
 */
static inline void vu0_transform_by_transposed(const void* point, void* out)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)\n"
                     "qmtc2.ni $t8, $vf12\n"
                     "qmtc2.ni $t3, $vf13\n"
                     "qmtc2.ni $t2, $vf14\n"
                     "qmtc2.ni $t0, $vf15\n"
                     "vmulax.xyzw $ACC, $vf12, $vf5x\n"
                     "vmadday.xyzw $ACC, $vf13, $vf5y\n"
                     "vmaddaz.xyzw $ACC, $vf14, $vf5z\n"
                     "vmaddw.xyz $vf5, $vf15, $vf0w\n"
                     "sqc2 $vf5, 0x0(%1)"
                     :
                     : "r"(point), "r"(out)
                     : "memory");
}

#endif
