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

#ifdef __cplusplus
}
#endif

#endif
