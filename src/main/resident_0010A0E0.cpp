#include "include_asm.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_00101550.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_00137290.h"
#include "main/func_0011EE00.h"
#include "main/resident_data.h"
#include "main/resident_00101260.h"

/** Address bit that maps EE main memory uncached. */
#define UNCACHED_SEGMENT 0x20000000

/** EE interrupt controller cause for the end of vertical blank. */
#define INTC_VBLANK_END 3

/** Priority resident threads are created with and return to after a time slice. */
#define RESIDENT_THREAD_PRIORITY 50

/** Priority a time-sliced thread runs at during its slice. */
#define RESIDENT_THREAD_SLICE_PRIORITY 44

/** Size of a disc block, the unit voice positions are given in. */
#define SOUND_BLOCK_SIZE 2048

/** Resource request tag of a voice read. */
#define SOUND_VOICE_READ_TAG 7

/** Resource request tag of the voice table read. */
#define SOUND_VOICE_TABLE_READ_TAG 8

/** Resource request priority of a voice read. */
#define SOUND_VOICE_READ_PRIORITY 216000

/** Resource request tag of a music read. */
#define SOUND_MUSIC_READ_TAG 4

/** Key queued for music streamed from a resource rather than the music table. */
#define SOUND_RESOURCE_MUSIC_KEY 30000

/** Space the installed archive needs ahead of its resources. */
#define RESIDENT_INSTALL_HEADER_SIZE 0x2000

/** Unit the install's space is reserved in. */
#define RESIDENT_INSTALL_ALIGNMENT 0x40000

/** Kernel thread creation parameters (libkernl ThreadParam). */
struct ThreadParam
{
    s32 status;
    void (*entry)(void*);
    void* stack;
    s32 stackSize;
    void* gpReg;
    s32 initPriority;
    s32 currentPriority;
    u32 attr;
    u32 option;
    s32 waitType;
    s32 waitId;
    s32 wakeupCount;
};

/** GS CSR; bit 13 is the field being displayed. */
#define GS_CSR (*(volatile u64*)0x12001000)

/** Position of the table of contents, in 2048-byte blocks. */
#define RESIDENT_ARCHIVE_TOC_POSITION 0x400

/** Words in the table of contents: a position, size and install flag per resource. */
#define RESIDENT_ARCHIVE_TOC_WORDS (RESIDENT_RESOURCE_COUNT * 3)

/** Seed of the key stream the table of contents is encrypted with. */
#define RESIDENT_ARCHIVE_TOC_KEY 0x13578642

/** Pad direction buttons, in the held bits. */
#define SCE_PADLup 0x10
#define SCE_PADLright 0x20
#define SCE_PADLdown 0x40
#define SCE_PADLleft 0x80

/** INTC cause of the vblank start interrupt. */
#define INTC_VBLANK_S 2

/** scePad2CreateSocket option that opens one specific port. */
#define SCE_PAD2_SPECIFIC_PORT 2

/** Socket parameters for scePad2CreateSocket. */
typedef struct scePad2SocketParam
{
    s32 option;
    s32 port;
    s32 slot;
    s32 number;
    u8 name[16];
} scePad2SocketParam;


/**
 * @brief Check whether the object release ring has no insertion slot available.
 * @param queue Deferred release queues.
 * @return True when the object ring is full, or false when it has space.
 */
static inline bool resident_object_release_ring_is_full(const ResidentReleaseQueues* queue)
{
    return queue->objects.read_index == queue->objects.write_index;
}

extern "C" {
/** The time-slice scheduler. */
extern ResidentThreadScheduler D_001CFA00;

void func_00114A00(ResidentThreadScheduler* scheduler, ResidentTimeSlicedThread* thread);
void func_00114870(s32 alarm_id, u16 time, void* common);
s32 iReleaseAlarm(s32 alarm_id);
s32 iChangeThreadPriority(s32 thread_id, s32 priority);

/** The global pointer value threads start with. */
extern u8 _gp;

s32 CreateThread(ThreadParam* param);
s32 TerminateThread(s32 thread_id);
s32 DeleteThread(s32 thread_id);
void ExitDeleteThread(void);
void func_4DA730(struct ResidentSoundEmitter* emitter, float* position);
u32 func_0010E4B0(ResidentSound* sound, const float* position, s32 arg2, s32 arg3);
s32 AddIntcHandler(s32 cause, s32 (*handler)(s32 cause), s32 next);
s32 RemoveIntcHandler(s32 cause, s32 handler_id);
s32 EnableIntc(s32 cause);
s32 DisableIntc(s32 cause);
s32 DIntr(void);
s32 EIntr(void);
s32 sceDbcInit(void);
s32 sceCdDiskReady(s32 mode);
void* sceCdPOffCallback(void (*callback)(void*), void* argument);
void D_00118C50(void* argument);
s32 scePad2Init(s32 mode);
s32 scePad2CreateSocket(scePad2SocketParam* param, void* buffer);
s32 scePad2GetState(s32 socket);
s32 scePad2Read(s32 socket, u8* data);
s32 scePad2GetButtonProfile(s32 socket, u8* profile);
s32 sceVibGetProfile(s32 socket, u8* profile);
s32 sceVibSetActParam(s32 socket, s32 profile_size, u8* profile, s32 data_size, u8* data);
s32 AddIntcHandler(s32 cause, s32 (*handler)(s32), s32 next);
s32 EnableIntc(s32 cause);
s32 D_0011E9A0(s32 cause);
void func_4DD520(ResidentDisplay* display, s32 field);
void func_4DCDA0(ResidentDisplay* display, s32 value);
void func_00103510(ResidentResourceQueue* queue);
void resident_pad_update_vibration(ResidentInputSystem* input, s32 slot);
void func_0011E9E0(ResidentInputSystem* input, s32 slot, s32 full);
extern u32 D_001B641C;
void func_00118880(void* worker, s32 command, s32 argument);
void func_00114E00(void* value);
s32 iWakeupThread(s32 thread_id);
s32 StartThread(s32 thread_id, void* argument);
s32 SleepThread(void);
s32 func_00135320(double left, double right);
void func_0010BC10(void* packet, void* data);
void func_0010BC50(void* packet, void* data);
void func_0010BC90(void* packet, void* data);
void func_0010BCD0(void* packet, void* data);
void func_0010C6D0(s32 alarm_id, u16 time, void* common);
s32 func_00108430(void* object, s32 arg1, void* callback, void* argument, s32 arg4, s32 command, s32 arg6, s32 arg7);
s32 func_00107DD0(void* object, s32 arg1, void* callback, void* argument, s32 arg4, s32 command, s32 arg6, s32 arg7,
                  u32 arg8, s32 arg9, s32 arg10);
void func_0010A7A0(ResidentStreamThread* stream);
void func_00107420(ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3);
u32 func_00108A00(ResidentSoundStream* stream, u32* reply, s32 arg2, s32 arg3, s32 index, u32 arg5, u32 arg6, u32 arg7,
                  u32 arg8, u32 arg9);
void func_0010AA30(ResidentStreamThread* stream);
void func_0010B600(ResidentStreamThread* stream, s32 value);
typedef struct ResidentSpeakerAngles
{
    float angles[4];
} ResidentSpeakerAngles;
extern const ResidentSpeakerAngles D_00144260;
typedef struct ConstantByteSetterOwnerresident_0010A0E0
{
    u8 unk00[0x1012];
    u8 unk1012;
} ConstantByteSetterOwnerresident_0010A0E0;





typedef struct ResidentThreadHandle114DD0
{
    u8 pad00[0x8];
    s32 unk08;
} ResidentThreadHandle114DD0;

typedef struct ResidentThreadStartContext14EB0
{
    u8 pad00[0x8];
    s32 unk08;
} ResidentThreadStartContext14EB0;

typedef struct ResidentByteAndWordResetB730
{
    u8 pad00[0x78];
    u8 unk78[4];
    u32 unk7C;
    u32 unk80;
    u32 unk84;
} ResidentByteAndWordResetB730;



extern s32 D_001B640C;
extern ResidentSound* D_001B6410;
extern u32 D_001CF8E0[56];

/**
 * @brief Point the receive blocks back at the start of the first buffer and clear their state.
 * @param stream Streaming thread.
 */
static inline void reset_receive_blocks(ResidentStreamThread* stream)
{
    stream->output_half = 0;
    stream->unk1B = 0;
    stream->output_cursor = stream->output_buffers[0] + 0x80;
    stream->unk20 = stream->output_buffers[0] + 0x40;
    stream->unk24 = stream->output_buffers[0] + 0x40;
    stream->unk28 = 0;
    stream->output_pending[0] = 0;
    stream->output_pending[1] = 0;
    stream->unk34[0] = 0;
    stream->unk34[1] = 0;
}

/**
 * @brief Empty both send blocks.
 * @param stream Streaming thread.
 */
static inline void reset_send_blocks(ResidentStreamThread* stream)
{
    stream->input_ready[0] = 0;
    stream->input_ready[1] = 0;
    stream->unk4A = 0;
    stream->input_half = 0;
    stream->unk4C = stream->input_buffers[0] + 0x40;
    stream->input_cursor = stream->input_buffers[0] + 0x80;
    stream->unk54[0] = 0;
    stream->unk54[1] = 0;
    stream->unk5C[0] = 0;
    stream->unk5C[1] = 0;
}

/**
 * @brief Empty the ring.
 * @param stream Streaming thread.
 */
static inline void reset_ring(ResidentStreamThread* stream)
{
    stream->unk78[0] = 0;
    stream->unk78[1] = 0;
    stream->unk7A = 0;
    stream->unk7B = 0;
    stream->unk7C = stream->unk84;
    stream->unk80 = stream->unk84;
}

/**
 * @brief Reset the streaming state and send a stream request (command -5) to the IOP.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param entry Resource entry to stream; its words at 0x10 and 0x14 are kept.
 * @param value Kept at unk90.
 * @param arg6 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 func_0010A0E0(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 value,
                  s32 arg6)
{
    if (stream->first_state != 0)
    {
        return 0;
    }

    reset_receive_blocks(stream);
    reset_send_blocks(stream);
    reset_ring(stream);
    stream->unk90 = value;
    stream->unk94 = 1;
    stream->unk95 = 0;
    stream->unk96 = 2;
    stream->unkBD = 0;
    stream->unk98 = 0;
    stream->unk9C = entry;
    stream->unkA0 = 0;
    stream->unkA4 = entry[4];
    stream->unkA8 = entry[5];
    stream->unkC0 = 0;
    return func_00108430(stream->stream, arg1, callback, argument, 0, -5, arg6, 0);
}

/**
 * @brief Reset the streaming state and send a stream request (command -4) to the IOP.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param entry Resource entry to stream; its words at 0x10 and 0x14 are kept.
 * @param arg6 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 func_0010A200(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 arg6)
{
    if (stream->first_state != 0)
    {
        return 0;
    }

    reset_receive_blocks(stream);
    reset_send_blocks(stream);
    reset_ring(stream);
    stream->unk94 = 1;
    stream->unk95 = 1;
    stream->unk96 = 0;
    stream->unkBD = 0;
    stream->unk98 = 0;
    stream->unk9C = entry;
    stream->unkA0 = 0;
    stream->unkA4 = entry[4];
    stream->unkA8 = entry[5];
    stream->unkC0 = 0;
    return func_00108430(stream->stream, arg1, callback, argument, 0, -4, arg6, 0);
}

/**
 * @brief Reset the block state and send a stream request (command -3) to the IOP; the ring is left alone.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param entry Resource entry to stream; its words at 0x10 and 0x14 are kept.
 * @param arg6 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 func_0010A310(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 arg6)
{
    if (stream->first_state != 0)
    {
        return 0;
    }

    reset_receive_blocks(stream);
    reset_send_blocks(stream);
    stream->unk94 = 1;
    stream->unk95 = 0;
    stream->unk96 = 0;
    stream->unkBD = 0;
    stream->unk98 = 0;
    stream->unk9C = entry;
    stream->unkA0 = 0;
    stream->unkA4 = entry[4];
    stream->unkA8 = entry[5];
    stream->unkC0 = 0;
    return func_00108430(stream->stream, arg1, callback, argument, 0, -3, arg6, 0);
}

/**
 * @brief Send command -2 to the IOP.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param arg6 Request argument.
 * @return The request result, or zero while unkB0 is set.
 */
s32 func_0010A400(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, s32 arg6)
{
    if (stream->second_state != 0)
    {
        return 0;
    }

    stream->unk74 = 0;
    stream->unkBE = 0;
    return func_00108430(stream->stream, arg1, callback, argument, 0, -2, arg6, 0);
}

/**
 * @brief Reset the block state and send command -1 to the IOP at full volume, centred.
 * @param stream Streaming thread.
 * @param arg1 Request argument.
 * @param callback Called when the request completes.
 * @param argument Passed to callback.
 * @param value Kept at unk90.
 * @param arg6 Request argument.
 * @param arg10 Request argument.
 * @return The request result, or zero while a request is already running.
 */
s32 func_0010A450(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, s32 value, s32 arg6,
                  s32 arg10)
{
    if (stream->first_state != 0)
    {
        return 0;
    }

    reset_receive_blocks(stream);
    reset_send_blocks(stream);
    stream->unk90 = value;
    stream->unk94 = 0;
    stream->unkBD = 0;
    stream->unkC0 = 0;
    return func_00107DD0(stream->stream, arg1, callback, argument, 0, -1, arg6, 0, (0x7F << 24) | (0x40 << 16), 0,
                         arg10);
}

/**
 * @brief Append bytes to the ring, first moving unread data back to the start of the ring when the end is too close.
 * @param stream Streaming thread.
 * @param data Bytes to append.
 * @param size Number of bytes in data.
 * @return Number of bytes appended.
 */
s32 func_0010A530(ResidentStreamThread* stream, const void* data, s32 size)
{
    s32 space;
    s32 unread;

    DIntr();
    space = stream->unk8C - stream->unk80;

    if (size <= space)
    {
        memcpy_guess((void*)((u32)stream->unk80 | UNCACHED_SEGMENT), data, size);
        stream->unk80 += size;
    }
    else
    {
        if (stream->unk7C != stream->unk84)
        {
            unread = stream->unk80 - stream->unk7C;
            memcpy_guess((void*)((u32)stream->unk84 | UNCACHED_SEGMENT), stream->unk7C, unread);
            stream->unk7C = stream->unk84;
            stream->unk80 = stream->unk84 + unread;
            space = stream->unk8C - stream->unk80;
        }

        if (space < size)
        {
            size = space;
        }

        memcpy_guess((void*)((u32)stream->unk80 | UNCACHED_SEGMENT), data, size);
        stream->unk80 += size;
    }

    EIntr();
    return size;
}

/**
 * @brief Copy words into the ring half being written, marking the half full and moving to the other half when it
 * fills.
 * @param stream Streaming thread.
 * @param words Words to copy.
 * @param size Number of bytes in words.
 * @return Number of bytes copied, or zero when the ring can't take data.
 */
s32 func_0010A650(ResidentStreamThread* stream, const u32* words, s32 size)
{
    u32* end;
    u32* next;
    u8 next_half;
    u32* cursor;
    s32 i;

    if (stream->unkBE != 0)
    {
        return 0;
    }

    if (stream->unk78[stream->unk7B] != 0)
    {
        return 0;
    }

    DIntr();

    if (stream->unk7B == 0)
    {
        end = (u32*)((u32)stream->unk88 | UNCACHED_SEGMENT);
        next = (u32*)((u32)stream->unk88 | UNCACHED_SEGMENT);
        next_half = 1;
    }
    else
    {
        end = (u32*)((u32)stream->unk8C | UNCACHED_SEGMENT);
        next = (u32*)((u32)stream->unk84 | UNCACHED_SEGMENT);
        next_half = 0;
    }

    cursor = (u32*)((u32)stream->unk80 | UNCACHED_SEGMENT);
    i = 0;

    while (i < size / 4)
    {
        *cursor++ = *words++;
        i++;

        if (cursor == end)
        {
            stream->unk78[stream->unk7B] = 1;
            cursor = next;
            stream->unk7B = next_half;
            break;
        }
    }

    stream->unk80 = (u8*)((u32)cursor & ~UNCACHED_SEGMENT);
    EIntr();
    return i * 4;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010A7A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010AA30);

/**
 * @brief Body of the streaming thread: on every wakeup run both streaming passes, then wake the waiting thread, if any.
 * @param stream Streaming thread.
 */
void func_0010B4C0(ResidentStreamThread* stream)
{
    for (;;)
    {
        do
        {
            func_00114E80();
            func_0010AA30(stream);
            func_0010A7A0(stream);
        } while (!stream->waiting_thread);

        WakeupThread(stream->waiting_thread);
        stream->waiting_thread = 0;
    }
}

/**
 * @brief Handle a notification from the IOP side of the stream.
 * @param stream Streaming thread.
 * @param event 0 when a receive block arrived, 2 to set unk74, 4 to send the next chunk.
 */
void func_0010B510(ResidentStreamThread* stream, s32 event)
{
    u32 value;

    switch (event)
    {
        case 0:
            stream->unk24 = stream->unk20;
            value = *(u32*)((u32)(stream->unk24 + 0x18) | UNCACHED_SEGMENT);

            if (value != 0)
            {
                stream->output_pending[stream->unk1B] = value;
                stream->unk34[stream->unk1B] = *(u32*)((u32)(stream->unk24 + 0x1C) | UNCACHED_SEGMENT);

                if (stream->unk1B == 0)
                {
                    stream->unk1B = 1;
                    stream->unk20 = stream->output_buffers[1] + 0x40;
                }
                else
                {
                    stream->unk1B = 0;
                    stream->unk20 = stream->output_buffers[0] + 0x40;
                }
            }

            stream->unk28 = 1;
            break;

        case 2:
            stream->unk74 = 1;
            break;

        case 4:
            func_0010B600(stream, 1);
            break;
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010B600);

/** Clear bytes at 0x78-0x7B and copy the word at 0x84 to offsets 0x7C and 0x80. */
void func_0010B730(void* object)
{
    ResidentByteAndWordResetB730* receiver = (ResidentByteAndWordResetB730*)object;
    receiver->unk78[0] = 0;
    receiver->unk78[1] = 0;
    receiver->unk78[2] = 0;
    receiver->unk78[3] = 0;
    receiver->unk7C = receiver->unk84;
    receiver->unk80 = receiver->unk84;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010B760);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010B810);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BBF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BC00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BC10);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BC50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BC90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010BCD0);

/**
 * @brief Send queued SIF commands until the queue is empty or the IOP has no room.
 * @param sif SIF link.
 */
void func_0010BD10(ResidentSif* sif)
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
s32 func_0010BDA0(ResidentSif* sif, s32 command, void* source, void* destination, s32 size, s32 in_interrupt)
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
void func_0010BE80(ResidentSif* sif, s32 command, void* source, void* destination, s32 size)
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
        func_0010BDA0(sif, command, source, destination, size, 1);
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
        func_0010BDA0(sif, command, source, destination, size, 1);
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
void func_0010BFA0(ResidentSif* sif, s32 command, void* source, void* destination, s32 size)
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
        func_0010BDA0(sif, command, source, destination, size, 0);
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
        func_0010BDA0(sif, command, source, destination, size, 0);
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C0E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C200);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C420);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C550);

/**
 * @brief Wait a moment, then try to bind the SIF link's RPC client to server 0x1234.
 * @param sif SIF link.
 * @return Zero once the server answers, minus one when binding fails.
 */
s32 func_0010C640(ResidentSif* sif)
{
    do
    {
        resident_system_set_alarm(resident_get_system(), 0x106, func_0010C6D0, (void*)GetThreadId());
        func_00114E80();

        if (sceSifBindRpc(&sif->rpc_client, 0x1234, 0) < 0)
        {
            return -1;
        }
    } while (sif->rpc_client.server == 0);

    return 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C6D0);

/**
 * @brief Set up the SIF link: carve its buffers, register its SIF command handlers and start its thread.
 * @param sif SIF link.
 */
void func_0010C700(ResidentSif* sif)
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
    sceSifAddCmdHandler(0, func_0010BCD0, 0);
    sceSifAddCmdHandler(1, func_0010BC90, 0);
    sceSifAddCmdHandler(2, func_0010BC50, 0);
    sceSifAddCmdHandler(4, func_0010BC10, 0);
    EIntr();
    sif->start();
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010C820);

/** @brief Regenerate all 55 words of the resident subtractive random table. */
static inline void refresh_random_table(void)
{
    s32 i;
    s32 j;

    for (i = 24; i > 0; --i)
    {
        D_001CF8E0[i] -= D_001CF8E0[i + 31];
    }

    for (j = 25; j <= 55; ++j)
    {
        D_001CF8E0[j] -= D_001CF8E0[j - 24];
    }
}

/**
 * @brief Advance the resident subtractive random sequence and return its next word.
 * @return Next unsigned word from the 55-element sequence.
 */
static inline u32 next_random_word(void)
{
    if (++D_001B640C > 55)
    {
        refresh_random_table();
        D_001B640C = 1;
    }

    return D_001CF8E0[D_001B640C];
}

/**
 * @brief Return a random fraction.
 * @return Random value from 0 up to 1.
 */
float func_0010C8E0(void)
{
    return next_random_word() * 2.32830671e-10f;
}

/**
 * @brief Return a random number below a limit.
 * @param limit Exclusive upper bound.
 * @return Random number from 0 to limit - 1, or 0 when limit is 0.
 */
u32 resident_random_below(u32 limit)
{
    if (limit == 0)
    {
        return 0;
    }

    return next_random_word() % limit;
}

/**
 * @brief Return a random number between two bounds.
 * @param low First bound, included.
 * @param high Second bound, excluded; it may be below low.
 * @return Random number from low up to (but not including) high, or low when the bounds are equal.
 */
s32 resident_random_range(s32 low, s32 high)
{
    s32 span;
    s32 result;

    if (high == low)
    {
        result = low;
    }
    else
    {
        span = high - low;
        span = span >= 0 ? span : -span;
        result = low + next_random_word() % span;
    }

    return result;
}

/**
 * @brief Return the next resident random number.
 * @return Random number from 0 to 0x7FFF.
 */
u32 resident_rand(void)
{
    return next_random_word() & 0x7FFF;
}

/**
 * @brief Advance the resident subtractive random sequence and return its next word.
 * @return Next unsigned word from the 55-element sequence.
 */
u32 resident_next_random_word(void)
{
    return next_random_word();
}

/**
 * @brief Seed the resident subtractive random table and warm it up.
 * @param seed Seed value.
 */
void func_0010D100(u32 seed)
{
    s32 i;
    u32 value;
    s32 index;

    D_001CF8E0[55] = seed;
    value = 1;

    for (i = 1; i <= 54; i++)
    {
        index = (21 * i) % 55;
        D_001CF8E0[index] = value;
        value = seed - value;
        seed = D_001CF8E0[index];
    }

    refresh_random_table();
    refresh_random_table();
    refresh_random_table();
    D_001B640C = 55;
}

/**
 * @brief Write a number as decimal text.
 * @param buffer Receives the text and its terminating zero.
 * @param value Number to write; negative numbers get a leading '-'.
 * @param width Number of digits to write, padded on the left with pad and losing the leading digits that don't fit;
 * zero or less writes every digit.
 * @param pad Padding character.
 * @return buffer.
 */
char* func_0010D710(char* buffer, s32 value, s32 width, char pad)
{
    char* cursor;
    char digits[12];
    char* digit;
    s32 count;
    s32 i;
    s32 j;

    cursor = buffer;

    if (value < 0)
    {
        *cursor++ = '-';
        value = -value;
    }

    if (width > 0)
    {
        cursor += width;
        *cursor = 0;
        i = 0;

        for (i = 0; i < width; i++)
        {
            *--cursor = value % 10 + '0';
            value /= 10;

            if (value == 0)
            {
                i++;
                break;
            }
        }

        while (i < width)
        {
            *--cursor = pad;
            i++;
        }
    }
    else
    {
        digit = digits + sizeof(digits);
        count = 0;

        do
        {
            *--digit = value % 10 + '0';
            count++;
            value /= 10;
        } while (value > 0);

        for (j = 0; j < count; j++)
        {
            *cursor++ = *digit++;
        }

        *cursor = 0;
    }

    return buffer;
}

/** @brief Get the resident system. @return g_system. */
ResidentSystem* resident_get_system(void)
{
    return &g_system;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010D8F0);

/**
 * @brief Put the four surround speakers back at their default angles.
 * @param sound Sound system.
 */
void resident_sound_reset_speaker_angles(ResidentSound* sound)
{
    ResidentSpeakerAngles angles = D_00144260;
    sound->speaker_angles[0] = angles.angles[0];
    sound->speaker_angles[1] = angles.angles[1];
    sound->speaker_angles[2] = angles.angles[2];
    sound->speaker_angles[3] = angles.angles[3];
}

/**
 * @brief Set the sound output mode.
 * @param sound Sound system.
 * @param mode Output mode: 1 mono, 0 stereo, 2 Dolby Pro Logic II, 3 headphones.
 */
void resident_sound_set_output_mode(ResidentSound* sound, s32 mode)
{
    sound->output_mode = mode;
    func_00108C40(sound->stream, 0, 0, 0, mode & 0xFF);
}

/**
 * @brief Ask the sound system to switch unk354 to a new value.
 * @param sound Sound system.
 * @param value New value.
 * @return Zero while the sound system is busy, otherwise one.
 */
s32 func_0010DAA0(ResidentSound* sound, s32 value)
{
    if (sound->state != 0)
    {
        return 0;
    }

    if (sound->unk354 == value)
    {
        return 1;
    }

    if (sound->effects_disabled != 0)
    {
        return 1;
    }

    sound->state = 9;
    sound->unk354 = value;
    sound->unk355 = 0;
    return 1;
}

/**
 * @brief Scale the sound volume and send it to the stream.
 * @param sound Sound system.
 * @param scale Scale, 0x7FFF for the full volume.
 */
void resident_sound_set_volume_scale(ResidentSound* sound, s32 scale)
{
    s32 volume;

    if (sound->music_disabled)
    {
        return;
    }

    volume = sound->volume * scale / 0x7FFF;

    if (volume > 0x7FFF)
    {
        volume = 0x7FFF;
    }

    if (volume < 0)
    {
        volume = 0;
    }

    sound->scaled_volume = volume;
    func_00107250(sound->stream, 0, 0, 0, sound->scaled_volume);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010DBB0);

/**
 * @brief Send stream command func_00107420 when unk30 is set and unk38 isn't minus one, then copy unk40 to unk33C.
 * @param sound Sound system.
 */
void func_0010DE90(ResidentSound* sound)
{
    if (sound->music_disabled)
    {
        return;
    }

    if (sound->music_count == 0)
    {
        return;
    }

    if (sound->unk38 == -1)
    {
        return;
    }

    func_00107420(sound->stream, 0, 0, 0);
    sound->unk33c = sound->unk40;
}

/**
 * @brief Pop the stream result stack and resend the scaled volume.
 * @param sound Sound system.
 */
void func_0010DEF0(ResidentSound* sound)
{
    if (sound->music_disabled)
    {
        return;
    }

    sound->unk350 = 0;

    if (sound->unk34 != 0)
    {
        sound->unk34--;
    }

    func_00107B60(sound->stream, 0, 0, 0, 1, 0, 0);
    func_00107250(sound->stream, 0, 0, 0, sound->scaled_volume);
}

/**
 * @brief Send stream command func_00107B60 in mode 2.
 * @param sound Sound system.
 */
void func_0010DF70(ResidentSound* sound)
{
    if (sound->music_disabled)
    {
        return;
    }

    func_00107B60(sound->stream, 0, 0, 0, 2, 0, 0);
}

/**
 * @brief Pass a value to the sound stream's func_00107D90.
 * @param value Value forwarded to the stream.
 */
void func_0010DFC0(const s32* value)
{
    func_00107D90(D_001B6410->stream, value);
}

/**
 * @brief Count the entries of the loaded sound bank.
 * @param sound Sound system.
 * @return Number of entries, or zero while no bank is loaded or it is still loading.
 */
static inline s32 bank_entry_count(ResidentSound* sound)
{
    if (sound->voice_file_key == 0)
    {
        return 0;
    }

    if (resident_find_resource_request(sound->resource_queue, 0, 0, 8, 0xFFFFFFFF, 0) != 0)
    {
        return 0;
    }

    return *(s32*)sound->voice_table;
}

/**
 * @brief Count the entries of the loaded sound bank.
 * @param sound Sound system.
 * @return Number of entries, or zero while no bank is loaded or it is still loading.
 */
s32 func_0010DFF0(ResidentSound* sound)
{
    s32 count;

    if (sound->voice_file_key == 0)
    {
        return 0;
    }

    if (resident_find_resource_request(sound->resource_queue, 0, 0, 8, 0xFFFFFFFF, 0) != 0)
    {
        count = 0;
    }
    else
    {
        count = *(s32*)sound->voice_table;
    }

    return count;
}

/**
 * @brief Read an entry of the loaded sound bank.
 * @param sound Sound system.
 * @param index Entry index.
 * @param second Receives the entry's second halfword, or zero.
 * @return The entry's first halfword, or minus one when there is no such entry.
 */
s32 func_0010E060(ResidentSound* sound, s32 index, u32* second)
{
    s32 count;
    u16* entry;
    s32 first;

    *second = 0;
    count = bank_entry_count(sound);

    if (count == 0)
    {
        return -1;
    }

    if (index >= count)
    {
        return -1;
    }

    entry = (u16*)((s32*)sound->voice_table + 1) + index * 2;
    first = entry[0];
    *second = entry[1];
    return first;
}

/**
 * @brief Load another sound bank, first releasing everything allocated from the current one.
 * @param sound Sound system.
 * @param key Resource key of the bank.
 */
void func_0010E130(ResidentSound* sound, s32 key)
{
    s32 i;

    if (sound->voice_file_key == key)
    {
        return;
    }

    for (i = 0; i < 8; i++)
    {
        if (sound->voice_buffers[i] != 0)
        {
            resident_cancel_resource_requests(g_resource_queue, sound->voice_file_key, (u32)sound->voice_buffers[i], 0,
                                              0xFFFFFFFF, 0);
            resident_queue_allocation_release(g_resident_release_queues, sound->voice_buffers[i]);
            sound->voice_buffers[i] = 0;
        }
    }

    resident_queue_resource_request(sound->resource_queue, key, sound->voice_table, 8, 0x34BC0, 0, 0x800, 0, 1);
    sound->voice_file_key = key;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E200);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_get_voice_level);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010E4B0);

/**
 * @brief Set the object positional sounds are heard from.
 * @param sound Sound system.
 * @param listener Listening object.
 * @param value Stored with the listener; its use is unknown.
 * @param range Distance positional sounds reach.
 */
void resident_sound_set_listener(ResidentSound* sound, void* listener, float value, float range)
{
    sound->listener = listener;
    sound->unk1394 = value;
    sound->range_squared = range * range;
}

/**
 * @brief Set the angle of one surround speaker.
 * @param sound Sound system.
 * @param speaker Speaker index, 0 to 3.
 * @param angle Speaker angle in radians.
 */
void resident_sound_set_speaker_angle(ResidentSound* sound, s32 speaker, float angle)
{
    sound->speaker_angles[speaker] = angle;
}

/**
 * @brief Set the angles of all four surround speakers.
 * @param sound Sound system.
 * @param angles Four speaker angles in radians.
 */
void resident_sound_set_speaker_angles(ResidentSound* sound, const float* angles)
{
    sound->speaker_angles[0] = angles[0];
    sound->speaker_angles[1] = angles[1];
    sound->speaker_angles[2] = angles[2];
    sound->speaker_angles[3] = angles[3];
}

/**
 * @brief Allocate a buffer for a resource and start loading it.
 * @param sound Sound system.
 * @param key Resource key.
 * @return One when the load started, zero while busy or when the buffer can't be allocated.
 */
s32 func_0010EAD0(ResidentSound* sound, s32 key)
{
    if (sound->state != 0)
    {
        return 0;
    }

    delete sound->unk400;
    sound->unk404 = resident_get_resource_size(sound->archive, key);
    sound->unk400 = (u8*)memalign(0x40, sound->unk404);

    if (sound->unk400 == 0)
    {
        return 0;
    }

    resident_queue_resource_request(sound->resource_queue, key, sound->unk400, 5, 0x34BC0, 0, 0, 0, 1);
    sound->state = 5;
    return 1;
}

/**
 * @brief Upload a sound file through the stream into a slot, using that slot's unk454 value.
 * @param sound Sound system.
 * @param file Sound file to upload; kept at unk360.
 * @param index Stream slot, and index into unk454.
 * @param append True to add to the slot's existing data.
 * @return Zero while the sound system is busy, otherwise one.
 */
s32 func_0010EB90(ResidentSound* sound, const void* file, s32 index, bool append)
{
    if (sound->state != 0)
    {
        return 0;
    }

    sound->unk360 = file;
    func_00106160(sound->stream, file, sound->unk454[index], index, 0, append, 0);
    sound->state = 4;
    return 1;
}

/**
 * @brief Send each entry of a setup table to the stream, waiting for each reply and keeping its first word in unk454.
 * @param sound Sound system.
 * @param count Number of entries, below 32.
 * @param entries Setup table.
 * @return One when sent, zero when count is too large.
 */
s32 func_0010EC00(ResidentSound* sound, s32 count, const ResidentSoundSetupEntry* entries)
{
    s32 i;
    u32 handle;
    u32 reply[16];

    if (count >= 32)
    {
        return 0;
    }

    for (i = 0; i < count; i++)
    {
        handle = func_00108A00(sound->stream, reply, 0, 0, i, entries[i].unk00, entries[i].unk04, entries[i].unk08,
                               entries[i].unk0C, entries[i].unk10);

        while (func_0010C0E0(&D_001CC590, handle))
        {
        }

        sound->unk454[i] = reply[0];
    }

    return 1;
}

/**
 * @brief Wake the sound stream's thread, if the sound system has a stream.
 * @param sound Sound system.
 */
void func_0010ECF0(ResidentSound* sound)
{
    ResidentSoundStream* stream = sound->stream;

    if (stream != 0)
    {
        func_001071A0(stream, 0);
    }
}

/**
 * @brief Clear the target of every active request slot aimed at an object.
 * @param sound Sound system.
 * @param target Object to forget.
 */
void func_0010ED20(ResidentSound* sound, ResidentSoundEmitter* target)
{
    s32 i;

    DIntr();

    for (i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].target == target)
        {
            sound->slots[i].target = 0;
        }
    }

    EIntr();
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010ED90);

void func_0010EE50(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010EE60);

/**
 * @brief Request callback: push the music handle at the start of a reply onto the sound system's handles.
 * @param reply Reply from the IOP.
 */
void func_0010EF50(const void* reply)
{
    ResidentSound* sound = D_001B6410;
    u32 handle = *(const u32*)reply;
    u32 index = sound->unk34;
    sound->unk34 = index + 1;
    sound->music_handles[index] = handle;
}

/**
 * @brief Request callback: push the stream's answer onto the sound system's stack.
 * @param reply Reply from the IOP.
 */
void func_0010EF80(void* reply)
{
    u32 handle = func_00107DB0(D_001B6410->stream, (const s32*)reply);

    D_001B6410->music_handles[D_001B6410->unk34++] = handle;
    D_001B6410->unk338 = handle;
    D_001B6410->unk452 = 0;
}

/**
 * @brief Ask the sound stream whether its thread's first state is set.
 * @param sound Sound system.
 * @return Nonzero when it is.
 */
s32 func_0010EFD0(ResidentSound* sound)
{
    return func_00107B10(sound->stream, 0, 0, 0, 1) != 0;
}

extern void func_0010EE60(void* response, ResidentRequestSlot* slot);
extern s32 func_00108000(void* context, s32 first, void (*callback)(void*, ResidentRequestSlot*),
                         ResidentRequestSlot* slot, s32 selected, s32 value, s32 arg3, s32 zero, u32 packed,
                         u32 placement, u32 room);
extern s32 func_00108220(void* context, s32 first,
    void (*callback)(void*, ResidentRequestSlot*), ResidentRequestSlot* slot,
    s32 selected, s32 value, s32 arg3, s32 zero, s32 packed);

/**
 * @brief Find a free sound slot, starting at the cursor and advancing it past every slot looked at.
 * @param receiver Sound system.
 * @return Free slot index, or -1 when all sixty are in use.
 */
static inline s32 find_available_request_slot(ResidentSound* receiver)
{
    s32 i;
    s32 slot;
    for (i = 0; i < 60; i++)
    {
        slot = receiver->cursor;
        if (receiver->slots[slot].active == 0)
        {
            receiver->cursor = slot + 1;
            if (slot + 1 >= 60)
            {
                receiver->cursor = 0;
            }
            return slot;
        }
        receiver->cursor = slot + 1;
        if (slot + 1 >= 60)
        {
            receiver->cursor = 0;
        }
    }
    return -1;
}

/**
 * @brief Locate a slot in the slot array.
 * @param slots Slot array.
 * @param index Valid slot index.
 * @return The slot.
 */
static inline ResidentRequestSlot* request_slot(ResidentRequestSlot* slots, s32 index)
{
    return &slots[index];
}

/**
 * @brief Stop a queued music track and remove it from the queue.
 * @param sound Sound system.
 * @param index Queue position of the track.
 * @param mode Stop mode.
 */
static inline void sound_remove_music_track(ResidentSound* sound, s32 index, s32 mode)
{
    if (sound->music_count == 0)
    {
        return;
    }

    func_00107B60(sound->stream, 0, func_0010EE50, 0, sound->music_handles[index], mode, 0);

    if (index == sound->unk38)
    {
        sound->unk38 = -1;
        sound->unk40 = 0;
    }

    if (sound->unk38 > index)
    {
        sound->unk38--;
    }

    for (s32 i = index; i < sound->music_count; i++)
    {
        sound->music_handles[i] = sound->music_handles[i + 1];
        sound->music_keys[i] = sound->music_keys[i + 1];
    }

    sound->music_count--;
    sound->unk34--;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_stop_music);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0010F250);

/**
 * @brief Send voice command 4 to a started sound.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param first First command argument.
 * @param second Second command argument.
 */
void func_00110340(ResidentSound* sound, s32 identifier, s32 first, s32 second)
{
    if (sound->effects_disabled)
    {
        return;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].started && sound->slots[i].identifier == identifier)
        {
            func_00107530(sound->stream, 0, 0, 0, sound->slots[i].handle, 4, first, second);
            return;
        }
    }
}

/**
 * @brief Send voice command 5 to a started sound.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param first First command argument.
 * @param second Second command argument.
 */
void func_001103E0(ResidentSound* sound, s32 identifier, s32 first, s32 second)
{
    if (sound->effects_disabled)
    {
        return;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].started && sound->slots[i].identifier == identifier)
        {
            func_00107530(sound->stream, 0, 0, 0, sound->slots[i].handle, 5, first, second);
            return;
        }
    }
}

/**
 * @brief Send voice command 1 to a started sound that has no target.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param first First command argument.
 * @param second Second command argument.
 */
void func_00110480(ResidentSound* sound, s32 identifier, s32 first, s32 second)
{
    if (sound->effects_disabled)
    {
        return;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].started && sound->slots[i].identifier == identifier)
        {
            if (sound->slots[i].target != 0)
            {
                return;
            }

            func_00107530(sound->stream, 0, 0, 0, sound->slots[i].handle, 1, first, second);
            return;
        }
    }
}

/**
 * @brief Send voice command 0 to a started sound, optionally recording its new volume.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param volume Volume, sent as the first command argument.
 * @param second Second command argument.
 * @param keep_volume Zero to also store volume in the slot.
 */
void func_00110520(ResidentSound* sound, s32 identifier, s32 volume, s32 second, s32 keep_volume)
{
    if (sound->effects_disabled)
    {
        return;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].started && sound->slots[i].identifier == identifier)
        {
            if (!keep_volume)
            {
                sound->slots[i].volume = volume;
            }

            if (!sound->slots[i].unk1c)
            {
                func_00107530(sound->stream, 0, 0, 0, sound->slots[i].handle, 0, volume, second);
            }

            return;
        }
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001105E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001106B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_stop);

/**
 * @brief Report whether a sound still holds its slot.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @return One while the sound's slot is in use, otherwise zero.
 */
s32 resident_sound_is_active(ResidentSound* sound, s32 identifier)
{
    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].identifier == identifier)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Free every voice read ahead of time, cancelling reads still in progress.
 * @param sound Sound system.
 */
void func_00110C60(ResidentSound* sound)
{
    for (s32 i = 0; i < 8; i++)
    {
        if (sound->voice_buffers[i] != 0)
        {
            resident_cancel_resource_requests(g_resource_queue, sound->voice_file_key, (u32)sound->voice_buffers[i], 0,
                                              -1, 0);
            resident_queue_allocation_release(g_resident_release_queues, sound->voice_buffers[i]);
            sound->voice_buffers[i] = 0;
        }
    }
}

/**
 * @brief Free one voice read ahead of time, cancelling its read if it is still in progress.
 * @param sound Sound system.
 * @param voice Index of the voice in the voice table.
 */
void func_00110CE0(ResidentSound* sound, s32 voice)
{
    for (s32 i = 0; i < 8; i++)
    {
        if (sound->voice_buffers[i] != 0 && sound->voice_indices[i] == voice)
        {
            resident_cancel_resource_requests(g_resource_queue, sound->voice_file_key, (u32)sound->voice_buffers[i], 0,
                                              -1, 0);
            resident_queue_allocation_release(g_resident_release_queues, sound->voice_buffers[i]);
            sound->voice_buffers[i] = 0;
        }
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110D80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00110FB0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111420);

/**
 * @brief Play sound data already in memory from an object, in a free slot.
 * @param sound Sound system.
 * @param buffer Sound data.
 * @param emitter Object the sound comes from.
 * @param value Stored in the slot; its use is unknown.
 * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
 * @param low Value packed into the lower 16 bits.
 * @param owns_buffer Nonzero to delete buffer once the sound stops, or now when effects are disabled.
 * @return Slot identifier, one when effects are disabled, or -1 when no slot is free.
 */
s32 func_00111860(ResidentSound* sound, u8* buffer, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low,
                  s32 owns_buffer)
{
    if (sound->effects_disabled)
    {
        if (owns_buffer)
        {
            delete buffer;
        }

        return 1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    sound->slots[slot].buffer = buffer;
    float position[4];
    func_4DA730(emitter, position);
    emitter->has_sound = 1;
    u32 placement = func_0010E4B0(sound, position, 0, 0);
    sound->slots[slot].unk28 = 0;
    sound->slots[slot].active = 1;
    sound->slots[slot].started = 0;
    sound->slots[slot].stop_requested = 0;
    sound->slots[slot].unk03 = 1;
    sound->slots[slot].owns_buffer = owns_buffer;
    sound->slots[slot].identifier = sound->next_identifier;
    sound->slots[slot].target = emitter;
    sound->slots[slot].unk30 = 0;
    sound->slots[slot].selector = 0;
    sound->slots[slot].value = 0;
    sound->slots[slot].volume = volume;
    sound->slots[slot].unk1c = 0;
    sound->slots[slot].unk2c = value;
    sound->slots[slot].unk34 = (u32)volume << 24 | ((u32)low & 0xFFFF);
    sound->slots[slot].unk38 = placement;
    sound->slots[slot].unk06[0] = sound->unk451;
    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return sound->slots[slot].identifier;
}

/**
 * @brief Play sound data already in memory, in a free slot.
 * @param sound Sound system.
 * @param buffer Sound data.
 * @param value Stored in the slot; its use is unknown.
 * @param volume Volume, 0x7F for full; packed into the upper byte.
 * @param pan Pan, 0x40 for centre; packed into the next byte.
 * @param low Value packed into the lower 16 bits.
 * @param owns_buffer Nonzero to delete buffer once the sound stops, or now when effects are disabled.
 * @return Slot identifier, one when effects are disabled, or -1 when no slot is free.
 */
s32 func_00111A90(ResidentSound* sound, u8* buffer, s32 value, s32 volume, s32 pan, s32 low, s32 owns_buffer)
{
    if (sound->effects_disabled)
    {
        if (owns_buffer)
        {
            delete buffer;
        }

        return 1;
    }

    if (sound->state == 9)
    {
        return -1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    sound->slots[slot].buffer = buffer;
    sound->slots[slot].unk28 = 0;
    sound->slots[slot].active = 1;
    sound->slots[slot].started = 0;
    sound->slots[slot].stop_requested = 0;
    sound->slots[slot].unk03 = 1;
    sound->slots[slot].owns_buffer = owns_buffer;
    sound->slots[slot].identifier = sound->next_identifier;
    sound->slots[slot].target = 0;
    sound->slots[slot].unk30 = 0;
    sound->slots[slot].selector = 0;
    sound->slots[slot].value = 0;
    sound->slots[slot].unk2c = value;
    sound->slots[slot].unk34 = ((u32)low & 0xFFFF) | ((u32)volume << 24 | (u32)pan << 16);
    sound->slots[slot].unk38 = 0;
    sound->slots[slot].unk06[0] = 0;
    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return sound->slots[slot].identifier;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_play_voice);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00111EF0);

/**
 * @brief Play a sound effect from an object in a free slot.
 * @param sound Sound system.
 * @param number Sound number; its low 16 bits are stored.
 * @param emitter Object the sound comes from.
 * @param selector Request selector.
 * @param value Value forwarded to request dispatch.
 * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
 * @param low Value packed into the lower 16 bits.
 * @return Slot identifier, zero on dispatch failure, one when effects are disabled, or -1 without an emitter or a free
 *         slot.
 */
s32 func_00112160(ResidentSound* sound, s32 number, ResidentSoundEmitter* emitter, s32 selector, s32 value, s32 volume,
                  s32 low)
{
    if (sound->effects_disabled)
    {
        return 1;
    }

    if (sound->state == 9)
    {
        return -1;
    }

    if (emitter == 0)
    {
        return -1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    float position[4];
    func_4DA730(emitter, position);
    emitter->has_sound = 1;
    u32 placement = func_0010E4B0(sound, position, 0, 0);
    ResidentRequestSlot* const request = request_slot(sound->slots, slot);
    request->buffer = 0;
    request->unk28 = 0;
    request->active = 1;
    request->started = 0;
    request->stop_requested = 0;
    request->owns_buffer = 0;
    request->unk03 = 0;
    s32* identifier = &sound->slots[slot].identifier;
    *identifier = sound->next_identifier;
    request->target = emitter;
    request->unk30 = 0;
    request->selector = selector;
    request->value = number;
    request->unk38 = placement;
    request->volume = volume;
    request->unk1c = 0;

    if (!func_00108000(sound->stream, 0, func_0010EE60, request, sound->unk454[selector], number, value, 0,
                       (u32)volume << 24 | ((u32)low & 0xFFFF), placement, sound->unk451))
    {
        request->active = 0;
        return 0;
    }

    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return *identifier;
}


/**
 * @brief Play a sound effect in a free slot.
 * @param sound Sound system.
 * @param number Sound number; its low 16 bits are stored.
 * @param selector Request selector.
 * @param value Value forwarded to request dispatch.
 * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
 * @param pan Pan, 0x40 for centre; packed into the next byte.
 * @param low Value packed into the lower 16 bits.
 * @return Slot identifier, zero on dispatch failure, one when effects are disabled, or -1 when no slot is free.
 */
s32 resident_sound_play(ResidentSound* sound, s32 number, s32 selector, s32 value, s32 volume, s32 pan, s32 low)
{
    s32 slot;
    s32 i;

    if (sound->effects_disabled)
    {
        return 1;
    }

    if (sound->state == 9)
    {
        return -1;
    }

    slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    ResidentRequestSlot* const request = request_slot(sound->slots, slot);
    s32* identifier;
    request->buffer = 0;
    request->unk28 = 0;
    request->active = 1;
    request->started = 0;
    request->stop_requested = 0;
    request->owns_buffer = 0;
    request->unk03 = 0;
    identifier = &sound->slots[slot].identifier;
    *identifier = sound->next_identifier;
    request->target = 0;
    request->unk30 = 0;
    request->selector = selector;
    request->value = number;
    request->volume = volume;
    request->unk1c = 0;

    if (!func_00108220(sound->stream, 0, func_0010EE60, request, sound->unk454[selector], number, value, 0,
                       ((u32)low & 0xFFFF) | (((u32)volume << 24) | ((u32)pan << 16))))
    {
        request->active = 0;
        return 0;
    }

    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return *identifier;
}


/**
 * @brief Report whether music is playing.
 * @param sound Sound system.
 * @param key Music to check for, or -1 for any.
 * @return Nonzero while that music plays, or always when music is disabled.
 */
s32 resident_sound_is_music_playing(ResidentSound* sound, s32 key)
{
    if (sound->music_disabled)
    {
        return 1;
    }

    if (sound->music_count == 0)
    {
        return 0;
    }

    func_0010F250(sound, 0);

    if (key == -1)
    {
        return 1;
    }

    for (s32 i = 0; i < sound->music_count; i++)
    {
        if (sound->music_keys[i] == key)
        {
            return 1;
        }
    }

    return 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_load_bank);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_sound_play_music);

/**
 * @brief Set the table of music the sound system plays.
 * @param sound Sound system.
 * @param count Number of entries.
 * @param entries Music entries, by music number minus one.
 */
void func_00112D70(ResidentSound* sound, s32 count, const ResidentMusicEntry* entries)
{
    sound->music_entry_count = count;
    sound->music_entries = entries;
}

/**
 * @brief Start the sound system and its stream.
 * @param sound Sound system.
 */
void func_00112D80(ResidentSound* sound)
{
    sound->stream = func_00101280(resident_get_system());
    sound->archive = resident_get_archive(resident_get_system());
    sound->resource_queue = func_00101250(resident_get_system());
    s32 request = func_00109000(sound->stream, 0, 0, 0, 0x18000, 0x3000, 0x1000, 3, 1);

    while (func_0010C0E0(&D_001CC590, request))
    {
    }

    func_00108E10(sound->stream);
    func_00108C40(sound->stream, 0, 0, 0, sound->output_mode);
    func_00107250(sound->stream, 0, 0, 0, sound->volume);
    sound->unk350 = 0;
    sound->unk452 = 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112E70);

/** @brief Remove the sound interrupt handler and free the sound buffers. */
ResidentSound::~ResidentSound()
{
    DisableIntc(INTC_VBLANK_END);
    RemoveIntcHandler(INTC_VBLANK_END, interrupt_handler);
    delete[] unk400;
    delete[] (u8*)voice_table;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00112FE0);

void func_00113180(void* object)
{
}

/**
 * @brief Measure a heap and its fallback heaps.
 * @param heap Heap to measure.
 * @param free_bytes Receives the total size of the free blocks.
 * @param used_bytes Receives the total size of the allocated blocks.
 * @return Largest allocation that would fit in one free block.
 */
s32 func_00113190(ResidentHeap* heap, s32* free_bytes, s32* used_bytes)
{
    s32 largest = 0;

    *used_bytes = 0;
    *free_bytes = 0;

    for (ResidentHeapBlock* block = heap->free_anchor->physical_previous; block != heap->free_anchor;
         block = block->physical_previous)
    {
        if (block->allocated)
        {
            *used_bytes += block->size;
        }
        else
        {
            *free_bytes += block->size;

            if (block->size > largest)
            {
                largest = block->size;
            }
        }
    }

    largest -= 0x10;

    if (largest < 0)
    {
        largest = 0;
    }

    if (heap->use_fallbacks)
    {
        for (s32 i = 0; i < heap->fallback_count; i++)
        {
            if (heap->fallbacks[i])
            {
                s32 fallback_free;
                s32 fallback_used;
                s32 fallback_largest = func_00113190(heap->fallbacks[i], &fallback_free, &fallback_used);

                if (fallback_largest > largest)
                {
                    largest = fallback_largest;
                }

                *free_bytes += fallback_free;
                *used_bytes += fallback_used;
            }
        }
    }

    return largest;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_heap_resize);

/**
 * @brief Return a block to its heap, merging it with free neighbours and relinking the free list.
 * @param memory Allocation to release.
 */
void resident_heap_release(void* memory)
{
    ResidentHeapBlock* block = (ResidentHeapBlock*)((u8*)memory - 0x20);
    ResidentHeapBlock* previous_free = block->owner->free_anchor;
    ResidentHeapBlock* next_free;
    if (!block->physical_next->allocated)
    {
        previous_free = block->physical_next->free_previous;
        block->physical_previous->physical_next = block->physical_next;
        block->physical_next->physical_previous = block->physical_previous;
        block->physical_next->size += block->size;
        block = block->physical_next;
        next_free = block->free_next;
    }
    else
    {
        if (block->physical_previous->allocated)
        {
            next_free = previous_free->free_next;
            while ((u32)next_free < (u32)block && next_free != previous_free)
            {
                next_free = next_free->free_next;
            }
            previous_free = next_free->free_previous;
        }
        else
        {
            previous_free = block->physical_previous->free_previous;
        }
    }
    if (!block->physical_previous->allocated)
    {
        next_free = block->physical_previous->free_next;
        block->physical_previous->physical_previous->physical_next = block;
        block->size += block->physical_previous->size;
        block->physical_previous = block->physical_previous->physical_previous;
    }
    block->free_previous = previous_free;
    block->free_next = next_free;
    next_free->free_previous = block;
    previous_free->free_next = block;
    block->allocated = 0;
}

/**
 * @brief Allocate from the top of a heap's free blocks, trying its child heaps first.
 * @param heap Heap.
 * @param size Requested payload size in bytes.
 * @return Allocation, or null when no block is available.
 */
void* func_001135B0(ResidentHeap* heap, s32 size)
{
    if (heap->use_fallbacks)
    {
        for (s32 i = heap->fallback_count - 1; i >= 0; i--)
        {
            if (heap->fallbacks[i])
            {
                void* memory = func_001135B0(heap->fallbacks[i], size);

                if (memory)
                {
                    return memory;
                }
            }
        }
    }

    ResidentHeapBlock* block;
    s32 rounded;
    s32 alignment;
    ResidentHeapBlock* anchor;

    anchor = heap->free_anchor;
    alignment = heap->alignment;
    rounded = -alignment & (size + 0x1F + alignment);

    for (block = anchor->free_previous; block != anchor; block = block->free_previous)
    {
        if (block->size >= rounded && block->size - rounded > alignment + 0x20)
        {
            ResidentHeapBlock* taken = (ResidentHeapBlock*)((u8*)block + block->size - rounded);
            taken->size = rounded;
            taken->allocated = 1;
            taken->tag = RESIDENT_HEAP_BLOCK_TAG;
            taken->marker = RESIDENT_HEAP_BLOCK_MARKER;
            taken->owner = heap;
            block->physical_previous->physical_next = taken;
            taken->physical_previous = block->physical_previous;
            block->physical_previous = taken;
            taken->physical_next = block;
            block->size -= rounded;
            block->allocated = 0;
            block->tag = 0;
            block->marker = 0;
            return taken + 1;
        }
    }

    return 0;
}


/**
 * @brief Allocate from a heap, splitting a free block when there is room, then trying its child heaps.
 * @param receiver Heap.
 * @param size Requested payload size in bytes.
 * @return Allocation, or null when no block is available.
 */
void* resident_heap_allocate(void* receiver, s32 size)
{
    ResidentHeap* heap = (ResidentHeap*)receiver;
    ResidentHeapBlock* block;
    s32 rounded;
    s32 alignment;
    ResidentHeapBlock* anchor;
    if (heap->alternate)
    {
        return func_001135B0(heap, size);
    }
    alignment = heap->alignment;
    anchor = heap->free_anchor;
    rounded = -alignment & (size + 0x1F + alignment);
    for (block = anchor->free_next; block != anchor; block = block->free_next)
    {
        if (block->size >= rounded)
        {
            ResidentHeapBlock* rest = (ResidentHeapBlock*)((u8*)block + rounded);
            s32 remaining = block->size - rounded;
            if (remaining > alignment + 0x20)
            {
                rest->size = remaining;
                rest->allocated = 0;
                rest->free_previous = block->free_previous;
                rest->free_next = block->free_next;
                block->free_previous->free_next = rest;
                block->free_next->free_previous = rest;
                block->physical_previous->physical_next = rest;
                rest->physical_previous = block->physical_previous;
                block->physical_previous = rest;
                rest->physical_next = block;
                block->size = rounded;
            }
            else
            {
                block->free_previous->free_next = block->free_next;
                block->free_next->free_previous = block->free_previous;
            }
            block->tag = RESIDENT_HEAP_BLOCK_TAG;
            block->marker = RESIDENT_HEAP_BLOCK_MARKER;
            block->owner = heap;
            block->allocated = 1;
            return block + 1;
        }
    }
    if (heap->use_fallbacks)
    {
        s32 count = heap->fallback_count;
        s32 i;
        for (i = 0; i < count; i++)
        {
            if (heap->fallbacks[i])
            {
                void* memory = resident_heap_allocate(heap->fallbacks[i], size);
                if (memory)
                {
                    return memory;
                }
            }
        }
    }
    return 0;
}

/**
 * @brief Give a heap a memory range to allocate from.
 * @param heap Heap.
 * @param address Start of the range, or null.
 * @param size Size of the range in bytes.
 * @return Nonzero on success, zero for a null range.
 */
u32 func_001138B0(ResidentHeap* heap, void* address, u32 size)
{
    ResidentHeapBlock* block = (ResidentHeapBlock*)address;

    heap->free_anchor = &heap->head;

    if (address == 0)
    {
        return 0;
    }

    heap->alternate = 0;
    heap->free_anchor->size = 4;
    heap->free_anchor->allocated = 1;
    heap->free_anchor->physical_next = block;
    heap->free_anchor->physical_previous = block;
    heap->free_anchor->free_previous = block;
    heap->free_anchor->free_next = block;
    block->size = size;
    block->allocated = 0;
    block->physical_previous = block->physical_next = heap->free_anchor;
    block->free_previous = block->free_next = heap->free_anchor;
    return 1;
}

/**
 * @brief Give a heap memory of its own.
 * @param heap Heap.
 * @param size Usable size in bytes.
 * @return Nonzero on success, zero when the memory can't be allocated.
 */
u32 func_00113930(ResidentHeap* heap, u32 size)
{
    heap->free_anchor = &heap->head;
    heap->memory = malloc_guess(size + heap->alignment + 0x20);

    if (heap->memory == 0)
    {
        return 0;
    }

    u32 payload = (u32)((ResidentHeapBlock*)heap->memory + 1);
    ResidentHeapBlock* block = (ResidentHeapBlock*)((payload + heap->alignment - 1) & -heap->alignment) - 1;
    heap->alternate = 0;
    heap->free_anchor->size = 4;
    heap->free_anchor->allocated = 1;
    heap->free_anchor->physical_next = block;
    heap->free_anchor->physical_previous = block;
    heap->free_anchor->free_previous = block;
    heap->free_anchor->free_next = block;
    block->size = size;
    block->allocated = 0;
    block->physical_previous = block->physical_next = heap->free_anchor;
    block->free_previous = block->free_next = heap->free_anchor;
    return 1;
}

/**
 * @brief Delete a heap's child heaps.
 * @param heap Heap.
 */
void func_00113A10(ResidentHeap* heap)
{
    for (s32 i = 0; i < heap->fallback_count; i++)
    {
        if (heap->fallbacks[i])
        {
            delete heap->fallbacks[i];
            heap->fallbacks[i] = 0;
        }
    }

    heap->fallback_count = 0;
}

/** @brief Construct an empty heap with no memory, 16-byte alignment and child heaps enabled. */
inline ResidentHeap::ResidentHeap()
{
    alternate = 0;
    free_anchor = 0;
    alignment = 16;
    memory = 0;

    for (s32 i = 0; i < 8; i++)
    {
        fallbacks[i] = 0;
    }

    fallback_count = 0;
    use_fallbacks = 1;
}

/**
 * @brief Give a heap a memory range to allocate from.
 * @param heap Heap.
 * @param address Start of the range, or null.
 * @param size Size of the range in bytes.
 * @return True on success, false for a null range.
 */
static inline bool heap_set_memory(ResidentHeap* heap, void* address, u32 size)
{
    ResidentHeapBlock* block = (ResidentHeapBlock*)address;

    heap->free_anchor = &heap->head;

    if (address == 0)
    {
        return false;
    }

    heap->alternate = 0;
    heap->free_anchor->size = 4;
    heap->free_anchor->allocated = 1;
    heap->free_anchor->physical_next = block;
    heap->free_anchor->physical_previous = block;
    heap->free_anchor->free_previous = block;
    heap->free_anchor->free_next = block;
    block->size = size;
    block->allocated = 0;
    block->physical_previous = block->physical_next = heap->free_anchor;
    block->free_previous = block->free_next = heap->free_anchor;
    return true;
}

/**
 * @brief Add a child heap over a memory range.
 * @param heap Parent heap.
 * @param address Start of the child's range.
 * @param size Size of the child's range in bytes.
 * @return Nonzero when the child was added, zero when the parent is full or the child can't be made.
 */
u32 func_00113AB0(ResidentHeap* heap, void* address, u32 size)
{
    if (heap->fallback_count >= 8)
    {
        return 0;
    }

    ResidentHeap* child = new (0) ResidentHeap;
    child->alignment = heap->alignment;

    if (child == 0)
    {
        return 0;
    }

    if (!heap_set_memory(child, address, size))
    {
        delete child;
        return 0;
    }

    heap->fallbacks[heap->fallback_count++] = child;
    return 1;
}

/**
 * @brief Add a child heap with memory of its own.
 * @param heap Parent heap.
 * @param size Usable size of the child in bytes.
 * @return Nonzero when the child was added, zero when the parent is full or the child can't be made.
 */
u32 func_00113C40(ResidentHeap* heap, u32 size)
{
    if (heap->fallback_count >= 8)
    {
        return 0;
    }

    ResidentHeap* child = new (0) ResidentHeap;
    child->alignment = heap->alignment;

    if (child == 0)
    {
        return 0;
    }

    if (!func_00113930(child, size))
    {
        delete child;
        return 0;
    }

    heap->fallbacks[heap->fallback_count++] = child;
    return 1;
}

/** @brief Release heap storage and child heaps. */
ResidentHeap::~ResidentHeap()
{
    if (memory)
    {
        free_guess(memory);
    }

    for (s32 i = 0; i < fallback_count; i++)
    {
        if (fallbacks[i])
        {
            delete fallbacks[i];
            fallbacks[i] = 0;
        }
    }

    fallback_count = 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113E40);

void func_00113EA0(void* object)
{
}

typedef struct ResidentPolledFlag13EB0
{
    u8 pad00[0x1011];
    volatile u8 flag;
} ResidentPolledFlag13EB0;

/** Return the state byte or wait for it to clear when requested. */
u32 func_00113EB0(void* object, s32 wait)
{
    ResidentPolledFlag13EB0* state = (ResidentPolledFlag13EB0*)object;
    if (wait != 0) {
        return state->flag;
    }
    while (state->flag != 0) {
    }
    return 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113EF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00113FD0);

/** Store 0x1 at receiver offset 0x1012. */
void func_001140F0(void* object)
{
    ConstantByteSetterOwnerresident_0010A0E0* receiver = (ConstantByteSetterOwnerresident_0010A0E0*)object;
    receiver->unk1012 = 0x1;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114100);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001142C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114330);

s32 func_001143E0(double left, double right)
{
    return func_00135320(left, right) > 0;
}

s32 func_00114400(double left, double right)
{
    return func_00135320(left, right) < 0;
}

s32 func_00114420(double left, double right)
{
    return func_00135320(left, right) == 0;
}

void func_00114450(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114460);

/**
 * @brief Set a time-sliced thread's slice and create it at the normal resident priority.
 * @param thread Thread.
 * @param time_slice Horizontal syncs per slice.
 * @param stack_size Stack size in bytes.
 * @return Nonzero when the thread was created.
 */
s32 func_00114560(ResidentTimeSlicedThread* thread, s16 time_slice, s32 stack_size)
{
    thread->time_slice = time_slice;
    return func_00115000(thread, RESIDENT_THREAD_PRIORITY, stack_size);
}


INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114580);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114650);

/**
 * @brief Stop handing out time slices, returning the running thread to the normal priority.
 * @param scheduler Scheduler.
 */
void func_00114720(ResidentThreadScheduler* scheduler)
{
    if (scheduler->active)
    {
        if (scheduler->current)
        {
            if (scheduler->alarm_id >= 0)
            {
                iReleaseAlarm(scheduler->alarm_id);
                scheduler->alarm_id = -1;
            }

            iChangeThreadPriority(scheduler->current->thread_id, RESIDENT_THREAD_PRIORITY);
            scheduler->current = 0;
        }

        scheduler->active = 0;
    }
}

static inline bool scheduler_slot_empty(ResidentThreadScheduler* scheduler, s32 index)
{
    if (scheduler->threads[index])
    {
        return false;
    }

    return true;
}

/**
 * @brief End the running time slice and give the next thread its slice, from interrupt context.
 * @param scheduler Scheduler.
 */
void func_00114790(ResidentThreadScheduler* scheduler)
{
    scheduler->alarm_id = -1;

    if (scheduler->current)
    {
        iChangeThreadPriority(scheduler->current->thread_id, RESIDENT_THREAD_PRIORITY);
        scheduler->current = 0;
    }

    do
    {
        if (!scheduler_slot_empty(scheduler, scheduler->next))
        {
            scheduler->current = scheduler->threads[scheduler->next];
            iChangeThreadPriority(scheduler->current->thread_id, RESIDENT_THREAD_SLICE_PRIORITY);
            scheduler->next++;
            scheduler->alarm_id = resident_system_iset_alarm(&g_system, scheduler->current->time_slice,
                                                             func_00114870, scheduler);
            return;
        }

        scheduler->next++;
    } while (scheduler->next < 8);

    scheduler->active = 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114870);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001148B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114A00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114BD0);

/** Return whether waking the resident thread succeeds. */
s32 func_00114DD0(const void* object)
{
    const ResidentThreadHandle114DD0* receiver = (const ResidentThreadHandle114DD0*)object;
    return iWakeupThread(receiver->unk08) >= 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00114E00);

/** Return whether the resident thread sleep request succeeds. */
s32 func_00114E80(void)
{
    return SleepThread() >= 0;
}

/** Return whether the resident thread starts successfully. */
s32 func_00114EB0(void* object)
{
    ResidentThreadStartContext14EB0* receiver = (ResidentThreadStartContext14EB0*)object;
    return StartThread(receiver->unk08, object) >= 0;
}

// TODO: This only matches at optimization level 0. It homes its argument and leaves its delay slots empty, so I
// think the original turned the optimizer off here, maybe to keep the thread entry easy to step through.
#pragma push
#pragma optimization_level 0

/**
 * @brief Entry point of every resident thread: run the thread's body, then delete the thread.
 * @param argument The thread.
 */
void func_00114EE0(void* argument)
{
    ResidentThread* thread = (ResidentThread*)argument;
    thread->run();
    delete thread;
}

#pragma pop

/** @brief Stop and delete the kernel thread. */
ResidentThread::~ResidentThread()
{
    s32 id = thread_id;

    if (id >= 0)
    {
        if (id == GetThreadId())
        {
            delete stack;
            ExitDeleteThread();
        }
        else
        {
            TerminateThread(id);
            DeleteThread(thread_id);
            delete stack;
        }
    }
}

/**
 * @brief Create the kernel thread with a new stack; it runs the thread's body once started.
 * @param thread Thread.
 * @param priority Thread priority.
 * @param stack_size Stack size in bytes.
 * @return Nonzero when the thread was created, zero when it already exists or creation failed.
 */
s32 func_00115000(ResidentThread* thread, s32 priority, s32 stack_size)
{
    if (thread->thread_id >= 0)
    {
        return 0;
    }

    thread->stack = new (0) u8[stack_size];

    if (thread->stack == 0)
    {
        return 0;
    }

    FlushCache(0);
    ThreadParam param;
    param.entry = func_00114EE0;
    param.stack = thread->stack;
    param.stackSize = stack_size;
    param.gpReg = &_gp;
    param.initPriority = priority;
    thread->priority = priority;
    thread->thread_id = CreateThread(&param);
    return thread->thread_id >= 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001150C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001151B0);

/**
 * @brief Report whether a resource exists in the decrypted resource table.
 * @param archive Resource archive.
 * @param index Resource index, counted from the sixth entry.
 * @return One when the resource has a size, zero when it is empty, or two when the table isn't decrypted.
 */
s32 func_00115270(const ResidentArchive* archive, s32 index)
{
    if (archive->table_tag != RESIDENT_ARCHIVE_TABLE_TAG)
    {
        return 2;
    }

    if ((archive->resource_entries[index + 5] & 0x00FFFFFF) << 11)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Set the three BB Navigator files the install writes.
 * @param archive Resource archive.
 * @param first First file.
 * @param first_size Size of first.
 * @param second Second file.
 * @param second_size Size of second.
 * @param third Third file.
 * @param third_size Size of third.
 */
void resident_archive_set_navigator_files(ResidentArchive* archive, u8* first, s32 first_size, u8* second, s32 second_size, u8* third,
                                          s32 third_size)
{
    archive->navigator_files[0] = first;
    archive->navigator_file_sizes[0] = first_size;
    archive->navigator_files[1] = second;
    archive->navigator_file_sizes[1] = second_size;
    archive->navigator_files[2] = third;
    archive->navigator_file_sizes[2] = third_size;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_set_system_files);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00115310);

/**
 * @brief Clear the pending hard disk unit error.
 * @param archive Resource archive.
 */
void resident_archive_clear_unit_error(ResidentArchive* archive)
{
    archive->unk140 = 0;
    archive->unk6c = 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_has_unit_error);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_query_unit);

/**
 * @brief Get the result of the last worker command.
 * @param archive Resource archive.
 * @return Zero on success, otherwise an error.
 */
s32 resident_archive_get_command_result(const ResidentArchive* archive)
{
    return archive->command_result;
}

/**
 * @brief Report whether a worker command is running.
 * @param archive Resource archive.
 * @return Nonzero while a command runs.
 */
s32 resident_archive_is_busy(const ResidentArchive* archive)
{
    return archive->busy;
}

/**
 * @brief Get the words the install still has to copy.
 * @param archive Resource archive.
 * @return Remaining words.
 */
s32 resident_archive_get_copy_remaining(const ResidentArchive* archive)
{
    return archive->copy_remaining;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_is_unit_ready);

/**
 * @brief Set the buffer the install copies through.
 * @param archive Resource archive.
 * @param buffer Copy buffer, or null once the copy is done.
 */
void resident_archive_set_copy_buffer(ResidentArchive* archive, u8* buffer)
{
    archive->copy_buffer = buffer;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_cancel_command);

/**
 * @brief Queue a command for the hard disk worker.
 * @param archive Resource archive.
 * @param command Worker command.
 * @param argument Command argument.
 */
void resident_archive_start_command(ResidentArchive* archive, s32 command, s32 argument)
{
    func_00118880(archive->unkEC, command, argument);
}

/**
 * @brief Get the free space the last space query found.
 * @param archive Resource archive.
 * @return Free space in bytes.
 */
u32 resident_archive_get_free_space(const ResidentArchive* archive)
{
    return archive->free_space;
}

/**
 * @brief Get the space the install needs, rounded up to 256 KiB.
 * @param archive Resource archive.
 * @return Needed space in bytes.
 */
u32 resident_archive_get_install_size(const ResidentArchive* archive)
{
    u32 total = 0;

    for (s32 i = 0; i < 0x1800; i++)
    {
        if (archive->install_flags[i] != 0)
        {
            total += archive->resource_entries[i];
        }
    }

    s32 size = total * 4 + RESIDENT_INSTALL_HEADER_SIZE;

    return (size + RESIDENT_INSTALL_ALIGNMENT - 1) & ~(RESIDENT_INSTALL_ALIGNMENT - 1);
}

/**
 * @brief Sum the entries of every resource the install copies.
 * @param archive Resource archive.
 * @return Install size in words.
 */
s32 resident_archive_get_install_words(const ResidentArchive* archive)
{
    u32 total = 0;

    for (s32 i = 0; i < 0x1800; i++)
    {
        if (archive->install_flags[i] != 0)
        {
            total += archive->resource_entries[i];
        }
    }

    return total;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_001158E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118880);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118A70);

void func_00118B80(void* object, void* value)
{
    func_00114E00(value);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118BA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00118C70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_00119650);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011B5C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011B6A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011B870);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011BA90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011BC80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011BE20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011BFD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C120);

void func_0011C6B0(void* object)
{
}

/**
 * @brief Get the position of a resource in the archive.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return Position in 2048-byte blocks.
 */
u32 func_0011C6C0(const ResidentArchive* archive, s32 key)
{
    return archive->resource_positions[key] & 0x00FFFFFF;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C6E0);

/** Return bit 0 of the word at receiver offset 0xCC. */
s32 func_0011C7C0(const void* object)
{
    const u32* values = (const u32*)object;
    return (values[0x33] & 1) != 0;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C7D0);

/**
 * @brief Get the size of a resource, in whole 2048-byte blocks.
 * @param archive Resource archive.
 * @param key Resource key.
 * @return Resource size in bytes.
 */
u32 resident_get_resource_size(const ResidentArchive* archive, s32 key)
{
    return (archive->resource_entries[key] & 0x00FFFFFF) << 11;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011C8E0);

/**
 * @brief Read a resource and wait for the read to finish, retrying until it starts.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param key Resource key.
 * @param size Bytes to read, or zero for the whole resource.
 * @return One.
 */
s32 func_0011CA60(ResidentArchive* archive, void* buffer, s32 key, s32 size)
{
    do
    {
        while (!func_0011D080(archive, key))
        {
        }
    } while (!func_0011CC00(archive, buffer, size));

    while (archive->read_busy)
    {
    }

    return 1;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011CB00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011CC00);

/**
 * @brief Start reading the selected resource without checking the result.
 * @param archive Resource archive.
 * @param buffer Destination.
 * @param size Bytes to read, or zero for the whole resource.
 */
void func_0011D060(ResidentArchive* archive, void* buffer, s32 size)
{
    func_0011CC00(archive, buffer, size);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D080);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011D320);

/**
 * @brief Read and decrypt the archive's table of contents.
 * @param archive Resource archive.
 * @return One once the table is loaded, or zero while another read is running.
 */
s32 func_0011D470(ResidentArchive* archive)
{
    if (archive->read_busy)
    {
        return 0;
    }

    sceCdDiskReady(0);
    archive->resource_positions[0] = RESIDENT_ARCHIVE_TOC_POSITION;
    func_0011D080(archive, 0);

    u32* buffer = new (0) u32[RESIDENT_ARCHIVE_TOC_WORDS];
    func_0011CC00(archive, buffer, RESIDENT_ARCHIVE_TOC_WORDS * sizeof(u32));

    while (archive->read_busy)
    {
    }

    u32* toc = archive->resource_positions;
    u32* source = buffer;

    for (s32 i = 0; i < RESIDENT_ARCHIVE_TOC_WORDS; i++)
    {
        *toc++ = *source++;
    }

    delete buffer;

    u32 key = RESIDENT_ARCHIVE_TOC_KEY;

    for (s32 i = 0; i < RESIDENT_RESOURCE_COUNT; i++)
    {
        archive->resource_positions[i] ^= key;
        key ^= key << 1;
        archive->resource_entries[i] ^= key;
        key = ~key ^ RESIDENT_ARCHIVE_TOC_KEY;
        archive->install_flags[i] ^= key;
        key ^= (key << 2) ^ RESIDENT_ARCHIVE_TOC_KEY;
    }

    archive->table_tag = archive->resource_positions[0];
    archive->resource_positions[0] = RESIDENT_ARCHIVE_TOC_POSITION;
    return 1;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", __dt__15ResidentArchiveFv);

/**
 * @brief Install the disc power-off callback and start the hard disk worker, when the archive uses the hard disk.
 * @param archive Resource archive.
 */
void func_0011D950(ResidentArchive* archive)
{
    if (archive->unk12184)
    {
        sceCdPOffCallback(D_00118C50, archive->unkD8);
        archive->disk_worker()->start();
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", resident_archive_get_clock);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DA80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DBA0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DC00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DD40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", __dt__19ResidentClass14FC60Fv);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011DE00);

/**
 * @brief Attach the display whose field the vblank handler updates.
 * @param input Input system.
 * @param display Display to update each vblank, or null.
 * @param enabled Nonzero to update the display each vblank.
 */
void resident_input_attach_display(ResidentInputSystem* input, void* display, u8 enabled)
{
    ResidentDisplay* attached = static_cast<ResidentDisplay*>(display);

    input->display_enabled = enabled;
    input->display = attached;

    if (attached != 0)
    {
        attached->vblank_enabled = enabled;
    }
}

/**
 * @brief Take the number of vblanks counted since the last call.
 * @param input Input system.
 * @return Vblanks since the last call.
 */
s32 resident_input_take_vblank_count(ResidentInputSystem* input)
{
    u32 count = input->vblank_count;
    input->vblank_count = 0;
    return count;
}

/**
 * @brief Wait for the next vblank and return the GS field it recorded.
 * @param input Input system.
 * @param mode Minus one reads the field without waiting; other values wait.
 * @return Display field, zero or one.
 */
u32 func_0011DF10(ResidentInputSystem* input, s32 mode)
{
    D_001B641C = 0;

    if (mode == -1)
    {
        return input->field;
    }

    input->vblank_wait_count = 0;

    while (!input->vblank_wait_count)
    {
    }

    return input->field;
}

/**
 * @brief Set the seconds clock the vblank handler counts.
 * @param input Input system.
 * @param seconds New clock value.
 */
void func_0011DF60(ResidentInputSystem* input, u32 seconds)
{
    input->seconds = seconds;
    input->second_vblanks = 0;
}

/**
 * @brief Get the seconds clock the vblank handler counts.
 * @param input Input system.
 * @return Seconds counted.
 */
u32 func_0011DF70(const ResidentInputSystem* input)
{
    return input->seconds;
}

/**
 * @brief Reset the seconds clock the vblank handler counts.
 * @param input Input system.
 */
void func_0011DF80(ResidentInputSystem* input)
{
    input->seconds = 0;
    input->second_vblanks = 0;
}

/**
 * @brief Clear the pressed and held-since-clear latches of a pad.
 * @param input Input system.
 * @param slot Pad slot.
 */
void resident_pad_clear_latched(ResidentInputSystem* input, s32 slot)
{
    input->held_since_clear[slot] = 0;
    input->pressed[slot] = 0;
}

/**
 * @brief Get the pressed buttons, or the held ones once they have been held long enough to repeat.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Button bits.
 */
u16 resident_pad_get_repeated(const ResidentInputSystem* input, s32 slot)
{
    if (input->repeat_counts[slot] >= input->repeat_delay)
    {
        return input->held[slot];
    }

    return input->pressed[slot];
}

/**
 * @brief Get the buttons newly pressed since the latches were last cleared.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Pressed button bits.
 */
u16 resident_pad_get_pressed(const ResidentInputSystem* input, s32 slot)
{
    return input->pressed[slot];
}

/**
 * @brief Get every button held at some point since the latches were last cleared.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Held button bits.
 */
u16 resident_pad_get_held_since_clear(const ResidentInputSystem* input, s32 slot)
{
    return input->held_since_clear[slot];
}

/**
 * @brief Get the buttons a pad holds this frame.
 * @param input Input system.
 * @param slot Pad slot.
 * @return Held button bits.
 */
u16 resident_pad_get_held(const ResidentInputSystem* input, s32 slot)
{
    return input->held[slot];
}

/**
 * @brief Choose whether a pad's left stick also presses the direction buttons.
 * @param input Input system.
 * @param slot Pad slot.
 * @param enabled Nonzero to map the stick onto the direction buttons.
 */
void resident_pad_set_stick_dpad(ResidentInputSystem* input, s32 slot, s32 enabled)
{
    input->stick_dpad[slot] = enabled;
}

/**
 * @brief Enable or disable a pad's vibration; disabling stops both motors.
 * @param input Input system.
 * @param slot Pad slot.
 * @param enabled Nonzero to allow vibration.
 */
void resident_pad_set_vibration_enabled(ResidentInputSystem* input, s32 slot, s32 enabled)
{
    if (!enabled)
    {
        input->small_motor[slot] = 0;
        input->large_motor[slot] = 0;
        input->vibration_dirty[slot] = 1;
    }

    input->vibration_enabled[slot] = enabled;
}

/**
 * @brief Send a pad's motor levels to it when they changed or a motor is running.
 * @param input Input system.
 * @param slot Pad slot.
 */
void resident_pad_update_vibration(ResidentInputSystem* input, s32 slot)
{
    u8 levels[2];
    s32 level_count;

    if (input->states[slot] != 1)
    {
        return;
    }

    if (!input->vibration_dirty[slot])
    {
        if (!input->vibration_enabled[slot])
        {
            return;
        }

        if (!input->small_motor[slot] && !input->large_motor[slot])
        {
            return;
        }
    }

    if (!input->vibration_profile_read[slot])
    {
        if (sceVibGetProfile(input->sockets[slot], input->vibration_profiles[slot]) <= 0)
        {
            return;
        }

        input->vibration_profile_read[slot] = 1;
    }

    input->vibration_profiles[slot][0] &= 3;

    switch (input->vibration_profiles[slot][0])
    {
    case 1:
        levels[0] = (input->small_motor[slot] & 1) | (input->large_motor[slot] != 0);
        level_count = 1;
        break;

    case 2:
        levels[0] = input->large_motor[slot];
        level_count = 1;
        break;

    case 3:
        levels[0] = ((input->large_motor[slot] & 0x7F) << 1) | (input->small_motor[slot] & 1);
        levels[1] = input->large_motor[slot] >> 7;
        level_count = 2;
        break;

    default:
        return;
    }

    if (sceVibSetActParam(input->sockets[slot], 1, input->vibration_profiles[slot], level_count, levels) == 1)
    {
        input->vibration_dirty[slot] = 0;
    }
}

/**
 * @brief Set a pad's motor levels while vibration is enabled.
 * @param input Input system.
 * @param slot Pad slot.
 * @param small Small motor, on when nonzero.
 * @param large Large motor strength.
 */
void resident_pad_set_vibration(ResidentInputSystem* input, s32 slot, s32 small, s32 large)
{
    if (!input->vibration_enabled[slot])
    {
        input->small_motor[slot] = 0;
        input->large_motor[slot] = 0;
        return;
    }

    if ((input->small_motor[slot] || input->large_motor[slot]) && !small && !large)
    {
        input->small_motor[slot] = 0;
        input->large_motor[slot] = 0;
        input->vibration_dirty[slot] = 1;
        return;
    }

    input->small_motor[slot] = small;
    input->large_motor[slot] = large;
}

/**
 * @brief Copy a range of a pad's button pressures.
 * @param input Input system.
 * @param slot Pad slot.
 * @param pressures Receives the pressures, zero when the pad isn't analog.
 * @param first First pressure index.
 * @param last Last pressure index, inclusive.
 * @return Nonzero when the pad is in analog mode.
 */
s32 func_0011E290(ResidentInputSystem* input, s32 slot, u8* pressures, s32 first, s32 last)
{
    if (!input->analog[slot])
    {
        for (s32 i = first; i <= last; i++)
        {
            *pressures++ = 0;
        }

        return 0;
    }

    for (s32 i = first; i <= last; i++)
    {
        *pressures++ = input->pressures[slot][i];
    }

    return 1;
}

/**
 * @brief Read a pad's four analog stick axes with the dead zone and calibration applied.
 * @param input Input system.
 * @param slot Pad slot.
 * @param right_x Receives the right stick's x axis.
 * @param right_y Receives the right stick's y axis.
 * @param left_x Receives the left stick's x axis.
 * @param left_y Receives the left stick's y axis.
 * @return Nonzero when the pad is in analog mode; the axes are zero otherwise.
 */
s32 resident_pad_get_sticks(ResidentInputSystem* input, s32 slot, s32* right_x, s32* right_y, s32* left_x, s32* left_y)
{
    if (!input->analog[slot])
    {
        *left_y = 0;
        *left_x = 0;
        *right_y = 0;
        *right_x = 0;
        return 0;
    }

    s32 dead_zone = input->dead_zones[slot];

    for (s32 axis = 0; axis < RESIDENT_PAD_AXIS_COUNT; axis++)
    {
        s32* out;

        switch (axis)
        {
        case 0:
            out = right_x;
            break;

        case 1:
            out = right_y;
            break;

        case 2:
            out = left_x;
            break;

        default:
            out = left_y;
            break;
        }

        s32 value = input->sticks[slot][axis] - 0x80 - input->stick_offsets[slot][axis];
        s32 distance = value >= 0 ? value : -value;

        if (distance < dead_zone)
        {
            value = 0;
        }
        else if (value > 0)
        {
            value -= dead_zone;
        }
        else
        {
            value += dead_zone;
        }

        s32 limit = input->stick_limits[slot][axis];

        if (value > limit)
        {
            value = limit;
        }

        if (value < -limit)
        {
            value = -limit;
        }

        *out = value;
    }

    return 1;
}

/**
 * @brief Count a vblank, update the attached display and wake the pad polling thread.
 * @param input Input system.
 */
void resident_input_handle_vblank(ResidentInputSystem* input)
{
    input->field = (GS_CSR >> 13) & 1;
    input->vblank_total++;

    if (++input->second_vblanks > 59)
    {
        input->second_vblanks = 0;
        input->seconds++;
    }

    if (input->display_enabled)
    {
        func_4DD520(input->display, input->field);
    }

    if (input->unk2fc)
    {
        s32 value = input->display->unk3e40;

        if (value >= 0x800000 || value <= 0)
        {
            input->unk2fc = 0;
        }
        else
        {
            value += input->unk250;
            func_4DCDA0(input->display, value);
        }
    }

    func_00103510(func_00101250(resident_get_system()));
    input->vblank_wait_count++;
    input->vblank_count++;
    func_00114DD0(&input->poll_thread);
}

/**
 * @brief Poll both pads: read their buttons, sticks and pressures, update the latches and send vibration.
 * @param input Input system.
 */
void resident_pad_update(ResidentInputSystem* input)
{
    for (s32 slot = 0; slot < RESIDENT_PAD_COUNT; slot++)
    {
        s32 left_x;
        s32 left_y;
        s32 right_x;
        s32 right_y;
        u8 data[0x20];
        u8 profile[0x20];

        s32 state = scePad2GetState(input->sockets[slot]);
        input->states[slot] = state;

        if (state != 1)
        {
            func_0011E9E0(input, slot, 1);
            input->retry_delays[slot] = 2;
            continue;
        }

        s32 data_size;

        if ((data_size = scePad2Read(input->sockets[slot], data)) < 0)
        {
            func_0011E9E0(input, slot, 1);
            continue;
        }

        s32 profile_size = scePad2GetButtonProfile(input->sockets[slot], profile);

        if (profile_size < 0)
        {
            func_0011E9E0(input, slot, 1);
            continue;
        }

        if (input->retry_delays[slot] > 0)
        {
            input->retry_delays[slot]--;
            continue;
        }

        input->previous_held[slot] = input->held[slot];

        if (profile[0] == 0xF9 && profile[1] == 0xFF && profile[2] == 0 && profile[3] == 0)
        {
            input->held[slot] = ~((data[0] & 1) | ((data[0] & 0xFE) << 2) | 6 | (data[1] << 10));
        }
        else
        {
            input->held[slot] = ~(data[0] | (data[1] << 8));
        }

        if (profile_size >= 3 && (profile[2] & 0xF) == 0xF)
        {
            if (data_size >= 6)
            {
                input->analog[slot] = 1;

                for (s32 axis = 0; axis < RESIDENT_PAD_AXIS_COUNT; axis++)
                {
                    input->sticks[slot][axis] = data[2 + axis];
                }
            }

            if (data_size >= 18 && profile_size >= 4 && (profile[2] & 0xF0) == 0xF0 && profile[3] == 0xFF)
            {
                for (s32 i = 0; i < RESIDENT_PAD_PRESSURE_COUNT; i++)
                {
                    input->pressures[slot][i] = data[6 + i];
                }
            }

            if (input->hook == 0 && input->stick_dpad[slot] &&
                resident_pad_get_sticks(input, slot, &right_x, &right_y, &left_x, &left_y))
            {
                if (left_x <= -(input->stick_limits[slot][2] >> 1))
                {
                    input->held[slot] |= SCE_PADLleft;
                }

                if (left_x >= input->stick_limits[slot][2] >> 1)
                {
                    input->held[slot] |= SCE_PADLright;
                }

                if (left_y <= -(input->stick_limits[slot][3] >> 1))
                {
                    input->held[slot] |= SCE_PADLup;
                }

                if (left_y >= input->stick_limits[slot][3] >> 1)
                {
                    input->held[slot] |= SCE_PADLdown;
                }
            }
        }
        else
        {
            input->analog[slot] = 0;
        }

        if (input->hook == 0)
        {
            if (input->previous_held[slot] == input->held[slot] && input->held[slot] != 0)
            {
                if (input->repeat_counts[slot] < input->repeat_delay)
                {
                    input->repeat_counts[slot]++;
                }
            }
            else
            {
                input->repeat_counts[slot] = 0;
            }

            input->held_since_clear[slot] |= input->held[slot];
            input->pressed[slot] |= input->held[slot] & ~input->previous_held[slot];
        }

        resident_pad_update_vibration(input, slot);
    }

    if (input->hook != 0)
    {
        input->hook->update(input);
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011E970);

/**
 * @brief Clear a pad's buttons, sticks and pressures, and wait a couple of polls before reading it again.
 * @param input Input system.
 * @param slot Pad slot.
 * @param full Nonzero in its low byte to also clear unk2a8.
 */
void func_0011E9E0(ResidentInputSystem* input, s32 slot, s32 full)
{
    input->held[slot] = 0;
    input->previous_held[slot] = 0;
    input->held_since_clear[slot] = 0;
    input->pressed[slot] = 0;
    input->repeat_counts[slot] = 0;
    input->retry_delays[slot] = 2;
    input->vibration_profile_read[slot] = 0;
    input->analog[slot] = 0;

    // TODO: I'd expect input->sticks[slot][axis] here, but only a byte pointer into the array puts the row address
    // where the original computes it.
    u8* sticks = (u8*)input->sticks + slot * RESIDENT_PAD_AXIS_COUNT;

    for (s32 axis = 0; axis < RESIDENT_PAD_AXIS_COUNT; axis++)
    {
        sticks[axis] = 0;
    }

    for (s32 i = 0; i < RESIDENT_PAD_PRESSURE_COUNT; i++)
    {
        input->pressures[slot][i] = 0;
    }

    if ((u8)full)
    {
        input->unk2a8[slot] = 0;
    }
}

/**
 * @brief Start the input system: open both pad sockets, install the vblank handler and start the polling thread.
 * @param input Input system.
 */
void func_0011EA80(ResidentInputSystem* input)
{
    while (!sceDbcInit())
    {
    }

    while (!scePad2Init(0))
    {
    }

    input->repeat_delay = 12;

    for (s32 slot = 0; slot < RESIDENT_PAD_COUNT; slot++)
    {
        scePad2SocketParam param;

        param.option = SCE_PAD2_SPECIFIC_PORT;
        param.port = slot != 0;
        param.slot = 0;
        param.number = 0;
        param.name[0] = 0;
        input->vibration_profile_read[slot] = 0;
        input->vibration_dirty[slot] = 0;
        input->vibration_enabled[slot] = 0;
        input->sockets[slot] = scePad2CreateSocket(&param, input->pad_buffers[slot]);
        input->states[slot] = 0;
        func_0011E9E0(input, slot, 1);
        input->stick_dpad[slot] = 1;

        input->stick_offsets[slot][0] = 0;
        input->stick_offsets[slot][1] = 0;
        input->stick_offsets[slot][2] = 0;
        input->stick_offsets[slot][3] = 0;

        input->dead_zones[slot] = 0x20;

        input->stick_limits[slot][0] = 0x50;
        input->stick_limits[slot][1] = 0x50;
        input->stick_limits[slot][2] = 0x50;
        input->stick_limits[slot][3] = 0x50;

        input->small_motor[slot] = 0;
        input->large_motor[slot] = 0;
    }

    input->vblank_handler = AddIntcHandler(INTC_VBLANK_S, D_0011E9A0, 0);
    EnableIntc(INTC_VBLANK_S);
    input->hook = 0;
    input->display = 0;
    input->vblank_count = 0;
    input->unk2fc = 0;
    input->poll_thread.input = input;
    input->poll_thread.start();
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0010A0E0", func_0011EC30);

/**
 * @brief Release pending allocations, then destroy pending objects and flush the cache.
 * @param queues Deferred release queues to drain.
 */
void resident_drain_release_queues(ResidentReleaseQueues* queues)
{
    for (;;)
    {
        s32 next = queues->allocations.read_index + 1;

        if (next >= 0x400)
        {
            next = 0;
        }

        if (next == queues->allocations.write_index)
        {
            break;
        }

        ::operator delete(queues->allocations.entries[next]);
        queues->allocations.read_index = next;
    }

    for (;;)
    {
        s32 next = queues->objects.read_index + 1;

        if (next >= 0x400)
        {
            next = 0;
        }

        if (next == queues->objects.write_index)
        {
            break;
        }

        delete static_cast<ResidentClass14FA20*>(queues->objects.entries[next]);
        queues->objects.read_index = next;
    }

    FlushCache(0);
}

/**
 * @brief Queue an object for destruction by its virtual destructor.
 * @param queue Deferred release queues.
 * @param object Object to destroy later; null succeeds without insertion.
 * @return One on success, or zero when the object ring is full.
 */
s32 resident_enqueue_object(ResidentReleaseQueues* queue, void* object)
{
    if (object == 0)
    {
        return 1;
    }

    if (resident_object_release_ring_is_full(queue))
    {
        return 0;
    }

    queue->objects.entries[queue->objects.write_index++] = object;

    if (queue->objects.write_index >= 0x400)
    {
        queue->objects.write_index = 0;
    }

    return 1;
}
}
