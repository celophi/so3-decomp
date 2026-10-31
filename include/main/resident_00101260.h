#ifndef SO3_MAIN_RESIDENT_00101260_H
#define SO3_MAIN_RESIDENT_00101260_H

#include "types.h"
#include "main/resident_0010A0E0.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Locate the entry table within its resident owner.
 * @param object Opaque table owner.
 * @return Opaque entry table.
 */
void* resident_get_entry_table(void* object);

/**
 * @brief Find the entry associated with one of the table's sixteen keys.
 * @param table Opaque entry table.
 * @param key Full-word entry key.
 * @return Matching full-word entry, or zero when the key is absent.
 */
u32 resident_find_entry(void* table, s32 key);

/** Remove the entry associated with a key. */
void func_00101480(void* table, s32 key);

/** Return the first pointer argument unchanged. */
void* func_00101270(void* value);

/**
 * @brief Get the resource archive the runtime owner holds.
 * @param owner Runtime owner.
 * @return Resource archive.
 */
ResidentArchive* resident_get_archive(void* owner);

/** Return the receiver address at byte offset 0x1480. */
void* func_001012D0(void* object);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
    u32 func_001014B0(void* table, void* entry, s32 key);
}
#endif

#endif
