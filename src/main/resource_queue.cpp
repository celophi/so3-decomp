#include "include_asm.h"
#include "main/debug.h"
#include "main/interrupt_lock.h"
#include "main/system.h"
#include "main/utility.h"

/** "StorageQueue Status", the name the resource queue registers its status under. */
extern const char g_storage_queue_status_name[];

/** @brief Do nothing. */
void ResidentListener::reserved()
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
        resident_start_next_resource_request(queue);
    } while (resident_finish_resource_request(queue));

    return queue->cancel_pending;
}

/**
 * @brief Stop the active read and clear the archive's pending flags.
 * @param queue Resident resource queue.
 */
extern "C" void resident_stop_resource_read(ResidentResourceQueue* queue)
{
    queue->unk30 = 0;

    ResidentArchive* archive = queue->archive;

    archive->unk12186 = 0;
    archive->disc_thread.unkAC.unk1d = 0;

    if (queue->unk2c)
    {
        resident_archive_release_read(queue->archive);
    }
}

/**
 * @brief Relink the first queued request of kind 4 at the head of the request list.
 * @param queue Resource queue.
 * @return True when such a request was found.
 */
extern "C" bool resident_promote_object_request(ResidentResourceQueue* queue)
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
        resident_start_next_resource_request(queue);
    } while (resident_finish_resource_request(queue));

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
extern "C" void resident_start_next_resource_request(ResidentResourceQueue* queue)
{
    if (queue->unk2c && resident_promote_object_request(queue))
    {
        s32 index = queue->requests[0].next;

        if (index == 0)
        {
            return;
        }

        if (!queue->status && !queue->unk2e)
        {
            resident_archive_hold_read(queue->archive);

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
        if (resident_archive_select_resource(queue->archive, queue->requests[index].file_key))
        {
            resident_archive_start_read_unchecked(queue->archive, queue->requests[index].buffer, queue->requests[index].byte_count);
            queue->status = 1;
            queue->requests[index].state = 1;
        }

        break;

    case 2:
        if (resident_archive_select_counted(queue->archive, queue->requests[index].file_offset, queue->requests[index].file_key))
        {
            queue->status = 1;
            queue->requests[index].state = 1;
        }

        break;

    case 3:
        if (resident_archive_is_idle(queue->archive) &&
            resident_archive_select_counted(queue->archive, queue->requests[index].file_offset, queue->requests[index].file_key))
        {
            resident_archive_start_read_unchecked(queue->archive, queue->requests[index].buffer, queue->requests[index].byte_count);
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
extern "C" bool resident_finish_resource_request(ResidentResourceQueue* queue)
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
 * @brief Update the object the archive passes back.
 * @param data Object to update.
 */
void ResidentResourceQueueListener::notify(void* data)
{
    static_cast<ResidentListObject*>(data)->update();
}

/**
 * @brief Lower the priority of every queued request that is still positive.
 * @param queue Resident resource queue.
 */
extern "C" void resident_lower_resource_priorities(ResidentResourceQueue* queue)
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
void ResidentResourceQueue::update()
{
    (void)semaphore.wait();

    if (unk30)
    {
        archive->disc_thread.unk70++;
    }

    do
    {
        resident_start_next_resource_request(this);
    } while (resident_finish_resource_request(this));

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
        resident_start_next_resource_request(queue);
    } while (resident_finish_resource_request(queue));

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
extern "C" bool resident_queue_object_request(ResidentResourceQueue* queue, s32 priority, ResidentListener* context, u32 tag, void* completion_callback)
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
extern "C" bool resident_queue_resource_range_request(ResidentResourceQueue* queue, s32 file_key, void* buffer, s32 file_offset, u32 byte_count,
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
            resident_archive_stop_ring_read(queue->archive);
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
        resident_start_next_resource_request(queue);
    }

    return true;
}

/**
 * @brief Cancel the active read, then empty the request table and its queued list.
 * @param queue Resident resource queue.
 */
extern "C" void resident_clear_resource_requests(ResidentResourceQueue* queue)
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
extern "C" s32 resident_reset_resource_request_table(ResidentResourceQueue* queue, s32 capacity)
{
    delete[] queue->requests;
    queue->requests = new (0) ResidentResourceRequest[capacity];

    if (queue->requests == 0)
    {
        return 0;
    }

    queue->request_capacity = capacity;
    resident_clear_resource_requests(queue);
    return 1;
}

/**
 * @brief Register the queue's listener with the archive again.
 * @param queue Resident resource queue.
 */
extern "C" void resident_reregister_resource_queue(ResidentResourceQueue* queue)
{
    resident_archive_set_listener(queue->archive, &queue->listener, queue);
}

/** @brief Stop listening to the archive and free the request table. */
ResidentResourceQueue::~ResidentResourceQueue()
{
    resident_archive_set_listener(archive, 0, 0);
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

    resident_archive_set_listener(archive, &listener, this);
    resident_debug_register_value(g_storage_queue_status_name, &status, 1);
    resident_reset_resource_request_table(this, 0x100);
}

/**
 * @brief Return the object's kind.
 * @return Three.
 */
s32 ResidentListObject::get_default_list_kind()
{
    return 3;
}

/** @brief Destroy the object through its virtual destructor. */
void ResidentListObject::destroy()
{
    delete this;
}

/** @brief Update the object; the base does nothing. */
void ResidentListObject::update()
{
}

void ResidentListObject::render()
{
}
