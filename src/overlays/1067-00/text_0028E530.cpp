#include "include_asm.h"
#include "overlays/1067-00/text_0028E530.h"
#include "overlays/1067-00/text_0021FB80.h"

/** Partial nested state containing three adjacent words. */
typedef struct FieldState5CC
{
    u8 unk00[0x5CC];
    u32 unk5CC;
    u32 unk5D0;
    u32 unk5D4;
} FieldState5CC;

/** Partial field context with a nested state pointer at offset 0x38. */
typedef struct FieldContext38
{
    u8 unk00[0x38];
    FieldState5CC* state;
} FieldContext38;

/** Partial resident state containing a signed word at offset 0x14. */
typedef struct FieldState6648
{
    u8 unk00[0x14];
    s32 unk14;
} FieldState6648;

extern FieldState6648* D_001B6648;


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028E530);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028E770);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028E840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028E890);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028F5B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028F690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028F710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028F8F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028F970);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_0028FFD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_002900A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_002903D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_002904A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00290580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00290620);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_002906A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00290DC0);

s32 func_00291080(const ResidentContextRef* object)
{
    FieldState5CC* state = ((FieldContext38*)object->context)->state;
    if (state != 0)
    {
        if (state->unk5CC != 0)
        {
            return 1;
        }
        if (state->unk5D0 != 0)
        {
            return 1;
        }
    }
    return 0;
}

s32 func_002910D0(void)
{
    s32 result = (0xF2 - D_001B6648->unk14 % 0x106) * 1024;
    if (result < 0x400)
    {
        result = 0x400;
    }
    return result;
}

s32 func_00291110(void* object)
{
    return ((FieldContext38*)D_001B6430->context)->state->unk5D4 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00291130);

FieldClass1570D0::~FieldClass1570D0()
{
}

void func_002911D0(FieldState2F0* object)
{
    object->unk2F0 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_002911E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_002912C0);

s32 func_00291410(FieldObject157160* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00291420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00291450);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00291690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00291840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00291930);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_002919F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00291A70);

void func_00291B60(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0028E530", func_00291B70);
