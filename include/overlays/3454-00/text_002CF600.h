#ifndef SO3_OVERLAYS_3454_00_TEXT_002CF600_H
#define SO3_OVERLAYS_3454_00_TEXT_002CF600_H

#include "types.h"

/** Return whether the helper reports a nonzero low byte. */
s32 func_002D51E0(void* object, s32 arg2, s32 arg3);
/** Call the object cleanup helper, then clear the byte at receiver offset 0x2F88. */
void func_002D76F0(void* receiver);

#ifdef __cplusplus
extern "C" {
void func_002DEE60(u8* object, void* context);
#endif
/** Run the paired update helpers in order. */
void func_002D6ED0(void* object);
void func_002D6F00(void* object);
/** Call the nested update helper and set two receiver state bytes. */
void func_002D25E0(void* object);
/** Initialize the object and store the resolved field value at offset 0x600. */
void func_002DC4E0(void* receiver);
#ifdef __cplusplus
}
#endif

#endif
