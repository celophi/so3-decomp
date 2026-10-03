#ifndef SO3_OVERLAYS_1070_00_TEXT_001E2B40_H
#define SO3_OVERLAYS_1070_00_TEXT_001E2B40_H

#include "overlays/1070-00/text_00284BF0.h"

/** Partial receiver with an aligned value at 0x30 and a byte at 0x50. */
typedef struct FieldCopy79A0
{
    u8 unk00[0x30];
    unsigned __int128 unk30;
    u8 unk40[0x10];
    u8 unk50;
} FieldCopy79A0;

/** Partial receiver whose value at 0x40 is copied by func_001E7A60. */
typedef struct FieldCopy7A60
{
    u8 unk00[0x40];
    unsigned __int128 unk40;
    u8 unk50;
} FieldCopy7A60;

/** Partial receiver whose value at 0x40 is copied by func_001E7A80. */
typedef struct FieldCopy7A80
{
    u8 unk00[0x40];
    unsigned __int128 unk40;
    u8 unk50;
} FieldCopy7A80;

/** Partial receiver with three float values at 0x40 and a byte at 0x50. */
typedef struct FieldFloatUpdate7AA0
{
    u8 unk00[0x40];
    float unk40;
    float unk44;
    float unk48;
    u8 unk4c[4];
    u8 unk50;
} FieldFloatUpdate7AA0;

/** Partial receiver with an aligned value at 0x20 and a byte at 0x50. */
typedef struct FieldCopy7920
{
    u8 unk00[0x20];
    unsigned __int128 unk20;
    u8 unk30[0x20];
    u8 unk50;
} FieldCopy7920;

/** Partial receiver with four float values at 0x20 and a byte at 0x50. */
typedef struct FieldFloatUpdate7940
{
    u8 unk00[0x20];
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    u8 unk30[0x20];
    u8 unk50;
} FieldFloatUpdate7940;

/** Partial receiver with four float values at 0x30 and a byte at 0x50. */
typedef struct FieldFloatUpdate7960
{
    u8 unk00[0x30];
    float unk30;
    float unk34;
    float unk38;
    float unk3c;
    u8 unk40[0x10];
    u8 unk50;
} FieldFloatUpdate7960;

/** Partial receiver with an aligned value at 0x30 and a byte at 0x50. */
typedef struct FieldCopy7980
{
    u8 unk00[0x30];
    unsigned __int128 unk30;
    u8 unk40[0x10];
    u8 unk50;
} FieldCopy7980;

/** Partial receiver with a value byte at 0x210 and flag byte at 0x59D. */
typedef struct FieldByteFlagState210
{
    u8 unk00[0x210];
    u8 unk210;
    u8 unk211[0x38C];
    u8 unk59d_0_2 : 3;
    u8 unk59d_3 : 1;
    u8 unk59d_4_7 : 4;
} FieldByteFlagState210;

/** Partial receiver whose word is stored by func_001E6D60. */
typedef struct FieldWordState70
{
    u8 unk00[0x70];
    u32 unk70;
} FieldWordState70;

/** Partial receiver whose word is tested by func_001E7830. */
typedef struct FieldWordState704
{
    u8 unk00[0x704];
    u32 unk704;
} FieldWordState704;

/** Partial receiver whose unsigned byte is read by func_001E7850. */
typedef struct FieldByteState794
{
    u8 unk00[0x794];
    u8 unk794;
} FieldByteState794;

/** Partial receiver whose word is stored by func_001E2F20. */
typedef struct FieldWordStateD4
{
    u8 unk00[0xD4];
    u32 unkd4;
} FieldWordStateD4;

/** Partial receiver whose unsigned byte is read by func_001E3660. */
typedef struct FieldByteState14
{
    u8 unk00[0x14];
    u8 unk14;
} FieldByteState14;

/** Partial receiver whose aligned value is copied by func_001E2C40. */
typedef struct FieldCopy2C40
{
    u8 unk00[0x20];
    unsigned __int128 unk20;
} FieldCopy2C40;

/** Partial receiver whose aligned value is copied by func_001E5000. */
typedef struct FieldCopy5000
{
    u8 unk00[0x20];
    unsigned __int128 unk20;
} FieldCopy5000;

/** Partial receiver whose aligned value is copied by func_001E5010. */
typedef struct FieldCopy5010
{
    u8 unk00[0x20];
    unsigned __int128 unk20;
} FieldCopy5010;

/** Partial receiver with an aligned value and an update byte at offset 0x50. */
typedef struct FieldCopy5750
{
    u8 unk00[0x20];
    unsigned __int128 unk20;
    u8 unk30[0x20];
    u8 unk50;
} FieldCopy5750;

/** Partial receiver containing four adjacent floating-point values. */
typedef struct FieldFloatValues20
{
    u8 unk00[0x20];
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
} FieldFloatValues20;

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
 * @brief Set the byte at 0x50 to one and copy an aligned 16-byte value to 0x30.
 * @param object Receiver containing the byte and destination value.
 * @param source Aligned value loaded after the byte is stored.
 */
void func_001E79A0(FieldCopy79A0* object, const unsigned __int128* source);

/**
 * @brief Set the byte at 0x50 to one and copy an aligned 16-byte value to 0x40.
 * @param object Receiver containing the byte and destination value.
 * @param source Aligned value loaded after the byte is stored.
 */
void func_001E7A60(FieldCopy7A60* object, const unsigned __int128* source);

/**
 * @brief Set the byte at 0x50 to one and copy an aligned 16-byte value to 0x40.
 * @param object Receiver containing the byte and destination value.
 * @param source Aligned value loaded after the byte is stored.
 */
void func_001E7A80(FieldCopy7A80* object, const unsigned __int128* source);

/**
 * @brief Set the byte at 0x50 to one and store three adjacent floats at 0x40.
 * @param object Receiver containing the byte and destination float values.
 * @param first Value to store at 0x40.
 * @param second Value to store at 0x44.
 * @param third Value to store at 0x48.
 */
void func_001E7AA0(FieldFloatUpdate7AA0* object, float first, float second, float third);

/**
 * @brief Set the byte at 0x50 to one and copy an aligned 16-byte value to 0x20.
 * @param object Receiver containing the byte and destination value.
 * @param source Aligned value loaded after the byte is stored.
 */
void func_001E7920(FieldCopy7920* object, const unsigned __int128* source);

/**
 * @brief Set the byte at 0x50 to one and store three floats followed by one.
 * @param object Receiver containing the byte and destination float values.
 * @param first Value to store at 0x20.
 * @param second Value to store at 0x24.
 * @param third Value to store at 0x28.
 */
void func_001E7940(FieldFloatUpdate7940* object, float first, float second, float third);

/**
 * @brief Set the byte at 0x50 to one and store four adjacent floats at 0x30.
 * @param object Receiver containing the byte and destination float values.
 * @param first Value to store at 0x30.
 * @param second Value to store at 0x34.
 * @param third Value to store at 0x38.
 * @param fourth Value to store at 0x3C.
 */
void func_001E7960(FieldFloatUpdate7960* object, float first, float second, float third, float fourth);

/**
 * @brief Set the byte at 0x50 to one and copy an aligned 16-byte value to 0x30.
 * @param object Receiver containing the byte and destination value.
 * @param source Aligned value loaded after the byte is stored.
 */
void func_001E7980(FieldCopy7980* object, const unsigned __int128* source);

/**
 * @brief Store a byte at offset 0x210 and set bit 3 of the byte at 0x59D.
 * @param object Receiver containing the value and flag bytes.
 * @param value Value whose low byte is stored.
 */
void func_001E7870(FieldByteFlagState210* object, u32 value);

/**
 * @brief Return the address at offset 0x90.
 * @param object Base address of the receiver.
 * @return The address at offset 0x90.
 */
void* func_001E78E0(void* object);

/**
 * @brief Return the address at offset 0x1D0.
 * @param object Base address of the receiver.
 * @return The address at offset 0x1D0.
 */
void* func_001E78F0(void* object);

/**
 * @brief Return the address at offset 0x1E0.
 * @param object Base address of the receiver.
 * @return The address at offset 0x1E0.
 */
void* func_001E7900(void* object);

/**
 * @brief Return the address at offset 0x1F0.
 * @param object Base address of the receiver.
 * @return The address at offset 0x1F0.
 */
void* func_001E7910(void* object);

/**
 * @brief Store a word at offset 0x70.
 * @param object Receiver containing the destination word.
 * @param value Word to store.
 */
void func_001E6D60(FieldWordState70* object, u32 value);

/**
 * @brief Test whether the word at offset 0x704 is nonzero.
 * @param object Receiver containing the word.
 * @return One if the word is nonzero, otherwise zero.
 */
s32 func_001E7830(const FieldWordState704* object);

/**
 * @brief Return the address at offset 0x79C.
 * @param object Base address of the receiver.
 * @return The address at offset 0x79C.
 */
void* func_001E7840(void* object);

/**
 * @brief Read the unsigned byte at offset 0x794.
 * @param object Receiver containing the byte.
 * @return The byte value.
 */
u8 func_001E7850(const FieldByteState794* object);

/**
 * @brief Store a word at offset 0xD4.
 * @param object Receiver containing the destination word.
 * @param value Word to store.
 */
void func_001E2F20(FieldWordStateD4* object, u32 value);

/**
 * @brief Read the unsigned byte at offset 0x14.
 * @param object Receiver containing the byte.
 * @return The byte value.
 */
u8 func_001E3660(const FieldByteState14* object);

/**
 * @brief Return the address at offset 0x90.
 * @param object Base address of the receiver.
 * @return The address at offset 0x90.
 */
void* func_001E4540(void* object);

/**
 * @brief Copy an aligned 16-byte value to two destinations.
 * @param first Aligned destination written after second.
 * @param second Aligned destination written first.
 * @param source Aligned value loaded before either destination is written.
 */
void func_001E4A00(unsigned __int128* first, unsigned __int128* second, const unsigned __int128* source);

/**
 * @brief Copy an aligned 16-byte value to offset 0x20.
 * @param object Receiver containing the aligned destination value.
 * @param source Aligned value to copy.
 */
void func_001E2C40(FieldCopy2C40* object, const unsigned __int128* source);

/**
 * @brief Copy an aligned 16-byte value to offset 0x20.
 * @param object Receiver containing the aligned destination value.
 * @param source Aligned value to copy.
 */
void func_001E5000(FieldCopy5000* object, const unsigned __int128* source);

/**
 * @brief Copy an aligned 16-byte value to offset 0x20.
 * @param object Receiver containing the aligned destination value.
 * @param source Aligned value to copy.
 */
void func_001E5010(FieldCopy5010* object, const unsigned __int128* source);

/**
 * @brief Set the update byte to one and copy an aligned 16-byte value.
 * @param object Receiver containing the update byte and destination value.
 * @param source Aligned value to copy.
 */
void func_001E5750(FieldCopy5750* object, const unsigned __int128* source);

/**
 * @brief Store three floating-point values and set the following value to one.
 * @param object Receiver whose values are initialized.
 * @param first Value to store at offset 0x20.
 * @param second Value to store at offset 0x24.
 * @param third Value to store at offset 0x28.
 */
void func_001E5020(FieldFloatValues20* object, float first, float second, float third);

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

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_001E2C20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E2C30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E2C50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E2D20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E2D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E2DD0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_001E3090(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E30D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E4440(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_001E4450(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E4490(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E5040(void* object);

/**
 * @brief Return the fixed value 8.
 * @param object Receiver or first argument; unused.
 * @return Always 8.
 */
s32 func_001E5070(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_001E6D10(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_001E6D20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E6D70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E7480(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E77E0(void* object);

/**
 * @brief Return the fixed value 11.
 * @param object Receiver or first argument; unused.
 * @return Always 11.
 */
s32 func_001E77F0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_001E7800(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E7810(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E7820(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E7860(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E96B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E96C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E9AE0(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_001E9AF0(void* object);

/**
 * @brief Return the fixed value 16.
 * @param object Receiver or first argument; unused.
 * @return Always 16.
 */
s32 func_001EB5A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EB5E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EDA10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EDA20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EDA60(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EDA70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EDA80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EDA90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EDB10(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_001EDB30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EE1F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EE200(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EE240(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EE270(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EE280(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EE290(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EE2A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EE2B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EE2C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EE3D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EE490(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEE20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEE30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEE40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEE50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEE60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEE70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEE80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEE90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEEA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEEB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEEC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEED0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEEE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEEF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEF00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEF10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEF20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEF30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEF40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EEF50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEF60(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEF70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEF80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEF90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEFA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEFB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEFC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEFD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEFE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001EEFF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EF000(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EF010(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EF040(void* object);

#ifdef __cplusplus
}
#endif

#endif
