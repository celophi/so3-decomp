#ifndef SO3_MAIN_SOUND_STREAM_H
#define SO3_MAIN_SOUND_STREAM_H

#include "types.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"
#include "main/resource_queue.h"

#ifdef __cplusplus
class ResidentStreamThread;
#else
typedef struct ResidentStreamThread ResidentStreamThread;
#endif

#ifdef __cplusplus
struct ResidentSystem;
#else
typedef struct ResidentSystem ResidentSystem;
#endif

/** Header shared by every chunk of a sound file; size is the offset of the next chunk, and the data follows. */
typedef struct SoundChunk
{
    u32 tag;
    u32 size;
    u32 key;
    s32 unk0C;
} SoundChunk;

/** Header of a SEQ or SEQW sound file. */
typedef struct SoundFileHeader
{
    u32 tag;
    u32 size;
    s32 unk08;
    u32 unk0C;
    u32 unk10;
    u32 unk14;
    u8 has_lip;
    u8 unk19[0xD];
    s16 bank_id;
    s8 priority;
} SoundFileHeader;

/** WAV chunk of a sound file. */
typedef struct SoundWaveChunk
{
    u32 tag;
    u32 size;
    u32 unk08;
    s32 unk0C;
    u32 unk10;
    s32 wave_size;
} SoundWaveChunk;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the stream thread's second state to one when the value is positive.
 * @param stream Sound stream.
 * @param value Value to check.
 */
void resident_stream_set_second_state(struct ResidentSoundStream* stream, const s32* value);

/**
 * @brief Set the stream thread's first state to one when the value is positive.
 * @param stream Sound stream.
 * @param value Value to check.
 * @return The value when it is positive, otherwise zero.
 */
s32 resident_stream_set_first_state(struct ResidentSoundStream* stream, const s32* value);

/**
 * @brief Run the resident helper with an object and four word arguments.
 * @param object Input object.
 * @param arg1 First input word.
 * @param arg2 Second input word.
 * @param arg3 Third input word.
 * @param arg4 Fourth input word.
 */
u32 resident_stream_set_output_mode(void* object, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

/**
 * @brief Query the stream: modes one and two read the stream thread's states, other modes go to resident_stream_command_13.
 * @param stream Sound stream.
 * @param arg1 First argument for resident_stream_command_13.
 * @param arg2 Second argument for resident_stream_command_13.
 * @param arg3 Third argument for resident_stream_command_13.
 * @param mode Query mode.
 * @return Query result.
 */
s32 resident_stream_query(struct ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 mode);

s32 resident_stream_command_13(struct ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 mode);

/**
 * @brief Send a command for one of the stream's voices.
 * @param stream Sound stream.
 * @param arg1 Unused by the sound callers, which pass zero.
 * @param arg2 Unused by the sound callers, which pass zero.
 * @param arg3 Unused by the sound callers, which pass zero.
 * @param handle Voice handle.
 * @param command Command number.
 * @param first First command argument.
 * @param second Second command argument.
 */
u32 resident_stream_send_voice_command(struct ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 handle, s32 command, s32 first, s32 second);

/**
 * @brief Stop one of the stream's voices or music tracks.
 * @param stream Sound stream.
 * @param arg1 Unused by the sound callers, which pass zero.
 * @param callback Called when the stop completes.
 * @param argument Passed to the callback.
 * @param handle Voice or track handle; 1 and 2 are special values.
 * @param mode Stop mode.
 * @param arg6 Unused by the sound callers, which pass zero.
 * @return Nonzero when the stop was sent.
 */
s32 resident_stream_stop(struct ResidentSoundStream* stream, u32 arg1, void (*callback)(void*), void* argument, u32 handle, s32 mode,
                  u32 arg6);

/**
 * @brief Start the sound stream.
 * @param stream Sound stream.
 * @param arg1 Unused by the sound callers, which pass zero.
 * @param arg2 Unused by the sound callers, which pass zero.
 * @param arg3 Unused by the sound callers, which pass zero.
 * @param arg4 First setup size.
 * @param arg5 Second setup size.
 * @param arg6 Third setup size.
 * @param arg7 Setup value.
 * @param arg8 Setup value.
 * @return Zero.
 */
s32 resident_stream_start(struct ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s32 arg7, s32 arg8);

/**
 * @brief Stream setup step run after resident_stream_start completes.
 * @param stream Sound stream.
 */
void resident_stream_setup_buffers(struct ResidentSoundStream* stream);

/**
 * @brief Send a word to the sound stream.
 * @param stream Sound stream.
 * @param arg1 Unused by the sound callers, which pass zero.
 * @param arg2 Unused by the sound callers, which pass zero.
 * @param arg3 Unused by the sound callers, which pass zero.
 * @param value Value sent.
 */
u32 resident_stream_set_volume(struct ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3, s32 value);

/*
 * Sound stream requests to the IOP. Each one takes the SIF request semaphore, fills the next 64-byte argument block
 * and sends the command; it returns the request handle, or zero when no reply slot is free. arg1 is the reply
 * buffer, then the callback and its argument (or two plain arguments).
 */

/**
 * @brief Send sound stream command 0x14 with a count and that many words.
 * @param stream Sound stream; unused.
 * @param arg1 Reply buffer address, or zero.
 * @param callback Called with the reply, or null.
 * @param argument Passed to callback.
 * @param values Words to send.
 * @param count Number of words.
 * @return Request handle, or zero when no reply slot is free.
 */
u32 resident_stream_send_words(struct ResidentSoundStream* stream, s32 arg1, void* callback, void* argument, const u32* values,
                  s32 count);

/**
 * @brief Send sound stream command 0x10 with a flag in the seventh word.
 * @return Request handle, or zero when no reply slot is free.
 */
s32 resident_stream_play_flagged(void* object, s32 arg1, void* callback, void* argument, s32 arg4, s32 command, s32 arg6, s32 arg7,
                  u32 arg8, s32 arg9, u8 arg10);

/**
 * @brief Send sound stream command 0x10 for a request slot.
 * @return Request handle, or zero when no reply slot is free.
 */
s32 resident_stream_play_slot(void* context, s32 first, void (*callback)(void*, struct ResidentRequestSlot*),
                  struct ResidentRequestSlot* slot, s32 selected, s32 value, s32 arg3, s32 zero, u32 packed,
                  u32 placement, u32 room);

/**
 * @brief Send sound stream command 0x10 for a request slot, with one packed word.
 * @return Request handle, or zero when no reply slot is free.
 */
s32 resident_stream_play_slot_packed(void* context, s32 first, void (*callback)(void*, struct ResidentRequestSlot*),
                  struct ResidentRequestSlot* slot, s32 selected, s32 value, s32 arg3, s32 zero, s32 packed);

/**
 * @brief Send sound stream command 0x10 with the fifth word set to 0x7F400000.
 * @return Request handle, or zero when no reply slot is free.
 */
s32 resident_stream_play_streamed(void* object, s32 arg1, void* callback, void* argument, s32 arg4, s32 command, s32 arg6, s32 arg7);

/**
 * @brief Send sound stream command 0xC with an empty argument block.
 * @param object Sound stream; unused.
 * @param arg1 Reply buffer address, or zero.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @return Request handle, or zero when no reply slot is free.
 */
u32 resident_stream_command_0c(void* object, s32 arg1, s32 arg2, s32 arg3);

/**
 * @brief Send sound stream command 0x7 with four values, allocating a slot buffer first when a size is given.
 * @param stream Sound stream.
 * @param reply Reply buffer, or null.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @param index Slot the buffer is for.
 * @param arg5 First value.
 * @param arg6 Second value.
 * @param arg7 Third value.
 * @param arg8 Fourth value.
 * @param arg9 Size of the slot buffer to allocate, or zero for none.
 * @return Request handle, or zero when no reply slot is free.
 */
u32 resident_stream_send_setup(struct ResidentSoundStream* stream, u32* reply, s32 arg2, s32 arg3, s32 index, u32 arg5, u32 arg6,
                  u32 arg7, u32 arg8, u32 arg9);

/**
 * @brief Send sound stream command 0xB to the IOP with four values in the argument block.
 * @param stream Sound stream; unused.
 * @param arg1 Reply buffer address, or zero.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @param value0 First value.
 * @param value1 Second value.
 * @param value2 Third value.
 * @param value3 Fourth value.
 * @return Request handle, or zero when no reply slot is free.
 */
u32 resident_stream_command_0b(struct ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3, u32 value0, u32 value1, u32 value2,
                  u32 value3);

/**
 * @brief Wake the stream thread, or wake it and sleep until it has run.
 * @param stream Sound stream.
 * @param no_wait Nonzero to wake the thread without waiting for it.
 * @return Zero.
 */
s32 resident_stream_wake_thread(struct ResidentSoundStream* stream, s32 no_wait);

/**
 * @brief Run one step of the sequence upload at the front of the sequence queue.
 * @param stream Sound stream.
 * @return Zero, minus one when an IOP request can't be made, or minus two when the IOP reports an error.
 */
s32 resident_stream_step_sequence_upload(struct ResidentSoundStream* stream);

/**
 * @brief Run one step of the bank load at the front of the bank queue.
 * @param stream Sound stream.
 * @return Zero, or minus one when an IOP request can't be made.
 */
s32 resident_stream_step_bank_load(struct ResidentSoundStream* stream);

/**
 * @brief Read the word at offset 0x14 of a SEQW file header.
 * @param stream Sound stream; unused.
 * @param file Sound file.
 * @return The word, or zero when the file isn't a SEQW file.
 */
u32 resident_sound_file_get_word14(struct ResidentSoundStream* stream, const SoundFileHeader* file);

/**
 * @brief Find the VSC chunk of a lip table entry.
 * @param stream Sound stream.
 * @param entry Lip table entry.
 * @param slot Slot holding the lip table.
 * @return Data of the VSC chunk, or null when the entry or the chunk is missing.
 */
void* resident_stream_find_lip_chunk(struct ResidentSoundStream* stream, s32 entry, s32 slot);

/**
 * @brief Report whether a sound file has an upload in the sequence queue.
 * @param stream Sound stream.
 * @param file Sound file.
 * @return One when the file is queued, otherwise zero.
 */
s32 resident_stream_is_sequence_queued(struct ResidentSoundStream* stream, const void* file);

/**
 * @brief Queue the upload of a sound file's sequence and wave data to the IOP.
 * @param stream Sound stream.
 * @param file SEQ or SEQW file, or a bare WAV chunk.
 * @param arg2 Stored with the request.
 * @param slot Slot the file's LIP chunk is copied into, or zero for none.
 * @param result Receives the IOP's reply once the upload finishes; may be null.
 * @param arg5 Stored with the request.
 * @param arg6 Stored with the request.
 * @return One when queued, zero when the queue is full, or minus one when the file has no WAV chunk.
 */
s32 resident_stream_queue_sequence(struct ResidentSoundStream* stream, const void* file, u32 arg2, s32 slot, s32* result, u32 arg5,
                  u32 arg6);

/**
 * @brief Run the sequence uploads until one has to wait.
 * @param stream Sound stream.
 * @return Zero, or the negative result of a failed step.
 */
s32 resident_stream_run_sequence_uploads(struct ResidentSoundStream* stream);

/**
 * @brief Continue the bank load waiting at the front of the bank queue by sending its wave data request.
 * @param stream Sound stream.
 * @param arg1 First request argument.
 * @param arg2 Second request argument.
 * @return Data of the slot the bank's sound file was copied into.
 */
u8* resident_stream_request_bank_waves(struct ResidentSoundStream* stream, u32 arg1, u32 arg2);

/**
 * @brief Report whether a sound file has a load in the bank queue.
 * @param stream Sound stream.
 * @param file Sound file.
 * @return One when the file is queued, minus one when it is queued and waiting for resident_stream_request_bank_waves, otherwise zero.
 */
s32 resident_stream_is_bank_queued(struct ResidentSoundStream* stream, const void* file);

/**
 * @brief Queue a sound bank load.
 * @param stream Sound stream.
 * @param file SEQ or SEQW file, or a bare WAV chunk.
 * @param result Receives the loaded size, or zero when the load is dropped; may be null.
 * @param arg3 Stored with the request.
 * @param arg4 Stored with the request.
 * @param arg5 Stored with the request.
 * @param arg6 Stored with the request.
 * @param arg7 Stored with the request.
 * @return One when queued, zero when the queue is full, minus one when the file has no WAV chunk, or minus two or
 * minus three when the sequence or wave header value is 0xFC or more.
 */
s32 resident_stream_queue_bank(struct ResidentSoundStream* stream, const void* file, s32* result, u32 arg3, u32 arg4, u32 arg5,
                  u32 arg6, u32 arg7);

/**
 * @brief Choose the channel for the bank load at the front of the bank queue.
 * @param stream Sound stream.
 * @return Channel index, or minus one when the bank can't be loaded.
 */
s32 resident_stream_pick_bank_channel(struct ResidentSoundStream* stream);

/**
 * @brief Run the bank loads until one has to wait.
 * @param stream Sound stream.
 * @return Zero, or the negative result of a failed step.
 */
s32 resident_stream_run_bank_loads(struct ResidentSoundStream* stream);


#ifdef __cplusplus
/**
 * @brief Report whether an IOP request of the stream is still running.
 * @param stream Sound stream; unused.
 * @param request Request ID.
 * @return True while the request runs.
 */
bool resident_stream_is_request_running(struct ResidentSoundStream* stream, s32 request);
#endif

/**
 * @brief Send sound stream command 0x1C to the IOP.
 * @param stream Sound stream; unused.
 * @param reply Receives the reply, or null.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @return Request handle.
 */
u32 resident_stream_command_1c(struct ResidentSoundStream* stream, void* reply, s32 arg2, s32 arg3);

/**
 * @brief Send sound stream command 0x1B to the IOP with four values in the argument block.
 * @param stream Sound stream; unused.
 * @param value0 First value.
 * @param value1 Second value.
 * @param value2 Third value.
 * @param value3 Fourth value.
 * @return Request handle, or zero when no reply slot is free.
 */
u32 resident_stream_command_1b(struct ResidentSoundStream* stream, s32 value0, s32 value1, s32 value2, s32 value3);

/**
 * @brief Send sound stream command 0x19 to the IOP with an empty argument block.
 * @param stream Sound stream; unused.
 * @param reply Receives the reply, or null.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @return Request handle, or zero when no reply slot is free.
 */
u32 resident_stream_command_19(struct ResidentSoundStream* stream, void* reply, s32 arg2, s32 arg3);

/**
 * @brief Send sound stream command 0x18 to the IOP.
 * @param stream Sound stream; unused.
 * @param reply Receives the reply, or null.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @return Request handle.
 */
u32 resident_stream_command_18(struct ResidentSoundStream* stream, void* reply, s32 arg2, s32 arg3);

/**
 * @brief Read four values from the sound stream's IOP side.
 * @param stream Sound stream.
 * @param x Receives the first value.
 * @param y Receives the second value.
 * @param z Receives the third value.
 * @param w Receives the fourth value.
 */
void resident_stream_read_iop_vector(struct ResidentSoundStream* stream, u32* x, u32* y, u32* z, u32* w);


#ifdef __cplusplus
}
#endif

/** Object a positional sound comes from; only its flag for an attached sound is known. */
typedef struct ResidentSoundEmitter
{
    u8 unk000[0x90];
    float unk90[3][4];
    u8 unkc0[0x14E];
    u8 unk20e_0_3 : 4;
    u8 has_sound : 1;
    u8 unk20e_5_7 : 3;
} ResidentSoundEmitter;

/** One of the sixty sound slots: a sound effect or voice the stream plays. */
typedef struct ResidentRequestSlot
{
    u8 active;
    u8 started;
    u8 stop_requested;
    u8 unk03;
    u8 owns_buffer;

    // TODO: volatile is my guess for selector and value, like handle below; the lip sync lookups read value again
    volatile u8 selector;
    u8 unk06[2];
    volatile u16 value;
    u8 unk0a[2];

    /**
     * Voice handle from the stream.
     * TODO: volatile is my guess, like target; resident_sound_stop_all reads it into a local it never uses, and only a volatile
     * read keeps that load.
     */
    volatile u32 handle;

    s32 identifier;
    s32 stop_mode;
    s32 volume;
    u8 unk1c;
    u8 unk1d[3];

    /**
     * Object a positional sound comes from, or null.
     * TODO: volatile is my guess; the reply callbacks reread it after every use, and nothing else I tried does that.
     */
    struct ResidentSoundEmitter* volatile target;

    // TODO: volatile is my guess for buffer, unk2c, unk34 and unk38 too; the update only loads them in order with it
    u8* volatile buffer;
    u32 unk28;
    volatile u32 unk2c;
    union
    {
        u32 unk30;
        float unk30_float;
    };

    volatile u32 unk34;
    volatile u32 unk38;
} ResidentRequestSlot;

#ifdef __cplusplus

/** A sound bank load waiting in the stream's bank queue. */
struct ResidentBankRequest
{
    const void* file;
    s32* result;
    s16 bank_id;
    s8 priority;
    u8 waiting;
    s32 wave_size;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
};

/** A sequence upload waiting in the stream's sequence queue. */
struct ResidentSequenceRequest
{
    s32 remaining;
    const u8* cursor;
    const void* file;
    s32 unk0C;
    u8 slot;
    u32 unk14;
    u32 unk18;
    s32* result;
};

/** One of the four regions of sound memory the stream loads banks into. */
struct ResidentStreamChannel
{
    s32 size;
    s16 bank_id;
    s8 priority;
    u32 age;
    u32 address;
    u8 slot;
};

/** Sound stream at g_system + 0x15A5C: queues sound bank loads and sequence uploads for the IOP; vtable D_0014FA90. */
class ResidentSoundStream : public ResidentListener
{
    public:
        u8 unk04[0x40];
        u32 unk44;
        u8 unk48[0x44];
        u8 waiting;
        ResidentStreamThread* thread;
        u32 next_age;
        ResidentStreamChannel channels[4];
        u8 bank_state;
        u8 bank_channel;
        u8 bank_first_channel;
        u8 bank_channel_count;
        s32 bank_request;
        s32 bank_status[4];
        u8 unk100[0x30];
        u32 bank_address;
        u8 bank_slot;
        ResidentBankRequest* bank_queue;
        ResidentBankRequest* bank_read;
        ResidentBankRequest* bank_write;
        ResidentBankRequest* bank_queue_end;
        u8 sequence_state;
        u32 sequence_address;
        s32 sequence_request;
        s32 sequence_status;
        u8 unk158[0x3C];
        ResidentSequenceRequest* sequence_queue;
        ResidentSequenceRequest* sequence_read;
        ResidentSequenceRequest* sequence_write;
        ResidentSequenceRequest* sequence_queue_end;
        void* slots[32];

        /**
         * @brief Handle a SIF command from the IOP.
         * @param data Command number.
         */
        virtual void notify(void* data);

        /** @brief Free the queues, the loaded files and the stream thread. */
        virtual ~ResidentSoundStream();

        /** @brief Create the stream thread and the two request queues, with every channel and slot empty. */
        ResidentSoundStream();
};
#endif

#ifndef __cplusplus
typedef struct ResidentSoundStream ResidentSoundStream;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the resident system's sound stream.
 * @param system Resident system.
 * @return Sound stream at offset 0x15A5C.
 */
struct ResidentSoundStream* resident_system_get_sound_stream(struct ResidentSystem* system);

#ifdef __cplusplus
}
#endif

#endif
