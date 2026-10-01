#ifndef SO3_OVERLAYS_3454_00_TEXT_0029F140_H
#define SO3_OVERLAYS_3454_00_TEXT_0029F140_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ObjAAAA0 ObjAAAA0;
typedef struct ObjAE500 ObjAE500;
typedef struct ObjAE810 ObjAE810;

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_0029F680(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_0029F690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002A0C00(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A78E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_002A78F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_002AC300(void* object);

/**
 * @brief Replace the float field at 0x710 when the input is at least its current value.
 * @param object Object containing the float field.
 * @param value New field value.
 */
void func_002AAAA0(ObjAAAA0* object, float value);

/**
 * @brief Replace the float field at 0x700 when the input is at least its current value.
 * @param object Object containing the float field.
 * @param value New field value.
 */
void func_002AAAC0(ObjAAAA0* object, float value);

/**
 * @brief Update both fields when the stored float is no greater than the input, or the stored halfword is less than the input.
 * @param object Object containing the fields.
 * @param value_590 Value compared and stored in the halfword field.
 * @param value New float value.
 */
void func_002AAAE0(ObjAAAA0* object, u32 value_590, float value);

/**
 * @brief Replace the float field at 0x6C8 when the input is at least its current value.
 * @param object Object containing the float field.
 * @param value New field value.
 */
void func_002AAB10(ObjAAAA0* object, float value);

/**
 * @brief Clear three byte fields.
 * @param object Object containing the fields.
 */
void func_002AE500(ObjAE500* object);

/**
 * @brief Store a pointer in the object's field.
 * @param object Object containing the pointer field.
 * @param value Pointer to store.
 */
void func_002AE810(ObjAE810* object, void* value);

#ifdef __cplusplus
}
#endif

#endif
