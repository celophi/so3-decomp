#ifndef SO3_OVERLAYS_1067_00_TEXT_002BEA90_H
#define SO3_OVERLAYS_1067_00_TEXT_002BEA90_H

#include "types.h"

/** Partial receiver layouts defined in the owning source. */
typedef struct FieldTable14 FieldTable14;
typedef struct FieldGrid20 FieldGrid20;
typedef struct FieldWord1C FieldWord1C;
typedef struct FieldWord0C FieldWord0C;
typedef struct FieldWord10 FieldWord10;
typedef struct FieldWord14 FieldWord14;
typedef struct FieldWord28 FieldWord28;
typedef struct FieldInputState FieldInputState;
typedef struct FieldFlags1C FieldFlags1C;
typedef struct FieldBytePtr10 FieldBytePtr10;
typedef struct FieldBitFlags1C FieldBitFlags1C;
typedef struct FieldInputBlock FieldInputBlock;
typedef struct FieldEntry90 FieldEntry90;
typedef struct FieldCollection90 FieldCollection90;
typedef struct FieldCell40 FieldCell40;
typedef struct FieldGrid40 FieldGrid40;
typedef struct FieldSignedWord1C FieldSignedWord1C;
typedef struct FieldSignedWord0C FieldSignedWord0C;
typedef struct FieldSignedWord10 FieldSignedWord10;
typedef struct FieldPointer14 FieldPointer14;
typedef struct FieldState100 FieldState100;
typedef struct FieldFloat2C FieldFloat2C;
typedef struct FieldEntry50 FieldEntry50;
typedef struct FieldCollection50 FieldCollection50;
typedef struct FieldCollection FieldCollection;
typedef struct FieldThing FieldThing;
typedef struct FieldPair FieldPair;
typedef struct FieldMotion FieldMotion;
typedef struct FieldList FieldList;
typedef struct FieldState28 FieldState28;
typedef struct FieldSelector FieldSelector;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear bit 0 of the flag byte at offset 0x1C.
 * @param self Receiver to update.
 */
void func_002BED50(FieldBitFlags1C* self);

/**
 * @brief Store input range and whether its first byte is 1.
 * @param self Receiver to update.
 * @param data Input byte stream.
 * @param count Input count.
 */
void func_002BF3F0(FieldInputBlock* self, const u8* data, s32 count);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF430(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF440(void* object);

/**
 * @brief Return the fixed float value 100.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002BF450(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF460(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF470(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF480(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF490(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF4C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4E0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF4F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF500(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF510(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF520(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF530(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF540(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF550(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF560(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF570(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF580(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF590(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002BF5A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF5B0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF5C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF5D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF5E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002BF5F0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF600(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002BF610(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002BF620(void* object);

/**
 * @brief Address an indexed 0x90-byte record.
 * @param self Record collection.
 * @param index Record index.
 * @return Indexed record.
 */
FieldEntry90* func_002BF690(FieldCollection90* self, s32 index);

/**
 * @brief Address an indexed 0x40-byte grid cell.
 * @param self Cell grid.
 * @param row Row index.
 * @param column Column index.
 * @return Indexed cell.
 */
FieldCell40* func_002BF6B0(FieldGrid40* self, s32 row, s32 column);

/**
 * @brief Read the signed word at offset 0x1C.
 * @param self Receiver.
 * @return Stored word.
 */
s32 func_002BF6D0(const FieldSignedWord1C* self);

/**
 * @brief Read the signed word at offset 0x0C.
 * @param self Receiver.
 * @return Stored word.
 */
s32 func_002BF6E0(const FieldSignedWord0C* self);

/**
 * @brief Read the signed word at offset 0x10.
 * @param self Receiver.
 * @return Stored word.
 */
s32 func_002BF6F0(const FieldSignedWord10* self);

/**
 * @brief Return the fixed value 0x20.
 * @param self Receiver of the call.
 * @return Fixed value.
 */
s32 func_002BF700(void* self);

/**
 * @brief Test whether the pointer at offset 0x14 is present.
 * @param self Receiver.
 * @return Whether the pointer is non-null.
 */
bool func_002BF710(const FieldPointer14* self);

/**
 * @brief Return the fixed float value 1.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002BFE60(void* object);

/**
 * @brief Clear an inactive state flag or activate once.
 * @param state Receiver to update.
 */
void func_002C0390(FieldState100* state);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C0550(void* object);

/**
 * @brief Clear the word at offset 0x28.
 * @param self Receiver to update.
 */
void func_002C0560(FieldWord28* self);

/**
 * @brief Read the float at offset 0x2C.
 * @param self Receiver.
 * @return Stored float.
 */
float func_002C0570(const FieldFloat2C* self);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C0580(void* object);

/**
 * @brief Address an indexed 0x40-byte grid cell.
 * @param self Cell grid.
 * @param row Row index.
 * @param column Column index.
 * @return Indexed cell.
 */
FieldCell40* func_002C0590(FieldGrid40* self, s32 row, s32 column);

/**
 * @brief Address an indexed 0x50-byte record.
 * @param self Record collection.
 * @param index Record index.
 * @return Indexed record.
 */
FieldEntry50* func_002C05B0(FieldCollection50* self, s32 index);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1370(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1580(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1590(void* object);

/**
 * @brief Return the fixed float value 100.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C15A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15B0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15E0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C15F0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1610(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1620(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1630(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1640(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1650(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1660(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1670(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1680(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1690(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C16A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C16B0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C16C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C16D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C16E0(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C16F0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1700(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1710(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1720(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1730(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1740(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1750(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C1760(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C1770(void* object);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002C17E0(const FieldWord1C* object);

/**
 * @brief Read the word at offset 0x0C.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002C17F0(const FieldWord0C* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002C1800(const FieldWord10* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C1810(void* object);

/**
 * @brief Test the word at offset 0x14.
 * @param object Receiver to test.
 * @return True when the word is nonzero.
 */
bool func_002C1820(const FieldWord14* object);

/**
 * @brief Return the fixed float value 1.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C1F70(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2000(void* object);

/**
 * @brief Clear the word at offset 0x28.
 * @param object Receiver to update.
 */
void func_002C2010(FieldWord28* object);

/**
 * @brief Return the fixed float value 2500.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C2020(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2040(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2240(void* object);

/**
 * @brief Store an input pointer and word, then update the byte mode from its first byte.
 * @param state Receiver to update.
 * @param input Input byte sequence; at least one byte is required.
 * @param unk30 Word to store at offset 0x30.
 */
void func_002C29D0(FieldInputState* state, u8* input, u32 unk30);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2A10(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A20(void* object);

/**
 * @brief Return the fixed float value 100.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C2A30(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A40(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A50(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A60(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A70(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A80(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2A90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2AA0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2AB0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2AC0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2AD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2AE0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2AF0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B00(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B10(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B20(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2B40(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2B60(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B70(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C2B80(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2B90(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2BA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2BB0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2BC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C2BD0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2BE0(void* object);

/**
 * @brief Return the fixed float value 0.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C2BF0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C2C00(void* object);

/**
 * @brief Find a 160-byte indexed entry.
 * @param object Collection owner.
 * @param index Entry index.
 * @return The entry address.
 */
char* func_002C2C70(FieldCollection* object, s32 index);

/**
 * @brief Find a 64-byte grid cell.
 * @param object Collection owner.
 * @param row Row index.
 * @param column Column index.
 * @return The cell address.
 */
char* func_002C2C90(FieldCollection* object, s32 row, s32 column);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Collection owner.
 * @return The stored word.
 */
s32 func_002C2CB0(FieldCollection* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Collection owner.
 * @return The stored word.
 */
s32 func_002C2CC0(FieldCollection* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Collection owner.
 * @return The stored word.
 */
s32 func_002C2CD0(FieldCollection* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver of the call.
 * @return 32.
 */
int func_002C2CE0(void* object);

/**
 * @brief Test whether the pointer at offset 0x14 is present.
 * @param object Collection owner.
 * @return True when the pointer is nonnull.
 */
bool func_002C2CF0(FieldCollection* object);

/**
 * @brief Return the fixed float value 1.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C3AC0(void* object);

/**
 * @brief Select the pair and update its comparison flag.
 * @param object Pair to update.
 * @param first First compared object.
 * @param second Second compared object.
 */
void func_002C4FC0(FieldPair* object, FieldThing* first, FieldThing* second);

/**
 * @brief Set the motion selector, rate and flag.
 * @param object Motion state to update.
 * @param value Byte value to store.
 * @param index Selector, or -1 to reuse the current selector.
 * @param rate New rate.
 */
void func_002C5640(FieldMotion* object, u8 value, s16 index, float rate);

/**
 * @brief Start a motion when its flags permit it.
 * @param object Motion state to update.
 * @param value New word value.
 * @param mode New mode bit.
 * @param rate New rate.
 */
void func_002C5A10(FieldMotion* object, s32 value, s32 mode, float rate);

/**
 * @brief Mark matching linked-list nodes and clear the owner state.
 * @param object List owner to update.
 */
void func_002C7780(FieldList* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C9660(void* object);

/**
 * @brief Clear the word at offset 0x28.
 * @param object State to update.
 */
void func_002C9670(FieldState28* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002C9680(void* object);

/**
 * @brief Return the fixed float value 2500.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002C9690(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver of the call.
 * @return The fixed value.
 */
int func_002C96B0(void* object);

/**
 * @brief Return the fixed value four.
 * @param object Receiver of the call.
 * @return Four.
 */
int func_002C9A20(void* object);

/**
 * @brief Store selection pointers and update the mode byte.
 * @param object Selector to update.
 * @param value Byte stream to select.
 * @param context Associated context.
 */
void func_002CA150(FieldSelector* object, const u8* value, void* context);

/**
 * @brief Return a null pointer.
 * @param object Receiver of the call.
 * @return Null.
 */
void* func_002CA190(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1A0(void* object);

/**
 * @brief Return the fixed float value 100.0f.
 * @param object Receiver of the call.
 * @return The fixed float value.
 */
float func_002CA1B0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1D0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1E0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA1F0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA200(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA210(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA220(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA230(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA240(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA250(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA260(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA270(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA280(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA290(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA2A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA2B0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA2C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA2D0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA2E0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA2F0(void* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver of the call.
 * @return Zero.
 */
float func_002CA300(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA310(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA320(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA330(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA340(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002CA350(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA360(void* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver of the call.
 * @return Zero.
 */
float func_002CA370(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CA380(void* object);

/**
 * @brief Find the indexed 64-byte entry.
 * @param object Table owner.
 * @param index Entry index.
 * @return The entry address.
 */
void* func_002CA3F0(FieldTable14* object, u32 index);

/**
 * @brief Find a 64-byte grid entry.
 * @param object Grid owner.
 * @param column Column index.
 * @param row Row index.
 * @return The entry address.
 */
void* func_002CA400(FieldGrid20* object, u32 column, u32 row);

/**
 * @brief Read the word at offset 0x1C.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002CA420(const FieldWord1C* object);

/**
 * @brief Read the word at offset 0xC.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002CA430(const FieldWord0C* object);

/**
 * @brief Read the word at offset 0x10.
 * @param object Receiver to read.
 * @return The stored word.
 */
u32 func_002CA440(const FieldWord10* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
int func_002CA450(void* object);

/**
 * @brief Test the word at offset 0x14.
 * @param object Receiver to test.
 * @return True when the word is nonzero.
 */
bool func_002CA460(const FieldWord14* object);

/**
 * @brief Return the float value one.
 * @param object Receiver of the call.
 * @return One as a float.
 */
float func_002CABA0(void* object);

/**
 * @brief Set flag bits in the word at offset 0x1C.
 * @param object Receiver to update.
 * @param flags Bits to set.
 */
void func_002CB5B0(FieldFlags1C* object, u32 flags);

/**
 * @brief Return the fixed value nine.
 * @param object Receiver of the call.
 * @return Nine.
 */
int func_002CBAA0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD780(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD790(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD7A0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002CD7B0(void* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
int func_002CD9E0(void* object);

/**
 * @brief Store a byte in the selected object when present.
 * @param object Receiver containing the selected object.
 * @param value Byte to store.
 */
void func_002CE510(FieldBytePtr10* object, u8 value);

#ifdef __cplusplus
}
#endif

#endif
