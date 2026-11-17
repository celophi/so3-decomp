#include "include_asm.h"
#include "main/interrupt_lock.h"
#include "main/sif.h"
#include "main/system.h"
#include "main/utility.h"

extern "C" {

void resident_sif_wake_alarm(s32 alarm_id, u16 time, void* common);

/**
 * @brief SIF command 4 handler: pass 4 to the SIF command receiver.
 * @param packet Command packet.
 * @param data Handler data.
 */
void resident_sif_handle_command_4(void* packet, void* data)
{
    ResidentListener* receiver = static_cast<ResidentListener*>(g_sif_command_receiver);

    if (receiver)
    {
        receiver->notify((void*)4);
    }

    ee_exit_handler();
}

/**
 * @brief SIF command 2 handler: pass 2 to the SIF command receiver.
 * @param packet Command packet.
 * @param data Handler data.
 */
void resident_sif_handle_command_2(void* packet, void* data)
{
    ResidentListener* receiver = static_cast<ResidentListener*>(g_sif_command_receiver);

    if (receiver)
    {
        receiver->notify((void*)2);
    }

    ee_exit_handler();
}

/**
 * @brief SIF command 1 handler: pass 1 to the SIF command receiver.
 * @param packet Command packet.
 * @param data Handler data.
 */
void resident_sif_handle_command_1(void* packet, void* data)
{
    ResidentListener* receiver = static_cast<ResidentListener*>(g_sif_command_receiver);

    if (receiver)
    {
        receiver->notify((void*)1);
    }

    ee_exit_handler();
}

/**
 * @brief SIF command 0 handler: pass 0 to the SIF command receiver.
 * @param packet Command packet.
 * @param data Handler data.
 */
void resident_sif_handle_command_0(void* packet, void* data)
{
    ResidentListener* receiver = static_cast<ResidentListener*>(g_sif_command_receiver);

    if (receiver)
    {
        receiver->notify((void*)0);
    }

    ee_exit_handler();
}

/**
 * @brief Send queued SIF commands until the queue is empty or the IOP has no room.
 * @param sif SIF link.
 */
void resident_sif_flush_commands(ResidentSif* sif)
{
    s32 next;
    ResidentSifQueuedCommand* queued;
    s32 command;
    void* source;
    void* destination;
    s32 size;

    for (;;)
    {
        next = sif->queue_read_index + 1;

        if (next == 256)
        {
            next = 0;
        }

        if (next == sif->queue_write_index)
        {
            return;
        }

        queued = &sif->queue[next];
        command = queued->command;
        source = queued->source;
        destination = queued->destination;
        size = queued->size;
        sif->queue_packets[next].option = size;

        if (sceSifSendCmd(command, &sif->queue_packets[next], sizeof(SifCommandHeader), source, destination, size) == 0)
        {
            return;
        }

        sif->queue_read_index = next;
    }
}

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
s32 resident_sif_queue_command(ResidentSif* sif, s32 command, void* source, void* destination, s32 size, s32 in_interrupt)
{
    s32 write_index;

    if (!in_interrupt)
    {
        DIntr();
    }

    if (sif->queue_read_index == (write_index = sif->queue_write_index))
    {
        if (!in_interrupt)
        {
            EIntr();
        }

        return 0;
    }

    sif->queue[write_index].command = command;
    sif->queue[write_index].source = source;
    sif->queue[write_index].destination = destination;
    sif->queue[write_index].size = size;
    write_index++;

    if (write_index == 256)
    {
        write_index = 0;
    }

    sif->queue_write_index = write_index;

    if (!in_interrupt)
    {
        EIntr();
    }

    return 1;
}

/**
 * @brief Send a SIF command from interrupt context, queueing it if earlier commands are waiting or the IOP has no
 * room.
 * @param sif SIF link.
 * @param command Command ID.
 * @param source EE data sent with the command.
 * @param destination IOP address of the data.
 * @param size Data size in bytes; zero sends nothing.
 */
void resident_sif_isend_command(ResidentSif* sif, s32 command, void* source, void* destination, s32 size)
{
    s32 next;
    u32 sent;

    if (size == 0)
    {
        return;
    }

    next = sif->queue_read_index + 1;

    if (next == 256)
    {
        next = 0;
    }

    if (next != sif->queue_write_index)
    {
        resident_sif_queue_command(sif, command, source, destination, size, 1);
        return;
    }

    sif->interrupt_packets[sif->interrupt_packet_index].option = size;
    sent = isceSifSendCmd(command, &sif->interrupt_packets[sif->interrupt_packet_index], sizeof(SifCommandHeader),
                          source, destination, size);
    sif->interrupt_packet_index++;

    if (sif->interrupt_packet_index == 256)
    {
        sif->interrupt_packet_index = 0;
    }

    if (sent == 0)
    {
        resident_sif_queue_command(sif, command, source, destination, size, 1);
    }
}

/**
 * @brief Send a SIF command, queueing it if earlier commands are waiting or the IOP has no room.
 * @param sif SIF link.
 * @param command Command ID.
 * @param source EE data sent with the command.
 * @param destination IOP address of the data.
 * @param size Data size in bytes; zero sends nothing.
 */
void resident_sif_send_command(ResidentSif* sif, s32 command, void* source, void* destination, s32 size)
{
    s32 next;
    u32 sent;

    if (size == 0)
    {
        return;
    }

    next = sif->queue_read_index + 1;

    if (next == 256)
    {
        next = 0;
    }

    if (next != sif->queue_write_index)
    {
        resident_sif_queue_command(sif, command, source, destination, size, 0);
        return;
    }

    DIntr();
    sif->interrupt_packets[sif->interrupt_packet_index].option = size;
    sent = sceSifSendCmd(command, &sif->interrupt_packets[sif->interrupt_packet_index], sizeof(SifCommandHeader),
                         source, destination, size);
    sif->interrupt_packet_index++;

    if (sif->interrupt_packet_index == 256)
    {
        sif->interrupt_packet_index = 0;
    }

    EIntr();

    if (sent == 0)
    {
        resident_sif_queue_command(sif, command, source, destination, size, 0);
    }
}

/**
 * @brief Check whether a request sent over the SIF link is still waiting for its reply.
 * @param sif SIF link.
 * @param handle Request handle.
 * @return True while the request is outstanding.
 */
bool resident_sif_is_request_pending(ResidentSif* sif, u32 handle)
{
    if (!handle)
    {
        return false;
    }

    ResidentInterruptLock lock;
    s32 index = sif->reply_index + 1;
    s32 end = sif->unk1C;

    if (index == 32)
    {
        index = 0;
    }

    for (;;)
    {
        if (index == end)
        {
            break;
        }

        if (sif->replies[index].unk10 == handle)
        {
            return true;
        }

        if (++index == 32)
        {
            index = 0;
        }
    }

    return false;
}

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
u32 resident_sif_request(ResidentSif* sif, s32 command, void* reply, s32 callback, s32 argument, s32 in_interrupt)
{
    if (!in_interrupt)
    {
        DIntr();
    }

    s32 read = sif->reply_index;
    s32 index = sif->unk1C;

    if (read == index)
    {
        if (!in_interrupt)
        {
            EIntr();
            (void)sif->unk32C.signal();
        }
        else
        {
            (void)sif->unk32C.isignal();
        }

        return 0;
    }

    sif->replies[index].unk00 = command;
    sif->replies[index].buffer = (u32*)reply;
    sif->replies[index].callback = (void (*)(void*, void*))callback;
    sif->replies[index].argument = (void*)argument;
    sif->unk14++;

    if (sif->unk14 == 0)
    {
        sif->unk14 = 1;
    }

    sif->replies[index].unk10 = sif->unk14;
    index++;

    if (index == 32)
    {
        index = 0;
    }

    sif->unk1C = index;

    if (sif->unk2DC[0])
    {
        if (!in_interrupt)
        {
            EIntr();
        }
    }
    else if (!in_interrupt)
    {
        EIntr();
        (void)sif->unk32C.signal();
    }
    else
    {
        (void)sif->unk32C.isignal();
    }

    return sif->unk14;
}

/**
 * @brief Move to the next reply slot and deliver the reply in the reply buffer to it: copy it into the slot's buffer,
 * if any, and call the slot's callback.
 * @param sif SIF link.
 */
void resident_sif_deliver_reply(ResidentSif* sif)
{
    DIntr();
    s32 index = sif->reply_index + 1;

    if (index == 32)
    {
        index = 0;
    }

    sif->reply_index = index;
    EIntr();

    ResidentSifReply* reply = &sif->replies[index];

    if (reply->buffer)
    {
        u32* source = sif->reply_data;
        u32* destination = reply->buffer;

        for (s32 i = 0; i < 64 / sizeof(u32); i++)
        {
            *destination++ = *source++;
        }
    }

    if (reply->callback)
    {
        if (reply->buffer)
        {
            reply->callback(reply->buffer, reply->argument);
        }
        else
        {
            reply->callback(sif->reply_data, reply->argument);
        }
    }
}

/**
 * @brief Send the request in the slot after the last reply to the IOP and wait for the reply.
 * @param sif SIF link.
 * @return Zero when no request is waiting, one after the call, or the RPC's negative error.
 */
static inline s32 sif_call_next(ResidentSif* sif)
{
    s32 index = sif->reply_index + 1;

    if (index == 32)
    {
        index = 0;
    }

    if (index == sif->unk1C)
    {
        return 0;
    }

    u32 function = sif->replies[index].unk00;
    u8* send = sif->buffer + index * 64;
    s32 result = sceSifCallRpc(&sif->rpc_client, function, 0, send, 64, sif->reply_data, 64, 0, 0);

    return result < 0 ? result : 1;
}

/**
 * @brief Thread body: sleep until a request is queued, then call the IOP for each waiting request and deliver its
 * reply.
 */
void ResidentSif::run()
{
    for (;;)
    {
        unk2DC[0] = 0;
        WaitSema(unk32C.id);
        unk2DC[0] = 1;

        for (;;)
        {
            s32 result = sif_call_next(&g_sif);

            if (result == 0)
            {
                break;
            }

            if (result == 1)
            {
                resident_sif_deliver_reply(&g_sif);
            }
        }
    }
}

/**
 * @brief Wait a moment, then try to bind the SIF link's RPC client to server 0x1234.
 * @param sif SIF link.
 * @return Zero once the server answers, minus one when binding fails.
 */
s32 resident_sif_bind(ResidentSif* sif)
{
    do
    {
        resident_system_set_alarm(resident_get_system(), 0x106, resident_sif_wake_alarm, (void*)GetThreadId());
        resident_thread_sleep();

        if (sceSifBindRpc(&sif->rpc_client, 0x1234, 0) < 0)
        {
            return -1;
        }
    } while (sif->rpc_client.server == 0);

    return 0;
}

/**
 * @brief Alarm handler that wakes the thread waiting on it.
 * @param alarm_id Alarm.
 * @param time Time the alarm fired.
 * @param common ID of the thread to wake.
 */
void resident_sif_wake_alarm(s32 alarm_id, u16 time, void* common)
{
    iWakeupThread((s32)common);
    ee_exit_handler();
}

/**
 * @brief Set up the SIF link: carve its buffers, register its SIF command handlers and start its thread.
 * @param sif SIF link.
 */
void resident_sif_start(ResidentSif* sif)
{
    u8* buffer;

    sif->allocation = new (0) u8[0x950];
    buffer = (u8*)(((u32)sif->allocation + 63) & ~63);
    sif->buffer = buffer;
    sif->unk2A4 = buffer + 0x800;
    sif->reply_data = (u32*)(buffer + 0x800);
    sif->unk2AC = buffer + 0x840;
    sif->unk2B0 = buffer + 0x880;
    sif->unk2E0[0] = buffer + 0x8C0;
    sif->unk2E0[1] = buffer + 0x8D0;
    sif->unk2E0[2] = buffer + 0x8E0;
    sif->unk2E0[3] = buffer + 0x8F0;
    sif->unk2E0[4] = buffer + 0x900;
    sif->unk14 = 1;
    sif->reply_index = 0;
    sif->unk1C = 1;
    sif->interrupt_packet_index = 0;
    sif->queue_read_index = 0;
    sif->queue_write_index = 1;
    g_sif_command_receiver = 0;
    DIntr();
    sceSifSetCmdBuffer(sif->handlers, 5);
    sceSifAddCmdHandler(0, resident_sif_handle_command_0, 0);
    sceSifAddCmdHandler(1, resident_sif_handle_command_1, 0);
    sceSifAddCmdHandler(2, resident_sif_handle_command_2, 0);
    sceSifAddCmdHandler(4, resident_sif_handle_command_4, 0);
    EIntr();
    sif->start();
}

/** @brief Free the buffers and destroy the semaphores. */
ResidentSif::~ResidentSif()
{
    delete allocation;
}
}
