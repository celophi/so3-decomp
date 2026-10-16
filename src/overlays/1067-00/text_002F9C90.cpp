#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_00101550.h"
#include "sdk/main/libc_guess_00137290.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/1067-00/field_runtime.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/item_allocation.h"
#include "overlays/1067-00/text_002607B0.h"
#include "main/resident_001001E0.h"

extern "C" void func_114100(void* queue, void* submission);
extern "C" void* D_001B6610;

/** Partial receiver with a byte at offset 0x60. */
struct FieldByte60F9C90
{
    u8 pad[0x60];
    u8 value;
};

/** Partial receiver with a byte at offset 4. */
struct FieldByte4F9C90
{
    u8 pad[4];
    u8 value;
};

/** Allocation totals used to enforce the two resident inventory pools. */
struct TransactionInventoryTotals
{
    u8 unk00[0x11722];
    u16 unsellable_count;
    u16 sellable_count;
};

/** Dynamic shop membership bitmap for the 750 catalog items. */
struct DynamicShopInventory
{
    u16 unk00;
    u8 item_flags[94];
};

/** Resident inventory view containing the eleven dynamic shop lists. */
struct TransactionDynamicInventory
{
    u8 unk00[0x11280];
    DynamicShopInventory shops[11];
};

// Resident library ABI spellings used by the Field overlay.
extern "C" ResidentObject1B64F8* D_001B64F8;
extern "C" u16 func_457470(u16 seed, const void* data, s32 size);
extern "C" u32 func_414130(ItemCreationCategoryRecord* item);
extern "C" u32 func_40D760(ItemCreationAllocationRecord* allocation);

extern "C" void* func_0013A678(void* destination, s32 value, u32 size);
extern "C" u8 func_40B360(u32 shop_id);
extern "C" void* func_1012D0(FieldRuntimeRoot* root);
extern "C" u32 func_11DF70(void* clock);
extern "C" const u16* D_31A500[42];

/**
 * @brief Find an inventory entry by its one-based item code.
 * @param inventory Resident item inventory.
 * @param code One-based item code.
 * @return Entry, or null when the code is out of range.
 */
static inline ItemCreationCategoryRecord* transaction_item_record(ResidentObject1B64F8* inventory, u16 code)
{
    u8 valid = code >= 1 && code < 751;
    if (valid)
    {
        return &inventory->item_types[code - 1];
    }
    return 0;
}

/**
 * @brief Find an allocation by its one-based instance identifier.
 * @param inventory Resident item inventory.
 * @param identifier One-based instance identifier.
 * @return Allocation, or null when the identifier is out of range.
 */
static inline ItemCreationAllocationRecord* transaction_allocation(ResidentObject1B64F8* inventory, s16 identifier)
{
    u8 valid = identifier > 0 && identifier < 3001;
    if (valid)
    {
        return &reinterpret_cast<ItemCreationAllocationRecord*>(inventory)[identifier - 1];
    }
    return 0;
}

/**
 * @brief Report whether an inventor is recorded for the item.
 * @param item Inventory item entry.
 * @return One when an inventor is recorded, otherwise zero.
 */
static inline u8 item_has_inventor(const ItemCreationCategoryRecord* item)
{
    return item->inventor_id != 0;
}

/**
 * @brief Read an item's membership bit in a dynamic shop list.
 * @param shop Dynamic shop bitmap.
 * @param code One-based item code.
 * @return Membership bit, or zero when the item is absent.
 */
static inline u8 dynamic_shop_has_item(const DynamicShopInventory* shop, u16 code)
{
    s32 index = code - 1;
    return shop->item_flags[index / 8] & (1 << (index & 7));
}

/**
 * @brief Select a resident dynamic shop list.
 * @param inventory Resident item inventory.
 * @param slot One-based dynamic shop slot.
 * @return Selected shop list.
 */
static inline DynamicShopInventory* transaction_dynamic_shop(ResidentObject1B64F8* inventory, u8 slot)
{
    return &reinterpret_cast<TransactionDynamicInventory*>(inventory)->shops[slot - 1];
}

/**
 * @brief Read an item's shop category.
 * @param item Catalog definition.
 * @return Shop category.
 */
static inline u8 transaction_item_category(const ItemCreationCategoryDefinition* item)
{
    return item->category;
}

/** Model request keys at offsets 18 and 1A and raw buffer addresses at 1C and 20. */
struct FieldModelRequests
{
    u8 pad00[0x18];
    s16 first_key;
    s16 second_key;
    u32 first_request;
    u32 second_request;
};
INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", shop_sell_item);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", shop_complete_purchase);

void shop_clear_purchases(ShopTransaction* object)
{
    for (s32 index = 0; index < 750; index++)
    {
        object->purchase_quantities[index] = 0;
    }
    object->purchase_total = 0;
    object->pending_unsellable_count = 0;
    object->pending_sellable_count = 0;
}

/**
 * @brief Decrease the selected purchase quantity by one.
 * @param transaction Shop transaction to update.
 * @param code Item code in the low halfword.
 * @return One on success, or zero for an invalid code or an empty quantity.
 */
s32 shop_decrease_quantity(ShopTransaction* transaction, u32 code)
{
    u16 item_code = code;
    u8 valid = item_code > 0 && item_code < 751;
    if (!valid)
    {
        return 0;
    }
    u8* quantity = &transaction->purchase_quantities[item_code - 1];
    if (*quantity == 0)
    {
        return 0;
    }
    --*quantity;
    ItemCreationCategoryRecord* item = transaction_item_record(D_001B64F8, item_code);
    if (D_001B64F0[item->catalog_index].unsellable)
    {
        --transaction->pending_unsellable_count;
    }
    else
    {
        --transaction->pending_sellable_count;
    }
    transaction->purchase_total -= shop_get_buy_price(transaction, code);
    return 1;
}

/**
 * @brief Increase the selected purchase quantity after checking stock, fol and inventory space.
 * @param transaction Shop transaction to update.
 * @param code Item code in the low halfword.
 * @return One on success, or zero when the item cannot be added.
 */
s32 shop_increase_quantity(ShopTransaction* transaction, u32 code)
{
    u16 item_code = code;
    u8 valid = item_code > 0 && item_code < 751;
    if (!valid)
    {
        return 0;
    }
    u32 price = shop_get_buy_price(transaction, code);
    ItemCreationCategoryRecord* item = transaction_item_record(D_001B64F8, item_code);
    u8* quantity = &transaction->purchase_quantities[item_code - 1];
    if (*quantity + static_cast<u8>(item->inventory_count + item->equipped_count) + 1 > 20)
    {
        return 0;
    }
    if (!D_001B64F0[item->catalog_index].unlimited_stock)
    {
        if (*quantity + 1 > item->shop_stock)
        {
            return 0;
        }
    }
    ResidentCheckedRecord* record = static_cast<ResidentCheckedRecord*>(func_101440(func_101290(func_10D8E0()), 1));
    u16 checksum = record->checksum;
    const u8* end = reinterpret_cast<const u8*>(&record->checksum);
    u32 fol;
    if (checksum != func_457470(record->checksum_seed, reinterpret_cast<u8*>(record) + 0x26, end - (reinterpret_cast<const u8*>(record) + 0x26)))
    {
        fol = 0;
    }
    else
    {
        fol = record->encoded_fol ^ 0x7CE3C7F7;
    }
    if (fol < price + transaction->purchase_total)
    {
        return 0;
    }
    if (D_001B64F0[item->catalog_index].unsellable)
    {
        TransactionInventoryTotals* inventory = reinterpret_cast<TransactionInventoryTotals*>(D_001B64F8);
        if (transaction->pending_unsellable_count + inventory->unsellable_count + 1 > 100)
        {
            return 0;
        }
        ++transaction->pending_unsellable_count;
    }
    else
    {
        TransactionInventoryTotals* inventory = reinterpret_cast<TransactionInventoryTotals*>(D_001B64F8);
        if (transaction->pending_sellable_count + inventory->sellable_count + 1 > 2900)
        {
            return 0;
        }
        ++transaction->pending_sellable_count;
    }
    ++*quantity;
    transaction->purchase_total += price;
    return 1;
}

/**
 * @brief Calculate the sale price of an item instance.
 * @param transaction Shop transaction containing the play time used for pricing.
 * @param identifier One-based allocation identifier.
 * @return Sale price, or zero for an invalid or unsellable instance.
 */
s32 shop_get_sale_price(ShopTransaction* transaction, s16 identifier)
{
    ItemCreationAllocationRecord* allocation = transaction_allocation(D_001B64F8, identifier);
    if (!allocation || !allocation->allocated)
    {
        return 0;
    }
    u32 price = func_40D760(allocation);
    u16 item_code = allocation->definition_index() + 1;
    if (item_code == 153)
    {
        price += transaction->play_time_seconds;
        if (price > 99999999)
        {
            price = 99999999;
        }
    }
    price = (s32)(0.2f * price);
    if (price == 0)
    {
        price = 1;
    }
    return price;
}

/**
 * @brief Limit purchases by the per-item inventory capacity and finite shop stock.
 * @param transaction Shop transaction; unused by this accessor.
 * @param code One-based item code.
 * @return Purchase limit, or zero when the code is invalid or the inventory is full.
 */
s32 shop_get_buy_limit(ShopTransaction* transaction, u16 code)
{
    ItemCreationCategoryRecord* item = transaction_item_record(D_001B64F8, code);
    if (item == 0)
    {
        return 0;
    }
    s32 limit = 20 - static_cast<u8>(item->inventory_count + item->equipped_count);
    if (limit <= 0)
    {
        return 0;
    }
    if (!D_001B64F0[item->catalog_index].unlimited_stock)
    {
        u8 stock = item->shop_stock;
        if (stock < limit)
        {
            limit = stock;
        }
    }
    return limit;
}

/**
 * @brief Calculate an item's purchase price with stock adjustments and the shop discount.
 * @param transaction Shop transaction containing the price adjustments.
 * @param code One-based item code in the low halfword.
 * @return Purchase price from one through 99999999, or zero for an invalid code.
 */
s32 shop_get_buy_price(ShopTransaction* transaction, u32 code)
{
    u16 item_code = code;
    ItemCreationCategoryRecord* item = transaction_item_record(D_001B64F8, item_code);
    if (!item)
    {
        return 0;
    }
    u32 price = func_414130(item);
    if (item_code == 153)
    {
        price += transaction->play_time_seconds;
        if (price > 99999999)
        {
            price = 99999999;
        }
    }
    u8 unlimited_stock = D_001B64F0[item->catalog_index].unlimited_stock;
    if (!unlimited_stock && item_has_inventor(item))
    {
        s32 stock_adjustment;
        if (unlimited_stock)
        {
            stock_adjustment = 0;
        }
        else
        {
            stock_adjustment = 100 - item->shop_stock;
        }
        price = (s32)(price * ((stock_adjustment + 100) / 100.0f) + 0.99f);
    }
    if (static_cast<u8>(item->flags & 4))
    {
        price = (s32)(0.2f * price + 0.99f);
    }
    price = (s32)(price * ((100 - transaction->discount_percent) / 100.0f) + 0.99f);
    if (price == 0)
    {
        return 1;
    }
    if (price > 99999999)
    {
        price = 99999999;
    }
    return price;
}

u16 shop_get_category_item(const ShopTransaction* object, u8 category, u16 index)
{
    u16 value = 0;
    if (category < 8)
    {
        const ShopItemList* items = object->category_items + category;
        if (index < items->count)
        {
            value = items->item_codes[index];
        }
    }
    return value;
}

/**
 * @brief Initialize the shop lists, pending purchases and price adjustments.
 * @param transaction Shop transaction to initialize.
 * @param shop_id One-based shop identifier from one through 42.
 * @param discount_percent Purchase discount, capped at 99 percent.
 * @return One on success, or zero for an invalid shop identifier.
 */
s32 shop_init_transaction(ShopTransaction* transaction, u8 shop_id, u8 discount_percent)
{
    u8 valid = shop_id > 0 && shop_id < 43;
    if (!valid)
    {
        return 0;
    }
    func_0013A678(transaction, 0, sizeof(*transaction));
    transaction->shop_id = shop_id;
    transaction->shop_index = shop_id - 1;
    transaction->dynamic_inventory_slot = func_40B360(shop_id);
    transaction->discount_percent = discount_percent < 100 ? discount_percent : 99;
    transaction->play_time_seconds = func_11DF70(func_1012D0(func_10D8E0()));
    ShopItemList* all_items = &transaction->category_items[7];
    u16* output = all_items->item_codes;
    s32 count = 0;
    const u16* catalog = D_31A500[transaction->shop_index];
    while (true)
    {
        u16 item_code = *catalog++;
        if (item_code == 0)
        {
            break;
        }
        *output++ = item_code;
        ++count;
    }
    s32 slot = transaction->dynamic_inventory_slot;
    if (slot != 0)
    {
        DynamicShopInventory* shop = transaction_dynamic_shop(D_001B64F8, slot);
        for (s32 i = 0; i < 750; i++)
        {
            u16 item_code = i + 1;
            if (dynamic_shop_has_item(shop, item_code))
            {
                ItemCreationCategoryRecord* item = transaction_item_record(D_001B64F8, item_code);
                if (item->shop_stock > 0)
                {
                    *output++ = item_code;
                    ++count;
                }
            }
        }
    }
    all_items->count = count;
    const ShopItemList* list = &transaction->category_items[7];
    for (s32 i = 0; i < list->count; i++)
    {
        u16 item_code = list->item_codes[i];
        u8 category = transaction_item_category(&D_001B64F0[item_code - 1]);
        ShopItemList* destination = &transaction->category_items[category];
        destination->item_codes[destination->count] = item_code;
        ++destination->count;
    }
    return 1;
}

extern "C" void func_002FB840(void* object);

/** @brief Forward the object to func_002FB840. @param object Object to forward. */
extern "C" void func_002FAE00(void* object)
{
    func_002FB840(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FAE20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FAEB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FAF50);

u8 func_002FB510(const FieldStateTargets* object, u8 key)
{
    const u8 count = object->unk87;
    u8 result = 0;
    const FieldStateTargetEntry* entry = object->entries;
    for (s32 i = 0; i < count; i++, entry++)
    {
        if (key == entry->unk1c)
        {
            result = entry->unk1f;
            break;
        }
    }
    return result;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB560);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB5B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB650);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB6F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB840);

void func_002FB8A0(FieldStateTargets* object)
{
    FieldStateTargetEntry* entry = object->entries;
    for (s32 index = 0; index < object->unk87; index++)
    {
        entry->target->unk0a = 2;
        entry++;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB8E0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FB9B0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FBA90);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FBED0);

/** @brief Forward the object to func_002FB840. @param object Object to forward. */
extern "C" void func_002FBFC0(void* object)
{
    func_002FB840(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FBFE0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC120);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC310);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC730);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC880);

/** @brief Forward the object to func_002FB840. @param object Object to forward. */
extern "C" void func_002FC9D0(void* object)
{
    func_002FB840(object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FC9F0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FCB40);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FCC50);

extern "C" void func_002FD1B0(FieldFloatState5C* object, float first, float second, float third, float fourth, float fifth)
{
    object->enabled = 1;
    object->values[0] = first;
    object->values[1] = second;
    object->values[2] = third;
    object->values[3] = fourth;
    object->values[4] = fifth;
}

extern "C" LibClass178F30* D_001B6628;

/**
 * @brief Attach the window's auxiliary display to the resident display manager.
 * @param object Window containing the display.
 */
extern "C" void field_attach_model_display(FieldStatus14* object)
{
    D_001B6628->append_node(object->display, -1);
    D_001B6628->current_display = object->display;
    object->display_attached = 1;
}

extern "C" void* D_001B6650;
extern "C" void field_replace_model_camera(FieldStatus14* object, void* attached)
{
    if (object->display != 0)
    {
        D_001B6628->current_display = object->previous_display;
        object->display->func_003EF740();
        object->display = 0;
    }
    object->previous_display = D_001B6628->current_display;
    object->display = new (0) LibClass179080(D_001B6650);
    ((LibClass179080*)object->display)->copy_camera((const LibClass179080*)attached);
    ((LibClass179080*)object->display)->unk210 = &object->member;
    object->rotation = 1.57f;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD2E0);

extern "C" s32 func_002FD480(const FieldStatus14* object)
{
    return object->status == 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD490);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD640);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FD800);

/**
 * @brief Cancel pending model requests or restore and release an attached display.
 * @param object Model window containing the request state and auxiliary display.
 */
void field_cancel_model_request(FieldStatus14* object)
{
    FieldModelRequests* requests = (FieldModelRequests*)object;
    switch (object->status)
    {
        case 0:
        case 5:
            return;
        case 1:
            if (requests->first_request)
            {
                func_00103B20(D_001B65E8, requests->first_key, requests->first_request, 0, -1, 0);
            }
            if (requests->second_request)
            {
                func_00103B20(D_001B65E8, requests->second_key, requests->second_request, 0, -1, 0);
            }
            object->status = 8;
            return;
        case 2:
            object->status = 7;
            return;
        case 3:
        case 4:
            object->status = 5;
            return;
        default:
            if (object->display && object->display_attached && object->previous_display)
            {
                object->display_attached = 0;
                D_001B6628->current_display = object->previous_display;
                lib_object_detach_owner(object->display);
                object->display->func_003EF740();
                object->display = 0;
            }
            return;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FDA70);

/**
 * @brief Allocate an aligned byte buffer and request a model resource for an idle window.
 * @param object Model window receiving the resource.
 * @param key Resident resource key.
 * @return One when the request is accepted, or zero when busy, allocation fails or submission fails.
 */
s32 field_request_model_resource(FieldStatus14* object, s32 key)
{
    FieldModelRequests* state = (FieldModelRequests*)object;
    if (object->status != 0)
    {
        return 0;
    }
    state->first_key = key;
    state->second_key = 0;
    state->first_request = (u32)func_00139700(64, func_0011C8C0(D_001B65E4, key));
    if (!state->first_request)
    {
        return 0;
    }
    state->second_request = 0;
    if (!func_00103E70(D_001B65E8, key, state->first_request, 0x1357F, 1, 0, 0, 0, 1))
    {
        delete[] (u8*)state->first_request;
        state->first_request = 0;
        return 0;
    }
    object->status = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FDCD0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE020);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_001DF360__16FieldClass15BB90Fv);

extern "C" void func_002FD800(FieldStatus14* object);

/** @brief Restore the previous display, release the auxiliary display, and delete the window. */
void FieldClass15BB90::func_001DD7B0()
{
    func_002FD800(this);
    if (display && display_attached && previous_display)
    {
        display_attached = 0;
        D_001B6628->current_display = previous_display;
        lib_object_detach_owner(display);
        display->func_003EF740();
        display = 0;
    }
    lib_object_detach_owner(this);
    delete this;
}

FieldClass15BB90::~FieldClass15BB90()
{
}

/** @brief Initialize window state, owned transform storage, and homogeneous vectors. */
FieldClass15BB90::FieldClass15BB90()
{
    status = 0;
    unk1c = 0;
    unk20 = 0;
    unk24 = 0;
    unk28 = 0;
    unk2c = 0;
    unk30 = 0;
    unk34 = 0;
    unk38 = 0;
    unk3c = 0;
    unk40 = 0;
    unk44 = 0;
    unk48 = 0;
    unk4c = 0;
    unk50 = 0;
    previous_display = 0;
    unk58 = 0;
    unk54 = 0;
    unk5b = 0;
    display_attached = 0;
    unk5c = 0;
    display = 0;
    unk78 = 0;
    unk80.packed = 0;
    unk80.components[3] = 1.0f;
    unk90.packed = 0;
    unk90.components[3] = 1.0f;
}

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 3.
 */
s32 func_002FE870(FieldClass150070* object)
{
    return 3;
}

extern "C" void func_002FE880(FieldByte60F9C90* object)
{
    object->value = 9;
}

/** @brief Detach the object and add it to the resident release queue. @param object Object to release. */
extern "C" void func_002FE890(void* object)
{
    lib_object_detach_owner(object);
    resident_enqueue_object(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FE8C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FEA60);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FEC10);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FECF0);

extern "C" void func_4D00B0(void* object);

/** @brief Forward the object to func_4D00B0. @param object Object to forward. */
extern "C" void func_002FED30(void* object)
{
    func_4D00B0(object);
}

extern "C" void func_002FED50(void* object)
{
    u8* submission = static_cast<u8*>(object);
    if (object != 0)
    {
        submission += 0x90;
    }
    func_114100(D_001B6610, submission);
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FED80);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_002FFF50);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_00300D20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", __ct__16FieldClass15BBB0Fv);

extern "C" void func_00301090(FieldByte4F9C90* object)
{
    object->value = 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_003010A0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002F9C90", func_003010B0);
