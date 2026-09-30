#ifndef SO3_OVERLAYS_1070_00_TEXT_001F2BB0_H
#define SO3_OVERLAYS_1070_00_TEXT_001F2BB0_H

#include "types.h"
/** Common node prefix used by the indexed lists; full extent is unknown. */
typedef struct FieldIndexedListNode
{
    void* value;
    struct FieldIndexedListNode* next;
} FieldIndexedListNode;
/** Partial indexed list with a stored head node. */
typedef struct FieldIndexedList
{
    FieldIndexedListNode* head;
} FieldIndexedList;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the supplied object pointer.
 * @param object Object or subobject pointer.
 * @return The same pointer.
 */
void* func_001FAD90(void* object);

/**
 * @brief Find a node by advancing from the first list element.
 * @param list List with a non-null head node.
 * @param index Number of links to advance; nonpositive values select the first node.
 * @return The selected node, or null if the chain ends first.
 */
FieldIndexedListNode* func_001FA7A0(const FieldIndexedList* list, s32 index);

/**
 * @brief Find a node by advancing from the first list element.
 * @param list List with a non-null head node.
 * @param index Number of links to advance; nonpositive values select the first node.
 * @return The selected node, or null if the chain ends first.
 */
FieldIndexedListNode* func_001FA8A0(const FieldIndexedList* list, s32 index);

#ifdef __cplusplus
}
#endif

#endif
