#include "overlays/1067-00/text_00273720.h"
#include "include_asm.h"
#include "main/resident_data.h"

FieldClass154F30::~FieldClass154F30()
{
}

u32 func_002737A0(void* object)
{
    return 0x3;
}

void func_002737B0(FieldClass154F30* object, const FieldFloatSourceAF0* source)
{
    object->unk28 = 0;
    object->unkE4 = source->unkAF0;
}

float func_002737C0(void* object)
{
    return 2500.0f;
}

bool func_002737E0(void* object)
{
    return true;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002737F0);

FieldClass1550E8::FieldClass1550E8()
{
    unk70 = 0.0f;
    unk60 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

FieldClass1550E8::~FieldClass1550E8()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00273C40);

void func_00273F20(void* object, s32 count, void* buffer, bool flag)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00273F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002749B0);

s32 func_00274BD0(void* object)
{
    return 240;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00274BE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00274CA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00274F60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275150);

s32 func_002751E0(void* object)
{
    return 7;
}

s32 func_002751F0(void* object)
{
    return 0;
}

s32 func_00275200(void* object)
{
    return 0;
}

extern "C" u8* func_00275210(FieldEmbeddedBuffer75210* object)
{
    if (object->unk618 != 0)
    {
        return &object->unk620;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275310);

void func_00275400(FieldFlagOwner273720* object, s32 enable)
{
    s32 i;
    if (object->unk18 != 0)
    {
        if (enable)
        {
            object->unk18->unk6A |= 1;
        }
        else
        {
            object->unk18->unk6A = object->unk18->unk6A & ~1;
        }
    }
    for (i = 0; i < 2; i++)
    {
        if (object->unk60[i] != 0)
        {
            if (enable)
            {
                object->unk60[i]->unk6A |= 1;
            }
            else
            {
                object->unk60[i]->unk6A = object->unk60[i]->unk6A & ~1;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275490);

void func_00275AD0(FieldResourceOwner273720* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records)
{
    object->unk2C = header;
    object->unk30 = records;
    if (object->unk2C->unk00 == 1)
    {
        object->unk34 = 1;
    }
    else
    {
        object->unk34 = 0;
    }
}

s32 func_00275B10(void* object)
{
    return 0;
}

void func_00275B20(FieldClass1552E0* object)
{
}

float func_00275B30(FieldClass1552E0* object)
{
    return 100.0f;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B40(FieldClass1552E0* object, float value)
{
}

void func_00275B50(void* object, FieldResourceHeader273720* header, FieldResourceRecord273720* records)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B60(FieldClass1552E0* object, u8 value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B70(FieldClass1552E0* object, float value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B80(FieldClass1552E0* object, float value)
{
}

void func_00275B90(void* object)
{
}

s32 func_00275BA0(FieldClass1552E0* object)
{
    return 0;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BB0(FieldClass1552E0* object, u8 value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BC0(FieldClass1552E0* object, u8 value)
{
}

void func_00275BD0(void* object)
{
}

s32 func_00275BE0(FieldClass1552E0* object)
{
    return 0;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BF0(FieldClass1552E0* object, u8 value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C00(FieldClass1552E0* object, float value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C10(FieldClass1552E0* object, float value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C20(FieldClass1552E0* object, u8 value)
{
}

void func_00275C30(void* object)
{
}

s32 func_00275C40(void* object)
{
    return 0;
}

void func_00275C50(void* object)
{
}

s32 func_00275C60(void* object)
{
    return 0;
}

void func_00275C70(void* object, float value)
{
}

/**
 * @brief Report the default floating-point value.
 * @param object Callback receiver.
 * @return Always zero.
 */
float func_00275C80(FieldClass1552E0* object)
{
    return 0.0f;
}

void func_00275C90(void* object)
{
}

void func_00275CA0(void* object)
{
}

u8 func_00275CB0(FieldClass1552E0* object)
{
    return 0;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275CC0(FieldClass1552E0* object, u8 value)
{
}

/**
 * @brief Report the default byte value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00275CD0(FieldClass1552E0* object)
{
    return 0;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275CE0(FieldClass1552E0* object, float value)
{
}

/**
 * @brief Report the default floating-point value.
 * @param object Callback receiver.
 * @return Always zero.
 */
float func_00275CF0(FieldClass1552E0* object)
{
    return 0.0f;
}

void func_00275D00(void* object)
{
}

FieldClass1552E0::FieldClass1552E0()
{
    unk04 = 0;
    unk14 = 0;
    unk18 = 0;
    unk1C = 0;
    unk20 = 0;
    unk24 = 0;
}

FieldClass1550E8* func_00275D70(FieldClass1552E0* object, s32 index)
{
    return &object->unk14[index];
}

FieldObject154E60* func_00275D80(FieldClass1552E0* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

FieldBitset154E80* func_00275DA0(FieldClass1552E0* object)
{
    return object->unk1C;
}

s32 func_00275DB0(FieldClass1552E0* object)
{
    return object->unk0C;
}

s32 func_00275DC0(FieldClass1552E0* object)
{
    return object->unk10;
}

u32 func_00275DD0(FieldClass1552E0* object)
{
    return 0x20;
}

bool func_00275DE0(FieldClass1552E0* object)
{
    return object->unk14 != 0;
}

/**
 * @brief Copy another grid's size and reallocate this grid to match.
 * @param object Grid to resize.
 * @param other Grid whose size is copied.
 */
void func_00275DF0(FieldClass1552E0* object, const FieldClass1552E0* other)
{
    object->unk0C = other->unk0C;
    object->unk10 = other->unk10;
    object->resize(object->unk0C, object->unk10);
}

/**
 * @brief Reallocate the cells, the bit set and the secondary elements for a new size.
 * @param object Grid to resize.
 * @param rows Cell count.
 * @param columns Secondary elements per cell plus one.
 */
void func_00275E30(FieldClass1552E0* object, s32 rows, s32 columns)
{
    object->unk14 = 0;
    object->unk20 = 0;
    delete[] object->unk18;
    object->unk18 = new (0) FieldClass1550E8[rows + 2];
    if (object->unk18 == 0)
    {
        return;
    }
    delete object->unk1C;
    if (D_001B6684 != 0)
    {
        void* heap = func_00100C80(D_001B6684);
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            func_00100C80(heap);
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
    }
    else
    {
        object->unk1C = new (0) FieldBitset154E80(rows);
        if (object->unk1C == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            return;
        }
        if (object->unk1C->unk08 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    if (columns > 1)
    {
        delete[] object->unk24;
        object->unk24 = new (0) FieldClass154E60[rows * (columns - 1) + 2];
        if (object->unk24 == 0)
        {
            delete[] object->unk18;
            object->unk18 = 0;
            delete object->unk1C;
            object->unk1C = 0;
            return;
        }
    }
    else
    {
        delete[] object->unk24;
        object->unk24 = 0;
    }
    if (object->unk18 != 0)
    {
        object->unk14 = object->unk18 + 1;
    }
    if (object->unk24 != 0)
    {
        object->unk20 = (FieldObject154E60*)(object->unk24 + 1);
    }
    object->unk0C = rows;
    object->unk10 = columns;
    object->unk1C->clear();
}

FieldClass1552E0::~FieldClass1552E0()
{
    delete[] unk18;
    delete unk1C;
    delete[] unk24;
}

float func_00276460(FieldClass1552E0* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00276470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00276480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00276490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002764A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002764B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002764C0);
