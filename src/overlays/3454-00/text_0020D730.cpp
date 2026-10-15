#include "include_asm.h"
#include "overlays/lib/vector.h"
#include "overlays/3454-00/text_0020D730.h"

typedef struct N66Vector4Source { float x; float y; float z; float w; } N66Vector4Source;
extern "C" {
void func_4B1640(void* object);
float func_4B16C0(void* object, float key);
void func_00217720(void* object);
void func_00218270(void* object);
void func_00217280(void* object);
void func_00217D70(void* object);
void func_4CE4C0(float* output, const float* input);
extern u8 D_50CD30[];
extern u8 D_177BE0[];
extern u8 D_174440[];
extern u8 D_1730F0[];
extern u8 D_15D2D0[];
extern u8 D_15D2C0[];
extern u8 D_15D2B0[];
extern u8 D_15D300[];
void func_00218990(void);
void func_00219390(void);
void func_00219400(void);
void func_00216AB0(void* object);
void func_00216B10(void* object);
void func_00216B70(void* object);

typedef struct WrapperPointerSlots
{
    u8 pad00[0x10];
    void* field10;
    u8 pad14[8];
    void* field1C;
} WrapperPointerSlots;

typedef struct N59Receiver0_0020D730
{
    u32 unk00;
    u8 pad04[0xC];
    void* vtable;
} N59Receiver0_0020D730;

typedef struct ConstantByteSetterOwnertext_0020D730
{
    u8 unk00[0x60];
    u8 unk60;
} ConstantByteSetterOwnertext_0020D730;



typedef struct HalfwordGetterOwnertext_0020D730
{
    u8 unk00[0x18];
    s16 unk18;
    s16 unk1a;
    u8 unk1c[0x4];
    s16 unk20;
    s16 unk22;
    u8 unk24[0x4];
    s16 unk28;
    s16 unk2a;
    u8 unk2c[0xC];
    s16 unk38;
    s16 unk3a;
    u8 unk3c[0xC];
    s16 unk48;
    s16 unk4a;
} HalfwordGetterOwnertext_0020D730;



typedef struct WordGetterOwnertext_0020D730
{
    u8 unk00[0x4];
    u32 unk04;
    u8 unk08[0x8];
    u32 unk10;
    u8 unk14[0x4];
    u32 unk18;
    u8 unk1c[0x4];
    u32 unk20;
    u8 unk24[0xC];
    u32 unk30;
    u8 unk34[0xC];
    u32 unk40;
} WordGetterOwnertext_0020D730;

typedef struct ClearForwardWordOwnertext_0020D730
{
    u8 unk00[0x48];
    u32 unk48;
    u32 unk4c;
} ClearForwardWordOwnertext_0020D730;

/** Four consecutive words cleared by the small reset helpers. */
typedef struct FourWordClearOwnertext_0020D730
{
    u32 words[4];
} FourWordClearOwnertext_0020D730;


typedef struct FlagQuadwordOwnertext_0020D730 { u8 unk00[0x20]; unsigned __int128 slots[3]; u8 ready; } FlagQuadwordOwnertext_0020D730;


typedef struct FlagFloatQuadOwnertext_0020D730
{
    u8 unk00[0x30];
    float values[4];
    u8 unk40[0x10];
    u8 flag50;
} FlagFloatQuadOwnertext_0020D730;

typedef struct FlagFloatTripleOwnertext_0020D730 { u8 pad00[0x40]; float values[3]; u8 pad4C[4]; u8 flag50; } FlagFloatTripleOwnertext_0020D730;

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x22];
    PackedModePair at22;
    u8 unk24[0x6];
    PackedModePair at2a;
    u8 unk2c[0x6];
    PackedModePair at32;
    u8 unk34[0xE];
    PackedModePair at42;
    u8 unk44[0xE];
    PackedModePair at52;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_0020D730_08
{
    float key00;
    u8 unk04[0x4];
} FloatKeyScanEntry_text_0020D730_08;

typedef struct FloatDiffEntry_text_0020D730_08
{
    u32 unk00;
    float value;
} FloatDiffEntry_text_0020D730_08;

typedef struct FloatDiffEntry_text_0020D730_10
{
    u32 unk00;
    float value;
    u8 unk08[8];
} FloatDiffEntry_text_0020D730_10;

typedef struct FloatKeyScanOwner_text_0020D730_08
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_0020D730_08* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x6];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_0020D730_08;

typedef struct FloatKeyScanEntry_text_0020D730_10
{
    float key00;
    u8 unk04[0x8];
    float key0c;
} FloatKeyScanEntry_text_0020D730_10;

typedef struct FloatKeyScanOwner_text_0020D730_10
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_0020D730_10* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x6];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_0020D730_10;

typedef struct FloatKeyScanEntry_text_0020D730_20
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x10];
} FloatKeyScanEntry_text_0020D730_20;

typedef struct FloatKeyScanOwner_text_0020D730_20
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_0020D730_20* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x6];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_0020D730_20;

typedef struct FloatKeyScanEntry_text_0020D730_30
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x20];
} FloatKeyScanEntry_text_0020D730_30;

typedef struct FloatKeyScanOwner_text_0020D730_30
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_0020D730_30* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x6];
    s16 count28;
    u8 unk2a[0xE];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_0020D730_30;

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0020D730);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0020DE80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0020EB20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0020EF00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0020EF40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0020EFD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0020F850);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0020F990);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00210530);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00210BA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00210CF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00210FC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211090);

void func_002115A0(void* object)
{
}

void func_002115B0(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002115C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002115D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002115E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211600);

s32 func_00211690(void* object)
{
    return 3;
}

void func_002116A0(void* object)
{
}

void func_002116B0(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnertext_0020D730* receiver = (FlagQuadwordOwnertext_0020D730*)object;
    receiver->ready = 1;
    receiver->slots[0] = *value;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002116D0);

void func_002116F0(void* object, float x, float y, float z, float w)
{
    FlagFloatQuadOwnertext_0020D730* receiver = (FlagFloatQuadOwnertext_0020D730*)object;
    receiver->flag50 = 1;
    receiver->values[0] = x;
    receiver->values[1] = y;
    receiver->values[2] = z;
    receiver->values[3] = w;
}

void func_00211710(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnertext_0020D730* receiver = (FlagQuadwordOwnertext_0020D730*)object;
    receiver->ready = 1;
    receiver->slots[1] = *value;
}

void func_00211730(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnertext_0020D730* receiver = (FlagQuadwordOwnertext_0020D730*)object;
    receiver->ready = 1;
    receiver->slots[1] = *value;
}

void func_00211750(void* object, const float* input)
{
    FlagFloatQuadOwnertext_0020D730* receiver = (FlagFloatQuadOwnertext_0020D730*)object;
    receiver->flag50 = 1;
    func_4CE4C0(receiver->values, input);
}

void func_00211780(void* object, const float* input)
{
    FlagFloatQuadOwnertext_0020D730* receiver = (FlagFloatQuadOwnertext_0020D730*)object;
    receiver->flag50 = 1;
    func_4CE4C0(receiver->values, input);
}

void func_002117B0(u8* object, float x, float y, float z)
{
    N66Vector4Source value;
    object[0x50] = 1;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    func_4CE4C0((float*)(object + 0x30), &value.x);
}

void func_002117F0(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnertext_0020D730* receiver = (FlagQuadwordOwnertext_0020D730*)object;
    receiver->ready = 1;
    receiver->slots[2] = *value;
}

void func_00211810(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnertext_0020D730* receiver = (FlagQuadwordOwnertext_0020D730*)object;
    receiver->ready = 1;
    receiver->slots[2] = *value;
}

void func_00211830(void* object, float x, float y, float z)
{
    FlagFloatTripleOwnertext_0020D730* receiver = (FlagFloatTripleOwnertext_0020D730*)object;
    receiver->flag50 = 1;
    receiver->values[0] = x;
    receiver->values[1] = y;
    receiver->values[2] = z;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211850);

void func_00211940(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0;
}

void func_00211950(void* object)
{
}

s32 func_00211960(void* object)
{
    return 0;
}

s32 func_00211970(float value)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

const void* func_00211990(void)
{
    return D_50CD30;
}

void func_002119A0(void* object)
{
}

s32 func_002119B0(void* object)
{
    return 0;
}

void func_002119C0(void* object)
{
}

void func_002119D0(void* object)
{
}

s32 func_002119E0(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002119F0);

s32 func_00211A80(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211A90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211B20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211BD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211C80);

/** Store 0x9 at receiver offset 0x60. */
void func_00211D10(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

void func_00211D20(void* object)
{
}

void func_00211D30(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211D40);

/** Store 0x9 at receiver offset 0x60. */
void func_00211DD0(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

void func_00211DE0(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0;
}

/** Build a four-word stack value and return its address. */
void* func_00211DF0(void)
{
    s32 stack[4];
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    s32* result = stack;
    stack[2] = 0;
    return result;
}

/** Store 0x9 at receiver offset 0x60. */
void func_00211E20(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211E30);

/** Store 0x9 at receiver offset 0x60. */
void func_00211EC0(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211ED0);

/** Store 0x6 at receiver offset 0x60. */
void func_00211F60(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x6;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00211F70);

/** Store 0x9 at receiver offset 0x60. */
void func_00212000(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

/** Store 0x9 at receiver offset 0x60. */
void func_00212010(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212020);

/** Store 0x9 at receiver offset 0x60. */
void func_002120B0(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002120C0);

/** Store 0x9 at receiver offset 0x60. */
void func_00212150(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212160);

/** Store 0x9 at receiver offset 0x60. */
void func_002121F0(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212200);

/** Store 0x6 at receiver offset 0x60. */
void func_00212290(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x6;
}

/** Store 0x9 at receiver offset 0x60. */
void func_002122A0(void* object)
{
    ConstantByteSetterOwnertext_0020D730* receiver = (ConstantByteSetterOwnertext_0020D730*)object;
    receiver->unk60 = 0x9;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002122B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212580);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212600);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212660);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002126D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212730);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002128D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212BB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212C30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212C90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212D00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212D60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00212F00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002131D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00213240);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002132A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00213300);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002134A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00213780);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002137F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00213850);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002138B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00213A50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00213D30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00213DA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00213E00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00213E60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00214000);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002142C0);

void* func_00214320(void* object)
{
    func_00218990();
    *(void**)object = D_177BE0;
    return object;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00214360);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002144F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002147C0);

void* func_00214820(void* object)
{
    func_00219390();
    *(void**)object = D_174440;
    return object;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00214860);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00214A00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00214CE0);

void* func_00214D40(void* object)
{
    func_00219400();
    *(void**)object = D_1730F0;
    return object;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00214D80);

void func_00214F20(void* object)
{
    func_4B1640(object);
}

void func_00214F40(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00214F50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00214F80);

s32 func_00214FD0(void* object)
{
    return 0;
}

s32 func_00214FE0(void* object)
{
    return 0;
}

s32 func_00214FF0(void* object)
{
    return 0;
}

s32 func_00215000(void* object)
{
    return 0;
}

void func_00215010(void* object)
{
}

void func_00215020(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00215030);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00215090);

float func_002150C0(void* object, float key)
{
    return func_4B16C0(object, key);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002150E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00215140);

struct ResetVector90_0020D730 { u8 pad[0x90]; FieldVec4B value; };

void func_00215170(void* object)
{
    ((ResetVector90_0020D730*)object)->value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    func_00217280(object);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002151B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002156A0);

extern "C" void func_00215710(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xA0);
}

void func_00215730(void* object)
{
    ClearForwardWordOwnertext_0020D730* state = (ClearForwardWordOwnertext_0020D730*)object;
    state->unk48 = 0;
    func_00217720(object);
}

void func_00215750(const void* object, float* output)
{
    const FloatKeyScanOwner_text_0020D730_08* receiver = (const FloatKeyScanOwner_text_0020D730_08*)object;
    FloatDiffEntry_text_0020D730_08* entries = (FloatDiffEntry_text_0020D730_08*)receiver->entries;
    if (entries != 0)
    {
        *output = entries[receiver->count18 - 1].value - entries[0].value;
    }
}

void func_00215780(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0x4C);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00215790);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002157E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00215830);

void* func_002158B0(void* receiver)
{
    N59Receiver0_0020D730* object = (N59Receiver0_0020D730*)receiver;
    func_00216B30(receiver);
    object->vtable = D_15D300;
    object->unk00 = 0;
    return receiver;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002158F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00215990);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00215A20);

struct ResetVectorB0_0020D730 { u8 pad[0xB0]; FieldVec4B value; };

void func_00215AA0(void* object)
{
    ((ResetVectorB0_0020D730*)object)->value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    func_00217D70(object);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00215AE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216250);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216330);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002163A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216450);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002164C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216530);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002165A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216680);

extern "C" void func_002166C0(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xC0);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002166E0);

void func_00216760(void* object)
{
    ClearForwardWordOwnertext_0020D730* state = (ClearForwardWordOwnertext_0020D730*)object;
    state->unk4c = 0;
    func_00218270(object);
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216780);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002167E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216840);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002168A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216900);

void func_00216940(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0x50);
}

void func_00216950(const void* object, float* output)
{
    const FloatKeyScanOwner_text_0020D730_10* receiver = (const FloatKeyScanOwner_text_0020D730_10*)object;
    FloatDiffEntry_text_0020D730_10* entries = (FloatDiffEntry_text_0020D730_10*)receiver->entries;
    if (entries != 0)
    {
        *output = entries[receiver->count20 - 1].value - entries[0].value;
    }
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216980);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002169A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216A00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216A20);

void* func_00216A70(void* object)
{
    ((WrapperPointerSlots*)object)->field1C = D_15D2D0;
    func_00216AB0(object);
    return object;
}

void func_00216AB0(void* object)
{
    u8* bytes = (u8*)object;
    *(u16*)(bytes + 0x10) = 0;
    *(u16*)(bytes + 0x12) = 0;
    *(u32*)(bytes + 0x14) = 0;
    *(u32*)(bytes + 0x18) = 0;
}

void* func_00216AD0(void* object)
{
    ((WrapperPointerSlots*)object)->field1C = D_15D2C0;
    func_00216B10(object);
    return object;
}

void func_00216B10(void* object)
{
    u8* bytes = (u8*)object;
    *(u16*)(bytes + 0x10) = 0;
    *(u16*)(bytes + 0x12) = 0;
    *(u32*)(bytes + 0x14) = 0;
    *(u32*)(bytes + 0x18) = 0;
}

void* func_00216B30(void* object)
{
    ((WrapperPointerSlots*)object)->field10 = D_15D2B0;
    func_00216B70(object);
    return object;
}

void func_00216B70(void* object)
{
    u8* bytes = (u8*)object;
    *(u16*)(bytes + 0x4) = 0;
    *(u16*)(bytes + 0x6) = 0;
    *(u32*)(bytes + 0x8) = 0;
    *(u32*)(bytes + 0xC) = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216B90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216C00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216C50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216CC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216D10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216D80);

/** Set the low mode and record whether either mode equals four. */
void func_00216E10(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Set the high packed mode and record whether either mode equals four. */
void func_00216E70(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Return the word at receiver offset 0x30. */
u32 func_00216ED0(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk30;
}

/** Return the signed halfword at receiver offset 0x38. */
s16 func_00216EE0(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk38;
}

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_00216EF0(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk3a;
}

void func_00216F00(void* object)
{
    FourWordClearOwnertext_0020D730* receiver = (FourWordClearOwnertext_0020D730*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216F20);

/** Return the word at receiver offset 0x4. */
u32 func_00216F70(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216F80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00216FD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002170B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217210);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217280);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217310);

/** Set the low packed mode at 0x32 and record whether either mode equals four. */
void func_00217360(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at32.lowMode = mode;
    receiver->at32.hasModeFour = receiver->at32.lowMode == 4 || receiver->at32.highMode == 4;
}

/** Set the high packed mode at 0x32 and record whether either mode equals four. */
void func_002173C0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at32.highMode = mode;
    receiver->at32.hasModeFour = receiver->at32.lowMode == 4 || receiver->at32.highMode == 4;
}

/** Return the word at receiver offset 0x20. */
u32 func_00217420(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk20;
}

/** Return the signed halfword at receiver offset 0x28. */
s16 func_00217430(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk28;
}

/** Return the signed halfword at receiver offset 0x2A. */
s16 func_00217440(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk2a;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_00217450(void* object, float key)
{
    FloatKeyScanOwner_text_0020D730_10* receiver = static_cast<FloatKeyScanOwner_text_0020D730_10*>(object);
    s16 count = receiver->count28;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_002174A0(void* object)
{
    FourWordClearOwnertext_0020D730* receiver = (FourWordClearOwnertext_0020D730*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

/** Return the key span between the first and last entries. */
float func_002174C0(void* object)
{
    const FloatKeyScanOwner_text_0020D730_10* receiver = static_cast<const FloatKeyScanOwner_text_0020D730_10*>(object);
    s32 count = receiver->count28;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_0020D730_10* entries = receiver->entries;
    const FloatKeyScanEntry_text_0020D730_10* lastEntry = entries + --count;
    float first = entries[0].key0c;
    float last = lastEntry->key0c;
    return last - first;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217510);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217570);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002175C0);

/** Return the word at receiver offset 0x4. */
u32 func_00217650(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217660);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002176B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217720);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002177B0);

/** Set the low packed mode at 0x22 and record whether either mode equals four. */
void func_00217850(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.lowMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/** Set the high packed mode at 0x22 and record whether either mode equals four. */
void func_002178B0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.highMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/** Return the word at receiver offset 0x10. */
u32 func_00217910(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk10;
}

/** Return the signed halfword at receiver offset 0x18. */
s16 func_00217920(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk18;
}

/** Return the signed halfword at receiver offset 0x1A. */
s16 func_00217930(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk1a;
}

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00217940(void* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217950);

/** Return the word at receiver offset 0x4. */
u32 func_00217980(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217990);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002179E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217A50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217AA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217B90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217D00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217D70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217E00);

/** Set the low packed mode at 0x52 and record whether either mode equals four. */
void func_00217E50(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.lowMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Set the high packed mode at 0x52 and record whether either mode equals four. */
void func_00217EB0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.highMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Return the word at receiver offset 0x40. */
u32 func_00217F10(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk40;
}

/** Return the signed halfword at receiver offset 0x48. */
s16 func_00217F20(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk48;
}

/** Return the signed halfword at receiver offset 0x4A. */
s16 func_00217F30(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk4a;
}

s32 func_00217F40(void* object)
{
    return 0;
}

s32 func_00217F50(void* object)
{
    return 0;
}

s32 func_00217F60(void* object)
{
    return 0;
}

void func_00217F70(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_00217F80(void* object, float key)
{
    FloatKeyScanOwner_text_0020D730_30* receiver = static_cast<FloatKeyScanOwner_text_0020D730_30*>(object);
    s16 count = receiver->count48;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_00217FD0(void* object)
{
    FourWordClearOwnertext_0020D730* receiver = (FourWordClearOwnertext_0020D730*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00217FF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218040);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002180B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218100);

/** Return the word at receiver offset 0x4. */
u32 func_002181A0(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002181B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218200);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218270);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218300);

/** Set the low packed mode at 0x2A and record whether either mode equals four. */
void func_002183A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at2a.lowMode = mode;
    receiver->at2a.hasModeFour = receiver->at2a.lowMode == 4 || receiver->at2a.highMode == 4;
}

/** Set the high packed mode at 0x2A and record whether either mode equals four. */
void func_00218400(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at2a.highMode = mode;
    receiver->at2a.hasModeFour = receiver->at2a.lowMode == 4 || receiver->at2a.highMode == 4;
}

/** Return the word at receiver offset 0x18. */
u32 func_00218460(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk18;
}

/** Return the signed halfword at receiver offset 0x20. */
s16 func_00218470(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk20;
}

/** Return the signed halfword at receiver offset 0x22. */
s16 func_00218480(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk22;
}

s32 func_00218490(void* object)
{
    return 0;
}

s32 func_002184A0(void* object)
{
    return 0;
}

s32 func_002184B0(void* object)
{
    return 0;
}

void func_002184C0(void* object)
{
}

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_002184D0(void* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002184E0);

/** Return the word at receiver offset 0x4. */
u32 func_00218510(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218520);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218570);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002185C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218610);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002186A0);

/** Return the key span between the first and last entries. */
float func_00218700(void* object)
{
    const FloatKeyScanOwner_text_0020D730_10* receiver = static_cast<const FloatKeyScanOwner_text_0020D730_10*>(object);
    s32 count = receiver->count20;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_0020D730_10* entries = receiver->entries;
    const FloatKeyScanEntry_text_0020D730_10* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_00218750(void* object, float key)
{
    FloatKeyScanOwner_text_0020D730_10* receiver = static_cast<FloatKeyScanOwner_text_0020D730_10*>(object);
    s16 count = receiver->count20;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002187A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002187F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218860);

void* func_00218910(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218920);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218990);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218A00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218A90);

/** Return the key span between the first and last entries. */
float func_00218AF0(void* object)
{
    const FloatKeyScanOwner_text_0020D730_08* receiver = static_cast<const FloatKeyScanOwner_text_0020D730_08*>(object);
    s32 count = receiver->count18;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_0020D730_08* entries = receiver->entries;
    const FloatKeyScanEntry_text_0020D730_08* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_00218B40(void* object, float key)
{
    FloatKeyScanOwner_text_0020D730_08* receiver = static_cast<FloatKeyScanOwner_text_0020D730_08*>(object);
    s16 count = receiver->count18;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218B90);

void func_00218BC0(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218BD0);

s32 func_00218C00(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218C10);

s32 func_00218C40(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218C50);

s32 func_00218C80(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218C90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218CE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218D50);

void func_00218D80(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218D90);

s32 func_00218DC0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218DD0);

s32 func_00218E00(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218E10);

s32 func_00218E40(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218E50);

void* func_00218F00(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218F10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00218F80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219010);

/** Return the key span between the first and last entries. */
float func_00219070(void* object)
{
    const FloatKeyScanOwner_text_0020D730_20* receiver = static_cast<const FloatKeyScanOwner_text_0020D730_20*>(object);
    s32 count = receiver->count38;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_0020D730_20* entries = receiver->entries;
    const FloatKeyScanEntry_text_0020D730_20* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_002190C0(void* object, float key)
{
    FloatKeyScanOwner_text_0020D730_20* receiver = static_cast<FloatKeyScanOwner_text_0020D730_20*>(object);
    s16 count = receiver->count38;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219110);

void func_00219140(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219150);

s32 func_00219180(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219190);

s32 func_002191C0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002191D0);

s32 func_00219200(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219210);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219260);

void* func_00219310(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219320);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219390);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219400);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219470);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219530);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002195B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_002196D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219770);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219830);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219C50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219CE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219E20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219E80);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_00219F00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A000);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A090);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A120);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A180);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A280);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A2E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A360);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A460);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A4F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A590);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A5E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021A980);

/** Set the low packed mode at 0x42 and record whether either mode equals four. */
void func_0021A9E0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Set the low packed mode at 0x52 and record whether either mode equals four. */
void func_0021AA40(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.lowMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Set the low packed mode at 0x22 and record whether either mode equals four. */
void func_0021AAA0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.lowMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AB00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AB80);

void func_0021AC00(void* object)
{
}

void func_0021AC10(void* object)
{
}

void func_0021AC20(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AC30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021ACC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AD60);

/** Set the high packed mode at 0x22 and record whether either mode equals four. */
void func_0021ADC0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.highMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/** Return the word at receiver offset 0x10. */
u32 func_0021AE20(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk10;
}

/** Return the signed halfword at receiver offset 0x18. */
s16 func_0021AE30(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk18;
}

/** Return the signed halfword at receiver offset 0x1A. */
s16 func_0021AE40(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk1a;
}

s32 func_0021AE50(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AE60);

s32 func_0021AE90(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AEA0);

s32 func_0021AED0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AEE0);

void func_0021AF10(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AF20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AF50);

void func_0021AFB0(void* object)
{
    FourWordClearOwnertext_0020D730* receiver = (FourWordClearOwnertext_0020D730*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021AFD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B030);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B120);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B170);

/** Return the word at receiver offset 0x4. */
u32 func_0021B210(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B220);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B2B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B360);

/** Set the high packed mode at 0x52 and record whether either mode equals four. */
void func_0021B3B0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.highMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Return the word at receiver offset 0x40. */
u32 func_0021B410(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk40;
}

/** Return the signed halfword at receiver offset 0x48. */
s16 func_0021B420(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk48;
}

/** Return the signed halfword at receiver offset 0x4A. */
s16 func_0021B430(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk4a;
}

s32 func_0021B440(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B450);

s32 func_0021B480(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B490);

s32 func_0021B4C0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B4D0);

void func_0021B500(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B510);

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_0021B540(void* object, float key)
{
    FloatKeyScanOwner_text_0020D730_30* receiver = static_cast<FloatKeyScanOwner_text_0020D730_30*>(object);
    s16 count = receiver->count48;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

void func_0021B590(void* object)
{
    FourWordClearOwnertext_0020D730* receiver = (FourWordClearOwnertext_0020D730*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B5B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B600);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B670);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B6C0);

/** Return the word at receiver offset 0x4. */
u32 func_0021B760(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B770);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B850);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021B9B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BA40);

/** Set the high packed mode at 0x42 and record whether either mode equals four. */
void func_0021BAF0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Return the word at receiver offset 0x30. */
u32 func_0021BB50(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk30;
}

/** Return the signed halfword at receiver offset 0x38. */
s16 func_0021BB60(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk38;
}

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_0021BB70(const void* object)
{
    const HalfwordGetterOwnertext_0020D730* receiver = (const HalfwordGetterOwnertext_0020D730*)object;
    return receiver->unk3a;
}

s32 func_0021BB80(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BB90);

s32 func_0021BBC0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BBD0);

s32 func_0021BC00(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BC10);

void func_0021BC40(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BC50);

void func_0021BC80(void* object)
{
    FourWordClearOwnertext_0020D730* receiver = (FourWordClearOwnertext_0020D730*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BCA0);

/** Return the word at receiver offset 0x4. */
u32 func_0021BCF0(const void* object)
{
    const WordGetterOwnertext_0020D730* receiver = (const WordGetterOwnertext_0020D730*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BD00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BD30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BD60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BD90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BDC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021BEA0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C000);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C030);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C060);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C090);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C0C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C150);

/** Return the key span between the first and last entries. */
float func_0021C1B0(void* object)
{
    const FloatKeyScanOwner_text_0020D730_20* receiver = static_cast<const FloatKeyScanOwner_text_0020D730_20*>(object);
    s32 count = receiver->count38;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_0020D730_20* entries = receiver->entries;
    const FloatKeyScanEntry_text_0020D730_20* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_0021C200(void* object, float key)
{
    FloatKeyScanOwner_text_0020D730_20* receiver = static_cast<FloatKeyScanOwner_text_0020D730_20*>(object);
    s16 count = receiver->count38;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key00)
        {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C250);

void* func_0021C2A0(void* value)
{
    return value;
}

void* func_0021C2B0(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C2C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C2D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C2E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C2F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C300);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C310);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021C440);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021CA70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021CB70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021CBF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021CC20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021CF80);

s32 func_0021D170(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021D180);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_0020D730", func_0021D680);

}
