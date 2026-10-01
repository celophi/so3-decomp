#ifndef SO3_OVERLAYS_1067_00_TEXT_002F3310_H
#define SO3_OVERLAYS_1067_00_TEXT_002F3310_H

#include "types.h"
#include "overlays/1067-00/text_002F1B20.h"

#include "overlays/1067-00/text_001DD3C0.h"

typedef struct FieldByte60F3310 FieldByte60F3310;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store two in the receiver's byte at offset 0x60.
 * @param object Receiver containing the byte.
 */
void func_002F9760(FieldByte60F3310* object);


#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 9.
 */
s32 func_002F3860(FieldClass150070* object);
#endif

#ifdef __cplusplus
}
#endif

#endif
