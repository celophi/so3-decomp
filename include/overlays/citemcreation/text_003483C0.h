#ifndef SO3_OVERLAYS_CITEMCREATION_TEXT_003483C0_H
#define SO3_OVERLAYS_CITEMCREATION_TEXT_003483C0_H

#include "types.h"
#include "overlays/citemcreation/text_003684D0.h"

#ifdef __cplusplus
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/1067-00/text_002D5260.h"
#endif

/** Partial nested object with a flag byte. */
typedef struct ItemCreationFlagNode
{
    u8 unk00[0x3F];
    u8 unk3f;
} ItemCreationFlagNode;

#ifdef __cplusplus
class AbortDevelopmentDialog;
class ItemSubmissionDialog;
#else
struct AbortDevelopmentDialog;
#endif
/** Resource window with native primary vtable at 0x186770 and extent 0x1C4. */
typedef struct ItemCreationClass186770
#ifdef __cplusplus
    : public FieldClass15AE70
#endif
{
#ifdef __cplusplus
    /** @brief Initialize the resource window and its owned arrays. */
    ItemCreationClass186770();
    /** @brief Destroy the resource window and its Field base. */
    virtual ~ItemCreationClass186770();
    /** @brief Open the selected resource group. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Reopen the associated window. @return Action status. */
    virtual s32 func_slotb4();
    /** @brief Reopen the option window. @return Action status. */
    virtual s32 func_slotb8();
    /** @brief Refresh the active resource window. */
    virtual void func_slot5c();
    /** @brief Move the resource column in direction zero. */
    virtual void func_slot68();
    /** @brief Move the resource column in direction one. */
    virtual void func_slot6c();
    /** @brief Create the resource grid and displays. @param associated Associated window. @return Initialization status. */
    virtual s32 func_slotf4(void* associated);
#else
    u8 unk00[0xA8];
#endif
    ItemCreationSelectedDisplayState* unka8;
    struct FieldClass15B200* unkac[12];
    struct FieldResourceDisplay2D5CF0* unkdc[9];
    u8 unk100[9];
    s8 unk109;
    u8 unk10a[2];
    struct FieldObject23CEA0* unk10c;
    struct ItemSubmissionDialog* unk110;
    struct ItemDetailsWindow* unk114;
    struct InadequateLineDialog* unk118;
    struct FieldClass15B200* unk11c[3];
    struct FieldClass15B200* unk128[3];
    struct LibObject178750* unk134[3];
    struct LibObject178750* unk140[3];
    struct LibObject178750* unk14c[3];
    struct LibObject178750* unk158[3];
    struct LibObject174F20* unk164[3];
    u8 unk170[4];
    struct ItemCreationOptionResourceDisplay* unk174[12];
    u8 unk1a4[0x18];
    u8 unk1bc;
    struct AbortDevelopmentDialog* unk1c0;
} ItemCreationNineResourceView;

/** Partial owner of twelve nested flag objects. */
typedef struct ItemCreationFlagGroups
{
    u8 unk00[0x174];
    ItemCreationFlagNode* unk174[12];
} ItemCreationFlagGroups;

#ifdef __cplusplus
class InventorTransferWindow;
#else
typedef struct InventorTransferWindow InventorTransferWindow;
#endif

#ifdef __cplusplus
/** @brief Workshop-map window base with twelve selectable workshop positions. */
class ItemCreationClass185A60 : public FieldClass15AE70
{
public:
    /** @brief Initialize the selection and display pointers. */
    ItemCreationClass185A60()
    {
        unka8 = 0;
        for (s32 index = 0; index < 12; index++)
        {
            unkac[index] = 0;
        }
        unk15c = 0;
        unkdc.func_slot0c();
    }
    /** @brief Destroy the selection state and window base. */
    virtual ~ItemCreationClass185A60()
    {
    }
    /** @brief Apply the current selection. @return Selection result code. */
    virtual s32 func_slotb0();
    /** @brief Reset the current selection. @return Selection result code. */
    virtual s32 func_slotb4();
    virtual s32 func_slotb8();
    virtual s32 func_slotbc();
    virtual s32 func_slotc0();
    virtual s32 func_slotc4();
    virtual s32 func_slotc8();
    virtual s32 func_slotcc();
    virtual s32 func_slotd0();
    virtual s32 func_slotd4();
    virtual s32 func_slotd8();
    virtual s32 func_slotdc();
    virtual void func_slote0();
    virtual void func_slote4();
    virtual u8 func_slote8();
    virtual void func_slotec(u8 value);
    virtual void func_slotf0();
    virtual s32 func_slotf4(void* associated);
    virtual void func_slotf8(u16 direction);
    ItemCreationSelectedDisplayState* unka8;
    void* unkac[12];
    ItemCreationSelection unkdc;
    LibClass175030* unk15c;
    /**
     * @brief Create and attach the selection transfer display.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @return Whether the display was created.
     */
    s32 create_selection_display_status(float x, float y);
};

/** @brief Base window for a six-inventor transfer strip. */
class TransferInventorStrip : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    TransferInventorStrip()
    {
        unkc4 = 0;
        unka8 = 0;
        unka9 = 0;
        for (s32 i = 0; i < 6; i++)
        {
            unkac[i] = 0;
        }
        unkcc = 0;
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~TransferInventorStrip()
    {
    }
    /**
     * @brief Select the active view and apply its selected option.
     * @return Always one.
     */
    virtual s32 func_slotb0();
    /** @brief Transfer the selected inventor into its workshop strip and refresh the markers. */
    virtual void func_slot5c();
    /**
     * @brief Clear the selected option and restore the active view.
     * @return Always two.
     */
    virtual s32 func_slotb4();
    virtual s32 func_slotb8();
    virtual s32 func_slotbc();
    virtual s32 func_slotc0();
    virtual s32 func_slotc4();
    virtual s32 func_slotc8();
    virtual s32 func_slotcc();
    virtual s32 func_slotd0();
    virtual s32 func_slotd4();
    virtual s32 func_slotd8();
    virtual s32 func_slotdc();
    virtual void func_slote0();
    virtual void func_slote4();
    virtual u8 func_slote8();
    virtual void func_slotec(u8 value);
    virtual void func_slotf0();
    virtual s32 func_slotf4(void* associated);
    /**
     * @brief Dispatch a grid direction and refresh the selected option markers.
     * @param direction Direction code.
     */
    virtual void func_slotf8(s32 direction);
    /** @brief Forward direction 2 to the window. */
    virtual void func_slot74();
    /** @brief Forward direction 3 to the window. */
    virtual void func_slot70();
    u8 unka8;
    u8 unka9;
    u8 unkaa[2];
    struct ItemCreationOptionResourceDisplay* unkac[6];
    ItemCreationSelectedDisplayState* unkc4;
    struct FieldObject23CEA0* unkc8;
    InventorTransferWindow* unkcc;
};

/** @brief Destination inventor strip used during inventor transfer. */
class DestinationInventorStrip : public TransferInventorStrip
{
public:
    /** @brief Destroy the option window and its base. */
    virtual ~DestinationInventorStrip();
    /** @brief Apply the selected option and refresh its associated window. @return Always one. */
    virtual s32 func_slotb0();
    /** @brief Reset the option and restore its associated selection display. @return Always two. */
    virtual s32 func_slotb4();
    /**
     * @brief Set up the option window and recover its associated display.
     * @param associated Object associated with the window.
     * @return Zero when no option state is attached, or one after setup.
     */
    virtual s32 func_slotf4(void* associated);
    /**
     * @brief Dispatch a grid direction and refresh the selected option markers.
     * @param direction Direction code.
     */
    virtual void func_slotf8(s32 direction);
};

/** @brief Source inventor strip used during inventor transfer. */
class SourceInventorStrip : public TransferInventorStrip
{
public:
    /** @brief Destroy the option window and its base. */
    virtual ~SourceInventorStrip();
    /** @brief Apply the selected option and refresh its associated window. @return Always one. */
    virtual s32 func_slotb0();
    /** @brief Reset the option and restore its associated selection display. @return Always two. */
    virtual s32 func_slotb4();
    /**
     * @brief Set up the option window and recover its associated display.
     * @param associated Object associated with the window.
     * @return Zero when no option state is attached, or one after setup.
     */
    virtual s32 func_slotf4(void* associated);
    /**
     * @brief Dispatch a grid direction and refresh the selected option markers.
     * @param direction Direction code.
     */
    virtual void func_slotf8(s32 direction);
};

/** @brief Workshop selector showing installed facilities and assignment controls. */
class WorkshopSelectionWindow : public ItemCreationClass185A60
{
public:
    /** @brief Initialize the selection window and its display pointers. */
    WorkshopSelectionWindow();
    /** @brief Destroy the selection window through its base. */
    virtual ~WorkshopSelectionWindow();
    /** @brief Forward direction 2 to the window. */
    virtual void func_slot74();
    /** @brief Forward direction 4 to the window. */
    virtual void func_slot70();
    /** @brief Forward direction 3 to the window. */
    virtual void func_slot6c();
    /** @brief Forward direction 1 to the window. */
    virtual void func_slot68();
    /** @brief Confirm inventor assignment or show the workshop-full warning. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Activate the workshop inventor strip and its talent display. @return Always one. */
    virtual s32 func_slotbc();
    /** @brief Move the selection and refresh the associated detail windows. @param direction Direction code. */
    virtual void func_slotf8(u16 direction);
    /** @brief Create the workshop selector, facility labels and assignment controls. @param associated Associated resource slot. @return Creation status. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelection* workshop_selection;
    LibObject178750* workshop_name;
    LibObject178750* facility_labels[9];
    class ItemCreationClass174C40* register_button;
    class ItemCreationClass174C40* back_button;
    class ItemCreationClass174C40* view_button;
    LibObject178750* register_label;
    LibObject178750* back_label;
    LibObject178750* view_label;
    class WorkshopFullDialog* workshop_full_dialog;
};

/** @brief Inventor transfer window showing source and destination workshops. */
class InventorTransferWindow : public ItemCreationClass185A60
{
public:
    /**
     * @brief Apply the selected option and enable the corresponding option window.
     * @return Zero without a state, three for an unchanged alternate selection, or one otherwise.
     */
    virtual s32 func_slotb0();
    /**
     * @brief Reset the option transfer or return to the primary option window.
     * @return Zero without a selection state, or two otherwise.
     */
    virtual s32 func_slotb4();
    /** @brief Initialize the selection window and its display pointers. */
    InventorTransferWindow();
    /** @brief Destroy the selection window through its base. */
    virtual ~InventorTransferWindow();
    /** @brief Forward direction 2 to the window. */
    virtual void func_slot74();
    /** @brief Forward direction 4 to the window. */
    virtual void func_slot70();
    /** @brief Forward direction 3 to the window. */
    virtual void func_slot6c();
    /** @brief Forward direction 1 to the window. */
    virtual void func_slot68();
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelection* workshop_selection;
    ItemCreationSelectedDisplayState* selection_state;
    u8 unk168[4];
    LibClass175030* unk16c;
    u8 current_workshop_id;
    u8 unk171[3];
    LibObject178750* current_workshop_name;
    u8 source_workshop_id;
    u8 source_inventor_id;
    u8 unk17a[2];
    LibClass174EF0* source_workshop_name;
    LibClass174EF0* source_facility_labels[9];
    LibClass174EF0* source_inventor_widgets[3];
    u8 destination_workshop_id;
    u8 destination_inventor_id;
    u8 unk1b2[2];
    LibClass174EF0* destination_workshop_name;
    LibClass174EF0* destination_facility_labels[9];
    LibClass174EF0* destination_inventor_widgets[3];
};

/** @brief Warning dialog shown when a workshop has no room for another inventor. */
class WorkshopFullDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    WorkshopFullDialog()
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~WorkshopFullDialog();
    /** @brief Restore the parent after confirming. @return One. */
    virtual s32 func_slotb0();
    /** @brief Restore the parent after returning. @return Two. */
    virtual s32 func_slotb4();
    /** @brief Build the window displays. @param associated Associated source. @return One. */
    virtual s32 func_slotf4(void* associated);
};

/** @brief Confirmation dialog for assigning an inventor to a workshop. */
class AssignInventorDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    AssignInventorDialog() : unka8(0), unkac(0), unkb0(0), unkb4(0), unkb8(0), unkbc(0), unkc0(0), unkc4(0), unkc5(0)
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~AssignInventorDialog();
    /** @brief Restore the associated window. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Apply the current option. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Create the option displays. @param associated Text source. @return Setup status. */
    virtual s32 func_slotf4(void* associated);
    /** @brief Move the selection in direction three. */
    virtual void func_slot70();
    /** @brief Move the selection in direction two. */
    virtual void func_slot74();
    FieldObject23CEA0* unka8;
    ItemCreationOptionResourceDisplay* unkac;
    LibObject178750* unkb0;
    LibObject178750* unkb4;
    LibObject178750* unkb8;
    LibObject178750* unkbc;
    LibObject178750* unkc0;
    u8 unkc4;
    u8 unkc5;
    u8 unkc6[2];
};

/** @brief Summary of the unassigned inventor pending workshop assignment. */
class PendingInventorSummary : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    PendingInventorSummary() : unka8(0), unkac(0), unkb0(0), unkb4(0), unkb8(0), unkbc(0), unkc0(0)
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~PendingInventorSummary();
    /** @brief Build the selected detail displays. @param associated Text source. @return One. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    u32 unkac;
    LibObject178750* unkb0;
    LibObject178750* unkb4;
    u8 unkb8;
    u8 unkb9[3];
    LibObject178750* unkbc;
    LibObject174F20* unkc0;
};

/** @brief Selectable portrait strip for a workshop's assigned NPC inventors. */
class WorkshopInventorStrip : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    WorkshopInventorStrip()
    {
        for (s32 i = 0; i < 6; i++)
        {
            inventor_portraits[i] = 0;
            portrait_indices[i] = 0;
            inventor_ids[i] = 0;
        }
        selection_state = 0;
        inventor_grid = 0;
        inventor_count = 0;
        workshop_id = 0;
        selected_inventor_index = -1;
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~WorkshopInventorStrip();
    /** @brief Move the grid in direction two and refresh the alternate display. */
    virtual void func_slot74();
    /** @brief Move the grid in direction three and refresh the alternate display. */
    virtual void func_slot70();
    /** @brief Perform the default action. @return Always zero. */
    virtual s32 func_slotb0();
    /** @brief Return to the associated window. @return Zero without an associated window, or one after restoring it. */
    virtual s32 func_slotb4();
    /** @brief Create the row displays and selection grid. @param associated Text source. @return Setup status. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* selection_state;
    ItemCreationOptionResourceDisplay* inventor_portraits[6];
    FieldObject23CEA0* inventor_grid;
    u8 inventor_count;
    u8 workshop_id;
    s16 selected_inventor_index;
    u8 portrait_indices[6];
    u8 inventor_ids[6];
};

/** @brief Inventor name and eight creation-skill talent displays. */
class InventorTalentsWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    InventorTalentsWindow() : selection_state(0), inventor_name(0)
    {
        for (s32 i = 0; i < 9; i++)
        {
            skill_labels[i] = 0;
            skill_values[i] = 0;
        }
        selected_inventor_id = 0;
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~InventorTalentsWindow();
    /** @brief Create the inventor title, skill labels and numeric talent displays. @param associated Text source. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* selection_state;
    LibObject178750* inventor_name;
    LibObject178750* skill_labels[9];
    LibObject174F20* skill_values[9];
    u8 selected_inventor_id;
    u8 unkf9[3];
};

/** @brief Warning dialog for an inadequate development line. */
class InadequateLineDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the window and attach its State. @param state Owning selection State. */
    InadequateLineDialog(ItemCreationSelectedDisplayState* state) : unka8(0)
    {
        unka8 = state;
        unkac = 0;

        unkb0 = 0;
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~InadequateLineDialog();
    /** @brief Create the window controls. @param associated Associated source. @return Setup status. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    u8 unkac;
    u8 unkad[3];
    LibObject178750* unkb0;
};

/** @brief Warning dialog for insufficient Fol to begin development. */
class InsufficientFolDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the Field window base. */
    InsufficientFolDialog()
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~InsufficientFolDialog();
    /** @brief Return to the associated window. @return Always one. */
    virtual s32 func_slotb0();
    /** @brief Handle the alternate action. @return Action status. */
    virtual s32 func_slotb4();
    /** @brief Create and attach the window display. @param associated Associated object. @return Always one. */
    virtual s32 func_slotf4(void* associated);
};

/** @brief Completion dialog shown after all development lines have finished. */
class DevelopmentCompleteDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the Field window base. */
    DevelopmentCompleteDialog()
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~DevelopmentCompleteDialog();
    /** @brief Handle the window action. @return Handler status. */
    virtual s32 func_slotb0();
    /** @brief Run the default alternate action. @return Always zero. */
    virtual s32 func_slotb4();
    virtual s32 func_slotb8();
    virtual s32 func_slotbc();
    virtual s32 func_slotc0();
    virtual s32 func_slotc4();
    virtual s32 func_slotc8();
    virtual s32 func_slotcc();
    virtual s32 func_slotd0();
    virtual s32 func_slotd4();
    virtual s32 func_slotd8();
    virtual s32 func_slotdc();
    virtual void func_slote0();
    virtual void func_slote4();
    virtual u8 func_slote8();
    virtual void func_slotec(u8 value);
    virtual void func_slotf0();
    /**
     * @brief Create and attach the window display.
     * @param associated Object associated with the window.
     * @return Setup status.
     */
    virtual s32 func_slotf4(void* associated);
};

struct LibObject172410;
struct LibObject174F20;
struct LibObject172440;
class ItemCreationClass172870;

/** @brief Item detail window showing its name, description, quantity and factors. */
class ItemDetailsWindow : public FieldClass15AE70
{
public:
    /** @brief Release the container and base window contents. */
    virtual void func_slot0c();
    /** @brief Initialize the window and keep its selection state. @param object Selection state. */
    ItemDetailsWindow(ItemCreationSelectedDisplayState* object);
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemDetailsWindow();
    /** @brief Handle the window action. @return Handler status. */
    virtual s32 func_slotb0();
    /** @brief Run the default alternate action. @return Always zero. */
    virtual s32 func_slotb4();
    virtual s32 func_slotb8();
    virtual s32 func_slotbc();
    virtual s32 func_slotc0();
    virtual s32 func_slotc4();
    virtual s32 func_slotc8();
    virtual s32 func_slotcc();
    virtual s32 func_slotd0();
    virtual s32 func_slotd4();
    virtual s32 func_slotd8();
    virtual s32 func_slotdc();
    virtual void func_slote0();
    virtual void func_slote4();
    virtual u8 func_slote8();
    virtual void func_slotec(u8 value);
    virtual void func_slotf0();
    /**
     * @brief Create and attach the window display.
     * @param associated Object associated with the window.
     * @return Setup status.
     */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    LibObject178750* unkac;
    LibObject172410* unkb0;
    LibObject174F20* unkb4;
    ItemCreationClass172870* unkb8;
    LibObject178750* unkbc;
    LibObject178750* unkc0;
    LibObject172440* unkc4[8];
    LibObject178750* unke4;
    LibObject178660* unke8;
    u8 unkec;
    u8 unked;
    u16 unkee;
    u16 unkf0;
    u8 unkf2[2];
    u32 unkf4;
    LibClass178630* unkf8;
};

/** @brief Failure dialog for a line that created no items. */
class LineFailureDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the window through its Field base. */
    LineFailureDialog()
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~LineFailureDialog();
    /** @brief Handle the window action. @return Handler status. */
    virtual s32 func_slotb0();
    /** @brief Run the default alternate action. @return Always zero. */
    virtual s32 func_slotb4();
    virtual s32 func_slotb8();
    virtual s32 func_slotbc();
    virtual s32 func_slotc0();
    virtual s32 func_slotc4();
    virtual s32 func_slotc8();
    virtual s32 func_slotcc();
    virtual s32 func_slotd0();
    virtual s32 func_slotd4();
    virtual s32 func_slotd8();
    virtual s32 func_slotdc();
    virtual void func_slote0();
    virtual void func_slote4();
    virtual u8 func_slote8();
    virtual void func_slotec(u8 value);
    virtual void func_slotf0();
    /**
     * @brief Create and attach the window display.
     * @param associated Object associated with the window.
     * @return Setup status.
     */
    virtual s32 func_slotf4(void* associated);
    LibObject178750* unka8;
};

/** @brief Success dialog for an invented item. */
class InventionSuccessDialog : public FieldClass15AE70
{
public:
    /** @brief Destroy the window through its Field base. */
    virtual ~InventionSuccessDialog();
    /** @brief Handle the window action. @return Handler status. */
    virtual s32 func_slotb0();
    /** @brief Run the default alternate action. @return Always zero. */
    virtual s32 func_slotb4();
    virtual s32 func_slotb8();
    virtual s32 func_slotbc();
    virtual s32 func_slotc0();
    virtual s32 func_slotc4();
    virtual s32 func_slotc8();
    virtual s32 func_slotcc();
    virtual s32 func_slotd0();
    virtual s32 func_slotd4();
    virtual s32 func_slotd8();
    virtual s32 func_slotdc();
    virtual void func_slote0();
    virtual void func_slote4();
    virtual u8 func_slote8();
    virtual void func_slotec(u8 value);
    virtual void func_slotf0();
    /**
     * @brief Create and attach the window display.
     * @param associated Object associated with the window.
     * @return Setup status.
     */
    virtual s32 func_slotf4(void* associated);
    LibObject178750* unka8;
};

/** @brief Framed background panel for the development controls. */
class DevelopmentControlPanel : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    DevelopmentControlPanel() : unka8(0)
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~DevelopmentControlPanel();
    /** @brief Create the action panel and frames. @param associated Associated object. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    void* unka8;
};

/** @brief Development-abort confirmation with all-line and current-line choices. */
class AbortDevelopmentDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    AbortDevelopmentDialog() : unka8(0), unkac(0), unkb0(0)
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~AbortDevelopmentDialog();
    /** @brief Move backward through the dialog choices and refresh their colors and target. */
    virtual void func_slot68();
    /** @brief Advance the dialog choices and refresh their colors and target. */
    virtual void func_slot6c();
    /** @brief Apply the selected result action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Restore the third row and associated resource window. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the result action displays. @param associated Text source. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    FieldClass153130* unkac;
    FieldClass153170* unkb0;
};

class InventorStatusList;

/** @brief Inventor status window showing contract, skill and work state. */
class InventorStatusWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    InventorStatusWindow()
    {
        unka8 = 0;
        unkac = 0;
        unkb0 = 0;
        unkb4 = 0;
        unkb8 = 0;
        unkbc = 0;
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~InventorStatusWindow();
    /** @brief Update the option window and its active container. */
    virtual void func_slot5c();
    /** @brief Create the option window widgets. @param associated Associated source. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    u32 unkac;
    u32 unkb0;
    u32 unkb4;
    InventorStatusList* unkb8;
    u8 unkbc;
    u8 unkbd[0x1F];
};

/** @brief Confirmation dialog for requesting item submission. */
class ItemSubmissionDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    ItemSubmissionDialog() : unka8(0), unkac(0)
    {
    }
    /** @brief Destroy the window through its Field base. */
    virtual ~ItemSubmissionDialog();
    /** @brief Move backward through the dialog choices and refresh their colors and target. */
    virtual void func_slot68();
    /** @brief Advance the dialog choices and refresh their colors and target. */
    virtual void func_slot6c();
    /** @brief Apply the selected action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated resource window. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the option displays. @param associated Associated source. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    FieldClass153130* unkac;
    FieldClass153170* unkb0;
    LibObject178750* unkb4;
};

class LibClass1721F0;

/** @brief Base storage for an inventor status row. */
class ItemCreationClass185030
{
public:
    /** @brief Destroy the option row interface. */
    virtual ~ItemCreationClass185030()
    {
    }
    /** @brief Update the row flag. @param source Row owner. @param value Current flag. */
    virtual void func_slot0c(LibClass1721F0* source, u8 value) = 0;
    /** @brief Update the row index. @param source Row owner. @param index Current index. */
    virtual void func_slot10(LibClass1721F0* source, s32 index) = 0;
    /** @brief Update the row position. @param source Row owner. @param x Horizontal setting. @param y Vertical setting. */
    virtual void func_slot14(LibClass1721F0* source, float x, float y) = 0;
    /** @brief Read the row float setting. @return Current setting. */
    virtual float func_slot18();
};

/** @brief Inventor status row showing name, contract, skill and work state. */
class InventorStatusRow : public ItemCreationClass185030
{
public:
    /** @brief Initialize the four text widgets. */
    InventorStatusRow()
    {
    }
    /** @brief Destroy the four text widgets and row interface. */
    virtual ~InventorStatusRow();
    /** @brief Update the row flag. @param source Row owner. @param value Current flag. */
    virtual void func_slot0c(LibClass1721F0* source, u8 value);
    /** @brief Update the row index. @param source Row owner. @param index Current index. */
    virtual void func_slot10(LibClass1721F0* source, s32 index);
    /** @brief Update the row position. @param source Row owner. @param x Horizontal setting. @param y Vertical setting. */
    virtual void func_slot14(LibClass1721F0* source, float x, float y);
    LibObject178750 unk04;
    LibObject178750 unk118;
    LibObject178750 unk22c;
    LibObject178750 unk340;
};

/** @brief Panel widget used by the item-creation windows. */
class ItemCreationClass184F30 : public LibClass178630
{
public:
    /** @brief Initialize the widget and select kind 2. */
    ItemCreationClass184F30();
    /** @brief Destroy the resident widget base. */
    virtual ~ItemCreationClass184F30();
};

/** @brief Child-widget aggregate embedded in the item-creation display container. */
class ItemCreationClass1723F0
{
public:
    ItemCreationClass184F30 unk00;
    ItemCreationClass1746A0 unk90;
    ItemCreationClass1746A0 unke4;
    ItemCreationClass1725D0 unk138;
    ItemCreationClass175030 unk190;
    ItemCreationClass172600 unk20c;
    ItemCreationClass172870 unk260;
    u8 unk2b8[0x64];
    /** @brief Initialize the seven embedded widgets. */
    ItemCreationClass1723F0()
    {
    }
    /** @brief Destroy the seven embedded widgets. */
    ~ItemCreationClass1723F0()
    {
    }
    /** @brief Handle the aggregate selection. @param index Selected index. */
    virtual void func_00412C10(s32 index);
    /** @brief Run the second aggregate state hook. */
    virtual void func_00412C20();
    /** @brief Read the aggregate value. @return Aggregate value. */
    virtual float func_00412C30();
    /** @brief Update the aggregate widgets and selection state. */
    virtual void func_00413020();
};

/** @brief Display container for item-creation child widgets. */
class ItemCreationClass184F60 : public LibObject178660, public ItemCreationClass1723F0
{
public:
    /** @brief Initialize the container and its widget aggregate. */
    ItemCreationClass184F60();
    /** @brief Destroy the widget aggregate and container. */
    virtual ~ItemCreationClass184F60();
};

/** @brief Warning dialog for missing modification materials. */
class MissingMaterialsDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the Field window base. */
    MissingMaterialsDialog()
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~MissingMaterialsDialog();
    /** @brief Handle the return action. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Handle the alternate action. @return Action status. */
    virtual s32 func_slotb4();
    /** @brief Set up the window. @param associated Associated object. @return Setup status. */
    virtual s32 func_slotf4(void* associated);
};

extern "C" {
#endif

/**
 * @brief Refresh the selected item's child window displays.
 * @param object Child window receiver.
 */
void func_00352DE0(struct ItemDetailsWindow* object);

/**
 * @brief Create the resource displays for the twelve-option selection grid.
 * @param object Window owning the selection and resource displays.
 * @return Always one.
 */
s32 func_0034FA70(struct ItemCreationClass185A60* object);

/**
 * @brief Select the result window's text resource for its mode.
 * @param object Result window.
 * @param mode Mode to store; zero through two select a resource.
 */
void func_003500D0(struct InadequateLineDialog* object, u8 mode);

/**
 * @brief Restore the associated window and dispatch the result state.
 * @param object Result window.
 * @return Always one.
 */
s32 func_0034FE00(struct InadequateLineDialog* object);

/**
 * @brief Restore the associated window and dispatch the result state.
 * @param object Result window.
 * @return Always one.
 */
s32 func_0034FF70(struct InadequateLineDialog* object);

/**
 * @brief Create and attach the result window's display widgets.
 * @param object Result window.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 func_003501B0(struct InadequateLineDialog* object, void* associated);

/**
 * @brief Refresh the nine resource displays and count their active entries.
 * @param object Owner of the selected resource values and displays.
 */
void func_00356160(ItemCreationNineResourceView* object);

/**
 * @brief Refresh the three assigned-item groups and their selector grid.
 * @param object Owner of the group displays and selected item values.
 */
void func_00356FD0(ItemCreationNineResourceView* object);

/**
 * @brief Hide a resource slot or refresh it from the selected item and mode.
 * @param object Resource window receiving the update.
 * @param index Selected resource slot.
 * @param mode Resource record selector.
 * @param active Zero hides the slot; a nonzero byte refreshes it.
 */
void func_003568F0(ItemCreationClass186770* object, u8 index, u8 mode, u8 active);

/**
 * @brief Set the option window mode and refresh its selection colors.
 * @param object Option window.
 * @param mode Zero resets the selection; one activates it.
 */
void func_00348B60(AssignInventorDialog* object, u16 mode);

/**
 * @brief Refresh the NPC inventors assigned to a workshop.
 * @param object Workshop inventor strip.
 * @param workshop_id Workshop ID stored as a byte; zero selects unassigned inventors.
 */
void func_00349DE0(WorkshopInventorStrip* object, u32 workshop_id);

/**
 * @brief Enable or disable inventor selection and refresh the talent display.
 * @param object Workshop inventor strip.
 * @param mode Zero resets the grid; one activates it.
 */
void func_0034A1E0(WorkshopInventorStrip* object, u16 mode);

/**
 * @brief Refresh the option detail displays for the current code.
 * @param object Option detail window.
 */
void func_0034B970(InventorTalentsWindow* object);

/**
 * @brief Switch the workshop control flags and move their workshop marker.
 * @param object Workshop selection window.
 * @param mode Zero or one selects the marker group; other values leave the state unchanged.
 */
void func_0034A670(WorkshopSelectionWindow* object, u8 mode);

/**
 * @brief Dim the facility labels, then brighten those available in the selected workshop.
 * @param object Workshop selection window.
 * @param selected Workshop from one through twelve; other values leave the displays dim.
 */
void func_0034A7A0(WorkshopSelectionWindow* object, u8 selected);

/**
 * @brief Rebuild and refresh the option list selected by the transfer state.
 * @param object Inventor transfer window.
 * @param option Option to display, or 0xFF to use the current selection.
 */
void func_0034D980(InventorTransferWindow* object, u8 option);

/**
 * @brief Move the transfer display and refresh its selected option markers and list.
 * @param object Owner of the selection and optional transfer display.
 * @param direction Direction used to advance the embedded selection.
 */
void func_0034E4D0(InventorTransferWindow* object, u16 direction);

/**
 * @brief Move the optional transfer display using the embedded selection.
 * @param object Owner of the selection and optional transfer display.
 * @param direction Direction used to advance the embedded selection.
 */
void func_0034F9B0(InventorTransferWindow* object, u16 direction);

/**
 * @brief Initialize the view display at its fixed coordinates and report success.
 * @param object View that owns the display.
 * @param associated Associated object forwarded to the field initializer.
 * @return Always one.
 */
s32 func_0034FD50(InventorTransferWindow* object, void* associated);

/**
 * @brief Refresh an option display from its current option list.
 * @param object Option display to refresh.
 */
void func_0034D340(TransferInventorStrip* object);

/**
 * @brief Refresh the option markers for the selected option.
 * @param object Inventor transfer window.
 * @param option Selected option byte.
 */
void func_0034DB00(InventorTransferWindow* object, u8 option);

/**
 * @brief Clear all twelve nested flags and enable the selected group of four.
 * @param object Owner of the optional nested objects.
 * @param group Group to enable, from zero through two; other values leave all flags clear.
 */
void func_00356780(ItemCreationFlagGroups* object, u16 group);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348510(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348520(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348580(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003485F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348610(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348620(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348630(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348640(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348650(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348660(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348670(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348680(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00350DE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00350DF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351C30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351C40(void* object);

/**
 * @brief Store the window control byte.
 * @param object Window base.
 * @param value Value to store.
 */
void func_00348400(FieldClass15AE70* object, u8 value);

/**
 * @brief Read the window control byte.
 * @param object Window base.
 * @return Control value.
 */
u8 func_00348410(const FieldClass15AE70* object);

/**
 * @brief Store the byte state code.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348420(struct FieldClass15AE70* object, u8 value);

/**
 * @brief Read the byte state code.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_00348430(struct FieldClass15AE70* object);

/**
 * @brief Store the halfword state flags.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348440(struct FieldClass15AE70* object, u16 value);

/**
 * @brief Read the halfword state flags.
 * @param object Object containing the field.
 * @return Field value.
 */
u16 func_00348450(struct FieldClass15AE70* object);

/**
 * @brief Store the alternate associated window pointer.
 * @param object Window base containing the pointer.
 * @param value Pointer to store.
 */
void func_00348480(struct FieldClass15AE70* object, void* value);

/**
 * @brief Read the alternate associated window pointer.
 * @param object Window base containing the pointer.
 * @return Associated window pointer.
 */
void* func_00348490(struct FieldClass15AE70* object);

/**
 * @brief Write the word at offset 0x4.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003484A0(void* object, u32 value);

/**
 * @brief Read the word at offset 0x4.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_003484B0(void* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_003484C0(void* object);

/**
 * @brief Read the byte at offset 0xD.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_003486B0(struct FieldClass15AE70* object);

/**
 * @brief Write the byte at offset 0xD.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003486C0(struct FieldClass15AE70* object, u8 value);

/**
 * @brief Return the selection state's associated pointer.
 * @param object Selection state.
 * @return Stored pointer.
 */
void* func_0034FF60(ItemCreationSelectedDisplayState* object);

/**
 * @brief Write the halfword at offset 0x6C.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003527C0(struct LibClass174610* object, u16 value);

/**
 * @brief Clear the flag byte in 24 nested objects.
 * @param object Object holding the nested pointers.
 */
void func_0034DA30(InventorTransferWindow* object);

#ifdef __cplusplus
}
#endif

#endif
