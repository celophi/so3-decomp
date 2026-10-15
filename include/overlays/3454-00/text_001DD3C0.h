#ifndef SO3_OVERLAYS_3454_00_TEXT_001DD3C0_H
#define SO3_OVERLAYS_3454_00_TEXT_001DD3C0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Validate the checksum for the record fields beginning at 0x4C. */
s32 func_001E3BA0(const void* object);

/** Validate the checksum for the record fields beginning at 0x58. */
s32 func_001E7B20(const void* object);
/** Validate the checksum for the record fields beginning at 0x40. */
s32 func_001E7BD0(const void* object);
/** Validate the checksum for the record fields beginning at 0x34. */
s32 func_001E7C10(const void* object);

/** Validate the checksum for the record fields beginning at 0x70. */
s32 func_001E7CD0(const void* object);
/** Validate the checksum for the record fields beginning at 0x7C. */
s32 func_001E7E50(const void* object);
/** Validate the checksum for the record fields beginning at 0x76. */
s32 func_001E7EC0(const void* object);

/** Return the fixed value 0. */
s32 func_001DD400(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001DD4C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E9500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EA190(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001EC6F0(void* object);

/** Return the word at receiver offset 0xD58. */
u32 func_001E8DD0(const void* object);


/** Store the word at receiver offset 0x70. */
void func_001DE6B0(void* object, u32 value);

/** Set the ready byte and copy one 128-bit value into receiver slot 0. */
void func_001E0CB0(void* object, const unsigned __int128* value);

#ifdef __cplusplus
}
#endif

#endif
