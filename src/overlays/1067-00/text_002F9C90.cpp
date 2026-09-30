#include "include_asm.h"
#include "overlays/1067-00/text_002F9C90.h"


INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002F9C90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002F9FD0);

void func_002FA210(FieldHalfwordBuckets* object)
{
    for (s32 index = 0; index < 750; index++)
    {
        object->unk2f0c[index] = 0;
    }
    object->unk2f04 = 0;
    object->unk2f08 = 0;
    object->unk2f0a = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FA2A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FA3B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FA620);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FA7B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FA870);

u16 func_002FAB20(const FieldHalfwordBuckets* object, u8 category, u16 index)
{
    u16 value = 0;
    if (category < 8)
    {
        const FieldHalfwordBucket* bucket = object->buckets + category;
        if (index < bucket->count)
        {
            value = bucket->values[index];
        }
    }
    return value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FAB70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FAE00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FAE20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FAEB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FAF50);

u8 func_002FB510(const FieldStateTargets* object, u8 key)
{
    const u8 count = object->unk87;
    u8 result = 0;
    const FieldStateTargetEntry* entry = object->entries;
    for (s32 i = 0; i < count; i++, entry++)
    {
        if (key == entry->unk1c)
        {
            result = entry->unk1f;
            break;
        }
    }
    return result;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB5B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB840);

void func_002FB8A0(FieldStateTargets* object)
{
    FieldStateTargetEntry* entry = object->entries;
    for (s32 index = 0; index < object->unk87; index++)
    {
        entry->target->unk0a = 2;
        entry++;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB8E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB9B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FBA90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FBED0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FBFC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FBFE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC880);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC9D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC9F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FCB40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FCC50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD1B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD1D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD220);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD2E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD800);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FDA70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FDC00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FDCD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE020);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE370);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE870);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE880);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE890);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE8C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FEA60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FEC10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FECF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FED30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FED50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FED80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FFF50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_00300D20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_00300EB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_00301090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_003010A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_003010B0);
