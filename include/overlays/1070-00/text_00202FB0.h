#ifndef SO3_OVERLAYS_1070_00_TEXT_00202FB0_H
#define SO3_OVERLAYS_1070_00_TEXT_00202FB0_H

#include "overlays/1070-00/text_00284BF0.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read the object pointer at offset 0x7C.
 * @param object Receiver reached through the context-0x08 object.
 * @return The stored object pointer.
 */
void* func_0020CBC0(const FieldContext08Target* object);

/**
 * @brief Read the object pointer at offset 0xDC.
 * @param object Object reached through context field 0x08.
 * @return The stored object pointer.
 */
FieldContext08Target* func_0020CBD0(const FieldContext08* object);

/**
 * @brief Read the Field context pointer at offset 0x08.
 * @param ref Reference to the Field context.
 * @return The stored object pointer.
 */
FieldContext08* func_0020CBE0(const FieldContextRef* ref);

/**
 * @brief Read the halfword value at offset 0x6E.
 * @param object Object containing the halfword.
 * @return The stored unsigned halfword.
 */
u16 func_0020CC20(const FieldObjectFlags* object);

#ifdef __cplusplus
}
#endif

#endif
