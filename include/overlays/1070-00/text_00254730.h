#ifndef SO3_OVERLAYS_1070_00_TEXT_00254730_H
#define SO3_OVERLAYS_1070_00_TEXT_00254730_H

#include "overlays/1070-00/text_001E2B40.h"

/** Partial receiver whose word flags include a mirrored bit in a flag byte. */
typedef struct FieldMirroredFlags
{
    u8 unk00[0x1D0];
    void* unk1d0;
    u8 unk1d4[8];
    u32 unk1dc;
    u8 unk1e0[0x16];
    u8 unk1f6_0 : 1;
    u8 unk1f6_1 : 1;
    u8 unk1f6_2_7 : 6;
} FieldMirroredFlags;

/** Partial receiver containing two object pointers and resettable state. */
typedef struct FieldPointerReset66
{
    u8 unk00[0x10];
    u32 unk10;
    void* unk14;
    void* unk18;
    u8 unk1c[0x4A];
    u8 unk66_0 : 1;
    u8 unk66_1 : 1;
    u8 unk66_2_7 : 6;
} FieldPointerReset66;

/** Partial receiver with a circular-list sentinel and keyed float state. */
typedef struct FieldKeyedFloatState98
{
    FieldListNode link;
    u8 unk0c[0x7C];
    void* unk88;
    u8 unk8c[8];
    s32 unk94;
    u32 unk98;
    float unk9c;
    float unka0;
    float unka4;
    float unka8;
    float unkac;
    float unkb0;
    u16 unkb4;
    u8 unkb6[2];
    u32 unkb8;
} FieldKeyedFloatState98;

/** Partial circular-list element carrying a packed key at offset 0x54. */
typedef struct FieldKeyedListElement54
{
    FieldListNode link;
    u8 unk0c[0x48];
    u32 unk54;
} FieldKeyedListElement54;

/** Partial list owner with a sentinel link at offset 0x14. */
typedef struct FieldKeyedFlagList14
{
    u8 unk00[0x14];
    FieldListNode unk14;
} FieldKeyedFlagList14;

/** Partial receiver containing the keyed-list owner at offset 0xD8. */
typedef struct FieldKeyedFlagOwnerD8
{
    u8 unk00[0xD8];
    FieldKeyedFlagList14* unkd8;
} FieldKeyedFlagOwnerD8;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Store the word flags and mirror bit one into the flag byte.
 * @param object Receiver to update.
 * @param value Word flags to store.
 */
void func_0025BB70(FieldMirroredFlags* object, u32 value);

/**
 * @brief Clear two object pointers, flag bit one, and the leading state word.
 * @param object Receiver to reset.
 */
void func_00262060(FieldPointerReset66* object);

/**
 * @brief Store the data pointer and flags, clear bit zero, and mirror flag bit one.
 * @param object Receiver to update.
 * @param data Data allocation pointer to store.
 * @param flags Word flags to store.
 */
void func_0025BBA0(FieldMirroredFlags* object, void* data, u32 flags);

/**
 * @brief Set the packed key and float state, and merge the supplied flags.
 * @param object Receiver to update.
 * @param key Packed key to store.
 * @param flags Halfword flags combined with the preserved high byte.
 * @param first Value for offset 0x9C.
 * @param second Value for offset 0xA0.
 * @param third Value for offset 0xA8.
 * @param fourth Value for offset 0xB0.
 * @param fifth Value for offset 0xA4.
 */
void func_00263B20(FieldKeyedFloatState98* object, u32 key, u16 flags, float first, float second, float third, float fourth, float fifth);

/**
 * @brief Find a circular-list element with the requested packed key.
 * @param object Receiver containing the circular-list sentinel.
 * @param key Packed key to find.
 * @return The matching element, or null after returning to the sentinel.
 */
FieldKeyedListElement54* func_00263230(FieldKeyedFloatState98* object, u32 key);

/**
 * @brief Reset the keyed list element and store the supplied signed value as a float.
 * @param object Receiver containing the keyed list.
 * @param key Key to find.
 * @param value Signed value forwarded to the matching element.
 */
void func_00259EC0(FieldKeyedFlagOwnerD8* object, u32 key, s32 value);

/**
 * @brief Return the fixed value 16.
 * @param object Receiver or first argument; unused.
 * @return Always 16.
 */
s32 func_00255410(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00255420(void* object);

/**
 * @brief Return the fixed value 9.
 * @param object Receiver or first argument; unused.
 * @return Always 9.
 */
s32 func_00257120(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_0025C390(void* object);

/**
 * @brief Return the fixed value 3.
 * @param object Receiver or first argument; unused.
 * @return Always 3.
 */
s32 func_00261490(void* object);

#ifdef __cplusplus
}
#endif

#endif
