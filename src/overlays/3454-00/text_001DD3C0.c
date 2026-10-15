#include "include_asm.h"
#include "overlays/3454-00/text_001DD3C0.h"

typedef struct WordSetterOwnertext_001DD3C0
{
    u8 unk00[0x70];
    u32 unk70;
} WordSetterOwnertext_001DD3C0;



typedef struct WordGetterOwnertext_001DD3C0
{
    u8 unk00[0xD58];
    u32 unkd58;
} WordGetterOwnertext_001DD3C0;

/** Partial receiver with three aligned quadword slots and a ready byte at 0x50. */
typedef struct QuadwordSetterOwnertext_001DD3C0
{
    u8 unk00[0x20];
    unsigned __int128 slots[3];
    u8 ready;
} QuadwordSetterOwnertext_001DD3C0;

typedef struct BattleChecksumState
{
    u8 pad00[0x70];
    s16 unk70;
    s16 unk72;
    s16 unk74;
    s16 unk76;
    s16 unk78;
    s16 unk7A;
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    u8 pad82[0x22];
    u32 checksumA4;
    u32 checksumA8;
    u32 checksumAC;
    u32 checksumB0;
} BattleChecksumState;

typedef struct BattleCheckedWordState
{
    u8 pad00[0x34];
    u32 unk34;
    u32 unk38;
    u32 unk3c;
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u32 unk4c;
    u32 unk50;
    u32 unk54;
    u32 unk58;
    u32 unk5c;
    u32 unk60;
    u8 pad64[0x30];
    u32 unk94;
    u32 unk98;
    u32 unk9c;
    u32 unka0;
    u8 pada4[4];
    u32 unka8;
} BattleCheckedWordState;


INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD3C0);

s32 func_001DD400(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD410);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD440);

void func_001DD4C0(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD4D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD4F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD590);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD800);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD8D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD960);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DD9C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DDA10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DDB40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DE5F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DE650);

/** Store the word at receiver offset 0x70. */
void func_001DE6B0(void* object, u32 value)
{
    WordSetterOwnertext_001DD3C0* receiver = object;
    receiver->unk70 = value;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DE6C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DEA00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DF060);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DF0A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DF2F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DF340);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DF530);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DF580);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DF7C0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DF930);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001DFDF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E0050);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E0520);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E0B30);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E0C40);

void func_001E0CB0(void* object, const unsigned __int128* value)
{
    QuadwordSetterOwnertext_001DD3C0* receiver = object;
    receiver->ready = 1;
    receiver->slots[0] = *value;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E0CD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E0E20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E0EF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E1020);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E1180);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E1320);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E1450);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E1630);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E17F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E1870);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E2240);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E2330);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E27A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E2850);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E2A00);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E2AB0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E2C60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E2CD0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E2D90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E2E70);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3020);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3090);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3150);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3230);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3430);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3500);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3600);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3800);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E38D0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E39D0);

s32 func_001E3BA0(const void* object)
{
    const BattleCheckedWordState* state = (const BattleCheckedWordState*)object;
    u32 check = state->unka8 ^ (state->unk54 ^ (state->unk4c + state->unk50));
    if (state->unk9c != check)
    {
        return 0;
    }
    return state->unk50 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3BE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3C50);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3D20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E3E20);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4010);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E40A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4190);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E42B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4390);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E45A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E46A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4700);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E47E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4850);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4980);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4C40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4CC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4D40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4DC0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E4FF0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E5130);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E5400);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E5480);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E56B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E5750);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E57F0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E5890);

s16 func_001E5900(void* object, s16 value)
{
    s16* fields = (s16*)object;
    fields[1] = value;
    return fields[1];
}

s16 func_001E5910(void* object, s16 value)
{
    s16* fields = (s16*)object;
    fields[0] = value;
    return fields[0];
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E5920);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E5B90);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E7A60);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E7AB0);

s32 func_001E7B20(const void* object)
{
    const BattleCheckedWordState* state = (const BattleCheckedWordState*)object;
    u32 check = state->unka8 ^ (state->unk60 ^ (state->unk58 + state->unk5c));
    if (state->unka0 != check)
    {
        return 0;
    }
    return state->unk60 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E7B60);

s32 func_001E7BD0(const void* object)
{
    const BattleCheckedWordState* state = (const BattleCheckedWordState*)object;
    u32 check = state->unka8 ^ (state->unk48 ^ (state->unk40 + state->unk44));
    if (state->unk98 != check)
    {
        return 0;
    }
    return state->unk48 ^ 0x7DE3F7E3;
}

s32 func_001E7C10(const void* object)
{
    const BattleCheckedWordState* state = (const BattleCheckedWordState*)object;
    u32 check = state->unka8 ^ (state->unk3c ^ (state->unk34 + state->unk38));
    if (state->unk94 != check)
    {
        return 0;
    }
    return state->unk3c ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E7C50);

/** Validate the checksum for the record fields beginning at 0x70. */
s32 func_001E7CD0(const void* object)
{
    const BattleChecksumState* state = (const BattleChecksumState*)object;
    if (state->checksumA4 != (state->checksumA8 ^ (state->unk74 ^ (state->unk70 + state->unk72))))
    {
        return 0;
    }
    return state->unk74 ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E7D10);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E7DB0);

/** Validate the checksum for the record fields beginning at 0x7C. */
s32 func_001E7E50(const void* object)
{
    const BattleChecksumState* state = (const BattleChecksumState*)object;
    if (state->checksumAC != (state->checksumA8 ^ (state->unk80 ^ (state->unk7C + state->unk7E))))
    {
        return 0;
    }
    return state->unk80 ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E7E90);

/** Validate the checksum for the record fields beginning at 0x76. */
s32 func_001E7EC0(const void* object)
{
    const BattleChecksumState* state = (const BattleChecksumState*)object;
    if (state->checksumB0 != (state->checksumA8 ^ (state->unk7A ^ (state->unk76 + state->unk78))))
    {
        return 0;
    }
    return state->unk7A ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E7F00);

/** Return the word at receiver offset 0xD58. */
u32 func_001E8DD0(const void* object)
{
    const WordGetterOwnertext_001DD3C0* receiver = object;
    return receiver->unkd58;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E8DE0);

s32 func_001E9500(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E9510);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E96B0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001E9F30);

void func_001EA190(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001EA1A0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001EAFE0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001EB870);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001EBBB0);

void func_001EC6F0(void* object)
{
}

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001EC700);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001ECB40);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001ED070);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001ED0E0);

INCLUDE_ASM("build/overlays/3454-00/asm/nonmatchings/text_001DD3C0", func_001ED230);
