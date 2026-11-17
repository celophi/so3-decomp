#ifndef SO3_MAIN_PROGRAM_H
#define SO3_MAIN_PROGRAM_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"

#ifndef __cplusplus
typedef struct ResidentProgram ResidentProgram;
#endif

#ifdef __cplusplus

/** The running program, with vtable g_resident_program_vtable; its constructor registers it in g_current_program. */
class ResidentProgram
{
public:
    /** @brief Run the program; it ends by switching to the next one, so it never returns. */
    virtual void run();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** The running program; its constructor registers it, and switching programs calls its run(). */
extern struct ResidentProgram* g_current_program;

#ifdef __cplusplus
}
#endif

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
ResidentRegisteredObject* resident_program_construct(ResidentRegisteredObject* object);

#ifdef __cplusplus
}
#endif

#endif
