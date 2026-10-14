#include "include_asm.h"
#include "overlays/3253-00/text_001F2D50.h"

/** Partial receiver with a word at offset 0x0C. */
struct FieldWordAt0C
{
    u8 unk00[0x0C];
    u32 unk0C;
};

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F2D50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F3050);

void func_001F3540(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F3550);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F3990);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F3D40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F3E90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F4030);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F4CE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F51E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F90B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9100);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9160);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9230);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F92B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9350);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F94C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9560);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9640);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F96E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9780);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9800);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9AA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9AE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9DF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001F9EE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FA100);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FA170);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FA290);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FA310);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCBB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCC20);

void* func_001FCC80(void* receiver, s32 value)
{
    FieldWordAt0C* object = (FieldWordAt0C*)receiver;
    object->unk0C = value;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCC90);

void* func_001FCCB0(void* receiver, s32 value)
{
    FieldWordAt0C* object = (FieldWordAt0C*)receiver;
    object->unk0C = value;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCCC0);

void* func_001FCCE0(void* object)
{
    return object;
}

void* func_001FCCF0(void* receiver, s32 value)
{
    FieldWordAt0C* object = (FieldWordAt0C*)receiver;
    object->unk0C = value;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCD00);

void* func_001FCD20(void* receiver, s32 value)
{
    FieldWordAt0C* object = (FieldWordAt0C*)receiver;
    object->unk0C = value;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCD30);

void* func_001FCD50(void* receiver, s32 value)
{
    FieldWordAt0C* object = (FieldWordAt0C*)receiver;
    object->unk0C = value;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCD60);

void* func_001FCD80(void* object)
{
    return object;
}

void* func_001FCD90(void* receiver, s32 value)
{
    FieldWordAt0C* object = (FieldWordAt0C*)receiver;
    object->unk0C = value;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCDA0);

void* func_001FCDC0(void* receiver, s32 value)
{
    FieldWordAt0C* object = (FieldWordAt0C*)receiver;
    object->unk0C = value;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCDD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCDF0);

void* func_001FCE10(void* receiver, s32 value)
{
    FieldWordAt0C* object = (FieldWordAt0C*)receiver;
    object->unk0C = value;
    return object;
}

void* func_001FCE20(void* receiver, s32 value)
{
    FieldWordAt0C* object = (FieldWordAt0C*)receiver;
    object->unk0C = value;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCE30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCE50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FCE70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD0B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD100);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD150);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD460);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD4C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD560);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD650);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD780);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD800);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD810);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FD950);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FDAE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FE900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FEFE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_001FFA00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00200550);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00200FC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_002010E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_002011E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00201600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_002016C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00201700);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00201720);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00201750);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00201D60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00201DF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00201F30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_00201FD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001F2D50", func_002027A0);
