#ifndef SO3_OVERLAYS_CSHOP_CSHOP_H
#define SO3_OVERLAYS_CSHOP_CSHOP_H

#include "types.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0023B1D0.h"

#ifdef __cplusplus
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002F9C90.h"

struct ItemCreationAllocationRecord;
class FieldClass15BB90;
class ItemCreationClass172870;
class ItemCreationOptionResourceDisplay;

/** Owned instances of the selected item, with sale prices and factors. */
struct ShopSaleItemWindow : public FieldClass15AD40
{
    LibObject172410* item_icons[5];
    LibObject174F20* sale_prices[5];
    LibObject172440* factors[8];
    ItemCreationClass172870* factor_separator;
    LibClass178630* panel;
    /** @brief Initialize the sale item window. */
    ShopSaleItemWindow()
    {
        for (s32 i = 0; i < 5; i++)
        {
            item_icons[i] = 0;
            sale_prices[i] = 0;
        }
        FieldClass15AD40();
    }
    /** @brief Destroy the Field list window. */
    virtual ~ShopSaleItemWindow();
    /** @brief Show the selected item instance and its factors. */
    virtual void func_slot5c();
    /** @brief Open confirmation for selling the selected instance. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Return to the sell list. @return Transition result. */
    virtual s32 func_slotb4();
    /** @brief Open confirmation for selling all instances. @return Action result. */
    virtual s32 func_slotbc();
    /** @brief Refresh the visible record displays. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the visible record displays. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    /** @brief Create the list displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Set row and selection visibility. @param visible Row display flag. @param selected Selection display flag. */
    virtual void func_slot10c(u32 visible, u32 selected);
};

/** Sellable items grouped by category. */
struct ShopSellListWindow : public FieldClass15AD40
{
    /** @brief Initialize the sell list window. */
    ShopSellListWindow()
    {
        for (s32 i = 0; i < 6; i++)
        {
            item_icons[i] = 0;
            item_counts[i] = 0;
        }
        FieldClass15AD40();
    }
    LibObject172410* item_icons[6];
    LibObject174F20* item_counts[6];
    LibClass178630* panel;
    u16 item_codes[750];
    /** @brief Destroy the Field list window. */
    virtual ~ShopSellListWindow();
    /** @brief Update the current catalog selection and its highlight. */
    virtual void func_slot5c();
    /** @brief Open the selected item's instances. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Return to the action window. @return Transition result. */
    virtual s32 func_slotb4();
    /** @brief Toggle the description and base-parameter views. @return Always one. */
    virtual s32 func_slotbc();
    /** @brief Select the previous item category. @return Always one. */
    virtual s32 func_slotc8();
    /** @brief Select the next item category. @return Always one. */
    virtual s32 func_slotcc();
    /** @brief Refresh the visible records. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the visible records. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    /** @brief Create the list displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Set row and selection visibility. @param visible Row display flag. @param selected Selection display flag. */
    virtual void func_slot10c(u32 visible, u32 selected);
};
/** Shop inventory with prices and purchase quantities. */
struct ShopBuyListWindow : public FieldClass15AD40
{
    LibObject172410* item_icons[6];
    LibObject174F20* price_displays[6];
    LibObject178750* multiply_labels[6];
    LibObject174F20* quantity_displays[6];
    LibObject178750* separator_labels[6];
    LibObject174F20* buy_limit_displays[6];
    LibClass178630* panel;
    s32 error_sound_timer;
    /** @brief Initialize the buy list window. */
    ShopBuyListWindow();
    /** @brief Destroy the Field list window. */
    virtual ~ShopBuyListWindow();
    /** @brief Update the selected item, row highlight and error sound timer. */
    virtual void func_slot5c();
    /** @brief Decrease the selected purchase quantity and refresh its row. */
    virtual void func_slot70();
    /** @brief Increase the selected purchase quantity and refresh its row. */
    virtual void func_slot74();
    /** @brief Open purchase confirmation. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Clear purchase quantities and return to the action window. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Open details for the selected item. @return Always one. */
    virtual s32 func_slotb8();
    /** @brief Toggle the description and base-parameter views. @return Always one. */
    virtual s32 func_slotbc();
    /** @brief Select the previous item category. @return Always one. */
    virtual s32 func_slotc8();
    /** @brief Select the next item category. @return Always one. */
    virtual s32 func_slotcc();
    /** @brief Refresh the visible records. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the visible records. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    /** @brief Create the list displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Set row and selection visibility. @param visible Row display flag. @param selected Selection display flag. */
    virtual void func_slot10c(u32 visible, u32 selected);
};

/** Item category, description, factors and model. */
struct ShopItemDetailWindow : public FieldClass15AE70
{
    /** @brief Destroy the Field window base. */
    virtual ~ShopItemDetailWindow();
    /** @brief Refresh the detail container and base window. */
    virtual void func_slot0c();
    /** @brief Close the detail window after its item model finishes closing. */
    virtual void func_slot5c();
    /** @brief Request cancellation of the attached status window when present. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    /** @brief Initialize the item detail window. */
    ShopItemDetailWindow();
    LibObject178750* category_label;
    LibObject172410* item_icon;
    ItemCreationClass172870* factor_separator;
    LibObject178750* description_text;
    LibObject178750* factor_heading;
    LibObject172440* factors[8];
    LibClass178630* panel;
    LibObject178660* detail_container;
    FieldClass15BB90* item_model;
    u8 closing;
};

/** Current fol, transaction total and remaining fol. */
struct ShopFolWindow : public FieldClass15AE70
{
    /** @brief Clear the three numeric display pointers. */
    ShopFolWindow() : current_fol(0), transaction_total(0), remaining_fol(0)
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopFolWindow();
    /** @brief Update current fol, transaction total and remaining fol. */
    virtual void func_slot5c();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject174F20* current_fol;
    LibObject174F20* transaction_total;
    LibObject174F20* remaining_fol;
};

/** Buy and sell actions with the current item category. */
struct ShopActionWindow : public FieldClass15AE70
{
    /** @brief Clear the choice display pointer. */
    ShopActionWindow() : choice(0)
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopActionWindow();
    /** @brief Highlight the selected action and show the item category. */
    virtual void func_slot5c();
    /** @brief Move the choice grid in direction 3 unless the window state byte is set. */
    virtual void func_slot70();
    /** @brief Move the choice grid in direction 2 unless the window state byte is set. */
    virtual void func_slot74();
    /** @brief Enter the selected buy or sell mode. @return Zero while locked, otherwise one. */
    virtual s32 func_slotb0();
    /** @brief Request the shop window transition. @return Zero while locked, otherwise two. */
    virtual s32 func_slotb4();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* choice;
    LibObject178750* category_label;
    LibObject178750* buy_label;
    LibObject178750* sell_label;
    LibClass174C40* previous_category_icon;
    LibClass174C40* next_category_icon;
};

/** Item description and base parameters. */
struct ShopDescriptionWindow : public FieldClass15AE70
{
    LibObject174D90* description;
    LibObject178750* help_text;
    LibObject178750* switch_hint;
    LibObject178750* parameters_heading;
    LibObject178750* parameter_labels[5];
    LibObject178750* parameter_separators[5];
    LibObject174F20* parameter_values[5];
    u32 description_key;
    u8 show_parameters;
    /** @brief Clear the description pointers and toggle state. */
    ShopDescriptionWindow() : description(0), help_text(0), description_key(0), show_parameters(0)
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopDescriptionWindow();
    /** @brief Show the selected category's five catalog values, or its description text when the value view is off. */
    virtual void func_slot5c();
    /**
     * @brief Create the description displays and five paired value rows.
     * @param associated Full resource source word.
     * @return One after creating the displays, or zero for a missing resource slot.
     */
    virtual s32 func_slotf4(u32 associated);
};

/** Party equipment compatibility and parameter comparisons. */
struct ShopEquipmentPreviewWindow : public FieldClass15AE70
{
    void* unka8;
    ItemCreationOptionResourceDisplay* resources[8];
    LibObject178750* labels[8];
    s32 pulse_level;
    s32 pulse_step;
    /** @brief Clear the window display pointer. */
    ShopEquipmentPreviewWindow() : unka8(0)
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopEquipmentPreviewWindow();
    /** @brief Preview the selected item's equipment compatibility and parameter changes. */
    virtual void func_slot5c();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
};

/** Shop name and scrolling help for the selected action. */
struct ShopHelpWindow : public FieldClass15AE70
{
    /** @brief Clear the message display and scroll state. */
    ShopHelpWindow()
    {
        text = 0;
        text_width = 0;
        scroll_timer = 0;
        help_index = 0;
        scrolling = 0;
        label_width = 0;
        scroll_start_x = 0;
        scroll_left = 0;
        scroll_width = 0;
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopHelpWindow();
    /** @brief Update and scroll the selected action's help text. */
    virtual void func_slot5c();
    /** @brief Set the window text. @param text_key Help message index before the resource offset. */
    virtual void func_slot60(s32 text_key);
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* text;
    s32 text_width;
    s16 scroll_timer;
    u8 scrolling;
    u8 unkb3;
    s32 help_index;
    float label_width;
    float scroll_start_x;
    float scroll_left;
    float scroll_width;
};

/** Background assembled from three resource images. */
struct ShopBackgroundWindow : public FieldClass15AE70
{
    /** @brief Destroy the Field window base. */
    virtual ~ShopBackgroundWindow();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
};

/** Confirmation for selling all instances of the selected item. */
struct ShopSellAllConfirmWindow : public FieldClass15AE70
{
    /** @brief Clear the choice and paired display pointers. */
    ShopSellAllConfirmWindow()
    {
        choice = 0;
        yes_label = 0;
        no_label = 0;
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopSellAllConfirmWindow();
    /** @brief Update the choice with action code three. */
    virtual void func_slot70();
    /** @brief Update the choice with action code two. */
    virtual void func_slot74();
    /** @brief Run the selected action. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Return to the associated window. @return Transition result. */
    virtual s32 func_slotb4();
    /** @brief Create the choice display. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* choice;
    LibObject178750* yes_label;
    LibObject178750* no_label;
};

/** Confirmation for purchasing the selected items. */
struct ShopBuyConfirmWindow : public FieldClass15AE70
{
    /** @brief Clear the choice and paired display pointers. */
    ShopBuyConfirmWindow()
    {
        choice = 0;
        yes_label = 0;
        no_label = 0;
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopBuyConfirmWindow();
    /** @brief Refresh the choice focus flag. */
    virtual void func_slot5c();
    /** @brief Update the choice with action code three. */
    virtual void func_slot70();
    /** @brief Update the choice with action code two. */
    virtual void func_slot74();
    /** @brief Run the selected action. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Return to the associated window. @return Transition result. */
    virtual s32 func_slotb4();
    /** @brief Create the choice display. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* choice;
    LibObject178750* yes_label;
    LibObject178750* no_label;
};

/** Confirmation for selling the selected item instance. */
struct ShopSellConfirmWindow : public FieldClass15AE70
{
    /** @brief Clear the choice and paired display pointers. */
    ShopSellConfirmWindow()
    {
        choice = 0;
        yes_label = 0;
        no_label = 0;
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopSellConfirmWindow();
    /** @brief Update the choice with action code three. */
    virtual void func_slot70();
    /** @brief Update the choice with action code two. */
    virtual void func_slot74();
    /** @brief Run the selected action. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Return to the associated window. @return Transition result. */
    virtual s32 func_slotb4();
    /** @brief Create the choice display. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* choice;
    LibObject178750* yes_label;
    LibObject178750* no_label;
};

/** Shop copy of the shared movement storage receiver. */
typedef LibMovementState ShopClass187B90;

/** Shop copy of the shared intrusive-link root. */
typedef LibClass171E80 ShopClass187B68;
/** Shop copy of the shared intrusive-list sentinel. */
typedef LibClass171E90 ShopClass187B78;

/** Shop resources, windows, selected items and transaction state. */
struct ShopState : FieldClass153E30
{
    /** @brief Initialize the shop controller and its record selection. */
    ShopState();
    /** @brief Initialize the selected records. @return Nonzero when selection links are present. */
    virtual u8 func_00264110();
    /** @brief Destroy the record selection and Field controller base. */
    virtual ~ShopState();
    s32 resource_slot;
    u8 windows_initialized;
    u8 unk39[3];
    ShopEquipmentPreviewWindow* equipment_window;
    ShopDescriptionWindow* description_window;
    ShopActionWindow* action_window;
    ShopBuyListWindow* buy_window;
    ShopSellListWindow* sell_window;
    ShopFolWindow* fol_window;
    FieldRecordSelection selection;
    ShopTransaction transaction;
    s32 selected_item;
    s32 category;
    s32 shop_id;
    s32 selected_action;
    ItemCreationAllocationRecord* selected_allocation;
    u8 mode;
};
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct ShopState ShopState;
    typedef struct ShopHelpWindow ShopScrollingWindow;
    typedef struct ShopFolWindow ShopValueDisplay;
    typedef struct ObjectField20 ObjectField20;
    typedef struct ObjectField34 ObjectField34;
    typedef struct ObjectStatusFields ObjectStatusFields;
#ifndef __cplusplus
    typedef struct ShopSaleItemWindow ShopSaleItemWindow;
#endif

    /**
     * @brief Open the alternate choice window for the selected allocation.
     * @param receiver Window associated with the new choice window.
     * @return Always one.
     */
    s32 func_0034A0F0(void* receiver);

    /**
     * @brief Open the bucket choice window when the combined count is nonzero.
     * @param receiver Window associated with the new choice window.
     * @return One after opening, or three when the count is zero.
     */
    s32 func_0034CC10(void* receiver);

    /**
     * @brief Open the choice window when an allocation record is selected.
     * @param receiver Window associated with the new choice window.
     * @return Always one.
     */
    s32 func_0034A1E0(void* receiver);

    /**
     * @brief Set the text key and reset its scrolling timer.
     * @param object Scrolling text window.
     * @param key Shop text key before the resource key offset.
     */
    void shop_set_help_text(ShopScrollingWindow* object, s32 key);

    /**
     * @brief Refresh the current text and advance its horizontal scrolling.
     * @param object Scrolling text window.
     */
    void shop_update_help_text(ShopScrollingWindow* object);

    /**
     * @brief Set the window state code and flags when its control byte is clear.
     * @param receiver Window callback receiver.
     * @return Zero while the control byte is set, otherwise two.
     */
    s32 func_0034DEF0(void* receiver);

    /**
     * @brief Select the shop mode from the choice control's signed selection.
     * @param receiver Window containing the choice control.
     * @return Zero while the control byte is set, otherwise one.
     */
    s32 func_0034DF50(void* receiver);

    /**
     * @brief Return the current window to its associated state when its control byte is clear.
     * @param receiver Window callback receiver.
     * @return Zero while the control byte is set, otherwise two.
     */
    s32 func_003488D0(void* receiver);

    /**
     * @brief Return the current window to its associated state when its control byte is clear.
     * @param receiver Window callback receiver.
     * @return Zero while the control byte is set, otherwise two.
     */
    s32 func_00349110(void* receiver);

    /**
     * @brief Return the current window to its associated state when its control byte is clear.
     * @param receiver Window callback receiver.
     * @return Zero while the control byte is set, otherwise two.
     */
    s32 func_003499B0(void* receiver);

    /**
     * @brief Pass the supplied object to the current state and select state code three.
     * @param object Supplied window or callback object.
     * @return Always two.
     */
    s32 func_0034A0A0(void* object);

    /**
     * @brief Refresh the checked value and the totals for the current allocation.
     * @param object Numeric display containing the three values.
     */
    void shop_update_fol(ShopValueDisplay* object);

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
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_003485F0(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00348600(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00348610(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00348620(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00348630(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00348640(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00348650(void* object);

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
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_00348690(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_003486A0(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_003486B0(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_003486C0(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_003486D0(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_003486E0(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_003486F0(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00348700(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00348710(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00348740(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_003516A0(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_003516B0(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_003516C0(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00351800(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00351810(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_00351890(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_00351970(void* object);

    /**
     * @brief Return the fixed value 4.
     * @param object Receiver or first argument; unused.
     * @return Always 4.
     */
    s32 func_00351BE0(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_00351C30(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_00351C40(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00351C50(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_00351C60(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00351C70(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00351C80(void* object);

    /**
     * @brief Perform no work.
     * @param object Receiver or first argument; unused.
     */
    void func_00351C90(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_00351CA0(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_00351CB0(void* object);

    /**
     * @brief Return the fixed value 0.
     * @param object Receiver or first argument; unused.
     * @return Always 0.
     */
    s32 func_00351CC0(void* object);

    /**
     * @brief Set field at offset 0x20.
     * @param object Object containing the field.
     * @param value Value to store.
     */
    void func_00348960(ObjectField20* object, u32 value);

    /**
     * @brief Get field at offset 0x20.
     * @param object Object containing the field.
     * @return Field value.
     */
    u32 func_00349820(ObjectField20* object);

    /**
     * @brief Get field at offset 0x34.
     * @param object Object containing the field.
     * @return Field value.
     */
    u32 func_0034A1D0(ObjectField34* object);

    /**
     * @brief Get field at offset 0x38.
     * @param object Object containing the field.
     * @return Field value.
     */
    u8 func_00351BD0(ObjectStatusFields* object);

    /**
     * @brief Set field at offset 0x24.
     * @param object Object containing the field.
     * @param value Value to store.
     */
    void func_00351BF0(ObjectStatusFields* object, u32 value);

    /**
     * @brief Get field at offset 0x24.
     * @param object Object containing the field.
     * @return Field value.
     */
    u32 func_00351C00(ObjectStatusFields* object);

    /**
     * @brief Set field at offset 0x28.
     * @param object Object containing the field.
     * @param value Value to store.
     */
    void func_00351C10(ObjectStatusFields* object, s8 value);

    /**
     * @brief Get field at offset 0x28.
     * @param object Object containing the field.
     * @return Field value.
     */
    s8 func_00351C20(ObjectStatusFields* object);

    /**
     * @brief Create and attach the shop state windows.
     * @param receiver Current shop state.
     * @return Always one.
     */
    s32 shop_create_windows(void* receiver);

    /**
     * @brief Register a completed resource buffer and finish the receiver setup.
     * @param receiver Current shop state.
     * @param buffer Completed resource buffer.
     * @return Setup result, or zero for a missing buffer.
     */
    s32 shop_register_resource(void* receiver, void* buffer);

    /**
     * @brief Check the value associated with the field at offset 0x54.
     * @param object Object containing the field.
     * @return Nonzero if the value is set.
     */
    s32 func_00351540(u8* object);

    /**
     * @brief Advance the current selection and refresh the receiver.
     * @param object Receiver to refresh.
     * @return Always 1.
     */
    s32 func_0034AF50(void* object);

    /**
     * @brief Move the current selection backward and refresh the receiver.
     * @param object Receiver to refresh.
     * @return Always 1.
     */
    s32 func_0034AFA0(void* object);

    /**
     * @brief Advance the current selection and refresh the receiver.
     * @param object Receiver to refresh.
     * @return Always 1.
     */
    s32 func_0034CA50(void* object);

    /**
     * @brief Move the current selection backward and refresh the receiver.
     * @param object Receiver to refresh.
     * @return Always 1.
     */
    s32 func_0034CAA0(void* object);

    /**
     * @brief Toggle the current display's byte flag.
     * @param object Callback receiver; unused.
     * @return Always 1.
     */
    s32 func_0034AFF0(void* object);

    /**
     * @brief Toggle the current display's byte flag.
     * @param object Callback receiver; unused.
     * @return Always 1.
     */
    s32 func_0034CAF0(void* object);

    /**
     * @brief Create and select the shop message window.
     * @return One after attaching the window.
     */
    s32 shop_open_item_details(void);

    /**
     * @brief Set the current shop state to mode 1.
     * @param object Callback receiver; unused.
     * @return Always 2.
     */
    s32 func_0034B020(void* object);

    /**
     * @brief Move to the next nonempty item category.
     * @param object Current shop state.
     * @param direction Signed selection step.
     */
    void shop_change_category(ShopState* object, s32 direction);

    /**
     * @brief Change the current shop mode.
     * @param object Current shop state.
     * @param mode New mode, using its low byte.
     */
    void shop_set_mode(ShopState* object, u32 mode);

    /**
     * @brief Rebuild the catalog code list for the current mode and clamp its scroll and cursor.
     * @param object Catalog list window.
     * @param reset Nonzero to move the scroll offset and cursor back to the first row.
     */
    void shop_refresh_sell_list(void* object, u8 reset);

    /**
     * @brief Size the bucket list to the current bucket's entry count and clamp its scroll and cursor.
     * @param object Bucket list window.
     * @param reset Nonzero to move the scroll offset and cursor back to the first row.
     */
    void shop_refresh_buy_list(void* object, u8 reset);

    /**
     * @brief Release the shop state resources and clear its runtime flags.
     * @param object Shop state to release.
     */
    void shop_release_resources(ShopState* object);

    /**
     * @brief Enqueue the receiver for resident processing.
     * @param object Receiver to enqueue.
     */
    void func_003510B0(void* object);

    /**
     * @brief Append a value after the list's sentinel node.
     * @param list List containing an existing sentinel and element count.
     * @param value Object pointer to append.
     */
    void func_00351CD0(FieldCountedList* list, void* value);

    /**
     * @brief Append a value after the list's sentinel node.
     * @param list List containing an existing sentinel and element count.
     * @param value Object pointer to append.
     */
    void func_00351D60(FieldCountedList* list, void* value);

    /**
     * @brief Append a value after the list's sentinel node.
     * @param list List containing an existing sentinel and element count.
     * @param value Object pointer to append.
     */
    void func_00351DF0(FieldCountedList* list, void* value);

    /**
     * @brief Append a value after the list's sentinel node.
     * @param list List containing an existing sentinel and element count.
     * @param value Object pointer to append.
     */
    void func_00351E80(FieldCountedList* list, void* value);

    /**
     * @brief Clear the current state's transaction and return to mode 1.
     * @param object Callback receiver; unused.
     * @return Always 2.
     */
    s32 func_0034CBD0(void* object);

    /**
     * @brief Set the shop identifier and its runtime-dependent price adjustment.
     * @param object Current shop state.
     * @param shop_id Shop identifier.
     */
    void shop_set_id(ShopState* object, u16 shop_id);

    /**
     * @brief Clamp a four-row list's range and selection to the current category's record count.
     * @param object Display containing list parameters and record count.
     */
    void shop_refresh_sale_item_range(ShopSaleItemWindow* object);

#ifdef __cplusplus
}
#endif

#endif
