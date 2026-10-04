#include "include_asm.h"
#include "overlays/1067-00/text_0024C4B0.h"
#include "overlays/lib/text_0045AD10.h"
#include "vu0.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_00207AF0.h"
#include "overlays/1067-00/text_002934A0.h"
#include "overlays/1067-00/text_00272360.h"
#include "overlays/lib/text_0046AE20.h"
#include "main/resident_0013F3E0.h"
#include "overlays/lib/text_004BD360.h"
#include "main/resident_0012F0F8.h"
#include "overlays/lib/text_00429B00.h"

struct FieldMotionVector81
{
    u8 unk00[0x10];
    FieldVec4A unk10;
    u8 unk20[0x10];
    FieldVec4A unk30;
    u8 unk40[0x30];
    u32 unk70;
    u8 unk74[0x0C];
    u8 unk80;
};
struct FieldContextVector371
{
    u8 unk00[0x308];
    void* unk308;
    u8 unk30c[0x62];
    u8 unk36e;
    u8 unk36f;
    u8 unk370_0_1 : 2;
    u8 unk370_2 : 1;
    u8 unk370_3_7 : 5;
};
/** Format used for camera table-entry names. */
static const char D_31A840[] = "Camera%02d";

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

struct FieldState260 { u8 pad[0x260]; FieldVec4A unk260; };

/** Partial context containing an angular transition. */
struct FieldContextAngle
{
    u8 unk00[0x30];
    FieldMotionAngle motion;
};

/** Partial context receiver containing its first motion state. */
struct FieldContextMotion
{
    u8 unk00[0x30];
    FieldMotionF0 motion;
};

/** Partial context containing the target motion state. */
struct FieldContextMotion4
{
    u8 unk00[0x30];
    FieldMotionC8 motion;
};

struct FieldMotion2 {
    u8 pad00[0x70]; u32 flags;
    u8 pad74[0x80]; float unkf4; float current;
    u8 padFC[0xC]; float fallback;
    u8 pad10C[0x14]; float duration;
    float change;
    float target;
};
/** Partial context containing the planar motion state and its completion byte. */
struct FieldContextMotion2
{
    u8 unk00[0x30];
    FieldMotion2 motion;
    u8 unk15c[0x212];
    u8 unk36e;
};
/** Partial command-list owner containing a motion back-pointer. */
struct FieldCommandOwner80
{
    u8 unk00[0x78];
    float unk78;
    FieldClass151460* unk7c;
};
struct FieldMotion3 {
    u8 pad00[0x70]; u32 flags;
    float duration;
    float change;
    float target;
    u8 pad80[0x74]; float current;
    u8 padF8[0xC]; float fallback;
};


/** Partial context containing the rotation state and completion byte. */
struct FieldContextRotation
{
    u8 unk00[0x30];
    FieldMotionRotation210 motion;
    u8 unk240[0x12E];
    u8 unk36e;
};


extern "C" void* func_00204A10(void*);
extern "C" void func_45B0E0(void*, void*, bool);

/** @brief Destroy the command and detach its inherited node. */
FieldClass1512C0::~FieldClass1512C0()
{
}

/** @brief Build the borrowed curve and begin its float transition. @return Always one. */
s32 FieldClass1512C0::func_00207B90()
{
    FieldContextMotion* object = (FieldContextMotion*)D_001B6430->context->unk14;
    s32 count = unk1c + 2;
    FieldObject1573D0* motion = object->motion.unk90;
    FieldFloatPair8* pair;
    s32 index;
    FieldMotionF0* channel = &object->motion;
    motion->unk14.unk00 = 0;
    delete[] motion->unk14.unk04;
    motion->unk14.unk04 = 0;
    motion->unk14.unk04 = new (0) FieldVec4B[count];
    func_00272950(&motion->unk14, 0.0f, 0.0f);
    pair = unk28;
    for (index = 0; index < unk1c; index++)
    {
        func_00272950(&motion->unk14, pair->unk00, pair->unk04);
        pair++;
    }
    func_00272950(&motion->unk14, 1.0f, 1.0f);
    func_002723E0(&motion->unk14);
    func_002934E0(motion, channel->unkb0, unk20, unk24);
    return 1;
}

/** @brief Set the motion target and duration, then complete the command. @return One. */
s32 FieldClass1512E0::func_00207CC0()
{
    FieldContextMotion* state = (FieldContextMotion*)D_001B6430->context->unk14;
    func_00209780(&state->motion, unk1c, unk20);
    return 1;
}

/** @brief Set or apply the motion target and complete the command. @return One. */
s32 FieldClass151300::func_00207D00()
{
    FieldContextMotion4* state = (FieldContextMotion4*)D_001B6430->context->unk14;
    func_00209C90(&state->motion, unk20, unk1c);
    return 1;
}

/** @brief Apply a queued planar movement at the current angle. @return Always one. */
s32 FieldClass151320::func_00207D40()
{
    FieldContextMotion2* object = (FieldContextMotion2*)D_001B6430->context->unk14;
    FieldMotion2* channel = &object->motion;
    float angle = func_00142148(channel->unkf4, channel->current);
    float first = unk20 * func_004CC3E0(angle);
    float second = unk20 * func_004CC690(angle);
    func_00209BB0(channel, first, unk1c);
    ((FieldClass151460*)channel)->func_00207EE0(second, unk1c);
    object->unk36e = 0;
    return 1;
}

/** @brief Wait for the command list's owning motion. @return Zero while active, otherwise one. */
s32 FieldClass151340::func_00207DF0()
{
    if (((FieldCommandOwner80*)unk10)->unk7c->func_00208C80())
    {
        ((FieldCommandOwner80*)unk10)->unk78 = 1.0f;
        return 0;
    }
    return 1;
}

/** @brief Begin the queued scalar motion and clear the context state. @return Always one. */
s32 FieldClass151360::func_00207E50()
{
    FieldContextMotion2* object = (FieldContextMotion2*)D_001B6430->context->unk14;
    func_00209BB0(&object->motion, unk20, unk1c);
    object->unk36e = 0;
    return 1;
}

/** @brief Begin motion through the command list's owner. @return Always one. */
s32 FieldClass151380::func_00207E90()
{
    ((FieldCommandOwner80*)unk10)->unk7c->func_00207EE0(unk20, unk1c);
    ((FieldContextMotion2*)D_001B6430->context->unk14)->unk36e = 0;
    return 1;
}

extern "C" void func_00207EE0(void* object)
{
}

/** @brief Begin the queued angular motion. @return Always one. */
s32 FieldClass1513A0::func_00207EF0()
{
    FieldContextAngle* object = (FieldContextAngle*)D_001B6430->context->unk14;
    func_00209CF0(&object->motion, unk20, unk1c);
    return 1;
}

/** @brief Begin a queued rotation and clear the context state. @return Always one. */
s32 FieldClass1513C0::func_00207F30()
{
    FieldContextRotation* object = (FieldContextRotation*)D_001B6430->context->unk14;
    func_0020A600(&object->motion, unk20, unk1c);
    object->unk36e = 0;
    return 1;
}

/** @brief Wait for readiness, then apply the owner timer. @return One when ready, otherwise zero. */
s32 FieldClass1513E0::func_00207F70()
{
    if (!D_001B6430->context->unk38->unk4c8_0)
    {
        return 0;
    }
    ((FieldClass151490*)unk10)->unk78 = (float)unk1c;
    return 1;
}

/** @brief Wait for readiness, then invoke the owner motion callback. @return One when ready, otherwise zero. */
s32 FieldClass151400::func_00207FE0()
{
    if (!D_001B6430->context->unk38->unk4c8_0)
    {
        return 0;
    }
    ((FieldClass151460*)((FieldClass151490*)unk10)->unk7c)->func_00208C30();
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0022D6C0__16FieldClass151420Fv);

/** @brief Apply the retained motion vector when resident state is ready. @return Always one. */
s32 FieldClass151440::func_00208230()
{
    if (!D_001B6430->context->unk38->unk4c8_0)
    {
        return 1;
    }
    FieldContextVector371* context = (FieldContextVector371*)D_001B6430->context->unk14;
    context->unk36e = 1;
    FieldMotionVector81* motion = (FieldMotionVector81*)((FieldClass151490*)unk10)->unk7c;
    motion->unk30 = unk20;
    if (motion->unk80 == 1)
    {
        motion->unk70 &= ~0x10;
    }
    if (!(unk30 & 1))
    {
        motion->unk10 = unk20;
        func_0010EA70(D_001B65F8, context->unk308, 75.0f, 1000.0f);
        context->unk370_2 = 1;
    }

    return 1;
}

/** @brief Destroy the command node. */
FieldClass1512E0::~FieldClass1512E0()
{
}

/** @brief Destroy the command node. */
FieldClass151300::~FieldClass151300()
{
}

/** @brief Destroy the command node. */
FieldClass151320::~FieldClass151320()
{
}

/** @brief Destroy the command node. */
FieldClass151340::~FieldClass151340()
{
}

/** @brief Destroy the command node. */
FieldClass151360::~FieldClass151360()
{
}

/** @brief Destroy the command node. */
FieldClass151380::~FieldClass151380()
{
}

/** @brief Destroy the command node. */
FieldClass1513A0::~FieldClass1513A0()
{
}

/** @brief Destroy the command and detach its inherited node. */
FieldClass1513C0::~FieldClass1513C0()
{
}

/** @brief Destroy the timer command and its inherited node. */
FieldClass1513E0::~FieldClass1513E0()
{
}

/** @brief Destroy the command and its inherited node. */
FieldClass151400::~FieldClass151400()
{
}

/** @brief Destroy the command node and its inherited record buffer. */
FieldClass151420::~FieldClass151420()
{
}

/** @brief Destroy the vector command and its inherited node. */
FieldClass151440::~FieldClass151440()
{
}

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

/** @brief Release interpolation storage, then destroy the inherited list. */
FieldClass15B900::~FieldClass15B900()
{
    func_002DCD20();
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209350);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209420);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002094E0);

/** @brief Release the owned vector array. */
FieldClass1514F8::~FieldClass1514F8()
{
    if (unk04)
    {
        delete[] unk04;
        unk04 = 0;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00209640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_002096A0);

extern "C" void func_00209780(FieldMotionF0* object, float target, float duration)
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

extern "C" void func_002098C0(FieldMotionRange* object, float target, float duration)
{
    if (target == 0.0f)
    {
        FieldVec4A measured;
        FieldVec4A delta;
        FieldVec4A length;
        const FieldVec4A& center = static_cast<FieldState260*>(D_001B6430->context->unk14)->unk260;
        delta = object->position;
        delta.x -= center.x;
        delta.y -= center.y;
        delta.z -= center.z;
        measured = delta;
        vu0_length_xyz(&length, &measured);
        object->target = length.x;
    }
    else
    {
        object->target = target;
    }
    if (duration == 0.0f)
    {
        object->start = object->target;
    }
    else
    {
        object->duration = duration;
        object->step = (object->target - object->start) / object->duration;
        object->flags |= 0x100;
    }
}

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

extern "C" void func_00209C90(FieldMotionC8* object, float target, float duration)
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

/** @brief Delete the optional channel and destroy the inherited field object. */
FieldClass151510::~FieldClass151510()
{
    if (unkA8)
    {
        delete unkA8;
        unkA8 = 0;
    }
}

/**
 * @brief Copy the inherited resource and optional channel, then bind its context.
 * @param other Source actor using the same channel protocol.
 * @return One on success; zero if either initialization fails.
 */
s32 FieldClass151510::func_00204480(void* other)
{
    if (!FieldClass150F90::func_00204480(other))
    {
        return 0;
    }
    FieldClass154D20* channel = ((FieldClass151510*)other)->unkA8;
    if (channel)
    {
        if (!func_0020BF00())
        {
            return 0;
        }
        unkA8->func_0020BD00(channel);
        unkA8->func_0020BCF0(unk80);
    }
    return 1;
}

/** @brief Default context handler. @param context Unused context pointer. */
void FieldClass154D20::func_0020BCF0(void* context)
{
}

/** @brief Default copy handler. @param other Unused source channel. */
void FieldClass154D20::func_0020BD00(FieldClass154D20* other)
{
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_00204210__16FieldClass151510Fv);

/** @brief Update the inherited object and optional channel. */
void FieldClass151510::func_001DF360()
{
    FieldClass150F90::func_001DF360();
    if (unkA8)
    {
        unkA8->func_0020BDA0();
    }
}

void FieldClass154D20::func_0020BDA0()
{
}

/** @brief Load the selected actor resource. @param key Resource key, or -1. @return One on success, zero otherwise. */
s32 FieldClass151510::func_00204A10(s32 key)
{
    return FieldClass150F90::func_00204A10(key) != 0;
}

extern "C" void func_0020BDD0(FieldCallbackState* object, void* context, u32 enabled)
{
    if (object->active)
    {
        func_45B0E0(object->target, context, enabled != 0);
    }
}

/** @brief Clear the inherited resource, aligned payload pointer, and optional channel. */
void FieldClass151510::func_00204E40()
{
    FieldClass150F90::func_00204E40();
    unkB0 = 0;
    delete unkA8;
    unkA8 = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BE50__16FieldClass151510Fv);

/** @brief Store the channel context. @param context Context pointer. */
void FieldClass153570::func_0020BCF0(void* context)
{
    unkC4 = context;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020BF00__16FieldClass151510Fv);

/** @brief Store the resource pointer and its aligned payload address. @param resource Resource address. */
void FieldClass151510::func_0020BF50(void* resource)
{
    unkAC = resource;
    unkB0 = (void*)(((u32)resource + 0x7F) & ~0x7F);
}

/** @brief Clear the optional channel, set defaults 50 and 180, and set type bit one. */
FieldClass151510::FieldClass151510()
{
    unkAC = 0;
    unkB0 = 0;
    unkA8 = 0;
    unkA0 = 50.0f;
    unkA4 = 180.0f;
    unk78 |= 0x1;
}

/** @brief Clear the optional owner's attachment and destroy the inherited node. */
FieldClass151570::~FieldClass151570()
{
    if (unk20)
    {
        unk20->unk80 = 0;
    }
}

/** @brief Detach the node and enqueue it for deferred destruction. */
void FieldClass151570::func_001DD7B0()
{
    func_004D65C0(this);
    func_0011ED90(D_001B65F4, this);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_001DF360__16FieldClass151570Fv);

/**
 * @brief Test a shape descriptor while its record range is inactive.
 * @param node Node supplying the descriptor and first record index.
 * @param other Other descriptor passed to the shape test.
 * @return Low byte of the shape-test result.
 */
extern "C" s32 func_0020C230(FieldClass1515B0* node, FieldShapeOwner18* other)
{
    FieldShapeRecord20* records = node->unk14->unk0c;
    FieldShapeRecord20* record = &records[node->unk1c];
    for (;;)
    {
        record->unk0c_4 = 0;
        if (record->unk0c_5)
        {
            break;
        }
        ++record;
    }
    s32 result = func_0045EBD0(node->unk18, other) & 0xFF;
    record = &records[node->unk1c];
    for (;;)
    {
        record->unk0c_4 = 1;
        if (record->unk0c_5)
        {
            break;
        }
        ++record;
    }
    return result;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020DBC0__16FieldClass1515E0FP17FieldShapeOwner18P16FieldShapeData10i);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020C360);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020C4C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_00207AF0", func_0020DBC0__16FieldClass151600FP17FieldShapeOwner18P16FieldShapeData10i);

/**
 * @brief Copy the entry's name and bind its matching transform.
 * @param entry Shape entry to update.
 * @param name Source of the 17-byte name buffer.
 * @return Matching transform, or null.
 */
extern "C" LibClass178A90* func_0020CA10(FieldClass151620* entry, const char* name)
{
    func_0013A4C0(entry->unk84, name, sizeof(entry->unk84));
    LibClass178A90* transform = (LibClass178A90*)func_00473390(
        ((FieldClass150F90*)D_001B6430->context->unk08->unkdc)->unk7c, entry->unk84);
    entry->shape.unk04 = transform;
    return transform;
}

/** @brief Detach the optional attachment and destroy the inherited list node. */
FieldClass151620::~FieldClass151620()
{
    if (unk80)
    {
        func_004D65C0(unk80);
        unk80->func_001DD7B0();
        unk80 = 0;
    }
}

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

/**
 * @brief Find the first specialized shape node passing the descriptor test.
 * @param object Shape list and resource owner.
 * @param other Descriptor tested against each node.
 * @param data Resource supplying the other descriptor's record array.
 * @param height Receives the matching transformed vertical offset.
 * @return Matching node, or null when the list has no match.
 */
extern "C" FieldClass1515B0* func_0020CB70(FieldClass151640* object,
    FieldShapeOwner18* other, FieldShapeData10* data, float* height)
{
    LibListNode* node = (LibListNode*)&object->unk1f0;
    D_001B656C = ((FieldShapeData10*)object->FieldClass1515D0::unk00)->unk0c;
    D_001B6570 = data->unk0c;
    for (;;)
    {
        node = node->next;
        if (!node || (LibListNode*)&object->unk1f0 == node)
        {
            break;
        }
        if (func_0020C230((FieldClass1515B0*)node, other))
        {
            FieldVec4A transformed;
            FieldVec4A* point = &((FieldShapeRecord20*)D_0050CB30.unk0c)->unk10;
            const void* matrix = D_0050CB30.unk14->func_004D00A0();
            func_00433730(matrix, point, &transformed);
            *height = transformed.y - ((FieldShapeRecord20*)D_0050CB30.unk0c)->unk04;
            return (FieldClass1515B0*)node;
        }
    }
    return 0;
}

/**
 * @brief Find a named camera for a shape node passing the query test.
 * @param object Shape resource and list owner.
 * @param query Position supplied to the shape predicate.
 * @return Camera entry handle, or null when no matching name is found.
 */
extern "C" void* func_0020CC50(FieldClass151640* object, FieldVec4A* query)
{
    FieldClass150F90* root = (FieldClass150F90*)D_001B6430->context->unk08->unkdc;
    if (!root)
    {
        return 0;
    }
    if (!root->unk7c)
    {
        return 0;
    }
    FieldClass1515D0* first = object->func_001DDCD0();
    FieldClass1515D0* second = object->func_001DDCD0();
    func_0045F580(first, second);
    LibListNode* node = (LibListNode*)&object->unk178;
    for (;;)
    {
        node = node->next;
        if (!node || (LibListNode*)&object->unk178 == node)
        {
            break;
        }
        FieldClass1515B0* shape = (FieldClass1515B0*)node;
        FieldShapeRecord20* records = shape->unk14->unk0c;
        s32 index = shape->unk18->unk0e;
        for (;;)
        {
            FieldShapeRecord20& record = records[index];
            record.unk0c_4 = 0;
            if (record.unk0c_5)
            {
                break;
            }
            ++index;
        }
        u8 found = func_0045BFB0(shape->unk18, query);
        FieldShapeRecord20* restore_records = shape->unk14->unk0c;
        s32 restore_index = shape->unk18->unk0e;
        for (;;)
        {
            FieldShapeRecord20& record = restore_records[restore_index];
            record.unk0c_4 = 1;
            if (record.unk0c_5)
            {
                break;
            }
            ++restore_index;
        }
        void* result;
        if (!found)
        {
            result = 0;
        }
        else
        {
            char name[32];
            func_0013C4F0(name, D_31A840, (u8)(shape->unk18->unk0b - 0x3f));
            result = func_00473680(((FieldClass150F90*)D_001B6430->context->unk08->unkdc)->unk7c, name);
        }
        if (result)
        {
            return result;
        }
    }
    return 0;
}

/** @brief Return this shape resource. @return The inherited resource receiver. */
FieldClass1515D0* FieldClass151640::func_001DDCD0()
{
    return this;
}

/**
 * @brief Test transform attachments against another shape resource.
 * @param object Attachment list and resource owner.
 * @param other Resource supplying the other shape descriptor.
 * @param point Point transformed in place when an attachment passes the test.
 * @return One when a test passes, otherwise zero.
 */
extern "C" u8 func_0020CE40(FieldClass151640* object, FieldClass1515D0* other,
    FieldVec4A* point)
{
    func_0045F580(object->func_001DDCD0(), other);
    FieldShapeAttributeResource resource;
    LibListNode* node = (LibListNode*)&object->unk88;
    FieldClass1515D0 storage;
    bool prepared = false;
    for (;;)
    {
        node = node->next;
        if (node == 0 || (LibListNode*)&object->unk88 == node)
        {
            break;
        }
        FieldClass151570* attachment = (FieldClass151570*)node;
        FieldClass151620* entry = attachment->unk20;
        if (entry)
        {
            if (!prepared)
            {
                resource.tag = 0x415452;
                func_0045B210(&storage, &resource);
                prepared = true;
            }
            resource.data.prefix.unk0c = &entry->record;
            D_001B656C = ((FieldShapeData10*)storage.unk00)->unk0c;
        }
        else
        {
            D_001B656C = ((FieldShapeData10*)object->func_001DDCD0()->unk00)->unk0c;
        }
        u8 passed = func_0045EBD0(attachment->unk1c,
            (FieldShapeOwner18*)((FieldShapeData30*)other->unk00 + 1));
        if (!passed)
        {
            continue;
        }
        func_00433730(&attachment->unk70, point, point);
        return 1;
    }
    return 0;
}

/**
 * @brief Test the shape entries using a temporary borrowed attribute resource.
 * @param object Receiver containing the shape list.
 * @param query Input passed to the Lib shape predicate.
 * @return One when a shape passes the predicate, otherwise zero.
 */
extern "C" s32 func_0020D060(FieldShapeListOwner20* object, void* query)
{
    if (object->count)
    {
        FieldShapeAttributeResource resource;
        resource.tag = 0x415452;
        FieldClass1515D0 storage;
        func_0045B210(&storage, &resource);
        FieldClass151620* node = (FieldClass151620*)&object->unk10;
        for (;;)
        {
            node = static_cast<FieldClass151620*>(node->unk08);
            if (node == 0 || (FieldClass151620*)&object->unk10 == node)
            {
                break;
            }
            resource.data.prefix.unk0c = &node->record;
            D_001B656C = ((FieldShapeData10*)storage.unk00)->unk0c;
            u8 result = func_0045CBE0(&node->shape, query);
            if (!result)
            {
                continue;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Test the main shape and attached shapes against a vector pair.
 * @param object Receiver containing the shape list.
 * @param query Two contiguous vectors passed to the Lib shape predicate.
 * @return One when a shape passes the predicate, otherwise zero.
 */
extern "C" s32 func_0020D1A0(FieldClass154D20* object, FieldVec4B* query)
{
    if (object->unk00 == 0)
    {
        return 0;
    }
    u8 initial_result = func_0045BD20(object->func_001DDCD0(), query, &query[1]);
    if (initial_result)
    {
        return 1;
    }
    FieldShapeListOwner20* list = (FieldShapeListOwner20*)object;
    if (list->count)
    {
        FieldShapeAttributeResource resource;
        resource.tag = 0x415452;
        FieldClass1515D0 storage;
        func_0045B210(&storage, &resource);
        FieldClass151620* node = (FieldClass151620*)&list->unk10;
        for (;;)
        {
            node = static_cast<FieldClass151620*>(node->unk08);
            if (node == 0 || (FieldClass151620*)&list->unk10 == node)
            {
                break;
            }
            resource.data.prefix.unk0c = &node->record;
            func_0045F580(&storage, &storage);
            u8 result = func_0045B920(&node->shape, query, &query[1]);
            if (!result)
            {
                continue;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Test the main shape and attached shapes against another resource.
 * @param object Receiver containing the shape list.
 * @param other Resource storage supplying the other shape descriptors.
 * @return One when a shape passes the predicate, otherwise zero.
 */
extern "C" s32 func_0020D330(FieldClass154D20* object, FieldClass1515D0* other)
{
    if (object->unk00 == 0)
    {
        return 0;
    }
    u8 initial_result = func_0045F5A0(object->func_001DDCD0(), other);
    if (initial_result)
    {
        return 1;
    }
    FieldShapeListOwner20* list = (FieldShapeListOwner20*)object;
    if (list->count)
    {
        FieldShapeAttributeResource resource;
        resource.tag = 0x415452;
        FieldClass1515D0 storage;
        func_0045B210(&storage, &resource);
        FieldClass151620* node = (FieldClass151620*)&list->unk10;
        for (;;)
        {
            node = static_cast<FieldClass151620*>(node->unk08);
            if (node == 0 || (FieldClass151620*)&list->unk10 == node)
            {
                break;
            }
            resource.data.prefix.unk0c = &node->record;
            func_0045F580(&storage, other);
            u8 result = func_0045EBD0(&node->shape, (FieldShapeData30*)other->unk00 + 1);
            if (!result)
            {
                continue;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Allocate a transform attachment and append it to the receiver's list.
 * @param object Receiver containing the attachment list.
 * @param shape Shape descriptor supplying the transform receiver.
 */
extern "C" void func_0020D4C0(FieldClass151640* object, FieldShapeOwner18* shape)
{
    FieldClass151570* node = new (0) FieldClass151570;
    node->unk18 = node->unk14 = shape->unk04;
    node->unk1c = shape;
    node->unk30 = *(const LibMatrix44Value*)node->unk18->func_004D00A0();
    object->unk88.func_004D74F0(node, (void*)-1);
}

/** @brief Test the descriptor array's terminal flag. @param shape Descriptor to test. @return Whether the array ends here. */
static inline bool field_owner_is_last(const FieldShapeOwner18* shape)
{
    if (shape->unk0a & 0x20)
    {
        return true;
    }
    return false;
}

/**
 * @brief Append attachments for descriptors whose transforms have animation channels.
 * @param object Receiver containing the attachment list.
 * @param manager Animation manager searched for bound transform channels.
 * @param shape First descriptor in the terminated descriptor array.
 * @return Last attachment created in this array, or null.
 */
extern "C" FieldClass151570* func_0020D5E0(FieldClass151640* object, LibClass178220* manager, FieldShapeOwner18* shape)
{
    if (manager == 0)
    {
        return 0;
    }
    FieldClass151570* node = 0;
    for (;; shape++)
    {
        LibClass178A90* transform = shape->unk04;
        if (shape->unk0e != -1 && transform)
        {
            bool found;
            do
            {
                found = true;
                if (func_004BDAA0(manager, (u32)transform, 0, 0) ||
                    func_004BDAA0(manager, (u32)transform, 1, 0) ||
                    func_004BDAA0(manager, (u32)transform, 2, 0))
                {
                    break;
                }
                transform = ((FieldTransformParentLink20C*)transform)->unk208;
                found = false;
            } while (transform);
            if (found)
            {
                node = new (0) FieldClass151570;
                node->unk14 = shape->unk04;
                node->unk18 = transform;
                node->unk1c = shape;
                node->unk30 = *(const LibMatrix44Value*)node->unk18->func_004D00A0();
                object->unk88.func_004D74F0(node, (void*)-1);
            }
        }
        if (shape->unk00)
        {
            func_0020D5E0(object, manager, shape->unk00);
        }
        if (field_owner_is_last(shape))
        {
            break;
        }
    }
    return node;
}

/**
 * @brief Create specialized nodes for descriptors and mark their associated records.
 * @param object Receiver supplying shape data and the destination list.
 * @param shape First descriptor in the terminated descriptor array.
 */
extern "C" void func_0020D810(FieldClass151640* object, FieldShapeOwner18* shape)
{
    FieldShapeRecord20* records = ((FieldShapeData10*)object->FieldClass1515D0::unk00)->unk0c;
    for (;; shape++)
    {
        s32 index = shape->unk0e;
        if (shape->unk0b == 1 && shape->unk04 && index != -1)
        {
            FieldClass1515E0* node = new (0) FieldClass1515E0;
            if (node == 0)
            {
                break;
            }
            node->func_0020DBC0(shape, (FieldShapeData10*)object->FieldClass1515D0::unk00, index);
            object->unk1f0.func_004D74F0(node, (void*)-1);
            for (;; index++)
            {
                records[index].unk0c_4 = 1;
                if (records[index].unk0c_5)
                {
                    break;
                }
            }
        }
        if (shape->unk00)
        {
            func_0020D810(object, shape->unk00);
        }
        if (field_owner_is_last(shape))
        {
            break;
        }
    }
}
