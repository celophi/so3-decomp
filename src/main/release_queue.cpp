#include "include_asm.h"
#include "main/resident_data.h"

/**
 * @brief Check whether a release ring has no insertion slot available.
 * @param ring Release ring to check.
 * @return True when the ring is full, or false when it has space.
 */
static inline bool release_ring_is_full(const ResidentReleaseRing* ring)
{
    return ring->read_index == ring->write_index;
}

extern "C" {

/**
 * @brief Release pending allocations, then destroy pending objects and flush the cache.
 * @param queues Deferred release queues to drain.
 */
void resident_drain_release_queues(ResidentReleaseQueues* queues)
{
    for (;;)
    {
        s32 next = queues->allocations.read_index + 1;

        if (next >= 0x400)
        {
            next = 0;
        }

        if (next == queues->allocations.write_index)
        {
            break;
        }

        ::operator delete(queues->allocations.entries[next]);
        queues->allocations.read_index = next;
    }

    for (;;)
    {
        s32 next = queues->objects.read_index + 1;

        if (next >= 0x400)
        {
            next = 0;
        }

        if (next == queues->objects.write_index)
        {
            break;
        }

        delete static_cast<ResidentLink*>(queues->objects.entries[next]);
        queues->objects.read_index = next;
    }

    FlushCache(0);
}

/**
 * @brief Queue an object for destruction by its virtual destructor.
 * @param queue Deferred release queues.
 * @param object Object to destroy later; null succeeds without insertion.
 * @return One on success, or zero when the object ring is full.
 */
s32 resident_enqueue_object(ResidentReleaseQueues* queue, void* object)
{
    if (object == 0)
    {
        return 1;
    }

    if (release_ring_is_full(&queue->objects))
    {
        return 0;
    }

    queue->objects.entries[queue->objects.write_index++] = object;

    if (queue->objects.write_index >= 0x400)
    {
        queue->objects.write_index = 0;
    }

    return 1;
}
}

/**
 * @brief Queue an allocation for release with operator delete.
 * @param queues Deferred release queues.
 * @param allocation Allocation to release later; null succeeds without insertion.
 * @return One on success, or zero when the allocation ring is full.
 */
s32 resident_queue_allocation_release(ResidentReleaseQueues* queues, void* allocation)
{
    ResidentReleaseRing* ring = &queues->allocations;

    if (allocation == 0)
    {
        return 1;
    }

    if (release_ring_is_full(ring))
    {
        return 0;
    }

    ring->entries[ring->write_index++] = allocation;

    if (ring->write_index >= 0x400)
    {
        ring->write_index = 0;
    }

    return 1;
}

extern "C" {
extern u8 g_resident_release_queues_vtable[];
}

/** @brief Drain both release rings. */
ResidentReleaseQueues::~ResidentReleaseQueues()
{
    vtable = g_resident_release_queues_vtable;
    resident_drain_release_queues(this);
}

/** @brief Start with both release rings empty. */
ResidentReleaseQueues::ResidentReleaseQueues()
{
    vtable = g_resident_release_queues_vtable;
    allocations.write_index = 1;
    allocations.read_index = 0;
    objects.write_index = 1;
    objects.read_index = 0;
}
