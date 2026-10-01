#ifndef SO3_OVERLAYS_1067_00_TEXT_002AE9E0_H
#define SO3_OVERLAYS_1067_00_TEXT_002AE9E0_H

#include "types.h"
#include "overlays/1067-00/text_001DD3C0.h"

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

/** Partial receiver containing sequence state at offset 0x10. */
typedef struct FieldSequenceState10
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x8];
    FieldSequenceTail state;
} FieldSequenceState10;

/** Partial receiver containing sequence state at offset 0x20. */
typedef struct FieldSequenceState20
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x18];
    FieldSequenceTail state;
} FieldSequenceState20;

/** Partial receiver containing sequence state at offset 0x40. */
typedef struct FieldSequenceState40
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x38];
    FieldSequenceTail state;
} FieldSequenceState40;

/** Partial reset receiver with two halfwords and two words at offset 0x10. */
typedef struct FieldResetState10
{
    u8 unk00[0x10];
    u16 unk10;
    u16 unk12;
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

/** Partial receiver containing sequence state at offset 0x30. */
typedef struct FieldSequenceState30
{
    u8 unk00[4];
    void* unk04;
    u8 unk08[0x28];
    FieldSequenceTail state;
} FieldSequenceState30;

/** Opaque common callback base with table D_154D50. */
typedef struct FieldObject154D50 FieldObject154D50;
#ifdef __cplusplus
/** Partial sequence receiver containing a vector at offset 0xA0. */
typedef struct FieldSequenceVectorA0
{
    u8 unk00[0xA0];
    FieldVec4A unkA0;
} FieldSequenceVectorA0;

/** Partial sequence receiver containing a vector at offset 0xC0. */
typedef struct FieldSequenceVectorC0
{
    u8 unk00[0xC0];
    FieldVec4A unkC0;
} FieldSequenceVectorC0;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear two halfwords and two words beginning at offset 0x10.
 * @param object Receiver containing the fields to reset.
 */
void func_002B7DA0(FieldResetState10* object);

/**
 * @brief Clear two halfwords and two words beginning at offset 0x10.
 * @param object Receiver containing the fields to reset.
 */
void func_002B7E00(FieldResetState10* object);

/**
 * @brief Clear two halfwords and two words beginning at offset 0x04.
 * @param object Receiver containing the fields to reset.
 */
void func_002B7E60(FieldResetState04* object);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002B83C0(FieldSequenceState20* object);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B84A0(FieldSequenceState20* object, u8 mode);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B8500(FieldSequenceState20* object, u8 mode);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002B8860(FieldSequenceState10* object);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B8990(FieldSequenceState10* object, u8 mode);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B89F0(FieldSequenceState10* object, u8 mode);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002B8C50(FieldSequenceState40* object);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B8D30(FieldSequenceState40* object, u8 mode);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002B8D90(FieldSequenceState40* object, u8 mode);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002BAC40(FieldSequenceState10* object, u8 mode);

/**
 * @brief Set the lower mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002BAD00(FieldSequenceState40* object, u8 mode);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002BAE90(FieldSequenceState40* object);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002BB020(FieldSequenceState40* object, u8 mode);

/**
 * @brief Reset the sequence fields and set both modes to one.
 * @param object Receiver containing the sequence state.
 */
void func_002BBA30(FieldSequenceState10* object);

/**
 * @brief Set the upper mode and record whether either mode equals four.
 * @param object Receiver containing the sequence state.
 * @param mode Mode value; only its low four bits are stored.
 */
void func_002BBBC0(FieldSequenceState10* object, u8 mode);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF510(FieldObject154D50* object);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF520(FieldObject154D50* object);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF530(FieldObject154D50* object);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF540(FieldObject154D50* object);

/**
 * @brief Return the default callback value.
 * @param object Callback receiver.
 * @return One.
 */
float func_002AF590(FieldObject154D50* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002B8070(FieldSequenceState30* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8080(FieldSequenceState30* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002B8100(FieldSequenceState30* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002B8560(FieldSequenceState20* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8570(FieldSequenceState20* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8580(FieldSequenceState20* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002B8790(FieldSequenceState20* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002B8A50(FieldSequenceState10* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8A60(FieldSequenceState10* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8A70(FieldSequenceState10* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002B8AC0(FieldSequenceState10* object);

/**
 * @brief Read the signed sequence word.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence word.
 */
s32 func_002B8DF0(FieldSequenceState40* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8E00(FieldSequenceState40* object);

/**
 * @brief Read the signed sequence halfword.
 * @param object Sequence receiver.
 * @return Current value of the signed sequence halfword.
 */
s16 func_002B8E10(FieldSequenceState40* object);

/**
 * @brief Read the sequence record pointer.
 * @param object Sequence receiver.
 * @return Current value of the sequence record pointer.
 */
void* func_002B9080(FieldSequenceState40* object);


#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002B0B20(FieldClass150070* object);

/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 14.
 */
s32 func_002B4030(FieldClass150070* object);

/**
 * @brief Copy the receiver's vector to the output.
 * @param object Sequence receiver.
 * @param output Destination vector.
 */
void func_002B7440(FieldSequenceVectorA0* object, FieldVec4B* output);

/**
 * @brief Copy the receiver's vector to the output.
 * @param object Sequence receiver.
 * @param output Destination vector.
 */
void func_002B7C80(FieldSequenceVectorC0* object, FieldVec4B* output);

#endif

#ifdef __cplusplus
}
#endif

#endif
