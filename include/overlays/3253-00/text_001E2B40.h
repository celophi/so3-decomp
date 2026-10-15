#ifndef SO3_OVERLAYS_3253_00_TEXT_001E2B40_H
#define SO3_OVERLAYS_3253_00_TEXT_001E2B40_H

#include "types.h"

struct BattleField70;
struct BattleFieldD68;
struct BattleHalfwordPair;
struct BattleVectorSlot50;

#ifdef __cplusplus
extern "C" {
#endif

/** Validate the checksum for the record fields beginning at 0x4C. */
s32 func_001EAEF0(const void* object);

/** Validate the checksum for the record fields beginning at 0x58. */
s32 func_001EEDF0(const void* object);
/** Validate the checksum for the record fields beginning at 0x40. */
s32 func_001EEEA0(const void* object);
/** Validate the checksum for the record fields beginning at 0x34. */
s32 func_001EEEE0(const void* object);

/** Validate the checksum for the record fields beginning at 0x70. */
s32 func_001EEFA0(const void* object);
/** Validate the checksum for the record fields beginning at 0x7C. */
s32 func_001EF120(const void* object);
/** Validate the checksum for the record fields beginning at 0x76. */
s32 func_001EF190(const void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001E2B80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001E2C40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_001F07E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_001F13B0(void* object);

/**
 * @brief Store a word in the receiver's field at offset 0x70.
 * @param object Receiver.
 * @param value Word to store.
 */
void func_001E5D40(BattleField70* object, u32 value);

/**
 * @brief Mark a vector slot ready and copy a 128-bit value into it.
 * @param object Receiver containing the slot and ready flag.
 * @param value Value to copy.
 */
void func_001E85A0(BattleVectorSlot50* object, const unsigned __int128* value);

/**
 * @brief Store and return the receiver's second signed halfword.
 * @param object Halfword pair to update.
 * @param value Value to store.
 * @return Stored signed halfword.
 */
s16 func_001ECC50(BattleHalfwordPair* object, s16 value);

/**
 * @brief Store and return the receiver's first signed halfword.
 * @param object Halfword pair to update.
 * @param value Value to store.
 * @return Stored signed halfword.
 */
s16 func_001ECC60(BattleHalfwordPair* object, s16 value);

/**
 * @brief Read the receiver's word at offset 0xD68.
 * @param object Receiver.
 * @return Stored word.
 */
u32 func_001F02B0(const BattleFieldD68* object);

#ifdef __cplusplus
}
#endif

#endif
