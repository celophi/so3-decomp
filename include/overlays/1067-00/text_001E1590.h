#ifndef SO3_OVERLAYS_1067_00_TEXT_001E1590_H
#define SO3_OVERLAYS_1067_00_TEXT_001E1590_H

#include "types.h"
#include "overlays/1067-00/text_001DED80.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_002CD390.h"
#endif

/** Partial 28-byte record reset by func_001E5690 and reset_requests. */
typedef struct FieldSlotRecord1C
{
    u8 unk00[4];
    u32 unk04;
    u8 unk08_0 : 1;
    u8 unk08_1_7 : 7;
    u8 unk09[3];
    s32 unk0c;
    u32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_3_7 : 5;
    u8 unk17[5];
} FieldSlotRecord1C;

/** Partial receiver owning a counted array of 28-byte records at offset 0x1C. */
typedef struct FieldSlotRecordOwner1C
{
    u8 unk00[0x14];
    u8 unk14;
    u8 unk15[7];
    FieldSlotRecord1C* unk1c;
    u32 unk20;
    s32 unk24;
    u8 unk28[5];
    u8 unk2d;
    u8 unk2e;
    u8 unk2f;
    u8 unk30[8];
    s32 unk38;
    s32 unk3c;
} FieldSlotRecordOwner1C;

#ifdef __cplusplus
/** Resource loader with 28-byte request slots and a secondary completion interface at offset 0x18. */
class FieldResourceLoader : public FieldResourceLoadTask, public FieldClass1DD400
{
public:
    /**
     * @brief Initialize the record state, allocation flags, and request span.
     */
    FieldResourceLoader()
    {
        unk2c = 0x80;
        request_capacity = 0;
        request_priority = 0x34BC0;
        requests = 0;
        callback_ready = 0;
        unk30_0 = 0;
        reset_requests();
    }

    /**
     * @brief Destroy the record loader.
     */
    virtual ~FieldResourceLoader();

    /**
     * @brief Advance reads or handle cancellation.
     * @param cancel_request One requests cancellation; zero advances reads.
     */
    virtual void update_requests(s32 cancel_request);

    /**
     * @brief Poll cancellation and release request buffers once reads finish.
     * @return One if a buffer was present before cleanup, two if a buffer remains pending, otherwise zero.
     */
    virtual s32 poll_request_release();

    /**
     * @brief Cancel pending reads or queue the loader for removal, according to its state.
     * @return One after queuing the loader for removal, otherwise zero.
     */
    virtual s32 request_removal();

    /**
     * @brief Start the request for the current record when its buffer address is nonzero.
     */
    virtual void start_current_read();

    /**
     * @brief Consume completion, skip available requests, and select the next request.
     */
    virtual void advance_requests();

    /**
     * @brief Reset request slots, counts, and the completion callback.
     * Existing buffer addresses are cleared without freeing their storage.
     */
    virtual void reset_requests();

    /**
     * @brief Release resources in every allocated request slot.
     */
    virtual void release_requests();

    /**
     * @brief Flush the cache once and mark the current request ready to advance.
     * @param arg Unused callback argument.
     */
    virtual void func_001DDB30(void* arg);

    FieldResourceRequest* requests;

    FieldClass1DD400* completion_callback;

    s32 request_capacity;

    s32 request_priority;

    u8 unk2c;

    u8 request_count;

    u8 current_request;

    u8 unk2f;

    u8 unk30_0 : 1;

    u8 callback_ready : 1;

    u8 unk30_2_7 : 6;

    u8 unk31[3];
};

/** Loader created and reused by file key; its separate request array reserves 50 slots. */
class FieldKeyedResourceLoader : public FieldResourceLoader
{
public:
    /**
     * @brief Reserve 50 request slots and prepare the initial file request.
     * @param key File key retained for lookup and the initial request.
     */
    FieldKeyedResourceLoader(s32 key);

    /**
     * @brief Destroy the keyed loader.
     */
    virtual ~FieldKeyedResourceLoader();

    /**
     * @brief Queue the loader on the resident object queue without detaching it.
     */
    virtual void func_001DD7B0();

    /**
     * @brief Flush the cache once for this loader.
     * @param arg Unused secondary-interface argument.
     */
    virtual void func_001DDB30(void* arg);

    /**
     * @brief Advance the keyed loader's record requests.
     * @param cancel_request One requests cancellation; zero advances reads.
     */
    virtual void update_requests(s32 cancel_request);

    /**
     * @brief Advance the keyed loader's current request.
     */
    virtual void advance_requests();

    /**
     * @brief Reset request slots, restore the start delay, and clear the initial slot index.
     * Existing buffer addresses are cleared without freeing their storage.
     */
    virtual void reset_requests();

    s32 file_key;

    s32 start_delay;

    s32 initial_request_slot;

    void* buffer_allocation;

    u8 completion_ready;

    u8 unk45[3];
};

struct FieldBufferSlots;
struct FieldRecordSelection;

/** Partial FieldListObject receiver with MAIN vtable 0x153E30. */
class FieldClass153E30 : public FieldListObject
{
public:
    /** @brief Initialize the callback receiver and its Field base storage. */
    FieldClass153E30();
    /**
     * @brief Destroy the callback receiver.
     */
    virtual ~FieldClass153E30();
    /**
     * @brief Release the callback receiver through its virtual handler.
     */
    virtual void func_001DD7B0();
    /**
     * @brief Report the receiver state.
     * @return Receiver state byte.
     */
    virtual u8 func_00264110();
    /**
     * @brief Append a non-null display child to the receiver list.
     * @param value Child to append.
     * @return One when a child was supplied, otherwise zero.
     */
    virtual s32 add_child(void* value);
    /**
     * @brief Unlink a registered display child and invoke its release hook.
     * @param value Child to remove.
     * @return Zero for a null child, otherwise one.
     */
    virtual s32 remove_child(void* value);
    /**
     * @brief Report the handler state.
     * @return Handler result.
     */
    virtual s32 func_00264080();
    /**
     * @brief Store the pointer at offset 0x20.
     * @param value Pointer to store.
     */
    virtual void func_00263C70(void* value);
    /**
     * @brief Get the pointer at offset 0x20.
     * @return Stored pointer.
     */
    virtual void* func_00261150();
    /**
     * @brief Store the pointer at offset 0x24.
     * @param value Pointer to store.
     */
    virtual void func_00263C80(void* value);
    /**
     * @brief Get the pointer at offset 0x24.
     * @return Stored pointer.
     */
    virtual void* func_00263C90();
    /**
     * @brief Store the byte at offset 0x28.
     * @param value Byte to store.
     */
    virtual void func_00263CA0(s8 value);
    /**
     * @brief Get the signed byte at offset 0x28.
     * @return Stored byte.
     */
    virtual s8 func_00263CB0();
    /**
     * @brief Return the loaded resource slot.
     * @return Zero in the base implementation.
     */
    virtual u32 get_resource_slot();
    /**
     * @brief Update the callback receiver.
     */
    virtual void func_00263E90();
    /**
     * @brief Report whether window setup finished.
     * @return Zero in the base implementation.
     */
    virtual u8 windows_ready();
    /**
     * @brief Load the completed resource buffer and create the windows.
     * @param buffer Completed resource buffer.
     * @return Zero in the base implementation.
     */
    virtual s32 on_resource_loaded(void* buffer);
    /** @brief Create the menu windows. @return Zero in the base implementation. */
    virtual s32 init_windows();
    /**
     * @brief Forward the flag to each child with all seven list bits selected.
     * @param flag Flag forwarded without narrowing.
     */
    virtual void func_00263E20(u32 flag);
    /** @brief Release the receiver's associated objects and queued children. */
    virtual void func_slot5c();
    /** @brief Default receiver hook. @return Zero. */
    virtual s32 func_slot60();
    /** @brief Default receiver hook. @return Zero. */
    virtual s32 func_slot64();
    /** @brief Default receiver hook. */
    virtual void func_slot68();
    /** @brief Return the receiver's selection object. @return Null in the base implementation. */
    virtual FieldRecordSelection* selected_records();
    /** @brief Default receiver hook. */
    virtual void func_slot70();
    /** @brief Default receiver hook. */
    virtual void func_slot74();
    /** @brief Default receiver hook. */
    virtual void func_slot78();
    /** @brief Default receiver hook. @return Zero. */
    virtual s32 func_slot7c();
    /** @brief Default receiver hook. @return Zero. */
    virtual s32 func_slot80();
    /** @brief Default receiver hook. @return Zero. */
    virtual s32 func_slot84();
    /** @brief Default receiver hook. */
    virtual void func_slot88();
    FieldClass153EC0 unk14;
    void* unk20;
    void* unk24;
    s8 unk28;
    u8 unk29;
    u8 unk2a[2];
    void* unk2c;
    void* unk30;
};

/** Handler for keyed resource requests, decoded buffer delivery, and attachment slots. */
class FieldResourceRequestHandler : public FieldListObject, public FieldClass1DD400
{
public:
    /**
     * @brief Decode and attach the resource group selected for this loader.
     * @param loader Completed record loader.
     * @return Resource loading result.
     */
    s32 func_001E1830(FieldResourceLoader* loader);

    /**
     * @brief Attach additional resources from a completed record loader.
     * @param loader Completed record loader.
     * @return Resource attachment result.
     */
    s32 func_001E3580(FieldResourceLoader* loader);

    /**
     * @brief Attach resource buffers from a completed record loader.
     * @param loader Completed record loader.
     * @return Resource attachment result.
     */
    s32 func_001E2E40(FieldResourceLoader* loader);

    /**
     * @brief Fill the aligned resource slots from a completed record loader.
     * @param loader Completed record loader.
     * @return Resource loading result.
     */
    s32 func_001E39A0(FieldResourceLoader* loader);

    /**
     * @brief Attach decoded resources from a completed loader to the buffer slots.
     * @param loader Completed record loader.
     * @return Attachment result.
     */
    s32 func_001E4220(FieldResourceLoader* loader);

    /**
     * @brief Decode the completed request, notify its receiver, and release the temporary buffer and loader.
     */
    void deliver_completed_request();

    /**
     * @brief Decode the completed request and attach its resource groups.
     * @param loader Completed record loader.
     * @return Temporary byte buffer, or null when unavailable.
     */
    u8* decode_request_resources(FieldResourceLoader* loader);

    /**
     * @brief Clear the request state, parallel arrays, and loader pointers.
     */
    FieldResourceRequestHandler();

    /**
     * @brief Release the owned buffers and destroy the request handler.
     */
    virtual ~FieldResourceRequestHandler();

    /**
     * @brief Report this object's default list kind.
     * @return The class's default list kind.
     */
    virtual s32 get_default_list_kind();

    /**
     * @brief Queue the object on the resident object queue without detaching it.
     */
    virtual void func_001DD7B0();

    /**
     * @brief Reuse a matching keyed loader or create and append one when needed.
     */
    virtual void update();

    /**
     * @brief Decode into the shared buffer or retain the loader for later resource processing.
     * @param arg Completed resource loader.
     */
    virtual void func_001DDB30(void* arg);

    s32 file_key;

    u8 unk1c;

    u8 request_mode;

    u8 unk1e;

    u8 notification_pending;

    u8 unk20;

    u8 unk21[3];

    u32 unk24;

    u8 unk28;

    u8 unk29[3];

    FieldClass153E30* receiver;

    u32 next_file_key;

    u8 next_request_mode;

    u8 unk35[3];

    u32 unk38;

    FieldResourceLoader* completed_loader;

    u32 unk40;

    u8* owned_buffers[10];

    u32 unk6c[10];

    FieldBufferSlots* buffer_slots;

    FieldKeyedResourceLoader* request_loader;

    FieldKeyedResourceLoader* unk9c;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
/**
 * @brief Allocate a 128-byte-aligned buffer, retrying after other loaders release storage.
 * @param loader Loader whose owner pointer identifies its context list.
 * @param size Requested size in bytes.
 * @param mode Nonzero for the Lib allocator, zero for the resident allocator.
 * @return Allocated buffer, or null when allocation or recovery fails after at most eight attempts.
 */
void* field_allocate_request_buffer(FieldListObject* loader, u32 size, s32 mode);

/**
 * @brief Append a file-backed resource request when a slot remains.
 * @param loader Loader owning the request array.
 * @param file_key File key used to look up the resource size.
 * @param kind Resource kind stored in the request.
 * @return Appended request, or null when the array is full.
 */
FieldResourceRequest* field_append_resource_request(FieldResourceLoader* loader, s32 file_key, u8 kind);

/**
 * @brief Cancel listed kind-eight loaders, initialize the request, and append its new loader.
 * @param handler Request handler receiving completion.
 * @param file_key File key to request.
 * @param mode One decodes into the shared buffer first; other values retain the completed loader.
 * @return Created loader, or null when allocation fails.
 */
FieldKeyedResourceLoader* field_start_keyed_resource_request(FieldResourceRequestHandler* handler, s32 file_key, u8 mode);
#endif

#ifdef __cplusplus
/**
 * @brief Store the file key and mode for the request that follows direct-buffer decoding.
 * @param handler Request handler retaining the next request.
 * @param file_key Next file key; zero leaves no request queued.
 * @param mode Mode passed to the next keyed request.
 */
void field_set_next_resource_request(FieldResourceRequestHandler* handler, u32 file_key, u8 mode);
#endif

#ifdef __cplusplus
}
#endif

#endif
