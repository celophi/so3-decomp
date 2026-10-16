#ifndef SO3_CLAMP_H
#define SO3_CLAMP_H

#include "ee.h"

/**
 * @brief Clamp value to [low, high] without branching.
 *
 * Shared by every clamp I've found so far, so it's written once here. Values
 * stored with a bias add it before the call and remove it after.
 * @param value Value to clamp.
 * @param low Lowest allowed value.
 * @param high Highest allowed value.
 * @return value limited to [low, high].
 */
static inline s32 clamp(s32 value, s32 low, s32 high)
{
    value = ee_movn(value, low, value < low);
    value = ee_movz(value, high, value <= high);
    return value;
}

#endif
