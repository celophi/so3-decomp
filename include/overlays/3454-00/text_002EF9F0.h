#ifndef SO3_OVERLAYS_3454_00_TEXT_002EF9F0_H
#define SO3_OVERLAYS_3454_00_TEXT_002EF9F0_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void func_002F5480(void* object);
/** Initialize the object and store the resolved field value at offset 0x600. */
void func_002EFE00(void* receiver);
/** Initialize the object and store the resolved field value at offset 0x600. */
void func_002F09B0(void* receiver);
/** Initialize the object and store the resolved field value at offset 0x460. */
void func_002F18C0(void* receiver);

/**
 * @brief Set the paired update flag when value matches the receiver word at 0xB88.
 * @param object Receiver containing the comparison word and flag bytes.
 * @param value Value to compare with the receiver word at 0xB88.
 */
void func_002F6F20(void* object, u32 value);

/**
 * @brief Set the paired update flag when value matches the receiver word at 0xB88.
 * @param object Receiver containing the comparison word and flag bytes.
 * @param value Value to compare with the receiver word at 0xB88.
 */
void func_002FD1D0(void* object, u32 value);

/**
 * @brief Set the paired update flag when value matches the receiver word at 0xB88.
 * @param object Receiver containing the comparison word and flag bytes.
 * @param value Value to compare with the receiver word at 0xB88.
 */
void func_002FF350(void* object, u32 value);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002F41A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002F41B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002F41C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002F4E30(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002F4E40(void* object);


/** Store the byte constant at receiver offset 0x39D. */
void func_002F41D0(void* object);

/** Run the paired update helpers in order. */
void func_002F44B0(void* object);
void func_002F4680(void* object);

#ifdef __cplusplus
}
#endif

#endif
