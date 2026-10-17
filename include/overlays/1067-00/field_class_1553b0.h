#ifndef SO3_OVERLAYS_1067_00_FIELD_CLASS_1553B0_H
#define SO3_OVERLAYS_1067_00_FIELD_CLASS_1553B0_H

#include "overlays/1067-00/text_001DD3C0.h"

#ifdef __cplusplus
/** 0x20-byte Field controller base with native table 0x1553B0. */
class FieldClass1553B0 : public FieldListObject
{
public:
    /** @brief Initialize the controller state. */
    FieldClass1553B0()
    {
        unk1C_0 = 0;
        unk18 = 0;
    }

    /** @brief Destroy the controller. */
    virtual ~FieldClass1553B0()
    {
    }

    /** @brief Detach the controller and queue it for release. */
    virtual void func_001DD7B0();

    /** @brief Default reset handler. */
    virtual void func_00272220();

    /** @brief Clear the controller's state bit. */
    virtual void func_00272290();

    /** @brief Default handler that performs no work. */
    virtual void func_00272130();

    /** @brief Default handler that performs no work. */
    virtual void func_002721A0();

    /** @brief Release storage through the Lib heap. @param object Storage to release. */
    static void operator delete(void* object);

    u8 unk14[4];

    s32 unk18;

    u8 unk1C_0 : 1;

    u8 unk1C_1_7 : 7;
};
#endif

#endif
