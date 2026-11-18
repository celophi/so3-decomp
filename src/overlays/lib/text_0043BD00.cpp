#include "include_asm.h"
#include "overlays/lib/text_0043A920.h"
#include "overlays/lib/text_0049B820.h"
#include "overlays/lib/particle_grid.h"
#include "overlays/lib/text_0043BD00.h"

extern "C" {

typedef struct WordNonzeroOwnertext_0043A920
{
    u8 unk00[0x14];
    u32 unk14;
} WordNonzeroOwnertext_0043A920;

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

extern void* __vt__7LibLink;

extern u8 D_00173A28[];

extern u8 D_00173F48[];

extern u8 D_00173F38[];

extern void func_004447E0(void* object, void* cell, void* row, s32 index, void* extra4, void* extra5, void* extra6, void* extra7, void* extra8);

/** @brief Destroy the transform. */
LibClass173B10::~LibClass173B10()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", update__14LibClass173B10Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot88__14LibClass173B10Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot84__14LibClass173B10Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot88__14LibClass173C40Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043C570);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", update__14LibClass173C40Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot84__14LibClass173C40Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043CBF0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043CCE0);

/** @brief Destroy the transform. */
LibClass173C40::~LibClass173C40()
{
}

/** @brief Destroy the grid. */
LibClass173CD0::~LibClass173CD0()
{
}

s32 func_0043D0B0(void* object)
{
    return 0;
}

s32 func_0043D0C0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043D0D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", __dt__14LibClass173DA0Fv);

void func_0043D1F0(void* object, const void* source)
{
    FourQuadwordCopyTargetOwnertext_0043A920* receiver = (FourQuadwordCopyTargetOwnertext_0043A920*)object;
    const FourQuadwordCopySourceOwnertext_0043A920* values = (const FourQuadwordCopySourceOwnertext_0043A920*)source;
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
    void* result = (void*)item;

    if (item != 0)
    {
        result = (u8*)item + 0x30;
    }

    return result;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043D270);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043D670);

/**
 * @brief Store the value at receiver offset 0x28.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D770(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk28 = value;
}

/**
 * @brief Store the value at receiver offset 0x30.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D780(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk30 = value;
}

/** Return the float member at receiver offset 0x30. */
float func_0043D790(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk30;
}

/** Store the byte at receiver offset 0x4D. */
void func_0043D7A0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4d = value;
}

/** Return the unsigned byte at receiver offset 0x4D. */
u8 func_0043D7B0(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = (const ByteGetterOwnertext_0043A920*)object;
    return receiver->unk4d;
}

/**
 * @brief Store the value at receiver offset 0x34.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D7C0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk34 = value;
}

/** Store the byte at receiver offset 0x56. */
void func_0043D7D0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk56 = value;
}

/** Return the unsigned byte at receiver offset 0x56. */
u8 func_0043D7E0(const void* object)
{
    const ByteGetterOwnertext_0043A920* receiver = (const ByteGetterOwnertext_0043A920*)object;
    return receiver->unk56;
}

/**
 * @brief Store the value at receiver offset 0x44.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D7F0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk44 = value;
}

/** Return the float member at receiver offset 0x44. */
float func_0043D800(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk44;
}

/** Return the float member at receiver offset 0x28. */
float func_0043D810(void* object)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    return receiver->unk28;
}

/** Store the word at receiver offset 0x48. */
void func_0043D820(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unk48 = value;
}

/** Return the word at receiver offset 0x48. */
u32 func_0043D830(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk48;
}

/** Store the byte at receiver offset 0x4F. */
void func_0043D840(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4f = value;
}

/** Store the byte at receiver offset 0x4E. */
void func_0043D850(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk4e = value;
}

/** Store the word at receiver offset 0x50. */
void func_0043D860(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unk50 = value;
}

/** Return the word at receiver offset 0x50. */
u32 func_0043D870(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk50;
}

/** Store the byte at receiver offset 0x55. */
void func_0043D880(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk55 = value;
}

/**
 * @brief Store the value at receiver offset 0x3C.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D890(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk3c = value;
}

/** Store the byte at receiver offset 0x54. */
void func_0043D8A0(void* object, u8 value)
{
    ByteSetterOwnertext_0043A920* receiver = (ByteSetterOwnertext_0043A920*)object;
    receiver->unk54 = value;
}

/**
 * @brief Store the value at receiver offset 0x40.
 * @param object Receiver whose float field is updated.
 * @param value Value to store.
 */
void func_0043D8B0(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
    receiver->unk40 = value;
}

void func_0043D8C0(void* object, const u8* source, u32 value)
{
    ByteSourceStateOwnertext_0043A920* receiver = (ByteSourceStateOwnertext_0043A920*)object;
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
void func_0043D930(void* object, float value)
{
    LibFloatFieldOwner0043A920* receiver = (LibFloatFieldOwner0043A920*)object;
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
    SingleIndexTableAddressOwnertext_0043A920* receiver = (SingleIndexTableAddressOwnertext_0043A920*)object;
    return receiver->base14 + index * 48;
}

void* func_0043D9A0(void* object, s32 row, s32 column)
{
    TwoIndexTableAddressOwnertext_0043A920* receiver = (TwoIndexTableAddressOwnertext_0043A920*)object;
    return &receiver->entries[row * (receiver->count - 1) + column];
}

/** Return the word at receiver offset 0x1C. */
u32 func_0043D9C0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk1c;
}

/** Return the word at receiver offset 0xC. */
u32 func_0043D9D0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk0c;
}

/** Return the word at receiver offset 0x10. */
u32 func_0043D9E0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unk10;
}

/**
 * @brief Report a selected cell.
 * @return One.
 */
s32 LibClass173E70::func_slot3C()
{
    return 1;
}

s32 func_0043DA00(void* receiver)
{
    WordNonzeroOwnertext_0043A920* object = (WordNonzeroOwnertext_0043A920*)receiver;
    return object->unk14 != 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043DA10);

/** @brief Construct the element. */
LibClass173F38::LibClass173F38()
{
}

/** @brief Destroy the element. */
LibClass173F38::~LibClass173F38()
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_0043E0A0);

/** @brief Release the cells, the bit set and the secondary elements. */
LibClass173E70::~LibClass173E70()
{
    delete[] unk18;
    delete unk1c;
    delete[] unk24;
}

/**
 * @brief Copy another grid's size and emission settings.
 * @param source Grid to copy.
 */
void LibClass173DA0::copy_settings(const LibClass173A40* source)
{
    const LibClass173DA0* other = static_cast<const LibClass173DA0*>(source);

    unk0c = other->unk0c;
    unk10 = other->unk10;
    resize(unk0c, unk10);
    unk28 = other->unk28;
    unk30 = other->unk30;
    unk34 = other->unk34;
    unk38 = other->unk38;
    unk48 = other->unk48;
    unk4c = other->unk4c;
    unk4d = other->unk4d;
    unk4e = other->unk4e;
    unk4f = other->unk4f;
    unk50 = other->unk50;
    unk54 = other->unk54;
    unk55 = other->unk55;
    unk3c = other->unk3c;
    unka0 = other->unka0;
    unka4 = other->unka4;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot10__14LibClass173DA0Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_slot14__14LibClass173DA0Fv);

/**
 * @brief Copy another grid's size and resize this grid to match.
 * @param source Grid to copy.
 */
void LibClass173E70::copy_settings(const LibClass173A40* source)
{
    unk0c = source->unk0c;
    unk10 = source->unk10;
    resize(unk0c, unk10);
}

float func_00441520(void* object)
{
    return 1.0f;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_00441530);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_00441600);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_00441660);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_00441B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_0043BD00", func_00441B50);

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
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unkb8 = value;
}

/** Return the word at receiver offset 0xB8. */
u32 func_00441BB0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
    return receiver->unkb8;
}

/** Store the word at receiver offset 0xBC. */
void func_00441BC0(void* object, u32 value)
{
    WordSetterOwnertext_0043A920* receiver = (WordSetterOwnertext_0043A920*)object;
    receiver->unkbc = value;
}

/** Return the word at receiver offset 0xBC. */
u32 func_00441BD0(const void* object)
{
    const WordGetterOwnertext_0043A920* receiver = (const WordGetterOwnertext_0043A920*)object;
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

}
