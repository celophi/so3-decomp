#ifndef SO3_OVERLAYS_1070_00_TEXT_00223F90_H
#define SO3_OVERLAYS_1070_00_TEXT_00223F90_H

#include "overlays/1070-00/text_00284BF0.h"

/** Partial receiver with a word value and adjacent state byte. */
typedef struct FieldWordByteState30
{
    u8 unk00[0x30];
    u32 unk30;
    u8 unk34;
} FieldWordByteState30;

/** Partial receiver with three state bytes and four float values. */
typedef struct FieldFloatResetState1C
{
    u8 unk00[0x1C];
    u8 unk1c;
    u8 unk1d;
    u8 unk1e;
    u8 unk1f;
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
} FieldFloatResetState1C;

/** Partial receiver holding a byte source, a word, and a derived state byte. */
typedef struct FieldByteSourceState
{
    u8 unk00[0x2C];
    const u8* source;
    u32 unk30;
    u8 unk34;
} FieldByteSourceState;

/** One 16-byte entry whose first component is used by the sequence range helper. */
typedef struct FieldFloatValueEntry16
{
    float unk00;
    u8 unk04[0xC];
} FieldFloatValueEntry16;

/** Partial receiver with a float-entry pointer at 0x4 and signed count at 0x20. */
typedef struct FieldFloatValueSequence20
{
    u8 unk00[4];
    FieldFloatValueEntry16* entries;
    u8 unk08[0x18];
    s16 count;
} FieldFloatValueSequence20;

/** Partial sequence receiver with cached range, counts, and mode state. */
typedef struct FieldFloatSequenceState2C
{
    u8 unk00[4];
    FieldFloatValueEntry16* entries;
    u8 unk08[0x14];
    float range1c;
    s16 count20;
    s16 count22;
    u8 unk24[7];
    u8 flags2b_0 : 1;
    u8 flags2b_1 : 1;
    u8 flags2b_2_7 : 6;
} FieldFloatSequenceState2C;

#ifdef __cplusplus
extern "C" {

/**
 * @brief Advance the receiver's word cursor and pass its values to a helper.
 * @param object Receiver containing the cursor at offset 0x540.
 * @return One after the helper call.
 */
s32 func_00233B40(void* object);

/**
 * @brief Copy two words to the receiver, then pass them to its callback.
 * @param object Receiver with words at offsets 0x0C and 0x10.
 * @param source Source of the words to copy.
 */
void func_0022FD50(void* object, const void* source);

#endif

/**
 * @brief Invoke the receiver's callback at vtable offset 0x64.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_00224CE0(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x68.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_00224D10(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x6C.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_00224D40(void* object);

/**
 * @brief Invoke the receiver's callback at vtable offset 0x70.
 * @param object Receiver with the callback dispatch table at offset zero.
 */
void func_00224D70(void* object);

/**
 * @brief Set the receiver's float at 0x5C to one and call its vtable slot 0x34.
 * @param object Receiver with the initialized field and callback table.
 */
void func_00228A00(void* object);

/**
 * @brief Store the receiver's virtual float result in the supplied output.
 * @param object Receiver with the float callback at vtable offset 0x7C.
 * @param output Destination for the returned float.
 */
void func_00224000(void* object, float* output);

/** @brief Forward the receiver and shared owner to the common helper. */
void func_00224E00(void* object);

/** @brief Forward the receiver and shared owner to the common helper. */
void func_00227BC0(void* object);

/** @brief Pass the shared context's offset-0x58 object to its helper. */
void func_00230570(void);

/**
 * @brief Return whether the shared context's status helper reports false.
 * @return One when the helper returns zero; otherwise zero.
 */
s32 func_00230680(void);


/**
 * @brief Set the four vector components.
 * @param vector Destination vector.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 * @return The destination vector.
 */
FieldVector* func_00229DF0(FieldVector* vector, float x, float y, float z, float w);

/**
 * @brief Return the range between the first and last values when at least two entries exist.
 * @param object Sequence to inspect.
 * @return Last first-component value minus the first, or zero for fewer than two entries.
 */
float func_00224180(const FieldFloatValueSequence20* object);

/**
 * @brief Initialize a sequence state's data pointer, counts, mode, and range.
 * @param object State to update.
 * @param count Number of entries.
 * @param entries Float values stored at the start of each 16-byte entry.
 */
void func_00224220(FieldFloatSequenceState2C* object, s32 count, FieldFloatValueEntry16* entries);


/**
 * @brief Set the word at offset 0x30 and its adjacent state byte.
 * @param object Receiver to update.
 * @param value Word to store.
 * @param state State byte to store.
 */
void func_002279E0(FieldWordByteState30* object, u32 value, u8 state);

/**
 * @brief Clear three state bytes and four float values.
 * @param object Receiver to reset.
 */
void func_002286C0(FieldFloatResetState1C* object);

/**
 * @brief Reset the state, set two byte/float pairs, and copy the second state when its float is zero.
 * @param object Receiver to update.
 * @param first_state First state byte.
 * @param second_state Second state byte.
 * @param first Value for offset 0x20.
 * @param second Value for offset 0x28.
 */
void func_00228670(FieldFloatResetState1C* object, u8 first_state, u8 second_state, float first, float second);

/**
 * @brief Read the word at receiver offset 0x18.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_00223F90(const void* object);

/**
 * @brief Read the signed halfword at receiver offset 0x20.
 * @param object Receiver to inspect.
 * @return Stored signed value.
 */
s32 func_00223FA0(const void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223FB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223FC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00223FD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00223FE0(void* object);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_00223FF0(void* object);

/**
 * @brief Read the word at receiver offset 0x4.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_00224030(const void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00224DF0(void* object);


/**
 * @brief Set the receiver's byte at offset 0x48 to one.
 * @param object Receiver.
 */
void func_00228020(void* object);

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
void func_00228480(void* object);

/**
 * @brief Detach the receiver, then process it through the shared owner.
 * @param object Receiver to detach and process.
 */
void func_00231920(void* object);

/**
 * @brief Initialize the receiver's base state, set its secondary vtable, and return it.
 * @param object Receiver to initialize.
 * @return The receiver.
 */
void* func_00231BA0(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_00228770(void* object);

/**
 * @brief Clear bit 0x40 in the receiver's word at offset 0x204.
 * @param object Receiver.
 */
void func_0022D480(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022D5F0(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_0022D680(void* object);

/**
 * @brief Clear the receiver's word at offset 0x28 and copy a float from source offset 0xAF0
 *        to receiver offset 0xE4.
 * @param object Receiver to update.
 * @param source Source of the float value.
 */
void func_0022D690(void* object, const void* source);

/**
 * @brief Return the floating-point value 2500.
 * @param object Receiver or first argument; unused.
 * @return 2500.0f.
 */
float func_0022D6A0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0022D6C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022DE80(void* object);

/**
 * @brief Return the fixed value 240.
 * @param object Receiver or first argument; unused.
 * @return Always 240.
 */
s32 func_0022EAB0(void* object);

/**
 * @brief Return the fixed value 7.
 * @param object Receiver or first argument; unused.
 * @return Always 7.
 */
s32 func_0022F140(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022F150(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022F160(void* object);

/**
 * @brief Return the field at offset 0x620 when the word at +0x618 is nonzero.
 * @param object Receiver.
 * @return Address at +0x620, or null when the word at +0x618 is zero.
 */
void* func_0022F170(const void* object);

/**
 * @brief Store the source and word, and set the state byte when the first source byte is one.
 * @param object Receiver to update.
 * @param source Non-null source of the state byte.
 * @param value Word to store.
 */
void func_0022FA30(FieldByteSourceState* object, const u8* source, u32 value);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022FA70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FA80(void* object);

/**
 * @brief Return the floating-point value 100.
 * @param object Receiver or first argument; unused.
 * @return 100.0f.
 */
float func_0022FA90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FAA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FAB0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FAC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FAD0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FAE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FAF0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022FB00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FB10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FB20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FB30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022FB40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FB50(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FB60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FB70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FB80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FB90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022FBA0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FBB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022FBC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FBD0(void* object);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_0022FBE0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FBF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FC00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022FC10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FC20(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0022FC30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FC40(void* object);

/**
 * @brief Return the floating-point value 0.
 * @param object Receiver or first argument; unused.
 * @return 0.0f.
 */
float func_0022FC50(void* object);

/**
 * @brief Return the table base at offset 0x14 plus index times 0x80.
 * @param object Receiver containing the table base.
 * @param index Table entry index.
 * @return Address of the selected table entry.
 */
void* func_0022FCD0(const void* object, u32 index);

/**
 * @brief Return a row entry from the indexed table.
 * @param object Receiver containing the row count and table base.
 * @param index Row index.
 * @param row Entry index within the row.
 * @return Address of the selected table entry.
 */
void* func_0022FCE0(const void* object, s32 index, s32 row);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FC60(void* object);

/**
 * @brief Read the word at receiver offset 0x1C.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0022FD00(const void* object);

/**
 * @brief Read the word at receiver offset 0xC.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0022FD10(const void* object);

/**
 * @brief Read the word at receiver offset 0x10.
 * @param object Receiver to inspect.
 * @return Stored word.
 */
u32 func_0022FD20(const void* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver or first argument; unused.
 * @return Always 32.
 */
s32 func_0022FD30(void* object);

/**
 * @brief Test whether the receiver's word at offset 0x14 is nonzero.
 * @param object Receiver.
 * @return One when the word is nonzero; otherwise zero.
 */
s32 func_0022FD40(const void* object);

/**
 * @brief Return the floating-point value 1.
 * @param object Receiver or first argument; unused.
 * @return 1.0f.
 */
float func_002303D0(void* object);

/**
 * @brief Return the shared floating-point value.
 * @param object Receiver or first argument; unused.
 * @return The value at D_001B66B4.
 */
float func_00230440(void* object);

/**
 * @brief Test whether the shared context word at offset 0x50 is nonzero.
 * @param object Receiver or first argument; unused.
 * @return One when the context word is nonzero; otherwise zero.
 */
s32 func_002304D0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002304F0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00230500(void* object);

#ifdef __cplusplus
}
#endif

#endif
