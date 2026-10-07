#ifndef SO3_OVERLAYS_LIB_TEXT_004095C0_H
#define SO3_OVERLAYS_LIB_TEXT_004095C0_H

#include "types.h"

typedef struct ItemCreationAllocationRecord ItemCreationAllocationRecord;

typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;
typedef struct ItemCreationCategoryDefinition ItemCreationCategoryDefinition;

/** Twelve-byte category entry containing its list head and catalog index. */
struct ItemCreationCategoryRecord
{
    s16 unk00;
    u16 unk02;
    u8 unk04[4];
    u8 unk08;
    u8 unk09[3];
};

/** Thirty-two-byte catalog entry containing the three mode-selection fields. */
struct ItemCreationCategoryDefinition
{
    u8 unk00[0xB];
    u8 unk0b_low : 4;
    u8 unk0b_mode : 3;
    u8 unk0b_high : 1;
    u8 unk0c[4];
    u32 unk10_low : 10;
    u32 unk10_code : 10;
    u32 unk10_high : 12;
    u8 unk14[7];
    u8 unk1b_low : 6;
    u8 unk1b_flag : 1;
    u8 unk1b_high : 1;
    u8 unk1c[2];
    u8 unk1e_low : 1;
    u8 unk1e_value : 3;
    u8 unk1e_high : 4;
    u8 unk1f;
};

typedef ItemCreationCategoryRecord LibCategoryRecord;
typedef ItemCreationCategoryDefinition LibCategoryDefinition;

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief Collect a category's allocation records whose packed selection field is zero.
 * @param state Resident record and category-list storage.
 * @param records Output array receiving pointers to the collected records.
 * @param category One-based category identifier from one through seven hundred fifty.
 * @return Number of collected records, or zero for an invalid identifier or empty list.
 */
s32 func_0040CF90(const void* state, ItemCreationAllocationRecord** records, u16 category);

/**
 * @brief Return a packed record's table identifier unless its validated flag suppresses it.
 * @param record Packed item record to validate and locate in the resident table.
 * @return One-based table identifier, or zero for a valid checksum and bit 6 set in byte 7.
 */
s16 func_0040D890(const ItemCreationAllocationRecord* record);

/**
 * @brief Read one of eight ten-bit packed values when the record checksum is valid.
 * @param record Packed item record to validate and read.
 * @param index Packed value index from zero through seven.
 * @return The packed value, or zero for an invalid checksum or index.
 */
u16 func_0040D930(const ItemCreationAllocationRecord* record, u32 index);

#ifdef __cplusplus
}
#endif

#endif
