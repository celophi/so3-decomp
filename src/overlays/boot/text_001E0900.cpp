// TODO: BootNewGameSettings::update_page_images only matches with constant pull-out off. Several other boot files
// stop matching with it, so I think this file was built with it off.
#pragma opt_pulloutconstants off

#include "include_asm.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/init.h"
#include "overlays/boot/resident.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_00101550.h"
#include "main/resident_0011EE70.h"
#include "main/resident_00121860.h"
#include "sdk/main/libc_0013C6D0.h"
#include "sdk/main/libc_0013CA60.h"
#include "vu0.h"
#include "ee.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_004AB8B0.h"

/** Timebase used to convert frame ticks to seconds. */
#define BOOT_FRAME_TICKS_PER_SECOND 60.0f

/** Display width in pixels. */
#define BOOT_SCREEN_WIDTH 640

/** Height of one interlaced field, half the 448-line frame. */
#define BOOT_FIELD_HEIGHT 224

/** Reverb the settings screen plays under (studio A). */
#define BOOT_SETTINGS_REVERB_PRESET 2

extern "C" {
extern BootFloorQuery* g_floor_query;
extern LibScreenText* g_screen_text;
extern BootResidentDisplay* g_display_callbacks;
void resident_system_set_progressive(ResidentSystem* system, u8 progressive);
extern LibCameraContext* D_001B6520;
extern u8 D_001B6420;
extern BootTrackPool<BootPooledFloatTrack>* g_float_track_pool;
extern BootTrackPool<BootPooledVectorTrack>* g_vector_track_pool;
extern BootTrackPool<BootClass177EE0>* D_001B666C;
extern BootTrackPool<BootPooledFloatCurveTrack>* g_float_curve_track_pool;
extern BootTrackPool<BootPooledVectorCurveTrack>* g_vector_curve_track_pool;
extern BootTrackPool<BootPooledFloatQuaternionTrack>* g_float_quaternion_track_pool;
extern BootTrackPool<BootPooledQuaternionCurveTrack>* g_quaternion_curve_track_pool;
extern BootTrackPool<BootPooledQuaternionTrack>* g_quaternion_track_pool;
void resident_system_create_status(ResidentSystem* system);
extern struct LibPacketQueue* g_packet_queue;
extern const struct BootLabelOffsets g_settings_label_offsets;
extern const struct BootCaption g_opening_captions[];
void lib_compute_sine_cosine_pair_degree9(LibVector4* output, float angle);
extern const char g_root_node_name[];
extern const char g_look_node_name[];
extern const char g_right_speaker_name[];
extern const char g_left_speaker_name[];
extern const char g_rear_left_speaker_name[];
extern const char g_rear_right_speaker_name[];
extern const char g_center_speaker_name[];
extern u8 g_settings_option_counts[5];
extern u8 g_difficulty_option_count;
extern const s16 g_voice_lines[];
extern const char g_empty_name[];
extern const char g_bone_root_name[];
extern const char g_camera_node_name[];
extern const char g_face_model_name[];
s32 resident_sound_stop(ResidentSound* sound, s32 handle, s32 flag);
s32 resident_sound_is_active(ResidentSound* sound, s32 handle);
u32 resident_sound_get_voice_level(ResidentSound* sound, s32 handle, float time);
void lib_animation_bind_state(LibAnimation* animation, LibAnimationTarget* target, const char* name);
}

/** Horizontal offsets of the six option labels. */
struct BootLabelOffsets
{
    s32 values[6];
};


static inline void copy_transfer_name(BootBattleTrophyCard* trophy_card, const char* base, const char* suffix);
static inline s32 prepare_transfer_request(BootBattleTrophyCard* trophy_card);

/**
 * @brief Clear the stored filename and copy the optional base and suffix.
 * @param trophy_card State containing the filename buffer.
 * @param base Base filename; a null pointer leaves the buffer unchanged.
 * @param suffix Optional suffix to append after the base.
 */
static inline void copy_transfer_name(BootBattleTrophyCard* trophy_card, const char* base, const char* suffix)
{
    s32 index;

    if (base != 0)
    {
        for (index = 0; index < BOOT_TRANSFER_NAME_CAPACITY; index++)
        {
            trophy_card->filename[index] = 0;
        }

        strcpy_guess(trophy_card->filename, base);

        if (suffix != 0)
        {
            strcat(trophy_card->filename, suffix);
        }
    }
}

/**
 * @brief Clear an allocated buffer and populate its transfer request records.
 * @param trophy_card State containing the buffer and filename storage.
 * @return 1 when the records are prepared, or 0 when no buffer is allocated.
 */
static inline s32 prepare_transfer_request(BootBattleTrophyCard* trophy_card)
{
    u8 ready;

    if (trophy_card->transfer_buffer == 0)
    {
        ready = 0;
    }
    else
    {
        memset_guess(trophy_card->transfer_buffer, 0, BOOT_TRANSFER_BUFFER_SIZE);

        if (strlen(g_card_product_code) + 1 <= BOOT_TRANSFER_NAME_CAPACITY)
        {
            copy_transfer_name(trophy_card, g_card_product_code, g_trophy_file_suffix);
        }

        trophy_card->file_buffer.name = trophy_card->filename;
        trophy_card->file_buffer.data = trophy_card->transfer_buffer;
        trophy_card->file_buffer.size = BOOT_TRANSFER_BUFFER_SIZE;
        trophy_card->file_buffer.unk0C = 0;
        trophy_card->file_request.directory = trophy_card->filename;
        trophy_card->file_request.file_count = 1;
        trophy_card->file_request.unk08 = 0;
        trophy_card->file_request.files = &trophy_card->file_buffer;
        ready = 1;
    }

    return ready;
}

/**
 * @brief Read the saved difficulty when the protected settings pass their checksum.
 * @param settings System settings.
 * @return Difficulty, or Earth when the checksum fails.
 */
static inline u8 settings_difficulty(LibSystemSettings* settings)
{
    if (settings->checksum != lib_compute_checksum(settings->key, &settings->unk26, (u8*)&settings->checksum - &settings->unk26))
    {
        return LIB_DIFFICULTY_EARTH;
    }

    return settings->difficulty;
}

/**
 * @brief Save a difficulty and reseal the protected settings, unless their checksum is already broken.
 * @param settings System settings.
 * @param value Difficulty to save.
 */
static inline void settings_set_difficulty(LibSystemSettings* settings, u8 value)
{
    s32 length = (u8*)&settings->checksum - &settings->unk26;

    if (settings->checksum == lib_compute_checksum(settings->key, &settings->unk26, length))
    {
        settings->difficulty = value;
        settings->key = resident_next_random_word();
        settings->checksum = lib_compute_checksum(settings->key, &settings->unk26, length);
    }
}

/**
 * @brief Read a byte of the extra protected block when the block passes its checksum.
 * @param settings System settings.
 * @param data Start of the extra protected block.
 * @param value Byte to read.
 * @return Stored byte, or zero when the checksum fails.
 */
static inline u8 settings_extra_byte(LibSystemSettings* settings, u8* data, u8* value)
{
    if (settings->extra_checksum != lib_compute_checksum(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }

    return *value;
}

/**
 * @brief Check whether Universe difficulty is unlocked, trusting the flag only when its checksum passes.
 * @param settings System settings.
 * @return The unlock flag, or zero when the checksum fails.
 */
static inline u8 settings_universe_unlocked(LibSystemSettings* settings)
{
    u8* data = &settings->unk1A0;

    if (settings->extra_checksum != lib_compute_checksum(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }

    return settings->universe_unlocked;
}

/**
 * @brief Check whether 4D difficulty is unlocked, trusting the flag only when its checksum passes.
 * @param settings System settings.
 * @return The unlock flag, or zero when the checksum fails.
 */
static inline u8 settings_fourth_dimension_unlocked(LibSystemSettings* settings)
{
    u8* data = &settings->unk1A0;

    if (settings->extra_checksum != lib_compute_checksum(settings->extra_key, data, (u8*)&settings->extra_checksum - data))
    {
        return 0;
    }

    return settings->fourth_dimension_unlocked;
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Two.
 */
s32 BootBattleTrophyCard::get_default_list_kind()
{
    return 2;
}

/**
 * @brief Report which card slots hold a ready card.
 * @return Bit 0 for slot 1 and bit 1 for slot 2; zero while the card object is busy.
 */
u16 BootBattleTrophyCard::get_ready_slots()
{
    LibMemoryCard* owner = card;
    LibMemoryCardSlot* modes;
    u16 flags;

    if (owner->ready == 0)
    {
        return 0;
    }

    modes = owner->slots;
    flags = 0;

    if (modes[0].card_state == 2)
    {
        flags |= LIB_CARD_SLOT_1;
    }

    if (modes[1].card_state == 2)
    {
        flags |= LIB_CARD_SLOT_2;
    }

    return flags;
}

/** @brief Apply transferred flags and header values, copy the payload, and release its buffer. */
void BootBattleTrophyCard::finish_transfer()
{
    u8 saved_bits[BOOT_TRANSFER_FLAG_BYTES];
    s32 index;
    u8* saved;
    LibTrophyFlags* bits;

    if (transfer_buffer != 0)
    {
        saved = (u8*)transfer_buffer + BOOT_TROPHY_FILE_FLAGS_OFFSET;
        bits = &settings->trophy_flags;
        memset_guess(saved_bits, 0, BOOT_TRANSFER_FLAG_BYTES);
        memcpy_guess(saved_bits, saved, BOOT_TRANSFER_FLAG_BYTES);

        for (index = 0; index < BOOT_TRANSFER_FLAG_COUNT; index++)
        {
            set_resource_bit(bits, index, saved_bits[index / 8] & (1 << (index % 8)));
        }

        bits->trophy_key = *(u32*)transfer_buffer;
        memcpy_guess(&bits->checksum_seed, saved + BOOT_TRANSFER_FLAG_BYTES, 8);
        memcpy_guess(transfer_destination, (u8*)transfer_buffer + BOOT_TROPHY_FILE_RECORDS_OFFSET, BOOT_TROPHY_RECORD_BYTES);

        if (transfer_buffer != 0)
        {
            delete[] transfer_buffer;
            transfer_buffer = 0;
        }
    }
}

/**
 * @brief Return the stored signed request result.
 * @return The stored value.
 */
s32 BootBattleTrophyCard::get_transfer_result()
{
    return transfer_result;
}

/**
 * @brief Return the transfer state.
 * @return 1 once the transfer has finished, -1 while it runs or after a reset.
 */
s16 BootBattleTrophyCard::get_transfer_state()
{
    return transfer_state;
}

/**
 * @brief Advance the stored two-phase request and update its completion state.
 * @return Narrowed request status, or -1 when the phase is unsupported.
 */
s16 BootBattleTrophyCard::advance_transfer()
{
    s16 result = -1;

    switch (transfer_phase)
    {
    case BOOT_TROPHY_TRANSFER_OPEN:
        transfer_open = 1;
        result = lib_memory_card_start_transfer(card, transfer_slot, &file_request);

        if (result == -1)
        {
            transfer_pending = 0;
            transfer_state = 1;
            card_step = BOOT_TROPHY_CARD_IDLE;
            transfer_slot = -1;
            transfer_phase = BOOT_TROPHY_TRANSFER_INACTIVE;
        }
        else if (result == 0)
        {
            transfer_phase++;
        }

        break;
    case BOOT_TROPHY_TRANSFER_POLL:
        result = lib_memory_card_get_result(card, transfer_slot, &transfer_result);

        if (result == 0)
        {
            break;
        }

        if (result == 1)
        {
            transfer_pending = 0;

            if (transfer_result >= 0)
            {
                finish_transfer();
                transfer_state = 1;
                card_step = BOOT_TROPHY_CARD_IDLE;
                transfer_slot = -1;
                transfer_phase = BOOT_TROPHY_TRANSFER_INACTIVE;
            }
            else
            {
                transfer_state = 1;
                transfer_slot = -1;
                transfer_phase = BOOT_TROPHY_TRANSFER_INACTIVE;
                card_step = BOOT_TROPHY_CARD_INSPECT_SLOT;
                transfer_pending = 0;

                if (transfer_open == 1)
                {
                    transfer_open = 0;
                }
            }
        }

        break;
    }

    return result;
}

/**
 * @brief Initialize the buffer and request records for a selected transfer mode.
 * @param mode Transfer mode 0 or 1.
 * @param destination Nonnull destination for the transfer.
 * @return 1 when prepared, or 0 for invalid arguments or allocation failure.
 */
s32 BootBattleTrophyCard::start_transfer(u16 mode, void* destination)
{
    u8 ready;

    if (mode != 0 && mode != 1)
    {
        return 0;
    }

    if (destination == 0)
    {
        return 0;
    }

    transfer_destination = destination;
    transfer_slot = mode;
    transfer_result = -1;
    transfer_phase = BOOT_TROPHY_TRANSFER_OPEN;
    transfer_pending = 1;
    slot = transfer_slot;
    card_poll_paused = 0;

    if (transfer_buffer == 0)
    {
        transfer_buffer = new (0) u8[BOOT_TRANSFER_BUFFER_SIZE];
    }

    ready = prepare_transfer_request(this);

    if (!ready)
    {
        return 0;
    }

    transfer_open = 0;
    return 1;
}

/**
 * @brief Store mode 1 or 2 and reset the state for selector 0.
 * @param mode Mode to store; values other than 1 or 2 have no effect.
 */
void BootBattleTrophyCard::set_mode(u8 mode)
{
    if (mode == 1 || mode == 2)
    {
        card_mode = mode;
        reset_slot(0);
    }
}

/**
 * @brief Drop a pending transfer and go back to waiting for the card.
 * @param trophy_card Memory card trophy_card.
 */
static inline void cancel_transfer(BootBattleTrophyCard* trophy_card)
{
    trophy_card->transfer_state = 1;
    trophy_card->transfer_result = -12;
    trophy_card->transfer_slot = -1;
    trophy_card->transfer_phase = BOOT_TROPHY_TRANSFER_INACTIVE;
    trophy_card->card_step = BOOT_TROPHY_CARD_INSPECT_SLOT;
    trophy_card->transfer_open = 0;
    trophy_card->transfer_pending = 0;
}

/** @brief Advance the memory card state for the current mode. */
void BootBattleTrophyCard::update()
{
    s32 progress;
    s32 status;
    u8 done;

    if (card != 0 && card->ready != 0)
    {
        status = last_card_status;

        if (card_poll_paused == 0)
        {
            status = card->slots[slot].card_state;

            if (status != last_card_status)
            {
                last_card_status = status;
                card_step = BOOT_TROPHY_CARD_INSPECT_SLOT;
                transfer_state = -1;

                if (transfer_open != 0)
                {
                    cancel_transfer(this);
                }

                return;
            }
        }

        progress = 0;
        done = 0;

        for (;;)
        {
            if (done)
            {
                break;
            }

            switch (card_step)
            {
            case BOOT_TROPHY_CARD_IDLE:
                done = 1;
                break;
            case BOOT_TROPHY_CARD_INSPECT_SLOT:
                if (status != 2)
                {
                    if (transfer_pending == 0)
                    {
                        handle_card_event(1, 15, 1);
                    }
                    else
                    {
                        cancel_transfer(this);
                    }

                    return;
                }

                card_formatted = card->slots[slot].formatted;

                if (card_formatted == 0)
                {
                    if (card_mode == 1)
                    {
                        handle_card_event(1, 16, 1);
                    }
                    else
                    {
                        handle_card_event(1, 16, card_mode);
                    }

                    return;
                }

                free_space = card->slots[slot].free_space;

                if (card_formatted == 0 && card_mode == 1)
                {
                    free_space = BOOT_CARD_MAX_EXPECTED_SPACE;
                }

                slot_free_space[slot] = free_space;
                card_step = BOOT_TROPHY_CARD_PROBE_SAVE;

                if (free_space < BOOT_CARD_SAVE_SPACE_MINIMUM)
                {
                    low_space = 1;
                }

                break;
            case BOOT_TROPHY_CARD_PROBE_SAVE:
                if (strlen(g_card_product_code) + 1 <= BOOT_TRANSFER_NAME_CAPACITY)
                {
                    copy_transfer_name(this, g_card_product_code, g_any_file_suffix);
                }

                status = lib_memory_card_probe_file(card, slot, filename, 0, 1, save_file_probe_buffer);

                if (status == -1)
                {
                    done = 1;
                }
                else
                {
                    card_step = BOOT_TROPHY_CARD_WAIT_SAVE_PROBE;
                }

                break;
            case BOOT_TROPHY_CARD_WAIT_SAVE_PROBE:
                status = lib_memory_card_get_result(card, slot, &progress);

                if (status != 0 && status == 1)
                {
                    if (progress == 0)
                    {
                        if (low_space != 0)
                        {
                            handle_card_event(1, 2, 1);
                        }
                        else
                        {
                            handle_card_event(1, 16, 1);
                        }
                    }
                    else if (progress > 0)
                    {
                        handle_card_event(1, 17, 1);
                    }
                    else
                    {
                        handle_card_event(1, 0, 1);
                    }
                }

                if (card_mode == 1)
                {
                    if (status == 1)
                    {
                        card_step = BOOT_TROPHY_CARD_PROBE_TROPHIES;
                    }
                    else
                    {
                        done = 1;
                    }
                }
                else if (status == 1)
                {
                    card_step = BOOT_TROPHY_CARD_PROBE_TROPHIES;
                }
                else
                {
                    done = 1;
                }

                break;
            case BOOT_TROPHY_CARD_PROBE_TROPHIES:
                if (strlen(g_card_product_code) + 1 <= BOOT_TRANSFER_NAME_CAPACITY)
                {
                    copy_transfer_name(this, g_card_product_code, g_trophy_file_suffix);
                }

                status = lib_memory_card_probe_file(card, slot, filename, 0, 1, trophy_file_probe_buffer);

                if (status == -1)
                {
                    done = 1;
                }
                else
                {
                    card_step = BOOT_TROPHY_CARD_WAIT_TROPHY_PROBE;
                }

                break;
            case BOOT_TROPHY_CARD_WAIT_TROPHY_PROBE:
                status = lib_memory_card_get_result(card, slot, &progress);

                if (status != 0 && status == 1)
                {
                    if (progress == 0)
                    {
                        if (card_mode == 1)
                        {
                            handle_card_event(1, BOOT_TROPHY_FILE_MISSING, 1);
                        }
                        else
                        {
                            handle_card_event(1, BOOT_TROPHY_FILE_MISSING, 2);
                        }
                    }
                    else if (progress > 0)
                    {
                        if (card_mode == 1)
                        {
                            handle_card_event(1, BOOT_TROPHY_FILE_PRESENT, 1);
                        }
                        else if (transfer_pending != 0)
                        {
                            card_step = BOOT_TROPHY_CARD_TRANSFER;
                            transfer_state = -1;
                        }
                        else
                        {
                            handle_card_event(1, BOOT_TROPHY_FILE_PRESENT, 2);
                        }
                    }
                    else if (card_mode == 1)
                    {
                        handle_card_event(1, 15, 1);
                    }
                    else
                    {
                        handle_card_event(1, 0, 1);
                        reset_slot(0);
                    }
                }

                done = 1;
                break;
            case BOOT_TROPHY_CARD_TRANSFER:
                advance_transfer();
                done = 1;
                break;
            default:
                done = 1;
                break;
            }
        }
    }
}

/**
 * @brief Return a mode's stored byte, or zero for an unsupported mode.
 * @param trophy_card State holding the mode values.
 * @param mode Mode 0 or 1 to query.
 * @return The stored byte, or zero when the mode is unsupported.
 */
static inline u8 state_mode_value(BootBattleTrophyCard* trophy_card, u16 mode)
{
    if (mode != 0 && mode != 1)
    {
        return 0;
    }

    return trophy_card->mode_status[mode];
}

/**
 * @brief Query a slot's state byte, resetting slot 0 when its reset flag is set.
 * @param mode Slot 0 or 1 to query; other values return zero without a reset.
 * @param kind Select guarded values with 1, or the direct mode byte otherwise.
 * @return The selected byte before any reset.
 */
u16 BootBattleTrophyCard::get_slot_state(u16 mode, u16 kind)
{
    u16 value = 0;

    if (mode != 0 && mode != 1)
    {
        return 0;
    }

    if (kind == 1)
    {
        if (mode == 0)
        {
            if (!slot1_status_valid)
            {
                value = 0;
            }
            else
            {
                value = slot1_status;
            }
        }
        else if (mode == 1)
        {
            if (!slot2_status_valid)
            {
                value = 0;
            }
            else
            {
                value = slot2_status;
            }
        }
    }
    else
    {
        value = state_mode_value(this, mode);
    }

    if (pending_slot_reset)
    {
        reset_slot(0);
    }

    return value;
}

/**
 * @brief Apply an event to the selected mode and update its reset and completion flags.
 * @param enabled Process the event when this byte equals 1.
 * @param event Event code or direct byte status to store.
 * @param kind Classify the event with 1, or store its byte status with 2.
 */
void BootBattleTrophyCard::handle_card_event(u8 enabled, u16 event, u16 kind)
{
    u8 ready;

    if (enabled == 1)
    {
        if (slot == 1)
        {
            if (kind == 1)
            {
                classify_card_event(event, &slot2_status);

                if (card_mode != 1)
                {
                    slot2_status_valid = 1;
                }

                if (card_mode == 1)
                {
                    ready = 0;

                    switch (event)
                    {
                    case 16:
                        if (card_formatted == 0)
                        {
                            slot2_status_valid = 1;
                            ready = 1;
                        }

                        break;
                    case 15:
                    case BOOT_TROPHY_FILE_PRESENT:
                    case BOOT_TROPHY_FILE_MISSING:
                        slot2_status_valid = 1;
                        ready = 1;
                        break;
                    }

                    if (ready)
                    {
                        pending_slot_reset = 1;
                    }
                }
                else if (card_mode == 2)
                {
                    switch (event)
                    {
                    case 15:
                        mode_status[1] = 15;
                        mode_status_valid[1] = 1;
                        pending_slot_reset = 1;
                        break;
                    }
                }
            }
            else if (kind == 2)
            {
                mode_status[1] = event;
                mode_status_valid[1] = 1;
                pending_slot_reset = 1;
            }
        }

        if (slot == 0)
        {
            if (kind == 1)
            {
                classify_card_event(event, &slot1_status);

                if (card_mode == 1)
                {
                    ready = 0;

                    switch (event)
                    {
                    case 16:
                        if (card_formatted == 0)
                        {
                            slot1_status_valid = 1;
                            ready = 1;
                        }

                        break;
                    case 15:
                    case BOOT_TROPHY_FILE_PRESENT:
                    case BOOT_TROPHY_FILE_MISSING:
                        slot1_status_valid = 1;
                        ready = 1;
                        break;
                    }

                    if (ready == 1)
                    {
                        reset_slot(1);
                    }
                }
                else
                {
                    switch (event)
                    {
                    case 15:
                        if (card_mode == 2)
                        {
                            mode_status[0] = 15;
                            mode_status_valid[0] = 1;
                            reset_slot(1);
                        }

                        /* fall through */
                    case 2:
                    case 16:
                    case 17:
                        slot1_status_valid = 1;
                        break;
                    }

                    if (card_mode == 1)
                    {
                        reset_slot(1);
                    }
                }
            }
            else if (kind == 2)
            {
                mode_status[0] = event;
                mode_status_valid[0] = 1;
                reset_slot(1);
            }
        }
    }

    if (pending_slot_reset == 0)
    {
        card_poll_paused = 0;
    }
    else
    {
        card_poll_paused = enabled;
    }
}

/**
 * @brief Select an event's byte status and update the current mode's stored status.
 * @param event Event code to classify.
 * @param result Byte receiving the selected status, initially cleared to zero.
 */
void BootBattleTrophyCard::classify_card_event(u16 event, u8* result)
{
    s32 value;

    *result = 0;
    if (card_mode == 1)
    {
        value = slot_free_space[slot];

        switch (event)
        {
        case 15:
            *result = BOOT_CARD_STATUS_UNAVAILABLE;
            break;
        case 2:
            save_probe_status[slot] = BOOT_CARD_STATUS_NO_SPACE;
            break;
        case 16:
            if (card_formatted == 0)
            {
                *result = 16;
            }
            else
            {
                save_probe_status[slot] = 16;
            }

            break;
        case 17:
            save_probe_status[slot] = BOOT_CARD_STATUS_SAVE_PRESENT;
            break;
        case BOOT_TROPHY_FILE_MISSING:
            if (save_probe_status[slot] == BOOT_CARD_STATUS_SAVE_PRESENT)
            {
                if (value < 0 || value > BOOT_CARD_MAX_EXPECTED_SPACE)
                {
                    *result = BOOT_CARD_STATUS_UNAVAILABLE;
                }

                *result = BOOT_CARD_STATUS_SAVE_PRESENT;
                if (0 <= value && value < BOOT_CARD_TROPHY_SPACE_MINIMUM)
                {
                    *result = BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE;
                }
            }
            else
            {
                if (value < 0 || value > BOOT_CARD_MAX_EXPECTED_SPACE)
                {
                    *result = BOOT_CARD_STATUS_UNAVAILABLE;
                }

                *result = save_probe_status[slot];
                if (0 <= value && value < BOOT_CARD_BOTH_SPACE_MINIMUM)
                {
                    *result = BOOT_CARD_STATUS_EITHER_FILE_ONLY;
                }

                if (0 <= value && value < BOOT_CARD_SAVE_SPACE_MINIMUM)
                {
                    *result = BOOT_CARD_STATUS_NO_SPACE;
                }
                else if (value >= BOOT_CARD_SAVE_SPACE_MINIMUM && value < BOOT_CARD_TROPHY_SPACE_MINIMUM)
                {
                    *result = BOOT_CARD_STATUS_SAVE_SPACE_ONLY;
                }
                else if (value >= BOOT_CARD_TROPHY_SPACE_MINIMUM && value < BOOT_CARD_BOTH_SPACE_MINIMUM)
                {
                    *result = BOOT_CARD_STATUS_EITHER_FILE_ONLY;
                }
            }

            break;
        case BOOT_TROPHY_FILE_PRESENT:
            if (save_probe_status[slot] == BOOT_CARD_STATUS_SAVE_PRESENT)
            {
                *result = BOOT_CARD_STATUS_SAVE_PRESENT;
            }
            else
            {
                if (value < 0 || value > BOOT_CARD_MAX_EXPECTED_SPACE)
                {
                    *result = BOOT_CARD_STATUS_UNAVAILABLE;
                }

                *result = save_probe_status[slot];
                if (0 <= value && value < BOOT_CARD_SAVE_SPACE_MINIMUM)
                {
                    *result = BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE;
                }
            }

            break;
        }
    }
    else
    {
        switch (event)
        {
        case 15:
            *result = BOOT_CARD_STATUS_UNAVAILABLE;
            break;
        case 2:
            *result = 2;
            break;
        case 16:
            *result = 16;
            break;
        case 17:
            *result = BOOT_CARD_STATUS_SAVE_PRESENT;
            break;
        }
    }
}

/**
 * @brief Select a slot and reset its fields along with the shared state.
 * @param mode Slot 0 or 1 to select; other values reset only the shared state.
 */
void BootBattleTrophyCard::reset_slot(s16 mode)
{
    s32 selected = mode;
    slot = mode;
    last_card_status = -1;
    card_poll_paused = 0;
    card_step = BOOT_TROPHY_CARD_IDLE;
    low_space = 0;

    if (selected == 0)
    {
        slot1_status_valid = 0;
        slot1_status = 0;
        pending_slot_reset = 0;
        card_poll_paused = 0;
        mode_status[0] = 0;
        mode_status_valid[0] = 0;
    }

    if (selected == 1)
    {
        slot2_status_valid = 0;
        slot2_status = 0;
        mode_status[1] = 0;
        mode_status_valid[1] = 0;
    }

    if (selected == 0 || selected == 1)
    {
        slot_free_space[selected] = -1;
        save_probe_status[selected] = -1;
    }
}

/**
 * @brief Create the memory card object for both slots and prepare the transfer buffer.
 * @return 1 when initialized, or 0 when the card object, settings or buffer is unavailable.
 */
s32 BootBattleTrophyCard::initialize()
{
    LibMemoryCard* owner;
    u8 ready;

    owner = new (0) LibMemoryCard;
    card = owner;

    if (card == 0)
    {
        return 0;
    }

    lib_memory_card_init(card, g_update_list);
    lib_memory_card_open_slot(card, 0, 0, 0);
    lib_memory_card_open_slot(card, 1, 1, 0);
    card_step = BOOT_TROPHY_CARD_IDLE;
    reset_slot(0);
    settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    if (settings == 0)
    {
        return 0;
    }

    if (transfer_buffer == 0)
    {
        transfer_buffer = new (0) u8[BOOT_TRANSFER_BUFFER_SIZE];
    }

    ready = prepare_transfer_request(this);

    if (!ready)
    {
        return 0;
    }

    return 1;
}

/** @brief Release the transfer buffer and the memory card object, then queue this object for deletion. */
void BootBattleTrophyCard::destroy()
{
    if (transfer_buffer != 0)
    {
        delete[] transfer_buffer;
        transfer_buffer = 0;
    }

    if (card != 0)
    {
        card->destroy();
    }

    resident_enqueue_object(g_resident_release_queues, this);
}

/** @brief Destroy the object. */
BootBattleTrophyCard::~BootBattleTrophyCard()
{
}

/** @brief Clear the transfer state, both modes, and the filename. */
BootBattleTrophyCard::BootBattleTrophyCard()
{
    s32 index;
    card = 0;
    card_step = BOOT_TROPHY_CARD_UNINITIALIZED;
    slot = -1;
    last_card_status = -1;
    card_poll_paused = 0;
    card_formatted = 0;
    free_space = 0;
    pending_slot_reset = 0;
    memset_guess(save_file_probe_storage, 0, sizeof(save_file_probe_storage));
    save_file_probe_buffer = (u8*)BOOT_ALIGN_CARD_QUERY(save_file_probe_storage);
    low_space = 0;
    slot1_status_valid = 0;
    mode_status_valid[0] = 0;
    slot1_status = 0;
    mode_status[0] = 0;
    slot2_status_valid = 0;
    mode_status_valid[1] = 0;
    slot2_status = 0;
    mode_status[1] = 0;
    card_mode = 1;
    trophy_file_probe_buffer = 0;
    memset_guess(trophy_file_probe_storage, 0, sizeof(trophy_file_probe_storage));
    trophy_file_probe_buffer = (u8*)BOOT_ALIGN_CARD_QUERY(trophy_file_probe_storage);
    transfer_phase = BOOT_TROPHY_TRANSFER_INACTIVE;
    transfer_buffer = 0;
    transfer_slot = -1;
    transfer_result = -1;
    transfer_state = -1;
    transfer_destination = 0;
    settings = 0;
    transfer_pending = 0;

    for (index = 0; index < BOOT_TRANSFER_NAME_CAPACITY; index++)
    {
        filename[index] = 0;
    }

    transfer_open = 0;
    slot_free_space[0] = -1;
    save_probe_status[0] = -1;
    slot_free_space[1] = -1;
    save_probe_status[1] = -1;
}

/** @brief Destroy the object. */
BootStartupChecks::~BootStartupChecks()
{
}

/**
 * @brief Read the PlayStation BB Unit's state: one when it isn't initialized, two when it's ready.
 * @param archive Resource archive.
 * @return Unit state, or three when the archive has no unit information.
 */
static inline u8 unit_state(ResidentArchive* archive)
{
    return archive->unk12184 != 0 ? archive->unit_state : 3;
}

/** @brief Run the memory card, progressive display and BB Unit screens in turn, then start the opening movie. */
void BootStartupChecks::update()
{
    LibSystemSettings* settings;
    BootInput* input;
    s32 slot1;
    s32 slot2;
    u8 finished;
    u8 again;

    if (resident_archive_has_unit_error(g_resource_archive))
    {
        return;
    }

    settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);
    input = g_boot_program.input;
    slot1 = input->slot1_state;
    slot2 = input->slot2_state;

    if (screen == BOOT_STARTUP_CARD_CHECK)
    {
        switch (step)
        {
        case BOOT_STARTUP_CARD_INSPECT:
            if (RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
            {
                check_main_code();
                g_field_runtime->message_arguments[0] = 175;

                // Statuses 16-17 need no warning; these pairs can split the save and trophy files between cards.
                if ((u32)(slot1 - 16) <= 1 ||
                    (u32)(slot2 - 16) <= 1 ||
                    (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE) ||
                    (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE) ||
                    (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE) ||
                    (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE) ||
                    (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY) ||
                    (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE))
                {
                    screen = BOOT_STARTUP_PROGRESSIVE;
                    step = BOOT_STARTUP_PROGRESSIVE_DETECT;
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_NO_CARD;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_UNAVAILABLE && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT2_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_EITHER_FILE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_NO_SPACE && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_EITHER_FILE_ONLY && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_FULL;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_SPACE_ONLY)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE && slot2 == BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_UNAVAILABLE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_SLOT1_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_NO_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }

                if (slot1 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE && slot2 == BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE)
                {
                    shown_slot1 = slot1;
                    shown_slot2 = slot2;
                    message = BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE;
                    step = BOOT_STARTUP_CARD_SHOW_WARNING;
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    return;
                }
            }

            break;
        case BOOT_STARTUP_CARD_SHOW_WARNING:
            check_main_code();
            container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
            lib_queue_display_object(g_field_runtime,
                                     reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
            text = new (0) LibTextWidget(g_boot_program.get_messages(), message, 0, 32.0f, 128.0f, 576.0f, 320.0f);
            lib_container_attach_widget(container, text);
            step = BOOT_STARTUP_CARD_WAIT_FOR_INPUT;
            break;
        case BOOT_STARTUP_CARD_WAIT_FOR_INPUT:
        {
            u16 pressed = input->pressed;

            if (pressed & settings->confirm_buttons)
            {
                check_main_code();
                screen = BOOT_STARTUP_PROGRESSIVE;
                step = BOOT_STARTUP_PROGRESSIVE_DETECT;
                text->destroy();
                text = 0;
                container->destroy();
                container = 0;
                resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
            }
            else if (pressed & settings->cancel_buttons)
            {
                text->destroy();
                text = 0;
                container->destroy();
                container = 0;
                resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                step = BOOT_STARTUP_CARD_INSPECT;
            }
            else if (shown_slot1 != slot1 || shown_slot2 != slot2)
            {
                text->destroy();
                text = 0;
                container->destroy();
                container = 0;
                input->clear_card_states();
                step = BOOT_STARTUP_CARD_INSPECT;
            }

            break;
        }
        }
    }
    else if (screen == BOOT_STARTUP_PROGRESSIVE)
    {
        finished = 0;

        do
        {
            switch (step)
            {
            case BOOT_STARTUP_PROGRESSIVE_DETECT:
                again = 0;
                check_main_code();

                if ((input->held & BOOT_BUTTON_TRIANGLE) && (input->held & BOOT_BUTTON_CROSS))
                {
                    step++;
                    container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
                    lib_queue_display_object(g_field_runtime,
                                             reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
                }
                else if (++frames >= 30 && RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
                {
                    finished = 1;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_LOAD_OFFER:
                again = 0;

                if (RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
                {
                    check_main_code();
                    text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_PROGRESSIVE_OFFER, 0, 32.0f, 96.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(container, text);
                    step++;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_OFFER:
                again = 0;
                check_main_code();

                if (input->pressed & settings->confirm_buttons)
                {
                    step++;
                    frames = 0;
                    text->destroy();
                    text = 0;
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                    settings->widescreen = BOOT_STARTUP_PROGRESSIVE;
                }
                else if (input->pressed & settings->alternate_buttons)
                {
                    step++;
                    frames = 0;
                    text->destroy();
                    text = 0;
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                    settings->widescreen = 0;
                }
                else if (input->pressed & settings->cancel_buttons)
                {
                    resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                    finished = 1;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_SWITCH_DELAY:
                again = 0;
                check_main_code();

                if (++frames > 10)
                {
                    g_boot_program.set_progressive(1);
                    frames = 0;
                    step++;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_SWITCH_WAIT:
                again = 0;
                check_main_code();

                if (++frames > 60)
                {
                    step++;

                    if (settings->widescreen)
                    {
                        text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_PROGRESSIVE_WIDE_STARTED, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                        text->set_scale(0.75f);
                    }
                    else
                    {
                        text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_PROGRESSIVE_NORMAL_STARTED, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                    }

                    lib_container_attach_widget(container, text);
                    frames = 0;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_CONFIRM:
                again = 0;
                check_main_code();

                if (input->pressed & settings->confirm_buttons)
                {
                    finished = 1;
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                }
                else if (++frames > 539 || (input->pressed & settings->cancel_buttons))
                {
                    text->destroy();
                    text = 0;
                    step++;
                    frames = 0;
                    resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_REVERT_DELAY:
                check_main_code();
                again = 0;

                if (++frames > 10)
                {
                    settings->widescreen = 0;
                    g_boot_program.set_progressive(0);
                    step++;
                    frames = 0;
                }

                break;
            case BOOT_STARTUP_PROGRESSIVE_REVERT_WAIT:
                check_main_code();
                again = 0;

                if (++frames > 60)
                {
                    step = BOOT_STARTUP_PROGRESSIVE_LOAD_OFFER;
                    frames = 0;
                }

                break;
            default:
                check_main_code();
                again = 0;
                break;
            }
        } while (again);

        if (finished)
        {
            step = BOOT_STARTUP_UNIT_INSPECT;

            if (text != 0)
            {
                text->destroy();
                text = 0;
            }

            if (container != 0)
            {
                container->destroy();
                container = 0;
            }

            screen = BOOT_STARTUP_UNIT_CHECK;
        }
    }
    else
    {
        finished = 0;

        do
        {
            switch (step)
            {
            case BOOT_STARTUP_UNIT_INSPECT:
                again = 0;
                check_main_code();

                if (unit_state(g_resource_archive) != 2)
                {
                    if (unit_state(g_resource_archive) == 1)
                    {
                        step++;
                        container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
                        lib_queue_display_object(g_field_runtime,
                                                 reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
                    }
                    else if (g_boot_program.unit_data_deleted != 0)
                    {
                        step = BOOT_STARTUP_UNIT_LOAD_DELETED_WARNING;
                        container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
                        lib_queue_display_object(g_field_runtime,
                                                 reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
                    }
                    else
                    {
                        finished = 1;
                    }
                }

                break;
            case BOOT_STARTUP_UNIT_LOAD_WARNING:
                again = 0;
                check_main_code();

                if (RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
                {
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_UNIT_NOT_INITIALIZED, 0, 32.0f, 96.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(container, text);
                    step++;
                }

                break;
            case BOOT_STARTUP_UNIT_WAIT_FOR_INPUT:
                check_main_code();
                again = 0;

                if (input->pressed & settings->confirm_buttons)
                {
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                    finished = 1;
                }

                break;
            case BOOT_STARTUP_UNIT_LOAD_DELETED_WARNING:
                again = 0;

                if (RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) != 0)
                {
                    resident_sound_play(g_sound, 8, 0, 0, 0x7F, 0x40, 0);
                    text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_UNIT_DATA_DELETED, 0, 32.0f, 128.0f, 576.0f, 320.0f);
                    lib_container_attach_widget(container, text);
                    step = BOOT_STARTUP_UNIT_WAIT_FOR_INPUT;
                }

                break;
            default:
                again = 0;
                break;
            }
        } while (again);

        if (finished)
        {
            if (container != 0)
            {
                container->destroy();
                container = 0;
            }

            if (text != 0)
            {
                text->destroy();
                text = 0;
            }

            lib_object_detach_owner(this);
            destroy();
            g_update_list->append_node(new (0) BootOpeningMovie, -1);
        }
    }
}

/** @brief Start on the memory card check. */
BootStartupChecks::BootStartupChecks()
{
    step = BOOT_STARTUP_CARD_INSPECT;
    frames = 0;
    screen = BOOT_STARTUP_CARD_CHECK;
    container = 0;
    text = 0;
}

/**
 * @brief Report the list kind used when registration requests the default.
 * @return Four.
 */
s32 BootNewGameSettings::get_default_list_kind()
{
    return 4;
}

/**
 * @brief Multiply the first three components of a vector by another vector's.
 * @param vector Vector to scale.
 * @param scale Per-component factors; w is unused.
 * @return The scaled vector.
 */
static inline FieldVec4B scale_components(const FieldVec4A& vector, const LibVector4& scale)
{
    FieldVec4B result = vector;
    result.x *= scale.x;
    result.y *= scale.y;
    result.z *= scale.z;
    return result;
}

/**
 * @brief Combine two rotations.
 * @param left Rotation applied second.
 * @param right Rotation applied first.
 * @return The product left * right.
 */
static inline FieldVec4B multiply_rotations(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B result;
    result.x = left.w * right.x + right.w * left.x + left.y * right.z - left.z * right.y;
    result.y = left.w * right.y + right.w * left.y + left.z * right.x - left.x * right.z;
    result.z = left.w * right.z + right.w * left.z + left.x * right.y - left.y * right.x;
    result.w = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;
    return result;
}

/**
 * @brief Return the absolute value of a float (one abs.s).
 * @param value Value to convert.
 * @return Absolute value.
 */
static inline float abs_float(float value)
{
    return __s_abs(value);
}

/** @brief Move the girl to her angle around the listener with her lean, then step her walk animations. */
void BootNewGameSettings::place_girl()
{
    LibVector4 position;
    LibVector4 angles;
    LibMatrix44Value matrix;
    FieldVec4B target;
    FieldVec4B rotation;
    FieldVec4B roll;
    LibVector4 axis;
    LibVector4 offset;
    float angle = girl_angle;
    lib_compute_sine_cosine_pair_degree9(&angles, angle);
    position.x = 300.0f * angles.z;
    position.z = 300.0f * angles.w;
    position.y = 0.0f;
    position.w = 1.0f;
    target = scale_components(FieldVec4A(-1.0f, -1.0f, -1.0f, -1.0f), position);
    lib_matrix_look_at(&matrix, reinterpret_cast<const FieldVec4B*>(&position), &target, 0.0f);
    lib_matrix_to_quaternion(&rotation, &matrix);
    axis.x = 0.0f;
    axis.y = 1.0f;
    axis.z = 0.0f;
    axis.w = girl_lean;
    lib_quaternion_from_axis_angle(&roll, &axis);
    rotation = multiply_rotations(roll, rotation);

    if (turn_speed == 0.0f)
    {
        if (girl_lean > 0.0f)
        {
            girl_lean -= 3.1415927f * g_frame_seconds;
            girl_lean = ee_max_in_place(0.0f, girl_lean);
        }
        else
        {
            girl_lean += 3.1415927f * g_frame_seconds;
            girl_lean = ee_min(0.0f, girl_lean);
        }
    }
    else if (turn_speed < 0.0f)
    {
        girl_lean += 9.424778f * g_frame_seconds;
        girl_lean = ee_min(1.5707964f, girl_lean);
    }
    else
    {
        girl_lean -= 9.424778f * g_frame_seconds;
        girl_lean = ee_max(-1.5707964f, girl_lean);
    }

    LibTransformOwner* root = lib_find_transform_entry(girl_scene, g_root_node_name);
    root->set_translation_vector(&position);
    root->set_orientation((LibVector4*)&rotation);

    bool again = true;

    while (again)
    {
        switch (walk_state)
        {
        case 0:
            if (turn_speed != 0.0f)
            {
                animation_frame = 0.0f;
                girl_animations[1]->started = 0;
                walk_state = 1;
            }
            else if (lib_animation_apply_frame(girl_animations[0], animation_frame, 2) > 0)
            {
                animation_frame = 0.0f;
            }
            else
            {
                again = false;
            }

            break;
        case 1:
            if (lib_animation_apply_frame(girl_animations[1], animation_frame, 2) > 0)
            {
                if (turn_speed == 0.0f)
                {
                    animation_frame = 0.0f;
                    girl_animations[5]->started = 0;
                    walk_state = 5;
                }
                else
                {
                    animation_frame = 0.0f;
                    girl_animations[2]->started = 0;
                    walk_state = 2;
                }
            }
            else
            {
                again = false;
            }

            break;
        case 2:
            if (lib_animation_apply_frame(girl_animations[2], animation_frame, 2) > 0)
            {
                if (turn_speed == 0.0f)
                {
                    animation_frame = 0.0f;
                    girl_animations[4]->started = 0;
                    walk_state = 4;
                }
                else
                {
                    animation_frame = 0.0f;
                    girl_animations[3]->started = 0;
                    walk_state = 3;
                }
            }
            else
            {
                again = false;
            }

            break;
        case 3:
            if (lib_animation_apply_frame(girl_animations[3], animation_frame, 2) > 0)
            {
                if (turn_speed == 0.0f)
                {
                    animation_frame = 0.0f;
                    girl_animations[5]->started = 0;
                    walk_state = 5;
                }
                else
                {
                    animation_frame = 0.0f;
                    girl_animations[2]->started = 0;
                    walk_state = 2;
                }
            }
            else
            {
                again = false;
            }

            break;
        case 4:
            if (lib_animation_apply_frame(girl_animations[4], animation_frame, 2) > 0)
            {
                girl_animations[0]->started = 0;
                animation_frame = 0.0f;
                walk_state = 0;
            }
            else
            {
                again = false;
            }

            break;
        case 5:
            if (lib_animation_apply_frame(girl_animations[5], animation_frame, 2) > 0)
            {
                girl_animations[0]->started = 0;
                animation_frame = 0.0f;
                walk_state = 0;
            }
            else
            {
                again = false;
            }

            break;
        }
    }

    switch (walk_state)
    {
    case 0:
    case 4:
    case 5:
        animation_frame += g_frame_ticks;
        break;
    case 1:
    case 2:
    case 3:
    {
        float step;

        if (turn_speed == 0.0f)
        {
            step = 1.0f;
        }
        else
        {
            step = ee_max(0.5f, abs_float(turn_speed));
        }

        animation_frame += step;
        break;
    }
    }

    LibTransform* look = static_cast<LibTransform*>(lib_find_named_entry(girl_scene, g_look_node_name));

    if (look != 0)
    {
        offset.x = 0.0f;
        offset.y = -160.0f;
        offset.z = 0.0f;
        offset.w = 1.0f;
        lib_solve_ik_chain(look, &offset, 1, 4, 0, 0.5f);
    }
}

/**
 * @brief Read the cursor position for a speaker on the speaker setup screen.
 * @param speaker Speaker index.
 * @param x Receives the horizontal position.
 * @param y Receives the vertical position.
 */
void BootNewGameSettings::get_speaker_cursor_position(s32 speaker, float* x, float* y)
{
    BootClass170F30* speakers[4];
    LibVector4 position;
    LibVector4 screen;
    speakers[0] = lib_find_renderable_entry(room_scene, g_right_speaker_name);
    speakers[1] = lib_find_renderable_entry(room_scene, g_left_speaker_name);
    speakers[2] = lib_find_renderable_entry(room_scene, g_rear_left_speaker_name);
    speakers[3] = lib_find_renderable_entry(room_scene, g_rear_right_speaker_name);
    speakers[speaker]->update_transform_matrix();
    BootClass170F30* model = speakers[speaker];
    position.x = model->transform.m[0][3];
    position.y = model->transform.m[1][3];
    position.z = model->transform.m[2][3];
    position.w = 1.0f;
    LibDisplayManager* manager = g_display_manager;
    static_cast<LibClass179080*>(manager->current_display)->update_projection();
    lib_load_camera_screen_matrix(static_cast<LibClass179080*>(g_display_manager->current_display));
    vu0_wait_microprogram();
    vu0_start_microprogram_vf5(&position);
    vu0_wait_microprogram();
    vu0_read_vf6(&screen);
    *x = screen.x - 1728.0f;
    *y = screen.y - 1824.0f;
}

/**
 * @brief Give a speaker model an even color modulation and recompute its combined color.
 * @param model Speaker model.
 * @param shade Red, green and blue factor; alpha is one.
 */
static inline void set_speaker_color(BootClass170F30* const& model, float shade)
{
    LibVector4 color;
    color.x = shade;
    color.y = shade;
    color.z = shade;
    color.w = 1.0f;
    BootClass170F30* speaker = model;
    copy_vector(&speaker->base_color_factor, &color);
    speaker->update_combined_color_factor();
}

/** @brief Place the five speaker models around the listener and pulse the one being moved. */
void BootNewGameSettings::place_speakers()
{
    BootClass170F30* speakers[5];
    speakers[0] = lib_find_renderable_entry(room_scene, g_right_speaker_name);
    speakers[1] = lib_find_renderable_entry(room_scene, g_left_speaker_name);
    speakers[2] = lib_find_renderable_entry(room_scene, g_rear_left_speaker_name);
    speakers[3] = lib_find_renderable_entry(room_scene, g_rear_right_speaker_name);
    speakers[4] = lib_find_renderable_entry(room_scene, g_center_speaker_name);

    for (s32 i = 0; i < 5; i++)
    {
        LibVector4 position;
        LibVector4 angles;
        LibMatrix44Value matrix;
        FieldVec4B target;
        LibVector4 rotation;
        lib_compute_sine_cosine_pair_degree9(&angles, i < 4 ? g_sound->speaker_angles[i] : 1.5707964f);
        position.x = 250.0f * angles.z;
        position.z = 250.0f * angles.w;
        position.y = 0.0f;
        position.w = 1.0f;
        speakers[i]->set_translation_vector(&position);
        target = scale_components(FieldVec4A(-1.0f, -1.0f, -1.0f, -1.0f), position);
        lib_matrix_look_at(&matrix, reinterpret_cast<const FieldVec4B*>(&position), &target, 0.0f);
        lib_matrix_to_quaternion(reinterpret_cast<FieldVec4B*>(&rotation), &matrix);
        speakers[i]->set_orientation(&rotation);
    }

    if (adjusting_speaker != 0)
    {
        for (s32 i = 0; i < 4; i++)
        {
            if (i == selected_speaker)
            {
                LibVector4 scale;
                copy_vector(&scale, &speakers[i]->base_color_factor);

                if (adjusting_speaker == 1)
                {
                    scale.x += 2.0f * g_frame_seconds;
                    scale.y += 2.0f * g_frame_seconds;
                    scale.z += 2.0f * g_frame_seconds;

                    if (!(scale.x <= 2.0f))
                    {
                        scale.x = 2.0f;
                        scale.y = 2.0f;
                        scale.z = 2.0f;
                        adjusting_speaker = 2;
                    }
                }
                else
                {
                    scale.x -= 2.0f * g_frame_seconds;
                    scale.y -= 2.0f * g_frame_seconds;
                    scale.z -= 2.0f * g_frame_seconds;

                    if (scale.x < 1.0f)
                    {
                        scale.x = 1.0f;
                        scale.y = 1.0f;
                        scale.z = 1.0f;
                        adjusting_speaker = 1;
                    }
                }

                BootClass170F30* model = speakers[i];
                copy_vector(&model->base_color_factor, &scale);
                model->update_combined_color_factor();
            }
            else
            {
                set_speaker_color(speakers[i], 1.0f);
            }
        }
    }
    else
    {
        for (s32 i = 0; i < 4; i++)
        {
            set_speaker_color(speakers[i], 1.0f);
        }
    }
}

/** @brief Select the option that matches the current page's saved setting. */
void BootNewGameSettings::load_option_value()
{
    LibSystemSettings* settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    switch (page)
    {
    case BOOT_SETTINGS_TV_MODE:
        if (settings->widescreen != 0)
        {
            selection = 1;
        }
        else
        {
            selection = 0;
        }

        break;
    case BOOT_SETTINGS_SOUND:
        switch (g_sound->output_mode)
        {
        case 1:
            selection = LIB_SOUND_MONO;
            break;
        case 0:
            selection = LIB_SOUND_STEREO;
            break;
        case 2:
            selection = LIB_SOUND_DOLBY_PRO_LOGIC_II;
            break;
        case 3:
            selection = LIB_SOUND_HEADPHONES;
            break;
        }

        break;
    case BOOT_SETTINGS_EVENT_SKIP:
        selection = !settings->event_skip;
        break;
    case BOOT_SETTINGS_VOICE:
        selection = settings->voice_mode;
        break;
    case BOOT_SETTINGS_VIBRATION:
        selection = !settings->vibration;
        break;
    case BOOT_SETTINGS_DIFFICULTY:
        selection = settings_difficulty(settings);
        break;
    }
}

/** @brief Save the selected option for the current page and apply it to the display, sound or pad. */
void BootNewGameSettings::apply_option_value()
{
    LibSystemSettings* settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    switch (page)
    {
    case BOOT_SETTINGS_TV_MODE:
        switch (selection)
        {
        case 0:
            settings->widescreen = 0;
            g_scene_camera->pixel_aspect = (1.3333334f * (1.0714285f * (float)g_boot_program.display->display_area.height)) / (float)g_boot_program.display->display_area.width;
            g_scene_camera->horizontal_fov = 1.5707964f;
            g_boot_program.update_projection_aspect();
            break;
        case 1:
            settings->widescreen = 1;
            g_scene_camera->pixel_aspect =
                (1.7777778f * ((1.3333334f * (1.0714285f * (float)g_boot_program.display->display_area.height)) / (float)g_boot_program.display->display_area.width)) /
                1.3333334f;
            g_scene_camera->horizontal_fov = 1.8325958f;
            g_boot_program.update_projection_aspect();
            break;
        }

        break;
    case BOOT_SETTINGS_SOUND:
        switch (selection)
        {
        case LIB_SOUND_MONO:
            resident_sound_set_output_mode(g_sound, 1);
            settings->sound_output = LIB_SOUND_MONO;
            break;
        case LIB_SOUND_STEREO:
            resident_sound_set_output_mode(g_sound, 0);
            settings->sound_output = LIB_SOUND_STEREO;
            break;
        case LIB_SOUND_DOLBY_PRO_LOGIC_II:
            resident_sound_set_output_mode(g_sound, 2);
            settings->sound_output = LIB_SOUND_DOLBY_PRO_LOGIC_II;
            break;
        case LIB_SOUND_HEADPHONES:
            resident_sound_set_output_mode(g_sound, 3);
            settings->sound_output = LIB_SOUND_HEADPHONES;
            break;
        }

        break;
    case BOOT_SETTINGS_EVENT_SKIP:
        switch (selection)
        {
        case 0:
            settings->event_skip = 1;
            break;
        case 1:
            settings->event_skip = 0;
            break;
        }

        break;
    case BOOT_SETTINGS_VOICE:
        settings->voice_mode = selection;
        break;
    case BOOT_SETTINGS_VIBRATION:
        switch (selection)
        {
        case 0:
            settings->vibration = 1;
            resident_pad_set_vibration_enabled(g_input_system, 0, 1);
            resident_pad_set_vibration(g_input_system, 0, 1, 0x40);
            rumble_frames = 10;
            break;
        case 1:
            settings->vibration = 0;
            resident_pad_set_vibration_enabled(g_input_system, 0, 0);
            break;
        }

        break;
    case BOOT_SETTINGS_DIFFICULTY:
        settings_set_difficulty(settings, selection);
        break;
    }
}

/**
 * @brief Pick the message that describes the selected option.
 * @return Message key, or zero for an unknown page.
 */
s32 BootNewGameSettings::get_value_message()
{
    LibSystemSettings* settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    switch (page)
    {
    case BOOT_SETTINGS_TV_MODE:
        return selection + BOOT_MSG_TV_NORMAL;
    case BOOT_SETTINGS_SOUND:
        if (selection == LIB_SOUND_HEADPHONES)
        {
            return BOOT_MSG_SOUND_HEADPHONES;
        }

        return selection + BOOT_MSG_SOUND_MONO;
    case BOOT_SETTINGS_EVENT_SKIP:
        return selection + BOOT_MSG_EVENT_SKIP_ON;
    case BOOT_SETTINGS_VOICE:
        if (selection == LIB_VOICE_AUTO)
        {
            return BOOT_MSG_VOICE_AUTO;
        }

        return selection + BOOT_MSG_VOICE_SUBTITLES_AND_SOUND;
    case BOOT_SETTINGS_VIBRATION:
        return selection + BOOT_MSG_VIBRATION_ON;
    case BOOT_SETTINGS_DIFFICULTY:
        if (selection == LIB_DIFFICULTY_FOURTH_DIMENSION)
        {
            if (settings_fourth_dimension_unlocked(settings))
            {
                return BOOT_MSG_FOURTH_DIMENSION;
            }

            return BOOT_MSG_FOURTH_DIMENSION_LOCKED;
        }

        if (settings_universe_unlocked(settings) && selection == LIB_DIFFICULTY_UNIVERSE)
        {
            return BOOT_MSG_UNIVERSE_UNLOCKED;
        }

        return selection + BOOT_MSG_DIFFICULTY_EARTH;
    }

    return 0;
}

/**
 * @brief Read the cursor position for the selected row of the current page.
 * @param x Receives the horizontal position.
 * @param y Receives the vertical position; unchanged for an unknown row.
 */
void BootNewGameSettings::get_cursor_position(float* x, float* y)
{
    LibSystemSettings* settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    *x = 58.0f;
    switch (page)
    {
    case BOOT_SETTINGS_SOUND:
        switch (selection)
        {
        case LIB_SOUND_MONO:
            *y = 90.0f;
            return;
        case LIB_SOUND_STEREO:
            *y = 126.0f;
            return;
        case LIB_SOUND_DOLBY_PRO_LOGIC_II:
            *y = 160.0f;
            return;
        case LIB_SOUND_HEADPHONES:
            *y = 194.0f;
            return;
        }

        break;
    case BOOT_SETTINGS_VOICE:
        switch (selection)
        {
        case LIB_VOICE_SUBTITLES_AND_SOUND:
            *y = 108.0f;
            return;
        case LIB_VOICE_SOUND_ONLY:
            *y = 148.0f;
            return;
        case LIB_VOICE_SUBTITLES_ONLY:
            *y = 188.0f;
            return;
        case LIB_VOICE_AUTO:
            *y = 228.0f;
            return;
        }

        break;
    case BOOT_SETTINGS_DIFFICULTY:
        if (settings_universe_unlocked(settings))
        {
            switch (selection)
            {
            case LIB_DIFFICULTY_EARTH:
                *y = 108.0f;
                return;
            case LIB_DIFFICULTY_GALAXY:
                *y = 148.0f;
                return;
            case LIB_DIFFICULTY_UNIVERSE:
                *y = 188.0f;
                return;
            case LIB_DIFFICULTY_FOURTH_DIMENSION:
                *y = 228.0f;
                return;
            }
        }
        else
        {
            switch (selection)
            {
            case LIB_DIFFICULTY_EARTH:
                *y = 108.0f;
                return;
            case LIB_DIFFICULTY_GALAXY:
                *y = 158.0f;
                return;
            case LIB_DIFFICULTY_UNIVERSE:
                *y = 208.0f;
                return;
            }
        }

        break;
    default:
        switch (selection)
        {
        case 0:
            *y = 108.0f;
            return;
        case 1:
            *y = 176.0f;
            return;
        }

        break;
    }
}

/**
 * @brief Store a model's color modulation and recompute its combined color.
 * @param model Model to update.
 * @param red Red factor.
 * @param green Green factor.
 * @param blue Blue factor.
 * @param alpha Alpha factor.
 */
static inline void set_model_color(LibModel* model, float red, float green, float blue, float alpha)
{
    LibVector4 color;
    color.x = red;
    color.y = green;
    color.z = blue;
    color.w = alpha;
    copy_vector(&model->base_color_factor, &color);
    model->update_combined_color_factor();
}

/** @brief Rebuild the current page's option rows when the page changes, then place and highlight them. */
void BootNewGameSettings::update_option_rows()
{
    LibSystemSettings* settings;

    if (image_blocks[4] != 0 && on_speaker_setup == 0)
    {
        settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

        if (shown_page != page)
        {
            shown_page = page;

            for (s32 i = 0; i < 4; i++)
            {
                if (images[16 + i] != 0)
                {
                    lib_object_detach_owner(images[16 + i]);
                    images[16 + i]->destroy();
                    images[16 + i] = 0;
                }

                images[16 + i] = new (0) BootImage;
            }

            switch (page)
            {
            case BOOT_SETTINGS_TV_MODE:
                row_x = -272.0f;
                images[16]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[3]), 0);
                images[16]->set_rectangle(0, 8, 288, 40, 0x80808080, 0);
                images[16]->model->set_translation(-272.0f, -142.0f, 0.0f);
                images[17]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[3]), 0);
                images[17]->set_rectangle(0, 68, 288, 40, 0x80808080, 0);
                images[17]->model->set_translation(-272.0f, -74.0f, 0.0f);
                break;
            case BOOT_SETTINGS_SOUND:
                row_x = -272.0f;
                images[16]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[3]), 0);
                images[16]->set_rectangle(0, 106, 288, 40, 0x80808080, 0);
                images[16]->model->set_translation(-272.0f, -162.0f, 0.0f);
                images[17]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[3]), 0);
                images[17]->set_rectangle(0, 162, 200, 40, 0x80808080, 0);
                images[17]->model->set_translation(-272.0f, -126.0f, 0.0f);
                images[18]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[3]), 0);
                images[18]->set_rectangle(0, 236, 424, 40, 0x80808080, 0);
                images[18]->model->set_translation(-272.0f, -90.0f, 0.0f);
                images[19]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[3]), 0);
                images[19]->set_rectangle(224, 168, 237, 38, 0x80808080, 0);
                images[19]->model->set_translation(-272.0f, -55.0f, 0.0f);
                break;
            case BOOT_SETTINGS_EVENT_SKIP:
                row_x = -272.0f;
                images[16]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[3]), 0);
                images[16]->set_rectangle(0, 312, 340, 40, 0x80808080, 0);
                images[16]->model->set_translation(-272.0f, -142.0f, 0.0f);
                images[17]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[3]), 0);
                images[17]->set_rectangle(0, 368, 340, 40, 0x80808080, 0);
                images[17]->model->set_translation(-272.0f, -74.0f, 0.0f);
                break;
            case BOOT_SETTINGS_VOICE:
                row_x = -260.0f;
                images[16]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                images[16]->set_rectangle(0, 0, 340, 40, 0x80808080, 0);
                images[16]->model->set_translation(-260.0f, -142.0f, 0.0f);
                images[17]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                images[17]->set_rectangle(0, 55, 340, 40, 0x80808080, 0);
                images[17]->model->set_translation(-260.0f, -102.0f, 0.0f);
                images[18]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                images[18]->set_rectangle(0, 110, 340, 40, 0x80808080, 0);
                images[18]->model->set_translation(-260.0f, -62.0f, 0.0f);
                images[19]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                images[19]->set_rectangle(0, 416, 500, 40, 0x80808080, 0);
                images[19]->model->set_translation(-260.0f, -22.0f, 0.0f);
                break;
            case BOOT_SETTINGS_VIBRATION:
                row_x = -254.0f;
                images[16]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                images[16]->set_rectangle(0, 160, 340, 40, 0x80808080, 0);
                images[16]->model->set_translation(-272.0f, -142.0f, 0.0f);
                images[17]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                images[17]->set_rectangle(0, 215, 340, 40, 0x80808080, 0);
                images[17]->model->set_translation(-272.0f, -74.0f, 0.0f);
                break;
            case BOOT_SETTINGS_DIFFICULTY:
                row_x = -260.0f;

                if (!settings_universe_unlocked(settings))
                {
                    images[16]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                    images[16]->set_rectangle(0, 257, 340, 42, 0x80808080, 0);
                    images[16]->model->set_translation(-260.0f, -142.0f, 0.0f);
                    images[17]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                    images[17]->set_rectangle(0, 313, 340, 42, 0x80808080, 0);
                    images[17]->model->set_translation(-260.0f, -92.0f, 0.0f);
                    images[18]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                    images[18]->set_rectangle(0, 369, 340, 42, 0x80808080, 0);
                    images[18]->model->set_translation(-260.0f, -42.0f, 0.0f);
                }
                else
                {
                    images[16]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                    images[16]->set_rectangle(3, 257, 340, 42, 0x80808080, 0);
                    images[16]->model->set_translation(-260.0f, -142.0f, 0.0f);
                    images[17]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                    images[17]->set_rectangle(3, 313, 340, 42, 0x80808080, 0);
                    images[17]->model->set_translation(-260.0f, -102.0f, 0.0f);
                    images[18]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                    images[18]->set_rectangle(3, 369, 340, 42, 0x80808080, 0);
                    images[18]->model->set_translation(-260.0f, -62.0f, 0.0f);
                    images[19]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[4]), 0);
                    images[19]->set_rectangle(0, 466, 340, 42, 0x80808080, 0);
                    images[19]->model->set_translation(-260.0f, -24.0f, 0.0f);
                }

                break;
            }
        }

        if (settings->widescreen)
        {
            for (s32 i = 0; i < 4; i++)
            {
                if (images[16 + i] != 0 && images[16 + i]->model != 0)
                {
                    LibVector4 position;
                    copy_vector(&position, &images[16 + i]->model->translation);
                    position.x = 8.0f + 1.3333334f * row_x;
                    images[16 + i]->model->set_translation_vector(&position);
                }
            }
        }
        else
        {
            for (s32 i = 0; i < 4; i++)
            {
                if (images[16 + i] != 0 && images[16 + i]->model != 0)
                {
                    LibVector4 position;
                    copy_vector(&position, &images[16 + i]->model->translation);
                    position.x = row_x;
                    images[16 + i]->model->set_translation_vector(&position);
                }
            }
        }

        s32 i;
        LibModel* model;
        // Form the settings block pointer before the loop to preserve its access pattern.
        u8* extra = &settings->unk1A0;

        for (i = 0; i < 4; i++)
        {
            if (images[16 + i] == 0)
            {
                continue;
            }

            model = images[16 + i]->model;

            if (model == 0)
            {
                continue;
            }

            if (i == 2 && page == BOOT_SETTINGS_DIFFICULTY)
            {
                if (!settings_extra_byte(settings, extra, &settings->universe_unlocked))
                {
                    set_model_color(model, 0.5f, 0.5f, 0.5f, 1.0f);
                    continue;
                }
            }

            if (i == 3 && page == BOOT_SETTINGS_DIFFICULTY)
            {
                if (!settings_extra_byte(settings, extra, &settings->fourth_dimension_unlocked))
                {
                    set_model_color(model, 0.5f, 0.5f, 0.5f, 1.0f);
                    continue;
                }
            }

            if (selection == i)
            {
                LibVector4 scale;
                copy_vector(&scale, &model->base_color_factor);

                if (highlight_phase == 0)
                {
                    scale.x -= 0.01f * g_frame_ticks;
                    scale.y -= 0.005f * g_frame_ticks;

                    if (scale.y < 0.5f)
                    {
                        scale.y = 0.5f;
                    }

                    if (scale.x < 0.5f)
                    {
                        scale.x = 0.5f;
                        highlight_phase = 1;
                    }
                }
                else if (highlight_phase != 0)
                {
                    scale.x += 0.01f * g_frame_ticks;
                    scale.y += 0.005f * g_frame_ticks;

                    if (!(scale.y <= 1.0f))
                    {
                        scale.y = 1.0f;
                    }

                    if (!(scale.x <= 1.0f))
                    {
                        scale.x = 1.0f;
                        highlight_phase = 0;
                    }
                }

                copy_vector(&model->base_color_factor, &scale);
                model->update_combined_color_factor();
            }
            else
            {
                set_model_color(model, 1.0f, 1.0f, 1.0f, 1.0f);
            }
        }
    }
}


/** @brief Create the page's images once their textures are loaded, then place and highlight them. */
void BootNewGameSettings::update_page_images()
{
    LibSystemSettings* settings;
    BootLabelOffsets offsets;

    if (image_blocks[4] == 0)
    {
        return;
    }

    if (images[0] == 0)
    {
        images[0] = new (0) BootImage;
        images[0]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[0]), 0);
        images[0]->set_rectangle(0, 1, 0x1E8, 0xDF, 0x80808080, 0);
        images[0]->model->set_translation(-244.0f, -112.0f, 0.0f);
    }

    if (images[1] == 0)
    {
        images[1] = new (0) BootImage;
        images[1]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[1]), 0);
        images[1]->set_rectangle(0, 0, 0x280, 0x50, 0x80808080, 0);
        images[1]->model->set_translation(-320.0f, -216.0f, 0.0f);
    }

    if (images[2] == 0 && on_speaker_setup == 0)
    {
        images[2] = new (0) BootImage;
        images[2]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[0]), 0);
        images[2]->set_rectangle(0x1A, 0xF5, 0x18, 0x16, 0x80808080, 0);

        for (s32 i = 0; i < 6; i++)
        {
            images[3 + i] = new (0) BootImage;
            images[3 + i]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[0]), 0);
            images[3 + i]->set_rectangle(0x52, 0xF3 + i * 29, 0xEE, 0x1C, 0x80808080, 0);
        }
    }

    if (images[9] == 0)
    {
        for (s32 i = 0; i < 6; i++)
        {
            images[9 + i] = new (0) BootImage;
            images[9 + i]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[2]), 0);
            images[9 + i]->set_rectangle(0, 2 + i * 32, 0x180, 0x20, 0x80808080, 0);
        }
    }

    if (images[15] == 0 && on_speaker_setup == 0)
    {
        images[15] = new (0) BootImage;
        images[15]->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(image_blocks[2]), 0);
        images[15]->set_rectangle(0, 0xC2, 0x180, 0x20, 0x80808080, 0);
    }

    settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    if (settings->widescreen)
    {
        if (images[1] != 0)
        {
            images[1]->model->set_translation(-414.66669f, -216.0f, 0.0f);
            images[1]->model->set_scale(1.31f, 1.0f, 1.0f);
        }

        for (s32 i = 0; i < 6; i++)
        {
            if (images[3 + i] != 0)
            {
                images[3 + i]->model->set_translation(160.0f, 30.0f + (float)(i * 29), 0.0f);
            }

            if (images[9 + i] != 0)
            {
                images[9 + i]->model->set_translation(21.0f, -204.0f, 0.0f);
            }
        }

        if (images[15] != 0)
        {
            images[15]->model->set_translation(-426.66669f, 170.0f, 0.0f);
        }
    }
    else
    {
        if (images[1] != 0)
        {
            images[1]->model->set_translation(-320.0f, -216.0f, 0.0f);
            images[1]->model->set_scale(1.0f, 1.0f, 1.0f);
        }

        for (s32 i = 0; i < 6; i++)
        {
            if (images[3 + i] != 0)
            {
                images[3 + i]->model->set_translation(56.0f, 30.0f + (float)(i * 29), 0.0f);
            }

            if (images[9 + i] != 0)
            {
                images[9 + i]->model->set_translation(-80.0f, -204.0f, 0.0f);
            }
        }

        if (images[15] != 0)
        {
            images[15]->model->set_translation(-320.0f, 170.0f, 0.0f);
        }
    }

    offsets = g_settings_label_offsets;

    for (s32 i = 0; i < 6; i++)
    {
        if (page == i)
        {
            if (images[3 + i] != 0)
            {
                LibVector4 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = 1.0f;
                LibModel* model = images[3 + i]->model;
                copy_vector(&model->base_color_factor, &color);
                model->update_combined_color_factor();
            }

            if (images[2] != 0)
            {
                if (settings->widescreen)
                {
                    images[2]->model->set_translation(142.0f + 1.3333334f * (float)offsets.values[i], (float)(31.0 + 29.0 * i), 0.0f);
                }
                else
                {
                    images[2]->model->set_translation(44.0f + (float)offsets.values[i], (float)(31.0 + 29.0 * i), 0.0f);
                }
            }

            if (images[9 + i] != 0)
            {
                images[9 + i]->model->draw_flags &= ~LIB_DRAW_HIDDEN;
            }
        }
        else
        {
            if (images[3 + i] != 0)
            {
                LibVector4 color;
                color.x = 0.5f;
                color.y = 0.5f;
                color.z = 0.5f;
                color.w = 1.0f;
                LibModel* model = images[3 + i]->model;
                copy_vector(&model->base_color_factor, &color);
                model->update_combined_color_factor();
            }

            if (images[9 + i] != 0)
            {
                images[9 + i]->model->draw_flags |= LIB_DRAW_HIDDEN;
            }
        }
    }

    if (images[15] != 0)
    {
        if (page == BOOT_SETTINGS_DIFFICULTY)
        {
            images[15]->model->draw_flags |= LIB_DRAW_HIDDEN;
        }
        else
        {
            images[15]->model->draw_flags &= ~LIB_DRAW_HIDDEN;
        }
    }
}


/** @brief Show the message that describes the selected option. */
inline void BootNewGameSettings::show_value_message()
{
    lib_text_set_resource(description_text, g_boot_program.get_messages(), get_value_message(), 0);
}

/**
 * @brief Test buttons pressed this frame against a mask.
 * @param input Pad input.
 * @param mask Buttons to test.
 * @return Nonzero when any of them was pressed.
 */
static inline s32 button_pressed(BootInput* input, u16 mask)
{
    return input->pressed & mask;
}

/**
 * @brief Move the cursor straight to a position.
 * @param cursor Cursor to move.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
static inline void place_cursor(LibSelectionCursor* cursor, float x, float y)
{
    ItemCreationClass185050& motion = *cursor;
    motion.position.x = x;
    motion.position.y = y;
    motion.arrived = 1;
    cursor->unkae = 1;
}

/**
 * @brief Test whether a list walk has come back to the list.
 * @param list List sentinel.
 * @param node Current node.
 * @return Whether node is the sentinel.
 */
static inline bool at_end(const LibListSentinel* list, const LibListSentinel* node)
{
    if (list == node)
    {
        return true;
    }

    return false;
}

/**
 * @brief Read a surround speaker's current angle.
 * @param sound Sound system.
 * @param speaker Speaker index.
 * @return Angle in radians.
 */
static inline float speaker_angle(ResidentSound* sound, s32 speaker)
{
    return sound->speaker_angles[speaker];
}

/** @brief Run the current page or the speaker setup, then stream the next model block and place the rows. */
void BootNewGameSettings::update()
{
    BootInput* input = g_boot_program.input;
    LibSystemSettings* settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);
    u8 extra = settings_extra_byte(settings, &settings->unk1A0, &settings->universe_unlocked);
    g_difficulty_option_count = extra ? 4 : 3;

    switch (stage)
    {
    case BOOT_SETTINGS_STAGE_LOAD:
        if (resident_poll_resource_queue(g_resource_queue) != 0)
        {
            resident_sound_play_music(g_sound, 0x48, 1, 0, 0);
            resident_queue_resource_request(g_resource_queue, BOOT_RES_SETTINGS_MODELS, model_data,
                                            BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
            clear_to_menu_background();
            g_renderer->prepend_node(new (0) LibColorFade, -1);
            loaded_image_blocks = 0;
            stage++;
            highlight_phase = 0;
            container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
            lib_queue_display_object(g_field_runtime,
                                     reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
            description_text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_TV_NORMAL, 1, 32.0f, 272.0f, 344.0f, 224.0f);
            description_text->set_color(0x34130F);
            lib_container_attach_widget(container, description_text);
            load_option_value();
            show_value_message();
            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor = new (0) LibSelectionCursor;
            cursor->init(1, 0, 0xF42400, x, y, 0.0f);
            lib_queue_display_object(g_field_runtime, reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(cursor)));
            resident_sound_set_reverb(g_sound, BOOT_SETTINGS_REVERB_PRESET);
        }

        break;
    case BOOT_SETTINGS_STAGE_LOAD_IMAGES:
        image_blocks[loaded_image_blocks] =
            resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(image_data), loaded_image_blocks, 1);
        resident_decode_resource_block(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(image_data),
                                       (void*)RESIDENT_ALIGN_RESOURCE(image_blocks[loaded_image_blocks]), loaded_image_blocks);

        if (++loaded_image_blocks >= 5)
        {
            stage++;
            shown_page = 0xFF;
            FlushCache(0);
        }

        break;
    case BOOT_SETTINGS_STAGE_PAGE:
        if (input->repeated == BOOT_BUTTON_DOWN && cursor->arrived)
        {
            selection = (selection + 1) % g_settings_option_counts[page];
            apply_option_value();
            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->set_move_target(x, y, 0.05f);
            highlight_phase = 0;
            resident_sound_play(g_sound, 0, 0, 0, 0x7F, 0x40, 0);
            show_value_message();
        }

        if (input->repeated == BOOT_BUTTON_UP && cursor->arrived)
        {
            u8 count = g_settings_option_counts[page];
            selection = (selection + count - 1) % count;
            highlight_phase = 0;
            apply_option_value();
            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->set_move_target(x, y, 0.05f);
            resident_sound_play(g_sound, 0, 0, 0, 0x7F, 0x40, 0);
            show_value_message();
        }

        if (button_pressed(input, settings->confirm_buttons))
        {
            if (selection == 2 && page == BOOT_SETTINGS_DIFFICULTY && !settings_extra_byte(settings, &settings->unk1A0, &settings->universe_unlocked))
            {
                resident_sound_play(g_sound, 3, 0, 0, 0x7F, 0x40, 0);
                break;
            }

            if (selection == 3 && page == BOOT_SETTINGS_DIFFICULTY && !settings_extra_byte(settings, &settings->unk1A0, &settings->fourth_dimension_unlocked))
            {
                resident_sound_play(g_sound, 3, 0, 0, 0x7F, 0x40, 0);
                break;
            }

            resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            stage = BOOT_SETTINGS_STAGE_NEXT_PAGE;
        }
        else if (button_pressed(input, settings->cancel_buttons))
        {
            if (page == BOOT_SETTINGS_TV_MODE)
            {
                resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                resident_sound_stop_music(g_sound, 0x1E, -1);
                stage = BOOT_SETTINGS_STAGE_EXIT;
                break;
            }
            else
            {
                resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                stage = BOOT_SETTINGS_STAGE_PREVIOUS_PAGE;
            }
        }

        if (button_pressed(input, settings->alternate_buttons) && page == BOOT_SETTINGS_SOUND && selection == 2)
        {
            resident_sound_play(g_sound, 4, 0, 0, 0x7F, 0x40, 0);
            queue_fade();
            stage = BOOT_SETTINGS_STAGE_ENTER_SPEAKERS;
        }

        break;
    case BOOT_SETTINGS_STAGE_EXIT:
        clear_to_black();

        if (resident_find_resource_request(g_resource_queue, 0x29, 0, 0, -1, 0) != 0)
        {
            resident_cancel_resource_requests(g_resource_queue, 0x29, 0, 0, -1, 0);
        }

        for (s32 i = 0; i < 21; i++)
        {
            if (images[i] != 0)
            {
                lib_object_detach_owner(images[i]);
                images[i]->destroy();
                images[i] = 0;
            }
        }

        if (container != 0)
        {
            container->destroy();
            container = 0;
        }

        if (description_text != 0)
        {
            description_text->destroy();
            description_text = 0;
        }

        if (cursor != 0)
        {
            cursor->destroy();
            cursor = 0;
        }

        g_update_list->append_node(new (0) BootTitleMenu(BOOT_TITLE_ITEM_NEW_GAME), -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    case BOOT_SETTINGS_STAGE_NEXT_PAGE:
        if (++page > BOOT_SETTINGS_DIFFICULTY)
        {
            clear_to_black();
            resident_sound_stop_music(g_sound, 0x1E, -1);
            stage = BOOT_SETTINGS_STAGE_START_GAME;
        }
        else
        {
            load_option_value();
            float x;
            float y;
            get_cursor_position(&x, &y);
            place_cursor(cursor, x, y);
            show_value_message();
            stage = BOOT_SETTINGS_STAGE_PAGE;
        }

        break;
    case BOOT_SETTINGS_STAGE_PREVIOUS_PAGE:
    {
        page--;
        load_option_value();
        float x;
        float y;
        get_cursor_position(&x, &y);
        place_cursor(cursor, x, y);
        show_value_message();
        stage = BOOT_SETTINGS_STAGE_PAGE;
        break;
    }
    case BOOT_SETTINGS_STAGE_ENTER_SPEAKERS:
        on_speaker_setup = 1;
        description_text->destroy();
        description_text = 0;
        stage = BOOT_SETTINGS_STAGE_BUILD_SPEAKERS;

        for (s32 i = 2; i < 9; i++)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
            images[i] = 0;
        }

        images[15]->destroy();
        lib_object_detach_owner(images[15]);
        images[15] = 0;

        for (s32 i = 16; i < 20; i++)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
            images[i] = 0;
        }

        break;
    case BOOT_SETTINGS_STAGE_BUILD_SPEAKERS:
        if (loaded_model_blocks == 8)
        {
            resident_pad_set_stick_dpad(g_input_system, 0, 0);
            room_scene = new (0) BootScene;
            lib_scene_use_data(room_scene, (u8*)RESIDENT_ALIGN_RESOURCE(model_blocks[0]));
            func_474010(room_scene, g_boot_program.display, g_update_list, D_001B6624, g_display_manager, g_renderer, 1);
            girl_scene = new (0) BootScene;
            lib_scene_use_data(girl_scene, (u8*)RESIDENT_ALIGN_RESOURCE(model_blocks[1]));
            func_474010(girl_scene, g_boot_program.display, g_update_list, D_001B6624, g_display_manager, g_renderer, 1);
            s32 count = 0;

            for (BootClass170F30* model = lib_find_renderable_entry(girl_scene, g_empty_name); model != 0; model = lib_find_next_renderable_entry(girl_scene, model))
            {
                if (model->type_id == 0x100)
                {
                    girl_models[count] = new (0) BootClass170F30;
                    girl_models[count]->build_from(g_renderer, model);
                    girl_models[count++]->parent_transform = model->parent_transform;
                }
            }

            for (s32 i = 0; i < 6; i++)
            {
                girl_animations[i] = new (0) LibAnimation;
                girl_animations[i]->set_resource((void*)RESIDENT_ALIGN_RESOURCE(model_blocks[2 + i]));
                lib_animation_bind_channels(girl_animations[i], girl_scene, 0);
                animation_targets[i] = new (0) LibAnimationTarget;
                lib_animation_bind_state(girl_animations[i], animation_targets[i], g_bone_root_name);
                lib_animation_read_channel_pose(girl_animations[i], animation_targets[i]);
            }

            g_renderer->prepend_node(new (0) LibColorFade, -1);
            g_display_manager->current_display = static_cast<LibListObject*>(lib_find_camera_entry(room_scene, g_camera_node_name));
            girl_angle = 1.5707964f;
            animation_frame = 0.0f;
            turn_speed = 0.0f;
            walk_state = 0;
            girl_lean = 0.0f;
            blink_frame = 0;
            adjusting_speaker = 0;
            resident_sound_set_listener(g_sound, lib_find_transform_entry(room_scene, g_root_node_name), 0.0f, 500.0f);
            description_text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_SPEAKER_SETUP, 1, 32.0f, 352.0f, 576.0f, 112.0f);
            description_text->set_color(0x34130F);
            lib_container_attach_widget(container, description_text);
            place_girl();
            selected_speaker = 0;
            voice_count = 0;
            place_speakers();
            resident_sound_set_volume_scale(g_sound, 10000);
            stage++;
        }

        break;
    case BOOT_SETTINGS_STAGE_SHOW_SPEAKERS:
    {
        float x;
        float y;
        get_speaker_cursor_position(0, &x, &y);
        place_cursor(cursor, x, y);
        stage++;
        voice_line = 0;
        break;
    }
    case BOOT_SETTINGS_STAGE_SPEAKERS:
        if (input->repeated & (BOOT_BUTTON_DOWN | BOOT_BUTTON_LEFT))
        {
            if (adjusting_speaker == 0)
            {
                if (cursor->arrived)
                {
                    selected_speaker = (selected_speaker + 1) & 3;
                    float x;
                    float y;
                    get_speaker_cursor_position(selected_speaker, &x, &y);
                    cursor->set_move_target(x, y, 0.05f);
                    highlight_phase = 0;
                    resident_sound_play(g_sound, 0, 0, 0, 0x7F, 0x40, 0);
                }
            }
            else
            {
                float turned = speaker_angle(g_sound, selected_speaker);
                float angle = turned;
                turned += 1.5707964f * g_frame_seconds;

                if (turned >= 6.2831855f)
                {
                    turned -= 6.2831855f;
                }

                float upper = speaker_angle(g_sound, (selected_speaker + 1) & 3) - 0.2617994f;
                float lower = 0.2617994f + speaker_angle(g_sound, (selected_speaker - 1) & 3);

                if (angle < turned)
                {
                    if (selected_speaker == 0 && angle <= 1.3089969f && turned > 1.3089969f)
                    {
                        turned = 1.3089969f;
                    }

                    if (upper - angle >= -0.000001f && turned > upper)
                    {
                        turned = upper;
                    }

                    if (angle - lower >= -0.000001f && turned < lower)
                    {
                        turned = lower;
                    }
                }

                resident_sound_set_speaker_angle(g_sound, selected_speaker, turned);
                settings->speaker_angles[selected_speaker] = turned;
            }
        }

        if (input->repeated & (BOOT_BUTTON_UP | BOOT_BUTTON_RIGHT))
        {
            if (adjusting_speaker == 0)
            {
                if (cursor->arrived)
                {
                    selected_speaker = (selected_speaker + 3) & 3;
                    float x;
                    float y;
                    get_speaker_cursor_position(selected_speaker, &x, &y);
                    cursor->set_move_target(x, y, 0.05f);
                    resident_sound_play(g_sound, 0, 0, 0, 0x7F, 0x40, 0);
                }
            }
            else
            {
                float turned = speaker_angle(g_sound, selected_speaker);
                float angle = turned;
                turned -= 1.5707964f * g_frame_seconds;

                if (turned < 0.0f)
                {
                    turned += 6.2831855f;
                }

                float upper = speaker_angle(g_sound, (selected_speaker + 1) & 3) - 0.2617994f;
                float lower = 0.2617994f + speaker_angle(g_sound, (selected_speaker - 1) & 3);

                if (angle > turned)
                {
                    if (selected_speaker == 1 && angle >= 1.8325948f && turned < 1.8325957f)
                    {
                        turned = 1.8325957f;
                    }

                    if (upper - angle >= -0.000001f && turned > upper)
                    {
                        turned = upper;
                    }

                    if (angle - lower >= -0.000001f && turned < lower)
                    {
                        turned = lower;
                    }
                }

                resident_sound_set_speaker_angle(g_sound, selected_speaker, turned);
                settings->speaker_angles[selected_speaker] = turned;
            }
        }

        if (button_pressed(input, settings->alternate_buttons))
        {
            s32 line = resident_random_below(9);

            if (voice_count < 12)
            {
                voice_count++;
            }
            else
            {
                line += 9;
            }

            if (voice_line != 0)
            {
                resident_sound_stop(g_sound, voice_line, 0);
                voice_line = 0;
            }

            voice_line = resident_sound_play_voice(g_sound, g_voice_lines[line],
                                                   (ResidentSoundEmitter*)lib_find_transform_entry(girl_scene, g_root_node_name), 0, 0x7F, 0);
        }

        if (button_pressed(input, settings->confirm_buttons))
        {
            if (adjusting_speaker == 0)
            {
                resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                adjusting_speaker = 1;
                saved_speaker_angle = speaker_angle(g_sound, selected_speaker);
            }
            else
            {
                resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                adjusting_speaker = 0;
            }
        }

        if (button_pressed(input, settings->cancel_buttons))
        {
            if (adjusting_speaker == 0)
            {
                resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                queue_fade();
                stage = BOOT_SETTINGS_STAGE_LEAVE_SPEAKERS;
            }
            else
            {
                resident_sound_play(g_sound, 2, 0, 0, 0x7F, 0x40, 0);
                resident_sound_set_speaker_angle(g_sound, selected_speaker, saved_speaker_angle);
                settings->speaker_angles[selected_speaker] = saved_speaker_angle;
                adjusting_speaker = 0;
                place_speakers();
                float x;
                float y;
                get_speaker_cursor_position(selected_speaker, &x, &y);
                place_cursor(cursor, x, y);
            }
        }

        if ((input->pressed & 9) && adjusting_speaker == 0)
        {
            resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
            resident_sound_reset_speaker_angles(g_sound);
            place_speakers();

            for (s32 i = 0; i < 4; i++)
            {
                settings->speaker_angles[i] = speaker_angle(g_sound, i);
            }

            float x;
            float y;
            get_speaker_cursor_position(selected_speaker, &x, &y);
            place_cursor(cursor, x, y);
        }

        if (voice_line != 0)
        {
            BootClass170F30* face = lib_find_renderable_entry(girl_scene, g_face_model_name);
            LibListSentinel* end = &face->children.sentinel;
            LibListSentinel* node = end->next;

            if (resident_sound_is_active(g_sound, voice_line) != 0)
            {
                s32 shape;

                switch (resident_sound_get_voice_level(g_sound, voice_line, 2.0f))
                {
                case 0:
                    shape = -1;
                    break;
                case 1:
                    shape = 1;
                    break;
                case 2:
                    shape = 2;
                    break;
                case 3:
                    shape = 3;
                    break;
                case 4:
                    shape = 1;
                    break;
                case 5:
                    shape = 4;
                    break;
                case 6:
                    shape = -1;
                    break;
                case 7:
                    shape = -1;
                    break;
                }

                for (; !at_end(end, node); node = node->next)
                {
                    LibMorphTarget* target = (LibMorphTarget*)node;

                    if (target->object_kind == 2)
                    {
                        if (shape == target->shape->id)
                        {
                            lib_morph_target_set_weight(target, 100.0f);
                        }
                        else
                        {
                            lib_morph_target_set_weight(target, 0.0f);
                        }
                    }
                }
            }
            else
            {
                voice_line = 0;

                for (; !at_end(end, node); node = node->next)
                {
                    LibMorphTarget* target = (LibMorphTarget*)node;

                    if (target->object_kind == 2)
                    {
                        lib_morph_target_set_weight(target, 0.0f);
                    }
                }
            }
        }

        if (blink_frame == 0 && resident_rand() < 250)
        {
            blink_frame = 1;
        }

        if (blink_frame != 0)
        {
            BootClass170F30* face = lib_find_renderable_entry(girl_scene, g_face_model_name);
            LibListSentinel* end = &face->children.sentinel;
            LibListSentinel* node = end->next;
            blink_frame++;

            for (; !at_end(end, node); node = node->next)
            {
                LibMorphTarget* target = (LibMorphTarget*)node;

                if (target->object_kind == 2 && target->shape->id == 0)
                {
                    if (blink_frame < 5)
                    {
                        lib_morph_target_set_weight(target, 100.0f);
                    }
                    else
                    {
                        lib_morph_target_set_weight(target, 0.0f);
                        blink_frame = 0;
                    }

                    break;
                }
            }
        }

        {
            s32 first;
            s32 second;
            s32 turn;
            s32 fourth;
            resident_pad_get_sticks(g_input_system, 0, &first, &second, &turn, &fourth);
            turn_speed -= 0.01f * (float)turn;
            turn_speed = ee_max(turn_speed, -1.0f);
            turn_speed = ee_min(turn_speed, 1.0f);

            if (turn == 0)
            {
                if (turn_speed > 0.0f)
                {
                    turn_speed -= 0.1f;

                    if (turn_speed < 0.0f)
                    {
                        turn_speed = 0.0f;
                    }
                }
                else if (turn_speed < 0.0f)
                {
                    turn_speed += 0.1f;

                    if (turn_speed > 0.0f)
                    {
                        turn_speed = 0.0f;
                    }
                }
            }
        }

        girl_angle += 0.017453292f * (0.35f * turn_speed);

        if (girl_angle > 6.2831855f)
        {
            girl_angle -= 6.2831855f;
        }

        if (girl_angle < 0.0f)
        {
            girl_angle += 6.2831855f;
        }

        place_girl();
        place_speakers();

        if (adjusting_speaker != 0)
        {
            float x;
            float y;
            get_speaker_cursor_position(selected_speaker, &x, &y);
            place_cursor(cursor, x, y);
        }

        break;
    case BOOT_SETTINGS_STAGE_LEAVE_SPEAKERS:
    {
        resident_pad_set_stick_dpad(g_input_system, 0, 1);

        for (s32 i = 0; i < 6; i++)
        {
            if (girl_animations[i] != 0)
            {
                girl_animations[i]->destroy();
                girl_animations[i] = 0;
            }

            if (animation_targets[i] != 0)
            {
                animation_targets[i]->destroy();
                animation_targets[i] = 0;
            }
        }

        resident_sound_set_volume_scale(g_sound, 0x8000);
        room_scene->destroy();
        room_scene = 0;
        girl_scene->destroy();
        girl_scene = 0;
        shown_page = 0xFF;

        for (s32 i = 0; i < 10; i++)
        {
            if (girl_models[i] != 0)
            {
                lib_object_detach_owner(girl_models[i]);
                girl_models[i]->destroy();
                girl_models[i] = 0;
            }
        }

        g_boot_program.select_projection();
        description_text->destroy();
        description_text = new (0) LibTextWidget(g_boot_program.get_messages(), BOOT_MSG_TV_NORMAL, 1, 32.0f, 272.0f, 344.0f, 224.0f);
        description_text->set_color(0x34130F);
        lib_container_attach_widget(container, description_text);
        load_option_value();
        show_value_message();
        float x;
        float y;
        get_cursor_position(&x, &y);
        place_cursor(cursor, x, y);
        on_speaker_setup = 0;
        stage = BOOT_SETTINGS_STAGE_PAGE;
        break;
    }
    case BOOT_SETTINGS_STAGE_START_GAME:
        if (resident_find_resource_request(g_resource_queue, 0x29, 0, 0, -1, 0) != 0)
        {
            resident_cancel_resource_requests(g_resource_queue, 0x29, 0, 0, -1, 0);
        }

        settings->continue_selected = 0;
        g_update_list->append_node(new (0) BootGameLauncher, -1);
        lib_object_detach_owner(this);
        destroy();
        return;
    }

    if (stage > BOOT_SETTINGS_STAGE_LOAD && resident_find_resource_request(g_resource_queue, 0x29, 0, 0, -1, 0) == 0 && loaded_model_blocks < 8)
    {
        model_blocks[loaded_model_blocks] =
            resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(model_data), loaded_model_blocks, 1);
        resident_decode_resource_block(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(model_data),
                                       (void*)RESIDENT_ALIGN_RESOURCE(model_blocks[loaded_model_blocks]), loaded_model_blocks);
        loaded_model_blocks++;
        FlushCache(0);
    }

    if (rumble_frames != 0 && --rumble_frames == 0)
    {
        resident_pad_set_vibration(g_input_system, 0, 0, 0);
    }

    update_page_images();
    update_option_rows();
}

/** @brief Release the loaded data and owned objects. */
BootNewGameSettings::~BootNewGameSettings()
{
    delete image_data;
    delete model_data;

    for (s32 i = 0; i < 5; i++)
    {
        delete image_blocks[i];
    }

    for (s32 i = 0; i < 8; i++)
    {
        delete model_blocks[i];
    }

    for (s32 i = 0; i < 21; i++)
    {
        if (images[i] != 0)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
        }
    }

    for (s32 i = 0; i < 10; i++)
    {
        if (girl_models[i] != 0)
        {
            lib_object_detach_owner(girl_models[i]);
            girl_models[i]->destroy();
        }
    }

    for (s32 i = 0; i < 6; i++)
    {
        if (girl_animations[i] != 0)
        {
            girl_animations[i]->destroy();
        }

        if (animation_targets[i] != 0)
        {
            animation_targets[i]->destroy();
        }
    }

    if (room_scene != 0)
    {
        room_scene->destroy();
    }

    if (girl_scene != 0)
    {
        girl_scene->destroy();
    }

    if (container != 0)
    {
        container->destroy();
    }

    if (description_text != 0)
    {
        description_text->destroy();
    }

    if (cursor != 0)
    {
        cursor->destroy();
    }

    if (rumble_frames != 0)
    {
        resident_pad_set_vibration(g_input_system, 0, 0, 0);
    }

    g_floor_query = 0;
}

/** @brief Start loading the page images and the speaker setup scenes, and clear the owned objects. */
BootNewGameSettings::BootNewGameSettings()
{
    LibSystemSettings* resource;
    image_data = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_RES_SETTINGS_IMAGES));
    resident_queue_resource_request(g_resource_queue, BOOT_RES_SETTINGS_IMAGES, image_data,
                                    BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
    model_data = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_RES_SETTINGS_MODELS));
    stage = BOOT_SETTINGS_STAGE_LOAD;

    for (s32 i = 0; i < 5; i++)
    {
        image_blocks[i] = 0;
    }

    for (s32 i = 0; i < 21; i++)
    {
        images[i] = 0;
    }

    for (s32 i = 0; i < 8; i++)
    {
        model_blocks[i] = 0;
    }

    for (s32 i = 0; i < 6; i++)
    {
        girl_animations[i] = 0;
        animation_targets[i] = 0;
    }

    for (s32 i = 0; i < 10; i++)
    {
        girl_models[i] = 0;
    }

    container = 0;
    description_text = 0;
    cursor = 0;
    room_scene = 0;
    girl_scene = 0;
    on_speaker_setup = 0;
    rumble_frames = 0;
    g_floor_query = &flat_floor;
    page = 0;
    loaded_model_blocks = 0;
    resource = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    // The audio system reverses the mono and stereo codes used by the saved setting.
    switch (g_sound->output_mode)
    {
    case 1:
        resource->sound_output = LIB_SOUND_MONO;
        break;
    case 0:
        resource->sound_output = LIB_SOUND_STEREO;
        break;
    case 2:
        resource->sound_output = LIB_SOUND_DOLBY_PRO_LOGIC_II;
        break;
    case 3:
        resource->sound_output = LIB_SOUND_HEADPHONES;
        break;
    }
}

/**
 * @brief Negate the matrix's second vector, then apply the matrix through the Lib model.
 * @param matrix Matrix supplied by the caller.
 * @param context Opaque caller context.
 */
void BootClass170F30::build_packet(const void* matrix, void* context)
{
    LibVector4 negated[4];
    LibVector4* rows = reinterpret_cast<LibVector4*>(transform.m);
    LibVector4* vector1 = &negated[1];
    LibVector4* vector2 = &negated[2];
    LibVector4* vector3 = &negated[3];
    copy_vector(&negated[0], &rows[0]);
    copy_vector(vector1, &rows[1]);
    copy_vector(vector2, &rows[2]);
    copy_vector(vector3, &rows[3]);
    vector1->x *= -1.0f;
    vector1->y *= -1.0f;
    vector1->z *= -1.0f;
    vector1->w *= -1.0f;
    copy_vector(&rows[0], &negated[0]);
    copy_vector(&rows[1], vector1);
    copy_vector(&rows[2], vector2);
    copy_vector(&rows[3], vector3);
    transform_dirty = 1;
    LibModel::build_packet(matrix, context);
}

/** @brief Destroy the model object. */
BootClass170F30::~BootClass170F30()
{
}

/**
 * @brief Apply the source blend mode and copy its inherited transform state.
 * @param source Blend transform to copy.
 */
void LibBlendTransform::copy_blend_state(const LibBlendTransform* source)
{
    set_blend_mode(source->blend_mode);
    LibTransform::copy_offset_transform_state(source);
}

/**
 * @brief Read the cached combined transformation matrix.
 * @return Pointer to the stored matrix; this call does not update it.
 */
const LibMatrix44Value* LibTransform::get_transform_matrix()
{
    return &transform;
}

/**
 * @brief Read the additional local translation.
 * @return Stored translation vector; only xyz is used to build the offset matrix.
 */
const LibVector4* LibTransform::get_offset_translation() const
{
    return &offset_translation;
}

/**
 * @brief Read the additional local rotation.
 * @return Stored quaternion in x, y, z, w order.
 */
const LibVector4* LibTransform::get_offset_rotation() const
{
    return &offset_rotation;
}

/**
 * @brief Read the additional local scale.
 * @return Stored scale vector; only xyz is used to build the offset matrix.
 */
const LibVector4* LibTransform::get_offset_scale() const
{
    return &offset_scale;
}
