#ifndef SO3_SDK_MAIN_LIBMC_0012BB10_H
#define SO3_SDK_MAIN_LIBMC_0012BB10_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start the memory card library.
 * @return Zero on success.
 */
s32 sceMcInit(void);

/**
 * @brief Wait for, or poll, the memory card command in progress.
 * @param mode Zero to wait until it finishes, one to check and return at once.
 * @param command Receives the finished command's number.
 * @param result Receives its result.
 * @return Nonzero when a command finished; zero while one is still running.
 */
s32 sceMcSync(s32 mode, s32* command, s32* result);

s32 mcHearAlarm(s32 callback_arg0, s32 callback_arg1, s32 sema_id);

#ifdef __cplusplus
}
#endif

#endif
