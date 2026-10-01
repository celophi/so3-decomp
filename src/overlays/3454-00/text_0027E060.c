#include "include_asm.h"
#include "overlays/3454-00/text_0027E060.h"

s32 func_00291A40(void* object);
void func_002A0720(void* object, s32 state);


struct Obj27E060
{
    u8 unk000[0x561];
    u8 unk561;
    u8 unk562[0x27DE];
    float unk2D40[36];
    u8 unk2DD0[4];
    float unk2DD4;
    u8 unk2DD8[0x30];
    u32 unk2E08;
    u8 unk2E0C[0xC];
    u8 unk2E18;
    u8 unk2E19;
    u8 unk2E1A;
    u8 unk2E1B;
    u8 unk2E1C;
    u8 unk2E1D[3];
    u8 unk2E20;
    u8 unk2E21[0x27];
    float unk2E48[36];
    u8 unk2ED8[4];
    float unk2EDC;
    u8 unk2EE0[0x30];
    u8 unk2F10;
    u8 unk2F11;
    u8 unk2F12;
    u8 unk2F13[3];
    u8 unk2F16;
    u8 unk2F17[0x45];
    u32 unk2F5C;
};

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027E060);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027E250);

void func_0027E3E0(void* object)
{
    if (func_00291A40(object))
    {
        func_002A0720(object, 0);
    }
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027E420);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027E740);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027E9A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027EAF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027EF40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027F2D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027F800);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0027FE90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00280070);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00280310);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00281180);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_002817A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00281870);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00281D40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00282100);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_002822A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00282A00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_002837D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00284220);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00285480);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00286650);

void func_00286910(Obj27E060* object, u8 first_code, u8 second_code)
{
    if ((u32)(second_code - 1) <= 1 || second_code == 3)
    {
        object->unk2E18 = 0;
    }
    if (second_code >= 5 && first_code == 0)
    {
        object->unk2E1A = 0;
        object->unk2E20 = 0;
        object->unk2E1C = 0;
    }
    if (first_code == 5 || first_code == 10 || first_code == 12 || first_code == 13)
    {
        object->unk2DD4 = 0.0f;
    }
    if (first_code == 6 || first_code == 7)
    {
        object->unk2E1A = 0;
        object->unk2E1C = 0;
    }
}

void func_002869C0(Obj27E060* object, u32 unused, s32 enabled)
{
    if (enabled)
    {
        s32 index = object->unk561;
        if (index >= 0 && index < 36)
        {
            float previous = object->unk2D40[index];
            float value = object->unk2DD4;
            if (!(previous <= value) || previous == 0.0f)
            {
                object->unk2D40[index] = value;
            }
        }
    }
    object->unk2E20 = 0;
    object->unk2E1A = 0;
    object->unk2E1C = 0;
    object->unk2E08 = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00286A30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_00287720);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_002884C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028A6E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028AA20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028AC40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028AE20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028B4F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028BBD0);

void func_0028BDB0(Obj27E060* object, u8 first_code, u8 second_code)
{
    if (second_code == 1)
    {
        object->unk2F10 = 0;
    }
    if (second_code >= 5 && first_code == 0)
    {
        object->unk2F12 = 0;
        object->unk2F16 = 0;
    }
    if (first_code == 5 || first_code == 10 || first_code == 12 || first_code == 13)
    {
        object->unk2EDC = 0.0f;
    }
    if (first_code == 6 || first_code == 7)
    {
        object->unk2F12 = 0;
    }
}

void func_0028BE50(Obj27E060* object, u32 unused, s32 enabled)
{
    if (enabled)
    {
        s32 index = object->unk561;
        if (index >= 0 && index < 36)
        {
            float previous = object->unk2E48[index];
            float value = object->unk2EDC;
            if (!(previous <= value) || previous == 0.0f)
            {
                object->unk2E48[index] = value;
            }
        }
    }
    object->unk2F16 = 0;
    object->unk2F12 = 0;
    object->unk2F5C = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028BEC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028C440);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028C690);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028CC60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028D2C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0027E060", func_0028DAA0);
