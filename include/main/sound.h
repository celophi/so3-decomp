#ifndef SO3_MAIN_SOUND_H
#define SO3_MAIN_SOUND_H

#include "types.h"
#include "ee.h"
#include "sdk/main/libkernl_00121940.h"
#include "main/resource_queue.h"
#include "main/sound_stream.h"

#ifdef __cplusplus
struct ResidentArchive;
#else
typedef struct ResidentArchive ResidentArchive;
#endif

/** Voice table the sound system reads from its voice file: where each voice lies in the file. */
typedef struct ResidentVoiceTable
{
    u32 count;

    struct
    {
        u16 block;
        u16 block_count;
    } entries[1];
} ResidentVoiceTable;

/** How one piece of music is played. */
typedef struct ResidentMusicEntry
{
    u8 in_memory;
    u8 unk01;
    u16 resource;
} ResidentMusicEntry;

/** What the sound system is busy with. Only the states I've identified are listed. */
enum ResidentSoundState
{
    RESIDENT_SOUND_IDLE = 0,
    RESIDENT_SOUND_UPLOADING = 4,
    RESIDENT_SOUND_LOADING = 5,
    RESIDENT_SOUND_CHANGING_REVERB = 9
};

/** Lib's renderer as the sound interrupt sees it; only the count at 0x40C4 is known. */
typedef struct ResidentSoundRenderer
{
    u8 unk0000[0x40C4];

    /**
     * Counted up by the sound interrupt.
     * TODO: volatile is my guess, since the interrupt and Lib both use it; the interrupt rereads it after the test,
     * and nothing else I tried does that.
     */
    volatile s32 unk40c4;
} ResidentSoundRenderer;

/**
 * The sound system: sound effects and voices in sixty slots, streamed music, and the surround output with its
 * listener and speaker placement.
 */
struct ResidentSound
{
    struct ResidentSoundStream* stream;
    ResidentArchive* archive;
    ResidentResourceQueue* resource_queue;
    struct ResidentSoundRenderer* unk0c;
    s32 music_entry_count;
    const ResidentMusicEntry* music_entries;
    u32 music_handles[3];
    s32 music_keys[3];
    s32 music_count;

    /**
     * Handles pushed onto music_handles; request callbacks push from other threads.
     * TODO: volatile is my guess from that; it's the only form I found where resident_sound_restore_volume rereads the count.
     */
    volatile u32 unk34;
    s32 unk38;
    s32 unk3c;
    s32 unk40;
    u32 music_status[3][16];
    s32 unk104[3];
    u8 state;
    u8 unk111;
    u8 unk112[2];
    u32 unk114;
    u8 unk118[0xF0];
    u32 unk208[15];
    u8 unk244[0xB4];
    struct ResidentRequestSlot* unk2F8[15];
    u32 unk334;
    u32 unk338;
    s32 unk33c;
    s32 volume;
    s32 scaled_volume;
    u8 unk348;
    u8 unk349[3];
    float unk34c;
    u8 unk350;
    u8 unk351;
    u8 unk352;
    u8 unk353;
    u8 reverb_preset;
    u8 reverb_step;
    u8 unk356;
    u8 unk357;
    s32 unk358;
    u32 unk35c;
    const void* unk360;
    u8 unk364[4];
    const void* unk368;
    u8 unk36c[4];
    u8 music_disabled;
    u8 effects_disabled;
    u8 unk372[2];
    s32 unk374;
    s32 unk378;
    u8 unk37c[0x40];
    s32 unk3bc;
    u32 unk3c0[16];
    u8* unk400;
    u32 unk404;
    ResidentVoiceTable* voice_table;
    s32 voice_file_key;
    u8* voice_buffers[8];
    s32 voice_indices[8];
    u8 output_mode;
    u8 unk451;
    u8 unk452;
    u8 unk453;
    u32 unk454[32];
    s32 unk4d4;
    s32 interrupt_handler;
    u32 next_identifier;
    s32 cursor;
    ResidentRequestSlot slots[60];
    u8 unk12f4[0x9C];
    void* listener;
    float unk1394;
    float range_squared;
    float speaker_angles[4];
    float unk13ac[4];
    void* unk13bc[32];
    s32 unk143c;

#ifdef __cplusplus
    /** @brief Start silent at half volume, with no music or voices, and install the sound interrupt handler. */
    ResidentSound();

    /** @brief Remove the sound interrupt handler and free the sound buffers. */
    virtual ~ResidentSound();
#endif
};

typedef struct ResidentSound ResidentSound;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Forward the manager's first pointer and the argument to resident_stream_set_second_state.
 * @param argument Value forwarded as the helper's second argument.
 */
void resident_sound_set_stream_second_state(const s32* value);

/** Run the resident helper on the object's pointer when it is non-null. */
void resident_sound_wake_stream(ResidentSound* sound);

/**
 * @brief Start the sound system and its stream.
 * @param sound Sound system.
 */
void resident_sound_start(ResidentSound* sound);

/** One entry of the table resident_sound_send_setup sends to the stream. */
typedef struct ResidentSoundSetupEntry
{
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
    u32 unk10;
} ResidentSoundSetupEntry;


#ifdef __cplusplus
/**
 * @brief Upload a sound file through the stream into a slot, using that slot's unk454 value.
 * @param sound Sound system.
 * @param file Sound file to upload; kept at unk360.
 * @param index Stream slot, and index into unk454.
 * @param append True to add to the slot's existing data.
 * @return Zero while the sound system is busy, otherwise one.
 */
s32 resident_sound_upload_file(ResidentSound* sound, const void* file, s32 index, bool append);
#endif

/**
 * @brief Send each entry of a setup table to the stream, waiting for each reply and keeping its first word in unk454;
 * main runs it after starting the sound system.
 * @param sound Sound system.
 * @param count Number of entries, below 32.
 * @param entries Setup table.
 * @return One when sent, zero when count is too large.
 */
s32 resident_sound_send_setup(ResidentSound* sound, s32 count, const ResidentSoundSetupEntry* entries);

/**
 * @brief Allocate a buffer for a resource and start loading it; main runs it once the archive is idle.
 * @param sound Sound system.
 * @param key Resource key.
 * @return One when the load started, zero while busy or when the buffer can't be allocated.
 */
s32 resident_sound_load_resource(ResidentSound* sound, s32 key);

/**
 * @brief Update the sound system; main calls it until sound->state is zero.
 * @param sound Sound system.
 * @param mode Nonzero to count frame time on the started slots.
 * @return One.
 */
s32 resident_sound_update(ResidentSound* sound, s32 mode);

/**
 * @brief Put the four surround speakers back at their default angles.
 * @param sound Sound system.
 */
void resident_sound_reset_speaker_angles(ResidentSound* sound);

/**
 * @brief Set the sound output mode.
 * @param sound Sound system.
 * @param mode Output mode: 1 mono, 0 stereo, 2 Dolby Pro Logic II, 3 headphones.
 */
void resident_sound_set_output_mode(ResidentSound* sound, s32 mode);

/**
 * @brief Set the object positional sounds are heard from.
 * @param sound Sound system.
 * @param listener Listening object.
 * @param value Stored with the listener; its use is unknown.
 * @param range Distance positional sounds reach.
 */
void resident_sound_set_listener(ResidentSound* sound, void* listener, float value, float range);

/**
 * @brief Set the angle of one surround speaker.
 * @param sound Sound system.
 * @param speaker Speaker index, 0 to 3.
 * @param angle Speaker angle in radians.
 */
void resident_sound_set_speaker_angle(ResidentSound* sound, s32 speaker, float angle);

/**
 * @brief Set the angles of all four surround speakers.
 * @param sound Sound system.
 * @param angles Four speaker angles in radians.
 */
void resident_sound_set_speaker_angles(ResidentSound* sound, const float* angles);

/** Append the pointer at object offset zero to the resident manager array. */
void resident_sound_push_music_handle(const void* reply);

/** Run the resident helper on the pointer at offset zero with its final flag set. */
s32 resident_sound_is_stream_state_set(ResidentSound* sound);

#define RESIDENT_SOUND_VOLUME_FULL 127
#define RESIDENT_SOUND_PAN_CENTRE 64
#define RESIDENT_SOUND_VOLUME_SCALE_FULL 0x7FFF

/**
 * @brief Play a sound effect in a free slot.
 * @param sound Sound system.
 * @param number Sound number; its low 16 bits are stored.
 * @param selector Request selector.
 * @param value Value forwarded to request dispatch.
 * @param volume Volume, up to RESIDENT_SOUND_VOLUME_FULL; stored and packed into the upper byte.
 * @param pan Pan, RESIDENT_SOUND_PAN_CENTRE for centre; packed into the next byte.
 * @param low Value packed into the lower 16 bits.
 * @return Slot identifier, zero on dispatch failure, one when disabled, or minus one when no slot is free.
 */
s32 resident_sound_play(ResidentSound* sound, s32 number, s32 selector, s32 value, s32 volume, s32 pan, s32 low);

/**
 * @brief Report whether music is playing.
 * @param sound Sound system.
 * @param key Music to check for, or -1 for any.
 * @return Nonzero while that music plays, or always when sound is disabled.
 */
s32 resident_sound_is_music_playing(ResidentSound* sound, s32 key);

void resident_sound_ignore_reply(void* object);

/**
 * @brief Set the table of music the sound system plays.
 * @param sound Sound system.
 * @param count Number of entries.
 * @param entries Music entries, by music number minus one.
 */
void resident_sound_set_music_table(ResidentSound* sound, s32 count, const ResidentMusicEntry* entries);

void resident_sound_do_nothing(void* object);

/**
 * @brief Free every voice read ahead of time, cancelling reads still in progress.
 * @param sound Sound system.
 */
void resident_sound_free_read_ahead(ResidentSound* sound);

#ifdef __cplusplus
/**
 * @brief Stop every sound, or mark each one to stop once the stream has started it.
 * @param sound Sound system.
 * @param mode Stop mode passed to the stream.
 * @return Always true.
 */
bool resident_sound_stop_all(ResidentSound* sound, s32 mode);
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
    /**
     * @brief Send voice command 4 to a started sound.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param first First command argument.
     * @param second Second command argument.
     */
    void resident_sound_voice_command_4(ResidentSound* sound, s32 identifier, s32 first, s32 second);

    /**
     * @brief Send voice command 5 to a started sound.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param first First command argument.
     * @param second Second command argument.
     */
    void resident_sound_voice_command_5(ResidentSound* sound, s32 identifier, s32 first, s32 second);

    /**
     * @brief Send voice command 1 to a started sound that has no target.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param first First command argument.
     * @param second Second command argument.
     */
    void resident_sound_voice_command_1(ResidentSound* sound, s32 identifier, s32 first, s32 second);

    /**
     * @brief Send voice command 0 to a started sound, optionally recording its new volume.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param volume Volume, sent as the first command argument.
     * @param second Second command argument.
     * @param keep_volume Zero to also store volume in the slot.
     */
    void resident_sound_set_voice_volume(ResidentSound* sound, s32 identifier, s32 volume, s32 second, s32 keep_volume);

    /**
     * @brief Report whether a sound still holds its slot.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @return One while the sound's slot is in use, otherwise zero.
     */
    s32 resident_sound_is_active(ResidentSound* sound, s32 identifier);

    /**
     * @brief Stop a sound, or mark it to stop once the stream has started it.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param mode Stop mode passed to the stream.
     * @return True when the sound was found (or effects are disabled), false when no slot holds it.
     */
    bool resident_sound_stop(ResidentSound* sound, s32 identifier, s32 mode);

    /**
     * @brief Read a playing voice's level at a time.
     * @param sound Sound system.
     * @param identifier Identifier resident_sound_play returned.
     * @param time Time to sample.
     * @return Voice level.
     */
    u32 resident_sound_get_voice_level(ResidentSound* sound, s32 identifier, float time);

    /**
     * @brief Free one voice read ahead of time, cancelling its read if it is still in progress.
     * @param sound Sound system.
     * @param voice Index of the voice in the voice table.
     */
    void resident_sound_free_read_ahead_voice(ResidentSound* sound, s32 voice);

    /**
     * @brief Read a voice into one of the read-ahead buffers.
     * @param sound Sound system.
     * @param voice Index of the voice in the voice table.
     * @return Zero once the read is queued, or -1 when the voice can't be read now.
     */
    s32 resident_sound_read_ahead_voice(ResidentSound* sound, s32 voice);

    /**
     * @brief Play a voice from an object in a free slot, reading it unless it was read ahead of time.
     * @param sound Sound system.
     * @param voice Index of the voice in the voice table.
     * @param emitter Object the voice comes from.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, one when effects are disabled, or -1 when the voice can't be played.
     */
    s32 resident_sound_play_voice_at(ResidentSound* sound, s32 voice, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low);

    /**
     * @brief Play a voice in a free slot, reading it unless it was read ahead of time.
     * @param sound Sound system.
     * @param voice Index of the voice in the voice table.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param pan Pan, 0x40 for centre; packed into the next byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, one when effects are disabled, or -1 when the voice can't be played.
     */
    s32 resident_sound_play_voice_number(ResidentSound* sound, s32 voice, s32 value, s32 volume, s32 pan, s32 low);

    /**
     * @brief Play sound data already in memory from an object, in a free slot.
     * @param sound Sound system.
     * @param buffer Sound data.
     * @param emitter Object the sound comes from.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param low Value packed into the lower 16 bits.
     * @param owns_buffer Nonzero to delete buffer once the sound stops, or now when effects are disabled.
     * @return Slot identifier, one when effects are disabled, or -1 when no slot is free.
     */
    s32 resident_sound_play_data_at(ResidentSound* sound, u8* buffer, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low,
                      s32 owns_buffer);

    /**
     * @brief Play sound data already in memory, in a free slot.
     * @param sound Sound system.
     * @param buffer Sound data.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; packed into the upper byte.
     * @param pan Pan, 0x40 for centre; packed into the next byte.
     * @param low Value packed into the lower 16 bits.
     * @param owns_buffer Nonzero to delete buffer once the sound stops, or now when effects are disabled.
     * @return Slot identifier, one when effects are disabled, or -1 when no slot is free.
     */
    s32 resident_sound_play_data(ResidentSound* sound, u8* buffer, s32 value, s32 volume, s32 pan, s32 low, s32 owns_buffer);

    /**
     * @brief Play a voice resource from an object in a free slot, reading the resource for it.
     * @param sound Sound system.
     * @param resource Resource key of the voice.
     * @param emitter Object the voice comes from.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, one when effects are disabled, or -1 when the voice can't be played.
     */
    s32 resident_sound_play_voice(ResidentSound* sound, s32 resource, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low);

    /**
     * @brief Play a voice resource in a free slot, reading the resource for it.
     * @param sound Sound system.
     * @param resource Resource key of the voice.
     * @param value Stored in the slot; its use is unknown.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param pan Pan, 0x40 for centre; packed into the next byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, one when effects are disabled, or -1 when the voice can't be played.
     */
    s32 resident_sound_play_voice_resource(ResidentSound* sound, s32 resource, s32 value, s32 volume, s32 pan, s32 low);

    /**
     * @brief Play a sound effect from an object in a free slot.
     * @param sound Sound system.
     * @param number Sound number; its low 16 bits are stored.
     * @param emitter Object the sound comes from.
     * @param selector Request selector.
     * @param value Value forwarded to request dispatch.
     * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
     * @param low Value packed into the lower 16 bits.
     * @return Slot identifier, zero on dispatch failure, one when effects are disabled, or -1 without an emitter or a free
     *         slot.
     */
    s32 resident_sound_play_at(ResidentSound* sound, s32 number, ResidentSoundEmitter* emitter, s32 selector, s32 value, s32 volume,
                      s32 low);

    /**
     * @brief Queue streamed music from a music file already in memory.
     * @param sound Sound system.
     * @param music Music file, non-null.
     * @param stop_others Nonzero to stop the queued music first.
     * @param value Stored for the music; its use is unknown.
     * @return One when the music was queued or music is disabled, otherwise zero.
     */
    s32 resident_sound_load_bank(ResidentSound* sound, const void* music, s32 stop_others, s32 value);

    /**
     * @brief Queue music.
     * @param sound Sound system.
     * @param music Music number, from one.
     * @param stop_others Nonzero to stop the queued music first.
     * @param value Stored for the music; its use is unknown.
     * @param second Stored for streamed music; nonzero also sets a flag.
     * @return One when the music was queued or music is disabled, otherwise zero.
     */
    s32 resident_sound_play_music(ResidentSound* sound, s32 music, s32 stop_others, s32 value, s32 second);

    /**
     * @brief Start the pending music (unk33c): stop every queued track, stop the one being faded (or the stream's
     * current one), then queue the pending key as the track being started.
     * @param sound Sound system.
     * @param key Stored at unk3c with the new track.
     * @return One when the music was queued or music is disabled; zero when nothing is pending, the queue is busy or
     * full.
     */
    s32 resident_sound_start_pending_music(ResidentSound* sound, s32 key);

    /**
     * @brief Stop music.
     * @param sound Sound system.
     * @param fade_frames Frames to fade out over, or zero to stop at once.
     * @param key Music to stop, or -1 for all of it.
     * @return One when music was stopped or music is disabled, otherwise zero.
     */
    s32 resident_sound_stop_music(ResidentSound* sound, s32 fade_frames, s32 key);

/**
 * @brief Switch to another reverb preset. The sound update applies it once every voice is idle.
 * @param sound Sound system.
 * @param preset Reverb preset.
 * @return Zero while the sound system is busy, otherwise one.
 */
s32 resident_sound_set_reverb(ResidentSound* sound, s32 preset);

/**
 * @brief Scale the sound volume and send it to the stream.
 * @param sound Sound system.
 * @param scale Scale, RESIDENT_SOUND_VOLUME_SCALE_FULL for the full volume.
 */
void resident_sound_set_volume_scale(ResidentSound* sound, s32 scale);

/**
 * @brief Send stream command resident_stream_command_18 when unk30 is set and unk38 isn't minus one, then copy unk40 to unk33C.
 * @param sound Sound system.
 */
void resident_sound_flush_command_18(ResidentSound* sound);

/**
 * @brief Pop the stream result stack and resend the scaled volume.
 * @param sound Sound system.
 */
void resident_sound_restore_volume(ResidentSound* sound);

/**
 * @brief Send stream command resident_stream_stop in mode 2.
 * @param sound Sound system.
 */
void resident_sound_stop_stream(ResidentSound* sound);

/**
 * @brief Count the entries of the loaded sound bank.
 * @param sound Sound system.
 * @return Number of entries, or zero while no bank is loaded or it is still loading.
 */
s32 resident_sound_count_bank_entries(ResidentSound* sound);

/**
 * @brief Read an entry of the loaded sound bank.
 * @param sound Sound system.
 * @param index Entry index.
 * @param second Receives the entry's second halfword, or zero.
 * @return The entry's first halfword, or minus one when there is no such entry.
 */
s32 resident_sound_get_bank_entry(ResidentSound* sound, s32 index, u32* second);

/**
 * @brief Load another sound bank, first releasing everything allocated from the current one.
 * @param sound Sound system.
 * @param key Resource key of the bank.
 */
void resident_sound_switch_bank(ResidentSound* sound, s32 key);

/**
 * @brief Get the voice data of a request slot, asking the stream for it the first time.
 * @param sound Sound system.
 * @param identifier Slot identifier.
 * @return The voice data, or zero when there is none.
 */
u32 resident_sound_get_voice_data(ResidentSound* sound, s32 identifier);

/**
 * @brief Clear the target of every active request slot aimed at an object.
 * @param sound Sound system.
 * @param target Object to forget.
 */
void resident_sound_clear_target(ResidentSound* sound, ResidentSoundEmitter* target);

/**
 * @brief Request callback: push the stream's answer onto the sound system's stack.
 * @param reply Reply from the IOP.
 */
void resident_sound_push_stream_answer(void* reply);

/**
 * @brief Request callback for a played sound: keep the IOP's answer in the slot and free the slot unless it repeats.
 * @param reply Reply from the IOP.
 * @param slot Request slot.
 */
void resident_sound_on_play_reply(void* reply, ResidentRequestSlot* slot);

/**
 * @brief Request callback: free each listed request slot whose reply word is zero, then clear unk348.
 * @param reply Reply from the IOP, one word per entry of sound->unk2F8.
 * @param sound Sound system.
 */
void resident_sound_free_finished_slots(const u32* reply, ResidentSound* sound);

/**
 * @brief Add a thread to the ones the sound interrupt wakes, unless it is already there.
 * @param sound Sound system.
 * @param thread Thread to wake.
 * @return False when the list of 32 is full, otherwise true.
 */
bool resident_sound_add_wake_thread(ResidentSound* sound, void* thread);

/**
 * @brief Clear the target of every active request slot aimed at an object, with interrupts disabled.
 * @param sound Sound system.
 * @param target Object being removed.
 */
void resident_sound_iclear_target(ResidentSound* sound, ResidentSoundEmitter* target);
}

#endif

#endif
