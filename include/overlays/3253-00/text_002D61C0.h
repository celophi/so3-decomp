#ifndef SO3_OVERLAYS_3253_00_TEXT_002D61C0_H
#define SO3_OVERLAYS_3253_00_TEXT_002D61C0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Return whether the helper reports a nonzero low byte. */
s32 func_002E2170(void* object, s32 arg2, s32 arg3);
/** Clean up the embedded object at 0x290 and clear the byte at 0x391. */
void func_002DE7D0(void* object);
/** Call the object cleanup helper, then clear the byte at receiver offset 0x2F68. */
void func_002E4CF0(void* receiver);

/** Run the paired update helpers in order. */
void func_002E4360(void* object);
void func_002E4390(void* object);

#ifdef __cplusplus
}
#endif

#endif
