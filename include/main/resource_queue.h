#ifndef SO3_MAIN_RESOURCE_QUEUE_H
#define SO3_MAIN_RESOURCE_QUEUE_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "main/semaphore.h"
#include "main/object.h"

#ifdef __cplusplus
struct ResidentArchive;
#else
typedef struct ResidentArchive ResidentArchive;
#endif

#ifndef __cplusplus
typedef struct ResidentListener ResidentListener;
typedef struct ResidentResourceQueueListener ResidentResourceQueueListener;
#endif

/** One entry of the resource queue's request table; entry 0 is the head of the queued list. */
typedef struct ResidentResourceRequest
{
    u32 tag;
    void* buffer;
    s32 byte_count;
    s32 priority;
    s32 file_key;
    s32 next;
    s32 previous;
    s32 file_offset;
    struct ResidentListener* completion_callback;
    struct ResidentListener* context;
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
        /** @brief First slot; no listener overrides it, and it does nothing. */
        virtual void reserved();

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
        /**
         * @brief Update the object the archive passes back.
         * @param data Resource queue.
         */
        virtual void notify(void* data);
};

/** The resident resource queue ("StorageQueue"), reached through g_resource_queue; vtable D_0014FA70. */
class ResidentResourceQueue : public ResidentListObject
{
public:
    ResidentResourceRequest* requests;
    s32 request_capacity;
    s32 active_request;
    struct ResidentArchive* archive;
    ResidentSemaphore semaphore;
    u8 unk2c;
    u8 status;
    u8 unk2e;
    u8 cancel_pending;
    u8 unk30;
    ResidentResourceQueueListener listener;

    /** @brief Create the semaphore, register with the archive and allocate a 256-entry request table. */
    ResidentResourceQueue();

    /** @brief Stop listening to the archive and free the request table. */
    ~ResidentResourceQueue();

    /** @brief Process the queue under its semaphore until nothing more can start. */
    virtual void update();
};
#endif

typedef struct ResidentResourceQueue ResidentResourceQueue;

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

#ifdef __cplusplus
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
bool resident_queue_resource_request(ResidentResourceQueue* queue, s32 file_key, void* buffer, u32 tag, s32 priority,
                                     void* completion_callback, u32 byte_count, s32 file_offset, u8 request_kind);

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
bool resident_queue_resource_range_request(ResidentResourceQueue* queue, s32 file_key, void* buffer, s32 file_offset, u32 byte_count, u32 tag,
                   s32 priority, void* completion_callback);

/**
 * @brief Queue a request of kind four, which carries an object instead of a read.
 * @param queue Resident resource queue.
 * @param priority Lower values run first; minus one inserts at the front.
 * @param context Object the request carries.
 * @param tag Tag retained for later lookup and cancellation.
 * @param completion_callback Optional callback object notified when the request finishes.
 * @return True when queued, or false when no request slot remains.
 */
bool resident_queue_object_request(ResidentResourceQueue* queue, s32 priority, ResidentListener* context, u32 tag, void* completion_callback);
#endif

/**
 * @brief Start the next queued read when the archive is idle.
 * @param queue Resident resource queue.
 */
void resident_start_next_resource_request(ResidentResourceQueue* queue);

#ifdef __cplusplus
/**
 * @brief Finish the active request once the archive is done with it.
 * @param queue Resident resource queue.
 * @return True when a request finished, so another pass may start more work.
 */
bool resident_finish_resource_request(ResidentResourceQueue* queue);
#endif

/**
 * @brief Cancel the active read, then empty the request table and its queued list.
 * @param queue Resident resource queue.
 */
void resident_clear_resource_requests(ResidentResourceQueue* queue);

/**
 * @brief Stop the active read and clear the archive's pending flags.
 * @param queue Resident resource queue.
 */
void resident_stop_resource_read(ResidentResourceQueue* queue);

/**
 * @brief Process completed work, then report whether any request is still queued.
 * @param queue Resident resource queue.
 * @return Nonzero when the queue is empty.
 */
s32 resident_poll_resource_queue(ResidentResourceQueue* queue);

/**
 * @brief Lower the priority of every queued request that is still positive.
 * @param queue Resident resource queue.
 */
void resident_lower_resource_priorities(ResidentResourceQueue* queue);

/**
 * @brief Replace the request table with an empty one.
 * @param queue Resident resource queue.
 * @param capacity Number of entries in the new table.
 * @return One on success, or zero when the table cannot be allocated.
 */
s32 resident_reset_resource_request_table(ResidentResourceQueue* queue, s32 capacity);

/**
 * @brief Register the queue's listener with the archive again.
 * @param queue Resident resource queue.
 */
void resident_reregister_resource_queue(ResidentResourceQueue* queue);

#ifdef __cplusplus
#endif


/**
 * @brief Set the listener the archive notifies when a read finishes.
 * @param archive Resource archive.
 * @param listener Listener, or null to remove it.
 * @param context Object passed back to the listener.
 * @return The listener it replaces.
 */
struct ResidentListener* resident_archive_set_listener(ResidentArchive* archive, struct ResidentListener* listener, void* context);

#ifdef __cplusplus
}
#endif

#endif
