#ifndef SO3_SDK_MAIN_LIBCDVD_00130000_H
#define SO3_SDK_MAIN_LIBCDVD_00130000_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the CD/DVD library.
 * @param mode 0 for a normal initialization.
 * @return Nonzero on success.
 */
s32 sceCdInit(s32 mode);

/**
 * @brief Set the disc media type.
 * @param media 1 for CD, 2 for DVD.
 * @return Nonzero on success.
 */
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

/** How sceCdRead reads: retry count, spindle control and data pattern. */
typedef struct sceCdRMode
{
    u8 trycount;
    u8 spindlctrl;
    u8 datapattern;
    u8 pad;
} sceCdRMode;

/**
 * @brief Start reading sectors from the disc.
 * @param lsn First sector.
 * @param sectors Number of sectors.
 * @param buffer Destination.
 * @param mode Read mode.
 * @return Nonzero when the read was started.
 */
s32 sceCdRead(u32 lsn, u32 sectors, void* buffer, sceCdRMode* mode);

/**
 * @brief Wait for the current disc command.
 * @param mode 0 to block until it finishes.
 * @return Zero when finished.
 */
s32 sceCdSync(s32 mode);

/**
 * @brief Abort the current disc command.
 * @return Nonzero when the abort was issued.
 */
s32 sceCdBreak(void);

/**
 * @brief Get the last disc command's error.
 * @return The error code, zero for none, or -1 when it can't be read.
 */
s32 sceCdGetError(void);

#ifdef __cplusplus
}
#endif

#endif
