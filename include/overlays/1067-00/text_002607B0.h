#ifndef SO3_OVERLAYS_1067_00_TEXT_002607B0_H
#define SO3_OVERLAYS_1067_00_TEXT_002607B0_H

#include "overlays/1067-00/text_002636B0.h"

typedef struct FieldObject153D20 FieldObject153D20;
typedef struct FieldObject153E00 FieldObject153E00;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 2.
 */
s32 func_00260840(FieldObject153D20* object);

/**
 * @brief Read the unsigned value at offset 0x0A.
 * @param object Receiver to inspect.
 * @return Stored value.
 */
u16 func_00262B90(const FieldObject15AE70* object);

/**
 * @brief Read the unsigned value at offset 0x08.
 * @param object Receiver to inspect.
 * @return Stored value.
 */
u8 func_00262BA0(const FieldObject15AE70* object);

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 3.
 */
s32 func_00263680(FieldObject153E00* object);

#ifdef __cplusplus
}
#endif

#endif
