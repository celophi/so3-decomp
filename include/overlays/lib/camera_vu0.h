#ifndef SO3_OVERLAYS_LIB_CAMERA_VU0_H
#define SO3_OVERLAYS_LIB_CAMERA_VU0_H

/**
 * @brief Upload clip points and normals to VU0 data qwords 8 through 27.
 *
 * Stores six points, six normals, four points, then four normals through
 * vf20-vf25 and vi1.
 * @param points Ten 16-byte aligned point vectors.
 * @param normals Ten 16-byte aligned normal vectors.
 */
static inline void vu0_upload_clip_geometry(const void* points, const void* normals)
{
    asm __volatile__(
        "lqc2       $vf20, 0x0(%0)\n"
        "lqc2       $vf21, 0x10(%0)\n"
        "lqc2       $vf22, 0x20(%0)\n"
        "lqc2       $vf23, 0x30(%0)\n"
        "lqc2       $vf24, 0x40(%0)\n"
        "lqc2       $vf25, 0x50(%0)\n"
        "viaddi     $vi1, $vi0, 0x8\n"
        "vsqi.xyzw  $vf20, ($vi1++)\n"
        "vsqi.xyzw  $vf21, ($vi1++)\n"
        "vsqi.xyzw  $vf22, ($vi1++)\n"
        "vsqi.xyzw  $vf23, ($vi1++)\n"
        "vsqi.xyzw  $vf24, ($vi1++)\n"
        "vsqi.xyzw  $vf25, ($vi1++)\n"
        "lqc2       $vf20, 0x0(%1)\n"
        "lqc2       $vf21, 0x10(%1)\n"
        "lqc2       $vf22, 0x20(%1)\n"
        "lqc2       $vf23, 0x30(%1)\n"
        "lqc2       $vf24, 0x40(%1)\n"
        "lqc2       $vf25, 0x50(%1)\n"
        "vsqi.xyzw  $vf20, ($vi1++)\n"
        "vsqi.xyzw  $vf21, ($vi1++)\n"
        "vsqi.xyzw  $vf22, ($vi1++)\n"
        "vsqi.xyzw  $vf23, ($vi1++)\n"
        "vsqi.xyzw  $vf24, ($vi1++)\n"
        "vsqi.xyzw  $vf25, ($vi1++)\n"
        "lqc2       $vf20, 0x60(%0)\n"
        "lqc2       $vf21, 0x70(%0)\n"
        "lqc2       $vf22, 0x80(%0)\n"
        "lqc2       $vf23, 0x90(%0)\n"
        "vsqi.xyzw  $vf20, ($vi1++)\n"
        "vsqi.xyzw  $vf21, ($vi1++)\n"
        "vsqi.xyzw  $vf22, ($vi1++)\n"
        "vsqi.xyzw  $vf23, ($vi1++)\n"
        "lqc2       $vf20, 0x60(%1)\n"
        "lqc2       $vf21, 0x70(%1)\n"
        "lqc2       $vf22, 0x80(%1)\n"
        "lqc2       $vf23, 0x90(%1)\n"
        "vsqi.xyzw  $vf20, ($vi1++)\n"
        "vsqi.xyzw  $vf21, ($vi1++)\n"
        "vsqi.xyzw  $vf22, ($vi1++)\n"
        "vsqi.xyzw  $vf23, ($vi1++)\n"
        :
        : "r"(points), "r"(normals)
        : "memory");
}

/**
 * @brief Wait for the running microprogram, then transform ten clip points by the matrix in vf1-vf4 into vf5-vf14.
 *
 * Also sets vf31 to one and vf30 to minus one, which the normal builders use.
 * @param points Ten 16-byte aligned points.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); Lib's func_004E1670 is the only site.
 */
static inline void vu0_transform_clip_points(const void* address)
{
    asm __volatile__(
        "cfc2.i      $zero, $vi0\n"
        "lqc2        $vf20, 0x0(%0)\n"
        "lqc2        $vf21, 0x10(%0)\n"
        "lqc2        $vf22, 0x20(%0)\n"
        "lqc2        $vf23, 0x30(%0)\n"
        "lqc2        $vf24, 0x40(%0)\n"
        "lqc2        $vf25, 0x50(%0)\n"
        "lqc2        $vf26, 0x60(%0)\n"
        "lqc2        $vf27, 0x70(%0)\n"
        "lqc2        $vf28, 0x80(%0)\n"
        "lqc2        $vf29, 0x90(%0)\n"
        "vmaxw.xyzw  $vf31, $vf0, $vf0w\n"
        "vsubw.xyzw  $vf30, $vf0, $vf0w\n"
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
        "vmulax.xyzw $ACC, $vf1, $vf24x\n"
        "vmadday.xyzw $ACC, $vf2, $vf24y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf24z\n"
        "vmaddw.xyzw $vf9, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf1, $vf25x\n"
        "vmadday.xyzw $ACC, $vf2, $vf25y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf25z\n"
        "vmaddw.xyzw $vf10, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf1, $vf26x\n"
        "vmadday.xyzw $ACC, $vf2, $vf26y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf26z\n"
        "vmaddw.xyzw $vf11, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf1, $vf27x\n"
        "vmadday.xyzw $ACC, $vf2, $vf27y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf27z\n"
        "vmaddw.xyzw $vf12, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf1, $vf28x\n"
        "vmadday.xyzw $ACC, $vf2, $vf28y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf28z\n"
        "vmaddw.xyzw $vf13, $vf4, $vf0w\n"
        "vmulax.xyzw $ACC, $vf1, $vf29x\n"
        "vmadday.xyzw $ACC, $vf2, $vf29y\n"
        "vmaddaz.xyzw $ACC, $vf3, $vf29z\n"
        "vmaddw.xyzw $vf14, $vf4, $vf0w\n"
        :
        : "r"(address)
        : "memory");
}

/**
 * @brief Store the ten transformed clip points from vf5-vf14.
 * @param points Ten 16-byte aligned destination vectors.
 * @see vu0_transform_clip_points.
 */
static inline void vu0_store_clip_points(void* address)
{
    asm __volatile__(
        "sqc2        $vf5, 0x0(%0)\n"
        "sqc2        $vf6, 0x10(%0)\n"
        "sqc2        $vf7, 0x20(%0)\n"
        "sqc2        $vf8, 0x30(%0)\n"
        "sqc2        $vf9, 0x40(%0)\n"
        "sqc2        $vf10, 0x50(%0)\n"
        "sqc2        $vf11, 0x60(%0)\n"
        "sqc2        $vf12, 0x70(%0)\n"
        "sqc2        $vf13, 0x80(%0)\n"
        "sqc2        $vf14, 0x90(%0)\n"
        :
        : "r"(address)
        : "memory");
}

/**
 * @brief Build the unit normals of the planes through the eye (vf4) and the near rectangle (vf5-vf8), and of the
 *        near plane and its opposite, and store them.
 * @param normals Ten 16-byte aligned destination vectors; the first six are written.
 * @see vu0_transform_clip_points.
 */
static inline void vu0_build_side_clip_normals(void* address)
{
    asm __volatile__(
        "vsub.xyz    $vf15, $vf6, $vf5\n"
        "vsub.xyz    $vf16, $vf5, $vf4\n"
        "vsub.xyz    $vf17, $vf7, $vf6\n"
        "vsub.xyz    $vf18, $vf6, $vf4\n"
        "vsub.xyz    $vf19, $vf8, $vf7\n"
        "vsub.xyz    $vf20, $vf7, $vf4\n"
        "vsub.xyz    $vf23, $vf7, $vf5\n"
        "vsub.xyz    $vf21, $vf5, $vf8\n"
        "vsub.xyz    $vf22, $vf8, $vf4\n"
        "vopmula.xyz $ACC, $vf16, $vf15\n"
        "vopmsub.xyz $vf24, $vf15, $vf16\n"
        "vopmula.xyz $ACC, $vf15, $vf23\n"
        "vopmsub.xyz $vf28, $vf23, $vf15\n"
        "vopmula.xyz $ACC, $vf18, $vf17\n"
        "vmul.xyz    $vf15, $vf24, $vf24\n"
        "vopmsub.xyz $vf25, $vf17, $vf18\n"
        "vopmula.xyz $ACC, $vf20, $vf19\n"
        "vopmsub.xyz $vf26, $vf19, $vf20\n"
        "vadday.x    $ACC, $vf15, $vf15y\n"
        "vmaddz.x    $vf15, $vf31, $vf15z\n"
        "vopmula.xyz $ACC, $vf22, $vf21\n"
        "vmul.xyz    $vf16, $vf25, $vf25\n"
        "vopmsub.xyz $vf27, $vf21, $vf22\n"
        "vrsqrt      $Q, $vf0w, $vf15x\n"
        "vmul.xyz    $vf17, $vf26, $vf26\n"
        "vmul.xyz    $vf18, $vf27, $vf27\n"
        "vmul.xyz    $vf19, $vf28, $vf28\n"
        "vadday.x    $ACC, $vf16, $vf16y\n"
        "vmaddz.x    $vf16, $vf31, $vf16z\n"
        "vwaitq      \n"
        "vmulq.xyz   $vf24, $vf24, $Q\n"
        "vnop        \n"
        "vnop        \n"
        "vrsqrt      $Q, $vf0w, $vf16x\n"
        "sqc2        $vf24, 0x0(%0)\n"
        "vadday.x    $ACC, $vf17, $vf17y\n"
        "vmaddz.x    $vf17, $vf31, $vf17z\n"
        "vwaitq      \n"
        "vmulq.xyz   $vf25, $vf25, $Q\n"
        "vnop        \n"
        "vnop        \n"
        "vrsqrt      $Q, $vf0w, $vf17x\n"
        "sqc2        $vf25, 0x10(%0)\n"
        "vadday.x    $ACC, $vf18, $vf18y\n"
        "vmaddz.x    $vf18, $vf31, $vf18z\n"
        "vwaitq      \n"
        "vmulq.xyz   $vf26, $vf26, $Q\n"
        "vnop        \n"
        "vnop        \n"
        "vrsqrt      $Q, $vf0w, $vf18x\n"
        "sqc2        $vf26, 0x20(%0)\n"
        "vadday.x    $ACC, $vf19, $vf19y\n"
        "vmaddz.x    $vf19, $vf31, $vf19z\n"
        "vwaitq      \n"
        "vmulq.xyz   $vf27, $vf27, $Q\n"
        "vnop        \n"
        "vnop        \n"
        "vrsqrt      $Q, $vf0w, $vf19x\n"
        "sqc2        $vf27, 0x30(%0)\n"
        "vwaitq      \n"
        "vmulq.xyz   $vf28, $vf28, $Q\n"
        "vmulx.xyz   $vf29, $vf28, $vf30x\n"
        "sqc2        $vf28, 0x40(%0)\n"
        "sqc2        $vf29, 0x50(%0)\n"
        :
        : "r"(address)
        : "memory");
}

/**
 * @brief Build the unit normals of the planes through the eye (vf4) and the screen-edge points (vf11-vf14), and store
 *        them after the first six.
 * @param normals Ten 16-byte aligned destination vectors; the last four are written.
 * @see vu0_transform_clip_points.
 */
static inline void vu0_build_end_clip_normals(void* address)
{
    asm __volatile__(
        "vsub.xyz    $vf15, $vf12, $vf11\n"
        "vsub.xyz    $vf16, $vf11, $vf4\n"
        "vsub.xyz    $vf17, $vf13, $vf12\n"
        "vsub.xyz    $vf18, $vf12, $vf4\n"
        "vsub.xyz    $vf19, $vf14, $vf13\n"
        "vopmula.xyz $ACC, $vf16, $vf15\n"
        "vopmsub.xyz $vf24, $vf15, $vf16\n"
        "vsub.xyz    $vf20, $vf13, $vf4\n"
        "vopmula.xyz $ACC, $vf18, $vf17\n"
        "vopmsub.xyz $vf25, $vf17, $vf18\n"
        "vmul.xyz    $vf15, $vf24, $vf24\n"
        "vsub.xyz    $vf21, $vf11, $vf14\n"
        "vsub.xyz    $vf22, $vf14, $vf4\n"
        "vmul.xyz    $vf16, $vf25, $vf25\n"
        "vadday.x    $ACC, $vf15, $vf15y\n"
        "vmaddz.x    $vf15, $vf31, $vf15z\n"
        "vopmula.xyz $ACC, $vf20, $vf19\n"
        "vopmsub.xyz $vf26, $vf19, $vf20\n"
        "vopmula.xyz $ACC, $vf22, $vf21\n"
        "vrsqrt      $Q, $vf0w, $vf15x\n"
        "vopmsub.xyz $vf27, $vf21, $vf22\n"
        "vmul.xyz    $vf17, $vf26, $vf26\n"
        "vmul.xyz    $vf18, $vf27, $vf27\n"
        "vadday.x    $ACC, $vf16, $vf16y\n"
        "vmaddz.x    $vf16, $vf31, $vf16z\n"
        "vwaitq      \n"
        "vmulq.xyz   $vf24, $vf24, $Q\n"
        "vnop        \n"
        "vnop        \n"
        "vrsqrt      $Q, $vf0w, $vf16x\n"
        "vadday.x    $ACC, $vf17, $vf17y\n"
        "vmaddz.x    $vf17, $vf31, $vf17z\n"
        "vwaitq      \n"
        "vmulq.xyz   $vf25, $vf25, $Q\n"
        "sqc2        $vf24, 0x60(%0)\n"
        "vnop        \n"
        "vrsqrt      $Q, $vf0w, $vf17x\n"
        "sqc2        $vf25, 0x70(%0)\n"
        "vadday.x    $ACC, $vf18, $vf18y\n"
        "vmaddz.x    $vf18, $vf31, $vf18z\n"
        "vwaitq      \n"
        "vmulq.xyz   $vf26, $vf26, $Q\n"
        "vnop        \n"
        "vnop        \n"
        "vrsqrt      $Q, $vf0w, $vf18x\n"
        "sqc2        $vf26, 0x80(%0)\n"
        "vwaitq      \n"
        "vmulq.xyz   $vf27, $vf27, $Q\n"
        "sqc2        $vf27, 0x90(%0)\n"
        :
        : "r"(address)
        : "memory");
}

#endif
