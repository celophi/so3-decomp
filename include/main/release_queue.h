#ifndef SO3_MAIN_RELEASE_QUEUE_H
#define SO3_MAIN_RELEASE_QUEUE_H

#include "types.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"
#include "gs.h"

/**
 * Pointer ring with write_index at the next insertion slot and read_index at the
 * last released slot. Equal indices mean full; an empty ring has write_index
 * one slot ahead of read_index, wrapping at 0x400.
 */
typedef struct ResidentReleaseRing
{
    s32 write_index;
    s32 read_index;
    void* entries[0x400];
} ResidentReleaseRing;

/** Resident rings for deferred allocation release and object destruction. */
typedef struct ResidentReleaseQueues
{
    ResidentReleaseRing allocations;
    ResidentReleaseRing objects;
    void* vtable;

#ifdef __cplusplus
    /** @brief Start with both release rings empty. */
    ResidentReleaseQueues();

    /** @brief Drain both release rings. */
    ~ResidentReleaseQueues();
#endif
} ResidentReleaseQueues;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Queue an object for destruction by its virtual destructor.
 * @param queue Deferred release queues.
 * @param object Object to destroy later; null succeeds without insertion.
 * @return One on success, or zero when the object ring is full.
 */
s32 resident_enqueue_object(ResidentReleaseQueues* queue, void* object);

/**
 * @brief Release pending allocations, then destroy pending objects and flush the cache.
 * @param queues Deferred release queues to drain.
 */
void resident_drain_release_queues(ResidentReleaseQueues* queues);


/**
 * @brief Queue an allocation for release with operator delete.
 * @param queues Deferred release queues.
 * @param allocation Allocation to release later; null succeeds without insertion.
 * @return One on success, or zero when the allocation ring is full.
 */
s32 resident_queue_allocation_release(ResidentReleaseQueues* queues, void* allocation);

#ifdef __cplusplus
}
#endif

#endif
