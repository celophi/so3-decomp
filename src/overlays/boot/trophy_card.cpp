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
