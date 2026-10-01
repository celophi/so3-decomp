#ifndef SO3_OVERLAYS_1070_00_TEXT_00315E30_H
#define SO3_OVERLAYS_1070_00_TEXT_00315E30_H

#include "types.h"

/** Partial receiver containing object slots and their parallel marker bytes. */
typedef struct FieldMarkedObjectSlots
{
    u8 unk00[0x18];
    void* unk18[32];
    u8 unk98[32];
} FieldMarkedObjectSlots;

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
 * @brief Mark the first object slot whose pointer equals the target.
 * @param object Receiver containing object slots and marker bytes.
 * @param target Object pointer to find.
 */
void func_00316670(FieldMarkedObjectSlots* object, void* target);

/**
 * @brief Reset the byte counts and associated totals.
 * @param object Receiver containing the counts and totals.
 */
void func_003173D0(FieldHalfwordBuckets* object);

/**
 * @brief Read a halfword from an in-range category and populated bucket index.
 * @param object Receiver containing the buckets.
 * @param category Bucket category.
 * @param index Index within the selected bucket.
 * @return The stored halfword, or zero when either index is out of range.
 */
u16 func_00317CD0(const FieldHalfwordBuckets* object, u8 category, u16 index);

/**
 * @brief Find a target entry by its byte key and return its state.
 * @param object Receiver containing the target entries.
 * @param key Byte key to find.
 * @return The first matching entry state, or zero if no entry matches.
 */
u8 func_003186B0(const FieldStateTargets* object, u8 key);

/**
 * @brief Set every populated target state to two.
 * @param object Receiver containing the target entries.
 */
void func_00318A30(FieldStateTargets* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00316440(void* object);

#ifdef __cplusplus
}
#endif

#endif
