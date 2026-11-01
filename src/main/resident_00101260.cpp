#include "include_asm.h"
#include "main/resident_00101260.h"
#include "main/func_00101510.h"
#include "main/resident_0011EE70.h"

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

/**
 * @brief Construct the resident system and each of its parts.
 * @param system Resident system to construct.
 * @return The constructed system.
 */
ResidentSystem* func_001012E0(ResidentSystem* system)
{
    func_00112FE0(&system->sound);
    func_0011EC30(&system->input);
    func_0011DC00(&system->archive);
    func_00101510(&system->entry_table);
    resident_initialize_release_queues(&system->release_queues);
    func_001044F0(&system->resource_queue);
    func_001093E0(&system->sound_stream);
    system->unk15C94 = 0;
    system->unk15C90 = 0;
    system->unk15C98 = 0;
    system->unk15C80 = 0;
    system->progressive = 0;
    system->status = 0;
    return system;
}

/**
 * @brief Destroy the input system's semaphore and polling thread, then free it when asked.
 * @param input Input system to destroy, or null.
 * @param flags Positive to free the input system after destroying it.
 * @return The input system.
 */
ResidentInputSystem* func_001013A0(ResidentInputSystem* input, s16 flags)
{
    if (input != 0)
    {
        input->semaphore.ResidentSemaphore::~ResidentSemaphore();
        input->poll_thread.ResidentClass14FC60::~ResidentClass14FC60();

        if (flags > 0)
        {
            operator delete(input);
        }
    }

    return input;
}

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
void func_00101480(void* object, s32 key)
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
u32 func_001014B0(void* object, void* entry, s32 key)
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
