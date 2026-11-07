#ifndef SO3_OVERLAYS_BOOT_PROGRAM_H
#define SO3_OVERLAYS_BOOT_PROGRAM_H

#include "overlays/boot/boot.h"
#include "overlays/boot/title_menu.h"
#include "overlays/boot/trophy_card.h"
#include "angle.h"

/** Aspect ratio of a 4:3 television picture. */
#define BOOT_ASPECT_STANDARD 1.3333334f

/** Aspect ratio of a 16:9 widescreen picture. */
#define BOOT_ASPECT_WIDE 1.7777778f

/** 480 / 448: stretches the 448-line frame to the 480 lines of a full NTSC picture. */
#define BOOT_FRAME_LINE_SCALE 1.0714285f

/** Horizontal field of view on a 4:3 picture: 90 degrees. */
#define BOOT_FOV_STANDARD HALF_PI

/** Horizontal field of view on a widescreen picture: 105 degrees. */
#define BOOT_FOV_WIDE 1.8325958f

/** Pixel aspect that shows a LibDisplayArea as a 4:3 picture. */
#define BOOT_PIXEL_ASPECT_STANDARD(area) ((BOOT_ASPECT_STANDARD * (BOOT_FRAME_LINE_SCALE * (float)(area).height)) / (float)(area).width)

/** Pixel aspect that shows a LibDisplayArea as a 16:9 picture. */
#define BOOT_PIXEL_ASPECT_WIDE(area) ((BOOT_ASPECT_WIDE * BOOT_PIXEL_ASPECT_STANDARD(area)) / BOOT_ASPECT_STANDARD)

/**
 * Popup with vtable D_171070 in main data that tells the player to fix the PlayStation BB Unit while the resident
 * loader reports an error, and removes itself once the error clears.
 */
class BootUnitErrorPopup : public LibListObject
{
    public:
        /**
         * @brief Start enabled, with nothing shown.
         * @param owner Program whose message bank the popup uses.
         */
        BootUnitErrorPopup(class BootProgram* owner)
        {
            program = owner;
            container = 0;
            text = 0;
            panel = 0;
            enabled = 1;
        }

        /** @brief Destroy the object. */
        virtual ~BootUnitErrorPopup();

        /** @brief Release the owned objects, then queue this object for deletion. */
        virtual void destroy();

        /** @brief Show the popup while the loader reports a BB Unit error, and remove it once the error clears. */
        virtual void update();

        /**
         * @brief Turn the popup on or off.
         * @param value Nonzero to allow the popup.
         */
        virtual void set_enabled(u8 value);

        /** Program whose message bank the popup uses. */
        class BootProgram* program;

        u8 enabled;
        u8 unk19[3];
        LibContainer* container;
        LibTextWidget* text;

        /** Frame behind the text. */
        LibPanel* panel;
};

/** Start of resource 3, the main executable as an ELF file: the ELF header, then the first program header. */
struct BootProgramImage
{
    u8 elf_header[0x34];

    /** First program header's segment type. */
    u32 segment_type;

    /** File offset of the first segment, the executable's code. */
    u32 code_offset;
};

/** Boot's pad and memory card monitor, with vtable D_171030 in main data; samples both every frame. */
class BootInput : public LibListObject
{
    public:
        /** @brief Clear the card states and start querying the cards. */
        BootInput();

        /** @brief Destroy the object. */
        virtual ~BootInput();

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
class BootOpeningMovie : public LibListObject
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
        ResidentHeap* movie_heap;
        LibMoviePlayer* player;
        BootImage* caption_image;
        LibContainer* container;
        LibTextWidget* caption_text;
};

/** Blocks decoded from the boot program's common UI resource. */
enum BootCommonUiBlock
{
    BOOT_COMMON_UI_MESSAGES,
    BOOT_COMMON_UI_CAPTIONS,
    BOOT_COMMON_UI_IMAGES,
    BOOT_COMMON_UI_BLOCK_COUNT
};

/** 0x20-byte loader for resource 0x26, with vtable D_171090 in main data. */
class BootResourceLoader : public LibListObject
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

        /** @brief Body of update_projection_aspect, which the program's own functions inline. */
        inline void apply_projection_aspect();

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

        LibCameraContext* display;
        LibCamera* projection;
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
        /** Cleared on construction and when run starts; nothing in boot reads it. */
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

/**
 * Resident DMA callbacks object g_display_callbacks, with vtable D_0014FDE0 in main data; lib_initialize creates it
 * and both callbacks do nothing. It records the current display.
 */
struct BootResidentDisplay
{
    void* vtable;
    LibCameraContext* display;
};

#endif
