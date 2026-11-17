#include "include_asm.h"
#include "main/stream_output.h"
#include "main/sif.h"

#define SOUND_TAG_SEQ 0x20514553
#define SOUND_TAG_SEQW 0x57514553
#define SOUND_TAG_WAV 0x20564157
#define SOUND_TAG_LIP 0x2050494C
#define SOUND_TAG_LIPT 0x5450494C
#define SOUND_TAG_VSC 0x20435356
#define STREAM_BLOCK_SIZE 0x1000
#define STREAM_CHANNEL_SIZE 0x10000

extern "C" {

s32 SleepThread(void);

}

/**
 * @brief Read four values from the sound stream's IOP side.
 * @param stream Sound stream.
 * @param x Receives the first value.
 * @param y Receives the second value.
 * @param z Receives the third value.
 * @param w Receives the fourth value.
 */
extern "C" void resident_stream_read_iop_vector(ResidentSoundStream* stream, u32* x, u32* y, u32* z, u32* w)
{
    u32 reply[16];
    u32 handle;

    {
        ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
        handle = resident_sif_request(&g_sif, 0xE, reply, 0, 0, 0);
    }

    while (resident_sif_is_request_pending(&g_sif, handle))
    {
    }

    if (reply[0])
    {
        *x = reply[1];
        *y = reply[2];
        *z = reply[3];
        *w = reply[4];
    }
}

/**
 * @brief Send sound stream command 0x1C to the IOP.
 * @param stream Sound stream; unused.
 * @param reply Receives the reply, or null.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @return Request handle.
 */
extern "C" u32 resident_stream_command_1c(ResidentSoundStream* stream, void* reply, s32 arg2, s32 arg3)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());

    return resident_sif_request(&g_sif, 0x1C, reply, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0x1B to the IOP with four values in the argument block.
 * @param stream Sound stream; unused.
 * @param value0 First value.
 * @param value1 Second value.
 * @param value2 Third value.
 * @param value3 Fourth value.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 resident_stream_command_1b(ResidentSoundStream* stream, s32 value0, s32 value1, s32 value2, s32 value3)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = value0;
    arguments[1] = value1;
    arguments[2] = value2;
    arguments[3] = value3;
    return resident_sif_request(&g_sif, 0x1B, 0, 0, 0, 0);
}

/**
 * @brief Send sound stream command 0x19 to the IOP with an empty argument block.
 * @param stream Sound stream; unused.
 * @param reply Receives the reply, or null.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 resident_stream_command_19(ResidentSoundStream* stream, void* reply, s32 arg2, s32 arg3)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    return resident_sif_request(&g_sif, 0x19, reply, arg2, arg3, 0);
}

/**
 * @brief Read the word at offset 0x14 of a SEQW file header.
 * @param stream Sound stream; unused.
 * @param file Sound file.
 * @return The word, or zero when the file isn't a SEQW file.
 */
extern "C" u32 resident_sound_file_get_word14(ResidentSoundStream* stream, const SoundFileHeader* file)
{
    if (file->tag == SOUND_TAG_SEQW)
    {
        return file->unk14;
    }

    return 0;
}

/** A LIPT chunk: one VSC chunk key for each lip table entry. */
struct SoundLipTable
{
    SoundChunk header;
    u32 keys[1];
};

/**
 * @brief Get the data that follows a chunk's header.
 * @param chunk Sound file chunk.
 * @return The chunk's data.
 */
static inline void* sound_chunk_data(const SoundChunk* chunk)
{
    return (u8*)chunk + sizeof(SoundChunk);
}

/**
 * @brief Get the chunk after this one.
 * @param chunk Sound file chunk.
 * @return The next chunk.
 */
static inline SoundChunk* sound_chunk_next(const SoundChunk* chunk)
{
    return (SoundChunk*)((u8*)chunk + chunk->size);
}

/**
 * @brief Find the VSC chunk of a lip table entry.
 * @param stream Sound stream.
 * @param entry Lip table entry.
 * @param slot Slot holding the lip table; the slot after it is searched too.
 * @return Data of the VSC chunk, or null when the entry or the chunk is missing.
 */
extern "C" void* resident_stream_find_lip_chunk(ResidentSoundStream* stream, s32 entry, s32 slot)
{
    SoundChunk* chunk;
    u32 key = 0;
    u32 tag;
    // TODO: Only matches with the slot index scaled by hand like this; my guess is the original did its own math.
    s32 offset = slot * 4;
    SoundChunk* first = *(SoundChunk**)((u8*)&stream->slots[0] + offset);
    u32 next_tag;
    SoundChunk* next;

    for (chunk = first, tag = chunk->tag; tag != 0; chunk = sound_chunk_next(chunk), tag = chunk->tag)
    {
        if (tag == SOUND_TAG_LIPT)
        {
            key = ((SoundLipTable*)chunk)->keys[entry];
            break;
        }
    }

    if (key == 0)
    {
        return 0;
    }

    for (chunk = first, tag = chunk->tag; tag != 0; chunk = sound_chunk_next(chunk), tag = chunk->tag)
    {
        if (tag == SOUND_TAG_VSC && key == chunk->key)
        {
            return sound_chunk_data(chunk);
        }
    }

    next = *(SoundChunk**)((u8*)&stream->slots[1] + offset);

    for (next_tag = next->tag; next_tag != 0; next = sound_chunk_next(next), next_tag = next->tag)
    {
        if (next_tag == SOUND_TAG_VSC && key == next->key)
        {
            return sound_chunk_data(next);
        }
    }

    return 0;
}

/**
 * @brief Report whether a sound file has an upload in the sequence queue.
 * @param stream Sound stream.
 * @param file Sound file.
 * @return One when the file is queued, otherwise zero.
 */
extern "C" s32 resident_stream_is_sequence_queued(ResidentSoundStream* stream, const void* file)
{
    DIntr();

    ResidentSequenceRequest* request = stream->sequence_read;

    for (;;)
    {
        if (request == stream->sequence_write)
        {
            break;
        }

        if (request->file == file)
        {
            EIntr();
            return 1;
        }

        if (++request >= stream->sequence_queue_end)
        {
            request = stream->sequence_queue;
        }
    }

    EIntr();
    return 0;
}

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
extern "C" s32 resident_stream_queue_sequence(ResidentSoundStream* stream, const void* file, u32 arg2, s32 slot, s32* result, u32 arg5,
                             u32 arg6)
{
    ResidentSequenceRequest* next = stream->sequence_write + 1;

    if (next == stream->sequence_queue_end)
    {
        next = stream->sequence_queue;
    }

    if (next == stream->sequence_read)
    {
        return 0;
    }

    s32 size = 0;
    const SoundChunk* chunk = (const SoundChunk*)file;

    if (chunk->tag == SOUND_TAG_SEQ)
    {
        size = chunk->size;
    }
    else
    {
        if (chunk->tag == SOUND_TAG_SEQW)
        {
            size = chunk->size;
            chunk = (const SoundChunk*)((const u8*)file + size);
        }

        if (chunk->tag == SOUND_TAG_WAV)
        {
            size += chunk->size;
        }
        else
        {
            return -1;
        }
    }

    stream->sequence_write->remaining = size;
    stream->sequence_write->cursor = (const u8*)file;
    stream->sequence_write->file = file;
    stream->sequence_write->unk0C = arg2;
    stream->sequence_write->slot = slot;
    stream->sequence_write->unk14 = arg5;
    stream->sequence_write->unk18 = arg6;
    stream->sequence_write->result = result;
    stream->sequence_write = next;
    return 1;
}

/**
 * @brief Get the data loaded into one of the stream's slots.
 * @param stream Sound stream.
 * @param slot Slot.
 * @return The slot's data, or null.
 */
static inline void* stream_slot(ResidentSoundStream* stream, u8 slot)
{
    return stream->slots[slot];
}

/**
 * @brief Find the end of a list of chunks: the chunk with a zero tag.
 * @param chunk First chunk.
 * @return The terminating chunk.
 */
static inline SoundChunk* chunk_list_end(SoundChunk* chunk)
{
    while (chunk->tag != 0)
    {
        chunk = (SoundChunk*)((u8*)chunk + chunk->size);
    }

    return chunk;
}

/**
 * @brief Move the sequence upload to its next step once the IOP has replied to its request.
 * @param stream Sound stream.
 */
static inline void sequence_step_when_replied(ResidentSoundStream* stream)
{
    if (!resident_sif_is_request_pending(&g_sif, stream->sequence_request))
    {
        stream->sequence_state++;
    }
}

/**
 * @brief Run one step of the sequence upload at the front of the sequence queue.
 *
 * The steps: ask the IOP for room, copy the file's LIP chunk into its slot, wait for the reply, send the file in
 * 4 KiB blocks (the SIF handler sends the rest), finish the upload, wait for that reply, then report the result and
 * move to the next request.
 *
 * @param stream Sound stream.
 * @return Zero, minus one when an IOP request can't be made, or minus two when the IOP reports an error.
 */
extern "C" s32 resident_stream_step_sequence_upload(ResidentSoundStream* stream)
{
    switch (stream->sequence_state)
    {
    case 1:
        stream->sequence_request = resident_stream_command_0b(stream, (s32)&stream->sequence_status, 0, 0, stream->sequence_address,
                                                 stream->sequence_read->unk0C, stream->sequence_read->unk14,
                                                 stream->sequence_read->unk18);

        if (!stream->sequence_request)
        {
            return -1;
        }

        stream->sequence_state++;
        break;

    case 2:
    {
        const SoundFileHeader* file;
        const SoundChunk* wave;
        const SoundChunk* chunk;
        ResidentSequenceRequest* request = stream->sequence_read;
        u8* slot = &request->slot;
        u32 index = *slot;

        if (index != 0 && stream_slot(stream, index) != 0)
        {
            file = (const SoundFileHeader*)request->cursor;

            if (file->has_lip)
            {
                wave = (const SoundChunk*)((const u8*)file + file->size);
                chunk = (const SoundChunk*)((const u8*)wave + wave->size);

                if (chunk->tag == SOUND_TAG_LIP)
                {
                    u32 size = chunk->key;
                    const u32* source = (const u32*)(chunk + 1);
                    u32* destination = request->unk14 == 0 ? (u32*)stream_slot(stream, index)
                                                           : (u32*)chunk_list_end((SoundChunk*)stream_slot(stream, index));

                    for (u32 i = 0; i < size / 4; i++)
                    {
                        *destination++ = *source++;
                    }

                    *destination = 0;
                }
                else
                {
                    *slot = 0;
                }
            }
            else
            {
                *slot = 0;
            }
        }

        stream->sequence_state++;
        sequence_step_when_replied(stream);
        break;
    }

    case 3:
        sequence_step_when_replied(stream);
        break;

    case 4:
        stream->sequence_state++;
        resident_sif_send_command(&g_sif, 1, (void*)stream->sequence_read->cursor, (void*)stream->sequence_address,
                      STREAM_BLOCK_SIZE);
        break;

    case 6:
        stream->sequence_request = resident_stream_command_0c(stream, (s32)&stream->sequence_status, 0, 0);

        if (!stream->sequence_request)
        {
            return -1;
        }

        stream->sequence_state++;
        break;

    case 7:
        sequence_step_when_replied(stream);
        break;

    case 8:
        if (stream->sequence_status < 0)
        {
            return -2;
        }

        if (stream->sequence_read->unk0C < 4)
        {
            if (stream->sequence_read->result)
            {
                *stream->sequence_read->result = stream->sequence_status;
            }
        }
        else if (stream->sequence_read->result)
        {
            *stream->sequence_read->result = stream->sequence_read->unk0C;
        }

        stream->sequence_state = 0;
        stream->sequence_read++;

        if (stream->sequence_read == stream->sequence_queue_end)
        {
            stream->sequence_read = stream->sequence_queue;
        }

        break;
    }

    return 0;
}

/**
 * @brief Run the sequence uploads until one has to wait.
 * @param stream Sound stream.
 * @return Zero, or the negative result of a failed step.
 */
extern "C" s32 resident_stream_run_sequence_uploads(ResidentSoundStream* stream)
{
    if (stream->sequence_read == stream->sequence_write)
    {
        return 0;
    }

    for (;;)
    {
        s32 result = resident_stream_step_sequence_upload(stream);

        if (result < 0)
        {
            return result;
        }

        if (stream->sequence_state != 0)
        {
            return 0;
        }

        if (stream->sequence_read == stream->sequence_write)
        {
            return 0;
        }

        stream->sequence_state = 1;
    }
}

/**
 * @brief Continue the bank load waiting at the front of the bank queue by sending its wave data request.
 * @param stream Sound stream.
 * @param arg1 First request argument.
 * @param arg2 Second request argument.
 * @return Data of the slot the bank's sound file was copied into.
 */
extern "C" u8* resident_stream_request_bank_waves(ResidentSoundStream* stream, u32 arg1, u32 arg2)
{
    ResidentBankRequest* request = stream->bank_read;

    stream->bank_request = resident_stream_play_slot(stream, (s32)stream->bank_status, (void (*)(void*, ResidentRequestSlot*))arg1,
                                         (ResidentRequestSlot*)arg2, stream->bank_address, request->unk10, request->unk14, 0,
                                         request->unk18, request->unk1C, request->unk20);
    request->waiting = 0;
    stream->bank_state++;
    return (u8*)stream->slots[stream->bank_slot] + sizeof(SoundChunk);
}

/**
 * @brief Report whether a sound file has a load in the bank queue.
 * @param stream Sound stream.
 * @param file Sound file.
 * @return One when the file is queued, minus one when it is queued and waiting for resident_stream_request_bank_waves, otherwise zero.
 */
extern "C" s32 resident_stream_is_bank_queued(ResidentSoundStream* stream, const void* file)
{
    DIntr();

    ResidentBankRequest* request = stream->bank_read;

    for (;;)
    {
        if (request == stream->bank_write)
        {
            break;
        }

        if (request->file == file)
        {
            if (request->waiting)
            {
                EIntr();
                return -1;
            }

            EIntr();
            return 1;
        }

        if (++request >= stream->bank_queue_end)
        {
            request = stream->bank_queue;
        }
    }

    EIntr();
    return 0;
}

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
extern "C" s32 resident_stream_queue_bank(ResidentSoundStream* stream, const void* file, s32* result, u32 arg3, u32 arg4, u32 arg5,
                             u32 arg6, u32 arg7)
{
    ResidentBankRequest* request = stream->bank_write;
    ResidentBankRequest* next = request + 1;

    if (next == stream->bank_queue_end)
    {
        next = stream->bank_queue;
    }

    if (next == stream->bank_read)
    {
        return 0;
    }

    s32 sequence_value = 0;
    s32 wave_value = 0;
    s32 wave_size = 0;
    const SoundChunk* chunk = (const SoundChunk*)file;
    const SoundFileHeader* header = 0;

    if (chunk->tag == SOUND_TAG_SEQ)
    {
        header = (const SoundFileHeader*)chunk;
        sequence_value = header->unk08;
    }
    else
    {
        if (chunk->tag == SOUND_TAG_SEQW)
        {
            header = (const SoundFileHeader*)chunk;
            sequence_value = header->unk08;
            chunk = (const SoundChunk*)((const u8*)file + chunk->size);
        }

        if (chunk->tag == SOUND_TAG_WAV)
        {
            wave_value = ((const SoundWaveChunk*)chunk)->unk0C;
            wave_size = ((const SoundWaveChunk*)chunk)->wave_size;
        }
        else
        {
            return -1;
        }
    }

    if (sequence_value >= 0xFC)
    {
        return -2;
    }

    if (wave_value >= 0xFC)
    {
        return -3;
    }

    s16 bank_id = 0;
    s8 priority = 0;

    if (header != 0)
    {
        bank_id = header->bank_id;
        priority = header->priority;
    }

    request->file = file;
    request->result = result;
    request->bank_id = bank_id;
    request->priority = priority;
    request->waiting = 0;
    request->wave_size = wave_size;
    request->unk10 = arg3;
    request->unk14 = arg4;
    request->unk18 = arg5;
    request->unk1C = arg6;
    request->unk20 = arg7;
    stream->bank_write = next;
    return 1;
}

/**
 * @brief Check whether a file is still waiting in the sequence queue.
 * @param stream Sound stream.
 * @param file File to look for.
 * @return True when a queued sequence upload uses the file.
 */
static inline bool stream_is_sequence_queued(ResidentSoundStream* stream, const void* file)
{
    DIntr();

    ResidentSequenceRequest* request = stream->sequence_read;

    for (;;)
    {
        if (request == stream->sequence_write)
        {
            break;
        }

        if (request->file == file)
        {
            EIntr();
            return true;
        }

        if (++request >= stream->sequence_queue_end)
        {
            request = stream->sequence_queue;
        }
    }

    EIntr();
    return false;
}

/**
 * @brief Find the loaded bank channel that was filled the longest ago.
 * @param stream Sound stream.
 * @return The channel, or minus one when no channel holds a bank.
 */
static inline s32 stream_find_oldest_channel(ResidentSoundStream* stream)
{
    s32 oldest = 0;
    u32 oldest_age = 0xFFFFFFFF;

    for (s32 index = 0; index < 4; index++)
    {
        if (stream->channels[index].size > 0 && stream->channels[index].age < oldest_age)
        {
            oldest_age = stream->channels[index].age;
            oldest = index;
        }
    }

    if (oldest_age == 0xFFFFFFFF)
    {
        return -1;
    }

    return oldest;
}

/**
 * @brief Pick the channel the bank at the front of the bank queue goes into.
 *
 * A bank that's already loaded keeps its channel. Otherwise it's the first run of free channels the wave data fits
 * in, and when there's none, the channel that was filled the longest ago.
 *
 * @param stream Sound stream.
 * @return The channel, or minus one when the bank can't be placed.
 */
extern "C" s32 resident_stream_pick_bank_channel(ResidentSoundStream* stream)
{
    s32 index = 0;
    s32 size;

    if (stream->bank_read->bank_id != 0)
    {
        for (index = 0; index < 4; index++)
        {
            size = stream->channels[index].size;

            if (size > 0 && (u32)stream->bank_read->bank_id == stream->channels[index].bank_id)
            {
                if (stream->bank_read->priority <= stream->channels[index].priority)
                {
                    return index;
                }

                return -1;
            }
        }
    }

    size = stream->bank_read->wave_size;

    if (size >= 4 * STREAM_CHANNEL_SIZE)
    {
        return -1;
    }

    for (index = 0; index != 4; index++)
    {
        s32 remaining = size;
        s32 next = index;
        s32 fits = 1;

        while (remaining > 0)
        {
            if (next == 4)
            {
                fits = 0;
                break;
            }

            if (stream->channels[next].size != 0)
            {
                fits = 0;
                break;
            }

            remaining -= STREAM_CHANNEL_SIZE;
            next++;
        }

        if (fits)
        {
            return index;
        }
    }

    return stream_find_oldest_channel(stream);
}

/**
 * @brief Run one step of the bank load at the front of the bank queue.
 *
 * The steps: ask the IOP which channels are in use, free the oldest bank when there's no room, upload the bank's
 * sequence, send the wave data, then record the channels the bank took and move to the next request.
 *
 * @param stream Sound stream.
 * @return Zero, or minus one when an IOP request can't be made.
 */
extern "C" s32 resident_stream_step_bank_load(ResidentSoundStream* stream)
{
    s32 index;
    ResidentBankRequest* request;
    s32 count;
    s32 remaining;
    s32 position;

    switch (stream->bank_state)
    {
        case 1:
        {
            u32 sizes[16];

            sizes[0] = stream->channels[0].size;
            sizes[1] = stream->channels[1].size;
            sizes[2] = stream->channels[2].size;
            sizes[3] = stream->channels[3].size;
            stream->bank_request = resident_stream_send_words(stream, (s32)stream->bank_status, 0, 0, sizes, 4);

            if (stream->bank_request == 0)
            {
                return -1;
            }

            stream->bank_state++;
            break;
        }

        case 2:
        {
            if (resident_sif_is_request_pending(&g_sif, stream->bank_request))
            {
                break;
            }

            s32 used = 0;

            for (index = 0; index < 4; index++)
            {
                if (stream->bank_status[index] == 0)
                {
                    if (stream->channels[index].size >= 0)
                    {
                        stream->channels[index].size = 0;
                    }
                    else if (index == 0)
                    {
                        stream->channels[index].size = 0;
                    }
                    else if (stream->channels[index - 1].size == 0)
                    {
                        stream->channels[index].size = 0;
                    }
                }

                if (stream->channels[index].size != 0)
                {
                    used++;
                }
            }

            if (used == 0)
            {
                stream->next_age = 0;
            }

            s32 channel = resident_stream_pick_bank_channel(stream);

            if (channel < 0)
            {
                stream->bank_state = 10;
                break;
            }

            if (stream->channels[channel].size != 0)
            {
                stream->bank_channel = channel;
                stream->bank_state++;
            }
            else
            {
                stream->bank_first_channel = channel;
                stream->bank_state = 5;
            }

            break;
        }

        case 3:
            stream->bank_request = resident_stream_stop(stream, (u32)stream->bank_status, 0, 0,
                                                 stream->channels[stream->bank_channel].size, 0, 0);

            if (stream->bank_request == 0)
            {
                return -1;
            }

            stream->bank_state++;
            break;

        case 4:
        {
            if (resident_sif_is_request_pending(&g_sif, stream->bank_request))
            {
                break;
            }

            stream->channels[stream->bank_channel].size = 0;

            for (index = stream->bank_channel + 1; index < 4; index++)
            {
                if (stream->channels[index].size >= 0)
                {
                    break;
                }

                stream->channels[index].size = 0;
            }

            stream->bank_first_channel = stream->bank_channel;
            stream->bank_state++;
            break;
        }

        case 5:
        {
            count = 0;
            remaining = stream->bank_read->wave_size;
            position = stream->bank_first_channel;

            if (remaining > 0)
            {
                do
                {
                    if (position == 4)
                    {
                        count = 0;
                        break;
                    }

                    if (stream->channels[position].size != 0)
                    {
                        count = 0;
                        break;
                    }

                    remaining -= STREAM_CHANNEL_SIZE;
                    position++;
                    count++;
                } while (remaining > 0);
            }

            stream->bank_channel_count = count;

            if (stream->bank_channel_count == 0)
            {
                s32 oldest = stream_find_oldest_channel(stream);

                if (oldest < 0)
                {
                    stream->bank_state = 10;
                    break;
                }

                stream->bank_channel = oldest;
                stream->bank_state = 3;
                break;
            }

            stream->bank_address = stream->channels[stream->bank_first_channel].address;
            stream->bank_slot = stream->channels[stream->bank_first_channel].slot;

            if (resident_stream_queue_sequence(stream, stream->bank_read->file, stream->bank_address, stream->bank_slot, 0, 0, 0) <= 0)
            {
                stream->bank_state = 10;
                break;
            }

            stream->bank_state++;
            break;
        }

        case 6:
        {
            request = stream->bank_read;

            if (!stream_is_sequence_queued(stream, request->file))
            {
                request->waiting = 1;
                stream->bank_state++;
            }

            break;
        }

        case 8:
        {
            if (resident_sif_is_request_pending(&g_sif, stream->bank_request))
            {
                break;
            }

            request = stream->bank_read;

            if (stream->bank_status[0] > 0)
            {
                ResidentStreamChannel* channel = &stream->channels[stream->bank_first_channel];

                channel->size = stream->bank_status[0];
                channel->bank_id = request->bank_id;
                channel->priority = request->priority;
                channel->age = stream->next_age++;

                remaining = stream->bank_channel_count - 1;

                for (position = stream->bank_first_channel + 1; remaining != 0; position++, remaining--)
                {
                    if (position >= 4)
                    {
                        break;
                    }

                    stream->channels[position].size = -1;
                }
            }

            if (request->result != 0)
            {
                *request->result = stream->bank_status[0];
            }

            request++;

            if (request == stream->bank_queue_end)
            {
                request = stream->bank_queue;
            }

            stream->bank_read = request;
            stream->bank_state = 0;
            break;
        }

        case 10:
            if (stream->bank_read->result != 0)
            {
                *stream->bank_read->result = 0;
            }

            stream->bank_read++;

            if (stream->bank_read == stream->bank_queue_end)
            {
                stream->bank_read = stream->bank_queue;
            }

            stream->bank_state = 0;
            break;
    }

    return 0;
}

/**
 * @brief Run the bank loads until one has to wait.
 * @param stream Sound stream.
 * @return Zero, or the negative result of a failed step.
 */
extern "C" s32 resident_stream_run_bank_loads(ResidentSoundStream* stream)
{
    if (stream->bank_read == stream->bank_write)
    {
        return 0;
    }

    for (;;)
    {
        s32 result = resident_stream_step_bank_load(stream);

        if (result < 0)
        {
            return result;
        }

        if (stream->bank_state != 0)
        {
            return 0;
        }

        if (stream->bank_read == stream->bank_write)
        {
            return 0;
        }

        stream->bank_state = 1;
    }
}

/**
 * @brief Handle a SIF command from the IOP for the sound stream.
 *
 * Command one acknowledges a sequence upload block and sends the next one; commands zero, two and four go to the
 * stream thread.
 *
 * @param data Command number.
 */
void ResidentSoundStream::notify(void* data)
{
    s32 command = (s32)data;

    switch (command)
    {
        case 0:
            resident_stream_thread_handle_event(this->thread, 0);
            break;

        case 1:
            this->sequence_read->remaining -= STREAM_BLOCK_SIZE;

            if (this->sequence_read->remaining <= 0)
            {
                this->sequence_state++;
            }
            else
            {
                this->sequence_read->cursor += STREAM_BLOCK_SIZE;
                resident_sif_isend_command(&g_sif, 1, (void*)this->sequence_read->cursor, (void*)this->sequence_address,
                              STREAM_BLOCK_SIZE);
            }

            break;

        case 2:
            resident_stream_thread_handle_event(this->thread, 2);
            break;

        case 4:
            resident_stream_thread_handle_event(this->thread, 4);
            break;
    }
}

/**
 * @brief Wake the stream thread, or wake it and sleep until it has run.
 * @param stream Sound stream.
 * @param no_wait Nonzero to wake the thread without waiting for it.
 * @return Zero.
 */
extern "C" s32 resident_stream_wake_thread(ResidentSoundStream* stream, s32 no_wait)
{
    if (stream->waiting)
    {
        return 0;
    }

    if (no_wait)
    {
        stream->waiting = 1;
        stream->thread->waiting_thread = 0;
        ResidentThread& thread = *stream->thread;
        resident_thread_wakeup(&thread);
        stream->waiting = 0;
    }
    else
    {
        stream->waiting = 1;
        stream->thread->waiting_thread = GetThreadId();
        ResidentThread& thread = *stream->thread;
        resident_thread_wake(&thread);
        SleepThread();
        stream->waiting = 0;
    }

    return 0;
}

/**
 * @brief Report whether an IOP request of the stream is still running.
 * @param stream Sound stream; unused.
 * @param request Request ID.
 * @return True while the request runs.
 */
extern "C" bool resident_stream_is_request_running(ResidentSoundStream* stream, s32 request)
{
    return resident_sif_is_request_pending(&g_sif, request);
}

/**
 * @brief Send sound stream command 0x17 to the IOP with one value.
 * @param stream Sound stream; unused.
 * @param arg1 Reply buffer address, or zero.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @param value Value sent in the argument block.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 resident_stream_set_volume(ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3, s32 value)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = value;
    return resident_sif_request(&g_sif, 0x17, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0x18 to the IOP.
 * @param stream Sound stream; unused.
 * @param reply Receives the reply, or null.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @return Request handle.
 */
extern "C" u32 resident_stream_command_18(ResidentSoundStream* stream, void* reply, s32 arg2, s32 arg3)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());

    return resident_sif_request(&g_sif, 0x18, reply, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0x15 to the IOP with 4 values in the argument block.
 * @param stream Sound stream; unused.
 * @param arg1 Reply buffer address, or zero.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @param handle First value.
 * @param command Second value.
 * @param first Third value.
 * @param second Fourth value.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 resident_stream_send_voice_command(ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 handle, s32 command, s32 first, s32 second)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = handle;
    arguments[1] = command;
    arguments[2] = first;
    arguments[3] = second;
    return resident_sif_request(&g_sif, 0x15, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0x14 with a count and that many words.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 resident_stream_send_words(ResidentSoundStream* stream, s32 arg1, void* callback, void* argument, const u32* values,
                             s32 count)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    *arguments++ = count;

    for (s32 i = 0; i < count; i++)
    {
        *arguments++ = *values++;
    }

    return resident_sif_request(&g_sif, 0x14, (void*)arg1, (s32)callback, (s32)argument, 0);
}

/**
 * @brief Send sound stream command 0x13 to the IOP with 1 value in the argument block.
 * @param stream Sound stream; unused.
 * @param arg1 Reply buffer address, or zero.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @param mode Value sent.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" s32 resident_stream_command_13(ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 mode)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = mode;
    return resident_sif_request(&g_sif, 0x13, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Query the stream: modes one and two read the stream thread's states, other modes go to resident_stream_command_13.
 * @param stream Sound stream.
 * @param arg1 First argument for resident_stream_command_13.
 * @param arg2 Second argument for resident_stream_command_13.
 * @param arg3 Third argument for resident_stream_command_13.
 * @param mode Query mode.
 * @return Query result.
 */
extern "C" s32 resident_stream_query(ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 mode)
{
    if (mode == 1 || mode == 2)
    {
        return resident_stream_thread_is_state_set(stream->thread, mode);
    }

    return resident_stream_command_13(stream, arg1, arg2, arg3, mode);
}

/**
 * @brief Send sound stream command 0x12 (stop); handles 1 and 2 are first checked against the stream thread.
 * @return Nonzero when the stop was sent.
 */
extern "C" s32 resident_stream_stop(ResidentSoundStream* stream, u32 arg1, void (*callback)(void*), void* argument, u32 handle, s32 mode, u32 arg6)
{
    if (handle == 1 || handle == 2)
    {
        if (!resident_stream_thread_finish_state(stream->thread, handle))
        {
            return 0;
        }
    }

    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = handle;
    arguments[1] = mode;
    arguments[2] = arg6;
    return resident_sif_request(&g_sif, 0x12, (void*)arg1, (s32)callback, (s32)argument, 0);
}

/**
 * @brief Set the stream thread's second state to one when the value is positive.
 * @param stream Sound stream.
 * @param value Value to check.
 */
extern "C" void resident_stream_set_second_state(ResidentSoundStream* stream, const s32* value)
{
    resident_stream_thread_set_second_state(stream->thread, value);
}

/**
 * @brief Set the stream thread's first state to one when the value is positive.
 * @param stream Sound stream.
 * @param value Value to check.
 * @return The value when it is positive, otherwise zero.
 */
extern "C" s32 resident_stream_set_first_state(ResidentSoundStream* stream, const s32* value)
{
    return resident_stream_thread_set_first_state(stream->thread, value);
}

/**
 * @brief Send sound stream command 0x10 with a flag in the seventh word.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" s32 resident_stream_play_flagged(void* object, s32 arg1, void* callback, void* argument, s32 arg4, s32 command, s32 arg6, s32 arg7, u32 arg8, s32 arg9, u8 arg10)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = arg4;
    arguments[1] = command;
    arguments[2] = arg6;
    arguments[3] = arg7;
    arguments[4] = arg8;
    arguments[5] = arg9;
    arguments[6] = arg10 ? 1 : 0;
    arguments[7] = 0;
    return resident_sif_request(&g_sif, 0x10, (void*)arg1, (s32)callback, (s32)argument, 0);
}

/**
 * @brief Send sound stream command 0x10 for a request slot.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" s32 resident_stream_play_slot(void* context, s32 first, void (*callback)(void*, ResidentRequestSlot*), ResidentRequestSlot* slot, s32 selected, s32 value, s32 arg3, s32 zero, u32 packed, u32 placement, u32 room)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = selected;
    arguments[1] = value;
    arguments[2] = arg3;
    arguments[3] = zero;
    arguments[4] = packed;
    arguments[5] = placement;
    arguments[6] = 0;
    arguments[7] = room;
    return resident_sif_request(&g_sif, 0x10, (void*)first, (s32)callback, (s32)slot, 0);
}

/**
 * @brief Send sound stream command 0x10 for a request slot, with one packed word.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" s32 resident_stream_play_slot_packed(void* context, s32 first, void (*callback)(void*, ResidentRequestSlot*), ResidentRequestSlot* slot, s32 selected, s32 value, s32 arg3, s32 zero, s32 packed)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = selected;
    arguments[1] = value;
    arguments[2] = arg3;
    arguments[3] = zero;
    arguments[4] = packed;
    arguments[5] = 0;
    arguments[6] = 0;
    arguments[7] = 0;
    return resident_sif_request(&g_sif, 0x10, (void*)first, (s32)callback, (s32)slot, 0);
}

/**
 * @brief Send sound stream command 0x10 with the fifth word set to 0x7F400000.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" s32 resident_stream_play_streamed(void* object, s32 arg1, void* callback, void* argument, s32 arg4, s32 command, s32 arg6, s32 arg7)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = arg4;
    arguments[1] = command;
    arguments[2] = arg6;
    arguments[3] = arg7;
    arguments[4] = 0x7F400000;
    arguments[5] = 0;
    arguments[6] = 0;
    arguments[7] = 0;
    return resident_sif_request(&g_sif, 0x10, (void*)arg1, (s32)callback, (s32)argument, 0);
}

/**
 * @brief Send sound stream command 0xC with an empty argument block.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 resident_stream_command_0c(void* object, s32 arg1, s32 arg2, s32 arg3)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    return resident_sif_request(&g_sif, 0xC, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0xB to the IOP with 4 values in the argument block.
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
extern "C" u32 resident_stream_command_0b(ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3, u32 value0, u32 value1, u32 value2,
                             u32 value3)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = value0;
    arguments[1] = value1;
    arguments[2] = value2;
    arguments[3] = value3;
    return resident_sif_request(&g_sif, 0xB, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0x7 with four values, allocating a slot buffer first when a size is given.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 resident_stream_send_setup(ResidentSoundStream* stream, u32* reply, s32 arg2, s32 arg3, s32 index, u32 arg5, u32 arg6, u32 arg7,
                  u32 arg8, u32 arg9)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = arg5;
    arguments[1] = arg6;
    arguments[2] = arg7;
    arguments[3] = arg8;

    if (arg9)
    {
        stream->slots[index] = new (0) u8[arg9];

        if (stream->slots[index])
        {
            *(u32*)stream->slots[index] = 0;
        }
    }

    return resident_sif_request(&g_sif, 0x7, reply, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0x6 to the IOP with 1 value in the argument block.
 * @param object Sound stream; unused.
 * @param arg1 Reply buffer address, or zero.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @param arg4 Value sent.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 resident_stream_set_output_mode(void* object, u32 arg1, u32 arg2, u32 arg3, u32 arg4)
{
    ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
    u32* arguments = g_sif.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = arg4;
    return resident_sif_request(&g_sif, 0x6, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Stream setup step run after resident_stream_start: send command 0x2 with the SIF buffers and keep the reply as
 * the sequence address.
 * @param stream Sound stream.
 */
extern "C" void resident_stream_setup_buffers(ResidentSoundStream* stream)
{
    u32 reply[16];
    u32 handle;

    {
        ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
        u32* arguments = g_sif.get_request_arguments();

        if (!arguments)
        {
            return;
        }

        arguments[0] = (u32)g_sif.unk2AC;
        arguments[1] = (u32)g_sif.unk2B0;
        handle = resident_sif_request(&g_sif, 0x2, reply, 0, 0, 0);
    }

    while (resident_sif_is_request_pending(&g_sif, handle))
    {
    }

    stream->sequence_address = reply[0];
}

/**
 * @brief Start the sound stream: take the SIF commands, send command 0x1, set up the four channels, then start the
 * stream thread.
 * @return Zero.
 */
extern "C" s32 resident_stream_start(ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s32 arg7, s32 arg8)
{
    u32 handle;

    {
        ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
        u32* arguments = g_sif.get_request_arguments();

        if (!arguments)
        {
            return 0;
        }

        g_sif_command_receiver = stream;
        arguments[0] = arg4;
        arguments[1] = arg5;
        arguments[2] = arg6;
        arguments[3] = arg7;
        arguments[4] = arg8;
        arguments[5] = 0;
        handle = resident_sif_request(&g_sif, 0x1, (void*)arg1, arg2, arg3, 0);
    }

    while (resident_sif_is_request_pending(&g_sif, handle))
    {
    }

    for (s32 i = 0; i < 4; i++)
    {
        u32 reply[16];
        handle = resident_stream_send_setup(stream, reply, 0, 0, i + 0x1C, 0, 0x100, 0x100, 0x10000, 0x400);

        while (resident_sif_is_request_pending(&g_sif, handle))
        {
        }

        stream->channels[i].address = reply[0];
        stream->channels[i].slot = i + 0x1C;
    }

    stream->thread->start();
    return 0;
}

/** @brief Free the queues, the loaded files and the stream thread. */
ResidentSoundStream::~ResidentSoundStream()
{
    for (s32 index = 0; index < 4; index++)
    {
        if (channels[index].slot)
        {
            operator delete(slots[channels[index].slot]);
        }
    }

    for (s32 slot = 0; slot < 32; slot++)
    {
        if (slots[slot] != 0)
        {
            operator delete(slots[slot]);
        }
    }

    delete sequence_queue;
    delete bank_queue;
    delete thread;
}

/** @brief Create the stream thread and the two request queues, with every channel and slot empty. */
ResidentSoundStream::ResidentSoundStream()
{
    unk44 = 0;

    thread = new (0) ResidentStreamThread(this);
    waiting = 0;

    for (s32 i = 0; i < 4; i++)
    {
        channels[i].size = 0;
        channels[i].slot = 0;
    }

    bank_state = 0;
    bank_queue = new (0) ResidentBankRequest[32];
    bank_read = bank_queue;
    bank_write = bank_queue;
    bank_queue_end = bank_queue + 32;
    sequence_state = 0;
    sequence_address = 0;
    sequence_queue = new (0) ResidentSequenceRequest[32];
    sequence_read = sequence_queue;
    sequence_write = sequence_queue;
    sequence_queue_end = sequence_queue + 32;

    for (s32 slot = 0; slot < 32; slot++)
    {
        slots[slot] = 0;
    }
}
