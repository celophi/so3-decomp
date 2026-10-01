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
    u8 unk103c_0_1 : 2;
    u8 unk103c_2 : 1;
    u8 unk103c_3_7 : 5;
} FieldConditionalState103C;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear the linked pointer when flag bit four is set and the pointer matches.
 * @param object Receiver containing the flags and linked pointer.
 * @param target Pointer to compare.
 */
void func_0023BCA0(FieldConditionalLinkA0* object, void* target);

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

#ifdef __cplusplus
}
#endif

#endif
