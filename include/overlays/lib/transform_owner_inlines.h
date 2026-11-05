#ifndef SO3_OVERLAYS_LIB_TRANSFORM_OWNER_INLINES_H
#define SO3_OVERLAYS_LIB_TRANSFORM_OWNER_INLINES_H

#include "overlays/lib/text_004CD3A0.h"

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
    display_manager = 0;
    unk88 = 0;
    unk8c = 0;
    object_kind = 2;
}

#endif

#endif
