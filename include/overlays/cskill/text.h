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
typedef struct SkillDualSelection SkillDualSelection;
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
typedef struct SkillTextReceiver SkillTextReceiver;
typedef struct SkillCostWindow SkillCostWindow;
typedef struct SkillVector4 SkillVector4;
typedef struct SkillSecondarySelection SkillSecondarySelection;
typedef struct SkillFourRowSelection SkillFourRowSelection;
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
 * @brief Switch to the associated selection window for row modes four and five.
 * @param object Window containing the mode table and attached display.
 */
void func_003522C0(SkillTacticalWindow* object);

/**
 * @brief Rebuild the mode query's displayed selection state.
 * @param record Mode-query receiver.
 */
void func_00351BE0(SkillTacticalWindow* record);

/**
 * @brief Update owner and window messages for the selected six-row entry.
 * @param object Six-row window receiver.
 */
void func_00353720(void* object);

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

/** @brief Update the message for the current selection mode. @param object Window with paired selection grids. */
void func_00349E80(SkillDualSelection* object);
/** @brief Set the paired grid mode and update its display flags. @param object Window with paired grids. @param mode Signed mode code. */
void func_00349F30(SkillDualSelection* object, s16 mode);
/** @brief Refresh the first selection rows. @param object Window receiver. @param reset Nonzero to reset the grid position. */
void func_0034A2B0(SkillDualSelection* object, s32 reset);
/** @brief Refresh the second selection rows. @param object Window receiver. @param reset Nonzero to reset the grid position. */
void func_0034A130(SkillDualSelection* object, s32 reset);




/**
 * @brief Refresh the selected detail pointer and checksum-protected status values.
 * @param record Selection and status display storage.
 */
void func_00358200(SkillCharacterWindow* record);

/**
 * @brief Forward the current grid index to the active window's choice callback.
 * @param object Window with a grid selection.
 */
void func_0035CD50(SkillGridChoice* object);

/**
 * @brief Apply the current grid choice and report the callback status.
 * @param object Window with a grid selection.
 * @return One when the callback returns zero, or two otherwise.
 */
s32 func_0035CEB0(SkillGridChoice* object);

/**
 * @brief Hide the window lists, restore its associated selection, and queue its callback.
 * @param object Window base receiver.
 * @return Always two.
 */
s32 func_0035CE30(FieldClass15AE70* object);


















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
 * @param offset Vertical offset subtracted from both base positions.
 */
void func_0034C110(SkillModeSelection* record, float offset);

/**
 * @brief Update paired-list item visibility and colors for the current selection.
 * @param record Receiver containing paired lists and selection values.
 */
void func_0034BEE0(SkillModeSelection* record);

/**
 * @brief Refresh the selected item's display receiver and color.
 * @param record Receiver containing the item list and selection state.
 */
void func_0034C1F0(SkillModeSelection* record);

/** @brief Advance the mode window animation. @param object Mode window. */
void func_0034C060(SkillModeSelection* object);

/**
 * @brief Configure the second grid and register its newly allocated display object.
 * @param record Receiver containing the second grid and display owner.
 * @return One after setup, otherwise zero without the second grid.
 */
s32 func_0034B190(SkillDualSelection* record);

/**
 * @brief Configure the first grid and register its newly allocated display object.
 * @param record Receiver containing the first grid and display owner.
 * @return One after setup, otherwise zero without the first grid.
 */
s32 func_0034B2C0(SkillDualSelection* record);

/**
 * @brief Configure the selection grid position and register its display state.
 * @param record Receiver with the display owner and selection grid.
 * @param row_count Number of grid rows; zero leaves the grid unchanged.
 * @return One for zero rows or completed setup, otherwise zero without a display owner.
 */
s32 func_0034E260(SkillModeSelection* record, s16 row_count);

/** @brief Create the mode window's text and image rows. @param object Mode window. @return Nonzero after creating the rows. */
s32 func_00351090(SkillModeSelection* object);

/**
 * @brief Cycle the symbology character and refresh its name, MP, and condition markers.
 * @param object Character window.
 * @param forward Nonzero advances selection; zero moves it backward.
 * @return Zero without a selection, otherwise 4.
 */
s32 skill_cycle_symbology_character(SkillSymbologyCharacterWindow* object, s32 forward);

/** @brief Refresh party and condition markers for the selected symbology character. @param object Character window. */
void func_00363890(SkillSymbologyCharacterWindow* object);

/**
 * @brief Update the status bytes selected by a mode value.
 * @param object Receiver with pointers to status records.
 * @param mode Zero clears all seven records; a positive or negative value selects one of two records.
 */
void func_00349920(u8* object, s32 mode);

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
 * @brief Update six item fields and sum values other than -1.
 * @param owner Record containing the items and values.
 * @param mode Value stored in the first item's byte; zero clears the other item bytes.
 * @return Sum of the six values, with -1 treated as zero, or zero when mode is zero.
 */
s32 func_003534C0(SkillBattleSetupWindow* owner, s32 mode);

/**
 * @brief Set the six-row window's list flags and selection activity.
 * @param object Six-row selection window.
 * @param flag Full window flag, whose low byte controls each display.
 * @param active Nonzero to activate the selection grid.
 */
void func_00353570(SkillBattleSetupWindow* object, u32 flag, s32 active);

/** @brief Refresh the selected skill's costs and damage multiplier. @param object Skill cost window. */
void skill_refresh_costs(FieldClass15AE70* object);

/** @brief Set mode-window display and selection activity. @param object Mode window. @param flag Display flag word. @param active Grid activity value. */
void func_00351360(SkillModeSelection* object, u32 flag, s32 active);

/**
 * @brief Color the paired six-row lists and position the selected-row display.
 * @param record Record containing the lists, selection, and display receiver.
 */
void func_003538F0(SkillBattleSetupWindow* record);

/**
 * @brief Show the selected slot's icon and copy its record links to the owning controller.
 * @param object Window with the slot icons and record selection.
 */
void func_00358310(SkillCharacterWindow* object);

/** @brief Refresh the four-row window's record values. @param object Four-row selection window. */
void func_003559F0(SkillFourRowSelection* object);
/** @brief Rebuild the six-row status values. @param object Status-row window. @return One on success, or zero on failure. */
s32 func_00354190(SkillBattleSetupWindow* object);
/** @brief Rebuild the mode-query rows and description. @param object Mode-query window. */
void func_00352C00(SkillTacticalWindow* object);
/** @brief Rebuild the mode rows for a signed mode code. @param object Mode-selection window. @param mode Signed mode. @return One on success, or zero on failure. */
s32 func_00350890(SkillModeSelection* object, s16 mode);
/** @brief Create the second dual-grid display and row markers. @param object Dual-grid window. @return One after setup, or zero on failure. */
u8 func_0034B720(SkillDualSelection* object);

/** @brief Rebuild both paired selection grids. @param object Paired selection window. */
void func_0034B3F0(SkillDualSelection* object);

/**
 * @brief Set the four-row window's display flags and grid activity.
 * @param object Four-row selection window.
 * @param flag Display flag value.
 * @param active Nonzero to activate the grid.
 */
void func_003558B0(SkillFourRowSelection* object, u32 flag, s32 active);

/**
 * @brief Update four item values and status bytes.
 * @param owner Record containing the four item pointers.
 * @param first Value used by the first item and third-item selection.
 * @param second Value used by the second item.
 * @param third Value used by the third item.
 */
void func_003580D0(SkillCharacterWindow* owner, s32 first, s32 second, s32 third);


/**
 * @brief Apply the selected mode and notify its receiver.
 * @param record Selection and mode storage.
 */
void func_003522C0(SkillTacticalWindow* record);

/** @brief Append the character HP and MP gauge geometry. @param drawer Gauge packet drawer. */
void skill_build_hp_mp_gauge_packet(SkillHpMpGaugeDrawer* drawer);

#ifdef __cplusplus
}
#endif

#endif
