#ifndef SO3_OVERLAYS_1067_00_TEXT_0028E530_H
#define SO3_OVERLAYS_1067_00_TEXT_0028E530_H

#include "types.h"

typedef struct FieldObject157160 FieldObject157160;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Apply a packed mode, flags, and three floats to the receiver.
 * @param object Receiver to update.
 * @param index Selected index, or -1.
 * @param mode Mode byte.
 * @param flags Flag byte.
 * @param x First float.
 * @param y Second float.
 * @param z Third float.
 */
void func_0028F5B0(void* object, s32 index, u8 mode, u8 flags, float x, float y, float z);

/**
 * @brief Apply five float values to the receiver.
 * @param object Receiver to update.
 * @param first First float.
 * @param second Second float.
 * @param third Third float.
 * @param fourth Fourth float.
 * @param fifth Fifth float.
 */
void func_0028F710(void* object, float first, float second, float third, float fourth, float fifth);

/**
 * @brief Report the fixed type value for this receiver.
 * @param object Receiver to inspect.
 * @return Always 3.
 */
s32 func_00291410(FieldObject157160* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00291B60(void* object);

#ifdef __cplusplus
}
#endif

#endif
