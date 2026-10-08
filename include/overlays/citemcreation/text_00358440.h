#ifndef SO3_OVERLAYS_CITEMCREATION_TEXT_00358440_H
#define SO3_OVERLAYS_CITEMCREATION_TEXT_00358440_H

#include "types.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/citemcreation/text_003684D0.h"
#ifdef __cplusplus
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002D5260.h"
#endif

typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;
struct ItemCreationAllocationRecord;
struct LibObject178660;
struct FieldObject23BE00;

typedef struct WorkshopExpansionWindow WorkshopExpansionWindow;

/** @brief Nine-inventor grid for the three development teams. */
typedef struct AssignedInventorGrid AssignedInventorGrid;

typedef struct AvailableInventorGrid AvailableInventorGrid;

#ifdef __cplusplus
/** @brief List of individual inventory items of a selected catalog type. */
class InventoryItemInstanceList : public FieldClass15AD40
{
public:
    /** @brief Clear the row displays and the list flag. */
    InventoryItemInstanceList()
    {
        for (s32 index = 0; index < 6; index++)
        {
            unk138[index] = 0;
        }
        unk1b0 = 0;
        FieldClass15AD40();
    }
    /** @brief Release the optional panel and destroy the Field list window. */
    virtual ~InventoryItemInstanceList();
    /** @brief Release the category container and base window contents. */
    virtual void func_slot0c();
    /** @brief Update the category rows and selected item preview. */
    virtual void func_slot5c();
    /** @brief Perform no work for the window hook at slot 0x68. */
    virtual void func_slot68();
    /** @brief Perform no work for the window hook at slot 0x6C. */
    virtual void func_slot6c();
    virtual s32 func_slotb0();
    /** @brief Restore the category display or its parent. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Toggle the selected item preview. @return Always zero. */
    virtual s32 func_slotb8();
    /**
     * @brief Create the category list and item preview displays.
     * @param associated Object associated with the window.
     * @return Always one.
     */
    virtual s32 func_slot104(void* associated);
    /**
     * @brief Set the paired display flags and update auxiliary displays.
     * @param value Low byte stored in each paired display flag.
     * @param alternate Auxiliary flag value; its full value selects the height.
     */
    virtual void func_slot10c(u32 value, u32 alternate);
    /** @brief Set the list flag. @param value Flag value to store. */
    virtual void func_slot110(u8 value);
    /** @brief Refresh the visible record rows. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the row displays. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    struct LibObject172410* unk138[6];
    struct ItemCreationOptionResourceDisplay* unk150[6];
    struct LibObject172440* unk168[8];
    struct ItemCreationClass172870* unk188;
    struct LibClass178630* unk18c;
    LibObject178750* unk190;
    LibObject178750* unk194;
    LibObject178750* unk198;
    u8 unk19c[4];
    LibObject178750* unk1a0;
    LibObject178750* unk1a4;
    struct LibObject172410* unk1a8;
    LibObject178660* unk1ac;
    u8 unk1b0;
    u8 unk1b1[3];
    ItemCreationSelectedDisplayState* unk1b4;
    s32 unk1b8;
    s32 unk1bc;
};

class FieldClass153130;
class FieldClass153170;

/** @brief Confirmation dialog for starting invention. */
class StartInventingDialog : public FieldClass15AE70
{
public:
    /** @brief Initialize the window and attach its State. @param state Owning selection State. */
    StartInventingDialog(ItemCreationSelectedDisplayState* state) : selection_state(0)
    {
        selection_state = state;
        unkb4 = 0;
        yes_label = 0;
        unkb0 = 0;
        unkbc[0] = 0;
        unkbc[1] = 0;
        unkbc[2] = 0;
    }
    /** Destroy the window through Field's window base. */
    virtual ~StartInventingDialog();
    /** @brief Move the selector backward and refresh its two display colors and target. */
    virtual void func_slot68();
    /** @brief Move the selector forward and refresh its two display colors and target. */
    virtual void func_slot6c();
    /** @brief Apply the selected values. @return Always one. */
    virtual s32 func_slotb0();
    /** @brief Restore the selection display. @return Always two. */
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
     * @brief Create and attach the selection window displays.
     * @param associated Object associated with the window.
     * @return Always one.
     */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* selection_state;
    LibObject178750* yes_label;
    LibObject178750* unkb0;
    FieldClass153130* unkb4;
    FieldClass153170* unkb8;
    bool unkbc[3];
};

struct LibObject175140;
struct ItemCreationOptionResourceDisplay;

/** @brief Inventor information window showing eight creation-skill talents. */
class InventorInformationWindow : public FieldClass15AE70
{
public:
    /** @brief Construct the detail window with its displays cleared. */
    InventorInformationWindow();
    /** @brief Destroy the window through Field's window base. */
    virtual ~InventorInformationWindow();
    virtual s32 func_slotb0();
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
     * @brief Create and attach the detail window displays.
     * @param associated Object associated with the window.
     * @return One when the displays are created; zero when no state is attached.
     */
    virtual s32 func_slotf4(void* associated);
    /** @brief Refresh the selected inventor portrait, name and numeric talents. */
    void func_00358850();
    /** Selection state for the inventor information window. */
    ItemCreationSelectedDisplayState* selection_state;
    ItemCreationOptionResourceDisplay* unkac;
    LibObject175140* unkb0;
    LibObject178750* unkb4;
    /** Creation-skill label widgets. */
    LibObject178750* skill_labels[9];
    /** Numeric creation-skill talent displays. */
    LibObject174F20* talent_displays[9];
    u8 unk100;
    u8 unk101;
    u16 unk102;
};

struct LibClass178600;
struct LibClass178630;
struct LibObject178750;
struct LibObject174F20;
struct ItemCreationOptionResourceDisplay;

/** @brief Control-help window for item creation and active development. */
class ItemCreationControlHelp : public FieldClass15AE70
{
public:
    /** Construct the window with its sixteen words cleared. */
    ItemCreationControlHelp();
    /** @brief Refresh both checked numeric displays. */
    virtual void func_slot5c();
    /** Destroy the window through Field's window base. */
    virtual ~ItemCreationControlHelp();
    /** @brief Run the default window action. @return Always one. */
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
     * @brief Create and attach the resource window displays.
     * @param associated Object associated with the window.
     * @return Always one.
     */
    virtual s32 func_slotf4(void* associated);
    /**
     * @brief Select the visible resource widgets and the panel size.
     * @param mode Resource display mode.
     * @param unused Unused caller state word.
     */
    void func_003598E0(u16 mode, u32 unused);
    LibClass178630* unka8;
    LibObject178750* unkac;
    LibObject178750* unkb0;
    LibObject178750* unkb4;
    LibObject178750* unkb8;
    LibObject178750* unkbc;
    LibObject178750* unkc0;
    LibObject178750* unkc4;
    LibObject178750* unkc8;
    ItemCreationOptionResourceDisplay* unkcc;
    LibObject174F20* unkd0;
    ItemCreationOptionResourceDisplay* unkd4;
    LibObject174F20* unkd8;
    float unkdc;
    float unke0;
    float unke4;
};

class ItemCreationClass1746A0;

/** @brief Item-creation title and scrolling status-message banner. */
class ItemCreationStatusBanner : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    ItemCreationStatusBanner()
        : heading_text(0), message_text(0), message_scroll_span(0), unkb4(0x42600000), message_hold_count(0), scroll_started(0), heading_width(0.0f), message_start_x(0.0f), message_frame_x(0.0f), message_frame_width(0.0f), message_frame(0), unkd0(0)
    {
    }
    /** @brief Destroy the status message window and its Field base. */
    virtual ~ItemCreationStatusBanner();
    /** @brief Hold, then advance and wrap the horizontal status message. */
    virtual void func_slot5c();
    /** @brief Set a status message and reset its scroll. @param text_key Absolute text key or signed relative index. */
    virtual void func_slot60(s32 text_key);
    /** @brief Create the message window widgets. @param associated Associated source. @return One on success, or zero for missing widgets. */
    virtual s32 func_slotf4(void* associated);
    LibObject178750* heading_text;
    LibObject178750* message_text;
    s32 message_scroll_span;
    u32 unkb4;
    s16 message_hold_count;
    u8 scroll_started;
    u8 unkbb;
    float heading_width;
    float message_start_x;
    float message_frame_x;
    float message_frame_width;
    ItemCreationClass1746A0* message_frame;
    ItemCreationClass1746A0* unkd0;
};

struct ItemCreationOptionResourceDisplay;

/** @brief Background image window for item creation. */
class ItemCreationBackground : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    ItemCreationBackground() : left_display(0), middle_display(0), right_display(0)
    {
    }
    /** @brief Destroy the resource window and its Field base. */
    virtual ~ItemCreationBackground();
    /** @brief Create and position the three resource displays. @param associated Associated source. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationOptionResourceDisplay* left_display;
    ItemCreationOptionResourceDisplay* middle_display;
    ItemCreationOptionResourceDisplay* right_display;
};

struct FieldObject23CEA0;
struct FieldObject23BE00;

/** @brief Main menu for inventing, facility expansion and inventor transfer. */
class ItemCreationMainMenu : public FieldClass15AE70
{
public:
    /** @brief Initialize the window and attach its State. @param state Owning selection State. */
    ItemCreationMainMenu(ItemCreationSelectedDisplayState* state) : selection_state(0)
    {
        selection_state = state;
        choice_selector = 0;
        selection_marker = 0;
        transfer_available = 0;
    }
    /** @brief Destroy the choice window and its Field base. */
    virtual ~ItemCreationMainMenu();
    /** @brief Move the selector in the first direction and refresh its labels. */
    virtual void func_slot68();
    /** @brief Move the selector in the second direction and refresh its labels. */
    virtual void func_slot6c();
    /** @brief Confirm the current choice. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Restore the prior display. @return Action status. */
    virtual s32 func_slotb4();
    /** @brief Create the choice labels and field selection widgets. @param associated Associated source. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* selection_state;
    FieldObject23CEA0* choice_selector;
    FieldObject23BE00* selection_marker;
    u8 transfer_available;
    u8 unkb5[3];
};

/** @brief Inventory catalog-type list showing item names and available counts. */
class InventoryItemTypeList : public FieldClass15AD40
{
public:
    /** @brief Initialize the item-type list and retain its selection state. @param state Selection state. */
    InventoryItemTypeList(ItemCreationSelectedDisplayState* state);
    /** @brief Release the embedded list and destroy the Field window. */
    virtual ~InventoryItemTypeList();
    /** @brief Set the item-type list marker visibility and depth. @param value Unused first argument. @param alternate Marker visibility and depth mode. */
    virtual void func_slot10c(u32 value, u32 alternate);
    /** @brief Refresh the item-type list's selection cursor. */
    virtual void func_slot5c();
    /** @brief Open the selected item type's instance list. @return One on activation, three on rejection, or zero when unavailable. */
    virtual s32 func_slotb0();
    /** @brief Return to the item-group window or restore its parent selection. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the item-type list widgets and initialize its selection. @param associated Associated source. @return Always one. */
    virtual s32 func_slot104(void* associated);
    /** @brief Refresh twelve item-type rows beginning at the list index. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the item-type list rows. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    /** @brief Rebuild the related category list. @param reset Whether to reset the selection. @param mode Category mode. */
    virtual void func_slot11c(u16 reset, u8 mode);
    LibObject178750* unk138[12];
    LibObject174F20* unk168[12];
    LibClass178630* unk198;
    ItemCreationClass1746A0* unk19c;
    ItemCreationSelectedDisplayState* unk1a0;
    u32 unk1a4;
    ItemCreationClass187A60 unk1a8;
    u16 unk1b4;
    u8 unk1b6[2];
    u32 unk1b8[24];
    u16 unk218;
    u8 unk21a[2];
    PlanItemGroupWindow* unk21c;
};

class FieldClass153130;
class FieldClass153170;

/** @brief Item-group selection window used while specifying a development plan. */
class PlanItemGroupWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the plan window for its selection state. @param state Owning selection state. */
    PlanItemGroupWindow(ItemCreationSelectedDisplayState* state);
    /** @brief Restore the group selector opacity and request its redraw. */
    virtual void func_slot64();
    /** Destroy the window through Field's window base. */
    virtual ~PlanItemGroupWindow();
    /** @brief Refresh the previous mode selection. */
    virtual void func_slot68();
    /** @brief Refresh the next mode selection. */
    virtual void func_slot6c();
    /** @brief Open the related list. @return Zero for an inactive selector; otherwise one. */
    virtual s32 func_slotb0();
    /** @brief Restore the prior item pair and parent window. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the mode display widgets. @param associated Associated parent. @return Setup status. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    FieldClass153130* unkac;
    FieldClass153170* unkb0;
    u16 unkb4;
    u8 unkb6[2];
    u32 unkb8;
    LibClass178630* unkbc;
    LibClass178630* unkc0;
    LibClass178630* unkc4;
    LibObject178750* unkc8[6];
    ItemCreationOptionResourceDisplay* unke0[6];
    LibObject178750* unkf8;
    float unkfc[4];
    s16 unk10c;
    u8 unk10e[2];
    LibObject178750* unk110[3];
    LibObject172410* unk11c[3];
    LibObject178750* unk128[6];
    LibObject174F20* unk140[3];
    u8 unk14c;
    u8 unk14d[3];
    InventoryItemTypeList* unk150;
};

/** @brief Choice between original invention and a specified plan. */
class InventionPolicyWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the invention choices for their selection state. @param state Owning selection state. */
    InventionPolicyWindow(ItemCreationSelectedDisplayState* state);
    /** @brief Move to the previous invention choice and refresh its text and marker. */
    virtual void func_slot68();
    /** @brief Move to the next invention choice and refresh its text and marker. */
    virtual void func_slot6c();
    /** @brief Handle the confirmed invention choice. @return Action status. */
    virtual s32 func_slotb0();
    /** Destroy the window through Field's window base. */
    virtual ~InventionPolicyWindow();
    /** @brief Reset the choices and return to the parent when enabled. @return Always two. */
    virtual s32 func_slotb4();
    /**
     * @brief Create the two choice displays and their selection widgets.
     * @param associated Object associated with the window.
     * @return Zero without a parent, otherwise one.
     */
    virtual s32 func_slotf4(void* associated);
    AssignedInventorGrid* unka8;
    u8 unkac;
    u8 unkad[0x3];
    LibClass178630* unkb0;
    LibObject178750* unkb4[2];
    float unkbc;
    float unkc0[3];
    FieldClass153130* unkcc;
    FieldClass153170* unkd0;
    u8 unkd4;
    u8 unkd5[0x3];
    ItemCreationSelectedDisplayState* selection_state;
    PlanItemGroupWindow* unkdc;
    FieldClass15AE70* unke0;
};

/** @brief Creation-skill selector filtered by installed workshop facilities. */
class CreationSkillWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Initialize the creation-skill window for its selection state.
     * @param state Owning selection state.
     */
    CreationSkillWindow(ItemCreationSelectedDisplayState* state);
    /** Destroy the window through Field's window base. */
    virtual ~CreationSkillWindow();
    /** @brief Refresh the option display for the first selection direction. */
    virtual void func_slot6c();
    /** @brief Refresh the option display for the second selection direction. */
    virtual void func_slot68();
    /** @brief Confirm the selected creation skill. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Reset the skill selection and handle the return mode. @return Always two. */
    virtual s32 func_slotb4();
    /**
     * @brief Create the eight creation-skill labels and their selection widgets.
     * @param associated Object associated with the window.
     * @return Zero without a parent, otherwise one.
     */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* selection_state;
    AssignedInventorGrid* unkac;
    LibClass178630* panel;
    LibObject178750* skill_labels[8];
    FieldClass153130* skill_selector;
    FieldClass153170* skill_marker;
    u8 unkdc;
    u8 unkdd[3];
    PlanItemGroupWindow* unke0;
    InventoryItemTypeList* unke4;
    /** Creation-skill facility bits permitted by the current selection. */
    u16 selectable_skill_mask;
};

/** @brief Display of a workshop's installed creation facilities. */
class WorkshopFacilitiesWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    WorkshopFacilitiesWindow() : selection_state(0), unkac(0)
    {
    }
    /** Destroy the window through Field's window base. */
    virtual ~WorkshopFacilitiesWindow();
    /** @brief Create the workshop-facility panel and eight skill labels. @param associated Object associated with the window. @return Always one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* selection_state;
    u8 unkac;
    u8 unkad[3];
};

/** @brief Display of the current workshop name. */
class WorkshopNameWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the window and attach its State. @param state Owning selection State. */
    WorkshopNameWindow(ItemCreationSelectedDisplayState* state) : selection_state(0)
    {
        selection_state = state;
    }
    /** Destroy the window through Field's window base. */
    virtual ~WorkshopNameWindow();
    /** @brief Create the panel and name label for the current workshop. @param associated Object associated with the window. @return Zero without selection state, otherwise one. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* selection_state;
};

/** @brief Nine-inventor grid for the three development teams. */
class AssignedInventorGrid : public FieldClass15AE70
{
public:
    /** @brief Initialize the assigned-inventor selection window. */
    AssignedInventorGrid();
    /** @brief Release the resources and destroy the Field window base. */
    virtual ~AssignedInventorGrid();
    /** @brief Refresh the assigned-inventor displays. */
    virtual void func_slot5c();
    /** Call the virtual at 0xa0. */
    virtual void func_slot68();
    /** Call the virtual at 0xa4. */
    virtual void func_slot6c();
    /** Call the virtual at 0xa8. */
    virtual void func_slot70();
    /** Call the virtual at 0xac. */
    virtual void func_slot74();
    /** @brief Toggle information for the selected inventor. @return One when available, or zero for a non-inventor cell or missing state. */
    virtual s32 func_slotb8();
    /** @brief Restore the active selection or leave item selection. @return Two when handled; zero when inactive. */
    virtual s32 func_slotb4();
    /** @brief Move the marker left or wrap within its row. */
    virtual void func_slota8();
    /** @brief Move the marker right or wrap within its row. */
    virtual void func_slotac();
    /** @brief Move the marker up or enter the related window. */
    virtual void func_slota0();
    /** @brief Move the marker down or enter the related window. */
    virtual void func_slota4();
    /** @brief Open the selected line's skill or policy window, or begin an inventor swap. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Apply the three selected components. @return Action status. */
    virtual s32 func_slotbc();
    /** @brief Create the selection displays. @param associated Associated window. @return Initialization status. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    FieldObject23CEA0* unkac;
    FieldObject23CEA0* unkb0;
    FieldObject23CEA0* unkb4;
    struct ItemCreationOptionResourceDisplay* unkb8[9];
    ItemCreationOptionResourceDisplay* unkdc[12];
    ItemCreationOptionResourceDisplay* unk10c[12];
    ItemCreationOptionResourceDisplay* unk13c[9];
    FieldClass15B200* unk160[12];
    u8 unk190;
    u8 unk191[3];
    LibObject178750* unk194[3];
    LibObject178750* unk1a0[3];
    LibObject174F20* unk1ac[3];
    LibObject178750* unk1b8[3];
    LibObject178750* unk1c4[3];
    LibObject178750* unk1d0[3];
    LibObject178750* unk1dc[3];
    CreationSkillWindow* unk1e8;
    InventionPolicyWindow* unk1ec;
    u8 unk1f0;
    u8 unk1f1;
    u8 unk1f2[9];
    u8 unk1fb;
    u32 unk1fc[3];
    u32 unk208[3];
    StartInventingDialog* unk214;
    u8 unk218[3];
    u8 unk21b[3];
    u8 unk21e[2];
};

/** @brief Workshop facility and development-line expansion menu. */
class WorkshopExpansionWindow : public FieldClass15AE70
{
public:
    /** Construct the window with its fields and arrays cleared. */
    WorkshopExpansionWindow();
    /** @brief Destroy the selection window through its Field window base. */
    virtual ~WorkshopExpansionWindow();
    /** @brief Refresh the checked-record value display, using zero for an invalid checksum. */
    virtual void func_slot5c();
    /** @brief Move the grid in direction zero and refresh its selected entry. */
    virtual void func_slot68();
    /** @brief Move the grid in direction one and refresh its selected entry. */
    virtual void func_slot6c();
    /** @brief Empty callback. */
    virtual void func_slot70();
    /** @brief Empty callback. */
    virtual void func_slot74();
    /** @brief Handle the callback at native slot 0xb0. @return Callback result. */
    virtual s32 func_slotb0();
    /** @brief Handle the callback at native slot 0xb4. @return Callback result. */
    virtual s32 func_slotb4();
    /** @brief Construct the panel widgets. @param associated Associated window. @return One on success, zero without an active state. */
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    /** One-based workshop ID selecting the expansion-price table. */
    u8 workshop_id;
    u8 unkad[3];
    /** Installation costs indexed by creation-skill ID minus one. */
    u32 facility_costs[8];
    u8 unkd0[8];
    u16 unkd8;
    u8 unkda[2];
    FieldObject23CEA0* unkdc;
    FieldObject23BE00* unke0;
    LibObject174F20* unke4;
    LibObject178750* unke8[9];
    u8 unk10c;
    u8 unk10d;
    u8 unk10e[2];
    /** Cost of adding a development line, indexed by the current line count. */
    u32 additional_line_costs[3];
    LibObject178750* unk11c;
    LibObject174F20* unk120;
};

/** @brief Overview of development teams and available inventors. */
class DevelopmentTeamsWindow : public FieldClass15AE70
{
public:
    /** Construct the window with its arrays and records cleared. */
    DevelopmentTeamsWindow();
    /** @brief Release the seven resource owners and destroy the option window. */
    virtual ~DevelopmentTeamsWindow();
    /** @brief Refresh the three option labels. */
    virtual void func_slot5c();
    /**
     * @brief Construct the assigned and available option displays.
     * @param associated Object associated with the window.
     * @return One when the selection state is present, otherwise zero.
     */
    virtual s32 func_slotf4(void* associated);
    struct ItemCreationOptionResourceDisplay* unka8[9];
    struct ItemCreationOptionResourceDisplay* unkcc[14];
    FieldClass15B200* unk104[7];
    ItemCreationSelectedDisplayState* unk120;
    u8 unk124;
    u8 unk125;
    u8 unk126[2];
    LibObject178750* unk128[3];
    LibObject178750* unk134[3];
    LibObject178750* unk140[3];
};

/** @brief Fourteen-inventor selection grid for available team members. */
class AvailableInventorGrid : public FieldClass15AE70
{
public:
    /** @brief Initialize the window storage through its Field base. */
    AvailableInventorGrid()
    {
        func_slotec(1);
        unka8 = 0;
        unkac = 0;
        unkb0 = 0;
        unkb4 = 0;
        for (s32 i = 0; i < 14; i++)
        {
            unkb8[i] = 0;
            unkf0[i] = 0;
        }
        unk128 = 0;
    }
    /** @brief Toggle information for the selected available inventor. @return One when a state is attached, zero otherwise. */
    virtual s32 func_slotb8();
    /** @brief Release the resource and destroy the window through its Field base. */
    virtual ~AvailableInventorGrid();
    /** Empty callback at native slot 0x5c. */
    virtual void func_slot5c();
    /** Call the virtual at 0xa0. */
    virtual void func_slot68();
    /** Call the virtual at 0xa4. */
    virtual void func_slot6c();
    /** Call the virtual at 0xa8. */
    virtual void func_slot70();
    /** Call the virtual at 0xac. */
    virtual void func_slot74();
    virtual void func_slota0();
    virtual void func_slota4();
    virtual void func_slota8();
    virtual void func_slotac();
    virtual s32 func_slotb0();
    virtual s32 func_slotb4();
    virtual s32 func_slotf4(void* associated);
    ItemCreationSelectedDisplayState* unka8;
    FieldObject23CEA0* unkac;
    FieldObject23CEA0* unkb0;
    FieldObject23CEA0* unkb4;
    ItemCreationOptionResourceDisplay* unkb8[14];
    ItemCreationOptionResourceDisplay* unkf0[14];
    FieldClass15B200* unk128;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Update a checked item display and its quantity, or hide the displays for an empty item.
 * @param object Owner of the checked item and quantity displays.
 * @param value Signed item index; zero hides the displays.
 * @param quantity Quantity to display, or -1 to hide its display.
 * @param index Index of the display to update.
 */
void func_0035E150(struct PlanItemGroupWindow* object, s16 value, s32 quantity, s8 index);

/**
 * @brief Update panel marker visibility and values from the selected state.
 * @param object Panel associated with the selected state.
 */
void func_00366050(WorkshopExpansionWindow* object);

/**
 * @brief Refresh the available and assigned resource displays from the selected state.
 * @param object Resource window with an optional associated selected state.
 */
void func_00366F10(struct DevelopmentTeamsWindow* object);

/**
 * @brief Refresh the assigned-group markers, colors, and the two group grids.
 * @param object Nine-slot view containing three assigned-group displays.
 */
void func_00363D20(AssignedInventorGrid* object);

/**
 * @brief Refresh the nine assigned-inventor portraits and their inventor IDs.
 * @param object Inventor grid for the three development lines.
 */
void func_003614B0(AssignedInventorGrid* object);

/**
 * @brief Refresh the fourteen available-inventor portraits.
 * @param object Available-inventor grid.
 */
void func_00364D20(AvailableInventorGrid* object);
/** @brief Update selection markers and display activation. @param object Selection window. @param enabled Full-word activation flag. */
void func_00364E00(AvailableInventorGrid* object, u32 enabled);

/**
 * @brief Initialize facility and development-line expansion costs for a workshop.
 * @param object Workshop-expansion window.
 * @param workshop_id Workshop ID from one through twelve.
 */
void item_creation_initialize_expansion_costs(WorkshopExpansionWindow* object, u8 workshop_id);

/**
 * @brief Activate the selected display and refresh its markers, or deactivate the displays and clear their markers.
 * @param object View containing nine markers and two twelve-marker groups.
 * @param mode One activates the selected display; zero deactivates displays; other values do nothing.
 */
void func_00360E60(AssignedInventorGrid* object, u16 mode);

/**
 * @brief Clear the view markers and mark the group selected by the current display index.
 * @param object View containing the markers and selected display.
 */
void func_00361220(AssignedInventorGrid* object);

/**
 * @brief Activate a selected display and its marker, or deactivate the current displays and markers.
 * @param object Fourteen-slot selection window.
 * @param mode One activates the selected display; zero deactivates the current displays; other values do nothing.
 */
void func_00364090(AvailableInventorGrid* object, u16 mode);

/**
 * @brief Test whether a development line contains any assigned inventor.
 * @param object Assigned-inventor grid containing three lines of inventor IDs.
 * @param line_index Development-line index from zero through two.
 * @return One when the line contains an inventor, or zero for an empty or invalid line.
 */
u8 func_003623C0(AssignedInventorGrid* object, u8 line_index);

/**
 * @brief Confirm the active slot and update its alternate field display.
 * @param object Fourteen-slot selection window linked to its state.
 * @return 1 when the active selection was processed, or 0 when unavailable.
 */
u8 func_003644F0(AvailableInventorGrid* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003641F0(void* object);

/**
 * @brief Test whether a category is rejected by the selected mode or has no accepted records.
 * @param object Category display containing its selected state and mode.
 * @param category Category entry containing the zero-based catalog index.
 * @return One when its catalog fields fail the mode test or no collected record passes it; otherwise zero.
 */
u8 func_0035CAD0(struct InventoryItemTypeList* object, const ItemCreationCategoryRecord* category);

/**
 * @brief Update creation-skill colors and the selected skill marker.
 * @param object Creation-skill selection window.
 * @param selected Selected skill row.
 */
void item_creation_update_skill_labels(CreationSkillWindow* object, u16 selected);

/** @brief Update the selection markers and window activation. @param object Nine-slot window. @param active Activation value. */
void func_003610D0(AssignedInventorGrid* object, u32 active);

/** @brief Hide or update the inventor detail window for the assigned-grid row. @param object Assigned inventor grid. */
void func_00360FD0(AssignedInventorGrid* object);

/**
 * @brief Refresh the choice labels, selection marker, and current status text.
 * @param object Three-choice window.
 */
void func_00368370(ItemCreationMainMenu* object);

/** @brief Resize the mode list and rebuild its category rows. @param object Mode list. @param mode Compact display mode. */
void func_0035D0C0(InventoryItemTypeList* object, s32 mode);

#ifdef __cplusplus
/**
 * @brief Test whether a record is empty, rejected by the selected mode, or already assigned.
 * @param object Owner of the selected mode and assigned identifier pairs.
 * @param record Packed item record to test; null is accepted as an empty record.
 * @return True for an empty record, a failed mode predicate, or an assigned identifier.
 */
bool func_0035B310(struct InventoryItemInstanceList* object, const struct ItemCreationAllocationRecord* record);
#endif

#ifdef __cplusplus
}
#endif

#endif
