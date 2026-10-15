#include "include_asm.h"
#include "overlays/lib/text_004AB8B0.h"

extern "C" {

extern void func_004B0B20(void* object);
extern void func_004B2870(void* object);
extern void* D_001B6678;
extern void* D_001B666C;
extern void* D_001B6664;
extern void func_004B0820(void* object);
extern void func_004B0FF0(void* owner, void* object);
extern void func_004ACAF0(void* object);
extern void func_004B2B80(void* owner, void* object);
extern void func_004B2AE0(void* object);
extern void func_004B2B30(void* owner, void* object);

typedef struct HalfwordGetterOwnertext_004AB8B0
{
    u8 unk00[0x18];
    s16 unk18;
    s16 unk1a;
    u8 unk1c[0x4];
    s16 unk20;
    s16 unk22;
    u8 unk24[0x14];
    s16 unk38;
    s16 unk3a;
} HalfwordGetterOwnertext_004AB8B0;



typedef struct WordGetterOwnertext_004AB8B0
{
    u8 unk00[0x4];
    u32 unk04;
    u8 unk08[0x8];
    u32 unk10;
    u8 unk14[0x4];
    u32 unk18;
    u8 unk1c[0x14];
    u32 unk30;
} WordGetterOwnertext_004AB8B0;


typedef struct FourWordClearOwnertext_004AB8B0 { u32 words[4]; } FourWordClearOwnertext_004AB8B0;

typedef struct ClearForwardWordOwnertext_004AB8B0
{
    u8 unk00[0x48];
    u32 unk48;
    u32 unk4c;
} ClearForwardWordOwnertext_004AB8B0;

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
    u8 unk2c[0x16];
    PackedModePair at42;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_004AB8B0_08
{
    float key00;
    u8 unk04[0x4];
} FloatKeyScanEntry_text_004AB8B0_08;

typedef struct FloatKeyScanOwner_text_004AB8B0_08
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004AB8B0_08* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x16];
    s16 count38;
} FloatKeyScanOwner_text_004AB8B0_08;

typedef struct FloatKeyScanEntry_text_004AB8B0_10
{
    float key00;
    u8 unk04[0x8];
    float key0c;
} FloatKeyScanEntry_text_004AB8B0_10;

typedef struct FloatDiffEntry_text_004AB8B0_10
{
    u32 unk00;
    float value;
    u8 unk08[8];
} FloatDiffEntry_text_004AB8B0_10;

typedef struct FloatDiffEntry_text_004AB8B0_08
{
    u32 unk00;
    float value;
} FloatDiffEntry_text_004AB8B0_08;

typedef struct FloatKeyScanOwner_text_004AB8B0_10
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004AB8B0_10* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x16];
    s16 count38;
} FloatKeyScanOwner_text_004AB8B0_10;

typedef struct FloatKeyScanEntry_text_004AB8B0_20
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x10];
} FloatKeyScanEntry_text_004AB8B0_20;

typedef struct FloatKeyScanOwner_text_004AB8B0_20
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004AB8B0_20* entries;
    u8 unk08[0x10];
    s16 count18;
    u8 unk1a[0x6];
    s16 count20;
    u8 unk22[0x16];
    s16 count38;
} FloatKeyScanOwner_text_004AB8B0_20;

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AB8B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABA60);

s32 func_004ABAA0(void* object)
{
    return 99;
}

void func_004ABAB0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABAC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABD10);

void func_004ABD30(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABD40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ABFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC320);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC3A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC3B0);

void func_004AC410(void* object)
{
    u8* bytes = (u8*)object;
    *(u16*)(bytes + 0x4) = 0;
    *(u16*)(bytes + 0x6) = 0;
    *(u32*)(bytes + 0x8) = 0;
    *(u32*)(bytes + 0xC) = 0;
}

void func_004AC430(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC4C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC5A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AC800);

/** Set the low packed mode at 0x42 and record whether either mode equals four. */
void func_004AC850(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Set the high packed mode at 0x42 and record whether either mode equals four. */
void func_004AC8B0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Return the word at receiver offset 0x30. */
u32 func_004AC910(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk30;
}

/** Return the signed halfword at receiver offset 0x38. */
s16 func_004AC920(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk38;
}

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_004AC930(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk3a;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004AC940(void* object, float key)
{
    FloatKeyScanOwner_text_004AB8B0_20* receiver = static_cast<FloatKeyScanOwner_text_004AB8B0_20*>(object);
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

void func_004AC990(void* object)
{
    FourWordClearOwnertext_004AB8B0* receiver = (FourWordClearOwnertext_004AB8B0*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

/** Return the key span between the first and last entries. */
float func_004AC9B0(void* object)
{
    const FloatKeyScanOwner_text_004AB8B0_20* receiver = static_cast<const FloatKeyScanOwner_text_004AB8B0_20*>(object);
    s32 count = receiver->count38;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_004AB8B0_20* entries = receiver->entries;
    const FloatKeyScanEntry_text_004AB8B0_20* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACA00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACA50);

/** Return the word at receiver offset 0x4. */
u32 func_004ACAE0(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACAF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACB40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACBA0);

void func_004ACBD0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACBE0);

s32 func_004ACC10(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACC20);

s32 func_004ACC50(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACC60);

s32 func_004ACC90(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACCA0);

void* func_004ACD50(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACD60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACDC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACEC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ACF50);

typedef struct LibResetWrapperState004ACFF0
{
    u8 unk00[0x50];
    u32 unk50;
    u8 unk54[4];
    u32 unk58;
} LibResetWrapperState004ACFF0;

void func_004ACFF0(void* object)
{
    LibResetWrapperState004ACFF0* receiver = (LibResetWrapperState004ACFF0*)object;
    receiver->unk58 = 0;
    receiver->unk50 = 0;
    func_004B04C0(object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD010);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD0F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD1C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD210);

void func_004AD2B0(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0x54);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD2C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD320);

void func_004AD380(void* object)
{
    func_004B0820(object);
    func_004B0FF0(D_001B6678, object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD3B0);

/** Set the low packed mode at 0x42 and record whether either mode equals four. */
void func_004AD410(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.lowMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD470);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD6B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD770);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AD860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004ADC60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AE5A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AE7E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AEFE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AEFF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF6A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF6D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF7D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF840);

void func_004AF8A0(void* object)
{
    ((ClearForwardWordOwnertext_004AB8B0*)object)->unk4c = 0;
    func_004B0B20(object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AF8C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AFCE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AFD40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AFDA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AFE00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AFE60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AFF20);

void func_004AFF60(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0x50);
}

void func_004AFF70(const void* object, float* output)
{
    const FloatKeyScanOwner_text_004AB8B0_10* receiver = (const FloatKeyScanOwner_text_004AB8B0_10*)object;
    FloatDiffEntry_text_004AB8B0_10* entries = (FloatDiffEntry_text_004AB8B0_10*)receiver->entries;
    if (entries != 0)
    {
        *output = entries[receiver->count20 - 1].value - entries[0].value;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004AFFA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B00A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B02F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B04C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0550);

/** Set the high packed mode at 0x42 and record whether either mode equals four. */
void func_004B05A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Return the word at receiver offset 0x30. */
u32 func_004B0600(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk30;
}

/** Return the signed halfword at receiver offset 0x38. */
s16 func_004B0610(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk38;
}

/** Return the signed halfword at receiver offset 0x3A. */
s16 func_004B0620(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk3a;
}

s32 func_004B0630(void* object)
{
    return 0;
}

s32 func_004B0640(void* object)
{
    return 0;
}

s32 func_004B0650(void* object)
{
    return 0;
}

void func_004B0660(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B0670(void* object, float key)
{
    FloatKeyScanOwner_text_004AB8B0_20* receiver = static_cast<FloatKeyScanOwner_text_004AB8B0_20*>(object);
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

void func_004B06C0(void* object)
{
    FourWordClearOwnertext_004AB8B0* receiver = (FourWordClearOwnertext_004AB8B0*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

/** Return the key span between the first and last entries. */
float func_004B06E0(void* object)
{
    const FloatKeyScanOwner_text_004AB8B0_20* receiver = static_cast<const FloatKeyScanOwner_text_004AB8B0_20*>(object);
    s32 count = receiver->count38;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_004AB8B0_20* entries = receiver->entries;
    const FloatKeyScanEntry_text_004AB8B0_20* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0780);

/** Return the word at receiver offset 0x4. */
u32 func_004B0810(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0820);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0950);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0AB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0B20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0BB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0C50);

/** Set the low packed mode at 0x2A and record whether either mode equals four. */
void func_004B0CA0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at2a.lowMode = mode;
    receiver->at2a.hasModeFour = receiver->at2a.lowMode == 4 || receiver->at2a.highMode == 4;
}

/** Set the high packed mode at 0x2A and record whether either mode equals four. */
void func_004B0D00(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at2a.highMode = mode;
    receiver->at2a.hasModeFour = receiver->at2a.lowMode == 4 || receiver->at2a.highMode == 4;
}

/** Return the word at receiver offset 0x18. */
u32 func_004B0D60(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk18;
}

/** Return the signed halfword at receiver offset 0x20. */
s16 func_004B0D70(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk20;
}

/** Return the signed halfword at receiver offset 0x22. */
s16 func_004B0D80(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk22;
}

s32 func_004B0D90(void* object)
{
    return 0;
}

s32 func_004B0DA0(void* object)
{
    return 0;
}

s32 func_004B0DB0(void* object)
{
    return 0;
}

void func_004B0DC0(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B0DD0(void* object, float key)
{
    FloatKeyScanOwner_text_004AB8B0_10* receiver = static_cast<FloatKeyScanOwner_text_004AB8B0_10*>(object);
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

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_004B0E20(void* object)
{
    return 0.0f;
}

/** Return the key span between the first and last entries. */
float func_004B0E30(void* object)
{
    const FloatKeyScanOwner_text_004AB8B0_10* receiver = static_cast<const FloatKeyScanOwner_text_004AB8B0_10*>(object);
    s32 count = receiver->count20;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_004AB8B0_10* entries = receiver->entries;
    const FloatKeyScanEntry_text_004AB8B0_10* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0E80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0EB0);

/** Return the word at receiver offset 0x4. */
u32 func_004B0F40(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0FA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B0FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B10A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1100);

void* func_004B11B0(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B11C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1400);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B14C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B14F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1550);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1580);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B15B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B15E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1610);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B16C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1720);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1790);

typedef struct LibResetWrapperState004B1800
{
    u8 unk00[0xB0];
    u32 unkB0;
    u32 unkB4;
} LibResetWrapperState004B1800;

void func_004B1800(void* object)
{
    LibResetWrapperState004B1800* receiver = (LibResetWrapperState004B1800*)object;
    receiver->unkB0 = 0;
    receiver->unkB4 = 0;
    func_004AC770(object);
}

void func_004B1820(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0xB8);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1830);

void func_004B1890(void* object)
{
    func_004ACAF0(object);
    func_004B2B80(D_001B666C, object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B18C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B1A50);

void func_004B24A0(void* object, float value1, float value2)
{
    func_004B2EB0(object, &value2, value1);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B24C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B24E0);

void func_004B2500(void* object, float value1, float value2)
{
    func_004B3120(object, &value2, value1);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2520);

void func_004B2580(void* object)
{
    func_004B2AE0(object);
    func_004B2B30(D_001B6664, object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B25B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2630);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2690);

void func_004B2700(void* object)
{
    ((ClearForwardWordOwnertext_004AB8B0*)object)->unk48 = 0;
    func_004B2870(object);
}

void func_004B2720(const void* object, float* output)
{
    const FloatKeyScanOwner_text_004AB8B0_10* receiver = (const FloatKeyScanOwner_text_004AB8B0_10*)object;
    FloatDiffEntry_text_004AB8B0_08* entries = (FloatDiffEntry_text_004AB8B0_08*)receiver->entries;
    if (entries != 0)
    {
        *output = entries[receiver->count18 - 1].value - entries[0].value;
    }
}

void func_004B2750(const void* object, float* value)
{
    *value = *(const float*)((const u8*)object + 0x4C);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2760);

void func_004B27E0(void* object)
{
    u8* bytes = (u8*)object;
    *(u16*)(bytes + 0x10) = 0;
    *(u16*)(bytes + 0x12) = 0;
    *(u32*)(bytes + 0x14) = 0;
    *(u32*)(bytes + 0x18) = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2800);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2870);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2900);

/** Set the low packed mode at 0x22 and record whether either mode equals four. */
void func_004B29A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.lowMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/** Set the high packed mode at 0x22 and record whether either mode equals four. */
void func_004B2A00(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at22.highMode = mode;
    receiver->at22.hasModeFour = receiver->at22.lowMode == 4 || receiver->at22.highMode == 4;
}

/** Return the word at receiver offset 0x10. */
u32 func_004B2A60(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk10;
}

/** Return the signed halfword at receiver offset 0x18. */
s16 func_004B2A70(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk18;
}

/** Return the signed halfword at receiver offset 0x1A. */
s16 func_004B2A80(const void* object)
{
    const HalfwordGetterOwnertext_004AB8B0* receiver = (const HalfwordGetterOwnertext_004AB8B0*)object;
    return receiver->unk1a;
}

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_004B2A90(void* object)
{
    return 0.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2AA0);

/** Return the word at receiver offset 0x4. */
u32 func_004B2AD0(const void* object)
{
    const WordGetterOwnertext_004AB8B0* receiver = (const WordGetterOwnertext_004AB8B0*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2AE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2B80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2BD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2C60);

/** Return the key span between the first and last entries. */
float func_004B2CC0(void* object)
{
    const FloatKeyScanOwner_text_004AB8B0_08* receiver = static_cast<const FloatKeyScanOwner_text_004AB8B0_08*>(object);
    s32 count = receiver->count18;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_004AB8B0_08* entries = receiver->entries;
    const FloatKeyScanEntry_text_004AB8B0_08* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004B2D10(void* object, float key)
{
    FloatKeyScanOwner_text_004AB8B0_08* receiver = static_cast<FloatKeyScanOwner_text_004AB8B0_08*>(object);
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

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2D60);

void func_004B2D90(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2DA0);

s32 func_004B2DD0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2DE0);

s32 func_004B2E10(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2E20);

s32 func_004B2E50(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2EB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2F10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B2F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3120);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B31B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B35A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3680);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B37E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B38C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3A00);

void func_004B3A70(void* object, float value1, float value2)
{
    func_004B3C30(object, &value2, value1);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3A90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3B20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3BA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3C30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3CB0);

void func_004B3D40(void* object)
{
}

void func_004B3D50(void* object)
{
}

s32 func_004B3D60(void* object)
{
    return 0;
}

s32 func_004B3D70(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3D80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B3DE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B43C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B4550);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B46E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004AB8B0", func_004B4840);

}
