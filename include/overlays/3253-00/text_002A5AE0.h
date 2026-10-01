#ifndef SO3_OVERLAYS_3253_00_TEXT_002A5AE0_H
#define SO3_OVERLAYS_3253_00_TEXT_002A5AE0_H

#include "types.h"

struct BattleFloat714;

struct BattleFloat704;

struct BattleFloat6D0;

struct BattleObjectEC;

struct BattleObject1F8;

struct BattleObject101;

struct BattleObject178;

struct BattleParent23;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Raise the float at offset 0x714 to at least the given value.
 * @param object Battle object containing the float.
 * @param next New lower bound.
 */
void func_002AFF90(BattleFloat714* object, float next);

/**
 * @brief Raise the float at offset 0x704 to at least the given value.
 * @param object Battle object containing the float.
 * @param next New lower bound.
 */
void func_002AFFB0(BattleFloat704* object, float next);

/**
 * @brief Raise the float at offset 0x6D0 to at least the given value.
 * @param object Battle object containing the float.
 * @param next New lower bound.
 */
void func_002B0000(BattleFloat6D0* object, float next);

/**
 * @brief Clear three byte fields on the object.
 * @param object Battle object to update.
 */
void func_002B3380(BattleObjectEC* object);

/**
 * @brief Store a word at offset 0x1F8.
 * @param object Battle object to update.
 * @param value Word to store.
 */
void func_002B3690(BattleObject1F8* object, u32 value);

/**
 * @brief Clear the selected child byte at offset 0x204 when a child is present.
 * @param object Battle object containing the selected child.
 */
void func_002B3B60(BattleParent23* object);

/**
 * @brief Store a byte in the selected child at offset 0x209 when a child is present.
 * @param object Battle object containing the selected child.
 * @param value Value to store.
 */
void func_002B3BC0(BattleParent23* object, u8 value);

/**
 * @brief Set the selected child byte to 1 at offset 0x20B when a child is present.
 * @param object Battle object containing the selected child.
 */
void func_002B3BF0(BattleParent23* object);

/**
 * @brief Store a byte in the selected child at offset 0x208 when a child is present.
 * @param object Battle object containing the selected child.
 * @param value Value to store.
 */
void func_002B3CD0(BattleParent23* object, u8 value);

/**
 * @brief Store a float in the selected child at offset 0x90 when a child is present.
 * @param object Battle object containing the selected child.
 * @param value Value to store.
 */
void func_002B3DD0(BattleParent23* object, float value);

/**
 * @brief Set the byte at offset 0x101 to 1.
 * @param object Battle object to update.
 */
void func_002B5A30(BattleObject101* object);

/**
 * @brief Set the byte at offset 0x101 to 1.
 * @param object Battle object to update.
 */
void func_002B5A40(BattleObject101* object);

/**
 * @brief Set the byte at offset 0x101 to 1.
 * @param object Battle object to update.
 */
void func_002B5A50(BattleObject101* object);

/**
 * @brief Copy the word at offset 0x178 to offset 0x14.
 * @param object Battle object to update.
 */
void func_002B5A70(BattleObject178* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A6030(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002ACB80(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002ACB90(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B14D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B59C0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_002B59D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B5A20(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_002B5A60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002B5A80(void* object);

#ifdef __cplusplus
}
#endif

#endif
