#ifndef SO3_OVERLAYS_1067_00_TEXT_001ED7E0_H
#define SO3_OVERLAYS_1067_00_TEXT_001ED7E0_H

#include "types.h"

/** Partial receiver with three four-float values and a byte flag. */
typedef struct FieldVectorState50
{
    u8 unk00[0x20];
    float unk20[4];
    float unk30[4];
    float unk40[4];
    u8 unk50;
} FieldVectorState50;

/** Partial receiver with a byte flag at offset 0x60. */
typedef struct FieldByteState60
{
    u8 unk00[0x60];
    u8 unk60;
} FieldByteState60;

/** Partial receiver with four floats at offset 0x20. */
typedef struct FieldFloat4At20
{
    u8 unk00[0x20];
    float unk20[4];
} FieldFloat4At20;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mark the vector state and set its first four-float value with a final component of one.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_001EDE80(FieldVectorState50* state, float x, float y, float z);

/**
 * @brief Mark the vector state and set its second four-float value.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
void func_001EDEA0(FieldVectorState50* state, float x, float y, float z, float w);

/**
 * @brief Mark the vector state and transform an input into its second value.
 * @param state Receiver to update.
 * @param input Four-float input to transform.
 */
void func_001EDEE0(FieldVectorState50* state, const float* input);

/**
 * @brief Mark the vector state and transform an input into its second value.
 * @param state Receiver to update.
 * @param input Four-float input to transform.
 */
void func_001EDF10(FieldVectorState50* state, const float* input);

/**
 * @brief Mark the vector state and transform a three-float input with a final component of one.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_001EDF40(FieldVectorState50* state, float x, float y, float z);

/**
 * @brief Mark the vector state and set the first three components of its third value.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_001EDFA0(FieldVectorState50* state, float x, float y, float z);

/**
 * @brief Clear the byte flag at offset 0x60.
 * @param state Receiver to update.
 */
void func_001EE150(FieldByteState60* state);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_001EE160(void* object);

/**
 * @brief Return zero for this receiver.
 * @param object Receiver of the call.
 * @return Zero.
 */
s32 func_001EE170(void* object);

/**
 * @brief Test whether a value is negative.
 * @param object Receiver of the call.
 * @param value Value to test.
 * @return True when value is negative, otherwise false.
 */
bool func_001EE180(void* object, float value);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_001EE1B0(void* object);

/**
 * @brief Return zero for this receiver.
 * @param object Receiver of the call.
 * @return Zero.
 */
s32 func_001EE1C0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_001EE1D0(void* object);

/**
 * @brief Set four floats at offset 0x20, using one as the last component.
 * @param state Receiver to update.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 */
void func_001EE230(FieldFloat4At20* state, float x, float y, float z);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_001EE250(void* object);

/**
 * @brief Return three for this receiver.
 * @param object Receiver of the call.
 * @return Three.
 */
s32 func_001EE260(void* object);

#ifdef __cplusplus
}
#endif

#endif
