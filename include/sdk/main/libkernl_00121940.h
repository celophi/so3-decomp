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
