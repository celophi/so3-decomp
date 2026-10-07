#ifndef SO3_OVERLAYS_CITEMCREATION_ITEM_DISPLAY_INLINES_H
#define SO3_OVERLAYS_CITEMCREATION_ITEM_DISPLAY_INLINES_H

#include "overlays/citemcreation/text_003483C0.h"

#ifdef __cplusplus

#include "overlays/lib/marker_widget_inlines.h"

#include "overlays/lib/resource_widget_inlines.h"

#include "overlays/lib/movement_widget_inlines.h"

#include "overlays/lib/list_indicator_inlines.h"

#include "overlays/1067-00/text_0023B1D0.h"

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
    void* unk58;
    u8 unk5c;
};

#endif

#endif
