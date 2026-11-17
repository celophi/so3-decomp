#ifndef SO3_MAIN_SOUND_SET_H
#define SO3_MAIN_SOUND_SET_H

#include "types.h"
#include "gs.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"
#include "main/object.h"
#include "main/sound_stream.h"

#define RESIDENT_SOUND_BANK_SLOT_COUNT 3
#define RESIDENT_SOUND_BANK_LIST_COUNT 16

/** One queued bank load: which slot it fills and the file holding the picked variant. */
typedef struct ResidentSoundBankLoad
{
    u8 slot;
    u8 variant;
    u8 unk02[2];
    s32 file_key;
} ResidentSoundBankLoad;

/** One part of registered sound bank data, which starts with a word holding its part count followed by the parts. */
typedef struct ResidentSoundBankPart
{
    u16 sector;
    u16 unk02;
} ResidentSoundBankPart;

/** The files holding each variant of one sound bank. */
typedef struct ResidentSoundBankVariants
{
    s32 count;
    const s32* file_keys;
} ResidentSoundBankVariants;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Move the set state from byte 0x25 to byte 0x24 when set.
 * @param object Object containing the state bytes.
 */
void resident_sound_bank_set_apply_pending(void* object);

/**
 * @brief Read the byte at offset 0x25 of an object.
 * @param object Object to read; the field context passes its object at offset 0x24.
 * @return The byte at offset 0x25.
 */
u8 resident_sound_bank_set_get_pending(void* object);

/** Store a resident data pointer in the shared global. */
void resident_sound_bank_set_install_variants(const void* value);

/**
 * @brief Play a voice resource, from an emitter when one is given.
 * @param object Sound bank set; unused.
 * @param resource Voice resource.
 * @param emitter Object the voice follows, or null.
 * @param value Value forwarded to the voice request.
 * @param volume Volume, 0x7F for full.
 * @param low Value forwarded to the voice request.
 * @return Slot identifier of the voice.
 */
s32 resident_sound_bank_set_play_voice(void* object, s32 resource, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low);

/**
 * @brief Play sound data the caller supplies, from an emitter when one is given.
 * @param object Sound bank set; unused.
 * @param buffer Sound data to play.
 * @param emitter Object the sound follows, or null.
 * @param value Value forwarded to the sound request.
 * @param volume Volume, 0x7F for full.
 * @param low Value forwarded to the sound request.
 * @param owns_buffer Nonzero to free the buffer when the sound ends.
 * @return Slot identifier of the sound.
 */
s32 resident_sound_bank_set_play_data(void* object, u8* buffer, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low,
                  s32 owns_buffer);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/**
 * Resident object that loads a randomly picked variant of up to three sound banks and plays sounds from them. It reads
 * each picked bank file into a staging buffer and uploads it, or uploads data lists registered with it.
 */
class ResidentSoundBankSet : public ResidentListObject
{
public:
    /** @brief Construct an empty set with no banks assigned and register it with the update list. */
    ResidentSoundBankSet();

    /** @brief Detach the set and free its staging buffer. */
    virtual ~ResidentSoundBankSet();

    /** @brief Advance the bank loads by one step each frame while loads are in progress. */
    virtual void update();

    s16 variants[RESIDENT_SOUND_BANK_SLOT_COUNT];
    u8 banks[RESIDENT_SOUND_BANK_SLOT_COUNT];
    u8 unk1d[3];
    u8* buffer;
    u8 unk24;
    u8 loading;
    u8 unk26[2];
    ResidentSoundBankLoad loads[10];
    u8 load_count;
    u8 load_index;
    u8 load_step;
    u8 upload_lists;
    u8 list_index;
    u8 part_index;
    u8 first_part;
    u8 unk7f;
    s32* lists[RESIDENT_SOUND_BANK_SLOT_COUNT][RESIDENT_SOUND_BANK_LIST_COUNT];
    s32 list_sizes[RESIDENT_SOUND_BANK_SLOT_COUNT];
};
extern "C" {

    /**
     * @brief Cancel the bank file reads and forget each slot's variant unless loads are in progress.
     * @param set Sound bank set.
     */
    void resident_sound_bank_set_cancel(ResidentSoundBankSet* set);

    /**
     * @brief Play a sound from a slot's bank, from an emitter when one is given.
     * @param set Sound bank set.
     * @param slot Bank slot.
     * @param id Sound number within the bank.
     * @param emitter Object the sound follows, or null.
     * @param arg4 Value forwarded to the sound request.
     * @param arg5 Value forwarded to the sound request.
     * @param arg6 Value forwarded to the sound request.
     * @return Slot identifier of the sound, or -1 when the slot has no bank loaded.
     */
    s32 resident_sound_bank_set_play(ResidentSoundBankSet* set, s32 slot, s32 id, ResidentSoundEmitter* emitter, s32 arg4, s32 arg5,
                      s32 arg6);

    /**
     * @brief Start uploading the registered data lists unless loads are in progress.
     * @param set Sound bank set.
     */
    void resident_sound_bank_set_upload(ResidentSoundBankSet* set);

    /**
     * @brief Register bank data in the first free entry of a list unless loads are in progress.
     * @param set Sound bank set.
     * @param list List to add to.
     * @param data Bank data.
     */
    void resident_sound_bank_set_register(ResidentSoundBankSet* set, s32 list, s32* data);

    /**
     * @brief Clear every registered data list and its size unless loads are in progress.
     * @param set Sound bank set.
     */
    void resident_sound_bank_set_clear_lists(ResidentSoundBankSet* set);

    /**
     * @brief Get the budget picking a variant for every assigned slot without one would cost.
     * @param set Sound bank set.
     * @return The pick cost times the number of such slots.
     */
    s32 resident_sound_bank_set_get_pick_cost(ResidentSoundBankSet* set);

    /**
     * @brief Pick variants for the slots and start loading them.
     * @param set Sound bank set.
     * @param budget Budget each pick spends from.
     * @return One when loading started, or zero otherwise.
     */
    s32 resident_sound_bank_set_pick_variants(ResidentSoundBankSet* set, s32 budget);

    /**
     * @brief Assign a bank to a slot unless loads are in progress, forgetting its variant when the bank changes.
     * @param set Sound bank set.
     * @param slot Slot to assign.
     * @param bank One-based bank number, or zero for none.
     * @return One when assigned, or zero while loads are in progress.
     */
    s32 resident_sound_bank_set_assign(ResidentSoundBankSet* set, s32 slot, s32 bank);
}

#endif

#endif
