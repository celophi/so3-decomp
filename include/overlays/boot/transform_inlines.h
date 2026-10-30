#ifndef SO3_OVERLAYS_BOOT_TRANSFORM_INLINES_H
#define SO3_OVERLAYS_BOOT_TRANSFORM_INLINES_H

#include "overlays/boot/text_001DD3C0.h"

#ifdef __cplusplus

/**
 * @brief Set the draw flags (BOOT_DRAW_*).
 * @param value New flags.
 */
inline void BootTransformOwner::set_draw_flags(u16 value)
{
    draw_flags = value;
}

/**
 * @brief Set the object's type ID.
 * @param value Type ID.
 */
inline void BootTransformOwner::set_type_id(u16 value)
{
    type_id = value;
}

/** @brief Clear all four words. */
inline BootWordQuad::BootWordQuad()
{
    unk0c = 0;
    unk08 = 0;
    unk04 = 0;
    unk00 = 0;
}

/** @brief Install the interface's vtable. */
inline BootDmaCallbacks::BootDmaCallbacks()
{
}

/** @brief Initialize the owner's state bytes and tracking words. */
inline BootTransformOwner::BootTransformOwner()
{
    draw_bucket = 0;
    matrix_ready = 0;
    unk63 = 0;
    unk66 = 0;
    unk68 = 0;
    unk69 = 0;
    draw_flags = BOOT_DRAW_FLAG_0010;
    type_id = 1;
    unk80 = 0;
    unk88 = 0;
    unk8c = 0;
    object_kind = 2;
}

#endif

#endif
