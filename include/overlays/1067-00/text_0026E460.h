#ifndef SO3_OVERLAYS_1067_00_TEXT_0026E460_H
#define SO3_OVERLAYS_1067_00_TEXT_0026E460_H

#include "types.h"

/** @brief Forward the callback after adjusting from the secondary object at offset 0x04. */
void func_0026ED50(void* object);
/** @brief Forward the callback after adjusting from the secondary object at offset 0x04. */
u8 func_0026ED60(void* object);
/** @brief Forward the callback after adjusting from the secondary object at offset 0x04. */
u8 func_0026ED70(void* object, void* value);
/** @brief Read the state byte after adjusting from the secondary object at offset 0x04. */
u8 func_0026ED80(const void* object);
/** @brief Read the object pointer after adjusting from the secondary object at offset 0x04. */
void* func_0026ED90(const void* object);
/** @brief Forward the callback after adjusting from the secondary object at offset 0x04. */
void func_0026EDA0(void* object);
/** @brief Forward the callback after adjusting from the secondary object at offset 0x04. */
void func_0026EDB0(void* object);
/** @brief Destroy the owner after adjusting from the secondary object at offset 0x04. */
void* func_0026EDC0(void* object, s32 flags);
/** @brief Forward the float callback after adjusting from the secondary object at offset 0xA8. */
void func_0026EDD0(void* object, float value);
/** @brief Forward the integer callback after adjusting from the secondary object at offset 0xA8. */
void func_0026EDE0(void* object, s32 value);
/** @brief Forward the callback after adjusting from the secondary object at offset 0x20. */
void func_0026EDF0(void* object);
/** @brief Destroy the owner after adjusting from the secondary object at offset 0x20. */
void* func_0026EE00(void* object, s32 flags);

#endif
