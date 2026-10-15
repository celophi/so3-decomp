#ifndef SO3_OVERLAYS_3454_00_TEXT_0021D990_H
#define SO3_OVERLAYS_3454_00_TEXT_0021D990_H

#include "types.h"

typedef struct N54Owner64_0021D990 N54Owner64_0021D990;

#ifdef __cplusplus
extern "C" {
void* func_002264B0(void* receiver);
/** Initialize the receiver and select state 6. */
void* func_00226670(void* object);
/** Initialize the receiver and select state 5. */
void* func_00226900(void* object);
#endif

/** Forward the receiver to func_4D00B0. */
void func_00228A90(void* object);

/** Store the byte at receiver offset 0x3D. */
void func_00227330(void* object, u8 value);

/** Return the receiver address at byte offset 0x20. */
const float* func_00227360(const void* object);

/** Set the active byte and notify the embedded receiver. */
void func_00228AB0(N54Owner64_0021D990* object);

#ifdef __cplusplus
}
#endif

#endif
