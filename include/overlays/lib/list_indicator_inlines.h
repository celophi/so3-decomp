#ifndef SO3_OVERLAYS_LIB_LIST_INDICATOR_INLINES_H
#define SO3_OVERLAYS_LIB_LIST_INDICATOR_INLINES_H

#include "overlays/lib/text_00419A70.h"

#ifdef __cplusplus
/** @brief Initialize the widget storage and select kind 3. */
inline LibListIndicator::LibListIndicator()
{
    unk38 = 3;
}

inline LibListIndicator::LibListIndicator(float x, float y, float height, float extent, float position)
{
    unk38 = 3;
    lib_list_indicator_init(this, x, y, height, extent, position);
}

#endif

#endif
