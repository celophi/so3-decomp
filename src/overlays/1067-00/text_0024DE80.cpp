#include "include_asm.h"
#include "overlays/1067-00/text_0024DE80.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004BD360.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_0021FB80.h"

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
extern "C" void func_4D9250(void* target, u32 first, u32 second);
extern "C" void func_4D00B0(void* object);


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024DE80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024DF50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E2B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E310);

FieldClass1535B0::~FieldClass1535B0()
{
}

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

/** Partial field target with its owned container, child and effect handle. */
struct FieldOwner24E860
{
    u8 unk00[0x12C];
    LibObject178660* unk12c;
    FieldClass150070* child;
    u32 unk134;
    u8 unk138[0x10D4];
    s32 unk120c;
    u32 unk1210;
    u8 unk1214[4];
    s32 unk1218;
};

/**
 * @brief Release the target's container and effect handle and set its state to five.
 * @param owner Target receiver.
 */
extern "C" void func_0024E7C0(FieldOwner24E860* owner)
{
    owner->child = 0;
    owner->unk134 = 0;
    if (owner->unk12c != 0)
    {
        owner->unk12c->func_003EF740();
        owner->unk12c = 0;
    }
    if (owner->unk120c >= 0)
    {
        func_00465430(D_001B657C, owner->unk120c);
    }
    owner->unk120c = -1;
    owner->unk1218 = 5;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_0024DE80", func_0024E830);

void func_0024E860(FieldOwner24E860* owner, u32 value)
{
    if (owner->child != 0)
    {
        owner->child->func_001DD7B0();
        owner->child = 0;
    }
    owner->unk1210 = value;
}

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
