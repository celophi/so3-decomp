#include "include_asm.h"
#include "main/resident_0011EE70.h"

extern void func_4CE4C0(void* destination, const float* source);
extern u8 D_50CD30[];
extern u8 D_0014FC78[];
extern const void* D_001B6424;

typedef struct ByteTransitionViewOwnerresident_0011EE70
{
    u8 pad00[0x24];
    u8 unk24;
    u8 unk25;
} ByteTransitionViewOwnerresident_0011EE70;

typedef struct ResidentFlagBytesViewOwnerresident_0011EE70
{
    u8 pad00[0x25];
    u8 unk25;
    u8 pad26[0x53];
    u8 unk79;
    u8 unk7A;
    u8 unk7B;
    u8 unk7C;
    u8 pad7D;
    u8 unk7E;
} ResidentFlagBytesViewOwnerresident_0011EE70;

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

typedef struct ResidentWordAndFlag2B4Ownerresident_0011EE70
{
    u8 pad00[0x2B4];
    u32 unk2B4;
    u32 unk2B8;
    u8 pad2BC[0x7];
    u8 unk2C3;
    u8 unk2C4;
} ResidentWordAndFlag2B4Ownerresident_0011EE70;


typedef struct FlagQuadwordOwnerresident_0011EE70 { u8 unk00[0x20]; unsigned __int128 slots[3]; u8 ready; } FlagQuadwordOwnerresident_0011EE70;

typedef struct FlagFloatQuadOwnerresident_0011EE70 { u8 pad00[0x30]; float values[4]; u8 pad40[0x10]; u8 flag50; } FlagFloatQuadOwnerresident_0011EE70;

typedef struct FlagFloatQuadOffset20Ownerresident_0011EE70
{
    u8 pad00[0x20];
    float values[4];
    u8 pad30[0x20];
    u8 flag50;
} FlagFloatQuadOffset20Ownerresident_0011EE70;

typedef struct FlagFloatTripleOwnerresident_0011EE70 { u8 pad00[0x40]; float values[3]; u8 pad4C[4]; u8 flag50; } FlagFloatTripleOwnerresident_0011EE70;

typedef struct ResidentInitViewOwnerresident_0011EE70
{
    u32 unk00;
    u32 unk04;
    u8 pad08[0x1000];
    u32 unk1008;
    u32 unk100C;
    u8 pad1010[0x1000];
    void* unk2010;
} ResidentInitViewOwnerresident_0011EE70;

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011EE70);

/**
 * @brief Initialize the selected fields and return the receiver.
 * @param object Object to update.
 * @return The same object.
 */
void* func_0011EED0(void* object)
{
    ResidentInitViewOwnerresident_0011EE70* receiver = object;
    receiver->unk2010 = D_0014FC78;
    receiver->unk00 = 1;
    receiver->unk04 = 0;
    receiver->unk1008 = 1;
    receiver->unk100C = 0;
    return receiver;
}

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

/**
 * @brief Return the low 28 bits of the word at receiver offset 0xC.
 * @param object Object containing the word.
 * @return The word with its upper four bits cleared.
 */
u32 func_0011F760(const void* object)
{
    const u32* words = object;
    return words[3] & 0x0FFFFFFF;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F770);

/**
 * @brief Advance the packet cursor to the next 16-byte boundary.
 * @param packet Packet whose cursor is updated.
 * @param cursor Requested cursor.
 * @return The updated packet cursor.
 */
u8* func_0011F830(ResidentPacket* packet, u8* cursor)
{
    if (((u32)cursor & 0xF) != 0)
    {
        cursor = (u8*)(((u32)cursor + 0xF) & 0xFFFFFFF0);
    }
    packet->unk08 = cursor;
    return packet->unk08;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F860);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F8A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F940);

/**
 * @brief Move the set state from byte 0x25 to byte 0x24 when set.
 * @param object Object containing the state bytes.
 */
void func_0011F9B0(void* object)
{
    ByteTransitionViewOwnerresident_0011EE70* receiver = object;
    if (receiver->unk25 != 0)
    {
        receiver->unk25 = 0;
        receiver->unk24 = 1;
    }
}

/** Return the unsigned byte at receiver offset 0x25. */
u8 func_0011F9D0(void* object)
{
    const ByteTransitionViewOwnerresident_0011EE70* receiver = object;
    return receiver->unk25;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011F9E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FA80);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FB40);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_0011FC20);

/**
 * @brief Initialize selected status bytes when the byte at 0x25 is clear.
 * @param object Object containing the status bytes.
 */
void func_0011FFD0(void* object)
{
    ResidentFlagBytesViewOwnerresident_0011EE70* receiver = object;
    if (receiver->unk25 == 0)
    {
        receiver->unk79 = 0;
        receiver->unk7C = 0;
        receiver->unk25 = 1;
        receiver->unk7B = 1;
        receiver->unk7A = 0;
        receiver->unk7E = 1;
    }
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120000);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_00120050);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_0011EE70", func_001200C0);

void func_00120360(const void* value)
{
    D_001B6424 = value;
}

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

void func_00120A50(void* object, u8 flag, u32 value)
{
    ResidentWordAndFlag2B4Ownerresident_0011EE70* receiver = object;
    receiver->unk2C4 = flag;
    receiver->unk2B8 = value;
}

void func_00120A60(void* object, u8 flag, u32 value)
{
    ResidentWordAndFlag2B4Ownerresident_0011EE70* receiver = object;
    receiver->unk2C3 = flag;
    receiver->unk2B4 = value;
}

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

/**
 * @brief Store three components and set the fourth to 1.0 at offset 0x20.
 * @param object Object containing the vector and flag.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_00121670(void* object, float x, float y, float z)
{
    FlagFloatQuadOffset20Ownerresident_0011EE70* receiver = object;
    receiver->flag50 = 1;
    receiver->values[0] = x;
    receiver->values[1] = y;
    receiver->values[2] = z;
    receiver->values[3] = 1.0f;
}

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
