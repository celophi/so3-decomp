#include "include_asm.h"
#include "overlays/boot/title_menu.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/trophy_viewer.h"
#include "overlays/boot/music_player.h"
#include "overlays/boot/resident.h"
#include "overlays/lib/render_buffer.h"
#include "overlays/lib/text_004095C0.h"

extern "C" {

// Boot calls lib_draw_buffer_end through its own prototype, with a u8 mode.
void func_455BD0(LibDrawBuffer* buffer, u8 mode, float distance, s32 flag);
extern LibDisplayManager* g_scene_display_manager;

extern const char g_new_game_node_name[];
extern const char g_continue_node_name[];
extern const char g_battle_collection_node_name[];
extern const char g_install_node_name[];
extern const char g_title_camera_node_name[];
void lib_scene_load_data(BootScene* scene, ResidentResourceHeader* source);
void lib_scene_release_entries(BootScene* scene);

}

#include "overlays/boot/transform_inlines.h"

/** Steps between leaving the title and handing the next program to boot. */
enum BootLaunchStep
{
    BOOT_LAUNCH_PREPARE = 0,
    BOOT_LAUNCH_WAIT_TO_PLAY_MOVIE = 1,
    BOOT_LAUNCH_PLAY_MOVIE = 2,
    BOOT_LAUNCH_STOP_MOVIE = 3,
    BOOT_LAUNCH_RELEASE_MOVIE_HEAP = 4,
    BOOT_LAUNCH_LOAD_PROGRAM = 5,
    BOOT_LAUNCH_HAND_OFF = 6
};

enum BootLaunchConstants
{
    BOOT_LAUNCH_MOVIE_ID = 13,
    BOOT_LAUNCH_PROGRAM_RESOURCE = 0x42B,
    BOOT_LAUNCH_WORK_BUFFER_SIZE = 0x12000,
    BOOT_LAUNCH_MOVIE_START_DELAY_FRAMES = 60,
    BOOT_LAUNCH_HAND_OFF_DELAY_FRAMES = 40
};

/** @brief Run the launch steps: seed, movie, load, hand over. */
void BootGameLauncher::update()
{
    LibSystemSettings* settings;
    BootInput* input = g_boot_program.input;
    settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);
    u32 previous;

    switch (step)
    {
    case BOOT_LAUNCH_PREPARE:
        previous = resident_next_random_word();

        while (previous == resident_next_random_word())
        {
        }

        previous = resident_rand();

        while (previous == resident_rand())
        {
        }

        previous = resident_random_below(BOOT_RANDOM_WARMUP_RANGE);

        while (previous == resident_random_below(BOOT_RANDOM_WARMUP_RANGE))
        {
        }

        previous = resident_random_range(0, BOOT_RANDOM_WARMUP_RANGE);

        while (previous == resident_random_range(0, BOOT_RANDOM_WARMUP_RANGE))
        {
        }

        if ((u8)settings->continue_selected == 0)
        {
            LibSealedRecord* record = &settings->sealed_record;
            memset_guess(record, 0, sizeof(LibSealedRecord));
            seal_record(record);
            LibTrophyFlags* bits = &settings->trophy_flags;
            s32 size = bits->flags.size;

            for (s32 i = 0; i < size; i++)
            {
                bits->flags.bytes[i] = 0;
            }

            bits->trophy_key = resident_next_random_word();
            lib_trophy_flags_update_checksum(bits);
        }

        if ((u8)settings->continue_selected == 0 && settings->sound_output == LIB_SOUND_DOLBY_PRO_LOGIC_II)
        {
            step++;
            timer = 0;
        }
        else
        {
            step = BOOT_LAUNCH_LOAD_PROGRAM;
            timer = 0;
        }

        break;
    case BOOT_LAUNCH_WAIT_TO_PLAY_MOVIE:
        if (++timer > BOOT_LAUNCH_MOVIE_START_DELAY_FRAMES)
        {
            if (!resident_archive_has_unit_error(g_resource_archive) && resident_archive_is_unit_ready(g_resource_archive) != 0 && resident_archive_is_busy(g_resource_archive) != 0)
            {
                break;
            }

            movie_heap = new (0) ResidentHeap;
            movie_heap->alignment = 0x40;
            resident_heap_create_memory(movie_heap, BOOT_MOVIE_HEAP_SIZE);
            void* heap = resident_exchange_allocation_heap(movie_heap);
            player = new (0) LibMoviePlayer(BOOT_MOVIE_FRAME_WIDTH, BOOT_MOVIE_FRAME_HEIGHT);
            resident_exchange_allocation_heap(heap);
            player->state->set_scale(1.0f, 1.0f);
            player->state->set_words(0x800, 0x800, 1);

            if (((LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1))->widescreen)
            {
                player->state->unk80D8 = 1;
            }

            lib_movie_play(player, BOOT_LAUNCH_MOVIE_ID, 1);
            step++;
        }
        else if (input->held & BOOT_BUTTON_START)
        {
            step = BOOT_LAUNCH_LOAD_PROGRAM;
        }

        break;
    case BOOT_LAUNCH_PLAY_MOVIE:
        timer++;

        if ((input->held & BOOT_BUTTON_START) || !player->is_playing)
        {
            step++;
        }

        break;
    case BOOT_LAUNCH_STOP_MOVIE:
        lib_movie_stop(player);
        player->destroy();
        player = 0;
        step++;
        break;
    case BOOT_LAUNCH_RELEASE_MOVIE_HEAP:
        delete movie_heap;
        movie_heap = 0;
        step++;
        break;
    case BOOT_LAUNCH_LOAD_PROGRAM:
        program = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_LAUNCH_PROGRAM_RESOURCE));
        resident_queue_resource_request(g_resource_queue, BOOT_LAUNCH_PROGRAM_RESOURCE, program,
                                        BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
        step++;
        break;
    case BOOT_LAUNCH_HAND_OFF:
        if (resident_poll_resource_queue(g_resource_queue) != 0 && ++timer > BOOT_LAUNCH_HAND_OFF_DELAY_FRAMES)
        {
            lib_object_detach_owner(this);
            destroy();
            g_boot_program.next_program = program;
            return;
        }

        break;
    }
}

/**
 * @brief Encode a saved record and seal it with a fresh checksum; a damaged record is wiped instead.
 * @param record Record to seal; an already sealed record is left alone.
 */
void seal_record(LibSealedRecord* record)
{
    s32 i;

    if (record->sealed == 0)
    {
        record->sealed = LIB_RECORD_SEALED;
        record->unk00 ^= LIB_RECORD_XOR_BYTE;
        record->unk02 ^= LIB_RECORD_XOR_HALFWORD;
        record->unk04 ^= LIB_RECORD_XOR_WORD;
        record->unk08 ^= LIB_RECORD_XOR_WORD;
        record->unk0C ^= LIB_RECORD_XOR_WORD;
        record->unk10 ^= LIB_RECORD_XOR_WORD;
        record->unk14 ^= LIB_RECORD_XOR_WORD;
        record->unk18 ^= LIB_RECORD_XOR_WORD;
        record->unk1C ^= LIB_RECORD_XOR_WORD;
        record->unk20 ^= LIB_RECORD_XOR_WORD;
        record->unk24 ^= LIB_RECORD_XOR_WORD;
        record->unk28 ^= LIB_RECORD_XOR_WORD;
        record->unk2C ^= LIB_RECORD_XOR_WORD;
        record->unk30 ^= LIB_RECORD_XOR_WORD;
        record->unk34 ^= LIB_RECORD_XOR_WORD;
        record->unk38 ^= LIB_RECORD_XOR_WORD;
        record->unk3C ^= LIB_RECORD_XOR_WORD;
        record->unk40 ^= LIB_RECORD_XOR_WORD;
        record->unk44 ^= LIB_RECORD_XOR_WORD;
        record->unk48 ^= LIB_RECORD_XOR_WORD;
        record->unk4C ^= LIB_RECORD_XOR_WORD;
        record->unk50 ^= LIB_RECORD_XOR_WORD;
        record->unk54 ^= LIB_RECORD_XOR_WORD;
        record->unk58 ^= LIB_RECORD_XOR_WORD;

        for (i = 0; i < LIB_RECORD_ENCODED_TAIL_SIZE; i++)
        {
            record->encoded_tail[i] ^= LIB_RECORD_XOR_BYTE;
        }

        record->key = resident_next_random_word();
        record->checksum = lib_compute_checksum(record->key * LIB_RECORD_CHECKSUM_KEY_FACTOR, record, (u8*)&record->checksum - (u8*)record);
    }
    else if (record->sealed != LIB_RECORD_SEALED)
    {
        memset_guess(record, 0, sizeof(LibSealedRecord));
    }
}

/** @brief Release the player, its heap and the work buffer. */
BootGameLauncher::~BootGameLauncher()
{
    if (player != 0)
    {
        player->destroy();
    }

    delete movie_heap;
    delete buffer;
}

/** @brief Clear the state and allocate the 0x12000-byte work buffer. */
BootGameLauncher::BootGameLauncher()
{
    program = 0;
    step = BOOT_LAUNCH_PREPARE;
    buffer = (u8*)memalign(0x40, BOOT_LAUNCH_WORK_BUFFER_SIZE);
    movie_heap = 0;
    player = 0;
}
