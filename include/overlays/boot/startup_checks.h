#ifndef SO3_OVERLAYS_BOOT_STARTUP_CHECKS_H
#define SO3_OVERLAYS_BOOT_STARTUP_CHECKS_H

#include "overlays/boot/boot.h"

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
class BootStartupChecks : public LibListObject
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

        LibContainer* container;
        LibTextWidget* text;
};

#endif
