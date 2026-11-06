#ifndef SO3_OVERLAYS_BOOT_TRANSFORM_INLINES_H
#define SO3_OVERLAYS_BOOT_TRANSFORM_INLINES_H

#include "overlays/boot/boot.h"

#ifdef __cplusplus

#include "overlays/lib/transform_owner_inlines.h"

/** @brief Clear the rectangle. */
inline LibScreenRect::LibScreenRect()
{
    height = 0;
    width = 0;
    y = 0;
    x = 0;
}

#include "overlays/lib/dma_callbacks_inlines.h"

#endif

#endif
