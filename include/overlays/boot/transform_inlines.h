#ifndef SO3_OVERLAYS_BOOT_TRANSFORM_INLINES_H
#define SO3_OVERLAYS_BOOT_TRANSFORM_INLINES_H

#include "overlays/boot/text_001DD3C0.h"

#ifdef __cplusplus

/** @brief Store the halfword at offset 0x6A. @param value Value to store. */
inline void BootClass178A90::func_001DFE30(u16 value)
{
    unk6a = value;
}

/** @brief Store the halfword at offset 0x6C. @param value Value to store. */
inline void BootClass178A90::func_001DFE40(u16 value)
{
    unk6c = value;
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
inline BootClass170D50::BootClass170D50()
{
}

/** @brief Initialize the owner's state bytes and tracking words. */
inline BootClass178A90::BootClass178A90()
{
    unk60 = 0;
    unk61 = 0;
    unk63 = 0;
    unk66 = 0;
    unk68 = 0;
    unk69 = 0;
    unk6a = 0x10;
    unk6c = 1;
    unk80 = 0;
    unk88 = 0;
    unk8c = 0;
    unk0f = 2;
}

#endif

#endif
