#ifndef SO3_MAIN_ENTRY_TABLE_H
#define SO3_MAIN_ENTRY_TABLE_H

#include "types.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"

/** Sixteen keyed full-word entries in the resident system. */
typedef struct ResidentEntryTable
{
    u32 entries[16];
    s32 keys[16];

#ifdef __cplusplus
    ResidentEntryTable();
#endif
} ResidentEntryTable;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Find the entry associated with one of the table's sixteen keys.
 * @param table Opaque entry table.
 * @param key Full-word entry key.
 * @return Matching full-word entry, or zero when the key is absent.
 */
u32 resident_find_entry(void* table, s32 key);

/**
 * @brief Remove every entry stored under a key.
 * @param table Opaque entry table.
 * @param key Key to remove.
 */
void resident_remove_entry(void* table, s32 key);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {

    /**
     * @brief Store an entry under a key, replacing the key's entry or taking the first free slot.
     * @param table Opaque entry table.
     * @param entry Entry to store.
     * @param key Key to store it under.
     * @return One when the entry was stored, or zero when the table is full.
     */
    u32 resident_store_entry(void* table, void* entry, s32 key);
}

#endif

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif
