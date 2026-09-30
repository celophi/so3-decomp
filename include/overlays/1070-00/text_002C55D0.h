#ifndef SO3_OVERLAYS_1070_00_TEXT_002C55D0_H
#define SO3_OVERLAYS_1070_00_TEXT_002C55D0_H

#include "overlays/1070-00/text_00284BF0.h"

/** Partial receiver storing a linked object and an additional word value. */
typedef struct FieldLinkedState
{
    u8 unk00[0x24];
    void* unk24;
    u32 unk28;
} FieldLinkedState;

/** Partial receiver describing a bit limit and its packed 64-bit words. */
typedef struct FieldBitCountState
{
    s32 unk00;
    u8 unk04[0x10];
    u64* unk14;
} FieldBitCountState;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set all four vector components to one value.
 * @param vector Destination vector.
 * @param value Component value.
 * @return The destination vector.
 */
FieldVector* func_002CC6F0(FieldVector* vector, float value);

/**
 * @brief Set the linked receiver pointer and adjacent word value.
 * @param object Receiver to update.
 * @param receiver Object pointer to store.
 * @param value Word to store.
 */
void func_002CB980(FieldLinkedState* object, void* receiver, u32 value);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D1DE0(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D2490(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D2B50(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D3180(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D36F0(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D3D30(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D42B0(const FieldBitCountState* object);

/**
 * @brief Count the set bits below the stored signed bit limit.
 * @param object Receiver containing the bit limit and packed words.
 * @return The number of set bits, or zero for a nonpositive limit.
 */
s32 func_002D4850(const FieldBitCountState* object);

#ifdef __cplusplus
}
#endif

#endif
