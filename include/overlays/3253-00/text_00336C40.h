#ifndef SO3_OVERLAYS_3253_00_TEXT_00336C40_H
#define SO3_OVERLAYS_3253_00_TEXT_00336C40_H

#include "types.h"

struct BattleObject2F26;

#ifdef __cplusplus
extern "C" {
#endif

/** Forward the state pair to func_00292930. */
void func_0033EEF0(BattleObject2F26* object, u8 current, u8 previous);

/** Call func_00286130 when the float at receiver offset 0x2FA4 is zero. */
void func_0033EB10(void* object);

/** Set two state bytes when previous is 13, then forward the state pair. */
void func_0033DD80(BattleObject2F26* object, u8 current, u8 previous);
void func_00342200(BattleObject2F26* object, u8 current, u8 previous);

#ifdef __cplusplus
}
#endif

#endif
