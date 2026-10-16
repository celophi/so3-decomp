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

/** Opaque resource-label window with its resident table at 0x18B220. */
typedef struct TacticsWindow18B220 TacticsWindow18B220;

typedef struct TacticsGridOwner TacticsGridOwner;
typedef struct TacticsPresetOwner TacticsPresetOwner;
typedef struct TacticsDualSelectionOwner TacticsDualSelectionOwner;

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
/** Native storage receiver with its dispatch pointer after the scalar state. */
class TacticsStorage18B010
{
public:
    LibStorageBlock0C storage;
    u8 unk0c[4];
    float unk10;
    float unk14;
    float unk18;
    float unk1c;
    float unk20;
    float unk24;
    u8 unk28[0x10];

    /** @brief Clear the three movement coordinate pairs. */
    TacticsStorage18B010()
    {
        unk14 = 0.0f;
        unk10 = 0.0f;
        unk1c = 0.0f;
        unk18 = 0.0f;
        unk24 = 0.0f;
        unk20 = 0.0f;
    }

    /** @brief Release the receiver's owned storage. */
    virtual ~TacticsStorage18B010();
    /** @brief Perform no work. */
    virtual void func_slot0c();
};

/** @brief Release the receiver's owned storage. */
inline TacticsStorage18B010::~TacticsStorage18B010()
{
}

/** Known native State prefix through its owned selection pointer at offset 3C. */
struct TacticsResourceMenuState : public FieldClass153E30
{
    /** @brief Clear the resource slot, window initialization flag, and selection pointer. */
    TacticsResourceMenuState();
    /** @brief Destroy the State; its complete virtual tail remains unresolved. */
    virtual ~TacticsResourceMenuState();
    /**
     * @brief Allocate and initialize the State's record selection.
     * @return One when a selection exists and initialization succeeds; otherwise zero.
     */
    virtual u8 initialize_record_selection();
    /**
     * @brief Load the completed aligned resource using the State's heap context.
     * @param buffer Completed resource buffer, or null to report failure.
     * @return Zero for a null buffer; otherwise the virtual completion result.
     */
    virtual s32 load_resource_and_initialize_windows(void* buffer);

    /** @brief Release the loaded resource, detach the State, and dispatch its release handler. */
    virtual void func_slot5c();

    /** @brief Initialize the State's windows for its resource mode. @return One on success, otherwise zero. */
    virtual s32 initialize_mode_windows();

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
     * @brief Initialize the window and attach three resource displays.
     * @param associated Full resource source word.
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
     * @param text_key Text key in the supported 2714..271B range.
     */
    virtual void func_slot60(s32 text_key);

    /**
     * @brief Initialize the scrolling window and its text displays.
     * @param associated Associated context forwarded to the base initializer.
     * @return One after initialization succeeds; otherwise zero.
     */
    virtual s32 func_slotf4(void* associated);

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
    /** @brief Apply the grid action for the selected entry. @return Window action status. */
    virtual u8 func_slotb0();
    /** @brief Close the child and restore its associated window. @return Two after closing. */
    virtual u8 func_slotb4();
    /**
     * @brief Initialize the child window's grid and text displays.
     * @param associated Full resource source word.
     * @param x Horizontal position.
     * @param y Vertical position.
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
    /** @brief Destroy the window base. */
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
    /** @brief Restore the associated window. @return Window action status. */
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
    /** @brief Clear the display pointers and restore the resident grid selection. */
    TacticsWindow18B220();
    /** @brief Destroy the parent window base. */
    virtual ~TacticsWindow18B220();
    /** @brief Restore the grid and resource widget movement flags. */
    virtual void func_slot64();
    /** @brief Move to the preceding grid entry and update its title, cursor, and indicators. */
    virtual void func_slot68();
    /** @brief Move to the following grid entry and update its title, cursor, and indicators. */
    virtual void func_slot6c();
    /** @brief Save the enabled grid selection. @return Window action status. */
    virtual u8 func_slotb0();
    /**
     * @brief Open the selection child for an enabled grid, or update control-mode flags.
     * @return Two after the action, or zero for a disabled grid or an absent runtime or child.
     */
    virtual u8 func_slotb4();
    /** @brief Restore and activate the resource icon child. @return One after activation. */
    virtual u8 func_slotb8();
    /**
     * @brief Initialize the grid and resource displays.
     * @param associated Full resource source word forwarded to the base and title.
     * @return Window initialization status.
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
    /** @brief Restore the selection movement or visibility state. */
    virtual void func_slot64();
    /** @brief Move to the preceding coordinate, wrapping after the first. */
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

    void* character_records;
    void* entry_records;
    struct FieldObject23B1D0* selection;
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
    /** @brief Refresh the associated text when the grid selection changes. */
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
    /** @brief Close the grid window. @return Window action status. */
    virtual u8 func_slotb4();
    /**
     * @brief Initialize the grid and its resource displays.
     * @param associated Full resource source word.
     * @return One on success; otherwise zero.
     */
    virtual s32 func_slotf4(u32 associated);

    /**
     * @brief Set the grid resource record and highlight its initial entry.
     * @param record_index Signed resident record index.
     * @param initial_entry Initial grid entry.
     * @return Marker position status.
     */
    s32 set_grid_record(s16 record_index, u8 initial_entry);

    void* character_records;
    void* entry_records;
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
struct TacticsCharacterNameWidgetList
{
    struct TacticsListNode* head;
    u32 count;
    /** @brief Create the head node and start with an empty list. */
    TacticsCharacterNameWidgetList();
    /** @brief Release the value nodes and the head node. */
    virtual ~TacticsCharacterNameWidgetList();
};
/** Linked list with an empty head node, owned value nodes, and a count. */
struct TacticsStatValueWidgetList
{
    struct TacticsListNode* head;
    u32 count;
    /** @brief Create the head node and start with an empty list. */
    TacticsStatValueWidgetList();
    /** @brief Release the value nodes and the head node. */
    virtual ~TacticsStatValueWidgetList();
};
/** Linked list with an empty head node, owned value nodes, and a count. */
struct TacticsTextWidgetList
{
    struct TacticsListNode* head;
    u32 count;
    /** @brief Create the head node and start with an empty list. */
    TacticsTextWidgetList();
    /** @brief Release the value nodes and the head node. */
    virtual ~TacticsTextWidgetList();
};
/** Linked list with an empty head node, owned value nodes, and a count. */
struct TacticsCoordinatePositionList
{
    struct TacticsCoordinateNode* head;
    u32 count;
    /** @brief Create the head node and start with an empty list. */
    TacticsCoordinatePositionList();
    /** @brief Release the value nodes and the head node. */
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
    /** @brief Move the chosen selector to its preceding entry. */
    virtual void func_slot68();
    /** @brief Move the chosen selector to its following entry. */
    virtual void func_slot6c();
    /** @brief Map the chosen selector's last five entries to its first three. */
    virtual void func_slot70();
    /** @brief Map the chosen selector's first three entries to entries three, five, and six. */
    virtual void func_slot74();
    /** @brief Apply the chosen selector's entry. @return Selection action status. */
    virtual u8 func_slotb0();
    /**
     * @brief Return to the first selector, update control-mode flags, or open its child window.
     * @return Two after the action, or zero when the runtime or child allocation is absent.
     */
    virtual u8 func_slotb4();
    /**
     * @brief Initialize the paired selectors and their eight resource rows.
     * @param associated Resource source forwarded to the base and text displays.
     * @return One on success, otherwise zero when records or required displays are absent.
     */
    virtual s32 func_slotf4(void* associated);

    void* character_records;
    void* entry_records;
    u8* character_record_buffer;
    u8* entry_record_buffer;
    struct FieldObject23B1D0* first_selector;
    struct FieldObject23B1D0* second_selector;
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
 * @brief Save the enabled grid selection and copy its node position to the display.
 * @param object Tactics receiver holding the grid, node list, and display target.
 * @return Zero when the grid's control byte is clear; otherwise one.
 */
u8 save_grid_selection_to_display(TacticsGridOwner* object);

/**
 * @brief Color up to six list displays and place the cursor for the selected grid entry.
 * @param object Tactics receiver holding the display list, grid, and cursor.
 */
void refresh_grid_list_selection(TacticsWindow18B420* object);

/**
 * @brief Place the present indicators using the selected grid row's coordinate pairs.
 * @param object Tactics receiver holding the grid, indicators, and base coordinates.
 */
void position_grid_indicators(TacticsGridOwner* object);

/**
 * @brief Enqueue the receiver for deferred processing.
 * @param object Receiver to append to the resident object queue.
 */
void enqueue_resident_object(void* object);

/**
 * @brief Select a preset display position, clearing it for an invalid index.
 * @param object Receiver holding the position pair.
 * @param index Zero-based preset index.
 * @return The receiver's updated position pair.
 */
TacticsPresetPosition* set_preset_position_from_index(TacticsPresetOwner* object, s32 index);

typedef struct TacticsListNode
{
    void* value;
    struct TacticsListNode* next;
#ifdef __cplusplus
    /** @brief Finish the node lifetime; the stored value is not owned. */
    ~TacticsListNode() {}
#endif
} TacticsListNode;

typedef struct TacticsList
{
    TacticsListNode* head;
} TacticsList;

/**
 * @brief Mark each icon active and color the selected one differently.
 * @param object Holder of the icon list.
 * @param selected Index of the icon to color differently.
 */
void color_icon_list_selection(void* object, s16 selected);

/**
 * @brief Return the field at byte offset 0x20.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 get_field_word_20(void* object);

/**
 * @brief Store the field at byte offset 0x20.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void set_field_word_20(void* object, u32 value);

/**
 * @brief Return the field at byte offset 0x24.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 get_field_word_24(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void tactics_callback_noop(void* object);

/**
 * @brief Return bit zero of the byte at offset 0x38.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 read_mode_flag_bit(void* object);

/**
 * @brief Return the field at byte offset 0x34.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 read_word_at_34(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 return_constant_four(void* object);

/**
 * @brief Store the field at byte offset 0x24.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void write_word_at_24(void* object, u32 value);

/**
 * @brief Store the field at byte offset 0x28.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void write_byte_at_28(void* object, u8 value);

/**
 * @brief Return the field at byte offset 0x28.
 * @param object Object containing the field.
 * @return The field value.
 */
s8 read_signed_byte_at_28(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 return_zero_callback_6(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 return_zero_callback_1(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void noop_callback_1(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 return_zero_callback_2(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void noop_callback_2(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void noop_callback_3(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void noop_callback_4(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 return_zero_callback_3(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 return_zero_callback_4(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 return_zero_callback_5(void* object);

/**
 * @brief Return the node at `index`. Index zero is the first node after the head node.
 * @param list List to search.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
TacticsListNode* get_widget_node_at_index(TacticsList* list, s32 index);

/**
 * @brief Return the node at `index`. Index zero is the first node after the head node.
 * @param list List to search.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
TacticsListNode* get_stat_value_node(TacticsList* list, s32 index);

/**
 * @brief Return the node at `index`. Index zero is the first node after the head node.
 * @param list List to search.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
TacticsListNode* get_text_widget_node(TacticsList* list, s32 index);

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
