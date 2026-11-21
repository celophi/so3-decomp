#ifndef SO3_OVERLAYS_LIB_CULL_VU0_H
#define SO3_OVERLAYS_LIB_CULL_VU0_H

#include "types.h"

/**
 * @brief Load a position into vf5.
 * @param position 16-byte aligned position, w set to one.
 * @see vu0_start_microprogram_d0_vf8.
 */
static inline void vu0_load_position_vf5(const void* position)
{
    asm __volatile__("lqc2 $vf5, 0x0(%0)" : : "r"(position) : "memory");
}

/**
 * @brief Load a vector into vf8 and start the microprogram at 0xD0.
 *
 * Lib's renderer runs it on an object's position (vf5) after loading the
 * object's matrix with vu0_start_microprogram_1f0_vf5_vf8, then reads vf6.x as
 * how far behind the camera it is, so I think it's a view depth.
 * @param vector 16-byte aligned vector; Lib passes (0, 0, 1, 1).
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 * @see func_004D3780 in Lib.
 */
static inline void vu0_start_microprogram_d0_vf8(const void* vector)
{
    asm __volatile__("lqc2 $vf8, 0x0(%0)\n"
                     "nop\n"
                     "nop\n"
                     "vcallms 0xD0" : : "r"(vector) : "memory");
}

/**
 * @brief Start the microprogram at 0xC88.
 *
 * Lib's renderer starts it after the sphere test at 0xB60 when vi3 is zero, and
 * reads vi2 afterwards.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 * @see func_004D3780 in Lib.
 */
static inline void vu0_start_microprogram_c88(void)
{
    asm __volatile__("vcallms 0xC88" : : : "memory");
}

/**
 * @brief Read vi3 without waiting for the running microprogram.
 * @return The register's value.
 * @see vu0_start_microprogram_b60_vf5.
 */
static inline s32 vu0_read_vi3(void)
{
    s32 value;
    asm __volatile__("cfc2.ni %0, $vi3" : "=r"(value) : : "memory");
    return value;
}

/**
 * @brief Store vf8.
 * @param vector 16-byte aligned destination.
 * @see vu0_start_microprogram_b60_vf5.
 */
static inline void vu0_store_vf8(void* vector)
{
    asm __volatile__("sqc2 $vf8, 0x0(%0)" : : "r"(vector) : "memory");
}

/**
 * @brief Store vf9.
 * @param vector 16-byte aligned destination.
 * @see vu0_start_microprogram_b60_vf5.
 */
static inline void vu0_store_vf9(void* vector)
{
    asm __volatile__("sqc2 $vf9, 0x0(%0)" : : "r"(vector) : "memory");
}

/**
 * @brief Point vi1 at the first occluder in VU0 data memory (qword 8).
 * @see func_00430E00 uploads the occluders; func_004D3290 tests against them in Lib.
 */
static inline void vu0_first_occluder(void)
{
    asm __volatile__("viaddi $vi1, $vi0, 0x8");
}

/**
 * @brief Step vi1 past one occluder (nine qwords) without testing it.
 * @see vu0_first_occluder.
 */
static inline void vu0_skip_occluder(void)
{
    asm __volatile__("viaddi $vi1, $vi1, 0x9");
}

/**
 * @brief Start the microprogram at 0xD58.
 *
 * It tests the sphere in vf1 against the occluder vi1 points at and steps vi1
 * on. Lib hides the object when vi2 comes back zero.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf, 5.4.6).
 * @see func_004D3290 in Lib.
 */
static inline void vu0_start_microprogram_d58(void)
{
    asm __volatile__("vcallms 0xD58" : : : "memory");
}

#endif
