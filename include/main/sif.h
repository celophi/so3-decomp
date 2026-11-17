#ifndef SO3_MAIN_SIF_H
#define SO3_MAIN_SIF_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "main/semaphore.h"
#include "main/thread.h"

#ifndef __cplusplus
typedef struct ResidentSif ResidentSif;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** Object that receives the IOP's SIF commands 0 to 3, or null; the sound system registers its stream. */
extern void* g_sif_command_receiver;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/** A command the SIF link sends once the IOP has room for it. */
typedef struct ResidentSifQueuedCommand
{
    s32 command;
    void* source;
    void* destination;
    s32 size;
} ResidentSifQueuedCommand;

/** Where a reply from the IOP goes, and who hears about it. */
typedef struct ResidentSifReply
{
    // TODO: volatile is my guess; the link's thread reads this and the link's buffer into locals before the RPC call,
    volatile u32 unk00;
    u32* buffer;
    void (*callback)(void* reply, void* argument);
    void* argument;
    u32 unk10;
} ResidentSifReply;

/**
 * The EE side of the link with the IOP: the SIF command handlers, the RPC binding to server 0x1234, a ring of
 * reply slots and a queue for commands the IOP couldn't take yet. Its kernel thread has vtable D_0014FB10.
 */
class ResidentSif : public ResidentThread
{
public:
    u8* allocation;
    s32 unk14;

    // TODO: The two ring indices are volatile because the reply interrupt moves them; the request wrappers
    // reread unk1C after comparing it, and nothing else I tried does that.

    volatile s32 reply_index;
    volatile s32 unk1C;
    ResidentSifReply replies[32];
    u8* volatile buffer;
    u8* unk2A4;
    u32* reply_data;
    u8* unk2AC;
    u8* unk2B0;
    SifClientData rpc_client;
    u8 unk2DC[4];
    u8* unk2E0[5];
    SifCommandHandlerEntry handlers[5];
    u8 unk31C[0x10];
    ResidentSemaphore unk32C;
    ResidentSemaphore request_semaphore;

    /**
     * @brief Get the semaphore held while a request is queued.
     * @return The request semaphore.
     */
    ResidentSemaphore* get_request_semaphore()
    {
        return &request_semaphore;
    }

    /**
     * @brief Get the 64-byte argument block of the next request.
     * @return The block, or null when every reply slot is taken.
     */
    u32* get_request_arguments()
    {
        if (reply_index == unk1C)
        {
            return 0;
        }

        u8* base = buffer;

        return (u32*)(base + unk1C * 64);
    }

    s32 interrupt_packet_index;
    SifCommandHeader interrupt_packets[256];
    s32 queue_read_index;
    s32 queue_write_index;
    ResidentSifQueuedCommand queue[256];
    u8 unk2348[8];
    SifCommandHeader queue_packets[256];

    /** @brief Free the buffers and destroy the semaphores. */
    virtual ~ResidentSif();

    /** @brief Thread body: sleep until a request is queued, then call the IOP for each waiting request. */
    virtual void run();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
/** The SIF link with the IOP. */
extern ResidentSif g_sif;

/**
 * @brief Set up the SIF link: carve its buffers, register its SIF command handlers and start its thread.
 * @param sif SIF link.
 */
void resident_sif_start(ResidentSif* sif);

/**
 * @brief Wait a moment, then try to bind the SIF link's RPC client to server 0x1234.
 * @param sif SIF link.
 * @return Zero once the server answers, minus one when binding fails.
 */
s32 resident_sif_bind(ResidentSif* sif);

/**
 * @brief Send queued SIF commands until the queue is empty or the IOP has no room.
 * @param sif SIF link.
 */
void resident_sif_flush_commands(ResidentSif* sif);

/**
 * @brief Queue a SIF command to send later.
 * @param sif SIF link.
 * @param command Command ID.
 * @param source EE data sent with the command.
 * @param destination IOP address of the data.
 * @param size Data size in bytes.
 * @param in_interrupt Nonzero when called with interrupts already disabled.
 * @return One when queued, zero when the queue is full.
 */
s32 resident_sif_queue_command(ResidentSif* sif, s32 command, void* source, void* destination, s32 size, s32 in_interrupt);

/**
 * @brief Send a SIF command from interrupt context, queueing it if earlier commands are waiting or the IOP has no
 * room.
 * @param sif SIF link.
 * @param command Command ID.
 * @param source EE data sent with the command.
 * @param destination IOP address of the data.
 * @param size Data size in bytes; zero sends nothing.
 */
void resident_sif_isend_command(ResidentSif* sif, s32 command, void* source, void* destination, s32 size);

#ifdef __cplusplus
/**
 * @brief Check whether a request sent over the SIF link is still waiting for its reply.
 * @param sif SIF link.
 * @param handle Request handle.
 * @return True while the request is outstanding.
 */
bool resident_sif_is_request_pending(ResidentSif* sif, u32 handle);
#endif

/**
 * @brief Send a SIF command, queueing it if earlier commands are waiting or the IOP has no room.
 * @param sif SIF link.
 * @param command Command ID.
 * @param source EE data sent with the command.
 * @param destination IOP address of the data.
 * @param size Data size in bytes; zero sends nothing.
 */
void resident_sif_send_command(ResidentSif* sif, s32 command, void* source, void* destination, s32 size);

/**
 * @brief Send a request to the IOP with the argument block from get_request_arguments: fill the next reply slot,
 * number the request and release the request semaphore.
 * @param sif SIF link.
 * @param command Request command.
 * @param reply Receives the reply, or null.
 * @param callback Called with the reply, or zero.
 * @param argument Passed to callback.
 * @param in_interrupt Nonzero when called with interrupts already disabled.
 * @return Request handle, or zero when every reply slot is taken.
 */
u32 resident_sif_request(ResidentSif* sif, s32 command, void* reply, s32 callback, s32 argument, s32 in_interrupt);

/**
 * @brief Move to the next reply slot and deliver the reply in the reply buffer to it.
 * @param sif SIF link.
 */
void resident_sif_deliver_reply(ResidentSif* sif);
#endif

#ifdef __cplusplus
}
#endif

#endif
