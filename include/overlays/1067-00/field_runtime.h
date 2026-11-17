#ifndef SO3_OVERLAYS_1067_00_FIELD_RUNTIME_H
#define SO3_OVERLAYS_1067_00_FIELD_RUNTIME_H

#include "types.h"
#include "main/system.h"

/** Opaque resource-section directory in the resident system. */
typedef struct FieldRuntimeSections FieldRuntimeSections;

/** Resource section containing packed flags and variable words. */
typedef struct FieldRuntimeValues
{
    u8 unk00[4];
    u8 unk04[0x180];
    u8 flags_5000[4];
    u32 unk188[];
} FieldRuntimeValues;

#endif
