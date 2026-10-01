#ifndef SO3_OVERLAYS_1067_00_TEXT_00202240_CALLBACKS_H
#define SO3_OVERLAYS_1067_00_TEXT_00202240_CALLBACKS_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Write a word to each attached field entry.
 * @param object Receiver with attached entries.
 * @param value Word to store.
 */
void func_00204070(void* object, u32 value);

/**
 * @brief Apply a float to the receiver's attached fields.
 * @param object Receiver with attached fields.
 * @param value Float to apply.
 */
void func_002040E0(void* object, float value);

#ifdef __cplusplus
}
#else
/**
 * @brief Reset the receiver's attached field state.
 * @param object Receiver to reset.
 */
void func_00202580(void* object);

/**
 * @brief Check whether the field state can be initialized.
 * @param object Receiver to check.
 * @return Nonzero when initialization succeeds.
 */
s32 func_00202620(void* object);

/**
 * @brief Update the attached field state.
 * @param object Receiver to update.
 * @param enable Boolean setting to apply.
 * @param update Nonzero to store the setting in the receiver.
 */
void func_00204370(void* object, u8 enable, s32 update);

/**
 * @brief Update flags for marked list entries.
 * @param object List owner.
 * @param value Boolean value passed through the C ABI.
 */
void func_00206200(void* object, u8 value);
#endif

#endif
