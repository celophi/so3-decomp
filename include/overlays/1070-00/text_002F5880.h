#ifndef SO3_OVERLAYS_1070_00_TEXT_002F5880_H
#define SO3_OVERLAYS_1070_00_TEXT_002F5880_H

#include "types.h"

/** Partial reset prefix with an opaque word and four halfwords. */
typedef struct FieldResetState18
{
    u8 unk00[0x18];
    u32 unk18;
    u8 unk1c[4];
    u16 unk20;
    u8 unk22[2];
    s16 unk24;
    s16 unk26;
    s16 unk28;
} FieldResetState18;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clear a word and halfword, and set three halfwords to minus one.
 * @param object Receiver to reset.
 */
void func_002F5880(FieldResetState18* object);

#ifdef __cplusplus
}
#endif

#endif
