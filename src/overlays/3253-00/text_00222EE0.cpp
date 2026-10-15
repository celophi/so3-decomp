#include "include_asm.h"
#include "overlays/3253-00/text_00222EE0.h"

extern "C" void func_494D80(void* object);
extern "C" u8 D_178C60[];
extern "C" u8 D_1799E0[];
extern "C" u8 D_178930[];
extern "C" void func_4781A0(void* object);
extern "C" void func_4EABF0(void* object);
extern "C" void func_474E70(void* embedded, void* adjusted);

typedef struct HalfwordGetterOwnertext_00222EE0
{
    u8 unk00[0x38];
    s16 unk38;
    u8 unk3a[0xE];
    s16 unk48;
} HalfwordGetterOwnertext_00222EE0;



typedef struct ByteSetterOwnertext_00222EE0
{
    u8 unk00[0x41];
    u8 unk41;
} ByteSetterOwnertext_00222EE0;



typedef struct WordGetterOwnertext_00222EE0
{
    u8 unk00[0x4];
    u32 unk04;
    u8 unk08[0x28];
    u32 unk30;
    u8 unk34[0xC];
    u32 unk40;
} WordGetterOwnertext_00222EE0;


/** First four words of the receiver cleared by func_00223320. */
typedef struct BattleFourWords10
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
} BattleFourWords10;

typedef struct FourWordClearOwnertext_00222EE0 { u32 words[4]; } FourWordClearOwnertext_00222EE0;

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x42];
    PackedModePair at42;
    u8 unk44[0xE];
    PackedModePair at52;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_00222EE0_20
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x10];
} FloatKeyScanEntry_text_00222EE0_20;

typedef struct FloatKeyScanOwner_text_00222EE0_20
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_00222EE0_20* entries;
    u8 unk08[0x30];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_00222EE0_20;

typedef struct FloatKeyScanEntry_text_00222EE0_30
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x20];
} FloatKeyScanEntry_text_00222EE0_30;

typedef struct FloatKeyScanOwner_text_00222EE0_30
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_00222EE0_30* entries;
    u8 unk08[0x30];
    s16 count38;
    u8 unk3a[0xE];
    s16 count48;
} FloatKeyScanOwner_text_00222EE0_30;

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00222EE0);

/** Return the word at receiver offset 0x4. */
u32 func_00222F80(const void* object)
{
    const WordGetterOwnertext_00222EE0* receiver = static_cast<const WordGetterOwnertext_00222EE0*>(object);
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00222F90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223020);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223100);

/** Set the high packed mode at 0x52 and record whether either mode equals four. */
void func_00223150(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.highMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Return the word at receiver offset 0x40. */
u32 func_002231B0(const void* object)
{
    const WordGetterOwnertext_00222EE0* receiver = static_cast<const WordGetterOwnertext_00222EE0*>(object);
    return receiver->unk40;
}

/** Return the signed halfword at receiver offset 0x48. */
s16 func_002231C0(const void* object)
{
    const HalfwordGetterOwnertext_00222EE0* receiver = static_cast<const HalfwordGetterOwnertext_00222EE0*>(object);
    return receiver->unk48;
}

s32 func_002231D0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002231E0);

s32 func_00223210(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223220);

s32 func_00223250(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223260);

void func_00223290(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002232A0);

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_002232D0(void* object, float key)
{
    FloatKeyScanOwner_text_00222EE0_30* receiver = static_cast<FloatKeyScanOwner_text_00222EE0_30*>(object);
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

void func_00223320(void* object)
{
    BattleFourWords10* state = (BattleFourWords10*)object;
    state->unk00 = 0;
    state->unk04 = 0;
    state->unk08 = 0;
    state->unk0c = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223340);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223390);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223400);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223450);

/** Return the word at receiver offset 0x4. */
u32 func_002234F0(const void* object)
{
    const WordGetterOwnertext_00222EE0* receiver = static_cast<const WordGetterOwnertext_00222EE0*>(object);
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223500);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002235E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223740);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002237D0);

/** Set the high packed mode at 0x42 and record whether either mode equals four. */
void func_002238A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at42.highMode = mode;
    receiver->at42.hasModeFour = receiver->at42.lowMode == 4 || receiver->at42.highMode == 4;
}

/** Return the word at receiver offset 0x30. */
u32 func_00223900(const void* object)
{
    const WordGetterOwnertext_00222EE0* receiver = static_cast<const WordGetterOwnertext_00222EE0*>(object);
    return receiver->unk30;
}

/** Return the signed halfword at receiver offset 0x38. */
s16 func_00223910(const void* object)
{
    const HalfwordGetterOwnertext_00222EE0* receiver = static_cast<const HalfwordGetterOwnertext_00222EE0*>(object);
    return receiver->unk38;
}

s32 func_00223920(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223930);

s32 func_00223960(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223970);

s32 func_002239A0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002239B0);

void func_002239E0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002239F0);

void func_00223A20(void* object)
{
    FourWordClearOwnertext_00222EE0* receiver = (FourWordClearOwnertext_00222EE0*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223A40);

/** Return the word at receiver offset 0x4. */
u32 func_00223A90(const void* object)
{
    const WordGetterOwnertext_00222EE0* receiver = static_cast<const WordGetterOwnertext_00222EE0*>(object);
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223AA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223AD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223B00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223B30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223B60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223C40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223DA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223DD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223E00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223E30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223E60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223EF0);

/** Return the key span between the first and last entries. */
float func_00223F50(void* object)
{
    const FloatKeyScanOwner_text_00222EE0_20* receiver = static_cast<const FloatKeyScanOwner_text_00222EE0_20*>(object);
    s32 count = receiver->count38;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_00222EE0_20* entries = receiver->entries;
    const FloatKeyScanEntry_text_00222EE0_20* lastEntry = entries + --count;
    float first = entries[0].key00;
    float last = lastEntry->key00;
    return last - first;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_00223FA0(void* object, float key)
{
    FloatKeyScanOwner_text_00222EE0_20* receiver = static_cast<FloatKeyScanOwner_text_00222EE0_20*>(object);
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

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00223FF0);

void* func_00224040(void* value)
{
    return value;
}

void* func_00224050(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00224060);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00224070);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00224080);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00224090);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002240A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002240B0);

s32 func_00224140(void* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00224150);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00224180);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002244B0);

s32 func_002246A0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002246B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00224BC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00224D90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00225050);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00225180);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002255F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00225740);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002258C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002262E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00226550);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002269E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00226E20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002274D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002276E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002277D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00227970);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00227B20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00227B40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00227C80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00227F60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002280D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00228120);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00228500);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00228670);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00228750);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00228960);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00229300);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002298E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00229CA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00229F70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022A420);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022A5D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022AA60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022AC10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022AD80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022AE10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022AEC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022B030);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022B1F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022B320);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022B590);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022B650);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022B7C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022B970);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BA40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BB40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BC40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BCD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BD40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BDB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BE40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BEB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BF20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022BF90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022C0B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022C120);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022C3D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022C440);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022C4B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022C600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022C690);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022C740);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022CE50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022CEC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022CF90);

void* func_0022D170(void* receiver)
{
    func_4781A0(receiver);
    *(void**)receiver = D_178930;
    ((u8*)receiver)[0x3C] = 15;
    return receiver;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D1B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D210);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D270);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D2D0);

extern "C" void* func_0022D330(void* object)
{
    func_494D80(object);
    *(void**)object = D_178C60;
    *(u32*)((u8*)object + 0x44) = 0;
    *((u8*)object + 0x3C) = 6;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D370);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D3E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D440);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D4B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D510);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D570);

extern "C" void* func_0022D5C0(void* object)
{
    func_494D80(object);
    *(void**)object = D_1799E0;
    *(u32*)((u8*)object + 0x44) = 0;
    *((u8*)object + 0x3C) = 5;
    return object;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D690);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D730);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022D8C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022DBC0);

/** Store the byte at receiver offset 0x41. */
void func_0022E000(void* object, u8 value)
{
    ByteSetterOwnertext_00222EE0* receiver = static_cast<ByteSetterOwnertext_00222EE0*>(object);
    receiver->unk41 = value;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E010);

const float* func_0022E030(const void* object)
{
    return (const float*)((const u8*)object + 0x20);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E040);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E070);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E080);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E090);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E0B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E130);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E250);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E510);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E710);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E840);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022E940);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022EA10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022EB40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022EFE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022F1F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022F300);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022F450);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022F5B0);

void func_0022F760(void* object)
{
    func_4EABF0(object);
}

struct N54Owner64_00222EE0 { u8 pad00[0x64]; u8 active; };

void func_0022F780(N54Owner64_00222EE0* object)
{
    object->active = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0x90;
    }
    func_474E70((u8*)object + 0xB0, adjusted);
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022F7C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022F830);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022F970);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022FC10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022FCA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_0022FEE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00230050);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00230630);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00230660);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00230720);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00230880);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00230900);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00230D00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002316A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00231950);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00231AE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00231B30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00231EB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00232320);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00232520);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_002326E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00232A70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00232AA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_00222EE0", func_00232E00);
