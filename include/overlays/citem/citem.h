#ifndef SO3_OVERLAYS_CITEM_CITEM_H
#define SO3_OVERLAYS_CITEM_CITEM_H

#include "types.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002AE9E0.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004BD360.h"

/** Valuables the item menu tracks, one event flag each. */
#define ITEM_VALUABLE_COUNT 68

struct ItemCharacterStats;
struct ItemCreationAllocationRecord;
struct ItemCreationCategoryRecord;
struct ItemCreationClass172870;
struct ItemCreationOptionResourceDisplay;
class FieldClass153130;
class FieldClass153170;
class FieldClass15BB90;
class FieldObject23CEA0;
class ItemCategoryWindow;
class ItemControlHelpWindow;
class ItemHelpWindow;
class ItemListPanel;
class ItemResourceWindow;
class ItemTypeListWindow;
class ItemListNode;

/** Comparator returning zero when passed the same node twice. */
typedef s32 (*ItemListComparator)(const ItemListNode* left, const ItemListNode* right, u32 comparison_arg);

/** Value node shared by the gauge and item type lists. The payload isn't owned by the node. */
class ItemListNode
{
    public:
        void* value;
        ItemListNode* next;

        /** @brief Destroy the link without releasing its payload. */
        ~ItemListNode()
        {
        }
};

/** One selector position. */
class ItemCoordinateNode
{
    public:
        float x;
        float y;
        ItemCoordinateNode* next;

        /** @brief Start at the origin. */
        ItemCoordinateNode()
        {
            x = y = 0.0f;
        }

        /** @brief Destroy the link. */
        ~ItemCoordinateNode()
        {
        }
};

/** A position passed by value to ItemCoordinateList::append. */
struct ItemCoordinate
{
    float x;
    float y;

    /** @brief Store both coordinates. @param x Horizontal coordinate. @param y Vertical coordinate. */
    ItemCoordinate(float x, float y) : x(x), y(y)
    {
    }
};

/** HP and MP gauges owned by the use window, behind a sentinel node. */
class ItemGaugeList
{
    public:
        ItemListNode* head;
        u32 count;

        /** @brief Allocate the sentinel and initialize the empty list. */
        ItemGaugeList();

        /** @brief Release the links and sentinel without destroying the gauges. */
        virtual ~ItemGaugeList();

        /**
         * @brief Add a gauge to the end of the list.
         * @param gauge Gauge stored in the node. The caller owns it.
         */
        void append(void* gauge);

        /** @brief Delete the list nodes after the sentinel and reset the list count. */
        void clear();
};

/** Item type records shown by the type list window, behind a sentinel node. */
class ItemTypeList
{
    public:
        ItemListNode* head;
        u32 count;

        /** @brief Allocate the sentinel and initialize the empty list. */
        ItemTypeList();

        /** @brief Release the links and sentinel without destroying the records. */
        virtual ~ItemTypeList();

        /**
         * @brief Add an item type record to the end of the list.
         * @param record Item type record.
         */
        void append(ItemCreationCategoryRecord* record);

        /** @brief Delete the list nodes after the sentinel and reset the list count. */
        void clear();

        /**
         * @brief Return the node at `index`. Index zero is the first node after the sentinel.
         * @param index Zero-based index among the value nodes.
         * @return The node at that index, or null if the list ends first.
         */
        ItemListNode* at(s32 index);

        /**
         * @brief Sort the list by moving links; the payloads and sentinel stay put.
         * @param compare Signed node comparator, returning zero for equal nodes.
         * @param comparison_arg Argument forwarded to each comparator call.
         * @param ascending Nonzero for ascending order, zero for descending order.
         */
        void sort(ItemListComparator compare, u32 comparison_arg, s32 ascending);
};

/** Selector positions, behind a sentinel node. */
class ItemCoordinateList
{
    public:
        ItemCoordinateNode* head;
        u32 count;

        /** @brief Allocate the sentinel and initialize the empty list. */
        ItemCoordinateList();

        /** @brief Release the positions and the sentinel. */
        virtual ~ItemCoordinateList();

        /** @brief Delete the position nodes after the sentinel and reset the list count. */
        void clear();

        /**
         * @brief Add a position to the end of the list.
         * @param position Position to add.
         */
        void append(ItemCoordinate position);
};

/** Item menu State: owns the windows, the party selection, and what the player picked. */
class ItemController : public LibClass171FF0, public FieldClass153E30
{
    public:
        /** @brief Initialize the controller's bases and clear its window and selection state. */
        ItemController();

        /** @brief Remove the items listed in record_identifiers when requested, then destroy the bases. */
        virtual ~ItemController();

        /**
         * @brief Allocate and populate a missing party selection.
         * @return One after creating and populating the selection; otherwise zero.
         */
        virtual u8 func_00264110();

        /**
         * @brief Load the completed menu resource and create the windows.
         * @param buffer Completed resource buffer.
         * @return Window creation result, or zero for a null buffer.
         */
        virtual s32 on_resource_loaded(void* buffer);

        /** @brief Collect the owned valuables and create the menu windows. @return One. */
        virtual s32 init_windows();

        /** @brief Report whether window setup finished. @return Setup flag. */
        virtual u8 windows_ready();

        /** @brief Return the loaded resource slot. @return Resource slot. */
        virtual u32 get_resource_slot();

        /** @brief Report this object's default list kind. @return Four. */
        virtual s32 get_default_list_kind();

        /** @brief Release the party selection and queue the controller's Field receiver. */
        virtual void func_001DD7B0();

        /** @brief Release the loaded resources, detach the controller, and queue its receiver. */
        virtual void func_slot5c();

        /** @brief Return the party selection. @return Party selection. */
        virtual FieldRecordSelection* selected_records();

        u32 resource_slot;
        u8 windows_initialized : 1;
        u8 unk3c_1_7 : 7;
        u8 unk3d[3];
        FieldRecordSelection* party;
        ItemResourceWindow* resource_window;
        ItemHelpWindow* help_window;
        ItemCategoryWindow* category_window;
        ItemTypeListWindow* type_list_window;
        ItemControlHelpWindow* control_help_window;
        ItemListPanel* list_panel;

        /** The windows aren't created when this is one. */
        u8 unk5c;

        u8 unk5d;
        u16 unk5e;

        /** Indices of the valuables the player owns, in flag order. */
        u8 valuables[ITEM_VALUABLE_COUNT];

        s32 valuable_count;
        u8 unka8;
        u8 remove_flagged_records;
        s16 record_identifiers[5];

        /** Category window row: 0 to 9, in the order of the category labels. */
        s32 selected_category;

        /** One-based item type ID, or a valuable index while Valuables is selected. */
        u32 selected_item_type;

        /** Individual item highlighted in the instance list, or null. */
        ItemCreationAllocationRecord* selected_allocation;
};

/** "Confirm Drop" window that asks "Drop item?" with Yes and No. */
class ItemDropConfirmWindow : public FieldClass15AE70
{
    public:
        /** @brief Clear the grid and text links. */
        ItemDropConfirmWindow()
        {
            grid = 0;
            yes_text = 0;
            no_text = 0;
        }

        /** @brief Destroy the window. */
        virtual ~ItemDropConfirmWindow();

        /** @brief Enable the Yes/No grid while this is the focused window. */
        virtual void func_slot5c();

        /** @brief Send grid direction three and recolor Yes and No for the new cursor. */
        virtual void func_slot70();

        /** @brief Send grid direction two and recolor Yes and No for the new cursor. */
        virtual void func_slot74();

        /**
         * @brief Drop the selected item on Yes, then return to the instance list or the type list.
         * @return Zero while input is blocked, the back result when No is selected, otherwise one.
         */
        virtual u8 func_slotb0();

        /**
         * @brief Close the window and return to the instance list.
         * @return Zero while input is blocked, otherwise two.
         */
        virtual u8 func_slotb4();

        /**
         * @brief Create the panels, the title and question, and the Yes/No grid.
         * @param associated Resource source word.
         * @return One.
         */
        virtual s32 func_slotf4(u32 associated);

        /** Two-column Yes/No grid; its unk114 is the selected column. */
        FieldObject23CEA0* grid;

        LibObject178750* yes_text;
        LibObject178750* no_text;
};

/** Gauge origin, zeroed on construction. */
struct ItemGaugeOrigin
{
    /** @brief Start at the origin. */
    ItemGaugeOrigin()
    {
        x = y = 0.0f;
    }

    float x;
    float y;
};

/** Draws one party member's HP and MP gauges. */
class ItemHpMpGaugeDrawer : public FieldClass159A70
{
    public:
        /** @brief Clear the origin, spacing and character link. */
        ItemHpMpGaugeDrawer()
        {
            origin.x = 0.0f;
            origin.y = 0.0f;
            row_spacing = 0.0f;
            character_id = 0;
            characters = 0;
        }

        /** @brief Release the drawing packet and base. */
        virtual ~ItemHpMpGaugeDrawer();

        /**
         * @brief Rebuild the drawing packet.
         * @param first Unused draw flag.
         * @param depth Unused drawing depth.
         * @param value Unused drawing value.
         */
        virtual void func_002BC4F0(u32 first, u32 depth, float value);

        /** @brief Build the paired HP and MP gauge drawing packet. */
        void build_packet();

        ItemGaugeOrigin origin;
        float row_spacing;
        s16 character_id;
        u8 unk3e[2];

        /** Party character records, indexed by character_id. */
        ItemCharacterStats* characters;
};

/** HP and MP gauge transform with drawing and DMA notification interfaces. */
class ItemHpMpGauge : public FieldClass1599E0, public ItemHpMpGaugeDrawer
{
    public:
        /** @brief Initialize the gauge bases with release not yet queued. */
        ItemHpMpGauge()
        {
            queued_for_release = 0;
        }

        /** @brief Release the drawing and transform bases. */
        virtual ~ItemHpMpGauge();

        /** @brief Submit the drawing packet for DMA notification. */
        virtual void func_003EEBE0();

        /** @brief Leave the default update state unchanged. */
        virtual void update();

        /** @brief Report the transform kind. @return Fourteen. */
        virtual s32 get_default_list_kind();

        /** @brief Detach and queue the gauge for release. */
        virtual void func_003EF740();

        /** @brief Restore the saved transform state. */
        virtual void func_003F4420();

        /**
         * @brief Update gauge visibility and rebuild changed packets.
         * @param first Update enabled.
         * @param second Mark the packet changed.
         * @param third Allow drawing.
         */
        virtual void func_0044B100(u32 first, u32 second, u32 third);

        /** @brief Complete DMA notification processing. @param value Unused notification value. */
        virtual void func_003F4410(u32 value);

        /**
         * @brief Initialize the gauge transform.
         * @param code Transform code.
         * @param first First transform flag.
         * @param source Transform source.
         * @param x Unused first coordinate.
         * @param y Unused second coordinate.
         * @param z Third coordinate.
         * @return One.
         */
        virtual s32 initialize(s32 code, s32 first, void* source, float x, float y, float z);

        u8 queued_for_release;
};

/** Moving cursor over a fixed list of positions. */
class ItemCoordinateSelector : public LibClass175030
{
    public:
        /** @brief Start with no positions and nothing selected. */
        ItemCoordinateSelector()
        {
            selected = -1;
        }

        /** @brief Destroy the positions and the movement base. */
        virtual ~ItemCoordinateSelector();

        /** @brief Report the intrusive object kind. @return Three. */
        virtual s32 get_default_list_kind();

        /** @brief Leave the default update hook unchanged. */
        virtual void update();

        /** @brief Leave the default notification hook unchanged. */
        virtual void func_003EEBE0();

        ItemCoordinateList positions;

        /** Index into positions, or -1. */
        s32 selected;
};

/** Background panel behind the item lists. */
class ItemListPanel : public FieldClass15AE70
{
    public:
        /** @brief Initialize the panel's Field base. */
        ItemListPanel()
        {
        }

        /** @brief Destroy the panel window. */
        virtual ~ItemListPanel();

        /**
         * @brief Create and attach the panel.
         * @param associated Resource source word.
         * @return One.
         */
        virtual s32 func_slotf4(u32 associated);
};

/**
 * The item types in the selected category with how many of each the party holds. Types that
 * include a newly acquired item are tinted green. Valuables list the owned valuables instead.
 */
class ItemTypeListWindow : public FieldClass15AD40
{
    public:
        /** @brief Clear the row widgets and link the controller. @param owner Parent item controller. */
        ItemTypeListWindow(ItemController* owner);

        /** @brief Destroy the item type list and the Field window. */
        virtual ~ItemTypeListWindow();

        /** @brief Process list input, publish the highlighted item type and move the row marker. */
        virtual void func_slot5c();

        /**
         * @brief Open the instance list for the highlighted item type.
         * @return Three for an empty list, zero without a controller or for Valuables, otherwise one.
         */
        virtual u8 func_slotb0();

        /** @brief Hide the cursor and return to the category window. @return Two. */
        virtual u8 func_slotb4();

        /** @brief Toggle sorting and refresh the visible rows. @return Zero for Valuables, otherwise one. */
        virtual u8 func_slotbc();

        /**
         * @brief Create the row widgets, the clip region, the cursor and the scroll indicator.
         * @param associated Resource source word.
         * @return One.
         */
        virtual s32 func_slot104(u32 associated);

        /**
         * @brief Show or hide the cursor.
         * @param unused Unused.
         * @param cursor Nonzero shows the cursor at full brightness; zero hides it and dims it.
         */
        virtual void func_slot10c(u32 unused, u32 cursor);

        /** @brief Fill the visible rows with names and counts. @param start First list index. */
        virtual void refresh_rows(s32 start);

        /** @brief Position the row widgets. @param start Base vertical coordinate. */
        virtual void set_scroll_position(float start);

        /**
         * @brief Rebuild the item type list for a category and reset the visible rows and cursor.
         * @param reset Nonzero to move the cursor back to the first row.
         * @param category Category to list, or -1 for the controller's selected category.
         */
        virtual void rebuild_list(s32 reset, s32 category);

        /** ":" after each item name. */
        LibObject178750* separators[14];

        LibObject174F20* counts[14];
        ItemController* controller;
        ItemTypeList item_types;

        /** One bit per item type ID that includes a newly acquired item. */
        u32 new_item_types[24];

        u8 sort_enabled;
};

/** Category selector: Weapons through New Items, each with an icon. */
class ItemCategoryWindow : public FieldClass15AE70
{
    public:
        /** @brief Initialize the controller link and window fields. @param owner Parent item controller. */
        ItemCategoryWindow(ItemController* owner)
        {
            selector = 0;
            highlight = 0;
            type_list = 0;
            controller = owner;
            label_count = 0;
            unkbc = 0;
            FieldClass15AE70();
        }

        /** @brief Destroy the window. */
        virtual ~ItemCategoryWindow();

        /** @brief Publish the highlighted category and hide the Sort prompt while this window is focused. */
        virtual void func_slot5c();

        /** @brief Restore the selector brightness. */
        virtual void func_slot64();

        /** @brief Move up a category, then update the highlight, the help line and the type list. */
        virtual void func_slot68();

        /** @brief Move down a category, then update the highlight, the help line and the type list. */
        virtual void func_slot6c();

        /**
         * @brief Enter the type list for the highlighted category.
         * @return Zero while the selector is missing or idle, otherwise one.
         */
        virtual u8 func_slotb0();

        /** @brief Handle Back by setting window state one with flag 0x80. @return Two. */
        virtual u8 func_slotb4();

        /**
         * @brief Create the panel, the category labels and icons, the selector and its highlight.
         * @param associated Resource source word.
         * @return Zero when the type list window is missing, otherwise one.
         */
        virtual s32 func_slotf4(u32 associated);

        FieldClass153130* selector;
        FieldClass153170* highlight;
        ItemTypeListWindow* type_list;
        ItemController* controller;
        u16 label_count;
        u8 unkba[2];
        void* unkbc;
};

/** Button prompts under the list: Sort, Back and Select. */
class ItemControlHelpWindow : public FieldClass15AE70
{
    public:
        /** @brief Clear the prompt links and layout. */
        ItemControlHelpWindow()
        {
            prompts[0] = 0;
            prompts[1] = 0;
            prompts[2] = 0;
            width = 0.0f;
            height = 0.0f;
            scale = 0.0f;
            unkc0 = 0.0f;
            row_spacing = 0.0f;
            text_x = 0.0f;
            text_y = 0.0f;
            unkd0 = 0.0f;
        }

        /** @brief Destroy the window. */
        virtual ~ItemControlHelpWindow();

        /**
         * @brief Create the panel and the three prompts.
         * @param associated Resource source word.
         * @return One.
         */
        virtual s32 func_slotf4(u32 associated);

        /** Sort, Back and Select. */
        LibObject178750* prompts[3];

        float width;
        float height;
        float scale;
        float unkc0;
        float row_spacing;
        float text_x;
        float text_y;
        float unkd0;
};

/** Help bar with the "Items" title and a help line that scrolls when it doesn't fit. */
class ItemHelpWindow : public FieldClass15AE70
{
    public:
        /** @brief Clear the help line and its scrolling state. */
        ItemHelpWindow()
        {
            text_display = 0;
            scroll_extent = 0;
            scrolling = 0;
            delay_frames = 0;
            label_width = 0.0f;
            start_x = 0.0f;
            clip_x = 0.0f;
            clip_width = 0.0f;
        }

        /** @brief Destroy the window. */
        virtual ~ItemHelpWindow();

        /** @brief Hold the help line at its start for 120 frames, then scroll it left and wrap. */
        virtual void func_slot5c();

        /**
         * @brief Show a help line and restart its hold, for keys in this overlay's help range.
         * @param text_key Message key; only keys 7020 through 7034 are accepted.
         */
        virtual void func_slot60(s32 text_key);

        /**
         * @brief Create the title, the caption and the clipped help line, then show the first line.
         * @param associated Resource source word.
         * @return Zero when a widget couldn't be allocated, otherwise one.
         */
        virtual s32 func_slotf4(u32 associated);

        LibObject178750* text_display;

        /** Help line width plus a six-pixel gap. */
        s32 scroll_extent;

        s16 delay_frames;
        u8 scrolling;
        u8 unkb3;
        float label_width;
        float start_x;
        float clip_x;
        float clip_width;
};

/** Three resource tiles placed 256 units apart. */
class ItemResourceWindow : public FieldClass15AE70
{
    public:
        /** @brief Clear the tile links. */
        ItemResourceWindow()
        {
            left_tile = 0;
            middle_tile = 0;
            right_tile = 0;
        }

        /** @brief Destroy the window. */
        virtual ~ItemResourceWindow();

        /**
         * @brief Create and attach the three tiles.
         * @param associated Resource source word.
         * @return One.
         */
        virtual s32 func_slotf4(u32 associated);

        ItemCreationOptionResourceDisplay* left_tile;
        ItemCreationOptionResourceDisplay* middle_tile;
        ItemCreationOptionResourceDisplay* right_tile;
        u8 unkb4[4];
};

/** Party panels for equipping the selected item, with ATK, DEF and INT comparisons. */
class ItemEquipWindow : public FieldClass15AE70
{
    public:
        /** @brief Clear the selector links and comparison state. */
        ItemEquipWindow()
        {
            party = 0;
            selector = 0;
            x = 0.0f;
            y = 0.0f;
            row_height = 0.0f;
            pulse_level = 0;
            pulse_step = 1;
            accessory_slot = 2;
            message_changed = 0;
        }

        /** @brief Restore the category help line and destroy the window. */
        virtual ~ItemEquipWindow();

        /** @brief Pulse the comparison colors and compare each member's ATK, DEF and INT with the item equipped. */
        virtual void func_slot5c();

        /** @brief Move the selector from the back row to the front row. */
        virtual void func_slot68();

        /** @brief Move the selector from the front row to the back row. */
        virtual void func_slot6c();

        /** @brief Move the selector back one member, wrapping to the eighth. */
        virtual void func_slot70();

        /** @brief Move the selector forward one member, wrapping after the eighth. */
        virtual void func_slot74();

        /**
         * @brief Equip the selected item on the selected member and recalculate their statistics.
         * @return Three when nobody is selected or the item can't be equipped, otherwise zero.
         */
        virtual u8 func_slotb0();

        /** @brief Close the window and return to the instance list, or to the type list when none remain. @return Two. */
        virtual u8 func_slotb4();

        /**
         * @brief Switch between the two accessory slots for an accessory.
         * @return One when the selected item is an accessory, otherwise zero.
         */
        virtual s32 func_slotc0();

        /** @brief Same as func_slotc0. @return Its result. */
        virtual s32 func_slotc4();

        /**
         * @brief Create the party panels with names, portraits and comparison labels, then show the equip help line.
         * @param associated Resource source word.
         * @return Zero when the selector couldn't be allocated, otherwise one.
         */
        virtual s32 func_slotf4(u32 associated);

        FieldRecordSelection* party;
        ItemCoordinateSelector* selector;
        float x;
        float y;

        /** Height of each character panel. */
        float row_height;

        s32 pulse_level;
        s32 pulse_step;

        /** Equipment slot an accessory goes in: 2 for accessory 1, 3 for accessory 2. */
        s32 accessory_slot;

        /** The help line was replaced and has to be restored on close. */
        u8 message_changed;

        u8 unkc9[3];
        ItemCreationOptionResourceDisplay* portraits[8];

        /** "Up!", "Down!", "Same!" or "..." for ATK, DEF and INT. */
        LibObject178750* stat_results[8][3];
};

/** Party panels for using the selected item, with HP, MP, status and gauges. */
class ItemUseWindow : public FieldClass15AE70
{
    public:
        /** @brief Clear the selector links and state. */
        ItemUseWindow()
        {
            party = 0;
            selector = 0;
            x = 0.0f;
            y = 0.0f;
            row_height = 0.0f;
            message_changed = 0;
        }

        /** @brief Restore the category help line and destroy the gauges and the window. */
        virtual ~ItemUseWindow();

        /** @brief Release the gauges and the window's widgets. */
        virtual void func_slot0c();

        /** @brief Update the gauges and refresh each member's HP, MP, status badges and name color. */
        virtual void func_slot5c();

        /** @brief Move the selector from the back row to the front row. */
        virtual void func_slot68();

        /** @brief Move the selector from the front row to the back row. */
        virtual void func_slot6c();

        /** @brief Move the selector back one member, wrapping to the eighth. */
        virtual void func_slot70();

        /** @brief Move the selector forward one member, wrapping after the eighth. */
        virtual void func_slot74();

        /** @brief Use the selected item on the selected member. @return Three when it can't be used, otherwise zero. */
        virtual u8 func_slotb0();

        /** @brief Close the window and return to the instance list, or to the type list when none remain. @return Two. */
        virtual u8 func_slotb4();

        /**
         * @brief Create the party panels with names, HP and MP, portraits, status badges, gauges and selector positions.
         * @param associated Resource source word.
         * @return Zero when the selector couldn't be allocated, otherwise one.
         */
        virtual s32 func_slotf4(u32 associated);

        FieldRecordSelection* party;
        ItemCoordinateSelector* selector;
        float x;
        float y;

        /** Height of each character panel. */
        float row_height;

        ItemGaugeList gauges;
        LibObject174F20* hp_values[8];
        LibObject174F20* mp_values[8];
        LibObject174F20* max_hp_values[8];
        LibObject174F20* max_mp_values[8];
        LibObject175140* names[8];
        ItemCreationOptionResourceDisplay* portraits[8];

        /** Three status icons, then the incapacitated portrait. */
        ItemCreationOptionResourceDisplay* status_badges[8][4];

        /** The help line was replaced and has to be restored on close. */
        u8 message_changed;

        u8 unk209[3];
};

/**
 * The individual items of the selected type, each with its factor marks. Details replaces the rows
 * with the item's name, description and factors next to its 3D model. Valuables open straight into
 * the details.
 */
class ItemInstanceListWindow : public FieldClass15AD40
{
    public:
        /** @brief Clear the rows and the details state. */
        ItemInstanceListWindow()
        {
            for (s32 index = 0; index < 6; index++)
            {
                item_rows[index] = 0;
            }
            details_shown = 0;
            model = 0;
            closing_details = 0;
            FieldClass15AD40();
        }

        /** @brief Detach the panel and destroy the window. */
        virtual ~ItemInstanceListWindow();

        /** @brief Release the detail container and the window's widgets. */
        virtual void func_slot0c();

        /** @brief Process list input, show the highlighted item's factors, and close the details once their model is released. */
        virtual void func_slot5c();

        /** @brief Turn the details model, up to thirty degrees. */
        virtual void func_slot68();

        /** @brief Turn the details model back, down to zero. */
        virtual void func_slot6c();

        /**
         * @brief Open the equip or use window for the highlighted item.
         * @return Zero while the details are shown, three when the item can't be used, otherwise one.
         */
        virtual u8 func_slotb0();

        /**
         * @brief Close the details, or return to the type list.
         * @return Two.
         */
        virtual u8 func_slotb4();

        /**
         * @brief Show or hide the details for the highlighted item.
         * @return Zero.
         */
        virtual u8 func_slotb8();

        /**
         * @brief Ask whether to drop the highlighted item.
         * @return Zero while the details are shown, three for an item that can't be dropped, otherwise one.
         */
        virtual u8 func_slotbc();

        /**
         * @brief Create the item rows, factor widgets, description, prompts, cursor and scroll indicator.
         * @param associated Loaded resource slot.
         * @return One.
         */
        virtual s32 func_slot104(u32 associated);

        /**
         * @brief Show or hide the rows and the cursor.
         * @param rows Visibility of each item row and its factor marks.
         * @param cursor Nonzero shows the cursor and indicator at full brightness; zero hides them and dims the cursor.
         */
        virtual void func_slot10c(u32 rows, u32 cursor);

        /** @brief Fill the visible rows. @param start First list index. */
        virtual void refresh_rows(s32 start);

        /** @brief Position the rows. @param start Vertical offset. */
        virtual void set_scroll_position(float start);

        /**
         * @brief Recount the items and clamp the cursor, or open the details for a valuable.
         * @param reset Nonzero to move the cursor back to the first row.
         */
        void refresh_instances(s32 reset);

        /** Name and modification number of each visible item. */
        LibObject172410* item_rows[6];

        LibObject172440* factors[8];

        /** Line under the rows; it moves up while the details are shown. */
        ItemCreationClass172870* divider;

        LibClass178630* panel;

        /** "Drop / Details" prompt. */
        LibObject178750* details_prompt;

        /** "Back / Use"; with the details shown, "Switch / Back", or "Back" for a valuable. */
        LibObject178750* action_prompt;

        /** Icon showing how many factors each visible item has. */
        ItemCreationOptionResourceDisplay* factor_marks[6];

        LibObject178660* detail_container;
        LibObject178750* category_label;
        u8 unk1a0[4];
        LibObject178750* description;

        /** "Factor". */
        LibObject178750* factor_heading;

        /** Name of the selected item type, drawn large. */
        LibObject172410* selected_item;

        u8 details_shown;
        u8 unk1b1[7];
        FieldClass15BB90* model;

        /** Set when the player asked to close the details; they close once the model is released. */
        u8 closing_details;
};

/**
 * @brief Compare two item types by their catalog list order.
 * @param left First node, holding an item type record.
 * @param right Second node, holding an item type record.
 * @param comparison_arg Unused.
 * @return Negative, zero or positive as left sorts before, with or after right.
 */
s32 item_compare_sort_order(const ItemListNode* left, const ItemListNode* right, u32 comparison_arg);

#endif
