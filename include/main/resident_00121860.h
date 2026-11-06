#ifndef SO3_MAIN_RESIDENT_00121860_H
#define SO3_MAIN_RESIDENT_00121860_H

#include "types.h"

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
s32 func_00121860(const char* name, void* value, s32 kind);
/** @brief Do nothing. */
void func_00121870(void);
/**
 * @brief Do nothing.
 * @param object Unused receiver.
 */
void func_00121880(void* object);
/**
 * @brief Hook Lib calls after it installs a display, and boot before it restarts Lib; empty in the retail build.
 * @param display Display being installed.
 */
void resident_display_set_hook(void* display);

#ifdef __cplusplus
}
#endif

#endif
