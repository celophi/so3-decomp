#ifndef SO3_OVERLAYS_BOOT_TRANSFORM_INLINES_H
#define SO3_OVERLAYS_BOOT_TRANSFORM_INLINES_H

#include "overlays/boot/text_001DD3C0.h"

#ifdef __cplusplus

/**
 * @brief Set the draw flags (LIB_DRAW_*).
 * @param value New flags.
 */
inline void LibTransformOwner::set_draw_flags(u16 value)
{
    draw_flags = value;
}

/**
 * @brief Set the object's type ID.
 * @param value Type ID.
 */
inline void LibTransformOwner::set_type_id(u16 value)
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

#include "overlays/lib/dma_callbacks_inlines.h"

/** @brief Initialize the owner's state bytes and tracking words. */
inline LibTransformOwner::LibTransformOwner()
{
    draw_bucket = 0;
    matrix_ready = 0;
    unk63 = 0;
    unk66 = 0;
    unk68 = 0;
    unk69 = 0;
    draw_flags = LIB_DRAW_FLAG_0010;
    type_id = 1;
    unk80 = 0;
    unk88 = 0;
    unk8c = 0;
    object_kind = 2;
}

#endif

#endif
