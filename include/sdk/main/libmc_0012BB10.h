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

/**
 * @brief Start reading a card's type, free space and format state.
 * @param port Card port.
 * @param slot Card slot.
 * @param type Receives the card type, or null.
 * @param free Receives the free space, or null.
 * @param format Receives whether the card is formatted, or null.
 * @return Zero when the command started.
 */
s32 sceMcGetInfo(s32 port, s32 slot, s32* type, s32* free, s32* format);

s32 mcHearAlarm(s32 callback_arg0, s32 callback_arg1, s32 sema_id);

#ifdef __cplusplus
}
#endif

#endif
