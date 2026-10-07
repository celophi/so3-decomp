#include "overlays/1067-00/grid_marker.h"
#include "overlays/1067-00/text_marker.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_data.h"
#include "include_asm.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/citemcreation/text_003483C0.h"
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/citemcreation/text_003684D0.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/1067-00/text_002764D0.h"
#include "overlays/1067-00/text_002F9C90.h"

/** Consecutive label keys: COOK, ALCH, CRFT, CMPD, SMTH, WRIT, ENG, SYTH. */
enum ItemCreationMessageKey
{
    ITEM_CREATION_SKILL_LABEL_BASE = 0x3458
};

/** Installed creation-facility bits in saved workshop records. */
enum ItemCreationFacilityFlag
{
    ITEM_CREATION_FACILITY_COOK = 0x1,
    ITEM_CREATION_FACILITY_ALCH = 0x2,
    ITEM_CREATION_FACILITY_CRFT = 0x4,
    ITEM_CREATION_FACILITY_CMPD = 0x8,
    ITEM_CREATION_FACILITY_SMTH = 0x10,
    ITEM_CREATION_FACILITY_WRIT = 0x20,
    ITEM_CREATION_FACILITY_ENG = 0x40,
    ITEM_CREATION_FACILITY_SYTH = 0x80
};

extern "C" LibWidgetColors4C5590 D_0036F600;

/** Partial widget aggregate with grid settings and selection callbacks. */
class LibClass1723F0
{
public:
    u8 unk00[0x90];
    ItemCreationClass1746A0 unk90;
    ItemCreationClass1746A0 unke4;
    ItemCreationClass1725D0 unk138;
    ItemCreationClass175030 unk190;
    u8 unk20c[0xEC];
    s32 unk2f8;
    u8 unk2fc[8];
    s32 unk304;
    s32 unk308;
    s32 unk30c;
    u8 unk310[6];
    s8 unk316;
    u8 unk317;
    u8 unk318;
    u8 unk319[3];
    /** @brief Update the aggregate index. @param index Requested index. */
    virtual void func_00412C10(s32 index);
    /** @brief Update the aggregate float setting. @param value Requested setting. */
    virtual void func_00412C20(float value);
    /** @brief Read the aggregate float setting. @return Current setting. */
    virtual float func_00412C30();
    /** @brief Refresh the aggregate. */
    virtual void func_00413020();
};
/** Widget container with an object base and a selection aggregate. */
class LibClass172320 : public LibObject178660, public LibClass1723F0
{
public:
    /** @brief Initialize the container and its widget aggregate. */
    LibClass172320();
    /** @brief Destroy the aggregate and object bases. */
    virtual ~LibClass172320();
};
/** Resident owner of 32 interface rows and the collection state. */
class LibClass1721F0 : public LibClass172320
{
public:
    /** @brief Initialize the option container transform code. */
    LibClass1721F0()
    {
        func_003527C0(&static_cast<LibClass174610&>(*this), 0x6FF6);
    }
    /** @brief Destroy the option row collection. */
    virtual ~LibClass1721F0();
    /** @brief Update row values. @param first First value. @param second Second value. @param third Third value. */
    virtual void func_00412C40(u32 first, u32 second, u32 third);
    /** @brief Create an option row. @param index Row index. @return Created row. */
    virtual ItemCreationClass185030* create_row(s32 index) = 0;
    /** @brief Notify the selected index. @param index Selected index. */
    virtual void notify_index(s32 index);
    /** @brief Notify cancellation. */
    virtual void notify_cancel();
    /** @brief Update the aggregate index. @param index Requested index. */
    virtual void func_00412C10(s32 index);
    /** @brief Update the aggregate float setting. @param value Requested setting. */
    virtual void func_00412C20(float value);
    /** @brief Read the aggregate float setting. @return Current setting. */
    virtual float func_00412C30();
    ItemCreationClass185030* unk410[32];
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
/** Inventor status list with up to 32 row widgets. */
class InventorStatusList : public LibClass1721F0
{
public:
    /** @brief Initialize the option container and clear its own state. */
    InventorStatusList();
    /** @brief Destroy the option container and its collection base. */
    virtual ~InventorStatusList();
    /** @brief Update row values. @param first First value. @param second Second value. @param third Third value. */
    virtual void func_00412C40(u32 first, u32 second, u32 third);
    /** @brief Create an option row. @param index Row index. @return Created row. */
    virtual ItemCreationClass185030* create_row(s32 index);
    /** @brief Notify the selected index. @param index Selected index. */
    virtual void notify_index(s32 index);
    /** @brief Notify cancellation. */
    virtual void notify_cancel();
    /** @brief Update the aggregate index. @param index Requested index. */
    virtual void func_00412C10(s32 index);
    /** @brief Update the aggregate float setting. @param value Requested setting. */
    virtual void func_00412C20(float value);
    u32 unk4b0;
    void* unk4b4;
    u8 unk4b8;
    u8 unk4b9[3];
};
/** @brief Read the aggregate flag. @param aggregate Aggregate owner. @return Current flag. */
extern "C" u8 func_4135D0(LibClass1723F0* aggregate);
/** @brief Read the aggregate index. @param aggregate Aggregate owner. @return Current index. */
extern "C" s32 func_413460(LibClass1723F0* aggregate);
/** @brief Refresh the aggregate. @param aggregate Aggregate owner. */
extern "C" void func_413750(LibClass1723F0* aggregate);

/**
 * @brief Configure the aggregate grid and its visible row dimensions.
 * @param object Widget aggregate.
 * @param count Number of selectable entries.
 * @param columns Entries per row.
 * @param rows Number of visible rows.
 * @param width Horizontal grid extent.
 * @param row_height Height of each row.
 * @param timing Movement timing value.
 */
extern "C" void func_413C00(LibClass1723F0* object, s32 count, s32 columns, s32 rows, float width, float row_height, float timing);
/**
 * @brief Set the aggregate selection and refresh its widgets.
 * @param object Widget aggregate.
 * @param first First displayed row.
 * @param second Selected entry within the visible grid.
 * @param count Number of selectable entries.
 */
extern "C" void func_4138E0(LibClass1723F0* object, s32 first, s32 second, s32 count);


/**
 * @brief Set the frame widget rectangle.
 * @param object Frame widget.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Initialization status.
 */
extern "C" s32 func_421170(ItemCreationClass172870* object, float x, float y, float width, float height);
/**
 * @brief Set the frame widget color.
 * @param object Frame widget.
 * @param color Packed color.
 */
extern "C" void func_420D20(ItemCreationClass172870* object, u32 color);
extern "C" s32 func_44B510(ItemCreationClass1746A0* object, s32 code);
extern "C" s32 func_44B570(ItemCreationClass1746A0* object, float x, float y, float width, float height);


/** Packed sixteen-byte allocation record checked before displaying its value. */
typedef struct ItemCreationAllocationRecord
{
    union
    {
        u16 raw;
        struct
        {
            u16 value : 10;
            u16 other : 6;
        } bits;
    } unk00;
    u16 unk02;
    u16 unk04;
    u16 unk06;
    u16 unk08;
    u16 unk0a;
    u8 unk0c;
    u8 unk0d_low : 3;
    u8 unk0d_shift : 2;
    u8 unk0d_high : 2;
    u8 unk0d_flag : 1;
    u16 unk0e;
} ItemCreationAllocationRecord;


enum
{
    ITEM_CREATION_COLOR_DIM = 0x505050,
    ITEM_CREATION_COLOR_BRIGHT = 0x808080,
    ITEM_CREATION_COLOR_SELECTED = 0x288080,
    ITEM_CREATION_COLOR_ASSIGNED = 0x1E8CFF
};

/** One development line with three inventor IDs and its creation skill. */
typedef struct ItemCreationLineRecord
{
    u8 inventors[3];
    u8 skill_id;
    u8 unk04[0xC];
} ItemCreationLineRecord;

/** Saved workshop with three development lines, facilities and a line count. */
struct ItemCreationWorkshopRecord
{
    ItemCreationLineRecord lines[3];
    u16 facility_mask;
    u8 workshop_id;
    u8 line_count;
};

/** Twelve-byte inventor record with contract and work status. */
typedef struct ItemCreationInventorRecord
{
    u8 unk00[6];
    u8 inventor_id;
    u8 unk07;
    u8 contract_status;
    u8 unk09;
    u8 working;
    u8 unk0b;
} ItemCreationInventorRecord;

typedef struct ItemCreationRuntimeData
{
    ItemCreationAllocationRecord records[3000];
    u8 unkbb80[0x2EE0];
    ItemCreationCategoryRecord item_types[750];
    ItemCreationInventorRecord inventors[38];
    ItemCreationWorkshopRecord workshops[12];
} ItemCreationRuntimeData;

/** Partial holder of the current Field callback receiver. */
typedef struct ItemCreationWindowCallbacks
{
    u8 unk00[0x14];
    FieldClass153E30* unk14;
    u8 unk18[2];
    u16 unk1a;
} ItemCreationWindowCallbacks;

struct ItemCreationCheckedRecord;
struct ItemCreationControlState;
typedef struct ItemCreationRuntime643C
{
    ItemCreationCheckedRecord* unk00;
    u8 unk04[8];
    ItemCreationControlState* unk0c;
    ItemCreationWindowCallbacks* unk10;
    u8 unk14[0xC];
    FieldBufferSlots* unk20;
} ItemCreationRuntime643C;

/**
 * @brief Configure the packed allocation record and its detail values.
 * @param record Allocation record to configure.
 * @param value Ten-bit allocation value.
 * @param channel Channel identifier.
 * @param values Eight detail values, or null for catalog defaults.
 * @param flag Packed record flag.
 * @param enabled Record activation flag.
 */
extern "C" void func_40D2E0(ItemCreationAllocationRecord* record, u16 value, u8 channel,
                          const u16* values, bool flag, bool enabled);

/**
 * @brief Store text field 88 and mark the widget for redraw.
 * @param object Text widget.
 * @param value Field value.
 */
static inline void set_text_unk88(LibClass174EF0* object, float value)
{
    object->unk88 = value;
    object->unk3c = 1;
}
/**
 * @brief Store text field 80 and mark the widget for redraw.
 * @param object Text widget.
 * @param value Field value.
 */
static inline void set_text_unk80(LibClass174EF0* object, float value)
{
    object->unk80 = value;
    object->unk3c = 1;
}

extern "C" void func_00351510(InventorStatusWindow* object, u8 mode);
extern "C" void func_003565A0(ItemCreationClass186770* object, u16 direction);

// These external interfaces are scoped here because their owning code is in other overlays.
extern ItemCreationRuntimeData* D_001B64F8;
extern ItemCreationRuntime643C* D_001B643C;
extern "C" s32 func_002CFE40(void* object, s16 index);

/** @brief Return the selected position pair, or null for an invalid index. */
static inline const float* option_selection_position(ItemCreationSelection* selection, s32 index);
/**
 * @brief Read the selection flag for a one-based option code.
 * @param selection Selection containing twelve option flags.
 * @param code Option code from one through twelve.
 * @return Stored option flag.
 */
static inline u8 selection_enabled(ItemCreationSelection* selection, u8 code);
/** @brief Position and enable a transfer display. */
static inline void set_transfer_position(LibClass175030* display, float x, float y);

/**
 * @brief Read the low byte of the selected grid index.
 * @param display Six-slot index display.
 * @return The byte-sized selected index.
 */
static inline u8 selected_option_index(FieldObject23CEA0* display);

/**
 * @brief Read an option byte from either list.
 * @param state State containing the adjacent option lists.
 * @param list List selector, one or two.
 * @param index Selected six-slot index, from zero through five.
 * @return Stored option byte, or zero for an unsupported list or index.
 */
static inline u32 option_list_value(ItemCreationSelectedDisplayState* state, u8 list, s32 index);

/**
 * @brief Convert an option code to its displayed list index.
 * @param value Option code, or zero for an empty entry.
 * @return Code minus 31, or zero for an empty entry.
 */
static inline u32 option_list_index(u8 value);

/**
 * @brief Store the selected index for either option list.
 * @param object Owner of the option marker selections.
 * @param list List selector, one or two.
 * @param value Byte-sized list index to store.
 */
static inline void set_option_list_index(InventorTransferWindow* object, u8 list, u8 value);

/**
 * @brief Offset one displayed coordinate from its origin.
 * @param origin Base coordinate.
 * @param offset Coordinate displacement.
 * @return Coordinate after applying the displacement.
 */
static inline float shifted_position(float origin, float offset);

/**
 * @brief Test whether the selector is still moving.
 * @param object Selection widget to test.
 * @return One until movement completes, or zero afterward.
 */
static inline bool selector_moving(FieldClass153130* object);

/**
 * @brief Convert a selected item value to its resource slot.
 * @param value Selected item value, or zero for an empty entry.
 * @return Resource slot corresponding to the selected value.
 */
static inline u32 item_resource_index(u8 value);

static inline float shifted_position(float origin, float offset)
{
    return origin + offset;
}

static inline bool selector_moving(FieldClass153130* object)
{
    if (object->unk35)
    {
        return 0;
    }
    return 1;
}

static inline u32 item_resource_index(u8 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 11;
}

/** @brief Store the window control byte. @param object Window base. @param value Control value. */
void func_00348400(FieldClass15AE70* object, u8 value)
{
    object->unk0c = value;
}

/** @brief Read the window control byte. @param object Window base. @return Control value. */
u8 func_00348410(const FieldClass15AE70* object)
{
    return object->unk0c;
}

/** @brief Store the byte state code. @param object Window base. @param value Value to store. */
void func_00348420(FieldClass15AE70* object, u8 value)
{
    object->unk08 = value;
}

/** @brief Read the byte state code. @param object Window base. @return Current field value. */
u8 func_00348430(FieldClass15AE70* object)
{
    return object->unk08;
}

/** @brief Store the halfword state flags. @param object Window base. @param value Value to store. */
void func_00348440(FieldClass15AE70* object, u16 value)
{
    object->unk0a = value;
}

/** @brief Read the halfword state flags. @param object Window base. @return Current field value. */
u16 func_00348450(FieldClass15AE70* object)
{
    return object->unk0a;
}

/** @brief Store the alternate associated window. @param object Window base. @param value Associated window. */
void func_00348480(FieldClass15AE70* object, void* value)
{
    object->unk9c = value;
}

/** @brief Read the alternate associated window. @param object Window base. @return Associated window. */
void* func_00348490(FieldClass15AE70* object)
{
    return object->unk9c;
}

void func_003484A0(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x4) = value;
}

u32 func_003484B0(void* object)
{
    return *(u32*)((u8*)object + 0x4);
}

/** @brief Return the window's nested display container. @return Stored container. */
LibObject178660* FieldClass15AE70::func_slot58()
{
    return unk10;
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

s32 func_003485F0(void* object)
{
    return 0;
}

s32 func_00348600(void* object)
{
    return 0;
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

void func_00348690(void* object)
{
}

void func_003486A0(void* object)
{
}

/** @brief Read the window's alternate control byte. @param object Window receiver. @return Current byte. */
u8 func_003486B0(FieldClass15AE70* object)
{
    return object->unk0d[0];
}

/** @brief Store the window's alternate control byte. @param object Window receiver. @param value Byte to store. */
void func_003486C0(FieldClass15AE70* object, u8 value)
{
    object->unk0d[0] = value;
}

void func_003486D0(void* object)
{
}

/** @brief Read the selection state's associated pointer. @return Stored pointer. */
void* ItemCreationSelectedDisplayState::func_00261150()
{
    return unk20;
}

/** @brief Store the selection state's associated pointer. @param value Pointer to store. */
void ItemCreationSelectedDisplayState::func_00263C70(void* value)
{
    unk20 = value;
}

/**
 * @brief Restore the parent window and switch the active Field receiver.
 * @return Two for returning.
 */
s32 WorkshopFullDialog::func_slotb4()
{
    func_slot20(0);
    WorkshopSelectionWindow* parent = static_cast<WorkshopSelectionWindow*>(func_slot44());
    func_0034A670(parent, 1);
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 2;
}

/**
 * @brief Restore the parent window and switch the active Field receiver.
 * @return One for confirmation.
 */
s32 WorkshopFullDialog::func_slotb0()
{
    func_slot20(0);
    WorkshopSelectionWindow* parent = static_cast<WorkshopSelectionWindow*>(func_slot44());
    func_0034A670(parent, 1);
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 1;
}


/**
 * @brief Create the confirmation window panels and text displays.
 * @param associated Text source associated with the window.
 * @return Always one.
 */
s32 WorkshopFullDialog::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 60.0f, 160.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 368.0f, 190.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibWidgetColors4C5590 colors = D_0036F600;
    LibClass178630* heading_panel = new (0) LibClass178630;
    func_004C5A80(heading_panel, 0, 0.0f, 0.0f, 368.0f, 48.0f, 88.0f);
    func_4C5590(heading_panel, &colors);
    func_004C6190(unk10, heading_panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(0.0f, 0.0f, 368.0f, 48.0f, (s32)associated, 0x15FA0, 0);
    heading->set_mode(1);
    heading->set_vertical_alignment(1);
    func_004C6190(unk10, heading);
    LibObject178750* first = new (0) LibObject178750;
    first->func_004C7FE0(48.0f, 72.0f, 0.0f, 0.0f, (s32)associated, 0x15FA1, 0);
    func_004C6190(unk10, first);
    LibObject178750* second = new (0) LibObject178750;
    second->func_004C7FE0(240.0f, 150.0f, 0.0f, 0.0f, (s32)associated, 0x15FA2, 0);
    func_004C6190(unk10, second);
    return 1;
}

/**
 * @brief Destroy the window through its Field base.
 */
WorkshopFullDialog::~WorkshopFullDialog()
{
}

/** @brief Refresh the two option colors from the grid selection. @param object Option window. */
static inline void update_selection_colors(AssignInventorDialog* object)
{
    if (object->unka8 != 0)
    {
        if (object->unka8->unk114 == 0)
        {
            object->unkbc->set_color(ITEM_CREATION_COLOR_SELECTED);
            object->unkc0->set_color(ITEM_CREATION_COLOR_BRIGHT);
        }
        else
        {
            object->unkbc->set_color(ITEM_CREATION_COLOR_BRIGHT);
            object->unkc0->set_color(ITEM_CREATION_COLOR_SELECTED);
        }
    }
}

/**
 * @brief Set the option window mode and refresh its selection colors.
 * @param object Option window.
 * @param mode Zero resets the selection; one activates it.
 */
extern "C" void func_00348B60(AssignInventorDialog* object, u16 mode)
{
    switch (mode)
    {
    case 1:
        object->func_slot20(1);
        if (object->unka8 != 0)
        {
            func_0023CEA0(object->unka8, 1);
            update_selection_colors(object);
        }
        break;
    case 0:
        object->func_slot20(0);
        if (object->unka8 != 0)
        {
            func_0023C550(object->unka8, 1);
            func_0023CEA0(object->unka8, 0);
            update_selection_colors(object);
        }
        break;
    }
}

/**
 * @brief Move the grid selection in direction two and refresh its colors.
 */
void AssignInventorDialog::func_slot74()
{
    if (unka8 != 0)
    {
        if (unka8->func_0023CDB0(2) != 1)
        {
            update_selection_colors(this);
        }
    }
}

/**
 * @brief Move the grid selection in direction three and refresh its colors.
 */
void AssignInventorDialog::func_slot70()
{
    if (unka8 != 0)
    {
        if (unka8->func_0023CDB0(3) != 1)
        {
            update_selection_colors(this);
        }
    }
}

/**
 * @brief Reset this window and restore its associated Field receiver.
 * @return Always two.
 */
s32 AssignInventorDialog::func_slotb4()
{
    func_00348B60(this, 0);
    WorkshopSelectionWindow* parent = static_cast<WorkshopSelectionWindow*>(func_slot44());
    func_0034A670(parent, 1);
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 2;
}

/**
 * @brief Store an option code when the selection state has its runtime table.
 * @param state Selection state.
 * @param index Inventor ID.
 * @param code Option code.
 */
static inline void store_option_code(ItemCreationSelectedDisplayState* state, u8 index, u8 code)
{
    if (state->unk40 != 0)
    {
        state->unk40->unk188[index] = code;
    }
}

/**
 * @brief Apply the chosen option code or return to the associated window.
 * @return Zero without a grid, one after applying the code, or the return callback result.
 */
s32 AssignInventorDialog::func_slotb0()
{
    if (unka8 == 0)
    {
        return 0;
    }
    if (unka8->unk114 == 0)
    {
        ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
        u8 code = unkc5 == 0 ? 0 : unkc5 + 1;
        u8 index = unkc4 == 0 ? 0 : unkc4 + 31;
        store_option_code(state, index, code);
        func_slot1c(0xFF, 0x80);
    }
    else
    {
        return func_slotb4();
    }
    return 1;
}

/**
 * @brief Create the selected option resource, text displays, and two-column grid.
 * @param associated Text source associated with the window.
 * @return Zero without an option code, or one after setup.
 */
s32 AssignInventorDialog::func_slotf4(void* associated)
{
    if (unkc4 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 60.0f, 190.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 368.0f, 165.0f, 88.0f);
    func_004C6190(unk10, panel);
    u16 resource_index = unkc4 + 20;
    unkac = new (0) ItemCreationOptionResourceDisplay;
    void* payload = func_002D3D80(D_001B643C->unk20, (u8)resource_index);
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 81);
    unkac->unkcc = payload;
    unkac->unkd0 = resource_index;
    unkac->func_002D6440(record, 18.5f, 18.5f);
    ItemCreationOptionResourceDisplay* display = unkac;
    display->unk50.unk34 = 2.0f;
    display->unk50.unk30 = 2.0f;
    display->unk3c = 1;
    func_004C6190(unk10, unkac);
    unkb0 = new (0) LibObject178750;
    unkb0->func_004C7FE0(152.0f, 18.5f, 0.0f, 0.0f, (s32)associated, unkc4 + 0x3584, 0);
    unkb0->set_color(0x808050);
    func_004C6190(unk10, unkb0);
    unkb4 = new (0) LibObject178750;
    unkb4->func_004C7FE0(152.0f, 44.5f, 0.0f, 0.0f, (s32)associated, 0x3584, 0);
    func_004C6190(unk10, unkb4);
    unkb8 = new (0) LibObject178750;
    unkb8->func_004C7FE0(152.0f, 70.5f, 0.0f, 0.0f, (s32)associated, 0x15F9D, 0);
    func_004C6190(unk10, unkb8);
    unkbc = new (0) LibObject178750;
    unkbc->func_004C7FE0(178.5f, 124.5f, 0.0f, 0.0f, (s32)associated, 0x15F9E, 0);
    func_004C6190(unk10, unkbc);
    unkc0 = new (0) LibObject178750;
    unkc0->func_004C7FE0(238.5f, 124.5f, 0.0f, 0.0f, (s32)associated, 0x15F9F, 0);
    func_004C6190(unk10, unkc0);
    unka8 = new (0) FieldObject23CEA0;
    unka8->func_0023CE80(2, 1);
    unka8->func_0023CE60(60.0f, 0.0f);
    unka8->unkF2 = 0;
    unka8->unk119 = 1;
    unka8->func_0023CF50(1, 238.5f, 314.5f);
    func_0023CEA0(unka8, 0);
    func_0036F040(&unk74, unka8);
    update_selection_colors(this);
    return 1;
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass175110::~ItemCreationClass175110()
{
}

/**
 * @brief Destroy the window through its Field base.
 */
AssignInventorDialog::~AssignInventorDialog()
{
}

/**
 * @brief Destroy the window through its Field base.
 */
PendingInventorSummary::~PendingInventorSummary()
{
}

/**
 * @brief Read an inventor's normalized placement code from the option table.
 * @param table Option table, or null.
 * @param inventor_option_code Inventor option code selecting the table entry.
 * @return Placement code from one through thirteen, or zero otherwise.
 */
static inline u16 inventor_location_code(ItemCreationOptionTable* table, u8 inventor_option_code)
{
    if (table == 0)
    {
        return 0;
    }
    u16 code = table->unk188[inventor_option_code];
    switch (code)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    default:
        code = 0;
        break;
    }
    return code;
}

/** @brief Convert an inventor option code to an inventor ID. @param inventor_option_code Option code, or zero. @return Inventor ID, or zero. */
static inline u32 inventor_id_from_option_code(s32 inventor_option_code)
{
    if (inventor_option_code == 0)
    {
        return 0;
    }
    return inventor_option_code - 31;
}

/** @brief Reset both display scale values and mark drawing state dirty. @param display Resource display. */
static inline void reset_display_scale(ItemCreationOptionResourceDisplay* display)
{
    display->unk50.unk34 = 1.0f;
    display->unk50.unk30 = 1.0f;
    display->unk3c = 1;
}

/**
 * @brief Refresh the NPC inventors assigned to a workshop.
 * @param object Workshop inventor strip.
 * @param workshop_id Workshop ID stored as a byte; zero selects unassigned inventors.
 */
void func_00349DE0(WorkshopInventorStrip* object, u32 workshop_id)
{
    if (object->selection_state != 0)
    {
        for (s32 index = 0; index < 6; index++)
        {
            object->portrait_indices[index] = 0;
            object->inventor_ids[index] = 0;
        }
        object->workshop_id = workshop_id;
        u8 location_code = object->workshop_id + 1;
        object->inventor_count = 0;
        for (s32 inventor_option_code = 32; inventor_option_code <= 59; inventor_option_code++)
        {
            if (location_code == (u8)inventor_location_code(object->selection_state->unk40, (u8)inventor_option_code))
            {
                u16 portrait_index = inventor_option_code - 11;
                u16 inventor_id = inventor_id_from_option_code(inventor_option_code);
                object->portrait_indices[object->inventor_count] = portrait_index;
                object->inventor_ids[object->inventor_count] = inventor_id;
                object->inventor_count++;
            }
            if (object->inventor_count >= 7)
            {
                break;
            }
        }
        for (s32 index = 0; index < 6; index++)
        {
            void* allocation = func_002D3D80(D_001B643C->unk20, 0);
            FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 16);
            reset_display_scale(object->inventor_portraits[index]);
            object->inventor_portraits[index]->func_002D5CF0(allocation, record, 0);
        }
        for (s32 index = 0; index < 6; index++)
        {
            s32 raw_portrait_index = object->portrait_indices[index];
            if (raw_portrait_index != 0)
            {
                u8 portrait_index = raw_portrait_index;
                void* allocation = func_002D3D80(D_001B643C->unk20, portrait_index);
                FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 81);
                object->inventor_portraits[index]->unkd0 = portrait_index;
                object->inventor_portraits[index]->func_002D5CF0(allocation, record, 0);
                object->inventor_portraits[index]->unk3f = 1;
                reset_display_scale(object->inventor_portraits[index]);
            }
        }
    }
}

/**
 * @brief Update the talent display for the selected inventor.
 * @param object Workshop inventor strip.
 * @param enabled Whether to show the selected inventor or clear the talent display.
 */
static inline void update_selected_inventor_talents(WorkshopInventorStrip* object, bool enabled)
{
    if (object->inventor_grid != 0)
    {
        object->selected_inventor_index = object->inventor_grid->unk114;
        InventorTalentsWindow* child = static_cast<InventorTalentsWindow*>(object->func_slot4c());
        u8 code = enabled ? object->inventor_ids[object->selected_inventor_index] : 0;
        if (child != 0)
        {
            child->selected_inventor_id = code;
            func_0034B970(child);
        }
    }
}

/**
 * @brief Move the grid in direction two and refresh the alternate display.
 */
void WorkshopInventorStrip::func_slot74()
{
    if (inventor_grid != 0)
    {
        if (inventor_grid->func_0023CDB0(2) != 1)
        {
            update_selected_inventor_talents(this, true);
        }
    }
}

/**
 * @brief Move the grid in direction three and refresh the alternate display.
 */
void WorkshopInventorStrip::func_slot70()
{
    if (inventor_grid != 0)
    {
        if (inventor_grid->func_0023CDB0(3) != 1)
        {
            update_selected_inventor_talents(this, true);
        }
    }
}

/**
 * @brief Reset the grid and restore its associated window.
 * @return Zero without an associated window, or one after restoring it.
 */
s32 WorkshopInventorStrip::func_slotb4()
{
    func_0034A1E0(this, 0);
    WorkshopSelectionWindow* parent = static_cast<WorkshopSelectionWindow*>(func_slot44());
    if (parent == 0)
    {
        return 0;
    }
    func_0034A670(parent, 1);
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 1;
}

/**
 * @brief Enable or disable inventor selection and refresh the talent display.
 * @param object Workshop inventor strip.
 * @param mode Zero resets the grid; one activates it.
 */
void func_0034A1E0(WorkshopInventorStrip* object, u16 mode)
{
    switch (mode)
    {
    case 1:
        if (object->inventor_grid != 0)
        {
            object->inventor_grid->unkad = 1;
            update_selected_inventor_talents(object, true);
        }
        break;
    case 0:
        if (object->inventor_grid != 0)
        {
            object->inventor_grid->unkad = 0;
            update_selected_inventor_talents(object, false);
        }
        break;
    }
}

/**
 * @brief Destroy the window through its Field base.
 */
WorkshopInventorStrip::~WorkshopInventorStrip()
{
}

void func_0034A670(WorkshopSelectionWindow* object, u8 mode)
{
    LibClass178600* nested;
    switch (mode)
    {
    case 1:
    {
        nested = object->register_button;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->view_button;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->register_label;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->view_label;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->back_button;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->back_label;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        LibClass175030* transfer = object->unk15c;
        if (transfer != 0)
        {
            transfer->unk30 = 128.0f;
            transfer->unk3c = 1;
        }
        break;
    }
    case 0:
    {
        nested = object->register_button;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->view_button;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->register_label;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->view_label;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->back_button;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->back_label;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        LibClass175030* transfer = object->unk15c;
        if (transfer != 0)
        {
            transfer->unk30 = 64.0f;
            transfer->unk3c = 1;
        }
        break;
    }
    }
}

void func_0034A7A0(WorkshopSelectionWindow* object, u8 selected)
{
    ItemCreationRuntimeData* state;
    ItemCreationWorkshopRecord* record;
    s32 index;
    u16 flags;
    u8 enabled;

    for (index = 0; index < 8; index++)
    {
        LibObject178750* display = object->facility_labels[index];
        if (display != 0)
        {
            display->set_color(ITEM_CREATION_COLOR_DIM);
        }
    }
    if (object->facility_labels[8] != 0)
    {
        object->facility_labels[8]->unk3f = 0;
    }
    state = D_001B64F8;
    enabled = 0;
    if (selected > 0 && selected < 13)
    {
        enabled = 1;
    }
    if (enabled)
    {
        record = &state->workshops[selected - 1];
    }
    else
    {
        record = 0;
    }
    if (record != 0)
    {
        flags = record->facility_mask;
        if (flags & ITEM_CREATION_FACILITY_COOK)
        {
            LibObject178750* display = object->facility_labels[0];
            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
        }
        if (flags & ITEM_CREATION_FACILITY_ALCH)
        {
            LibObject178750* display = object->facility_labels[1];
            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
        }
        if (flags & ITEM_CREATION_FACILITY_CRFT)
        {
            LibObject178750* display = object->facility_labels[2];
            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
        }
        if (flags & ITEM_CREATION_FACILITY_CMPD)
        {
            LibObject178750* display = object->facility_labels[3];
            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
        }
        if (flags & ITEM_CREATION_FACILITY_SMTH)
        {
            LibObject178750* display = object->facility_labels[4];
            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
        }
        if (flags & ITEM_CREATION_FACILITY_WRIT)
        {
            LibObject178750* display = object->facility_labels[5];
            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
        }
        if (flags & ITEM_CREATION_FACILITY_ENG)
        {
            LibObject178750* display = object->facility_labels[6];
            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
        }
        if (flags & ITEM_CREATION_FACILITY_SYTH)
        {
            LibObject178750* display = object->facility_labels[7];
            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
        }
    }
}

/**
 * @brief Activate the workshop inventor strip and its talent display.
 * @return Always one.
 */
s32 WorkshopSelectionWindow::func_slotbc()
{
    func_0034A670(this, 0);
    WorkshopInventorStrip* alternate = static_cast<WorkshopInventorStrip*>(this->func_slot4c());
    func_0034A1E0(alternate, 1);
    D_001B643C->unk10->unk14->func_00263C70(alternate);
    return 1;
}

/**
 * @brief Set the transfer display opacity and mark it for drawing.
 * @param display Transfer display.
 * @param opacity Alpha value, with 128 representing full opacity.
 */
static inline void set_transfer_opacity(LibClass175030* display, float opacity)
{
    display->unk30 = opacity;
    display->unk3c = 1;
}

/**
 * @brief Confirm inventor assignment or show the workshop-full warning.
 * @return Zero without required windows, three for a full workshop, or one when requesting confirmation.
 */
s32 WorkshopSelectionWindow::func_slotb0()
{
    WorkshopInventorStrip* alternate = static_cast<WorkshopInventorStrip*>(this->func_slot4c());
    if (alternate == 0)
    {
        return 0;
    }
    AssignInventorDialog* parent = static_cast<AssignInventorDialog*>(this->func_slot44());
    if (parent == 0)
    {
        return 0;
    }
    if (this->workshop_full_dialog == 0)
    {
        return 0;
    }
    u8 inventor_count = alternate->inventor_count;
    set_transfer_opacity(this->unk15c, 64.0f);
    if (inventor_count >= 6)
    {
        this->workshop_full_dialog->func_slot20(1);
        D_001B643C->unk10->unk14->func_00263C70(this->workshop_full_dialog);
        return 3;
    }
    func_00348B60(parent, 1);
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 1;
}

/**
 * @brief Move the selection and refresh the associated detail windows.
 * @param direction Direction code.
 */
void WorkshopSelectionWindow::func_slotf8(u16 direction)
{
    AssignInventorDialog* parent;
    ItemCreationSelection* selection;
    const float* position;
    s32 index;
    u8 selected;

    if (this->unk15c != 0 && this->unk15c->unk35 != 0)
    {
        selection = &this->unkdc;
        index = func_003696B0(selection, direction);
        if (index <= 0)
        {
            position = 0;
        }
        else if (index > 12)
        {
            position = 0;
        }
        else
        {
            position = selection->unk00[index - 1].unk00;
        }
        this->unk15c->func_00466E40(position[0], position[1], 0.05f);
        func_002CFE40(D_001B643C->unk10, 0);
    }
    selected = this->workshop_selection->unk6c;
    if (this->workshop_name != 0)
    {
        func_4C6DF0(this->workshop_name, this->func_slot54(), selected + 0x3520, 0);
    }
    func_0034A7A0(this, selected);
    WorkshopInventorStrip* alternate = static_cast<WorkshopInventorStrip*>(this->func_slot4c());
    if (alternate != 0)
    {
        func_00349DE0(alternate, selected);
    }
    parent = static_cast<AssignInventorDialog*>(this->func_slot44());
    if (parent != 0)
    {
        parent->unkc5 = selected;
        u32 key = parent->unkc5 + 0x3520;
        if (parent->unkb4 != 0)
        {
            func_4C6DF0(parent->unkb4, parent->func_slot54(), key, 0);
        }
    }
}

/**
 * @brief Forward direction 2 to the window.
 */
void WorkshopSelectionWindow::func_slot74()
{
    func_slotf8(2);
}

/**
 * @brief Forward direction 4 to the window.
 */
void WorkshopSelectionWindow::func_slot70()
{
    func_slotf8(4);
}

/**
 * @brief Forward direction 3 to the window.
 */
void WorkshopSelectionWindow::func_slot6c()
{
    func_slotf8(3);
}

/**
 * @brief Forward direction 1 to the window.
 */
void WorkshopSelectionWindow::func_slot68()
{
    func_slotf8(1);
}

/** @brief Destroy the selection window through its base. */
WorkshopSelectionWindow::~WorkshopSelectionWindow()
{
}

/** @brief Initialize the selection window and its display pointers. */
WorkshopSelectionWindow::WorkshopSelectionWindow()
{
    workshop_selection = 0;
    workshop_selection = &unkdc;
    workshop_name = 0;
    for (s32 index = 0; index < 9; index++)
    {
        facility_labels[index] = 0;
    }
    register_button = 0;
    back_button = 0;
    view_button = 0;
    register_label = 0;
    back_label = 0;
    view_label = 0;
    workshop_full_dialog = 0;
}

/** Six-byte inventor record containing a talent value and its one-based skill. */
struct ItemCreationInventorTalent
{
    u8 unk00[2];
    u8 talent;
    u8 skill;
    u8 unk04[2];
};

/** NPC inventor talents, indexed by inventor ID minus one. */
extern "C" const ItemCreationInventorTalent D_501DA0[];

/**
 * @brief Test whether an inventor is a party member.
 * @param inventor_id Inventor ID.
 * @return One for party-member inventor IDs, otherwise zero.
 */
static inline u8 is_party_inventor(u8 inventor_id)
{
    return inventor_id >= 29;
}

/** Thirteen-byte party record containing its eight creation-skill talents. */
struct ItemCreationPartyTalents
{
    u8 talents[8];
    u8 unk08[5];
};
/** Party-member talents, indexed by inventor ID minus twenty-nine. */
extern "C" const ItemCreationPartyTalents D_501E50[];

/**
 * @brief Find a party member's creation talents.
 * @param index Party-member index within the table.
 * @return Talent record at that index.
 */
static inline const ItemCreationPartyTalents* party_talent_record(s32 index)
{
    return &D_501E50[index];
}
/**
 * @brief Read an inventor's talent in a creation skill.
 * @param inventor_id Inventor ID.
 * @param skill_index Creation skill index from zero through seven.
 * @return Talent value, or zero for an unassigned skill.
 */
static inline u8 inventor_talent(u8 inventor_id, s32 skill_index)
{
    u8 talent = 0;
    if (is_party_inventor(inventor_id))
    {
        talent = party_talent_record(inventor_id - 29)->talents[skill_index];
    }
    else
    {
        const ItemCreationInventorTalent* record = &D_501DA0[inventor_id - 1];
        if (record->skill == skill_index + 1)
        {
            talent = record->talent;
        }
    }
    return talent;
}

/**
 * @brief Convert an inventor ID to its option-table code.
 * @param inventor_id Inventor ID, or zero.
 * @return Zero for no inventor, otherwise its ID plus thirty-one.
 */
static inline u32 inventor_option_code_from_id(u8 inventor_id)
{
    if (inventor_id == 0)
    {
        return 0;
    }
    return inventor_id + 31;
}

/**
 * @brief Return the runtime record for a one-based option code.
 * @param state State containing the runtime option records.
 * @param option One-based option code.
 * @return Selected record, or null for an invalid code.
 */
static inline ItemCreationInventorRecord* option_record(ItemCreationRuntimeData* state, u8 option)
{
    u8 valid = option >= 1 && option < 39;
    if (valid)
    {
        return &state->inventors[option - 1];
    }
    return 0;
}

/**
 * @brief Show an inventor's talent for one skill.
 * @param object Option detail window.
 * @param record Selected inventor record.
 * @param index Skill index from zero through seven.
 */
static inline void show_inventor_skill(InventorTalentsWindow* object, ItemCreationInventorRecord* record, u8 index)
{
    object->skill_labels[index]->set_color(0x808080);
    u8 talent = inventor_talent(record->inventor_id, index);
    LibObject174F20* value_display = object->skill_values[index];
    value_display->unkfc = talent;
    value_display->unk3c = 1;
    object->skill_values[index]->unk3d = 1;
}

void func_0034B970(InventorTalentsWindow* object)
{
    object->inventor_name->unk3f = 0;
    for (s32 index = 0; index < 8; index++)
    {
        object->skill_labels[index]->set_color(0x505050);
        object->skill_values[index]->unk3d = 0;
    }
    u8 code = object->selected_inventor_id;
    if (code != 0)
    {
        ItemCreationInventorRecord* record = option_record(D_001B64F8, code);

        if (code > 0)
        {
            func_4C6DF0(object->inventor_name, object->func_slot54(), code + 0x3584, 0);
            object->inventor_name->unk3f = 1;
            if (object->selection_state != 0)
            {
                u16 flags = item_creation_inventor_skill_mask(object->selection_state, inventor_option_code_from_id(object->selected_inventor_id));
                if (flags & 0x1)
                {
                    show_inventor_skill(object, record, 0);
                }
                if (flags & 0x2)
                {
                    show_inventor_skill(object, record, 1);
                }
                if (flags & 0x4)
                {
                    show_inventor_skill(object, record, 2);
                }
                if (flags & 0x8)
                {
                    show_inventor_skill(object, record, 3);
                }
                if (flags & 0x10)
                {
                    show_inventor_skill(object, record, 4);
                }
                if (flags & 0x20)
                {
                    show_inventor_skill(object, record, 5);
                }
                if (flags & 0x40)
                {
                    show_inventor_skill(object, record, 6);
                }
                if (flags & 0x80)
                {
                    show_inventor_skill(object, record, 7);
                }
            }
        }
    }
}

/**
 * @brief Create the inventor title, skill labels and numeric talent displays.
 * @param associated Text source passed to the window base and child widgets.
 * @return One after setup completes.
 */
s32 InventorTalentsWindow::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 464.0f, 296.0f, 17);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 160.0f, 172.0f, 88.0f);
    func_004C6190(unk10, panel);
    inventor_name = new (0) LibObject178750;
    inventor_name->func_004C7FE0(0.0f, 8.0f, 160.0f, 19.2f, (s32)associated, 0x3584, 1);
    inventor_name->set_scale(0.8f, 0.8f);
    inventor_name->set_mode(1);
    inventor_name->unk3f = 0;
    func_004C6190(unk10, inventor_name);
    float row_y = 34.0f;
    for (s32 index = 0; index < 8; index++)
    {
        if (index != 0 && index % 3 == 0)
        {
            row_y += 4.0f;
        }
        skill_labels[index] = new (0) LibObject178750;
        skill_values[index] = new (0) LibObject174F20;
        float y = row_y + 42.0f * (index / 3);
        float x = 10.0f + 50.0f * (index % 3);
        skill_labels[index]->func_004C7FE0(x, y, 0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_SKILL_LABEL_BASE, 1);
        func_00464D90(skill_values[index], 99, (s32)associated, 1, x, y + 21.0f, 38.4f, 19.2f);
        skill_values[index]->set_mode(1);
        set_text_unk80(skill_labels[index], 0.6f);
        skill_values[index]->set_scale(0.8f, 0.8f);
        func_004C6190(unk10, skill_labels[index]);
        func_004C6190(unk10, skill_values[index]);
    }
    if (skill_labels[8] != 0)
    {
        skill_labels[8]->unk3f = 0;
    }
    if (skill_values[8] != 0)
    {
        skill_values[8]->unk3f = 0;
    }
    func_0034B970(this);
    return 1;
}

/**
 * @brief Destroy the window through its Field base.
 */
InventorTalentsWindow::~InventorTalentsWindow()
{
}

static inline u8 selected_option_index(FieldObject23CEA0* display)
{
    return display->unk114;
}

static inline u32 option_list_value(ItemCreationSelectedDisplayState* state, u8 list, s32 index)
{
    if (index < 0)
    {
        return 0;
    }
    if (index > 6)
    {
        return 0;
    }
    switch (list)
    {
    case 1:
        return state->unk71[index];
    case 2:
        return state->unk77[index];
    default:
        return 0;
    }
}

static inline u32 option_list_index(u8 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 31;
}

static inline void set_option_list_index(InventorTransferWindow* object, u8 list, u8 value)
{
    switch (list)
    {
    case 1:
        object->source_inventor_id = value;
        break;
    case 2:
        object->destination_inventor_id = value;
        break;
    }
}

/**
 * @brief Dispatch a grid direction and refresh the selected option markers.
 * @param direction Direction code.
 */
void DestinationInventorStrip::func_slotf8(s32 direction)
{
    if (unkc8 != 0 && unkc8->func_0023CDB0(direction) != 1)
    {
        InventorTransferWindow* target = unkcc;
        ItemCreationSelectedDisplayState* state;
        if (target != 0 && (state = unkc4) != 0)
        {
            u8 list = unka8;
            u32 value = option_list_value(state, list, selected_option_index(unkc8));
            u8 result = value;
            if (value != 0)
            {
                result = option_list_index(value);
            }
            set_option_list_index(target, list, result);
            func_0034DB00(target, 0xFF);
        }
    }
}

/**
 * @brief Reset the option and restore its associated selection display.
 * @return Always two.
 */
s32 DestinationInventorStrip::func_slotb4()
{
    if (unkc4 != 0)
    {
        item_creation_advance_inventor_transfer(unkc4, -1);
    }
    if (unkc8 != 0)
    {
        func_0023CEA0(unkc8, 0);
    }
    if (unkcc != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(unkcc);
    }
    unkc4->unk129 = 2;
    InventorTransferWindow* target = static_cast<InventorTransferWindow*>(func_slot44());
    if (target != 0)
    {
        switch (target->selection_state->unk129)
        {
        case 0:
            target->unk16c->unk3f = 0;
            target->unk15c->unk3f = 1;
            break;
        case 1:
            break;
        case 2:
            target->unk15c->unk3f = 1;
            break;
        case 3:
            break;
        }
        func_0034DB00(target, 0xFF);
    }
    return 2;
}

/**
 * @brief Select the active view and apply its selected option.
 * @return Always one.
 */
s32 DestinationInventorStrip::func_slotb0()
{
    if (unkcc != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(unkcc);
    }
    if (unkc8 != 0 && unkc4 != 0)
    {
        u8 list = unka8;
        u8 value = option_list_value(unkc4, list, selected_option_index(unkc8));
        item_creation_advance_inventor_transfer(unkc4, value);
    }
    return 1;
}

/**
 * @brief Set up the option window and recover its associated display.
 * @param associated Object associated with the window.
 * @return Zero when no option state is attached, or one after setup.
 */
s32 DestinationInventorStrip::func_slotf4(void* associated)
{
    if (unkc4 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 384.0f, 17);
    TransferInventorStrip::func_slotf4(associated);
    unkcc = static_cast<InventorTransferWindow*>(func_slot44());
    return 1;
}

/**
 * @brief Destroy the option window and its base.
 */
DestinationInventorStrip::~DestinationInventorStrip()
{
}

/**
 * @brief Dispatch a grid direction and refresh the selected option markers.
 * @param direction Direction code.
 */
void SourceInventorStrip::func_slotf8(s32 direction)
{
    if (unkc8 != 0 && unkc8->func_0023CDB0(direction) != 1)
    {
        InventorTransferWindow* target = unkcc;
        ItemCreationSelectedDisplayState* state;
        if (target != 0 && (state = unkc4) != 0)
        {
            u8 list = unka8;
            u32 value = option_list_value(state, list, selected_option_index(unkc8));
            u8 result = value;
            if (value != 0)
            {
                result = option_list_index(value);
            }
            set_option_list_index(target, list, result);
            func_0034DB00(target, 0xFF);
        }
    }
}

/**
 * @brief Read the selection flag for a one-based option code.
 * @param selection Selection containing twelve option flags.
 * @param code Option code from one through twelve.
 * @return Stored option flag.
 */
static inline u8 selection_enabled(ItemCreationSelection* selection, u8 code)
{
    return selection->unk60[code - 1];
}

/**
 * @brief Return a selection position.
 * @param selection Selection owner.
 * @param index One-based position index.
 * @return Position pair, or null for an invalid index.
 */
static inline const float* option_selection_position(ItemCreationSelection* selection, s32 index)
{
    if (index <= 0)
    {
        return 0;
    }
    if (index > 12)
    {
        return 0;
    }
    return selection->unk00[index - 1].unk00;
}

/**
 * @brief Place and enable the transfer display.
 * @param display Display to position.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 */
static inline void set_transfer_position(LibClass175030* display, float x, float y)
{
    display->unk10 = x;
    display->unk14 = y;
    display->unk35 = 1;
    display->unk3c = 1;
}

/**
 * @brief Reset the option and restore its associated selection display.
 * @return Always two.
 */
s32 SourceInventorStrip::func_slotb4()
{
    if (unkc4 != 0)
    {
        item_creation_advance_inventor_transfer(unkc4, -1);
    }
    if (unkc8 != 0)
    {
        func_0023CEA0(unkc8, 0);
    }
    if (unkcc != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(unkcc);
    }
    unkc4->unk129 = 0;
    InventorTransferWindow* target = static_cast<InventorTransferWindow*>(func_slot44());
    if (target != 0)
    {
        u8 selected = unka9;
        target->workshop_selection->unk6c = selected;
        const float* position = option_selection_position(target->workshop_selection, selected);
        set_transfer_position(target->unk15c, position[0], position[1]);
        switch (target->selection_state->unk129)
        {
        case 0:
            target->unk16c->unk3f = 0;
            target->unk15c->unk3f = 1;
            break;
        case 1:
            break;
        case 2:
            target->unk15c->unk3f = 1;
            break;
        case 3:
            break;
        }
        func_0034DB00(target, 0xFF);
    }
    return 2;
}

/**
 * @brief Apply the selected option and refresh its associated window.
 * @return Always one.
 */
s32 SourceInventorStrip::func_slotb0()
{
    if (unkcc != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(unkcc);
    }
    if (unkc8 != 0 && unkc4 != 0)
    {
        u8 value = option_list_value(unkc4, unka8, selected_option_index(unkc8));
        item_creation_advance_inventor_transfer(unkc4, value);
    }
    InventorTransferWindow* target = static_cast<InventorTransferWindow*>(func_slot44());
    if (target != 0)
    {
        switch (target->selection_state->unk129)
        {
        case 0:
            target->unk16c->unk3f = 0;
            target->unk15c->unk3f = 1;
            break;
        case 1:
            break;
        case 2:
            target->unk15c->unk3f = 1;
            break;
        case 3:
            break;
        }
        func_0034DB00(target, 0xFF);
        func_0034D980(target, 0xFF);
    }
    return 1;
}

/**
 * @brief Set up the option window and recover its associated display.
 * @param associated Object associated with the window.
 * @return Zero when no option state is attached, or one after setup.
 */
s32 SourceInventorStrip::func_slotf4(void* associated)
{
    if (unkc4 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 300.0f, 17);
    TransferInventorStrip::func_slotf4(associated);
    unkcc = static_cast<InventorTransferWindow*>(func_slot44());
    return 1;
}

/**
 * @brief Destroy the option window and its base.
 */
SourceInventorStrip::~SourceInventorStrip()
{
}

/**
 * @brief Transfer the selected option into its list display and refresh the option markers.
 */
void TransferInventorStrip::func_slot5c()
{
    InventorTransferWindow* target = unkcc;
    ItemCreationSelectedDisplayState* state;
    u8 status;
    u8 list;
    u32 value;
    u8 result;
    if (target != 0 && (state = unkc4) != 0)
    {
        list = unka8;
        status = state->unk129;
        if (list == 1)
        {
            switch (status)
            {
        case 1:
        case 2:
        case 3:
                value = option_list_value(state, list, selected_option_index(unkc8));
                result = value;
                if (value != 0)
                {
                    result = option_list_index(value);
                }
                set_option_list_index(target, list, result);
                func_0034DB00(target, 0xFF);
            break;
            }
        }
        list = unka8;
        if (list == 2)
        {
            switch (status)
            {
        case 3:
                value = option_list_value(unkc4, list, selected_option_index(unkc8));
                result = value;
                if (value != 0)
                {
                    result = option_list_index(value);
                }
                target = unkcc;
                set_option_list_index(target, list, result);
                func_0034DB00(target, 0xFF);
            break;
            }
        }
    }
}

/**
 * @brief Dispatch a grid direction and refresh the selected option markers.
 * @param direction Direction code.
 */
void TransferInventorStrip::func_slotf8(s32 direction)
{
    if (unkc8 != 0 && unkc8->func_0023CDB0(direction) != 1)
    {
        InventorTransferWindow* target = unkcc;
        ItemCreationSelectedDisplayState* state;
        if (target != 0 && (state = unkc4) != 0)
        {
            u8 list = unka8;
            u32 value = option_list_value(state, list, selected_option_index(unkc8));
            u8 result = value;
            if (value != 0)
            {
                result = option_list_index(value);
            }
            set_option_list_index(target, list, result);
            func_0034DB00(target, 0xFF);
        }
    }
}

/**
 * @brief Forward direction 2 to the window.
 */
void TransferInventorStrip::func_slot74()
{
    func_slotf8(2);
}

/**
 * @brief Forward direction 3 to the window.
 */
void TransferInventorStrip::func_slot70()
{
    func_slotf8(3);
}

/**
 * @brief Clear the selected option and restore the active view.
 * @return Always two.
 */
s32 TransferInventorStrip::func_slotb4()
{
    if (unkc4 != 0)
    {
        item_creation_advance_inventor_transfer(unkc4, -1);
    }
    if (unkc8 != 0)
    {
        func_0023CEA0(unkc8, 0);
    }
    if (unkcc != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(unkcc);
    }
    return 2;
}

/**
 * @brief Select the active view and apply its selected option.
 * @return Always one.
 */
s32 TransferInventorStrip::func_slotb0()
{
    if (unkcc != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(unkcc);
    }
    if (unkc8 != 0 && unkc4 != 0)
    {
        u8 list = unka8;
        u8 value = option_list_value(unkc4, list, selected_option_index(unkc8));
        item_creation_advance_inventor_transfer(unkc4, value);
    }
    return 1;
}

/**
 * @brief Refresh the six resource displays from their current option list.
 * @param object Option display to refresh.
 */
void func_0034D340(TransferInventorStrip* object)
{
    if (object->unkc4 != 0)
    {
        u16 slot;
        u8 count;
        void* allocation;
        s32 index;
        u8 selected;
        u8 status;
        if (object->unka8 == 1)
        {
            count = object->unkc4->unk58;
        }
        else
        {
            count = object->unkc4->unk59;
        }
        object->unka9 = count;
        slot = 0;
        selected = object->unkc4->unk58;
        status = object->unkc4->unk129;
        for (index = 0; index < 6; index++)
        {
            u8 list = object->unka8;
            FieldResourceRecord* record;
            if (list == 2 && (status < 2 || selected == object->unka9))
            {
                allocation = func_002D3D80(D_001B643C->unk20, 0);
                record = func_002D3CC0(D_001B643C->unk20, 16);
            }
            else
            {
                u8 value = option_list_value(object->unkc4, list, (u16)index);
                if (value == 0)
                {
                    allocation = func_002D3D80(D_001B643C->unk20, 0);
                    record = func_002D3CC0(D_001B643C->unk20, 16);
                }
                else
                {
                    u32 resource_index = item_resource_index(value);
                    slot = resource_index;
                    allocation = func_002D3D80(D_001B643C->unk20, (u8)resource_index);
                    record = func_002D3CC0(D_001B643C->unk20, 81);
                }
            }
            object->unkac[index]->unkd0 = slot;
            object->unkac[index]->func_002D5CF0(allocation, record, 0);
        }
    }
}


void func_0034D980(InventorTransferWindow* object, u8 option)
{
    if (object->selection_state != 0)
    {
        if (option == 0xFF)
        {
            option = object->workshop_selection->unk6c;
        }
        switch (object->selection_state->unk129)
        {
        case 0:
        case 1:
            item_creation_build_transfer_inventor_list(object->selection_state, option, 1);
            item_creation_refresh_team_and_transfer_windows(object->selection_state, 6);
            break;
        case 2:
        case 3:
            item_creation_build_transfer_inventor_list(object->selection_state, option, 2);
            item_creation_refresh_team_and_transfer_windows(object->selection_state, 7);
            break;
        }
    }
}

void func_0034DA30(InventorTransferWindow* object)
{
    object->source_workshop_name->unk3f = 0;
    for (s32 index = 0; index < 8; index++)
    {
        object->source_facility_labels[index]->unk3f = 0;
    }
    for (s32 index = 0; index < 3; index++)
    {
        object->source_inventor_widgets[index]->unk3f = 0;
    }
    object->destination_workshop_name->unk3f = 0;
    for (s32 index = 0; index < 8; index++)
    {
        object->destination_facility_labels[index]->unk3f = 0;
    }
    for (s32 index = 0; index < 3; index++)
    {
        object->destination_inventor_widgets[index]->unk3f = 0;
    }
}

/**
 * @brief Test whether a runtime option code selects one of the 38 records.
 * @param option One-based option code.
 * @return True for a valid option record.
 */
static inline bool runtime_option_valid(u8 option)
{
    return option >= 1 && option < 39;
}
/**
 * @brief Return the runtime record selected by an option code.
 * @param state State containing the runtime option records.
 * @param option One-based option code.
 * @return Selected record, or null for an invalid code.
 */
static inline ItemCreationInventorRecord* runtime_option_record(ItemCreationRuntimeData* state, u8 option)
{
    if (runtime_option_valid(option))
    {
        return &state->inventors[option - 1];
    }
    return 0;
}

/**
 * @brief Show a talent value on a number widget.
 * @param display Number widget.
 * @param talent Talent value.
 */
static inline void set_talent_value(LibObject174F20* display, u32 talent)
{
    display->unkfc = talent;
    display->unk3c = 1;
}

/**
 * @brief Read a workshop's installed-facility mask.
 * @param state Selection state.
 * @param workshop_id Valid one-based workshop ID from one through twelve.
 * @return Installed creation-facility mask.
 */
static inline u16 workshop_facility_mask(ItemCreationSelectedDisplayState* state, u8 workshop_id)
{
    return state->workshop_facility_masks[workshop_id - 1];
}
/**
 * @brief Read the source or destination workshop ID.
 * @param object Inventor transfer window.
 * @param group Zero for the source workshop, one for the destination.
 * @return Workshop ID.
 */
static inline u8 transfer_workshop_id(InventorTransferWindow* object, s32 group)
{
    return group == 0 ? object->source_workshop_id : object->destination_workshop_id;
}
/**
 * @brief Store the source or destination workshop ID.
 * @param object Inventor transfer window.
 * @param group Zero for the source workshop, one for the destination.
 * @param value Workshop ID.
 */
static inline void set_transfer_workshop_id(InventorTransferWindow* object, s32 group, u8 value)
{
    if (group == 0)
    {
        object->source_workshop_id = value;
    }
    else
    {
        object->destination_workshop_id = value;
    }
}
/**
 * @brief Return the source or destination workshop title.
 * @param object Inventor transfer window.
 * @param group Zero for the source workshop, one for the destination.
 * @return Title widget.
 */
static inline LibObject178750* transfer_workshop_title(InventorTransferWindow* object, s32 group)
{
    return group == 0 ? object->source_workshop_name : object->destination_workshop_name;
}
/**
 * @brief Return one of a workshop's facility labels.
 * @param object Inventor transfer window.
 * @param group Zero for the source workshop, one for the destination.
 * @param index Label index.
 * @return Label widget.
 */
static inline LibObject178750* transfer_facility_label(InventorTransferWindow* object, s32 group, s32 index)
{
    return group == 0 ? object->source_facility_labels[index] : object->destination_facility_labels[index];
}
/**
 * @brief Show a facility label, bright when that facility is installed.
 * @param object Option window.
 * @param group Zero for the source workshop, one for the destination.
 * @param index Label index.
 * @param flags Enabled-label mask.
 */
static inline void show_transfer_facility(InventorTransferWindow* object, s32 group, s32 index, u16 flags)
{
    transfer_facility_label(object, group, index)->unk3f = 1;
    if (flags & (1 << index))
    {
        transfer_facility_label(object, group, index)->set_color(ITEM_CREATION_COLOR_BRIGHT);
    }
    else
    {
        transfer_facility_label(object, group, index)->set_color(ITEM_CREATION_COLOR_DIM);
    }
}
/**
 * @brief Refresh a transfer workshop's title and installed-facility labels.
 * @param object Option window.
 * @param stage Current selection stage.
 * @param group Zero for the source workshop, one for the destination.
 * @param selected Workshop ID to store at the group's selection stage, or zero.
 */
static inline void update_transfer_workshop(InventorTransferWindow* object, s32 stage, s32 group, u8 selected)
{
    if (stage >= 2 * group)
    {
        if (selected && stage == 2 * group)
        {
            set_transfer_workshop_id(object, group, selected);
        }
        void* associated = object->func_slot54();
        func_4C6DF0(transfer_workshop_title(object, group), associated, transfer_workshop_id(object, group) + 0x3520, 0);
        transfer_workshop_title(object, group)->unk3f = 1;
        u16 flags = workshop_facility_mask(object->selection_state, transfer_workshop_id(object, group));
        show_transfer_facility(object, group, 0, flags);
        show_transfer_facility(object, group, 1, flags);
        show_transfer_facility(object, group, 2, flags);
        show_transfer_facility(object, group, 3, flags);
        show_transfer_facility(object, group, 4, flags);
        show_transfer_facility(object, group, 5, flags);
        show_transfer_facility(object, group, 6, flags);
        show_transfer_facility(object, group, 7, flags);
    }
}
/** @brief Test the accepted one-based skill-code range. @param channel Skill code. @return Whether it is one through nine. */
static inline u8 skill_code_in_range(u8 channel)
{
    return channel > 0 && channel < 10;
}
/**
 * @brief Read the source or destination inventor ID.
 * @param object Inventor transfer window.
 * @param group Zero for the source workshop, one for the destination.
 * @return Inventor ID.
 */
static inline u8 transfer_inventor_id(InventorTransferWindow* object, s32 group)
{
    return group == 0 ? object->source_inventor_id : object->destination_inventor_id;
}
/**
 * @brief Return an inventor name, skill label, or talent widget.
 * @param object Inventor transfer window.
 * @param group Zero for the source workshop, one for the destination.
 * @param index Display index.
 * @return Display widget.
 */
static inline LibClass174EF0* transfer_inventor_widget(InventorTransferWindow* object, s32 group, s32 index)
{
    return group == 0 ? object->source_inventor_widgets[index] : object->destination_inventor_widgets[index];
}
/**
 * @brief Read the selected inventor's specialty talent.
 * @param state Selection state.
 * @param selected_inventor_id Inventor ID.
 * @return Specialty talent, or zero without a specialty.
 */
static inline u8 selected_inventor_talent(ItemCreationSelectedDisplayState* state, u8 selected_inventor_id)
{
    u8 result = 0;
    if (D_001B64F8 != 0)
    {
        ItemCreationInventorRecord* record = runtime_option_record(D_001B64F8, selected_inventor_id);
        if (record != 0)
        {
            u8 skill_code = item_creation_inventor_skill_message(state, inventor_option_code_from_id(selected_inventor_id)) - 0x3457;
            u8 talent = 0;
            if (skill_code_in_range(skill_code))
            {
                u8 inventor_id = record->inventor_id;
                if (is_party_inventor(inventor_id))
                {
                    talent = party_talent_record(inventor_id - 29)->talents[skill_code - 1];
                }
                else
                {
                    const ItemCreationInventorTalent* single = &D_501DA0[inventor_id - 1];
                    if (skill_code == single->skill)
                    {
                        talent = single->talent;
                    }
                }
            }
            result = talent;
        }
    }
    return result;
}
/**
 * @brief Refresh an inventor's name, skill and talent once its selection stage is reached.
 * @param object Option window.
 * @param stage Current selection stage.
 * @param group Zero for the source workshop, one for the destination.
 */
static inline void update_transfer_inventor(InventorTransferWindow* object, s32 stage, s32 group)
{
    if (stage >= 2 * group + 1)
    {
        s32 raw_code = transfer_inventor_id(object, group);
        if (raw_code != 0)
        {
            u8 code = raw_code;
            void* associated = object->func_slot54();
            func_4C6DF0(static_cast<LibObject178750*>(transfer_inventor_widget(object, group, 0)), associated, code + 0x3584, 0);
            transfer_inventor_widget(object, group, 0)->unk3f = 1;
        }
        else
        {
            transfer_inventor_widget(object, group, 0)->unk3f = 0;
        }
        s32 raw_detail = transfer_inventor_id(object, group);
        if (raw_detail != 0)
        {
            u8 code = raw_detail;
            u16 text = item_creation_inventor_skill_message(object->selection_state, inventor_option_code_from_id(code));
            void* associated = object->func_slot54();
            func_4C6DF0(static_cast<LibObject178750*>(transfer_inventor_widget(object, group, 1)), associated, text, 0);
            transfer_inventor_widget(object, group, 1)->unk3f = 1;
            s32 raw_inventor = transfer_inventor_id(object, group);
            u8 talent = selected_inventor_talent(object->selection_state, raw_inventor);
            set_talent_value(static_cast<LibObject174F20*>(transfer_inventor_widget(object, group, 2)), talent);
            transfer_inventor_widget(object, group, 2)->unk3f = 1;
        }
    }
}
/**
 * @brief Refresh the source and destination workshops and inventor details.
 * @param object Inventor transfer window.
 * @param option Workshop ID to store, or 0xFF for the current selection.
 */
extern "C" void func_0034DB00(InventorTransferWindow* object, u8 option)
{
    func_0034DA30(object);
    if (option == 0xFF)
    {
        option = object->workshop_selection->unk6c;
    }
    u32 stage = object->selection_state->unk129;
    update_transfer_workshop(object, stage, 0, option);
    update_transfer_inventor(object, stage, 0);
    update_transfer_workshop(object, stage, 1, option);
    update_transfer_inventor(object, stage, 1);
    if (option == 0xFF)
    {
        func_0034D980(object, option);
    }
}

/** @brief Move the transfer selector and refresh both workshop details. @param direction Direction code. */
void InventorTransferWindow::func_slotf8(u16 direction)
{
    ItemCreationSelection* selection;
    const float* position;
    s32 index;
    u8 selected;

    if (unk15c != 0 && unk15c->unk35 != 0)
    {
        selection = &unkdc;
        index = func_003696B0(selection, direction);
        if (index <= 0)
        {
            position = 0;
        }
        else if (index > 12)
        {
            position = 0;
        }
        else
        {
            position = selection->unk00[index - 1].unk00;
        }
        unk15c->func_00466E40(position[0], position[1], 0.05f);
        func_002CFE40(D_001B643C->unk10, 0);
    }
    selected = workshop_selection->unk6c;
    func_0034DB00(this, selected);
    func_0034D980(this, selected);
}

/**
 * @brief Forward direction 2 to the window.
 */
void InventorTransferWindow::func_slot74()
{
    func_slotf8(2);
}

/**
 * @brief Forward direction 4 to the window.
 */
void InventorTransferWindow::func_slot70()
{
    func_slotf8(4);
}

/**
 * @brief Forward direction 3 to the window.
 */
void InventorTransferWindow::func_slot6c()
{
    func_slotf8(3);
}

/**
 * @brief Forward direction 1 to the window.
 */
void InventorTransferWindow::func_slot68()
{
    func_slotf8(1);
}

/**
 * @brief Reset the option transfer or return to the primary option window.
 * @return Zero without a selection state, or two otherwise.
 */
s32 InventorTransferWindow::func_slotb4()
{
    ItemCreationSelectedDisplayState* state = selection_state;
    if (state == 0)
    {
        return 0;
    }
    switch (state->unk129)
    {
    case 0:
    {
        item_creation_restore_workshop_assignments(state);
        ItemCreationSelectedDisplayState* count_state = selection_state;
        for (s32 index = 1; index < 28; index++)
        {
            ItemCreationInventorRecord* record = runtime_option_record(D_001B64F8, index);
            if (record != 0 && record->contract_status == 2)
            {
                count_state->unk19b++;
            }
        }
        item_creation_advance_inventor_transfer(selection_state, -1);
        state = selection_state;
        state->unk47 = 0;
        func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
        state = selection_state;
        state->func_00263C70(state->unka0);
        break;
    }
    case 1:
        break;
    case 2:
    {
        state->unk129 = 1;
        TransferInventorStrip* window = static_cast<TransferInventorStrip*>(func_slot44());
        if (window->unkc8 != 0)
        {
            func_0023CEA0(window->unkc8, 1);
        }
        D_001B643C->unk10->unk14->func_00263C70(window);
        item_creation_refresh_team_and_transfer_windows(selection_state, 7);
        unk15c->unk3f = 0;
        break;
    }
    case 3:
        break;
    }
    return 2;
}

/**
 * @brief Apply the selected option and enable the corresponding option window.
 * @return Zero without a state, three for an unchanged alternate selection, or one otherwise.
 */
s32 InventorTransferWindow::func_slotb0()
{
    if (selection_state == 0)
    {
        return 0;
    }
    switch (selection_state->unk129)
    {
    case 0:
    {
        ItemCreationSelection* selection = workshop_selection;
        const float* position = selection->unk00[selection->unk6c - 1].unk00;
        set_transfer_position(unk16c, position[0], position[1]);
        unk16c->unk3f = 1;
        unk15c->unk3f = 0;
        TransferInventorStrip* window = static_cast<TransferInventorStrip*>(func_slot44());
        if (window->unkc8 != 0)
        {
            func_0023CEA0(window->unkc8, 1);
        }
        D_001B643C->unk10->unk14->func_00263C70(window);
        item_creation_advance_inventor_transfer(selection_state, source_workshop_id);
        break;
    }
    case 1:
        break;
    case 2:
    {
        if (destination_workshop_id == selection_state->unk12a)
        {
            return 3;
        }
        TransferInventorStrip* window = static_cast<TransferInventorStrip*>(func_slot4c());
        if (window->unkc8 != 0)
        {
            func_0023CEA0(window->unkc8, 1);
        }
        D_001B643C->unk10->unk14->func_00263C70(window);
        item_creation_advance_inventor_transfer(selection_state, destination_workshop_id);
        break;
    }
    case 3:
        break;
    }
    return 1;
}

/** @brief Destroy the selection window through its base. */
InventorTransferWindow::~InventorTransferWindow()
{
}

/** @brief Initialize the selection window and its display pointers. */
InventorTransferWindow::InventorTransferWindow()
{
    workshop_selection = 0;
    workshop_selection = &unkdc;
    selection_state = 0;
    current_workshop_id = 0;
    destination_workshop_id = 0;
    unk16c = 0;
    current_workshop_name = 0;
    source_workshop_id = 0;
    source_inventor_id = 0;
    source_workshop_name = 0;
    source_inventor_widgets[0] = 0;
    source_inventor_widgets[1] = 0;
    source_inventor_widgets[2] = 0;
    destination_workshop_id = 0;
    destination_inventor_id = 0;
    destination_workshop_name = 0;
    destination_inventor_widgets[0] = 0;
    destination_inventor_widgets[1] = 0;
    destination_inventor_widgets[2] = 0;
    for (s32 index = 0; index < 9; index++)
    {
        source_facility_labels[index] = 0;
        destination_facility_labels[index] = 0;
    }
}

/** @brief Move the optional workshop selection display. @param direction Direction code. */
void ItemCreationClass185A60::func_slotf8(u16 direction)
{
    ItemCreationSelection* selection;
    const float* position;
    s32 index;

    if (unk15c != 0 && unk15c->unk35 != 0)
    {
        selection = &unkdc;
        index = func_003696B0(selection, direction);
        if (index <= 0)
        {
            position = 0;
        }
        else if (index > 12)
        {
            position = 0;
        }
        else
        {
            position = selection->unk00[index - 1].unk00;
        }
        unk15c->func_00466E40(position[0], position[1], 0.05f);
        func_002CFE40(D_001B643C->unk10, 0);
    }
}

/**
 * @brief Create the resource displays for the twelve-option selection grid.
 * @param object Window owning the selection and resource displays.
 * @return Always one.
 */
extern "C" s32 func_0034FA70(ItemCreationClass185A60* object)
{
    func_00369510(&object->unkdc);
    void* allocation = func_002D3D80(D_001B643C->unk20, 13);
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 2);
    if (allocation != 0 && record != 0)
    {
        ItemCreationOptionResourceDisplay* const display = new (0) ItemCreationOptionResourceDisplay;
        display->unkcc = allocation;
        display->unkd0 = 13;
        display->func_002D6440(record, 0.0f, 0.0f);
        display->unk50.unk34 = 0.85f;
        display->unk50.unk30 = 0.85f;
        display->unk3c = 1;
        display->unk34 = 3;
        func_004C6190(object->unk10, display);
    }
    allocation = func_002D3D80(D_001B643C->unk20, 0);
    for (s32 index = 0; index < 12; index++)
    {
        ItemCreationOptionResourceDisplay* const display = new (0) ItemCreationOptionResourceDisplay;
        u8 code = index + 1;
        u8 enabled = selection_enabled(&object->unkdc, code);
        const float* position = option_selection_position(&object->unkdc, code);
        switch (code)
        {
        case 1:
        case 2:
        case 5:
            record = func_002D3CC0(D_001B643C->unk20, 42);
            break;
        case 3:
        case 4:
            record = func_002D3CC0(D_001B643C->unk20, 43);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            record = func_002D3CC0(D_001B643C->unk20, 44);
            break;
        }
        display->unkcc = allocation;
        display->unkd0 = 0;
        display->func_002D6440(record, position[0], position[1] - 6.0f);
        display->unk34 = 3;
        func_004C6190(object->unk10, display);
        if (enabled == 0)
        {
            display->unk3f = 0;
        }
    }
    return 1;
}

s32 func_0034FD50(InventorTransferWindow* object, void* associated)
{
    object->FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    return 1;
}

/**
 * @brief Test whether any of the three result flags is clear.
 * @param state Selection state.
 * @return Whether a result flag is clear.
 */
static inline bool result_flag_missing(const ItemCreationSelectedDisplayState* state)
{
    if (state->unk1b1[0] != 0 && state->unk1b1[1] != 0 && state->unk1b1[2] != 0)
    {
        return false;
    }
    return true;
}

/**
 * @brief Restore the associated window and dispatch the result state.
 * @return Always one.
 */
s32 InadequateLineDialog::func_slotb4()
{
    func_slot20(0);
    void* associated = func_slot44();
    if (associated != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(associated);
    }
    ItemCreationSelectedDisplayState* state = unka8;
    if (state != 0)
    {
        if (result_flag_missing(state) == false)
        {
            DevelopmentCompleteDialog* window = new (0) DevelopmentCompleteDialog;
            state = unka8;
            window->func_slotf4(state->func_00263CC0());
            state = unka8;
            state->func_00263FD0(window);
            state = unka8;
            state->func_00263C70(window);
            func_00112400(D_001B65F8, 8, 0, 0, 127, 64, 0);
        }
        else
        {
            state->unk19a = 1;
        }
    }
    return 1;
}

/**
 * @brief Return the selection state's associated pointer.
 * @param object Selection state.
 * @return Stored pointer.
 */
void* func_0034FF60(ItemCreationSelectedDisplayState* object)
{
    return object->unk34;
}

/**
 * @brief Restore the associated window and dispatch the result state.
 * @return Always one.
 */
s32 InadequateLineDialog::func_slotb0()
{
    func_slot20(0);
    void* associated = func_slot44();
    if (associated != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(associated);
    }
    ItemCreationSelectedDisplayState* state = unka8;
    if (state != 0)
    {
        if (result_flag_missing(state) == false)
        {
            DevelopmentCompleteDialog* window = new (0) DevelopmentCompleteDialog;
            state = unka8;
            window->func_slotf4(state->func_00263CC0());
            state = unka8;
            state->func_00263FD0(window);
            state = unka8;
            state->func_00263C70(window);
            func_00112400(D_001B65F8, 8, 0, 0, 127, 64, 0);
        }
        else
        {
            state->unk19a = 1;
        }
    }
    return 1;
}

/**
 * @brief Select the result window's text resource for its mode.
 * @param object Result window.
 * @param mode Mode to store; zero through two select a resource.
 */
extern "C" void func_003500D0(InadequateLineDialog* object, u8 mode)
{
    if (object->unkb0 != 0)
    {
        object->unkac = mode;
        switch (object->unkac)
        {
        case 0:
            func_4C6DF0(object->unkb0, object->func_slot54(), 0x15FD7, 0);
            break;
        case 1:
            func_4C6DF0(object->unkb0, object->func_slot54(), 0x15FD8, 0);
            break;
        case 2:
            func_4C6DF0(object->unkb0, object->func_slot54(), 0x15FD9, 0);
            break;
        }
    }
}


/**
 * @brief Destroy the window through its Field base.
 */
InadequateLineDialog::~InadequateLineDialog()
{
}

/**
 * @brief Destroy the window through its Field base.
 */
DevelopmentControlPanel::~DevelopmentControlPanel()
{
}

/** @brief Restore the third action row and associated resource window. @return Always two. */
s32 AbortDevelopmentDialog::func_slotb4()
{
    func_slot20(0);
    if (unkac != 0)
    {
        func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkac)), 2);
        if (unkac != 0)
        {
            for (s32 index = 0; index < 3; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(
                    func_0036F230(&unk2c, index)->unk00);
                if (index == 2)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    unkb0->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    ItemCreationNineResourceView* parent = state->unkd8;
    FieldObject23CEA0* marker = parent->unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 128.0f;
        marker->unkae = 1;
        parent->unka8->unk19a = 1;
    }
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 2;
}

/**
 * @brief Read a result group flag.
 * @param state Current selection state.
 * @param group Result group index.
 * @return Stored group flag.
 */
static inline u8 result_group_marker(const ItemCreationSelectedDisplayState* state, u16 group)
{
    return state->unk1c3[group];
}
/**
 * @brief Read a result group code.
 * @param state Current selection state.
 * @param group Result group index.
 * @return Stored group code.
 */
static inline u8 result_group_code(const ItemCreationSelectedDisplayState* state, u16 group)
{
    return state->unk1c0[group];
}
/**
 * @brief Store a result group flag.
 * @param state Current selection state.
 * @param group Result group index.
 * @param marker Flag value to store.
 */
static inline void set_result_group_marker(ItemCreationSelectedDisplayState* state, u8 group, u8 marker)
{
    state->unk1c3[group] = marker;
}
/**
 * @brief Store a result group code.
 * @param state Current selection state.
 * @param group Result group index.
 * @param code Code value to store.
 */
static inline void set_result_group_code(ItemCreationSelectedDisplayState* state, u8 group, u8 code)
{
    state->unk1c0[group] = code;
}

/**
 * @brief Complete selected result slots and restore or open the result window.
 * @return Callback result selected by the current action.
 */
s32 AbortDevelopmentDialog::func_slotb0()
{
    if (unkac == 0)
    {
        return 0;
    }
    switch (unkac->func_0023B3A0())
    {
    case 0:
        func_slot20(0);
        if (unkac != 0)
        {
            func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkac)), 2);
            if (unkac != 0)
            {
                for (s32 index = 0; index < 3; index++)
                {
                    LibObject178750* display = static_cast<LibObject178750*>(
                        func_0036F230(&unk2c, index)->unk00);
                    if (index == 2)
                    {
                        display->set_color(ITEM_CREATION_COLOR_SELECTED);
                        unkb0->func_0023B7E0(display);
                    }
                    else
                    {
                        display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                    }
                }
            }
        }
        for (s32 slot = 0; slot < 3; slot++)
        {
            ItemCreationSelectedDisplayState* state = unka8;
            state->unk1b1[(u8)slot] = 1;
            ItemCreationClass184EF0* target = state->unk1b4[(u8)slot];
            if (target != 0)
            {
                target->func_slot10();
            }
            if (result_flag_missing(unka8) == false)
            {
                for (s32 group = 0; group < 3; group++)
                {
                    unka8->unk1e2[(u16)group][0] = 0;
                    unka8->unk1e2[(u16)group][1] = 0;
                    if (result_group_marker(unka8, group) != 0)
                    {
                        set_result_group_marker(unka8, group, 1);
                    }
                    if (result_group_code(unka8, group) == 8)
                    {
                        set_result_group_code(unka8, group, 0);
                        set_result_group_marker(unka8, group, 0);
                    }
                }
                state = unka8;
                state->unk47 = 1;
                func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
                if (unka8->unk1b4[0] != 0)
                {
                    item_creation_rebuild_line_target(unka8, 0);
                }
                if (unka8->unk1b4[1] != 0)
                {
                    item_creation_rebuild_line_target(unka8, 1);
                }
                if (unka8->unk1b4[2] != 0)
                {
                    item_creation_rebuild_line_target(unka8, 2);
                }
                unka8->unk19a = 0;
            }
        }
        break;
    case 1:
    {
        ItemCreationSelectedDisplayState* state = unka8;
        u8 selected_slot = state->unk1b0;
        if (selected_slot != 0xFF)
        {
            state->unk1b1[selected_slot] = 1;
            ItemCreationClass184EF0* target = state->unk1b4[selected_slot];
            if (target != 0)
            {
                target->func_slot10();
            }
            unka8->unk1b0 = 0xFF;
            func_slot20(0);
            if (unkac != 0)
            {
                func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkac)), 2);
                if (unkac != 0)
                {
                    for (s32 index = 0; index < 3; index++)
                    {
                        LibObject178750* display = static_cast<LibObject178750*>(
                            func_0036F230(&unk2c, index)->unk00);
                        if (index == 2)
                        {
                            display->set_color(ITEM_CREATION_COLOR_SELECTED);
                            unkb0->func_0023B7E0(display);
                        }
                        else
                        {
                            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                        }
                    }
                }
            }
            if (result_flag_missing(unka8) == false)
            {
                DevelopmentCompleteDialog* window = new (0) DevelopmentCompleteDialog;
                window->func_slotf4(unka8->func_00263CC0());
                unka8->func_00263FD0(window);
                unka8->func_00263C70(window);
                func_00112400(D_001B65F8, 8, 0, 0, 127, 64, 0);
                return 0;
            }
            state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
            ItemCreationNineResourceView* parent = state->unkd8;
            FieldObject23CEA0* marker = parent->unk10c;
            if (marker != 0)
            {
                marker->FieldClass151C50::unk30 = 128.0f;
                marker->unkae = 1;
                parent->unka8->unk19a = 1;
            }
            D_001B643C->unk10->unk14->func_00263C70(parent);
        }
        break;
    }
    case 2:
        unka8->unk1b0 = 0xFF;
        func_slotb4();
        return 1;
    default:
        return 0;
    }
    return 1;
}

void func_00350DE0(void* object)
{
}

void func_00350DF0(void* object)
{
}

/** @brief Advance the dialog choices and refresh their colors and target. */
void AbortDevelopmentDialog::func_slot6c()
{
    if (unkac != 0 && (u8)unkac->func_0023B3B0(1) != 1)
    {
        u16 selected = unkac->func_0023B3A0();
        if (unkac != 0)
        {
            s32 index;
            for (index = 0; index < 3; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    unkb0->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
}

/** @brief Move backward through the dialog choices and refresh their colors and target. */
void AbortDevelopmentDialog::func_slot68()
{
    if (unkac != 0 && (u8)unkac->func_0023B3B0(0) != 1)
    {
        u16 selected = unkac->func_0023B3A0();
        if (unkac != 0)
        {
            s32 index;
            for (index = 0; index < 3; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    unkb0->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
}

/**
 * @brief Destroy the window through its Field base.
 */
AbortDevelopmentDialog::~AbortDevelopmentDialog()
{
}

/**
 * @brief Report whether an option container has no pending mode.
 * @param container Option container.
 * @return One when the container mode is zero.
 */
static inline u8 option_container_idle(InventorStatusList* container)
{
    return container->unk4a4 == 0;
}

/** @brief Finish or cancel the option container's pending action while this window is current. */
void InventorStatusWindow::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }
    InventorStatusList* child = unkb8;
    if (child == 0)
    {
        return;
    }
    switch (unkbc)
    {
    case 0:
        break;
    case 1:
        if (option_container_idle(child))
        {
            if (child->unk30c > 0)
            {
                child->unk4a4 = 3;
                child->unk30c = -1;
                child->unk308 = -1;
                child->unk316 = -1;
            }
            else
            {
                child->func_003EF740();
                unkb8 = 0;
                func_slot20(0);
                ItemCreationClass186770* window = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14)->unkd8;
                FieldObject23CEA0* grid = window->unk10c;
                if (grid != 0)
                {
                    grid->FieldClass151C50::unk30 = 128.0f;
                    grid->unkae = 1;
                    window->unka8->unk19a = 1;
                }
                D_001B643C->unk10->unk14->func_00263C70(window);
                unkbc = 0;
            }
        }
        break;
    case 2:
        break;
    }
}

/**
 * @brief Create and queue the option container, or reset its active flag.
 * @param object Option window receiving the container.
 * @param mode One creates the container when absent and inactive; zero resets the flag.
 */
extern "C" void func_00351510(InventorStatusWindow* object, u8 mode)
{
    s32 count = 0;
    switch (mode)
    {
    case 1:
        if (object->unkb8 == 0 && object->unkbc == 0)
        {
            InventorStatusList* container = new (0) InventorStatusList;
            object->unkb8 = container;
            for (s32 index = 0; index < 28; index++)
            {
                if (runtime_option_record(D_001B64F8, static_cast<u8>(index + 1))->contract_status != 0)
                {
                    count++;
                }
            }
            func_00352020(object->unkb8, object->func_slot54(), count);
            func_00465B20(D_001B657C, object->unkb8);
            object->unkbc = 1;
        }
        break;
    case 0:
        object->unkbc = 0;
        break;
    }
}

/** @brief Initialize the container and its widget aggregate. */
ItemCreationClass184F60::ItemCreationClass184F60()
{
}

#include "overlays/citemcreation/item_display_inlines.h"

/**
 * @brief Create the row displays and selection grid.
 * @param associated Text source passed to the window base.
 * @return One after setup completes.
 */
s32 WorkshopInventorStrip::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 300.0f, 17);
    for (s32 index = 0; index < 4; index++)
    {
        ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
        switch (index)
        {
        case 0:
            func_421170(frame, 0.0f, 0.0f, 440.0f, 3.0f);
            break;
        case 1:
            func_421170(frame, 0.0f, 80.0f, 440.0f, 3.0f);
            break;
        case 2:
            func_421170(frame, 0.0f, 0.0f, 3.0f, 80.0f);
            break;
        case 3:
            func_421170(frame, 439.0f, 0.0f, 3.0f, 82.0f);
            break;
        }
        func_420D20(frame, 0x808050);
        func_004C6190(unk10, frame);
    }
    void* payload = func_002D3D80(D_001B643C->unk20, 0);
    float x = 0.0f;
    for (s32 index = 0; index < 6; index++)
    {
        x += 8.0f;
        ItemCreationOptionResourceDisplay* display = new (0) ItemCreationOptionResourceDisplay;
        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 16);
        display->unkcc = payload;
        display->unkd0 = 0;
        display->func_002D6440(record, x + 64.0f * (index % 6), 8.0f);
        func_004C6190(unk10, display);
        inventor_portraits[index] = display;
    }
    inventor_grid = new (0) FieldObject23CEA0;
    inventor_grid->func_0023CE80(6, 1);
    inventor_grid->func_0023CE60(72.0f, 0.0f);
    inventor_grid->unkF2 = 0;
    inventor_grid->unk119 = 1;
    inventor_grid->func_0023CF50(0, 36.0f, 320.0f);
    func_0023CEA0(inventor_grid, 0);
    func_0036F040(&unk74, inventor_grid);
    func_0034A1E0(this, 0);
    return 1;
}

/**
 * @brief Create the action panel and its frame widgets.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 DevelopmentControlPanel::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 0.0f, 60.0f, 18);
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0(16.0f, 12.0f, 440.0f, 208.0f);
    func_004C6190(unk10, frame);
    LibClass178630* panel = new (0) LibClass178630(0, 0.0f, 0.0f, 472.0f, 220.0f, 16.0f);
    LibWidgetColors4C5590 colors = {0};
    colors.values[0] = 0xF8C4B4;
    colors.values[1] = 0xF8C4B4;
    colors.values[2] = 0xF8C4B4;
    colors.values[3] = 0xF8C4B4;
    func_4C5590(panel, &colors);
    func_004C6190(unk10, panel);
    frame = new (0) ItemCreationClass1746A0(1);
    func_004C6190(unk10, frame);
    return 1;
}

/**
 * @brief Create the three result actions, selector, and marker.
 * @param associated Text source associated with the window.
 * @return Always one.
 */
s32 AbortDevelopmentDialog::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 64.0f, 150.0f, 15);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 512.0f, 188.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(0.0f, 12.0f, 512.0f, 24.0f, (s32)associated, 0x15FBD, 1);
    heading->unk9c = 1;
    heading->unk3c = 1;
    func_004C6190(unk10, heading);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 66.0f, 488.0f, 3.0f);
    func_420D20(frame, ITEM_CREATION_COLOR_BRIGHT);
    func_004C6190(unk10, frame);
    for (s32 index = 0; index < 3; index++)
    {
        LibObject178750* display = new (0) LibObject178750;
        display->func_004C7FE0(164.0f, 82.0f + 30.0f * index, 0.0f, 0.0f, (s32)associated, 0x15FBA + index, 0);
        func_004C6190(unk10, display);
        func_0036F1A0(&unk2c, display);
    }
    unkac = new (0) FieldClass153130;
    unkac->func_0023B530(1, 3, 1, 2, 1, 164.0f, 94.0f, 0.0f, 30.0f);
    func_004C6190(unk10, unkac);
    LibObject178750* target = static_cast<LibObject178750*>(func_0036F230(&unk2c, 2)->unk00);
    unkb0 = new (0) FieldClass153170;
    unkb0->func_0023B850(target, ITEM_CREATION_COLOR_SELECTED);
    func_004C6190(unk10, unkb0);
    func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkac)), 2);
    if (unkac != 0)
    {
        for (s32 index = 0; index < 3; index++)
        {
            LibObject178750* display = static_cast<LibObject178750*>(
                func_0036F230(&unk2c, index)->unk00);
            if (index == 2)
            {
                display->set_color(ITEM_CREATION_COLOR_SELECTED);
                unkb0->func_0023B7E0(display);
            }
            else
            {
                display->set_color(ITEM_CREATION_COLOR_BRIGHT);
            }
        }
    }
    return 1;
}

/**
 * @brief Create and attach the option window panel, headings, and frame.
 * @param associated Associated source used for the text slots.
 * @return Always one.
 */
s32 InventorStatusWindow::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 64.0f, 84.0f, 15);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 520.0f, 372.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* text0 = new (0) LibObject178750;
    text0->func_004C7FE0(12.0f, 12.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x15FB2, 1);
    set_text_unk88(text0, -1.0f);
    set_text_unk80(text0, 0.9f);
    text0->set_color(ITEM_CREATION_COLOR_ASSIGNED);
    func_004C6190(unk10, text0);
    LibObject178750* text1 = new (0) LibObject178750;
    text1->func_004C7FE0(225.0f, 12.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x15FB5, 1);
    set_text_unk88(text1, -1.0f);
    set_text_unk80(text1, 0.9f);
    text1->set_color(ITEM_CREATION_COLOR_ASSIGNED);
    func_004C6190(unk10, text1);
    LibObject178750* text2 = new (0) LibObject178750;
    text2->func_004C7FE0(340.0f, 12.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x15FB3, 1);
    set_text_unk88(text2, -1.0f);
    set_text_unk80(text2, 0.9f);
    text2->set_color(ITEM_CREATION_COLOR_ASSIGNED);
    func_004C6190(unk10, text2);
    LibObject178750* text3 = new (0) LibObject178750;
    text3->func_004C7FE0(413.0f, 12.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x15FB4, 1);
    set_text_unk88(text3, -1.0f);
    set_text_unk80(text3, 0.9f);
    text3->set_color(ITEM_CREATION_COLOR_ASSIGNED);
    func_004C6190(unk10, text3);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 40.0f, 496.0f, 3.0f);
    func_420D20(frame, ITEM_CREATION_COLOR_DIM);
    func_004C6190(unk10, frame);
    return 1;
}

/**
 * @brief Destroy the window through its Field base.
 */
InventorStatusWindow::~InventorStatusWindow()
{
}

/**
 * @brief Update the option container and dispatch its completed action.
 * @param first First inherited update flag, unused here.
 * @param second Second inherited update flag, unused here.
 * @param third Third inherited update flag, unused here.
 */
void InventorStatusList::func_00412C40(u32 first, u32 second, u32 third)
{
    if (unk4a4 != 0)
    {
        if (func_4135D0(&static_cast<LibClass1723F0&>(*this)))
        {
            s32 result = func_413460(&static_cast<LibClass1723F0&>(*this));
            if (result > 0)
            {
                notify_index(unk30c);
            }
            else if (result < 0)
            {
                func_00112400(D_001B65F8, 2, 0, 0, 127, 64, 0);
                notify_cancel();
            }
            if (result != 0)
            {
                unk4a4 = 0;
                return;
            }
            func_00413020();
            unk4b8 = 1;
        }
        else
        {
            unk4b8 = 0;
        }
        func_413750(&static_cast<LibClass1723F0&>(*this));
        return;
    }
    if (unk318 != 0)
    {
        func_00412C10(unk304);
        unk318 = 0;
    }
}

void func_00351C30(void* object)
{
}

void func_00351C40(void* object)
{
}

/**
 * @brief Arrange the option rows at successive heights.
 * @param y Height of the first row.
 */
void InventorStatusList::func_00412C20(float y)
{
    for (s32 i = 0; i < unk4a0; i++)
    {
        unk410[i]->func_slot14(this, 0.0f, y);
        y += 27.0f;
    }
}

/**
 * @brief Refresh the visible option rows for a starting index.
 * @param index First option index shown by the collection.
 */
void InventorStatusList::func_00412C10(s32 index)
{
    for (s32 row_index = 0; row_index < unk4a0; index++, row_index++)
    {
        ItemCreationClass185030* row = unk410[row_index];
        if (index < unk2f8)
        {
            row->func_slot10(this, index);
            row->func_slot0c(this, 1);
        }
        else
        {
            row->func_slot0c(this, 0);
        }
    }
}

/**
 * @brief Create the option row and attach its four text widgets.
 * @param index Requested row index, unused here.
 * @return Created option row.
 */
ItemCreationClass185030* InventorStatusList::create_row(s32 index)
{
    InventorStatusRow* display = new (0) InventorStatusRow;
    display->unk04.func_004C7FE0(0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    func_004C6190(this, &display->unk04);
    display->unk118.func_004C7FE0(0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    func_004C6190(this, &display->unk118);
    display->unk22c.func_004C7FE0(0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    func_004C6190(this, &display->unk22c);
    display->unk340.func_004C7FE0(0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    func_004C6190(this, &display->unk340);
    return display;
}


/**
 * @brief Configure the option container and create its visible rows.
 * @param object Option container to configure.
 * @param associated Source retained for row text.
 * @param count Number of selectable options.
 * @return One on success, or zero when configuration or allocation fails.
 */
extern "C" s32 func_00352020(InventorStatusList* object, void* associated, s32 count)
{
    object->unk4b4 = associated;
    func_004C6510(object, 5, 0, 0, 64.0f, 128.0f, 0.0f);
    object->unk6c = 0x6FF6;
    float height = 322.0f;
    s32 visible_rows = static_cast<s32>(height) / 27.0f;
    object->unk4a0 = visible_rows + 2;
    if (object->unk4a0 <= 0 || object->unk4a0 > 32)
    {
        return 0;
    }
    if (!func_44B570(&object->unk90, 0.0f, 2.0f, 506.0f, height))
    {
        return 0;
    }
    func_004C6190(object, &object->unk90);
    for (s32 index = 0; index < 32; index++)
    {
        object->unk410[index] = 0;
    }
    for (s32 index = 0; index < object->unk4a0; index++)
    {
        ItemCreationClass185030* row = object->create_row(index);
        if (!row)
        {
            return 0;
        }
        object->unk410[index] = row;
    }
    if (!func_44B510(&object->unke4, 1))
    {
        return 0;
    }
    func_004C6190(object, &object->unke4);
    if (!func_41A930(&object->unk138, 494.0f, 4.0f, 314.0f, 100.0f, 0.0f))
    {
        return 0;
    }
    func_004C6190(object, &object->unk138);
    if (!func_00467360(&object->unk190, 12.0f, 14.0f))
    {
        return 0;
    }
    func_004C6190(object, &object->unk190);
    func_413C00(&static_cast<LibClass1723F0&>(*object), count, 1, visible_rows, 506.0f, 27.0f, 3.0f);
    func_4138E0(&static_cast<LibClass1723F0&>(*object), 0, 0, object->unk2f8);
    object->unk4a4 = 3;
    return 1;
}


/** @brief Destroy the option container and its collection base. */
InventorStatusList::~InventorStatusList()
{
}

/** @brief Initialize the option container and clear its own state. */
InventorStatusList::InventorStatusList()
{
    unk4b0 = 0;
    unk4b4 = 0;
    unk4b8 = 0;
}

/** @brief Destroy the widget aggregate and container. */
ItemCreationClass184F60::~ItemCreationClass184F60()
{
}

/** @brief Destroy the resident widget base. */
ItemCreationClass184F30::~ItemCreationClass184F30()
{
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass1746A0::~ItemCreationClass1746A0()
{
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass1725D0::~ItemCreationClass1725D0()
{
}

/** @brief Destroy the storage base and widget base. */
ItemCreationClass175030::~ItemCreationClass175030()
{
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass172600::~ItemCreationClass172600()
{
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass172870::~ItemCreationClass172870()
{
}

/** @brief Store the transform receiver's halfword code. @param object Transform receiver. @param value Code to store. */
void func_003527C0(LibClass174610* object, u16 value)
{
    object->unk6c = value;
}

/** @brief Destroy the list sentinel and list receiver. */
LibClass178A70::~LibClass178A70()
{
}


#include "overlays/lib/scalar_indicator_inlines.h"

/** @brief Initialize the widget and select kind 2. */
ItemCreationClass184F30::ItemCreationClass184F30()
{
    unk38 = 2;
}


/**
 * @brief Create and attach the selection transfer display.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @return Whether the display was created.
 */
inline s32 ItemCreationClass185A60::create_selection_display_status(float x, float y)
{
    u8 display_created;
    if (unk10 == 0)
    {
        display_created = 0;
    }
    else
    {
        unk15c = new (0) ItemCreationClass175030;
        if (unk15c == 0)
        {
            display_created = 0;
        }
        else
        {
            func_00467360(unk15c, x, y);
            func_004C6190(unk10, unk15c);
            display_created = 1;
        }
    }
    return display_created;
}

/**
 * @brief Create the workshop selector, facility labels and assignment controls.
 * @param associated Associated resource slot.
 * @return Whether the displays were created.
 */
s32 WorkshopSelectionWindow::func_slotf4(void* associated)
{
    this->FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    this->workshop_selection->unk79 = 2;
    this->workshop_selection->unk6c = 1;
    float x;
    float initial_y;
    initial_y = this->workshop_selection->unk00[0].unk00[1];
    x = this->workshop_selection->unk00[0].unk00[0];
    if (!(u8)this->create_selection_display_status(x, initial_y))
    {
        return 0;
    }
    if (!(u8)func_0034FA70(this))
    {
        return 0;
    }
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 448.0f, 0.0f, 160.0f, 224.0f, 88.0f);
    func_004C6190(this->unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(448.0f, 12.0f, 160.0f, 24.0f, (s32)associated, 0x15F94, 1);
    heading->set_mode(1);
    heading->set_vertical_alignment(1);
    heading->set_scale(0.8f, 0.8f);
    heading->set_color(0x808050);
    func_004C6190(this->unk10, heading);
    this->workshop_name = new (0) LibObject178750;
    this->workshop_name->func_004C7FE0(448.0f, 40.0f, 160.0f, 24.0f, (s32)associated, 0x15F95, 1);
    this->workshop_name->set_mode(1);
    this->workshop_name->set_vertical_alignment(1);
    set_text_unk88(this->workshop_name, -1.0f);
    this->workshop_name->set_scale(0.8f, 0.8f);
    func_004C6190(this->unk10, this->workshop_name);
    LibObject178750* option_heading = new (0) LibObject178750;
    option_heading->func_004C7FE0(448.0f, 84.0f, 160.0f, 24.0f, (s32)associated, 0x32D7, 1);
    option_heading->set_mode(1);
    option_heading->set_vertical_alignment(1);
    option_heading->set_scale(0.8f, 0.8f);
    option_heading->set_color(0x808050);
    set_text_unk80(option_heading, 0.5f);
    func_004C6190(this->unk10, option_heading);
    this->register_button = new (0) ItemCreationClass174C40;
    this->back_button = new (0) ItemCreationClass174C40;
    this->view_button = new (0) ItemCreationClass174C40;
    this->register_label = new (0) LibObject178750;
    this->back_label = new (0) LibObject178750;
    this->view_label = new (0) LibObject178750;
    this->register_button->unk34 = 6;
    this->back_button->unk34 = 6;
    this->view_button->unk34 = 6;
    func_4530E0(this->register_button, 0x20, 312.0f, 156.4f);
    this->register_label->func_004C7FE0(344.0f, 160.0f, 0.0f, 0.0f, (s32)associated, 0x15F9A, 1);
    func_4530E0(this->view_button, 0x23, 312.0f, 180.4f);
    this->view_label->func_004C7FE0(344.0f, 184.0f, 0.0f, 0.0f, (s32)associated, 0x15F9B, 1);
    func_4530E0(this->back_button, 0x21, 312.0f, 180.4f);
    this->back_label->func_004C7FE0(344.0f, 184.0f, 0.0f, 0.0f, (s32)associated, 0x15F9C, 1);
    this->register_button->set_scale(0.9f, 0.9f);
    this->back_button->set_scale(0.9f, 0.9f);
    this->view_button->set_scale(0.9f, 0.9f);
    this->register_label->set_scale(0.9f, 0.9f);
    this->back_label->set_scale(0.9f, 0.9f);
    this->view_label->set_scale(0.9f, 0.9f);
    func_004C6190(this->unk10, this->register_button);
    func_004C6190(this->unk10, this->back_button);
    func_004C6190(this->unk10, this->view_button);
    func_004C6190(this->unk10, this->register_label);
    func_004C6190(this->unk10, this->back_label);
    func_004C6190(this->unk10, this->view_label);
    float y = 126.0f;
    for (s32 index = 0; index < 8; index++)
    {
        if (index != 0 && index % 3 == 0)
        {
            y += 4.0f;
        }
        this->facility_labels[index] = new (0) LibObject178750;
        this->facility_labels[index]->func_004C7FE0(458.0f + 50.0f * (index % 3), y + 30.0f * (index / 3),
                                                                     0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_SKILL_LABEL_BASE, 1);
        set_text_unk80(this->facility_labels[index], 0.6f);
        func_004C6190(this->unk10, this->facility_labels[index]);
    }
    if (this->facility_labels[8] != 0)
    {
        this->facility_labels[8]->unk3f = 0;
    }
    if (this->workshop_name != 0)
    {
        func_4C6DF0(this->workshop_name, this->func_slot54(), 0x3521, 0);
    }
    func_0034A7A0(this, 1);
    WorkshopInventorStrip* alternate = static_cast<WorkshopInventorStrip*>(this->func_slot4c());
    if (alternate != 0)
    {
        func_00349DE0(alternate, 1);
    }
    AssignInventorDialog* parent = static_cast<AssignInventorDialog*>(this->func_slot44());
    if (parent != 0)
    {
        parent->unkc5 = 1;
        u32 key = parent->unkc5 + 0x3520;
        if (parent->unkb4 != 0)
        {
            func_4C6DF0(parent->unkb4, parent->func_slot54(), key, 0);
        }
    }
    func_0034A670(this, 1);
    return 1;
}

/**
 * @brief Create the workshop map and source and destination inventor details.
 * @param associated Associated resource slot.
 * @return Whether the window was created.
 */
s32 InventorTransferWindow::func_slotf4(void* associated)
{
    if (selection_state == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    workshop_selection->unk79 = 1;
    current_workshop_id = selection_state->workshop_id;
    workshop_selection->unk6c = current_workshop_id;
    const float* position = option_selection_position(workshop_selection, current_workshop_id);
    float x;
    float initial_y;
    initial_y = position[1];
    x = position[0];
    if (!(u8)create_selection_display_status(x, initial_y))
    {
        return 0;
    }
    if (!(u8)func_0034FA70(this))
    {
        return 0;
    }
    unk16c = new (0) ItemCreationClass175030;
    func_00467360(unk16c, position[0], position[1]);
    set_transfer_opacity(unk16c, 80.0f);
    func_004C6190(unk10, unk16c);
    unk16c->unk3f = 0;
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 444.0f, 0.0f, 168.0f, 396.0f, 88.0f);
    func_004C6190(unk10, panel);
    float y = 12.0f;
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(444.0f, 12.0f, 168.0f, 396.0f, (s32)associated, 0x15F91, 1);
    heading->set_mode(1);
    heading->set_scale(0.8f, 0.8f);
    heading->set_color(0x505080);
    func_004C6190(unk10, heading);
    y += 22.0f;
    current_workshop_name = new (0) LibObject178750;
    (current_workshop_name)->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, current_workshop_id + 0x3520, 1);
    current_workshop_name->set_mode(1);
    current_workshop_name->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, current_workshop_name);
    y += 30.0f;
    LibObject178750* primary_heading = new (0) LibObject178750;
    primary_heading->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x15F92, 1);
    primary_heading->set_mode(1);
    primary_heading->set_scale(0.8f, 0.8f);
    primary_heading->set_color(0x808050);
    func_004C6190(unk10, primary_heading);
    y += 22.0f;
    source_workshop_name = new (0) LibObject178750;
    source_workshop_name->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x15F95, 1);
    source_workshop_name->set_mode(1);
    source_workshop_name->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, source_workshop_name);
    source_workshop_name->unk3f = 0;
    y += 22.0f;
    for (s32 index = 0; index < 8; index++)
    {
        source_facility_labels[index] = new (0) LibObject178750;
        source_facility_labels[index]->func_004C7FE0(458.0f + 50.0f * (index % 3), y + 22.0f * (index / 3), 0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_SKILL_LABEL_BASE, 1);
        source_facility_labels[index]->set_scale(0.7f, 0.7f);
        func_004C6190(unk10, source_facility_labels[index]);
        source_facility_labels[index]->unk3f = 0;
    }
    y += 70.0f;
    source_inventor_widgets[0] = new (0) LibObject178750;
    (static_cast<LibObject178750*>(source_inventor_widgets[0]))->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x3584, 1);
    source_inventor_widgets[0]->set_mode(1);
    source_inventor_widgets[0]->set_scale(0.8f, 0.8f);
    source_inventor_widgets[0]->set_color(0x288080);
    func_004C6190(unk10, source_inventor_widgets[0]);
    source_inventor_widgets[0]->unk3f = 0;
    y += 23.0f;
    source_inventor_widgets[1] = new (0) LibObject178750;
    (static_cast<LibObject178750*>(source_inventor_widgets[1]))->func_004C7FE0(490.0f, y, 0.0f, 0.0f, (s32)associated, ITEM_CREATION_SKILL_LABEL_BASE, 1);
    source_inventor_widgets[1]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, source_inventor_widgets[1]);
    source_inventor_widgets[1]->unk3f = 0;
    source_inventor_widgets[2] = new (0) LibObject174F20;
    func_00464D90(static_cast<LibObject174F20*>(source_inventor_widgets[2]), 99, (s32)associated, 1, 528.0f, y, 38.4f, 19.2f);
    source_inventor_widgets[2]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, source_inventor_widgets[2]);
    source_inventor_widgets[2]->unk3f = 0;
    y += 30.0f;
    LibObject178750* alternate_heading = new (0) LibObject178750;
    (alternate_heading)->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x15F93, 1);
    alternate_heading->set_mode(1);
    alternate_heading->set_scale(0.8f, 0.8f);
    alternate_heading->set_color(0x808050);
    func_004C6190(unk10, alternate_heading);
    y += 22.0f;
    destination_workshop_name = new (0) LibObject178750;
    destination_workshop_name->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x15F95, 1);
    destination_workshop_name->set_mode(1);
    destination_workshop_name->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, destination_workshop_name);
    destination_workshop_name->unk3f = 0;
    y += 22.0f;
    for (s32 index = 0; index < 8; index++)
    {
        destination_facility_labels[index] = new (0) LibObject178750;
        destination_facility_labels[index]->func_004C7FE0(458.0f + 50.0f * (index % 3), y + 22.0f * (index / 3), 0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_SKILL_LABEL_BASE, 1);
        destination_facility_labels[index]->set_scale(0.7f, 0.7f);
        func_004C6190(unk10, destination_facility_labels[index]);
        destination_facility_labels[index]->unk3f = 0;
    }
    y += 70.0f;
    destination_inventor_widgets[0] = new (0) LibObject178750;
    (static_cast<LibObject178750*>(destination_inventor_widgets[0]))->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x3584, 1);
    destination_inventor_widgets[0]->set_mode(1);
    destination_inventor_widgets[0]->set_color(0x288080);
    destination_inventor_widgets[0]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, destination_inventor_widgets[0]);
    destination_inventor_widgets[0]->unk3f = 0;
    y += 23.0f;
    destination_inventor_widgets[1] = new (0) LibObject178750;
    (static_cast<LibObject178750*>(destination_inventor_widgets[1]))->func_004C7FE0(490.0f, y, 0.0f, 0.0f, (s32)associated, ITEM_CREATION_SKILL_LABEL_BASE, 1);
    destination_inventor_widgets[1]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, destination_inventor_widgets[1]);
    destination_inventor_widgets[1]->unk3f = 0;
    destination_inventor_widgets[2] = new (0) LibObject174F20;
    func_00464D90(static_cast<LibObject174F20*>(destination_inventor_widgets[2]), 99, (s32)associated, 1, 528.0f, y, 38.4f, 19.2f);
    destination_inventor_widgets[2]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, destination_inventor_widgets[2]);
    destination_inventor_widgets[2]->unk3f = 0;
    return 1;
}

/**
 * @brief Position the inventor row's four text widgets.
 * @param source Owning row collection; unused.
 * @param x Row horizontal coordinate.
 * @param y Row vertical coordinate.
 */
void InventorStatusRow::func_slot14(LibClass1721F0* source, float x, float y)
{
    unk04.unk18.unk00 = shifted_position(x, 12.0f);
    unk04.unk18.unk04 = y;
    unk04.unk3c = 1;
    unk118.unk18.unk00 = shifted_position(x, 240.0f) - 20.0f;
    unk118.unk18.unk04 = y;
    unk118.unk3c = 1;
    unk22c.unk18.unk00 = shifted_position(x, 345.0f) - 8.0f;
    unk22c.unk18.unk04 = y;
    unk22c.unk3c = 1;
    unk340.unk18.unk00 = shifted_position(x, 412.0f);
    unk340.unk18.unk04 = y;
    unk340.unk3c = 1;
}

/**
 * @brief Find an NPC inventor's talent record.
 * @param index Inventor ID minus one.
 * @return Record at that index.
 */
static inline const ItemCreationInventorTalent* inventor_talent_record(s32 index)
{
    return &D_501DA0[index];
}

/**
 * @brief Build the inventor's creation-skill capability mask.
 * @param inventor_id Inventor ID.
 * @return All nine capability bits for party inventors, otherwise the NPC specialty bit.
 */
static inline u16 inventor_skill_mask(u8 inventor_id)
{
    if (is_party_inventor(inventor_id))
    {
        return 0x1FF;
    }
    return 1 << (inventor_talent_record(inventor_id - 1)->skill - 1);
}

/**
 * @brief Test whether a skill is absent from a capability mask.
 * @param flags Skill capability mask.
 * @param index Skill index.
 * @return True when the skill's bit is clear.
 */
static inline bool skill_missing(u16 flags, s32 index)
{
    return !(flags & (1 << index));
}

/**
 * @brief Show one inventor's name, contract, specialty and work status.
 * @param source Inventor status list supplying the text resource.
 * @param index Position among the inventor records with nonzero contract status.
 */
void InventorStatusRow::func_slot10(LibClass1721F0* source, s32 index)
{
    void* text_source = static_cast<InventorStatusList*>(source)->unk4b4;
    ItemCreationInventorRecord* records[28];
    s32 count = 0;
    for (s32 position = 0; position < 28; position++)
    {
        ItemCreationInventorRecord* record = runtime_option_record(D_001B64F8, static_cast<u8>(position + 1));
        if (record->contract_status != 0)
        {
            records[count++] = record;
        }
    }
    ItemCreationInventorRecord** selected = &records[index];
    func_4C6DF0(&unk04, text_source, (*selected)->inventor_id + 0x3584, 0);
    func_4C6DF0(&unk118, text_source, (*selected)->contract_status + 0x15FB7, 0);
    if ((*selected)->contract_status == 2)
    {
        unk118.set_color(0x505080);
    }
    else
    {
        unk118.set_color(0x805050);
    }
    u8 inventor_id = (*selected)->inventor_id;
    s32 skill_index = 0;
    u16 flags = inventor_skill_mask(inventor_id);
    for (s32 skill = 0; skill < 8; skill++)
    {
        if (!skill_missing(flags, skill))
        {
            skill_index = skill;
            break;
        }
    }
    func_4C6DF0(&unk22c, text_source, skill_index + 0x3458, 0);
    func_4C6DF0(&unk340, text_source, ((*selected)->working != 0) + 0x15FB6, 0);
}

/**
 * @brief Store the row display flag on each text widget.
 * @param source Owning row collection; unused.
 * @param value Flag byte to store.
 */
void InventorStatusRow::func_slot0c(LibClass1721F0* source, u8 value)
{
    unk04.unk3d = value;
    unk118.unk3d = value;
    unk22c.unk3d = value;
    unk340.unk3d = value;
}

/**
 * @brief Calculate the packed allocation checksum.
 * @param record Allocation record to read.
 * @return Calculated checksum.
 */
static inline u16 allocation_checksum(ItemCreationAllocationRecord* record)
{
    return (0x83CF << record->unk0d_shift) ^
        ((record->unk08 + (record->unk00.raw + record->unk04)) ^
         (record->unk02 + (record->unk06 + record->unk0a)));
}
/**
 * @brief Test whether the packed allocation checksum differs.
 * @param record Allocation record to validate.
 * @return True when the stored checksum differs.
 */
static inline bool allocation_invalid(ItemCreationAllocationRecord* record)
{
    return record->unk0e != (u16)((0x83CF << record->unk0d_shift) ^
        ((((const u16*)record)[4] + (((const u16*)record)[0] + ((const u16*)record)[2])) ^
         (((const u16*)record)[1] + (((const u16*)record)[3] + ((const u16*)record)[5]))));
}
/**
 * @brief Read the ten-bit allocation value from a valid record.
 * @param record Allocation record to validate.
 * @return Packed value, or zero when the checksum differs.
 */
static inline u16 allocation_value(ItemCreationAllocationRecord* record)
{
    if (allocation_invalid(record))
    {
        return 0;
    }
    return record->unk00.bits.value;
}
/**
 * @brief Clear the allocation record and initialize its checksum.
 * @param record Allocation record to reset.
 */
static inline void reset_record(ItemCreationAllocationRecord* record)
{
    *(unsigned __int128*)record = 0;
    record->unk0d_shift = func_0010CF80() & 3;
    record->unk0e = allocation_checksum(record);
}
/**
 * @brief Reset the allocation record and apply its category value.
 * @param record Allocation record to configure.
 * @param category Category containing the catalog value.
 */
static inline void configure_record(ItemCreationAllocationRecord* record, const ItemCreationCategoryRecord* category)
{
    reset_record(record);
    func_40D2E0(record, category->unk02 + 1, 0, 0, false, true);
}

/**
 * @brief Test the signed one-based allocation index.
 * @param index Allocation index.
 * @return True for indices from one through three thousand.
 */
static inline bool valid_record_index(s16 index)
{
    return index > 0 && index <= 3000;
}
/**
 * @brief Find an allocation record by its signed halfword index.
 * @param value Index to narrow to a signed halfword.
 * @return Record, or null for an invalid index.
 */
static inline ItemCreationAllocationRecord* allocation_record(s32 value)
{
    ItemCreationRuntimeData* records = D_001B64F8;
    s16 index = value;
    if (valid_record_index(index))
    {
        return &records->records[index - 1];
    }
    return 0;
}
/**
 * @brief Test the one-based category index.
 * @param index Category index.
 * @return True for indices from one through seven hundred fifty.
 */
static inline u8 valid_category_index(u16 index)
{
    return index > 0 && index <= 750;
}
/**
 * @brief Find a category record by its one-based index.
 * @param index Category index.
 * @return Record, or null for an invalid index.
 */
static inline ItemCreationCategoryRecord* category_record(u16 index)
{
    ItemCreationRuntimeData* records = D_001B64F8;
    if (valid_category_index(index))
    {
        return &records->item_types[index - 1];
    }
    return 0;
}

/**
 * @brief Set the allocation code and channel, marking the widget for refresh.
 * @param display Code widget.
 * @param value Allocation code.
 * @param channel Channel identifier.
 */
static inline void set_code(LibObject172410* display, u16 value, u8 channel)
{
    display->unkfc = value;
    display->unkfe = channel;
    display->unk3c = 1;
}

/**
 * @brief Refresh the allocation value, detail codes, and selected display text.
 * @param object Allocation display window.
 */
void func_00352DE0(ItemDetailsWindow* object)
{
    ItemCreationSelectedDisplayState* state = object->unka8;
    if (state == 0)
    {
        return;
    }
    ItemCreationClass184EF0* target = state->unk1b4[(s8)state->unk1b0];
    ItemCreationAllocationRecord temporary __attribute__((aligned(16)));
    ItemCreationAllocationRecord* record = 0;
    switch (target->unk83)
    {
        case 1:
        {
            FieldClass15BB30* category_target = static_cast<FieldClass15BB30*>(target);
            ItemCreationCategoryRecord* category = category_record(category_target->unk3c8);
            reset_record(&temporary);
            configure_record(&temporary, category);
            record = &temporary;
            object->unkb4->unk3f = 1;
            object->unke4->unk3f = 1;
            LibObject174F20* value = object->unkb4;
            value->unkfc = category_target->unk3b0;
            value->unk3c = 1;
            break;
        }
        case 2:
        {
            record = allocation_record(static_cast<FieldClass15BB50*>(target)->unk94);
            object->unkb4->unk3f = 0;
            object->unke4->unk3f = 0;
            break;
        }
        case 3:
        {
            record = allocation_record(static_cast<FieldClass15BB70*>(target)->unke0);
            object->unkb4->unk3f = 0;
            object->unke4->unk3f = 0;
            break;
        }
    }
    func_4C6DF0(object->unkac, object->func_slot54(), (u8)D_001B64F0[allocation_value(record)].unk0b_mode + 0x1B62, 0);
    set_code(object->unkb0, allocation_value(record) + 1, record->unk0c & 0x7F);
    func_4C6DF0(object->unkbc, object->func_slot54(), (u16)(allocation_value(record) + 1) + 0xD6D8, 0);
    for (s32 index = 0; index < 8; index++)
    {
        object->unkc4[index]->unk3f = 0;
    }
    s32 display_index = 0;
    for (s32 index = 0; index < 8; index++)
    {
        u16 value = func_0040D930(record, index);
        if (value != 0 && value != 700)
        {
            LibObject172440* display = object->unkc4[display_index];
            display->unkfc = value;
            display->unk3c = 1;
            object->unkc4[display_index]->unk3f = 1;
            display_index++;
        }
    }
    s32 message = (u16)D_001B64F0[allocation_value(record)].unk10_code + 0x88;
    state = object->unka8;
    if (state->unk19c != 0)
    {
        func_002FD940(state->unk19c);
        state->unk1a8 = 1;
    }
    state->unk1a0 = message;
    state->unk1a4 = 0;
    state = object->unka8;
    state->unk98->func_slot58()->func_0044B110(0, 9, 1200, 0, 0.0f);
    state->unk9c->func_slot58()->func_0044B110(0, 9, 1400, 0, 0.0f);
    state->unkb4->func_slot58()->func_0044B110(0, 9, 1800, 0, 0.0f);
    state->unke4->func_slot58()->func_0044B110(0, 9, 1800, 0, 0.0f);
    state->unkd8->func_slot58()->func_0044B110(0, 9, 2000, 0, 0.0f);
}


/**
 * @brief Restore the selected item views and open the result window when ready.
 * @return Zero after opening the result window, otherwise one.
 */
s32 ItemDetailsWindow::func_slotb0()
{
    func_slot20(0);
    unke8->unkab = 0;
    FieldClass15AE70* alternate = static_cast<FieldClass15AE70*>(func_slot4c());
    if (alternate != 0)
    {
        static_cast<ItemCreationControlHelp*>(alternate)->func_003598E0(3, 1);
    }
    ItemCreationSelectedDisplayState* state = unka8;
    state->unk98->func_slot58()->func_0044B110(20, 0, 0, 0, 0.0f);
    state->unk9c->func_slot58()->func_0044B110(19, 0, 0, 0, 0.0f);
    state->unkb4->func_slot58()->func_0044B110(18, 0, 0, 0, 0.0f);
    state->unke4->func_slot58()->func_0044B110(18, 0, 0, 0, 0.0f);
    state->unkd8->func_slot58()->func_0044B110(17, 0, 0, 0, 0.0f);
    state = unka8;
    if (state->unk19c != 0)
    {
        func_002FD940(state->unk19c);
        state->unk1a8 = 1;
    }
    state->unk1a4 = 0;
    state->unk1a0 = 0;
    state->unk1ac = 0;
    ItemCreationNineResourceView* window = static_cast<ItemCreationNineResourceView*>(func_slot44());
    FieldObject23CEA0* grid = window->unk10c;
    if (grid != 0)
    {
        grid->FieldClass151C50::unk30 = 128.0f;
        grid->unkae = 1;
        window->unka8->unk19a = 1;
    }
    D_001B643C->unk10->unk14->func_00263C70(window);
    if (result_flag_missing(unka8) == false)
    {
        DevelopmentCompleteDialog* next = new (0) DevelopmentCompleteDialog;
        next->func_slotf4(unka8->func_00263CC0());
        unka8->func_00263FD0(next);
        unka8->func_00263C70(next);
        func_00112400(D_001B65F8, 8, 0, 0, 127, 64, 0);
        return 0;
    }
    return 1;
}

/**
 * @brief Allocate the panel transform and set its third coordinate.
 * @param object Panel widget.
 * @param z Third transform component.
 * @return One on success, or zero if the transform could not be allocated.
 */
extern "C" s32 func_4C4AB0(LibClass178630* object, float z);
/**
 * @brief Initialize an item widget's rectangle and item codes.
 * @param object Item widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @param value Halfword item code.
 * @param variant Byte item variant.
 * @param flag Drawing state flag.
 * @return One on success, or zero if its drawing storage could not be initialized.
 */
extern "C" s32 func_413F70(LibObject172410* object, float x, float y, float width, float height, u16 value, u8 variant, u8 flag);
/**
 * @brief Initialize a detail widget's rectangle and value codes.
 * @param object Detail widget.
 * @param value Halfword value code.
 * @param variant Byte value variant.
 * @param flag Drawing state flag.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero if its drawing storage could not be initialized.
 */
extern "C" s32 func_4143F0(LibObject172440* object, u16 value, u8 variant, u8 flag, float x, float y, float width, float height);
/**
 * @brief Create and configure the Field window's nested display container.
 * @param object Field window receiver.
 * @param associated Object associated with the window.
 * @param first First container configuration value.
 * @param second Second container configuration value.
 * @param third Third container configuration value.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param z Third coordinate.
 * @return One when the container and associated object are present, otherwise zero.
 */
extern "C" s32 func_002CE760(FieldClass15AE70* object, void* associated, s32 first, s32 second, s32 third, float x, float y, float z);
/** @brief Attach a widget to its container. @param object Container. @param child Widget to attach. */
extern "C" void func_4C6190(LibObject178660* object, LibClass178600* child);
/**
 * @brief Set the display depth and mark it for drawing.
 * @param display Drawing display.
 * @param value Depth value.
 */
static inline void set_depth(LibClass174EF0* display, float value)
{
    display->unk88 = value;
    display->unk3c = 1;
}
/** Partial Field runtime reached through D_001B657C. */
struct FieldRuntime
{
    u8 unk00[0x514];
    void* unk514;
    u32 unk518;
    void* unk51c;
    u32 unk520;
};


/**
 * @brief Create the window's panels, text and value displays and register its runtime callback.
 * @param associated Text source associated with the window.
 * @return Always one.
 */
s32 ItemDetailsWindow::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 0xA28, 28.0f, 82.0f, 0.0f);
    unke8 = new (0) LibObject178660;
    func_004C6510(unke8, 5, 0, 0, 28.0f, 82.0f, 0.0f);
    func_00465B20(D_001B657C, static_cast<LibClass174610*>(unke8));
    unkf8 = new (0) LibClass178630;
    func_004C5A80(unkf8, 1, 0.0f, 0.0f, 584.0f, 374.0f, 88.0f);
    func_4C6190(unk10, unkf8);
    func_4C4AB0(unkf8, 1500.0f);
    unkac = new (0) LibObject178750;
    unkb0 = new (0) LibObject172410;
    unkb4 = new (0) LibObject174F20;
    unkb8 = new (0) ItemCreationClass172870;
    unkbc = new (0) LibObject178750;
    unkc0 = new (0) LibObject178750;
    for (s32 index = 0; index < 8; index++)
    {
        unkc4[index] = new (0) LibObject172440;
    }
    unkac->func_004C7FE0(16.0f, 12.0f, 0.0f, 0.0f, (s32)associated, unkec + 0x1B62, 0);
    set_depth(unkac, -1.0f);
    unkac->set_scale(0.8f, 0.8f);
    unkac->set_color(0x805050);
    func_4C6190(unk10, unkac);
    func_413F70(unkb0, 24.0f, 34.0f, 0.0f, 0.0f, (u16)(s32)associated, unkee + 0xC350, 0);
    set_depth(unkb0, -1.0f);
    unkb0->set_scale(1.2f, 1.2f);
    func_4C6190(unk10, unkb0);
    func_00464D90(unkb4, 99, 0, 0, 430.0f, 16.0f, 100.0f, 30.0f);
    unkb4->set_scale(2.0f, 2.0f);
    unkb4->set_color(0x508050);
    func_4C6190(unk10, unkb4);
    unke4 = new (0) LibObject178750;
    unke4->func_004C7FE0(550.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x15FC4, 0);
    unke4->set_scale(0.9f, 0.9f);
    func_4C6190(unk10, unke4);
    func_421170(unkb8, 8.0f, 69.0f, 568.0f, 3.0f);
    ItemCreationClass172870* frame = unkb8;
    frame->unk50 = 0x606060;
    frame->unk3c = 1;
    func_4C6190(unk10, unkb8);
    unkbc->func_004C7FE0(24.0f, 80.0f, 534.0f, 66.0f, (s32)associated, unkee + 0xD6D8, 0);
    unkbc->set_mode(0);
    unkbc->set_vertical_alignment(1);
    set_depth(unkbc, -1.0f);
    unkbc->set_scale(0.9f, 0.9f);
    func_4C6190(unke8, unkbc);
    unkc0->func_004C7FE0(16.0f, 155.0f, 0.0f, 0.0f, (s32)associated, 0x15FE0, 0);
    unkc0->set_scale(0.8f, 0.8f);
    unkc0->set_color(0x805050);
    set_depth(unkc0, -1.0f);
    func_4C6190(unk10, unkc0);
    FieldRuntime* runtime = D_001B657C;
    runtime->unk51c = associated;
    runtime->unk520 = 0x11171;
    for (s32 index = 0; index < 8; index++)
    {
        func_4143F0(unkc4[index], 0, 1, 0, 26.0f, 178.0f + 24.0f * index, 0.0f, 0.0f);
        set_depth(unkc4[index], -1.0f);
        unkc4[index]->set_scale(0.8f, 0.8f);
        func_4C6190(unke8, unkc4[index]);
    }
    float heights[5] = {52.0f, 104.0f, 208.0f, 312.0f, 342.0f};
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(12.0f, heights[4] - 8.0f, 555.0f, 24.0f, (s32)associated, 0x1B74, 0);
    footer->set_scale(0.9f, 0.9f);
    footer->set_mode(2);
    func_4C6190(unke8, footer);
    return 1;
}

/** @brief Release the container and base window contents. */
void ItemDetailsWindow::func_slot0c()
{
    unke8->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

/**
 * @brief Detach the owned panel and destroy the selected item window.
 */
ItemDetailsWindow::~ItemDetailsWindow()
{
    if (unkf8 != 0)
    {
        func_004C4A90(unkf8);
    }
}

/**
 * @brief Initialize the selected item window and its display pointers.
 * @param object Selection state kept by the window.
 */
ItemDetailsWindow::ItemDetailsWindow(ItemCreationSelectedDisplayState* object)
{
    unkac = 0;
    unkb0 = 0;
    unkb4 = 0;
    unkb8 = 0;
    unkbc = 0;
    unkc0 = 0;
    unkc4[0] = 0;
    unkc4[1] = 0;
    unkc4[2] = 0;
    unkc4[3] = 0;
    unkc4[4] = 0;
    unkc4[5] = 0;
    unkc4[6] = 0;
    unkc4[7] = 0;
    unkec = 0;
    unkee = 0;
    unkf0 = 0;
    unkf4 = 0;
    unka8 = object;
    unkf8 = 0;
    FieldClass15AE70();
}

/** @brief Close the popup and restore its associated window marker. @return Always one. */
s32 MissingMaterialsDialog::func_slotb0()
{
    D_001B643C->unk10->unk14->func_00263F50(this);
    AssignedInventorGrid* parent = static_cast<AssignedInventorGrid*>(func_slot44());
    FieldObject23CEA0* marker = parent->unkb4;
    marker->FieldClass151C50::unk30 = 128.0f;
    marker->unkae = 1;
    marker = parent->unkb4;
    if (marker != 0)
    {
        marker->unkad = 1;
    }
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 1;
}

/** @brief Create the popup display and attach its widgets. @param associated Associated source. @return Always one. */
s32 MissingMaterialsDialog::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 90.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 436.0f, 160.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x1B6C, 1);
    func_004C6190(unk10, heading);
    LibObject178750* description = new (0) LibObject178750;
    description->func_004C7FE0(36.0f, 40.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x1B6F, 0);
    func_004C6190(unk10, description);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 100.0f, 411.0f, 4.0f);
    frame->unk50 = 0x606060;
    frame->unk3c = 1;
    func_004C6190(unk10, frame);
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(315.0f, 115.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x1B73, 0);
    footer->set_scale(0.9f, 0.9f);
    func_004C6190(unk10, footer);
    return 1;
}

/**
 * @brief Return to the associated window.
 * @return Always one.
 */
s32 InsufficientFolDialog::func_slotb0()
{
    D_001B643C->unk10->unk14->func_00263F50(this);
    AssignedInventorGrid* parent = static_cast<AssignedInventorGrid*>(func_slot44());
    if (parent->unkb4 != 0)
    {
        parent->unkb4->unkad = 1;
    }
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 1;
}

/**
 * @brief Create and attach the popup panel, text, and frame.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 InsufficientFolDialog::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 80.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 470.0f, 160.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* display = new (0) LibObject178750;
    display->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x1B6C, 1);
    func_004C6190(unk10, display);
    display = new (0) LibObject178750;
    display->func_004C7FE0(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x1B6E, 0);
    func_004C6190(unk10, display);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 100.0f, 446.0f, 4.0f);
    frame->unk50 = 0x606060;
    frame->unk3c = 1;
    func_004C6190(unk10, frame);
    display = new (0) LibObject178750;
    display->func_004C7FE0(340.0f, 115.0f, 0.0f, 0.0f, (s32)associated, 0x1B73, 0);
    display->unk84 = 0.9f;
    display->unk80 = 0.9f;
    display->unk3c = 1;
    func_004C6190(unk10, display);
    return 1;
}

/**
 * @brief Clear the two stored values for one result group.
 * @param state Current selection state.
 * @param group Result group index.
 */
static inline void reset_result_group(ItemCreationSelectedDisplayState* state, u16 group)
{
    s16* pair = state->unk1e2[group];
    pair[0] = 0;
    pair[1] = 0;
}
/**
 * @brief Restore the resource window and reset completed result groups.
 * @return Always one.
 */
s32 DevelopmentCompleteDialog::func_slotb0()
{
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    state->func_00263F50(this);
    ItemCreationNineResourceView* window = state->unkd8;
    FieldObject23CEA0* grid = window->unk10c;
    if (grid != 0)
    {
        grid->FieldClass151C50::unk30 = 128.0f;
        grid->unkae = 1;
        window->unka8->unk19a = 1;
    }
    state->func_00263C70(window);
    if (result_flag_missing(state) == false)
    {
        for (s32 index = 0; index < 3; index++)
        {
            reset_result_group(state, index);
            if (result_group_marker(state, index) != 0)
            {
                set_result_group_marker(state, index, 1);
            }
            if (result_group_code(state, index) == 8)
            {
                set_result_group_code(state, index, 0);
                set_result_group_marker(state, index, 0);
            }
        }
        state->unk47 = 1;
        func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
        if (state->unk1b4[0] != 0)
        {
            item_creation_rebuild_line_target(state, 0);
        }
        if (state->unk1b4[1] != 0)
        {
            item_creation_rebuild_line_target(state, 1);
        }
        if (state->unk1b4[2] != 0)
        {
            item_creation_rebuild_line_target(state, 2);
        }
        state->unk19a = 0;
    }
    return 1;
}

/**
 * @brief Restore the selected display and open the result window when ready.
 * @return Zero after opening the result window, otherwise one.
 */
s32 LineFailureDialog::func_slotb0()
{
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    state->func_00263F50(this);
    ItemCreationNineResourceView* window = state->unkd8;
    FieldObject23CEA0* grid = window->unk10c;
    if (grid != 0)
    {
        grid->FieldClass151C50::unk30 = 128.0f;
        grid->unkae = 1;
        window->unka8->unk19a = 1;
    }
    state->func_00263C70(window);
    if (result_flag_missing(state) == false)
    {
        DevelopmentCompleteDialog* next = new (0) DevelopmentCompleteDialog;
        next->func_slotf4(state->func_00263CC0());
        state->func_00263FD0(next);
        state->func_00263C70(next);
        func_00112400(D_001B65F8, 8, 0, 0, 127, 64, 0);
        return 0;
    }
    return 1;
}

/**
 * @brief Refresh and restore the selected item window and its display flag.
 * @return Always one.
 */
s32 InventionSuccessDialog::func_slotb0()
{
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    state->func_00263F50(this);
    ItemDetailsWindow* window = state->unke0;
    func_00352DE0(window);
    window->func_slot20(1);
    window->unke8->unkab = 1;
    D_001B643C->unk10->unk14->func_00263C70(window);
    return 1;
}

/** @brief Advance the dialog choices and refresh their colors and target. */
void ItemSubmissionDialog::func_slot6c()
{
    if (unkac != 0 && (u8)unkac->func_0023B3B0(1) != 1)
    {
        u16 selected = unkac->func_0023B3A0();
        if (unkac != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    unkb0->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
}

/** @brief Move backward through the dialog choices and refresh their colors and target. */
void ItemSubmissionDialog::func_slot68()
{
    if (unkac != 0 && (u8)unkac->func_0023B3B0(0) != 1)
    {
        u16 selected = unkac->func_0023B3A0();
        if (unkac != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    unkb0->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
}

/** @brief Restore the two display colors and associated resource window. @return Always two. */
s32 ItemSubmissionDialog::func_slotb4()
{
    func_slot20(0);
    func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkac)), 1);
    if (unkac != 0)
    {
        s32 index;
        for (index = 0; index < 2; index++)
        {
            LibObject178750* display = static_cast<LibObject178750*>(
                func_0036F230(&unk2c, index)->unk00);
            if (index == 1)
            {
                display->set_color(0x288080);
                unkb0->func_0023B7E0(display);
            }
            else
            {
                display->set_color(0x808080);
            }
        }
    }
    if (unka8 != 0 && unka8->unkb4 != 0)
    {
        static_cast<ItemCreationControlHelp*>(unka8->unkb4)->func_003598E0(3, 1);
    }
    ItemCreationNineResourceView* parent = static_cast<ItemCreationNineResourceView*>(func_slot44());
    FieldObject23CEA0* marker = parent->unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 128.0f;
        marker->unkae = 1;
        parent->unka8->unk19a = 1;
    }
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 2;
}

/** @brief Apply the selected action or restore the resource window. @return Action status. */
s32 ItemSubmissionDialog::func_slotb0()
{
    if (unkac == 0)
    {
        return 0;
    }
    switch (unkac->func_0023B3A0())
    {
        case 0:
        {
            func_slot20(0);
            func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkac)), 1);
            if (unkac != 0)
            {
                s32 index;
                for (index = 0; index < 2; index++)
                {
                    LibObject178750* display = static_cast<LibObject178750*>(
                        func_0036F230(&unk2c, index)->unk00);
                    if (index == 1)
                    {
                        display->set_color(0x288080);
                        unkb0->func_0023B7E0(display);
                    }
                    else
                    {
                        display->set_color(0x808080);
                    }
                }
            }
            ItemCreationSelectedDisplayState* state = unka8;
            u8 index = state->unk1b0;
            state->unk1b1[index] = 1;
            ItemCreationClass184EF0* target = state->unk1b4[index];
            if (target != 0)
            {
                target->func_slot0c();
            }
            target = unka8->unk1b4[(s8)unka8->unk1b0];
            if (target->unk83 == 1 && static_cast<FieldClass15BB30*>(target)->unk3b0 == 0)
            {
                LineFailureDialog* next = new (0) LineFailureDialog;
                next->func_slotf4(unka8->func_00263CC0());
                unka8->func_00263FD0(next);
                unka8->func_00263C70(next);
                func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
            }
            else
            {
                ItemDetailsWindow* alternate = static_cast<ItemDetailsWindow*>(func_slot4c());
                func_00352DE0(alternate);
                alternate->func_slot20(1);
                alternate->unke8->unkab = 1;
                func_00112400(D_001B65F8, 18, 0, 0, 127, 64, 0);
                D_001B643C->unk10->unk14->func_00263C70(alternate);
            }
            break;
        }
        case 1:
            return func_slotb4();
        default:
            return 0;
    }
    return 1;
}

/** @brief Create the two-option display, selector, and marker. @param associated Associated source. @return Always one. */
s32 ItemSubmissionDialog::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 112.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 416.0f, 156.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FCA, 1);
    func_004C6190(unk10, heading);
    unkb4 = new (0) LibObject178750;
    unkb4->func_004C7FE0(158.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FD7, 1);
    func_004C6190(unk10, unkb4);
    LibObject178750* description = new (0) LibObject178750;
    description->func_004C7FE0(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x15FCB, 0);
    func_004C6190(unk10, description);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 68.0f, 392.0f, 4.0f);
    frame->unk50 = 0x606060;
    frame->unk3c = 1;
    func_004C6190(unk10, frame);
    LibObject178750* first = new (0) LibObject178750;
    first->func_004C7FE0(172.0f, 80.0f, 0.0f, 0.0f, (s32)associated, 0x15FCC, 0);
    func_004C6190(unk10, first);
    func_0036F1A0(&unk2c, first);
    LibObject178750* second = new (0) LibObject178750;
    second->func_004C7FE0(172.0f, 108.0f, 0.0f, 0.0f, (s32)associated, 0x15FCD, 0);
    func_004C6190(unk10, second);
    func_0036F1A0(&unk2c, second);
    unkac = new (0) FieldClass153130;
    unkac->func_0023B530(1, 2, 1, 1, 1, 172.0f, 92.0f, 0.0f, 28.0f);
    func_004C6190(unk10, unkac);
    LibObject178750* target = static_cast<LibObject178750*>(func_0036F230(&unk2c, 1)->unk00);
    unkb0 = new (0) FieldClass153170;
    unkb0->func_0023B850(target, 0x288080);
    func_004C6190(unk10, unkb0);
    if (unkac != 0)
    {
        s32 index;
        for (index = 0; index < 2; index++)
        {
            LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
            if (index == 1)
            {
                display->set_color(0x288080);
                unkb0->func_0023B7E0(display);
            }
            else
            {
                display->set_color(0x808080);
            }
        }
    }
    return 1;
}

/**
 * @brief Destroy the window through its Field base.
 */
ItemSubmissionDialog::~ItemSubmissionDialog()
{
}

void func_00356160(ItemCreationNineResourceView* object)
{
    void* allocation;
    u32 resource;
    s32 index;
    u32 value;
    FieldResourceRecord* record;

    object->unk109 = 0;
    for (index = 0; index < 9; index++)
    {
        value = object->unka8->unk68[(u16)index];
        if (value != 0)
        {
            resource = (u8)item_resource_index(value);
            allocation = func_002D3D80(D_001B643C->unk20, resource);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            func_002D5CF0(object->unkdc[index], allocation, record, resource);
            object->unkdc[index]->unk3F = 1;
            object->unk109++;
        }
        else
        {
            object->unkdc[index]->unk3F = 0;
        }
    }
}

/**
 * @brief Restore the resource marker and reopen its option window.
 * @return Zero when inactive, otherwise one.
 */
s32 ItemCreationClass186770::func_slotb8()
{
    if (unka8->unk19a == 0)
    {
        return 0;
    }
    FieldObject23CEA0* marker = unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 64.0f;
        marker->unkae = 1;
        unka8->unk19a = 0;
        ItemCreationSelectedDisplayState* state = unka8;
        if (state->unk19c != 0)
        {
            func_002FD940(state->unk19c);
            state->unk1a8 = 1;
        }
        state->unk1a4 = 0;
        state->unk1a0 = 0;
        state->unk1ac = 0;
    }
    InventorStatusWindow* next = unka8->unke8;
    func_00351510(next, 1);
    next->func_slot20(1);
    D_001B643C->unk10->unk14->func_00263C70(next);
    return 1;
}

/**
 * @brief Open the two-option window for the selected resource group.
 * @return Action status.
 */
s32 ItemCreationClass186770::func_slotb0()
{
    if (unk110 == 0)
    {
        return 0;
    }
    if (unka8->unk19a == 0)
    {
        return 0;
    }
    u16 index = static_cast<u16>(unk10c->unk114);
    if (unka8->unk1b1[index] != 0)
    {
        return 3;
    }
    ItemCreationControlHelp* parent = static_cast<ItemCreationControlHelp*>(func_slot44());
    if (parent != 0)
    {
        parent->func_003598E0(4, 1);
    }
    if (unka8 != 0)
    {
        unka8->unk1b0 = static_cast<u8>(static_cast<u16>(unk10c->unk114));
    }
    unk110->func_slot20(1);
    ItemSubmissionDialog* next = unk110;
    if (next->unkb4 != 0)
    {
        func_4C6DF0(next->unkb4, next->func_slot54(), 0x15FD7 + index, 0);
    }
    D_001B643C->unk10->unk14->func_00263C70(unk110);
    FieldObject23CEA0* marker = unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 64.0f;
        marker->unkae = 1;
        unka8->unk19a = 0;
        ItemCreationSelectedDisplayState* state = unka8;
        if (state->unk19c != 0)
        {
            func_002FD940(state->unk19c);
            state->unk1a8 = 1;
        }
        state->unk1a4 = 0;
        state->unk1a0 = 0;
        state->unk1ac = 0;
    }
    return 1;
}

/**
 * @brief Restore the marker and reopen the associated window.
 * @return Zero when inactive, otherwise two.
 */
s32 ItemCreationClass186770::func_slotb4()
{
    if (unka8->unk19a == 0)
    {
        return 0;
    }
    unka8->unk1b0 = static_cast<u8>(static_cast<u16>(unk10c->unk114));
    FieldObject23CEA0* marker = unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 64.0f;
        marker->unkae = 1;
        unka8->unk19a = 0;
        ItemCreationSelectedDisplayState* state = unka8;
        if (state->unk19c != 0)
        {
            func_002FD940(state->unk19c);
            state->unk1a8 = 1;
        }
        state->unk1a4 = 0;
        state->unk1a0 = 0;
        state->unk1ac = 0;
    }
    unk1c0->func_slot20(1);
    D_001B643C->unk10->unk14->func_00263C70(unk1c0);
    return 2;
}

/**
 * @brief Move the resource column while skipping unavailable alternatives.
 * @param object Resource window.
 * @param direction Direction code, zero or one.
 */
extern "C" void func_003565A0(ItemCreationClass186770* object, u16 direction)
{
    if (object->unka8->unk19a == 0)
    {
        return;
    }
    FieldObject23CEA0* grid = object->unk10c;
    switch (static_cast<u16>(grid->unk114))
    {
    case 0:
        if (direction == 0)
        {
            if (object->unk134[2]->unk94 == 0x505050UL)
            {
                if (object->unk134[1]->unk94 == 0x505050UL)
                {
                    return;
                }
                direction = 1;
            }
        }
        else
        {
            if (object->unk134[1]->unk94 == 0x505050UL)
            {
                if (object->unk134[2]->unk94 == 0x505050UL)
                {
                    return;
                }
                direction = 0;
            }
        }
        break;
    case 1:
        if (direction == 0)
        {
            if (object->unk134[0]->unk94 == 0x505050UL)
            {
                if (object->unk134[2]->unk94 == 0x505050UL)
                {
                    return;
                }
                direction = 1;
            }
        }
        else
        {
            if (object->unk134[2]->unk94 == 0x505050UL)
            {
                if (object->unk134[0]->unk94 == 0x505050UL)
                {
                    return;
                }
                direction = 0;
            }
        }
        break;
    case 2:
        if (direction == 0)
        {
            if (object->unk134[1]->unk94 == 0x505050UL)
            {
                if (object->unk134[0]->unk94 == 0x505050UL)
                {
                    return;
                }
                direction = 1;
            }
        }
        else
        {
            if (object->unk134[0]->unk94 == 0x505050UL)
            {
                if (object->unk134[1]->unk94 == 0x505050UL)
                {
                    return;
                }
                direction = 0;
            }
        }
        break;
    }
    if (grid != 0 && grid->func_0023CDB0(static_cast<s16>(direction)) != 1)
    {
        func_00356780(reinterpret_cast<ItemCreationFlagGroups*>(object), static_cast<u16>(object->unk10c->unk114));
    }
}

void func_00356780(ItemCreationFlagGroups* object, u16 group)
{
    s32 index;
    for (index = 0; index < 12; index++)
    {
        ItemCreationFlagNode* node = object->unk174[index];
        if (node != 0)
        {
            node->unk3f = 0;
        }
    }
    switch (group)
    {
    case 0:
        if (object->unk174[0] != 0)
        {
            object->unk174[0]->unk3f = 1;
        }
        if (object->unk174[1] != 0)
        {
            object->unk174[1]->unk3f = 1;
        }
        if (object->unk174[2] != 0)
        {
            object->unk174[2]->unk3f = 1;
        }
        if (object->unk174[3] != 0)
        {
            object->unk174[3]->unk3f = 1;
        }
        break;
    case 1:
        if (object->unk174[4] != 0)
        {
            object->unk174[4]->unk3f = 1;
        }
        if (object->unk174[5] != 0)
        {
            object->unk174[5]->unk3f = 1;
        }
        if (object->unk174[6] != 0)
        {
            object->unk174[6]->unk3f = 1;
        }
        if (object->unk174[7] != 0)
        {
            object->unk174[7]->unk3f = 1;
        }
        break;
    case 2:
        if (object->unk174[8] != 0)
        {
            object->unk174[8]->unk3f = 1;
        }
        if (object->unk174[9] != 0)
        {
            object->unk174[9]->unk3f = 1;
        }
        if (object->unk174[10] != 0)
        {
            object->unk174[10]->unk3f = 1;
        }
        if (object->unk174[11] != 0)
        {
            object->unk174[11]->unk3f = 1;
        }
        break;
    }
}

/**
 * @brief Move the selected resource column in direction 1.
 */
void ItemCreationClass186770::func_slot6c()
{
    func_003565A0(this, 1);
}

/**
 * @brief Move the selected resource column in direction 0.
 */
void ItemCreationClass186770::func_slot68()
{
    func_003565A0(this, 0);
}

/**
 * @brief Hide a resource slot or refresh it from the selected item and mode.
 * @param object Resource window receiving the update.
 * @param index Selected resource slot.
 * @param mode Resource record selector.
 * @param active Zero hides the slot; a nonzero byte refreshes it.
 */
extern "C" void func_003568F0(ItemCreationClass186770* object, u8 index, u8 mode, u8 active)
{
    u32 resource;
    FieldResourceRecord* record;
    void* allocation;

    if (active == 0)
    {
        object->unkdc[index]->unk3F = 0;
    }
    else
    {
        resource = (u8)item_resource_index(object->unka8->unk68[(u16)index]);
        record = 0;
        switch (mode)
        {
        case 0:
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            break;
        case 1:
            record = func_002D3CC0(D_001B643C->unk20, 0x50);
            break;
        case 2:
            record = func_002D3CC0(D_001B643C->unk20, 0x4F);
            break;
        case 3:
            record = func_002D3CC0(D_001B643C->unk20, 0x52);
            break;
        }
        allocation = func_002D3D80(D_001B643C->unk20, resource);
        func_002D5CF0(object->unkdc[index], allocation, record, resource);
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00356A40);

void func_00356FD0(ItemCreationNineResourceView* object)
{
    s32 index;

    object->unk1bc = object->unka8->unk57;
    for (index = 0; index < 3; index++)
    {
        if (index < object->unk1bc)
        {
            LibObject174F20* value;
            LibObject178750* display1;
            LibObject178750* display2;
            LibObject178750* display3;
            LibObject178750* display4;

            display1 = object->unk134[index];
            display1->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display1->unk3c = 1;
            display2 = object->unk140[index];
            display2->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display2->unk3c = 1;
            display3 = object->unk14c[index];
            display3->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display3->unk3c = 1;
            display4 = object->unk158[index];
            display4->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display4->unk3c = 1;
            value = object->unk164[index];
            value->unkfc = object->unka8->unk1c8[index];
            value->unk3c = 1;
        }
        else
        {
            ItemCreationFlagNode* marker;
            LibObject178750* display1;
            LibObject178750* display2;
            LibObject178750* display3;
            LibObject178750* display4;

            display1 = object->unk134[index];
            display1->unk94 = ITEM_CREATION_COLOR_DIM;
            display1->unk3c = 1;
            display2 = object->unk140[index];
            display2->unk94 = ITEM_CREATION_COLOR_DIM;
            display2->unk3c = 1;
            display3 = object->unk14c[index];
            display3->unk94 = ITEM_CREATION_COLOR_DIM;
            display3->unk3c = 1;
            display4 = object->unk158[index];
            display4->unk94 = ITEM_CREATION_COLOR_DIM;
            display4->unk3c = 1;
            object->unk164[index]->unk3f = 0;
            marker = static_cast<ItemCreationFlagNode*>(object->unk11c[index]->unk30);
            if (marker != 0)
            {
                marker->unk3f = 0;
            }
            marker = static_cast<ItemCreationFlagNode*>(object->unk128[index]->unk30);
            if (marker != 0)
            {
                marker->unk3f = 0;
            }
        }
    }
    object->unk10c->func_0023CE80(1, object->unk1bc);
    func_00356780((ItemCreationFlagGroups*)object, 0);
}

/**
 * @brief Create the resource grid, its meters and labels, and the selection displays.
 * @param associated Associated source passed to the Field setup and the labels.
 * @return Zero without a selected state, otherwise one.
 */
s32 ItemCreationClass186770::func_slotf4(void* associated)
{
    if (unka8 == 0)
    {
        return 0;
    }
    unk1bc = unka8->unk57;
    func_002CE8D0(reinterpret_cast<FieldObjectCE8D0*>(this), associated, 16.0f, 251.4f, 17);
    LibWidgetColors4C5590 colors = {0};
    colors.values[0] = 0xBCA4B4;
    colors.values[1] = 0xBCA4B4;
    colors.values[2] = 0x574C52;
    colors.values[3] = 0x574C52;
    float rows[3] = {0};
    for (s32 row = 0; row < 3; row++)
    {
        rows[row] = shifted_position(shifted_position(0.0f, 70.0f * row), 3.3f * row);
        for (s32 column = 0; column < 4; column++)
        {
            u32 index = column + row * 4;
            unkac[index] = new (0) FieldClass15B200(unk10, 1);
            FieldClass15B200*& resource = unkac[index];
            switch (column)
            {
            case 0:
                func_002D5290(resource, 0xBC, 0x18, &colors, 0.0f, rows[row], 226.0f, 70.0f);
                break;
            case 1:
                func_002D5290(resource, 0xBC, 0x18, &colors, 226.0f, rows[row], 264.0f, 35.0f);
                break;
            case 2:
                func_002D5290(resource, 0xBC, 0x18, &colors, 226.0f, 35.0f + rows[row], 264.0f, 35.0f);
                break;
            case 3:
                func_002D5290(resource, 0xBC, 0x18, &colors, 490.0f, rows[row], 118.0f, 70.0f);
                break;
            }
            LibClass178600* child = static_cast<LibClass178600*>(resource->unk30);
            if (child)
            {
                child->unk28 = 40.0f;
                child->unk3c = 1;
            }
        }
    }
    colors.values[0] = 0x2846AA;
    colors.values[1] = 0x233CA0;
    colors.values[2] = 0x46D7E6;
    colors.values[3] = 0x32C3D2;
    for (s32 row = 0; row < 3; row++)
    {
        unk134[row] = new (0) LibObject178750;
        unk134[row]->func_004C7FE0(8.0f, rows[row] - 6.0f, 0.0f, 0.0f, (s32)associated, row + 0x15FD7, 1);
        unk134[row]->set_color(0x1E8CFF);
        unk134[row]->set_scale(0.75f, 0.75f);
        func_004C6190(unk10, unk134[row]);
        unk140[row] = new (0) LibObject178750;
        unk140[row]->func_004C7FE0(234.0f, rows[row] - 6.0f, 0.0f, 0.0f, (s32)associated, 0x15FA5, 1);
        unk140[row]->set_color(0x1E8CFF);
        unk140[row]->set_scale(0.75f, 0.75f);
        func_004C6190(unk10, unk140[row]);
        unk14c[row] = new (0) LibObject178750;
        unk14c[row]->func_004C7FE0(234.0f, (35.0f + rows[row]) - 6.0f, 0.0f, 0.0f, (s32)associated, 0x15FA4, 1);
        unk14c[row]->set_color(0x1E8CFF);
        unk14c[row]->set_scale(0.75f, 0.75f);
        func_004C6190(unk10, unk14c[row]);
        unk158[row] = new (0) LibObject178750;
        unk158[row]->func_004C7FE0(498.0f, rows[row] - 6.0f, 0.0f, 0.0f, (s32)associated, 0x15FA6, 1);
        unk158[row]->set_color(0x1E8CFF);
        unk158[row]->set_scale(0.75f, 0.75f);
        func_004C6190(unk10, unk158[row]);
        unk164[row] = new (0) LibObject174F20;
        func_00464D90(unk164[row], 0, 0, 0, 486.0f, 28.0f + rows[row], 112.0f, 24.0f);
        unk164[row]->set_mode(2);
        func_004C6190(unk10, unk164[row]);
        unk11c[row] = new (0) FieldClass15B200(unk10, 0);
        func_002D5290(unk11c[row], 0, 0, &colors, 228.0f, 17.5f + rows[row], 256.0f, 8.0f);
        LibClass178600* child = static_cast<LibClass178600*>(unk11c[row]->unk30);
        if (child)
        {
            child->unk28 = 100.0f;
            child->unk3c = 1;
        }
        func_002D5260(reinterpret_cast<FieldObject2D5260*>(unk11c[row]), 0.0f, 8.0f);
    }
    colors.values[0] = 0x1EAA32;
    colors.values[1] = 0x19A028;
    colors.values[2] = 0x46D7E6;
    colors.values[3] = 0x32C3D2;
    for (s32 row = 0; row < 3; row++)
    {
        unk128[row] = new (0) FieldClass15B200(unk10, 0);
        func_002D5290(unk128[row], 0, 0, &colors, 228.0f, 17.5f + (35.0f + rows[row]), 0.0f, 8.0f);
        LibClass178600* child = static_cast<LibClass178600*>(unk128[row]->unk30);
        if (child)
        {
            child->unk28 = 100.0f;
            child->unk3c = 1;
        }
    }
    u8 slot;
    void* allocation;
    float y = 4.0f;
    for (s32 index = 0; index < 9; index++)
    {
        u8 code = unka8->unk68[(u16)index];
        FieldResourceRecord* record;
        if (code == 0)
        {
            allocation = func_002D3D80(D_001B643C->unk20, 0);
            record = func_002D3CC0(D_001B643C->unk20, 0x20);
            slot = 0;
        }
        else
        {
            slot = (u8)item_resource_index(code);
            allocation = func_002D3D80(D_001B643C->unk20, slot);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            unk109++;
            unk170[index / 3] = 1;
        }
        if (index != 0 && index % 3 == 0)
        {
            y = 4.0f + rows[index / 3];
        }
        ItemCreationOptionResourceDisplay* display = new (0) ItemCreationOptionResourceDisplay;
        display->unkcc = allocation;
        display->unkd0 = slot;
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), record, 10.0f + 72.0f * (index % 3), y);
        display->unk50.unk34 = 1.0f;
        display->unk50.unk30 = 1.0f;
        display->unk3c = 1;
        display->unk34 = 3;
        func_004C6190(unk10, display);
        unkdc[index] = reinterpret_cast<FieldResourceDisplay2D5CF0*>(display);
    }
    allocation = func_002D3D80(D_001B643C->unk20, 0);
    for (s32 row = 0; row < 3; row++)
    {
        float y1 = 3.0f + rows[row];
        float y2 = shifted_position(y1, 29.0f);
        for (s32 column = 0; column < 4; column++)
        {
            ItemCreationOptionResourceDisplay* display = new (0) ItemCreationOptionResourceDisplay;
            display->unkcc = allocation;
            display->unkd0 = 0;
            switch (column)
            {
            case 0:
                func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), func_002D3CC0(D_001B643C->unk20, 0x53), 4.0f, y1);
                break;
            case 1:
                func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), func_002D3CC0(D_001B643C->unk20, 0x54), 4.0f, y2);
                break;
            case 2:
                func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), func_002D3CC0(D_001B643C->unk20, 0x55), 187.0f, y1);
                break;
            case 3:
                func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), func_002D3CC0(D_001B643C->unk20, 0x56), 187.0f, y2);
                break;
            }
            display->unk50.unk34 = 2.0f;
            display->unk50.unk30 = 2.0f;
            display->unk3c = 1;
            display->unk34 = 3;
            func_004C6190(unk10, display);
            unk174[column + row * 4] = display;
        }
    }
    unk10c = new (0) FieldObject23CEA0;
    unk10c->func_0023CE80(1, unk1bc);
    unk10c->func_0023CE60(0.0f, 73.3f);
    unk10c->unkF2 = 0;
    unk10c->unk119 = 1;
    unk10c->func_0023CF50(0, 34.0f, 264.4f);
    func_0036F040(&unk74, unk10c);
    func_0023CEA0(unk10c, 0);
    func_00356780(reinterpret_cast<ItemCreationFlagGroups*>(this), 0);
    return 1;
}

/**
 * @brief Delete an owned object and clear its pointer.
 * @param resource Nullable owned object pointer.
 */
template <class T>
static inline void release_owned(T*& resource)
{
    if (resource)
    {
        delete resource;
        resource = 0;
    }
}

/** @brief Release the owned rectangles before destroying the Field window base. */
ItemCreationClass186770::~ItemCreationClass186770()
{
    for (s32 index = 0; index < 3; index++)
    {
        if (unk11c[index] != 0)
        {
            release_owned(unk11c[index]);
        }
        if (unk128[index] != 0)
        {
            release_owned(unk128[index]);
        }
    }
    for (s32 index = 0; index < 12; index++)
    {
        if (unkac[index] != 0)
        {
            release_owned(unkac[index]);
        }
    }
}

/**
 * @brief Initialize the resource window and its owned arrays.
 */
ItemCreationClass186770::ItemCreationClass186770()
{
    unka8 = 0;
    unk109 = 0;
    for (s32 index = 0; index < 3; index++)
    {
        unk134[index] = 0;
        unk140[index] = 0;
        unk14c[index] = 0;
        unk158[index] = 0;
        unk164[index] = 0;
        unk170[index] = 0;
        unk11c[index] = 0;
        unk128[index] = 0;
    }
    for (s32 index = 0; index < 12; index++)
    {
        unkac[index] = 0;
        unk174[index] = 0;
    }
    for (s32 index = 0; index < 9; index++)
    {
        unkdc[index] = 0;
        unk100[index] = 0xFF;
    }
    unk10c = 0;
    unk110 = 0;
    unk114 = 0;
    unk118 = 0;
    unk1bc = 0;
}

s32 StartInventingDialog::func_slotb4()
{
    AssignedInventorGrid* parent = static_cast<AssignedInventorGrid*>(func_slot44());
    if (parent != 0)
    {
        func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkb4)), 1);
        unkac->set_color(ITEM_CREATION_COLOR_BRIGHT);
        unkb0->set_color(ITEM_CREATION_COLOR_SELECTED);
        unkb8->func_0023B7E0(unkb0);
        func_slot20(0);
        if (parent->unkb4 != 0)
        {
            parent->unkb4->unkad = 1;
        }
        D_001B643C->unk10->unk14->func_00263C70(parent);
    }
    unkbc[0] = 0;
    unkbc[1] = 0;
    unkbc[2] = 0;
    return 2;
}

s32 StartInventingDialog::func_slotb0()
{
    FieldClass153130* selector = unkb4;
    if (selector->func_0023B3A0() == 0)
    {
        unka8->func_0036BF30(0, unkbc[0]);
        unka8->func_0036BF30(1, unkbc[1]);
        unka8->func_0036BF30(2, unkbc[2]);
        unka8->unk47 = 2;
        func_0027CB50(D_001B6430->context->unk58, 0x42, 0, 0);
    }
    else
    {
        func_slotb4();
    }
    return 1;
}

void StartInventingDialog::func_slot6c()
{
    if (unkb4 != 0 && !selector_moving(unkb4) && (u8)unkb4->func_0023B3B0(1) != 1)
    {
        u16 selected = unkb4->func_0023B3A0();
        switch (selected)
        {
        case 0:
        {
            unkac->set_color(ITEM_CREATION_COLOR_SELECTED);
            unkb0->set_color(ITEM_CREATION_COLOR_BRIGHT);
            unkb8->func_0023B7E0(unkac);
            break;
        }
        case 1:
        {
            unkac->set_color(ITEM_CREATION_COLOR_BRIGHT);
            unkb0->set_color(ITEM_CREATION_COLOR_SELECTED);
            unkb8->func_0023B7E0(unkb0);
            break;
        }
        }
    }
}

void StartInventingDialog::func_slot68()
{
    if (unkb4 != 0 && !selector_moving(unkb4) && (u8)unkb4->func_0023B3B0(0) != 1)
    {
        u16 selected = unkb4->func_0023B3A0();
        switch (selected)
        {
        case 0:
        {
            unkac->set_color(ITEM_CREATION_COLOR_SELECTED);
            unkb0->set_color(ITEM_CREATION_COLOR_BRIGHT);
            unkb8->func_0023B7E0(unkac);
            break;
        }
        case 1:
        {
            unkac->set_color(ITEM_CREATION_COLOR_BRIGHT);
            unkb0->set_color(ITEM_CREATION_COLOR_SELECTED);
            unkb8->func_0023B7E0(unkb0);
            break;
        }
        }
    }
}

/**
 * @brief Create the option window's frame, resource widgets, and selection grid.
 * @param associated Associated window object; unused.
 * @return One when the required window state is present, or zero otherwise.
 */
s32 TransferInventorStrip::func_slotf4(void* associated)
{
    if (unka8 == 0)
    {
        return 0;
    }
    if (unk10 == 0)
    {
        return 0;
    }
    if (unkc4 == 0)
    {
        return 0;
    }
    for (s32 index = 0; index < 4; index++)
    {
        ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
        switch (index)
        {
        case 0:
            func_421170(frame, 0.0f, 0.0f, 440.0f, 3.0f);
            break;
        case 1:
            func_421170(frame, 0.0f, 80.0f, 440.0f, 3.0f);
            break;
        case 2:
            func_421170(frame, 0.0f, 0.0f, 3.0f, 80.0f);
            break;
        case 3:
            func_421170(frame, 439.0f, 0.0f, 3.0f, 82.0f);
            break;
        }
        if (unka8 == 1)
        {
            func_420D20(frame, 0x505080);
        }
        else
        {
            func_420D20(frame, 0x808050);
        }
        func_004C6190(unk10, frame);
    }
    void* allocation = func_002D3D80(D_001B643C->unk20, 0);
    float offset = 0.0f;
    for (s32 index = 0; index < 6; index++)
    {
        offset += 8.0f;
        ItemCreationOptionResourceDisplay* resource = new (0) ItemCreationOptionResourceDisplay;
        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 16);
        resource->unkcc = allocation;
        resource->unkd0 = 0;
        resource->func_002D6440(record, offset + 64.0f * (index % 6), 8.0f);
        func_004C6190(unk10, resource);
        unkac[index] = resource;
    }
    unkc8 = new (0) FieldObject23CEA0;
    unkc8->func_0023CE80(6, 1);
    unkc8->func_0023CE60(72.0f, 0.0f);
    unkc8->unkF2 = 0;
    unkc8->unk119 = 1;
    unkc8->func_0023CF50(0, 36.0f, unka8 == 1 ? 320.0f : 400.0f);
    func_0023CEA0(unkc8, 0);
    func_0036F040(&unk74, unkc8);
    if (unkc8 != 0)
    {
        func_0023CEA0(unkc8, 0);
    }
    return 1;
}

/**
 * @brief Create and attach the result window's display widgets.
 * @param object Result window.
 * @param associated Object associated with the window.
 * @return Always one.
 */
extern "C" s32 func_003501B0(InadequateLineDialog* object, void* associated)
{
    object->FieldClass15AE70::func_slot10(associated, 95.0f, 188.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 455.0f, 160.0f, 88.0f);
    func_004C6190(object->unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x1B6C, 1);
    func_004C6190(object->unk10, heading);
    object->unkb0 = new (0) LibObject178750;
    object->unkb0->func_004C7FE0(210.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FD7, 1);
    func_004C6190(object->unk10, object->unkb0);
    LibObject178750* subheading = new (0) LibObject178750;
    subheading->func_004C7FE0(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x1B6D, 0);
    func_004C6190(object->unk10, subheading);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 100.0f, 430.0f, 4.0f);
    frame->unk50 = 0x606060;
    frame->unk3c = 1;
    func_004C6190(object->unk10, frame);
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(340.0f, 110.0f, 0.0f, 0.0f, (s32)associated, 0x1B73, 0);
    footer->set_scale(0.9f, 0.9f);
    func_004C6190(object->unk10, footer);
    return 1;
}

/**
 * @brief Create the result window display and clear the current selection flag.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 DevelopmentCompleteDialog::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 100.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 430.0f, 160.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x1B6C, 1);
    func_004C6190(unk10, heading);
    LibObject178750* subheading = new (0) LibObject178750;
    subheading->func_004C7FE0(36.0f, 45.0f, 0.0f, 0.0f, (s32)associated, 0x1B88, 0);
    func_004C6190(unk10, subheading);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 110.0f, 408.0f, 4.0f);
    frame->unk50 = 0x606060;
    frame->unk3c = 1;
    func_004C6190(unk10, frame);
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(320.0f, 120.0f, 0.0f, 0.0f, (s32)associated, 0x15FC3, 0);
    footer->set_scale(0.9f, 0.9f);
    func_004C6190(unk10, footer);
    static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14)->unk19a = 0;
    return 1;
}

/**
 * @brief Create and attach the result prompt display.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 LineFailureDialog::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 85.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 470.0f, 160.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x1B6C, 1);
    func_004C6190(unk10, heading);
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    unka8 = new (0) LibObject178750;
    unka8->func_004C7FE0(210.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FD7 + state->unk1b0, 1);
    func_004C6190(unk10, unka8);
    LibObject178750* subheading = new (0) LibObject178750;
    subheading->func_004C7FE0(36.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x15FCE, 0);
    func_004C6190(unk10, subheading);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 100.0f, 448.0f, 4.0f);
    frame->unk50 = 0x606060;
    frame->unk3c = 1;
    func_004C6190(unk10, frame);
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(360.0f, 115.0f, 0.0f, 0.0f, (s32)associated, 0x15FC3, 0);
    footer->set_scale(0.9f, 0.9f);
    func_004C6190(unk10, footer);
    return 1;
}

/**
 * @brief Create and attach the result prompt display.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 InventionSuccessDialog::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 112.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 416.0f, 140.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FC1, 1);
    func_004C6190(unk10, heading);
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    unka8 = new (0) LibObject178750;
    unka8->func_004C7FE0(210.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FD7 + state->unk1b0, 1);
    func_004C6190(unk10, unka8);
    LibObject178750* subheading = new (0) LibObject178750;
    subheading->func_004C7FE0(36.0f, 45.0f, 0.0f, 0.0f, (s32)associated, 0x15FC2, 0);
    func_004C6190(unk10, subheading);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 75.0f, 394.0f, 4.0f);
    frame->unk50 = 0x606060;
    frame->unk3c = 1;
    func_004C6190(unk10, frame);
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(320.0f, 95.0f, 0.0f, 0.0f, (s32)associated, 0x15FC3, 0);
    footer->set_scale(0.9f, 0.9f);
    func_004C6190(unk10, footer);
    return 1;
}

#include "include_asm.h"
#include "overlays/lib/text_004095C0.h"
#include "main/resident_0012F0F8.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/citemcreation/text_003483C0.h"
#include "overlays/citemcreation/item_display_inlines.h"
#include "overlays/citemcreation/text_003684D0.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_002F9C90.h"










/** Partial controls containing the mode-list activation flag. */
struct ItemCreationControlState
{
    u8 unk00[0x9A];
    u8 unk9a;
};




/** Partial record containing a checked value and its checksum fields. */
typedef struct ItemCreationCheckedRecord
{
    u8 unk00[0x34];
    u32 unk34;
    u8 unk38[0x6C];
    u16 unka4;
    u16 unka6;
} ItemCreationCheckedRecord;

/** String record with its text beginning at field 0x20. */
struct ItemCreationStringRecord
{
    u8 unk00[0x20];
    char unk20;
    u8 unk21[0xF3];
};

// These external interfaces are scoped here because their owning code is in other overlays.
extern "C"
{
    extern ResidentRequest112400* D_001B65F8;
    extern ItemCreationCategoryDefinition* D_001B64F0;
    extern const char D_0036F738[];
    /** @brief Select the mode display state. @param object Mode window. @param mode Display mode. */
    void func_0035D7C0(PlanItemGroupWindow* object, u8 mode);
    extern FieldRuntime* D_001B657C;
/**
 * @brief Update the Field list count, selected index, and display bounds.
 * @param object List parameter and callback receiver.
 * @param count List entry count.
 * @param index Selected entry index.
 * @param row Visible row index.
 */
void func_002CE220(FieldStateCE420* object, s32 count, s32 index, u8 row);
/**
 * @brief Configure the frame widget's rectangle.
 * @param object Frame widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero if its storage could not be initialized.
 */
s32 func_44B570(ItemCreationClass1746A0* object, float x, float y, float width, float height);

/**
 * @brief Configure the divider widget's rectangle.
 * @param object Divider widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return Initialization status.
 */
s32 func_421170(ItemCreationClass172870* object, float x, float y, float width, float height);
/** @brief Set the divider color. @param object Divider widget. @param color Packed color. */
void func_420D20(ItemCreationClass172870* object, u32 color);
/** @brief Update the active Field list. @param object List window receiver. */
void func_002CD7C0(FieldClass15AD40* object);
/** @brief Update the Field list parameters. @param object List parameter receiver. */
void func_002CDFB0(FieldStateCE420* object);
/**
 * @brief Update the list display marker.
 * @param object List window receiver.
 * @param display Selected display, or null.
 * @param color Packed marker color.
 */
void func_002CD8B0(FieldClass15AD40* object, LibClass174EF0* display, u32 color);

/** @brief Return the text widget bounds. @param object Text widget. @return Stored bounds. */
LibBounds4C69B0* func_4C69B0(LibObject178750* object);

/** @brief Refresh the panel grid selection and selected entry. @param object Panel selection window. */
void func_00365F20(WorkshopExpansionWindow* object);
/** @brief Reset the grid indices and update its position. @param object Grid receiver. */
void func_0023C710(FieldObject23CEA0* object);

}

/** @brief Set the transform position. @param object Drawing transform. @param x Horizontal coordinate. @param y Vertical coordinate. */
extern "C" void func_44B190(LibClass174610* object, float x, float y);

/** Field selection API imported by this overlay without its resident global declarations. */
extern "C" s32 func_0027CB50(void* object, s32 identifier, s32 first, s32 second);

/** @brief Set the widget height and refresh its rectangle. @param widget Drawing widget. @param height Rectangle height. */
static inline void set_height(LibClass178600* widget, float height)
{
    widget->unk18.unk0c = height;
    widget->unk3c = 1;
}

static inline bool valid_record_index_middle(s16 index);
static inline ItemCreationAllocationRecord* allocation_record_middle(s32 value);
static inline bool allocation_invalid_middle(ItemCreationAllocationRecord* record);
static inline u16 allocation_value_middle(ItemCreationAllocationRecord* record);
static inline u32 item_resource_index_middle(u8 inventor_option_code);
static inline u32 item_available_resource_index(u16 inventor_option_code);
static inline u32 item_assigned_code(u8 inventor_option_code);
/**
 * @brief Set the panel position and mark its rectangle for refresh.
 * @param panel Panel widget.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 */
static inline void set_panel_position(LibClass178630* panel, float x, float y);

/**
 * @brief Test whether a signed item index identifies an allocation record.
 * @param index Signed item index.
 * @return True for indices from one through three thousand.
 */
static inline bool valid_record_index_middle(s16 index)
{
    return index > 0 && index <= 3000;
}

/**
 * @brief Find an allocation record using the signed halfword item index.
 * @param value Item index to narrow to a signed halfword.
 * @return Allocation record, or null when the index is outside the table.
 */
static inline ItemCreationAllocationRecord* allocation_record_middle(s32 value)
{
    ItemCreationAllocationRecord* records = D_001B64F8->records;
    s16 index = value;
    if (valid_record_index_middle(index))
    {
        return &records[index - 1];
    }
    return 0;
}

/**
 * @brief Test the allocation record checksum against its packed halfword values.
 * @param record Allocation record to check.
 * @return True when its checksum differs from the calculated value.
 */
static inline bool allocation_invalid_middle(ItemCreationAllocationRecord* record)
{
    const u16* words = (const u16*)record;
    return record->unk0e != (u16)((0x83CF << record->unk0d_shift) ^
        ((words[4] + (words[0] + words[2])) ^
         (words[1] + (words[3] + words[5]))));
}

/**
 * @brief Read the packed allocation value when the record checksum is valid.
 * @param record Allocation record to read.
 * @return Its ten-bit value, or zero when the checksum is invalid.
 */
static inline u16 allocation_value_middle(ItemCreationAllocationRecord* record)
{
    if (allocation_invalid_middle(record))
    {
        return 0;
    }
    return record->unk00.bits.value;
}

/**
 * @brief Convert an inventor option code to its portrait resource index.
 * @param inventor_option_code Inventor option code; zero denotes an empty slot.
 * @return Zero for an empty slot, or the option code minus eleven.
 */
static inline u32 item_resource_index_middle(u8 inventor_option_code)
{
    if (inventor_option_code == 0)
    {
        return 0;
    }
    return inventor_option_code - 11;
}

/**
 * @brief Convert a workshop inventor option code to its portrait resource index.
 * @param inventor_option_code Inventor option code; zero denotes an empty slot.
 * @return Zero for an empty slot, or the option code minus eleven.
 */
static inline u32 item_available_resource_index(u16 inventor_option_code)
{
    if (inventor_option_code == 0)
    {
        return 0;
    }
    return inventor_option_code - 11;
}

/**
 * @brief Convert an inventor option code to its saved inventor ID.
 * @param inventor_option_code Inventor option code; zero denotes an empty slot.
 * @return Zero for an empty slot, or the option code minus thirty-one.
 */
static inline u32 item_assigned_code(u8 inventor_option_code)
{
    if (inventor_option_code == 0)
    {
        return 0;
    }
    return inventor_option_code - 31;
}

/**
 * @brief Test whether a detail index identifies one of the thirty-eight records.
 * @param index Detail index to test.
 * @return True for indices from one through thirty-eight.
 */
static inline bool valid_detail_index(u8 index)
{
    return index > 0 && index < 39;
}
/**
 * @brief Find the detail record selected by an item code.
 * @param value Index to narrow to a byte.
 * @return Selected record, or null when the index is outside the table.
 */
static inline ItemCreationInventorRecord* detail_record(s32 value)
{
    ItemCreationRuntimeData* table = D_001B64F8;
    u8 index = value;
    if (valid_detail_index(index))
    {
        return &table->inventors[index - 1];
    }
    return 0;
}

/**
 * @brief Read an inventor's normalized placement code from the selected state's option table.
 * @param state Selected state whose option table may be null.
 * @param inventor_option_code Inventor option code selecting the table entry.
 * @return Placement code from one through thirteen, or zero otherwise.
 */
static inline u16 selected_inventor_location_code(ItemCreationSelectedDisplayState* state, u8 inventor_option_code)
{
    if (state->unk40 == 0)
    {
        return 0;
    }
    u16 code = state->unk40->unk188[inventor_option_code];
    switch (code)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    default:
        code = 0;
        break;
    }
    return code;
}

/**
 * @brief Find the first inventor whose placement code is one.
 * @param state Selected state, or null.
 * @return Inventor ID, or zero when there is no state or no such inventor.
 */
static inline u16 first_placed_inventor(ItemCreationSelectedDisplayState* state)
{
    if (state == 0)
    {
        return 0;
    }
    u16 inventor_id = 0;
    for (s32 inventor_option_code = 32; inventor_option_code <= 59; inventor_option_code++)
    {
        if (selected_inventor_location_code(state, (u8)inventor_option_code) == 1)
        {
            inventor_id = inventor_id_from_option_code(inventor_option_code);
            break;
        }
    }
    return inventor_id;
}

/**
 * @brief Read an inventor's talent for a one-based creation skill.
 * @param record Inventor record.
 * @param skill Creation skill from one through nine.
 * @return Talent value, or zero for an out-of-range or unassigned skill.
 */
static inline u8 inventor_skill_talent(ItemCreationInventorRecord* record, u8 skill)
{
    u8 talent = 0;
    if (skill_code_in_range(skill))
    {
        u8 inventor_id = record->inventor_id;
        if (is_party_inventor(inventor_id))
        {
            talent = party_talent_record(inventor_id - 29)->talents[skill - 1];
        }
        else
        {
            const ItemCreationInventorTalent* entry = inventor_talent_record(inventor_id - 1);
            if (skill == entry->skill)
            {
                talent = entry->talent;
            }
        }
    }
    return talent;
}

// TODO: This matches with strength reduction off, but not with the file's settings. Needs further investigation.
#pragma push
#pragma opt_strength_reduction off
/**
 * @brief Build the inventor detail window for the first placed inventor.
 * @param associated Associated source passed to the Field setup and the labels.
 * @return One.
 */
s32 PendingInventorSummary::func_slotf4(void* associated)
{
    unkb8 = first_placed_inventor(unka8);
    func_002CE8D0(reinterpret_cast<FieldObjectCE8D0*>(this), associated, 16.0f, 384.0f, 17);
    for (s32 index = 0; index < 4; index++)
    {
        ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
        switch (index)
        {
        case 0:
            func_421170(frame, 0.0f, 0.0f, 440.0f, 3.0f);
            break;
        case 1:
            func_421170(frame, 0.0f, 80.0f, 440.0f, 3.0f);
            break;
        case 2:
            func_421170(frame, 0.0f, 0.0f, 3.0f, 80.0f);
            break;
        case 3:
            func_421170(frame, 439.0f, 0.0f, 3.0f, 82.0f);
            break;
        }
        func_420D20(frame, 0x505080);
        func_004C6190(unk10, frame);
    }
    void* allocation = func_002D3D80(D_001B643C->unk20, (u8)(unkb8 + 20));
    ItemCreationOptionResourceDisplay* display = new (0) ItemCreationOptionResourceDisplay;
    FieldResourceRecord* resource_record = func_002D3CC0(D_001B643C->unk20, 0x51);
    display->unkcc = allocation;
    display->unkd0 = 0;
    display->unk50.unk34 = 1.0f;
    display->unk50.unk30 = 1.0f;
    display->unk3c = 1;
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), resource_record, 8.0f, 9.0f);
    func_004C6190(unk10, display);
    unkb0 = new (0) LibObject178750;
    unkb0->func_004C7FE0(78.0f, 9.0f, 0.0f, 0.0f, (s32)associated, unkb8 + 0x3584, 0);
    func_004C6190(unk10, unkb0);
    unkb4 = new (0) LibObject178750;
    unkb4->func_004C7FE0(78.0f, 48.0f, 0.0f, 0.0f, (s32)associated, unkb8 + 0x35E8, 0);
    set_text_unk88(unkb4, -1.0f);
    func_004C6190(unk10, unkb4);
    u16 skill = 0;
    ItemCreationInventorRecord* record = detail_record(unkb8);
    if (record != 0)
    {
        u16 skills = inventor_skill_mask(record->inventor_id);
        if (skills & 1) { skill = 0; }
        if (skills & 2) { skill = 1; }
        if (skills & 4) { skill = 2; }
        if (skills & 8) { skill = 3; }
        if (skills & 0x10) { skill = 4; }
        if (skills & 0x20) { skill = 5; }
        if (skills & 0x40) { skill = 6; }
        if (skills & 0x80) { skill = 7; }
        unkbc = new (0) LibObject178750;
        u16 selected = skill;
        unkbc->func_004C7FE0(308.0f, 9.0f, 0.0f, 0.0f, (s32)associated, selected + 0x3458, 0);
        func_004C6190(unk10, unkbc);
        u16 talent = inventor_skill_talent(record, selected + 1);
        unkc0 = new (0) LibObject174F20;
        func_00464D90(unkc0, (u16)talent, 0, 0, 408.0f, 9.0f, 24.0f, 24.0f);
        func_004C6190(unk10, unkc0);
    }
    return 1;
}
#pragma pop

/**
 * @brief Refresh one inventor skill label and numeric talent.
 * @param object Inventor information window.
 * @param record Selected inventor record.
 * @param index Creation-skill index from zero through seven.
 */
static inline void refresh_inventor_skill(InventorInformationWindow* object, ItemCreationInventorRecord* record, s32 index)
{
    if (object->unk102 & (1 << index))
    {
        if (index != 0)
        {
            object->unkb8[index]->unk3d = 1;
        }
        u8 talent = inventor_talent(record->inventor_id, index);
        LibObject174F20* value_widget = object->unkdc[index];
        value_widget->unkfc = talent;
        value_widget->unk3c = 1;
        object->unkdc[index]->unk3d = 1;
        object->unkb8[index]->set_color(0x808080);
        object->unkdc[index]->set_color(0x808080);
    }
    else
    {
        object->unkb8[index]->set_color(0x505050);
    }
}

s32 StartInventingDialog::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 40.0f, 88.0f, 15);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 396.0f, 132.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(0.0f, 16.0f, 396.0f, 24.0f, (s32)associated, 0x1B72, 0);
    heading->set_vertical_alignment(1);
    heading->set_mode(1);
    func_004C6190(unk10, heading);
    unkac = new (0) LibObject178750;
    unkb0 = new (0) LibObject178750;
    unkac->func_004C7FE0(168.0f, 56.0f, 396.0f, 24.0f, (s32)associated, 0x15FCC, 0);
    unkb0->func_004C7FE0(168.0f, 86.0f, 396.0f, 24.0f, (s32)associated, 0x15FCD, 0);
    unkac->set_vertical_alignment(1);
    unkac->set_mode(0);
    unkb0->set_vertical_alignment(1);
    unkb0->set_mode(0);
    func_004C6190(unk10, unkac);
    func_004C6190(unk10, unkb0);
    unkb4 = new (0) FieldClass153130;
    unkb4->func_0023B530(1, 2, 1, 1, 1, 168.0f, 68.0f, 0.0f, 30.0f);
    func_004C6190(unk10, unkb4);
    unkb8 = new (0) FieldClass153170;
    unkb8->func_0023B850(unkb0, 0x288080);
    func_004C6190(unk10, unkb8);
    unkac->set_color(0x808080);
    unkb0->set_color(0x288080);
    unkb8->func_0023B7E0(unkb0);
    return 1;
}

StartInventingDialog::~StartInventingDialog()
{
}

void InventorInformationWindow::func_00358850()
{
    if (unk101 == 0)
    {
        unkac->unk3d = 0;
        unkb0->unk3d = 0;
        unkb4->unk3d = 0;
        for (s32 index = 0; index < 8; index++)
        {
            unkb8[index]->unk3d = 0;
            unkdc[index]->unk3d = 0;
        }
        return;
    }
    FieldRecordSelection* selection = unka8->unk48;
    u32 resource = (u8)item_resource_index_middle(unk101);
    void* allocation = func_002D3D80(D_001B643C->unk20, resource);
    FieldResourceRecord* source = func_002D3CC0(D_001B643C->unk20, 81);
    unkac->func_002D5CF0(allocation, source, resource);
    unkac->unk3d = 1;
    if ((u8)resource > 59)
    {
        s8 index = func_0028E240(selection, unk101 - 59);
        ItemCreationStringRecord* strings = static_cast<ItemCreationStringRecord*>(selection->unk04);
        LibObject175140* display = unkb0;
        display->unkfc = &strings[index].unk20;
        display->unk3c = 1;
        unkb0->unk3d = 1;
        unkb4->unk3d = 0;
    }
    else
    {
        unkb0->unk3d = 0;
        s32 index = item_assigned_code(unk101);
        func_4C6DF0(unkb4, func_slot54(), index + 0x3584, 1);
        unkb4->unk3d = 1;
    }
    for (s32 index = 0; index < 8; index++)
    {
        unkb8[index]->unk3d = 1;
        unkdc[index]->unk3d = 0;
    }
    ItemCreationInventorRecord* record = detail_record(item_assigned_code(unk101));
    if (record != 0)
    {
        refresh_inventor_skill(this, record, 0);
        refresh_inventor_skill(this, record, 1);
        refresh_inventor_skill(this, record, 2);
        refresh_inventor_skill(this, record, 3);
        refresh_inventor_skill(this, record, 4);
        refresh_inventor_skill(this, record, 5);
        refresh_inventor_skill(this, record, 6);
        refresh_inventor_skill(this, record, 7);
    }
}

s32 InventorInformationWindow::func_slotf4(void* associated)
{
    if (unka8 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 252.0f, 260.0f, 15);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 372.0f, 196.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(134.0f, 8.0f, 0.0f, 0.0f, (s32)associated, 0x15FA3, 0);
    heading->set_scale(0.9f, 0.9f);
    func_004C6190(unk10, heading);
    void* allocation = func_002D3D80(D_001B643C->unk20, 49);
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 81);
    unkac = new (0) ItemCreationOptionResourceDisplay;
    unkac->unkcc = allocation;
    unkac->unkd0 = 49;
    unkac->func_002D6440(record, 22.0f, 18.0f);
    ItemCreationOptionResourceDisplay* resource = unkac;
    resource->unk50.unk34 = 1.0f;
    resource->unk50.unk30 = 1.0f;
    resource->unk3c = 1;
    func_004C6190(unk10, unkac);
    unkac->unk3d = 0;
    unkb0 = new (0) LibObject175140;
    unkb0->func_00467AD0(96.0f, 42.0f, 0.0f, 0.0f, D_0036F738, 1);
    func_004C6190(unk10, unkb0);
    unkb0->unk3d = 0;
    unkb4 = new (0) LibObject178750;
    unkb4->func_004C7FE0(96.0f, 42.0f, 0.0f, 0.0f, (s32)associated, 0x3584, 1);
    func_004C6190(unk10, unkb4);
    unkb4->unk3d = 0;
    for (s32 index = 0; index < 8; index++)
    {
        unkb8[index] = new (0) LibObject178750;
        unkdc[index] = new (0) LibObject174F20;
        float y = 88.0f + 36.0f * (index / 3);
        float x = 22.0f + 122.0f * (index % 3);
        unkb8[index]->func_004C7FE0(x, y, 0.0f, 0.0f, (s32)associated, ITEM_CREATION_SKILL_LABEL_BASE + index, 1);
        func_00464D90(unkdc[index], 99, 0, 0, x + 62.0f, y, 28.0f, 24.0f);
        func_004C6190(unk10, unkb8[index]);
        func_004C6190(unk10, unkdc[index]);
        unkb8[index]->unk3d = 0;
        unkdc[index]->unk3d = 0;
    }
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(278.0f, 161.0f, 0.0f, 0.0f, (s32)associated, 0x32F2, 0);
    footer->set_scale(0.9f, 0.9f);
    func_004C6190(unk10, footer);
    return 1;
}

InventorInformationWindow::~InventorInformationWindow()
{
}

InventorInformationWindow::InventorInformationWindow()
{
    unka8 = 0;
    unkac = 0;
    unkb0 = 0;
    unkb4 = 0;
    for (s32 i = 0; i < 9; i++)
    {
        unkb8[i] = 0;
        unkdc[i] = 0;
    }
    unk100 = 0;
    unk101 = 0;
    unk102 = 0;
}

static inline void set_panel_position(LibClass178630* panel, float x, float y)
{
    panel->unk18.unk08 = x;
    panel->unk18.unk0c = y;
    panel->unk3c = 1;
}

void ItemCreationControlHelp::func_003598E0(u16 mode, u32 unused)
{
    unkb0->unk3f = 0;
    unkac->unk3f = 0;
    unkb8->unk3f = 0;
    unkb4->unk3f = 0;
    unkc0->unk3f = 0;
    unkbc->unk3f = 0;
    unkc8->unk3f = 0;
    unkc4->unk3f = 0;
    unkcc->unk3f = 0;
    unkd0->unk3f = 0;
    unkd4->unk3f = 0;
    unkd8->unk3f = 0;
    switch (mode)
    {
    case 1:
        break;
    case 2:
        set_panel_position(unka8, unkdc, unke0);
        func_4C6DF0(unkb0, func_slot54(), 0x32D9, 0);
        func_4C6DF0(unkac, func_slot54(), 0x32DE, 0);
        func_4C6DF0(unkb8, func_slot54(), 0x32DA, 0);
        func_4C6DF0(unkb4, func_slot54(), 0x32DF, 0);
        func_4C6DF0(unkc0, func_slot54(), 0x32DB, 0);
        func_4C6DF0(unkbc, func_slot54(), 0x32E0, 0);
        func_4C6DF0(unkc8, func_slot54(), 0x32DC, 0);
        func_4C6DF0(unkc4, func_slot54(), 0x32E1, 0);
        unkb0->unk3f = 1;
        unkac->unk3f = 1;
        unkb8->unk3f = 1;
        unkb4->unk3f = 1;
        unkc0->unk3f = 1;
        unkbc->unk3f = 1;
        unkc8->unk3f = 1;
        unkc4->unk3f = 1;
        unkcc->unk3f = 1;
        unkd0->unk3f = 1;
        break;
    case 3:
    case 4:
        set_panel_position(unka8, unkdc, unke4);
        func_4C6DF0(unkb0, func_slot54(), 0x32D9, 0);
        func_4C6DF0(unkac, func_slot54(), 0x15FC5, 0);
        func_4C6DF0(unkb8, func_slot54(), 0x32DB, 0);
        func_4C6DF0(unkb4, func_slot54(), 0x15FA9, 0);
        func_4C6DF0(unkc0, func_slot54(), 0x32DA, 0);
        func_4C6DF0(unkbc, func_slot54(), 0x15FAB, 0);
        unkb0->unk3f = 1;
        unkac->unk3f = 1;
        unkb8->unk3f = 1;
        unkb4->unk3f = 1;
        unkc0->unk3f = 1;
        unkbc->unk3f = 1;
        unkd4->unk3f = 1;
        unkd8->unk3f = 1;
        break;
    }
}

void ItemCreationControlHelp::func_slot5c()
{
    if (this->unkd0 != 0)
    {
        ItemCreationCheckedRecord* record = reinterpret_cast<ItemCreationCheckedRecord*>(D_001B6430->unk04);
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        LibObject174F20* display;
        u32 value;

        if (checksum != func_00457470(record->unka6, ((u8*)record + 0x26),
            end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        display = this->unkd0;
        display->unkfc = value;
        display->unk3c = 1;
    }
    if (this->unkd8 != 0)
    {
        ItemCreationCheckedRecord* record = reinterpret_cast<ItemCreationCheckedRecord*>(D_001B6430->unk04);
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        LibObject174F20* display;
        u32 value;

        if (checksum != func_00457470(record->unka6, ((u8*)record + 0x26),
            end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        display = this->unkd8;
        display->unkfc = value;
        display->unk3c = 1;
    }
}

s32 ItemCreationControlHelp::func_slotf4(void* associated)
{
    unkdc = 168.0f;
    unke0 = 160.0f;
    unke4 = 176.0f;
    FieldClass15AE70::func_slot14(associated, 0, 9, 1800, 460.0f, 72.0f, 0.0f);
    unka8 = new (0) LibClass178630;
    func_004C5A80(unka8, 0, 0.0f, 0.0f, unkdc, unke0, 88.0f);
    func_004C6190(unk10, unka8);
    unkb0 = new (0) LibObject178750;
    unkac = new (0) LibObject178750;
    unkb8 = new (0) LibObject178750;
    unkb4 = new (0) LibObject178750;
    unkc0 = new (0) LibObject178750;
    unkbc = new (0) LibObject178750;
    unkc8 = new (0) LibObject178750;
    unkc4 = new (0) LibObject178750;
    unkcc = new (0) ItemCreationOptionResourceDisplay;
    unkd0 = new (0) LibObject174F20;
    unkd4 = new (0) ItemCreationOptionResourceDisplay;
    unkd8 = new (0) LibObject174F20;
    unkb0->func_004C7FE0(8.0f, 6.0f, 0.0f, 0.0f, (s32)associated, 0x32D9, 0);
    unkac->func_004C7FE0(40.0f, 10.0f, 0.0f, 0.0f, (s32)associated, 0x32DE, 0);
    unkb8->func_004C7FE0(8.0f, 34.0f, 0.0f, 0.0f, (s32)associated, 0x32DA, 0);
    unkb4->func_004C7FE0(40.0f, 40.0f, 0.0f, 0.0f, (s32)associated, 0x32DF, 0);
    unkc0->func_004C7FE0(8.0f, 62.0f, 0.0f, 0.0f, (s32)associated, 0x32DB, 0);
    unkbc->func_004C7FE0(40.0f, 68.0f, 0.0f, 0.0f, (s32)associated, 0x32E0, 0);
    unkc8->func_004C7FE0(8.0f, 90.0f, 0.0f, 0.0f, (s32)associated, 0x32DC, 0);
    unkc4->func_004C7FE0(40.0f, 94.0f, 0.0f, 0.0f, (s32)associated, 0x32E1, 0);
    void* data = func_002D3D80(D_001B643C->unk20, 0);
    unkcc->unkcc = data;
    unkcc->unkd0 = 0;
    unkcc->func_002D6440(func_002D3CC0(D_001B643C->unk20, 25), 5.0f, 126.0f);
    {
        ItemCreationCheckedRecord* record = reinterpret_cast<ItemCreationCheckedRecord*>(D_001B6430->unk04);
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        u32 value;
        if (checksum != func_00457470(record->unka6, ((u8*)record + 0x26), end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        func_00464D90(unkd0, value, (s32)associated, 0, 32.0f, 126.0f, 126.0f, 24.0f);
        unkd0->set_color(0x288080);
    }
    unkd4->unkcc = data;
    unkd4->unkd0 = 0;
    unkd4->func_002D6440(func_002D3CC0(D_001B643C->unk20, 25), 5.0f, 140.0f);
    {
        ItemCreationCheckedRecord* record = reinterpret_cast<ItemCreationCheckedRecord*>(D_001B6430->unk04);
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        u32 value;
        if (checksum != func_00457470(record->unka6, ((u8*)record + 0x26), end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        func_00464D90(unkd8, value, (s32)associated, 0, 32.0f, 140.0f, 126.0f, 24.0f);
        unkd8->set_color(0x288080);
    }
    func_004C6190(unk10, unkac);
    func_004C6190(unk10, unkb0);
    func_004C6190(unk10, unkb4);
    func_004C6190(unk10, unkb8);
    func_004C6190(unk10, unkbc);
    func_004C6190(unk10, unkc0);
    func_004C6190(unk10, unkc4);
    func_004C6190(unk10, unkc8);
    func_004C6190(unk10, unkcc);
    func_004C6190(unk10, unkd0);
    func_004C6190(unk10, unkd4);
    func_004C6190(unk10, unkd8);
    return 1;
}

ItemCreationControlHelp::~ItemCreationControlHelp()
{
}

ItemCreationControlHelp::ItemCreationControlHelp()
{
    unka8 = 0;
    unkac = 0;
    unkb0 = 0;
    unkb4 = 0;
    unkb8 = 0;
    unkbc = 0;
    unkc0 = 0;
    unkc4 = 0;
    unkc8 = 0;
    unkcc = 0;
    unkd0 = 0;
    unkd4 = 0;
    unkd8 = 0;
    unkdc = 0;
    unke0 = 0;
    unke4 = 0;
}

void InventoryItemInstanceList::func_slot10c(u32 value, u32 alternate)
{
    s32 index;
    LibClass178600* nested;
    for (index = 0; index < 6; index++)
    {
        unk138[index]->unk3f = value;
        unk150[index]->unk3f = value;
    }
    nested = unk18c;
    if (nested != 0)
    {
        nested->unk3f = 1;
    }
    nested = FieldStateCE420::unk04;
    if (nested != 0)
    {
        nested->unk3f = alternate;
        if (alternate != 0)
        {
            ItemCreationClass175030* marker = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            marker->ItemCreationClass185050::unk30 = 128.0f;
            marker->unk3c = 1;
        }
        else
        {
            ItemCreationClass175030* marker = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            marker->ItemCreationClass185050::unk30 = 64.0f;
            marker->unk3c = 1;
        }
    }
    nested = FieldStateCE420::unk00;
    if (nested != 0)
    {
        nested->unk3f = alternate;
    }
}

s32 InventoryItemInstanceList::func_slotb8()
{
    ItemCreationAllocationRecord* records[99];
    ItemCreationSelectedDisplayState* state =
        static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    if (unk1b8 == 7)
    {
        return 0;
    }
    if (unk1b0 != 0)
    {
        if (state->unk19c != 0)
        {
            func_002FD940(state->unk19c);
            state->unk1a8 = 1;
        }
        state->unk1a4 = 0;
        state->unk1a0 = 0;
        state->unk1ac = 0;
        unk1b0 = 0;
        unk190->unk3f = 1;
        func_4C6DF0(unk190, state->func_00263CC0(), 0x1B75, 0);
        LibObject178750* display = unk194;
        display->unk18.unk00 = 428.0f;
        display->unk18.unk04 = 330.0f;
        display->unk3c = 1;
        func_4C6DF0(unk194, state->func_00263CC0(), 0x1B76, 0);
        func_00112400(D_001B65F8, 2, 0, 0, 127, 64, 0);
    }
    else
    {
        s32 count = func_0040CF90(D_001B64F8->records, records, (u16)unk1bc);
        s32 selected = unk24;
        if (count != 0 && selected >= 0)
        {
            s32 message = (u16)D_001B64F0[allocation_value_middle(records[selected])].unk10_code + 0x88;
            if (state->unk19c != 0)
            {
                func_002FD940(state->unk19c);
                state->unk1a8 = 1;
            }
            state->unk1a0 = message;
            state->unk1a4 = 0;
            unk1b0 = 1;
            unk190->unk3f = 0;
            func_4C6DF0(unk190, state->func_00263CC0(), 0x1B75, 0);
            LibObject178750* display = unk194;
            display->unk18.unk00 = 405.0f;
            display->unk18.unk04 = 337.0f;
            display->unk3c = 1;
            func_4C6DF0(unk194, state->func_00263CC0(), 0x1B77, 0);
            func_00112400(D_001B65F8, 1, 0, 0, 127, 64, 0);
        }
    }
    return 0;
}

s32 InventoryItemInstanceList::func_slotb4()
{
    ItemCreationSelectedDisplayState* state =
        static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    if (unk1b0 != 0)
    {
        if (state->unk19c != 0)
        {
            func_002FD940(state->unk19c);
            state->unk1a8 = 1;
        }
        state->unk1a4 = 0;
        state->unk1a0 = 0;
        state->unk1ac = 0;
        unk1b0 = 0;
        unk190->unk3f = 1;
        func_4C6DF0(unk190, state->func_00263CC0(), 0x1B75, 0);
        LibObject178750* display = unk194;
        display->unk18.unk00 = 428.0f;
        display->unk18.unk04 = 330.0f;
        display->unk3c = 1;
        func_4C6DF0(unk194, state->func_00263CC0(), 0x1B76, 0);
        return 2;
    }
    else
    {
        state->func_00263F50(this);
        if (state->unk19c != 0)
        {
            func_002FD940(state->unk19c);
            state->unk1a8 = 1;
        }
        state->unk1a4 = 0;
        state->unk1a0 = 0;
        state->unk1ac = 0;
        FieldClass15AD40* parent = static_cast<FieldClass15AD40*>(func_slot44());
        parent->func_slot10c(1, 1);
        D_001B643C->unk10->unk14->func_00263C70(parent);
        return 2;
    }
}

/**
 * @brief Close the category state and clear its active preview fields.
 * @param state Current selection state.
 * @param category Category display to close.
 */
static inline void close_category(ItemCreationSelectedDisplayState* state, void* category)
{
    state->func_00263F50(category);
    if (state->unk19c != 0)
    {
        func_002FD940(state->unk19c);
        state->unk1a8 = 1;
    }
    state->unk1a4 = 0;
    state->unk1a0 = 0;
    state->unk1ac = 0;
}

/**
 * @brief Apply the selected category record and restore its parent display.
 * @return Zero while preview is active, three for an unavailable selection, or one for a valid selection.
 */
s32 InventoryItemInstanceList::func_slotb0()
{
    ItemCreationAllocationRecord* records[99];
    if (unk1b0 != 0)
    {
        return 0;
    }
    ItemCreationSelectedDisplayState* active = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    s32 count = func_0040CF90(D_001B64F8->records, records, (u16)unk1bc);
    s32 selected = FieldStateCE420::unk24;
    if (count == 0 || selected < 0)
    {
        return 3;
    }
    if ((u64)unk138[FieldStateCE420::unk28]->unk94 == 0x505050U)
    {
        return 3;
    }
    ItemCreationAllocationRecord* record = records[selected];
    if (func_0035B310(this, record))
    {
        return 3;
    }
    s16 identifier = func_0040D890(record);
    AssignedInventorGrid* parent = unk1b4->unkbc;
    u8 group;
    PlanItemGroupWindow* mode = unk1b4->unkd0;
    group = parent->unk1f0;
    if (mode != 0)
    {
        if (mode->unk14c == 0)
        {
            close_category(active, this);
            func_0035E150(mode, identifier, -1, 0);
            func_0035D7C0(mode, 1);
            D_001B643C->unk10->unk14->func_00263C70(mode);
            unk1b4->unk1e2[(u8)group][0] = identifier;
        }
        else if (mode->unk14c == 1)
        {
            close_category(active, this);
            ItemCreationSelectedDisplayState* state = unk1b4;
            if (state->unkd0 != 0)
            {
                state->unkd0->func_slot20(0);
            }
            if (state->unkd4 != 0)
            {
                state->unkd4->func_slot20(0);
            }
            unk1b4->unk1c0[(u8)group] = 8;
            set_result_group_marker(unk1b4, (u8)group, 3);
            unk1b4->unk1e2[(u8)group][1] = identifier;
            item_creation_rebuild_line_target(unk1b4, group);
            parent = unk1b4->unkbc;
            FieldObject23CEA0* marker = parent->unkb4;
            marker->FieldClass151C50::unk30 = 128.0f;
            marker->unkae = 1;
            if (parent->unkb4 != 0)
            {
                parent->unkb4->unkad = 1;
            }
            D_001B643C->unk10->unk14->func_00263C70(parent);
        }
        else
        {
            close_category(active, this);
            ItemCreationSelectedDisplayState* state = unk1b4;
            if (state->unkd0 != 0)
            {
                state->unkd0->func_slot20(0);
            }
            if (state->unkd4 != 0)
            {
                state->unkd4->func_slot20(0);
            }
            set_result_group_marker(unk1b4, (u8)group, 2);
            unk1b4->unk1e2[(u8)group][0] = identifier;
            unk1b4->unk1e2[(u8)group][1] = 0;
            item_creation_rebuild_line_target(unk1b4, parent->unk1f0);
            parent = unk1b4->unkbc;
            FieldObject23CEA0* marker = parent->unkb4;
            marker->FieldClass151C50::unk30 = 128.0f;
            marker->unkae = 1;
            if (parent->unkb4 != 0)
            {
                parent->unkb4->unkad = 1;
            }
            D_001B643C->unk10->unk14->func_00263C70(parent);
        }
    }
    return 1;
}

void func_0035AF70(void* object)
{
}

void func_0035AF80(void* object)
{
}

/** @brief Update the category rows and selected item preview. */
void InventoryItemInstanceList::func_slot5c()
{
    ItemCreationAllocationRecord* records[99];
    if (D_001B643C->unk10->unk14->func_00261150() == this && unk1b0 == 0)
    {
        func_002CD7C0(this);
    }
    else if (unk1b0 == 0)
    {
        func_002CDFB0(&static_cast<FieldStateCE420&>(*this));
    }
    if (D_001B643C->unk10->unk14->func_00261150() == this)
    {
        ItemCreationClass175030* marker = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
        marker->ItemCreationClass185050::unk30 = 128.0f;
        marker->unk3c = 1;
    }
    else
    {
        ItemCreationClass175030* marker = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
        marker->ItemCreationClass185050::unk30 = 64.0f;
        marker->unk3c = 1;
    }
    s32 category = unk1bc;
    if (unk1b8 != 7)
    {
        s32 count = func_0040CF90(D_001B64F8->records, records, (u16)category);
        s32 selected = unk24;
        if (count != 0 && selected >= 0)
        {
            s32 displayed = 0;
            for (s32 index = 0; index < 8; index++)
            {
                u16 value = func_0040D930(records[selected], index);
                if (value != 0 && value != 700)
                {
                    LibObject172440* display = unk168[displayed];
                    display->unkfc = value;
                    display->unk3c = 1;
                    unk168[displayed]->unk3f = 1;
                    displayed++;
                }
            }
            for (; displayed < 8; displayed++)
            {
                unk168[displayed]->unk3f = 0;
            }
            LibObject172410* display = unk138[unk28];
            func_002CD8B0(this, display, display->unk94);
        }
        else
        {
            func_002CD8B0(this, 0, 0x808080);
        }
    }
    unk138[0]->unk3f = 0;
    unk150[0]->unk3f = 0;
    unk138[1]->unk3f = 0;
    unk150[1]->unk3f = 0;
    unk138[2]->unk3f = 0;
    unk150[2]->unk3f = 0;
    unk138[3]->unk3f = 0;
    unk150[3]->unk3f = 0;
    unk138[4]->unk3f = 0;
    unk150[4]->unk3f = 0;
    unk138[5]->unk3f = 0;
    unk150[5]->unk3f = 0;
    if (unk1b0 != 0)
    {
        unk198->unk3f = 1;
        unk1a8->unk3f = 1;
        unk1a0->unk3f = 1;
        unk1a4->unk3f = 1;
        FieldStateCE420::unk04->unk3f = 0;
        unk00->unk3f = 0;
        ItemCreationClass172870* marker = unk188;
        marker->unk18.unk04 = 66.0f;
        marker->unk3c = 1;
        func_002CD8B0(this, 0, 0x808080);
    }
    else
    {
        unk198->unk3f = 0;
        unk1a8->unk3f = 0;
        unk1a0->unk3f = 0;
        unk1a4->unk3f = 0;
        unk138[0]->unk3f = 1;
        unk150[0]->unk3f = 1;
        unk138[1]->unk3f = 1;
        unk150[1]->unk3f = 1;
        unk138[2]->unk3f = 1;
        unk150[2]->unk3f = 1;
        unk138[3]->unk3f = 1;
        unk150[3]->unk3f = 1;
        unk138[4]->unk3f = 1;
        unk150[4]->unk3f = 1;
        unk138[5]->unk3f = 1;
        unk150[5]->unk3f = 1;
        FieldStateCE420::unk04->unk3f = 1;
        unk00->unk3f = 1;
        ItemCreationClass172870* marker = unk188;
        marker->unk18.unk04 = 160.0f;
        marker->unk3c = 1;
    }
}

bool func_0035B310(InventoryItemInstanceList* object, const ItemCreationAllocationRecord* record)
{
    if (record == 0)
    {
        return true;
    }
    bool result = false;
    switch (object->unk1b4->unkd0->unk14c)
    {
    case 2:
        if (func_002FBED0(func_0040D890(record)) == 0)
        {
            result = true;
        }
        break;
    case 0:
        if (func_002FC730(func_0040D890(record)) == 0)
        {
            result = true;
        }
        break;
    case 1:
        if (func_002FC880(func_0040D890(record)) == 0)
        {
            result = true;
        }
        break;
    }
    for (s32 index = 0; index < 3; index++)
    {
        if (object->unk1b4->unk1e2[(u16)index][0] == func_0040D890(record))
        {
            result = true;
        }
        if (object->unk1b4->unk1e2[(u16)index][1] == func_0040D890(record))
        {
            result = true;
        }
    }
    return result;
}

void InventoryItemInstanceList::set_scroll_position(float start)
{
    float value = start + 16.0f;
    s32 index = 0;
    do
    {
        LibObject172410* first = unk138[index];
        first->unk18.unk04 = value;
        first->unk3c = 1;
        ItemCreationOptionResourceDisplay* second = unk150[index];
        second->unk18.unk04 = value;
        second->unk3c = 1;
        value += 28.0f;
        index++;
    } while (index < 6);
}

void InventoryItemInstanceList::refresh_rows(s32 start)
{
    ItemCreationAllocationRecord* records[99];
    s32 category = unk1bc;
    func_0013A678(records, 0, sizeof(records));
    unk88 = func_0040CF90(D_001B64F8->records, records, (u16)category);
    for (s32 row = 0; row < 6; row++)
    {
        ItemCreationAllocationRecord* record = records[start + row];
        s32 count = 0;
        if (record != 0)
        {
            for (s32 index = 0; index < 8; index++)
            {
                u16 value = func_0040D930(records[start + row], index);
                if (value != 0 && value != 700)
                {
                    count++;
                }
            }
            if (func_0035B310(this, record))
            {
                LibObject172410* display = unk138[row];
                display->unk94 = ITEM_CREATION_COLOR_DIM;
                display->unk3c = 1;
            }
            else if (record->unk0d_flag)
            {
                LibObject172410* display = unk138[row];
                display->unk94 = 0x508050;
                display->unk3c = 1;
            }
            else
            {
                LibObject172410* display = unk138[row];
                display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                display->unk3c = 1;
            }
            LibObject172410* display = unk138[row];
            u8 value = records[start + row]->unk0c & 0x7F;
            display->unkfc = category;
            display->unkfe = value;
            display->unk3c = 1;
            void* allocation = func_002D3D80(D_001B643C->unk20, 14);
            FieldResourceRecord* resource = func_002D3CC0(D_001B643C->unk20, count + 60);
            func_002D5CF0((FieldResourceDisplay2D5CF0*)unk150[row], allocation, resource, 14);
            unk138[row]->unk3d = 1;
            unk150[row]->unk3d = 1;
        }
        else
        {
            unk138[row]->unk3d = 0;
            unk150[row]->unk3d = 0;
        }
    }
}

/**
 * @brief Create the category list, item previews, and selection displays.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 InventoryItemInstanceList::func_slot104(void* associated)
{
    ItemCreationAllocationRecord* records[99];
    FieldClass15AE70::func_slot14(associated, 0, 9, 2600, 25.0f, 83.0f, 0.0f);
    FieldStateCE420::unk3c = 1;
    unk1ac = new (0) LibObject178660;
    func_004C6510(unk1ac, 5, 0, 0, 25.0f, 83.0f, 0.0f);
    func_00465B20(D_001B657C, unk1ac);
    unk18c = new (0) LibClass178630;
    func_004C5A80(unk18c, 1, 0.0f, 0.0f, 590.0f, 370.0f, 88.0f);
    func_004C6190(unk10, unk18c);
    func_4C4AB0(unk18c, 1500.0f);
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0;
    func_44B570(frame, 16.0f, 16.0f, 600.0f, 140.0f);
    func_004C6190(unk10, frame);
    void* allocation = func_002D3D80(D_001B643C->unk20, 14);
    for (s32 index = 0; index < 6; index++)
    {
        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 60);
        unk150[index] = new (0) ItemCreationOptionResourceDisplay;
        unk150[index]->unkcc = allocation;
        unk150[index]->unkd0 = 14;
        float y = 16.0f + 28.0f * index;
        unk150[index]->func_002D6440(record, 30.0f, y);
        ItemCreationOptionResourceDisplay* resource = unk150[index];
        resource->unk50.unk34 = 0.95f;
        resource->unk50.unk30 = 0.95f;
        resource->unk3c = 1;
        unk150[index]->unk3f = 0;
        func_004C6190(unk10, unk150[index]);
        unk138[index] = new (0) LibObject172410;
        func_413F70(unk138[index], 60.0f, y, 323.99997f, 21.599998f, 100, 0, 0);
        unk138[index]->set_scale(0.9f, 0.9f);
        LibObject172410* display = unk138[index];
        display->unkfa = 1;
        display->unk3c = 1;
        set_depth(unk138[index], -1.0f);
        unk138[index]->unk3f = 0;
        func_004C6190(unk10, unk138[index]);
    }
    frame = new (0) ItemCreationClass1746A0;
    func_44B510(frame, 1);
    func_004C6190(unk10, frame);
    unk188 = new (0) ItemCreationClass172870;
    func_421170(unk188, 24.0f, 160.0f, 550.0f, 4.0f);
    ItemCreationClass172870* divider = unk188;
    divider->unk50 = 0xDC6464;
    divider->unk3c = 1;
    func_004C6190(unk10, unk188);
    for (s32 index = 0; index < 8; index++)
    {
        unk168[index] = new (0) LibObject172440;
        func_4143F0(unk168[index], 0, 1, 0, 24.0f, (float)(175 + 22 * index), 0.0f, 0.0f);
        LibObject172440* display = unk168[index];
        display->unk80 = 0.8f;
        display->unk84 = 0.8f;
        display->unk3c = 1;
        unk168[index]->unk3f = 0;
        func_004C6190(unk1ac, unk168[index]);
    }
    unk198 = new (0) LibObject178750;
    unk198->func_004C7FE0(16.0f, 12.0f, 0.0f, 0.0f, (s32)associated, unk1b8 + 0x1B62, 0);
    set_depth(unk198, -1.0f);
    unk198->set_scale(0.8f, 0.8f);
    unk198->set_color(0x805050);
    unk198->unk3f = 0;
    func_004C6190(unk10, unk198);
    unk1a8 = new (0) LibObject172410;
    func_413F70(unk1a8, 24.0f, 34.0f, 561.6f, 31.199999f, 0, 0, 0);
    LibObject172410* category_display = unk1a8;
    category_display->unkfc = unk1bc;
    category_display->unkfe = 0;
    category_display->unk3c = 1;
    unk1a8->set_scale(1.3f, 1.3f);
    unk1a8->unk3f = 0;
    func_004C6190(unk10, unk1a8);
    if (unk1b8 == 7)
    {
        LibObject178750* title = new (0) LibObject178750;
        title->func_004C7FE0(24.0f, 34.0f, 0.0f, 0.0f, (s32)associated, unk1bc + 0x124F9, 0);
        title->set_scale(1.3f, 1.3f);
        func_004C6190(unk10, title);
        unk1a0 = new (0) LibObject178750;
        unk1a0->func_004C7FE0(24.0f, 76.0f, 534.0f, 66.0f, (s32)associated, unk1bc + 0x128E1, 0);
    }
    else
    {
        unk1a0 = new (0) LibObject178750;
        unk1a0->func_004C7FE0(24.0f, 76.0f, 534.0f, 66.0f, (s32)associated, unk1bc + 0xD6D8, 0);
    }
    unk1a0->set_mode(0);
    unk1a0->set_vertical_alignment(1);
    set_depth(unk1a0, -1.0f);
    unk1a0->set_scale(0.9f, 0.9f);
    unk1a0->unk3f = 0;
    func_004C6190(unk1ac, unk1a0);
    unk1a4 = new (0) LibObject178750;
    unk1a4->func_004C7FE0(16.0f, 150.0f, 0.0f, 0.0f, (s32)associated, 0x15FE0, 0);
    unk1a4->set_scale(0.8f, 0.8f);
    unk1a4->set_color(0x805050);
    set_depth(unk1a4, -1.0f);
    unk1a4->unk3f = 0;
    func_004C6190(unk10, unk1a4);
    unk190 = new (0) LibObject178750;
    unk190->func_004C7FE0(460.0f, 295.0f, 0.0f, 0.0f, (s32)associated, 0x1B75, 0);
    func_004C6190(unk10, unk190);
    unk194 = new (0) LibObject178750;
    unk194->func_004C7FE0(428.0f, 330.0f, 0.0f, 0.0f, (s32)associated, 0x1B76, 0);
    func_004C6190(unk1ac, unk194);
    FieldStateCE420::unk34 = 28.0f;
    FieldStateCE420::unk38 = 28.0f;
    FieldStateCE420::unk04 = new (0) ItemCreationClass175030;
    func_00467360(static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04), 28.0f, 28.0f);
    func_004C6190(unk10, FieldStateCE420::unk04);
    FieldStateCE420::unk04->unk3f = 0;
    FieldStateCE420::unk00 = new (0) ItemCreationClass1725D0;
    func_41A930(static_cast<ItemCreationClass1725D0*>(FieldStateCE420::unk00), 558.0f, 14.0f, 140.0f, 10.0f, 0.0f);
    FieldStateCE420::unk00->unk3f = 0;
    func_004C6190(unk10, FieldStateCE420::unk00);
    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, 5, 378, 28);
    FieldStateCE420::unk2b = 3;
    FieldClass15AE60::unk84 = 0;
    FieldClass15AE60::unk85 = 0;
    func_slot110(1);
    func_slot10c(1, 1);
    unk1b4 = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    FieldClass15AE60::unk88 = 0;
    FieldClass15AE60::unk88 = func_0040CF90(D_001B64F8->records, records, unk1bc);
    s32 visible = FieldClass15AE60::unk88;
    if (visible >= 5)
    {
        visible = 5;
    }
    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, visible, 378, 28);
    func_002CE220(&static_cast<FieldStateCE420&>(*this), FieldClass15AE60::unk88, 0, 0);
    return 1;
}

void InventoryItemInstanceList::func_slot110(u8 value)
{
    unk84 = value;
}

#include "overlays/lib/text_004BD360.h"

/** @brief Release the category container and its base window contents. */
void InventoryItemInstanceList::func_slot0c()
{
    unk1ac->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

InventoryItemInstanceList::~InventoryItemInstanceList()
{
    if (unk18c != 0)
    {
        func_004C4A90(unk18c);
    }
}

/**
 * @brief Set the category marker visibility and depth.
 * @param value Unused first argument.
 * @param alternate Marker visibility and depth mode.
 */
void InventoryItemTypeList::func_slot10c(u32 value, u32 alternate)
{
    LibClass178600* nested = FieldStateCE420::unk04;
    if (nested != 0)
    {
        nested->unk3f = alternate;
        if (alternate != 0)
        {
            ItemCreationClass175030* marker = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            marker->ItemCreationClass185050::unk30 = 128.0f;
            marker->unk3c = 1;
        }
        else
        {
            ItemCreationClass175030* marker = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            marker->ItemCreationClass185050::unk30 = 64.0f;
            marker->unk3c = 1;
        }
    }
}

/** @brief Restore the mode window or its parent selection. @return Always two. */
s32 InventoryItemTypeList::func_slotb4()
{
    func_slot10c(0, 0);
    PlanItemGroupWindow* mode = static_cast<PlanItemGroupWindow*>(func_slot44());
    if (mode != 0)
    {
        if (mode->unk14c == 0)
        {
            AssignedInventorGrid* parent = static_cast<AssignedInventorGrid*>(mode->func_slot44());
            if (parent != 0)
            {
                ItemCreationSelectedDisplayState* state = unk1a0;
                if (state != 0)
                {
                    if (state->unkd0 != 0)
                    {
                        state->unkd0->func_slot20(0);
                    }
                    if (state->unkd4 != 0)
                    {
                        state->unkd4->func_slot20(0);
                    }
                    state = unk1a0;
                    u8 group = parent->unk1f0;
                    state->unk1e2[group][0] = state->unk1f8;
                    state->unk1e2[group][1] = state->unk1fa;
                    state->unk1fa = 0;
                    state->unk1f8 = 0;
                }
            }
            FieldObject23CEA0* marker = parent->unkb4;
            marker->FieldClass151C50::unk30 = 128.0f;
            marker->unkae = 1;
            marker = parent->unkb4;
            if (marker != 0)
            {
                marker->unkad = 1;
            }
            D_001B643C->unk10->unk14->func_00263C70(parent);
        }
        else
        {
            mode->func_slot64();
            D_001B643C->unk10->unk14->func_00263C70(mode);
        }
    }
    return 2;
}

/**
 * @brief Return the category record at the mode list's selected index.
 * @param self Mode list.
 * @return Selected category record, or null.
 */
static inline ItemCreationCategoryRecord* selected_record(InventoryItemTypeList* self)
{
    return static_cast<ItemCreationCategoryRecord*>(func_0036EF70(&self->unk1a8, self->unk24)->unk00);
}
/** @brief Open the selected category. @return One on activation, three on rejection, or zero when unavailable. */
s32 InventoryItemTypeList::func_slotb0()
{
    if (unk88 == 0)
    {
        return 3;
    }
    if (unk1a0 == 0)
    {
        return 0;
    }
    if (FieldClass15AE60::unk8c == 7)
    {
        return 0;
    }
    ItemCreationCategoryRecord* record = selected_record(this);
    if (record != 0)
    {
        LibClass174EF0* display = static_cast<LibClass174EF0*>(unk48[unk28]);
        if (display->unk94 == 0x505050UL)
        {
            return 3;
        }
        if (func_0035CAD0(this, record))
        {
            return 3;
        }
    }
    else
    {
        return 3;
    }
    InventoryItemInstanceList* category = new (0) InventoryItemInstanceList;
    u16 category_id = record->unk02 + 1;
    category->unk1b8 = unk1a4;
    category->unk1bc = category_id;
    category->func_slot104(unk1a0->func_00263CC0());
    category->func_slot40(this);
    unk1a0->func_00263FD0(category);
    unk1a0->func_00263C70(category);
    ItemCreationClass175030* marker = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
    if (marker != 0)
    {
        marker->ItemCreationClass185050::unk30 = 64.0f;
        marker->unk3c = 1;
    }
    return 1;
}

/** @brief Position the mode list rows. @param start Base vertical coordinate. */
void InventoryItemTypeList::set_scroll_position(float start)
{
    s32 index;
    float value = start + 16.0f;
    index = 0;
    do
    {
        LibClass178600* first;
        LibClass178600* second;
        LibClass178600* third;
        first = unk48[index];
        first->unk18.unk00 = 24.0f;
        first->unk18.unk04 = value;
        first->unk3c = 1;
        second = unk138[index];
        second->unk18.unk00 = 326.0f;
        second->unk18.unk04 = value;
        second->unk3c = 1;
        third = unk168[index];
        third->unk18.unk00 = 334.0f;
        third->unk18.unk04 = value;
        third->unk3c = 1;
        value += 28.0f;
        index++;
    } while (index < 12);
}

/** @brief Refresh twelve mode rows beginning at the list index. @param start First list index. */
void InventoryItemTypeList::refresh_rows(s32 start)
{
    if (unk1a0 != 0)
    {
        ItemCreationListNode* node = func_0036EF70(&unk1a8, start);
        for (s32 index = 0; index < 12; index++)
        {
            if (node != 0)
            {
                s32 identifier;
                s32 key;
                ItemCreationCategoryRecord* record = static_cast<ItemCreationCategoryRecord*>(node->unk00);
                if (record != 0)
                {
                    identifier = static_cast<u16>(record->unk02 + 1);
                    key = identifier + 50000;
                    LibClass174EF0* display;
                    if (func_0035CAD0(this, record))
                    {
                        display = static_cast<LibClass174EF0*>(unk48[index]);
                        display->set_color(0x505050);
                    }
                    else if (unk1b8[identifier / 32] & (1 << (identifier % 32)))
                    {
                        display = static_cast<LibClass174EF0*>(unk48[index]);
                        display->set_color(0x508050);
                    }
                    else
                    {
                        display = static_cast<LibClass174EF0*>(unk48[index]);
                        display->set_color(0x808080);
                    }
                    func_4C6DF0(static_cast<LibObject178750*>(unk48[index]), func_slot54(), key, 0);
                    LibObject174F20* value = unk168[index];
                    value->unkfc = record->unk08;
                    value->unk3c = 1;
                    unk48[index]->unk3d = 1;
                    unk168[index]->unk3d = 1;
                    unk138[index]->unk3d = 1;
                }
                node = node->unk04;
            }
            else
            {
                unk48[index]->unk3d = 0;
                unk168[index]->unk3d = 0;
                unk138[index]->unk3d = 0;
            }
        }
    }
}

u8 func_0035CAD0(InventoryItemTypeList* object, const ItemCreationCategoryRecord* category)
{
    ItemCreationAllocationRecord* records[100];
    bool result = false;
    s32 count;
    s32 index;
    switch (object->unk21c->unk14c)
    {
    case 2:
    {
        ItemCreationSelectedDisplayState* selected = object->unk1a0;
        if (selected->unk1c0[(u16)selected->unk1e0] != (u8)D_001B64F0[category->unk02].unk1e_value)
        {
            result = true;
        }
        else
        {
            count = func_0040CF90(D_001B64F8->records, records, category->unk02 + 1);
            for (index = 0; index < count; index++)
            {
                if (func_002FBED0(func_0040D890(records[index])))
                {
                    break;
                }
            }
            if (index == count)
            {
                result = true;
            }
        }
        break;
    }
    case 0:
        if ((u8)D_001B64F0[category->unk02].unk0b_mode != 0)
        {
            result = true;
        }
        else
        {
            count = func_0040CF90(D_001B64F8->records, records, category->unk02 + 1);
            for (index = 0; index < count; index++)
            {
                if (func_002FC730(func_0040D890(records[index])))
                {
                    break;
                }
            }
            if (index == count)
            {
                result = true;
            }
        }
        break;
    case 1:
        if ((u8)D_001B64F0[category->unk02].unk1b_flag == 0)
        {
            result = true;
        }
        else
        {
            count = func_0040CF90(D_001B64F8->records, records, category->unk02 + 1);
            for (index = 0; index < count; index++)
            {
                if (func_002FC880(func_0040D890(records[index])))
                {
                    break;
                }
            }
            if (index == count)
            {
                result = true;
            }
        }
        break;
    }
    return result;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0035CD00);

/** @brief Refresh the active mode list and its selection cursor. */
void InventoryItemTypeList::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        func_002CD8B0(this, 0, 0x808080);
    }
    else
    {
        func_002CD7C0(this);
        if (unk24 >= 0 && unk88 != 0)
        {
            LibClass174EF0* display = static_cast<LibClass174EF0*>(unk48[unk28]);
            func_002CD8B0(this, display, display->unk94);
        }
        else
        {
            func_002CD8B0(this, 0, 0x808080);
        }
    }
}

/** @brief Resize the mode list and rebuild its category rows. @param object Mode list. @param mode Compact display mode. */
extern "C" void func_0035D0C0(InventoryItemTypeList* object, s32 mode)
{
    if (mode != 0)
    {
        LibClass174610& transform = static_cast<LibClass174610&>(*object->unk10);
        func_44B190(&transform, transform.unk20.components[0], 186.0f);
        set_height(object->unk198, 280.0f);
        set_height(object->unk19c, 248.0f);
        set_height(object->FieldStateCE420::unk00, 260.0f);
        object->unk218 = 9;
    }
    else
    {
        LibClass174610& transform = static_cast<LibClass174610&>(*object->unk10);
        func_44B190(&transform, transform.unk20.components[0], 128.0f);
        set_height(object->unk198, 336.0f);
        set_height(object->unk19c, 310.0f);
        set_height(object->FieldStateCE420::unk00, 300.0f);
        object->unk218 = 11;
    }
    object->func_slot11c(1, 0);
}

/** @brief Create the mode list widgets and initialize its selection. @param associated Associated source. @return Always one. */
s32 InventoryItemTypeList::func_slot104(void* associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 2400, 220.0f, 128.0f, 0.0f);
    unk3c = 1;
    unk198 = new (0) LibClass178630;
    func_004C5A80(unk198, 1, 0.0f, 0.0f, 400.0f, 336.0f, 88.0f);
    func_004C6190(unk10, unk198);
    unk19c = new (0) ItemCreationClass1746A0;
    func_44B570(unk19c, 18.0f, 14.0f, 378.0f, 316.0f);
    func_004C6190(unk10, unk19c);
    for (s32 index = 0; index < 12; index++)
    {
        unk48[index] = new (0) LibObject178750;
        unk138[index] = new (0) LibObject178750;
        unk168[index] = new (0) LibObject174F20;
        float y = 16.0f + 28.0f * index;
        static_cast<LibObject178750*>(unk48[index])->func_004C7FE0(22.0f, y, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 50000, 0);
        unk138[index]->func_004C7FE0(326.0f, y - 4.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 2020, 1);
        func_00464D90(unk168[index], index, reinterpret_cast<s32>(associated), 1, 334.0f, y, 28.0f, 24.0f);
        LibClass174EF0* display = static_cast<LibClass174EF0*>(unk48[index]);
        display->unk88 = -1.0f;
        display->unk3c = 1;
        display = static_cast<LibClass174EF0*>(unk48[index]);
        display->set_scale(0.9f, 0.9f);
        func_004C6190(unk10, unk48[index]);
        func_004C6190(unk10, unk138[index]);
        func_004C6190(unk10, unk168[index]);
    }
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0;
    func_44B510(frame, 1);
    func_004C6190(unk10, frame);
    FieldStateCE420::unk34 = 20.0f;
    FieldStateCE420::unk38 = 28.0f;
    FieldStateCE420::unk04 = new (0) ItemCreationClass175030;
    func_00467360(static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04), 20.0f, 28.0f);
    func_004C6190(unk10, FieldStateCE420::unk04);
    FieldStateCE420::unk04->unk3f = 0;
    FieldStateCE420::unk00 = new (0) ItemCreationClass1725D0;
    func_41A930(static_cast<ItemCreationClass1725D0*>(FieldStateCE420::unk00), 376.0f, 16.0f, 308.0f, 10.0f, 0.0f);
    func_004C6190(unk10, FieldStateCE420::unk00);
    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, unk218, 378, 28);
    unk2b = 3;
    unk84 = 0;
    unk85 = 0;
    func_slot10c(1, 0);
    func_slot11c(1, 0);
    return 1;
}

/**
 * @brief Initialize the mode list and retain its selection state.
 * @param state Selection state associated with the window.
 */
InventoryItemTypeList::InventoryItemTypeList(ItemCreationSelectedDisplayState* state)
{
    for (s32 index = 0; index < 12; index++)
    {
        unk48[index] = 0;
        unk138[index] = 0;
        unk168[index] = 0;
    }
    unk1a0 = 0;
    unk1a0 = state;
    FieldClass15AD40();
    unk1a4 = 0;
    unk1b4 = 0;
    unk218 = 11;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0035D7C0);

void func_0035E150(PlanItemGroupWindow* object, s16 value, s32 quantity, s8 index)
{
    object->unk10c = value;
    if (object->unk10c != 0)
    {
        ItemCreationAllocationRecord* record = allocation_record_middle(object->unk10c);
        u16 decoded = allocation_value_middle(record);
        u8 flag = record->unk0c & 0x7F;
        LibObject172410* display = object->unk11c[index];
        display->unkfc = decoded + 1;
        display->unkfe = flag;
        display->unk3c = 1;
        object->unk11c[index]->unk3f = 1;
        if (quantity == -1)
        {
            object->unk140[index]->unk3f = 0;
            object->unk128[index * 2 + 1]->unk3f = 0;
        }
        else
        {
            LibObject174F20* quantity_display = object->unk140[index];
            quantity_display->unkfc = quantity;
            quantity_display->unk3c = 1;
            object->unk140[index]->unk3f = 1;
            object->unk128[index * 2 + 1]->unk3f = 1;
        }
    }
    else
    {
        object->unk11c[index]->unk3f = 0;
        object->unk128[index * 2 + 1]->unk3f = 0;
        object->unk140[index]->unk3f = 0;
    }
}

/**
 * @brief Set the selector depth and request a refresh when present.
 * @param selector Selection widget to update, or null.
 * @param depth Depth value.
 */
static inline void set_selector_depth(FieldClass153130* selector, float depth)
{
    if (selector != 0)
    {
        selector->ItemCreationClass185050::unk30 = depth;
        selector->LibClass178600::unk3c = 1;
    }
}

/**
 * @brief Set the grid depth and request a refresh when present.
 * @param selector Grid to update, or null.
 * @param depth Depth value.
 */
static inline void set_selector_depth(FieldObject23CEA0* selector, float depth)
{
    if (selector != 0)
    {
        selector->FieldClass151C50::unk30 = depth;
        selector->LibClass174610::unkae = 1;
    }
}

/** @brief Restore the group selector depth and request its redraw. */
void PlanItemGroupWindow::func_slot64()
{
    set_selector_depth(unkac, 128.0f);
}


/**
 * @brief Restore the prior item pair and return to the parent window.
 * @return Always two.
 */
s32 PlanItemGroupWindow::func_slotb4()
{
    if (unk14c == 1)
    {
        func_0035D7C0(this, 0);
        return 2;
    }
    AssignedInventorGrid* parent = static_cast<AssignedInventorGrid*>(func_slot44());
    if (parent != 0)
    {
        ItemCreationSelectedDisplayState* state = unka8;
        if (state != 0)
        {
            if (state->unkd0 != 0)
            {
                state->unkd0->func_slot20(0);
            }
            if (state->unkd4 != 0)
            {
                state->unkd4->func_slot20(0);
            }
            state = unka8;
            u8 group = parent->unk1f0;
            state->unk1e2[group][0] = state->unk1f8;
            state->unk1e2[group][1] = state->unk1fa;
            state->unk1fa = 0;
            state->unk1f8 = 0;
        }
        FieldObject23CEA0* marker = parent->unkb4;
        marker->FieldClass151C50::unk30 = 128.0f;
        marker->unkae = 1;
        marker = parent->unkb4;
        if (marker != 0)
        {
            marker->unkad = 1;
        }
        D_001B643C->unk10->unk14->func_00263C70(parent);
    }
    return 2;
}

/**
 * @brief Open the related list while the selection widget is active.
 * @return Zero for a missing or inactive selector; one after opening the list.
 */
s32 PlanItemGroupWindow::func_slotb0()
{
    FieldClass153130* selector = unkac;
    if (selector == 0)
    {
        return 0;
    }
    bool inactive = !selector->ItemCreationClass185050::unk35;
    if (inactive)
    {
        return 0;
    }
    set_selector_depth(selector, 64.0f);
    unkac->func_0023B3A0();
    unk150->func_slot10c(1, 1);
    unk150->func_slot110(1);
    ItemCreationControlState* controls = D_001B643C->unk0c;
    if (controls != 0)
    {
        controls->unk9a = 1;
    }
    D_001B643C->unk10->unk14->func_00263C70(unk150);
    return 1;
}

/** @brief Refresh the selected mode colors, marker, and related list. */
void PlanItemGroupWindow::func_slot6c()
{
    if (unkac != 0 && (u8)unkac->func_0023B3B0(1) != 1)
    {
        u16 raw_index = unkac->func_0023B3A0();
        s16 selected = raw_index;
        if (unkac != 0)
        {
            s32 index;
            for (index = 0; index < unkb4; index++)
            {
                ItemCreationListNode* node = func_0036F230(&unk2c, index);
                LibObject178750* display = static_cast<LibObject178750*>(node->unk00);
                if (index == selected)
                {
                    display->set_color(0x288080);
                    unkb0->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(0x808080);
                }
            }
        }
        u8 selection = (u8)unkac->func_0023B3A0();
        unk150->func_slot11c(1, selection);
        unk150->func_slot10c(1, 0);
    }
}

/** @brief Refresh the previous mode colors, marker, and related list. */
void PlanItemGroupWindow::func_slot68()
{
    if (unkac != 0 && (u8)unkac->func_0023B3B0(0) != 1)
    {
        u16 raw_index = unkac->func_0023B3A0();
        s16 selected = raw_index;
        if (unkac != 0)
        {
            s32 index;
            for (index = 0; index < unkb4; index++)
            {
                ItemCreationListNode* node = func_0036F230(&unk2c, index);
                LibObject178750* display = static_cast<LibObject178750*>(node->unk00);
                if (index == selected)
                {
                    display->set_color(0x288080);
                    unkb0->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(0x808080);
                }
            }
        }
        u8 selection = (u8)unkac->func_0023B3A0();
        unk150->func_slot11c(1, selection);
        unk150->func_slot10c(1, 0);
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0035E770);

PlanItemGroupWindow::~PlanItemGroupWindow()
{
}

/** @brief Initialize the plan window for its selection state. @param state Owning selection state. */
PlanItemGroupWindow::PlanItemGroupWindow(ItemCreationSelectedDisplayState* state)
{
    unka8 = 0;
    unka8 = state;
    unkac = 0;
    unkb0 = 0;
    unkb4 = 0;
    unkb8 = 0;
    unk150 = 0;
    for (s32 i = 0; i < 6; i++)
    {
        unkc8[i] = 0;
        unke0[i] = 0;
    }
    for (s32 i = 0; i < 4; i++)
    {
        unkfc[i] = 0;
    }
    unkbc = 0;
    unkc0 = 0;
    unkc4 = 0;
    FieldClass15AE70();
}

/**
 * @brief Reset the choice displays and return to the parent when enabled.
 * @return Always two.
 */
s32 InventionPolicyWindow::func_slotb4()
{
    func_slot20(0);
    unkcc->func_0023B310();
    if (unkcc != 0)
    {
        for (s32 index = 0; index < 2; index++)
        {
            LibObject178750* display = unkb4[index];
            if (index == 0)
            {
                display->set_color(0x288080);
                unkd0->func_0023B7E0(display);
            }
            else
            {
                display->set_color(0x808080);
            }
        }
    }
    u8 mode = unkd4;
    if (mode != 1)
    {
        switch (mode)
        {
        case 0:
            if (unka8 != 0)
            {
                FieldObject23CEA0* marker = unka8->unkb4;
                marker->FieldClass151C50::unk30 = 128.0f;
                marker->unkae = 1;
                D_001B643C->unk10->unk14->func_00263C70(unka8);
            }
            break;
        }
    }
    return 2;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0035F2D0);

/** @brief Move the selector and refresh the choice colors and target marker. */
void InventionPolicyWindow::func_slot6c()
{
    if (this->unkcc != 0 && (u8)this->unkcc->func_0023B3B0(1) != 1)
    {
        u16 selected = this->unkcc->func_0023B3A0();
        if (this->unkcc != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                LibObject178750* display = this->unkb4[index];
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    this->unkd0->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
}

/** @brief Move the selector and refresh the choice colors and target marker. */
void InventionPolicyWindow::func_slot68()
{
    if (this->unkcc != 0 && (u8)this->unkcc->func_0023B3B0(0) != 1)
    {
        u16 selected = this->unkcc->func_0023B3A0();
        if (this->unkcc != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                LibObject178750* display = this->unkb4[index];
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    this->unkd0->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
}

/**
 * @brief Create the two choice displays and their selection widgets.
 * @param associated Object associated with the window.
 * @return Zero without a parent, otherwise one.
 */
s32 InventionPolicyWindow::func_slotf4(void* associated)
{
    unka8 = static_cast<AssignedInventorGrid*>(func_slot44());
    if (unka8 == 0)
    {
        return 0;
    }
    unkbc = 382.0f;
    unkc0[0] = 224.0f;
    unkc0[1] = 302.0f;
    unkc0[2] = 380.0f;
    FieldClass15AE70::func_slot10(associated, unkbc, unkc0[0], 14);
    unkb0 = new (0) LibClass178630;
    func_004C5A80(unkb0, 0, 0.0f, 0.0f, 204.0f, 100.0f, 88.0f);
    func_004C6190(unk10, unkb0);
    for (s32 index = 0; index < 2; index++)
    {
        unkb4[index] = new (0) LibObject178750;
        unkb4[index]->func_004C7FE0(20.0f, 20.0f + 32.0f * index, 0.0f, 0.0f, (s32)associated, index + 0x15FD4, 0);
        func_004C6190(unk10, unkb4[index]);
    }
    unkcc = new (0) FieldClass153130;
    unkcc->func_0023B530(1, 2, 1, 0, 1, 16.0f, 32.0f, 0.0f, 32.0f);
    func_004C6190(unk10, unkcc);
    unkd0 = new (0) FieldClass153170;
    unkd0->func_0023B850(unkb4[0], 0x288080);
    func_004C6190(unk10, unkd0);
    if (unkcc != 0)
    {
        for (s32 index = 0; index < 2; index++)
        {
            LibObject178750* display = unkb4[index];
            if (index == 0)
            {
                display->set_color(0x288080);
                unkd0->func_0023B7E0(display);
            }
            else
            {
                display->set_color(0x808080);
            }
        }
    }
    return 1;
}

InventionPolicyWindow::~InventionPolicyWindow()
{
}

InventionPolicyWindow::InventionPolicyWindow(void* object)
{
    unka8 = 0;
    unkac = 0;
    unkb0 = 0;
    unkb4[0] = 0;
    unkb4[1] = 0;
    unkbc = 0;
    unkc0[0] = 0;
    unkc0[1] = 0;
    unkc0[2] = 0;
    unkcc = 0;
    unkd0 = 0;
    unkd4 = 0;
    unkd8 = 0;
    unkd8 = object;
    unkdc = 0;
    unke0 = 0;
}

/**
 * @brief Apply the selectable creation-skill color and selected row marker.
 * @param object Creation-skill selection window.
 * @param text Skill-label display.
 * @param index Zero-based skill row.
 * @param selected Selected skill row.
 * @param mask Facility bit enabling this creation skill.
 */
static inline void highlight_skill_label(CreationSkillWindow* object, LibObject178750* text, s32 index, u16 selected, u16 mask)
{
    if (object->selectable_skill_mask & mask)
    {
        text->unk94 = 0x808080;
        text->unk3c = 1;
        if (index == selected)
        {
            text->unk94 = 0x288080;
            text->unk3c = 1;
            object->skill_marker->func_0023B7E0(text);
            object->skill_marker->unk3f = 1;
        }
    }
}

/**
 * @brief Update creation-skill colors and the selected skill marker.
 * @param object Creation-skill selection window.
 * @param selected Selected skill row.
 */
extern "C" void item_creation_update_skill_labels(CreationSkillWindow* object, u16 selected)
{
    for (s32 index = 0; index < 8; index++)
    {
        LibObject178750* text = object->skill_labels[index];
        if (text != 0)
        {
            text->unk94 = 0x505050;
            text->unk3c = 1;
        }
    }
    if (object->skill_marker != 0)
    {
        object->skill_marker->unk3f = 0;
    }
    for (s32 index = 0; index < 8; index++)
    {
        ItemCreationSelectedDisplayState* state = object->unka8;
        LibObject178750* text = object->skill_labels[index];
        if (state->workshop_skill_enabled[(u8)(index + 1) - 1] != 0)
        {
            if (text != 0)
            {
                text->unk94 = 0x505080;
                text->unk3c = 1;
            }
            switch (index + 1)
            {
            case 1:
                highlight_skill_label(object, text, index, selected, ITEM_CREATION_FACILITY_COOK);
                break;
            case 2:
                highlight_skill_label(object, text, index, selected, ITEM_CREATION_FACILITY_ALCH);
                break;
            case 3:
                highlight_skill_label(object, text, index, selected, ITEM_CREATION_FACILITY_CRFT);
                break;
            case 4:
                highlight_skill_label(object, text, index, selected, ITEM_CREATION_FACILITY_CMPD);
                break;
            case 5:
                highlight_skill_label(object, text, index, selected, ITEM_CREATION_FACILITY_SMTH);
                break;
            case 6:
                highlight_skill_label(object, text, index, selected, ITEM_CREATION_FACILITY_WRIT);
                break;
            case 7:
                highlight_skill_label(object, text, index, selected, ITEM_CREATION_FACILITY_ENG);
                break;
            case 8:
                highlight_skill_label(object, text, index, selected, ITEM_CREATION_FACILITY_SYTH);
                break;
            }
        }
    }
}


/**
 * @brief Reset the skill selection and handle the current return mode.
 * @return Always two.
 */
s32 CreationSkillWindow::func_slotb4()
{
    func_slot20(0);
    skill_selector->func_0023B310();
    item_creation_update_skill_labels(this, 0);
    switch (unkdc)
    {
    case 0:
        if (unkac != 0)
        {
            FieldObject23CEA0* marker = unkac->unkb4;
            marker->FieldClass151C50::unk30 = 128.0f;
            marker->unkae = 1;
            D_001B643C->unk10->unk14->func_00263C70(unkac);
        }
        break;
    case 1:
        unkdc = 0;
        break;
    }
    return 2;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003600E0);

/**
 * @brief Refresh the creation-skill display after selection movement.
 */
void CreationSkillWindow::func_slot6c()
{
    if (skill_selector != 0 && (u8)skill_selector->func_0023B3B0(1) != 1)
    {
        u16 selected = skill_selector->func_0023B3A0();
        item_creation_update_skill_labels(this, selected);
    }
}
/**
 * @brief Refresh the creation-skill display after selection movement.
 */
void CreationSkillWindow::func_slot68()
{
    if (skill_selector != 0 && (u8)skill_selector->func_0023B3B0(0) != 1)
    {
        u16 selected = skill_selector->func_0023B3A0();
        item_creation_update_skill_labels(this, selected);
    }
}
/**
 * @brief Create the eight creation-skill labels and selection widgets.
 * @param associated Object associated with the window.
 * @return Zero without a parent, otherwise one.
 */
s32 CreationSkillWindow::func_slotf4(void* associated)
{
    unkac = static_cast<AssignedInventorGrid*>(func_slot44());
    if (unkac == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 312.0f, 224.0f, 14);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 96.0f, 248.0f, 88.0f);
    func_004C6190(unk10, panel);
    for (s32 index = 0; index < 8; index++)
    {
        skill_labels[index] = new (0) LibObject178750;
        skill_labels[index]->func_004C7FE0(20.0f, 12.0f + 28.0f * index, 0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_SKILL_LABEL_BASE, 0);
        func_004C6190(unk10, skill_labels[index]);
        if (unka8->workshop_skill_enabled[(u8)(index + 1) - 1] != 0)
        {
            skill_labels[index]->set_color(0x808080);
        }
        else
        {
            skill_labels[index]->set_color(0x505050);
        }
    }
    skill_selector = new (0) FieldClass153130;
    skill_selector->func_0023B530(1, 8, 1, 0, 1, 16.0f, 24.0f, 0.0f, 28.0f);
    func_004C6190(unk10, skill_selector);
    skill_marker = new (0) FieldClass153170;
    skill_marker->func_0023B850(skill_labels[0], 0x288080);
    func_004C6190(unk10, skill_marker);
    item_creation_update_skill_labels(this, 0);
    return 1;
}

CreationSkillWindow::~CreationSkillWindow()
{
}

CreationSkillWindow::CreationSkillWindow(void* object)
{
    unka8 = 0;
    unka8 = static_cast<ItemCreationSelectedDisplayState*>(object);
    unkac = 0;
    panel = 0;
    skill_labels[0] = 0;
    skill_labels[1] = 0;
    skill_labels[2] = 0;
    skill_labels[3] = 0;
    skill_labels[4] = 0;
    skill_labels[5] = 0;
    skill_labels[6] = 0;
    skill_labels[7] = 0;
    skill_selector = 0;
    skill_marker = 0;
    unkdc = 0;
    selectable_skill_mask = 0;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003608C0);

void func_00360E60(AssignedInventorGrid* object, u16 mode)
{
    s32 index;

    switch (mode)
    {
    case 1:
        if (object->unkb4 != 0)
        {
            func_0023CEA0(object->unkb4, 1);
        }
        func_00361220(object);
        break;
    case 0:
        if (object->unka8->unk128 != 1)
        {
            if (object->unkac != 0)
            {
                func_0023CEA0(object->unkac, 0);
            }
            if (object->unkb0 != 0)
            {
                func_0023CEA0(object->unkb0, 0);
            }
        }
        else
        {
            if (object->unkb4 != 0)
            {
                func_0023CEA0(object->unkb4, 0);
            }
        }
        for (index = 0; index < 9; index++)
        {
            object->unkb8[index]->unk3f = 0;
        }
        for (index = 0; index < 12; index++)
        {
            object->unkdc[index]->unk3f = 0;
            object->unk10c[index]->unk3f = 0;
        }
        break;
    }
}

/** @brief Hide the inventor detail window or update the assigned-grid selection. @param object Assigned inventor grid. */
extern "C" void func_00360FD0(AssignedInventorGrid* object)
{
    if (object->unka8 != 0 && object->unkb4 != 0)
    {
        s16 index = object->unkb4->unk114;
        if ((u32)(index - 3) <= 1U || (u32)(index - 8) <= 1U || index == 13 || index == 14)
        {
            InventorInformationWindow* details = object->unka8->unkc0;
            if (details != 0)
            {
                details->func_slot20(0);
                details->unk100 = 0;
            }
            return;
        }
        if ((u32)(index - 5) <= 1U || index == 7)
        {
            index -= 2;
        }
        if ((u32)(index - 10) <= 1U || index == 12)
        {
            index -= 4;
        }
        item_creation_show_inventor_information(object->unka8, object, index);
    }
}

/**
 * @brief Update the selection grids and the window's display activation.
 * @tparam Window Window type with primary, alternate and selected grids.
 * @param object Selection window.
 * @param enabled Full-word display flag; zero disables the grids.
 */
template <class Window>
static inline void update_selection_markers(Window* object, u32 enabled)
{
    if (object->unkac)
    {
        if (enabled)
        {
            if (object == D_001B643C->unk10->unk14->func_00261150())
            {
                if (object->unkb4 == object->unkac)
                {
                    func_0023CEA0(object->unkac, 1);
                }
                else
                {
                    func_0023CEA0(object->unkac, 0);
                }
            }
            else
            {
                func_0023CEA0(object->unkac, 0);
            }
        }
        else
        {
            func_0023CEA0(object->unkac, 0);
        }
    }
    if (object->unkb0)
    {
        if (enabled)
        {
            if (object == D_001B643C->unk10->unk14->func_00261150())
            {
                if (object->unkb4 == object->unkb0)
                {
                    func_0023CEA0(object->unkb0, 1);
                }
                else
                {
                    func_0023CEA0(object->unkb0, 0);
                }
            }
            else
            {
                func_0023CEA0(object->unkb0, 0);
            }
        }
        else
        {
            func_0023CEA0(object->unkb0, 0);
        }
    }
    object->func_slot20(enabled);
}

/** @brief Update the two selection markers, then set the window activation. @param object Nine-slot window. @param active Activation value. */
extern "C" void func_003610D0(AssignedInventorGrid* object, u32 active)
{
    update_selection_markers(object, active);
}

void func_00361220(AssignedInventorGrid* object)
{
    s16 selected;

    if (object->unkb4 != 0)
    {
        selected = object->unkb4->unk114;
        for (s32 index = 0; index < 9; index++)
        {
            object->unkb8[index]->unk3f = 0;
        }
        for (s32 index = 0; index < 12; index++)
        {
            object->unkdc[index]->unk3f = 0;
            object->unk10c[index]->unk3f = 0;
        }
        if (object->unka8->unk57 != 0 && object->unkb4->unkad != 0)
        {
            switch (selected)
            {
            case 0:
                object->unkb8[0]->unk3f = 1;
                break;
            case 1:
                object->unkb8[1]->unk3f = 1;
                break;
            case 2:
                object->unkb8[2]->unk3f = 1;
                break;
            case 3:
                object->unkdc[0]->unk3f = 1;
                object->unkdc[1]->unk3f = 1;
                object->unkdc[2]->unk3f = 1;
                object->unkdc[3]->unk3f = 1;
                break;
            case 4:
                object->unk10c[0]->unk3f = 1;
                object->unk10c[1]->unk3f = 1;
                object->unk10c[2]->unk3f = 1;
                object->unk10c[3]->unk3f = 1;
                break;
            case 5:
                object->unkb8[3]->unk3f = 1;
                break;
            case 6:
                object->unkb8[4]->unk3f = 1;
                break;
            case 7:
                object->unkb8[5]->unk3f = 1;
                break;
            case 8:
                object->unkdc[4]->unk3f = 1;
                object->unkdc[5]->unk3f = 1;
                object->unkdc[6]->unk3f = 1;
                object->unkdc[7]->unk3f = 1;
                break;
            case 9:
                object->unk10c[4]->unk3f = 1;
                object->unk10c[5]->unk3f = 1;
                object->unk10c[6]->unk3f = 1;
                object->unk10c[7]->unk3f = 1;
                break;
            case 10:
                object->unkb8[6]->unk3f = 1;
                break;
            case 11:
                object->unkb8[7]->unk3f = 1;
                break;
            case 12:
                object->unkb8[8]->unk3f = 1;
                break;
            case 13:
                object->unkdc[8]->unk3f = 1;
                object->unkdc[9]->unk3f = 1;
                object->unkdc[10]->unk3f = 1;
                object->unkdc[11]->unk3f = 1;
                break;
            case 14:
                object->unk10c[8]->unk3f = 1;
                object->unk10c[9]->unk3f = 1;
                object->unk10c[10]->unk3f = 1;
                object->unk10c[11]->unk3f = 1;
                break;
            }
        }
    }
}

/**
 * @brief Refresh the nine assigned-inventor portraits and their inventor IDs.
 * @param object Inventor grid for the three development lines.
 */
void func_003614B0(AssignedInventorGrid* object)
{
    void* allocation;
    u32 portrait_index;
    s32 slot_index;
    u32 inventor_option_code;
    FieldResourceRecord* record;

    object->unk190 = 0;
    for (slot_index = 0; slot_index < 9; slot_index++)
    {
        inventor_option_code = object->unka8->unk68[(u16)slot_index];
        if (inventor_option_code != 0)
        {
            portrait_index = (u8)item_resource_index_middle(inventor_option_code);
            allocation = func_002D3D80(D_001B643C->unk20, portrait_index);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            object->unk13c[slot_index]->func_002D5CF0(allocation, record, portrait_index);
            object->unk13c[slot_index]->unk3f = 1;
            object->unk190++;
            object->unk1f2[slot_index] = item_assigned_code(inventor_option_code);
        }
        else
        {
            object->unk13c[slot_index]->unk3f = 0;
            object->unk1f2[slot_index] = 0;
        }
    }
}

/** @brief Apply the selected three-component item. @return Action status. */
s32 AssignedInventorGrid::func_slotbc()
{
    if (unk214 == 0)
    {
        return 0;
    }
    if (unka8->unk47 != 1)
    {
        return 0;
    }
    if (unka8->unk128 == 1)
    {
        return 3;
    }
    for (s32 index = 0; index < 3; index++)
    {
        unk218[index] = 0;
        unk21b[index] = 0;
    }
    u8 active_count = 0;
    for (s32 index = 0; index < unk1f1; index++)
    {
        unk218[index] = func_003623C0(this, index);
        if (unk218[index] != 0)
        {
            if (unk1fc[index] != 0 && unk208[index] != 0)
            {
                unk21b[index] = 1;
            }
            else
            {
                unk21b[index] = 0;
            }
            active_count++;
        }
        else if (unk1fc[index] == 0 && unk208[index] == 0)
        {
            unk21b[index] = 1;
        }
        else
        {
            unk21b[index] = 0;
        }
    }
    if (active_count == 0)
    {
        return 3;
    }
    s32 index;
    for (index = 0; index < 3; index++)
    {
        if ((s32)unka8->unk1c8[index] > 0)
        {
            break;
        }
    }
    if (index == 3)
    {
        return 3;
    }
    ItemCreationCheckedRecord* record = D_001B643C->unk00;
    u16 checksum = record->unka4;
    const u8* end = (const u8*)&record->unka4;
    u32 value;
    if (checksum != func_00457470(record->unka6, ((u8*)record + 0x26), end - ((const u8*)record + 0x26)))
    {
        value = 0;
    }
    else
    {
        value = record->unk34 ^ 0x7CE3C7F7;
    }
    ItemCreationSelectedDisplayState* state = unka8;
    if (value < state->unk1c8[2] + (state->unk1c8[0] + state->unk1c8[1]))
    {
        InsufficientFolDialog* popup = new (0) InsufficientFolDialog;
        popup->func_slotf4(unka8->func_00263CC0());
        popup->func_slot40(this);
        unka8->func_00263FD0(popup);
        unka8->func_00263C70(popup);
        if (unkb4 != 0)
        {
            unkb4->unkad = 0;
        }
        return 3;
    }
    StartInventingDialog* child = unk214;
    for (index = 0; index < 3; index++)
    {
        child->unkbc[index] = 0;
    }
    for (s32 part = 0; part < unk1f1; part++)
    {
        if (unk218[part] != 0 || unk21b[part] != 0)
        {
            if (unk218[part] == 1 && unk21b[part] == 0)
            {
                StartInventingDialog* reset = unk214;
                for (s32 flag = 0; flag < 3; flag++)
                {
                    reset->unkbc[flag] = 0;
                }
                return 3;
            }
            if (unk218[part] == 1 && unk21b[part] == 1)
            {
                unk214->unkbc[part] = 1;
            }
        }
    }
    if (unkb4 != 0)
    {
        unkb4->unkad = 0;
    }
    child = unk214;
    child->func_slot20(1);
    LibObject178750* first = child->unkac;
    first->unk94 = ITEM_CREATION_COLOR_BRIGHT;
    first->unk3c = 1;
    LibObject178750* second = child->unkb0;
    second->unk94 = ITEM_CREATION_COLOR_SELECTED;
    second->unk3c = 1;
    child->unkb8->func_0023B7E0(child->unkb0);
    func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(child->unkb4)), 1);
    D_001B643C->unk10->unk14->func_00263C70(unk214);
    return 1;
}


/** @brief Toggle information for the selected inventor. @return One when available, or zero for a non-inventor cell or missing state. */
s32 AssignedInventorGrid::func_slotb8()
{
    u8 active;
    if (unka8 == 0)
    {
        return 0;
    }
    if (unkb4 == 0)
    {
        return 0;
    }
    s16 index = unkb4->unk114;
    if ((u32)(index - 3) <= 1U || (u32)(index - 8) <= 1U || index == 13 || index == 14)
    {
        return 0;
    }
    func_00360FD0(this);
    InventorInformationWindow* details = unka8->unkc0;
    if (details != 0)
    {
        active = !details->unk100;
        details->func_slot20(active);
        details->unk100 = active;
    }
    return 1;
}

/** @brief Restore the active selection window or leave item selection. @return Two when handled; zero when inactive. */
s32 AssignedInventorGrid::func_slotb4()
{
    ItemCreationSelectedDisplayState* state = unka8;
    if (state == 0)
    {
        return 0;
    }
    if (unkb4 == 0)
    {
        return 0;
    }
    if (state->unk47 != 1)
    {
        return 0;
    }
    if (state->unk128 == 1 && state->unk11c != this)
    {
        AvailableInventorGrid* other = state->unkb8;
        FieldObject23CEA0* primary = unkac;
        primary->FieldClass151C50::unk30 = 128.0f;
        primary->unkae = 1;
        func_0023CEA0(unkb0, 0);
        FieldObject23CEA0* alternate = unkb0;
        alternate->index = unkac->unk114;
        func_0023CB30(alternate);
        func_0023C7B0(unkb0);
        unkb4 = unkac;
        func_00361220(this);
        primary = other->unkac;
        primary->FieldClass151C50::unk30 = 128.0f;
        primary->unkae = 1;
        func_0023CEA0(other->unkb0, 0);
        alternate = other->unkb0;
        alternate->index = other->unkac->unk114;
        func_0023CB30(alternate);
        func_0023C7B0(other->unkb0);
        other->unkb4 = other->unkac;
        if (other->unkb4 != 0)
        {
            s16 selected = other->unkb4->unk114;
            for (s32 index = 0; index < 14; index++)
            {
                if (selected == index)
                {
                    other->unkb8[index]->unk3f = 1;
                }
                else
                {
                    other->unkb8[index]->unk3f = 0;
                }
            }
        }
        unka8->func_00263C70(other);
        unkac->unkad = 0;
        unkb0->unkad = 0;
        for (s32 index = 0; index < 9; index++)
        {
            unkb8[index]->unk3f = 0;
        }
        item_creation_select_inventor_for_swap(unka8, this, -1);
    }
    else
    {
        item_creation_select_inventor_for_swap(state, this, -1);
        if (unkb4 == unkb0)
        {
            FieldObject23CEA0* primary = unkac;
            primary->FieldClass151C50::unk30 = 128.0f;
            primary->unkae = 1;
            func_0023CEA0(unkb0, 0);
            FieldObject23CEA0* alternate = unkb0;
            alternate->index = unkac->unk114;
            func_0023CB30(alternate);
            func_0023C7B0(unkb0);
            unkb4 = unkac;
            func_00361220(this);
        }
        else
        {
            ItemCreationSelectedDisplayState* state = unka8;
            state->unk47 = 0;
            func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
            state = unka8;
            state->unk120 = 0;
            state->unk11c = 0;
            state->unk126 = -1;
            state->unk124 = -1;
            state->unk128 = 0;
        }
    }
    return 2;
}

/** @brief Read the creation-skill bits for an assigned inventor. @param inventor_id One-based runtime inventor record ID. @return Skill bits. */
static inline u32 assigned_inventor_skill_mask(s32 inventor_id)
{
    return inventor_skill_mask(runtime_option_record(D_001B64F8, static_cast<u8>(inventor_id))->inventor_id);
}

/** @brief Intersect the selected line's inventor skill bits. @param object Assigned-inventor grid. @return Shared skill bits, or zero for an empty line. */
static inline u16 assigned_selection_skill_mask(AssignedInventorGrid* object)
{
    u16 first_mask = 0x1FF;
    u16 second_mask = 0x1FF;
    u16 third_mask = 0x1FF;
    u32 first = 0;
    u32 second = 0;
    u32 third = 0;
    switch (object->unk1f0)
    {
    case 0:
        first = object->unk1f2[0];
        second = object->unk1f2[1];
        third = object->unk1f2[2];
        break;
    case 1:
        first = object->unk1f2[3];
        second = object->unk1f2[4];
        third = object->unk1f2[5];
        break;
    case 2:
        first = object->unk1f2[6];
        second = object->unk1f2[7];
        third = object->unk1f2[8];
        break;
    }
    u16 count = 0;
    if (first != 0)
    {
        first_mask = assigned_inventor_skill_mask(first);
        count++;
    }
    if (second != 0)
    {
        second_mask = assigned_inventor_skill_mask(second);
        count++;
    }
    if (third != 0)
    {
        third_mask = assigned_inventor_skill_mask(third);
        count++;
    }
    if (count)
    {
        return first_mask & second_mask & third_mask;
    }
    return 0;
}

/** @brief Open the selected line's skill or policy window, or start swapping an inventor. @return Zero when inactive, one when handled, or three when unavailable. */
s32 AssignedInventorGrid::func_slotb0()
{
    ItemCreationSelectedDisplayState* state = this->unka8;
    if (state == 0)
    {
        return 0;
    }
    FieldObject23CEA0* marker = this->unkb4;
    if (marker == 0)
    {
        return 0;
    }
    bool inactive = !marker->FieldClass151C50::unk35;
    if (inactive)
    {
        return 0;
    }
    if (state->unk47 != 1)
    {
        return 0;
    }
    FieldGridPosition* position;
    s16 selected = marker->unk114;
    position = &marker->FieldClass151C50::unk10;
    if (selected == 3 || selected == 8 || selected == 13)
    {
        if (this->unk1e8 != 0)
        {
            this->unk1f0 = (u8)((selected + 1) % 4);
            u16 mask = assigned_selection_skill_mask(this);
            CreationSkillWindow* choices = this->unk1e8;
            choices->selectable_skill_mask = mask;
            item_creation_update_skill_labels(choices, 0);
            FieldObject23CEA0* marker = this->unkb4;
            marker->FieldClass151C50::unk30 = 64.0f;
            marker->unkae = 1;
            this->unk1e8->func_slot20(1);
            static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14)->unk1e0 = this->unk1f0;
            D_001B643C->unk10->unk14->func_00263C70(this->unk1e8);
        }
        return 1;
    }
    if (selected == 4 || selected == 9 || selected == 14)
    {
        if (this->unk1ec != 0)
        {
            this->unk1f0 = (u8)((selected + 1) / 5 - 1);
            u8 first = 0;
            u8 second = 0;
            u8 third = 0;
            switch (this->unk1f0)
            {
            case 0:
                first = this->unk1f2[0];
                second = this->unk1f2[1];
                third = this->unk1f2[2];
                break;
            case 1:
                first = this->unk1f2[3];
                second = this->unk1f2[4];
                third = this->unk1f2[5];
                break;
            case 2:
                first = this->unk1f2[6];
                second = this->unk1f2[7];
                third = this->unk1f2[8];
                break;
            }
            if (first == 0 && second == 0 && third == 0)
            {
                return 3;
            }
            if (this->unk208[this->unk1f0] == 0x15FD6)
            {
                return 3;
            }
            FieldObject23CEA0* marker = this->unkb4;
            marker->FieldClass151C50::unk30 = 64.0f;
            marker->unkae = 1;
            s32 index = this->unk1f0;
            InventionPolicyWindow* choice = this->unk1ec;
            if (index >= 0 && index < 4)
            {
                choice->unkac = index;
                LibObject178660* container = choice->func_slot58();
                if (container != 0)
                {
                    LibClass174610& transform = static_cast<LibClass174610&>(*container);
                    func_44B190(&transform, choice->unkbc, choice->unkc0[choice->unkac]);
                }
            }
            this->unk1ec->func_slot20(1);
            static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14)->unk1e0 = this->unk1f0;
            D_001B643C->unk10->unk14->func_00263C70(this->unk1ec);
        }
        return 1;
    }
    s32 index = 0;
    switch (selected)
    {
    case 0:
    case 1:
    case 2:
        index = selected;
        break;
    case 5:
    case 6:
    case 7:
        index = selected - 2;
        break;
    case 10:
    case 11:
    case 12:
        index = selected - 4;
        break;
    }
    item_creation_select_inventor_for_swap(state, this, (s16)index);
    if (this->unka8->unk128 == 1)
    {
        FieldObject23CEA0* primary = this->unkac;
        primary->FieldClass151C50::unk30 = 96.0f;
        primary->unkae = 1;
        float x = position->x;
        float y = position->y;
        FieldObject23CEA0* alternate = this->unkb0;
        alternate->FieldClass151C50::unk10.x = x;
        alternate->FieldClass151C50::unk10.y = y;
        alternate->FieldClass151C50::unk35 = 1;
        alternate->unkae = 1;
        func_0023CEA0(this->unkb0, 1);
        alternate = this->unkb0;
        alternate->index = selected;
        func_0023CB30(alternate);
        func_0023C7B0(this->unkb0);
        this->unkb4 = this->unkb0;
    }
    return 1;
}

/**
 * @brief Test whether a development line contains any assigned inventor.
 * @param object Assigned-inventor grid containing three lines of inventor IDs.
 * @param line_index Development-line index from zero through two.
 * @return One when the line contains an inventor, or zero for an empty or invalid line.
 */
u8 func_003623C0(AssignedInventorGrid* object, u8 line_index)
{
    u8 present;
    u8 first_inventor_id = 0;
    u8 second_inventor_id = 0;
    u8 third_inventor_id = 0;
    switch (line_index)
    {
    case 0:
        first_inventor_id = object->unk1f2[0];
        second_inventor_id = object->unk1f2[1];
        third_inventor_id = object->unk1f2[2];
        break;
    case 1:
        first_inventor_id = object->unk1f2[3];
        second_inventor_id = object->unk1f2[4];
        third_inventor_id = object->unk1f2[5];
        break;
    case 2:
        first_inventor_id = object->unk1f2[6];
        second_inventor_id = object->unk1f2[7];
        third_inventor_id = object->unk1f2[8];
        break;
    }
    if (first_inventor_id == 0 && second_inventor_id == 0 && third_inventor_id == 0)
    {
        present = 0;
    }
    else
    {
        present = 1;
    }
    return present;
}

/** @brief Move the active nine-slot marker right and refresh its selected detail. */
void AssignedInventorGrid::func_slotac()
{
    if (unkb4 == unkb0 || unka8->unk128 == 1)
    {
        s16 index = unkb4->unk114;
        if (index == 2)
        {
            if (unkb4 != 0)
            {
                func_0023C550(unkb4, 0);
            }
            func_00361220(this);
            func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
            return;
        }
        else if (index == 7)
        {
            if (unkb4 != 0)
            {
                func_0023C550(unkb4, 5);
            }
            func_00361220(this);
            func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
            return;
        }
        else if (index == 12)
        {
            if (unkb4 != 0)
            {
                func_0023C550(unkb4, 10);
            }
            func_00361220(this);
            func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
            return;
        }
    }
    if (unkb4 != 0 && unkb4->func_0023CDB0(2) != 1)
    {
        func_00361220(this);
        func_00360FD0(this);
    }
}

/** @brief Move the active nine-slot marker left and refresh its selected detail. */
void AssignedInventorGrid::func_slota8()
{
    if (unkb4 == unkb0 || unka8->unk128 == 1)
    {
        s16 index = unkb4->unk114;
        if (index == 0)
        {
            if (unkb4 != 0)
            {
                func_0023C550(unkb4, 2);
            }
            func_00361220(this);
            func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
            return;
        }
        else if (index == 5)
        {
            if (unkb4 != 0)
            {
                func_0023C550(unkb4, 7);
            }
            func_00361220(this);
            func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
            return;
        }
        else if (index == 10)
        {
            if (unkb4 != 0)
            {
                func_0023C550(unkb4, 12);
            }
            func_00361220(this);
            func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
            return;
        }
    }
    if (unkb4 != 0 && unkb4->func_0023CDB0(3) != 1)
    {
        func_00361220(this);
        func_00360FD0(this);
    }
}

/** @brief Move to the related window from the last row or move the grid marker down. */
void AssignedInventorGrid::func_slota4()
{
    bool inactive = !unkb4->FieldClass151C50::unk35;
    if (inactive)
    {
        return;
    }
    u8 base = (u8)((unk1f1 - 1) * 5);
    s16 index = unkb4->unk114;
    if (base == index || base + 1 == index || base + 2 == index || base + 3 == index || base + 4 == index)
    {
        AvailableInventorGrid* other = static_cast<AvailableInventorGrid*>(func_slot44());
        if (base == index)
        {
            if (other->unkb4 != 0)
            {
                func_0023C550(other->unkb4, 0);
            }
        }
        else if (base + 1 == index)
        {
            if (other->unkb4 != 0)
            {
                func_0023C550(other->unkb4, 1);
            }
        }
        else if (base + 2 == index)
        {
            if (other->unkb4 != 0)
            {
                func_0023C550(other->unkb4, 2);
            }
        }
        else if (base + 3 == index)
        {
            if (other->unkb4 != 0)
            {
                func_0023C550(other->unkb4, 3);
            }
        }
        else if (base + 4 == index)
        {
            if (other->unkb4 != 0)
            {
                func_0023C550(other->unkb4, 4);
            }
        }
        func_00364090(other, 1);
        if (other->unka8 != 0 && other->unkb4 != 0)
        {
            item_creation_show_inventor_information(other->unka8, other, other->unkb4->unk114);
        }
        func_00360E60(this, 0);
        D_001B643C->unk10->unk14->func_00263C70(other);
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    }
    else if (unkb4 != 0 && unkb4->func_0023CDB0(1) != 1)
    {
        func_00361220(this);
        func_00360FD0(this);
    }
}

/** @brief Move to the related window from the first row or move the grid marker up. */
void AssignedInventorGrid::func_slota0()
{
    bool inactive = !unkb4->FieldClass151C50::unk35;
    if (inactive)
    {
        return;
    }
    s16 index = unkb4->unk114;
    if (index >= 0 && index < 5)
    {
        AvailableInventorGrid* other = static_cast<AvailableInventorGrid*>(func_slot44());
        if (other->unkb4 != 0)
        {
            func_0023C550(other->unkb4, (u8)(index + 7));
        }
        func_00364090(other, 1);
        if (other->unka8 != 0 && other->unkb4 != 0)
        {
            item_creation_show_inventor_information(other->unka8, other, other->unkb4->unk114);
        }
        func_00360E60(this, 0);
        D_001B643C->unk10->unk14->func_00263C70(other);
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    }
    else if (unkb4 != 0 && unkb4->func_0023CDB0(0) != 1)
    {
        func_00361220(this);
        func_00360FD0(this);
    }
}

void AssignedInventorGrid::func_slot74()
{
    func_slotac();
}

void AssignedInventorGrid::func_slot70()
{
    func_slota8();
}

void AssignedInventorGrid::func_slot6c()
{
    func_slota4();
}

void AssignedInventorGrid::func_slot68()
{
    func_slota0();
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00362BA0);

void func_00363D20(AssignedInventorGrid* object)
{
    s32 index;
    object->unk1f1 = object->unka8->unk57;
    for (index = 0; index < 3; index++)
    {
        if (index < object->unk1f1)
        {
            LibObject178750* display1;
            LibObject178750* display2;
            LibObject178750* display3;
            LibObject178750* display4;
            object->unk194[index]->unk3f = 1;
            object->unk1a0[index]->unk3f = 1;
            object->unk1ac[index]->unk3f = 1;
            display1 = object->unk1b8[index];
            display1->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display1->unk3c = 1;
            display2 = object->unk1c4[index];
            display2->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display2->unk3c = 1;
            display3 = object->unk1d0[index];
            display3->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display3->unk3c = 1;
            display4 = object->unk1dc[index];
            display4->unk94 = ITEM_CREATION_COLOR_ASSIGNED;
            display4->unk3c = 1;
        }
        else
        {
            LibObject178750* display1;
            LibObject178750* display2;
            LibObject178750* display3;
            LibObject178750* display4;
            object->unk194[index]->unk3f = 0;
            object->unk1a0[index]->unk3f = 0;
            object->unk1ac[index]->unk3f = 0;
            display1 = object->unk1b8[index];
            display1->unk94 = ITEM_CREATION_COLOR_DIM;
            display1->unk3c = 1;
            display2 = object->unk1c4[index];
            display2->unk94 = ITEM_CREATION_COLOR_DIM;
            display2->unk3c = 1;
            display3 = object->unk1d0[index];
            display3->unk94 = ITEM_CREATION_COLOR_DIM;
            display3->unk3c = 1;
            display4 = object->unk1dc[index];
            display4->unk94 = ITEM_CREATION_COLOR_DIM;
            display4->unk3c = 1;
        }
    }
    object->unkac->func_0023CE80(5, object->unk1f1);
    object->unkb0->func_0023CE80(5, object->unk1f1);
}

/** @brief Release the twelve owned resources before destroying the window base. */
AssignedInventorGrid::~AssignedInventorGrid()
{
    for (s32 index = 0; index < 12; index++)
    {
        if (unk160[index])
        {
            release_owned(unk160[index]);
        }
    }
}


/** @brief Initialize the nine-slot selection window and clear its owned arrays. */
AssignedInventorGrid::AssignedInventorGrid()
{
    func_slotec(1);
    unka8 = 0;
    unkac = 0;
    unkb0 = 0;
    unkb4 = 0;
    for (s32 index = 0; index < 9; index++)
    {
        unk13c[index] = 0;
        unkb8[index] = 0;
        unk1f2[index] = 0;
    }
    for (s32 index = 0; index < 12; index++)
    {
        unkdc[index] = 0;
        unk10c[index] = 0;
    }
    for (s32 index = 0; index < 12; index++)
    {
        unk160[index] = 0;
    }
    for (s32 index = 0; index < 3; index++)
    {
        unk160[index] = 0;
        unk194[index] = 0;
        unk1a0[index] = 0;
        unk1ac[index] = 0;
        unk1b8[index] = 0;
        unk1c4[index] = 0;
        unk1d0[index] = 0;
        unk1dc[index] = 0;
        unk1fc[index] = 0;
        unk208[index] = 0;
    }
    unk190 = 0;
    unk1e8 = 0;
    unk1ec = 0;
    unk1f1 = 0;
    unk214 = 0;
    for (s32 index = 0; index < 3; index++)
    {
        unk218[index] = 0;
        unk21b[index] = 0;
    }
}


void func_00364090(AvailableInventorGrid* object, u16 mode)
{
    s32 index;
    s32 selected;

    switch (mode)
    {
    case 1:
        if (object->unkb4 != 0)
        {
            func_0023CEA0(object->unkb4, 1);
        }
        if (object->unkb4 != 0)
        {
            selected = object->unkb4->unk114;
            for (index = 0; index < 14; index++)
            {
                if (selected == index)
                {
                    object->unkb8[index]->unk3f = 1;
                }
                else
                {
                    object->unkb8[index]->unk3f = 0;
                }
            }
        }
        break;
    case 0:
        if (object->unka8->unk128 != 1)
        {
            if (object->unkac != 0)
            {
                func_0023CEA0(object->unkac, 0);
            }
            if (object->unkb0 != 0)
            {
                func_0023CEA0(object->unkb0, 0);
            }
        }
        else
        {
            if (object->unkb4 != 0)
            {
                func_0023CEA0(object->unkb4, 0);
            }
        }
        for (index = 0; index < 14; index++)
        {
            object->unkb8[index]->unk3f = 0;
        }
        break;
    }
}

void func_003641F0(void* object)
{
}

/**
 * @brief Highlight the attached marker's current fourteen-slot row.
 * @param object Fourteen-slot selection window.
 */
static inline void highlight_current_row(AvailableInventorGrid* object)
{
    if (object->unkb4 != 0)
    {
        s16 selected = object->unkb4->unk114;
        for (s32 index = 0; index < 14; index++)
        {
            if (selected == index)
            {
                object->unkb8[index]->unk3f = 1;
            }
            else
            {
                object->unkb8[index]->unk3f = 0;
            }
        }
    }
}

/** @brief Restore the fourteen-slot selection window or leave item selection. @return Two when handled, zero when inactive. */
s32 AvailableInventorGrid::func_slotb4()
{
    ItemCreationSelectedDisplayState* state = unka8;
    if (state == 0)
    {
        return 0;
    }
    bool inactive = !unkb4->FieldClass151C50::unk35;
    if (inactive)
    {
        return 0;
    }
    if (state->unk47 != 1)
    {
        return 0;
    }
    if (state->unk128 == 1 && state->unk11c != this)
    {
        AssignedInventorGrid* other = state->unkbc;
        FieldObject23CEA0* primary = unkac;
        primary->FieldClass151C50::unk30 = 128.0f;
        primary->unkae = 1;
        func_0023CEA0(unkb0, 0);
        FieldObject23CEA0* alternate = unkb0;
        alternate->index = unkac->unk114;
        func_0023CB30(alternate);
        func_0023C7B0(unkb0);
        unkb4 = unkac;
        highlight_current_row(this);
        primary = other->unkac;
        primary->FieldClass151C50::unk30 = 128.0f;
        primary->unkae = 1;
        func_0023CEA0(other->unkb0, 0);
        alternate = other->unkb0;
        alternate->index = other->unkac->unk114;
        func_0023CB30(alternate);
        func_0023C7B0(other->unkb0);
        other->unkb4 = other->unkac;
        func_00361220(other);
        unka8->func_00263C70(other);
        unkac->unkad = 0;
        unkb0->unkad = 0;
        for (s32 index = 0; index < 14; index++)
        {
            unkb8[index]->unk3f = 0;
        }
        item_creation_select_inventor_for_swap(unka8, this, -1);
    }
    else
    {
        item_creation_select_inventor_for_swap(state, this, -1);
        if (unkb4 == unkb0)
        {
            FieldObject23CEA0* primary = unkac;
            primary->FieldClass151C50::unk30 = 128.0f;
            primary->unkae = 1;
            func_0023CEA0(unkb0, 0);
            FieldObject23CEA0* alternate = unkb0;
            alternate->index = unkac->unk114;
            func_0023CB30(alternate);
            func_0023C7B0(unkb0);
            unkb4 = unkac;
            highlight_current_row(this);
        }
        else
        {
            ItemCreationSelectedDisplayState* state = unka8;
            state->unk47 = 0;
            func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
            state = unka8;
            state->unk120 = 0;
            state->unk11c = 0;
            state->unk126 = -1;
            state->unk124 = -1;
            state->unk128 = 0;
        }
    }
    return 2;
}


u8 func_003644F0(AvailableInventorGrid* object)
{
    ItemCreationSelectedDisplayState* state = object->unka8;
    FieldObject23CEA0* display;
    u16 index;
    bool inactive;
    const FieldGridPosition* position;
    if (state == 0)
    {
        return 0;
    }
    display = object->unkb4;
    if (display == 0)
    {
        return 0;
    }
    inactive = !display->unk35;
    if (inactive)
    {
        return 0;
    }
    if (state->unk47 != 1)
    {
        return 0;
    }
    index = display->unk114;
    position = &display->unk10;
    item_creation_select_inventor_for_swap(state, object, (s16)index);
    if (object->unka8->unk128 == 1)
    {
        FieldObject23CEA0* restore = object->unkac;
        FieldObject23CEA0* target;
        float x;
        float y;
        restore->FieldClass151C50::unk30 = 96.0f;
        restore->unkae = 1;
        x = position->x;
        y = position->y;
        target = object->unkb0;
        target->unk10.x = x;
        target->unk10.y = y;
        target->unk35 = 1;
        target->unkae = 1;
        func_0023CEA0(object->unkb0, 1);
        target = object->unkb0;
        target->index = (s16)index;
        func_0023CB30(target);
        func_0023C7B0(object->unkb0);
        object->unkb4 = object->unkb0;
    }
    return 1;
}


/**
 * @brief Apply the selected marker index when its state and marker are present.
 * @param state Current selection state.
 * @param object Selection window containing the marker.
 */
static inline void apply_selected_index(ItemCreationSelectedDisplayState* state, AvailableInventorGrid* object)
{
    if (state)
    {
        FieldObject23CEA0* marker = object->unkb4;
        if (marker)
        {
            item_creation_show_inventor_information(state, object, marker->unk114);
        }
    }
}

/** @brief Toggle information for the selected available inventor. @return One when state is attached, zero otherwise. */
s32 AvailableInventorGrid::func_slotb8()
{
    u8 flag;
    if (unkac == 0)
    {
        return 0;
    }
    ItemCreationSelectedDisplayState* state = unka8;
    if (state == 0)
    {
        return 0;
    }
    apply_selected_index(state, this);
    InventorInformationWindow* display = unka8->unkc0;
    if (display)
    {
        flag = !display->unk100;
        display->func_slot20(flag);
        display->unk100 = flag;
    }
    return 1;
}


/**
 * @brief Update row visibility while a selection marker is attached.
 * @param object Fourteen-slot selection window.
 * @param index Selected row index.
 */
static inline void highlight_selected_row(AvailableInventorGrid* object, s16 index)
{
    if (object->unkb4 != 0)
    {
        for (s32 slot = 0; slot < 14; slot++)
        {
            if (index == slot)
            {
                object->unkb8[slot]->unk3f = 1;
            }
            else
            {
                object->unkb8[slot]->unk3f = 0;
            }
        }
    }
}

/** @brief Move the fourteen-slot marker right and refresh its selected detail. */
void AvailableInventorGrid::func_slotac()
{
    if (unkb4 != 0 && unkb4->func_0023CDB0(2) != 1)
    {
        highlight_selected_row(this, unkb4->unk114);
        if (unka8 != 0 && unkb4 != 0)
        {
            item_creation_show_inventor_information(unka8, this, unkb4->unk114);
        }
    }
}


/** @brief Move the fourteen-slot marker left and refresh its selected detail. */
void AvailableInventorGrid::func_slota8()
{
    if (unkb4 != 0 && unkb4->func_0023CDB0(3) != 1)
    {
        highlight_selected_row(this, unkb4->unk114);
        if (unka8 != 0 && unkb4 != 0)
        {
            item_creation_show_inventor_information(unka8, this, unkb4->unk114);
        }
    }
}


/**
 * @brief Return the current signed marker row.
 * @param marker Selection marker.
 * @return Selected row index.
 */
static inline s16 selected_row(FieldObject23CEA0* marker)
{
    return marker->unk114;
}

/**
 * @brief Map a lower fourteen-slot row to its related grid row.
 * @param index Fourteen-slot row index.
 * @return Related grid row index.
 */
static inline u8 related_row(s16 index)
{
    s16 row = index - 7;
    if (index >= 11)
    {
        row = 4;
    }
    return row;
}

/** @brief Transfer a supported row to the related window or move the marker down. */
void AvailableInventorGrid::func_slota4()
{
    FieldObject23CEA0* marker = unkb4;
    ItemCreationSelectedDisplayState* state = unka8;
    s16 index = selected_row(marker);
    if (state->unk57 && index >= 7 && index < 14)
    {
        u16 selected = related_row(index);
        if (state->unk128 == 1 && index >= 10)
        {
            selected = 2;
        }
        AssignedInventorGrid* other = static_cast<AssignedInventorGrid*>(func_slot44());
        if (other->unkb4 != 0)
        {
            func_0023C550(other->unkb4, selected);
        }
        func_00360FD0(other);
        func_00360E60(other, 1);
        func_00364090(this, 0);
        D_001B643C->unk10->unk14->func_00263C70(other);
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
        return;
    }
    if (marker != 0 && marker->func_0023CDB0(1) != 1)
    {
        highlight_selected_row(this, unkb4->unk114);
        if (unka8 != 0 && unkb4 != 0)
        {
            item_creation_show_inventor_information(unka8, this, unkb4->unk114);
        }
    }
}


/**
 * @brief Clamp the source column to the related grid's last column.
 * @param index Source column index.
 * @return Related column index.
 */
static inline s16 related_column(s16 index)
{
    if (index >= 4)
    {
        index = 4;
    }
    return index;
}

/**
 * @brief Map an upper fourteen-slot row to the related grid's final row.
 * @param row_count Number of related grid rows.
 * @param index Fourteen-slot row index.
 * @return Related grid row index.
 */
static inline u8 upper_related_row(u8 row_count, s16 index)
{
    s16 column = related_column(index);
    return column + (row_count - 1) * 5;
}

/**
 * @brief Keep a related grid row on its center column.
 * @param index Related grid row index.
 * @return Index at the grid row's center column.
 */
static inline u8 centered_related_row(u8 index)
{
    return (index / 5) * 5 + 2;
}

/** @brief Transfer a supported row to the related window or move the marker up. */
void AvailableInventorGrid::func_slota0()
{
    FieldObject23CEA0* marker = unkb4;
    s16 index = selected_row(marker);
    u8 row_count = unka8->unk57;
    if (row_count && index >= 0 && index < 7)
    {
        u16 selected = upper_related_row(row_count, index);
        if (unka8->unk128 == 1 && index >= 3 && index < 7)
        {
            selected = centered_related_row(selected);
        }
        AssignedInventorGrid* other = static_cast<AssignedInventorGrid*>(func_slot44());
        if (other->unkb4 != 0)
        {
            func_0023C550(other->unkb4, selected);
        }
        func_00360FD0(other);
        func_00360E60(other, 1);
        func_00364090(this, 0);
        D_001B643C->unk10->unk14->func_00263C70(other);
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
        return;
    }
    if (marker != 0 && marker->func_0023CDB0(0) != 1)
    {
        highlight_selected_row(this, unkb4->unk114);
        if (unka8 != 0 && unkb4 != 0)
        {
            item_creation_show_inventor_information(unka8, this, unkb4->unk114);
        }
    }
}


void AvailableInventorGrid::func_slot74()
{
    func_slotac();
}

void AvailableInventorGrid::func_slot70()
{
    func_slota8();
}

void AvailableInventorGrid::func_slot6c()
{
    func_slota4();
}

void AvailableInventorGrid::func_slot68()
{
    func_slota0();
}

/**
 * @brief Refresh the fourteen available-inventor portraits.
 * @param object Available-inventor grid.
 */
void func_00364D20(AvailableInventorGrid* object)
{
    void* allocation;
    s32 slot_index;
    u32 inventor_option_code;
    u32 portrait_index;
    FieldResourceRecord* record;

    for (slot_index = 0; slot_index < 14; slot_index++)
    {
        inventor_option_code = object->unka8->unk5a[(u16)slot_index];
        if (inventor_option_code != 0)
        {
            portrait_index = (u8)item_resource_index_middle(inventor_option_code);
            allocation = func_002D3D80(D_001B643C->unk20, portrait_index);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            object->unkf0[slot_index]->func_002D5CF0(allocation, record, portrait_index);
            object->unkf0[slot_index]->unk3f = 1;
        }
        else
        {
            object->unkf0[slot_index]->unk3f = 0;
        }
    }
}

/**
 * @brief Update the fourteen-slot selection markers and display activation.
 * @param object Selection window.
 * @param enabled Full-word activation flag.
 */
extern "C" void func_00364E00(AvailableInventorGrid* object, u32 enabled)
{
    update_selection_markers(object, enabled);
}

/**
 * @brief Create the fourteen available-inventor portraits and their two selection grids.
 * @param associated Associated display passed to the Field setup.
 * @return Zero without a selected state, one after setup.
 */
s32 AvailableInventorGrid::func_slotf4(void* associated)
{
    if (this->unka8 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot14(associated, 0, 9, 2000, 16.0f, 72.0f, 0.0f);
    LibWidgetColors4C5590 colors = {0};
    colors.values[0] = 0xBCA4B4;
    colors.values[1] = 0xBCA4B4;
    colors.values[2] = 0x574C52;
    colors.values[3] = 0x574C52;
    this->unk128 = new (0) FieldClass15B200(this->unk10, 1);
    func_002D5290(this->unk128, 0xBC, 0x18, &colors, 0.0f, 0.0f, 444.0f, 154.0f);
    LibClass178600* child = static_cast<LibClass178600*>(this->unk128->unk30);
    if (child)
    {
        child->unk28 = 40.0f;
        child->unk3c = 1;
    }
    float x = 6.0f;
    float y = 6.0f;
    void* allocation = func_002D3D80(D_001B643C->unk20, 0);
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 0x2D);
    for (s32 index = 0; index < 14; index++)
    {
        ItemCreationOptionResourceDisplay* widget = new (0) ItemCreationOptionResourceDisplay;
        widget->unkcc = allocation;
        widget->unkd0 = 0;
        widget->func_002D6440(record,
                     6.0f + 61.7142868f * (index % 7), 6.0f + 72.0f * (index / 7));
        widget->unk50.unk30 = 1.71428573f;
        widget->unk50.unk34 = 2.0f;
        widget->unk3c = 1;
        widget->unk3f = 0;
        func_004C6190(this->unk10, widget);
        this->unkb8[index] = widget;
    }
    u8 resource;
    x += 4.0f;
    y += 4.0f;
    for (s32 index = 0; index < 14; index++)
    {
        u8 value = this->unka8->unk5a[(u16)index];
        if (value == 0)
        {
            allocation = func_002D3D80(D_001B643C->unk20, 0);
            record = func_002D3CC0(D_001B643C->unk20, 0x20);
            resource = 0;
        }
        else
        {
            resource = item_resource_index(value);
            allocation = func_002D3D80(D_001B643C->unk20, resource);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
        }
        ItemCreationOptionResourceDisplay* widget = new (0) ItemCreationOptionResourceDisplay;
        widget->unkcc = allocation;
        widget->unkd0 = resource;
        widget->func_002D6440(record,
                     x + 61.7142868f * (index % 7), y + 72.0f * (index / 7));
        widget->unk50.unk30 = 0.856999993f;
        widget->unk50.unk34 = 1.0f;
        widget->unk3c = 1;
        func_004C6190(this->unk10, widget);
        this->unkf0[index] = widget;
    }
    this->unkac = new (0) FieldObject23CEA0;
    this->unkac->func_0023CE80(7, 2);
    this->unkac->func_0023CE60(61.7142868f, 72.0f);
    this->unkac->unkF2 = 1;
    this->unkac->unk119 = 1;
    float bottom = 36.0f + (72.0f + y);
    float left = 8.0f + (16.0f + x);
    this->unkac->func_0023CF50(0, left, bottom - 24.0f);
    func_0036F040(&this->unk74, this->unkac);
    func_0023CEA0(this->unkac, 0);
    this->unkb0 = new (0) FieldObject23CEA0;
    this->unkb0->func_0023CE80(7, 2);
    this->unkb0->func_0023CE60(61.7142868f, 72.0f);
    this->unkb0->unkF2 = 1;
    this->unkb0->unk119 = 1;
    this->unkb0->func_0023CF50(0, left, bottom - 8.0f);
    func_0036F040(&this->unk74, this->unkb0);
    func_0023CEA0(this->unkb0, 0);
    this->unkb4 = this->unkac;
    func_00364D20(this);
    return 1;
}

/** @brief Release the owned resource before destroying the selection window. */
AvailableInventorGrid::~AvailableInventorGrid()
{
    if (unk128)
    {
        release_owned(unk128);
    }
}


/**
 * @brief Initialize facility and development-line expansion costs for a workshop.
 * @param object Workshop-expansion window.
 * @param workshop_id Workshop ID from one through twelve.
 */
extern "C" void item_creation_initialize_expansion_costs(WorkshopExpansionWindow* object, u8 workshop_id)
{
    switch (workshop_id)
    {
    case 1:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 2:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 3:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 4:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 5:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 6:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 7:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 8:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 9:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 10:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 11:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    case 12:
        object->facility_costs[0] = 800;
        object->facility_costs[1] = 2000;
        object->facility_costs[2] = 8000;
        object->facility_costs[3] = 4000;
        object->facility_costs[4] = 3000;
        object->facility_costs[5] = 5000;
        object->facility_costs[6] = 6000;
        object->facility_costs[7] = 9500;
        object->additional_line_costs[0] = 1000;
        object->additional_line_costs[1] = 2000;
        object->additional_line_costs[2] = 3000;
        break;
    }
}

/**
 * @brief Move the panel grid in direction one and refresh its selected entry.
 */
void WorkshopExpansionWindow::func_slot6c()
{
    if (unkd8 > 1)
    {
        FieldObject23CEA0* grid = unkdc;
        if (grid != 0 && grid->func_0023CDB0(1) != 1)
        {
            func_00365F20(this);
        }
    }
}

/**
 * @brief Move the panel grid in direction zero and refresh its selected entry.
 */
void WorkshopExpansionWindow::func_slot68()
{
    if (unkd8 > 1)
    {
        FieldObject23CEA0* grid = unkdc;
        if (grid != 0 && grid->func_0023CDB0(0) != 1)
        {
            func_00365F20(this);
        }
    }
}

/**
 * @brief Disable and reset the panel selection, then return to its associated parent.
 * @return Always two.
 */
s32 WorkshopExpansionWindow::func_slotb4()
{
    if (unkdc != 0)
    {
        func_0023CEA0(unkdc, 0);
    }
    func_slot20(0);
    if (unkdc != 0)
    {
        func_0023C710(unkdc);
    }
    func_00365F20(this);
    ItemCreationMainMenu* parent = static_cast<ItemCreationMainMenu*>(func_slot44());
    if (parent != 0)
    {
        FieldObject23CEA0* marker = parent->unkac;
        if (marker != 0)
        {
            marker->FieldClass151C50::unk30 = 128.0f;
            marker->unkae = 1;
        }
        D_001B643C->unk10->unk14->func_00263C70(parent);
    }
    return 2;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00365BF0);

/**
 * @brief Refresh the panel grid selection and selected entry.
 * @param object Panel selection window.
 */
extern "C" void func_00365F20(WorkshopExpansionWindow* object)
{
    if (object->unkdc && object->unke0)
    {
        s16 selected = object->unkdc->unk114;
        s32 index = 0;
        ItemCreationListNode* node = object->unk2c.unk00->unk04;
        while (node)
        {
            LibObject178750* widget = static_cast<LibObject178750*>(node->unk00);
            if (index == selected)
            {
                object->unke0->func_0023B9B0(func_4C69B0(widget)->unk08, (s16)index);
                widget->unk94 = 0x288080;
                widget->unk3c = 1;
                FieldClass15AE70* text =
                    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90());
                if (text)
                {
                    text->func_slot60(0x352F);
                }
            }
            else
            {
                widget->unk94 = 0x808080;
                widget->unk3c = 1;
            }
            node = node->unk04;
            ++index;
        }
    }
}

/** @brief Read the alternate associated object. @return Stored object. */
void* ItemCreationSelectedDisplayState::func_00263C90()
{
    return unk24;
}

void func_00366050(WorkshopExpansionWindow* object)
{
    if (object->unka8 != 0)
    {
        if (object->unkd8 != 0)
        {
            for (s32 index = 0; index < object->unkd8; index++)
            {
                LibObject178750* display = object->unke8[index];
                if (display != 0)
                {
                    if (index != object->unk10c)
                    {
                        ItemCreationListNode* node = func_0036F160(&object->unk38, index);
                        LibObject174F20* other = static_cast<LibObject174F20*>(node->unk00);
                        if (other != 0)
                        {
                            if (object->unka8->workshop_skill_enabled[object->unkd0[index] - 1] == 0)
                            {
                                display->unk3f = 0;
                                other->unk3f = 1;
                            }
                            else
                            {
                                display->unk3f = 1;
                                other->unk3f = 0;
                            }
                        }
                    }
                    else
                    {
                        object->unk10d = object->unka8->unk57;
                        if (object->unk10d < 3)
                        {
                            LibObject174F20* valueDisplay = object->unk120;
                            valueDisplay->unkfc = object->additional_line_costs[object->unk10d];
                            valueDisplay->unk3c = 1;
                        }
                        else
                        {
                            display->unk3f = 1;
                            if (object->unk120 != 0)
                            {
                                object->unk120->unk3f = 0;
                            }
                        }
                    }
                }
            }
            if (object->unke4 != 0)
            {
                ItemCreationCheckedRecord* record = D_001B643C->unk00;
                const u8* end = (const u8*)&record->unka4;
                u16 checksum = record->unka4;
                LibObject174F20* display;
                u32 value;
                if (checksum != func_00457470(record->unka6, ((u8*)record + 0x26),
                    end - ((const u8*)record + 0x26)))
                {
                    value = 0;
                }
                else
                {
                    value = record->unk34 ^ 0x7CE3C7F7;
                }
                display = object->unke4;
                display->unkfc = value;
                display->unk3c = 1;
            }
        }
    }
}

/**
 * @brief Position an expansion entry below the heading.
 * @param row Zero-based visible row.
 * @param spacing Distance between row origins.
 * @return Vertical position.
 */
static inline float expansion_row_y(u32 row, float spacing)
{
    return 68.0f + (float)row * spacing;
}

/**
 * @brief Scale a row coordinate by its spacing.
 * @param row Row coordinate.
 * @param spacing Distance between rows.
 * @return Offset from the first row.
 */
static inline float expansion_row_offset(float row, float spacing)
{
    return row * spacing;
}

/**
 * @brief Build the available workshop facilities and additional-line entries.
 * @param associated Source passed to the window and its labels.
 * @return One after setup, or zero without a selected workshop state or workshop id.
 */
s32 WorkshopExpansionWindow::func_slotf4(void* associated)
{
    if (unka8 == 0)
    {
        return 0;
    }
    if (workshop_id == 0)
    {
        return 0;
    }
    unk10d = unka8->unk57;
    item_creation_initialize_expansion_costs(this, workshop_id);
    FieldClass15AE70::func_slot10(associated, 280.0f, 78.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 344.0f, 388.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* left = new (0) LibObject178750;
    LibObject178750* right = new (0) LibObject178750;
    LibObject178750* footer_left = new (0) LibObject178750;
    LibObject178750* footer_right = new (0) LibObject178750;
    left->func_004C7FE0(28.0f, 24.0f, 0.0f, 0.0f, (s32)associated, 0x32F3, 1);
    right->func_004C7FE0(240.0f, 24.0f, 0.0f, 0.0f, (s32)associated, 0x32F4, 1);
    footer_left->func_004C7FE0(62.0f, 350.0f, 0.0f, 0.0f, (s32)associated, 0x32F5, 0);
    footer_right->func_004C7FE0(242.0f, 350.0f, 0.0f, 0.0f, (s32)associated, 0x32F6, 0);
    func_004C6190(unk10, left);
    func_004C6190(unk10, right);
    func_004C6190(unk10, footer_left);
    func_004C6190(unk10, footer_right);
    unke4 = new (0) LibObject174F20;
    ItemCreationCheckedRecord* record = D_001B643C->unk00;
    u16 checksum = record->unka4;
    const u8* end = (const u8*)&record->unka4;
    u32 value;
    if (checksum !=
        (u16)func_00457470(record->unka6, ((u8*)record + 0x26), end - ((const u8*)record + 0x26)))
    {
        value = 0;
    }
    else
    {
        value = record->unk34 ^ 0x7CE3C7F7;
    }
    unke4->func_00464D90(112.0f, 350.0f, 126.0f, 24.0f, value, (s32)associated, 0);
    LibObject174F20* value_display = unke4;
    value_display->unk94 = 0x288080;
    value_display->unk3c = 1;
    func_004C6190(unk10, unke4);
    ItemCreationClass172870* first = new (0) ItemCreationClass172870;
    func_421170(first, 24.0f, 52.0f, 288.0f, 5.0f);
    first->unk50 = 0x606060;
    first->unk3c = 1;
    func_004C6190(unk10, first);
    ItemCreationClass172870* second = new (0) ItemCreationClass172870;
    func_421170(second, 24.0f, 338.0f, 288.0f, 5.0f);
    second->unk50 = 0x606060;
    second->unk3c = 1;
    func_004C6190(unk10, second);
    for (s32 index = 0; index < 9; index++)
    {
        LibObject178750* text = new (0) LibObject178750;
        text->func_004C7FE0(203.0f, 68.0f + expansion_row_offset((float)index, 30.0f), 0.0f, 0.0f,
                            (s32)associated, 0x352E, 0);
        func_004C6190(unk10, text);
        text->unk3f = 0;
        unke8[index] = text;
    }
    for (s32 index = 0; index < 8; index++)
    {
        u8 option = index + 1;
        if (unka8->workshop_skill_enabled[option - 1] != 1)
        {
            unkd0[unkd8] = option;
            u32 cost = facility_costs[index];
            LibObject178750* text = new (0) LibObject178750;
            LibObject174F20* quantity = new (0) LibObject174F20;
            text->func_004C7FE0(62.0f, expansion_row_y((u32)unkd8, 30.0f), 0.0f, 0.0f,
                                (s32)associated, 0x3672 + index, 0);
            quantity->func_00464D90(160.0f, expansion_row_y((u32)unkd8, 30.0f), 126.0f, 24.0f, cost,
                                    (s32)associated, 0);
            func_004C6190(unk10, text);
            func_004C6190(unk10, quantity);
            func_0036F1A0(&unk2c, text);
            func_0036F0D0(&unk38, quantity);
            unkd8++;
        }
    }
    if (unk10d < 3)
    {
        unk10c = unkd8;
        unk11c = new (0) LibObject178750;
        unk120 = new (0) LibObject174F20;
        unk11c->func_004C7FE0(62.0f, expansion_row_y((u32)unkd8, 30.0f), 0.0f, 0.0f,
                              (s32)associated, 0x1B71, 0);
        unk120->func_00464D90(160.0f, expansion_row_y((u32)unkd8, 30.0f), 126.0f, 24.0f,
                              additional_line_costs[unk10d], (s32)associated, 0);
        func_004C6190(unk10, unk11c);
        func_004C6190(unk10, unk120);
        func_0036F1A0(&unk2c, unk11c);
        func_0036F0D0(&unk38, unk120);
        unkd8++;
    }
    unkdc = new (0) FieldObject23CEA0;
    u16 count = unkd8;
    unkdc->func_0023CE80(1, count ? count : 1);
    unkdc->func_0023CE60(0.0f, 30.0f);
    unkdc->unkF2 = 0;
    unkdc->func_0023CF50(0, 334.0f, 146.0f);
    func_0036F040(&unk74, unkdc);
    if (unkd8 != 0)
    {
        FieldObject23BE00* marker = new (0) FieldObject23BE00;
        unke0 = marker;
        unke0->func_0023BB20(62.0f, 67.0f, 48.0f, 1.0f, unkdc, 0x288080);
        func_004C6190(unk10, unke0);
        func_0036EFB0(&unk8c, unke0);
    }
    func_00365F20(this);
    FieldObject23CEA0* grid = unkdc;
    if (grid)
    {
        func_0023CEA0(grid, 0);
    }
    func_slot20(0);
    func_00366050(this);
    return 1;
}


void WorkshopExpansionWindow::func_slot5c()
{
    if (this->unke4 != 0)
    {
        ItemCreationCheckedRecord* record = reinterpret_cast<ItemCreationCheckedRecord*>(D_001B6430->unk04);
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        LibObject174F20* display;
        u32 value;

        if (checksum != func_00457470(record->unka6, ((u8*)record + 0x26),
            end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        display = this->unke4;
        display->unkfc = value;
        display->unk3c = 1;
    }
}

WorkshopExpansionWindow::WorkshopExpansionWindow()
{
    unka8 = 0;
    workshop_id = 0;
    for (s32 i = 0; i < 8; i++)
    {
        facility_costs[i] = 0;
        unkd0[i] = 0;
    }
    for (s32 i = 0; i < 9; i++)
    {
        unke8[i] = 0;
    }
    unk11c = 0;
    unk120 = 0;
    unk10c = 0xFF;
    unk10d = 0;
    unkd8 = 0;
    unke4 = 0;
    unkdc = 0;
    unke0 = 0;
}

/** @brief Refresh the three option labels and their visibility. */
void DevelopmentTeamsWindow::func_slot5c()
{
    ItemCreationSelectedDisplayState* state =
        static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    for (s32 index = 0; index < 3; ++index)
    {
        if (index < state->unk57)
        {
            u16 code = state->unk1c0[(u16)index];
            if (code)
            {
                func_4C6DF0(unk140[index], func_slot54(), code + 0x3457, 0);
            }
            else
            {
                func_4C6DF0(unk140[index], func_slot54(), 0x15FDD, 0);
            }
            unk140[index]->unk3f = 1;
        }
        else
        {
            unk140[index]->unk3f = 0;
        }
    }
}

void func_00366F10(DevelopmentTeamsWindow* object)
{
    u16 resource;
    if (object->unk120 != 0)
    {
        if (object->unk120->unk48 != 0)
        {
            for (s32 index = 0; index < 9; index++)
            {
                ItemCreationOptionResourceDisplay* display = object->unka8[index];
                if (display != 0)
                {
                    display->unk3f = 0;
                }
            }
            for (s32 index = 0; index < 14; index++)
            {
                ItemCreationOptionResourceDisplay* display = object->unkcc[index];
                if (display != 0)
                {
                    display->unk3f = 0;
                }
            }
            object->unk124 = object->unk120->workshop_id + 1;
            if (object->unk124 != 0)
            {
                s32 slot = 0;
                for (s32 index = 0; index < 14; index++)
                {
                    u8 value = object->unk120->unk5a[(u16)index];
                    if (value != 0)
                    {
                        resource = item_available_resource_index(value);
                        void* allocation = func_002D3D80(D_001B643C->unk20, (u8)resource);
                        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 0x51);
                        object->unkcc[slot]->unkd0 = resource;
                        func_002D5CF0((FieldResourceDisplay2D5CF0*)object->unkcc[slot], allocation, record, 0);
                        object->unkcc[slot]->unk3f = 1;
                        slot++;
                    }
                }
                for (s32 index = 0; index < 9; index++)
                {
                    u8 value = object->unk120->unk68[(u16)index];
                    if (value != 0)
                    {
                        resource = item_available_resource_index(value);
                        void* allocation = func_002D3D80(D_001B643C->unk20, (u8)resource);
                        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 0x51);
                        object->unka8[index]->unkd0 = resource;
                        func_002D5CF0((FieldResourceDisplay2D5CF0*)object->unka8[index], allocation, record, 0);
                        object->unka8[index]->unk3f = 1;
                    }
                }
            }
        }
    }
}

/**
 * @brief Set a resource panel child's scalar drawing value.
 * @param resource Resource panel; nothing happens without a child.
 * @param value Scalar drawing value.
 */
static inline void set_resource_scalar(FieldClass15B200* resource, float value)
{
    LibClass178600* child = static_cast<LibClass178600*>(resource->unk30);
    if (child)
    {
        child->unk28 = value;
        child->unk3c = 1;
    }
}

/**
 * @brief Construct the assigned and available option displays.
 * @param associated Object associated with the window.
 * @return One when the selection state is present, otherwise zero.
 */
s32 DevelopmentTeamsWindow::func_slotf4(void* associated)
{
    if (unk120 == 0)
    {
        return 0;
    }
    unk125 = unk120->unk57;
    FieldClass15AE70::func_slot10(associated, 288.0f, 78.0f, 17);
    LibWidgetColors4C5590 colors = {0};
    colors.values[0] = 0xBCA4B4;
    colors.values[1] = 0xBCA4B4;
    colors.values[2] = 0x574C52;
    colors.values[3] = 0x574C52;
    float rows[3] = {0};
    rows[0] = 0.0f;
    rows[1] = 75.0f;
    rows[2] = 150.0f;
    unk104[0] = new (0) FieldClass15B200(unk10, 1);
    func_002D5290(unk104[0], 0xBC, 0x18, &colors, 0.0f, rows[0], 230.0f, 72.0f);
    set_resource_scalar(unk104[0], 40.0f);
    unk104[1] = new (0) FieldClass15B200(unk10, 1);
    func_002D5290(unk104[1], 0xBC, 0x18, &colors, 0.0f, rows[1], 230.0f, 72.0f);
    set_resource_scalar(unk104[1], 40.0f);
    unk104[2] = new (0) FieldClass15B200(unk10, 1);
    func_002D5290(unk104[2], 0xBC, 0x18, &colors, 0.0f, rows[2], 230.0f, 72.0f);
    set_resource_scalar(unk104[2], 40.0f);
    void* allocation = func_002D3D80(D_001B643C->unk20, 0);
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 16);
    float inset = 10.0f;
    for (s32 index = 0; index < 9; index++)
    {
        if (index && index % 3 == 0)
        {
            inset = 10.0f;
        }
        ItemCreationOptionResourceDisplay* display = new (0) ItemCreationOptionResourceDisplay;
        display->unkcc = allocation;
        display->unkd0 = 0;
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), record, inset + 66.0f * (index % 3), 4.0f + 75.0f * (index / 3));
        func_004C6190(unk10, display);
        unka8[index] = display;
        unka8[index]->unk34 = 3;
        display->unk50.unk34 = 1.0f;
        display->unk50.unk30 = 1.0f;
        display->unk3c = 1;
        inset += 6.0f;
    }
    colors.values[0] = 0xBCA4B4;
    colors.values[1] = 0xBCA4B4;
    colors.values[2] = 0x574C52;
    colors.values[3] = 0x574C52;
    unk104[3] = new (0) FieldClass15B200(unk10, 1);
    func_002D5290(unk104[3], 0xBC, 0x18, &colors, 230.0f, rows[0], 106.0f, 72.0f);
    set_resource_scalar(unk104[3], 40.0f);
    unk104[4] = new (0) FieldClass15B200(unk10, 1);
    func_002D5290(unk104[4], 0xBC, 0x18, &colors, 230.0f, rows[1], 106.0f, 72.0f);
    set_resource_scalar(unk104[4], 40.0f);
    unk104[5] = new (0) FieldClass15B200(unk10, 1);
    func_002D5290(unk104[5], 0xBC, 0x18, &colors, 230.0f, rows[2], 106.0f, 72.0f);
    set_resource_scalar(unk104[5], 40.0f);
    for (s32 index = 0; index < 3; index++)
    {
        unk140[index] = new (0) LibObject178750;
        unk140[index]->func_004C7FE0(230.0f, 72.0f * index + 3.0f * index, 106.0f, 72.0f, (s32)associated, 0x15FDD, 0);
        unk140[index]->set_mode(1);
        unk140[index]->set_vertical_alignment(1);
        if (index >= unk125)
        {
            unk140[index]->unk3f = 0;
        }
        func_004C6190(unk10, unk140[index]);
    }
    for (s32 index = 0; index < 3; index++)
    {
        unk128[index] = new (0) LibObject178750;
        unk134[index] = new (0) LibObject178750;
        unk128[index]->func_004C7FE0(8.0f, rows[index] - 6.0f, 0.0f, 0.0f, (s32)associated, index + 0x15FD7, 1);
        unk134[index]->func_004C7FE0(238.0f, rows[index] - 6.0f, 0.0f, 0.0f, (s32)associated, 0x15FDA, 1);
        unk128[index]->set_scale(0.75f, 0.75f);
        unk134[index]->set_scale(0.75f, 0.75f);
        if (index < unk125)
        {
            unk128[index]->set_color(0x1E8CFF);
            unk134[index]->set_color(0x1E8CFF);
        }
        else
        {
            unk128[index]->set_color(0x505050);
            unk134[index]->set_color(0x505050);
        }
        func_004C6190(unk10, unk128[index]);
        func_004C6190(unk10, unk134[index]);
    }
    colors.values[0] = 0xBCA4B4;
    colors.values[1] = 0xBCA4B4;
    colors.values[2] = 0x574C52;
    colors.values[3] = 0x574C52;
    unk104[6] = new (0) FieldClass15B200(unk10, 1);
    func_002D5290(unk104[6], 0xBC, 0x18, &colors, 0.0f, 226.0f, 336.0f, 161.0f);
    set_resource_scalar(unk104[6], 40.0f);
    allocation = func_002D3D80(D_001B643C->unk20, 0);
    record = func_002D3CC0(D_001B643C->unk20, 16);
    inset = 4.0f;
    s32 columns = 4;
    for (s32 index = 0; index < 14; index++)
    {
        if (index && index % columns == 0)
        {
            inset = 4.0f;
        }
        ItemCreationOptionResourceDisplay* display = new (0) ItemCreationOptionResourceDisplay;
        columns = 7;
        display->unkcc = allocation;
        display->unkd0 = 0;
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), record, inset + 44.57f * (index % columns), 236.0f + 78.0f * (index / columns));
        display->unk50.unk30 = 0.6857f;
        display->unk50.unk34 = 1.0f;
        display->unk3c = 1;
        func_004C6190(unk10, display);
        unkcc[index] = display;
        inset += 3.0f;
    }
    func_00366F10(this);
    return 1;
}

/** @brief Release the seven resource owners and destroy the option window. */
DevelopmentTeamsWindow::~DevelopmentTeamsWindow()
{
    for (s32 i = 0; i < 7; i++)
    {
        if (unk104[i])
        {
            release_owned(unk104[i]);
        }
    }
}

DevelopmentTeamsWindow::DevelopmentTeamsWindow()
{
    for (s32 i = 0; i < 9; i++)
    {
        unka8[i] = 0;
    }
    for (s32 i = 0; i < 14; i++)
    {
        unkcc[i] = 0;
    }
    for (s32 i = 0; i < 7; i++)
    {
        unk104[i] = 0;
    }
    for (s32 i = 0; i < 3; i++)
    {
        unk128[i] = 0;
        unk134[i] = 0;
        unk140[i] = 0;
    }
    unk120 = 0;
    unk124 = 0;
    unk125 = 0;
}

/**
 * @brief Create the workshop-facility panel and color its eight creation-skill labels.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 WorkshopFacilitiesWindow::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 288.0f, 17);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 266.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(0.0f, 20.0f, 266.0f, 16.0f, (s32)associated, 0x32D7, 0);
    heading->set_mode(1);
    heading->set_vertical_alignment(1);
    func_004C6190(unk10, heading);
    ItemCreationClass172870* divider = new (0) ItemCreationClass172870;
    func_421170(divider, heading->unke8, 44.0f, func_4C69B0(heading)->unk08, 4.0f);
    func_420D20(divider, 0x505050);
    func_004C6190(unk10, divider);
    for (s32 skill_index = 0; skill_index < 8; skill_index++)
    {
        LibObject178750* skill_label = new (0) LibObject178750;
        float x = 26.0f + 80.0f * (skill_index % 3);
        float y = 64.0f + 36.0f * (skill_index / 3);
        skill_label->func_004C7FE0(x, y, 0.0f, 0.0f, (s32)associated, ITEM_CREATION_SKILL_LABEL_BASE + skill_index, 0);
        func_004C6190(unk10, skill_label);
        func_0036F1A0(&unk2c, skill_label);
    }
    if (unka8)
    {
        for (s32 skill_index = 0; skill_index < 8; skill_index++)
        {
            ItemCreationListNode* node = func_0036F230(&unk2c, skill_index);
            LibObject178750* skill_label = static_cast<LibObject178750*>(node->unk00);
            if (skill_label)
            {
                if (unka8->workshop_skill_enabled[(u8)(skill_index + 1) - 1])
                {
                    skill_label->set_color(0x808080);
                }
                else
                {
                    skill_label->set_color(0x505050);
                }
            }
        }
    }
    return 1;
}


WorkshopFacilitiesWindow::~WorkshopFacilitiesWindow()
{
}

/**
 * @brief Create the panel and name label for the current workshop.
 * @param associated Object associated with the window.
 * @return Zero without the selection state, otherwise one.
 */
s32 WorkshopNameWindow::func_slotf4(void* associated)
{
    if (unka8 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 220.0f, 17);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 266.0f, 64.0f, 88.0f);
    func_004C6190(unk10, panel);
    u32 workshop_name_key = 0x3520;
    if (unka8)
    {
        workshop_name_key = item_creation_current_workshop_name_key(unka8);
    }
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(0.0f, 16.0f, 266.0f, 32.0f, (s32)associated, workshop_name_key, 1);
    heading->set_mode(1);
    heading->set_vertical_alignment(1);
    heading->set_color(0x806080);
    heading->set_scale(1.3f, 1.3f);
    func_004C6190(unk10, heading);
    return 1;
}


WorkshopNameWindow::~WorkshopNameWindow()
{
}

/**
 * @brief Refresh the choice labels, selection marker, and current status text.
 * @param object Three-choice window.
 */
extern "C" void func_00368370(ItemCreationMainMenu* object)
{
    if (object->unkac)
    {
        s16 selected = object->unkac->unk114;
        s32 index = 0;
        ItemCreationListNode* node = object->unk2c.unk00->unk04;
        while (node)
        {
            LibObject178750* widget = static_cast<LibObject178750*>(node->unk00);
            if (index == selected)
            {
                object->unkb0->func_0023B9B0(func_4C69B0(widget)->unk08, (s16)index);
                object->unkb0->unk3f = 1;
                widget->unk94 = ITEM_CREATION_COLOR_SELECTED;
                widget->unk3c = 1;
                if (!object->unkb4 && index == 2)
                {
                    widget->unk94 = ITEM_CREATION_COLOR_DIM;
                    widget->unk3c = 1;
                    object->unkb0->unk3f = 0;
                }
                FieldClass15AE70* text =
                    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90());
                if (text)
                {
                    text->func_slot60(selected);
                }
            }
            else
            {
                widget->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                widget->unk3c = 1;
                if (!object->unkb4 && index == 2)
                {
                    widget->unk94 = ITEM_CREATION_COLOR_DIM;
                    widget->unk3c = 1;
                }
            }
            node = node->unk04;
            ++index;
        }
    }
}

#include "include_asm.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/citemcreation/text_003684D0.h"
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/citemcreation/text_003483C0.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/1067-00/text_0028E240.h"


/** @brief Return the text display bounds. @param object Text display. @return Stored bounds. */
extern "C" LibBounds4C69B0* func_4C69B0(LibObject178750* object);

enum
{
    ITEM_CREATION_FLAG_0 = 0x1,
    ITEM_CREATION_FLAG_1 = 0x2,
    ITEM_CREATION_FLAG_2 = 0x4,
    ITEM_CREATION_FLAG_3 = 0x8,
    ITEM_CREATION_FLAG_4 = 0x10,
    ITEM_CREATION_FLAG_5 = 0x20,
    ITEM_CREATION_FLAG_6 = 0x40,
    ITEM_CREATION_FLAG_7 = 0x80,
    ITEM_CREATION_FLAG_8 = 0x100
};


/** Partial word in the resident state section copied during initialization. */
struct RuntimeStateSection58
{
    u8 unk00[0x1B4];
    s32 unk1b4;
};


typedef struct ItemCreationRuntimeRoot ItemCreationRuntimeRoot;
typedef struct ItemCreationRuntimeDirectory ItemCreationRuntimeDirectory;
typedef struct ItemCreationRuntimeFlags
{
    u8 unk00[0x7A];
    u8 unk7a;
    u8 unk7b;
} ItemCreationRuntimeFlags;


/**
 * @brief Create and configure the Field window's nested display container.
 * @param object Field window receiver.
 * @param associated Object associated with the window.
 * @param first First container configuration value.
 * @param second Second container configuration value.
 * @param third Third container configuration value.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param z Third coordinate.
 * @return One when the container and associated object are present, otherwise zero.
 */
extern "C" s32 func_002CE760(FieldClass15AE70* object, void* associated, s32 first, s32 second, s32 third, float x, float y, float z);
// Resident interfaces are scoped here because the shared declarations belong to another overlay.
extern "C"
{
    ItemCreationRuntimeRoot* func_10D8E0(void);
    ItemCreationRuntimeDirectory* func_101290(ItemCreationRuntimeRoot* root);
    ItemCreationRuntimeFlags* func_101440(ItemCreationRuntimeDirectory* directory, s32 key);


    extern LibVector4 D_50CD30[];
}

/**
 * @brief Convert an inventor option code to its saved inventor ID.
 * @param value Inventor option code; zero denotes an empty position.
 * @return Zero for an empty code, or the code minus 31.
 */
static inline u32 inventor_id_from_option_code(u8 value);

/**
 * @brief Test a one-based workshop ID.
 * @param index Workshop ID.
 * @return True for indices one through twelve.
 */
static inline bool workshop_id_valid(u8 index);

/**
 * @brief Test a nonzero saved inventor ID.
 * @param index Inventor ID.
 * @return True for indices one through thirty-eight.
 */
static inline bool saved_inventor_id_valid(u8 index);

/**
 * @brief Test a nonzero saved skill ID.
 * @param index Skill ID.
 * @return True for values one through nine.
 */
static inline bool saved_skill_id_valid(u8 index);

/**
 * @brief Save the inventors and creation skill for one development line.
 * @param state Runtime workshop data.
 * @param workshop_id One-based workshop ID.
 * @param line_index Development-line index, zero through two.
 * @param first First inventor ID, or zero for an empty position.
 * @param second Second inventor ID, or zero for an empty position.
 * @param third Third inventor ID, or zero for an empty position.
 * @param skill_id Saved skill ID, or zero for an empty line.
 */
static inline void store_workshop_line(ItemCreationRuntimeData* state, u8 workshop_id, u8 line_index, u8 first, u8 second, u8 third, u8 skill_id);

static inline void enable_record_flag(ItemCreationSelectedDisplayState* object, u16 mask)
{
    if (object->workshop != 0)
    {
        object->workshop->facility_mask |= mask;
    }
}

/**
 * @brief Convert an inventor option code to its saved inventor ID.
 * @param value Inventor option code; zero denotes an empty position.
 * @return Zero for an empty code, or the code minus 31.
 */
static inline u32 inventor_id_from_option_code(u8 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 31;
}

/**
 * @brief Test a one-based workshop ID.
 * @param index Workshop ID.
 * @return True for indices one through twelve.
 */
static inline bool workshop_id_valid(u8 index)
{
    return index > 0 && index < 13;
}

/**
 * @brief Test a nonzero saved inventor ID.
 * @param index Inventor ID.
 * @return True for indices one through thirty-eight.
 */
static inline bool saved_inventor_id_valid(u8 index)
{
    return index >= 1 && index < 39;
}

/**
 * @brief Test a nonzero saved skill ID.
 * @param index Skill ID.
 * @return True for values one through nine.
 */
static inline bool saved_skill_id_valid(u8 index)
{
    return index >= 1 && index < 10;
}

/**
 * @brief Save the inventors and creation skill for one development line.
 * @param state Runtime workshop data.
 * @param workshop_id One-based workshop ID.
 * @param line_index Development-line index, zero through two.
 * @param first First inventor ID, or zero for an empty position.
 * @param second Second inventor ID, or zero for an empty position.
 * @param third Third inventor ID, or zero for an empty position.
 * @param skill_id Saved skill ID, or zero for an empty line.
 */
static inline void store_workshop_line(ItemCreationRuntimeData* state, u8 workshop_id, u8 line_index, u8 first, u8 second, u8 third, u8 skill_id)
{
    if (!workshop_id_valid(workshop_id) || (s32)line_index < 0 || (s32)line_index >= 3)
    {
        return;
    }
    if (first > 0 && !saved_inventor_id_valid(first))
    {
        return;
    }
    if (second > 0 && !saved_inventor_id_valid(second))
    {
        return;
    }
    if (third > 0 && !saved_inventor_id_valid(third))
    {
        return;
    }
    if (skill_id > 0 && !saved_skill_id_valid(skill_id))
    {
        return;
    }
    ItemCreationWorkshopRecord* selected = &state->workshops[workshop_id - 1];
    ItemCreationLineRecord* line = &selected->lines[line_index];
    line->inventors[0] = first;
    line->inventors[1] = second;
    line->inventors[2] = third;
    line->skill_id = skill_id;
}

/** @brief Move the selector in its second direction and refresh the choice labels. */
void ItemCreationMainMenu::func_slot6c()
{
    if (!func_slot28())
    {
        if (unkac->func_0023CDB0(1) != 1)
        {
            func_00368370(this);
        }
    }
}

/** @brief Move the selector in its first direction and refresh the choice labels. */
void ItemCreationMainMenu::func_slot68()
{
    if (!func_slot28())
    {
        if (unkac->func_0023CDB0(0) != 1)
        {
            func_00368370(this);
        }
    }
}

/** @brief Restore the prior display. @return Zero while blocked, otherwise two. */
s32 ItemCreationMainMenu::func_slotb4()
{
    if (func_slot28())
    {
        return 0;
    }
    func_slot1c(0xFF, 0x80);
    return 2;
}

/**
 * @brief Confirm the selected choice and open its related window or record action.
 * @return Zero while blocked or for an unknown choice, three for an unavailable third choice, otherwise one.
 */
s32 ItemCreationMainMenu::func_slotb0()
{
    if (func_slot28())
    {
        return 0;
    }
    ItemCreationSelectedDisplayState* state;
    FieldObject23CEA0* selector = unkac;
    bool inactive = !selector->FieldClass151C50::unk35;
    if (inactive)
    {
        return 0;
    }
    state = static_cast<ItemCreationSelectedDisplayState*>(
        D_001B643C->unk10->unk14);
    if (!state)
    {
        return 0;
    }
    switch (selector->unk114)
    {
    case 0:
        state->unk47 = 1;
        func_0027CB50(D_001B6430->context->unk58,
                     state->unk1f0, 0, 0);
        break;
    case 1:
        {
            set_selector_depth(selector, 64.0f);
            WorkshopExpansionWindow* panel = static_cast<WorkshopExpansionWindow*>(func_slot4c());
            if (panel)
            {
                if (panel->unkdc)
                {
                    func_0023CEA0(panel->unkdc, 1);
                }
                panel->func_slot20(1);
                D_001B643C->unk10->unk14->func_00263C70(panel);
            }
            break;
        }
    case 2:
        if (!unkb4)
        {
            return 3;
        }
        state->unk47 = 3;
        func_0027CB50(D_001B6430->context->unk58,
                     state->unk1f0, 0, 0);
        break;
    case 3:
        break;
    default:
        return 0;
    }
    return 1;
}


/**
 * @brief Create the choice labels and field selection widgets.
 * @param associated Source associated with the nested display container and labels.
 * @return Always one.
 */
s32 ItemCreationMainMenu::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 78.0f, 17);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 266.0f, 140.0f, 88.0f);
    func_4C6190(unk10, panel);
    for (s32 index = 0; index < 3; index++)
    {
        LibObject178750* text = new (0) LibObject178750;
        float y = 20.0f + 34.0f * index;
        func_004C7FE0(text, (s32)associated, 0x32D3 + index, 0, 22.0f, y, 0.0f, 0.0f);
        text->set_scale(0.9f, 0.9f);
        text->unk88 = -1.0f;
        text->unk3c = 1;
        func_4C6190(unk10, text);
        func_0036F1A0(&unk2c, text);
    }
    bool outside_first_group = unka8->workshop_id >= 6;
    if (unka8->unk19b != 0 && !outside_first_group)
    {
        unkb4 = 1;
    }
    else
    {
        ItemCreationListNode* node = func_0036F230(&unk2c, 2);
        LibObject178750* text = static_cast<LibObject178750*>(node->unk00);
        if (text != 0)
        {
            text->unk94 = 0x505050;
            text->unk3c = 1;
        }
    }
    unkac = new (0) FieldObject23CEA0;
    unkac->func_0023CE80(1, 3);
    unkac->func_0023CE60(0.0f, 34.0f);
    unkac->unkF2 = 0;
    unkac->func_0023CF50(0, 38.0f, 98.0f);
    func_0036F040(&unk74, unkac);
    FieldObject23BE00* marker = new (0) FieldObject23BE00;
    unkb0 = marker;
    unkb0->func_0023BB20(22.0f, 18.0f, 215.99998f, 1.0f, unkac, 0x288080);
    func_4C6190(unk10, unkb0);
    func_0036EFB0(&unk8c, unkb0);
    func_00368370(this);
    return 1;
}

/** @brief Destroy the choice window through its Field base. */
ItemCreationMainMenu::~ItemCreationMainMenu()
{
}

/**
 * @brief Set a status message and reset its timed scroll.
 * @param text_key Absolute text key from 0x32CB through 0x32D2, or a signed relative index.
 */
void ItemCreationStatusBanner::func_slot60(s32 text_key)
{
    s32 key = text_key;
    if (text_key < 0x32CB)
    {
        key += 0x32CB;
    }
    if (key >= 0x32CB && key < 0x32D3)
    {
        unkba = 0;
        unkb8 = 0;
        void* associated = func_slot54();
        func_4C6DF0(unkac, associated, key, 1);
        LibBounds4C69B0* bounds = func_4C69B0(unkac);
        unkb0 = (s32)bounds->unk08 + 6;
    }
}

/** @brief Hold, then advance and wrap the horizontal status message. */
void ItemCreationStatusBanner::func_slot5c()
{
    LibObject178750* position = unkac;
    float x = position->unk18.unk00;
    float y = position->unk18.unk04;
    float z = position->unk18.unk08;
    float w = position->unk18.unk0c;
    float start;
    if (this->unkba == 0)
    {
        position->unk18.unk00 = this->unkc0;
        position->unk18.unk04 = y;
        position->unk18.unk08 = z;
        position->unk18.unk0c = w;
        position->unk3c = 1;
        this->unkb8++;
        if (!((float)this->unkb8 <= 120.0f))
        {
            this->unkb8 = 0;
            this->unkba = 1;
        }
        return;
    }
    start = this->unkc4;
    x -= 108.0f * D_001B6690;
    if (x < start - (float)this->unkb0)
    {
        x = start + this->unkc8 + 2.0f;
    }
    position->unk18.unk00 = x;
    position->unk18.unk04 = y;
    position->unk18.unk08 = z;
    position->unk18.unk0c = w;
    position->unk3c = 1;
}

/**
 * @brief Create the heading, list, value and footer displays and lay out the two columns.
 * @param associated Text source associated with the window.
 * @return Zero when an allocation failed, otherwise one.
 */
s32 ItemCreationStatusBanner::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1400, 16.0f, 16.0f, 0.0f);
    unkac = new (0) LibObject178750;
    LibObject178750* footer = new (0) LibObject178750;
    unkcc = new (0) ItemCreationClass1746A0;
    unkd0 = new (0) ItemCreationClass1746A0;
    if (unkac == 0 || unkcc == 0 || unkd0 == 0)
    {
        return 0;
    }
    unka8 = new (0) LibObject178750;
    func_004C7FE0(unka8, (s32)associated, 0x32C8, 0, 16.0f, 6.0f, 0.0f, 0.0f);
    LibObject178750* heading = unka8;
    heading->unk88 = -1.0f;
    heading->unk3c = 1;
    func_4C6190(unk10, unka8);
    LibBounds4C69B0* bounds = func_4C69B0(unka8);
    unkbc = bounds->unk08;
    unkc4 = 18.0f + unkbc;
    unkc8 = 640.0f - (16.0f + shifted_position(unkc4, 32.0f));
    unkc0 = 24.0f + unkbc;
    func_44B570(unkcc, unkc4, 0.0f, unkc8, 56.0f);
    func_4C6190(unk10, unkcc);
    func_0036F270(&unk20, unkcc);
    func_004C7FE0(unkac, (s32)associated, 0x32CB, 0, unkc0, 6.0f, 0.0f, 0.0f);
    func_4C6190(unk10, unkac);
    func_0036F1A0(&unk2c, unkac);
    func_44B510(unkd0, 1);
    func_4C6190(unk10, unkd0);
    func_0036F270(&unk20, unkd0);
    func_004C7FE0(footer, (s32)associated, 0x32CA, 0, 36.0f, 39.0f, 0.0f, 0.0f);
    footer->unk84 = 0.65f;
    footer->unk80 = 0.65f;
    footer->unk3c = 1;
    func_4C6190(unk10, footer);
    func_slot60(0);
    return 1;
}

/** @brief Destroy the status message window through its Field base. */
ItemCreationStatusBanner::~ItemCreationStatusBanner()
{
}

/**
 * @brief Create and position the three resource displays.
 * @param associated Source associated with the window's nested container.
 * @return Always one.
 */
s32 ItemCreationBackground::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1200, 16.0f, 16.0f, 0.0f);
    unka8 = new (0) ItemCreationOptionResourceDisplay;
    unkac = new (0) ItemCreationOptionResourceDisplay;
    unkb0 = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = func_002D3D80(D_001B643C->unk20, 11);
    unka8->unkcc = allocation;
    unkac->unkcc = allocation;
    unkb0->unkcc = allocation;
    unka8->unkd0 = 11;
    unkac->unkd0 = 11;
    unkb0->unkd0 = 11;
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 5);
    unka8->func_002D6440(record, 0.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 6);
    unkac->func_002D6440(record, 256.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 7);
    unkb0->func_002D6440(record, 512.0f, 0.0f);
    ItemCreationOptionResourceDisplay* display = unka8;
    display->unk50.unk44 = 200.0f;
    display->unk50.unk48 = 200.0f;
    display->unk50.unk4c = 200.0f;
    display->unk3c = 1;
    display = unkac;
    display->unk50.unk44 = 200.0f;
    display->unk50.unk48 = 200.0f;
    display->unk50.unk4c = 200.0f;
    display->unk3c = 1;
    display = unkb0;
    display->unk50.unk44 = 200.0f;
    display->unk50.unk48 = 200.0f;
    display->unk50.unk4c = 200.0f;
    display->unk3c = 1;
    display = unka8;
    display->unk28 = 80.0f;
    display->unk3c = 1;
    display = unkac;
    display->unk28 = 80.0f;
    display->unk3c = 1;
    display = unkb0;
    display->unk28 = 80.0f;
    display->unk3c = 1;
    func_4C6190(unk10, unka8);
    func_4C6190(unk10, unkac);
    func_4C6190(unk10, unkb0);
    return 1;
}

/** @brief Destroy the resource window through its Field base. */
ItemCreationBackground::~ItemCreationBackground()
{
}

/** @brief Initialize the twelve float pairs and their selection order. */
void ItemCreationSelection::func_slot10()
{
    unk00[0].unk00[0] = 136.0f;
    unk00[0].unk00[1] = 164.0f;
    unk00[1].unk00[0] = 136.0f;
    unk00[1].unk00[1] = 180.0f;
    unk00[2].unk00[0] = 60.0f;
    unk00[2].unk00[1] = 168.0f;
    unk00[3].unk00[0] = 348.0f;
    unk00[3].unk00[1] = 44.0f;
    unk00[4].unk00[0] = 340.0f;
    unk00[4].unk00[1] = 92.0f;
    unk00[5].unk00[0] = 212.0f;
    unk00[5].unk00[1] = 196.0f;
    unk00[6].unk00[0] = 160.0f;
    unk00[6].unk00[1] = 96.0f;
    unk00[7].unk00[0] = 96.0f;
    unk00[7].unk00[1] = 80.0f;
    unk00[8].unk00[0] = 108.0f;
    unk00[8].unk00[1] = 56.0f;
    unk00[9].unk00[0] = 60.0f;
    unk00[9].unk00[1] = 16.0f;
    unk00[10].unk00[0] = 380.0f;
    unk00[10].unk00[1] = 20.0f;
    unk00[11].unk00[0] = 16.0f;
    unk00[11].unk00[1] = 198.0f;
    unk6d[0] = 1;
    unk6d[1] = 2;
    unk6d[2] = 0;
    unk6d[3] = 5;
    unk6d[4] = 4;
    unk6d[5] = 3;
    unk6d[6] = 10;
    unk6d[7] = 9;
    unk6d[8] = 8;
    unk6d[9] = 7;
    unk6d[10] = 6;
    unk6d[11] = 11;
}

void func_00369510(ItemCreationSelection* object)
{
    s32 enabled;
    ItemCreationRuntimeFlags* flags = func_101440(func_101290(func_10D8E0()), 4);
    if (flags != 0)
    {
        enabled = (flags->unk7a & ITEM_CREATION_FLAG_4) != 0;
        if (enabled)
        {
            object->unk60[0] = 1;
        }
        enabled = (flags->unk7a & ITEM_CREATION_FLAG_5) != 0;
        if (enabled)
        {
            object->unk60[1] = 1;
        }
        enabled = (flags->unk7a & ITEM_CREATION_FLAG_6) != 0;
        if (enabled)
        {
            object->unk60[2] = 1;
        }
        enabled = (flags->unk7a & ITEM_CREATION_FLAG_7) != 0;
        if (enabled)
        {
            object->unk60[3] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_0) != 0;
        if (enabled)
        {
            object->unk60[4] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_1) != 0;
        if (enabled)
        {
            object->unk60[5] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_2) != 0;
        if (enabled)
        {
            object->unk60[6] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_3) != 0;
        if (enabled)
        {
            object->unk60[7] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_4) != 0;
        if (enabled)
        {
            object->unk60[8] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_5) != 0;
        if (enabled)
        {
            object->unk60[9] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_6) != 0;
        if (enabled)
        {
            object->unk60[10] = 1;
        }
        enabled = (flags->unk7b & ITEM_CREATION_FLAG_7) != 0;
        if (enabled)
        {
            object->unk60[11] = 1;
        }
        if (object->unk79 == 1 || object->unk79 == 2)
        {
            for (s32 index = 5; index < 12; index++)
            {
                object->unk60[index] = 0;
            }
        }
    }
}

u8 func_003696B0(ItemCreationSelection* object, u16 direction)
{
    s32 selected = object->unk6d[object->unk6c - 1];
    s32 slot;
    s32 index;

    do
    {
        switch (direction)
        {
        case 1:
        case 4:
            selected--;
            break;
        case 3:
        case 2:
            selected++;
            break;
        }
        if (selected < 0)
        {
            selected = 11;
        }
        if (selected >= 12)
        {
            selected = 0;
        }
        slot = -1;
        for (index = 0; index < 12; index++)
        {
            if (selected == object->unk6d[index])
            {
                slot = index + 1;
                break;
            }
        }
    } while (!object->unk60[slot - 1]);
    object->unk6c = slot;
    return object->unk6c;
}

/**
 * @brief Refresh the enabled selection slots.
 * @return Always one.
 */
s32 ItemCreationSelection::func_slot0c()
{
    func_00369510(this);
    return 1;
}

/** @brief Initialize the selection coordinates, slot flags, and order. */
ItemCreationSelection::ItemCreationSelection()
{
    for (s32 index = 0; index < 12; index++)
    {
        unk00[index].unk00[0] = 0.0f;
        unk00[index].unk00[1] = 0.0f;
        unk60[index] = 0;
        unk6d[index] = 0;
    }
    unk6c = 0;
    func_slot10();
}

// Field target setup interfaces; their shared declarations belong to Field.
extern "C"
{
    u8 func_002FAF50(FieldClass15BB30* target, u8 code, u8 group, u8 first, u8 second, u8 third, u8 count);
    u8 func_002FC310(FieldClass15BB50* target, u8 code, u8 group, u8 first, u8 second, u8 third, u8 count, s16 value);
    u8 func_002FCC50(FieldClass15BB70* target, u8 code, u8 group, u8 first, u8 second, u8 third, s16 first_value,
                     s16 second_value);
}

/**
 * @brief Rebuild the creation target for one three-inventor development line.
 * @param object Selection state.
 * @param line_index Development-line index from zero through two.
 */
void item_creation_rebuild_line_target(ItemCreationSelectedDisplayState* object, u8 line_index)
{
    u8 index = line_index;
    if (object->unk1c0[index] != 0 && object->unk1c3[index] != 0)
    {
        u8 first_inventor_id = inventor_id_from_option_code(object->unk68[index * 3]);
        u8 second_inventor_id = inventor_id_from_option_code(object->unk68[index * 3 + 1]);
        u8 third_inventor_id = inventor_id_from_option_code(object->unk68[index * 3 + 2]);
        ::operator delete(object->unk1b4[index]);
        object->unk1b4[index] = 0;
        u8 result = 0;
        switch (object->unk1c3[index])
        {
        case 1:
            object->unk1b4[index] = new (0) FieldClass15BB30;
            result = func_002FAF50(static_cast<FieldClass15BB30*>(object->unk1b4[index]), object->workshop_id, line_index,
                                  first_inventor_id, second_inventor_id, third_inventor_id, object->unk1c0[index]);
            break;
        case 2:
            object->unk1b4[index] = new (0) FieldClass15BB50;
            result = func_002FC310(static_cast<FieldClass15BB50*>(object->unk1b4[index]), object->workshop_id, line_index,
                                  first_inventor_id, second_inventor_id, third_inventor_id, object->unk1c0[index], object->unk1e2[index][0]);
            break;
        case 3:
            object->unk1b4[index] = new (0) FieldClass15BB70;
            result = func_002FCC50(static_cast<FieldClass15BB70*>(object->unk1b4[index]), object->workshop_id, line_index,
                                  first_inventor_id, second_inventor_id, third_inventor_id, object->unk1e2[index][0], object->unk1e2[index][1]);
            break;
        }
        if (result == 1)
        {
            object->unk1c8[index] = object->unk1b4[index]->unk78;
        }
        else
        {
            object->unk1c8[index] = 0;
        }
    }
    else
    {
        object->unk1c8[index] = 0;
        ::operator delete(object->unk1b4[index]);
        object->unk1b4[index] = 0;
    }
}

/**
 * @brief Advance or cancel the workshop/inventor selection steps of an inventor transfer.
 * @param object Selection state.
 * @param selection_value Workshop ID or inventor option code for the current step; -1 cancels it.
 */
void item_creation_advance_inventor_transfer(ItemCreationSelectedDisplayState* object, s32 selection_value)
{
    ItemCreationSelection* selection;
    InventorTransferWindow* transfer_window;
    s32 source_workshop_id;
    switch (object->unk129)
    {
    case 0:
        if (selection_value == -1)
        {
            object->unk129 = 0;
            object->unk12a = 0;
            object->unk12b = 0;
            object->unk12c = 0;
            object->unk12d = 0;
        }
        else
        {
            object->unk12a = selection_value;
            object->unk129 = 1;
        }
        break;
    case 1:
        if (selection_value == -1)
        {
            object->unk12b = 0;
            object->unk129 = 0;
        }
        else
        {
            object->unk12b = selection_value;
            object->unk129 = 2;
        }
        break;
    case 2:
        if (selection_value == -1)
        {
            object->unk12c = 0;
            object->unk129 = 1;
        }
        else
        {
            object->unk12c = selection_value;
            object->unk129 = 3;
        }
        break;
    case 3:
        if (selection_value == -1)
        {
            object->unk12d = 0;
            object->unk129 = 2;
            break;
        }
        object->unk12d = selection_value;
        if (object->unk12b != 0)
        {
            u8 placement_code = object->unk12c == 0 ? 0 : object->unk12c + 1;
            if (object->unk40 != 0)
            {
                object->unk40->unk188[object->unk12b] = placement_code;
            }
        }
        if (object->unk12d != 0)
        {
            u8 placement_code = object->unk12a == 0 ? 0 : object->unk12a + 1;
            if (object->unk40 != 0)
            {
                object->unk40->unk188[object->unk12d] = placement_code;
            }
        }
        source_workshop_id = object->unk12a;
        if (object->unkf8 != 0)
        {
            item_creation_build_transfer_inventor_list(object, source_workshop_id, 1);
            func_0034D340(object->unkf8);
            if (object->unkf8->unkc8 != 0)
            {
                func_0023CEA0(object->unkf8->unkc8, 0);
            }
        }
        object->unk129 = 0;
        object->unk12a = 0;
        object->unk12b = 0;
        object->unk12c = 0;
        object->unk12d = 0;
        transfer_window = object->unkf4;
        if (transfer_window != 0)
        {
            const float* position;
            LibClass175030* display;
            float x;
            float y;
            transfer_window->workshop_selection->unk6c = source_workshop_id;
            selection = transfer_window->workshop_selection;
            if ((u8)source_workshop_id <= 0)
            {
                position = 0;
            }
            else if ((u8)source_workshop_id > 12)
            {
                position = 0;
            }
            else
            {
                position = selection->unk00[(u8)source_workshop_id - 1].unk00;
            }
            display = transfer_window->unk15c;
            x = position[0];
            y = position[1];
            display->unk10 = x;
            display->unk14 = y;
            display->unk35 = 1;
            display->unk3c = 1;
            transfer_window = object->unkf4;
            switch (transfer_window->selection_state->unk129)
            {
            case 0:
                transfer_window->unk16c->unk3f = 0;
                transfer_window->unk15c->unk3f = 1;
                break;
            case 1:
                break;
            case 2:
                transfer_window->unk15c->unk3f = 1;
                break;
            case 3:
                break;
            }
            func_0034DA30(object->unkf4);
            func_0034DB00(object->unkf4, source_workshop_id);
        }
        if (object->unkfc != 0)
        {
            object->unk77[0] = 0;
            object->unk77[1] = 0;
            object->unk77[2] = 0;
            object->unk77[3] = 0;
            object->unk77[4] = 0;
            object->unk77[5] = 0;
            func_0034D340(object->unkfc);
            if (object->unkfc->unkc8 != 0)
            {
                func_0023CEA0(object->unkfc->unkc8, 0);
            }
        }
        break;
    }
}

/**
 * @brief Copy the first five workshops' saved facility masks into the selection state.
 * @param object Selection state; its other seven workshop masks are left unchanged.
 */
void func_00369EB0(ItemCreationSelectedDisplayState* object)
{
    object->workshop_facility_masks[0] = D_001B64F8->workshops[0].facility_mask;
    object->workshop_facility_masks[1] = D_001B64F8->workshops[1].facility_mask;
    object->workshop_facility_masks[2] = D_001B64F8->workshops[2].facility_mask;
    object->workshop_facility_masks[3] = D_001B64F8->workshops[3].facility_mask;
    object->workshop_facility_masks[4] = D_001B64F8->workshops[4].facility_mask;
}

/**
 * @brief Read the specialty message key for an inventor option code.
 * @param object Unused receiver.
 * @param inventor_option_code Inventor ID plus 31, or an unmapped byte.
 * @return The NPC specialty key from 0x3458 through 0x345E, or 0x3457 for party or unmapped codes.
 */
u16 item_creation_inventor_skill_message(void* object, u8 inventor_option_code)
{
    u16 skill_code = 0;

    switch (inventor_option_code)
    {
    case 35:
    case 45:
    case 54:
    case 58:
        skill_code = 1;
        break;
    case 33:
    case 39:
    case 49:
    case 50:
        skill_code = 2;
        break;
    case 34:
    case 41:
    case 48:
    case 52:
        skill_code = 5;
        break;
    case 43:
    case 51:
    case 53:
    case 56:
        skill_code = 4;
        break;
    case 36:
    case 46:
    case 55:
    case 57:
        skill_code = 7;
        break;
    case 38:
    case 44:
    case 47:
    case 59:
        skill_code = 3;
        break;
    case 32:
    case 37:
    case 40:
    case 42:
        skill_code = 6;
        break;
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
        skill_code = 0;
        break;
    }
    return skill_code + 0x3457;
}

/**
 * @brief Read the creation-skill capability mask for an inventor option code.
 * @param object Unused receiver.
 * @param inventor_option_code Inventor ID plus 31, or an unmapped byte.
 * @return One specialty bit for NPC codes, 0x1FF for party codes, or zero when unmapped.
 */
u16 item_creation_inventor_skill_mask(void* object, u8 inventor_option_code)
{
    u16 skill_mask = 0;

    switch (inventor_option_code)
    {
    case 35:
    case 45:
    case 54:
    case 58:
        skill_mask |= 0x1;
        break;
    case 33:
    case 39:
    case 49:
    case 50:
        skill_mask |= 0x2;
        break;
    case 34:
    case 41:
    case 48:
    case 52:
        skill_mask |= 0x10;
        break;
    case 43:
    case 51:
    case 53:
    case 56:
        skill_mask |= 0x8;
        break;
    case 36:
    case 46:
    case 55:
    case 57:
        skill_mask |= 0x40;
        break;
    case 38:
    case 44:
    case 47:
    case 59:
        skill_mask |= 0x4;
        break;
    case 32:
    case 37:
    case 40:
    case 42:
        skill_mask |= 0x20;
        break;
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
        skill_mask |= 0x1ff;
        break;
    }
    return skill_mask;
}

/**
 * @brief Select or cancel an inventor slot, swapping inventor codes after the second selection.
 * @param object Selection state.
 * @param grid Assigned or available inventor grid.
 * @param slot_index Grid slot; -1 cancels the pending selection.
 */
void item_creation_select_inventor_for_swap(ItemCreationSelectedDisplayState* object, void* grid, s16 slot_index)
{
    switch (object->unk128)
    {
    case 0:
        if (slot_index == -1)
        {
            object->unk120 = 0;
            object->unk11c = 0;
            object->unk126 = -1;
            object->unk124 = -1;
            object->unk128 = 0;
        }
        else
        {
            object->unk11c = grid;
            object->unk120 = 0;
            object->unk124 = slot_index;
            object->unk128 = 1;
        }
        break;
    case 1:
        if (slot_index == -1)
        {
            object->unk120 = 0;
            object->unk11c = 0;
            object->unk126 = -1;
            object->unk124 = -1;
            object->unk128 = 0;
        }
        else
        {
            object->unk120 = grid;
            object->unk126 = slot_index;
            object->unk128 = 2;
        }
        break;
    }
    if (object->unk11c != 0 && object->unk120 != 0 && object->unk128 == 2)
    {
        void* source_grid = object->unk11c;
        void* destination_grid = object->unk120;
        u8 source_inventor_code = 0;
        u8 destination_inventor_code = 0;
        AvailableInventorGrid* available_grid;
        AssignedInventorGrid* assigned_grid;

        if (source_grid == object->unkb8)
        {
            source_inventor_code = object->unk5a[(u16)object->unk124];
        }
        else if (source_grid == object->unkbc)
        {
            source_inventor_code = object->unk68[(u16)object->unk124];
        }
        if (destination_grid == object->unkb8)
        {
            destination_inventor_code = object->unk5a[(u16)object->unk126];
        }
        else if (destination_grid == object->unkbc)
        {
            destination_inventor_code = object->unk68[(u16)object->unk126];
        }
        if (source_grid == object->unkb8)
        {
            object->unk5a[(u16)object->unk124] = destination_inventor_code;
        }
        else if (source_grid == object->unkbc)
        {
            object->unk68[(u16)object->unk124] = destination_inventor_code;
        }
        if (object->unk120 == object->unkb8)
        {
            s32 marker_index;
            object->unk5a[(u16)object->unk126] = source_inventor_code;
            available_grid = object->unkb8;
            if (available_grid->unkb4 != 0)
            {
                s32 active = available_grid->unkb4->unk114;
                for (marker_index = 0; marker_index < 14; marker_index++)
                {
                    if (active == marker_index)
                    {
                        available_grid->unkb8[marker_index]->unk3f = 1;
                    }
                    else
                    {
                        available_grid->unkb8[marker_index]->unk3f = 0;
                    }
                }
            }
        }
        else if (object->unk120 == object->unkbc)
        {
            object->unk68[(u16)object->unk126] = source_inventor_code;
            func_00361220(object->unkbc);
        }
        func_00364D20(object->unkb8);
        func_003614B0(object->unkbc);
        source_grid = object->unk11c;
        available_grid = object->unkb8;
        if (available_grid == source_grid)
        {
            FieldObject23CEA0* restore;
            FieldObject23CEA0* display = available_grid->unkb4;
            if (display == available_grid->unkb0)
            {
                s16 selected_index = display->unk114;
                float x;
                float y;
                restore = available_grid->unkac;
                restore->FieldClass151C50::unk30 = 128.0f;
                restore->unkae = 1;
                x = display->unk10.x;
                y = display->unk10.y;
                restore = available_grid->unkac;
                restore->unk10.x = x;
                restore->unk10.y = y;
                restore->unk35 = 1;
                restore->unkae = 1;
                restore = available_grid->unkac;
                restore->index = selected_index;
                func_0023CB30(restore);
                func_0023C7B0(available_grid->unkac);
                func_0023CEA0(available_grid->unkb0, 0);
                available_grid->unkb4 = available_grid->unkac;
            }
            func_00364090(object->unkb8, 0);
            if (object->unkb8 == object->unk120)
            {
                func_00364090(object->unkb8, 1);
            }
            else if (object->unkbc == object->unk120)
            {
                func_00360E60(object->unkbc, 1);
                item_creation_rebuild_line_target(object, (u8)(object->unk126 / 3));
            }
        }
        else
        {
            assigned_grid = object->unkbc;
            if (assigned_grid == source_grid)
            {
                FieldObject23CEA0* restore;
                FieldObject23CEA0* display = assigned_grid->unkb4;
                if (display == assigned_grid->unkb0)
                {
                    s16 selected_index = display->unk114;
                    float x;
                    float y;
                    restore = assigned_grid->unkac;
                    restore->FieldClass151C50::unk30 = 128.0f;
                    restore->unkae = 1;
                    x = display->unk10.x;
                    y = display->unk10.y;
                    restore = assigned_grid->unkac;
                    restore->unk10.x = x;
                    restore->unk10.y = y;
                    restore->unk35 = 1;
                    restore->unkae = 1;
                    restore = assigned_grid->unkac;
                    restore->index = selected_index;
                    func_0023CB30(restore);
                    func_0023C7B0(assigned_grid->unkac);
                    func_0023CEA0(assigned_grid->unkb0, 0);
                    assigned_grid->unkb4 = assigned_grid->unkac;
                }
                func_00360E60(object->unkbc, 0);
                if (object->unkb8 == object->unk120)
                {
                    func_00364090(object->unkb8, 1);
                    item_creation_rebuild_line_target(object, (u8)(object->unk124 / 3));
                }
                else if (object->unkbc == object->unk120)
                {
                    func_00360E60(object->unkbc, 1);
                    item_creation_rebuild_line_target(object, (u8)(object->unk124 / 3));
                    item_creation_rebuild_line_target(object, (u8)(object->unk126 / 3));
                }
            }
        }
        item_creation_show_inventor_information(object, object->unk120, object->unk126);
        object->unk120 = 0;
        object->unk11c = 0;
        object->unk126 = -1;
        object->unk124 = -1;
        object->unk128 = 0;
    }
}

/**
 * @brief Refresh inventor information from a slot in the assigned or available grid.
 * @param object Selection state.
 * @param grid Grid supplying the inventor code; another nonnull grid clears the inventor.
 * @param slot_index Slot in the supplied grid.
 */
void item_creation_show_inventor_information(ItemCreationSelectedDisplayState* object, void* grid, s16 slot_index)
{
    if (grid != 0 && object->unkb8 != 0 && object->unkbc != 0 && object->unkc0 != 0)
    {
        u8 inventor_option_code = 0;
        InventorInformationWindow* information_window;
        object->unk118 = grid;
        if (object->unk118 == object->unkb8)
        {
            inventor_option_code = object->unk5a[(u16)slot_index];
        }
        else if (object->unk118 == object->unkbc)
        {
            inventor_option_code = object->unk68[(u16)slot_index];
        }
        information_window = object->unkc0;
        information_window->unk101 = inventor_option_code;
        if (information_window->unka8 != 0)
        {
            information_window->unk102 = 0;
            information_window->unk102 = item_creation_inventor_skill_mask(information_window->unka8, information_window->unk101);
        }
        information_window->func_00358850();
        object->unk118 = 0;
    }
}

/**
 * @brief Refresh workshop skill and line colors, or one transfer inventor strip.
 * @param object Selection state.
 * @param refresh_mode One refreshes workshop/team labels; six refreshes source inventors; seven refreshes destination inventors.
 */
void item_creation_refresh_team_and_transfer_windows(ItemCreationSelectedDisplayState* object, u8 refresh_mode)
{
    switch (refresh_mode)
    {
    case 1:
        if (object->unka8 != 0)
        {
            WorkshopFacilitiesWindow* display = object->unka8;
            if (display->unka8 != 0)
            {
                s32 index;
                for (index = 0; index < 8; index++)
                {
                    ItemCreationListNode* node = func_0036F230(&display->unk2c, index);
                    LibObject178750* label = static_cast<LibObject178750*>(node->unk00);
                    if (label != 0)
                    {
                        u8 skill_id = index + 1;
                        if (display->unka8->workshop_skill_enabled[skill_id - 1] != 0)
                        {
                            label->set_color(0x808080);
                        }
                        else
                        {
                            label->set_color(0x505050);
                        }
                    }
                }
            }
        }
        if (object->unkb0 != 0)
        {
            DevelopmentTeamsWindow* display = object->unkb0;
            s32 index;
            display->unk125 = display->unk120->unk57;
            for (index = 0; index < 3; index++)
            {
                if (index < display->unk125)
                {
                    LibObject178750* label = display->unk128[index];
                    label->set_color(0x1E8CFF);
                    label = display->unk134[index];
                    label->set_color(0x1E8CFF);
                }
                else
                {
                    LibObject178750* label = display->unk128[index];
                    label->set_color(0x505050);
                    label = display->unk134[index];
                    label->set_color(0x505050);
                }
            }
        }
        break;
    case 6:
        if (object->unkf8 != 0)
        {
            func_0034D340(object->unkf8);
        }
        break;
    case 7:
        if (object->unkfc != 0)
        {
            func_0034D340(object->unkfc);
        }
        break;
    }
}

/**
 * @brief Rebuild a transfer strip from the NPC inventors placed in the selected workshop.
 * @param object Selection state.
 * @param workshop_id Workshop ID from one through eleven; other values leave state unchanged.
 * @param transfer_list One selects the source strip and two the destination strip.
 */
void item_creation_build_transfer_inventor_list(ItemCreationSelectedDisplayState* object, u16 workshop_id, u8 transfer_list)
{
    s32 clear_index;
    u16 inventor_count;
    s32 inventor_option_code;
    u8 selected_workshop_id;

    if (object->unk40 != 0 && (workshop_id == 0 ? 0 : workshop_id + 1) > 1 && (workshop_id == 0 ? 0 : workshop_id + 1) < 13)
    {
        clear_index = 0;
        do
        {
            switch (transfer_list)
            {
            case 1:
                object->unk71[clear_index] = 0;
                break;
            case 2:
                object->unk77[clear_index] = 0;
                break;
            }
            clear_index++;
        } while (clear_index < 6);
        selected_workshop_id = 0;
        switch (transfer_list)
        {
        case 1:
            object->unk58 = workshop_id;
            selected_workshop_id = object->unk58;
            break;
        case 2:
            object->unk59 = workshop_id;
            selected_workshop_id = object->unk59;
            break;
        }
        inventor_count = 0;
        inventor_option_code = 32;
        do
        {
            s32 placement_code = object->unk40->unk188[inventor_option_code];
            if (placement_code > 1 && placement_code == (selected_workshop_id == 0 ? 0 : selected_workshop_id + 1))
            {
                switch (transfer_list)
                {
                case 1:
                    object->unk71[inventor_count++] = inventor_option_code;
                    break;
                case 2:
                    object->unk77[inventor_count++] = inventor_option_code;
                    break;
                }
            }
            inventor_option_code++;
        } while (inventor_option_code <= 59);
    }
}

/**
 * @brief Save the three-inventor teams and creation skills for the current workshop.
 * @param object Selected display state.
 */
void item_creation_save_workshop_lines(ItemCreationSelectedDisplayState* object)
{
    for (s32 index = 0; index < object->unk57; index++)
    {
        store_workshop_line(D_001B64F8, object->workshop->workshop_id, index,
            inventor_id_from_option_code(object->unk68[index * 3]),
            inventor_id_from_option_code(object->unk68[index * 3 + 1]),
            inventor_id_from_option_code(object->unk68[index * 3 + 2]), object->unk1c0[index]);
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0036AAA0);

/**
 * @brief Restore installed workshop skills and enable appraisal.
 * @param object Selection state with its optional workshop record.
 */
void item_creation_restore_workshop_skill_flags(ItemCreationSelectedDisplayState* object)
{
    if (object->workshop != 0)
    {
        object->facility_mask = object->workshop->facility_mask;
        if (object->facility_mask & ITEM_CREATION_FACILITY_COOK)
        {
            enable_record_flag(object, ITEM_CREATION_FACILITY_COOK);
            object->workshop_skill_enabled[0] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_ALCH)
        {
            enable_record_flag(object, ITEM_CREATION_FACILITY_ALCH);
            object->workshop_skill_enabled[1] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_CRFT)
        {
            enable_record_flag(object, ITEM_CREATION_FACILITY_CRFT);
            object->workshop_skill_enabled[2] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_CMPD)
        {
            enable_record_flag(object, ITEM_CREATION_FACILITY_CMPD);
            object->workshop_skill_enabled[3] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_SMTH)
        {
            enable_record_flag(object, ITEM_CREATION_FACILITY_SMTH);
            object->workshop_skill_enabled[4] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_WRIT)
        {
            enable_record_flag(object, ITEM_CREATION_FACILITY_WRIT);
            object->workshop_skill_enabled[5] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_ENG)
        {
            enable_record_flag(object, ITEM_CREATION_FACILITY_ENG);
            object->workshop_skill_enabled[6] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_SYTH)
        {
            enable_record_flag(object, ITEM_CREATION_FACILITY_SYTH);
            object->workshop_skill_enabled[7] = 1;
        }
        enable_record_flag(object, ITEM_CREATION_FLAG_8);
        object->workshop_skill_enabled[8] = 1;
    }
}

/**
 * @brief Read the workshop ID corresponding to the current area.
 * @param object Unused receiver.
 * @return Workshop ID from one through twelve, or zero outside a workshop area.
 */
u8 item_creation_current_workshop_id(ItemCreationSelectedDisplayState* object)
{
    u8 workshop_id;
    switch (D_001B6430->context->unk08->unkb8)
    {
    case 31:
        workshop_id = 1;
        break;
    case 32:
        workshop_id = 2;
        break;
    case 94:
        workshop_id = 3;
        break;
    case 113:
        workshop_id = 4;
        break;
    case 142:
        workshop_id = 5;
        break;
    case 499:
        workshop_id = 6;
        break;
    case 575:
        workshop_id = 7;
        break;
    case 602:
        workshop_id = 8;
        break;
    case 652:
        workshop_id = 9;
        break;
    case 664:
        workshop_id = 10;
        break;
    case 805:
        workshop_id = 11;
        break;
    case 1135:
        workshop_id = 12;
        break;
    default:
        workshop_id = 0;
        break;
    }
    return workshop_id;
}

/**
 * @brief Read the workshop name message corresponding to the current area.
 * @param object Unused receiver.
 * @return Message key from 0x3521 through 0x352C, or the 0x3520 error label.
 */
u32 item_creation_current_workshop_name_key(void* object)
{
    switch (D_001B6430->context->unk08->unkb8)
    {
    case 31:
        return 0x3521;
    case 32:
        return 0x3522;
    case 94:
        return 0x3523;
    case 113:
        return 0x3524;
    case 142:
        return 0x3525;
    case 499:
        return 0x3526;
    case 575:
        return 0x3527;
    case 602:
        return 0x3528;
    case 652:
        return 0x3529;
    case 664:
        return 0x352A;
    case 805:
        return 0x352B;
    case 1135:
        return 0x352C;
    default:
        return 0x3520;
    }
}

/**
 * @brief Find the map position for a one-based workshop ID.
 * @param selection Workshop selection containing twelve map positions.
 * @param workshop_id Workshop ID from one through twelve.
 * @return Position, or null for an invalid workshop ID.
 */
static inline const float* workshop_map_position(ItemCreationSelection* selection, s32 workshop_id)
{
    if (workshop_id <= 0)
    {
        return 0;
    }
    if (workshop_id > 12)
    {
        return 0;
    }
    return selection->unk00[workshop_id - 1].unk00;
}
/**
 * @brief Enable or disable the inventor transfer windows and restore the selected workshop.
 * @param object State owning the transfer window and source/destination inventor strips.
 * @param enabled Full-word control flag; nonzero refreshes the workshop selections and inventor strips.
 */
extern "C" void func_0036B1E0(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    if (object->unkf4 != 0)
    {
        if (enabled != 0)
        {
            func_0034DA30(object->unkf4);
            func_0034DB00(object->unkf4, object->workshop_id);
            func_0034D980(object->unkf4, object->workshop_id);
            InventorTransferWindow* transfer_window = object->unkf4;
            s32 selected_workshop_id = object->workshop_id;
            transfer_window->workshop_selection->unk6c = selected_workshop_id;
            const float* workshop_position = workshop_map_position(transfer_window->workshop_selection, selected_workshop_id);
            set_transfer_position(transfer_window->unk15c, workshop_position[0], workshop_position[1]);
            object->func_00263C70(object->unkf4);
        }
        object->unkf4->func_slot20(enabled);
    }
    if (object->unkf8 != 0)
    {
        object->unkf8->func_slot20(enabled);
        if (enabled != 0)
        {
            func_0034D340(object->unkf8);
        }
    }
    if (object->unkfc != 0)
    {
        object->unkfc->func_slot20(enabled);
        if (enabled != 0)
        {
            func_0034D340(object->unkfc);
        }
    }
    if (object->unk9c != 0 && enabled != 0)
    {
        object->unk9c->func_slot60(0x32CD);
    }
}

/**
 * @brief Activate the resource window and reset the related selection displays.
 * @param object State owning the resource, option, and message windows.
 * @param enabled Full-word activation flag; zero disables the resource window.
 */
extern "C" void func_0036B360(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    ItemCreationClass186770* resource = object->unkd8;
    if (resource != 0)
    {
        if (resource->unk10c != 0)
        {
            func_0023CEA0(resource->unk10c, enabled);
            if (enabled != 0)
            {
                FieldObject23CEA0* marker = resource->unk10c;
                marker->FieldClass151C50::unk30 = 128.0f;
                marker->unkae = 1;
            }
            else
            {
                FieldObject23CEA0* marker = resource->unk10c;
                marker->FieldClass151C50::unk30 = 64.0f;
                marker->unkae = 1;
            }
        }
        resource->func_slot20(enabled);
        if (enabled != 0)
        {
            func_00356FD0(object->unkd8);
            func_00356160(object->unkd8);
            object->func_00263C70(object->unkd8);
            for (s32 index = 0; index < 3; index++)
            {
                u8 value = object->unk148[index];
                func_0036C080(object, index, value);
                if (value == 0)
                {
                    object->unk1b1[index] = 1;
                }
            }
            item_creation_schedule_inventor_resource(object);
        }
    }
    if (object->unke4 != 0)
    {
        object->unke4->func_slot20(enabled);
    }
    if (object->unkb4 != 0)
    {
        if (enabled != 0)
        {
            object->unkb4->func_003598E0(3, enabled);
        }
        object->unkb4->func_slot20(enabled);
    }
    if (object->unke8 != 0)
    {
        object->unke8->func_slot20(0);
    }
    if (object->unkec != 0)
    {
        object->unkec->func_slot20(0);
    }
    ItemDetailsWindow* actor = object->unke0;
    if (actor != 0)
    {
        actor->func_slot20(0);
        actor->unke8->unkab = 0;
    }
    ItemSubmissionDialog* colors = object->unkdc;
    if (colors != 0)
    {
        colors->func_slot20(0);
        func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(colors->unkac)), 1);
        if (colors->unkac != 0)
        {
            for (s32 index = 0; index < 2; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(
                    func_0036F230(&colors->unk2c, index)->unk00);
                if (index == 1)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    func_0023B7E0(static_cast<FieldObject23B950*>(static_cast<void*>(colors->unkb0)),
                                   static_cast<FieldTarget23B850*>(static_cast<void*>(display)));
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
    if (object->unkf0 != 0)
    {
        object->unkf0->func_slot20(0);
    }
    ItemCreationStatusBanner* message = object->unk9c;
    if (message != 0 && enabled != 0)
    {
        if (message->unka8 != 0)
        {
            func_4C6DF0(message->unka8, message->func_slot54(), 0x1B89, 0);
            float height = func_4C69B0(message->unka8)->unk08;
            message->unkbc = height;
            message->unkc4 = 18.0f + height;
            message->unkc8 = 640.0f - (16.0f + (32.0f + message->unkc4));
            message->unkc0 = 24.0f + message->unkbc;
            float width = message->unkc8;
            ItemCreationClass1746A0* frame = message->unkcc;
            frame->unk18.unk00 = message->unkc4;
            frame->unk18.unk04 = 0.0f;
            frame->unk18.unk08 = width;
            frame->unk18.unk0c = 56.0f;
            frame->unk50 = 0;
            frame->unk3c = 1;
        }
        object->unk9c->func_slot60(0x32D0);
    }
}

/**
 * @brief Enable or disable inventor team selection and reset its subsidiary windows.
 * @param object State owning the assigned/available inventor grids and their detail windows.
 * @param enabled Full-word control flag; nonzero refreshes the inventor grids and team-selection prompt.
 */
extern "C" void func_0036B6E0(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    if (object->unkb4 != 0)
    {
        if (enabled != 0)
        {
            object->unkb4->func_003598E0(2, enabled);
        }
        object->unkb4->func_slot20(enabled);
    }
    if (object->unkbc != 0)
    {
        if (enabled != 0)
        {
            func_00363D20(object->unkbc);
            if (object->unkbc->unkb4 != 0)
            {
                func_0023C550(object->unkbc->unkb4, 0);
            }
            func_00361220(object->unkbc);
            func_003614B0(object->unkbc);
        }
        func_003610D0(object->unkbc, enabled);
    }
    if (object->unkb8 != 0)
    {
        func_00364E00(object->unkb8, enabled);
        if (enabled != 0)
        {
            func_00364090(object->unkb8, 1);
            if (object->unkb8->unkb4 != 0)
            {
                func_0023C550(object->unkb8->unkb4, 0);
            }
            func_00364D20(object->unkb8);
            AvailableInventorGrid* available_grid = object->unkb8;
            if (available_grid->unkb4 != 0)
            {
                s32 slot_index;
                s32 selected_slot = available_grid->unkb4->unk114;
                for (slot_index = 0; slot_index < 14; slot_index++)
                {
                    if (selected_slot == slot_index)
                    {
                        available_grid->unkb8[slot_index]->unk3f = 1;
                    }
                    else
                    {
                        available_grid->unkb8[slot_index]->unk3f = 0;
                    }
                }
            }
            object->func_00263C70(object->unkb8);
        }
    }
    InventorInformationWindow* inventor_information = object->unkc0;
    if (inventor_information != 0)
    {
        inventor_information->func_slot20(0);
        inventor_information->unk100 = 0;
    }
    if (object->unkc4 != 0)
    {
        object->unkc4->func_slot20(0);
    }
    if (object->unkc8 != 0)
    {
        object->unkc8->func_slot20(0);
    }
    if (object->unkcc != 0)
    {
        object->unkcc->func_slot20(0);
    }
    if (object->unkd0 != 0)
    {
        object->unkd0->func_slot20(0);
    }
    if (object->unkd4 != 0)
    {
        object->unkd4->func_slot20(0);
    }
    ItemCreationStatusBanner* status_banner = object->unk9c;
    if (status_banner != 0 && enabled != 0)
    {
        if (status_banner->unka8 != 0)
        {
            func_4C6DF0(status_banner->unka8, status_banner->func_slot54(), 0x32C9, 0);
            float title_width = func_4C69B0(status_banner->unka8)->unk08;
            status_banner->unkbc = title_width;
            status_banner->unkc4 = 18.0f + title_width;
            status_banner->unkc8 = 640.0f - (16.0f + (32.0f + status_banner->unkc4));
            status_banner->unkc0 = 24.0f + status_banner->unkbc;
            float message_frame_width = status_banner->unkc8;
            ItemCreationClass1746A0* message_frame = status_banner->unkcc;
            message_frame->unk18.unk00 = status_banner->unkc4;
            message_frame->unk18.unk04 = 0.0f;
            message_frame->unk18.unk08 = message_frame_width;
            message_frame->unk18.unk0c = 56.0f;
            message_frame->unk50 = 0;
            message_frame->unk3c = 1;
        }
        object->unk9c->func_slot60(0x32D2);
    }
}

/**
 * @brief Enable or disable the main menu and workshop summary windows.
 * @param object State owning the main menu, facilities, workshop name and development-team summary.
 * @param enabled Full-word control flag; nonzero restores main-menu focus and its status prompt.
 */
extern "C" void func_0036BA10(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    ItemCreationMainMenu* main_menu = object->unka0;
    if (main_menu != 0)
    {
        if (main_menu->unkac != 0)
        {
            func_0023CEA0(main_menu->unkac, enabled);
        }
        main_menu->func_slot20(enabled);
        if (enabled != 0)
        {
            object->func_00263C70(object->unka0);
            object->unk1b1[0] = 0;
            object->unk1b1[1] = 0;
            object->unk1b1[2] = 0;
        }
    }
    if (object->unka8 != 0)
    {
        object->unka8->func_slot20(enabled);
    }
    WorkshopExpansionWindow* expansion_window = object->unkac;
    if (expansion_window != 0)
    {
        if (expansion_window->unkdc != 0)
        {
            func_0023CEA0(expansion_window->unkdc, 0);
        }
        expansion_window->func_slot20(0);
    }
    if (object->unkb0 != 0)
    {
        object->unkb0->func_slot20(enabled);
        if (enabled != 0)
        {
            func_00366F10(object->unkb0);
        }
    }
    if (object->unka4 != 0)
    {
        object->unka4->func_slot20(enabled);
    }
    ItemCreationStatusBanner* status_banner = object->unk9c;
    if (status_banner != 0 && enabled != 0)
    {
        if (status_banner->unka8 != 0)
        {
            func_4C6DF0(status_banner->unka8, status_banner->func_slot54(), 0x32C8, 0);
            float title_width = func_4C69B0(status_banner->unka8)->unk08;
            status_banner->unkbc = title_width;
            status_banner->unkc4 = 18.0f + title_width;
            status_banner->unkc8 = 640.0f - (16.0f + (32.0f + status_banner->unkc4));
            status_banner->unkc0 = 24.0f + status_banner->unkbc;
            float message_frame_width = status_banner->unkc8;
            ItemCreationClass1746A0* message_frame = status_banner->unkcc;
            message_frame->unk18.unk00 = status_banner->unkc4;
            message_frame->unk18.unk04 = 0.0f;
            message_frame->unk18.unk08 = message_frame_width;
            message_frame->unk18.unk0c = 56.0f;
            message_frame->unk50 = 0;
            message_frame->unk3c = 1;
        }
        object->unk9c->func_slot60(0x32CB);
        if (object->unk45 == 0 && object->unka0 != 0)
        {
            s16 menu_index = object->unka0->unkac != 0 ? object->unka0->unkac->unk114 : -1;
            if (menu_index == 2)
            {
                object->unk9c->func_slot60(0x32CD);
            }
        }
    }
}

/**
 * @brief Activate an item-creation window group after clearing pending inventor resources.
 *
 * Group zero shows the main menu, one selects team members, two shows inventing,
 * and three transfers inventors. Group four and other values leave visibility unchanged.
 * All groups clear pending inventor resources.
 * Activated groups restore their active receiver when one is available.
 *
 * @param object State owning the window groups and pending inventor resources.
 * @param group Window group to activate.
 */
extern "C" void item_creation_activate_window_group(ItemCreationSelectedDisplayState* object, u8 group)
{
    if (object->unk19c != 0)
    {
        func_002FD940(object->unk19c);
        object->unk1a8 = 1;
    }
    object->unk1a4 = 0;
    object->unk1a0 = 0;
    object->unk1ac = 0;
    switch (group)
    {
    case 0:
        func_0036B6E0(object, 0);
        func_0036B1E0(object, 0);
        func_0036B360(object, 0);
        func_0036BA10(object, 1);
        break;
    case 1:
        func_0036BA10(object, 0);
        func_0036B1E0(object, 0);
        func_0036B360(object, 0);
        func_0036B6E0(object, 1);
        object->unk98->func_slot58()->func_0044B110(0, 9, 1200, 0, 0.0f);
        object->unk9c->func_slot58()->func_0044B110(0, 9, 1400, 0, 0.0f);
        object->unkb4->func_slot58()->func_0044B110(0, 9, 1800, 0, 0.0f);
        break;
    case 2:
        func_0036BA10(object, 0);
        func_0036B6E0(object, 0);
        func_0036B1E0(object, 0);
        func_0036B360(object, 1);
        object->unk98->func_slot58()->func_0044B110(20, 0, 0, 0, 0.0f);
        object->unk9c->func_slot58()->func_0044B110(19, 0, 0, 0, 0.0f);
        object->unkb4->func_slot58()->func_0044B110(18, 0, 0, 0, 0.0f);
        object->unk1f4 = 360;
        break;
    case 3:
        func_0036BA10(object, 0);
        func_0036B6E0(object, 0);
        func_0036B360(object, 0);
        func_0036B1E0(object, 1);
        item_creation_save_workshop_lines(object);
        break;
    case 4:
    default:
        break;
    }
    object->unk46 = object->unk47;
}

void ItemCreationSelectedDisplayState::func_0036BF30(s32 index, bool enabled)
{
    ItemCreationAllocationRecord* records[100];
    unk148[index] = enabled;
    unk1b1[index] = 0;
    if (unk1b4[index] == 0)
    {
        unk1b1[index] = 1;
        unk148[index] = 0;
    }
    if (enabled && unk1b4[index] != 0)
    {
        s32 category = 0;
        if (unk1c3[index] >= 2)
        {
            switch (unk1c0[index])
            {
                case 1:
                    category = 20;
                    break;
                case 2:
                    category = 23;
                    break;
                case 3:
                    category = 36;
                    break;
                case 4:
                    category = 37;
                    break;
                case 5:
                    category = 33;
                    break;
                case 6:
                    category = 30;
                    break;
                case 7:
                    category = 31;
                    break;
                case 8:
                    category = 32;
                    break;
            }
            if (func_0040CF90(D_001B64F8, records, (u16)category) != 0)
            {
                func_0040C9F0(D_001B64F8, func_0040D890(records[0]));
            }
        }
    }
    unk188[index][0] = 0;
    unk188[index][1] = 0;
    unk188[index][2] = 0;
    unk191[index][0] = 1;
    unk191[index][1] = 1;
    unk191[index][2] = 1;
}

/** @brief Return a random integer in a range. @param lower Lower bound. @param upper Upper bound. @return Random value. */
extern "C" s32 func_10CC40(s32 lower, s32 upper);

void func_0036C080(ItemCreationSelectedDisplayState* object, s32 index, u32 value)
{
    object->unk148[index] = value;
    if (value != 0)
    {
        if (object->unk1b4[index] != 0)
        {
            object->unk164[index] = 360.0f * (1.0f + object->unk1b4[index]->unk7c / 100.0f);
        }
        else
        {
            object->unk164[index] = 360.0f;
        }
        object->unk170[index] = func_10CC40(1, 5);
        object->unk14c[index] = object->unk164[index];
        object->unk158[index] = 100.0f;
        object->unk1d4[index] = 0;
        object->unk17c[index] = 0.0f;
        if (object->unk1b4[index] == 0)
        {
            object->unk1b1[index] = 1;
        }
    }
    else
    {
        object->unk158[index] = 0.0f;
    }
    if (value != 0)
    {
        object->unk19a = 1;
    }
}

/**
 * @brief Choose an eligible assigned inventor and schedule the corresponding display resources.
 * @param object Selection state containing development lines and assigned inventor codes.
 */
void item_creation_schedule_inventor_resource(ItemCreationSelectedDisplayState* object)
{
    if (object->unk1b1[0] == 0 || object->unk1b1[1] == 0 || object->unk1b1[2] == 0)
    {
        s32 slot_index;
        s32 line_index;
        s32 inventor_option_code;
        for (;;)
        {
            slot_index = func_0010CF80() % 9;
            line_index = slot_index / 3;
            if (object->unk1b4[line_index] == 0)
            {
                continue;
            }
            if (object->unk1b1[line_index] != 0)
            {
                continue;
            }
            if (func_002FB510(object->unk1b4[line_index], slot_index % 3) == 3)
            {
                continue;
            }
            inventor_option_code = object->unk68[slot_index];
            if (inventor_option_code > 0)
            {
                break;
            }
        }
        if (inventor_option_code >= 32 && inventor_option_code < 60)
        {
            s32 resource_key = inventor_option_code + 596;
            if (object->unk19c != 0)
            {
                func_002FD940(object->unk19c);
                object->unk1a8 = 1;
            }
            object->unk1a0 = resource_key;
            object->unk1a4 = 0;
        }
        else
        {
            s32 resource_key = (inventor_option_code - 60) * 9 + 538;
            s32 skill_id = object->unk1c0[line_index];
            if (object->unk19c != 0)
            {
                func_002FD940(object->unk19c);
                object->unk1a8 = 1;
            }
            object->unk1a0 = resource_key;
            if (skill_id != 0)
            {
                object->unk1a4 = resource_key + skill_id;
            }
            else
            {
                object->unk1a4 = 0;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0036C340);

s32 func_0036CD60(void* object)
{
    return -1;
}

/**
 * @brief Release the record selection and detach the selected-display state.
 * @param object Selection state.
 */
extern "C" void func_0036CD70(ItemCreationSelectedDisplayState* object)
{
    if (object->unk48 != 0)
    {
        release_owned(object->unk48);
    }
    if (object->unk34 != 0)
    {
        func_00465430(D_001B657C, reinterpret_cast<s32>(object->unk34));
    }
    func_004D65C0(object);
    object->func_001DD7B0();
    object->unk44 = 5;
}


/**
 * @brief Allocate and configure the windows for the selected display mode.
 * @return Always one.
 */
s32 ItemCreationSelectedDisplayState::func_00263CD0()
{
    unk98 = new (0) ItemCreationBackground;
    unk9c = new (0) ItemCreationStatusBanner;
    unk98->func_slotf4(unk34);
    FieldClass153E30::func_00263FD0(unk98);
    unk98->func_slot40(0);
    unk9c->func_slotf4(unk34);
    FieldClass153E30::func_00263FD0(unk9c);
    unk24 = unk9c;
    unk9c->func_slot40(unk98);
    if (unk45 == 0)
    {
        unka0 = new (0) ItemCreationMainMenu(this);
        unka4 = new (0) WorkshopNameWindow(this);
        unka8 = new (0) WorkshopFacilitiesWindow;
        unkac = new (0) WorkshopExpansionWindow;
        unkb0 = new (0) DevelopmentTeamsWindow;
        unkb4 = new (0) ItemCreationControlHelp;
        unkb8 = new (0) AvailableInventorGrid;
        unkbc = new (0) AssignedInventorGrid;
        unkc0 = new (0) InventorInformationWindow;
        unkc4 = new (0) CreationSkillWindow(this);
        unkc8 = new (0) InventionPolicyWindow(this);
        unkcc = new (0) StartInventingDialog(this);
        unkd0 = new (0) PlanItemGroupWindow(this);
        unkd4 = new (0) InventoryItemTypeList(this);
        unkd8 = new (0) ItemCreationClass186770;
        unkdc = new (0) ItemSubmissionDialog;
        unke0 = new (0) ItemDetailsWindow(this);
        unke4 = new (0) DevelopmentControlPanel;
        unke8 = new (0) InventorStatusWindow;
        unkec = new (0) AbortDevelopmentDialog;
        unkf0 = new (0) InadequateLineDialog(this);
        unkf4 = new (0) InventorTransferWindow;
        unkf8 = new (0) SourceInventorStrip;
        unkfc = new (0) DestinationInventorStrip;
        unka0->func_slot48(unkac);
        unka0->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unka0);
        unka4->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unka4);
        unka8->unka8 = this;
        unka8->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unka8);
        unkac->unka8 = this;
        unkac->workshop_id = workshop_id;
        unkac->func_slot40(unka0);
        unkac->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkac);
        unkb0->unk120 = this;
        unkb0->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkb0);
        unkb4->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkb4);
        unkb8->unka8 = this;
        unkb8->func_slot40(unkbc);
        unkb8->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkb8);
        unkbc->unka8 = this;
        unkbc->func_slot40(unkb8);
        unkbc->unk1e8 = unkc4;
        unkbc->unk1ec = unkc8;
        unkbc->unk214 = unkcc;
        unkbc->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkbc);
        unkc0->unka8 = this;
        unkc0->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkc0);
        CreationSkillWindow* category_window;
        InventoryItemTypeList* category_list;
        category_list = unkd4;
        category_window = unkc4;
        category_window->unke0 = unkd0;
        category_window->unke4 = category_list;
        unkc4->func_slot40(unkbc);
        unkc4->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkc4);
        InventionPolicyWindow* mode_window;
        InventoryItemTypeList* mode_list;
        mode_list = unkd4;
        mode_window = unkc8;
        mode_window->unkdc = unkd0;
        mode_window->unke0 = mode_list;
        unkc8->func_slot40(unkbc);
        unkc8->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkc8);
        unkcc->func_slot40(unkbc);
        unkcc->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkcc);
        unkd0->func_slot40(unkbc);
        unkd0->unk150 = unkd4;
        unkd0->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkd0);
        unkd4->func_slot40(unkd0);
        unkd4->unk21c = unkd0;
        unkd4->func_slot104(unk34);
        FieldClass153E30::func_00263FD0(unkd4);
        unkd8->unka8 = this;
        unkd8->func_slot40(unkb4);
        unkd8->unk110 = unkdc;
        unkd8->unk114 = unke0;
        unkd8->unk118 = unkf0;
        unkd8->unk1c0 = unkec;
        unkd8->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkd8);
        unkdc->unka8 = this;
        unkdc->func_slot40(unkd8);
        unkdc->func_slot48(unke0);
        unkdc->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkdc);
        unke0->unka8 = this;
        unke0->func_slot40(unkd8);
        unke0->func_slot48(unkb4);
        unke0->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unke0);
        unke4->unka8 = this;
        unke4->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unke4);
        unke8->unka8 = this;
        unke8->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unke8);
        unkec->unka8 = this;
        unkec->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkec);
        unkf0->func_slot40(unkd8);
        unkf0->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkf0);
        unkf4->selection_state = this;
        unkf4->func_slot40(unkf8);
        unkf4->func_slot48(unkfc);
        unkf4->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkf4);
        unkf8->unkc4 = this;
        unkf8->unka8 = 1;
        unkf8->func_slot40(unkf4);
        unkf8->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkf8);
        unkfc->unkc4 = this;
        unkfc->unka8 = 2;
        unkfc->func_slot40(unkf4);
        unkfc->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkfc);
        item_creation_activate_window_group(this, 0);
        unk20 = unka0;
    }
    else if (unk45 == 1)
    {
        unk114 = new (0) InventorTalentsWindow;
        unk104 = new (0) WorkshopInventorStrip;
        unk108 = new (0) PendingInventorSummary;
        unk10c = new (0) AssignInventorDialog;
        unk110 = new (0) WorkshopFullDialog;
        unk100 = new (0) WorkshopSelectionWindow;
        unk114->selection_state = this;
        unk114->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unk114);
        unk104->selection_state = this;
        unk104->func_slotf4(unk34);
        unk104->func_slot48(unk114);
        unk104->func_slot40(unk100);
        FieldClass153E30::func_00263FD0(unk104);
        unk108->unka8 = this;
        unk108->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unk108);
        unk10c->unkc4 = unk108->unkb8;
        unk10c->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unk10c);
        unk10c->func_slot20(0);
        unk110->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unk110);
        unk110->func_slot20(0);
        unk100->func_slot40(unk10c);
        unk100->func_slot48(unk104);
        unk100->workshop_full_dialog = unk110;
        unk100->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unk100);
        unk10c->func_slot40(unk100);
        unk110->func_slot40(unk100);
        unk9c->func_slot60(0x32CF);
        item_creation_activate_window_group(this, 4);
        unk20 = unk100;
    }
    unk38 = 1;
    return 1;
}

/** Loaded resource buffer; its 128-byte aligned header records the payload size. */
struct ItemCreationBufferHeader
{
    u8 unk00[0x40];
    s32 unk40;
};

// Resident and Lib interfaces linked under this overlay's short names.
extern "C"
{
    void* func_100C90(void);
    void* func_113710(void* heap, s32 size);
    void func_1134C0(void* memory);
    void* func_100C80(void* heap);
    void* func_4656B0(FieldRuntime* runtime, void* data);
}

/**
 * @brief Align a loaded buffer to its header.
 * @param buffer Loaded buffer.
 * @return Header at the next 128-byte boundary.
 */
static inline ItemCreationBufferHeader* buffer_header(void* buffer)
{
    return reinterpret_cast<ItemCreationBufferHeader*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7FU);
}

/**
 * @brief Load the completed buffer into the Field runtime and finish setup.
 * @param buffer Completed buffer, or null.
 * @return Zero without a buffer, otherwise the setup result.
 */
s32 ItemCreationSelectedDisplayState::func_001E1820(void* buffer)
{
    if (!buffer)
    {
        return 0;
    }
    s32 size = buffer_header(buffer)->unk40 + 0x80;
    void* previous_heap = func_100C90();
    void* heap = D_001B6430->context->unk70;
    void* memory = func_113710(heap, size);
    if (memory)
    {
        func_1134C0(memory);
        func_100C80(heap);
    }
    unk34 = func_4656B0(D_001B657C, buffer_header(buffer));
    func_100C80(previous_heap);
    FieldRuntime* runtime = D_001B657C;
    runtime->unk514 = unk34;
    runtime->unk518 = 0xC351;
    return func_00263CD0();
}

/**
 * @brief Save workshop lines and append the selection state to the resident queue.
 * @param object Selection state to save and enqueue.
 */
void item_creation_save_and_enqueue_selection(ItemCreationSelectedDisplayState* object)
{
    item_creation_save_workshop_lines(object);
    func_0011ED90(D_001B65F4, object);
}

/** @brief Find a saved workshop. @param index Workshop ID. @return Record, or null outside IDs one through twelve. */
static inline ItemCreationWorkshopRecord* saved_workshop_record(u8 index)
{
    ItemCreationRuntimeData* records = D_001B64F8;
    if (workshop_id_valid(index))
    {
        return &records->workshops[index - 1];
    }
    return 0;
}
/** @brief Find a saved inventor. @param index Inventor ID. @return Record, or null outside IDs one through thirty-eight. */
static inline ItemCreationInventorRecord* saved_inventor_record(u8 index)
{
    ItemCreationRuntimeData* records = D_001B64F8;
    if (saved_inventor_id_valid(index))
    {
        return &records->inventors[index - 1];
    }
    return 0;
}

/**
 * @brief Prepare record selection and count available option records.
 * @return One on success, zero when required runtime data is missing.
 */
u8 ItemCreationSelectedDisplayState::func_00264110()
{
    unk40 = reinterpret_cast<ItemCreationOptionTable*>(func_101440(func_101290(func_10D8E0()), 4));
    if (!unk40)
    {
        return 0;
    }
    unk48 = new(0) FieldRecordSelection;
    if (!unk48)
    {
        return 0;
    }
    if (!(func_0028E3D0(unk48) & 0xFF))
    {
        return 0;
    }
    if (unk45 == 0)
    {
        workshop_id = item_creation_current_workshop_id(this);
    }
    if (unk45 == 0)
    {
        unk12e[0] = workshop_id;
        workshop = saved_workshop_record(unk12e[0]);
        unk57 = workshop->line_count;
    }
    unk1f0 = reinterpret_cast<RuntimeStateSection58*>(D_001B6430->context->unk58)->unk1b4;
    item_creation_restore_workshop_assignments(this);
    item_creation_restore_workshop_skill_flags(this);
    func_00369EB0(this);
    for (s32 index = 1; index < 28; index++)
    {
        ItemCreationInventorRecord* record = saved_inventor_record(index);
        if (record && record->contract_status == 2)
        {
            unk19b++;
        }
    }
    return 1;
}


/** @brief Release the assigned target storage and selection-state base. */
ItemCreationSelectedDisplayState::~ItemCreationSelectedDisplayState()
{
    for (s32 index = 0; index < 3; index++)
    {
        operator delete(unk1b4[index]);
        unk1b4[index] = 0;
    }
}

/** @brief Initialize the selected-display windows and resource state. */
ItemCreationSelectedDisplayState::ItemCreationSelectedDisplayState()
{
    unk34 = 0;
    unk38 = 0;
    unk3c = 0;
    unk3c = D_001B643C->unk20;
    unk40 = 0;
    unk44 = 0;
    unk45 = 0;
    unk47 = 0;
    unk46 = 0;
    unk45 = D_001B643C->unk10->unk1a;
    unk48 = 0;
    unk4c = 0;
    workshop_id = 0;
    unk57 = 0;
    unk58 = 0;
    unk59 = 0;
    unk140 = 130.0f;
    for (s32 index = 0; index < 9; index++)
    {
        workshop_skill_enabled[index] = 0;
    }
    for (s32 index = 0; index < 14; index++)
    {
        unk5a[index] = 0;
    }
    for (s32 index = 0; index < 9; index++)
    {
        unk68[index] = 0;
    }
    for (s32 index = 0; index < 6; index++)
    {
        unk71[index] = 0;
        unk77[index] = 0;
    }
    for (s32 index = 0; index < 12; index++)
    {
        workshop_facility_masks[index] = 0;
    }
    unk1fa = 0;
    unk1f8 = 0;
    for (s32 index = 0; index < 3; index++)
    {
        for (s32 column = 0; column < 2; column++)
        {
            unk1e2[index][column] = 0;
        }
    }
    unk98 = 0;
    unk9c = 0;
    unka0 = 0;
    unka4 = 0;
    unka8 = 0;
    unkac = 0;
    unkb0 = 0;
    unkb4 = 0;
    unkb8 = 0;
    unkbc = 0;
    unkc0 = 0;
    unkc4 = 0;
    unkc8 = 0;
    unkcc = 0;
    unkd0 = 0;
    unkd4 = 0;
    unkd8 = 0;
    unkdc = 0;
    unke0 = 0;
    unke4 = 0;
    unke8 = 0;
    unkec = 0;
    unkf0 = 0;
    unkf4 = 0;
    unkf8 = 0;
    unkfc = 0;
    unk100 = 0;
    unk104 = 0;
    unk108 = 0;
    unk10c = 0;
    unk110 = 0;
    unk114 = 0;
    unk118 = 0;
    unk11c = 0;
    unk120 = 0;
    unk124 = -1;
    unk126 = -1;
    unk128 = 0;
    unk129 = 0;
    unk12a = 0;
    unk12b = 0;
    unk12c = 0;
    unk12d = 0;
    unk12e[0] = 0;
    facility_mask = 0;
    workshop = 0;
    unk138 = 0;
    for (s32 index = 0; index < 3; index++)
    {
        unk14c[index] = 0.0f;
        unk158[index] = 0.0f;
        unk164[index] = 0.0f;
        unk170[index] = 0.0f;
        unk17c[index] = 0.0f;
        unk188[index][0] = 0;
        unk188[index][1] = 0;
        unk188[index][2] = 0;
        unk191[index][0] = 1;
        unk191[index][1] = 1;
        unk191[index][2] = 1;
    }
    unk19a = 0;
    unk19b = 0;
    unk19c = 0;
    unk1ac = 0;
    unk1b0 = 0xFF;
    unk19c = 0;
    unk1a8 = 0;
    unk1a4 = 0;
    unk1a0 = 0;
    unk1b1[0] = 0;
    unk1b1[1] = 0;
    unk1b1[2] = 0;
    for (s32 index = 0; index < 3; index++)
    {
        unk1b4[index] = 0;
        unk1b1[index] = 0;
        unk1c0[index] = 0;
        unk1c3[index] = 0;
        unk1c8[index] = 0;
        unk1d4[index] = 0;
    }
}


s32 func_0036E540(void* object)
{
    return 3;
}

void func_0036E550(void* object)
{
}

void func_0036E560(void* object)
{
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param value Source vector.
 */
void LibClass171EF0::func_003EF770(const LibVector4* value)
{
    unk50 = 1;
    unk20.packed = value->packed;
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param value Source vector.
 */
void LibClass171EF0::func_003EF780(const LibVector4* value)
{
    unk50 = 1;
    unk20.packed = value->packed;
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param x Component value.
 * @param y Component value.
 * @param z Component value.
 */
void LibClass171EF0::func_003EF790(float x, float y, float z)
{
    unk50 = 1;
    unk20.components[0] = x;
    unk20.components[1] = y;
    unk20.components[2] = z;
    unk20.components[3] = 1.0f;
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param x Component value.
 * @param y Component value.
 * @param z Component value.
 * @param w Component value.
 */
void LibClass171EF0::func_003EEED0(float x, float y, float z, float w)
{
    unk50 = 1;
    unk30.components[0] = x;
    unk30.components[1] = y;
    unk30.components[2] = z;
    unk30.components[3] = w;
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param value Source vector.
 */
void LibClass171EF0::func_003EEEF0(const LibVector4* value)
{
    unk50 = 1;
    unk30.packed = value->packed;
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param value Source vector.
 */
void LibClass171EF0::func_003EEF10(const LibVector4* value)
{
    unk50 = 1;
    unk30.packed = value->packed;
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param value Source vector.
 */
void LibClass171EF0::func_003EEF30(const LibVector4* value)
{
    unk50 = 1;
    func_004CE4C0(unk30.components, value->components);
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param value Source vector.
 */
void LibClass171EF0::func_003EEF60(const LibVector4* value)
{
    unk50 = 1;
    func_004CE4C0(unk30.components, value->components);
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param x Component value.
 * @param y Component value.
 * @param z Component value.
 */
void LibClass171EF0::func_003EEF90(float x, float y, float z)
{
    float value[4];
    unk50 = 1;
    value[0] = x;
    value[1] = y;
    value[2] = z;
    value[3] = 1.0f;
    func_004CE4C0(unk30.components, value);
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param value Source vector.
 */
void LibClass171EF0::func_003EEFD0(const LibVector4* value)
{
    unk50 = 1;
    unk40.packed = value->packed;
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param value Source vector.
 */
void LibClass171EF0::func_003EEFF0(const LibVector4* value)
{
    unk50 = 1;
    unk40.packed = value->packed;
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param x Component value.
 * @param y Component value.
 * @param z Component value.
 */
void LibClass171EF0::func_003EF010(float x, float y, float z)
{
    unk50 = 1;
    unk40.components[0] = x;
    unk40.components[1] = y;
    unk40.components[2] = z;
}

/** @brief Return the default output status. @param output Unused output object. @return Zero. */
s32 LibClass178A90::func_003EEE20(void* output)
{
    return 0;
}

/** @brief Test whether a value is negative. @param value Value to test. @param mode Unused mode. @return One if negative, otherwise zero. */
s32 LibClass178A90::func_003EEE30(float value, float mode)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

/** @brief Return the default transform vector. @return Resident vector pointer. */
const LibVector4* LibClass178A90::func_003EFAA0()
{
    return D_50CD30;
}

/** @brief Return the default transform receiver. @return Null. */
LibClass178A90* LibClass178A90::func_003EEE50()
{
    return 0;
}

/** @brief Run the default transform detach hook. */
void LibClass178A90::func_003EEE60()
{
}

void func_0036E790(void* object)
{
}

void func_0036E7A0(void* object)
{
}

float func_0036E7B0(void* object)
{
    return 0.0f;
}

/**
 * @brief Run the default container state hook.
 * @param first Unused first argument.
 * @param second Unused second argument.
 * @param third Unused third argument.
 */
void LibObject178660::func_00412C40(u32 first, u32 second, u32 third)
{
}

/** @brief Restore the stored transform state byte. */
void LibClass174610::func_003F4420()
{
    unk60 = unka8;
}

/** @brief Run the default notification hook. @param value Unused argument. */
void LibClass171FF0::func_003EFA90(u32 value)
{
}

/**
 * @brief Return the default row float setting.
 * @param source Owning row collection, unused by the base implementation.
 * @return Zero.
 */
float ItemCreationClass185030::func_slot18(LibClass1721F0* source)
{
    return 0.0f;
}

/** @brief Perform the default movement-completion callback. */
void ItemCreationClass185050::func_slot0c()
{
}

/** @brief Perform the default window callback at slot 0x5C. */
void FieldClass15AE70::func_slot5c()
{
}

/** @brief Perform the default window callback at slot 0x70. */
void FieldClass15AE70::func_slot70()
{
}

/** @brief Perform the default window callback at slot 0x74. */
void FieldClass15AE70::func_slot74()
{
}

/** @brief Perform the default window action. @return Zero. */
s32 FieldClass15AE70::func_slotb0()
{
    return 0;
}

/** @brief Perform the default alternate window action. @return Zero. */
s32 FieldClass15AE70::func_slotb4()
{
    return 0;
}

/** @brief Destroy the four embedded text widgets and their row interface. */
InventorStatusRow::~InventorStatusRow()
{
}

/** @brief Destroy the popup Field window base. */
MissingMaterialsDialog::~MissingMaterialsDialog()
{
}

/**
 * @brief Destroy the popup through its Field window base.
 */
InsufficientFolDialog::~InsufficientFolDialog()
{
}

/**
 * @brief Destroy the result window through its Field base.
 */
DevelopmentCompleteDialog::~DevelopmentCompleteDialog()
{
}

/**
 * @brief Destroy the result prompt window and release its Field base.
 */
LineFailureDialog::~LineFailureDialog()
{
}

/**
 * @brief Destroy the selected item prompt window through its Field base.
 */
InventionSuccessDialog::~InventionSuccessDialog()
{
}

/** @brief Release the embedded list and destroy the Field window. */
InventoryItemTypeList::~InventoryItemTypeList()
{
}

/** @brief Destroy the selection window through its Field window base. */
WorkshopExpansionWindow::~WorkshopExpansionWindow()
{
}

/** @brief Read the selected-display state flag. @return Stored state flag. */
u8 ItemCreationSelectedDisplayState::func_00261D20()
{
    return unk38;
}

/** @brief Report the selected-display object kind. @return Object kind 4. */
s32 ItemCreationSelectedDisplayState::func_001DF3D0()
{
    return 4;
}

/** @brief Store the alternate associated object. @param value Object to store. */
void ItemCreationSelectedDisplayState::func_00263C80(void* value)
{
    unk24 = value;
}

/** @brief Store the signed state byte. @param value State byte to store. */
void ItemCreationSelectedDisplayState::func_00263CA0(s8 value)
{
    unk28 = value;
}

/** @brief Read the signed state byte. @return Stored state byte. */
s8 ItemCreationSelectedDisplayState::func_00263CB0()
{
    return unk28;
}

s32 func_0036EC10(void* object)
{
    return 0;
}

s32 func_0036EC20(void* object)
{
    return 0;
}

void func_0036EC30(void* object)
{
}

s32 func_0036EC40(void* object)
{
    return 0;
}

void func_0036EC50(void* object)
{
}

void func_0036EC60(void* object)
{
}

void func_0036EC70(void* object)
{
}

s32 func_0036EC80(void* object)
{
    return 0;
}

s32 func_0036EC90(void* object)
{
    return 0;
}

s32 func_0036ECA0(void* object)
{
    return 0;
}

/** @brief Allocate the sentinel node and initialize the list count. */
ItemCreationClass187A60::ItemCreationClass187A60()
{
    unk00 = new (0) ItemCreationListNode;
    if (unk00 == 0)
    {
        throw;
    }
    unk00->unk04 = 0;
    unk04 = 0;
}

/** @brief Release the list nodes and its sentinel. */
ItemCreationClass187A60::~ItemCreationClass187A60()
{
    func_0036EEF0(this);
    if (unk00 != 0)
    {
        delete unk00;
        unk00 = 0;
    }
}

/**
 * @brief Append a record to the sentinel-based list.
 * @param object List containing a valid sentinel.
 * @param record Record stored by the new node.
 */
void func_0036EDB0(ItemCreationCountedList* object, void* record)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        node->unk00 = record;
        node->unk04 = 0;
        tail = object->unk00;
        while (tail->unk04)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

void func_0036EE40(ItemCreationCountedList* object, ItemCreationListNode* after, void* const* record)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    node->unk00 = *record;
    if (after != 0)
    {
        node->unk04 = after->unk04;
        after->unk04 = node;
    }
    else
    {
        ItemCreationListNode* tail = object->unk00;
        ItemCreationListNode* next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        node->unk04 = 0;
    }
    object->unk04++;
}

/**
 * @brief Release the nodes after the list sentinel and clear the count.
 * @param object Counted list whose linked nodes are owned allocations.
 */
extern "C" void func_0036EEF0(ItemCreationCountedList* object)
{
    ItemCreationListNode* node = object->unk00->unk04;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        ItemCreationListNode* next = node->unk04;
        release_owned(node);
        node = next;
    }
    object->unk00->unk04 = 0;
    object->unk04 = 0;
}

/**
 * @brief Find the data node at a list index.
 * @param object List containing a valid sentinel.
 * @param index Data-node index; nonpositive values select the first node.
 * @return Selected node, or null when the list ends first.
 */
ItemCreationListNode* func_0036EF70(ItemCreationCountedList* object, s32 index)
{
    ItemCreationListNode* node = object->unk00->unk04;
    for (s32 current = 0; current < index; current++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->unk04;
    }
    return node;
}

void func_0036EFB0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

void func_0036F040(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

void func_0036F0D0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

/**
 * @brief Find the data node at a list index.
 * @param object List containing a valid sentinel.
 * @param index Data-node index; nonpositive values select the first node.
 * @return Selected node, or null when the list ends first.
 */
ItemCreationListNode* func_0036F160(ItemCreationCountedList* object, s32 index)
{
    ItemCreationListNode* node = object->unk00->unk04;
    for (s32 current = 0; current < index; current++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->unk04;
    }
    return node;
}

void func_0036F1A0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}

ItemCreationListNode* func_0036F230(FieldCountedList* object, s32 index)
{
    ItemCreationListNode* node = object->unk00;
    s32 current = 0;
    node = node->unk04;
    for (current = 0; current < index; current++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->unk04;
    }
    return node;
}

void func_0036F270(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = value;
        node->unk04 = 0;
        tail = object->unk00;
        next = tail->unk04;
        while (next != 0)
        {
            tail = next;
            next = next->unk04;
        }
        tail->unk04 = node;
        object->unk04++;
    }
}


#include "overlays/citemcreation/item_display_inlines.h"
