#include "include_asm.h"
#include "overlays/3253-00/text_00285100.h"

struct BattleObject2E0B
{
    u8 pad[0x2DC8];
    u32 unk2DC8;
    u8 pad2DCC[0x38];
    u8 unk2E04;
    u8 unk2E05;
    u8 unk2E06;
    u8 unk2E07;
    u8 unk2E08;
    u8 pad2E09[2];
    u8 unk2E0B;
};

struct BattleObject2F26
{
    u8 pad[0x2EEC];
    u32 unk2EEC;
    u8 pad2EF0[0x30];
    u8 unk2F20;
    u8 unk2F21;
    u8 unk2F22;
    u8 pad2F23[3];
    u8 unk2F26;
};

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285100);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002851E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285220);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285280);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002852A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285320);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002856E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002857F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285A60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285C50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285DE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00285E20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00286130);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00286390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002864B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00286900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00286C90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00287170);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002877D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002879B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00287C50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00288AC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00289560);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00289630);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002899D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00289D90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00289F20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_0028A620);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_0028B2D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_0028BC30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_0028CE50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_0028DFE0);

void func_0028E2A0(BattleObject2E0B* object, u8 current, u8 previous)
{
    if ((u32)(previous - 1) <= 1 || previous == 3)
    {
        object->unk2E04 = 0;
    }
    if (previous >= 5 && current == 0)
    {
        object->unk2E06 = 0;
        object->unk2E0B = 0;
        object->unk2E08 = 0;
    }
    if (current == 5 || current == 10 || current == 12 || current == 13)
    {
        object->unk2DC8 = 0;
    }
    if (current == 6 || current == 7)
    {
        object->unk2E06 = 0;
        object->unk2E08 = 0;
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_0028E350);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_0028E3C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_0028EEF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_0028FB00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00291310);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00291610);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00291820);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00291A00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00292090);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00292750);

void func_00292930(BattleObject2F26* object, u8 current, u8 previous)
{
    if (previous == 1)
    {
        object->unk2F20 = 0;
    }
    if (previous >= 5 && current == 0)
    {
        object->unk2F22 = 0;
        object->unk2F26 = 0;
    }
    if (current == 5 || current == 10 || current == 12 || current == 13)
    {
        object->unk2EEC = 0;
    }
    if (current == 6 || current == 7)
    {
        object->unk2F22 = 0;
    }
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002929D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00292A40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00292FC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00293210);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_002937E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00293E40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00285100", func_00294620);
