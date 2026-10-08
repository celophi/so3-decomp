#ifndef SO3_OVERLAYS_CITEMCREATION_TEXT_003684D0_H
#define SO3_OVERLAYS_CITEMCREATION_TEXT_003684D0_H

#include "types.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/development_line_target.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_001E1590.h"
class FieldClass15BB90;
#endif

struct FieldClass15AE70;
struct FieldRecordSelection;
struct FieldRuntimeValues;
struct InventorInformationWindow;

typedef FieldListNode ItemCreationListNode;

typedef FieldCountedList ItemCreationCountedList;

#ifdef __cplusplus
/** @brief Counted display list owning its sentinel and nodes. */
class ItemCreationClass187A60 : public ItemCreationCountedList
{
public:
    /** @brief Allocate the sentinel node and initialize the list count. */
    ItemCreationClass187A60();
    /** @brief Release the list nodes and sentinel. */
    virtual ~ItemCreationClass187A60();
};
#endif

/** Partial item creation state with inventor assignments, workshop selections and development lines. */
typedef struct ItemCreationSelectedDisplayState
#ifdef __cplusplus
    : public FieldClass153E30
#endif
{
#ifdef __cplusplus
    /** @brief Initialize the selected-display windows and resource state. */
    ItemCreationSelectedDisplayState();
    /** @brief Destroy the selection state and its Field base. */
    virtual ~ItemCreationSelectedDisplayState();
    /** @brief Report the selected-display object kind. @return Object kind 4. */
    virtual s32 func_001DF3D0();
    /** @brief Prepare record selection and count available option records. @return One on success, zero when required runtime data is missing. */
    virtual u8 func_00264110();
    /** @brief Store the associated state pointer. @param value Pointer to store. */
    virtual void func_00263C70(void* value);
    /** @brief Return the associated state pointer. @return Stored pointer. */
    virtual void* func_00261150();
    /** @brief Store the alternate associated object. @param value Object to store. */
    virtual void func_00263C80(void* value);
    /** @brief Read the alternate associated object. @return Stored object. */
    virtual void* func_00263C90();
    /** @brief Store the signed state byte. @param value State byte to store. */
    virtual void func_00263CA0(s8 value);
    /** @brief Read the signed state byte. @return Stored state byte. */
    virtual s8 func_00263CB0();
    /** @brief Read the selected-display state flag. @return Stored state flag. */
    virtual u8 func_00261D20();
    /** @brief Read the resource source word. @return Stored word. */
    virtual u32 func_00263CC0();
    /**
     * @brief Set a slot, consume an available category record, and reset its status bytes.
     * @param index Slot index from zero through two.
     * @param enabled Full-word state copied into the slot byte and tested for zero.
     */
    void func_0036BF30(s32 index, bool enabled);
    /**
     * @brief Load the completed buffer into the Field runtime and finish setup.
     * @param buffer Completed buffer, or null.
     * @return Zero without a buffer, otherwise the setup result.
     */
    virtual s32 func_001E1820(void* buffer);
    /** @brief Allocate and attach the selected-display windows. @return One. */
    virtual s32 func_00263CD0();
#else
    u8 unk00[0x34];
#endif
    u32 unk34;
    /** @brief Readiness byte set after the entry screen setup. */
    u8 window_setup_ready;
    u8 unk39[3];
    /** @brief Cached Field resource buffer slots. */
    struct FieldBufferSlots* resource_buffer_slots;
    struct FieldRuntimeValues* unk40;
    /** @brief Phase used by the State update and exit paths. */
    u8 update_phase;
    /** @brief Manager argument selecting the entry screen set. */
    u8 entry_mode;
    /** @brief Requested window group copied after group handling. */
    u8 window_group_snapshot;
    /** @brief Window group requested by the menu, dialog and grid handlers. */
    u8 requested_window_group;
    /** @brief Field record selection used by inventor screens. */
    struct FieldRecordSelection* record_selection;
    /** @brief Pending window-group activation across the transition phases. */
    u8 window_group_change_pending;
    u8 workshop_id;
    /** Enabled workshop skills; the ninth appraisal entry is always enabled. */
    u8 workshop_skill_enabled[9];
    u8 line_count;
    u8 source_transfer_workshop_id;
    u8 destination_transfer_workshop_id;
    /** @brief Inventor option codes in the fourteen-slot available grid. */
    u8 available_inventor_option_codes[14];
    u8 assigned_inventor_option_codes[9];
    u8 source_transfer_inventor_option_codes[6];
    u8 destination_transfer_inventor_option_codes[6];
    u8 unk7d;
    u16 workshop_facility_masks[12];
    u8 unk96[2];
    /** @brief Background image window. */
    struct ItemCreationBackground* background;
    /** @brief Title and scrolling status-message banner. */
    struct ItemCreationStatusBanner* status_banner;
    /** @brief Main invention, expansion and transfer menu. */
    struct ItemCreationMainMenu* main_menu;
    struct WorkshopNameWindow* workshop_name_window;
    struct WorkshopFacilitiesWindow* workshop_facilities_window;
    struct WorkshopExpansionWindow* workshop_expansion_window;
    struct DevelopmentTeamsWindow* development_teams_window;
    struct ItemCreationControlHelp* control_help;
    struct AvailableInventorGrid* available_inventor_grid;
    struct AssignedInventorGrid* assigned_inventor_grid;
    struct InventorInformationWindow* inventor_information_window;
    struct CreationSkillWindow* creation_skill_window;
    struct InventionPolicyWindow* invention_policy_window;
    struct StartInventingDialog* start_inventing_dialog;
    struct PlanItemGroupWindow* plan_item_group_window;
    struct InventoryItemTypeList* inventory_item_type_list;
    struct ItemCreationClass186770* development_lines_window;
    struct ItemSubmissionDialog* item_submission_dialog;
    struct ItemDetailsWindow* item_details_window;
    struct DevelopmentControlPanel* development_control_panel;
    struct InventorStatusWindow* inventor_status_window;
    struct AbortDevelopmentDialog* abort_development_dialog;
    struct InadequateLineDialog* inadequate_line_dialog;
    struct InventorTransferWindow* inventor_transfer_window;
    struct SourceInventorStrip* source_inventor_strip;
    struct DestinationInventorStrip* destination_inventor_strip;
    struct WorkshopSelectionWindow* workshop_selection_window;
    struct WorkshopInventorStrip* workshop_inventor_strip;
    struct PendingInventorSummary* pending_inventor_summary;
    struct AssignInventorDialog* assign_inventor_dialog;
    /** @brief Workshop-capacity warning dialog. */
    struct WorkshopFullDialog* workshop_full_dialog;
    /** @brief Selected inventor's creation-skill talent display. */
    struct InventorTalentsWindow* inventor_talents_window;
    /** @brief Grid supplying inventor information during a refresh. */
    void* inventor_information_grid;
    /** @brief Grid containing the source slot of the pending inventor swap. */
    void* swap_source_grid;
    /** @brief Grid containing the destination slot of the pending inventor swap. */
    void* swap_destination_grid;
    /** @brief Source grid slot selected for the inventor swap; -1 when unset. */
    s16 swap_source_slot_index;
    /** @brief Destination grid slot selected for the inventor swap; -1 when unset. */
    s16 swap_destination_slot_index;
    /** @brief Selection stage for the two-slot inventor swap. */
    u8 inventor_swap_stage;
    /** @brief Selection stage for the workshop/inventor transfer. */
    u8 inventor_transfer_stage;
    /** @brief Source workshop selected for the pending transfer. */
    u8 pending_transfer_source_workshop_id;
    /** @brief Source inventor option code selected for the pending transfer. */
    u8 pending_transfer_source_inventor_option_code;
    /** @brief Destination workshop selected for the pending transfer. */
    u8 pending_transfer_destination_workshop_id;
    /** @brief Destination inventor option code selected for the pending transfer. */
    u8 pending_transfer_destination_inventor_option_code;
    u8 unk12e[2];
    u16 facility_mask;
    u8 unk132[2];
    struct ItemCreationWorkshopRecord* workshop;
    u32 unk138;
    /** @brief Offset advanced while positioning the resource window. */
    float resource_motion_offset;
    /** @brief Offset used to position the resource window. */
    float resource_placement_offset;
    /** @brief Radial distance used to position the resource window. */
    float resource_placement_radius;
    /** @brief Development enable bytes for the three lines. */
    u8 line_development_enabled[3];
    u8 unk14b;
    /** @brief Countdown for each line's target updates. */
    float line_target_update_countdowns[3];
    /** @brief Quality percentage displayed for each line. */
    float line_quality_percentages[3];
    /** @brief Interval used to reset each line's target update countdown. */
    float line_target_update_intervals[3];
    float unk170[3];
    /** @brief Width of each line's Time bar. */
    float line_time_meter_widths[3];
    /** @brief Cached target states for each line's three inventor slots. */
    u8 line_inventor_states[3][3];
    s8 unk191[3][3];
    /** @brief Enable development-line processing and the main development window's actions. */
    u8 development_processing_enabled;
    /** @brief Tally accumulated by scans of contracted inventors. */
    u8 contracted_inventor_tally;
    /** @brief Window used to display keyed resources. */
#ifdef __cplusplus
    FieldClass15BB90* resource_window;
#else
    struct FieldStatus14* resource_window;
#endif
    /** @brief Primary resource key awaiting display. */
    s32 pending_resource_key;
    /** @brief Optional secondary resource key awaiting display. */
    s32 pending_secondary_resource_key;
    /** @brief Pending release of the current resource window. */
    u8 resource_window_release_pending;
    u8 unk1a9[3];
    /** @brief Countdown used to schedule inventor resources. */
    u32 inventor_resource_countdown;
    /** @brief Line used by submission, abort, details and outcome dialogs; 0xFF when unset. */
    u8 dialog_line_index;
    /** @brief Lines excluded from further processing in the current run. */
    u8 line_stopped[3];
    /** @brief Development target for each workshop line, or null. */
#ifdef __cplusplus
    ItemCreationClass184EF0* line_targets[3];
#else
    struct FieldStateTargets* line_targets[3];
#endif
    u8 line_skill_ids[3];
    /** @brief Target mode per line: zero unset, one original invention, two/three use one/two items. */
    u8 line_plan_modes[3];
    u8 unk1c6[2];
    u32 line_fol_costs[3];
    s32 line_target_update_results[3];
    /** @brief Zero-based line selected for skill and invention-policy editing. */
    s8 selected_line_index;
    u8 unk1e1;
    /** @brief One-based inventory allocation-record IDs for each line; zero marks an unused slot. */
    s16 line_item_ids[3][2];
    u8 unk1ee[2];
    s32 unk1f0;
    /** @brief Countdown for periodic runtime-data updates. */
    s32 runtime_data_update_countdown;
    /** @brief First plan item ID saved for cancellation of item selection. */
    s16 saved_first_plan_item_id;
    /** @brief Second plan item ID saved for cancellation of item selection. */
    s16 saved_second_plan_item_id;
} ItemCreationSelectedDisplayState;

/** Two scalar coordinates, cleared when a selection pair is constructed. */
typedef struct ItemCreationFloatPair
{
    float unk00[2];
#ifdef __cplusplus
    /** @brief Clear the two coordinates. */
    ItemCreationFloatPair()
    {
        unk00[1] = 0.0f;
        unk00[0] = 0.0f;
    }
#endif
} ItemCreationFloatPair;

/** Partial selection state with twelve float pairs and a byte permutation. */
typedef struct ItemCreationSelection
{
#ifdef __cplusplus
    /** @brief Initialize the selection coordinates and enabled slots. */
    ItemCreationSelection();
#endif
    ItemCreationFloatPair workshop_map_positions[12];
    u8 workshop_selection_flags[12];
    /** Workshop ID used by the map selection. */
    u8 selected_workshop_id;
    /** Navigation index for each workshop map entry. */
    u8 workshop_navigation_indices[12];
    u8 unk79;
#ifdef __cplusplus
    /** @brief Destroy the selection state. */
    virtual ~ItemCreationSelection()
    {
    }
    /**
     * @brief Refresh the enabled selection slots.
     * @return Always one.
     */
    virtual s32 func_slot0c();
    /** @brief Initialize the float pairs and selection order. */
    virtual void func_slot10();
#else
    void* unk7c;
#endif
} ItemCreationSelection;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Select or cancel an inventor slot, swapping inventor codes after the second selection.
 * @param object Selection state.
 * @param grid Assigned or available inventor grid.
 * @param slot_index Grid slot; -1 cancels the pending selection.
 */
void item_creation_select_inventor_for_swap(ItemCreationSelectedDisplayState* object, void* grid, s16 slot_index);

/**
 * @brief Rebuild the creation target for one three-inventor development line.
 * @param object Selection state.
 * @param line_index Development-line index from zero through two.
 */
void item_creation_rebuild_line_target(ItemCreationSelectedDisplayState* object, u8 line_index);

/**
 * @brief Allocate a node and append its value to the sentinel-based list.
 * @param object List containing a valid sentinel node.
 * @param value Value to append; may be null.
 */
void func_0036F270(ItemCreationCountedList* object, void* value);

/** @brief Release every data node while retaining the list sentinel. @param object List to clear. */
void func_0036EEF0(ItemCreationCountedList* object);

/**
 * @brief Restore installed workshop skills and enable appraisal.
 * @param object Selection state with an optional saved workshop.
 */
void item_creation_restore_workshop_skill_flags(ItemCreationSelectedDisplayState* object);

/**
 * @brief Restore saved workshop teams and rebuild the available-inventor list.
 * @param object Selection state containing the current workshop and inventor assignments.
 */
void item_creation_restore_workshop_assignments(ItemCreationSelectedDisplayState* object);

/**
 * @brief Save the three-inventor teams and creation skills for the current workshop.
 * @param object Selection state containing the current workshop and its teams.
 */
void item_creation_save_workshop_lines(ItemCreationSelectedDisplayState* object);

/**
 * @brief Save workshop lines and append the selection state to the resident queue.
 * @param object Selection state to save and enqueue.
 */
void item_creation_save_and_enqueue_selection(ItemCreationSelectedDisplayState* object);

/**
 * @brief Refresh inventor information from a slot in the assigned or available grid.
 * @param object Selection state.
 * @param grid Grid supplying the inventor code; another nonnull grid clears the inventor.
 * @param slot_index Slot in the supplied grid.
 */
void item_creation_show_inventor_information(ItemCreationSelectedDisplayState* object, void* grid, s16 slot_index);

/**
 * @brief Refresh workshop skill and line colors, or one transfer inventor strip.
 * @param object Selection state.
 * @param refresh_mode One refreshes workshop/team labels; six refreshes source inventors; seven refreshes destination inventors.
 */
void item_creation_refresh_team_and_transfer_windows(ItemCreationSelectedDisplayState* object, u8 refresh_mode);

/**
 * @brief Advance or cancel the workshop/inventor selection steps of an inventor transfer.
 * @param object Selection state.
 * @param selection_value Workshop ID or inventor option code for the current step; -1 cancels it.
 */
void item_creation_advance_inventor_transfer(ItemCreationSelectedDisplayState* object, s32 selection_value);

/**
 * @brief Enable or disable the inventor transfer windows and restore the selected workshop.
 * @param object State owning the transfer window and source/destination inventor strips.
 * @param enabled Full-word control flag; nonzero refreshes the workshop selections and inventor strips.
 */
void func_0036B1E0(ItemCreationSelectedDisplayState* object, u32 enabled);

/**
 * @brief Activate an item-creation window group after clearing pending inventor resources.
 *
 * Group zero shows the main menu, one selects team members, two shows inventing,
 * and three transfers inventors. Group four and other values leave visibility unchanged.
 * All groups clear pending inventor resources.
 * Activated groups restore their active receiver when one is available.
 *
 * @param object State owning the window groups and pending inventor resources.
 * @param group Window group to activate.
 */
void item_creation_activate_window_group(ItemCreationSelectedDisplayState* object, u8 group);
/** @brief Enable or disable one option window group. @param object Selection state. @param enabled Full-word control flag. */
void func_0036B360(ItemCreationSelectedDisplayState* object, u32 enabled);
/**
 * @brief Enable or disable inventor team selection and reset its subsidiary windows.
 * @param object State owning the assigned/available inventor grids and their detail windows.
 * @param enabled Full-word control flag; nonzero refreshes the inventor grids and team-selection prompt.
 */
void func_0036B6E0(ItemCreationSelectedDisplayState* object, u32 enabled);
/**
 * @brief Enable or disable the main menu and workshop summary windows.
 * @param object State owning the main menu, facilities, workshop name and development-team summary.
 * @param enabled Full-word control flag; nonzero selects the main menu as active receiver when present and restores its status prompt.
 */
void func_0036BA10(ItemCreationSelectedDisplayState* object, u32 enabled);

/**
 * @brief Read the specialty message key for an inventor option code.
 * @param object Unused receiver.
 * @param inventor_option_code Inventor ID plus 31, or an unmapped byte.
 * @return The NPC specialty key from 0x3458 through 0x345E, or 0x3457 for party or unmapped codes.
 */
u16 item_creation_inventor_skill_message(void* object, u8 inventor_option_code);

/**
 * @brief Read the creation-skill capability mask for an inventor option code.
 * @param object Unused receiver.
 * @param inventor_option_code Inventor ID plus 31, or an unmapped byte.
 * @return One specialty bit for NPC codes, 0x1FF for party codes, or zero when unmapped.
 */
u16 item_creation_inventor_skill_mask(void* object, u8 inventor_option_code);

/**
 * @brief Enable selection slots from resident section-four flags.
 * @param object Selection state whose mode may disable slots six through twelve.
 */
void func_00369510(ItemCreationSelection* object);

/**
 * @brief Move through the circular selection order until an enabled slot is reached.
 * @param object Selection state containing a valid current slot and at least one enabled slot.
 * @param direction Values one and four move backward; values two and three move forward.
 * @return One-based index of the selected slot.
 */
u8 func_003696B0(ItemCreationSelection* object, u16 direction);

/**
 * @brief Copy the first five workshops' saved facility masks into the selection state.
 * @param object Selection state; its other seven workshop masks are left unchanged.
 */
void func_00369EB0(ItemCreationSelectedDisplayState* object);

/**
 * @brief Rebuild a transfer strip from the NPC inventors placed in the selected workshop.
 * @param object Selection state.
 * @param workshop_id Workshop ID from one through eleven; other values leave state unchanged.
 * @param transfer_list One selects the source strip and two the destination strip.
 */
void item_creation_build_transfer_inventor_list(ItemCreationSelectedDisplayState* object, u16 workshop_id, u8 transfer_list);

/**
 * @brief Read the workshop ID corresponding to the current area.
 * @param object Unused receiver.
 * @return Workshop ID from one through twelve, or zero outside a workshop area.
 */
u8 item_creation_current_workshop_id(ItemCreationSelectedDisplayState* object);

/**
 * @brief Read the workshop name message corresponding to the current area.
 * @param object Unused receiver.
 * @return Message key from 0x3521 through 0x352C, or the 0x3520 error label.
 */
u32 item_creation_current_workshop_name_key(void* object);

/**
 * @brief Return the fixed value -1.
 * @param object Receiver or first argument; unused.
 * @return Always -1.
 */
s32 func_0036CD60(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_0036E540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E790(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E7A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036EC30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036EC50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036EC60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036EC70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036ECA0(void* object);

/**
 * @brief Return zero.
 * @param object Object argument; unused.
 * @return Returned value.
 */
float func_0036E7B0(void* object);

/**
 * @brief Append a value to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param value Value stored in the appended node.
 */
void func_0036F1A0(ItemCreationCountedList* object, void* value);

/**
 * @brief Append a value to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param value Value stored in the appended node.
 */
void func_0036F040(ItemCreationCountedList* object, void* value);

/**
 * @brief Append a value to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param value Value stored in the appended node.
 */
void func_0036EFB0(ItemCreationCountedList* object, void* value);

/**
 * @brief Append a record pointer to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param record Record pointer stored in the appended node.
 */
void func_0036EDB0(ItemCreationCountedList* object, void* record);

/**
 * @brief Insert a record pointer after a node, or append it when no node is supplied.
 * @param object List containing the sentinel and stored count.
 * @param after Node to insert after, or null to append.
 * @param record Pointer to the record pointer copied into the new node.
 */
void func_0036EE40(ItemCreationCountedList* object, ItemCreationListNode* after, void* const* record);

/**
 * @brief Follow the linked nodes at offset 4 up to the requested index.
 * @param object Object holding the first node pointer.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends early.
 */
ItemCreationListNode* func_0036EF70(ItemCreationCountedList* object, s32 index);

/**
 * @brief Append a value to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param value Value stored in the appended node.
 */
void func_0036F0D0(ItemCreationCountedList* object, void* value);

/**
 * @brief Follow the linked nodes at offset 4 up to the requested index.
 * @param object Object holding the first node pointer.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends early.
 */
ItemCreationListNode* func_0036F160(ItemCreationCountedList* object, s32 index);

/**
 * @brief Find a display node after the list sentinel.
 * @param object Counted display list with an initialized sentinel.
 * @param index Zero-based node index; negative values also select the first node.
 * @return Reached node, or null if the chain ends early.
 */
ItemCreationListNode* func_0036F230(FieldCountedList* object, s32 index);

/**
 * @brief Store and refresh one selected resource state.
 * @param object Owning selection state.
 * @param index Resource index.
 * @param value Full-word activation value, stored as a byte.
 */
void func_0036C080(ItemCreationSelectedDisplayState* object, s32 index, u32 value);

/**
 * @brief Choose an eligible assigned inventor and schedule the corresponding display resources.
 * @param object Selection state containing development lines and assigned inventor codes.
 */
void item_creation_schedule_inventor_resource(ItemCreationSelectedDisplayState* object);

#ifdef __cplusplus
}
#endif

#endif
