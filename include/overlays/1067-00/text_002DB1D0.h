#ifndef SO3_OVERLAYS_1067_00_TEXT_002DB1D0_H
#define SO3_OVERLAYS_1067_00_TEXT_002DB1D0_H

#include "types.h"
#include "overlays/1067-00/text_002DA0D0.h"
#include "overlays/1067-00/text_001DD3C0.h"

/** Partial receiver with a state byte at offset 0x60. */
typedef struct FieldObjectDBB50
{
    u8 unk00[0x60];
    u8 unk60_0 : 1;
    u8 unk60_1_7 : 7;
} FieldObjectDBB50;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Detach this object and add it to the resident object queue.
 * @param object Object to detach and queue.
 */
void func_002DB280(FieldClass150070* object);

/**
 * @brief Set bit zero of the byte at offset 0x60.
 * @param object Object with the state byte.
 */
void func_002DBB50(FieldObjectDBB50* object);

#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 5.
 */
s32 func_002DB270(FieldClass150070* object);
#endif

#ifdef __cplusplus
}
#endif

#endif
