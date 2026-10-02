#include "include_asm.h"
#include "overlays/1067-00/text_002764D0.h"
#include "overlays/1067-00/text_002CABC0.h"
#include "boot/resident_data.h"
#include "boot/resident_0010A0E0.h"
#include "overlays/0002-01/text_004CD3A0.h"


typedef struct FieldFlagState271B0
{
    u8 unk00[0x428];
    s32 unk428;
    u8 unk42c[0x171];
    u8 unk59d_0 : 1;
    u8 unk59d_1 : 1;
    u8 unk59d_2_7 : 6;
} FieldFlagState271B0;

typedef struct FieldFlagState2B320
{
    u8 unk00[0x24];
    s32 unk24;
    u8 unk28[0x24];
    u8 unk4c_0 : 1;
    u8 unk4c_1 : 1;
    u8 unk4c_2 : 1;
    u8 unk4c_3 : 1;
    u8 unk4c_4 : 1;
    u8 unk4c_5 : 1;
    u8 unk4c_6_7 : 2;
    u8 unk4d[0x1C];
    u8 unk69_0 : 1;
    u8 unk69_1 : 1;
    u8 unk69_2_7 : 6;
} FieldFlagState2B320;

typedef struct FieldEntry293F0
{
    u8 unk00[4];
    u32 unk04;
    u8 unk08[0x14];
    u8 unk1c_0 : 1;
    u8 unk1c_1_7 : 7;
    u8 unk1d[3];
} FieldEntry293F0;

typedef struct FieldEntryOwner293F0
{
    u8 unk00[0x1C];
    FieldEntry293F0* entries;
} FieldEntryOwner293F0;

typedef struct FieldLookupNode2BF70
{
    u8 unk00[8];
    struct FieldLookupNode2BF70* next;
    u8 unk0c[8];
    u32 unk14;
} FieldLookupNode2BF70;

typedef struct FieldLookupList2BF70
{
    u8 unk00[0x14];
    FieldLookupNode2BF70 head;
} FieldLookupList2BF70;

typedef struct FieldFlagEntry2BB00
{
    u8 unk00_0 : 1;
    u8 unk00_1 : 1;
    u8 unk00_2 : 1;
    u8 unk00_3_7 : 5;
    u8 unk01[0x1F];
} FieldFlagEntry2BB00;

typedef struct FieldFlagTable2BB00
{
    u8 unk00[0xCC];
    FieldFlagEntry2BB00 entries[8];
} FieldFlagTable2BB00;

typedef struct FieldFloatState28F00
{
    u8 unk00[0x340];
    float unk340;
    float unk344;
    float unk348;
    float unk34c;
} FieldFloatState28F00;

typedef struct FieldState2BAF0
{
    u8 unk00[0x1CC];
    u32 unk1cc;
    u8 unk1d0[0x18];
    u8 unk1e8;
} FieldState2BAF0;

typedef struct FieldState2B390
{
    u8 unk00[0x1E4];
    u32 unk1e4;
    u8 unk1e8[2];
    u8 unk1ea_0_3 : 4;
    u8 unk1ea_4 : 1;
    u8 unk1ea_5_7 : 3;
} FieldState2B390;

typedef struct FieldQword27A9A0
{
    unsigned __int128 value;
} FieldQword27A9A0;

typedef struct FieldState27B2A0
{
    u8 unk00[0x14];
    u32 unk14;
    u32 unk18;
    u8 unk1c[0x0C];
    u32 unk28;
    u32 unk2c;
    u32 unk30;
    u32 unk34;
} FieldState27B2A0;

typedef struct FieldSource2A550
{
    u8 unk00[0x70];
    u32 unk70;
} FieldSource2A550;

typedef struct FieldState2A550
{
    u8 unk00[0x14];
    u32 unk14;
    u32 unk18;
    u8 unk1c[0x0C];
    u32 unk28;
    u32 unk2c;
    u32 unk30;
    u8 unk34[0x1C];
    u32 unk50;
    u32 unk54;
    u8 unk58[0x10];
    u8 unk68;
    u8 unk69_0 : 1;
    u8 unk69_1_7 : 7;
} FieldState2A550;

typedef struct FieldState27A9A0
{
    u8 unk00[0x14];
    u32 unk14;
    u32 unk18;
    u8 unk1c[0x0C];
    u32 unk28;
    u32 unk2c;
    u32 unk30;
    u8 unk34[0x24C];
    FieldQword27A9A0 unk280;
    FieldQword27A9A0 unk290;
} FieldState27A9A0;


/* US Field uses shortened names for these resident copy and fill routines. */
extern "C" void* func_13A4C0(void* destination, const void* source, u32 size);
extern "C" void* func_13A678(void* destination, s32 value, u32 size);
extern "C" u32 func_11C8C0(void* table, s32 index);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_002764D0);

s32 func_00276BE0(FieldFlagState271B0* object)
{
    object->unk428 = D_001B6430->context->unkdc;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00276C00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00276CE0);

s32 func_00276DF0(void* object)
{
    D_001B6430->context->unk44->unk52_0 = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00276E20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00276E90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277110);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277160);

s32 func_002771B0(FieldFlagState271B0* object)
{
    object->unk59d_1 = object->unk428 != 0;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_002771E0);

s32 func_00277320(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277500);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_002775C0);

s32 func_00277610(FieldFlagState271B0* object)
{
    D_001B6448 = (object->unk428 & 1) != 0;
    return 1;
}

s32 func_00277630(void* object)
{
    return 1;
}

s32 func_00277640(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_002776F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_002779C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277A40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277B40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277C10);

s32 func_00277CA0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277CB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277D10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00277F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278250);

void func_002782A0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

void func_002782D0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

s32 func_00278300(FieldObject155540* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_002786D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278760);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_002788D0);

void func_00278950(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_002789F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278A80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278AE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278B70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278C00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278CF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278D90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278EE0);

void func_00278F00(FieldFloatState28F00* object, float target, float duration)
{
    if (duration == 0.0f)
    {
        object->unk340 = target;
    }
    else
    {
        object->unk34c = target;
        object->unk348 = duration;
        object->unk344 = (target - object->unk340) / duration;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00278F40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00279010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00279050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00279130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_002791E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00279280);

FieldClass155640::~FieldClass155640()
{
    ResidentContext* context = D_001B6430->context;
    if (this == context->unk1c)
    {
        context->unk1c = 0;
    }
}

void func_002793F0(FieldEntryOwner293F0* object)
{
    s32 index;
    for (index = 0; index < 26; index++)
    {
        if (object->entries[index].unk04 == 0)
        {
            object->entries[index].unk1c_0 = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_00279440);

/**
 * @brief Build the LibClass3F5B80 option bits from the field context's word at offset 0xD0.
 * @return Bits 0, 1, 2, 4 and 3 for context bits 1, 2, 3, 4 and 5.
 */
static inline u8 settings_option_flags()
{
    u32 bits = 0;
    u32 options = D_001B6430->context->unkd0;
    bits |= (options & 0x2) != 0;
    bits |= (options & 0x4) ? 0x2 : 0;
    bits |= (options & 0x8) ? 0x4 : 0;
    bits |= (options & 0x10) ? 0x10 : 0;
    bits |= (options & 0x20) ? 0x8 : 0;
    return bits;
}

void FieldClass155640::func_001E0F60()
{
    if (!unk30_1)
    {
        return;
    }
    if (unk15 == 1)
    {
        if (field_records_blocked())
        {
            return;
        }
        FieldClass150040* record = &unk1c[unk2e];
        if (!record->unk1c_1)
        {
            record->unk1c_0 = 1;
        }
        else
        {
            record->unk1c_0 = 0;
            record->unk1c_1 = 0;
        }
        if (unk7d6_0)
        {
            unk7d6_0 = 0;
            u8 flags = settings_option_flags();
            LibClass3F5B80 source;
            source.func_003F4EB0(unk7c8, unk7d4, unk7cc, flags);
            func_002797D0(&source);
            unk34.func_003F5AC0();
            unk34.func_003F4EB0(unk7c8, unk7d4, unk7cc, flags);
        }
        for (; unk2e < unk2d; unk2e++)
        {
            FieldClass150040* next = &unk1c[unk2e];
            if (!next->unk16_0 && !next->unk1c_0 && next->unk0c != -1)
            {
                break;
            }
        }
        if (unk2e >= unk2d)
        {
            unk15 = 5;
        }
        else
        {
            unk15 = 0;
        }
    }
    unk30_1 = 0;
}

void FieldClass155640::func_002797D0(LibClass3F5B80* source)
{
    for (s32 i = 0; i < 0x1A; i++)
    {
        FieldClass150040* record = &unk1c[i];
        if (i == 0)
        {
            record->unk0c = 0xD7E;
            record->unk00 = (func_002CBAE0() + 0x7FF) & ~0x7FF;
            record->unk14 = i;
            record->unk15 = 3;
            record->unk16_2 = 1;
            record->unk1c_1 = 0;
            continue;
        }
        if (i == 2 && !unk7d6_1)
        {
            record->release();
            record->unk16_0 = 1;
            continue;
        }
        if (source->func_003F4B50(i) == -1)
        {
            record->release();
            record->unk16_0 = 1;
            // The original reads the member's entry here too and ignores it.
            unk34.func_003F4B50(i);
            continue;
        }
        record->unk16_0 = 0;
        if (unk34.func_003F4B50(i) != source->func_003F4B50(i))
        {
            record->release();
            s32 size = -1;
            if (i == 2)
            {
                size = 0x9C000;
            }
            s32 value = source->func_003F4B50(i);
            record = &unk1c[i];
            record->unk0c = value;
            if (size <= 0)
            {
                record->unk00 = (func_11C8C0(D_001B65E4, record->unk0c) + 0x7FF) & ~0x7FF;
            }
            else
            {
                record->unk00 = (size + 0x7FF) & ~0x7FF;
            }
            record->unk14 = i;
            record->unk15 = 3;
            record->unk16_2 = 1;
            record->unk1c_0 = 0;
        }
    }
    unk2e = 0;
}

void FieldClass155640::func_00279B80()
{
    unk7d0 = 0x1E;
    LibClass3F5B80 source;
    u8 flags = settings_option_flags();
    source.func_003F4EB0(unk7c8, unk7d4, unk7cc, flags);
    unk2d = unk24 = 0x1A;
    if (unk15 == 1)
    {
        unk7d6_0 = 1;
        unk30_1 = 1;
        for (s32 i = 1; i < 0x1A; i++)
        {
            FieldClass150040* record = &unk1c[i];
            if (unk34.func_003F4B50(i) != source.func_003F4B50(i))
            {
                u32 word = record->unk00;
                u32 size = record->rounded_unk04();
                func_00103B20(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
                record->unk1c_0 = 0;
                record->unk1c_1 = 1;
            }
            else
            {
                u32 word = record->unk00;
                u32 size = record->rounded_unk04();
                record->unk10 = func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
                if (record->unk10)
                {
                    unk30_1 = 0;
                }
            }
        }
    }
    else
    {
        func_002797D0(&source);
        unk34.func_003F5AC0();
        unk34.func_003F4EB0(unk7c8, unk7d4, unk7cc, flags);
        while (unk2e < unk2d)
        {
            FieldClass150040* next = &unk1c[unk2e];
            if (!next->unk16_0 && !next->unk1c_0 && next->unk0c != -1)
            {
                break;
            }
            unk2e++;
        }
        if (unk2e >= unk2d)
        {
            unk15 = 5;
        }
        else
        {
            unk15 = 0;
        }
    }
}

void FieldClass155640::func_00279EA0(s32 id, s32 area, u8 kind, s8 mode, bool flag)
{
    unk7c8 = id;
    unk7cc = area;
    unk7d4 = kind;
    unk7d6_1 = flag;
    unk7d5 = mode;
    func_00279B80();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_001E0A50__16FieldClass155640Fi);

void func_0027A3E0(FieldFlagState2B320* object)
{
    object->unk4c_3 = 0;
    object->unk24 = -3;
    object->unk69_1 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027A420);

void func_0027A550(FieldState2A550* object, u32 value14, const FieldSource2A550* source,
                   const void* data, u32 value18, u32 value28, u32 value2c, u32 value30)
{
    object->unk14 = value14;
    object->unk54 = source->unk70;
    object->unk18 = value18;
    object->unk28 = value28;
    object->unk2c = value2c;
    object->unk30 = value30;
    if (data != 0)
    {
        func_13A4C0(object->unk58, data, 0x10);
    }
    else
    {
        func_13A678(object->unk58, 0, 0x10);
    }
    object->unk68 = 0;
    object->unk69_0 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027A5E0);

void func_0027A6B0(FieldFlagState2B320* object)
{
    object->unk4c_3 = 0;
    object->unk24 = -3;
    object->unk69_1 = 0;
}

void func_0027A6F0(FieldState2A550* object, u32 value14, u32 value50,
                   const void* data, u32 value18, u32 value28, u32 value2c, u32 value30)
{
    object->unk14 = value14;
    object->unk18 = value18;
    object->unk28 = value28;
    object->unk2c = value2c;
    object->unk30 = value30;
    if (data != 0)
    {
        func_13A4C0(object->unk58, data, 0x10);
    }
    else
    {
        func_13A678(object->unk58, 0, 0x10);
    }
    object->unk68 = 0;
    object->unk50 = value50;
    object->unk69_0 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027A780);

void func_0027A9A0(FieldState27A9A0* object, u32 value14,
                   const FieldQword27A9A0* first, const FieldQword27A9A0* second,
                   u32 value18, u32 value28, u32 value2c, u32 value30)
{
    object->unk28 = value28;
    object->unk2c = value2c;
    object->unk30 = value30;
    object->unk14 = value14;
    object->unk18 = value18;
    object->unk280 = *first;
    object->unk290 = *second;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027A9D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027AA60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027ABF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027AC70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027AFC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B140);

void func_0027B2A0(FieldState27B2A0* object, u32 value14, u32 value18,
                   u32 value28, u32 value34, u32 value2c, u32 value30)
{
    object->unk14 = value14;
    object->unk18 = value18;
    object->unk28 = value28;
    object->unk34 = value34;
    object->unk2c = value2c;
    object->unk30 = value30;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B2C0);

void func_0027B320(FieldFlagState2B320* object)
{
    object->unk4c_3 = 0;
    object->unk24 = -3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B350);

void func_0027B390(FieldState2B390* object, u32 value, s32 force)
{
    if (value != object->unk1e4 || force != 0)
    {
        object->unk1ea_4 = 1;
        object->unk1e4 = value;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B3D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B5F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B6D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B740);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027B7D0);

void func_0027BAF0(FieldState2BAF0* object, u32 value, s32 unused)
{
    object->unk1cc = value;
    object->unk1e8 = 1;
}

s32 func_0027BB00(FieldFlagTable2BB00* object, s8 index)
{
    FieldFlagEntry2BB00* entry = &object->entries[index];
    if (entry->unk00_2)
    {
        return 1;
    }
    return entry->unk00_0 ? 2 : 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027BB50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027BC80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027BDD0);

FieldLookupNode2BF70* func_0027BF70(FieldLookupList2BF70* object, u32 key)
{
    FieldLookupNode2BF70* node = &object->head;
    FieldLookupNode2BF70* head = node;
    while (1)
    {
        node = node->next;
        if (node == 0)
        {
            break;
        }
        if (head == node)
        {
            break;
        }
        if (key == node->unk14)
        {
            return node;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027BFC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027C020);

void func_0027C080(FieldFlagState2B320* object)
{
    if (!object->unk4c_5)
    {
        object->unk4c_0 = 1;
    }
    else
    {
        object->unk4c_3 = 1;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027C0D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027C130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027C180);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027C200);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027C2A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027CB20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027CB50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027CCD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027CE30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027CFD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027D0D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027D200);

s32 func_0027D320(FieldObject1557B0* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027D330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027D360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002764D0", func_0027D370);
