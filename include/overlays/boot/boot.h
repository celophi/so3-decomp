#ifndef SO3_OVERLAYS_BOOT_BOOT_H
#define SO3_OVERLAYS_BOOT_BOOT_H

#include "types.h"
#include "main/func_0011EE00.h"
#include "main/resident_00101260.h"
#include "main/resident_00101550.h"
#include "main/resident_0010A0E0.h"
#include "sdk/main/libc_guess_00137290.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/lib/text_003E68C0.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/render_buffer.h"
#include "overlays/lib/scene.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/image_capture.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/model.h"
#include "overlays/lib/text_0045AD10.h"
#include "main/resident_001001E0.h"
#include "overlays/lib/vector.h"
#include "overlays/lib/memory_card.h"
#include "overlays/lib/movie_player.h"
#include "sdk/main/libc_guess_0013C948.h"

class LibContainer;
class LibMoviePlayer;
struct ResidentInputSystem;

/** Resource IDs used by the boot program and its menus. */
enum BootScreenResourceId
{
    BOOT_RES_GAME_DATA = 0xA,
    BOOT_RES_COMMON_UI = 0x26,
    BOOT_RES_TITLE_SCENE = 0x27,
    BOOT_RES_SETTINGS_IMAGES = 0x28,
    BOOT_RES_SETTINGS_MODELS = 0x29,
    BOOT_RES_TROPHY_VIEWER = 0x2B,
    BOOT_RES_MUSIC_PLAYER = 0x2C
};

extern class LibClass179080* g_scene_camera;

extern FieldRuntime* g_field_runtime;

extern ResidentArchive* g_resource_archive;

extern ResidentResourceQueue* g_resource_queue;

extern ResidentReleaseQueues* g_resident_release_queues;

extern ResidentSound* g_sound;

/** Dark blue every boot menu screen draws its text in. */
#define BOOT_TEXT_COLOR 0x34130F

/** Menu sound effects boot plays through resident_sound_play. */
enum BootSound
{
    /** Cursor moved to another entry. */
    BOOT_SOUND_CURSOR = 0,

    /** Entry chosen. */
    BOOT_SOUND_CONFIRM = 1,

    /** Backed out of a screen. */
    BOOT_SOUND_CANCEL = 2,

    /** Entry can't be chosen yet, such as a locked difficulty. */
    BOOT_SOUND_INVALID = 3,

    /** Secondary button pressed, which opens the speaker setup. */
    BOOT_SOUND_ALTERNATE = 4,

    /** Warning or error message shown. */
    BOOT_SOUND_WARNING = 8
};

/** Arguments every boot resource load passes to the resident queue. */
enum BootResourceRequest
{
    /** Tag on every boot request; boot's lookups and cancels match any tag. */
    BOOT_RESOURCE_TAG = 1,

    /** Queue priority for boot's loads (lower runs first); 1067-00 queues its reads at the same priority. */
    BOOT_RESOURCE_PRIORITY = 0x34BC0,

    /** Plain read request; kinds two and three select the file by an offset instead. */
    BOOT_RESOURCE_READ = 1
};

/**
 * @brief Set or clear a selected bit in the resource's flag array.
 * @param bits Resource storage containing the flag array.
 * @param index Unsigned flag index.
 * @param enabled Nonzero to set the bit, or zero to clear it.
 */
static inline void set_resource_bit(LibTrophyFlags* bits, u32 index, s32 enabled)
{
    u32 byte_index = index / 8;
    u32 bit_index = index % 8;
    u8 mask;

    if (enabled)
    {
        mask = 1ULL << bit_index;
        bits->flags.bytes[byte_index] |= mask;
    }
    else
    {
        mask = ~(1ULL << bit_index);
        bits->flags.bytes[byte_index] &= mask;
    }
}


/** Title menu choices; auto-select picks Continue when a card holds a save. */
enum BootTitleItem
{
    BOOT_TITLE_ITEM_AUTO = -1,
    BOOT_TITLE_ITEM_NEW_GAME = 0,
    BOOT_TITLE_ITEM_CONTINUE = 1,
    BOOT_TITLE_ITEM_BATTLE_TROPHIES = 2,
    BOOT_TITLE_ITEM_INSTALL = 3
};

/** Message keys in boot's English message bank (resource 38, block 0). */
enum BootMessage
{
    BOOT_MSG_PROGRESSIVE_OFFER = 0x1,
    BOOT_MSG_PROGRESSIVE_WIDE_STARTED = 0x2,
    BOOT_MSG_PROGRESSIVE_NORMAL_STARTED = 0x7,
    BOOT_MSG_UNIT_NOT_INITIALIZED = 0x8,
    /** First of the descriptions for each page's options; see BootNewGameSettings::get_value_message. */
    BOOT_MSG_TV_NORMAL = 0xA,
    BOOT_MSG_SOUND_MONO = 0xC,
    BOOT_MSG_SPEAKER_SETUP = 0xF,
    BOOT_MSG_EVENT_SKIP_ON = 0x10,
    BOOT_MSG_VOICE_SUBTITLES_AND_SOUND = 0x12,
    BOOT_MSG_VIBRATION_ON = 0x15,
    BOOT_MSG_DIFFICULTY_EARTH = 0x17,
    BOOT_MSG_UNIVERSE_UNLOCKED = 0x1A,
    BOOT_MSG_SOUND_HEADPHONES = 0x1B,
    BOOT_MSG_VOICE_AUTO = 0x1C,
    BOOT_MSG_INSTALL_CONFIRM = 0x1E,
    BOOT_MSG_OVERWRITE_CONFIRM = 0x1F,
    BOOT_MSG_NOT_ENOUGH_SPACE = 0x20,
    BOOT_MSG_ERROR = 0x21,
    BOOT_MSG_UNIT_ERROR = 0x22,
    BOOT_MSG_INSTALLING = 0x23,
    BOOT_MSG_PERCENT = 0x24,
    BOOT_MSG_ABORT_CONFIRM = 0x25,
    BOOT_MSG_INSTALL_COMPLETE = 0x26,
    /** First of the eight battle-system tips shown while installing. */
    BOOT_MSG_FIRST_TIP = 0x28,
    BOOT_MSG_UNIT_FIX = 0x32,
    BOOT_MSG_UNIT_DATA_DELETED = 0x33,
    BOOT_MSG_FOURTH_DIMENSION_LOCKED = 0x50,
    BOOT_MSG_FOURTH_DIMENSION = 0x51,
    /** The memory card free-space warnings shown at startup. */
    BOOT_MSG_NO_CARD = 0x7D0,
    BOOT_MSG_SLOT1_FULL = 0x7D1,
    BOOT_MSG_SLOT2_FULL = 0x7D2,
    BOOT_MSG_BOTH_SLOTS_FULL = 0x7D3,
    BOOT_MSG_SLOT1_NO_TROPHY_SPACE = 0x7D5,
    BOOT_MSG_SLOT2_NO_TROPHY_SPACE = 0x7D6,
    BOOT_MSG_BOTH_SLOTS_NO_TROPHY_SPACE = 0x7D7,
    BOOT_MSG_SLOT1_NO_SAVE_SPACE = 0x7D8,
    BOOT_MSG_SLOT2_NO_SAVE_SPACE = 0x7D9,
    BOOT_MSG_BOTH_SLOTS_NO_SAVE_SPACE = 0x7DA
};

#define BOOT_TRANSFER_FLAG_COUNT LIB_TROPHY_COUNT

#define BOOT_TRANSFER_FLAG_BYTES ((BOOT_TRANSFER_FLAG_COUNT + 7) / 8)

#define BOOT_TROPHY_RECORD_BYTES (BOOT_TRANSFER_FLAG_COUNT * LIB_TROPHY_RECORD_SIZE)

#define BOOT_TROPHY_FILE_FLAGS_OFFSET 0x4B4

#define BOOT_TROPHY_FILE_RECORDS_OFFSET (BOOT_TROPHY_FILE_FLAGS_OFFSET + BOOT_TRANSFER_FLAG_BYTES + 8)

#define BOOT_TRANSFER_BUFFER_SIZE (BOOT_TROPHY_FILE_RECORDS_OFFSET + BOOT_TROPHY_RECORD_BYTES)

/** Button bits returned by the pad sampler and stored in BootInput. */
enum BootInputButton
{
    BOOT_BUTTON_START = 0x8,
    BOOT_BUTTON_UP = 0x10,
    BOOT_BUTTON_RIGHT = 0x20,
    BOOT_BUTTON_DOWN = 0x40,
    BOOT_BUTTON_LEFT = 0x80,
    BOOT_BUTTON_L1 = 0x400,
    BOOT_BUTTON_R1 = 0x800,
    BOOT_BUTTON_TRIANGLE = 0x1000,
    BOOT_BUTTON_CROSS = 0x4000
};

/** On-card trophy collection file, including the saved flags and all 300 trophy records. */
struct BootTrophyCardFile
{
    u8 trophy_key[4];
    u8 header[BOOT_TROPHY_FILE_FLAGS_OFFSET - 4];
    u8 trophy_flags[BOOT_TRANSFER_FLAG_BYTES];
    /** Saved checksum seed and checksum, stored without word alignment. */
    u8 checksum_words[8];
    u8 records[BOOT_TROPHY_RECORD_BYTES];
};

typedef char BootTrophyCardFileSizeCheck[sizeof(BootTrophyCardFile) == BOOT_TRANSFER_BUFFER_SIZE ? 1 : -1];

/** Card status values used to decide whether boot can save data or show a space warning. */
enum BootCardCapacityStatus
{
    BOOT_CARD_STATUS_NO_SPACE = 10,
    BOOT_CARD_STATUS_SAVE_SPACE_ONLY = 11,
    BOOT_CARD_STATUS_EITHER_FILE_ONLY = 12,
    BOOT_CARD_STATUS_SAVE_PRESENT_NO_TROPHY_SPACE = 13,
    BOOT_CARD_STATUS_TROPHY_PRESENT_NO_SAVE_SPACE = 14,
    BOOT_CARD_STATUS_UNAVAILABLE = 15,
    BOOT_CARD_STATUS_SAVE_PRESENT = 17
};

/** Results of probing the Battle Trophies collection file on a memory card. */
enum BootTrophyProbeEvent
{
    BOOT_TROPHY_FILE_PRESENT = 5,
    BOOT_TROPHY_FILE_MISSING = 6
};

/** Heap capacity and frame dimensions shared by the opening and launch movies. */
enum BootMovieConstants
{
    BOOT_MOVIE_HEAP_SIZE = 0x579F2C,
    BOOT_MOVIE_FRAME_WIDTH = 640,
    BOOT_MOVIE_FRAME_HEIGHT = 448
};

/** Resource and state limits used while boot runs and hands off to the main program. */
enum BootProgramConstants
{
    BOOT_PROGRAM_MAIN_CODE_RESOURCE = 3,
    BOOT_PROGRAM_MAIN_CODE_MAX_SIZE = 0x50000,
    BOOT_SAVED_WIDESCREEN_UNSET = 0xFF,
    BOOT_RANDOM_WARMUP_RANGE = 1000
};

extern ResidentInputSystem* g_input_system;

extern LibUpdateList* g_update_list;

#endif
