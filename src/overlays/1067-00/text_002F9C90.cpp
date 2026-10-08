#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_002F9C90.h"

/** Partial receiver with a byte at offset 0x60. */
struct FieldByte60F9C90
{
    u8 pad[0x60];
    u8 value;
};

/** Partial receiver with a byte at offset 4. */
struct FieldByte4F9C90
{
    u8 pad[4];
    u8 value;
};

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

extern "C" void func_002FB840(void* object);

/** @brief Forward the object to func_002FB840. @param object Object to forward. */
extern "C" void func_002FAE00(void* object)
{
    func_002FB840(object);
}

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

/** @brief Forward the object to func_002FB840. @param object Object to forward. */
extern "C" void func_002FBFC0(void* object)
{
    func_002FB840(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FBFE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC880);

/** @brief Forward the object to func_002FB840. @param object Object to forward. */
extern "C" void func_002FC9D0(void* object)
{
    func_002FB840(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC9F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FCB40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FCC50);

extern "C" void func_002FD1B0(FieldFloatState5C* object, float first, float second, float third, float fourth, float fifth)
{
    object->enabled = 1;
    object->values[0] = first;
    object->values[1] = second;
    object->values[2] = third;
    object->values[3] = fourth;
    object->values[4] = fifth;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD1D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD220);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD2E0);

extern "C" s32 func_002FD480(const FieldStatus14* object)
{
    return object->status == 0;
}

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

FieldClass15BB90::~FieldClass15BB90()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE790);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 3.
 */
s32 func_002FE870(FieldClass150070* object)
{
    return 3;
}

extern "C" void func_002FE880(FieldByte60F9C90* object)
{
    object->value = 9;
}

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_002FE890(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE8C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FEA60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FEC10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FECF0);

extern "C" void func_4D00B0(void* object);

/** @brief Forward the object to func_4D00B0. @param object Object to forward. */
extern "C" void func_002FED30(void* object)
{
    func_4D00B0(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FED50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FED80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FFF50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_00300D20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_00300EB0);

extern "C" void func_00301090(FieldByte4F9C90* object)
{
    object->value = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_003010A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_003010B0);
