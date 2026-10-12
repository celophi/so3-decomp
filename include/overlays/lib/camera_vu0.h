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

#endif
