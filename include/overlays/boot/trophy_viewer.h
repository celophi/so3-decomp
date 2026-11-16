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

    u32 checksum;
    BootTrophyTime time;
    u32 key;
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

        u8* heap_padding;
        u8* resource_data;
        u8* image_blocks[3];
        BootImage* images[10];
        s32 step;
        u8 images_loaded;
        u8 slot;
        u8 by_time;
        u8 slot_ready[2];
        u8 unk59[3];
        s32 cursor_column;
        s32 cursor_row;
        s32 first_row;
        s32 scroll_step;
        s32 row_count;
        s32 input_delay;
        float rank_timer;
        s32 rank;
        s32 shown_rank;
        s32 page_delay;
        u8 unk84[4];
        LibContainer* container;
        LibTextWidget* message_text;
        LibSelectionCursor* cursor;
        LibTextWidget* slot1_text;
        LibTextWidget* slot2_text;
        LibStringLabel* number_label;
        LibTextWidget* name_text;
        LibTextWidget* date_text;
        LibTextWidget* percentage_text;
        LibTextWidget* sort_text;
        LibListIndicator* scroll_indicator;
        LibTextWidget* rank_text;
        LibClipRegion* grid_clip;
        LibClipRegion* screen_clip;
        BootProgressBar* progress_bar;
        float load_time;
        float bar_alpha;
        u8 bar_fading;
        char number_text[9];
        s16 order[LIB_TROPHY_COUNT];
        u8 unk32E[2];
        BootImage* trophy_images[LIB_TROPHY_COUNT];
        BootTrophyRecord* records;
        LibImageResource* textures[LIB_TROPHY_COUNT];
        float flip_progress[LIB_TROPHY_COUNT];
        s32 reveal_index;
        s32 earned_count;
        u32 palettes[3][32];
        u8 unk12CC[0x280];
};
#endif

#endif
