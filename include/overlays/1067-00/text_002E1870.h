#ifndef SO3_OVERLAYS_1067_00_TEXT_002E1870_H
#define SO3_OVERLAYS_1067_00_TEXT_002E1870_H

#include "types.h"

/** Partial receiver containing encoded values and their check words. */
typedef struct FieldCheckedWordsState1870
{
    u8 unk00[0x34];
    u32 unk34;
    u32 unk38;
    u32 unk3C;
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u32 unk4C;
    u32 unk50;
    u32 unk54;
    u32 unk58;
    u32 unk5C;
    u32 unk60;
    u8 unk64[8];
    u32 unk6C;
    u8 unk70[0x24];
    u32 unk94;
    u32 unk98;
    u32 unk9C;
    u32 unkA0;
    u8 unkA4[4];
    u32 unkA8;
} FieldCheckedWordsState1870;

/** Partial receiver whose constructor installs the table at 0x0015B9A0. */
typedef struct FieldObject15B9A0
{
    u8 unk00[0x5C];
    u8 unk5C[2];
    s16 unk5E[2];
    u8 unk62[2];
    s16 unk64;
    u8 unk66[2];
    u8 unk68;
    u8 unk69[0x17];
    u32 unk80;
    u32 unk84;
} FieldObject15B9A0;

typedef struct FieldOuter14 FieldOuter14;

typedef struct FieldTransferDescriptor2EDFD0 FieldTransferDescriptor2EDFD0;

/** Transfer record initialized by func_002EEC90. */
typedef struct FieldTransfer2EDFD0
{
    char* name;
    u32 unk04;
    u32 unk08;
    FieldTransferDescriptor2EDFD0* descriptor;
} FieldTransfer2EDFD0;

/** Partial receiver containing a transfer record and selection state. */
typedef struct FieldObject2EDFD0
{
    u8 unk00[0xFF8];
    FieldTransfer2EDFD0 unkFF8;
    u8 unk1008[0x48];
    u16 unk1050;
    u8 unk1052[6];
    s16 unk1058;
    s16 unk105A;
    u8 unk105C[2];
    s16 unk105E;
    u8 unk1060;
    u8 unk1061[0x1BD];
    u8 unk121E;
    u8 unk121F[0x35];
    void* unk1254;
} FieldObject2EDFD0;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the receiver's unsigned halfword at offset 0x1050.
 * @param object Receiver containing the halfword.
 * @return Stored halfword.
 */
u16 func_002EE9B0(const FieldObject2EDFD0* object);

/**
 * @brief Store a nonnull pointer in the receiver.
 * @param object Receiver containing the pointer field at offset 0x1254.
 * @param value Pointer to store.
 * @return One if stored, or zero when value is null.
 */
s32 func_002EE9C0(FieldObject2EDFD0* object, void* value);

/**
 * @brief Decode the value stored in unk50 after validating its check word.
 * @param object Encoded values and check words.
 * @return Decoded signed value, or zero if validation fails.
 */
s32 func_002E7EF0(const FieldCheckedWordsState1870* object);

/**
 * @brief Decode the value stored in unk60 after validating its check word.
 * @param object Encoded values and check words.
 * @return Decoded signed value, or zero if validation fails.
 */
s32 func_002E80A0(const FieldCheckedWordsState1870* object);

/**
 * @brief Decode the value stored in unk48 after validating its check word.
 * @param object Encoded values and check words.
 * @return Decoded signed value, or zero if validation fails.
 */
s32 func_002E8270(const FieldCheckedWordsState1870* object);

/**
 * @brief Decode the value stored in unk6C after validating its check word.
 * @param object Encoded values and check words.
 * @return Decoded signed value, or zero if validation fails.
 */
s32 func_002E8440(const FieldCheckedWordsState1870* object);

/**
 * @brief Decode the value stored in unk3C after validating its check word.
 * @param object Encoded values and check words.
 * @return Decoded signed value, or zero if validation fails.
 */
s32 func_002E8600(const FieldCheckedWordsState1870* object);

/**
 * @brief Select a halfword slot and clear the receiver's related state.
 * @param object Receiver containing the indexed state.
 * @param index Slot to select.
 */
void func_002ECFA0(FieldObject15B9A0* object, s16 index);

/**
 * @brief Report which of two attached status words equal two.
 * @param object Receiver with the nested status object.
 * @return Bit 0 for the first word and bit 1 for the second, or zero when inactive.
 */
u16 func_002ECFE0(const FieldOuter14* object);

/**
 * @brief Return the receiver's fixed type code.
 * @param object Receiver; unused.
 * @return Type code 4.
 */
s32 func_002ECF70(FieldObject15B9A0* object);

/**
 * @brief Read the receiver's state byte.
 * @param object Receiver containing the state.
 * @return Value stored in unk68.
 */
u8 func_002ECF80(FieldObject15B9A0* object);

/**
 * @brief Read one of the receiver's two signed halfword values.
 * @param object Receiver containing the values.
 * @param index Element index; no bounds check is performed.
 * @return Selected signed halfword.
 */
s16 func_002ECF90(FieldObject15B9A0* object, s32 index);

/**
 * @brief Read the receiver's byte at offset 0x121E.
 * @param object Receiver containing the byte.
 * @return Stored byte.
 */
u8 func_002EED90(const FieldObject2EDFD0* object);

/**
 * @brief Get an indexed 24-byte record in resource section four.
 * @param object Receiver; unused.
 * @param index One-based record index.
 * @return Address of the indexed record.
 */
void* func_002EEE30(void* object, s32 index);

/**
 * @brief Store the halfword and byte state values.
 * @param object State receiver.
 * @param value Value to store in unk105E.
 * @param flag Value to store in unk1060.
 */
void func_002EEE20(FieldObject2EDFD0* object, s16 value, u8 flag);

/**
 * @brief Get the embedded transfer record.
 * @param object Receiver containing the record.
 * @return Address of the transfer record.
 */
FieldTransfer2EDFD0* func_002EF000(FieldObject2EDFD0* object);

/**
 * @brief Store the selection limit without clamping it.
 * @param object State receiver.
 * @param value New selection limit.
 */
void func_002EF010(FieldObject2EDFD0* object, s16 value);

/**
 * @brief Select an index within the stored inclusive limit.
 * @param object State receiver.
 * @param index Requested index.
 * @return One if selected, or zero if outside the range.
 */
s32 func_002EF030(FieldObject2EDFD0* object, s16 index);

#ifdef __cplusplus
}
#endif

#endif
