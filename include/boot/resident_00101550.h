#ifndef SO3_BOOT_RESIDENT_00101550_H
#define SO3_BOOT_RESIDENT_00101550_H

#include "types.h"

/** Dispatch table whose complete layout is not yet known. */
typedef struct ResidentDispatchTable ResidentDispatchTable;

/** Partial prefix of an object registered with the resident dispatcher. */
typedef struct ResidentRegisteredObject
{
    const ResidentDispatchTable* dispatch;
} ResidentRegisteredObject;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the dispatch pointer and register the object.
 * @param object Object to register.
 * @return The registered object.
 */
ResidentRegisteredObject* func_00101560(ResidentRegisteredObject* object);

#ifdef __cplusplus
}
#endif

#endif
