#ifndef SO3_OVERLAYS_LIB_ANIMATION_BINDING_H
#define SO3_OVERLAYS_LIB_ANIMATION_BINDING_H

#include "types.h"

enum
{
    LIB_ANIMATION_BINDING_CAPACITY = 16
};

/** Partial binding owner with sixteen animation links and their mode bytes. */
typedef struct LibAnimationBindingOwner
{
    u8 unk00[0x34];
    void* animation_slots[LIB_ANIMATION_BINDING_CAPACITY];
    u8 unk74[0x2B];
    u8 animation_modes[LIB_ANIMATION_BINDING_CAPACITY];
} LibAnimationBindingOwner;

#endif
