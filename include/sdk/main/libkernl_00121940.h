#ifndef SO3_SDK_MAIN_LIBKERNL_00121940_H
#define SO3_SDK_MAIN_LIBKERNL_00121940_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief EE kernel syscall 100: write back or invalidate the caches (libkernl FlushCache).
 * @param mode Cache operation selector.
 */
void FlushCache(s32 mode);

/**
 * @brief Initialize the TLB.
 */
void InitTLB(void);

/**
 * @brief Signal a semaphore from interrupt context.
 * @param sema_id Semaphore ID to signal.
 * @return Result from the syscall.
 */
s32 iSignalSema(s32 sema_id);

/**
 * @brief Delete a semaphore.
 * @param sema_id Semaphore ID to delete.
 * @return The deleted semaphore's ID, or a negative value on failure.
 */
s32 DeleteSema(s32 sema_id);

/** Alarm callback: the alarm ID, the time it was set for, and the argument passed to SetAlarm. */
typedef void (*KernelAlarmHandler)(s32 alarm_id, u16 time, void* common);

/**
 * @brief Call a handler after a number of horizontal syncs.
 * @param time Horizontal syncs to wait.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 SetAlarm(u16 time, KernelAlarmHandler handler, void* common);

/**
 * @brief SetAlarm for use from interrupt context.
 * @param time Horizontal syncs to wait.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 iSetAlarm(u16 time, KernelAlarmHandler handler, void* common);

/**
 * @brief Report failure to close a file descriptor.
 * @param fd File descriptor.
 * @return -1.
 */
s32 close(s32 fd);
/**
 * @brief Report an unsupported ioctl request.
 * @param fd File descriptor.
 * @param request Request code.
 * @param argp Request argument.
 * @return -1.
 */
s32 ioctl(s32 fd, s32 request, void* argp);
/**
 * @brief Report that seeking is unsupported.
 * @param fd File descriptor.
 * @param offset Offset.
 * @param whence Reference point.
 * @return -1.
 */
s32 lseek(s32 fd, s32 offset, s32 whence);
/**
 * @brief Report that a file descriptor is a terminal.
 * @param fd File descriptor.
 * @return 1.
 */
s32 isatty(s32 fd);
/**
 * @brief Return the fixed process identifier.
 * @return 1.
 */
s32 getpid(void);
/**
 * @brief Reinitialize the TLB before library termination.
 */
void TerminateLibrary(void);

#ifdef __cplusplus
}
#endif

#endif
