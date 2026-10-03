#ifndef SO3_OVERLAYS_LIB_TEXT_003F90C0_H
#define SO3_OVERLAYS_LIB_TEXT_003F90C0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read the selected pair of scaled byte values from the Lib table.
 * @param index Signed table row, defaulting to zero outside zero through nine.
 * @param component Pair within the row, defaulting to zero outside zero through two.
 * @param first Optional destination for the first value.
 * @param second Optional destination for the second value.
 */
void func_00408600(s32 index, s32 component, float* first, float* second);

#ifdef __cplusplus
}
#endif

#endif
