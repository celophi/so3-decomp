#ifndef SO3_OVERLAYS_1067_00_TEXT_00273720_H
#define SO3_OVERLAYS_1067_00_TEXT_00273720_H

#include "types.h"
#include "overlays/1067-00/text_001ED7E0.h"

/** Partial receiver containing an integer count and copied float state. */
typedef struct FieldObject154F30
{
    u8 unk00[0x28];
    s32 unk28;
    u8 unk2C[0xB8];
    float unkE4;
} FieldObject154F30;

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

/** Complete extent of an aligned 128-byte array element with table D_1550E8. */
typedef struct FieldObject1550E8
{
    u8 unk00[0x60];
    FieldVector4 unk60;
    float unk70;
    u8 unk74[0xC];
} FieldObject1550E8;
/** Complete 64-byte polymorphic secondary-array element. */
typedef struct FieldObject154E60
{
    void* vtable;
    u8 unk04[0x3C];
} FieldObject154E60;
typedef struct FieldBitset154E80 FieldBitset154E80;

/** Partial array owner initialized by func_00275D10 with table D_1552E0. */
typedef struct FieldObject1552E0
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    FieldObject1550E8* unk14;
    FieldObject1550E8* unk18;
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
    FieldObject154E60* unk24;
} FieldObject1552E0;

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
void func_002737B0(FieldObject154F30* object, const FieldFloatSourceAF0* source);

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
void func_00275B20(FieldObject1552E0* object);

/**
 * @brief Return the default floating-point limit.
 * @param object Callback receiver.
 * @return Always 100.0f.
 */
float func_00275B30(FieldObject1552E0* object);

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
s32 func_00275BA0(FieldObject1552E0* object);

/**
 * @brief Report the default count for callback slot 0x90.
 * @param object Callback receiver.
 * @return Zero entries.
 */
s32 func_00275BE0(FieldObject1552E0* object);

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
u8 func_00275CB0(FieldObject1552E0* object);

/**
 * @brief Get an indexed element from the primary array.
 * @param object Object owning the array.
 * @param index Index of the element.
 * @return Address of the indexed element.
 */
FieldObject1550E8* func_00275D70(FieldObject1552E0* object, s32 index);

/**
 * @brief Get an indexed element from the secondary array.
 * @param object Object owning the secondary array.
 * @param row Signed row index.
 * @param column Signed column index.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_00275D80(FieldObject1552E0* object, s32 row, s32 column);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_00275DA0(FieldObject1552E0* object);

/**
 * @brief Get the first configured dimension.
 * @param object Object to query.
 * @return Signed dimension stored at offset 0xC.
 */
s32 func_00275DB0(FieldObject1552E0* object);

/**
 * @brief Get the second configured dimension.
 * @param object Object to query.
 * @return Signed dimension stored at offset 0x10.
 */
s32 func_00275DC0(FieldObject1552E0* object);

/**
 * @brief Report the supported operation flags for this object kind.
 * @param object Object to query.
 * @return Always 0x20.
 */
u32 func_00275DD0(FieldObject1552E0* object);

/**
 * @brief Test whether the primary element array is present.
 * @param object Object to query.
 * @return True when the array exists, otherwise false.
 */
bool func_00275DE0(FieldObject1552E0* object);

/**
 * @brief Report the default floating-point value for this object kind.
 * @param object Object to query.
 * @return Always 1.0.
 */
float func_00276460(FieldObject1552E0* object);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B40(FieldObject1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B60(FieldObject1552E0* object, u8 value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B70(FieldObject1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B80(FieldObject1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BB0(FieldObject1552E0* object, u8 value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BC0(FieldObject1552E0* object, u8 value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BF0(FieldObject1552E0* object, u8 value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C00(FieldObject1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C10(FieldObject1552E0* object, float value);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C20(FieldObject1552E0* object, u8 value);

/**
 * @brief Report the default floating-point value.
 * @param object Callback receiver.
 * @return Always zero.
 */
float func_00275C80(FieldObject1552E0* object);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275CC0(FieldObject1552E0* object, u8 value);

/**
 * @brief Report the default byte value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00275CD0(FieldObject1552E0* object);

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275CE0(FieldObject1552E0* object, float value);

/**
 * @brief Report the default floating-point value.
 * @param object Callback receiver.
 * @return Always zero.
 */
float func_00275CF0(FieldObject1552E0* object);

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

#ifdef __cplusplus
}
#endif

#endif
