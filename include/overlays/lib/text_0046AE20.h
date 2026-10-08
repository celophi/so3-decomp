#ifndef SO3_OVERLAYS_LIB_TEXT_0046AE20_H
#define SO3_OVERLAYS_LIB_TEXT_0046AE20_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find a camera entry matching its name and state filters.
 * @param object Manager supplying the entry table.
 * @param name Entry name; null or empty accepts any name.
 * @return Matching entry handle, or null.
 */
void* func_00473680(void* object, const char* name);

/**
 * @brief Update each active entry of the object's table with a boolean setting and an option flag.
 * @param object Object whose entry table is updated.
 * @param enable Boolean setting forwarded to each entry.
 * @param option Nonzero to select the alternate update path.
 */
void func_004728A0(void* object, s32 enable, s32 option);

/**
 * @brief Return the handle of the next table entry after entry that passes the entry state filter.
 * @param object Object whose entry table is searched.
 * @param entry Handle of the current entry.
 * @return The next entry's handle, or null if there is none.
 */
void* func_00472EB0(void* object, void* entry);

/**
 * @brief Return the handle of the first table entry that passes the entry state filter and matches name.
 * @param object Object whose entry table is searched.
 * @param name Entry name to match; null or empty matches any entry.
 * @return The entry's handle, or null if there is none.
 */
void* func_00473940(void* object, const char* name);

/**
 * @brief Find a named table entry.
 * @param object Object whose table is searched.
 * @param name Name to search; null selects an unnamed entry.
 * @return Matching entry handle, or null.
 */
void* func_00473390(void* object, const char* name);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/** Partial Lib class with vtable D_175320 in main data; its destructor is func_004792A0. */
class LibClass175320
{
public:
    /** @brief Destroy the object. */
    virtual ~LibClass175320();
};
#endif

#endif
