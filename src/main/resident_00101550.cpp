#include "include_asm.h"
#include "main/resident_00101550.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_001001E0.h"
#include "main/resident_00101260.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"

#define D1_CHCR (*(volatile u32*)0x10009000)
#define D1_QWC (*(volatile u32*)0x10009020)
#define D1_TADR (*(volatile u32*)0x10009030)
#define D_STAT (*(volatile u32*)0x1000E010)

#define D_STAT_CHANNEL_1 0x2
#define D_CHCR_FROM_MEMORY 0x1
#define D_CHCR_CHAIN_MODE 0x4
#define D_CHCR_START 0x100

/** Chunk tags of the sound files, as they read in memory. */
#define SOUND_TAG_SEQ 0x20514553
#define SOUND_TAG_SEQW 0x57514553
#define SOUND_TAG_WAV 0x20564157

/** Sequence uploads are sent in 4 KiB blocks. */
#define STREAM_BLOCK_SIZE 0x1000

extern "C" {
extern void* g_packet_queue;
extern u8 D_00148400[];
extern u8 D_0014A9E0[];
s32 DIntr(void);
s32 EIntr(void);
s32 SleepThread(void);
void func_0010B510(ResidentStreamThread* thread, s32 command);
bool func_00114E00(ResidentThread* thread);
u32 func_0010C200(ResidentSif* sif, s32 command, void* reply, s32 arg3, s32 arg4, s32 arg5);
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
INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_decode_lz_words);

/**
 * @brief Decode an LZ payload with byte literals, back references, and runs of repeated bytes.
 * @param decoder Resident decoder; unused.
 * @param source Compressed byte stream, without its block header.
 * @param destination Output byte buffer.
 * @param decoded_size Output byte count at which decoding stops.
 * @return One after decoding.
 */
INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_decode_lz_runs);

/**
 * @brief Decode an LZ payload with byte literals and back references.
 * @param decoder Resident decoder; unused.
 * @param source Compressed byte stream, without its block header.
 * @param destination Output byte buffer.
 * @return One when a token with zero distance ends the stream.
 */
INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_decode_lz_bytes);

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
    archive->unkc9 = 0;

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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00102D50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001031C0);

/**
 * @brief Update the object the archive passes back to the listener.
 * @param listener Resource queue listener.
 * @param context Object to update.
 */
void func_001034E0(ResidentResourceQueueListener* listener, ResidentClass14FA40* context)
{
    context->func_00104770();
}

/** @brief Lower the priority of every queued request that is still positive. @param queue Resident resource queue. */
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

/**
 * @brief Process the queue under its semaphore until nothing more can start.
 * @param queue Resource queue.
 */
extern "C" void func_00103580(ResidentResourceQueue* queue)
{
    (void)queue->semaphore.wait();

    if (queue->unk30)
    {
        queue->archive->unk70++;
    }

    do
    {
        func_00102D50(queue);
    } while (func_001031C0(queue));

    (void)queue->semaphore.signal();
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001037E0);

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
 * @return One when queued, or zero when the file key is zero or no request slot remains.
 */
extern "C" s32 func_00103AE0(ResidentResourceQueue* queue, s32 file_key, void* buffer, s32 file_offset, u32 byte_count,
                             u32 tag, s32 priority, void* completion_callback)
{
    return resident_queue_resource_request(queue, file_key, buffer, tag, priority, completion_callback, byte_count,
                                           file_offset, 3);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_cancel_resource_requests);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", resident_queue_resource_request);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001041C0);

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

/** @brief Register the queue's listener with the archive again. @param queue Resident resource queue. */
extern "C" void func_001043F0(ResidentResourceQueue* queue)
{
    func_0011D320(queue->archive, &queue->listener, queue);
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", __dt__21ResidentResourceQueueFv);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001044F0);

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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00104790);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00104C90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105210);

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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105BF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105DD0);

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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00105FB0);

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
extern "C" s32 func_00106160(ResidentSoundStream* stream, const void* file, s32 arg2, s32 slot, s32* result, u32 arg5,
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00106240);

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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001068C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00106A50);

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
extern "C" u32 func_00107730(ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3, const u32* values, s32 count)
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

    return func_0010C200(&D_001CC590, 0x14, (void*)arg1, arg2, arg3, 0);
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
extern "C" u32 func_00108800(ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3, s32 value0, s32 value1, s32 value2, s32 value3)
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", __dt__19ResidentSoundStreamFv);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_001093E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109510);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109800);

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
            D1_QWC = 0;
            D1_TADR = (u32)D_00148400 & 0x0FFFFFFF;
            D_STAT = D_STAT_CHANNEL_1;
            D1_CHCR = D_CHCR_START | D_CHCR_CHAIN_MODE | D_CHCR_FROM_MEMORY;
            break;

        case 2:
            D1_QWC = 0;
            D1_TADR = (u32)D_0014A9E0 & 0x0FFFFFFF;
            D_STAT = D_STAT_CHANNEL_1;
            D1_CHCR = D_CHCR_START | D_CHCR_CHAIN_MODE | D_CHCR_FROM_MEMORY;
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101550", func_00109D50);

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
 * @brief Read the stream thread's signed byte at offset 0xBC.
 * @param thread Stream thread.
 * @return The signed byte, promoted to a word.
 */
extern "C" s32 func_00109FD0(const ResidentStreamThread* thread)
{
    return thread->unkBC;
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
