#ifndef SO3_OVERLAYS_1067_00_TEXT_001ED7E0_H
#define SO3_OVERLAYS_1067_00_TEXT_001ED7E0_H

#include "types.h"
#include "overlays/1067-00/text_001ED7E0_callbacks.h"

/** One 16-byte value also accessed as four floats. */
typedef unsigned __int128 FieldQword;
typedef union FieldVector4
{
    float floats[4];
    FieldQword packed;
} FieldVector4;

/** Partial receiver with three four-float values and a byte flag. */
typedef struct FieldVectorState50
{
    u8 unk00[0x20];
    FieldVector4 unk20;
    FieldVector4 unk30;
    FieldVector4 unk40;
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

/** Partial objects used by field helpers. */
typedef struct FieldValueAt18 { u8 pad[0x18]; u32 value; } FieldValueAt18;
typedef struct FieldFlagsAt78 { u8 pad[0x78]; u32 flags; } FieldFlagsAt78;
typedef struct FieldWordAt210 { u8 pad[0x210]; u32 value; } FieldWordAt210;

/** Opaque partial receiver types defined by the owning source unit. */
typedef struct FieldScriptCursorF32 FieldScriptCursorF32;
typedef struct FieldScriptCursorS8 FieldScriptCursorS8;
typedef struct FieldScriptCursorS32 FieldScriptCursorS32;
typedef struct FieldScriptCursorU32 FieldScriptCursorU32;
typedef struct FieldRecords FieldRecords;
typedef struct FieldScriptVec FieldScriptVec;
typedef struct FieldLateNodes FieldLateNodes;
typedef struct FieldLateFlag30 FieldLateFlag30;
typedef struct FieldLateRetryOwner FieldLateRetryOwner;
typedef struct FieldLateCommandStream FieldLateCommandStream;
typedef struct FieldLatePointer40 FieldLatePointer40;
typedef struct FieldLateLarge FieldLateLarge;
typedef struct FieldLateRecords FieldLateRecords;
typedef struct FieldLateFloatArgs FieldLateFloatArgs;
typedef struct FieldLateDeleting FieldLateDeleting;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mark the vector state and copy a 16-byte value into its first vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EDE60(FieldVectorState50* state, const FieldQword* input);

/**
 * @brief Mark the vector state and copy a 16-byte value into its second vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EDEC0(FieldVectorState50* state, const FieldQword* input);

/**
 * @brief Mark the vector state and copy a 16-byte value into its third vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EDF80(FieldVectorState50* state, const FieldQword* input);

/**
 * @brief Copy a 16-byte value into the first vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EE210(FieldVectorState50* state, const FieldQword* input);

/**
 * @brief Copy a 16-byte value into the first vector.
 * @param state Receiver to update.
 * @param input Value to copy.
 */
void func_001EE220(FieldVectorState50* state, const FieldQword* input);

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
 * @brief Clean up the receiver and add it to the resident queue.
 * @param object Receiver to clean up and queue.
 */
void func_001EE1E0(void* object);

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

/**
 * @brief Run two cleanup helpers on the receiver.
 * @param object Receiver to clean up.
 */
void func_001F0F90(void* object);

/**
 * @brief Return the fixed value 16.
 * @param object Receiver of the call.
 * @return 16.
 */
s32 func_001F1F60(void* object);

/**
 * @brief Clean up the receiver and add it to the resident queue.
 * @param object Receiver to clean up and queue.
 */
void func_001F1F70(void* object);

/**
 * @brief Copy the current float operand to two receiver objects.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F2070(FieldScriptCursorF32* cursor);

/**
 * @brief Store the current float operand in the receiver.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F23E0(FieldScriptCursorF32* cursor);

/**
 * @brief Reset the records and related state fields.
 * @param state Record owner to reset.
 */
void func_001F2DE0(FieldRecords* state);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
s32 func_001F2EE0(void* object);

/**
 * @brief Copy the current script operand to the shared word and field context.
 * @param cursor Current script operand cursor.
 * @param count Operand count supplied by the script dispatcher; unused.
 * @return Always 1.
 */
s32 func_001F2EB0(FieldScriptCursorU32* cursor, u32 count);

/**
 * @brief Pass the signed byte operand to the receiver.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F2EF0(FieldScriptCursorS8* cursor);

/**
 * @brief Process a sentinel or a sequence of integer operands.
 * @param cursor Operand cursor.
 * @param count Maximum number of operands to process.
 * @return One.
 */
s32 func_001F3120(FieldScriptCursorS32* cursor, u32 count);

/**
 * @brief Store the low byte of the current operand.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F4840(FieldScriptCursorS32* cursor);

/**
 * @brief Set or clear receiver flags from two operands.
 * @param cursor Operand cursor.
 * @return One.
 */
s32 func_001F49C0(FieldScriptCursorU32* cursor);

/**
 * @brief Copy three components and flags from the receiver to the cursor.
 * @param cursor Destination cursor.
 * @return One.
 */
s32 func_001F4CA0(FieldScriptVec* cursor);

/**
 * @brief Copy one 16-byte value to two destinations.
 * @param first First destination.
 * @param second Second destination.
 * @param source Value to copy.
 */
void func_001F5580(FieldQword* first, FieldQword* second, const FieldQword* source);

/**
 * @brief Subtract the first three components of one vector from another.
 * @param destination Result vector.
 * @param left Minuend vector.
 * @param right Subtrahend vector.
 */
void func_001F5590(FieldVector4* destination, const FieldVector4* left, const FieldVector4* right);

/**
 * @brief Copy a 16-byte value.
 * @param destination Destination value.
 * @param source Value to copy.
 */
void func_001F55E0(FieldQword* destination, const FieldQword* source);

/**
 * @brief Store a 32-bit value in the receiver.
 * @param object Receiver to update.
 * @param value Value to store.
 */
void func_001F55F0(FieldValueAt18* object, u32 value);

/**
 * @brief Set flag bits in the receiver.
 * @param object Receiver to update.
 * @param flags Bits to set.
 */
void func_001F8A70(FieldFlagsAt78* object, u32 flags);

/**
 * @brief Fill four floats with one value.
 * @param values Destination array.
 * @param value Value for each component.
 * @return The destination array.
 */
float* func_001F8A80(float* values, float value);

/**
 * @brief Copy a receiver word and run the copy helper.
 * @param destination Destination receiver.
 * @param source Source receiver.
 */
void func_001F8C40(FieldWordAt210* destination, const FieldWordAt210* source);

/**
 * @brief Find the subobject at offset 0x1D0.
 * @param object Containing object.
 * @return Subobject address.
 */
void* func_001F8C60(void* object);

/**
 * @brief Find the subobject at offset 0x1E0.
 * @param object Containing object.
 * @return Subobject address.
 */
void* func_001F8C70(void* object);

/**
 * @brief Find the subobject at offset 0x1F0.
 * @param object Containing object.
 * @return Subobject address.
 */
void* func_001F8C80(void* object);

/**
 * @brief Invoke the first virtual method on each record.
 * @param object Record owner.
 */
void func_001F9050(FieldLateNodes* object);

/**
 * @brief Run an initialization helper once and set the guard bit.
 * @param object Receiver containing the guard bit.
 */
void func_001F90D0(FieldLateFlag30* object);

/**
 * @brief Retry a buffer operation up to eight times while continuation is allowed.
 * @param owner Owner of the retry state.
 * @param buffer Buffer passed to the operation.
 * @param mode Selects the operation.
 * @return The operation result, or zero after retries stop.
 */
s32 func_001F9A80(FieldLateRetryOwner* owner, void* buffer, s32 mode);

#ifdef __cplusplus
}
#endif

#endif
