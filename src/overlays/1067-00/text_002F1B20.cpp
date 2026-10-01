#include "include_asm.h"
#include "overlays/1067-00/text_002F1B20.h"

/** Partial target with a byte at offset 0x140. */
struct FieldByte140
{
    u8 pad[0x140];
    u8 value;
};

/** Partial global state with a target pointer at offset 0x20. */
struct FieldGlobal20
{
    u8 pad[0x20];
    FieldByte140* target;
};

extern "C" FieldGlobal20* D_001B643C;


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F1B20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F1B60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F1E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F23E0);

void func_002F2460(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2740);

extern "C" u8 func_002F2880(void)
{
    return D_001B643C->target->value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2890);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2900);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2B20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2EC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F2FA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3020);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F30A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F31D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3250);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3290);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F1B20", func_002F3300);
