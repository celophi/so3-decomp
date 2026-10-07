#include "include_asm.h"
#include "overlays/1067-00/text_002F3310.h"

/** Partial receiver with a byte at offset 0x60. */
struct FieldByte60F3310
{
    u8 pad[0x60];
    u8 value;
};

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F3310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F33A0);

void FieldClass15BA10::func_001DD7B0()
{
    if (unk14 != 0)
    {
        func_004D65C0(unk14);
        unk14->func_001DD7B0();
        unk14 = 0;
    }
    delete this;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F3760);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F37D0);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002F3860(FieldClass150070* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F3870);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F3B00);

void FieldClass15BA50::func_001DD7B0()
{
    func_004D65C0(this);
    if (unk18 != 0)
    {
        func_004D65C0(this);
        unk18->func_001DD7B0();
    }
    unk18 = 0;
    delete this;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F3C00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F4260);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F4310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F4520);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F4730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F4E40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F52D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F61A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F6C70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F70D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F7CD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F8590);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F87B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F8E80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F9130);

extern "C" void func_002F9760(FieldByte60F3310* object)
{
    object->value = 2;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F9770);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F97C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F97E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F9810);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F99B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F99F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F9A80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F9BB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F9C70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F3310", func_002F9C80);
