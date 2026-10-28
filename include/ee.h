#ifndef SO3_EE_H
#define SO3_EE_H

#include "types.h"

/*
 * EE single-instruction helpers the game wrote inline.
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
