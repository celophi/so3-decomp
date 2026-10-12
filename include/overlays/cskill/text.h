#ifndef SO3_OVERLAYS_CSKILL_TEXT_H
#define SO3_OVERLAYS_CSKILL_TEXT_H

#include "types.h"

/** Linked nodes used by the indexed list helpers. */
typedef struct SkillListNode
{
    void* value;
    struct SkillListNode* next;
#ifdef __cplusplus
    /** @brief Destroy a node without releasing its stored value. */
    ~SkillListNode()
    {
    }
#endif
} SkillListNode;

/** Float components stored by the paired-value lists. */
typedef struct SkillPairValue
{
    float first;
    float second;
} SkillPairValue;

/** List storage begins with an anchor node. */
typedef struct SkillList
{
    SkillListNode* head;
    u32 count;
} SkillList;

typedef struct SkillList183C48 SkillList183C48;
typedef struct SkillList183C38 SkillList183C38;
typedef struct SkillList184268 SkillList184268;
typedef struct SkillPairList184258 SkillPairList184258;
typedef struct SkillController SkillController;
typedef struct SkillSymbologyHelpWindow SkillSymbologyHelpWindow;
typedef struct SkillSymbologyCharacterWindow SkillSymbologyCharacterWindow;
typedef struct SkillOptionsWindow SkillOptionsWindow;
typedef struct SkillSymbologyWindow SkillSymbologyWindow;
typedef struct SkillTacticalDetailWindow SkillTacticalDetailWindow;
typedef struct SkillGridChoice SkillGridChoice;
typedef struct FieldClass15AE70 FieldClass15AE70;
typedef struct SkillCharacterStats SkillCharacterStats;
#ifdef __cplusplus
class FieldClass153E30;
class LibClass171EF0;
class LibObject178660;
#else
typedef struct FieldClass153E30 FieldClass153E30;
typedef struct LibClass171EF0 LibClass171EF0;
typedef struct LibObject178660 LibObject178660;
#endif
typedef struct SkillTacticalPromptWindow SkillTacticalPromptWindow;
typedef struct SkillCostWindow SkillCostWindow;
typedef struct SkillVector4 SkillVector4;
typedef struct SkillSecondarySelection SkillSecondarySelection;
typedef struct SkillStatusSkillWindow SkillStatusSkillWindow;
typedef struct SkillModeSelection SkillModeSelection;
typedef struct SkillBattleSetupWindow SkillBattleSetupWindow;
typedef struct SkillTacticalWindow SkillTacticalWindow;
typedef struct SkillHelpWindow SkillHelpWindow;
typedef struct SkillCharacterWindow SkillCharacterWindow;
typedef struct SkillHpMpGaugeDrawer SkillHpMpGaugeDrawer;
typedef struct SkillHpMpGauge SkillHpMpGauge;
#ifdef __cplusplus
class ItemCreationClass175110;
#endif

#ifdef __cplusplus
struct SkillPairListNode;
/** List with an allocated anchor, element count, and virtual destructor. */
struct SkillList183C48
{
    SkillListNode* head;
    u32 count;
    /** @brief Allocate the anchor and initialize an empty list. */
    SkillList183C48();
    /** @brief Release the linked nodes and the anchor. */
    virtual ~SkillList183C48();
};

/** List with an allocated anchor, element count, and virtual destructor. */
struct SkillList183C38
{
    SkillListNode* head;
    u32 count;
    /** @brief Allocate the anchor and initialize an empty list. */
    SkillList183C38();
    /** @brief Release the linked nodes and the anchor. */
    virtual ~SkillList183C38();
};

/** List with an allocated anchor, element count, and virtual destructor. */
struct SkillList184268
{
    SkillListNode* head;
    u32 count;
    /** @brief Allocate the anchor and initialize an empty list. */
    SkillList184268();
    /** @brief Release the linked nodes and the anchor. */
    virtual ~SkillList184268();
};

/** List with an allocated anchor, element count, and virtual destructor. */
struct SkillPairList184258
{
    SkillPairListNode* head;
    u32 count;
    /** @brief Allocate the anchor and initialize an empty list. */
    SkillPairList184258();
    /** @brief Release the linked nodes and the anchor. */
    virtual ~SkillPairList184258();
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Append a pair of float values when node allocation succeeds.
 * @param list List receiver.
 * @param value Values copied into the new node.
 */
void func_00364BF0(SkillPairList184258* list, SkillPairValue value);

/**
 * @brief Open the selected Anti-Attack Aura or Damage Conversion detail grid.
 * @param object Window containing the mode table and attached display.
 */
void skill_open_tactical_details(SkillTacticalWindow* object);

/**
 * @brief Rebuild the mode query's displayed selection state.
 * @param record Mode-query receiver.
 */
void func_00351BE0(SkillTacticalWindow* record);

/**
 * @brief Show the selected battle skill's description, or clear it for an empty slot.
 * @param object Battle setup window.
 */
void skill_refresh_battle_message(SkillBattleSetupWindow* object);

/**
 * @brief Update the controller's selected code and associated display state.
 * @param owner Controller receiver.
 * @param code Selected code.
 * @param enabled State flag.
 */
void func_0035AF00(SkillController* owner, s32 code, u8 enabled);

/**
 * @brief Apply the selected record's mode to its protected byte table.
 * @param record Selection receiver.
 * @return Mode application result.
 */
u8 func_003523A0(SkillTacticalWindow* record);

/**
 * @brief Decode current MP and mark valid flags when its checksum fails.
 * @param record Protected values receiver.
 * @return Decoded value, or zero when its checksum is invalid.
 */
u32 skill_character_mp(SkillCharacterStats* record);

/**
 * @brief Clamp and store protected current MP, updating flag bit zero.
 * @param record Character statistics.
 * @param value Requested MP.
 * @return Stored MP, or zero when the MP checksum is invalid.
 */
s32 skill_set_character_mp(SkillCharacterStats* record, s32 value);

/**
 * @brief Decode current HP and mark valid flags when its checksum fails.
 * @param record Protected values receiver.
 * @return Decoded value, or zero when its checksum is invalid.
 */
u32 skill_character_hp(SkillCharacterStats* record);

/**
 * @brief Add flag bits when the protected record's checksum is valid.
 * @param record Encoded flags receiver.
 * @param flags Flag bits to add.
 * @return Updated decoded flags, or five when the checksum is invalid.
 */
u32 skill_add_character_flags(SkillCharacterStats* record, u32 flags);

/**
 * @brief Retain selected flag bits when the protected record's checksum is valid.
 * @param record Encoded flags receiver.
 * @param flags Mask of flag bits to retain.
 * @return Updated decoded flags, or five when the checksum is invalid.
 */
u32 skill_mask_character_flags(SkillCharacterStats* record, u32 flags);

/**
 * @brief Release all paired-value nodes after the anchor and reset the count.
 * @param record List receiver.
 */
void func_00364B70(SkillPairList184258* record);

/** @brief Show help for the selected tactical detail entry. @param object Tactical detail window. */
void skill_refresh_tactical_detail_help(SkillTacticalDetailWindow* object);
/** @brief Select the Aura or Damage Conversion detail grid, or hide both grids. @param object Tactical detail window. @param mode Zero for Aura, one for Damage Conversion, or two to hide both. */
void skill_select_tactical_detail_mode(SkillTacticalDetailWindow* object, s16 mode);
/** @brief Refresh Aura labels, the selected-type marker and current cursor. @param object Tactical detail window. @param reset Nonzero to select the saved Aura type. */
void skill_refresh_aura_rows(SkillTacticalDetailWindow* object, s32 reset);
/** @brief Refresh Damage Conversion labels, the selected-row marker and current cursor. @param object Tactical detail window. @param reset Nonzero to select the saved conversion direction. */
void skill_refresh_damage_conversion_rows(SkillTacticalDetailWindow* object, s32 reset);

/**
 * @brief Refresh the selected detail pointer and checksum-protected status values.
 * @param record Selection and status display storage.
 */
void func_00358200(SkillCharacterWindow* record);

/**
 * @brief Find a node by walking from the list anchor.
 * @param list List to search.
 * @param index Number of links to follow from the first node.
 * @return Node at the given index, or 0 if an earlier link is null.
 */
SkillListNode* func_0035C890(SkillList* list, s32 index);

/**
 * @brief Find a node by walking from the list anchor.
 * @param list List to search.
 * @param index Number of links to follow from the first node.
 * @return Node at the given index, or 0 if an earlier link is null.
 */
SkillListNode* func_0035CAE0(SkillList* list, s32 index);

/**
 * @brief Update paired-list positions and color values using the row spacing.
 * @param record Receiver with the two lists and their base positions.
 * @param scroll_offset Vertical offset subtracted from both base positions.
 */
void skill_position_selection_rows(SkillModeSelection* record, float scroll_offset);

/**
 * @brief Update paired-list item visibility and colors for the current selection.
 * @param record Receiver containing paired lists and selection values.
 */
void skill_refresh_selection_rows(SkillModeSelection* record);

/**
 * @brief Attach the selection marker to the selected skill and refresh its color.
 * @param record Receiver containing the item list and selection state.
 */
void skill_refresh_selection_marker(SkillModeSelection* record);

/** @brief Advance the mode window animation. @param object Mode window. */
void func_0034C060(SkillModeSelection* object);

/**
 * @brief Initialize the damage-conversion grid and register its cursor.
 * @param record Window containing the damage-conversion grid.
 * @return One after setup, or zero when the damage-conversion grid is absent.
 */
s32 skill_initialize_damage_conversion_grid(SkillTacticalDetailWindow* record);

/**
 * @brief Initialize the anti-attack aura grid and register its cursor.
 * @param record Window containing the anti-attack aura grid.
 * @return One after setup, or zero when the aura grid is absent.
 */
s32 skill_initialize_aura_grid(SkillTacticalDetailWindow* record);

/**
 * @brief Configure the selection grid position and register its display state.
 * @param record Receiver with the display owner and selection grid.
 * @param row_count Number of grid rows; zero leaves the grid unchanged.
 * @return One for zero rows or completed setup, otherwise zero without a display owner.
 */
s32 skill_initialize_selection_grid(SkillModeSelection* record, s16 row_count);

/** @brief Create the mode window's text and image rows. @param object Mode window. @return Nonzero after creating the rows. */
s32 func_00351090(SkillModeSelection* object);

/**
 * @brief Cycle the symbology character and refresh its name, MP, and condition markers.
 * @param object Character window.
 * @param forward Nonzero advances selection; zero moves it backward.
 * @return Zero without a selection, otherwise 4.
 */
s32 skill_cycle_symbology_character(SkillSymbologyCharacterWindow* object, s32 forward);

/** @brief Refresh the selected symbol's description, mastery and MP expenditure. @param object Help window. @param selected_index Selected entry index. */
void skill_refresh_symbology_help(SkillSymbologyHelpWindow* object, s32 selected_index);

/** @brief Refresh party and condition markers for the selected symbology character. @param object Character window. */
void skill_refresh_symbology_character_markers(SkillSymbologyCharacterWindow* object);

/**
 * @brief Update the status bytes selected by a mode value.
 * @param object Receiver with pointers to status records.
 * @param mode Zero clears all seven records; a positive or negative value selects one of two records.
 */
/** @brief Hide the tactical prompt for zero, select Yes for positive state, or No for negative state. */
void skill_set_tactical_prompt_state(SkillTacticalPromptWindow* object, s32 state);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C9D0(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035CB20(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035CBB0(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C440(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C4D0(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C560(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C5F0(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C780(SkillList* list, void* value);

/**
 * @brief Release linked nodes after the anchor and clear the list when nonempty.
 * @param record List owner whose nodes are released.
 */
void func_00364A70(SkillList184268* record);

/**
 * @brief Release all linked nodes after the anchor and reset the list count.
 * @param record List receiver.
 */
void func_0035C810(SkillList183C48* record);

/**
 * @brief Release all linked nodes after the anchor and reset the list count.
 * @param record List receiver.
 */
void func_0035CA60(SkillList183C38* record);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_003649E0(SkillList* list, void* value);

/**
 * @brief Clear the list, release its storage, and optionally free the owner.
 * @param record List owner to release.
 * @param flag Free the owner when positive.
 * @return The original owner pointer.
 */
SkillPairList184258* func_00364AF0(SkillPairList184258* record, s16 flag);

/**
 * @brief Refresh the six equipped CP values and their visibility.
 * @param owner Battle setup window.
 * @param mode Nonzero to show CP displays; zero hides them.
 * @return Equipped CP sum when shown, treating -1 as zero, otherwise zero.
 */
s32 skill_refresh_battle_cp_displays(SkillBattleSetupWindow* owner, s32 mode);

/**
 * @brief Set the six-row window's list flags and selection activity.
 * @param object Six-row selection window.
 * @param flag Full window flag, whose low byte controls each display.
 * @param active Nonzero to activate the selection grid.
 */
void skill_set_battle_setup_visibility(SkillBattleSetupWindow* object, u32 flag, s32 active);

/** @brief Refresh the selected skill's costs and damage multiplier. @param object Skill cost window. */
void skill_refresh_costs(FieldClass15AE70* object);

/** @brief Set mode-window display and selection activity. @param object Mode window. @param flag Display flag word. @param active Grid activity value. */
void skill_set_selection_visibility(SkillModeSelection* object, u32 flag, s32 active);

/**
 * @brief Color the paired six-row lists and position the selected-row display.
 * @param record Record containing the lists, selection, and display receiver.
 */
void skill_refresh_battle_selection(SkillBattleSetupWindow* record);

/**
 * @brief Show the selected slot's icon and copy its record links to the owning controller.
 * @param object Window with the slot icons and record selection.
 */
void func_00358310(SkillCharacterWindow* object);

/** @brief Refresh the status-skill levels, next-level SP costs, and maximum-level labels. @param object Status-skill window. */
void func_003559F0(SkillStatusSkillWindow* object);
/** @brief Rebuild the six-row status values. @param object Status-row window. @return One on success, or zero on failure. */
s32 func_00354190(SkillBattleSetupWindow* object);
/** @brief Create battle slot labels, separators, skill names, and slot icons. @param object Battle setup window. @return Row refresh result, or zero on allocation failure. */
s32 func_003547C0(SkillBattleSetupWindow* object);
/** @brief Refresh the tactical modes, selected character's row, and associated displays. @param object Tactical selection window. */
void skill_refresh_tactical_rows(SkillTacticalWindow* object);
/** @brief Rebuild the mode rows for a signed mode code. @param object Mode-selection window. @param mode Signed mode. @return One on success, or zero on failure. */
s32 func_00350890(SkillModeSelection* object, s16 mode);
/** @brief Create the Aura and Damage Conversion labels and selection markers. @param object Tactical detail window. @return One after setup, or zero on failure. */
u8 skill_initialize_tactical_detail_labels(SkillTacticalDetailWindow* object);

/** @brief Rebuild available Aura types and the saved conversion direction. @param object Tactical detail window. */
void skill_refresh_tactical_detail_choices(SkillTacticalDetailWindow* object);

/**
 * @brief Set status-skill display visibility and selection activity.
 * @param object Status-skill window.
 * @param flag Display flag value.
 * @param active Nonzero to activate the grid.
 */
void skill_set_status_skill_visibility(SkillStatusSkillWindow* object, u32 flag, s32 active);

/**
 * @brief Display the selected skill's level, mastery, and remaining progress.
 * @param owner Character status window.
 * @param level Skill level, or -1 to hide.
 * @param mastery Stored mastery value, displayed minus one, or -1 to hide.
 * @param remaining Progress to the next level, or -1 to hide.
 */
void skill_refresh_mastery_display(SkillCharacterWindow* owner, s32 level, s32 mastery, s32 remaining);

/** @brief Append the character HP and MP gauge geometry. @param drawer Gauge packet drawer. */
void skill_build_hp_mp_gauge_packet(SkillHpMpGaugeDrawer* drawer);

#ifdef __cplusplus
}
#endif

#endif
