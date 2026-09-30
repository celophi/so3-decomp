#ifndef SO3_OVERLAYS_1067_00_TEXT_0022DC70_H
#define SO3_OVERLAYS_1067_00_TEXT_0022DC70_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Submit a newly allocated request for the receiver when its state bits permit, then update those bits.
 * @param object Receiver whose state bits are checked and updated.
 * @param flag Nonzero to give the request a pseudo-random bit.
 */
/**
 * @brief Release the object stored at offset 0x548 through its virtual handler at vtable offset 0x10, then clear the field.
 * @param object Receiver owning the stored object.
 */
void func_00233620(void* object);

/**
 * @brief Create and register the object stored at offset 0x548 when the current state permits it.
 * @param object Receiver owning the stored object.
 */
void func_00234000(void* object);

void func_002379A0(void* object, s32 flag);

#ifdef __cplusplus
}
#endif

#endif
