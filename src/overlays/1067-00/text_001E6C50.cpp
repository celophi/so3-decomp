#include "include_asm.h"
#include "overlays/1067-00/text_001E6C50.h"
#include "boot/resident_data.h"
#include "overlays/1067-00/text_0022DC70.h"

FieldClass1501F0::~FieldClass1501F0()
{
}

void FieldClass150220::func_001E6CF0(void* source)
{
    unk18 = source;
}

void FieldClass150220::func_001E6D00()
{
    unk20_0 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E73D0__16FieldClass1501F0FPCv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E6D80__16FieldClass1501F0FPvPCvf);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E6FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E73D0__16FieldClass150250FPCv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E6D80__16FieldClass150250FPvPCvf);

void FieldClass150220::func_001E73D0(const void* matrix)
{
    unk20_0 = 1;
}

FieldClass150250::~FieldClass150250()
{
}

void FieldClass150250::func_001E6D00()
{
    s32 i;
    unk20_0 = 0;
    for (i = 0; i < 6; i++)
    {
        unk130[i].unk0c = 0.0f;
    }
}

void func_001E7560(FieldStateReset66* object)
{
    object->unk14 = 0;
    object->unk18 = 0;
    object->unk66_1 = 0;
    object->unk10 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E7590);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E7660);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E76B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E78B0);

void func_001E7E90(FieldVectorSlots50* object, const unsigned __int128* value)
{
    object->ready = 1;
    object->slots[0] = *value;
}

void func_001E7EB0(FieldVectorSlots50* object, const unsigned __int128* value)
{
    object->ready = 1;
    object->slots[2] = *value;
}

void func_001E7ED0(FieldVectorSlots50* object, const unsigned __int128* value)
{
    object->ready = 1;
    object->slots[1] = *value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E7EF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E8050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E81D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E82B0);

FieldKeyedListNode54* func_001E8490(FieldKeyedListNode54* list, u32 key)
{
    FieldKeyedListNode54* node = list;
    for (;;)
    {
        node = node->next;
        if (list == node)
        {
            break;
        }
        if (key == node->unk54)
        {
            return node;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E84E0);

void func_001E8E00(FieldMotionParams98* object, u32 key, u16 flags, float a, float b, float c, float d, float e)
{
    object->unkac = 300.0f;
    object->unk98 = key;
    object->unk9c = a;
    object->unka0 = b;
    object->unka8 = c;
    object->unkb0 = d;
    object->unkb8 = 2;
    object->unkb4 = (object->unkb4 & ~0xFF) | flags;
    object->unka4 = e;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E8E50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E8F50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E8FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9050);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9180);

s16 func_001E9380(const FieldHalfword3A* object)
{
    return object->unk3a;
}

// Array delete through func_100BE0; needs the element type.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9390);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E93E0);

void func_001E94F0(FieldEntryArrayObject30* object)
{
    object->unk04 = 0;
    object->unk42_0_3 = 1;
    object->unk42_4_7 = 1;
    object->unk3a = 0;
    object->unk38 = 0;
    object->unk3c = -1;
    object->unk30 = 0;
    object->unk3e = -1;
    object->unk40 = -1;
    object->unk43_0 = 0;
    object->unk43_1 = 0;
}

void FieldClass150330::func_001DD7B0()
{
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E95B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9690);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9A50);

// Returns &object->unk90; subobject type unknown.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9B70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9B80);

void* func_001E9E80(void* object)
{
    return object;
}

void* func_001E9E90(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9EA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EA2E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EA540);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EA650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EA730__16FieldClass1504C0Fv);

void FieldClass1504C0::func_001DF360()
{
    unkc0++;
    if (unk30 == 0 || !unkc4_1)
    {
        return;
    }
    func_001EA730();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EAA10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EAC90);

FieldClass1504C0::~FieldClass1504C0()
{
    FieldClass150060* current;
    FieldClass150060* node = ((FieldClass150060*)unk38.unk00)->unk08;
    for (;;)
    {
        current = node;
        if (!node || (FieldClass150060*)unk38.unk00 == node)
        {
            break;
        }
        node = node->unk08;
        func_004D65C0(current);
        static_cast<FieldClass150070*>(current)->func_001DD7B0();
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EAE60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EAF60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EB070);

// Returns &object->unk20; subobject type unknown.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EB2B0);

s32 func_001EB2C0(const FieldPackedRecord0E* record)
{
    return (record->unk0a & 0x20) != 0;
}

void* func_001EB2D0(const FieldPackedRecord0E* record)
{
    return record->unk00;
}

s16 func_001EB2E0(const FieldPackedRecord0E* record)
{
    return record->unk0e;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EB2F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EB590);

void FieldClass1504C0::func_001DD7B0()
{
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

void func_001EB690(FieldCountOwner34* object, s32 count)
{
    FieldCountTarget* target = object->unk34;
    if (target)
    {
        target->unkfc = count;
        target->unk3c = 1;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EB6B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001ECDE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001ECE80);

s32 func_001ECF10(const FieldGatedObject448* object)
{
    if (!object->unk80 || !object->unk448 || object->unk8c_5)
    {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001ECF60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001ECFF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001ED160);
