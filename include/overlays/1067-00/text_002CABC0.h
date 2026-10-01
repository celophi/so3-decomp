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

/** Partial receiver with state bits at 0x4B5-0x4B6 and a mask at 0x4C0. */
typedef struct FieldStateCB100
{
    u8 unk00[0x4B5];
    u8 unk4b5_0 : 1;
    u8 unk4b5_1 : 1;
    u8 unk4b5_2 : 1;
    u8 unk4b5_3 : 1;
    u8 unk4b5_4 : 1;
    u8 unk4b5_5 : 1;
    u8 unk4b5_6 : 1;
    u8 unk4b5_7 : 1;
    u8 unk4b6_0 : 1;
    u8 unk4b6_1 : 1;
    u8 unk4b6_2 : 1;
    u8 unk4b6_3_7 : 5;
    u8 unk4b7[9];
    u32 mask;
} FieldStateCB100;

struct FieldNameEntry;
struct FieldNameGroup;
struct FieldNameOwner;

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
 * @brief Apply selected state-bit updates and remember the mask.
 * @param object Receiver to update.
 * @param mask Bits selecting which state fields to update.
 */
void func_002CB100(FieldStateCB100* object, u32 mask);

/**
 * @brief Find a record whose name matches the receiver's name.
 * @param object Receiver containing the name to find.
 * @param group_ptr Pointer to the record group.
 * @return Matching record, or null if none matches.
 */
FieldNameEntry* func_002CB9D0(FieldNameOwner* object, FieldNameGroup** group_ptr);

/**
 * @brief Sum the two resource sizes rounded up to 2,048-byte boundaries.
 * @return Combined aligned size.
 */
u32 func_002CBAE0();

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
