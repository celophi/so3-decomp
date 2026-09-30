#ifndef SO3_OVERLAYS_1070_00_TEXT_00274A70_H
#define SO3_OVERLAYS_1070_00_TEXT_00274A70_H

#include "types.h"

/** Partial receiver whose word value is at offset 0x18. */
typedef struct FieldWordState18
{
    u8 unk00[0x18];
    u32 unk18;
} FieldWordState18;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the word value at offset 0x18.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_00281CE0(FieldWordState18* object, u32 value);

#ifdef __cplusplus
}
#endif

#endif
