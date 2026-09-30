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

#ifdef __cplusplus
}
#endif

#endif
