#ifndef SO3_OVERLAYS_1067_00_TEXT_001F9B70_H
#define SO3_OVERLAYS_1067_00_TEXT_001F9B70_H

#include "types.h"
#include "overlays/1067-00/text_001ED7E0.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the fixed value nine.
 * @param object Receiver of the call.
 * @return Nine.
 */
int func_001FA2A0(void* object);

/**
 * @brief Find and process indexed objects matching the next operand.
 * @param stream Operand stream.
 * @return One.
 */
s32 func_001FA2D0(FieldLateCommandStream* stream);

/**
 * @brief Pass the receiver to the release helper.
 * @param object Receiver to release.
 */
void func_001FC370(void* object);

/**
 * @brief Run two helpers on a receiver and another object.
 * @param object Receiver.
 * @param other Other object.
 */
void func_001FC390(void* object, void* other);

/**
 * @brief Link the receiver to a target and clear its former link.
 * @param object Receiver to link.
 * @param target Target object.
 */
void func_001FC3D0(FieldLatePointer40* object, FieldLatePointer40* target);

/**
 * @brief Reset two vectors and related receiver state.
 * @param object Receiver to reset.
 */
void func_001FC900(FieldLateLarge* object);

/**
 * @brief Reset the records and related receiver state.
 * @param object Record owner to reset.
 */
void func_001FC9C0(FieldLateRecords* object);

/**
 * @brief Find and process the receiver's selected object.
 * @param object Receiver to query.
 * @return One.
 */
s32 func_001FD340(void* object);

/**
 * @brief Decode up to four float arguments and pass them to the helper.
 * @param object Argument stream.
 * @param count Number of arguments.
 * @return One.
 */
s32 func_001FD390(FieldLateFloatArgs* object, u32 count);

/**
 * @brief Return the fixed value four.
 * @param object Receiver of the call.
 * @return Four.
 */
int func_001FD670(void* object);

/**
 * @brief Perform no action for this receiver.
 * @param object Receiver of the call.
 */
void func_001FD770(void* object);

/**
 * @brief Run cleanup helpers and invoke the receiver's first virtual method.
 * @param object Receiver to clean up.
 */
void func_001FD780(FieldLateDeleting* object);

#ifdef __cplusplus
}
#endif

#endif
