#ifndef SO3_OVERLAYS_3253_00_TEXT_00356F40_H
#define SO3_OVERLAYS_3253_00_TEXT_00356F40_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the update flag and set the matching flag when value equals 0xB88.
 * @param object Receiver containing the comparison word and flag bytes.
 * @param value Value to compare with the receiver word at 0xB88.
 */
void func_00360E50(void* object, u32 value);

/** Update the receiver's child object when its initialization counter is zero. */
void func_003631B0(void* object);

/** Update the receiver's child object when its initialization counter is zero. */
void func_00363680(void* object);

/** Update the receiver's child object when its initialization counter is zero. */
void func_00363D50(void* object);

/** Forward the receiver to func_00309800. */
void func_00363C20(void* object);

/** Forward the receiver to func_00309800. */
void func_00363C40(void* object);

/** Forward the receiver to func_003452D0. */
void func_003663D0(void* object);

/** Forward the receiver to func_003452D0. */
void func_003663F0(void* object);

/** Forward the receiver to func_003452D0. */
void func_00366410(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00363D40(void* object);

/** Call the selected helper when the float at receiver offset 0x6B0 is zero. */
void func_00364B50(void* object);
void func_00364B90(void* object);
void func_003653C0(void* object);
void func_00365A30(void* object);
void func_00365A70(void* object);
void func_00366B30(void* object);

/** Return zero unless the float at 0x6B0 is zero, then return the helper result. */
s32 func_00364BD0(void* object);
s32 func_00365450(void* object);
s32 func_00365AB0(void* object);
s32 func_00366BD0(void* object);

#ifdef __cplusplus
}
#endif

#endif
