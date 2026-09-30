#ifndef SO3_OVERLAYS_1067_00_TEXT_002F9C90_H
#define SO3_OVERLAYS_1067_00_TEXT_002F9C90_H

#include "types.h"
#include "overlays/1067-00/text_002F3310.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset the byte counts and associated totals.
 * @param object Receiver containing the counts and totals.
 */
void func_002FA210(FieldHalfwordBuckets* object);

/**
 * @brief Read a halfword from an in-range category and populated bucket index.
 * @param object Receiver containing the buckets.
 * @param category Bucket category.
 * @param index Index within the selected bucket.
 * @return The stored halfword, or zero when either index is out of range.
 */
u16 func_002FAB20(const FieldHalfwordBuckets* object, u8 category, u16 index);

/**
 * @brief Find a target entry by its byte key and return its state.
 * @param object Receiver containing the target entries.
 * @param key Byte key to find.
 * @return The first matching entry state, or zero if no entry matches.
 */
u8 func_002FB510(const FieldStateTargets* object, u8 key);

/**
 * @brief Set every populated target state to two.
 * @param object Receiver containing the target entries.
 */
void func_002FB8A0(FieldStateTargets* object);

#ifdef __cplusplus
}
#endif

#endif
