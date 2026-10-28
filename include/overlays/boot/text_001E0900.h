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
class BootModeOwner0910 : public BootClass170E90
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
struct BootTransferBuffer0AF0
{
    char* unk00;
    void* unk04;
    u32 unk08;
    u32 unk0C;
};

/** @brief Request record retained by the mode owner's selected entry. */
struct BootTransferRequest0AF0
{
    char* unk00;
    s32 unk04;
    u32 unk08;
    BootTransferBuffer0AF0* unk0C;
};

/**
 * Battle Trophies memory card file (BASLUS-20488BTLCOL), with vtable D_170EB0 in main data. It reads and writes the
 * file through a Lib memory card object and reports each slot's free-space state for the startup checks. Mode 0
 * and mode 1 select the two card slots.
 */
class BootBattleTrophyCard : public BootClass170E90
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
        void func_001E0970();

        /** @brief Return the stored signed request result. @return The stored value. */
        s32 func_001E0AD0();

        /** @brief Return the signed 16-bit value at offset 0xDCE. @return The stored value. */
        s16 func_001E0AE0();

        /**
         * @brief Advance the stored two-phase request and update its completion state.
         * @return Narrowed request status, or -1 when the phase is unsupported.
         */
        s16 func_001E0AF0();

        /**
         * @brief Initialize the buffer and request records for a selected transfer mode.
         * @param mode Transfer mode 0 or 1.
         * @param destination Nonnull destination for the transfer.
         * @return 1 when prepared, or 0 for invalid arguments or allocation failure.
         */
        s32 func_001E0C30(u16 mode, void* destination);

        /**
         * @brief Store mode 1 or 2 and reset the state for selector 0.
         * @param mode Mode to store; values other than 1 or 2 have no effect.
         */
        void func_001E0DE0(u8 mode);

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
        void func_001E1500(u8 enabled, u16 event, u16 kind);

        /**
         * @brief Select an event's byte status and update the current mode's stored status.
         * @param event Event code to classify.
         * @param result Byte receiving the selected status, initially cleared to zero.
         */
        void func_001E17C0(u16 event, u8* result);

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
        s32 unk24;
        u8 unk28;
        u8 unk29;
        u8 unk2A;
        u8 unk2B;
        u8 unk2C;
        u8 unk2D;
        char filename[BOOT_TRANSFER_NAME_CAPACITY];
        u8 unk6E[0xCC0];
        u8* unkD30;
        u8 unkD34;
        u8 unkD35[2];
        u8 unkD37[2];
        u8 unkD39[0x80];
        u8* unkDBC;
        s16 unkDC0;
        u8* transfer_buffer;
        void* unkDC8;
        s16 unkDCC;
        s16 unkDCE;
        s32 unkDD0;
        BootTransferBuffer0AF0 unkDD4;
        BootTransferRequest0AF0 unkDE4;
        BootResource0970* settings;
        u8 unkDF8;
        u8 unkDF9;
        s32 unkDFC[2];
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
class BootStartupChecks : public BootClass170E90
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

        BootClass178660* container;
        BootClass178750* text;
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

extern "C" void func_4BDD10(class BootClass178220* animation);

/** Partial 0x70-byte Lib animation with vtable D_178220 in main data; boot calls the Lib constructor. */
class BootClass178220 : public BootClass170E90
{
    public:
        /** @brief Construct an empty animation. */
        BootClass178220();

        /**
         * @brief Release the current channels and resource, then play from borrowed data.
         * @param data Animation data the caller keeps.
         */
        void set_resource(void* data)
        {
            if (entries)
            {
                func_4BDD10(this);
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
class BootClass178370 : public BootClass170E90
{
    public:
        /** @brief Construct an empty target. */
        BootClass178370();

        u8 unk14[0xBC];
};

/** Partial 0xB0-byte Lib scene with vtable D_175320 in main data; boot calls the Lib constructor. */
class BootClass175320 : public BootClass170E90
{
    public:
        /** @brief Construct an empty scene. */
        BootClass175320();

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
class BootNewGameSettings : public BootClass170E90
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
        BootClass175320* room_scene;
        BootClass175320* girl_scene;
        BootClass170F30* girl_models[10];

        /** Walk animations, one per walk_state. */
        BootClass178220* girl_animations[6];

        BootClass178370* animation_targets[6];
        BootClass170F10 unk138;
        BootClass178660* container;

        /** Description of the selected option. */
        BootClass178750* description_text;

        BootClass175070* cursor;
};

/** Boot's pad and memory card monitor, with vtable D_171030 in main data; samples both every frame. */
class BootInput : public BootClass170E90
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
class BootClass172500 : public BootClass170E90
{
    public:
        /**
         * @brief Initialize the player and its decoder for a frame size.
         * @param width Frame width.
         * @param height Frame height.
         */
        BootClass172500(s32 width, s32 height);

        /** @brief Destroy the player. */
        virtual ~BootClass172500();

        u8 unk14[0x15E6EC];
        BootMovieState15E700* state;
        u8 unk15E704[0x90];

        /** Nonzero while the movie plays. */
        u8 unk15E794;

        u8 unk15E795[0x2B];
};

/** The opening movie with its timed captions, with vtable D_171050 in main data; Start skips it. */
class BootOpeningMovie : public BootClass170E90
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
        BootClass172500* player;
        BootImage* caption_image;
        BootClass178660* container;
        BootClass178750* caption_text;
};

/** Partial 0x20-byte boot object with vtable D_171090 in main data. */
class BootResourceLoader : public BootClass170E90
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
            exit_code = 0;
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

        /** Nonzero once the boot program should end; passed on to the resident runtime. */
        s32 exit_code;

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

/** Shared keyframe sequence fields with packed modes and the pooled flag. */
struct BootSequenceTail
{
    s32 unk00;

    /** Last key minus first key. */
    float span;

    s16 unk08;
    s16 unk0a;
    s16 unk0c;
    s16 unk0e;
    s16 unk10;
    u8 unk12_0_3 : 4;
    u8 unk12_4_7 : 4;
    u8 unk13_0 : 1;
    u8 unk13_1 : 1;

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
class BootClass171B00
{
    public:
        /** @brief Reset the record. */
        BootClass171B00();

        u32 unk00;
        u16 unk04;
        u16 unk06;
        u32 unk08;
        u32 unk0C;

        // Virtual slot 8; only its position is known.
        virtual void func_001F4970();
};

/** BootClass171B00 with vtable D_171B30 in main data. */
class BootClass171B30 : public BootClass171B00
{
    public:
        /** @brief Reset the record and clear its first word. */
        BootClass171B30();

        // Virtual slots 0xC (pure) and 0x10; only their positions are known.
        virtual void func_slot0c() = 0;

        virtual void func_001F48D0();
};

/** 0x24-byte BootClass171B30 with the Lib vtable D_178200. */
class BootClass178200 : public BootClass171B30
{
    public:
        // Lib implementation of the pure slot; only its position is known.
        virtual void func_slot0c();

        u8 unk14[0x10];
};

/** Vector record with vtable D_171B10 in main data; its data comes before the vptr. */
class BootClass171B10
{
    public:
        /** @brief Reset the record. */
        BootClass171B10();

        FieldVec4B unk00;
        s16 unk10;
        s16 unk12;
        u32 unk14;
        u32 unk18;

        // Virtual slot 8; only its position is known.
        virtual void func_001F4960();
};

/** BootClass171B10 with vtable D_171B50 in main data. */
class BootClass171B50 : public BootClass171B10
{
    public:
        /** @brief Reset the record and clear its vector. */
        BootClass171B50();

        // Pure virtual slot 0xC; only its position is known.
        virtual void func_slot0c() = 0;

        /**
         * @brief Store a value and key in the two-entry history and count it, up to two.
         * @param value Value to store.
         * @param key Key to store.
         */
        virtual void func_001F0560(const FieldVec4A* value, float key);

        FieldVec4B unk20[2];
        float unk40[2];
};

/** 0x20-byte BootClass171B50 with the Lib vtable D_1781E0. */
class BootClass1781E0 : public BootClass171B50
{
    public:
        // Lib implementation of the pure slot; only its position is known.
        virtual void func_slot0c();
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
        virtual void func_001F4850(const FieldVec4A* value, float key);

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
class BootClass171B88
{
    public:
        /** @brief Install the vtable; the range is left unset. */
        BootClass171B88();

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
        virtual void func_001EFE50(const float* first, const float* second, const float* third, const float* fourth, float start, float end);
};

/** 0x20-byte BootClass171B88 with vtable D_171270 in main data. */
class BootClass171270 : public BootClass171B88
{
    public:
        // Virtual slot 0xC; only its position is known.
        virtual void func_001EEE20();
};

/** Root of the keyframe tracks, with only a destructor, with vtable D_171170 in main data. */
class BootClass171170
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootClass171170()
        {
        }
};

/** 8-byte scalar keyframe of BootClass1717A0: a key followed by its value. */
struct BootTrackKey1717A0
{
    /**
     * @brief Copy the key and value.
     * @param entry Entry to copy.
     * @return This entry.
     */
    BootTrackKey1717A0& operator=(const BootTrackKey1717A0& entry)
    {
        key = entry.key;
        value = entry.value;
        return *this;
    }

    float key;
    float value;
};

/** Partial keyframe track with vtable D_1717A0 in main data; its constructor and destructor are out of line. */
class BootClass1717A0 : public BootClass171170
{
    public:
        /** @brief Construct the track. */
        BootClass1717A0();

        /** @brief Destroy the track. */
        virtual ~BootClass1717A0();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void func_001F1F20(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void func_001F26E0(s32 count, void* entries);

        /** @brief Set the lower mode nibble. @param mode Mode value. */
        virtual void func_001F1FC0(u32 mode);

        /** @brief Set the upper mode nibble. @param mode Mode value. */
        virtual void func_001F2020(u32 mode);

        /** @brief Return the stored word at offset 0x10. @return Stored word. */
        virtual u32 func_001F2080() const;

        /** @brief Append a keyframe. @param value Keyframe value. @param key Sort key. @return Append status. */
        virtual s32 func_001F26A0(const float* value, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Replacement status. */
        virtual s32 func_001F2660(s32 index, float key, const float* value);

        /** @brief Insert an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Insertion status. */
        virtual s32 func_001F2620(s32 index, float key, const float* value);

        /** @brief Read an indexed keyframe; the base has none. @return Nonzero when the keyframe is available. */
        virtual s32 func_001EED60(s32 index, float* key, float* value, float* first, float* second) const;

        /** @brief Add a keyframe through the track implementation. @param value Keyframe value. @param key Sort key. */
        virtual void func_001F25E0(const float* value, float key);

        /** @brief Run the default update hook. */
        virtual void func_001EED80();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 func_001F2590(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void func_slot40(float* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float func_001F2450(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void func_slot48(float* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero with fewer than two keys. */
        virtual float func_001F2540() const;

        /** @brief Evaluate the track at a key. @param key Evaluation key. @param output Receives the evaluated value. */
        virtual void func_001F20C0(float key, float* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 func_001F2090() const;

        /** @brief Return a pooled track to its pool, or delete an ordinary track. */
        virtual void func_001EECB0();

        /** @brief Return the keyframe storage. @return Keyframe storage. */
        virtual void* func_001F20F0();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void func_001F1E90();

        // Virtual slot 0x64; only its position is known.
        virtual s16 func_001F20A0();

        /** @brief Handle a keyframe with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F26D0(const float* value, float key);

        /** @brief Handle an indexed keyframe with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F2690(s32 index, float key, const float* value);

        /** @brief Handle an indexed keyframe with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F2650(s32 index, float key, const float* value);

        /** @brief Handle a keyframe with a key; the base implementation ignores it. */
        virtual void func_001F2610(const float* value, float key);

        /** @brief Return zero. @return Zero. */
        virtual float func_001F20B0() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual float func_001F24E0(float key) const;

        // Pure virtual slots 0x80 and 0x84; only their positions are known.
        virtual float func_slot80(float key) const = 0;

        virtual void func_slot84() = 0;

        void* unk04;
        float unk08;
        float unk0c;
        BootSequenceTail state;
};

/** Partial BootClass1717A0 with vtable D_171560 in main data. */
class BootClass171560 : public BootClass1717A0
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootClass171560()
        {
        }

        /** @brief Read an indexed keyframe. @return One when the index is within the capacity, otherwise zero. */
        virtual s32 func_001EED60(s32 index, float* key, float* value, float* first, float* second) const;

        /** @brief Append a keyframe. @param value Keyframe value. @param key Sort key. @return Nonzero when the keyframe was stored. */
        virtual s32 func_001F26D0(const float* value, float key);

        /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the keyframe was stored. */
        virtual s32 func_001F2690(s32 index, float key, const float* value);

        /** @brief Insert a keyframe at an index. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Nonzero when the keyframe was stored. */
        virtual s32 func_001F2650(s32 index, float key, const float* value);

        /** @brief Store a single keyframe. @param value Keyframe value. @param key Sort key. */
        virtual void func_001F2610(const float* value, float key);
};

/** Partial BootClass171560 with vtable D_1715F0 in main data. */
class BootClass1715F0 : public BootClass171560
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootClass1715F0()
        {
        }

        /** @brief Reset to a single zero keyframe at key zero, then set the lower mode to one. */
        virtual void func_001EED80();

        /** @brief Return the difference between the endpoint values. @param output Receives the difference. */
        virtual void func_slot40(float* output) const;

        /** @brief Return the cached value. @param output Receives the cached value. */
        virtual void func_slot48(float* output) const;

        /** @brief Clear the word at offset 0x48 and reset the sequence. */
        virtual void func_001F1E90();

        /** @brief Evaluate the track at a key. @param key Evaluation key. @return Evaluated value. */
        virtual float func_slot80(float key) const;

        BootClass178200 unk24;
        s32 unk48;
        float unk4c;
};

/** 0x50-byte pooled track with the Lib vtable D_177F70. */
class BootClass177F70 : public BootClass1715F0
{
    public:
        /** @brief Construct the track. */
        BootClass177F70();

        /** @brief Destroy the track. */
        virtual ~BootClass177F70();

        // Lib implementation of the pure slot 0x84; only its position is known.
        virtual void func_slot84();
};

/** Partial keyframe track with vtable D_171830 in main data; its constructor and destructor are out of line. */
class BootClass171830 : public BootClass171170
{
    public:
        /** @brief Construct the track. */
        BootClass171830();

        /** @brief Destroy the track. */
        virtual ~BootClass171830();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void func_001F28A0(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void func_001F1A80(s32 count, void* entries);

        /** @brief Set the lower mode nibble. @param mode Mode value. */
        virtual void func_001F1AD0(s32 mode);

        /** @brief Set the upper mode nibble. @param mode Mode value. */
        virtual void func_001F1B30(s32 mode);

        /** @brief Return the stored word at offset 0x20. @return Stored word. */
        virtual s32 func_001F1B90() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param key Sort key. @return Append status. */
        virtual s32 func_001F2860(const FieldVec4A* value, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Replacement status. */
        virtual s32 func_001F2820(s32 index, float key, const FieldVec4A* value);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Insertion status. */
        virtual s32 func_001F27E0(s32 index, float key, const FieldVec4A* value);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param key Sort key. */
        virtual void func_001F27A0(const FieldVec4A* value, float key);

        /** @brief Run the default update hook. */
        virtual void func_001EED80();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 func_001F1BC0(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void func_slot40(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float func_001F1D30(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void func_slot48(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float func_001F1C30() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void func_001F1CE0(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 func_001F1BA0() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void func_001EECB0();

        // Virtual slot 0x5C; only its position is known.
        virtual void* func_001F1DC0();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void func_001F19F0();

        // Virtual slot 0x64; only its position is known.
        virtual s16 func_001F1BB0();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F2890(const FieldVec4A* value, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F2850(s32 index, float key, const FieldVec4A* value);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F2810(s32 index, float key, const FieldVec4A* value);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void func_001F27D0(const FieldVec4A* value, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A func_001F1C10() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A func_001F1C80(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A func_slot80(float key) const = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual void func_slot84() = 0;

        void* unk04;
        u8 unk08[8];
        FieldVec4B unk10;
        BootSequenceTail state;
};

/** Partial BootClass171830 with vtable D_1713B0 in main data. */
class BootClass1713B0 : public BootClass171830
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootClass1713B0()
        {
        }

        // Overrides of base slots; only their positions are known.
        virtual s32 func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
        virtual s32 func_001F2890(const FieldVec4A* value, float key);
        virtual s32 func_001F2850(s32 index, float key, const FieldVec4A* value);
        virtual s32 func_001F2810(s32 index, float key, const FieldVec4A* value);
        virtual void func_001F27D0(const FieldVec4A* value, float key);
};

/** Partial BootClass1713B0 with vtable D_171440 in main data. */
class BootClass171440 : public BootClass1713B0
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootClass171440()
        {
        }

        // Overrides of base slots; only their positions are known.
        virtual void func_001EED80();
        virtual void func_slot40(FieldVec4B* output) const;
        virtual void func_slot48(FieldVec4B* output) const;
        virtual void func_001F19F0();
        virtual FieldVec4A func_slot80(float key) const;

        BootClass1781E0 unk40;
        u8 unk90[0x20];
};

/** 0xB0-byte pooled track with vtable D_1714D0 in main data. */
class BootClass1714D0 : public BootClass171440
{
    public:
        /** @brief Construct the track. */
        BootClass1714D0();

        /** @brief Destroy the track. */
        virtual ~BootClass1714D0();

        // Overrides of base slots; only their positions are known.
        virtual void func_001EECB0();
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
class BootClass1718C0 : public BootClass171170
{
    public:
        /** @brief Construct the track. */
        BootClass1718C0();

        /** @brief Destroy the track. */
        virtual ~BootClass1718C0();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void func_001F2CB0(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void func_001F2C60(s32 count, void* entries);

        /** @brief Set the lower mode nibble. @param mode Mode value. */
        virtual void func_001F1580(s32 mode);

        /** @brief Set the upper mode nibble. @param mode Mode value. */
        virtual void func_001F15E0(s32 mode);

        /** @brief Return the stored word at offset 0x30. @return Stored word. */
        virtual s32 func_001F1640() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param key Sort key. @return Append status. */
        virtual s32 func_001F2C20(const FieldVec4A* value, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Replacement status. */
        virtual s32 func_001F2BE0(s32 index, float key, const FieldVec4A* value);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @return Insertion status. */
        virtual s32 func_001F2BA0(s32 index, float key, const FieldVec4A* value);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param key Sort key. */
        virtual void func_001F2B60(const FieldVec4A* value, float key);

        /** @brief Run the default update hook. */
        virtual void func_001EED80();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 func_001F2B10(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void func_slot40(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float func_001F29D0(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void func_slot48(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float func_001F2AC0() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void func_001F1690(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 func_001F1650() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void func_001EECB0();

        // Virtual slot 0x5C; only its position is known.
        virtual void* func_001F16E0();

        // Virtual slot 0x60; only its position is known.
        virtual void func_001F14F0();

        // Virtual slot 0x64; only its position is known.
        virtual s16 func_001F1660();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F2C50(const FieldVec4A* value, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F2C10(s32 index, float key, const FieldVec4A* value);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F2BD0(s32 index, float key, const FieldVec4A* value);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void func_001F2B90(const FieldVec4A* value, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A func_001F1670() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A func_001F2A60(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A func_slot80(float key) const = 0;

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
        virtual s32 func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
        virtual s32 func_001F2C50(const FieldVec4A* value, float key);
        virtual s32 func_001F2C10(s32 index, float key, const FieldVec4A* value);
        virtual s32 func_001F2BD0(s32 index, float key, const FieldVec4A* value);
        virtual void func_001F2B90(const FieldVec4A* value, float key);
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
        virtual void func_slot40(FieldVec4B* output) const;
        virtual void func_slot48(FieldVec4B* output) const;
        virtual FieldVec4A func_slot80(float key) const;
        virtual void func_slot84();

        BootClass1781C0 unk50;
        u8 unkA0[0x20];
};

/** 16-byte keyframe of BootClass171950: a key and three values. */
struct BootTrackKey171950
{
    /**
     * @brief Copy the key and three values.
     * @param entry Entry to copy.
     * @return This entry.
     */
    BootTrackKey171950& operator=(const BootTrackKey171950& entry)
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

/** Partial keyframe track with vtable D_171950 in main data; its constructor and destructor are out of line. */
class BootClass171950 : public BootClass171170
{
    public:
        /** @brief Construct the track. */
        BootClass171950();

        /** @brief Destroy the track. */
        virtual ~BootClass171950();

        /** @brief Replace the entry array with count new entries. @param count Number of entries. */
        virtual void func_001F1210(s32 count);

        /** @brief Install an entry array, set both counts, mark the array as installed and cache its span. @param count Number of entries; must be at least one. @param entries Entry array to install. */
        virtual void func_001F2F70(s32 count, void* entries);

        /** @brief Store the low nibble at offset 0x2A, then set flag bit 0 at offset 0x2B when either nibble is 4. @param value Value whose low four bits are stored. */
        virtual void func_001F12B0(s32 value);

        /** @brief Store the high nibble at offset 0x2A, then set flag bit 0 at offset 0x2B when either nibble is 4. @param value Value whose low four bits are stored. */
        virtual void func_001F1310(s32 value);

        /** @brief Read the signed cycle count at offset 0x18. @return The stored count. */
        virtual s32 func_001F1370() const;

        /** @brief Append an entry through slot 24. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @param key Sort value. @return The result of slot 24. */
        virtual s32 func_001F4FD0(const float* x, const float* y, const float* z, float key);

        /** @brief Default virtual handler that performs no work. */
        virtual void func_001EECA0();

        /** @brief Set an entry through slot 25. @param index Entry index. @param key Sort value. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @return The result of slot 25. */
        virtual s32 func_001F5000(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Insert an entry through slot 26. @param index Entry index. @param key Sort value. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @return The result of slot 26. */
        virtual s32 func_001F5030(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Default entry reader that returns zero. @param index Entry index. @param key Receives the sort value, or null. @param x Receives the first component, or null. @param y Receives the second component, or null. @param z Receives the third component, or null. @return Always 0. */
        virtual s32 func_001EED60(s32 index, float* key, float* x, float* y, float* z) const;

        /** @brief Add an entry through slot 27. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @param key Sort value. */
        virtual void func_001F5060(const float* x, const float* y, const float* z, float key);

        /** @brief Default virtual handler that performs no work. */
        virtual void func_001EED80();

        /** @brief Test whether an entry has exactly the given sort value. @param key Sort value to find. @return 1 when a matching entry exists, otherwise 0. */
        virtual s32 func_001F2F20(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void func_slot40(float* output) const = 0;

        /** @brief Wrap a value into the span between the first and last entry sort values. @param value Value to wrap. @return value reduced by a whole number of spans, or value unchanged when that number is zero. */
        virtual float func_001F2DE0(float value) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void func_slot48(float* output) const = 0;

        /** @brief Compute the span between the first and last entry sort values. @return The span, or 0.0f when fewer than two entries exist. */
        virtual float func_001F2ED0() const;

        /** @brief Store slot 30's value for a sort value. @param key Sort value. @param out Receives the value. */
        virtual void func_001F13F0(float key, float* output);

        /** @brief Read the signed entry count at offset 0x20. @return The stored count. */
        virtual s16 func_001F1380() const;

        /** @brief Delete the object through its virtual destructor. */
        virtual void func_001EECB0();

        /** @brief Read the entry array pointer at offset 4. @return The stored entry array, possibly null. */
        virtual void* func_001F1420() const;

        /** @brief Reset the entry array pointer, counters, indices, nibbles and ownership flags. */
        virtual void func_001F1180();

        /** @brief Read the signed halfword at offset 0x22. @return The stored halfword. */
        virtual s16 func_001F1390() const;

        /** @brief Default append handler. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @param key Sort value. @return Always 0. */
        virtual s32 func_001F13A0(const float* x, const float* y, const float* z, float key);

        /** @brief Default set handler. @param index Entry index. @param key Sort value. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @return Always 0. */
        virtual s32 func_001F13B0(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Default insert handler. @param index Entry index. @param key Sort value. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @return Always 0. */
        virtual s32 func_001F13C0(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Default add handler. @param x First component, or null. @param y Second component, or null. @param z Third component, or null. @param key Sort value. */
        virtual void func_001F13D0(const float* x, const float* y, const float* z, float key);

        /** @brief Report a fixed zero value for this receiver class. @return Always 0.0f. */
        virtual float func_001F13E0() const;

        /** @brief Find the first entry with the requested sort value. @param key Sort value to find. @return The entry's first component, or zero when no entry matches. */
        virtual float func_001F2E70(float key);

        // Pure virtual slot 0x80; only its position is known.
        virtual float func_slot80(float key) = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual s32 func_slot84(const float* x, const float* y, const float* z, float key) = 0;

        BootTrackKey171950* unk04;
        BootTrackKey171950 unk08;
        BootSequenceTail state;
};

/** Partial BootClass171950 with vtable D_171280 in main data. */
class BootClass171280 : public BootClass171950
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootClass171280()
        {
        }

        // Overrides of base slots; only their positions are known.
        virtual s32 func_001F4FD0(const float* x, const float* y, const float* z, float key);
        virtual s32 func_001F5000(s32 index, float key, const float* x, const float* y, const float* z);
        virtual s32 func_001F5030(s32 index, float key, const float* x, const float* y, const float* z);
        virtual s32 func_001EED60(s32 index, float* key, float* x, float* y, float* z) const;
        virtual void func_001F5060(const float* x, const float* y, const float* z, float key);
        virtual void func_001EED80();
        virtual void func_slot40(float* output) const;
        virtual void func_slot48(float* output) const;
        virtual void func_001F1180();
        virtual float func_slot80(float key);
        virtual s32 func_slot84(const float* x, const float* y, const float* z, float key);

        /** @brief Replace an indexed entry. @param index Entry index. @param key Sort value. @param x First component. @param y Second component. @param z Third component. @return One when the entry was stored. */
        virtual s32 func_001F3FE0(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Insert an entry at an index. @param index Entry index. @param key Sort value. @param x First component. @param y Second component. @param z Third component. @return One when the entry was stored. */
        virtual s32 func_001F3EC0(s32 index, float key, const float* x, const float* y, const float* z);

        /** @brief Store a single entry in the cached entry. @param x First component. @param y Second component. @param z Third component. @param key Sort value. */
        virtual void func_001F3E40(const float* x, const float* y, const float* z, float key);

        BootClass171270 unk2C;
        float unk4c;
        float unk50;
};

/** 0x54-byte pooled track with the Lib vtable D_177C70. */
class BootClass177C70 : public BootClass171280
{
    public:
        /** @brief Construct the track. */
        BootClass177C70();

        /** @brief Destroy the track. */
        virtual ~BootClass177C70();
};

/** Vector range with vtable D_171B98 in main data; its data comes before the vptr. */
class BootClass171B98
{
    public:
        /** @brief Install the vtable; the range is left unset. */
        BootClass171B98();

        FieldVec4B unk00;
        FieldVec4B unk10;
        FieldVec4B unk20;
        FieldVec4B unk30;
        float unk40;
        float unk44;
        float unk48;

        /**
         * @brief Set the range from two endpoint vectors and their tangents.
         * @param first First endpoint vector.
         * @param second First endpoint tangent.
         * @param third Second endpoint vector.
         * @param fourth Second endpoint tangent.
         * @param start Start key.
         * @param end End key.
         */
        virtual void func_001EFDD0(const FieldVec4A* first, const FieldVec4A* second, const FieldVec4A* third, const FieldVec4A* fourth, float start, float end);
};

/** 0x50-byte BootClass171B98 with vtable D_1710C0 in main data. */
class BootClass1710C0 : public BootClass171B98
{
    public:
        // Virtual slot 0xC; only its position is known.
        virtual void func_001EEC80();
};

/** 16-byte keyframe of BootClass171830; the value's fourth component is its key. */
struct BootTrackKey171830
{
    /** @brief Leave the value uninitialized. */
    BootTrackKey171830()
    {
    }

    FieldVec4B value;
};

/** 48-byte vector keyframe of BootClass1719E0: a BootClass171830 keyframe and two auxiliary vectors. */
struct BootTrackKey1719E0 : public BootTrackKey171830
{
    /** @brief Leave the vectors uninitialized. */
    BootTrackKey1719E0()
    {
    }

    FieldVec4B first;
    FieldVec4B second;
};

/** Partial vector keyframe track with vtable D_1719E0 in main data; its constructor and destructor are out of line. */
class BootClass1719E0 : public BootClass171170
{
    public:
        /** @brief Construct the track. */
        BootClass1719E0();

        /** @brief Destroy the track. */
        virtual ~BootClass1719E0();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void func_001F3030(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void func_001F0D10(s32 count, void* entries);

        /** @brief Set the lower mode nibble. @param mode Mode value. */
        virtual void func_001F0D60(s32 mode);

        /** @brief Set the upper mode nibble. @param mode Mode value. */
        virtual void func_001F0DC0(s32 mode);

        /** @brief Return the stored word at offset 0x40. @return Stored word. */
        virtual s32 func_001F0E20() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. @return Append status. */
        virtual s32 func_001F4CD0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Replacement status. */
        virtual s32 func_001F4D00(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Insertion status. */
        virtual s32 func_001F4D30(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. */
        virtual void func_001F4D60(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void func_001EED80();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 func_001F0E90(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void func_slot40(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float func_001F1010(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void func_slot48(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float func_001F0F00() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void func_001F0FC0(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 func_001F0E30() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void func_001EECB0();

        // Virtual slot 0x5C; only its position is known.
        virtual void* func_001F10B0();

        /** @brief Reset the sequence fields and set both modes to one. */
        virtual void func_001F0C80();

        // Virtual slot 0x64; only its position is known.
        virtual s16 func_001F0E40();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F0E50(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F0E60(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F0E70(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void func_001F0E80(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A func_001F0EE0() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A func_001F0F50(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A func_slot80(float key) const = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual s32 func_slot84(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key) = 0;

        void* unk04;
        u8 unk08[8];
        FieldVec4B unk10;
        FieldVec4B unk20;
        FieldVec4B unk30;
        BootSequenceTail state;
        u8 unk54[0xC];
};

/** Partial BootClass1719E0 with vtable D_1710D0 in main data. */
class BootClass1710D0 : public BootClass1719E0
{
    public:
        /** @brief Destroy the track. */
        virtual ~BootClass1710D0()
        {
        }

        // Overrides of base slots; only their positions are known.
        virtual s32 func_001F4CD0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
        virtual s32 func_001F4D00(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
        virtual s32 func_001F4D30(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);
        virtual s32 func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;
        virtual void func_001F4D60(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);
        virtual void func_001EED80();
        virtual void func_slot40(FieldVec4B* output) const;
        virtual void func_slot48(FieldVec4B* output) const;
        virtual void func_001F0C80();
        virtual FieldVec4A func_slot80(float key) const;
        virtual s32 func_slot84(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Replace an indexed keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first First auxiliary vector. @param second Second auxiliary vector. @return Nonzero when the keyframe was stored. */
        virtual s32 func_001EF7D0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert a keyframe at an index. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first First auxiliary vector. @param second Second auxiliary vector. @return Nonzero when the keyframe was stored. */
        virtual s32 func_001F45F0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Store a single keyframe in the cached vectors. @param value Keyframe value. @param first First auxiliary vector. @param second Second auxiliary vector. @param key Key. */
        virtual void func_001F4560(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        BootClass1710C0 unk60;
        FieldVec4B unkB0;
        FieldVec4B unkC0;
};

/** 0xD0-byte pooled track with vtable D_1711D0 in main data. */
class BootClass1711D0 : public BootClass1710D0
{
    public:
        /** @brief Construct the track. */
        BootClass1711D0();

        /** @brief Destroy the track. */
        virtual ~BootClass1711D0();

        // Overrides of base slots; only their positions are known.
        virtual void func_001EECB0();

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
class BootClass171A70 : public BootClass171170
{
    public:
        /** @brief Construct the track. */
        BootClass171A70();

        /** @brief Destroy the track. */
        virtual ~BootClass171A70();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void func_001F4A10(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void func_001F5FB0(s32 count, void* entries);

        /** @brief Set the lower mode nibble. @param mode Mode value. */
        virtual void func_001F47F0(s32 mode);

        /** @brief Set the upper mode nibble. @param mode Mode value. */
        virtual void func_001F4AC0(s32 mode);

        /** @brief Return the stored word at offset 0x30. @return Stored word. */
        virtual s32 func_001F4B20() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. @return Append status. */
        virtual s32 func_001F4B60(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Replacement status. */
        virtual s32 func_001F4BA0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Insertion status. */
        virtual s32 func_001F4BE0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. */
        virtual void func_001F4C20(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void func_001EED80();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 func_001F5F60(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void func_slot40(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float func_001F5E20(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void func_slot48(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float func_001F5F10() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void func_001F4C70(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 func_001F4B30() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void func_001EECB0();

        // Virtual slot 0x5C; only its position is known.
        virtual void* func_001F4CC0();

        // Virtual slot 0x60; only its position is known.
        virtual void func_001F4980();

        // Virtual slot 0x64; only its position is known.
        virtual s16 func_001F4B40();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F4B50(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F4B90(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F4BD0(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void func_001F4C10(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A func_001F4C50() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A func_001F5EB0(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A func_slot80(float key) const = 0;

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
        virtual void func_slot40(FieldVec4B* output) const;
        virtual void func_slot48(FieldVec4B* output) const;
        virtual FieldVec4A func_slot80(float key) const;
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
class BootClass171680 : public BootClass171170
{
    public:
        /** @brief Construct the track. */
        BootClass171680();

        /** @brief Destroy the track. */
        virtual ~BootClass171680();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void func_001F5950(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void func_001F5A00(s32 count, void* entries);

        /** @brief Set the lower mode nibble. @param mode Mode value. */
        virtual void func_001F4730(s32 mode);

        /** @brief Set the upper mode nibble. @param mode Mode value. */
        virtual void func_001F5A50(s32 mode);

        /** @brief Return the stored word at offset 0x40. @return Stored word. */
        virtual s32 func_001F5AB0() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. @return Append status. */
        virtual s32 func_001F5AF0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Replacement status. */
        virtual s32 func_001F5B30(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Insertion status. */
        virtual s32 func_001F5B70(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. */
        virtual void func_001F5BB0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void func_001EED80();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 func_001F5BE0(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void func_slot40(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float func_001F5D60(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void func_slot48(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float func_001F5C50() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void func_001F5D10(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 func_001F5AC0() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void func_001EECB0();

        // Virtual slot 0x5C; only its position is known.
        virtual void* func_001F5E00();

        // Virtual slot 0x60; only its position is known.
        virtual void func_001F58C0();

        // Virtual slot 0x64; only its position is known.
        virtual s16 func_001F5AD0();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F5AE0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F5B20(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F5B60(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void func_001F5BA0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A func_001F5C30() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A func_001F5CA0(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A func_slot80(float key) const = 0;

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
        virtual void func_slot40(FieldVec4B* output) const;
        virtual void func_slot48(FieldVec4B* output) const;
        virtual FieldVec4A func_slot80(float key) const;
        virtual void func_slot84();

        u8 unk54[0x3C];
};

/** 8-byte packed keyframe of BootClass171710: three halfword values and a halfword key. */
struct BootTrackKey171710
{
    /**
     * @brief Copy the values and key.
     * @param entry Entry to copy.
     * @return This entry.
     */
    BootTrackKey171710& operator=(const BootTrackKey171710& entry)
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

/** Partial keyframe track with vtable D_171710 in main data; its constructor and destructor are out of line. */
class BootClass171710 : public BootClass171170
{
    public:
        /** @brief Construct the track. */
        BootClass171710();

        /** @brief Destroy the track. */
        virtual ~BootClass171710();

        /** @brief Allocate storage for the requested keyframe count. @param count Requested keyframe count. */
        virtual void func_001F5360(s32 count);

        /** @brief Bind an external keyframe array. @param count Keyframe count. @param entries External keyframe storage. */
        virtual void func_001F5400(s32 count, void* entries);

        /** @brief Set the lower mode nibble. @param mode Mode value. */
        virtual void func_001F4790(s32 mode);

        /** @brief Set the upper mode nibble. @param mode Mode value. */
        virtual void func_001F5460(s32 mode);

        /** @brief Return the stored word at offset 0x10. @return Stored word. */
        virtual s32 func_001F54C0() const;

        /** @brief Append a vector keyframe. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. @return Append status. */
        virtual s32 func_001F5500(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default track hook. */
        virtual void func_001EECA0();

        /** @brief Replace an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Replacement status. */
        virtual s32 func_001F5540(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Insert an indexed vector keyframe. @param index Keyframe index. @param key Sort key. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @return Insertion status. */
        virtual s32 func_001F5580(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Read an indexed vector keyframe. @param index Keyframe index. @param key Receives the sort key. @param value Receives the value. @param first Receives the first auxiliary vector. @param second Receives the second auxiliary vector. @return Nonzero when the keyframe is available. */
        virtual s32 func_001EED60(s32 index, float* key, FieldVec4B* value, FieldVec4B* first, FieldVec4B* second) const;

        /** @brief Add a vector keyframe through the track implementation. @param value Keyframe value. @param first Optional first auxiliary vector. @param second Optional second auxiliary vector. @param key Sort key. */
        virtual void func_001F55C0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Run the default update hook. */
        virtual void func_001EED80();

        /** @brief Test whether the track contains the supplied key. @param key Key to find. @return Nonzero when the key exists. */
        virtual s32 func_001F55F0(float key) const;

        // Pure virtual slot 0x40; only its position is known.
        virtual void func_slot40(FieldVec4B* output) const = 0;

        /** @brief Wrap a key into the stored key range. @param key Key to wrap. @return Wrapped key. */
        virtual float func_001F5810(float key) const;

        // Pure virtual slot 0x48; only its position is known.
        virtual void func_slot48(FieldVec4B* output) const = 0;

        /** @brief Return the span between the first and last keys. @return Key span, or zero when fewer than two keys are stored. */
        virtual float func_001F5670() const;

        /** @brief Evaluate the vector track at a key. @param key Evaluation key. @param output Receives the evaluated vector. */
        virtual void func_001F57C0(float key, FieldVec4B* output) const;

        /** @brief Return the stored keyframe count. @return Keyframe count. */
        virtual s16 func_001F54D0() const;

        /** @brief Return a pooled track or delete an ordinary track. */
        virtual void func_001EECB0();

        // Virtual slot 0x5C; only its position is known.
        virtual void* func_001F58B0();

        // Virtual slot 0x60; only its position is known.
        virtual void func_001F52D0();

        // Virtual slot 0x64; only its position is known.
        virtual s16 func_001F54E0();

        /** @brief Handle a vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F54F0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F5530(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle an indexed vector set with a key; the base implementation ignores it. @return Handler result. */
        virtual s32 func_001F5570(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second);

        /** @brief Handle a vector set with a key; the base implementation ignores it. */
        virtual void func_001F55B0(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key);

        /** @brief Return a zero vector. @return Zero vector. */
        virtual FieldVec4A func_001F5650() const;

        /** @brief Return the value of the keyframe with the supplied key. @param key Key to find. @return Keyframe value, or zero when the key is absent. */
        virtual FieldVec4A func_001F56D0(float key) const;

        // Pure virtual slot 0x80; only its position is known.
        virtual FieldVec4A func_slot80(float key) const = 0;

        // Pure virtual slot 0x84; only its position is known.
        virtual void func_slot84() = 0;

        void* unk04;
        u8 unk08[8];
        BootSequenceTail state;
};

/** 0x2C-byte pooled track with the Lib vtable D_1730F0. */
class BootClass1730F0 : public BootClass171710
{
    public:
        /** @brief Construct the track. */
        BootClass1730F0();

        /** @brief Destroy the track. */
        virtual ~BootClass1730F0();

        // Lib implementations of the pure slots; only their positions are known.
        virtual void func_slot40(FieldVec4B* output) const;
        virtual void func_slot48(FieldVec4B* output) const;
        virtual FieldVec4A func_slot80(float key) const;
        virtual void func_slot84();

        u8 unk24[8];
};

extern "C" {
s32 func_001EC010(BootTrackPool<BootClass177F70>* pool, s32 count);
void func_001EC490(BootTrackPool<BootClass177F70>* pool);
s32 func_001EC630(BootTrackPool<BootClass1714D0>* pool, s32 count);
void func_001ECAC0(BootTrackPool<BootClass1714D0>* pool);
s32 func_001ECC60(BootTrackPool<BootClass177EE0>* pool, s32 count);
void func_001ED060(BootTrackPool<BootClass177EE0>* pool);
s32 func_001ED200(BootTrackPool<BootClass177C70>* pool, s32 count);
s32 func_001ED7B0(BootTrackPool<BootClass1711D0>* pool, s32 count);
void func_001EDBC0(BootTrackPool<BootClass1711D0>* pool);
s32 func_001EDD60(BootTrackPool<BootClass177BE0>* pool, s32 count);
void func_001EE0C0(BootTrackPool<BootClass177BE0>* pool);
s32 func_001EE250(BootTrackPool<BootClass174440>* pool, s32 count);
void func_001EE5C0(BootTrackPool<BootClass174440>* pool);
s32 func_001EE760(BootTrackPool<BootClass1730F0>* pool, s32 count);
void func_001EEAE0(BootTrackPool<BootClass1730F0>* pool);
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
s32 func_432310(BootModeOwner0910* owner, u32 mode, BootTransferRequest0AF0* request);
s32 func_432270(BootModeOwner0910* owner, s32 mode, s32* result);
extern BootClass178DD0* D_001B6614;
void* func_100B00(u32 size, s32 flags);
char* func_13C948(char* destination, const char* source);
void* func_13A4C0(void* destination, const void* source, u32 size);
extern const char D_205100[];
extern const char D_205980[];
extern const char D_205988[];
s32 func_431F90(BootModeOwner0910* owner, s32 slot, char* name, s32 first, s32 second, u8* buffer);
}

#endif
