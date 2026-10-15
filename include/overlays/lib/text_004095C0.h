#ifndef SO3_OVERLAYS_LIB_TEXT_004095C0_H
#define SO3_OVERLAYS_LIB_TEXT_004095C0_H

#include "types.h"
#include "main/item_category.h"

typedef struct FieldRecord FieldRecord;

typedef struct ItemCreationAllocationRecord ItemCreationAllocationRecord;

typedef struct ItemCreationCategoryDefinition ItemCreationCategoryDefinition;

/** Thirty-two-byte item definition with packed stats, factors and inventory flags. */
struct ItemCreationCategoryDefinition
{
    u32 base_price : 24;
    u32 stamina : 8;
    u32 attack : 14;
    u32 hit : 14;
    /** Variant added to character-specific weapon resource IDs. */
    u32 weapon_variant : 4;
    u32 agility : 14;
    u32 defense : 14;
    u32 category : 3;
    /** Unused catalog entry, excluded from invention candidate lists. */
    u32 unused : 1;
    u32 intelligence : 14;
    u32 equipment_mask : 10;
    u32 luck : 8;
#ifdef __cplusplus
    u32 sort_order : 10;
    u32 model_index : 10;
    u32 initial_factor : 10;
    u32 unk13_high : 2;
#else
    union
    {
        struct
        {
            u32 sort_order : 10;
            u32 model_index : 10;
            u32 initial_factor : 10;
            u32 unk13_high : 2;
        };
        /** Low halfword containing the ten-bit list-order key. */
        u16 sort_key_bits;
    };
#endif
    u8 unk14[3];
    u8 unk17_low : 6;
    u8 unlimited_stock : 1;
    /** Also selects the reserved 100-allocation inventory pool. */
    u8 unsellable : 1;
    u8 unk18[3];
    u8 unk1b_low : 6;
    /** May supply factors as the second item in synthesis. */
    u8 synthesis_material : 1;
    u8 unk1b_high : 1;
    u32 final_factor : 10;
    /** Base difficulty used by invention and Specify Plan. */
    u32 creation_difficulty : 7;
    u32 creation_skill_id : 3;
    u32 unk1c_high : 12;
};

typedef ItemCreationCategoryRecord LibCategoryRecord;
typedef ItemCreationCategoryDefinition LibCategoryDefinition;

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Follow count list links from the object's first node. @return The node reached, or null if traversal ends early. */
void* func_00411DD0(void* object, s32 count);

/** Resident category catalog. */
extern ItemCreationCategoryDefinition* D_001B64F0;

/**
 * @brief Remove a flagged record from its category list and update the resident counts.
 * @param state Resident record and category-list storage.
 * @param identifier One-based signed record identifier from one through three thousand.
 * @return One on success, or zero when the identifier is invalid or the record is not flagged.
 */
s32 func_0040C9F0(void* state, s16 identifier);

/**
 * @brief Collect a category's allocation records that have no equipped owner.
 * @param state Resident record and category-list storage.
 * @param records Output array receiving pointers to the collected records.
 * @param category One-based category identifier from one through seven hundred fifty.
 * @return Number of collected records, or zero for an invalid identifier or empty list.
 */
s32 lib_collect_unequipped_allocations(const void* state, ItemCreationAllocationRecord** records, u16 category);

/**
 * @brief Return a packed record's table identifier unless its validated flag suppresses it.
 * @param record Packed item record to validate and locate in the resident table.
 * @return One-based table identifier, or zero for a valid checksum and bit 6 set in byte 7.
 */
s16 lib_allocation_get_identifier(const ItemCreationAllocationRecord* record);

/**
 * @brief Read one of eight ten-bit packed values when the record checksum is valid.
 * @param record Packed item record to validate and read.
 * @param index Packed value index from zero through seven.
 * @return The packed value, or zero for an invalid checksum or index.
 */
u16 func_0040D930(const ItemCreationAllocationRecord* record, u32 index);

/**
 * @brief Calculate eight comparison values for a protected entry and detail.
 * @param code Selected entry code.
 * @param entry Protected entry record, updated when its encoded values are repaired.
 * @param detail Protected detail record.
 * @param first First output value.
 * @param second Second output value.
 * @param third Third output value.
 * @param fourth Fourth output value.
 * @param fifth Fifth output value.
 * @param sixth Sixth output value.
 * @param seventh Seventh output value.
 * @param eighth Eighth output value.
 * @return Nonzero when the comparison values are available.
 */
u8 func_004095C0(s32 code, FieldRecord* entry, void* detail, s32* first, s32* second, s32* third, s32* fourth, s32* fifth, s32* sixth, s32* seventh,
                 s32* eighth);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00412C30(void* object);


/** Store the word at receiver offset 0x0. */
void func_0040B690(void* object, u32 value);


/** Store the byte at receiver offset 0x33. */
void func_0040B640(void* object, u8 value);

/** Store the byte at receiver offset 0x32. */
void func_0040B660(void* object, u8 value);

/** Store the byte at receiver offset 0x8. */
void func_0040B670(void* object, u8 value);

/** Store the byte at receiver offset 0x9. */
void func_0040B680(void* object, u8 value);

/** Store the byte at receiver offset 0x6. */
void func_0040B6B0(void* object, u8 value);

/** Store the byte at receiver offset 0x8D4. */
void func_0040FAF0(void* object, u8 value);

/** Store the byte at receiver offset 0x90A. */
void func_0040FB00(void* object, u8 value);


/** Store the low halfword at receiver offset 0x30. */
void func_0040B650(void* object, u32 value);

/** Store the low halfword at receiver offset 0x2. */
void func_0040B6C0(void* object, u32 value);

/** Return the fixed integer value 4. */
s32 func_0040E3A0(void* object);

/** Return the fixed integer value 1. */
s32 func_00415030(void* object);

/** Return the fixed integer value 12. */
s32 func_004194F0(void* object);

/** Return the fixed value 0. */
s32 func_004152B0(void* object);

void func_00411E10(void* object);
void func_00411E20(void* object);
void func_00412C00(void* object);
void func_00412C10(void* object);
void func_00412C20(void* object);
void func_00412C40(void* object);

#ifdef __cplusplus
}
#endif

#endif
