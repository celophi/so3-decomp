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
class TacticsFormationWindow;
class TacticsChangeWindow;
class TacticsCharacterNameWidgetList;
class TacticsStatValueWidgetList;
class TacticsTextWidgetList;
class TacticsCoordinatePositionList;
#endif

typedef struct FieldCountedList FieldCountedList;
typedef struct FieldListNode FieldListNode;

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

#ifdef __cplusplus
/** Tactics menu controller: loads the menu resource and builds the windows for the chosen mode. */
class TacticsController : public FieldClass153E30
{
public:
    /** @brief Clear the resource slot, window initialization flag, and selection pointer. */
    TacticsController();

    /** @brief Release the owned record selection and destroy the State base. */
    virtual ~TacticsController();

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

/** Resource window owning three displays of resource 11. */
class TacticsResourceWindow : public FieldClass15AE70
{
public:
    /** @brief Destroy the resource window. */
    virtual ~TacticsResourceWindow();

    /**
     * @brief Initialize the resource window and attach its three displays.
     * @param associated Resource source word forwarded to the base initializer.
     * @return One after the displays are attached.
     */
    virtual s32 func_slotf4(u32 associated);
};

/** 0xC4-byte help bar with the menu title, the mode name, and a scrolling description. */
class TacticsHelpWindow : public FieldClass15AE70
{
public:
    /** @brief Clear the scrolling text state and movement bounds. */
    TacticsHelpWindow()
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
    virtual ~TacticsHelpWindow();

    /** @brief Hold the text position, then scroll and wrap it after the timer expires. */
    virtual void func_slot5c();

    /**
     * @brief Replace the text for supported keys and reset its scrolling state.
     * @param text_key Help line key, from TACTICS_MSG_HELP_FIRST up to TACTICS_MSG_HELP_END.
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

/** 0xB0-byte Yes/No window that asks before leaving the current setup. */
class TacticsExitConfirmWindow : public FieldClass15AE70
{
public:
    /** @brief Clear the grid pointer and saved selection. */
    TacticsExitConfirmWindow()
    {
        grid = 0;
        selected = -1;
    }

    /** @brief Destroy the child window's base. */
    virtual ~TacticsExitConfirmWindow();

    /** @brief Compare the State's active window with this window; neither outcome has further work. */
    virtual void func_slot5c();

    /** @brief Move to the preceding grid entry and update its text highlight. */
    virtual void func_slot68();

    /** @brief Move to the following grid entry and update its text highlight. */
    virtual void func_slot6c();

    /**
     * @brief On Yes, refresh any pending character state and leave the setup; on No, close this window.
     * @return One after Yes; two after No closes the window.
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

/** 0xD4-byte "Set Leader" window listing the party members by name. */
class TacticsLeaderWindow : public FieldClass15AE70
{
public:
    /** @brief Clear the record selection, saved character IDs, and grid origin. */
    TacticsLeaderWindow()
    {
        record_selection = 0;
        grid = 0;
        cursor = 0;
        indicator = 0;
        candidate_count = 0;
        base_x = 0.0f;
        base_y = 0.0f;
        selected = 0;
        func_0013A678(character_ids, 0, sizeof(character_ids));
        candidate_indices_by_slot[0] = 0;
        candidate_indices_by_slot[1] = 0;
        candidate_indices_by_slot[2] = 0;
    }

    /** @brief Destroy the leader window's base. */
    virtual ~TacticsLeaderWindow();

    /** @brief Move to the preceding grid entry and update the name highlight. */
    virtual void func_slot68();

    /** @brief Move to the following grid entry and update the name highlight. */
    virtual void func_slot6c();

    /**
     * @brief Save the chosen character ID and update the parent label.
     * @return One after the selected character ID is applied.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Restore the saved grid entry, refresh its highlight, and return to the associated window.
     * @return Two after restoring the associated window.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Initialize the party names, grid, cursor, and indicator.
     * @param associated Full resource source word forwarded to the base and title.
     * @return Zero when a panel allocation or resource link fails; otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    FieldRecordSelection* record_selection;

    struct FieldObject23CEA0* grid;

    struct FieldObject23BE00* cursor;

    struct ItemCreationClass172600* indicator;

    s16 selected;

    u8 candidate_count;

    u8 character_ids[3];

    u8 unkbe[2];

    float base_x;

    float base_y;

    s32 candidate_indices_by_slot[3];
};

/** 0xDC-byte "Formation" window: ten formations, the party's positions, and the leader's name. */
class TacticsFormationWindow : public FieldClass15AE70
{
public:
    /** @brief Clear the displays and restore the resident grid selection. */
    TacticsFormationWindow();

    /** @brief Destroy the formation window base. */
    virtual ~TacticsFormationWindow();

    /** @brief Restore the grid and resource widget movement flags. */
    virtual void func_slot64();

    /** @brief Move to the preceding formation and update its description, cursor, and character positions. */
    virtual void func_slot68();

    /** @brief Move to the following formation and update its description, cursor, and character positions. */
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
     * @brief Restore the leader window's grid and highlight, then activate it.
     * @return One after activating the leader window.
     */
    virtual u8 func_slotb8();

    /**
     * @brief Create the formation window's grid, character displays, and leader label.
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

/** 0xC8-byte "Change Tactics" window: eight character rows with each one's battle strategy. */
class TacticsChangeWindow : public FieldClass15AE70
{
public:
    /** @brief Clear the resource links, coordinate selection, and preset position. */
    TacticsChangeWindow()
    {
        character_records = 0;
        equipment_records = 0;
        selection = 0;
        selected = -1;
        func_0013A678(record_enabled, 0, sizeof(record_enabled));
        preset_position.x = 0.0f;
        preset_position.y = 0.0f;
    }

    /** @brief Destroy the coordinate-selection window. */
    virtual ~TacticsChangeWindow();

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
     * @brief Return the text key of a character's chosen battle strategy.
     * @param character_id Signed character ID selecting the key range.
     * @param record_index Record index in the resident entry table.
     * @return Text key of the chosen strategy's name.
     */
    u32 get_strategy_text_key(s16 character_id, s32 record_index);

    class TacticsCharacterRecord* character_records;

    struct TacticsCharacterEquipment* equipment_records;

    class TacticsCoordinateSelector* selection;

    s16 selected;

    u8 record_enabled[8];

    u8 unkbe[2];

    TacticsPresetPosition preset_position;
};

/** 0xF8-byte "Tactics Menu" window listing one character's six battle strategies. */
class TacticsStrategyWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the grid window's pointers and control fields. */
    TacticsStrategyWindow();

    /** @brief Destroy the grid window. */
    virtual ~TacticsStrategyWindow();

    /** @brief Refresh the associated text when the active grid selection changes. */
    virtual void func_slot5c();

    /** @brief Move to the preceding grid entry and refresh its highlight. */
    virtual void func_slot68();

    /** @brief Move to the following grid entry and refresh its highlight. */
    virtual void func_slot6c();

    /**
     * @brief Save the chosen strategy, update the character's row, and return to the Change Tactics window.
     * @return One after the selected entry is applied.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Close the grid window, restore its parent, and reset the associated text.
     * @return Two after closing.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Create the strategy window's text, panels, selector, and indicators.
     * @param associated Full resource source word forwarded to the base window and text widgets.
     * @return Zero when required resources or displays are missing; otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    /**
     * @brief Show a character's six strategies and highlight the current one.
     * @param record_index Signed record index in the resident record table.
     * @param initial_entry Strategy to highlight.
     * @return Marker position status.
     */
    s32 set_character(s16 record_index, u8 initial_entry);

    class TacticsCharacterRecord* character_records;

    struct TacticsCharacterEquipment* equipment_records;

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
class TacticsCharacterNameWidgetList : public FieldCountedList
{
public:
    /** @brief Create the head node and start with an empty list. */
    TacticsCharacterNameWidgetList();

    /** @brief Delete the value nodes and the head node. */
    virtual ~TacticsCharacterNameWidgetList();
};

/** Linked list with an empty head node, owned value nodes, and a count. */
class TacticsStatValueWidgetList : public FieldCountedList
{
public:
    /** @brief Create the head node and start with an empty list. */
    TacticsStatValueWidgetList();

    /** @brief Release the stat-value nodes and the head node. */
    virtual ~TacticsStatValueWidgetList();
};

/** Linked list with an empty head node, owned value nodes, and a count. */
class TacticsTextWidgetList : public FieldCountedList
{
public:
    /** @brief Create the head node and start with an empty list. */
    TacticsTextWidgetList();

    /** @brief Release the text-widget nodes and the head node. */
    virtual ~TacticsTextWidgetList();
};

/** Linked list with an empty head node, owned value nodes, and a count. */
class TacticsCoordinatePositionList
{
public:
    class TacticsCoordinateNode* head;

    u32 count;

    /** @brief Create the head node and start with an empty list. */
    TacticsCoordinatePositionList();

    /** @brief Release the coordinate nodes and the head node. */
    virtual ~TacticsCoordinatePositionList();
};

/** 0x17C-byte "Replace" window that swaps two party slots and shows each row's level, HP, and MP. */
class TacticsReplaceWindow : public FieldClass15AE70
{
public:
    /** @brief Construct the owned lists and clear the window control fields. */
    TacticsReplaceWindow();

    /** @brief Release both binary buffers, then destroy the lists and base window. */
    virtual ~TacticsReplaceWindow();

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

    class TacticsCharacterRecord* character_records;

    struct TacticsCharacterEquipment* equipment_records;

    class TacticsCharacterRecord* character_record_buffer;

    struct TacticsCharacterEquipment* equipment_record_buffer;

    class TacticsCoordinateSelector* first_selector;

    class TacticsCoordinateSelector* second_selector;

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
 * @brief Color up to six strategy names and place the cursor on the selected one.
 * @param object Strategy window holding the names, grid, and cursor.
 */
void highlight_strategy(TacticsStrategyWindow* object);

/**
 * @brief Place the party's character displays at the selected formation's positions.
 * @param object Formation window holding the grid, character displays, and base coordinates.
 */
void position_formation_characters(TacticsFormationWindow* object);

/**
 * @brief Select the position of a row's strategy text, clearing it for an invalid row.
 * @param object Change Tactics window holding the position pair.
 * @param index Zero-based row index.
 * @return The receiver's updated position pair.
 */
TacticsPresetPosition* set_strategy_text_position(TacticsChangeWindow* object, s32 index);

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
 * @brief Update the formation window's character positions, description, highlight, and indicator.
 * @param object Formation window to refresh.
 */
void refresh_formation_display(TacticsFormationWindow* object);

/**
 * @brief Select the character ID in the parent and point its label at the matching record's text.
 * @param object Formation window.
 * @param character_id Full character code; zero selects code 1.
 */
void set_leader(TacticsFormationWindow* object, u32 character_id);

#ifdef __cplusplus
}
#endif

#endif
