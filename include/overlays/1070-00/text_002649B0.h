#ifndef SO3_OVERLAYS_1070_00_TEXT_002649B0_H
#define SO3_OVERLAYS_1070_00_TEXT_002649B0_H

#include "overlays/1070-00/text_00254730.h"

/** Partial receiver containing a scalar interpolation state. */
typedef struct FieldFloatTransition330
{
    u8 unk00[0x330];
    float unk330;
    float unk334;
    float unk338;
    float unk33c;
} FieldFloatTransition330;

/** Partial owner of a keyed float state and its packed key. */
typedef struct FieldKeyedFloatOwner3A0
{
    u8 unk00[0x3A0];
    FieldKeyedFloatState98* unk3a0;
    float unk3a4;
    u8 unk3a8[4];
    u32 unk3ac;
    u8 unk3b0[0xB];
    u8 unk3bb_0_1 : 2;
    u8 unk3bb_2 : 1;
    u8 unk3bb_3_7 : 5;
} FieldKeyedFloatOwner3A0;

/** Partial receiver combining an owner key with two key fragments. */
typedef struct FieldPackedKeySource
{
    u8 unk00[8];
    FieldKeyedFloatOwner3A0* unk08;
    u16* unk0c;
    u8 unk10[4];
    u32 unk14;
} FieldPackedKeySource;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Combine the owner key with the halfword and word key fragments.
 * @param object Receiver containing the owner and key fragments.
 * @return The combined packed key.
 */
u32 func_0026F810(FieldPackedKeySource* object);

/**
 * @brief Clear the owner scalar and reset the attached keyed float state.
 * @param object Owner containing the optional keyed float state.
 */
void func_0026FB50(FieldKeyedFloatOwner3A0* object);

/**
 * @brief Set a scalar immediately or configure its linear transition.
 * @param object Receiver containing the scalar transition state.
 * @param value Target scalar value.
 * @param duration Transition interval; zero updates immediately.
 */
void func_00273EA0(FieldFloatTransition330* object, float value, float duration);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002662C0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00267510(void* object);

/**
 * @brief Clear the receiver word at offset 0x28.
 * @param object Receiver to update.
 */
void func_00267520(void* object);

/**
 * @brief Return the floating-point value 2500.0.
 * @param object Receiver to update.
 * @return 2500.0f.
 */
float func_00267530(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00267550(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_002677E0(void* object);

/**
 * @brief Clear the receiver word at offset 0x28.
 * @param object Receiver to update.
 */
void func_002677F0(void* object);

/**
 * @brief Return the floating-point value 2500.0.
 * @param object Receiver to update.
 * @return 2500.0f.
 */
float func_00267800(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00267820(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_002679D0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00267AB0(void* object);

/**
 * @brief Clear the receiver word at offset 0x28.
 * @param object Receiver to update.
 */
void func_00267AC0(void* object);

/**
 * @brief Return the floating-point value 2500.0.
 * @param object Receiver to update.
 * @return 2500.0f.
 */
float func_00267AD0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00267AF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00267DF0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00267E80(void* object);

/**
 * @brief Clear the receiver word at offset 0x28.
 * @param object Receiver to update.
 */
void func_00267E90(void* object);

/**
 * @brief Return the floating-point value 2500.0.
 * @param object Receiver to update.
 * @return 2500.0f.
 */
float func_00267EA0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00267EC0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00268110(void* object);

/**
 * @brief Clear the receiver word at offset 0x28.
 * @param object Receiver to update.
 */
void func_00268120(void* object);

/**
 * @brief Return the floating-point value 2500.0.
 * @param object Receiver to update.
 * @return 2500.0f.
 */
float func_00268130(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00268150(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269630(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269640(void* object);

/**
 * @brief Return the floating-point value 100.0.
 * @param object Receiver or first argument; unused.
 * @return 100.0f.
 */
float func_00269650(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269660(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269670(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269680(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002696A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002696B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002696C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002696D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002696E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002696F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269700(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269710(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269720(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269730(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269740(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269750(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269760(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269770(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269780(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269790(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_002697A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002697B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002697C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002697D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002697E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002697F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269800(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00269810(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269820(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269830(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269840(void* object);

/**
 * @brief Return the floating-point value 100.0.
 * @param object Receiver or first argument; unused.
 * @return 100.0f.
 */
float func_00269850(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269860(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269870(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269880(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269890(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002698A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002698B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002698C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002698D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002698E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002698F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269900(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269910(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269920(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269930(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269940(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269950(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269960(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269970(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269980(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269990(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_002699A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002699B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002699C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002699D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002699E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002699F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269A00(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00269A10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269A20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269A30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269A40(void* object);

/**
 * @brief Return the floating-point value 100.0.
 * @param object Receiver or first argument; unused.
 * @return 100.0f.
 */
float func_00269A50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269A60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269A70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269A80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269A90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269AA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269AB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269AC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269AD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269AE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269AF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269B00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269B10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269B20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269B30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269B40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269B50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269B60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269B70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269B80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269B90(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00269BA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269BB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269BC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269BD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269BE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269BF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269C00(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00269C10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269C20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269C30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269C40(void* object);

/**
 * @brief Return the floating-point value 100.0.
 * @param object Receiver or first argument; unused.
 * @return 100.0f.
 */
float func_00269C50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269C60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269C70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269C80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269C90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269CA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269CB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269CC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269CD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269CE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269CF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269D00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269D10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269D20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269D30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269D40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269D50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269D60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269D70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269D80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269D90(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00269DA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269DB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269DC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269DD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269DE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269DF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269E00(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00269E10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269E20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269E30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269E40(void* object);

/**
 * @brief Return the floating-point value 100.0.
 * @param object Receiver or first argument; unused.
 * @return 100.0f.
 */
float func_00269E50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269E60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269E70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269E80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269E90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269EA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269EB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269EC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269ED0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269EE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269EF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269F00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269F10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269F20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269F30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269F40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269F50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269F60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269F70(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269F80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269F90(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00269FA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269FB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269FC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269FD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00269FE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00269FF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A000(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_0026A010(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A020(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0026A030(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A040(void* object);

/**
 * @brief Return the floating-point value 100.0.
 * @param object Receiver or first argument; unused.
 * @return 100.0f.
 */
float func_0026A050(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A060(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A070(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A080(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A090(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A0A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A0B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0026A0C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A0D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A0E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A0F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0026A100(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A110(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A120(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A130(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A140(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A150(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0026A160(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A170(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0026A180(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A190(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_0026A1A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A1B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A1C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0026A1D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A1E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0026A1F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A200(void* object);

/**
 * @brief Return the floating-point value 0.0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_0026A210(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026A220(void* object);

/**
 * @brief Return the table entry at an offset of 0x80 bytes per index.
 * @param object Receiver to inspect.
 * @param index Table entry index.
 * @return Address of the selected table entry.
 */
void* func_0026A290(const void* object, u32 index);

/**
 * @brief Read the word at receiver offset 0x1C.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A2C0(const void* object);

/**
 * @brief Read the word at receiver offset 0xC.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A2D0(const void* object);

/**
 * @brief Read the word at receiver offset 0x10.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A2E0(const void* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver or first argument; unused.
 * @return Always 32.
 */
s32 func_0026A2F0(void* object);

/**
 * @brief Test whether the word at receiver offset 0x14 is nonzero.
 * @param object Receiver to inspect.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_0026A300(const void* object);

/**
 * @brief Return the indexed table entry at 80-byte intervals.
 * @param object Receiver containing the table base at offset 0x14.
 * @param index Table entry index.
 * @return Address of the selected table entry.
 */
void* func_0026A3B0(const void* object, u32 index);

/**
 * @brief Read the word at receiver offset 0x1C.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A3F0(const void* object);

/**
 * @brief Read the word at receiver offset 0xC.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A400(const void* object);

/**
 * @brief Read the word at receiver offset 0x10.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A410(const void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0026A420(void* object);

/**
 * @brief Test whether the word at receiver offset 0x14 is nonzero.
 * @param object Receiver to inspect.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_0026A430(const void* object);

/**
 * @brief Return the indexed table entry at 112-byte intervals.
 * @param object Receiver containing the table base at offset 0x14.
 * @param index Table entry index.
 * @return Address of the selected table entry.
 */
void* func_0026A4E0(const void* object, u32 index);

/**
 * @brief Read the word at receiver offset 0x1C.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A520(const void* object);

/**
 * @brief Read the word at receiver offset 0xC.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A530(const void* object);

/**
 * @brief Read the word at receiver offset 0x10.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A540(const void* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver or first argument; unused.
 * @return Always 32.
 */
s32 func_0026A550(void* object);

/**
 * @brief Test whether the word at receiver offset 0x14 is nonzero.
 * @param object Receiver to inspect.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_0026A560(const void* object);

/**
 * @brief Return the table entry at an offset of 0x80 bytes per index.
 * @param object Receiver to inspect.
 * @param index Table entry index.
 * @return Address of the selected table entry.
 */
void* func_0026A610(const void* object, u32 index);

/**
 * @brief Read the word at receiver offset 0x1C.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A640(const void* object);

/**
 * @brief Read the word at receiver offset 0xC.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A650(const void* object);

/**
 * @brief Read the word at receiver offset 0x10.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A660(const void* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver or first argument; unused.
 * @return Always 32.
 */
s32 func_0026A670(void* object);

/**
 * @brief Test whether the word at receiver offset 0x14 is nonzero.
 * @param object Receiver to inspect.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_0026A680(const void* object);

/**
 * @brief Return the indexed table entry at 96-byte intervals.
 * @param object Receiver containing the table base at offset 0x14.
 * @param index Table entry index.
 * @return Address of the selected table entry.
 */
void* func_0026A730(const void* object, u32 index);

/**
 * @brief Read the word at receiver offset 0x1C.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A770(const void* object);

/**
 * @brief Read the word at receiver offset 0xC.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A780(const void* object);

/**
 * @brief Read the word at receiver offset 0x10.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A790(const void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0026A7A0(void* object);

/**
 * @brief Test whether the word at receiver offset 0x14 is nonzero.
 * @param object Receiver to inspect.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_0026A7B0(const void* object);

/**
 * @brief Return the table entry at an offset of 0x80 bytes per index.
 * @param object Receiver to inspect.
 * @param index Table entry index.
 * @return Address of the selected table entry.
 */
void* func_0026A860(const void* object, u32 index);

/**
 * @brief Read the word at receiver offset 0x1C.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A890(const void* object);

/**
 * @brief Read the word at receiver offset 0xC.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A8A0(const void* object);

/**
 * @brief Read the word at receiver offset 0x10.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0026A8B0(const void* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver or first argument; unused.
 * @return Always 32.
 */
s32 func_0026A8C0(void* object);

/**
 * @brief Test whether the word at receiver offset 0x14 is nonzero.
 * @param object Receiver to inspect.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_0026A8D0(const void* object);

/**
 * @brief Return the floating-point value 1.0.
 * @param object Receiver or first argument; unused.
 * @return 1.0f.
 */
float func_0026D3D0(void* object);

/**
 * @brief Return the floating-point value 1.0.
 * @param object Receiver or first argument; unused.
 * @return 1.0f.
 */
float func_0026D3E0(void* object);

/**
 * @brief Return the floating-point value 1.0.
 * @param object Receiver or first argument; unused.
 * @return 1.0f.
 */
float func_0026D3F0(void* object);

/**
 * @brief Return the floating-point value 1.0.
 * @param object Receiver or first argument; unused.
 * @return 1.0f.
 */
float func_0026D400(void* object);

/**
 * @brief Return the floating-point value 1.0.
 * @param object Receiver or first argument; unused.
 * @return 1.0f.
 */
float func_0026D410(void* object);

/**
 * @brief Return the floating-point value 1.0.
 * @param object Receiver or first argument; unused.
 * @return 1.0f.
 */
float func_0026D420(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0026D5F0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0026D9B0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0026D9C0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0026D9D0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_0026E770(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_0026F460(void* object);

/**
 * @brief Clear the receiver word at offset 0x28.
 * @param object Receiver to update.
 */
void func_0026F470(void* object);

/**
 * @brief Return the floating-point value 2500.0.
 * @param object Receiver or first argument; unused.
 * @return 2500.0f.
 */
float func_0026F480(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0026F4A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0026F690(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00274720(void* object);

/**
 * @brief Clear the receiver word at offset 0x28.
 * @param object Receiver to update.
 */
void func_00274730(void* object);

/**
 * @brief Return the floating-point value 2500.0.
 * @param object Receiver or first argument; unused.
 * @return 2500.0f.
 */
float func_00274740(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00274760(void* object);

#ifdef __cplusplus
}
#endif

#endif
