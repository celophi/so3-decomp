#include "include_asm.h"
#include "main/lz_copy.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "main/decode_stream.h"
#include "main/system.h"
#include "main/utility.h"

/** "SLZ" and "SLE" block tags, as the stream decoder compares them. */
extern const char g_stream_decode_slz_tag[];
extern const char g_stream_decode_sle_tag[];

/**
 * @brief Decode the next part of an LZ word stream.
 * @param decoder Resident decoder; unused.
 * @param stream Stream state: the cursors and the flag bits carried between calls.
 * @param limit Number of output bytes to decode before returning.
 * @return Nonzero once the stream has ended.
 */
extern "C" s32 resident_decode_lz_words_step(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit)
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
extern "C" s32 resident_decode_lz_runs_step(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit)
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
extern "C" s32 resident_decode_lz_bytes_step(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit)
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
 * @brief Decode the next part of a block started by resident_start_stream_decode.
 * @param decoder Resident decoder.
 * @param stream Stream state.
 * @param limit Most bytes a stored block copies in this step.
 * @return Nonzero once the whole block is decoded.
 */
extern "C" s32 resident_continue_stream_decode(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit)
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
        return resident_decode_lz_bytes_step(decoder, stream, limit);

    case 2:
        return resident_decode_lz_runs_step(decoder, stream, limit);

    default:
        return resident_decode_lz_words_step(decoder, stream, limit);
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
extern "C" s32 resident_start_stream_decode(ResidentDecodeObject* decoder, ResidentDecodeStream* stream,
                             ResidentResourceHeader* source, u8* destination, s32 index)
{
    s32 not_slz = memcmp(source->signature, g_stream_decode_slz_tag, 3);
    s32 not_sle = memcmp(source->signature, g_stream_decode_sle_tag, 3);

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

        resident_decrypt_resource_block(resident_system_get_decoder(resident_get_system()), source, system->sle_key, 0);
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
