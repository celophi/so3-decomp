#ifndef SO3_OVERLAYS_BOOT_INSTALLER_H
#define SO3_OVERLAYS_BOOT_INSTALLER_H

#include "overlays/boot/text_001DD3C0.h"

/** Resources the installer loads. */
enum BootInstallResource
{
    /** Two images: the screen sprite sheet and its banner. */
    BOOT_RES_SCREEN_IMAGES = 0x2A,
    /** SYSTEM.CNF, icon.sys and the icon written to the BB Unit partition. */
    BOOT_RES_SYSTEM_FILES = 0x2D,
    /** PlayStation BB Navigator icons and title file. */
    BOOT_RES_NAVIGATOR_FILES = 0x2E,
    /** The eight images shown with the battle-system tips. */
    BOOT_RES_TIP_IMAGES = 0x2F,
    BOOT_RES_SOUND = 0x427
};

/**
 * Boot screen that offers to install the game on the PlayStation BB Unit (hard disk), with vtable D_170D30
 * in main data. It asks yes/no, checks the unit and its free space, writes the partition files while
 * showing a progress bar and battle-system tips, then hands over to the next boot stage.
 */
class BootInstaller : public LibListObject
{
    public:
        /** @brief Allocate the boot buffers and clear the owned objects. */
        BootInstaller();

        /** @brief Release the owned objects and buffers. */
        virtual ~BootInstaller();

        /**
         * @brief Report the list kind used when registration requests the default.
         * @return Four.
         */
        virtual s32 get_default_list_kind();

        /** @brief Advance the install sequence: load the screen, ask, check the BB Unit, install, then hand over. */
        virtual void update();

        /**
         * @brief Replace the tip image with block @p index of the tip image resource.
         * @param index Tip image to decode.
         */
        void show_tip_image(s32 index);

        /** @brief Create the yes/no choice images and pulse the selected one; release them once installing starts. */
        void update_choice_images();

        /** @brief Create the four screen images once, then place them for the 4:3 or widescreen layout. */
        void place_screen_images();

        u8* screen_image_data;
        u8* sound_data;
        u8* screen_image_buffers[2];
        u8* system_file_data;
        u8* navigator_file_data;
        u8* system_file_buffers[3];
        u8* navigator_file_buffers[3];
        u8* install_buffer;
        BootImage* images[20];
        BootProgressBar* progress_bar;
        BootImage* tip_image;
        u8* tip_image_buffer;
        u8* tip_image_data;

        /** Current step of the install sequence. */
        s32 step;

        /** Step taken when the player answers no or cancels. */
        s32 no_step;

        /** Step taken when the player answers yes. */
        s32 yes_step;

        u8 selection;
        u8 screen_images_loaded;
        u8 sound_started;
        u8 exiting;

        /** Nonzero while the selected choice image grows back to full size. */
        u8 choice_growing;

        u8 unkb9[3];
        u8* unkbc;

        /** Install size used as the progress denominator. */
        s32 install_total;

        /** Next tip to show. */
        s32 tip_index;

        /** Progress percentage at which the next tip is shown. */
        s32 next_tip_percent;

        s32 menu_frames;
        s32 wait_frames;

        /** 0x200-byte buffer the resident install code fills with the icon.sys header. */
        u8* icon_header;

        LibContainer* container;
        LibTextWidget* message_text;
        LibTextWidget* progress_text;
        LibTextWidget* tip_text;
        LibSelectionCursor* cursor;
};

#endif
