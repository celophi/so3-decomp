#ifndef SO3_OVERLAYS_LIB_WIDGET_AGGREGATE_H
#define SO3_OVERLAYS_LIB_WIDGET_AGGREGATE_H

#include "types.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_00419A70.h"

class LibClass1721F0;

/** One row of a LibClass1721F0 list; each menu supplies its own row class. */
class LibAggregateRow
{
public:
    virtual ~LibAggregateRow();

    /**
     * @brief Show or hide the row's widgets.
     * @param owner List that owns the row.
     * @param visible Nonzero to show the row.
     */
    virtual void set_visible(LibClass1721F0* owner, u8 visible) = 0;

    /**
     * @brief Fill the row for an entry.
     * @param owner List that owns the row.
     * @param index Entry index.
     */
    virtual void refresh_row(LibClass1721F0* owner, s32 index) = 0;

    /**
     * @brief Move the row.
     * @param owner List that owns the row.
     * @param x Horizontal position.
     * @param y Vertical position.
     */
    virtual void position_row(LibClass1721F0* owner, float x, float y) = 0;

    /**
     * @brief Read the row's float setting.
     * @param owner List that owns the row.
     * @return The setting.
     */
    virtual float get_setting(LibClass1721F0* owner) = 0;
};

/** Panel with vtable D_1722E0 in main data; the frame of a widget aggregate. */
class LibClass1722E0 : public LibPanel
{
public:
    /** @brief Initialize the panel. */
    LibClass1722E0();

    virtual ~LibClass1722E0();

    /**
     * @brief Set the frame up at the origin.
     * @param width Frame width.
     * @param height Frame height.
     * @return True on success.
     */
    bool init_frame(float width, float height)
    {
        if (!lib_panel_init_rectangle(this, 0, 0.0f, 0.0f, width, height, 88.0f))
        {
            return false;
        }

        unk8c = 0;
        return true;
    }
};

/** Widget aggregate with grid settings and selection callbacks, with vtable D_1723F0 in main data after its data. */
class LibClass1723F0
{
public:
    LibClass1722E0 unk00;
    ItemCreationClass1746A0 unk90;
    ItemCreationClass1746A0 unke4;
    LibListIndicator unk138;
    ItemCreationClass175030 unk190;
    ItemCreationClass172600 unk20c;
    ItemCreationClass172870 unk260;
    float page_repeat_delay[2];
    float unk2c0;
    float unk2c4;
    float unk2c8;
    float unk2cc;
    float unk2d0;
    float unk2d4;
    float unk2d8;
    float unk2dc;
    float unk2e0;
    float unk2e4;
    float unk2e8;
    float unk2ec;
    float unk2f0;
    s32 unk2f4;
    s32 unk2f8;
    s32 unk2fc;
    s32 unk300;
    s32 unk304;
    s32 unk308;
    s32 unk30c;
    s8 unk310;
    s8 unk311;
    s8 unk312;
    s8 unk313;
    s8 unk314;
    s8 unk315;
    s8 unk316;
    u8 unk317;
    u8 unk318;
    u8 unk319[3];

    ~LibClass1723F0()
    {
    }

    /**
     * @brief Update the aggregate index; the base does nothing.
     * @param index Requested index.
     */
    virtual void func_00412C10(s32 index);

    /**
     * @brief Update the aggregate float setting; the base does nothing.
     * @param value Requested setting.
     */
    virtual void func_00412C20(float value);

    /**
     * @brief Read the aggregate float setting.
     * @return Zero in the base.
     */
    virtual float func_00412C30();

    /**
     * @brief Apply pad input to the selection, scrolling and paging, and count down the page repeat delays.
     * @return True when the selection or scroll position changed.
     */
    virtual bool func_00413020();
};

extern "C" {
/**
 * @brief Read the result of a running selection.
 * @param aggregate Widget aggregate.
 * @return Positive when an entry was chosen, negative when the selection was cancelled, otherwise zero.
 */
s32 func_00413460(LibClass1723F0* aggregate);

/**
 * @brief Test whether the aggregate takes input this frame.
 * @param aggregate Widget aggregate.
 * @return Nonzero when it does.
 */
u8 func_004135D0(LibClass1723F0* aggregate);

/**
 * @brief Update the aggregate's indicators.
 * @param aggregate Widget aggregate.
 */
void func_00413750(LibClass1723F0* aggregate);

/**
 * @brief Start a selection.
 * @param aggregate Widget aggregate.
 * @param first First entry index shown.
 * @param selected Selected row.
 * @param count Number of entries.
 */
void func_004138E0(LibClass1723F0* aggregate, s32 first, s32 selected, s32 count);

/**
 * @brief Set the aggregate's entry count, grid shape and cell size, and take the widgets' current places as origins.
 * @param aggregate Widget aggregate.
 * @param count Number of entries.
 * @param per_page Cells per row.
 * @param visible Rows shown at once.
 * @param x Cell width.
 * @param y Cell height.
 * @param z Scroll timing.
 */
void func_00413C00(LibClass1723F0* aggregate, s32 count, s32 per_page, s32 visible, float x, float y, float z);
}

/** Widget container with a selection aggregate, with vtable D_172320 in main data. */
class LibClass172320 : public LibContainer, public LibClass1723F0
{
public:
    LibClass172320();

    virtual ~LibClass172320();
};

/** Container owning up to 32 interface rows, with MAIN vtable at 0x1721F0. */
class LibClass1721F0 : public LibClass172320
{
public:
    /** @brief Initialize the container and set its transform type. */
    LibClass1721F0();

    virtual ~LibClass1721F0();

    /**
     * @brief Run the container state hook.
     * @param first First update flag.
     * @param second Second update flag.
     * @param third Third update flag.
     */
    virtual void func_00412C40(bool first, bool second, bool third);

    /**
     * @brief Create the row for an index.
     * @param index Row index.
     * @return The new row.
     */
    virtual void* create_row(s32 index) = 0;

    /**
     * @brief Called when the selected index changes.
     * @param index Selected index.
     */
    virtual void notify_index(s32 index);

    /** @brief Called when the selection is cancelled. */
    virtual void notify_cancel();

    /**
     * @brief Update the aggregate index.
     * @param index Requested index.
     */
    virtual void func_00412C10(s32 index);

    /**
     * @brief Update the aggregate float setting.
     * @param value Requested setting.
     */
    virtual void func_00412C20(float value);

    /**
     * @brief Read the aggregate float setting.
     * @return Current setting.
     */
    virtual float func_00412C30();

    /**
     * @brief Show or hide every row and the six aggregate widgets.
     * @param visible Nonzero to show them.
     */
    void set_rows_visible(u8 visible);

    /**
     * @brief Set the list up: its frame, scissors, markers, indicator, cursor and rows.
     * @param count Number of entries.
     * @param flags Bit 0 opens the list with its transition, bits 1 and 2 show the two markers, bits 3 and 4 mute
     *              the confirm and cancel sounds.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width List width.
     * @param height List height.
     * @param row_height Height of one row.
     * @param timing Scroll timing passed to the aggregate.
     * @return One on success, or zero when a widget or row couldn't be set up.
     */
    s32 init(s32 count, s32 flags, float x, float y, float width, float height, float row_height, float timing);

    void* rows[32];
    float unk490;
    float unk494;
    float unk498;
    float unk49c;
    s32 unk4a0;
    s32 unk4a4;
    u8 unk4a8;
    u8 unk4a9;
    u8 unk4aa;
    u8 unk4ab[5];
};

/** Container showing up to sixteen lines of text over a frame, with vtable D_174F70 in main data. */
class LibClass174F70 : public LibContainer
{
public:
    virtual ~LibClass174F70();

    /**
     * @brief Run the container state hook.
     * @param first First update flag.
     * @param second Second update flag.
     * @param third Third update flag.
     */
    virtual void func_00412C40(bool first, bool second, bool third);

    /**
     * @brief Called by the state hook when the list closes; the base does nothing.
     * @param result Chosen item number, or zero when cancelled.
     */
    virtual void func_004662A0(s32 result);

    /**
     * @brief Add a line of text from a resource slot.
     * @param slot Resource slot index.
     * @param key Key of the text in the slot.
     * @return The line's widget, or null when the lines are used up or the text can't be measured.
     */
    LibTextWidget* add_item(s32 slot, u32 key);

    /**
     * @brief Set the list up for up to 16 items: frame, cursor, markers and item text widgets, attached by the flags.
     * @param capacity Number of items, at most 16.
     * @param flags Bit 0x10000 hides the frame, 0x4 the cursor, 0x8 both markers; 0x2 picks the single marker over
     *        the pair; 0x20 clears unk13f8 and unkab; 0x1, 0x10 and 0x80000000 are kept as flags.
     * @param text_flag Flag passed to each item's text setup.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width Frame width.
     * @param height Frame height.
     * @return 1 on success, 0 when a part can't be set up or the capacity is too large.
     */
    s32 init(s32 capacity, u32 flags, u8 text_flag, float x, float y, float width, float height);

    ItemCreationClass175030 unkf0;
    LibClass1722E0 unk16c;
    ItemCreationClass172600 unk1fc;
    ItemCreationClass172870 unk250;
    LibTextWidget items[16];
    s32 item_capacity;
    s32 item_count;
    s32 unk13f0;
    s32 unk13f4;
    s32 unk13f8;
    u8 unk13fc;
    u8 text_flag;
    u8 unk13fe;
    u8 unk13ff;
    u8 show_frame;
    u8 show_cursor;
    u8 show_marker;
    u8 show_markers;
    u8 unk1404;
};

#endif
