#ifndef SO3_OVERLAYS_3454_00_TEXT_0027E060_H
#define SO3_OVERLAYS_3454_00_TEXT_0027E060_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Obj27E060 Obj27E060;

/**
 * @brief Set state zero when the object passes its status check.
 * @param object Object to check and update.
 */
void func_0027E3E0(void* object);


/**
 * @brief Clear state fields selected by two input codes.
 * @param object Object containing the state fields.
 * @param first_code First input code.
 * @param second_code Second input code.
 */
void func_00286910(Obj27E060* object, u8 first_code, u8 second_code);

/**
 * @brief Update an indexed float field from its source value and clear related state.
 * @param object Object containing the indexed field and state.
 * @param unused Event value unused by this routine.
 * @param enabled Whether to update the indexed float field.
 */
void func_002869C0(Obj27E060* object, u32 unused, s32 enabled);

/**
 * @brief Clear a second group of state fields selected by two input codes.
 * @param object Object containing the state fields.
 * @param first_code First input code.
 * @param second_code Second input code.
 */
void func_0028BDB0(Obj27E060* object, u8 first_code, u8 second_code);

/**
 * @brief Update a second indexed float field and clear its related state.
 * @param object Object containing the indexed field and state.
 * @param unused Event value unused by this routine.
 * @param enabled Whether to update the indexed float field.
 */
void func_0028BE50(Obj27E060* object, u32 unused, s32 enabled);

#ifdef __cplusplus
}
#endif

#endif
