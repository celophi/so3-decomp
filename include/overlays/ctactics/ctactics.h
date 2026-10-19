#ifndef SO3_OVERLAYS_CTACTICS_CTACTICS_H
#define SO3_OVERLAYS_CTACTICS_CTACTICS_H

#include "types.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/lib/text_0045AD10.h"
struct FieldRecordSelection;
struct LibObject178750;
#endif

typedef struct FieldCountedList FieldCountedList;
typedef struct FieldListNode FieldListNode;

/** Opaque resource-label window with its resident table at 0x18B220. */
typedef struct TacticsWindow18B220 TacticsWindow18B220;

typedef struct TacticsWindow18B520 TacticsWindow18B520;

typedef struct TacticsPresetPosition
{
#ifdef __cplusplus
    /** @brief Initialize both coordinate components to zero. */
    TacticsPresetPosition()
    {
        y = 0.0f;
        x = 0.0f;
    }

    /** @brief Initialize a coordinate pair. @param px Horizontal value. @param py Vertical value. */
    TacticsPresetPosition(float px, float py)
    {
        x = px;
        y = py;
    }
#endif

    float x;

    float y;
} TacticsPresetPosition;

typedef struct TacticsCharacterNameWidgetList TacticsCharacterNameWidgetList;
typedef struct TacticsStatValueWidgetList TacticsStatValueWidgetList;
typedef struct TacticsTextWidgetList TacticsTextWidgetList;
typedef struct TacticsCoordinatePositionList TacticsCoordinatePositionList;

#ifdef __cplusplus
/** Known native State prefix through its owned selection pointer at offset 3C. */
struct TacticsResourceMenuState : public FieldClass153E30
{
    /** @brief Clear the resource slot, window initialization flag, and selection pointer. */
    TacticsResourceMenuState();

    /** @brief Release the owned record selection and destroy the State base. */
    virtual ~TacticsResourceMenuState();

    /** @brief Report this object's default list kind. @return Four. */
    virtual s32 get_default_list_kind();

    /** @brief Submit the State to the resident object queue. */
    virtual void func_001DD7B0();

    /** @brief Return the loaded resource slot. @return Resource slot. */
    virtual u32 func_00263CC0();

    /** @brief Report whether window setup finished. @return Setup flag. */
    virtual u8 func_00261D20();

    /**
     * @brief Allocate and initialize the State's record selection.
     * @return One when a selection exists and initialization succeeds; otherwise zero.
     */
    virtual u8 func_00264110();

    /**
     * @brief Load the completed aligned resource using the State's heap context.
     * @param buffer Completed resource buffer, or null to report failure.
     * @return Zero for a null buffer; otherwise the window initialization result.
     */
    virtual s32 func_001E1820(void* buffer);

    /** @brief Release the loaded resource, detach the State, and dispatch its release handler. */
    virtual void func_slot5c();

    /**
     * @brief Initialize the State's windows and their resource-mode associations.
     * @return One after setup, or zero when a required window allocation fails.
     */
    virtual s32 func_00263CD0();

    s32 resource_slot;

    u8 windows_initialized : 1;

    u8 unk38_1_7 : 7;

    u8 unk39[3];

    FieldRecordSelection* selection;
};

/** Known native window interface used to initialize its resource displays. */
struct TacticsWindow18B720 : public FieldClass15AE70
{
    /** @brief Destroy the resource window. */
    virtual ~TacticsWindow18B720();

    /**
     * @brief Initialize the resource window and attach its three displays.
     * @param associated Resource source word forwarded to the base initializer.
     * @return One after the displays are attached.
     */
    virtual s32 func_slotf4(u32 associated);
};

/** Native 0xC4-byte scrolling window with its text widget and movement bounds. */
struct TacticsWindow18B620 : public FieldClass15AE70
{
    /** @brief Clear the scrolling text state and movement bounds. */
    TacticsWindow18B620()
    {
        text = 0;
        scroll_span = 0;
        scroll_phase = 0;
        initial_pause_frames = 0;
        label_right_edge = 0.0f;
        initial_text_x = 0.0f;
        clip_x = 0.0f;
        clip_width = 0.0f;
    }

    /** @brief Destroy the scrolling window. */
    virtual ~TacticsWindow18B620();

    /** @brief Hold the text position, then scroll and wrap it after the timer expires. */
    virtual void func_slot5c();

    /**
     * @brief Replace the text for supported keys and reset its scrolling state.
     * @param text_key Text key in the supported 0x2714..0x271B range.
     */
    virtual void func_slot60(s32 text_key);

    /**
     * @brief Initialize the scrolling window and its text displays.
     * @param associated Resource source word forwarded to the base and text displays.
     * @return One after initialization succeeds; otherwise zero.
     */
    virtual s32 func_slotf4(u32 associated);

    LibObject178750* text;

    s32 scroll_span;

    s16 initial_pause_frames;

    u8 scroll_phase;

    float label_right_edge;

    float initial_text_x;

    float clip_x;

    float clip_width;
};

/** Native 0xB0-byte tactics child window containing a grid and its saved selection. */
struct TacticsWindow18B020 : public FieldClass15AE70
{
    /** @brief Clear the grid pointer and saved selection. */
    TacticsWindow18B020()
    {
        grid = 0;
        selected = -1;
    }

    /** @brief Destroy the child window's base. */
    virtual ~TacticsWindow18B020();

    /** @brief Compare the State's active window with this window; neither outcome has further work. */
    virtual void func_slot5c();

    /** @brief Move to the preceding grid entry and update its text highlight. */
    virtual void func_slot68();

    /** @brief Move to the following grid entry and update its text highlight. */
    virtual void func_slot6c();

    /**
     * @brief Apply the first grid entry or close the child, refreshing pending field state.
     * @return Two when closing succeeds; otherwise one.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Close the child window and restore the associated window's movement.
     * @return Two after restoring the associated window and queuing removal.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Create the child window's two-entry grid, panels, and text displays.
     * @param associated Full resource source word forwarded to the base and displays.
     * @param x Horizontal window position.
     * @param y Vertical window position.
     * @param code Base window initializer code.
     * @param text_key Text key for the heading display.
     * @return One after initialization, or zero when a required display or grid is absent.
     */
    virtual s32 func_slotf4(u32 associated, float x, float y, s32 code, s32 text_key);

    /**
     * @brief Highlight the text display for the selected grid entry.
     * @param selected Entry to highlight.
     */
    virtual void func_slotf8(s16 selected);

    struct FieldObject23CEA0* grid;

    s16 selected;

    u8 unkae[2];
};

/** Native 0xD4-byte tactics window with three character IDs and an icon grid. */
struct TacticsWindow18B120 : public FieldClass15AE70
{
    /** @brief Clear the record selection, saved character IDs, and grid origin. */
    TacticsWindow18B120()
    {
        record_selection = 0;
        grid = 0;
        cursor = 0;
        indicator = 0;
        icon_count = 0;
        base_x = 0.0f;
        base_y = 0.0f;
        selected = 0;
        func_0013A678(character_ids, 0, sizeof(character_ids));
        icon_indices_by_slot[0] = 0;
        icon_indices_by_slot[1] = 0;
        icon_indices_by_slot[2] = 0;
    }

    /** @brief Destroy the icon-grid window's base. */
    virtual ~TacticsWindow18B120();

    /** @brief Move to the preceding grid entry and update the icon highlight. */
    virtual void func_slot68();

    /** @brief Move to the following grid entry and update the icon highlight. */
    virtual void func_slot6c();

    /**
     * @brief Save the chosen character ID and update the parent label.
     * @return One after the selected character ID is applied.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Restore the saved grid entry, refresh its icon, and return to the associated window.
     * @return Two after restoring the associated window.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Initialize the resource icons, grid, marker, and indicator.
     * @param associated Full resource source word forwarded to the base and title.
     * @return Zero when a panel allocation or resource link fails; otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    FieldRecordSelection* record_selection;

    struct FieldObject23CEA0* grid;

    struct FieldObject23BE00* cursor;

    struct ItemCreationClass172600* indicator;

    s16 selected;

    u8 icon_count;

    u8 character_ids[3];

    u8 unkbe[2];

    float base_x;

    float base_y;

    s32 icon_indices_by_slot[3];
};

/** Native 0xDC-byte parent window containing a grid, character IDs, and their label. */
struct TacticsWindow18B220 : public FieldClass15AE70
{
    /** @brief Clear the displays and restore the resident grid selection. */
    TacticsWindow18B220();

    /** @brief Destroy the parent window base. */
    virtual ~TacticsWindow18B220();

    /** @brief Restore the grid and resource widget movement flags. */
    virtual void func_slot64();

    /** @brief Move to the preceding grid entry and update its title, cursor, and indicators. */
    virtual void func_slot68();

    /** @brief Move to the following grid entry and update its title, cursor, and indicators. */
    virtual void func_slot6c();

    /**
     * @brief Save the enabled grid selection and fit the indicator to its text.
     * @return Zero when the grid's control byte is clear; otherwise one.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Open the selection child for an enabled grid, or update the control-mode flags.
     * @return Two after the action, or zero for a disabled grid or an absent runtime or child.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Restore the icon child grid and highlight, then activate that child.
     * @return One after activating the resource icon child.
     */
    virtual u8 func_slotb8();

    /**
     * @brief Create the parent window's grid, resource widgets, and selected-entry label.
     * @param associated Full resource source word forwarded to the base and text widgets.
     * @return One after initialization, or zero when the resource selection or a panel is absent.
     */
    virtual s32 func_slotf4(u32 associated);

    LibObject178750* title;

    struct ItemCreationClass172600* indicator;

    class ItemCreationClass174C40* resource_widget;

    struct FieldObject23CEA0* grid;

    struct FieldObject23BE00* cursor;

    FieldRecordSelection* record_selection;

    struct ItemCreationOptionResourceDisplay* character_displays[3];

    u8 character_ids[3];

    u8 selected;

    float base_x;

    float base_y;

    LibObject175140* label;
};

/** Native 0xC8-byte tactics window containing the coordinate selector. */
struct TacticsWindow18B520 : public FieldClass15AE70
{
    /** @brief Clear the resource links, coordinate selection, and preset position. */
    TacticsWindow18B520()
    {
        character_records = 0;
        entry_records = 0;
        selection = 0;
        selected = -1;
        func_0013A678(record_enabled, 0, sizeof(record_enabled));
        preset_position.x = 0.0f;
        preset_position.y = 0.0f;
    }

    /** @brief Destroy the coordinate-selection window. */
    virtual ~TacticsWindow18B520();

    /** @brief Restore the selector movement or visibility state. */
    virtual void func_slot64();

    /** @brief Move to the preceding coordinate, wrapping before the first. */
    virtual void func_slot68();

    /** @brief Move to the following coordinate, wrapping after the eighth. */
    virtual void func_slot6c();

    /** @brief Map the last five coordinate entries to the first three. */
    virtual void func_slot70();

    /** @brief Map the first three coordinate entries to entries three, five, and six. */
    virtual void func_slot74();

    /**
     * @brief Open the grid window for the selected enabled record and remember its current entry.
     * @return One after opening the grid window, or three for a disabled record.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Open a child window, or update the window flags for the resident control mode.
     * @return Two after the action, or zero when the runtime or child allocation is absent.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Initialize the coordinate selector, row displays, and resource bindings.
     * @param associated Resource source word forwarded to the base and text displays.
     * @return One on success, or zero when records or required displays are absent.
     */
    virtual s32 func_slotf4(u32 associated);

    /**
     * @brief Find the text key for a resource record's saved grid entry.
     * @param character_id Signed character ID selecting the key range.
     * @param record_index Record index in the resident entry table.
     * @return Text key for the record's saved entry.
     */
    u32 get_record_text_key(s16 character_id, s32 record_index);

    struct TacticsGridResourceRecord* character_records;

    struct TacticsEntryResourceRecord* entry_records;

    struct TacticsCoordinateSelector18AFD0* selection;

    s16 selected;

    u8 record_enabled[8];

    u8 unkbe[2];

    TacticsPresetPosition preset_position;
};

/** Native 0xF8-byte tactics grid window with its text displays and cursor. */
struct TacticsWindow18B420 : public FieldClass15AE70
{
    /** @brief Initialize the grid window's pointers and control fields. */
    TacticsWindow18B420();

    /** @brief Destroy the grid window. */
    virtual ~TacticsWindow18B420();

    /** @brief Refresh the associated text when the active grid selection changes. */
    virtual void func_slot5c();

    /** @brief Move to the preceding grid entry and refresh its highlight. */
    virtual void func_slot68();

    /** @brief Move to the following grid entry and refresh its highlight. */
    virtual void func_slot6c();

    /**
     * @brief Save the selected grid entry, update its parent display, and restore the parent window.
     * @return One after the selected entry is applied.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Close the grid window, restore its parent, and reset the associated text.
     * @return Two after closing.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Create the grid window's text, panels, selector, and indicators.
     * @param associated Full resource source word forwarded to the base window and text widgets.
     * @return Zero when required resources or displays are missing; otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    /**
     * @brief Configure the grid resource keys and highlight its initial entry.
     * @param record_index Signed record index in the resident record table.
     * @param initial_entry Initial grid entry.
     * @return Marker position status.
     */
    s32 set_grid_record(s16 record_index, u8 initial_entry);

    struct TacticsGridResourceRecord* character_records;

    struct TacticsEntryResourceRecord* entry_records;

    struct FieldObject23CEA0* grid;

    s16 selected;

    u8 unkb6[2];

    LibObject178750* text[6];

    u8 unkd0[4];

    struct ItemCreationClass172600* selection_indicator;

    struct FieldObject23BE00* cursor;

    s32 keys[6];

    s16 character_id;

    u8 selected_entry;
};

/** Linked list with an empty head node, owned value nodes, and a count. */
struct TacticsCharacterNameWidgetList : public FieldCountedList
{
    /** @brief Create the head node and start with an empty list. */
    TacticsCharacterNameWidgetList();

    /** @brief Delete the value nodes and the head node. */
    virtual ~TacticsCharacterNameWidgetList();
};

/** Linked list with an empty head node, owned value nodes, and a count. */
struct TacticsStatValueWidgetList : public FieldCountedList
{
    /** @brief Create the head node and start with an empty list. */
    TacticsStatValueWidgetList();

    /** @brief Release the stat-value nodes and the head node. */
    virtual ~TacticsStatValueWidgetList();
};

/** Linked list with an empty head node, owned value nodes, and a count. */
struct TacticsTextWidgetList : public FieldCountedList
{
    /** @brief Create the head node and start with an empty list. */
    TacticsTextWidgetList();

    /** @brief Release the text-widget nodes and the head node. */
    virtual ~TacticsTextWidgetList();
};

/** Linked list with an empty head node, owned value nodes, and a count. */
struct TacticsCoordinatePositionList
{
    struct TacticsCoordinateNode* head;

    u32 count;

    /** @brief Create the head node and start with an empty list. */
    TacticsCoordinatePositionList();

    /** @brief Release the coordinate nodes and the head node. */
    virtual ~TacticsCoordinatePositionList();
};

/** Native 0x17C-byte tactics window owning two binary buffers and eleven lists. */
struct TacticsWindow18B320 : public FieldClass15AE70
{
    /** @brief Construct the owned lists and clear the window control fields. */
    TacticsWindow18B320();

    /** @brief Release both binary buffers, then destroy the lists and base window. */
    virtual ~TacticsWindow18B320();

    /** @brief Refresh the eight resource rows after a record change while this window is active. */
    virtual void func_slot5c();

    /**
     * @brief Move the chosen selector back one entry, wrapping to its eighth entry.
     */
    virtual void func_slot68();

    /**
     * @brief Advance the chosen selector one entry, wrapping after its eighth entry.
     */
    virtual void func_slot6c();

    /**
     * @brief Map the chosen selector's last five entries back to its first three.
     */
    virtual void func_slot70();

    /** @brief Map the chosen selector's first three entries to entries three, five, and six. */
    virtual void func_slot74();

    /**
     * @brief Confirm a swap between the two selected character slots, or start choosing the second slot.
     * @return One when the selection continues, three when the swap is refused or rolled back.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Return to the first selector, update control-mode flags, or open its child window.
     * @return Two after the action, or zero when the runtime or child allocation is absent.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Initialize the paired selectors and their eight resource rows.
     * @param associated Resource source word forwarded to the base and text displays.
     * @return One on success, otherwise zero when records or required displays are absent.
     */
    virtual s32 func_slotf4(u32 associated);

    struct TacticsGridResourceRecord* character_records;

    struct TacticsEntryResourceRecord* entry_records;

    struct TacticsGridResourceRecord* character_record_buffer;

    struct TacticsEntryResourceRecord* entry_record_buffer;

    struct TacticsCoordinateSelector18AFD0* first_selector;

    struct TacticsCoordinateSelector18AFD0* second_selector;

    u8 use_second;

    u8 refresh_pending;

    s16 source_record_index;

    s16 destination_record_index;

    u8 unkc6[2];

    TacticsTextWidgetList level_label_list;

    TacticsStatValueWidgetList level_value_list;

    TacticsTextWidgetList hp_label_list;

    TacticsTextWidgetList mp_label_list;

    TacticsStatValueWidgetList hp_value_list;

    TacticsTextWidgetList hp_separator_text_list;

    TacticsStatValueWidgetList max_hp_value_list;

    TacticsStatValueWidgetList mp_value_list;

    TacticsTextWidgetList mp_separator_text_list;

    TacticsStatValueWidgetList max_mp_value_list;

    TacticsCharacterNameWidgetList unk140;

    s16 row_character_ids[8];

    struct ItemCreationOptionResourceDisplay* resource_displays[8];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_cursor_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_grid_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_icon_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_stat_value_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_text_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_clip_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param list List to append to.
 * @param value Pointer stored in the node. The caller owns it.
 */
void append_panel_widget_node(FieldCountedList* list, void* value);

/**
 * @brief Copy `value.x` and `value.y` into a new node at the end of the list.
 * @param list List to append to.
 * @param value Coordinate pair to copy.
 */
void append_coordinate_pair(TacticsCoordinatePositionList* list, TacticsPresetPosition value);

/**
 * @brief Delete every node after the head node and set the count to zero.
 * @param list List to clear. The head node stays allocated.
 */
void clear_character_name_widget_list(TacticsCharacterNameWidgetList* list);

/**
 * @brief Delete every node after the head node and set the count to zero.
 * @param list List to clear. The head node stays allocated.
 */
void clear_stat_value_list(TacticsStatValueWidgetList* list);

/**
 * @brief Delete every node after the head node and set the count to zero.
 * @param list List to clear. The head node stays allocated.
 */
void clear_text_widget_list(TacticsTextWidgetList* list);

/**
 * @brief Delete every coordinate node after the head node and set the count to zero.
 * @param list List to clear. The head node stays allocated.
 */
void clear_coordinate_widget_list(TacticsCoordinatePositionList* list);

/**
 * @brief Color up to six list displays and place the cursor for the selected grid entry.
 * @param object Tactics receiver holding the display list, grid, and cursor.
 */
void refresh_grid_list_selection(TacticsWindow18B420* object);

/**
 * @brief Place the present character displays using the selected grid row's coordinate pairs.
 * @param object Parent window holding the grid, character displays, and base coordinates.
 */
void position_grid_indicators(TacticsWindow18B220* object);

/**
 * @brief Select a preset display position, clearing it for an invalid index.
 * @param object Coordinate window holding the position pair.
 * @param index Zero-based preset index.
 * @return The receiver's updated position pair.
 */
TacticsPresetPosition* set_preset_position_from_index(TacticsWindow18B520* object, s32 index);

/**
 * @brief Return the node at `index`. Index zero is the first node after the head node.
 * @param list List to search.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
FieldListNode* get_widget_node_at_index(FieldCountedList* list, s32 index);

/**
 * @brief Return the node at `index`. Index zero is the first node after the head node.
 * @param list List to search.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
FieldListNode* get_stat_value_node(FieldCountedList* list, s32 index);

/**
 * @brief Return the node at `index`. Index zero is the first node after the head node.
 * @param list List to search.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
FieldListNode* get_text_widget_node(FieldCountedList* list, s32 index);

/**
 * @brief Update the parent window's indicators, grid title, highlight, and selection indicator.
 * @param object Parent window to refresh.
 */
void refresh_parent_selection_display(TacticsWindow18B220* object);

/**
 * @brief Select the character ID in the parent and point its label at the matching record's text.
 * @param object Parent window produced by the paired window factory.
 * @param character_id Full character code; zero selects code 1.
 */
void set_parent_character_id(TacticsWindow18B220* object, u32 character_id);

#ifdef __cplusplus
}
#endif

#endif
