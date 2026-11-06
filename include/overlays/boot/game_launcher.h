#ifndef SO3_OVERLAYS_BOOT_GAME_LAUNCHER_H
#define SO3_OVERLAYS_BOOT_GAME_LAUNCHER_H

#include "overlays/boot/boot.h"

/**
 * Starts the game, with vtable D_171CB0 in main data. On a new game with Dolby Pro Logic II output it first plays
 * movie 13, then loads resource 0x42B and hands it to the boot program to run next.
 */
class BootGameLauncher : public LibListObject
{
    public:
        /** @brief Clear the state and allocate the 0x12000-byte work buffer. */
        BootGameLauncher();

        /** @brief Release the player, its heap and the work buffer. */
        virtual ~BootGameLauncher();

        /** @brief Run the launch steps: seed, movie, load, hand over. */
        virtual void update();

        /** Resource 0x42B, the program to run next. */
        u8* program;

        u8* buffer;
        s32 step;
        s32 timer;
        ResidentHeap* movie_heap;
        LibMoviePlayer* player;
};

#endif
