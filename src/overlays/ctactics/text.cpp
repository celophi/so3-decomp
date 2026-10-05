#include "include_asm.h"
#include "overlays/ctactics/text.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_003F90C0.h"

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

/** Partial next-selection callback receiver; its complete extent is unknown. */
struct TacticsSelectionOwner
{
    u8 pad_00[0xB0];
    FieldObject23B1D0* selection;
};

/** Partial dual-selector callback receiver; its complete extent is unknown. */
struct TacticsDualSelectionOwner
{
    u8 pad_00[0xB8];
    FieldObject23B1D0* first;
    FieldObject23B1D0* second;
    u8 use_second;
};

/** Partial tactics receiver holding a grid selection and the corresponding display list. */
struct TacticsGridOwner
{
    u8 pad_00[0x2C];
    TacticsList nodes;
    u8 pad_30[0x7C];
    TacticsPositionTarget* target;
    u8 pad_b0[4];
    FieldObject23CEA0* grid;
    u8 pad_b8[8];
    TacticsPositionTarget* indicators[3];
    u8 pad_cc[3];
    u8 selected;
    float base_x;
    float base_y;
};

/** Partial selection storage of the native Field grid receiver. */
typedef struct TacticsGrid23D170
{
    u8 pad_00[0x114];
    s16 selected;
} TacticsGrid23D170;

/** Partial tactics receiver holding the bounded display list and its grid cursor. */
struct TacticsHighlightOwner
{
    u8 pad_00[0x2C];
    TacticsList nodes;
    u8 pad_30[0x80];
    TacticsGrid23D170* grid;
    u8 pad_b4[0x24];
    FieldObject23BE00* cursor;
};

/** Partial saved selection reached through the resident reference's first pointer. */
typedef struct TacticsSavedGridSelection
{
    u8 pad_00[0x20];
    u8 selected;
} TacticsSavedGridSelection;

/** Partial resident reference used by the tactics selection callbacks. */
typedef struct TacticsGridSelectionRef
{
    TacticsSavedGridSelection* state;
} TacticsGridSelectionRef;

extern "C" TacticsGridSelectionRef* D_001B643C;

static inline bool tactics_selection_inactive(FieldObject23B1D0* selection);

static inline u8 tactics_grid_empty(FieldObject23CEA0* grid);

static inline void tactics_set_position(TacticsPositionTarget* target, float x, float y, float z, float w);

static inline void tactics_set_xy(TacticsPositionTarget* target, float x, float y);

/**
 * @brief Report whether the grid's control byte is clear.
 * @param grid Field grid containing the control byte.
 * @return One when the control byte is zero; otherwise zero.
 */
static inline u8 tactics_grid_empty(FieldObject23CEA0* grid)
{
    if (grid->unk35)
    {
        return 0;
    }
    return 1;
}

/**
 * @brief Test whether the selection control byte is clear.
 * @param selection Field coordinate selector.
 * @return True when the control byte is zero.
 */
static inline bool tactics_selection_inactive(FieldObject23B1D0* selection)
{
    if (selection->flag75)
    {
        return false;
    }
    return true;
}

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

/**
 * @brief Store the horizontal and vertical position and mark the display active.
 * @param target Display receiver to update.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
static inline void tactics_set_xy(TacticsPositionTarget* target, float x, float y)
{
    target->position.x = x;
    target->position.y = y;
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

/**
 * @brief Save the enabled grid selection and copy its node position to the display.
 * @param object Tactics receiver holding the grid, node list, and display target.
 * @return Zero when the grid's control byte is clear; otherwise one.
 */
u8 func_00349B40(TacticsGridOwner* object)
{
    if (tactics_grid_empty(object->grid) == 1)
    {
        return 0;
    }
    object->selected = object->grid->unk114;
    D_001B643C->state->selected = object->selected;
    TacticsPosition* position =
        &((TacticsPositionTarget*)func_00351BF0(&object->nodes, object->selected)->value)->position;
    LibBounds4C69B0* bounds = func_004C69B0(
        (LibObject178750*)func_00351BF0(&object->nodes, object->selected)->value);
    tactics_set_position(object->target, position->x, position->y, bounds->unk08, 24.0f);
    return 1;
}

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

/**
 * @brief Place the present indicators using the selected grid row's coordinate pairs.
 * @param object Tactics receiver holding the grid, indicators, and base coordinates.
 */
void func_00349EB0(TacticsGridOwner* object)
{
    if (object->grid != 0)
    {
        float first = 0.0f;
        float second = 0.0f;
        s16 index = object->grid->unk114;
        if (object->indicators[0] != 0)
        {
            func_00408600(index, 0, &first, &second);
            first /= 42.0f;
            second /= 42.0f;
            first -= 10.0f + 0.2f * (250.0f - second);
            tactics_set_xy(object->indicators[0], -14.400001f + (object->base_x + first),
                -16.0f + (object->base_y + second));
        }
        if (object->indicators[1] != 0)
        {
            func_00408600(index, 1, &first, &second);
            first /= 42.0f;
            second /= 42.0f;
            first -= 10.0f + 0.2f * (250.0f - second);
            tactics_set_xy(object->indicators[1], -14.400001f + (object->base_x + first),
                -16.0f + (object->base_y + second));
        }
        if (object->indicators[2] != 0)
        {
            func_00408600(index, 2, &first, &second);
            first /= 42.0f;
            second /= 42.0f;
            first -= 10.0f + 0.2f * (250.0f - second);
            tactics_set_xy(object->indicators[2], -14.400001f + (object->base_x + first),
                -16.0f + (object->base_y + second));
        }
    }
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034A120);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034A200);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034A350);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034AE50);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034AEC0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034AF20);

/**
 * @brief Advance the chosen selector one entry, wrapping after its eighth entry.
 * @param object Tactics receiver containing two selectors and the selector choice byte.
 */
void func_0034AFB0(TacticsDualSelectionOwner* object)
{
    FieldObject23B1D0* selection;
    if (object->use_second)
    {
        selection = object->second;
    }
    else
    {
        selection = object->first;
    }
    if (tactics_selection_inactive(selection))
    {
        return;
    }
    s32 index = selection->selected + 1;
    if (index >= 8)
    {
        index = 0;
    }
    func_0023B1D0(selection, index, 0);
}

/**
 * @brief Move the chosen selector back one entry, wrapping to its eighth entry.
 * @param object Tactics receiver containing two selectors and the selector choice byte.
 */
void func_0034B020(TacticsDualSelectionOwner* object)
{
    FieldObject23B1D0* selection;
    if (object->use_second)
    {
        selection = object->second;
    }
    else
    {
        selection = object->first;
    }
    if (tactics_selection_inactive(selection))
    {
        return;
    }
    s32 index = selection->selected - 1;
    if (index < 0)
    {
        index = 7;
    }
    func_0023B1D0(selection, index, 0);
}

/**
 * @brief Map the chosen selector's first three entries to entries three, five, and six.
 * @param object Tactics receiver containing two selectors and the selector choice byte.
 */
void func_0034B080(TacticsDualSelectionOwner* object)
{
    FieldObject23B1D0* selection;
    if (object->use_second)
    {
        selection = object->second;
    }
    else
    {
        selection = object->first;
    }
    if (tactics_selection_inactive(selection))
    {
        return;
    }
    s32 index = selection->selected;
    switch (index)
    {
        case 0:
            index = 3;
            break;
        case 1:
            index = 5;
            break;
        case 2:
            index = 6;
            break;
        default:
            return;
    }
    func_0023B1D0(selection, index, 0);
}

/**
 * @brief Map the chosen selector's last five entries back to its first three.
 * @param object Tactics receiver containing two selectors and the selector choice byte.
 */
void func_0034B120(TacticsDualSelectionOwner* object)
{
    FieldObject23B1D0* selection;
    if (object->use_second)
    {
        selection = object->second;
    }
    else
    {
        selection = object->first;
    }
    if (tactics_selection_inactive(selection))
    {
        return;
    }
    s32 index = selection->selected;
    switch (index)
    {
        case 3:
            index = 0;
            break;
        case 4:
            index = 1;
            break;
        case 5:
            index = 1;
            break;
        case 6:
            index = 2;
            break;
        case 7:
            index = 2;
            break;
        default:
            return;
    }
    func_0023B1D0(selection, index, 0);
}

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

/**
 * @brief Color up to six list displays and place the cursor for the selected grid entry.
 * @param object Tactics receiver holding the display list, grid, and cursor.
 */
void func_0034DD10(TacticsHighlightOwner* object)
{
    s16 selected = object->grid->selected;
    s32 index = 0;
    TacticsListNode* node = object->nodes.head->next;
    while (node != 0)
    {
        if (index >= 6)
        {
            break;
        }
        TacticsIcon* display = (TacticsIcon*)node->value;
        if (index == selected)
        {
            display->color = 0x288080;
            display->active = 1;
            func_0023B9B0(object->cursor, index,
                func_004C69B0((LibObject178750*)display)->unk08);
        }
        else
        {
            display->color = 0x808080;
            display->active = 1;
        }
        node = node->next;
        index++;
    }
}

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

/**
 * @brief Advance the enabled coordinate selector, wrapping after its eighth entry.
 * @param object Tactics receiver holding the coordinate selector.
 */
void func_0034EC80(TacticsSelectionOwner* object)
{
    FieldObject23B1D0* selection = object->selection;
    if (tactics_selection_inactive(selection))
    {
        return;
    }
    s32 index = selection->selected + 1;
    if (index >= 8)
    {
        index = 0;
    }
    func_0023B1D0(selection, index, 0);
}

/**
 * @brief Move the enabled coordinate selector back, wrapping to its eighth entry.
 * @param object Tactics receiver holding the coordinate selector.
 */
void func_0034ECD0(TacticsSelectionOwner* object)
{
    FieldObject23B1D0* selection = object->selection;
    if (tactics_selection_inactive(selection))
    {
        return;
    }
    s32 index = selection->selected - 1;
    if (index < 0)
    {
        index = 7;
    }
    func_0023B1D0(selection, index, 0);
}

/**
 * @brief Map the first three selector entries to entries three, five, and six.
 * @param object Tactics receiver holding the enabled coordinate selector.
 */
void func_0034ED20(TacticsSelectionOwner* object)
{
    FieldObject23B1D0* selection = object->selection;
    if (tactics_selection_inactive(selection))
    {
        return;
    }
    s32 index = selection->selected;
    switch (index)
    {
        case 0:
            index = 3;
            break;
        case 1:
            index = 5;
            break;
        case 2:
            index = 6;
            break;
        default:
            return;
    }
    func_0023B1D0(selection, index, 0);
}

/**
 * @brief Map the last five selector entries back to the first three.
 * @param object Tactics receiver holding the enabled coordinate selector.
 */
void func_0034EDA0(TacticsSelectionOwner* object)
{
    FieldObject23B1D0* selection = object->selection;
    if (tactics_selection_inactive(selection))
    {
        return;
    }
    s32 index = selection->selected;
    switch (index)
    {
        case 3:
            index = 0;
            break;
        case 4:
            index = 1;
            break;
        case 5:
            index = 1;
            break;
        case 6:
            index = 2;
            break;
        case 7:
            index = 2;
            break;
        default:
            return;
    }
    func_0023B1D0(selection, index, 0);
}

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

/**
 * @brief Enqueue the receiver for deferred processing.
 * @param object Receiver to append to the resident object queue.
 */
void func_00350790(void* object)
{
    func_0011ED90(D_001B65F4, object);
}

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
