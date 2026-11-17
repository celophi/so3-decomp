#ifndef SO3_MAIN_STATS_H
#define SO3_MAIN_STATS_H

#include "types.h"
#include "gs.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Return the word at receiver offset 0x14. */
u32 resident_stats_get_word14(const void* object);

/** Return the word at receiver offset 0x10. */
u32 resident_stats_get_word10(const void* object);

/** Return the word at receiver offset 0xC. */
u32 resident_stats_get_word0c(const void* object);

/** Return the word at receiver offset 0x8. */
u32 resident_stats_get_word08(const void* object);

/** Return the word at receiver offset 0x4. */
u32 resident_stats_get_word04(const void* object);

/** Return the word at receiver offset 0x0. */
u32 resident_stats_get_word00(const void* object);

/** Clamp the value to [0, 100], store it at offset 0x10, and return it. */
s32 resident_stats_set_word10(void* object, s32 value);

/** Clamp the value to [0, 255], store it at offset 0x8, and return it. */
s32 resident_stats_set_word08(void* object, s32 value);

/** Clamp the value to [0, 999], store it at offset 0x4, and return it. */
s32 resident_stats_set_word04(void* object, s32 value);

/** Clamp the value to [0, 9999], store it at offset 0, and return it. */
s32 resident_stats_set_word00(void* object, s32 value);

/** Clamp the value to [0, 999999999], store it at offset 0x14, and return it. */
s32 resident_stats_set_word14(void* object, s32 value);

/** Clamp the value to [0, 99999999], store it at offset 0xC, and return it. */
s32 resident_stats_set_word0c(void* object, s32 value);

#ifdef __cplusplus
}
#endif

#endif
