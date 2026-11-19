#ifndef SO3_OVERLAYS_LIB_LIGHT_RANDOM_H
#define SO3_OVERLAYS_LIB_LIGHT_RANDOM_H

#include "types.h"

/** Seed of the 1664525/1013904223 linear congruential sequence Lib's lights draw from. */
extern "C" u32 D_001B65B8;

/**
 * @brief Advance the light random seed.
 * @return New seed.
 */
static inline u32 lib_light_random()
{
    D_001B65B8 = 1664525L * D_001B65B8 + 1013904223L;
    return D_001B65B8;
}

/**
 * @brief Turn the next light random seed into a fraction by using its low 23 bits as a float mantissa.
 * @return Random value from 0 up to 1.
 */
static inline float lib_light_random_fraction()
{
    u32 bits = (lib_light_random() & 0x7FFFFF) | 0x3F800000;
    return *(float*)&bits - 1.0f;
}

#endif
