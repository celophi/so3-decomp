#ifndef SO3_OVERLAYS_1067_00_TEXT_002636B0_H
#define SO3_OVERLAYS_1067_00_TEXT_002636B0_H

#include "types.h"

/** Partial field object with two object pointers and a signed state byte. */
typedef struct FieldObject153E20
{
    u8 unk00[0x20];
    void* unk20;
    void* unk24;
    s8 unk28;
} FieldObject153E20;

/** @brief Store the object pointer at offset 0x20. */
void func_00263C70(FieldObject153E20* object, void* value);

/** @brief Store the object pointer at offset 0x24. */
void func_00263C80(FieldObject153E20* object, void* value);

/** @brief Read the object pointer at offset 0x24. */
void* func_00263C90(const FieldObject153E20* object);

/** @brief Store the signed state byte at offset 0x28. */
void func_00263CA0(FieldObject153E20* object, s8 value);

/** @brief Read the signed state byte at offset 0x28. */
s8 func_00263CB0(const FieldObject153E20* object);

#endif
