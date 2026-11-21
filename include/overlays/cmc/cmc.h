#ifndef SO3_OVERLAYS_CMC_CMC_H
#define SO3_OVERLAYS_CMC_CMC_H

#include "types.h"

#ifdef __cplusplus
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_marker.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_002F1B20.h"
#include "overlays/lib/memory_card.h"
#include "overlays/lib/widget_aggregate.h"
#include "main/sound.h"
#include "overlays/1067-00/text_001E1590.h"
#include "main/resident_data.h"

class CardTask;
class CmcClass189C20;
class TrophyCheckingWindow;
class TrophyLoadedWindow;
class TrophyLoadFailedWindow;
class TrophyNoDataConfirmWindow;
class TrophyCorruptWindow;
class TrophySlotSelectWindow;
class CardSlotSelectWindow;
class TrophyNoCardWindow;
class TrophySkipConfirmWindow;
class TrophyNoDataWindow;
class CardProgressBar;
class LibDrawBuffer;
class LibModel;
class CardMessageWindow;

/** Partial controller of the memory card menu: creates and drives every card window, with MAIN vtable at 0x18AF20. */
class CardMenuController : public FieldClass153E30
{
public:
    /** @brief Initialize the callback controller and its retained object pointers. */
    CardMenuController();

    /** @brief Show the window for the pending request and set the alternate window's text for it. */
    void dispatch_window_request();

    /**
     * @brief Store a window request and dispatch it when it's nonzero.
     * @param request Window request code.
     */
    void request_window(u32 request)
    {
        unk54 = request;

        if (unk54 != 0)
        {
            dispatch_window_request();
        }
    }

    /**
     * @brief Read the flag that makes closing the card menu fade back to the field.
     * @return The flag.
     */
    u8 get_unk50()
    {
        return unk50;
    }

    /** @brief With no window request pending, fade the screen out and hand the field back to a camera facing the field object's heading. */
    void func_003583B0();

    /**
     * @brief Create the memory card handler, add it to the update list and link its Field object to the controller.
     * @return One on success, or zero when the handler or its Field object couldn't be set up.
     */
    virtual u8 func_00264110();

    /** @brief Destroy the callback controller. */
    virtual ~CardMenuController();

    /** @brief Add this object to the resident queue. */
    virtual void func_001DD7B0();

    /**
     * @brief Bind a completed resource buffer and finish controller setup.
     * @param buffer Completed buffer.
     * @return Setup result, or zero when the buffer is null.
     */
    virtual s32 on_resource_loaded(void* buffer);

    /**
     * @brief Create the card menu's windows, set each up and register it with the controller.
     * @return One.
     */
    virtual s32 init_windows();

    /** @brief Release the retained resource slot, detach the controller, and queue it. */
    virtual void func_slot5c();

    /**
     * @brief Report the controller's default list kind.
     * @return Always 4.
     */
    virtual s32 get_default_list_kind();

    /**
     * @brief Return the menu resource slot.
     * @return Resource slot.
     */
    virtual u32 get_resource_slot();

    /**
     * @brief Report whether the windows are ready.
     * @return Ready flag.
     */
    virtual u8 windows_ready();

    /**
     * @brief Return the linked memory card handler.
     * @return Handler pointer as a word.
     */
    virtual s32 func_slot60();

    /**
     * @brief Return the Field save-data object.
     * @return Object pointer as a word.
     */
    virtual s32 func_slot64();

    s32 resource_slot;
    CardTask* linked_object;
    FieldClass15B9C0* unk3c;
    u8 unk40;
    u8 unk41[3];
    CmcClass189C20* unk44;
    u16 unk48;
    u8 unk4a[2];
    CardMessageWindow* unk4c;
    u8 unk50;
    u8 unk51;
    u16 unk52;
    u32 unk54;
    TrophyCheckingWindow* unk58;
    TrophyLoadedWindow* unk5c;
    TrophyLoadFailedWindow* unk60;
    TrophyNoDataConfirmWindow* unk64;
    TrophyCorruptWindow* unk68;
    TrophySlotSelectWindow* unk6c;
    TrophyNoCardWindow* unk70;
    TrophySkipConfirmWindow* unk74;
    TrophyNoDataWindow* unk78;
    CardSlotSelectWindow* unk7c;
    u8 unk80;
};

/** Partial title and help window of the card menu ("Memory Card", Save / Load / Import Data, message 0x2328 on), with MAIN vtable at 0x18AD20. */
class CardMessageWindow : public FieldClass15AE70
{
public:
    /** @brief Initialize the window, retained widgets, and animation state. */
    CardMessageWindow();

    /**
     * @brief Set the window message.
     * @param text_key Message key.
     */
    virtual void func_slot60(s32 text_key);

    virtual ~CardMessageWindow();

    /** @brief Update widget state and advance the text rectangle animation. */
    virtual void func_slot5c();

    /**
     * @brief Create the window's panel, message text and option displays.
     * @param associated Full resource source word.
     * @return One on success.
     */
    virtual s32 func_slotf4(u32 associated);

    LibTextWidget* unkA8;
    LibTextWidget* unkAc;
    LibTextWidget* unkB0;
    s32 unkB4;
    s8 unkB8;
    u8 unkB9;
    u8 unkBa;
    u8 unkBb;
    s16 unkBc;
    s8 unkBe;
    u8 unkBf;
    float unkC0;
    float unkC4;
    float unkC8;
    float unkCc;
    ItemCreationClass172870* unkD0;
    u8 unkD4;
    u8 unkD5;
};

/** Partial 0xB0-byte window saying there's no Battle Trophies data on the card (message 0x234A), with MAIN vtable at 0x188F10. */
class TrophyNoDataWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Create the window for a controller.
     * @param controller Controller the window reports to.
     */
    TrophyNoDataWindow(CardMenuController* controller) : unka8(0)
    {
        unka8 = controller;
        unkac = 0;
    }

    virtual ~TrophyNoDataWindow();

    /**
     * @brief Request controller action 0x79 and hide the nested display.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return One.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    LibTextWidget* unkac;
};

/** Partial 0xC0-byte yes/no dialog asking whether to go on without loading Battle Trophies data (message 0x2349), with MAIN vtable at 0x189010. */
class TrophySkipConfirmWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Create the window for a controller.
     * @param controller Controller the window reports to.
     */
    TrophySkipConfirmWindow(CardMenuController* controller) : unka8(0)
    {
        unka8 = controller;
        unkac = 0;
        unkb0 = 0;
        unkb4 = 0;
        selector = 0;
        marker = 0;
    }

    virtual ~TrophySkipConfirmWindow();

    /**
     * @brief Request controller action 0x79, hide the nested display, and select the second choice.
     * @return Two.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Confirm the first choice, or behave like func_slotb4 for the second.
     * @return Zero while the selector is still moving, otherwise one.
     */
    virtual u8 func_slotb0();

    /** @brief Move the selector in direction two and recolour the choices. */
    virtual void func_slot74();

    /** @brief Move the selector in direction three and recolour the choices. */
    virtual void func_slot70();

    /**
     * @brief Create the panel, the question and both choices, the selector, and its marker.
     * @param associated Full resource source word.
     * @return One.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    LibTextWidget* unkac;
    LibTextWidget* unkb0;
    LibTextWidget* unkb4;
    FieldClass153130* selector;
    FieldClass153170* marker;
};

/** Partial 0xC0-byte yes/no dialog for a card with no Battle Trophies data, asking whether to start anyway (message 0x2345), with MAIN vtable at 0x189310. */
class TrophyNoDataConfirmWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Create the window for a controller.
     * @param controller Controller the window reports to.
     */
    TrophyNoDataConfirmWindow(CardMenuController* controller) : unka8(0)
    {
        unka8 = controller;
        selector = 0;
        unkac = 0;
        unkb0 = 0;
        unkb4 = 0;
        marker = 0;
    }

    virtual ~TrophyNoDataConfirmWindow();

    /**
     * @brief Request controller action 0x79 and hide the nested display once the selector stops.
     * @return Zero while the selector is still moving, otherwise one.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Confirm the first choice, or request controller action 0x79 for the second.
     * @return Zero while the selector is still moving, otherwise one.
     */
    virtual u8 func_slotb0();

    /** @brief Move the selector in direction two and recolour the choices. */
    virtual void func_slot74();

    /** @brief Move the selector in direction three and recolour the choices. */
    virtual void func_slot70();

    /**
     * @brief Create the panel, the question and both choices, the selector, and its marker.
     * @param associated Full resource source word.
     * @return One.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    LibTextWidget* unkac;
    LibTextWidget* unkb0;
    LibTextWidget* unkb4;
    FieldClass153130* selector;
    FieldClass153170* marker;
};

/** Partial window choosing the MEMORY CARD slot to load Battle Trophies data from, with MAIN vtable at 0x189110. */
class TrophySlotSelectWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Create the window for a controller.
     * @param controller Controller the window reports to.
     */
    TrophySlotSelectWindow(CardMenuController* controller) : unka8(0)
    {
        unka8 = controller;
        linked = 0;
        selector = 0;
        first_text = 0;
        second_text = 0;
        marker = 0;
    }

    /**
     * @brief Run the selection action.
     * @return Window action status.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Request the controller action and hide the nested display.
     * @return Two.
     */
    virtual u8 func_slotb4();

    virtual ~TrophySlotSelectWindow();

    /** @brief Move the child selector backward. */
    virtual void func_slot68();

    /** @brief Move the child selector forward. */
    virtual void func_slot6c();

    /** @brief While this is the focused window, colour each choice by its record state and move the marker. */
    virtual void func_slot5c();

    /**
     * @brief Create the panel, the two choices and their selector and marker.
     * @param associated Full resource source word.
     * @return Zero when the controller has no linked object, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    CardTask* linked;
    FieldClass153130* selector;
    LibTextWidget* first_text;
    LibTextWidget* second_text;
    FieldClass153170* marker;
};

/** Partial 0xB0-byte window saying the Battle Trophies data is corrupted (message 0x2348), with MAIN vtable at 0x189210. */
class TrophyCorruptWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Create the window for a controller.
     * @param controller Controller the window reports to.
     */
    TrophyCorruptWindow(CardMenuController* controller) : unka8(0)
    {
        unka8 = controller;
        unkac = 0;
    }

    virtual ~TrophyCorruptWindow();

    /**
     * @brief Request controller action 0x79 and hide the nested display.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return One.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    LibTextWidget* unkac;
};

/** Partial 0xB0-byte window saying the Battle Trophies data failed to load (message 0x2344), with MAIN vtable at 0x189410. */
class TrophyLoadFailedWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Create the window for a controller.
     * @param controller Controller the window reports to.
     */
    TrophyLoadFailedWindow(CardMenuController* controller) : unka8(0)
    {
        unka8 = controller;
        unkac = 0;
    }

    virtual ~TrophyLoadFailedWindow();

    /**
     * @brief Request controller action 0x79 and hide the nested display.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return One.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    LibTextWidget* unkac;
};

/** Partial 0xB0-byte window saying the Battle Trophies data loaded (message 0x2343), with MAIN vtable at 0x189510. */
class TrophyLoadedWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Create the window for a controller.
     * @param controller Controller the window reports to.
     */
    TrophyLoadedWindow(CardMenuController* controller) : unka8(0)
    {
        unka8 = controller;
        unkac = 0;
    }

    virtual ~TrophyLoadedWindow();

    /**
     * @brief Set bit 6 of the checked record's byte 0x25, lock the window, and run the controller's closing step.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return One.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    LibTextWidget* unkac;
};

/** Partial 0xB0-byte window saying the chosen slot has no memory card, in the Battle Trophies flow (message 0x519), with MAIN vtable at 0x189710. */
class TrophyNoCardWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Create the window for a controller.
     * @param controller Controller the window reports to.
     */
    TrophyNoCardWindow(CardMenuController* controller) : unka8(0)
    {
        unka8 = controller;
        // TODO: the game stores the controller twice here
        unka8 = controller;
        unkac = 0;
    }

    virtual ~TrophyNoCardWindow();

    /**
     * @brief Request controller action 0x79 and hide the nested display.
     * @return One.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Request controller action 0x79 and hide the nested display.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when either widget couldn't be allocated, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    LibTextWidget* unkac;
};

/** Partial 0xB4-byte window shown while the Battle Trophies data is checked (message 0x2342), with MAIN vtable at 0x189610. */
class TrophyCheckingWindow : public FieldClass15AE70
{
public:
    /**
     * @brief Create the window for a controller.
     * @param controller Controller the window reports to.
     */
    TrophyCheckingWindow(CardMenuController* controller) : unka8(0)
    {
        unka8 = controller;
        unkb0 = 0;
        unkac = 0;
    }

    virtual ~TrophyCheckingWindow();

    /** @brief Once this is the focused window and the linked object has finished, hide the window and request the follow-up window its result codes select. */
    virtual void func_slot5c();

    /**
     * @brief Take the controller's linked object, then create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when the controller has no linked object, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    CardTask* unkac;
    LibTextWidget* unkb0;
};

/** Partial 0xB8-byte window with the three option resource displays, with MAIN vtable at 0x18AE20. */
class CmcClass18AE20 : public FieldClass15AE70
{
public:
    virtual ~CmcClass18AE20();

    /**
     * @brief Create the three option resource displays and pick the mode from the runtime's window flags.
     * @param associated Full resource source word.
     * @return One.
     */
    virtual s32 func_slotf4(u32 associated);

    s8 unka8;
    u8 unka9[3];
    ItemCreationOptionResourceDisplay* unkac;
    ItemCreationOptionResourceDisplay* unkb0;
    ItemCreationOptionResourceDisplay* unkb4;
};

/** Partial 0xAC-byte window shown while a memory card is formatted (message 0x515), with MAIN vtable at 0x18A720. */
class CardFormattingWindow : public FieldClass15AE70
{
public:
    CardFormattingWindow() : unka8(0), unkac(0)
    {
    }

    virtual ~CardFormattingWindow();

    /** @brief Once this is the focused window, act on the memory card handler's result. */
    virtual void func_slot5c();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when a required object is missing, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    /** @brief Open the save window for the selected slot and restart the card handler. */
    void func_00353B60();

    CardTask* unka8;
    s32 unkac;
};

/** Partial 0xE0-byte save or load verification dialog ("Create new data?", "Overwrite?", "Load data?" with Yes / No), with MAIN vtable at 0x189B20. */
class CardVerifyWindow : public FieldClass15AE70
{
public:
    CardVerifyWindow()
    {
        func_0034F310();
    }

    virtual ~CardVerifyWindow();

    /** @brief Once this is the focused window, recolour the choices for the grid's cursor and finish when the card handler is done. */
    virtual void func_slot5c();

    /** @brief Move the grid in direction two. */
    virtual void func_slot74();

    /** @brief Move the grid in direction three. */
    virtual void func_slot70();

    /**
     * @brief Close the window, restore its parent and set the alternate window's text unless input is locked.
     * @return Zero while locked, otherwise two.
     */
    virtual u8 func_slotb4();

    /**
     * @brief On the first choice act for the window's mode and restart the card handler, otherwise act like func_slotb4.
     * @return Zero without a handler or while locked, two when func_slotb4 handled it, otherwise one.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Store the mode and card kind, then create the window.
     * @param associated Full resource source word.
     * @param mode Window mode.
     * @param kind Card kind; anything outside two to four becomes five.
     * @return func_slotf8's result.
     */
    virtual s32 func_slotf4(u32 associated, u8 mode, s8 kind);

    /**
     * @brief Create the panels, texts and the choice grid.
     * @param associated Full resource source word.
     * @return One on success.
     */
    virtual s32 func_slotf8(u32 associated);

    /**
     * @brief Open the result window for the selected card slot, close the slot list for card kinds two to four and close this window.
     * @return Zero when the result window couldn't be allocated, otherwise one.
     */
    s32 func_0034E3B0();

    /** @brief Open the save window for the selected slot and restart the card handler with the slot and card kind. */
    void func_0034E230();

    /** @brief Clear the window's state and set its default mode, card kind and colours. */
    void func_0034F310();

    CardTask* unka8;
    FieldObject23CEA0* grid;
    u8 mode;
    u8 unkb1;
    s16 unkb2;
    s16 slot;
    s8 kind;
    u8 unkb7;
    LibWidgetColors4C5590 colors;
    LibTextWidget* first_text;
    LibTextWidget* second_text;
    u8 unkd0;
    u8 unkd1[3];
    void* unkd4;
    FieldClass153170* marker;
    u8 unkdc;
};

/** Partial 0xC4-byte yes/no dialog offering to format an unformatted memory card (message 0x50D), with MAIN vtable at 0x18A920. */
class CardFormatPromptWindow : public FieldClass15AE70
{
public:
    CardFormatPromptWindow()
    {
        unka8 = 0;
        grid = 0;
        first_text = 0;
        second_text = 0;
        unkb8 = 0;
        marker = 0;
        locked = 0;
    }

    virtual ~CardFormatPromptWindow();

    /** @brief Once this is the focused window, lock it when the card handler finished, otherwise recolour the choices for the grid's cursor. */
    virtual void func_slot5c();

    /** @brief Move the grid in direction two. */
    virtual void func_slot74();

    /** @brief Move the grid in direction three. */
    virtual void func_slot70();

    /**
     * @brief Restore the parent window, close this one and set the alternate window's text unless it's locked.
     * @return Zero while locked, otherwise two.
     */
    virtual u8 func_slotb4();

    /**
     * @brief On the first choice open the result window for the card handler, otherwise act like func_slotb4.
     * @return Zero while locked or without a handler, two when func_slotb4 handled it, otherwise one.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Create the window's panels, texts, grid and marker.
     * @param associated Full resource source word.
     * @return One on success.
     */
    virtual s32 func_slotf4(u32 associated);

    /** @brief Close the slot list and its window, dim the top window's choices and open the follow-up window. */
    void func_003545C0();

    CardTask* unka8;
    FieldObject23CEA0* grid;
    LibTextWidget* first_text;
    LibTextWidget* second_text;
    s32 unkb8;
    FieldClass153170* marker;
    u8 locked;
};

/** Partial save entry the slot list finds by slot number. */
struct CmcRowRecord
{
    u8 unk00[0x10];
    char display_text;
    u8 unk11[0x23];
    s32 slot;
    u32 elapsed_seconds;
    u32 unk3c;
    u32 text_resource_key;
    u8 unk44[8];
    s32 unk4c;
    u8 unk50[8];
    u32 unk58;
    u8 unk5c[4];
    u8 codes[8];
    u8 unk68[0x15];
    u8 unk7d;
};

/** Partial 0x5E0-byte list of the save files on a memory card, with MAIN vtable at 0x189810. */
class CardFileList : public LibClass1721F0
{
public:
    /**
     * @brief Create the slot list for a memory card handler.
     * @param card Memory card handler the list shows.
     */
    CardFileList(CardTask* card);

    virtual ~CardFileList();

    /**
     * @brief While a selection runs, finish it with the chosen index or a cancel, otherwise apply a pending index.
     * @param first First update flag, unused here.
     * @param second Second update flag, unused here.
     * @param third Third update flag, unused here.
     */
    virtual void func_00412C40(bool first, bool second, bool third);

    /**
     * @brief Create a save slot row and its panel, texts, name, play-time digits and separators.
     * @param index Row index, unused here.
     * @return The new row, or null when it or one of its widgets couldn't be set up.
     */
    virtual void* create_row(s32 index);

    /**
     * @brief Called when the selected index changes; does nothing here.
     * @param index Selected index.
     */
    virtual void notify_index(s32 index);

    /** @brief Called when the selection is cancelled; does nothing here. */
    virtual void notify_cancel();

    /**
     * @brief Refresh the visible rows for the slots starting at an index.
     * @param index Slot shown in the first row.
     */
    virtual void func_00412C10(s32 index);

    /**
     * @brief Move every row to x zero, 64 apart vertically starting at the given y.
     * @param value Vertical position of the first row.
     */
    virtual void func_00412C20(float value);

    /**
     * @brief Set the number of slots shown as available and the unk5d6 flag.
     * @param count Slots below this index are available unless a save or file uses them.
     * @param flag Value for unk5d6.
     */
    void set_slot_limit(u16 count, u8 flag)
    {
        unk4c4 = count;
        unk5d6 = flag;
    }

    /** @brief Clear the list state and the 45 slot entries. */
    void func_0034C970();

    /**
     * @brief Set the list up under the runtime's controller, create its rows and widgets and select the card's slot.
     * @param associated Full resource source word.
     * @param count Number of slots.
     * @param unused Unused.
     * @return One on success, or zero when something is missing or fails.
     */
    s32 func_0034C5D0(u32 associated, s32 count, s32 unused);

    /**
     * @brief Rebuild the slot states from the card's save entries and refresh the rows.
     * @return One.
     */
    s32 func_0034C460();

    /**
     * @brief Find the save entry for a slot number among the card's entries.
     * @param slot Slot number, counting from zero.
     * @return The entry, or null when no entry has that slot.
     */
    CmcRowRecord* func_0034BB50(u16 slot);

    /**
     * @brief Get the save entry for a slot index.
     * @param index Slot index.
     * @return The entry, or null when the index is out of range.
     */
    CmcRowRecord* entry(s32 index)
    {
        if (index < 0)
        {
            return 0;
        }
        else if (index > 0x2D)
        {
            return 0;
        }

        return entries[index];
    }

    /**
     * @brief Check the selection state.
     * @param state State to compare with.
     * @return True when the list is in that state.
     */
    bool in_state(s32 state)
    {
        return unk4a4 == state;
    }

    /**
     * @brief Get the cursor position.
     * @return The cursor position.
     */
    s32 cursor()
    {
        return unk308;
    }

    /** @brief Cancel the running selection. */
    void cancel()
    {
        unk4a4 = 3;
        unk30c = -1;
        unk308 = -1;
        unk316 = -1;
    }

    u32 resource_source;
    CardMenuController* controller;
    CardTask* card;
    CmcRowRecord* found;
    u16 unk4c0;
    u8 unk4c2;
    u16 unk4c4;
    u8 unk4c6[45];
    CmcRowRecord* entries[45];
    s8 unk5a8[45];
    u8 unk5d5;
    u8 unk5d6;
    u8 unk5d7[9];
};

/** Partial 0xC4-byte window shown while saving, with a progress bar (message 0x531), with MAIN vtable at 0x18A520. */
class CardSavingWindow : public FieldClass15AE70
{
public:
    CardSavingWindow()
    {
        unka8 = 0;
        unkb0 = 0;
        unkb4 = 0.0f;
        unkac = 0;
        unkb8 = 0;
        unkbc = 360.0f;
        unkc0 = 0;
    }

    virtual ~CardSavingWindow();

    /** @brief Once this is the focused window, follow the memory card handler's progress. */
    virtual void func_slot5c();

    /**
     * @brief Create the window's widgets.
     * @param associated Full resource source word.
     * @return One on success.
     */
    virtual s32 func_slotf4(u32 associated);

    /** @brief Open the save confirmation window under the controller's slot window, close the parent's slot list and this window. */
    void func_00352D40();

    CardTask* unka8;
    LibPanel* unkac;
    CardProgressBar* unkb0;
    float unkb4;
    u8 unkb8;
    u8 unkb9[3];
    float unkbc;
    u8 unkc0;
};

/** Partial window listing the card's save files to save over, with MAIN vtable at 0x189D20. */
class CardSaveListWindow : public FieldClass15AE70
{
public:
    CardSaveListWindow()
    {
        unka8 = 0;
        unkac = 0;
        list = 0;
        unkb4 = 0;
        unkb6 = 0;
        unkb8 = 0;
        unkc1 = 0;
        unkc0 = 0;
        unkbc = -1;
        unkc2 = 0;
    }

    virtual ~CardSaveListWindow();

    /** @brief Once this is the focused window, follow the memory card handler's progress. */
    virtual void func_slot5c();

    /**
     * @brief Create the save slot list for the card handler, show the controller's slot window and open the frame.
     * @param associated Full resource source word.
     * @return Zero when something is missing or the list already exists, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    /** @brief Close the slot list and this window and open the result window for the selected card slot. */
    void func_0034F830();

    CardMenuController* unka8;
    CardTask* unkac;
    CardFileList* list;
    u16 unkb4;
    u8 unkb6;
    u8 unkb7;
    FieldClass15AE70* unkb8;
    s32 unkbc;
    u8 unkc0;
    u8 unkc1;
    u8 unkc2;
};

/** Partial window listing the card's save files to load, with MAIN vtable at 0x189E20. */
class CardLoadListWindow : public FieldClass15AE70
{
public:
    CardLoadListWindow()
    {
        unka8 = 0;
        unkac = 0;
        list = 0;
        unkb4 = 0;
        unkb6 = 0;
        unkb8 = 0;
        unkc1 = 0;
        unkc0 = 0;
        unkbc = -1;
        unkc2 = 0;
    }

    virtual ~CardLoadListWindow();

    /** @brief Once this is the focused window, follow the memory card handler's progress. */
    virtual void func_slot5c();

    /**
     * @brief Create the save slot list for the card handler, show the controller's slot window and open the frame.
     * @param associated Full resource source word.
     * @return Zero when something is missing or the list already exists, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    /** @brief Close the slot list and this window and open the result window for the selected card slot. */
    void func_00350260();

    CardMenuController* unka8;
    CardTask* unkac;
    CardFileList* list;
    u16 unkb4;
    u8 unkb6;
    u8 unkb7;
    FieldClass15AE70* unkb8;
    s32 unkbc;
    u8 unkc0;
    u8 unkc1;
    u8 unkc2;
};

/** Partial window shown while loading (message 0x532), with MAIN vtable at 0x18A420. */
class CardLoadingWindow : public FieldClass15AE70
{
public:
    /** @brief Start with no card handler and the runtime's controller. */
    CardLoadingWindow();

    virtual ~CardLoadingWindow();

    /** @brief Once this is the focused window, follow the memory card handler's progress. */
    virtual void func_slot5c();

    /**
     * @brief Take the card handler, then create the frame, its panel and two resource texts.
     * @param associated Full resource source word.
     * @return Zero when the handler or a widget is missing, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    /**
     * @brief Open the save result window, optionally closing the parent's slot list, and close this window.
     * @param close_parent One to close the parent window and its slot list and attach to the controller's slot window.
     * @return One.
     */
    s32 func_00352230(u8 close_parent);

    /**
     * @brief Ask the controller for the error window that matches a card result code.
     * @param code Card result code; 0x81, 0x83, 0x85 and 0x86 map to their windows, zero asks for nothing.
     */
    void request_error_window(s32 code)
    {
        if (code == 0x81)
        {
            code = 0x76;
        }
        else if (code == 0x85)
        {
            code = 0x79;
        }
        else if (code == 0x83)
        {
            code = 0x78;
        }
        else if (code == 0x86)
        {
            code = 0x75;
        }

        if (code != 0)
        {
            unkac->unk54 = code;
        }
    }

    CardTask* unka8;
    CardMenuController* unkac;
};

/** 0x2C-byte progress bar drawn into its own model, with MAIN vtable at 0x188D80. */
class CardProgressBar : public LibListObject
{
public:
    CardProgressBar() : draw_buffer(0), model(0)
    {
    }

    virtual ~CardProgressBar();

    /** @brief Detach from the owner, detach and destroy the model, then delete the bar. */
    virtual void destroy();

    /**
     * @brief Draw the bar's border, outline and a fill proportional to done / total.
     * @param done Completed amount.
     * @param total Total amount.
     */
    void func_00348520(s32 done, s32 total);

    /**
     * @brief Recreate the bar's draw buffer and model, set the model up, draw the bar empty and show it.
     * @param width Bar width.
     * @param height Bar height.
     * @param color Bar color.
     * @param mode Draw mode.
     */
    void func_003492E0(s32 width, s32 height, u32 color, s32 mode);

    LibDrawBuffer* draw_buffer;
    LibModel* model;
    s32 width;
    s32 height;
    u32 color;
    s32 mode;
};

/** Partial memory card task: runs the card checks, loads and saves for the menu, with MAIN vtable at 0x18AFB0. */
class CardTask : public LibListObject
{
public:
    virtual ~CardTask();

    /** @brief Initialize the handler with nothing selected. */
    CardTask();

    /**
     * @brief Return the handler's list kind.
     * @return Two.
     */
    virtual s32 get_default_list_kind();

    /** @brief Release the Field object and the memory card, then queue the handler for release. */
    virtual void destroy();

    /** @brief Run the selected memory card operation one frame further. */
    virtual void update();

    /**
     * @brief Read the result of the last operation's check step.
     * @return The result, or -1 when the check failed or didn't run.
     */
    s32 get_unk5c()
    {
        return unk5c;
    }

    /**
     * @brief Finish the running operation.
     * @param other Value for unk39.
     */
    void stop(u8 other)
    {
        unk1e = 0;
        unk39 = other;
        unk34 = 1;
    }

    /**
     * @brief Run one step of the selected card slot's two-step check.
     * @return Zero while the check runs, one once it passed, or -1 on failure.
     */
    s32 func_0035AE70();

    /**
     * @brief Record the file just read as a save entry, then start reading the next file or finish.
     * @param skip Nonzero to skip recording the entry.
     */
    void func_00359970(s32 skip);

    /**
     * @brief Read the card object's byte at offset 0x28.
     * @return Stored byte.
     */
    u8 func_00359C10();

    /**
     * @brief Read the Field save object's word at offset 0x1250, clamped to zero.
     * @return The word, or zero when it isn't positive.
     */
    s32 func_00359C20();

    /**
     * @brief Run one step of loading the selected card slot into the Field object.
     * @return Zero while the load runs, one once a step finished, or -1 when the Field object isn't ready.
     */
    s32 func_00359DA0();

    /**
     * @brief Run one step of saving the Field object's data to the selected card slot.
     * @return Zero while the save runs, one once it finished, or -1 when the data isn't ready.
     */
    s32 func_00359C50();

    /**
     * @brief Create the memory card and the Field object and open both card slots.
     * @return One on success, or zero when an allocation or the Field object's setup fails.
     */
    u8 func_0035AFF0();

    /**
     * @brief Select a record and reset the run state for the given mode.
     * @param index Record index to select.
     * @param mode Run mode; mode one skips the colour defaults.
     */
    void func_0035ADD0(s16 index, u8 mode);

    /**
     * @brief Set the state and the companion byte, clearing unk1e when the state is one.
     * @param value New state.
     * @param other New companion byte.
     */
    void func_0035ADA0(u8 value, u8 other);

    /**
     * @brief Reset the state for a new run starting at unk1e = value.
     * @param value Starting value for unk1e.
     */
    void func_0035AF60(s16 value);

    /**
     * @brief Read the selected card slot's formatted flag.
     * @return Formatted flag.
     */
    s32 func_0035AF80();

    /**
     * @brief Read the selected card slot's free space.
     * @return Free space.
     */
    s32 func_0035AFA0();

    /**
     * @brief Read unk22.
     * @return Stored value.
     */
    s16 func_0035AFC0();

    /**
     * @brief Read a card slot's state.
     * @param index Card slot.
     * @return Card state.
     */
    s32 func_0035AFD0(s16 index);

    LibMemoryCard* card;
    FieldClass15B9C0* unk18;
    s16 selected;
    s16 unk1e;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    u8 unk26[2];
    s32 unk28;
    s32 unk2c;
    s32 unk30;
    u8 unk34;
    u8 unk35;
    s16 unk36;
    u8 unk38;
    u8 unk39;
    u8 unk3a[2];
    s32 unk3c;
    u8 unk40;
    u8 mode;
    u8 unk42[2];
    u8 unk44;
    u8 unk45;
    s16 unk46;
    u8 unk48;
    u8 unk49;
    u8 unk4a[2];
    s32 unk4c;
    s32 unk50;
    u16 unk54;
    u8 unk56[2];
    s32 unk58;
    s32 unk5c;
    u8 unk60;
    u8 unk61[3];
    s32 unk64;
    u8 unk68;
    u8 unk69;
    u8 unk6a[2];
};

/** Partial eight-byte base of a save file list row, with MAIN vtable at 0x188DA0. */
class CardListRow
{
public:
    CardListRow()
    {
    }

    virtual ~CardListRow()
    {
    }

    /**
     * @brief Set the row widget byte flags.
     * @param unused Unused owner argument.
     * @param value Byte flag value.
     */
    virtual void func_0034D880(void* unused, u8 value) = 0;

    /**
     * @brief Refresh the row widgets.
     * @param owner Containing list owner.
     * @param index Signed row index.
     */
    virtual void refresh_row(void* owner, s32 index) = 0;

    /**
     * @brief Position the row widgets.
     * @param owner Containing list owner.
     * @param x Horizontal position.
     * @param y Vertical position.
     */
    virtual void position_row(void* owner, float x, float y) = 0;

    /**
     * @brief Return zero as a floating-point value.
     * @return Zero.
     */
    virtual float func_00358F80();

    u8 unk04;
    u8 unk05;
    u8 pad06[2];
};

/** 0xD10-byte save file list row: a panel, text widgets and five numeric widgets for the play time. */
class CardFileRow : public CardListRow
{
public:
    /** @brief Initialize the embedded widgets and root state. */
    CardFileRow();

    virtual ~CardFileRow();

    /**
     * @brief Set the row widget byte flags.
     * @param unused Unused owner argument.
     * @param value Byte flag value.
     */
    virtual void func_0034D880(void* unused, u8 value);

    /**
     * @brief Refresh the row widgets.
     * @param owner Containing list owner.
     * @param index Signed row index.
     */
    virtual void refresh_row(void* owner, s32 index);

    /**
     * @brief Position the row widgets.
     * @param owner Containing list owner.
     * @param x Horizontal position.
     * @param y Vertical position.
     */
    virtual void position_row(void* owner, float x, float y);

    LibPanel panel;
    LibTextWidget first_text;
    LibStringLabel string_widget;
    LibTextWidget second_text;
    LibObject174F20 numbers[5];
    LibTextWidget array_text[2];
    LibTextWidget third_text;
    LibTextWidget fourth_text;
};

/** Partial 0xB0-byte window saying MEMORY CARD slot 1 or 2 is empty (messages 0x535 and 0x536), with MAIN vtable at 0x189920. */
class CardSlotEmptyWindow : public FieldClass15AE70
{
public:
    CardSlotEmptyWindow() : unka8(-1), unkac(0)
    {
    }

    virtual ~CardSlotEmptyWindow();

    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when either widget couldn't be allocated, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    s16 unka8;
    u8 unkaa[2];
    LibTextWidget* unkac;
};

/** Partial 0xA8-byte memory card error window (message 0x50F), with MAIN vtable at 0x189A20. */
class CardErrorWindow : public FieldClass15AE70
{
public:
    virtual ~CardErrorWindow();

    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when either widget couldn't be allocated, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

};

/** Partial 0xA8-byte window saying the card has no Star Ocean data (message 0x527), with MAIN vtable at 0x189F20. */
class CardNoDataWindow : public FieldClass15AE70
{
public:
    virtual ~CardNoDataWindow();

    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when either widget couldn't be allocated, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

};

/** Partial 0xA8-byte "Load failed" window (message 0x511), with MAIN vtable at 0x18A020. */
class CardLoadFailedWindow : public FieldClass15AE70
{
public:
    virtual ~CardLoadFailedWindow();

    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when either widget couldn't be allocated, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

};

/** Partial 0xB0-byte "Load Successful" window (message 0x2341), with MAIN vtable at 0x18A120. */
class CardLoadedWindow : public FieldClass15AE70
{
public:
    /** @brief Clear the window and play the confirmation sound. */
    CardLoadedWindow()
    {
        unkac = 0;
        unka8 = 0;
        resident_sound_play(g_sound, 4, 0, 0, 0x7F, 0x40, 0);
    }

    /**
     * @brief Close this window, then either finish the card menu or reopen the slot window's request after closing the parent's slot list.
     * @return One.
     */
    virtual u8 func_slotb0();

    virtual ~CardLoadedWindow();

    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when a required object is missing, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    void* unkac;
};

/** Partial 0xA8-byte "Save failed" window (message 0x510), with MAIN vtable at 0x18A220. */
class CardSaveFailedWindow : public FieldClass15AE70
{
public:
    virtual ~CardSaveFailedWindow();

    /**
     * @brief Restore the parent window, queue this window, and set the alternate window text key.
     * @return One.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when either widget couldn't be allocated, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

};

/** Partial 0xB0-byte "Save Successful" window (message 0x517), with MAIN vtable at 0x18A320. */
class CardSavedWindow : public FieldClass15AE70
{
public:
    /** @brief Clear the window and play the confirmation sound. */
    CardSavedWindow()
    {
        unka8 = 0;
        unkac = 0;
        resident_sound_play(g_sound, 4, 0, 0, 0x7F, 0x40, 0);
    }

    /**
     * @brief Unless locked, store the card's record back into the Field object, refresh the slot list, restore the parent, and close the parent too when the controller asks for it.
     * @return Zero while locked, otherwise one.
     */
    virtual u8 func_slotb0();

    virtual ~CardSavedWindow();

    /**
     * @brief Run the window action when its guard byte is clear.
     * @return Zero when guarded, otherwise one after running the action.
     */
    virtual u8 func_slotb4();

    /** @brief Once this is the focused window and the card handler finished, lock the window and finish it. */
    virtual void func_slot5c();

    /** @brief Open the result window for the selected card slot, then close the slot list and its window and this window. */
    void func_003519B0();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when a required object is missing, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
    u8 unkac;
    u8 unkad[3];
};

/** Partial 0xA8-byte "Format failed" window (message 0x523), with MAIN vtable at 0x18A620. */
class CardFormatFailedWindow : public FieldClass15AE70
{
public:
    CardFormatFailedWindow()
    {
    }

    /**
     * @brief Handle the window action.
     * @return Action status.
     */
    virtual u8 func_slotb0();

    virtual ~CardFormatFailedWindow();

    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual u8 func_slotb4();

    /** @brief Check whether this is the focused window; nothing else happens either way. */
    virtual void func_slot5c();

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when either widget couldn't be allocated, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);
};

/** Partial 0xB0-byte window saying the card lacks free space (message 0x50E), with MAIN vtable at 0x18A820. */
class CardNoSpaceWindow : public FieldClass15AE70
{
public:
    CardNoSpaceWindow()
    {
        unka8 = 0;
        text_key = 0;
    }

    /**
     * @brief Handle the window action.
     * @return Action status.
     */
    virtual u8 func_slotb0();

    virtual ~CardNoSpaceWindow();

    /**
     * @brief Run the window action and return status one.
     * @return One.
     */
    virtual u8 func_slotb4();

    /** @brief Perform no work. */
    virtual void func_slot5c();

    /**
     * @brief Take the card handler, then create the frame, its panel and its resource text.
     * @param associated Full resource source word.
     * @return Zero when the handler or a widget is missing, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    CardTask* unka8;
    s32 text_key;
};

/** Partial 0xCC-byte window interface, with MAIN vtable at 0x189C20. */
class CmcClass189C20 : public FieldClass15AE70
{
public:
    CmcClass189C20()
    {
        for (s32 index = 0; index < 8; index++)
        {
            displays[index] = 0;
        }
    }

    virtual ~CmcClass189C20();

    /** @brief Release nested displays and unregister this window. */
    virtual void func_slot0c();

    /**
     * @brief Create the eight option resource displays in a row and the resource text below them.
     * @param associated Full resource source word.
     * @return One.
     */
    virtual s32 func_slotf4(u32 associated);

    /**
     * @brief Hide the eight displays, then show one per nonzero code in a save entry's code list.
     * @param codes Eight resource codes; zero entries are skipped.
     * @param show Zero to only hide the displays.
     * @return Zero when showing without a code list, otherwise one.
     */
    s32 func_0034F3F0(const u8* codes, u8 show);

    ItemCreationOptionResourceDisplay* displays[8];
    LibTextWidget* unkc8;
};

/** Partial 0xB4-byte window shown while a memory card is checked (message 0x51A), with MAIN vtable at 0x18AA20. */
class CardCheckingWindow : public FieldClass15AE70
{
public:
    CardCheckingWindow()
    {
        unka8 = 0;
        unkac = -1;
        unkb0 = 0;
    }

    /** @brief Once this is the focused window, act on the memory card handler's result and open the window that follows it. */
    virtual void func_slot5c();

    virtual ~CardCheckingWindow();

    /**
     * @brief Set display flags on selected lists.
     * @param flag Display flag word.
     * @param list_mask List groups selected by bits 0 through 6.
     */
    virtual void func_slot18(u32 flag, u32 list_mask);

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when a required object is missing, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    /**
     * @brief Open the save slot list window for the card handler and close this window.
     * @param count Number of slots shown as available, used when it's a valid slot count.
     * @param flag Slot list flag stored with the count.
     */
    void func_00355080(s32 count, u8 flag);

    /**
     * @brief Open the card progress window for the card handler and close this window.
     * @param count Number of slots shown as available, used when it's a valid slot count.
     * @param flag Slot list flag stored with the count.
     */
    void func_00355240(s32 count, u8 flag);

    CardTask* unka8;
    s32 unkac;
    u8 unkb0;
};

/** Partial 0xAC-byte window saying the chosen slot has no memory card (message 0x519), with MAIN vtable at 0x18AB20. */
class CardNoCardWindow : public FieldClass15AE70
{
public:
    CardNoCardWindow() : unka8(0)
    {
    }

    /**
     * @brief Handle the window action.
     * @return Action status.
     */
    /**
     * @brief Restore the parent window, dim its two choices, close this window and set the alternate text.
     * @return One.
     */
    virtual u8 func_slotb0();

    virtual ~CardNoCardWindow();

    /**
     * @brief Restore the parent window, dim its two choices, close this window and set the alternate text.
     * @return Two.
     */
    virtual u8 func_slotb4();

    /**
     * @brief Set display flags on selected lists.
     * @param flag Display flag word.
     * @param list_mask List groups selected by bits 0 through 6.
     */
    virtual void func_slot18(u32 flag, u32 list_mask);

    /**
     * @brief Create the window frame, its panel, and its resource text.
     * @param associated Full resource source word.
     * @return Zero when a required object is missing, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    CardMenuController* unka8;
};

/** Partial 0xC0-byte window choosing MEMORY CARD slot 1 or 2, with MAIN vtable at 0x18AC20. */
class CardSlotSelectWindow : public FieldClass15AE70
{
public:
    CardSlotSelectWindow()
    {
        unka8 = 0;
        grid = 0;
        unkb0 = 0;
        unkb4 = 0;
        unkb8 = 1;
        unkb9[0] = 0;
        unkb9[1] = 0;
        marker = 0;
    }

    /** @brief While this is the focused window, colour both card slots by readiness, move the marker, and close the menu once confirmed. */
    virtual void func_slot5c();

    virtual ~CardSlotSelectWindow();

    /**
     * @brief Set list flags and the target display byte flag when the low flag byte is one.
     * @param flag Display flag word.
     * @param list_mask List groups selected by bits 0 through 6.
     */
    virtual void func_slot18(u32 flag, u32 list_mask);

    /**
     * @brief Find the final associated window.
     * @return Last window in the chain, including this window when it has no association.
     */
    virtual void* func_slot3c();

    /**
     * @brief Set the window control byte to one and return status two.
     * @return Two.
     */
    virtual u8 func_slotb4();

    /** @brief Move the grid in direction one while the window is unlocked and the grid is enabled. */
    virtual void func_slot6c();

    /** @brief Move the grid in direction zero while the window is unlocked and the grid is enabled. */
    virtual void func_slot68();

    /**
     * @brief Confirm the grid's card slot: open the slot window when it's ready, otherwise the card error window.
     * @return Zero while locked or disabled, three after opening the error window, otherwise one.
     */
    virtual u8 func_slotb0();

    /**
     * @brief Create the card slot window's panel, both slot texts, the grid and its marker.
     * @param associated Full resource source word.
     * @return Zero when the card handler or a widget is missing, otherwise one.
     */
    virtual s32 func_slotf4(u32 associated);

    /**
     * @brief Select a card slot and open the slot window under this one.
     * @param slot Card slot.
     */
    void func_003568C0(s16 slot);

    CardTask* unka8;
    FieldObject23CEA0* grid;
    LibTextWidget* unkb0;
    LibTextWidget* unkb4;
    u8 unkb8;
    u8 unkb9[2];
    u8 unkbb;
    FieldClass153170* marker;
};

/** Active window receiver directory reached through the Field runtime. */
struct FieldWindowCallbacks
{
    u8 unk00[0x14];
    FieldClass153E30* unk14;
    u8 unk18[2];
    u16 unk1a;
};

/** Partial menu state the card windows signal when they close. */
struct CmcMenuState
{
    /**
     * @brief Check whether the menu is closing.
     * @return True when the closing flag is set.
     */
    bool is_closing()
    {
        return unk2d != 0;
    }

    u8 unk00[0x2D];
    u8 unk2d;
    u8 unk2e[0x6D];
    u8 unk9b;
    u8 unk9c;
    u8 unk9d;
    u8 unk9e;
};

/** Field runtime prefix containing the active window directory. */
struct FieldWindowRuntime
{
    ResidentCheckedRecord* unk00;
    u8 unk04[8];
    CmcMenuState* unk0c;
    FieldWindowCallbacks* unk10;
    u8 unk14[0xC];
    FieldBufferSlots* slots;
};

#endif

typedef struct CmcDrawParameters CmcDrawParameters;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the drawing parameters to their defaults.
 * @param parameters Drawing parameters to initialize.
 */
void cmc_initialize_drawing_parameters(CmcDrawParameters* parameters);

#ifdef __cplusplus
}
#endif

#endif
