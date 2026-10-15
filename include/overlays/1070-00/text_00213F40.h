#ifndef SO3_OVERLAYS_1070_00_TEXT_00213F40_H
#define SO3_OVERLAYS_1070_00_TEXT_00213F40_H

#include "types.h"

#ifdef __cplusplus
/** Observed primary prefix of the receiver passed to func_0021AB20. */
class FieldReceiverHead21AB20
{
public:
    u8 unk00[0x14];
};

/** Observed secondary prefix, beginning at offset 0x14. */
class FieldReceiverTail21AB20
{
public:
    u8 unk00[0xC];
    s32 unk0c;
};

/** Partial receiver with its checked word at offset 0x20. */
class FieldReceiver21AB20 : public FieldReceiverHead21AB20, public FieldReceiverTail21AB20
{
};
#else
typedef struct FieldReceiverTail21AB20 FieldReceiverTail21AB20;
#endif

/** A 32-byte record in the observed child and sibling traversal. */
typedef struct FieldTraversalRecord
{
    struct FieldTraversalRecord* children;
    u8 unk04[6];
    u8 unk0a;
    u8 unk0b[3];
    s16 unk0e;
    u8 unk10[0x10];
} FieldTraversalRecord;

/** Partial receiver whose scaled float value is at offset 0x30. */
typedef struct FieldFloatState30
{
    u8 unk00[0x30];
    float unk30;
} FieldFloatState30;



/** Circular-list node with a key halfword at offset 0x6E. */
typedef struct FieldKeyNode6E
{
    u8 unk00[8];
    struct FieldKeyNode6E* next;
    u8 unk0c[0x62];
    u16 key6e;
} FieldKeyNode6E;

/** Receiver with a circular-list sentinel at offset 0x18. */
typedef struct FieldKeyList18
{
    u8 unk00[0x18];
    FieldKeyNode6E sentinel;
} FieldKeyList18;




/** Partial target containing a value and its update byte. */
typedef struct FieldValueState100
{
    u8 unk00[0x40];
    u8 unk40;
    u8 unk41[0xBF];
    s32 unk100;
} FieldValueState100;

/** Partial receiver whose optional value target is at offset 0x34. */
typedef struct FieldValueOwner34
{
    u8 unk00[0x34];
    FieldValueState100* unk34;
} FieldValueOwner34;

/** Partial receiver containing two checked halfword groups and their check words. */
typedef struct FieldCheckedState00
{
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0a;
    u8 unk0c[0xDC];
    s32 unke8;
    s32 unkec;
    u8 unkf0[0x1C];
    s32 unk10c;
} FieldCheckedState00;

/** Partial receiver containing checked word and halfword groups. */
typedef struct FieldCheckedState7C
{
    u8 unk00[0x34];
    u32 unk34;
    u32 unk38;
    u32 unk3c;
    u32 unk40;
    u32 unk44;
    u32 unk48;
    u32 unk4c;
    u32 unk50;
    u32 unk54;
    u32 unk58;
    u32 unk5c;
    u32 unk60;
    u8 unk64[8];
    u32 unk6c;
    u8 unk70[0xC];
    s16 unk7c;
    s16 unk7e;
    s16 unk80;
    u8 unk82[0x12];
    u32 unk94;
    u32 unk98;
    u32 unk9c;
    u32 unka0;
    u8 unka4[4];
    s32 unka8;
    s32 unkac;
} FieldCheckedState7C;

/** Partial 0x1C-byte array entry handled by func_0021A970. */
typedef struct FieldEntry1C
{
    u32 unk00;
    u32 unk04;
    u8 unk08_0 : 1;
    u8 unk08_1_7 : 7;
    u8 unk09[3];
    s32 unk0c;
    u32 unk10;
    u8 unk14[2];
    u8 unk16_0 : 1;
    u8 unk16_1 : 1;
    u8 unk16_2 : 1;
    u8 unk16_3_7 : 5;
    u8 unk17[5];
#ifdef __cplusplus
    /** @brief Read the entry's byte count. @return Stored byte count. */
    u32 byte_count() const
    {
        return unk00;
    }

    /**
     * @brief Read the stored address, rounded to 128 bytes unless either control flag is set.
     * @return Raw or rounded address value.
     */
    u32 rounded_unk04()
    {
        if (unk08_0 || unk16_2)
        {
            return unk04;
        }
        return (unk04 + 127) & ~127;
    }
#endif
} FieldEntry1C;

/** Partial receiver with writable words at offsets 0x14, 0x18, and 0x1C. */
typedef struct FieldWordTriplet14
{
    u8 unk00[0x14];
    u32 unk14;
    u32 unk18;
    u32 unk1c;
} FieldWordTriplet14;

/** Partial receiver with the flag byte at offset 0x1C. */
typedef struct FieldFlagAt1C
{
    u8 unk00[0x1C];
    u8 unk1c_0 : 1;
    u8 unk1c_1_7 : 7;
} FieldFlagAt1C;

/** Partial receiver with the bit fields updated by func_00216A50. */
typedef struct FieldFlagMirrorAt20
{
    u8 unk00[0x20];
    u8 unk20_0 : 1;
    u8 unk20_1 : 1;
    u8 unk20_2 : 1;
    u8 unk20_3_7 : 5;
} FieldFlagMirrorAt20;



/** One 16-byte interpolation entry with three observed float fields. */
typedef struct FieldCurveEntry
{
    float unk00;
    float unk04;
    float unk08;
    u8 unk0c[4];
} FieldCurveEntry;

/** Partial interpolation table holding a signed count and its entries. */
typedef struct FieldFloatCurve
{
    s32 count;
    FieldCurveEntry* entries;
} FieldFloatCurve;

#ifdef __cplusplus
extern "C" {
void* func_00216CC0(void* receiver);


/**
 * @brief Invoke the receiver's callback at vtable offset 0x54.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_0021A930(void* object);

/**
 * @brief Return the word predicate when the float is nonpositive, otherwise one.
 * @param object Receiver with the word at 0x0C and float at 0x78.
 * @return The selected zero-or-one result.
 */
s32 func_0021AF10(const void* object);

/**
 * @brief Call the receiver's output callback with zero and one local word.
 * @param object Receiver with the output callback at vtable offset 0x34.
 */
void func_00223C40(void* object);

/**
 * @brief Initialize the receiver's table pointer and state byte.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
void* func_00215CC0(void* object);

/**
 * @brief Run the receiver detachment helper, then process the receiver with the shared owner.
 * @param object Receiver passed to both helpers.
 */
void func_00215FF0(void* object);

/**
 * @brief Run the receiver detachment helper, then process the receiver with the shared owner.
 * @param object Receiver passed to both helpers.
 */
void func_00216F00(void* object);

/** @brief Detach the second argument, then invoke its virtual method at offset 0x10. */
void func_00223580(void* unused, void* object);
#endif

/**
 * @brief Advance to the next contiguous record.
 * @param record Current traversal record.
 * @return The following record.
 */
FieldTraversalRecord* func_0021EC30(FieldTraversalRecord* record);

/**
 * @brief Test bit 0x20 that terminates the observed sibling traversal.
 * @param record Current traversal record.
 * @return One when the bit is set, otherwise zero.
 */
s32 func_0021EC40(const FieldTraversalRecord* record);

/**
 * @brief Get the child record sequence.
 * @param record Current traversal record.
 * @return The child sequence pointer, or null.
 */
FieldTraversalRecord* func_0021EC50(const FieldTraversalRecord* record);

/**
 * @brief Read the signed record index.
 * @param record Current traversal record.
 * @return The stored index, including the observed -1 sentinel.
 */
s16 func_0021EC60(const FieldTraversalRecord* record);

/**
 * @brief Read the stored float scaled by one sixteenth.
 * @param object Receiver to inspect.
 * @return The stored value multiplied by 0.0625.
 */
float func_00214DA0(const FieldFloatState30* object);


/**
 * @brief Update the optional target value and set its update byte.
 * @param object Receiver whose target may be null.
 * @param value Signed value to store.
 */
void func_0021EF10(FieldValueOwner34* object, s32 value);

/**
 * @brief Validate the second halfword group and decode its stored value.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_002140E0(const FieldCheckedState00* object);

/**
 * @brief Validate the first halfword group and decode its stored value.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214200(const FieldCheckedState00* object);

/**
 * @brief Validate the halfword group at offset 0x7C and decode its stored value.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214320(const FieldCheckedState7C* object);

/**
 * @brief Validate the word group at offset 0x58 and decode the value at offset 0x6C.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214490(const FieldCheckedState7C* object);

/**
 * @brief Validate the word group at offset 0x58 and decode its stored value.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214650(const FieldCheckedState7C* object);

/**
 * @brief Validate the word group at offset 0x4C and decode the value at offset 0x50.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_002148D0(const FieldCheckedState7C* object);

/**
 * @brief Validate the word group at offset 0x40 and decode the value at offset 0x48.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214AA0(const FieldCheckedState7C* object);

/**
 * @brief Validate the word group at offset 0x34 and decode the value at offset 0x3C.
 * @param object Receiver to inspect.
 * @return The decoded value, or zero when the check does not match.
 */
s32 func_00214C70(const FieldCheckedState7C* object);

/**
 * @brief Forward the receiver's secondary interface to its external operation.
 * @param object Receiver whose secondary interface starts at offset 0x20.
 */
void func_002156B0(void* object);


/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00215EB0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00215EC0(void* object);

/**
 * @brief Set bit zero in the receiver's byte at offset 0x34.
 * @param object Receiver to update.
 */
void func_0021CBD0(void* object);


/**
 * @brief Clear the receiver's word at offset 0x4C, then run its reset routine.
 * @param object Receiver to reset.
 */
void func_00223AA0(void* object);

/**
 * @brief Reset the receiver's state fields.
 * @param object Receiver to reset.
 */
void func_00223D70(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00215FE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216090(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216100(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216180(void* object);

/**
 * @brief Clear bit zero in the receiver's byte at offset 0x1C.
 * @param object Receiver to update.
 */
void func_002161F0(FieldFlagAt1C* object);

/**
 * @brief Clear bit two and copy bit one into bit zero of the receiver byte at 0x20.
 * @param object Receiver to update.
 */
void func_00216A50(FieldFlagMirrorAt20* object);

/**
 * @brief Call the helper on the subobject at 0x5A4, then update the receiver.
 * @param object Receiver to update.
 */
void func_00216A20(void* object);


/**
 * @brief Call the receiver's virtual callback with the value one when non-null.
 * @param object Optional callback receiver.
 */
void func_002239C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216870(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216880(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00216890(void* object);

/**
 * @brief Return the fixed value 300.
 * @param object Receiver or first argument; unused.
 * @return Always 300.
 */
s32 func_00216910(void* object);

/**
 * @brief Return the fixed value -1.
 * @param object Receiver or first argument; unused.
 * @return Always -1.
 */
s32 func_00216C30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216CA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00216CB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00219670(void* object);

/**
 * @brief Copy the receiver's 128-bit value from offset 0x20 to 0x650 and store three floats
 *        at offsets 0x680, 0x688, and 0x68C.
 * @param object Receiver.
 * @param x First float.
 * @param y Second float.
 * @param z Third float.
 */
void func_00219810(void* object, float x, float y, float z);

/**
 * @brief Return the fixed value 12.
 * @param object Receiver or first argument; unused.
 * @return Always 12.
 */
s32 func_0021A960(void* object);

/**
 * @brief Pass the entry's word at offset 0x4 to func_100D60 and clear it, if bit 1 of its
 *        byte at offset 0x16 is set.
 * @param entry Entry to update.
 * @return 1 if the word was passed on and cleared, otherwise 0.
 */
s32 func_0021A970(FieldEntry1C* entry);

/**
 * @brief Return the receiver address.
 * @param object Receiver to return.
 * @return The receiver address.
 */
void* func_00217CC0(void* object);

/**
 * @brief Return the receiver address.
 * @param object Receiver to return.
 * @return The receiver address.
 */
void* func_0021A460(void* object);

/**
 * @brief Return the receiver address.
 * @param object Receiver to return.
 * @return The receiver address.
 */
void* func_0021D710(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00221620(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00221660(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00221FB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002239B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223A40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223A50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223A60(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223A70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00223A80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00223A90(void* object);

/**
 * @brief Copy the source vector and initialize the destination vector.
 * @param object Receiver containing vectors at offsets 0x20, 0x170, and 0x190.
 */
void func_00222D20(void* object);

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
void func_0021EEE0(void* object);

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
void func_00221630(void* object);

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
void func_00221C30(void* object);

/**
 * @brief Copy the receiver's float at offset 0x50 to the output pointer.
 * @param object Receiver.
 * @param value Destination for the float.
 */
void func_00223C80(const void* object, float* value);


/**
 * @brief Evaluate the interpolation curve at the supplied position.
 * @param curve Curve records and their signed count.
 * @param position Position to evaluate.
 * @return Interpolated curve value, or zero for fewer than two records.
 */
float func_002166F0(const FieldFloatCurve* curve, float position);

/**
 * @brief Store three words at receiver offsets 0x14, 0x18, and 0x1C.
 * @param object Receiver to update.
 * @param value18 Value for offset 0x18.
 * @param value14 Value for offset 0x14.
 * @param value1c Value for offset 0x1C.
 */
void func_00218AE0(FieldWordTriplet14* object, u32 value18, u32 value14, u32 value1c);




#ifdef __cplusplus
/**
 * @brief Check whether the circular list contains the supplied key.
 * @param object Receiver whose list is inspected.
 * @param key Key to search for.
 * @return 1 when the key is present, otherwise 0.
 */
s32 func_002179B0(const FieldKeyList18* object, s32 key);



/**
 * @brief Check collected receivers, excluding the supplied object.
 * @param object Receiver containing the collection state.
 * @param excluded Receiver to exclude from the check.
 * @return True when a collected receiver reports the observed condition.
 */
bool func_0021AB20(FieldReceiver21AB20* object, void* excluded);
/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_00223ED0(void* object, u8 mode);


/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_00223F30(void* object, u8 mode);


}
#endif

#endif
