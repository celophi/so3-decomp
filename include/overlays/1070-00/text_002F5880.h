#ifndef SO3_OVERLAYS_1070_00_TEXT_002F5880_H
#define SO3_OVERLAYS_1070_00_TEXT_002F5880_H

#include "types.h"

/** Partial reset prefix with an opaque word and four halfwords. */
typedef struct FieldResetState18
{
    u8 unk00[0x18];
    u32 unk18;
    u8 unk1c[4];
    u16 unk20;
    u8 unk22[2];
    s16 unk24;
    s16 unk26;
    s16 unk28;
} FieldResetState18;

/** Partial state containing two floats and adjacent status bytes. */
typedef struct FieldStatus44
{
    u8 unk00[0x20];
    float unk20;
    float unk24;
    u8 unk28[0x1c];
    u8 unk44;
    u8 unk45;
} FieldStatus44;

typedef struct FieldClampState FieldClampState;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear a word and halfword, and set three halfwords to minus one.
 * @param object Receiver to reset.
 */
void func_002F5880(FieldResetState18* object);

/**
 * @brief Store two float values and mark the state at offset 0x44.
 * @param object State to update.
 * @param first First float value.
 * @param second Second float value.
 */
void func_00305650(FieldStatus44* object, float first, float second);

/**
 * @brief Store a byte in the state at offset 0x45.
 * @param object State to update.
 * @param unused Unused callback argument.
 * @param value Value to store.
 */
void func_003056F0(FieldStatus44* object, u32 unused, u8 value);

/**
 * @brief Return zero as a float.
 * @return Zero.
 */
float func_00305700(void);

/**
 * @brief Clamp a selected position and reset related state fields.
 * @param object State to update.
 * @param value Selected unsigned position.
 */
void func_00305830(FieldClampState* object, u16 value);

#ifdef __cplusplus
}
#endif

#endif
