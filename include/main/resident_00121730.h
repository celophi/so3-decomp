#ifndef SO3_MAIN_RESIDENT_00121730_H
#define SO3_MAIN_RESIDENT_00121730_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store a three-float vector and set the receiver's flag.
 * @param object Receiver object.
 * @param x First vector component.
 * @param y Second vector component.
 * @param z Third vector component.
 */
void func_00121730(u8* object, float x, float y, float z);

/**
 * @brief Store a quadword and set the ready flag.
 * @param object Receiver object.
 * @param value Quadword to store at offset 0x40.
 */
void func_00121770(void* object, const unsigned __int128* value);
/**
 * @brief Store a quadword and set the ready flag.
 * @param object Receiver object.
 * @param value Quadword to store at offset 0x40.
 */
void func_00121790(void* object, const unsigned __int128* value);
/**
 * @brief Store three float components and set the receiver's flag.
 * @param object Receiver object.
 * @param x First vector component.
 * @param y Second vector component.
 * @param z Third vector component.
 */
void func_001217B0(void* object, float x, float y, float z);
/**
 * @brief Return zero.
 * @param object Unused receiver.
 * @return Zero.
 */
s32 func_001217D0(void* object);
/**
 * @brief Return the optional subobject at offset 0x238.
 * @param object Receiver object.
 * @return The subobject when its flag at offset 0x2C0 is set, or null.
 */
void* func_001217E0(void* object);

/**
 * @brief Call the base handler with the receiver adjusted by 0x210 bytes.
 * @param object Adjusted receiver.
 * @return Result from the base handler.
 */
s32 func_00121800(void* object);
/**
 * @brief Call the base handler with the receiver adjusted by 0x210 bytes.
 * @param object Adjusted receiver.
 * @return Result from the base handler.
 */
void* func_00121810(void* object);
/**
 * @brief Call the base handler with the receiver adjusted by 0x210 bytes.
 * @param object Adjusted receiver.
 * @return Result from the base handler.
 */
void* func_00121820(void* object);
/**
 * @brief Call the base handler with the receiver adjusted by 0x78 bytes.
 * @param object Adjusted receiver.
 */
void func_00121830(void* object);
/**
 * @brief Call the base handler with the receiver adjusted by 0x78 bytes.
 * @param object Adjusted receiver.
 * @return Result from the base handler.
 */
s32 func_00121840(void* object);
/**
 * @brief Call the base handler with the receiver adjusted by 0x78 bytes.
 * @param object Adjusted receiver.
 * @return Result from the base handler.
 */
void* func_00121850(void* object);

/**
 * @brief Return -1.
 * @param object Unused receiver.
 * @return -1.
 */
s32 func_00121860(void* object);
/**
 * @brief Do nothing.
 * @param object Unused receiver.
 */
void func_00121870(void* object);
/**
 * @brief Do nothing.
 * @param object Unused receiver.
 */
void func_00121880(void* object);
/**
 * @brief Do nothing.
 * @param object Unused receiver.
 */
void func_00121890(void* object);

#ifdef __cplusplus
}
#endif

#endif
