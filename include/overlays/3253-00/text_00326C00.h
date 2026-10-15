#ifndef SO3_OVERLAYS_3253_00_TEXT_00326C00_H
#define SO3_OVERLAYS_3253_00_TEXT_00326C00_H

#include "overlays/3253-00/text_00285100.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear two state words and apply the supplied state transition.
 * @param object Battle object to update.
 * @param current Current state value.
 * @param previous Previous state value.
 */
void func_00336590(BattleObject2F26* object, u8 current, u8 previous);

/** Set two state bytes when previous is 13, then forward the state pair. */
void func_0032F070(BattleObject2F26* object, u8 current, u8 previous);
void func_00333720(BattleObject2F26* object, u8 current, u8 previous);

/** Clean up the embedded object at 0x290 and clear the byte at 0x391. */
void func_00328240(void* object);

#ifdef __cplusplus
}
#endif

#endif
