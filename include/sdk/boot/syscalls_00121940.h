#ifndef SO3_SDK_BOOT_SYSCALLS_00121940_H
#define SO3_SDK_BOOT_SYSCALLS_00121940_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief EE kernel syscall 100 (FlushCache in the SDK reference patterns).
 * @param mode Cache operation selector.
 */
void func_00121FE0(s32 mode);

#ifdef __cplusplus
}
#endif

#endif
