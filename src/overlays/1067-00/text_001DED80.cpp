#include "include_asm.h"
#include "boot/resident_data.h"
#include "overlays/1067-00/text_001DED80.h"
#include "overlays/1067-00/text_0022DC70.h"

// Reads an unresolved $gp-relative global.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DED80);

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DEDF0);

FieldFlaggedListObject* func_001DEE30(FieldFlaggedListObject* list, s32 key, u32 mask)
{
    FieldFlaggedListObject* node = list;
    for (;;)
    {
        node = node->next;
        if (!node || list == node)
        {
            break;
        }
        if ((mask & node->unk78) && key == node->unk70)
        {
            return node;
        }
    }
    return 0;
}

void func_001DEE90(FieldFlaggedListObject* list)
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
            func_00234000(node);
        }
    }
}

void func_001DEF00(FieldFlaggedListObject* list)
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
            func_00233620(node);
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DEF70);

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF040);

// Deleting destructor; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF100);

// Deleting destructor; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF1C0);

void func_001DF220(void* object)
{
}

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF230);

// Deleting destructor; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF260);

s32 func_001DF2B0(const void* object)
{
    return 0;
}

s32 func_001DF2C0(const void* object)
{
    return 0;
}

s32 func_001DF2D0(const void* object)
{
    return 0;
}

s32 func_001DF2E0(const void* object)
{
    return 0;
}

void func_001DF2F0(void* object)
{
}

void func_001DF300(void* object)
{
}

s32 FieldClass150010::func_001DF3D0()
{
    return 3;
}

void FieldClass150010::func_001DD7B0()
{
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

u8 func_001DF350(const FieldByteState14* object)
{
    return object->unk14;
}

void FieldClass150070::func_001DF360()
{
}

void func_001DF370(void* object)
{
}

// Tail call to func_0023AD00; void or forwarded return is unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF380);

s32 FieldClass150070::func_001DF3D0()
{
    return 3;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF3E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF550);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF780);

// Calls resident func_121FE0; needs its declaration and symbol mapping.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF800);

void func_001DF850(FieldEntryArrayObject* object)
{
    object->unk4c = 0;
    func_001DFAE0(object);
}

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF870);

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF8D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF930);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF990);

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF9F0);

void func_001DFA30(const FieldEntryArrayObject* object, float* out)
{
    *out = object->unk50;
}

void func_001DFA40(const FieldEntryArrayObject* object, float* out)
{
    FieldArrayEntry10* entries = object->unk04;
    if (entries)
    {
        *out = entries[object->unk20 - 1].unk04 - entries[0].unk04;
    }
}

// Deleting destructor; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DFA70);

void func_001DFAE0(FieldEntryArrayObject* object)
{
    object->unk04 = 0;
    object->unk2a_0_3 = 1;
    object->unk2a_4_7 = 1;
    object->unk22 = 0;
    object->unk20 = 0;
    object->unk24 = -1;
    object->unk18 = 0;
    object->unk26 = -1;
    object->unk28 = -1;
    object->unk2b_0 = 0;
    object->unk2b_1 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DFB70);

void func_001DFC10(FieldEntryArrayObject* object, s32 value)
{
    object->unk2a_0_3 = value;
    object->unk2b_0 = object->unk2a_0_3 == 4 || object->unk2a_4_7 == 4;
}

void func_001DFC70(FieldEntryArrayObject* object, s32 value)
{
    object->unk2a_4_7 = value;
    object->unk2b_0 = object->unk2a_0_3 == 4 || object->unk2a_4_7 == 4;
}

s32 func_001DFCD0(const FieldEntryArrayObject* object)
{
    return object->unk18;
}

s16 func_001DFCE0(const FieldEntryArrayObject* object)
{
    return object->unk20;
}

s16 func_001DFCF0(const FieldEntryArrayObject* object)
{
    return object->unk22;
}

s32 func_001DFD00(const void* object)
{
    return 0;
}

s32 func_001DFD10(const void* object)
{
    return 0;
}

s32 func_001DFD20(const void* object)
{
    return 0;
}

void func_001DFD30(void* object)
{
}

float func_001DFD40(const void* object)
{
    return 0.0f;
}

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DFD50);

FieldArrayEntry10* func_001DFD80(const FieldEntryArrayObject* object)
{
    return object->unk04;
}

// Array delete through func_100BE0; needs the element type.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DFD90);

float func_001DFDE0(const FieldEntryArrayObject* object, float value)
{
    FieldArrayEntry10* entries = object->unk04;
    s32 last = object->unk20 - 1;
    float first = entries[0].unk00;
    float span = entries[last].unk00 - first;
    float cycles = (value - first) / span;
    s32 count;
    if (cycles < 0.0f)
    {
        cycles -= 1.0f;
    }
    count = cycles;
    if (count != 0)
    {
        return value - count * span;
    }
    return value;
}

// Loop load placement and register allocation not matched yet.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DFE70);

float func_001DFED0(const FieldEntryArrayObject* object)
{
    s32 last;
    if (object->unk20 < 2)
    {
        return 0.0f;
    }
    last = object->unk20 - 1;
    return object->unk04[last].unk00 - object->unk04[0].unk00;
}

s32 func_001DFF20(const FieldEntryArrayObject* object, float key)
{
    s16 count = object->unk20;
    s32 i;
    for (i = 0; i < count; i++)
    {
        if (key == object->unk04[i].unk00)
        {
            return 1;
        }
    }
    return 0;
}

void func_001DFF70(FieldEntryArrayObject* object, s32 count, FieldArrayEntry10* entries)
{
    s32 last = count - 1;
    object->unk2b_1 = 1;
    object->unk04 = entries;
    object->unk22 = count;
    object->unk20 = count;
    object->unk1c = object->unk04[last].unk00 - object->unk04[0].unk00;
}

s32 func_001DFFC0(const FieldEntryArrayObject* object, s32 index, float* key, float* x, float* y, float* z)
{
    if (object->unk04 == 0)
    {
        return 0;
    }
    if (index >= object->unk22)
    {
        return 0;
    }
    if (key)
    {
        *key = object->unk04[index].unk00;
    }
    if (x)
    {
        *x = object->unk04[index].unk04;
    }
    if (y)
    {
        *y = object->unk04[index].unk08;
    }
    if (z)
    {
        *z = object->unk04[index].unk0c;
    }
    return 1;
}

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E0080);

s32 func_001E0100(FieldEntryArrayObject* object, s32 index, float key, const float* x, const float* y, const float* z)
{
    s16 count;
    s32 i;
    if (object->unk04 == 0)
    {
        return 0;
    }
    count = object->unk20;
    if (index >= count)
    {
        return 0;
    }
    if (count >= object->unk22)
    {
        return 0;
    }
    for (i = count; i > index; i--)
    {
        object->unk04[i] = object->unk04[i - 1];
    }
    object->unk04[index].unk04 = *x;
    object->unk04[index].unk08 = *y;
    object->unk04[index].unk0c = *z;
    object->unk04[index].unk00 = key;
    if (index == object->unk20 - 1)
    {
        object->unk1c = key - object->unk04[0].unk00;
    }
    object->unk20++;
    return 1;
}

s32 func_001E0220(FieldEntryArrayObject* object, s32 index, float key, const float* x, const float* y, const float* z)
{
    if (object->unk04 == 0)
    {
        return 0;
    }
    if (index >= object->unk22)
    {
        return 0;
    }
    object->unk04[index].unk04 = *x;
    object->unk04[index].unk08 = *y;
    object->unk04[index].unk0c = *z;
    object->unk04[index].unk00 = key;
    if (index == object->unk20 - 1)
    {
        object->unk1c = key - object->unk04[0].unk00;
    }
    return 1;
}

s32 func_001E02C0(FieldEntryArrayObject* object, const float* x, const float* y, const float* z, float key)
{
    if (object->unk04 == 0)
    {
        return 0;
    }
    if (object->unk20 >= object->unk22)
    {
        return 0;
    }
    object->unk04[object->unk20].unk04 = *x;
    object->unk04[object->unk20].unk08 = *y;
    object->unk04[object->unk20].unk0c = *z;
    object->unk04[object->unk20].unk00 = key;
    object->unk1c = key - object->unk04[0].unk00;
    object->unk20++;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E0380);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E07A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E0A50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E0F60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1100);

void func_001E11E0(FieldFloatSpan1C* object, const float* a, const float* b, const float* c, const float* d, float start, float end)
{
    object->unk00 = *a;
    object->unk10 = start;
    object->unk08 = *b;
    object->unk04 = *c;
    object->unk14 = end;
    object->unk0c = *d;
    object->unk18 = end - start;
    if (object->unk18 == 0.0f)
    {
        object->unk18 = 1.0f;
    }
}

// Mirror-branch scheduling not matched yet.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1230);

// Index loop strength reduction not matched yet.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1310);

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1470);

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E14A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E14D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1500);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1530);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1540);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1550);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1560);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1570);

// Compiler-generated this-adjustment thunk; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1580);
