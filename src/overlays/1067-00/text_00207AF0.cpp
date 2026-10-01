#include "include_asm.h"
#include "overlays/1067-00/text_00207AF0.h"

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207AF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207B90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207CC0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207D00);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207D40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207DF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207E50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207E90);

extern "C" void func_00207EE0(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207EF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207F30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207F70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00207FE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208040);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208300);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002083A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208440);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002084E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208580);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208620);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002086C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208760);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208800);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002088A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208940);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208A10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208AB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208C30);

bool func_00208C80(const FieldState81* object)
{
    return object->bit0 != 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208C90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208D40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00208E60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209160);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002091E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209280);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002092E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209350);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002094E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002095C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002096A0);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002097F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002098C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002099B0);

extern "C" void func_00209B30(FieldCopyState* object)
{
    object->dstB8 = object->srcB0;
    object->dst9C = object->src94;
    object->dstD0 = object->srcC8;
    object->dst110 = object->srcF0;
    object->dst150 = object->src140;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209B60);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209CF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209EB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209F50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020A090);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020A1E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020A340);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020A470);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020A600);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020A790);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020A9D0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020B9A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BA30);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BBA0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BC40);

extern "C" void func_0020BCF0(void* object)
{
}

extern "C" void func_0020BD00(void* object)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BD10);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BE50);

extern "C" void func_0020BEF0(FieldAtC4* object, u32 value)
{
    object->value = value;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BF00);

extern "C" void func_0020BF50(FieldAlignedSize* object, u32 size)
{
    object->size = size;
    object->rounded = (size + 0x7F) & ~0x7F;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BF70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BFD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020C070);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020C0A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020C230);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020C300);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020C360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020C4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020C750);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020CA10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020CA60);

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

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020CB70);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020CC50);

extern "C" void* func_0020CE30(void* object)
{
    return object;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020CE40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020CFF0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020D060);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020D1A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020D330);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020D4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020D5E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020D810);
