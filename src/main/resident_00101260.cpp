#include "include_asm.h"
#include "main/resident_00101260.h"

/**
 * @brief Get the resident system's release queues.
 * @param system Resident system.
 * @return Release queues at offset 0x13A10.
 */
ResidentReleaseQueues* func_00101260(ResidentSystem* system)
{
    return &system->release_queues;
}

/**
 * @brief Get the resident system's sound system, which starts it.
 * @param system Resident system.
 * @return Sound system at offset 0.
 */
ResidentSound* func_00101270(ResidentSystem* system)
{
    return &system->sound;
}

/**
 * @brief Get the resident system's sound stream.
 * @param system Resident system.
 * @return Sound stream at offset 0x15A5C.
 */
ResidentSoundStream* func_00101280(ResidentSystem* system)
{
    return &system->sound_stream;
}

/**
 * @brief Get the resident system's entry table.
 * @param system Resident system.
 * @return Entry table at offset 0x13990.
 */
ResidentEntryTable* resident_get_entry_table(ResidentSystem* system)
{
    return &system->entry_table;
}

/**
 * @brief Get the byte after the resident system's decoder.
 * @param system Resident system.
 * @return Byte at offset 0x1398D.
 */
u8* func_001012A0(ResidentSystem* system)
{
    return system->unk1398D;
}

/**
 * @brief Get the resident system's overlay decoder.
 * @param system Resident system.
 * @return Decoder at offset 0x1398C.
 */
ResidentDecodeObject* func_001012B0(ResidentSystem* system)
{
    return &system->decoder;
}

/**
 * @brief Get the resident system's resource archive.
 * @param system Resident system.
 * @return Resource archive at offset 0x17C0.
 */
ResidentArchive* resident_get_archive(ResidentSystem* system)
{
    return &system->archive;
}

/**
 * @brief Get the resident system's input system.
 * @param system Resident system.
 * @return Input system at offset 0x1480.
 */
ResidentInputSystem* func_001012D0(ResidentSystem* system)
{
    return &system->input;
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
