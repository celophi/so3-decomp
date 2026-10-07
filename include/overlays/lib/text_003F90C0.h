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

/**
 * @brief Resolve a detail entry and return its selected values.
 * @param detail Opaque detail record.
 * @param code Signed record code, from one through ten.
 * @param index Signed entry index, from zero through thirty-one.
 * @param kind Optional destination for the entry kind.
 * @param value Optional destination for the entry value.
 * @param result_index Optional destination for the result index.
 * @param remainder Optional destination for the remaining value.
 * @param mode Full-word lookup mode.
 * @return Lookup result, or zero for invalid code or index.
 */
s32 func_408EA0(void* detail, s32 code, s32 index, s32* kind, s32* value, s32* result_index, s32* remainder, s32 mode);

/**
 * @brief Resolve a protected detail entry and return its selected values.
 * @param detail Detail record containing the encoded entry arrays.
 * @param code Signed record code, from one through ten.
 * @param index Signed entry index, from zero through forty-one.
 * @param kind Optional destination for the entry kind.
 * @param value Optional destination for the entry value.
 * @param result_index Optional destination for the result index.
 * @param remainder Optional destination for the remaining value.
 * @return Signed lookup result, or zero when the entry is unavailable.
 */
s32 func_00408850(void* detail, s32 code, s32 index, s32* kind, s32* value, s32* result_index, s32* remainder);

#ifdef __cplusplus
}
#endif

#endif
