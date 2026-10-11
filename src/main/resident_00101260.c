#include "include_asm.h"
#include "main/resident_00101260.h"

/** Sixteen keyed full-word entries in the resident runtime. */
typedef struct ResidentEntryTable
{
    u32 entries[16];
    s32 keys[16];
} ResidentEntryTable;

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_00101260);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_00101270);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_00101280);

/** @brief Locate the resident entry table. @param object Table owner. @return Embedded entry table. */
void* resident_get_entry_table(void* object)
{
    return (u8*)object + 0x13990;
}

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_001012A0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_001012B0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_001012C0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_001012D0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_001012E0);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_001013A0);

/** @brief Search the resident entry table by key. @param object Entry table. @param key Key to find. @return Matching entry, or zero. */
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

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_00101480);

INCLUDE_ASM("build/main/asm/nonmatchings/main/resident_00101260", func_001014B0);
