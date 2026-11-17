#include "include_asm.h"
#include "main/stream_output.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "main/sif.h"
#include "main/system.h"
#include "main/utility.h"

extern "C" {
extern void* g_packet_queue;
extern u8 g_stream_upload_chain[];

s32 sceGsSyncPath(s32 mode, u16 timeout);

s32 func_4DC4F0(void* queue, u32 operation, u32 flags, void* packet, u32 value, void* completion);
}

/**
 * @brief Get the address just past one of the stream DMA transfer's rings.
 * @param dma Stream DMA transfer.
 * @param ring Ring index, 0 or 1.
 * @return End of the ring.
 */
static inline u32 ring_end(const ResidentStreamDma* dma, s32 ring)
{
    return dma->ring_start[ring] + dma->ring_size;
}

/**
 * @brief Take samples out of one of the stream DMA transfer's rings and convert them to floats.
 * @param dma Stream DMA transfer.
 * @param ring Ring index, 0 or 1.
 * @param count Number of samples to take; a multiple of four.
 * @param output Receives the samples.
 * @return One when the samples were taken, or zero when the ring doesn't hold that many yet.
 */
extern "C" s32 resident_stream_dma_read_samples(ResidentStreamDma* dma, s32 ring, s32 count, float* output)
{
    DIntr();

    u32 read = dma->ring_read[ring];
    u32 end = read + count * sizeof(s32);

    // TODO: Only matches when the loop below reuses this variable for its count; my guess at the original.
    s32 limit = ring_end(dma, ring);

    if (end >= (u32)limit)
    {
        end -= dma->ring_size;

        if (read <= dma->ring_write[ring])
        {
            EIntr();
            return 0;
        }
    }
    else if (dma->ring_write[ring] < end && read <= dma->ring_write[ring])
    {
        EIntr();
        return 0;
    }

    s32 index = 0;
    const s32* source = (const s32*)read;
    limit = count / 4;

    for (; index < limit; index++)
    {
        output[0] = source[0];
        output[1] = source[1];
        output[2] = source[2];
        output[3] = source[3];
        source += 4;
        output += 4;
    }

    dma->ring_read[ring] = end;
    EIntr();
    return 1;
}

/**
 * @brief Get the address just past a ring that starts at a given address.
 * @param dma Stream DMA transfer.
 * @param start Start of the ring.
 * @return End of the ring.
 */
static inline u32 ring_end_from(const ResidentStreamDma* dma, u32 start)
{
    return start + dma->ring_size;
}

/**
 * @brief Take one decoded channel out of VU1 memory once the stream's VIF1 transfer has run.
 *
 * Copies the channel's 4 KiB table back to the stream thread, packs the 4 KiB of samples that follow down to
 * halfwords for the output buffer, and adds the unpacked samples to the channel's ring when there is room. After
 * the first channel it queues the transfer for the second; after the second it hands over to the stream thread.
 *
 * @param dma Stream DMA transfer.
 */
extern "C" void resident_stream_dma_take_channel(ResidentStreamDma* dma)
{
    while (sceGsSyncPath(1, 0) & 0x1C)
    {
    }

    s32 i;
    const unsigned __int128* source;
    unsigned __int128* output = (unsigned __int128*)dma->output;

    switch (dma->phase)
    {
        case 1:
        {
            unsigned __int128* samples = (unsigned __int128*)((u32)dma->owner->unkF0 | UNCACHED_SEGMENT);

            source = (const unsigned __int128*)0x1100E000;

            for (i = 0; i < 0x40; i++)
            {
                *samples++ = *source++;
                *samples++ = *source++;
                *samples++ = *source++;
                *samples++ = *source++;
            }

            const unsigned __int128* block = source;

            for (i = 0; i < 0x40; i++)
            {
                unsigned __int128 low = *source++;
                unsigned __int128 high = *source++;

                *output++ = ee_pack_halfwords(high, low);
                low = *source++;
                high = *source++;
                *output++ = ee_pack_halfwords(high, low);
            }

            dma->output = (u32)output;

            if (dma->ring_start[0] != 0)
            {
                u32 end = dma->ring_write[0] + 0x1000;
                bool fits = true;

                if (end >= ring_end_from(dma, dma->ring_start[0]))
                {
                    end -= dma->ring_size;

                    if (dma->ring_write[0] < dma->ring_read[0])
                    {
                        fits = false;
                    }
                }
                else if (end >= dma->ring_read[0] && dma->ring_write[0] < dma->ring_read[0])
                {
                    fits = false;
                }

                if (fits)
                {
                    unsigned __int128* ring = (unsigned __int128*)dma->ring_write[0];

                    for (i = 0; i < 0x40; i++)
                    {
                        *ring++ = *block++;
                        *ring++ = *block++;
                        *ring++ = *block++;
                        *ring++ = *block++;
                    }

                    dma->ring_write[0] = end;
                }
            }

            dma->phase = 2;
            g_vif1_dma_queue->push(dma);
            break;
        }

        case 2:
        {
            unsigned __int128* samples = (unsigned __int128*)((u32)dma->owner->unkF4 | UNCACHED_SEGMENT);

            source = (const unsigned __int128*)0x1100E000;

            for (i = 0; i < 0x40; i++)
            {
                *samples++ = *source++;
                *samples++ = *source++;
                *samples++ = *source++;
                *samples++ = *source++;
            }

            const unsigned __int128* block = source;

            for (i = 0; i < 0x40; i++)
            {
                unsigned __int128 low = *source++;
                unsigned __int128 high = *source++;

                *output++ = ee_pack_halfwords(high, low);
                low = *source++;
                high = *source++;
                *output++ = ee_pack_halfwords(high, low);
            }

            if (dma->ring_start[1] != 0)
            {
                u32 end = dma->ring_write[1] + 0x1000;
                bool fits = true;

                if (end >= ring_end_from(dma, dma->ring_start[1]))
                {
                    end -= dma->ring_size;

                    if (dma->ring_write[1] < dma->ring_read[1])
                    {
                        fits = false;
                    }
                }
                else if (end >= dma->ring_read[1] && dma->ring_write[1] < dma->ring_read[1])
                {
                    fits = false;
                }

                if (fits)
                {
                    unsigned __int128* ring = (unsigned __int128*)dma->ring_write[1];

                    for (i = 0; i < 0x40; i++)
                    {
                        *ring++ = *block++;
                        *ring++ = *block++;
                        *ring++ = *block++;
                        *ring++ = *block++;
                    }

                    dma->ring_write[1] = end;
                }
            }

            dma->output = (u32)output;
            resident_stream_dma_finish_block(dma->owner);
            break;
        }
    }
}

/**
 * @brief Start the VIF1 DMA chain for the transfer's current phase.
 * @param channel DMA channel; unused.
 */
void ResidentStreamDma::submit_dma(u32 channel)
{
    switch (this->phase)
    {
        case 1:
            *D1_QWC = 0;
            *D1_TADR = (u32)g_stream_upload_chain & 0x0FFFFFFF;
            *D_STAT = D_STAT_CIS1;
            *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
            break;

        case 2:
            *D1_QWC = 0;
            *D1_TADR = (u32)g_stream_output_tag_1 & 0x0FFFFFFF;
            *D_STAT = D_STAT_CIS1;
            *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
            break;
    }
}

/**
 * @brief Queue the packet that follows a finished stream DMA transfer.
 * @param channel DMA channel; unused.
 */
void ResidentStreamDma::complete_dma(u32 channel)
{
    func_4DC4F0(g_packet_queue, 5, 0, this, 0, 0);
}

/**
 * @brief Set the stream thread's unk110 to two while holding its semaphore.
 */
void ResidentStreamThread::notify(void* data)
{
    (void)this->semaphore.wait();
    stream->thread->unk110 = 2;
    (void)this->semaphore.signal();
}

/**
 * @brief Account for one finished 4 KiB block and queue the next VIF1 transfer, or swap buffers once both are full.
 * @param thread Stream thread.
 */
extern "C" void resident_stream_dma_finish_block(ResidentStreamThread* thread)
{
    u8* input_cursor = thread->input_cursor;

    thread->output_cursor += 0x1000;
    thread->input_cursor = input_cursor + 0x1000;
    thread->output_pending[thread->output_half]--;

    if (thread->output_pending[thread->output_half] != 0)
    {
        start_output_dma(thread);
    }
    else
    {
        thread->input_ready[thread->input_half] = 1;

        if (thread->output_half == 0)
        {
            thread->output_half = 1;
            thread->output_cursor = thread->output_buffers[1] + 0x80;
        }
        else
        {
            thread->output_half = 0;
            thread->output_cursor = thread->output_buffers[0] + 0x80;
        }

        if (thread->input_half == 0)
        {
            thread->input_half = 1;
            thread->input_cursor = thread->input_buffers[1] + 0x80;
        }
        else
        {
            thread->input_half = 0;
            thread->input_cursor = thread->input_buffers[0] + 0x80;
        }

        thread->unkB9 = 0;
        thread->dma->phase = 0;
        g_microcode_loader->unk06 = 0;
    }
}

/**
 * @brief Take samples out of one of the stream thread's sample rings and convert them to floats.
 * @param thread Stream thread.
 * @param ring Ring index, 0 or 1.
 * @param count Number of samples to take; a multiple of four.
 * @param output Receives the samples.
 * @return One when the samples were taken, or zero when the ring doesn't hold that many yet.
 */
extern "C" s32 resident_stream_read_samples(ResidentStreamThread* thread, s32 ring, s32 count, float* output)
{
    return resident_stream_dma_read_samples(thread->dma, ring, count, output);
}

/**
 * @brief Set the two sample rings of the stream DMA transfer and empty them.
 * @param thread Stream thread.
 * @param first_ring Start of the first ring.
 * @param second_ring Start of the second ring.
 * @param ring_size Size of each ring in bytes.
 */
extern "C" void resident_stream_set_sample_rings(ResidentStreamThread* thread, u32 first_ring, u32 second_ring, u32 ring_size)
{
    ResidentStreamDma* dma = thread->dma;

    DIntr();
    dma->ring_start[0] = first_ring;
    dma->ring_start[1] = second_ring;
    dma->ring_size = ring_size;
    dma->ring_read[0] = first_ring;
    dma->ring_read[1] = second_ring;
    dma->ring_write[0] = first_ring;
    dma->ring_write[1] = second_ring;
    EIntr();
}

/**
 * @brief Get how many times the playing stream has looped.
 * @param thread Stream thread.
 * @return Loop count, or zero when nothing is playing.
 */
extern "C" s32 resident_stream_get_loop_count(ResidentStreamThread* thread)
{
    if (thread->first_state == 1)
    {
        return thread->loop_count;
    }

    return 0;
}

/**
 * @brief Report whether the stream's two channels hold mid and side instead of left and right.
 * @param thread Stream thread.
 * @return The stream header's mid/side flag.
 */
extern "C" s32 resident_stream_is_mid_side(const ResidentStreamThread* thread)
{
    return thread->mid_side;
}

/**
 * @brief Report whether one of the stream thread's two states is set.
 * @param thread Stream thread.
 * @param which One for the first state; any other value selects the second.
 * @return Nonzero when the selected state is nonzero.
 */
extern "C" s32 resident_stream_thread_is_state_set(ResidentStreamThread* thread, s32 which)
{
    s32 state;

    if (which == 1)
    {
        state = thread->first_state;
    }
    else
    {
        state = thread->second_state;
    }

    return state != 0;
}

/**
 * @brief Move one of the stream thread's two states to two when it is one or two.
 * @param thread Stream thread.
 * @param which One for the first state, two for the second.
 * @return One when the state was moved, otherwise zero.
 */
extern "C" s32 resident_stream_thread_finish_state(ResidentStreamThread* thread, s32 which)
{
    switch (which)
    {
        case 1:
            if (thread->first_state > 0 && thread->first_state < 3)
            {
                thread->first_state = 2;
                return 1;
            }

            break;

        case 2:
            if (thread->second_state > 0 && thread->second_state < 3)
            {
                thread->second_state = 2;
                return 1;
            }

            break;
    }

    return 0;
}

typedef struct ResidentHelperObjectB0
{
    u8 unk00[0xB0];
    u32 unkB0;
} ResidentHelperObjectB0;

s32 resident_stream_thread_set_second_state(void* object, const s32* value)
{
    if (*value > 0)
    {
        ((ResidentHelperObjectB0*)object)->unkB0 = 1;
        return *value;
    }

    return 0;
}

typedef struct ResidentHelperObjectAC110
{
    u8 unk00[0xAC];
    u32 unkAC;
    u8 unkB0[0x60];
    u32 unk110;
} ResidentHelperObjectAC110;

s32 resident_stream_thread_set_first_state(void* object, const s32* value)
{
    if (*value > 0)
    {
        ((ResidentHelperObjectAC110*)object)->unk110 = 1;
        ((ResidentHelperObjectAC110*)object)->unkAC = 1;
        return *value;
    }

    return 0;
}

extern "C" {

/** Size and address fields of the DMA tags that send the thread's two 0x1000-byte tables, in the two stream chains. */
extern u16 g_stream_table_tags_0[];
extern u32* g_stream_table_tag_addresses_0[];
extern u16 g_stream_table_tags_1[];
extern u32* g_stream_table_tag_addresses_1[];

/** Three words in the VU1 stream programs that the constructor patches, and the address each one gets. */
extern u32* const g_stream_vu1_patch_sites[3];
extern const u32 g_stream_vu1_patch_targets[3];

void resident_stream_thread_send_chunk(ResidentStreamThread* stream, s32 value);

typedef struct ResidentByteAndWordResetB730
{
    u8 pad00[0x78];
    u8 unk78[4];
    u32 unk7C;
    u32 unk80;
    u32 unk84;
} ResidentByteAndWordResetB730;

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
s32 resident_stream_thread_request_5(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 value,
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
    stream->loop_count = 0;
    return resident_stream_play_streamed(stream->stream, arg1, callback, argument, 0, -5, arg6, 0);
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
s32 resident_stream_thread_request_4(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 arg6)
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
    stream->loop_count = 0;
    return resident_stream_play_streamed(stream->stream, arg1, callback, argument, 0, -4, arg6, 0);
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
s32 resident_stream_thread_request_3(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, u32* entry, s32 arg6)
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
    stream->loop_count = 0;
    return resident_stream_play_streamed(stream->stream, arg1, callback, argument, 0, -3, arg6, 0);
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
s32 resident_stream_thread_request_2(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, s32 arg6)
{
    if (stream->second_state != 0)
    {
        return 0;
    }

    stream->unk74 = 0;
    stream->unkBE = 0;
    return resident_stream_play_streamed(stream->stream, arg1, callback, argument, 0, -2, arg6, 0);
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
s32 resident_stream_thread_request_1(ResidentStreamThread* stream, s32 arg1, void* callback, void* argument, s32 value, s32 arg6,
                  u8 arg10)
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
    stream->loop_count = 0;
    return resident_stream_play_flagged(stream->stream, arg1, callback, argument, 0, -1, arg6, 0, (0x7F << 24) | (0x40 << 16), 0,
                         arg10);
}

/**
 * @brief Append bytes to the ring, first moving unread data back to the start of the ring when the end is too close.
 * @param stream Streaming thread.
 * @param data Bytes to append.
 * @param size Number of bytes in data.
 * @return Number of bytes appended.
 */
s32 resident_stream_thread_append(ResidentStreamThread* stream, const void* data, s32 size)
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
s32 resident_stream_thread_write_words(ResidentStreamThread* stream, const u32* words, s32 size)
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

/**
 * @brief Second streaming pass: send the full ring half to the IOP when it asks for data, then ask for more with
 * request 0xA.
 * @param stream Streaming thread.
 * @return Zero, or -1 when no reply slot is free for the request.
 */
s32 resident_stream_thread_send_pass(ResidentStreamThread* stream)
{
    if (stream->second_state == 4)
    {
        stream->second_state = 0;
    }

    if (stream->second_state == 2)
    {
        stream->second_state = 4;
    }

    if (stream->unk74 != 0)
    {
        stream->unkB7 = 0;
        stream->unk74 = 0;
        void* destination = *(void**)((u32)stream->unk70 | UNCACHED_SEGMENT);

        if (destination != 0 && stream->unk78[stream->unk7A] != 0)
        {
            resident_sif_send_command(&g_sif, 2, stream->unk7C, destination, 0x2000);
            stream->unk78[stream->unk7A] = 0;

            if (stream->unk7A == 0)
            {
                stream->unk7A = 1;
                stream->unk7C = stream->unk88;
            }
            else
            {
                stream->unk7A = 0;
                stream->unk7C = stream->unk84;
            }
        }
    }

    if (stream->second_state != 0 && stream->unkB7 == 0)
    {
        ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
        u32* arguments = g_sif.get_request_arguments();

        if (!arguments)
        {
            return -1;
        }

        arguments[0] = (u32)stream->unk70;

        if (resident_sif_request(&g_sif, 0xA, 0, 0, 0, 0))
        {
            stream->unkB7 = 1;
        }
    }

    return 0;
}

/**
 * @brief Read one word of the status block the IOP keeps for the stream.
 * @param stream Stream thread.
 * @param offset Offset of the word.
 * @return The word.
 */
static inline u32 stream_status(ResidentStreamThread* stream, s32 offset)
{
    return *(u32*)((u32)(stream->unk24 + offset) | UNCACHED_SEGMENT);
}

/**
 * @brief Hand the filled output half to the input side and start its VIF1 transfer.
 * @param stream Stream thread.
 */
static inline void start_output(ResidentStreamThread* stream)
{
    stream->unk54[stream->input_half] = stream->output_pending[stream->output_half];
    stream->unk5C[stream->input_half] = (void*)stream->unk34[stream->output_half];
    stream->unkB9 = 1;
    stream->log_cursor = stream->unkCC;
    start_output_dma(stream);
}

/**
 * @brief Run the first streaming pass.
 *
 * Applies a pending stop, sends the next header block, then reads the IOP's status block: it feeds the stream from
 * memory or from the disc, starts the output transfer when a half is ready, and tells the IOP what it did with
 * request 9.
 *
 * @param stream Stream thread.
 * @return Zero, or minus one when no request slot is free.
 */
s32 resident_stream_thread_receive_pass(ResidentStreamThread* stream)
{
    (void)stream->semaphore.wait();

    if (stream->first_state == 2 && stream->unk28 != 0 && stream->unkB4[0] == 0
        && stream_status(stream, 0x20) == 0 && stream->unkB8 == 0)
    {
        stream->first_state = 3;

        switch (stream->unk110)
        {
            case 1:
                stream->unk110 = 0;
                break;

            case 2:
                if (stream->unk94 == 0)
                {
                    resident_stop_resource_read(resident_system_get_resource_queue(resident_get_system()));
                }

                stream->unkB4[1] = 0;
                stream->unk110 = 3;
                break;

            default:
                if (stream->unk94 == 0 && stream->unkB4[1] != 0)
                {
                    resident_stop_resource_read(resident_system_get_resource_queue(resident_get_system()));
                    resident_cancel_resource_requests(resident_system_get_resource_queue(resident_get_system()), 0, 0,
                                                      0, 0xFFFFFFFF, 4);
                    stream->unkB4[1] = 0;
                }

                stream->unk110 = 3;
                break;
        }
    }

    if (stream->dma != 0 && stream->dma->phase != 0)
    {
        (void)stream->semaphore.signal();
        return 0;
    }

    if (stream->unk28 != 0 && stream_status(stream, 0x24) == 0)
    {
        resident_stream_thread_send_chunk(stream, 0);
    }

    if (stream->input_ready[stream->unk4A] != 0 && stream->unkB8 == 0 && stream->unkBD == 0
        && stream->first_state > 0 && stream->first_state < 3)
    {
        stream->unkBB = 0;
        // TODO: Only matches with the size in a local; my guess is the original named it.
        s32 size = 0x1040;
        u32* header = (u32*)((u32)stream->unk4C | UNCACHED_SEGMENT);
        header[0] = 1;
        header[1] = 0;
        header[2] = stream->unkCC[stream->unkBB];
        header[3] = --stream->unk54[stream->unk4A];
        stream->unkB8 = 1;
        resident_sif_send_command(&g_sif, 0, stream->unk4C, stream->unk5C[stream->unk4A], size);
    }

    if (stream->unk28 != 0)
    {
        stream->unkB4[2] = 0;
        stream->unk28 = 0;
        stream->mid_side = stream_status(stream, 0x28);
        stream->loop_count = stream_status(stream, 0x2C);
        stream->unkC4 = stream_status(stream, 0x30) != 0;

        if (stream->first_state == 4)
        {
            stream->first_state = 0;
        }

        if (stream->first_state > 0 && stream->first_state < 3)
        {
            u32 destination;
            s32 value;

            if (stream->unk94 != 0)
            {
                s32 available = stream_status(stream, 0xC);

                if (stream->unkB4[0] != 0)
                {
                    u32 current = stream_status(stream, 0x8);

                    if (current != stream->unk98 || available == 0)
                    {
                        stream->unkB4[1] = 0;
                        stream->unkB4[0] = 0;

                        if (stream->unk96 != 0)
                        {
                            stream->unk96--;

                            if (stream->unk96 == 0)
                            {
                                stream->unk94 = 0;
                                stream->unk96 = 1;
                            }
                        }
                    }
                }
                else if (stream->unkB4[1] == 0)
                {
                    value = stream_status(stream, 0x4);

                    if (value >= 0)
                    {
                        destination = stream_status(stream, 0x8);

                        if (stream->unk95 == 0)
                        {
                            s32 offset = stream->unkA0;

                            resident_sif_send_command(&g_sif, 3, (u8*)stream->unk9C + offset, (void*)destination, 0x4E000);
                            stream->unkA0 += 0x4E000;

                            if (stream->unkA8 != 0)
                            {
                                if (stream->unkA0 == stream->unkA8)
                                {
                                    stream->unkA0 = stream->unkA4;
                                }
                            }

                            stream->unk98 = destination;
                            stream->unkB4[1] = 1;
                            stream->unkB4[0] = 1;
                        }
                        else
                        {
                            value = stream->unk80 - stream->unk7C;
                            value &= ~0x3F;

                            if (available < value)
                            {
                                value = available;
                            }

                            resident_sif_send_command(&g_sif, 3, stream->unk7C, (void*)destination, value);
                            stream->unk7C += value;

                            if (value != 0)
                            {
                                stream->unk98 = destination;
                                stream->unk110 = 2;
                                stream->unkB4[1] = 1;
                            }
                        }
                    }
                }
            }
            else if (stream->unkB4[0] != 0)
            {
                if (stream_status(stream, 0x10) == 0)
                {
                    resident_stop_resource_read(resident_system_get_resource_queue(resident_get_system()));
                    stream->unkB4[1] = 0;
                    stream->unkB4[0] = 0;
                }
            }
            else if (stream->unkB4[1] == 0)
            {
                value = stream_status(stream, 0x4);

                if (value >= 0)
                {
                    if (resident_queue_object_request(resident_system_get_resource_queue(resident_get_system()), value, stream, 3, 0))
                    {
                        stream->unkB4[1] = 1;
                    }
                }
            }

            if (stream->output_pending[stream->output_half] != 0 && stream->input_ready[stream->input_half] == 0
                && stream->unkB9 == 0)
            {
                start_output(stream);
            }
        }

        if (stream->first_state > 0 && stream->first_state < 3)
        {
            if (stream_status(stream, 0x14) == 1)
            {
                resident_stream_stop(stream->stream, 0, 0, 0, 1, 0, 0);
                stream->first_state = 2;
            }
        }
    }

    if (stream->first_state != 0 && stream->unkB4[2] == 0)
    {
        ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
        u32* arguments = g_sif.get_request_arguments();

        if (!arguments)
        {
            (void)stream->semaphore.signal();
            return -1;
        }

        arguments[0] = (u32)stream->unk20;

        if (stream->output_pending[stream->unk1B] == 0)
        {
            arguments[1] = 1;
        }
        else
        {
            arguments[1] = 0;
        }

        arguments[2] = stream->unk110;

        if (stream->unk110 != 0)
        {
            arguments[2] = stream->unk110;
        }

        switch (stream->unk110)
        {
            case 1:
                if (stream->unk94 == 0 || stream->unk96 != 0)
                {
                    arguments[5] = stream->unk90;
                }

                break;

            case 2:
                stream->unkB4[0] = 1;
                break;

            case 3:
                stream->first_state = 4;
                break;
        }

        if (resident_sif_request(&g_sif, 9, 0, 0, 0, 0))
        {
            stream->unkB4[2] = 1;
            stream->unk110 = 0;
        }
    }

    (void)stream->semaphore.signal();
    return 0;
}

/** @brief Body of the streaming thread: on every wakeup run both streaming passes, then wake the waiting thread, if any. */
void ResidentStreamThread::run()
{
    for (;;)
    {
        do
        {
            resident_thread_sleep();
            resident_stream_thread_receive_pass(this);
            resident_stream_thread_send_pass(this);
        } while (!waiting_thread);

        WakeupThread(waiting_thread);
        waiting_thread = 0;
    }
}

/**
 * @brief Handle a notification from the IOP side of the stream.
 * @param stream Streaming thread.
 * @param event 0 when a receive block arrived, 2 to set unk74, 4 to send the next chunk.
 */
void resident_stream_thread_handle_event(ResidentStreamThread* stream, s32 event)
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
            resident_stream_thread_send_chunk(stream, 1);
            break;
    }
}

/**
 * @brief Send the next 0x1000-byte chunk of the current send block to the IOP behind a four-word header, or, once the
 * block has no chunks left, release it and switch to the other send block. Nothing happens while it is already running.
 * @param stream Streaming thread.
 * @param value Unused.
 */
void resident_stream_thread_send_chunk(ResidentStreamThread* stream, s32 value)
{
    if (stream->unkBA)
    {
        return;
    }

    stream->unkBA = 1;

    if (stream->unkB8)
    {
        if (stream->unk54[stream->unk4A])
        {
            stream->unk4C += 0x1000;
            stream->unkBB++;
            u32* header = (u32*)((u32)stream->unk4C | UNCACHED_SEGMENT);
            header[0] = 1;
            header[1] = 0;
            header[2] = stream->unkCC[stream->unkBB];
            header[3] = --stream->unk54[stream->unk4A];
            resident_sif_isend_command(&g_sif, 0, stream->unk4C, stream->unk5C[stream->unk4A], 0x1040);
        }
        else
        {
            stream->input_ready[stream->unk4A] = 0;

            if (stream->unk4A == 0)
            {
                stream->unk4A = 1;
                stream->unk4C = stream->input_buffers[1] + 0x40;
            }
            else
            {
                stream->unk4A = 0;
                stream->unk4C = stream->input_buffers[0] + 0x40;
            }

            stream->unkB8 = 0;
        }
    }

    stream->unkBA = 0;
}

/** Clear bytes at 0x78-0x7B and copy the word at 0x84 to offsets 0x7C and 0x80. */
void resident_stream_thread_reset_blocks(void* object)
{
    ResidentByteAndWordResetB730* receiver = (ResidentByteAndWordResetB730*)object;
    receiver->unk78[0] = 0;
    receiver->unk78[1] = 0;
    receiver->unk78[2] = 0;
    receiver->unk78[3] = 0;
    receiver->unk7C = receiver->unk84;
    receiver->unk80 = receiver->unk84;
}

/** @brief Free the buffers and stop the thread. */
ResidentStreamThread::~ResidentStreamThread()
{
    delete allocation;
    delete dma;
}

/**
 * @brief Allocate the buffers, clear the streaming state, patch the VU1 programs and create the DMA transfer.
 * @param stream Sound stream that owns the thread.
 */
ResidentStreamThread::ResidentStreamThread(ResidentSoundStream* stream)
{
    allocation = new (0) u8[0x122C0];
    u32 base = ((u32)allocation + 0x7F) & ~0x7F;

    output_buffers[0] = (u8*)base;
    output_buffers[1] = (u8*)(base + 0x3080);
    unk44 = (u8*)(base + 0x6100);
    reset_receive_blocks(this);
    input_buffers[0] = (u8*)(base + 0x6100);
    input_buffers[1] = (u8*)(base + 0x9180);
    unk6C = (u8*)(base + 0xC200);
    reset_send_blocks(this);
    resident_thread_create(&static_cast<ResidentThread&>(*this), 0x2B, 0x4000);

    unkF0 = (u32*)((u8*)(base + 0xC200));
    unkF4 = (u32*)((u8*)(base + 0xD200));
    unk70 = (u8*)(base + 0xE200);
    unk74 = 0;
    unk84 = (u8*)((u32)((u8*)(base + 0xE240)) | UNCACHED_SEGMENT);
    unk88 = (u8*)((u32)((u8*)(base + 0x10240)) | UNCACHED_SEGMENT);
    unk8C = (u8*)((u32)((u8*)(base + 0x12240)) | UNCACHED_SEGMENT);
    reset_ring(this);
    first_state = 0;
    second_state = 0;
    unk110 = 0;
    unkB4[0] = 0;
    unkB4[1] = 0;
    unkB4[2] = 0;
    unkB7 = 0;
    unkB8 = 0;
    unkB9 = 0;
    mid_side = -1;
    unkBD = 0;
    unkBE = 0;
    loop_count = 0;
    unkBA = 0;

    for (s32 i = 0; i < 8; i++)
    {
        ((u32*)unkCC)[i] = 0;
    }

    for (s32 i = 0; i < 0x400; i++)
    {
        unkF0[i] = 0;
        unkF4[i] = 0;
    }

    g_stream_table_tags_0[0] = 0x100;
    g_stream_table_tag_addresses_0[0] = unkF0;
    g_stream_table_tags_1[0] = 0x100;
    g_stream_table_tag_addresses_1[0] = unkF4;

    u32 i = 0;

    do
    {
        *g_stream_vu1_patch_sites[i] = (g_stream_vu1_patch_targets[i] >> 3) | 0x14000000;
        i++;
    } while (i < 3);

    FlushCache(0);
    this->stream = stream;
    dma = new (0) ResidentStreamDma(this);
    dma->phase = 0;
    semaphore.create(1, 1);
    waiting_thread = 0;
    unk104 = 0;
}
}
