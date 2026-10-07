#ifndef SO3_OVERLAYS_1067_00_TEXT_MARKER_H
#define SO3_OVERLAYS_1067_00_TEXT_MARKER_H

#include "overlays/lib/text_00419A70.h"

#ifdef __cplusplus
/** Field text marker with primary vtable at 0x153170. */
class FieldClass153170 : public ItemCreationClass172870
{
public:
    /** @brief Initialize the Field target marker. */
    FieldClass153170();
    /** @brief Destroy the Field target marker. */
    virtual ~FieldClass153170();
    /**
     * @brief Configure the marker for a text display.
     * @param target Text display used for the marker bounds.
     * @param color Packed marker color.
     */
    void func_0023B850(LibObject178750* target, u32 color);
    /** @brief Update the marker bounds. @param target Text display to follow. */
    void func_0023B7E0(LibObject178750* target);
    /** @brief Refresh the marker bounds when target tracking is enabled. */
    virtual void func_00413D20();
    void* unk58;
    u8 unk5c;
};

#endif

#endif
