#include "include_asm.h"
#include "overlays/1067-00/text_002E1870.h"
#include "overlays/1067-00/field_runtime.h"

/** Partial attached state with two status words. */
typedef struct FieldAttached148
{
    u8 pad[0x48];
    u32 value48;
    u8 pad4C[0xFC];
    u32 value148;
} FieldAttached148;

/** Partial active holder of the attached state. */
typedef struct FieldInner20
{
    u8 pad[0x14];
    FieldAttached148* attached;
    u8 pad18[8];
    u8 active20;
} FieldInner20;

struct FieldOuter14
{
    u8 pad[0x14];
    FieldInner20* inner;
};

// Packed-record checksum; repeated-load code generation remains unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E1870);

// Rolling checksum; loop scheduling remains unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E18E0);

// Large dispatcher; needs callback and runtime-record interfaces.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E19D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E7D20);

s32 func_002E7EF0(const FieldCheckedWordsState1870* object)
{
    u32 check = object->unkA8 ^ (object->unk54 ^ (object->unk4C + object->unk50));
    if (object->unk9C != check)
    {
        return 0;
    }
    return object->unk50 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E7F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E7FA0);

s32 func_002E80A0(const FieldCheckedWordsState1870* object)
{
    u32 check = object->unkA8 ^ (object->unk60 ^ (object->unk58 + object->unk5C));
    if (object->unkA0 != check)
    {
        return 0;
    }
    return object->unk60 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E80E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8150);

s32 func_002E8270(const FieldCheckedWordsState1870* object)
{
    u32 check = object->unkA8 ^ (object->unk48 ^ (object->unk40 + object->unk44));
    if (object->unk98 != check)
    {
        return 0;
    }
    return object->unk48 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E82B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8340);

s32 func_002E8440(const FieldCheckedWordsState1870* object)
{
    u32 check = object->unkA8 ^ (object->unk60 ^ (object->unk58 + object->unk5C));
    if (object->unkA0 != check)
    {
        return 0;
    }
    return object->unk6C ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8500);

s32 func_002E8600(const FieldCheckedWordsState1870* object)
{
    u32 check = object->unkA8 ^ (object->unk3C ^ (object->unk34 + object->unk38));
    if (object->unk94 != check)
    {
        return 0;
    }
    return object->unk3C ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E86C0);

// Checked-value getter; failure-path register allocation remains unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E88F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8990);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8BC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8C60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8D00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8DA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8E40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002E8EE0);

s32 func_002ECF70(FieldObject15B9A0* object)
{
    return 4;
}

u8 func_002ECF80(FieldObject15B9A0* object)
{
    return object->unk68;
}

s16 func_002ECF90(FieldObject15B9A0* object, s32 index)
{
    return object->unk5E[index];
}

void func_002ECFA0(FieldObject15B9A0* object, s16 index)
{
    object->unk64 = index;
    object->unk5E[object->unk64] = -1;
    object->unk5C[object->unk64] = 0;
    object->unk80 = 0;
    object->unk84 = 0;
    object->unk68 = 0;
}

u16 func_002ECFE0(const FieldOuter14* object)
{
    FieldAttached148* attached;
    u16 flags;
    if (!object->inner->active20)
    {
        return 0;
    }
    attached = object->inner->attached;
    flags = 0;
    if (attached->value48 == 2)
    {
        flags |= 1;
    }
    if (attached->value148 == 2)
    {
        flags |= 2;
    }
    return flags;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002ED040);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002ED130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002ED240);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002ED8D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDB20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDC90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDD20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDDB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDEC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDFA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EDFD0);

u16 func_002EE9B0(const FieldObject2EDFD0* object)
{
    return object->unk1050;
}

s32 func_002EE9C0(FieldObject2EDFD0* object, void* value)
{
    if (value == 0)
    {
        return 0;
    }
    object->unk1254 = value;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EE9E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EEB30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EEC90);

u8 func_002EED90(const FieldObject2EDFD0* object)
{
    return object->unk121E;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EEDA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EEE00);

void func_002EEE20(FieldObject2EDFD0* object, s16 value, u8 flag)
{
    object->unk105E = value;
    object->unk1060 = flag;
}

void* func_002EEE30(void* object, s32 index)
{
    FieldRuntimeRoot* root;
    FieldRuntimeSections* sections;
    u8* base;
    root = func_10D8E0();
    sections = func_101290(root);
    base = (u8*)func_101440(sections, 4);
    return base + 0xC6B0 + (index - 1) * 24;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EEE90);

FieldTransfer2EDFD0* func_002EF000(FieldObject2EDFD0* object)
{
    return &object->unkFF8;
}

void func_002EF010(FieldObject2EDFD0* object, s16 value)
{
    if (value > 50)
    {
        object->unk105A = 50;
    }
    object->unk105A = value;
}

s32 func_002EF030(FieldObject2EDFD0* object, s16 index)
{
    if (index < 0 || index > object->unk105A)
    {
        return 0;
    }
    object->unk1058 = index;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EF070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EF2B0);

// Header validation; inline comparison and result handling remain unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EF520);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EF6B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002EFFF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F0190);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F0750);

// Header validation; inline comparison register allocation remains unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F0D90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F0EF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F11F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002E1870", func_002F17F0);
