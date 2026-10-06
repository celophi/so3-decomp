#ifndef SO3_OVERLAYS_CITEMCREATION_ITEM_DISPLAY_INLINES_H
#define SO3_OVERLAYS_CITEMCREATION_ITEM_DISPLAY_INLINES_H

#include "overlays/citemcreation/text_003483C0.h"

#ifdef __cplusplus

/** @brief Initialize the widget storage and select kind 6. */
inline ItemCreationClass172870::ItemCreationClass172870()
{
    unk38 = 6;
}

/** @brief Initialize the widget storage and select kind 4. */
inline ItemCreationClass1746A0::ItemCreationClass1746A0()
{
    unk38 = 4;
}

/** @brief Initialize the widget storage and select kind 9. */
inline ItemCreationClass175030::ItemCreationClass175030()
{
    unk38 = 9;
}

/** @brief Initialize the widget storage and select kind 3. */
inline ItemCreationClass1725D0::ItemCreationClass1725D0()
{
    unk38 = 3;
}

/** Field selection widget with primary vtable at 0x153130. */
class FieldClass153130 : public ItemCreationClass175030
{
public:
    /** @brief Initialize the Field selection widget. */
    FieldClass153130();
    /** @brief Destroy the Field selection widget. */
    virtual ~FieldClass153130();
    /**
     * @brief Configure the selection widget and its drawing dimensions.
     * @param first First selection code.
     * @param second Second selection code.
     * @param third Third selection code.
     * @param value Selection value.
     * @param flag Selection flag.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param z Third drawing coordinate.
     * @param extent Drawing extent.
     * @return Configuration status.
     */
    s32 func_0023B530(u8 first, u8 second, u8 third, u16 value, u8 flag,
                     float x, float y, float z, float extent);
    u8 unk7c;
    u8 unk7d;
    float unk80;
    float unk84;
    float unk88;
    float unk8c;
    u16 unk90;
    u8 unk92;
    u8 unk93;
    u16 unk94;
};

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
