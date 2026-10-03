#ifndef SO3_OVERLAYS_CITEM_TEXT_H
#define SO3_OVERLAYS_CITEM_TEXT_H

#include "types.h"

typedef struct ItemRecord ItemRecord;
typedef struct StatusRecord StatusRecord;
typedef struct DisplayRecord DisplayRecord;
typedef struct Record00349190 Record00349190;
typedef struct Record00349C50 Record00349C50;
typedef struct Record0034C800 Record0034C800;
typedef struct Record00349BF0 Record00349BF0;
typedef struct Record0034C7A0 Record0034C7A0;
typedef struct Record0034C6A0 Record0034C6A0;
typedef struct Record00350BD0 Record00350BD0;
typedef struct Record00353EF0 Record00353EF0;
typedef struct Record00350C20 Record00350C20;
typedef struct Record00350FC0 Record00350FC0;
typedef struct Record003540E0 Record003540E0;
typedef struct Record003542F0 Record003542F0;
typedef struct Record00354740 Record00354740;
typedef struct Record0034E8B0 Record0034E8B0;
typedef struct TransformRecord TransformRecord;
typedef struct ScreenOwner ScreenOwner;
typedef struct Record00353A50 Record00353A50;
typedef struct Record00352960 Record00352960;
typedef struct Record00352EE0 Record00352EE0;
typedef struct Record003531B0 Record003531B0;
typedef struct ItemListNode ItemListNode;
typedef struct ItemListOwner ItemListOwner;
typedef struct AngleOwner AngleOwner;
typedef struct ControlOwner ControlOwner;

/** Four float components stored on a 16-byte boundary. */
typedef struct Vector4
{
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) Vector4;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Compare the low ten-bit definition keys of two list entries.
 * @param left First list node containing an item record.
 * @param right Second list node containing an item record.
 * @return Signed difference between their definition keys.
 */
s32 func_00351E40(const ItemListNode* left, const ItemListNode* right);

/**
 * @brief Initialize a record and pass its setup arguments to the shared initializer.
 * @param record Record to initialize.
 * @param arg1 First integer setup argument.
 * @param arg2 Second integer setup argument.
 * @param arg3 Pointer setup argument.
 * @param first First float input; unused by this routine.
 * @param second Second float input; unused by this routine.
 * @param third Float passed to the shared initializer.
 * @return Always 1.
 */
s32 func_00349190(Record00349190* record, s32 arg1, s32 arg2, void* arg3, float first, float second, float third);

/**
 * @brief Initialize a record and run cleanup when requested.
 * @param record Record to initialize.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record00349BF0* func_00349BF0(Record00349BF0* record, s16 flag);

/**
 * @brief Initialize a record and run cleanup when requested.
 * @param record Record to initialize.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record0034C7A0* func_0034C7A0(Record0034C7A0* record, s16 flag);

/**
 * @brief Initialize a record and its embedded part.
 * @param record Record to initialize.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record0034C6A0* func_0034C6A0(Record0034C6A0* record, s16 flag);

/**
 * @brief Initialize a record and run cleanup when requested.
 * @param record Record to initialize.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record00353EF0* func_00353EF0(Record00353EF0* record, s16 flag);

/**
 * @brief Clean up a record and its attached object when present.
 * @param record Record to clean up.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record00350C20* func_00350C20(Record00350C20* record, s16 flag);

/**
 * @brief Set positions and flags for three rows of fourteen slots.
 * @param owner Record holding the slot arrays.
 * @param start Starting vertical position before the first offset.
 */
void func_00350FC0(Record00350FC0* owner, float start);

/**
 * @brief Update slot flags and the attached control's float value.
 * @param record Record holding the slots and controls.
 * @param flag Flag stored in paired slots.
 * @param control_flag Flag stored in the optional controls.
 */
void func_0034E8B0(Record0034E8B0* record, u8 flag, s32 control_flag);

/**
 * @brief Free list nodes and optionally the owner.
 * @param record List owner to clean up.
 * @param flag Cleanup flag.
 * @return The list owner.
 */
Record003540E0* func_003540E0(Record003540E0* record, s16 flag);

/**
 * @brief Free list nodes and optionally the owner.
 * @param record List owner to clean up.
 * @param flag Cleanup flag.
 * @return The list owner.
 */
Record003542F0* func_003542F0(Record003542F0* record, s16 flag);

/**
 * @brief Free list nodes and optionally the owner.
 * @param record List owner to clean up.
 * @param flag Cleanup flag.
 * @return The list owner.
 */
Record00354740* func_00354740(Record00354740* record, s16 flag);

/**
 * @brief Set the attached control's flag and one of two float values.
 * @param owner Record holding the control.
 * @param ignored Unused second argument.
 * @param flag Value to store and choice of float value.
 */
void func_00350F70(ControlOwner* owner, s32 ignored, s32 flag);

/**
 * @brief Increase the attached angle and clamp it at its limit.
 * @param owner Record holding the angle.
 */
void func_0034F340(AngleOwner* owner);

/**
 * @brief Decrease the attached angle and clamp it at zero.
 * @param owner Record holding the angle.
 */
void func_0034F2E0(AngleOwner* owner);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_00354370(ItemListOwner* owner, void* value);

/**
 * @brief Follow links from the node after the head.
 * @param owner List owner to search.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends first.
 */
ItemListNode* func_00354480(ItemListOwner* owner, s32 index);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_003544C0(ItemListOwner* owner, void* value);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_00354550(ItemListOwner* owner, void* value);

/**
 * @brief Follow links from the node after the head.
 * @param owner List owner to search.
 * @param index Number of links to follow.
 * @return Reached node, or null if the chain ends first.
 */
ItemListNode* func_003545E0(ItemListOwner* owner, s32 index);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_00354620(ItemListOwner* owner, void* value);

/**
 * @brief Append a payload to the list when node allocation succeeds.
 * @param owner List with a sentinel head and element count.
 * @param value Payload stored in the new node.
 */
void func_003546B0(ItemListOwner* owner, void* value);

/**
 * @brief Initialize a display record and run cleanup when requested.
 * @param display Display record to initialize.
 * @param flag Cleanup flag.
 * @return The display record.
 */
DisplayRecord* func_00353E40(DisplayRecord* display, s16 flag);

/**
 * @brief Initialize a record and run cleanup when requested.
 * @param record Record to initialize.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record00352960* func_00352960(Record00352960* record, s16 flag);

/**
 * @brief Initialize a record and run cleanup when requested.
 * @param record Record to initialize.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record00352EE0* func_00352EE0(Record00352EE0* record, s16 flag);

/**
 * @brief Initialize a record and run cleanup when requested.
 * @param record Record to initialize.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record003531B0* func_003531B0(Record003531B0* record, s16 flag);

/**
 * @brief Initialize an item record and run cleanup when requested.
 * @param item Item record to initialize.
 * @param flag Cleanup flag.
 * @return The item record.
 */
ItemRecord* func_00348400(ItemRecord* item, s16 flag);

/**
 * @brief Initialize a screen owner and run cleanup when requested.
 * @param owner Screen owner to initialize.
 * @param flag Cleanup flag.
 * @return The screen owner.
 */
ScreenOwner* func_00351F50(ScreenOwner* owner, s16 flag);

/**
 * @brief Initialize a record and run cleanup when requested.
 * @param record Record to initialize.
 * @param flag Cleanup flag.
 * @return The record.
 */
Record00353A50* func_00353A50(Record00353A50* record, s16 flag);

/**
 * @brief Copy three components and a unit fourth component to the field at 0x30.
 * @param record Transform record to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_00353C50(TransformRecord* record, float x, float y, float z);

/**
 * @brief Copy a four-component value to the field at 0x20.
 * @param record Transform record to update.
 * @param value Components to copy.
 */
void func_00353B30(TransformRecord* record, const Vector4* value);

/**
 * @brief Copy a four-component value to the field at 0x20.
 * @param record Transform record to update.
 * @param value Components to copy.
 */
void func_00353B50(TransformRecord* record, const Vector4* value);

/**
 * @brief Copy a four-component value to the field at 0x30.
 * @param record Transform record to update.
 * @param value Components to copy.
 */
void func_00353BB0(TransformRecord* record, const Vector4* value);

/**
 * @brief Copy a four-component value to the field at 0x30.
 * @param record Transform record to update.
 * @param value Components to copy.
 */
void func_00353BD0(TransformRecord* record, const Vector4* value);

/**
 * @brief Copy a four-component value to the field at 0x40.
 * @param record Transform record to update.
 * @param value Components to copy.
 */
void func_00353C90(TransformRecord* record, const Vector4* value);

/**
 * @brief Copy a four-component value to the field at 0x40.
 * @param record Transform record to update.
 * @param value Components to copy.
 */
void func_00353CB0(TransformRecord* record, const Vector4* value);

/**
 * @brief Store three components at 0x20 with a unit fourth component.
 * @param record Transform record to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_00353B70(TransformRecord* record, float x, float y, float z);

/**
 * @brief Store four components at 0x30.
 * @param record Transform record to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void func_00353B90(TransformRecord* record, float x, float y, float z, float w);

/**
 * @brief Store three components at 0x40.
 * @param record Transform record to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_00353CD0(TransformRecord* record, float x, float y, float z);

/**
 * @brief Check whether a float is negative.
 * @param value Value to check.
 * @return One if negative, otherwise zero.
 */
s32 func_00353D00(float value);

/**
 * @brief Set two fields of the attached screen record when present.
 * @param owner Record holding the screen pointer.
 */
void func_00351FB0(ScreenOwner* owner);

/**
 * @brief Read the word field at 0x38.
 * @param record Record to read.
 * @return Current field value.
 */
u32 func_00349C50(Record00349C50* record);

/**
 * @brief Read the word field at 0x40.
 * @param record Record to read.
 * @return Current field value.
 */
u32 func_0034C800(Record0034C800* record);

/**
 * @brief Store the byte field at 0x12C.
 * @param record Record to update.
 * @param value Value to store.
 */
void func_00350BD0(Record00350BD0* record, u8 value);

/**
 * @brief Return the external table at 0x50CD30.
 * @return Pointer to the table.
 */
u8* func_00353D20(void);

/**
 * @brief Copy the byte field at 0xA8 to the field at 0x60.
 * @param display Display record to update.
 */
void func_00353E30(DisplayRecord* display);

/**
 * @brief Store the word field at 0x24.
 * @param state Status record to update.
 * @param value Value to store.
 */
void func_00353F70(StatusRecord* state, u32 value);

/**
 * @brief Read the word field at 0x24.
 * @param state Status record to read.
 * @return Current field value.
 */
u32 func_00353F80(StatusRecord* state);

/**
 * @brief Store the signed byte field at 0x28.
 * @param state Status record to update.
 * @param value Value to store.
 */
void func_00353F90(StatusRecord* state, s8 value);

/**
 * @brief Read the signed byte field at 0x28.
 * @param state Status record to read.
 * @return Current field value.
 */
s8 func_00353FA0(StatusRecord* state);

/**
 * @brief Read the low bit of the byte field at 0x3C.
 * @param state Status record to read.
 * @return Low bit of the field.
 */
u32 func_00354050(StatusRecord* state);

/**
 * @brief Store the byte field at 0xC.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_00348460(ItemRecord* item, u8 value);

/**
 * @brief Read the byte field at 0xC.
 * @param item Item record to read.
 * @return Current field value.
 */
u8 func_00348470(ItemRecord* item);

/**
 * @brief Store the byte field at 0x8.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_00348480(ItemRecord* item, u8 value);

/**
 * @brief Read the byte field at 0x8.
 * @param item Item record to read.
 * @return Current field value.
 */
u8 func_00348490(ItemRecord* item);

/**
 * @brief Store the halfword field at 0xA.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_003484A0(ItemRecord* item, u16 value);

/**
 * @brief Read the halfword field at 0xA.
 * @param item Item record to read.
 * @return Current field value.
 */
u16 func_003484B0(ItemRecord* item);

/**
 * @brief Store the word field at 0x98.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_003484C0(ItemRecord* item, u32 value);

/**
 * @brief Read the word field at 0x98.
 * @param item Item record to read.
 * @return Current field value.
 */
u32 func_003484D0(ItemRecord* item);

/**
 * @brief Store the word field at 0x9C.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_003484E0(ItemRecord* item, u32 value);

/**
 * @brief Read the word field at 0x9C.
 * @param item Item record to read.
 * @return Current field value.
 */
u32 func_003484F0(ItemRecord* item);

/**
 * @brief Store the word field at 0x4.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_00348500(ItemRecord* item, u32 value);

/**
 * @brief Read the word field at 0x4.
 * @param item Item record to read.
 * @return Current field value.
 */
u32 func_00348510(ItemRecord* item);

/**
 * @brief Read the word field at 0x10.
 * @param item Item record to read.
 * @return Current field value.
 */
u32 func_00348520(ItemRecord* item);

/**
 * @brief Read the byte field at 0xD.
 * @param item Item record to read.
 * @return Current field value.
 */
u8 func_00348710(ItemRecord* item);

/**
 * @brief Store the byte field at 0xD.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_00348720(ItemRecord* item, u8 value);

/**
 * @brief Read the word field at 0x20.
 * @param item Item record to read.
 * @return Current field value.
 */
u32 func_003487B0(ItemRecord* item);

/**
 * @brief Store the word field at 0x20.
 * @param item Item record to update.
 * @param value Value to store.
 */
void func_003489F0(ItemRecord* item, u32 value);

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
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348610(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348620(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348630(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348640(void* object);

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
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348700(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348730(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353A30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353A40(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00353B00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353B10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353B20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353CF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353D40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353E10(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_00353E20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353EA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353EB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353EC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353ED0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353EE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353FB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00353FC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353FD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353FE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00353FF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00354000(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00354010(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00354020(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00354030(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00354040(void* object);

#ifdef __cplusplus
}
#endif

#endif
