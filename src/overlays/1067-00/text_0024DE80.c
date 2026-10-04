#include "include_asm.h"
#include "overlays/1067-00/text_0024DE80.h"

/** Partial value pair attached at receiver offset 0x11C. */
typedef struct FieldValues24
{
    u8 pad[0x24];
    u32 first;
    u32 second;
} FieldValues24;

struct FieldObject11CValues
{
    u8 pad[0x11C];
    FieldValues24* values;
};

extern void* D_001B663C;
extern void func_4D9250(void* target, u32 first, u32 second);
extern void func_4D00B0(void* object);


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024DE80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024DF50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E2B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", __dt__16FieldClass1535B0Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", __ct__16FieldClass1535B0Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E530);

void func_0024E610(void* object)
{
}

void func_0024E620(void* object)
{
}

void func_0024E630(void* object)
{
}

void func_0024E640(void* object)
{
}

void func_0024E650(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E660);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E720);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E740);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E7C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E830);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E8B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024EDD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024FBB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_00250600);

void func_002507B0(FieldObject11CValues* object)
{
    func_4D9250(D_001B663C, object->values->first, object->values->second);
    func_4D00B0(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_002507F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_00250920);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_002516D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_00251800);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_00251B50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_00253340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_00253380);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_00253580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_00253600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_002538A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_002539F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_00253B30);

void func_00254180(FieldObject153730* object)
{
    object->bit0 = 1;
}

s32 func_002541A0(FieldObject153730* object)
{
    return 3;
}

void func_002541B0(FieldObject153730* object)
{
    object->unk60 = 9;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_002541C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_002541D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_002541E0);
