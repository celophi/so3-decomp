#ifndef SO3_OVERLAYS_1067_00_TEXT_002934A0_H
#define SO3_OVERLAYS_1067_00_TEXT_002934A0_H

#include "types.h"

typedef struct FieldObject1573D0 FieldObject1573D0;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 4.
 */
s32 func_002934D0(FieldObject1573D0* object);

/**
 * @brief Initialize the object's float values and two state bits.
 * @param object Object to initialize.
 * @param first_value Value stored at offset 0x24.
 * @param second_value Value stored at offset 0x20.
 * @param third_value Value stored at offset 0x2C.
 */
void func_002934E0(FieldObject1573D0* object, float first_value, float second_value, float third_value);

/**
 * @brief Advance the object's float transition while its active bit is set.
 * @param object Object with the transition state and embedded curve.
 */
void func_00293540(FieldObject1573D0* object);

#ifdef __cplusplus
}
#endif

#endif
