#ifndef SO3_MAIN_RESIDENT_00101260_H
#define SO3_MAIN_RESIDENT_00101260_H

#include "types.h"
#include "main/resident_0010A0E0.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the resident system's release queues.
 * @param system Resident system.
 * @return Release queues at offset 0x13A10.
 */
ResidentReleaseQueues* func_00101260(struct ResidentSystem* system);

/**
 * @brief Get the resident system's sound stream.
 * @param system Resident system.
 * @return Sound stream at offset 0x15A5C.
 */
struct ResidentSoundStream* func_00101280(struct ResidentSystem* system);

/**
 * @brief Get the resident system's entry table.
 * @param system Resident system.
 * @return Entry table at offset 0x13990.
 */
ResidentEntryTable* resident_get_entry_table(struct ResidentSystem* system);

/**
 * @brief Get the byte after the resident system's decoder.
 * @param system Resident system.
 * @return Byte at offset 0x1398D.
 */
u8* func_001012A0(struct ResidentSystem* system);

/**
 * @brief Find the entry associated with one of the table's sixteen keys.
 * @param table Opaque entry table.
 * @param key Full-word entry key.
 * @return Matching full-word entry, or zero when the key is absent.
 */
u32 resident_find_entry(void* table, s32 key);

/** Remove the entry associated with a key. */
void func_00101480(void* table, s32 key);

/**
 * @brief Get the resident system's sound system, which starts it.
 * @param system Resident system.
 * @return Sound system at offset 0.
 */
ResidentSound* func_00101270(struct ResidentSystem* system);

/**
 * @brief Get the resident system's resource archive.
 * @param system Resident system.
 * @return Resource archive at offset 0x17C0.
 */
ResidentArchive* resident_get_archive(struct ResidentSystem* system);

/**
 * @brief Get the resident system's input system.
 * @param system Resident system.
 * @return Input system at offset 0x1480.
 */
struct ResidentInputSystem* func_001012D0(struct ResidentSystem* system);

/**
 * @brief Get the resident system's resource queue.
 * @param object Resident system.
 * @return Resource queue at offset 0x15A24.
 */
ResidentResourceQueue* func_00101250(void* object);

/**
 * @brief Get the resident system's overlay decoder.
 * @param system Resident system.
 * @return Decoder at offset 0x1398C.
 */
ResidentDecodeObject* func_001012B0(struct ResidentSystem* system);

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
