#ifndef SO3_OVERLAYS_1067_00_TEXT_002CABC0_H
#define SO3_OVERLAYS_1067_00_TEXT_002CABC0_H

#include "types.h"
#include "overlays/1067-00/text_002C04E0.h"

/** Partial callback subobject whose table is D_15AD20. */
typedef struct FieldCallback15AD20
{
    u8 unk00[4];
    u8 unk04_0 : 1;
    u8 unk04_1_7 : 7;
} FieldCallback15AD20;

/** Partial receiver whose callback bases are at offsets 0x14 and 0x18. */
typedef struct FieldObject15ACF0
{
    u8 unk00[0x39];
    u8 unk39_0 : 1;
    u8 unk39_1 : 1;
    u8 unk39_2_7 : 6;
} FieldObject15ACF0;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set flag bits in the word at offset 0x1C.
 * @param object Receiver to update.
 * @param flags Bits to set.
 */
void func_002CB5B0(FieldFlags1C* object, u32 flags);

/**
 * @brief Return the fixed value nine.
 * @param object Receiver of the call.
 * @return Nine.
 */
int func_002CBAA0(void* object);

/**
 * @brief Set the callback subobject's first flag.
 * @param object Callback subobject to update.
 */
void func_002CCDF0(FieldCallback15AD20* object);

/**
 * @brief Set the receiver's second flag.
 * @param object Receiver to update.
 */
void func_002CCE10(FieldObject15ACF0* object);

#ifdef __cplusplus
}
#endif

#endif
