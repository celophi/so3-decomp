#ifndef SO3_OVERLAYS_3253_00_TEXT_003977C0_H
#define SO3_OVERLAYS_3253_00_TEXT_003977C0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Return bits 0 and 2 when the byte fields at offsets 0x3C and 0x3D are set. */
u32 func_003A5650(const u8* object);

/**
 * @brief Initialize the record's leading fields and pointer at offset 0x0C.
 * @param arg0 Record to initialize.
 * @return The initialized record.
 */
void* func_0039ECA0(void* arg0);

#ifdef __cplusplus
}
#endif

#endif
