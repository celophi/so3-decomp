#ifndef SO3_OVERLAYS_1067_00_FIELD_CLASS_155780_H
#define SO3_OVERLAYS_1067_00_FIELD_CLASS_155780_H

#include "types.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/lib/text_004CD3A0.h"

#ifdef __cplusplus
/**
 * Partial Field object with vtable D_155780 in main data. Its destructor
 * releases the resource handle at offset 0x24. It adds the vtable slots at
 * 0x1C, 0x20 and 0x24.
 */
class FieldClass155780 : public FieldClass150070
{
public:
    /** @brief Release the handle at offset 0x24, then destroy the object. */
    virtual ~FieldClass155780();
    // Placeholder virtuals in their vtable order (byte offset in the name); only
    // their positions are known.
    virtual void func_slot1c();
    virtual void func_slot20();
    virtual void func_slot24();
    void* unk14;
    u8 unk18[0xC];
    s32 unk24;
    u8 unk28[0x24];
    u8 unk4c;
    u8 unk4d[3];
    void* unk50;
    u8 unk54[0xC];
};

/** Partial Field object with vtable D_155750 in main data. */
class FieldClass155750 : public FieldClass155780
{
public:
    /** @brief Call slot 0x20, then destroy the object. */
    virtual ~FieldClass155750();
    /** @brief Release the object at offset 0x50 and update the state bits at offset 0x4C. */
    virtual void func_slot20();
};

/** Partial Field object with vtable D_152740 in main data and an embedded Lib object. */
class FieldClass152740 : public FieldClass155750
{
public:
    /** @brief Destroy the embedded Lib object, then the object. */
    virtual ~FieldClass152740();
    /** @brief Run the base handler, then point offset 0x50 at the embedded Lib object. */
    virtual void func_slot20()
    {
        FieldClass155750::func_slot20();
        unk50 = &unk60;
    }
    LibClass178EA0 unk60;
};
#endif

#endif
