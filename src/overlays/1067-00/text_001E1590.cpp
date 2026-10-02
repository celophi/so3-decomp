#include "include_asm.h"
#include "overlays/1067-00/text_001E1590.h"
#include "boot/resident_data.h"
#include "overlays/1067-00/text_0022DC70.h"

s32 FieldClass150120::func_001DF3D0()
{
    return 4;
}

void FieldClass150120::func_001DD7B0()
{
    func_0011ED90(D_001B65F4, this);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E15C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E16B0);

s32 func_001E1820(const void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E1830);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E2E40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E3580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E39A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E4220);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E48A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E4E50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001DDB30__16FieldClass150120FPv);

void func_001E5020(FieldWordByte30* object, u32 word, u8 value)
{
    object->unk30 = word;
    object->unk34 = value;
}

FieldClass150120::~FieldClass150120()
{
    s32 i;
    for (i = 0; i < 10; i++)
    {
        if (unk44[i])
        {
            delete[] unk44[i];
            unk44[i] = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5110);

// Reads an unresolved $gp-relative global.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5220);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5520);

// Calls resident func_121FE0; needs its declaration and symbol mapping.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5650);

void func_001E5690(FieldSlotRecordOwner1C* object)
{
    s32 i;
    if (object->unk1c)
    {
        for (i = 0; i < object->unk24; i++)
        {
            FieldSlotRecord1C* record = &object->unk1c[i];
            record->unk0c = -1;
            record->unk04 = 0;
            record->unk10 = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->unk14 = 0;
            record->unk15 = 0;
        }
    }
    object->unk20 = 0;
    object->unk2f = 0;
    object->unk2d = 0;
    object->unk2e = 0;
    object->unk14 = 8;
    object->unk2f = 0;
    object->unk38 = 2;
    object->unk3c = -1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5770);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E57F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5A40);

void func_001E5AD0(FieldSlotRecordOwner1C* object)
{
    s32 i;
    if (object->unk1c)
    {
        for (i = 0; i < object->unk24; i++)
        {
            FieldSlotRecord1C* record = &object->unk1c[i];
            record->unk0c = -1;
            record->unk04 = 0;
            record->unk10 = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->unk14 = 0;
            record->unk15 = 0;
        }
    }
    object->unk20 = 0;
    object->unk2f = 0;
    object->unk2d = 0;
    object->unk2e = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5BA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5D20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5ED0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E5FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E64E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E6790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E68D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E6950);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E69A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E6B40);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E6C20);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E1590", func_001E6C30);

