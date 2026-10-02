#ifndef OVERLAYS_3253_00_TEXT_003D7950_H
#define OVERLAYS_3253_00_TEXT_003D7950_H

#include "types.h"

struct BattleState7950
{
    u8 unk00[0x60];
    u8 unk60;
};

/**
 * @brief Set the object's state byte to 10.
 * @param object Object whose state is changed.
 */
extern "C" void func_003D7B70(BattleState7950* object);

#endif
