#ifndef SO3_OVERLAYS_3454_00_TEXT_00370690_H
#define SO3_OVERLAYS_3454_00_TEXT_00370690_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
void func_00375280(u8* receiver, void* value1, void* value2, void* value3);
#endif

/** Forward the receiver to the corresponding shared animation helper. */
void func_00370920(void* object);
void func_00370940(void* object);
void func_003730D0(void* object);
void func_003730F0(void* object);
void func_00373110(void* object);

/** Call the selected helper when the float at receiver offset 0x6A8 is zero. */
void func_00371850(void* object);
void func_00371890(void* object);
void func_003720C0(void* object);
void func_00372730(void* object);
void func_00372770(void* object);
void func_00373830(void* object);

/** Return zero unless the float at 0x6A8 is zero, then return the helper result. */
s32 func_003718D0(void* object);
s32 func_00372150(void* object);
s32 func_003727B0(void* object);
s32 func_003738D0(void* object);

/** Initialize the receiver's child object when its counter is zero. */
void func_00370A50(void* object);

/** Set the receiver word at offset 0x2F9C to one. */
void func_00373DC0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00370A40(void* object);

#ifdef __cplusplus
}
#endif

#endif
