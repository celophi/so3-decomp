#ifndef SO3_OVERLAYS_1070_00_TEXT_00305890_H
#define SO3_OVERLAYS_1070_00_TEXT_00305890_H

#include "overlays/1070-00/text_001F2BB0.h"

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

#ifdef __cplusplus
}
#endif

#endif
