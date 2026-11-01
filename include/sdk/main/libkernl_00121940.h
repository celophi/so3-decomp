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

/** Semaphore settings passed to CreateSema (Sony's struct SemaParam). */
typedef struct SemaParam
{
    s32 currentCount;
    s32 maxCount;
    s32 initCount;
    s32 numWaitThreads;
    u32 attr;
    u32 option;
} SemaParam;

/**
 * @brief Create a semaphore.
 * @param param Initial and maximum counts.
 * @return The new semaphore's ID, or a negative value on failure.
 */
s32 CreateSema(SemaParam* param);

/**
 * @brief Enable interrupts (libkernl EIntr).
 * @return Result from the syscall.
 */
s32 EIntr(void);

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

/** @brief Return the calling thread's ID. @return Thread ID. */
s32 GetThreadId(void);

s32 WakeupThread(s32 thread_id);

/** Header that starts every SIF command packet. */
typedef struct SifCommandHeader
{
    /** Packet size in the low 8 bits, extra data size in the upper 24. */
    u32 size;

    /** IOP address of the extra data. */
    void* destination;

    /** Command ID. */
    s32 command;

    /** Free word for the sender. */
    u32 option;
} SifCommandHeader;

/** @brief Handle a SIF command. @param packet Received packet. @param data Value registered with the handler. */
typedef void (*SifCommandHandler)(void* packet, void* data);

/** One registered SIF command handler. */
typedef struct SifCommandHandlerEntry
{
    SifCommandHandler handler;
    void* data;
} SifCommandHandlerEntry;

/** Server side of a SIF RPC binding. */
typedef struct SifServeData SifServeData;

/** Client side of a SIF RPC binding. */
typedef struct SifClientData
{
    void* packet;
    u32 packet_id;
    s32 semaphore_id;
    u32 mode;
    u32 command;
    void* buffer;
    void* cache_buffer;
    void (*end_function)(void* parameter);
    void* end_parameter;

    /** Server the binding reached, or null until the IOP side is ready. */
    SifServeData* server;
} SifClientData;

SifCommandHandlerEntry* sceSifSetCmdBuffer(SifCommandHandlerEntry* entries, s32 count);

void sceSifAddCmdHandler(u32 command, SifCommandHandler handler, void* data);

u32 sceSifSendCmd(s32 command, void* packet, s32 packet_size, void* source, void* destination, s32 size);

u32 isceSifSendCmd(s32 command, void* packet, s32 packet_size, void* source, void* destination, s32 size);

s32 sceSifBindRpc(SifClientData* client, u32 server_id, u32 mode);

s32 DIntr(void);

s32 EIntr(void);

/**
 * @brief Change a thread's priority.
 * @param thread_id Thread ID.
 * @param priority New priority.
 * @return The previous priority, or a negative value on failure.
 */
s32 ChangeThreadPriority(s32 thread_id, s32 priority);

/** @brief Initialize the SIF remote procedure call layer. @param mode Initialization mode; 0 for normal. */
void sceSifInitRpc(u32 mode);

/**
 * @brief Reboot the IOP with a replacement module image.
 * @param image Path of the IOP replacement image.
 * @return Nonzero once the reboot request is sent.
 */
s32 sceSifRebootIop(const char* image);

/** @brief Check whether the IOP has finished rebooting. @return Nonzero once it has. */
s32 sceSifSyncIop(void);

/** @brief Reset the IOP module loader's RPC binding. @return Zero on success. */
s32 sceSifLoadFileReset(void);

/** @brief Reset the file system RPC binding. @return Zero on success. */
s32 sceFsReset(void);

/** @brief Initialize the IOP heap RPC binding. @return Zero on success. */
s32 sceSifInitIopHeap(void);

/** @brief Allocate IOP memory. @param size Bytes to allocate. @return IOP address, or null. */
void* sceSifAllocIopHeap(u32 size);

/** @brief Free IOP memory. @param address IOP address. @return Zero on success. */
s32 sceSifFreeIopHeap(void* address);

/** One EE-to-IOP SIF DMA transfer. */
typedef struct SifDmaTransfer
{
    /** EE source address. */
    void* data;

    /** IOP destination address. */
    void* address;

    /** Bytes to transfer, a multiple of 16. */
    u32 size;

    u32 mode;
} SifDmaTransfer;

/**
 * @brief Queue EE-to-IOP SIF DMA transfers.
 * @param transfers Transfers to queue.
 * @param count Number of transfers.
 * @return Transfer ID for sceSifDmaStat, or zero on failure.
 */
u32 sceSifSetDma(SifDmaTransfer* transfers, s32 count);

/** @brief Check a SIF DMA transfer. @param id Transfer ID. @return Negative once the transfer is done. */
s32 sceSifDmaStat(u32 id);

/**
 * @brief Load an IOP module from IOP memory.
 * @param module Module image in IOP memory.
 * @param argument_size Size of the arguments.
 * @param arguments Module arguments.
 * @return Module ID, or a negative value on failure.
 */
s32 sceSifLoadModuleBuffer(void* module, s32 argument_size, const char* arguments);

/**
 * @brief Load and start an IOP module from IOP memory.
 * @param module Module image in IOP memory.
 * @param argument_size Size of the arguments.
 * @param arguments Module arguments.
 * @param result Receives the module's start result.
 * @return Module ID, or a negative value on failure.
 */
s32 sceSifLoadStartModuleBuffer(void* module, s32 argument_size, const char* arguments, s32* result);

#ifdef __cplusplus
}
#endif

#endif
