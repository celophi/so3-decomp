#include "main/func_0011EE00.h"

/**
 * @brief Check whether a release ring has no insertion slot available.
 * @param ring Release ring to check.
 * @return One when the ring is full, or zero when it has space.
 */
static inline s32 resident_release_ring_is_full(const ResidentReleaseRing* ring)
{
    return ring->read_index == ring->write_index;
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

    if (resident_release_ring_is_full(ring))
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
