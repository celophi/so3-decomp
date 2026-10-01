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

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00224DF0(void* object);

/**
 * @brief Return the fixed value 14.
 * @param object Receiver or first argument; unused.
 * @return Always 14.
 */
s32 func_00228770(void* object);

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
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0022FC60(void* object);

/**
 * @brief Return the fixed value 32.
 * @param object Receiver or first argument; unused.
 * @return Always 32.
 */
s32 func_0022FD30(void* object);

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
