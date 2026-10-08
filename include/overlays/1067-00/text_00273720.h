#ifndef SO3_OVERLAYS_1067_00_TEXT_00273720_H
#define SO3_OVERLAYS_1067_00_TEXT_00273720_H

#include "types.h"
#include "overlays/1067-00/text_001ED7E0.h"
#ifdef __cplusplus
#include "overlays/1067-00/field_class_154D40.h"
#endif

/** Partial source for the receiver's copied float state. */
typedef struct FieldFloatSourceAF0
{
    u8 unk00[0xAF0];
    float unkAF0;
} FieldFloatSourceAF0;

/** Partial linked object containing halfword flags. */
typedef struct FieldFlagTarget273720
{
    u8 unk00[0x6A];
    u16 unk6A;
} FieldFlagTarget273720;

/** Partial owner of three linked flag objects. */
typedef struct FieldFlagOwner273720
{
    u8 unk00[0x18];
    FieldFlagTarget273720* unk18;
    u8 unk1C[0x44];
    FieldFlagTarget273720* unk60[2];
} FieldFlagOwner273720;

/** Partial resource descriptor with its leading mode byte. */
typedef struct FieldResourceHeader273720
{
    u8 unk00;
} FieldResourceHeader273720;

typedef struct FieldResourceRecord273720 FieldResourceRecord273720;

/** Partial receiver storing a resource descriptor and records. */
typedef struct FieldResourceOwner273720
{
    u8 unk00[0x2C];
    FieldResourceHeader273720* unk2C;
    FieldResourceRecord273720* unk30;
    u8 unk34;
} FieldResourceOwner273720;

/** Complete 64-byte polymorphic secondary-array element. */
typedef struct FieldObject154E60
{
    void* vtable;
    u8 unk04[0x3C];
} FieldObject154E60;
typedef struct FieldBitset154E80 FieldBitset154E80;

#ifdef __cplusplus
/** Complete 128-byte grid element with vtable D_1550E8 in main data. */
class FieldClass1550E8 : public FieldClass154E70
{
public:
    /** @brief Start with a zero vector and a zero scalar. */
    FieldClass1550E8();

    /** @brief Destroy the object. */
    virtual ~FieldClass1550E8();

    u8 unk04[0x5C];
    FieldVec4A unk60;
    float unk70;
    u8 unk74[0xC];
};

/** Partial grid of FieldClass1550E8 cells with vtable D_1552E0 in main data. */
class FieldClass1552E0 : public FieldClass154D50
{
public:
    /** @brief Start with no storage. */
    FieldClass1552E0();

    /** @brief Release the cells, the bit set and the secondary elements. */
    virtual ~FieldClass1552E0();

    FieldClass1550E8* unk14;
    FieldClass1550E8* unk18;
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
    FieldClass154E60* unk24;
};
/** Partial FieldClass1552E0 with vtable D_155100 in main data. */
class FieldClass155100 : public FieldClass1552E0
{
public:
    /** @brief Clear the count. */
    FieldClass155100()
    {
        unk28 = 0;
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass155100()
    {
    }

    s32 unk28;
};

/** Partial FieldClass155100 with vtable D_1551D0 in main data. */
class FieldClass1551D0 : public FieldClass155100
{
public:
    /** @brief Clear the state words. */
    FieldClass1551D0()
    {
        unk2C = 0;
        unk30 = 0;
        unk34 = 0;
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass1551D0()
    {
    }

    s32 unk2C;
    s32 unk30;
    u8 unk34;
};

/** Complete 0xF0-byte FieldClass1551D0 with vtable D_154F30 in main data. */
class FieldClass154F30 : public FieldClass1551D0
{
public:
    /** @brief Start enabled with a 128.0 extent. */
    FieldClass154F30()
    {
        unk04 = 1;
        unk38 = 0.0f;
        unkE0 = 0;
        unkE4 = 128.0f;
    }

    /** @brief Destroy the object. */
    virtual ~FieldClass154F30();

    float unk38;
    u8 unk3C[4];
    FieldVec4A unk40[8];
    u8 unkC0[0x20];
    u8 unkE0;
    float unkE4;
};
#else
typedef struct FieldClass154F30 FieldClass154F30;
typedef struct FieldClass1550E8 FieldClass1550E8;
typedef struct FieldClass1552E0 FieldClass1552E0;
#endif

/** Partial receiver with an embedded buffer after the word at offset 0x618. */
typedef struct FieldEmbeddedBuffer75210
{
    u8 unk00[0x618];
    u32 unk618;
    u8 unk61C[4];
    u8 unk620;
} FieldEmbeddedBuffer75210;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Report the receiver's fixed classification mask.
 * @param object Receiver to inspect.
 * @return The mask 0x3.
 */
u32 func_002737A0(void* object);

/**
 * @brief Clear the receiver's count and copy its float state from the source.
 * @param object Receiver to update.
 * @param source Source containing the float state.
 */
void func_002737B0(FieldClass154F30* object, const FieldFloatSourceAF0* source);

/**
 * @brief Report the fixed float value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 2500.0f.
 */
float func_002737C0(void* object);

/**
 * @brief Report that this receiver supports the callback condition.
 * @param object Receiver to inspect.
 * @return Always true.
 */
bool func_002737E0(void* object);

/**
 * @brief Leave the callback's buffer unchanged.
 * @param object Callback receiver.
 * @param count Number of entries supplied by the caller.
 * @param buffer Scratch buffer supplied by the caller.
 * @param flag Callback option flag.
 */
void func_00273F20(void* object, s32 count, void* buffer, bool flag);

/**
 * @brief Report the receiver's fixed iteration count.
 * @param object Receiver to inspect.
 * @return Always 240.
 */
s32 func_00274BD0(void* object);

/**
 * @brief Set or clear bit zero in each present linked object's halfword flags.
 * @param object Owner of the primary link and two additional links.
 * @param enable Nonzero to set the bit; zero to clear it.
 * @return No value.
 */
void func_00275400(FieldFlagOwner273720* object, s32 enable);

/**
 * @brief Bind a resource header and records and update the mode byte.
 * @param object Receiver storing the resource pointers.
 * @param header Resource header whose first byte selects the mode.
 * @param records Resource records stored for later indexed access.
 * @return No value.
 */
void func_00275AD0(FieldResourceOwner273720* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Leave the receiver unchanged after processing.
 * @param object Callback receiver.
 */
void func_00275B20(FieldClass1552E0* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00275B30(FieldClass1552E0* object);

/**
 * @brief Leave resource binding unchanged for the default callback.
 * @param object Callback receiver.
 * @param header Resource header supplied by the caller.
 * @param records Resource records supplied by the caller.
 */
void func_00275B50(void* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records);

/**
 * @brief Report the default count for callback slot 0x80.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00275BA0(FieldClass1552E0* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00275BE0(FieldClass1552E0* object);

/**
 * @brief Leave the receiver unchanged for the scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C70(void* object, float value);

/**
 * @brief Report the default mode value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00275CB0(FieldClass1552E0* object);

/**
 * @brief Get an indexed element from the primary array.
 * @param object Object owning the array.
 * @param index Index of the element.
 * @return Address of the indexed element.
 */
FieldClass1550E8* func_00275D70(FieldClass1552E0* object, s32 index);

/**
 * @brief Get an indexed element from the secondary array.
 * @param object Object owning the secondary array.
 * @param row Signed row index.
 * @param column Signed column index.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_00275D80(FieldClass1552E0* object, s32 row, s32 column);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00275DA0(FieldClass1552E0* object);

/**
 * @brief Get the first configured dimension.
 * @param object Object to query.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00275DB0(FieldClass1552E0* object);

/**
 * @brief Get the second configured dimension.
 * @param object Object to query.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00275DC0(FieldClass1552E0* object);

/**
 * @brief Report the supported operation flags for this object kind.
 * @param object Object to query.
 * @return Always 0x20.
 */
u32 func_00275DD0(FieldClass1552E0* object);

/**
 * @brief Test whether the primary element array is present.
 * @param object Object to query.
 * @return True when the array exists, otherwise false.
 */
bool func_00275DE0(FieldClass1552E0* object);

/**
 * @brief Report the default floating-point value for this object kind.
 * @param object Object to query.
 * @return Always 1.0.
 */
float func_00276460(FieldClass1552E0* object);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B40(FieldClass1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B60(FieldClass1552E0* object, u8 value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B70(FieldClass1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B80(FieldClass1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BB0(FieldClass1552E0* object, u8 value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BC0(FieldClass1552E0* object, u8 value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BF0(FieldClass1552E0* object, u8 value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C00(FieldClass1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C10(FieldClass1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C20(FieldClass1552E0* object, u8 value);

/**
 * @brief Report the default floating-point value.
 * @param object Callback receiver.
 * @return Always zero.
 */
float func_00275C80(FieldClass1552E0* object);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275CC0(FieldClass1552E0* object, u8 value);

/**
 * @brief Report the default byte value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00275CD0(FieldClass1552E0* object);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275CE0(FieldClass1552E0* object, float value);

/**
 * @brief Report the default floating-point value.
 * @param object Callback receiver.
 * @return Always zero.
 */
float func_00275CF0(FieldClass1552E0* object);

/**
 * @brief Return the fixed value 7.
 * @param object Receiver or first argument; unused.
 * @return Always 7.
 */
s32 func_002751E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002751F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00275200(void* object);

/**
 * @brief Return the embedded buffer when the receiver's state word is nonzero.
 * @param object Receiver containing the state word and buffer.
 * @return Address of the buffer at offset 0x620, or zero.
 */
u8* func_00275210(FieldEmbeddedBuffer75210* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00275B10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275B90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275BD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275C30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00275C40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275C50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00275C60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275C90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275CA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00275D00(void* object);

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_00275E30(FieldClass1552E0* object, s32 rows, s32 columns);

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00275DF0(FieldClass1552E0* object, const FieldClass1552E0* other);

#ifdef __cplusplus
}
#endif

#endif
