#ifndef SO3_MAIN_FUNC_0011EE00_H
#define SO3_MAIN_FUNC_0011EE00_H

#include "main/resident_0010A0E0.h"

#ifdef __cplusplus
extern "C" {
#endif

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
