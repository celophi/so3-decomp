#ifndef SO3_OVERLAYS_1070_00_TEXT_001E2B40_H
#define SO3_OVERLAYS_1070_00_TEXT_001E2B40_H

#include "overlays/1070-00/text_00284BF0.h"

/** Partial receiver used by the connected byte-dimension and float-pair setters. */
typedef struct FieldDimensionState
{
    u8 unk00[0xF0];
    u8 unkf0;
    u8 unkf1;
    u8 unkf2[10];
    float unkfc;
    float unk100;
    u8 unk104[8];
    u16 unk10c;
} FieldDimensionState;

/** Partial receiver whose state byte is at offset 0xAD. */
typedef struct FieldByteStateAD
{
    u8 unk00[0xAD];
    u8 unkad;
} FieldByteStateAD;

/** Partial receiver whose unsigned halfword is at offset 0x94. */
typedef struct FieldHalfwordState94
{
    u8 unk00[0x94];
    u16 unk94;
} FieldHalfwordState94;

/** Leading word and signed time components used by the time-state helpers. */
typedef struct FieldTimeState
{
    u32 unk00;
    s16 hours;
    s16 minutes;
    s16 seconds;
} FieldTimeState;

/** Partial keyed list element containing float state and a flag byte. */
typedef struct FieldKeyedFlagElement28
{
    FieldListNode link;
    u8 unk0c[0x10];
    float unk1c;
    u32 unk20;
    float unk24;
    u32 unk28;
    u8 unk2c_0 : 1;
    u8 unk2c_1_7 : 7;
} FieldKeyedFlagElement28;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the adjacent floating-point values at offsets 0xFC and 0x100.
 * @param object Receiver to update.
 * @param first Value for offset 0xFC.
 * @param second Value for offset 0x100.
 */
void func_001ED580(FieldDimensionState* object, float first, float second);

/**
 * @brief Store two byte dimensions and their product minus one.
 * @param object Receiver to update.
 * @param first Value whose low byte supplies the first dimension.
 * @param second Value whose low byte supplies the second dimension.
 */
void func_001ED5A0(FieldDimensionState* object, s32 first, s32 second);

/**
 * @brief Set the state byte at offset 0xAD.
 * @param object Receiver to update.
 * @param value Byte to store.
 */
void func_001ED5C0(FieldByteStateAD* object, u8 value);

/**
 * @brief Read the unsigned halfword at offset 0x94.
 * @param object Receiver to inspect.
 * @return The stored halfword.
 */
u16 func_001EB720(const FieldHalfwordState94* object);

/**
 * @brief Convert the stored hours, minutes and seconds to seconds.
 * @param object Time state to read.
 * @return Total seconds represented by the stored components.
 */
s32 func_001EDBD0(const FieldTimeState* object);

/**
 * @brief Set the leading word of the time state.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_001EDC10(FieldTimeState* object, u32 value);

/**
 * @brief Split seconds into time components, clamping to 999 hours, 59 minutes, 59 seconds.
 * @param object Time state to update; zero seconds also clears its leading word.
 * @param seconds Total seconds to split.
 */
void func_001EDC20(FieldTimeState* object, u32 seconds);

/**
 * @brief Clear the float and word state, store an integer as a float, and set flag bit zero.
 * @param object List element to update.
 * @param value Signed value to convert and store.
 */
void func_001E7020(FieldKeyedFlagElement28* object, s32 value);

#ifdef __cplusplus
}
#endif

#endif
