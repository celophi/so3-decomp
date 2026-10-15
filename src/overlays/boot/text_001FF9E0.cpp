#include "include_asm.h"
#include "overlays/boot/text_001FF0A0.h"

extern "C" void func_11F770(void* owner, void* object);

typedef struct FieldU8At064
{
    u8 pad[0x64];
    u8 value;
} FieldU8At064;

void func_001FF9E0(void* object)
{
    ((FieldU8At064*)object)->value = 0;
    func_4D00B0(object);
}

struct N50Owner94_001FF9E0 { u8 pad00[0x64]; u8 active; u8 pad65[0x2F]; void* owner; };

void func_001FFA00(N50Owner94_001FF9E0* object)
{
    object->active = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0x90;
    }
    func_11F770(object->owner, adjusted);
}

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_001FFA40);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_00200080);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_002001A0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_002002B0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_002006E0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_00200C50);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_00200E70);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_00201B70);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_002044F0);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_00204850);

INCLUDE_ASM("build/overlays/boot/asm/nonmatchings/text_001FF9E0", func_00204C40);

s32 func_002050C0(void* object)
{
    return 4;
}

