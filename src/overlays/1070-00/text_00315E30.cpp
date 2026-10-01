#include "include_asm.h"
#include "overlays/1070-00/text_00315E30.h"

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00315E30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003160A0);

s32 func_00316440(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316450);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316520);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003165B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316610);

void func_00316670(FieldMarkedObjectSlots* object, void* target)
{
    for (s32 index = 0; index < 32; index++)
    {
        if (object->unk18[index] == target)
        {
            object->unk98[index] = 1;
            return;
        }
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003166C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316800);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003168F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003169A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003169B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316A00);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316A20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316A50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316BF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316C30);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316CF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316D90);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316E50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316E60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00316E70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003171A0);

void func_003173D0(FieldHalfwordBuckets* object)
{
    for (s32 index = 0; index < 750; index++)
    {
        object->unk2f0c[index] = 0;
    }
    object->unk2f04 = 0;
    object->unk2f08 = 0;
    object->unk2f0a = 0;
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00317460);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00317570);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003177E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00317970);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00317A30);

u16 func_00317CD0(const FieldHalfwordBuckets* object, u8 category, u16 index)
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

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00317D20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00317FB0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00317FD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00318060);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00318100);

extern "C" u8 func_003186B0(const FieldStateTargets* object, u8 key)
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

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00318700);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00318750);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003187F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00318890);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003189D0);

void func_00318A30(FieldStateTargets* object)
{
    FieldStateTargetEntry* entry = object->entries;
    for (s32 index = 0; index < object->unk87; index++)
    {
        entry->target->unk0a = 2;
        entry++;
    }
}

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00318A70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00318B40);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00318C20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00319060);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00319150);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00319170);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003192B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003194A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_003198C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00319A10);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00319B60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00319B80);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00319CD0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_00319DE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A330);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A3C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A4C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A5F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A610);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A6D0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A6E0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A770);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A780);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A7A0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A7F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031A8C0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031AA60);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031AA70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031AC20);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031ADE0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031AEF0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031B020);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031B1B0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031B280);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031B6F0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031BA70);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031BD50);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031BEA0);

INCLUDE_ASM("build/overlays/1070-00/asm/nonmatchings/text_00315E30", func_0031BF40);
