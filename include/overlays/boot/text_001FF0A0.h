#ifndef SO3_OVERLAYS_BOOT_TEXT_001FF0A0_H
#define SO3_OVERLAYS_BOOT_TEXT_001FF0A0_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/boot/text_001DD3C0.h"

class BootClass175140;

/** Time a trophy was earned, laid out like the console clock: stat, second, minute, hour, pad, day, month, year. */
struct BootTrophyTime
{
    u8 stat;
    u8 second;
    u8 minute;
    u8 hour;
    u8 pad;
    u8 day;
    u8 month;
    u8 year;
};

/** Partial 0xF10-byte record the Battle Trophies viewer keeps for each of the 300 trophies. */
struct BootTrophyRecordF10
{
    /** @brief Leave the record uninitialized. */
    BootTrophyRecordF10()
    {
    }

    u8 unk00[4];
    BootTrophyTime time;
    u32 unk0C;

    /** 64x96 picture, five bits per pixel, packed from the lowest bit up. */
    u8 image[0xF00];
};

/**
 * Battle Trophies viewer, with vtable D_171CD0 in main data. It loads the trophy data from a memory card slot and
 * lists the 300 battle trophies.
 */
class BootBattleTrophyViewer : public BootClass170E90
{
    public:
        /** @brief Start loading resource 0x2B, clear the owned objects and build the three palettes. */
        BootBattleTrophyViewer();

        /** @brief Release the loaded data and every owned object. */
        virtual ~BootBattleTrophyViewer();

        /** @brief Report the list kind used when registration requests the default. @return Four. */
        virtual s32 get_default_list_kind();

        /** @brief Run the viewer. */
        virtual void update();

        /** @brief Destroy every owned object and release the per-trophy allocations. */
        void release();

        /**
         * @brief Build a trophy's texture from the picture template, the trophy's packed picture and the first palette.
         * @param record Trophy record holding the picture.
         * @param texture Texture resource to fill.
         * @param index Trophy index.
         */
        void build_trophy_texture(const BootTrophyRecordF10* record, BootTextureResource* texture, s32 index);

        /**
         * @brief Reset the display order to trophy number order, then optionally sort it newest first.
         * @param newest_first Nonzero to sort by the time each trophy was earned; unearned ones go last.
         */
        void sort_trophies(u8 newest_first);

        /**
         * @brief Check the trophy data and create a picture for each trophy: its own picture when earned, a blank
         * frame otherwise.
         * @return One when done, or zero when a trophy record fails its check, after clearing that trophy.
         */
        s32 create_trophy_images();

        /** @brief Scroll the grid, show the cursor's trophy number, turn newly shown pictures and grow the selected one. */
        void update_grid();

        /** @brief Create the two screen images once the pictures load, place them for the screen shape and fade out the bar. */
        void update_images();

        u8* unk14;

        /** Resource 0x2B. */
        u8* resource_data;

        u8* unk1C[3];
        BootImage* unk28[10];
        s32 unk50;
        u8 unk54;

        /** Memory card slot being read: zero for slot 1, one for slot 2. */
        u8 slot;

        /** Nonzero to list the trophies newest first; see sort_trophies. */
        u8 by_time;

        u8 unk57;
        u8 unk58;
        u8 unk59[3];

        /** Column of the cursor in the grid of eight. */
        s32 cursor_column;

        /** Row of the cursor among the visible rows. */
        s32 cursor_row;

        /** First visible row. */
        s32 first_row;

        /** Scroll animation step: counts up to 5 scrolling down, down to -5 scrolling up, zero when still. */
        s32 scroll_step;

        s32 unk6C;
        u8 unk70[0x10];
        s32 unk80;
        u8 unk84[4];
        BootClass178660* unk88;
        BootClass170E90* unk8C;
        BootClass170E90* unk90;
        BootClass170E90* unk94;
        BootClass170E90* unk98;

        /** Label showing the number of the trophy under the cursor. */
        BootClass175140* number_label;

        BootClass170E90* unkA0;
        BootClass170E90* unkA4;
        BootClass170E90* unkA8;
        BootClass170E90* unkAC;
        BootClass170E90* unkB0;
        BootClass170E90* unkB4;
        BootClass171DD0* unkB8;
        BootClass171DD0* unkBC;

        /** Loading bar, faded out once loading finishes. */
        BootProgressBar* unkC0;

        u8 unkC4[4];

        /** Opacity of the loading bar as it fades out. */
        float bar_alpha;

        /** Nonzero while the loading bar fades out. */
        u8 bar_fading;

        /** Number of the selected trophy, as text. */
        char number_text[9];

        /** Trophy number shown at each list position. */
        s16 order[300];

        u8 unk32E[2];

        /** Picture of each trophy. */
        BootImage* trophy_images[300];

        /** Record of each trophy, as read from the memory card. */
        BootTrophyRecordF10* records;

        /** Texture built for each earned trophy. */
        BootTextureResource* textures[300];

        float unkC94[300];
        s32 unk1144;

        /** Number of trophies earned. */
        s32 earned_count;

        /** Three 32-color grey-blue ramps, stored in the GS swizzled CLUT order. */
        u32 palettes[3][32];

        u8 unk12CC[0x280];
};
#endif

#endif
