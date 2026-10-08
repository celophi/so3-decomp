#ifndef SO3_MAIN_ITEM_CATEGORY_H
#define SO3_MAIN_ITEM_CATEGORY_H

#include "types.h"

typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;

/** Twelve-byte category entry containing its list head and catalog index. */
struct ItemCreationCategoryRecord
{
    s16 allocation_list_head;
    u16 catalog_index;
    u8 unk04[4];
    u8 unk08;
    u8 unk09[3];
};

#endif
