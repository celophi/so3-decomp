#ifndef SO3_MAIN_DECODE_H
#define SO3_MAIN_DECODE_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ResidentResourceHeader;

#ifdef __cplusplus
}
#endif

#define RESIDENT_RESOURCE_ALIGNMENT 128

/** Round a resource buffer address up to RESIDENT_RESOURCE_ALIGNMENT. */
#define RESIDENT_ALIGN_RESOURCE(value) (((u32)(value) + RESIDENT_RESOURCE_ALIGNMENT - 1) & ~(RESIDENT_RESOURCE_ALIGNMENT - 1))

/** Resident decoder used by the resource loading helpers; it keeps no state, so it is one byte. */
typedef struct ResidentDecodeObject
{
    u8 unk00;
} ResidentDecodeObject;

/** Header of an SLZ/SLE compression block; next_offset is relative to this header. */
typedef struct ResidentResourceHeader
{
    u8 signature[3];
    u8 compression_kind;
    u32 compressed_size;
    u32 decoded_size;
    u32 next_offset;
} ResidentResourceHeader;

#ifdef __cplusplus
extern "C" {
#endif

/** Resident resource decoder. */
extern ResidentDecodeObject* g_resident_resource_decoder;

/**
 * @brief Decode an LZ payload with 16-bit literals and word offsets.
 * @param decoder Resident decoder; unused.
 * @param source Compressed word stream, without its block header.
 * @param destination Output word buffer.
 * @return One when a token with zero distance ends the stream.
 */
s32 resident_decode_lz_words(ResidentDecodeObject* decoder, const u16* source, u16* destination);

/**
 * @brief Decode an LZ payload with byte literals, back references, and runs of repeated bytes.
 * @param decoder Resident decoder; unused.
 * @param source Compressed byte stream, without its block header.
 * @param destination Output byte buffer.
 * @param decoded_size Output byte count at which decoding stops.
 * @return One after decoding.
 */
s32 resident_decode_lz_runs(ResidentDecodeObject* decoder, const u8* source, u8* destination, u32 decoded_size);

/**
 * @brief Decode an LZ payload with byte literals and back references.
 * @param decoder Resident decoder; unused.
 * @param source Compressed byte stream, without its block header.
 * @param destination Output byte buffer.
 * @return One when a token with zero distance ends the stream.
 */
s32 resident_decode_lz_bytes(ResidentDecodeObject* decoder, const u8* source, u8* destination);

/**
 * @brief Decode or copy the selected SLZ/SLE block into a destination buffer.
 * @param decoder Resident decoder.
 * @param source First block header; SLE payloads are decrypted in place.
 * @param destination Destination buffer.
 * @param index Links to follow; nonpositive values select the first block.
 * @return One after decoding, or zero for an invalid header or a missing block.
 */
s32 resident_decode_resource_block(ResidentDecodeObject* decoder, ResidentResourceHeader* source, void* destination, s32 index);

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
u8* resident_allocate_decode_buffer(ResidentDecodeObject* decoder, ResidentResourceHeader* source, s32 index, s32 aligned);

/**
 * @brief Find a compression block by following its relative links.
 * @param decoder Resident decoder; unused.
 * @param source First block header.
 * @param index Links to follow; nonpositive values select the first block.
 * @return Selected header, or null when the chain ends.
 */
ResidentResourceHeader* resident_find_resource_block(ResidentDecodeObject* decoder, ResidentResourceHeader* source, s32 index);

/**
 * @brief Decrypt the selected SLE block in place and retag it as SLZ.
 * @param decoder Resident decoder; unused.
 * @param source First block header.
 * @param key Sixteen-byte key.
 * @param index Links to follow; nonpositive values select the first block.
 * @return One after decrypting, or zero when the chain ends.
 */
s32 resident_decrypt_resource_block(ResidentDecodeObject* decoder, ResidentResourceHeader* source, unsigned __int128 key, s32 index);

#ifdef __cplusplus
}
#endif

#endif
