#ifndef SO3_OVERLAYS_0002_01_TEXT_0046AE20_H
#define SO3_OVERLAYS_0002_01_TEXT_0046AE20_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Update each active entry of the object's table with a boolean setting and an option flag.
 * @param object Object whose entry table is updated.
 * @param enable Boolean setting forwarded to each entry.
 * @param option Nonzero to select the alternate update path.
 */
void func_004728A0(void* object, s32 enable, s32 option);

#ifdef __cplusplus
}
#endif

#endif
