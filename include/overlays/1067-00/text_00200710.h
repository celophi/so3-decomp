#ifndef SO3_OVERLAYS_1067_00_TEXT_00200710_H
#define SO3_OVERLAYS_1067_00_TEXT_00200710_H

#include "types.h"
#include "overlays/1067-00/text_001FF260.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Decrement counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002016F0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Increment counters for matching resource entries that pass their flag checks.
 * @param object Resource list to update.
 * @param first Low-halfword key for kinds 0x43484152 and 0x41545243.
 * @param second Low-halfword key for kind 0x414E494D.
 */
void func_002017B0(FieldResourceList14* object, s32 first, s32 second);

/**
 * @brief Find the size selected by a resource entry's flag.
 * @param object Resource list to search.
 * @param kind Resource kind to match.
 * @param key Resource key to match.
 * @return The selected size, or zero when no matching entry exists.
 */
u32 func_00201E20(FieldResourceList14* object, u32 kind, u32 key);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
s32 func_00201510(void* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
s32 func_00201520(void* object);

/**
 * @brief Return the current field frame delta.
 * @param object Receiver of the call; unused.
 * @return Current frame delta.
 */
float func_00201530(void* object);

/**
 * @brief Add an object to the resident object queue.
 * @param object Object to queue.
 */
void func_00201540(void* object);

/**
 * @brief Detach an object and add it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_00201560(void* object);

/**
 * @brief Return the fixed value twelve.
 * @param object Receiver of the call.
 * @return Twelve.
 */
s32 func_00202120(void* object);

#ifdef __cplusplus
}
#endif

#endif
