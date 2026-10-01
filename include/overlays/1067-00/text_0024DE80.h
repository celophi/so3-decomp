#ifndef SO3_OVERLAYS_1067_00_TEXT_0024DE80_H
#define SO3_OVERLAYS_1067_00_TEXT_0024DE80_H

#include "types.h"

/** Partial receiver with a flag byte after its leading word. */
typedef struct FieldObject11CValues FieldObject11CValues;

typedef struct FieldObject153730
{
    u8 unk00[4];
    u8 bit0 : 1;
    u8 rest : 7;
    u8 unk05[0x5B];
    u8 unk60;
} FieldObject153730;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set bit zero of the receiver byte at offset 4.
 * @param object Receiver containing the flag byte.
 */
void func_00254180(FieldObject153730* object);

/**
 * @brief Store the byte value 9 at receiver offset 0x60.
 * @param object Receiver containing the byte field.
 */
void func_002541B0(FieldObject153730* object);

/**
 * @brief Report the fixed category for this object.
 * @param object Receiver.
 * @return Always 3.
 */
s32 func_002541A0(FieldObject153730* object);

/**
 * @brief Pass the receiver's attached value pair to a helper, then update the receiver.
 * @param object Receiver containing the attached value pair.
 */
void func_002507B0(FieldObject11CValues* object);

/**
 * @brief Process a value on a field target.
 * @param target Target receiver.
 * @param value Value to process.
 */
void func_0024E860(void* target, u32 value);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0024E610(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0024E620(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0024E630(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0024E640(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0024E650(void* object);

#ifdef __cplusplus
}
#endif

#endif
