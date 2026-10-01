#include "include_asm.h"
#include "boot/resident_data.h"
#include "overlays/0002-01/text_004CD3A0.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/text_0024C4B0.h"
#include "overlays/0002-01/text_0046AE20.h"
#include "overlays/0002-01/text_0045AD10.h"
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

void func_001DD5E0(FieldClass150060* list)
{
    void* entries[0x20];
    FieldClass150060* link = list;
    for (;;)
    {
        link = link->unk08;
        if (!link || list == link)
        {
            break;
        }
        FieldClass150F90* object = static_cast<FieldClass150F90*>(link);
        if ((object->unk78 & 0x8) && object->func_00204420())
        {
            void* table = object->unk7c;
            if (table)
            {
                s32 count = 0;
                void* entry = func_00473940(table, 0);
                while (entry && count < 0x20)
                {
                    entries[count++] = entry;
                    entry = func_00472EB0(table, entry);
                }
                if (count > 0)
                {
                    func_004D4010(D_001B661C, count, entries);
                }
            }
        }
    }
}

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

void func_001DD730(FieldClass150060* list)
{
    FieldClass150060* current;
    FieldClass150060* node = list->unk08;
    for (;;)
    {
        current = node;
        if (!node || list == node)
        {
            break;
        }
        node = node->unk08;
        func_004D65C0(current);
        static_cast<FieldClass150070*>(current)->func_001DD7B0();
    }
}

void FieldClass150070::func_001DD7B0()
{
    delete this;
}

// Needs FieldClass153330 (slot 37) and the unknown type-0x20 class.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DD3C0", func_001DD860);

void FieldClass152F00::func_00205710(const FieldVec4A* value)
{
    FieldClass150EB0::func_00205710(value);
    unk530 = *value;
}

// Slot 12 argument conversion differs (97.37%); see working notes.
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

s32 func_001DDBA0(FieldClass150060* list, FieldClass151510* self, void* arg0, void* arg1)
{
    if (self->test_unk204(0x400000))
    {
        return 0;
    }
    FieldClass150060* link = list;
    FieldClass150060* skip = self;
    for (;;)
    {
        link = link->unk08;
        if (!link || list == link)
        {
            break;
        }
        if (link == skip)
        {
            continue;
        }
        FieldClass150F90* object = static_cast<FieldClass150F90*>(link);
        u32 flags = object->unk78;
        if (!(flags & 0x1))
        {
            continue;
        }
        if ((flags & 0x10000) && !(flags & 0x200))
        {
            continue;
        }
        FieldClass151510* body = static_cast<FieldClass151510*>(object);
        if (!body->func_00204420())
        {
            continue;
        }
        if (body->test_unk204(0x8))
        {
            continue;
        }
        FieldClass154D20* shape = body->unkA8;
        if (shape && func_0045BD20(shape->func_001DDCD0(), arg0, arg1))
        {
            return 1;
        }
    }
    return 0;
}

FieldClass1515D0* FieldClass154D20::func_001DDCD0()
{
    return this;
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

FieldClass1515D0* FieldClass153570::func_001DDCD0()
{
    return &unk80;
}

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

void FieldClass152430::func_001DE3D0()
{
    unk170 = unk20;
    unk190 = FieldVec4A(0.0f, 0.0f, 0.0f, 1.0f);
}

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
