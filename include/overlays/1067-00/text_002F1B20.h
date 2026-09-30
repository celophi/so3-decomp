#ifndef SO3_OVERLAYS_1067_00_TEXT_002F1B20_H
#define SO3_OVERLAYS_1067_00_TEXT_002F1B20_H

#include "types.h"

/** Halfword bucket with a signed used count. */
typedef struct FieldHalfwordBucket
{
    u16 values[750];
    s32 count;
} FieldHalfwordBucket;

/** Partial receiver containing eight halfword buckets and associated byte counts. */
typedef struct FieldHalfwordBuckets
{
    FieldHalfwordBucket buckets[8];
    u8 unk2f00[4];
    u32 unk2f04;
    u16 unk2f08;
    u16 unk2f0a;
    u8 unk2f0c[750];
} FieldHalfwordBuckets;

/** Partial target with an unsigned byte state. */
typedef struct FieldByteState0A
{
    u8 unk00[0xA];
    u8 unk0a;
} FieldByteState0A;

/** A 32-byte record containing a state target. */
typedef struct FieldStateTargetEntry
{
    FieldByteState0A* target;
    u8 unk04[0x18];
    u8 unk1c;
    u8 unk1d[2];
    u8 unk1f;
} FieldStateTargetEntry;

/** Partial receiver containing three target entries and their populated count. */
typedef struct FieldStateTargets
{
    FieldStateTargetEntry entries[3];
    u8 unk60[0x27];
    u8 unk87;
} FieldStateTargets;

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
