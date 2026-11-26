#ifndef SO3_OVERLAYS_LIB_GRID_BOUNDS_VU0_H
#define SO3_OVERLAYS_LIB_GRID_BOUNDS_VU0_H

/**
 * @brief Start a bounding box in vf26 (minimum) and vf27 (maximum) for the grid passes to grow with
 *        vu0_extend_bounds_vf1.
 * @param min 16-byte aligned starting minimum.
 * @param max 16-byte aligned starting maximum; its w is the 0.5 vu0_begin_bounds_sphere halves with.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibObject1751A0::update in Lib.
 */
static inline void vu0_load_bounds(const void* min, const void* max)
{
    asm __volatile__("lqc2 $vf26, 0x0(%0)\n"
                     "lqc2 $vf27, 0x0(%1)" : : "r"(min), "r"(max) : "memory");
}

/**
 * @brief Put the centre of the vf26/vf27 box in vf1 and start the square root of its half diagonal, padded by
 *        padding.x on each axis, in Q.
 * @param padding 16-byte aligned vector whose x pads the box.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibObject1751A0::update in Lib.
 */
static inline void vu0_begin_bounds_sphere(const void* padding)
{
    asm __volatile__("lqc2 $vf28, 0x0(%0)\n"
                     "vadd.xyz $vf1, $vf26, $vf27\n"
                     "vmulw.xyz $vf1, $vf1, $vf27w\n"
                     "vsub.xyz $vf2, $vf27, $vf1\n"
                     "vaddx.xyz $vf2, $vf2, $vf28x\n"
                     "vmul.xyz $vf2, $vf2, $vf2\n"
                     "vaddw.xyz $vf31, $vf0, $vf0w\n"
                     "vadday.x $ACC, $vf2, $vf2y\n"
                     "vmaddz.x $vf2, $vf31, $vf2z\n"
                     "vsqrt $Q, $vf2x" : : "r"(padding) : "memory");
}

/**
 * @brief Store the vf26/vf27 box as two consecutive vectors.
 * @param box 16-byte aligned destination for the minimum, followed by the maximum.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibObject1751A0::update in Lib.
 */
static inline void vu0_store_bounds(void* box)
{
    asm __volatile__("sqc2 $vf26, 0x0(%0)\n"
                     "sqc2 $vf27, 0x10(%0)" : : "r"(box) : "memory");
}

/**
 * @brief Store vu0_begin_bounds_sphere's centre with the square root as w.
 * @param sphere 16-byte aligned destination.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibObject1751A0::update in Lib.
 */
static inline void vu0_store_bounds_sphere(void* sphere)
{
    asm __volatile__("vwaitq\n"
                     "vmulq.w $vf1, $vf0, $Q\n"
                     "sqc2 $vf1, 0x0(%0)" : : "r"(sphere) : "memory");
}

#endif
