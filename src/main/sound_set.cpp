#include "main/object_list.h"
#include "main/sound_set.h"
#include "main/system.h"
#include "main/utility.h"

#define SOUND_BANK_PICK_COST 300
#define SOUND_BANK_SECTOR_SHIFT 11

extern "C" {
extern const ResidentSoundBankVariants* g_sound_bank_variants;
extern ResidentObjectList* g_update_list;
}

typedef struct ResidentSoundBankSetState
{
    u8 pad00[0x24];
    u8 unk24;
    u8 unk25;
} ResidentSoundBankSetState;

/**
 * @brief Cancel the bank file reads and forget each slot's variant unless loads are in progress.
 * @param set Sound bank set.
 */
void resident_sound_bank_set_cancel(ResidentSoundBankSet* set)
{
    if (set->loading == 0)
    {
        resident_cancel_resource_requests(resident_system_get_resource_queue(resident_get_system()), 0, 0, 6, 0xFFFFFFFF, 0);
        set->variants[0] = -1;
        set->variants[1] = -1;
        set->variants[2] = -1;
        set->loading = 0;
        set->unk24 = 0;
    }
}

/**
 * @brief Move the set state from byte 0x25 to byte 0x24 when set.
 * @param object Object containing the state bytes.
 */
void resident_sound_bank_set_apply_pending(void* object)
{
    ResidentSoundBankSetState* receiver = (ResidentSoundBankSetState*)object;

    if (receiver->unk25 != 0)
    {
        receiver->unk25 = 0;
        receiver->unk24 = 1;
    }
}

/** Return the unsigned byte at receiver offset 0x25. */
u8 resident_sound_bank_set_get_pending(void* object)
{
    const ResidentSoundBankSetState* receiver = (const ResidentSoundBankSetState*)object;
    return receiver->unk25;
}

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
s32 resident_sound_bank_set_play_voice(void* object, s32 resource, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low)
{
    ResidentSound* sound = resident_system_get_sound(resident_get_system());

    if (emitter == 0)
    {
        return resident_sound_play_voice_resource(sound, resource, value, volume, 0x40, low);
    }

    return resident_sound_play_voice(sound, resource, emitter, value, volume, low);
}

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
s32 resident_sound_bank_set_play_data(void* object, u8* buffer, ResidentSoundEmitter* emitter, s32 value, s32 volume, s32 low, s32 owns_buffer)
{
    ResidentSound* sound = resident_system_get_sound(resident_get_system());

    if (emitter == 0)
    {
        return resident_sound_play_data(sound, buffer, value, volume, 0x40, low, owns_buffer);
    }

    return resident_sound_play_data_at(sound, buffer, emitter, value, volume, low, owns_buffer);
}

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
s32 resident_sound_bank_set_play(ResidentSoundBankSet* set, s32 slot, s32 id, ResidentSoundEmitter* emitter, s32 arg4, s32 arg5, s32 arg6)
{
    ResidentSound* sound;

    if (set->variants[slot] < 0)
    {
        return -1;
    }

    sound = resident_system_get_sound(resident_get_system());

    if (emitter == 0)
    {
        return resident_sound_play(sound, id, slot * 2 + 1, arg4, arg5, 0x40, arg6);
    }

    return resident_sound_play_at(sound, id, emitter, slot * 2 + 1, arg4, arg5, arg6);
}

/**
 * @brief Advance the bank loads by one step each frame while loads are in progress.
 */
void ResidentSoundBankSet::update()
{
    ResidentResourceQueue* queue;
    ResidentSound* sound;
    s32* data;
    u8* part;
    bool finished;

    if (loading == 0)
    {
        return;
    }

    queue = resident_system_get_resource_queue(resident_get_system());
    sound = resident_system_get_sound(resident_get_system());

    if (upload_lists == 0)
    {
        if (buffer == 0)
        {
            return;
        }

        switch (load_step)
        {
            case 0:
                if (load_index >= load_count)
                {
                    loading = 0;
                    delete buffer;
                    buffer = 0;
                    return;
                }

                resident_queue_resource_request(queue, loads[load_index].file_key, buffer, 6, 0x34BC0, 0,
                                                0, 0, 1);
                load_step = 1;
                break;

            case 1:
                if (resident_find_resource_request(queue, loads[load_index].file_key, (u32)buffer, 6,
                                                   0xFFFFFFFF, 0) != 0)
                {
                    break;
                }

                if (resident_sound_upload_file(sound, buffer, loads[load_index].slot * 2 + 1, 0) != 0)
                {
                    load_step = 2;
                }

                break;

            case 2:
                resident_sound_update(sound, 0);

                if (sound->state == 0)
                {
                    variants[loads[load_index].slot] = loads[load_index].variant;
                    load_step = 0;
                    load_index++;
                }

                break;
        }
    }
    else
    {
        finished = false;

        do
        {
            switch (load_step)
            {
                case 0:
                    for (;;)
                    {
                        if (lists[list_index][load_index] != 0)
                        {
                            break;
                        }

                        if (++load_index < RESIDENT_SOUND_BANK_LIST_COUNT)
                        {
                            continue;
                        }

                        first_part = 1;
                        load_index = 0;

                        if (++list_index < RESIDENT_SOUND_BANK_SLOT_COUNT)
                        {
                            continue;
                        }

                        finished = true;
                        break;
                    }

                    if (list_index >= RESIDENT_SOUND_BANK_SLOT_COUNT)
                    {
                        loading = 0;
                        return;
                    }

                    load_step = 1;
                    part_index = 0;
                    break;

                case 1:
                    data = lists[list_index][load_index];

                    if (part_index >= data[0])
                    {
                        load_step = 0;

                        if (++load_index >= RESIDENT_SOUND_BANK_LIST_COUNT)
                        {
                            first_part = 1;
                            list_index++;
                            load_index = 0;
                        }

                        break;
                    }

                    part = (u8*)data
                           + (((ResidentSoundBankPart*)(data + 1))[part_index].sector << SOUND_BANK_SECTOR_SHIFT);

                    if (resident_sound_upload_file(sound, part, list_index * 2 + 2, !first_part) != 0)
                    {
                        load_step = 2;
                        first_part = 0;
                        list_sizes[list_index] += resident_sound_file_get_word14(sound->stream, (const SoundFileHeader*)part);
                    }
                    else
                    {
                        finished = true;
                    }

                    break;

                case 2:
                    resident_sound_update(sound, 0);

                    if (sound->state == 0)
                    {
                        load_step = 1;
                        part_index++;
                    }
                    else
                    {
                        finished = true;
                    }

                    break;
            }
        } while (!finished);
    }
}

/**
 * @brief Start uploading the registered data lists unless loads are in progress.
 * @param set Sound bank set.
 */
void resident_sound_bank_set_upload(ResidentSoundBankSet* set)
{
    if (set->loading == 0)
    {
        set->load_index = 0;
        set->list_index = 0;
        set->loading = 1;
        set->upload_lists = 1;
        set->load_step = 0;
        set->first_part = 1;
    }
}

/**
 * @brief Register bank data in the first free entry of a list unless loads are in progress.
 * @param set Sound bank set.
 * @param list List to add to.
 * @param data Bank data.
 */
void resident_sound_bank_set_register(ResidentSoundBankSet* set, s32 list, s32* data)
{
    s32 index;

    if (set->loading == 0)
    {
        for (index = 0; index < RESIDENT_SOUND_BANK_LIST_COUNT; index++)
        {
            if (set->lists[list][index] == 0)
            {
                set->lists[list][index] = data;
                return;
            }
        }
    }
}

/**
 * @brief Clear every registered data list and its size unless loads are in progress.
 * @param set Sound bank set.
 */
void resident_sound_bank_set_clear_lists(ResidentSoundBankSet* set)
{
    s32 list;
    s32 index;

    if (set->loading == 0)
    {
        for (list = 0; list < RESIDENT_SOUND_BANK_SLOT_COUNT; list++)
        {
            set->list_sizes[list] = 0;

            for (index = 0; index < RESIDENT_SOUND_BANK_LIST_COUNT; index++)
            {
                set->lists[list][index] = 0;
            }
        }
    }
}

/**
 * @brief Queue a load of a randomly picked variant of a slot's bank.
 * @param set Sound bank set.
 * @param index Load to fill.
 * @param slot Slot the variant is for.
 */
static inline void pick_bank_variant(ResidentSoundBankSet* set, s32 index, s32 slot)
{
    s32 variant;

    set->loads[index].slot = slot;
    variant = resident_random_below(g_sound_bank_variants[set->banks[slot] - 1].count);
    set->loads[index].file_key = g_sound_bank_variants[set->banks[slot] - 1].file_keys[variant];
    set->loads[index].variant = variant;
}

/**
 * @brief Pick a variant for each assigned slot without one, then spend the rest of a budget re-picking random slots,
 *        and start loading the picks.
 * @param set Sound bank set.
 * @param budget Budget; each pick costs SOUND_BANK_PICK_COST.
 * @return One when loading started, or zero while loads are in progress, when the budget runs out or when the staging
 *         buffer can't be allocated.
 */
s32 resident_sound_bank_set_pick_variants(ResidentSoundBankSet* set, s32 budget)
{
    u8 picked[RESIDENT_SOUND_BANK_SLOT_COUNT];
    s32 count;
    s32 slot;
    s32 index;

    if (set->loading != 0)
    {
        return 0;
    }

    count = 0;

    for (slot = 0; slot < RESIDENT_SOUND_BANK_SLOT_COUNT; slot++)
    {
        if (set->banks[slot] != 0)
        {
            if (set->variants[slot] == -1)
            {
                pick_bank_variant(set, count, slot);
                picked[slot] = 1;
                count++;
                budget -= SOUND_BANK_PICK_COST;
            }
            else
            {
                picked[slot] = 0;
            }
        }
    }

    if (budget < 0)
    {
        return 0;
    }

    while (budget > SOUND_BANK_PICK_COST)
    {
        for (index = 0; index < RESIDENT_SOUND_BANK_SLOT_COUNT; index++)
        {
            if (!picked[index] && set->banks[index] != 0)
            {
                break;
            }
        }

        if (index == RESIDENT_SOUND_BANK_SLOT_COUNT)
        {
            break;
        }

        for (index = 0; index < 100; index++)
        {
            slot = resident_random_below(RESIDENT_SOUND_BANK_SLOT_COUNT);

            if (!picked[slot] && set->banks[slot] != 0)
            {
                break;
            }
        }

        if (picked[slot] || set->banks[slot] == 0)
        {
            break;
        }

        pick_bank_variant(set, count, slot);
        picked[slot] = 1;
        count++;
        budget -= SOUND_BANK_PICK_COST;
    }

    delete set->buffer;
    set->buffer = new (0) u8[0x21C00];

    if (set->buffer != 0)
    {
        set->load_count = count;
        set->load_index = 0;
        set->loading = 1;
        set->upload_lists = 0;
        set->load_step = 0;
        return 1;
    }

    return 0;
}

void resident_sound_bank_set_install_variants(const void* value)
{
    g_sound_bank_variants = (const ResidentSoundBankVariants*)value;
}

/**
 * @brief Get the budget picking a variant for every assigned slot without one would cost.
 * @param set Sound bank set.
 * @return The pick cost times the number of such slots.
 */
s32 resident_sound_bank_set_get_pick_cost(ResidentSoundBankSet* set)
{
    s32 cost = 0;
    s32 slot;

    for (slot = 0; slot < RESIDENT_SOUND_BANK_SLOT_COUNT; slot++)
    {
        if (set->banks[slot] != 0 && set->variants[slot] == -1)
        {
            cost += SOUND_BANK_PICK_COST;
        }
    }

    return cost;
}

/**
 * @brief Assign a bank to a slot unless loads are in progress, forgetting its variant when the bank changes.
 * @param set Sound bank set.
 * @param slot Slot to assign.
 * @param bank One-based bank number, or zero for none.
 * @return One when assigned, or zero while loads are in progress.
 */
s32 resident_sound_bank_set_assign(ResidentSoundBankSet* set, s32 slot, s32 bank)
{
    if (set->loading != 0)
    {
        return 0;
    }

    if (set->banks[slot] != bank)
    {
        set->variants[slot] = -1;
    }

    set->banks[slot] = bank;
    return 1;
}

/** @brief Detach the set and free its staging buffer. */
ResidentSoundBankSet::~ResidentSoundBankSet()
{
    lib_object_detach_owner(this);
    delete buffer;
}

/** @brief Construct an empty set with no banks assigned and register it with the update list. */
ResidentSoundBankSet::ResidentSoundBankSet() : buffer(0)
{
    s32 slot;

    buffer = 0;

    for (slot = 0; slot < RESIDENT_SOUND_BANK_SLOT_COUNT; slot++)
    {
        banks[slot] = 0;
        variants[slot] = -1;
    }

    loading = 0;
    unk24 = 0;
    g_update_list->append_node(this, -1);
}
