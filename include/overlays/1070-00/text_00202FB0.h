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
    u8 unk1c[0xC];
    s32 unk28;
    s32 unk2c;
    s32 unk30;
    s32 unk34;
    u8 unk38[0x14];
    u8 unk4c_0 : 1;
    u8 unk4c_1 : 1;
    u8 unk4c_2 : 1;
    u8 unk4c_3_7 : 5;
} FieldFlagListElement;

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

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
