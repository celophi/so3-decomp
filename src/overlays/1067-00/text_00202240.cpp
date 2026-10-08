#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_00202240.h"
#include "overlays/1067-00/text_0021FB80.h"

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

u32 func_00202240(const FieldPackedKeySource* object)
{
    return (object->unk14 << 19) | (((u32)*object->unk0c << 16) | object->unk08->unk3ac);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00202270);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00202310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00202580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00202620);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00202840);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002029D0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00202C50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00202CF0);

extern "C" void func_00203500(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00203510);

FieldClass150EB0::~FieldClass150EB0()
{
    delete unk384;
    unk384 = 0;
    delete unk3a0;
    unk3a0 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002036F0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002039A0);

extern "C" void func_002039B0(void* object)
{
}

extern "C" bool func_002039C0(const FieldVector180* obj)
{
    return obj->x != 0.0f || obj->y != 0.0f || obj->z != 0.0f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00203A30);

extern "C" s32 func_00203A70(void* object)
{
    return 4;
}

FieldClass150F50::~FieldClass150F50()
{
}

extern "C" s32 func_00203B10(void* object)
{
    return 5;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00203B20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00203CB0);

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_00203DF0(void* object)
{
    func_004D65C0(object);
    func_0011ED90(D_001B65F4, object);
}

/** Partial item flags with the enable bit word at offset 0x6A. */
struct FieldItemFlags
{
    u8 unk00[0x6A];
    u16 unk6a;
};

/** Partial item kind with its mode byte at offset 0xF. */
struct FieldItemKind
{
    u8 unk00[0xF];
    u8 unk0f;
};

/** Sixteen-byte item record. */
struct FieldItemRecord
{
    u8 unk00;
    u8 unk01[7];
    FieldItemFlags* unk08;
    FieldItemKind* unk0c;
};

/** Partial item count holder. */
struct FieldItemCount
{
    u32 unk00;
    s32 unk04;
};

/** Partial item table: records at offset 0x18 and their count holder at offset 0x20. */
struct FieldItemState
{
    u8 unk00[0x18];
    FieldItemRecord* unk18;
    u32 unk1c;
    FieldItemCount* unk20;
};

/** Partial owner of the item table at offset 0x7C (FieldClass150F90 layout). */
struct FieldItemOwner
{
    u8 unk00[0x7C];
    FieldItemState* unk7c;
};

/**
 * @brief Set or clear bit 12 of the flags of every unused mode-one item.
 * @param object Owner of the item table.
 * @param enabled True to set the bit, false to clear it.
 */
extern "C" void func_00203E20(FieldItemOwner* object, bool enabled)
{
    if (!object->unk7c)
    {
        return;
    }
    s32 count = object->unk7c->unk20->unk04;
    for (s32 index = 0; index < count; ++index)
    {
        FieldItemRecord* records = object->unk7c->unk18;
        FieldItemFlags* flags = records[index].unk08;
        if (records[index].unk00 == 0 && records[index].unk0c->unk0f == 1)
        {
            if (enabled)
            {
                flags->unk6a |= 0x1000;
            }
            else
            {
                flags->unk6a &= 0xEFFF;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00203EB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00203F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_001DD7B0__16FieldClass150F90Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002040E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204210);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002042A0__16FieldClass150F90FUc);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204370__16FieldClass150F90FUci);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204480__16FieldClass150F90FPv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002047D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204A10__16FieldClass150F90Fi);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204DC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204E40__16FieldClass150F90Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204EC0__16FieldClass150F90FPv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204F80);

extern "C" void func_00204FA0(FieldByteState210* obj, u8 value)
{
    obj->unk210 = value;
    obj->unk59d_3 = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00204FC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00205140__16FieldClass150F90Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_001DF360__16FieldClass150F90Fv);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", __dt__16FieldClass150F90Fv);

FieldClass150F90::FieldClass150F90()
{
    unk7c = 0;
    unk80 = 0;
    unk84 = 0;
    unk20 = FieldVec4A(0.0f, 0.0f, 0.0f, 1.0f);
    unk40 = FieldVec4A(1.0f, 1.0f, 1.0f, 1.0f);
    unk30 = FieldVec4A(0.0f, 0.0f, 0.0f, 1.0f);
    unk60 = unk50 = FieldVec4A(1.0f, 1.0f, 1.0f, 1.0f);
    unk88 = 0;
    unk78 = 0;
    unk74 = -1;
    unk90 = 3.0f;
    unk8c_2 = 0;
    unk8c_0 = 0;
    unk8c_1 = 0;
    unk8c_3 = 0;
    unk8c_4 = 0;
    unk8c_5 = 0;
    unk8c_6 = 0;
    unk8c_7 = 0;
    unk8d_0 = 0;
    unk8d_1 = 0;
}

/** Partial FieldClass150070 object with vtable D_150F70 in main data. */
class FieldClass150F70 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass150F70();
};

FieldClass150F70::~FieldClass150F70()
{
}

extern "C" s32 func_00205700(void* object)
{
    return 14;
}

extern "C" void func_00205710(FieldSlot* object, const FieldLocalQword* value)
{
    object->unk20 = *value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00205720);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00205820);

extern "C" void* func_00205850(FieldState570* object)
{
    return &object->unk570;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00205860);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002058B0);

extern "C" void func_00206020(FieldOuter870* object, void* arg, void* other)
{
    if (object->unk838->unk634 && func_00206280(object->unk870))
    {
        func_4C9010(object, arg, other);
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00206080);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00206170);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00206280);

extern "C" void func_002067F0(FieldStateAD* object)
{
    if (object->unka0)
    {
        func_00206280(object);
        object->unkad_0 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00206840);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002069D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00206C10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002072F0);

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

/** Partial FieldClass150F90 with vtable D_1511F0 in main data. */
class FieldClass1511F0 : public FieldClass150F90
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass1511F0();
};

FieldClass1511F0::~FieldClass1511F0()
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_002074B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00207560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00202240", func_00207570);
