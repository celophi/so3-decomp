#ifndef SO3_OVERLAYS_1067_00_TEXT_002F1B20_H
#define SO3_OVERLAYS_1067_00_TEXT_002F1B20_H

#include "types.h"
#include "overlays/lib/vector.h"

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
    u32 play_time_seconds;
    u32 purchase_total;
    u16 pending_unsellable_count;
    u16 pending_sellable_count;
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
    u32 unk64;
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
/** Partial 0x80-byte record the Field object keeps a pointer to at 0x180. */
struct FieldClass15B9C0Record
{
    u8 unk00[0x80];
};

/**
 * Partial 0x1280-byte Field object, with MAIN vtable at 0x15B9C0. Only the slots before the destructor
 * (which sits at 0x1C) are placeholders.
 */
class FieldClass15B9C0
{
public:
    /** @brief Construct the object and its members. */
    FieldClass15B9C0();

    /** @brief Placeholder for the first vtable slot. */
    virtual void func_002EEE30();

    /** @brief Placeholder for an empty vtable slot. */
    virtual void func_slot0c();

    /** @brief Placeholder for an empty vtable slot. */
    virtual void func_slot10();

    /** @brief Placeholder for the vtable slot at 0x14. */
    virtual void func_001DD400();

    /** @brief Placeholder for the vtable slot at 0x18. */
    virtual void func_002F3300();

    virtual ~FieldClass15B9C0();

    u8 unk04[0x17C];
    FieldClass15B9C0Record* unk180;
    u8 unk184[0xDF8];
    u8* unkF7C;
    u8 unkF80[0xC];
    void* unkF8C;
    u8 unkF90[0x78];
    u8 unk1008;
    u8 unk1009;
    u8 unk100a;
    char unk100b[0x4F];
    s16 unk105a;
    u8 unk105c[0x14];
    s32 unk1070;
    u8 unk1074[0xC];
    FieldVec4A unk1080;
    float unk1090;
    float unk1094;
    s32 unk1098;
    u8 unk109c[0x1A8];
    u8 unk1244;
    u8 unk1245[8];
    u8 unk124d;
    u8 unk124e[0x32];
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Follow count list links from the object's first node.
 * @return The node reached, or null if traversal ends early.
 */
void* func_002F3250(void* object, s32 count);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002F2460(void* object);

/**
 * @brief Read a byte from the current global target.
 * @param object Field object; unused.
 * @return The target byte at offset 0x140.
 */
u8 func_002F2880(void* object);

#ifdef __cplusplus
}
#endif

#endif
