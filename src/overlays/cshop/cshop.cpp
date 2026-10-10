#include "include_asm.h"
#include "overlays/cshop/cshop.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"
#include "overlays/lib/list_indicator_inlines.h"
#include "overlays/lib/marker_widget_inlines.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_00101260.h"
#include "main/resident_001001E0.h"
#include "main/resident_data.h"
#include "main/item_category.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_001E1590.h"

/** Item-name rectangle and scale shared by the shop lists. */
#define SHOP_ITEM_NAME_WIDTH 323.99997f
#define SHOP_ITEM_NAME_HEIGHT 21.599998f
#define SHOP_ITEM_NAME_SCALE 0.9f

extern "C" u8 func_28E3D0(void* object);

enum ShopMessage
{
    SHOP_MSG_QUANTITY_SEPARATOR = 0x7E7,
    SHOP_MSG_TITLE = 0x2EE0,
    SHOP_MSG_BUY_HELP = 0x2EE1,
    SHOP_MSG_BUY = 0x2EE4,
    SHOP_MSG_SELL = 0x2EE5,
    SHOP_MSG_CURRENT_FOL = 0x2EE7,
    SHOP_MSG_TOTAL_FOL = 0x2EE8,
    SHOP_MSG_REMAINING_FOL = 0x2EE9,
    SHOP_MSG_MULTIPLY = 0x2EEA,
    SHOP_MSG_CONFIRM_PURCHASE = 0x2EEC,
    SHOP_MSG_PURCHASE_PROMPT = 0x2EED,
    SHOP_MSG_CONFIRM_SALE = 0x2EEE,
    SHOP_MSG_SALE_PROMPT = 0x2EEF,
    SHOP_MSG_SELL_ALL_PROMPT = 0x2EF0,
    SHOP_MSG_YES = 0x2EF1,
    SHOP_MSG_NO = 0x2EF2,
    SHOP_MSG_WEAPONS = 0x2EF6,
    SHOP_MSG_EQUIPPED = 0x2EFE,
    SHOP_MSG_STAT_INCREASE = 0x2EFF,
    SHOP_MSG_STAT_DECREASE = 0x2F00,
    SHOP_MSG_STAT_UNCHANGED = 0x2F01,
    SHOP_MSG_ATK = 0x2F02,
    SHOP_MSG_HIT = 0x2F03,
    SHOP_MSG_DEF = 0x2F04,
    SHOP_MSG_AGL = 0x2F05,
    SHOP_MSG_INT = 0x2F06,
    SHOP_MSG_PARAMETER_SEPARATOR = 0x2F07,
    SHOP_MSG_DESCRIPTION_HELP = 0x2F08,
    SHOP_MSG_SELL_ALL_HELP = 0x2F0A,
    SHOP_MSG_SELL_BACK_HELP = 0x2F0B,
    SHOP_MSG_BACK_HELP = 0x2F0C,
    SHOP_MSG_FACTOR = 0x2F0D,
    SHOP_MSG_SWITCH_HELP = 0x2F0E,
    SHOP_MSG_BASE_PARAMETERS = 0x2F0F,
    SHOP_MSG_SHOP_NAMES = 0x12924,
    SHOP_MSG_LIST_DESCRIPTIONS = 0x1294E,
    SHOP_MSG_ITEM_NAMES = 50000,
    SHOP_MSG_DETAIL_DESCRIPTIONS = 55000,
    SHOP_MSG_FACTORS = 70000
};

enum ShopMode
{
    SHOP_MODE_ACTION = 1,
    SHOP_MODE_BUY = 2,
    SHOP_MODE_SELL = 3
};

enum ShopCategory
{
    SHOP_CATEGORY_WEAPONS = 0,
    SHOP_CATEGORY_ARMOR = 1,
    SHOP_CATEGORY_ACCESSORIES = 2,
    SHOP_CATEGORY_USABLE_ITEMS = 3,
    SHOP_CATEGORY_FOOD = 4,
    SHOP_CATEGORY_OTHER_ITEMS = 5,
    SHOP_CATEGORY_MATERIALS = 6,
    SHOP_CATEGORY_ALL = 7
};

enum ShopDiscountFlag
{
    SHOP_DISCOUNT_10_PERCENT = 2,
    SHOP_DISCOUNT_20_PERCENT = 4,
    SHOP_DISCOUNT_30_PERCENT = 8
};

enum ShopItemFlag
{
    SHOP_ITEM_PLAYER_INVENTED = 0x04
};

/** Item factor identifiers omitted from the shop factor displays. */
enum ShopFactor
{
    SHOP_FACTOR_NONE = 0,
    SHOP_FACTOR_NOTHING = 700
};

/** Selection cursor opacity before the parent display alpha is applied. */
enum ShopCursorOpacity
{
    SHOP_CURSOR_FOCUSED_OPACITY = 128,
    SHOP_CURSOR_UNFOCUSED_OPACITY = 64
};

/** Partial resource header with the total block size, including the header. */
struct ShopAlignedResource
{
    u8 unk00[0x40];
    s32 byte_count;
};

/** Packed sixteen-byte item allocation record. */
struct ItemCreationAllocationRecord
{
    union
    {
        u16 halves[2];
        struct
        {
            u16 definition_index : 10;
            u16 factor0_low_bits : 6;
            u16 factor0_high_bits : 4;
            u16 factor1 : 10;
            u16 unk03_high : 2;
        } bits;
    } definition_factors;
    union
    {
        u16 halves[2];
        struct
        {
            u16 factor2 : 10;
            u16 factor3_low_bits : 6;
            u16 factor3_high_bits : 4;
            u16 factor4 : 10;
            /** Suppress the allocation ID when the record checksum is valid. */
            u16 suppress_allocation_id : 1;
            u16 unk07_high : 1;
        } bits;
    } factors_234;
    union
    {
        u16 halves[2];
        struct
        {
            u16 factor5 : 10;
            u16 factor6_low_bits : 6;
            u16 factor6_high_bits : 4;
            u16 factor7 : 10;
            u16 unk0b_high : 2;
        } bits;
    } factors_567;
    u8 modification_number : 7;
    u8 equipped_owner_low_bit : 1;
    u8 equipped_owner_high_bits : 3;
    /** @brief Random two-bit shift used in the record checksum. */
    u8 checksum_shift : 2;
    u8 battle_usable : 1;
    u8 allocated : 1;
    u8 new_item : 1;
    /** @brief Checksum of the six halfwords at offsets 00 through 0A. */
    u16 checksum;

    /**
     * @brief Calculate the checksum of the six halfwords for a given shift.
     * @param shift Two-bit shift applied to the checksum key.
     * @return Calculated checksum.
     */
    u16 calculate_checksum(u32 shift) const
    {
        return (0x83CF << shift) ^ ((factors_567.halves[0] + (definition_factors.halves[0] + factors_234.halves[0])) ^
                                  (definition_factors.halves[1] + (factors_234.halves[1] + factors_567.halves[1])));
    }
    /**
     * @brief Calculate the checksum of the six halfwords with the stored shift.
     * @return Calculated checksum.
     */
    u16 calculate_checksum() const
    {
        return (0x83CF << checksum_shift) ^ ((factors_567.halves[0] + (definition_factors.halves[0] + factors_234.halves[0])) ^
                                           (definition_factors.halves[1] + (factors_234.halves[1] + factors_567.halves[1])));
    }
    /**
     * @brief Clear the record, choose its checksum shift and store the checksum.
     * @param key Fixed shift to use instead of a random one, or null.
     */
    void reset(const u8* key)
    {
        *(unsigned __int128*)this = 0;
        checksum_shift = func_0010CF80() & 3;
        if (key != 0)
        {
            checksum_shift = *key;
        }
        checksum = calculate_checksum(checksum_shift);
    }
    /**
     * @brief Test whether the stored checksum differs from the record contents.
     * @return True when the checksum differs.
     */
    bool invalid() const
    {
        return checksum != calculate_checksum();
    }
    /**
     * @brief Read the catalog definition index from a valid allocation.
     * @return Definition index, or zero when the checksum differs.
     */
    u16 definition_index()
    {
        if (invalid())
        {
            return 0;
        }
        return definition_factors.bits.definition_index;
    }
};

/** Allocation indices linking the instances of one item type. */
struct ShopAllocationLink
{
    s16 previous;
    s16 next;
};

/** Item allocations, their list links and the inventory totals for each item type. */
struct ShopInventoryState
{
    ItemCreationAllocationRecord allocations[3000];
    ShopAllocationLink allocation_links[3000];
    ItemCreationCategoryRecord item_records[750];
};

/** Four packed panel colors copied as one aligned block. */
union ShopPanelColors
{
    unsigned __int128 packed;
    LibWidgetColors4C5590 colors;
} __attribute__((aligned(16)));
extern "C" const ShopPanelColors D_00351FA0;
extern "C" const ShopPanelColors D_00351FB0;
extern "C" const ShopPanelColors D_00351FC0;

/** Partial resource runtime containing the selected slot and display code. */
struct FieldRuntime
{
    u8 unk00[0x514];
    s32 item_name_resource_slot;
    u32 item_name_base_key;
    s32 factor_resource_slot;
    u32 factor_base_key;
};

struct ShopRuntimeFlags
{
    u8 unk00[0x81];
    u8 flags;
    u8 unk82[0x13E];
    /** Invincibility effect countdown; also triggers the maximum shop discount while active. */
    s32 invincibility_timer;
};

typedef struct ShopCallbacks
{
    u8 unk00[0x14];
    ShopState* shop;
} ShopCallbacks;
typedef struct ShopRuntime
{
    ResidentCheckedRecord* saved_record;
    u8 unk04[0xC];
    ShopCallbacks* callbacks;
    u8 unk14[0x8];
    /** Field camera supplying the item preview's view and projection settings. */
    void* field_camera;
    FieldBufferSlots* resource_buffers;
} ShopRuntime;
/**
 * @brief Remove the window from its runtime context.
 * @param context Runtime window context.
 * @param window Window to remove.
 */
extern "C" void func_002CFE10(ShopCallbacks* context, FieldClass15AE70* window);
// Resident runtime interface, scoped to this overlay.
extern ShopRuntime* D_001B643C;
extern ResidentObjectQueue* D_001B65F4;
extern float D_001B6690;
extern ShopInventoryState* D_001B64F8;

// This Field overlay interface has no recovered declaration in its owning header.
extern "C" void func_002CE220(FieldStateCE420* object, s32 count, s32 offset, s32 selected);

/**
 * @brief Return the saved runtime section containing the shop flags.
 * @return Runtime flag section selected by directory key 4.
 */
static inline ShopRuntimeFlags* shop_runtime_flags()
{
    return reinterpret_cast<ShopRuntimeFlags*>(func_00101440(func_00101290(func_0010D8E0()), 4));
}

/**
 * @brief Read a masked runtime flag as a byte-valued truth value.
 * @param mask Flag bits to test.
 * @return One when any requested bit is set, zero otherwise.
 */
static inline u8 shop_runtime_flag(u8 mask)
{
    return (shop_runtime_flags()->flags & mask) != 0;
}

/**
 * @brief Clear selected bits in the runtime flag byte.
 * @param mask Flag bits to clear.
 */
static inline void clear_shop_runtime_flag(u32 mask)
{
    ShopRuntimeFlags* flags = shop_runtime_flags();
    flags->flags = flags->flags & ~mask;
}

/**
 * @brief Find the inventory item record for a one-based item code.
 * @param inventory Resident item inventory.
 * @param item_code One-based item code.
 * @return Selected record, or null when the code is out of range.
 */
static inline ItemCreationCategoryRecord* shop_item_record(ShopInventoryState* inventory, u16 item_code)
{
    u8 valid = item_code > 0 && item_code < 751;
    if (valid)
    {
        return &inventory->item_records[item_code - 1];
    }
    return 0;
}

/**
 * @brief Set the numeric widget value and mark it for redraw.
 * @param object Numeric widget.
 * @param number Value to display.
 */
static inline void set_shop_number(LibObject174F20* object, s32 number)
{
    object->numeric_value = number;
    object->unk3c = 1;
}

// These Field list interfaces have no declarations in their owning header.
extern "C" void func_002CD7C0(void* object);
extern "C" void func_002CD8B0(void* object, void* element, u32 color);
ShopSellAllConfirmWindow::~ShopSellAllConfirmWindow()
{
}

/** @brief Store the window byte at offset 0xC. @param value Unsigned byte to store. */
void FieldClass15AE70::func_slot24(u8 value)
{
    unk0c = value;
}

/** @brief Read the window byte at offset 0xC. @return Stored unsigned byte. */
u8 FieldClass15AE70::func_slot28()
{
    return unk0c;
}

/** @brief Store the window byte at offset 0x8. @param value Unsigned byte to store. */
void FieldClass15AE70::func_slot2c(u8 value)
{
    unk08 = value;
}

/** @brief Read the window byte at offset 0x8. @return Stored unsigned byte. */
u8 FieldClass15AE70::func_slot30()
{
    return unk08;
}

/** @brief Store the window halfword at offset 0xA. @param value Unsigned halfword to store. */
void FieldClass15AE70::func_slot34(u16 value)
{
    unk0a = value;
}

/** @brief Read the window halfword at offset 0xA. @return Stored unsigned halfword. */
u16 FieldClass15AE70::func_slot38()
{
    return unk0a;
}

/** @brief Store the alternate associated pointer. @param associated Pointer to store. */
void FieldClass15AE70::func_slot48(void* associated)
{
    unk9c = associated;
}

/** @brief Read the alternate associated pointer. @return Stored pointer. */
void* FieldClass15AE70::func_slot4c()
{
    return unk9c;
}

/**
 * @brief Store the opaque source word.
 * @param value Word to store.
 */
void FieldClass15AE70::func_slot50(u32 value)
{
    unk04 = value;
}

/**
 * @brief Return the stored resource source word.
 * @return Stored word.
 */
u32 FieldClass15AE70::func_slot54()
{
    return unk04;
}

/** @brief Return the nested display container. @return Stored container. */
LibObject178660* FieldClass15AE70::func_slot58()
{
    return unk10;
}

void func_00348530(void* object)
{
}

void func_00348540(void* object)
{
}

void func_00348550(void* object)
{
}

void func_00348560(void* object)
{
}

void func_00348570(void* object)
{
}

void func_00348580(void* object)
{
}

void func_00348590(void* object)
{
}

void func_003485A0(void* object)
{
}

void func_003485B0(void* object)
{
}

void func_003485C0(void* object)
{
}

void func_003485D0(void* object)
{
}

void func_003485E0(void* object)
{
}

void func_003485F0(void* object)
{
}

void func_00348600(void* object)
{
}

void func_00348610(void* object)
{
}

void func_00348620(void* object)
{
}

void func_00348630(void* object)
{
}

void func_00348640(void* object)
{
}

void func_00348650(void* object)
{
}

s32 func_00348660(void* object)
{
    return 0;
}

s32 func_00348670(void* object)
{
    return 0;
}

s32 func_00348680(void* object)
{
    return 0;
}

s32 func_00348690(void* object)
{
    return 0;
}

s32 func_003486A0(void* object)
{
    return 0;
}

s32 func_003486B0(void* object)
{
    return 0;
}

s32 func_003486C0(void* object)
{
    return 0;
}

s32 func_003486D0(void* object)
{
    return 0;
}

s32 func_003486E0(void* object)
{
    return 0;
}

s32 func_003486F0(void* object)
{
    return 0;
}

void func_00348700(void* object)
{
}

void func_00348710(void* object)
{
}

/** @brief Read the window byte at offset 0x0D. @return Stored unsigned byte. */
u8 FieldClass15AE70::func_slote8()
{
    return unk0d;
}

/** @brief Store the window byte at offset 0x0D. @param value Unsigned byte to store. */
void FieldClass15AE70::func_slotec(u8 value)
{
    unk0d = value;
}

void func_00348740(void* object)
{
}

void ShopSellAllConfirmWindow::func_slot74()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(2) == 1)
    {
        return;
    }
    if (choice->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
}

void ShopSellAllConfirmWindow::func_slot70()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(3) == 1)
    {
        return;
    }
    if (choice->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
}

/**
 * @brief Remove the confirmation window and restore its parent.
 * @param receiver Confirmation window.
 * @return Zero while input is locked, or two after returning to the parent.
 */
s32 shop_cancel_sell_all_confirmation(void* receiver)
{
    FieldClass15AE70* confirmation_window = static_cast<FieldClass15AE70*>(receiver);
    if (confirmation_window->func_slot28())
    {
        return 0;
    }
    ShopState* state = D_001B643C->callbacks->shop;
    state->func_00263F50(confirmation_window);
    state->func_00263C70(confirmation_window->func_slot44());
    return 2;
}

void shop_set_active_window(ShopState* object, void* value)
{
    object->unk20 = value;
}

/**
 * @brief Sell all unequipped instances of the selected item and return to the list.
 * @return Zero while locked, the alternate action result, or one after applying the choice.
 */
s32 ShopSellAllConfirmWindow::func_slotb0()
{
    ItemCreationAllocationRecord* unequipped_allocations[100];
    if (func_slot28())
    {
        return 0;
    }
    if (choice != 0 && choice->unk114 != 0)
    {
        return func_slotb4();
    }
    ShopState* state = D_001B643C->callbacks->shop;
    ShopTransaction* transaction = &state->transaction;
    s32 allocation_count = func_0040CF90(D_001B64F8, unequipped_allocations, state->selected_item);
    for (s32 i = 0; i < allocation_count; i++)
    {
        shop_sell_item(transaction, func_0040D890(unequipped_allocations[i]));
    }
    func_00112400(D_001B65F8, 6, 0, 0, 127, 64, 0);
    shop_refresh_sale_item_range(static_cast<ShopSaleItemWindow*>(func_slot44()));
    state->func_00263F50(this);
    state->func_00263F50(func_slot44());
    shop_set_mode(state, SHOP_MODE_SELL);
    state->selected_allocation = 0;
    return 1;
}

/**
 * @brief Create the paired-choice window and its displays.
 * @param associated Full resource source word.
 * @return One after creating the displays.
 */
s32 ShopSellAllConfirmWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 120.0f, 170.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 370.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    shop_append_panel(&unk14, panel);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 370.0f, 48.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopPanelColors colors = D_00351FC0;
    func_4C5590(panel, &colors.colors);
    shop_append_panel(&unk14, panel);
    LibObject178750* text = new (0) LibObject178750;
    text->func_004C7FE0(0.0f, 12.0f, 370.0f, 24.0f, static_cast<s32>(associated), SHOP_MSG_CONFIRM_SALE, 0);
    text->set_mode(1);
    func_004C6190(unk10, text);
    text = new (0) LibObject178750;
    text->func_004C7FE0(0.0f, 64.0f, 370.0f, 48.0f, static_cast<s32>(associated), SHOP_MSG_SELL_ALL_PROMPT, 0);
    text->set_mode(1);
    func_004C6190(unk10, text);
    yes_label = new (0) LibObject178750;
    no_label = new (0) LibObject178750;
    yes_label->func_004C7FE0(115.0f, 132.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_YES, 0);
    func_004C6190(unk10, yes_label);
    no_label->func_004C7FE0(210.0f, 132.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_NO, 0);
    func_004C6190(unk10, no_label);
    choice = new (0) FieldObject23CEA0;
    choice->func_0023CE80(2, 1);
    choice->func_0023CE60(93.0f, 0.0f);
    choice->unkF2 = 0;
    choice->func_0023CF50(1, 222.0f, 302.0f);
    shop_append_choice(&unk74, choice);
    if (choice->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
    return 1;
}

void ShopSellConfirmWindow::func_slot74()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(2) == 1)
    {
        return;
    }
    if (choice->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
}

void ShopSellConfirmWindow::func_slot70()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(3) == 1)
    {
        return;
    }
    if (choice->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
}

/**
 * @brief Remove the confirmation window and restore its parent.
 * @param receiver Confirmation window.
 * @return Zero while input is locked, or two after returning to the parent.
 */
s32 shop_cancel_sell_confirmation(void* receiver)
{
    FieldClass15AE70* confirmation_window = static_cast<FieldClass15AE70*>(receiver);
    if (confirmation_window->func_slot28())
    {
        return 0;
    }
    ShopState* state = D_001B643C->callbacks->shop;
    state->func_00263F50(confirmation_window);
    state->func_00263C70(confirmation_window->func_slot44());
    return 2;
}

/**
 * @brief Apply the selected record and update the remaining choices.
 * @return Zero while locked, the alternate action result, or one after applying the choice.
 */
s32 ShopSellConfirmWindow::func_slotb0()
{
    ItemCreationAllocationRecord* records[100];
    if (func_slot28())
    {
        return 0;
    }
    if (choice != 0 && choice->unk114 != 0)
    {
        return func_slotb4();
    }
    ShopState* state = D_001B643C->callbacks->shop;
    shop_sell_item(&state->transaction, func_0040D890(state->selected_allocation));
    func_00112400(D_001B65F8, 6, 0, 0, 127, 64, 0);
    shop_refresh_sale_item_range(static_cast<ShopSaleItemWindow*>(func_slot44()));
    state->func_00263F50(this);
    state->selected_allocation = 0;
    if (func_0040CF90(D_001B64F8, records, state->selected_item) == 0)
    {
        state->func_00263F50(func_slot44());
        shop_set_mode(state, SHOP_MODE_SELL);
    }
    else
    {
        state->func_00263C70(func_slot44());
    }
    return 1;
}

/**
 * @brief Create the two-option choice window and its displays.
 * @param associated Full resource source word.
 * @return One after creating the displays.
 */
s32 ShopSellConfirmWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 140.0f, 170.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    shop_append_panel(&unk14, panel);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 48.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopPanelColors colors = D_00351FB0;
    func_4C5590(panel, &colors.colors);
    shop_append_panel(&unk14, panel);
    LibObject178750* text = new (0) LibObject178750;
    func_004C7FE0(text, static_cast<s32>(associated), SHOP_MSG_CONFIRM_SALE, 0, 0.0f, 12.0f, 320.0f, 24.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    text = new (0) LibObject178750;
    func_004C7FE0(text, static_cast<s32>(associated), SHOP_MSG_SALE_PROMPT, 0, 0.0f, 64.0f, 320.0f, 48.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    yes_label = new (0) LibObject178750;
    no_label = new (0) LibObject178750;
    func_004C7FE0(yes_label, static_cast<s32>(associated), SHOP_MSG_YES, 0, 82.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, yes_label);
    func_004C7FE0(no_label, static_cast<s32>(associated), SHOP_MSG_NO, 0, 172.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, no_label);
    choice = new (0) FieldObject23CEA0;
    choice->func_0023CE80(2, 1);
    choice->func_0023CE60(90.0f, 0.0f);
    choice->unkF2 = 0;
    choice->func_0023CF50(1, 212.0f, 302.0f);
    shop_append_choice(&unk74, choice);
    if (choice->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
    return 1;
}

void ShopBuyConfirmWindow::func_slot5c()
{
    ShopState* state = D_001B643C->callbacks->shop;
    func_0023CEA0(choice, state->func_00261150() == this);
    D_001B643C->callbacks->shop->func_00261150();
}

void* shop_get_active_window(ShopState* object)
{
    return object->unk20;
}

void ShopBuyConfirmWindow::func_slot74()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(2) == 1)
    {
        return;
    }
    if (choice->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
}

void ShopBuyConfirmWindow::func_slot70()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(3) == 1)
    {
        return;
    }
    if (choice->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
}

/**
 * @brief Remove the confirmation window and restore its parent.
 * @param receiver Confirmation window.
 * @return Zero while input is locked, or two after returning to the parent.
 */
s32 shop_cancel_buy_confirmation(void* receiver)
{
    FieldClass15AE70* confirmation_window = static_cast<FieldClass15AE70*>(receiver);
    if (confirmation_window->func_slot28())
    {
        return 0;
    }
    ShopState* state = D_001B643C->callbacks->shop;
    state->func_00263F50(confirmation_window);
    state->func_00263C70(confirmation_window->func_slot44());
    return 2;
}

/**
 * @brief Complete the purchase and refresh the buy list.
 * @return Zero while locked, the alternate action result, or one after applying the choice.
 */
s32 ShopBuyConfirmWindow::func_slotb0()
{
    if (func_slot28())
    {
        return 0;
    }
    if (choice != 0 && choice->unk114 != 0)
    {
        return func_slotb4();
    }
    ShopState* state = D_001B643C->callbacks->shop;
    shop_complete_purchase(&state->transaction);
    func_00112400(D_001B65F8, 6, 0, 0, 127, 64, 0);
    state->func_00263F50(this);
    void* window = func_slot44();
    shop_refresh_buy_list(window, 0);
    state->func_00263C70(window);
    return 1;
}

/**
 * @brief Create the focus-sensitive choice window and its displays.
 * @param associated Full resource source word.
 * @return One after creating the displays.
 */
s32 ShopBuyConfirmWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 160.0f, 170.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    shop_append_panel(&unk14, panel);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 48.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopPanelColors colors = D_00351FA0;
    func_4C5590(panel, &colors.colors);
    shop_append_panel(&unk14, panel);
    LibObject178750* text = new (0) LibObject178750;
    func_004C7FE0(text, static_cast<s32>(associated), SHOP_MSG_CONFIRM_PURCHASE, 0, 0.0f, 12.0f, 320.0f, 24.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    text = new (0) LibObject178750;
    func_004C7FE0(text, static_cast<s32>(associated), SHOP_MSG_PURCHASE_PROMPT, 0, 0.0f, 64.0f, 320.0f, 48.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    yes_label = new (0) LibObject178750;
    no_label = new (0) LibObject178750;
    func_004C7FE0(yes_label, static_cast<s32>(associated), SHOP_MSG_YES, 0, 82.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, yes_label);
    func_004C7FE0(no_label, static_cast<s32>(associated), SHOP_MSG_NO, 0, 172.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, no_label);
    choice = new (0) FieldObject23CEA0;
    choice->func_0023CE80(2, 1);
    choice->func_0023CE60(80.0f, 0.0f);
    choice->unkF2 = 0;
    choice->func_0023CF50(0, 232.0f, 302.0f);
    choice->unkad = 0;
    shop_append_choice(&unk74, choice);
    if (choice->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
    return 1;
}

/**
 * @brief Update the first four display pairs and the optional list controls.
 * @param value Value stored in the display flags using its low byte.
 * @param selected Value tested for zero and stored in the optional control flags.
 */
void ShopSaleItemWindow::func_slot10c(u32 value, u32 selected)
{
    item_names[0]->unk3f = value;
    sale_prices[0]->unk3f = value;
    item_names[1]->unk3f = value;
    sale_prices[1]->unk3f = value;
    item_names[2]->unk3f = value;
    sale_prices[2]->unk3f = value;
    item_names[3]->unk3f = value;
    sale_prices[3]->unk3f = value;
    if (panel != 0)
    {
        panel->unk3f = 1;
    }
    if (FieldClass15AE60::unk04 != 0)
    {
        FieldClass15AE60::unk04->unk3f = selected;
        if (selected != 0)
        {
            LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_FOCUSED_OPACITY;
            selection_cursor->unk3c = 1;
        }
        else
        {
            LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_UNFOCUSED_OPACITY;
            selection_cursor->unk3c = 1;
        }
    }
    if (FieldClass15AE60::unk00 != 0)
    {
        FieldClass15AE60::unk00->unk3f = selected;
    }
}

/**
 * @brief Remove the sale-item window and return to the sell list.
 * @param object Sale-item window.
 * @return Always two.
 */
s32 shop_return_to_sell_list(void* object)
{
    ShopState* state = D_001B643C->callbacks->shop;
    state->func_00263F50(object);
    shop_set_mode(state, SHOP_MODE_SELL);
    return 2;
}

/**
 * @brief Open the sell-all confirmation when an item allocation is selected.
 * @param receiver Parent window to restore after confirmation.
 * @return Always one, including when no item allocation is selected.
 */
s32 shop_open_sell_all_confirmation(void* receiver)
{
    ShopState* state = D_001B643C->callbacks->shop;
    if (state->selected_allocation != 0)
    {
        ShopSellAllConfirmWindow* confirmation_window = new (0) ShopSellAllConfirmWindow;
        confirmation_window->func_slotf4(state->func_00263CC0());
        confirmation_window->func_slot40(receiver);
        state->func_00263FD0(confirmation_window);
        state->func_00263C70(confirmation_window);
    }
    return 1;
}

s32 shop_get_resource_slot(ShopState* object)
{
    return object->resource_slot;
}

/**
 * @brief Open the sale confirmation when an item allocation is selected.
 * @param receiver Parent window to restore after confirmation.
 * @return Always one, including when no item allocation is selected.
 */
s32 shop_open_sell_confirmation(void* receiver)
{
    ShopState* state = D_001B643C->callbacks->shop;
    if (state->selected_allocation != 0)
    {
        ShopSellConfirmWindow* confirmation_window = new (0) ShopSellConfirmWindow;
        confirmation_window->func_slotf4(state->func_00263CC0());
        confirmation_window->func_slot40(receiver);
        state->func_00263FD0(confirmation_window);
        state->func_00263C70(confirmation_window);
    }
    return 1;
}

/**
 * @brief Set cursor opacity for focus and show the selected unequipped instance's factors.
 */
void ShopSaleItemWindow::func_slot5c()
{
    ItemCreationAllocationRecord* unequipped_allocations[100];
    if (D_001B643C->callbacks->shop->func_00261150() == this)
    {
        LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_FOCUSED_OPACITY;
        selection_cursor->unk3c = 1;
    }
    else
    {
        LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_UNFOCUSED_OPACITY;
        selection_cursor->unk3c = 1;
        return;
    }
    func_002CD7C0(this);
    ShopState* state = D_001B643C->callbacks->shop;
    s32 allocation_count = func_0040CF90(D_001B64F8, unequipped_allocations, state->selected_item);
    s32 selected_allocation_index = FieldClass15AE60::unk24;
    if (allocation_count != 0 && selected_allocation_index >= 0)
    {
        s32 factor_count = 0;
        for (s32 i = 0; i < 8; i++)
        {
            u16 factor_id = func_0040D930(unequipped_allocations[selected_allocation_index], i);
            if (factor_id != SHOP_FACTOR_NONE && factor_id != SHOP_FACTOR_NOTHING)
            {
                LibObject172440* factor_display = factors[factor_count];
                factor_display->unkfc = factor_id;
                factor_display->unk3c = 1;
                factors[factor_count]->unk3f = 1;
                factor_count++;
            }
        }
        for (; factor_count < 8; factor_count++)
        {
            factors[factor_count]->unk3f = 0;
        }
        state->selected_allocation = unequipped_allocations[selected_allocation_index];
        LibObject172410* item_name = item_names[FieldClass15AE60::unk28];
        func_002CD8B0(this, item_name, item_name->unk94);
    }
    else
    {
        state->selected_allocation = 0;
        func_002CD8B0(this, 0, 0x808080);
    }
}

/**
 * @brief Position five item and sale-price rows and request their refresh.
 * @param scroll_offset Vertical offset added to the first row's position.
 */
void ShopSaleItemWindow::set_scroll_position(float scroll_offset)
{
    s32 row = 0;
    float row_y = scroll_offset + 16.0f;
    do
    {
        LibClass178600* item_name = this->item_names[row];
        item_name->unk18.unk04 = row_y;
        item_name->unk3c = 1;
        LibClass178600* sale_price_display = this->sale_prices[row];
        sale_price_display->unk18.unk04 = row_y;
        sale_price_display->unk3c = 1;
        row_y += 28.0f;
        row++;
    } while (row < 5);
}

/**
 * @brief Populate five item name and price rows from the selected item's unequipped allocations.
 * @param offset First allocation to display.
 */
void ShopSaleItemWindow::refresh_rows(s32 offset)
{
    ItemCreationAllocationRecord* unequipped_allocations[100];
    ShopState* state = D_001B643C->callbacks->shop;
    ShopTransaction* transaction = &state->transaction;
    s32 item_code = state->selected_item;
    for (s32 i = 99; i >= 0; i--)
    {
        unequipped_allocations[i] = 0;
    }
    this->FieldClass15AE60::unk88 = func_0040CF90(D_001B64F8, unequipped_allocations, item_code);
    for (s32 i = 0; i < 5; i++)
    {
        if (unequipped_allocations[offset + i] == 0)
        {
            this->item_names[i]->unk3d = 0;
            this->sale_prices[i]->unk3d = 0;
        }
        else
        {
            u16 item_identifier = item_code;
            u8 modification_number = unequipped_allocations[offset + i]->modification_number;
            LibObject172410* item_name = this->item_names[i];
            item_name->unkfc = item_identifier;
            item_name->unkfe = modification_number;
            item_name->unk3c = 1;
            set_shop_number(this->sale_prices[i], shop_get_sale_price(transaction, func_0040D890(unequipped_allocations[offset + i])));
            this->item_names[i]->unk3d = 1;
            this->sale_prices[i]->unk3d = 1;
        }
    }
}

/**
 * @brief Clamp sale-list scrolling and selection to the unequipped allocations.
 * @param object Sale list window.
 */
void shop_refresh_sale_item_range(ShopSaleItemWindow* object)
{
    ItemCreationAllocationRecord* unequipped_allocations[100];
    object->FieldClass15AE60::unk88 = 0;
    ShopState* state = D_001B643C->callbacks->shop;
    object->FieldClass15AE60::unk88 = func_0040CF90(D_001B64F8, unequipped_allocations, state->selected_item);
    s32 allocation_count = object->FieldClass15AE60::unk88;
    s32 visible_rows = allocation_count;
    if (visible_rows >= 4)
    {
        visible_rows = 4;
    }
    s32 first_allocation = object->FieldClass15AE60::unk22;
    if (allocation_count < first_allocation + 4)
    {
        first_allocation = allocation_count - 4;
    }
    if (first_allocation < 0)
    {
        first_allocation = 0;
    }
    s32 selected_row = object->FieldClass15AE60::unk28;
    if (selected_row >= visible_rows)
    {
        selected_row = visible_rows - 1;
    }
    if (selected_row < 0)
    {
        selected_row = 0;
    }
    func_002CE420(&static_cast<FieldClass15AE60&>(*object), 1, visible_rows, 378, 28);
    func_002CE220(&static_cast<FieldClass15AE60&>(*object), object->FieldClass15AE60::unk88, first_allocation, selected_row);
}

/**
 * @brief Configure an item-code widget and its display rectangle.
 * @param object Item name display.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Display width.
 * @param height Display height.
 * @param code Encoded item code stored in the widget.
 * @param variation Encoded variation stored in the widget.
 * @param flag Display flag.
 * @return One on success, or zero if initialization fails.
 */
extern "C" s32 func_00413F70(LibObject172410* object, float x, float y, float width, float height, u16 code, u8 variation, u8 flag);
/**
 * @brief Enable shrinking the item name to fit its display rectangle.
 * @param object Item name display.
 * @param enabled Nonzero to shrink oversized text along either axis.
 */
static inline void set_shop_item_name_auto_fit(LibObject172410* object, u8 enabled)
{
    object->unkfa = enabled;
    object->unk3c = 1;
}
/**
 * @brief Set the item name glyph spacing and request a refresh.
 * @param object Item name display.
 * @param spacing Extra horizontal advance per glyph before display scaling.
 */
static inline void set_shop_item_name_spacing(LibObject172410* object, float spacing)
{
    object->unk88 = spacing;
    object->unk3c = 1;
}
/**
 * @brief Configure the separator's display rectangle.
 * @param object Separator widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Display width.
 * @param height Display height.
 * @return One on success, or zero if its storage cannot be initialized.
 */
extern "C" s32 func_421170(ItemCreationClass172870* object, float x, float y, float width, float height);
/**
 * @brief Configure a detail-code widget and its display rectangle.
 * @param object Detail-code widget.
 * @param code Code to store.
 * @param variation Variation to store.
 * @param flag Display flag.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Display width.
 * @param height Display height.
 * @return One on success, or zero if initialization fails.
 */
extern "C" s32 func_4143F0(LibObject172440* object, u16 code, u8 variation, u8 flag, float x, float y, float width, float height);
/**
 * @brief Create the clipped sale item rows and factor displays.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 ShopSaleItemWindow::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 36.0f, 88.0f, 15);
    FieldClass15AE60::unk3c = 1;
    LibClass1746A0* clip_region = new (0) LibClass1746A0;
    LibClass1746A0* reset_clip = new (0) LibClass1746A0;
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 1, 0.0f, 0.0f, 568.0f, 340.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_44B570(clip_region, 16.0f, 16.0f, 560.0f, 110.0f);
    func_004C6190(unk10, clip_region);
    for (s32 row = 0; row < 5; row++)
    {
        item_names[row] = new (0) LibObject172410;
        func_00413F70(item_names[row], 30.0f, 16.0f + 28.0f * row, SHOP_ITEM_NAME_WIDTH, SHOP_ITEM_NAME_HEIGHT, 100, 0, 0);
        item_names[row]->set_scale(SHOP_ITEM_NAME_SCALE, SHOP_ITEM_NAME_SCALE);
        set_shop_item_name_auto_fit(item_names[row], 1);
        set_shop_item_name_spacing(item_names[row], -1.0f);
        item_names[row]->unk3f = 1;
        func_004C6190(unk10, item_names[row]);
        sale_prices[row] = new (0) LibObject174F20;
        sale_prices[row]->func_00464D90(490.0f, 12.0f + 30.0f * row, 28.0f, 24.0f, 0, 0, 1);
        func_004C6190(unk10, sale_prices[row]);
    }
    func_44B510(reset_clip, 1);
    func_004C6190(unk10, reset_clip);
    factor_separator = new (0) ItemCreationClass172870;
    func_421170(factor_separator, 24.0f, 135.0f, 520.0f, 4.0f);
    ItemCreationClass172870* separator = factor_separator;
    separator->unk50 = 0xDC6464;
    separator->unk3c = 1;
    func_004C6190(unk10, factor_separator);
    FieldRuntime* runtime = D_001B657C;
    runtime->factor_resource_slot = static_cast<s32>(associated);
    runtime->factor_base_key = SHOP_MSG_FACTORS + 1;
    for (s32 factor_index = 0; factor_index < 8; factor_index++)
    {
        factors[factor_index] = new (0) LibObject172440;
        func_4143F0(factors[factor_index], 0, 1, 0, 24.0f, 148 + 22 * factor_index, 0.0f, 0.0f);
        LibObject172440* factor_display = factors[factor_index];
        factor_display->unk80 = 0.8f;
        factor_display->unk84 = 0.8f;
        factor_display->unk3c = 1;
        factors[factor_index]->unk3f = 0;
        func_004C6190(unk10, factors[factor_index]);
    }
    LibObject178750* sell_all_help = new (0) LibObject178750;
    sell_all_help->func_004C7FE0(435.0f, 270.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_SELL_ALL_HELP, 0);
    func_004C6190(unk10, sell_all_help);
    LibObject178750* back_help = new (0) LibObject178750;
    back_help->func_004C7FE0(415.0f, 300.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_SELL_BACK_HELP, 0);
    func_004C6190(unk10, back_help);
    FieldClass15AE60::unk34 = 28.0f;
    FieldClass15AE60::unk38 = 28.0f;
    LibClass175030* selection_cursor = new (0) LibClass175030;
    FieldClass15AE60::unk04 = selection_cursor;
    func_00467360(static_cast<LibClass175030*>(FieldClass15AE60::unk04), 28.0f, 28.0f);
    func_004C6190(unk10, FieldClass15AE60::unk04);
    FieldClass15AE60::unk04->unk3f = 0;
    LibClass1725D0* scrollbar = new (0) LibClass1725D0;
    FieldClass15AE60::unk00 = scrollbar;
    func_41A930(static_cast<LibClass1725D0*>(FieldClass15AE60::unk00), 540.0f, 14.0f, 110.0f, 10.0f, 0.0f);
    FieldClass15AE60::unk00->unk3f = 0;
    func_004C6190(unk10, FieldClass15AE60::unk00);
    func_002CE420(&static_cast<FieldClass15AE60&>(*this), 1, 4, 378, 28);
    FieldClass15AE60::unk2b = 3;
    FieldClass15AE60::unk84 = 0;
    FieldClass15AE60::unk85 = 0;
    func_slot110(1);
    func_slot10c(1, 1);
    shop_refresh_sale_item_range(this);
    return 1;
}

/** @brief Store the list byte at offset 0x12C. @param value Unsigned byte to store. */
void FieldClass15AD40::func_slot110(u8 value)
{
    FieldClass15AE60::unk84 = value;
}

/**
 * @brief Update the first five item and sale-price rows and the optional list controls.
 * @param value Value stored in the display flags using its low byte.
 * @param selected Value tested for zero and stored in the optional control flags.
 */
void ShopSellListWindow::func_slot10c(u32 value, u32 selected)
{
    item_names[0]->unk3f = value;
    item_counts[0]->unk3f = value;
    item_names[1]->unk3f = value;
    item_counts[1]->unk3f = value;
    item_names[2]->unk3f = value;
    item_counts[2]->unk3f = value;
    item_names[3]->unk3f = value;
    item_counts[3]->unk3f = value;
    item_names[4]->unk3f = value;
    item_counts[4]->unk3f = value;
    if (panel != 0)
    {
        panel->unk3f = 1;
    }
    if (FieldClass15AE60::unk04 != 0)
    {
        FieldClass15AE60::unk04->unk3f = selected;
        if (selected != 0)
        {
            LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_FOCUSED_OPACITY;
            selection_cursor->unk3c = 1;
        }
        else
        {
            LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_UNFOCUSED_OPACITY;
            selection_cursor->unk3c = 1;
        }
    }
    if (FieldClass15AE60::unk00 != 0)
    {
        FieldClass15AE60::unk00->unk3f = selected;
    }
}

s32 shop_next_sell_category(void* object)
{
    shop_change_category(D_001B643C->callbacks->shop, 1);
    shop_refresh_sell_list(object, 1);
    return 1;
}

s32 shop_previous_sell_category(void* object)
{
    shop_change_category(D_001B643C->callbacks->shop, -1);
    shop_refresh_sell_list(object, 1);
    return 1;
}

/**
 * @brief Toggle between the item description and base parameters.
 * @param object Callback receiver; unused.
 * @return Always one.
 */
s32 shop_toggle_sell_parameters(void* object)
{
    ShopDescriptionWindow* description_window = D_001B643C->callbacks->shop->description_window;
    description_window->show_parameters = !description_window->show_parameters;
    return 1;
}

/**
 * @brief Return from the sell list to the action menu.
 * @param object Callback receiver; unused.
 * @return Always two.
 */
s32 shop_cancel_sell(void* object)
{
    shop_set_mode(D_001B643C->callbacks->shop, SHOP_MODE_ACTION);
    return 2;
}

s32 ShopSellListWindow::func_slotb0()
{
    ShopState* state = D_001B643C->callbacks->shop;
    if (FieldClass15AE60::unk88 != 0)
    {
        ShopSaleItemWindow* window = new (0) ShopSaleItemWindow;
        window->func_slot104(state->func_00263CC0());
        state->func_00263FD0(window);
        state->func_00263C70(window);
    }
    else
    {
        return 3;
    }
    return 1;
}

/** @brief Update the current catalog selection and its highlight. */
void ShopSellListWindow::func_slot5c()
{
    if (D_001B643C->callbacks->shop->func_00261150() == this)
    {
        LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_FOCUSED_OPACITY;
        selection_cursor->unk3c = 1;
    }
    else
    {
        LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_UNFOCUSED_OPACITY;
        selection_cursor->unk3c = 1;
        return;
    }
    func_002CD7C0(this);
    ShopState* state = D_001B643C->callbacks->shop;
    if (FieldClass15AE60::unk88 != 0)
    {
        state->selected_item = item_codes[FieldClass15AE60::unk24];
        LibObject172410* item_name = item_names[FieldClass15AE60::unk28];
        func_002CD8B0(this, item_name, item_name->unk94);
    }
    else
    {
        state->selected_item = -1;
        func_002CD8B0(this, 0, 0x808080);
    }
}

/**
 * @brief Position six item and inventory-count rows and request their refresh.
 * @param scroll_offset Vertical offset added to the first row's position.
 */
void ShopSellListWindow::set_scroll_position(float scroll_offset)
{
    s32 row = 0;
    float row_y = scroll_offset + 16.0f;
    do
    {
        LibClass178600* item_name = this->item_names[row];
        item_name->unk18.unk04 = row_y;
        item_name->unk3c = 1;
        LibClass178600* item_count_display = this->item_counts[row];
        item_count_display->unk18.unk04 = row_y;
        item_count_display->unk3c = 1;
        row_y += 28.0f;
        row++;
    } while (row < 6);
}

/**
 * @brief Populate six item name and inventory-count rows from the stored codes.
 * @param offset First stored code to display.
 */
void ShopSellListWindow::refresh_rows(s32 offset)
{
    for (s32 i = 0; i < 6; i++)
    {
        this->item_names[i]->unk3d = 0;
        this->item_counts[i]->unk3d = 0;
        s32 item_code = this->item_codes[offset + i];
        if (item_code != 0)
        {
            u16 item_identifier = item_code;
            ItemCreationCategoryRecord* item_record = shop_item_record(D_001B64F8, item_identifier);
            if (item_record != 0)
            {
                u8 player_invented = item_record->flags & SHOP_ITEM_PLAYER_INVENTED;
                u32 color = 0x808080;
                if (player_invented)
                {
                    color = 0x805050;
                }
                LibObject172410* item_name = this->item_names[i];
                item_name->unkfc = item_identifier;
                item_name->unkfe = 0;
                item_name->unk3c = 1;
                this->item_names[i]->set_color(color);
                this->item_names[i]->unk3d = 1;
                set_shop_number(this->item_counts[i], item_record->inventory_count);
                this->item_counts[i]->unk3d = 1;
            }
        }
    }
}

/**
 * @brief Find the catalog definition for a runtime category record.
 * @param record Runtime category record.
 * @return Definition selected by the record's catalog index.
 */
static inline ItemCreationCategoryDefinition* shop_definition(const ItemCreationCategoryRecord* record)
{
    return &D_001B64F0[record->catalog_index];
}

/**
 * @brief Read an item definition's category.
 * @param record Catalog definition.
 * @return Item category stored in the definition.
 */
static inline u8 shop_definition_category(const ItemCreationCategoryDefinition* record)
{
    return record->category;
}

/**
 * @brief Rebuild the sellable item list and clamp its scrolling and selection.
 * @param receiver Sell list window.
 * @param reset_selection Reset scrolling and selection to the first item when nonzero.
 */
void shop_refresh_sell_list(void* receiver, u8 reset_selection)
{
    ShopSellListWindow* object = static_cast<ShopSellListWindow*>(receiver);
    object->FieldClass15AE60::unk88 = 0;
    ShopState* state = D_001B643C->callbacks->shop;
    s32 item_count = 0;
    for (s32 item_code = 1; item_code <= 750; item_code++)
    {
        ItemCreationCategoryRecord* item_record = shop_item_record(D_001B64F8, item_code);
        if (item_record == 0)
        {
            continue;
        }
        ItemCreationCategoryDefinition* definition = shop_definition(item_record);
        if (definition->unsellable || item_record->inventory_count == 0)
        {
            continue;
        }
        if (state->category == SHOP_CATEGORY_ALL)
        {
            object->item_codes[item_count++] = item_code;
        }
        else
        {
            u8 item_category = shop_definition_category(definition);
            if (item_category == state->category)
            {
                object->item_codes[item_count++] = item_code;
            }
        }
    }
    object->FieldClass15AE60::unk88 = item_count;
    for (; item_count < 750; item_count++)
    {
        object->item_codes[item_count] = 0;
    }
    item_count = object->FieldClass15AE60::unk88;
    s32 visible_rows = item_count >= 5 ? 5 : item_count;
    s32 first_item = object->FieldClass15AE60::unk22;
    if (item_count < first_item + 5)
    {
        first_item = item_count - 5;
    }
    if (first_item < 0)
    {
        first_item = 0;
    }
    s32 selected_row = object->FieldClass15AE60::unk28;
    if (selected_row >= visible_rows)
    {
        selected_row = visible_rows - 1;
    }
    if (selected_row < 0)
    {
        selected_row = 0;
    }
    if (reset_selection)
    {
        selected_row = 0;
        first_item = 0;
    }
    func_002CE420(&static_cast<FieldClass15AE60&>(*object), 1, visible_rows, 378, 28);
    func_002CE220(&static_cast<FieldClass15AE60&>(*object), object->FieldClass15AE60::unk88, first_item, selected_row);
}

/**
 * @brief Create the clipped inventory rows and scrolling controls.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 ShopSellListWindow::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1800, 16.0f, 260.0f, 0.0f);
    FieldClass15AE60::unk3c = 1;
    LibClass1746A0* clip_region = new (0) LibClass1746A0;
    LibClass1746A0* reset_clip = new (0) LibClass1746A0;
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 1, 0.0f, 0.0f, 608.0f, 178.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_44B570(clip_region, 16.0f, 16.0f, 580.0f, 140.0f);
    func_004C6190(unk10, clip_region);
    for (s32 row = 0; row < 6; row++)
    {
        item_names[row] = new (0) LibObject172410;
        func_00413F70(item_names[row], 30.0f, 16.0f + 28.0f * row, SHOP_ITEM_NAME_WIDTH, SHOP_ITEM_NAME_HEIGHT, 100, 0, 0);
        item_names[row]->set_scale(SHOP_ITEM_NAME_SCALE, SHOP_ITEM_NAME_SCALE);
        set_shop_item_name_auto_fit(item_names[row], 1);
        set_shop_item_name_spacing(item_names[row], -1.0f);
        item_names[row]->unk3f = 1;
        func_004C6190(unk10, item_names[row]);
        item_counts[row] = new (0) LibObject174F20;
        item_counts[row]->func_00464D90(544.0f, 12.0f + 30.0f * row, 28.0f, 24.0f, 0, 0, 1);
        func_004C6190(unk10, item_counts[row]);
    }
    func_44B510(reset_clip, 1);
    func_004C6190(unk10, reset_clip);
    FieldClass15AE60::unk34 = 28.0f;
    FieldClass15AE60::unk38 = 28.0f;
    LibClass175030* selection_cursor = new (0) LibClass175030;
    FieldClass15AE60::unk04 = selection_cursor;
    func_00467360(static_cast<LibClass175030*>(FieldClass15AE60::unk04), 28.0f, 28.0f);
    FieldClass15AE60::unk04->unk3f = 0;
    func_004C6190(unk10, FieldClass15AE60::unk04);
    LibClass1725D0* scrollbar = new (0) LibClass1725D0;
    FieldClass15AE60::unk00 = scrollbar;
    func_41A930(static_cast<LibClass1725D0*>(FieldClass15AE60::unk00), 580.0f, 14.0f, 145.0f, 10.0f, 0.0f);
    func_004C6190(unk10, FieldClass15AE60::unk00);
    FieldClass15AE60::unk00->unk3f = 0;
    func_002CE420(&static_cast<FieldClass15AE60&>(*this), 1, 5, 378, 28);
    FieldClass15AE60::unk2b = 3;
    FieldClass15AE60::unk84 = 0;
    FieldClass15AE60::unk85 = 0;
    func_slot10c(0, 0);
    return 1;
}

void ShopItemDetailWindow::func_slot5c()
{
    if (closing != 0 && func_002FD480(item_model))
    {
        if (item_model != 0)
        {
            item_model->func_001DD7B0();
            item_model = 0;
        }
        func_002CFE10(D_001B643C->callbacks, this);
        shop_set_mode(D_001B643C->callbacks->shop, SHOP_MODE_BUY);
        closing = 0;
    }
}

/**
 * @brief Request cancellation of the attached status window when present.
 * @return Always two.
 */
s32 ShopItemDetailWindow::func_slotb4()
{
    if (item_model != 0)
    {
        func_002FD940(item_model);
        closing = 1;
    }
    return 2;
}

/**
 * @brief Configure the packed allocation record and its detail values.
 * @param record Allocation record to configure.
 * @param item_code One-based item code.
 * @param modification_number Item type's factor-change count, or zero for an unmodified item.
 * @param factors Eight factor codes, or null for catalog defaults.
 * @param new_item Mark the item as new in inventory lists.
 * @param suppress_allocation_id Suppress the resident allocation identifier when the record checksum is valid.
 */
extern "C" void func_0040D2E0(ItemCreationAllocationRecord* record, u16 item_code, u8 modification_number, const u16* factors, bool new_item, bool suppress_allocation_id);

/**
 * @brief Load a text resource into the multiline text widget.
 * @param object Multiline text widget.
 * @param slot Resource slot index.
 * @param key Resource key.
 * @param mode Drawing mode mask.
 * @param flag Flag whose low byte is stored by the widget.
 * @return Setup status.
 */
extern "C" s32 func_0045F690(LibObject174D90* object, u32 slot, s32 key, u32 mode, u32 flag);

/**
 * @brief Reset a temporary allocation and initialize its definition and factors.
 * @param allocation Allocation record to initialize.
 * @param item Inventory item record supplying the catalog index.
 * @param factors Eight factor codes, or null for catalog defaults.
 */
static inline void initialize_shop_item_allocation(ItemCreationAllocationRecord* allocation, const ItemCreationCategoryRecord* item, const u16* factors)
{
    allocation->reset(0);
    func_0040D2E0(allocation, item->catalog_index + 1, 0, factors, false, true);
}

/** Five vertical row positions; the last places the detail window footer. */
struct ShopFooterPositions
{
    float values[5];
};
extern "C" ShopFooterPositions D_00351F80;

/** Partial saved display settings used to frame the item model preview. */
struct ShopDisplaySettings
{
    u8 unk00[0x18C];
    u8 widescreen;
};

/**
 * @brief Read the selected item code.
 * @return Item code from the shop state.
 */
static inline s32 shop_selected_item()
{
    return D_001B643C->callbacks->shop->selected_item;
}

/**
 * @brief Select the item name by its catalog code and request a refresh.
 * @param object Item name display.
 * @param code One-based catalog code selecting the item name.
 */
static inline void set_shop_item_name_code(LibObject172410* object, u16 code)
{
    object->unkfc = code;
    object->unkfe = 0;
    object->unk3c = 1;
}

/**
 * @brief Create the item description, factor list and model.
 * @param associated Resource source word.
 * @return Always one.
 */
s32 ShopItemDetailWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 2200, 28.0f, 87.0f, 0.0f);
    detail_container = new (0) LibObject178660;
    func_004C6510(detail_container, 5, 0, 0, 28.0f, 87.0f, 0.0f);
    func_00465B20(D_001B657C, detail_container);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 1, 0.0f, 0.0f, 584.0f, 369.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_004C4AB0(panel, 1500.0f);
    s32 item_code = shop_selected_item();
    ItemCreationAllocationRecord preview_allocation __attribute__((aligned(16)));
    preview_allocation.reset(0);
    ItemCreationCategoryRecord* item_record = shop_item_record(D_001B64F8, item_code);
    initialize_shop_item_allocation(&preview_allocation, item_record, 0);
    category_label = new (0) LibObject178750;
    category_label->func_004C7FE0(16.0f, 12.0f, 0.0f, 0.0f, associated, shop_definition_category(&D_001B64F0[preview_allocation.definition_index()]) + SHOP_MSG_WEAPONS, 0);
    LibObject178750* category_heading = category_label;
    category_heading->unk88 = -1.0f;
    category_heading->unk3c = 1;
    category_label->set_scale(0.8f, 0.8f);
    category_label->set_color(0x805050);
    category_label->set_mode(0);
    func_004C6190(unk10, category_label);
    item_name = new (0) LibObject172410;
    func_00413F70(item_name, 24.0f, 34.0f, 0.0f, 0.0f, associated, item_code + SHOP_MSG_ITEM_NAMES, 0);
    set_shop_item_name_spacing(item_name, -1.0f);
    item_name->set_scale(1.2f, 1.2f);
    set_shop_item_name_code(item_name, preview_allocation.definition_index() + 1);
    func_004C6190(unk10, item_name);
    factor_separator = new (0) ItemCreationClass172870;
    func_421170(factor_separator, 8.0f, 66.0f, 568.0f, 3.0f);
    ItemCreationClass172870* separator = factor_separator;
    separator->unk50 = 0x606060;
    separator->unk3c = 1;
    func_004C6190(unk10, factor_separator);
    description_text = new (0) LibObject178750;
    description_text->func_004C7FE0(24.0f, 78.0f, 534.0f, 66.0f, static_cast<s32>(associated), item_code + SHOP_MSG_DETAIL_DESCRIPTIONS, 0);
    description_text->set_mode(0);
    description_text->set_vertical_alignment(1);
    LibObject178750* description = description_text;
    description->unk88 = -1.0f;
    description->unk3c = 1;
    description_text->set_scale(0.9f, 0.9f);
    func_004C6190(detail_container, description_text);
    factor_heading = new (0) LibObject178750;
    factor_heading->func_004C7FE0(16.0f, 150.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_FACTOR, 0);
    factor_heading->set_scale(0.8f, 0.8f);
    factor_heading->set_color(0x805050);
    LibObject178750* factor_heading_widget = factor_heading;
    factor_heading_widget->unk88 = -1.0f;
    factor_heading_widget->unk3c = 1;
    func_004C6190(unk10, factor_heading);
    FieldRuntime* runtime = D_001B657C;
    runtime->factor_resource_slot = static_cast<s32>(associated);
    runtime->factor_base_key = SHOP_MSG_FACTORS + 1;
    for (s32 i = 0; i < 8; i++)
    {
        factors[i] = new (0) LibObject172440;
        func_4143F0(factors[i], 0, 1, 0, 26.0f, 172.0f + 23 * i, 0.0f, 0.0f);
        LibObject172440* factor_display = factors[i];
        factor_display->unk88 = -1.0f;
        factor_display->unk3c = 1;
        factors[i]->set_scale(0.8f, 0.8f);
        factors[i]->unk3f = 0;
        func_004C6190(detail_container, factors[i]);
    }
    s32 factor_count = 0;
    for (s32 i = 0; i < 8; i++)
    {
        u16 factor_id = func_0040D930(&preview_allocation, i);
        if (factor_id != SHOP_FACTOR_NONE && factor_id != SHOP_FACTOR_NOTHING)
        {
            LibObject172440* factor_display = factors[factor_count];
            factor_display->unkfc = factor_id;
            factor_display->unk3c = 1;
            factors[factor_count]->unk3f = 1;
            factor_count++;
        }
    }
    ShopFooterPositions positions = D_00351F80;
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(12.0f, positions.values[4] - 8.0f, 560.0f, 24.0f, static_cast<s32>(associated), SHOP_MSG_BACK_HELP, 0);
    footer->set_mode(2);
    func_004C6190(detail_container, footer);
    s32 model_resource_key = static_cast<u16>(D_001B64F0[item_record->catalog_index].model_index) + 0x88;
    closing = 0;
    item_model = new (0) FieldClass15BB90;
    func_002FDC00(item_model, model_resource_key);
    item_model->unk5b = 1;
    func_002FD220(item_model, D_001B643C->field_camera);
    func_002FD1D0(item_model);
    if (reinterpret_cast<ShopDisplaySettings*>(func_00101440(func_00101290(func_0010D8E0()), 1))->widescreen != 0)
    {
        func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(item_model), 0.5235988f, 600.0f, 0.34906584f, 120.0f, 35.0f);
    }
    else
    {
        func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(item_model), 0.5235988f, 500.0f, 0.34906584f, 90.0f, 50.0f);
    }
    D_001B6614->func_004D74F0(item_model, reinterpret_cast<void*>(-1));
    return 1;
}

/** @brief Destroy the list receiver and its contained sentinel. */
LibClass178A70::~LibClass178A70()
{
}

void ShopItemDetailWindow::func_slot0c()
{
    detail_container->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

ShopItemDetailWindow::~ShopItemDetailWindow()
{
    if (panel != 0)
    {
        func_004C4A90(panel);
    }
}

ShopItemDetailWindow::ShopItemDetailWindow()
{
    category_label = 0;
    item_name = 0;
    factor_separator = 0;
    description_text = 0;
    factor_heading = 0;
    factors[0] = 0;
    factors[1] = 0;
    factors[2] = 0;
    factors[3] = 0;
    factors[4] = 0;
    factors[5] = 0;
    factors[6] = 0;
    factors[7] = 0;
    panel = 0;
    FieldClass15AE70();
}

/**
 * @brief Update the first five rows of six display columns and the optional controls.
 * @param value Value stored in the display flags using its low byte.
 * @param selected Value tested for zero and stored in the optional control flags.
 */
void ShopBuyListWindow::func_slot10c(u32 value, u32 selected)
{
    s32 i = 0;
    value &= 0xFF;
    for (; i < 5; i++)
    {
        item_names[i]->unk3f = value;
        price_displays[i]->unk3f = value;
        multiply_labels[i]->unk3f = value;
        quantity_displays[i]->unk3f = value;
        separator_labels[i]->unk3f = value;
        buy_limit_displays[i]->unk3f = value;
    }
    if (panel != 0)
    {
        panel->unk3f = 1;
    }
    if (FieldClass15AE60::unk04 != 0)
    {
        FieldClass15AE60::unk04->unk3f = selected;
        if (selected != 0)
        {
            LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_FOCUSED_OPACITY;
            selection_cursor->unk3c = 1;
        }
        else
        {
            LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_UNFOCUSED_OPACITY;
            selection_cursor->unk3c = 1;
        }
    }
    if (FieldClass15AE60::unk00 != 0)
    {
        FieldClass15AE60::unk00->unk3f = selected;
    }
}

void ShopBuyListWindow::func_slot74()
{
    ShopState* state = D_001B643C->callbacks->shop;
    ShopTransaction* transaction = &state->transaction;
    if (shop_increase_quantity(transaction, shop_get_category_item(transaction, state->category, FieldClass15AE60::unk24)))
    {
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
        refresh_rows(FieldClass15AE60::unk22);
    }
    else if (error_sound_timer < 0)
    {
        func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
        error_sound_timer = 30;
    }
}

void ShopBuyListWindow::func_slot70()
{
    ShopState* state = D_001B643C->callbacks->shop;
    ShopTransaction* transaction = &state->transaction;
    if (shop_decrease_quantity(transaction, shop_get_category_item(transaction, state->category, FieldClass15AE60::unk24)))
    {
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
        refresh_rows(FieldClass15AE60::unk22);
    }
    else if (error_sound_timer < 0)
    {
        func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
        error_sound_timer = 30;
    }
}

s32 shop_next_buy_category(void* object)
{
    shop_change_category(D_001B643C->callbacks->shop, 1);
    shop_refresh_buy_list(object, 0);
    return 1;
}

s32 shop_previous_buy_category(void* object)
{
    shop_change_category(D_001B643C->callbacks->shop, -1);
    shop_refresh_buy_list(object, 0);
    return 1;
}

/**
 * @brief Toggle between the item description and base parameters.
 * @param object Callback receiver; unused.
 * @return Always one.
 */
s32 shop_toggle_parameters(void* object)
{
    ShopDescriptionWindow* description_window = D_001B643C->callbacks->shop->description_window;
    description_window->show_parameters = !description_window->show_parameters;
    return 1;
}

/**
 * @brief Create and activate the selected item detail window.
 * @return Always one.
 */
s32 shop_open_item_details(void)
{
    ShopState* state = D_001B643C->callbacks->shop;
    ShopItemDetailWindow* detail_window = new (0) ShopItemDetailWindow;
    detail_window->func_slotf4(state->func_00263CC0());
    state->func_00263FD0(detail_window);
    state->func_00263C70(detail_window);
    return 1;
}

/**
 * @brief Clear the pending purchases and return to the action menu.
 * @param object Callback receiver; unused.
 * @return Always two.
 */
s32 shop_cancel_purchase(void* object)
{
    ShopState* state = D_001B643C->callbacks->shop;
    shop_clear_purchases(&state->transaction);
    shop_set_mode(state, SHOP_MODE_ACTION);
    return 2;
}

/**
 * @brief Open the purchase confirmation when pending quantities are nonzero.
 * @param receiver Parent window to restore after confirmation.
 * @return One when opened, or three when no quantities are pending.
 */
s32 shop_open_buy_confirmation(void* receiver)
{
    ShopState* state = D_001B643C->callbacks->shop;
    if ((u16)(state->transaction.pending_unsellable_count + state->transaction.pending_sellable_count))
    {
        ShopBuyConfirmWindow* confirmation_window = new (0) ShopBuyConfirmWindow;
        confirmation_window->func_slotf4(state->func_00263CC0());
        confirmation_window->func_slot40(receiver);
        state->func_00263FD0(confirmation_window);
        state->func_00263C70(confirmation_window);
    }
    else
    {
        return 3;
    }
    return 1;
}

/** @brief Update the current bucket selection, highlight, and countdown. */
void ShopBuyListWindow::func_slot5c()
{
    if (D_001B643C->callbacks->shop->func_00261150() == this)
    {
        LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_FOCUSED_OPACITY;
        selection_cursor->unk3c = 1;
    }
    else
    {
        LibClass175030* selection_cursor = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        selection_cursor->LibMovementState::unk30 = SHOP_CURSOR_UNFOCUSED_OPACITY;
        selection_cursor->unk3c = 1;
        return;
    }
    func_002CD7C0(this);
    ShopState* state = D_001B643C->callbacks->shop;
    state->selected_item = shop_get_category_item(&state->transaction, state->category, FieldClass15AE60::unk24);
    if (FieldClass15AE60::unk24 >= 0)
    {
        LibObject172410* item_name = item_names[FieldClass15AE60::unk28];
        func_002CD8B0(this, item_name, item_name->unk94);
    }
    if (error_sound_timer >= 0)
    {
        error_sound_timer--;
    }
}

/**
 * @brief Read the number of items in a shop category.
 * @param transaction Shop transaction.
 * @param category Item category.
 * @return Entry count, or zero when the index is out of range.
 */
static inline s32 shop_category_item_count(ShopTransaction* transaction, u8 category)
{
    if (category < 8)
    {
        return transaction->category_items[category].count;
    }
    return 0;
}

/**
 * @brief Set the buy list range for the selected category and clamp its selection.
 * @param receiver Buy list window.
 * @param reset_selection Reset scrolling and selection to the first item when nonzero.
 */
void shop_refresh_buy_list(void* receiver, u8 reset_selection)
{
    ShopBuyListWindow* object = static_cast<ShopBuyListWindow*>(receiver);
    object->FieldClass15AE60::unk88 = 0;
    ShopState* state = D_001B643C->callbacks->shop;
    ShopTransaction* transaction = &state->transaction;
    object->FieldClass15AE60::unk88 = shop_category_item_count(transaction, state->category);
    s32 item_count = object->FieldClass15AE60::unk88;
    s32 visible_rows = item_count >= 5 ? 5 : item_count;
    s32 first_item = object->FieldClass15AE60::unk22;
    if (item_count < first_item + 5)
    {
        first_item = item_count - 5;
    }
    if (first_item < 0)
    {
        first_item = 0;
    }
    s32 selected_row = object->FieldClass15AE60::unk28;
    if (selected_row >= visible_rows)
    {
        selected_row = visible_rows - 1;
    }
    if (selected_row < 0)
    {
        selected_row = 0;
    }
    if (reset_selection)
    {
        selected_row = 0;
        first_item = 0;
    }
    func_002CE420(&static_cast<FieldClass15AE60&>(*object), 1, visible_rows, 378, 28);
    func_002CE220(&static_cast<FieldClass15AE60&>(*object), object->FieldClass15AE60::unk88, first_item, selected_row);
}

/**
 * @brief Position six purchase rows and request their refresh.
 * @param scroll_offset Vertical offset added to the first row's position.
 */
void ShopBuyListWindow::set_scroll_position(float scroll_offset)
{
    s32 row = 0;
    float row_y = scroll_offset + 16.0f;
    do
    {
        LibClass178600* row_widget = this->item_names[row];
        row_widget->unk18.unk04 = row_y;
        row_widget->unk3c = 1;
        row_widget = this->price_displays[row];
        row_widget->unk18.unk04 = row_y;
        row_widget->unk3c = 1;
        row_widget = this->multiply_labels[row];
        row_widget->unk18.unk04 = row_y;
        row_widget->unk3c = 1;
        row_widget = this->quantity_displays[row];
        row_widget->unk18.unk04 = row_y;
        row_widget->unk3c = 1;
        row_widget = this->separator_labels[row];
        row_widget->unk18.unk04 = row_y;
        row_widget->unk3c = 1;
        row_widget = this->buy_limit_displays[row];
        row_widget->unk18.unk04 = row_y;
        row_widget->unk3c = 1;
        row_y += 28.0f;
        row++;
    } while (row < 6);
}

/**
 * @brief Read the pending purchase quantity for an item.
 * @param transaction Shop transaction.
 * @param code One-based item code.
 * @return Purchase quantity, or zero when the code is out of range.
 */
static inline u8 shop_purchase_quantity(ShopTransaction* transaction, s32 code)
{
    u8 result;
    u8 valid = code >= 1 && code < 751;
    if (valid)
    {
        result = transaction->purchase_quantities[code - 1];
    }
    else
    {
        result = 0;
    }
    return result;
}

/**
 * @brief Refresh buy-list prices, purchase quantities and purchase limits.
 * @param offset First category entry to display.
 */
void ShopBuyListWindow::refresh_rows(s32 offset)
{
    ShopState* state = D_001B643C->callbacks->shop;
    ShopTransaction* transaction = &state->transaction;
    for (s32 i = 0; i < 6; i++)
    {
        this->item_names[i]->unk3d = 0;
        this->price_displays[i]->unk3d = 0;
        this->quantity_displays[i]->unk3d = 0;
        this->multiply_labels[i]->unk3d = 0;
        this->separator_labels[i]->unk3d = 0;
        this->buy_limit_displays[i]->unk3d = 0;
        if (offset + i < shop_category_item_count(transaction, state->category))
        {
            s32 item_code = shop_get_category_item(transaction, state->category, offset + i);
            ItemCreationCategoryRecord* item_record = shop_item_record(D_001B64F8, item_code);
            if (item_record != 0)
            {
                u8 player_invented = item_record->flags & SHOP_ITEM_PLAYER_INVENTED;
                u32 color = 0x808080;
                if (player_invented)
                {
                    color = 0x808050;
                }
                LibObject172410* item_name = this->item_names[i];
                item_name->unkfc = item_code;
                item_name->unkfe = 0;
                item_name->unk3c = 1;
                this->item_names[i]->set_color(color);
                set_shop_number(this->price_displays[i], shop_get_buy_price(transaction, item_code));
                set_shop_number(this->quantity_displays[i], shop_purchase_quantity(transaction, item_code));
                set_shop_number(this->buy_limit_displays[i], shop_get_buy_limit(transaction, item_code));
                this->item_names[i]->unk3d = 1;
                this->price_displays[i]->unk3d = 1;
                this->quantity_displays[i]->unk3d = 1;
                this->separator_labels[i]->unk3d = 1;
                this->multiply_labels[i]->unk3d = 1;
                this->buy_limit_displays[i]->unk3d = 1;
            }
        }
    }
}

/**
 * @brief Create the clipped purchase rows and scrolling controls.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 ShopBuyListWindow::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1800, 16.0f, 260.0f, 0.0f);
    FieldClass15AE60::unk3c = 1;
    LibClass1746A0* clip_region = new (0) LibClass1746A0;
    LibClass1746A0* reset_clip = new (0) LibClass1746A0;
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 1, 0.0f, 0.0f, 608.0f, 168.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_44B570(clip_region, 16.0f, 16.0f, 580.0f, 140.0f);
    func_004C6190(unk10, clip_region);
    for (s32 row = 0; row < 6; row++)
    {
        item_names[row] = new (0) LibObject172410;
        func_00413F70(item_names[row], 30.0f, 16.0f + 28.0f * row, SHOP_ITEM_NAME_WIDTH, SHOP_ITEM_NAME_HEIGHT, 100, 0, 0);
        item_names[row]->set_scale(SHOP_ITEM_NAME_SCALE, SHOP_ITEM_NAME_SCALE);
        set_shop_item_name_auto_fit(item_names[row], 1);
        set_shop_item_name_spacing(item_names[row], -1.0f);
        item_names[row]->unk3f = 1;
        func_004C6190(unk10, item_names[row]);
        price_displays[row] = new (0) LibObject174F20;
        float row_y = 12.0f + 30.0f * row;
        price_displays[row]->func_00464D90(360.0f, row_y, 126.0f, 24.0f, 0, 0, 0);
        func_004C6190(unk10, price_displays[row]);
        multiply_labels[row] = new (0) LibObject178750;
        multiply_labels[row]->func_004C7FE0(486.0f, row_y, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_MULTIPLY, 1);
        func_004C6190(unk10, multiply_labels[row]);
        quantity_displays[row] = new (0) LibObject174F20;
        quantity_displays[row]->func_00464D90(506.0f, row_y, 28.0f, 24.0f, 0, 0, 0);
        func_004C6190(unk10, quantity_displays[row]);
        separator_labels[row] = new (0) LibObject178750;
        separator_labels[row]->func_004C7FE0(534.0f, row_y, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_QUANTITY_SEPARATOR, 1);
        func_004C6190(unk10, separator_labels[row]);
        buy_limit_displays[row] = new (0) LibObject174F20;
        buy_limit_displays[row]->func_00464D90(544.0f, row_y, 28.0f, 24.0f, 0, 0, 1);
        func_004C6190(unk10, buy_limit_displays[row]);
    }
    func_44B510(reset_clip, 1);
    func_004C6190(unk10, reset_clip);
    FieldClass15AE60::unk34 = 28.0f;
    FieldClass15AE60::unk38 = 28.0f;
    LibClass175030* selection_cursor = new (0) LibClass175030;
    FieldClass15AE60::unk04 = selection_cursor;
    func_00467360(static_cast<LibClass175030*>(FieldClass15AE60::unk04), 28.0f, 28.0f);
    func_004C6190(unk10, FieldClass15AE60::unk04);
    FieldClass15AE60::unk04->unk3f = 0;
    LibClass1725D0* scrollbar = new (0) LibClass1725D0;
    FieldClass15AE60::unk00 = scrollbar;
    func_41A930(static_cast<LibClass1725D0*>(FieldClass15AE60::unk00), 580.0f, 14.0f, 145.0f, 10.0f, 0.0f);
    func_004C6190(unk10, FieldClass15AE60::unk00);
    FieldClass15AE60::unk00->unk3f = 0;
    func_002CE420(&static_cast<FieldClass15AE60&>(*this), 1, 5, 378, 28);
    FieldClass15AE60::unk2b = 3;
    FieldClass15AE60::unk84 = 0;
    FieldClass15AE60::unk85 = 0;
    func_slot10c(0, 0);
    return 1;
}

ShopBuyListWindow::ShopBuyListWindow()
{
    for (s32 i = 0; i < 6; i++)
    {
        item_names[i] = 0;
        price_displays[i] = 0;
        quantity_displays[i] = 0;
        buy_limit_displays[i] = 0;
    }
    error_sound_timer = 0;
    FieldClass15AD40();
}

/**
 * @brief Show current fol and the balance after the pending purchase or selected sale.
 * @param object Fol display window.
 */
void shop_update_fol(ShopValueDisplay* object)
{
    s32 current_fol;
    ShopState* state = D_001B643C->callbacks->shop;
    ResidentCheckedRecord* saved_record = D_001B643C->saved_record;
    ShopTransaction* transaction = &state->transaction;
    ItemCreationAllocationRecord* allocation = state->selected_allocation;
    u16 checksum = saved_record->checksum;
    const u8* end = (const u8*)&saved_record->checksum;
    if (checksum != func_00457470(saved_record->checksum_seed, (u8*)saved_record + 0x26, end - ((const u8*)saved_record + 0x26)))
    {
        current_fol = 0;
    }
    else
    {
        current_fol = saved_record->encoded_fol ^ 0x7CE3C7F7;
    }
    if (allocation != 0)
    {
        s32 sale_price = shop_get_sale_price(transaction, func_0040D890(allocation));
        s32 remaining_fol = current_fol + sale_price;
        set_shop_number(object->transaction_total, sale_price);
        if (remaining_fol > 99999999)
        {
            remaining_fol = 99999999;
        }
        set_shop_number(object->remaining_fol, remaining_fol);
    }
    else
    {
        s32 purchase_total = transaction->purchase_total;
        s32 remaining_fol = current_fol - purchase_total;
        set_shop_number(object->transaction_total, purchase_total);
        if (remaining_fol < 0)
        {
            remaining_fol = 0;
        }
        set_shop_number(object->remaining_fol, remaining_fol);
    }
    set_shop_number(object->current_fol, current_fol);
}

s32 ShopFolWindow::func_slotf4(u32 associated)
{
    if (associated == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot14(associated, 0, 9, 2000, 16.0f, 428.0f, 0.0f);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 608.0f, 40.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* label = new (0) LibObject178750;
    label->func_004C7FE0(24.0f, 8.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_CURRENT_FOL, 1);
    func_004C6190(unk10, label);
    label = new (0) LibObject178750;
    label->func_004C7FE0(204.0f, 8.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_TOTAL_FOL, 1);
    func_004C6190(unk10, label);
    label = new (0) LibObject178750;
    label->func_004C7FE0(396.0f, 8.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_REMAINING_FOL, 1);
    func_004C6190(unk10, label);
    current_fol = new (0) LibObject174F20;
    transaction_total = new (0) LibObject174F20;
    remaining_fol = new (0) LibObject174F20;
    current_fol->func_00464D90(64.0f, 8.0f, 126.0f, 24.0f, 0, 0, 0);
    func_004C6190(unk10, current_fol);
    transaction_total->func_00464D90(260.0f, 8.0f, 126.0f, 24.0f, 0, 0, 0);
    func_004C6190(unk10, transaction_total);
    remaining_fol->func_00464D90(464.0f, 8.0f, 126.0f, 24.0f, 0, 0, 0);
    func_004C6190(unk10, remaining_fol);
    return 1;
}

void ShopActionWindow::func_slot74()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(2) == 1)
    {
        return;
    }
}

void ShopActionWindow::func_slot70()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(3) == 1)
    {
        return;
    }
}

s32 shop_cancel_action(void* receiver)
{
    FieldClass15AE70* object = static_cast<FieldClass15AE70*>(receiver);
    if (object->func_slot28())
    {
        return 0;
    }
    object->func_slot1c(255, 128);
    return 2;
}

s32 shop_select_action(void* receiver)
{
    ShopActionWindow* object = static_cast<ShopActionWindow*>(receiver);
    if (object->func_slot28())
    {
        return 0;
    }
    shop_set_mode(D_001B643C->callbacks->shop, object->choice->unk114 != 0 ? SHOP_MODE_SELL : SHOP_MODE_BUY);
    return 1;
}

/**
 * @brief Set the choice cursor opacity and request a drawing update.
 * @param choice Choice grid.
 * @param opacity Cursor opacity before drawing.
 */
static inline void set_shop_choice_opacity(FieldObject23CEA0* choice, float opacity)
{
    choice->FieldClass151C50::unk30 = opacity;
    choice->unkae = 1;
}
/**
 * @brief Update cursor opacity, the selected action, and category text.
 */
void ShopActionWindow::func_slot5c()
{
    ShopState* state = D_001B643C->callbacks->shop;
    if (state->func_00261150() == this)
    {
        set_shop_choice_opacity(choice, SHOP_CURSOR_FOCUSED_OPACITY);
    }
    else
    {
        set_shop_choice_opacity(choice, SHOP_CURSOR_UNFOCUSED_OPACITY);
    }
    state->selected_action = choice->unk114;
    if (choice != 0)
    {
        s16 selected_action = choice->unk114;
        if (buy_label != 0)
        {
            if (selected_action == 0)
            {
                buy_label->set_color(0x288080);
            }
            else
            {
                buy_label->set_color(0x808080);
            }
        }
        if (sell_label != 0)
        {
            if (selected_action == 1)
            {
                sell_label->set_color(0x288080);
            }
            else
            {
                sell_label->set_color(0x808080);
            }
        }
    }
    func_4C6DF0(category_label, state->func_00263CC0(), state->category + SHOP_MSG_WEAPONS, 0);
}

/**
 * @brief Create the buy and sell choices and category controls.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 ShopActionWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 2000, 16.0f, 220.0f, 0.0f);
    LibClass178630* action_panel = new (0) LibClass178630;
    func_004C5A80(action_panel, 0, 0.0f, 0.0f, 250.0f, 40.0f, 88.0f);
    func_004C6190(unk10, action_panel);
    buy_label = new (0) LibObject178750;
    sell_label = new (0) LibObject178750;
    func_004C7FE0(buy_label, static_cast<s32>(associated), SHOP_MSG_BUY, 1, 34.0f, 8.0f, 0.0f, 0.0f);
    func_004C7FE0(sell_label, static_cast<s32>(associated), SHOP_MSG_SELL, 1, 142.0f, 8.0f, 0.0f, 0.0f);
    func_004C6190(unk10, buy_label);
    func_004C6190(unk10, sell_label);
    choice = new (0) FieldObject23CEA0;
    choice->func_0023CE80(2, 1);
    choice->func_0023CE60(108.0f, 0.0f);
    choice->unkF2 = 0;
    choice->func_0023CF50(0, 40.0f, 224.0f);
    choice->func_0044B110(0, 9, 2000, 0, 0.0f);
    shop_append_choice(&unk74, choice);
    LibClass178630* category_panel = new (0) LibClass178630;
    func_004C5A80(category_panel, 0, 250.0f, 0.0f, 358.0f, 40.0f, 88.0f);
    func_004C6190(unk10, category_panel);
    previous_category_icon = new (0) LibClass174C40;
    func_4530E0(previous_category_icon, 10, 280.0f, 3.0f);
    func_004C6190(unk10, previous_category_icon);
    category_label = new (0) LibObject178750;
    func_004C7FE0(category_label, static_cast<s32>(associated), SHOP_MSG_WEAPONS, 1, 274.0f, 8.0f, 310.0f, 8.0f);
    category_label->set_color(0x508050);
    category_label->set_mode(1);
    func_004C6190(unk10, category_label);
    next_category_icon = new (0) LibClass174C40;
    func_4530E0(next_category_icon, 11, 554.0f, 3.0f);
    func_004C6190(unk10, next_category_icon);
    return 1;
}

ItemCreationClass175110::~ItemCreationClass175110()
{
}

/**
 * @brief Show the selected item description or base parameters.
 */
void ShopDescriptionWindow::func_slot5c()
{
    ShopState* state = D_001B643C->callbacks->shop;
    if (state->selected_item >= 0)
    {
        if (show_parameters != 0)
        {
            help_text->unk3f = 0;
            description->unk3f = 0;
            parameters_heading->unk3f = 1;
            ItemCreationAllocationRecord preview_allocation __attribute__((aligned(16)));
            preview_allocation.reset(0);
            ItemCreationCategoryRecord* item_record = shop_item_record(D_001B64F8, state->selected_item);
            initialize_shop_item_allocation(&preview_allocation, item_record, 0);
            set_shop_number(parameter_values[0], D_001B64F0[preview_allocation.definition_index()].attack);
            set_shop_number(parameter_values[1], D_001B64F0[preview_allocation.definition_index()].hit);
            set_shop_number(parameter_values[2], D_001B64F0[preview_allocation.definition_index()].defense);
            set_shop_number(parameter_values[3], D_001B64F0[preview_allocation.definition_index()].agility);
            set_shop_number(parameter_values[4], D_001B64F0[preview_allocation.definition_index()].intelligence);
            for (s32 parameter_index = 0; parameter_index < 5; parameter_index++)
            {
                parameter_labels[parameter_index]->unk3f = 1;
                parameter_separators[parameter_index]->unk3f = 1;
                parameter_values[parameter_index]->unk3f = 1;
            }
        }
        else
        {
            s32 item_description_key = state->selected_item + SHOP_MSG_LIST_DESCRIPTIONS;
            if (item_description_key != description_key)
            {
                help_text->unk3f = 0;
                description->unk3f = 1;
                func_0045F690(description, func_slot54(), item_description_key, 8, 1);
                LibObject174D90* description_text = description;
                description_text->unk80 = 0.8f;
                description_text->unk84 = 0.8f;
                description_text->unk3c = 1;
            }
            for (s32 parameter_index = 0; parameter_index < 5; parameter_index++)
            {
                parameter_labels[parameter_index]->unk3f = 0;
                parameter_separators[parameter_index]->unk3f = 0;
                parameter_values[parameter_index]->unk3f = 0;
            }
            parameters_heading->unk3f = 0;
        }
        switch_hint->unk3f = 1;
    }
    else
    {
        help_text->unk3f = 1;
        description->unk3f = 0;
        switch_hint->unk3f = 0;
        parameters_heading->unk3f = 0;
        for (s32 parameter_index = 0; parameter_index < 5; parameter_index++)
        {
            parameter_labels[parameter_index]->unk3f = 0;
            parameter_separators[parameter_index]->unk3f = 0;
            parameter_values[parameter_index]->unk3f = 0;
        }
    }
}

/**
 * @brief Create the item description, base parameter, and switch-help displays.
 * @param associated Full resource source word.
 * @return One when created, or zero when the resource source is absent.
 */
s32 ShopDescriptionWindow::func_slotf4(u32 associated)
{
    if (associated == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot14(associated, 0, 9, 1800, 220.0f, 80.0f, 0.0f);
    unk10->func_0044B110(0, 9, 1800, 100, 0.0f);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 404.0f, 140.0f, 88.0f);
    func_004C6190(unk10, panel);
    description = new (0) LibObject174D90;
    description->func_00461720(32.0f, 13.0f, 362.0f, 140.0f, static_cast<s32>(associated), SHOP_MSG_DESCRIPTION_HELP, 8, 0);
    LibObject174D90* description_text = description;
    description_text->unk52c = 0.0f;
    description_text->unk524 = 0.0f;
    func_004C6190(unk10, description);
    description->unk3f = 0;
    help_text = new (0) LibObject178750;
    help_text->func_004C7FE0(40.0f, 13.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_DESCRIPTION_HELP, 0);
    func_004C6190(unk10, help_text);
    help_text->unk3f = 0;
    parameters_heading = new (0) LibObject178750;
    parameters_heading->func_004C7FE0(40.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_BASE_PARAMETERS, 0);
    parameters_heading->set_color(0x806080);
    parameters_heading->set_scale(0.75f, 0.75f);
    func_004C6190(unk10, parameters_heading);
    parameters_heading->unk3f = 0;
    for (s32 parameter_index = 0; parameter_index < 5; parameter_index++)
    {
        parameter_labels[parameter_index] = new (0) LibObject178750;
        float parameter_y = 42.0f + static_cast<float>(28 * (parameter_index / 2));
        parameter_labels[parameter_index]->func_004C7FE0(50.0f + static_cast<float>(190 * (parameter_index % 2)), parameter_y, 0.0f, 0.0f,
                                                     static_cast<s32>(associated), SHOP_MSG_ATK + parameter_index, 0);
        parameter_labels[parameter_index]->set_color(0x805050);
        func_004C6190(unk10, parameter_labels[parameter_index]);
        parameter_labels[parameter_index]->unk3f = 0;
        parameter_separators[parameter_index] = new (0) LibObject178750;
        parameter_separators[parameter_index]->func_004C7FE0(100.0f + static_cast<float>(190 * (parameter_index % 2)), parameter_y, 0.0f, 0.0f,
                                                     static_cast<s32>(associated), SHOP_MSG_PARAMETER_SEPARATOR, 0);
        parameter_separators[parameter_index]->set_color(0x805050);
        func_004C6190(unk10, parameter_separators[parameter_index]);
        parameter_separators[parameter_index]->unk3f = 0;
        parameter_values[parameter_index] = new (0) LibObject174F20;
        parameter_values[parameter_index]->func_00464D90(90.0f + static_cast<float>(190 * (parameter_index % 2)), parameter_y, 80.0f, 30.0f, 0,
                                                    static_cast<s32>(associated), 1);
        func_004C6190(unk10, parameter_values[parameter_index]);
        parameter_values[parameter_index]->unk3f = 0;
    }
    switch_hint = new (0) LibObject178750;
    switch_hint->func_004C7FE0(285.0f, 104.0f, 0.0f, 0.0f, static_cast<s32>(associated), SHOP_MSG_SWITCH_HELP, 0);
    func_004C6190(unk10, switch_hint);
    return 1;
}

/** Character record copied before applying a prospective equipment change. */
struct ShopCharacterRecord
{
    s16 character_id;
    /** Selects the clamping rules used by the character stat setters. */
    s16 stat_limit_type;
    s16 encoded_level;
    s16 unk06;
    s32 encoded_flags;
    s32 encoded_experience;
    s32 encoded_base_hp;
    s32 encoded_max_hp;
    s32 encoded_hp;
    s32 encoded_base_mp;
    s32 encoded_max_mp;
    s32 encoded_mp;
    float unk28;
    /** Fury is stored at sixteen times its displayed amount. */
    float scaled_max_fury;
    float scaled_fury;
    s32 encoded_base_attack;
    s32 encoded_effective_attack;
    s32 encoded_attack;
    s32 encoded_base_defense;
    s32 encoded_effective_defense;
    s32 encoded_defense;
    s32 encoded_base_agility;
    s32 encoded_effective_agility;
    s32 encoded_agility;
    s32 encoded_base_hit;
    s32 encoded_effective_hit;
    s32 encoded_hit;
    /** The resident INT helpers validate these values through the HIT checksum. */
    s32 encoded_base_intelligence;
    s32 encoded_effective_intelligence;
    s32 encoded_intelligence;
    s16 encoded_base_knockback_power;
    s16 encoded_effective_knockback_power;
    s16 encoded_knockback_power;
    s16 encoded_base_knockback_resistance;
    s16 encoded_effective_knockback_resistance;
    s16 encoded_knockback_resistance;
    s16 encoded_base_critical_rate;
    s16 encoded_effective_critical_rate;
    s16 encoded_critical_rate;
    s32 level_checksum;
    s32 flags_experience_checksum;
    s32 hp_checksum;
    s32 mp_checksum;
    s32 attack_checksum;
    s32 defense_checksum;
    s32 agility_checksum;
    s32 hit_checksum;
    s32 knockback_power_checksum;
    s32 checksum_salt;
    s32 critical_rate_checksum;
    s32 knockback_resistance_checksum;
    s32 unkb4[3];
    s32 unkc0;
};

/** Character equipment and skill values copied for an equipment preview. */
struct ShopCharacterEquipment
{
    s16 encoded_base_luck;
    s16 encoded_effective_luck;
    s16 encoded_luck;
    s16 encoded_base_stamina;
    s16 encoded_effective_stamina;
    s16 encoded_stamina;
    s16 encoded_equipment_slot_count;
    s16 encoded_slot_limit;
    s16 encoded_equipment_ids[4];
    s16 encoded_sp;
    s16 encoded_cp;
    u8 unk1c[4];
    char character_name[24];
    u8 battle_strategy;
    /** Strategy saved when the tactics selection window opens. */
    u8 previous_battle_strategy;
    u8 unk3a;
    u8 encoded_anti_attack_aura_mask;
    u8 encoded_status_skill_levels[5];
    u8 encoded_battle_skill_indices[6];
    u8 encoded_tactical_skill_states[7];
    s16 encoded_symbology_mastery[32];
    s16 encoded_battle_skill_mastery[42];
    /** Damage responses in earth, water, fire, wind order. */
    u8 elemental_damage_responses[4];
    u8 attack_element_mask;
    /** Variant index used with character-specific resource groups. */
    u8 character_resource_variant;
    u32 luck_checksum;
    u32 stamina_checksum;
    u32 equipment_checksum;
    u32 sp_cp_checksum;
    u32 symbology_mastery_checksum;
    u32 battle_skill_mastery_checksum;
    u32 tactical_skill_states_checksum;
    u32 battle_skill_indices_checksum;
    u32 status_skill_levels_checksum;
    u32 checksum_salt;
    u32 unk110;
};

/**
 * @brief Apply an allocation to copied character and equipment data.
 * @param record Record copy to update.
 * @param equipment Equipment copy to update.
 * @param allocation Allocation record to apply.
 * @param index Statistic group to apply.
 * @return One on success, or zero when either copied record is null.
 */
extern "C" s32 func_003F9890(ShopCharacterRecord* record, ShopCharacterEquipment* equipment, ItemCreationAllocationRecord* allocation, s32 index);

/**
 * @brief Read the checksum-protected attack value.
 * @param character Character record.
 * @return Decoded statistic, or zero when its checksum is invalid.
 */
static inline s32 shop_character_attack(const ShopCharacterRecord& character)
{
    if (character.attack_checksum != (character.checksum_salt ^ (character.encoded_attack ^ (character.encoded_base_attack + character.encoded_effective_attack))))
    {
        return 0;
    }
    return character.encoded_attack ^ 0x7DE3F7E3;
}

/**
 * @brief Read the checksum-protected defense value.
 * @param character Character record.
 * @return Decoded statistic, or zero when its checksum is invalid.
 */
static inline s32 shop_character_defense(const ShopCharacterRecord& character)
{
    if (character.defense_checksum != (character.checksum_salt ^ (character.encoded_defense ^ (character.encoded_base_defense + character.encoded_effective_defense))))
    {
        return 0;
    }
    return character.encoded_defense ^ 0x7DE3F7E3;
}

/**
 * @brief Validate the equipment allocation ID checksum.
 * @param equipment Character equipment record.
 * @return True when the checksum agrees with the allocation IDs and salt.
 */
static inline bool shop_equipment_valid(const ShopCharacterEquipment* equipment)
{
    return equipment->equipment_checksum ==
           (equipment->checksum_salt ^ ((equipment->encoded_equipment_ids[1] + equipment->encoded_equipment_ids[2]) ^
                                       (equipment->encoded_equipment_ids[3] + equipment->encoded_equipment_ids[0])));
}

/**
 * @brief Read a checksum-protected equipment allocation ID.
 * @param equipment Character equipment record.
 * @param equipment_slot Equipment slot index.
 * @return Allocation ID, or zero for an invalid check word or slot index.
 */
static inline s16 shop_equipment_allocation_id(const ShopCharacterEquipment* equipment, s32 equipment_slot)
{
    if (!shop_equipment_valid(equipment))
    {
        return 0;
    }
    if (equipment_slot < 0)
    {
        return 0;
    }
    if (equipment_slot > (equipment->encoded_slot_limit ^ 0x7E93))
    {
        return 0;
    }
    return equipment->encoded_equipment_ids[equipment_slot] ^ 0x7E93;
}

/**
 * @brief Find an allocation record in resident storage.
 * @param index One-based allocation index.
 * @return Allocation record, or null outside one through three thousand.
 */
static inline ItemCreationAllocationRecord* shop_allocation_record(s16 index)
{
    ShopInventoryState* base = D_001B64F8;
    u8 valid = index >= 1 && index <= 3000;
    if (valid)
    {
        return &base->allocations[index - 1];
    }
    return 0;
}

/**
 * @brief Set a character display's brightness and request a redraw.
 * @param object Character display.
 * @param value Scale for all three colour channels.
 */
static inline void set_shop_character_brightness(ItemCreationOptionResourceDisplay* object, float value)
{
    object->unk50.unk44 = value;
    object->unk50.unk48 = value;
    object->unk50.unk4c = value;
    object->unk3c = 1;
}

/**
 * @brief Calculate an allocation record's checksum for a given shift.
 * @param record Allocation record.
 * @param shift Two-bit shift applied to the checksum key.
 * @return Calculated checksum.
 */
static inline u16 shop_allocation_checksum(ItemCreationAllocationRecord* record, u32 shift)
{
    return (0x83CF << shift) ^ ((record->factors_567.halves[0] + (record->definition_factors.halves[0] + record->factors_234.halves[0])) ^
                              (record->definition_factors.halves[1] + (record->factors_234.halves[1] + record->factors_567.halves[1])));
}

/**
 * @brief Clear an allocation record, choose its checksum shift and store the checksum.
 * @param record Allocation record to reset.
 * @param key Fixed shift to use instead of a random one, or null.
 */
static inline void reset_shop_allocation(ItemCreationAllocationRecord* record, const u8* key)
{
    *(unsigned __int128*)record = 0;
    record->checksum_shift = func_0010CF80() & 3;
    if (key != 0)
    {
        record->checksum_shift = *key;
    }
    record->checksum = shop_allocation_checksum(record, record->checksum_shift);
}

/**
 * @brief Reset an allocation record and initialize it from a catalog record.
 * @param allocation Allocation record to initialize.
 * @param item Catalog record supplying the allocation value.
 */
static inline void initialize_shop_allocation(ItemCreationAllocationRecord* allocation, const ItemCreationCategoryRecord* item)
{
    reset_shop_allocation(allocation, 0);
    func_0040D2E0(allocation, item->catalog_index + 1, 0, 0, false, true);
}

/**
 * @brief Get the shop state's record selection.
 * @param state Shop state.
 * @return Record selection.
 */
static inline FieldRecordSelection* shop_record_selection(ShopState* state)
{
    return &state->selection;
}

/**
 * @brief Read the catalog definition index from a valid allocation.
 * @param record Allocation record.
 * @return Definition index, or zero when the checksum differs.
 */
static inline u16 shop_allocation_definition_index(const ItemCreationAllocationRecord& record)
{
    u16 definition_index = record.definition_factors.bits.definition_index;
    if (record.checksum !=
        (u16)((0x83CF << record.checksum_shift) ^ ((record.factors_567.halves[0] + (*(u16*)&record + record.factors_234.halves[0])) ^
                                               (record.definition_factors.halves[1] + (record.factors_234.halves[1] + record.factors_567.halves[1])))))
    {
        return 0;
    }
    return definition_index;
}

/**
 * @brief Highlight eligible characters and compare attack or defense with the selected equipment applied.
 */
void ShopEquipmentPreviewWindow::func_slot5c()
{
    ShopState* state = D_001B643C->callbacks->shop;
    for (s32 i = 0; i < 8; i++)
    {
        ItemCreationOptionResourceDisplay* character_display = character_displays[i];
        if (character_display != 0)
        {
            set_shop_character_brightness(character_display, 128.0f);
        }
        comparison_labels[i]->unk3f = 0;
    }
    pulse_level += pulse_step;
    if (pulse_level > 18)
    {
        pulse_step = -1;
    }
    if (pulse_level < 0)
    {
        pulse_step = 1;
    }
    if (state->selected_item >= 0)
    {
        const ItemCreationCategoryRecord* item_record = shop_item_record(D_001B64F8, state->selected_item);
        if (shop_definition_category(shop_definition(item_record)) != SHOP_CATEGORY_WEAPONS &&
            shop_definition_category(shop_definition(item_record)) != SHOP_CATEGORY_ARMOR &&
            shop_definition_category(shop_definition(item_record)) != SHOP_CATEGORY_ACCESSORIES)
        {
            return;
        }
        ItemCreationAllocationRecord preview_allocation __attribute__((aligned(16)));
        reset_shop_allocation(&preview_allocation, 0);
        initialize_shop_allocation(&preview_allocation, item_record);
        for (s32 i = 0; i < 8; i++)
        {
            bool already_equipped;
            s32 equipment_slot;
            FieldRecordSelection* selection = shop_record_selection(state);
            FieldRecord* character_record = &selection->records[static_cast<s16>(i)];
            s8 character_slot = selection->slots[static_cast<s16>(i)];
            const ShopCharacterEquipment* equipment = &static_cast<const ShopCharacterEquipment*>(selection->unk04)[static_cast<s16>(i)];
            if (character_slot <= 0)
            {
                continue;
            }
            s32 equipment_bit = 1 << (character_slot - 1);
            u16 equipment_mask = shop_definition(item_record)->equipment_mask;
            if (equipment_mask & equipment_bit)
            {
                already_equipped = false;
                for (equipment_slot = 0; equipment_slot < 4; equipment_slot++)
                {
                    s16 allocation_id = shop_equipment_allocation_id(equipment, equipment_slot);
                    if (allocation_id > 0)
                    {
                        ItemCreationAllocationRecord* equipped_allocation = shop_allocation_record(allocation_id);
                        if (equipped_allocation != 0 &&
                            static_cast<u16>(equipped_allocation->definition_index() + 1) ==
                                static_cast<u16>(shop_allocation_definition_index(preview_allocation) + 1))
                        {
                            already_equipped = true;
                            break;
                        }
                    }
                }
                if (already_equipped)
                {
                    func_4C6DF0(comparison_labels[i], state->func_00263CC0(), SHOP_MSG_EQUIPPED, 0);
                    comparison_labels[i]->set_color(0xFF8028);
                    comparison_labels[i]->unk3f = 1;
                    continue;
                }
            }
            else
            {
                set_shop_character_brightness(character_displays[i], 50.0f);
                comparison_labels[i]->unk3f = 0;
                continue;
            }
            const ShopCharacterRecord* character = reinterpret_cast<const ShopCharacterRecord*>(character_record);
            ShopCharacterRecord character_copy = *character;
            ShopCharacterEquipment equipment_copy = *equipment;
            switch (shop_definition_category(shop_definition(item_record)))
            {
            case SHOP_CATEGORY_WEAPONS:
                func_003F9890(&character_copy, &equipment_copy, &preview_allocation, 0);
                comparison_labels[i]->unk3f = 1;
                if (shop_character_attack(character_copy) > shop_character_attack(*character))
                {
                    func_4C6DF0(comparison_labels[i], state->func_00263CC0(), SHOP_MSG_STAT_INCREASE, 0);
                    comparison_labels[i]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) |
                                         (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) << 8) |
                                         (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
                }
                else if (shop_character_attack(character_copy) == shop_character_attack(*character))
                {
                    func_4C6DF0(comparison_labels[i], state->func_00263CC0(), SHOP_MSG_STAT_UNCHANGED, 0);
                }
                else
                {
                    func_4C6DF0(comparison_labels[i], state->func_00263CC0(), SHOP_MSG_STAT_DECREASE, 0);
                    comparison_labels[i]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) |
                                         (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 8) |
                                         (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
                }
                break;
            case SHOP_CATEGORY_ARMOR:
                func_003F9890(&character_copy, &equipment_copy, &preview_allocation, 1);
                comparison_labels[i]->unk3f = 1;
                if (shop_character_defense(character_copy) > shop_character_defense(*character))
                {
                    func_4C6DF0(comparison_labels[i], state->func_00263CC0(), SHOP_MSG_STAT_INCREASE, 0);
                    comparison_labels[i]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) |
                                         (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) << 8) |
                                         (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
                }
                else if (shop_character_defense(character_copy) == shop_character_defense(*character))
                {
                    func_4C6DF0(comparison_labels[i], state->func_00263CC0(), SHOP_MSG_STAT_UNCHANGED, 0);
                }
                else
                {
                    func_4C6DF0(comparison_labels[i], state->func_00263CC0(), SHOP_MSG_STAT_DECREASE, 0);
                    comparison_labels[i]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * pulse_level))) |
                                         (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 8) |
                                         (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * pulse_level))) << 16));
                }
                break;
            case SHOP_CATEGORY_ACCESSORIES:
                comparison_labels[i]->unk3f = 0;
                break;
            }
        }
    }
}

/**
 * @brief Create the character displays and equipment comparison labels.
 * @param associated Resource source word.
 * @return One on success, or zero when no source word is given.
 */
s32 ShopEquipmentPreviewWindow::func_slotf4(u32 associated)
{
    if (associated == 0)
    {
        return 0;
    }
    pulse_level = 0;
    pulse_step = 1;
    FieldClass15AE70::func_slot14(associated, 0, 9, 2000, 16.0f, 68.0f, 0.0f);
    unk10->LibClass174610::func_0044B110(0, 9, 2000, 200, 0.0f);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 232.0f, 152.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopState* state = D_001B643C->callbacks->shop;
    FieldRecordSelection* selection;
    s32 character_resource_slot;
    u16 column;
    u16 row;
    for (s32 i = 0; i < 8; i++)
    {
        selection = &state->selection;
        character_resource_slot = static_cast<u16>(selection->slots[static_cast<s16>(i)]);
        // TODO: Recover the purpose of this unused record pointer.
        FieldRecord* unused_record = &selection->records[static_cast<s16>(i)];
        column = i % 4;
        row = i / 4;
        if (character_resource_slot != 0)
        {
            character_displays[i] = new (0) ItemCreationOptionResourceDisplay;
            void* character_buffer = func_002D3D80(D_001B643C->resource_buffers, static_cast<u8>(character_resource_slot));
            FieldResourceRecord* display_record = func_002D3CC0(D_001B643C->resource_buffers, 4);
            character_displays[i]->unkcc = character_buffer;
            character_displays[i]->unkd0 = character_resource_slot;
            character_displays[i]->func_002D6440(display_record, 20.0f + 50.0f * column, 12.0f + 68.0f * row);
            ItemCreationOptionResourceDisplay* character_display = character_displays[i];
            character_display->unk50.unk30 = 0.62f;
            character_display->unk50.unk34 = 0.72f;
            character_display->unk3c = 1;
            character_displays[i]->unk34 = 3;
            func_004C6190(unk10, character_displays[i]);
        }
        else
        {
            character_displays[i] = 0;
        }
        comparison_labels[i] = new (0) LibObject178750;
        comparison_labels[i]->func_004C7FE0(20.0f + 50.0f * column, 43.0f + (12.0f + 68.0f * row), 0.0f, 0.0f,
                                           static_cast<s32>(associated), SHOP_MSG_EQUIPPED, 0);
        LibObject178750* comparison_label = comparison_labels[i];
        comparison_label->unk84 = 0.8f;
        comparison_label->unk80 = 0.8f;
        comparison_label->unk3c = 1;
        comparison_labels[i]->unk3f = 0;
        func_004C6190(unk10, comparison_labels[i]);
    }
    return 1;
}

/**
 * @brief Select the action help message and restart its scrolling delay.
 * @param object Shop help window.
 * @param action_index Selected action before the help message base.
 */
void shop_set_help_text(ShopScrollingWindow* object, s32 action_index)
{
    object->scrolling = 0;
    object->scroll_timer = 0;
    func_4C6DF0(object->help_text, object->func_slot54(), action_index + SHOP_MSG_BUY_HELP, 1);
    object->help_text_width = static_cast<s32>(func_004C69B0(object->help_text)->unk08) + 6;
    object->help_action = action_index;
}

/**
 * @brief Refresh the selected action help, pause, then scroll it across the clipped area.
 * @param object Shop help window.
 */
void shop_update_help_text(ShopScrollingWindow* object)
{
    ShopState* state = D_001B643C->callbacks->shop;
    object->help_text->unk3d = 1;
    if (object->help_action != state->selected_action)
    {
        object->func_slot60(state->selected_action);
    }
    LibObject178750* help_text = object->help_text;
    float text_x = help_text->unk18.unk00;
    float text_y = help_text->unk18.unk04;
    float display_width = help_text->unk18.unk08;
    float display_height = help_text->unk18.unk0c;
    if (object->scrolling == 0)
    {
        help_text->unk18.unk00 = object->help_start_x;
        help_text->unk18.unk04 = text_y;
        help_text->unk18.unk08 = display_width;
        help_text->unk18.unk0c = display_height;
        help_text->unk3c = 1;
        object->scroll_timer++;
        if (!(static_cast<float>(object->scroll_timer) <= 120.0f))
        {
            object->scroll_timer = 0;
            object->scrolling = 1;
        }
        return;
    }
    float clip_left = object->help_clip_left;
    text_x -= 108.0f * D_001B6690;
    if (text_x < clip_left - static_cast<float>(object->help_text_width))
    {
        text_x = 2.0f + (clip_left + object->help_clip_width);
    }
    help_text->unk18.unk00 = text_x;
    help_text->unk18.unk04 = text_y;
    help_text->unk18.unk08 = display_width;
    help_text->unk18.unk0c = display_height;
    help_text->unk3c = 1;
}

/**
 * @brief Create the shop name, clipped action help, and title displays.
 * @param associated Full resource source word.
 * @return One on success, or zero if initialization fails.
 */
s32 ShopHelpWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1400, 16.0f, 16.0f, 0.0f);
    help_text = new (0) LibObject178750;
    LibObject178750* title_text = new (0) LibObject178750;
    LibClass1746A0* clip_region = new (0) LibClass1746A0;
    LibClass1746A0* reset_clip = new (0) LibClass1746A0;
    if (help_text == 0 || clip_region == 0 || reset_clip == 0)
    {
        return 0;
    }
    LibObject178750* shop_name = new (0) LibObject178750;
    shop_name->func_004C7FE0(16.0f, 6.0f, 0.0f, 0.0f, static_cast<s32>(associated), D_001B643C->callbacks->shop->shop_id + SHOP_MSG_SHOP_NAMES, 0);
    func_004C6190(unk10, shop_name);
    shop_name_width = func_004C69B0(shop_name)->unk08;
    help_clip_left = 18.0f + shop_name_width;
    float right_padding = 32.0f;
    help_clip_width = 640.0f - (16.0f + (help_clip_left + right_padding));
    help_start_x = 24.0f + shop_name_width;
    func_44B570(clip_region, help_clip_left, 0.0f, help_clip_width, 56.0f);
    func_004C6190(unk10, clip_region);
    shop_append_frame(&unk20, clip_region);
    func_004C7FE0(help_text, static_cast<s32>(associated), SHOP_MSG_BUY_HELP, 0, help_clip_left, 6.0f, 0.0f, 0.0f);
    func_004C6190(unk10, help_text);
    help_text->unk3d = 0;
    shop_append_text(&unk2c, help_text);
    func_44B510(reset_clip, 1);
    func_004C6190(unk10, reset_clip);
    shop_append_frame(&unk20, reset_clip);
    func_004C7FE0(title_text, static_cast<s32>(associated), SHOP_MSG_TITLE, 0, 36.0f, 39.0f, 0.0f, 0.0f);
    title_text->set_scale(0.65f, 0.65f);
    func_004C6190(unk10, title_text);
    func_slot60(0);
    return 1;
}

/**
 * @brief Create the left, middle, and right background images from one cached buffer.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 ShopBackgroundWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1200, 16.0f, 16.0f, 0.0f);
    ItemCreationOptionResourceDisplay* left_image = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* middle_image = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* right_image = new (0) ItemCreationOptionResourceDisplay;
    void* background_buffer = func_002D3D80(D_001B643C->resource_buffers, 11);
    left_image->unkcc = background_buffer;
    middle_image->unkcc = background_buffer;
    right_image->unkcc = background_buffer;
    left_image->unkd0 = 11;
    middle_image->unkd0 = 11;
    right_image->unkd0 = 11;
    FieldResourceRecord* image_record = func_002D3CC0(D_001B643C->resource_buffers, 5);
    left_image->func_002D6440(image_record, 0.0f, 0.0f);
    image_record = func_002D3CC0(D_001B643C->resource_buffers, 6);
    middle_image->func_002D6440(image_record, 256.0f, 0.0f);
    image_record = func_002D3CC0(D_001B643C->resource_buffers, 7);
    right_image->func_002D6440(image_record, 512.0f, 0.0f);
    func_004C6190(unk10, left_image);
    func_004C6190(unk10, middle_image);
    func_004C6190(unk10, right_image);
    return 1;
}

/**
 * @brief Advance through item categories until a nonempty category is found.
 * @param object Shop controller.
 * @param direction Signed category step.
 */
void shop_change_category(ShopState* object, s32 direction)
{
    switch (object->mode)
    {
    case SHOP_MODE_BUY:
    {
        s32 attempts = 0;
        for (;;)
        {
            object->category += direction;
            if (object->category < 0)
            {
                object->category = SHOP_CATEGORY_ALL;
            }
            if (object->category >= 8)
            {
                object->category = 0;
            }
            if (attempts >= 9)
            {
                break;
            }
            if (shop_category_item_count(&object->transaction, object->category) != 0)
            {
                break;
            }
            attempts++;
        }
        break;
    }
    case SHOP_MODE_SELL:
    {
        s32 attempts = 0;
        for (;;)
        {
            object->category += direction;
            if (object->category < 0)
            {
                object->category = SHOP_CATEGORY_ALL;
            }
            if (object->category >= 8)
            {
                object->category = 0;
            }
            if (attempts > 8)
            {
                object->category = SHOP_CATEGORY_ALL;
                break;
            }
            s32 item_code;
            for (item_code = 1; item_code <= 750; item_code++)
            {
                ItemCreationCategoryRecord* item_record = shop_item_record(D_001B64F8, item_code);
                if (item_record != 0 && item_record->inventory_count != 0 &&
                    (object->category == SHOP_CATEGORY_ALL || object->category == shop_definition_category(&D_001B64F0[item_record->catalog_index])))
                {
                    break;
                }
            }
            if (item_code <= 750)
            {
                break;
            }
            attempts++;
        }
        break;
    }
    default:
        object->category = SHOP_CATEGORY_ALL;
        break;
    }
}

/**
 * @brief Switch the active shop window and refresh the corresponding item list.
 * @param object Shop controller.
 * @param mode Action, buy, or sell mode.
 */
void shop_set_mode(ShopState* object, u32 mode)
{
    s32 previous_mode = object->mode;
    object->mode = mode;
    switch (object->mode)
    {
    case SHOP_MODE_ACTION:
        object->buy_window->func_slot20(0);
        object->sell_window->func_slot20(0);
        object->func_00263C70(object->action_window);
        object->selected_item = -1;
        object->category = SHOP_CATEGORY_ALL;
        break;
    case SHOP_MODE_BUY:
        object->sell_window->func_slot20(0);
        object->buy_window->func_slot20(1);
        object->buy_window->func_slot110(1);
        object->buy_window->func_slot10c(1, 1);
        shop_refresh_buy_list(object->buy_window, previous_mode != object->mode);
        object->func_00263C70(object->buy_window);
        break;
    case SHOP_MODE_SELL:
        object->buy_window->func_slot20(0);
        object->sell_window->func_slot20(1);
        object->sell_window->func_slot110(1);
        object->sell_window->func_slot10c(1, 1);
        shop_refresh_sell_list(object->sell_window, previous_mode != object->mode);
        object->func_00263C70(object->sell_window);
        break;
    }
}

/**
 * @brief Select the shop and initialize purchases with the active discount.
 * @param object Shop controller.
 * @param shop_id Shop identifier.
 */
void shop_set_id(ShopState* object, u16 shop_id)
{
    object->shop_id = shop_id;
    s32 discount_percent = 0;
    if (shop_runtime_flag(SHOP_DISCOUNT_10_PERCENT))
    {
        discount_percent = 10;
    }
    if (shop_runtime_flag(SHOP_DISCOUNT_20_PERCENT))
    {
        discount_percent = 20;
    }
    if (shop_runtime_flag(SHOP_DISCOUNT_30_PERCENT))
    {
        discount_percent = 30;
    }
    if (shop_runtime_flags()->invincibility_timer > 0)
    {
        discount_percent = 100;
    }
    shop_init_transaction(&object->transaction, object->shop_id, discount_percent);
}

/**
 * @brief Release the shop resources and controller, then clear the discount flags.
 * @param object Shop controller.
 */
void shop_release_resources(ShopState* object)
{
    if (object->resource_slot != 0)
    {
        func_00465430(D_001B657C, object->resource_slot);
    }
    func_004D65C0(object);
    object->func_001DD7B0();
    clear_shop_runtime_flag(SHOP_DISCOUNT_10_PERCENT);
    clear_shop_runtime_flag(SHOP_DISCOUNT_20_PERCENT);
    clear_shop_runtime_flag(SHOP_DISCOUNT_30_PERCENT);
}

void shop_queue_object(void* object)
{
    func_0011ED90(D_001B65F4, object);
}

/**
 * @brief Create and attach the shop windows, then select action mode.
 * @param receiver Shop controller.
 * @return Always one.
 */
s32 shop_create_windows(void* receiver)
{
    ShopState* object = static_cast<ShopState*>(receiver);
    ShopBackgroundWindow* background_window = new (0) ShopBackgroundWindow;
    ShopHelpWindow* help_window = new (0) ShopHelpWindow;
    object->equipment_window = new (0) ShopEquipmentPreviewWindow;
    object->description_window = new (0) ShopDescriptionWindow;
    object->action_window = new (0) ShopActionWindow;
    object->buy_window = new (0) ShopBuyListWindow;
    object->sell_window = new (0) ShopSellListWindow;
    object->fol_window = new (0) ShopFolWindow;
    background_window->func_slotf4(object->resource_slot);
    object->FieldClass153E30::func_00263FD0(background_window);
    help_window->func_slotf4(object->resource_slot);
    object->FieldClass153E30::func_00263FD0(help_window);
    object->unk24 = help_window;
    help_window->func_slot40(background_window);
    object->equipment_window->func_slotf4(object->resource_slot);
    object->FieldClass153E30::func_00263FD0(object->equipment_window);
    object->description_window->func_slotf4(object->resource_slot);
    object->FieldClass153E30::func_00263FD0(object->description_window);
    object->action_window->func_slotf4(object->resource_slot);
    object->FieldClass153E30::func_00263FD0(object->action_window);
    object->buy_window->func_slot104(object->resource_slot);
    object->FieldClass153E30::func_00263FD0(object->buy_window);
    object->buy_window->func_slot20(0);
    object->sell_window->func_slot104(object->resource_slot);
    object->FieldClass153E30::func_00263FD0(object->sell_window);
    object->sell_window->func_slot20(0);
    object->fol_window->func_slotf4(object->resource_slot);
    object->FieldClass153E30::func_00263FD0(object->fol_window);
    object->unk20 = object->action_window;
    object->windows_initialized = 1;
    shop_set_mode(object, SHOP_MODE_ACTION);
    return 1;
}

/** @brief Align a packed resource buffer. @param buffer Resource buffer. @return Aligned resource header. */
static inline ShopAlignedResource* aligned_shop_resource(void* buffer)
{
    return reinterpret_cast<ShopAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}
/**
 * @brief Register the loaded resource and select its item-name bank.
 * @param receiver Shop controller.
 * @param buffer Completed resource buffer, aligned to 128 bytes before use.
 * @return Controller setup result, or zero when the buffer is null.
 */
s32 shop_register_resource(void* receiver, void* buffer)
{
    ShopState* object = static_cast<ShopState*>(receiver);
    if (buffer == 0)
    {
        return 0;
    }
    ShopAlignedResource* resource = aligned_shop_resource(buffer);
    s32 allocation_size = resource->byte_count + 0x80;
    void* previous_heap = func_00100C90();
    void* resource_heap = D_001B6430->context->unk70;
    void* heap_probe = func_00113710(resource_heap, allocation_size);
    if (heap_probe != 0)
    {
        func_001134C0(heap_probe);
        func_00100C80(resource_heap);
    }
    object->resource_slot = func_004656B0(D_001B657C, resource);
    func_00100C80(previous_heap);
    FieldRuntime* runtime = D_001B657C;
    runtime->item_name_resource_slot = object->resource_slot;
    runtime->item_name_base_key = SHOP_MSG_ITEM_NAMES + 1;
    return object->func_00263CD0();
}

/**
 * @brief Initialize the shop record selection from the resident tables.
 * @param object Shop controller.
 * @return One when both selection tables are present, or zero otherwise.
 */
s32 shop_init_record_selection(ShopState* object)
{
    return func_28E3D0(&object->selection) != 0;
}

/** @brief Initialize the shop controller and its record selection. */
ShopState::ShopState()
{
    resource_slot = 0;
    windows_initialized = 0;
    equipment_window = 0;
    description_window = 0;
    action_window = 0;
    buy_window = 0;
    sell_window = 0;
    fol_window = 0;
    selected_item = -1;
    shop_id = -1;
    selected_action = 0;
    selected_allocation = 0;
    mode = 0;
    category = SHOP_CATEGORY_ALL;
}

void func_003516A0(void* object)
{
}

void func_003516B0(void* object)
{
}

void func_003516C0(void* object)
{
}

ShopSellConfirmWindow::~ShopSellConfirmWindow()
{
}

ShopBuyConfirmWindow::~ShopBuyConfirmWindow()
{
}

ShopSaleItemWindow::~ShopSaleItemWindow()
{
}

void func_00351800(void* object)
{
}

void func_00351810(void* object)
{
}

ShopSellListWindow::~ShopSellListWindow()
{
}

s32 func_00351890(void* object)
{
    return 0;
}

ShopBuyListWindow::~ShopBuyListWindow()
{
}

ShopFolWindow::~ShopFolWindow()
{
}

s32 func_00351970(void* object)
{
    return 0;
}

ShopActionWindow::~ShopActionWindow()
{
}

ShopDescriptionWindow::~ShopDescriptionWindow()
{
}

ShopEquipmentPreviewWindow::~ShopEquipmentPreviewWindow()
{
}

ShopHelpWindow::~ShopHelpWindow()
{
}

ShopBackgroundWindow::~ShopBackgroundWindow()
{
}

/** @brief Destroy the record selection and Field controller base. */
ShopState::~ShopState()
{
}

u8 shop_windows_initialized(ShopState* object)
{
    return object->windows_initialized;
}

s32 func_00351BE0(void* object)
{
    return 4;
}

void shop_set_help_window(ShopState* object, void* value)
{
    object->unk24 = value;
}

void* shop_get_help_window(ShopState* object)
{
    return object->unk24;
}

void func_00351C10(ShopState* object, s8 value)
{
    object->unk28 = value;
}

s8 func_00351C20(ShopState* object)
{
    return object->unk28;
}

s32 func_00351C30(void* object)
{
    return 0;
}

s32 func_00351C40(void* object)
{
    return 0;
}

void func_00351C50(void* object)
{
}

s32 func_00351C60(void* object)
{
    return 0;
}

void func_00351C70(void* object)
{
}

void func_00351C80(void* object)
{
}

void func_00351C90(void* object)
{
}

s32 func_00351CA0(void* object)
{
    return 0;
}

s32 func_00351CB0(void* object)
{
    return 0;
}

s32 func_00351CC0(void* object)
{
    return 0;
}

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void shop_append_choice(FieldCountedList* list, void* value)
{
    FieldListNode* node = static_cast<FieldListNode*>(func_00100AC0(sizeof(FieldListNode), 0));
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* tail = list->unk00;
        while (tail->unk04 != 0)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        list->unk04++;
    }
}

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void shop_append_text(FieldCountedList* list, void* value)
{
    FieldListNode* node = static_cast<FieldListNode*>(func_00100AC0(sizeof(FieldListNode), 0));
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* tail = list->unk00;
        while (tail->unk04 != 0)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        list->unk04++;
    }
}

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void shop_append_frame(FieldCountedList* list, void* value)
{
    FieldListNode* node = static_cast<FieldListNode*>(func_00100AC0(sizeof(FieldListNode), 0));
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* tail = list->unk00;
        while (tail->unk04 != 0)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        list->unk04++;
    }
}

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void shop_append_panel(FieldCountedList* list, void* value)
{
    FieldListNode* node = static_cast<FieldListNode*>(func_00100AC0(sizeof(FieldListNode), 0));
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* tail = list->unk00;
        while (tail->unk04 != 0)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        list->unk04++;
    }
}
