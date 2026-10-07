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

/** Partial option-code table through entry 59. */
typedef struct ItemCreationOptionTable
{
    u8 unk00[0x188];
    s32 unk188[60];
} ItemCreationOptionTable;

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
    /** @brief Return the associated state pointer. @return Stored pointer. */
    virtual void* func_00263CC0();
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
    void* unk34;
    u8 unk38;
    u8 unk39[3];
    struct FieldBufferSlots* unk3c;
    ItemCreationOptionTable* unk40;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    struct FieldRecordSelection* unk48;
    u8 unk4c;
    u8 workshop_id;
    /** Enabled workshop skills; the ninth appraisal entry is always enabled. */
    u8 workshop_skill_enabled[9];
    u8 unk57;
    u8 unk58;
    u8 unk59;
    u8 unk5a[14];
    u8 unk68[9];
    u8 unk71[6];
    u8 unk77[6];
    u8 unk7d;
    u16 workshop_facility_masks[12];
    u8 unk96[2];
    struct ItemCreationBackground* unk98;
    struct ItemCreationStatusBanner* unk9c;
    struct ItemCreationMainMenu* unka0;
    struct WorkshopNameWindow* unka4;
    struct WorkshopFacilitiesWindow* unka8;
    struct WorkshopExpansionWindow* unkac;
    struct DevelopmentTeamsWindow* unkb0;
    struct ItemCreationControlHelp* unkb4;
    struct AvailableInventorGrid* unkb8;
    struct AssignedInventorGrid* unkbc;
    struct InventorInformationWindow* unkc0;
    struct CreationSkillWindow* unkc4;
    struct InventionPolicyWindow* unkc8;
    struct StartInventingDialog* unkcc;
    struct PlanItemGroupWindow* unkd0;
    struct InventoryItemTypeList* unkd4;
    struct ItemCreationClass186770* unkd8;
    struct ItemSubmissionDialog* unkdc;
    struct ItemDetailsWindow* unke0;
    struct DevelopmentControlPanel* unke4;
    struct InventorStatusWindow* unke8;
    struct AbortDevelopmentDialog* unkec;
    struct InadequateLineDialog* unkf0;
    struct InventorTransferWindow* unkf4;
    struct SourceInventorStrip* unkf8;
    struct DestinationInventorStrip* unkfc;
    struct WorkshopSelectionWindow* unk100;
    struct WorkshopInventorStrip* unk104;
    struct PendingInventorSummary* unk108;
    struct AssignInventorDialog* unk10c;
    struct WorkshopFullDialog* unk110;
    struct InventorTalentsWindow* unk114;
    void* unk118;
    void* unk11c;
    void* unk120;
    s16 unk124;
    s16 unk126;
    u8 unk128;
    u8 unk129;
    u8 unk12a;
    u8 unk12b;
    u8 unk12c;
    u8 unk12d;
    u8 unk12e[2];
    u16 facility_mask;
    u8 unk132[2];
    struct ItemCreationWorkshopRecord* workshop;
    u32 unk138;
    u8 unk13c[4];
    float unk140;
    u8 unk144[4];
    u8 unk148[3];
    u8 unk14b;
    float unk14c[3];
    float unk158[3];
    float unk164[3];
    float unk170[3];
    float unk17c[3];
    u8 unk188[3][3];
    s8 unk191[3][3];
    u8 unk19a;
    u8 unk19b;
#ifdef __cplusplus
    FieldClass15BB90* unk19c;
#else
    struct FieldStatus14* unk19c;
#endif
    s32 unk1a0;
    s32 unk1a4;
    u8 unk1a8;
    u8 unk1a9[3];
    u32 unk1ac;
    u8 unk1b0;
    u8 unk1b1[3];
#ifdef __cplusplus
    ItemCreationClass184EF0* unk1b4[3];
#else
    struct FieldStateTargets* unk1b4[3];
#endif
    u8 unk1c0[3];
    u8 unk1c3[3];
    u8 unk1c6[2];
    u32 unk1c8[3];
    s32 unk1d4[3];
    s8 unk1e0;
    u8 unk1e1;
    s16 unk1e2[3][2];
    u8 unk1ee[2];
    s32 unk1f0;
    s32 unk1f4;
    s16 unk1f8;
    s16 unk1fa;
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
    ItemCreationFloatPair unk00[12];
    u8 unk60[12];
    u8 unk6c;
    u8 unk6d[12];
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
 * @param enabled Full-word control flag; nonzero restores main-menu focus and its status prompt.
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
