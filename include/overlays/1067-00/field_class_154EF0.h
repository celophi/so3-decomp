#ifndef SO3_OVERLAYS_1067_00_FIELD_CLASS_154EF0_H
#define SO3_OVERLAYS_1067_00_FIELD_CLASS_154EF0_H

#include "types.h"
#include "overlays/1067-00/text_001DD3C0.h"

#ifdef __cplusplus
class FieldClass154D50;

/**
 * Partial view of the Lib object with vtable D_1751A0 in main data; only the
 * fields used by Field code are listed.
 */
struct LibObject1751A0
{
    /** @brief Destroy the linked Lib object. */
    virtual ~LibObject1751A0();
    /** @brief Report the fixed object kind. @return Always 7. */
    virtual s32 func_00468360();
    /** @brief Release the linked Lib object. */
    virtual void func_00434FA0();
    u8 unk04[0x66];
    u16 unk6A;
    u8 unk6c[0x9E4];
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
    /** @brief Report the fixed object type. @return Always 4. */
    virtual s32 func_001DF3D0();
    /** @brief Detach, release owned objects and queue this object once. */
    virtual void func_001DD7B0();
    /** @brief Update the object for the current frame. */
    virtual void func_001DF360();
    // Unnamed virtual handlers retain their slot offsets in the names.
    /** @brief Do nothing with the linked object. @param target Linked object; unused. */
    virtual void func_slot1c(LibObject1751A0* target);
    /** @brief Do nothing. */
    virtual void func_slot20();
    /** @brief Report the fixed value. @return Always 300. */
    virtual s32 func_slot24();
    /** @brief Release the linked object and any unborrowed grid. */
    virtual void func_slot28();
    /** @brief Clear bit 2 and copy bit 1 to bit 0. */
    virtual void func_slot2c();
    /** @brief Create the grid for this object. */
    virtual void func_slot30() = 0;
    /** @brief Create and attach the linked Lib object. @return The linked object. */
    virtual LibObject1751A0* func_slot34();
    /** @brief Clear every word of the grid bit set. */
    virtual void func_slot38();
    /** @brief Set or clear bit 0 of the linked object flags. @param enabled Nonzero to set the flag. */
    virtual void func_slot3c(s32 enabled);
    u8 unk14[4];
    LibObject1751A0* unk18;
    FieldClass154D50* unk1c;
    u8 unk20_0 : 1;
    u8 unk20_1 : 1;
    u8 unk20_2 : 1;
    u8 unk20_3 : 1;
    u8 unk20_4_7 : 4;
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
