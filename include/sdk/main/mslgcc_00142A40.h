#ifndef SO3_SDK_MAIN_MSLGCC_00142A40_H
#define SO3_SDK_MAIN_MSLGCC_00142A40_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the address of D_0014F620.
 * @return Pointer to D_0014F620.
 */
u8* func_001430C0(void);

/**
 * @brief Return the address of D_0014F6A0.
 * @return Pointer to D_0014F6A0.
 */
u8* func_001431D0(void);

/**
 * @brief Return the address of D_0014F760.
 * @return Pointer to D_0014F760.
 */
u8* func_00143B20(void);

/**
 * @brief Test a three-word pointer-to-member representation.
 * @param member The representation to inspect.
 * @return One if any word is nonzero; otherwise zero.
 */
s32 __ptmf_test(const u32* member);

#ifdef __cplusplus
}
#endif

#endif
