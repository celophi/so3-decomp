#ifndef SO3_OVERLAYS_BOOT_NEW_GAME_SETTINGS_H
#define SO3_OVERLAYS_BOOT_NEW_GAME_SETTINGS_H

#include "overlays/boot/boot.h"
#include "overlays/boot/title_menu.h"

/** Partial model object with vtable D_170F30 in main data. */
class BootClass170F30 : public LibModel
{
    public:
        /** @brief Destroy the model object. */
        virtual ~BootClass170F30();

        /**
         * @brief Negate the matrix's second vector, then apply the matrix through the Lib model.
         * @param matrix Matrix supplied by the caller.
         * @param context Opaque caller context.
         */
        virtual void build_packet(const void* matrix, void* context);
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
class BootNewGameSettings : public LibListObject
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
        LibAnimation* girl_animations[6];

        LibAnimationTarget* animation_targets[6];

        /** Installed in g_floor_query while the screen runs, so Lib sees a floor at height zero. */
        BootFlatFloor flat_floor;

        LibContainer* container;

        /** Description of the selected option. */
        LibTextWidget* description_text;

        LibSelectionCursor* cursor;
};

#endif
