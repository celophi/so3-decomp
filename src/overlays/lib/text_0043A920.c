#include "include_asm.h"
#include "overlays/lib/text_0043A920.h"

extern void* __vt__14LibClass171E80;
extern u8 D_00173A28[];
extern u8 D_00173F48[];
extern u8 D_00173F38[];
extern void func_004447E0(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8);

typedef struct ConstantByteSetterOwnertext_0043A920
{
    u8 unk00[0x60];
    u8 unk60;
} ConstantByteSetterOwnertext_0043A920;

typedef struct WordNonzeroOwnertext_0043A920
{
    u8 unk00[0x14];
    u32 unk14;
} WordNonzeroOwnertext_0043A920;

typedef struct ByteClearOwnertext_0043A920
{
    u8 unk00[0x480];
    u8 unk480;
} ByteClearOwnertext_0043A920;



typedef struct HalfwordGetterOwnertext_0043A920
{
    u8 unk00[0x48];
    s16 unk48;
    s16 unk4a;
} HalfwordGetterOwnertext_0043A920;



typedef struct ByteGetterOwnertext_0043A920
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e[0x8];
    u8 unk56;
} ByteGetterOwnertext_0043A920;



typedef struct ByteSetterOwnertext_0043A920
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u8 unk50[0x4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} ByteSetterOwnertext_0043A920;



typedef struct WordSetterOwnertext_0043A920
{
    u8 unk00[0x48];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x64];
    u32 unkb8;
    u32 unkbc;
} WordSetterOwnertext_0043A920;



typedef struct WordGetterOwnertext_0043A920
{
    u8 unk00[0x4];
    u32 unk04;
    u8 unk08[0x4];
    u32 unk0c;
    u32 unk10;
    u8 unk14[0x8];
    u32 unk1c;
    u8 unk20[0x20];
    u32 unk40;
    u8 unk44[0x4];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x64];
    u32 unkb8;
    u32 unkbc;
} WordGetterOwnertext_0043A920;


typedef struct LibFloatFieldOwner0043A920
{
    u8 unk00[0x28];
    float unk28;
    u8 unk2c[4];
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
} LibFloatFieldOwner0043A920;

s32 func_0043A920(void* object)
{
    return -1;
}

typedef struct QuadwordSetter230Ownertext_0043A920 { u8 unk00[0x230]; unsigned __int128 value230; u8 unk240[0x241]; u8 flag481; } QuadwordSetter230Ownertext_0043A920;
typedef struct QuadwordSetter250Ownertext_0043A920 { u8 unk00[0x250]; unsigned __int128 value250; u8 unk260[0x222]; u8 flag482; } QuadwordSetter250Ownertext_0043A920;
typedef struct QuadwordSetter2B0Ownertext_0043A920 { u8 unk00[0x2B0]; unsigned __int128 value2B0; u8 unk2C0[0x1C5]; u8 flag485; } QuadwordSetter2B0Ownertext_0043A920;

typedef struct FourWordClearOwnertext_0043A920 { u32 words[4]; } FourWordClearOwnertext_0043A920;

typedef struct FlagFloat340Ownertext_0043A920 { u8 pad00[0x340]; float xy[2]; u8 pad348[0x8]; float zw[2]; u8 pad358[0x132]; u8 flag48A; } FlagFloat340Ownertext_0043A920;
typedef struct FlagFloat300Ownertext_0043A920 { u8 pad00[0x300]; float xy[2]; u8 pad308[0x8]; float zw[2]; u8 pad318[0x170]; u8 flag488; } FlagFloat300Ownertext_0043A920;
typedef struct FlagFloat2C0Ownertext_0043A920 { u8 pad00[0x2C0]; float xy[2]; u8 pad2C8[0x8]; float zw[2]; u8 pad2D8[0x1AE]; u8 flag486; } FlagFloat2C0Ownertext_0043A920;

typedef struct FlagFloat230Receivertext_0043A920 { u8 pad00[0x230]; float x230; u8 pad234[4]; float z238; u8 pad23C[4]; float y240; u8 pad244[0x23D]; u8 flag481; } FlagFloat230Receivertext_0043A920;
typedef struct FlagFloat220Receivertext_0043A920 { u8 pad00[0x220]; float x220; float y224; u8 pad228[0x1D0]; float z3F8; u8 pad3FC[0x84]; u8 flag480; } FlagFloat220Receivertext_0043A920;

typedef struct ClearFlagQuadwordOwnertext_0043A920 { u8 pad00[0x3A0]; unsigned __int128 value3A0; u8 pad3B0[0xDF]; u8 flag48F; } ClearFlagQuadwordOwnertext_0043A920;

typedef struct ClearFlagSlot3A0Ownertext_0043A920 { u8 pad00[0x3A0]; unsigned __int128 value3A0; u8 pad3B0[0xDF]; u8 flag48F; } ClearFlagSlot3A0Ownertext_0043A920;
typedef struct ClearFlagSlot380Ownertext_0043A920 { u8 pad00[0x380]; unsigned __int128 value380; u8 pad390[0xFE]; u8 flag48E; } ClearFlagSlot380Ownertext_0043A920;
typedef struct ClearFlagSlot360Ownertext_0043A920 { u8 pad00[0x360]; unsigned __int128 value360; u8 pad370[0x11B]; u8 flag48B; } ClearFlagSlot360Ownertext_0043A920;
typedef struct ClearFlagSlot320Ownertext_0043A920 { u8 pad00[0x320]; unsigned __int128 value320; u8 pad330[0x159]; u8 flag489; } ClearFlagSlot320Ownertext_0043A920;
typedef struct ClearFlagSlot2E0Ownertext_0043A920 { u8 pad00[0x2E0]; unsigned __int128 value2E0; u8 pad2F0[0x197]; u8 flag487; } ClearFlagSlot2E0Ownertext_0043A920;
typedef struct ClearFlagSlot2B0Ownertext_0043A920 { u8 pad00[0x2B0]; unsigned __int128 value2B0; u8 pad2C0[0x1C5]; u8 flag485; } ClearFlagSlot2B0Ownertext_0043A920;
typedef struct ClearFlagSlot290Ownertext_0043A920 { u8 pad00[0x290]; unsigned __int128 value290; u8 pad2A0[0x1E4]; u8 flag484; } ClearFlagSlot290Ownertext_0043A920;
typedef struct ClearFlagSlot270Ownertext_0043A920 { u8 pad00[0x270]; unsigned __int128 value270; u8 pad280[0x203]; u8 flag483; } ClearFlagSlot270Ownertext_0043A920;
typedef struct ClearFlagSlot250Ownertext_0043A920 { u8 pad00[0x250]; unsigned __int128 value250; u8 pad260[0x222]; u8 flag482; } ClearFlagSlot250Ownertext_0043A920;
typedef struct ClearFlagSlot230Ownertext_0043A920 { u8 pad00[0x230]; unsigned __int128 value230; u8 pad240[0x241]; u8 flag481; } ClearFlagSlot230Ownertext_0043A920;

typedef struct TwoQuadwordFlag3A0Ownertext_0043A920 { u8 pad00[0x3A0]; unsigned __int128 values[2]; u8 pad3C0[0xCF]; u8 flag48F; } TwoQuadwordFlag3A0Ownertext_0043A920;

typedef struct TwoQuadwordFlag380Ownertext_0043A920 { u8 pad00[0x380]; unsigned __int128 values[2]; u8 pad3A0[0xEE]; u8 flag48E; } TwoQuadwordFlag380Ownertext_0043A920;
typedef struct TwoQuadwordFlag360Ownertext_0043A920 { u8 pad00[0x360]; unsigned __int128 values[2]; u8 pad380[0x10B]; u8 flag48B; } TwoQuadwordFlag360Ownertext_0043A920;
typedef struct TwoQuadwordFlag320Ownertext_0043A920 { u8 pad00[0x320]; unsigned __int128 values[2]; u8 pad340[0x149]; u8 flag489; } TwoQuadwordFlag320Ownertext_0043A920;
typedef struct TwoQuadwordFlag2E0Ownertext_0043A920 { u8 pad00[0x2E0]; unsigned __int128 values[2]; u8 pad300[0x187]; u8 flag487; } TwoQuadwordFlag2E0Ownertext_0043A920;
typedef struct TwoQuadwordFlag290Ownertext_0043A920 { u8 pad00[0x290]; unsigned __int128 values[2]; u8 pad2B0[0x1D4]; u8 flag484; } TwoQuadwordFlag290Ownertext_0043A920;
typedef struct TwoQuadwordFlag270Ownertext_0043A920 { u8 pad00[0x270]; unsigned __int128 values[2]; u8 pad290[0x1F3]; u8 flag483; } TwoQuadwordFlag270Ownertext_0043A920;
typedef struct TwoQuadwordFlag250Ownertext_0043A920 { u8 pad00[0x250]; unsigned __int128 values[2]; u8 pad270[0x212]; u8 flag482; } TwoQuadwordFlag250Ownertext_0043A920;
typedef struct TwoQuadwordFlag230Ownertext_0043A920 { u8 pad00[0x230]; unsigned __int128 values[2]; u8 pad250[0x231]; u8 flag481; } TwoQuadwordFlag230Ownertext_0043A920;

typedef struct ByteSourceStateOwnertext_0043A920 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; const u8* sourceA0; u32 valueA4; } ByteSourceStateOwnertext_0043A920;
typedef struct TwoWordClearArgStateOwnertext_0043A920 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; void* unkA0; void* unkA4; } TwoWordClearArgStateOwnertext_0043A920;
typedef struct FourQuadwordCopyTargetOwnertext_0043A920
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0x30];
    unsigned __int128 values60[4];
} FourQuadwordCopyTargetOwnertext_0043A920;
typedef struct FourQuadwordCopySourceOwnertext_0043A920
{
    u8 pad00[0x150];
    unsigned __int128 values150[4];
} FourQuadwordCopySourceOwnertext_0043A920;
typedef struct TwoIndexTableEntryOwnertext_0043A920
{
    u8 data[0x40];
} TwoIndexTableEntryOwnertext_0043A920;
typedef struct TwoIndexTableAddressOwnertext_0043A920
{
    u8 pad00[0x10];
    s32 count;
    u8 pad14[0xC];
    TwoIndexTableEntryOwnertext_0043A920* entries;
} TwoIndexTableAddressOwnertext_0043A920;
typedef struct SingleIndexTableAddressOwnertext_0043A920
{
    u8 pad00[0x14];
    u8* base14;
} SingleIndexTableAddressOwnertext_0043A920;

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x52];
    PackedModePair at52;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_0043A920_30
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x20];
} FloatKeyScanEntry_text_0043A920_30;

typedef struct FloatKeyScanOwner_text_0043A920_30
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_0043A920_30* entries;
    u8 unk08[0x40];
    s16 count48;
} FloatKeyScanOwner_text_0043A920_30;

void func_0043A930(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x498] = 1;
    *(float*)(bytes + 0x3D8) = first;
    *(float*)(bytes + 0x3D8) = second;
}

void func_0043A950(void* object, float value)
{
    u8* bytes = (u8*)object;
    bytes[0x498] = 0;
    *(float*)(bytes + 0x3D8) = value;
}

void func_0043A960(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x497] = 1;
    *(float*)(bytes + 0x3D0) = first;
    *(float*)(bytes + 0x3D0) = second;
}

void func_0043A980(void* object, float value)
{
    u8* bytes = (u8*)object;
    bytes[0x497] = 0;
    *(float*)(bytes + 0x3D0) = value;
}

void func_0043A990(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x490] = 2;
    *(float*)(bytes + 0x43C) = first;
    *(float*)(bytes + 0x440) = second;
}

typedef struct LibFloat43CByte490
{
    u8 unk00[0x43C];
    float unk43C;
    u8 unk440[0x50];
    u8 unk490;
} LibFloat43CByte490;

/** Set the byte at receiver offset 0x490 and store the float at offset 0x43C. */
void func_0043A9B0(void* object, float value)
{
    LibFloat43CByte490* receiver = (LibFloat43CByte490*)object;
    receiver->unk490 = 1;
    receiver->unk43C = value;
}

void func_0043A9C0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag3A0Ownertext_0043A920* receiver = object;
    receiver->flag48F = 2;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043A9E0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag3A0Ownertext_0043A920* receiver = object;
    receiver->flag48F = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AA00(void* object, const unsigned __int128* value)
{
    ClearFlagQuadwordOwnertext_0043A920* receiver = object;
    receiver->flag48F = 0;
    receiver->value3A0 = *value;
}

void func_0043AA10(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag380Ownertext_0043A920* receiver = object;
    receiver->flag48E = 2;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AA30(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag380Ownertext_0043A920* receiver = object;
    receiver->flag48E = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AA50(void* object, const unsigned __int128* value)
{
    ClearFlagSlot380Ownertext_0043A920* receiver = object;
    receiver->flag48E = 0;
    receiver->value380 = *value;
}

void func_0043AA60(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x48D] = 1;
    *(float*)(bytes + 0x3C8) = first;
    *(float*)(bytes + 0x3CC) = second;
}

void func_0043AA80(void* object, float value)
{
    u8* bytes = (u8*)object;
    bytes[0x48D] = 0;
    *(float*)(bytes + 0x3C8) = value;
}

void func_0043AA90(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x48C] = 1;
    *(float*)(bytes + 0x3C0) = first;
    *(float*)(bytes + 0x3C4) = second;
}

void func_0043AAB0(void* object, float value)
{
    u8* bytes = (u8*)object;
    bytes[0x48C] = 0;
    *(float*)(bytes + 0x3C0) = value;
}

void func_0043AAC0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag360Ownertext_0043A920* receiver = object;
    receiver->flag48B = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AAE0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot360Ownertext_0043A920* receiver = object;
    receiver->flag48B = 0;
    receiver->value360 = *value;
}

void func_0043AAF0(void* object, float x, float y, float z, float w)
{
    FlagFloat340Ownertext_0043A920* receiver = object;
    receiver->flag48A = 1;
    receiver->xy[0] = x;
    receiver->xy[1] = y;
    receiver->zw[0] = z;
    receiver->zw[1] = w;
}

void func_0043AB10(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x48A] = 0;
    *(float*)(bytes + 0x340) = first;
    *(float*)(bytes + 0x344) = second;
}

void func_0043AB20(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag320Ownertext_0043A920* receiver = object;
    receiver->flag489 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AB40(void* object, const unsigned __int128* value)
{
    ClearFlagSlot320Ownertext_0043A920* receiver = object;
    receiver->flag489 = 0;
    receiver->value320 = *value;
}

void func_0043AB50(void* object, float x, float y, float z, float w)
{
    FlagFloat300Ownertext_0043A920* receiver = object;
    receiver->flag488 = 1;
    receiver->xy[0] = x;
    receiver->xy[1] = y;
    receiver->zw[0] = z;
    receiver->zw[1] = w;
}

void func_0043AB70(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x488] = 0;
    *(float*)(bytes + 0x300) = first;
    *(float*)(bytes + 0x304) = second;
}

void func_0043AB80(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag2E0Ownertext_0043A920* receiver = object;
    receiver->flag487 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043ABA0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot2E0Ownertext_0043A920* receiver = object;
    receiver->flag487 = 0;
    receiver->value2E0 = *value;
}

void func_0043ABB0(void* object, float x, float y, float z, float w)
{
    FlagFloat2C0Ownertext_0043A920* receiver = object;
    receiver->flag486 = 1;
    receiver->xy[0] = x;
    receiver->xy[1] = y;
    receiver->zw[0] = z;
    receiver->zw[1] = w;
}

void func_0043ABD0(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x486] = 0;
    *(float*)(bytes + 0x2C0) = first;
    *(float*)(bytes + 0x2C4) = second;
}

void func_0043ABE0(void* object, const unsigned __int128* value)
{
    QuadwordSetter2B0Ownertext_0043A920* receiver = object;
    receiver->flag485 = 1;
    receiver->value2B0 = *value;
}

void func_0043AC00(void* object, const unsigned __int128* value)
{
    ClearFlagSlot2B0Ownertext_0043A920* receiver = object;
    receiver->flag485 = 0;
    receiver->value2B0 = *value;
}

void func_0043AC10(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag290Ownertext_0043A920* receiver = object;
    receiver->flag484 = 2;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AC30(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag290Ownertext_0043A920* receiver = object;
    receiver->flag484 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AC50(void* object, const unsigned __int128* value)
{
    ClearFlagSlot290Ownertext_0043A920* receiver = object;
    receiver->flag484 = 0;
    receiver->value290 = *value;
}

void func_0043AC60(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag270Ownertext_0043A920* receiver = object;
    receiver->flag483 = 2;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043AC80(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag270Ownertext_0043A920* receiver = object;
    receiver->flag483 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043ACA0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot270Ownertext_0043A920* receiver = object;
    receiver->flag483 = 0;
    receiver->value270 = *value;
}

void func_0043ACB0(void* object, const unsigned __int128* value)
{
    QuadwordSetter250Ownertext_0043A920* receiver = object;
    receiver->flag482 = 2;
    receiver->value250 = *value;
}

void func_0043ACD0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag250Ownertext_0043A920* receiver = object;
    receiver->flag482 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043ACF0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot250Ownertext_0043A920* receiver = object;
    receiver->flag482 = 0;
    receiver->value250 = *value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043AD00);

void func_0043AD20(void* object, const unsigned __int128* value)
{
    QuadwordSetter230Ownertext_0043A920* receiver = object;
    receiver->flag481 = 6;
    receiver->value230 = *value;
}

void func_0043AD40(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x481] = 5;
    *(float*)(bytes + 0x230) = first;
    *(float*)(bytes + 0x240) = second;
}

void func_0043AD60(void* object, float x, float y, float z)
{
    FlagFloat230Receivertext_0043A920* receiver = object;
    receiver->flag481 = 4;
    receiver->x230 = x;
    receiver->y240 = y;
    receiver->z238 = z;
}

void func_0043AD80(void* object, float first, float second)
{
    u8* bytes = (u8*)object;
    bytes[0x481] = 3;
    *(float*)(bytes + 0x230) = first;
    *(float*)(bytes + 0x240) = second;
}

void func_0043ADA0(void* object, const unsigned __int128* value)
{
    QuadwordSetter230Ownertext_0043A920* receiver = object;
    receiver->flag481 = 2;
    receiver->value230 = *value;
}

void func_0043ADC0(void* object, const unsigned __int128* first, const unsigned __int128* second)
{
    TwoQuadwordFlag230Ownertext_0043A920* receiver = object;
    receiver->flag481 = 1;
    receiver->values[0] = *first;
    receiver->values[1] = *second;
}

void func_0043ADE0(void* object, const unsigned __int128* value)
{
    ClearFlagSlot230Ownertext_0043A920* receiver = object;
    receiver->flag481 = 0;
    receiver->value230 = *value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043ADF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043AE20);

void func_0043AE80(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 10;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AEA0(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 9;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AEC0(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 8;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AEE0(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 7;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AF00(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 6;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AF20(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 5;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AF40(void* object, float x, float y, float z)
{
    FlagFloat220Receivertext_0043A920* receiver = object;
    receiver->flag480 = 4;
    receiver->x220 = x;
    receiver->y224 = y;
    receiver->z3F8 = z;
}

void func_0043AF60(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 3;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AF80(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 2;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AFA0(void* object, const unsigned __int128* vector, float amount)
{
    u8* bytes = (u8*)object;
    bytes[0x480] = 1;
    *(unsigned __int128*)(bytes + 0x220) = *vector;
    *(float*)(bytes + 0x3F8) = amount;
}

void func_0043AFC0(void* object)
{
    ByteClearOwnertext_0043A920* receiver = object;
    receiver->unk480 = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043AFD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043B600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043B6A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043B700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043B730);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043B840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043BC40);

void func_0043BCD0(void* object)
{
}

void func_0043BCE0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043BCF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043BD00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043BD70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043BEA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043BFE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043C0C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043C570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043C640);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043C7C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043CBF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043CCE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043CF70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043CFD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043D040);

s32 func_0043D0B0(void* object)
{
    return 0;
}

s32 func_0043D0C0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043D0D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043D190);

void func_0043D1F0(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0043A920* receiver = object;
    const FourQuadwordCopySourceOwnertext_0043A920* values = source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0043D220(void* object)
{
}

s32 func_0043D230(void* object)
{
    return 1;
}

typedef struct MappedEntry0043D240
{
    u8 unk00[0x30];
} MappedEntry0043D240;

typedef struct MappedOwner0043D240
{
    u8 unk00[0x14];
    MappedEntry0043D240* entries;
} MappedOwner0043D240;

void* func_0043D240(const void* object, s32 index)
{
    const MappedOwner0043D240* owner = (const MappedOwner0043D240*)object;
    MappedEntry0043D240* item = &owner->entries[index];
    void* result = item;
    if (item != 0)
    {
        result = (u8*)item + 0x30;
    }
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043D270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043D670);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D770(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D780(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0043D790(void* object)
{
    LibFloatFieldOwner0043A920* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0043D7A0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0043D7B0(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D7C0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0043D7D0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0043D7E0(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D7F0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0043D800(void* object)
{
    LibFloatFieldOwner0043A920* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0043D810(void* object)
{
    LibFloatFieldOwner0043A920* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0043D820(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0043D830(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0043D840(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0043D850(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0043D860(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0043D870(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0043D880(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D890(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0043D8A0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D8B0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = object;
    receiver->unk40 = value;
}

void func_0043D8C0(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0043A920* receiver = object;
    receiver->sourceA0 = source;
    receiver->valueA4 = value;
    if (*receiver->sourceA0 == 1)
    {
        receiver->state57 = 1;
    }
    else
    {
        receiver->state57 = 0;
    }
}

void func_0043D900(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0043A920* receiver = object;
    receiver->unkA0 = 0;
    receiver->unkA4 = 0;
    if (enabled)
    {
        receiver->state57 = 1;
    }
    else
    {
        receiver->state57 = 0;
    }
}

/**
 * @brief Store the value at receiver offset 0x38.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D930(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = object;
    receiver->unk38 = value;
}

void func_0043D940(void* object)
{
}

s32 func_0043D950(void* object)
{
    return 0;
}

void func_0043D960(void* object)
{
}

s32 func_0043D970(void* object)
{
    return 0;
}

void* func_0043D980(void* object, s32 index)
{
    SingleIndexTableAddressOwnertext_0043A920* receiver = object;
    return receiver->base14 + index * 48;
}

void* func_0043D9A0(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0043A920* receiver = object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0043D9C0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0043D9D0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0043D9E0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = object;
    return receiver->unk10;
}

s32 func_0043D9F0(void* object)
{
    return 1;
}

s32 func_0043DA00(void* receiver)
{
    WordNonzeroOwnertext_0043A920* object = receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043DA10);

void* func_0043DF70(void* receiver)
{
    *(void**)receiver = &__vt__14LibClass171E80;
    *(void**)receiver = D_00173A28;
    *(void**)receiver = D_00173F48;
    *(void**)receiver = D_00173F38;
    return receiver;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043DFB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043E030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043E0A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043E0D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043E140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043E220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043E2F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0043EA10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004414E0);

float func_00441520(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00441530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00441600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00441660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00441B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00441B50);

void func_00441B80(void* object)
{
}

s32 func_00441B90(void* object)
{
    return 1;
}

/** Store the word at receiver offset 0xB8. */
void func_00441BA0(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = object;
    receiver->unkb8 = value;
}

/** Return the word at receiver offset 0xB8. */
u32 func_00441BB0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = object;
    return receiver->unkb8;
}

/** Store the word at receiver offset 0xBC. */
void func_00441BC0(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = object;
    receiver->unkbc = value;
}

/** Return the word at receiver offset 0xBC. */
u32 func_00441BD0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = object;
    return receiver->unkbc;
}

void func_00441BE0(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8)
{
    u8* state = (u8*)cell;
    state[0x130] = 0;
    state[0x132] = 0;
    state[0x131] = 0;
    state[0x133] = 0;
    func_004447E0(object, cell, row, index, extra4, extra5, extra6, extra7, extra8);
}

extern void func_00444BF0(void* object, void* state, void* row);
