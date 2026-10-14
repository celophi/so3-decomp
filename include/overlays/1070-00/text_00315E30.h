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

/** Partial receiver with a state byte at offset 0x60. */
typedef struct FieldByteState60
{
    u8 unk00[0x60];
    u8 unk60;
} FieldByteState60;

/** Partial receiver containing a byte state at offset 0x45. */
typedef struct FieldByteState45
{
    u8 unk00[0x45];
    u8 unk45;
} FieldByteState45;

/** Partial receiver containing a signed halfword at offset 0x14. */
typedef struct FieldSignedHalfAt14
{
    u8 unk00[0x14];
    s16 unk14;
} FieldSignedHalfAt14;

/** Partial receiver with two float values at 0x20 and an initialized byte at 0x44. */
typedef struct FieldFloatPairState20
{
    u8 unk00[0x20];
    float first;
    float second;
    u8 unk28[0x1C];
    u8 initialized;
} FieldFloatPairState20;

#ifdef __cplusplus
extern "C" {

/**
 * @brief Invoke the receiver's callback while its fourth mark byte is clear.
 * @param object Receiver containing the mark bytes and callback vtable.
 */
void func_00316BF0(FieldMarkedObjectSlots* object);

#endif

/**
 * @brief Call the shared no-argument helper at 0x004EABF0.
 */
void func_00316A00(void);

/**
 * @brief Call the shared no-argument helper at 0x003189D0.
 */
void func_00317FB0(void);

/**
 * @brief Call the shared no-argument helper at 0x003189D0.
 */
void func_00319150(void);

/**
 * @brief Call the shared no-argument helper at 0x003189D0.
 */
void func_00319B60(void);

/**
 * @brief Set the state byte and five adjacent floating-point values.
 * @param object Receiver to update.
 * @param first Value written at offset 0x64.
 * @param second Value written at offset 0x68.
 * @param third Value written at offset 0x6C.
 * @param fourth Value written at offset 0x70.
 * @param fifth Value written at offset 0x74.
 */
void func_0031A780(void* object, float first, float second, float third, float fourth, float fifth);

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

/**
 * @brief Set the receiver's byte at offset 0x60 to two.
 * @param object Receiver to update.
 */
void func_003169A0(FieldByteState60* object);

/**
 * @brief Store a byte value at receiver offset 0x45.
 * @param object Receiver to update.
 * @param unused Unused second argument.
 * @param value Byte value to store.
 */
void func_0031A6D0(FieldByteState45* object, void* unused, u8 value);

/**
 * @brief Check whether the signed halfword at offset 0x14 is zero.
 * @param object Receiver containing the halfword.
 * @return One when zero; otherwise zero.
 */
s32 func_0031AA60(const FieldSignedHalfAt14* object);

/**
 * @brief Store two float values and mark the receiver initialized.
 * @param object Receiver to update.
 * @param first First value to store.
 * @param second Second value to store.
 */
void func_0031A5F0(FieldFloatPairState20* object, float first, float second);

#ifdef __cplusplus
}
#endif

#endif
