#ifndef SO3_EE_H
#define SO3_EE_H

/*
 * EE single-instruction helpers. The compiler has no intrinsic for either
 * instruction, so the game must have written them inline. See
 * docs/coding-standards.md, "Exception: two EE instruction helpers".
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
    asm("max.s %0, %1, %2" : "=f"(result) : "f"(left), "f"(right));
    return result;
}

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

#endif
