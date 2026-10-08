#include "include_asm.h"
#include "overlays/cskill/text.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/grid_marker.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/lib/text_003F90C0.h"

#define SKILL_FLAG_ENCODING_MASK 0x7DE3F7E3

/** Partial record containing protected flag bits and two encoded values. */
typedef struct SkillProtectedFlags
{
    u8 unk00[8];
    u32 encoded;
    s32 salt;
    u32 value_first;
    u32 salt_first;
    u32 encoded_first;
    u32 value_second;
    u32 salt_second;
    u32 encoded_second;
    u8 unk28[0x60];
    u32 checksum;
    u32 checksum_first;
    u32 checksum_second;
    u8 unk94[0x14];
    u32 key;
    u8 unkac[0x18];
} SkillProtectedFlags;

/** Four-float position with a zero-initializing default constructor. */
typedef struct SkillVector4
{
    /** @brief Initialize every position component to zero. */
    SkillVector4()
    {
        x = y = z = w = 0.0f;
    }
    /** @brief Initialize a position from its components. @param x_value Horizontal component. @param y_value Vertical component. @param z_value Depth component. @param w_value Fourth component. */
    SkillVector4(float x_value, float y_value, float z_value, float w_value)
    {
        x = x_value;
        y = y_value;
        z = z_value;
        w = w_value;
    }
    float x;
    float y;
    float z;
    float w;
} SkillVector4;



typedef struct RecordWithMethods
{
    void* methods;
} RecordWithMethods;

struct StatusDetail;

/** Partial selected-record window with text and protected-value displays. */
struct SkillProtectedDisplay : public FieldClass15AE70
{
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* selection;
    LibObject175140* text;
    u8 unkb0[4];
    LibObject174F20* display;
};

/** Partial controller list window, created by func_00364670. */
struct SkillOwnerListWindow : public FieldClass15AE70
{
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    u8 unka8[0x18];
    LibClass178600* first;
    LibClass178600* second;
};

/** Resource window owning the paired resource displays. */
struct SkillResourceWindow : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillResourceWindow()
    {
        unka8 = 0;
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillResourceWindow();
    /** @brief Leave the resource-window drawing state unchanged. */
    virtual void func_slot5c();
    /** @brief Ignore the window message key. @param key Unused signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    u32 unka8;
};

/** Message window associated with the status display. */
struct SkillStatusMessageWindow : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillStatusMessageWindow()
    {
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillStatusMessageWindow();
    /** @brief Handle a window message key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
};

/** Message window associated with the mode display. */
struct SkillModeMessageWindow : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillModeMessageWindow()
    {
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillModeMessageWindow();
    /** @brief Handle a window message key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
};

/** Partial receiver with primary and Field callback interfaces. */
struct SkillQueueOwner : public RecordWithMethods, public FieldClass153E30
{
    u8 kind;
    u8 unk39[3];
    u32 associated;
    u8 active;
    u8 unk41[3];
    FieldRecordSelection* mode_records;
    u16 selected;
    u8 unk4a[2];
    FieldClass15AE70* window;
    StatusOwner003580D0* status;
    SkillStatusMessageWindow* status_message;
    SkillFourRowSelection* four_rows;
    Record003538F0* status_rows;
    Record00352B30* mode_query;
    SkillModeMessageWindow* mode_message;
    SkillModeSelection* mode_window;
    SkillDualSelection* paired;
    SkillTextReceiver* text_window;
    SkillOwnerListWindow* list_window;
    SkillProtectedDisplay* primary;
    Record003619C0* primary_rows;
    SkillOptionsWindow* options;
    u8 unk84[8];
    FieldRecord* entry;
    StatusDetail* detail;
    u8 code;
    u8 unk95[3];
    s32 message;
    u8 row_mode;
    u8 unk9d[3];
    SkillSecondarySelection* secondary;
    u8 unka4[4];
    u16 state;
};

struct SkillDualSelection : public FieldClass15AE70
{
    /** @brief Initialize both grids, the paired display list and empty selection state. */
    SkillDualSelection();
    /** @brief Release the paired display list and destroy the window base. */
    virtual ~SkillDualSelection();
    /** @brief Move the active grid in direction zero. */
    virtual void func_slot68();
    /** @brief Move the active grid in direction one. */
    virtual void func_slot6c();
    /** @brief Cancel the active grid. */
    virtual void func_slot70();
    /** @brief Process the active grid selection. @return Selection event code. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated window. @return Two after restoring the window, or three when absent. */
    virtual s32 func_slotb4();
    /** @brief Leave the grid selection unchanged. @return Zero. */
    virtual s32 func_slotd8();
    /** @brief Leave the grid selection unchanged. @return Zero. */
    virtual s32 func_slotdc();
    /** @brief Initialize both grids. @param associated Full resource source word. @return One on success; zero on allocation failure. */
    virtual s32 func_slotf4(u32 associated);
    FieldObject23CEA0* first;
    FieldObject23CEA0* second;
    FieldObject23BE00* first_display;
    FieldObject23BE00* second_display;
    s16 mode;
    u8 unkba[2];
    FieldRecordSelection* records;
    float first_spacing;
    float second_spacing;
    SkillList183C38 list;
    u8 values[7];
    u8 enabled[2];
    u8 unkdd[3];
    LibClass172600* first_marker;
    LibClass172600* second_marker;
    float first_x;
    float first_y;
    float second_x;
    float second_y;
    u8 count;
    u8 unkf9[3];
    SkillQueueOwner* owner;
};

/** Mode window with its selection, positions, display lists, and row values. */
struct SkillModeSelection : public FieldClass15AE70
{
    /** @brief Initialize the mode rows, owned list, and controller link. @param owner Window controller. */
    SkillModeSelection(SkillQueueOwner* owner);
    /** @brief Destroy the mode list and base display lists. */
    virtual ~SkillModeSelection();
    /** @brief Update the active mode window and its list indicator. */
    virtual void func_slot5c();
    /** @brief Ignore the supplied message key. @param key Unused signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Move the mode selection in direction zero. */
    virtual void func_slot68();
    /** @brief Move the mode selection in direction one. */
    virtual void func_slot6c();
    /** @brief Process the selected mode entry. @return Mode selection event code. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated mode window. @return Mode selection event code. */
    virtual s32 func_slotb4();
    /** @brief Move to the preceding page of mode entries. @return Zero after processing. */
    virtual s32 func_slotd0();
    /** @brief Move to the following page of mode entries. @return Zero after processing. */
    virtual s32 func_slotd4();
    /** @brief Leave the mode window unchanged. @return Zero. */
    virtual s32 func_slotd8();
    /** @brief Leave the mode window unchanged. @return Zero. */
    virtual s32 func_slotdc();
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    u8 state;
    u8 animation_mode;
    u8 unkaa[2];
    float step;
    float remaining;
    FieldObject23CEA0* selection;
    SkillVector4 first_position;
    SkillVector4 second_position;
    FieldObject23B950* recipient;
    FieldRecordSelection* mode_records;
    u32 unke0;
    s16 mode;
    u8 unke6[2];
    s32 values[42];
    u8 unk190[42];
    u8 unk1ba[42];
    u8 colors[42];
    u8 unk20e[2];
    SkillList183C48 second;
    float spacing;
    float offset;
    float row_height;
    LibClass1725D0* marker;
    float track_size;
    u32 unk230[42];
    s32 item_count;
    s32 count;
    LibObject178750* display;
    u8 flag;
    u8 unk2e5[3];
    SkillQueueOwner* owner;
};
/** Partial window with a grid-choice callback after its Field virtual interface. */
struct SkillGridChoice : public FieldClass15AE70
{
    /** @brief Initialize an empty grid choice with no selected entry. */
    SkillGridChoice();
    /** @brief Release the window base and optionally its storage. */
    virtual ~SkillGridChoice();
    /**
     * @brief Create the choice panel, text widgets, and two-entry grid.
     * @param associated Full resource source word.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @param code Base display code.
     * @return One after setup, or zero when an allocation fails.
     */
    virtual s32 func_slot10(u32 associated, float x, float y, s32 code);
    /** @brief Refresh the current grid choice. */
    virtual void func_slot5c();
    /** @brief Leave the current choice message unchanged. @param text_key Unused message key. */
    virtual void func_slot60(s32 text_key);
    /** @brief Move the choice grid in direction zero. */
    virtual void func_slot68();
    /** @brief Move the choice grid in direction one. */
    virtual void func_slot6c();
    /** @brief Process the current choice. @return Choice event code. */
    virtual s32 func_slotb0();
    /** @brief Cancel the choice window. @return Two after queuing cancellation. */
    virtual s32 func_slotb4();
    /** @brief Handle the current grid choice. @param selected Selected grid index. */
    virtual void func_slotf4(s16 selected);
    FieldObject23CEA0* selection;
    s16 selected;
};

struct SkillSecondarySelection : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillSecondarySelection()
    {
        owner = 0;
        selection = 0;
        previous = 0;
        code = 0;
        state = 0;
        status = 0;
        four_rows = 0;
        status_rows = 0;
        mode_query = 0;
        cursor = 0;
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillSecondarySelection();
    /** @brief Refresh the visible window state. */
    virtual void func_slot5c();
    /** @brief Handle a window message key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Refresh the associated owner and reset the selection state. */
    virtual void func_slot64();
    /** @brief Move the selection in direction zero. */
    virtual void func_slot68();
    /** @brief Move the selection in direction one. */
    virtual void func_slot6c();
    /** @brief Process the selected window. @return Selection event code. */
    virtual s32 func_slotb0();
    /** @brief Open the grid choice. @return Selection event code. */
    virtual s32 func_slotb4();
    /** @brief Cycle the status record in direction zero. @return Selection event code. */
    virtual s32 func_slotd8();
    /** @brief Cycle the status record in direction one. @return Selection event code. */
    virtual s32 func_slotdc();
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    SkillQueueOwner* owner;
    FieldObject23CEA0* selection;
    s16 code;
    s16 previous;
    s16 direction;
    u8 state;
    u8 unkb7;
    StatusOwner003580D0* status;
    FieldObject23BE00* cursor;
    SkillFourRowSelection* four_rows;
    Record003538F0* status_rows;
    Record00352B30* mode_query;
};

/** Partial four-row window with its record selection, grid, and cursor display. */
struct SkillFourRowSelection : public FieldClass15AE70
{
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* records;
    FieldObject23CEA0* selection;
    FieldClass15AE70* message;
    StatusOwner003580D0* status;
    u8 unkb8[8];
    LibObject178750* first_display;
    LibObject178750* second_display;
    LibClass172870* third_display;
    FieldObject23BE00* cursor;
    LibObject174F20* first_rows[4];
    LibObject174F20* second_rows[4];
    LibObject178750* third_rows[4];
    u8 flag;
};

/** Runtime callback state containing the active controller interface. */
struct SkillRuntimeCallbacks
{
    u8 unk00[0x14];
    FieldClass153E30* controller;
};

/** Partial resident runtime view. */
struct SkillRuntime
{
    u8 unk00[0xC];
    FieldSlotRecordOwner1C* loader;
    SkillRuntimeCallbacks* callbacks;
    u8 unk14[0xC];
    FieldBufferSlots* resources;
};
extern "C" SkillRuntime* D_001B643C;

/** @brief Refresh the owner message window when its kind requires it. @param owner Controller owner. */
static inline void refresh_owner_message(SkillQueueOwner* owner)
{
    if (owner->kind == 2)
    {
        FieldClass15AE70* window = owner->window;
        if (window != 0)
        {
            func_00348720(window);
        }
    }
}

/** @brief Convert an entry resource key to its message index. @param key Entry resource key. @return Message index, or zero for the special entry. */
static inline s32 message_from_key(s32 key)
{
    s32 message;
    s32 index = key - 0x178A;
    if (index == 0)
    {
        message = 0;
    }
    else
    {
        message = key - 0x18FF;
    }
    return message;
}

/** @brief Update the optional controller owner's row message. @param owner Optional controller owner. @param row Selected row. @param key Selected entry resource key. */
static inline void set_row_message(SkillQueueOwner* owner, s16 row, s32 key)
{
    if (owner != 0)
    {
        if (row == 2 || row == 3)
        {
            owner->row_mode = 1;
        }
        else
        {
            owner->row_mode = 0;
        }
        s32 message = key - 0x18FF;
        if (message < 0)
        {
            message = 0;
        }
        owner->message = message;
        refresh_owner_message(owner);
    }
}

/**
 * @brief Show the selected grid entry's message through the controller's owning window.
 * @param controller Active Field controller interface.
 * @param selection Grid containing the current entry index.
 * @param first_key Resource key for entry zero.
 */
static inline void show_grid_message(FieldClass153E30* controller, FieldObject23CEA0* selection, s32 first_key)
{
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(controller);
    owner->window->func_slot60(selection->unk114 + first_key);
}

/**
 * @brief Dispatch a movement direction when the grid is active.
 * @param selection Grid receiver.
 * @param direction Signed direction code.
 */
static inline void move_active_grid(FieldObject23CEA0* selection, s16 direction)
{
    u8 inactive = !selection->unk35;
    if (inactive != 1)
    {
        selection->func_0023CDB0(direction);
    }
}


/** @brief Set display flags for the selected window lists. @param object Window base. @param flag Flag value. @param lists List-selection bit mask. */
extern "C" void func_002CE530(FieldClass15AE70* object, u32 flag, u32 lists);
/** @brief Queue a nonnull window in the runtime callback list. @param runtime Runtime callback state. @param object Window to queue. */
extern "C" void func_002CFE10(SkillRuntimeCallbacks* runtime, FieldClass15AE70* object);


typedef struct State003620F0
{
    u8 unk00[0xE5];
    u8 flag;
} State003620F0;

typedef struct Mode003620F0
{
    u8 unk00[0x10];
    s8 mode;
} Mode003620F0;

typedef struct Record003620F0
{
    u8 unk00[0xA8];
    Record00363740* primary;
    Mode003620F0* mode;
    State003620F0* state;
} Record003620F0;

typedef struct Record003611B0
{
    u8 unk00[0x104];
    u8 unk104;
} Record003611B0;

/** Linked node containing a pair of float values. */
typedef struct SkillPairListNode
{
    float first;
    float second;
    struct SkillPairListNode* next;

    /** @brief Initialize both stored values to zero. */
    SkillPairListNode()
    {
        second = 0.0f;
        first = 0.0f;
    }

    /** @brief Destroy a paired-value node. */
    ~SkillPairListNode()
    {
    }
} SkillPairListNode;

typedef struct StatusItem : public LibClass178600
{
    u8 unk40[0xBC];
    s32 unkfc;
} StatusItem;

typedef struct StatusOwner003580D0 : public FieldClass15AE70
{
    /** @brief Initialize the status display and controller link. @param owner Window controller. */
    StatusOwner003580D0(SkillQueueOwner* owner);
    /** @brief Destroy the status window and its base display lists. */
    virtual ~StatusOwner003580D0();
    /** @brief Refresh the active status message. */
    virtual void func_slot5c();
    /** @brief Ignore the supplied message key. @param key Unused signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* selection;
    LibObject175140* portrait;
    LibObject178750* first_label;
    LibObject178750* second_label;
    LibObject178750* third_label;
    LibObject178750* fourth_label;
    LibObject178750* fifth_label;
    LibObject174F20* first_value;
    LibObject178750* sixth_label;
    LibObject174F20* second_value;
    LibObject174F20* third_value;
    LibObject174F20* items[3];
    LibObject178750* fallback_label;
    u32 unke4[3];
    u8 unkf0[4];
    u8 changed;
    u8 unkf5[3];
    SkillFourRowSelection* four_rows;
    Record003538F0* status_rows;
    Record00352B30* mode_query;
    SkillModeSelection* mode_window;
    SkillDualSelection* paired;
    LibClass178600* first_display;
    LibClass178600* second_display;
    LibClass178600* icons[8];
    u8 codes[8];
    u8 active;
    u8 unk13d[3];
    SkillQueueOwner* owner;
} StatusOwner003580D0;

/** @brief Advance or retreat the record selection and refresh its linked windows. @param status Status window. @param forward Nonzero to advance. @return Byte event code zero or four. */
static inline s32 cycle_status_record(StatusOwner003580D0* status, s32 forward)
{
    if (status->changed == 1)
    {
        return 0;
    }
    status->selection->active = 0;
    status->changed = 1;
    func_0028E2B0(status->selection, forward);
    if (status->active != 0)
    {
        func_00358310(status);
    }
    if (status->four_rows != 0)
    {
        func_003559F0(status->four_rows);
    }
    if (status->status_rows != 0)
    {
        func_00354190(status->status_rows);
    }
    if (status->mode_query != 0)
    {
        func_00352C00(status->mode_query);
    }
    if (status->mode_window != 0)
    {
        func_00350890(status->mode_window, status->mode_window->mode);
    }
    if (status->paired != 0)
    {
        func_0034B3F0(status->paired);
    }
    return (u8)(status->selection->count == 1 ? 0 : 4);
}


/** Display storage whose value is a selected detail pointer. */
typedef struct StatusPointerItem
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[0xBF];
    void* unkfc;
} StatusPointerItem;

/** Fixed-stride detail records containing two encoded signed status values. */
typedef struct StatusDetail
{
    u8 unk00[0x18];
    s16 first;
    s16 second;
    u8 unk1c[4];
    char text[0xD4];
    u32 checksum;
    u8 unkf8[0x14];
    u32 key;
    u8 unk110[4];
} StatusDetail;

typedef struct Record003581B0Inner
{
    void* entries;
    StatusDetail* details;
    s8 codes[8];
    u8 unk10;
    s8 index;
    u8 flag;
} Record003581B0Inner;

typedef struct Record003581B0
{
    u8 unk00[0xA8];
    Record003581B0Inner* inner;
    StatusPointerItem* pointer_item;
    u8 unkb0[0x1C];
    StatusItem* second_item;
    StatusItem* first_item;
    u8 unkd4[0x20];
    u8 flag;
} Record003581B0;

typedef struct PacketBuffer0035DDE0
{
    u8* base;
    u32 unk04;
    u8* cursor;
    u8* unk0c;
    u32 capacity;
    u8 unk14;
    u8 unk15;
} PacketBuffer0035DDE0;

/** Coordinate selector with an owned pair list after its movement state. */
struct SkillCoordinateSelector : public LibClass175030
{
    SkillPairList184258 nodes;
    s32 selected;
};

/** Options window with a selector and its owned display list. */
struct SkillOptionsWindow : public FieldClass15AE70
{
    /** @brief Initialize an empty options window and its display list. */
    SkillOptionsWindow();
    /** @brief Release the display list and window base. */
    virtual ~SkillOptionsWindow();
    /** @brief Release the listed displays and window attachments. */
    virtual void func_slot0c();
    /** @brief Refresh option display values. */
    virtual void func_slot5c();
    /** @brief Handle an unused message key. @param key Message key. */
    virtual void func_slot60(s32 key);
    /** @brief Move the selector to the preceding row. */
    virtual void func_slot68();
    /** @brief Move the selector to the following row. */
    virtual void func_slot6c();
    /** @brief Move the selector to the preceding entry. */
    virtual void func_slot70();
    /** @brief Move the selector to the following entry. */
    virtual void func_slot74();
    /** @brief Apply the selected options. @return Action status. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated window. @return Two after cancellation. */
    virtual s32 func_slotb4();
    /** @brief Create the option displays. @param associated Full resource source word. @return Setup status. */
    virtual s32 func_slotf4(u32 associated);
    FieldRecordSelection* records;
    SkillCoordinateSelector* child;
    float x;
    float y;
    void* unkb8;
    SkillList184268 nested;
    LibObject174F20* first_values[8];
    LibObject174F20* second_values[8];
    LibObject174F20* first_previews[8];
    LibObject174F20* second_previews[8];
    LibObject175140* labels[8];
    ItemCreationOptionResourceDisplay* indicators[8];
    ItemCreationOptionResourceDisplay* badges[8][4];
    s32 selected_kind;
    s32 selected_index;
};


typedef struct Record0035DDE0
{
    u8 unk00[8];
    PacketBuffer0035DDE0* buffer;
} Record0035DDE0;

typedef struct Record0035DE40
{
    u8 unk00[0x2C];
    void* methods;
} Record0035DE40;

/** Grid selection state used by the mode query. */
typedef FieldObject23CEA0 QuerySelection;

/** Partial mode-query receiver with a six-element signed mode table. */
typedef struct Record00352B30 : public FieldClass15AE70
{
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    QuerySelection* selection;
    s16 unkac[5];
    u8 unkb6[0xE];
    FieldRecordSelection* records;
    FieldClass15AE70* attachment;
    FieldObject23BE00* cursor;
    u8 active;
    u8 unkd1[3];
    s32 values[12];
    s32 unk104;
    s16 modes[6];
    SkillQueueOwner* parent;
} Record00352B30;

typedef struct Record0035D4A0
{
    void* methods;
    u8 unk04[0x8C];
    void* secondary_methods;
    u8 unk94[0x2C];
    Record0035DE40 nested;
} Record0035D4A0;

typedef struct ListItem0035CCE0
{
    u8 unk00[0x18];
    SkillVector4 position;
    u8 unk28[0x14];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x54];
    u32 unk94;
} ListItem0035CCE0;

/** Partial receiver holding two arrays of 30 paired display items. */
typedef struct Record003619C0 : public FieldClass15AE70
{
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    u8 unka8[4];
    FieldRecordSelection* records;
    FieldObject23CEA0* selection;
    u8 unkb4[4];
    ListItem0035CCE0* first[30];
    ListItem0035CCE0* second[30];
    u8 unk1a8[4];
    s32 selected;
    s32 position;
    s32 shift;
} Record003619C0;

typedef struct ListNode0035CCE0
{
    ListItem0035CCE0* value;
    struct ListNode0035CCE0* next;
} ListNode0035CCE0;

/** Partial status attachment exposing its activity byte. */
struct SkillStatusAttachment
{
    u8 unk00[0xCB];
    u8 active;
};

/** Partial six-row Field window with native display lists and value tables. */
typedef struct Record003538F0 : public FieldClass15AE70
{
    /** @brief Initialize both display lists, the value tables and controller link. @param owner Window controller. */
    Record003538F0(SkillQueueOwner* owner);
    /** @brief Release both owned display lists and the window base. */
    virtual ~Record003538F0();
    /** @brief Refresh the active row message. */
    virtual void func_slot5c();
    /** @brief Ignore the supplied message key. @param key Unused signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Refresh the row positions and selected cursor. */
    virtual void func_slot64();
    /** @brief Move the row selection in direction zero. */
    virtual void func_slot68();
    /** @brief Move the row selection in direction one. */
    virtual void func_slot6c();
    /** @brief Process the selected row. @return Selection event code. */
    virtual s32 func_slotb0();
    /** @brief Restore the associated window. @return Two after restoring the window. */
    virtual s32 func_slotb4();
    /** @brief Cycle the status record in direction zero. @return Record-change event code. */
    virtual s32 func_slotd8();
    /** @brief Cycle the status record in direction one. @return Record-change event code. */
    virtual s32 func_slotdc();
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    SkillStatusAttachment* attachment;
    FieldObject23CEA0* selection;
    FieldObject23BAB0* display;
    float row_x;
    float row_y;
    float row_spacing;
    float x;
    float y;
    float spacing;
    u8 unkcc[8];
    FieldRecordSelection* mode_records;
    SkillList183C38 second;
    SkillList183C38 third;
    s32 keys[6];
    StatusItem* unk108[7];
    float unk124;
    s32 unk128[6];
    s32 first_values[6];
    s32 second_values[6];
    s32 third_values[6];
    u8 flag;
    u8 active;
    u8 unk18a[2];
    SkillQueueOwner* owner;
} Record003538F0;

/** Partial display receiver with counter and horizontal position controls. */
typedef struct Record0035A560 : public FieldClass15AE70
{
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* display;
    s32 limit;
    u8 unkb0[2];
    s16 counter;
    u8 active;
    u8 unkb5[0xF];
    float extent;
    float first_x;
    float origin;
    float offset;
    s32 mode;
} Record0035A560;









typedef struct Record00355420
{
    void* methods;
    u8 unk04[0x3C];
    u8 unk40;
} Record00355420;

typedef struct Record00355490
{
    RecordWithMethods base;
    u8 unk04[0xC];
    void* methods;
} Record00355490;

typedef struct Record003610F0
{
    u8 unk00[0x38];
    void* methods;
} Record003610F0;

typedef struct Record00361060
{
    void* methods;
    u8 unk04[0x3C];
    Record003610F0 nested;
} Record00361060;

typedef struct Record00364720
{
    Record00361060 base;
    SkillPairList184258 list;
} Record00364720;

typedef struct Record0035D3E0
{
    u8 unk00[0x20];
    u32 unk20;
    u32 unk24;
    u32 unk28;
    float unk2c;
    u8 unk30[0x3C];
    u16 unk6c;
    u8 unk6e[0x46];
    u32 unkb4;
    u32 unkb8;
} Record0035D3E0;

extern "C" FieldRecordSelection* func_0028E4D0(FieldRecordSelection* selection);
extern "C" u64 D_4ED330[];
extern "C" void func_11F140(PacketBuffer0035DDE0* buffer, u64 value);
extern "C" u8 D_50CD30[];
extern "C" u8 D_183C60[];
extern "C" u8 D_183E60[];
extern "C" u8 D_183570[];
extern "C" u8 D_183970[];
extern "C" u8 D_184160[];
extern "C" u8 D_183F60[];
extern "C" u8 D_184060[];
extern "C" u8 D_182E40[];
extern "C" u8 D_182F70[];
extern "C" u8 D_182F50[];
extern "C" u8 D_182F60[];
extern "C" u8 D_178A70[];
extern "C" u8 D_183370[];
extern "C" u8 D_183670[];
extern "C" u8 D_183770[];
extern "C" u8 D_183870[];
extern "C" u8 D_183A70[];
extern "C" u8 D_183E50[];
extern "C" u8 D_183DB0[];
extern "C" u8 D_183E24[];
extern "C" u8 D_183E3C[];
extern "C" void func_2CEAF0(void* object, s32 flag);
extern "C" void* func_2BC410(void* object, s16 flag);
extern "C" void* func_002BC280(void* object, s16 flag);
extern "C" void func_44B210(void* record);
extern "C" u8 D_183C48[];
extern "C" u8 D_183C38[];
extern "C" u8 D_184258[];
extern "C" u8 D_184268[];
extern "C" u8 D_183D60[];
extern "C" u8 D_183D84[];
extern "C" u8 D_175030[];
extern "C" u8 D_175054[];
extern "C" void* func_4618F0(void* record, s16 flag);
extern "C" void* func_4C48B0(void* record, s16 flag);
extern "C" u8 D_183170[];
extern "C" u8 D_183270[];
extern "C" u8 D_159FE0[];
extern "C" u8 D_183470[];
extern "C" u8 D_183DA0[];
extern "C" void func_44B110(void* object, s32 arg1, s32 arg2, void* arg3, float value, s32 flag);
extern "C" void func_2CEBE0(void* object);
extern "C" void func_003648E0(void* object);
extern "C" void func_0035C8D0(void* object);
extern "C" void func_4CE4C0(void* destination, const void* source);
extern "C" void func_4D00B0(void* object);

extern "C" void func_420D20(FieldObject23B850* object, u32 color);
extern "C" void func_4C6190(void* owner, void* object);

extern "C" void func_0034BD30(Record0034C1F0* record, s32 index);
extern "C" void* func_4C69B0(void* item);
extern "C" s32 func_4C6A40(void* item);

/**
 * @brief Read the key shared by the record's protected checksums.
 * @param record Protected record.
 * @return Record key.
 */
static inline u32 protected_key(SkillProtectedFlags* record)
{
    return record->key;
}

static inline RecordWithMethods* release_record182f50(RecordWithMethods* record, s16 flag);
static inline RecordWithMethods* release_record182f60(RecordWithMethods* record, s16 flag);
static inline Record003610F0* release_record183da0(Record003610F0* record, s16 flag);
static inline Record0035DE40* release_record183e50(Record0035DE40* record, s16 flag);
static inline Record00361060* release_record175030(Record00361060* record, s16 flag);

/**
 * @brief Reset the base record's method table and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
static inline RecordWithMethods* release_record182f50(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_182F50;
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

/**
 * @brief Release the derived record's base state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
static inline RecordWithMethods* release_record182f60(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_182F60;
        release_record182f50(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

/**
 * @brief Release the nested record state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
static inline Record003610F0* release_record183da0(Record003610F0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183DA0;
        func_4618F0(record, -1);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

/**
 * @brief Release the nested record state and optionally free its storage.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
static inline Record0035DE40* release_record183e50(Record0035DE40* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183E50;
        func_2BC410(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

/**
 * @brief Release the embedded record and base state, then optionally free the owner.
 * @param record Record to release, or null.
 * @param flag Positive values release the record's storage.
 * @return Original record pointer.
 */
static inline Record00361060* release_record175030(Record00361060* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_175030;
        record->nested.methods = D_175054;
        release_record183da0(&record->nested, -1);
        func_4C48B0(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

/**
 * @brief Write the 8-bit field at offset 0xC.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348400(FieldClass15AE70* object, u8 value)
{
    object->unk0c = value;
}

/**
 * @brief Read the 8-bit field at offset 0xC.
 * @param object Receiver storage.
 * @return Field value.
 */
u8 func_00348410(FieldClass15AE70* object)
{
    return object->unk0c;
}

/**
 * @brief Write the 8-bit field at offset 0x8.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348420(FieldClass15AE70* object, u8 value)
{
    object->unk08 = value;
}

/**
 * @brief Read the 8-bit field at offset 0x8.
 * @param object Receiver storage.
 * @return Field value.
 */
u8 func_00348430(FieldClass15AE70* object)
{
    return object->unk08;
}

/**
 * @brief Write the 16-bit field at offset 0xA.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348440(FieldClass15AE70* object, u16 value)
{
    object->unk0a = value;
}

/**
 * @brief Read the 16-bit field at offset 0xA.
 * @param object Receiver storage.
 * @return Field value.
 */
u16 func_00348450(FieldClass15AE70* object)
{
    return object->unk0a;
}

/**
 * @brief Store the alternate associated pointer.
 * @param object Window receiver.
 * @param value Pointer to store.
 */
void func_00348480(FieldClass15AE70* object, void* value)
{
    object->unk9c = value;
}

/**
 * @brief Return the alternate associated pointer.
 * @param object Window receiver.
 * @return Stored pointer.
 */
void* func_00348490(FieldClass15AE70* object)
{
    return object->unk9c;
}

/**
 * @brief Write the 32-bit field at offset 0x4.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_003484A0(FieldClass15AE70* object, u32 value)
{
    object->unk04 = value;
}

/**
 * @brief Read the 32-bit field at offset 0x4.
 * @param object Receiver storage.
 * @return Field value.
 */
u32 func_003484B0(FieldClass15AE70* object)
{
    return object->unk04;
}

/**
 * @brief Return the nested display container.
 * @param object Window receiver.
 * @return Stored container pointer.
 */
LibObject178660* func_003484C0(FieldClass15AE70* object)
{
    return object->unk10;
}

void func_003484D0(void* object)
{
}

void func_003484E0(void* object)
{
}

void func_003484F0(void* object)
{
}

void func_00348500(void* object)
{
}

void func_00348510(void* object)
{
}

void func_00348520(void* object)
{
}

void func_00348530(void* object)
{
}

void func_00348540(void* object)
{
}

void func_00348550(void* object)
{
}

void func_00348560(void* object)
{
}

void func_00348570(void* object)
{
}

void func_00348580(void* object)
{
}

void func_00348590(void* object)
{
}

void func_003485A0(void* object)
{
}

void func_003485B0(void* object)
{
}

void func_003485C0(void* object)
{
}

void func_003485D0(void* object)
{
}

void func_003485E0(void* object)
{
}

void func_003485F0(void* object)
{
}

void func_00348600(void* object)
{
}

s32 func_00348610(void* object)
{
    return 0;
}

s32 func_00348620(void* object)
{
    return 0;
}

s32 func_00348630(void* object)
{
    return 0;
}

s32 func_00348640(void* object)
{
    return 0;
}

s32 func_00348650(void* object)
{
    return 0;
}

s32 func_00348660(void* object)
{
    return 0;
}

s32 func_00348670(void* object)
{
    return 0;
}

s32 func_00348680(void* object)
{
    return 0;
}

s32 func_00348690(void* object)
{
    return 0;
}

s32 func_003486A0(void* object)
{
    return 0;
}

s32 func_003486B0(void* object)
{
    return 0;
}

s32 func_003486C0(void* object)
{
    return 0;
}

void func_003486D0(void* object)
{
}

void func_003486E0(void* object)
{
}

/**
 * @brief Read the 8-bit field at offset 0xD.
 * @param object Receiver storage.
 * @return Field value.
 */
u8 func_003486F0(FieldClass15AE70* object)
{
    return object->unk0d;
}

/**
 * @brief Write the 8-bit field at offset 0xD.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_00348700(FieldClass15AE70* object, u8 value)
{
    object->unk0d = value;
}

void func_00348710(void* object)
{
}

/** Comparison window with its labels, numeric images, and controller. */
struct SkillComparisonDisplay : FieldClass15AE70
{
    /** @brief Initialize the comparison displays and controller link. @param owner Window controller. */
    SkillComparisonDisplay(SkillQueueOwner* owner);
    /** @brief Destroy the comparison window and its base display lists. */
    virtual ~SkillComparisonDisplay();
    /** @brief Set the comparison title key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the window displays. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* title;
    u32 unkac;
    LibObject178750* item_label;
    LibObject178750* rate_label;
    LibObject178750* separator;
    LibObject174F20* hundreds;
    LibObject174F20* tens;
    LibObject174F20* ones;
    LibObject178750* first_label;
    LibObject174F20* first_value;
    LibObject178750* second_label;
    LibObject174F20* second_value;
    LibObject178750* third_label;
    LibObject174F20* third_value;
    SkillQueueOwner* owner;
};
/**
 * @brief Calculate the eight comparison values for a selected entry.
 * @param code Selected entry code.
 * @param entry Protected entry record.
 * @param detail Protected detail record.
 * @param first First output value.
 * @param second Second output value.
 * @param third Third output value.
 * @param fourth Fourth output value.
 * @param fifth Fifth output value.
 * @param sixth Sixth output value.
 * @param seventh Seventh output value.
 * @param eighth Eighth output value.
 * @return Nonzero when the comparison values are available.
 */
extern "C" u8 func_4095C0(s32 code, FieldRecord* entry, StatusDetail* detail, s32* first, s32* second, s32* third, s32* fourth, s32* fifth, s32* sixth,
                          s32* seventh, s32* eighth);
/**
 * @brief Set the comparison label group visibility.
 * @param object Comparison window.
 * @param visible Display visibility byte.
 */
static inline void comparison_labels(SkillComparisonDisplay* object, u8 visible)
{
    object->item_label->unk3f = visible;
    object->rate_label->unk3f = visible;
    object->first_label->unk3f = visible;
    object->second_label->unk3f = visible;
    object->third_label->unk3f = visible;
}
/**
 * @brief Set the comparison value group visibility.
 * @param object Comparison window.
 * @param visible Display visibility byte.
 */
static inline void comparison_values(SkillComparisonDisplay* object, u8 visible)
{
    object->item_label->unk3f = visible;
    object->hundreds->unk3f = visible;
    object->separator->unk3f = visible;
    object->tens->unk3f = visible;
    object->ones->unk3f = visible;
    object->first_value->unk3f = visible;
    object->second_value->unk3f = visible;
    object->third_value->unk3f = visible;
}
/**
 * @brief Set the comparison value group color.
 * @param object Comparison window.
 * @param color Packed display color.
 */
static inline void comparison_colors(SkillComparisonDisplay* object, u32 color)
{
    object->item_label->set_color(color);
    object->hundreds->set_color(color);
    object->separator->set_color(color);
    object->tens->set_color(color);
    object->ones->set_color(color);
    object->first_value->set_color(color);
    object->second_value->set_color(color);
    object->third_value->set_color(color);
}
/**
 * @brief Hide the comparison rate and its label.
 * @param object Comparison window.
 */
static inline void clear_comparison_rate(SkillComparisonDisplay* object)
{
    object->rate_label->unk3f = 0;
    object->item_label->unk3f = 0;
    object->hundreds->unk3f = 0;
    object->separator->unk3f = 0;
    object->tens->unk3f = 0;
    object->ones->unk3f = 0;
}
/**
 * @brief Update a numeric image and mark it changed.
 * @param image Numeric image.
 * @param value Image value.
 */
static inline void comparison_value(LibObject174F20* image, s32 value)
{
    image->numeric_value = value;
    image->unk3c = 1;
}
void func_00348720(FieldClass15AE70* receiver)
{
    SkillComparisonDisplay* object = static_cast<SkillComparisonDisplay*>(receiver);
    if (object->owner == 0)
    {
        return;
    }
    s32 result_first = -1, result_second = -1, result_third = -1, result_fourth = -1, result_fifth = -1, result_sixth = -1, result_seventh = -1,
        result_eighth = -1;
    s32 code = object->owner->message;
    FieldRecord* entry = object->owner->entry;
    StatusDetail* detail = object->owner->detail;
    s32 mode = object->owner->row_mode;
    if (code == 0)
    {
        comparison_labels(object, 0);
        comparison_values(object, 0);
        return;
    }
    comparison_labels(object, 1);
    if (func_4095C0(code, entry, detail, &result_first, &result_second, &result_third, &result_fourth, &result_fifth, &result_sixth, &result_seventh,
                    &result_eighth) != 0)
    {
        result_fifth++;
        float scaled = (float)result_fifth / 1024.0f;
        scaled *= 100.0f;
        s32 percent = (s32)scaled;
        s32 hundreds = percent / 100;
        s32 tens = (percent % 100) / 10;
        s32 ones = percent % 10;
        s32 value;
        if (mode != 0)
        {
            if (result_seventh == 0)
            {
                func_4C6DF0(object->third_label, object->func_slot54(), 0x17C3, 0);
                value = result_eighth;
            }
            else
            {
                func_4C6DF0(object->third_label, object->func_slot54(), 0x17C4, 0);
                value = result_seventh;
            }
            comparison_value(object->hundreds, hundreds);
            comparison_value(object->tens, tens);
            comparison_value(object->ones, ones);
            comparison_value(object->first_value, result_third);
            comparison_value(object->second_value, result_sixth);
            comparison_value(object->third_value, value);
            comparison_colors(object, 0x508050);
        }
        else
        {
            if (result_first == 0)
            {
                func_4C6DF0(object->third_label, object->func_slot54(), 0x17C3, 0);
                value = result_second;
            }
            else
            {
                func_4C6DF0(object->third_label, object->func_slot54(), 0x17C4, 0);
                value = result_first;
            }
            comparison_value(object->hundreds, 1);
            comparison_value(object->tens, 0);
            comparison_value(object->ones, 0);
            comparison_value(object->first_value, result_third);
            comparison_value(object->second_value, result_fourth);
            comparison_value(object->third_value, value);
            comparison_colors(object, 0x288080);
        }
        comparison_values(object, 1);
    }
    else
    {
        comparison_values(object, 0);
    }
    if (code == 97 || code == 98 || code == 100 || code == 99)
    {
        clear_comparison_rate(object);
    }
    if (code >= 131 && code < 155)
    {
        clear_comparison_rate(object);
        object->second_label->unk3f = 0;
        object->second_value->unk3f = 0;
        object->third_label->unk3f = 0;
        object->third_value->unk3f = 0;
    }
}

/** Window containing paired text choices, icons, and values. */
struct SkillTextReceiver : FieldClass15AE70
{
    /** @brief Initialize the window and clear its initial state. */
    SkillTextReceiver()
    {
        display = 0;
        first_choice = 0;
        second_choice = 0;
        first_icon = 0;
        first_value = 0;
        second_icon = 0;
        second_value = 0;
    }
    /** @brief Destroy the window base and its display lists. */
    virtual ~SkillTextReceiver();
    /** @brief Handle a window message key. @param key Signed message key. */
    virtual void func_slot60(s32 key);
    /** @brief Initialize the display widgets. @param associated Full resource source word. @return Initialization result. */
    virtual s32 func_slotf4(u32 associated);
    LibObject178750* display;
    LibObject178750* first_choice;
    LibObject178750* second_choice;
    ItemCreationClass174C40* first_icon;
    LibObject178750* first_value;
    ItemCreationClass174C40* second_icon;
    LibObject178750* second_value;
};

void func_00348CB0(SkillComparisonDisplay* record, u32 key)
{
    if (record->title != 0)
    {
        u32 source = record->func_slot54();
        func_4C6DF0(record->title, source, key, 0);
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00348D10);

SkillComparisonDisplay::~SkillComparisonDisplay()
{
}
SkillComparisonDisplay::SkillComparisonDisplay(SkillQueueOwner* controller)
{
    title = 0;
    unkac = 0;
    first_label = 0;
    first_value = 0;
    item_label = 0;
    rate_label = 0;
    hundreds = 0;
    separator = 0;
    tens = 0;
    ones = 0;
    second_label = 0;
    second_value = 0;
    third_label = 0;
    third_value = 0;
    owner = 0;
    owner = controller;
}

void func_00349920(u8* object, s32 mode)
{
    if (mode == 0)
    {
        (*(u8**)(object + 0xA8))[0x3F] = 0;
        (*(u8**)(object + 0xB8))[0x3F] = 0;
        (*(u8**)(object + 0xC0))[0x3F] = 0;
        (*(u8**)(object + 0xAC))[0x3F] = 0;
        (*(u8**)(object + 0xB0))[0x3F] = 0;
        (*(u8**)(object + 0xB4))[0x3F] = 0;
        (*(u8**)(object + 0xBC))[0x3F] = 0;
    }
    else if (mode > 0)
    {
        (*(u8**)(object + 0xAC))[0x3F] = 1;
        (*(u8**)(object + 0xB0))[0x3F] = 0;
    }
    else
    {
        (*(u8**)(object + 0xAC))[0x3F] = 0;
        (*(u8**)(object + 0xB0))[0x3F] = 1;
    }
}

s32 func_003499B0(SkillTextReceiver* object, u32 associated)
{
    object->FieldClass15AE70::func_slot10(associated, 320.0f, 176.0f, 15);
    object->display = new (0) LibObject178750;
    object->first_choice = new (0) LibObject178750;
    object->second_choice = new (0) LibObject178750;
    object->first_icon = new (0) ItemCreationClass174C40;
    object->first_value = new (0) LibObject178750;
    object->second_icon = new (0) ItemCreationClass174C40;
    object->second_value = new (0) LibObject178750;
    object->display->func_004C7FE0(64.0f, 38.0f, 0.0f, 0.0f, (s32)associated, 0x1797, 0);
    object->first_choice->func_004C7FE0(140.0f, 38.0f, 0.0f, 0.0f, (s32)associated, 0x1798, 0);
    object->second_choice->func_004C7FE0(140.0f, 38.0f, 0.0f, 0.0f, (s32)associated, 0x1799, 0);
    object->first_choice->unk3f = 0;
    object->second_choice->unk3f = 0;
    func_4530E0(object->first_icon, 35, 64.0f, 86.0f);
    object->first_value->func_004C7FE0(100.0f, 90.0f, 0.0f, 0.0f, (s32)associated, 0x1791, 0);
    func_4530E0(object->second_icon, 32, 64.0f, 122.0f);
    object->second_value->func_004C7FE0(100.0f, 126.0f, 0.0f, 0.0f, (s32)associated, 0x1792, 0);
    func_004C6190(object->unk10, object->display);
    func_004C6190(object->unk10, object->first_choice);
    func_004C6190(object->unk10, object->second_choice);
    func_004C6190(object->unk10, object->first_icon);
    func_004C6190(object->unk10, object->first_value);
    func_004C6190(object->unk10, object->second_icon);
    func_004C6190(object->unk10, object->second_value);
    return 1;
}

/** @brief Release the resource widget's storage and destroy its base. */
ItemCreationClass175110::~ItemCreationClass175110()
{
}

SkillTextReceiver::~SkillTextReceiver()
{
}

void func_00349E80(SkillDualSelection* object)
{
    if (object->mode == 0)
    {
        FieldObject23CEA0* selection = object->first;
        SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
        owner->window->func_slot60(object->values[selection->unk114] + 0x1AB0);
    }
    else if (object->mode == 1)
    {
        show_grid_message(D_001B643C->callbacks->controller, object->second, 0x1ABA);
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00349F30);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034A130);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034A2B0);

s32 func_0034A560(void* object)
{
    return 0;
}

s32 func_0034A570(void* object)
{
    return 0;
}

s32 func_0034A580(SkillDualSelection* object)
{
    FieldClass15AE70* window = static_cast<FieldClass15AE70*>(object->func_slot44());
    if (window == 0)
    {
        return 3;
    }
    LibClass178600* first = object->owner->status->first_display;
    if (first != 0)
    {
        first->unk3f = 1;
    }
    LibClass178600* second = object->owner->status->second_display;
    if (second != 0)
    {
        second->unk3f = 1;
    }
    func_00349F30(object, 2);
    window->func_slot64();
    D_001B643C->callbacks->controller->func_00263C70(window);
    return 2;
}

void func_0034A640(u8* object, u32 value)
{
    *(u32*)(object + 0x20) = value;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034A650);

void func_0034AF00(SkillDualSelection* object)
{
    if (object->mode == 0)
    {
        u8 inactive = !object->first->unk35;
        if (inactive == 1)
        {
            return;
        }
    }
    else if (object->mode == 1)
    {
        u8 inactive = !object->second->unk35;
        if (inactive == 1)
        {
            return;
        }
    }
    object->func_slotb4();
}

void func_0034AF90(SkillDualSelection* object)
{
    if (object->mode == 0)
    {
        if (object->count <= 1)
        {
            return;
        }
        FieldObject23CEA0* selection = object->first;
        u8 inactive = !selection->unk35;
        if (inactive == 1)
        {
            return;
        }
        if (selection->func_0023CDB0(1) != 1)
        {
            func_0034A2B0(object, 0);
            func_00349E80(object);
        }
    }
    else if (object->mode == 1)
    {
        FieldObject23CEA0* selection = object->second;
        u8 inactive = !selection->unk35;
        if (inactive == 1)
        {
            return;
        }
        if (selection->func_0023CDB0(1) != 1)
        {
            func_0034A130(object, 0);
            func_00349E80(object);
        }
    }
}

void func_0034B090(SkillDualSelection* object)
{
    if (object->mode == 0)
    {
        if (object->count <= 1)
        {
            return;
        }
        FieldObject23CEA0* selection = object->first;
        u8 inactive = !selection->unk35;
        if (inactive == 1)
        {
            return;
        }
        if (selection->func_0023CDB0(0) != 1)
        {
            func_0034A2B0(object, 0);
            func_00349E80(object);
        }
    }
    else if (object->mode == 1)
    {
        FieldObject23CEA0* selection = object->second;
        u8 inactive = !selection->unk35;
        if (inactive == 1)
        {
            return;
        }
        if (selection->func_0023CDB0(0) != 1)
        {
            func_0034A130(object, 0);
            func_00349E80(object);
        }
    }
}

/**
 * @brief Configure the second grid and register its newly allocated display object.
 * @param record Receiver containing the second grid and display owner.
 * @return One after setup, otherwise zero without the second grid.
 */
s32 func_0034B190(SkillDualSelection* record)
{
    float x;
    float y;
    FieldObject23BE00* display;
    if (record->second == 0)
    {
        return 0;
    }
    x = record->unk10->unk20.components[0] + record->second_x;
    y = record->unk10->unk20.components[1] + record->second_y;
    display = (FieldObject23BE00*)::operator new(108, 0);
    if (display != 0)
    {
        display = func_0023BE00(display);
    }
    record->second_display = display;
    func_0023BB20(record->second_display, reinterpret_cast<FieldObject23CEB0*>(record->second), 0x808080, record->second_x, record->second_y, 96.0f, 1.0f);
    func_4C6190(record->unk10, record->second_display);
    func_0035C440(reinterpret_cast<SkillList*>(&record->unk8c), record->second_display);
    func_0023CE80((FieldObject23CE80*)record->second, 1, 2);
    func_0023CE60((FieldObject23CE80*)record->second, 0.0f, record->second_spacing);
    record->second->unkF2 = 0;
    record->second->unk119 = 1;
    func_0023CF50(reinterpret_cast<FieldObject23CEB0*>(record->second), 0, x, y);
    func_0023CEA0(record->second, 0);
    func_0035C4D0(reinterpret_cast<SkillList*>(&record->unk74), record->second);
    return 1;
}

/**
 * @brief Configure the first grid and register its newly allocated display object.
 * @param record Receiver containing the first grid and display owner.
 * @return One after setup, otherwise zero without the first grid.
 */
s32 func_0034B2C0(SkillDualSelection* record)
{
    float x;
    float y;
    FieldObject23BE00* display;
    if (record->first == 0)
    {
        return 0;
    }
    x = record->unk10->unk20.components[0] + record->first_x;
    y = record->unk10->unk20.components[1] + record->first_y;
    display = (FieldObject23BE00*)::operator new(108, 0);
    if (display != 0)
    {
        display = func_0023BE00(display);
    }
    record->first_display = display;
    func_0023BB20(record->first_display, reinterpret_cast<FieldObject23CEB0*>(record->first), 0x808080, record->first_x, record->first_y, 48.0f, 1.0f);
    func_4C6190(record->unk10, record->first_display);
    func_0035C440(reinterpret_cast<SkillList*>(&record->unk8c), record->first_display);
    func_0023CE80((FieldObject23CE80*)record->first, 1, 7);
    func_0023CE60((FieldObject23CE80*)record->first, 0.0f, record->first_spacing);
    record->first->unkF2 = 0;
    record->first->unk119 = 1;
    func_0023CF50(reinterpret_cast<FieldObject23CEB0*>(record->first), 0, x, y);
    func_0023CEA0(record->first, 0);
    func_0035C4D0(reinterpret_cast<SkillList*>(&record->unk74), record->first);
    return 1;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034B3F0);

/** @brief Initialize the scalar indicator storage and select kind five. */
inline ItemCreationClass172600::ItemCreationClass172600()
{
    unk38 = 5;
}

u8 func_0034B720(SkillDualSelection* object)
{
    object->first_spacing = 26.0f;
    object->first_x = 64.0f;
    object->first_y = 14.0f;
    for (s32 index = 0; index < 7; index++)
    {
        LibObject178750* item = new (0) LibObject178750;
        if (item == 0)
        {
            return 0;
        }
        s32 slot = static_cast<s32>(object->func_slot54());
        func_004C7FE0(item, slot, index + 0x1AAA, 0, object->first_x, object->first_y + object->first_spacing * (float)index, 0.0f, 0.0f);
        item->unk88 = -1.0f;
        item->unk3c = 1;
        func_004C6190(object->unk10, item);
        func_0035C9D0(reinterpret_cast<SkillList*>(&object->unk2c), item);
    }
    object->first_marker = new (0) LibClass172600;
    func_0041AD10(object->first_marker, object->first_x, object->first_y, 72.0f, 24.0f);
    object->first_marker->unk3d = 0;
    func_004C6190(object->unk10, object->first_marker);
    object->second_spacing = 48.0f;
    object->second_x = 116.0f;
    object->second_y = 8.0f + (104.0f - object->second_spacing);
    for (s32 index = 0; index < 2; index++)
    {
        LibObject178750* item = new (0) LibObject178750;
        if (item == 0)
        {
            return 0;
        }
        s32 slot = static_cast<s32>(object->func_slot54());
        func_004C7FE0(item, slot, index + 0x1AB8, 0, object->second_x, object->second_y + object->second_spacing * (float)index, 0.0f, 0.0f);
        item->unk88 = -1.0f;
        item->unk3c = 1;
        func_004C6190(object->unk10, item);
        func_0035C9D0(reinterpret_cast<SkillList*>(&object->list), item);
    }
    object->second_marker = new (0) LibClass172600;
    func_0041AD10(object->second_marker, object->second_x, object->second_y, 96.0f, 24.0f);
    object->second_marker->unk3d = 0;
    func_004C6190(object->unk10, object->second_marker);
    return 1;
}

s32 func_0034BA30(SkillDualSelection* object, u32 associated)
{
    object->FieldClass15AE70::func_slot10(associated, 320.0f, 176.0f, 15);
    LibClass1746A0* first = new (0) LibClass1746A0;
    LibClass1746A0* second = new (0) LibClass1746A0;
    object->first = new (0) FieldObject23CEA0;
    object->second = new (0) FieldObject23CEA0;
    if (first == 0 || second == 0 || object->first == 0 || object->second == 0)
    {
        return 0;
    }
    func_44B570(first, 14.0f, 14.0f, 278.0f, 182.0f);
    func_004C6190(object->unk10, first);
    func_0035CB20(reinterpret_cast<SkillList*>(&object->unk20), first);
    if ((u8)func_0034B720(object) == 0)
    {
        return 0;
    }
    func_44B510(second, 1);
    func_004C6190(object->unk10, second);
    func_0035CB20(reinterpret_cast<SkillList*>(&object->unk20), second);
    if ((u8)func_0034B2C0(object) == 0 ||
        (u8)func_0034B190(object) == 0)
    {
        return 0;
    }
    func_0034B3F0(object);
    func_0034A2B0(object, 1);
    func_0034A130(object, 1);
    func_00349F30(object, 2);
    return 1;
}

SkillDualSelection::~SkillDualSelection()
{
}

SkillDualSelection::SkillDualSelection()
{
    first = 0;
    first_display = 0;
    first_spacing = 0.0f;
    second = 0;
    second_display = 0;
    second_spacing = 0.0f;
    mode = -1;
    records = 0;
    first_x = 0.0f;
    first_y = 0.0f;
    second_x = 0.0f;
    second_y = 0.0f;
    first_marker = 0;
    second_marker = 0;
    count = 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034BD30);

void func_0034BEE0(Record0034C1F0* record)
{
    s32 index;
    for (index = 0; index < 42; index++)
    {
        ListItem0035CCE0* first = (ListItem0035CCE0*)func_0035CAE0(reinterpret_cast<SkillList*>(&record->unk2c), index)->value;
        ListItem0035CCE0* second = (ListItem0035CCE0*)func_0035C890(reinterpret_cast<SkillList*>(&record->second), index)->value;
        if (record->values[index] == 0 && index > 0)
        {
            first->unk3f = 0;
            second->unk3f = 0;
        }
        else if (index == record->selection->unk114)
        {
            if (record->colors[index] != 0)
            {
                first->unk94 = 0x288080;
                first->unk3c = 1;
                second->unk94 = 0x288080;
                second->unk3c = 1;
            }
            else
            {
                first->unk94 = 0x505050;
                first->unk3c = 1;
                second->unk94 = 0x505050;
                second->unk3c = 1;
            }
            func_0034BD30(record, index);
            func_4C69B0(first);
            func_4C6A40(first);
        }
        else if (record->colors[index] != 0)
        {
            first->unk94 = 0x808080;
            first->unk3c = 1;
            second->unk94 = 0x288080;
            second->unk3c = 1;
        }
        else
        {
            first->unk94 = 0x505050;
            first->unk3c = 1;
            second->unk94 = 0x505050;
            second->unk3c = 1;
        }
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034C060);

void func_0034C110(Record0034C110* record, float offset)
{
    s32 index = 0;
    ListNode0035CCE0* first = reinterpret_cast<ListNode0035CCE0*>(record->unk2c.unk00)->next;
    ListNode0035CCE0* second = reinterpret_cast<ListNode0035CCE0*>(record->second.head)->next;
    while (first != 0)
    {
        ListItem0035CCE0* item = first->value;
        float z;
        float w;
        float second_z;
        float second_w;
        float row;
        float x;
        float y;
        float second_x;
        float second_y;
        row = (float)index;
        x = record->first_position.x;
        y = record->first_position.y;
        z = record->first_position.z;
        w = record->first_position.w;
        y -= offset;
        y += record->spacing * row;
        item->position.x = x;
        item->position.y = y;
        item->position.z = z;
        item->position.w = w;
        item->unk3c = 1;
        item = first->value;
        item->unk94 = 0x808080;
        item->unk3c = 1;
        first = first->next;
        if (second != 0)
        {
            second_x = record->second_position.x;
            second_y = record->second_position.y;
            second_z = record->second_position.z;
            second_w = record->second_position.w;
            second_y -= offset;
            second_y += record->spacing * row;
            item = second->value;
            item->position.x = second_x;
            item->position.y = second_y;
            item->position.z = second_z;
            item->position.w = second_w;
            item->unk3c = 1;
            item = second->value;
            item->unk94 = 0x288080;
            item->unk3c = 1;
            second = second->next;
        }
        index++;
    }
}

/**
 * @brief Refresh the selected item's display receiver and color.
 * @param record Receiver containing the item list and selection state.
 */
void func_0034C1F0(Record0034C1F0* record)
{
    SkillListNode* node = func_0035CAE0(reinterpret_cast<SkillList*>(&record->unk2c), record->selection->unk114);
    if (record->recipient != 0)
    {
        if (record->state != 0 && record->animation_mode == 2)
        {
            record->recipient->flag3F = 0;
        }
        else
        {
            record->recipient->flag3F = 1;
        }
    }
    if (node != 0)
    {
        if (record->recipient == 0)
        {
            FieldObject23B950* recipient = (FieldObject23B950*)::operator new(sizeof(FieldObject23B950), 0);
            if (recipient != 0)
            {
                recipient = func_0023B950(recipient);
            }
            record->recipient = recipient;
            func_0023B850((FieldObject23B850*)record->recipient, (FieldTarget23B850*)node->value, 0x288080);
            func_4C6190(record->unk10, record->recipient);
        }
        func_0023B7E0(record->recipient, (FieldTarget23B850*)node->value);
        if (record->colors[record->selection->unk114] != 0)
        {
            func_420D20((FieldObject23B850*)record->recipient, 0x288080);
        }
        else
        {
            func_420D20((FieldObject23B850*)record->recipient, 0x505050);
        }
        func_0023B780(record->recipient);
    }
}

/**
 * @brief Update the active mode window and its list indicator.
 * @param object Mode window.
 */
void func_0034C320(SkillModeSelection* object)
{
    if (D_001B643C->callbacks->controller->func_00261150() != object)
    {
        return;
    }
    switch (object->state)
    {
    case 0:
    {
        s32 key = object->values[object->selection->unk114];
        if (key == 0)
        {
            return;
        }
        s32 message = message_from_key(key);
        SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
        if (owner != 0)
        {
            if (message < 0)
            {
                message = 0;
            }
            owner->message = message;
            refresh_owner_message(owner);
        }
        break;
    }
    case 1:
        if (object->animation_mode == 2)
        {
            object->step *= -1.0f;
        }
        object->state = 2;
    case 2:
        func_0034C060(object);
        if (object->remaining <= 0.0f)
        {
            object->state = 3;
        }
        else
        {
            break;
        }
    case 3:
        object->animation_mode = 0;
        object->step = 0.0f;
        object->remaining = 0.0f;
        object->state = 0;
        break;
    }
    if (object->count > 0)
    {
        object->marker->unk3f = 1;
        LibClass1725D0* marker = object->marker;
        marker->unk50 = 100.0f * (6.0f / object->track_size);
        marker->unk3c = 1;
        marker = object->marker;
        marker->unk54 = 100.0f * ((float)object->selection->row_count / object->track_size);
        marker->unk3c = 1;
    }
    else
    {
        object->marker->unk3f = 0;
    }
    func_0034C1F0(object);
}

u32 func_0034C520(u8* object)
{
    return *(u32*)(object + 0x20);
}

s32 func_0034C530(void* object)
{
    return 0;
}

s32 func_0034C540(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034C550);

u32 func_0034C7C0(u8* object)
{
    return *(u32*)(object + 0x44);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034C7D0);

/**
 * @brief Refresh the optional controller owner's message for the selected mode entry.
 * @param object Mode selection window.
 */
static inline void refresh_mode_message(SkillModeSelection* object)
{
    s16 selected = object->selection->unk114;
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    if (owner != 0)
    {
        s32 message = object->values[selected] - 0x18FF;
        if (message < 0)
        {
            message = 0;
        }
        owner->message = message;
        refresh_owner_message(owner);
    }
}
s32 func_0034DA70(SkillModeSelection* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->FieldClass151C50::unk35;
    if (inactive == 1)
    {
        return 0;
    }
    if ((s32)object->state > 0)
    {
        return 0;
    }
    s16 first = selection->row_count;
    s16 selected = selection->unk114;
    s32 count = object->item_count;
    s32 first_index;
    s32 last_index = count - 1;
    if (selected >= last_index)
    {
        return 0;
    }
    if (count < 2)
    {
        return 0;
    }
    s32 visible_index;
    if (count < 6)
    {
        visible_index = last_index;
        first_index = 0;
    }
    else
    {
        visible_index = selected - first;
        first_index = first + 6;
        s32 end = first_index + 6;
        if (end >= count)
        {
            visible_index += end - count;
            first_index = count - 6;
            if (visible_index >= 6)
            {
                visible_index = 5;
            }
        }
    }
    object->step = -object->spacing * (float)(first_index - first);
    object->animation_mode = 2;
    func_0034C060(object);
    object->selection->row_count = first_index;
    selection = object->selection;
    selection->index = visible_index;
    func_0023CB30(selection);
    func_0023CEE0(reinterpret_cast<FieldObject23CEB0*>(object->selection));
    func_0034BEE0(object);
    func_0034C1F0(object);
    refresh_mode_message(object);
    refresh_mode_message(object);
    func_0034C1F0(object);
    func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    return 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034DCE0);

void func_0034DF00(SkillModeSelection* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->FieldClass151C50::unk35;
    if (inactive == 1)
    {
        return;
    }
    if (object->state > 0)
    {
        return;
    }
    if (selection->unk114 + 1 >= object->item_count)
    {
        return;
    }
    u8 result = selection->func_0023CDB0(1);
    if (result == 1)
    {
        return;
    }
    if (result == 3)
    {
        object->state = 1;
        object->step = object->spacing / 4.0f;
        object->remaining = 4.0f;
        object->animation_mode = 2;
    }
    func_0034BEE0(object);
    func_0034C1F0(object);
    refresh_mode_message(object);
    refresh_mode_message(object);
}

void func_0034E0B0(SkillModeSelection* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->FieldClass151C50::unk35;
    if (inactive == 1)
    {
        return;
    }
    if (object->state > 0)
    {
        return;
    }
    s16 selected = selection->unk114;
    if (selection->row_count == 0 && selected == 0)
    {
        return;
    }
    u8 result = selection->func_0023CDB0(0);
    if (result == 1)
    {
        return;
    }
    if (result == 2)
    {
        object->state = 1;
        object->step = object->spacing / 4.0f;
        object->remaining = 4.0f;
        object->animation_mode = 1;
    }
    func_0034BEE0(object);
    func_0034C1F0(object);
    refresh_mode_message(object);
    refresh_mode_message(object);
}

/**
 * @brief Configure the selection grid position and register its display state.
 * @param record Receiver with the display owner and selection grid.
 * @param row_count Number of grid rows; zero leaves the grid unchanged.
 * @return One for zero rows or completed setup, otherwise zero without a display owner.
 */
s32 func_0034E260(Record0034C1F0* record, s16 row_count)
{
    float first;
    float second;
    if (row_count == 0)
    {
        return 1;
    }
    if (record->unk10 == 0)
    {
        return 0;
    }
    first = record->unk10->unk20.components[0] + record->offset;
    second = 16.0f + record->unk10->unk20.components[1];
    func_0023CE80((FieldObject23CE80*)record->selection, 1, row_count);
    func_0023CE60((FieldObject23CE80*)record->selection, 0.0f, record->spacing);
    record->selection->unkF2 = 0;
    record->selection->unk119 = 0;
    reinterpret_cast<FieldObject23CEB0*>(record->selection)->unk116 = 36;
    func_0023CF50(reinterpret_cast<FieldObject23CEB0*>(record->selection), 0, first, second);
    func_0035C4D0(reinterpret_cast<SkillList*>(&record->unk74), record->selection);
    if (record->selection != 0)
    {
        FieldObject23B950* recipient = record->recipient;
        if (recipient != 0)
        {
            recipient->unk28 = 0;
            recipient->flag3C = 1;
        }
        func_0023CEA0((FieldObject23CEA0*)record->selection, 0);
    }
    return 1;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034E380);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034F1A0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034FB40);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0034FC30);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003505C0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003506B0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00350890);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00351090);

void func_00351360(SkillModeSelection* object, u32 flag, s32 active)
{
    object->flag = flag;
    object->func_slot18(flag, 2);
    if (object->selection != 0)
    {
        LibClass178600* recipient = reinterpret_cast<LibClass178600*>(object->recipient);
        if (recipient != 0)
        {
            if (active != 0)
            {
                recipient->unk28 = 128.0f;
                recipient->unk3c = 1;
            }
            else
            {
                recipient->unk28 = 0.0f;
                recipient->unk3c = 1;
            }
        }
        func_0023CEA0(object->selection, active);
    }
    SkillListNode* node = object->second.head->next;
    s32 index = 0;
    for (; node != 0; node = node->next, index++)
    {
        if (index == 0)
        {
            static_cast<LibClass178600*>(node->value)->unk3f = 0;
        }
        else
        {
            static_cast<LibClass178600*>(node->value)->unk3f = flag & 0xFF;
        }
    }
    object->display->unk3f = flag;
    if ((u8)flag == 1 && (u8)active == 1)
    {
        func_0034BEE0(object);
    }
    if ((u8)flag == 0)
    {
        object->marker->unk3f = 0;
    }
}

#include "overlays/lib/list_indicator_inlines.h"

s32 func_00351490(SkillModeSelection* object, u32 associated)
{
    object->FieldClass15AE70::func_slot10(associated, 320.0f, 176.0f, 15);
    object->display = new (0) LibObject178750;
    object->display->func_004C7FE0(248.0f, 9.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x1787, 1);
    func_004C6190(object->unk10, object->display);
    object->display->set_color(0x288CFF);
    object->display->set_scale(0.6f, 0.6f);
    {
        LibObject178750* display = object->display;
        display->unk88 = 2.0f;
        display->unk3c = 1;
    }
    object->display->unk3f = 0;
    LibClass1746A0* first = new (0) LibClass1746A0;
    LibClass1746A0* second = new (0) LibClass1746A0;
    object->selection = new (0) FieldObject23CEA0;
    if (first == 0 || second == 0 || object->selection == 0)
    {
        return 0;
    }
    func_44B570(first, 14.0f, 20.0f, 278.0f, 176.0f);
    func_004C6190(object->unk10, first);
    func_0035CB20(reinterpret_cast<SkillList*>(&object->unk20), first);
    if ((u8)func_00351090(object) == 0)
    {
        return 0;
    }
    object->marker = new (0) LibClass1725D0;
    func_41A930(object->marker, 280.0f, 18.0f, 178.0f, 100.0f, 0.0f);
    func_004C6190(object->unk10, object->marker);
    object->marker->unk3f = 0;
    func_44B510(second, 1);
    func_004C6190(object->unk10, second);
    func_0035CB20(reinterpret_cast<SkillList*>(&object->unk20), second);
    if ((u8)func_0034E260(object, 6) == 0)
    {
        return 0;
    }
    return 1;
}

SkillModeSelection::~SkillModeSelection()
{
}
SkillModeSelection::SkillModeSelection(SkillQueueOwner* controller)
{
    selection = 0;
    spacing = 29.0f;
    offset = 20.0f;
    row_height = 24.0f;
    mode_records = 0;
    state = 0;
    step = 0;
    remaining = 0;
    unke0 = 0;
    recipient = 0;
    mode = -1;
    for (s32 i = 0; i < 42; i++)
    {
        values[i] = 0;
        unk190[i] = 0;
        unk1ba[i] = 0;
        unk230[i] = 0;
        item_count = 0;
    }
    state = 0;
    if (selection != 0)
    {
        func_0023C710(selection);
    }
    marker = 0;
    track_size = 0;
    owner = 0;
    owner = controller;
    flag = 0;
    display = 0;
}

s32 func_00351980(FieldClass15AE70* object, u32 associated)
{
    func_002CE8D0(reinterpret_cast<FieldObjectCE8D0*>(object), associated, 320.0f, 176.0f, 0xF);
    LibClass178630* widget = new (0) LibClass178630;
    if (widget == 0)
    {
        return 0;
    }
    func_004C5A80(widget, 0, 0.0f, 0.0f, 304.0f, 208.0f, 88.0f);
    func_004C6190(object->unk10, widget);
    return 1;
}

SkillModeMessageWindow::~SkillModeMessageWindow()
{
}

void func_00351AC0(Record00352B30* object)
{
    func_00351BE0(object);
    if (D_001B643C->callbacks->controller->func_00261150() == object)
    {
        FieldClass15AE70* window = static_cast<FieldClass15AE70*>(object->func_slot4c());
        window->func_slot18(0, 4);
    }
}

void func_00351B30(Record00352B30* object)
{
    FieldObject23CEA0* selection = object->selection;
    selection->FieldClass151C50::unk30 = 128.0f;
    selection->unkae = 1;
    LibObject178660* display = object->attachment->unk10;
    if (display != 0)
    {
        display->unkab = 1;
    }
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    FieldClass15AE70* window = owner->window;
    if (object->unk104 > 0)
    {
        window->func_slot60(object->modes[object->selection->unk114] + 0x1AA3);
    }
    else
    {
        window->func_slot60(0x1795);
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00351BE0);

void func_003521C0(Record00352B30* record)
{
    QuerySelection* selection = record->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (record->unk104 < 2)
    {
        return;
    }
    if (selection->func_0023CDB0(1) != 1)
    {
        func_00351BE0(record);
    }
}

void func_00352240(Record00352B30* record)
{
    QuerySelection* selection = record->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (record->unk104 < 2)
    {
        return;
    }
    if (selection->func_0023CDB0(0) != 1)
    {
        func_00351BE0(record);
    }
}

void func_003522C0(Record00352B30* object)
{
    u8 mode;
    switch (object->modes[object->selection->unk114])
    {
    case 4:
        mode = 0;
        break;
    case 5:
        mode = 1;
        break;
    default:
        return;
    }
    SkillDualSelection* window = static_cast<SkillDualSelection*>(object->func_slot4c());
    func_00349F30(window, mode);
    FieldObject23CEA0* selection = object->selection;
    selection->FieldClass151C50::unk30 = 64.0f;
    selection->unkae = 1;
    LibObject178660* display = object->attachment->unk10;
    if (display != 0)
    {
        display->unkab = 0;
    }
    D_001B643C->callbacks->controller->func_00263C70(window);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003523A0);

s32 func_00352630(Record00352B30* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    StatusOwner003580D0* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    object->values[(u8)object->records->slots[object->records->current]] = selection->index;
    return cycle_status_record(status, 1);
}

s32 func_003527A0(Record00352B30* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    StatusOwner003580D0* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    object->values[(u8)object->records->slots[object->records->current]] = selection->index;
    return cycle_status_record(status, 0);
}

s32 func_00352920(Record00352B30* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    object->values[(u8)object->records->slots[object->records->current]] = object->selection->index;
    object->unkac[0] = 0;
    object->unkac[1] = 0;
    object->unkac[2] = 0;
    object->unkac[3] = 0;
    object->unkac[4] = 0;
    object->unk104 = 0;
    LibObject178660* display = object->attachment->unk10;
    if (display != 0)
    {
        display->unkab = 0;
    }
    FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(object->func_slot44());
    associated->func_slot64();
    D_001B643C->callbacks->controller->func_00263C70(associated);
    object->active = 1;
    func_00351BE0(object);
    if (D_001B643C->callbacks->controller->func_00261150() == object)
    {
        s32 opacity = object->unk104 ? 128 : 0;
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = (float)opacity;
        cursor->unk3c = 1;
    }
    else
    {
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = 0.0f;
        cursor->unk3c = 1;
    }
    func_0023CEA0(object->selection, 0);
    return 2;
}

s32 func_00352A90(Record00352B30* record)
{
    QuerySelection* selection = record->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    if (record->unk104 == 0)
    {
        return 0;
    }
    record->values[(u8)record->records->slots[record->records->current]] = selection->index;
    if (func_003523A0(record) == 3)
    {
        return 3;
    }
    return 1;
}

s32 func_00352B30(Record00352B30* record)
{
    QuerySelection* selection = record->selection;
    u8 inactive = !selection->unk35;
    s16 index;
    s16 mode;
    LibClass178600* display;

    if (inactive == 1)
    {
        return 0;
    }
    index = selection->unk114;
    if (record->unk104 == 0)
    {
        return 3;
    }
    mode = record->modes[index];
    if (mode == 4 || mode == 5)
    {
        func_003522C0(record);
        display = record->parent->status->first_display;
        if (display != 0)
        {
            display->unk3f = 0;
        }
        display = record->parent->status->second_display;
        if (display != 0)
        {
            display->unk3f = 0;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00352C00);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00353040);

RecordWithMethods* func_00353380(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183370;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003533E0);

s32 func_003534C0(StatusOwner003534C0* owner, s32 mode)
{
    s32 sum = 0;
    s32 i;
    owner->unk108[0]->unk3f = mode;
    if (mode != 0)
    {
        for (i = 0; i < 6; i++)
        {
            s32 value = owner->unk128[i];
            StatusItem* item = owner->unk108[i + 1];
            item->unkfc = value;
            item->unk3c = 1;
            if (value == -1)
            {
                owner->unk108[i + 1]->unk3f = 0;
                value = 0;
            }
            else
            {
                owner->unk108[i + 1]->unk3f = 1;
            }
            sum += value;
        }
    }
    else
    {
        for (i = 0; i < 6; i++)
        {
            owner->unk108[i + 1]->unk3f = 0;
        }
    }
    return sum;
}

/**
 * @brief Set the low byte of each linked display flag.
 * @param list Display list.
 * @param flag Full flag word.
 */
static inline void set_list_display_flags(SkillList183C38* list, u32 flag)
{
    for (SkillListNode* node = list->head->next; node != 0; node = node->next)
    {
        static_cast<LibClass178600*>(node->value)->unk3f = flag & 0xFF;
    }
}

void func_00353570(Record003538F0* object, u32 flag, s32 active)
{
    object->flag = flag;
    object->active = active;
    object->func_slot18(flag, 0x42);
    set_list_display_flags(&object->second, flag);
    set_list_display_flags(&object->third, flag);
    if (active != 0)
    {
        LibClass178600* display = reinterpret_cast<LibClass178600*>(object->display);
        display->unk28 = 128.0f;
        display->unk3c = 1;
    }
    else
    {
        LibClass178600* display = reinterpret_cast<LibClass178600*>(object->display);
        display->unk28 = 0.0f;
        display->unk3c = 1;
    }
    func_0023CEA0(object->selection, active);
    func_003534C0(object, flag);
}

void func_00353670(Record003538F0* object)
{
    FieldObject23CEA0* selection = object->selection;
    selection->FieldClass151C50::unk30 = 128.0f;
    selection->unkae = 1;
    func_003538F0(object);
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    StatusOwner003580D0* status = owner->status;
    if (owner != 0 && status != 0)
    {
        s32 index = object->selection->unk114;
        if (object->keys[index] == 0x178A)
        {
            func_003580D0(status, -1, -1, -1);
        }
        else
        {
            func_003580D0(status, object->first_values[index], object->second_values[index], object->third_values[index]);
        }
    }
}

void func_00353720(void* receiver)
{
    Record003538F0* object = static_cast<Record003538F0*>(receiver);
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    FieldObject23CEA0* selection = object->selection;
    FieldClass15AE70* window = owner->window;
    if (selection == 0 || owner == 0 || window == 0)
    {
        return;
    }
    s16 row = selection->unk114;
    s32 key = object->keys[row];
    if (key == 0x178A)
    {
        owner->message = 0;
        refresh_owner_message(owner);
        window->func_slot60(0x1795);
    }
    else
    {
        set_row_message(owner, row, key);
        s32 text = key + 0xC8;
        if (text >= 0x1A62)
        {
            window->func_slot60(0x1A62);
        }
        else
        {
            window->func_slot60(text);
        }
    }
}

void func_003538A0(void* object)
{
    if (D_001B643C->callbacks->controller->func_00261150() == object)
    {
        func_00353720(object);
    }
}

void func_003538F0(Record003538F0* record)
{
    s32 index;
    for (index = 0; index < 6; index++)
    {
        ListItem0035CCE0* first = (ListItem0035CCE0*)func_0035CAE0(reinterpret_cast<SkillList*>(&record->unk2c), index)->value;
        ListItem0035CCE0* second = (ListItem0035CCE0*)func_0035CAE0(reinterpret_cast<SkillList*>(&record->second), index)->value;
        if (index == record->selection->unk114)
        {
            LibBounds4C69B0* metrics;
            first->unk94 = 0x288080;
            first->unk3c = 1;
            second->unk94 = 0x288080;
            second->unk3c = 1;
            metrics = (LibBounds4C69B0*)func_4C69B0(first);
            func_0023BAB0(record->display, first->position.x,
                         1.0f + (24.0f + first->position.y), 16.0f + metrics->unk08);
        }
        else
        {
            first->unk94 = 0x808080;
            first->unk3c = 1;
            second->unk94 = 0x808080;
            second->unk3c = 1;
        }
    }
}

s32 func_003539F0(Record003538F0* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    StatusOwner003580D0* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    return cycle_status_record(status, 1);
}

s32 func_00353B40(Record003538F0* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    StatusOwner003580D0* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    return cycle_status_record(status, 0);
}

void func_00353CA0(Record003538F0* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (selection != 0 && selection->unk114 == 3)
    {
        func_0023CE70(reinterpret_cast<FieldObject23CEB0*>(selection), object->x, object->y + object->spacing);
    }
    if (object->selection->func_0023CDB0(1) == 1)
    {
        return;
    }
    if (object->attachment != 0)
    {
        object->attachment->active = 0;
    }
    func_003538F0(object);
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    StatusOwner003580D0* status = owner->status;
    if (owner != 0)
    {
        if (status != 0)
        {
            s32 index = object->selection->unk114;
            if (object->keys[index] == 0x178A)
            {
                func_003580D0(status, -1, -1, -1);
            }
            else
            {
                func_003580D0(status, object->first_values[index], object->second_values[index], object->third_values[index]);
            }
        }
    }
}

void func_00353DC0(Record003538F0* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (selection != 0 && selection->unk114 == 4)
    {
        func_0023CE70(reinterpret_cast<FieldObject23CEB0*>(selection), object->x, object->y);
    }
    if (object->selection->func_0023CDB0(0) == 1)
    {
        return;
    }
    if (object->attachment != 0)
    {
        object->attachment->active = 0;
    }
    func_003538F0(object);
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    StatusOwner003580D0* status = owner->status;
    if (owner != 0)
    {
        if (status != 0)
        {
            s32 index = object->selection->unk114;
            if (object->keys[index] == 0x178A)
            {
                func_003580D0(status, -1, -1, -1);
            }
            else
            {
                func_003580D0(status, object->first_values[index], object->second_values[index], object->third_values[index]);
            }
        }
    }
}

s32 func_00353EE0(Record003538F0* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillQueueOwner* owner = object->owner;
    if (owner != 0)
    {
        owner->message = 0;
        refresh_owner_message(owner);
    }
    for (s32 index = 0; index < 6; index++)
    {
        ListItem0035CCE0* first = static_cast<ListItem0035CCE0*>(func_0035CAE0(reinterpret_cast<SkillList*>(&object->unk2c), index)->value);
        if (first != 0)
        {
            first->unk94 = 0x808080;
            first->unk3c = 1;
        }
        ListItem0035CCE0* second = static_cast<ListItem0035CCE0*>(func_0035CAE0(reinterpret_cast<SkillList*>(&object->second), index)->value);
        if (second != 0)
        {
            second->unk94 = 0x808080;
            second->unk3c = 1;
        }
    }
    SkillModeSelection* mode = static_cast<SkillModeSelection*>(object->func_slot4c());
    if (mode != 0 && object->selection != 0)
    {
        func_00351360(mode, 0, 0);
    }
    func_00353570(object, 1, 0);
    FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(object->func_slot44());
    associated->func_slot64();
    D_001B643C->callbacks->controller->func_00263C70(associated);
    return 2;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00354060);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00354190);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003547C0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00354D80);

Record00355420* func_00355420(Record00355420* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_159FE0;
        func_4618F0(&record->unk40, -1);
        func_4C48B0(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

Record00355490* func_00355490(Record00355490* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_178A70;
        release_record182f60(&record->base, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

Record003538F0::~Record003538F0()
{
}
Record003538F0::Record003538F0(SkillQueueOwner* controller)
{
    attachment = 0;
    selection = 0;
    row_x = 0.0f;
    row_y = 0.0f;
    row_spacing = 0.0f;
    x = 0.0f;
    y = 0.0f;
    spacing = 0.0f;
    mode_records = 0;
    display = 0;
    unk108[0] = 0;
    unk124 = 258.0f;
    for (s32 index = 0; index < 6; index++)
    {
        keys[index] = 0;
        unk128[index] = -1;
        unk108[index + 1] = 0;
        first_values[index] = -1;
        second_values[index] = -1;
        third_values[index] = -1;
    }
    flag = 0;
    active = 0;
    owner = 0;
    owner = controller;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003556B0);

void func_003558B0(SkillFourRowSelection* object, u32 flag, s32 active)
{
    object->flag = flag;
    object->func_slot18(flag, 10);
    object->first_display->unk3f = flag;
    object->second_display->unk3f = flag;
    object->third_display->unk3f = flag;
    object->cursor->unk3f = flag;
    if (active != 0)
    {
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = 128.0f;
        cursor->unk3c = 1;
    }
    else
    {
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = 0.0f;
        cursor->unk3c = 1;
    }
    func_0023CEA0(object->selection, active);
    if (active != 0)
    {
        object->message->func_slot60(0x1A91 + object->selection->unk114);
    }
    if ((u8)flag == 0)
    {
        for (s32 index = 0; index < 4; index++)
        {
            object->first_rows[index]->unk3f = 0;
            object->second_rows[index]->unk3f = 0;
            object->third_rows[index]->unk3f = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003559F0);

void func_00355CA0(SkillFourRowSelection* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (selection->func_0023CDB0(1) == 1)
    {
        return;
    }
    for (s32 index = 0; index < 4; index++)
    {
        LibObject178750* item = static_cast<LibObject178750*>(func_0035CAE0(reinterpret_cast<SkillList*>(&object->unk2c), index)->value);
        if (index == object->selection->unk114)
        {
            item->unk94 = 0x288080;
            item->unk3c = 1;
            LibBounds4C69B0* metrics = func_004C69B0(item);
            func_0023B9B0(object->cursor, (s16)index, metrics->unk08);
        }
        else
        {
            item->unk94 = 0x808080;
            item->unk3c = 1;
        }
    }
}

void func_00355D90(SkillFourRowSelection* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (selection->func_0023CDB0(0) == 1)
    {
        return;
    }
    for (s32 index = 0; index < 4; index++)
    {
        LibObject178750* item = static_cast<LibObject178750*>(func_0035CAE0(reinterpret_cast<SkillList*>(&object->unk2c), index)->value);
        if (index == object->selection->unk114)
        {
            item->unk94 = 0x288080;
            item->unk3c = 1;
            LibBounds4C69B0* metrics = func_004C69B0(item);
            func_0023B9B0(object->cursor, (s16)index, metrics->unk08);
        }
        else
        {
            item->unk94 = 0x808080;
            item->unk3c = 1;
        }
    }
}

s32 func_00355E80(SkillFourRowSelection* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    StatusOwner003580D0* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    return cycle_status_record(status, 1);
}

s32 func_00355FD0(SkillFourRowSelection* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    StatusOwner003580D0* status = owner->status;
    if (owner == 0 || status == 0)
    {
        return 0;
    }
    return cycle_status_record(status, 0);
}

s32 func_00356130(SkillFourRowSelection* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    for (s32 index = 0; index < 4; index++)
    {
        LibObject178750* item = static_cast<LibObject178750*>(func_0035CAE0(reinterpret_cast<SkillList*>(&object->unk2c), index)->value);
        item->unk94 = 0x808080;
        item->unk3c = 1;
    }
    func_003558B0(object, 1, 0);
    static_cast<FieldClass15AE70*>(object->func_slot44())->func_slot64();
    FieldClass153E30* controller = D_001B643C->callbacks->controller;
    controller->func_00263C70(object->func_slot44());
    return 2;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00356220);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00356CB0);

/** @brief Decode the second value, marking valid protected flags on corruption. */
static inline u32 protected_second(SkillProtectedFlags* record)
{
    u32 first = record->value_second;
    u32 salt = record->salt_second;
    u32 key = protected_key(record);
    u32 encoded = record->encoded_second;
    u32 checksum = record->checksum_second;
    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded;
        s32 flag_salt = record->salt;
        if (record->checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded = ((flags ^ SKILL_FLAG_ENCODING_MASK) | 1) ^ SKILL_FLAG_ENCODING_MASK;
            s32 current_salt = record->salt;
            record->checksum = ((record->encoded + record->key) ^ current_salt) ^ record->key;
        }
        return 0;
    }
    return encoded ^ SKILL_FLAG_ENCODING_MASK;
}


u32 func_00356EE0(SkillProtectedFlags* record)
{
    return protected_second(record);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00356F80);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00357000);

/** @brief Decode the first value, marking valid protected flags on corruption. @param record Protected entry record. @return Decoded first value, or zero after corruption. */
static inline u32 protected_first(SkillProtectedFlags* record)
{
    u32 first = record->value_first;
    u32 salt = record->salt_first;
    u32 key = protected_key(record);
    u32 encoded = record->encoded_first;
    u32 checksum = record->checksum_first;
    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded;
        s32 flag_salt = record->salt;
        if (record->checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded = ((flags ^ SKILL_FLAG_ENCODING_MASK) | 1) ^ SKILL_FLAG_ENCODING_MASK;
            s32 current_salt = record->salt;
            record->checksum = ((record->encoded + record->key) ^ current_salt) ^ record->key;
        }
        return 0;
    }
    return encoded ^ SKILL_FLAG_ENCODING_MASK;
}

u32 func_00357230(SkillProtectedFlags* record)
{
    return protected_first(record);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003572D0);

u32 func_00357350(SkillProtectedFlags* record, u32 flags)
{
    u32 key = record->key;
    u32 value = record->encoded;
    s32 salt = record->salt;
    u32 checksum = record->checksum;
    if (checksum != ((value + key) ^ salt ^ key))
    {
        return 5;
    }
    record->encoded = ((value ^ SKILL_FLAG_ENCODING_MASK) | flags) ^ SKILL_FLAG_ENCODING_MASK;
    s32 current_salt = record->salt;
    record->checksum = ((record->encoded + record->key) ^ current_salt) ^ record->key;
    return record->encoded ^ SKILL_FLAG_ENCODING_MASK;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003573D0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003575A0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00357BF0);

RecordWithMethods* func_00357E80(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183570;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

u8* func_00357EE0(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183570;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xB4) = 0;
    *(float*)(object + 0xB8) = 32.0f;
    *(float*)(object + 0xBC) = 62.0f;
    *(u32*)(object + 0xC0) = 0;
    *(u32*)(object + 0xC4) = 0;
    *(u32*)(object + 0xC8) = 0;
    *(u32*)(object + 0xCC) = 0;
    *(u8*)(object + 0x100) = 0;
    *(u32*)(object + 0xD0) = 0;
    *(u32*)(object + 0xE0) = 0;
    *(u32*)(object + 0xF0) = 0;
    *(u32*)(object + 0xD4) = 0;
    *(u32*)(object + 0xE4) = 0;
    *(u32*)(object + 0xF4) = 0;
    *(u32*)(object + 0xD8) = 0;
    *(u32*)(object + 0xE8) = 0;
    *(u32*)(object + 0xF8) = 0;
    *(u32*)(object + 0xDC) = 0;
    *(u32*)(object + 0xEC) = 0;
    *(u32*)(object + 0xFC) = 0;
    return object;
}

s32 func_00357F80(FieldClass15AE70* object, u32 associated)
{
    func_002CE8D0(reinterpret_cast<FieldObjectCE8D0*>(object), associated, 16.0f, 176.0f, 0x11);
    LibClass178630* widget = new (0) LibClass178630;
    if (widget == 0)
    {
        return 0;
    }
    func_004C5A80(widget, 0, 0.0f, 0.0f, 304.0f, 208.0f, 88.0f);
    func_0035CBB0(reinterpret_cast<SkillList*>(&object->unk14), widget);
    func_004C6190(object->unk10, widget);
    return 1;
}

SkillStatusMessageWindow::~SkillStatusMessageWindow()
{
}

void func_003580D0(StatusOwner003580D0* owner, s32 first, s32 second, s32 third)
{
    if (second == -1)
    {
        owner->items[1]->unk3f = 0;
    }
    else
    {
        LibObject174F20* item = owner->items[1];
        item->numeric_value = second - 1;
        item->unk3c = 1;
        owner->items[1]->unk3f = 1;
    }
    if (first == -1)
    {
        owner->items[0]->unk3f = 0;
    }
    else
    {
        LibObject174F20* item = owner->items[0];
        item->numeric_value = first;
        item->unk3c = 1;
        owner->items[0]->unk3f = 1;
    }
    if (third == -1)
    {
        owner->items[2]->unk3f = 0;
        owner->fallback_label->unk3f = 0;
    }
    else if (first == 10)
    {
        owner->items[2]->unk3f = 0;
        owner->fallback_label->unk3f = 1;
    }
    else
    {
        LibObject174F20* item = owner->items[2];
        item->numeric_value = third;
        item->unk3c = 1;
        owner->items[2]->unk3f = 1;
        owner->fallback_label->unk3f = 0;
    }
}

void func_003581B0(void* object)
{
    Record003581B0* record = (Record003581B0*)object;
    if (record->flag == 1)
    {
        if (record->inner->flag == 1)
        {
            func_00358200(record);
            record->flag = 0;
        }
    }
}

void func_00358200(Record003581B0* record)
{
    StatusDetail* detail;
    u32 key;
    s32 value;
    StatusPointerItem* pointer_item;
    StatusItem* item;

    pointer_item = record->pointer_item;
    pointer_item->unkfc = record->inner->details[record->inner->index].text;
    pointer_item->unk3c = 1;
    detail = &record->inner->details[record->inner->index];
    key = detail->key;
    value = (detail->checksum != (((detail->second + key) ^ detail->first) ^ key)) ? 0 : (detail->first ^ 0x7E93);
    item = record->first_item;
    item->unkfc = value;
    item->unk3c = 1;
    if (record->inner != 0)
    {
        detail = &record->inner->details[record->inner->index];
        if (detail != 0)
        {
            key = detail->key;
            value = (detail->checksum != (((detail->second + key) ^ detail->first) ^ key)) ? 0 : (detail->second ^ 0x7E93);
            item = record->second_item;
            item->unkfc = value;
            item->unk3c = 1;
        }
    }
}

void func_00358310(StatusOwner003580D0* object)
{
    if (object->active != 0 && object->selection != 0)
    {
        u16 code = object->selection->slots[object->selection->current];
        s32 selected = 0;
        for (s32 i = 0; i < 8; i++)
        {
            LibClass178600* icon = object->icons[i];
            if (icon != 0)
            {
                icon->unk3f = 0;
            }
        }
        for (s32 i = 0; i < 8; i++)
        {
            if (code == object->codes[i])
            {
                break;
            }
            selected++;
        }
        LibClass178600* icon = object->icons[selected];
        if (icon != 0)
        {
            icon->unk3f = 1;
        }
        SkillQueueOwner* record = object->owner;
        if (record != 0)
        {
            FieldRecordSelection* selection = object->selection;
            s8 index = selection->current;
            StatusDetail* detail = &static_cast<StatusDetail*>(selection->unk04)[index];
            FieldRecord* entry = &selection->records[index];
            record->entry = entry;
            record->detail = detail;
            record->code = code;
        }
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00358410);

StatusOwner003580D0::~StatusOwner003580D0()
{
}
StatusOwner003580D0::StatusOwner003580D0(SkillQueueOwner* controller)
{
    selection = 0;
    portrait = 0;
    third_value = 0;
    items[0] = 0;
    items[1] = 0;
    items[2] = 0;
    unke4[0] = 0;
    unke4[1] = 0;
    unke4[2] = 0;
    four_rows = 0;
    status_rows = 0;
    mode_query = 0;
    mode_window = 0;
    paired = 0;
    changed = 0;
    fifth_label = 0;
    first_value = 0;
    sixth_label = 0;
    second_value = 0;
    for (s32 index = 0; index < 8; index++)
    {
        icons[index] = 0;
        codes[index] = 0;
    }
    active = 0;
    first_display = 0;
    second_display = 0;
    owner = 0;
    owner = controller;
}

/** Partial secondary selection control and its state byte. */
void func_003592E0(SkillSecondarySelection* object)
{
    FieldObject23CEA0* selection = object->selection;
    selection->FieldClass151C50::unk30 = 128.0f;
    selection->unkae = 1;
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    func_0035AF00(owner, object->code, 1);
    object->state = 0;
}

void func_00359340(SkillSecondarySelection* object)
{
    if (D_001B643C->callbacks->controller->func_00261150() != object)
    {
        return;
    }
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (object->state != 1)
    {
        return;
    }
    s32 key = object->code + 0x1771;
    FieldClass15AE70* window = static_cast<FieldClass15AE70*>(D_001B643C->callbacks->controller->func_00263C90());
    window->func_slot60(key);
    s16 selected = object->code;
    for (s32 index = 0; index <= 2; index++)
    {
        ListItem0035CCE0* item = static_cast<ListItem0035CCE0*>(func_0035CAE0(reinterpret_cast<SkillList*>(&object->unk2c), index)->value);
        if (index == selected)
        {
            item->unk94 = 0x288080;
            item->unk3c = 1;
            LibBounds4C69B0* metrics = static_cast<LibBounds4C69B0*>(func_4C69B0(item));
            func_0023B9B0(object->cursor, (s16)index, metrics->unk08);
        }
        else
        {
            item->unk94 = 0x808080;
            item->unk3c = 1;
        }
    }
    object->state = 0;
}

void SkillResourceWindow::func_slot60(s32 key)
{
}

u32 func_00359490(u8* object)
{
    return *(u32*)(object + 0x24);
}

s32 func_003594A0(SkillSecondarySelection* object)
{
    if (object->func_slot28())
    {
        return 0;
    }
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    return cycle_status_record(object->status, 1);
}

s32 func_003595E0(SkillSecondarySelection* object)
{
    if (object->func_slot28())
    {
        return 0;
    }
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    return cycle_status_record(object->status, 0);
}

s32 func_00359730(FieldClass15AE70* object)
{
    FieldSlotRecordOwner1C* loader = D_001B643C->loader;
    if (loader == 0)
    {
        return 0;
    }
    u8 ready = loader->unk2d != 0;
    if (ready == 1)
    {
        object->func_slot1c(1, 0x80);
    }
    else
    {
        SkillGridChoice* choice = new (0) SkillGridChoice;
        if (choice == 0)
        {
            return 0;
        }
        choice->func_slot10(object->func_slot54(), 192.0f, 160.0f, 5);
        choice->func_slot40(object);
        D_001B643C->callbacks->controller->func_00263FD0(choice);
        D_001B643C->callbacks->controller->func_00263C70(choice);
    }
    return 2;
}

/**
 * @brief Refresh the mode-query cursor opacity for the active window.
 * @param object Mode-query window.
 */
static inline void refresh_query_cursor(Record00352B30* object)
{
    if (D_001B643C->callbacks->controller->func_00261150() == object)
    {
        s32 opacity = object->unk104 ? 128 : 0;
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = (float)opacity;
        cursor->unk3c = 1;
    }
    else
    {
        LibClass178600* cursor = object->cursor;
        cursor->unk28 = 0.0f;
        cursor->unk3c = 1;
    }
}
s32 func_00359870(SkillSecondarySelection* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    u16 code = object->selection->unk114;
    SkillQueueOwner* selected_owner = object->owner;
    selected_owner->selected = code;
    func_0035AF00(selected_owner, selected_owner->selected, 1);
    switch (code)
    {
    case 1:
    {
        func_003559F0(object->four_rows);
        SkillFourRowSelection* window = object->four_rows;
        for (s32 index = 0; index < 4; index++)
        {
            LibClass174EF0* item = static_cast<LibClass174EF0*>(func_0035CAE0(reinterpret_cast<SkillList*>(&window->unk2c), index)->value);
            if (index == window->selection->unk114)
            {
                item->unk94 = 0x288080;
                item->unk3c = 1;
                LibBounds4C69B0* metrics = static_cast<LibBounds4C69B0*>(func_4C69B0(item));
                func_0023B9B0(window->cursor, (s16)index, metrics->unk08);
            }
            else
            {
                item->unk94 = 0x808080;
                item->unk3c = 1;
            }
        }
        func_003558B0(object->four_rows, 1, 1);
        func_00353570(object->status_rows, 0, 0);
        Record00352B30* query = object->mode_query;
        query->active = 0;
        query->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(query->attachment), 0);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        object->owner->func_00263C70(object->four_rows);
        break;
    }
    case 0:
    {
        func_00354190(object->status_rows);
        func_003538F0(object->status_rows);
        func_00353720(object->status_rows);
        FieldClass153E30* controller = D_001B643C->callbacks->controller;
        Record003538F0* window = object->status_rows;
        SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(controller);
        StatusOwner003580D0* status = owner->status;
        if (owner != 0 && status != 0)
        {
            s32 index = window->selection->unk114;
            if (window->keys[index] == 0x178A)
            {
                func_003580D0(status, -1, -1, -1);
            }
            else
            {
                func_003580D0(status, window->first_values[index], window->second_values[index], window->third_values[index]);
            }
        }
        func_00353570(object->status_rows, 1, 1);
        func_003558B0(object->four_rows, 0, 0);
        Record00352B30* query = object->mode_query;
        query->active = 0;
        query->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(query->attachment), 0);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        object->owner->func_00263C70(object->status_rows);
        break;
    }
    case 2:
    {
        object->owner->func_00263C70(object->mode_query);
        func_00352C00(object->mode_query);
        if (object->owner->paired != 0)
        {
            func_0034B3F0(object->owner->paired);
        }
        func_00351BE0(object->mode_query);
        Record00352B30* query = object->mode_query;
        if (query->attachment != 0)
        {
            if (query->unk104 != 0)
            {
                LibObject178660* display = query->attachment->unk10;
                if (display != 0)
                {
                    display->unkab = 1;
                }
            }
            else
            {
                LibObject178660* display = query->attachment->unk10;
                if (display != 0)
                {
                    display->unkab = 0;
                }
            }
        }
        query = object->mode_query;
        query->active = 1;
        func_00351BE0(query);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 1);
        func_00353570(object->status_rows, 0, 0);
        func_003558B0(object->four_rows, 0, 0);
        FieldClass153E30* controller = D_001B643C->callbacks->controller;
        query = object->mode_query;
        SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(controller);
        FieldClass15AE70* window = owner->window;
        if (query->unk104 > 0)
        {
            window->func_slot60(query->modes[query->selection->unk114] + 0x1AA3);
        }
        else
        {
            window->func_slot60(0x1795);
        }
        break;
    }
    }
    FieldObject23CE80* selection = reinterpret_cast<FieldObject23CE80*>(object->selection);
    selection->unkE0 = 64.0f;
    selection->unkAE = 1;
    return 1;
}

void func_00359D80(SkillSecondarySelection* object)
{
    if (object->func_slot28())
    {
        return;
    }
    if (object->selection->func_0023CDB0(1) == 1)
    {
        return;
    }
    object->previous = object->code;
    object->code = object->selection->unk114;
    if (object->previous == object->code)
    {
        return;
    }
    object->direction = 1;
    object->state = 1;
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    func_0035AF00(owner, object->code, 1);
}

void func_00359E30(SkillSecondarySelection* object)
{
    if (object->func_slot28())
    {
        return;
    }
    if (object->selection->func_0023CDB0(0) == 1)
    {
        return;
    }
    object->previous = object->code;
    object->code = object->selection->unk114;
    if (object->previous == object->code)
    {
        return;
    }
    object->direction = 0;
    object->state = 1;
    SkillQueueOwner* owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    func_0035AF00(owner, object->code, 1);
}

s32 func_00359EE0(SkillSecondarySelection* object, u32 associated)
{
    object->FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 8);
    object->owner = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller);
    LibClass178630* panel = new (0) LibClass178630;
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    LibObject178750* third = new (0) LibObject178750;
    object->selection = new (0) FieldObject23CEA0;
    if (object->owner == 0 || panel == 0 || first == 0 || second == 0 || third == 0 || object->selection == 0)
    {
        return 0;
    }
    func_004C5A80(panel, 0, 0.0f, 0.0f, 200.0f, 104.0f, 88.0f);
    func_0035CBB0(reinterpret_cast<SkillList*>(&object->unk14), panel);
    func_004C6190(object->unk10, panel);
    second->func_004C7FE0(70.0f, 13.0f, 0.0f, 0.0f, (s32)associated, 0x1777, 0);
    first->func_004C7FE0(70.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x1776, 0);
    third->func_004C7FE0(70.0f, 67.0f, 0.0f, 0.0f, (s32)associated, 0x1778, 0);
    func_004C6190(object->unk10, second);
    func_0035C9D0(reinterpret_cast<SkillList*>(&object->unk2c), second);
    func_004C6190(object->unk10, first);
    func_0035C9D0(reinterpret_cast<SkillList*>(&object->unk2c), first);
    func_004C6190(object->unk10, third);
    func_0035C9D0(reinterpret_cast<SkillList*>(&object->unk2c), third);
    second->unk94 = 0x288080;
    second->unk3c = 1;
    ItemCreationOptionResourceDisplay* icon_first = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* icon_second = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* icon_third = new (0) ItemCreationOptionResourceDisplay;
    void* resource = func_002D3D80(D_001B643C->resources, 0);
    icon_first->unkcc = resource;
    icon_second->unkcc = resource;
    icon_third->unkcc = resource;
    icon_first->unkd0 = 0;
    icon_second->unkd0 = 0;
    icon_third->unkd0 = 0;
    icon_second->func_002D6440(func_002D3CC0(D_001B643C->resources, 0x12), 32.0f, 11.0f);
    icon_first->func_002D6440(func_002D3CC0(D_001B643C->resources, 0x14), 32.0f, 38.0f);
    icon_third->func_002D6440(func_002D3CC0(D_001B643C->resources, 0x15), 32.0f, 65.0f);
    func_004C6190(object->unk10, icon_first);
    func_004C6190(object->unk10, icon_second);
    func_004C6190(object->unk10, icon_third);
    LibBounds4C69B0* metrics = func_004C69B0(first);
    FieldObject23BE00* cursor = static_cast<FieldObject23BE00*>(::operator new(0x6C, 0));
    if (cursor != 0)
    {
        cursor = func_0023BE00(cursor);
    }
    object->cursor = cursor;
    object->cursor->func_0023BB20(70.0f, 13.0f, metrics->unk08, 1.0f, object->selection, 0x288080);
    func_004C6190(object->unk10, object->cursor);
    func_0035C440(reinterpret_cast<SkillList*>(&object->unk8c), object->cursor);
    object->selection->func_0023CE80(1, 3);
    object->selection->func_0023CE60(0.0f, 27.0f);
    object->selection->unkF2 = 0;
    object->selection->unk119 = 1;
    object->selection->func_0023CF50(0, 56.0f, 85.0f);
    func_0035C4D0(reinterpret_cast<SkillList*>(&object->unk74), object->selection);
    return 1;
}

SkillSecondarySelection::~SkillSecondarySelection()
{
}

void func_0035A560(Record0035A560* record)
{
    LibObject178750* display = record->display;
    float x = display->unk18.unk00;
    float y = display->unk18.unk04;
    float z = display->unk18.unk08;
    float w = display->unk18.unk0c;
    if (record->active == 0)
    {
        display->unk18.unk00 = record->first_x;
        display->unk18.unk04 = y;
        display->unk18.unk08 = z;
        display->unk18.unk0c = w;
        display->unk3c = 1;
        record->counter++;
        if (!((float)record->counter <= 120.0f))
        {
            record->counter = 0;
            record->active = 1;
        }
        return;
    }
    {
        float origin = record->origin;
        x -= 108.0f * D_001B6690;
        if (x < origin - (float)record->limit)
        {
            x = 2.0f + (origin + record->offset);
        }
        display->unk18.unk00 = x;
        display->unk18.unk04 = y;
        display->unk18.unk08 = z;
        display->unk18.unk0c = w;
        display->unk3c = 1;
    }
}

void func_0035A650(Record0035A560* record, s32 key)
{
    if (key >= 6001 && key <= 6005)
    {
        record->active = 0;
        record->counter = 0;
        u32 source = record->func_slot54();
        func_4C6DF0(record->display, source, key, 0);
        LibBounds4C69B0* extent = func_004C69B0(record->display);
        record->limit = (s32)extent->unk08 + 6;
    }
}

/**
 * @brief Add a horizontal offset to a display origin.
 * @param origin Display origin.
 * @param offset Horizontal offset.
 * @return Shifted horizontal coordinate.
 */
static inline float shifted_position(const float& origin, float offset)
{
    return origin + offset;
}
s32 func_0035A6E0(Record0035A560* object, u32 associated)
{
    object->FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 19);
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    s32 mode = object->mode;
    if (mode == 1)
    {
        first->func_004C7FE0(16.0f, 5.0f, 0.0f, 0.0f, (s32)associated, 0x17C7, 0);
        second->func_004C7FE0(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x17C8, 0);
    }
    else if (mode == 2)
    {
        first->func_004C7FE0(16.0f, 5.0f, 0.0f, 0.0f, (s32)associated, 0x1770, 0);
        second->func_004C7FE0(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x1794, 0);
        first->set_scale(1.1f, 1.1f);
    }
    else
    {
        first->func_004C7FE0(16.0f, 5.0f, 0.0f, 0.0f, (s32)associated, 0x1770, 0);
        second->func_004C7FE0(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x1794, 0);
    }
    func_004C6190(object->unk10, first);
    func_0035C9D0(reinterpret_cast<SkillList*>(&object->unk2c), first);
    second->set_scale(0.65f, 0.65f);
    func_004C6190(object->unk10, second);
    func_0035C9D0(reinterpret_cast<SkillList*>(&object->unk2c), second);
    object->display = new (0) LibObject178750;
    ItemCreationClass1746A0* first_frame = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* second_frame = new (0) ItemCreationClass1746A0;
    if (object->display == 0 || first_frame == 0 || second_frame == 0)
    {
        return 0;
    }
    object->extent = func_004C69B0(first)->unk08;
    object->origin = 18.0f + object->extent;
    object->offset = 640.0f - (16.0f + shifted_position(object->origin, 32.0f));
    object->first_x = 24.0f + object->extent;
    func_44B570(first_frame, object->origin, 0.0f, object->offset, 56.0f);
    func_004C6190(object->unk10, first_frame);
    func_0035CB20(reinterpret_cast<SkillList*>(&object->unk20), first_frame);
    object->display->func_004C7FE0(object->first_x, 6.0f, 0.0f, 0.0f, (s32)associated, 0x1771, 0);
    func_004C6190(object->unk10, object->display);
    func_0035C9D0(reinterpret_cast<SkillList*>(&object->unk2c), object->display);
    func_44B510(second_frame, 1);
    func_004C6190(object->unk10, second_frame);
    func_0035CB20(reinterpret_cast<SkillList*>(&object->unk20), second_frame);
    object->func_slot60(0x1771);
    return 1;
}

RecordWithMethods* func_0035AB60(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183970;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

u8* func_0035ABC0(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183970;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u8*)(object + 0xB0) = 0xFF;
    *(u8*)(object + 0xB4) = 0;
    *(u16*)(object + 0xB2) = 0;
    *(float*)(object + 0xB8) = -96.0f;
    *(u32*)(object + 0xBC) = 0;
    *(u32*)(object + 0xC0) = 0;
    *(u32*)(object + 0xC4) = 0;
    *(u32*)(object + 0xC8) = 0;
    *(u32*)(object + 0xCC) = 0;
    *(u32*)(object + 0xD0) = 0;
    *(u32*)(object + 0xD4) = 1;
    return object;
}

void SkillResourceWindow::func_slot5c()
{
}

s32 func_0035AC50(FieldClass15AE70* object, u32 associated)
{
    object->FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 20);
    ItemCreationOptionResourceDisplay* first = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* second = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* third = new (0) ItemCreationOptionResourceDisplay;
    void* resource = func_002D3D80(D_001B643C->resources, 11);
    first->unkcc = resource;
    second->unkcc = resource;
    third->unkcc = resource;
    first->unkd0 = 11;
    second->unkd0 = 11;
    third->unkd0 = 11;
    first->func_002D6440(func_002D3CC0(D_001B643C->resources, 5), 0.0f, 0.0f);
    second->func_002D6440(func_002D3CC0(D_001B643C->resources, 6), 256.0f, 0.0f);
    third->func_002D6440(func_002D3CC0(D_001B643C->resources, 7), 512.0f, 0.0f);
    func_004C6190(object->unk10, first);
    func_004C6190(object->unk10, second);
    func_004C6190(object->unk10, third);
    return 1;
}

SkillResourceWindow::~SkillResourceWindow()
{
}

/**
 * @brief Set the primary status label and value visibility.
 * @param object Status window.
 * @param visible Display visibility byte.
 */
static inline void status_primary_group(StatusOwner003580D0* object, u8 visible)
{
    object->first_label->unk3f = visible;
    object->third_value->unk3f = visible;
}
/**
 * @brief Set detailed status visibility and hide its fallback label.
 * @param object Status window.
 * @param visible Display visibility byte.
 */
static inline void status_detail_group(StatusOwner003580D0* object, u8 visible)
{
    object->second_label->unk3f = visible;
    object->third_label->unk3f = visible;
    object->fourth_label->unk3f = visible;
    object->items[0]->unk3f = visible;
    object->items[1]->unk3f = visible;
    object->items[2]->unk3f = visible;
    object->fallback_label->unk3f = 0;
    object->fifth_label->unk3f = visible;
    object->first_value->unk3f = visible;
    object->sixth_label->unk3f = visible;
    object->second_value->unk3f = visible;
}
void func_0035AF00(SkillQueueOwner* owner, s32 code, u8 enabled)
{
    switch (code)
    {
    case 1:
    {
        StatusOwner003580D0* status = owner->status;
        status_primary_group(status, 1);
        FieldRecordSelection* selection = status->selection;
        StatusDetail* detail = &static_cast<StatusDetail*>(selection->unk04)[selection->current];
        u32 key = detail->key;
        s32 value = (detail->checksum != (((detail->second + key) ^ detail->first) ^ key)) ? 0 : (detail->first ^ 0x7E93);
        LibObject174F20* item = status->third_value;
        item->numeric_value = value;
        item->unk3c = 1;
        status_detail_group(owner->status, 0);
        Record00352B30* query = owner->mode_query;
        query->active = 0;
        query->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(query->attachment), 0);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        func_00353570(owner->status_rows, 0, 0);
        func_003558B0(owner->four_rows, 1, 0);
        func_003559F0(owner->four_rows);
        break;
    }
    case 0:
    {
        s32 value = func_003534C0(owner->status_rows, 1);
        StatusOwner003580D0* status = owner->status;
        LibObject174F20* item = status->first_value;
        if (item != 0)
        {
            if (value < 0)
            {
                value = 0;
            }
            item->numeric_value = value;
            item->unk3c = 1;
        }
        FieldRecordSelection* selection = status->selection;
        if (selection != 0)
        {
            StatusDetail* detail = &static_cast<StatusDetail*>(selection->unk04)[selection->current];
            if (detail != 0)
            {
                u32 key = detail->key;
                s32 value;
                if (detail->checksum != (((detail->second + key) ^ detail->first) ^ key))
                {
                    value = 0;
                }
                else
                {
                    value = detail->second ^ 0x7E93;
                }
                LibObject174F20* item = status->second_value;
                item->numeric_value = value;
                item->unk3c = 1;
            }
        }
        status_primary_group(owner->status, 0);
        status_detail_group(owner->status, 1);
        Record00352B30* query = owner->mode_query;
        query->active = 0;
        query->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(query->attachment), 0);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        func_003558B0(owner->four_rows, 0, 0);
        func_00353570(owner->status_rows, 1, 0);
        break;
    }
    case 2:
    {
        status_detail_group(owner->status, 0);
        status_primary_group(owner->status, 0);
        func_00353570(owner->status_rows, 0, 0);
        func_003558B0(owner->four_rows, 0, 0);
        Record00352B30* query = owner->mode_query;
        query->active = 1;
        func_00351BE0(query);
        refresh_query_cursor(query);
        func_0023CEA0(query->selection, 0);
        func_00352C00(owner->mode_query);
        break;
    }
    }
    if (enabled == 1)
    {
        FieldClass15AE70* window = owner->window;
        if (window != 0)
        {
            window->func_slot60(0x1795);
        }
    }
    func_003580D0(owner->status, -1, -1, -1);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035B440);

void func_0035B4B0(SkillQueueOwner* record)
{
    FieldClass153E30* entry = record;
    func_0011ED90(D_001B65F4, entry);
}

s32 func_0035B4E0(SkillQueueOwner* owner)
{
    SkillResourceWindow* resource = new (0) SkillResourceWindow;
    Record0035A560* message = static_cast<Record0035A560*>(::operator new(0xD8, 0));
    if (message != 0)
    {
        message = reinterpret_cast<Record0035A560*>(func_0035ABC0(reinterpret_cast<u8*>(message)));
    }
    resource->func_slotf4(owner->associated);
    owner->FieldClass153E30::func_00263FD0(resource);
    resource->func_slot40(0);
    message->mode = owner->kind;
    message->func_slotf4(owner->associated);
    owner->FieldClass153E30::func_00263FD0(message);
    owner->unk24 = message;
    message->func_slot40(resource);
    if (owner->kind == 1)
    {
        SkillOwnerListWindow* list = static_cast<SkillOwnerListWindow*>(::operator new(0x120, 0));
        if (list != 0)
        {
            list = reinterpret_cast<SkillOwnerListWindow*>(func_00364670(reinterpret_cast<u8*>(list)));
        }
        owner->list_window = list;
        SkillProtectedDisplay* primary = static_cast<SkillProtectedDisplay*>(::operator new(0xC0, 0));
        if (primary != 0)
        {
            primary = reinterpret_cast<SkillProtectedDisplay*>(func_00363610(reinterpret_cast<u8*>(primary)));
        }
        owner->primary = primary;
        Record003619C0* rows = static_cast<Record003619C0*>(::operator new(0x1B8, 0));
        if (rows != 0)
        {
            rows = reinterpret_cast<Record003619C0*>(func_00362F70(reinterpret_cast<u8*>(rows)));
        }
        owner->primary_rows = rows;
        owner->options = new (0) SkillOptionsWindow;
        owner->list_window->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->list_window);
        owner->list_window->func_slot40(owner->primary);
        owner->primary->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->primary);
        owner->primary->func_slot40(owner->primary_rows);
        owner->primary_rows->func_slot40(owner->list_window);
        owner->primary_rows->func_slot48(owner->options);
        owner->primary_rows->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->primary_rows);
        owner->options->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->options);
        owner->options->func_slot40(owner->primary_rows);
        message->func_slot60(0x1775);
        owner->unk20 = owner->primary_rows;
    }
    else if (owner->kind == 2)
    {
        owner->secondary = new (0) SkillSecondarySelection;
        owner->status = new (0) StatusOwner003580D0(owner);
        owner->status_message = new (0) SkillStatusMessageWindow;
        SkillFourRowSelection* four = static_cast<SkillFourRowSelection*>(::operator new(0x104, 0));
        if (four != 0)
        {
            four = reinterpret_cast<SkillFourRowSelection*>(func_00357EE0(reinterpret_cast<u8*>(four)));
        }
        owner->four_rows = four;
        owner->status_rows = new (0) Record003538F0(owner);
        Record00352B30* query = static_cast<Record00352B30*>(::operator new(0x118, 0));
        if (query != 0)
        {
            query = reinterpret_cast<Record00352B30*>(func_003533E0(reinterpret_cast<u8*>(query)));
        }
        owner->mode_query = query;
        owner->mode_message = new (0) SkillModeMessageWindow;
        owner->mode_window = new (0) SkillModeSelection(owner);
        owner->paired = new (0) SkillDualSelection;
        owner->text_window = new (0) SkillTextReceiver;
        owner->window = new (0) SkillComparisonDisplay(owner);
        owner->mode_query->parent = owner;
        owner->paired->owner = owner;
        owner->secondary->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->secondary);
        owner->secondary->func_slot40(message);
        owner->secondary->status = owner->status;
        owner->secondary->four_rows = owner->four_rows;
        owner->secondary->status_rows = owner->status_rows;
        owner->secondary->mode_query = owner->mode_query;
        owner->status->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->status);
        owner->status->func_slot40(owner->secondary);
        owner->status->four_rows = owner->four_rows;
        owner->status->status_rows = owner->status_rows;
        owner->status->mode_query = owner->mode_query;
        owner->status->mode_window = owner->mode_window;
        owner->status->paired = owner->paired;
        owner->four_rows->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->four_rows);
        owner->four_rows->func_slot40(owner->secondary);
        owner->four_rows->message = owner->window;
        owner->four_rows->status = owner->status;
        owner->status_rows->mode_records = owner->mode_records;
        owner->status_rows->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->status_rows);
        owner->status_rows->func_slot40(owner->secondary);
        owner->status_rows->func_slot48(owner->mode_window);
        reinterpret_cast<SkillComparisonDisplay*>(owner->window)->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->window);
        owner->window->func_slot40(owner->status_message);
        owner->text_window->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->text_window);
        owner->text_window->func_slot40(owner->mode_query);
        LibObject178660* attachment = owner->text_window->unk10;
        if (attachment != 0)
        {
            attachment->LibClass174610::unkab = 0;
        }
        owner->mode_query->func_slot40(owner->secondary);
        owner->mode_query->func_slot48(owner->paired);
        owner->mode_query->attachment = owner->text_window;
        owner->mode_query->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->mode_query);
        owner->status_message->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->status_message);
        owner->status_message->func_slot40(owner->status);
        owner->mode_message->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->mode_message);
        owner->mode_message->func_slot40(owner->mode_window);
        owner->mode_window->mode_records = owner->mode_records;
        owner->mode_window->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->mode_window);
        owner->mode_window->func_slot40(owner->status_rows);
        owner->mode_window->func_slot48(owner->status);
        owner->paired->func_slotf4(owner->associated);
        owner->FieldClass153E30::func_00263FD0(owner->paired);
        owner->paired->func_slot40(owner->mode_query);
        func_00353570(owner->status_rows, 1, 0);
        func_00354190(owner->status_rows);
        Record00352B30* mode_query = owner->mode_query;
        mode_query->active = 0;
        mode_query->func_slot18(0, 2);
        func_00349920(reinterpret_cast<u8*>(mode_query->attachment), 0);
        refresh_query_cursor(mode_query);
        func_0023CEA0(mode_query->selection, 0);
        func_003558B0(owner->four_rows, 0, 0);
        func_00351360(owner->mode_window, 0, 0);
        func_00349F30(owner->paired, 2);
        owner->unk20 = owner->secondary;
    }
    owner->state = 6;
    owner->active = 1;
    return 1;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035BD90);

/**
 * @brief Allocate and initialize the record's selection state.
 * @param record Owner of the selection state.
 * @return One when initialization succeeds, or zero on failure.
 */
s32 func_0035BE50(SkillQueueOwner* record)
{
    FieldRecordSelection* selection = (FieldRecordSelection*)::operator new(24, 0);
    if (selection != 0)
    {
        selection = func_0028E4D0(selection);
    }
    record->mode_records = selection;
    if (record->mode_records == 0)
    {
        return 0;
    }
    return (u8)func_0028E3D0(record->mode_records) != 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035BEC0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035BF70);

void func_0035C030(void* object)
{
}

void func_0035C040(void* object)
{
}

RecordWithMethods* func_0035C050(RecordWithMethods* record, s16 flag)
{
    return release_record182f50(record, flag);
}

RecordWithMethods* func_0035C0A0(RecordWithMethods* record, s16 flag)
{
    return release_record182f60(record, flag);
}

s32 func_0035C100(void* object)
{
    return 3;
}

void func_0035C110(void* object)
{
}

void func_0035C120(void* object)
{
}

/**
 * @brief Store a 128-bit value at offset 0x20 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C130(LibClass171EF0* object, const unsigned __int128* value)
{
    object->unk50 = 1;
    object->unk20.packed = *value;
}

/**
 * @brief Store a 128-bit value at offset 0x20 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C150(LibClass171EF0* object, const unsigned __int128* value)
{
    object->unk50 = 1;
    object->unk20.packed = *value;
}

/**
 * @brief Store 3 float values at offset 0x20 and set the byte at 0x50. Set the fourth float to 1.0f.
 * @param object Receiver storage.
 * @param x Float value to store.
 * @param y Float value to store.
 * @param z Float value to store.
 */
void func_0035C170(LibClass171EF0* object, float x, float y, float z)
{
    object->unk50 = 1;
    object->unk20.components[0] = x;
    object->unk20.components[1] = y;
    object->unk20.components[2] = z;
    object->unk20.components[3] = 1.0f;
}

/**
 * @brief Store 4 float values at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param x Float value to store.
 * @param y Float value to store.
 * @param z Float value to store.
 * @param w Float value to store.
 */
void func_0035C190(LibClass171EF0* object, float x, float y, float z, float w)
{
    object->unk50 = 1;
    object->unk30.components[0] = x;
    object->unk30.components[1] = y;
    object->unk30.components[2] = z;
    object->unk30.components[3] = w;
}

/**
 * @brief Store a 128-bit value at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C1B0(LibClass171EF0* object, const unsigned __int128* value)
{
    object->unk50 = 1;
    object->unk30.packed = *value;
}

/**
 * @brief Store a 128-bit value at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C1D0(LibClass171EF0* object, const unsigned __int128* value)
{
    object->unk50 = 1;
    object->unk30.packed = *value;
}

/**
 * @brief Update the vector at offset 0x30 and mark the receiver changed.
 * @param object Vector receiver.
 * @param value Vector components.
 */
void func_0035C1F0(LibClass171EF0* object, const SkillVector4* value)
{
    object->unk50 = 1;
    func_4CE4C0(&object->unk30, value);
}

/**
 * @brief Update the vector at offset 0x30 and mark the receiver changed.
 * @param object Vector receiver.
 * @param value Vector components.
 */
void func_0035C220(LibClass171EF0* object, const SkillVector4* value)
{
    object->unk50 = 1;
    func_4CE4C0(&object->unk30, value);
}

/**
 * @brief Update the vector at offset 0x30 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param x First float component.
 * @param y Second float component.
 * @param z Third float component.
 */
void func_0035C250(LibClass171EF0* object, float x, float y, float z)
{
    object->unk50 = 1;
    SkillVector4 value(x, y, z, 1.0f);
    func_4CE4C0(&object->unk30, &value);
}

/**
 * @brief Store a 128-bit value at offset 0x40 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C290(LibClass171EF0* object, const unsigned __int128* value)
{
    object->unk50 = 1;
    object->unk40.packed = *value;
}

/**
 * @brief Store a 128-bit value at offset 0x40 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C2B0(LibClass171EF0* object, const unsigned __int128* value)
{
    object->unk50 = 1;
    object->unk40.packed = *value;
}

/**
 * @brief Store 3 float values at offset 0x40 and set the byte at 0x50.
 * @param object Receiver storage.
 * @param x Float value to store.
 * @param y Float value to store.
 * @param z Float value to store.
 */
void func_0035C2D0(LibClass171EF0* object, float x, float y, float z)
{
    object->unk50 = 1;
    object->unk40.components[0] = x;
    object->unk40.components[1] = y;
    object->unk40.components[2] = z;
}

s32 func_0035C2F0(void* object)
{
    return 0;
}

bool func_0035C300(float value)
{
    return value < 0.0f;
}

u8* func_0035C320(void)
{
    return D_50CD30;
}

s32 func_0035C330(void* object)
{
    return 0;
}

void func_0035C340(void* object)
{
}

void func_0035C350(u8* object, u32 value)
{
    *(u32*)(object + 0x24) = value;
}

/**
 * @brief Write the 8-bit field at offset 0x28.
 * @param object Receiver storage.
 * @param value Value to store.
 */
void func_0035C360(FieldClass153E30* object, u8 value)
{
    object->unk28 = value;
}

/**
 * @brief Read the signed 8-bit field at offset 0x28.
 * @param object Receiver storage.
 * @return Field value.
 */
s8 func_0035C370(FieldClass153E30* object)
{
    return object->unk28;
}

s32 func_0035C380(void* object)
{
    return 0;
}

s32 func_0035C390(void* object)
{
    return 0;
}

void func_0035C3A0(void* object)
{
}

void func_0035C3B0(void* object)
{
}

void func_0035C3C0(void* object)
{
}

void func_0035C3D0(void* object)
{
}

s32 func_0035C3E0(void* object)
{
    return 0;
}

s32 func_0035C3F0(void* object)
{
    return 0;
}

s32 func_0035C400(void* object)
{
    return 0;
}

s32 func_0035C410(void* object)
{
    return 4;
}

u8 func_0035C420(u8* object)
{
    return object[0x40];
}

u32 func_0035C430(u8* object)
{
    return *(u32*)(object + 0x3C);
}

void func_0035C440(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        SkillListNode* tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

void func_0035C4D0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035C560(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035C5F0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

SkillList183C48::SkillList183C48()
{
    head = new (0) SkillListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

SkillList183C48::~SkillList183C48()
{
    func_0035C810(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_0035C780(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035C810(SkillList183C48* record)
{
    SkillListNode* node = record->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        SkillListNode* next = node->next;
        delete node;
        node = next;
    }
    record->head->next = 0;
    record->count = 0;
}

SkillListNode* func_0035C890(SkillList* list, s32 index)
{
    SkillListNode* node = list->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

SkillList183C38::SkillList183C38()
{
    head = new (0) SkillListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

SkillList183C38::~SkillList183C38()
{
    func_0035CA60(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_0035C9D0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035CA60(SkillList183C38* record)
{
    SkillListNode* node = record->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        SkillListNode* next = node->next;
        delete node;
        node = next;
    }
    record->head->next = 0;
    record->count = 0;
}

SkillListNode* func_0035CAE0(SkillList* list, s32 index)
{
    SkillListNode* node = list->head->next;
    s32 i;
    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void func_0035CB20(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_0035CBB0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CC40);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CC50);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CC60);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CC70);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CC80);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CC90);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CCA0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CCB0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CCC0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CCD0);

/** @brief Color the choice text entries for the selected index. @param selected Selected grid index. */
void SkillGridChoice::func_slotf4(s16 selected)
{
    s32 index = 0;
    SkillListNode* node = reinterpret_cast<SkillListNode*>(unk2c.unk00->unk04);
    while (node != 0)
    {
        LibObject178750* item = static_cast<LibObject178750*>(node->value);
        if (index == selected)
        {
            item->unk94 = 0x288080;
            item->unk3c = 1;
        }
        else
        {
            item->unk94 = 0x808080;
            item->unk3c = 1;
        }
        node = node->next;
        index++;
    }
}

void func_0035CD50(SkillGridChoice* object)
{
    if (D_001B643C->callbacks->controller->func_00261150() == object)
    {
        object->func_slotf4(object->selection->unk114);
    }
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CDB0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035CDF0);

s32 func_0035CE30(FieldClass15AE70* object)
{
    func_002CE530(object, 0, 0x7F);
    FieldClass153E30* controller = D_001B643C->callbacks->controller;
    controller->func_00263C70(object->func_slot44());
    func_002CFE10(D_001B643C->callbacks, object);
    return 2;
}

s32 func_0035CEB0(SkillGridChoice* object)
{
    u8 result = 0;
    object->selected = object->selection->unk114;
    if (object->selected == 0)
    {
        object->func_slot1c(0xFF, 0x80);
    }
    else
    {
        result = object->func_slotb4();
    }
    return result == 0 ? 1 : 2;
}

s32 SkillGridChoice::func_slot10(u32 associated, float x, float y, s32 code)
{
    FieldClass15AE70::func_slot10(associated, x, y, code);
    LibClass178630* panel = new (0) LibClass178630;
    if (panel == 0)
    {
        return 0;
    }
    func_004C5A80(panel, 1, 0.0f, 0.0f, 256.0f, 160.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_0035CBB0(reinterpret_cast<SkillList*>(&unk14), panel);
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    LibObject178750* title = new (0) LibObject178750;
    if (first == 0 || second == 0 || title == 0)
    {
        return 0;
    }
    func_004C7FE0(first, static_cast<s32>(associated), 0x7E8, 0, 92.0f, 84.0f, 0.0f, 0.0f);
    func_004C7FE0(second, static_cast<s32>(associated), 0x7E9, 0, 92.0f, 120.0f, 0.0f, 0.0f);
    func_004C7FE0(title, static_cast<s32>(associated), 0x1793, 0, 16.0f, 16.0f, 0.0f, 0.0f);
    func_004C6190(unk10, first);
    func_004C6190(unk10, second);
    func_004C6190(unk10, title);
    func_0035C9D0(reinterpret_cast<SkillList*>(&unk2c), first);
    func_0035C9D0(reinterpret_cast<SkillList*>(&unk2c), second);
    func_0035C9D0(reinterpret_cast<SkillList*>(&unk2c), title);
    selection = new (0) FieldObject23CEA0;
    if (selection == 0)
    {
        return 0;
    }
    selection->func_0023CE80(1, 2);
    selection->func_0023CE60(0.0f, 36.0f);
    selection->unkF2 = 0;
    selection->func_0023CF50(1, x + 92.0f, 16.0f + (y + 84.0f));
    func_0035C4D0(reinterpret_cast<SkillList*>(&unk74), selection);
    return 1;
}

SkillGridChoice::~SkillGridChoice()
{
}

inline SkillGridChoice::SkillGridChoice()
{
    selection = 0;
    selected = -1;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035D340);

s32 func_0035D3E0(Record0035D3E0* record, s32 arg1, s32 arg2, void* arg3, float first, float second, float third)
{
    record->unk6c = 0x6006;
    record->unk20 = 0;
    record->unk24 = 0;
    record->unk28 = 0;
    record->unk2c = 1.0f;
    func_44B110(record, arg1, arg2, arg3, third, 0);
    record->unkb4 = 0;
    record->unkb8 = 0;
    return 1;
}

void func_0035D440(void* object)
{
    func_4D00B0(object);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035D460);

Record0035D4A0* func_0035D4A0(Record0035D4A0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183DB0;
        record->secondary_methods = D_183E24;
        record->nested.methods = D_183E3C;
        release_record183e50(&record->nested, 0);
        func_002BC280(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035D540);

void func_0035DDE0(Record0035DDE0* record)
{
    PacketBuffer0035DDE0* buffer = record->buffer;
    if (buffer != 0)
    {
        buffer->cursor = buffer->base + 64;
        buffer->unk0c = buffer->cursor;
        buffer->unk15 = 0;
        func_11F140(buffer, D_4ED330[0]);
        func_0035D540(record);
    }
}

Record0035DE40* func_0035DE40(Record0035DE40* record, s16 flag)
{
    return release_record183e50(record, flag);
}

/** @brief Decode the first preview value after validating its protected check. @param record Protected entry record. @return Decoded preview value, or zero
 * after corruption. */
static inline u32 protected_first_salt(SkillProtectedFlags* record)
{
    u32 first = record->value_first;
    u32 salt = record->salt_first;
    u32 key = protected_key(record);
    u32 encoded = record->encoded_first;
    u32 checksum = record->checksum_first;
    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded;
        s32 flag_salt = record->salt;
        if (record->checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded = ((flags ^ SKILL_FLAG_ENCODING_MASK) | 1) ^ SKILL_FLAG_ENCODING_MASK;
            s32 current_salt = record->salt;
            record->checksum = ((record->encoded + record->key) ^ current_salt) ^ record->key;
        }
        return 0;
    }
    return salt ^ SKILL_FLAG_ENCODING_MASK;
}

/** @brief Decode the second preview value after validating its protected check. @param record Protected entry record. @return Decoded preview value, or zero
 * after corruption. */
static inline u32 protected_second_salt(SkillProtectedFlags* record)
{
    u32 first = record->value_second;
    u32 salt = record->salt_second;
    u32 key = protected_key(record);
    u32 encoded = record->encoded_second;
    u32 checksum = record->checksum_second;
    if (checksum != ((first + salt) ^ encoded ^ key))
    {
        u32 flags = record->encoded;
        s32 flag_salt = record->salt;
        if (record->checksum == ((flags + key) ^ flag_salt ^ key))
        {
            record->encoded = ((flags ^ SKILL_FLAG_ENCODING_MASK) | 1) ^ SKILL_FLAG_ENCODING_MASK;
            s32 current_salt = record->salt;
            record->checksum = ((record->encoded + record->key) ^ current_salt) ^ record->key;
        }
        return 0;
    }
    return salt ^ SKILL_FLAG_ENCODING_MASK;
}

/**
 * @brief Decode the record flag word after validating its check word.
 * @param record Protected entry record.
 * @return Decoded flags, or five when the check word is invalid.
 */
static inline u32 protected_flags(SkillProtectedFlags* record)
{
    u32 key = record->key;
    u32 value = record->encoded;
    s32 salt = record->salt;
    if (record->checksum != ((value + key) ^ salt ^ key))
    {
        return 5;
    }
    return value ^ SKILL_FLAG_ENCODING_MASK;
}
void SkillOptionsWindow::func_slot5c()
{
    for (s32 row = 0; row < 8; ++row)
    {
        s16 index = row;
        if (records->slots[index] > 0)
        {
            SkillProtectedFlags* entry = &reinterpret_cast<SkillProtectedFlags*>(records->records)[index];
            u32 first_value = protected_first(entry);
            LibObject174F20* first_display = first_values[row];
            first_display->numeric_value = first_value;
            first_display->unk3c = 1;
            u32 second_value = protected_second(entry);
            LibObject174F20* second_display = second_values[row];
            second_display->numeric_value = second_value;
            second_display->unk3c = 1;
            if (row < 3)
            {
                u32 first_preview = protected_first_salt(entry);
                LibObject174F20* first_preview_display = first_previews[row];
                first_preview_display->numeric_value = first_preview;
                first_preview_display->unk3c = 1;
                u32 second_preview = protected_second_salt(entry);
                LibObject174F20* second_preview_display = second_previews[row];
                second_preview_display->numeric_value = second_preview;
                second_preview_display->unk3c = 1;
            }
            badges[row][0]->unk3f = protected_flags(entry) & 2;
            badges[row][1]->unk3f = protected_flags(entry) & 8;
            badges[row][2]->unk3f = protected_flags(entry) & 4;
            if (protected_flags(entry) & 5)
            {
                indicators[row]->unk3f = 0;
                badges[row][3]->unk3f = 1;
                if (row < 3)
                {
                    LibObject175140* label = labels[row];
                    label->unk94 = 0x505080;
                    label->unk3c = 1;
                }
            }
            else
            {
                indicators[row]->unk3f = 1;
                badges[row][3]->unk3f = 0;
                if (row < 3)
                {
                    LibObject175140* label = labels[row];
                    label->unk94 = 0x808080;
                    label->unk3c = 1;
                }
            }
        }
    }
}

void func_0035E2A0(Record0035E2A0* record)
{
    SkillCoordinateSelector* child = record->child;
    bool inactive = !child->LibMovementState::unk35;
    if (!inactive)
    {
        s32 index = child->selected - 1;
        if (index < 0)
        {
            index = 7;
        }
        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(child), index, 0);
    }
}

void func_0035E2F0(Record0035E2A0* record)
{
    SkillCoordinateSelector* child = record->child;
    bool inactive = !child->LibMovementState::unk35;
    if (!inactive)
    {
        s32 index = child->selected + 1;
        if (index >= 8)
        {
            index = 0;
        }
        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(child), index, 0);
    }
}

void func_0035E340(Record0035E2A0* record)
{
    SkillCoordinateSelector* child = record->child;
    bool inactive = !child->LibMovementState::unk35;
    if (!inactive)
    {
        s32 index = child->selected;
        switch (index)
        {
        case 0:
            index = 3;
            break;
        case 1:
            index = 5;
            break;
        case 2:
            index = 6;
            break;
        default:
            return;
        }
        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(child), index, 0);
    }
}

void func_0035E3C0(Record0035E2A0* record)
{
    SkillCoordinateSelector* child = record->child;
    bool inactive = !child->LibMovementState::unk35;
    if (!inactive)
    {
        s32 index = child->selected;
        switch (index)
        {
        case 3:
            index = 0;
            break;
        case 4:
            index = 1;
            break;
        case 5:
            index = 1;
            break;
        case 6:
            index = 2;
            break;
        case 7:
            index = 2;
            break;
        default:
            return;
        }
        func_0023B1D0(reinterpret_cast<FieldObject23B1D0*>(child), index, 0);
    }
}

/**
 * @brief Cancel the options window and restore its associated window.
 * @param object Options window.
 * @return Two after restoring the prior window.
 */
s32 func_0035E470(SkillOptionsWindow* object)
{
    object->child->unk3f = 0;
    object->unk10->LibClass174610::unkab = 0;
    SkillListNode* node = object->nested.head->next;
    while (node != 0)
    {
        static_cast<LibClass174610*>(node->value)->unkab = 0;
        node = node->next;
    }
    node = object->nested.head->next;
    while (node != 0)
    {
        static_cast<LibClass174610*>(node->value)->func_0044B100(1, 1, 1);
        node = node->next;
    }
    FieldClass15AE70* window = static_cast<FieldClass15AE70*>(object->func_slot44());
    window->func_slot64();
    D_001B643C->callbacks->controller->func_00263C70(window);
    SkillOwnerListWindow* list_window = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller)->list_window;
    if (list_window->first != 0)
    {
        list_window->first->unk3f = 1;
    }
    if (list_window->second != 0)
    {
        list_window->second->unk3f = 1;
    }
    static_cast<FieldClass15AE70*>(D_001B643C->callbacks->controller->func_00263C90())->func_slot60(0x1775);
    return 2;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035E5C0);

u32 func_0035FA20(SkillProtectedFlags* record, u32 flags)
{
    u32 key = record->key;
    u32 value = record->encoded;
    s32 salt = record->salt;
    u32 checksum = record->checksum;
    if (checksum != ((value + key) ^ salt ^ key))
    {
        return 5;
    }
    record->encoded = ((value ^ SKILL_FLAG_ENCODING_MASK) & flags) ^ SKILL_FLAG_ENCODING_MASK;
    s32 current_salt = record->salt;
    record->checksum = ((record->encoded + record->key) ^ current_salt) ^ record->key;
    return record->encoded ^ SKILL_FLAG_ENCODING_MASK;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_0035FAA0);

Record00361060* func_00361060(Record00361060* record, s16 flag)
{
    return release_record175030(record, flag);
}

Record003610F0* func_003610F0(Record003610F0* record, s16 flag)
{
    return release_record183da0(record, flag);
}

extern "C" void func_002CEA20(void* object);

void func_00361150(Record00364810* object)
{
    SkillListNode* node = object->nested.head->next;
    while (node != 0)
    {
        LibClass171EA0* display = (LibClass171EA0*)node->value;
        display->func_003EF740();
        node = node->next;
    }
    func_002CEA20(object);
}

void func_003611B0(Record003611B0* record)
{
    record->unk104 = 1;
    func_44B210(record);
    func_0011ED90(D_001B65F4, record);
}

SkillOptionsWindow::SkillOptionsWindow()
{
    records = 0;
    child = 0;
    x = 0.0f;
    y = 0.0f;
    unkb8 = 0;
    selected_kind = 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00361250);

/**
 * @brief Advance the paired display lists toward scroll position 16.
 * @param record Paired display list receiver.
 * @return Zero.
 */
s32 func_003619C0(Record003619C0* record)
{
    u8 inactive = !record->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    if (record->shift == 0)
    {
        s32 old_position = record->position;
        if (old_position < 16)
        {
            s32 offset;
            s32 i;
            record->position += 14;
            if (record->position > 16)
            {
                record->position = 16;
            }
            offset = ((record->position - old_position) / 2) * 33;
            for (i = 0; i < 30; i++)
            {
                ListItem0035CCE0* item = record->second[i];
                float y = (float)(s32)(item->position.y - (float)offset);
                item->position.y = y;
                item->unk3c = 1;
                item = record->first[i];
                item->position.y = y;
                item->unk3c = 1;
            }
        }
    }
    func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    return 0;
}

/**
 * @brief Move the paired display lists toward scroll position zero.
 * @param record Paired display list receiver.
 * @return Zero.
 */
s32 func_00361B90(Record003619C0* record)
{
    u8 inactive = !record->selection->unk35;
    if (inactive == 1)
    {
        return 0;
    }
    if (record->shift == 0)
    {
        s32 old_position = record->position;
        if (old_position > 0)
        {
            s32 offset;
            s32 i;
            record->position -= 14;
            if (record->position < 0)
            {
                record->position = 0;
            }
            offset = ((record->position - old_position) / 2) * 33;
            for (i = 0; i < 30; i++)
            {
                ListItem0035CCE0* item = record->second[i];
                float y = (float)(s32)(item->position.y - (float)offset);
                item->position.y = y;
                item->unk3c = 1;
                item = record->first[i];
                item->position.y = y;
                item->unk3c = 1;
            }
        }
    }
    func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    return 0;
}

void func_00361D60(Record003619C0* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (object->selected == 13)
    {
        if (object->position == 16)
        {
            return;
        }
        if (object->shift != 0)
        {
            return;
        }
        object->shift = -33;
        object->position += 2;
        object->selected = 12;
        move_active_grid(object->selection, 3);
    }
    else
    {
        object->selected++;
        move_active_grid(object->selection, 2);
    }
}

void func_00361E50(Record003619C0* object)
{
    u8 inactive = !object->selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (object->selected == 0)
    {
        if (object->position == 0)
        {
            return;
        }
        if (object->shift != 0)
        {
            return;
        }
        object->shift = 33;
        object->position -= 2;
        object->selected = 1;
        move_active_grid(object->selection, 2);
    }
    else
    {
        object->selected--;
        move_active_grid(object->selection, 3);
    }
}

void func_00361F30(Record003619C0* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (object->selected == 12 || object->selected == 13)
    {
        if (object->shift != 0)
        {
            return;
        }
        if (object->position == 16)
        {
            return;
        }
        object->shift = -33;
        object->position += 2;
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    }
    else
    {
        move_active_grid(selection, 1);
        object->selected += 2;
    }
}

void func_00362010(Record003619C0* object)
{
    FieldObject23CEA0* selection = object->selection;
    u8 inactive = !selection->unk35;
    if (inactive == 1)
    {
        return;
    }
    if (object->selected == 0 || object->selected == 1)
    {
        if (object->shift != 0)
        {
            return;
        }
        if (object->position == 0)
        {
            return;
        }
        object->shift = 33;
        object->position -= 2;
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    }
    else
    {
        move_active_grid(selection, 0);
        object->selected -= 2;
    }
}

s32 func_003620F0(Record003620F0* record)
{
    u8 inactive = !record->state->flag;
    Record00363740* primary;
    if (inactive == 1)
    {
        return 0;
    }
    primary = record->primary;
    if (primary == 0)
    {
        return 0;
    }
    if (record->mode->mode < 2)
    {
        return 0;
    }
    return func_00363740(primary, 1);
}

s32 func_00362170(Record003620F0* record)
{
    u8 inactive = !record->state->flag;
    Record00363740* primary;
    if (inactive == 1)
    {
        return 0;
    }
    primary = record->primary;
    if (primary == 0)
    {
        return 0;
    }
    if (record->mode->mode < 2)
    {
        return 0;
    }
    return func_00363740(primary, 0);
}

/**
 * @brief Set the row grid state to one.
 * @param object Row window.
 */
void func_003621F0(Record003619C0* object)
{
    func_0023CEA0(object->selection, 1);
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00362210);

s32 func_00362500(FieldClass15AE70* object)
{
    FieldSlotRecordOwner1C* loader = D_001B643C->loader;
    if (loader == 0)
    {
        return 0;
    }
    u8 ready = loader->unk2d != 0;
    if (ready == 1)
    {
        object->func_slot1c(1, 0x80);
    }
    else
    {
        SkillGridChoice* choice = new (0) SkillGridChoice;
        if (choice == 0)
        {
            return 0;
        }
        choice->func_slot10(object->func_slot54(), 192.0f, 160.0f, 5);
        choice->func_slot40(object);
        D_001B643C->callbacks->controller->func_00263FD0(choice);
        D_001B643C->callbacks->controller->func_00263C70(choice);
    }
    return 2;
}

s32 func_00362650(Record003619C0* object)
{
    u8 inactive = !object->selection->FieldClass151C50::unk35;
    if (inactive == 1)
    {
        return 0;
    }
    s32 kind, value, result_index, unused;
    FieldRecordSelection* records = object->records;
    s32 current = records->current;
    s32 selected = object->position + object->selected;
    SkillProtectedFlags* entry = &reinterpret_cast<SkillProtectedFlags*>(records->records)[current];
    StatusDetail* detail = &static_cast<StatusDetail*>(records->unk04)[current];
    if (func_408EA0(detail, records->slots[records->current], selected, &kind, &value, &result_index, &unused, 1) == 0 || selected == 29)
    {
        return 3;
    }
    if (kind != 3 && kind != 18 && kind != 19 && kind != 20 && kind != 27)
    {
        return 3;
    }
    if (protected_flags(entry) & 7)
    {
        return 3;
    }
    s32 required = 0;
    func_4095C0(kind, reinterpret_cast<FieldRecord*>(entry), detail, &required, 0, 0, 0, 0, 0, 0, 0);
    s32 available = (s32)protected_second(entry);
    if (available <= required)
    {
        return 3;
    }
    func_0023CEA0(object->selection, 0);
    SkillOwnerListWindow* list_window = static_cast<SkillQueueOwner*>(D_001B643C->callbacks->controller)->list_window;
    if (list_window->first != 0)
    {
        list_window->first->unk3f = 0;
    }
    if (list_window->second != 0)
    {
        list_window->second->unk3f = 0;
    }
    SkillOptionsWindow* options = static_cast<SkillOptionsWindow*>(object->func_slot4c());
    options->child->unk3f = 1;
    options->unk10->LibClass174610::unkab = 1;
    SkillListNode* node = options->nested.head->next;
    while (node != 0)
    {
        static_cast<LibClass174610*>(node->value)->unkab = 1;
        node = node->next;
    }
    node = options->nested.head->next;
    while (node != 0)
    {
        static_cast<LibClass174610*>(node->value)->func_0044B100(1, 1, 1);
        node = node->next;
    }
    s32 option_index = result_index;
    options->selected_kind = kind;
    options->selected_index = option_index;
    D_001B643C->callbacks->controller->func_00263C70(options);
    static_cast<FieldClass15AE70*>(D_001B643C->callbacks->controller->func_00263C90())->func_slot60(0x1774);
    return 1;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_003629E0);

u8* func_00362F70(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_183F60;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0x1A8) = 0;
    return object;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00362FC0);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00363190);

RecordWithMethods* func_003635B0(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184060;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

u8* func_00363610(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_184060;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xB4) = 0;
    *(u32*)(object + 0xB8) = 0;
    *(u32*)(object + 0xBC) = 0;
    return object;
}


void func_00363660(SkillProtectedDisplay* object)
{
    SkillProtectedFlags* record = &((SkillProtectedFlags*)object->selection->records)[object->selection->current];
    u32 value = protected_second(record);
    LibObject174F20* display = object->display;
    display->numeric_value = value;
    display->unk3c = 1;
    object->display->unk3f = 1;
}

s32 func_00363740(Record00363740* object, s32 mode)
{
    if (object->selection == 0)
    {
        return 0;
    }
    object->selection->active = 0;
    func_0028E2B0(object->selection, mode);
    LibObject175140* text = object->text;
    text->unkfc = static_cast<StatusDetail*>(object->selection->unk04)[object->selection->current].text;
    text->unk3c = 1;
    SkillProtectedFlags* record = &reinterpret_cast<SkillProtectedFlags*>(object->selection->records)[object->selection->current];
    u32 value = protected_second(record);
    LibObject174F20* display = object->display;
    display->numeric_value = value;
    display->unk3c = 1;
    func_00363890(object);
    return 4;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00363890);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00363AE0);

RecordWithMethods* func_00364610(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184160;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

u8* func_00364670(u8* object)
{
    func_2CEBE0(object);
    *(u32*)object = (u32)D_184160;
    *(u32*)(object + 0xA8) = 0;
    *(u32*)(object + 0xAC) = 0;
    *(u32*)(object + 0xB0) = 0;
    *(u32*)(object + 0xB4) = 0;
    *(u32*)(object + 0xC4) = 0;
    *(u32*)(object + 0xC0) = 0;
    *(u32*)(object + 0xD4) = 0;
    *(u32*)(object + 0xD8) = 0;
    *(u8*)(object + 0x114) = 0;
    *(u32*)(object + 0xDC) = 0;
    *(u32*)(object + 0xE0) = 0;
    *(u8*)(object + 0x115) = 0;
    *(u32*)(object + 0xE4) = 0;
    *(u32*)(object + 0xE8) = 0;
    *(u8*)(object + 0x116) = 0;
    *(u32*)(object + 0xEC) = 0;
    *(u32*)(object + 0xF0) = 0;
    *(u8*)(object + 0x117) = 0;
    *(u32*)(object + 0xF4) = 0;
    *(u32*)(object + 0xF8) = 0;
    *(u8*)(object + 0x118) = 0;
    *(u32*)(object + 0xFC) = 0;
    *(u32*)(object + 0x100) = 0;
    *(u8*)(object + 0x119) = 0;
    *(u32*)(object + 0x104) = 0;
    *(u32*)(object + 0x108) = 0;
    *(u8*)(object + 0x11A) = 0;
    *(u32*)(object + 0x10C) = 0;
    *(u32*)(object + 0x110) = 0;
    *(u8*)(object + 0x11B) = 0;
    *(u8*)(object + 0x11C) = 0;
    return object;
}

Record00364720* func_00364720(Record00364720* record, s16 flag)
{
    if (record != 0)
    {
        record->base.methods = D_183D60;
        record->base.nested.methods = D_183D84;
        func_00364AF0(&record->list, -1);
        release_record175030(&record->base, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

void func_003647E0(void* object)
{
}

s32 func_003647F0(void* object)
{
    return 14;
}

void func_00364800(u8* object)
{
    object[0x60] = object[0xa8];
}

SkillOptionsWindow::~SkillOptionsWindow()
{
}

RecordWithMethods* func_00364880(RecordWithMethods* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_183F60;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            ::operator delete(record);
        }
    }
    return record;
}

SkillList184268::SkillList184268()
{
    head = new (0) SkillListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

SkillList184268::~SkillList184268()
{
    func_00364A70(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_003649E0(SkillList* list, void* value)
{
    SkillListNode* node = new (0) SkillListNode;
    if (node != 0)
    {
        SkillListNode* current;
        SkillListNode* next;
        node->value = value;
        node->next = 0;
        current = list->head;
        next = current->next;
        while (next != 0)
        {
            current = next;
            next = next->next;
        }
        current->next = node;
        list->count++;
    }
}

void func_00364A70(SkillList184268* record)
{
    SkillListNode* node = record->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        SkillListNode* next = node->next;
        delete node;
        node = next;
    }
    record->head->next = 0;
    record->count = 0;
}

SkillPairList184258::~SkillPairList184258()
{
    func_00364B70(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00364B70(SkillPairList184258* record)
{
    SkillPairListNode* node = record->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        SkillPairListNode* next = node->next;
        delete node;
        node = next;
    }
    record->head->next = 0;
    record->count = 0;
}

void func_00364BF0(SkillPairList184258* list, SkillPairValue value)
{
    SkillPairListNode* node = new (0) SkillPairListNode;
    if (node != 0)
    {
        node->first = value.first;
        node->second = value.second;
        node->next = 0;
        SkillPairListNode* tail = list->head;
        SkillPairListNode* next = tail->next;
        while (next != 0)
        {
            tail = next;
            next = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

SkillPairList184258::SkillPairList184258()
{
    head = new (0) SkillPairListNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00364D30);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00364D40);

INCLUDE_ASM("build/overlays/cskill/asm/nonmatchings/text", func_00364D50);
