#ifndef SO3_OVERLAYS_1067_00_TEXT_0023B1D0_H
#define SO3_OVERLAYS_1067_00_TEXT_0023B1D0_H

#include "types.h"

typedef struct FieldState23B3A0 FieldState23B3A0;
typedef struct FieldObject153270 FieldObject153270;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read the unsigned halfword at offset 0x90.
 * @param object Receiver.
 * @return The current unsigned halfword.
 */
u16 func_0023B3A0(FieldState23B3A0* object);

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 4.
 */
s32 func_0023D2B0(FieldObject153270* object);

#ifdef __cplusplus
}
#endif

#endif
