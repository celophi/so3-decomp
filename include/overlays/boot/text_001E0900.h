#ifndef SO3_OVERLAYS_BOOT_TEXT_001E0900_H
#define SO3_OVERLAYS_BOOT_TEXT_001E0900_H

#include "overlays/boot/text_001DD3C0.h"
#include "main/resident_001001E0.h"
#include "overlays/lib/vector.h"

#define BOOT_TRANSFER_NAME_CAPACITY 64
#define BOOT_TRANSFER_BUFFER_SIZE 1158050
#define BOOT_TRANSFER_FLAG_COUNT 300
#define BOOT_TRANSFER_FLAG_BYTES ((BOOT_TRANSFER_FLAG_COUNT + 7) / 8)

/** @brief Partial 0x100-byte record the memory card object keeps per slot. */
struct BootModeSlot0910
{
    u8 unk00[0x48];

    /** Card state; two once the card is ready. */
    s32 unk48;

    /** Free space. */
    s32 unk4C;

    /** Nonzero when the card is formatted. */
    s32 unk50;

    u8 unk54[0xAC];
};

/** Partial 0x58-byte Lib memory card object that runs the two transfer modes; boot calls the Lib constructor. */
class BootModeOwner0910 : public BootListObject
{
    public:
        /** @brief Initialize the memory card object. */
        BootModeOwner0910();

        BootModeSlot0910* unk14;
        u8 unk18[8];
        u8 unk20;
        u8 unk21[0x37];
};

enum BootModeFlags0910
{
    BOOT_MODE_0910_FLAG_0 = 0x1,
    BOOT_MODE_0910_FLAG_1 = 0x2
};

/** @brief Stored filename, buffer address, extent, and an unknown word. */
struct BootCardFileBuffer
{
    char* unk00;
    void* unk04;
    u32 unk08;
    u32 unk0C;
};

/** @brief Request record retained by the mode owner's selected entry. */
struct BootCardFileRequest
{
    char* unk00;
    s32 unk04;
    u32 unk08;
    BootCardFileBuffer* unk0C;
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

        /** @brief Report the list kind used when registration requests the default. @return Two. */
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

        /** @brief Return the last transfer's result. @return Result code; negative on failure. */
        s32 get_transfer_result();

        /** @brief Return the transfer state. @return 1 once the transfer has finished, -1 while it runs or after a reset. */
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

        s16 unk1A;
        s16 unk1C;
        u8 unk1E;
        u8 unk1F;
        u32 unk20;
        s32 free_space;
        u8 unk28;
        u8 slot1_status_valid;
        u8 slot2_status_valid;
        u8 slot1_status;
        u8 slot2_status;
        u8 unk2D;
        char filename[BOOT_TRANSFER_NAME_CAPACITY];
        u8 unk6E[0xCC0];
        u8* unkD30;
        u8 card_mode;
        u8 unkD35[2];
        u8 unkD37[2];
        u8 unkD39[0x80];
        u8* unkDBC;
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
        u8 unkDF8;
        u8 unkDF9;
        s32 slot_free_space[2];
        s32 unkE04[2];
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

/** Interface with one pure virtual function, with vtable D_170F20 in main data. */
class BootClass170F20
{
    public:
        /** @brief Return the interface's value. @return Value. */
        virtual float func_001E9380() = 0;
};

/** Implementation of BootClass170F20 that returns zero, with vtable D_170F10 in main data. */
class BootClass170F10 : public BootClass170F20
{
    public:
        /** @brief Return zero. @return Always 0.0f. */
        virtual float func_001E9380()
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

        /** @brief Report the list kind used when registration requests the default. @return Four. */
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
        BootClass170F10 unk138;
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

        /** @brief Virtual slot 5. @return Always 0. */
        virtual s32 func_001E9640();

        /** @brief Forget the memory card states so the next query starts fresh. */
        void clear_card_states();

        u8 card_query_enabled;
        u8 unk15;

        /** Buttons held down. */
        u16 held;

        /** Buttons pressed this frame. */
        u16 pressed;

        u16 unk1A;

        /** Buttons pressed this frame or auto-repeating. */
        u16 repeated;

        u8 unk1E[2];

        /** Last nonzero state of card slot 1, as BootStartupChecks compares them. */
        u32 slot1_state;

        /** Last nonzero state of card slot 2. */
        u32 slot2_state;

        u32 unk28;
        u32 unk2C;

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
    s32 unk80C0;

    float unk80C4;
    float unk80C8;
    u8 unk80CC[0xC];
    u8 unk80D8;
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
        u8 unk15E794;

        u8 unk15E795[0x2B];
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
            data = func_139700(0x40, func_11C8C0(D_001B65E4, 0x26));
            func_103E70(D_001B65E8, 0x26, data, 1, 0x34BC0, 0, 0, 0, 1);
            program = owner;
            block = 0;
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
struct BootInputRoot9670;

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

        /** @brief Read the message bank handle. @return Bank handle. */
        s32 get_messages() const
        {
            return messages;
        }

        /** @brief Read the pad and memory card monitor. @return Monitor. */
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
struct BootResident6658
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

/** Bookkeeping every track keeps after its key storage: counts, the cached lookup and how it extends past its ends. */
struct BootSequenceTail
{
    /** Whole key spans the last wrapped key was past the first key; negative before it. */
    s32 cycle_count;

    /** Last key minus first key. */
    float span;

    s16 key_count;
    s16 key_capacity;
    s16 unk0c;
    s16 unk0e;

    /** Upper key index of the last lookup, where the next search starts; -1 when unset. */
    s16 cached_index;

    /** What the track does before its first key; 4 repeats the keys, the other codes are still unclear. */
    u8 before_mode : 4;

    /** What the track does after its last key, with the same codes as before_mode. */
    u8 after_mode : 4;

    /** Set when either mode is 4. */
    u8 repeats : 1;

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

        u32 unk00;
        u16 unk04;
        u16 unk06;
        u32 unk08;
        u32 unk0C;

        // Virtual slot 8; only its position is known.
        virtual void func_001F4970();
};

/** BootFloatHistoryBase with vtable D_171B30 in main data. */
class BootFloatHistory : public BootFloatHistoryBase
{
    public:
        /** @brief Reset the record and clear its first word. */
        BootFloatHistory();

        /** @brief Evaluate the record at a key. @param key Evaluation key. @return Evaluated value. */
        virtual float sample(float key) const = 0;

        // Virtual slot 0x10; only its position is known.
        virtual void push_sample();
};

/** 0x24-byte BootFloatHistory with the Lib vtable D_178200. */
class BootClass178200 : public BootFloatHistory
{
    public:
        /** @brief Evaluate the record at a key. @param key Evaluation key. @return Evaluated value. */
        virtual float sample(float key) const;

        /** @brief Add a key and its value to the record. @param key Key. @param value Value at the key. */
        virtual void add_sample(float key, float value);

        u8 unk14[0x10];
};

/** Vector record with vtable D_171B10 in main data; its data comes before the vptr. */
class BootVectorHistoryBase
{
    public:
        /** @brief Reset the record. */
        BootVectorHistoryBase();

        FieldVec4B unk00;
        s16 unk10;
        s16 unk12;
        u32 unk14;
        u32 unk18;

        // Virtual slot 8; only its position is known.
        virtual void func_001F4960();
};

/** BootVectorHistoryBase with vtable D_171B50 in main data. */
class BootVectorHistory : public BootVectorHistoryBase
{
    public:
        /** @brief Reset the record and clear its vector. */
        BootVectorHistory();

        /** @brief Evaluate the record at a key. @param key Evaluation key. @return Evaluated vector. */
        virtual FieldVec4B sample(float key) = 0;

        /**
         * @brief Store a value and key in the two-entry history and count it, up to two.
         * @param key Key to store.
         * @param value Value to store.
         */
        virtual void push_sample(float key, const FieldVec4A* value);

        FieldVec4B unk20[2];
        float unk40[2];
};

/** 0x20-byte BootVectorHistory with the Lib vtable D_1781E0. */
class BootClass1781E0 : public BootVectorHistory
{
    public:
        /** @brief Evaluate the record at a key. @param key Evaluation key. @return Evaluated vector. */
        virtual FieldVec4B sample(float key);
};

/** Vector record with vtable D_171B20 in main data; its data comes before the vptr. */
class BootClass171B20
{
    public:
        /** @brief Reset the record. */
        BootClass171B20();

        FieldVec4B unk00;
        s16 unk10;
        s16 unk12;
        u32 unk14;
        u32 unk18;

        // Virtual slot 8; only its position is known.
        virtual void func_001F4950();
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

        FieldVec4B unk20[2];
        float unk40[2];
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

        float unk00;
        float unk04;
        float unk08;
        float unk0C;
        float unk10;
        float unk14;
        float unk18;

        /**
         * @brief Set the range from two endpoint values and their tangents.
         * @param first First endpoint value.
         * @param second First endpoint tangent.
         * @param third Second endpoint value.
         * @param fourth Second endpoint tangent.
         * @param start Start key.
         * @param end End key.
         */
        virtual void set_endpoints(const float* first, const float* second, const float* third, const float* fourth, float start, float end);
};

/** 0x20-byte BootFloatSegmentBase with vtable D_171270 in main data. */
class BootFloatSegment : public BootFloatSegmentBase
{
    public:
        // Virtual slot 0xC; only its position is known.
        virtual void func_001EEE20();
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

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void allocate_keys(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void bind_keys(s32 count, void* entries);

        /** @brief Set what the track does before its first key. @param mode Mode value. */
        virtual void set_before_mode(u32 mode);

        /** @brief Set what the track does after its last key. @param mode Mode value. */
        virtual void set_after_mode(u32 mode);

        /** @brief Return how many key spans the last wrapped key was past the first key. @return Signed cycle count. */
        virtual u32 get_cycle_count() const;

        /** @brief Append a keyframe. @param value Keyframe value. @param key Sort key. @return Append status. */
        virtual s32 append_key(const float* value, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Replacement status. */
        virtual s32 replace_key(s32 index, float key, const float* value);

        /** @brief Insert an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Insertion status. */
        virtual s32 insert_key(s32 index, float key, const float* value);

        /** @brief Read an indexed keyframe; the base has none. @return Nonzero when the keyframe is available. */
        virtual s32 read_key(s32 index, float* key, float* value, float* first, float* second) const;

        /** @brief Add a keyframe through the track implementation. @param value Keyframe value. @param key Sort key. */
        virtual void set_single_key(const float* value, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 has_key(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void get_end_delta(float* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float wrap_key(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void get_cached_value(float* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero with fewer than two keys. */
        virtual float get_key_span() const;

        /** @brief Evaluate the track at a key. @param key Evaluation key. @param output Receives the evaluated value. */
        virtual void evaluate(float key, float* output);

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track to its pool, or delete an ordinary track. */
        virtual void release();

        /** @brief Return the keyframe storage. @return Keyframe storage. */
        virtual void* get_keys();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void reset_state();

        /** @brief Return the number of keys the storage can hold. @return Key capacity. */
        virtual s16 get_key_capacity();

        /** @brief Handle a keyframe with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_append_key(const float* value, float key);

        /** @brief Handle an indexed keyframe with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_replace_key(s32 index, float key, const float* value);

        /** @brief Handle an indexed keyframe with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_insert_key(s32 index, float key, const float* value);

        /** @brief Handle a keyframe with a key; the base implementation ignores it. */
        virtual void on_set_single_key(const float* value, float key);

        /** @brief Return zero. @return Zero. */
        virtual float get_zero_value() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual float find_key_value(float key) const;

        // Pure virtual slots 0x80 and 0x84; only their positions are known.
        virtual float sample(float key) = 0;

        virtual void func_slot84() = 0;

        BootFloatTrackKey* unk04;

        /** Single cached keyframe, used before an array is allocated. */
        BootFloatTrackKey unk08;

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

        /** @brief Read an indexed keyframe. @return One when the index is within the capacity, otherwise zero. */
        virtual s32 read_key(s32 index, float* key, float* value, float* first, float* second) const;

        /** @brief Append a keyframe. @param value Keyframe value. @param key Sort key. @return Nonzero when the keyframe was stored. */
        virtual s32 on_append_key(const float* value, float key);

        /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the keyframe
         * was stored. */
        virtual s32 on_replace_key(s32 index, float key, const float* value);

        /** @brief Insert a keyframe at an index. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the
         * keyframe was stored. */
        virtual s32 on_insert_key(s32 index, float key, const float* value);

        /** @brief Store a single keyframe. @param value Keyframe value. @param key Sort key. */
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

        /** @brief Reset to a single zero keyframe at key zero, then set before_mode to one. */
        virtual void reset_keys();

        /** @brief Return the difference between the endpoint values. @param output Receives the difference. */
        virtual void get_end_delta(float* output) const;

        /** @brief Return the cached value. @param output Receives the cached value. */
        virtual void get_cached_value(float* output) const;

        /** @brief Clear the word at offset 0x48 and reset the sequence. */
        virtual void reset_state();

        /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated value. */
        virtual float sample(float key);

        BootClass178200 unk24;
        float unk48;
        float unk4c;
};

/** 0x50-byte float track allocated from a BootTrackPool, with the Lib vtable D_177F70. */
class BootPooledFloatTrack : public BootFloatTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledFloatTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledFloatTrack();

        // Lib implementation of the pure slot 0x84; only its position is known.
        virtual void func_slot84();
};

struct BootVectorTrackKey;

/** Key storage for tracks of xyz vectors whose w holds the key (vtable D_171830 in main data). */
class BootVectorTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootVectorTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootVectorTrackBase();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void allocate_keys(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void bind_keys(s32 count, void* entries);

        /** @brief Set what the track does before its first key. @param mode Mode value. */
        virtual void set_before_mode(s32 mode);

        /** @brief Set what the track does after its last key. @param mode Mode value. */
        virtual void set_after_mode(s32 mode);

        /** @brief Return how many key spans the last wrapped key was past the first key. @return Signed cycle count. */
        virtual s32 get_cycle_count() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param key Sort key. @return Append status. */
        virtual s32 append_key(const FieldVec4A* value, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Replacement
         * status. */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first
         * Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param key Sort key. */
        virtual void set_single_key(const FieldVec4A* value, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 has_key(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float wrap_key(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void get_cached_value(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float get_key_span() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void evaluate(float key, FieldVec4B* output);

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /** @brief Return the key storage. @return Key array, or null. */
        virtual void* get_keys();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void reset_state();

        /** @brief Return the number of keys the storage can hold. @return Key capacity. */
        virtual s16 get_key_capacity();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_append_key(const FieldVec4A* value, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void on_set_single_key(const FieldVec4A* value, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A get_zero_value() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A find_key_value(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A sample(float key) = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual void func_slot84() = 0;

        BootVectorTrackKey* unk04;
        u8 unk08[8];
        FieldVec4B unk10;
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

        // Overrides of base slots; only their positions are known.
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

        // Overrides of base slots; only their positions are known.
        virtual void reset_keys();
        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_cached_value(FieldVec4B* output) const;
        virtual void reset_state();
        virtual FieldVec4A sample(float key);

        BootClass1781E0 unk40;
        FieldVec4B unk90;
        FieldVec4B unkA0;
};

/** 0xB0-byte vector track allocated from a BootTrackPool (vtable D_1714D0 in main data). */
class BootPooledVectorTrack : public BootVectorTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledVectorTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledVectorTrack();

        // Overrides of base slots; only their positions are known.
        virtual void release();
        virtual void func_slot84();
};

/** 32-byte keyframe of BootClass1718C0: a key and a value at offset 0x10. */
struct BootTrackKey1718C0
{
    /** @brief Leave the keyframe uninitialized. */
    BootTrackKey1718C0();

    float key;
    FieldVec4B value;
};

/** Partial keyframe track with vtable D_1718C0 in main data; its constructor and destructor are out of line. */
class BootClass1718C0 : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootClass1718C0();

        /** @brief Destroy the track. */
        virtual ~BootClass1718C0();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void allocate_keys(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void bind_keys(s32 count, void* entries);

        /** @brief Set what the track does before its first key. @param mode Mode value. */
        virtual void set_before_mode(s32 mode);

        /** @brief Set what the track does after its last key. @param mode Mode value. */
        virtual void set_after_mode(s32 mode);

        /** @brief Return how many key spans the last wrapped key was past the first key. @return Signed cycle count. */
        virtual s32 get_cycle_count() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param key Sort key. @return Append status. */
        virtual s32 append_key(const FieldVec4A* value, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Replacement
         * status. */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Insertion status.
         */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first
         * Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param key Sort key. */
        virtual void set_single_key(const FieldVec4A* value, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 has_key(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float wrap_key(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void get_cached_value(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float get_key_span() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /** @brief Return the key storage. @return Key array, or null. */
        virtual void* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /** @brief Return the number of keys the storage can hold. @return Key capacity. */
        virtual s16 get_key_capacity();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_append_key(const FieldVec4A* value, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void on_set_single_key(const FieldVec4A* value, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A get_zero_value() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A find_key_value(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A sample(float key) const = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual void func_slot84() = 0;

        void* unk04;
        u8 unk08[8];
        float unk10;
        u8 unk14[0xC];
        FieldVec4B unk20;
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

        // Overrides of base slots; only their positions are known.
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

        // Lib implementations of the pure slots; only their positions are known.
        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_cached_value(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void func_slot84();

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
        unk00 = entry.unk00;
        unk04 = entry.unk04;
        unk08 = entry.unk08;
        unk0c = entry.unk0c;
        return *this;
    }

    float unk00;
    float unk04;
    float unk08;
    float unk0c;
};

/** Key storage for float tracks whose keys carry a value and two tangents (vtable D_171950 in main data). */
class BootFloatCurveTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootFloatCurveTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootFloatCurveTrackBase();

        /** @brief Replace the entry array with count new entries. @param count Number of entries. */
        virtual void allocate_keys(s32 count);

        /** @brief Install an entry array, set both counts, mark the array as installed and cache its span. @param count Number of entries; must be at least
         * one. @param entries Entry array to install. */
        virtual void bind_keys(s32 count, void* entries);

        /** @brief Store the low nibble at offset 0x2A, then set flag bit 0 at offset 0x2B when either nibble is 4. @param value Value whose low four bits are
         * stored. */
        virtual void set_before_mode(s32 value);

        /** @brief Store the high nibble at offset 0x2A, then set flag bit 0 at offset 0x2B when either nibble is 4. @param value Value whose low four bits are
         * stored. */
        virtual void set_after_mode(s32 value);

        /** @brief Return how many key spans the last wrapped key was past the first key. @return Signed cycle count. */
        virtual s32 get_cycle_count() const;

        /** @brief Append an entry through slot 24. @param x First component, or null. @param y Second component, or null. @param z Third component, or null.
         * @param key Sort value. @return The result of slot 24. */
        virtual s32 append_key(const float* x, const float* y, const float* z, float key);

        /** @brief Default virtual handler that performs no work. */
        virtual void func_001EECA0();

        /** @brief Set an entry through slot 25. @param index Entry index. @param key Sort value. @param x First component, or null. @param y Second component,
         * or null. @param z Third component, or null. @return The result of slot 25. */
        virtual s32 replace_key(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Insert an entry through slot 26. @param index Entry index. @param key Sort value. @param x First component, or null. @param y Second
         * component, or null. @param z Third component, or null. @return The result of slot 26. */
        virtual s32 insert_key(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Default entry reader that returns zero. @param index Entry index. @param key Receives the sort value, or null. @param x Receives the first
         * component, or null. @param y Receives the second component, or null. @param z Receives the third component, or null. @return Always 0. */
        virtual s32 read_key(s32 index, float* key, float* x, float* y, float* z) const;

        /** @brief Add an entry through slot 27. @param x First component, or null. @param y Second component, or null. @param z Third component, or null.
         * @param key Sort value. */
        virtual void set_single_key(const float* x, const float* y, const float* z, float key);

        /** @brief Default virtual handler that performs no work. */
        virtual void reset_keys();

        /** @brief Test whether an entry has exactly the given sort value. @param key Sort value to find. @return 1 when a matching entry exists, otherwise 0.
         */
        virtual s32 has_key(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void get_end_delta(float* output) const = 0;

        /** @brief Wrap a value into the span between the first and last entry sort values. @param value Value to wrap. @return value reduced by a whole number
         * of spans, or value unchanged when that number is zero. */
        virtual float wrap_key(float value) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void get_cached_value(float* output) const = 0;

        /** @brief Compute the span between the first and last entry sort values. @return The span, or 0.0f when fewer than two entries exist. */
        virtual float get_key_span() const;

        /** @brief Store slot 30's value for a sort value. @param key Sort value. @param out Receives the value. */
        virtual void evaluate(float key, float* output);

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 get_key_count() const;

        /** @brief Delete the object through its virtual destructor. */
        virtual void release();

        /** @brief Return the key storage. @return Key array, or null. */
        virtual void* get_keys() const;

        /** @brief Reset the entry array pointer, counters, indices, nibbles and ownership flags. */
        virtual void reset_state();

        /** @brief Return the number of keys the storage can hold. @return Key capacity. */
        virtual s16 get_key_capacity() const;

        /** @brief Default append handler. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @param key
         * Sort value. @return Always 0. */
        virtual s32 on_append_key(const float* x, const float* y, const float* z, float key);

        /** @brief Default set handler. @param index Entry index. @param key Sort value. @param x First component, or null. @param y Second component, or null.
         * @param z Third component, or null. @return Always 0. */
        virtual s32 on_replace_key(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Default insert handler. @param index Entry index. @param key Sort value. @param x First component, or null. @param y Second component, or
         * null. @param z Third component, or null. @return Always 0. */
        virtual s32 on_insert_key(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Default add handler. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @param key
         * Sort value. */
        virtual void on_set_single_key(const float* x, const float* y, const float* z, float key);

        /** @brief Report a fixed zero value for this receiver class. @return Always 0.0f. */
        virtual float get_zero_value() const;

        /** @brief Find the first entry with the requested sort value. @param key Sort value to find. @return The entry's first component, or zero when no entry
         * matches. */
        virtual float find_key_value(float key);

        // Pure virtual slot 0x80; only its position is known.
        virtual float sample(float key) = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual s32 append_curve_key(const float* x, const float* y, const float* z, float key) = 0;

        BootFloatCurveTrackKey* unk04;
        BootFloatCurveTrackKey unk08;
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

        // Overrides of base slots; only their positions are known.
        virtual s32 append_key(const float* x, const float* y, const float* z, float key);
        virtual s32 replace_key(s32 index, float key, const float* x, const float* y, const float* z);
        virtual s32 insert_key(s32 index, float key, const float* x, const float* y, const float* z);
        virtual s32 read_key(s32 index, float* key, float* x, float* y, float* z) const;
        virtual void set_single_key(const float* x, const float* y, const float* z, float key);
        virtual void reset_keys();
        virtual void get_end_delta(float* output) const;
        virtual void get_cached_value(float* output) const;
        virtual void reset_state();
        virtual float sample(float key);
        virtual s32 append_curve_key(const float* x, const float* y, const float* z, float key);

        /** @brief Replace an indexed entry. @param index Entry index. @param key Sort value. @param x First component. @param y Second component. @param z
         * Third component. @return One when the entry was stored. */
        virtual s32 replace_curve_key(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Insert an entry at an index. @param index Entry index. @param key Sort value. @param x First component. @param y Second component. @param z
         * Third component. @return One when the entry was stored. */
        virtual s32 insert_curve_key(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Store a single entry in the cached entry. @param x First component. @param y Second component. @param z Third component. @param key Sort
         * value. */
        virtual void set_single_curve_key(const float* x, const float* y, const float* z, float key);

        BootFloatSegment unk2C;
        float unk4c;
        float unk50;
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

        FieldVec4B unk00;
        FieldVec4B unk10;
        FieldVec4B unk20;
        FieldVec4B unk30;
        float unk40;
        float unk44;
        float unk48;

        /**
         * @brief Set the range from two endpoint vectors and their tangents.
         * @param start Start key.
         * @param end End key.
         * @param first First endpoint vector.
         * @param second First endpoint tangent.
         * @param third Second endpoint vector.
         * @param fourth Second endpoint tangent.
         */
        virtual void set_endpoints(float start, float end, const FieldVec4A* first, const FieldVec4A* second, const FieldVec4A* third,
                                   const FieldVec4A* fourth);
};

/** 0x50-byte BootVectorSegmentBase with vtable D_1710C0 in main data. */
class BootVectorSegment : public BootVectorSegmentBase
{
    public:
        // Virtual slot 0xC; only its position is known.
        virtual void evaluate();
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

/** 48-byte vector keyframe of BootVectorCurveTrackBase: a BootVectorTrackBase keyframe and two auxiliary vectors. */
struct BootTrackKey1719E0 : public BootVectorTrackKey
{
    /** @brief Leave the vectors uninitialized. */
    BootTrackKey1719E0()
    {
    }

    FieldVec4B first;
    FieldVec4B second;
};

/** Key storage for vector tracks whose keys carry a value and two tangent vectors (vtable D_1719E0 in main data). */
class BootVectorCurveTrackBase : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootVectorCurveTrackBase();

        /** @brief Destroy the track. */
        virtual ~BootVectorCurveTrackBase();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void allocate_keys(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void bind_keys(s32 count, void* entries);

        /** @brief Set what the track does before its first key. @param mode Mode value. */
        virtual void set_before_mode(s32 mode);

        /** @brief Set what the track does after its last key. @param mode Mode value. */
        virtual void set_after_mode(s32 mode);

        /** @brief Return how many key spans the last wrapped key was past the first key. @return Signed cycle count. */
        virtual s32 get_cycle_count() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary
         * vector. @param key Sort key. @return Append status. */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional
         * first auxiliary vector. @param second Optional second auxiliary vector. @return Replacement status. */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first
         * auxiliary vector. @param second Optional second auxiliary vector. @return Insertion status. */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first
         * Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param first Optional first auxiliary vector. @param
         * second Optional second auxiliary vector. @param key Sort key. */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 has_key(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float wrap_key(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void get_cached_value(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float get_key_span() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void evaluate(float key, FieldVec4B* output);

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /** @brief Return the key storage. @return Key array, or null. */
        virtual void* get_keys();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void reset_state();

        /** @brief Return the number of keys the storage can hold. @return Key capacity. */
        virtual s16 get_key_capacity();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A get_zero_value() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A find_key_value(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A sample(float key) = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual s32 append_curve_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key) = 0;

        void* unk04;
        u8 unk08[8];
        FieldVec4B unk10;
        FieldVec4B unk20;
        FieldVec4B unk30;
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

        // Overrides of base slots; only their positions are known.
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
        virtual void reset_keys();
        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_cached_value(FieldVec4B* output) const;
        virtual void reset_state();
        virtual FieldVec4A sample(float key);
        virtual s32 append_curve_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first First auxiliary
         * vector. @param second Second auxiliary vector. @return Nonzero when the keyframe was stored. */
        virtual s32 replace_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert a keyframe at an index. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first First auxiliary
         * vector. @param second Second auxiliary vector. @return Nonzero when the keyframe was stored. */
        virtual s32 insert_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Store a single keyframe in the cached vectors. @param value Keyframe value. @param first First auxiliary vector. @param second Second
         * auxiliary vector. @param key Key. */
        virtual void set_single_curve_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        BootVectorSegment unk60;
        FieldVec4B unkB0;
        FieldVec4B unkC0;
};

/** 0xD0-byte vector curve track allocated from a BootTrackPool (vtable D_1711D0 in main data). */
class BootPooledVectorCurveTrack : public BootVectorCurveTrack
{
    public:
        /** @brief Construct the track. */
        BootPooledVectorCurveTrack();

        /** @brief Destroy the track. */
        virtual ~BootPooledVectorCurveTrack();

        // Overrides of base slots; only their positions are known.
        virtual void release();

        // Virtual slot 0x94; only its position is known.
        virtual void func_001EEDF0();
};

/** Partial 32-byte keyframe of BootClass171A70 with its key first. */
struct BootTrackKey171A70
{
    /** @brief Leave the keyframe uninitialized. */
    BootTrackKey171A70();

    float key;
    u8 unk04[0x1C];
};

/** Partial keyframe track with vtable D_171A70 in main data; its constructor and destructor are out of line. */
class BootClass171A70 : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootClass171A70();

        /** @brief Destroy the track. */
        virtual ~BootClass171A70();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void allocate_keys(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void bind_keys(s32 count, void* entries);

        /** @brief Set what the track does before its first key. @param mode Mode value. */
        virtual void set_before_mode(s32 mode);

        /** @brief Set what the track does after its last key. @param mode Mode value. */
        virtual void set_after_mode(s32 mode);

        /** @brief Return how many key spans the last wrapped key was past the first key. @return Signed cycle count. */
        virtual s32 get_cycle_count() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary
         * vector. @param key Sort key. @return Append status. */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional
         * first auxiliary vector. @param second Optional second auxiliary vector. @return Replacement status. */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first
         * auxiliary vector. @param second Optional second auxiliary vector. @return Insertion status. */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first
         * Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param first Optional first auxiliary vector. @param
         * second Optional second auxiliary vector. @param key Sort key. */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 has_key(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float wrap_key(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void get_cached_value(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float get_key_span() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /** @brief Return the key storage. @return Key array, or null. */
        virtual void* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /** @brief Return the number of keys the storage can hold. @return Key capacity. */
        virtual s16 get_key_capacity();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A get_zero_value() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A find_key_value(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A sample(float key) const = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual void func_slot84() = 0;

        void* unk04;
        u8 unk08[0x28];
        BootSequenceTail state;
};

/** 0x80-byte pooled track with the Lib vtable D_177BE0. */
class BootClass177BE0 : public BootClass171A70
{
    public:
        /** @brief Construct the track. */
        BootClass177BE0();

        /** @brief Destroy the track. */
        virtual ~BootClass177BE0();

        // Lib implementations of the pure slots; only their positions are known.
        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_cached_value(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void func_slot84();

        u8 unk44[0x3C];
};

/** Partial 48-byte keyframe of BootClass171680 with its key first. */
struct BootTrackKey171680
{
    /** @brief Leave the keyframe uninitialized. */
    BootTrackKey171680();

    float key;
    u8 unk04[0x2C];
};

/** Partial keyframe track with vtable D_171680 in main data; its constructor and destructor are out of line. */
class BootClass171680 : public BootTrack
{
    public:
        /** @brief Construct the track. */
        BootClass171680();

        /** @brief Destroy the track. */
        virtual ~BootClass171680();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void allocate_keys(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void bind_keys(s32 count, void* entries);

        /** @brief Set what the track does before its first key. @param mode Mode value. */
        virtual void set_before_mode(s32 mode);

        /** @brief Set what the track does after its last key. @param mode Mode value. */
        virtual void set_after_mode(s32 mode);

        /** @brief Return how many key spans the last wrapped key was past the first key. @return Signed cycle count. */
        virtual s32 get_cycle_count() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary
         * vector. @param key Sort key. @return Append status. */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional
         * first auxiliary vector. @param second Optional second auxiliary vector. @return Replacement status. */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first
         * auxiliary vector. @param second Optional second auxiliary vector. @return Insertion status. */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first
         * Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param first Optional first auxiliary vector. @param
         * second Optional second auxiliary vector. @param key Sort key. */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 has_key(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float wrap_key(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void get_cached_value(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float get_key_span() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /** @brief Return the key storage. @return Key array, or null. */
        virtual void* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /** @brief Return the number of keys the storage can hold. @return Key capacity. */
        virtual s16 get_key_capacity();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A get_zero_value() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A find_key_value(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A sample(float key) const = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual void func_slot84() = 0;

        void* unk04;
        u8 unk08[0x38];
        BootSequenceTail state;
};

/** 0x90-byte pooled track with the Lib vtable D_174440. */
class BootClass174440 : public BootClass171680
{
    public:
        /** @brief Construct the track. */
        BootClass174440();

        /** @brief Destroy the track. */
        virtual ~BootClass174440();

        // Lib implementations of the pure slots; only their positions are known.
        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_cached_value(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void func_slot84();

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
        unk00[0] = entry.unk00[0];
        unk00[1] = entry.unk00[1];
        unk00[2] = entry.unk00[2];
        key = entry.key;
        return *this;
    }

    s16 unk00[3];
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

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void allocate_keys(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void bind_keys(s32 count, void* entries);

        /** @brief Set what the track does before its first key. @param mode Mode value. */
        virtual void set_before_mode(s32 mode);

        /** @brief Set what the track does after its last key. @param mode Mode value. */
        virtual void set_after_mode(s32 mode);

        /** @brief Return how many key spans the last wrapped key was past the first key. @return Signed cycle count. */
        virtual s32 get_cycle_count() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary
         * vector. @param key Sort key. @return Append status. */
        virtual s32 append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional
         * first auxiliary vector. @param second Optional second auxiliary vector. @return Replacement status. */
        virtual s32 replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first
         * auxiliary vector. @param second Optional second auxiliary vector. @return Insertion status. */
        virtual s32 insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first
         * Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 read_key(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param first Optional first auxiliary vector. @param
         * second Optional second auxiliary vector. @param key Sort key. */
        virtual void set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void reset_keys();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 has_key(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void get_end_delta(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float wrap_key(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void get_cached_value(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float get_key_span() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void evaluate(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 get_key_count() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void release();

        /** @brief Return the key storage. @return Key array, or null. */
        virtual void* get_keys();

        /** @brief Clear the key storage, counts, modes and cached indices. */
        virtual void reset_state();

        /** @brief Return the number of keys the storage can hold. @return Key capacity. */
        virtual s16 get_key_capacity();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A get_zero_value() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A find_key_value(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A sample(float key) const = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual void func_slot84() = 0;

        void* unk04;
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

        // Lib implementations of the pure slots; only their positions are known.
        virtual void get_end_delta(FieldVec4B* output) const;
        virtual void get_cached_value(FieldVec4B* output) const;
        virtual FieldVec4A sample(float key) const;
        virtual void func_slot84();

        u8 unk24[8];
};

extern "C" {
s32 float_track_pool_allocate(BootTrackPool<BootPooledFloatTrack>* pool, s32 count);
void float_track_pool_release(BootTrackPool<BootPooledFloatTrack>* pool);
s32 vector_track_pool_allocate(BootTrackPool<BootPooledVectorTrack>* pool, s32 count);
void vector_track_pool_release(BootTrackPool<BootPooledVectorTrack>* pool);
s32 func_001ECC60(BootTrackPool<BootClass177EE0>* pool, s32 count);
void func_001ED060(BootTrackPool<BootClass177EE0>* pool);
s32 float_curve_track_pool_allocate(BootTrackPool<BootPooledFloatCurveTrack>* pool, s32 count);
s32 vector_curve_track_pool_allocate(BootTrackPool<BootPooledVectorCurveTrack>* pool, s32 count);
void vector_curve_track_pool_release(BootTrackPool<BootPooledVectorCurveTrack>* pool);
s32 func_001EDD60(BootTrackPool<BootClass177BE0>* pool, s32 count);
void func_001EE0C0(BootTrackPool<BootClass177BE0>* pool);
s32 func_001EE250(BootTrackPool<BootClass174440>* pool, s32 count);
void func_001EE5C0(BootTrackPool<BootClass174440>* pool);
s32 quaternion_track_pool_allocate(BootTrackPool<BootPooledQuaternionTrack>* pool, s32 count);
void quaternion_track_pool_release(BootTrackPool<BootPooledQuaternionTrack>* pool);
}

extern "C" {
extern BootInputRoot9670* D_001B65F0;
u16 func_11E010(BootInputRoot9670* root, s32 slot);
u16 func_11DFF0(BootInputRoot9670* root, s32 slot);
u16 func_11E000(BootInputRoot9670* root, s32 slot);
u16 func_11DFB0(BootInputRoot9670* root, s32 slot);
void func_11DF90(BootInputRoot9670* root, s32 slot);
void* func_100AC0(u32 size, s32 flags);
s32 func_432720(BootModeOwner0910* owner, void* queue);
void func_432660(BootModeOwner0910* owner, s32 mode, u32 enabled, u32 flags);
s32 func_432310(BootModeOwner0910* owner, u32 mode, BootCardFileRequest* request);
s32 func_432270(BootModeOwner0910* owner, s32 mode, s32* result);
extern BootUpdateList* D_001B6614;
void* func_100B00(u32 size, s32 flags);
char* func_13C948(char* destination, const char* source);
void* func_13A4C0(void* destination, const void* source, u32 size);
/** Product code at the start of every save name: "BASLUS-20488". */
extern const char g_card_product_code[];
/** Save name suffix of the battle trophy file: "BTLCOL". */
extern const char g_trophy_file_suffix[];
/** Suffix that matches any of the game's saves: "-*". */
extern const char g_any_file_suffix[];
s32 func_431F90(BootModeOwner0910* owner, s32 slot, char* name, s32 first, s32 second, u8* buffer);
}

#endif
