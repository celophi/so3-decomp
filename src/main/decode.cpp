#include "include_asm.h"
#include "main/lz_copy.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "main/heap.h"
#include "main/system.h"
#include "main/utility.h"

/** "SLZ" and "SLE" block tags, as the decoder compares them. */
extern const char g_decode_slz_tag[];
extern const char g_decode_sle_tag[];

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
extern "C" s32 resident_decrypt_resource_block(ResidentDecodeObject* decoder, ResidentResourceHeader* source, unsigned __int128 key,
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
    s32 not_slz = memcmp(source->signature, g_decode_slz_tag, 3);
    s32 not_sle = memcmp(source->signature, g_decode_sle_tag, 3);

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
