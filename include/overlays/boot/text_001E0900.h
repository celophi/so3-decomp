#ifndef SO3_OVERLAYS_BOOT_TEXT_001E0900_H
#define SO3_OVERLAYS_BOOT_TEXT_001E0900_H

#include "overlays/boot/text_001DD3C0.h"
#include "main/resident_001001E0.h"
#include "overlays/lib/vector.h"
#include "sdk/main/libc_guess_0013C948.h"

#define BOOT_TRANSFER_NAME_CAPACITY 64
/** Mask used to align memory card query buffers to 64 bytes. */
#define BOOT_CARD_QUERY_ALIGNMENT_MASK 0x3F
#define BOOT_ALIGN_CARD_QUERY(value) (((u32)(value) + BOOT_CARD_QUERY_ALIGNMENT_MASK) & ~BOOT_CARD_QUERY_ALIGNMENT_MASK)
#define BOOT_TRANSFER_FLAG_COUNT BOOT_TROPHY_COUNT
#define BOOT_TRANSFER_FLAG_BYTES ((BOOT_TRANSFER_FLAG_COUNT + 7) / 8)
#define BOOT_TROPHY_RECORD_SIZE 0xF10
#define BOOT_TROPHY_RECORD_BYTES (BOOT_TRANSFER_FLAG_COUNT * BOOT_TROPHY_RECORD_SIZE)
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

/** @brief Partial 0x100-byte record the memory card object keeps per slot. */
struct BootCardSlotState
{
    u8 unk00[0x48];

    /** Card state; two once the card is ready. */
    s32 card_state;

    /** Free space. */
    s32 free_space;

    /** Nonzero when the card is formatted. */
    s32 formatted;

    u8 unk54[0xAC];
};

/** Partial 0x58-byte Lib memory card object that runs the two transfer modes; boot calls the Lib constructor. */
class BootModeOwner0910 : public BootListObject
{
    public:
        /** @brief Initialize the memory card object. */
        BootModeOwner0910();

        /** The two card slots. */
        BootCardSlotState* slots;

        u8 unk18[8];

        /** Zero while the card object is busy. */
        u8 ready;

        u8 unk21[0x37];
};

enum BootCardSlotMask
{
    BOOT_CARD_SLOT_1 = 0x1,
    BOOT_CARD_SLOT_2 = 0x2
};

/** One file of a memory card request: Lib opens `<directory>/<name>` and transfers size bytes at data. */
struct BootCardFileBuffer
{
    char* name;
    void* data;
    u32 size;
    u32 unk0C;
};

/** Memory card request for files in one directory; Lib keeps a pointer to it in the slot until it finishes. */
struct BootCardFileRequest
{
    char* directory;
    s32 file_count;
    u32 unk08;
    BootCardFileBuffer* files;
};

/** Card checks and file probes performed before a Battle Trophy transfer. */
enum BootTrophyCardStep
{
    BOOT_TROPHY_CARD_UNINITIALIZED = -1,
    BOOT_TROPHY_CARD_IDLE = 0,
    BOOT_TROPHY_CARD_INSPECT_SLOT,
    BOOT_TROPHY_CARD_PROBE_SAVE,
    BOOT_TROPHY_CARD_WAIT_SAVE_PROBE,
    BOOT_TROPHY_CARD_PROBE_TROPHIES,
    BOOT_TROPHY_CARD_WAIT_TROPHY_PROBE,
    BOOT_TROPHY_CARD_TRANSFER = 8
};

/** Phases of a Battle Trophy memory card file request. */
enum BootTrophyTransferPhase
{
    BOOT_TROPHY_TRANSFER_INACTIVE = -1,
    BOOT_TROPHY_TRANSFER_OPEN,
    BOOT_TROPHY_TRANSFER_POLL
};

/** Free-space limits used when classifying memory card save and trophy capacity. */
enum BootCardFreeSpace
{
    BOOT_CARD_SAVE_SPACE_MINIMUM = 175,
    BOOT_CARD_TROPHY_SPACE_MINIMUM = 1200,
    BOOT_CARD_BOTH_SPACE_MINIMUM = BOOT_CARD_SAVE_SPACE_MINIMUM + BOOT_CARD_TROPHY_SPACE_MINIMUM,
    BOOT_CARD_MAX_EXPECTED_SPACE = 8000
};

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

/**
 * Battle Trophies memory card file (BASLUS-20488BTLCOL), with vtable D_170EB0 in main data. It reads and writes the
 * file through a Lib memory card object and reports each slot's free-space state for the startup checks. Mode 0
 * and mode 1 select the two card slots.
 */
class BootBattleTrophyCard : public BootListObject
{
    public:
        /** @brief Clear the transfer state, both modes, and the filename. */
        BootBattleTrophyCard();

        /** @brief Destroy the object. */
        virtual ~BootBattleTrophyCard()
        {
        }

        /**
         * @brief Report the list kind used when registration requests the default.
         * @return Two.
         */
        virtual s32 get_default_list_kind();

        /** @brief Release the transfer buffer and the memory card object, then queue this object for deletion. */
        virtual void destroy();

        /** @brief Advance the memory card state for the current mode. */
        virtual void update();

        /**
         * @brief Report which card slots hold a ready card.
         * @return Bit 0 for slot 1 and bit 1 for slot 2; zero while the card object is busy.
         */
        u16 get_ready_slots();

        /** @brief Apply transferred flags and header values, copy the payload, and release its buffer. */
        void finish_transfer();

        /**
         * @brief Return the last transfer's result.
         * @return Result code; negative on failure.
         */
        s32 get_transfer_result();

        /**
         * @brief Return the transfer state.
         * @return 1 once the transfer has finished, -1 while it runs or after a reset.
         */
        s16 get_transfer_state();

        /**
         * @brief Advance the stored two-phase request and update its completion state.
         * @return Narrowed request status, or -1 when the phase is unsupported.
         */
        s16 advance_transfer();

        /**
         * @brief Initialize the buffer and request records for a selected transfer mode.
         * @param mode Transfer mode 0 or 1.
         * @param destination Nonnull destination for the transfer.
         * @return 1 when prepared, or 0 for invalid arguments or allocation failure.
         */
        s32 start_transfer(u16 mode, void* destination);

        /**
         * @brief Store mode 1 or 2 and reset the state for selector 0.
         * @param mode Mode to store; values other than 1 or 2 have no effect.
         */
        void set_mode(u8 mode);

        /**
         * @brief Query a slot's state byte, resetting slot 0 when its reset flag is set.
         * @param mode Slot 0 or 1 to query; other values return zero without a reset.
         * @param kind Select guarded values with 1, or the direct mode byte otherwise.
         * @return The selected byte before any reset.
         */
        u16 get_slot_state(u16 mode, u16 kind);

        /**
         * @brief Apply an event to the selected mode and update its reset and completion flags.
         * @param enabled Process the event when this byte equals 1.
         * @param event Event code or direct byte status to store.
         * @param kind Classify the event with 1, or store its byte status with 2.
         */
        void handle_card_event(u8 enabled, u16 event, u16 kind);

        /**
         * @brief Select an event's byte status and update the current mode's stored status.
         * @param event Event code to classify.
         * @param result Byte receiving the selected status, initially cleared to zero.
         */
        void classify_card_event(u16 event, u8* result);

        /**
         * @brief Select a slot and reset its fields along with the shared state.
         * @param mode Slot 0 or 1 to select; other values reset only the shared state.
         */
        void reset_slot(s16 mode);

        /**
         * @brief Create the memory card object for both slots and prepare the transfer buffer.
         * @return 1 when initialized, or 0 when the card object, settings or buffer is unavailable.
         */
        s32 initialize();

        BootModeOwner0910* card;

        /** Selected slot, or -1. */
        s16 slot;

        /** Card status last read for the selected slot; a change restarts card_step. */
        s16 last_card_status;

        /** Step of update()'s card state machine; 0 is idle, 8 runs the transfer. */
        s16 card_step;

        /** Skip polling the selected card while a slot result awaits consumption. */
        u8 card_poll_paused;
        u8 unk1F;

        /** Copy of the slot's formatted flag from the last check. */
        u32 card_formatted;

        s32 free_space;
        /** Reset slot 0 after a caller reads a pending slot result. */
        u8 pending_slot_reset;
        u8 slot1_status_valid;
        u8 slot2_status_valid;
        u8 slot1_status;
        u8 slot2_status;

        /** Set when the slot had under 175 units free. */
        u8 low_space;

        char filename[BOOT_TRANSFER_NAME_CAPACITY];
        /** Backing storage for the general save-file card query. */
        u8 save_file_probe_storage[0xCC0];

        /** 64-byte-aligned pointer into save_file_probe_storage. */
        u8* save_file_probe_buffer;
        u8 card_mode;
        /** Whether each direct mode status has been set. */
        u8 mode_status_valid[2];

        /** Direct status returned by get_slot_state for each mode. */
        u8 mode_status[2];
        /** Backing storage for the Battle Trophies file query. */
        u8 trophy_file_probe_storage[0x80];

        /** 64-byte-aligned pointer into trophy_file_probe_storage. */
        u8* trophy_file_probe_buffer;
        s16 transfer_phase;
        u8* transfer_buffer;
        void* transfer_destination;
        s16 transfer_slot;

        /** 1 once the transfer has finished, -1 while it runs or after a reset. */
        s16 transfer_state;

        s32 transfer_result;
        BootCardFileBuffer file_buffer;
        BootCardFileRequest file_request;
        BootSystemSettings* settings;

        /** Set by start_transfer until the transfer finishes or fails. */
        u8 transfer_pending;

        /** Set once the card file has been opened for the transfer. */
        u8 transfer_open;

        s32 slot_free_space[2];
        /** Save-file probe status used when classifying each slot. */
        s32 save_probe_status[2];
};

/** Startup screens BootStartupChecks runs in turn. */
enum BootStartupScreen
{
    /** Warns when neither memory card has room for a save and the Battle Trophies. */
    BOOT_STARTUP_CARD_CHECK,
    /** Offers progressive display when its button combination is held. */
    BOOT_STARTUP_PROGRESSIVE,
    /** Reports an uninitialized PlayStation BB Unit or damaged data on it. */
    BOOT_STARTUP_UNIT_CHECK
};

/** Steps used while checking memory card space. */
enum BootStartupCardStep
{
    BOOT_STARTUP_CARD_INSPECT,
    BOOT_STARTUP_CARD_SHOW_WARNING,
    BOOT_STARTUP_CARD_WAIT_FOR_INPUT
};

/** Steps of the optional progressive display setup. */
enum BootStartupProgressiveStep
{
    BOOT_STARTUP_PROGRESSIVE_DETECT,
    BOOT_STARTUP_PROGRESSIVE_LOAD_OFFER,
    BOOT_STARTUP_PROGRESSIVE_OFFER,
    BOOT_STARTUP_PROGRESSIVE_SWITCH_DELAY,
    BOOT_STARTUP_PROGRESSIVE_SWITCH_WAIT,
    BOOT_STARTUP_PROGRESSIVE_CONFIRM,
    BOOT_STARTUP_PROGRESSIVE_REVERT_DELAY,
    BOOT_STARTUP_PROGRESSIVE_REVERT_WAIT
};

/** Steps used to report PlayStation BB Unit status. */
enum BootStartupUnitStep
{
    BOOT_STARTUP_UNIT_INSPECT,
    BOOT_STARTUP_UNIT_LOAD_WARNING,
    BOOT_STARTUP_UNIT_WAIT_FOR_INPUT,
    BOOT_STARTUP_UNIT_LOAD_DELETED_WARNING
};

/**
 * Screens shown before the opening movie, with vtable D_170ED0 in main data: the memory card space warning,
 * the progressive display offer and the PlayStation BB Unit status. Every step checks the main executable.
 */
class BootStartupChecks : public BootListObject
{
    public:
        /** @brief Start on the memory card check. */
        BootStartupChecks();

        /** @brief Destroy the object. */
        virtual ~BootStartupChecks();

        /** @brief Run the memory card, progressive display and BB Unit screens in turn, then start the opening movie. */
        virtual void update();

        s32 step;

        /** Frames spent in the current step. */
        s32 frames;

        s32 screen;

        /** Memory card warning being shown. */
        s32 message;

        u8 unk24[8];

        /** Slot 1 state the warning was chosen for; it closes if either slot changes. */
        s32 shown_slot1;

        /** Slot 2 state the warning was chosen for. */
        s32 shown_slot2;

        BootContainer* container;
        BootTextWidget* text;
};

/**
 * Floor height lookup, with vtable D_170F20 in main data. Lib (0x4C8860) calls the one in g_floor_query with a
 * model's position and uses the result as the offset of a horizontal plane it keeps for the object. The field
 * installs one of its own objects; the new-game settings screen installs a BootFlatFloor.
 */
class BootFloorQuery
{
    public:
        /**
         * @brief Return the floor height under a position; Lib passes the position and the object.
         * @return Floor height.
         */
        virtual float get_floor_height() = 0;
};

/** Flat floor at height zero, with vtable D_170F10 in main data. */
class BootFlatFloor : public BootFloorQuery
{
    public:
        /**
         * @brief Return the floor height, which is zero everywhere.
         * @return Zero.
         */
        virtual float get_floor_height()
        {
            return 0.0f;
        }
};

extern "C" void lib_animation_release_channels(class BootAnimation* animation);

/** Partial 0x70-byte Lib animation with vtable D_178220 in main data; boot calls the Lib constructor. */
class BootAnimation : public BootListObject
{
    public:
        /** @brief Construct an empty animation. */
        BootAnimation();

        /**
         * @brief Release the current channels and resource, then play from borrowed data.
         * @param data Animation data the caller keeps.
         */
        void set_resource(void* data)
        {
            if (entries)
            {
                lib_animation_release_channels(this);
                delete[] entries;
            }

            targets_bound = 0;

            if (!resource_is_borrowed)
            {
                operator delete(resource_data);
            }

            resource_is_borrowed = 1;
            resource_data = data;
        }

        u8 unk14[0x1C];
        void* resource_data;
        u8 unk34[0xC];
        u8* entries;
        u8 unk44[0x24];
        u8 resource_is_borrowed;
        u8 unk69;

        /** Cleared to restart the animation from its first frame. */
        u8 unk6A;

        u8 unk6B[3];
        u8 targets_bound;
        u8 unk6F;
};

/** Partial 0xD0-byte Lib animation target with vtable D_178370 in main data; boot calls the Lib constructor. */
class BootAnimationTarget : public BootListObject
{
    public:
        /** @brief Construct an empty target. */
        BootAnimationTarget();

        u8 unk14[0xBC];
};

/** Partial 0xB0-byte Lib scene with vtable D_175320 in main data; boot calls the Lib constructor. */
class BootScene : public BootListObject
{
    public:
        /** @brief Construct an empty scene. */
        BootScene();

        u8 unk14[0x9C];
};

/** Pages of the new-game settings, in the order the player sees them. */
enum BootSettingsPage
{
    BOOT_SETTINGS_TV_MODE,
    BOOT_SETTINGS_SOUND,
    BOOT_SETTINGS_EVENT_SKIP,
    BOOT_SETTINGS_VOICE,
    BOOT_SETTINGS_VIBRATION,
    BOOT_SETTINGS_DIFFICULTY
};

/** Stages of BootNewGameSettings::update. */
enum BootSettingsStage
{
    BOOT_SETTINGS_STAGE_LOAD,
    BOOT_SETTINGS_STAGE_LOAD_IMAGES,
    BOOT_SETTINGS_STAGE_PAGE,
    BOOT_SETTINGS_STAGE_EXIT,
    BOOT_SETTINGS_STAGE_NEXT_PAGE,
    BOOT_SETTINGS_STAGE_PREVIOUS_PAGE,
    BOOT_SETTINGS_STAGE_ENTER_SPEAKERS,
    BOOT_SETTINGS_STAGE_BUILD_SPEAKERS,
    BOOT_SETTINGS_STAGE_SHOW_SPEAKERS,
    BOOT_SETTINGS_STAGE_SPEAKERS,
    BOOT_SETTINGS_STAGE_LEAVE_SPEAKERS,
    BOOT_SETTINGS_STAGE_START_GAME
};

/**
 * New-game settings screens, with vtable D_170EF0 in main data. The player steps through six pages (TV mode,
 * sound output, event skip, voice playback, vibration, difficulty), with a speaker setup scene behind the sound
 * page, then the game starts. Cancelling on the first page goes back to the title.
 */
class BootNewGameSettings : public BootListObject
{
    public:
        /** @brief Start loading the page images and the speaker setup scenes, and clear the owned objects. */
        BootNewGameSettings();

        /** @brief Release the loaded data and owned objects. */
        virtual ~BootNewGameSettings();

        /**
         * @brief Report the list kind used when registration requests the default.
         * @return Four.
         */
        virtual s32 get_default_list_kind();

        /** @brief Run the current page or the speaker setup, then stream the next model block and place the rows. */
        virtual void update();

        /** @brief Select the option that matches the current page's saved setting. */
        void load_option_value();

        /** @brief Save the selected option for the current page and apply it to the display, sound or pad. */
        void apply_option_value();

        /**
         * @brief Pick the message that describes the selected option.
         * @return Message key, or zero for an unknown page.
         */
        s32 get_value_message();

        /** @brief Show the message that describes the selected option. */
        void show_value_message();

        /**
         * @brief Read the cursor position for the selected row of the current page.
         * @param x Receives the horizontal position.
         * @param y Receives the vertical position; unchanged for an unknown row.
         */
        void get_cursor_position(float* x, float* y);

        /** @brief Rebuild the current page's option rows when the page changes, then place and highlight them. */
        void update_option_rows();

        /** @brief Move the girl to her angle around the listener with her lean, then step her walk animations. */
        void place_girl();

        /**
         * @brief Read the cursor position for a speaker on the speaker setup screen.
         * @param speaker Speaker index.
         * @param x Receives the horizontal position.
         * @param y Receives the vertical position.
         */
        void get_speaker_cursor_position(s32 speaker, float* x, float* y);

        /** @brief Place the five speaker models around the listener and pulse the one being moved. */
        void place_speakers();

        /** @brief Create the page's images once their textures are loaded, then place and highlight them. */
        void update_page_images();

        /** Resource 0x28: the page images. */
        u8* image_data;

        /** Decoded blocks of image_data. */
        u8* image_blocks[5];

        /** Resource 0x29: the speaker room, the girl and her six walk animations. */
        u8* model_data;

        /** Decoded blocks of model_data. */
        u8* model_blocks[8];

        s32 stage;

        /** The girl's angle around the listener in the middle. */
        float girl_angle;

        /** Turn from the analog stick, eased back to zero when released. */
        float turn_speed;

        /** Frame within the current walk animation. */
        float animation_frame;

        /** The girl's lean into the turn. */
        float girl_lean;

        /** Angle of the speaker being moved, restored on cancel. */
        float saved_speaker_angle;

        u8 page;

        /** Page the option rows were last built for, or 0xFF to rebuild them. */
        u8 shown_page;

        u8 selection;
        u8 loaded_image_blocks;

        /** Highlight pulse on the selected row: zero darkening, one brightening. */
        u8 highlight_phase;

        /** Nonzero while the speaker setup scene replaces the option rows. */
        u8 on_speaker_setup;

        u8 loaded_model_blocks;
        u8 selected_speaker;
        u8 walk_state;

        /** Voice lines played so far; after twelve the later lines are used. */
        u8 voice_count;

        /** Nonzero while the selected speaker is being moved: one while its pulse grows, two while it shrinks. */
        u8 adjusting_speaker;

        u8 unk73;

        /** Voice line the girl's face lip-syncs to, or zero. */
        s32 voice_line;

        /** Blink frame counter, zero while her eyes are open. */
        s32 blink_frame;

        /** Frames left of the vibration that confirms turning it on. */
        s32 rumble_frames;

        /** Horizontal position of the current page's rows. */
        float row_x;

        BootImage* images[21];
        BootScene* room_scene;
        BootScene* girl_scene;
        BootClass170F30* girl_models[10];

        /** Walk animations, one per walk_state. */
        BootAnimation* girl_animations[6];

        BootAnimationTarget* animation_targets[6];

        /** Installed in g_floor_query while the screen runs, so Lib sees a floor at height zero. */
        BootFlatFloor flat_floor;

        BootContainer* container;

        /** Description of the selected option. */
        BootTextWidget* description_text;

        BootSelectionCursor* cursor;
};

/** Boot's pad and memory card monitor, with vtable D_171030 in main data; samples both every frame. */
class BootInput : public BootListObject
{
    public:
        /** @brief Clear the card states and start querying the cards. */
        BootInput();

        /** @brief Destroy the object. */
        virtual ~BootInput()
        {
        }

        /** @brief Sample the first pad, then keep the latest nonzero state of each memory card slot. */
        virtual void update();

        /**
         * @brief Virtual slot 0x1C; nothing in boot, main or Lib calls it, so its purpose is unknown.
         * @return Zero.
         */
        virtual s32 func_slot1c();

        /** @brief Forget the memory card states so the next query starts fresh. */
        void clear_card_states();

        u8 card_query_enabled;
        u8 unk15;

        /** Buttons held down. */
        u16 held;

        /** Buttons pressed this frame. */
        u16 pressed;

        /** Buttons held at any point since the pad state was last cleared. */
        u16 held_any;

        /** Buttons pressed this frame or auto-repeating. */
        u16 repeated;

        u8 unk1E[2];

        /** Last nonzero state of card slot 1, as BootStartupChecks compares them. */
        u32 slot1_state;

        /** Last nonzero state of card slot 2. */
        u32 slot2_state;

        /** Last nonzero raw status byte of card slot 1 (get_slot_state kind 2). */
        u32 slot1_raw_state;

        /** Last nonzero raw status byte of card slot 2. */
        u32 slot2_raw_state;

        /** Nonzero while the card in slot 1 is ready. */
        s32 slot1_ready;

        /** Nonzero while the card in slot 2 is ready. */
        s32 slot2_ready;
};

/** Partial 0x58-byte resident object whose vtable pointer follows its data; boot calls the resident constructor. */
class BootResident113E40
{
    public:
        /** @brief Initialize the object. */
        BootResident113E40();

        u8 unk00[0x2C];
        s32 unk2C;
        u8 unk30[0x24];

        /** @brief Destroy the object. */
        virtual ~BootResident113E40();
};

/** Partial movie decoder state reached through the player. */
struct BootMovieState15E700
{
    /**
     * @brief Store the two scale words at offset 0x80C4.
     * @param first First scale.
     * @param second Second scale.
     */
    void set_scale(float first, float second)
    {
        unk80C4 = first;
        unk80C8 = second;
    }

    /**
     * @brief Store the three words at offset 0x80AC.
     * @param first First word.
     * @param second Second word.
     * @param third Third word.
     */
    void set_words(s32 first, s32 second, s32 third)
    {
        unk80AC = first;
        unk80B0 = second;
        unk80B4 = third;
    }

    u8 unk00[0x80AC];
    s32 unk80AC;
    s32 unk80B0;
    s32 unk80B4;
    u8 unk80B8[8];

    /** Frame being shown. */
    s32 current_frame;

    float unk80C4;
    float unk80C8;
    u8 unk80CC[0xC];
    u8 unk80D8;
};

/** Heap capacity and frame dimensions shared by the opening and launch movies. */
enum BootMovieConstants
{
    BOOT_MOVIE_HEAP_SIZE = 0x579F2C,
    BOOT_MOVIE_FRAME_WIDTH = 640,
    BOOT_MOVIE_FRAME_HEIGHT = 448
};

/** Partial 0x15E7C0-byte Lib movie player with vtable D_172500 in main data; boot calls the Lib constructor. */
class BootMoviePlayer : public BootListObject
{
    public:
        /**
         * @brief Initialize the player and its decoder for a frame size.
         * @param width Frame width.
         * @param height Frame height.
         */
        BootMoviePlayer(s32 width, s32 height);

        /** @brief Destroy the player. */
        virtual ~BootMoviePlayer();

        u8 unk14[0x15E6EC];
        BootMovieState15E700* state;
        u8 unk15E704[0x90];

        /** Nonzero while the movie plays. */
        u8 is_playing;

        u8 unk15E795[0x2B];
};

/** Steps of the opening movie, from loading its images through opening the title menu. */
enum BootOpeningMovieStep
{
    BOOT_MOVIE_PREPARE,
    BOOT_MOVIE_CAPTIONS,
    BOOT_MOVIE_WAIT_FOR_END,
    BOOT_MOVIE_STOP,
    BOOT_MOVIE_OPEN_TITLE
};

/** Visibility phases of an opening movie caption. */
enum BootCaptionPhase
{
    BOOT_CAPTION_HIDDEN,
    BOOT_CAPTION_FADE_IN,
    BOOT_CAPTION_SHOWN,
    BOOT_CAPTION_FADE_OUT
};

/** The opening movie with its timed captions, with vtable D_171050 in main data; Start skips it. */
class BootOpeningMovie : public BootListObject
{
    public:
        /** @brief Create the movie player in its own heap, set up for 4:3 or widescreen. */
        BootOpeningMovie();

        /** @brief Release the caption objects, the player and its heap. */
        virtual ~BootOpeningMovie();

        /** @brief Play the opening movie with its timed captions until it ends or the player skips it. */
        virtual void update();

        /** Step: start, captions, wait for the end, stop, hand over. */
        s32 step;

        /** Caption being shown. */
        s32 caption;

        /** Caption phase: zero none, one fading in, two shown, three fading out. */
        s32 caption_phase;

        /** Nonzero once the caption image exists. */
        u8 caption_image_loaded;

        u8 unk21[3];
        BootResident113E40* movie_heap;
        BootMoviePlayer* player;
        BootImage* caption_image;
        BootContainer* container;
        BootTextWidget* caption_text;
};

/** Blocks decoded from the boot program's common UI resource. */
enum BootCommonUiBlock
{
    BOOT_COMMON_UI_MESSAGES,
    BOOT_COMMON_UI_CAPTIONS,
    BOOT_COMMON_UI_IMAGES,
    BOOT_COMMON_UI_BLOCK_COUNT
};

/** Partial 0x20-byte boot object with vtable D_171090 in main data. */
class BootResourceLoader : public BootListObject
{
    public:
        /**
         * @brief Start loading the program's resource 0x26.
         * @param owner Program that receives the decoded blocks.
         */
        BootResourceLoader(class BootProgram* owner)
        {
            data = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_RES_COMMON_UI));
            resident_queue_resource_request(g_resource_queue, BOOT_RES_COMMON_UI, data, BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
            program = owner;
            block = BOOT_COMMON_UI_MESSAGES;
        }

        /** @brief Destroy the object. */
        virtual ~BootResourceLoader();

        /** @brief Decode the next of the program's three resource blocks, then destroy this object after the last. */
        virtual void update();

        class BootProgram* program;

        /** Loaded resource whose blocks are decoded. */
        u8* data;

        /** Next block to decode. */
        s32 block;
};

/** Resident program object base, with vtable D_14F9F0 in main data; the constructor registers the object. */
class BootResidentProgram
{
    public:
        /** @brief Register the object as the running program. */
        BootResidentProgram();

        /** @brief Run the program; the base implementation is resident. */
        virtual void run();
};

/** Opaque resident input root queried by slot. */
struct ResidentInputSystem;

/** Resource and state limits used while boot runs and hands off to the main program. */
enum BootProgramConstants
{
    BOOT_PROGRAM_MAIN_CODE_RESOURCE = 3,
    BOOT_PROGRAM_MAIN_CODE_MAX_SIZE = 0x50000,
    BOOT_SAVED_WIDESCREEN_UNSET = 0xFF,
    BOOT_RANDOM_WARMUP_RANGE = 1000
};

/**
 * The boot program, g_boot_program, with vtable D_1710B0 in main data. It owns the display, the pad monitor and
 * resource 0x26 (messages, captions and images), and runs the boot screens until one asks to exit.
 */
class BootProgram : public BootResidentProgram
{
    public:
        /** @brief Register the program and start with nothing loaded or created. */
        BootProgram()
        {
            projection = 0;
            input = 0;
            message_block = 0;
            display = 0;
            image_block = 0;
            trophy_card = 0;
            caption_block = 0;
            unk2C = 0;
            next_program = 0;
            error_popup = 0;
            image = 0;
            messages = 0;
            captions = 0;
            unit_data_deleted = 0;
        }

        /** @brief Run the boot program. */
        virtual void run();

        /** @brief Release the program's objects, resources, and buffers. */
        virtual ~BootProgram();

        /** @brief Make the boot projection the display manager's current display. */
        void select_projection();

        /** @brief Set the projections' aspect and field of view for the 4:3 or widescreen setting. */
        void update_projection_aspect();

        /**
         * @brief Replace the display and, on a full rebuild, the scratch heap.
         * @param full Nonzero to also recreate the scratch heap and rebind the display.
         */
        void rebuild_display(u8 full);

        /**
         * @brief Switch progressive output on or off, then rebuild the display and rebind it everywhere.
         * @param progressive Nonzero for progressive (525p) output.
         */
        void set_progressive(u8 progressive);

        /** @brief Fill the track pools, then create and register the projection. */
        void create_pools_and_projection();

        /** @brief Release the track pools and every object, resource and buffer the program owns. */
        void release_resources();

        /**
         * @brief Read the message bank handle.
         * @return Bank handle.
         */
        s32 get_messages() const
        {
            return messages;
        }

        /**
         * @brief Read the pad and memory card monitor.
         * @return Monitor.
         */
        BootInput* get_input() const
        {
            return input;
        }

        BootDimensionsACD0* display;
        BootProjectionACD0* projection;
        BootInput* input;

        /** Resource 0x26's first block, holding the message bank. */
        u8* message_block;

        /** Boot's message bank. */
        s32 messages;

        /** Resource 0x26's second block, holding the caption bank. */
        u8* caption_block;

        /** The opening movie's caption bank. */
        s32 captions;

        /** Resource 0x26's third block, holding the images. */
        u8* image_block;

        BootBattleTrophyCard* trophy_card;
        BootUnitErrorPopup* error_popup;
        s32 unk2C;

        /** Program to run next, set when the boot program should end; passed on to the resident runtime. */
        u8* next_program;

        /** Widescreen setting kept across the display reset, or 0xFF when there were no saved settings. */
        u8 saved_widescreen;

        u8 unk35[3];

        /** Frame counter. */
        s32 frame;

        /** Nonzero when damaged game data on the PlayStation BB Unit was deleted. */
        u8 unit_data_deleted;

        u8 unk3D[3];

        /** Resource 3: the program image, holding a copy of the main executable's code. */
        BootProgramImage* image;
};

/** Partial resident object D_001B6658 that holds the current display. */
struct BootResidentDisplay
{
    u8 unk00[4];
    BootDimensionsACD0* display;
};

/** 0x2910-byte Lib heap that may sit at the start of scratchpad memory. */
class BootScratchHeap
{
    public:
        /**
         * @brief Create the heap.
         * @param size Heap size in bytes.
         * @param count Block count.
         */
        BootScratchHeap(s32 size, s32 count);

        /**
         * @brief Allocate the heap object through the resident allocator.
         * @param size Object size in bytes.
         * @param heap Heap selector.
         * @return The allocated storage.
         */
        static void* operator new(u32 size, s32 heap)
        {
            return ::operator new(size, heap);
        }

        /**
         * @brief Release the storage when construction fails, unless it is the scratchpad.
         * @param object Storage to release.
         * @param heap Heap selector passed to operator new.
         */
        static void operator delete(void* object, s32 heap)
        {
            if (object != (void*)0x70000000)
            {
                ::operator delete(object);
            }
        }

        u8 unk00[0x2910];
};

/** How a track evaluates keys outside its first and last keyframes. */
enum BootTrackEndMode
{
    /** Keep the first or last value outside the key span. */
    BOOT_TRACK_END_HOLD,

    /** Wrap the key into the stored span. */
    BOOT_TRACK_END_CYCLE,

    /** Use the first value at the last segment's endpoint. */
    BOOT_TRACK_END_CYCLE_TO_FIRST,

    /** Reflect the key on odd cycles. */
    BOOT_TRACK_END_PING_PONG,

    /** Continue evaluating the first or last segment outside the span. */
    BOOT_TRACK_END_EXTEND_SEGMENT,

    /** Wrap the key and add the endpoint difference for each cycle. */
    BOOT_TRACK_END_OFFSET_CYCLE,

    /** Interpolate from the stored single key before the first array key. */
    BOOT_TRACK_END_USE_PRE_START_KEY
};

/** Bookkeeping every track keeps after its key storage: counts, the cached lookup and how it extends past its ends. */
struct BootSequenceTail
{
    /** Whole key spans the last wrapped key was past the first key; negative before it. */
    s32 cycle_count;

    /** Last key minus first key. */
    float span;

    s16 key_count;
    s16 key_capacity;

    /** Lower key index the last search found; the next search starts there. */
    s16 search_index;

    /** Lower key index the cached segment was built from; -1 after the keys change. */
    s16 segment_lower;

    /** Upper key index the cached segment was built from; -1 after the keys change. */
    s16 segment_upper;

    /** BootTrackEndMode applied before the first key. */
    u8 before_mode : 4;

    /** BootTrackEndMode applied after the last key. */
    u8 after_mode : 4;

    /** Set when either end extends its first or last keyframe segment. */
    u8 extends_segment : 1;

    /** Set when the keys are bound from outside, so the track doesn't free them. */
    u8 external_keys : 1;

    /** Set while the track belongs to a pool. */
    u8 pooled : 1;

    u8 unk13_3_7 : 5;
};

/** Fixed pool of tracks with a bitmap of used slots. */
template <class T> struct BootTrackPool
{
        /**
         * @brief Allocate the tracks, mark them pooled and clear the used bitmap.
         * @param count Number of tracks.
         * @return One on success, or zero when the tracks could not be allocated.
         */
        s32 init(s32 count)
        {
            s32 index;
            s32 word_count;
            s32 word;
            items = new (0) T[count];

            if (items == 0)
            {
                return 0;
            }

            for (index = 0; index < count; index++)
            {
                items[index].state.pooled = true;
            }

            if (!external)
            {
                delete[] used;
            }

            capacity = count;
            words = (u32)(count + 63) >> 6;
            used = new (0) u64[words];
            external = false;
            this->count = count;
            unk04 = 0;
            word_count = words;

            for (word = 0; word < word_count; word++)
            {
                used[word] = 0;
            }

            return 1;
        }

        /**
         * @brief Mark a track's pool slot as free.
         * @param track Track to release.
         */
        void free(T* track)
        {
            u32 index = ((u32)track - (u32)items) / ((u32)&items[1] - (u32)items);
            used[index >> 6] &= ~((u64)1 << (index & 0x3F));
        }

        /** @brief Release every track in the pool and its storage. */
        void release()
        {
            s32 track_count = count;
            s32 index;

            for (index = 0; index < track_count; index++)
            {
                items[index].state.pooled = false;
            }

            delete[] items;

            if (!external)
            {
                delete[] used;
                used = 0;
            }

            items = 0;
            count = 0;
        }

        s32 count;
        s32 unk04;
        T* items;
        s32 capacity;
        s32 words;
        u64* used;
        bool external;
};

/** Track record with vtable D_171B00 in main data; its data comes before the vptr. */
class BootFloatHistoryBase
{
    public:
        /** @brief Reset the record. */
        BootFloatHistoryBase();

        /** @brief Forget the stored samples. */
        void reset();

        u32 unk00;
        s16 sample_count;
        s16 next_index;
        u32 unk08;
        u32 unk0C;

        /** @brief Slot 8; empty here and in every Lib copy, so its purpose is unknown. */
        virtual void func_slot08();
};

/** BootFloatHistoryBase with vtable D_171B30 in main data. */
class BootFloatHistory : public BootFloatHistoryBase
{
    public:
        /** @brief Reset the record and clear its first word. */
        BootFloatHistory();

        /**
         * @brief Evaluate the record at a key.
         * @param key Evaluation key.
         * @return Evaluated value.
         */
        virtual float sample(float key) const = 0;

        /**
         * @brief Store a value and key in the two-entry history and count it, up to two.
         * @param value Value to store.
         * @param key Key to store.
         */
        virtual void push_sample(const float* value, float key);

        float values[2];
        float keys[2];
};

/** 0x24-byte BootFloatHistory with the Lib vtable D_178200. */
class BootClass178200 : public BootFloatHistory
{
    public:
        /**
         * @brief Evaluate the record at a key.
         * @param key Evaluation key.
         * @return Evaluated value.
         */
        virtual float sample(float key) const;

        /**
         * @brief Add a key and its value to the record.
         * @param key Key.
         * @param value Value at the key.
         */
        virtual void add_sample(float key, float value);
};

/** Vector record with vtable D_171B10 in main data; its data comes before the vptr. */
class BootVectorHistoryBase
{
    public:
        /** @brief Reset the record. */
        BootVectorHistoryBase();

        /** @brief Forget the stored samples. */
        void reset();

        FieldVec4B unk00;
        s16 sample_count;
        s16 next_index;
        u32 unk14;
        u32 unk18;

        /** @brief Slot 8; empty here and in every Lib copy, so its purpose is unknown. */
        virtual void func_slot08();
};

/** BootVectorHistoryBase with vtable D_171B50 in main data. */
class BootVectorHistory : public BootVectorHistoryBase
{
    public:
        /** @brief Reset the record and clear its vector. */
        BootVectorHistory();

        /**
         * @brief Evaluate the record at a key.
         * @param key Evaluation key.
         * @return Evaluated vector.
         */
        virtual FieldVec4B sample(float key) = 0;

        /**
         * @brief Store a value and key in the two-entry history and count it, up to two.
         * @param key Key to store.
         * @param value Value to store.
         */
        virtual void push_sample(float key, const FieldVec4A* value);

        FieldVec4B values[2];
        float keys[2];
};

/** 0x20-byte BootVectorHistory with the Lib vtable D_1781E0. */
class BootClass1781E0 : public BootVectorHistory
{
    public:
        /**
         * @brief Evaluate the record at a key.
         * @param key Evaluation key.
         * @return Evaluated vector.
         */
        virtual FieldVec4B sample(float key);
};

/**
 * Two-sample vector history with vtable D_171B20 in main data; its data comes before the vptr. The same layout as
 * BootVectorHistoryBase; Lib's BootClass1718C0-family sampler resets and fills one.
 */
class BootClass171B20
{
    public:
        /** @brief Reset the record. */
        BootClass171B20();

        /** @brief Forget the stored samples. */
        void reset();

        FieldVec4B unk00;
        s16 sample_count;
        s16 next_index;
        u32 unk14;
        u32 unk18;

        /** @brief Slot 8; empty here and in every Lib copy, so its purpose is unknown. */
        virtual void func_slot08();
};

/** BootClass171B20 with vtable D_171B70 in main data. */
class BootClass171B70 : public BootClass171B20
{
    public:
        /** @brief Reset the record and clear its vector. */
        BootClass171B70();

        // Pure virtual slot 0xC; only its position is known.
        virtual void func_slot0c() = 0;

        /**
         * @brief Store a value and key in the two-entry history and count it, up to two.
         * @param value Value to store.
         * @param key Key to store.
         */
        virtual void push_sample(const FieldVec4A* value, float key);

        FieldVec4B values[2];
        float keys[2];
};

/** 0x20-byte BootClass171B70 with the Lib vtable D_1781C0. */
class BootClass1781C0 : public BootClass171B70
{
    public:
        // Lib implementation of the pure slot; only its position is known.
        virtual void func_slot0c();
};

/** Scalar range with vtable D_171B88 in main data; its data comes before the vptr. */
class BootFloatSegmentBase
{
    public:
        /** @brief Install the vtable; the range is left unset. */
        BootFloatSegmentBase();

        float start_value;
        float end_value;
        float start_tangent;
        float end_tangent;
        float start_key;
        float end_key;
        float key_span;

        /**
         * @brief Evaluate the segment at a key; Lib implements this.
         * @param key Evaluation key.
         * @return Value at the key.
         */
        float interpolate(float key) const;

        /**
         * @brief Set the segment from the values, tangents and keys at its two ends.
         * @param from_value Value at the start key.
         * @param from_tangent Tangent at the start key.
         * @param to_value Value at the end key.
         * @param to_tangent Tangent at the end key.
         * @param from_key Key the segment starts at.
         * @param to_key Key the segment ends at.
         */
        virtual void set_endpoints(const float* from_value, const float* from_tangent, const float* to_value, const float* to_tangent, float from_key,
                                   float to_key);
};

/** 0x20-byte BootFloatSegmentBase with vtable D_171270 in main data. */
class BootFloatSegment : public BootFloatSegmentBase
{
    public:
        /**
         * @brief Evaluate the segment at a key.
         * @param key Evaluation key.
         * @return Value at the key.
         */
        virtual float evaluate(float key) const;
};

/** Root of the keyframe tracks (vtable D_171170 in main data). A track holds keys sorted by time and samples a value between them. */
class BootTrack
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootTrack()
        {
        }
};

/** 8-byte scalar keyframe of BootFloatTrackBase: a key followed by its value. */
struct BootFloatTrackKey
{
    /**
     * @brief Copy the key and value.
     * @param entry Entry to copy.
     * @return This entry.
     */
    BootFloatTrackKey& operator=(const BootFloatTrackKey& entry)
    {
        key = entry.key;
        value = entry.value;
        return *this;
    }

    float key;
    float value;
};

/** Key storage and bookkeeping for tracks of single float values (vtable D_1717A0 in main data); keys aren't stored at this level. */
class BootFloatTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootFloatTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootFloatTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootFloatTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const float* value, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const float* value);

        /**
         * @brief Insert an indexed keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const float* value);

        /**
         * @brief Read an indexed keyframe; the base has none.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, float* value, float* first, float* second) const;

        /**
         * @brief Add a keyframe through the track implementation.
         * @param value Keyframe value.
         * @param key Sort key.
         */
        virtual void set_single_key(const float* value, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(float* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(float* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero with fewer than two keys.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated value.
         */
        virtual void evaluate(float key, float* output);

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track to its pool, or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the keyframe storage.
         * @return Keyframe storage.
         */
        virtual BootFloatTrackKey* get_keys();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a keyframe with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const float* value, float key);

        /**
         * @brief Handle an indexed keyframe with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const float* value);

        /**
         * @brief Handle an indexed keyframe with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const float* value);

        /**
         * @brief Handle a keyframe with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const float* value, float key);

        /**
         * @brief Return zero.
         * @return Zero.
         */
        virtual float get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual float find_key_value(float key);

        // Implemented by the derived tracks: sample (slot 0x80) and return_to_pool (slot 0x84).
        virtual float sample(float key) = 0;

        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        /**
         * @brief Normalize a key across the cached span and store its signed period count.
         * @param key Key whose period count is representable as a signed 32-bit integer.
         * @return Normalized key, with odd-period reflection selected by the control fields.
         */
        float update_cycle_count(float key);

        /**
         * @brief Find the entries around a key, starting from the cached cursor.
         * @param key Key to place.
         * @param lower Receives the lower entry index.
         * @param upper Receives the upper entry index.
         * @return One when the active end mode extends the first or last segment, otherwise zero.
         */
        u8 find_surrounding_keys(float key, s32* lower, s32* upper);

        BootFloatTrackKey* key_array;

        /** Single cached keyframe, used before an array is allocated. */
        BootFloatTrackKey single_key;

        BootSequenceTail state;
};

/** Float track that stores its keys in the array (vtable D_171560 in main data). */
class BootFloatKeyTrack : public BootFloatTrackBase
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootFloatKeyTrack()
        {
        }

        /**
         * @brief Read an indexed keyframe.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return One when the index is within the capacity, otherwise zero.
         */
        virtual s32 read_key(s32 index, float* key, float* value, float* first, float* second) const;

        /**
         * @brief Append a keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 on_append_key(const float* value, float key);

        /**
         * @brief Replace an indexed keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 on_replace_key(s32 index, float key, const float* value);

        /**
         * @brief Insert a keyframe at an index.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 on_insert_key(s32 index, float key, const float* value);

        /**
         * @brief Store a single keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         */
        virtual void on_set_single_key(const float* value, float key);
};

/** Float track that samples its keys and caches the value and its change per frame (vtable D_1715F0 in main data). */
class BootFloatTrack : public BootFloatKeyTrack
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootFloatTrack()
        {
        }

        /** @brief Reset to a single zero keyframe at key zero, then select the cycle end mode. */
        virtual void reset_keys();

        /**
         * @brief Return the difference between the endpoint values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(float* output) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(float* output) const;

        /** @brief Clear the last sampled value, then reset the key state. */
        virtual void reset_state();

        /**
         * @brief Evaluate the track at a key.
         * @param key Evaluation key.
         * @return Evaluated value.
         */
        virtual float sample(float key);

        BootClass178200 sample_history;
        float last_value;
        float value_rate;
};

/** 0x50-byte float track allocated from a BootTrackPool, with the Lib vtable D_177F70. */
class BootPooledFloatTrack : public BootFloatTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledFloatTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledFloatTrack();

        /** @brief Free the keys and give the track back to its pool; boot uses the Lib implementation. */
        virtual void return_to_pool();
};

/** 16-byte keyframe of BootVectorTrackBase; the value's fourth component is its key. */
struct BootVectorTrackKey
{
    /** @brief Leave the value uninitialized. */
    BootVectorTrackKey()
    {
    }

    FieldVec4B value;
};

/** Key storage for tracks of xyz vectors whose w holds the key (vtable D_171830 in main data). */
class BootVectorTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootVectorTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootVectorTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootVectorTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param key Sort key.
         */
        virtual void set_single_key(const FieldVec4A* value, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output);

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootVectorTrackKey* get_keys();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        /**
         * @brief Normalize a key across the cached span and store its signed period count.
         * @param key Key whose period count is representable as a signed 32-bit integer.
         * @return Normalized key, with odd-period reflection selected by the control fields.
         */
        float update_cycle_count(float key);

        /**
         * @brief Find the entries around a key, starting from the cached cursor.
         * @param key Key to place.
         * @param lower Receives the lower entry index.
         * @param upper Receives the upper entry index.
         * @return One when the active end mode extends the first or last segment, otherwise zero.
         */
        u8 find_surrounding_keys(float key, s32* lower, s32* upper);

        BootVectorTrackKey* key_array;
        u8 unk08[8];

        /** Single cached keyframe, used before an array is allocated. */
        BootVectorTrackKey single_key;

        BootSequenceTail state;
};

/** Vector track that stores its keys in the array (vtable D_1713B0 in main data). */
class BootVectorKeyTrack : public BootVectorTrackBase
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootVectorKeyTrack()
        {
        }

        // Overrides of the base slots of the same names.
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        virtual s32 on_append_key(const FieldVec4A* value, float key);
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);
        virtual void on_set_single_key(const FieldVec4A* value, float key);
};

/** Vector track that samples its keys and caches the value and its change per frame (vtable D_171440 in main data). */
class BootVectorTrack : public BootVectorKeyTrack
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootVectorTrack()
        {
        }

        // Overrides of the base slots of the same names.
        virtual void reset_keys();

        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_value_rate(FieldVec4B* output) const;
        virtual void reset_state();
        virtual FieldVec4A sample(float key);

        BootClass1781E0 sample_history;
        FieldVec4B last_value;
        FieldVec4B value_rate;
};

/** 0xB0-byte vector track allocated from a BootTrackPool (vtable D_1714D0 in main data). */
class BootPooledVectorTrack : public BootVectorTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledVectorTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledVectorTrack();

        // Overrides of the base slots of the same names.
        virtual void release();

        virtual void return_to_pool();
};

/** 32-byte keyframe of BootClass1718C0: a key and a value at offset 0x10. */
struct BootTrackKey1718C0
{
    /** @brief Leave the keyframe uninitialized. */
    BootTrackKey1718C0();

    float key;
    FieldVec4B value;
};

/**
 * Keyframe track with vtable D_1718C0 in main data; its constructor and destructor are out of line. The values look
 * like rotations: Lib's sampler (0x4B1A50, through D_177EE0) handles the end modes with quaternion inverses and a VU
 * normalize, as BootFloatQuaternionTrackBase's does, but interpolates with plain float maths and a BootClass171B70
 * history instead of slerp.
 */
class BootClass1718C0 : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootClass1718C0();

        /** @brief Destroy the track. */
        virtual ~BootClass1718C0();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootTrackKey1718C0* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param key Sort key.
         */
        virtual void set_single_key(const FieldVec4A* value, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootTrackKey1718C0* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) const = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        BootTrackKey1718C0* key_array;
        u8 unk08[8];

        /** Key of the single cached keyframe, used before an array is allocated. */
        float single_key;

        u8 unk14[0xC];

        /** Value of the single cached keyframe. */
        FieldVec4B single_value;

        BootSequenceTail state;
};

/** Partial BootClass1718C0 with vtable D_171320 in main data. */
class BootClass171320 : public BootClass1718C0
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootClass171320()
        {
        }

        // Overrides of the base slots of the same names.
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        virtual s32 on_append_key(const FieldVec4A* value, float key);
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);
        virtual void on_set_single_key(const FieldVec4A* value, float key);
};

/** 0xC0-byte pooled track with the Lib vtable D_177EE0. */
class BootClass177EE0 : public BootClass171320
{
    public:
        /** @brief Construct the track. */
        BootClass177EE0();

        /** @brief Destroy the track. */
        virtual ~BootClass177EE0();

        // Boot uses the Lib implementations of these.
        virtual void get_end_delta(FieldVec4B* output) const;

        virtual void get_value_rate(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void return_to_pool();

        BootClass1781C0 unk50;
        u8 unkA0[0x20];
};

/** 16-byte keyframe of BootFloatCurveTrackBase: a key and three values. */
struct BootFloatCurveTrackKey
{
    /**
     * @brief Copy the key and three values.
     * @param entry Entry to copy.
     * @return This entry.
     */
    BootFloatCurveTrackKey& operator=(const BootFloatCurveTrackKey& entry)
    {
        key = entry.key;
        value = entry.value;
        in_tangent = entry.in_tangent;
        out_tangent = entry.out_tangent;
        return *this;
    }

    float key;
    float value;
    float in_tangent;
    float out_tangent;
};

/** Key storage for float tracks whose keys carry a value and two tangents (vtable D_171950 in main data). */
class BootFloatCurveTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootFloatCurveTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootFloatCurveTrackBase();

        /**
         * @brief Replace the entry array with count new entries.
         * @param count Number of entries.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Install an entry array, set both counts, mark the array as installed and cache its span.
         * @param count Number of entries; must be at least one.
         * @param entries Entry array to install.
         */
        virtual void bind_keys(s32 count, BootFloatCurveTrackKey* entries);

        /**
         * @brief Set what the track does before its first key, and whether it extends an end segment.
         * @param value Value whose low four bits are stored.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key, and whether it extends an end segment.
         * @param value Value whose low four bits are stored.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append an entry through slot 24.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @param key Sort value.
         * @return The result of slot 24.
         */
        virtual s32 append_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /** @brief Default virtual handler that performs no work. */
        virtual void func_slot24();

        /**
         * @brief Set an entry through slot 25.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @return The result of slot 25.
         */
        virtual s32 replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Insert an entry through slot 26.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @return The result of slot 26.
         */
        virtual s32 insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Default entry reader that returns zero.
         * @param index Entry index.
         * @param key Receives the sort value, or null.
         * @param value Receives the key value, or null.
         * @param in_tangent Receives the arriving tangent, or null.
         * @param out_tangent Receives the leaving tangent, or null.
         * @return Always 0.
         */
        virtual s32 read_key(s32 index, float* key, float* value, float* in_tangent, float* out_tangent) const;

        /**
         * @brief Add an entry through slot 27.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @param key Sort value.
         */
        virtual void set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /** @brief Default virtual handler that performs no work. */
        virtual void reset_keys();

        /**
         * @brief Test whether an entry has exactly the given sort value.
         * @param key Sort value to find.
         * @return 1 when a matching entry exists, otherwise 0.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(float* output) const = 0;

        /**
         * @brief Wrap a value into the span between the first and last entry sort values.
         * @param key Value to wrap.
         * @return value reduced by a whole number of spans, or value unchanged when that number is zero.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(float* output) const = 0;

        /**
         * @brief Compute the span between the first and last entry sort values.
         * @return The span, or 0.0f when fewer than two entries exist.
         */
        virtual float get_key_span() const;

        /**
         * @brief Store slot 30's value for a sort value.
         * @param key Sort value.
         * @param output Receives the value.
         */
        virtual void evaluate(float key, float* output);

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Delete the object through its virtual destructor. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootFloatCurveTrackKey* get_keys() const;

        /** @brief Reset the entry array pointer, counters, indices, nibbles and ownership flags. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity() const;

        /**
         * @brief Default append handler.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @param key Sort value.
         * @return Always 0.
         */
        virtual s32 on_append_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /**
         * @brief Default set handler.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @return Always 0.
         */
        virtual s32 on_replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Default insert handler.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @return Always 0.
         */
        virtual s32 on_insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Default add handler.
         * @param value Key value, or null.
         * @param in_tangent Tangent arriving at the key, or null.
         * @param out_tangent Tangent leaving the key, or null.
         * @param key Sort value.
         */
        virtual void on_set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /**
         * @brief Report a fixed zero value for this receiver class.
         * @return Always 0.0f.
         */
        virtual float get_zero_value() const;

        /**
         * @brief Find the first entry with the requested sort value.
         * @param key Sort value to find.
         * @return The entry's first component, or zero when no entry matches.
         */
        virtual float find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual float sample(float key) = 0;

        /**
         * @brief Append a key with its tangents.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Key.
         * @return Nonzero when the key was stored.
         */
        virtual s32 append_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key) = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        /**
         * @brief Normalize a key across the cached span and store its signed period count.
         * @param key Key whose period count is representable as a signed 32-bit integer.
         * @return Normalized key, with odd-period reflection selected by the control fields.
         */
        float update_cycle_count(float key);

        /**
         * @brief Find the entries around a key, starting from the cached cursor.
         * @param key Key to place.
         * @param lower Receives the lower entry index.
         * @param upper Receives the upper entry index.
         * @return One when the active end mode extends the first or last segment, otherwise zero.
         */
        u8 find_surrounding_keys(float key, s32* lower, s32* upper);

        BootFloatCurveTrackKey* key_array;
        BootFloatCurveTrackKey single_key;
        BootSequenceTail state;
};

/** Float curve track that stores and samples its keys (vtable D_171280 in main data). */
class BootFloatCurveTrack : public BootFloatCurveTrackBase
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootFloatCurveTrack()
        {
        }

        // Overrides of the base slots of the same names.
        virtual s32 append_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        virtual s32 replace_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);
        virtual s32 insert_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);
        virtual s32 read_key(s32 index, float* key, float* value, float* in_tangent, float* out_tangent) const;
        virtual void set_single_key(const float* value, const float* in_tangent, const float* out_tangent, float key);
        virtual void reset_keys();
        virtual void get_end_delta(float* output) const;
        virtual void get_value_rate(float* output) const;
        virtual void reset_state();
        virtual float sample(float key);
        virtual s32 append_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        /**
         * @brief Replace an indexed entry.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return One when the entry was stored.
         */
        virtual s32 replace_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Insert an entry at an index.
         * @param index Entry index.
         * @param key Sort value.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return One when the entry was stored.
         */
        virtual s32 insert_curve_key(s32 index, float key, const float* value, const float* in_tangent, const float* out_tangent);

        /**
         * @brief Store a single entry in the cached entry.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Sort value.
         */
        virtual void set_single_curve_key(const float* value, const float* in_tangent, const float* out_tangent, float key);

        BootFloatSegment curve_segment;
        float last_value;
        float value_rate;
};

/** 0x54-byte float curve track allocated from a BootTrackPool, with the Lib vtable D_177C70. */
class BootPooledFloatCurveTrack : public BootFloatCurveTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledFloatCurveTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledFloatCurveTrack();
};

/** Vector range with vtable D_171B98 in main data; its data comes before the vptr. */
class BootVectorSegmentBase
{
    public:
        /** @brief Install the vtable; the range is left unset. */
        BootVectorSegmentBase();

        FieldVec4B start_value;
        FieldVec4B end_value;
        FieldVec4B start_tangent;
        FieldVec4B end_tangent;
        float start_key;
        float end_key;
        float key_span;

        /**
         * @brief Evaluate the segment at a key; Lib implements this.
         * @param key Evaluation key.
         * @return Value at the key.
         */
        FieldVec4B interpolate(float key) const;

        /**
         * @brief Set the segment from the keys, values and tangents at its two ends.
         * @param from_key Key the segment starts at.
         * @param to_key Key the segment ends at.
         * @param from_value Value at the start key.
         * @param from_tangent Tangent at the start key.
         * @param to_value Value at the end key.
         * @param to_tangent Tangent at the end key.
         */
        virtual void set_endpoints(float from_key, float to_key, const FieldVec4A* from_value, const FieldVec4A* from_tangent, const FieldVec4A* to_value,
                                   const FieldVec4A* to_tangent);
};

/** 0x50-byte BootVectorSegmentBase with vtable D_1710C0 in main data. */
class BootVectorSegment : public BootVectorSegmentBase
{
    public:
        /**
         * @brief Evaluate the segment at a key.
         * @param key Evaluation key.
         * @return Value at the key.
         */
        virtual FieldVec4B evaluate(float key) const;
};

/** 48-byte vector keyframe of BootVectorCurveTrackBase: a BootVectorTrackBase keyframe and two auxiliary vectors. */
struct BootVectorCurveTrackKey : public BootVectorTrackKey
{
    /** @brief Leave the vectors uninitialized. */
    BootVectorCurveTrackKey()
    {
    }

    FieldVec4B in_tangent;
    FieldVec4B out_tangent;
};

/** Key storage for vector tracks whose keys carry a value and two tangent vectors (vtable D_1719E0 in main data). */
class BootVectorCurveTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootVectorCurveTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootVectorCurveTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootVectorCurveTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Sort key.
         * @return Append status.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return Replacement status.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return Insertion status.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Sort key.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output);

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootVectorCurveTrackKey* get_keys();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) = 0;

        /**
         * @brief Append a key with its tangents.
         * @param value Key value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @param key Key.
         * @return Nonzero when the key was stored.
         */
        virtual s32 append_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key) = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        /**
         * @brief Normalize a key across the cached span and store its signed period count.
         * @param key Key whose period count is representable as a signed 32-bit integer.
         * @return Normalized key, with odd-period reflection selected by the control fields.
         */
        float update_cycle_count(float key);

        /**
         * @brief Find the entries around a key, starting from the cached cursor.
         * @param key Key to place.
         * @param lower Receives the lower entry index.
         * @param upper Receives the upper entry index.
         * @return One when the active end mode extends the first or last segment, otherwise zero.
         */
        u8 find_surrounding_keys(float key, s32* lower, s32* upper);

        void* key_array;
        u8 unk08[8];

        /** Single cached keyframe, used before an array is allocated. */
        BootVectorCurveTrackKey single_key;

        BootSequenceTail state;
        u8 unk54[0xC];
};

/** Vector curve track that stores and samples its keys (vtable D_1710D0 in main data). */
class BootVectorCurveTrack : public BootVectorCurveTrackBase
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootVectorCurveTrack()
        {
        }

        // Overrides of the base slots of the same names.
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
        virtual void reset_keys();
        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_value_rate(FieldVec4B* output) const;
        virtual void reset_state();
        virtual FieldVec4A sample(float key);
        virtual s32 append_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

        /**
         * @brief Replace an indexed keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 replace_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

        /**
         * @brief Insert a keyframe at an index.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key.
         * @return Nonzero when the keyframe was stored.
         */
        virtual s32 insert_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent);

        /**
         * @brief Store a single keyframe in the cached vectors.
         * @param value Keyframe value.
         * @param in_tangent Tangent arriving at the key.
         * @param out_tangent Tangent leaving the key. auxiliary vector.
         * @param key Key.
         */
        virtual void set_single_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key);

        BootVectorSegment curve_segment;
        FieldVec4B last_value;
        FieldVec4B value_rate;
};

/** 0xD0-byte vector curve track allocated from a BootTrackPool (vtable D_1711D0 in main data). */
class BootPooledVectorCurveTrack : public BootVectorCurveTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledVectorCurveTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledVectorCurveTrack();

        // Overrides of the base slots of the same names.
        virtual void release();

        /** @brief Free the keys and give the track back to its pool. */
        virtual void return_to_pool();
};

/** 32-byte keyframe of BootFloatQuaternionTrackBase: a key and a rotation quaternion at offset 0x10. */
struct BootFloatQuaternionTrackKey
{
    /** @brief Leave the keyframe uninitialized. */
    BootFloatQuaternionTrackKey();

    float key;
    u8 unk04[0xC];

    /** Rotation quaternion (x, y, z, w). */
    float value[4];
};

/**
 * Key storage for rotation tracks with full float quaternions (vtable D_171A70 in main data); its constructor and
 * destructor are out of line. Lib's sampler slerps between neighbouring keys.
 */
class BootFloatQuaternionTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootFloatQuaternionTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootFloatQuaternionTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootFloatQuaternionTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @param second Second auxiliary vector.
         */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootFloatQuaternionTrackKey* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) const = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        BootFloatQuaternionTrackKey* key_array;
        u8 unk08[0x28];
        BootSequenceTail state;
};

/** 0x80-byte float quaternion track allocated from a BootTrackPool, with the Lib vtable D_177BE0. */
class BootPooledFloatQuaternionTrack : public BootFloatQuaternionTrackBase
{
    public:
        /** @brief Construct the track. */
        BootPooledFloatQuaternionTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledFloatQuaternionTrack();

        // Boot uses the Lib implementations of these.
        virtual void get_end_delta(FieldVec4B* output) const;

        virtual void get_value_rate(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void return_to_pool();

        u8 unk44[0x3C];
};

/** 48-byte keyframe of BootQuaternionCurveTrackBase: a key, a rotation quaternion and its squad control quaternion. */
struct BootQuaternionCurveTrackKey
{
    /** @brief Leave the keyframe uninitialized. */
    BootQuaternionCurveTrackKey();

    float key;
    u8 unk04[0xC];

    /** Rotation quaternion (x, y, z, w). */
    float value[4];

    /** Inner control quaternion that squad blends through between this key and the next. */
    float control[4];
};

/**
 * Key storage for smooth rotation tracks (vtable D_171680 in main data); its constructor and destructor are out
 * of line. Each key carries a control quaternion, and Lib's sampler interpolates with squad.
 */
class BootQuaternionCurveTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootQuaternionCurveTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootQuaternionCurveTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootQuaternionCurveTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @param second Second auxiliary vector.
         */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootQuaternionCurveTrackKey* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key);

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) const = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        BootQuaternionCurveTrackKey* key_array;
        u8 unk08[0x38];
        BootSequenceTail state;
};

/** 0x90-byte quaternion curve track allocated from a BootTrackPool, with the Lib vtable D_174440. */
class BootPooledQuaternionCurveTrack : public BootQuaternionCurveTrackBase
{
    public:
        /** @brief Construct the track. */
        BootPooledQuaternionCurveTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledQuaternionCurveTrack();

        // Boot uses the Lib implementations of these.
        virtual void get_end_delta(FieldVec4B* output) const;

        virtual void get_value_rate(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void return_to_pool();

        u8 unk54[0x3C];
};

/** 8-byte packed keyframe of BootQuaternionTrackBase: three halfword values and a halfword key. */
struct BootQuaternionTrackKey
{
    /**
     * @brief Copy the values and key.
     * @param entry Entry to copy.
     * @return This entry.
     */
    BootQuaternionTrackKey& operator=(const BootQuaternionTrackKey& entry)
    {
        packed_rotation[0] = entry.packed_rotation[0];
        packed_rotation[1] = entry.packed_rotation[1];
        packed_rotation[2] = entry.packed_rotation[2];
        key = entry.key;
        return *this;
    }

    /** Rotation as the quaternion's x, y and z in 1.15 fixed point; w is rebuilt from them. */
    s16 packed_rotation[3];

    s16 key;
};

/** Key storage for rotation tracks with quaternions packed as three halfwords (vtable D_171710 in main data). */
class BootQuaternionTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootQuaternionTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootQuaternionTrackBase();

        /**
         * @brief Allocate storage for the requested keyframe count.
         * @param count Requested keyframe count.
         */
        virtual void allocate_keys(s32 count);

        /**
         * @brief Bind an external keyframe array.
         * @param count Keyframe count.
         * @param entries External keyframe storage.
         */
        virtual void bind_keys(s32 count, BootQuaternionTrackKey* entries);

        /**
         * @brief Set what the track does before its first key.
         * @param value Mode value.
         */
        virtual void set_before_mode(u32 value);

        /**
         * @brief Set what the track does after its last key.
         * @param value Mode value.
         */
        virtual void set_after_mode(u32 value);

        /**
         * @brief Return how many key spans the last wrapped key was past the first key.
         * @return Signed cycle count.
         */
        virtual s32 get_cycle_count() const;

        /**
         * @brief Append a vector keyframe.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @return Append status.
         */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Slot 0x24; BootTrack's empty version (track_default_func_slot24) is the only one. */
        virtual void func_slot24();

        /**
         * @brief Replace an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Replacement status.
         */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Insert an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Sort key.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Read an indexed vector keyframe.
         * @param index Keyframe index.
         * @param key Receives the sort key.
         * @param value Receives the value.
         * @param first Receives the first auxiliary vector.
         * @param second Receives the second auxiliary vector.
         * @return Nonzero when the keyframe is available.
         */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /**
         * @brief Add a vector keyframe through the track implementation.
         * @param value Keyframe value.
         * @param first Optional first auxiliary vector.
         * @param second Optional second auxiliary vector.
         * @param key Sort key.
         * @param second Second auxiliary vector.
         */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /**
         * @brief Test whether the track contains the supplied key.
         * @param key Key to find.
         * @return Nonzero when the key exists.
         */
        virtual s32 has_key(float key) const;

        /**
         * @brief Return the difference between the last and first key values.
         * @param output Receives the difference.
         */
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /**
         * @brief Wrap a key into the stored key range.
         * @param key Key to wrap.
         * @return Wrapped key.
         */
        virtual float wrap_key(float key) const;

        /**
         * @brief Return how fast the value changed at the last sample, per second.
         * @param output Receives the rate.
         */
        virtual void get_value_rate(FieldVec4B* output) const = 0;

        /**
         * @brief Return the span between the first and last keys.
         * @return Key span, or zero when fewer than two keys are stored.
         */
        virtual float get_key_span() const;

        /**
         * @brief Evaluate the vector track at a key.
         * @param key Evaluation key.
         * @param output Receives the evaluated vector.
         */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /**
         * @brief Return the stored keyframe count.
         * @return Keyframe count.
         */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /**
         * @brief Return the key storage.
         * @return Key array, or null.
         */
        virtual BootQuaternionTrackKey* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /**
         * @brief Return the number of keys the storage can hold.
         * @return Key capacity.
         */
        virtual s16 get_key_capacity();

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         * @return Handler result.
         */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle an indexed vector set with a key; the base implementation ignores it.
         * @param index Key index.
         * @param key Key the keyframe sits at.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @return Handler result.
         */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /**
         * @brief Handle a vector set with a key; the base implementation ignores it.
         * @param value Key value.
         * @param first First auxiliary vector.
         * @param second Second auxiliary vector.
         * @param key Key the keyframe sits at.
         */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /**
         * @brief Return a zero vector.
         * @return Zero vector.
         */
        virtual FieldVec4A get_zero_value() const;

        /**
         * @brief Return the value of the keyframe with the supplied key.
         * @param key Key to find.
         * @return Keyframe value, or zero when the key is absent.
         */
        virtual FieldVec4A find_key_value(float key) const;

        /**
         * @brief Sample the track at a key and cache the value and its change per second.
         * @param key Key to sample at.
         * @return Value at the key.
         */
        virtual FieldVec4A sample(float key) const = 0;

        /** @brief Free the keys and give the track back to its pool; pooled tracks implement it. */
        virtual void return_to_pool() = 0;

        /** @brief Delete the key storage unless it is external, and clear the key pointer. */
        void free_keys();

        BootQuaternionTrackKey* key_array;
        u8 unk08[8];
        BootSequenceTail state;
};

/** 0x2C-byte quaternion track allocated from a BootTrackPool, with the Lib vtable D_1730F0. */
class BootPooledQuaternionTrack : public BootQuaternionTrackBase
{
    public:
        /** @brief Construct the track. */
        BootPooledQuaternionTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledQuaternionTrack();

        // Boot uses the Lib implementations of these.
        virtual void get_end_delta(FieldVec4B* output) const;

        virtual void get_value_rate(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void return_to_pool();

        u8 unk24[8];
};

extern "C" {
s32 float_track_pool_allocate(BootTrackPool<BootPooledFloatTrack>* pool, s32 count);
void float_track_pool_release(BootTrackPool<BootPooledFloatTrack>* pool);
s32 vector_track_pool_allocate(BootTrackPool<BootPooledVectorTrack>* pool, s32 count);
void vector_track_pool_release(BootTrackPool<BootPooledVectorTrack>* pool);
s32 track_1718C0_pool_allocate(BootTrackPool<BootClass177EE0>* pool, s32 count);
void track_1718C0_pool_release(BootTrackPool<BootClass177EE0>* pool);
s32 float_curve_track_pool_allocate(BootTrackPool<BootPooledFloatCurveTrack>* pool, s32 count);
void float_curve_track_pool_release(BootTrackPool<BootPooledFloatCurveTrack>* pool);
s32 vector_curve_track_pool_allocate(BootTrackPool<BootPooledVectorCurveTrack>* pool, s32 count);
void vector_curve_track_pool_release(BootTrackPool<BootPooledVectorCurveTrack>* pool);
s32 float_quaternion_track_pool_allocate(BootTrackPool<BootPooledFloatQuaternionTrack>* pool, s32 count);
void float_quaternion_track_pool_release(BootTrackPool<BootPooledFloatQuaternionTrack>* pool);
s32 quaternion_curve_track_pool_allocate(BootTrackPool<BootPooledQuaternionCurveTrack>* pool, s32 count);
void quaternion_curve_track_pool_release(BootTrackPool<BootPooledQuaternionCurveTrack>* pool);
s32 quaternion_track_pool_allocate(BootTrackPool<BootPooledQuaternionTrack>* pool, s32 count);
void quaternion_track_pool_release(BootTrackPool<BootPooledQuaternionTrack>* pool);
}

extern "C" {
extern ResidentInputSystem* g_input_system;
s32 func_432720(BootModeOwner0910* owner, void* queue);
void func_432660(BootModeOwner0910* owner, s32 mode, u32 enabled, u32 flags);
s32 func_432310(BootModeOwner0910* owner, u32 mode, BootCardFileRequest* request);
s32 func_432270(BootModeOwner0910* owner, s32 mode, s32* result);
extern BootUpdateList* D_001B6614;
/** Product code at the start of every save name: "BASLUS-20488". */
extern const char g_card_product_code[];
/** Save name suffix of the battle trophy file: "BTLCOL". */
extern const char g_trophy_file_suffix[];
/** Suffix that matches any of the game's saves: "-*". */
extern const char g_any_file_suffix[];
s32 func_431F90(BootModeOwner0910* owner, s32 slot, char* name, s32 first, s32 second, u8* buffer);
}

#endif
