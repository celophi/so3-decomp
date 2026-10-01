#ifndef SO3_OVERLAYS_0002_01_TEXT_0045AD10_H
#define SO3_OVERLAYS_0002_01_TEXT_0045AD10_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Run the test at offset 0x30 of the object referenced by the first word of object.
 * @param object Object whose first word refers to the tested object.
 * @param arg0 First argument passed to the test.
 * @param arg1 Second argument passed to the test.
 * @return The test result.
 */
s32 func_0045BD20(void* object, void* arg0, void* arg1);

#ifdef __cplusplus
}
#endif

#endif
