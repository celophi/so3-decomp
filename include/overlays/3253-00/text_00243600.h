#ifndef SO3_OVERLAYS_3253_00_TEXT_00243600_H
#define SO3_OVERLAYS_3253_00_TEXT_00243600_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void func_0024AD60(void* object);

/**
 * @brief Clear byte 0x92, then run the supplied operation.
 * @param receiver Object containing byte 0x92.
 * @param arg1 First forwarded argument.
 * @param arg2 Second forwarded argument.
 * @param arg3 Third forwarded argument.
 * @return Result from the operation.
 */
s32 func_0024A960(void* receiver, void* arg1, s32 arg2, s32 arg3);

/**
 * @brief Run an operation on an object with three additional arguments.
 * @param receiver Operation object.
 * @param arg1 First additional argument.
 * @param arg2 Second additional argument.
 * @param arg3 Third additional argument.
 * @return Operation result.
 */
s32 func_0024A980(void* receiver, void* arg1, s32 arg2, s32 arg3);

#ifdef __cplusplus
}
#endif

#endif
