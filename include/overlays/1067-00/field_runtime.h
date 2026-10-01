#ifndef SO3_OVERLAYS_1067_00_FIELD_RUNTIME_H
#define SO3_OVERLAYS_1067_00_FIELD_RUNTIME_H

#include "types.h"

/** Opaque resident runtime root and its resource-section directory. */
typedef struct FieldRuntimeRoot FieldRuntimeRoot;
typedef struct FieldRuntimeSections FieldRuntimeSections;

/** Resource section containing packed flags and variable words. */
typedef struct FieldRuntimeValues
{
    u8 unk00[4];
    u8 unk04[0x180];
    u8 unk184[4];
    u32 unk188[];
} FieldRuntimeValues;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the resident runtime root.
 * @return Resident root pointer.
 */
FieldRuntimeRoot* func_10D8E0(void);

/**
 * @brief Get the runtime root's resource-section directory.
 * @param root Resident runtime root.
 * @return Embedded section directory.
 */
FieldRuntimeSections* func_101290(FieldRuntimeRoot* root);

/**
 * @brief Find a resource section by its directory key.
 * @param sections Resource-section directory.
 * @param key Section key to find.
 * @return Section data, or null when no entry matches.
 */
void* func_101440(FieldRuntimeSections* sections, s32 key);

#ifdef __cplusplus
}
#endif

#endif
