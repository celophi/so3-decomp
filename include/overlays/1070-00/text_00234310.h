#ifndef SO3_OVERLAYS_1070_00_TEXT_00234310_H
#define SO3_OVERLAYS_1070_00_TEXT_00234310_H

#include "overlays/1070-00/text_00284BF0.h"


/** Partial receiver for the observed conditional state update. */
typedef struct FieldConditionalLinkA0
{
    u8 unk00[0x70];
    u32 unk70;
    u8 unk74[0x2C];
    void* unka0;
} FieldConditionalLinkA0;

/** Partial receiver for the observed conditional state update. */
typedef struct FieldConditionalState103C
{
    u8 unk00[0xCB];
    u8 unkcb;
    u8 unkcc[0x9F1];
    u8 unkabd;
    u8 unkabe[0x54A];
    u32 unk1008;
    s32 unk100c;
    u8 unk1010[0x2C];
    u8 unk103c_0 : 1;
    u8 unk103c_1 : 1;
    u8 unk103c_2 : 1;
    u8 unk103c_3_7 : 5;
} FieldConditionalState103C;

/** Partial receiver containing the flag byte at offset 0x4C0. */
typedef struct FieldFlagState4C0
{
    u8 unk00[0x4C0];
    u8 unk4c0_0 : 1;
    u8 unk4c0_1_7 : 7;
} FieldFlagState4C0;

/** Partial nested object with the bit used to choose a color value. */
typedef struct FieldColorFlag1C
{
    u8 unk00[0x1C];
    u8 unk1c;
} FieldColorFlag1C;

/** Partial color state containing its flag source and output word. */
typedef struct FieldColorState30
{
    u8 unk00[0x30];
    FieldColorFlag1C* unk30;
    u32 unk34;
} FieldColorState30;

/** Partial receiver with an optional color state at offset 0x44. */
typedef struct FieldOptionalColor44
{
    u8 unk00[0x44];
    FieldColorState30* unk44;
} FieldOptionalColor44;

/** Partial state copied and conditionally initialized by func_0023BC60. */
typedef struct FieldConditionalVectorState
{
    u8 unk00[0x10];
    unsigned __int128 unk10;
    u8 unk20[0x50];
    u32 unk70;
    u8 unk74[0x1C];
    unsigned __int128 unk90;
    u32 unka0;
    s32 unka4;
    s32 unka8;
} FieldConditionalVectorState;

#ifdef __cplusplus
extern "C" {


#endif


/**
 * @brief Call the shared no-argument helper at 0x004967C0.
 */
void func_0023A350(void);

/**
 * @brief Call the shared no-argument helper at 0x004967C0.
 */
void func_00239B90(void);

/**
 * @brief Call the shared no-argument helper at 0x004EABF0.
 */
void func_0023C5D0(void);

/**
 * @brief Update shared field state from the receiver's float value.
 * @param object Receiver containing a pointer at offset 0x540.
 * @return One after the update.
 */
s32 func_00238F30(const void* object);


/**
 * @brief Call the shared no-argument helper at 0x004EABF0.
 */
void func_0023D4E0(void);

/**
 * @brief Set flag bit zero from the supplied word's low bit.
 * @param object Receiver to update.
 * @param value Word whose low bit determines the flag.
 */
void func_00244220(FieldFlagState4C0* object, u32 value);

/**
 * @brief Set flag bit two while preserving the other bits in the byte.
 * @param object Non-null writable receiver containing the flag byte.
 */
void func_0023A870(void* object);

/**
 * @brief Set flag bit zero while preserving the other bits in the byte.
 * @param object Non-null writable receiver containing the flag byte.
 */
void func_0023BA90(void* object);

/**
 * @brief Set flag bit one while preserving the other bits in the byte.
 * @param object Non-null writable receiver containing the flag byte.
 */
void func_0023BAB0(void* object);

/**
 * @brief Set flag bit one while preserving the other bits in the byte.
 * @param object Non-null writable receiver containing the flag byte.
 */
void func_002399E0(void* object);

/**
 * @brief Set flag bit one while preserving the other bits in the byte.
 * @param object Non-null writable receiver containing the flag byte.
 */
void func_0023BA70(void* object);

/**
 * @brief Copy the byte at offset 0xF0 into the byte at offset 0x60.
 * @param object Receiver with a readable source byte and writable destination byte.
 */
void func_0023C4F0(void* object);

/**
 * @brief Copy the byte at offset 0x94 into the byte at offset 0x60.
 * @param object Receiver with a readable source byte and writable destination byte.
 */
void func_0023E5D0(void* object);

/** @brief Call the helper when both observed nested pointers are present. */
s32 func_0023E800(void);

/**
 * @brief Store 0 in the observed word and return 1.
 * @param object Non-null receiver containing the writable word.
 * @return Always 1.
 */
s32 func_0023ED60(void* object);

/**
 * @brief Store 1 in the observed word and return 1.
 * @param object Non-null receiver containing the writable word.
 * @return Always 1.
 */
s32 func_0023F940(void* object);

/**
 * @brief Set flag bit zero and store the supplied word bits.
 * @param object Non-null writable receiver to update.
 * @param value Word bits to store.
 */
void func_00243630(void* object, u32 value);

/**
 * @brief Clear the linked pointer when flag bit four is set and the pointer matches.
 * @param object Receiver containing the flags and linked pointer.
 * @param target Pointer to compare.
 */
void func_0023BCA0(FieldConditionalLinkA0* object, void* target);

/** @brief Invoke the optional child callback at offset 0x90, then clear the pointer. */
void func_00236300(void* object);

/** @brief Invoke the optional child callback at offset 0x44, then clear the pointer. */
void func_00236500(void* object);

/** @brief Invoke the optional child's callback at offset 0x20, then clear the pointer. */
void func_00238420(void* object);

/** @brief Set the receiver's low two flag bits to two and call its +0x20 callback. */
void func_0023A830(FieldConditionalState103C* object);

/**
 * @brief Set flag bit two and conditionally update the byte, state and word flags.
 * @param object Receiver to update.
 */
void func_0023A2D0(FieldConditionalState103C* object);

/**
 * @brief Check the byte-state condition or whether the first float is below the second.
 * @param object Slot object to inspect.
 * @return True when either observed condition holds.
 */
bool func_0023D480(const FieldSlotObject* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00236740(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00236750(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002367C0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00237BE0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00239AD0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0023B250(void* object);

/**
 * @brief Return the fixed value 13.
 * @param object Receiver or first argument; unused.
 * @return Always 13.
 */
s32 func_0023BA60(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_0023C4E0(void* object);

/**
 * @brief Update the receiver's state flags.
 * @param object Receiver whose state is updated.
 */
void func_00237FF0(void* object);

/**
 * @brief Copy the vector state and update its conditional word.
 * @param object State to update.
 */
void func_0023BC60(FieldConditionalVectorState* object);

/**
 * @brief Update the optional state's color word from the nested flag's low bit.
 * @param object Receiver containing the optional state.
 */
void func_002364C0(FieldOptionalColor44* object);

/**
 * @brief Initialize the receiver and process it through the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_00236540(void* object);

/**
 * @brief Initialize the receiver and process it through the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002378C0(void* object);

/**
 * @brief Initialize the receiver and process it through the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002435F0(void* object);

/**
 * @brief Initialize the receiver and process it through the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_00243C40(void* object);

/**
 * @brief Initialize the linked receiver and clear its observed state bit.
 * @param object Receiver containing the state word.
 */
void func_0023BB30(FieldConditionalLinkA0* object);

/**
 * @brief Build and store the receiver's word from its source pair.
 * @param object Receiver containing the source pointer and destination word.
 * @return One after the word is stored.
 */
s32 func_0023F900(void* object);

/**
 * @brief Initialize the shared context's float transition state.
 * @return One after the transition state is initialized.
 */
s32 func_00238390(void);

/**
 * @brief Copy the source low bit into the shared state flag.
 * @param object Receiver containing a pointer to the source word.
 */
s32 func_00238FA0(void* object);

/**
 * @brief Clear the indexed context slot when it still points to this receiver.
 * @param object Receiver containing the slot index.
 */
void func_0023DDC0(void* object);

/**
 * @brief Store the receiver's float in shared context and refresh helper state.
 * @param object Receiver containing the source float pointer.
 * @return One after the context update.
 */
s32 func_00238F60(void* object);

/**
 * @brief Clear the word at offset 0x250, initialize the receiver and process it.
 * @param object Receiver to update.
 */
void func_00243AE0(void* object);

/**
 * @brief Return the fixed value 9.
 * @param object Receiver or first argument; unused.
 * @return Always 9.
 */
s32 func_00243620(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00243B30(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00243B40(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00243B50(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00243B60(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00243B70(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00243B80(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00243B90(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00243BA0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00244240(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00244250(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00244260(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00244270(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00244280(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00244290(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002442A0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002442B0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002442C0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002442D0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002442E0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002442F0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00244300(void* object);

/**
 * @brief Initialize the receiver and process it through the shared owner.
 * @param object Receiver to initialize and process.
 */
void func_002343C0(void* object);

/**
 * @brief Release the optional child pointer at receiver offset 0x90.
 * @param object Receiver containing the child pointer.
 */
void func_002362D0(void* object);

#ifdef __cplusplus
}
#endif

#endif
