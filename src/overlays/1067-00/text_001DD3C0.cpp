#include "include_asm.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/text_0021DB80.h"
#include "overlays/1067-00/text_0022DC70.h"

// Not code: 64 zero bytes at the start of .text.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DD3C0);

void FieldClass1DD400::func_001DD400()
{
}

void FieldClass150070::func_001DD410()
{
}

void func_001DD420(FieldAttachedObject70* object, void* attached)
{
    object->unk70 = attached;
}

void func_001DD430(void* object)
{
}

// Reads an unresolved $gp-relative global.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DD440);

s32 func_001DD490(const void* object)
{
    return 4;
}

FieldClass14FE30::~FieldClass14FE30()
{
    func_004D65C0(&unkA0);
}

void func_001DD570(FieldFlaggedListObject* list)
{
    FieldFlaggedListObject* node = list;
    for (;;)
    {
        node = node->next;
        if (!node || list == node)
        {
            break;
        }
        if (node->unk78 & 8)
        {
            func_002379A0(node, 1);
        }
    }
}

// Reads an unresolved $gp-relative global.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DD5E0);

void func_001DD6E0(FieldFlaggedListObject* list)
{
    FieldFlaggedListObject* node = list;
    for (;;)
    {
        node = node->next;
        if (!node || list == node)
        {
            break;
        }
        if (node->unk78 & 2)
        {
            node->unk208 = 0;
        }
    }
}

// Virtual calls; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DD730);

void FieldClass150070::func_001DD7B0()
{
    delete this;
}

FieldClass150070::~FieldClass150070()
{
    func_004D65C0(this);
}

// Virtual calls and an unresolved $gp-relative global.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DD860);

// 128-bit copy; needs a 16-byte vector type.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DD960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DD9A0);

void func_001DDB30(FieldFlaggedListObject* list)
{
    FieldFlaggedListObject* node = list;
    for (;;)
    {
        node = node->next;
        if (!node || list == node)
        {
            break;
        }
        if (node->unk78 & 2)
        {
            func_00227130(node);
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DDBA0);

void* func_001DDCD0(void* object)
{
    return object;
}

bool func_001DDCE0(const FieldFloatGateState7C* object)
{
    if (!func_00204420(object))
    {
        return false;
    }
    return object->unk8c_5 ? false : true;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DDD30);

// Returns &object->unk80; subobject type unknown.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DDF40);

FieldFlaggedListObject* func_001DDF50(FieldFlaggedListObject* list, s32 key)
{
    FieldFlaggedListObject* node = list;
    for (;;)
    {
        node = node->next;
        if (!node || list == node)
        {
            break;
        }
        if (!node->unk8c_2 && key == node->unk74 && node->unk7c != 0)
        {
            return node;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DDFC0);

void func_001DE3B0(void* object)
{
}

void func_001DE3C0(void* object)
{
}

// 128-bit copies; needs a 16-byte vector type.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DE3D0);

// Calls Lib func_004728A0; needs its declaration and symbol mapping.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DE400);

// Reads an unresolved $gp-relative global.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DE470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DE4F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DE8B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DE9C0);

void func_001DEA80(FieldSlotRecordOwner* object)
{
    s32 i;
    if (object->unk1c)
    {
        for (i = 0; i < object->unk24; i++)
        {
            FieldSlotRecord20* record = &object->unk1c[i];
            record->unk0c = -1;
            record->unk04 = 0;
            record->unk10 = 0;
            record->unk16_0 = 0;
            record->unk16_1 = 1;
            record->unk08_0 = 0;
            record->unk16_2 = 0;
            record->unk14 = 0;
            record->unk15 = 0;
        }
    }
    object->unk20 = 0;
    object->unk2f = 0;
    object->unk2d = 0;
    object->unk2e = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DEB50);

FieldClass150010::~FieldClass150010()
{
}

FieldClass150060::~FieldClass150060()
{
}

FieldClass150050::~FieldClass150050()
{
}
