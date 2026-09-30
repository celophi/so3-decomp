#ifndef SO3_OVERLAYS_1067_00_TEXT_002CABC0_H
#define SO3_OVERLAYS_1067_00_TEXT_002CABC0_H

#include "types.h"
#include "overlays/1067-00/text_002C04E0.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set flag bits in the word at offset 0x1C.
 * @param object Receiver to update.
 * @param flags Bits to set.
 */
void func_002CB5B0(FieldFlags1C* object, u32 flags);

/**
 * @brief Return the fixed value nine.
 * @param object Receiver of the call.
 * @return Nine.
 */
int func_002CBAA0(void* object);

#ifdef __cplusplus
}
#endif

#endif
