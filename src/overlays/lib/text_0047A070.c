#include "include_asm.h"
#include "overlays/lib/text_0046AE20.h"

typedef struct HalfwordSetterOwnertext_0046AE20
{
    u8 unk00[0x6C];
    u16 unk6c;
} HalfwordSetterOwnertext_0046AE20;

typedef struct ByteGetterOwnertext_0046AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e[0x8];
    u8 unk56;
} ByteGetterOwnertext_0046AE20;

typedef struct ByteSetterOwnertext_0046AE20
{
    u8 unk00[0x4D];
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    u8 unk50[0x4];
    u8 unk54;
    u8 unk55;
    u8 unk56;
} ByteSetterOwnertext_0046AE20;

typedef struct WordSetterOwnertext_0046AE20
{
    u8 unk00[0x48];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x5C];
    u32 unkb0;
    u32 unkb4;
    u32 unkb8;
    u32 unkbc;
} WordSetterOwnertext_0046AE20;

typedef struct WordGetterOwnertext_0046AE20
{
    u8 unk00[0x8];
    u32 unk08;
    u32 unk0c;
    u8 unk10[0x38];
    u32 unk48;
    u8 unk4c[0x4];
    u32 unk50;
    u8 unk54[0x5C];
    u32 unkb0;
    u32 unkb4;
    u32 unkb8;
    u32 unkbc;
} WordGetterOwnertext_0046AE20;

typedef struct LibFlagState59C
{
    u8 unk00[0x59C];
    u8 unk59c;
    u8 unk59d_0 : 1;
    u8 unk59d_1_7 : 7;
} LibFlagState59C;

typedef struct LibFloatFieldOwner0046AE20
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
} LibFloatFieldOwner0046AE20;

typedef struct LibManagedEntry
{
    u8 unk00;
    u8 unk01[3];
    u32 unk04;
    void* handle;
    LibEntryMetadata* metadata;
} LibManagedEntry;

typedef struct LibEntryTableHeader
{
    u32 flags;
    s32 count;
} LibEntryTableHeader;

typedef struct LibTransformByteState
{
    u8 unk00[0x50];
    u8 transform_dirty;
} LibTransformByteState;

typedef struct LibObjectFlags6A
{
    u8 unk00[0x6A];
    u16 flags;
} LibObjectFlags6A;

typedef struct ByteSourceStateOwnertext_0046AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; const u8* sourceA0; u32 valueA4; } ByteSourceStateOwnertext_0046AE20;

typedef struct TwoWordClearArgStateOwnertext_0046AE20 { u8 pad00[0x57]; u8 state57; u8 pad58[0x48]; void* unkA0; void* unkA4; } TwoWordClearArgStateOwnertext_0046AE20;

typedef struct FourQuadwordCopyTargetOwnertext_0046AE20
{
    u8 pad00[0x2C];
    u32 unk2C;
    u8 pad30[0x30];
    unsigned __int128 values60[4];
} FourQuadwordCopyTargetOwnertext_0046AE20;

typedef struct FourQuadwordCopySourceOwnertext_0046AE20
{
    u8 pad00[0x150];
    unsigned __int128 values150[4];
} FourQuadwordCopySourceOwnertext_0046AE20;


/** Store the word at receiver offset 0xB0. */
void func_0047A070(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkb0 = value;
}

/** Return the word at receiver offset 0xB0. */
u32 func_0047A080(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkb0;
}

/** Store the word at receiver offset 0xB4. */
void func_0047A090(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkb4 = value;
}

/** Return the word at receiver offset 0xB4. */
u32 func_0047A0A0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkb4;
}

/** Store the word at receiver offset 0xB0. */
void func_0047A0B0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkb0 = value;
}

/** Return the word at receiver offset 0xB0. */
u32 func_0047A0C0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkb0;
}

/** Store the word at receiver offset 0xB4. */
void func_0047A0D0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unkb4 = value;
}

/** Return the word at receiver offset 0xB4. */
u32 func_0047A0E0(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unkb4;
}

s32 func_0047A0F0(void* object)
{
    return 0;
}

s32 func_0047A100(void* object)
{
    return 0;
}

s32 func_0047A110(void* object)
{
    return 0;
}

s32 func_0047A120(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A540);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A640(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A650(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047A660(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047A670(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047A680(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A690(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047A6A0(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047A6B0(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A6C0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0047A6D0(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0047A6E0(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0047A6F0(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0047A700(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0047A710(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0047A720(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0047A730(void* object, u32 value)
{
    WordSetterOwnertext_0046AE20* receiver = object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0047A740(const void* object)
{
    const WordGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0047A750(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A760(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0047A770(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047A780(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk40 = value;
}

void func_0047A790(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0046AE20* receiver = object;
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

void func_0047A7D0(void* object, s32 enabled)
{
    TwoWordClearArgStateOwnertext_0046AE20* receiver = object;
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
void func_0047A800(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk38 = value;
}

void func_0047A810(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0046AE20* receiver = object;
    const FourQuadwordCopySourceOwnertext_0046AE20* values = source;
    receiver->unk2C = 0;
    receiver->values60[0] = values->values150[0];
    receiver->values60[1] = values->values150[1];
    receiver->values60[2] = values->values150[2];
    receiver->values60[3] = values->values150[3];
}

void func_0047A840(void* object)
{
}

s32 func_0047A850(void* object)
{
    return 1;
}

typedef struct MappedEntry0047A860
{
    u8 unk00[0x120];
} MappedEntry0047A860;

typedef struct MappedOwner0047A860
{
    u8 unk00[0x14];
    MappedEntry0047A860* entries;
} MappedOwner0047A860;

void* func_0047A860(const void* object, s32 index)
{
    const MappedOwner0047A860* owner = (const MappedOwner0047A860*)object;
    MappedEntry0047A860* item = &owner->entries[index];
    void* result = item;
    if (item != 0)
    {
        result = (u8*)item + 0xF0;
    }
    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047A890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0046AE20", func_0047ACA0);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADA0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADB0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0047ADC0(void* object)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0047ADD0(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0047ADE0(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0047ADF0(void* object, float value)
{
    LibFloatFieldOwner0046AE20* receiver = object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0047AE00(void* object, u8 value)
{
    ByteSetterOwnertext_0046AE20* receiver = object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0047AE10(const void* object)
{
    const ByteGetterOwnertext_0046AE20* receiver = object;
    return receiver->unk56;
}
