#include "include_asm.h"
#include "overlays/cstatus/text.h"
#include "main/resident_data.h"

struct StatusObject
{
    void* methods;
    u8 unknown_04[0x30];
    u32 field_34;
    u8 flag_38 : 1;
    u8 unknown_38 : 7;
    u8 unknown_39[3];
    u32 field_3C;
    u16 field_40;
    u16 field_42;
    u32 field_44;
};

typedef struct StateC000Mode
{
    u8 unknown_00[0x10];
    s8 state_10;
    u8 unknown_11;
    u8 flag_12;
} StateC000Mode;

struct StateC000
{
    u8 unknown_00[0xA8];
    StateC000Mode* mode;
    u8 active;
    u8 unknown_AD[0x127];
    void* other;
    u8 status;
};

typedef struct OverlayNode
{
    void* value;
    struct OverlayNode* next;
} OverlayNode;

struct OverlayList
{
    OverlayNode* head;
    s32 count;
    void* methods;
};

typedef struct StatusPosition
{
    float x;
    float y;
    float z;
    float w;
} StatusPosition;

/** Partial Lib display receiver holding its position and refresh flag. */
typedef struct StatusPositionTarget
{
    u8 pad_00[0x18];
    StatusPosition position;
    u8 pad_28[0x14];
    u8 active;
} StatusPositionTarget;

/** Partial status position state; the complete receiver extent is unknown. */
struct StatusPositionOwner
{
    u8 pad_00[0xA8];
    StatusPositionTarget* target;
    s32 distance;
    u8 pad_b0[2];
    s16 timer;
    u8 state;
    u8 pad_b5[7];
    float initial_x;
    float base_x;
    float width;
};

extern u8 D_188890[];
extern u8 D_1889C0[];
extern u8 D_188CC0[];
extern u8 D_1888B0[];
extern u8 D_188BC0[];
extern u8 D_188AC0[];
extern u8 D_1888C0[];
extern u8 D_188D70[];
extern u8 D_188D60[];
extern u8 D_188D50[];
extern u8 D_175110[];

extern void func_00350D00(OverlayList* list);
extern void func_00350FA0(OverlayList* list);
extern void func_003511B0(OverlayList* list);
extern void func_2642D0(void* object);
extern void func_4618F0(void* object, s32 flags);
extern void func_2CEAF0(void* object, s32 flags);
extern void func_100B40(void* object);
extern void* func_100AC0(s32 size, s32 flags);
extern void func_00348AE0(void* object);
extern void func_4C48B0(void* object, s32 flags);
extern void func_28E2B0(void* object, s32 flags);
extern void func_2FD940(void* object);
extern void func_2CEBE0(void* object);
extern void func_00351020(void* list);
extern void func_00350E10(void* list);
extern void func_00350B70(void* list);
extern void func_00349440(void* object, s32 value);

static inline void status_set_position(StatusPositionTarget* target, float x, float y, float z, float w);

/**
 * @brief Store the display position and mark it for refresh.
 * @param target Display receiver to update.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Third position component.
 * @param w Fourth position component.
 */
static inline void status_set_position(StatusPositionTarget* target, float x, float y, float z, float w)
{
    target->position.x = x;
    target->position.y = y;
    target->position.z = z;
    target->position.w = w;
    target->active = 1;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_003483C0);

void func_00348400(void* object, u8 value)
{
    ((u8*)object)[0xC] = value;
}

u8 func_00348410(void* object)
{
    return ((u8*)object)[0xC];
}

void func_00348420(void* object, u8 value)
{
    ((u8*)object)[0x8] = value;
}

u8 func_00348430(void* object)
{
    return ((u8*)object)[0x8];
}

void func_00348440(void* object, u16 value)
{
    *(u16*)((u8*)object + 0xA) = value;
}

u16 func_00348450(void* object)
{
    return *(u16*)((u8*)object + 0xA);
}

void func_00348460(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x98) = value;
}

u32 func_00348470(void* object)
{
    return *(u32*)((u8*)object + 0x98);
}

void func_00348480(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x9C) = value;
}

u32 func_00348490(void* object)
{
    return *(u32*)((u8*)object + 0x9C);
}

void func_003484A0(void* object, u32 value)
{
    *(u32*)((u8*)object + 4) = value;
}

u32 func_003484B0(void* object)
{
    return *(u32*)((u8*)object + 4);
}

u32 func_003484C0(void* object)
{
    return *(u32*)((u8*)object + 0x10);
}

void func_003484D0(void* object)
{
}

void func_003484E0(void* object)
{
}

void func_003484F0(void* object)
{
}

void func_00348500(void* object)
{
}

void func_00348510(void* object)
{
}

void func_00348520(void* object)
{
}

void func_00348530(void* object)
{
}

void func_00348540(void* object)
{
}

void func_00348550(void* object)
{
}

void func_00348560(void* object)
{
}

void func_00348570(void* object)
{
}

void func_00348580(void* object)
{
}

void func_00348590(void* object)
{
}

void func_003485A0(void* object)
{
}

void func_003485B0(void* object)
{
}

void func_003485C0(void* object)
{
}

void func_003485D0(void* object)
{
}

void func_003485E0(void* object)
{
}

s32 func_003485F0(void* object)
{
    return 0;
}

s32 func_00348600(void* object)
{
    return 0;
}

s32 func_00348610(void* object)
{
    return 0;
}

s32 func_00348620(void* object)
{
    return 0;
}

s32 func_00348630(void* object)
{
    return 0;
}

s32 func_00348640(void* object)
{
    return 0;
}

s32 func_00348650(void* object)
{
    return 0;
}

s32 func_00348660(void* object)
{
    return 0;
}

s32 func_00348670(void* object)
{
    return 0;
}

s32 func_00348680(void* object)
{
    return 0;
}

void func_00348690(void* object)
{
}

void func_003486A0(void* object)
{
}

u8 func_003486B0(void* object)
{
    return ((u8*)object)[0xD];
}

void func_003486C0(void* object, u8 value)
{
    ((u8*)object)[0xD] = value;
}

void func_003486D0(void* object)
{
}

u32 func_003486E0(void* object)
{
    return *(u32*)((u8*)object + 0x20);
}

void func_003486F0(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x20) = value;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00348700);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00348960);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00348AE0);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00348C10);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00348D00);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00348E50);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00349070);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00349260);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00349390);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00349440);

void func_003495C0(void* object)
{
    s32 value = *(s32*)((u8*)object + 0x110);
    s32 quotient = value / 11;
    s32 remainder = value % 11;
    if (remainder == 10)
    {
        func_00349440(object, quotient * 11);
    }
    else
    {
        func_00349440(object, value + 1);
    }
}

void func_00349640(void* object)
{
    s32 value = *(s32*)((u8*)object + 0x110);
    s32 quotient = value / 11;
    s32 remainder = value % 11;
    if (remainder == 0)
    {
        func_00349440(object, quotient * 11 + 10);
    }
    else
    {
        func_00349440(object, value - 1);
    }
}

void func_003496C0(void* object)
{
    s32 value = *(s32*)((u8*)object + 0x110);
    if (value / 11 == 8)
    {
        func_00349440(object, value % 11);
    }
    else
    {
        func_00349440(object, value + 11);
    }
}

void func_00349730(void* object)
{
    s32 value = *(s32*)((u8*)object + 0x110);
    if (value / 11 == 0)
    {
        func_00349440(object, value % 11 + 88);
    }
    else
    {
        func_00349440(object, value - 11);
    }
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_003497A0);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_003498A0);

s32 func_003498C0(void* object)
{
    return 0;
}

s32 func_003498D0(void* object)
{
    return 0;
}

s32 func_003498E0(void* object)
{
    func_00348AE0(object);
    return 2;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00349900);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00349CC0);

void* func_0034AC90(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)((u8*)object + 0x38) = D_1888B0;
        func_4618F0(object, -1);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

void* func_0034ACF0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_175110;
        func_4618F0((u8*)object + 0x40, -1);
        func_4C48B0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034AD60);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034AF00);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034B0A0);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034B170);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034B190);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034B1B0);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034BDA0);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034BEA0);

s32 func_0034C000(StateC000* object)
{
    if (object->active == 1)
    {
        return 0;
    }
    if (object->mode->state_10 < 2)
    {
        return 0;
    }
    object->active = 1;
    object->mode->flag_12 = 0;
    func_28E2B0(object->mode, 1);
    if (object->other != 0)
    {
        func_2FD940(object->other);
        object->status = 1;
    }
    return 4;
}

s32 func_0034C090(StateC000* object)
{
    if (object->active == 1)
    {
        return 0;
    }
    if (object->mode->state_10 < 2)
    {
        return 0;
    }
    object->active = 1;
    object->mode->flag_12 = 0;
    func_28E2B0(object->mode, 0);
    if (object->other != 0)
    {
        func_2FD940(object->other);
        object->status = 1;
    }
    return 4;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034C130);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034C2B0);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034C410);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034C480);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034C500);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034C640);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034C870);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034F640);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034F6B0);

void* func_0034F6F0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_1889C0;
        func_00350BF0((OverlayList*)((u8*)object + 0xFC), -1);
        func_00350E90((OverlayList*)((u8*)object + 0xF0), -1);
        func_003510A0((OverlayList*)((u8*)object + 0xE4), -1);
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

void* func_0034F780(void* object)
{
    func_2CEBE0(object);
    *(void**)object = D_1889C0;
    func_00351020((u8*)object + 0xE4);
    func_00350E10((u8*)object + 0xF0);
    func_00350B70((u8*)object + 0xFC);
    *(u32*)((u8*)object + 0xA8) = 0;
    *(u8*)((u8*)object + 0xAC) = 0;
    *(u32*)((u8*)object + 0xB0) = 0;
    *(u32*)((u8*)object + 0x108) = 0;
    *(u32*)((u8*)object + 0x10C) = 0;
    *(u32*)((u8*)object + 0x110) = 0;
    *(u32*)((u8*)object + 0x114) = 0;
    *(u32*)((u8*)object + 0x118) = 0;
    *(u32*)((u8*)object + 0x11C) = 0;
    *(u32*)((u8*)object + 0x120) = 0;
    *(u32*)((u8*)object + 0x124) = 0;
    *(u32*)((u8*)object + 0x128) = 0;
    *(u32*)((u8*)object + 0x12C) = 0;
    *(u32*)((u8*)object + 0x130) = 0;
    *(u32*)((u8*)object + 0x134) = 0;
    *(u32*)((u8*)object + 0x13C) = 0;
    *(u32*)((u8*)object + 0x140) = 0;
    *(u32*)((u8*)object + 0x144) = 0;
    *(u32*)((u8*)object + 0x148) = 0;
    *(u32*)((u8*)object + 0x14C) = 0;
    *(u32*)((u8*)object + 0x150) = 0;
    *(u32*)((u8*)object + 0x154) = 0;
    *(u32*)((u8*)object + 0x158) = 0;
    *(u32*)((u8*)object + 0x15C) = 0;
    *(u32*)((u8*)object + 0x160) = 0;
    *(u32*)((u8*)object + 0x164) = 0;
    *(u32*)((u8*)object + 0x168) = 0;
    *(u32*)((u8*)object + 0x16C) = 0;
    *(u32*)((u8*)object + 0x170) = 0;
    *(u32*)((u8*)object + 0x174) = 0;
    *(u32*)((u8*)object + 0x178) = 0;
    *(u32*)((u8*)object + 0x17C) = 0;
    *(u32*)((u8*)object + 0x180) = 0;
    *(u32*)((u8*)object + 0x184) = 0;
    *(u32*)((u8*)object + 0x188) = 0;
    *(u32*)((u8*)object + 0x18C) = 0;
    *(u32*)((u8*)object + 0x190) = 0;
    *(u32*)((u8*)object + 0x194) = 0;
    *(u32*)((u8*)object + 0x1DC) = 0;
    *(u32*)((u8*)object + 0x198) = 0x822;
    *(u32*)((u8*)object + 0x19C) = 0x822;
    *(u32*)((u8*)object + 0x1A0) = 0x822;
    *(u32*)((u8*)object + 0x1A4) = 0x822;
    *(u32*)((u8*)object + 0x1A8) = 0x822;
    *(u32*)((u8*)object + 0x1AC) = 0x822;
    *(u32*)((u8*)object + 0x1B0) = 0;
    *(u32*)((u8*)object + 0xB4) = 0;
    *(u32*)((u8*)object + 0xDC) = 0;
    *(u16*)((u8*)object + 0xBC) = 0;
    *(u32*)((u8*)object + 0xC0) = 0;
    *(u32*)((u8*)object + 0xC4) = 0;
    *(u8*)((u8*)object + 0xC8) = 0;
    *(u8*)((u8*)object + 0xC9) = 0;
    *(u8*)((u8*)object + 0xCA) = 0;
    *(u8*)((u8*)object + 0xCB) = 0;
    *(u8*)((u8*)object + 0xCC) = 0;
    *(u8*)((u8*)object + 0xCD) = 0;
    *(u8*)((u8*)object + 0xCE) = 0;
    *(u8*)((u8*)object + 0xCF) = 0;
    *(u32*)((u8*)object + 0xD0) = 0;
    *(u32*)((u8*)object + 0xD4) = 0;
    *(u32*)((u8*)object + 0xD8) = 0;
    *(u8*)((u8*)object + 0x1B4) = 0;
    *(u8*)((u8*)object + 0x1B5) = 0;
    *(u32*)((u8*)object + 0x1B8) = 0;
    *(float*)((u8*)object + 0x1BC) = 50.0f;
    *(u32*)((u8*)object + 0x1C0) = 0;
    *(float*)((u8*)object + 0x1C4) = 98.0f;
    *(u8*)((u8*)object + 0x1D0) = 0;
    *(u32*)((u8*)object + 0x1D4) = 0;
    *(u8*)((u8*)object + 0x1D8) = 0;
    *(u8*)((u8*)object + 0x1D9) = 0;
    *(u8*)((u8*)object + 0x1DA) = 0;
    *(u32*)((u8*)object + 0x1E0) = 0;
    *(u32*)((u8*)object + 0x1F0) = 0;
    *(u32*)((u8*)object + 0x1E4) = 0;
    *(u32*)((u8*)object + 0x1F4) = 0;
    *(u32*)((u8*)object + 0x1E8) = 0;
    *(u32*)((u8*)object + 0x1F8) = 0;
    *(u32*)((u8*)object + 0x1EC) = 0;
    *(u32*)((u8*)object + 0x1FC) = 0;
    return object;
}

/**
 * @brief Hold the display position until its timer expires, then scroll and wrap it.
 * @param object Status state containing the display receiver and movement bounds.
 */
void func_0034F920(StatusPositionOwner* object)
{
    StatusPositionTarget* target = object->target;
    float x = target->position.x;
    float y = target->position.y;
    float z = target->position.z;
    float w = target->position.w;
    if (object->state == 0)
    {
        status_set_position(target, object->initial_x, y, z, w);
        object->timer++;
        if (!((float)object->timer <= 120.0f))
        {
            object->timer = 0;
            object->state = 1;
        }
        return;
    }
    x -= 108.0f * D_001B6690;
    if (x < object->base_x - (float)object->distance)
    {
        x = 2.0f + (object->base_x + object->width);
    }
    status_set_position(target, x, y, z, w);
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034FA10);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034FAA0);

void* func_0034FE40(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_188AC0;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034FEA0);

void* func_00350100(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_188BC0;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350160);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350200);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350220);

u32 func_00350530(void* object)
{
    return *(u32*)((u8*)object + 0x24);
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350540);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350700);

s32 func_003507E0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_003507F0);

StatusObject* func_00350890(StatusObject* object)
{
    func_2642D0(object);
    object->methods = D_188CC0;
    object->field_34 = 0;
    object->flag_38 = 0;
    object->field_3C = 0;
    object->field_44 = 0;
    object->field_40 = 0;
    object->field_42 = 0;
    return object;
}

void* func_003508F0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_188890;
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350940);

void func_003509A0(void* object)
{
}

void func_003509B0(void* object)
{
}

void* func_003509C0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_1888C0;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            func_100B40(object);
        }
    }
    return object;
}

void func_00350A20(void* object)
{
}

void func_00350A30(void* object)
{
}

s32 func_00350A40(void* object)
{
    return 0;
}

s32 func_00350A50(void* object)
{
    return 0;
}

void func_00350A60(void* object)
{
}

u32 func_00350A70(void* object)
{
    return ((u8*)object)[0x38] & 1;
}

u32 func_00350A80(void* object)
{
    return *(u32*)((u8*)object + 0x34);
}

s32 func_00350A90(void* object)
{
    return 4;
}

u32 func_00350AA0(void* object)
{
    return *(u32*)((u8*)object + 0x3C);
}

void func_00350AB0(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x24) = value;
}

void func_00350AC0(void* object, u8 value)
{
    ((u8*)object)[0x28] = value;
}

s8 func_00350AD0(void* object)
{
    return ((s8*)object)[0x28];
}

s32 func_00350AE0(void* object)
{
    return 0;
}

s32 func_00350AF0(void* object)
{
    return 0;
}

void func_00350B00(void* object)
{
}

void func_00350B10(void* object)
{
}

void func_00350B20(void* object)
{
}

void func_00350B30(void* object)
{
}

s32 func_00350B40(void* object)
{
    return 0;
}

s32 func_00350B50(void* object)
{
    return 0;
}

s32 func_00350B60(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350B70);

OverlayList* func_00350BF0(OverlayList* list, s32 flags)
{
    if (list != 0)
    {
        list->methods = D_188D70;
        func_00350D00(list);
        if (list->head != 0)
        {
            func_100B40(list->head);
            list->head = 0;
        }
        if ((s16)flags > 0)
        {
            func_100B40(list);
        }
    }
    return list;
}

void func_00350C70(OverlayList* list, void* value)
{
    OverlayNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350D00);

void func_00350D80(OverlayList* list, void* value)
{
    OverlayNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350E10);

OverlayList* func_00350E90(OverlayList* list, s32 flags)
{
    if (list != 0)
    {
        list->methods = D_188D60;
        func_00350FA0(list);
        if (list->head != 0)
        {
            func_100B40(list->head);
            list->head = 0;
        }
        if ((s16)flags > 0)
        {
            func_100B40(list);
        }
    }
    return list;
}

void func_00350F10(OverlayList* list, void* value)
{
    OverlayNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350FA0);

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00351020);

OverlayList* func_003510A0(OverlayList* list, s32 flags)
{
    if (list != 0)
    {
        list->methods = D_188D50;
        func_003511B0(list);
        if (list->head != 0)
        {
            func_100B40(list->head);
            list->head = 0;
        }
        if ((s16)flags > 0)
        {
            func_100B40(list);
        }
    }
    return list;
}

void func_00351120(OverlayList* list, void* value)
{
    OverlayNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_003511B0);

void* func_00351230(void* list, s32 count)
{
    OverlayNode* node = (*(OverlayNode**)list)->next;
    s32 i;

    for (i = 0; i < count; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void func_00351270(OverlayList* list, void* value)
{
    OverlayNode* node = func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}
