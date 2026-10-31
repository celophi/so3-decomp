#ifndef SO3_MAIN_RESIDENT_00101550_H
#define SO3_MAIN_RESIDENT_00101550_H

#include "types.h"

#ifdef __cplusplus
/** Resident object root with vtable at 0x14FA20. */
class ResidentClass14FA20
{
public:
    /** @brief Destroy the resident root. */
    virtual ~ResidentClass14FA20();
};

/** Partial resident intrusive node with vtable at 0x14FA30. */
class ResidentClass14FA30 : public ResidentClass14FA20
{
public:
    /** @brief Destroy the intrusive node. */
    virtual ~ResidentClass14FA30();

    ResidentClass14FA30* previous;
    ResidentClass14FA30* next;
};

/** Partial resident object interface with vtable at 0x14FA40. */
class ResidentClass14FA40 : public ResidentClass14FA30
{
public:
    /** @brief Destroy the resident object. */
    virtual ~ResidentClass14FA40();

    /** @brief Return the object's kind. @return Object kind. */
    virtual s32 func_00104730();

    /** @brief Queue the object for release. */
    virtual void func_00104740();

    s16 list_kind;
    u8 unk0e;
    u8 unk0f;
    void* owner;
};
#endif

/** Dispatch table whose complete layout is not yet known. */
typedef struct ResidentDispatchTable ResidentDispatchTable;

/** Partial prefix of an object registered with the resident dispatcher. */
typedef struct ResidentRegisteredObject
{
    const ResidentDispatchTable* dispatch;
} ResidentRegisteredObject;

/** Partial resident resource queue reached through g_resource_queue. */
typedef struct ResidentResourceQueue
{
    u8 unk00[0x30];
    u8 unk30;
} ResidentResourceQueue;

/** Resident decoder used by the resource loading helpers; it keeps no state, so it is one byte. */
typedef struct ResidentDecodeObject
{
    u8 unk00;
} ResidentDecodeObject;

/** Header of an SLZ/SLE compression block; next_offset is relative to this header. */
typedef struct ResidentResourceHeader
{
    /** Three-byte SLZ/SLE tag, without a terminating null byte. */
    u8 signature[3];

    u8 compression_kind;
    u32 compressed_size;
    u32 decoded_size;
    u32 next_offset;
} ResidentResourceHeader;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start queued work and process completed requests until no more completions are available.
 * @param queue Resident resource queue.
 * @return Nonzero while cancellation of an active read is still pending.
 */
s32 resident_update_resource_queue(ResidentResourceQueue* queue);

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
s32 resident_find_resource_request(ResidentResourceQueue* queue, s32 file_key, u32 buffer_address, u32 tag,
                                  u32 byte_count, s32 request_kind);

/**
 * @brief Remove every matching request and cancel its active read when applicable.
 * @param queue Resident resource queue.
 * @param file_key File key to match, or zero to accept any key.
 * @param buffer_address Destination address to match, or zero to accept any address.
 * @param tag Exact request tag to match, or zero to accept any tag.
 * @param byte_count Read length to match, or 0xFFFFFFFF to accept any length.
 * @param request_kind Request kind to match in the low byte, or zero to accept any kind.
 */
void resident_cancel_resource_requests(ResidentResourceQueue* queue, s32 file_key, u32 buffer_address, u32 tag,
                                     u32 byte_count, s32 request_kind);

/**
 * @brief Queue a resource request in priority order.
 * @param queue Resident resource queue.
 * @param file_key Nonzero file key for the request.
 * @param buffer Destination buffer.
 * @param tag Tag retained for later lookup and cancellation.
 * @param priority Lower values run first; minus one inserts at the front.
 * @param completion_callback Optional callback object notified when the request finishes.
 * @param byte_count Read length passed to the resource backend.
 * @param file_offset Offset applied when selecting a file for request kinds two and three.
 * @param request_kind Request kind stored in the low byte.
 * @return One when queued, or zero when the file key is zero or no request slot remains.
 */
s32 resident_queue_resource_request(ResidentResourceQueue* queue, s32 file_key, void* buffer, u32 tag,
                                   s32 priority, void* completion_callback, u32 byte_count, s32 file_offset,
                                   s32 request_kind);

/**
 * @brief Initialize the dispatch pointer and register the object.
 * @param object Object to register.
 * @return The registered object.
 */
ResidentRegisteredObject* func_00101560(ResidentRegisteredObject* object);

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

/** Return the fixed integer value 3. */
s32 func_00104730(void* object);

void func_00101550(void* object);
void func_00102A90(void* object);
void func_00104770(void* object);
void func_00104780(void* object);

/**
 * @brief Pass the pointer at offset 0x90 to the resident helper.
 * @param receiver Object containing the pointer.
 * @param argument Input pointer forwarded to the resident helper.
 */
void func_00107D90(void* receiver, void* argument);

/**
 * @brief Pass the pointer at offset 0x90 to the alternate resident helper.
 * @param receiver Object containing the pointer.
 * @param argument Input pointer forwarded to the resident helper.
 */
void func_00107DB0(void* receiver, void* argument);

/**
 * @brief Run the resident helper with an object and four word arguments.
 * @param object Input object.
 * @param arg1 First input word.
 * @param arg2 Second input word.
 * @param arg3 Third input word.
 * @param arg4 Fourth input word.
 */
void func_00108C40(void* object, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

/** Run the resident object helper with four word arguments. */
s32 func_00107B10(void* object, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

/**
 * @brief Pass the pointer at offset 0x100 to the resident helper.
 * @param receiver Object containing the pointer.
 */
void func_00109F20(void* receiver);

/** Return the signed byte at receiver offset 0xBC. */
s8 func_00109FD0(const void* object);

/**
 * @brief Set the receiver flag when the input value is positive.
 * @param object Receiver whose field at offset 0xB0 is set.
 * @param value Input value to check and return.
 * @return The positive input value, or zero.
 */
s32 func_0010A080(void* object, const s32* value);

/** @brief Apply the resident helper to the supplied object and flag. @param object Helper receiver. @param flag Helper flag. */
void func_001071A0(void* object, s32 flag);

/**
 * @brief Set two receiver flags when the input value is positive.
 * @param object Receiver whose fields at offsets 0xAC and 0x110 are set.
 * @param value Input value to check and return.
 * @return The positive input value, or zero.
 */
s32 func_0010A0B0(void* object, const s32* value);

/** @brief Process the supplied resident object. @param object Input object. */
void func_00109510(void* object);

#ifdef __cplusplus
}
#endif

#endif
