#ifndef SO3_EE_H
#define SO3_EE_H

// Instruction helpers have precedent in CodeWarrior PS2 decompilations:
// https://github.com/dreamingmoths/memory-of-alessa/blob/main/include/math.h
// https://github.com/AshfordFamily/recvx-decomp/blob/master/include/ps2/veronica/prog/macros.h

/**
 * @brief Return the EE scalar maximum of two floating-point operands.
 * @param left First operand.
 * @param right Second operand.
 * @return Maximum produced by the EE scalar instruction.
 */
static inline float ee_max(float left, float right)
{
    float result;
    asm("max.s %0, %1, %2" : "=f"(result) : "f"(left), "f"(right));
    return result;
}

/**
 * @brief Request cache prefetch for the supplied address.
 * @param address Address to prefetch.
 */
static inline void ee_prefetch(const void* address)
{
    asm __volatile__("pref 0, 0(%0)" : : "r"(address));
}

#endif
