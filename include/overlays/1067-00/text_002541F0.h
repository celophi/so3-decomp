#ifndef SO3_OVERLAYS_1067_00_TEXT_002541F0_H
#define SO3_OVERLAYS_1067_00_TEXT_002541F0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct FieldObject1537C0 FieldObject1537C0;

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 3.
 */
s32 func_002541F0(FieldObject1537C0* object);

/**
 * @brief Detach the receiver from its owner and append it to the resident object queue.
 * @param object Receiver to detach and append.
 */
void func_00254200(void* object);

/**
 * @brief Return 8 when bit 1 of the resident context byte at 0xDF is clear.
 * @return 8 if the bit is clear, otherwise zero.
 */
s32 func_00254BD0(void);

#ifdef __cplusplus
}
#endif

#endif
