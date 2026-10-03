#include "include_asm.h"
#include "overlays/1070-00/text_002E55F0.h"

/** Partial receiver whose flag byte is at offset 0x28. */
typedef struct FieldSetFlag28
{
    u8 unk00[0x28];
    u8 unk28_0 : 1;
    u8 unk28_1_7 : 7;
} FieldSetFlag28;

/** Partial receiver whose flag byte is at offset 0x50. */
typedef struct FieldSetFlag50
{
    u8 unk00[0x50];
    u8 unk50_0 : 1;
    u8 unk50_1_7 : 7;
} FieldSetFlag50;

/** Partial target with two observed float fields and an update byte. */
typedef struct FieldFloatPairTarget24
{
    u8 unk00[0x24];
    float unk24;
    float unk28;
    u8 unk2c[0x14];
    u8 unk40;
} FieldFloatPairTarget24;

/** Partial receiver with an optional mutable target at offset 0x30. */
typedef struct FieldFloatPairOwner30
{
    u8 unk00[0x30];
    FieldFloatPairTarget24* unk30;
} FieldFloatPairOwner30;

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E55F0);

void func_002E5630(void* object)
{
}

void func_002E5640(void* object)
{
}

void func_002E5650(void* object)
{
}

void func_002E5660(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E5670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E5760);

s32 func_002E5890(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E58A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E5910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E59D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E5E70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E5ED0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E60E0);

void func_002E62E0(FieldFloatResetState* object, u8 first, u8 second, u16 third, u16 fourth)
{
    object->unk26 = first;
    object->unk27 = second;
    object->unk1a = third;
    object->unk1c = fourth;
    object->unk08 = object->unk34;
    object->unk0c = object->unk38;
    object->unk22 = 0;
    object->unk28 = 0;
    object->unk2c = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6380);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E63D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E63F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E67B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6920);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E69F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6AE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6BA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6C40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6CC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6D40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6DE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6E60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6EE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6F50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E6FF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7070);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E70F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7200);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7280);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E73A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7420);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E74A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E75C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7640);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E76E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E77E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7880);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7900);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7980);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7A20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7AA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7B20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7BC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7C40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7CC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7D60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7DE0);

s32 func_002E7E60(void* object)
{
    return 3;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7E70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7EA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E7FC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E8910);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E8E40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9210);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9550);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9590);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E95C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9660);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E99F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9A90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9AF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9B30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9B50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9D20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9E80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002E9E90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EA090);

void func_002EA0E0(FieldFlagOwner4C* object)
{
    if (object->unk4c != 0)
    {
        object->unk4c->unk4d_4 = 1;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EA110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EA1E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EA280);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EA320);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EA410);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EA480);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EB760);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EB7D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EB8C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBA20);

s32 func_002EBA30(void* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBA40);

void func_002EBA70(void* object)
{
}

s32 func_002EBA80(const FieldBufferSlots* object, s32 index)
{
    return object->unk134[index];
}

void* func_002EBA90(const FieldBufferSlots* object, s32 index)
{
    return object->unk128[index];
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBAA0);

FieldResourceRecord* func_002EBB20(const FieldBufferSlots* object, s32 index)
{
    if (index < 0)
    {
        return 0;
    }
    if (object->unk114 == 0)
    {
        return 0;
    }
    FieldResourceRecord* record = (FieldResourceRecord*)(((u32)object->unk114 + 127) & ~0x7F);
    for (s32 position = 0; ; position++)
    {
        if (position == index)
        {
            return record;
        }
        record = record->next_offset == 0 ? 0 : (FieldResourceRecord*)((u8*)record + record->next_offset);
        if (record == 0)
        {
            break;
        }
    }
    return 0;
}

u8 func_002EBBA0(FieldBufferSlots* object, void* allocation, s32 size)
{
    object->unk118 = size;
    if (object->unk118 <= 0)
    {
        return 0;
    }
    if (object->unk114 != 0)
    {
        return 0;
    }
    object->unk114 = allocation;
    return 1;
}

void* func_002EBBE0(const FieldBufferSlots* object, u8 index)
{
    if (index >= 64)
    {
        return 0;
    }
    return (void*)(((u32)object->unk14[index] + 127) & ~0x7F);
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBC20);

u8 func_002EBCA0(FieldBufferSlots* object, void* allocation, u8 index)
{
    if (allocation == 0)
    {
        return 0;
    }
    if (index < 0)
    {
        return 0;
    }
    if (index >= 64)
    {
        return 0;
    }
    if (object->unk14[index] != 0)
    {
        return 0;
    }
    object->unk14[index] = allocation;
    return 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBD10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBD20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBE90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBF60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBFC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EBFF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EC620);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EC670);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EC7B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EC8C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EC930);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EC9C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ECB30);

s32 func_002ECBD0(void* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ECBE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ECC10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ECF10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ECF20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ED100);

void func_002ED110(const void* object, float first, float second)
{
    const FieldFloatPairOwner30* state = (const FieldFloatPairOwner30*)object;
    FieldFloatPairTarget24* target = state->unk30;

    if (target != 0)
    {
        target->unk24 = first;
        target->unk28 = second;
        target->unk40 = 1;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ED140);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ED8B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ED900);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002ED960);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EDBA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EDBB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EDC60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE2B0);

void func_002EE2D0(FieldResetStateCC* object)
{
    object->unkcc = 0;
    object->unkd0 = 0;
    object->unk108 = 0;
    object->unk10c = 0;
    object->unk10e = 0;
    object->unk110 = 0;
    object->unk111 = 0;
    object->unk112 = 0;
    object->unk113 = 0;
    object->unk114 = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE450);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE4C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE5A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE7D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE880);

void func_002EE900(void* object)
{
}

void func_002EE910(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE920);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EE9B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EEDF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EEF80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EEFE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF110);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF210);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF280);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF360);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF540);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF710);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF8C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EF980);

void func_002EFA60(void* object)
{
}

s32 func_002EFA70(const FieldResourceSlots* object, s32 index, FieldResourceStateValues* output)
{
    if ((object->unk12ac & 0x1) == 0)
    {
        return 0;
    }
    u64 first = object->unk10a8[index].unk00;
    u64 second = object->unk10a8[index].unk08;
    output->unk04 = (first >> 14) & 0x3F;
    output->unk05 = (first >> 20) & 0x3F;
    output->unk06 = (first >> 26) & 0xF;
    output->unk07 = (first >> 30) & 0xF;
    output->unk00 = first & 0x3FFF;
    output->unk02 = (second >> 37) & 0x3FFF;
    return 1;
}

s32 func_002EFAF0(FieldResourceSlots* object, void* resource, void* target)
{
    for (s32 index = 0; index < 16; index++)
    {
        if (object->unk10a8[index].unk10 == 0)
        {
            object->unk10a8[index].unk10 = resource;
            object->unk10a8[index].unk14 = target;
            return index;
        }
    }
    return -1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EFB40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EFB70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002EFC20);

void func_002F0080(void* object)
{
}

void func_002F0090(void* object)
{
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F00A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F00B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0160);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F01E0);

s32 func_002F02C0(void* object)
{
    return 5;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F02D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F02E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F02F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0310);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0320);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0330);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0340);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0350);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0360);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0370);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0380);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0390);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F03A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F03B0);

s32 func_002F03C0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F03D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F04A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F0590);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F17F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F1960);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F19B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F1A50);

void func_002F2080(FieldByteFlags70* object)
{
    object->unk70_2 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F20A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F21D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F21E0);

s32 func_002F2280(void* object)
{
    return 9;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F2290);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F22C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F2F30);

void func_002F2FD0(void* object)
{
    FieldSetFlag28* state = (FieldSetFlag28*)object;

    state->unk28_0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F2FF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F32C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F33F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F3400);

s32 func_002F34A0(void* object)
{
    return 14;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F34B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F34E0);

void func_002F3C90(void* object)
{
    FieldSetFlag50* state = (FieldSetFlag50*)object;

    state->unk50_0 = 1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F3CB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F3D80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F3D90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F3F50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F4010);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F4130);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F4250);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F42A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F4330);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F43C0);

void func_002F43F0(FieldResetState40* object)
{
    object->unk48 = 0;
    object->unk4c = -1;
    object->unk40 = 0;
    object->unk4e = -1;
    object->unk50 = -1;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F4410);

void func_002F4550(FieldFloatSequenceState* object, FieldFloatPairEntry* values, s32 count, float first, float second)
{
    object->unk90 = first;
    object->unk98 = second / first;
    object->unk9c = 0.0f;
    object->unk94 = 0.0f;
    object->unka4 = count;
    object->unka0 = values;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F4580);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F45D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F47C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F4AD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F4D10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F4EC0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F52B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F5300);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_002E55F0", func_002F5470);
