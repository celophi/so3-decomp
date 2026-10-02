#include "include_asm.h"
#include "boot/resident_data.h"
#include "sdk/boot/syscalls_00121940.h"
#include "overlays/1067-00/text_001DED80.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_002DBC50.h"

/** Partial owner of a keyframe track at offset 0x90 (the class with vtable D_15B890). */
struct FieldTrackOwner15B890
{
    u8 unk00[0x90];
    FieldClass150090* unk90;
};

/**
 * @brief Run func_002DDA70 on the owner, then destroy and clear its keyframe track at offset 0x90.
 * @param object Owner; virtual slot 15 of D_15B890.
 */
extern "C" void func_001DF040(FieldTrackOwner15B890* object);

extern "C" void func_433AA0();
extern "C" s32 func_433880(void*, s32);
extern "C" s32 func_139700(s32, void*);
extern "C" s32 func_0023AEB0(FieldClass1530D0* owner, FieldClass150070* loader);

/**
 * @brief Read 0x80 bytes into buffer, retrying up to eight times while the node allows it.
 * @param owner Record loader whose word at offset 0x10 points to its FieldClass1530D0 list.
 * @param buffer Destination passed to the read.
 * @param mode Nonzero to read through func_433AA0/func_433880, zero for func_139700.
 * @return The first nonzero read result, or 0 once the node's word at 0x20 is 1, func_0023AEB0
 *         fails or eight reads fail. Same body as func_001F9A80 in text_001ED7E0.
 */
extern "C" s32 func_001E1100(FieldClass150070* owner, void* buffer, s32 mode);

bool func_001DED80(const FieldFloatGateState7C* object)
{
    ResidentContext* context = D_001B6430->context;
    if (!context->unk08->unkf5_5 || context->unkdd.unk7 || context->unkde_1)
    {
        return false;
    }
    return func_00204420(object);
}

void func_001DEDF0(void* list, void* object)
{
    func_004D65C0(object);
    static_cast<FieldClass150070*>(object)->func_001DD7B0();
}

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

void func_001DF040(FieldTrackOwner15B890* object)
{
    func_002DDA70(object);
    if (object->unk90)
    {
        object->unk90->func_001DF230();
        object->unk90 = 0;
    }
}

// Deleting destructor; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF090);

// 99.94%: the FieldClass1DD400 base sits at 0x90, but FieldClass150070 ends at 0x8C
// and no vtable is stored for anything in between (working/matching/ctor-layout).
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", __ct__16FieldClass14FE30Fv);


void func_001DF220(void* object)
{
}

// Virtual call; needs recovered classes.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001DF230);


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

u8 FieldClass150010::func_001DF350()
{
    return unk14;
}

void FieldClass150070::func_001DF360()
{
}

void FieldClass1DD400::func_001DDB30(void* arg)
{
}

s32 FieldClass150040::func_0023AD00()
{
    unk1c_0 = 0;
    unk1c_1 = 0;
    return FieldClass1530C0::func_0023AD00();
}

s32 FieldClass150070::func_001DF3D0()
{
    return 3;
}

void FieldClass14FFB0::func_001DF3E0()
{
    FieldClass150040* record = &unk1c[unk2e];
    if (record->rounded_unk04())
    {
        FieldClass1DD400* owner = this;
        u32 first = record->unk00;
        func_00103E70(D_001B65E8, record->unk0c, record->rounded_unk04(), 0x80000000, unk28, owner, first, 0, 1);
        u32 word = record->unk00;
        u32 size = record->rounded_unk04();
        record->unk10 = func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
        unk15 = 1;
        unk30_1 = 0;
    }
}

FieldClass14FFB0::~FieldClass14FFB0()
{
    if (unk1c)
    {
        func_001DF780();
        delete[] unk1c;
        unk1c = 0;
    }
}

s32 FieldClass14FFB0::func_001DF640()
{
    switch (unk15)
    {
    case 1:
    {
        FieldClass150040* record = unk1c;
        for (s32 i = 0; i < unk2d; i++, record++)
        {
            const FieldClass1530C0* entry = record;
            if (!entry->unk08_0)
            {
                u32 word = entry->unk00;
                u32 size = entry->rounded_unk04();
                func_00103B20(D_001B65E8, entry->unk0c, size, 0x80000000, word, 0);
            }
        }
        unk15 = 7;
        break;
    }
    case 9:
    case 10:
        unk15 = 7;
        break;
    case 7:
        break;
    default:
        func_001DD7B0();
        return 1;
    }
    return 0;
}

void FieldClass14FFB0::func_001DF780()
{
    s32 i;
    for (i = 0; i < unk24; i++)
    {
        FieldClass150040* record = &unk1c[i];
        record->func_0023AD00();
    }
}

void FieldClass14FFB0::func_001DDB30(void* arg)
{
    if (!unk30_1)
    {
        func_00121FE0(0);
        unk30_1 = 1;
    }
}

void func_001DF850(FieldEntryArrayObject* object)
{
    object->unk4c = 0;
    func_001DFAE0(object);
}

s32 FieldClass14FEB0::func_001E1470(const float* x, const float* y, const float* z, float key)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return func_001E02C0(x, y, z, key);
}

s32 FieldClass14FEB0::func_001E14A0(s32 index, float key, const float* x, const float* y, const float* z)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return func_001E0220(index, key, x, y, z);
}

s32 FieldClass14FEB0::func_001E14D0(s32 index, float key, const float* x, const float* y, const float* z)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    return func_001E0100(index, key, x, y, z);
}

void FieldClass14FEB0::func_001E1500(const float* x, const float* y, const float* z, float key)
{
    float y_value;
    float z_value;
    z_value = (z == 0) ? 0.0f : *z;
    z = &z_value;
    y_value = (y == 0) ? 0.0f : *y;
    y = &y_value;
    func_001E0080(x, y, z, key);
}

void FieldClass14FEB0::func_001DF300()
{
    float zero = 0.0f;
    func_001E1500(&zero, &zero, &zero, 0.0f);
}

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

FieldClass150090::~FieldClass150090()
{
    func_001DFD90();
}

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

void FieldClass150090::func_001DFD50(float key, float* out)
{
    *out = func_001E0380(key);
}

FieldArrayEntry10* func_001DFD80(const FieldEntryArrayObject* object)
{
    return object->unk04;
}

void FieldClass150090::func_001DFD90()
{
    if (!unk2b_1)
    {
        delete[] unk04;
    }
    unk04 = 0;
}

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

void FieldClass14FEB0::func_001E0080(const float* x, const float* y, const float* z, float key)
{
    func_001DFC10(6);
    unk0c = *x;
    unk10 = *y;
    unk14 = *z;
    unk08 = key;
}

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

// 93.70%: control flow and loads match; only callee-saved register colouring
// differs (working/matching/func_001E07A0/1067-00/notes.md).
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E07A0__16FieldClass14FFB0Fv);

void FieldClass14FFB0::func_001E0A50(s32 flag)
{
    switch (unk15)
    {
    case 0:
        if (!flag && unk1c)
        {
            func_00121FE0(0);
            FieldClass150040* record = &unk1c[unk2e];
            s32 size = func_001E1100(this, (void*)((record->unk00 + 0x7FF) & ~0x7FF), 1);
            if (size)
            {
                record->unk04 = size;
                record->unk08_0 = 0;
                func_001DF3E0();
            }
        }
        break;
    case 1:
        if (flag == 1)
        {
            for (s32 i = 0; i < unk2d; i++)
            {
                FieldClass150040* record = &unk1c[i];
                u32 word = record->unk00;
                u32 size = record->rounded_unk04();
                func_00103B20(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
            }
            unk15 = 9;
        }
        else
        {
            FieldClass150040* record = &unk1c[unk2e];
            u32 word = record->unk00;
            u32 size = record->rounded_unk04();
            if (!func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0) && !field_records_blocked())
            {
                func_001DDB30(0);
            }
        }
        break;
    case 9:
        if (!flag)
        {
            func_001DF3E0();
        }
        break;
    case 10:
    {
        bool done = true;
        FieldClass150040* records = unk1c;
        for (s32 i = 0; i < unk2d; i++)
        {
            FieldClass150040* record = &records[i];
            u32 word = record->unk00;
            u32 size = record->rounded_unk04();
            record->unk10 = func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
            if (record->unk10)
            {
                done = false;
            }
        }
        if (field_records_blocked())
        {
            done = false;
        }
        if (done)
        {
            for (s32 i = 0; i < unk24; i++, records++)
            {
                records->func_0023AD00();
            }
            unk2e = 0;
            unk15 = 0;
        }
        break;
    }
    case 7:
    {
        bool done = true;
        FieldClass150040* record = unk1c;
        for (s32 i = 0; i < unk2d; i++, record++)
        {
            u32 word = record->unk00;
            u32 size = record->rounded_unk04();
            record->unk10 = func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0);
            if (record->unk10)
            {
                done = false;
            }
        }
        if (field_records_blocked())
        {
            done = false;
        }
        if (done)
        {
            func_001DD7B0();
        }
        break;
    }
    }
    func_001E0F60();
}

void FieldClass14FFB0::func_001E0F60()
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
        u32 word = record->unk00;
        u32 size = record->rounded_unk04();
        if (func_00103640(D_001B65E8, record->unk0c, size, 0x80000000, word, 0))
        {
            return;
        }
        while (unk2e < unk2d)
        {
            unk2e++;
            if (!unk1c[unk2e].unk16_0)
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

s32 func_001E1100(FieldClass150070* owner, void* buffer, s32 mode)
{
    FieldClass1530D0* node = static_cast<FieldClass1530D0*>(static_cast<LibClass178DD0*>(owner->unk10));
    for (s32 i = 0; i < 8; i++)
    {
        s32 result;
        if (mode)
        {
            func_433AA0();
            result = func_433880(buffer, 0x80);
        }
        else
        {
            result = func_139700(0x80, buffer);
        }
        if (result)
        {
            return result;
        }
        if (node->LibClass178DD0::unk0c == 1 || !func_0023AEB0(node, owner))
        {
            break;
        }
    }
    return 0;
}

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

float func_001E1230(FieldEntryArrayObject* object, float key)
{
    float first = object->unk04[0].unk00;
    float cycles = (key - first) / object->unk1c;
    if (key < first)
    {
        cycles -= 1.0f;
    }
    object->unk18 = cycles;
    if (object->unk18 != 0)
    {
        float result = key - object->unk18 * object->unk1c;
        if ((object->unk2a_0_3 == 3 && object->unk18 < 0) || (object->unk2a_4_7 == 3 && object->unk18 > 0))
        {
            s32 index = object->unk20 - 1;
            float last = object->unk04[index].unk00;
            if (object->unk18 & 1)
            {
                result = first + (last - result);
            }
        }
        return result;
    }
    return key;
}

// Index loop strength reduction not matched yet.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001DED80", func_001E1310);

s32 FieldClass150090::func_001E1470(const float* x, const float* y, const float* z, float key)
{
    return func_001DFD00(x, y, z, key);
}

s32 FieldClass150090::func_001E14A0(s32 index, float key, const float* x, const float* y, const float* z)
{
    return func_001DFD10(index, key, x, y, z);
}

s32 FieldClass150090::func_001E14D0(s32 index, float key, const float* x, const float* y, const float* z)
{
    return func_001DFD20(index, key, x, y, z);
}

void FieldClass150090::func_001E1500(const float* x, const float* y, const float* z, float key)
{
    func_001DFD30(x, y, z, key);
}


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
