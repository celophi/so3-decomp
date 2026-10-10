#ifndef SO3_OVERLAYS_1067_00_TEXT_002F1B20_H
#define SO3_OVERLAYS_1067_00_TEXT_002F1B20_H

#include "types.h"

/** Item codes in one shop category, with a signed used count. */
typedef struct ShopItemList
{
    u16 item_codes[750];
    s32 count;
} ShopItemList;

/** Shop inventory lists, pending purchases and price adjustments. */
typedef struct ShopTransaction
{
    ShopItemList category_items[8];
    /** Play time in seconds when the shop opened; added to Pomello Juice prices. */
    u32 play_time_seconds;
    u32 purchase_total;
    u16 unk2f08;
    u16 unk2f0a;
    u8 purchase_quantities[750];
    u8 shop_id;
    u8 shop_index;
    u8 dynamic_inventory_slot;
    u8 discount_percent;
    u8 unk31fe[2];
} ShopTransaction;

/** Partial target with an unsigned byte state. */
typedef struct FieldByteState0A
{
    u8 unk00[0xA];
    u8 unk0a;
} FieldByteState0A;

/** A 32-byte record containing a state target. */
typedef struct FieldStateTargetEntry
{
    FieldByteState0A* target;
    u8 unk04[0x18];
    u8 unk1c;
    u8 unk1d[2];
    u8 unk1f;
} FieldStateTargetEntry;

/** Partial receiver containing three target entries and their populated count. */
typedef struct FieldStateTargets
{
    FieldStateTargetEntry entries[3];
    u8 unk60[4];
    /** Required progress. */
    u32 unk64;
    /** Current progress. */
    u32 unk68;
    u8 unk6c[0xC];
    u32 unk78;
    s32 unk7c;
    u8 unk80[3];
    u8 unk83;
    u8 unk84[3];
    u8 unk87;
} FieldStateTargets;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002F2460(void* object);

/**
 * @brief Read a byte from the current global target.
 * @return The target byte at offset 0x140.
 */
u8 func_002F2880(void);

#ifdef __cplusplus
}
#endif

#endif
