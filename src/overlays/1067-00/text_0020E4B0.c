#include "include_asm.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_0020E4B0.h"

/** Partial field context with a word at offset 0x50. */
typedef struct FieldContextE4C0
{
    u8 unk00[0x50];
    u32 value;
} FieldContextE4C0;


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E4B0);

s32 func_0020E4C0(void* object)
{
    return ((FieldContextE4C0*)D_001B6430->context)->value != 0;
}

s32 func_0020E4E0(void* object)
{
    return 1;
}

s32 func_0020E4F0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E500);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E590);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E670);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E6A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E750);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E7D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020E9B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020EF20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020EF90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F520);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F5D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F6C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F7B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F9D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0020E4B0", func_0020F9E0);
