#ifndef SO3_OVERLAYS_1067_00_TEXT_0023D390_H
#define SO3_OVERLAYS_1067_00_TEXT_0023D390_H

#include "types.h"

/** Partial receiver with a bit flag at byte offset 0x4B5. */
typedef struct FieldFlags4B5
{
    u8 unk00[0x4B5];
    u8 bit0 : 1;
    u8 rest : 7;
} FieldFlags4B5;

/** Partial receiver with a bit flag at byte offset 0x8C. */
typedef struct FieldFlags8C
{
    u8 unk00[0x8C];
    u8 low : 5;
    u8 bit5 : 1;
    u8 high : 2;
} FieldFlags8C;

/** Partial receiver with an aligned 128-bit slot at offset 0x20. */
typedef struct FieldVectorSlot20
{
    u8 unk00[0x20];
    unsigned __int128 value;
} FieldVectorSlot20;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set bit zero of the receiver byte at offset 0x4B5.
 * @param object Receiver containing the flag byte.
 * @param value Value to assign to the bit.
 */
void func_0023D3C0(FieldFlags4B5* object, u8 value);

/**
 * @brief Update bit five of the receiver byte when enabled.
 * @param object Receiver containing the flag byte.
 * @param value Bit is set when this value is zero.
 * @param enable Nonzero to update the bit.
 */
void func_0023D3E0(FieldFlags8C* object, u32 value, u32 enable);

/**
 * @brief Copy a 128-bit value into the receiver when one is supplied.
 * @param object Receiver containing the destination slot.
 * @param value Optional aligned value to copy.
 */
void func_0023D420(FieldVectorSlot20* object, const unsigned __int128* value);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0023D390(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0023D3A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0023D3B0(void* object);

#ifdef __cplusplus
}
#endif

#endif
