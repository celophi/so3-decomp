#ifndef SO3_OVERLAYS_1067_00_TEXT_001F9B70_H
#define SO3_OVERLAYS_1067_00_TEXT_001F9B70_H

#include "types.h"
#include "overlays/1067-00/text_001ED7E0.h"

typedef struct FieldScriptCursorU16 FieldScriptCursorU16;
typedef struct FieldHeldObject20 FieldHeldObject20;
typedef struct FieldFlagScriptCursor FieldFlagScriptCursor;
typedef struct FieldScriptCursorF14 FieldScriptCursorF14;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Detach the receiver from its owner and append it to the resident object queue.
 * @param object Receiver to detach and append.
 */
void func_001FA270(void* object);

/**
 * @brief Return the fixed value nine.
 * @param object Receiver of the call.
 * @return Nine.
 */
int func_001FA2A0(void* object);

/**
 * @brief Store the low bit of the current script word in the resident flag byte.
 * @param cursor Script cursor pointing to the current word.
 * @return Always one.
 */
s32 func_001FA2B0(FieldScriptCursorU32* cursor);

/**
 * @brief Find and process indexed objects matching the next operand.
 * @param stream Operand stream.
 * @return One.
 */
s32 func_001FA2D0(FieldLateCommandStream* stream);

/**
 * @brief Pass the current script word to the target in the resident context.
 * @param cursor Script cursor pointing to the current word.
 * @return Always one.
 */
s32 func_001FAB10(FieldScriptCursorU32* cursor);

/**
 * @brief Detach the receiver from its owner and append it to the resident object queue.
 * @param object Receiver to detach and append.
 */
void func_001FBD10(void* object);

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
 * @brief Store two nonnegative script values in resident context bytes.
 * @param cursor Script cursor containing two values.
 * @return Always one.
 */
s32 func_001FB8C0(FieldScriptCursorS32* cursor);

/**
 * @brief Invoke the resident helper when cursor flag bit 0 is set.
 * @param cursor Flagged script cursor pointing to the current word.
 * @return Always one.
 */
s32 func_001FB9D0(FieldFlagScriptCursor* cursor);

/**
 * @brief Clear the receiver's held object state, detach it, and queue it.
 * @param object Receiver to clear and queue.
 */
void func_001FC980(FieldHeldObject20* object);

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
 * @brief Set the cursor's float state to one when a context entry is active.
 * @param cursor Script cursor containing the float state and entry key.
 * @return Zero when active, otherwise one.
 */
s32 func_001FCC20(FieldScriptCursorF14* cursor);

/**
 * @brief Pass the current script word to the optional resident target.
 * @param cursor Script cursor pointing to the current word.
 * @return Always one.
 */
s32 func_001FCBD0(FieldScriptCursorU32* cursor);

/**
 * @brief Pass two script words to the resident context and advance one word.
 * @param cursor Script cursor to read and advance.
 * @return Always one.
 */
s32 func_001FCC80(FieldScriptCursorU32* cursor);

/**
 * @brief Pass the current script halfword to the resident context.
 * @param cursor Script cursor pointing to the halfword.
 * @return Always one.
 */
s32 func_001FCD20(FieldScriptCursorU16* cursor);

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
