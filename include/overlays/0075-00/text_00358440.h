#ifndef SO3_OVERLAYS_0075_00_TEXT_00358440_H
#define SO3_OVERLAYS_0075_00_TEXT_00358440_H

#include "types.h"

/** Partial detail display containing its selected byte and associated mask. */
typedef struct ItemCreationDetailDisplay
{
    u8 unk00[0xA8];
    struct ItemCreationSelectedDisplayState* unka8;
    u8 unkac[0x55];
    u8 unk101;
    u16 unk102;
} ItemCreationDetailDisplay;

/** Partial nested item with two flag bytes and a float setting. */
typedef struct ItemCreationNested
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x30];
    float unk70;
} ItemCreationNested;

/** Partial owner of six pairs of nested items and optional auxiliary items. */
typedef struct ItemCreationPairOwner
{
    u8 unk00[0xA8];
    ItemCreationNested* unka8;
    ItemCreationNested* unkac;
    u8 unkb0[0x88];
    ItemCreationNested* unk138[6];
    ItemCreationNested* unk150[6];
    u8 unk168[0x24];
    ItemCreationNested* unk18c;
} ItemCreationPairOwner;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Refresh the detail display from its selected item and mask.
 * @param object Detail display to refresh.
 */
void func_00358850(ItemCreationDetailDisplay* object);

/**
 * @brief Set the flags of six item pairs and update optional auxiliary items.
 * @param object Owner of the nested items.
 * @param value Low byte to store in each paired item's flag.
 * @param alternate Low byte for auxiliary flags; the full value selects their float setting.
 */
void func_0035A6A0(ItemCreationPairOwner* object, u32 value, u32 alternate);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035AF70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035AF80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003641F0(void* object);

/**
 * @brief Set six pairs of nested objects to increasing float values and mark them active.
 * @param object Object holding the pairs of nested pointers.
 * @param start Base float value for the first pair.
 */
void func_0035B480(u8* object, float start);

/**
 * @brief Write the byte at offset 0x12C.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_0035C3F0(void* object, u8 value);

/**
 * @brief Set twelve groups of three nested objects to increasing float values and mark them active.
 * @param object Object holding the groups of nested pointers.
 * @param start Base float value for the first group.
 */
void func_0035C890(u8* object, float start);

/**
 * @brief Update the object from its nested item when the item state differs.
 * @param object Object holding the nested item at offset 0xD4.
 */
void func_00360440(u8* object);

/**
 * @brief Update the object from its nested item using the alternate state query.
 * @param object Object holding the nested item at offset 0xD4.
 */
void func_003604A0(u8* object);

/**
 * @brief Update object state using a selected value.
 * @param object Object to update.
 * @param value Selected value.
 */
void func_0035FCA0(u8* object, u16 value);

/**
 * @brief Read the word at offset 0x24.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_00366040(void* object);

/**
 * @brief Set a nested object's value and select its float setting.
 * @param object Object holding the nested pointer.
 * @param unused Unused second argument.
 * @param value Value to write at offset 0x3F; selects the float setting.
 */
void func_0035C4D0(u8* object, void* unused, u32 value);

/**
 * @brief Set the nested object's float value and active flag if present.
 * @param object Object holding the nested pointer.
 */
void func_0035E2D0(u8* object);

#ifdef __cplusplus
}
#endif

#endif
