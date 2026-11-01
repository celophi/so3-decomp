#include "include_asm.h"
#include "main/resident_00101260.h"

/** Sixteen keyed full-word entries in the resident runtime. */
typedef struct ResidentEntryTable
{
    u32 entries[16];
    s32 keys[16];
} ResidentEntryTable;

void* func_00101260(void* object)
{
    return (u8*)object + 0x13A10;
}

/**
 * @brief Get the resident system's sound system, which starts it.
 * @param object Resident system.
 * @return Sound system at offset 0.
 */
ResidentSound* func_00101270(void* object)
{
    return (ResidentSound*)object;
}

/**
 * @brief Return the address at receiver offset 0x15A5C.
 * @param object Receiver containing the address.
 * @return Address at offset 0x15A5C.
 */
void* func_00101280(void* object)
{
    return (u8*)object + 0x15A5C;
}

/** @brief Locate the resident entry table. @param object Table owner. @return Embedded entry table. */
void* resident_get_entry_table(void* object)
{
    return (u8*)object + 0x13990;
}

/**
 * @brief Return the address at receiver offset 0x1398D.
 * @param object Receiver containing the address.
 * @return Address at offset 0x1398D.
 */
void* func_001012A0(void* object)
{
    return (u8*)object + 0x1398D;
}

/**
 * @brief Get the resident system's overlay decoder.
 * @param object Resident system.
 * @return Decoder at offset 0x1398C.
 */
ResidentDecodeObject* func_001012B0(void* object)
{
    return (ResidentDecodeObject*)((u8*)object + 0x1398C);
}

/**
 * @brief Get the resource archive the runtime owner holds.
 * @param owner Runtime owner.
 * @return Resource archive.
 */
ResidentArchive* resident_get_archive(void* owner)
{
    return (ResidentArchive*)((u8*)owner + 0x17C0);
}

/**
 * @brief Get the resident system's input system.
 * @param object Resident system.
 * @return Input system at offset 0x1480.
 */
struct ResidentInputSystem* func_001012D0(void* object)
{
    return (struct ResidentInputSystem*)((u8*)object + 0x1480);
}

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
