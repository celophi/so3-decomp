#include "include_asm.h"
#include "main/resident_data.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/mslgcc_00142A40.h"
#include "main/system.h"
#include "main/utility.h"

/**
 * @brief Allocate the system's status byte at a random heap address and mark it clean.
 * @param system Resident system.
 */
void resident_system_create_status(ResidentSystem* system)
{
    // This memory is never freed. It seems like this is a way to get a random heap address, 
    // since the resident heap is randomized and the allocation size is random.
    new (0) u8[(resident_rand() & 0x3FF) + 64];
    
    system->status = new (0) u8[16];
    *system->status = RESIDENT_STATUS_CLEAN;
}

/**
 * @brief Set an alarm from interrupt context, doubling the time in progressive mode so it lasts as long as in
 * interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_iset_alarm(ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common)
{
    if (system->progressive)
    {
        time *= 2;
    }

    return iSetAlarm(time, handler, common);
}

/**
 * @brief Set an alarm, doubling the time in progressive mode so it lasts as long as in interlaced mode.
 * @param system Resident system.
 * @param time Horizontal syncs to wait in interlaced mode.
 * @param handler Handler to call from interrupt context.
 * @param common Argument passed to the handler.
 * @return Alarm ID, or a negative value on failure.
 */
s32 resident_system_set_alarm(ResidentSystem* system, u16 time, KernelAlarmHandler handler, void* common)
{
    if (system->progressive)
    {
        time *= 2;
    }

    return SetAlarm(time, handler, common);
}

/**
 * @brief Set progressive (525p) or interlaced output and reset the GS to match.
 * @param system Resident system.
 * @param progressive Nonzero for progressive output.
 */
void resident_system_set_progressive(ResidentSystem* system, u8 progressive)
{
    system->progressive = progressive;

    if (progressive)
    {
        sceGsResetGraph(0, SCE_GS_NOINTERLACE, SCE_GS_DTV480P, SCE_GS_FRAME);
    }
    else
    {
        sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    }
}

/**
 * @brief Save main's stack and frame pointers, so each program can start from main's stack depth.
 * TODO: Come back to this, and figure out if the compiler can express this somehow.
 * @param system Resident system.
 */
void resident_system_save_stack(ResidentSystem* system)
{
    void** sp_slot = &system->saved_sp;
    void** fp_slot = &system->saved_fp;

    asm("sw $sp, 0(%0)" : : "r"(sp_slot));
    asm("sw $fp, 0(%0)" : : "r"(fp_slot));
}

/**
 * @brief Decode an overlay into its slot and delete the loaded resource, then go back to main's stack depth and run
 * the new program, which never returns.
 * TODO: Same as resident_system_save_stack; the stack reset matches, but I want to dig into how the original did it.
 * @param system Resident system.
 * @param source Loaded, compressed overlay resource; switching deletes it.
 * @param slot Slot in the resident overlay table g_overlay_slots.
 */
void resident_system_switch_program(ResidentSystem* system, ResidentResourceHeader* source, s32 slot)
{
    void* overlay = g_overlay_slots[slot];
    u32 size;

    if (overlay != 0)
    {
        resident_decode_resource_block(&system->decoder, source, overlay, 0);
        size = source->decoded_size;
        delete source;
        FlushCache(0);
        mwOverlayInit(overlay, size);
        FlushCache(2);
    }

    void** sp_slot = &system->saved_sp;
    void** fp_slot = &system->saved_fp;

    asm("lw $sp, 0(%0)" : : "r"(sp_slot));
    asm("lw $fp, 0(%0)" : : "r"(fp_slot));
    g_current_program->run();
}

/**
 * @brief Clear a decoded overlay's BSS and run its static initializers.
 * @param system Resident system.
 * @param overlay Decoded overlay image.
 * @param slot The overlay's slot in the resident overlay table g_overlay_slots.
 * @param size Decoded size of the overlay image; its BSS follows it.
 */
void resident_system_init_overlay(ResidentSystem* system, void* overlay, s32 slot, u32 size)
{
    mwOverlayInit(overlay, size);
}

/**
 * @brief Decode an overlay into its slot and run its static initializers.
 * @param system Resident system.
 * @param source Loaded, compressed overlay resource.
 * @param slot Slot in the resident overlay table g_overlay_slots.
 */
void resident_system_load_overlay(ResidentSystem* system, ResidentResourceHeader* source, s32 slot)
{
    u32 size;
    void* overlay = g_overlay_slots[slot];

    if (overlay != 0)
    {
        resident_decode_resource_block(&system->decoder, source, overlay, 0);
        size = source->decoded_size;
        FlushCache(0);
        mwOverlayInit(overlay, size);
        FlushCache(2);
    }
}

/**
 * @brief Get the resident system's resource queue.
 * @param object Resident system.
 * @return Resource queue at offset 0x15A24.
 */
ResidentResourceQueue* resident_system_get_resource_queue(void* object)
{
    return (ResidentResourceQueue*)((char*)object + 0x15A24);
}

/**
 * @brief Get the resident system's release queues.
 * @param system Resident system.
 * @return Release queues at offset 0x13A10.
 */
ResidentReleaseQueues* resident_system_get_release_queues(ResidentSystem* system)
{
    return &system->release_queues;
}

/**
 * @brief Get the resident system's sound system, which starts it.
 * @param system Resident system.
 * @return Sound system at offset 0.
 */
ResidentSound* resident_system_get_sound(ResidentSystem* system)
{
    return &system->sound;
}

/**
 * @brief Get the resident system's sound stream.
 * @param system Resident system.
 * @return Sound stream at offset 0x15A5C.
 */
ResidentSoundStream* resident_system_get_sound_stream(ResidentSystem* system)
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
u8* resident_system_get_unk1398d(ResidentSystem* system)
{
    return system->unk1398D;
}

/**
 * @brief Get the resident system's overlay decoder.
 * @param system Resident system.
 * @return Decoder at offset 0x1398C.
 */
ResidentDecodeObject* resident_system_get_decoder(ResidentSystem* system)
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
ResidentInputSystem* resident_system_get_input(ResidentSystem* system)
{
    return &system->input;
}

/** @brief Construct the resident system and each of its parts. */
ResidentSystem::ResidentSystem()
{
    unk15C94 = 0;
    unk15C90 = 0;
    unk15C98 = 0;
    unk15C80 = 0;
    progressive = 0;
    status = 0;
}
