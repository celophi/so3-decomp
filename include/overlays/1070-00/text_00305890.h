#ifndef SO3_OVERLAYS_1070_00_TEXT_00305890_H
#define SO3_OVERLAYS_1070_00_TEXT_00305890_H

#include "overlays/1070-00/text_001F2BB0.h"

/** Partial receiver with two indexed byte/halfword slots and signed counters. */
typedef struct FieldTwoSlotState
{
    u8 unk00[0x5C];
    u8 unk5c[2];
    s16 unk5e[2];
    u8 unk62;
    u8 unk63;
    s16 unk64;
    u8 unk66;
    u8 unk67[0x15];
    s32 unk7c;
    s32 unk80;
} FieldTwoSlotState;

/** Partial receiver with an embedded list, its count, and adjacent state values. */
typedef struct FieldHalfwordByteState105A
{
    u8 unk00[0x104C];
    FieldIndexedList unk104c;
    s32 unk1050;
    u8 unk1054[6];
    s16 unk105a;
    u8 unk105c[2];
    s16 unk105e;
    u8 unk1060;
} FieldHalfwordByteState105A;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find a node by advancing from the first list element.
 * @param list List with a non-null head node.
 * @param index Number of links to advance; nonpositive values select the first node.
 * @return The selected node, or null if the chain ends first.
 */
FieldIndexedListNode* func_003100B0(const FieldIndexedList* list, s32 index);

/**
 * @brief Read the state byte at offset 0x66.
 * @param object Receiver to inspect.
 * @return The stored state byte.
 */
u8 func_0030A190(const FieldTwoSlotState* object);

/**
 * @brief Read one of the two signed halfword slots.
 * @param object Receiver to inspect.
 * @param index Slot index, 0 or 1.
 * @return The selected signed halfword.
 */
s16 func_0030A1A0(const FieldTwoSlotState* object, s32 index);

/**
 * @brief Select and reset one slot, then clear the counters and state byte.
 * @param object Receiver to reset.
 * @param index Slot index, 0 or 1.
 */
void func_0030A1B0(FieldTwoSlotState* object, s16 index);

/**
 * @brief Set the signed halfword at offset 0x105E and its adjacent state byte.
 * @param object Receiver to update.
 * @param value Signed halfword to store.
 * @param state State byte to store.
 */
void func_0030BF10(FieldHalfwordByteState105A* object, s16 value, u8 state);

/**
 * @brief Store the signed halfword, preserving the preliminary write for values above 50.
 * @param object Receiver to update.
 * @param value Signed halfword ultimately stored at offset 0x105A.
 */
void func_0030C130(FieldHalfwordByteState105A* object, s16 value);

/**
 * @brief Read a stored list value after checking the signed index against the count.
 * @param object Receiver containing the list and count.
 * @param index Signed index to look up; negative values and values above the count are rejected.
 * @return The selected node value, or null if the index is rejected.
 */
void* func_0030BE90(const FieldHalfwordByteState105A* object, s16 index);

/**
 * @brief Append a value to the embedded indexed list.
 * @param object Receiver containing the list.
 * @param value Value pointer to append.
 */
void func_0030BEF0(FieldHalfwordByteState105A* object, void* value);

/**
 * @brief Append a value in a newly allocated node and increment the stored list count.
 * @param list Indexed list prefix with its count stored immediately after the head pointer.
 * @param value Value pointer to append.
 */
void func_0030FED0(FieldIndexedList* list, void* value);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00305C20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00305C30(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_0030A180(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0030F200(void* object);

/**
 * @brief Return the fixed value 9.
 * @param object Receiver or first argument; unused.
 * @return Always 9.
 */
s32 func_003106C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003108C0(void* object);

#ifdef __cplusplus
}
#endif

#endif
