#include "include_asm.h"
#include "overlays/3253-00/text_003A77E0.h"

/** Partial receiver containing a word at offset 0x14. */
struct FieldNonzeroWord14
{
    u8 unk00[0x14];
    u32 unk14;
};

/** Partial receiver containing a word at offset 0x1C. */
struct FieldWord1C
{
    u8 unk00[0x1C];
    u32 unk1C;
};

/** Partial object containing a word at offset 0x210. */
struct FieldWord210
{
    u8 unk00[0x210];
    u32 unk210;
};

/** Receiver whose first field points to the object containing the word. */
struct FieldObjectWord210
{
    FieldWord210* unk00;
};

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A77E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A7850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A7AB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A7B50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A7BF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A7C80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A7D30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A7FD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A84C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A8640);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A8740);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A87E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A8920);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A89A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A9040);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A9740);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A9810);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A9900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A9990);

u32 func_003A9A60(void* receiver)
{
    FieldObjectWord210* object = (FieldObjectWord210*)receiver;
    return object->unk00->unk210;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A9A70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A9B10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003A9DA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AA240);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AA2E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AA3D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AA440);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AA4E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AA600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AA680);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AA700);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AA970);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AABE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AAF50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ABDF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ABF00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ABF60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ABFB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AC470);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AC5E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AC6F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ACC50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ACE70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ACF10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ACF70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AD020);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AD2A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ADB50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ADBF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ADCD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003ADF00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AE200);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AE280);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AE4E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AE880);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AEAB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AED10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AED70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AF1C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AF1E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AF250);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AF550);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AFA50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AFAF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003AFB90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0060);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0100);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B06F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0790);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0820);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0920);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B09E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0B10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0BC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0BF0);

s32 func_003B0D20(void* object)
{
    return -1;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0D30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0D80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0E50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B0FE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B1140);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B1460);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B14C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B15D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B16C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B1AF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B25B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B2640);

s32 func_003B26B0(void* receiver)
{
    FieldNonzeroWord14* object = (FieldNonzeroWord14*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B26C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B2790);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B28D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B2A50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B2AC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B2B30);

u32 func_003B2C10(void* receiver)
{
    FieldWord1C* object = (FieldWord1C*)receiver;
    return object->unk1C;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B2C20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B3B90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B3C50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B4020);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B4070);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B4100);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B41E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B4940);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B49E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B4A90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B4B00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B5120);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B5450);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B5500);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B5A60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B5BF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B5E20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B60C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B6CC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B6FB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B71F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B7430);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_003A77E0", func_003B7670);
