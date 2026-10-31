#ifndef SO3_OVERLAYS_1067_00_FIELD_RUNTIME_H
#define SO3_OVERLAYS_1067_00_FIELD_RUNTIME_H

#include "types.h"
#include "main/resident_0010A0E0.h"

/** Opaque resource-section directory in the resident system. */
typedef struct FieldRuntimeSections FieldRuntimeSections;

/** Resource section containing packed flags and variable words. */
typedef struct FieldRuntimeValues
{
    u8 unk00[4];
    u8 unk04[0x180];

    /** Packed flag bank selected by script keys 0x5000 through 0x501F. */
    u8 flags_5000[4];

    u32 unk188[];
} FieldRuntimeValues;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the resident system's resource-section directory.
 * @param system Resident system.
 * @return Embedded section directory.
 */
FieldRuntimeSections* func_101290(ResidentSystem* system);

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
