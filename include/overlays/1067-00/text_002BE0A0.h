#ifndef SO3_OVERLAYS_1067_00_TEXT_002BE0A0_H
#define SO3_OVERLAYS_1067_00_TEXT_002BE0A0_H

#include "types.h"

/** Partial D_159B60 field object with its current entry index. */
typedef struct FieldObject159B60
{
    u8 unk00[0x28];
    u32 current;
} FieldObject159B60;

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Return the signed category for the D_159B60 callback table. */
s32 func_002BE180(const FieldObject159B60* object);
/** @brief Reset the current entry index. */
void func_002BE190(FieldObject159B60* object);
/** @brief Return the fixed distance limit for the field object. */
float func_002BE1A0(const FieldObject159B60* object);
/** @brief Report that the field object is active. */
u8 func_002BE1C0(const FieldObject159B60* object);
/** @brief Default callback for the field object. */
void func_002BE410(FieldObject159B60* object);

#ifdef __cplusplus
}
#endif

#endif
