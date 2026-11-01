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

/**
 * @brief Prepare a loaded overlay: clear the BSS after its image and run its static initializers.
 * @param overlay Overlay image, starting with its MWo3 header.
 * @param size Size of the loaded image; the BSS starts there.
 */
void mwOverlayInit(void* overlay, u32 size);

/** @brief Register main's exception tables with the C++ runtime. */
void func_00142AE0(void);

/** @brief Destroy the global objects registered on the destructor chain. */
void func_00142AC0(void);

/**
 * @brief Install a new handler, which operator new calls when it can't allocate.
 * @param handler Handler to install.
 * @return The previous handler.
 */
void (*func_001430D0(void (*handler)(void)))(void);

#ifdef __cplusplus
}
#endif

#endif
