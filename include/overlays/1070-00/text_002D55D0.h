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

/** Four leading words observed in the receiver for func_002D69A0. */
typedef struct FieldWords002D69A0
{
    u32 words[4];
} FieldWords002D69A0;

/** Partial receiver exposing the word read by func_002D6980. */
typedef struct FieldWordAt30
{
    u8 unk00[0x30];
    u32 unk30;
} FieldWordAt30;

/** Partial receiver with a pointer, word, and derived byte flag at 0x2C–0x34. */
typedef struct FieldPointerValueState2C
{
    u8 unk00[0x2C];
    const u8* unk2c;
    u32 unk30;
    u8 unk34;
} FieldPointerValueState2C;

/** Partial receiver with a float at 0x14 and bit flag at 0x5F4. */
typedef struct FieldConditionalFloat14
{
    u8 unk00[0x14];
    float unk14;
    u8 unk18[0x5DC];
    u8 unk5f4;
} FieldConditionalFloat14;

/** Partial receiver exposing a word at offset 0x10. */
typedef struct FieldWordAt10
{
    u8 unk00[0x10];
    s32 unk10;
} FieldWordAt10;

/** Partial receiver exposing the signed halfword read by func_002D6990. */
typedef struct FieldSignedHalfAt38
{
    u8 unk00[0x38];
    s16 unk38;
} FieldSignedHalfAt38;

/** Partial receiver exposing a signed halfword at offset 0x18. */
typedef struct FieldSignedHalfAt18
{
    u8 unk00[0x18];
    s16 unk18;
} FieldSignedHalfAt18;

/** Partial receiver containing a pointer at offset 0x1C. */
typedef struct FieldPointerAt1C
{
    u8 unk00[0x1C];
    void* unk1c;
} FieldPointerAt1C;

/** Partial receiver containing a pointer at offset 0x10. */
typedef struct FieldPointerAt10
{
    u8 unk00[0x10];
    void* unk10;
} FieldPointerAt10;

/** Partial receiver containing a pointer at offset 0x4C. */
typedef struct FieldPointerAt4C
{
    u8 unk00[0x4C];
    void* unk4c;
} FieldPointerAt4C;

/** Partial receiver exposing the pointer read by func_002D6A10. */
typedef struct FieldPointerAt04
{
    u8 unk00[4];
    void* unk04;
} FieldPointerAt04;

/** Partial receiver containing a word state at offset 0x28. */
typedef struct FieldWordAt28
{
    u8 unk00[0x28];
    u32 unk28;
} FieldWordAt28;

/** Partial receiver with observed words at offsets 0x0C, 0x10, and 0x1C. */
typedef struct FieldWordsAt0C10and1C
{
    u8 unk00[0x0C];
    u32 unk0c;
    u32 unk10;
    u8 unk14[8];
    u32 unk1c;
} FieldWordsAt0C10and1C;

/** Partial receiver exposing the word tested by func_002DBCF0. */
typedef struct FieldWordAt14
{
    u8 unk00[0x14];
    u32 unk14;
} FieldWordAt14;

/** Four leading words observed in the receiver for func_002D6F20. */
typedef struct FieldWords002D6F20
{
    u32 words[4];
} FieldWords002D6F20;

/** Four leading words observed in the receiver for func_002D7B20. */
typedef struct FieldWords002D7B20
{
    u32 words[4];
} FieldWords002D7B20;

/** Four leading words observed in the receiver for func_002D9F40. */
typedef struct FieldWords002D9F40
{
    u32 words[4];
} FieldWords002D9F40;

/** Four leading words observed in the receiver for func_002DA640. */
typedef struct FieldWords002DA640
{
    u32 words[4];
} FieldWords002DA640;

/** Four leading words observed in the receiver for func_002DAB20. */
typedef struct FieldWords002DAB20
{
    u32 words[4];
} FieldWords002DAB20;

/** Entry with the observed 0xA0-byte stride. */
typedef struct FieldEntryA0
{
    u8 bytes[0xA0];
} FieldEntryA0;

/** Partial receiver containing a pointer to 0xA0-byte entries. */
typedef struct FieldEntryArray14
{
    u8 unk00[0x14];
    FieldEntryA0* entries;
} FieldEntryArray14;

/** Entry with the observed 0x40-byte stride. */
typedef struct FieldEntry40
{
    u8 bytes[0x40];
} FieldEntry40;

/** Partial receiver containing a pointer to 0x40-byte entries. */
typedef struct FieldEntryArray40At14
{
    u8 unk00[0x14];
    FieldEntry40* entries;
} FieldEntryArray40At14;

/** Partial indexed storage with a count at 0x10 and base pointer at 0x20. */
typedef struct FieldIndexedStorageAt20
{
    u8 unk00[0x10];
    s32 count;
    u8 unk14[0xC];
    u8* data;
} FieldIndexedStorageAt20;

/** One 16-byte sequence entry with a float value at offset 0xC. */
typedef struct FieldFloatValueEntryC16
{
    u8 unk00[0xC];
    float value;
} FieldFloatValueEntryC16;

/** Partial receiver with float entries at offset 0x4 and signed count at 0x28. */
typedef struct FieldFloatValueSequence28
{
    u8 unk00[4];
    FieldFloatValueEntryC16* entries;
    u8 unk08[0x20];
    s16 count;
} FieldFloatValueSequence28;

/** One 8-byte sequence entry with a float at offset zero. */
typedef struct FieldFloatValueEntry8
{
    float value;
    u8 unk04[4];
} FieldFloatValueEntry8;

/** Partial receiver with float entries at offset 0x4 and signed count at 0x18. */
typedef struct FieldFloatValueSequence18
{
    u8 unk00[4];
    FieldFloatValueEntry8* entries;
    u8 unk08[0x10];
    s16 count;
} FieldFloatValueSequence18;

/** Partial sequence state with a float range and two mirrored counts. */
typedef struct FieldFloatSequenceState24
{
    u8 unk00[4];
    FieldFloatValueEntry8* entries;
    u8 unk08[0x0C];
    float range14;
    s16 count18;
    s16 count1a;
    u8 unk1c[7];
    u8 flags23_0 : 1;
    u8 flags23_1 : 1;
    u8 flags23_2_7 : 6;
} FieldFloatSequenceState24;

/** One 8-byte sequence entry with a signed halfword at offset 0x6. */
typedef struct FieldSignedValueEntry8
{
    u8 unk00[6];
    s16 value;
} FieldSignedValueEntry8;

/** Partial receiver with signed-value entries at 0x4 and signed count at 0x18. */
typedef struct FieldSignedValueSequence18
{
    u8 unk00[4];
    FieldSignedValueEntry8* entries;
    u8 unk08[0x10];
    s16 count;
} FieldSignedValueSequence18;

/** One 48-byte sequence entry with a float value at offset 0xC. */
typedef struct FieldFloatValueEntry48
{
    u8 unk00[0xC];
    float value;
    u8 unk10[0x20];
} FieldFloatValueEntry48;

/** Partial receiver with 48-byte-stride entries at 0x4 and signed count at 0x48. */
typedef struct FieldFloatValueSequence48
{
    u8 unk00[4];
    FieldFloatValueEntry48* entries;
    u8 unk08[0x40];
    s16 count;
} FieldFloatValueSequence48;

/** Partial receiver with a float value at offset 0x48. */
typedef struct FieldFloatState4C
{
    u8 unk00[0x48];
    float unk48;
} FieldFloatState4C;

/** One 48-byte sequence entry with a float at offset zero. */
typedef struct FieldFloatFirstEntry48
{
    float value;
    u8 unk04[0x2C];
} FieldFloatFirstEntry48;

/** Partial receiver with first-component entries at 0x4 and signed count at 0x48. */
typedef struct FieldFloatFirstSequence48
{
    u8 unk00[4];
    FieldFloatFirstEntry48* entries;
    u8 unk08[0x40];
    s16 count;
} FieldFloatFirstSequence48;

/** One 32-byte sequence entry with a float at offset zero. */
typedef struct FieldFloatValueEntry32
{
    float value;
    u8 unk04[0x1C];
} FieldFloatValueEntry32;

/** Partial receiver with 32-byte-stride entries at 0x4 and signed count at 0x38. */
typedef struct FieldFloatValueSequence38
{
    u8 unk00[4];
    FieldFloatValueEntry32* entries;
    u8 unk08[0x30];
    s16 count;
} FieldFloatValueSequence38;

/** Partial 32-byte-stride sequence state with mirrored counts and cached range. */
typedef struct FieldFloatSequenceState44
{
    u8 unk00[4];
    FieldFloatValueEntry32* entries;
    u8 unk08[0x2C];
    float range34;
    s16 count38;
    s16 count3a;
    u8 unk3c[7];
    u8 flags43_0 : 1;
    u8 flags43_1 : 1;
    u8 flags43_2_7 : 6;
} FieldFloatSequenceState44;

#ifdef __cplusplus
extern "C" {
void* func_002DC2B0(void* receiver);

/**
 * @brief Copy two words to the receiver, then pass them to its callback.
 * @param object Receiver with words at offsets 0x0C and 0x10.
 * @param source Source of the words to copy.
 */
void func_002DBD00(void* object, const void* source);

/**
 * @brief Copy two words to the receiver, then pass them to its callback.
 * @param object Receiver with words at offsets 0x0C and 0x10.
 * @param source Source of the words to copy.
 */
void func_002E3C70(void* object, const void* source);
#endif

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8330(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8370(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D83B0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D83F0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D84F0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8530(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8570(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D85B0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D88D0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8910(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8950(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D8990(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D9E00(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D9E40(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D9E80(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002D9EC0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA550(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA590(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA5D0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA610(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA6C0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA6F0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA720(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA750(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DA9D0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DAA10(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DAA50(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_002DAA90(void* object);

/**
 * @brief Store the receiver's virtual float result in the supplied output.
 * @param object Receiver with the float callback at vtable offset 0x7C.
 * @param output Destination for the returned float.
 */
void func_002D7430(void* object, float* output);


/**
 * @brief Initialize the receiver, then pass it to the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002DCB80(void* object);


/**
 * @brief Copy the vector at offset 0xC0 to the supplied destination.
 * @param object Receiver containing the source vector.
 * @param result Destination for the copied vector.
 */
void func_002D64B0(const void* object, void* result);

/**
 * @brief Return an element address from the receiver's 64-byte-stride storage.
 * @param object Receiver containing the count and storage pointer.
 * @param row First index used in the flattened offset.
 * @param column Second index added to the row offset.
 * @return Address of the selected element.
 */
u8* func_002DBC90(const FieldIndexedStorageAt20* object, s32 row, s32 column);

/**
 * @brief Return an element address from the receiver's 64-byte-stride storage.
 * @param object Receiver containing the count and storage pointer.
 * @param row First index used in the flattened offset.
 * @param column Second index added to the row offset.
 * @return Address of the selected element.
 */
u8* func_002E3C00(const FieldIndexedStorageAt20* object, s32 row, s32 column);

/**
 * @brief Return the range between entry values at offset 0xC when at least two exist.
 * @param object Sequence to inspect.
 * @return Last value minus the first, or zero for fewer than two entries.
 */
float func_002D6F40(const FieldFloatValueSequence28* object);


/**
 * @brief Initialize a sequence state's pointer, mirrored counts, mode, and range.
 * @param object State to update.
 * @param count Number of entries.
 * @param entries Float entries with an eight-byte stride.
 */
void func_002D8430(FieldFloatSequenceState24* object, s32 count, FieldFloatValueEntry8* entries);

/**
 * @brief Initialize a 32-byte sequence state and cache its float range.
 * @param object State to update.
 * @param count Number of entries.
 * @param entries Float entries with a 32-byte stride.
 */
void func_002D89D0(FieldFloatSequenceState44* object, s32 count, FieldFloatValueEntry32* entries);

/**
 * @brief Initialize the 32-byte sequence state and cache its float range.
 * @param object State to update.
 * @param count Number of entries.
 * @param entries Float entries with a 32-byte stride.
 */
void func_002DAF20(FieldFloatSequenceState44* object, s32 count, FieldFloatValueEntry32* entries);



/**
 * @brief Return the range between entry values when at least two entries exist.
 * @param object Sequence to inspect.
 * @return Last value minus the first, or zero for fewer than two entries.
 */
float func_002D8290(const FieldFloatValueSequence18* object);

/**
 * @brief Return the range between entry values at offset 0xC when at least two exist.
 * @param object Sequence to inspect.
 * @return Last value minus the first, or zero for fewer than two entries.
 */
float func_002D7B40(const FieldFloatValueSequence48* object);

/**
 * @brief Return the range between entry values when at least two entries exist.
 * @param object Sequence to inspect.
 * @return Last value minus the first, or zero for fewer than two entries.
 */
float func_002D8830(const FieldFloatValueSequence38* object);

/**
 * @brief Return the range between entry values when at least two entries exist.
 * @param object Sequence to inspect.
 * @return Last value minus the first, or zero for fewer than two entries.
 */
float func_002DAE80(const FieldFloatValueSequence38* object);

/**
 * @brief Return the range between first-component values when at least two entries exist.
 * @param object Sequence to inspect.
 * @return Last value minus the first, or zero for fewer than two entries.
 */
float func_002D9F60(const FieldFloatFirstSequence48* object);

/**
 * @brief Return the floating-point range between the first and last signed entry values.
 * @param object Sequence to inspect.
 * @return Last signed value minus the first, or zero for fewer than two entries.
 */
float func_002DAB40(const FieldSignedValueSequence18* object);



/**
 * @brief Return the word at receiver offset 0x30.
 * @param object Receiver containing the word.
 * @return The word stored at offset 0x30.
 */
u32 func_002D6980(const FieldWordAt30* object);

/**
 * @brief Return the signed halfword at receiver offset 0x38.
 * @param object Receiver containing the halfword.
 * @return The signed halfword stored at offset 0x38.
 */
s16 func_002D6990(const FieldSignedHalfAt38* object);

/**
 * @brief Return the word at receiver offset 0x30.
 * @param object Receiver containing the word.
 * @return The stored word.
 */
u32 func_002DA520(const FieldWordAt30* object);

/**
 * @brief Return the signed halfword at receiver offset 0x38.
 * @param object Receiver containing the halfword.
 * @return The stored halfword.
 */
s16 func_002DA530(const FieldSignedHalfAt38* object);

/**
 * @brief Set the receiver's pointer at offset 0x4C to the configured data address.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
FieldPointerAt4C* func_002D6550(FieldPointerAt4C* object);

/**
 * @brief Set the receiver's pointer at offset 0x1C to the configured data address.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
FieldPointerAt1C* func_002D65D0(FieldPointerAt1C* object);
/**
 * @brief Set the receiver pointer at offset 0x1C, reset its state fields, and return it.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
FieldPointerAt1C* func_002D65F0(FieldPointerAt1C* object);
/**
 * @brief Set the receiver pointer at offset 0x1C, reset its state fields, and return it.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
FieldPointerAt1C* func_002D6650(FieldPointerAt1C* object);

/**
 * @brief Clear the receiver's four leading words.
 * @param object Receiver to clear.
 */
void func_002D69A0(FieldWords002D69A0* object);

/**
 * @brief Return the pointer at receiver offset 0x04.
 * @param object Receiver containing the pointer.
 * @return The pointer stored at offset 0x04.
 */
void* func_002D6A10(const FieldPointerAt04* object);

/**
 * @brief Return the pointer at receiver offset 0x04.
 * @param object Receiver containing the pointer.
 * @return The stored pointer.
 */
void* func_002DA6B0(const FieldPointerAt04* object);

/**
 * @brief Return the word at receiver offset 0x10.
 * @param object Receiver containing the word.
 * @return The stored word.
 */
s32 func_002DA9A0(const FieldWordAt10* object);

/**
 * @brief Return the signed halfword at receiver offset 0x18.
 * @param object Receiver containing the halfword.
 * @return The stored halfword.
 */
s16 func_002DA9B0(const FieldSignedHalfAt18* object);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver pointer.
 * @return The receiver pointer.
 */
void* func_002DAF70(void* object);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver pointer.
 * @return The receiver pointer.
 */
void* func_002DAF80(void* object);

/**
 * @brief Clear the receiver's four leading words.
 * @param object Receiver to clear.
 */
void func_002D6F20(FieldWords002D6F20* object);

/**
 * @brief Clear the receiver's four leading words.
 * @param object Receiver to clear.
 */
void func_002D7B20(FieldWords002D7B20* object);

/**
 * @brief Clear the receiver's four leading words.
 * @param object Receiver to clear.
 */
void func_002D9F40(FieldWords002D9F40* object);

/**
 * @brief Clear the receiver's four leading words.
 * @param object Receiver to clear.
 */
void func_002DA640(FieldWords002DA640* object);

/**
 * @brief Clear the receiver's four leading words.
 * @param object Receiver to clear.
 */
void func_002DAB20(FieldWords002DAB20* object);

/**
 * @brief Return the fixed floating-point value 2500.0.
 * @param object Receiver or first argument; unused.
 * @return Always 2500.0.
 */
float func_002DB030(void* object);

/**
 * @brief Return the fixed floating-point value 100.0.
 * @param object Receiver or first argument; unused.
 * @return Always 100.0.
 */
float func_002DBA30(void* object);

/**
 * @brief Return floating-point zero.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0.
 */
float func_002DBB80(void* object);

/**
 * @brief Return floating-point zero.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0.
 */
float func_002DBBF0(void* object);

/**
 * @brief Return one when the receiver's word at 0x14 is nonzero.
 * @param object Receiver containing the word.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_002DBCF0(const FieldWordAt14* object);

/**
 * @brief Return the fixed floating-point value 1.0.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0.
 */
float func_002DCAD0(void* object);

/**
 * @brief Return the fixed floating-point value 2500.0.
 * @param object Receiver or first argument; unused.
 * @return Always 2500.0.
 */
float func_002E2E90(void* object);

/**
 * @brief Return the fixed floating-point value 100.0.
 * @param object Receiver or first argument; unused.
 * @return Always 100.0.
 */
float func_002E39B0(void* object);

/**
 * @brief Return floating-point zero.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0.
 */
float func_002E3B00(void* object);

/**
 * @brief Return floating-point zero.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0.
 */
float func_002E3B70(void* object);

/**
 * @brief Return the floating-point value one.
 * @param object Receiver or first argument; unused.
 * @return Always 1.0.
 */
float func_002E43B0(void* object);

/**
 * @brief Return the indexed address of a 0xA0-byte entry.
 * @param object Receiver containing the entry array.
 * @param index Entry index.
 * @return Address of the selected entry.
 */
FieldEntryA0* func_002DBC70(const FieldEntryArray14* object, s32 index);


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
 * @brief Set the receiver pointer at offset 0x10, reset its leading state, and return it.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
FieldPointerAt10* func_002D66B0(FieldPointerAt10* object);

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
 * @brief Read the word at offset 0x20 from the receiver.
 * @param object Receiver containing the sequence state.
 * @return The word at offset 0x20.
 */
s32 func_002D6EB0(const FieldSequenceState20* object);

/**
 * @brief Read the signed halfword at offset 0x28 from the receiver.
 * @param object Receiver containing the sequence state.
 * @return The signed halfword at offset 0x28.
 */
s16 func_002D6EC0(const FieldSequenceState20* object);

/**
 * @brief Read the pointer at offset 0x04 from the receiver.
 * @param object Receiver containing the sequence state.
 * @return The pointer at offset 0x04.
 */
void* func_002D70D0(const FieldSequenceState10* object);

/**
 * @brief Read the word at offset 0x10 from the receiver.
 * @param object Receiver containing the sequence state.
 * @return The word at offset 0x10.
 */
s32 func_002D7400(const FieldSequenceState10* object);

/**
 * @brief Read the signed halfword at offset 0x18 from the receiver.
 * @param object Receiver containing the sequence state.
 * @return The signed halfword at offset 0x18.
 */
s16 func_002D7410(const FieldSequenceState10* object);

/**
 * @brief Return floating-point zero.
 * @param object Receiver or first argument; unused.
 * @return Always 0.0.
 */
float func_002D7420(void* object);

/**
 * @brief Return the pointer at receiver offset 0x04.
 * @param object Receiver containing the pointer.
 * @return The pointer stored at offset 0x04.
 */
void* func_002D7460(const FieldPointerAt04* object);

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
 * @brief Read the word at offset 0x40 from the receiver.
 * @param object Receiver containing the sequence state.
 * @return The word at offset 0x40.
 */
s32 func_002D7A70(const FieldSequenceState40* object);

/**
 * @brief Read the signed halfword at offset 0x48 from the receiver.
 * @param object Receiver containing the sequence state.
 * @return The signed halfword at offset 0x48.
 */
s16 func_002D7A80(const FieldSequenceState40* object);

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
 * @brief Return the pointer at receiver offset 0x04.
 * @param object Receiver containing the pointer.
 * @return The pointer stored at offset 0x04.
 */
void* func_002D7CF0(const FieldPointerAt04* object);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver pointer.
 * @return The receiver pointer.
 */
void* func_002D80B0(void* object);

/**
 * @brief Initialize the receiver's base state and invoke its virtual setup callback.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
void* func_002D8130(void* object);

/**
 * @brief Initialize the receiver's base state and invoke its virtual setup callback.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
void* func_002D8B70(void* object);

/**
 * @brief Initialize the receiver's base state and invoke its virtual setup callback.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
void* func_002D7EF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002D8360(void* object);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver pointer.
 * @return The receiver pointer.
 */
void* func_002D86C0(void* object);

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
 * @brief Return the receiver unchanged.
 * @param object Receiver pointer.
 * @return The receiver pointer.
 */
void* func_002D8AF0(void* object);

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
 * @brief Subtract the shared float constant from the positive value at offset 0x48.
 * @param object Receiver containing the value.
 */
void func_002E2DB0(FieldFloatState4C* object);



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
 * @brief Return the word at offset 0x40.
 * @param object Receiver containing the sequence state.
 * @return The stored word.
 */
s32 func_002D9DD0(const FieldSequenceState40* object);

/**
 * @brief Return the signed halfword at offset 0x48.
 * @param object Receiver containing the sequence state.
 * @return The stored halfword.
 */
s16 func_002D9DE0(const FieldSequenceState40* object);

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
 * @brief Return the pointer at receiver offset 0x04.
 * @param object Receiver containing the pointer.
 * @return The stored pointer.
 */
void* func_002DAD80(const FieldPointerAt04* object);

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
 * @brief Return the pointer at receiver offset 0x04.
 * @param object Receiver containing the pointer.
 * @return The stored pointer.
 */
void* func_002DA110(const FieldPointerAt04* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_002DB010(void* object);

/**
 * @brief Clear the receiver word at offset 0x28.
 * @param object Receiver to update.
 */
void func_002DB020(FieldWordAt28* object);

/**
 * @brief Clear the receiver word at offset 0x28.
 * @param object Receiver to update.
 */
void func_002E2E70(FieldWordAt28* object);

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
 * @brief Return the word at receiver offset 0x1C.
 * @param object Receiver containing the word.
 * @return The stored word.
 */
u32 func_002E3C20(const FieldWordsAt0C10and1C* object);

/**
 * @brief Return the word at receiver offset 0x0C.
 * @param object Receiver containing the word.
 * @return The stored word.
 */
u32 func_002E3C30(const FieldWordsAt0C10and1C* object);

/**
 * @brief Return the word at receiver offset 0x10.
 * @param object Receiver containing the word.
 * @return The stored word.
 */
u32 func_002E3C40(const FieldWordsAt0C10and1C* object);

/** @brief Return the word at receiver offset 0x1C. */
u32 func_002DBCB0(const FieldWordsAt0C10and1C* object);

/** @brief Return the word at receiver offset 0x0C. */
u32 func_002DBCC0(const FieldWordsAt0C10and1C* object);

/** @brief Return the word at receiver offset 0x10. */
u32 func_002DBCD0(const FieldWordsAt0C10and1C* object);

/**
 * @brief Return an indexed 0x40-byte entry from the receiver's array.
 * @param object Receiver containing the entry array.
 * @param index Entry index.
 * @return Address of the selected entry.
 */
FieldEntry40* func_002E3BF0(const FieldEntryArray40At14* object, s32 index);

/** @brief Return the fixed value 32. */
s32 func_002DBCE0(void* object);

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

/**
 * @brief Return one when the receiver's word at 0x14 is nonzero.
 * @param object Receiver containing the word.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_002E3C60(const FieldWordAt14* object);

/**
 * @brief Store the source and value, then reflect whether its first byte is one.
 * @param object Receiver to update.
 * @param source Byte source whose first byte controls the flag.
 * @param value Word to store at offset 0x30.
 */
void func_002DB9D0(FieldPointerValueState2C* object, const u8* source, u32 value);

/**
 * @brief Store the source and value, then reflect whether its first byte is one.
 * @param object Receiver to update.
 * @param source Byte source whose first byte controls the flag.
 * @param value Word to store at offset 0x30.
 */
void func_002E3950(FieldPointerValueState2C* object, const u8* source, u32 value);

/**
 * @brief Set the float to one when flag bit zero is set.
 * @param object Receiver containing the float and flag.
 * @return Zero when the bit is set; otherwise one.
 */
s32 func_002E5260(FieldConditionalFloat14* object);

#ifdef __cplusplus
/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_002D68C0(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_002D9960(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_002D99C0(void* object, u8 mode);

/** Set the low packed mode at its target field and record whether either mode equals four. */
void func_002D9A20(void* object, u8 mode);


/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_002D6920(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_002D9D70(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_002DA4C0(void* object, u8 mode);

/** Set the high packed mode at its target field and record whether either mode equals four. */
void func_002DA940(void* object, u8 mode);


/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D6ED0(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D7AD0(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D82E0(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D8880(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_002D9EF0(void* object, float key);

/** Find a key in the receiver's fixed-size entry array. */
s32 func_002DAED0(void* object, float key);


}
#endif

#endif
