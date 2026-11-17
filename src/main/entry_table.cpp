#include "include_asm.h"
#include "main/entry_table.h"

/**
 * @brief Search the resident entry table by key.
 * @param object Entry table.
 * @param key Key to find.
 * @return Matching entry, or zero.
 */
u32 resident_find_entry(void* object, s32 key)
{
    ResidentEntryTable* table = (ResidentEntryTable*)object;
    s32 index;

    for (index = 0; index < 16; index++)
    {
        if (table->keys[index] == key)
        {
            return table->entries[index];
        }
    }

    return 0;
}

/**
 * @brief Remove every entry stored under a key.
 * @param object Entry table.
 * @param key Key to remove.
 */
void resident_remove_entry(void* object, s32 key)
{
    ResidentEntryTable* table = (ResidentEntryTable*)object;
    s32 index;

    for (index = 0; index < 16; index++)
    {
        if (table->keys[index] == key)
        {
            table->keys[index] = 0;
        }
    }
}

/**
 * @brief Store an entry under a key, replacing the key's entry or taking the first free slot.
 * @param object Entry table.
 * @param entry Entry to store.
 * @param key Key to store it under.
 * @return One when the entry was stored, or zero when the table is full.
 */
u32 resident_store_entry(void* object, void* entry, s32 key)
{
    ResidentEntryTable* table = (ResidentEntryTable*)object;
    s32 index;

    for (index = 0; index < 16; index++)
    {
        if (table->keys[index] == 0 || table->keys[index] == key)
        {
            table->entries[index] = (u32)entry;
            table->keys[index] = key;
            return 1;
        }
    }

    return 0;
}

/** @brief Start with no keys. */
ResidentEntryTable::ResidentEntryTable()
{
    int count = 0;
    char* cursor = (char*)this;

    do
    {
        *(unsigned int*)(cursor + 0x40) = 0;
        *(unsigned int*)(cursor + 0x44) = 0;
        count += 8;
        *(unsigned int*)(cursor + 0x48) = 0;
        *(unsigned int*)(cursor + 0x4C) = 0;
        *(unsigned int*)(cursor + 0x50) = 0;
        *(unsigned int*)(cursor + 0x54) = 0;
        *(unsigned int*)(cursor + 0x58) = 0;
        *(unsigned int*)(cursor + 0x5C) = 0;
        cursor += 0x20;
    } while (count < 16);
}
