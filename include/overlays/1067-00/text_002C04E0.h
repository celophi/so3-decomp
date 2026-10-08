#ifndef SO3_OVERLAYS_1067_00_TEXT_002C04E0_H
#define SO3_OVERLAYS_1067_00_TEXT_002C04E0_H

#include "types.h"
#include "overlays/1067-00/text_002BEA90.h"
#include "overlays/1067-00/text_001DD3C0.h"

typedef struct FieldFloat48 FieldFloat48;

#ifdef __cplusplus
#include "overlays/1067-00/field_class_154D40.h"

/** Partial FieldClass154E70 with vtable D_15A220 in main data; its only virtual is the destructor. */
class FieldClass15A220 : public FieldClass154E70
{
public:
    /** @brief Construct the object. */
    FieldClass15A220();

    /** @brief Destroy the object. */
    virtual ~FieldClass15A220();

    u8 unk04[0x4C];
};

/** Partial grid of FieldClass15A220 cells with vtable D_15A230 in main data. */
class FieldClass15A230 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass15A230();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass15A230();

    u8* unk14;
    FieldClass15A220* unk18;
    FieldBitset154E80* unk1C;
    u8* unk20;
    FieldClass154E60* unk24;
};

/** Partial FieldClass154E70 with vtable D_15A5B0 in main data; its only virtual is the destructor. */
class FieldClass15A5B0 : public FieldClass154E70
{
public:
    /** @brief Construct the object. */
    FieldClass15A5B0();

    /** @brief Destroy the object. */
    virtual ~FieldClass15A5B0();

    u8 unk04[0x9C];
};

/** Partial grid of FieldClass15A5B0 cells with vtable D_15A5C0 in main data. */
class FieldClass15A5C0 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass15A5C0();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass15A5C0();

    u8* unk14;
    FieldClass15A5B0* unk18;
    FieldBitset154E80* unk1C;
    u8* unk20;
    FieldClass154E60* unk24;
};

/** Partial 0x40-byte grid element with vtable D_15AB58 in main data. */
class FieldClass15AB58 : public FieldClass154E70
{
public:
    /** @brief Start with a 60.0 extent. */
    FieldClass15AB58();

    /** @brief Destroy the object. */
    virtual ~FieldClass15AB58();

    u8 unk04[0x2C];
    float unk30;
    u8 unk34[0xC];
};

/** Partial grid of FieldClass15AB58 cells with vtable D_15AB70 in main data. */
class FieldClass15AB70 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass15AB70();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass15AB70();

    u8* unk14;
    FieldClass15AB58* unk18;
    FieldBitset154E80* unk1C;
    u8* unk20;
    FieldClass154E60* unk24;
};

/** Partial FieldClass15A230 with vtable D_15A110 in main data. */
class FieldClass15A110 : public FieldClass15A230
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A110()
    {
    }
};

/** Partial FieldClass15A5C0 with vtable D_15A3D0 in main data. */
class FieldClass15A3D0 : public FieldClass15A5C0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A3D0()
    {
    }
};

/** Partial FieldClass15AB70 with vtable D_15A8D0 in main data. */
class FieldClass15A8D0 : public FieldClass15AB70
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A8D0()
    {
    }
};

/** Partial FieldClass15A110 with vtable D_15A040 in main data. */
class FieldClass15A040 : public FieldClass15A110
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A040();
};

/** Partial FieldClass15A3D0 with vtable D_15A4A0 in main data. */
class FieldClass15A4A0 : public FieldClass15A3D0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A4A0()
    {
    }
};

/** Partial FieldClass15A8D0 with vtable D_15A9A0 in main data. */
class FieldClass15A9A0 : public FieldClass15A8D0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A9A0()
    {
    }
};

/** Partial FieldClass15A4A0 with vtable D_15A300 in main data. */
class FieldClass15A300 : public FieldClass15A4A0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A300();
};

/** Partial FieldClass15A9A0 with vtable D_15A800 in main data. */
class FieldClass15A800 : public FieldClass15A9A0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A800();
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Decrease a positive float by the current field time step.
 * @param object Receiver containing the float at offset 0x48.
 */
void func_002C95B0(FieldFloat48* object);


/**
 * @brief Return the fixed value 3.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C0550(void* object);

/**
 * @brief Clear the word at offset 0x28.
 * @param self Receiver to update.
 */
void func_002C0560(FieldWord28* self);

/**
 * @brief Read the float at offset 0x2C.
 * @param self Receiver.
 * @return Stored float.
 */
float func_002C0570(const FieldFloat2C* self);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C0580(void* object);

/**
 * @brief Address an indexed 0x40-byte grid cell.
 * @param self Cell grid.
 * @param row Row index.
 * @param column Column index.
 * @return Indexed cell.
 */
FieldCell40* func_002C0590(FieldGrid40* self, s32 row, s32 column);

/**
 * @brief Address an indexed 0x50-byte record.
 * @param self Record collection.
 * @param index Record index.
 * @return Indexed record.
 */
FieldEntry50* func_002C05B0(FieldCollection50* self, s32 index);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1370(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1580(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1590(void* object);

/**
 * @brief Return the fixed float value 100.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C15A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15B0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15E0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15F0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1610(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1620(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1630(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1640(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1650(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1660(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1670(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1680(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1690(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C16A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C16B0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C16C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C16D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C16E0(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C16F0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1700(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1710(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1720(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1730(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1740(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1750(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C1760(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1770(void* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002C17E0(const FieldWord1C* object);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002C17F0(const FieldWord0C* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002C1800(const FieldWord10* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1810(void* object);

/**
 * @brief Test the word at offset 0x14.
 * @param object Receiver to test.
 * @return True when the word is nonzero.
 */
bool func_002C1820(const FieldWord14* object);

/**
 * @brief Return the fixed float value 1.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C1F70(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2000(void* object);

/**
 * @brief Clear the word at offset 0x28.
 * @param object Receiver to update.
 */
void func_002C2010(FieldWord28* object);

/**
 * @brief Return the fixed float value 2500.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C2020(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2040(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2240(void* object);

/**
 * @brief Store an input pointer and word, then update the byte mode from its first byte.
 * @param state Receiver to update.
 * @param input Input byte sequence; at least one byte is required.
 * @param unk30 Word to store at offset 0x30.
 */
void func_002C29D0(FieldInputState* state, u8* input, u32 unk30);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2A10(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A20(void* object);

/**
 * @brief Return the fixed float value 100.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C2A30(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A40(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A50(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A60(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A70(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A80(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2AA0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2AB0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2AC0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2AD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2AE0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2AF0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B00(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B10(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B20(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2B40(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2B60(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B70(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C2B80(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B90(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2BA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2BB0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2BC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2BD0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2BE0(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C2BF0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2C00(void* object);

/**
 * @brief Find a 160-byte indexed entry.
 * @param object Collection owner.
 * @param index Entry index.
 * @return The entry address.
 */
char* func_002C2C70(FieldCollection* object, s32 index);

/**
 * @brief Find a 64-byte grid cell.
 * @param object Collection owner.
 * @param row Row index.
 * @param column Column index.
 * @return The cell address.
 */
char* func_002C2C90(FieldCollection* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Collection owner.
 * @return The stored word.
 */
s32 func_002C2CB0(FieldCollection* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Collection owner.
 * @return The stored word.
 */
s32 func_002C2CC0(FieldCollection* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Collection owner.
 * @return The stored word.
 */
s32 func_002C2CD0(FieldCollection* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver of the call.
 * @return 32.
 */
int func_002C2CE0(void* object);

/**
 * @brief Test whether the pointer at offset 0x14 is present.
 * @param object Collection owner.
 * @return True when the pointer is nonnull.
 */
bool func_002C2CF0(FieldCollection* object);

/**
 * @brief Return the fixed float value 1.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C3AC0(void* object);

/**
 * @brief Select the pair and update its comparison flag.
 * @param object Pair to update.
 * @param first First compared object.
 * @param second Second compared object.
 */
void func_002C4FC0(FieldPair* object, FieldThing* first, FieldThing* second);

/**
 * @brief Set the motion selector, rate and flag.
 * @param object Motion state to update.
 * @param value Byte value to store.
 * @param index Selector, or -1 to reuse the current selector.
 * @param rate New rate.
 */
void func_002C5640(FieldMotion* object, u8 value, s16 index, float rate);

/**
 * @brief Start a motion when its flags permit it.
 * @param object Motion state to update.
 * @param value New word value.
 * @param mode New mode bit.
 * @param rate New rate.
 */
void func_002C5A10(FieldMotion* object, s32 value, s32 mode, float rate);

/**
 * @brief Mark matching linked-list nodes and clear the owner state.
 * @param object List owner to update.
 */
void func_002C7780(FieldList* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C9660(void* object);

/**
 * @brief Clear the word at offset 0x28.
 * @param object State to update.
 */
void func_002C9670(FieldState28* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C9680(void* object);

/**
 * @brief Return the fixed float value 2500.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C9690(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C96B0(void* object);

/**
 * @brief Return the fixed value four.
 * @param object Receiver of the call.
 * @return Four.
 */
int func_002C9A20(void* object);

/**
 * @brief Store selection pointers and update the mode byte.
 * @param object Selector to update.
 * @param value Byte stream to select.
 * @param context Associated context.
 */
void func_002CA150(FieldSelector* object, const u8* value, void* context);

/**
 * @brief Return a null pointer.
 * @param object Receiver of the call.
 * @return Null.
 */
void* func_002CA190(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1A0(void* object);

/**
 * @brief Return the fixed float value 100.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002CA1B0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1E0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1F0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA200(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA210(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA220(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA230(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA240(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA250(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA260(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA270(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA280(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA290(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA2A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA2B0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA2C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA2D0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA2E0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA2F0(void* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver of the call.
 * @return Zero.
 */
float func_002CA300(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA310(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA320(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA330(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA340(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA350(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA360(void* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver of the call.
 * @return Zero.
 */
float func_002CA370(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA380(void* object);

/**
 * @brief Find the indexed 64-byte entry.
 * @param object Table owner.
 * @param index Entry index.
 * @return The entry address.
 */
void* func_002CA3F0(FieldTable14* object, u32 index);

/**
 * @brief Find a 64-byte grid entry.
 * @param object Grid owner.
 * @param column Column index.
 * @param row Row index.
 * @return The entry address.
 */
void* func_002CA400(FieldGrid20* object, u32 column, u32 row);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002CA420(const FieldWord1C* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002CA430(const FieldWord0C* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002CA440(const FieldWord10* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
int func_002CA450(void* object);

/**
 * @brief Test the word at offset 0x14.
 * @param object Receiver to test.
 * @return True when the word is nonzero.
 */
bool func_002CA460(const FieldWord14* object);

/**
 * @brief Return the float value one.
 * @param object Receiver of the call.
 * @return One as a float.
 */
float func_002CABA0(void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/** Partial FieldClass150070 object with vtable D_15A760 in main data. */
class FieldClass15A760 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A760()
    {
    }

    /**
     * @brief Release the object's storage through the Lib heap.
     * @param object Storage to release.
     */
    static void operator delete(void* object);
};

/** Partial FieldClass15A760 object with vtable D_15A690 in main data. */
class FieldClass15A690 : public FieldClass15A760
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A690();
};

/** Partial FieldClass15A760 object with vtable D_15A7E0 in main data. */
class FieldClass15A7E0 : public FieldClass15A760
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A7E0()
    {
    }
};

/** Partial FieldClass15A7E0 object with vtable D_15A780 in main data. */
class FieldClass15A780 : public FieldClass15A7E0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A780();
};

/** Partial FieldClass15A7E0 object with vtable D_15A7A0 in main data. */
class FieldClass15A7A0 : public FieldClass15A7E0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A7A0();
};

/** Partial FieldClass15A7E0 object with vtable D_15A7C0 in main data. */
class FieldClass15A7C0 : public FieldClass15A7E0
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15A7C0();
};

/** Partial FieldClass15A760 object with vtable D_15AAD0 in main data. */
class FieldClass15AAD0 : public FieldClass15A760
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15AAD0();
};

/** Partial Field object with vtable D_15AAB0 in main data and an owned child at offset 0x2C. */
class FieldClass15AAB0 : public FieldClass15A760
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass15AAB0();
    /** @brief Delete the child, then detach this object and queue it for release. */
    virtual void func_001DD7B0();
    u8 unk14[0x18];
    FieldClass150070* unk2C;
};
#endif

#endif
