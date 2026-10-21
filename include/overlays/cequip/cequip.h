#ifndef SO3_OVERLAYS_CEQUIP_CEQUIP_H
#define SO3_OVERLAYS_CEQUIP_CEQUIP_H

#include "types.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_001E1590.h"

typedef struct EquipNewItemTypeList EquipNewItemTypeList;
typedef struct EquipItemTypeList EquipItemTypeList;
typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;
typedef struct EquipController EquipController;

#ifdef __cplusplus
/** Item type IDs that include a newly obtained item, behind a sentinel node. */
struct EquipNewItemTypeList
{
    struct EquipNewItemTypeNode* head;
    u32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    EquipNewItemTypeList();
    /** @brief Release the value nodes and sentinel storage. */
    virtual ~EquipNewItemTypeList();
};

/** Item type records listed for the selected slot, behind a sentinel node; a null record is the "(None)" row. */
struct EquipItemTypeList
{
    struct EquipItemTypeNode* head;
    u32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    EquipItemTypeList();
    /** @brief Release the value nodes and sentinel storage. */
    virtual ~EquipItemTypeList();
};

/** Contextual copies of the recovered list-node base and sentinel. */
typedef LibClass171E80 EquipClass182318;
typedef LibClass171E90 EquipClass182328;

/** Contextual copy of the movement widget's storage base. */
typedef ItemCreationClass185050 EquipClass182340;

/** Contextual tooltip widget with its owned DMA storage and resident table. */
struct EquipClass1797B0 : public LibClass178600
{
    /** @brief Initialize the tooltip display and drawing storage. */
    EquipClass1797B0()
    {
        unk38 = 0x12;
    }
    /** @brief Release tooltip drawing storage and the widget base. */
    virtual ~EquipClass1797B0();
    /** @brief Draw the tooltip rectangle and its stored resource. */
    virtual void draw();
    LibStorageBlock0C unk40;
    u8 unk4c[4];
};

/** Resident tooltip container with one tooltip and eight owned text widgets. */
struct EquipClass1796F0 : public LibObject178660
{
    /** @brief Initialize the tooltip container and its embedded displays. */
    EquipClass1796F0()
    {
        unk6c = 0x6FF8;
    }
    /** @brief Destroy the text array, tooltip, and container bases. */
    virtual ~EquipClass1796F0();
    /** @brief Update the tooltip text animation. @param first First update flag. @param second Second update flag. @param third Third update flag. */
    virtual void func_00412C40(u32 first, u32 second, u32 third);
    EquipClass1797B0 unkf0;
    LibObject178750 unk140[8];
    u8 unk9e0[0x30];
};

struct FieldRecordSelection;
/** Help bar with the "Equipment" title and label and a scrolling help line. */
struct EquipHelpWindow : public FieldClass15AE70
{
    /** @brief Initialize the text display, timer, and scrolling bounds. */
    EquipHelpWindow()
    {
        text = 0;
        scroll_span = 0;
        unkb0[0] = 0;
        initial_pause_frames = 0;
        scroll_phase = 0;
        label_right_edge = 0.0f;
        initial_text_x = 0.0f;
        clip_x = 0.0f;
        clip_width = 0.0f;
    }

    /** @brief Destroy the scrolling text window. */
    virtual ~EquipHelpWindow();
    /** @brief Hold the display position until its timer expires, then scroll and wrap it. */
    virtual void func_slot5c();
    /** @brief Reset the text display and recompute its width for the supported key range. @param text_key Text resource key. */
    virtual void func_slot60(s32 text_key);
    /** @brief Create the text, frame and scrolling display. @param associated Full resource source word. @return One when initial displays exist, otherwise zero. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* text;
    s32 scroll_span;
    u8 unkb0[2];
    s16 initial_pause_frames;
    u8 scroll_phase;
    u8 unkb5[3];
    float label_right_edge;
    float initial_text_x;
    float clip_x;
    float clip_width;
};

/** Yes/No window that asks "Finish equipping characters?" before leaving the menu. */
struct EquipExitConfirmWindow : public FieldClass15AE70
{
    /** @brief Initialize the selection grid pointer and signed selection index. */
    EquipExitConfirmWindow()
    {
        grid = 0;
        selected = -1;
    }

    /** @brief Destroy the initial equipment window. */
    virtual ~EquipExitConfirmWindow();
    /** @brief Create the panel, text labels and selection grid. @param associated Full resource source word. @param x Window horizontal position. @param y Window vertical position. @param code Nested display initializer code. @return One when all displays exist, otherwise zero. */
    virtual s32 func_slot10(u32 associated, float x, float y, s32 code);
    /** @brief Refresh icon colors while this window is selected. */
    virtual void func_slot5c();
    /** @brief Activate the selected icon or set the empty-selection state. @return One to stay, or two after cancellation. */
    virtual u8 func_slotb0();
    /** @brief Hide this window and restore the associated State window. @return Two. */
    virtual u8 func_slotb4();
    /** @brief Forward direction zero to the selection grid and test its result. */
    virtual void func_slot68();
    /** @brief Forward direction one to the selection grid and test its result. */
    virtual void func_slot6c();
    /** @brief Color each active icon according to its selection index. @param selected Selected icon index. */
    virtual void func_slotf4(s16 selected);
    FieldObject23CEA0* grid;
    s16 selected;
};

/** Selected character panel: name, level, portrait, Optimize/Switch prompts, and arrows when there are several characters. */
struct EquipCharacterWindow : public FieldClass15AE70
{
    /** @brief Initialize the window displays and acquire the active record selection. */
    EquipCharacterWindow();
    /** @brief Show the portrait of the selected character and hide the others. */
    void show_current_portrait();
    /** @brief Destroy the equipment window. */
    virtual ~EquipCharacterWindow();
    /** @brief Enable the display widget while its State window is selected. */
    virtual void func_slot5c();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    s16 character_slot;
    u8 unkaa[2];
    FieldRecordSelection* selection;
    LibObject175140* name_text;
    LibObject178750* level_label;
    LibObject174F20* level_value;
    ItemCreationClass174C40* left_indicator;
    ItemCreationClass174C40* right_indicator;
    ItemCreationOptionResourceDisplay* portraits[8];
    u8 portrait_slots[8];
    LibObject178750* optimize_prompt;
    LibObject178750* switch_prompt;
};

/** Background window owning three displays of resource 11. */
struct EquipResourceWindow : public FieldClass15AE70
{
    /** @brief Initialize the three option display pointers. */
    EquipResourceWindow()
    {
        left_tile = 0;
        middle_tile = 0;
        right_tile = 0;
    }

    /** @brief Destroy the option window. */
    virtual ~EquipResourceWindow();
    /** @brief Create and attach the three option displays. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
    ItemCreationOptionResourceDisplay* left_tile;
    ItemCreationOptionResourceDisplay* middle_tile;
    ItemCreationOptionResourceDisplay* right_tile;
};

/** Background panel behind the item lists. */
struct EquipItemListPanel : public FieldClass15AE70
{
    /** @brief Initialize the panel's Field base. */
    EquipItemListPanel()
    {
    }

    /** @brief Destroy the panel window. */
    virtual ~EquipItemListPanel();
    /** @brief Create and attach the panel display. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
};

struct EquipController;
/** Partial view of a 0x114-byte resource record with its protected equipment entries. */
struct EquipResourceEquipment
{
    u8 unk00[0xC];
    s16 encoded_slot_count;
    s16 encoded_last_slot;
    s16 encoded_items[4];
    u8 unk18[0xD8];
    s32 check_word;
    u8 unkf4[0x18];
    s32 check_salt;
    u8 unk110[4];
};
/** Slot name, item icon, and ATK/DEF/AGL/HIT/INT rows comparing the current value with the selected item's. */
struct EquipStatComparisonWindow : public FieldClass15AE70
{
    /** @brief Initialize item comparison records and display pointers. @param state Owning equipment State. */
    EquipStatComparisonWindow(EquipController* state);
    /** @brief Refresh the selected item icon and both statistic columns. @param category Selected category. @param selected Selected item record index. */
    void refresh_item_details(u8 category, s16 selected);
    /** @brief Destroy the item-details window. */
    virtual ~EquipStatComparisonWindow();
    /** @brief Create and attach the item-details displays. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
    EquipController* controller;
    u8 slot;
    u8 unkad;
    s16 item;
    s16 preview_item;
    u8 unkb2;
    u8 unkb3;
    FieldRecord preview_record;
    /** Encoded resource record used for the comparison. */
    EquipResourceEquipment preview_equipment;
    LibObject178750* slot_label;
    LibObject172410* item_icon;
    LibObject178750* stat_labels[5];
    LibObject178750* separators[5];
    LibObject178750* arrows[5];
    LibObject174F20* current_values[5];
    LibObject174F20* preview_values[5];
};

/** Background panel behind the equipment slot window. */
struct EquipSlotPanel : public FieldClass15AE70
{
    /** @brief Initialize the category panel's Field base. */
    EquipSlotPanel()
    {
    }

    /** @brief Destroy the category panel window. */
    virtual ~EquipSlotPanel();
    /** @brief Create and attach the category panel display. @param associated Full resource source word. @return One. */
    virtual s32 func_slotf4(u32 associated);
};

struct EquipParameterWindow;
struct EquipSlotWindow;
struct EquipPackedRecord;
struct EquipItemListWindow;
/** Equipment menu controller: loads the menu resource and builds its windows. */
struct EquipController : public FieldClass153E30
{
    /** @brief Initialize the equipment State and its resource table entries. */
    EquipController();
    /** @brief Destroy the equipment State. */
    virtual ~EquipController();
    /** @brief Create and connect the equipment State displays. @return One after display setup. */
    virtual s32 init_windows();
    /** @brief Load an aligned resource and create the State displays. @param buffer Resource buffer. @return Display creation result, or zero for a null buffer. */
    virtual s32 on_resource_loaded(void* buffer);
    /** @brief Report this object's default list kind. @return Four. */
    virtual s32 get_default_list_kind();
    /** @brief Submit the State to the resident object queue. */
    virtual void func_001DD7B0();
    /**
     * @brief Allocate and initialize the State's record selection.
     * @return One when a selection exists and initialization succeeds; otherwise zero.
     */
    virtual u8 func_00264110();
    /** @brief Return the loaded resource slot. @return Resource slot. */
    virtual u32 get_resource_slot();
    /** @brief Report whether window setup finished. @return Setup flag. */
    virtual u8 windows_ready();
    /** @brief Release the State resources and queue its receiver. */
    virtual void func_slot5c();
    /** @brief Return the record selection. @return Current record selection. */
    virtual FieldRecordSelection* selected_records();
    s32 resource_slot;
    FieldRecordSelection* selection;
    u8 windows_initialized : 1;
    u8 unk3c_1_7 : 7;
    u8 unk3d[3];
    EquipCharacterWindow* character_window;
    EquipSlotWindow* slot_window;
    EquipStatComparisonWindow* comparison_window;
    EquipItemListPanel* item_list_panel;
    EquipItemListWindow* item_list_window;
    EquipParameterWindow* parameter_window;
    u32 unk58;
    u32 unk5c;
    u16 selected_slot;
    u8 unk62[2];
    s32 selected_item_type;
    void* tooltip;
};

struct FieldState23B3A0;
/** Selected item's description, or its "Parameter Changes" (ATK, HIT, DEF, AGL, INT bonuses) while toggled on. */
struct EquipParameterWindow : public FieldClass15AE70
{
    /** @brief Initialize the category detail state, labels, and numeric displays. */
    EquipParameterWindow()
    {
        description_key = 0;
        show_parameters = 0;
        for (s32 i = 0; i < 5; i++)
        {
            parameter_labels[i] = 0;
            parameter_values[i] = 0;
        }
    }

    /** @brief Destroy the category detail window. */
    virtual ~EquipParameterWindow();
    /** @brief Refresh the selected category detail displays. */
    virtual void func_slot5c();
    /** @brief Create the multiline and comparison displays. @param associated Full resource source word. @return One, or zero without an associated object. */
    virtual s32 func_slotf4(u32 associated);
    LibObject174D90* description;
    LibObject178750* title;
    LibObject178750* parameter_labels[5];
    LibObject178750* separators[5];
    LibObject174F20* parameter_values[5];
    s32 description_key;
    u8 show_parameters;
};
/** Weapon, Armor, and Accessory slots with the equipped item or "(None)" in each, and the slot cursor. */
struct EquipSlotWindow : public FieldClass15AE70
{
    /** @brief Initialize the category widgets and attach the State selection. @param state Owning equipment State. */
    EquipSlotWindow(EquipController* state);
    /** @brief Destroy the category window. */
    virtual ~EquipSlotWindow();
    /** @brief Update the selected category tooltip. */
    virtual void func_slot5c();
    /** @brief Restore the associated record displays and start the selector animation. */
    virtual void func_slot64();
    /** @brief Cycle the selector backward and rebuild the associated category list. */
    virtual void func_slot68();
    /** @brief Cycle the selector forward and rebuild the associated category list. */
    virtual void func_slot6c();
    /** @brief Activate a supported category and restore its associated list window. @return One on activation, or three for an unsupported category. */
    virtual u8 func_slotb0();
    /** @brief Activate the alternate selection window. @return Selection result. */
    virtual u8 func_slotb4();
    /** @brief Apply the selected record action and refresh category displays. @return One. */
    virtual u8 func_slotb8();
    /** @brief Toggle the owning State display flag. @return One. */
    virtual u8 func_slotbc();
    /** @brief Cycle to the previous record and rebuild its displays. @return Four after cycling, or zero when unavailable. */
    virtual s32 func_slotd8();
    /** @brief Cycle to the next record and rebuild its displays. @return Four after cycling, or zero when unavailable. */
    virtual s32 func_slotdc();
    /** @brief Create category widgets. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    EquipController* controller;
    FieldRecordSelection* selection;
    float row_spacing;
    EquipPackedRecord* current_item;
    s16 equipped_items[4];
    u8 usable_slot_count;
    u8 unkc1[3];
    LibClass174EF0* slot_labels[4];
    LibObject172410* item_icons[4];
    LibClass174EF0* empty_labels[4];
    void* unkf4;
    void* parameter_window;
    FieldState23B3A0* equipment_slot_selector;
    FieldClass15AE70* comparison_window;
    FieldClass15AD40* item_list;
    u16 active_slot;
};

/** List of the unequipped items of the selected type, with their icons and modification marks. */
struct EquipItemInstanceListWindow : public FieldClass15AD40
{
    /** @brief Initialize list display pointers and attach the option State. @param state Owning equipment State. */
    EquipItemInstanceListWindow(EquipController* state);
    /** @brief Destroy the Field list window. */
    virtual ~EquipItemInstanceListWindow();
    /** @brief Run the equipment list update hook. */
    virtual void func_slot5c();
    /** @brief Activate the selected record and restore the category window. @return One on success, or three when no record is selectable. */
    virtual u8 func_slotb0();
    /** @brief Restore the associated window and clear the detail display. @return Two. */
    virtual u8 func_slotb4();
    /** @brief Return the empty equipment selection result. @return Zero. */
    virtual u8 func_slotb8();
    /** @brief Toggle the linked display flag. @return One. */
    virtual u8 func_slotbc();
    /** @brief Refresh the visible equipment rows. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Set the visible equipment row positions. @param start Base row position. */
    virtual void set_scroll_position(float start);
    /** @brief Create the equipment list displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Set the paired display flags. @param first First flag. @param second Second flag. */
    virtual void func_slot10c(u32 first, u32 second);
    /** @brief Recount the category records and clamp the visible selection. */
    void recount_rows();
    ItemCreationOptionResourceDisplay* factor_marks[9];
    LibObject172410* item_icons[9];
    LibClass178630* panel;
    void* mark_allocation;
    EquipController* controller;
    void* tooltip;
    s16 tooltip_item;
};

/** Item types that fit the selected slot, with how many of each are available; types holding a new item are tinted green. */
struct EquipItemListWindow : public FieldClass15AD40
{
    /** @brief Initialize the display pointers and owned lists. @param state Owning equipment State. */
    EquipItemListWindow(EquipController* state);
    /** @brief Destroy the owned lists and the Field window. */
    virtual ~EquipItemListWindow();
    /** @brief Update the selected category, row highlight, and detail window. */
    virtual void func_slot5c();
    /** @brief Activate the category list or create the selected record window. @return Selection result. */
    virtual u8 func_slotb0();
    /** @brief Restore the associated window and hide the alternate window. @return Two. */
    virtual u8 func_slotb4();
    virtual u8 func_slotbc();
    /** @brief Refresh category names, availability counts, and selection colors. @param start First category row. */
    virtual void refresh_rows(s32 start);
    /** @brief Position all three displays in each row. @param start Base row position. */
    virtual void set_scroll_position(float start);
    /** @brief Create the category names, counts, and selection displays. @param associated Full resource source word. @return One. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Rebuild the list for the selected category. @param category Category index, clamped to two. */
    virtual void func_slot108(u8 category);
    virtual void func_slot10c(u32 first, u32 second);
    LibObject178750* separators[9];
    LibObject174F20* counts[9];
    EquipController* controller;
    void* unk184;
    EquipItemTypeList item_types;
    s16 unk194;
    EquipNewItemTypeList new_item_types;
    FieldClass15AE70* comparison_window;
};

extern "C" {
#endif

/**
 * @brief Add an item type ID to the end of the list.
 * @param list List to append to.
 * @param value One-based item type ID.
 */
void append_new_item_type(EquipNewItemTypeList* list, u16 value);

/**
 * @brief Add an item type record to the end of the list.
 * @param list List to append to.
 * @param value Item type record, or null for the "(None)" row.
 */
void append_item_type(EquipItemTypeList* list, ItemCreationCategoryRecord* value);

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
 * @brief Return the node at `count`. Index zero is the first node after the sentinel.
 * @param object New item type list.
 * @param count Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
void* get_new_item_type_node(void* object, s32 count);

/**
 * @brief Return the node at `count`. Index zero is the first node after the sentinel.
 * @param object Item type list.
 * @param count Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
void* get_item_type_node(void* object, s32 count);

/**
 * @brief Delete the list nodes after the sentinel and reset the list count.
 * @param list List whose nodes should be released.
 */
void clear_new_item_types(EquipNewItemTypeList* list);

/**
 * @brief Delete the list nodes after the sentinel and reset the list count.
 * @param list List whose nodes should be released.
 */
void clear_item_types(EquipItemTypeList* list);

#ifdef __cplusplus
}
#endif

#endif
