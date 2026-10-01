#include "include_asm.h"
#include "overlays/3253-00/text_001E2B40.h"

struct BattleField70
{
    u8 pad[0x70];
    u32 unk70;
};

struct BattleFieldD68
{
    u8 pad[0xD68];
    u32 unkD68;
};

struct BattleHalfwordPair
{
    s16 unk0;
    s16 unk2;
};

struct BattleVectorSlot50
{
    u8 pad[0x20];
    unsigned __int128 slot;
    u8 pad30[0x20];
    u8 ready;
};

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E2B40);

s32 func_001E2B80(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E2B90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E2BC0);

void func_001E2C40(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E2C50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E2C70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E2D10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E2F80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E3050);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E30E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E3140);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E3190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E3210);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E3280);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E4910);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E4C80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E4E00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E5B80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E5C10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E5C80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E5CE0);

void func_001E5D40(BattleField70* object, u32 value)
{
    object->unk70 = value;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E5D50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E61A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E6A30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E6A70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E6CC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E6D10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E6EC0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E6F10);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E72D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E76E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E7950);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E7E20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E84B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E8530);

void func_001E85A0(BattleVectorSlot50* object, const unsigned __int128* value)
{
    object->ready = 1;
    object->slot = *value;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E85C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E8800);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E88D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E8A00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E8BF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E8DE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E95B0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E96A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E9AF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E9BA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E9D50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E9E00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001E9FB0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA020);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA0E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA1C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA370);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA3E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA4A0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA580);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA780);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA850);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EA950);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EAB50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EAC20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EAD20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EAEF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EAF30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EAFA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EB070);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EB170);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EB360);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EB3F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EB4E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EB600);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EB6E0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EB8F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EB9F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EBA50);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EBB30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EBBA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EBCD0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EBF90);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EC010);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EC090);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EC110);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EC340);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EC480);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EC750);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EC7D0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001ECA00);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001ECAA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001ECB40);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001ECBE0);

s16 func_001ECC50(BattleHalfwordPair* object, s16 value)
{
    object->unk2 = value;
    return object->unk2;
}

s16 func_001ECC60(BattleHalfwordPair* object, s16 value)
{
    object->unk0 = value;
    return object->unk0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001ECC70);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001ECE60);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EED30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EED80);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EEDF0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EEE30);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EEEA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EEEE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EEF20);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EEFA0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EEFE0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EF080);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EF120);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EF160);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EF190);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001EF1D0);

u32 func_001F02B0(const BattleFieldD68* object)
{
    return object->unkD68;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001F02C0);

s32 func_001F07E0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001F07F0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001F0960);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001F10C0);

void func_001F13B0(void* object)
{
}

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001F13C0);

INCLUDE_ASM("build/overlays/3253-00/asm/nonmatchings/text_001E2B40", func_001F2390);
