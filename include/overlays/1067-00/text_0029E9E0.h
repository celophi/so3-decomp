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
} FieldObject157F00;

/** Partial scalar state of the distinct D_158240 hierarchy. */
typedef struct FieldObject158240
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
    u8 unk48[4];
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    u8 unk50[4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} FieldObject158240;

typedef struct FieldArrayEntry158DD0 FieldArrayEntry158DD0;
typedef struct FieldArrayEntry158D00 FieldArrayEntry158D00;
typedef struct FieldBitset158DD0 FieldBitset158DD0;

/** Partial array owner associated with table D_158DD0. */
typedef struct FieldObject158DD0
{
    u8 unk00[0xC];
    s32 unk0C;
    s32 unk10;
    FieldArrayEntry158DD0* unk14;
    u8 unk18[4];
    FieldBitset158DD0* unk1C;
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
} FieldObject158D00;

/** Partial base initialized by func_002A57A0. */
typedef struct FieldObject158C30
{
    u8 unk00[0x1C];
    FieldBitset154E80* unk1C;
} FieldObject158C30;

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

#ifdef __cplusplus
}
#endif
#endif
