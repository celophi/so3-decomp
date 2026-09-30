#include "include_asm.h"
#include "overlays/1067-00/text_001FD860.h"


typedef unsigned __int128 FieldLocalQword;
extern "C" s32 func_0022A160(void*);
extern "C" void func_00208C30(void*);
extern "C" void func_00209160(void*, void*, u32);
extern "C" void func_001FF5A0(void*, u32, u32);
extern "C" void func_001FF7F0(FieldFlaggedPointerA0*, u32);

union FieldLocalVector4
{
    u32 words[4];
    FieldLocalQword packed;
};
extern "C" void func_00228DD0(FieldTransform*);
extern "C" bool func_00227280(FieldState3BA*);

struct FieldSlot { u8 pad[0x20]; FieldLocalQword unk20; };
struct FieldState704 { u8 pad[0x704]; u32 unk704; };
struct FieldState79C { u8 pad[0x79C]; u8 unk79c; };
struct FieldState794 { u8 pad[0x794]; u8 unk794; };
struct FieldState570 { u8 pad[0x570]; u8 unk570; };
struct FieldNested634 { u8 pad[0x634]; u32 unk634; };
struct FieldOuter870 { u8 pad[0x838]; FieldNested634* unk838; u8 pad83c[0x34]; void* unk870; };
struct FieldFlagTarget { u8 pad[0x6A]; u16 flags; };
struct FieldItem10 {
    FieldFlagTarget* target;
    u8 pad04[8];
    u8 unk0_1 : 2;
    u8 unk2 : 1;
    u8 unk3_7 : 5;
    u8 pad0d[3];
};
struct FieldListAC { u8 pad[0xA4]; FieldItem10* items; s32 count; };
struct FieldStateAD { u8 pad[0xA0]; void* unka0; u8 pad_a4[9]; u8 unkad_0 : 1; u8 unkad_rest : 7; };
struct FieldState820 { u8 pad[0x820]; void* unk820; };
struct FieldState634 { u8 pad[0x5A0]; u8 unk5a0; u8 pad5a1[0x93]; void* unk634; };
struct FieldState2C { u8 pad[0x1C]; u32 unk1c; u32 unk20; float unk24; u8 pad28[4]; u8 unk2c_0 : 1; u8 unk2c_rest : 7; };
extern "C" int func_00206280(void*);
extern "C" void func_4C9010(FieldOuter870*, void*, void*);
extern "C" void func_4A5E60(FieldState820*, void*, void*);
extern "C" void func_4D5C90(void*);
extern "C" void func_448250(FieldState634*);

struct FieldState544 { u8 pad[0x544]; float source; };
struct FieldMotion {
    FieldState544* source;
    u8 pad04[0x6C];
    u32 flags;
    u8 pad74[0x6C];
    float start;
    float target;
    float duration;
    float step;
};
struct FieldMotion2 {
    u8 pad00[0x70]; u32 flags;
    u8 pad74[0x84]; float current;
    u8 padFC[0xC]; float fallback;
    u8 pad10C[0x14]; float duration;
    float change;
    float target;
};
struct FieldMotion3 {
    u8 pad00[0x70]; u32 flags;
    float duration;
    float change;
    float target;
    u8 pad80[0x74]; float current;
    u8 padF8[0xC]; float fallback;
};
struct FieldMotion4 {
    u8 pad00[0x70]; u32 flags;
    u8 pad74[0x3C]; float current;
    float previous;
    u8 padB8[4]; float duration;
    float change;
    float target;
};

struct FieldCallbackBase { u8 pad[0xC]; };
class FieldCallbackObject : FieldCallbackBase
{
public:
    virtual void action(s32);
    virtual void finish();
};
extern "C" void func_00205260(FieldCallbackState*);
extern "C" void func_00204E40(FieldCallbackState*);

extern "C" void* func_00204A10(void*);
extern "C" void func_45B0E0(void*, void*, bool);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FD860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FD8D0);

s32 func_001FD950(void)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FD960);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FD9D0);

s32 func_001FDA50(void)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDA60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDAD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDB50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDBF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDC90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDCD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDD00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDD30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDDE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDEC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FDF20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE010);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE270);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE2F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE320);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE3A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE6D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE7A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE7D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE8B0);

s32 func_001FE950(u8* object, s32 has_index)
{
    s32 index = 0;
    if (has_index) index = **(s32**)(object + 0x548);
    if (index == -1) {
        if (*(u32*)(object + 0x5C4)) {
            *(float*)(object + 0x14) = 1.0f;
            return 0;
        }
    } else {
        void** items = (void**)(object + 0x5A4);
        void* item = items[index];
        if (!item) return 1;
        if (func_0022A160(item)) {
            *(float*)(object + 0x14) = 1.0f;
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FE9F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEB50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEC10);

void func_001FECE0(u8* object)
{
    *(u32*)(object + 0x204) &= ~0x40u;
}

void func_001FED00(u8* object)
{
    *(u32*)(object + 0x204) &= ~0x40u;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FED20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FED60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEDA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEDF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEE30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FEF40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF060);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF0D0);

void func_001FF110(u8* object)
{
    object[0x60] = object[0xA8];
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF220);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF240);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF250);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF260);

void func_001FF2C0(u8* object)
{
    func_00208C30(object);
    *(u32*)(object + 0x70) &= ~0x10u;
}

void func_001FF300(u8* object, void* value, u32 flags)
{
    func_00209160(object, value, flags);
    if (!(flags & 8)) {
        *(FieldLocalQword*)(object + 0x90) = *(FieldLocalQword*)(object + 0x10);
        if (*(u32*)(object + 0x70) & 0x10) *(u32*)(object + 0xA8) = *(u32*)(object + 0xA4);
        else *(u32*)(object + 0xA8) = -1;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF370);

void func_001FF400(u8* object)
{
    *(FieldLocalQword*)(object + 0x10) = *(FieldLocalQword*)(object + 0x90);
    *(FieldLocalQword*)(object + 0x30) = *(FieldLocalQword*)(object + 0x90);
    s32 next = *(s32*)(object + 0xA8);
    if (next >= 0) {
        *(s32*)(object + 0xA4) = next;
        func_001FF5A0(object, *(u32*)(object + 0xA4), 1);
        *(u32*)(object + 0x70) |= 0x10;
    }
}

void func_001FF460(u8* object)
{
    *(FieldLocalQword*)(object + 0x90) = *(FieldLocalQword*)(object + 0x10);
    if (*(u32*)(object + 0x70) & 0x10) *(u32*)(object + 0xA8) = *(u32*)(object + 0xA4);
    else *(u32*)(object + 0xA8) = -1;
}

void func_001FF4A0(FieldFlaggedPointerA0* object, void* value)
{
    if ((object->unk70 & 0x10) && object->unka0 == value)
    {
        object->unka0 = 0;
    }
}

s32 func_001FF4D0(u8* object)
{
    if (func_00208C80((const FieldState81*)object)) return 1;
    if (*(u32*)(object + 0x70) & 4) return 1;
    return object[0xAC];
}

void func_001FF530(FieldFlaggedPointerA0* object, void* value, u32 option)
{
    object->unka0 = value;
    object->unk81_0 = 0;
    if (value == 0) {
        object->unk70 &= ~0x10u;
        object->unka4 = -1;
    } else {
        object->unk70 |= 0x10;
        func_001FF7F0(object, option);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF5A0);

void func_001FF630(u8* object, float first, float second)
{
    *(float*)(object + 0x78) = first - *(float*)(object + 0x34);
    float zero = 0.0f;
    if (second != zero) *(float*)(object + 0x78) = *(float*)(object + 0x78) / second;
    *(float*)(object + 0x7C) = first;
    *(float*)(object + 0x74) = second;
    *(u32*)(object + 0x70) = (*(u32*)(object + 0x70) & ~0x10u) | 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF680);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF740);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FF7F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FFA10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FFC10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FFCC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_001FFEB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00200050);

void func_00200110(u8* object, u32 value)
{
    *(u32*)(object + 0x3B4) = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00200120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00200300);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002004A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002004E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00200650);

bool func_002006D0(u8* object)
{
    return *(u32*)(object + 0xC) != 0;
}

u32 func_002006E0(u8* object)
{
    return *(u32*)(object + 0x88);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002006F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00200700);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00200710);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002007B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00200970);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00200B30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00200CC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201480);

extern "C" s32 func_00201510(void* object)
{
    return 1;
}

extern "C" s32 func_00201520(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201530);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201540);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201590);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201660);

void func_002016F0(FieldResourceList14* object, s32 first, s32 second)
{
    FieldResourceListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        FieldResourceListEntry* entry = (FieldResourceListEntry*)node;
        u8 enabled = entry->unk49_1;
        if (enabled && (enabled ? entry->unk49_3 : 1) &&
            (((entry->unk1c == 0x43484152 || entry->unk1c == 0x41545243) &&
              first == (u16)entry->unk20) ||
             (entry->unk1c == 0x414E494D && second == (u16)entry->unk20)))
        {
            entry->unk40--;
        }
    }
}

void func_002017B0(FieldResourceList14* object, s32 first, s32 second)
{
    FieldResourceListNode* node = &object->unk14;
    for (;;)
    {
        node = node->next;
        if (&object->unk14 == node)
        {
            break;
        }
        FieldResourceListEntry* entry = (FieldResourceListEntry*)node;
        u8 enabled = entry->unk49_1;
        if (enabled && (enabled ? entry->unk49_3 : 1) &&
            (((entry->unk1c == 0x43484152 || entry->unk1c == 0x41545243) &&
              first == (u16)entry->unk20) ||
             (entry->unk1c == 0x414E494D && second == (u16)entry->unk20)))
        {
            entry->unk40++;
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201870);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002019C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201CF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201D70);

u32 func_00201E20(FieldResourceList14* object, u32 kind, u32 key)
{
    FieldResourceListNode* node = &object->unk14;
    FieldResourceListNode* sentinel = node;
    for (;;)
    {
        node = node->next;
        if (!node || sentinel == node)
        {
            break;
        }
        FieldResourceListEntry* entry = (FieldResourceListEntry*)node;
        if (kind == entry->unk1c && key == entry->unk20)
        {
            return entry->unk49_1 ? entry->unk18 : entry->unk14;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201EA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00201FF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002020F0);

extern "C" s32 func_00202120(void* object)
{
    return 12;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202130);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202230);

u32 func_00202240(const FieldPackedKeySource* object)
{
    return (object->unk14 << 19) | (((u32)*object->unk0c << 16) | object->unk08->unk3ac);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202270);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202620);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202840);

extern "C" FieldAssign14* func_00202990(FieldAssign14* dest, const FieldAssign14* src)
{
    dest->unk04 = src->unk04;
    dest->unk08 = src->unk08;
    dest->unk0c = src->unk0c;
    dest->unk0e = src->unk0e;
    dest->unk0f = src->unk0f;
    dest->unk10 = src->unk10;
    return dest;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002029D0);

extern "C" void func_00202BF0(FieldTransform* obj)
{
    func_00228DD0(obj);
    FieldLocalVector4 first;
    first.words[0] = 0;
    first.words[1] = 0;
    first.words[2] = 0;
    first.words[3] = 0x3F800000;
    obj->unk1a0 = first.packed;
    FieldLocalVector4 second;
    second.words[0] = 0;
    second.words[1] = 0;
    second.words[2] = 0;
    second.words[3] = 0x3F800000;
    obj->unk1c0 = second.packed;
    obj->unk3a8 = 0;
    obj->unk3a4 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202C50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00202CF0);

extern "C" void func_00203500(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203510);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203630);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002036F0);

extern "C" bool func_00203930(FieldState3BA* obj)
{
    if (!func_00227280(obj)) { return false; }
    obj->unk3bb_0 = 1;
    obj->unk3ba = 0;
    return true;
}

extern "C" s32 func_00203990(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002039A0);

extern "C" void func_002039B0(void* object)
{
}

extern "C" bool func_002039C0(const FieldVector180* obj)
{
    return obj->x != 0.0f || obj->y != 0.0f || obj->z != 0.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203A30);

extern "C" s32 func_00203A70(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203A80);

extern "C" s32 func_00203B10(void* object)
{
    return 5;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203B20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203CB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203DF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203E20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203EB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00203F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204020);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002040E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002042A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204370);

bool func_00204420(const FieldFloatGateState7C* object)
{
    if (object->unk7c == 0)
    {
        return false;
    }
    if (object->unk8c_0)
    {
        return false;
    }
    return !(object->unk90 > 0.0f);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002047D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204A10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204DC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204E40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204EC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204F80);

extern "C" void func_00204FA0(FieldByteState210* obj, u8 value)
{
    obj->unk210 = value;
    obj->unk59d_3 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00204FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00205140);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00205260);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002053D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00205480);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00205670);

extern "C" s32 func_00205700(void* object)
{
    return 14;
}

extern "C" void func_00205710(FieldSlot* object, const FieldLocalQword* value)
{
    object->unk20 = *value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00205720);

extern "C" int func_00205790(void* object)
{
    return 0;
}

extern "C" int func_002057A0(void* object)
{
    return 11;
}

extern "C" int func_002057B0(void* object)
{
    return 1;
}

extern "C" int func_002057C0(void* object)
{
    return 0;
}

extern "C" int func_002057D0(void* object)
{
    return 0;
}

extern "C" bool func_002057E0(const FieldState704* object)
{
    return object->unk704 != 0;
}

extern "C" void* func_002057F0(FieldState79C* object)
{
    return &object->unk79c;
}

extern "C" unsigned int func_00205800(const FieldState794* object)
{
    return object->unk794;
}

extern "C" int func_00205810(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00205820);

extern "C" void* func_00205850(FieldState570* object)
{
    return &object->unk570;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00205860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002058B0);

extern "C" void func_00206020(FieldOuter870* object, void* arg, void* other)
{
    if (object->unk838->unk634 && func_00206280(object->unk870))
    {
        func_4C9010(object, arg, other);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00206080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00206170);

extern "C" void func_00206200(FieldListAC* object, bool value)
{
    for (int i = 0; i < object->count; i++)
    {
        FieldItem10* item = &object->items[i];
        if (item->unk2)
        {
            if (value)
            {
                item->target->flags &= ~1;
            }
            else
            {
                item->target->flags |= 1;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00206280);

extern "C" void func_002067F0(FieldStateAD* object)
{
    if (object->unka0)
    {
        func_00206280(object);
        object->unkad_0 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00206840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002069D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00206C10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002072F0);

extern "C" void func_00207360(FieldState820* object, void* arg, void* other)
{
    if (func_00206280(object->unk820))
    {
        func_4A5E60(object, arg, other);
    }
}

extern "C" int func_002073C0(void* object)
{
    return 0;
}

extern "C" int func_002073D0(void* object)
{
    return 0;
}

extern "C" void* func_002073E0(void* object, void* value)
{
    return value;
}

extern "C" void* func_002073F0(void* object, void* value)
{
    return value;
}

extern "C" void func_00207400(FieldState634* object)
{
    if (object->unk5a0 && object->unk634)
    {
        func_4D5C90(object->unk634);
    }
    func_448250(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207450);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002074B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207570);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207630);

extern "C" void func_002077B0(FieldState2C* object, int value)
{
    object->unk1c = 0;
    object->unk20 = 0;
    object->unk24 = (float)value;
    object->unk2c_0 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002077E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002078A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002078F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002079D0);

extern "C" int func_00207AD0(void* object)
{
    return 4;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207AE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207AF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207B90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207CC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207D00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207D40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207DF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207E50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207E90);

extern "C" void func_00207EE0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207EF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207F70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00207FE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208040);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208300);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002083A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208440);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002084E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208620);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002086C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208760);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208800);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002088A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208A10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208AB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208C30);

bool func_00208C80(const FieldState81* object)
{
    return object->bit0 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208C90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208D40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00208E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00209160);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002091E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00209280);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002092E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00209350);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00209420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002094E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002095C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00209640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002096A0);

extern "C" void func_00209780(FieldMotion* object, float target, float duration)
{
    object->start = object->source->source;
    object->target = target;
    object->duration = duration;
    if (duration > 0.0f)
    {
        object->step = (object->target - object->start) / object->duration;
    }
    else
    {
        object->step = object->target - object->start;
    }
    object->flags |= 0x200;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002097F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002098C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_002099B0);

extern "C" void func_00209B30(FieldCopyState* object)
{
    object->dstB8 = object->srcB0;
    object->dst9C = object->src94;
    object->dstD0 = object->srcC8;
    object->dst110 = object->srcF0;
    object->dst150 = object->src140;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00209B60);

extern "C" void func_00209BB0(FieldMotion2* object, float target, float duration)
{
    if (target == 3.402823466e+38f)
    {
        target = object->fallback;
    }
    object->change = target - object->current;
    float zero = 0.0f;
    if (duration != zero)
    {
        object->change /= duration;
    }
    object->target = target;
    object->duration = duration;
    object->flags |= 8;
}

extern "C" void func_00209C20(FieldMotion3* object, float target, float duration)
{
    if (target == 3.402823466e+38f)
    {
        target = object->fallback;
    }
    object->change = target - object->current;
    float zero = 0.0f;
    if (duration != zero)
    {
        object->change /= duration;
    }
    object->target = target;
    object->duration = duration;
    object->flags |= 4;
}

extern "C" void func_00209C90(FieldMotion4* object, float target, float duration)
{
    float zero = 0.0f;
    if (duration != zero)
    {
        object->duration = duration;
        object->target = target;
        object->change = (target - object->current) / duration;
        object->flags |= 0x20;
    }
    else
    {
        object->current = target;
        object->previous = target;
        object->flags &= ~0x20u;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00209CF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00209EB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_00209F50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020A090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020A1E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020A340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020A470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020A600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020A790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020A9D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020B9A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020BA30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020BBA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020BC40);

extern "C" void func_0020BCF0(void* object)
{
}

extern "C" void func_0020BD00(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020BD10);

void func_0020BD60(FieldCallbackState* object)
{
    func_00205260(object);
    if (object->target)
    {
        object->target->finish();
    }
}

extern "C" void func_0020BDA0(void* object)
{
}

extern "C" bool func_0020BDB0(void* object)
{
    return func_00204A10(object) != 0;
}

extern "C" void func_0020BDD0(FieldCallbackState* object, void* context, u32 enabled)
{
    if (object->active)
    {
        func_45B0E0(object->target, context, enabled != 0);
    }
}

void func_0020BE00(FieldCallbackState* object)
{
    func_00204E40(object);
    object->active = 0;
    if (object->target)
    {
        object->target->action(1);
    }
    object->target = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020BE50);

extern "C" void func_0020BEF0(FieldAtC4* object, u32 value)
{
    object->value = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020BF00);

extern "C" void func_0020BF50(FieldAlignedSize* object, u32 size)
{
    object->size = size;
    object->rounded = (size + 0x7F) & ~0x7F;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020BF70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020BFD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020C070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020C0A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020C230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020C300);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020C360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020C4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020C750);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020CA10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020CA60);

extern "C" s32 func_0020CB20(FieldCbOwner* object, u16 kind)
{
    FieldCbLink* node = &object->sentinel;
    for (;;)
    {
        node = node->next;
        if (&object->sentinel == node)
        {
            break;
        }
        if (((FieldCbEntry*)node)->kind == kind)
        {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020CB70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020CC50);

extern "C" void* func_0020CE30(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020CE40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020CFF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020D060);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020D1A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020D330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020D4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020D5E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_001FD860", func_0020D810);
