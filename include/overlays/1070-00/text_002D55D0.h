#ifndef SO3_OVERLAYS_1070_00_TEXT_002D55D0_H
#define SO3_OVERLAYS_1070_00_TEXT_002D55D0_H

#include "types.h"

/** Common reset prefix containing two halfwords and two words at offset 0x10. */
typedef struct FieldResetState10
{
    u8 unk00[0x10];
    s16 unk10;
    s16 unk12;
    u32 unk14;
    u32 unk18;
} FieldResetState10;

/** Partial reset receiver with two halfwords and two words at offset 0x04. */
typedef struct FieldResetState04
{
    u8 unk00[4];
    u16 unk04;
    u16 unk06;
    u32 unk08;
    u32 unk0c;
} FieldResetState04;

/** Shared sequence fields with signed counters, halfword indices, and packed modes. */
typedef struct FieldSequenceTail
{
    s32 unk00;
    u8 unk04[4];
    s16 unk08;
    s16 unk0a;
    s16 unk0c;
    s16 unk0e;
    s16 unk10;
    u8 unk12_0_3 : 4;
    u8 unk12_4_7 : 4;
    u8 unk13_0 : 1;
    u8 unk13_1 : 1;
    u8 unk13_2_7 : 6;
} FieldSequenceTail;
/** Partial receiver containing sequence state at offset 0x20. */
typedef struct FieldSequenceState20
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x18];
    FieldSequenceTail state;
} FieldSequenceState20;
/** Partial receiver containing sequence state at offset 0x10. */
typedef struct FieldSequenceState10
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x8];
    FieldSequenceTail state;
} FieldSequenceState10;
/** Partial receiver containing sequence state at offset 0x40. */
typedef struct FieldSequenceState40
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x38];
    FieldSequenceTail state;
} FieldSequenceState40;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear two halfwords and two words beginning at offset 0x10.
 * @param object Receiver to reset.
 */
void func_002D6630(FieldResetState10* object);

/**
 * @brief Clear two halfwords and two words beginning at offset 0x10.
 * @param object Receiver to reset.
 */
void func_002D6690(FieldResetState10* object);

/**
 * @brief Clear two halfwords and two words beginning at offset 0x04.
 * @param object Receiver to reset.
 */
void func_002D66F0(FieldResetState04* object);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002D6D10(FieldSequenceState20* object);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002D6DF0(FieldSequenceState20* object, u8 mode);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002D6E50(FieldSequenceState20* object, u8 mode);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002D71E0(FieldSequenceState10* object);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002D7340(FieldSequenceState10* object, u8 mode);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002D73A0(FieldSequenceState10* object, u8 mode);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002D78D0(FieldSequenceState40* object);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002D79B0(FieldSequenceState40* object, u8 mode);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002D7A10(FieldSequenceState40* object, u8 mode);

#ifdef __cplusplus
}
#endif

#endif
