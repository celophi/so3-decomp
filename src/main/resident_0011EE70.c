#include "include_asm.h"
#include "main/resident_0011EE70.h"

extern void func_4CE4C0(void* destination, const float* source);
extern u8 D_50CD30[];

typedef struct ByteGetterOwnerresident_0011EE70
{
    u8 unk00[0x25];
    u8 unk25;
} ByteGetterOwnerresident_0011EE70;

typedef struct ByteClearOwnerresident_0011EE70
{
    u8 unk00[0x60];
    u8 unk60;
} ByteClearOwnerresident_0011EE70;



typedef struct WordSetterOwnerresident_0011EE70
{
    u8 unk00[0x70];
    u32 unk70;
} WordSetterOwnerresident_0011EE70;



typedef struct WordGetterOwnerresident_0011EE70
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0c;
    u32 unk10;
    u32 unk14;
} WordGetterOwnerresident_0011EE70;


typedef struct FlagQuadwordOwnerresident_0011EE70 { u8 unk00[0x20]; unsigned __int128 slots[3]; u8 ready; } FlagQuadwordOwnerresident_0011EE70;

typedef struct FlagFloatQuadOwnerresident_0011EE70 { u8 pad00[0x30]; float values[4]; u8 pad40[0x10]; u8 flag50; } FlagFloatQuadOwnerresident_0011EE70;

typedef struct FlagFloatTripleOwnerresident_0011EE70 { u8 pad00[0x40]; float values[3]; u8 pad4C[4]; u8 flag50; } FlagFloatTripleOwnerresident_0011EE70;

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011EE70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011EED0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011EF00);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011EF90);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F020);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F0B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F140);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F1D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F390);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F510);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F580);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F640);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F6E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F760);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F770);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F830);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F860);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F8A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F940);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F9B0);

/** Return the unsigned byte at receiver offset 0x25. */
u8 func_0011F9D0(void* object)
{
    const ByteGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk25;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F9E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FA80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FB40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FC20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FFD0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120050);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001200C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120360);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120370);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001203C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120410);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001204B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120560);

/** Return the word at receiver offset 0x14. */
u32 func_001205A0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk14;
}

s32 func_001205B0(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 100)
    {
        value = 100;
    }
    receiver->unk10 = value;
    return value;
}

/** Return the word at receiver offset 0x10. */
u32 func_001205E0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk10;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001205F0);

/** Return the word at receiver offset 0xC. */
u32 func_00120630(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk0c;
}

s32 func_00120640(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 255)
    {
        value = 255;
    }
    receiver->unk08 = value;
    return value;
}

/** Return the word at receiver offset 0x8. */
u32 func_00120670(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk08;
}

s32 func_00120680(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 999)
    {
        value = 999;
    }
    receiver->unk04 = value;
    return value;
}

/** Return the word at receiver offset 0x4. */
u32 func_001206B0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk04;
}

s32 func_001206C0(void* object, s32 value)
{
    WordGetterOwnerresident_0011EE70* receiver = object;
    if (value < 0)
    {
        value = 0;
    }
    if (value > 9999)
    {
        value = 9999;
    }
    receiver->unk00 = value;
    return value;
}

/** Return the word at receiver offset 0x0. */
u32 func_001206F0(const void* object)
{
    const WordGetterOwnerresident_0011EE70* receiver = object;
    return receiver->unk00;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120700);

/** Store the word at receiver offset 0x70. */
void func_001207B0(void* object, u32 value)
{
    WordSetterOwnerresident_0011EE70* receiver = object;
    receiver->unk70 = value;
}

void func_001207C0(void* object)
{
}

s32 func_001207D0(void* object)
{
    return 9;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001207E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120840);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120A50);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120A60);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120A70);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120BF0);

void func_00120EB0(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = object;
    receiver->ready = 1;
    receiver->slots[1] = *value;
}

void func_00120ED0(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = object;
    receiver->ready = 1;
    receiver->slots[0] = *value;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120EF0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120F20);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120FE0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001210B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001212A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001213B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121490);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121520);

s32 func_00121570(void* object)
{
    return 0;
}

void* func_00121580(void* object)
{
    return (u8*)object + 0x90;
}

void* func_00121590(void* object)
{
    return (u8*)object + 0x1D0;
}

void* func_001215A0(void* object)
{
    return (u8*)object + 0x1E0;
}

void* func_001215B0(void* object)
{
    return (u8*)object + 0x1F0;
}

void func_001215C0(void* object)
{
    ByteClearOwnerresident_0011EE70* receiver = object;
    receiver->unk60 = 0;
}

void func_001215D0(void* object)
{
}

s32 func_001215E0(void* object)
{
    return 0;
}

s32 func_001215F0(float value)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

const void* func_00121610(void)
{
    return D_50CD30;
}

void func_00121620(void* object)
{
}

s32 func_00121630(void* object)
{
    return 0;
}

void func_00121640(void* object)
{
}

void func_00121650(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = object;
    receiver->ready = 1;
    receiver->slots[0] = *value;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00121670);

void func_00121690(void* object, float x, float y, float z, float w)
{
    FlagFloatQuadOwnerresident_0011EE70* receiver = object;
    receiver->flag50 = 1;
    receiver->values[0] = x;
    receiver->values[1] = y;
    receiver->values[2] = z;
    receiver->values[3] = w;
}

void func_001216B0(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = object;
    receiver->ready = 1;
    receiver->slots[1] = *value;
}
