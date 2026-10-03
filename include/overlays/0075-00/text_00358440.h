#ifndef SO3_OVERLAYS_0075_00_TEXT_00358440_H
#define SO3_OVERLAYS_0075_00_TEXT_00358440_H

#include "types.h"

/** Partial view with nine markers and two twelve-marker groups. */
typedef struct ItemCreationNineSlotView
{
    u8 unk00[0xA8];
    struct ItemCreationSelectedDisplayState* unka8;
    struct FieldObject23CEA0* unkac;
    struct FieldObject23CEA0* unkb0;
    struct FieldObject23CEA0* unkb4;
    struct ItemCreationFlagNode* unkb8[9];
    struct ItemCreationFlagNode* unkdc[12];
    struct ItemCreationFlagNode* unk10c[12];
    struct FieldResourceDisplay2D5CF0* unk13c[9];
    u8 unk160[0x30];
    u8 unk190;
    u8 unk191[0x61];
    u8 unk1f2[9];
} ItemCreationNineSlotView;

/** Partial view with three activatable displays and fourteen selection markers. */
typedef struct ItemCreationFourteenSlotView
{
    u8 unk00[0xA8];
    struct ItemCreationSelectedDisplayState* unka8;
    struct FieldObject23CEA0* unkac;
    struct FieldObject23CEA0* unkb0;
    struct FieldObject23CEA0* unkb4;
    struct ItemCreationFlagNode* unkb8[14];
    struct FieldResourceDisplay2D5CF0* unkf0[14];
} ItemCreationFourteenSlotView;

/** Partial state containing three triples of item bytes. */
typedef struct ItemCreationTripleState
{
    u8 unk00[0x1F2];
    u8 unk1f2[3][3];
} ItemCreationTripleState;

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
 * @brief Refresh the nine item-resource displays and their assigned-item codes.
 * @param object View containing the item-resource displays and selection state.
 */
void func_003614B0(ItemCreationNineSlotView* object);

/**
 * @brief Refresh the fourteen item-resource displays and their marker bytes.
 * @param object View containing the item-resource displays and selection state.
 */
void func_00364D20(ItemCreationFourteenSlotView* object);

/**
 * @brief Activate the selected display and refresh its markers, or deactivate the displays and clear their markers.
 * @param object View containing nine markers and two twelve-marker groups.
 * @param mode One activates the selected display; zero deactivates displays; other values do nothing.
 */
void func_00360E60(ItemCreationNineSlotView* object, u16 mode);

/**
 * @brief Clear the view markers and mark the group selected by the current display index.
 * @param object View containing the markers and selected display.
 */
void func_00361220(ItemCreationNineSlotView* object);

/**
 * @brief Activate a selected display and its marker, or deactivate the current displays and markers.
 * @param object View containing the displays and fourteen selection markers.
 * @param mode One activates the selected display; zero deactivates the current displays; other values do nothing.
 */
void func_00364090(ItemCreationFourteenSlotView* object, u16 mode);

/**
 * @brief Report whether any byte in a selected item triple is nonzero.
 * @param object State containing the three item triples.
 * @param index Triple index, zero through two; other values report zero.
 * @return One when a byte in the selected triple is nonzero, or zero otherwise.
 */
u8 func_003623C0(ItemCreationTripleState* object, u8 index);

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
 * @brief Confirm the active slot and update its alternate field display.
 * @param object Fourteen-slot view linked to the selection state.
 * @return 1 when the active selection was processed, or 0 when unavailable.
 */
u8 func_003644F0(ItemCreationFourteenSlotView* object);

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
