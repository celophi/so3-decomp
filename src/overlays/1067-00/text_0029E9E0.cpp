#include "include_asm.h"
#include "overlays/1067-00/text_0029E9E0.h"

bool func_0029E9E0(FieldObject157BC0* object)
{
    return true;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_0029E9F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_0029EA20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_0029EE30);

void func_0029EF30(FieldObject157BC0* object, float value)
{
    object->unk28 = value;
}

void func_0029EF40(FieldObject157BC0* object, float value)
{
    object->unk30 = value;
}

float func_0029EF50(FieldObject157BC0* object)
{
    return object->unk30;
}

void func_0029EF60(FieldObject157BC0* object, u8 value)
{
    object->unk4D = value;
}

u8 func_0029EF70(FieldObject157BC0* object)
{
    return object->unk4D;
}

void func_0029EF80(FieldObject157BC0* object, float value)
{
    object->unk34 = value;
}

void func_0029EF90(FieldObject157BC0* object, u8 value)
{
    object->unk56 = value;
}

u8 func_0029EFA0(FieldObject157BC0* object)
{
    return object->unk56;
}

void func_0029EFB0(FieldObject157BC0* object, float value)
{
    object->unk44 = value;
}

float func_0029EFC0(FieldObject157BC0* object)
{
    return object->unk44;
}

float func_0029EFD0(FieldObject157BC0* object)
{
    return object->unk28;
}

void func_0029EFE0(FieldObject157BC0* object, FieldLinkedObject157BC0* value)
{
    object->unk48 = value;
}

FieldLinkedObject157BC0* func_0029EFF0(FieldObject157BC0* object)
{
    return object->unk48;
}

void func_0029F000(FieldObject157BC0* object, u8 value)
{
    object->unk4F = value;
}

void func_0029F010(FieldObject157BC0* object, u8 value)
{
    object->unk4E = value;
}

void func_0029F020(FieldObject157BC0* object, FieldLinkedObject157BC0* value)
{
    object->unk50 = value;
}

FieldLinkedObject157BC0* func_0029F030(FieldObject157BC0* object)
{
    return object->unk50;
}

void func_0029F040(FieldObject157BC0* object, u8 value)
{
    object->unk55 = value;
}

void func_0029F050(FieldObject157BC0* object, float value)
{
    object->unk3C = value;
}

void func_0029F060(FieldObject157BC0* object, u8 value)
{
    object->unk54 = value;
}

void func_0029F070(FieldObject157BC0* object, float value)
{
    object->unk40 = value;
}

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_0029F080(FieldObject157BC0* object, u8* header, FieldResourceRecord273720* records)
{
    object->unkA0 = header;
    object->unkA4 = records;
    if (*object->unkA0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_0029F0C0);

void func_0029F0F0(FieldObject157BC0* object, float value)
{
    object->unk38 = value;
}

void func_0029F100(void* object)
{
}

s32 func_0029F110(void* object)
{
    return 0;
}

void func_0029F120(void* object)
{
}

s32 func_0029F130(void* object)
{
    return 0;
}

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_0029F140(FieldObject157BC0* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

void func_0029F170(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_0029F180);

bool func_002A1C50(FieldObject157F00* object)
{
    return true;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A1C60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A1C90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A20A0);

void func_002A21A0(FieldObject157F00* object, float value)
{
    object->unk28 = value;
}

void func_002A21B0(FieldObject157F00* object, float value)
{
    object->unk30 = value;
}

float func_002A21C0(FieldObject157F00* object)
{
    return object->unk30;
}

void func_002A21D0(FieldObject157F00* object, u8 value)
{
    object->unk4D = value;
}

u8 func_002A21E0(FieldObject157F00* object)
{
    return object->unk4D;
}

void func_002A21F0(FieldObject157F00* object, float value)
{
    object->unk34 = value;
}

void func_002A2200(FieldObject157F00* object, u8 value)
{
    object->unk56 = value;
}

u8 func_002A2210(FieldObject157F00* object)
{
    return object->unk56;
}

void func_002A2220(FieldObject157F00* object, float value)
{
    object->unk44 = value;
}

float func_002A2230(FieldObject157F00* object)
{
    return object->unk44;
}

float func_002A2240(FieldObject157F00* object)
{
    return object->unk28;
}

void func_002A2250(FieldObject157F00* object, FieldLinkedObject157F00* value)
{
    object->unk48 = value;
}

FieldLinkedObject157F00* func_002A2260(FieldObject157F00* object)
{
    return object->unk48;
}

void func_002A2270(FieldObject157F00* object, u8 value)
{
    object->unk4F = value;
}

void func_002A2280(FieldObject157F00* object, u8 value)
{
    object->unk4E = value;
}

void func_002A2290(FieldObject157F00* object, FieldLinkedObject157F00* value)
{
    object->unk50 = value;
}

FieldLinkedObject157F00* func_002A22A0(FieldObject157F00* object)
{
    return object->unk50;
}

void func_002A22B0(FieldObject157F00* object, u8 value)
{
    object->unk55 = value;
}

void func_002A22C0(FieldObject157F00* object, float value)
{
    object->unk3C = value;
}

void func_002A22D0(FieldObject157F00* object, u8 value)
{
    object->unk54 = value;
}

void func_002A22E0(FieldObject157F00* object, float value)
{
    object->unk40 = value;
}

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_002A22F0(FieldObject157F00* object, u8* header, FieldResourceRecord273720* records)
{
    object->unkA0 = header;
    object->unkA4 = records;
    if (*object->unkA0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A2330);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A2360(FieldObject157F00* object, float value)
{
    object->unk38 = value;
}

void func_002A2370(void* object)
{
}

s32 func_002A2380(void* object)
{
    return 0;
}

void func_002A2390(void* object)
{
}

s32 func_002A23A0(void* object)
{
    return 0;
}

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_002A23B0(FieldObject157F00* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

void func_002A23E0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A23F0);

/**
 * @brief Report the default enabled callback state.
 * @param object Object being queried.
 * @return Always true.
 */
bool func_002A4EC0(FieldObject158240* object)
{
    return true;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A4ED0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A4F00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A5310);

/**
 * @brief Store the floating-point value at offset 0x28.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5410(FieldObject158240* object, float value)
{
    object->unk28 = value;
}

/**
 * @brief Store the floating-point value at offset 0x30.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5420(FieldObject158240* object, float value)
{
    object->unk30 = value;
}

/**
 * @brief Read the floating-point value at offset 0x30.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A5430(FieldObject158240* object)
{
    return object->unk30;
}

/**
 * @brief Store the byte state at offset 0x4D.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5440(FieldObject158240* object, u8 value)
{
    object->unk4D = value;
}

/**
 * @brief Read the byte state at offset 0x4D.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A5450(FieldObject158240* object)
{
    return object->unk4D;
}

/**
 * @brief Store the floating-point value at offset 0x34.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5460(FieldObject158240* object, float value)
{
    object->unk34 = value;
}

/**
 * @brief Store the byte state at offset 0x56.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5470(FieldObject158240* object, u8 value)
{
    object->unk56 = value;
}

/**
 * @brief Read the byte state at offset 0x56.
 * @param object Object to inspect.
 * @return Stored value.
 */
u8 func_002A5480(FieldObject158240* object)
{
    return object->unk56;
}

/**
 * @brief Store the floating-point value at offset 0x44.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5490(FieldObject158240* object, float value)
{
    object->unk44 = value;
}

/**
 * @brief Read the floating-point value at offset 0x44.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A54A0(FieldObject158240* object)
{
    return object->unk44;
}

/**
 * @brief Read the floating-point value at offset 0x28.
 * @param object Object to inspect.
 * @return Stored value.
 */
float func_002A54B0(FieldObject158240* object)
{
    return object->unk28;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A54C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A54D0);

/**
 * @brief Store the byte state at offset 0x4F.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A54E0(FieldObject158240* object, u8 value)
{
    object->unk4F = value;
}

/**
 * @brief Store the byte state at offset 0x4E.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A54F0(FieldObject158240* object, u8 value)
{
    object->unk4E = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A5500);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A5510);

/**
 * @brief Store the byte state at offset 0x55.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5520(FieldObject158240* object, u8 value)
{
    object->unk55 = value;
}

/**
 * @brief Store the floating-point value at offset 0x3C.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5530(FieldObject158240* object, float value)
{
    object->unk3C = value;
}

/**
 * @brief Store the byte state at offset 0x54.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5540(FieldObject158240* object, u8 value)
{
    object->unk54 = value;
}

/**
 * @brief Store the floating-point value at offset 0x40.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A5550(FieldObject158240* object, float value)
{
    object->unk40 = value;
}

/**
 * @brief Bind the resource bytes and records and set the mode from byte zero.
 * @param object Receiver to update.
 * @param header Resource header bytes.
 * @param records Resource records to bind.
 */
void func_002A5560(FieldObject158240* object, u8* header, FieldResourceRecord273720* records)
{
    object->unkA0 = header;
    object->unkA4 = records;
    if (*object->unkA0 == 1)
    {
        object->unk57 = 1;
    }
    else
    {
        object->unk57 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A55A0);

/**
 * @brief Store the floating-point value at offset 0x38.
 * @param object Object to update.
 * @param value Value to store.
 */
void func_002A55D0(FieldObject158240* object, float value)
{
    object->unk38 = value;
}

void func_002A55E0(void* object)
{
}

s32 func_002A55F0(void* object)
{
    return 0;
}

void func_002A5600(void* object)
{
}

s32 func_002A5610(void* object)
{
    return 0;
}

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldArrayEntry158DD0* func_002A5620(FieldObject158DD0* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5640(FieldObject158DD0* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset158DD0* func_002A5660(FieldObject158DD0* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5670(FieldObject158DD0* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5680(FieldObject158DD0* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5690(FieldObject158DD0* object)
{
    return 0x3F;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A56A0(FieldObject158DD0* object)
{
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A56B0);

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldArrayEntry158D00* func_002A5710(FieldObject158D00* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5730(FieldObject158D00* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5750(FieldObject158D00* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5760(FieldObject158D00* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5770(FieldObject158D00* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5780(FieldObject158D00* object)
{
    return 0x2F;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5790(FieldObject158D00* object)
{
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A57A0);

/**
 * @brief Get an indexed primary array element.
 * @param object Object owning the array.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldArrayEntry158C30* func_002A5800(FieldObject158C30* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5820(FieldObject158C30* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored value.
 */
FieldBitset154E80* func_002A5840(FieldObject158C30* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5850(FieldObject158C30* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5860(FieldObject158C30* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5870(FieldObject158C30* object)
{
    return 0x27;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5880(FieldObject158C30* object)
{
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A5890);

/**
 * @brief Get an indexed primary array element.
 * @param object Object to query.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldObject158A58* func_002A58F0(FieldObject158B60* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5910(FieldObject158B60* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002A5930(FieldObject158B60* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5940(FieldObject158B60* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5950(FieldObject158B60* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5960(FieldObject158B60* object)
{
    return 0x23;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5970(FieldObject158B60* object)
{
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A5980);

/**
 * @brief Get an indexed primary array element.
 * @param object Object to query.
 * @param index Signed element index.
 * @return Address of the indexed element.
 */
FieldObject158A78* func_002A59E0(FieldObject158A90* object, s32 index)
{
    return &object->unk14[index];
}

/**
 * @brief Get an element from a secondary array row.
 * @param object Object owning the array.
 * @param row Signed primary element index.
 * @param column Signed index within its secondary row.
 * @return Address of the indexed secondary element.
 */
FieldObject154E60* func_002A5A00(FieldObject158A90* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

/**
 * @brief Get the associated bitset object.
 * @param object Object to query.
 * @return Stored bitset object pointer.
 */
FieldBitset154E80* func_002A5A20(FieldObject158A90* object)
{
    return object->unk1C;
}

/**
 * @brief Get the first signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5A30(FieldObject158A90* object)
{
    return object->unk0C;
}

/**
 * @brief Get the second signed dimension.
 * @param object Object to query.
 * @return Stored value.
 */
s32 func_002A5A40(FieldObject158A90* object)
{
    return object->unk10;
}

/**
 * @brief Report supported operation flags.
 * @param object Object to query.
 * @return Supported flags.
 */
u32 func_002A5A50(FieldObject158A90* object)
{
    return 0x21;
}

/**
 * @brief Test whether the primary array is present.
 * @param object Object to query.
 * @return Whether the array is present.
 */
bool func_002A5A60(FieldObject158A90* object)
{
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A5A70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A5FD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6170);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A66D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6720);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A67A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6830);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6910);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6E70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6EC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6F50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A6FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A70D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A7630);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A7690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A7730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A77E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A78C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A7E20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A7E90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A7F40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A8000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A80D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A87F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A88C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A8FE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A90B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A9810);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002A98E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AA000);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AA0D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AA1A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AA6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AAD70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AB570);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AB650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002ABD90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002ABE80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002ABF90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD4E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD5D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD700);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD760);

/**
 * @brief Clear the index and copy four aligned values from the source.
 * @param object Receiver to update.
 * @param source Source of the four aligned values.
 */
void func_002AD830(FieldObject158860* object, const FieldVectorSource150* source)
{
    object->unk2C = 0;
    object->unk60 = source->unk150;
    object->unk70 = source->unk160;
    object->unk80 = source->unk170;
    object->unk90 = source->unk180;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD8A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD8E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD920);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD990);

void func_002AD9C0(void* object)
{
}

/**
 * @brief Report the default enabled callback state.
 * @param object Object to query.
 * @return Always true.
 */
bool func_002AD9D0(FieldObject158860* object)
{
    return true;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AD9E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002ADDF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002ADEF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AE070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0029E9E0", func_002AE240);

void func_002AE9A0(void* object)
{
}

s32 func_002AE9B0(void* object)
{
    return 0;
}

void func_002AE9C0(void* object)
{
}

s32 func_002AE9D0(void* object)
{
    return 0;
}
