#ifndef SO3_OVERLAYS_1070_00_TEXT_00202FB0_H
#define SO3_OVERLAYS_1070_00_TEXT_00202FB0_H

#include "overlays/1070-00/text_00284BF0.h"

/** Partial element in the context-0x58 circular list. */
typedef struct FieldFlagListElement
{
    FieldListNode link;
    u8 unk0c[8];
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u8 unk20[4];
    s32 unk24;
    s32 unk28;
    s32 unk2c;
    s32 unk30;
    s32 unk34;
    u32 unk38;
    u32 unk3c;
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u8 unk4c_0 : 1;
    u8 unk4c_1 : 1;
    u8 unk4c_2 : 1;
    u8 unk4c_3 : 1;
    u8 unk4c_4 : 1;
    u8 unk4c_5_7 : 3;
} FieldFlagListElement;

/** Partial list element with an additional flag byte at offset 0x6D. */
typedef struct FieldFlagElement6D
{
    FieldFlagListElement base;
    u8 unk50[0x1D];
    u8 unk6d_0 : 1;
    u8 unk6d_1 : 1;
    u8 unk6d_2_7 : 6;
} FieldFlagElement6D;

/** Partial list element with an additional flag byte at offset 0x69. */
typedef struct FieldFlagElement69
{
    FieldFlagListElement base;
    u8 unk50[0x19];
    u8 unk69_0 : 1;
    u8 unk69_1 : 1;
    u8 unk69_2_7 : 6;
} FieldFlagElement69;

/** Partial list element containing two aligned 16-byte values. */
typedef struct FieldFlagVectorElement
{
    FieldFlagListElement base;
    u8 unk50[0x230];
    unsigned __int128 unk280;
    unsigned __int128 unk290;
} FieldFlagVectorElement;

/** Partial record whose two adjacent signed bytes are updated together. */
typedef struct FieldBytePair
{
    u8 unk00[8];
    s8 unk08;
    s8 unk09;
} FieldBytePair;

/** Partial receiver owning the byte-pair record and initialization state. */
typedef struct FieldBytePairOwner
{
    u8 unk00[0x448];
    FieldBytePair* unk448;
    u8 unk44c[0x124];
    float unk570;
    u8 unk574[0x19];
    u8 unk58d;
    u8 unk58e[2];
    u8 unk590_0 : 1;
    u8 unk590_1 : 1;
    u8 unk590_2_7 : 6;
} FieldBytePairOwner;

/** Partial receiver whose flag byte is at offset 0x81. */
typedef struct FieldByteFlags81
{
    u8 unk00[0x81];
    u8 unk81_0 : 1;
    u8 unk81_1_7 : 7;
} FieldByteFlags81;

/** Partial receiver whose flag word is at offset 0x204. */
typedef struct FieldWordFlags204
{
    u8 unk00[0x204];
    u32 unk204;
} FieldWordFlags204;

/** Partial receiver whose flag byte is at offset 0x34. */
typedef struct FieldByteFlags34
{
    u8 unk00[0x34];
    u8 unk34_0 : 1;
    u8 unk34_1_7 : 7;
} FieldByteFlags34;

/** Partial pointed-to receiver whose flag byte is at offset 0x2C. */
typedef struct FieldByteFlags2C
{
    u8 unk00[0x2C];
    u8 unk2c_0 : 1;
    u8 unk2c_1 : 1;
    u8 unk2c_2_7 : 6;
} FieldByteFlags2C;

/** Partial owner of the receiver with flags at offset 0x2C. */
typedef struct FieldFlags2COwner
{
    u8 unk00[4];
    FieldByteFlags2C* unk04;
} FieldFlags2COwner;

/** Partial pointed-to receiver whose flag byte is at offset 0x7AF. */
typedef struct FieldByteFlags7AF
{
    u8 unk00[0x7AF];
    u8 unk7af_0 : 1;
    u8 unk7af_1_7 : 7;
} FieldByteFlags7AF;

/** Partial owner of the receiver with flags at offset 0x7AF. */
typedef struct FieldFlags7AFOwner
{
    u8 unk00[4];
    FieldByteFlags7AF* unk04;
} FieldFlags7AFOwner;

/** Partial receiver whose adjacent state bytes begin at offset 0x321. */
typedef struct FieldStateBytes321
{
    u8 unk00[0x321];
    u8 unk321;
    u8 unk322;
    u8 unk323;
    u8 unk324_0 : 1;
    u8 unk324_1_7 : 7;
} FieldStateBytes321;

/** Partial receiver with two zero-tested words and a flag byte at offset 0x8C. */
typedef struct FieldWordFlags8C
{
    u8 unk00[0x80];
    u32 unk80;
    u8 unk84[8];
    u8 unk8c_0_4 : 5;
    u8 unk8c_5 : 1;
    u8 unk8c_6_7 : 2;
    u8 unk8d[0x3BB];
    u32 unk448;
} FieldWordFlags8C;

/** Partial receiver containing the observed flag byte at offset 0x8C. */
typedef struct FieldByteFlags8C
{
    u8 unk00[0x8C];
    u8 unk8c_0_4 : 5;
    u8 unk8c_5 : 1;
    u8 unk8c_6_7 : 2;
} FieldByteFlags8C;

/** Partial receiver containing an aligned 16-byte value at offset 0x20. */
typedef struct FieldAlignedValue20
{
    u8 unk00[0x20];
    unsigned __int128 unk20;
} FieldAlignedValue20;

/** Partial element of the context-0x34 list, with state and a signed key. */
typedef struct FieldStateListElement3C
{
    FieldListNode link;
    u8 unk0c[9];
    u8 unk15;
    u8 unk16[0x26];
    s32 unk3c;
} FieldStateListElement3C;

/** Partial receiver reached through context field 0x34. */
typedef struct FieldContext34
{
    u8 unk00[0x14];
    FieldListNode unk14;
} FieldContext34;

/** A 28-byte queue record with byte flags and neutral word fields. */
typedef struct FieldRecord1C
{
    u8 unk00[4];
    u32 unk04;
    u8 unk08_0 : 1;
    u8 unk08_1_7 : 7;
    u8 unk09[3];
    s32 unk0c;
    u32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_3_7 : 5;
    u8 unk17[5];
} FieldRecord1C;

/** Partial owner of the record array, limit, and next record index. */
typedef struct FieldRecordQueue
{
    u8 unk00[0x15];
    u8 unk15;
    u8 unk16[6];
    FieldRecord1C* unk1c;
    u32 unk20;
    s32 unk24;
    u8 unk28[9];
    u8 unk31;
    u8 unk32;
    u8 unk33;
    union
    {
        u8 raw;
        struct
        {
            u8 bit0 : 1;
            u8 bits1_7 : 7;
        } bits;
    } unk34;
} FieldRecordQueue;

/** A 24-byte queue record with byte flags and neutral word fields. */
typedef struct FieldRecord18
{
    u8 unk00[4];
    u32 unk04;
    u8 unk08_0 : 1;
    u8 unk08_1_7 : 7;
    u8 unk09[3];
    s32 unk0c;
    u32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_3_7 : 5;
    u8 unk17;
} FieldRecord18;

/** Partial owner of the record array, limit, and next record index. */
typedef struct FieldRecordQueue18
{
    u8 unk00[0x15];
    u8 unk15;
    u8 unk16[6];
    FieldRecord18* unk1c;
    u32 unk20;
    s32 unk24;
    u8 unk28[9];
    u8 unk31;
    u8 unk32;
    u8 unk33;
    union
    {
        u8 raw;
        struct
        {
            u8 bit0 : 1;
            u8 bits1_7 : 7;
        } bits;
    } unk34;
} FieldRecordQueue18;

/** Partial receiver containing three aligned vector values. */
typedef struct FieldVectorProduct560
{
    u8 unk00[0x560];
    unsigned __int128 unk560;
    unsigned __int128 unk570;
    unsigned __int128 unk580;
} FieldVectorProduct560;

#ifdef __cplusplus
/**
 * @brief Consume the queue update flag and advance past flagged records.
 * @param object Queue whose pending update and index state are processed.
 */
template <class Queue>
static inline void advance_record_queue(Queue* object)
{
    if ((*(const u8*)&object->unk34 & 1) != 0)
    {
        object->unk34.bits.bit0 = 0;
        if (object->unk15 == 1)
        {
            u8 index = object->unk32;
            if (index < object->unk31)
            {
                do
                {
                    object->unk32++;
                    index = object->unk32;
                    if (object->unk1c[index].unk16_0 == 0)
                    {
                        break;
                    }
                } while (index < object->unk31);
            }
            if (index >= object->unk31)
            {
                object->unk15 = 5;
            }
            else
            {
                object->unk15 = 0;
            }
        }
    }
}

extern "C" {
#endif

/**
 * @brief Clear bit six of the receiver's flag word at offset 0x204.
 * @param object Receiver whose flag is cleared.
 */
void func_00203920(FieldWordFlags204* object);

/**
 * @brief Set bit zero of the receiver's flag byte at offset 0x34.
 * @param object Receiver whose flag is set.
 */
void func_002068F0(FieldByteFlags34* object);

/**
 * @brief Set bit one of the pointed-to receiver's flag byte at offset 0x2C.
 * @param object Owner of the receiver whose flag is set.
 */
void func_0020F730(FieldFlags2COwner* object);

/**
 * @brief Set bit zero of the pointed-to receiver's flag byte at offset 0x7AF.
 * @param object Owner of the receiver whose flag is set.
 */
void func_0020FAC0(FieldFlags7AFOwner* object);

/**
 * @brief Preserve the prior state, select state three, and update the adjacent flags.
 * @param object Receiver whose state and flags are updated.
 * @param value Value whose low byte is stored at offset 0x323.
 */
void func_00207020(FieldStateBytes321* object, u32 value);

/**
 * @brief Test two nonzero words and the cleared bit-five flag at offset 0x8C.
 * @param object Receiver to inspect.
 * @return One when both words are nonzero and the flag is clear, otherwise zero.
 */
s32 func_0020DDA0(const FieldWordFlags8C* object);

/**
 * @brief Conditionally set flag bit five according to whether the supplied value is zero.
 * @param object Receiver whose flag byte is updated.
 * @param value Zero to set the flag, or a nonzero value to clear it.
 * @param update Nonzero to update the flag, or zero to preserve it.
 */
void func_0020F6D0(FieldByteFlags8C* object, u32 value, u32 update);

/**
 * @brief Copy an aligned 16-byte value when the source is present.
 * @param object Receiver containing the aligned destination value.
 * @param source Aligned value to copy, or null to preserve the destination.
 */
void func_0020F710(FieldAlignedValue20* object, const unsigned __int128* source);

/**
 * @brief Consume an update and advance the 24-byte record queue past flagged entries.
 * @param object Record queue to update.
 */
void func_0020B680(FieldRecordQueue18* object);

/**
 * @brief Store the element's word parameters and copy its two 16-byte values.
 * @param object List element whose values are replaced.
 * @param value14 Word stored at offset 0x14.
 * @param value280 Aligned value copied to offset 0x280.
 * @param value290 Aligned value copied to offset 0x290.
 * @param value18 Word stored at offset 0x18.
 * @param value28 Signed word stored at offset 0x28.
 * @param value2c Signed word stored at offset 0x2C.
 * @param value30 Signed word stored at offset 0x30.
 */
void func_002085D0(FieldFlagVectorElement* object, u32 value14,
    const unsigned __int128* value280, const unsigned __int128* value290,
    u32 value18, s32 value28, s32 value2c, s32 value30);

/**
 * @brief Reset the element's common state and clear bit one of its byte at 0x6D.
 * @param object Element whose state and flags are reset.
 */
void func_00207FE0(FieldFlagElement6D* object);

/**
 * @brief Reset the element's common state and clear bit one of its byte at 0x69.
 * @param object Element whose state and flags are reset.
 */
void func_002082E0(FieldFlagElement69* object);

/**
 * @brief Clear the element's bit-two flag and set its signed state to -3.
 * @param object Element whose flag and state are reset.
 */
void func_00208EF0(FieldFlagListElement* object);

/**
 * @brief Set bit zero or bit two according to the element's bit-four flag.
 * @param object Element whose state flag is updated.
 */
void func_00209F50(FieldFlagListElement* object);

/**
 * @brief Update four words and state on the first list element with a matching key.
 * @param object Receiver containing the circular list.
 * @param key Stored word key to find.
 * @param value38 Value to store at offset 0x38.
 * @param value44 Value to store at offset 0x44.
 * @param value3c Value to store at offset 0x3C.
 * @param value40 Value to store at offset 0x40.
 */
void func_00209FA0(FieldContext58* object, u32 key, u32 value38, u32 value44, u32 value3c, u32 value40);

/**
 * @brief Copy an aligned vector and update its product with the stored vector.
 * @param object Receiver containing the source vectors and product.
 * @param source 16-byte aligned vector data to copy.
 */
void func_0020CBF0(FieldVectorProduct560* object, const unsigned __int128* source);

/**
 * @brief Multiply all four components of two aligned vectors.
 * @param out 16-byte aligned destination vector.
 * @param left 16-byte aligned first source vector.
 * @param right 16-byte aligned second source vector.
 */
void func_0020CC30(FieldVector* out, const FieldVector* left, const FieldVector* right);

/**
 * @brief Copy one aligned 128-bit value.
 * @param out Destination value.
 * @param source Source value.
 */
void func_0020CC50(unsigned __int128* out, const unsigned __int128* source);

/**
 * @brief Set the 24-byte queue owner's state flag at byte 0x34.
 * @param object Queue whose state flag is set.
 */
void func_0020C120(FieldRecordQueue18* object);

/**
 * @brief Set flag bit zero on list elements whose selected word key matches.
 * @param object Context containing the list sentinel.
 * @param key Word key to compare with the element's selected key field.
 */
void func_00209230(FieldContext58* object, u32 key);

/**
 * @brief Initialize a 24-byte queue record's word values, flags, and byte fields.
 * @param record Record to initialize.
 * @return The initialized record.
 */
FieldRecord18* func_002096A0(FieldRecord18* record);

/**
 * @brief Reinitialize 24-byte queue records and clear word and byte state.
 * @param object Queue whose records and state are reset.
 */
void func_00209720(FieldRecordQueue18* object);

/**
 * @brief Reinitialize queue records and clear word and byte state.
 * @param object Queue whose records and state are reset.
 */
void func_00204480(FieldRecordQueue* object);

/**
 * @brief Initialize a queue record's word values, flags, and byte fields.
 * @param record Record to initialize.
 * @return The initialized record.
 */
FieldRecord1C* func_00205620(FieldRecord1C* record);

/**
 * @brief Read the object pointer at offset 0x7C.
 * @param object Receiver reached through the context-0x08 object.
 * @return The stored object pointer.
 */
void* func_0020CBC0(const FieldContext08Target* object);

/**
 * @brief Read the object pointer at offset 0xDC.
 * @param object Object reached through context field 0x08.
 * @return The stored object pointer.
 */
FieldContext08Target* func_0020CBD0(const FieldContext08* object);

/**
 * @brief Read the Field context pointer at offset 0x08.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
FieldContext08* func_0020CBE0(const FieldContextRef* ref);

/**
 * @brief Read the halfword value at offset 0x6E.
 * @param object Object containing the halfword.
 * @return The stored unsigned halfword.
 */
u16 func_0020CC20(const FieldObjectFlags* object);

/**
 * @brief Set bit 2 of each element flag byte in the circular list.
 * @param object Object reached through context field 0x58.
 */
void func_00208F20(FieldContext58* object);

/**
 * @brief Test whether any element in the circular list has a nonnegative state.
 * @param object Receiver containing the circular list.
 * @return One if an element's signed state is nonnegative, otherwise zero.
 */
s32 func_002091E0(FieldContext58* object);

/**
 * @brief Set bit 0 of each element flag byte in the circular list.
 * @param object Object reached through context field 0x58.
 */
void func_002092C0(FieldContext58* object);

/**
 * @brief Replace the stored pointer, retaining its predecessor and setting state one.
 * @param object Object reached through context field 0x58.
 * @param value Pointer to store.
 * @param unused Unused caller-supplied argument.
 */
void func_002097F0(FieldContext58* object, void* value, s32 unused);

/**
 * @brief Set two adjacent signed bytes when the destination is present.
 * @param object Unused receiver.
 * @param pair Destination record, which may be null.
 * @param first Value for the first byte.
 * @param second Value for the second byte.
 */
void func_0020DC30(void* object, FieldBytePair* pair, s8 first, s8 second);

/**
 * @brief Read an indexed entry state from its two flag bits.
 * @param object Object reached through context field 0x58.
 * @param index Entry index, from 0 through 7.
 * @return One when bit two is set, otherwise two when bit zero is set, or zero.
 */
s32 func_00209810(const FieldContext58* object, s8 index);

/**
 * @brief Set six stored values on a list element.
 * @param object List element to update.
 * @param value14 Value for offset 0x14.
 * @param value18 Value for offset 0x18.
 * @param value28 Value for offset 0x28.
 * @param value34 Value for offset 0x34.
 * @param value2c Value for offset 0x2C.
 * @param value30 Value for offset 0x30.
 */
void func_00208E70(FieldFlagListElement* object, u32 value14, u32 value18,
    s32 value28, s32 value34, s32 value2c, s32 value30);

/**
 * @brief Initialize receiver flags and state, clear its byte pair, and invoke its update routines.
 * @param object Receiver to initialize.
 */
void func_0020DC50(FieldBytePairOwner* object);

void func_0020D240(FieldBytePairOwner* object);
void func_0020D810(FieldBytePairOwner* object, float value);

/**
 * @brief Test bit zero of the flag byte at offset 0x81.
 * @param object Receiver to inspect.
 * @return True when the flag is set.
 */
bool func_00203BE0(const FieldByteFlags81* object);

/**
 * @brief Read the state byte of the first list element with a matching signed key.
 * @param object Receiver containing the circular list.
 * @param key Signed key to find.
 * @return The matching element's state byte, or 0xFE when no element matches.
 */
u8 func_002058A0(FieldContext34* object, s32 key);

/**
 * @brief Find a list element by its signed key.
 * @param object Receiver containing the circular list.
 * @param key Key to find.
 * @param unused Unused caller-supplied argument.
 * @return The matching element, or null when no element matches.
 */
FieldStateListElement3C* func_002058F0(FieldContext34* object, s32 key, s32 unused);

/**
 * @brief Find an element by the stored word at offset 0x14.
 * @param object Receiver containing the list.
 * @param key Stored word to find.
 * @return The matching element, or null at a null link or the sentinel.
 */
FieldFlagListElement* func_00209E40(FieldContext58* object, u32 key);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00203900(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00203940(void* object);

/**
 * @brief Test whether any of the three observed float fields is nonzero.
 * @param object Non-null receiver containing floats at offsets 0x180 through 0x188.
 * @return True when any field compares unequal to zero, including unordered values.
 */
bool func_00203950(const void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_00204470(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_002059A0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00205BD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00206BD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00206BE0(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_0020B400(void* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_0020C480(void* object);

#ifdef __cplusplus
}
#endif

#endif
