#ifndef SO3_OVERLAYS_1067_00_TEXT_00202240_H
#define SO3_OVERLAYS_1067_00_TEXT_00202240_H

#include "types.h"
#include "overlays/1067-00/text_00200710.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Combine the receiver and owner components into a packed resource key.
 * @param object Receiver supplying the key components.
 * @return The combined packed key.
 */
u32 func_00202240(const FieldPackedKeySource* object);

/**
 * @brief Test the float value when the object pointer and flag permit it.
 * @param object Receiver containing the pointer, flag and float value.
 * @return True when the object pointer is nonnull, bit zero is clear and the float value is not positive.
 */
bool func_00204420(const FieldFloatGateState7C* object);

/**
 * @brief Copy the known fields from one record to another.
 * @param dest Destination record.
 * @param src Source record.
 * @return The destination record.
 */
FieldAssign14* func_00202990(FieldAssign14* dest, const FieldAssign14* src);

/**
 * @brief Initialize two aligned vectors and clear related fields.
 * @param obj Transform receiver.
 */
void func_00202BF0(FieldTransform* obj);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_00203500(void* object);

/**
 * @brief Set the receiver flag after a successful helper call.
 * @param obj Receiver to update.
 * @return True if the helper succeeds.
 */
bool func_00203930(FieldState3BA* obj);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
s32 func_00203990(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_002039B0(void* object);

/**
 * @brief Test whether any of three vector components is nonzero.
 * @param obj Receiver containing the vector.
 * @return True when any component is nonzero.
 */
bool func_002039C0(const FieldVector180* obj);

/**
 * @brief Return the fixed value four.
 * @param object Receiver of the call.
 * @return Four.
 */
s32 func_00203A70(void* object);

/**
 * @brief Return the fixed value five.
 * @param object Receiver of the call.
 * @return Five.
 */
s32 func_00203B10(void* object);

/**
 * @brief Store a byte and set the related bit flag.
 * @param obj Receiver to update.
 * @param value Byte to store.
 */
void func_00204FA0(FieldByteState210* obj, u8 value);

/**
 * @brief Return the fixed value fourteen.
 * @param object Receiver of the call.
 * @return Fourteen.
 */
s32 func_00205700(void* object);

/**
 * @brief Copy a 16-byte value into the receiver.
 * @param object Receiver to update.
 * @param value Value to copy.
 */
void func_00205710(FieldSlot* object, const unsigned __int128* value);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_00205790(void* object);

/**
 * @brief Return the fixed value eleven.
 * @param object Receiver of the call.
 * @return Eleven.
 */
int func_002057A0(void* object);

/**
 * @brief Return the fixed value one.
 * @param object Receiver of the call.
 * @return One.
 */
int func_002057B0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002057C0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002057D0(void* object);

/**
 * @brief Test the word at offset 0x704.
 * @param object Receiver to test.
 * @return True when the word is nonzero.
 */
bool func_002057E0(const FieldState704* object);

/**
 * @brief Find the field at offset 0x79C.
 * @param object Containing receiver.
 * @return The field address.
 */
void* func_002057F0(FieldState79C* object);

/**
 * @brief Read the byte at offset 0x794.
 * @param object Receiver to read.
 * @return The byte value.
 */
u32 func_00205800(const FieldState794* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_00205810(void* object);

/**
 * @brief Find the field at offset 0x570.
 * @param object Containing receiver.
 * @return The field address.
 */
void* func_00205850(FieldState570* object);

/**
 * @brief Run the callback when nested state and helper permit it.
 * @param object Receiver to inspect.
 * @param arg First callback argument.
 * @param other Second callback argument.
 */
void func_00206020(FieldOuter870* object, void* arg, void* other);

/**
 * @brief Update target flags for marked list entries.
 * @param object List owner.
 * @param value Selects whether to clear or set the flag.
 */
void func_00206200(FieldListAC* object, bool value);

/**
 * @brief Run the helper and clear a receiver bit when an object is present.
 * @param object Receiver to update.
 */
void func_002067F0(FieldStateAD* object);

/**
 * @brief Run the callback when the state helper succeeds.
 * @param object Receiver to inspect.
 * @param arg First callback argument.
 * @param other Second callback argument.
 */
void func_00207360(FieldState820* object, void* arg, void* other);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002073C0(void* object);

/**
 * @brief Return the fixed value zero.
 * @param object Receiver of the call.
 * @return Zero.
 */
int func_002073D0(void* object);

/**
 * @brief Return the second argument.
 * @param object Receiver of the call.
 * @param value Value to return.
 * @return The second argument.
 */
void* func_002073E0(void* object, void* value);

/**
 * @brief Return the second argument.
 * @param object Receiver of the call.
 * @param value Value to return.
 * @return The second argument.
 */
void* func_002073F0(void* object, void* value);

/**
 * @brief Run the receiver cleanup helpers.
 * @param object Receiver to clean up.
 */
void func_00207400(FieldState634* object);

#ifdef __cplusplus
}
#endif

#endif
