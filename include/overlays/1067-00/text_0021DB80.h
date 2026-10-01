#ifndef SO3_OVERLAYS_1067_00_TEXT_0021DB80_H
#define SO3_OVERLAYS_1067_00_TEXT_0021DB80_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct FieldObject1522C0 FieldObject1522C0;
typedef struct FieldScriptObject151D40 FieldScriptObject151D40;

/**
 * @brief Copy the current script word to the receiver at offset 0x18.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 0.
 */
s32 func_0021DE20(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Copy the current script word only while the guard at 0x424 is set.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return 0 when the word was copied, otherwise 1.
 */
s32 func_0021DE40(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Pop a float and two words from the receiver's script stack.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 0.
 */
s32 func_0021DE70(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Convert the current unsigned script word to the receiver float at 0x14.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021DEF0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 3.
 */
s32 func_0021FB30(FieldObject1522C0* object);

/**
 * @brief Detach this object and add it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_0021FB40(FieldObject1522C0* object);

/**
 * @brief Return the fixed value 2.
 * @param object Receiver or first argument; unused.
 * @return Always 2.
 */
s32 func_0021E840(void* object);

/**
 * @brief Copy the current script word to the resident halfword at 0xB0.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021E1C0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Copy the current script word to the resident halfword at 0xA8.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021E1E0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Copy the current script word to the resident halfword at 0xAA.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021E310(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Set or clear resident context bits using two script words.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021E160(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Set the receiver flag at 0x59D and its float at 0x14.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 0.
 */
s32 func_0021DF30(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Clear the runtime section's first four packed-flag bytes.
 * @param object Script callback receiver; unused.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021DF60(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Write the second script word to the indexed runtime flag selected by the first.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021DFB0(FieldScriptObject151D40* object, u32 count);

/**
 * @brief Read an indexed runtime flag and apply it to the receiver word at 0x424.
 * @param object Script callback receiver.
 * @param count Operand count supplied by the dispatcher; unused.
 * @return Always 1.
 */
s32 func_0021DFF0(FieldScriptObject151D40* object, u32 count);

#ifdef __cplusplus
}
#endif

#endif
