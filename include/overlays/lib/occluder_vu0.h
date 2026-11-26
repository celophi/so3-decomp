#ifndef SO3_OVERLAYS_LIB_OCCLUDER_VU0_H
#define SO3_OVERLAYS_LIB_OCCLUDER_VU0_H

#include "types.h"

/**
 * @brief Load the occluder matrix into vf5-vf8 and start the microprogram at 0x1F0 with the VU0 slot in vi1.
 * @param matrix 16-byte aligned matrix.
 * @param slot VU0 data slot (quadword) the corners and normals go to.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_load_matrix(const void* matrix, s32 slot)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)\n"
                     "lqc2 $vf6, 0x10(%0)\n"
                     "lqc2 $vf7, 0x20(%0)\n"
                     "lqc2 $vf8, 0x30(%0)\n"
                     "ctc2.ni %1, $vi1\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0x1F0" : : "r"(matrix), "r"(slot) : "memory");
}

/**
 * @brief Transform the four corners (vf20-vf23) by the microprogram's vf1-vf4, store them through vi1, build the four edge normals against the viewer position in vf9 and the face normal in vf20, start normalising them, and transform the corners by the camera in vf24-vf27.
 * @param corners Four 16-byte aligned corners.
 * @param position Viewer position, 16-byte aligned.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_build_faces(const void* corners, const void* position)
{
    asm __volatile__("cfc2.i $zero, $vi0\n"
                     "lqc2 $vf20, 0x0(%0)\n"
                     "lqc2 $vf21, 0x10(%0)\n"
                     "lqc2 $vf22, 0x20(%0)\n"
                     "lqc2 $vf23, 0x30(%0)\n"
                     "lqc2 $vf9, 0x0(%1)\n"
                     "vmulax.xyzw $ACC, $vf1, $vf20x\n"
                     "vmadday.xyzw $ACC, $vf2, $vf20y\n"
                     "vmaddaz.xyzw $ACC, $vf3, $vf20z\n"
                     "vmaddw.xyzw $vf5, $vf4, $vf0w\n"
                     "vmulax.xyzw $ACC, $vf1, $vf21x\n"
                     "vmadday.xyzw $ACC, $vf2, $vf21y\n"
                     "vmaddaz.xyzw $ACC, $vf3, $vf21z\n"
                     "vmaddw.xyzw $vf6, $vf4, $vf0w\n"
                     "vmulax.xyzw $ACC, $vf1, $vf22x\n"
                     "vmadday.xyzw $ACC, $vf2, $vf22y\n"
                     "vmaddaz.xyzw $ACC, $vf3, $vf22z\n"
                     "vmaddw.xyzw $vf7, $vf4, $vf0w\n"
                     "vmulax.xyzw $ACC, $vf1, $vf23x\n"
                     "vmadday.xyzw $ACC, $vf2, $vf23y\n"
                     "vmaddaz.xyzw $ACC, $vf3, $vf23z\n"
                     "vmaddw.xyzw $vf8, $vf4, $vf0w\n"
                     "vsqi.xyzw $vf5, ($vi1++)\n"
                     "vsqi.xyzw $vf6, ($vi1++)\n"
                     "vsqi.xyzw $vf7, ($vi1++)\n"
                     "vsqi.xyzw $vf8, ($vi1++)\n"
                     "vsub.xyz $vf10, $vf5, $vf9\n"
                     "vsub.xyz $vf11, $vf6, $vf5\n"
                     "vsub.xyz $vf12, $vf6, $vf9\n"
                     "vsub.xyz $vf13, $vf7, $vf6\n"
                     "vsub.xyz $vf14, $vf7, $vf9\n"
                     "vsub.xyz $vf15, $vf8, $vf7\n"
                     "vsub.xyz $vf16, $vf8, $vf9\n"
                     "vsub.xyz $vf17, $vf5, $vf8\n"
                     "vsub.xyz $vf18, $vf5, $vf6\n"
                     "vsub.xyz $vf19, $vf7, $vf5\n"
                     "vmaxw.xyzw $vf31, $vf0, $vf0w\n"
                     "vopmula.xyz $ACC, $vf11, $vf10\n"
                     "vopmsub.xyz $vf10, $vf10, $vf11\n"
                     "vopmula.xyz $ACC, $vf13, $vf12\n"
                     "vopmsub.xyz $vf11, $vf12, $vf13\n"
                     "vopmula.xyz $ACC, $vf15, $vf14\n"
                     "vopmsub.xyz $vf12, $vf14, $vf15\n"
                     "vmul.xyz $vf15, $vf10, $vf10\n"
                     "vopmula.xyz $ACC, $vf17, $vf16\n"
                     "vopmsub.xyz $vf13, $vf16, $vf17\n"
                     "vmul.xyz $vf16, $vf11, $vf11\n"
                     "vmul.xyz $vf17, $vf12, $vf12\n"
                     "vopmula.xyz $ACC, $vf18, $vf19\n"
                     "vopmsub.xyz $vf14, $vf19, $vf18\n"
                     "vmul.xyz $vf18, $vf13, $vf13\n"
                     "vadday.x $ACC, $vf15, $vf15y\n"
                     "vmaddz.x $vf15, $vf31, $vf15z\n"
                     "vmul.xyz $vf19, $vf14, $vf14\n"
                     "vadday.x $ACC, $vf16, $vf16y\n"
                     "vmaddz.x $vf16, $vf31, $vf16z\n"
                     "vrsqrt $Q, $vf0w, $vf15x\n"
                     "vadday.x $ACC, $vf17, $vf17y\n"
                     "vmaddz.x $vf17, $vf31, $vf17z\n"
                     "vadday.x $ACC, $vf18, $vf18y\n"
                     "vmaddz.x $vf18, $vf31, $vf18z\n"
                     "vadday.x $ACC, $vf19, $vf19y\n"
                     "vmaddz.x $vf19, $vf31, $vf19z\n"
                     "vmulax.xyzw $ACC, $vf24, $vf5x\n"
                     "vmadday.xyzw $ACC, $vf25, $vf5y\n"
                     "vmaddaz.xyzw $ACC, $vf26, $vf5z\n"
                     "vmaddw.xyzw $vf5, $vf27, $vf0w\n"
                     "vwaitq\n"
                     "vmulq.xyz $vf10, $vf10, $Q\n"
                     "vnop\n"
                     "vnop\n"
                     "vrsqrt $Q, $vf0w, $vf16x\n"
                     "vmulax.xyzw $ACC, $vf24, $vf6x\n"
                     "vmadday.xyzw $ACC, $vf25, $vf6y\n"
                     "vmaddaz.xyzw $ACC, $vf26, $vf6z\n"
                     "vmaddw.xyzw $vf6, $vf27, $vf0w\n"
                     "vmulax.xyzw $ACC, $vf24, $vf7x\n"
                     "vmadday.xyzw $ACC, $vf25, $vf7y\n"
                     "vmaddaz.xyzw $ACC, $vf26, $vf7z\n"
                     "vmaddw.xyzw $vf7, $vf27, $vf0w\n"
                     "vsub.xyz $vf20, $vf6, $vf5\n"
                     "vsub.xyz $vf21, $vf7, $vf5\n"
                     "vwaitq\n"
                     "vmulq.xyz $vf11, $vf11, $Q\n"
                     "vnop\n"
                     "vnop\n"
                     "vrsqrt $Q, $vf0w, $vf17x\n"
                     "vmulax.xyzw $ACC, $vf24, $vf8x\n"
                     "vmadday.xyzw $ACC, $vf25, $vf8y\n"
                     "vmaddaz.xyzw $ACC, $vf26, $vf8z\n"
                     "vmaddw.xyzw $vf8, $vf27, $vf0w\n"
                     "vopmula.xyz $ACC, $vf20, $vf21\n"
                     "vopmsub.xyz $vf20, $vf21, $vf20" : : "r"(corners), "r"(position) : "memory");
}

/**
 * @brief Store the first two camera-space corners, finish the third normal and start the fourth; vf30 becomes -1.
 * @param points Five 16-byte aligned vectors.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_store_first_corners(void* points)
{
    asm __volatile__("sqc2 $vf5, 0x0(%0)\n"
                     "sqc2 $vf6, 0x10(%0)\n"
                     "vwaitq\n"
                     "vmulq.xyz $vf12, $vf12, $Q\n"
                     "vnop\n"
                     "vsubw.xyz $vf30, $vf0, $vf0w\n"
                     "vrsqrt $Q, $vf0w, $vf18x" : : "r"(points) : "memory");
}

/**
 * @brief Store the last two camera-space corners and the face normal.
 * @param points Five 16-byte aligned vectors.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_store_last_corners(void* points)
{
    asm __volatile__("sqc2 $vf7, 0x20(%0)\n"
                     "sqc2 $vf8, 0x30(%0)\n"
                     "sqc2 $vf20, 0x40(%0)" : : "r"(points) : "memory");
}

/**
 * @brief Finish the fourth edge normal and start the fifth.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_normalize_fourth()
{
    asm __volatile__("vwaitq\n"
                     "vmulq.xyz $vf13, $vf13, $Q\n"
                     "vnop\n"
                     "vnop\n"
                     "vrsqrt $Q, $vf0w, $vf19x");
}

/**
 * @brief Finish the fifth edge normal.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_normalize_fifth()
{
    asm __volatile__("vwaitq\n"
                     "vmulq.xyz $vf14, $vf14, $Q");
}

/**
 * @brief Negate the five normals (vf10-vf14) with vf30.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_flip_normals()
{
    asm __volatile__("vmulx.xyz $vf10, $vf10, $vf30x\n"
                     "vmulx.xyz $vf11, $vf11, $vf30x\n"
                     "vmulx.xyz $vf12, $vf12, $vf30x\n"
                     "vmulx.xyz $vf13, $vf13, $vf30x\n"
                     "vmulx.xyz $vf14, $vf14, $vf30x");
}

/**
 * @brief Store the five normals through vi1 and start dividing by the first corner's z.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_store_normals()
{
    asm __volatile__("vsqi.xyzw $vf10, ($vi1++)\n"
                     "vsqi.xyzw $vf11, ($vi1++)\n"
                     "vsqi.xyzw $vf12, ($vi1++)\n"
                     "vsqi.xyzw $vf13, ($vi1++)\n"
                     "vsqi.xyzw $vf14, ($vi1++)\n"
                     "vdiv $Q, $vf0w, $vf5z");
}

/**
 * @brief Divide the first corner by its z, start the second divide and store the corner.
 * @param point 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_project_first(void* point)
{
    asm __volatile__("vwaitq\n"
                     "vmulq.xy $vf5, $vf5, $Q\n"
                     "vnop\n"
                     "vnop\n"
                     "vdiv $Q, $vf0w, $vf6z\n"
                     "sqc2 $vf5, 0x0(%0)" : : "r"(point) : "memory");
}

/**
 * @brief Divide the second corner by its z, start the third divide and store the corner.
 * @param point 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_project_second(void* point)
{
    asm __volatile__("vwaitq\n"
                     "vmulq.xy $vf6, $vf6, $Q\n"
                     "vnop\n"
                     "vnop\n"
                     "vdiv $Q, $vf0w, $vf7z\n"
                     "sqc2 $vf6, 0x0(%0)" : : "r"(point) : "memory");
}

/**
 * @brief Divide the third corner by its z, start the last divide and store the corner.
 * @param point 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_project_third(void* point)
{
    // TODO: This divides the last corner by the third corner's z, like the game; check whether that's a bug.
    asm __volatile__("vwaitq\n"
                     "vmulq.xy $vf7, $vf7, $Q\n"
                     "vnop\n"
                     "vnop\n"
                     "vdiv $Q, $vf0w, $vf7z\n"
                     "sqc2 $vf7, 0x0(%0)" : : "r"(point) : "memory");
}

/**
 * @brief Divide the last corner and store it.
 * @param point 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_00431090 in Lib.
 */
static inline void vu0_occluder_project_fourth(void* point)
{
    asm __volatile__("vwaitq\n"
                     "vmulq.xy $vf8, $vf8, $Q\n"
                     "sqc2 $vf8, 0x0(%0)" : : "r"(point) : "memory");
}

#endif
