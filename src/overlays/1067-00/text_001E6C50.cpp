#include "include_asm.h"
#include "overlays/1067-00/text_001E6C50.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/1067-00/text_00200710.h"
#include "overlays/1067-00/text_0021FB80.h"
#include "vu0.h"

/* Lib.bin data, not owned by this overlay: GS register values passed to func_0011F140. */
extern "C" u64 D_4ED330[];

FieldClass1501F0::~FieldClass1501F0()
{
}

void FieldClass150220::func_001E6CF0(FieldRecord150220* source)
{
    unk18 = source;
}

void FieldClass150220::func_001E6D00()
{
    unk20_0 = 0;
}

void FieldClass1501F0::func_001E73D0(const FieldMatrix44* matrix)
{
    if (unk20_0)
    {
        return;
    }
    func_00433730(matrix, &unk1c0, &unk1d0);
    unk20_0 = 1;
}

// The pole copy leaves no dead stack store but the ring copies do; vector member types unresolved.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E6D80__16FieldClass1501F0FP17FieldRecord150220PC13FieldMatrix44f);

FieldVec4A* FieldClass150250::func_001E6FC0(s32 face)
{
    if (unk130[face].w == 0.0f)
    {
        FieldVec4A points[3];
        switch (face)
        {
        case 0:
            points[0] = unkb0[0];
            points[1] = unkb0[4];
            points[2] = unkb0[5];
            break;
        case 1:
            points[0] = unkb0[0];
            points[1] = unkb0[1];
            points[2] = unkb0[3];
            break;
        case 2:
            points[0] = unkb0[5];
            points[1] = unkb0[4];
            points[2] = unkb0[6];
            break;
        case 3:
            points[0] = unkb0[0];
            points[1] = unkb0[2];
            points[2] = unkb0[6];
            break;
        case 4:
            points[0] = unkb0[1];
            points[1] = unkb0[5];
            points[2] = unkb0[7];
            break;
        case 5:
            points[0] = unkb0[2];
            points[1] = unkb0[3];
            points[2] = unkb0[7];
            break;
        }
        func_0023E2F0(points, &unk130[face]);
    }
    return &unk130[face];
}

INCLUDE_RODATA("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", D_31A7D8);

void FieldClass150250::func_001E73D0(const FieldMatrix44* matrix)
{
    s32 i;
    if (unk20_0)
    {
        return;
    }
    vu0_load_matrix(matrix);
    for (i = 0; i < 8; i++)
    {
        func_004336E0(&unk30[i], &unkb0[i]);
    }
    func_004336E0(&unk190, &unk1a0);
    unk20_0 = 1;
}

void FieldClass150250::func_001E6D80(FieldRecord150220* source, const FieldMatrix44* matrix, float scale)
{
    const FieldVec4A* center = &source->unk10;
    unk18 = source;
    for (s32 i = 0; i < 8; i++)
    {
        unk30[i] = *center;
        unk30[i].w = 1.0f;
    }
    unk30[0].x += source->unk00;
    unk30[0].y -= source->unk04;
    unk30[0].z += source->unk08;
    unk30[1].x += source->unk00;
    unk30[1].y -= source->unk04;
    unk30[1].z -= source->unk08;
    unk30[2].x += source->unk00;
    unk30[2].y += source->unk04;
    unk30[2].z += source->unk08;
    unk30[3].x += source->unk00;
    unk30[3].y += source->unk04;
    unk30[3].z -= source->unk08;
    unk30[4].x -= source->unk00;
    unk30[4].y -= source->unk04;
    unk30[4].z += source->unk08;
    unk30[5].x -= source->unk00;
    unk30[5].y -= source->unk04;
    unk30[5].z -= source->unk08;
    unk30[6].x -= source->unk00;
    unk30[6].y += source->unk04;
    unk30[6].z += source->unk08;
    unk30[7].x -= source->unk00;
    unk30[7].y += source->unk04;
    unk30[7].z -= source->unk08;
    unk190 = *center;
    if (matrix)
    {
        vu0_load_matrix(matrix);
        for (s32 i = 0; i < 8; i++)
        {
            func_004336E0(&unk30[i], &unk30[i]);
        }
    }
}

void FieldClass150220::func_001E73D0(const FieldMatrix44* matrix)
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
        unk130[i].w = 0.0f;
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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E78B0__16FieldClass150280FPvbbf);

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

FieldClass150280::~FieldClass150280()
{
    if (unk66_1)
    {
        FieldClass1502E0* list = unk1c->unk3a0;
        if (list && list->unk90 && unk14 == list->unk90->unk00)
        {
            list->unk90->func_001E9050();
        }
        if (unk66_3 && unk14)
        {
            func_004BDD10(unk14);
        }
        unk66_3 = 0;
        if (unk14)
        {
            unk14->func_003EF740();
            unk14 = 0;
        }
        if (unk18)
        {
            unk18->func_003EF740();
            unk18 = 0;
        }
    }
}

FieldClass150280::FieldClass150280()
{
    unk14 = 0;
    unk18 = 0;
    unk50 = 0;
    unk20 = 0;
    unk24 = 0;
    unk28 = 0;
    unk54 = -1;
    unk2c = 0.0f;
    unk58 = 2;
    unk40 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk64 = 0;
    unk60 = 1.0f;
    unk34 = -1.0f;
    unk30 = 0.0f;
    unk5c = -1;
    unk66_0 = 0;
    unk66_1 = 0;
    unk66_2 = 0;
    unk66_3 = 0;
    unk66_4 = 0;
    unk66_5 = 0;
    unk66_6 = 0;
}

FieldVec4B FieldClass1502E0::func_001E81D0(void* arg, float step)
{
    FieldVec4B result(0.0f, 0.0f, 0.0f, 1.0f);
    if (unk7c && unkac <= 0.0f)
    {
        result = unk7c->func_001E78B0(arg, unkb4 & 0x100 ? true : false, unkb4 & 0x200 ? true : false, step);
        unkb8 = unk7c->unk58;
        if (unk90 && !(unk7c->unk2c < 0.0f))
        {
            delete unk90;
            unk90 = 0;
        }
    }
    return result;
}

s32 FieldClass1502E0::func_001E82B0(s32 key)
{
    if (find(key))
    {
        return 0;
    }
    void* data = func_00201EA0(D_001B6430->context->unk2c, 'ANIM', key, 0);
    if (!data)
    {
        return 0;
    }
    FieldClass150280* item = new(0) FieldClass150280;
    if (!item)
    {
        return 0;
    }
    FieldClass150EB0* owner = unk78;
    item->unk14 = new(0) LibClass178220;
    item->unk18 = new(0) LibClass178370;
    item->unk66_1 = 1;
    item->unk54 = key;
    item->unk1c = owner;
    LibClass178220* anim = item->unk14;
    if (anim->unk40)
    {
        func_004BDD10(anim);
        delete[] anim->unk40;
    }
    anim->unk6e = 0;
    if (!anim->unk68)
    {
        operator delete(anim->unk30);
    }
    anim->unk68 = 1;
    anim->unk30 = (void*)(((u32)data + 0x7F) & ~0x7F);
    func_004BFE10(item->unk14, item->unk1c->unk7c);
    func_004D74F0(item, (void*)-1);
    return 1;
}

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

void FieldClass1502E0::func_001E8E00(u32 key, u16 flags, float a, float b, float c, float d, float e)
{
    unkac = 300.0f;
    unk98 = key;
    unk9c = a;
    unka0 = b;
    unka8 = c;
    unkb0 = d;
    unkb8 = 2;
    unkb4 = (unkb4 & ~0xFF) | flags;
    unka4 = e;
}

FieldClass1502E0::~FieldClass1502E0()
{
    s32 i;
    delete unk90;
    unk90 = 0;
    unk7c = 0;
    for (i = 0; i < 2; i++)
    {
        if (unk80[i])
        {
            unk80[i]->func_001DD7B0();
            unk80[i] = 0;
        }
    }
    func_001DD730();
}

FieldClass1502E0::FieldClass1502E0()
{
    unk7c = 0;
    unk8c = 0;
    unk90 = 0;
    unkb6 = 0;
    unkac = 0.0f;
    unkb8 = 2;
    unk94 = -1;
    unkb0 = 1.0f;
    unka4 = -1.0f;
    unk80[0] = 0;
    unk80[1] = 0;
    unk88 = 0;
    unkb4 = 0x100;
    unkbc_0 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9050__16FieldClass150320Fv);

FieldClass150320::~FieldClass150320()
{
    func_001E9050();
}

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

s32 func_001E95B0(s32 flag)
{
    if (!flag || D_001B6430->context->unkde_3)
    {
        if (!D_001B6428)
        {
            FieldClass1504F0* object = new(0) FieldClass1504F0;
            if (object)
            {
                object->unk4d_2 = flag;
                D_001B6614->func_004D74F0(object, (void*)-1);
                return 1;
            }
        }
    }
    else
    {
        D_001B6430->context->unkde_3 = 0;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9690__16FieldClass150330FP14ResidentPacketPC10FieldVec4BPC10FieldVec4BUi);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9A50);

// Returns &object->unk90; subobject type unknown.
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E9B70);

void FieldClass150330::func_001E9B80(const FieldVec4B* low, const FieldVec4B* high)
{
    unk38 = 8;
    unk3a = 12;
    unk24 = new(0) FieldVec4B[unk38];
    unk28 = new(0) FieldVec4B[unk38];
    unk2c = new(0) FieldIndexPair[unk3a];
    unk24[0] = FieldVec4A(high->x, low->y, high->z, 1.0f);
    unk24[1] = FieldVec4A(low->x, low->y, high->z, 1.0f);
    unk24[2] = FieldVec4A(low->x, low->y, low->z, 1.0f);
    unk24[3] = FieldVec4A(high->x, low->y, low->z, 1.0f);
    unk24[4] = FieldVec4A(high->x, high->y, high->z, 1.0f);
    unk24[5] = FieldVec4A(low->x, high->y, high->z, 1.0f);
    unk24[6] = FieldVec4A(low->x, high->y, low->z, 1.0f);
    unk24[7] = FieldVec4A(high->x, high->y, low->z, 1.0f);
    unk2c[0] = FieldIndexPair(0, 1);
    unk2c[1] = FieldIndexPair(1, 2);
    unk2c[2] = FieldIndexPair(2, 3);
    unk2c[3] = FieldIndexPair(3, 0);
    unk2c[4] = FieldIndexPair(4, 5);
    unk2c[5] = FieldIndexPair(5, 6);
    unk2c[6] = FieldIndexPair(6, 7);
    unk2c[7] = FieldIndexPair(7, 4);
    unk2c[8] = FieldIndexPair(0, 4);
    unk2c[9] = FieldIndexPair(1, 5);
    unk2c[10] = FieldIndexPair(2, 6);
    unk2c[11] = FieldIndexPair(3, 7);
}

FieldIndexPair::FieldIndexPair()
{
}

FieldVec4B::FieldVec4B()
{
}

void FieldClass150330::func_001E9EA0(float radius)
{
    s32 vertex = 0;
    s32 edge = 0;
    s32 ring_start;
    unk38 = 14;
    unk3a = 30;
    unk24 = new(0) FieldVec4B[unk38];
    unk28 = new(0) FieldVec4B[unk38];
    unk2c = new(0) FieldIndexPair[unk3a];
    for (s32 band = 0; band < 4; band++)
    {
        if (band == 0)
        {
            unk24[vertex].set(FieldVec4A(0.0f, radius, 0.0f, 1.0f));
            vertex++;
        }
        else if (band == 3)
        {
            unk24[vertex].set(FieldVec4A(0.0f, -radius, 0.0f, 1.0f));
            for (s32 i = 0; i < 6; i++)
            {
                unk2c[edge + i] = FieldIndexPair(ring_start + i, vertex);
            }
            return;
        }
        else
        {
            ring_start = vertex;
            float pitch = 1.5707964f - 1.0471976f * band;
            float ring = radius * func_004CC3E0(pitch);
            float height = radius * func_004CC690(pitch);
            for (s32 i = 0; i < 6; i++)
            {
                float yaw = 1.0471976f * i;
                unk24[vertex].set(FieldVec4A(ring * func_004CC3E0(yaw), height, ring * func_004CC690(yaw), 1.0f));
                vertex++;
            }
            switch (band)
            {
            case 1:
                for (s32 i = 0; i < 6; i++)
                {
                    unk2c[edge++] = FieldIndexPair(0, i + ring_start);
                    unk2c[edge++] = FieldIndexPair(i + ring_start, ring_start + (i == 5 ? 0 : i + 1));
                }
                break;
            default:
                for (s32 i = 0; i < 6; i++)
                {
                    unk2c[edge++] = FieldIndexPair(i + ring_start - 6, i + ring_start);
                    unk2c[edge++] = FieldIndexPair(i + ring_start, ring_start + (i == 5 ? 0 : i + 1));
                }
                break;
            }
        }
    }
}

void FieldClass150330::func_001EA2E0(FieldShapeOwner18* owner, FieldShapeRecord20* record, u32 color, s32 flag)
{
    unk3c_2 = flag;
    unk18 = owner;
    unk1c = record;
    unk14 = color;
    unk20 = unk18->unk04;
    FieldVec4B size = *(const FieldVec4B*)record;
    if (unk3c_2)
    {
        size *= 1.05f;
    }
    switch (record->unk0c_0_3)
    {
    case 0:
    {
        FieldVec4B low(size);
        FieldVec4B high(size);
        low *= -1.0f;
        func_001E9B80(&low, &high);
        break;
    }
    case 1:
        if (unk3c_2)
        {
            FieldVec4B low(FieldVec4A(size.x, size.x, size.x, 1.0f));
            FieldVec4B high(low);
            low *= -1.0f;
            func_001E9B80(&low, &high);
        }
        else
        {
            func_001E9EA0(size.x);
        }
        break;
    }
    for (s32 i = 0; i < unk38; i++)
    {
        unk24[i] += unk1c->unk10;
    }
}

FieldClass150330::~FieldClass150330()
{
    if (unk28)
    {
        delete[] unk28;
        unk28 = 0;
    }
    if (unk2c)
    {
        delete[] unk2c;
        unk2c = 0;
    }
    if (unk24)
    {
        delete[] unk24;
        unk24 = 0;
    }
}

FieldClass150330::FieldClass150330()
{
    unk3c_0 = 0;
    unk3c_1 = 1;
    unk3c_2 = 0;
    unk24 = 0;
    unk28 = 0;
    unk2c = 0;
    unk38 = 0;
    unk3a = 0;
    unk18 = 0;
    unk1c = 0;
    unk20 = 0;
    unk3c_3_5 = 0;
    unk30 = 0;
}

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

void FieldClass1504C0::func_001EAA10(ResidentPacket* packet)
{
    FieldClass150060* node = (FieldClass150060*)unk38.unk00;
    for (;;)
    {
        node = node->unk08;
        if (!node || (FieldClass150060*)unk38.unk00 == node)
        {
            break;
        }
        FieldClass150330* item = static_cast<FieldClass150330*>(node);
        if (!item->unk3c_1)
        {
            continue;
        }
        switch (item->unk3c_3_5)
        {
        case 0:
            if (!unkc4_2)
            {
                continue;
            }
            if (item->unk1c->unk0c_4 && unkc0 % 3 != 0)
            {
                continue;
            }
            break;
        case 1:
            if (!unkc4_3)
            {
                continue;
            }
            break;
        case 2:
            if (!unkc4_4)
            {
                continue;
            }
            break;
        }
        if (!item->unk3c_0 || D_001B6430->context->unkdd.unk7)
        {
            continue;
        }
        if (item->unk30 < 1.0f)
        {
            item->unk30 += D_001B6688 / 15.0f;
        }
        u32 color = (item->unk14 & 0xFFFFFF) | ((u32)(128.0f * item->unk30) << 24);
        for (s32 i = 0; i < item->unk3a; i++)
        {
            item->func_001E9690(packet, &item->unk28[item->unk2c[i].unk00], &item->unk28[item->unk2c[i].unk02], color);
        }
    }
}

void FieldClass1504C0::func_001EAC90(ResidentPacket* packet)
{
    if (unk30 == 0 || !unkc4_1)
    {
        return;
    }
    packet->unk15 = 1;
    func_0011F140(packet, D_4ED330[0]);
    func_0011EF00(packet, 0x48, 0x3000D);
    func_0011EF90(packet, 0x2C1);
    func_001EAA10(packet);
    func_0011EF00(packet, 0x48, 0x5000D);
}

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

FieldClass150420::~FieldClass150420()
{
}

s32 func_001ECF10(const FieldGatedObject448* object)
{
    if (!object->unk80 || !object->unk448 || object->unk8c_5)
    {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001ECF60);

FieldClass1504F0::~FieldClass1504F0()
{
    if (unk3c != -1)
    {
        func_00465430(D_001B657C, unk3c);
    }
    if (unk40)
    {
        unk40->func_001DD7B0();
        unk40 = 0;
    }
    FieldObject24B6B0* target = unk14;
    if (target)
    {
        u8 flags = target->unk590_0 | target->unk590_1;
        if (!flags)
        {
            FieldVec4A scale(1.0f, 1.0f, 1.0f, 1.0f);
            func_00249880(target, &scale);
            target->unk590_2 = 0;
        }
        target->unk590_3 = 0;
    }
    D_001B6430->context->unk64->unk48 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001ED160);
