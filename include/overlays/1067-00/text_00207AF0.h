#ifndef SO3_OVERLAYS_1067_00_TEXT_00207AF0_H
#define SO3_OVERLAYS_1067_00_TEXT_00207AF0_H

#include "types.h"
#include "overlays/1067-00/text_00207580.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Copy the receiver's float and aligned vector fields.
 * @param object Receiver to update.
 */
void func_00209B30(FieldCopyState* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_0020BCF0(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_0020BD00(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_0020BDA0(void* object);

/**
 * @brief Test whether the lookup helper returns an object.
 * @param object Receiver to query.
 * @return True when the helper returns a nonnull object.
 */
bool func_0020BDB0(void* object);

/**
 * @brief Run an update helper and finish the attached callback object.
 * @param object Callback receiver.
 */
void func_0020BD60(FieldCallbackState* object);

/**
 * @brief Forward the callback when the receiver is active.
 * @param object Callback receiver.
 * @param context Context passed to the callback.
 * @param enabled Value converted to a boolean for the callback.
 */
void func_0020BDD0(FieldCallbackState* object, void* context, u32 enabled);

/**
 * @brief Clear the attached callback object after notifying it.
 * @param object Callback receiver.
 */
void func_0020BE00(FieldCallbackState* object);

/**
 * @brief Store a word at offset 0xC4.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_0020BEF0(FieldAtC4* object, u32 value);

/**
 * @brief Store a size and its 128-byte rounded form.
 * @param object Receiver to update.
 * @param size Size to store and round.
 */
void func_0020BF50(FieldAlignedSize* object, u32 size);

/**
 * @brief Find a list entry with the requested kind.
 * @param object List owner.
 * @param kind Kind to search for.
 * @return One if found, otherwise zero.
 */
s32 func_0020CB20(FieldCbOwner* object, u16 kind);

/**
 * @brief Return the receiver unchanged.
 * @param object Receiver of the call.
 * @return The receiver.
 */
void* func_0020CE30(void* object);

/**
 * @brief Test bit zero of the byte at offset 0x81.
 * @param object Receiver to test.
 * @return True when the bit is set.
 */
bool func_00208C80(const FieldState81* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_00207EE0(void* object);

/**
 * @brief Set a target float and its change rate.
 * @param object Motion receiver.
 * @param target New target value.
 * @param duration Duration used for the rate.
 */
void func_00209780(FieldMotion* object, float target, float duration);

/**
 * @brief Set the first motion target and rate, substituting the fallback sentinel.
 * @param object Motion receiver.
 * @param target New value or sentinel.
 * @param duration Duration used for the rate.
 */
void func_00209BB0(FieldMotion2* object, float target, float duration);

/**
 * @brief Set the second motion target and rate, substituting the fallback sentinel.
 * @param object Motion receiver.
 * @param target New value or sentinel.
 * @param duration Duration used for the rate.
 */
void func_00209C20(FieldMotion3* object, float target, float duration);

/**
 * @brief Set or immediately apply the motion target.
 * @param object Motion receiver.
 * @param target New target value.
 * @param duration Duration used for the rate.
 */
void func_00209C90(FieldMotion4* object, float target, float duration);

#ifdef __cplusplus
}
#endif

#endif
