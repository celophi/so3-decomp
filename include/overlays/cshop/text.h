#ifndef SO3_OVERLAYS_CSHOP_TEXT_H
#define SO3_OVERLAYS_CSHOP_TEXT_H

#include "types.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0023B1D0.h"

#ifdef __cplusplus
class FieldClass15BB90;
class ItemCreationClass172870;

/** Shop list window using the Field callbacks at offset 0xA8. */
struct ShopClass187DA0 : public FieldClass15AD40
{
    LibObject172410* first[5];
    LibObject174F20* second[5];
    LibObject172440* third[8];
    ItemCreationClass172870* unk180;
    LibClass178630* extra;
    /** @brief Clear the paired row displays and initialize a temporary list base. */
    ShopClass187DA0()
    {
        for (s32 i = 0; i < 5; i++)
        {
            first[i] = 0;
            second[i] = 0;
        }
        FieldClass15AD40();
    }
    /** @brief Destroy the Field list window. */
    virtual ~ShopClass187DA0();
    /** @brief Update the visible shop list. */
    virtual void func_slot5c();
    /** @brief Open the selected shop action. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Return to the associated window. @return Transition result. */
    virtual s32 func_slotb4();
    /** @brief Open the selected record action. @return Action result. */
    virtual s32 func_slotbc();
    /** @brief Refresh the visible record displays. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the visible record displays. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    /** @brief Create the list displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Set the paired display flags. @param first First display flag. @param second Second display flag. */
    virtual void func_slot10c(u32 first, u32 second);
};

/** Shop list window with the Field callbacks at offset 0xA8. */
struct ShopClass187EC0 : public FieldClass15AD40
{
    /** @brief Clear the paired display pointers and initialize a temporary list base. */
    ShopClass187EC0()
    {
        for (s32 i = 0; i < 6; i++)
        {
            first[i] = 0;
            second[i] = 0;
        }
        FieldClass15AD40();
    }
    LibObject172410* first[6];
    LibObject174F20* second[6];
    LibClass178630* extra;
    u16 codes[750];
    /** @brief Destroy the Field list window. */
    virtual ~ShopClass187EC0();
    /** @brief Update the current catalog selection and its highlight. */
    virtual void func_slot5c();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotb0();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotb4();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotbc();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotc8();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotcc();
    /** @brief Refresh the visible records. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the visible records. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    /** @brief Create the list displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Set the paired display flags. @param first First display flag. @param second Second display flag. */
    virtual void func_slot10c(u32 first, u32 second);
};
/** Shop list window with the Field callbacks at offset 0xA8. */
struct ShopClass1880E0 : public FieldClass15AD40
{
    LibObject172410* first[6];
    LibObject174F20* second[6];
    LibObject178750* third[6];
    LibObject174F20* fourth[6];
    LibObject178750* fifth[6];
    LibObject174F20* sixth[6];
    LibClass178630* extra;
    s32 countdown;
    /** @brief Clear the owned row displays and initialize a temporary list base. */
    ShopClass1880E0();
    /** @brief Destroy the Field list window. */
    virtual ~ShopClass1880E0();
    /** @brief Update the current bucket selection, highlight, and countdown. */
    virtual void func_slot5c();
    /** @brief Remove one selected code and refresh its row. */
    virtual void func_slot70();
    /** @brief Add one selected code and refresh its row. */
    virtual void func_slot74();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotb0();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotb4();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotb8();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotbc();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotc8();
    /** @brief Run the list window hook. @return Handler result. */
    virtual s32 func_slotcc();
    /** @brief Refresh the visible records. @param start First record index. */
    virtual void refresh_rows(s32 start);
    /** @brief Position the visible records. @param start Base vertical coordinate. */
    virtual void set_scroll_position(float start);
    /** @brief Create the list displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slot104(u32 associated);
    /** @brief Set the paired display flags. @param first First display flag. @param second Second display flag. */
    virtual void func_slot10c(u32 first, u32 second);
};

/** Partial Field window using resident vtable 0x187FE0. */
struct ShopClass187FE0 : public FieldClass15AE70
{
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass187FE0();
    /** @brief Window hook at virtual offset 0xC. */
    virtual void func_slot0c();
    /** @brief Window hook at virtual offset 0x5C. */
    virtual void func_slot5c();
    /** @brief Request cancellation of the attached status window when present. @return Always two. */
    virtual s32 func_slotb4();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    /** @brief Clear the display pointers and initialize the temporary base window. */
    ShopClass187FE0();
    void* unka8;
    void* unkac;
    void* unkb0;
    void* unkb4;
    void* unkb8;
    void* unkbc;
    void* unkc0;
    void* unkc4;
    void* unkc8;
    void* unkcc;
    void* unkd0;
    void* unkd4;
    void* unkd8;
    LibClass178630* unkdc;
    LibObject178660* unke0;
    FieldClass15BB90* unke4;
    u8 unke8;
};

/** Partial Field window using resident vtable 0x188200. */
struct ShopClass188200 : public FieldClass15AE70
{
    /** @brief Clear the three numeric display pointers. */
    ShopClass188200() : first(0), second(0), third(0)
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass188200();
    /** @brief Window hook at virtual offset 0x5C. */
    virtual void func_slot5c();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject174F20* first;
    LibObject174F20* second;
    LibObject174F20* third;
};

/** Partial Field window using resident vtable 0x188300. */
struct ShopClass188300 : public FieldClass15AE70
{
    /** @brief Clear the choice display pointer. */
    ShopClass188300() : choice(0)
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass188300();
    /** @brief Window hook at virtual offset 0x5C. */
    virtual void func_slot5c();
    /** @brief Window hook at virtual offset 0x70. */
    virtual void func_slot70();
    /** @brief Window hook at virtual offset 0x74. */
    virtual void func_slot74();
    /** @brief Window hook at virtual offset 0xB0. */
    virtual s32 func_slotb0();
    /** @brief Window hook at virtual offset 0xB4. */
    virtual s32 func_slotb4();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* choice;
    LibObject178750* text;
    LibObject178750* first;
    LibObject178750* second;
    LibClass174C40* unkb8;
    LibClass174C40* unkbc;
};

/** Shop details window with five paired value rows. */
struct ShopClass188400 : public FieldClass15AE70
{
    LibObject174D90* unka8;
    LibObject178750* unkac;
    LibObject178750* unkb0;
    LibObject178750* unkb4;
    LibObject178750* first[5];
    LibObject178750* second[5];
    LibObject174F20* numbers[5];
    u32 unkf4;
    u8 unkf8;
    /** @brief Clear the description pointers and toggle state. */
    ShopClass188400() : unka8(0), unkac(0), unkf4(0), unkf8(0)
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass188400();
    /** @brief Window hook at virtual offset 0x5C. */
    virtual void func_slot5c();
    /**
     * @brief Create the description displays and five paired value rows.
     * @param associated Full resource source word.
     * @return One after creating the displays, or zero for a missing resource slot.
     */
    virtual s32 func_slotf4(u32 associated);
};

/** Partial Field window using resident vtable 0x188500. */
struct ShopClass188500 : public FieldClass15AE70
{
    void* unka8;
    u8 unkac[0x48];
    /** @brief Clear the window display pointer. */
    ShopClass188500() : unka8(0)
    {
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass188500();
    /** @brief Window hook at virtual offset 0x5C. */
    virtual void func_slot5c();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
};

/** Partial Field window using resident vtable 0x188600. */
struct ShopClass188600 : public FieldClass15AE70
{
    /** @brief Clear the message display and scroll state. */
    ShopClass188600()
    {
        text = 0;
        width = 0;
        timer = 0;
        key = 0;
        scrolling = 0;
        label_width = 0;
        origin = 0;
        bound = 0;
        extra = 0;
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass188600();
    /** @brief Window hook at virtual offset 0x5C. */
    virtual void func_slot5c();
    /** @brief Set the window text. @param text_key Text key before the resource offset. */
    virtual void func_slot60(s32 text_key);
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* text;
    s32 width;
    s16 timer;
    u8 scrolling;
    u8 unkb3;
    s32 key;
    float label_width;
    float origin;
    float bound;
    float extra;
};

/** Partial Field window using resident vtable 0x188700. */
struct ShopClass188700 : public FieldClass15AE70
{
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass188700();
    /** @brief Create the window displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
};

/** Choice window with paired text displays and resident vtable 0x187A70. */
struct ShopClass187A70 : public FieldClass15AE70
{
    /** @brief Clear the choice and paired display pointers. */
    ShopClass187A70()
    {
        unka8 = 0;
        yes_label = 0;
        no_label = 0;
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass187A70();
    /** @brief Update the choice with action code three. */
    virtual void func_slot70();
    /** @brief Update the choice with action code two. */
    virtual void func_slot74();
    /** @brief Run the selected action. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Return to the associated State. @return Transition result. */
    virtual s32 func_slotb4();
    /** @brief Create the choice display. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* unka8;
    LibObject178750* yes_label;
    LibObject178750* no_label;
};

/** Choice window with paired text displays and resident vtable 0x187CA0. */
struct ShopClass187CA0 : public FieldClass15AE70
{
    /** @brief Clear the choice and paired display pointers. */
    ShopClass187CA0()
    {
        unka8 = 0;
        unkac = 0;
        unkb0 = 0;
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass187CA0();
    /** @brief Refresh the choice focus flag. */
    virtual void func_slot5c();
    /** @brief Update the choice with action code three. */
    virtual void func_slot70();
    /** @brief Update the choice with action code two. */
    virtual void func_slot74();
    /** @brief Run the selected action. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Return to the associated State. @return Transition result. */
    virtual s32 func_slotb4();
    /** @brief Create the choice display. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* unka8;
    LibObject178750* unkac;
    LibObject178750* unkb0;
};

/** Choice window with two icon displays and resident vtable 0x187BA0. */
struct ShopClass187BA0 : public FieldClass15AE70
{
    /** @brief Clear the choice and paired display pointers. */
    ShopClass187BA0()
    {
        unka8 = 0;
        unkac = 0;
        unkb0 = 0;
    }
    /** @brief Destroy the Field window base. */
    virtual ~ShopClass187BA0();
    /** @brief Update the choice with action code three. */
    virtual void func_slot70();
    /** @brief Update the choice with action code two. */
    virtual void func_slot74();
    /** @brief Run the selected action. @return Action result. */
    virtual s32 func_slotb0();
    /** @brief Return to the associated State. @return Transition result. */
    virtual s32 func_slotb4();
    /** @brief Create the choice display. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* unka8;
    LibObject178750* unkac;
    LibObject178750* unkb0;
};

/** Shop copy of the shared movement storage receiver. */
typedef LibMovementState ShopClass187B90;

/** Shop copy of the shared intrusive-link root. */
typedef LibClass171E80 ShopClass187B68;
/** Shop copy of the shared intrusive-list sentinel. */
typedef LibClass171E90 ShopClass187B78;
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ShopState ShopState;
typedef struct ShopClass188600 ShopScrollingWindow;
typedef struct ShopClass188200 ShopValueDisplay;
typedef struct ObjectField20 ObjectField20;
typedef struct ObjectField34 ObjectField34;
typedef struct ObjectStatusFields ObjectStatusFields;
#ifndef __cplusplus
typedef struct ShopClass187DA0 ShopClass187DA0;
#endif

/**
 * @brief Open the alternate choice window for the selected allocation.
 * @param receiver Window associated with the new choice window.
 * @return Always one.
 */
s32 func_0034A0F0(void* receiver);

/**
 * @brief Open the bucket choice window when the combined count is nonzero.
 * @param receiver Window associated with the new choice window.
 * @return One after opening, or three when the count is zero.
 */
s32 func_0034CC10(void* receiver);

/**
 * @brief Open the choice window when an allocation record is selected.
 * @param receiver Window associated with the new choice window.
 * @return Always one.
 */
s32 func_0034A1E0(void* receiver);

/**
 * @brief Set the text key and reset its scrolling timer.
 * @param object Scrolling text window.
 * @param key Shop text key before the resource key offset.
 */
void func_00350360(ShopScrollingWindow* object, s32 key);

/**
 * @brief Refresh the current text and advance its horizontal scrolling.
 * @param object Scrolling text window.
 */
void func_003503E0(ShopScrollingWindow* object);

/**
 * @brief Set the window state code and flags when its control byte is clear.
 * @param receiver Window callback receiver.
 * @return Zero while the control byte is set, otherwise two.
 */
s32 func_0034DEF0(void* receiver);

/**
 * @brief Select the shop mode from the choice control's signed selection.
 * @param receiver Window containing the choice control.
 * @return Zero while the control byte is set, otherwise one.
 */
s32 func_0034DF50(void* receiver);

/**
 * @brief Return the current window to its associated state when its control byte is clear.
 * @param receiver Window callback receiver.
 * @return Zero while the control byte is set, otherwise two.
 */
s32 func_003488D0(void* receiver);

/**
 * @brief Return the current window to its associated state when its control byte is clear.
 * @param receiver Window callback receiver.
 * @return Zero while the control byte is set, otherwise two.
 */
s32 func_00349110(void* receiver);

/**
 * @brief Return the current window to its associated state when its control byte is clear.
 * @param receiver Window callback receiver.
 * @return Zero while the control byte is set, otherwise two.
 */
s32 func_003499B0(void* receiver);

/**
 * @brief Pass the supplied object to the current state and select state code three.
 * @param object Supplied window or callback object.
 * @return Always two.
 */
s32 func_0034A0A0(void* object);

/**
 * @brief Refresh the checked value and the totals for the current allocation.
 * @param object Numeric display containing the three values.
 */
void func_0034D920(ShopValueDisplay* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348530(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348540(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348550(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348560(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348570(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348580(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348590(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003485F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348600(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348610(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348620(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348630(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348640(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348650(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348660(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348670(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348680(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348690(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486A0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486B0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486E0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003486F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348700(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348710(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348740(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003516A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003516B0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003516C0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351800(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351810(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351890(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351970(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00351BE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351C30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351C40(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351C50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351C60(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351C70(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351C80(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00351C90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351CA0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351CB0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00351CC0(void* object);

/**
 * @brief Set field at offset 0x20.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348960(ObjectField20* object, u32 value);

/**
 * @brief Get field at offset 0x20.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_00349820(ObjectField20* object);

/**
 * @brief Get field at offset 0x34.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_0034A1D0(ObjectField34* object);

/**
 * @brief Get field at offset 0x38.
 * @param object Object containing the field.
 * @return Field value.
 */
u8 func_00351BD0(ObjectStatusFields* object);

/**
 * @brief Set field at offset 0x24.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00351BF0(ObjectStatusFields* object, u32 value);

/**
 * @brief Get field at offset 0x24.
 * @param object Object containing the field.
 * @return Field value.
 */
u32 func_00351C00(ObjectStatusFields* object);

/**
 * @brief Set field at offset 0x28.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00351C10(ObjectStatusFields* object, s8 value);

/**
 * @brief Get field at offset 0x28.
 * @param object Object containing the field.
 * @return Field value.
 */
s8 func_00351C20(ObjectStatusFields* object);


/**
 * @brief Create and attach the shop State windows.
 * @param receiver Current shop State.
 * @return Always one.
 */
s32 func_003510D0(void* receiver);

/**
 * @brief Register a completed resource buffer and finish the receiver setup.
 * @param receiver Current shop State.
 * @param buffer Completed resource buffer.
 * @return Setup result, or zero for a missing buffer.
 */
s32 func_00351460(void* receiver, void* buffer);

/**
 * @brief Check the value associated with the field at offset 0x54.
 * @param object Object containing the field.
 * @return Nonzero if the value is set.
 */
s32 func_00351540(u8* object);

/**
 * @brief Advance the current selection and refresh the receiver.
 * @param object Receiver to refresh.
 * @return Always 1.
 */
s32 func_0034AF50(void* object);

/**
 * @brief Move the current selection backward and refresh the receiver.
 * @param object Receiver to refresh.
 * @return Always 1.
 */
s32 func_0034AFA0(void* object);

/**
 * @brief Advance the current selection and refresh the receiver.
 * @param object Receiver to refresh.
 * @return Always 1.
 */
s32 func_0034CA50(void* object);

/**
 * @brief Move the current selection backward and refresh the receiver.
 * @param object Receiver to refresh.
 * @return Always 1.
 */
s32 func_0034CAA0(void* object);

/**
 * @brief Toggle the current display's byte flag.
 * @param object Callback receiver; unused.
 * @return Always 1.
 */
s32 func_0034AFF0(void* object);

/**
 * @brief Toggle the current display's byte flag.
 * @param object Callback receiver; unused.
 * @return Always 1.
 */
s32 func_0034CAF0(void* object);

/**
 * @brief Create and select the shop message window.
 * @return One after attaching the window.
 */
s32 func_0034CB20(void);

/**
 * @brief Set the current shop state to mode 1.
 * @param object Callback receiver; unused.
 * @return Always 2.
 */
s32 func_0034B020(void* object);

/**
 * @brief Move the current shop selection in the requested direction.
 * @param object Current shop state.
 * @param direction Signed selection step.
 */
void func_00350B30(ShopState* object, s32 direction);

/**
 * @brief Change the current shop mode.
 * @param object Current shop state.
 * @param mode New mode, using its low byte.
 */
void func_00350D00(ShopState* object, u32 mode);

/**
 * @brief Refresh the receiver's element contents.
 * @param object Receiver to refresh.
 * @param value Refresh option.
 */
void func_0034B3C0(void* object, u8 value);

/**
 * @brief Refresh the receiver's element contents.
 * @param object Receiver to refresh.
 * @param value Refresh option.
 */
void func_0034CE00(void* object, u8 value);

/**
 * @brief Release the shop state resources and clear its runtime flags.
 * @param object Shop state to release.
 */
void func_00350FE0(ShopState* object);

/**
 * @brief Enqueue the receiver for resident processing.
 * @param object Receiver to enqueue.
 */
void func_003510B0(void* object);

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void func_00351CD0(FieldCountedList* list, void* value);

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void func_00351D60(FieldCountedList* list, void* value);

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void func_00351DF0(FieldCountedList* list, void* value);

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void func_00351E80(FieldCountedList* list, void* value);

/**
 * @brief Clear the current state's buckets and return to mode 1.
 * @param object Callback receiver; unused.
 * @return Always 2.
 */
s32 func_0034CBD0(void* object);

/**
 * @brief Set the bucket category and derive its runtime-dependent value.
 * @param object Current shop state.
 * @param category Category code to initialize.
 */
void func_00350EC0(ShopState* object, u16 category);

/**
 * @brief Clamp a four-row list's range and selection to the current category's record count.
 * @param object Display containing list parameters and record count.
 */
void func_0034A640(ShopClass187DA0* object);

#ifdef __cplusplus
}
#endif

#endif
