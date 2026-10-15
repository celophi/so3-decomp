#include "include_asm.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/vector.h"

extern "C" void func_00449E00(void* object);

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

typedef struct MappedEntry0043D240
{
    u8 unk00[0x30];
} MappedEntry0043D240;

typedef struct MappedOwner0043D240
{
    u8 unk00[0x14];
    MappedEntry0043D240* entries;
} MappedOwner0043D240;


INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00441C40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004447B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004447E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00444BF0);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444CF0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444D00(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_00444D10(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_00444D20(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_00444D30(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = (const ByteGetterOwnertext_0043A920*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444D40(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_00444D50(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_00444D60(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = (const ByteGetterOwnertext_0043A920*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444D70(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_00444D80(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_00444D90(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_00444DA0(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_00444DB0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_00444DC0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_00444DD0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_00444DE0(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_00444DF0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_00444E00(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444E10(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_00444E20(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_00444E30(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk40 = value;
}

void func_00444E40(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0043A920* receiver = (ByteSourceStateOwnertext_0043A920*)object;
    receiver->sourceA0 = (const u8*)source;
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

void func_00444E80(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0043A920* receiver = (TwoWordClearArgStateOwnertext_0043A920*)object;
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
void func_00444EB0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk38 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00444EC0);

void* func_00444EE0(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0043A920* receiver = (TwoIndexTableAddressOwnertext_0043A920*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_00444F00(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_00444F10(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_00444F20(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk10;
}

s32 func_00444F30(void* object)
{
    return 63;
}

s32 func_00444F40(void* receiver)
{
    WordNonzeroOwnertext_0043A920* object = (WordNonzeroOwnertext_0043A920*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00444F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004454B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00445520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004455D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00445670);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00445700);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00445780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00445840);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00445950);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00446EA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00446F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447030);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447090);

void func_00447160(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0043A920* receiver = (FourQuadwordCopyTargetOwnertext_0043A920*)object;
    const FourQuadwordCopySourceOwnertext_0043A920* values = (const FourQuadwordCopySourceOwnertext_0043A920*)source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_00447190(void* object)
{
}

s32 func_004471A0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004471B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447330);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447500);

void func_00447C60(void* object)
{
}

s32 func_00447C70(void* object)
{
    return 0;
}

void func_00447C80(void* object)
{
}

s32 func_00447C90(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447D80);

float func_00447DC0(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447DD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447DF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447E10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447EF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00447FA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448180);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004482B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448360);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448630);

void* func_00448690(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004486A0);

s32 func_00448900(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448910);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448A10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448B90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448BE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448C30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448CF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448D60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448DC0);

/** Set the low packed mode at 0x52 and record whether either mode equals four. */
void func_00448E20(void* object, u8 mode)
{
    PackedModesOwner* receiver = (PackedModesOwner*)object;
    receiver->at52.lowMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448E80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448F00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448F80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00448FF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00449090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00449190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00449220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004492D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_004495C0);

struct ResetVector70_0043A920 { u8 pad[0x70]; FieldVec4B value; };

void func_00449AF0(void* object)
{
    ((ResetVector70_0043A920*)object)->value = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    func_00449E00(object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00449B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00449C20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00449D90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00449E00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_00449E90);

/** Set the high packed mode at 0x52 and record whether either mode equals four. */
void func_00449EE0(void* object, u8 mode)
{
    PackedModesOwner* receiver = (PackedModesOwner*)object;
    receiver->at52.highMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Return the word at receiver offset 0x40. */
u32 func_00449F40(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk40;
}

/** Return the signed halfword at receiver offset 0x48. */
s16 func_00449F50(const void* object)
{
    const HalfwordGetterOwnertext_0043A920* receiver = (const HalfwordGetterOwnertext_0043A920*)object;
    return receiver->unk48;
}

/** Return the signed halfword at receiver offset 0x4A. */
s16 func_00449F60(const void* object)
{
    const HalfwordGetterOwnertext_0043A920* receiver = (const HalfwordGetterOwnertext_0043A920*)object;
    return receiver->unk4a;
}

s32 func_00449F70(void* object)
{
    return 0;
}

s32 func_00449F80(void* object)
{
    return 0;
}

s32 func_00449F90(void* object)
{
    return 0;
}

void func_00449FA0(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_00449FB0(void* object, float key)
{
    FloatKeyScanOwner_text_0043A920_30* receiver = (FloatKeyScanOwner_text_0043A920_30*)object;
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

void func_0044A000(void* object)
{
    FourWordClearOwnertext_0043A920* receiver = (FourWordClearOwnertext_0043A920*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A020);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A070);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A0C0);

/** Return the word at receiver offset 0x4. */
u32 func_0044A160(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A1C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A210);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A280);

void* func_0044A330(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A340);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A370);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A3A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A3D0);

/** Store 0x8 at receiver offset 0x60. */
void func_0044A400(void* object)
{
    ConstantByteSetterOwnertext_0043A920* receiver = (ConstantByteSetterOwnertext_0043A920*)object;
    receiver->unk60 = 0x8;
}

/** Build a four-word stack value and return its address. */
void* func_0044A410(void)
{
    s32 stack[4];
    s32* result;
    stack[0] = 0;
    stack[3] = 0x7149F2CA;
    stack[1] = 0;
    result = stack;
    stack[2] = 0;
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A5A0);

s32 func_0044A5E0(void* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043A920", func_0044A5F0);
