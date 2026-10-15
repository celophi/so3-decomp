#ifndef SO3_OVERLAYS_3253_00_TEXT_00285100_H
#define SO3_OVERLAYS_3253_00_TEXT_00285100_H

#include "types.h"

struct BattleObject2E0B;
struct BattleObject2F26;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear selected fields according to two state values.
 * @param object Battle object whose state fields are updated.
 * @param current First state value.
 * @param previous Second state value.
 */
void func_0028E2A0(BattleObject2E0B* object, u8 current, u8 previous);

/**
 * @brief Clear a second set of fields according to two state values.
 * @param object Battle object whose state fields are updated.
 * @param current First state value.
 * @param previous Second state value.
 */
void func_00292930(BattleObject2F26* object, u8 current, u8 previous);

/** Forward the receiver and return the result from func_002B08B0. */
s32 func_00285280(void* object);

/** Clear the selected state when the 0x2A4B00 check succeeds. */
void func_002851E0(void* object);
/** Clear the selected state when the 0x2983E0 check succeeds. */
void func_00285DE0(void* object);

#ifdef __cplusplus
}
#endif

#endif
