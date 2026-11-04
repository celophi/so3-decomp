#ifndef SO3_EE_H
#define SO3_EE_H

#include "types.h"

/*
 * EE instruction helpers the game wrote inline.
 */

/**
 * @brief Return the EE scalar maximum of two floating-point operands.
 * @param left First operand.
 * @param right Second operand.
 * @return Maximum produced by the EE scalar instruction.
 * @see Silent Hill 2/3 (CodeWarrior) has the same one-instruction float_max
 *      (https://github.com/dreamingmoths/memory-of-alessa, include/math.h).
 */
static inline float ee_max(float left, float right)
{
    float result;
    asm __volatile__("max.s %0, %1, %2" : "=f"(result) : "f"(left), "f"(right));
    return result;
}

/**
 * @brief Return the EE scalar minimum of two floating-point operands.
 * @param left First operand.
 * @param right Second operand.
 * @return Minimum produced by the EE scalar instruction.
 * @see Silent Hill 2/3 (CodeWarrior) has the same one-instruction float_min
 *      (https://github.com/dreamingmoths/memory-of-alessa, include/math.h).
 */
static inline float ee_min(float left, float right)
{
    float result;
    asm __volatile__("min.s %0, %1, %2" : "=f"(result) : "f"(left), "f"(right));
    return result;
}

#ifdef __cplusplus
/**
 * @brief Return the EE scalar maximum of a value and a float read in place.
 *
 * The same max.s as ee_max, but the second operand is read through the
 * reference rather than copied into a parameter.
 * @param left First operand.
 * @param right Second operand, usually a field.
 * @return Maximum produced by the EE scalar instruction.
 * @see Silent Hill 2/3 (CodeWarrior) has the same one-instruction float_max
 *      (https://github.com/dreamingmoths/memory-of-alessa, include/math.h).
 */
static inline float ee_max_in_place(float left, const float& right)
{
    float result;
    asm __volatile__("max.s %0, %1, %2" : "=f"(result) : "f"(left), "f"(right));
    return result;
}
#endif

/**
 * @brief Request cache prefetch for the supplied address.
 *
 * No memory clobber: pref is only a cache hint and doesn't order loads or
 * stores.
 * @param address Address to prefetch.
 * @see Code Veronica X (CodeWarrior) has the same PREFETCH macro
 *      (https://github.com/AshfordFamily/recvx-decomp,
 *      include/ps2/veronica/prog/macros.h), as does ps2dev gsKit's
 *      GSKIT_PREFETCH (ee/gs/include/gsInit.h).
 */
static inline void ee_prefetch(const void* address)
{
    asm __volatile__("pref 0, 0(%0)" : : "r"(address));
}

/**
 * @brief Wait for every earlier load and store to finish (one sync).
 *
 * The game issues this between writing a packet's end tag and handing the
 * packet to DMA, so the tag is in memory before the transfer reads it.
 * @see ps2sdk has the same one-instruction EE_SYNC
 *      (https://github.com/ps2dev/ps2sdk, ee/kernel/include/kernel.h).
 */
static inline void ee_sync(void)
{
    asm __volatile__("sync");
}

/**
 * @brief Transpose a 16-byte-aligned 4x4 matrix of words with the EE's 128-bit MMI instructions.
 *
 * The registers are fixed ($t0-$t7) because every copy in the game uses the
 * same ones: about 115 functions across main, lib, 1067-00, 1070-00, 3253-00
 * and 3454-00 have this exact sequence.
 * @param out Aligned destination matrix.
 * @param in Aligned source matrix.
 * @see EE Core Instruction Set Manual (PEXTLW, PEXTUW, PCPYLD, PCPYUD, LQ, SQ).
 */
static inline void ee_transpose_matrix(void* out, const void* in)
{
    asm __volatile__("lq       $8, 0x0(%1)\n"
                     "lq       $9, 0x10(%1)\n"
                     "lq       $10, 0x20(%1)\n"
                     "lq       $11, 0x30(%1)\n"
                     "pextlw   $12, $9, $8\n"
                     "pextuw   $13, $9, $8\n"
                     "pextlw   $14, $11, $10\n"
                     "pextuw   $15, $11, $10\n"
                     "pcpyld   $8, $14, $12\n"
                     "pcpyud   $9, $12, $14\n"
                     "pcpyld   $10, $15, $13\n"
                     "pcpyud   $11, $13, $15\n"
                     "sq       $8, 0x0(%0)\n"
                     "sq       $9, 0x10(%0)\n"
                     "sq       $10, 0x20(%0)\n"
                     "sq       $11, 0x30(%0)\n"
                     :
                     : "r"(out), "r"(in)
                     : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

/*
 * My guess is the game wanted branchless selects that weren't at the mercy of
 * bad branch prediction, and the compiler only sometimes turns a ?: into
 * movn/movz on its own. Being volatile also stops the compiler's later cleanup
 * in the same block, which is why the target keeps an `andi 0xFF` after each
 * later compare. TODO: come back to this if a better explanation turns up.
 */

/**
 * @brief Return replacement if condition is non-zero, otherwise value (one movn).
 * @param value Value kept when condition is zero.
 * @param replacement Value used when condition is non-zero.
 * @param condition Selector.
 * @return The selected value.
 * @see https://decomp.me/scratch/e8lkP
 */
static inline s32 ee_movn(s32 value, s32 replacement, s32 condition)
{
    asm __volatile__("movn %0, %1, %2" : "+r"(value) : "r"(replacement), "r"(condition));
    return value;
}

/**
 * @brief Return replacement if condition is zero, otherwise value (one movz).
 * @param value Value kept when condition is non-zero.
 * @param replacement Value used when condition is zero.
 * @param condition Selector.
 * @return The selected value.
 * @see https://decomp.me/scratch/e8lkP
 */
static inline s32 ee_movz(s32 value, s32 replacement, s32 condition)
{
    asm __volatile__("movz %0, %1, %2" : "+r"(value) : "r"(replacement), "r"(condition));
    return value;
}

#endif
