#include "include_asm.h"
#include "overlays/1067-00/text_002934A0.h"
#include "overlays/1067-00/text_00272360.h"

struct FieldCurve
{
    s32 count;
    void* points;
};

struct FieldObject1573D0
{
    u8 pad[0x14];
    FieldCurve unk14;
    u8 pad1[4];
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    float unk30;
    float unk34;
    u8 unk38_0 : 1;
    u8 unk38_1 : 1;
    u8 unk38_2_7 : 6;
};

extern float D_001B6688;

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002934A0", func_002934A0);

s32 func_002934D0(FieldObject1573D0* object)
{
    return 4;
}

void func_002934E0(FieldObject1573D0* object, float first_value, float second_value, float third_value)
{
    object->unk20 = second_value;
    object->unk24 = first_value;
    object->unk28 = object->unk20 - object->unk24;
    object->unk2c = third_value;
    object->unk30 = 0.0f;
    object->unk34 = 1.0f;
    object->unk38_0 = 1;
    object->unk38_1 = 0;
}

void func_00293540(FieldObject1573D0* object)
{
    if (object->unk38_0 && !object->unk38_1)
    {
        object->unk30 += D_001B6688;
        if (object->unk30 >= object->unk2c)
        {
            object->unk34 = object->unk20;
            object->unk38_1 = 1;
        }
        else
        {
            object->unk34 = object->unk24 + object->unk28 * func_00272820(&object->unk14, object->unk30 / object->unk2c);
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002934A0", func_00293600);
