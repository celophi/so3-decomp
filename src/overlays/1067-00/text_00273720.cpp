#include "overlays/1067-00/text_00273720.h"
#include "include_asm.h"

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00273720);

u32 func_002737A0(void* object)
{
    return 0x3;
}

void func_002737B0(FieldObject154F30* object, const FieldFloatSourceAF0* source)
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00273B60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00273BC0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002750F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275150);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002751E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002751F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275210);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275B10);

void func_00275B20(FieldObject1552E0* object)
{
}

float func_00275B30(FieldObject1552E0* object)
{
    return 100.0f;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B40(FieldObject1552E0* object, float value)
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
void func_00275B60(FieldObject1552E0* object, u8 value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B70(FieldObject1552E0* object, float value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275B80(FieldObject1552E0* object, float value)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275B90);

s32 func_00275BA0(FieldObject1552E0* object)
{
    return 0;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BB0(FieldObject1552E0* object, u8 value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BC0(FieldObject1552E0* object, u8 value)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275BD0);

s32 func_00275BE0(FieldObject1552E0* object)
{
    return 0;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275BF0(FieldObject1552E0* object, u8 value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C00(FieldObject1552E0* object, float value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C10(FieldObject1552E0* object, float value)
{
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275C20(FieldObject1552E0* object, u8 value)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275C30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275C40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275C50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275C60);

void func_00275C70(void* object, float value)
{
}

/**
 * @brief Report the default floating-point value.
 * @param object Callback receiver.
 * @return Always zero.
 */
float func_00275C80(FieldObject1552E0* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275C90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275CA0);

u8 func_00275CB0(FieldObject1552E0* object)
{
    return 0;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275CC0(FieldObject1552E0* object, u8 value)
{
}

/**
 * @brief Report the default byte value.
 * @param object Callback receiver.
 * @return Always zero.
 */
u8 func_00275CD0(FieldObject1552E0* object)
{
    return 0;
}

/**
 * @brief Leave the receiver unchanged for the default scalar callback.
 * @param object Callback receiver.
 * @param value Scalar value supplied by the caller.
 */
void func_00275CE0(FieldObject1552E0* object, float value)
{
}

/**
 * @brief Report the default floating-point value.
 * @param object Callback receiver.
 * @return Always zero.
 */
float func_00275CF0(FieldObject1552E0* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275D00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275D10);

FieldObject1550E8* func_00275D70(FieldObject1552E0* object, s32 index)
{
    return &object->unk14[index];
}

FieldObject154E60* func_00275D80(FieldObject1552E0* object, s32 row, s32 column)
{
    return &object->unk20[row * (object->unk10 - 1) + column];
}

FieldBitset154E80* func_00275DA0(FieldObject1552E0* object)
{
    return object->unk1C;
}

s32 func_00275DB0(FieldObject1552E0* object)
{
    return object->unk0C;
}

s32 func_00275DC0(FieldObject1552E0* object)
{
    return object->unk10;
}

u32 func_00275DD0(FieldObject1552E0* object)
{
    return 0x20;
}

bool func_00275DE0(FieldObject1552E0* object)
{
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275DF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00275E30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00276380);

float func_00276460(FieldObject1552E0* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00276470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00276480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_00276490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002764A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002764B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00273720", func_002764C0);
