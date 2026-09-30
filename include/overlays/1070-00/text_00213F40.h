#ifndef SO3_OVERLAYS_1070_00_TEXT_00213F40_H
#define SO3_OVERLAYS_1070_00_TEXT_00213F40_H

#include "types.h"

/** A 32-byte record in the observed child and sibling traversal. */
typedef struct FieldTraversalRecord
{
    struct FieldTraversalRecord* children;
    u8 unk04[6];
    u8 unk0a;
    u8 unk0b[3];
    s16 unk0e;
    u8 unk10[0x10];
} FieldTraversalRecord;

/** Partial receiver whose scaled float value is at offset 0x30. */
typedef struct FieldFloatState30
{
    u8 unk00[0x30];
    float unk30;
} FieldFloatState30;

/** Partial target containing a value and its update byte. */
typedef struct FieldValueState100
{
    u8 unk00[0x40];
    u8 unk40;
    u8 unk41[0xBF];
    s32 unk100;
} FieldValueState100;

/** Partial receiver whose optional value target is at offset 0x34. */
typedef struct FieldValueOwner34
{
    u8 unk00[0x34];
    FieldValueState100* unk34;
} FieldValueOwner34;

/** Partial receiver containing two checked halfword groups and their check words. */
typedef struct FieldCheckedState00
{
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0a;
    u8 unk0c[0xDC];
    s32 unke8;
    s32 unkec;
    u8 unkf0[0x1C];
    s32 unk10c;
} FieldCheckedState00;

/** Partial receiver containing a checked halfword group at offset 0x7C. */
typedef struct FieldCheckedState7C
{
    u8 unk00[0x7C];
    s16 unk7c;
    s16 unk7e;
    s16 unk80;
    u8 unk82[0x26];
    s32 unka8;
    s32 unkac;
} FieldCheckedState7C;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Advance to the next contiguous record.
 * @param record Current traversal record.
 * @return The following record.
 */
FieldTraversalRecord* func_0021EC30(FieldTraversalRecord* record);

/**
 * @brief Test bit 0x20 that terminates the observed sibling traversal.
 * @param record Current traversal record.
 * @return One when the bit is set, otherwise zero.
 */
s32 func_0021EC40(const FieldTraversalRecord* record);

/**
 * @brief Get the child record sequence.
 * @param record Current traversal record.
 * @return The child sequence pointer, or null.
 */
FieldTraversalRecord* func_0021EC50(const FieldTraversalRecord* record);

/**
 * @brief Read the signed record index.
 * @param record Current traversal record.
 * @return The stored index, including the observed -1 sentinel.
 */
s16 func_0021EC60(const FieldTraversalRecord* record);

/**
 * @brief Read the stored float scaled by one sixteenth.
 * @param object Receiver to inspect.
 * @return The stored value multiplied by 0.0625.
 */
float func_00214DA0(const FieldFloatState30* object);

/**
 * @brief Update the optional target value and set its update byte.
 * @param object Receiver whose target may be null.
 * @param value Signed value to store.
 */
void func_0021EF10(FieldValueOwner34* object, s32 value);

/**
 * @brief Validate the second halfword group and decode its stored value.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_002140E0(const FieldCheckedState00* object);

/**
 * @brief Validate the first halfword group and decode its stored value.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214200(const FieldCheckedState00* object);

/**
 * @brief Validate the halfword group at offset 0x7C and decode its stored value.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214320(const FieldCheckedState7C* object);

#ifdef __cplusplus
}
#endif

#endif
