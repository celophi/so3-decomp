#ifndef SO3_OVERLAYS_0075_00_TEXT_003684D0_H
#define SO3_OVERLAYS_0075_00_TEXT_003684D0_H

#include "types.h"

/** Partial display coordinate vector and dirty flag. */
typedef struct ItemCreationScrollPosition
{
    u8 unk00[0x18];
    float unk18;
    float unk1c;
    float unk20;
    float unk24;
    u8 unk28[0x14];
    u8 unk3c;
} ItemCreationScrollPosition;

/** Partial timed horizontal scroll state. */
typedef struct ItemCreationScrollState
{
    u8 unk00[0xAC];
    ItemCreationScrollPosition* unkac;
    s32 unkb0;
    u8 unkb4[4];
    s16 unkb8;
    u8 unkba;
    u8 unkbb[5];
    float unkc0;
    float unkc4;
    float unkc8;
} ItemCreationScrollState;

/** Partial node of a sentinel-based display list. */
typedef struct ItemCreationListNode
{
    void* unk00;
    struct ItemCreationListNode* unk04;
} ItemCreationListNode;

/** Display-list prefix containing its sentinel node. */
typedef struct ItemCreationList
{
    ItemCreationListNode* unk00;
} ItemCreationList;

/** Partial option-code table through entry 59. */
typedef struct ItemCreationOptionTable
{
    u8 unk00[0x188];
    s32 unk188[60];
} ItemCreationOptionTable;

/** Partial selection state with available and assigned items and three views. */
typedef struct ItemCreationSelectedDisplayState
{
    u8 unk00[0x40];
    ItemCreationOptionTable* unk40;
    u8 unk44[3];
    u8 unk47;
    u8 unk48[5];
    u8 unk4d;
    u8 unk4e[8];
    u8 unk56;
    u8 unk57;
    u8 unk58;
    u8 unk59;
    u8 unk5a[14];
    u8 unk68[9];
    u8 unk71[6];
    u8 unk77[6];
    u8 unk7d[0x2B];
    struct ItemCreationListDisplay* unka8;
    u8 unkac[4];
    struct ItemCreationThreeSlotDisplay* unkb0;
    u8 unkb4[4];
    struct ItemCreationFourteenSlotView* unkb8;
    struct ItemCreationNineSlotView* unkbc;
    struct ItemCreationDetailDisplay* unkc0;
    u8 unkc4[0x30];
    struct ItemCreationFlagResetOwner* unkf4;
    struct ItemCreationOptionDisplay* unkf8;
    struct ItemCreationOptionDisplay* unkfc;
    u8 unk100[0x18];
    void* unk118;
    void* unk11c;
    void* unk120;
    s16 unk124;
    s16 unk126;
    u8 unk128;
    u8 unk129;
    u8 unk12a;
    u8 unk12b;
    u8 unk12c;
    u8 unk12d;
} ItemCreationSelectedDisplayState;

/** Partial selection state with twelve float pairs and a byte permutation. */
typedef struct ItemCreationSelection
{
    float unk00[12][2];
    u8 unk60[12];
    u8 unk6c;
    u8 unk6d[12];
    u8 unk79;
} ItemCreationSelection;

/** Option lists are part of the same selected display state. */
typedef ItemCreationSelectedDisplayState ItemCreationOptionState;

/**
 * Updates the selected item or completes an exchange between the two views.
 * @param object Selection state.
 * @param selected Selected view, or null when clearing the selection.
 * @param index Signed item index; -1 clears the pending selection.
 */
void func_0036A050(ItemCreationSelectedDisplayState* object, void* selected, s16 index);

/**
 * Refreshes the display allocated for a group of three assigned items.
 * @param object Selection state.
 * @param group Byte-sized assigned-item group index.
 */
void func_003698E0(ItemCreationSelectedDisplayState* object, u8 group);

/** Partial destination for five resident record halfwords. */
typedef struct ItemCreationRuntimeRecordSelection
{
    u8 unk00[0x7E];
    u16 unk7e[5];
} ItemCreationRuntimeRecordSelection;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Hold the starting position, then advance and wrap the horizontal scroll.
 * @param object State containing the display coordinates and scroll limits.
 */
void func_00368BD0(ItemCreationScrollState* object);

/**
 * @brief Update the detail display with an item selected from either slot view.
 * @param object State owning the item arrays and views.
 * @param selected Slot view supplying the item, or another nonnull view to clear the item.
 * @param index Index into the array belonging to the selected slot view.
 */
void func_0036A500(ItemCreationSelectedDisplayState* object, void* selected, s16 index);

/**
 * @brief Refresh selection colors or one option display.
 * @param object State owning the lists and displays.
 * @param mode One updates item and slot colors; six and seven refresh the option displays.
 */
void func_0036A5D0(ItemCreationSelectedDisplayState* object, u8 mode);

/**
 * @brief Advance or cancel a four-step option transfer and refresh its displays.
 * @param object State containing the transfer fields and displays.
 * @param value Incoming byte value, or signed -1 to cancel the current step.
 */
void func_00369B80(ItemCreationSelectedDisplayState* object, s32 value);

/**
 * @brief Map an item byte to its associated halfword mask.
 * @param object Receiver; unused.
 * @param value Item byte to map.
 * @return Associated mask, or zero for an unmapped byte.
 */
u16 func_00369FA0(void* object, u8 value);

/**
 * @brief Initialize the twelve float pairs and their selection order.
 * @param object Selection state to initialize.
 */
void func_00369400(ItemCreationSelection* object);

/**
 * @brief Enable selection slots from resident section-four flags.
 * @param object Selection state whose mode may disable slots six through twelve.
 */
void func_00369510(ItemCreationSelection* object);

/**
 * @brief Refresh selection-slot flags and report success.
 * @param object Selection state to refresh.
 * @return Always one.
 */
s32 func_00369780(ItemCreationSelection* object);

/**
 * @brief Move through the circular selection order until an enabled slot is reached.
 * @param object Selection state containing a valid current slot and at least one enabled slot.
 * @param direction Values one and four move backward; values two and three move forward.
 * @return One-based index of the selected slot.
 */
u8 func_003696B0(ItemCreationSelection* object, u16 direction);

/**
 * @brief Copy the first halfword from each of five resident records.
 * @param object Destination state for the five copied values.
 */
void func_00369EB0(ItemCreationRuntimeRecordSelection* object);

/**
 * @brief Rebuild one option list from matching table entries 32 through 59.
 * @param object State whose table supplies at most six matching entries per option.
 * @param option Selected option, from one through eleven; other values leave the state unchanged.
 * @param list List to rebuild, one or two.
 */
void func_0036A780(ItemCreationOptionState* object, u16 option, u8 list);

/**
 * @brief Map the resident context code to a one-based selection slot.
 * @param object Selected display state; unused.
 * @return One through twelve for mapped codes, or zero otherwise.
 */
u8 func_0036AFE0(ItemCreationSelectedDisplayState* object);

/**
 * @brief Map the resident context code to its associated identifier.
 * @param object Receiver; unused.
 * @return Identifier 0x3521 through 0x352C for mapped codes, or 0x3520 otherwise.
 */
u16 func_0036B0E0(void* object);

/**
 * @brief Return the fixed value -1.
 * @param object Receiver or first argument; unused.
 * @return Always -1.
 */
s32 func_0036CD60(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_0036E540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E560(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036E730(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036E770(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E780(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E790(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E7A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E7C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E7E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E800(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E810(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E820(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036E830(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036E840(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036E850(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_0036EBD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036EC30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036EC50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036EC60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0036EC70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036EC90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0036ECA0(void* object);

/**
 * @brief Read the byte at offset 0x38.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_0036EBC0(void* object);

/**
 * @brief Write the word at offset 0x24.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_0036EBE0(void* object, u32 value);

/**
 * @brief Write the byte at offset 0x28.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_0036EBF0(void* object, u8 value);

/**
 * @brief Read the signed byte at offset 0x28.
 * @param object Object containing the field.
 * @return Field value.
 */
s8 func_0036EC00(void* object);

/**
 * @brief Copy one byte between object fields.
 * @param object Object to update.
 */
void func_0036E7D0(u8* object);

/**
 * @brief Return zero.
 * @param object Object argument; unused.
 * @return Returned value.
 */
float func_0036E7B0(void* object);

/**
 * @brief Return zero.
 * @param object Object argument; unused.
 * @return Returned value.
 */
float func_0036E7F0(void* object);

/**
 * @brief Test whether the value is negative.
 * @param object Object argument; unused.
 * @param value Value to store or test.
 * @return Returned value.
 */
s32 func_0036E740(void* object, float value);

/**
 * @brief Mark the object active and copy a 128-bit value.
 * @param object Object to update.
 * @param value Value to store or test.
 */
void func_0036E570(u8* object, const unsigned __int128* value);

/**
 * @brief Mark the object active and copy a 128-bit value.
 * @param object Object to update.
 * @param value Value to store or test.
 */
void func_0036E590(u8* object, const unsigned __int128* value);

/**
 * @brief Mark the object active and copy a 128-bit value.
 * @param object Object to update.
 * @param value Value to store or test.
 */
void func_0036E5F0(u8* object, const unsigned __int128* value);

/**
 * @brief Mark the object active and copy a 128-bit value.
 * @param object Object to update.
 * @param value Value to store or test.
 */
void func_0036E610(u8* object, const unsigned __int128* value);

/**
 * @brief Mark the object active and copy a 128-bit value.
 * @param object Object to update.
 * @param value Value to store or test.
 */
void func_0036E6D0(u8* object, const unsigned __int128* value);

/**
 * @brief Mark the object active and copy a 128-bit value.
 * @param object Object to update.
 * @param value Value to store or test.
 */
void func_0036E6F0(u8* object, const unsigned __int128* value);

/**
 * @brief Mark the object active and set its float components.
 * @param object Object to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void func_0036E5D0(u8* object, float x, float y, float z, float w);

/**
 * @brief Mark the object active and set its float components.
 * @param object Object to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_0036E710(u8* object, float x, float y, float z);

/**
 * @brief Mark the object active and set its float components.
 * @param object Object to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_0036E5B0(u8* object, float x, float y, float z);

/**
 * @brief Return the address of D_50CD30.
 * @return Address of D_50CD30.
 */
u8* func_0036E760(void);

/**
 * @brief Mark the object active and copy a four-component float value.
 * @param object Object to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_0036E690(u8* object, float x, float y, float z);

/**
 * @brief Follow the linked nodes at offset 4 up to the requested index.
 * @param object Object holding the first node pointer.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends early.
 */
void* func_0036EF70(u8* object, s32 index);

/**
 * @brief Follow the linked nodes at offset 4 up to the requested index.
 * @param object Object holding the first node pointer.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends early.
 */
void* func_0036F160(u8* object, s32 index);

/**
 * @brief Follow the linked nodes at offset 4 up to the requested index.
 * @param object Object holding the first node pointer.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends early.
 */
ItemCreationListNode* func_0036F230(ItemCreationList* object, s32 index);

#ifdef __cplusplus
}
#endif

#endif
