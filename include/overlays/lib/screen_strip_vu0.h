#ifndef SO3_OVERLAYS_LIB_SCREEN_STRIP_VU0_H
#define SO3_OVERLAYS_LIB_SCREEN_STRIP_VU0_H

/**
 * @brief Transform a point into vf5 by the matrix LibClass1748D0::build_packet left in vf1-vf4.
 * @param position 16-byte aligned point.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); func_0044D600 in Lib.
 */
static inline void vu0_transform_point(const void* position)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)\n"
                     "vmulax.xyzw $ACC, $vf1, $vf5x\n"
                     "vmadday.xyzw $ACC, $vf2, $vf5y\n"
                     "vmaddaz.xyzw $ACC, $vf3, $vf5z\n"
                     "vmaddw.xyzw $vf5, $vf4, $vf0w" : : "r"(position) : "memory");
}

/**
 * @brief Start dividing one by vf5.w into Q.
 * @see vu0_transform_point.
 */
static inline void vu0_start_divide_by_w(void)
{
    asm __volatile__("vdiv $Q, $vf0w, $vf5w");
}

/**
 * @brief Finish vu0_start_divide_by_w's divide, store the screen point, and start the microprogram at 0x958 on an
 *        attribute vector in vf6; it leaves the GS XYZ words in vf6.
 * @param attribute 16-byte aligned attribute vector.
 * @param screen 16-byte aligned destination of the divided point.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6); func_0044D600 in Lib.
 */
static inline void vu0_store_projected_start_958(const void* attribute, void* screen)
{
    asm __volatile__("lqc2 $vf6, 0x0(%0)\n"
                     "vwaitq\n"
                     "vmulq.xyzw $vf5, $vf5, $Q\n"
                     "sqc2 $vf5, 0x0(%1)\n"
                     "nop\n"
                     "vcallms 0x958" : : "r"(attribute), "r"(screen) : "memory");
}

/**
 * @brief Scale vf5 by the Q that vu0_start_divide_by_w started, without waiting for it.
 * @see vu0_transform_point; func_0044D1D0 in Lib.
 */
static inline void vu0_scale_by_q(void)
{
    asm __volatile__("vmulq.xyzw $vf5, $vf5, $Q");
}

/**
 * @brief Store the scaled screen point and start the microprogram at 0x958 on an attribute vector in vf6; it leaves
 *        the GS XYZ words in vf6.
 * @param attribute 16-byte aligned attribute vector.
 * @param screen 16-byte aligned destination of the scaled point.
 * @see vu0_store_projected_start_958; func_0044D1D0 in Lib.
 */
static inline void vu0_store_point_start_958(const void* attribute, void* screen)
{
    asm __volatile__("lqc2 $vf6, 0x0(%0)\n"
                     "sqc2 $vf5, 0x0(%1)\n"
                     "nop\n"
                     "vcallms 0x958" : : "r"(attribute), "r"(screen) : "memory");
}

/**
 * @brief Wait for the running microprogram and store vf6.
 *
 * The game always reads into t1 here, so I've hard-coded it.
 * @param out 16-byte aligned destination.
 * @see vu0_store_projected_start_958.
 */
static inline void vu0_wait_store_vf6(void* out)
{
    asm __volatile__("cfc2.i $t1, $vi0\n"
                     "sqc2 $vf6, 0x0(%0)" : : "r"(out) : "$t1", "memory");
}

#endif
