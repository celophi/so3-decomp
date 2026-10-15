#ifndef SO3_OVERLAYS_3454_00_TEXT_00340310_H
#define SO3_OVERLAYS_3454_00_TEXT_00340310_H

#include "overlays/3454-00/text_0027E060.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Forward the object and two selector bytes to func_0028BDB0. */
void func_0034C9C0(Obj27E060* object, u8 first_code, u8 second_code);

/**
 * @brief Clear two state words and apply the supplied state transition.
 * @param object State object to update.
 * @param current Current state value.
 * @param previous Previous state value.
 */
void func_003449B0(Obj27E060* object, u8 current, u8 previous);

/** Call func_0027E740 when the float at receiver offset 0x2F94 is zero. */
void func_0034C5E0(void* object);

#ifdef __cplusplus
}
#endif

#endif
