#include "include_asm.h"
#include "overlays/0002-00/text_001FF0A0.h"

typedef struct FieldU8At060
{
    u8 pad[0x60];
    u8 value;
} FieldU8At060;


INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_001FF0A0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_001FF3A0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_001FF730);

void func_001FF9D0(void* object)
{
    ((FieldU8At060*)object)->value = 0;
}

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_001FF9E0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_001FFA00);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_001FFA40);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_00200080);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_002001A0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_002002B0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_002006E0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_00200C50);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_00200E70);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_00201B70);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_002044F0);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_00204850);

INCLUDE_ASM("build/overlays/0002-00/asm/nonmatchings/text_001FF0A0", func_00204C40);

s32 func_002050C0(void* object)
{
    return 4;
}

extern void func_001FF9E0(void* object);

void func_002050D0(void* object)
{
    func_001FF9E0((u8*)object - 0x90);
}
