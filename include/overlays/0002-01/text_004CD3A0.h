#ifndef SO3_OVERLAYS_0002_01_TEXT_004CD3A0_H
#define SO3_OVERLAYS_0002_01_TEXT_004CD3A0_H

#include "types.h"

/** Partial list node; the leading bytes and full object extent are unknown. */
typedef struct LibListNode
{
    u8 unk00[8];
    struct LibListNode* next;
} LibListNode;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Test whether a list traversal has reached its sentinel.
 * @param sentinel List sentinel.
 * @param node Current node.
 * @return 1 if node is the sentinel, otherwise 0.
 */
s32 func_004D6DC0(const void* sentinel, const void* node);

/**
 * @brief Get the next node in a circular list traversal.
 * @param node Current node or list sentinel.
 * @return Next node, which may be the list sentinel.
 */
LibListNode* func_004D6DD0(const LibListNode* node);

#ifdef __cplusplus
}
#endif

#endif
