#ifndef SO3_OVERLAYS_3454_00_TEXT_002FFF90_H
#define SO3_OVERLAYS_3454_00_TEXT_002FFF90_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Call the object cleanup helper, then clear the byte at receiver offset 0x2FE8. */
void func_00307350(void* receiver);
/** Call the object cleanup helper, then clear the byte at receiver offset 0x570. */
void func_0030A850(void* receiver);
/** Initialize the object and store the resolved field value at offset 0x2FEC. */
void func_003093C0(void* receiver);

/**
 * @brief Set the paired update flag when value matches the receiver word at 0xB88.
 * @param object Receiver containing the comparison word and flag bytes.
 * @param value Value to compare with the receiver word at 0xB88.
 */
void func_00302FB0(void* object, u32 value);

#ifdef __cplusplus
}
#endif

#endif
