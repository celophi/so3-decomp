#ifndef SO3_MAIN_RESIDENT_0013CD50_H
#define SO3_MAIN_RESIDENT_0013CD50_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Copy up to a fixed number of string bytes, padding with zeros after the terminator.
 * @param destination Buffer receiving the bytes.
 * @param source String to copy.
 * @param size Number of bytes to write.
 * @return Original destination pointer.
 */
char* func_0013CD50(char* destination, const char* source, u32 size);

#ifdef __cplusplus
}
#endif

#endif
