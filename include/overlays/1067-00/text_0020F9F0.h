#ifndef SO3_OVERLAYS_1067_00_TEXT_0020F9F0_H
#define SO3_OVERLAYS_1067_00_TEXT_0020F9F0_H

#include "types.h"

/** Partial receiver with byte flags at offset 0x141C. */
typedef struct FieldFlags141C
{
    u8 unk00[0x141C];
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 rest : 6;
} FieldFlags141C;

/** Partial receiver with byte flags at offset 0x107C. */
typedef struct FieldFlags107C
{
    u8 unk00[0x107C];
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 rest : 6;
} FieldFlags107C;

/** Partial receiver with byte flags at offset 0x10A1. */
typedef struct FieldFlags10A1
{
    u8 unk00[0x10A1];
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 rest : 5;
} FieldFlags10A1;

typedef struct FieldState6C
{
    u8 unknown[0x6C];
    u16 unk6c;
} FieldState6C;

#ifdef __cplusplus
#include "overlays/1067-00/text_001DD3C0.h"

/** Partial Field object with vtable D_151C00 in main data and four words for its release call. */
class FieldClass151C00 : public FieldClass150070
{
public:
    /** @brief Destroy the object. */
    virtual ~FieldClass151C00();
    /** @brief Pass the four words to the Lib manager, then detach and delete this object. */
    virtual void func_001DF360();
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 unk20;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set bit 1 of the receiver byte at offset 0x141C.
 * @param object Receiver containing the flag byte.
 */
void func_0020FCE0(FieldFlags141C* object);

/**
 * @brief Set bit 2 of the receiver byte at offset 0x10A1.
 * @param object Receiver containing the flag byte.
 */
void func_00210DA0(FieldFlags10A1* object);

/**
 * @brief Set bit 1 of the receiver byte at offset 0x107C.
 * @param object Receiver containing the flag byte.
 */
void func_00212460(FieldFlags107C* object);

/**
 * @brief Set bit 0 of the receiver byte at offset 0x10A1.
 * @param object Receiver containing the flag byte.
 */
void func_00212480(FieldFlags10A1* object);

/**
 * @brief Set bit 1 of the receiver byte at offset 0x10A1.
 * @param object Receiver containing the flag byte.
 */
void func_002124A0(FieldFlags10A1* object);

/**
 * @brief Store a 16-bit value in the field at offset 0x6C.
 * @param object State containing the field.
 * @param value Value to store.
 */
void func_00210140(FieldState6C* object, u16 value);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_0020FDD0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_00211BF0(void* object);

/**
 * @brief Return the fixed value 13.
 * @param object Receiver or first argument; unused.
 * @return Always 13.
 */
s32 func_00212440(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00212450(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002124C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002124D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002124E0(void* object);

#ifdef __cplusplus
}
#endif

#endif
