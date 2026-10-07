#ifndef SO3_MAIN_RESIDENT_00101260_H
#define SO3_MAIN_RESIDENT_00101260_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Locate the entry table within its resident owner.
 * @param object Opaque table owner.
 * @return Opaque entry table.
 */
void* func_00101290(void* object);

/**
 * @brief Find the entry associated with one of the table's sixteen keys.
 * @param table Opaque entry table.
 * @param key Full-word entry key.
 * @return Matching full-word entry, or zero when the key is absent.
 */
u32 func_00101440(void* table, s32 key);

#ifdef __cplusplus
}
#endif

#endif
