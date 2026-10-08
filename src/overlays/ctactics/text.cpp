#include "include_asm.h"
#include "overlays/ctactics/text.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_003F90C0.h"

/** Partial aligned resource header with its payload size at offset 40. */
struct TacticsAlignedResource
{
    u8 unk00[0x40];
    s32 unk40;
};
/**
 * @brief Round the resource buffer to its next 128-byte boundary.
 * @param buffer Completed buffer containing the aligned header.
 * @return Header at the next aligned address, including an already aligned input.
 */
static inline TacticsAlignedResource* aligned_resource(void* buffer)
{
    return reinterpret_cast<TacticsAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}
/** Coordinate value and next link in an owned list. */
struct TacticsCoordinateNode
{
    float x;
    float y;
    TacticsCoordinateNode* next;
    /** @brief Initialize both coordinate components to zero. */
    TacticsCoordinateNode() { y = 0.0f; x = 0.0f; }
    /** @brief Finish the coordinate node lifetime. */
    ~TacticsCoordinateNode() {}
};

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

/** Partial preset receiver; the complete object extent is unknown. */
struct TacticsPresetOwner
{
    u8 pad_00[0xC0];
    TacticsPresetPosition position;
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
    u8 pad_04[0x1C];
    FieldBufferSlots* resources;
} TacticsGridSelectionRef;

extern "C" TacticsGridSelectionRef* D_001B643C;

static inline bool tactics_selection_inactive(FieldObject23B1D0* selection);

static inline u8 tactics_grid_empty(FieldObject23CEA0* grid);

static inline void set_text_position(LibObject178750* target, float x, float y, float z, float w);
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
 * @brief Store the text position and mark it for refresh.
 * @param target Text widget receiving the position.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Third position component.
 * @param w Fourth position component.
 */
static inline void set_text_position(LibObject178750* target, float x, float y, float z, float w)
{
    target->unk18.unk00 = x;
    target->unk18.unk04 = y;
    target->unk18.unk08 = z;
    target->unk18.unk0c = w;
    target->unk3c = 1;
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

ItemCreationClass175110::~ItemCreationClass175110()
{
}

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

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", __dt__19TacticsWindow18B320Fv);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", __ct__19TacticsWindow18B320Fv);

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
void func_0034DD10(TacticsWindow18B420* object)
{
    s16 selected = object->grid->unk114;
    s32 index = 0;
    FieldListNode* node = object->unk2c.unk00->unk04;
    while (node != 0)
    {
        if (index >= 6)
        {
            break;
        }
        LibObject178750* display = static_cast<LibObject178750*>(node->unk00);
        if (index == selected)
        {
            display->unk94 = 0x288080;
            display->unk3c = 1;
            func_0023B9B0(object->cursor, index,
                func_004C69B0(display)->unk08);
        }
        else
        {
            display->unk94 = 0x808080;
            display->unk3c = 1;
        }
        node = node->unk04;
        index++;
    }
}

void TacticsWindow18B420::func_slot6c()
{
    if (static_cast<s16>(grid->func_0023CDB0(1)) == 1)
    {
        return;
    }
    func_0034DD10(this);
}

void TacticsWindow18B420::func_slot68()
{
    if (static_cast<s16>(grid->func_0023CDB0(0)) == 1)
    {
        return;
    }
    func_0034DD10(this);
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034DE80);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034DF40);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034E0E0);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034E350);

TacticsWindow18B420::~TacticsWindow18B420()
{
}

TacticsWindow18B420::TacticsWindow18B420()
{
    unka8 = 0;
    unkac = 0;
    grid = 0;
    selected = -1;
    text[0] = 0;
    text[1] = 0;
    text[2] = 0;
    text[3] = 0;
    text[4] = 0;
    text[5] = 0;
    unkd4 = 0;
    cursor = 0;
    unkf4 = 0;
    unkf6 = 0;
}

void TacticsWindow18B520::func_slot64()
{
    s16 state = selected;
    LibClass175030* target;
    if (state == 3 || state == 4)
    {
        LibClass175030* state_target = reinterpret_cast<LibClass175030*>(selection);
        state_target->unk3f = 1;
    }
    else
    {
        target = reinterpret_cast<LibClass175030*>(selection);
        target->unk30 = 128.0f;
        target->unk3c = 1;
    }
}

void TacticsWindow18B520::func_slot6c()
{
    FieldObject23B1D0* selection = this->selection;
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

void TacticsWindow18B520::func_slot68()
{
    FieldObject23B1D0* selection = this->selection;
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

void TacticsWindow18B520::func_slot74()
{
    FieldObject23B1D0* selection = this->selection;
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

void TacticsWindow18B520::func_slot70()
{
    FieldObject23B1D0* selection = this->selection;
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

TacticsWindow18B520::~TacticsWindow18B520()
{
}

void TacticsWindow18B620::func_slot60(s32 text_key)
{
    if (text_key >= 0x2714 && text_key < 0x271C)
    {
        state = 0;
        timer = 0;
        func_4C6DF0(text, func_slot54(), text_key, 1);
        distance = static_cast<s32>(func_004C69B0(text)->unk08) + 6;
    }
}

void TacticsWindow18B620::func_slot5c()
{
    LibObject178750* target = text;
    float x = target->unk18.unk00;
    float y = target->unk18.unk04;
    float z = target->unk18.unk08;
    float w = target->unk18.unk0c;
    if (state == 0)
    {
        set_text_position(target, initial_x, y, z, w);
        timer++;
        if (!((float)timer <= 120.0f))
        {
            timer = 0;
            state = 1;
        }
        return;
    }
    x -= 108.0f * D_001B6690;
    if (x < base_x - (float)distance)
    {
        x = 2.0f + (base_x + width);
    }
    set_text_position(target, x, y, z, w);
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034FE50);

TacticsWindow18B620::~TacticsWindow18B620()
{
}

s32 TacticsWindow18B720::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 20);
    ItemCreationOptionResourceDisplay* first = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* second = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* third = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = func_002D3D80(D_001B643C->resources, 11);
    first->unkcc = allocation;
    second->unkcc = allocation;
    third->unkcc = allocation;
    first->unkd0 = 11;
    second->unkd0 = 11;
    third->unkd0 = 11;
    func_002D6440(first, func_002D3CC0(D_001B643C->resources, 5), 0.0f, 0.0f);
    func_002D6440(second, func_002D3CC0(D_001B643C->resources, 6), 256.0f, 0.0f);
    func_002D6440(third, func_002D3CC0(D_001B643C->resources, 7), 512.0f, 0.0f);
    func_004C6190(unk10, first);
    func_004C6190(unk10, second);
    func_004C6190(unk10, third);
    return 1;
}

TacticsWindow18B720::~TacticsWindow18B720()
{
}

void TacticsState18B820::func_00263D80()
{
    if (unk34 != 0)
    {
        func_00465430(D_001B657C, unk34);
    }
    func_004D65C0(this);
    func_001DD7B0();
}

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

s32 TacticsState18B820::func_001E1820(void* buffer)
{
    if (buffer == 0)
    {
        return 0;
    }
    TacticsAlignedResource* aligned = aligned_resource(buffer);
    s32 size = aligned->unk40 + 0x80;
    void* saved_heap = func_00100C90();
    void* heap = D_001B6430->context->unk70;
    void* memory = func_00113710(heap, size);
    if (memory != 0)
    {
        func_001134C0(memory);
        func_00100C80(heap);
    }
    unk34 = func_004656B0(D_001B657C, aligned);
    func_00100C80(saved_heap);
    return func_00263CD0();
}

u8 TacticsState18B820::func_00264110()
{
    selection = new (0) FieldRecordSelection;
    u8 result = func_0028E3D0(selection);
    if (selection == 0 || result == 0)
    {
        return 0;
    }
    return 1;
}

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

TacticsList18B8E0::TacticsList18B8E0()
{
    head = new (0) TacticsListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

TacticsList18B8E0::~TacticsList18B8E0()
{
    func_00351520(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00351520(TacticsList18B8E0* list)
{
    TacticsListNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        TacticsListNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

void func_003515A0(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* cursor = list->unk00;
        while (cursor->unk04 != 0)
        {
            cursor = cursor->unk04;
        }
        cursor->unk04 = node;
        list->unk04++;
    }
}

void func_00351630(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* cursor = list->unk00;
        while (cursor->unk04 != 0)
        {
            cursor = cursor->unk04;
        }
        cursor->unk04 = node;
        list->unk04++;
    }
}

void func_003516C0(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* cursor = list->unk00;
        while (cursor->unk04 != 0)
        {
            cursor = cursor->unk04;
        }
        cursor->unk04 = node;
        list->unk04++;
    }
}

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


TacticsList18B8D0::TacticsList18B8D0()
{
    head = new (0) TacticsListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

TacticsList18B8D0::~TacticsList18B8D0()
{
    func_00351920(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00351890(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* cursor = list->unk00;
        while (cursor->unk04 != 0)
        {
            cursor = cursor->unk04;
        }
        cursor->unk04 = node;
        list->unk04++;
    }
}

void func_00351920(TacticsList18B8D0* list)
{
    TacticsListNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        TacticsListNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

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


TacticsList18B8C0::TacticsList18B8C0()
{
    head = new (0) TacticsListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

TacticsList18B8C0::~TacticsList18B8C0()
{
    func_00351B70(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00351AE0(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* cursor = list->unk00;
        while (cursor->unk04 != 0)
        {
            cursor = cursor->unk04;
        }
        cursor->unk04 = node;
        list->unk04++;
    }
}

void func_00351B70(TacticsList18B8C0* list)
{
    TacticsListNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        TacticsListNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

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


void func_00351C30(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* cursor = list->unk00;
        while (cursor->unk04 != 0)
        {
            cursor = cursor->unk04;
        }
        cursor->unk04 = node;
        list->unk04++;
    }
}

void func_00351CC0(FieldCountedList* list, void* value)
{
    FieldListNode* node = new (0) FieldListNode;
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* cursor = list->unk00;
        while (cursor->unk04 != 0)
        {
            cursor = cursor->unk04;
        }
        cursor->unk04 = node;
        list->unk04++;
    }
}

TacticsList18B8B0::~TacticsList18B8B0()
{
    func_00351DD0(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00351DD0(TacticsList18B8B0* list)
{
    TacticsCoordinateNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        TacticsCoordinateNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

void func_00351E50(TacticsList18B8B0* list, TacticsPresetPosition value)
{
    TacticsCoordinateNode* node = new (0) TacticsCoordinateNode;
    if (node != 0)
    {
        node->x = value.x;
        node->y = value.y;
        node->next = 0;
        TacticsCoordinateNode* cursor = list->head;
        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }
        cursor->next = node;
        list->count++;
    }
}

TacticsList18B8B0::TacticsList18B8B0()
{
    head = new (0) TacticsCoordinateNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00351F90);
