#ifndef SO3_OVERLAYS_CITEMCREATION_TEXT_00358440_H
#define SO3_OVERLAYS_CITEMCREATION_TEXT_00358440_H

#include "types.h"

typedef struct ItemCreationCategoryOwner ItemCreationCategoryOwner;
typedef struct ItemCreationCategoryRecord ItemCreationCategoryRecord;
typedef struct ItemCreationIdentifierOwner ItemCreationIdentifierOwner;
struct ItemCreationAllocationRecord;

/** Partial item display with its decoded halfword and adjacent byte. */
typedef struct ItemCreationAllocationDisplay
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0xBC];
    u16 unkfc;
    u8 unkfe;
} ItemCreationAllocationDisplay;

/** Two nested markers allocated for each checked item display. */
typedef struct ItemCreationAllocationDisplayPair
{
    struct ItemCreationFlagNode* unk00;
    struct ItemCreationFlagNode* unk04;
} ItemCreationAllocationDisplayPair;

/** Partial owner of three checked item displays, marker pairs, and quantity displays. */
typedef struct ItemCreationCheckedAllocationView
{
    u8 unk00[0x10C];
    s16 unk10c;
    u8 unk10e[0xE];
    ItemCreationAllocationDisplay* unk11c[3];
    ItemCreationAllocationDisplayPair unk128[3];
    struct ItemCreationValueDisplay* unk140[3];
} ItemCreationCheckedAllocationView;

/** Partial owner of the value display refreshed from a checked record. */
typedef struct ItemCreationCheckedValueOwner
{
    u8 unk00[0xE4];
    struct ItemCreationValueDisplay* unke4;
} ItemCreationCheckedValueOwner;

/** Partial owner of two value displays refreshed from the current checked record. */
typedef struct ItemCreationTwoCheckedValueOwner
{
    u8 unk00[0xD0];
    struct ItemCreationValueDisplay* unkd0;
    u8 unkd4[4];
    struct ItemCreationValueDisplay* unkd8;
} ItemCreationTwoCheckedValueOwner;

/** Partial panel with paired markers, selected-state codes and value displays. */
typedef struct ItemCreationPanelView
{
    u8 unk00[0x38];
    struct ItemCreationListNode* unk38;
    u8 unk3c[0x6C];
    struct ItemCreationSelectedDisplayState* unka8;
    u8 unkac[0x24];
    u8 unkd0[8];
    u16 unkd8;
    u8 unkda[0xA];
    struct ItemCreationValueDisplay* unke4;
    struct ItemCreationPanelMarker* unke8[9];
    u8 unk10c;
    u8 unk10d;
    u8 unk10e[2];
    u32 unk110[3];
    u8 unk11c[4];
    struct ItemCreationValueDisplay* unk120;
} ItemCreationPanelView;

/** Partial resource view with nine assigned and fourteen available displays. */
typedef struct ItemCreationAvailableResourceView
{
    u8 unk00[0xA8];
    struct ItemCreationIndexedResourceDisplay* unka8[9];
    struct ItemCreationIndexedResourceDisplay* unkcc[14];
    u8 unk104[0x1C];
    struct ItemCreationSelectedDisplayState* unk120;
    u8 unk124;
} ItemCreationAvailableResourceView;

/** Partial owner of two color displays, a selector, and its target display. */
typedef struct ItemCreationTwoColorOwner
{
    u8 unk00[0xB4];
    struct ItemCreationColorDisplay* unkb4[2];
    u8 unkbc[0x10];
    struct FieldState23B3A0* unkcc;
    struct FieldObject23B950* unkd0;
} ItemCreationTwoColorOwner;

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
    u8 unk191[3];
    struct ItemCreationFlagNode* unk194[3];
    struct ItemCreationFlagNode* unk1a0[3];
    struct ItemCreationFlagNode* unk1ac[3];
    struct ItemCreationColorDisplay* unk1b8[3];
    struct ItemCreationColorDisplay* unk1c4[3];
    struct ItemCreationColorDisplay* unk1d0[3];
    struct ItemCreationColorDisplay* unk1dc[3];
    u8 unk1e8[9];
    u8 unk1f1;
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
 * @brief Update a checked item display and its quantity, or hide the displays for an empty item.
 * @param object Owner of the checked item and quantity displays.
 * @param value Signed item index; zero hides the displays.
 * @param quantity Quantity to display, or -1 to hide its display.
 * @param index Index of the display to update.
 */
void func_0035E150(ItemCreationCheckedAllocationView* object, s16 value, s32 quantity, s8 index);

/**
 * @brief Display the checked record's decoded value, or zero for an invalid checksum.
 * @param object Owner of the optional value display.
 */
void func_00366CB0(ItemCreationCheckedValueOwner* object);

/**
 * @brief Refresh each optional display from the checked resident value.
 * @param object Owner of the two optional value displays.
 */
void func_00359C80(ItemCreationTwoCheckedValueOwner* object);

/**
 * @brief Update panel marker visibility and values from the selected state.
 * @param object Panel associated with the selected state.
 */
void func_00366050(ItemCreationPanelView* object);

/**
 * @brief Refresh the available and assigned resource displays from the selected state.
 * @param object Resource view with an optional associated selected state.
 */
void func_00366F10(ItemCreationAvailableResourceView* object);

/**
 * @brief Advance the selector and refresh the colors and target of two item displays.
 * @param object Owner of the item displays, selector, and target display.
 */
void func_0035F710(ItemCreationTwoColorOwner* object);

/**
 * @brief Move the selector backward and refresh the colors and target of two item displays.
 * @param object Owner of the item displays, selector, and target display.
 */
void func_0035F7F0(ItemCreationTwoColorOwner* object);

/**
 * @brief Refresh the assigned-group markers, colors, and the two group grids.
 * @param object Nine-slot view containing three assigned-group displays.
 */
void func_00363D20(ItemCreationNineSlotView* object);

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
 * @brief Fill six item rows from a category's collected records and update their visibility.
 * @param object Owner of the record rows and category selection.
 * @param start First collected-record index to display.
 */
void func_0035B4E0(ItemCreationIdentifierOwner* object, s32 start);

/**
 * @brief Test whether a category is rejected by the selected mode or has no accepted records.
 * @param object Category display containing its selected state and mode.
 * @param category Category entry containing the zero-based catalog index.
 * @return One when its catalog fields fail the mode test or no collected record passes it; otherwise zero.
 */
u8 func_0035CAD0(ItemCreationCategoryOwner* object, const ItemCreationCategoryRecord* category);

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
/**
 * @brief Test whether a record is empty, rejected by the selected mode, or already assigned.
 * @param object Owner of the selected mode and assigned identifier pairs.
 * @param record Packed item record to test; null is accepted as an empty record.
 * @return True for an empty record, a failed mode predicate, or an assigned identifier.
 */
bool func_0035B310(ItemCreationIdentifierOwner* object, const struct ItemCreationAllocationRecord* record);
#endif

#ifdef __cplusplus
}
#endif

#endif
