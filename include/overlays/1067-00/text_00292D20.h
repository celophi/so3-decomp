#ifndef SO3_OVERLAYS_1067_00_TEXT_00292D20_H
#define SO3_OVERLAYS_1067_00_TEXT_00292D20_H

#include "types.h"

typedef struct FieldObject1573A0 FieldObject1573A0;
typedef struct FieldOwner18 FieldOwner18;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 4.
 */
s32 func_00292D50(FieldObject1573A0* object);

/**
 * @brief Store a value on the object and set bit 7 in the current field context.
 * @param object Object receiving the value.
 * @param value Value to store.
 */
void func_00293350(FieldOwner18* object, u32 value);

#ifdef __cplusplus
}
#endif

#endif
