#ifndef SO3_MAIN_ITEM_CATEGORY_H
#define SO3_MAIN_ITEM_CATEGORY_H

#include "types.h"

#define ITEM_TYPE_COUNT 750

typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;

/** Twelve-byte category entry containing its list head and catalog index. */
struct ItemCreationCategoryRecord
{
    s16 allocation_list_head;
    u16 catalog_index;
    u8 first_creator_id;
    u8 inventor_id;
    u8 modification_count;
    u8 shop_stock;
    u8 inventory_count;
    u8 equipped_count;
    u8 battle_usable_count;
    u8 flags;
};

#endif
