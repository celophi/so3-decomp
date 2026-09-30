#ifndef SO3_OVERLAYS_1067_00_TEXT_002DBC50_H
#define SO3_OVERLAYS_1067_00_TEXT_002DBC50_H

#include "types.h"
#include "overlays/1067-00/text_002DB1D0.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Run the receiver's virtual cleanup and release its object at offset 0x78.
 * @param object Receiver to clean up.
 */
void func_002DDA70(void* object);

/**
 * @brief Release the receiver's object at offset 0x8C and allocation at offset 0xA0.
 * @param object Receiver to clean up.
 */
void func_002DCD20(void* object);

#ifdef __cplusplus
}
#endif

#endif
