#ifndef SO3_OVERLAYS_1070_00_TEXT_00284BF0_H
#define SO3_OVERLAYS_1070_00_TEXT_00284BF0_H

#include "types.h"

/** Partial list node; the leading bytes and full object extent are unknown. */
typedef struct FieldListNode
{
    u8 unk00[8];
    struct FieldListNode* next;
} FieldListNode;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Test whether a list traversal has reached its sentinel.
 * @param sentinel List sentinel.
 * @param node Current node.
 * @return 1 if node is the sentinel, otherwise 0.
 */
s32 func_00288650(const void* sentinel, const void* node);

/**
 * @brief Get the next node in a circular list traversal.
 * @param node Current node or list sentinel.
 * @return Next node, which may be the list sentinel.
 */
FieldListNode* func_00288660(const FieldListNode* node);

#ifdef __cplusplus
}
#endif

#endif
