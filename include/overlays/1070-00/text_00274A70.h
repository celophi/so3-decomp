#ifndef SO3_OVERLAYS_1070_00_TEXT_00274A70_H
#define SO3_OVERLAYS_1070_00_TEXT_00274A70_H

#include "types.h"

/** Partial receiver whose word value is at offset 0x18. */
typedef struct FieldWordState18
{
    u8 unk00[0x18];
    u32 unk18;
} FieldWordState18;

/** Partial target whose float value is at offset 0x90. */
typedef struct FieldFloatTarget90
{
    u8 unk00[0x90];
    float unk90;
} FieldFloatTarget90;

/** Partial receiver owning a float value and an optional linked target. */
typedef struct FieldFloatOwner540
{
    u8 unk00[0x144];
    FieldFloatTarget90* unk144;
    u8 unk148[0x3F8];
    float unk540;
} FieldFloatOwner540;

/** Partial linked record containing an object pointer. */
typedef struct FieldPointerState48
{
    u8 unk00[0x48];
    void* unk48;
} FieldPointerState48;

/** Partial receiver containing an optional linked record. */
typedef struct FieldPointerOwner588
{
    u8 unk00[0x588];
    FieldPointerState48* unk588;
} FieldPointerOwner588;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the word value at offset 0x18.
 * @param object Receiver to update.
 * @param value Word to store.
 */
void func_00281CE0(FieldWordState18* object, u32 value);

/**
 * @brief Set the receiver float and mirror it to the linked target when present.
 * @param object Receiver to update.
 * @param value Float value to store.
 */
void func_00276D80(FieldFloatOwner540* object, float value);

/**
 * @brief Read the object pointer through the optional linked record.
 * @param object Receiver to inspect.
 * @return The stored object pointer, or null when the linked record is absent.
 */
void* func_00277690(const FieldPointerOwner588* object);

#ifdef __cplusplus
}
#endif

#endif
