#ifndef SO3_OVERLAYS_3253_00_TEXT_002957E0_H
#define SO3_OVERLAYS_3253_00_TEXT_002957E0_H

#include "types.h"

struct BattleObject5D4;
struct BattleObject2D;
struct BattleObject6C4;
struct BattleObject6CC;
struct BattleObjectB84;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Check whether any of the low five object flags are set.
 * @param object Battle object containing the flags.
 * @return True when at least one of the low five flags is set.
 */
bool func_002975E0(const BattleObject5D4* object);

/**
 * @brief Set the object's byte at offset 0x2D to 1.
 * @param object Battle object to update.
 */
void func_0029AA20(BattleObject2D* object);

/**
 * @brief Check whether the float at offset 0x6C4 is not at most zero.
 * @param object Battle object containing the float.
 * @return True for a positive value or NaN.
 */
bool func_002975F0(const BattleObject6C4* object);

/**
 * @brief Check whether the float at offset 0x6CC is not at most zero.
 * @param object Battle object containing the float.
 * @return True for a positive value or NaN.
 */
bool func_00297620(const BattleObject6CC* object);

/**
 * @brief Read bit 6 of byte 0x540, or return 1 without an attached object.
 * @param object Battle object to check; may be null.
 * @return Selected bit, or 1 if the object or attachment is absent.
 */
u8 func_002979E0(const BattleObjectB84* object);

/**
 * @brief Read bit 5 of byte 0x540, or return 1 without an attached object.
 * @param object Battle object to check; may be null.
 * @return Selected bit, or 1 if the object or attachment is absent.
 */
u8 func_00297A20(const BattleObjectB84* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00297220(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00299110(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00299120(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00299130(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0029BB40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029E690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029E6A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A2CB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A2DB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A2DC0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A2DD0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A2DE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A2DF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A2E00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A4AE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A4AF0(void* object);

#ifdef __cplusplus
}
#endif

#endif
