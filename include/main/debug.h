#ifndef SO3_MAIN_DEBUG_H
#define SO3_MAIN_DEBUG_H

#include "types.h"
#include "main/resource_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Register a named value with the debug display; this build's version does nothing and returns -1.
 * @param name Name shown for the value, such as "StorageQueue Status".
 * @param value Value to show.
 * @param kind Unknown; both callers pass one.
 * @return -1.
 */
s32 resident_debug_register_value(const char* name, void* value, s32 kind);

/** @brief Do nothing. */
void resident_debug_initialize(void);

/**
 * @brief Hook Lib calls after it installs a display, and boot before it restarts Lib; empty in the retail build.
 * @param display Display being installed.
 */
void resident_display_set_hook(void* display);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/** Listener for the debug display (vtable D_0014FDE0); the retail build ignores every notification. */
class ResidentDebugListener : public ResidentListener
{
    public:
        virtual void notify(void* data);
};
#endif

#endif
