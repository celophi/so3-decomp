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

#ifdef __cplusplus
}
#endif

#endif
