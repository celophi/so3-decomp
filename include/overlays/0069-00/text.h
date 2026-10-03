#ifndef SO3_OVERLAYS_0069_00_TEXT_H
#define SO3_OVERLAYS_0069_00_TEXT_H

#include "types.h"

/** Linked nodes used by the indexed list helpers. */
typedef struct SkillListNode
{
    void* value;
    struct SkillListNode* next;
} SkillListNode;

/** List storage begins with an anchor node. */
typedef struct SkillList
{
    SkillListNode* head;
    u32 count;
} SkillList;

typedef struct RecordWithMethods RecordWithMethods;
typedef struct ListOwnerWithMethods ListOwnerWithMethods;
typedef struct StatusOwner003534C0 StatusOwner003534C0;
typedef struct Record003538F0 Record003538F0;
typedef struct Record00352B30 Record00352B30;
typedef struct Record0035A560 Record0035A560;
typedef struct StatusOwner003580D0 StatusOwner003580D0;
typedef struct Record003581B0 Record003581B0;
typedef struct Record0035E2A0 Record0035E2A0;
typedef struct Record0035BE50 Record0035BE50;
typedef struct Record0035DDE0 Record0035DDE0;
typedef struct Record0035DE40 Record0035DE40;
typedef struct Record0035D4A0 Record0035D4A0;
typedef struct Record0035D3E0 Record0035D3E0;
typedef struct Record00349DB0 Record00349DB0;
typedef struct Record0034BC40 Record0034BC40;
typedef struct Record00351790 Record00351790;
typedef struct Record00355420 Record00355420;
typedef struct Record00355490 Record00355490;
typedef struct Record00355500 Record00355500;
typedef struct Record003610F0 Record003610F0;
typedef struct Record00361060 Record00361060;
typedef struct Record003611B0 Record003611B0;
typedef struct Record003620F0 Record003620F0;
typedef struct Record00363740 Record00363740;
typedef struct Record00364810 Record00364810;
typedef struct Record00364720 Record00364720;
typedef struct Record0034C110 Record0034C110;
typedef struct Record0034C1F0 Record0034C1F0;
typedef struct Record0034B190 Record0034B190;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Write the 8-bit field at offset 0xC.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348400(u8* object, u8 value);

/**
 * @brief Read the 8-bit field at offset 0xC.
 * @param object Receiver storage.
 * @return Field value.
 */
u8 func_00348410(u8* object);

/**
 * @brief Write the 8-bit field at offset 0x8.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348420(u8* object, u8 value);

/**
 * @brief Read the 8-bit field at offset 0x8.
 * @param object Receiver storage.
 * @return Field value.
 */
u8 func_00348430(u8* object);

/**
 * @brief Write the 16-bit field at offset 0xA.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348440(u8* object, u16 value);

/**
 * @brief Read the 16-bit field at offset 0xA.
 * @param object Receiver storage.
 * @return Field value.
 */
u16 func_00348450(u8* object);

/**
 * @brief Write the 32-bit field at offset 0x98.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348460(u8* object, u32 value);

/**
 * @brief Read the 32-bit field at offset 0x98.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_00348470(u8* object);

/**
 * @brief Write the 32-bit field at offset 0x9C.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348480(u8* object, u32 value);

/**
 * @brief Read the 32-bit field at offset 0x9C.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_00348490(u8* object);

/**
 * @brief Write the 32-bit field at offset 0x4.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_003484A0(u8* object, u32 value);

/**
 * @brief Read the 32-bit field at offset 0x4.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_003484B0(u8* object);

/**
 * @brief Read the 32-bit field at offset 0x10.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_003484C0(u8* object);

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
u8 func_003486F0(u8* object);

/**
 * @brief Write the 8-bit field at offset 0xD.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348700(u8* object, u8 value);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348710(void* object);

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
 * @brief Update list item display values for the selected index.
 * @param object Receiver storage containing the list.
 * @param selected Selected list index.
 */
void func_0035CCE0(void* object, s16 selected);

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
void func_0035C130(u8* object, const unsigned __int128* value);

/**
 * @brief Store a 128-bit value at offset 0x20 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C150(u8* object, const unsigned __int128* value);

/**
 * @brief Store 3 float values at offset 0x20 and set the byte at 0x50. Set the fourth float to 1.0f.
 * @param object Receiver storage.
 * @param x Float value to store.
 * @param y Float value to store.
 * @param z Float value to store.
 */
void func_0035C170(u8* object, float x, float y, float z);

/**
 * @brief Store 4 float values at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param x Float value to store.
 * @param y Float value to store.
 * @param z Float value to store.
 * @param w Float value to store.
 */
void func_0035C190(u8* object, float x, float y, float z, float w);

/**
 * @brief Store a 128-bit value at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C1B0(u8* object, const unsigned __int128* value);

/**
 * @brief Store a 128-bit value at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C1D0(u8* object, const unsigned __int128* value);

/**
 * @brief Copy three floats and a unit fourth component into the receiver at offset 0x30.
 * @param object Receiver storage.
 * @param x First float component.
 * @param y Second float component.
 * @param z Third float component.
 */
void func_0035C250(u8* object, float x, float y, float z);

/**
 * @brief Store a 128-bit value at offset 0x40 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C290(u8* object, const unsigned __int128* value);

/**
 * @brief Store a 128-bit value at offset 0x40 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C2B0(u8* object, const unsigned __int128* value);

/**
 * @brief Store 3 float values at offset 0x40 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param x Float value to store.
 * @param y Float value to store.
 * @param z Float value to store.
 */
void func_0035C2D0(u8* object, float x, float y, float z);

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
s32 func_0035C300(float value);

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
void func_0035C360(u8* object, u8 value);

/**
 * @brief Read the signed 8-bit field at offset 0x28.
 * @param object Receiver storage.
 * @return Field value.
 */
s8 func_0035C370(u8* object);

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

/**
 * @brief Configure the second grid and register its newly allocated display object.
 * @param record Receiver containing the second grid and display owner.
 * @return One after setup, otherwise zero without the second grid.
 */
s32 func_0034B190(Record0034B190* record);

/**
 * @brief Configure the first grid and register its newly allocated display object.
 * @param record Receiver containing the first grid and display owner.
 * @return One after setup, otherwise zero without the first grid.
 */
s32 func_0034B2C0(Record0034B190* record);

/**
 * @brief Configure the selection grid position and register its display state.
 * @param record Receiver with the display owner and selection grid.
 * @param row_count Number of grid rows; zero leaves the grid unchanged.
 * @return One for zero rows or completed setup, otherwise zero without a display owner.
 */
s32 func_0034E260(Record0034C1F0* record, s16 row_count);

/**
 * @brief Initialize the receiver metadata and return its address.
 * @param object Receiver storage.
 * @return Address of the receiver.
 */
u8* func_0035D300(u8* object);

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
ListOwnerWithMethods* func_00364960(ListOwnerWithMethods* record, s16 flag);

/**
 * @brief Release linked nodes after the anchor and clear the list when nonempty.
 * @param record List owner whose nodes are released.
 */
void func_00364A70(ListOwnerWithMethods* record);

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
RecordWithMethods* func_00349840(RecordWithMethods* record, s16 flag);

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
RecordWithMethods* func_003591A0(RecordWithMethods* record, s16 flag);

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
RecordWithMethods* func_0035D2A0(RecordWithMethods* record, s16 flag);

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
Record00351790* func_00351790(Record00351790* record, s16 flag);

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
Record00355500* func_00355500(Record00355500* record, s16 flag);

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
ListOwnerWithMethods* func_0035C700(ListOwnerWithMethods* record, s16 flag);

/**
 * @brief Clear the list, release its storage, and optionally free the owner.
 * @param record List owner to release.
 * @param flag Free the owner when positive.
 * @return The original owner pointer.
 */
ListOwnerWithMethods* func_0035C950(ListOwnerWithMethods* record, s16 flag);

/**
 * @brief Clear the list, release its storage, and optionally free the owner.
 * @param record List owner to release.
 * @param flag Free the owner when positive.
 * @return The original owner pointer.
 */
ListOwnerWithMethods* func_00364AF0(ListOwnerWithMethods* record, s16 flag);

/**
 * @brief Update six item fields and sum values other than -1.
 * @param owner Record containing the items and values.
 * @param mode Value stored in the first item's byte; zero clears the other item bytes.
 * @return Sum of the six values, with -1 treated as zero, or zero when mode is zero.
 */
s32 func_003534C0(StatusOwner003534C0* owner, s32 mode);

/**
 * @brief Color the paired six-row lists and position the selected-row display.
 * @param record Record containing the lists, selection, and display receiver.
 */
void func_003538F0(Record003538F0* record);

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

/**
 * @brief Allocate and initialize the record's selection state.
 * @param record Owner of the selection state.
 * @return One when initialization succeeds, or zero on failure.
 */
s32 func_0035BE50(Record0035BE50* record);

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
