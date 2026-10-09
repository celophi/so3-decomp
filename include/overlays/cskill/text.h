#ifndef SO3_OVERLAYS_CSKILL_TEXT_H
#define SO3_OVERLAYS_CSKILL_TEXT_H

#include "types.h"

/** Linked nodes used by the indexed list helpers. */
typedef struct SkillListNode
{
    void* value;
    struct SkillListNode* next;
#ifdef __cplusplus
    /** @brief Destroy a node without releasing its stored value. */
    ~SkillListNode()
    {
    }
#endif
} SkillListNode;

/** Float components stored by the paired-value lists. */
typedef struct SkillPairValue
{
    float first;
    float second;
} SkillPairValue;

/** List storage begins with an anchor node. */
typedef struct SkillList
{
    SkillListNode* head;
    u32 count;
} SkillList;

typedef struct SkillList183C48 SkillList183C48;
typedef struct SkillList183C38 SkillList183C38;
typedef struct SkillList184268 SkillList184268;
typedef struct SkillPairList184258 SkillPairList184258;
typedef struct SkillQueueOwner SkillQueueOwner;
typedef struct SkillProtectedDisplay SkillProtectedDisplay;
typedef struct SkillOptionsWindow SkillOptionsWindow;
typedef struct Record003619C0 Record003619C0;
typedef struct SkillDualSelection SkillDualSelection;
typedef struct SkillGridChoice SkillGridChoice;
typedef struct FieldClass15AE70 FieldClass15AE70;
typedef struct SkillProtectedFlags SkillProtectedFlags;
#ifdef __cplusplus
class FieldClass153E30;
class LibClass171EF0;
class LibObject178660;
#else
typedef struct FieldClass153E30 FieldClass153E30;
typedef struct LibClass171EF0 LibClass171EF0;
typedef struct LibObject178660 LibObject178660;
#endif
typedef struct SkillTextReceiver SkillTextReceiver;
typedef struct SkillComparisonDisplay SkillComparisonDisplay;
typedef struct SkillVector4 SkillVector4;
typedef struct SkillSecondarySelection SkillSecondarySelection;
typedef struct SkillFourRowSelection SkillFourRowSelection;
typedef struct SkillModeSelection SkillModeSelection;
typedef struct RecordWithMethods RecordWithMethods;
typedef struct Record003538F0 StatusOwner003534C0;
typedef struct Record003538F0 Record003538F0;
typedef struct Record00352B30 Record00352B30;
typedef struct Record0035A560 Record0035A560;
typedef struct StatusOwner003580D0 StatusOwner003580D0;
typedef struct Record003581B0 Record003581B0;
typedef SkillOptionsWindow Record0035E2A0;
typedef struct Record0035DE40 Record0035DE40;
typedef Record0035DE40 Record0035DDE0;
typedef struct Record0035D4A0 Record0035D4A0;
typedef struct Record0035D3E0 Record0035D3E0;
#ifdef __cplusplus
class ItemCreationClass175110;
typedef ItemCreationClass175110 Record00349DB0;
#else
typedef struct ItemCreationClass175110 Record00349DB0;
#endif
typedef SkillDualSelection Record0034BC40;
typedef struct Record00355420 Record00355420;
typedef struct Record00355490 Record00355490;
typedef Record003538F0 Record00355500;
typedef struct Record003610F0 Record003610F0;
typedef struct Record00361060 Record00361060;
typedef struct Record003611B0 Record003611B0;
typedef struct Record003620F0 Record003620F0;
typedef struct SkillProtectedDisplay Record00363740;
typedef SkillOptionsWindow Record00364810;
typedef struct Record00364720 Record00364720;
typedef struct SkillModeSelection Record0034C110;
typedef struct SkillModeSelection Record0034C1F0;

#ifdef __cplusplus
struct SkillPairListNode;
/** List with an allocated anchor, element count, and virtual destructor. */
struct SkillList183C48
{
    SkillListNode* head;
    u32 count;
    /** @brief Allocate the anchor and initialize an empty list. */
    SkillList183C48();
    /** @brief Release the linked nodes and the anchor. */
    virtual ~SkillList183C48();
};

/** List with an allocated anchor, element count, and virtual destructor. */
struct SkillList183C38
{
    SkillListNode* head;
    u32 count;
    /** @brief Allocate the anchor and initialize an empty list. */
    SkillList183C38();
    /** @brief Release the linked nodes and the anchor. */
    virtual ~SkillList183C38();
};

/** List with an allocated anchor, element count, and virtual destructor. */
struct SkillList184268
{
    SkillListNode* head;
    u32 count;
    /** @brief Allocate the anchor and initialize an empty list. */
    SkillList184268();
    /** @brief Release the linked nodes and the anchor. */
    virtual ~SkillList184268();
};

/** List with an allocated anchor, element count, and virtual destructor. */
struct SkillPairList184258
{
    SkillPairListNode* head;
    u32 count;
    /** @brief Allocate the anchor and initialize an empty list. */
    SkillPairList184258();
    /** @brief Release the linked nodes and the anchor. */
    virtual ~SkillPairList184258();
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Create and connect the owner windows. @param owner Window controller. @return One after setup. */
s32 func_0035B4E0(SkillQueueOwner* owner);
/** @brief Initialize the mode-query window. @param object Allocated window storage. @return Initialized storage. */
u8* func_003533E0(u8* object);

/**
 * @brief Append a pair of float values when node allocation succeeds.
 * @param list List receiver.
 * @param value Values copied into the new node.
 */
void func_00364BF0(SkillPairList184258* list, SkillPairValue value);

/**
 * @brief Initialize the nested window at its fixed coordinates and attach its panel widget.
 * @param object Window base receiver.
 * @param associated Full resource source word.
 * @return One when the panel allocation succeeds, or zero otherwise.
 */
s32 func_00351980(FieldClass15AE70* object, u32 associated);

/**
 * @brief Refresh the selection rows and clear the associated active window's grid-list flags.
 * @param object Window with the selection rows.
 */
void func_00351AC0(Record00352B30* object);

/**
 * @brief Enable the selection display and show the current row's mode description.
 * @param object Window with the selected row and attached display.
 */
void func_00351B30(Record00352B30* object);

/**
 * @brief Switch to the associated selection window for row modes four and five.
 * @param object Window containing the mode table and attached display.
 */
void func_003522C0(Record00352B30* object);

/**
 * @brief Rebuild the mode query's displayed selection state.
 * @param record Mode-query receiver.
 */
void func_00351BE0(Record00352B30* record);

/**
 * @brief Update owner and window messages for the selected six-row entry.
 * @param object Six-row window receiver.
 */
void func_00353720(void* object);

/**
 * @brief Update the controller's selected code and associated display state.
 * @param owner Controller receiver.
 * @param code Selected code.
 * @param enabled State flag.
 */
void func_0035AF00(SkillQueueOwner* owner, s32 code, u8 enabled);

/**
 * @brief Dispatch direction one and refresh when the grid reports a change.
 * @param record Selection receiver.
 */
void func_003521C0(Record00352B30* record);

/**
 * @brief Dispatch direction zero and refresh when the grid reports a change.
 * @param record Selection receiver.
 */
void func_00352240(Record00352B30* record);

/**
 * @brief Refresh the description when this receiver is the active selection.
 * @param object Selection receiver.
 */
void func_003538A0(void* object);

/**
 * @brief Move the secondary grid in direction one and notify the owner when its index changes.
 * @param object Secondary grid window.
 */
void func_00359D80(SkillSecondarySelection* object);

/**
 * @brief Move the secondary grid in direction zero and notify the owner when its index changes.
 * @param object Secondary grid window.
 */
void func_00359E30(SkillSecondarySelection* object);
/**
 * @brief Initialize the three-row secondary selection window and its resource badges.
 * @param object Secondary selection window.
 * @param associated Full resource source word.
 * @return One on success; zero if the owner or an initial display allocation is absent.
 */
s32 func_00359EE0(SkillSecondarySelection* object, u32 associated);

/**
 * @brief Activate the secondary grid and update its controller's selected code.
 * @param object Secondary selection receiver.
 */
void func_003592E0(SkillSecondarySelection* object);

/**
 * @brief Release the listed display objects and run the base window release hook.
 * @param object Display-list receiver.
 */
void func_00361150(Record00364810* object);

/**
 * @brief Set the nested text receiver's resource key when present.
 * @param record Window receiver.
 * @param key Text resource key.
 */
void func_00348CB0(SkillComparisonDisplay* record, u32 key);

/**
 * @brief Load text keys 6001 through 6005 and refresh the width limit.
 * @param record Text display receiver.
 * @param key Text resource key.
 */
void func_0035A650(Record0035A560* record, s32 key);

/**
 * @brief Create the scrolling text display and its enclosing frames.
 * @param object Scrolling text window.
 * @param associated Full resource source word.
 * @return One when setup succeeds, or zero when a required display allocation fails.
 */
s32 func_0035A6E0(Record0035A560* object, u32 associated);

/**
 * @brief Apply the selected record's mode to its protected byte table.
 * @param record Selection receiver.
 * @return Mode application result.
 */
u8 func_003523A0(Record00352B30* record);

/**
 * @brief Store the cursor for the selected slot and apply its mode.
 * @param record Selection receiver.
 * @return Zero when inactive or empty, three when the mode reports three, or one otherwise.
 */
s32 func_00352A90(Record00352B30* record);

/**
 * @brief Update the selected record's value display and mark both change flags.
 * @param object Selected-record display receiver.
 */
void func_00363660(SkillProtectedDisplay* object);

/**
 * @brief Decode the second protected value and mark a valid flag record on corruption.
 * @param record Protected values receiver.
 * @return Decoded value, or zero when its checksum is invalid.
 */
u32 func_00356EE0(SkillProtectedFlags* record);

/**
 * @brief Decode the first protected value and mark a valid flag record on corruption.
 * @param record Protected values receiver.
 * @return Decoded value, or zero when its checksum is invalid.
 */
u32 func_00357230(SkillProtectedFlags* record);

/**
 * @brief Enqueue the receiver's secondary interface for processing.
 * @param record Receiver to enqueue, or null.
 */
void func_0035B4B0(SkillQueueOwner* record);

/**
 * @brief Add flag bits when the protected record's checksum is valid.
 * @param record Encoded flags receiver.
 * @param flags Flag bits to add.
 * @return Updated decoded flags, or five when the checksum is invalid.
 */
u32 func_00357350(SkillProtectedFlags* record, u32 flags);

/**
 * @brief Retain selected flag bits when the protected record's checksum is valid.
 * @param record Encoded flags receiver.
 * @param flags Mask of flag bits to retain.
 * @return Updated decoded flags, or five when the checksum is invalid.
 */
u32 func_0035FA20(SkillProtectedFlags* record, u32 flags);

/**
 * @brief Release all paired-value nodes after the anchor and reset the count.
 * @param record List receiver.
 */
void func_00364B70(SkillPairList184258* record);

/**
 * @brief Update the vector at offset 0x30 and mark the receiver changed.
 * @param object Vector receiver.
 * @param value Vector components.
 */
void func_0035C1F0(LibClass171EF0* object, const SkillVector4* value);

/**
 * @brief Update the vector at offset 0x30 and mark the receiver changed.
 * @param object Vector receiver.
 * @param value Vector components.
 */
void func_0035C220(LibClass171EF0* object, const SkillVector4* value);

/**
 * @brief Forward the receiver to its state update helper.
 * @param object Receiver to update.
 */
void func_0035D440(void* object);

/**
 * @brief Set the selected display object's status to one.
 * @param object Selection display receiver.
 */
void func_003621F0(Record003619C0* object);

/**
 * @brief Advance the paired display lists toward scroll position 16.
 * @param record Paired display list receiver.
 * @return Zero.
 */
s32 func_003619C0(Record003619C0* record);

/**
 * @brief Move the paired display lists toward scroll position zero.
 * @param record Paired display list receiver.
 * @return Zero.
 */
s32 func_00361B90(Record003619C0* record);

/** @brief Advance one grid entry, scrolling the paired rows at the bottom edge. @param object Paired-row window. */
void func_00361D60(Record003619C0* object);
/** @brief Move back one grid entry, scrolling the paired rows at the top edge. @param object Paired-row window. */
void func_00361E50(Record003619C0* object);
/** @brief Advance two grid entries, scrolling the paired rows at the bottom edge. @param object Paired-row window. */
void func_00361F30(Record003619C0* object);
/** @brief Move back two grid entries, scrolling the paired rows at the top edge. @param object Paired-row window. */
void func_00362010(Record003619C0* object);

/**
 * @brief Write the 8-bit field at offset 0xC.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348400(FieldClass15AE70* object, u8 value);

/**
 * @brief Read the 8-bit field at offset 0xC.
 * @param object Receiver storage.
 * @return Field value.
 */
u8 func_00348410(FieldClass15AE70* object);

/**
 * @brief Write the 8-bit field at offset 0x8.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348420(FieldClass15AE70* object, u8 value);

/**
 * @brief Read the 8-bit field at offset 0x8.
 * @param object Receiver storage.
 * @return Field value.
 */
u8 func_00348430(FieldClass15AE70* object);

/**
 * @brief Write the 16-bit field at offset 0xA.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348440(FieldClass15AE70* object, u16 value);

/**
 * @brief Read the 16-bit field at offset 0xA.
 * @param object Receiver storage.
 * @return Field value.
 */
u16 func_00348450(FieldClass15AE70* object);

/**
 * @brief Store the alternate associated pointer.
 * @param object Window receiver.
 * @param value Pointer to store.
 */
void func_00348480(FieldClass15AE70* object, void* value);

/**
 * @brief Return the alternate associated pointer.
 * @param object Window receiver.
 * @return Stored pointer.
 */
void* func_00348490(FieldClass15AE70* object);

/**
 * @brief Write the 32-bit field at offset 0x4.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_003484A0(FieldClass15AE70* object, u32 value);

/**
 * @brief Read the 32-bit field at offset 0x4.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_003484B0(FieldClass15AE70* object);

/**
 * @brief Return the nested display container.
 * @param object Window receiver.
 * @return Stored container pointer.
 */
LibObject178660* func_003484C0(FieldClass15AE70* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348510(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348520(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348580(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348610(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348620(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348630(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348640(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348650(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348660(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348670(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348680(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348690(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486E0(void* object);

/**
 * @brief Read the 8-bit field at offset 0xD.
 * @param object Receiver storage.
 * @return Field value.
 */
u8 func_003486F0(FieldClass15AE70* object);

/**
 * @brief Write the 8-bit field at offset 0xD.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348700(FieldClass15AE70* object, u8 value);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348710(void* object);

/** @brief Update the message for the current selection mode. @param object Window with paired selection grids. */
void func_00349E80(SkillDualSelection* object);
/** @brief Set the paired grid mode and update its display flags. @param object Window with paired grids. @param mode Signed mode code. */
void func_00349F30(SkillDualSelection* object, s16 mode);
/**
 * @brief Hide the paired status displays and return to the associated window.
 * @param object Paired selection window.
 * @return Two after switching windows, or three when no associated window exists.
 */
s32 func_0034A580(SkillDualSelection* object);
/** @brief Refresh the first selection rows. @param object Window receiver. @param reset Nonzero to reset the grid position. */
void func_0034A2B0(SkillDualSelection* object, s32 reset);
/** @brief Refresh the second selection rows. @param object Window receiver. @param reset Nonzero to reset the grid position. */
void func_0034A130(SkillDualSelection* object, s32 reset);
/** @brief Move the active grid in direction one and refresh its rows. @param object Window receiver. */
void func_0034AF90(SkillDualSelection* object);
/** @brief Move the active grid in direction zero and refresh its rows. @param object Window receiver. */
void func_0034B090(SkillDualSelection* object);

/**
 * @brief Run the window callback when its current selection is active.
 * @param object Window with two selection grids and a signed mode.
 */
void func_0034AF00(SkillDualSelection* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0034A560(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0034A570(void* object);

/**
 * @brief Write the 32-bit field at offset 0x20.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0034A640(u8* object, u32 value);

/**
 * @brief Initialize the receiver metadata and its embedded object, then return its address.
 * @param object Receiver storage.
 * @return Address of the receiver.
 */
u8* func_0034BCB0(u8* object);

/**
 * @brief Read the 32-bit field at offset 0x20.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_0034C520(u8* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0034C530(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0034C540(void* object);

/**
 * @brief Read the 32-bit field at offset 0x44.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_0034C7C0(u8* object);

/**
 * @brief Initialize the receiver metadata and return its address.
 * @param object Receiver storage.
 * @return Address of the receiver.
 */
u8* func_00357EE0(u8* object);

/**
 * @brief Handle the pending action when both status flags are set.
 * @param object Receiver storage.
 */
void func_003581B0(void* object);

/**
 * @brief Refresh the selected detail pointer and checksum-protected status values.
 * @param record Selection and status display storage.
 */
void func_00358200(Record003581B0* record);

/**
 * @brief Forward the current grid index to the active window's choice callback.
 * @param object Window with a grid selection.
 */
void func_0035CD50(SkillGridChoice* object);

/**
 * @brief Apply the current grid choice and report the callback status.
 * @param object Window with a grid selection.
 * @return One when the callback returns zero, or two otherwise.
 */
s32 func_0035CEB0(SkillGridChoice* object);

/**
 * @brief Hide the window lists, restore its associated selection, and queue its callback.
 * @param object Window base receiver.
 * @return Always two.
 */
s32 func_0035CE30(FieldClass15AE70* object);


/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00359480(void* object);

/**
 * @brief Read the 32-bit field at offset 0x24.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_00359490(u8* object);

/**
 * @brief Initialize the receiver metadata and return its address.
 * @param object Receiver storage.
 * @return Address of the receiver.
 */
u8* func_0035ABC0(u8* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035AC40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035C030(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035C040(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_0035C100(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035C110(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035C120(void* object);

/**
 * @brief Store a 128-bit value at offset 0x20 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C130(LibClass171EF0* object, const unsigned __int128* value);

/**
 * @brief Store a 128-bit value at offset 0x20 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C150(LibClass171EF0* object, const unsigned __int128* value);

/**
 * @brief Store 3 float values at offset 0x20 and set the byte at 0x50. Set the fourth float to 1.0f.
 * @param object Receiver storage.
 * @param x Float value to store.
 * @param y Float value to store.
 * @param z Float value to store.
 */
void func_0035C170(LibClass171EF0* object, float x, float y, float z);

/**
 * @brief Store 4 float values at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param x Float value to store.
 * @param y Float value to store.
 * @param z Float value to store.
 * @param w Float value to store.
 */
void func_0035C190(LibClass171EF0* object, float x, float y, float z, float w);

/**
 * @brief Store a 128-bit value at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C1B0(LibClass171EF0* object, const unsigned __int128* value);

/**
 * @brief Store a 128-bit value at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C1D0(LibClass171EF0* object, const unsigned __int128* value);

/**
 * @brief Update the vector at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param x First float component.
 * @param y Second float component.
 * @param z Third float component.
 */
void func_0035C250(LibClass171EF0* object, float x, float y, float z);

/**
 * @brief Store a 128-bit value at offset 0x40 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C290(LibClass171EF0* object, const unsigned __int128* value);

/**
 * @brief Store a 128-bit value at offset 0x40 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C2B0(LibClass171EF0* object, const unsigned __int128* value);

/**
 * @brief Store 3 float values at offset 0x40 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param x Float value to store.
 * @param y Float value to store.
 * @param z Float value to store.
 */
void func_0035C2D0(LibClass171EF0* object, float x, float y, float z);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0035C2F0(void* object);

/**
 * @brief Test whether a float is less than zero.
 * @param value Value to test.
 * @return 1 when the value is less than zero; otherwise 0.
 */
bool func_0035C300(float value);

/**
 * @brief Return the address of D_50CD30.
 * @return Address of D_50CD30.
 */
u8* func_0035C320(void);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0035C330(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035C340(void* object);

/**
 * @brief Write the 32-bit field at offset 0x24.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C350(u8* object, u32 value);

/**
 * @brief Write the 8-bit field at offset 0x28.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C360(FieldClass153E30* object, u8 value);

/**
 * @brief Read the signed 8-bit field at offset 0x28.
 * @param object Receiver storage.
 * @return Field value.
 */
s8 func_0035C370(FieldClass153E30* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0035C380(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0035C390(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035C3A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035C3B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035C3C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0035C3D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0035C3E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0035C3F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0035C400(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_0035C410(void* object);

/**
 * @brief Read the 8-bit field at offset 0x40.
 * @param object Receiver storage.
 * @return Field value.
 */
u8 func_0035C420(u8* object);

/**
 * @brief Read the 32-bit field at offset 0x3C.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_0035C430(u8* object);

/**
 * @brief Find a node by walking from the list anchor.
 * @param list List to search.
 * @param index Number of links to follow from the first node.
 * @return Node at the given index, or 0 if an earlier link is null.
 */
SkillListNode* func_0035C890(SkillList* list, s32 index);

/**
 * @brief Find a node by walking from the list anchor.
 * @param list List to search.
 * @param index Number of links to follow from the first node.
 * @return Node at the given index, or 0 if an earlier link is null.
 */
SkillListNode* func_0035CAE0(SkillList* list, s32 index);

/**
 * @brief Update paired-list positions and color values using the row spacing.
 * @param record Receiver with the two lists and their base positions.
 * @param offset Vertical offset subtracted from both base positions.
 */
void func_0034C110(Record0034C110* record, float offset);

/**
 * @brief Update paired-list item visibility and colors for the current selection.
 * @param record Receiver containing paired lists and selection values.
 */
void func_0034BEE0(Record0034C1F0* record);

/**
 * @brief Refresh the selected item's display receiver and color.
 * @param record Receiver containing the item list and selection state.
 */
void func_0034C1F0(Record0034C1F0* record);

/** @brief Advance the mode window animation. @param object Mode window. */
void func_0034C060(SkillModeSelection* object);

/** @brief Update the active mode window and its list indicator. @param object Mode window. */
void func_0034C320(SkillModeSelection* object);

/**
 * @brief Configure the second grid and register its newly allocated display object.
 * @param record Receiver containing the second grid and display owner.
 * @return One after setup, otherwise zero without the second grid.
 */
s32 func_0034B190(SkillDualSelection* record);

/**
 * @brief Configure the first grid and register its newly allocated display object.
 * @param record Receiver containing the first grid and display owner.
 * @return One after setup, otherwise zero without the first grid.
 */
s32 func_0034B2C0(SkillDualSelection* record);

/** @brief Advance the mode selection by one row and refresh its owner message. @param object Mode selection window. */
void func_0034DF00(SkillModeSelection* object);

/** @brief Move the mode selection back one row and refresh its owner message. @param object Mode selection window. */
void func_0034E0B0(SkillModeSelection* object);

/**
 * @brief Advance the mode selection by one page and refresh its owner message.
 * @param object Mode selection window.
 * @return Zero.
 */
s32 func_0034DA70(SkillModeSelection* object);

/**
 * @brief Configure the selection grid position and register its display state.
 * @param record Receiver with the display owner and selection grid.
 * @param row_count Number of grid rows; zero leaves the grid unchanged.
 * @return One for zero rows or completed setup, otherwise zero without a display owner.
 */
s32 func_0034E260(Record0034C1F0* record, s16 row_count);

/** @brief Create the mode window's text and image rows. @param object Mode window. @return Nonzero after creating the rows. */
s32 func_00351090(SkillModeSelection* object);
/** @brief Initialize the mode window and attach its displays. @param object Mode window. @param associated Full resource source word. @return One on success; zero on allocation or row initialization failure. */
s32 func_00351490(SkillModeSelection* object, u32 associated);

/** @brief Attach three resource displays to the window. @param object Window to initialize. @param associated Full resource source word. @return One after attaching the displays. */
s32 func_0035AC50(FieldClass15AE70* object, u32 associated);

/** @brief Create and attach the text receiver's seven displays. @param object Text receiver. @param associated Full resource source word. @return One after attaching all displays. */
s32 func_003499B0(SkillTextReceiver* object, u32 associated);

/**
 * @brief Initialize the receiver metadata and its embedded object, then return its address.
 * @param object Receiver storage.
 * @return Address of the receiver.
 */
u8* func_003611F0(u8* object);

/**
 * @brief Apply mode 1 to the primary record when the selector permits it.
 * @param record Receiver with primary, mode, and state references.
 * @return Primary operation's status, or zero when a guard prevents it.
 */
s32 func_003620F0(Record003620F0* record);

/**
 * @brief Apply mode 0 to the primary record when the selector permits it.
 * @param record Receiver with primary, mode, and state references.
 * @return Primary operation's status, or zero when a guard prevents it.
 */
s32 func_00362170(Record003620F0* record);

/**
 * @brief Update the primary record's selection and derived status items.
 * @param record Primary receiver.
 * @param mode Nonzero advances selection; zero moves it backward.
 * @return Zero without a selection, otherwise 4.
 */
s32 func_00363740(Record00363740* record, s32 mode);

/** @brief Refresh displays from the currently selected protected record. @param object Selected-record window. */
void func_00363890(Record00363740* object);

/**
 * @brief Initialize the receiver metadata and return its address.
 * @param object Receiver storage.
 * @return Address of the receiver.
 */
u8* func_00362F70(u8* object);

/**
 * @brief Initialize the receiver metadata and return its address.
 * @param object Receiver storage.
 * @return Address of the receiver.
 */
u8* func_00363610(u8* object);

/**
 * @brief Initialize the receiver metadata and return its address.
 * @param object Receiver storage.
 * @return Address of the receiver.
 */
u8* func_00364670(u8* object);

/**
 * @brief Release the embedded list and base state, then optionally free the owner.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
Record00364720* func_00364720(Record00364720* record, s16 flag);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003647E0(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_003647F0(void* object);

/**
 * @brief Copy the byte at offset 0xA8 to offset 0x60.
 * @param object Receiver storage.
 */
void func_00364800(u8* object);

/**
 * @brief Update the status bytes selected by a mode value.
 * @param object Receiver with pointers to status records.
 * @param mode Zero clears all seven records; a positive or negative value selects one of two records.
 */
void func_00349920(u8* object, s32 mode);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C9D0(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035CB20(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035CBB0(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C440(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C4D0(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C560(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C5F0(SkillList* list, void* value);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_0035C780(SkillList* list, void* value);

/**
 * @brief Release the list nodes and anchor, then optionally free the owner.
 * @param record List owner to release, or null.
 * @param flag Positive values release the owner's storage.
 * @return Original owner pointer.
 */
SkillList184268* func_00364960(SkillList184268* record, s16 flag);

/**
 * @brief Release linked nodes after the anchor and clear the list when nonempty.
 * @param record List owner whose nodes are released.
 */
void func_00364A70(SkillList184268* record);

/**
 * @brief Release all linked nodes after the anchor and reset the list count.
 * @param record List receiver.
 */
void func_0035C810(SkillList183C48* record);

/**
 * @brief Release all linked nodes after the anchor and reset the list count.
 * @param record List receiver.
 */
void func_0035CA60(SkillList183C38* record);

/**
 * @brief Append a value to the list.
 * @param list List to extend.
 * @param value Value stored in the new node.
 */
void func_003649E0(SkillList* list, void* value);


/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_00349E20(RecordWithMethods* record, s16 flag);

/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_00353380(RecordWithMethods* record, s16 flag);

/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_00357E80(RecordWithMethods* record, s16 flag);

/**
 * @brief Initialize the nested window and attach its rectangular panel widget.
 * @param object Window base receiver.
 * @param associated Full resource source word.
 * @return One when the panel allocation succeeds, or zero otherwise.
 */
s32 func_00357F80(FieldClass15AE70* object, u32 associated);

/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_00358070(RecordWithMethods* record, s16 flag);


/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_0035A500(RecordWithMethods* record, s16 flag);

/**
 * @brief Advance the display horizontally after the initial counter phase.
 * @param record Record containing the display, counter, and position controls.
 */
void func_0035A560(Record0035A560* record);

/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_0035AB60(RecordWithMethods* record, s16 flag);

/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_0035AEA0(RecordWithMethods* record, s16 flag);

/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_003635B0(RecordWithMethods* record, s16 flag);

/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_00364610(RecordWithMethods* record, s16 flag);

/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_00364880(RecordWithMethods* record, s16 flag);

/**
 * @brief Release the record and optionally free its storage.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
Record0035DE40* func_0035DE40(Record0035DE40* record, s16 flag);

/**
 * @brief Release nested state and optionally free the record.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
Record00349DB0* func_00349DB0(Record00349DB0* record, s16 flag);

/**
 * @brief Release nested state and optionally free the record.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
Record0034BC40* func_0034BC40(Record0034BC40* record, s16 flag);


/**
 * @brief Release nested state and optionally free the record.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
RecordWithMethods* func_00351A60(RecordWithMethods* record, s16 flag);

/**
 * @brief Release nested state and optionally free the record.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
Record00355420* func_00355420(Record00355420* record, s16 flag);


/**
 * @brief Release nested state and optionally free the record.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
Record003610F0* func_003610F0(Record003610F0* record, s16 flag);

/**
 * @brief Release nested state and optionally free the record.
 * @param record Record to release.
 * @param flag Free the storage when positive.
 * @return The original record pointer.
 */
Record00364810* func_00364810(Record00364810* record, s16 flag);

/**
 * @brief Reset the record fields and initialize its child state.
 * @param record Record to initialize.
 * @param arg1 First integer argument passed to the child initializer.
 * @param arg2 Second integer argument passed to the child initializer.
 * @param arg3 Pointer passed to the child initializer.
 * @param first First float argument; unused here.
 * @param second Second float argument; unused here.
 * @param third Float value passed to the child initializer.
 * @return One on completion.
 */
s32 func_0035D3E0(Record0035D3E0* record, s32 arg1, s32 arg2, void* arg3, float first, float second, float third);

/**
 * @brief Clear the list, release its storage, and optionally free the owner.
 * @param record List owner to release.
 * @param flag Free the owner when positive.
 * @return The original owner pointer.
 */
SkillList183C48* func_0035C700(SkillList183C48* record, s16 flag);

/**
 * @brief Clear the list, release its storage, and optionally free the owner.
 * @param record List owner to release.
 * @param flag Free the owner when positive.
 * @return The original owner pointer.
 */
SkillList183C38* func_0035C950(SkillList183C38* record, s16 flag);

/**
 * @brief Clear the list, release its storage, and optionally free the owner.
 * @param record List owner to release.
 * @param flag Free the owner when positive.
 * @return The original owner pointer.
 */
SkillPairList184258* func_00364AF0(SkillPairList184258* record, s16 flag);

/**
 * @brief Update six item fields and sum values other than -1.
 * @param owner Record containing the items and values.
 * @param mode Value stored in the first item's byte; zero clears the other item bytes.
 * @return Sum of the six values, with -1 treated as zero, or zero when mode is zero.
 */
s32 func_003534C0(StatusOwner003534C0* owner, s32 mode);

/**
 * @brief Advance the selected record through the six-row window.
 * @param object Six-row selection window.
 * @return Byte event code zero or four.
 */
s32 func_003539F0(Record003538F0* object);
/**
 * @brief Retreat the selected record through the six-row window.
 * @param object Six-row selection window.
 * @return Byte event code zero or four.
 */
s32 func_00353B40(Record003538F0* object);

/**
 * @brief Set the six-row window's list flags and selection activity.
 * @param object Six-row selection window.
 * @param flag Full window flag, whose low byte controls each display.
 * @param active Nonzero to activate the selection grid.
 */
void func_00353570(Record003538F0* object, u32 flag, s32 active);

/** @brief Refresh the comparison labels and values for the owner's selected entry. @param object Comparison window. */
void func_00348720(FieldClass15AE70* object);

/** @brief Set mode-window display and selection activity. @param object Mode window. @param flag Display flag word. @param active Grid activity value. */
void func_00351360(SkillModeSelection* object, u32 flag, s32 active);

/** @brief Cancel six-row selection and restore its associated window. @param object Six-row window. @return Zero while inactive, or two after cancellation. */
s32 func_00353EE0(Record003538F0* object);

/** @brief Save the mode-query choice, clear its pending state, and restore the associated window. @param object Mode-query window. @return Zero while inactive, or two after completing the transition. */
s32 func_00352920(Record00352B30* object);

/** @brief Save the mode-query choice and advance the selected record. @param object Mode-query window. @return Event code zero or four. */
s32 func_00352630(Record00352B30* object);

/** @brief Save the mode-query choice and retreat to the preceding record. @param object Mode-query window. @return Event code zero or four. */
s32 func_003527A0(Record00352B30* object);



/**
 * @brief Color the paired six-row lists and position the selected-row display.
 * @param record Record containing the lists, selection, and display receiver.
 */
void func_003538F0(Record003538F0* record);

/**
 * @brief Enable the selection grid, refresh its rows, and update the selected status values.
 * @param object Receiver with the row keys and three value tables.
 */
void func_00353670(Record003538F0* object);

/** @brief Move the six-row grid in direction one and refresh its selected status values. @param object Six-row selection window. */
void func_00353CA0(Record003538F0* object);

/** @brief Move the six-row grid in direction zero and refresh its selected status values. @param object Six-row selection window. */
void func_00353DC0(Record003538F0* object);

/**
 * @brief Show the selected slot's icon and copy its record links to the owning controller.
 * @param object Window with the slot icons and record selection.
 */
void func_00358310(StatusOwner003580D0* object);

/**
 * @brief Refresh the active secondary selection's description, row colors, and cursor.
 * @param object Secondary selection window.
 */
void func_00359340(SkillSecondarySelection* object);

/**
 * @brief Apply the selected mode and activate its associated selection window.
 * @param object Secondary selection window.
 * @return Zero while inactive, or one after applying the selection.
 */
s32 func_00359870(SkillSecondarySelection* object);

/** @brief Refresh the four-row window's record values. @param object Four-row selection window. */
void func_003559F0(SkillFourRowSelection* object);
/** @brief Rebuild the six-row status values. @param object Status-row window. @return One on success, or zero on failure. */
s32 func_00354190(Record003538F0* object);
/** @brief Rebuild the mode-query rows and description. @param object Mode-query window. */
void func_00352C00(Record00352B30* object);
/** @brief Rebuild the mode rows for a signed mode code. @param object Mode-selection window. @param mode Signed mode. @return One on success, or zero on failure. */
s32 func_00350890(SkillModeSelection* object, s16 mode);
/** @brief Create the second dual-grid display and row markers. @param object Dual-grid window. @return One after setup, or zero on failure. */
u8 func_0034B720(SkillDualSelection* object);

/** @brief Create both dual-grid panels and initialize their selections. @param object Dual-grid window. @param associated Full resource source word. @return One after setup, or zero on allocation or setup failure. */
s32 func_0034BA30(SkillDualSelection* object, u32 associated);

/** @brief Rebuild both paired selection grids. @param object Paired selection window. */
void func_0034B3F0(SkillDualSelection* object);
/** @brief Advance the selected record and refresh the linked windows. @param object Secondary selection window. @return Byte event code zero or four. */
s32 func_003594A0(SkillSecondarySelection* object);
/** @brief Retreat the selected record and refresh the linked windows. @param object Secondary selection window. @return Byte event code zero or four. */
s32 func_003595E0(SkillSecondarySelection* object);

/**
 * @brief Set the ready-state flag or open and attach a grid-choice window.
 * @param object Window supplying the display source and associated receiver.
 * @return Two after dispatch, or zero when the loader or window allocation is unavailable.
 */
s32 func_00359730(FieldClass15AE70* object);

/**
 * @brief Open a grid-choice window or mark the receiver when its source is busy.
 * @param object Source window for the choice.
 * @return Two after opening or marking the source, otherwise zero without a loader or allocation.
 */
s32 func_00362500(FieldClass15AE70* object);

/**
 * @brief Validate the selected entry and open its options window.
 * @param object Record window with the current selection and scroll position.
 * @return Zero while inactive, three for a rejected entry, or one after opening its options.
 */
s32 func_00362650(Record003619C0* object);
/** @brief Advance the selected record through the active controller. @param object Four-row selection window. @return Byte event code zero or four. */
s32 func_00355E80(SkillFourRowSelection* object);
/** @brief Retreat the selected record through the active controller. @param object Four-row selection window. @return Byte event code zero or four. */
s32 func_00355FD0(SkillFourRowSelection* object);

/**
 * @brief Set the four-row window's display flags and grid activity.
 * @param object Four-row selection window.
 * @param flag Display flag value.
 * @param active Nonzero to activate the grid.
 */
void func_003558B0(SkillFourRowSelection* object, u32 flag, s32 active);
/**
 * @brief Reset the four row colors and return to the associated window.
 * @param object Four-row selection window.
 * @return Two after switching windows, or zero while the grid is inactive.
 */
s32 func_00356130(SkillFourRowSelection* object);
/**
 * @brief Move the four-row grid in direction one and update its row colors and cursor.
 * @param object Four-row selection window.
 */
void func_00355CA0(SkillFourRowSelection* object);

/**
 * @brief Move the four-row grid in direction zero and update its row colors and cursor.
 * @param object Four-row selection window.
 */
void func_00355D90(SkillFourRowSelection* object);

/**
 * @brief Update four item values and status bytes.
 * @param owner Record containing the four item pointers.
 * @param first Value used by the first item and third-item selection.
 * @param second Value used by the second item.
 * @param third Value used by the third item.
 */
void func_003580D0(StatusOwner003580D0* owner, s32 first, s32 second, s32 third);

/**
 * @brief Mark the record, detach its nested registration, and enqueue it.
 * @param record Record to detach and enqueue.
 */
void func_003611B0(Record003611B0* record);

/**
 * @brief Reset the record's method table and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
RecordWithMethods* func_0035C050(RecordWithMethods* record, s16 flag);

/**
 * @brief Release the record's base state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
RecordWithMethods* func_0035C0A0(RecordWithMethods* record, s16 flag);

/**
 * @brief Release the derived record's base state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
Record00355490* func_00355490(Record00355490* record, s16 flag);

/**
 * @brief Release the nested record state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
Record00361060* func_00361060(Record00361060* record, s16 flag);

/**
 * @brief Release the nested record state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
Record0035D4A0* func_0035D4A0(Record0035D4A0* record, s16 flag);

/**
 * @brief Select the previous child node, wrapping a negative index to seven.
 * @param record Owner of the child selection; inactive children are unchanged.
 */
void func_0035E2A0(Record0035E2A0* record);

/**
 * @brief Select the next child node, wrapping indices of eight or greater to zero.
 * @param record Owner of the child selection; inactive children are unchanged.
 */
void func_0035E2F0(Record0035E2A0* record);

/**
 * @brief Remap child node indices zero, one, and two to three, five, and six.
 * @param record Owner of the child selection; inactive children are unchanged.
 */
void func_0035E340(Record0035E2A0* record);

/**
 * @brief Remap child indices three through seven to zero, one, one, two, and two.
 * @param record Owner of the child selection; inactive children are unchanged.
 */
void func_0035E3C0(Record0035E2A0* record);

/** @brief Cancel the options window and restore its associated window. @param object Options window. @return Two after restoring the prior window. */
s32 func_0035E470(SkillOptionsWindow* object);

/**
 * @brief Allocate and initialize the record's selection state.
 * @param record Owner of the selection state.
 * @return One when initialization succeeds, or zero on failure.
 */
s32 func_0035BE50(SkillQueueOwner* record);

/**
 * @brief Reset the packet buffer, append its initial register packet, and update the record.
 * @param record Record whose optional packet buffer is reset.
 */
void func_0035DDE0(Record0035DDE0* record);

void func_0035D540(Record0035DDE0* record);

/**
 * @brief Apply the selected mode and notify its receiver.
 * @param record Selection and mode storage.
 */
void func_003522C0(Record00352B30* record);

/**
 * @brief Apply an eligible selected mode and hide its status displays.
 * @param record Selection, mode and status display storage.
 * @return Zero when inactive or ineligible, three when unavailable, or one after applying the mode.
 */
s32 func_00352B30(Record00352B30* record);

#ifdef __cplusplus
}
#endif

#endif
