#ifndef SO3_SDK_MAIN_LIBCDVD_00130000_H
#define SO3_SDK_MAIN_LIBCDVD_00130000_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Initialize the CD/DVD library. @param mode 0 for a normal initialization. @return Nonzero on success. */
s32 sceCdInit(s32 mode);

/** @brief Set the disc media type. @param media 1 for CD, 2 for DVD. @return Nonzero on success. */
s32 sceCdMmode(s32 media);

/**
 * @brief Create the thread that runs the disc callback.
 * @param priority Thread priority.
 * @param stack Stack for the thread.
 * @param stack_size Size of stack in bytes.
 * @return The previous callback thread's stack.
 */
void* sceCdInitEeCB(s32 priority, void* stack, s32 stack_size);

/**
 * @brief Set the function called when a disc command finishes.
 * @param callback Callback, given the command that finished.
 * @return The previous callback.
 */
void* sceCdCallback(void (*callback)(s32 reason));

#ifdef __cplusplus
}
#endif

#endif
