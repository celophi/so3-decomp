#include "include_asm.h"
#include "overlays/lib/text_003F90C0.h"

typedef struct ByteSetterOwnertext_003F90C0
{
    u8 unk00[0xE6];
    u8 unke6;
} ByteSetterOwnertext_003F90C0;

typedef struct LibChecksumState
{
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    u8 pad0C[0x64];
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
    u8 padB4[0x34];
    u32 checksumE8;
    u32 checksumEC;
    u8 padF0[0x1C];
    u32 checksum10C;
} LibChecksumState;

typedef struct LibCheckedWordState
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
} LibCheckedWordState;



INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F90C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F92F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F9390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F9410);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F9490);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F96C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F9760);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F97E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F9860);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003F9890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FEEF0);

/** Validate the checksum for the record fields beginning at zero. */
s32 func_003FEFA0(const void* object)
{
    const LibChecksumState* state = (const LibChecksumState*)object;
    if (state->checksumE8 != (state->checksum10C ^ (state->unk04 ^ (state->unk00 + state->unk02))))
    {
        return 0;
    }
    return state->unk04 ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FEFE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF010);

/** Validate the checksum for the record fields beginning at six. */
s32 func_003FF0C0(const void* object)
{
    const LibChecksumState* state = (const LibChecksumState*)object;
    if (state->checksumEC != (state->checksum10C ^ (state->unk0A ^ (state->unk06 + state->unk08))))
    {
        return 0;
    }
    return state->unk0A ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF100);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF130);

/** Validate the checksum for the record fields beginning at 0x76. */
s32 func_003FF210(const void* object)
{
    const LibChecksumState* state = (const LibChecksumState*)object;
    if (state->checksumB0 != (state->checksumA8 ^ (state->unk7A ^ (state->unk76 + state->unk78))))
    {
        return 0;
    }
    return state->unk7A ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF2C0);

/** Validate the checksum for the record fields beginning at 0x70. */
s32 func_003FF3A0(const void* object)
{
    const LibChecksumState* state = (const LibChecksumState*)object;
    if (state->checksumA4 != (state->checksumA8 ^ (state->unk74 ^ (state->unk70 + state->unk72))))
    {
        return 0;
    }
    return state->unk74 ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF3E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF450);

/** Validate the checksum for the record fields beginning at 0x7C. */
s32 func_003FF500(const void* object)
{
    const LibChecksumState* state = (const LibChecksumState*)object;
    if (state->checksumAC != (state->checksumA8 ^ (state->unk80 ^ (state->unk7C + state->unk7E))))
    {
        return 0;
    }
    return state->unk80 ^ 0x7E93;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF540);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF570);

s32 func_003FF740(const void* object)
{
    const LibCheckedWordState* state = (const LibCheckedWordState*)object;
    u32 check = state->unka8 ^ (state->unk54 ^ (state->unk4c + state->unk50));
    if (state->unk9c != check)
    {
        return 0;
    }
    return state->unk50 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF7F0);

s32 func_003FF8F0(const void* object)
{
    const LibCheckedWordState* state = (const LibCheckedWordState*)object;
    u32 check = state->unka8 ^ (state->unk60 ^ (state->unk58 + state->unk5c));
    if (state->unka0 != check)
    {
        return 0;
    }
    return state->unk60 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF930);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FF9A0);

s32 func_003FFAC0(const void* object)
{
    const LibCheckedWordState* state = (const LibCheckedWordState*)object;
    u32 check = state->unka8 ^ (state->unk48 ^ (state->unk40 + state->unk44));
    if (state->unk98 != check)
    {
        return 0;
    }
    return state->unk48 ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FFB00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FFB90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FFC90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FFCE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FFD50);

s32 func_003FFE50(const void* object)
{
    const LibCheckedWordState* state = (const LibCheckedWordState*)object;
    u32 check = state->unka8 ^ (state->unk3c ^ (state->unk34 + state->unk38));
    if (state->unk94 != check)
    {
        return 0;
    }
    return state->unk3c ^ 0x7DE3F7E3;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FFE90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_003FFF10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00400350);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004005C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00400830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00401780);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004028C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00402990);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00402B30);

/** Store the byte at receiver offset 0xE6. */
void func_00404560(void* object, u8 value)
{
    ByteSetterOwnertext_003F90C0* receiver = object;
    receiver->unke6 = value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004045A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004047C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404900);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404A70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404BA0);

s32 func_00404CA0(void* object, s32 value)
{
    ((u8*)object)[0x3B] = (u8)value ^ 0x77;
    return value;
}

s32 func_00404CC0(void* object, s32 value)
{
    u8* bytes = (u8*)object;
    bytes[0x3A] = value;
    return value;
}

s32 func_00404CD0(void* object, s32 value)
{
    u8* bytes = (u8*)object;
    bytes[0x39] = value;
    return value;
}

s32 func_00404CE0(void* object, s32 value)
{
    u8* bytes = (u8*)object;
    bytes[0x38] = value;
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404CF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404D10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404DA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404E50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404F10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404F50);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00404F90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405130);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004051E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405390);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405440);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405630);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004056E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405890);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405A40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405CB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405D70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00405F70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00406040);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00406240);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00406310);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004063E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004064E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004066D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004067C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004068A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00406AB0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00406B10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00406BF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00406C60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00406D90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00407050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00407190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00407460);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00407500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004075A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00407640);

s16 func_004076B0(void* object, s16 value)
{
    s16* fields = (s16*)object;
    fields[1] = value;
    return fields[1];
}

s16 func_004076C0(void* object, s16 value)
{
    s16* fields = (s16*)object;
    fields[0] = value;
    return fields[0];
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004076D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00407FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00408090);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004081D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00408200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00408600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004086D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_004087A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00408850);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00408E20);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_003F90C0", func_00408EA0);
