#ifndef SO3_OVERLAYS_0002_00_TEXT_001ED4E0_H
#define SO3_OVERLAYS_0002_00_TEXT_001ED4E0_H

#include "types.h"

/** Partial receiver layout for the paired packed-field setters. */
typedef struct BootState1F0D60
{
    u8 pad00[0x52];
    u8 unk52_lo : 4;
    u8 unk52_hi : 4;
    u8 unk53_bit0 : 1;
    u8 unk53_other : 7;
} BootState1F0D60;

/** Partial receiver layout for the paired packed-field setters. */
typedef struct BootState1F12B0
{
    u8 pad00[0x2A];
    u8 unk2A_lo : 4;
    u8 unk2A_hi : 4;
    u8 unk2B_bit0 : 1;
    u8 unk2B_other : 7;
} BootState1F12B0;

/** Partial receiver layout for the paired packed-field setters. */
typedef struct BootState1F1580
{
    u8 pad00[0x42];
    u8 unk42_lo : 4;
    u8 unk42_hi : 4;
    u8 unk43_bit0 : 1;
    u8 unk43_other : 7;
} BootState1F1580;

/** Three float components followed by their scalar key. */
typedef struct BootVectorKeyEntry1F1D30
{
    float values[3];
    float key;
} __attribute__((aligned(16))) BootVectorKeyEntry1F1D30;

/** Partial vector-key array receiver with packed control fields. */
typedef struct BootState1F1AD0
{
    u8 unk00[4];
    BootVectorKeyEntry1F1D30* entries;
    u8 unk08[0x18];
    u32 unk20;
    float span;
    s16 count;
    s16 capacity;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    u8 unk32_lo : 4;
    u8 unk32_hi : 4;
    u8 unk33_bit0 : 1;
    u8 unk33_bit1 : 1;
    u8 unk33_other : 6;
} BootState1F1AD0;

/** Float key and value stored in the indexed array. */
typedef struct BootFloatEntry1F33B0
{
    float key;
    float value;
} BootFloatEntry1F33B0;

/** Partial float-entry array with counts, cached span, and packed control fields. */
typedef struct BootState1F1FC0
{
    u8 unk00[4];
    BootFloatEntry1F33B0* entries;
    u8 unk08[8];
    u32 unk10;
    float span;
    s16 count;
    s16 capacity;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 unk22_lo : 4;
    u8 unk22_hi : 4;
    u8 unk23_bit0 : 1;
    u8 unk23_bit1 : 1;
    u8 unk23_other : 6;
} BootState1F1FC0;

/** Partial receiver layout for the paired packed-field setters. */
typedef struct BootState1F4730
{
    u8 pad00[0x52];
    u8 unk52_lo : 4;
    u8 unk52_hi : 4;
    u8 unk53_bit0 : 1;
    u8 unk53_other : 7;
} BootState1F4730;

/** Partial receiver layout for the paired packed-field setters. */
typedef struct BootState1F4790
{
    u8 pad00[0x22];
    u8 unk22_lo : 4;
    u8 unk22_hi : 4;
    u8 unk23_bit0 : 1;
    u8 unk23_other : 7;
} BootState1F4790;

/** Partial receiver layout for the paired packed-field setters. */
typedef struct BootState1F47F0
{
    u8 pad00[0x42];
    u8 unk42_lo : 4;
    u8 unk42_hi : 4;
    u8 unk43_bit0 : 1;
    u8 unk43_other : 7;
} BootState1F47F0;

/** Settings record initialized before calls to the resident rendering interface. */
typedef struct BootSettings1F86C0
{
    u16 unk00;
    u8 unk02;
    u8 unk03;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    float unk08;
    float unk0C;
    float unk10;
    float unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
} BootSettings1F86C0;

/** Partial two-entry history of paired float values. */
typedef struct BootFloatHistory1F48D0
{
    u8 unk00[4];
    s16 count;
    s16 next_index;
    u8 unk08[12];
    float values[2];
    float unk1C[2];
} BootFloatHistory1F48D0;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset vector-key storage, counts, control fields, and cached indices.
 * @param object Array receiver to reset without releasing its current storage.
 */
void func_001F19F0(BootState1F1AD0* object);

/**
 * @brief Bind external vector-key storage and cache its first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void func_001F1A80(BootState1F1AD0* object, s32 count, BootVectorKeyEntry1F1D30* entries);

/**
 * @brief Test whether the vector-key array contains an exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return One if a key matches, or zero otherwise.
 */
s32 func_001F1BC0(BootState1F1AD0* object, float key);

/**
 * @brief Compute the span between the last and first vector-entry keys.
 * @param object Receiver with valid storage when it has at least two entries.
 * @return Key span, or zero when fewer than two entries exist.
 */
float func_001F1C30(BootState1F1AD0* object);

/**
 * @brief Wrap a key by the first-to-last vector-entry key span.
 * @param object Receiver with valid nonempty storage and a nonzero key span.
 * @param key Key to wrap using truncation after adjusting negative positions.
 * @return Key with the computed whole spans subtracted.
 */
float func_001F1D30(BootState1F1AD0* object, float key);

/**
 * @brief Read either or both members of an indexed float entry.
 * @param object Array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param key Optional destination for the entry key.
 * @param value Optional destination for the entry value.
 * @return One for an available slot, or zero if storage is absent or the index is too large.
 */
s32 func_001F3230(BootState1F1FC0* object, s32 index, float* key, float* value);

/**
 * @brief Test whether the float-entry array contains an exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return One if a matching key exists, or zero otherwise.
 */
s32 func_001F2590(BootState1F1FC0* object, float key);

/**
 * @brief Reset float-entry storage, counts, control fields, and cached indices.
 * @param object Array receiver to reset without releasing its current storage.
 */
void func_001F1E90(BootState1F1FC0* object);

/**
 * @brief Bind external entry storage and cache its first-to-last key span.
 * @param object Array receiver.
 * @param count Positive entry count representable in the receiver count fields.
 * @param entries External storage containing the specified number of entries.
 */
void func_001F26E0(BootState1F1FC0* object, s32 count, BootFloatEntry1F33B0* entries);

/**
 * @brief Wrap a key by the span between the first and last entries.
 * @param object Receiver with valid nonempty storage and a nonzero key span.
 * @param key Key to wrap using truncation after adjusting negative positions.
 * @return Key with the computed whole spans subtracted.
 */
float func_001F2450(BootState1F1FC0* object, float key);

/**
 * @brief Read the value associated with the first exactly equal key.
 * @param object Receiver with valid storage when its count is positive.
 * @param key Key to find.
 * @return Associated value, or zero when no key matches.
 */
float func_001F24E0(BootState1F1FC0* object, float key);

/**
 * @brief Compute the difference between the last and first entry keys.
 * @param object Receiver with valid storage when it has at least two entries.
 * @return Key span, or zero when fewer than two entries exist.
 */
float func_001F2540(BootState1F1FC0* object);

/**
 * @brief Store paired float values in the next slot of a two-entry history.
 * @param history History whose write index wraps and count saturates at two.
 * @param value First float value to copy.
 * @param associated Second float value to store.
 */
void func_001F48D0(BootFloatHistory1F48D0* history, const float* value, float associated);

/**
 * @brief Insert a float entry before an existing index and shift following entries.
 * @param object Array receiver with spare capacity.
 * @param index Nonnegative index less than the current count.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if inserted, or zero if storage is absent, full, or the index is too large.
 */
s32 func_001F32B0(BootState1F1FC0* object, s32 index, const float* value, float key);

/**
 * @brief Replace an indexed float entry and update the span when it is the last entry.
 * @param object Array receiver.
 * @param index Nonnegative entry index, checked against capacity.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if stored, or zero if storage is absent or the index is outside capacity.
 */
s32 func_001F33B0(BootState1F1FC0* object, s32 index, const float* value, float key);

/**
 * @brief Append a float entry and update the cached key span.
 * @param object Array receiver.
 * @param value Entry value to copy.
 * @param key Key associated with the entry.
 * @return One if appended, or zero if storage is absent or full.
 */
s32 func_001F3440(BootState1F1FC0* object, const float* value, float key);


/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F0D60(BootState1F0D60* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F0DC0(BootState1F0D60* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F12B0(BootState1F12B0* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F1310(BootState1F12B0* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F1580(BootState1F1580* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F15E0(BootState1F1580* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F1AD0(BootState1F1AD0* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F1B30(BootState1F1AD0* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F1FC0(BootState1F1FC0* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F2020(BootState1F1FC0* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F4730(BootState1F4730* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F4790(BootState1F4790* state, u32 value);

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F47F0(BootState1F47F0* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F4AC0(BootState1F47F0* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F5460(BootState1F4790* state, u32 value);

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param state Receiver containing the packed values and status bit.
 * @param value Value to store, truncated to four bits.
 */
void func_001F5A50(BootState1F4730* state, u32 value);

/**
 * @brief Initialize the settings record to its default values.
 * @param settings Settings record to initialize.
 */
void func_001F86C0(BootSettings1F86C0* settings);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EECA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EED60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EED70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EED80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F0E50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F0E60(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F0E70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F0E80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F13A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F13B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F13C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F13D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F2610(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2650(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2690(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F26D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F27D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2810(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2850(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2890(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F2B90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2BD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2C10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F2C50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F4950(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F4960(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F4970(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F4B50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F4B90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F4BD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F4C10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F54F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F5530(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F5570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F55B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F5AE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F5B20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F5B60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F5BA0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_001FB220(void* object);

/**
 * @brief Return the 32-bit word at offset 0x40.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F0E20(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x48.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F0E30(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x4A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F0E40(void* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F10B0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x18.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F1370(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x20.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F1380(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x22.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F1390(void* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F1420(void* object);

/**
 * @brief Return the 32-bit word at offset 0x30.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F1640(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x38.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F1650(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x3A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F1660(void* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F16E0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x20.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F1B90(void* object);

/**
 * @brief Return the vector-key array count.
 * @param object Array receiver.
 * @return Stored entry count.
 */
s16 func_001F1BA0(BootState1F1AD0* object);

/**
 * @brief Return the vector-key array capacity.
 * @param object Array receiver.
 * @return Stored entry capacity.
 */
s16 func_001F1BB0(BootState1F1AD0* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F1DC0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x10.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F2080(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x18.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F2090(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x1A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F20A0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F20F0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x30.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F4B20(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x38.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F4B30(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x3A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F4B40(void* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F4CC0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x10.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F54C0(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x18.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F54D0(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x1A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F54E0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F58B0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x40.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F5AB0(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x48.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F5AC0(void* object);

/**
 * @brief Return the signed 16-bit value at offset 0x4A.
 * @param object Object containing the value.
 * @return The stored value.
 */
s16 func_001F5AD0(void* object);

/**
 * @brief Return the 32-bit word at offset 0x4.
 * @param object Object containing the value.
 * @return The stored value.
 */
u32 func_001F5E00(void* object);

/**
 * @brief Return the object pointer.
 * @param object Object to return.
 * @return The object pointer.
 */
void* func_001F2950(void* object);

/**
 * @brief Return the object pointer.
 * @param object Object to return.
 * @return The object pointer.
 */
void* func_001F2D60(void* object);

/**
 * @brief Return the object pointer.
 * @param object Object to return.
 * @return The object pointer.
 */
void* func_001F30E0(void* object);

/**
 * @brief Return the object pointer.
 * @param object Object to return.
 * @return The object pointer.
 */
void* func_001F5E10(void* object);

/**
 * @brief Return the object pointer.
 * @param object Object to return.
 * @return The object pointer.
 */
void* func_001F6000(void* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0f.
 */
float func_001F13E0(void* object);

/**
 * @brief Return zero as a float.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0f.
 */
float func_001F20B0(void* object);

/**
 * @brief Copy the float at offset 0x50.
 * @param object Object containing the value.
 * @param value Destination for the value.
 */
void func_001EFD70(void* object, float* value);

/**
 * @brief Copy the float at offset 0x4C.
 * @param object Object containing the value.
 * @param value Destination for the value.
 */
void func_001F04B0(void* object, float* value);

/**
 * @brief Set the byte at offset 0x60 to 10.
 * @param object Object containing the byte.
 */
void func_001FA880(void* object);


/**
 * @brief Set the pointer at offset 0x4C to D_171B98.
 * @param object Object to update.
 * @return The object pointer.
 */
void* func_001EFDB0(void* object);

/**
 * @brief Set the pointer at offset 0x1C to D_171B88.
 * @param object Object to update.
 * @return The object pointer.
 */
void* func_001EFE30(void* object);

/**
 * @brief Clear the fields at offsets 0x10 through 0x18.
 * @param object Object to clear.
 */
void func_001F0660(void* object);

/**
 * @brief Clear the fields at offsets 0x10 through 0x18.
 * @param object Object to clear.
 */
void func_001F06C0(void* object);

/**
 * @brief Clear the fields at offsets 0x4 through 0xC.
 * @param object Object to clear.
 */
void func_001F0720(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void func_001F1670(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void func_001F1C10(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void func_001F4C50(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void func_001F5650(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void func_001F5C30(void* object);

/**
 * @brief Forward to the cleanup routine for the containing object.
 * @param object Embedded object at offset 0x90.
 */
void func_001FA890(void* object);

/**
 * @brief Clear four words starting at offset 0.
 * @param object Object to clear.
 */
void func_001F0EE0(void* object);

/**
 * @brief Write the difference between the last and first float values in an eight-byte record array.
 * @param object Object containing the array pointer and count.
 * @param result Destination for the difference; unchanged if the array is absent.
 */
void func_001F0480(void* object, float* result);

/**
 * @brief Write the difference between the last and first float values in a sixteen-byte record array.
 * @param object Object containing the array pointer and count.
 * @param result Destination for the difference; unchanged if the array is absent.
 */
void func_001EFD80(void* object, float* result);

#ifdef __cplusplus
}
#endif

#endif
