#include "include_asm.h"
#include "overlays/1070-00/text_002F5880.h"

struct FieldClampState
{
    u8 unk00[0xcb];
    u8 unkcb;
    u8 unkcc[0x340];
    s32 unk40c;
    s32 unk410;
    s32 unk414;
    s32 unk418;
    u8 unk41c[2];
    u8 unk41e;
    u8 unk41f[3];
    s8 unk422;
    u8 unk423[0xa1];
    s32 unk4c4;
};

void func_002F5880(FieldResetState18* object)
{
    object->unk20 = 0;
    object->unk24 = -1;
    object->unk18 = 0;
    object->unk26 = -1;
    object->unk28 = -1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_002F58A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_002F59E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_002F9A60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_002FFC40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_002FFCE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_002FFD80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_002FFE20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_002FFEC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_00303F50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_003040D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_003041A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_00304220);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_00304370);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_003049B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_00304B40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_00305410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_003054A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_003055A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_003055F0);

void func_00305650(FieldStatus44* object, float first, float second)
{
    object->unk20 = first;
    object->unk24 = second;
    object->unk44 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_00305670);

void func_003056F0(FieldStatus44* object, u32 unused, u8 value)
{
    object->unk45 = value;
}

float func_00305700(void)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_00305710);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_00305790);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002F5880", func_003057A0);

void func_00305830(FieldClampState* object, u16 value)
{
    s32 span = 7;
    s32 offset = value - 7;
    s32 limit = object->unk40c;
    if (offset < 0)
    {
        span += offset;
        offset = 0;
    }
    else if (offset > limit)
    {
        span += offset - limit;
        offset = limit;
    }
    object->unk410 = offset;
    object->unk41e = span;
    object->unk4c4 = 1;
    object->unkcb = 1;
    object->unk418 = -1;
    object->unk414 = -1;
    object->unk422 = -1;
}
