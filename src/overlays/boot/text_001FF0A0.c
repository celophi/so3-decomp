#include "include_asm.h"
#include "overlays/boot/text_001FF0A0.h"

typedef struct FieldU8At060
{
    u8 pad[0x60];
    u8 value;
} FieldU8At060;

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF0A0", func_001FF0A0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF0A0", func_001FF3A0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF0A0", func_001FF730);

void func_001FF9D0(void* object)
{
    ((FieldU8At060*)object)->value = 0;
}

