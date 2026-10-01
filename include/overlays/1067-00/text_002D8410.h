#ifndef SO3_OVERLAYS_1067_00_TEXT_002D8410_H
#define SO3_OVERLAYS_1067_00_TEXT_002D8410_H

#include "types.h"
#include "overlays/1067-00/text_002D5260.h"

#include "overlays/1067-00/text_001DD3C0.h"

/** Partial 0x74-byte receiver whose byte at offset 0x70 contains state flags. */
struct FieldState2D9F80
{
    u8 unk00[0x70];
    u8 unk70_0_1 : 2;
    u8 unk70_2 : 1;
    u8 unk70_3_7 : 5;
};

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
/**
 * @brief Report this object's type value.
 * @param object Callback receiver.
 * @return Always 4.
 */
s32 func_002D8410(FieldClass150070* object);
#endif

/**
 * @brief Clear this object's active state and attached resources.
 * @param object Receiver to clear.
 */
void func_002D9730(FieldClass150070* object);

/**
 * @brief Clear, detach, and delete the object through its virtual destructor.
 * @param object Receiver to destroy.
 */
void func_002D98A0(FieldClass150070* object);

/**
 * @brief Set state flag 2 on the object.
 * @param object Receiver whose flags are updated.
 */
void func_002D9F80(FieldState2D9F80* object);

#ifdef __cplusplus
}
#endif

#endif
