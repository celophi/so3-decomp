#ifndef SO3_OVERLAYS_CITEMCREATION_TEXT_003684D0_H
#define SO3_OVERLAYS_CITEMCREATION_TEXT_003684D0_H

#include "types.h"
#include "overlays/1067-00/text_002F1B20.h"
#ifdef __cplusplus
#include "overlays/1067-00/text_001E1590.h"
#endif

#ifdef __cplusplus
/** Common data prefix preceding the target callback table at offset 0x8C. */
struct ItemCreationTargetPrefix : public FieldStateTargets
{
    u8 unk88[4];
};
/** Target callback interface selected by MAIN vtable 0x184EF0. */
class ItemCreationClass184EF0 : public ItemCreationTargetPrefix
{
public:
    /** @brief Run the target status callback. @return Callback status. */
    virtual s32 func_slot08();
    /** @brief Run the target update callback. */
    virtual void func_slot0c();
    /** @brief Run the additional target callback. */
    virtual void func_slot10();
};
#endif

typedef struct ItemCreationTransformState ItemCreationTransformState;
struct FieldClass15AE70;
struct FieldRecordSelection;
struct ItemCreationClass186970;

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

/** Partial sentinel-based list with its stored node count. */
typedef struct ItemCreationCountedList
{
    ItemCreationListNode* unk00;
    s32 unk04;
} ItemCreationCountedList;

#ifdef __cplusplus
/** Counted display list with virtual destruction and an owned sentinel. */
class ItemCreationClass187A60 : public ItemCreationCountedList
{
public:
    /** @brief Allocate the sentinel node and initialize the list count. */
    ItemCreationClass187A60();
    /** @brief Release the list nodes and sentinel. */
    virtual ~ItemCreationClass187A60();
};
#endif

/** Partial option-code table through entry 59. */
typedef struct ItemCreationOptionTable
{
    u8 unk00[0x188];
    s32 unk188[60];
} ItemCreationOptionTable;

/** Partial selection state with available and assigned items and three views. */
typedef struct ItemCreationSelectedDisplayState
#ifdef __cplusplus
    : public FieldClass153E30
#endif
{
#ifdef __cplusplus
    /** @brief Destroy the selection state and its Field base. */
    virtual ~ItemCreationSelectedDisplayState();
    /** @brief Store the associated state pointer. @param value Pointer to store. */
    virtual void func_00263C70(void* value);
    /** @brief Return the associated state pointer. @return Stored pointer. */
    virtual void* func_00263CC0();
    /**
     * @brief Set a slot, consume an available category record, and reset its status bytes.
     * @param index Slot index from zero through two.
     * @param enabled Full-word state copied into the slot byte and tested for zero.
     */
    void func_0036BF30(s32 index, s32 enabled);
#else
    u8 unk00[0x34];
#endif
    void* unk34;
    u8 unk38[8];
    ItemCreationOptionTable* unk40;
    u8 unk44[3];
    u8 unk47;
    struct FieldRecordSelection* unk48;
    u8 unk4c;
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
    u8 unk7d[0x1B];
    struct FieldClass15AE70* unk98;
    struct FieldClass15AE70* unk9c;
    void* unka0;
    u8 unka4[4];
    struct ItemCreationListDisplay* unka8;
    u8 unkac[4];
    struct ItemCreationThreeSlotDisplay* unkb0;
    struct FieldClass15AE70* unkb4;
    struct ItemCreationFourteenSlotView* unkb8;
    struct ItemCreationClass1870B0* unkbc;
    struct ItemCreationClass186970* unkc0;
    u8 unkc4[0xC];
    struct ItemCreationClass186DB0* unkd0;
    struct ItemCreationClass186C90* unkd4;
    struct ItemCreationClass186770* unkd8;
    u8 unkdc[4];
    struct ItemCreationClass186070* unke0;
    struct FieldClass15AE70* unke4;
    struct ItemCreationClass185E60* unke8;
    u8 unkec[8];
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
    u8 unk12e[2];
    u16 unk130;
    u8 unk132[2];
    struct ItemCreationAssignedRecord* unk134;
    u8 unk138[0x10];
    u8 unk148[3];
    u8 unk14b[0x3D];
    u8 unk188[3][3];
    s8 unk191[3][3];
    u8 unk19a;
    u8 unk19b;
    struct FieldStatus14* unk19c;
    s32 unk1a0;
    s32 unk1a4;
    u8 unk1a8;
    u8 unk1a9[3];
    u32 unk1ac;
    u8 unk1b0;
    u8 unk1b1[3];
#ifdef __cplusplus
    ItemCreationClass184EF0* unk1b4[3];
#else
    struct FieldStateTargets* unk1b4[3];
#endif
    u8 unk1c0[3];
    u8 unk1c3[5];
    u32 unk1c8[3];
    u8 unk1d4[0xC];
    s8 unk1e0;
    u8 unk1e1;
    s16 unk1e2[3][2];
    u8 unk1ee[2];
    s32 unk1f0;
    u8 unk1f4[4];
    s16 unk1f8;
    s16 unk1fa;
} ItemCreationSelectedDisplayState;

/** Two scalar coordinates, cleared when a selection pair is constructed. */
typedef struct ItemCreationFloatPair
{
    float unk00[2];
#ifdef __cplusplus
    /** @brief Clear the two coordinates. */
    ItemCreationFloatPair()
    {
        unk00[1] = 0.0f;
        unk00[0] = 0.0f;
    }
#endif
} ItemCreationFloatPair;

/** Partial selection state with twelve float pairs and a byte permutation. */
typedef struct ItemCreationSelection
{
#ifdef __cplusplus
    /** @brief Initialize the selection coordinates and enabled slots. */
    ItemCreationSelection();
#endif
    ItemCreationFloatPair unk00[12];
    u8 unk60[12];
    u8 unk6c;
    u8 unk6d[12];
    u8 unk79;
#ifdef __cplusplus
    /** @brief Destroy the selection state. */
    virtual ~ItemCreationSelection()
    {
    }
    /**
     * @brief Refresh the enabled selection slots.
     * @return Always one.
     */
    virtual s32 func_slot0c();
    /** @brief Initialize the float pairs and selection order. */
    virtual void func_slot10();
#else
    void* unk7c;
#endif
} ItemCreationSelection;

/** Option lists are part of the same selected display state. */
typedef ItemCreationSelectedDisplayState ItemCreationOptionState;

#ifdef __cplusplus
/** Partial virtual root with no recovered data members. */
class ItemCreationClass184F08
{
public:
    /** @brief Destroy the virtual root. */
    virtual ~ItemCreationClass184F08()
    {
    }
};

/** Partial derived interface whose destructor also destroys the virtual root. */
class ItemCreationClass184F18 : public ItemCreationClass184F08
{
public:
    /** @brief Destroy the derived interface and its base. */
    virtual ~ItemCreationClass184F18();
};
#endif

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
 * @brief Update the selected item or complete an exchange between the two views.
 * @param object Selection state.
 * @param selected Selected view, or null when clearing the selection.
 * @param index Signed item index; -1 clears the pending selection.
 */
void func_0036A050(ItemCreationSelectedDisplayState* object, void* selected, s16 index);

/**
 * @brief Refresh the display allocated for a group of three assigned items.
 * @param object Selection state.
 * @param group Byte-sized assigned-item group index.
 */
void func_003698E0(ItemCreationSelectedDisplayState* object, u8 group);

/**
 * @brief Allocate a node and append its value to the sentinel-based list.
 * @param object List containing a valid sentinel node.
 * @param value Value to append; may be null.
 */
void func_0036F270(ItemCreationCountedList* object, void* value);

/** @brief Release every data node while retaining the list sentinel. @param object List to clear. */
void func_0036EEF0(ItemCreationCountedList* object);

/**
 * @brief Restore enabled selection flags from its saved assigned-item record.
 * @param object Selection state with an optional assigned-item record.
 */
void func_0036AE20(ItemCreationSelectedDisplayState* object);

/**
 * @brief Rebuild the available-item lists from the saved selection.
 * @param object Selection state containing the saved items and their flags.
 */
void func_0036AAA0(ItemCreationSelectedDisplayState* object);

/**
 * @brief Save the assigned-item state to resident records.
 * @param object Selection state containing the assigned items.
 */
void func_0036A8F0(ItemCreationSelectedDisplayState* object);

/**
 * @brief Save assigned items and append the selection state to the resident queue.
 * @param object Selection state to save and enqueue.
 */
void func_0036DEA0(ItemCreationSelectedDisplayState* object);

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
 * @brief Enable selection slots from resident section-four flags.
 * @param object Selection state whose mode may disable slots six through twelve.
 */
void func_00369510(ItemCreationSelection* object);

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
 * @brief Update the four-float transform and set its marker.
 * @param object Transform state to update.
 * @param input Source float vector.
 */
void func_0036E630(ItemCreationTransformState* object, const float* input);

/**
 * @brief Update the four-float transform and set its marker.
 * @param object Transform state to update.
 * @param input Source float vector.
 */
void func_0036E660(ItemCreationTransformState* object, const float* input);

/**
 * @brief Append a value to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param value Value stored in the appended node.
 */
void func_0036F1A0(ItemCreationCountedList* object, void* value);

/**
 * @brief Append a value to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param value Value stored in the appended node.
 */
void func_0036F040(ItemCreationCountedList* object, void* value);

/**
 * @brief Append a value to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param value Value stored in the appended node.
 */
void func_0036EFB0(ItemCreationCountedList* object, void* value);

/**
 * @brief Append a record pointer to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param record Record pointer stored in the appended node.
 */
void func_0036EDB0(ItemCreationCountedList* object, void* record);

/**
 * @brief Insert a record pointer after a node, or append it when no node is supplied.
 * @param object List containing the sentinel and stored count.
 * @param after Node to insert after, or null to append.
 * @param record Pointer to the record pointer copied into the new node.
 */
void func_0036EE40(ItemCreationCountedList* object, ItemCreationListNode* after, void* const* record);

/**
 * @brief Follow the linked nodes at offset 4 up to the requested index.
 * @param object Object holding the first node pointer.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends early.
 */
ItemCreationListNode* func_0036EF70(ItemCreationCountedList* object, s32 index);

/**
 * @brief Append a value to the sentinel list and increase its node count.
 * @param object List containing the sentinel and stored count.
 * @param value Value stored in the appended node.
 */
void func_0036F0D0(ItemCreationCountedList* object, void* value);

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

/**
 * @brief Choose an eligible assigned item and schedule its display resource.
 * @param object Selection state with assigned items, target states, and display resources.
 */
void func_0036C1C0(ItemCreationSelectedDisplayState* object);

#ifdef __cplusplus
}
#endif

#endif
