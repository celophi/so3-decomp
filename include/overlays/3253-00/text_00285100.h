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

#ifdef __cplusplus
}
#endif

#endif
