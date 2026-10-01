#include "include_asm.h"
#include "overlays/1067-00/text_002D5260.h"


extern "C" void func_467750(FieldState2D63F0* object);
extern "C" void func_4D00B0(FieldFlagState2D7AA0* object);

void func_002D5260(FieldObject2D5260* object, float first, float second)
{
    FieldState2D5260* state = object->unk30;
    if (state != 0)
    {
        state->unk20 = first;
        state->unk24 = second;
        state->unk3C = 1;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D5290);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D59F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D5A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D5AA0);

void func_002D5CE0(FieldFlagObject2D5CE0* object)
{
    object->unk3C = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D5CF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D5DA0);

void func_002D63F0(FieldState2D63F0* object)
{
    object->unk3C = 1;
    func_467750(object);
}

void func_002D6410(FieldState2D6410* object)
{
    object->unkCC = 0;
    object->unkD0 = 0;
    object->unk108 = 0;
    object->unk10C = 0;
    object->unk10E = 0;
    object->unk110 = 0;
    object->unk111 = 0;
    object->unk112 = 0;
    object->unk113 = 0;
    object->unk114 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D6440);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D6570);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D65E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D6660);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D66C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D68F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D69A0);

void func_002D6A20(void* object)
{
}

void func_002D6A30(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D6A40);

void func_002D6AD0(FieldScalarState2D6A40* object, u8 value)
{
    object->unkCB = value;
}

void func_002D6AE0(FieldScalarState2D6A40* object, float value)
{
    object->unkE0 = value;
    object->unkCE = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D6AF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D6CB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D70F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7150);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D72B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D73B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7500);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7540);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7630);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7820);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D78E0);

void func_002D79C0(void* object)
{
}

s32 func_002D79D0(FieldPackedTable2D79D0* object, s32 index, FieldPackedValues2D79D0* output)
{
    if ((object->unk14AC & 1) == 0)
    {
        return 0;
    }
    u64 first = object->entries[index].unk00;
    u64 second = object->entries[index].unk08;
    output->unk04 = (first >> 14) & 0x3F;
    output->unk05 = (first >> 20) & 0x3F;
    output->unk06 = (first >> 26) & 0xF;
    output->unk07 = (first >> 30) & 0xF;
    output->unk00 = first & 0x3FFF;
    output->unk02 = (second >> 37) & 0x3FFF;
    return 1;
}

s32 func_002D7A50(FieldSlotTable2D7A50* object, void* first, void* second)
{
    for (s32 index = 0; index < 32; index++)
    {
        if (object->entries[index].unk00 == 0)
        {
            object->entries[index].unk00 = first;
            object->entries[index].unk04 = second;
            return index;
        }
    }
    return -1;
}

void func_002D7AA0(FieldFlagState2D7AA0* object)
{
    object->active = 1;
    func_4D00B0(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7AD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D7B80);

void func_002D7FE0(void* object)
{
}

void func_002D7FF0(void* object)
{
}

float func_002D8000(void* object)
{
    return 0.0f;
}

void func_002D8010(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8020);

void func_002D80E0(FieldScalarState2D8020* object, u8 value)
{
    object->unkCB = value;
}

void func_002D80F0(FieldScalarState2D8020* object, float value)
{
    object->unkE0 = value;
    object->unkCE = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8100);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8180);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 5.
 */
s32 func_002D82E0(FieldClass150070* object)
{
    return 5;
}

void func_002D82F0(FieldState2D82F0* object)
{
    object->unk60 = 9;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8300);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8320);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8350);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8370);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8380);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8390);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D83F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002D5260", func_002D8400);
