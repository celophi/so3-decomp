#ifndef SO3_MAIN_RESIDENT_0010A0E0_H
#define SO3_MAIN_RESIDENT_0010A0E0_H

#include "types.h"

/** Partial ring buffer of 0x400 object pointers with write and read indices. */
typedef struct ResidentObjectQueue
{
    u8 unk00[0x1008];
    s32 write;
    s32 read;
    void* entries[0x400];
} ResidentObjectQueue;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Append an object to the ring buffer unless it is full.
 * @param queue Queue to append to.
 * @param object Object to append; null is accepted and ignored.
 * @return 1 when the object was appended or is null, 0 when the queue is full.
 */
s32 func_0011ED90(ResidentObjectQueue* queue, void* object);

#ifdef __cplusplus
}
#endif

#endif
