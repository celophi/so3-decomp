#ifndef SO3_OVERLAYS_1067_00_TEXT_0024C4B0_H
#define SO3_OVERLAYS_1067_00_TEXT_0024C4B0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Append an object to the ring buffer at offset 0x220 unless it is full.
 * @param queue Receiver owning the ring buffer.
 * @param object Object to append.
 * @return 1 when the object was appended, 0 when the buffer is full.
 */
s32 func_0024CE10(void* queue, void* object);

#ifdef __cplusplus
}
#endif

#endif
