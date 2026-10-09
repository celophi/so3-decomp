#include "include_asm.h"
#include "overlays/1067-00/text_001E6C50.h"
#include "overlays/1067-00/field_runtime.h"
#include "main/resident_data.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/1067-00/text_0022DC70.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_004AB8B0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/1067-00/text_00200710.h"
#include "overlays/1067-00/text_00212560.h"
#include "overlays/1067-00/text_0021FB80.h"
#include "vu0.h"

extern "C" void* D_001B64F8;

/* Lib.bin data, not owned by this overlay: GS register values passed to func_0011F140. */
extern "C" u64 D_4ED330[];

/**
 * @brief Subtract the center's xyz components from the point, preserving the point's w.
 * @param point Point to measure from.
 * @param center Center to subtract.
 * @return Displacement vector.
 */
static inline FieldVec4B field_difference(const FieldVec4A& point, const FieldVec4A& center)
{
    FieldVec4B result(point);
    result.x -= center.x;
    result.y -= center.y;
    result.z -= center.z;
    return result;
}

/**
 * @brief Test whether a circular-list walk has reached its head.
 * @param head List head.
 * @param node Current node.
 * @return Whether the node is the head.
 */
static inline bool field_is_list_head(const void* head, const void* node)
{
    if (head == node)
    {
        return true;
    }
    return false;
}
/**
 * @brief Measure the vector's xyz length.
 * @param v Displacement vector.
 * @return Length of the xyz components.
 */
static inline float field_length(const FieldVec4B& v)
{
    FieldVec4A out;
    vu0_length_xyz(&out, &v);
    return out.x;
}
/**
 * @brief Test whether a distance is within a supplied radius.
 * @param distance Measured distance.
 * @param radius Maximum distance.
 * @return Whether the distance is at most the radius.
 */
static inline bool field_within_radius(float distance, float radius)
{
    if (distance <= radius)
    {
        return true;
    }
    return false;
}

/** @brief Cull eligible shapes against the reference sphere and update visible vertices. */

/**
 * @brief Test the owner array's terminal flag.
 * @param owner Current owner record.
 * @return Whether the record terminates its array.
 */
static inline bool field_owner_is_last(const FieldShapeOwner18* owner)
{
    if (owner->unk0a & 0x20)
    {
        return true;
    }
    return false;
}
/**
 * @brief Create the indexed owner's successive shape records.
 * @param manager Shape manager to append to.
 * @param owner Owner containing a shape-record index.
 * @param data Shape-record arrays.
 */
static inline void field_append_indexed_shapes(FieldClass1504C0* manager, FieldShapeOwner18* owner, FieldShapeData10* data)
{
    FieldShapeRecord20* records = data->unk0c;
    if (owner->unk0e == -1)
    {
        return;
    }
    FieldShapeRecord20* record = &records[owner->unk0e];
    for (;;)
    {
        manager->append_shape(owner, record);
        if (record->unk0c_5)
        {
            break;
        }
        record++;
    }
}

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

extern "C" const char D_31A7D8[] = "Bip01";

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

/**
 * @brief Move the loaded animation to its last frame and reset the attached Lib vector state.
 */
void FieldClass150280::func_001E7590()
{
    if (unk14)
    {
        unk2c = unk14->unk64 - 1.0f;
        func_004B4550(unk14, unk2c, 0);
        LibClass178370* state = unk18;
        state->unkc0 = 0;
        state->unkc1 = 0;
        state->unkc2 = 0;
        state->unk60.packed = 0;
        state->unk60.components[3] = 1.0f;
        state->unk70.packed = 0;
        state->unk70.components[3] = 1.0f;
        state->unk80.packed = 0;
        state->unk80.components[3] = 1.0f;
        LibVector4 origin;
        origin.components[0] = 0.0f;
        origin.components[1] = 0.0f;
        origin.components[2] = 0.0f;
        origin.components[3] = 1.0f;
        unk18->unk90.packed = origin.packed;
        LibVector4 zero;
        zero.components[0] = 0.0f;
        zero.components[1] = 0.0f;
        zero.components[2] = 0.0f;
        zero.components[3] = 0.0f;
        unk18->unka0.packed = zero.packed;
        unk18->unkb0.packed = origin.packed;
    }
    else
    {
        unk2c = 0.0f;
    }
}

/**
 * @brief Evaluate the attached channel at the current animation key.
 * @return Evaluated float, or zero when no channel is attached.
 */
float FieldClass150280::func_001E7660()
{
    if (unk28)
    {
        float value;
        unk28->func_004C16F0(unk2c, &value);
        return value;
    }
    return 0.0f;
}

/**
 * @brief Load the animation when needed and reset its playback range and attached state.
 * @param start First playback frame.
 * @param end Last playback frame.
 */
void FieldClass150280::func_001E76B0(float start, float end)
{
    if (!unk66_3)
    {
        void* heap = func_00100C80(D_001B6430->context->unk70);
        if (!func_004BF100(unk14, unk1c->unk7c, 0))
        {
            func_00100C80(heap);
            return;
        }
        func_00100C80(heap);
        unk66_3 = 1;
    }
    unk14->unk6a = 0;
    LibVector4 initial;
    initial.components[0] = 0.0f;
    initial.components[1] = 0.0f;
    initial.components[2] = 0.0f;
    initial.components[3] = 0.0f;
    unk18->func_003EF780(&initial);
    LibClass178370* state = unk18;
    state->unkc0 = 0;
    state->unkc1 = 0;
    state->unkc2 = 0;
    state->unk60.packed = 0;
    state->unk60.components[3] = 1.0f;
    state->unk70.packed = 0;
    state->unk70.components[3] = 1.0f;
    state->unk80.packed = 0;
    state->unk80.components[3] = 1.0f;
    func_004BDB50(unk14, unk18, D_31A7D8);
    func_004B3DE0(unk14, unk18);
    unk2c = start;
    unk50 = 0;
    unk58 = 2;
    unk5c = -1;
    unk64 = 0;
    unk60 = 1.0f;
    unk30 = start;
    unk34 = end;
    unk28 = 0;
    unk20 = 0;
    unk24 = 0;
    unk40 = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    unk66_0 = 0;
    unk66_2 = 0;
    unk66_4 = 0;
    unk66_5 = 0;
    unk66_6 = 0;
}

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E84E0__16FieldClass1502E0Fv);

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

void FieldClass150320::func_001E9050()
{
    FieldSavedChannelEntry* entry = unk04;
    if (entry)
    {
        for (s32 i = 0; i < unk08; i++, entry++)
        {
            LibClass173180* channel = func_004BDA30(unk00, entry->unk00, 0);
            if (channel)
            {
                func_001E9390(channel);
                channel->func_0042A820();
            }
            func_004BD9D0(unk00, entry->unk00, entry->unk08, entry->unk06, entry->unk04, entry->unk07);
        }
        delete[] unk04;
        unk04 = 0;
    }
}

FieldClass150320::~FieldClass150320()
{
    func_001E9050();
}

/**
 * @brief Save type-6 animation entries and replace their channels with pooled channels.
 * @param animation Animation whose entries are updated.
 * @param owner Owner argument; unused.
 * @param duration Duration argument; unused.
 */
FieldClass150320::FieldClass150320(LibClass178220* animation, void* owner, float duration)
{
    unk00 = animation;
    unk04 = 0;
    FieldSavedChannelEntry* temporary = new(0) FieldSavedChannelEntry[1024];
    FieldSavedChannelEntry* saved = temporary;
    s32 count = 0;
    s32 total = animation->unk38;
    for (s32 index = 0; index < total; index++)
    {
        LibClass173180* original = func_004BDA30(animation, index, 0);
        LibClass173180* replacement;
        LibAnimationEntry14* entry = animation->unk50;
        if (entry && entry->unk00 == 6)
        {
            saved->unk00 = index;
            saved->unk04 = entry->unk00;
            saved->unk06 = entry->unk02;
            saved->unk07 = entry->unk03;
            saved->unk08 = original;
            replacement = func_001E93E0(D_001B666C);
            replacement->func_004C1560(original->func_004C16D0() + 1);
            LibVector4 value;
            original->func_004C16F0(0.0f, &value);
            replacement->func_0042A7C0(&value, 0, 0, 0.0f);
            func_004BD9D0(animation, index, replacement, 1, 4, entry->unk03);
            count++;
            saved++;
            if (count >= 1024)
            {
                break;
            }
        }
    }
    unk08 = count;
    if (count > 0)
    {
        void* heap = func_00100C80(0);
        u32 size = count * sizeof(FieldSavedChannelEntry);
        unk04 = new(0) FieldSavedChannelEntry[count];
        func_00100C80(heap);
        if (unk04)
        {
            func_0013A4C0(unk04, temporary, size);
        }
    }
    operator delete(temporary);
}

s16 func_001E9380(const FieldHalfword3A* object)
{
    return object->unk3a;
}

/**
 * @brief Release the vector channel's owned entry array and clear its array pointer.
 * @param channel Vector channel whose entry array is released.
 */
extern "C" void func_001E9390(LibClass173180* channel)
{
    LibClass177B50* vector = static_cast<LibClass177B50*>(channel);
    if (!vector->unk43_1)
    {
        delete[] vector->unk04;
    }
    vector->unk04 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001E93E0);

void func_001E94F0(LibClass177B50* object)
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

void FieldClass150330::func_001E9A50()
{
    if (!unk24 || !unk28 || !unk20)
    {
        return;
    }
    if (!unk3c_3_5 && !unk18)
    {
        return;
    }

    unk3c_0 = 1;
    if (!unk20->unk61)
    {
        unk20->func_004D0090();
    }
    const void* matrix = unk20->func_004D00A0();
    for (s32 index = 0; index < unk38; index++)
    {
        func_00433730(matrix, &unk24[index], &unk28[index]);
    }
}

// Returns &object->unk90; subobject type unknown.
extern "C" const void* func_001E9B70(FieldModelMatrix90* object)
{
    return &object->unk90;
}

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

void FieldClass1504C0::func_001EA730()
{
    FieldClass150060* node = (FieldClass150060*)unk38.unk00;
    for (;;)
    {
        node = node->unk08;
        if (!node || field_is_list_head(unk38.unk00, node))
        {
            break;
        }
        FieldClass150330* item = static_cast<FieldClass150330*>(node);
        switch (item->unk3c_3_5)
        {
        case 0:
        {
            if (!unkc4_2)
            {
                continue;
            }
            if (item->unk1c->unk0c_4 && unkc0 % 3 != 0)
            {
                continue;
            }
            if (unkc4_0)
            {
                FieldShapeOwner18* owner = item->unk18;
                const void* matrix = owner->unk04->func_004D00A0();
                FieldVec4A point(owner->unk10);
                float radius = point.w;
                point.w = 1.0f;
                func_00433730(matrix, &point, &point);
                if (!field_within_radius(field_length(field_difference(point, unkb0)), unkb0.w + radius))
                {
                    item->unk3c_1 = 0;
                    continue;
                }
                item->unk3c_1 = 1;
            }
            break;
        }
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
        if (item->unk3c_1)
        {
            item->func_001E9A50();
        }
    }
}

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EAE60__16FieldClass1504C0FP17FieldShapeOwner18P18FieldShapeRecord20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001E6C50", func_001EAF60__16FieldClass1504C0FP17FieldShapeOwner18P16FieldShapeData10);

/**
 * @brief Create shapes for an owner array and its nested owner arrays.
 * @param owner First owner record.
 * @param data Shape state and record arrays.
 */
void FieldClass1504C0::func_001EB070(FieldShapeOwner18* owner, FieldShapeData10* data)
{
    for (;;)
    {
        if (owner->unk0e != -1)
        {
            field_append_indexed_shapes(this, owner, data);
        }
        FieldShapeOwner18* child = owner->unk00;
        if (child)
        {
            for (;;)
            {
                if (child->unk0e != -1)
                {
                    FieldShapeRecord20* records = data->unk0c;
                    s16 index = func_001EB2E0(child);
                    if (index != -1)
                    {
                        func_001EAE60(child, &records[index]);
                    }
                }
                if (child->unk00)
                {
                    FieldShapeOwner18* nested = func_001EB2D0(child);
                    for (;;)
                    {
                        if (func_001EB2E0(nested) != -1)
                        {
                            func_001EAF60(nested, data);
                        }
                        if (func_001EB2D0(nested))
                        {
                            func_001EB070(func_001EB2D0(nested), data);
                        }
                        if (func_001EB2C0(nested))
                        {
                            break;
                        }
                        nested = func_001EB2B0(nested);
                    }
                }
                if (field_owner_is_last(child))
                {
                    break;
                }
                child++;
            }
        }
        if (field_owner_is_last(owner))
        {
            break;
        }
        owner++;
    }
}

extern "C" FieldShapeOwner18* func_001EB2B0(FieldShapeOwner18* owner)
{
    return owner + 1;
}

s32 func_001EB2C0(const FieldShapeOwner18* record)
{
    return (record->unk0a & 0x20) != 0;
}

FieldShapeOwner18* func_001EB2D0(const FieldShapeOwner18* record)
{
    return record->unk00;
}

s16 func_001EB2E0(const FieldShapeOwner18* record)
{
    return record->unk0e;
}

/**
 * @brief Bind shape data, create the owner's indexed shapes, and process its children.
 * @param owner Owner descriptor.
 * @param data Shape data and state entries.
 */
void FieldClass1504C0::func_001EB2F0(FieldShapeOwner18* owner, FieldShapeData10* data)
{
    unk30 = owner;
    unk34 = data;
    unkc4_0 = 0;
    unkc4_2 = 1;
    if (owner->unk0e != -1)
    {
        field_append_indexed_shapes(this, owner, unk34);
    }
    if (owner->unk00)
    {
        func_001EB070(owner->unk00, unk34);
    }
}

void FieldClass1504F0::func_001EB590()
{
    if (unk14)
    {
        FieldVec4A scale(1.0f, 1.0f, 1.0f, 1.0f);
        func_00249880(unk14, &scale);
        unk14->unk590_2 = 0;
        unk14->unk590_3 = 0;
        unk14 = 0;
    }
    func_004D65C0(this);
    func_001DD7B0();
    FieldObject220150* state = (FieldObject220150*)D_001B6430->context->unk18;
    state->unk6D3_1 = 1;
}

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

/**
 * @brief Detach and queue the object once, request detachment of its container, and clear the current instance.
 */
void FieldClass1504F0::func_001DD7B0()
{
    if (!unk4d_1)
    {
        func_004D65C0(this);
        func_0011ED90(D_001B65F4, this);
        if (unk18)
        {
            static_cast<LibClass174610&>(*unk18).func_003EF740();
            unk18 = 0;
        }
        unk4d_1 = 1;
        D_001B6428 = 0;
    }
}

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

/**
 * @brief Configure the active HUD widgets from the resident flags and resources.
 */
void FieldClass1504F0::func_001ED160()
{
    unk4d_6 = 0;
    unk4d_4 = 0;
    unk4d_5 = 0;
    ResidentContextObject38* state = D_001B6430->context->unk38;
    ResidentHudSection1B4* section = (ResidentHudSection1B4*)func_101440(func_101290(func_10D8E0()), 4);
    if (func_00217600(state, 0x4E9))
    {
        unk4d_6 = 1;
    }
    else
    {
        if (func_00217600(state, 0x810))
        {
            unk4d_4 = 1;
        }
        if (func_00217600(state, 0x80F))
        {
            unk4d_5 = 1;
        }
    }
    for (s32 index = 0; index < 2; index++)
    {
        if (unk24[index])
        {
            unk24[index]->unk3d = 0;
        }
        if (unk2c[index])
        {
            unk2c[index]->unk3d = 0;
        }
        if (unk34[index])
        {
            unk34[index]->unk3d = 0;
        }
    }
    LibClass178600* first_panel = unk24[0];
    first_panel->unk18.unk00 = 0.0f;
    first_panel->unk3c = 1;
    unk24[0]->unk3d = 1;
    if (!unk2c[0])
    {
        unk2c[0] = new(0) LibObject178750;
    }
    if (!unk34[0])
    {
        unk34[0] = new(0) LibObject174F20;
    }
    if (!func_00217600(state, 0x4E9))
    {
        ItemCreationCategoryRecord* resource = &((ResidentObject1B64F8*)D_001B64F8)->item_types[499];
        float offset = 0.0f;
        if (func_00217600(state, 0x810))
        {
            LibUiRect16* position = &unk24[0]->unk18;
            if (unk2c[0])
            {
                if (func_004C7FE0(unk2c[0], unk3c, 0x20, 0, 16.0f + position->unk00, 8.0f + position->unk04, 352.0f, 48.0f))
                {
                    LibClass174EF0* widget = unk2c[0];
                    widget->unk80 = 0.8f;
                    widget->unk3c = 1;
                    unk2c[0]->unk3d = 1;
                }
                func_004C6190(unk18, unk2c[0]);
            }
            if (unk34[0])
            {
                func_00464D90(unk34[0], resource->unk08, 0, 0, 92.0f + position->unk00, 8.0f + position->unk04, 0.0f, 0.0f);
                LibClass174EF0* widget = unk34[0];
                widget->unk9c = 0;
                widget->unk3c = 1;
                unk34[0]->unk3d = 1;
                func_004C6190(unk18, unk34[0]);
            }
            offset += 124.0f;
        }
        else
        {
            unk24[0]->unk3d = 0;
        }
        ItemCreationCategoryRecord* second_resource = &((ResidentObject1B64F8*)D_001B64F8)->item_types[498];
        if (func_00217600(state, 0x80F))
        {
            LibClass178600* second_panel = unk24[1];
            second_panel->unk18.unk00 = offset;
            second_panel->unk3c = 1;
            unk24[1]->unk3d = 1;
            LibUiRect16* position = &unk24[1]->unk18;
            if (!unk2c[1])
            {
                unk2c[1] = new(0) LibObject178750;
            }
            if (unk2c[1])
            {
                if (func_004C7FE0(unk2c[1], unk3c, 0x21, 0, 16.0f + position->unk00, 8.0f + position->unk04, 352.0f, 48.0f))
                {
                    LibClass174EF0* widget = unk2c[1];
                    widget->unk80 = 0.9f;
                    widget->unk3c = 1;
                    unk2c[1]->unk3d = 1;
                }
                func_004C6190(unk18, unk2c[1]);
            }
            if (!unk34[1])
            {
                unk34[1] = new(0) LibObject174F20;
            }
            if (unk34[1])
            {
                func_00464D90(unk34[1], second_resource->unk08, 0, 0, 80.0f + position->unk00, 8.0f + position->unk04, 0.0f, 0.0f);
                LibClass174EF0* widget = unk34[1];
                widget->unk9c = 0;
                widget->unk3c = 1;
                unk34[1]->unk3d = 1;
                func_004C6190(unk18, unk34[1]);
            }
        }
        else
        {
            unk24[1]->unk3d = 0;
        }
    }
    else
    {
        LibClass178600* special_panel = unk24[0];
        special_panel->unk18.unk08 = 264.0f;
        special_panel->unk3c = 1;
        LibUiRect16* position = &unk24[0]->unk18;
        if (unk2c[0])
        {
            if (func_004C7FE0(unk2c[0], unk3c, 0x22, 0, 16.0f + position->unk00, 8.0f + position->unk04, 352.0f, 48.0f))
            {
                LibClass174EF0* widget = unk2c[0];
                widget->unk80 = 0.8f;
                widget->unk3c = 1;
                unk2c[0]->unk3d = 1;
            }
            func_004C6190(unk18, unk2c[0]);
        }
        if (unk34[0])
        {
            func_00464D90(unk34[0], section->unk1b0, 0, 0, 208.0f + position->unk00, 8.0f + position->unk04, 0.0f, 0.0f);
            LibClass174EF0* widget = unk34[0];
            widget->unk9c = 0;
            widget->unk3c = 1;
            unk34[0]->unk3d = 1;
            func_004C6190(unk18, unk34[0]);
        }
    }
}
