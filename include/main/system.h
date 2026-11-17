#ifndef SO3_MAIN_SYSTEM_H
#define SO3_MAIN_SYSTEM_H

#include "types.h"
#include "sdk/main/libkernl_00121940.h"
#include "ee.h"
#include "main/main.h"
#include "main/entry_table.h"
#include "main/decode.h"
#include "main/resource_queue.h"
#include "main/sound_stream.h"
#include "main/sound.h"
#include "main/archive.h"
#include "main/input.h"
#include "main/release_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Load address of the overlay in each slot, or null for an empty slot. */
extern void* g_overlay_slots[];

struct ResidentSystem;

/**
 * @brief Clear a decoded overlay's BSS and run its static initializers.
 * @param system Resident system.
 * @param overlay Decoded overlay image.
 * @param slot The overlay's slot in the resident overlay table g_overlay_slots.
 * @param size Decoded size of the overlay image; its BSS follows it.
 */
void resident_system_init_overlay(struct ResidentSystem* system, void* overlay, s32 slot, u32 size);

/**
 * @brief Allocate the system's status byte at a random heap address and mark it clean.
 * @param system Resident system.
 */
void resident_system_create_status(struct ResidentSystem* system);

/**
 * @brief Set an alarm from interrupt context, doubling the time in progressive mode so it lasts as long as in
 * interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_iset_alarm(struct ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common);

/**
 * @brief Set an alarm, doubling the time in progressive mode so it lasts as long as in interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_set_alarm(struct ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common);

/**
 * @brief Set progressive (525p) or interlaced output and reset the GS to match.
 * @param system Resident system.
 * @param progressive Nonzero for progressive output.
 */
void resident_system_set_progressive(struct ResidentSystem* system, u8 progressive);

/**
 * @brief Save main's stack and frame pointers, so each program can start from main's stack depth.
 * @param system Resident system.
 */
void resident_system_save_stack(struct ResidentSystem* system);

/**
 * @brief Decode an overlay into its slot and delete the loaded resource, then go back to main's stack depth and run
 * the new program, which never returns.
 * @param system Resident system.
 * @param source Loaded, compressed overlay resource; switching deletes it.
 * @param slot Slot in the resident overlay table g_overlay_slots.
 */
void resident_system_switch_program(struct ResidentSystem* system, struct ResidentResourceHeader* source, s32 slot);

/**
 * @brief Decode an overlay into its slot and run its static initializers.
 * @param system Resident system.
 * @param source Loaded, compressed overlay resource.
 * @param slot Slot in the resident overlay table g_overlay_slots.
 */
void resident_system_load_overlay(struct ResidentSystem* system, struct ResidentResourceHeader* source, s32 slot);

#ifdef __cplusplus
}
#endif

/** Values of g_system's status byte. */
enum ResidentStatus
{
    /** Set when the status byte is allocated. */
    RESIDENT_STATUS_CLEAN = 0x66,

    /** Set when main's code no longer matches the copy in the program image. */
    RESIDENT_STATUS_TAMPERED = 0x67
};

#ifdef __cplusplus

/**
 * The resident system g_system, which outlives every program. It holds the sound system, the resource archive, the
 * entry table, the release and resource queues and the decoder that loads each program's overlay, and it switches
 * from one program to the next.
 */
struct ResidentSystem
{
    /** @brief Construct the resident system and each of its parts. */
    ResidentSystem();

    ~ResidentSystem();

    /**
     * @brief Free the system through the resident heap.
     * @param memory Allocation, or null.
     */
    static void operator delete(void* memory) throw()
    {
        resident_delete(memory);
    }

    ResidentSound sound;

    u8 unk_sound_end[0x1480 - sizeof(ResidentSound)];

    ResidentInputSystem input;
    ResidentArchive archive;
    ResidentDecodeObject decoder;
    u8 unk1398D[3];
    ResidentEntryTable entry_table;
    ResidentReleaseQueues release_queues;
    ResidentResourceQueue resource_queue;
    ResidentSoundStream sound_stream;
    u32 unk15C80;
    u8 progressive;
    u8 unk15C85[0xB];
    u32 unk15C90;
    u32 unk15C94;
    u32 unk15C98;
    void* saved_sp;
    void* saved_fp;

    u8 unk15CA4[0xC];
    unsigned __int128 sle_key;
    u8* status;
};
#endif

typedef struct ResidentSystem ResidentSystem;

#ifdef __cplusplus
extern "C" {
#endif

/** The resident system. */
extern ResidentSystem g_system;

/**
 * @brief Get the resident system's release queues.
 * @param system Resident system.
 * @return Release queues at offset 0x13A10.
 */
ResidentReleaseQueues* resident_system_get_release_queues(struct ResidentSystem* system);

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
u8* resident_system_get_unk1398d(struct ResidentSystem* system);

/**
 * @brief Get the resident system's sound system, which starts it.
 * @param system Resident system.
 * @return Sound system at offset 0.
 */
ResidentSound* resident_system_get_sound(struct ResidentSystem* system);

/**
 * @brief Get the resident system's resource archive.
 * @param system Resident system.
 * @return Resource archive at offset 0x17C0.
 */
ResidentArchive* resident_get_archive(struct ResidentSystem* system);

/**
 * @brief Get the resident system's resource queue.
 * @param object Resident system.
 * @return Resource queue at offset 0x15A24.
 */
ResidentResourceQueue* resident_system_get_resource_queue(void* object);

/**
 * @brief Get the resident system's overlay decoder.
 * @param system Resident system.
 * @return Decoder at offset 0x1398C.
 */
ResidentDecodeObject* resident_system_get_decoder(struct ResidentSystem* system);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
    
    }
#endif

#endif
