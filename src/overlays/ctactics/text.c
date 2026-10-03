#include "include_asm.h"
#include "overlays/ctactics/text.h"
#include "main/resident_data.h"

typedef struct
{
    u8 pad_00[0x3C];
    u8 active;
    u8 pad_3d[0x57];
    u32 color;
} TacticsIcon;

typedef struct TacticsIconNode
{
    TacticsIcon* icon;
    struct TacticsIconNode* next;
} TacticsIconNode;

typedef struct
{
    u8 pad_00[4];
    TacticsIconNode* next;
} TacticsIconList;

typedef struct
{
    u8 pad_00[0x2C];
    TacticsIconList* list;
} TacticsIconOwner;

typedef struct TacticsPosition
{
    float x;
    float y;
    float z;
    float w;
} TacticsPosition;

/** Partial Lib display receiver holding its position and refresh flag. */
typedef struct TacticsPositionTarget
{
    u8 pad_00[0x18];
    TacticsPosition position;
    u8 pad_28[0x14];
    u8 active;
} TacticsPositionTarget;

/** Partial tactics position state; the complete receiver extent is unknown. */
struct TacticsPositionOwner
{
    u8 pad_00[0xA8];
    TacticsPositionTarget* target;
    s32 distance;
    s16 timer;
    u8 state;
    u8 pad_b3[5];
    float initial_x;
    float base_x;
    float width;
};

/** Partial preset receiver; the complete object extent is unknown. */
struct TacticsPresetOwner
{
    u8 pad_00[0xC0];
    TacticsPresetPosition position;
};

static inline void tactics_set_position(TacticsPositionTarget* target, float x, float y, float z, float w);

/**
 * @brief Store the display position and mark it for refresh.
 * @param target Display receiver to update.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Third position component.
 * @param w Fourth position component.
 */
static inline void tactics_set_position(TacticsPositionTarget* target, float x, float y, float z, float w)
{
    target->position.x = x;
    target->position.y = y;
    target->position.z = z;
    target->position.w = w;
    target->active = 1;
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003483C0);

void func_00348400(void* object)
{
}

void func_00348410(void* object, s16 selected)
{
    s32 index = 0;
    TacticsIconNode* node = ((TacticsIconOwner*)object)->list->next;
    if (node != 0)
    {
        do
        {
            TacticsIcon* icon = node->icon;
            if (index == selected)
            {
                icon->color = 0x288080;
                icon->active = 1;
            }
            else
            {
                icon->color = 0x808080;
                icon->active = 1;
            }
            node = node->next;
            index++;
        } while (node != 0);
    }
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348480);

u32 func_003484C0(void* object)
{
    return *(u32*)((u8*)object + 0x20);
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003484D0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348530);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348590);

void func_00348630(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x20) = value;
}

u32 func_00348640(void* object)
{
    return *(u32*)((u8*)object + 0x98);
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348650);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348720);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348BF0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348C50);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348D40);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348E40);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348F90);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003490F0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003497D0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00349830);

u32 func_003499A0(void* object)
{
    return *(u32*)((u8*)object + 0x9C);
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003499B0);

void func_00349B20(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x98) = value;
}

u32 func_00349B30(void* object)
{
    return *(u32*)((u8*)object + 0x4);
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00349B40);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00349C10);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00349D40);

void func_00349E70(void* object)
{
    void* first;
    void* second;

    first = *(void**)((u8*)object + 0xB4);
    if (first != 0)
    {
        *(float*)((u8*)first + 0xE0) = 128.0f;
        *(u8*)((u8*)first + 0xAE) = 1;
    }

    second = *(void**)((u8*)object + 0xB0);
    if (second != 0)
    {
        *(u32*)((u8*)second + 0xD0) = 0x22;
        *(u8*)((u8*)second + 0x3C) = 1;
    }
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00349EB0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034A120);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034A200);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034A350);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034AE50);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034AEC0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034AF20);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034AFB0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034B020);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034B080);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034B120);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034B1E0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034B390);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034BA40);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034C120);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034D900);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034D990);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034D9F0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034DB20);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034DC00);

void func_0034DCF0(void* object)
{
}

u32 func_0034DD00(void* object)
{
    return *(u32*)((u8*)object + 0x24);
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034DD10);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034DDE0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034DE30);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034DE80);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034DF40);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034E0E0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034E350);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034EB60);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034EBC0);

void func_0034EC30(void* object)
{
    s16 state = *(s16*)((u8*)object + 0xB4);
    void* target;

    if (state == 3 || state == 4)
    {
        u8* state_target = *(u8**)((u8*)object + 0xB0);
        state_target[0x3F] = 1;
    }
    else
    {
        target = *(void**)((u8*)object + 0xB0);
        *(float*)((u8*)target + 0x70) = 128.0f;
        *(u8*)((u8*)target + 0x3C) = 1;
    }
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034EC80);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034ECD0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034ED20);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034EDA0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034EE50);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034EFA0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034F0E0);

/**
 * @brief Select a preset display position, clearing it for an invalid index.
 * @param object Receiver holding the position pair.
 * @param index Zero-based preset index.
 * @return The receiver's updated position pair.
 */
TacticsPresetPosition* func_0034F190(TacticsPresetOwner* object, s32 index)
{
    switch (index)
    {
    case 0:
        object->position.x = 96.0f;
        object->position.y = 68.0f;
        break;
    case 1:
        object->position.x = 96.0f;
        object->position.y = 188.0f;
        break;
    case 2:
        object->position.x = 96.0f;
        object->position.y = 308.0f;
        break;
    case 3:
        object->position.x = 390.0f;
        object->position.y = 38.0f;
        break;
    case 4:
        object->position.x = 390.0f;
        object->position.y = 110.0f;
        break;
    case 5:
        object->position.x = 390.0f;
        object->position.y = 182.0f;
        break;
    case 6:
        object->position.x = 390.0f;
        object->position.y = 254.0f;
        break;
    case 7:
        object->position.x = 390.0f;
        object->position.y = 326.0f;
        break;
    default:
        object->position.x = 0.0f;
        object->position.y = 0.0f;
        break;
    }
    return &object->position;
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034F290);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034FC70);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034FCD0);

/**
 * @brief Hold the display position until its timer expires, then scroll and wrap it.
 * @param object Tactics state containing the display receiver and movement bounds.
 */
void func_0034FD60(TacticsPositionOwner* object)
{
    TacticsPositionTarget* target = object->target;
    float x = target->position.x;
    float y = target->position.y;
    float z = target->position.z;
    float w = target->position.w;
    if (object->state == 0)
    {
        tactics_set_position(target, object->initial_x, y, z, w);
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
    tactics_set_position(target, x, y, z, w);
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034FE50);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00350430);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00350490);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003506E0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00350740);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00350790);

void func_003507B0(void* object)
{
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003507C0);

void func_00350D10(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x9C) = value;
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00350D20);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00350DE0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00350E60);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00350F00);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00350F60);

void func_00351020(void* object)
{
}

s32 func_00351030(void* object)
{
    return 3;
}

void func_00351040(void* object)
{
}

void func_00351050(void* object, u8 value)
{
    *(u8*)((u8*)object + 0xC) = value;
}

u8 func_00351060(void* object)
{
    return *(u8*)((u8*)object + 0xC);
}

void func_00351070(void* object, u8 value)
{
    *(u8*)((u8*)object + 0x8) = value;
}

u8 func_00351080(void* object)
{
    return *(u8*)((u8*)object + 0x8);
}

void func_00351090(void* object, u16 value)
{
    *(u16*)((u8*)object + 0xA) = value;
}

u16 func_003510A0(void* object)
{
    return *(u16*)((u8*)object + 0xA);
}

void func_003510B0(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x4) = value;
}

u32 func_003510C0(void* object)
{
    return *(u32*)((u8*)object + 0x10);
}

void func_003510D0(void* object)
{
}

void func_003510E0(void* object)
{
}

void func_003510F0(void* object)
{
}

void func_00351100(void* object)
{
}

void func_00351110(void* object)
{
}

void func_00351120(void* object)
{
}

void func_00351130(void* object)
{
}

void func_00351140(void* object)
{
}

void func_00351150(void* object)
{
}

void func_00351160(void* object)
{
}

void func_00351170(void* object)
{
}

void func_00351180(void* object)
{
}

void func_00351190(void* object)
{
}

void func_003511A0(void* object)
{
}

void func_003511B0(void* object)
{
}

void func_003511C0(void* object)
{
}

void func_003511D0(void* object)
{
}

s32 func_003511E0(void* object)
{
    return 0;
}

s32 func_003511F0(void* object)
{
    return 0;
}

s32 func_00351200(void* object)
{
    return 0;
}

s32 func_00351210(void* object)
{
    return 0;
}

s32 func_00351220(void* object)
{
    return 0;
}

s32 func_00351230(void* object)
{
    return 0;
}

s32 func_00351240(void* object)
{
    return 0;
}

s32 func_00351250(void* object)
{
    return 0;
}

s32 func_00351260(void* object)
{
    return 0;
}

s32 func_00351270(void* object)
{
    return 0;
}

void func_00351280(void* object)
{
}

void func_00351290(void* object)
{
}

u8 func_003512A0(void* object)
{
    return *(u8*)((u8*)object + 0xD);
}

void func_003512B0(void* object, u8 value)
{
    *(u8*)((u8*)object + 0xD) = value;
}

void func_003512C0(void* object)
{
}

void func_003512D0(void* object)
{
}

void func_003512E0(void* object)
{
}

void func_003512F0(void* object)
{
}

s32 func_00351300(void* object)
{
    return 0;
}

s32 func_00351310(void* object)
{
    return 0;
}

u32 func_00351320(void* object)
{
    return *(u8*)((u8*)object + 0x38) & 1;
}

u32 func_00351330(void* object)
{
    return *(u32*)((u8*)object + 0x34);
}

s32 func_00351340(void* object)
{
    return 4;
}

void func_00351350(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x24) = value;
}

void func_00351360(void* object, u8 value)
{
    *(u8*)((u8*)object + 0x28) = value;
}

s8 func_00351370(void* object)
{
    return *(s8*)((u8*)object + 0x28);
}

s32 func_00351380(void* object)
{
    return 0;
}

s32 func_00351390(void* object)
{
    return 0;
}

void func_003513A0(void* object)
{
}

s32 func_003513B0(void* object)
{
    return 0;
}

void func_003513C0(void* object)
{
}

void func_003513D0(void* object)
{
}

void func_003513E0(void* object)
{
}

s32 func_003513F0(void* object)
{
    return 0;
}

s32 func_00351400(void* object)
{
    return 0;
}

s32 func_00351410(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351420);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003514A0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351520);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003515A0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351630);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003516C0);

TacticsListNode* func_00351750(TacticsList* list, s32 index)
{
    TacticsListNode* node = list->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}


INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351790);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351810);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351890);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351920);

TacticsListNode* func_003519A0(TacticsList* list, s32 index)
{
    TacticsListNode* node = list->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}


INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_003519E0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351A60);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351AE0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351B70);

TacticsListNode* func_00351BF0(TacticsList* list, s32 index)
{
    TacticsListNode* node = list->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}


INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351C30);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351CC0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351D50);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351DD0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351E50);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351F00);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351F90);
