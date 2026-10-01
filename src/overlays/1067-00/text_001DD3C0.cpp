#include "include_asm.h"
#include "boot/resident_data.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/text_0024C4B0.h"
#include "overlays/0002-01/text_0046AE20.h"
#include "overlays/1067-00/text_0021DB80.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_0021FB80.h"

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

void FieldClass14FE30::func_001DD7B0()
{
    FieldClass150070& base = *this;
    func_004D65C0(&base);
    func_0011ED90(D_001B65F4, static_cast<FieldClass150070*>(this));
}

s32 FieldClass14FE30::func_001DF3D0()
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

// Virtual calls on list items; needs the item class.
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

// Virtual calls on list items; needs the item class.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DD730);

void FieldClass150070::func_001DD7B0()
{
    delete this;
}

// Virtual calls on list items; needs the item class.
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

void func_001DE400(FieldFlaggedListObject* list, s32 flag)
{
    FieldFlaggedListObject* node = list;
    for (;;)
    {
        node = node->next;
        if (!node || list == node)
        {
            break;
        }
        if (node->unk7c)
        {
            func_004728A0(node->unk7c, flag != 0, 0);
        }
    }
}

void func_001DE470(FieldFlaggedListObject* list, s32 only_keyed)
{
    FieldFlaggedListObject* node = list->next;
    for (;;)
    {
        FieldFlaggedListObject* current = node;
        if (!node || list == node)
        {
            break;
        }
        node = node->next;
        if (!only_keyed || current->unk70)
        {
            func_0024CE10(D_001B6430->context->unk40, current);
        }
    }
}

// VU0 vector-length code; needs the vector class and the D_155640 class.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DE4F0);

void FieldClass14FFB0::func_001DE8B0(s32 count)
{
    if (unk30_0)
    {
        if (unk1c)
        {
            delete[] unk1c;
        }
        unk1c = new(0) FieldClass150040[count];
    }
    else
    {
        void* heap = func_00100C80(D_001B6430->context->unk6c);
        if (unk1c)
        {
            delete[] unk1c;
        }
        unk1c = new(0) FieldClass150040[count];
        func_00100C80(heap);
    }
    unk24 = count;
}

FieldClass150040::FieldClass150040()
{
    unk1c_0 = 0;
    unk1c_1 = 0;
}

void FieldClass14FFB0::func_001DEA80()
{
    s32 i;
    if (unk1c)
    {
        for (i = 0; i < unk24; i++)
        {
            FieldClass150040* record = &unk1c[i];
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
    unk20 = 0;
    unk2f = 0;
    unk2d = 0;
    unk2e = 0;
}

FieldClass14FFB0::FieldClass14FFB0()
{
    unk2c = 0x80;
    unk24 = 0;
    unk28 = 0x34BC0;
    unk1c = 0;
    unk30_1 = 0;
    unk30_0 = 0;
    func_001DEA80();
}
