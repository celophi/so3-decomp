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
 * @brief Read the byte at offset 0x14.
 * @param object Receiver to inspect.
 * @return The stored byte.
 */
u8 func_001DF350(const FieldByteState14* object);

/**
 * @brief Default virtual handler that performs no work.
 * @param object Receiver of the virtual call.
 */
void func_001DF370(void* object);

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

#ifdef __cplusplus
}
#endif

#endif
