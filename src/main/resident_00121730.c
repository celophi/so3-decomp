#include "include_asm.h"
#include "main/resident_00121730.h"
#include "main/resident_0011EE70.h"

typedef struct N66Vector4Source { float x; float y; float z; float w; } N66Vector4Source;

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



void func_00121730(u8* object, float x, float y, float z)
{
    N66Vector4Source value;
    object[0x50] = 1;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    func_4CE4C0(object + 0x30, &value.x);
}

void func_00121770(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = object;
    receiver->ready = 1;
    receiver->slots[2] = *value;
}

void func_00121790(void* object, const unsigned __int128* value)
{
    FlagQuadwordOwnerresident_0011EE70* receiver = object;
    receiver->ready = 1;
    receiver->slots[2] = *value;
}

void func_001217B0(void* object, float x, float y, float z)
{
    FlagFloatTripleOwnerresident_0011EE70* receiver = object;
    receiver->flag50 = 1;
    receiver->values[0] = x;
    receiver->values[1] = y;
    receiver->values[2] = z;
}

s32 func_001217D0(void* object)
{
    return 0;
}

void* func_001217E0(void* object)
{
    if (((u8*)object)[0x2C0] != 0)
    {
        return (u8*)object + 0x238;
    }
    return 0;
}

s32 func_00121800(void* object)
{
    return func_001217D0((u8*)object - 0x210);
}

void* func_00121810(void* object)
{
    return func_001217E0((u8*)object - 0x210);
}

void* func_00121820(void* object)
{
    return func_001213B0((u8*)object - 0x210);
}

void func_00121830(void* object)
{
    func_00120BF0((u8*)object - 0x78);
}

s32 func_00121840(void* object)
{
    return func_001207D0((u8*)object - 0x78);
}

void* func_00121850(void* object)
{
    return func_00120700((u8*)object - 0x78);
}

s32 func_00121860(void* object)
{
    return -1;
}

void func_00121870(void* object)
{
}

void func_00121880(void* object)
{
}

void func_00121890(void* object)
{
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00121730", func_001218A0);
