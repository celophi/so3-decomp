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

/**
 * @brief Start opening a file on a card.
 * @param port Card port.
 * @param slot Card slot.
 * @param name File name.
 * @param mode Open mode flags.
 * @return Zero when the command started.
 */
s32 sceMcOpen(s32 port, s32 slot, const char* name, s32 mode);

/**
 * @brief Start creating a directory on a card.
 * @param port Card port.
 * @param slot Card slot.
 * @param name Directory name.
 * @return Zero when the command started.
 */
s32 sceMcMkdir(s32 port, s32 slot, const char* name);

/**
 * @brief Start changing a card's current directory.
 * @param port Card port.
 * @param slot Card slot.
 * @param name New directory.
 * @param previous Receives the previous directory, or null.
 * @return Zero when the command started.
 */
s32 sceMcChdir(s32 port, s32 slot, const char* name, char* previous);

/**
 * @brief Start writing to a card file.
 * @param fd File descriptor.
 * @param buffer Source.
 * @param size Bytes to write.
 * @return Zero when the command started.
 */
s32 sceMcWrite(s32 fd, const void* buffer, s32 size);

/**
 * @brief Start closing a card file.
 * @param fd File descriptor.
 * @return Zero when the command started.
 */
s32 sceMcClose(s32 fd);

/**
 * @brief Start moving a card file's position.
 * @param fd File descriptor.
 * @param offset Position offset.
 * @param mode Zero from the start, one from the current position, two from the end.
 * @return Zero when the command started.
 */
s32 sceMcSeek(s32 fd, s32 offset, s32 mode);

/**
 * @brief Start reading from a card file.
 * @param fd File descriptor.
 * @param buffer Destination.
 * @param size Bytes to read.
 * @return Zero when the command started.
 */
s32 sceMcRead(s32 fd, void* buffer, s32 size);

/**
 * @brief Start reading a card directory into a table.
 * @param port Card port.
 * @param slot Card slot.
 * @param name Directory or file pattern.
 * @param mode Zero to start a listing, nonzero to continue it.
 * @param maximum Most entries to read.
 * @param table Entry table, 64-byte aligned.
 * @return Zero when the command started.
 */
s32 sceMcGetDir(s32 port, s32 slot, const char* name, u32 mode, s32 maximum, void* table);

/**
 * @brief Start formatting a card.
 * @param port Card port.
 * @param slot Card slot.
 * @return Zero when the command started.
 */
s32 sceMcFormat(s32 port, s32 slot);

/**
 * @brief Start changing a file's information.
 * @param port Card port.
 * @param slot Card slot.
 * @param name File name.
 * @param info New file information.
 * @param flags Which parts of the information to change.
 * @return Zero when the command started.
 */
s32 sceMcSetFileInfo(s32 port, s32 slot, const char* name, const void* info, s32 flags);

s32 mcHearAlarm(s32 callback_arg0, s32 callback_arg1, s32 sema_id);

#ifdef __cplusplus
}
#endif

#endif
