#ifndef SO3_OVERLAYS_1070_00_TEXT_002E55F0_H
#define SO3_OVERLAYS_1070_00_TEXT_002E55F0_H

#include "types.h"

/** Partial receiver whose flag byte is at offset 0x70. */
typedef struct FieldByteFlags70
{
    u8 unk00[0x70];
    u8 unk70_0_1 : 2;
    u8 unk70_2 : 1;
    u8 unk70_3_7 : 5;
} FieldByteFlags70;

/** Partial reset prefix with an opaque word and four halfwords. */
typedef struct FieldResetState40
{
    u8 unk00[0x40];
    u32 unk40;
    u8 unk44[4];
    u16 unk48;
    u8 unk4a[2];
    s16 unk4c;
    s16 unk4e;
    s16 unk50;
} FieldResetState40;

/** Partial receiver with three allocations, aligned pointers and sizes. */
typedef struct FieldBufferSlots
{
    u8 unk00[0x11C];
    void* unk11c[3];
    void* unk128[3];
    s32 unk134[3];
} FieldBufferSlots;

/** One entry of the float-pair sequence. */
typedef struct FieldFloatPairEntry
{
    float unk00;
    float unk04;
} FieldFloatPairEntry;

/** Partial receiver containing float state and a sequence of float pairs. */
typedef struct FieldFloatSequenceState
{
    u8 unk00[0x90];
    float unk90;
    float unk94;
    float unk98;
    float unk9c;
    FieldFloatPairEntry* unka0;
    s32 unka4;
} FieldFloatSequenceState;

/** Partial receiver containing reset parameters and saved float values. */
typedef struct FieldFloatResetState
{
    u8 unk00[8];
    float unk08;
    float unk0c;
    u8 unk10[0xA];
    u16 unk1a;
    u16 unk1c;
    u8 unk1e[4];
    s16 unk22;
    u8 unk24[2];
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29[3];
    u32 unk2c;
    u8 unk30[4];
    float unk34;
    float unk38;
} FieldFloatResetState;

/** Partial target whose flag byte is at offset 0x4D. */
typedef struct FieldFlagTarget4D
{
    u8 unk00[0x4D];
    u8 unk4d_0_3 : 4;
    u8 unk4d_4 : 1;
    u8 unk4d_5_7 : 3;
} FieldFlagTarget4D;

/** Partial receiver with an optional flag target at offset 0x4C. */
typedef struct FieldFlagOwner4C
{
    u8 unk00[0x4C];
    FieldFlagTarget4D* unk4c;
} FieldFlagOwner4C;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set bit two of the flag byte at offset 0x70.
 * @param object Receiver to update.
 */
void func_002F2080(FieldByteFlags70* object);

/**
 * @brief Clear a word and halfword, and set three halfwords to minus one.
 * @param object Receiver to reset.
 */
void func_002F43F0(FieldResetState40* object);

/**
 * @brief Read the size of an indexed buffer slot.
 * @param object Receiver containing the slots.
 * @param index Slot index, from 0 through 2.
 * @return The stored buffer size.
 */
s32 func_002EBA80(const FieldBufferSlots* object, s32 index);

/**
 * @brief Read the aligned pointer of an indexed buffer slot.
 * @param object Receiver containing the slots.
 * @param index Slot index, from 0 through 2.
 * @return The stored aligned buffer pointer.
 */
void* func_002EBA90(const FieldBufferSlots* object, s32 index);

/**
 * @brief Store reset parameters, restore two floats, and clear transient state.
 * @param object Receiver to reset.
 * @param first Byte stored at offset 0x26.
 * @param second Byte stored at offset 0x27.
 * @param third Halfword stored at offset 0x1A.
 * @param fourth Halfword stored at offset 0x1C.
 */
void func_002E62E0(FieldFloatResetState* object, u8 first, u8 second, u16 third, u16 fourth);

/**
 * @brief Set bit four of the target flag byte when the target is present.
 * @param object Receiver containing the optional target.
 */
void func_002EA0E0(FieldFlagOwner4C* object);

/**
 * @brief Initialize float state and install a sequence of float pairs.
 * @param object Receiver to update.
 * @param values Sequence of float pairs.
 * @param count Number of entries.
 * @param first Initial float value and divisor.
 * @param second Float value used to calculate the ratio.
 */
void func_002F4550(FieldFloatSequenceState* object, FieldFloatPairEntry* values, s32 count, float first, float second);

#ifdef __cplusplus
}
#endif

#endif
