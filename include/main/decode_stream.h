#ifndef SO3_MAIN_DECODE_STREAM_H
#define SO3_MAIN_DECODE_STREAM_H

#include "types.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"
#include "main/decode.h"

/** State of a block that is decoded a part at a time. */
typedef struct ResidentDecodeStream
{
    u32 flags;
    s32 flag_count;
    s32 remaining;
    u8* destination;
    u8* source;
    u8* destination_end;
    u8 compression_kind;
    u8 unk19;
} ResidentDecodeStream;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Decode the next part of a block started by resident_start_stream_decode.
 * @param decoder Resident decoder.
 * @param stream Stream state.
 * @param limit Most bytes a stored block copies in this step.
 * @return Nonzero once the whole block is decoded.
 */
s32 resident_continue_stream_decode(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit);

/**
 * @brief Start decoding the selected SLZ/SLE block in steps; SLE payloads are decrypted in place first.
 * @param decoder Resident decoder.
 * @param stream Receives the stream state.
 * @param source First block header.
 * @param destination Destination buffer.
 * @param index Links to follow; nonpositive values select the first block.
 * @return One when the stream is ready, or zero for an invalid header or a missing block.
 */
s32 resident_start_stream_decode(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, ResidentResourceHeader* source,
                  u8* destination, s32 index);

/** @brief Decode the next part of an LZ word stream. */
s32 resident_decode_lz_words_step(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit);

/** @brief Decode the next part of an LZ stream with runs. */
s32 resident_decode_lz_runs_step(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit);

/** @brief Decode the next part of an LZ byte stream. */
s32 resident_decode_lz_bytes_step(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit);

#ifdef __cplusplus
}
#endif

#endif
