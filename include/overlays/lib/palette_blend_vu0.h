#ifndef SO3_OVERLAYS_LIB_PALETTE_BLEND_VU0_H
#define SO3_OVERLAYS_LIB_PALETTE_BLEND_VU0_H

/**
 * @brief Load the blend weights into vf3: x weights the end color and y the start color.
 * @param weights 16-byte aligned weights.
 * @see Sony's EE/VU manual (https://docs.alexrp.com/mips/ee_vu.pdf); LibPaletteBlendChannel::update in Lib.
 */
static inline void vu0_load_vf3(const void* weights)
{
    asm __volatile__("lqc2 $vf3, 0x0(%0)" : : "r"(weights) : "memory");
}

/**
 * @brief Blend two float colors by the weights in vf3 and pack the result into a 32-bit RGBA word.
 *
 * The game always packs through t0 here, so I've hard-coded it. PPACH then PPACB keep the low byte of each
 * channel.
 * @param start 16-byte aligned start color, 0-255 per channel.
 * @param end 16-byte aligned end color.
 * @return The packed color.
 * @see Sony's EE/VU manual and the EE Core Instruction Set Manual (PPACH, PPACB); LibPaletteBlendChannel::update
 *      in Lib.
 */
static inline u32 vu0_blend_color(const void* start, const void* end)
{
    u32 color;
    asm __volatile__("lqc2 $vf1, 0x0(%1)\n"
                     "lqc2 $vf2, 0x0(%2)\n"
                     "vmulay.xyzw $ACC, $vf1, $vf3y\n"
                     "vmaddx.xyzw $vf1, $vf2, $vf3x\n"
                     "vftoi0.xyzw $vf1, $vf1\n"
                     "qmfc2.ni $t0, $vf1\n"
                     "ppach $t0, $zero, $t0\n"
                     "ppacb %0, $zero, $t0" : "=r"(color) : "r"(start), "r"(end) : "$t0", "memory");
    return color;
}

#endif
