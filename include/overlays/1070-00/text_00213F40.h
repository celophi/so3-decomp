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

/** Partial receiver containing checked word and halfword groups. */
typedef struct FieldCheckedState7C
{
    u8 unk00[0x34];
    u32 unk34;
    u32 unk38;
    u32 unk3c;
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u32 unk4c;
    u32 unk50;
    u32 unk54;
    u32 unk58;
    u32 unk5c;
    u32 unk60;
    u8 unk64[8];
    u32 unk6c;
    u8 unk70[0xC];
    s16 unk7c;
    s16 unk7e;
    s16 unk80;
    u8 unk82[0x12];
    u32 unk94;
    u32 unk98;
    u32 unk9c;
    u32 unka0;
    u8 unka4[4];
    s32 unka8;
    s32 unkac;
} FieldCheckedState7C;

/** Partial 0x1C-byte array entry handled by func_0021A970. */
typedef struct FieldEntry1C
{
    u8 unk00[0x1C];
} FieldEntry1C;

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

/**
 * @brief Validate the word group at offset 0x58 and decode the value at offset 0x6C.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214490(const FieldCheckedState7C* object);

/**
 * @brief Validate the word group at offset 0x58 and decode its stored value.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214650(const FieldCheckedState7C* object);

/**
 * @brief Validate the word group at offset 0x4C and decode the value at offset 0x50.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_002148D0(const FieldCheckedState7C* object);

/**
 * @brief Validate the word group at offset 0x40 and decode the value at offset 0x48.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214AA0(const FieldCheckedState7C* object);

/**
 * @brief Validate the word group at offset 0x34 and decode the value at offset 0x3C.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214C70(const FieldCheckedState7C* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00215EB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00215EC0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00215FE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216090(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216100(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216180(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216870(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216880(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00216890(void* object);

/**
 * @brief Return the fixed value 300.
 * @param object Receiver or first argument; unused.
 * @return Always 300.
 */
s32 func_00216910(void* object);

/**
 * @brief Return the fixed value -1.
 * @param object Receiver or first argument; unused.
 * @return Always -1.
 */
s32 func_00216C30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216CA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216CB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00219670(void* object);

/**
 * @brief Return the fixed value 12.
 * @param object Receiver or first argument; unused.
 * @return Always 12.
 */
s32 func_0021A960(void* object);

/**
 * @brief Pass the entry's word at offset 0x4 to func_100D60 and clear it, if bit 1 of its
 *        byte at offset 0x16 is set.
 * @param entry Entry to update.
 * @return 1 if the word was passed on and cleared, otherwise 0.
 */
s32 func_0021A970(FieldEntry1C* entry);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00221620(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00221660(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00221FB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002239B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223A40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223A50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223A60(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223A70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00223A80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00223A90(void* object);

#ifdef __cplusplus
}
#endif

#endif
