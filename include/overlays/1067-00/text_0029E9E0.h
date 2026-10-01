#ifndef SO3_OVERLAYS_1067_00_TEXT_0029E9E0_H
#define SO3_OVERLAYS_1067_00_TEXT_0029E9E0_H

#include "overlays/1067-00/text_00293610.h"
#include "overlays/1067-00/text_00273720.h"

typedef struct FieldLinkedObject157F00 FieldLinkedObject157F00;

/** Partial scalar state of the distinct D_157F00 class hierarchy. */
typedef struct FieldObject157F00
{
    u8 unk00[0x28];
    float unk28;
    s32 unk2C;
    float unk30;
    float unk34;
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    FieldLinkedObject157F00* unk48;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    FieldLinkedObject157F00* unk50;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58[8];
    FieldVector4 unk60;
    FieldVector4 unk70;
    FieldVector4 unk80;
    FieldVector4 unk90;
    u8* unkA0;
    FieldResourceRecord273720* unkA4;
} FieldObject157F00;

typedef struct FieldArrayEntry158DD0 FieldArrayEntry158DD0;
typedef struct FieldArrayEntry158D00 FieldArrayEntry158D00;
typedef struct FieldBitset158DD0 FieldBitset158DD0;

/** Complete 0x170-byte array extent constructed by func_002A7E20. */
struct FieldArrayEntry158DD0
{
    u8 unk00[0x10];
    FieldVector4 unk10;
    u8 unk20[0x150];
};

/** Complete 0x120-byte array extent constructed by func_002A7630. */
struct FieldArrayEntry158D00
{
    u8 unk00[0x10];
    FieldVector4 unk10;
    u8 unk20[0x100];
};

/** Complete 0xB0-byte array extent constructed by func_002A6E70. */
struct FieldArrayEntry158C30
{
    u8 unk00[0x10];
    FieldVector4 unk10;
    u8 unk20[0x90];
};

/** Partial array owner associated with table D_158DD0. */
typedef struct FieldObject158DD0
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    FieldArrayEntry158DD0* unk14;
    u8 unk18[4];
    FieldBitset158DD0* unk1C;
    FieldObject154E60* unk20;
} FieldObject158DD0;

/** Partial array owner initialized by func_002A56B0. */
typedef struct FieldObject158D00
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    FieldArrayEntry158D00* unk14;
    u8 unk18[4];
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
} FieldObject158D00;

typedef struct FieldArrayEntry158C30 FieldArrayEntry158C30;

/** Partial base initialized by func_002A57A0. */
typedef struct FieldObject158C30
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    FieldArrayEntry158C30* unk14;
    u8 unk18[4];
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
} FieldObject158C30;

/** Aligned 0x60-byte array element constructed by func_002A5FD0. */
typedef struct FieldObject158A78
{
    u8 unk00[0x10];
    FieldVector4 unk10;
    FieldVector4 unk20;
    u8 unk30[0x30];
} FieldObject158A78;

/** Aligned 0x90-byte array element constructed by func_002A66D0. */
typedef struct FieldObject158A58
{
    u8 unk00[0x10];
    FieldVector4 unk10;
    u8 unk20[0x10];
    FieldVector4 unk30;
    FieldVector4 unk40;
    FieldVector4 unk50;
    u8 unk60[0x30];
} FieldObject158A58;

/** Partial array owner initialized by func_002A5890. */
typedef struct FieldObject158B60
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    FieldObject158A58* unk14;
    FieldObject158A58* unk18;
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
} FieldObject158B60;

/** Partial array owner initialized by func_002A5980. */
typedef struct FieldObject158A90
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    FieldObject158A78* unk14;
    FieldObject158A78* unk18;
    FieldBitset154E80* unk1C;
    FieldObject154E60* unk20;
} FieldObject158A90;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF30(FieldObject157BC0* object, float value);

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF40(FieldObject157BC0* object, float value);

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_0029EF50(FieldObject157BC0* object);

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF60(FieldObject157BC0* object, u8 value);

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_0029EF70(FieldObject157BC0* object);

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF80(FieldObject157BC0* object, float value);

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EF90(FieldObject157BC0* object, u8 value);

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_0029EFA0(FieldObject157BC0* object);

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EFB0(FieldObject157BC0* object, float value);

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_0029EFC0(FieldObject157BC0* object);

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_0029EFD0(FieldObject157BC0* object);

/**
 * @brief Store the linked object at offset 0x48.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029EFE0(FieldObject157BC0* object, FieldLinkedObject157BC0* value);

/**
 * @brief Read the linked object at offset 0x48.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157BC0* func_0029EFF0(FieldObject157BC0* object);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F000(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F010(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the linked object at offset 0x50.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F020(FieldObject157BC0* object, FieldLinkedObject157BC0* value);

/**
 * @brief Read the linked object at offset 0x50.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157BC0* func_0029F030(FieldObject157BC0* object);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F040(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F050(FieldObject157BC0* object, float value);

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F060(FieldObject157BC0* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F070(FieldObject157BC0* object, float value);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_0029F0F0(FieldObject157BC0* object, float value);

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21A0(FieldObject157F00* object, float value);

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21B0(FieldObject157F00* object, float value);

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A21C0(FieldObject157F00* object);

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21D0(FieldObject157F00* object, u8 value);

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A21E0(FieldObject157F00* object);

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A21F0(FieldObject157F00* object, float value);

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2200(FieldObject157F00* object, u8 value);

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A2210(FieldObject157F00* object);

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2220(FieldObject157F00* object, float value);

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A2230(FieldObject157F00* object);

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A2240(FieldObject157F00* object);

/**
 * @brief Store the linked object at offset 0x48.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2250(FieldObject157F00* object, FieldLinkedObject157F00* value);

/**
 * @brief Read the linked object at offset 0x48.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157F00* func_002A2260(FieldObject157F00* object);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2270(FieldObject157F00* object, u8 value);

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2280(FieldObject157F00* object, u8 value);

/**
 * @brief Store the linked object at offset 0x50.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2290(FieldObject157F00* object, FieldLinkedObject157F00* value);

/**
 * @brief Read the linked object at offset 0x50.
 * @param object Object to inspect.
 * @return Stored value.
 */
FieldLinkedObject157F00* func_002A22A0(FieldObject157F00* object);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22B0(FieldObject157F00* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22C0(FieldObject157F00* object, float value);

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22D0(FieldObject157F00* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A22E0(FieldObject157F00* object, float value);

/**
 * @brief Enable the default callback predicate for this receiver.
 * @param object Receiver to query.
 * @return Always true.
 */
bool func_0029E9E0(FieldObject157BC0* object);

/**
 * @brief Enable the default callback predicate for this receiver.
 * @param object Receiver to query.
 * @return Always true.
 */
bool func_002A1C50(FieldObject157F00* object);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2360(FieldObject157F00* object, float value);

/**
 * @brief Report the default enabled callback state.
 * @param object Object being queried.
 * @return Always true.
 */
bool func_002A4EC0(FieldObject158240* object);

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5410(FieldObject158240* object, float value);

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5420(FieldObject158240* object, float value);

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A5430(FieldObject158240* object);

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5440(FieldObject158240* object, u8 value);

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A5450(FieldObject158240* object);

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5460(FieldObject158240* object, float value);

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5470(FieldObject158240* object, u8 value);

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A5480(FieldObject158240* object);

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5490(FieldObject158240* object, float value);

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A54A0(FieldObject158240* object);

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A54B0(FieldObject158240* object);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A54E0(FieldObject158240* object, u8 value);

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A54F0(FieldObject158240* object, u8 value);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5520(FieldObject158240* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5530(FieldObject158240* object, float value);

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5540(FieldObject158240* object, u8 value);

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5550(FieldObject158240* object, float value);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A55D0(FieldObject158240* object, float value);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset158DD0* func_002A5660(FieldObject158DD0* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5670(FieldObject158DD0* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5680(FieldObject158DD0* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5690(FieldObject158DD0* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A56A0(FieldObject158DD0* object);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5750(FieldObject158D00* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5760(FieldObject158D00* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5770(FieldObject158D00* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5780(FieldObject158D00* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5790(FieldObject158D00* object);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5840(FieldObject158C30* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5850(FieldObject158C30* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5860(FieldObject158C30* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5870(FieldObject158C30* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5880(FieldObject158C30* object);

/**
 * @brief Get an indexed primary array element.
 * @param object Object to query.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldObject158A58* func_002A58F0(FieldObject158B60* object, s32 index);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002A5930(FieldObject158B60* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5940(FieldObject158B60* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5950(FieldObject158B60* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5960(FieldObject158B60* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5970(FieldObject158B60* object);

/**
 * @brief Get an indexed primary array element.
 * @param object Object to query.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldObject158A78* func_002A59E0(FieldObject158A90* object, s32 index);

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002A5A20(FieldObject158A90* object);

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5A30(FieldObject158A90* object);

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5A40(FieldObject158A90* object);

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5A50(FieldObject158A90* object);

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5A60(FieldObject158A90* object);

/**
 * @brief Report the default enabled callback state.
 * @param object Object to query.
 * @return Always true.
 */
bool func_002AD9D0(FieldObject158860* object);

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldArrayEntry158DD0* func_002A5620(FieldObject158DD0* object, s32 index);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5640(FieldObject158DD0* object, s32 row, s32 column);

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldArrayEntry158D00* func_002A5710(FieldObject158D00* object, s32 index);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5730(FieldObject158D00* object, s32 row, s32 column);

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldArrayEntry158C30* func_002A5800(FieldObject158C30* object, s32 index);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5820(FieldObject158C30* object, s32 row, s32 column);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5910(FieldObject158B60* object, s32 row, s32 column);

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5A00(FieldObject158A90* object, s32 row, s32 column);

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_0029F080(FieldObject157BC0* object, u8* header, FieldResourceRecord273720* records);

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_0029F140(FieldObject157BC0* object, const FieldVectorSource150* source);

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_002A22F0(FieldObject157F00* object, u8* header, FieldResourceRecord273720* records);

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_002A23B0(FieldObject157F00* object, const FieldVectorSource150* source);

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_002A5560(FieldObject158240* object, u8* header, FieldResourceRecord273720* records);

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_002AD830(FieldObject158860* object, const FieldVectorSource150* source);

#ifdef __cplusplus
}
#endif
#endif
