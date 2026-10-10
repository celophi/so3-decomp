#ifndef SO3_MAIN_ITEM_CATEGORY_H
#define SO3_MAIN_ITEM_CATEGORY_H

#include "types.h"

typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;

/** Twelve-byte category entry containing its list head and catalog index. */
struct ItemCreationCategoryRecord
{
    s16 allocation_list_head;
    u16 catalog_index;
    u8 unk04;
    u8 inventor_id;
    u8 unk06;
    u8 shop_stock;
    /** Items in inventory, excluding equipped items. */
    u8 inventory_count;
    u8 equipped_count;
    /** Unequipped items eligible for the battle item list. */
    u8 battle_usable_count;
    u8 flags;
};

#endif
