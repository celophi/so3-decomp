#include "include_asm.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_00137290.h"
#include "main/resident_data.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "overlays/lib/emission_vu0.h"
#include "angle.h"
#include "vu0.h"
#include "main/interrupt_lock.h"
#include "main/object_list.h"
#include "main/sif.h"
#include "main/system.h"
#include "main/stream_thread.h"
#include "main/utility.h"

#define INTC_VBLANK_END 3
#define SOUND_BLOCK_SIZE 2048
#define SOUND_VOICE_READ_TAG 7
#define SOUND_VOICE_TABLE_READ_TAG 8
#define SOUND_VOICE_READ_PRIORITY 216000
#define SOUND_MUSIC_READ_TAG 4
#define SOUND_RESOURCE_MUSIC_KEY 30000

extern "C" {
/** The time-slice scheduler. */
extern ResidentThreadScheduler g_scheduler;

void func_4DA730(struct ResidentSoundEmitter* emitter, float* position);

void func_4D9E70(ResidentImageObjectBase* transform);

void func_4CF5E0(float* value);

void func_4CC1A0(float* output, float angle);

/** For each pair of neighbouring speakers, the two ends of the range a sound's angle between them maps onto. */
struct SpeakerPairs
{
    float value[4][2];
} __attribute__((aligned(16)));

extern const SpeakerPairs g_speaker_pairs;

s32 RemoveIntcHandler(s32 cause, s32 handler_id);

s32 EnableIntc(s32 cause);

s32 DisableIntc(s32 cause);

/** One reverb preset: four values sent to the stream, then the four speaker levels kept in unk13ac. */
struct ResidentReverbPreset
{
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0a;
    s16 unk0c;
    s16 unk0e;
};

extern const ResidentReverbPreset g_reverb_presets[];

s32 AddIntcHandler(s32 cause, s32 (*handler)(s32), s32 next);

s32 func_4D44D0(ResidentSoundRenderer* renderer, s32 arg1);

typedef struct ResidentSpeakerAngles
{
    float angles[4];
} ResidentSpeakerAngles;
extern const ResidentSpeakerAngles g_default_speaker_angles;
extern ResidentSound* g_resident_sound;

/**
 * @brief Add a thread to the ones the sound interrupt wakes, unless it is already there.
 * @param sound Sound system.
 * @param thread Thread to wake.
 * @return False when the list of 32 is full, otherwise true.
 */
bool resident_sound_add_wake_thread(ResidentSound* sound, void* thread)
{
    ResidentInterruptLock lock;
    s32 count = sound->unk143c;

    if (count >= 32)
    {
        return false;
    }

    for (s32 i = 0; i < count; i++)
    {
        if (thread == sound->unk13bc[i])
        {
            return true;
        }
    }

    sound->unk13bc[sound->unk143c++] = thread;
    return true;
}

/**
 * @brief Put the four surround speakers back at their default angles.
 * @param sound Sound system.
 */
void resident_sound_reset_speaker_angles(ResidentSound* sound)
{
    ResidentSpeakerAngles angles = g_default_speaker_angles;
    sound->speaker_angles[0] = angles.angles[0];
    sound->speaker_angles[1] = angles.angles[1];
    sound->speaker_angles[2] = angles.angles[2];
    sound->speaker_angles[3] = angles.angles[3];
}

/**
 * @brief Set the sound output mode.
 * @param sound Sound system.
 * @param mode Output mode: 1 mono, 0 stereo, 2 Dolby Pro Logic II, 3 headphones.
 */
void resident_sound_set_output_mode(ResidentSound* sound, s32 mode)
{
    sound->output_mode = mode;
    resident_stream_set_output_mode(sound->stream, 0, 0, 0, mode & 0xFF);
}

/**
 * @brief Switch to another reverb preset. The sound update applies it once every voice is idle.
 * @param sound Sound system.
 * @param preset Reverb preset.
 * @return Zero while the sound system is busy, otherwise one.
 */
s32 resident_sound_set_reverb(ResidentSound* sound, s32 preset)
{
    if (sound->state != RESIDENT_SOUND_IDLE)
    {
        return 0;
    }

    if (sound->reverb_preset == preset)
    {
        return 1;
    }

    if (sound->effects_disabled != 0)
    {
        return 1;
    }

    sound->state = RESIDENT_SOUND_CHANGING_REVERB;
    sound->reverb_preset = preset;
    sound->reverb_step = 0;
    return 1;
}

/**
 * @brief Scale the sound volume and send it to the stream.
 * @param sound Sound system.
 * @param scale Scale, 0x7FFF for the full volume.
 */
void resident_sound_set_volume_scale(ResidentSound* sound, s32 scale)
{
    s32 volume;

    if (sound->music_disabled)
    {
        return;
    }

    volume = sound->volume * scale / 0x7FFF;

    if (volume > 0x7FFF)
    {
        volume = 0x7FFF;
    }

    if (volume < 0)
    {
        volume = 0;
    }

    sound->scaled_volume = volume;
    resident_stream_set_volume(sound->stream, 0, 0, 0, sound->scaled_volume);
}

/**
 * @brief Remove a music track from the queue.
 * @param sound Sound system.
 * @param index Queue position of the track.
 */
static inline void sound_drop_music_track(ResidentSound* sound, s32 index)
{
    if (index == sound->unk38)
    {
        sound->unk38 = -1;
        sound->unk40 = 0;
    }

    if (sound->unk38 > index)
    {
        sound->unk38--;
    }

    for (s32 i = index; i < sound->music_count; i++)
    {
        sound->music_handles[i] = sound->music_handles[i + 1];
        sound->music_keys[i] = sound->music_keys[i + 1];
    }

    sound->music_count--;
    sound->unk34--;
}

/**
 * @brief Stop a queued music track and remove it from the queue.
 * @param sound Sound system.
 * @param index Queue position of the track.
 * @param mode Stop mode.
 */
static inline void sound_remove_music_track(ResidentSound* sound, s32 index, s32 mode)
{
    if (sound->music_count == 0)
    {
        return;
    }

    resident_stream_stop(sound->stream, 0, resident_sound_ignore_reply, 0, sound->music_handles[index], mode, 0);
    sound_drop_music_track(sound, index);
}

/**
 * @brief Start the pending music (unk33c): stop every queued track, stop the one being faded (or the stream's
 * current one), then queue the pending key as the track being started.
 * @param sound Sound system.
 * @param key Stored at unk3c with the new track.
 * @return One when the music was queued or music is disabled; zero when nothing is pending, the queue is busy or full.
 */
s32 resident_sound_start_pending_music(ResidentSound* sound, s32 key)
{
    if (sound->music_disabled)
    {
        return 1;
    }

    if (sound->unk33c == 0)
    {
        return 0;
    }

    if (sound->unk350)
    {
        return 0;
    }

    if (sound->music_count != sound->unk34)
    {
        resident_sound_update(sound, 0);
        return 0;
    }

    if (sound->music_count != 0)
    {
        do
        {
            sound_remove_music_track(sound, 0, 0);
        } while (sound->music_count != 0);
    }

    if (sound->state)
    {
        return 0;
    }

    s32 current = sound->unk38;

    if (current >= 0)
    {
        sound_remove_music_track(sound, current, 0);
    }
    else if (resident_stream_query(sound->stream, 0, 0, 0, 1))
    {
        resident_stream_stop(sound->stream, 0, resident_sound_ignore_reply, 0, sound->unk338, 0, 0);
    }

    if (sound->music_count >= 3)
    {
        return 0;
    }

    sound->unk40 = sound->unk33c;
    sound->state = 7;
    sound->unk38 = sound->music_count;
    sound->music_keys[sound->music_count++] = sound->unk33c;
    sound->unk3c = key;
    sound->unk33c = 0;
    return 1;
}

/**
 * @brief Send stream command resident_stream_command_18 when unk30 is set and unk38 isn't minus one, then copy unk40 to unk33C.
 * @param sound Sound system.
 */
void resident_sound_flush_command_18(ResidentSound* sound)
{
    if (sound->music_disabled)
    {
        return;
    }

    if (sound->music_count == 0)
    {
        return;
    }

    if (sound->unk38 == -1)
    {
        return;
    }

    resident_stream_command_18(sound->stream, 0, 0, 0);
    sound->unk33c = sound->unk40;
}

/**
 * @brief Pop the stream result stack and resend the scaled volume.
 * @param sound Sound system.
 */
void resident_sound_restore_volume(ResidentSound* sound)
{
    if (sound->music_disabled)
    {
        return;
    }

    sound->unk350 = 0;

    if (sound->unk34 != 0)
    {
        sound->unk34--;
    }

    resident_stream_stop(sound->stream, 0, 0, 0, 1, 0, 0);
    resident_stream_set_volume(sound->stream, 0, 0, 0, sound->scaled_volume);
}

/**
 * @brief Send stream command resident_stream_stop in mode 2.
 * @param sound Sound system.
 */
void resident_sound_stop_stream(ResidentSound* sound)
{
    if (sound->music_disabled)
    {
        return;
    }

    resident_stream_stop(sound->stream, 0, 0, 0, 2, 0, 0);
}

/**
 * @brief Pass a value to the sound stream's resident_stream_set_second_state.
 * @param value Value forwarded to the stream.
 */
void resident_sound_set_stream_second_state(const s32* value)
{
    resident_stream_set_second_state(g_resident_sound->stream, value);
}

/**
 * @brief Count the entries of the loaded sound bank.
 * @param sound Sound system.
 * @return Number of entries, or zero while no bank is loaded or it is still loading.
 */
static inline s32 bank_entry_count(ResidentSound* sound)
{
    if (sound->voice_file_key == 0)
    {
        return 0;
    }

    if (resident_find_resource_request(sound->resource_queue, 0, 0, 8, 0xFFFFFFFF, 0) != 0)
    {
        return 0;
    }

    return *(s32*)sound->voice_table;
}

/**
 * @brief Count the entries of the loaded sound bank.
 * @param sound Sound system.
 * @return Number of entries, or zero while no bank is loaded or it is still loading.
 */
s32 resident_sound_count_bank_entries(ResidentSound* sound)
{
    s32 count;

    if (sound->voice_file_key == 0)
    {
        return 0;
    }

    if (resident_find_resource_request(sound->resource_queue, 0, 0, 8, 0xFFFFFFFF, 0) != 0)
    {
        count = 0;
    }
    else
    {
        count = *(s32*)sound->voice_table;
    }

    return count;
}

/**
 * @brief Read an entry of the loaded sound bank.
 * @param sound Sound system.
 * @param index Entry index.
 * @param second Receives the entry's second halfword, or zero.
 * @return The entry's first halfword, or minus one when there is no such entry.
 */
s32 resident_sound_get_bank_entry(ResidentSound* sound, s32 index, u32* second)
{
    s32 count;
    u16* entry;
    s32 first;

    *second = 0;
    count = bank_entry_count(sound);

    if (count == 0)
    {
        return -1;
    }

    if (index >= count)
    {
        return -1;
    }

    entry = (u16*)((s32*)sound->voice_table + 1) + index * 2;
    first = entry[0];
    *second = entry[1];
    return first;
}

/**
 * @brief Load another sound bank, first releasing everything allocated from the current one.
 * @param sound Sound system.
 * @param key Resource key of the bank.
 */
void resident_sound_switch_bank(ResidentSound* sound, s32 key)
{
    s32 i;

    if (sound->voice_file_key == key)
    {
        return;
    }

    for (i = 0; i < 8; i++)
    {
        if (sound->voice_buffers[i] != 0)
        {
            resident_cancel_resource_requests(g_resource_queue, sound->voice_file_key, (u32)sound->voice_buffers[i], 0,
                                              0xFFFFFFFF, 0);
            resident_queue_allocation_release(g_resident_release_queues, sound->voice_buffers[i]);
            sound->voice_buffers[i] = 0;
        }
    }

    resident_queue_resource_request(sound->resource_queue, key, sound->voice_table, 8, 0x34BC0, 0, 0x800, 0, 1);
    sound->voice_file_key = key;
}

/** Lip sync data of one voice: a mouth level for each span of frames. */
struct SoundVoiceLevels
{
    s32 unk00;
    s32 count;
    s32 frames_offset;
    s32 levels_offset;
};

/**
 * @brief Report whether a sound still holds its slot.
 * @param sound Sound system.
 * @param identifier Slot identifier.
 * @return True while the sound's slot is in use.
 */
static inline bool sound_is_active(ResidentSound* sound, s32 identifier)
{
    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].identifier == identifier)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Get the voice data of a request slot, asking the stream for it the first time.
 * @param sound Sound system.
 * @param identifier Slot identifier.
 * @return The voice data, or zero when there is none.
 */
u32 resident_sound_get_voice_data(ResidentSound* sound, s32 identifier)
{
    if (sound->effects_disabled)
    {
        return 0;
    }

    if (!sound_is_active(sound, identifier))
    {
        return 0;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].identifier == identifier)
        {
            u32 data = sound->slots[i].unk28;

            if (data == 0)
            {
                if (sound->slots[i].value != 0)
                {
                    data = (u32)resident_stream_find_lip_chunk(sound->stream, sound->slots[i].value, sound->slots[i].selector);
                    sound->slots[i].unk28 = data;
                }

                if (data == 0)
                {
                    return 0;
                }
            }

            return data;
        }
    }

    return 0;
}

/**
 * @brief Read a playing voice's level at a time.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param time Time to sample.
 * @return Voice level.
 */
u32 resident_sound_get_voice_level(ResidentSound* sound, s32 identifier, float time)
{
    if (sound->effects_disabled)
    {
        return 0;
    }

    if (!sound_is_active(sound, identifier))
    {
        return 0;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].identifier == identifier)
        {
            SoundVoiceLevels* data = (SoundVoiceLevels*)sound->slots[i].unk28;

            if (data == 0)
            {
                if (sound->slots[i].value != 0)
                {
                    data = (SoundVoiceLevels*)resident_stream_find_lip_chunk(sound->stream, sound->slots[i].value,
                                                            sound->slots[i].selector);
                    sound->slots[i].unk28 = (u32)data;
                }

                if (data == 0)
                {
                    return 0;
                }
            }

            s32 frame = (s32)(3.0f + (sound->slots[i].unk30_float + time));
            u16* frames = (u16*)((u8*)data + data->frames_offset);
            s32 count = data->count;
            u8* levels = (u8*)data + data->levels_offset;

            for (s32 j = 1; j < count; j++)
            {
                if (frames[j] >= frame)
                {
                    return levels[j - 1];
                }
            }

            return 0;
        }
    }

    return 0;
}

/**
 * @brief Get the squared length of a vector's xyz part.
 * @param vector 16-byte aligned vector.
 * @return Squared length.
 */
static inline float vector_length_squared(const float* vector)
{
    float squared[4] __attribute__((aligned(16)));

    vu0_length_squared_xyz(vector, squared);
    return squared[0];
}

/**
 * @brief Place a positional sound for the listener.
 *
 * Moves the position into the listener's space, works out the volume from the distance and the reverb preset's
 * levels (kept in unk451), then pans the sound between the two speakers its angle falls between.
 *
 * @param sound Sound system.
 * @param position World position of the sound.
 * @param arg2 Unused.
 * @param arg3 Unused.
 * @return The two speaker levels packed as two 16-bit halves, or zero without a listener or position.
 */
u32 resident_sound_place(ResidentSound* sound, const float* position, s32 arg2, s32 arg3)
{
    ResidentImageObjectBase* listener = (ResidentImageObjectBase*)sound->listener;

    if (listener == 0)
    {
        return 0;
    }

    if (position == 0)
    {
        return 0;
    }

    if (!listener->matrix_ready)
    {
        listener->update_transform_matrix();
        ResidentImageObjectBase* transform = (ResidentImageObjectBase*)sound->listener;
        transform->unk20e_0 = 1;
        transform->unk20e_1 = 0;
        ee_transpose_matrix(&transform->transposed_transform, &transform->transform);
        func_4D9E70((ResidentImageObjectBase*)sound->listener);
    }
    else if (!listener->unk20e_0)
    {
        ResidentImageObjectBase* transform = (ResidentImageObjectBase*)sound->listener;
        transform->unk20e_0 = 1;
        transform->unk20e_1 = 0;
        ee_transpose_matrix(&transform->transposed_transform, &transform->transform);
        func_4D9E70((ResidentImageObjectBase*)sound->listener);
    }
    else if (!listener->unk20e_2)
    {
        func_4D9E70(listener);
    }

    float local[4] __attribute__((aligned(16)));

    ResidentImageObjectBase* current = (ResidentImageObjectBase*)sound->listener;
    vu0_transform_emission_point(&current->inverse_transform, position, local);
    local[2] -= sound->unk1394;
    float distance_squared = vector_length_squared(local);
    distance_squared = ee_max(distance_squared, 1.0f);
    float distance = sqrtf(distance_squared);
    float volume;

    if (distance < sound->unk13ac[2])
    {
        volume = sound->unk13ac[0];
    }
    else if (distance > sound->unk13ac[3])
    {
        volume = sound->unk13ac[1];
    }
    else
    {
        volume = sound->unk13ac[0]
                 + (sound->unk13ac[1] - sound->unk13ac[0])
                       * ((distance - sound->unk13ac[2]) / (sound->unk13ac[3] - sound->unk13ac[2]));
        volume = ee_min(volume, 126.0f);
        volume = ee_max(volume, 1.0f);
    }

    float gain = (127.0f * sound->range_squared) / distance_squared;
    gain = ee_min(gain, 127.0f);
    gain *= 129.0f * sound->unk34c;

    func_4CF5E0(local);
    float height = local[1];
    local[1] = 0.0f;
    func_4CF5E0(local);
    height = ee_abs(height);
    func_4CF5E0(local);

    float angle = func_00142148(local[2], local[0]);

    if (angle < 0.0f)
    {
        angle += TWO_PI;
    }

    float offset;
    float span;
    s32 i;

    for (i = 0; i < 4; i++)
    {
        s32 next = (i + 1) & 3;
        float start = sound->speaker_angles[i];
        float end = sound->speaker_angles[next];

        if (start > end)
        {
            if (angle >= start)
            {
                offset = angle - start;
                span = (TWO_PI - start) + end;
                break;
            }

            if (angle < end)
            {
                span = (TWO_PI - start) + end;
                offset = (TWO_PI + angle) - start;
                break;
            }
        }
        else if (angle >= start && angle < end)
        {
            span = end - start;
            offset = angle - start;
            break;
        }
    }

    SpeakerPairs pairs = g_speaker_pairs;

    offset = pairs.value[i][0] + offset * (pairs.value[i][1] - pairs.value[i][0]) / span;
    func_4CC1A0(local, offset);

    float x;
    float y;

    if (local[2] < 0.0f && local[3] < 0.707f)
    {
        x = -local[2];
        y = -local[3];
    }
    else
    {
        x = local[2];
        y = local[3];
    }

    x *= gain;
    y *= gain;
    x = ee_min(x, 16383.0f);
    x = ee_max(x, -16383.0f);
    y = ee_min(y, 16383.0f);
    y = ee_max(y, -16383.0f);

    sound->unk451 = ((u32)volume & 0xFF) | 0x80;
    return ((((s32)x) | 0x8000) & 0xFFFF) | ((((s32)y) | 0x8000) << 16);
}

/**
 * @brief Set the object positional sounds are heard from.
 * @param sound Sound system.
 * @param listener Listening object.
 * @param value Stored with the listener; its use is unknown.
 * @param range Distance positional sounds reach.
 */
void resident_sound_set_listener(ResidentSound* sound, void* listener, float value, float range)
{
    sound->listener = listener;
    sound->unk1394 = value;
    sound->range_squared = range * range;
}

/**
 * @brief Set the angle of one surround speaker.
 * @param sound Sound system.
 * @param speaker Speaker index, 0 to 3.
 * @param angle Speaker angle in radians.
 */
void resident_sound_set_speaker_angle(ResidentSound* sound, s32 speaker, float angle)
{
    sound->speaker_angles[speaker] = angle;
}

/**
 * @brief Set the angles of all four surround speakers.
 * @param sound Sound system.
 * @param angles Four speaker angles in radians.
 */
void resident_sound_set_speaker_angles(ResidentSound* sound, const float* angles)
{
    sound->speaker_angles[0] = angles[0];
    sound->speaker_angles[1] = angles[1];
    sound->speaker_angles[2] = angles[2];
    sound->speaker_angles[3] = angles[3];
}

/**
 * @brief Allocate a buffer for a resource and start loading it.
 * @param sound Sound system.
 * @param key Resource key.
 * @return One when the load started, zero while busy or when the buffer can't be allocated.
 */
s32 resident_sound_load_resource(ResidentSound* sound, s32 key)
{
    if (sound->state != RESIDENT_SOUND_IDLE)
    {
        return 0;
    }

    delete sound->unk400;
    sound->unk404 = resident_get_resource_size(sound->archive, key);
    sound->unk400 = (u8*)memalign(0x40, sound->unk404);

    if (sound->unk400 == 0)
    {
        return 0;
    }

    resident_queue_resource_request(sound->resource_queue, key, sound->unk400, 5, 0x34BC0, 0, 0, 0, 1);
    sound->state = RESIDENT_SOUND_LOADING;
    return 1;
}

/**
 * @brief Upload a sound file through the stream into a slot, using that slot's unk454 value.
 * @param sound Sound system.
 * @param file Sound file to upload; kept at unk360.
 * @param index Stream slot, and index into unk454.
 * @param append True to add to the slot's existing data.
 * @return Zero while the sound system is busy, otherwise one.
 */
s32 resident_sound_upload_file(ResidentSound* sound, const void* file, s32 index, bool append)
{
    if (sound->state != RESIDENT_SOUND_IDLE)
    {
        return 0;
    }

    sound->unk360 = file;
    resident_stream_queue_sequence(sound->stream, file, sound->unk454[index], index, 0, append, 0);
    sound->state = RESIDENT_SOUND_UPLOADING;
    return 1;
}

/**
 * @brief Send each entry of a setup table to the stream, waiting for each reply and keeping its first word in unk454.
 * @param sound Sound system.
 * @param count Number of entries, below 32.
 * @param entries Setup table.
 * @return One when sent, zero when count is too large.
 */
s32 resident_sound_send_setup(ResidentSound* sound, s32 count, const ResidentSoundSetupEntry* entries)
{
    s32 i;
    u32 handle;
    u32 reply[16];

    if (count >= 32)
    {
        return 0;
    }

    for (i = 0; i < count; i++)
    {
        handle = resident_stream_send_setup(sound->stream, reply, 0, 0, i, entries[i].unk00, entries[i].unk04, entries[i].unk08,
                               entries[i].unk0C, entries[i].unk10);

        while (resident_sif_is_request_pending(&g_sif, handle))
        {
        }

        sound->unk454[i] = reply[0];
    }

    return 1;
}

/**
 * @brief Wake the sound stream's thread, if the sound system has a stream.
 * @param sound Sound system.
 */
void resident_sound_wake_stream(ResidentSound* sound)
{
    ResidentSoundStream* stream = sound->stream;

    if (stream != 0)
    {
        resident_stream_wake_thread(stream, 0);
    }
}

/**
 * @brief Clear the target of every active request slot aimed at an object.
 * @param sound Sound system.
 * @param target Object to forget.
 */
void resident_sound_clear_target(ResidentSound* sound, ResidentSoundEmitter* target)
{
    s32 i;

    DIntr();

    for (i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].target == target)
        {
            sound->slots[i].target = 0;
        }
    }

    EIntr();
}

/**
 * @brief Clear the target's has_sound flag once no other active slot plays from it.
 * @param sound Sound system whose slots are searched.
 * @param slot Slot that stops playing from its target.
 */
static inline void release_slot_target(ResidentSound* sound, ResidentRequestSlot* slot)
{
    s32 i;

    if (slot->target == 0)
    {
        return;
    }

    for (i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && slot != &sound->slots[i] && sound->slots[i].target == slot->target)
        {
            break;
        }
    }

    if (i == 60)
    {
        ResidentSoundEmitter* target = slot->target;
        target->has_sound = 0;
    }
}

/**
 * @brief Request callback: free each listed request slot whose reply word is zero, then clear unk348.
 * @param reply Reply from the IOP, one word per entry of sound->unk2F8.
 * @param sound Sound system.
 */
void resident_sound_free_finished_slots(const u32* reply, ResidentSound* sound)
{
    for (s32 i = 0; i < 15; i++)
    {
        ResidentRequestSlot* slot = sound->unk2F8[i];

        if (slot == 0)
        {
            break;
        }

        if (reply[i] == 0)
        {
            slot->active = 0;
            slot->started = 0;
            release_slot_target(g_resident_sound, slot);
        }
    }

    sound->unk348 = 0;
}

void resident_sound_ignore_reply(void* object)
{
}

/**
 * @brief Play request callback: keep the voice handle, and send the stop that was waiting for it.
 * @param reply Reply from the IOP; its first word is the voice handle.
 * @param slot Request slot.
 */
void resident_sound_on_play_reply(void* reply, ResidentRequestSlot* slot)
{
    slot->started = 1;
    slot->handle = *(u32*)reply;

    if (slot->stop_requested == 0)
    {
        return;
    }

    resident_stream_stop(g_resident_sound->stream, 0, resident_sound_ignore_reply, 0, slot->handle, slot->stop_mode, 0);

    if (slot->unk03 == 0)
    {
        slot->active = 0;
    }

    slot->started = 0;
    release_slot_target(g_resident_sound, slot);
}

/**
 * @brief Request callback: push the music handle at the start of a reply onto the sound system's handles.
 * @param reply Reply from the IOP.
 */
void resident_sound_push_music_handle(const void* reply)
{
    ResidentSound* sound = g_resident_sound;
    u32 handle = *(const u32*)reply;
    u32 index = sound->unk34;
    sound->unk34 = index + 1;
    sound->music_handles[index] = handle;
}

/**
 * @brief Request callback: push the stream's answer onto the sound system's stack.
 * @param reply Reply from the IOP.
 */
void resident_sound_push_stream_answer(void* reply)
{
    u32 handle = resident_stream_set_first_state(g_resident_sound->stream, (const s32*)reply);

    g_resident_sound->music_handles[g_resident_sound->unk34++] = handle;
    g_resident_sound->unk338 = handle;
    g_resident_sound->unk452 = 0;
}

/**
 * @brief Ask the sound stream whether its thread's first state is set.
 * @param sound Sound system.
 * @return Nonzero when it is.
 */
s32 resident_sound_is_stream_state_set(ResidentSound* sound)
{
    return resident_stream_query(sound->stream, 0, 0, 0, 1) != 0;
}

/**
 * @brief Find a free sound slot, starting at the cursor and advancing it past every slot looked at.
 * @param receiver Sound system.
 * @return Free slot index, or -1 when all sixty are in use.
 */
static inline s32 find_available_request_slot(ResidentSound* receiver)
{
    s32 i;
    s32 slot;

    for (i = 0; i < 60; i++)
    {
        slot = receiver->cursor;

        if (receiver->slots[slot].active == 0)
        {
            receiver->cursor = slot + 1;

            if (slot + 1 >= 60)
            {
                receiver->cursor = 0;
            }

            return slot;
        }

        receiver->cursor = slot + 1;

        if (slot + 1 >= 60)
        {
            receiver->cursor = 0;
        }
    }

    return -1;
}

/**
 * @brief Locate a slot in the slot array.
 * @param slots Slot array.
 * @param index Valid slot index.
 * @return The slot.
 */
static inline ResidentRequestSlot* request_slot(ResidentRequestSlot* slots, s32 index)
{
    return &slots[index];
}

/**
 * @brief Stop music.
 * @param sound Sound system.
 * @param fade_frames Frames to fade out over, or zero to stop at once.
 * @param key Music to stop, or -1 for all of it.
 * @return One when music was stopped or music is disabled, otherwise zero.
 */
s32 resident_sound_stop_music(ResidentSound* sound, s32 fade_frames, s32 key)
{
    if (sound->music_disabled)
    {
        return 1;
    }

    if (sound->music_count == 0)
    {
        return 0;
    }

    if (sound->music_count != sound->unk34)
    {
        resident_sound_update(sound, 0);
        return 0;
    }

    if (key == -1)
    {
        while (sound->music_count != 0)
        {
            sound_remove_music_track(sound, 0, fade_frames);
        }

        return 1;
    }

    for (s32 i = 0; i < sound->music_count; i++)
    {
        if (sound->music_keys[i] == key)
        {
            sound_remove_music_track(sound, i, fade_frames);
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Start uploading a sound file's sequence, keeping the stream's reply in unk378.
 * @param sound Sound system.
 * @param file Sound file; kept at unk360.
 * @param size Size of the file; kept at unk35c.
 * @return Zero while the sound system is busy, otherwise one.
 */
static inline s32 sound_start_sequence(ResidentSound* sound, const void* file, u32 size)
{
    if (sound->state != RESIDENT_SOUND_IDLE)
    {
        return 0;
    }

    sound->unk360 = file;
    sound->unk35c = size;
    sound->state = 1;
    resident_stream_queue_sequence(sound->stream, file, 0, 0, &sound->unk378, 0, 0);
    return 1;
}

/**
 * @brief Free a slot's sound data when the slot owns it.
 * @param slot Sound slot.
 */
static inline void sound_free_slot_buffer(ResidentRequestSlot* slot)
{
    if (slot->owns_buffer)
    {
        operator delete(slot->buffer);
        slot->buffer = 0;
        slot->owns_buffer = 0;
    }
}

/**
 * @brief Update the sound system; main calls it until sound->state is zero.
 *
 * Runs the stream's queues and the current loading step. Unless a step is still waiting, it then retires music
 * tracks that have stopped, asks the stream which started slots are still playing, sends the placement of every
 * positional sound in batches of eight, reads the music position, and moves each slot's bank load along.
 *
 * @param sound Sound system.
 * @param mode Nonzero to count frame time on the started slots.
 * @return One.
 */
s32 resident_sound_update(ResidentSound* sound, s32 mode)
{
    resident_sif_flush_commands(&g_sif);
    resident_stream_run_bank_loads(sound->stream);
    resident_stream_run_sequence_uploads(sound->stream);

    switch (sound->state)
    {
        case 1:
            if (resident_stream_is_sequence_queued(sound->stream, sound->unk360))
            {
                break;
            }

            sound->state = RESIDENT_SOUND_IDLE;
            resident_stream_play_slot_packed(sound->stream, 0, (void (*)(void*, ResidentRequestSlot*))resident_sound_push_music_handle, 0, sound->unk378, 0,
                          sound->unk3c, sound->unk378, 0x7F400000);

            if (sound->unk400)
            {
                delete[] sound->unk400;
                sound->unk400 = 0;
            }

            break;

        case 2:
            if (resident_find_resource_request(sound->resource_queue, 0, 0, 4, 0xFFFFFFFF, 0))
            {
                break;
            }

            sound->state = RESIDENT_SOUND_IDLE;
            sound_start_sequence(sound, sound->unk400, sound->unk404);
            break;

        case 3:
        {
            const ResidentMusicEntry* entry = &sound->music_entries[sound->unk40 - 1];

            if (sound->unk4d4 == 0)
            {
                s32 volume = sound->unk3c;

                if (resident_stream_thread_request_1(sound->stream->thread, 0, resident_sound_push_stream_answer, 0,
                                  resident_archive_get_resource_position(sound->archive, entry->resource), volume, 0))
                {
                    sound->state = RESIDENT_SOUND_IDLE;
                }
            }
            else
            {
                s32 volume = sound->unk3c;

                if (resident_stream_thread_request_5(sound->stream->thread, 0, resident_sound_push_stream_answer, 0, (u32*)sound->unk4d4,
                                  resident_archive_get_resource_position(sound->archive, entry->resource), volume))
                {
                    sound->state = RESIDENT_SOUND_IDLE;
                }
            }

            break;
        }

        case RESIDENT_SOUND_UPLOADING:
            if (resident_stream_is_sequence_queued(sound->stream, sound->unk360))
            {
                break;
            }

            sound->state = RESIDENT_SOUND_IDLE;
            break;

        case RESIDENT_SOUND_LOADING:
            if (resident_find_resource_request(sound->resource_queue, 0, 0, 5, 0xFFFFFFFF, 0))
            {
                break;
            }

            FlushCache(0);
            sound->state = 6;
            resident_stream_queue_sequence(sound->stream, sound->unk400, sound->unk454[0], 0, 0, 0, 0);
            break;

        case 6:
            if (resident_stream_is_sequence_queued(sound->stream, sound->unk400))
            {
                break;
            }

            sound->state = RESIDENT_SOUND_IDLE;

            if (sound->unk400)
            {
                delete[] sound->unk400;
                sound->unk400 = 0;
            }

            break;

        case 7:
        {
            const ResidentMusicEntry* entry = &sound->music_entries[sound->unk40 - 1];
            s32 volume = sound->unk3c;

            if (resident_stream_thread_request_1(sound->stream->thread, 0, resident_sound_push_stream_answer, 0,
                              resident_archive_get_resource_position(sound->archive, entry->resource), volume, 1))
            {
                sound->state = RESIDENT_SOUND_IDLE;
            }

            break;
        }

        case 8:
        {
            s32 volume = sound->unk3c;

            if (resident_stream_thread_request_3(sound->stream->thread, 0, resident_sound_push_stream_answer, 0, (u32*)sound->unk368, volume))
            {
                sound->state = RESIDENT_SOUND_IDLE;
            }

            break;
        }

        case RESIDENT_SOUND_CHANGING_REVERB:
            switch (sound->reverb_step)
            {
                case 0:
                {
                    s32 i;

                    for (i = 0; i < 60; i++)
                    {
                        if (sound->slots[i].active)
                        {
                            break;
                        }
                    }

                    if (i == 60)
                    {
                        if (resident_stream_command_1b(sound->stream, g_reverb_presets[sound->reverb_preset].unk00,
                                          g_reverb_presets[sound->reverb_preset].unk02, g_reverb_presets[sound->reverb_preset].unk04,
                                          g_reverb_presets[sound->reverb_preset].unk06))
                        {
                            sound->unk13ac[0] = g_reverb_presets[sound->reverb_preset].unk08;
                            sound->unk13ac[1] = g_reverb_presets[sound->reverb_preset].unk0a;
                            sound->unk13ac[2] = g_reverb_presets[sound->reverb_preset].unk0c;
                            sound->unk13ac[3] = g_reverb_presets[sound->reverb_preset].unk0e;
                            sound->reverb_step = 1;
                        }
                    }

                    break;
                }

                case 1:
                    sound->unk358 = resident_stream_command_1c(sound->stream, &sound->unk378, 0, 0);

                    if (sound->unk358)
                    {
                        sound->reverb_step = 2;
                    }

                    break;

                case 2:
                    if (!resident_stream_is_request_running(sound->stream, sound->unk358))
                    {
                        if (sound->unk378 == 1)
                        {
                            sound->state = RESIDENT_SOUND_IDLE;
                        }
                        else
                        {
                            sound->reverb_step = 0;
                        }
                    }

                    break;
            }

        case RESIDENT_SOUND_IDLE:
        default:
        {
            if (sound->music_count != 0 && sound->music_count == sound->unk34)
            {
                if (sound->unk111)
                {
                    bool busy = false;

                    for (s32 i = 0; i < sound->music_count; i++)
                    {
                        if (sound->unk38 != i && resident_stream_is_request_running(sound->stream, sound->unk104[i]))
                        {
                            busy = true;
                            break;
                        }
                    }

                    if (!busy)
                    {
                        sound->unk111 = 0;

                        for (s32 i = 0; i < sound->music_count; i++)
                        {
                            if (sound->unk38 != i && sound->music_status[i][0] == 0)
                            {
                                sound_drop_music_track(sound, i);
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for (s32 i = 0; i < sound->music_count; i++)
                    {
                        if (sound->unk38 == i)
                        {
                            if (!resident_stream_query(sound->stream, (u32)sound->music_status[i], 0, 0, sound->music_handles[i]))
                            {
                                sound_drop_music_track(sound, i);
                                i--;
                            }
                        }
                        else
                        {
                            sound->unk111 = 1;

                            if ((sound->unk104[i] = resident_stream_query(sound->stream, (u32)sound->music_status[i], 0, 0,
                                                                  sound->music_handles[i])) == 0)
                            {
                                sound->unk111 = 0;
                            }
                        }
                    }
                }
            }

            if (!sound->unk348)
            {
                s32 cursor = sound->unk334;
                s32 count = 0;

                for (s32 i = 0; i < 15; i++)
                {
                    sound->unk2F8[i] = 0;
                }

                for (s32 i = 0; i < 60; i++)
                {
                    ResidentRequestSlot* slot = &sound->slots[cursor];

                    if (++cursor >= 60)
                    {
                        cursor = 0;
                    }

                    if (slot->active && slot->started)
                    {
                        sound->unk208[count] = slot->handle;
                        sound->unk2F8[count] = slot;

                        if (++count >= 15)
                        {
                            break;
                        }
                    }
                }

                if (count != 0)
                {
                    sound->unk348 = 1;

                    if (!resident_stream_send_words(sound->stream, 0, resident_sound_free_finished_slots, sound, sound->unk208, count))
                    {
                        sound->unk348 = 0;
                    }
                }
            }

            u32 placements[8];
            u32 handles[8];
            s32 batch = 0;

            for (s32 i = 0; i < 60; i++)
            {
                if (sound->slots[i].active && sound->slots[i].started && sound->slots[i].target != 0)
                {
                    float position[4];
                    ResidentSoundEmitter* target = sound->slots[i].target;

                    position[0] = target->unk90[0][3];
                    position[1] = target->unk90[1][3];
                    position[2] = target->unk90[2][3];
                    position[3] = 1.0f;

                    if (sound->slots[i].unk1c)
                    {
                        placements[batch] = 0;
                        sound->slots[i].unk38 = 0;
                    }
                    else
                    {
                        sound->slots[i].unk38 = placements[batch] = resident_sound_place(sound, position, sound->slots[i].unk38, 1);
                    }

                    handles[batch] = sound->slots[i].handle | (sound->unk451 << 24);

                    if (++batch >= 8)
                    {
                        {
                            ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
                            u32* arguments = g_sif.get_request_arguments();

                            if (arguments)
                            {
                                for (s32 j = 0; j < 8; j++)
                                {
                                    *arguments++ = handles[j];
                                    *arguments++ = placements[j];
                                }

                                resident_sif_request(&g_sif, 0x16, 0, 0, 0, 0);
                            }

                            batch = 0;
                        }

                    }
                }
            }

            if (batch > 0)
            {
                ResidentSemaphoreLock lock(g_sif.get_request_semaphore());
                u32* arguments = g_sif.get_request_arguments();

                if (arguments)
                {
                    for (s32 j = 0; j < batch; j++)
                    {
                        *arguments++ = handles[j];
                        *arguments++ = placements[j];
                    }

                    for (; batch < 8; batch++)
                    {
                        *arguments++ = 0;
                        *arguments++ = 0;
                    }

                    resident_sif_request(&g_sif, 0x16, 0, 0, 0, 0);
                }
            }

            if (sound->music_count != 0 && sound->unk38 >= 0)
            {
                if (sound->unk356)
                {
                    if (!resident_stream_is_request_running(sound->stream, sound->unk374))
                    {
                        sound->unk356 = 0;
                        sound->unk3bc = sound->unk3c0[0];
                    }
                }
                else
                {
                    sound->unk374 = resident_stream_command_19(sound->stream, sound->unk3c0, 0, 0);

                    if (sound->unk374)
                    {
                        sound->unk356 = 1;
                    }
                }
            }

            for (s32 i = 0; i < 60; i++)
            {
                if (!sound->slots[i].active)
                {
                    continue;
                }

                if (sound->slots[i].started && mode != 0)
                {
                    sound->slots[i].unk30_float += g_frame_ticks;
                }

                switch (sound->slots[i].unk03)
                {
                    case 1:
                        if (resident_find_resource_request(sound->resource_queue, 0, (u32)sound->slots[i].buffer, 0, 0xFFFFFFFF, 0))
                        {
                            break;
                        }

                        if (sound->slots[i].stop_requested)
                        {
                            sound->slots[i].active = 0;
                            sound->slots[i].started = 0;
                            sound->slots[i].unk03 = 0;
                            DIntr();
                            release_slot_target(sound, &sound->slots[i]);
                            EIntr();
                            sound_free_slot_buffer(&sound->slots[i]);
                        }
                        else
                        {
                            FlushCache(0);

                            if (resident_stream_queue_bank(sound->stream, sound->slots[i].buffer, 0, 0, sound->slots[i].unk2c, sound->slots[i].unk34, sound->slots[i].unk38,
                                              sound->slots[i].unk06[0]) == 1)
                            {
                                sound->slots[i].unk03 = 2;
                            }
                        }

                        break;

                    case 2:
                    {
                        s32 status = resident_stream_is_bank_queued(sound->stream, sound->slots[i].buffer);

                        if (status < 0)
                        {
                            sound->slots[i].unk03 = 3;
                            sound->slots[i].unk28 = (u32)resident_stream_request_bank_waves(sound->stream, (u32)resident_sound_on_play_reply, (u32)&sound->slots[i]);
                        }

                        if (status == 0)
                        {
                            sound->slots[i].stop_requested = 1;
                        }

                        if (status != 0)
                        {
                            break;
                        }
                    }

                    case 3:
                        if (resident_stream_is_bank_queued(sound->stream, sound->slots[i].buffer))
                        {
                            break;
                        }

                        if (sound->slots[i].stop_requested)
                        {
                            sound->slots[i].active = 0;
                            sound->slots[i].started = 0;
                            DIntr();
                            release_slot_target(sound, &sound->slots[i]);
                            EIntr();
                        }

                        sound->slots[i].unk03 = 0;
                        sound_free_slot_buffer(&sound->slots[i]);
                        break;
                }
            }

            return 1;
        }
    }

    return 1;
}

/**
 * @brief Send voice command 4 to a started sound.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param first First command argument.
 * @param second Second command argument.
 */
void resident_sound_voice_command_4(ResidentSound* sound, s32 identifier, s32 first, s32 second)
{
    if (sound->effects_disabled)
    {
        return;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].started && sound->slots[i].identifier == identifier)
        {
            resident_stream_send_voice_command(sound->stream, 0, 0, 0, sound->slots[i].handle, 4, first, second);
            return;
        }
    }
}

/**
 * @brief Send voice command 5 to a started sound.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param first First command argument.
 * @param second Second command argument.
 */
void resident_sound_voice_command_5(ResidentSound* sound, s32 identifier, s32 first, s32 second)
{
    if (sound->effects_disabled)
    {
        return;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].started && sound->slots[i].identifier == identifier)
        {
            resident_stream_send_voice_command(sound->stream, 0, 0, 0, sound->slots[i].handle, 5, first, second);
            return;
        }
    }
}

/**
 * @brief Send voice command 1 to a started sound that has no target.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param first First command argument.
 * @param second Second command argument.
 */
void resident_sound_voice_command_1(ResidentSound* sound, s32 identifier, s32 first, s32 second)
{
    if (sound->effects_disabled)
    {
        return;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].started && sound->slots[i].identifier == identifier)
        {
            if (sound->slots[i].target != 0)
            {
                return;
            }

            resident_stream_send_voice_command(sound->stream, 0, 0, 0, sound->slots[i].handle, 1, first, second);
            return;
        }
    }
}

/**
 * @brief Send voice command 0 to a started sound, optionally recording its new volume.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param volume Volume, sent as the first command argument.
 * @param second Second command argument.
 * @param keep_volume Zero to also store volume in the slot.
 */
void resident_sound_set_voice_volume(ResidentSound* sound, s32 identifier, s32 volume, s32 second, s32 keep_volume)
{
    if (sound->effects_disabled)
    {
        return;
    }

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].started && sound->slots[i].identifier == identifier)
        {
            if (!keep_volume)
            {
                sound->slots[i].volume = volume;
            }

            if (!sound->slots[i].unk1c)
            {
                resident_stream_send_voice_command(sound->stream, 0, 0, 0, sound->slots[i].handle, 0, volume, second);
            }

            return;
        }
    }
}

/**
 * @brief Clear the target of every active request slot aimed at an object, with interrupts disabled.
 * @param sound Sound system.
 * @param target Object to forget.
 */
extern "C" void resident_sound_iclear_target(ResidentSound* sound, ResidentSoundEmitter* target)
{
    ResidentInterruptLock lock;

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].target == target)
        {
            sound->slots[i].target = 0;
        }
    }
}

/**
 * @brief Stop every sound, or mark each one to stop once the stream has started it.
 * @param sound Sound system.
 * @param mode Stop mode passed to the stream.
 * @return Always true.
 */
bool resident_sound_stop_all(ResidentSound* sound, s32 mode)
{
    if (sound->effects_disabled)
    {
        return true;
    }

    ResidentInterruptLock lock;

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active)
        {
            if (sound->slots[i].unk03)
            {
                sound->slots[i].stop_requested = 1;
                sound->slots[i].stop_mode = mode;
            }
            else if (!sound->slots[i].started)
            {
                sound->slots[i].stop_requested = 1;
                sound->slots[i].stop_mode = mode;
            }
            else
            {
                // TODO: The target reads the handle here and never uses it; the call below reads it again.
                u32 handle = sound->slots[i].handle;
                sound->slots[i].active = 0;
                sound->slots[i].started = 0;

                release_slot_target(sound, &sound->slots[i]);

                if (sound->slots[i].owns_buffer)
                {
                    delete sound->slots[i].buffer;
                    sound->slots[i].buffer = 0;
                    sound->slots[i].owns_buffer = 0;
                }

                lock.unlock();
                resident_stream_stop(sound->stream, 0, resident_sound_ignore_reply, 0, sound->slots[i].handle, mode, 0);
                lock.relock();
            }
        }
    }

    return true;
}

/**
 * @brief Stop a sound, or mark it to stop once the stream has started it.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @param mode Stop mode passed to the stream.
 * @return True when the sound was found (or effects are disabled), false when no slot holds it.
 */
bool resident_sound_stop(ResidentSound* sound, s32 identifier, s32 mode)
{
    if (sound->effects_disabled)
    {
        return true;
    }

    ResidentInterruptLock lock;

    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].identifier == identifier)
        {
            if (sound->slots[i].unk03)
            {
                sound->slots[i].stop_requested = 1;
                sound->slots[i].stop_mode = mode;
                return true;
            }

            if (!sound->slots[i].started)
            {
                sound->slots[i].stop_requested = 1;
                sound->slots[i].stop_mode = mode;
                return true;
            }

            u32 handle = sound->slots[i].handle;
            sound->slots[i].active = 0;
            sound->slots[i].started = 0;

            release_slot_target(sound, &sound->slots[i]);

            if (sound->slots[i].owns_buffer)
            {
                delete sound->slots[i].buffer;
                sound->slots[i].buffer = 0;
                sound->slots[i].owns_buffer = 0;
            }

            lock.unlock();
            resident_stream_stop(sound->stream, 0, resident_sound_ignore_reply, 0, handle, mode, 0);
            lock.relock();
            return true;
        }
    }

    return false;
}

/**
 * @brief Report whether a sound still holds its slot.
 * @param sound Sound system.
 * @param identifier Identifier resident_sound_play returned.
 * @return One while the sound's slot is in use, otherwise zero.
 */
s32 resident_sound_is_active(ResidentSound* sound, s32 identifier)
{
    for (s32 i = 0; i < 60; i++)
    {
        if (sound->slots[i].active && sound->slots[i].identifier == identifier)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Free every voice read ahead of time, cancelling reads still in progress.
 * @param sound Sound system.
 */
void resident_sound_free_read_ahead(ResidentSound* sound)
{
    for (s32 i = 0; i < 8; i++)
    {
        if (sound->voice_buffers[i] != 0)
        {
            resident_cancel_resource_requests(g_resource_queue, sound->voice_file_key, (u32)sound->voice_buffers[i], 0,
                                              -1, 0);
            resident_queue_allocation_release(g_resident_release_queues, sound->voice_buffers[i]);
            sound->voice_buffers[i] = 0;
        }
    }
}

/**
 * @brief Free one voice read ahead of time, cancelling its read if it is still in progress.
 * @param sound Sound system.
 * @param voice Index of the voice in the voice table.
 */
void resident_sound_free_read_ahead_voice(ResidentSound* sound, s32 voice)
{
    for (s32 i = 0; i < 8; i++)
    {
        if (sound->voice_buffers[i] != 0 && sound->voice_indices[i] == voice)
        {
            resident_cancel_resource_requests(g_resource_queue, sound->voice_file_key, (u32)sound->voice_buffers[i], 0,
                                              -1, 0);
            resident_queue_allocation_release(g_resident_release_queues, sound->voice_buffers[i]);
            sound->voice_buffers[i] = 0;
        }
    }
}

/**
 * @brief Count the voices in the voice table.
 * @param sound Sound system.
 * @return Voice count, or zero while there is no table or it is still being read.
 */
static inline s32 sound_voice_count(ResidentSound* sound)
{
    if (sound->voice_file_key == 0)
    {
        return 0;
    }

    if (resident_find_resource_request(sound->resource_queue, 0, 0, SOUND_VOICE_TABLE_READ_TAG, -1, 0))
    {
        return 0;
    }

    return sound->voice_table->count;
}

/**
 * @brief Read a voice into one of the read-ahead buffers.
 * @param sound Sound system.
 * @param voice Index of the voice in the voice table.
 * @return Zero once the read is queued, or -1 when the voice can't be read now.
 */
s32 resident_sound_read_ahead_voice(ResidentSound* sound, s32 voice)
{
    if (resident_find_resource_request(sound->resource_queue, 0, 0, SOUND_VOICE_TABLE_READ_TAG, -1, 0))
    {
        return -1;
    }

    if (sound_voice_count(sound) <= voice)
    {
        return -1;
    }

    for (s32 i = 0; i < 8; i++)
    {
        if (sound->voice_buffers[i] == 0)
        {
            u32 block_count = 0;
            s32 block;
            u8** buffer;
            u32 size;
            s32 count = sound_voice_count(sound);

            if (count == 0)
            {
                block = -1;
            }
            else if (voice >= count)
            {
                block = -1;
            }
            else
            {
                ResidentVoiceTable* table = sound->voice_table;
                block_count = table->entries[voice].block_count;
                block = table->entries[voice].block;
            }

            if (block == -1)
            {
                return -1;
            }

            size = block_count * SOUND_BLOCK_SIZE;
            u8** buffers = sound->voice_buffers;
            buffer = &buffers[i];
            *buffer = (u8*)memalign(64, size);

            if (*buffer == 0)
            {
                return -1;
            }

            sound->voice_indices[i] = voice;
            resident_queue_resource_range_request(sound->resource_queue, sound->voice_file_key, *buffer, block, size, SOUND_VOICE_READ_TAG,
                          SOUND_VOICE_READ_PRIORITY, 0);
            return 0;
        }
    }

    return -1;
}

/**
 * @brief Look up where a voice's data is in the voice file.
 * @param sound Sound system.
 * @param voice Index of the voice in the voice table.
 * @param block_count Receives the data's size in blocks; left alone when the voice isn't in the table.
 * @return First block of the data, or -1 when the voice isn't in the table.
 */
static inline s32 sound_voice_block(ResidentSound* sound, s32 voice, u32* block_count)
{
    s32 count = sound_voice_count(sound);

    if (count == 0)
    {
        return -1;
    }

    if (voice >= count)
    {
        return -1;
    }

    ResidentVoiceTable* table = sound->voice_table;
    *block_count = table->entries[voice].block_count;
    return table->entries[voice].block;
}

/**
 * @brief Check whether a voice file is set.
 * @param sound Sound system.
 * @return True when there is one.
 */
static inline bool sound_has_voice_file(const ResidentSound* sound)
{
    return sound->voice_file_key != 0;
}

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
s32 resident_sound_play_voice_at(ResidentSound* sound, s32 voice, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low)
{
    if (sound->effects_disabled)
    {
        return 1;
    }

    if (sound->state == 9)
    {
        return -1;
    }

    if (!sound_has_voice_file(sound))
    {
        return -1;
    }

    if (sound_voice_count(sound) <= voice)
    {
        return -1;
    }

    if (resident_find_resource_request(sound->resource_queue, 0, 0, SOUND_VOICE_TABLE_READ_TAG, -1, 0))
    {
        return -1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    u32 block_count = 0;
    s32 block = sound_voice_block(sound, voice, &block_count);

    if (block == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    bool preloaded = false;

    for (s32 j = 0; j < 8; j++)
    {
        if (sound->voice_buffers[j] && sound->voice_indices[j] == voice)
        {
            sound->slots[slot].buffer = sound->voice_buffers[j];
            preloaded = true;
            sound->voice_buffers[j] = 0;
            break;
        }
    }

    if (!preloaded)
    {
        sound->slots[slot].buffer = (u8*)memalign(64, block_count * SOUND_BLOCK_SIZE);

        if (sound->slots[slot].buffer == 0)
        {
            return -1;
        }
    }

    float position[4];
    func_4DA730(emitter, position);
    emitter->has_sound = 1;
    u32 placement = resident_sound_place(sound, position, 0, 0);
    sound->slots[slot].unk28 = 0;
    sound->slots[slot].active = 1;
    sound->slots[slot].started = 0;
    sound->slots[slot].stop_requested = 0;
    sound->slots[slot].unk03 = 1;
    sound->slots[slot].owns_buffer = 1;
    s32* identifier = &sound->slots[slot].identifier;
    *identifier = sound->next_identifier;
    sound->slots[slot].target = emitter;
    sound->slots[slot].unk30 = 0;
    sound->slots[slot].selector = 0;
    sound->slots[slot].value = 0;
    sound->slots[slot].volume = volume;
    sound->slots[slot].unk1c = 0;
    sound->slots[slot].unk2c = value;
    sound->slots[slot].unk34 = (u32)volume << 24 | ((u32)low & 0xFFFF);
    sound->slots[slot].unk38 = placement;
    sound->slots[slot].unk06[0] = sound->unk451;

    if (!preloaded)
    {
        resident_queue_resource_range_request(sound->resource_queue, sound->voice_file_key, sound->slots[slot].buffer, block,
                      block_count * SOUND_BLOCK_SIZE, SOUND_VOICE_READ_TAG, SOUND_VOICE_READ_PRIORITY, 0);
    }

    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return *identifier;
}

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
s32 resident_sound_play_voice_number(ResidentSound* sound, s32 voice, s32 value, s32 volume, s32 pan, s32 low)
{
    if (sound->effects_disabled)
    {
        return 1;
    }

    if (sound->state == 9)
    {
        return -1;
    }

    if (!sound_has_voice_file(sound))
    {
        return -1;
    }

    if (sound_voice_count(sound) <= voice)
    {
        return -1;
    }

    if (resident_find_resource_request(sound->resource_queue, 0, 0, SOUND_VOICE_TABLE_READ_TAG, -1, 0))
    {
        return -1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    u32 block_count = 0;
    s32 block = sound_voice_block(sound, voice, &block_count);

    if (block == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    bool preloaded = false;

    for (s32 j = 0; j < 8; j++)
    {
        if (sound->voice_buffers[j] && sound->voice_indices[j] == voice)
        {
            sound->slots[slot].buffer = sound->voice_buffers[j];
            preloaded = true;
            sound->voice_buffers[j] = 0;
            break;
        }
    }

    if (!preloaded)
    {
        sound->slots[slot].buffer = (u8*)memalign(64, block_count * SOUND_BLOCK_SIZE);

        if (sound->slots[slot].buffer == 0)
        {
            return -1;
        }
    }

    sound->slots[slot].unk28 = 0;
    sound->slots[slot].active = 1;
    sound->slots[slot].started = 0;
    sound->slots[slot].stop_requested = 0;
    sound->slots[slot].unk03 = 1;
    sound->slots[slot].owns_buffer = 1;
    s32* identifier = &sound->slots[slot].identifier;
    *identifier = sound->next_identifier;
    sound->slots[slot].target = 0;
    sound->slots[slot].unk30 = 0;
    sound->slots[slot].selector = 0;
    sound->slots[slot].value = 0;
    sound->slots[slot].volume = volume;
    sound->slots[slot].unk1c = 0;
    sound->slots[slot].unk2c = value;
    sound->slots[slot].unk34 = ((u32)low & 0xFFFF) | ((u32)volume << 24 | (u32)pan << 16);
    sound->slots[slot].unk38 = 0;
    sound->slots[slot].unk06[0] = 0;

    if (!preloaded)
    {
        resident_queue_resource_range_request(sound->resource_queue, sound->voice_file_key, sound->slots[slot].buffer, block,
                      block_count * SOUND_BLOCK_SIZE, SOUND_VOICE_READ_TAG, SOUND_VOICE_READ_PRIORITY, 0);
    }

    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return *identifier;
}

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
                  s32 owns_buffer)
{
    if (sound->effects_disabled)
    {
        if (owns_buffer)
        {
            delete buffer;
        }

        return 1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    sound->slots[slot].buffer = buffer;
    float position[4];
    func_4DA730(emitter, position);
    emitter->has_sound = 1;
    u32 placement = resident_sound_place(sound, position, 0, 0);
    sound->slots[slot].unk28 = 0;
    sound->slots[slot].active = 1;
    sound->slots[slot].started = 0;
    sound->slots[slot].stop_requested = 0;
    sound->slots[slot].unk03 = 1;
    sound->slots[slot].owns_buffer = owns_buffer;
    sound->slots[slot].identifier = sound->next_identifier;
    sound->slots[slot].target = emitter;
    sound->slots[slot].unk30 = 0;
    sound->slots[slot].selector = 0;
    sound->slots[slot].value = 0;
    sound->slots[slot].volume = volume;
    sound->slots[slot].unk1c = 0;
    sound->slots[slot].unk2c = value;
    sound->slots[slot].unk34 = (u32)volume << 24 | ((u32)low & 0xFFFF);
    sound->slots[slot].unk38 = placement;
    sound->slots[slot].unk06[0] = sound->unk451;
    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return sound->slots[slot].identifier;
}

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
s32 resident_sound_play_data(ResidentSound* sound, u8* buffer, s32 value, s32 volume, s32 pan, s32 low, s32 owns_buffer)
{
    if (sound->effects_disabled)
    {
        if (owns_buffer)
        {
            delete buffer;
        }

        return 1;
    }

    if (sound->state == RESIDENT_SOUND_CHANGING_REVERB)
    {
        return -1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    sound->slots[slot].buffer = buffer;
    sound->slots[slot].unk28 = 0;
    sound->slots[slot].active = 1;
    sound->slots[slot].started = 0;
    sound->slots[slot].stop_requested = 0;
    sound->slots[slot].unk03 = 1;
    sound->slots[slot].owns_buffer = owns_buffer;
    sound->slots[slot].identifier = sound->next_identifier;
    sound->slots[slot].target = 0;
    sound->slots[slot].unk30 = 0;
    sound->slots[slot].selector = 0;
    sound->slots[slot].value = 0;
    sound->slots[slot].unk2c = value;
    sound->slots[slot].unk34 = ((u32)low & 0xFFFF) | ((u32)volume << 24 | (u32)pan << 16);
    sound->slots[slot].unk38 = 0;
    sound->slots[slot].unk06[0] = 0;
    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return sound->slots[slot].identifier;
}

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
s32 resident_sound_play_voice(ResidentSound* sound, s32 resource, ResidentSoundEmitter* emitter, s32 value, s32 volume,
                              s32 low)
{
    if (sound->effects_disabled)
    {
        return 1;
    }

    if (sound->state == RESIDENT_SOUND_CHANGING_REVERB)
    {
        return -1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    sound->slots[slot].buffer = (u8*)memalign(64, resident_get_resource_size(sound->archive, resource));

    if (sound->slots[slot].buffer == 0)
    {
        return -1;
    }

    float position[4];
    func_4DA730(emitter, position);
    emitter->has_sound = 1;
    u32 placement = resident_sound_place(sound, position, 0, 0);
    sound->slots[slot].unk28 = 0;
    sound->slots[slot].active = 1;
    sound->slots[slot].started = 0;
    sound->slots[slot].stop_requested = 0;
    sound->slots[slot].unk03 = 1;
    sound->slots[slot].owns_buffer = 1;
    sound->slots[slot].identifier = sound->next_identifier;
    sound->slots[slot].target = emitter;
    sound->slots[slot].unk30 = 0;
    sound->slots[slot].selector = 0;
    sound->slots[slot].value = 0;
    sound->slots[slot].volume = volume;
    sound->slots[slot].unk1c = 0;
    sound->slots[slot].unk2c = value;
    sound->slots[slot].unk34 = (u32)volume << 24 | ((u32)low & 0xFFFF);
    sound->slots[slot].unk38 = placement;
    sound->slots[slot].unk06[0] = sound->unk451;
    resident_queue_resource_request(sound->resource_queue, resource, sound->slots[slot].buffer, SOUND_VOICE_READ_TAG,
                                    SOUND_VOICE_READ_PRIORITY, 0, 0, 0, 1);
    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return sound->slots[slot].identifier;
}

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
s32 resident_sound_play_voice_resource(ResidentSound* sound, s32 resource, s32 value, s32 volume, s32 pan, s32 low)
{
    if (sound->effects_disabled)
    {
        return 1;
    }

    if (sound->state == RESIDENT_SOUND_CHANGING_REVERB)
    {
        return -1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    sound->slots[slot].buffer = (u8*)memalign(64, resident_get_resource_size(sound->archive, resource));

    if (sound->slots[slot].buffer == 0)
    {
        return -1;
    }

    sound->slots[slot].unk28 = 0;
    sound->slots[slot].active = 1;
    sound->slots[slot].started = 0;
    sound->slots[slot].stop_requested = 0;
    sound->slots[slot].unk03 = 1;
    sound->slots[slot].owns_buffer = 1;
    sound->slots[slot].identifier = sound->next_identifier;
    sound->slots[slot].target = 0;
    sound->slots[slot].unk30 = 0;
    sound->slots[slot].selector = 0;
    sound->slots[slot].value = 0;
    sound->slots[slot].volume = volume;
    sound->slots[slot].unk1c = 0;
    sound->slots[slot].unk2c = value;
    sound->slots[slot].unk34 = ((u32)low & 0xFFFF) | ((u32)volume << 24 | (u32)pan << 16);
    sound->slots[slot].unk38 = 0;
    sound->slots[slot].unk06[0] = 0;
    resident_queue_resource_request(sound->resource_queue, resource, sound->slots[slot].buffer, SOUND_VOICE_READ_TAG,
                                    SOUND_VOICE_READ_PRIORITY, 0, 0, 0, 1);
    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return sound->slots[slot].identifier;
}

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
                  s32 low)
{
    if (sound->effects_disabled)
    {
        return 1;
    }

    if (sound->state == RESIDENT_SOUND_CHANGING_REVERB)
    {
        return -1;
    }

    if (emitter == 0)
    {
        return -1;
    }

    s32 slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    s32 i;

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    float position[4];
    func_4DA730(emitter, position);
    emitter->has_sound = 1;
    u32 placement = resident_sound_place(sound, position, 0, 0);
    ResidentRequestSlot* const request = request_slot(sound->slots, slot);
    request->buffer = 0;
    request->unk28 = 0;
    request->active = 1;
    request->started = 0;
    request->stop_requested = 0;
    request->owns_buffer = 0;
    request->unk03 = 0;
    s32* identifier = &sound->slots[slot].identifier;
    *identifier = sound->next_identifier;
    request->target = emitter;
    request->unk30 = 0;
    request->selector = selector;
    request->value = number;
    request->unk38 = placement;
    request->volume = volume;
    request->unk1c = 0;

    if (!resident_stream_play_slot(sound->stream, 0, resident_sound_on_play_reply, request, sound->unk454[selector], number, value, 0,
                       (u32)volume << 24 | ((u32)low & 0xFFFF), placement, sound->unk451))
    {
        request->active = 0;
        return 0;
    }

    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return *identifier;
}

/**
 * @brief Play a sound effect in a free slot.
 * @param sound Sound system.
 * @param number Sound number; its low 16 bits are stored.
 * @param selector Request selector.
 * @param value Value forwarded to request dispatch.
 * @param volume Volume, 0x7F for full; stored and packed into the upper byte.
 * @param pan Pan, 0x40 for centre; packed into the next byte.
 * @param low Value packed into the lower 16 bits.
 * @return Slot identifier, zero on dispatch failure, one when effects are disabled, or -1 when no slot is free.
 */
s32 resident_sound_play(ResidentSound* sound, s32 number, s32 selector, s32 value, s32 volume, s32 pan, s32 low)
{
    s32 slot;
    s32 i;

    if (sound->effects_disabled)
    {
        return 1;
    }

    if (sound->state == RESIDENT_SOUND_CHANGING_REVERB)
    {
        return -1;
    }

    slot = find_available_request_slot(sound);

    if (slot == -1)
    {
        return -1;
    }

    do
    {
        for (i = 0; i < 60; i++)
        {
            if (sound->slots[i].active && sound->slots[i].identifier == sound->next_identifier)
            {
                sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
                break;
            }
        }
    } while (i != 60);

    ResidentRequestSlot* const request = request_slot(sound->slots, slot);
    s32* identifier;
    request->buffer = 0;
    request->unk28 = 0;
    request->active = 1;
    request->started = 0;
    request->stop_requested = 0;
    request->owns_buffer = 0;
    request->unk03 = 0;
    identifier = &sound->slots[slot].identifier;
    *identifier = sound->next_identifier;
    request->target = 0;
    request->unk30 = 0;
    request->selector = selector;
    request->value = number;
    request->volume = volume;
    request->unk1c = 0;

    if (!resident_stream_play_slot_packed(sound->stream, 0, resident_sound_on_play_reply, request, sound->unk454[selector], number, value, 0,
                       ((u32)low & 0xFFFF) | (((u32)volume << 24) | ((u32)pan << 16))))
    {
        request->active = 0;
        return 0;
    }

    sound->next_identifier = (sound->next_identifier + 1) & 0x7FFFFFFF;
    return *identifier;
}

/**
 * @brief Report whether music is playing.
 * @param sound Sound system.
 * @param key Music to check for, or -1 for any.
 * @return Nonzero while that music plays, or always when music is disabled.
 */
s32 resident_sound_is_music_playing(ResidentSound* sound, s32 key)
{
    if (sound->music_disabled)
    {
        return 1;
    }

    if (sound->music_count == 0)
    {
        return 0;
    }

    resident_sound_update(sound, 0);

    if (key == -1)
    {
        return 1;
    }

    for (s32 i = 0; i < sound->music_count; i++)
    {
        if (sound->music_keys[i] == key)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Queue streamed music from a music file already in memory.
 * @param sound Sound system.
 * @param music Music file, non-null.
 * @param stop_others Nonzero to stop the queued music first.
 * @param value Stored for the music; its use is unknown.
 * @return One when the music was queued or music is disabled, otherwise zero.
 */
s32 resident_sound_load_bank(ResidentSound* sound, const void* music, s32 stop_others, s32 value)
{
    if (sound->music_disabled)
    {
        return 1;
    }

    if (music == 0)
    {
        return 0;
    }

    if (stop_others)
    {
        while (sound->music_count != 0)
        {
            sound_remove_music_track(sound, 0, 0);
        }
    }

    if (sound->state != RESIDENT_SOUND_IDLE)
    {
        return 0;
    }

    if (sound->unk38 >= 0)
    {
        sound_remove_music_track(sound, sound->unk38, 0);
    }
    else if (resident_stream_query(sound->stream, 0, 0, 0, 1))
    {
        resident_stream_stop(sound->stream, 0, resident_sound_ignore_reply, 0, sound->unk338, 0, 0);
    }

    if (sound->music_count >= 3)
    {
        return 0;
    }

    sound->unk40 = SOUND_RESOURCE_MUSIC_KEY;
    sound->state = 8;
    sound->unk368 = music;
    sound->unk38 = sound->music_count;
    sound->music_keys[sound->music_count++] = SOUND_RESOURCE_MUSIC_KEY;
    sound->unk3c = value;
    return 1;
}

/**
 * @brief Queue music.
 * @param sound Sound system.
 * @param music Music number, from one.
 * @param stop_others Nonzero to stop the queued music first.
 * @param value Stored for the music; its use is unknown.
 * @param second Stored for streamed music; nonzero also sets a flag.
 * @return One when the music was queued or music is disabled, otherwise zero.
 */
s32 resident_sound_play_music(ResidentSound* sound, s32 music, s32 stop_others, s32 value, s32 second)
{
    if (sound->music_disabled)
    {
        return 1;
    }

    if (music == 0)
    {
        return 0;
    }

    if (sound->unk350)
    {
        return 0;
    }

    if (sound->music_entry_count < music)
    {
        return 0;
    }

    if (sound->music_count != sound->unk34)
    {
        resident_sound_update(sound, 0);
        return 0;
    }

    const ResidentMusicEntry* entry = &sound->music_entries[music - 1];

    if (stop_others)
    {
        while (sound->music_count != 0)
        {
            sound_remove_music_track(sound, 0, 0);
        }
    }

    if (!entry->in_memory)
    {
        if (sound->state != RESIDENT_SOUND_IDLE)
        {
            return 0;
        }

        if (sound->unk38 >= 0)
        {
            sound_remove_music_track(sound, sound->unk38, 0);
        }
        else if (resident_stream_query(sound->stream, 0, 0, 0, 1))
        {
            resident_stream_stop(sound->stream, 0, resident_sound_ignore_reply, 0, sound->unk338, 0, 0);
        }

        if (sound->music_count >= 3)
        {
            return 0;
        }

        sound->unk40 = music;
        sound->state = 3;
        sound->unk38 = sound->music_count;
        sound->unk4d4 = second;

        if (second)
        {
            sound->unk452 = 1;
        }
    }
    else
    {
        if (sound->state != RESIDENT_SOUND_IDLE)
        {
            return 0;
        }

        if (sound->music_count >= 3)
        {
            return 0;
        }

        delete sound->unk400;
        sound->unk404 = resident_get_resource_size(sound->archive, entry->resource);
        sound->unk400 = (u8*)memalign(0x40, sound->unk404);

        if (sound->unk400 == 0)
        {
            return 0;
        }

        resident_queue_resource_request(sound->resource_queue, entry->resource, sound->unk400, SOUND_MUSIC_READ_TAG,
                                        SOUND_VOICE_READ_PRIORITY, 0, 0, 0, 1);
        sound->state = 2;
    }

    sound->music_keys[sound->music_count++] = music;
    sound->unk3c = value;
    sound->unk3bc = 0;
    sound->unk356 = 0;
    return 1;
}

/**
 * @brief Set the table of music the sound system plays.
 * @param sound Sound system.
 * @param count Number of entries.
 * @param entries Music entries, by music number minus one.
 */
void resident_sound_set_music_table(ResidentSound* sound, s32 count, const ResidentMusicEntry* entries)
{
    sound->music_entry_count = count;
    sound->music_entries = entries;
}

/**
 * @brief Start the sound system and its stream.
 * @param sound Sound system.
 */
void resident_sound_start(ResidentSound* sound)
{
    sound->stream = resident_system_get_sound_stream(resident_get_system());
    sound->archive = resident_get_archive(resident_get_system());
    sound->resource_queue = resident_system_get_resource_queue(resident_get_system());
    s32 request = resident_stream_start(sound->stream, 0, 0, 0, 0x18000, 0x3000, 0x1000, 3, 1);

    while (resident_sif_is_request_pending(&g_sif, request))
    {
    }

    resident_stream_setup_buffers(sound->stream);
    resident_stream_set_output_mode(sound->stream, 0, 0, 0, sound->output_mode);
    resident_stream_set_volume(sound->stream, 0, 0, 0, sound->volume);
    sound->unk350 = 0;
    sound->unk452 = 0;
}

/**
 * @brief Sound interrupt handler: wake the scheduler (when unk351 is set) and every thread waiting on the sound
 * interrupt, then count the renderer's unk40C4 up to two, after which func_4D44D0 is tried and the stream told when it
 * fails.
 * @param cause Interrupt cause.
 * @return Zero.
 */
s32 resident_sound_interrupt_handler(s32 cause)
{
    if (g_resident_sound->unk351)
    {
        resident_thread_wakeup(&g_scheduler);
    }

    s32 count = g_resident_sound->unk143c;

    for (s32 i = 0; i < count; i++)
    {
        resident_thread_wakeup(g_resident_sound->unk13bc[i]);
    }

    g_resident_sound->unk143c = 0;

    ResidentSound* sound = g_resident_sound;

    if (sound && sound && sound->unk0c)
    {
        if (sound->unk0c->unk40c4 > 1)
        {
            if (!func_4D44D0(sound->unk0c, 1))
            {
                resident_stream_wake_thread(sound->stream, 1);
            }
        }
        else
        {
            sound->unk0c->unk40c4++;
        }
    }

    ee_exit_handler();
    return 0;
}

/** @brief Remove the sound interrupt handler and free the sound buffers. */
ResidentSound::~ResidentSound()
{
    DisableIntc(INTC_VBLANK_END);
    RemoveIntcHandler(INTC_VBLANK_END, interrupt_handler);
    delete[] unk400;
    delete[] (u8*)voice_table;
}

/** @brief Start silent at half volume, with no music or voices, and install the sound interrupt handler. */
ResidentSound::ResidentSound()
{
    g_resident_sound = this;
    music_entries = 0;
    music_entry_count = 0;
    stream = 0;
    unk114 = 0;
    music_count = 0;
    unk34 = 0;
    unk38 = -1;
    unk352 = 0;
    state = 0;
    unk111 = 0;
    voice_table = (ResidentVoiceTable*)new (0) u8[0x800];
    voice_file_key = 0;
    unk33c = 0;
    volume = 0x4000;
    scaled_volume = volume;
    reverb_preset = 0xFF;
    unk356 = 0;
    unk143c = 0;
    unk334 = 0;
    unk348 = 0;
    unk4d4 = 0;
    unk452 = 0;
    unk34c = 1.0f;
    unk0c = 0;

    for (s32 i = 0; i < 8; i++)
    {
        voice_buffers[i] = 0;
        voice_indices[i] = 0;
    }

    unk13ac[0] = 1.0f;
    unk13ac[1] = 126.0f;
    unk13ac[2] = 100.0f;
    unk13ac[3] = 2500.0f;
    unk400 = 0;
    cursor = 0;
    next_identifier = 0;
    listener = 0;
    unk351 = 0;
    memset_guess(slots, 0, sizeof(slots));

    ResidentSpeakerAngles angles = g_default_speaker_angles;
    speaker_angles[0] = angles.angles[0];
    speaker_angles[1] = angles.angles[1];
    speaker_angles[2] = angles.angles[2];
    speaker_angles[3] = angles.angles[3];
    output_mode = 0;
    interrupt_handler = AddIntcHandler(INTC_VBLANK_END, resident_sound_interrupt_handler, 0);
    EnableIntc(INTC_VBLANK_END);
    FlushCache(0);
    music_disabled = 0;
    effects_disabled = 0;
}

void resident_sound_do_nothing(void* object)
{
}
}
