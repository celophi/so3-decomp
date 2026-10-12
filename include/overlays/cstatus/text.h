#ifndef SO3_OVERLAYS_CSTATUS_TEXT_H
#define SO3_OVERLAYS_CSTATUS_TEXT_H

#include "types.h"

typedef struct StatusWidgetList StatusWidgetList;
typedef struct StatusResourceState StatusResourceState;
typedef struct StatusHelpWindow StatusHelpWindow;
typedef struct StatusNameWindow StatusNameWindow;
typedef struct StatusCharacterWindow StatusCharacterWindow;

#ifdef __cplusplus
struct ItemCreationOptionResourceDisplay;
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_0044ABE0.h"

/** Status background window displaying the three resource panels. */
struct StatusBackgroundWindow : public FieldClass15AE70
{
    /** @brief Initialize the background window base. */
    StatusBackgroundWindow()
    {
    }
    /** @brief Destroy the background window base. */
    virtual ~StatusBackgroundWindow();
    /** @brief Create the status resource panels. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
};
/** Status caption window with a timed scrolling text display. */
struct StatusHelpWindow : public FieldClass15AE70
{
    /** @brief Initialize the text links and scroll state. */
    StatusHelpWindow()
    {
        help_caption = 0;
        scroll_distance = 0;
        unkb0[0] = 0;
        hold_timer = 0;
        scroll_active = 0;
        heading_width = 0;
        initial_text_x = 0;
        clip_x = 0;
        clip_width = 0;
    }
    /** @brief Destroy the caption window base. */
    virtual ~StatusHelpWindow();
    /** @brief Update the scrolling text position. */
    virtual void func_slot5c();
    /** @brief Set the selected caption. @param key Signed caption key. */
    virtual void func_slot60(s32 key);
    /** @brief Create the captions and frame geometry. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* help_caption;
    s32 scroll_distance;
    u8 unkb0[2];
    s16 hold_timer;
    u8 scroll_active;
    float heading_width;
    float initial_text_x;
    float clip_x;
    float clip_width;
};

struct StatusWidgetNode;

/** Status display list with an owned sentinel and a virtual destructor. */
struct StatusItemWidgetList
{
    StatusWidgetNode* head;
    s32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    StatusItemWidgetList();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~StatusItemWidgetList();
};

/** Status display list with an owned sentinel and a virtual destructor. */
struct StatusNumericWidgetList
{
    StatusWidgetNode* head;
    s32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    StatusNumericWidgetList();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~StatusNumericWidgetList();
};

/** Status display list with an owned sentinel and a virtual destructor. */
struct StatusTextWidgetList
{
    StatusWidgetNode* head;
    s32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    StatusTextWidgetList();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~StatusTextWidgetList();
};

/** Character status window displaying statistics, equipment, battle skills, and a model preview. */
struct StatusCharacterWindow : public FieldClass15AE70
{
    /** @brief Initialize the character window and its three owned widget lists. */
    StatusCharacterWindow();
    /** @brief Release the three display lists and window base. */
    virtual ~StatusCharacterWindow();
    /** @brief Detach the nested container and release the window state. */
    virtual void func_slot0c();
    /** @brief Update model cancellation and window transitions. */
    virtual void func_slot5c();
    /** @brief Refresh the character name, surname, and name-entry hint. */
    virtual void func_slot64();
    /** @brief Select the preceding status display page. */
    virtual void func_slot68();
    /** @brief Select the following status display page. */
    virtual void func_slot6c();
    /** @brief Open the character name editor. @return Handler result. */
    virtual s32 func_slotb0();
    /** @brief Close the character window. @return Handler result. */
    virtual s32 func_slotb4();
    /** @brief Cycle the selected character's model variant. @return Handler result. */
    virtual s32 func_slotb8();
    /** @brief Select the preceding character. @return Handler result. */
    virtual s32 func_slotd8();
    /** @brief Select the following character. @return Handler result. */
    virtual s32 func_slotdc();
    /** @brief Create the character's portrait, stats, equipment, and scroll widgets. @param associated Full resource source word. @return One on completion, zero on failure. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* selection;
    u8 character_change_pending;
    u8 unkad[3];
    LibObject175140* character_name_widget;
    LibObject178750* surname_caption;
    LibObject178750* name_entry_hint;
    u16 selected_slot;
    u8 unkbe[2];
    float name_x;
    float name_y;
    u8 resource_slots[8];
    float portrait_x;
    float portrait_y;
    ItemCreationOptionResourceDisplay* portrait;
    ItemCreationClass172870* name_divider;
    LibObject178660* container;
    StatusTextWidgetList text_widgets;
    StatusNumericWidgetList numeric_widgets;
    StatusItemWidgetList item_widgets;
    LibObject174F20* hp_value;
    LibObject174F20* max_hp_value;
    LibObject174F20* mp_value;
    LibObject174F20* max_mp_value;
    LibObject174F20* level_value;
    LibObject174F20* experience_value;
    LibObject174F20* next_level_experience_value;
    LibObject174F20* attack_value;
    LibObject174F20* defense_value;
    LibObject174F20* agility_value;
    LibObject174F20* hit_value;
    LibObject174F20* intelligence_value;
    LibObject178750* max_level_caption;
    LibObject178750* skills_label;
    LibObject178750* sp_label;
    LibObject178750* cp_label;
    LibObject174F20* sp_value;
    LibObject174F20* assigned_cp_value;
    LibObject178750* cp_separator;
    LibObject174F20* cp_value;
    LibObject178750* short_minor_attack_button;
    LibObject178750* short_minor_attack_label;
    LibObject178750* long_minor_attack_button;
    LibObject178750* long_minor_attack_label;
    LibObject178750* short_major_attack_button;
    LibObject178750* short_major_attack_label;
    LibObject178750* long_major_attack_button;
    LibObject178750* long_major_attack_label;
    LibObject178750* support_skill_1_label;
    LibObject178750* support_skill_1_caption;
    LibObject178750* support_skill_2_label;
    LibObject178750* support_skill_2_caption;
    LibObject178750* short_minor_attack_skill_caption;
    LibObject178750* long_minor_attack_skill_caption;
    LibObject178750* short_major_attack_skill_caption;
    LibObject178750* long_major_attack_skill_caption;
    u32 battle_skill_caption_keys[6];
    s32 assigned_cp;
    u8 scroll_page;
    u8 scroll_active;
    u8 unk1b6[2];
    LibClass1725D0* scroll_marker;
    float scroll_extent;
    float scroll_position;
    float scroll_step;
    float scroll_delta;
    float scroll_timer;
    u8 alternate_portrait_group;
    u8 unk1d1[3];
    FieldStatus14* character_model;
    u8 model_cancel_pending;
    u8 model_reload_pending;
    u8 window_transition_pending;
    u8 unk1db;
    LibObject178750* color_setup_hint;
    LibObject172410* equipment_values[4];
    LibObject178750* empty_equipment_captions[4];
};

/** Character name editor with kana and alphanumeric grids and the ten default names. */
struct StatusNameWindow : public FieldClass15AE70
{
    /** @brief Initialize the glyph grid and default character names. */
    StatusNameWindow();
    /** @brief Destroy the name editor window base. */
    virtual ~StatusNameWindow();
    /** @brief Move the name cursor to the selected glyph. */
    virtual void func_slot5c();
    /** @brief Move the selection to the preceding row. */
    virtual void func_slot68();
    /** @brief Move the selection to the following row. */
    virtual void func_slot6c();
    /** @brief Move the selection to the preceding column. */
    virtual void func_slot70();
    /** @brief Move the selection to the following column. */
    virtual void func_slot74();
    /** @brief Handle the current selection command. @return Handler result. */
    virtual s32 func_slotb0();
    /** @brief Delete the last name entry. @return Handler result. */
    virtual s32 func_slotb4();
    /** @brief Return the default command result. @return Zero. */
    virtual s32 func_slotc0();
    /** @brief Return the default command result. @return Zero. */
    virtual s32 func_slotc4();
    /** @brief Select the Confirm command. */
    virtual void func_slote0();
    /** @brief Restore the default character name and refresh its glyphs. */
    virtual void func_slote4();
    /** @brief Create the name-entry displays. @param associated Associated object. @return Creation result. */
    virtual s32 func_slotf4(void* associated);
    FieldRecordSelection* selection;
    LibObject178750* surname_caption;
    LibObject178750* name_glyph_widgets[7];
    LibObject175140* name_text;
    LibClass178600* name_cursor;
    u16 name_glyph_keys[7];
    u8 unke2[2];
    s32 first_name_marker;
    s8 selected_name_glyph;
    s8 last_name_byte;
    u8 name_bytes[24];
    u8 unk102[2];
    float name_x;
    float name_y;
    LibClass175030* grid_marker;
    s32 selected_grid_cell;
    u8 grid_mode;
    u8 unk115;
    u16 selected_character_id;
    float command_x;
    float row_height;
    float glyph_scale;
    float glyph_width;
    s8 default_names[10][32];
    LibObject178750* command_labels[7];
    ItemCreationOptionResourceDisplay* portrait;
    u8 portrait_resource_slot;
    u8 unk289[3];
    LibObject178750* alphabet_symbol_grid;
    u8 hiragana_bytes[90];
    u8 katakana_bytes[90];
    u8 alphanumeric_bytes[80];
};

#endif

extern const char g_status_default_fayt_name[];
extern const char g_status_default_sophia_name[];
extern const char g_status_default_maria_name[];
extern const char g_status_default_cliff_name[];
extern const char g_status_default_nel_name[];
extern const char g_status_default_albel_name[];
extern const char g_status_default_roger_name[];
extern const char g_status_default_peppita_name[];
extern const char g_status_default_adray_name[];
extern const char g_status_default_mirage_name[];
/** Byte templates copied into the status selection glyph maps. */
typedef struct StatusGlyphMap90
{
    u8 values[90];
} StatusGlyphMap90;

typedef struct StatusGlyphMap80
{
    u8 values[80];
} StatusGlyphMap80;

#ifdef __cplusplus
extern "C" {
#endif

extern StatusGlyphMap90 g_status_hiragana_bytes;
extern StatusGlyphMap90 g_status_katakana_bytes;
extern StatusGlyphMap80 g_status_alphanumeric_bytes;

/**
 * @brief Initialize the name editor's glyph lookup maps.
 * @param object Character name editor.
 */
void status_initialize_name_maps(StatusNameWindow* object);

/**
 * @brief Refresh the selected character portrait and its scale.
 * @param object Character status window.
 */
void status_refresh_portrait(StatusCharacterWindow* object);

/**
 * @brief Refresh the assigned battle-skill captions and total their CP cost.
 * @param object Character status window with the current record selection.
 */
void status_refresh_battle_skill_keys(StatusCharacterWindow* object);

/**
 * @brief Scroll the three status display lists and advance their indicator.
 * @param object Character status window.
 */
void status_update_scroll(StatusCharacterWindow* object);

/**
 * @brief Move the status selection to the requested entry.
 * @param object Character name editor.
 * @param value Requested entry index.
 */
void status_move_name_grid_cursor(StatusNameWindow* object, s32 value);

/**
 * @brief Append the diacritic associated with the selected grid code.
 * @param object Character name editor.
 * @param code Selected grid code.
 */
void status_append_name_diacritic(StatusNameWindow* object, s16 code);

/**
 * @brief Append the selected grid entry and refresh its display.
 * @param object Character name editor.
 * @param mode Supplied grid mode; unused.
 */
void status_append_selected_name_glyph(StatusNameWindow* object, u8 mode);

/**
 * @brief Remove the last encoded name entry and refresh the text and cursor.
 * @param object Character name editor.
 * @return Two after removing an entry, or three when the name is empty.
 */
s32 status_remove_last_name_entry(StatusNameWindow* object);

/**
 * @brief Select the alphanumeric grid and refresh its display flags.
 * @param object Character name editor.
 * @param mode Supplied grid mode; unused.
 */
void status_select_alphanumeric_grid(StatusNameWindow* object, u8 mode);

/** @brief Refresh the selected entry and its cursor. @param object Character name editor. */
void status_refresh_name_markers(StatusNameWindow* object);
/** @brief Refresh the current entry display. @param object Character name editor. */
void status_refresh_name_glyphs(StatusNameWindow* object);
/** @brief Decode the current entry bytes into glyph keys. @param object Character name editor. */
void status_decode_name_glyphs(StatusNameWindow* object);

/**
 * @brief Begin a status scroll when the requested mode differs from the current mode.
 * @param object Character status window.
 * @param mode Requested scroll mode; zero and one choose opposing directions.
 */
void status_begin_scroll(StatusCharacterWindow* object, u16 mode);

/**
 * @brief Refresh the selected character's name, statistics, equipment, and status captions.
 * @param object Character status window.
 */
void status_refresh_character_display(StatusCharacterWindow* object);

/**
 * @brief Create and attach the character model preview when needed.
 * @param object Character status window containing the optional model preview.
 */
void status_create_character_model(StatusCharacterWindow* object);

/**
 * @brief Release the nodes after the sentinel without destroying their payloads.
 * @param list List whose linked nodes are released.
 */
void status_clear_item_widgets(StatusWidgetList* list);

/**
 * @brief Release the nodes after the sentinel without destroying their payloads.
 * @param list List whose linked nodes are released.
 */
void status_clear_numeric_widgets(StatusWidgetList* list);

/**
 * @brief Release the nodes after the sentinel without destroying their payloads.
 * @param list List whose linked nodes are released.
 */
void status_clear_text_widgets(StatusWidgetList* list);

/**
 * @brief Follow links from the first node in a list.
 * @param list Address of the list head pointer.
 * @param count Number of additional links to follow.
 * @return Reached node, or null when the chain ends.
 */
void* status_list_node_at(void* list, s32 count);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void status_append_scissor_widget(StatusWidgetList* list, void* value);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void status_append_item_widget(StatusWidgetList* list, void* value);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void status_append_name_widget(StatusWidgetList* list, void* value);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void status_append_numeric_widget(StatusWidgetList* list, void* value);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void status_append_text_widget(StatusWidgetList* list, void* value);

#ifdef __cplusplus
}
#endif

#endif
