#ifndef SO3_OVERLAYS_BOOT_TROPHY_VIEWER_H
#define SO3_OVERLAYS_BOOT_TROPHY_VIEWER_H

#include "types.h"
#include "overlays/boot/boot.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/clip_region.h"

/**
 * @brief Return the system settings in the resident save data.
 * @return System settings.
 */
static inline LibSystemSettings* boot_settings()
{
    return (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);
}

/**
 * @brief Read a selected bit in the resource's flag array.
 * @param bits Resource storage containing the flag array.
 * @param index Unsigned flag index.
 * @return One if the bit is set, otherwise zero.
 */
static inline s32 resource_bit(LibTrophyFlags* bits, u32 index)
{
    return (bits->flags.bytes[index / 8] >> (index % 8)) & 1;
}

#ifdef __cplusplus

class LibStringLabel;

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

/** 0xF10-byte record the Battle Trophies viewer keeps for each of the 300 trophies. */
struct BootTrophyRecord
{
    /**
     * @brief Copy a record; declared only, which keeps the array header on new[] and delete[].
     * @param other Record to copy.
     * @return This record.
     */
    BootTrophyRecord& operator=(const BootTrophyRecord& other);

    /** Checksum over the rest of the record, which lib_trophy_record_decode checks after decoding it. */
    u32 checksum;

    BootTrophyTime time;

    /** Key the game gave this trophy; a record whose key doesn't match is treated as forged. */
    u32 key;

    /** 64x96 picture, five bits per pixel, packed from the lowest bit up. */
    u8 image[0xF00];
};

/**
 * Battle Trophies viewer, with vtable D_171CD0 in main data. It loads the trophy data from a memory card slot and
 * lists the 300 battle trophies.
 */
class BootBattleTrophyViewer : public LibListObject
{
    public:
        /** @brief Start loading resource 0x2B, clear the owned objects and build the three palettes. */
        BootBattleTrophyViewer();

        /** @brief Release the loaded data and every owned object. */
        virtual ~BootBattleTrophyViewer();

        /**
         * @brief Report the list kind used when registration requests the default.
         * @return Four.
         */
        virtual s32 get_default_list_kind();

        /** @brief Run the viewer: choose a memory card slot, load its trophy data, then browse the trophy grid. */
        virtual void update();

        /** @brief Destroy every owned object and release the per-trophy allocations. */
        void release();

        /**
         * @brief Build a trophy's texture from the picture template, the trophy's packed picture and the first palette.
         * @param record Trophy record holding the picture.
         * @param texture Texture resource to fill.
         * @param index Trophy index.
         */
        void build_trophy_texture(const BootTrophyRecord* record, LibImageResource* texture, s32 index);

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

        /** Block of random size allocated after the resource and only freed, so the heap layout varies. */
        u8* heap_padding;

        /** Resource 0x2B. */
        u8* resource_data;

        /** Decoded image blocks of resource 0x2B. */
        u8* image_blocks[3];

        /** Screen images built from the image blocks. */
        BootImage* images[10];

        /** Screen state. */
        s32 step;

        /** Number of resource 0x2B's images decoded so far. */
        u8 images_loaded;

        /** Memory card slot being read: zero for slot 1, one for slot 2. */
        u8 slot;

        /** Nonzero to list the trophies newest first; see sort_trophies. */
        u8 by_time;

        /** Nonzero while the card in each slot can be read, as last shown. */
        u8 slot_ready[2];

        u8 unk59[3];

        /** Column of the cursor in the grid of eight. */
        s32 cursor_column;

        /** Row of the cursor among the visible rows. */
        s32 cursor_row;

        /** First visible row. */
        s32 first_row;

        /** Scroll animation step: counts up to 5 scrolling down, down to -5 scrolling up, zero when still. */
        s32 scroll_step;

        /** Number of rows in the grid. */
        s32 row_count;

        /** Frames before the cursor reads input again; counts down to zero. */
        s32 input_delay;

        /** Seconds the rank title has been shown. */
        float rank_timer;

        /** Highest rank title earned. */
        s32 rank;

        /** Rank title being shown; cycles down from rank. */
        s32 shown_rank;

        /** Frames before the next page jump. */
        s32 page_delay;

        u8 unk84[4];
        LibContainer* container;

        /** Prompt and status message. */
        LibTextWidget* message_text;

        LibSelectionCursor* cursor;

        /** Slot 1 choice. */
        LibTextWidget* slot1_text;

        /** Slot 2 choice. */
        LibTextWidget* slot2_text;

        /** Label showing the number of the trophy under the cursor. */
        LibStringLabel* number_label;

        /** Name of the trophy under the cursor. */
        LibTextWidget* name_text;

        /** When the trophy under the cursor was earned. */
        LibTextWidget* date_text;

        /** "Percentage Achieved" line (message 0x6A). */
        LibTextWidget* percentage_text;

        /** Sort order. */
        LibTextWidget* sort_text;

        /** Shows how far the grid is scrolled. */
        LibListIndicator* scroll_indicator;

        /** Rank title, shown once enough trophies are earned. */
        LibTextWidget* rank_text;

        /** Clips the trophy grid to the area between the header and footer. */
        LibClipRegion* grid_clip;

        /** Restores drawing to the whole display after the grid. */
        LibClipRegion* screen_clip;

        /** Loading bar, faded out once loading finishes. */
        BootProgressBar* progress_bar;

        /** Seconds spent loading. */
        float load_time;

        /** Opacity of the loading bar as it fades out. */
        float bar_alpha;

        /** Nonzero while the loading bar fades out. */
        u8 bar_fading;

        /** Number of the selected trophy, as text. */
        char number_text[9];

        /** Trophy number shown at each list position. */
        s16 order[LIB_TROPHY_COUNT];

        u8 unk32E[2];

        /** Picture of each trophy. */
        BootImage* trophy_images[LIB_TROPHY_COUNT];

        /** Record of each trophy, as read from the memory card. */
        BootTrophyRecord* records;

        /** Texture built for each earned trophy. */
        LibImageResource* textures[LIB_TROPHY_COUNT];

        /** How far each trophy picture has turned from its back to its front, zero when unrevealed. */
        float flip_progress[LIB_TROPHY_COUNT];

        /** Next trophy to start turning over as the screen opens. */
        s32 reveal_index;

        /** Number of trophies earned. */
        s32 earned_count;

        /** Three 32-color grey-blue ramps, stored in the GS swizzled CLUT order. */
        u32 palettes[3][32];

        u8 unk12CC[0x280];
};
#endif

#endif
