#ifndef SO3_OVERLAYS_LIB_MESSAGE_WINDOW_H
#define SO3_OVERLAYS_LIB_MESSAGE_WINDOW_H

#include "types.h"
#include "overlays/lib/widget_aggregate.h"

class LibMessageWindow;

/** Multiline text of a message window, passing its control codes on to the window. MAIN vtable at 0x174EB0. */
class LibMessageWindowText : public LibObject174D90
{
public:
    virtual ~LibMessageWindowText()
    {
    }

    /** @brief Flag the restart for the window. */
    virtual void func_0045F600();

    /** @brief Flag the end of the text for the window. */
    virtual void func_0045F610();

    /**
     * @brief Pass a three-value control code to the window.
     * @param first First value.
     * @param second Second value.
     * @param third Third value.
     */
    virtual void func_0045F620(s16 first, s16 second, u32 third);

    /**
     * @brief Pass a one-value control code to the window.
     * @param value Control value.
     */
    virtual void func_0045F630(u32 value);

    /**
     * @brief Pass a one-value control code to the window and set its flag byte at 0x1064.
     * @param value Control value.
     */
    virtual void func_0045F640(u32 value);

    /** @brief Flag a control code for the window and set its flag byte at 0x1064. */
    virtual void func_0045F650();

    LibMessageWindow* owner;
};

/** Partial message window: a container holding a panel, two clipping widgets and its multiline text. MAIN vtable at 0x174DD0. */
class LibMessageWindow : public LibContainer
{
public:
    virtual ~LibMessageWindow();

    /**
     * @brief Update and draw the container, then run the hooks for the text events flagged since the last call.
     * @param first Nonzero to chain the widget packets.
     * @param second Nonzero to update the widgets.
     * @param third Nonzero to draw the widgets.
     */
    virtual void func_0044B100(bool first, bool second, bool third);

    virtual void func_00412C40(bool first, bool second, bool third);

    /** @brief Hook run when the text restarts; the base window does nothing. */
    virtual void func_00461960();

    /** @brief Hook run at the end of the text; the base window does nothing. */
    virtual void func_00461970();

    /**
     * @brief Hook for a text control code with three values; the base window does nothing.
     * @param first First value.
     * @param second Second value.
     * @param third Third value.
     */
    virtual void func_00461980(s16 first, s16 second, u32 third);

    /** @brief Hook for the event flagged at 0x105F; the base window does nothing. */
    virtual void func_00461990();

    /** @brief Hook for the event flagged at 0x1060; the base window does nothing. */
    virtual void func_004619A0();

    /** @brief Window hook at slot 0xC8; the base window does nothing. */
    virtual void func_004619B0();

    /**
     * @brief Hook for a text control code with one value; the base window does nothing.
     * @param value Control value.
     */
    virtual void func_004619C0(u32 value);

    /**
     * @brief Hook for a second text control code with one value; the base window does nothing.
     * @param value Control value.
     */
    virtual void func_004619D0(u32 value);

    /** @brief Hook for a text control code; the base window does nothing. */
    virtual void func_004619E0();

    /**
     * @brief Advance from state 4 or 6 to the next state.
     * @return One when the state advanced, otherwise zero.
     */
    s32 func_00461B60();

    /**
     * @brief In state 4 or 6, load new text into the window and go back to state 2.
     * @param source Resource source word.
     * @param key Text resource key.
     * @param mode Drawing mode; its bits 16 and 18 are kept from the current mode.
     * @param flag Resource state flag.
     * @return One when the text was loaded, otherwise zero.
     */
    s32 func_00461BA0(u32 source, s32 key, u32 mode, u32 flag);

    LibClass1722E0 frame;
    LibClass175170 unk180;
    ItemCreationClass1746A0 unka18;
    ItemCreationClass1746A0 unka6c;
    LibMessageWindowText text;
    u32 source;
    s32 key;
    u32 mode;
    s32 state;
    u32 unk1050;
    s16 unk1054;
    s16 unk1056;
    u32 unk1058;
    u8 unk105c;
    u8 unk105d;
    u8 unk105e;
    u8 unk105f;
    u8 unk1060;
    u8 unk1061;
    u8 unk1062;
    u8 unk1063;
    u8 unk1064;
};

#endif
