#ifndef SO3_MAIN_RESIDENT_00101550_H
#define SO3_MAIN_RESIDENT_00101550_H

#include "types.h"
#include "main/resident_001001E0.h"

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
    /** @brief Construct an unlinked node. */
    ResidentClass14FA30() : previous(0), next(0)
    {
    }

    /** @brief Destroy the intrusive node. */
    virtual ~ResidentClass14FA30();

    ResidentClass14FA30* previous;
    ResidentClass14FA30* next;
};

/** Partial resident object interface with vtable at 0x14FA40. */
class ResidentClass14FA40 : public ResidentClass14FA30
{
public:
    /** @brief Construct an object with no owner. */
    ResidentClass14FA40() : unk0e(0), unk0f(0), owner(0)
    {
    }

    /** @brief Destroy the resident object. */
    virtual ~ResidentClass14FA40();

    /** @brief Return the object's kind. @return Object kind. */
    virtual s32 func_00104730();

    /** @brief Destroy the object through its virtual destructor. */
    virtual void func_00104740();

    /** @brief Update the object; its list calls this once a frame. */
    virtual void func_00104770();

    virtual void func_00104780();

    s16 list_kind;
    u8 unk0e;
    u8 unk0f;
    void* owner;
};
#endif

#ifdef __cplusplus
/**
 * Scoped lock that disables interrupts while it lives; vtable D_0014FA60. Its constructor reads the COP0 Status
 * register, so it is only built from the queue's hand-written code.
 */
class ResidentInterruptLock
{
public:
    /** Nonzero when the lock disabled interrupts and must enable them again. */
    u8 disabled;

    /** @brief Enable interrupts again if the lock disabled them. */
    virtual ~ResidentInterruptLock();
};
#endif

/** Dispatch table whose complete layout is not yet known. */
typedef struct ResidentDispatchTable ResidentDispatchTable;

/** Partial prefix of an object registered with the resident dispatcher. */
typedef struct ResidentRegisteredObject
{
    const ResidentDispatchTable* dispatch;
} ResidentRegisteredObject;

struct ResidentArchive;

/** One entry of the resource queue's request table; entry 0 is the head of the queued list. */
typedef struct ResidentResourceRequest
{
    /** Caller's tag, used to find and cancel the request. */
    u32 tag;

    void* buffer;
    u32 byte_count;

    /** Lower values run first; each queue pass lowers the positive ones, so waiting requests move up. */
    s32 priority;

    s32 file_key;

    /** Table index of the next queued request, or zero at the end of the list. */
    s32 next;

    /** Table index of the previous queued request. */
    s32 previous;

    s32 file_offset;
    void* completion_callback;
    u8 unk24[4];

    /** Nonzero while the entry holds a request. */
    u8 in_use;

    u8 state;
    u8 request_kind;
    u8 unk2b;
} ResidentResourceRequest;

#ifdef __cplusplus
/**
 * Something that can be notified: the archive notifies listeners when a read finishes, and the IOP's SIF commands
 * reach g_sif_command_receiver through notify(); vtable D_0014FA10.
 */
class ResidentListener
{
    public:
        virtual void func_00102A90();

        /**
         * @brief Handle a notification; the base class ignores it.
         * @param data What the notification carries: a registered context, or a SIF command.
         */
        virtual void notify(void* data);
};

/** Listener that forwards archive notifications to the resource queue's update; vtable D_0014FA00. */
class ResidentResourceQueueListener : public ResidentListener
{
    public:
        /** @brief Update the object the archive passes back. @param data Resource queue. */
        virtual void notify(void* data);
};

/** The resident resource queue ("StorageQueue"), reached through g_resource_queue; vtable D_0014FA70. */
class ResidentResourceQueue : public ResidentClass14FA40
{
public:
    /** Request table; entry 0 is the list head. */
    ResidentResourceRequest* requests;

    /** Number of entries in the request table. */
    s32 request_capacity;

    /** Request the archive is reading. */
    ResidentResourceRequest* active_request;

    struct ResidentArchive* archive;
    ResidentSemaphore semaphore;
    u8 unk2c;

    /** Read status, registered for display as "StorageQueue Status". */
    u8 status;

    u8 unk2e;

    /** Nonzero while cancellation of the active read is still pending. */
    u8 cancel_pending;

    u8 unk30;

    /** Listener registered with the archive; it calls this queue's update. */
    ResidentResourceQueueListener listener;

    /** @brief Destroy the queue. */
    ~ResidentResourceQueue();
};
#endif

typedef struct ResidentResourceQueue ResidentResourceQueue;

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

/** State of a block that is decoded a part at a time. */
typedef struct ResidentDecodeStream
{
    /** LZ flag bits not yet used. */
    u32 flags;

    /** Flags left before the next flag word is read. */
    s32 flag_count;

    /** Bytes left to copy from a stored block. */
    s32 remaining;

    u8* destination;
    u8* source;
    u8* destination_end;
    u8 compression_kind;
    u8 unk19;
} ResidentDecodeStream;

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

    /** Nonzero when a LIP chunk follows the WAV chunk. */
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
s32 func_00103AE0(ResidentResourceQueue* queue, s32 file_key, void* buffer, s32 file_offset, u32 byte_count, u32 tag,
                  s32 priority, void* completion_callback);

/** @brief Start the next queued read when the archive is idle. @param queue Resident resource queue. */
void func_00102D50(ResidentResourceQueue* queue);

/**
 * @brief Finish the active read if the archive has completed it.
 * @param queue Resident resource queue.
 * @return Nonzero when a request completed, so another pass may start more work.
 */
s32 func_001031C0(ResidentResourceQueue* queue);

/** @brief Clear the request table and its queued list. @param queue Resident resource queue. */
void func_001041C0(ResidentResourceQueue* queue);

/**
 * @brief Stop the active read and clear the archive's pending flags.
 * @param queue Resident resource queue.
 */
void func_00102AE0(ResidentResourceQueue* queue);

/**
 * @brief Process completed work, then report whether any request is still queued.
 * @param queue Resident resource queue.
 * @return Nonzero when the queue is empty.
 */
s32 func_00102D00(ResidentResourceQueue* queue);

/** @brief Lower the priority of every queued request that is still positive. @param queue Resident resource queue. */
void func_00103510(ResidentResourceQueue* queue);

/**
 * @brief Replace the request table with an empty one.
 * @param queue Resident resource queue.
 * @param capacity Number of entries in the new table.
 * @return One on success, or zero when the table cannot be allocated.
 */
s32 func_00104370(ResidentResourceQueue* queue, s32 capacity);

/** @brief Register the queue's listener with the archive again. @param queue Resident resource queue. */
void func_001043F0(ResidentResourceQueue* queue);

#ifdef __cplusplus
/**
 * @brief Update the object the archive passes back to the listener.
 * @param listener Resource queue listener.
 * @param context Object to update.
 */
void func_001034E0(ResidentResourceQueueListener* listener, ResidentClass14FA40* context);

/** @brief Destroy a resident object through its virtual destructor. @param object Object to destroy, or null. */
void func_00104740(ResidentClass14FA40* object);
#endif

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

/**
 * @brief Decrypt the selected SLE block in place and retag it as SLZ.
 * @param decoder Resident decoder; unused.
 * @param source First block header.
 * @param key Sixteen-byte key.
 * @param index Links to follow; nonpositive values select the first block.
 * @return One after decrypting, or zero when the chain ends.
 */
s32 func_00102340(ResidentDecodeObject* decoder, ResidentResourceHeader* source, unsigned __int128 key, s32 index);

/**
 * @brief Decode the next part of a block started by func_00105770.
 * @param decoder Resident decoder.
 * @param stream Stream state.
 * @param limit Most bytes a stored block copies in this step.
 * @return Nonzero once the whole block is decoded.
 */
s32 func_00105680(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit);

/**
 * @brief Start decoding the selected SLZ/SLE block in steps; SLE payloads are decrypted in place first.
 * @param decoder Resident decoder.
 * @param stream Receives the stream state.
 * @param source First block header.
 * @param destination Destination buffer.
 * @param index Links to follow; nonpositive values select the first block.
 * @return One when the stream is ready, or zero for an invalid header or a missing block.
 */
s32 func_00105770(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, ResidentResourceHeader* source,
                  u8* destination, s32 index);

/** @brief Decode the next part of an LZ word stream. */
s32 func_00104790(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit);

/** @brief Decode the next part of an LZ stream with runs. */
s32 func_00104C90(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit);

/** @brief Decode the next part of an LZ byte stream. */
s32 func_00105210(ResidentDecodeObject* decoder, ResidentDecodeStream* stream, s32 limit);

/** Return the fixed integer value 3. */
s32 func_00104730(void* object);

void func_00101550(void* object);
void func_00102A90(void* object);
void func_00104770(void* object);
void func_00104780(void* object);

/**
 * @brief Set the stream thread's second state to one when the value is positive.
 * @param stream Sound stream.
 * @param value Value to check.
 */
void func_00107D90(struct ResidentSoundStream* stream, const s32* value);

/**
 * @brief Set the stream thread's first state to one when the value is positive.
 * @param stream Sound stream.
 * @param value Value to check.
 * @return The value when it is positive, otherwise zero.
 */
s32 func_00107DB0(struct ResidentSoundStream* stream, const s32* value);

/**
 * @brief Run the resident helper with an object and four word arguments.
 * @param object Input object.
 * @param arg1 First input word.
 * @param arg2 Second input word.
 * @param arg3 Third input word.
 * @param arg4 Fourth input word.
 */
void func_00108C40(void* object, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

/**
 * @brief Query the stream: modes one and two read the stream thread's states, other modes go to func_00107940.
 * @param stream Sound stream.
 * @param arg1 First argument for func_00107940.
 * @param arg2 Second argument for func_00107940.
 * @param arg3 Third argument for func_00107940.
 * @param mode Query mode.
 * @return Query result.
 */
s32 func_00107B10(struct ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 mode);

s32 func_00107940(struct ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 mode);

/**
 * @brief Report whether one of the stream thread's two states is set.
 * @param thread Stream thread.
 * @param which One for the first state; any other value selects the second.
 * @return Nonzero when the selected state is nonzero.
 */
s32 func_00109FE0(struct ResidentStreamThread* thread, s32 which);

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
void func_00107530(struct ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 handle, s32 command, s32 first, s32 second);

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
s32 func_00107B60(struct ResidentSoundStream* stream, u32 arg1, void (*callback)(void*), void* argument, u32 handle, s32 mode,
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
 * @return Request identifier to wait for.
 */
s32 func_00109000(struct ResidentSoundStream* stream, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s32 arg7, s32 arg8);

/** @brief Stream setup step run after func_00109000 completes. @param stream Sound stream. */
void func_00108E10(struct ResidentSoundStream* stream);

/**
 * @brief Send a word to the sound stream.
 * @param stream Sound stream.
 * @param arg1 Unused by the sound callers, which pass zero.
 * @param arg2 Unused by the sound callers, which pass zero.
 * @param arg3 Unused by the sound callers, which pass zero.
 * @param value Value sent.
 */
void func_00107250(struct ResidentSoundStream* stream, s32 arg1, s32 arg2, s32 arg3, s32 value);


/**
 * @brief Take samples out of one of the stream thread's sample rings and convert them to floats.
 * @param thread Stream thread.
 * @param ring Ring index, 0 or 1.
 * @param count Number of samples to take; a multiple of four.
 * @param output Receives the samples.
 * @return One when the samples were taken, or zero when the ring doesn't hold that many yet.
 */
s32 func_00109F20(struct ResidentStreamThread* thread, s32 ring, s32 count, float* output);

/**
 * @brief Read the stream thread's signed byte at offset 0xBC.
 * @param thread Stream thread.
 * @return The byte.
 */
s8 func_00109FD0(const struct ResidentStreamThread* thread);

/**
 * @brief Set the receiver flag when the input value is positive.
 * @param object Receiver whose field at offset 0xB0 is set.
 * @param value Input value to check and return.
 * @return The positive input value, or zero.
 */
s32 func_0010A080(void* object, const s32* value);

/**
 * @brief Wake the stream thread, or wake it and sleep until it has run.
 * @param stream Sound stream.
 * @param no_wait Nonzero to wake the thread without waiting for it.
 * @return Zero.
 */
s32 func_001071A0(struct ResidentSoundStream* stream, s32 no_wait);

/**
 * @brief Run one step of the sequence upload at the front of the sequence queue.
 * @param stream Sound stream.
 * @return Zero, minus one when an IOP request can't be made, or minus two when the IOP reports an error.
 */
s32 func_00106240(struct ResidentSoundStream* stream);

/**
 * @brief Run one step of the bank load at the front of the bank queue.
 * @param stream Sound stream.
 * @return Zero, or minus one when an IOP request can't be made.
 */
s32 func_00106A50(struct ResidentSoundStream* stream);

/**
 * @brief Set two receiver flags when the input value is positive.
 * @param object Receiver whose fields at offsets 0xAC and 0x110 are set.
 * @param value Input value to check and return.
 * @return The positive input value, or zero.
 */
s32 func_0010A0B0(void* object, const s32* value);

/**
 * @brief Take samples out of one of the stream DMA transfer's rings and convert them to floats.
 * @param dma Stream DMA transfer.
 * @param ring Ring index, 0 or 1.
 * @param count Number of samples to take; a multiple of four.
 * @param output Receives the samples.
 * @return One when the samples were taken, or zero when the ring doesn't hold that many yet.
 */
s32 func_00109510(struct ResidentStreamDma* dma, s32 ring, s32 count, float* output);

struct ResidentStreamDma;

/**
 * @brief Read the word at offset 0x14 of a SEQW file header.
 * @param stream Sound stream; unused.
 * @param file Sound file.
 * @return The word, or zero when the file isn't a SEQW file.
 */
u32 func_00105F90(struct ResidentSoundStream* stream, const SoundFileHeader* file);

/**
 * @brief Find the VSC chunk of a lip table entry.
 * @param stream Sound stream.
 * @param entry Lip table entry.
 * @param slot Slot holding the lip table.
 * @return Data of the VSC chunk, or null when the entry or the chunk is missing.
 */
void* func_00105FB0(struct ResidentSoundStream* stream, s32 entry, s32 slot);

/**
 * @brief Report whether a sound file has an upload in the sequence queue.
 * @param stream Sound stream.
 * @param file Sound file.
 * @return One when the file is queued, otherwise zero.
 */
s32 func_001060C0(struct ResidentSoundStream* stream, const void* file);

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
s32 func_00106160(struct ResidentSoundStream* stream, const void* file, s32 arg2, s32 slot, s32* result, u32 arg5,
                  u32 arg6);

/**
 * @brief Run the sequence uploads until one has to wait.
 * @param stream Sound stream.
 * @return Zero, or the negative result of a failed step.
 */
s32 func_001065B0(struct ResidentSoundStream* stream);

/**
 * @brief Continue the bank load waiting at the front of the bank queue by sending its wave data request.
 * @param stream Sound stream.
 * @param arg1 First request argument.
 * @param arg2 Second request argument.
 * @return Data of the slot the bank's sound file was copied into.
 */
u8* func_00106640(struct ResidentSoundStream* stream, u32 arg1, u32 arg2);

/**
 * @brief Report whether a sound file has a load in the bank queue.
 * @param stream Sound stream.
 * @param file Sound file.
 * @return One when the file is queued, minus one when it is queued and waiting for func_00106640, otherwise zero.
 */
s32 func_001066D0(struct ResidentSoundStream* stream, const void* file);

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
s32 func_00106780(struct ResidentSoundStream* stream, const void* file, s32* result, u32 arg3, u32 arg4, u32 arg5,
                  u32 arg6, u32 arg7);

/**
 * @brief Choose the channel for the bank load at the front of the bank queue.
 * @param stream Sound stream.
 * @return Channel index, or minus one when the bank can't be loaded.
 */
s32 func_001068C0(struct ResidentSoundStream* stream);

/**
 * @brief Run the bank loads until one has to wait.
 * @param stream Sound stream.
 * @return Zero, or the negative result of a failed step.
 */
s32 func_00107020(struct ResidentSoundStream* stream);

/**
 * @brief Handle a SIF command from the IOP for the sound stream.
 * @param stream Sound stream.
 * @param command Command number.
 */
void func_001070B0(struct ResidentSoundStream* stream, s32 command);

/**
 * @brief Report whether an IOP request of the stream is still running.
 * @param stream Sound stream; unused.
 * @param request Request ID.
 * @return Nonzero while the request runs.
 */
s32 func_00107230(struct ResidentSoundStream* stream, s32 request);

/**
 * @brief Start the VIF1 DMA chain for the transfer's current phase.
 * @param dma Stream DMA transfer.
 * @param channel DMA channel; unused.
 */
void func_00109BE0(struct ResidentStreamDma* dma, u32 channel);

/**
 * @brief Queue the packet that follows a finished stream DMA transfer.
 * @param dma Stream DMA transfer.
 * @param channel DMA channel; unused.
 */
void func_00109C80(struct ResidentStreamDma* dma, u32 channel);

/**
 * @brief Account for one finished 4 KiB block and queue the next VIF1 transfer, or swap buffers once both are full.
 * @param thread Stream thread.
 */
void func_00109D50(struct ResidentStreamThread* thread);

/**
 * @brief Set the two sample rings of the stream DMA transfer and empty them.
 * @param thread Stream thread.
 * @param first_ring Start of the first ring.
 * @param second_ring Start of the second ring.
 * @param ring_size Size of each ring in bytes.
 */
void func_00109F40(struct ResidentStreamThread* thread, u32 first_ring, u32 second_ring, u32 ring_size);

/**
 * @brief Read the stream thread's word at offset 0xC0 while its first state is one.
 * @param thread Stream thread.
 * @return The word, or zero in any other state.
 */
s32 func_00109FB0(struct ResidentStreamThread* thread);

/**
 * @brief Move one of the stream thread's two states to two when it is one or two.
 * @param thread Stream thread.
 * @param which One for the first state, two for the second.
 * @return One when the state was moved, otherwise zero.
 */
s32 func_0010A000(struct ResidentStreamThread* thread, s32 which);

/**
 * @brief Read four values from the sound stream.
 * @param stream Sound stream.
 * @param x Receives the first value.
 * @param y Receives the second value.
 * @param z Receives the third value.
 * @param w Receives the fourth value.
 */
void func_001058C0(struct ResidentSoundStream* stream, float* x, float* y, float* z, float* w);

/**
 * @brief Construct the resource queue.
 * @param queue Resource queue to construct.
 * @return The constructed queue.
 */
ResidentResourceQueue* func_001044F0(ResidentResourceQueue* queue);

/**
 * @brief Construct the sound stream.
 * @param stream Sound stream to construct.
 * @return The constructed stream.
 */
struct ResidentSoundStream* func_001093E0(struct ResidentSoundStream* stream);


#ifdef __cplusplus
}
#endif

#endif
