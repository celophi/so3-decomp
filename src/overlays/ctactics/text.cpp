#include "include_asm.h"
#include "overlays/ctactics/text.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002607B0.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/grid_marker.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_003F90C0.h"
#include "overlays/lib/scalar_indicator_inlines.h"

/**
 * @brief Clear the grid window's selection state and resource keys.
 * @param object Grid window to reset.
 */
static inline void clear_grid_state(TacticsWindow18B420* object)
{
    object->unkf4 = 0;
    object->unkf6 = 0;
    object->keys[0] = 0;
    object->keys[1] = 0;
    object->keys[2] = 0;
    object->keys[3] = 0;
    object->keys[4] = 0;
    object->keys[5] = 0;
}

/** Resident entry record with its saved grid entry at offset 0x38 and stride 0x114. */
struct TacticsEntryResourceRecord
{
    u8 unk00[0x38];
    u8 selected_entry;
    u8 previous_entry;
    u8 unk3a[0xDA];
};

/** Resource table record with a signed kind and a verified C4-byte stride. */
struct TacticsGridResourceRecord
{
    s16 kind;
    u8 unk02[0xC2];
};

/**
 * @brief Return a text display from the grid window's owned display list.
 * @param object Grid window containing the list.
 * @param index Node index.
 * @return Display payload stored in the indexed node.
 */
static inline LibObject178750* grid_display(TacticsWindow18B420* object, s32 index)
{
    return static_cast<LibObject178750*>(func_00351BF0(
        reinterpret_cast<TacticsList*>(&object->unk2c), index)->value);
}

/**
 * @brief Update a widget rectangle and request its refresh.
 * @param object Widget to position.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
static inline void set_widget_rectangle(LibClass178600* object, float x, float y,
    float width, float height)
{
    object->unk18.unk00 = x;
    object->unk18.unk04 = y;
    object->unk18.unk08 = width;
    object->unk18.unk0c = height;
    object->unk3c = 1;
}

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
    u8 selected_resource_code;
} TacticsSavedGridSelection;

/** Partial callback directory containing its active native State. */
struct TacticsRuntimeCallbacks
{
    u8 unk00[0x14];
    FieldClass153E30* state;
};

/** Partial resident reference used by the tactics selection callbacks. */
typedef struct TacticsGridSelectionRef
{
    TacticsSavedGridSelection* state;
    void* records04;
    void* records08;
    FieldClass153E00* runtime;
    TacticsRuntimeCallbacks* callbacks;
    u8 pad_14[0xC];
    FieldBufferSlots* resources;
} TacticsGridSelectionRef;

extern "C" TacticsGridSelectionRef* D_001B643C;
extern "C" LibWidgetColors4C5590 D_00352000;

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

extern "C" LibWidgetColors4C5590 D_00352010;
/** Four packed colors copied into the child title panel. */
extern "C" LibWidgetColors4C5590 D_00352020;

/**
 * @brief Read the string-backed icon in the window's display list.
 * @param object Icon-grid window containing the list.
 * @param index Display index.
 * @return Icon stored in the selected list node.
 */
static inline LibObject175140* icon_display(TacticsWindow18B120* object, s32 index)
{
    return static_cast<LibObject175140*>(func_00351750(
        reinterpret_cast<TacticsList*>(&object->unk44), index)->value);
}

/**
 * @brief Test whether a resource slot has no entry code.
 * @param resource Record selection containing the slot codes.
 * @param index Signed resource slot index.
 * @return True when the slot's entry code is zero.
 */
static inline bool icon_resource_empty(FieldRecordSelection* resource, s16 index)
{
    if (*reinterpret_cast<const u8*>(&resource->slots[index]))
    {
        return false;
    }
    return true;
}

/**
 * @brief Fit the indicator to the selected icon's position and drawing width.
 * @param object Icon-grid window whose selected display supplies the rectangle.
 */
static inline void position_icon_indicator(TacticsWindow18B120* object)
{
    if (icon_display(object, object->grid_entries[object->selected]) != 0)
    {
        LibUiRect16* position = &icon_display(object,
            object->grid_entries[object->selected])->unk18;
        LibBounds4C69B0* bounds = func_00467950(icon_display(object,
            object->grid_entries[object->selected]));
        set_widget_rectangle(object->indicator, position->unk00, position->unk04,
            bounds->unk08, 24.0f);
    }
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

/** @brief Move to the following grid entry and update its text highlight. */
void TacticsWindow18B020::func_slot6c()
{
    if (grid->func_0023CDB0(1) != 1)
    {
        func_slotf8(grid->unk114);
    }
}

/** @brief Move to the preceding grid entry and update its text highlight. */
void TacticsWindow18B020::func_slot68()
{
    if (grid->func_0023CDB0(0) != 1)
    {
        func_slotf8(grid->unk114);
    }
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348590);

void func_00348630(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x20) = value;
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_00348650);

/**
 * @brief Create the child window's two-entry grid, panels, and text displays.
 * @param associated Full resource source word forwarded to the base and displays.
 * @param x Horizontal window position.
 * @param y Vertical window position.
 * @param code Base window initializer code.
 * @param text_key Text key for the heading display.
 * @return One after initialization, or zero when a required display or grid is absent.
 */
s32 TacticsWindow18B020::func_slotf4(u32 associated, float x, float y,
    s32 code, s32 text_key)
{
    FieldClass15AE70::func_slot10(associated, x, y, code);
    LibWidgetColors4C5590 colors = D_00352020;
    LibClass178630* title_panel = new (0) LibClass178630;
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 1, 0.0f, 0.0f, 290.0f, 208.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_00351CC0(&unk14, panel);
    func_004C5A80(title_panel, 1, 0.0f, 0.0f, 290.0f, 40.0f, 88.0f);
    func_4C5590(title_panel, &colors);
    func_004C6190(unk10, title_panel);
    func_00351CC0(&unk14, title_panel);
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    LibObject178750* heading = new (0) LibObject178750;
    LibObject178750* notice = new (0) LibObject178750;
    grid = new (0) FieldObject23CEA0;
    if (first == 0 || second == 0 || heading == 0 || grid == 0)
    {
        return 0;
    }
    func_004C7FE0(first, associated, 0x7E8, 0, 110.0f, 132.0f, 0.0f, 0.0f);
    func_004C7FE0(second, associated, 0x7E9, 0, 110.0f, 168.0f, 0.0f, 0.0f);
    func_004C7FE0(heading, associated, text_key, 0, 24.0f, 64.0f, 0.0f, 0.0f);
    func_004C7FE0(notice, associated, 0x29D0, 0, 0.0f, 8.0f, 290.0f, 40.0f);
    notice->set_mode(1);
    func_004C6190(unk10, first);
    func_004C6190(unk10, second);
    func_004C6190(unk10, heading);
    func_004C6190(unk10, notice);
    func_00351AE0(&unk2c, first);
    func_00351AE0(&unk2c, second);
    func_00351AE0(&unk2c, heading);
    func_00351AE0(&unk2c, notice);
    grid->func_0023CE80(1, 2);
    grid->func_0023CE60(0.0f, 36.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(1, 110.0f + x, 132.0f + y);
    func_00351630(&unk74, grid);
    func_slotf8(grid->unk114);
    return 1;
}

/** @brief Destroy the child window's base. */
TacticsWindow18B020::~TacticsWindow18B020()
{
}

/** @brief Move to the following grid entry and update the icon highlight. */
void TacticsWindow18B120::func_slot6c()
{
    if (entry_count != 1)
    {
        if (grid->func_0023CDB0(1) != 1)
        {
            s32 selected_entry = grid->unk114;
            s32 index = 0;
            FieldListNode* node = unk44.unk00->unk04;
            if (node != 0)
            {
                do
                {
                    LibObject175140* icon = static_cast<LibObject175140*>(node->unk00);
                    if (index == selected_entry)
                    {
                        icon->set_color(0x288080);
                        func_0023B9B0(cursor, selected_entry, func_00467950(icon)->unk08);
                    }
                    else
                    {
                        icon->set_color(0x808080);
                    }
                    node = node->unk04;
                    index++;
                } while (node != 0);
            }
        }
    }
}

/** @brief Move to the preceding grid entry and update the icon highlight. */
void TacticsWindow18B120::func_slot68()
{
    if (entry_count != 1)
    {
        if (grid->func_0023CDB0(0) != 1)
        {
            s32 selected_entry = grid->unk114;
            s32 index = 0;
            FieldListNode* node = unk44.unk00->unk04;
            if (node != 0)
            {
                do
                {
                    LibObject175140* icon = static_cast<LibObject175140*>(node->unk00);
                    if (index == selected_entry)
                    {
                        icon->set_color(0x288080);
                        func_0023B9B0(cursor, selected_entry, func_00467950(icon)->unk08);
                    }
                    else
                    {
                        icon->set_color(0x808080);
                    }
                    node = node->unk04;
                    index++;
                } while (node != 0);
            }
        }
    }
}

/**
 * @brief Restore the saved grid entry, refresh its icon, and return to the associated window.
 * @return Two after restoring the associated window.
 */
s32 TacticsWindow18B120::func_slotb4()
{
    FieldObject23CEA0* selected_grid = grid;
    if (selected_grid != 0)
    {
        selected_grid->index = grid_entries[selected];
        func_0023CB30(selected_grid);
        func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(grid));
        grid->unkad = 0;
    }
    s32 selected_entry = grid_entries[selected];
    s32 index = 0;
    FieldListNode* node = unk44.unk00->unk04;
    if (node != 0)
    {
        do
        {
            LibObject175140* icon = static_cast<LibObject175140*>(node->unk00);
            if (index == selected_entry)
            {
                icon->set_color(0x288080);
                func_0023B9B0(cursor, selected_entry, func_00467950(icon)->unk08);
            }
            else
            {
                icon->set_color(0x808080);
            }
            node = node->unk04;
            index++;
        } while (node != 0);
    }
    func_slot20(0);
    FieldClass15AE70* parent = static_cast<FieldClass15AE70*>(func_slot44());
    parent->func_slot64();
    D_001B643C->callbacks->state->func_00263C70(parent);
    return 2;
}

/**
 * @brief Save the chosen resource code and update the parent label.
 * @return One after the selected resource code is applied.
 */
s32 TacticsWindow18B120::func_slotb0()
{
    for (s32 index = 0; index < 3; index++)
    {
        if (grid_entries[index] == grid->unk114)
        {
            selected = index;
        }
    }
    D_001B643C->state->selected_resource_code = entries[grid_entries[selected]];
    if (icon_display(this, grid_entries[selected]) != 0)
    {
        position_icon_indicator(this);
    }
    func_0034A120(static_cast<TacticsWindow18B220*>(func_slot44()), entries[grid_entries[selected]]);
    return 1;
}

/**
 * @brief Initialize the resource icons, grid, marker, and indicator.
 * @param associated Full resource source word forwarded to the base and title.
 * @return Zero when a panel allocation or resource link fails; otherwise one.
 */
s32 TacticsWindow18B120::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 200.0f, 136.0f, 8);
    LibClass178630* panel = new (0) LibClass178630;
    if (panel == 0)
    {
        return 0;
    }
    func_004C5A80(panel, 1, 0.0f, 0.0f, 232.0f, 148.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_00351CC0(&unk14, panel);
    LibClass178630* title_panel = new (0) LibClass178630;
    if (title_panel == 0)
    {
        return 0;
    }
    func_004C5A80(title_panel, 1, 0.0f, 0.0f, 232.0f, 40.0f, 88.0f);
    LibWidgetColors4C5590 colors = D_00352010;
    func_4C5590(title_panel, &colors);
    func_004C6190(unk10, title_panel);
    func_00351CC0(&unk14, title_panel);
    LibObject178750* title = new (0) LibObject178750;
    func_004C7FE0(title, associated, 0x272A, 1, 42.0f, 8.0f, 0.0f, 0.0f);
    func_004C6190(unk10, title);
    if (resource == 0)
    {
        return 0;
    }
    selected = -1;
    u8 entry;
    s32 grid_entry = 0;
    u8 saved_entry = D_001B643C->state->selected_resource_code;
    entry_count = 0;
    for (s32 index = 0; index < 3; index++)
    {
        grid_entries[index] = 0;
        entry = static_cast<u8>(resource->slots[static_cast<s16>(index)]);
        if (entry != 0)
        {
            LibObject175140* icon = new (0) LibObject175140;
            float y = 48.0f + 28.0f * entry_count;
            icon->func_00467AD0(24.0f, y, 0.0f, 0.0f,
                reinterpret_cast<const char*>(&static_cast<TacticsEntryResourceRecord*>(
                    resource->unk04)[static_cast<s16>(index)]) + 0x20, 0);
            func_004C6190(unk10, icon);
            func_003516C0(&unk44, icon);
            grid_entries[index] = grid_entry;
            grid_entry++;
            entries[entry_count++] = entry;
            if (saved_entry == entry)
            {
                selected = index;
            }
        }
    }
    if (selected == -1)
    {
        for (s32 index = 0; index < 3; index++)
        {
            if (icon_resource_empty(resource, index))
            {
                continue;
            }
            selected = index;
            break;
        }
    }
    if (selected == -1)
    {
        selected = 0;
    }
    base_x = 224.0f;
    base_y = 184.0f;
    grid = new (0) FieldObject23CEA0;
    grid->func_0023CE80(1, entry_count);
    grid->func_0023CE60(0.0f, 28.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(0, base_x, base_y);
    FieldObject23CEA0* selected_grid = grid;
    selected_grid->index = grid_entries[selected];
    func_0023CB30(selected_grid);
    func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(grid));
    func_00351630(&unk74, grid);
    cursor = new (0) FieldObject23BE00;
    cursor->func_0023BB20(24.0f, 48.0f, 120.0f, 1.0f, grid, 0x288080);
    func_004C6190(unk10, cursor);
    func_003515A0(&unk8c, cursor);
    indicator = new (0) ItemCreationClass172600;
    func_0041AD10(indicator, base_x, base_y, 144.0f, 24.0f);
    func_004C6190(unk10, indicator);
    s32 selected_entry = grid_entries[selected];
    s32 index = 0;
    FieldListNode* node = unk44.unk00->unk04;
    if (node != 0)
    {
        do
        {
            LibObject175140* icon = static_cast<LibObject175140*>(node->unk00);
            if (index == selected_entry)
            {
                icon->set_color(0x288080);
                func_0023B9B0(cursor, selected_entry, func_00467950(icon)->unk08);
            }
            else
            {
                icon->set_color(0x808080);
            }
            node = node->unk04;
            index++;
        } while (node != 0);
    }
    if (icon_display(this, grid_entries[selected]) != 0)
    {
        position_icon_indicator(this);
    }
    return 1;
}

/** @brief Destroy the icon-grid window's base. */
TacticsWindow18B120::~TacticsWindow18B120()
{
}

/**
 * @brief Restore the icon child grid and highlight, then activate that child.
 * @return One after activating the resource icon child.
 */
s32 TacticsWindow18B220::func_slotb8()
{
    ItemCreationClass174C40* widget = resource_widget;
    if (widget != 0)
    {
        widget->unkd0 = 0x32;
        widget->unk3c = 1;
    }
    FieldObject23CEA0* parent_grid = grid;
    if (parent_grid != 0)
    {
        parent_grid->FieldClass151C50::unk30 = 64.0f;
        parent_grid->unkae = 1;
    }
    TacticsWindow18B120* child = static_cast<TacticsWindow18B120*>(func_slot4c());
    FieldObject23CEA0* selected_grid = child->grid;
    if (selected_grid != 0)
    {
        selected_grid->index = child->grid_entries[child->selected];
        func_0023CB30(selected_grid);
        func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(child->grid));
        child->grid->unkad = 1;
    }
    s32 selected_entry = child->grid_entries[child->selected];
    s32 index = 0;
    FieldListNode* node = child->unk44.unk00->unk04;
    if (node != 0)
    {
        do
        {
            LibObject175140* icon = static_cast<LibObject175140*>(node->unk00);
            if (index == selected_entry)
            {
                icon->set_color(0x288080);
                func_0023B9B0(child->cursor, selected_entry, func_00467950(icon)->unk08);
            }
            else
            {
                icon->set_color(0x808080);
            }
            node = node->unk04;
            index++;
        } while (node != 0);
    }
    child->func_slot20(1);
    D_001B643C->callbacks->state->func_00263C70(child);
    return 1;
}

u32 func_003499A0(void* object)
{
    return *(u32*)((u8*)object + 0x9C);
}

/**
 * @brief Open the selection child for an enabled grid, or update the control-mode flags.
 * @return Two after the action, or zero for a disabled grid or an absent runtime or child.
 */
s32 TacticsWindow18B220::func_slotb4()
{
    if (tactics_grid_empty(grid) == 1)
    {
        return 0;
    }
    FieldClass153E00* runtime = D_001B643C->runtime;
    if (!runtime)
    {
        return 0;
    }
    u8 control_mode = runtime->unk2d != 0;
    if (control_mode == 1)
    {
        func_slot1c(1, 0x80);
    }
    else
    {
        TacticsWindow18B020* child = new (0) TacticsWindow18B020;
        if (!child)
        {
            return 0;
        }
        child->func_slotf4(func_slot54(), 175.0f, 160.0f, 5, 0x29CF);
        child->func_slot40(this);
        D_001B643C->callbacks->state->func_00263FD0(child);
        D_001B643C->callbacks->state->func_00263C70(child);
    }
    return 2;
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

ItemCreationClass175110::~ItemCreationClass175110()
{
}

/** @brief Destroy the parent window base. */
TacticsWindow18B220::~TacticsWindow18B220()
{
}

/** @brief Clear the displays and restore the resident grid selection. */
TacticsWindow18B220::TacticsWindow18B220()
{
    title = 0;
    grid = 0;
    cursor = 0;
    indicator = 0;
    resource_widget = 0;
    resource = 0;
    options[0] = 0;
    options[1] = 0;
    options[2] = 0;
    func_0013A678(entries, 0, 3);
    selected = D_001B643C->state->selected;
    base_x = 0.0f;
    base_y = 0.0f;
    label = 0;
}

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

/**
 * @brief Return to the first selector, update control-mode flags, or open its child window.
 * @return Two after the action, or zero when the runtime or child allocation is absent.
 */
s32 TacticsWindow18B320::func_slotb4()
{
    if (use_second == 1)
    {
        LibClass175030* second_target = reinterpret_cast<LibClass175030*>(second);
        second_target->unk10 = -128.0f;
        second_target->unk14 = -128.0f;
        second_target->unk35 = 1;
        second_target->unk3c = 1;
        reinterpret_cast<LibClass175030*>(second)->unk3f = 0;
        LibClass175030* first_target = reinterpret_cast<LibClass175030*>(first);
        first_target->unk30 = 128.0f;
        first_target->unk3c = 1;
        use_second = 0;
        unkc2 = -1;
        unkc4 = -1;
        return 2;
    }
    FieldClass153E00* runtime = D_001B643C->runtime;
    if (!runtime)
    {
        return 0;
    }
    u8 control_mode = runtime->unk2d != 0;
    if (control_mode == 1)
    {
        func_slot1c(1, 0x80);
    }
    else
    {
        TacticsWindow18B020* child = new (0) TacticsWindow18B020;
        if (!child)
        {
            return 0;
        }
        child->func_slotf4(func_slot54(), 175.0f, 160.0f, 5, 0x29CE);
        child->func_slot40(this);
        LibClass175030* first_target = reinterpret_cast<LibClass175030*>(first);
        first_target->unk30 = 64.0f;
        first_target->unk3c = 1;
        D_001B643C->callbacks->state->func_00263FD0(child);
        D_001B643C->callbacks->state->func_00263C70(child);
    }
    return 2;
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034B390);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034BA40);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034C120);

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", func_0034D900);

/** @brief Release the receiver's owned storage. */
TacticsStorage18B010::~TacticsStorage18B010()
{
}

INCLUDE_ASM("build/overlays/ctactics/asm/nonmatchings/text", __dt__19TacticsWindow18B320Fv);

/** @brief Construct the owned lists and clear the window control fields. */
TacticsWindow18B320::TacticsWindow18B320()
{
    unka8 = 0;
    unkac = 0;
    bufferc4 = 0;
    buffer114 = 0;
    second = 0;
    first = 0;
    use_second = 0;
    unkc2 = -1;
    unkc4 = -1;
    unkc1 = 0;
    unk14c[0] = 0;
    unk14c[1] = 0;
    unk14c[2] = 0;
    unk14c[3] = 0;
    unk14c[4] = 0;
    unk14c[5] = 0;
    unk14c[6] = 0;
    unk14c[7] = 0;
}

/** @brief Refresh the associated text when the active grid selection changes. */
void TacticsWindow18B420::func_slot5c()
{
    if (D_001B643C->callbacks->state->func_00261150() != this)
    {
        return;
    }
    s16 index = grid->unk114;
    if (index == selected)
    {
        return;
    }
    if (unkf4 == 2 || unkf4 == 9)
    {
        static_cast<FieldClass15AE70*>(D_001B643C->callbacks->state->func_00263C90())->func_slot60(index + 0x29D7);
    }
    else
    {
        static_cast<FieldClass15AE70*>(D_001B643C->callbacks->state->func_00263C90())->func_slot60(index + 0x29D1);
    }
    selected = index;
}

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

/**
 * @brief Close the grid window, restore its parent, and reset the associated text.
 * @return Two after closing.
 */
s32 TacticsWindow18B420::func_slotb4()
{
    cursor->unk3f = 0;
    unkd4->unk3f = 0;
    FieldClass15AE70::func_slot18(0, 0x7F);
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot64();
    FieldClass153E30* state = D_001B643C->callbacks->state;
    state->func_00263C70(func_slot44());
    static_cast<FieldClass15AE70*>(D_001B643C->callbacks->state->func_00263C90())->func_slot60(0x2714);
    return 2;
}

/**
 * @brief Save the selected grid entry, update its parent display, and restore the parent window.
 * @return One after the selected entry is applied.
 */
s32 TacticsWindow18B420::func_slotb0()
{
    TacticsWindow18B520* parent = static_cast<TacticsWindow18B520*>(func_slot44());
    static_cast<TacticsEntryResourceRecord*>(parent->unkac)[parent->selected].selected_entry = grid->unk114;
    LibObject178750* display = static_cast<LibObject178750*>(func_00351BF0(
        reinterpret_cast<TacticsList*>(&parent->unk2c), parent->selected)->value);
    TacticsGridResourceRecord* records = static_cast<TacticsGridResourceRecord*>(parent->unka8);
    s16 record_index = parent->selected;
    s16 kind;
    if (records)
    {
        kind = records[record_index].kind;
    }
    else
    {
        kind = 0;
    }
    u32 key = parent->get_record_text_key(kind, record_index);
    func_4C6DF0(display, parent->func_slot54(), key, 0);
    cursor->unk3f = 0;
    unkd4->unk3f = 0;
    FieldClass15AE70::func_slot18(0, 0x7F);
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot64();
    FieldClass153E30* state = D_001B643C->callbacks->state;
    state->func_00263C70(func_slot44());
    static_cast<FieldClass15AE70*>(D_001B643C->callbacks->state->func_00263C90())->func_slot60(0x2714);
    return 1;
}

/**
 * @brief Configure the grid resource keys and highlight its initial entry.
 * @param record_index Signed record index in the resident record table.
 * @param initial_entry Initial grid entry.
 * @return Marker position status.
 */
s32 TacticsWindow18B420::set_grid_record(s16 record_index, u8 initial_entry)
{
    clear_grid_state(this);
    unkf4 = static_cast<TacticsGridResourceRecord*>(unka8)[record_index].kind;
    unkf6 = initial_entry;
    s32 first_key;
    switch (unkf4)
    {
        case 1:
            first_key = 0x2968;
            break;
        case 2:
            first_key = 0x296E;
            break;
        case 3:
            first_key = 0x2968;
            break;
        case 4:
            first_key = 0x2968;
            break;
        case 5:
            first_key = 0x2968;
            break;
        case 6:
            first_key = 0x2968;
            break;
        case 7:
            first_key = 0x2968;
            break;
        case 8:
            first_key = 0x2968;
            break;
        case 9:
            first_key = 0x296E;
            break;
        case 10:
            first_key = 0x2968;
            break;
        default:
            first_key = 0x29CC;
            break;
    }
    if (first_key == 0x29CC)
    {
        keys[0] = 0x29CC;
        keys[1] = 0x29CC;
        keys[2] = 0x29CC;
        keys[3] = 0x29CC;
        keys[4] = 0x29CC;
        keys[5] = 0x29CC;
    }
    else
    {
        for (s32 index = 0; index < 6; index++)
        {
            keys[index] = first_key + index;
            LibObject178750* display = grid_display(this, index);
            func_4C6DF0(display, func_slot54(), keys[index], 0);
        }
    }
    for (s32 index = 0; index < 6; index++)
    {
        LibObject178750* display = grid_display(this, index);
        display->unk94 = 0x808080;
        display->unk3c = 1;
    }
    LibUiRect16* rectangle = &grid_display(this, unkf6)->unk18;
    LibBounds4C69B0* bounds = func_004C69B0(grid_display(this, unkf6));
    FieldObject23CEA0* selection = grid;
    selection->index = unkf6;
    func_0023CB30(selection);
    func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(grid));
    set_widget_rectangle(unkd4, rectangle->unk00, rectangle->unk04,
        bounds->unk08, bounds->unk0c);
    LibObject178750* selected = grid_display(this, unkf6);
    selected->unk94 = 0x288080;
    selected->unk3c = 1;
    return func_0023B9B0(cursor, unkf6, bounds->unk08);
}

/**
 * @brief Create the grid window's text, panels, selector, and indicators.
 * @param associated Full resource source word forwarded to the base window and text widgets.
 * @return Zero when required resources or displays are missing; otherwise one.
 */
s32 TacticsWindow18B420::func_slotf4(u32 associated)
{
    unka8 = D_001B643C->records04;
    unkac = D_001B643C->records08;
    if (unka8 == 0 || unkac == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 138.0f, 148.0f, 7);
    LibClass178630* panel = new (0) LibClass178630;
    text[0] = new (0) LibObject178750;
    text[1] = new (0) LibObject178750;
    text[2] = new (0) LibObject178750;
    text[3] = new (0) LibObject178750;
    text[4] = new (0) LibObject178750;
    text[5] = new (0) LibObject178750;
    grid = new (0) FieldObject23CEA0;
    LibClass178630* title_panel = new (0) LibClass178630;
    LibObject178750* title = new (0) LibObject178750;
    unkd4 = new (0) ItemCreationClass172600;
    cursor = new (0) FieldObject23BE00;
    if (panel == 0 || text[0] == 0 || text[1] == 0 || text[2] == 0 ||
        text[3] == 0 || text[4] == 0 || text[5] == 0 || grid == 0)
    {
        return 0;
    }
    LibWidgetColors4C5590 colors = D_00352000;
    func_004C5A80(panel, 1, 0.0f, 0.0f, 364.0f, 256.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_00351CC0(&unk14, panel);
    func_004C5A80(title_panel, 1, 0.0f, 0.0f, 364.0f, 48.0f, 88.0f);
    func_4C5590(title_panel, &colors);
    func_004C6190(unk10, title_panel);
    func_00351CC0(&unk14, title_panel);
    clear_grid_state(this);
    keys[0] = 0x29CC;
    keys[1] = 0x29CC;
    keys[2] = 0x29CC;
    keys[3] = 0x29CC;
    keys[4] = 0x29CC;
    keys[5] = 0x29CC;
    func_004C7FE0(text[0], associated, keys[0], 0, 28.0f, 60.0f, 0.0f, 0.0f);
    func_004C7FE0(text[1], associated, keys[1], 0, 28.0f, 90.0f, 0.0f, 0.0f);
    func_004C7FE0(text[2], associated, keys[2], 0, 28.0f, 120.0f, 0.0f, 0.0f);
    func_004C7FE0(text[3], associated, keys[3], 0, 28.0f, 150.0f, 0.0f, 0.0f);
    func_004C7FE0(text[4], associated, keys[4], 0, 28.0f, 180.0f, 0.0f, 0.0f);
    func_004C7FE0(text[5], associated, keys[5], 0, 28.0f, 210.0f, 0.0f, 0.0f);
    func_004C6190(unk10, text[0]);
    func_004C6190(unk10, text[1]);
    func_004C6190(unk10, text[2]);
    func_004C6190(unk10, text[3]);
    func_004C6190(unk10, text[4]);
    func_004C6190(unk10, text[5]);
    func_00351AE0(&unk2c, text[0]);
    func_00351AE0(&unk2c, text[1]);
    func_00351AE0(&unk2c, text[2]);
    func_00351AE0(&unk2c, text[3]);
    func_00351AE0(&unk2c, text[4]);
    func_00351AE0(&unk2c, text[5]);
    func_004C7FE0(title, associated, 0x2723, 1, 0.0f, 12.0f, 364.0f, 48.0f);
    title->unk9c = 1;
    title->unk3c = 1;
    func_004C6190(unk10, title);
    func_00351AE0(&unk2c, title);
    LibBounds4C69B0* bounds = func_004C69B0(text[0]);
    func_0041AD10(unkd4, bounds->unk00, bounds->unk04, bounds->unk08, 24.0f);
    func_004C6190(unk10, unkd4);
    grid->func_0023CE80(1, 6);
    grid->func_0023CE60(0.0f, 30.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(0, 166.0f, 208.0f);
    FieldObject23CEA0* selection = grid;
    selection->index = unkf6;
    func_0023CB30(selection);
    func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(grid));
    func_00351630(&unk74, grid);
    cursor->func_0023BB20(28.0f, 60.0f, 192.0f, 1.0f, grid, 0x288080);
    func_004C6190(unk10, cursor);
    cursor->unk3f = 0;
    unkd4->unk3f = 0;
    FieldClass15AE70::func_slot18(0, 0x7F);
    return 1;
}

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

/**
 * @brief Open a child window, or update the window flags for the resident control mode.
 * @return Two after the action, or zero when the runtime or child allocation is absent.
 */
s32 TacticsWindow18B520::func_slotb4()
{
    FieldClass153E00* runtime = D_001B643C->runtime;
    if (!runtime)
    {
        return 0;
    }
    u8 control_mode = runtime->unk2d != 0;
    if (control_mode == 1)
    {
        func_slot1c(1, 0x80);
    }
    else
    {
        TacticsWindow18B020* child = new (0) TacticsWindow18B020;
        if (!child)
        {
            return 0;
        }
        child->func_slotf4(func_slot54(), 175.0f, 160.0f, 5, 0x29CD);
        child->func_slot40(this);
        D_001B643C->callbacks->state->func_00263FD0(child);
        D_001B643C->callbacks->state->func_00263C70(child);
    }
    return 2;
}

/**
 * @brief Open the grid window for the selected enabled record and remember its current entry.
 * @return One after opening the grid window, or three for a disabled record.
 */
s32 TacticsWindow18B520::func_slotb0()
{
    selected = selection->selected;
    if (enabled[selected])
    {
        TacticsEntryResourceRecord* record = &static_cast<TacticsEntryResourceRecord*>(unkac)[selected];
        u8 initial_entry = record->selected_entry;
        record->previous_entry = initial_entry;
        if (selected == 3 || selected == 4)
        {
            reinterpret_cast<LibClass175030*>(selection)->unk3f = 0;
        }
        else
        {
            LibClass175030* target = reinterpret_cast<LibClass175030*>(selection);
            target->unk30 = 64.0f;
            target->unk3c = 1;
        }
        TacticsWindow18B420* child = static_cast<TacticsWindow18B420*>(func_slot44());
        child->set_grid_record(selected, initial_entry);
        child->cursor->unk3f = 1;
        child->unkd4->unk3f = 1;
        child->FieldClass15AE70::func_slot18(1, 0x7F);
        FieldClass153E30* state = D_001B643C->callbacks->state;
        state->func_00263C70(func_slot44());
    }
    else
    {
        return 3;
    }
    return 1;
}

/**
 * @brief Find the text key for a resource record's saved grid entry.
 * @param kind Signed record kind selecting the key range.
 * @param record_index Record index in the resident entry table.
 * @return Text key for the record's saved entry.
 */
u32 TacticsWindow18B520::get_record_text_key(s16 kind, s32 record_index)
{
    u32 first_key;
    switch (kind)
    {
        case 1:
            first_key = 0x2968;
            break;
        case 2:
            first_key = 0x296E;
            break;
        case 3:
            first_key = 0x2968;
            break;
        case 4:
            first_key = 0x2968;
            break;
        case 5:
            first_key = 0x2968;
            break;
        case 6:
            first_key = 0x2968;
            break;
        case 7:
            first_key = 0x2968;
            break;
        case 8:
            first_key = 0x2968;
            break;
        case 9:
            first_key = 0x296E;
            break;
        case 10:
            first_key = 0x2968;
            break;
        default:
            first_key = 0x29CC;
            break;
    }
    return first_key + static_cast<TacticsEntryResourceRecord*>(unkac)[record_index].selected_entry;
}

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
    if (resource_slot != 0)
    {
        func_00465430(D_001B657C, resource_slot);
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
    resource_slot = func_004656B0(D_001B657C, aligned);
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

/** @brief Clear the resource slot, window initialization flag, and selection pointer. */
TacticsState18B820::TacticsState18B820()
{
    resource_slot = 0;
    windows_initialized = 0;
    selection = 0;
}

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
