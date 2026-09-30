#ifndef SO3_OVERLAYS_1067_00_TEXT_001DED80_H
#define SO3_OVERLAYS_1067_00_TEXT_001DED80_H

#include "types.h"
#include "overlays/1067-00/text_001DD3C0.h"

/** Partial receiver with a byte at offset 0x14. */
typedef struct FieldByteState14
{
    u8 unk00[0x14];
    u8 unk14;
} FieldByteState14;

/** 16-byte entry of the array owned by FieldEntryArrayObject: a sort value followed by three floats. */
typedef struct FieldArrayEntry10
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
} FieldArrayEntry10;

/** Partial object owning a counted array of 16-byte entries, with index, nibble and flag state. */
typedef struct FieldEntryArrayObject
{
    u8 unk00[4];
    FieldArrayEntry10* unk04;
    u8 unk08[0x10];
    s32 unk18;
    float unk1c;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    u8 unk2a_0_3 : 4;
    u8 unk2a_4_7 : 4;
    u8 unk2b_0 : 1;
    u8 unk2b_1 : 1;
    u8 unk2b_2_7 : 6;
    u8 unk2c[0x20];
    u32 unk4c;
    float unk50;
} FieldEntryArrayObject;

/** Partial record of four copied floats, a start/end pair and their cached nonzero span. */
typedef struct FieldFloatSpan1C
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
    float unk10;
    float unk14;
    float unk18;
} FieldFloatSpan1C;

/** Partial receiver with a word at offset 0x30 and a byte at offset 0x34. */
typedef struct FieldWordByte30
{
    u8 unk00[0x30];
    u32 unk30;
    u8 unk34;
} FieldWordByte30;

/** Partial base receiver with a word at offset 0x18 and flag bit 0 at offset 0x20. */
typedef struct FieldFlagObject20
{
    u8 unk00[0x18];
    u32 unk18;
    u8 unk1c[4];
    u8 unk20_0 : 1;
    u8 unk20_1_7 : 7;
} FieldFlagObject20;

/** Four adjacent floats in a 16-byte record. */
typedef struct FieldFloat4
{
    float unk00;
    float unk04;
    float unk08;
    float unk0c;
} FieldFloat4;

/** Partial receiver with flag bit 0 at offset 0x20 and six 16-byte float records at offset 0x130. */
typedef struct FieldRecordObject130
{
    u8 unk00[0x20];
    u8 unk20_0 : 1;
    u8 unk20_1_7 : 7;
    u8 unk21[0x10F];
    FieldFloat4 unk130[6];
} FieldRecordObject130;

/** Partial receiver with three words at offsets 0x10-0x18 and flag bit 1 at offset 0x66. */
typedef struct FieldStateReset66
{
    u8 unk00[0x10];
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u8 unk1c[0x4A];
    u8 unk66_0 : 1;
    u8 unk66_1 : 1;
    u8 unk66_2_7 : 6;
} FieldStateReset66;

/** Partial circular-list node keyed by the word at offset 0x54. */
typedef struct FieldKeyedListNode54
{
    u8 unk00[8];
    struct FieldKeyedListNode54* next;
    u8 unk0c[0x48];
    u32 unk54;
} FieldKeyedListNode54;

/** Partial receiver with a key, five float parameters, a constant float, a flag halfword and a mode word at offsets 0x98-0xB8. */
typedef struct FieldMotionParams98
{
    u8 unk00[0x98];
    u32 unk98;
    float unk9c;
    float unka0;
    float unka4;
    float unka8;
    float unkac;
    float unkb0;
    u16 unkb4;
    u8 unkb6[2];
    s32 unkb8;
} FieldMotionParams98;

/** Partial receiver with a signed halfword at offset 0x3A. */
typedef struct FieldHalfword3A
{
    u8 unk00[0x3A];
    s16 unk3a;
} FieldHalfword3A;

/** Partial receiver with a pointer at offset 0x30, a signed counter at offset 0xC0 and flags at offset 0xC4. */
typedef struct FieldCounterObjectC0
{
    u8 unk00[0x30];
    void* unk30;
    u8 unk34[0x8C];
    s32 unkc0;
    u8 unkc4_0 : 1;
    u8 unkc4_1 : 1;
    u8 unkc4_2_7 : 6;
} FieldCounterObjectC0;

/** Partial record with a leading pointer, flag byte at offset 0xA and signed halfword at offset 0xE. */
typedef struct FieldPackedRecord0E
{
    void* unk00;
    u8 unk04[6];
    u8 unk0a;
    u8 unk0b[3];
    s16 unk0e;
} FieldPackedRecord0E;

/** Partial object receiving a byte flag at offset 0x3C and a signed count at offset 0xFC. */
typedef struct FieldCountTarget
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[0xBF];
    s32 unkfc;
} FieldCountTarget;

/** Partial receiver holding an optional FieldCountTarget at offset 0x34. */
typedef struct FieldCountOwner34
{
    u8 unk00[0x34];
    FieldCountTarget* unk34;
} FieldCountOwner34;

/** Partial receiver with pointers at offsets 0x80 and 0x448 and a disabling bit 5 at offset 0x8C. */
typedef struct FieldGatedObject448
{
    u8 unk00[0x80];
    void* unk80;
    u8 unk84[8];
    u8 unk8c_0_4 : 5;
    u8 unk8c_5 : 1;
    u8 unk8c_6_7 : 2;
    u8 unk8d[0x3BB];
    void* unk448;
} FieldGatedObject448;

/** Partial receiver with an entry array pointer at offset 4 and entry state at offsets 0x30-0x43. */
typedef struct FieldEntryArrayObject30
{
    u8 unk00[4];
    FieldArrayEntry10* unk04;
    u8 unk08[0x28];
    u32 unk30;
    u8 unk34[4];
    s16 unk38;
    s16 unk3a;
    s16 unk3c;
    s16 unk3e;
    s16 unk40;
    u8 unk42_0_3 : 4;
    u8 unk42_4_7 : 4;
    u8 unk43_0 : 1;
    u8 unk43_1 : 1;
    u8 unk43_2_7 : 6;
} FieldEntryArrayObject30;

/** Partial 28-byte record reset by func_001E5690 and func_001E5AD0. */
typedef struct FieldSlotRecord1C
{
    u8 unk00[4];
    u32 unk04;
    u8 unk08_0 : 1;
    u8 unk08_1_7 : 7;
    u8 unk09[3];
    s32 unk0c;
    u32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_3_7 : 5;
    u8 unk17[5];
} FieldSlotRecord1C;

/** Partial receiver owning a counted array of 28-byte records at offset 0x1C. */
typedef struct FieldSlotRecordOwner1C
{
    u8 unk00[0x14];
    u8 unk14;
    u8 unk15[7];
    FieldSlotRecord1C* unk1c;
    u32 unk20;
    s32 unk24;
    u8 unk28[5];
    u8 unk2d;
    u8 unk2e;
    u8 unk2f;
    u8 unk30[8];
    s32 unk38;
    s32 unk3c;
} FieldSlotRecordOwner1C;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find a listed object whose flag word shares a bit with the mask and whose word at offset 0x70 matches the key.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 * @param key Value compared with the word at offset 0x70.
 * @param mask Bits tested against the flag word at offset 0x78.
 * @return The first matching object, or null if none matches.
 */
FieldFlaggedListObject* func_001DEE30(FieldFlaggedListObject* list, s32 key, u32 mask);

/**
 * @brief Call func_00234000 for each listed object whose flag bit 3 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DEE90(FieldFlaggedListObject* list);

/**
 * @brief Call func_00233620 for each listed object whose flag bit 3 is set.
 * @param list Head of a circular object list; traversal stops on return to it or at a null link.
 */
void func_001DEF00(FieldFlaggedListObject* list);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DF220(void* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DF2B0(const void* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DF2C0(const void* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DF2D0(const void* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DF2E0(const void* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DF2F0(void* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DF300(void* object);

/**
 * @brief Report the fixed value 3 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 3.
 */
s32 func_001DF310(const void* object);

/**
 * @brief Read the byte at offset 0x14.
 * @param object Receiver to inspect.
 * @return The stored byte.
 */
u8 func_001DF350(const FieldByteState14* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DF360(void* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DF370(void* object);

/**
 * @brief Report the fixed value 3 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 3.
 */
s32 func_001DF3D0(const void* object);

/**
 * @brief Clear the word at offset 0x4C, then reset the entry array state.
 * @param object Receiver to reset.
 */
void func_001DF850(FieldEntryArrayObject* object);

/**
 * @brief Copy the float at offset 0x50 to the output.
 * @param object Receiver to inspect.
 * @param out Destination for the float.
 */
void func_001DFA30(const FieldEntryArrayObject* object, float* out);

/**
 * @brief Store the difference between the float at offset 4 of the last and first entries.
 * @param object Receiver owning the entry array and its signed count.
 * @param out Destination for the difference; unchanged when the array pointer is null.
 */
void func_001DFA40(const FieldEntryArrayObject* object, float* out);

/**
 * @brief Clear the entry array pointer, counters and flags, and set both nibbles and the three halfword indices to their initial values.
 * @param object Receiver to reset.
 */
void func_001DFAE0(FieldEntryArrayObject* object);

/**
 * @brief Store the low nibble at offset 0x2A, then set flag bit 0 at offset 0x2B when either nibble is 4.
 * @param object Receiver to update.
 * @param value Value whose low four bits are stored.
 */
void func_001DFC10(FieldEntryArrayObject* object, s32 value);

/**
 * @brief Store the high nibble at offset 0x2A, then set flag bit 0 at offset 0x2B when either nibble is 4.
 * @param object Receiver to update.
 * @param value Value whose low four bits are stored.
 */
void func_001DFC70(FieldEntryArrayObject* object, s32 value);

/**
 * @brief Read the signed cycle count at offset 0x18.
 * @param object Receiver to inspect.
 * @return The stored count.
 */
s32 func_001DFCD0(const FieldEntryArrayObject* object);

/**
 * @brief Read the signed entry count at offset 0x20.
 * @param object Receiver to inspect.
 * @return The stored count.
 */
s16 func_001DFCE0(const FieldEntryArrayObject* object);

/**
 * @brief Read the signed halfword at offset 0x22.
 * @param object Receiver to inspect.
 * @return The stored halfword.
 */
s16 func_001DFCF0(const FieldEntryArrayObject* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DFD00(const void* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DFD10(const void* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001DFD20(const void* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DFD30(void* object);

/**
 * @brief Report a fixed zero value for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.0f.
 */
float func_001DFD40(const void* object);

/**
 * @brief Read the entry array pointer at offset 4.
 * @param object Receiver to inspect.
 * @return The stored entry array, possibly null.
 */
FieldArrayEntry10* func_001DFD80(const FieldEntryArrayObject* object);

/**
 * @brief Wrap a value into the span between the first and last entry sort values.
 * @param object Receiver owning the entry array and its signed count.
 * @param value Value to wrap.
 * @return value reduced by a whole number of spans, or value unchanged when that number is zero.
 */
float func_001DFDE0(const FieldEntryArrayObject* object, float value);

/**
 * @brief Compute the span between the first and last entry sort values.
 * @param object Receiver owning the entry array and its signed count.
 * @return The span, or 0.0f when fewer than two entries exist.
 */
float func_001DFED0(const FieldEntryArrayObject* object);

/**
 * @brief Test whether an entry has exactly the given sort value.
 * @param object Receiver owning the entry array and its signed count.
 * @param key Sort value to find.
 * @return 1 when a matching entry exists, otherwise 0.
 */
s32 func_001DFF20(const FieldEntryArrayObject* object, float key);

/**
 * @brief Install an entry array, set both counts, mark the array as installed and cache its span.
 * @param object Receiver to update.
 * @param count Number of entries; must be at least one.
 * @param entries Entry array to install.
 */
void func_001DFF70(FieldEntryArrayObject* object, s32 count, FieldArrayEntry10* entries);

/**
 * @brief Write one entry, refreshing the cached span when it is the last active entry.
 * @param object Receiver owning the entry array and its counts.
 * @param index Entry index; rejected unless below the halfword at offset 0x22.
 * @param key Sort value to store.
 * @param x First float to store.
 * @param y Second float to store.
 * @param z Third float to store.
 * @return 1 when the entry was written, or 0 when the array is null or the index is rejected.
 */
s32 func_001E0220(FieldEntryArrayObject* object, s32 index, float key, const float* x, const float* y, const float* z);

/**
 * @brief Copy four floats, store the start and end values, and cache their span, using 1.0f when the span is zero.
 * @param object Record to fill.
 * @param a Float stored at offset 0.
 * @param b Float stored at offset 8.
 * @param c Float stored at offset 4.
 * @param d Float stored at offset 0xC.
 * @param start Value stored at offset 0x10.
 * @param end Value stored at offset 0x14.
 */
void func_001E11E0(FieldFloatSpan1C* object, const float* a, const float* b, const float* c, const float* d, float start, float end);

/**
 * @brief Report the fixed value 4 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 4.
 */
s32 func_001E1590(const void* object);

/**
 * @brief Report the fixed value 0 for this receiver class.
 * @param object Receiver of the virtual call.
 * @return Always 0.
 */
s32 func_001E1820(const void* object);

/**
 * @brief Store the word at offset 0x30 and the byte at offset 0x34.
 * @param object Receiver to update.
 * @param word Word to store.
 * @param value Byte to store.
 */
void func_001E5020(FieldWordByte30* object, u32 word, u8 value);

/**
 * @brief Store the word at offset 0x18.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_001E6CF0(FieldFlagObject20* object, u32 value);

/**
 * @brief Clear flag bit 0 at offset 0x20.
 * @param object Receiver to update.
 */
void func_001E6D00(FieldFlagObject20* object);

/**
 * @brief Set flag bit 0 at offset 0x20.
 * @param object Receiver to update.
 */
void func_001E73D0(FieldFlagObject20* object);

/**
 * @brief Clear flag bit 0 at offset 0x20 and the last float of each of the six records at offset 0x130.
 * @param object Receiver to update.
 */
void func_001E7520(FieldRecordObject130* object);

/**
 * @brief Clear the words at offsets 0x10-0x18 and flag bit 1 at offset 0x66.
 * @param object Receiver to reset.
 */
void func_001E7560(FieldStateReset66* object);

/**
 * @brief Find a node whose word at offset 0x54 matches the key, stopping on return to the list head.
 * @param list Head of a circular list; its links are assumed nonnull.
 * @param key Value compared with the word at offset 0x54.
 * @return The first matching node, or null if none matches.
 */
FieldKeyedListNode54* func_001E8490(FieldKeyedListNode54* list, u32 key);

/**
 * @brief Store the key and float parameters, the fixed value 300.0f, the low flag bits at offset 0xB4 and mode 2.
 * @param object Receiver to configure.
 * @param key Word stored at offset 0x98.
 * @param flags Value merged into the low byte of the halfword at offset 0xB4, preserving its high byte.
 * @param a Float stored at offset 0x9C.
 * @param b Float stored at offset 0xA0.
 * @param c Float stored at offset 0xA8.
 * @param d Float stored at offset 0xB0.
 * @param e Float stored at offset 0xA4.
 */
void func_001E8E00(FieldMotionParams98* object, u32 key, u16 flags, float a, float b, float c, float d, float e);

/**
 * @brief Read the signed halfword at offset 0x3A.
 * @param object Receiver to inspect.
 * @return The stored halfword.
 */
s16 func_001E9380(const FieldHalfword3A* object);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver to return.
 * @return object.
 */
void* func_001E9E80(void* object);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver to return.
 * @return object.
 */
void* func_001E9E90(void* object);

/**
 * @brief Update the receiver; func_001EA9B0 calls it after advancing the counter when the gating flags are set.
 * @param object Receiver to process.
 */
void func_001EA730(FieldCounterObjectC0* object);

/**
 * @brief Advance the counter at offset 0xC0, then call func_001EA730 when the pointer at offset 0x30 is set and flag bit 1 at offset 0xC4 is set.
 * @param object Receiver to update.
 */
void func_001EA9B0(FieldCounterObjectC0* object);

/**
 * @brief Test bit 5 of the flag byte at offset 0xA.
 * @param record Record to inspect.
 * @return 1 when the bit is set, otherwise 0.
 */
s32 func_001EB2C0(const FieldPackedRecord0E* record);

/**
 * @brief Read the leading pointer.
 * @param record Record to inspect.
 * @return The stored pointer.
 */
void* func_001EB2D0(const FieldPackedRecord0E* record);

/**
 * @brief Read the signed halfword at offset 0xE.
 * @param record Record to inspect.
 * @return The stored halfword.
 */
s16 func_001EB2E0(const FieldPackedRecord0E* record);

/**
 * @brief Store a count and set the byte flag in the optional target at offset 0x34.
 * @param object Receiver holding the target.
 * @param count Signed count stored at the target's offset 0xFC.
 */
void func_001EB690(FieldCountOwner34* object, s32 count);

/**
 * @brief Test that both pointers at offsets 0x80 and 0x448 are set and bit 5 at offset 0x8C is clear.
 * @param object Receiver to inspect.
 * @return 1 when all conditions hold, otherwise 0.
 */
s32 func_001ECF10(const FieldGatedObject448* object);

/**
 * @brief Copy one entry's sort value and floats to the optional outputs.
 * @param object Receiver owning the entry array and its counts.
 * @param index Entry index; rejected unless below the halfword at offset 0x22.
 * @param key Optional destination for the sort value.
 * @param x Optional destination for the first float.
 * @param y Optional destination for the second float.
 * @param z Optional destination for the third float.
 * @return 1 when the entry was read, or 0 when the array is null or the index is rejected.
 */
s32 func_001DFFC0(const FieldEntryArrayObject* object, s32 index, float* key, float* x, float* y, float* z);

/**
 * @brief Insert an entry before the given active index, shifting later entries up by one.
 * @param object Receiver owning the entry array and its counts.
 * @param index Insertion index; rejected unless below the active count.
 * @param key Sort value to store.
 * @param x First float to store.
 * @param y Second float to store.
 * @param z Third float to store.
 * @return 1 when the entry was inserted, or 0 when the array is null, full or the index is rejected.
 */
s32 func_001E0100(FieldEntryArrayObject* object, s32 index, float key, const float* x, const float* y, const float* z);

/**
 * @brief Append an entry after the active ones and refresh the cached span.
 * @param object Receiver owning the entry array and its counts.
 * @param x First float to store.
 * @param y Second float to store.
 * @param z Third float to store.
 * @param key Sort value to store.
 * @return 1 when the entry was appended, or 0 when the array is null or full.
 */
s32 func_001E02C0(FieldEntryArrayObject* object, const float* x, const float* y, const float* z, float key);

/**
 * @brief Reset every 28-byte record in the counted array at offset 0x1C, then clear the word at offset 0x20 and the bytes at offsets 0x2D-0x2F, and set the byte at offset 0x14 to 8, the word at 0x38 to 2 and the word at 0x3C to -1.
 * @param object Receiver owning the records; the loop is skipped when the array pointer is null.
 */
void func_001E5690(FieldSlotRecordOwner1C* object);

/**
 * @brief Reset every 28-byte record in the counted array at offset 0x1C, then clear the word at offset 0x20 and the bytes at offsets 0x2D-0x2F.
 * @param object Receiver owning the records; the loop is skipped when the array pointer is null.
 */
void func_001E5AD0(FieldSlotRecordOwner1C* object);

/**
 * @brief Clear the entry array pointer, counters and flags, and set both nibbles and the three halfword indices to their initial values.
 * @param object Receiver to reset.
 */
void func_001E94F0(FieldEntryArrayObject30* object);

#ifdef __cplusplus
}
#endif

#endif
