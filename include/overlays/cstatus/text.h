#ifndef SO3_OVERLAYS_CSTATUS_TEXT_H
#define SO3_OVERLAYS_CSTATUS_TEXT_H

#include "types.h"

typedef struct OverlayList OverlayList;
typedef struct StatusObject StatusObject;
typedef struct StatusResourceState StatusResourceState;
typedef struct StateC000 StateC000;
typedef struct StatusTextWindow StatusTextWindow;
typedef struct StatusContainerWindow StatusContainerWindow;
typedef struct StatusSelectionWindow StatusSelectionWindow;
typedef struct StatusScrollState StatusScrollState;
typedef StatusScrollState StatusRecordWindow;

#ifdef __cplusplus
struct ItemCreationOptionResourceDisplay;
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_0044ABE0.h"

/** Status background window displaying the three resource panels. */
struct StatusBackgroundWindow : public FieldClass15AE70
{
    /** @brief Initialize the background window base. */
    StatusBackgroundWindow()
    {
    }
    /** @brief Destroy the background window base. */
    virtual ~StatusBackgroundWindow();
    /** @brief Create the status resource panels. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
};
/** Status caption window with a timed scrolling text display. */
struct StatusTextWindow : public FieldClass15AE70
{
    /** @brief Initialize the text links and scroll state. */
    StatusTextWindow()
    {
        target = 0;
        distance = 0;
        unkb0[0] = 0;
        timer = 0;
        state = 0;
        label_width = 0;
        initial_x = 0;
        base_x = 0;
        width = 0;
    }
    /** @brief Destroy the caption window base. */
    virtual ~StatusTextWindow();
    /** @brief Update the scrolling text position. */
    virtual void func_slot5c();
    /** @brief Set the selected caption. @param key Signed caption key. */
    virtual void func_slot60(s32 key);
    /** @brief Create the captions and frame geometry. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* target;
    s32 distance;
    u8 unkb0[2];
    s16 timer;
    u8 state;
    float label_width;
    float initial_x;
    float base_x;
    float width;
};

struct OverlayNode;

/** Status display list with an owned sentinel and a virtual destructor. */
struct StatusList188D70
{
    OverlayNode* head;
    s32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    StatusList188D70();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~StatusList188D70();
};

/** Status display list with an owned sentinel and a virtual destructor. */
struct StatusList188D60
{
    OverlayNode* head;
    s32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    StatusList188D60();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~StatusList188D60();
};

/** Status display list with an owned sentinel and a virtual destructor. */
struct StatusList188D50
{
    OverlayNode* head;
    s32 count;
    /** @brief Allocate the sentinel and initialize the empty list. */
    StatusList188D50();
    /** @brief Release the list nodes and sentinel storage. */
    virtual ~StatusList188D50();
};

/** Status record window with three owned lists and two groups of caption displays. */
struct StatusScrollState : public FieldClass15AE70
{
    /** @brief Initialize the record window and its three owned display lists. */
    StatusScrollState();
    /** @brief Release the three display lists and window base. */
    virtual ~StatusScrollState();
    /** @brief Detach the nested container and release the window state. */
    virtual void func_slot0c();
    /** @brief Update nested-display cancellation and window transitions. */
    virtual void func_slot5c();
    /** @brief Refresh the selected record, caption, and markers. */
    virtual void func_slot64();
    /** @brief Select the preceding status display mode. */
    virtual void func_slot68();
    /** @brief Select the following status display mode. */
    virtual void func_slot6c();
    /** @brief Queue the record window exit. @return Handler result. */
    virtual s32 func_slotb0();
    /** @brief Request the alternate status transition. @return Handler result. */
    virtual s32 func_slotb4();
    /** @brief Cycle the selected record variant. @return Handler result. */
    virtual s32 func_slotb8();
    /** @brief Move to the preceding record. @return Handler result. */
    virtual s32 func_slotd8();
    /** @brief Move to the following record. @return Handler result. */
    virtual s32 func_slotdc();
    /** @brief Create the status record displays. @param associated Full resource source word. @return Creation result. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* selection;
    u8 record_active;
    u8 unkad[3];
    LibObject175140* record;
    LibObject178750* caption;
    LibClass178600* marker;
    u16 selected_slot;
    u8 unkbe[2];
    float x;
    float y;
    u8 resource_slots[8];
    float resource_x;
    float resource_y;
    ItemCreationOptionResourceDisplay* display;
    LibClass178600* other_marker;
    LibObject178660* container;
    StatusList188D50 first;
    StatusList188D60 second;
    StatusList188D70 third;
    void* unk108;
    void* unk10c;
    void* unk110;
    void* unk114;
    void* unk118;
    void* unk11c;
    void* unk120;
    void* unk124;
    void* unk128;
    void* unk12c;
    void* unk130;
    void* unk134;
    u8 unk138[4];
    void* unk13c;
    void* unk140;
    void* unk144;
    void* unk148;
    void* unk14c;
    void* unk150;
    void* unk154;
    void* unk158;
    void* unk15c;
    void* unk160;
    void* unk164;
    void* unk168;
    void* unk16c;
    void* unk170;
    void* unk174;
    void* unk178;
    void* unk17c;
    void* unk180;
    void* unk184;
    void* unk188;
    void* unk18c;
    void* unk190;
    void* unk194;
    s32 keys[6];
    s32 option_total;
    u8 mode;
    u8 active;
    u8 unk1b6[2];
    LibClass1725D0* scroll_marker;
    float extent;
    float position;
    float step;
    float delta;
    float timer;
    u8 alternate;
    u8 unk1d1[3];
    FieldStatus14* unk1d4;
    u8 unk1d8;
    u8 unk1d9;
    u8 unk1da;
    u8 unk1db;
    LibObject178750* variant_text;
    LibObject178750* first_tail[4];
    LibObject178750* second_tail[4];
};

/** Status selection window containing the glyph grid and ten saved text rows. */
struct StatusSelectionWindow : public FieldClass15AE70
{
    /** @brief Initialize the glyph grid and saved text rows. */
    StatusSelectionWindow();
    /** @brief Destroy the selection window base. */
    virtual ~StatusSelectionWindow();
    /** @brief Update the visible selection window. */
    virtual void func_slot5c();
    /** @brief Move the selection to the preceding row. */
    virtual void func_slot68();
    /** @brief Move the selection to the following row. */
    virtual void func_slot6c();
    /** @brief Move the selection to the preceding column. */
    virtual void func_slot70();
    /** @brief Move the selection to the following column. */
    virtual void func_slot74();
    /** @brief Handle the current selection command. @return Handler result. */
    virtual s32 func_slotb0();
    /** @brief Run the alternate selection command. @return Handler result. */
    virtual s32 func_slotb4();
    /** @brief Return the default command result. @return Zero. */
    virtual s32 func_slotc0();
    /** @brief Return the default command result. @return Zero. */
    virtual s32 func_slotc4();
    /** @brief Select the final glyph row. */
    virtual void func_slote0();
    /** @brief Restore the selected saved text and markers. */
    virtual void func_slote4();
    /** @brief Create the selection displays. @param associated Associated object. @return Creation result. */
    virtual s32 func_slotf4(void* associated);
    FieldRecordSelection* selection;
    LibObject178750* caption;
    LibObject178750* displays[7];
    LibObject175140* text;
    LibClass178600* cursor;
    u16 glyphs[7];
    u8 unke2[2];
    s32 first_marker;
    s8 selected;
    s8 last_entry;
    u8 entries[24];
    u8 unk102[2];
    float x;
    float y;
    LibClass175030* grid_marker;
    s32 grid_selected;
    u8 grid_mode;
    u8 unk115;
    u16 unk116;
    float left;
    u32 unk11c;
    u32 unk120;
    u32 unk124;
    s8 rows[10][32];
    u8 unk268[0x1C];
    u32 unk284;
    u8 unk288;
    u8 unk289[3];
    LibObject178750* unk28c;
    u8 map290[90];
    u8 map2ea[90];
    u8 map344[80];
};

#endif

extern const char D_00351500[];

extern const char D_00351508[];

extern const char D_00351510[];

extern const char D_00351518[];

extern const char D_00351520[];

extern const char D_00351528[];

extern const char D_00351530[];

extern const char D_00351538[];

extern const char D_00351540[];

extern const char D_00351548[];

/** Byte templates copied into the status selection glyph maps. */
typedef struct StatusGlyphMap90
{
    u8 values[90];
} StatusGlyphMap90;

typedef struct StatusGlyphMap80
{
    u8 values[80];
} StatusGlyphMap80;

#ifdef __cplusplus
extern "C" {
#endif

extern StatusGlyphMap90 D_00351380;
extern StatusGlyphMap90 D_003513E0;
extern StatusGlyphMap80 D_00351440;

/**
 * @brief Initialize the selection window's glyph lookup maps.
 * @param object Status selection receiver.
 */
void func_00348700(StatusSelectionWindow* object);

/**
 * @brief Select the record resource and update its scaled display.
 * @param object Status record and resource window.
 */
void func_0034C500(StatusScrollState* object);

/**
 * @brief Refresh six protected option captions and total their comparison values.
 * @param object Status record window with the current record selection.
 */
void func_0034C640(StatusScrollState* object);

/**
 * @brief Scroll the three status display lists and advance their indicator.
 * @param object Status scroll window.
 */
void func_0034AF00(StatusScrollState* object);

/**
 * @brief Update the selected record, caption rectangle, and status markers.
 * @param object Status record window.
 */
void func_0034BDA0(StatusRecordWindow* object);

/**
 * @brief Create and attach the status windows and record selection.
 * @param object Status resource state.
 * @return One after record selection and window setup succeed, or zero otherwise.
 */
s32 func_00350540(StatusResourceState* object);

/**
 * @brief Load the completed status resource and finish receiver setup.
 * @param object Status resource state.
 * @param buffer Completed resource buffer, or null.
 * @return Zero without a buffer, otherwise the receiver setup result.
 */
s32 func_00350700(StatusResourceState* object, void* buffer);

/**
 * @brief Release the status resource, queue the receiver, and clear its allocation slots.
 * @param object Status resource state to release.
 */
void func_00350160(StatusResourceState* object);

/**
 * @brief Clamp the focused status selection and move its cursor.
 * @param object Status selection window.
 */
void func_00349390(StatusSelectionWindow* object);

/**
 * @brief Move the status selection to the requested entry.
 * @param object Status selection receiver.
 * @param value Requested entry index.
 */
void func_00349440(StatusSelectionWindow* object, s32 value);

/**
 * @brief Append the diacritic associated with the selected grid code.
 * @param object Status selection receiver.
 * @param code Selected grid code.
 */
void func_00348960(StatusSelectionWindow* object, s16 code);

/**
 * @brief Append the selected grid entry and refresh its display.
 * @param object Status selection receiver.
 * @param mode Supplied grid mode.
 */
void func_00349070(StatusSelectionWindow* object, u8 mode);

/**
 * @brief Update the selection command state.
 * @param object Status selection receiver.
 * @return Selection handler result.
 */
s32 func_00348AE0(StatusSelectionWindow* object);

/**
 * @brief Select grid mode two and refresh its display flags.
 * @param object Status selection receiver.
 */
void func_00349260(StatusSelectionWindow* object);

/** @brief Refresh the selected entry and its cursor. @param object Status selection receiver. */
void func_00348C10(StatusSelectionWindow* object);
/** @brief Refresh the current entry display. @param object Status selection receiver. */
void func_00348D00(StatusSelectionWindow* object);
/** @brief Decode the current entry bytes into glyph keys. @param object Status selection receiver. */
void func_00348E50(StatusSelectionWindow* object);
/** @brief Load the selected slot's entries and refresh its display. @param object Status selection receiver. */
void func_003497A0(StatusSelectionWindow* object);

/**
 * @brief Select status entry 88.
 * @param object Status selection receiver.
 */
void func_003498A0(StatusSelectionWindow* object);

/**
 * @brief Begin a status scroll when the requested mode differs from the current mode.
 * @param object Status scroll state.
 * @param mode Requested scroll mode; zero and one choose opposing directions.
 */
void func_0034B0A0(StatusScrollState* object, u16 mode);

/**
 * @brief Request status scroll mode one.
 * @param object Status scroll state.
 */
void func_0034B170(StatusScrollState* object);

/**
 * @brief Request status scroll mode zero.
 * @param object Status scroll state.
 */
void func_0034B190(StatusScrollState* object);

/**
 * @brief Refresh the selected record's status displays.
 * @param object Status record window.
 */
void func_0034B1B0(StatusScrollState* object);

/**
 * @brief Update nested-display cancellation and status-window transitions.
 * @param object Status record window.
 */
void func_0034BEA0(StatusScrollState* object);

/**
 * @brief Create and attach the nested status display when needed.
 * @param object Status state containing the optional nested display.
 */
void func_0034C130(StatusScrollState* object);

/**
 * @brief Cycle the selected record variant or open its nested status display.
 * @param object Status record window.
 * @return Zero without a variant caption, or one after handling the request.
 */
s32 func_0034C2B0(StatusScrollState* object);

/**
 * @brief Request the nested status display when the resident context is available.
 * @param object Status state containing the optional nested display.
 * @return Zero without the resident context, or two after updating the request flags.
 */
s32 func_0034C410(StatusScrollState* object);

/**
 * @brief Clear the parent marker, reset resident selection flags, and request the nested display.
 * @param object Status state containing the parent and optional nested display.
 * @return Always one.
 */
s32 func_0034C480(StatusScrollState* object);

/**
 * @brief Submit the status receiver to the resident object queue.
 * @param object Receiver to submit.
 */
void func_00350200(void* object);

/**
 * @brief Release the nodes after the sentinel without destroying their payloads.
 * @param list List whose linked nodes are released.
 */
void func_00350D00(OverlayList* list);

/**
 * @brief Release the nodes after the sentinel without destroying their payloads.
 * @param list List whose linked nodes are released.
 */
void func_00350FA0(OverlayList* list);

/**
 * @brief Release the nodes after the sentinel without destroying their payloads.
 * @param list List whose linked nodes are released.
 */
void func_003511B0(OverlayList* list);

/**
 * @brief Queue the nested container for release, then release the Field window's displays.
 * @param object Status window containing the nested Lib container.
 */
void func_0034F6B0(StatusContainerWindow* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484D0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003484F0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348500(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348510(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348520(void* object);

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
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003485F0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348600(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348610(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348620(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348630(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348640(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00348650(void* object);

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
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00348690(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003486D0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003498C0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_003498D0(void* object);

/**
 * @brief Return the fixed value 1.
 * @param object Receiver or first argument; unused.
 * @return Always 1.
 */
s32 func_003507E0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003509A0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_003509B0(void* object);

/**
 * @brief Return the fixed value 4.
 * @param object Receiver or first argument; unused.
 * @return Always 4.
 */
s32 func_00350A90(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00350AE0(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00350AF0(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00350B00(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00350B10(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00350B20(void* object);

/**
 * @brief Perform no work.
 * @param object Receiver or first argument; unused.
 */
void func_00350B30(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00350B40(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00350B50(void* object);

/**
 * @brief Return the fixed value 0.
 * @param object Receiver or first argument; unused.
 * @return Always 0.
 */
s32 func_00350B60(void* object);

/**
 * @brief Set the field at offset 0xC.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348400(void* object, u8 value);

/**
 * @brief Read the field at offset 0xC.
 * @param object Object containing the field.
 * @return The field value.
 */
u8 func_00348410(void* object);

/**
 * @brief Set the field at offset 0x8.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348420(void* object, u8 value);

/**
 * @brief Read the field at offset 0x8.
 * @param object Object containing the field.
 * @return The field value.
 */
u8 func_00348430(void* object);

/**
 * @brief Set the field at offset 0xA.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348440(void* object, u16 value);

/**
 * @brief Read the field at offset 0xA.
 * @param object Object containing the field.
 * @return The field value.
 */
u16 func_00348450(void* object);

/**
 * @brief Set the field at offset 0x98.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348460(void* object, u32 value);

/**
 * @brief Read the field at offset 0x98.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_00348470(void* object);

/**
 * @brief Set the field at offset 0x9C.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00348480(void* object, u32 value);

/**
 * @brief Read the field at offset 0x9C.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_00348490(void* object);

/**
 * @brief Set the field at offset 4.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003484A0(void* object, u32 value);

/**
 * @brief Read the field at offset 4.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_003484B0(void* object);

/**
 * @brief Read the field at offset 0x10.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_003484C0(void* object);

/**
 * @brief Read the field at offset 0xD.
 * @param object Object containing the field.
 * @return The field value.
 */
u8 func_003486B0(void* object);

/**
 * @brief Set the field at offset 0xD.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003486C0(void* object, u8 value);

/**
 * @brief Read the field at offset 0x20.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_003486E0(void* object);

/**
 * @brief Set the field at offset 0x20.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_003486F0(void* object, u32 value);

/**
 * @brief Run func_00348AE0 and report status 2.
 * @param object Object passed to func_00348AE0.
 * @return Always 2.
 */
s32 func_003498E0(void* object);

/**
 * @brief Read the low bit of the byte at offset 0x38.
 * @param object Object containing the field.
 * @return The low bit.
 */
u32 func_00350A70(void* object);

/**
 * @brief Read the field at offset 0x34.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_00350A80(void* object);

/**
 * @brief Read the field at offset 0x3C.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_00350AA0(void* object);

/**
 * @brief Set the field at offset 0x24.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00350AB0(void* object, u32 value);

/**
 * @brief Set the field at offset 0x28.
 * @param object Object containing the field.
 * @param value Value to store.
 */
void func_00350AC0(void* object, u8 value);

/**
 * @brief Read the field at offset 0x28.
 * @param object Object containing the field.
 * @return The field value.
 */
s8 func_00350AD0(void* object);

/**
 * @brief Read the field at offset 0x24.
 * @param object Object containing the field.
 * @return The field value.
 */
u32 func_00350530(void* object);

/**
 * @brief Follow links from the first node in a list.
 * @param list Address of the list head pointer.
 * @param count Number of additional links to follow.
 * @return Reached node, or null when the chain ends.
 */
void* func_00351230(void* list, s32 count);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void func_00351270(OverlayList* list, void* value);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void func_00350C70(OverlayList* list, void* value);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void func_00350D80(OverlayList* list, void* value);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void func_00350F10(OverlayList* list, void* value);

/**
 * @brief Append a value to the list when node allocation succeeds.
 * @param list List to append to.
 * @param value Value stored in the new node.
 */
void func_00351120(OverlayList* list, void* value);

/**
 * @brief Clear a list, release its head, and optionally release the list.
 * @param list List to clean up.
 * @param flags Positive low halfword requests releasing the list.
 * @return Original list address.
 */
OverlayList* func_00350BF0(OverlayList* list, s32 flags);

/**
 * @brief Clear a list, release its head, and optionally release the list.
 * @param list List to clean up.
 * @param flags Positive low halfword requests releasing the list.
 * @return Original list address.
 */
OverlayList* func_00350E90(OverlayList* list, s32 flags);

/**
 * @brief Clear a list, release its head, and optionally release the list.
 * @param list List to clean up.
 * @param flags Positive low halfword requests releasing the list.
 * @return Original list address.
 */
OverlayList* func_003510A0(OverlayList* list, s32 flags);

/**
 * @brief Clean up base state and optionally release the object.
 * @param object Object to clean up.
 * @param flags Positive low halfword requests releasing the object.
 * @return Original object address.
 */
void* func_003509C0(void* object, s32 flags);

/**
 * @brief Clean up the interface at offset 0x38 and optionally release the object.
 * @param object Object to clean up.
 * @param flags Positive low halfword requests releasing the object.
 * @return Original object address.
 */
void* func_0034AC90(void* object, s32 flags);

/**
 * @brief Clean up the interface at offset 0x40 and base state, then optionally release the object.
 * @param object Object to clean up.
 * @param flags Positive low halfword requests releasing the object.
 * @return Original object address.
 */
void* func_0034ACF0(void* object, s32 flags);

/**
 * @brief Mark the current mode active and update its related state.
 * @param object Object containing the mode and related state.
 * @return 4 when activated, or 0 when already active or below state 2.
 */
s32 func_0034C000(StateC000* object);

/**
 * @brief Mark the current mode active and update its related state.
 * @param object Object containing the mode and related state.
 * @return 4 when activated, or 0 when already active or below state 2.
 */
s32 func_0034C090(StateC000* object);

/**
 * @brief Clean up three embedded lists and base state, then optionally release the object.
 * @param object Object containing the lists.
 * @param flags Positive low halfword requests releasing the object.
 * @return Original object address.
 */
void* func_0034F6F0(void* object, s32 flags);

/**
 * @brief Advance the index within its eleven-item group.
 * @param object Object containing the index at offset 0x110.
 */
void func_003495C0(StatusSelectionWindow* object);

/**
 * @brief Move the index back within its eleven-item group.
 * @param object Object containing the index at offset 0x110.
 */
void func_00349640(StatusSelectionWindow* object);

/**
 * @brief Advance the index, wrapping at the end of its eleven-item range.
 * @param object Object containing the index at offset 0x110.
 */
void func_003496C0(StatusSelectionWindow* object);

/**
 * @brief Move the index back, wrapping at the start of its eleven-item range.
 * @param object Object containing the index at offset 0x110.
 */
void func_00349730(StatusSelectionWindow* object);

/**
 * @brief Initialize the base state, embedded lists, and remaining fields.
 * @param object Object to initialize.
 * @return Initialized object.
 */
void* func_0034F780(void* object);

/**
 * @brief Initialize a status object and clear its state fields.
 * @param object Status object to initialize.
 * @return Initialized object.
 */
StatusObject* func_00350890(StatusObject* object);

#ifdef __cplusplus
}
#endif

#endif
