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

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D7A90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D7AA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D7AB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D7AC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D8360(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D83A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D83E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D8420(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D8520(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D8560(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D85A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D85E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D8900(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D8940(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D8980(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D89C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D9B80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D9B90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D9BA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D9DF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D9E30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002D9E70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D9EB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DA540(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DA580(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DA5C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DA600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DA9C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DAA00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DAA40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DAA80(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_002DB010(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002DB050(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DB250(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DBA10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBA20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBA40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBA50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBA60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBA70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBA80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBA90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DBAA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBAB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBAC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBAD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DBAE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBAF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBB00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBB10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBB20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBB30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DBB40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBB50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DBB60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBB70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBB90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBBA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DBBB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBBC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002DBBD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBBE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002DBC00(void* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver or first argument; unused.
 * @return Always 32.
 */
s32 func_002DBCE0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_002E2E60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E2E80(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002E2EB0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_002E3220(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002E3990(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E39A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E39C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E39D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E39E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E39F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3A00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3A10(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002E3A20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3A30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3A40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3A50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002E3A60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3A70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3A80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3A90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3AA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3AB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002E3AC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3AD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002E3AE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3AF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3B10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3B20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002E3B30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3B40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002E3B50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3B60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002E3B80(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002E3C50(void* object);

#ifdef __cplusplus
}
#endif

#endif
