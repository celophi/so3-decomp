#ifndef SO3_OVERLAYS_1067_00_TEXT_0028E240_H
#define SO3_OVERLAYS_1067_00_TEXT_0028E240_H

#include "types.h"

typedef struct FieldRecordSelection FieldRecordSelection;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Select entries with a nonzero value and clear state from the current field table.
 * @param selection Destination for table links, selected bytes, and a count.
 * @return Zero when either table link is missing; otherwise one.
 */
s32 func_0028E3D0(FieldRecordSelection* selection);

/**
 * @brief Find a record whose first value matches the given byte.
 * @param selection Selection with the record table to search.
 * @param value Signed byte value to find.
 * @return Record index, or -1 if no record matches.
 */
s32 func_0028E240(FieldRecordSelection* selection, s8 value);

#ifdef __cplusplus
}
#endif

#endif
