#include "include_asm.h"
#include "main/resident_00101550.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_001001E0.h"
#include "main/resident_00101260.h"
#include "main/resident_00121860.h"
#include "main/microcode_loader.h"
#include "main/lz_copy.h"
#include "main/stream_output.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"

#define SOUND_TAG_SEQ 0x20514553
#define SOUND_TAG_SEQW 0x57514553
#define SOUND_TAG_WAV 0x20564157
#define SOUND_TAG_LIP 0x2050494C
#define SOUND_TAG_LIPT 0x5450494C
#define SOUND_TAG_VSC 0x20435356
#define STREAM_BLOCK_SIZE 0x1000
#define STREAM_CHANNEL_SIZE 0x10000

extern "C" {
extern void* g_packet_queue;
extern u8 D_00148400[];
extern u8 D_0014A830[];
extern u8 D_0014A834[];
extern u8 D_0014A9E0[];
extern u8 D_0014A9E4[];

s32 DIntr(void);

s32 EIntr(void);

s32 SleepThread(void);

s32 sceGsSyncPath(s32 mode, u16 timeout);

void func_0010B510(ResidentStreamThread* thread, s32 command);

void* func_0010B810(void* memory, ResidentSoundStream* stream);

bool func_00114E00(ResidentThread* thread);

s32 func_4DC4F0(void* queue, u32 operation, u32 flags, void* packet, u32 value, void* completion);
}

/** Vtable of the running program. */
extern const ResidentDispatchTable D_0014F9F0;

/** "SLZ" and "SLE" block tags, as the decoder compares them. */
extern const char D_0014D740[];
extern const char D_0014D748[];

/** "SLZ" and "SLE" block tags, as the stream decoder compares them. */
extern const char D_0014D830[];
extern const char D_0014D838[];

/** "StorageQueue Status", the name the resource queue registers its status under. */
extern const char D_0014D750[];

/**
 * @brief Decrypt an SLE block's payload in place and retag the block as SLZ.
 *
 * Each byte has a running salt (3, 6, 9, ... wrapping at 256) subtracted and is then XORed with the next of the
 * sixteen key bytes.
 *
 * @param block Block header.
 * @param key Sixteen-byte key.
 */
static inline void decrypt_block(ResidentResourceHeader* block, unsigned __int128 key)
{
    s32 key_index = 0;
    u8* data = reinterpret_cast<u8*>(block + 1);
    const u8* key_bytes = reinterpret_cast<const u8*>(&key);
    s32 size = block->compressed_size;
    u8 salt = 3;

    for (s32 i = 0; i < size; i++)
    {
        *data = (*data - salt) ^ key_bytes[key_index];
        key_index = (key_index + 1) & 15;
        salt += 3;
        data++;
    }

    block->signature[2] = 'Z';
}

void func_00101550(void* object)
{
}

/**
 * @brief Construct the running program and register it as g_current_program.
 * @param object Program to construct.
 * @return The program.
 */
extern "C" ResidentRegisteredObject* func_00101560(ResidentRegisteredObject* object)
{
    object->dispatch = &D_0014F9F0;
    g_current_program = reinterpret_cast<ResidentProgram*>(object);
    return object;
}

/**
 * @brief Decode an LZ payload with 16-bit literals and word offsets.
 * @param decoder Resident decoder; unused.
 * @param source Compressed word stream, without its block header.
 * @param destination Output word buffer.
 * @return One when a token with zero distance ends the stream.
 */
extern "C" s32 resident_decode_lz_words(ResidentDecodeObject* decoder, const u16* source, u16* destination)
{
    s32 flags = 0;
    s32 bits = 1;

    for (;;)
    {
        if (--bits == 0)
        {
            flags = *source++;
            bits = 16;
        }
        else
        {
            flags >>= 1;
        }

        if (flags & 1)
        {
            *destination++ = *source++;
        }
        else
        {
            u16 token = *source;
            s32 distance = token & 0xFFF;
            s32 length;

            if (distance == 0)
            {
                break;
            }

            length = token >> 12;

            if (distance > 17)
            {

                switch (length)
                {
                    case 0:
                        lz_copy_halfwords_2(destination, destination - distance);
                        destination += 2;
                        break;
                    case 1:
                        lz_copy_halfwords_3(destination, destination - distance);
                        destination += 3;
                        break;
                    case 2:
                        lz_copy_halfwords_4(destination, destination - distance);
                        destination += 4;
                        break;
                    case 3:
                        lz_copy_halfwords_5(destination, destination - distance);
                        destination += 5;
                        break;
                    case 4:
                        lz_copy_halfwords_6(destination, destination - distance);
                        destination += 6;
                        break;
                    case 5:
                        lz_copy_halfwords_7(destination, destination - distance);
                        destination += 7;
                        break;
                    case 6:
                        lz_copy_halfwords_8(destination, destination - distance);
                        destination += 8;
                        break;
                    case 7:
                        lz_copy_halfwords_9(destination, destination - distance);
                        destination += 9;
                        break;
                    case 8:
                        lz_copy_halfwords_10(destination, destination - distance);
                        destination += 10;
                        break;
                    case 9:
                        lz_copy_halfwords_11(destination, destination - distance);
                        destination += 11;
                        break;
                    case 10:
                        lz_copy_halfwords_12(destination, destination - distance);
                        destination += 12;
                        break;
                    case 11:
                        lz_copy_halfwords_13(destination, destination - distance);
                        destination += 13;
                        break;
                    case 12:
                        lz_copy_halfwords_14(destination, destination - distance);
                        destination += 14;
                        break;
                    case 13:
                        lz_copy_halfwords_15(destination, destination - distance);
                        destination += 15;
                        break;
                    case 14:
                        lz_copy_halfwords_16(destination, destination - distance);
                        destination += 16;
                        break;
                    case 15:
                        lz_copy_halfwords_17(destination, destination - distance);
                        destination += 17;
                        break;
                }
            }
            else
            {
                for (s32 i = 0; i < length + 2; i++)
                {
                    *destination = *(destination - distance);
                    destination++;
                }
            }

            source++;
        }
    }

    return 1;
}

/**
 * @brief Decode an LZ payload with byte literals, back references, and runs of repeated bytes.
 * @param decoder Resident decoder; unused.
 * @param source Compressed byte stream, without its block header.
 * @param destination Output byte buffer.
 * @param decoded_size Output byte count at which decoding stops.
 * @return One after decoding.
 */
extern "C" s32 resident_decode_lz_runs(ResidentDecodeObject* decoder, const u8* source, u8* destination, u32 decoded_size)
{
    s32 flags = 0;
    s32 bits = 1;
    u8* end = destination + decoded_size;

    while (destination < end)
    {
        if (--bits == 0)
        {
            flags = *source++;
            bits = 8;
        }
        else
        {
            flags >>= 1;
        }

        if (flags & 1)
        {
            *destination++ = *source++;
        }
        else
        {
            u8 high = source[1];
            u8 low = source[0];
            s32 distance = low | ((high & 0xF) << 8);
            s32 length = (high & 0xF0) >> 4;

            if (length < 15)
            {
                if (distance > 17)
                {

                    switch (length)
                    {
                        case 0:
                            lz_copy_bytes_3(destination, destination - distance);
                            destination += 3;
                            break;
                        case 1:
                            lz_copy_bytes_4(destination, destination - distance);
                            destination += 4;
                            break;
                        case 2:
                            lz_copy_bytes_5(destination, destination - distance);
                            destination += 5;
                            break;
                        case 3:
                            lz_copy_bytes_6(destination, destination - distance);
                            destination += 6;
                            break;
                        case 4:
                            lz_copy_bytes_7(destination, destination - distance);
                            destination += 7;
                            break;
                        case 5:
                            lz_copy_bytes_8(destination, destination - distance);
                            destination += 8;
                            break;
                        case 6:
                            lz_copy_bytes_9(destination, destination - distance);
                            destination += 9;
                            break;
                        case 7:
                            lz_copy_bytes_10(destination, destination - distance);
                            destination += 10;
                            break;
                        case 8:
                            lz_copy_bytes_11(destination, destination - distance);
                            destination += 11;
                            break;
                        case 9:
                            lz_copy_bytes_12(destination, destination - distance);
                            destination += 12;
                            break;
                        case 10:
                            lz_copy_bytes_13(destination, destination - distance);
                            destination += 13;
                            break;
                        case 11:
                            lz_copy_bytes_14(destination, destination - distance);
                            destination += 14;
                            break;
                        case 12:
                            lz_copy_bytes_15(destination, destination - distance);
                            destination += 15;
                            break;
                        case 13:
                            lz_copy_bytes_16(destination, destination - distance);
                            destination += 16;
                            break;
                        case 14:
                            lz_copy_bytes_17(destination, destination - distance);
                            destination += 17;
                            break;
                    }
                }
                else
                {
                    for (s32 i = 0; i < length + 3; i++)
                    {
                        *destination = *(destination - distance);
                        destination++;
                    }
                }
            }
            else
            {
                u32 fill;
                s32 i;

                if (distance < 256)
                {
                    fill = source[2];
                    distance += 19;
                    source++;
                }
                else
                {
                    fill = distance & 0xFF;
                    distance = (distance >> 8) + 3;
                }

                fill |= fill << 8;

                if ((u32)destination & 1)
                {
                    *destination++ = fill;

                    if (distance & 1)
                    {
                        for (s32 j = 1; j < distance; j += 2)
                        {
                            *reinterpret_cast<u16*>(destination) = fill;
                            destination += 2;
                        }
                    }
                    else
                    {
                        for (i = 1; i < distance - 1; i += 2)
                        {
                            *reinterpret_cast<u16*>(destination) = fill;
                            destination += 2;
                        }

                        if (i < distance)
                        {
                            *destination++ = fill;
                        }
                    }
                }
                else
                {
                    for (i = 0; i < distance - 1; i += 2)
                    {
                        *reinterpret_cast<u16*>(destination) = fill;
                        destination += 2;
                    }

                    if (i < distance)
                    {
                        *destination++ = fill;
                    }
                }
            }

            source += 2;
        }
    }

    return 1;
}

/**
 * @brief Decode an LZ payload with byte literals and back references.
 * @param decoder Resident decoder; unused.
 * @param source Compressed byte stream, without its block header.
 * @param destination Output byte buffer.
 * @return One when a token with zero distance ends the stream.
 */
extern "C" s32 resident_decode_lz_bytes(ResidentDecodeObject* decoder, const u8* source, u8* destination)
{
    s32 flags = 0;
    s32 bits = 1;

    for (;;)
    {
        if (--bits == 0)
        {
            flags = *source++;
            bits = 8;
        }
        else
        {
            flags >>= 1;
        }

        if (flags & 1)
        {
            *destination++ = *source++;
        }
        else
        {
            u8 high = source[1];
            u8 low = source[0];
            s32 distance = low | ((high & 0xF) << 8);
            s32 length;

            if (distance == 0)
            {
                break;
            }

            length = high >> 4;

            if (distance > 18)
            {

                switch (length)
                {
                    case 0:
                        lz_copy_bytes_3(destination, destination - distance);
                        destination += 3;
                        break;
                    case 1:
                        lz_copy_bytes_4(destination, destination - distance);
                        destination += 4;
                        break;
                    case 2:
                        lz_copy_bytes_5(destination, destination - distance);
                        destination += 5;
                        break;
                    case 3:
                        lz_copy_bytes_6(destination, destination - distance);
                        destination += 6;
                        break;
                    case 4:
                        lz_copy_bytes_7(destination, destination - distance);
                        destination += 7;
                        break;
                    case 5:
                        lz_copy_bytes_8(destination, destination - distance);
                        destination += 8;
                        break;
                    case 6:
                        lz_copy_bytes_9(destination, destination - distance);
                        destination += 9;
                        break;
                    case 7:
                        lz_copy_bytes_10(destination, destination - distance);
                        destination += 10;
                        break;
                    case 8:
                        lz_copy_bytes_11(destination, destination - distance);
                        destination += 11;
                        break;
                    case 9:
                        lz_copy_bytes_12(destination, destination - distance);
                        destination += 12;
                        break;
                    case 10:
                        lz_copy_bytes_13(destination, destination - distance);
                        destination += 13;
                        break;
                    case 11:
                        lz_copy_bytes_14(destination, destination - distance);
                        destination += 14;
                        break;
                    case 12:
                        lz_copy_bytes_15(destination, destination - distance);
                        destination += 15;
                        break;
                    case 13:
                        lz_copy_bytes_16(destination, destination - distance);
                        destination += 16;
                        break;
                    case 14:
                        lz_copy_bytes_17(destination, destination - distance);
                        destination += 17;
                        break;
                    case 15:
                        lz_copy_bytes_18(destination, destination - distance);
                        destination += 18;
                        break;
                }
            }
            else
            {
                for (s32 i = 0; i < length + 3; i++)
                {
                    *destination = *(destination - distance);
                    destination++;
                }
            }

            source += 2;
        }
    }

    return 1;
}

/**
 * @brief Decrypt the selected SLE block in place and retag it as SLZ.
 * @param decoder Resident decoder; unused.
 * @param source First block header.
 * @param key Sixteen-byte key.
 * @param index Links to follow; nonpositive values select the first block.
 * @return One after decrypting, or zero when the chain ends.
 */
extern "C" s32 func_00102340(ResidentDecodeObject* decoder, ResidentResourceHeader* source, unsigned __int128 key,
                             s32 index)
{
    for (s32 block_index = 0; block_index < index; block_index++)
    {
        u32 next_offset = source->next_offset;

        if (next_offset == 0)
        {
            return 0;
        }

        source = reinterpret_cast<ResidentResourceHeader*>(reinterpret_cast<u8*>(source) + next_offset);
    }

    decrypt_block(source, key);
    return 1;
}

/**
 * @brief Decode or copy the selected SLZ/SLE block into a destination buffer.
 * @param decoder Resident decoder.
 * @param source First block header; SLE payloads are decrypted in place.
 * @param destination Destination buffer.
 * @param index Links to follow; nonpositive values select the first block.
 * @return One after decoding, or zero for an invalid header or a missing block.
 */
extern "C" s32 resident_decode_resource_block(ResidentDecodeObject* decoder, ResidentResourceHeader* source,
                                              void* destination, s32 index)
{
    s32 not_slz = memcmp(source->signature, D_0014D740, 3);
    s32 not_sle = memcmp(source->signature, D_0014D748, 3);

    if (not_slz != 0 && not_sle != 0)
    {
        return 0;
    }

    for (s32 block_index = 0; block_index < index; block_index++)
    {
        u32 next_offset = source->next_offset;

        if (next_offset == 0)
        {
            return 0;
        }

        source = reinterpret_cast<ResidentResourceHeader*>(reinterpret_cast<u8*>(source) + next_offset);
    }

    if (not_sle == 0)
    {
        decrypt_block(source, resident_get_system()->sle_key);
    }

    switch (source->compression_kind)
    {
    case 0:
        memcpy_guess(destination, source + 1, source->decoded_size);
        return 1;

    case 1:
        return resident_decode_lz_bytes(decoder, reinterpret_cast<const u8*>(source + 1),
                                        static_cast<u8*>(destination));

    case 2:
        return resident_decode_lz_runs(decoder, reinterpret_cast<const u8*>(source + 1), static_cast<u8*>(destination),
                                       source->decoded_size);

    default:
        return resident_decode_lz_words(decoder, reinterpret_cast<const u16*>(source + 1),
                                        static_cast<u16*>(destination));
    }
}

/**
 * @brief Allocate an output buffer for the selected compression block.
 *
 * Aligned allocations use the selected heap when one is set. Otherwise allocation
 * uses the default C allocator.
 *
 * @param decoder Resident decoder; unused.
 * @param source First block header.
 * @param index Links to follow; nonpositive values select the first block.
 * @param aligned Nonzero reserves space for aligning the payload to 128 bytes.
 * @return Allocation base, or null when the block or storage is unavailable.
 */
extern "C" u8* resident_allocate_decode_buffer(ResidentDecodeObject* decoder, ResidentResourceHeader* source,
                                             s32 index, s32 aligned)
{
    if (aligned && g_allocation_heap != 0)
    {
        for (s32 block_index = 0; block_index < index; block_index++)
        {
            u32 next_offset = source->next_offset;

            if (next_offset == 0)
            {
                return 0;
            }

            source = reinterpret_cast<ResidentResourceHeader*>(reinterpret_cast<u8*>(source) + next_offset);
        }

        u8* allocation = static_cast<u8*>(resident_heap_allocate(g_allocation_heap, source->decoded_size + 128));
        u32 padding = 128 - ((u32)allocation & 127);

        return static_cast<u8*>(resident_heap_resize(allocation, source->decoded_size + padding));
    }

    for (s32 block_index = 0; block_index < index; block_index++)
    {
        u32 next_offset = source->next_offset;

        if (next_offset == 0)
        {
            return 0;
        }

        source = reinterpret_cast<ResidentResourceHeader*>(reinterpret_cast<u8*>(source) + next_offset);
    }

    if (aligned)
    {
        u8* allocation = static_cast<u8*>(malloc_guess(source->decoded_size + 128));
        u32 padding = 128 - ((u32)allocation & 127);

        return static_cast<u8*>(func_0013B858(allocation, source->decoded_size + padding));
    }

    return static_cast<u8*>(malloc_guess(source->decoded_size));
}

/**
 * @brief Find a compression block by following its relative links.
 * @param decoder Resident decoder; unused.
 * @param source First block header.
 * @param index Links to follow; nonpositive values select the first block.
 * @return Selected header, or null when the chain ends.
 */
extern "C" ResidentResourceHeader* resident_find_resource_block(ResidentDecodeObject* decoder,
                                                              ResidentResourceHeader* source, s32 index)
{
    for (s32 block_index = 0; block_index < index; block_index++)
    {
        u32 next_offset = source->next_offset;

        if (next_offset == 0)
        {
            return 0;
        }

        source = reinterpret_cast<ResidentResourceHeader*>(reinterpret_cast<u8*>(source) + next_offset);
    }

    return source;
}

void func_00102A90(void* object)
{
}

/**
 * @brief Start queued work and process completed requests until no more completions are available.
 * @param queue Resident resource queue.
 * @return Nonzero while cancellation of an active read is still pending.
 */
extern "C" s32 resident_update_resource_queue(ResidentResourceQueue* queue)
{
    do
    {
        func_00102D50(queue);
    } while (func_001031C0(queue));

    return queue->cancel_pending;
}

/**
 * @brief Stop the active read and clear the archive's pending flags.
 * @param queue Resident resource queue.
 */
extern "C" void func_00102AE0(ResidentResourceQueue* queue)
{
    queue->unk30 = 0;

    ResidentArchive* archive = queue->archive;

    archive->unk12186 = 0;
    archive->disc_thread.unkAC.unk1d = 0;

    if (queue->unk2c)
    {
        func_0011BA90(queue->archive);
    }
}

/**
 * @brief Relink the first queued request of kind 4 at the head of the request list.
 * @param queue Resource queue.
 * @return True when such a request was found.
 */
extern "C" bool func_00102B30(ResidentResourceQueue* queue)
{
    ResidentInterruptLock lock;
    s32 index = queue->requests[0].next;

    for (;;)
    {
        if (index == 0)
        {
            return false;
        }

        if (queue->requests[index].request_kind == 4)
        {
            queue->requests[queue->requests[0].next].previous = index;
            queue->requests[index].next = queue->requests[queue->requests[0].next].next;
            queue->requests[0].next = index;
            queue->requests[index].previous = 0;
            return true;
        }

        index = queue->requests[index].next;
    }
}

/**
 * @brief Process completed work, then report whether any request is still queued.
 * @param queue Resident resource queue.
 * @return Nonzero when the queue is empty.
 */
extern "C" s32 resident_poll_resource_queue(ResidentResourceQueue* queue)
{
    do
    {
        func_00102D50(queue);
    } while (func_001031C0(queue));

    return queue->requests[0].next == 0;
}

/**
 * @brief Claim the archive for a kind-4 request, with interrupts off.
 * @param archive Resource archive.
 * @return True when unkAC.unk1c is set and nothing was claimed.
 */
static inline bool archive_claim_unk1d(ResidentArchive* archive)
{
    ResidentInterruptLock lock;

    if (archive->disc_thread.unkAC.unk1c)
    {
        return true;
    }

    archive->disc_thread.unkAC.unk1d = 1;
    return false;
}

/**
 * @brief Mark the archive as busy with a kind-4 request.
 * @param archive Resource archive.
 */
static inline void archive_begin_object_request(ResidentArchive* archive)
{
    archive->unk12186 = 1;
    archive->disc_thread.unkAC.unk1d = 1;
}

/**
 * @brief Start the request at the head of the queued list when the archive is idle.
 *
 * With unk2c set and a kind-4 request queued, that request is moved to the head and only it is considered: it starts
 * once nothing else is active and the archive is not reading.
 *
 * @param queue Resident resource queue.
 */
extern "C" void func_00102D50(ResidentResourceQueue* queue)
{
    if (queue->unk2c && func_00102B30(queue))
    {
        s32 index = queue->requests[0].next;

        if (index == 0)
        {
            return;
        }

        if (!queue->status && !queue->unk2e)
        {
            func_0011BC80(queue->archive);

            ResidentArchive* archive = queue->archive;

            (void)archive->disc_thread.semaphore.wait();
            u8 unk69 = archive->disc_thread.unk69;
            (void)archive->disc_thread.semaphore.signal();

            if (!unk69)
            {
                queue->unk30 = 1;
                queue->requests[index].context->notify(&queue->requests[index]);
                queue->status = 1;
                queue->requests[index].state = 1;
                queue->archive->disc_thread.unk70 = 0;
                queue->active_request = index;
            }
        }

        return;
    }

    if (queue->archive->read_busy)
    {
        return;
    }

    if (queue->status)
    {
        return;
    }

    if (queue->unk2e)
    {
        return;
    }

    s32 index = queue->requests[0].next;

    if (index == 0)
    {
        return;
    }

    switch (queue->requests[index].request_kind)
    {
    case 0:
        queue->status = 1;
        queue->requests[index].state = 1;
        break;

    case 1:
        if (func_0011D080(queue->archive, queue->requests[index].file_key))
        {
            func_0011D060(queue->archive, queue->requests[index].buffer, queue->requests[index].byte_count);
            queue->status = 1;
            queue->requests[index].state = 1;
        }

        break;

    case 2:
        if (func_0011CB00(queue->archive, queue->requests[index].file_offset, queue->requests[index].file_key))
        {
            queue->status = 1;
            queue->requests[index].state = 1;
        }

        break;

    case 3:
        if (func_0011C6E0(queue->archive) &&
            func_0011CB00(queue->archive, queue->requests[index].file_offset, queue->requests[index].file_key))
        {
            func_0011D060(queue->archive, queue->requests[index].buffer, queue->requests[index].byte_count);
            queue->status = 1;
            queue->requests[index].state = 1;
        }

        break;

    case 4:
        if (!archive_claim_unk1d(queue->archive))
        {
            queue->unk30 = 1;
            queue->status = 1;
            queue->requests[index].state = 1;
            queue->requests[index].context->notify(&queue->requests[index]);
            archive_begin_object_request(queue->archive);
            queue->archive->disc_thread.unk70 = 0;
        }

        break;
    }

    queue->active_request = index;
}

/**
 * @brief Notify the active request's completion callback, if it has one.
 * @param queue Resident resource queue.
 */
static inline void notify_completion(ResidentResourceQueue* queue)
{
    if (queue->requests[queue->active_request].completion_callback)
    {
        queue->requests[queue->active_request].completion_callback->notify(&queue->requests[queue->active_request]);
    }
}

/**
 * @brief Finish the active request once the archive is done with it.
 *
 * Reads (kinds one and three) wait for the archive's read to end, and kind four waits for unk30 to clear. A finished
 * request notifies its completion callback with the request and leaves the queued list.
 *
 * @param queue Resident resource queue.
 * @return True when a request finished, so another pass may start more work.
 */
extern "C" bool func_001031C0(ResidentResourceQueue* queue)
{
    u8 busy = queue->archive->read_busy;

    if (queue->cancel_pending && !busy)
    {
        queue->cancel_pending = 0;
    }

    if (queue->status)
    {
        switch (queue->requests[queue->active_request].request_kind)
        {
        case 0:
            queue->status = 0;
            break;

        case 2:
            queue->status = 0;
            notify_completion(queue);
            break;

        case 1:
            if (!busy)
            {
                queue->status = 0;
                notify_completion(queue);
            }

            break;

        case 3:
            if (!busy)
            {
                queue->status = 0;
                notify_completion(queue);
            }

            break;

        case 4:
            if (!queue->unk30)
            {
                queue->status = 0;
                notify_completion(queue);
            }

            break;
        }

        if (!queue->status)
        {
            ResidentInterruptLock lock;

            queue->requests[queue->requests[queue->active_request].previous].next = queue->requests[queue->active_request].next;
            queue->requests[queue->requests[queue->active_request].next].previous = queue->requests[queue->active_request].previous;
            queue->requests[queue->active_request].in_use = 0;
            return true;
        }
    }

    return false;
}

/**
 * @brief Update the object the archive passes back to the listener.
 * @param listener Resource queue listener.
 * @param context Object to update.
 */
void func_001034E0(ResidentResourceQueueListener* listener, ResidentClass14FA40* context)
{
    context->func_00104770();
}

/**
 * @brief Lower the priority of every queued request that is still positive.
 * @param queue Resident resource queue.
 */
extern "C" void func_00103510(ResidentResourceQueue* queue)
{
    s32 index = 0;

    for (;;)
    {
        index = queue->requests[index].next;

        if (index == 0)
        {
            break;
        }

        if (queue->requests[index].priority > 0)
        {
            queue->requests[index].priority--;
        }
    }
}

/** @brief Process the queue under its semaphore until nothing more can start. */
void ResidentResourceQueue::func_00104770()
{
    (void)semaphore.wait();

    if (unk30)
    {
        archive->disc_thread.unk70++;
    }

    do
    {
        func_00102D50(this);
    } while (func_001031C0(this));

    (void)semaphore.signal();
}

/**
 * @brief Process completed work, then find the first queued request matching the filters.
 * @param queue Resident resource queue.
 * @param file_key File key to match, or zero to accept any key.
 * @param buffer_address Destination address to match, or zero to accept any address.
 * @param tag Exact request tag to match, or zero to accept any tag.
 * @param byte_count Read length to match, or 0xFFFFFFFF to accept any length.
 * @param request_kind Request kind to match in the low byte, or zero to accept any kind.
 * @return Matching request address, or zero when none remains.
 */
extern "C" s32 resident_find_resource_request(ResidentResourceQueue* queue, s32 file_key, u32 buffer_address, u32 tag,
                                              u32 byte_count, s32 request_kind)
{
    do
    {
        func_00102D50(queue);
    } while (func_001031C0(queue));

    s32 index = 0;
    ResidentResourceRequest* requests = queue->requests;
    u8 kind = request_kind;

    for (;;)
    {
        index = requests[index].next;

        if (index == 0)
        {
            return 0;
        }

        if (tag != 0 && tag != requests[index].tag)
        {
            continue;
        }

        if (file_key != 0 && file_key != requests[index].file_key)
        {
            continue;
        }

        if (buffer_address != 0 && requests[index].buffer != (void*)buffer_address)
        {
            continue;
        }

        if (byte_count != 0xFFFFFFFF && byte_count != requests[index].byte_count)
        {
            continue;
        }

        if (kind != 0 && kind != requests[index].request_kind)
        {
            continue;
        }

        return (s32)&requests[index];
    }
}

/**
 * @brief Queue a request of kind four, which carries an object instead of a read.
 * @param queue Resident resource queue.
 * @param priority Lower values run first; minus one inserts at the front.
 * @param context Object the request carries.
 * @param tag Tag retained for later lookup and cancellation.
 * @param completion_callback Optional callback object notified when the request finishes.
 * @return True when queued, or false when no request slot remains.
 */
extern "C" bool func_001037E0(ResidentResourceQueue* queue, s32 priority, ResidentListener* context, u32 tag, void* completion_callback)
{
    ResidentInterruptLock lock;
    s32 index;

    for (index = 1; index < queue->request_capacity; index++)
    {
        if (!queue->requests[index].in_use)
        {
            break;
        }
    }

    if (index == queue->request_capacity)
    {
        return false;
    }

    queue->requests[index].in_use = 1;
    queue->requests[index].state = 0;
    queue->requests[index].tag = tag;
    queue->requests[index].file_key = 0;
    queue->requests[index].buffer = 0;
    queue->requests[index].priority = priority;
    queue->requests[index].request_kind = 4;
    queue->requests[index].completion_callback = static_cast<ResidentListener*>(completion_callback);
    queue->requests[index].context = context;
    queue->requests[index].byte_count = 0;
    queue->requests[index].file_offset = 0;

    if (priority == -1)
    {
        queue->requests[index].next = queue->requests[0].next;
        queue->requests[index].previous = 0;
        queue->requests[queue->requests[0].next].previous = index;
        queue->requests[0].next = index;
    }
    else
    {
        s32 next = 0;

        for (;;)
        {
            next = queue->requests[next].next;

            if (next == 0)
            {
                break;
            }

            if (priority < queue->requests[next].priority)
            {
                break;
            }
        }

        queue->requests[index].next = next;
        queue->requests[index].previous = queue->requests[next].previous;
        queue->requests[queue->requests[next].previous].next = index;
        queue->requests[next].previous = index;
    }

    return true;
}

/**
 * @brief Queue a request of kind three, which reads from an offset into the file.
 * @param queue Resident resource queue.
 * @param file_key Nonzero file key for the request.
 * @param buffer Destination buffer.
 * @param file_offset Offset applied when selecting the file.
 * @param byte_count Read length passed to the resource backend.
 * @param tag Tag retained for later lookup and cancellation.
 * @param priority Lower values run first; minus one inserts at the front.
 * @param completion_callback Optional callback object notified when the request finishes.
 * @return True when queued, or false when the file key is zero or no request slot remains.
 */
extern "C" bool func_00103AE0(ResidentResourceQueue* queue, s32 file_key, void* buffer, s32 file_offset, u32 byte_count,
                              u32 tag, s32 priority, void* completion_callback)
{
    return resident_queue_resource_request(queue, file_key, buffer, tag, priority, completion_callback, byte_count,
                                           file_offset, 3);
}

/**
 * @brief Stop the read the archive is doing for the active request, then mark the queue as changed.
 * @param queue Resident resource queue.
 */
static inline void cancel_active_read(ResidentResourceQueue* queue)
{
    if (queue->status)
    {
        switch (queue->requests[queue->active_request].request_kind)
        {
        case 0:
        case 2:
            queue->requests[queue->active_request].state = 0;
            queue->status = 0;
            break;

        case 1:
        case 3:
            queue->requests[queue->active_request].state = 0;
            func_0011C8E0(queue->archive);
            queue->cancel_pending = 1;
            queue->status = 0;
            break;

        case 4:
            break;
        }
    }

    queue->unk2e = 1;
}

/**
 * @brief Remove every matching request and cancel its active read when applicable.
 * @param queue Resident resource queue.
 * @param file_key File key to match, or zero to accept any key.
 * @param buffer_address Destination address to match, or zero to accept any address.
 * @param tag Exact request tag to match, or zero to accept any tag.
 * @param byte_count Read length to match, or 0xFFFFFFFF to accept any length.
 * @param request_kind Request kind to match in the low byte, or zero to accept any kind.
 */
extern "C" void resident_cancel_resource_requests(ResidentResourceQueue* queue, s32 file_key, u32 buffer_address,
                                                  u32 tag, u32 byte_count, s32 request_kind)
{
    s32 index = 0;
    ResidentInterruptLock lock;

    for (;;)
    {
        index = queue->requests[index].next;

        if (index == 0)
        {
            return;
        }

        if (tag != 0 && tag != queue->requests[index].tag)
        {
            continue;
        }

        if (file_key != 0 && file_key != queue->requests[index].file_key)
        {
            continue;
        }

        if (buffer_address != 0 && queue->requests[index].buffer != (void*)buffer_address)
        {
            continue;
        }

        if (byte_count != 0xFFFFFFFF && byte_count != queue->requests[index].byte_count)
        {
            continue;
        }

        if ((u8)request_kind != 0 && (u8)request_kind != queue->requests[index].request_kind)
        {
            continue;
        }

        queue->requests[queue->requests[index].previous].next = queue->requests[index].next;
        queue->requests[queue->requests[index].next].previous = queue->requests[index].previous;
        queue->requests[index].in_use = 0;

        if (queue->requests[index].state)
        {
            cancel_active_read(queue);
            queue->unk2e = 0;
        }
    }
}

/**
 * @brief Queue a resource request in priority order, then start the queue when called with interrupts enabled.
 * @param queue Resident resource queue.
 * @param file_key Nonzero file key for the request.
 * @param buffer Destination buffer.
 * @param tag Tag retained for later lookup and cancellation.
 * @param priority Lower values run first; minus one inserts at the front.
 * @param completion_callback Optional callback object notified when the request finishes.
 * @param byte_count Read length passed to the resource backend.
 * @param file_offset Offset applied when selecting a file for request kinds two and three.
 * @param request_kind Request kind.
 * @return True when queued, or false when the file key is zero or no request slot remains.
 */
extern "C" bool resident_queue_resource_request(ResidentResourceQueue* queue, s32 file_key, void* buffer, u32 tag, s32 priority,
                                     void* completion_callback, u32 byte_count, s32 file_offset, u8 request_kind)
{
    if (file_key == 0)
    {
        return false;
    }

    ResidentInterruptLock lock;
    s32 index;

    for (index = 1; index < queue->request_capacity; index++)
    {
        if (!queue->requests[index].in_use)
        {
            break;
        }
    }

    if (index == queue->request_capacity)
    {
        return false;
    }

    queue->requests[index].in_use = 1;
    queue->requests[index].state = 0;
    queue->requests[index].tag = tag;
    queue->requests[index].file_key = file_key;
    queue->requests[index].buffer = buffer;
    queue->requests[index].priority = priority;
    queue->requests[index].request_kind = request_kind;
    queue->requests[index].completion_callback = static_cast<ResidentListener*>(completion_callback);
    queue->requests[index].byte_count = byte_count;
    queue->requests[index].file_offset = file_offset;

    if (priority == -1)
    {
        queue->requests[index].next = queue->requests[0].next;
        queue->requests[index].previous = 0;
        queue->requests[queue->requests[0].next].previous = index;
        queue->requests[0].next = index;
    }
    else
    {
        s32 next = 0;

        for (;;)
        {
            next = queue->requests[next].next;

            if (next == 0)
            {
                break;
            }

            if (priority < queue->requests[next].priority)
            {
                break;
            }
        }

        queue->requests[index].next = next;
        queue->requests[index].previous = queue->requests[next].previous;
        queue->requests[queue->requests[next].previous].next = index;
        queue->requests[next].previous = index;
    }

    if (lock.was_enabled())
    {
        lock.unlock();
        func_00102D50(queue);
    }

    return true;
}

/**
 * @brief Cancel the active read, then empty the request table and its queued list.
 * @param queue Resident resource queue.
 */
extern "C" void func_001041C0(ResidentResourceQueue* queue)
{
    cancel_active_read(queue);

    ResidentInterruptLock lock;

    queue->unk2e = 0;
    queue->requests[0].next = 0;
    queue->requests[0].previous = 0;
    queue->requests[0].in_use = 1;

    for (s32 index = 1; index < queue->request_capacity; index++)
    {
        queue->requests[index].in_use = 0;
    }
}

/**
 * @brief Replace the request table with an empty one.
 * @param queue Resident resource queue.
 * @param capacity Number of entries in the new table.
 * @return One on success, or zero when the table cannot be allocated.
 */
extern "C" s32 func_00104370(ResidentResourceQueue* queue, s32 capacity)
{
    delete[] queue->requests;
    queue->requests = new (0) ResidentResourceRequest[capacity];

    if (queue->requests == 0)
    {
        return 0;
    }

    queue->request_capacity = capacity;
    func_001041C0(queue);
    return 1;
}

/**
 * @brief Register the queue's listener with the archive again.
 * @param queue Resident resource queue.
 */
extern "C" void func_001043F0(ResidentResourceQueue* queue)
{
    func_0011D320(queue->archive, &queue->listener, queue);
}

/** @brief Stop listening to the archive and free the request table. */
ResidentResourceQueue::~ResidentResourceQueue()
{
    func_0011D320(archive, 0, 0);
    delete[] requests;
}

/** @brief Create the semaphore, register with the archive and allocate a 256-entry request table. */
ResidentResourceQueue::ResidentResourceQueue()
{
    requests = 0;
    status = 0;
    unk2e = 0;
    archive = resident_get_archive(resident_get_system());
    cancel_pending = 0;
    unk30 = 0;
    unk2c = 0;

    SemaParam param;
    param.initCount = 1;
    param.maxCount = 1;
    semaphore.id = CreateSema(&param);

    func_0011D320(archive, &listener, this);
    func_00121860(D_0014D750, &status, 1);
    func_00104370(this, 0x100);
}

/**
 * @brief Return the object's kind.
 * @return Three.
 */
s32 ResidentClass14FA40::func_00104730()
{
    return 3;
}

/** @brief Destroy the object through its virtual destructor. */
void ResidentClass14FA40::func_00104740()
{
    delete this;
}

/** @brief Update the object; the base does nothing. */
void ResidentClass14FA40::func_00104770()
{
}

void ResidentClass14FA40::func_00104780()
{
}

/**
 * @brief Decode the next part of an LZ word stream.
 * @param decoder Resident decoder; unused.
 * @param stream Stream state: the cursors and the flag bits carried between calls.
 * @param limit Number of output bytes to decode before returning.
 * @return Nonzero once the stream has ended.
 */
extern "C" s32 func_00104790(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit)
{
    u16* start;
    u16* destination;
    const u16* source;
    s32 bits;
    s32 flags;

    if (stream->unk19 != 0)
    {
        return 1;
    }

    start = reinterpret_cast<u16*>(stream->destination);
    source = reinterpret_cast<const u16*>(stream->source);
    bits = stream->flag_count;
    flags = stream->flags;
    destination = start;

    for (;;)
    {
        if (reinterpret_cast<u8*>(destination) - reinterpret_cast<u8*>(start) >= limit)
        {
            break;
        }

        if (--bits == 0)
        {
            flags = *source++;
            bits = 16;
        }
        else
        {
            flags >>= 1;
        }

        if (flags & 1)
        {
            *destination++ = *source++;
        }
        else
        {
            u16 token = *source;
            s32 distance = token & 0xFFF;
            s32 length;

            if (distance == 0)
            {
                stream->unk19 = 1;
                break;
            }

            length = token >> 12;
            source++;

            if (distance > 17)
            {
                switch (length)
                {
                    case 0:
                        lz_copy_halfwords_2(destination, destination - distance);
                        destination += 2;
                        break;
                    case 1:
                        lz_copy_halfwords_3(destination, destination - distance);
                        destination += 3;
                        break;
                    case 2:
                        lz_copy_halfwords_4(destination, destination - distance);
                        destination += 4;
                        break;
                    case 3:
                        lz_copy_halfwords_5(destination, destination - distance);
                        destination += 5;
                        break;
                    case 4:
                        lz_copy_halfwords_6(destination, destination - distance);
                        destination += 6;
                        break;
                    case 5:
                        lz_copy_halfwords_7(destination, destination - distance);
                        destination += 7;
                        break;
                    case 6:
                        lz_copy_halfwords_8(destination, destination - distance);
                        destination += 8;
                        break;
                    case 7:
                        lz_copy_halfwords_9(destination, destination - distance);
                        destination += 9;
                        break;
                    case 8:
                        lz_copy_halfwords_10(destination, destination - distance);
                        destination += 10;
                        break;
                    case 9:
                        lz_copy_halfwords_11(destination, destination - distance);
                        destination += 11;
                        break;
                    case 10:
                        lz_copy_halfwords_12(destination, destination - distance);
                        destination += 12;
                        break;
                    case 11:
                        lz_copy_halfwords_13(destination, destination - distance);
                        destination += 13;
                        break;
                    case 12:
                        lz_copy_halfwords_14(destination, destination - distance);
                        destination += 14;
                        break;
                    case 13:
                        lz_copy_halfwords_15(destination, destination - distance);
                        destination += 15;
                        break;
                    case 14:
                        lz_copy_halfwords_16(destination, destination - distance);
                        destination += 16;
                        break;
                    case 15:
                        lz_copy_halfwords_17(destination, destination - distance);
                        destination += 17;
                        break;
                }
            }
            else
            {
                for (s32 i = 0; i < length + 2; i++)
                {
                    *destination = *(destination - distance);
                    destination++;
                }
            }
        }
    }

    stream->destination = reinterpret_cast<u8*>(destination);
    stream->source = reinterpret_cast<u8*>(const_cast<u16*>(source));
    stream->flag_count = bits;
    stream->flags = flags;
    return stream->unk19;
}

/**
 * @brief Decode the next part of an LZ stream with runs.
 * @param decoder Resident decoder; unused.
 * @param stream Stream state: the cursors and the flag bits carried between calls.
 * @param limit Number of output bytes to decode before returning.
 * @return One once the output is full, otherwise zero.
 */
extern "C" s32 func_00104C90(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit)
{
    u8* start;
    u8* destination;
    u8* source;
    u8* end;
    s32 bits;
    s32 flags;
    s32 distance;
    s32 value;

    if (stream->unk19 != 0)
    {
        return 1;
    }

    start = stream->destination;
    source = stream->source;
    end = stream->destination_end;
    bits = stream->flag_count;
    flags = stream->flags;
    destination = start;

    while (destination < end)
    {
        if (destination - start >= limit)
        {
            break;
        }

        if (--bits == 0)
        {
            flags = *source++;
            bits = 8;
        }
        else
        {
            flags >>= 1;
        }

        if (flags & 1)
        {
            *destination++ = *source++;
        }
        else
        {
            u8 high = source[1];
            u8 low = source[0];

            distance = low | ((high & 0xF) << 8);
            value = (high & 0xF0) >> 4;

            if (value < 15)
            {
                if (distance > 17)
                {
                    switch (value)
                    {
                        case 0:
                            lz_copy_bytes_3(destination, destination - distance);
                            destination += 3;
                            break;
                        case 1:
                            lz_copy_bytes_4(destination, destination - distance);
                            destination += 4;
                            break;
                        case 2:
                            lz_copy_bytes_5(destination, destination - distance);
                            destination += 5;
                            break;
                        case 3:
                            lz_copy_bytes_6(destination, destination - distance);
                            destination += 6;
                            break;
                        case 4:
                            lz_copy_bytes_7(destination, destination - distance);
                            destination += 7;
                            break;
                        case 5:
                            lz_copy_bytes_8(destination, destination - distance);
                            destination += 8;
                            break;
                        case 6:
                            lz_copy_bytes_9(destination, destination - distance);
                            destination += 9;
                            break;
                        case 7:
                            lz_copy_bytes_10(destination, destination - distance);
                            destination += 10;
                            break;
                        case 8:
                            lz_copy_bytes_11(destination, destination - distance);
                            destination += 11;
                            break;
                        case 9:
                            lz_copy_bytes_12(destination, destination - distance);
                            destination += 12;
                            break;
                        case 10:
                            lz_copy_bytes_13(destination, destination - distance);
                            destination += 13;
                            break;
                        case 11:
                            lz_copy_bytes_14(destination, destination - distance);
                            destination += 14;
                            break;
                        case 12:
                            lz_copy_bytes_15(destination, destination - distance);
                            destination += 15;
                            break;
                        case 13:
                            lz_copy_bytes_16(destination, destination - distance);
                            destination += 16;
                            break;
                        case 14:
                            lz_copy_bytes_17(destination, destination - distance);
                            destination += 17;
                            break;
                    }
                }
                else
                {
                    for (s32 i = 0; i < value + 3; i++)
                    {
                        *destination = *(destination - distance);
                        destination++;
                    }
                }
            }
            else
            {
                s32 i;

                if (distance < 256)
                {
                    value = source[2];
                    distance += 19;
                    source++;
                }
                else
                {
                    value = distance & 0xFF;
                    distance = (distance >> 8) + 3;
                }

                value |= value << 8;

                if ((u32)destination & 1)
                {
                    *destination++ = value;

                    if (distance & 1)
                    {
                        for (s32 j = 1; j < distance; j += 2)
                        {
                            *reinterpret_cast<u16*>(destination) = value;
                            destination += 2;
                        }
                    }
                    else
                    {
                        for (i = 1; i < distance - 1; i += 2)
                        {
                            *reinterpret_cast<u16*>(destination) = value;
                            destination += 2;
                        }

                        if (i < distance)
                        {
                            *destination++ = value;
                        }
                    }
                }
                else
                {
                    for (i = 0; i < distance - 1; i += 2)
                    {
                        *reinterpret_cast<u16*>(destination) = value;
                        destination += 2;
                    }

                    if (i < distance)
                    {
                        *destination++ = value;
                    }
                }
            }

            source += 2;
        }
    }

    stream->destination = destination;
    stream->source = source;
    stream->flag_count = bits;
    stream->flags = flags;

    if (destination >= stream->destination_end)
    {
        stream->unk19 = 1;
        return 1;
    }

    return 0;
}

/**
 * @brief Decode the next part of an LZ byte stream.
 * @param decoder Resident decoder; unused.
 * @param stream Stream state: the cursors and the flag bits carried between calls.
 * @param limit Number of output bytes to decode before returning.
 * @return Nonzero once the stream has ended.
 */
extern "C" s32 func_00105210(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit)
{
    u8* start;
    u8* destination;
    u8* source;
    s32 bits;
    s32 flags;

    if (stream->unk19 != 0)
    {
        return 1;
    }

    start = stream->destination;
    source = stream->source;
    bits = stream->flag_count;
    flags = stream->flags;
    destination = start;

    for (;;)
    {
        if (destination - start >= limit)
        {
            break;
        }

        if (--bits == 0)
        {
            flags = *source++;
            bits = 8;
        }
        else
        {
            flags >>= 1;
        }

        if (flags & 1)
        {
            *destination++ = *source++;
        }
        else
        {
            u8 high = source[1];
            u8 low = source[0];
            s32 distance = low | ((high & 0xF) << 8);
            s32 length;

            if (distance == 0)
            {
                stream->unk19 = 1;
                break;
            }

            length = (high & 0xF0) >> 4;
            source += 2;

            if (distance > 18)
            {

                switch (length)
                {
                    case 0:
                        lz_copy_bytes_3(destination, destination - distance);
                        destination += 3;
                        break;
                    case 1:
                        lz_copy_bytes_4(destination, destination - distance);
                        destination += 4;
                        break;
                    case 2:
                        lz_copy_bytes_5(destination, destination - distance);
                        destination += 5;
                        break;
                    case 3:
                        lz_copy_bytes_6(destination, destination - distance);
                        destination += 6;
                        break;
                    case 4:
                        lz_copy_bytes_7(destination, destination - distance);
                        destination += 7;
                        break;
                    case 5:
                        lz_copy_bytes_8(destination, destination - distance);
                        destination += 8;
                        break;
                    case 6:
                        lz_copy_bytes_9(destination, destination - distance);
                        destination += 9;
                        break;
                    case 7:
                        lz_copy_bytes_10(destination, destination - distance);
                        destination += 10;
                        break;
                    case 8:
                        lz_copy_bytes_11(destination, destination - distance);
                        destination += 11;
                        break;
                    case 9:
                        lz_copy_bytes_12(destination, destination - distance);
                        destination += 12;
                        break;
                    case 10:
                        lz_copy_bytes_13(destination, destination - distance);
                        destination += 13;
                        break;
                    case 11:
                        lz_copy_bytes_14(destination, destination - distance);
                        destination += 14;
                        break;
                    case 12:
                        lz_copy_bytes_15(destination, destination - distance);
                        destination += 15;
                        break;
                    case 13:
                        lz_copy_bytes_16(destination, destination - distance);
                        destination += 16;
                        break;
                    case 14:
                        lz_copy_bytes_17(destination, destination - distance);
                        destination += 17;
                        break;
                    case 15:
                        lz_copy_bytes_18(destination, destination - distance);
                        destination += 18;
                        break;
                }
            }
            else
            {
                for (s32 i = 0; i < length + 3; i++)
                {
                    *destination = *(destination - distance);
                    destination++;
                }
            }
        }
    }

    stream->destination = destination;
    stream->source = source;
    stream->flag_count = bits;
    stream->flags = flags;
    return stream->unk19;
}

/**
 * @brief Decode the next part of a block started by func_00105770.
 * @param decoder Resident decoder.
 * @param stream Stream state.
 * @param limit Most bytes a stored block copies in this step.
 * @return Nonzero once the whole block is decoded.
 */
extern "C" s32 func_00105680(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit)
{
    switch (stream->compression_kind)
    {
    case 0:
        if (stream->remaining < limit)
        {
            limit = stream->remaining;
        }

        memcpy_guess(stream->destination, stream->source, limit);
        stream->destination += limit;
        stream->source += limit;
        stream->remaining -= limit;

        if (stream->remaining == 0)
        {
            return 1;
        }

        return 0;

    case 1:
        return func_00105210(decoder, stream, limit);

    case 2:
        return func_00104C90(decoder, stream, limit);

    default:
        return func_00104790(decoder, stream, limit);
    }
}

/**
 * @brief Start decoding the selected SLZ/SLE block in steps; SLE payloads are decrypted in place first.
 * @param decoder Resident decoder.
 * @param stream Receives the stream state.
 * @param source First block header.
 * @param destination Destination buffer.
 * @param index Links to follow; nonpositive values select the first block.
 * @return One when the stream is ready, or zero for an invalid header or a missing block.
 */
extern "C" s32 func_00105770(ResidentDecodeObject* decoder, ResidentDecodeStream* stream,
                             ResidentResourceHeader* source, u8* destination, s32 index)
{
    s32 not_slz = memcmp(source->signature, D_0014D830, 3);
    s32 not_sle = memcmp(source->signature, D_0014D838, 3);

    if (not_slz != 0 && not_sle != 0)
    {
        return 0;
    }

    for (s32 block_index = 0; block_index < index; block_index++)
    {
        u32 next_offset = source->next_offset;

        if (next_offset == 0)
        {
            return 0;
        }

        source = reinterpret_cast<ResidentResourceHeader*>(reinterpret_cast<u8*>(source) + next_offset);
    }

    if (not_sle == 0)
    {
        ResidentSystem* system = resident_get_system();

        func_00102340(func_001012B0(resident_get_system()), source, system->sle_key, 0);
    }

    stream->compression_kind = source->compression_kind;
    stream->flags = 0;
    stream->unk19 = 0;
    stream->flag_count = 1;
    stream->destination = destination;
    stream->source = reinterpret_cast<u8*>(source + 1);
    stream->remaining = source->decoded_size;
    stream->destination_end = destination + source->decoded_size;
    return 1;
}

/**
 * @brief Read four values from the sound stream's IOP side.
 * @param stream Sound stream.
 * @param x Receives the first value.
 * @param y Receives the second value.
 * @param z Receives the third value.
 * @param w Receives the fourth value.
 */
extern "C" void func_001058C0(ResidentSoundStream* stream, u32* x, u32* y, u32* z, u32* w)
{
    u32 reply[16];
    u32 handle;

    {
        ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
        handle = func_0010C200(&D_001CC590, 0xE, reply, 0, 0, 0);
    }

    while (func_0010C0E0(&D_001CC590, handle))
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
extern "C" u32 func_00105AE0(ResidentSoundStream* stream, void* reply, s32 arg2, s32 arg3)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());

    return func_0010C200(&D_001CC590, 0x1C, reply, arg2, arg3, 0);
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
extern "C" u32 func_00105BF0(ResidentSoundStream* stream, s32 value0, s32 value1, s32 value2, s32 value3)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = value0;
    arguments[1] = value1;
    arguments[2] = value2;
    arguments[3] = value3;
    return func_0010C200(&D_001CC590, 0x1B, 0, 0, 0, 0);
}

/**
 * @brief Send sound stream command 0x19 to the IOP with an empty argument block.
 * @param stream Sound stream; unused.
 * @param reply Receives the reply, or null.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 func_00105DD0(ResidentSoundStream* stream, void* reply, s32 arg2, s32 arg3)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    return func_0010C200(&D_001CC590, 0x19, reply, arg2, arg3, 0);
}

/**
 * @brief Read the word at offset 0x14 of a SEQW file header.
 * @param stream Sound stream; unused.
 * @param file Sound file.
 * @return The word, or zero when the file isn't a SEQW file.
 */
extern "C" u32 func_00105F90(ResidentSoundStream* stream, const SoundFileHeader* file)
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
extern "C" void* func_00105FB0(ResidentSoundStream* stream, s32 entry, s32 slot)
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
extern "C" s32 func_001060C0(ResidentSoundStream* stream, const void* file)
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
extern "C" s32 func_00106160(ResidentSoundStream* stream, const void* file, u32 arg2, s32 slot, s32* result, u32 arg5,
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
    if (!func_0010C0E0(&D_001CC590, stream->sequence_request))
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
extern "C" s32 func_00106240(ResidentSoundStream* stream)
{
    switch (stream->sequence_state)
    {
    case 1:
        stream->sequence_request = func_00108800(stream, (s32)&stream->sequence_status, 0, 0, stream->sequence_address,
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
        func_0010BFA0(&D_001CC590, 1, (void*)stream->sequence_read->cursor, (void*)stream->sequence_address,
                      STREAM_BLOCK_SIZE);
        break;

    case 6:
        stream->sequence_request = func_00108640(stream, (s32)&stream->sequence_status, 0, 0);

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
extern "C" s32 func_001065B0(ResidentSoundStream* stream)
{
    if (stream->sequence_read == stream->sequence_write)
    {
        return 0;
    }

    for (;;)
    {
        s32 result = func_00106240(stream);

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
extern "C" u8* func_00106640(ResidentSoundStream* stream, u32 arg1, u32 arg2)
{
    ResidentBankRequest* request = stream->bank_read;

    stream->bank_request = func_00108000(stream, (s32)stream->bank_status, (void (*)(void*, ResidentRequestSlot*))arg1,
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
 * @return One when the file is queued, minus one when it is queued and waiting for func_00106640, otherwise zero.
 */
extern "C" s32 func_001066D0(ResidentSoundStream* stream, const void* file)
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
extern "C" s32 func_00106780(ResidentSoundStream* stream, const void* file, s32* result, u32 arg3, u32 arg4, u32 arg5,
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
extern "C" s32 func_001068C0(ResidentSoundStream* stream)
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
extern "C" s32 func_00106A50(ResidentSoundStream* stream)
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
            stream->bank_request = func_00107730(stream, (s32)stream->bank_status, 0, 0, sizes, 4);

            if (stream->bank_request == 0)
            {
                return -1;
            }

            stream->bank_state++;
            break;
        }

        case 2:
        {
            if (func_0010C0E0(&D_001CC590, stream->bank_request))
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

            s32 channel = func_001068C0(stream);

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
            stream->bank_request = func_00107B60(stream, (u32)stream->bank_status, 0, 0,
                                                 stream->channels[stream->bank_channel].size, 0, 0);

            if (stream->bank_request == 0)
            {
                return -1;
            }

            stream->bank_state++;
            break;

        case 4:
        {
            if (func_0010C0E0(&D_001CC590, stream->bank_request))
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

            if (func_00106160(stream, stream->bank_read->file, stream->bank_address, stream->bank_slot, 0, 0, 0) <= 0)
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
            if (func_0010C0E0(&D_001CC590, stream->bank_request))
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
extern "C" s32 func_00107020(ResidentSoundStream* stream)
{
    if (stream->bank_read == stream->bank_write)
    {
        return 0;
    }

    for (;;)
    {
        s32 result = func_00106A50(stream);

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
 * @param stream Sound stream.
 * @param command Command number.
 */
extern "C" void func_001070B0(ResidentSoundStream* stream, s32 command)
{
    switch (command)
    {
        case 0:
            func_0010B510(stream->thread, 0);
            break;

        case 1:
            stream->sequence_read->remaining -= STREAM_BLOCK_SIZE;

            if (stream->sequence_read->remaining <= 0)
            {
                stream->sequence_state++;
            }
            else
            {
                stream->sequence_read->cursor += STREAM_BLOCK_SIZE;
                func_0010BE80(&D_001CC590, 1, (void*)stream->sequence_read->cursor, (void*)stream->sequence_address,
                              STREAM_BLOCK_SIZE);
            }

            break;

        case 2:
            func_0010B510(stream->thread, 2);
            break;

        case 4:
            func_0010B510(stream->thread, 4);
            break;
    }
}

/**
 * @brief Wake the stream thread, or wake it and sleep until it has run.
 * @param stream Sound stream.
 * @param no_wait Nonzero to wake the thread without waiting for it.
 * @return Zero.
 */
extern "C" s32 func_001071A0(ResidentSoundStream* stream, s32 no_wait)
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
        func_00114DD0(&thread);
        stream->waiting = 0;
    }
    else
    {
        stream->waiting = 1;
        stream->thread->waiting_thread = GetThreadId();
        ResidentThread& thread = *stream->thread;
        func_00114E00(&thread);
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
extern "C" bool func_00107230(ResidentSoundStream* stream, s32 request)
{
    return func_0010C0E0(&D_001CC590, request);
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
extern "C" u32 func_00107250(ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3, s32 value)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = value;
    return func_0010C200(&D_001CC590, 0x17, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0x18 to the IOP.
 * @param stream Sound stream; unused.
 * @param reply Receives the reply, or null.
 * @param arg2 Command argument.
 * @param arg3 Command argument.
 * @return Request handle.
 */
extern "C" u32 func_00107420(ResidentSoundStream* stream, void* reply, s32 arg2, s32 arg3)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());

    return func_0010C200(&D_001CC590, 0x18, reply, arg2, arg3, 0);
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
extern "C" u32 func_00107530(ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 handle, s32 command, s32 first, s32 second)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = handle;
    arguments[1] = command;
    arguments[2] = first;
    arguments[3] = second;
    return func_0010C200(&D_001CC590, 0x15, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0x14 with a count and that many words.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 func_00107730(ResidentSoundStream* stream, s32 arg1, void* callback, void* argument, const u32* values,
                             s32 count)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    *arguments++ = count;

    for (s32 i = 0; i < count; i++)
    {
        *arguments++ = *values++;
    }

    return func_0010C200(&D_001CC590, 0x14, (void*)arg1, (s32)callback, (s32)argument, 0);
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
extern "C" s32 func_00107940(ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 mode)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = mode;
    return func_0010C200(&D_001CC590, 0x13, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Query the stream: modes one and two read the stream thread's states, other modes go to func_00107940.
 * @param stream Sound stream.
 * @param arg1 First argument for func_00107940.
 * @param arg2 Second argument for func_00107940.
 * @param arg3 Third argument for func_00107940.
 * @param mode Query mode.
 * @return Query result.
 */
extern "C" s32 func_00107B10(ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 mode)
{
    if (mode == 1 || mode == 2)
    {
        return func_00109FE0(stream->thread, mode);
    }

    return func_00107940(stream, arg1, arg2, arg3, mode);
}

/**
 * @brief Send sound stream command 0x12 (stop); handles 1 and 2 are first checked against the stream thread.
 * @return Nonzero when the stop was sent.
 */
extern "C" s32 func_00107B60(ResidentSoundStream* stream, u32 arg1, void (*callback)(void*), void* argument, u32 handle, s32 mode, u32 arg6)
{
    if (handle == 1 || handle == 2)
    {
        if (!func_0010A000(stream->thread, handle))
        {
            return 0;
        }
    }

    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = handle;
    arguments[1] = mode;
    arguments[2] = arg6;
    return func_0010C200(&D_001CC590, 0x12, (void*)arg1, (s32)callback, (s32)argument, 0);
}

/**
 * @brief Set the stream thread's second state to one when the value is positive.
 * @param stream Sound stream.
 * @param value Value to check.
 */
extern "C" void func_00107D90(ResidentSoundStream* stream, const s32* value)
{
    func_0010A080(stream->thread, value);
}

/**
 * @brief Set the stream thread's first state to one when the value is positive.
 * @param stream Sound stream.
 * @param value Value to check.
 * @return The value when it is positive, otherwise zero.
 */
extern "C" s32 func_00107DB0(ResidentSoundStream* stream, const s32* value)
{
    return func_0010A0B0(stream->thread, value);
}

/**
 * @brief Send sound stream command 0x10 with a flag in the seventh word.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" s32 func_00107DD0(void* object, s32 arg1, void* callback, void* argument, s32 arg4, s32 command, s32 arg6, s32 arg7, u32 arg8, s32 arg9, u8 arg10)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

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
    return func_0010C200(&D_001CC590, 0x10, (void*)arg1, (s32)callback, (s32)argument, 0);
}

/**
 * @brief Send sound stream command 0x10 for a request slot.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" s32 func_00108000(void* context, s32 first, void (*callback)(void*, ResidentRequestSlot*), ResidentRequestSlot* slot, s32 selected, s32 value, s32 arg3, s32 zero, u32 packed, u32 placement, u32 room)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

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
    return func_0010C200(&D_001CC590, 0x10, (void*)first, (s32)callback, (s32)slot, 0);
}

/**
 * @brief Send sound stream command 0x10 for a request slot, with one packed word.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" s32 func_00108220(void* context, s32 first, void (*callback)(void*, ResidentRequestSlot*), ResidentRequestSlot* slot, s32 selected, s32 value, s32 arg3, s32 zero, s32 packed)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

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
    return func_0010C200(&D_001CC590, 0x10, (void*)first, (s32)callback, (s32)slot, 0);
}

/**
 * @brief Send sound stream command 0x10 with the fifth word set to 0x7F400000.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" s32 func_00108430(void* object, s32 arg1, void* callback, void* argument, s32 arg4, s32 command, s32 arg6, s32 arg7)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

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
    return func_0010C200(&D_001CC590, 0x10, (void*)arg1, (s32)callback, (s32)argument, 0);
}

/**
 * @brief Send sound stream command 0xC with an empty argument block.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 func_00108640(void* object, s32 arg1, s32 arg2, s32 arg3)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    return func_0010C200(&D_001CC590, 0xC, (void*)arg1, arg2, arg3, 0);
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
extern "C" u32 func_00108800(ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3, u32 value0, u32 value1, u32 value2,
                             u32 value3)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = value0;
    arguments[1] = value1;
    arguments[2] = value2;
    arguments[3] = value3;
    return func_0010C200(&D_001CC590, 0xB, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Send sound stream command 0x7 with four values, allocating a slot buffer first when a size is given.
 * @return Request handle, or zero when no reply slot is free.
 */
extern "C" u32 func_00108A00(ResidentSoundStream* stream, u32* reply, s32 arg2, s32 arg3, s32 index, u32 arg5, u32 arg6, u32 arg7,
                  u32 arg8, u32 arg9)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

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

    return func_0010C200(&D_001CC590, 0x7, reply, arg2, arg3, 0);
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
extern "C" u32 func_00108C40(void* object, u32 arg1, u32 arg2, u32 arg3, u32 arg4)
{
    ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
    u32* arguments = D_001CC590.get_request_arguments();

    if (!arguments)
    {
        return 0;
    }

    arguments[0] = arg4;
    return func_0010C200(&D_001CC590, 0x6, (void*)arg1, arg2, arg3, 0);
}

/**
 * @brief Stream setup step run after func_00109000: send command 0x2 with the SIF buffers and keep the reply as
 * the sequence address.
 * @param stream Sound stream.
 */
extern "C" void func_00108E10(ResidentSoundStream* stream)
{
    u32 reply[16];
    u32 handle;

    {
        ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
        u32* arguments = D_001CC590.get_request_arguments();

        if (!arguments)
        {
            return;
        }

        arguments[0] = (u32)D_001CC590.unk2AC;
        arguments[1] = (u32)D_001CC590.unk2B0;
        handle = func_0010C200(&D_001CC590, 0x2, reply, 0, 0, 0);
    }

    while (func_0010C0E0(&D_001CC590, handle))
    {
    }

    stream->sequence_address = reply[0];
}

/**
 * @brief Start the sound stream: take the SIF commands, send command 0x1, set up the four channels, then start the
 * stream thread.
 * @return Zero.
 */
extern "C" s32 func_00109000(ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s32 arg7, s32 arg8)
{
    u32 handle;

    {
        ResidentSemaphoreLock lock(D_001CC590.get_request_semaphore());
        u32* arguments = D_001CC590.get_request_arguments();

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
        handle = func_0010C200(&D_001CC590, 0x1, (void*)arg1, arg2, arg3, 0);
    }

    while (func_0010C0E0(&D_001CC590, handle))
    {
    }

    for (s32 i = 0; i < 4; i++)
    {
        u32 reply[16];
        handle = func_00108A00(stream, reply, 0, 0, i + 0x1C, 0, 0x100, 0x100, 0x10000, 0x400);

        while (func_0010C0E0(&D_001CC590, handle))
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

    // TODO: The stream thread's constructor is still assembly under a C name, so I've written its new expression out
    // by hand.
    void* memory = operator new(sizeof(ResidentStreamThread), 0);

    if (memory != 0)
    {
        memory = func_0010B810(memory, this);
    }

    thread = static_cast<ResidentStreamThread*>(memory);
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
extern "C" s32 func_00109510(ResidentStreamDma* dma, s32 ring, s32 count, float* output)
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
extern "C" void func_00109800(ResidentStreamDma* dma)
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
            func_00109D50(dma->owner);
            break;
        }
    }
}

/**
 * @brief Start the VIF1 DMA chain for the transfer's current phase.
 * @param dma Stream DMA transfer.
 * @param channel DMA channel; unused.
 */
extern "C" void func_00109BE0(ResidentStreamDma* dma, u32 channel)
{
    switch (dma->phase)
    {
        case 1:
            *D1_QWC = 0;
            *D1_TADR = (u32)D_00148400 & 0x0FFFFFFF;
            *D_STAT = D_STAT_CIS1;
            *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
            break;

        case 2:
            *D1_QWC = 0;
            *D1_TADR = (u32)D_0014A9E0 & 0x0FFFFFFF;
            *D_STAT = D_STAT_CIS1;
            *D1_CHCR = DMA_CHCR_START | DMA_CHCR_MODE_CHAIN | DMA_CHCR_DIR_FROM_MEMORY;
            break;
    }
}

/**
 * @brief Queue the packet that follows a finished stream DMA transfer.
 * @param dma Stream DMA transfer.
 * @param channel DMA channel; unused.
 */
extern "C" void func_00109C80(ResidentStreamDma* dma, u32 channel)
{
    func_4DC4F0(g_packet_queue, 5, 0, dma, 0, 0);
}

/**
 * @brief Set the stream thread's unk110 to two while holding its semaphore.
 * @param thread Stream thread.
 */
extern "C" void func_00109CB0(ResidentStreamThread* thread)
{
    (void)thread->semaphore.wait();
    thread->stream->thread->unk110 = 2;
    (void)thread->semaphore.signal();
}

/**
 * @brief Account for one finished 4 KiB block and queue the next VIF1 transfer, or swap buffers once both are full.
 * @param thread Stream thread.
 */
extern "C" void func_00109D50(ResidentStreamThread* thread)
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
    return func_00109510(thread->dma, ring, count, output);
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
extern "C" s32 func_00109FE0(ResidentStreamThread* thread, s32 which)
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
extern "C" s32 func_0010A000(ResidentStreamThread* thread, s32 which)
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
