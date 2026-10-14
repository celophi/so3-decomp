#ifndef SO3_OVERLAYS_3253_00_TEXT_002C5F00_H
#define SO3_OVERLAYS_3253_00_TEXT_002C5F00_H

#include "types.h"

union BattleQuaternionView;
struct BattleHalfword6EView;
struct BattleVector4View;
struct BattleObject5FA0View;
struct BattleObject67A0View;
struct BattleObject7760View;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize a four-component value to the identity quaternion.
 * @param value Value to initialize.
 */
void func_002C5F60(BattleQuaternionView* value);

/**
 * @brief Store a halfword at receiver offset 0x6E.
 * @param object Receiver.
 * @param value Halfword to store.
 */
void func_002C5F70(BattleHalfword6EView* object, u16 value);

/**
 * @brief Set all four components to the supplied value.
 * @param value Four-component value to update.
 * @param component Value to store in each component.
 * @return The updated value.
 */
BattleVector4View* func_002C5F80(BattleVector4View* value, float component);

/**
 * @brief Initialize the receiver and clear its words at offsets 0x210 and 0x214.
 * @param object Receiver to initialize.
 * @return The initialized receiver.
 */
BattleObject5FA0View* func_002C5FA0(BattleObject5FA0View* object);

/**
 * @brief Initialize the receiver's observed fields.
 * @param object Receiver to initialize.
 * @return The initialized receiver.
 */
BattleObject67A0View* func_002C67A0(BattleObject67A0View* object);

/**
 * @brief Set the receiver's high flag bit when its state check succeeds.
 * @param object Receiver to update.
 * @return One when the state check succeeds; otherwise zero.
 */
s32 func_002C7760(BattleObject7760View* object);

/**
 * @brief Set the receiver's byte at offset 0x391 to one.
 * @param object Receiver to update.
 */
void func_002CBED0(void* object);

#ifdef __cplusplus
}
#endif

#endif
