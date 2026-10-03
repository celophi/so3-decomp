#include "include_asm.h"
#include "main/resident_data.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_001DD3C0.h"
#include "overlays/1067-00/text_0024C4B0.h"
#include "overlays/lib/text_0046AE20.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/1067-00/text_0021DB80.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_0021FB80.h"
#include "overlays/1067-00/text_0027E520.h"
#include "overlays/1067-00/text_002764D0.h"
#include "overlays/1067-00/text_002AE9E0.h"
#include "vu0.h"


/** @brief Vector passed to the VU0 length helper; copied as one quadword. */
class FieldDelta
{
public:
    FieldDelta() {}
    FieldDelta(const FieldDelta& other) { *(unsigned __int128*)this = *(const unsigned __int128*)&other; }
    FieldDelta(const FieldVec4A& other) { *(unsigned __int128*)this = *(const unsigned __int128*)&other; }
    FieldDelta operator=(const FieldDelta& other)
    {
        *(unsigned __int128*)this = *(const unsigned __int128*)&other;
        return *this;
    }

    float x, y, z, w;
} __attribute__((aligned(16)));

/** @brief Return a - b in x, y and z; w keeps a's value. */
static inline FieldDelta field_delta(const FieldVec4A& a, const FieldVec4A& b)
{
    FieldVec4A result;
    result = a;
    result.x -= b.x;
    result.y -= b.y;
    result.z -= b.z;
    return result;
}

/** @brief Length of v's x, y and z through the VU0 helper. */
static inline float field_length(const FieldDelta& v)
{
    FieldVec4A out;
    vu0_length_xyz(&out, &v);
    return out.x;
}

/** @brief Report whether node is the list head, ending a circular walk. */
static inline bool is_list_head(const void* head, const void* node)
{
    if (head == node)
    {
        return true;
    }
    return false;
}

/** @brief Report whether area equals the item's area word, or the context default when it is -1. */
static inline bool same_area(s32 area, const FieldClass152FE0* item)
{
    s32 item_area = item->unk694 == -1 ? D_001B6430->context->unkaa : item->unk694;
    return item_area == area;
}

/** @brief Report whether kind equals the item's kind byte at offset 0x69C. */
static inline bool same_kind(u8 kind, const FieldClass152FE0* item)
{
    return item->unk69c == kind;
}

void FieldClass1DD400::func_001DD400()
{
}

void FieldClass150070::func_001DD410()
{
}

void FieldClass1502A0::func_004295B0(void* attached)
{
    unk70 = attached;
}

void FieldClass1502A0::func_004295C0()
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

void FieldClass1502A0::func_001DD730()
{
    FieldClass150060* list = (FieldClass150060*)unk00;
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

void func_001DD860(FieldClass150060* list)
{
    FieldClass150F90* current;
    FieldClass150060* node = list->unk08;
    for (;;)
    {
        current = static_cast<FieldClass150F90*>(node);
        if (!node || list == node)
        {
            break;
        }
        node = node->unk08;
        if (current->unk78 & 0x400)
        {
            static_cast<FieldClass153330*>(current)->func_0023DE90(1);
        }
        else if (current->unk78 & 0x20000)
        {
            func_004D65C0(current);
            current->func_001DD7B0();
        }
        else if (current->unk78 & 0x20)
        {
            FieldClass152FE0* actor = static_cast<FieldClass152FE0*>(current);
            if (!actor->test_unk148())
            {
                actor->func_00205710(&actor->unk670);
            }
        }
    }
    FieldHeldObject20* holder = D_001B645C;
    if (holder)
    {
        func_0027E7D0(holder);
        holder->unk250 = 0;
    }
}

void FieldClass152F00::func_00205710(const FieldVec4A* value)
{
    FieldClass150EB0::func_00205710(value);
    unk530 = *value;
}

void func_001DD9A0(FieldClass150060* list, s8 mode, s32 arg)
{
    FieldClass150060* link = list;
    if (mode >= 2)
    {
        for (;;)
        {
            link = link->unk08;
            if (list == link)
            {
                break;
            }
            FieldClass150F90* object = static_cast<FieldClass150F90*>(link);
            if ((object->unk78 & 0x20002) && !object->test_unk70(0x80000000))
            {
                object->func_00204370(!object->unk8c_5, 0);
                object->func_002042A0(!object->unk8c_6);
                if (object->unk78 & 0x10)
                {
                    FieldClass152350* actor = static_cast<FieldClass152350*>(object);
                    func_00220150(actor, actor->unk6d2_4);
                }
            }
        }
    }
    else
    {
        for (;;)
        {
            link = link->unk08;
            if (!link || list == link)
            {
                break;
            }
            FieldClass150F90* object = static_cast<FieldClass150F90*>(link);
            if ((object->unk78 & 0x20002) && !object->test_unk70(0x80000000))
            {
                object->func_00204370(mode, arg);
            }
        }
    }
}

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

bool func_001DDD30(FieldListOwner94* list, FieldClass151510** target)
{
    if ((*target)->test_unk204(0x400000))
    {
        return false;
    }
    bool active = false;
    if (((*target)->unk78 & 0x10) && static_cast<FieldClass152350*>(*target)->unk638 > 0.0f)
    {
        active = true;
    }
    FieldClass150060* link = list;
    FieldClass154D20* own = (*target)->unkA8;
    for (;;)
    {
        link = link->unk08;
        if (!link || list == link)
        {
            break;
        }
        if (link == *target)
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
        if ((flags & 0x10) && static_cast<FieldClass152350*>(object)->unk638 > 0.0f)
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
        if (((*target)->unk78 & 0x20) && static_cast<FieldClass152FE0*>(*target)->unk69f_0 && (body->unk78 & 0x10))
        {
            continue;
        }
        if ((body->unk78 & 0x20) && (static_cast<FieldClass152FE0*>(body)->unk69f_0 || active))
        {
            continue;
        }
        FieldClass154D20* shape = body->unkA8;
        if (shape && func_0045F5A0(shape->func_001DDCD0(), own->func_001DDCD0()))
        {
            list->unk94 = body;
            *target = body;
            return true;
        }
    }
    return false;
}

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

void FieldClass14FE30::func_004D6730()
{
    if (D_001B6430->context->unkdd.unk7)
    {
        return;
    }
    unk60 = LibClass178DD0::unk0c;
    unk6c = new(0) void*[unk60];
    func_004D6AF0(this, unk6c);
    bool swapped;
    do
    {
        swapped = false;
        for (s32 i = 1; i < unk60 - 1; i++)
        {
            FieldClass150F90* first = static_cast<FieldClass150F90*>(unk6c[i]);
            FieldClass150F90* second = static_cast<FieldClass150F90*>(unk6c[i + 1]);
            float first_key = (first->unk78 & 0x400) ? static_cast<FieldClass153330*>(first)->unk464 : first->unk20.y;
            float second_key = (second->unk78 & 0x400) ? static_cast<FieldClass153330*>(second)->unk464 : second->unk20.y;
            if (first_key > second_key)
            {
                unk6c[i] = second;
                swapped = true;
                unk6c[i + 1] = first;
            }
        }
    } while (swapped);
    s32 count = unk60;
    FieldClass150F90* focus = static_cast<FieldClass150F90*>(D_001B6430->context->unk08->unkdc);
    if (!focus || (focus && focus->unk90 <= 0.0f))
    {
        for (unk5c = 0; unk5c < unk60; unk5c++)
        {
            FieldClass150F90* object = static_cast<FieldClass150F90*>(unk6c[unk5c]);
            if (object && object->unk0e && !object->test_unk70(0x80000000))
            {
                func_004D6700(this, object);
            }
        }
        for (s32 i = 0; i < count; i++)
        {
            FieldClass150F90* object = static_cast<FieldClass150F90*>(unk6c[i]);
            if (object && object->unk0e && !object->test_unk70(0x80000000) && (object->unk78 & 0x2))
            {
                static_cast<FieldClass152430*>(object)->func_001DE3D0();
            }
        }
        for (s32 i = 0; i < count; i++)
        {
            FieldClass150F90* object = static_cast<FieldClass150F90*>(unk6c[i]);
            if (object && object->unk0e && !object->test_unk70(0x80000000) && (object->unk78 & 0x2)
                && object->func_00204420())
            {
                static_cast<FieldClass152430*>(object)->func_00227CC0();
            }
        }
        for (s32 i = 0; i < count; i++)
        {
            FieldClass150F90* object = static_cast<FieldClass150F90*>(unk6c[i]);
            if (object && object->unk0e && !object->test_unk70(0x80000000) && (object->unk78 & 0x2)
                && object->func_00204420())
            {
                static_cast<FieldClass152430*>(object)->func_001DE3C0();
            }
        }
    }
    for (s32 j = 0; j < count; j++)
    {
        FieldClass150F90* object = static_cast<FieldClass150F90*>(unk6c[j]);
        if (object && object->unk0e && !object->test_unk70(0x80000000))
        {
            object->func_001DE3B0();
        }
    }
    delete[] unk6c;
    unk6c = 0;
}

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

void FieldClass14FE30::func_001DF360()
{
    ResidentContext* ctx = D_001B6430->context;
    if (ctx->unkdd.unk4 || func_002B0BC0((FieldFlagOwner2B0BC0*)ctx) || D_001B6430->context->unkde_1
        || D_001B6430->context->unkdd.unk5 || !D_001B6430->context->unk08->unkdc)
    {
        return;
    }
    if (D_001B6430->context->unkdd.unk6)
    {
        return;
    }
    func_004D6730();
    FieldClass150F90* focus = static_cast<FieldClass150F90*>(D_001B6430->context->unk08->unkdc);
    if (!focus)
    {
        return;
    }
    if (!focus->func_00204420())
    {
        return;
    }
    if (D_001B6430->context->unk38->unk4c8_0)
    {
        return;
    }
    if (D_001B6430->context->unk08->unkf5_3)
    {
        return;
    }
    const FieldVec4A* center = &static_cast<FieldClass150F90*>(D_001B6430->context->unk18)->unk20;
    FieldClass152FE0* nearest = 0;
    float best = 3.4028235e38f;
    FieldClass150060* node = reinterpret_cast<FieldClass150060*>(this);
    for (;;)
    {
        node = node->unk08;
        if (!node || is_list_head(this, node))
        {
            break;
        }
        FieldClass152FE0* item = static_cast<FieldClass152FE0*>(node);
        if (!(item->unk78 & 0x20) || item->test_unk70(0x80000000) || item->unk690 == -1)
        {
            continue;
        }
        FieldDelta delta;
        delta = field_delta(item->unk20, *center);
        float distance = field_length(delta);
        if (distance < best)
        {
            best = distance;
            nearest = item;
        }
    }
    if (!nearest)
    {
        return;
    }
    FieldClass155640* sound = static_cast<FieldClass155640*>(D_001B6430->context->unk1c);
    if (!sound)
    {
        sound = new(0) FieldClass155640;
        D_001B6430->context->unk1c = sound;
        static_cast<FieldClass1530D0*>(D_001B6430->context->unk30)->insert(sound);
    }
    s32 current_id = sound->unk7c8;
    if (nearest->unk690 != current_id || !same_area(sound->unk7cc, nearest) || !same_kind(sound->unk7d4, nearest))
    {
        s32 id = nearest->unk690;
        u8 kind = nearest->unk69c;
        sound->func_00279EA0(id, (nearest->unk694 == -1 ? D_001B6430->context->unkaa : nearest->unk694), kind, -1, 1);
    }
}

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
