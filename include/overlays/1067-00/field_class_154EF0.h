#ifndef SO3_OVERLAYS_1067_00_FIELD_CLASS_154EF0_H
#define SO3_OVERLAYS_1067_00_FIELD_CLASS_154EF0_H

#include "types.h"
#include "overlays/1067-00/text_001DD3C0.h"

#ifdef __cplusplus
/**
 * Partial view of the Lib object with vtable D_1751A0 in main data; only the
 * fields used by Field code are listed.
 */
struct LibObject1751A0
{
    u8 unk00[0xA50];
    FieldVec4B unkA50;
};

/**
 * Partial Field object with vtable D_154EF0 in main data. Its destructor calls
 * slot 0x28 before the FieldClass150070 chain; it adds the slots from 0x1C.
 */
class FieldClass154EF0 : public FieldClass150070
{
public:
    /** @brief Call slot 0x28, then destroy the object. */
    virtual ~FieldClass154EF0();
    /** @brief Update the object for the current frame. */
    virtual void func_001DF360();
    // Placeholder virtuals in their vtable order (byte offset in the name); only
    // their positions are known.
    virtual void func_slot1c(LibObject1751A0* target);
    virtual void func_slot20();
    virtual void func_slot24();
    virtual void func_slot28();
    virtual void func_slot2c();
    u8 unk14[4];
    LibObject1751A0* unk18;
    u8 unk1c[4];
    u8 unk20_0_1 : 2;
    u8 unk20_2 : 1;
    u8 unk20_3_7 : 5;
    u8 unk21[0xF];
    FieldVec4A unk30;
};

/** Partial FieldClass154EF0 with vtable D_154E20 in main data, allocated from the Lib heap. */
class FieldClass154E20 : public FieldClass154EF0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass154E20()
    {
    }

    /**
     * @brief Release the object's storage through the Lib heap.
     * @param object Storage to release.
     */
    static void operator delete(void* object);
};
#endif

#endif
