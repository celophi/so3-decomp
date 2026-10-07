#include "main/resident_0010A0E0.h"
#include "main/resident_data.h"
#include "include_asm.h"
#include "overlays/lib/text_004BD360.h"
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
    ITEM_CREATION_CATEGORY_LABEL_BASE = 0x3458
};

/** Category bits in saved records, ordered by the category label messages. */
enum ItemCreationCategoryFlag
{
    ITEM_CREATION_CATEGORY_FLAG_COOK = 0x1,
    ITEM_CREATION_CATEGORY_FLAG_ALCH = 0x2,
    ITEM_CREATION_CATEGORY_FLAG_CRFT = 0x4,
    ITEM_CREATION_CATEGORY_FLAG_CMPD = 0x8,
    ITEM_CREATION_CATEGORY_FLAG_SMTH = 0x10,
    ITEM_CREATION_CATEGORY_FLAG_WRIT = 0x20,
    ITEM_CREATION_CATEGORY_FLAG_ENG = 0x40,
    ITEM_CREATION_CATEGORY_FLAG_SYTH = 0x80
};

/** Partial view of an optional display whose concrete type is unknown. */
struct ItemCreationVisibility3F
{
    u8 unk00[0x3F];
    u8 unk3f;
};

/** Resident resource widget with its two resource indices at CC and D0. */
class ItemCreationClass174C40 : public ItemCreationClass175110
{
public:
    ItemCreationClass174C40() {}
    virtual ~ItemCreationClass174C40();
    virtual void func_00413D20();
    s32 unkcc;
    s32 unkd0;
    void set_scale(float x, float y)
    {
        unk50.unk34 = y;
        unk50.unk30 = x;
        unk3c = 1;
    }
};
extern "C" s32 func_4530E0(ItemCreationClass174C40*, s32, float, float);

extern "C" LibWidgetColors4C5590 D_0036F600;

/** Resident seven-widget aggregate with its true callback pointer at 0x31C. */
class LibClass1723F0
{
public:
    u8 unk00[0x2F8];
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
/** Resident 0x410-byte container whose aggregate is its genuine second base. */
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
/** 0x4C0-byte option container with the recovered resident ancestry. */
class ItemCreationClass185F60 : public LibClass1721F0
{
public:
    /** @brief Initialize the option container and clear its own state. */
    ItemCreationClass185F60();
    /** @brief Destroy the option container and its collection base. */
    virtual ~ItemCreationClass185F60();
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
 * @brief Initialize the transfer display storage and position.
 * @param object Transfer display.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @return Initialization status.
 */
extern "C" s32 func_467360(void* object, float x, float y);

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


/** Item code widget with MAIN vtable at 0x172410. */
struct LibObject172410 : public LibClass174EF0
{
    /** @brief Initialize the item code widget and select kind 15. */
    LibObject172410()
    {
        unk38 = 15;
    }
    /** @brief Destroy the item code widget. */
    virtual ~LibObject172410();
    /** @brief Draw the code widget. */
    virtual void func_00462310();
    u16 unkfc;
    u8 unkfe;
    u8 unkff;
};
/** Detail code widget with MAIN vtable at 0x172440. */
struct LibObject172440 : public LibClass174EF0
{
    /** @brief Initialize the detail code widget and select kind 16. */
    LibObject172440()
    {
        unk38 = 16;
    }
    /** @brief Destroy the detail code widget. */
    virtual ~LibObject172440();
    /** @brief Draw the code widget. */
    virtual void func_00462310();
    u16 unkfc;
    u8 unkfe;
    u8 unkff;
};

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

/** Twelve-byte category entry containing its list head and catalog index. */
struct ItemCreationCategoryRecord
{
    s16 unk00;
    u16 unk02;
    u8 unk04[4];
    u8 unk08;
    u8 unk09[3];
};

/** Thirty-two-byte catalog entry containing the three mode-selection fields. */
struct ItemCreationCategoryDefinition
{
    u8 unk00[0xB];
    u8 unk0b_low : 4;
    u8 unk0b_mode : 3;
    u8 unk0b_high : 1;
    u8 unk0c[4];
    u32 unk10_low : 10;
    u32 unk10_code : 10;
    u32 unk10_high : 12;
    u8 unk14[7];
    u8 unk1b_low : 6;
    u8 unk1b_flag : 1;
    u8 unk1b_high : 1;
    u8 unk1c[2];
    u8 unk1e_low : 1;
    u8 unk1e_value : 3;
    u8 unk1e_high : 4;
    u8 unk1f;
};


enum
{
    ITEM_CREATION_COLOR_DIM = 0x505050,
    ITEM_CREATION_COLOR_BRIGHT = 0x808080,
    ITEM_CREATION_COLOR_SELECTED = 0x288080,
    ITEM_CREATION_COLOR_ASSIGNED = 0x1E8CFF
};

typedef struct ItemCreationColorRecord
{
    u8 unk00[0x30];
    u16 unk30;
    u8 unk32[2];
} ItemCreationColorRecord;

/** Partial twelve-byte runtime option record. */
typedef struct ItemCreationRuntimeOptionRecord
{
    u8 unk00[6];
    u8 unk06;
    u8 unk07;
    u8 unk08;
    u8 unk09;
    u8 unk0a;
    u8 unk0b;
} ItemCreationRuntimeOptionRecord;

typedef struct ItemCreationColorRecordState
{
    ItemCreationAllocationRecord records[3000];
    u8 unkbb80[0x2EE0];
    ItemCreationCategoryRecord categories[750];
    ItemCreationRuntimeOptionRecord unk10d88[38];
    ItemCreationColorRecord unk10f50[12];
} ItemCreationColorRecordState;

/** Partial holder of the current Field callback receiver. */
typedef struct ItemCreationWindowCallbacks
{
    u8 unk00[0x14];
    FieldClass153E30* unk14;
    u8 unk18[2];
    u16 unk1a;
} ItemCreationWindowCallbacks;

typedef struct ItemCreationRuntime643C
{
    u8 unk00[0x10];
    ItemCreationWindowCallbacks* unk10;
    u8 unk14[0xC];
    FieldBufferSlots* unk20;
} ItemCreationRuntime643C;

/** Partial nested object containing the byte set when restoring its parent. */
struct ItemCreationSelectionRestoreMarker
{
    u8 unk00[0xAD];
    u8 unkad;
};

/** Partial associated window with its restore marker. */
struct ItemCreationPopupReturnParent
{
    u8 unk00[0xB4];
    FieldObject23CEA0* unkb4;
};

/** Partial parent context returned by the selection window's associated-object hook. */
struct ItemCreationSelectionRestoreParent
{
    u8 unk00[0xB4];
    ItemCreationSelectionRestoreMarker* unkb4;
};

struct ItemCreationOptionDisplay
{
    u8 unk00[0xA8];
    u8 unka8;
    u8 unka9;
    u8 unkaa[2];
    ItemCreationOptionResourceDisplay* unkac[6];
    ItemCreationSelectedDisplayState* unkc4;
    FieldObject23CEA0* unkc8;
};

/** Partial owner linking an option list, index display, and transfer display. */
struct ItemCreationOptionTransferOwner
{
    u8 unk00[0xA8];
    u8 unka8;
    u8 unka9[0x1B];
    ItemCreationSelectedDisplayState* unkc4;
    FieldObject23CEA0* unkc8;
    ItemCreationFlagResetOwner* unkcc;
};

/** Partial category-one target selected by native MAIN15BB30. */
class FieldClass15BB30 : public ItemCreationClass184EF0
{
public:
    u8 unk90[0x320];
    s32 unk3b0;
    u8 unk3b4[0x14];
    u16 unk3c8;
};

class FieldClass15BB50 : public ItemCreationClass184EF0
{
public:
    u8 unk90[4];
    s16 unk94;
    u8 unk96[0x22];
};
class FieldClass15BB70 : public ItemCreationClass184EF0
{
public:
    u8 unk90[0x50];
    s16 unke0;
    u8 unke2[0x26];
};
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
extern "C" ItemCreationCategoryDefinition* D_001B64F0;

/** @brief Initialize the option container. @param object Allocated container. @return Initialized container. */
extern "C" ItemCreationClass185F60* func_00352340(ItemCreationClass185F60* object);
/** @brief Set up the option rows. @param object Option container. @param associated Associated source. @param count Option count. @return Setup status. */
extern "C" s32 func_00352020(ItemCreationClass185F60* object, void* associated, s32 count);

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

extern "C" void func_00351510(ItemCreationClass185E60* object, u8 mode);
extern "C" void func_003565A0(ItemCreationClass186770* object, u16 direction);

// These external interfaces are scoped here because their owning code is in other overlays.
extern ItemCreationColorRecordState* D_001B64F8;
extern ItemCreationRuntime643C* D_001B643C;
extern "C" void func_466E40(void* point, float x, float y, float scale);
extern "C" s32 func_002CFE40(void* object, s16 index);
extern "C" u16 func_23B3A0(FieldState23B3A0* object);
extern "C" u32 func_23B3B0(FieldState23B3A0* object, u16 direction);

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
static inline void set_transfer_position(ItemCreationTransferDisplay* display, float x, float y);

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
static inline void set_option_list_index(ItemCreationFlagResetOwner* object, u8 list, u8 value);

/**
 * @brief Offset one displayed coordinate from its origin.
 * @param origin Base coordinate.
 * @param offset Coordinate displacement.
 * @return Coordinate after applying the displacement.
 */
static inline float shifted_position(float origin, float offset);

/**
 * @brief Test whether the selector's control byte is clear.
 * @param object Selector state to test.
 * @return One when the control byte is zero, or zero otherwise.
 */
static inline bool selector_inactive(FieldState23B3A0* object);

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

static inline bool selector_inactive(FieldState23B3A0* object)
{
    if (object->unk75)
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

u8 func_003486B0(void* object)
{
    return *(u8*)((u8*)object + 0xD);
}

void func_003486C0(void* object, u8 value)
{
    *(u8*)((u8*)object + 0xD) = value;
}

void func_003486D0(void* object)
{
}

u32 func_003486E0(void* object)
{
    return *(u32*)((u8*)object + 0x20);
}

void func_003486F0(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x20) = value;
}

/**
 * @brief Restore the parent window and switch the active Field receiver.
 * @return Two for returning.
 */
s32 ItemCreationClass185060::func_slotb4()
{
    func_slot20(0);
    ItemCreationFlagToggleOwner* parent = static_cast<ItemCreationFlagToggleOwner*>(func_slot44());
    func_0034A670(parent, 1);
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 2;
}

/**
 * @brief Restore the parent window and switch the active Field receiver.
 * @return One for confirmation.
 */
s32 ItemCreationClass185060::func_slotb0()
{
    func_slot20(0);
    ItemCreationFlagToggleOwner* parent = static_cast<ItemCreationFlagToggleOwner*>(func_slot44());
    func_0034A670(parent, 1);
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 1;
}


/**
 * @brief Create the confirmation window panels and text displays.
 * @param associated Text source associated with the window.
 * @return Always one.
 */
s32 ItemCreationClass185060::func_slotf4(void* associated)
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
ItemCreationClass185060::~ItemCreationClass185060()
{
}

/** @brief Refresh the two option colors from the grid selection. @param object Option window. */
static inline void update_selection_colors(ItemCreationClass185160* object)
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
extern "C" void func_00348B60(ItemCreationClass185160* object, u16 mode)
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
void ItemCreationClass185160::func_slot74()
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
void ItemCreationClass185160::func_slot70()
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
s32 ItemCreationClass185160::func_slotb4()
{
    func_00348B60(this, 0);
    ItemCreationFlagToggleOwner* parent = static_cast<ItemCreationFlagToggleOwner*>(func_slot44());
    func_0034A670(parent, 1);
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 2;
}

/**
 * @brief Store an option code when the selection state has its runtime table.
 * @param state Selection state.
 * @param index Option index.
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
s32 ItemCreationClass185160::func_slotb0()
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
s32 ItemCreationClass185160::func_slotf4(void* associated)
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
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unkac)), record, 18.5f, 18.5f);
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
ItemCreationClass185160::~ItemCreationClass185160()
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00349650);

/**
 * @brief Destroy the window through its Field base.
 */
ItemCreationClass185260::~ItemCreationClass185260()
{
}

/**
 * @brief Read a supported option code from the state table.
 * @param table Option state table, or null.
 * @param index Table entry to read.
 * @return Stored code from one through thirteen, or zero otherwise.
 */
static inline u16 option_code(ItemCreationOptionTable* table, u8 index)
{
    if (table == 0)
    {
        return 0;
    }
    u16 code = table->unk188[index];
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

/** @brief Convert a stored option index into its detail index. @param index Stored index. @return Detail index. */
static inline u32 detail_index(s32 index)
{
    if (index == 0)
    {
        return 0;
    }
    return index - 31;
}

/** @brief Reset both display scale values and mark drawing state dirty. @param display Resource display. */
static inline void reset_display_scale(ItemCreationOptionResourceDisplay* display)
{
    display->unk50.unk34 = 1.0f;
    display->unk50.unk30 = 1.0f;
    display->unk3c = 1;
}

/**
 * @brief Collect category options and refresh the six resource displays.
 * @param object Selection window associated with the option state.
 * @param category Category value stored as a byte.
 */
void func_00349DE0(ItemCreationClass185360* object, u32 category)
{
    if (object->unka8 != 0)
    {
        for (s32 index = 0; index < 6; index++)
        {
            object->unkcc[index] = 0;
            object->unkd2[index] = 0;
        }
        object->unkc9 = category;
        u8 desired = object->unkc9 + 1;
        object->unkc8 = 0;
        for (s32 index = 32; index <= 59; index++)
        {
            if (desired == (u8)option_code(object->unka8->unk40, (u8)index))
            {
                u16 resource = index - 11;
                u16 detail = detail_index(index);
                object->unkcc[object->unkc8] = resource;
                object->unkd2[object->unkc8] = detail;
                object->unkc8++;
            }
            if (object->unkc8 >= 7)
            {
                break;
            }
        }
        for (s32 index = 0; index < 6; index++)
        {
            void* allocation = func_002D3D80(D_001B643C->unk20, 0);
            FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 16);
            reset_display_scale(object->unkac[index]);
            func_002D5CF0(static_cast<FieldResourceDisplay2D5CF0*>(static_cast<void*>(object->unkac[index])), allocation, record, 0);
        }
        for (s32 index = 0; index < 6; index++)
        {
            s32 raw = object->unkcc[index];
            if (raw != 0)
            {
                u8 code = raw;
                void* allocation = func_002D3D80(D_001B643C->unk20, code);
                FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 81);
                object->unkac[index]->unkd0 = code;
                func_002D5CF0(static_cast<FieldResourceDisplay2D5CF0*>(static_cast<void*>(object->unkac[index])), allocation, record, 0);
                object->unkac[index]->unk3f = 1;
                reset_display_scale(object->unkac[index]);
            }
        }
    }
}

/**
 * @brief Copy the grid selection to the alternate option display.
 * @param object Grid window.
 * @param enabled Whether to copy the selected option code or reset it to zero.
 */
static inline void update_selection(ItemCreationClass185360* object, bool enabled)
{
    if (object->unkc4 != 0)
    {
        object->unkca = object->unkc4->unk114;
        ItemCreationClass185560* child = static_cast<ItemCreationClass185560*>(object->func_slot4c());
        u8 code = enabled ? object->unkd2[object->unkca] : 0;
        if (child != 0)
        {
            child->unkf8 = code;
            func_0034B970(child);
        }
    }
}

/**
 * @brief Move the grid in direction two and refresh the alternate display.
 */
void ItemCreationClass185360::func_slot74()
{
    if (unkc4 != 0)
    {
        if (unkc4->func_0023CDB0(2) != 1)
        {
            update_selection(this, true);
        }
    }
}

/**
 * @brief Move the grid in direction three and refresh the alternate display.
 */
void ItemCreationClass185360::func_slot70()
{
    if (unkc4 != 0)
    {
        if (unkc4->func_0023CDB0(3) != 1)
        {
            update_selection(this, true);
        }
    }
}

/**
 * @brief Reset the grid and restore its associated window.
 * @return Zero without an associated window, or one after restoring it.
 */
s32 ItemCreationClass185360::func_slotb4()
{
    func_0034A1E0(this, 0);
    ItemCreationFlagToggleOwner* parent = static_cast<ItemCreationFlagToggleOwner*>(func_slot44());
    if (parent == 0)
    {
        return 0;
    }
    func_0034A670(parent, 1);
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 1;
}

/**
 * @brief Activate or reset the option grid and refresh its alternate display.
 * @param object Option grid window.
 * @param mode Zero resets the grid; one activates it.
 */
void func_0034A1E0(ItemCreationClass185360* object, u16 mode)
{
    switch (mode)
    {
    case 1:
        if (object->unkc4 != 0)
        {
            object->unkc4->unkad = 1;
            update_selection(object, true);
        }
        break;
    case 0:
        if (object->unkc4 != 0)
        {
            object->unkc4->unkad = 0;
            update_selection(object, false);
        }
        break;
    }
}

/**
 * @brief Destroy the window through its Field base.
 */
ItemCreationClass185360::~ItemCreationClass185360()
{
}

void func_0034A670(ItemCreationFlagToggleOwner* object, u8 mode)
{
    ItemCreationNested* nested;
    switch (mode)
    {
    case 1:
        nested = object->unk18c;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->unk194;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->unk198;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->unk1a0;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->unk190;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->unk19c;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->unk15c;
        if (nested != 0)
        {
            nested->unk70 = 128.0f;
            nested->unk3c = 1;
        }
        break;
    case 0:
        nested = object->unk18c;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->unk194;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->unk198;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->unk1a0;
        if (nested != 0)
        {
            nested->unk3f = 0;
        }
        nested = object->unk190;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->unk19c;
        if (nested != 0)
        {
            nested->unk3f = 1;
        }
        nested = object->unk15c;
        if (nested != 0)
        {
            nested->unk70 = 64.0f;
            nested->unk3c = 1;
        }
        break;
    }
}

void func_0034A7A0(ItemCreationEightColorOwner* object, u8 selected)
{
    ItemCreationColorRecordState* state;
    ItemCreationColorRecord* record;
    s32 index;
    u16 flags;
    u8 enabled;

    for (index = 0; index < 8; index++)
    {
        ItemCreationColorDisplay* display = object->unk168[index];
        if (display != 0)
        {
            display->unk94 = ITEM_CREATION_COLOR_DIM;
            display->unk3c = 1;
        }
    }
    if (object->unk188 != 0)
    {
        object->unk188->unk3f = 0;
    }
    state = D_001B64F8;
    enabled = 0;
    if (selected > 0 && selected < 13)
    {
        enabled = 1;
    }
    if (enabled)
    {
        record = &state->unk10f50[selected - 1];
    }
    else
    {
        record = 0;
    }
    if (record != 0)
    {
        flags = record->unk30;
        if (flags & ITEM_CREATION_CATEGORY_FLAG_COOK)
        {
            ItemCreationColorDisplay* display = object->unk168[0];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_CATEGORY_FLAG_ALCH)
        {
            ItemCreationColorDisplay* display = object->unk168[1];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_CATEGORY_FLAG_CRFT)
        {
            ItemCreationColorDisplay* display = object->unk168[2];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_CATEGORY_FLAG_CMPD)
        {
            ItemCreationColorDisplay* display = object->unk168[3];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_CATEGORY_FLAG_SMTH)
        {
            ItemCreationColorDisplay* display = object->unk168[4];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_CATEGORY_FLAG_WRIT)
        {
            ItemCreationColorDisplay* display = object->unk168[5];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_CATEGORY_FLAG_ENG)
        {
            ItemCreationColorDisplay* display = object->unk168[6];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_CATEGORY_FLAG_SYTH)
        {
            ItemCreationColorDisplay* display = object->unk168[7];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
    }
}

/**
 * @brief Restore the alternate window and its mode displays.
 * @return Always one.
 */
s32 ItemCreationClass185460::func_slotbc()
{
    func_0034A670(static_cast<ItemCreationFlagToggleOwner*>(static_cast<void*>(this)), 0);
    ItemCreationClass185360* alternate = static_cast<ItemCreationClass185360*>(this->func_slot4c());
    func_0034A1E0(alternate, 1);
    D_001B643C->unk10->unk14->func_00263C70(alternate);
    return 1;
}

/**
 * @brief Store the transfer height and mark its drawing state dirty.
 * @param display Transfer display.
 * @param height Height to store.
 */
static inline void set_transfer_height(ItemCreationTransferDisplay* display, float height)
{
    display->unk70 = height;
    display->unk3c = 1;
}

/**
 * @brief Open the selected detail window or restore the associated window.
 * @return Zero without the required windows, three when opening a detail, or one when restoring its parent.
 */
s32 ItemCreationClass185460::func_slotb0()
{
    ItemCreationClass185360* alternate = static_cast<ItemCreationClass185360*>(this->func_slot4c());
    if (alternate == 0)
    {
        return 0;
    }
    ItemCreationClass185160* parent = static_cast<ItemCreationClass185160*>(this->func_slot44());
    if (parent == 0)
    {
        return 0;
    }
    if (this->unk1a4 == 0)
    {
        return 0;
    }
    u8 selected = alternate->unkc8;
    set_transfer_height(this->unk15c, 64.0f);
    if (selected >= 6)
    {
        this->unk1a4->func_slot20(1);
        D_001B643C->unk10->unk14->func_00263C70(this->unk1a4);
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
void ItemCreationClass185460::func_slotf8(u16 direction)
{
    ItemCreationClass185160* parent;
    ItemCreationSelection* selection;
    const float* position;
    s32 index;
    u8 selected;

    if (this->unk15c != 0 && this->unk15c->unk75 != 0)
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
        func_466E40(this->unk15c->unk40, position[0], position[1], 0.05f);
        func_002CFE40(D_001B643C->unk10, 0);
    }
    selected = this->unk160->unk6c;
    if (this->unk164 != 0)
    {
        func_4C6DF0(this->unk164, this->func_slot54(), selected + 0x3520, 0);
    }
    func_0034A7A0(static_cast<ItemCreationEightColorOwner*>(static_cast<void*>(this)), selected);
    ItemCreationClass185360* alternate = static_cast<ItemCreationClass185360*>(this->func_slot4c());
    if (alternate != 0)
    {
        func_00349DE0(alternate, selected);
    }
    parent = static_cast<ItemCreationClass185160*>(this->func_slot44());
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
void ItemCreationClass185460::func_slot74()
{
    func_slotf8(2);
}

/**
 * @brief Forward direction 4 to the window.
 */
void ItemCreationClass185460::func_slot70()
{
    func_slotf8(4);
}

/**
 * @brief Forward direction 3 to the window.
 */
void ItemCreationClass185460::func_slot6c()
{
    func_slotf8(3);
}

/**
 * @brief Forward direction 1 to the window.
 */
void ItemCreationClass185460::func_slot68()
{
    func_slotf8(1);
}

/** @brief Destroy the selection window through its base. */
ItemCreationClass185460::~ItemCreationClass185460()
{
}

/** @brief Initialize the selection window and its display pointers. */
ItemCreationClass185460::ItemCreationClass185460()
{
    unk160 = 0;
    unk160 = &unkdc;
    unk164 = 0;
    for (s32 index = 0; index < 9; index++)
    {
        unk168[index] = 0;
    }
    unk18c = 0;
    unk190 = 0;
    unk194 = 0;
    unk198 = 0;
    unk19c = 0;
    unk1a0 = 0;
    unk1a4 = 0;
}

/** Six-byte category record containing an icon and its channel. */
struct ItemCreationSingleIconRecord
{
    u8 unk00[2];
    u8 unk02;
    u8 unk03;
    u8 unk04[2];
};

/** Single-channel category records, indexed by category minus one. */
extern "C" const ItemCreationSingleIconRecord D_501DA0[];

/**
 * @brief Test whether a category uses the eight-channel icon table.
 * @param category Detail category.
 * @return One for categories from twenty-nine onward, otherwise zero.
 */
static inline u8 has_extended_icons(u8 category)
{
    return category >= 29;
}

/** Thirteen-byte category record containing eight channel icons. */
struct ItemCreationIconRecord
{
    u8 icons[8];
    u8 unk08[5];
};
/** Eight-channel category records, indexed by category minus twenty-nine. */
extern "C" const ItemCreationIconRecord D_501E50[];

/**
 * @brief Find an entry in the eight-channel icon table.
 * @param index Category index within the table.
 * @return Icon record at that index.
 */
static inline const ItemCreationIconRecord* extended_icon_record(s32 index)
{
    return &D_501E50[index];
}
/**
 * @brief Read the icon assigned to a category and channel.
 * @param category Detail category.
 * @param channel Channel index from zero through seven.
 * @return Assigned icon, or zero for an unassigned channel.
 */
static inline u8 detail_icon(u8 category, s32 channel)
{
    u8 icon = 0;
    if (has_extended_icons(category))
    {
        icon = extended_icon_record(category - 29)->icons[channel];
    }
    else
    {
        const ItemCreationSingleIconRecord* record = &D_501DA0[category - 1];
        if (record->unk03 == channel + 1)
        {
            icon = record->unk02;
        }
    }
    return icon;
}

/**
 * @brief Convert a stored option code to its option-table index.
 * @param index Stored one-based option code, or zero.
 * @return Zero for no option, otherwise the code plus thirty-one.
 */
static inline u32 stored_option_index(u8 index)
{
    if (index == 0)
    {
        return 0;
    }
    return index + 31;
}

/**
 * @brief Return the runtime record for a one-based option code.
 * @param state State containing the runtime option records.
 * @param option One-based option code.
 * @return Selected record, or null for an invalid code.
 */
static inline ItemCreationRuntimeOptionRecord* option_record(ItemCreationColorRecordState* state, u8 option)
{
    u8 valid = option >= 1 && option < 39;
    if (valid)
    {
        return &state->unk10d88[option - 1];
    }
    return 0;
}

/**
 * @brief Enable one channel's label and icon.
 * @param object Option detail window.
 * @param record Selected runtime option record.
 * @param index Channel index from zero through seven.
 */
static inline void show_channel(ItemCreationClass185560* object, ItemCreationRuntimeOptionRecord* record, u8 index)
{
    static_cast<LibObject178750*>(object->unkb0[index])->set_color(0x808080);
    u8 icon = detail_icon(record->unk06, index);
    LibObject174F20* image = static_cast<LibObject174F20*>(object->unkd4[index]);
    image->unkfc = icon;
    image->unk3c = 1;
    static_cast<LibObject174F20*>(object->unkd4[index])->unk3d = 1;
}

void func_0034B970(ItemCreationClass185560* object)
{
    object->unkac->unk3f = 0;
    for (s32 index = 0; index < 8; index++)
    {
        static_cast<LibObject178750*>(object->unkb0[index])->set_color(0x505050);
        static_cast<LibObject174F20*>(object->unkd4[index])->unk3d = 0;
    }
    u8 code = object->unkf8;
    if (code != 0)
    {
        ItemCreationRuntimeOptionRecord* record = option_record(D_001B64F8, code);
       
        // TODO: figure out if we can just do code > 0 instead of code != 0 too.
        if (code > 0)
        {
            func_4C6DF0(object->unkac, object->func_slot54(), code + 0x3584, 0);
            object->unkac->unk3f = 1;
            if (object->unka8 != 0)
            {
                u16 flags = func_00369FA0(object->unka8, stored_option_index(object->unkf8));
                if (flags & 0x1)
                {
                    show_channel(object, record, 0);
                }
                if (flags & 0x2)
                {
                    show_channel(object, record, 1);
                }
                if (flags & 0x4)
                {
                    show_channel(object, record, 2);
                }
                if (flags & 0x8)
                {
                    show_channel(object, record, 3);
                }
                if (flags & 0x10)
                {
                    show_channel(object, record, 4);
                }
                if (flags & 0x20)
                {
                    show_channel(object, record, 5);
                }
                if (flags & 0x40)
                {
                    show_channel(object, record, 6);
                }
                if (flags & 0x80)
                {
                    show_channel(object, record, 7);
                }
            }
        }
    }
}

/**
 * @brief Create the selected option title and its eight channel labels and images.
 * @param associated Text source passed to the window base and child widgets.
 * @return One after setup completes.
 */
s32 ItemCreationClass185560::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 464.0f, 296.0f, 17);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 160.0f, 172.0f, 88.0f);
    func_004C6190(unk10, panel);
    unkac = new (0) LibObject178750;
    unkac->func_004C7FE0(0.0f, 8.0f, 160.0f, 19.2f, (s32)associated, 0x3584, 1);
    unkac->set_scale(0.8f, 0.8f);
    unkac->set_mode(1);
    unkac->unk3f = 0;
    func_004C6190(unk10, unkac);
    float row_y = 34.0f;
    for (s32 index = 0; index < 8; index++)
    {
        if (index != 0 && index % 3 == 0)
        {
            row_y += 4.0f;
        }
        unkb0[index] = new (0) LibObject178750;
        unkd4[index] = new (0) LibObject174F20;
        float y = row_y + 42.0f * (index / 3);
        float x = 10.0f + 50.0f * (index % 3);
        static_cast<LibObject178750*>(unkb0[index])->func_004C7FE0(x, y, 0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_CATEGORY_LABEL_BASE, 1);
        func_00464D90(static_cast<LibObject174F20*>(unkd4[index]), 99, (s32)associated, 1, x, y + 21.0f, 38.4f, 19.2f);
        static_cast<LibObject174F20*>(unkd4[index])->set_mode(1);
        set_text_unk80(static_cast<LibObject178750*>(unkb0[index]), 0.6f);
        static_cast<LibObject174F20*>(unkd4[index])->set_scale(0.8f, 0.8f);
        func_004C6190(unk10, static_cast<LibObject178750*>(unkb0[index]));
        func_004C6190(unk10, static_cast<LibObject174F20*>(unkd4[index]));
    }
    if (unkb0[8] != 0)
    {
        static_cast<ItemCreationVisibility3F*>(unkb0[8])->unk3f = 0;
    }
    if (unkd4[8] != 0)
    {
        static_cast<ItemCreationVisibility3F*>(unkd4[8])->unk3f = 0;
    }
    func_0034B970(this);
    return 1;
}

/**
 * @brief Destroy the window through its Field base.
 */
ItemCreationClass185560::~ItemCreationClass185560()
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

static inline void set_option_list_index(ItemCreationFlagResetOwner* object, u8 list, u8 value)
{
    switch (list)
    {
    case 1:
        object->unk179 = value;
        break;
    case 2:
        object->unk1b1 = value;
        break;
    }
}

/**
 * @brief Dispatch a grid direction and refresh the selected option markers.
 * @param direction Direction code.
 */
void ItemCreationClass185660::func_slotf8(s32 direction)
{
    if (unkc8 != 0 && unkc8->func_0023CDB0(direction) != 1)
    {
        ItemCreationFlagResetOwner* target = unkcc;
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
s32 ItemCreationClass185660::func_slotb4()
{
    if (unkc4 != 0)
    {
        func_00369B80(unkc4, -1);
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
    ItemCreationFlagResetOwner* target = static_cast<ItemCreationFlagResetOwner*>(func_slot44());
    if (target != 0)
    {
        switch (target->unk164->unk129)
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
s32 ItemCreationClass185660::func_slotb0()
{
    if (unkcc != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(unkcc);
    }
    if (unkc8 != 0 && unkc4 != 0)
    {
        u8 list = unka8;
        u8 value = option_list_value(unkc4, list, selected_option_index(unkc8));
        func_00369B80(unkc4, value);
    }
    return 1;
}

/**
 * @brief Set up the option window and recover its associated display.
 * @param associated Object associated with the window.
 * @return Zero when no option state is attached, or one after setup.
 */
s32 ItemCreationClass185660::func_slotf4(void* associated)
{
    if (unkc4 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 384.0f, 17);
    ItemCreationClass185860::func_slotf4(associated);
    unkcc = static_cast<ItemCreationFlagResetOwner*>(func_slot44());
    return 1;
}

/**
 * @brief Destroy the option window and its base.
 */
ItemCreationClass185660::~ItemCreationClass185660()
{
}

/**
 * @brief Dispatch a grid direction and refresh the selected option markers.
 * @param direction Direction code.
 */
void ItemCreationClass185760::func_slotf8(s32 direction)
{
    if (unkc8 != 0 && unkc8->func_0023CDB0(direction) != 1)
    {
        ItemCreationFlagResetOwner* target = unkcc;
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
static inline void set_transfer_position(ItemCreationTransferDisplay* display, float x, float y)
{
    display->unk50 = x;
    display->unk54 = y;
    display->unk75 = 1;
    display->unk3c = 1;
}

/**
 * @brief Reset the option and restore its associated selection display.
 * @return Always two.
 */
s32 ItemCreationClass185760::func_slotb4()
{
    if (unkc4 != 0)
    {
        func_00369B80(unkc4, -1);
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
    ItemCreationFlagResetOwner* target = static_cast<ItemCreationFlagResetOwner*>(func_slot44());
    if (target != 0)
    {
        u8 selected = unka9;
        target->unk160->unk6c = selected;
        const float* position = option_selection_position(target->unk160, selected);
        set_transfer_position(target->unk15c, position[0], position[1]);
        switch (target->unk164->unk129)
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
s32 ItemCreationClass185760::func_slotb0()
{
    if (unkcc != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(unkcc);
    }
    if (unkc8 != 0 && unkc4 != 0)
    {
        u8 value = option_list_value(unkc4, unka8, selected_option_index(unkc8));
        func_00369B80(unkc4, value);
    }
    ItemCreationFlagResetOwner* target = static_cast<ItemCreationFlagResetOwner*>(func_slot44());
    if (target != 0)
    {
        switch (target->unk164->unk129)
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
s32 ItemCreationClass185760::func_slotf4(void* associated)
{
    if (unkc4 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 300.0f, 17);
    ItemCreationClass185860::func_slotf4(associated);
    unkcc = static_cast<ItemCreationFlagResetOwner*>(func_slot44());
    return 1;
}

/**
 * @brief Destroy the option window and its base.
 */
ItemCreationClass185760::~ItemCreationClass185760()
{
}

/**
 * @brief Transfer the selected option into its list display and refresh the option markers.
 * @param object Owner of the six-slot option list, valid selected index, and marker display.
 */
void func_0034CE00(ItemCreationOptionTransferOwner* object)
{
    ItemCreationFlagResetOwner* target = object->unkcc;
    ItemCreationSelectedDisplayState* state;
    u8 status;
    u8 list;
    u32 value;
    u8 result;
    if (target != 0 && (state = object->unkc4) != 0)
    {
        list = object->unka8;
        status = state->unk129;
        if (list == 1)
        {
            switch (status)
            {
        case 1:
        case 2:
        case 3:
                value = option_list_value(state, list, selected_option_index(object->unkc8));
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
        list = object->unka8;
        if (list == 2)
        {
            switch (status)
            {
        case 3:
                value = option_list_value(object->unkc4, list, selected_option_index(object->unkc8));
                result = value;
                if (value != 0)
                {
                    result = option_list_index(value);
                }
                target = object->unkcc;
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
void ItemCreationClass185860::func_slotf8(s32 direction)
{
    if (unkc8 != 0 && unkc8->func_0023CDB0(direction) != 1)
    {
        ItemCreationFlagResetOwner* target = unkcc;
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
void ItemCreationClass185860::func_slot74()
{
    func_slotf8(2);
}

/**
 * @brief Forward direction 3 to the window.
 */
void ItemCreationClass185860::func_slot70()
{
    func_slotf8(3);
}

/**
 * @brief Clear the selected option and restore the active view.
 * @return Always two.
 */
s32 ItemCreationClass185860::func_slotb4()
{
    if (unkc4 != 0)
    {
        func_00369B80(unkc4, -1);
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
s32 ItemCreationClass185860::func_slotb0()
{
    if (unkcc != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(unkcc);
    }
    if (unkc8 != 0 && unkc4 != 0)
    {
        u8 list = unka8;
        u8 value = option_list_value(unkc4, list, selected_option_index(unkc8));
        func_00369B80(unkc4, value);
    }
    return 1;
}

/**
 * @brief Refresh the six resource displays from their current option list.
 * @param object Option display to refresh.
 */
void func_0034D340(ItemCreationOptionDisplay* object)
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
            func_002D5CF0(static_cast<FieldResourceDisplay2D5CF0*>(static_cast<void*>(object->unkac[index])), allocation, record, 0);
        }
    }
}


void func_0034D980(ItemCreationFlagResetOwner* object, u8 option)
{
    if (object->unk164 != 0)
    {
        if (option == 0xFF)
        {
            option = object->unk160->unk6c;
        }
        switch (object->unk164->unk129)
        {
        case 0:
        case 1:
            func_0036A780(object->unk164, option, 1);
            func_0036A5D0(object->unk164, 6);
            break;
        case 2:
        case 3:
            func_0036A780(object->unk164, option, 2);
            func_0036A5D0(object->unk164, 7);
            break;
        }
    }
}

void func_0034DA30(ItemCreationFlagResetOwner* object)
{
    object->unk17c[0]->unk3f = 0;
    object->unk17c[1]->unk3f = 0;
    object->unk17c[2]->unk3f = 0;
    object->unk17c[3]->unk3f = 0;
    object->unk17c[4]->unk3f = 0;
    object->unk17c[5]->unk3f = 0;
    object->unk17c[6]->unk3f = 0;
    object->unk17c[7]->unk3f = 0;
    object->unk17c[8]->unk3f = 0;
    object->unk1a4[0]->unk3f = 0;
    object->unk1a4[1]->unk3f = 0;
    object->unk1a4[2]->unk3f = 0;
    object->unk1b4[0]->unk3f = 0;
    object->unk1b4[1]->unk3f = 0;
    object->unk1b4[2]->unk3f = 0;
    object->unk1b4[3]->unk3f = 0;
    object->unk1b4[4]->unk3f = 0;
    object->unk1b4[5]->unk3f = 0;
    object->unk1b4[6]->unk3f = 0;
    object->unk1b4[7]->unk3f = 0;
    object->unk1b4[8]->unk3f = 0;
    object->unk1dc[0]->unk3f = 0;
    object->unk1dc[1]->unk3f = 0;
    object->unk1dc[2]->unk3f = 0;
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
static inline ItemCreationRuntimeOptionRecord* runtime_option_record(ItemCreationColorRecordState* state, u8 option)
{
    if (runtime_option_valid(option))
    {
        return &state->unk10d88[option - 1];
    }
    return 0;
}

/**
 * @brief Show an icon on an image widget.
 * @param image Image widget.
 * @param icon Icon index.
 */
static inline void set_image_icon(LibObject174F20* image, u32 icon)
{
    image->unkfc = icon;
    image->unk3c = 1;
}

/**
 * @brief Read the enabled-label mask for a category.
 * @param state Selection state.
 * @param code One-based category code.
 * @return Bit mask of enabled labels.
 */
static inline u16 category_flags(ItemCreationSelectedDisplayState* state, u8 code)
{
    // The one-based lookup begins two bytes before its twelve mask entries.
    const u16* words = reinterpret_cast<const u16*>(&state->unk77[5]);
    return words[code];
}
/** @brief Read a group's category code. @param object Option window. @param group Group index. @return Category code. */
static inline u8 category_value(ItemCreationClass185960* object, s32 group)
{
    return group == 0 ? object->unk178 : object->unk1b0;
}
/** @brief Store a group's category code. @param object Option window. @param group Group index. @param value Category code. */
static inline void set_category_value(ItemCreationClass185960* object, s32 group, u8 value)
{
    if (group == 0)
    {
        object->unk178 = value;
    }
    else
    {
        object->unk1b0 = value;
    }
}
/** @brief Return a group's category title. @param object Option window. @param group Group index. @return Title widget. */
static inline LibObject178750* category_title(ItemCreationClass185960* object, s32 group)
{
    return static_cast<LibObject178750*>(group == 0 ? object->unk17c : object->unk1b4);
}
/** @brief Return one of a group's category labels. @param object Option window. @param group Group index. @param index Label index. @return Label widget. */
static inline LibClass174EF0* category_label(ItemCreationClass185960* object, s32 group, s32 index)
{
    return group == 0 ? object->unk180[index] : object->unk1b8[index];
}
/**
 * @brief Show a category label, bright when its bit is set in the mask.
 * @param object Option window.
 * @param group Group index.
 * @param index Label index.
 * @param flags Enabled-label mask.
 */
static inline void update_category_label(ItemCreationClass185960* object, s32 group, s32 index, u16 flags)
{
    category_label(object, group, index)->unk3f = 1;
    if (flags & (1 << index))
    {
        category_label(object, group, index)->set_color(ITEM_CREATION_COLOR_BRIGHT);
    }
    else
    {
        category_label(object, group, index)->set_color(ITEM_CREATION_COLOR_DIM);
    }
}
/**
 * @brief Refresh a group's category title and labels once the stage reaches it.
 * @param object Option window.
 * @param stage Current selection stage.
 * @param group Group index.
 * @param selected Category code to store at the group's own stage, or zero.
 */
static inline void update_category_group(ItemCreationClass185960* object, s32 stage, s32 group, u8 selected)
{
    if (stage >= 2 * group)
    {
        if (selected && stage == 2 * group)
        {
            set_category_value(object, group, selected);
        }
        void* associated = object->func_slot54();
        func_4C6DF0(category_title(object, group), associated, category_value(object, group) + 0x3520, 0);
        category_title(object, group)->unk3f = 1;
        u16 flags = category_flags(object->unk164, category_value(object, group));
        update_category_label(object, group, 0, flags);
        update_category_label(object, group, 1, flags);
        update_category_label(object, group, 2, flags);
        update_category_label(object, group, 3, flags);
        update_category_label(object, group, 4, flags);
        update_category_label(object, group, 5, flags);
        update_category_label(object, group, 6, flags);
        update_category_label(object, group, 7, flags);
    }
}
/** @brief Test a one-based detail channel. @param channel Channel. @return Whether it is one through nine. */
static inline u8 detail_channel_valid(u8 channel)
{
    return channel > 0 && channel < 10;
}
/** @brief Read a group's detail code. @param object Option window. @param group Group index. @return Detail code. */
static inline u8 detail_value(ItemCreationClass185960* object, s32 group)
{
    return group == 0 ? object->unk179 : object->unk1b1;
}
/** @brief Return one of a group's detail displays. @param object Option window. @param group Group index. @param index Display index. @return Display widget. */
static inline LibClass174EF0* detail_display(ItemCreationClass185960* object, s32 group, s32 index)
{
    return group == 0 ? object->unk1a4[index] : object->unk1dc[index];
}
/**
 * @brief Look up the icon for a stored detail code.
 * @param state Selection state.
 * @param code Stored detail code.
 * @return Icon index, or zero when the record or its channel has none.
 */
static inline u8 selected_detail_icon(ItemCreationSelectedDisplayState* state, u8 code)
{
    u8 result = 0;
    if (D_001B64F8 != 0)
    {
        ItemCreationRuntimeOptionRecord* record = runtime_option_record(D_001B64F8, code);
        if (record != 0)
        {
            u8 channel = func_00369F20(state, stored_option_index(code)) - 0x3457;
            u8 icon = 0;
            if (detail_channel_valid(channel))
            {
                u8 category = record->unk06;
                if (has_extended_icons(category))
                {
                    icon = extended_icon_record(category - 29)->icons[channel - 1];
                }
                else
                {
                    const ItemCreationSingleIconRecord* single = &D_501DA0[category - 1];
                    if (channel == single->unk03)
                    {
                        icon = single->unk02;
                    }
                }
            }
            result = icon;
        }
    }
    return result;
}
/**
 * @brief Refresh a group's detail name, text and icon once the stage passes it.
 * @param object Option window.
 * @param stage Current selection stage.
 * @param group Group index.
 */
static inline void update_detail_group(ItemCreationClass185960* object, s32 stage, s32 group)
{
    if (stage >= 2 * group + 1)
    {
        s32 raw_code = detail_value(object, group);
        if (raw_code != 0)
        {
            u8 code = raw_code;
            void* associated = object->func_slot54();
            func_4C6DF0(static_cast<LibObject178750*>(detail_display(object, group, 0)), associated, code + 0x3584, 0);
            detail_display(object, group, 0)->unk3f = 1;
        }
        else
        {
            detail_display(object, group, 0)->unk3f = 0;
        }
        s32 raw_detail = detail_value(object, group);
        if (raw_detail != 0)
        {
            u8 code = raw_detail;
            u16 text = func_00369F20(object->unk164, stored_option_index(code));
            void* associated = object->func_slot54();
            func_4C6DF0(static_cast<LibObject178750*>(detail_display(object, group, 1)), associated, text, 0);
            detail_display(object, group, 1)->unk3f = 1;
            s32 raw_icon_detail = detail_value(object, group);
            u8 icon = selected_detail_icon(object->unk164, raw_icon_detail);
            set_image_icon(static_cast<LibObject174F20*>(detail_display(object, group, 2)), icon);
            detail_display(object, group, 2)->unk3f = 1;
        }
    }
}
/**
 * @brief Refresh both category and detail groups, then reapply the default option.
 * @param prefix Option window.
 * @param option Category code to store, or 0xFF for the window's current option.
 */
extern "C" void func_0034DB00(ItemCreationFlagResetOwner* prefix, u8 option)
{
    ItemCreationClass185960* object = static_cast<ItemCreationClass185960*>(static_cast<void*>(prefix));
    func_0034DA30(prefix);
    if (option == 0xFF)
    {
        option = object->unk160->unk6c;
    }
    u32 stage = object->unk164->unk129;
    update_category_group(object, stage, 0, option);
    update_detail_group(object, stage, 0);
    update_category_group(object, stage, 1, option);
    update_detail_group(object, stage, 1);
    if (option == 0xFF)
    {
        func_0034D980(prefix, option);
    }
}

void func_0034E4D0(ItemCreationFlagResetOwner* object, u16 direction)
{
    ItemCreationSelection* selection;
    const float* position;
    s32 index;
    u8 selected;

    if (object->unk15c != 0 && object->unk15c->unk75 != 0)
    {
        selection = &object->unkdc;
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
        func_466E40(object->unk15c->unk40, position[0], position[1], 0.05f);
        func_002CFE40(D_001B643C->unk10, 0);
    }
    selected = object->unk160->unk6c;
    func_0034DB00(object, selected);
    func_0034D980(object, selected);
}

/**
 * @brief Forward direction 2 to the window.
 */
void ItemCreationClass185960::func_slot74()
{
    func_slotf8(2);
}

/**
 * @brief Forward direction 4 to the window.
 */
void ItemCreationClass185960::func_slot70()
{
    func_slotf8(4);
}

/**
 * @brief Forward direction 3 to the window.
 */
void ItemCreationClass185960::func_slot6c()
{
    func_slotf8(3);
}

/**
 * @brief Forward direction 1 to the window.
 */
void ItemCreationClass185960::func_slot68()
{
    func_slotf8(1);
}

/**
 * @brief Reset the option transfer or return to the primary option window.
 * @return Zero without a selection state, or two otherwise.
 */
s32 ItemCreationClass185960::func_slotb4()
{
    ItemCreationSelectedDisplayState* state = unk164;
    if (state == 0)
    {
        return 0;
    }
    switch (state->unk129)
    {
    case 0:
    {
        func_0036AAA0(state);
        ItemCreationSelectedDisplayState* count_state = unk164;
        for (s32 index = 1; index < 28; index++)
        {
            ItemCreationRuntimeOptionRecord* record = runtime_option_record(D_001B64F8, index);
            if (record != 0 && record->unk08 == 2)
            {
                count_state->unk19b++;
            }
        }
        func_00369B80(unk164, -1);
        state = unk164;
        state->unk47 = 0;
        func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
        state = unk164;
        static_cast<FieldClass153E30*>(static_cast<void*>(state))->func_00263C70(state->unka0);
        break;
    }
    case 1:
        break;
    case 2:
    {
        state->unk129 = 1;
        ItemCreationClass185860* window = static_cast<ItemCreationClass185860*>(func_slot44());
        if (window->unkc8 != 0)
        {
            func_0023CEA0(window->unkc8, 1);
        }
        D_001B643C->unk10->unk14->func_00263C70(window);
        func_0036A5D0(unk164, 7);
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
s32 ItemCreationClass185960::func_slotb0()
{
    if (unk164 == 0)
    {
        return 0;
    }
    switch (unk164->unk129)
    {
    case 0:
    {
        ItemCreationSelection* selection = unk160;
        const float* position = selection->unk00[selection->unk6c - 1].unk00;
        set_transfer_position(unk16c, position[0], position[1]);
        unk16c->unk3f = 1;
        unk15c->unk3f = 0;
        ItemCreationClass185860* window = static_cast<ItemCreationClass185860*>(func_slot44());
        if (window->unkc8 != 0)
        {
            func_0023CEA0(window->unkc8, 1);
        }
        D_001B643C->unk10->unk14->func_00263C70(window);
        func_00369B80(unk164, unk178);
        break;
    }
    case 1:
        break;
    case 2:
    {
        if (unk1b0 == unk164->unk12a)
        {
            return 3;
        }
        ItemCreationClass185860* window = static_cast<ItemCreationClass185860*>(func_slot4c());
        if (window->unkc8 != 0)
        {
            func_0023CEA0(window->unkc8, 1);
        }
        D_001B643C->unk10->unk14->func_00263C70(window);
        func_00369B80(unk164, unk1b0);
        break;
    }
    case 3:
        break;
    }
    return 1;
}

/** @brief Destroy the selection window through its base. */
ItemCreationClass185960::~ItemCreationClass185960()
{
}

/** @brief Initialize the selection window and its display pointers. */
ItemCreationClass185960::ItemCreationClass185960()
{
    unk160 = 0;
    unk160 = &unkdc;
    unk164 = 0;
    unk170 = 0;
    unk1b0 = 0;
    unk16c = 0;
    unk174 = 0;
    unk178 = 0;
    unk179 = 0;
    unk17c = 0;
    unk1a4[0] = 0;
    unk1a4[1] = 0;
    unk1a4[2] = 0;
    unk1b0 = 0;
    unk1b1 = 0;
    unk1b4 = 0;
    unk1dc[0] = 0;
    unk1dc[1] = 0;
    unk1dc[2] = 0;
    for (s32 index = 0; index < 9; index++)
    {
        unk180[index] = 0;
        unk1b8[index] = 0;
    }
}

void func_0034F9B0(ItemCreationFlagResetOwner* object, u16 direction)
{
    ItemCreationSelection* selection;
    const float* position;
    s32 index;

    if (object->unk15c != 0 && object->unk15c->unk75 != 0)
    {
        selection = &object->unkdc;
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
        func_466E40(object->unk15c->unk40, position[0], position[1], 0.05f);
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
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), record, 0.0f, 0.0f);
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
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), record, position[0], position[1] - 6.0f);
        display->unk34 = 3;
        func_004C6190(object->unk10, display);
        if (enabled == 0)
        {
            display->unk3f = 0;
        }
    }
    return 1;
}

s32 func_0034FD50(ItemCreationFlagResetOwner* object, void* associated)
{
    func_002CE8D0((FieldObjectCE8D0*)object, associated, 16.0f, 72.0f, 17);
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
 * @param object Result window.
 * @return Always one.
 */
extern "C" s32 func_0034FE00(ItemCreationClass185B60* object)
{
    object->func_slot20(0);
    void* associated = object->func_slot44();
    if (associated != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(associated);
    }
    ItemCreationSelectedDisplayState* state = object->unka8;
    if (state != 0)
    {
        if (result_flag_missing(state) == false)
        {
            ItemCreationClass186370* window = new (0) ItemCreationClass186370;
            state = object->unka8;
            window->func_slotf4(state->func_00263CC0());
            state = object->unka8;
            state->func_00263FD0(window);
            state = object->unka8;
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
 * @param object Result window.
 * @return Always one.
 */
extern "C" s32 func_0034FF70(ItemCreationClass185B60* object)
{
    object->func_slot20(0);
    void* associated = object->func_slot44();
    if (associated != 0)
    {
        D_001B643C->unk10->unk14->func_00263C70(associated);
    }
    ItemCreationSelectedDisplayState* state = object->unka8;
    if (state != 0)
    {
        if (result_flag_missing(state) == false)
        {
            ItemCreationClass186370* window = new (0) ItemCreationClass186370;
            state = object->unka8;
            window->func_slotf4(state->func_00263CC0());
            state = object->unka8;
            state->func_00263FD0(window);
            state = object->unka8;
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
extern "C" void func_003500D0(ItemCreationClass185B60* object, u8 mode)
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
ItemCreationClass185B60::~ItemCreationClass185B60()
{
}

/**
 * @brief Destroy the window through its Field base.
 */
ItemCreationClass185C60::~ItemCreationClass185C60()
{
}

/** @brief Restore the third action row and associated resource window. @return Always two. */
s32 ItemCreationClass185D60::func_slotb4()
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
                    func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index)->unk00);
                if (index == 2)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    func_0023B7E0(static_cast<FieldObject23B950*>(static_cast<void*>(unkb0)),
                        static_cast<FieldTarget23B850*>(static_cast<void*>(display)));
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
s32 ItemCreationClass185D60::func_slotb0()
{
    if (unkac == 0)
    {
        return 0;
    }
    switch (func_23B3A0(static_cast<FieldState23B3A0*>(static_cast<void*>(unkac))))
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
                        func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index)->unk00);
                    if (index == 2)
                    {
                        display->set_color(ITEM_CREATION_COLOR_SELECTED);
                        func_0023B7E0(static_cast<FieldObject23B950*>(static_cast<void*>(unkb0)),
                            static_cast<FieldTarget23B850*>(static_cast<void*>(display)));
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
                    func_003698E0(unka8, 0);
                }
                if (unka8->unk1b4[1] != 0)
                {
                    func_003698E0(unka8, 1);
                }
                if (unka8->unk1b4[2] != 0)
                {
                    func_003698E0(unka8, 2);
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
                            func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index)->unk00);
                        if (index == 2)
                        {
                            display->set_color(ITEM_CREATION_COLOR_SELECTED);
                            func_0023B7E0(static_cast<FieldObject23B950*>(static_cast<void*>(unkb0)),
                                static_cast<FieldTarget23B850*>(static_cast<void*>(display)));
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
                ItemCreationClass186370* window = new (0) ItemCreationClass186370;
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

void func_00350E00(ItemCreationThreeColorList* object)
{
    if (object->unkac != 0 && (u8)func_23B3B0(object->unkac, 1) != 1)
    {
        u16 selected = func_23B3A0(object->unkac);
        if (object->unkac != 0)
        {
            s32 index;
            for (index = 0; index < 3; index++)
            {
                ItemCreationColorDisplay* display = (ItemCreationColorDisplay*)func_0036F230(&object->unk2c, index)->unk00;
                if (index == selected)
                {
                    display->unk94 = ITEM_CREATION_COLOR_SELECTED;
                    display->unk3c = 1;
                    func_0023B7E0(object->unkb0, (FieldTarget23B850*)display);
                }
                else
                {
                    display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                    display->unk3c = 1;
                }
            }
        }
    }
}

void func_00350ED0(ItemCreationThreeColorList* object)
{
    if (object->unkac != 0 && (u8)func_23B3B0(object->unkac, 0) != 1)
    {
        u16 selected = func_23B3A0(object->unkac);
        if (object->unkac != 0)
        {
            s32 index;
            for (index = 0; index < 3; index++)
            {
                ItemCreationColorDisplay* display = (ItemCreationColorDisplay*)func_0036F230(&object->unk2c, index)->unk00;
                if (index == selected)
                {
                    display->unk94 = ITEM_CREATION_COLOR_SELECTED;
                    display->unk3c = 1;
                    func_0023B7E0(object->unkb0, (FieldTarget23B850*)display);
                }
                else
                {
                    display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                    display->unk3c = 1;
                }
            }
        }
    }
}

/**
 * @brief Destroy the window through its Field base.
 */
ItemCreationClass185D60::~ItemCreationClass185D60()
{
}

/**
 * @brief Report whether an option container has no pending mode.
 * @param container Option container.
 * @return One when the container mode is zero.
 */
static inline u8 option_container_idle(ItemCreationClass185F60* container)
{
    return container->unk4a4 == 0;
}

/** @brief Finish or cancel the option container's pending action while this window is current. */
void ItemCreationClass185E60::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }
    ItemCreationClass185F60* child = unkb8;
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
extern "C" void func_00351510(ItemCreationClass185E60* object, u8 mode)
{
    s32 count = 0;
    switch (mode)
    {
    case 1:
        if (object->unkb8 == 0 && object->unkbc == 0)
        {
            ItemCreationClass185F60* container = static_cast<ItemCreationClass185F60*>(func_00100AC0(sizeof(ItemCreationClass185F60), 0));
            if (container != 0)
            {
                container = func_00352340(container);
            }
            object->unkb8 = container;
            for (s32 index = 0; index < 28; index++)
            {
                if (runtime_option_record(D_001B64F8, static_cast<u8>(index + 1))->unk08 != 0)
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
s32 ItemCreationClass185360::func_slotf4(void* associated)
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
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), record, x + 64.0f * (index % 6), 8.0f);
        func_004C6190(unk10, display);
        unkac[index] = display;
    }
    unkc4 = new (0) FieldObject23CEA0;
    unkc4->func_0023CE80(6, 1);
    unkc4->func_0023CE60(72.0f, 0.0f);
    unkc4->unkF2 = 0;
    unkc4->unk119 = 1;
    unkc4->func_0023CF50(0, 36.0f, 320.0f);
    func_0023CEA0(unkc4, 0);
    func_0036F040(&unk74, unkc4);
    func_0034A1E0(this, 0);
    return 1;
}

/**
 * @brief Initialize frame geometry and storage.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Drawing width.
 * @param height Drawing height.
 */
inline ItemCreationClass1746A0::ItemCreationClass1746A0(float x, float y, float width, float height)
{
    unk38 = 4;
    func_44B570(this, x, y, width, height);
}
/** @brief Initialize enabled frame storage. @param code Initialization code passed to the resident routine. */
inline ItemCreationClass1746A0::ItemCreationClass1746A0(s32 code)
{
    unk38 = 4;
    func_44B510(this, code);
}

/**
 * @brief Create the action panel and its frame widgets.
 * @param associated Object associated with the window.
 * @return Always one.
 */
s32 ItemCreationClass185C60::func_slotf4(void* associated)
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
s32 ItemCreationClass185D60::func_slotf4(void* associated)
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
    LibObject178750* target = static_cast<LibObject178750*>(func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), 2)->unk00);
    unkb0 = new (0) FieldClass153170;
    unkb0->func_0023B850(target, ITEM_CREATION_COLOR_SELECTED);
    func_004C6190(unk10, unkb0);
    func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkac)), 2);
    if (unkac != 0)
    {
        for (s32 index = 0; index < 3; index++)
        {
            LibObject178750* display = static_cast<LibObject178750*>(
                func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index)->unk00);
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
s32 ItemCreationClass185E60::func_slotf4(void* associated)
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
ItemCreationClass185E60::~ItemCreationClass185E60()
{
}

/**
 * @brief Update the option container and dispatch its completed action.
 * @param first First inherited update flag, unused here.
 * @param second Second inherited update flag, unused here.
 * @param third Third inherited update flag, unused here.
 */
void ItemCreationClass185F60::func_00412C40(u32 first, u32 second, u32 third)
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
void ItemCreationClass185F60::func_00412C20(float y)
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
void ItemCreationClass185F60::func_00412C10(s32 index)
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
ItemCreationClass185030* ItemCreationClass185F60::create_row(s32 index)
{
    ItemCreationClass186050* display = new (0) ItemCreationClass186050;
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


INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00352020);

/** @brief Destroy the option container and its collection base. */
ItemCreationClass185F60::~ItemCreationClass185F60()
{
}

/** @brief Initialize the option container and clear its own state. */
ItemCreationClass185F60::ItemCreationClass185F60()
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

void func_003527C0(void* object, u16 value)
{
    *(u16*)((u8*)object + 0x6C) = value;
}

/** @brief Destroy the list sentinel and list receiver. */
LibClass178A70::~LibClass178A70()
{
}


/** @brief Initialize the widget storage and select kind 5. */
ItemCreationClass172600::ItemCreationClass172600()
{
    unk38 = 5;
}

/** @brief Initialize the widget and select kind 2. */
ItemCreationClass184F30::ItemCreationClass184F30()
{
    unk38 = 2;
}

/**
 * @brief Set the transfer display value and mark it for drawing.
 * @param display Transfer display.
 * @param value Display value.
 */
static inline void set_transfer_value(ItemCreationTransferDisplay* display, float value)
{
    display->unk70 = value;
    display->unk3c = 1;
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
        unk15c = static_cast<ItemCreationTransferDisplay*>(static_cast<void*>(new (0) ItemCreationClass175030));
        if (unk15c == 0)
        {
            display_created = 0;
        }
        else
        {
            func_467360(unk15c, x, y);
            func_004C6190(unk10, static_cast<LibClass178600*>(static_cast<void*>(unk15c)));
            display_created = 1;
        }
    }
    return display_created;
}

/**
 * @brief Build the option grid and its resource displays.
 * @param associated Associated resource slot.
 * @return Whether the displays were created.
 */
s32 ItemCreationClass185460::func_slotf4(void* associated)
{
    this->FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    this->unk160->unk79 = 2;
    this->unk160->unk6c = 1;
    float x;
    float initial_y;
    initial_y = this->unk160->unk00[0].unk00[1];
    x = this->unk160->unk00[0].unk00[0];
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
    this->unk164 = new (0) LibObject178750;
    this->unk164->func_004C7FE0(448.0f, 40.0f, 160.0f, 24.0f, (s32)associated, 0x15F95, 1);
    this->unk164->set_mode(1);
    this->unk164->set_vertical_alignment(1);
    set_text_unk88(this->unk164, -1.0f);
    this->unk164->set_scale(0.8f, 0.8f);
    func_004C6190(this->unk10, this->unk164);
    LibObject178750* option_heading = new (0) LibObject178750;
    option_heading->func_004C7FE0(448.0f, 84.0f, 160.0f, 24.0f, (s32)associated, 0x32D7, 1);
    option_heading->set_mode(1);
    option_heading->set_vertical_alignment(1);
    option_heading->set_scale(0.8f, 0.8f);
    option_heading->set_color(0x808050);
    set_text_unk80(option_heading, 0.5f);
    func_004C6190(this->unk10, option_heading);
    this->unk18c = new (0) ItemCreationClass174C40;
    this->unk190 = new (0) ItemCreationClass174C40;
    this->unk194 = new (0) ItemCreationClass174C40;
    this->unk198 = new (0) LibObject178750;
    this->unk19c = new (0) LibObject178750;
    this->unk1a0 = new (0) LibObject178750;
    this->unk18c->unk34 = 6;
    this->unk190->unk34 = 6;
    this->unk194->unk34 = 6;
    func_4530E0(this->unk18c, 0x20, 312.0f, 156.4f);
    this->unk198->func_004C7FE0(344.0f, 160.0f, 0.0f, 0.0f, (s32)associated, 0x15F9A, 1);
    func_4530E0(this->unk194, 0x23, 312.0f, 180.4f);
    this->unk1a0->func_004C7FE0(344.0f, 184.0f, 0.0f, 0.0f, (s32)associated, 0x15F9B, 1);
    func_4530E0(this->unk190, 0x21, 312.0f, 180.4f);
    this->unk19c->func_004C7FE0(344.0f, 184.0f, 0.0f, 0.0f, (s32)associated, 0x15F9C, 1);
    this->unk18c->set_scale(0.9f, 0.9f);
    this->unk190->set_scale(0.9f, 0.9f);
    this->unk194->set_scale(0.9f, 0.9f);
    this->unk198->set_scale(0.9f, 0.9f);
    this->unk19c->set_scale(0.9f, 0.9f);
    this->unk1a0->set_scale(0.9f, 0.9f);
    func_004C6190(this->unk10, this->unk18c);
    func_004C6190(this->unk10, this->unk190);
    func_004C6190(this->unk10, this->unk194);
    func_004C6190(this->unk10, this->unk198);
    func_004C6190(this->unk10, this->unk19c);
    func_004C6190(this->unk10, this->unk1a0);
    float y = 126.0f;
    for (s32 index = 0; index < 8; index++)
    {
        if (index != 0 && index % 3 == 0)
        {
            y += 4.0f;
        }
        this->unk168[index] = new (0) LibObject178750;
        static_cast<LibObject178750*>(this->unk168[index])->func_004C7FE0(458.0f + 50.0f * (index % 3), y + 30.0f * (index / 3),
                                                                     0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_CATEGORY_LABEL_BASE, 1);
        set_text_unk80(static_cast<LibObject178750*>(this->unk168[index]), 0.6f);
        func_004C6190(this->unk10, this->unk168[index]);
    }
    if (this->unk168[8] != 0)
    {
        this->unk168[8]->unk3f = 0;
    }
    if (this->unk164 != 0)
    {
        func_4C6DF0(this->unk164, this->func_slot54(), 0x3521, 0);
    }
    func_0034A7A0(static_cast<ItemCreationEightColorOwner*>(static_cast<void*>(this)), 1);
    ItemCreationClass185360* alternate = static_cast<ItemCreationClass185360*>(this->func_slot4c());
    if (alternate != 0)
    {
        func_00349DE0(alternate, 1);
    }
    ItemCreationClass185160* parent = static_cast<ItemCreationClass185160*>(this->func_slot44());
    if (parent != 0)
    {
        parent->unkc5 = 1;
        u32 key = parent->unkc5 + 0x3520;
        if (parent->unkb4 != 0)
        {
            func_4C6DF0(parent->unkb4, parent->func_slot54(), key, 0);
        }
    }
    func_0034A670(static_cast<ItemCreationFlagToggleOwner*>(static_cast<void*>(this)), 1);
    return 1;
}

/**
 * @brief Build the selection window and its option displays.
 * @param associated Associated resource slot.
 * @return Whether the window was created.
 */
s32 ItemCreationClass185960::func_slotf4(void* associated)
{
    if (unk164 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    unk160->unk79 = 1;
    unk170 = unk164->unk4d;
    unk160->unk6c = unk170;
    const float* position = option_selection_position(unk160, unk170);
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
    unk16c = static_cast<ItemCreationTransferDisplay*>(static_cast<void*>(new (0) ItemCreationClass175030));
    func_467360(unk16c, position[0], position[1]);
    set_transfer_value(unk16c, 80.0f);
    func_004C6190(unk10, static_cast<LibClass178600*>(static_cast<void*>(unk16c)));
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
    unk174 = new (0) LibObject178750;
    (unk174)->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, unk170 + 0x3520, 1);
    unk174->set_mode(1);
    unk174->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, unk174);
    y += 30.0f;
    LibObject178750* primary_heading = new (0) LibObject178750;
    primary_heading->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x15F92, 1);
    primary_heading->set_mode(1);
    primary_heading->set_scale(0.8f, 0.8f);
    primary_heading->set_color(0x808050);
    func_004C6190(unk10, primary_heading);
    y += 22.0f;
    unk17c = new (0) LibObject178750;
    (static_cast<LibObject178750*>(unk17c))->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x15F95, 1);
    unk17c->set_mode(1);
    unk17c->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, unk17c);
    unk17c->unk3f = 0;
    y += 22.0f;
    for (s32 index = 0; index < 8; index++)
    {
        unk180[index] = new (0) LibObject178750;
        (static_cast<LibObject178750*>(unk180[index]))->func_004C7FE0(458.0f + 50.0f * (index % 3), y + 22.0f * (index / 3), 0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_CATEGORY_LABEL_BASE, 1);
        unk180[index]->set_scale(0.7f, 0.7f);
        func_004C6190(unk10, unk180[index]);
        unk180[index]->unk3f = 0;
    }
    y += 70.0f;
    unk1a4[0] = new (0) LibObject178750;
    (static_cast<LibObject178750*>(unk1a4[0]))->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x3584, 1);
    unk1a4[0]->set_mode(1);
    unk1a4[0]->set_scale(0.8f, 0.8f);
    unk1a4[0]->set_color(0x288080);
    func_004C6190(unk10, unk1a4[0]);
    unk1a4[0]->unk3f = 0;
    y += 23.0f;
    unk1a4[1] = new (0) LibObject178750;
    (static_cast<LibObject178750*>(unk1a4[1]))->func_004C7FE0(490.0f, y, 0.0f, 0.0f, (s32)associated, ITEM_CREATION_CATEGORY_LABEL_BASE, 1);
    unk1a4[1]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, unk1a4[1]);
    unk1a4[1]->unk3f = 0;
    unk1a4[2] = new (0) LibObject174F20;
    func_00464D90(static_cast<LibObject174F20*>(unk1a4[2]), 99, (s32)associated, 1, 528.0f, y, 38.4f, 19.2f);
    unk1a4[2]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, unk1a4[2]);
    unk1a4[2]->unk3f = 0;
    y += 30.0f;
    LibObject178750* alternate_heading = new (0) LibObject178750;
    (alternate_heading)->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x15F93, 1);
    alternate_heading->set_mode(1);
    alternate_heading->set_scale(0.8f, 0.8f);
    alternate_heading->set_color(0x808050);
    func_004C6190(unk10, alternate_heading);
    y += 22.0f;
    unk1b4 = new (0) LibObject178750;
    (static_cast<LibObject178750*>(unk1b4))->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x15F95, 1);
    unk1b4->set_mode(1);
    unk1b4->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, unk1b4);
    unk1b4->unk3f = 0;
    y += 22.0f;
    for (s32 index = 0; index < 8; index++)
    {
        unk1b8[index] = new (0) LibObject178750;
        (static_cast<LibObject178750*>(unk1b8[index]))->func_004C7FE0(458.0f + 50.0f * (index % 3), y + 22.0f * (index / 3), 0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_CATEGORY_LABEL_BASE, 1);
        unk1b8[index]->set_scale(0.7f, 0.7f);
        func_004C6190(unk10, unk1b8[index]);
        unk1b8[index]->unk3f = 0;
    }
    y += 70.0f;
    unk1dc[0] = new (0) LibObject178750;
    (static_cast<LibObject178750*>(unk1dc[0]))->func_004C7FE0(444.0f, y, 168.0f, 396.0f, (s32)associated, 0x3584, 1);
    unk1dc[0]->set_mode(1);
    unk1dc[0]->set_color(0x288080);
    unk1dc[0]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, unk1dc[0]);
    unk1dc[0]->unk3f = 0;
    y += 23.0f;
    unk1dc[1] = new (0) LibObject178750;
    (static_cast<LibObject178750*>(unk1dc[1]))->func_004C7FE0(490.0f, y, 0.0f, 0.0f, (s32)associated, ITEM_CREATION_CATEGORY_LABEL_BASE, 1);
    unk1dc[1]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, unk1dc[1]);
    unk1dc[1]->unk3f = 0;
    unk1dc[2] = new (0) LibObject174F20;
    func_00464D90(static_cast<LibObject174F20*>(unk1dc[2]), 99, (s32)associated, 1, 528.0f, y, 38.4f, 19.2f);
    unk1dc[2]->set_scale(0.8f, 0.8f);
    func_004C6190(unk10, unk1dc[2]);
    unk1dc[2]->unk3f = 0;
    return 1;
}

void func_00352B00(ItemCreationFourPositionDisplay* object, float x, float y)
{
    object->unk1c = shifted_position(x, 12.0f);
    object->unk20 = y;
    object->unk40 = 1;
    object->unk130 = shifted_position(x, 240.0f) - 20.0f;
    object->unk134 = y;
    object->unk154 = 1;
    object->unk244 = shifted_position(x, 345.0f) - 8.0f;
    object->unk248 = y;
    object->unk268 = 1;
    object->unk358 = shifted_position(x, 412.0f);
    object->unk35c = y;
    object->unk37c = 1;
}

/**
 * @brief Find a single-channel category record.
 * @param index Category minus one.
 * @return Record at that index.
 */
static inline const ItemCreationSingleIconRecord* single_icon_record(s32 index)
{
    return &D_501DA0[index];
}

/**
 * @brief Build the mask of channels a category can use.
 * @param category Detail category.
 * @return All nine channel bits for extended categories, otherwise the record's channel bit.
 */
static inline u16 category_channel_flags(u8 category)
{
    if (has_extended_icons(category))
    {
        return 0x1FF;
    }
    return 1 << (single_icon_record(category - 1)->unk03 - 1);
}

/**
 * @brief Test whether a channel is absent from a channel mask.
 * @param flags Channel mask.
 * @param index Channel index.
 * @return True when the channel's bit is clear.
 */
static inline bool channel_missing(u16 flags, s32 index)
{
    return !(flags & (1 << index));
}

/**
 * @brief Show the texts for one available option row.
 * @param source Option container supplying the text resource.
 * @param index Position among the available option records.
 */
void ItemCreationClass186050::func_slot10(LibClass1721F0* source, s32 index)
{
    void* text_source = static_cast<ItemCreationClass185F60*>(source)->unk4b4;
    ItemCreationRuntimeOptionRecord* records[28];
    s32 count = 0;
    for (s32 position = 0; position < 28; position++)
    {
        ItemCreationRuntimeOptionRecord* record = runtime_option_record(D_001B64F8, static_cast<u8>(position + 1));
        if (record->unk08 != 0)
        {
            records[count++] = record;
        }
    }
    ItemCreationRuntimeOptionRecord** selected = &records[index];
    func_4C6DF0(&unk04, text_source, (*selected)->unk06 + 0x3584, 0);
    func_4C6DF0(&unk118, text_source, (*selected)->unk08 + 0x15FB7, 0);
    if ((*selected)->unk08 == 2)
    {
        unk118.set_color(0x505080);
    }
    else
    {
        unk118.set_color(0x805050);
    }
    u8 category = (*selected)->unk06;
    s32 channel_index = 0;
    u16 flags = category_channel_flags(category);
    for (s32 channel = 0; channel < 8; channel++)
    {
        if (!channel_missing(flags, channel))
        {
            channel_index = channel;
            break;
        }
    }
    func_4C6DF0(&unk22c, text_source, channel_index + 0x3458, 0);
    func_4C6DF0(&unk340, text_source, ((*selected)->unk0a != 0) + 0x15FB6, 0);
}

void func_00352DC0(u8* object, u32 unused, u8 value)
{
    object[0x41] = value;
    object[0x155] = value;
    object[0x269] = value;
    object[0x37D] = value;
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
    ItemCreationColorRecordState* records = D_001B64F8;
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
    ItemCreationColorRecordState* records = D_001B64F8;
    if (valid_category_index(index))
    {
        return &records->categories[index - 1];
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
void func_00352DE0(ItemCreationClass186070* object)
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
s32 ItemCreationClass186070::func_slotb0()
{
    func_slot20(0);
    unke8->unkab = 0;
    FieldClass15AE70* alternate = static_cast<FieldClass15AE70*>(func_slot4c());
    if (alternate != 0)
    {
        static_cast<ItemCreationClass186A70*>(alternate)->func_003598E0(3, 1);
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
        ItemCreationClass186370* next = new (0) ItemCreationClass186370;
        next->func_slotf4(unka8->func_00263CC0());
        unka8->func_00263FD0(next);
        unka8->func_00263C70(next);
        func_00112400(D_001B65F8, 8, 0, 0, 127, 64, 0);
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003537A0);

/** @brief Release the container and base window contents. */
void ItemCreationClass186070::func_slot0c()
{
    unke8->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

/**
 * @brief Detach the owned panel and destroy the selected item window.
 */
ItemCreationClass186070::~ItemCreationClass186070()
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
ItemCreationClass186070::ItemCreationClass186070(ItemCreationSelectedDisplayState* object)
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
s32 ItemCreationClass186170::func_slotb0()
{
    D_001B643C->unk10->unk14->func_00263F50(this);
    ItemCreationPopupReturnParent* parent = static_cast<ItemCreationPopupReturnParent*>(func_slot44());
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
s32 ItemCreationClass186170::func_slotf4(void* associated)
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
s32 ItemCreationClass186270::func_slotb0()
{
    D_001B643C->unk10->unk14->func_00263F50(this);
    ItemCreationPopupReturnParent* parent = static_cast<ItemCreationPopupReturnParent*>(func_slot44());
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
s32 ItemCreationClass186270::func_slotf4(void* associated)
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
s32 ItemCreationClass186370::func_slotb0()
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
            func_003698E0(state, 0);
        }
        if (state->unk1b4[1] != 0)
        {
            func_003698E0(state, 1);
        }
        if (state->unk1b4[2] != 0)
        {
            func_003698E0(state, 2);
        }
        state->unk19a = 0;
    }
    return 1;
}

/**
 * @brief Restore the selected display and open the result window when ready.
 * @return Zero after opening the result window, otherwise one.
 */
s32 ItemCreationClass186470::func_slotb0()
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
        ItemCreationClass186370* next = new (0) ItemCreationClass186370;
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
s32 ItemCreationClass186570::func_slotb0()
{
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    state->func_00263F50(this);
    ItemCreationClass186070* window = state->unke0;
    func_00352DE0(window);
    window->func_slot20(1);
    window->unke8->unkab = 1;
    D_001B643C->unk10->unk14->func_00263C70(window);
    return 1;
}

void func_00355670(ItemCreationTwoColorList* object)
{
    if (object->unkac != 0 && (u8)func_23B3B0(object->unkac, 1) != 1)
    {
        u16 selected = func_23B3A0(object->unkac);
        if (object->unkac != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                ItemCreationColorDisplay* display = (ItemCreationColorDisplay*)func_0036F230(&object->unk2c, index)->unk00;
                if (index == selected)
                {
                    display->unk94 = ITEM_CREATION_COLOR_SELECTED;
                    display->unk3c = 1;
                    func_0023B7E0(object->unkb0, (FieldTarget23B850*)display);
                }
                else
                {
                    display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                    display->unk3c = 1;
                }
            }
        }
    }
}

void func_00355740(ItemCreationTwoColorList* object)
{
    if (object->unkac != 0 && (u8)func_23B3B0(object->unkac, 0) != 1)
    {
        u16 selected = func_23B3A0(object->unkac);
        if (object->unkac != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                ItemCreationColorDisplay* display = (ItemCreationColorDisplay*)func_0036F230(&object->unk2c, index)->unk00;
                if (index == selected)
                {
                    display->unk94 = ITEM_CREATION_COLOR_SELECTED;
                    display->unk3c = 1;
                    func_0023B7E0(object->unkb0, (FieldTarget23B850*)display);
                }
                else
                {
                    display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                    display->unk3c = 1;
                }
            }
        }
    }
}

/** @brief Restore the two display colors and associated resource window. @return Always two. */
s32 ItemCreationClass186670::func_slotb4()
{
    func_slot20(0);
    func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkac)), 1);
    if (unkac != 0)
    {
        s32 index;
        for (index = 0; index < 2; index++)
        {
            LibObject178750* display = static_cast<LibObject178750*>(
                func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index)->unk00);
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
        static_cast<ItemCreationClass186A70*>(unka8->unkb4)->func_003598E0(3, 1);
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
s32 ItemCreationClass186670::func_slotb0()
{
    if (unkac == 0)
    {
        return 0;
    }
    switch (func_23B3A0(reinterpret_cast<FieldState23B3A0*>(unkac)))
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
                        func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index)->unk00);
                    if (index == 1)
                    {
                        display->set_color(0x288080);
                        func_0023B7E0(static_cast<FieldObject23B950*>(static_cast<void*>(unkb0)),
                        static_cast<FieldTarget23B850*>(static_cast<void*>(display)));
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
                ItemCreationClass186470* next = new (0) ItemCreationClass186470;
                next->func_slotf4(unka8->func_00263CC0());
                unka8->func_00263FD0(next);
                unka8->func_00263C70(next);
                func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
            }
            else
            {
                ItemCreationClass186070* alternate = static_cast<ItemCreationClass186070*>(func_slot4c());
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
s32 ItemCreationClass186670::func_slotf4(void* associated)
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
    LibObject178750* target = static_cast<LibObject178750*>(func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), 1)->unk00);
    unkb0 = new (0) FieldClass153170;
    unkb0->func_0023B850(target, 0x288080);
    func_004C6190(unk10, unkb0);
    if (unkac != 0)
    {
        s32 index;
        for (index = 0; index < 2; index++)
        {
            LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index)->unk00);
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
ItemCreationClass186670::~ItemCreationClass186670()
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
    ItemCreationClass185E60* next = unka8->unke8;
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
    ItemCreationClass186A70* parent = static_cast<ItemCreationClass186A70*>(func_slot44());
    if (parent != 0)
    {
        parent->func_003598E0(4, 1);
    }
    if (unka8 != 0)
    {
        unka8->unk1b0 = static_cast<u8>(static_cast<u16>(unk10c->unk114));
    }
    unk110->func_slot20(1);
    ItemCreationClass186670* next = unk110;
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00357120);

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

s32 ItemCreationClass186870::func_slotb4()
{
    ItemCreationSelectionRestoreParent* parent = static_cast<ItemCreationSelectionRestoreParent*>(func_slot44());
    if (parent != 0)
    {
        func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(unkb4)), 1);
        unkac->set_color(ITEM_CREATION_COLOR_BRIGHT);
        unkb0->set_color(ITEM_CREATION_COLOR_SELECTED);
        func_0023B7E0(static_cast<FieldObject23B950*>(static_cast<void*>(unkb8)),
                     static_cast<FieldTarget23B850*>(static_cast<void*>(unkb0)));
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

s32 ItemCreationClass186870::func_slotb0()
{
    FieldState23B3A0* selector = static_cast<FieldState23B3A0*>(static_cast<void*>(unkb4));
    if (func_23B3A0(selector) == 0)
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

void func_00358240(ItemCreationDirectColorOwner* object)
{
    if (object->unkb4 != 0 && !selector_inactive(object->unkb4) && (u8)func_23B3B0(object->unkb4, 1) != 1)
    {
        u16 selected = func_23B3A0(object->unkb4);
        switch (selected)
        {
        case 0:
        {
            ItemCreationColorDisplay* first = object->unkac;
            ItemCreationColorDisplay* second;
            first->unk94 = ITEM_CREATION_COLOR_SELECTED;
            first->unk3c = 1;
            second = object->unkb0;
            second->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            second->unk3c = 1;
            func_0023B7E0(object->unkb8, (FieldTarget23B850*)object->unkac);
            break;
        }
        case 1:
        {
            ItemCreationColorDisplay* first = object->unkac;
            ItemCreationColorDisplay* second;
            first->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            first->unk3c = 1;
            second = object->unkb0;
            second->unk94 = ITEM_CREATION_COLOR_SELECTED;
            second->unk3c = 1;
            func_0023B7E0(object->unkb8, (FieldTarget23B850*)object->unkb0);
            break;
        }
        }
    }
}

void func_00358340(ItemCreationDirectColorOwner* object)
{
    if (object->unkb4 != 0 && !selector_inactive(object->unkb4) && (u8)func_23B3B0(object->unkb4, 0) != 1)
    {
        u16 selected = func_23B3A0(object->unkb4);
        switch (selected)
        {
        case 0:
        {
            ItemCreationColorDisplay* first = object->unkac;
            ItemCreationColorDisplay* second;
            first->unk94 = ITEM_CREATION_COLOR_SELECTED;
            first->unk3c = 1;
            second = object->unkb0;
            second->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            second->unk3c = 1;
            func_0023B7E0(object->unkb8, (FieldTarget23B850*)object->unkac);
            break;
        }
        case 1:
        {
            ItemCreationColorDisplay* first = object->unkac;
            ItemCreationColorDisplay* second;
            first->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            first->unk3c = 1;
            second = object->unkb0;
            second->unk94 = ITEM_CREATION_COLOR_SELECTED;
            second->unk3c = 1;
            func_0023B7E0(object->unkb8, (FieldTarget23B850*)object->unkb0);
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
s32 ItemCreationClass185860::func_slotf4(void* associated)
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
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(resource)), record, offset + 64.0f * (index % 6), 8.0f);
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
extern "C" s32 func_003501B0(ItemCreationClass185B60* object, void* associated)
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
s32 ItemCreationClass186370::func_slotf4(void* associated)
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
s32 ItemCreationClass186470::func_slotf4(void* associated)
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
s32 ItemCreationClass186570::func_slotf4(void* associated)
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


/** String-backed drawing widget with MAIN vtable at 0x175140. */
struct LibObject175140 : public LibClass174EF0
{
    /** @brief Initialize the string-backed drawing widget. */
    LibObject175140()
    {
        unk38 = 14;
    }
    /** @brief Destroy the string-backed drawing widget. */
    virtual ~LibObject175140();
    /**
     * @brief Configure the drawing rectangle and string.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param width Drawing width.
     * @param height Drawing height.
     * @param value String to draw.
     * @param flag Drawing flag.
     * @return Configuration status.
     */
    s32 func_00467AD0(float x, float y, float width, float height, const char* value, u8 flag);
    const char* unkfc;
};

/** Partial parent containing the Field selection marker. */
struct ItemCreationTwoColorReturnParent
{
    u8 unk00[0xB4];
    FieldObject23CEA0* unkb4;
};


/** Partial display containing the mode used to select item predicates. */
struct ItemCreationModeDisplay
{
    u8 unk00[0x14C];
    u8 unk14c;
};

/** Partial category display containing its selection state and mode display. */
struct ItemCreationCategoryOwner
{
    u8 unk00[0x1A0];
    ItemCreationSelectedDisplayState* unk1a0;
    u8 unk1a4[0x78];
    ItemCreationModeDisplay* unk21c;
};


/** Partial row display containing its color, record code, and update markers. */
struct ItemCreationRowDisplay
{
    u8 unk00[0x1C];
    float unk1c;
    u8 unk20[0x1C];
    u8 unk3c;
    u8 unk3d;
    u8 unk3e[0x56];
    u32 unk94;
    u8 unk98[0x64];
    u16 unkfc;
    u8 unkfe;
};

/** Partial resource display containing its update and visibility markers. */
struct ItemCreationRowResourceDisplay
{
    u8 unk00[0x1C];
    float unk1c;
    u8 unk20[0x1C];
    u8 unk3c;
    u8 unk3d;
};

/** Partial owner of six display pairs, the selection state, and category identifier. */
struct ItemCreationIdentifierOwner
{
    u8 unk00[0x130];
    s32 unk130;
    u8 unk134[4];
    ItemCreationRowDisplay* unk138[6];
    ItemCreationRowResourceDisplay* unk150[6];
    u8 unk168[0x4C];
    ItemCreationSelectedDisplayState* unk1b4;
    u8 unk1b8[4];
    s32 unk1bc;
};


/** Partial panel marker containing its visibility flag. */
struct ItemCreationPanelMarker
{
    u8 unk00[0x3F];
    u8 unk3f;
};

/** Partial resource display containing its active flag and resource byte. */
struct ItemCreationIndexedResourceDisplay
{
    u8 unk00[0x3F];
    u8 unk3f;
    u8 unk40[0x90];
    u8 unkd0;
};

/** Shared partial prefix of the nine- and fourteen-slot selection windows. */
struct ItemCreationSelectionMarkerView
{
    u8 unk00[0xA8];
    ItemCreationSelectedDisplayState* unka8;
    u8 unkac[8];
    FieldObject23CEA0* unkb4;
};

/** Partial Field context containing the selected display state. */
struct ItemCreationFieldContext
{
    u8 unk00[0x14];
    FieldClass153E30* unk14;
};

/** Partial controls containing the mode-list activation flag. */
struct ItemCreationControlState
{
    u8 unk00[0x9A];
    u8 unk9a;
};
/** Partial display marker containing its update byte and scalar field. */
struct ItemCreationPanelReturnMarker
{
    u8 unk00[0xAE];
    u8 unkae;
    u8 unkaf[0x31];
    float unke0;
};

/** Partial associated parent containing its selection marker. */
struct ItemCreationPanelReturnParent
{
    u8 unk00[0xAC];
    ItemCreationPanelReturnMarker* unkac;
};

/** Partial associated parent containing its selection marker and group. */
struct ItemCreationModeReturnParent
{
    u8 unk00[0xB4];
    FieldObject23CEA0* unkb4;
    u8 unkb8[0x138];
    u8 unk1f0;
};
/** Partial resident directory containing the Field context and item-resource buffers. */
typedef struct ItemCreationResourceDirectory
{
    struct ItemCreationCheckedRecord* unk00;
    u8 unk04[8];
    ItemCreationControlState* unk0c;
    ItemCreationFieldContext* unk10;
    u8 unk14[0xC];
    FieldBufferSlots* unk20;
} ItemCreationResourceDirectory;

/** Partial record containing a checked value and its checksum fields. */
typedef struct ItemCreationCheckedRecord
{
    u8 unk00[0x34];
    u32 unk34;
    u8 unk38[0x6C];
    u16 unka4;
    u16 unka6;
} ItemCreationCheckedRecord;

/** Partial resident services containing the item-selection context. */
struct ItemCreationRecordServices
{
    u8 unk00[0x58];
    void* unk58;
};

/** Partial resident directory containing the current checked record. */
typedef struct ItemCreationRecordDirectory6430
{
    ItemCreationRecordServices* unk00;
    ItemCreationCheckedRecord* unk04;
} ItemCreationRecordDirectory6430;

/** String record with its text beginning at field 0x20. */
struct ItemCreationStringRecord
{
    u8 unk00[0x20];
    char unk20;
    u8 unk21[0xF3];
};
/** Partial selection containing the string-record array. */
struct ItemCreationStringSelection
{
    void* unk00;
    ItemCreationStringRecord* unk04;
};
/** Detail record containing its icon category. */
struct ItemCreationDetailRecord
{
    u8 unk00[6];
    u8 unk06;
    u8 unk07[5];
};
/** Partial runtime state containing the thirty-eight detail records. */
struct ItemCreationDetailRecords
{
    u8 unk00[0x10D88];
    ItemCreationDetailRecord records[38];
};

// These external interfaces are scoped here because their owning code is in other overlays.
extern "C"
{
    extern ResidentRequest112400* D_001B65F8;
    extern ItemCreationCategoryDefinition* D_001B64F0;
    extern const char D_0036F738[];
    u16 func_457470(u16 seed, const u8* buffer, s32 length);
    u32 func_23B3B0(FieldState23B3A0* item, u16 flag);
    u16 func_23B3A0(FieldState23B3A0* item);
    /** @brief Select the mode display state. @param object Mode window. @param mode Display mode. */
    void func_0035D7C0(ItemCreationClass186DB0* object, u8 mode);
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
 * @brief Allocate the panel transform and set its third coordinate.
 * @param object Panel widget.
 * @param z Third transform component.
 * @return One on success, or zero if the transform could not be allocated.
 */
s32 func_4C4AB0(LibClass178630* object, float z);
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
/**
 * @brief Configure the list indicator's rectangle and scalar pair.
 * @param object List indicator widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param height Rectangle height.
 * @param first First scalar value.
 * @param second Second scalar value.
 * @return One on success, or zero if its storage could not be initialized.
 */
s32 func_41A930(ItemCreationClass1725D0* object, float x, float y, float height, float first, float second);

/**
 * @brief Initialize an item widget's rectangle and item codes.
 * @param object Item widget.
 * @param value Halfword item code.
 * @param variant Byte item variant.
 * @param flag Drawing state flag.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero if its drawing storage could not be initialized.
 */
s32 func_413F70(LibObject172410* object, u16 value, u8 variant, u8 flag, float x, float y, float width, float height);
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
s32 func_4143F0(LibObject172440* object, u16 value, u8 variant, u8 flag, float x, float y, float width, float height);
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
void func_00365F20(ItemCreationClass1872B0* object);
/** @brief Reset the grid indices and update its position. @param object Grid receiver. */
void func_0023C710(FieldObject23CEA0* object);

}

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


static inline bool valid_record_index_middle(s16 index);
static inline ItemCreationAllocationRecord* allocation_record_middle(s32 value);
static inline bool allocation_invalid_middle(ItemCreationAllocationRecord* record);
static inline u16 allocation_value_middle(ItemCreationAllocationRecord* record);
static inline u32 item_resource_index_middle(u8 value);
static inline u32 item_available_resource_index(u16 value);
static inline u32 item_assigned_code(u8 value);
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
 * @brief Convert an item byte to its allocation-table index.
 * @param value Item byte; zero denotes no item.
 * @return Zero for no item, or the item byte minus eleven.
 */
static inline u32 item_resource_index_middle(u8 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 11;
}

/**
 * @brief Convert a halfword resource code to its allocation-table index.
 * @param value Resource code; zero denotes no resource.
 * @return Zero for no resource, or the resource code minus eleven.
 */
static inline u32 item_available_resource_index(u16 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 11;
}

/**
 * @brief Convert an item byte to its assigned-item code.
 * @param value Item byte; zero denotes no item.
 * @return Zero for no item, or the item byte minus thirty-one.
 */
static inline u32 item_assigned_code(u8 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 31;
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
static inline ItemCreationDetailRecord* detail_record(s32 value)
{
    ItemCreationDetailRecords* table = static_cast<ItemCreationDetailRecords*>(static_cast<void*>(D_001B64F8->records));
    u8 index = value;
    if (valid_detail_index(index))
    {
        return &table->records[index - 1];
    }
    return 0;
}

/**
 * @brief Refresh a detail channel using the selected record and enabled mask.
 * @param object Detail window.
 * @param record Selected detail record.
 * @param index Channel index from zero through seven.
 */
static inline void refresh_detail_channel(ItemCreationClass186970* object, ItemCreationDetailRecord* record, s32 index)
{
    if (object->unk102 & (1 << index))
    {
        if (index != 0)
        {
            object->unkb8[index]->unk3d = 1;
        }
        u8 icon = detail_icon(record->unk06, index);
        LibObject174F20* image = object->unkdc[index];
        image->unkfc = icon;
        image->unk3c = 1;
        object->unkdc[index]->unk3d = 1;
        object->unkb8[index]->set_color(0x808080);
        object->unkdc[index]->set_color(0x808080);
    }
    else
    {
        object->unkb8[index]->set_color(0x505050);
    }
}

s32 ItemCreationClass186870::func_slotf4(void* associated)
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

ItemCreationClass186870::~ItemCreationClass186870()
{
}

void ItemCreationClass186970::func_00358850()
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
    void* allocation = func_002D3D80(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, resource);
    FieldResourceRecord* source = func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 81);
    func_002D5CF0(static_cast<FieldResourceDisplay2D5CF0*>(static_cast<void*>(unkac)), allocation, source, resource);
    unkac->unk3d = 1;
    if ((u8)resource > 59)
    {
        s8 index = func_0028E240(selection, unk101 - 59);
        ItemCreationStringSelection* strings = static_cast<ItemCreationStringSelection*>(static_cast<void*>(selection));
        LibObject175140* display = unkb0;
        display->unkfc = &strings->unk04[index].unk20;
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
    ItemCreationDetailRecord* record = detail_record(item_assigned_code(unk101));
    if (record != 0)
    {
        refresh_detail_channel(this, record, 0);
        refresh_detail_channel(this, record, 1);
        refresh_detail_channel(this, record, 2);
        refresh_detail_channel(this, record, 3);
        refresh_detail_channel(this, record, 4);
        refresh_detail_channel(this, record, 5);
        refresh_detail_channel(this, record, 6);
        refresh_detail_channel(this, record, 7);
    }
}

s32 ItemCreationClass186970::func_slotf4(void* associated)
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
    void* allocation = func_002D3D80(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 49);
    FieldResourceRecord* record = func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 81);
    unkac = new (0) ItemCreationOptionResourceDisplay;
    unkac->unkcc = allocation;
    unkac->unkd0 = 49;
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unkac)), record, 22.0f, 18.0f);
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
        unkb8[index]->func_004C7FE0(x, y, 0.0f, 0.0f, (s32)associated, ITEM_CREATION_CATEGORY_LABEL_BASE + index, 1);
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

ItemCreationClass186970::~ItemCreationClass186970()
{
}

ItemCreationClass186970::ItemCreationClass186970()
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

void ItemCreationClass186A70::func_003598E0(u16 mode, u32 unused)
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

void func_00359C80(ItemCreationTwoCheckedValueOwner* object)
{
    if (object->unkd0 != 0)
    {
        ItemCreationCheckedRecord* record = static_cast<ItemCreationRecordDirectory6430*>(static_cast<void*>(D_001B6430))->unk04;
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        ItemCreationValueDisplay* display;
        u32 value;

        if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26),
            end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        display = object->unkd0;
        display->unkfc = value;
        display->unk3c = 1;
    }
    if (object->unkd8 != 0)
    {
        ItemCreationCheckedRecord* record = static_cast<ItemCreationRecordDirectory6430*>(static_cast<void*>(D_001B6430))->unk04;
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        ItemCreationValueDisplay* display;
        u32 value;

        if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26),
            end - ((const u8*)record + 0x26)))
        {
            value = 0;
        }
        else
        {
            value = record->unk34 ^ 0x7CE3C7F7;
        }
        display = object->unkd8;
        display->unkfc = value;
        display->unk3c = 1;
    }
}

s32 ItemCreationClass186A70::func_slotf4(void* associated)
{
    unkdc = 168.0f;
    unke0 = 160.0f;
    unke4 = 176.0f;
    func_002CE760(this, associated, 0, 9, 1800, 460.0f, 72.0f, 0.0f);
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
    void* data = func_002D3D80(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 0);
    unkcc->unkcc = data;
    unkcc->unkd0 = 0;
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unkcc)),
        func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 25), 5.0f, 126.0f);
    {
        ItemCreationCheckedRecord* record = static_cast<ItemCreationRecordDirectory6430*>(static_cast<void*>(D_001B6430))->unk04;
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        u32 value;
        if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26), end - ((const u8*)record + 0x26)))
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
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unkd4)),
        func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 25), 5.0f, 140.0f);
    {
        ItemCreationCheckedRecord* record = static_cast<ItemCreationRecordDirectory6430*>(static_cast<void*>(D_001B6430))->unk04;
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        u32 value;
        if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26), end - ((const u8*)record + 0x26)))
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

ItemCreationClass186A70::~ItemCreationClass186A70()
{
}

ItemCreationClass186A70::ItemCreationClass186A70()
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

void ItemCreationClass186B70::func_slot10c(u32 value, u32 alternate)
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

s32 ItemCreationClass186B70::func_slotb8()
{
    ItemCreationAllocationRecord* records[99];
    ItemCreationSelectedDisplayState* state =
        static_cast<ItemCreationSelectedDisplayState*>(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14);
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

s32 ItemCreationClass186B70::func_slotb4()
{
    ItemCreationSelectedDisplayState* state =
        static_cast<ItemCreationSelectedDisplayState*>(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14);
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
        static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(parent);
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
s32 ItemCreationClass186B70::func_slotb0()
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
    if (func_0035B310(static_cast<ItemCreationIdentifierOwner*>(static_cast<void*>(this)), record))
    {
        return 3;
    }
    s16 identifier = func_0040D890(record);
    ItemCreationClass1870B0* parent = unk1b4->unkbc;
    u8 group;
    ItemCreationClass186DB0* mode = unk1b4->unkd0;
    group = parent->unk1f0;
    if (mode != 0)
    {
        if (mode->unk14c == 0)
        {
            close_category(active, this);
            func_0035E150(static_cast<ItemCreationCheckedAllocationView*>(static_cast<void*>(mode)), identifier, -1, 0);
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
            func_003698E0(unk1b4, group);
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
            func_003698E0(unk1b4, parent->unk1f0);
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
void ItemCreationClass186B70::func_slot5c()
{
    ItemCreationAllocationRecord* records[99];
    if (static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00261150() == this && unk1b0 == 0)
    {
        func_002CD7C0(this);
    }
    else if (unk1b0 == 0)
    {
        func_002CDFB0(&static_cast<FieldStateCE420&>(*this));
    }
    if (static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00261150() == this)
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

bool func_0035B310(ItemCreationIdentifierOwner* object, const ItemCreationAllocationRecord* record)
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

void ItemCreationClass186B70::set_scroll_position(float start)
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

void ItemCreationClass186B70::refresh_rows(s32 start)
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
            if (func_0035B310(static_cast<ItemCreationIdentifierOwner*>(static_cast<void*>(this)), record))
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
            void* allocation = func_002D3D80(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 14);
            FieldResourceRecord* resource = func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, count + 60);
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
s32 ItemCreationClass186B70::func_slot104(void* associated)
{
    ItemCreationAllocationRecord* records[99];
    func_002CE760(this, associated, 0, 9, 2600, 25.0f, 83.0f, 0.0f);
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
    void* allocation = func_002D3D80(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 14);
    for (s32 index = 0; index < 6; index++)
    {
        FieldResourceRecord* record = func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 60);
        unk150[index] = new (0) ItemCreationOptionResourceDisplay;
        unk150[index]->unkcc = allocation;
        unk150[index]->unkd0 = 14;
        float y = 16.0f + 28.0f * index;
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unk150[index])), record, 30.0f, y);
        ItemCreationOptionResourceDisplay* resource = unk150[index];
        resource->unk50.unk34 = 0.95f;
        resource->unk50.unk30 = 0.95f;
        resource->unk3c = 1;
        unk150[index]->unk3f = 0;
        func_004C6190(unk10, unk150[index]);
        unk138[index] = new (0) LibObject172410;
        func_413F70(unk138[index], 100, 0, 0, 60.0f, y, 323.99997f, 21.599998f);
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
    func_413F70(unk1a8, 0, 0, 0, 24.0f, 34.0f, 561.6f, 31.199999f);
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
    func_467360(static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04), 28.0f, 28.0f);
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
    unk1b4 = static_cast<ItemCreationSelectedDisplayState*>(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14);
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

void ItemCreationClass186B70::func_slot110(u8 value)
{
    unk84 = value;
}

#include "overlays/lib/text_004BD360.h"

/** @brief Release the category container and its base window contents. */
void ItemCreationClass186B70::func_slot0c()
{
    unk1ac->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

ItemCreationClass186B70::~ItemCreationClass186B70()
{
    if (unk18c != 0)
    {
        func_004C4A90(unk18c);
    }
}

void func_0035C4D0(u8* object, void* unused, u32 value)
{
    u8* nested = *(u8**)(object + 0xAC);
    if (nested != 0)
    {
        nested[0x3F] = value;
        if (value != 0)
        {
            nested = *(u8**)(object + 0xAC);
            *(float*)(nested + 0x70) = 128.0f;
            nested[0x3C] = 1;
        }
        else
        {
            nested = *(u8**)(object + 0xAC);
            *(float*)(nested + 0x70) = 64.0f;
            nested[0x3C] = 1;
        }
    }
}

/** @brief Restore the mode window or its parent selection. @return Always two. */
s32 ItemCreationClass186C90::func_slotb4()
{
    func_slot10c(0, 0);
    ItemCreationClass186DB0* mode = static_cast<ItemCreationClass186DB0*>(func_slot44());
    if (mode != 0)
    {
        if (mode->unk14c == 0)
        {
            ItemCreationModeReturnParent* parent = static_cast<ItemCreationModeReturnParent*>(mode->func_slot44());
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
            static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(parent);
        }
        else
        {
            mode->func_slot64();
            static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(mode);
        }
    }
    return 2;
}

/**
 * @brief Return the category record at the mode list's selected index.
 * @param self Mode list.
 * @return Selected category record, or null.
 */
static inline ItemCreationCategoryRecord* selected_record(ItemCreationClass186C90* self)
{
    return static_cast<ItemCreationCategoryRecord*>(func_0036EF70(&self->unk1a8, self->unk24)->unk00);
}
/** @brief Open the selected category. @return One on activation, three on rejection, or zero when unavailable. */
s32 ItemCreationClass186C90::func_slotb0()
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
        if (func_0035CAD0(static_cast<ItemCreationCategoryOwner*>(static_cast<void*>(this)), record))
        {
            return 3;
        }
    }
    else
    {
        return 3;
    }
    ItemCreationClass186B70* category = new (0) ItemCreationClass186B70;
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
void ItemCreationClass186C90::set_scroll_position(float start)
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
void ItemCreationClass186C90::refresh_rows(s32 start)
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
                    if (func_0035CAD0(static_cast<ItemCreationCategoryOwner*>(static_cast<void*>(this)), record))
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

u8 func_0035CAD0(ItemCreationCategoryOwner* object, const ItemCreationCategoryRecord* category)
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
void ItemCreationClass186C90::func_slot5c()
{
    if (static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00261150() != this)
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
extern "C" void func_0035D0C0(ItemCreationClass186C90* object, s32 mode)
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
s32 ItemCreationClass186C90::func_slot104(void* associated)
{
    func_002CE760(this, associated, 0, 9, 2400, 220.0f, 128.0f, 0.0f);
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
        static_cast<LibObject178750*>(unk138[index])->func_004C7FE0(326.0f, y - 4.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 2020, 1);
        func_00464D90(static_cast<LibObject174F20*>(unk168[index]), index, reinterpret_cast<s32>(associated), 1, 334.0f, y, 28.0f, 24.0f);
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
    func_467360(static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04), 20.0f, 28.0f);
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
ItemCreationClass186C90::ItemCreationClass186C90(ItemCreationSelectedDisplayState* state)
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

void func_0035E150(ItemCreationCheckedAllocationView* object, s16 value, s32 quantity, s8 index)
{
    object->unk10c = value;
    if (object->unk10c != 0)
    {
        ItemCreationAllocationRecord* record = allocation_record_middle(object->unk10c);
        u16 decoded = allocation_value_middle(record);
        u8 flag = record->unk0c & 0x7F;
        ItemCreationAllocationDisplay* display = object->unk11c[index];
        display->unkfc = decoded + 1;
        display->unkfe = flag;
        display->unk3c = 1;
        object->unk11c[index]->unk3f = 1;
        if (quantity == -1)
        {
            object->unk140[index]->unk3f = 0;
            object->unk128[index].unk04->unk3f = 0;
        }
        else
        {
            ItemCreationValueDisplay* quantity_display = object->unk140[index];
            quantity_display->unkfc = quantity;
            quantity_display->unk3c = 1;
            object->unk140[index]->unk3f = 1;
            object->unk128[index].unk04->unk3f = 1;
        }
    }
    else
    {
        object->unk11c[index]->unk3f = 0;
        object->unk128[index].unk04->unk3f = 0;
        object->unk140[index]->unk3f = 0;
    }
}

/**
 * @brief Set a selection marker's depth and mark its actual drawing base for refresh.
 * @param widget Selection marker to update when present.
 * @param depth_field Depth member of the marker's storage base.
 * @param dirty_field Refresh byte of the marker's drawing base.
 * @param depth Depth value.
 */
template<class Widget, class DepthBase, class DirtyBase>
static inline void set_selector_depth(Widget* widget, float DepthBase::* depth_field, u8 DirtyBase::* dirty_field, float depth)
{
    if (widget != 0)
    {
        widget->*depth_field = depth;
        widget->*dirty_field = 1;
    }
}

void func_0035E2D0(u8* object)
{
    u8* nested = *(u8**)(object + 0xAC);
    if (nested != 0)
    {
        *(float*)(nested + 0x70) = 128.0f;
        nested[0x3C] = 1;
    }
}

/**
 * @brief Restore the prior item pair and return to the parent window.
 * @return Always two.
 */
s32 ItemCreationClass186DB0::func_slotb4()
{
    if (unk14c == 1)
    {
        func_0035D7C0(this, 0);
        return 2;
    }
    ItemCreationModeReturnParent* parent = static_cast<ItemCreationModeReturnParent*>(func_slot44());
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
        static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(parent);
    }
    return 2;
}

/**
 * @brief Open the related list while the selection widget is active.
 * @return Zero for a missing or inactive selector; one after opening the list.
 */
s32 ItemCreationClass186DB0::func_slotb0()
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
    set_selector_depth(selector, &ItemCreationClass185050::unk30, &LibClass178600::unk3c, 64.0f);
    func_23B3A0(reinterpret_cast<FieldState23B3A0*>(unkac));
    unk150->func_slot10c(1, 1);
    unk150->func_slot110(1);
    ItemCreationControlState* controls = static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk0c;
    if (controls != 0)
    {
        controls->unk9a = 1;
    }
    static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(unk150);
    return 1;
}

/** @brief Refresh the selected mode colors, marker, and related list. */
void ItemCreationClass186DB0::func_slot6c()
{
    if (unkac != 0 && (u8)func_23B3B0(reinterpret_cast<FieldState23B3A0*>(unkac), 1) != 1)
    {
        u16 raw_index = func_23B3A0(reinterpret_cast<FieldState23B3A0*>(unkac));
        s16 selected = raw_index;
        if (unkac != 0)
        {
            s32 index;
            for (index = 0; index < unkb4; index++)
            {
                ItemCreationListNode* node = func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index);
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
        u8 selection = (u8)func_23B3A0(reinterpret_cast<FieldState23B3A0*>(unkac));
        unk150->func_slot11c(1, selection);
        unk150->func_slot10c(1, 0);
    }
}

/** @brief Refresh the previous mode colors, marker, and related list. */
void ItemCreationClass186DB0::func_slot68()
{
    if (unkac != 0 && (u8)func_23B3B0(reinterpret_cast<FieldState23B3A0*>(unkac), 0) != 1)
    {
        u16 raw_index = func_23B3A0(reinterpret_cast<FieldState23B3A0*>(unkac));
        s16 selected = raw_index;
        if (unkac != 0)
        {
            s32 index;
            for (index = 0; index < unkb4; index++)
            {
                ItemCreationListNode* node = func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index);
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
        u8 selection = (u8)func_23B3A0(reinterpret_cast<FieldState23B3A0*>(unkac));
        unk150->func_slot11c(1, selection);
        unk150->func_slot10c(1, 0);
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0035E770);

ItemCreationClass186DB0::~ItemCreationClass186DB0()
{
}

ItemCreationClass186DB0::ItemCreationClass186DB0(void* object)
{
    unka8 = 0;
    unka8 = static_cast<ItemCreationSelectedDisplayState*>(object);
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
    // The original builds a window base here and destroys it straight away; nothing uses it.
    FieldClass15AE70();
}

/**
 * @brief Reset the choice displays and return to the parent when enabled.
 * @return Always two.
 */
s32 ItemCreationClass186EB0::func_slotb4()
{
    func_slot20(0);
    func_0023B310(reinterpret_cast<FieldObject23B280*>(unkcc));
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
                static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(unka8);
            }
            break;
        }
    }
    return 2;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0035F2D0);

void func_0035F710(ItemCreationTwoColorOwner* object)
{
    if (object->unkcc != 0 && (u8)func_23B3B0(object->unkcc, 1) != 1)
    {
        u16 selected = func_23B3A0(object->unkcc);
        if (object->unkcc != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                ItemCreationColorDisplay* display = object->unkb4[index];
                if (index == selected)
                {
                    display->unk94 = ITEM_CREATION_COLOR_SELECTED;
                    display->unk3c = 1;
                    func_0023B7E0(object->unkd0, (FieldTarget23B850*)display);
                }
                else
                {
                    display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                    display->unk3c = 1;
                }
            }
        }
    }
}

void func_0035F7F0(ItemCreationTwoColorOwner* object)
{
    if (object->unkcc != 0 && (u8)func_23B3B0(object->unkcc, 0) != 1)
    {
        u16 selected = func_23B3A0(object->unkcc);
        if (object->unkcc != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                ItemCreationColorDisplay* display = object->unkb4[index];
                if (index == selected)
                {
                    display->unk94 = ITEM_CREATION_COLOR_SELECTED;
                    display->unk3c = 1;
                    func_0023B7E0(object->unkd0, (FieldTarget23B850*)display);
                }
                else
                {
                    display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                    display->unk3c = 1;
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
s32 ItemCreationClass186EB0::func_slotf4(void* associated)
{
    unka8 = static_cast<ItemCreationTwoColorReturnParent*>(func_slot44());
    if (unka8 == 0)
    {
        return 0;
    }
    unkbc = 382.0f;
    unkc0 = 224.0f;
    unkc4 = 302.0f;
    unkc8 = 380.0f;
    FieldClass15AE70::func_slot10(associated, unkbc, unkc0, 14);
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

ItemCreationClass186EB0::~ItemCreationClass186EB0()
{
}

ItemCreationClass186EB0::ItemCreationClass186EB0(void* object)
{
    unka8 = 0;
    unkac = 0;
    unkb0 = 0;
    unkb4[0] = 0;
    unkb4[1] = 0;
    unkbc = 0;
    unkc0 = 0;
    unkc4 = 0;
    unkc8 = 0;
    unkcc = 0;
    unkd0 = 0;
    unkd4 = 0;
    unkd8 = 0;
    unkd8 = object;
    unkdc = 0;
    unke0 = 0;
}

/**
 * @brief Apply the enabled option color and selected row marker.
 * @param object Option window.
 * @param text Row text display.
 * @param index Row index.
 * @param selected Selected row index.
 * @param mask Selection bit for this category.
 */
static inline void highlight_category_label(ItemCreationClass186FB0* object, LibObject178750* text, s32 index, u16 selected, u16 mask)
{
    if (object->selectable_category_mask & mask)
    {
        text->unk94 = 0x808080;
        text->unk3c = 1;
        if (index == selected)
        {
            text->unk94 = 0x288080;
            text->unk3c = 1;
            object->category_marker->func_0023B7E0(text);
            object->category_marker->unk3f = 1;
        }
    }
}

/**
 * @brief Update the category label colors and the selected row marker.
 * @param object Category selection window.
 * @param selected Selected row index.
 */
extern "C" void item_creation_update_category_labels(ItemCreationClass186FB0* object, u16 selected)
{
    for (s32 index = 0; index < 8; index++)
    {
        LibObject178750* text = object->category_labels[index];
        if (text != 0)
        {
            text->unk94 = 0x505050;
            text->unk3c = 1;
        }
    }
    if (object->category_marker != 0)
    {
        object->category_marker->unk3f = 0;
    }
    for (s32 index = 0; index < 8; index++)
    {
        ItemCreationSelectedDisplayState* state = object->unka8;
        LibObject178750* text = object->category_labels[index];
        if (state->category_enabled[(u8)(index + 1) - 1] != 0)
        {
            if (text != 0)
            {
                text->unk94 = 0x505080;
                text->unk3c = 1;
            }
            switch (index + 1)
            {
            case 1:
                highlight_category_label(object, text, index, selected, ITEM_CREATION_CATEGORY_FLAG_COOK);
                break;
            case 2:
                highlight_category_label(object, text, index, selected, ITEM_CREATION_CATEGORY_FLAG_ALCH);
                break;
            case 3:
                highlight_category_label(object, text, index, selected, ITEM_CREATION_CATEGORY_FLAG_CRFT);
                break;
            case 4:
                highlight_category_label(object, text, index, selected, ITEM_CREATION_CATEGORY_FLAG_CMPD);
                break;
            case 5:
                highlight_category_label(object, text, index, selected, ITEM_CREATION_CATEGORY_FLAG_SMTH);
                break;
            case 6:
                highlight_category_label(object, text, index, selected, ITEM_CREATION_CATEGORY_FLAG_WRIT);
                break;
            case 7:
                highlight_category_label(object, text, index, selected, ITEM_CREATION_CATEGORY_FLAG_ENG);
                break;
            case 8:
                highlight_category_label(object, text, index, selected, ITEM_CREATION_CATEGORY_FLAG_SYTH);
                break;
            }
        }
    }
}


/**
 * @brief Reset the option selection and handle the current return mode.
 * @return Always two.
 */
s32 ItemCreationClass186FB0::func_slotb4()
{
    func_slot20(0);
    func_0023B310(reinterpret_cast<FieldObject23B280*>(category_selector));
    item_creation_update_category_labels(this, 0);
    switch (unkdc)
    {
    case 0:
        if (unkac != 0)
        {
            FieldObject23CEA0* marker = unkac->unkb4;
            marker->FieldClass151C50::unk30 = 128.0f;
            marker->unkae = 1;
            static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(unkac);
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
 * @brief Refresh the option display after selection movement.
 */
void ItemCreationClass186FB0::func_slot6c()
{
    if (category_selector != 0 && (u8)func_23B3B0(reinterpret_cast<FieldState23B3A0*>(category_selector), 1) != 1)
    {
        u16 selected = func_23B3A0(reinterpret_cast<FieldState23B3A0*>(category_selector));
        item_creation_update_category_labels(this, selected);
    }
}
/**
 * @brief Refresh the option display after selection movement.
 */
void ItemCreationClass186FB0::func_slot68()
{
    if (category_selector != 0 && (u8)func_23B3B0(reinterpret_cast<FieldState23B3A0*>(category_selector), 0) != 1)
    {
        u16 selected = func_23B3A0(reinterpret_cast<FieldState23B3A0*>(category_selector));
        item_creation_update_category_labels(this, selected);
    }
}
/**
 * @brief Create the eight category labels and their selection widgets.
 * @param associated Object associated with the window.
 * @return Zero without a parent, otherwise one.
 */
s32 ItemCreationClass186FB0::func_slotf4(void* associated)
{
    unkac = static_cast<ItemCreationTwoColorReturnParent*>(func_slot44());
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
        category_labels[index] = new (0) LibObject178750;
        category_labels[index]->func_004C7FE0(20.0f, 12.0f + 28.0f * index, 0.0f, 0.0f, (s32)associated, index + ITEM_CREATION_CATEGORY_LABEL_BASE, 0);
        func_004C6190(unk10, category_labels[index]);
        if (unka8->category_enabled[(u8)(index + 1) - 1] != 0)
        {
            category_labels[index]->set_color(0x808080);
        }
        else
        {
            category_labels[index]->set_color(0x505050);
        }
    }
    category_selector = new (0) FieldClass153130;
    category_selector->func_0023B530(1, 8, 1, 0, 1, 16.0f, 24.0f, 0.0f, 28.0f);
    func_004C6190(unk10, category_selector);
    category_marker = new (0) FieldClass153170;
    category_marker->func_0023B850(category_labels[0], 0x288080);
    func_004C6190(unk10, category_marker);
    item_creation_update_category_labels(this, 0);
    return 1;
}

ItemCreationClass186FB0::~ItemCreationClass186FB0()
{
}

ItemCreationClass186FB0::ItemCreationClass186FB0(void* object)
{
    unka8 = 0;
    unka8 = static_cast<ItemCreationSelectedDisplayState*>(object);
    unkac = 0;
    panel = 0;
    category_labels[0] = 0;
    category_labels[1] = 0;
    category_labels[2] = 0;
    category_labels[3] = 0;
    category_labels[4] = 0;
    category_labels[5] = 0;
    category_labels[6] = 0;
    category_labels[7] = 0;
    category_selector = 0;
    category_marker = 0;
    unkdc = 0;
    selectable_category_mask = 0;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003608C0);

void func_00360E60(ItemCreationClass1870B0* object, u16 mode)
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

/** @brief Hide the detail window or update its selected item slot. @param selected Nine- or fourteen-slot selection window. */
extern "C" void func_00360FD0(void* selected)
{
    ItemCreationSelectionMarkerView* object = static_cast<ItemCreationSelectionMarkerView*>(selected);
    if (object->unka8 != 0 && object->unkb4 != 0)
    {
        s16 index = object->unkb4->unk114;
        if ((u32)(index - 3) <= 1U || (u32)(index - 8) <= 1U || index == 13 || index == 14)
        {
            ItemCreationClass186970* details = object->unka8->unkc0;
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
        func_0036A500(object->unka8, selected, index);
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
            if (object == static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00261150())
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
            if (object == static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00261150())
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
extern "C" void func_003610D0(ItemCreationClass1870B0* object, u32 active)
{
    update_selection_markers(object, active);
}

void func_00361220(ItemCreationClass1870B0* object)
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

void func_003614B0(ItemCreationClass1870B0* object)
{
    void* allocation;
    u32 resource;
    s32 index;
    u32 value;
    FieldResourceRecord* record;

    object->unk190 = 0;
    for (index = 0; index < 9; index++)
    {
        value = object->unka8->unk68[(u16)index];
        if (value != 0)
        {
            resource = (u8)item_resource_index_middle(value);
            allocation = func_002D3D80(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, resource);
            record = func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 0x51);
            func_002D5CF0(static_cast<FieldResourceDisplay2D5CF0*>(static_cast<void*>(object->unk13c[index])), allocation, record, resource);
            object->unk13c[index]->unk3f = 1;
            object->unk190++;
            object->unk1f2[index] = item_assigned_code(value);
        }
        else
        {
            object->unk13c[index]->unk3f = 0;
            object->unk1f2[index] = 0;
        }
    }
}

/** @brief Apply the selected three-component item. @return Action status. */
s32 ItemCreationClass1870B0::func_slotbc()
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
    ItemCreationCheckedRecord* record = static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk00;
    u16 checksum = record->unka4;
    const u8* end = (const u8*)&record->unka4;
    u32 value;
    if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26), end - ((const u8*)record + 0x26)))
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
        ItemCreationClass186270* popup = new (0) ItemCreationClass186270;
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
    ItemCreationClass186870* child = unk214;
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
                ItemCreationClass186870* reset = unk214;
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
    static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(unk214);
    return 1;
}


/** @brief Toggle the detail window for a selected item row. @return One when allowed; zero for a compound row. */
s32 ItemCreationClass1870B0::func_slotb8()
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
    ItemCreationClass186970* details = unka8->unkc0;
    if (details != 0)
    {
        active = !details->unk100;
        details->func_slot20(active);
        details->unk100 = active;
    }
    return 1;
}

/** @brief Restore the active selection window or leave item selection. @return Two when handled; zero when inactive. */
s32 ItemCreationClass1870B0::func_slotb4()
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
        ItemCreationFourteenSlotView* other = reinterpret_cast<ItemCreationFourteenSlotView*>(state->unkb8);
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
        func_0036A050(unka8, this, -1);
    }
    else
    {
        func_0036A050(state, this, -1);
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
            func_0027CB50(static_cast<ItemCreationRecordDirectory6430*>(static_cast<void*>(D_001B6430))->unk00->unk58, state->unk1f0, 0, 0);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00361D40);

u8 func_003623C0(ItemCreationClass1870B0* object, u8 index)
{
    u8 present;
    u8 first = 0;
    u8 second = 0;
    u8 third = 0;
    switch (index)
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
    if (first == 0 && second == 0 && third == 0)
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
void ItemCreationClass1870B0::func_slotac()
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
void ItemCreationClass1870B0::func_slota8()
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
void ItemCreationClass1870B0::func_slota4()
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
        ItemCreationFourteenSlotView* other = static_cast<ItemCreationFourteenSlotView*>(func_slot44());
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
            func_0036A500(other->unka8, other, other->unkb4->unk114);
        }
        func_00360E60(this, 0);
        static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(other);
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    }
    else if (unkb4 != 0 && unkb4->func_0023CDB0(1) != 1)
    {
        func_00361220(this);
        func_00360FD0(this);
    }
}

/** @brief Move to the related window from the first row or move the grid marker up. */
void ItemCreationClass1870B0::func_slota0()
{
    bool inactive = !unkb4->FieldClass151C50::unk35;
    if (inactive)
    {
        return;
    }
    s16 index = unkb4->unk114;
    if (index >= 0 && index < 5)
    {
        ItemCreationFourteenSlotView* other = static_cast<ItemCreationFourteenSlotView*>(func_slot44());
        if (other->unkb4 != 0)
        {
            func_0023C550(other->unkb4, (u8)(index + 7));
        }
        func_00364090(other, 1);
        if (other->unka8 != 0 && other->unkb4 != 0)
        {
            func_0036A500(other->unka8, other, other->unkb4->unk114);
        }
        func_00360E60(this, 0);
        static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(other);
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
    }
    else if (unkb4 != 0 && unkb4->func_0023CDB0(0) != 1)
    {
        func_00361220(this);
        func_00360FD0(this);
    }
}

void ItemCreationClass1870B0::func_slot74()
{
    func_slotac();
}

void ItemCreationClass1870B0::func_slot70()
{
    func_slota8();
}

void ItemCreationClass1870B0::func_slot6c()
{
    func_slota4();
}

void ItemCreationClass1870B0::func_slot68()
{
    func_slota0();
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00362BA0);

void func_00363D20(ItemCreationClass1870B0* object)
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
    func_0023CE80((FieldObject23CE80*)object->unkac, 5, object->unk1f1);
    func_0023CE80((FieldObject23CE80*)object->unkb0, 5, object->unk1f1);
}

/** @brief Release the twelve owned resources before destroying the window base. */
ItemCreationClass1870B0::~ItemCreationClass1870B0()
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
ItemCreationClass1870B0::ItemCreationClass1870B0()
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


void func_00364090(ItemCreationFourteenSlotView* object, u16 mode)
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
static inline void highlight_current_row(ItemCreationClass1871B0* object)
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
s32 ItemCreationClass1871B0::func_slotb4()
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
        ItemCreationClass1870B0* other = state->unkbc;
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
        func_0036A050(unka8, this, -1);
    }
    else
    {
        func_0036A050(state, this, -1);
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
            func_0027CB50(static_cast<ItemCreationRecordDirectory6430*>(static_cast<void*>(D_001B6430))->unk00->unk58, state->unk1f0, 0, 0);
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


u8 func_003644F0(ItemCreationFourteenSlotView* object)
{
    ItemCreationSelectedDisplayState* state = object->unka8;
    FieldObject23CEA0* display;
    u16 index;
    bool inactive;
    const float* position;
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
    func_0036A050(state, object, (s16)index);
    if (object->unka8->unk128 == 1)
    {
        FieldObject23CEA0* restore = object->unkac;
        FieldObject23CEA0* target;
        float x;
        float y;
        restore->FieldClass151C50::unk30 = 96.0f;
        restore->unkae = 1;
        x = position[0];
        y = position[1];
        target = object->unkb0;
        target->unk10 = x;
        target->unk14 = y;
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
static inline void apply_selected_index(ItemCreationSelectedDisplayState* state, ItemCreationClass1871B0* object)
{
    if (state)
    {
        FieldObject23CEA0* marker = object->unkb4;
        if (marker)
        {
            func_0036A500(state, object, marker->unk114);
        }
    }
}

/** @brief Toggle the detail window for the selected item. @return One when state is attached, zero otherwise. */
s32 ItemCreationClass1871B0::func_slotb8()
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
    ItemCreationClass186970* display = unka8->unkc0;
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
static inline void highlight_selected_row(ItemCreationClass1871B0* object, s16 index)
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
void ItemCreationClass1871B0::func_slotac()
{
    if (unkb4 != 0 && unkb4->func_0023CDB0(2) != 1)
    {
        highlight_selected_row(this, unkb4->unk114);
        if (unka8 != 0 && unkb4 != 0)
        {
            func_0036A500(unka8, this, unkb4->unk114);
        }
    }
}


/** @brief Move the fourteen-slot marker left and refresh its selected detail. */
void ItemCreationClass1871B0::func_slota8()
{
    if (unkb4 != 0 && unkb4->func_0023CDB0(3) != 1)
    {
        highlight_selected_row(this, unkb4->unk114);
        if (unka8 != 0 && unkb4 != 0)
        {
            func_0036A500(unka8, this, unkb4->unk114);
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
void ItemCreationClass1871B0::func_slota4()
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
        ItemCreationClass1870B0* other = static_cast<ItemCreationClass1870B0*>(func_slot44());
        if (other->unkb4 != 0)
        {
            func_0023C550(other->unkb4, selected);
        }
        func_00360FD0(other);
        func_00360E60(other, 1);
        func_00364090(reinterpret_cast<ItemCreationFourteenSlotView*>(this), 0);
        static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(other);
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
        return;
    }
    if (marker != 0 && marker->func_0023CDB0(1) != 1)
    {
        highlight_selected_row(this, unkb4->unk114);
        if (unka8 != 0 && unkb4 != 0)
        {
            func_0036A500(unka8, this, unkb4->unk114);
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
void ItemCreationClass1871B0::func_slota0()
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
        ItemCreationClass1870B0* other = static_cast<ItemCreationClass1870B0*>(func_slot44());
        if (other->unkb4 != 0)
        {
            func_0023C550(other->unkb4, selected);
        }
        func_00360FD0(other);
        func_00360E60(other, 1);
        func_00364090(reinterpret_cast<ItemCreationFourteenSlotView*>(this), 0);
        static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(other);
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
        return;
    }
    if (marker != 0 && marker->func_0023CDB0(0) != 1)
    {
        highlight_selected_row(this, unkb4->unk114);
        if (unka8 != 0 && unkb4 != 0)
        {
            func_0036A500(unka8, this, unkb4->unk114);
        }
    }
}


void ItemCreationClass1871B0::func_slot74()
{
    func_slotac();
}

void ItemCreationClass1871B0::func_slot70()
{
    func_slota8();
}

void ItemCreationClass1871B0::func_slot6c()
{
    func_slota4();
}

void ItemCreationClass1871B0::func_slot68()
{
    func_slota0();
}

void func_00364D20(ItemCreationFourteenSlotView* object)
{
    void* allocation;
    s32 index;
    u32 value;
    u32 resource;
    FieldResourceRecord* record;

    for (index = 0; index < 14; index++)
    {
        value = object->unka8->unk5a[(u16)index];
        if (value != 0)
        {
            resource = (u8)item_resource_index_middle(value);
            allocation = func_002D3D80(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, resource);
            record = func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 0x51);
            func_002D5CF0(object->unkf0[index], allocation, record, resource);
            object->unkf0[index]->unk3F = 1;
        }
        else
        {
            object->unkf0[index]->unk3F = 0;
        }
    }
}

/**
 * @brief Update the fourteen-slot selection markers and display activation.
 * @param object Selection window.
 * @param enabled Full-word activation flag.
 */
extern "C" void func_00364E00(ItemCreationClass1871B0* object, u32 enabled)
{
    update_selection_markers(object, enabled);
}

/**
 * @brief Create the fourteen-slot item displays and their two selection grids.
 * @param associated Associated display passed to the Field setup.
 * @return Zero without a selected state, one after setup.
 */
s32 ItemCreationClass1871B0::func_slotf4(void* associated)
{
    if (this->unka8 == 0)
    {
        return 0;
    }
    func_002CE760(this, associated, 0, 9, 2000, 16.0f, 72.0f, 0.0f);
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
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(widget)), record,
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
        func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(widget)), record,
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
    func_00364D20(reinterpret_cast<ItemCreationFourteenSlotView*>(this));
    return 1;
}

/** @brief Release the owned resource before destroying the selection window. */
ItemCreationClass1871B0::~ItemCreationClass1871B0()
{
    if (unk128)
    {
        release_owned(unk128);
    }
}


/**
 * @brief Fill the item and auxiliary cost arrays for the category.
 * @param object Panel selection window.
 * @param category Category code.
 */
extern "C" void func_00365600(ItemCreationClass1872B0* object, u8 category)
{
    switch (category)
    {
    case 1:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 2:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 3:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 4:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 5:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 6:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 7:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 8:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 9:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 10:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 11:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    case 12:
        object->unkb0[0] = 800;
        object->unkb0[1] = 2000;
        object->unkb0[2] = 8000;
        object->unkb0[3] = 4000;
        object->unkb0[4] = 3000;
        object->unkb0[5] = 5000;
        object->unkb0[6] = 6000;
        object->unkb0[7] = 9500;
        object->unk110[0] = 1000;
        object->unk110[1] = 2000;
        object->unk110[2] = 3000;
        break;
    }
}

/**
 * @brief Move the panel grid in direction one and refresh its selected entry.
 */
void ItemCreationClass1872B0::func_slot6c()
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
void ItemCreationClass1872B0::func_slot68()
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
s32 ItemCreationClass1872B0::func_slotb4()
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
    ItemCreationPanelReturnParent* parent = static_cast<ItemCreationPanelReturnParent*>(func_slot44());
    if (parent != 0)
    {
        ItemCreationPanelReturnMarker* marker = parent->unkac;
        if (marker != 0)
        {
            marker->unke0 = 128.0f;
            marker->unkae = 1;
        }
        static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(parent);
    }
    return 2;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00365BF0);

/**
 * @brief Refresh the panel grid selection and selected entry.
 * @param object Panel selection window.
 */
extern "C" void func_00365F20(ItemCreationClass1872B0* object)
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
                func_0023B9B0(object->unke0, (s16)index, func_4C69B0(widget)->unk08);
                widget->unk94 = 0x288080;
                widget->unk3c = 1;
                FieldClass15AE70* text =
                    static_cast<FieldClass15AE70*>(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C90());
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

u32 func_00366040(void* object)
{
    return *(u32*)((u8*)object + 0x24);
}

void func_00366050(ItemCreationPanelView* object)
{
    if (object->unka8 != 0)
    {
        if (object->unkd8 != 0)
        {
            for (s32 index = 0; index < object->unkd8; index++)
            {
                ItemCreationPanelMarker* display = object->unke8[index];
                if (display != 0)
                {
                    if (index != object->unk10c)
                    {
                        ItemCreationListNode* node = (ItemCreationListNode*)func_0036F160((u8*)&object->unk38, index);
                        ItemCreationPanelMarker* other = (ItemCreationPanelMarker*)node->unk00;
                        if (other != 0)
                        {
                            if (object->unka8->category_enabled[object->unkd0[index] - 1] == 0)
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
                            ItemCreationValueDisplay* valueDisplay = object->unk120;
                            valueDisplay->unkfc = object->unk110[object->unk10d];
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
                ItemCreationCheckedRecord* record = static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk00;
                const u8* end = (const u8*)&record->unka4;
                u16 checksum = record->unka4;
                ItemCreationValueDisplay* display;
                u32 value;
                if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26),
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003661F0);

void func_00366CB0(ItemCreationCheckedValueOwner* object)
{
    if (object->unke4 != 0)
    {
        ItemCreationCheckedRecord* record = static_cast<ItemCreationRecordDirectory6430*>(static_cast<void*>(D_001B6430))->unk04;
        const u8* end = (const u8*)&record->unka4;
        u16 checksum = record->unka4;
        ItemCreationValueDisplay* display;
        u32 value;

        if (checksum != (u16)func_457470(record->unka6, ((u8*)record + 0x26),
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

ItemCreationClass1872B0::ItemCreationClass1872B0()
{
    unka8 = 0;
    unkac = 0;
    for (s32 i = 0; i < 8; i++)
    {
        unkb0[i] = 0;
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
void ItemCreationClass1873B0::func_slot5c()
{
    ItemCreationSelectedDisplayState* state =
        static_cast<ItemCreationSelectedDisplayState*>(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14);
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

void func_00366F10(ItemCreationAvailableResourceView* object)
{
    u16 resource;
    if (object->unk120 != 0)
    {
        if (object->unk120->unk48 != 0)
        {
            for (s32 index = 0; index < 9; index++)
            {
                ItemCreationIndexedResourceDisplay* display = object->unka8[index];
                if (display != 0)
                {
                    display->unk3f = 0;
                }
            }
            for (s32 index = 0; index < 14; index++)
            {
                ItemCreationIndexedResourceDisplay* display = object->unkcc[index];
                if (display != 0)
                {
                    display->unk3f = 0;
                }
            }
            object->unk124 = object->unk120->unk4d + 1;
            if (object->unk124 != 0)
            {
                s32 slot = 0;
                for (s32 index = 0; index < 14; index++)
                {
                    u8 value = object->unk120->unk5a[(u16)index];
                    if (value != 0)
                    {
                        resource = item_available_resource_index(value);
                        void* allocation = func_002D3D80(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, (u8)resource);
                        FieldResourceRecord* record = func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 0x51);
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
                        void* allocation = func_002D3D80(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, (u8)resource);
                        FieldResourceRecord* record = func_002D3CC0(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk20, 0x51);
                        object->unka8[index]->unkd0 = resource;
                        func_002D5CF0((FieldResourceDisplay2D5CF0*)object->unka8[index], allocation, record, 0);
                        object->unka8[index]->unk3f = 1;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00367100);

/** @brief Release the seven resource owners and destroy the option window. */
ItemCreationClass1873B0::~ItemCreationClass1873B0()
{
    for (s32 i = 0; i < 7; i++)
    {
        if (unk104[i])
        {
            release_owned(unk104[i]);
        }
    }
}

ItemCreationClass1873B0::ItemCreationClass1873B0()
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
 * @brief Create the option grid and mark its available entries.
 * @param associated Associated source.
 * @return Always one.
 */
s32 ItemCreationClass1874B0::func_slotf4(void* associated)
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
    for (s32 index = 0; index < 8; index++)
    {
        LibObject178750* text = new (0) LibObject178750;
        float x = 26.0f + 80.0f * (index % 3);
        float y = 64.0f + 36.0f * (index / 3);
        text->func_004C7FE0(x, y, 0.0f, 0.0f, (s32)associated, ITEM_CREATION_CATEGORY_LABEL_BASE + index, 0);
        func_004C6190(unk10, text);
        func_0036F1A0(&unk2c, text);
    }
    if (unka8)
    {
        for (s32 index = 0; index < 8; index++)
        {
            ItemCreationListNode* node = func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), index);
            LibObject178750* text = static_cast<LibObject178750*>(node->unk00);
            if (text)
            {
                if (unka8->category_enabled[(u8)(index + 1) - 1])
                {
                    text->set_color(0x808080);
                }
                else
                {
                    text->set_color(0x505050);
                }
            }
        }
    }
    return 1;
}


ItemCreationClass1874B0::~ItemCreationClass1874B0()
{
}

/**
 * @brief Create the panel and label for the active selection mode.
 * @param associated Associated source.
 * @return Zero without the selection state, otherwise one.
 */
s32 ItemCreationClass1875B0::func_slotf4(void* associated)
{
    if (unka8 == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 220.0f, 17);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 266.0f, 64.0f, 88.0f);
    func_004C6190(unk10, panel);
    u32 code = 0x3520;
    if (unka8)
    {
        code = func_0036B0E0(unka8);
    }
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(0.0f, 16.0f, 266.0f, 32.0f, (s32)associated, code, 1);
    heading->set_mode(1);
    heading->set_vertical_alignment(1);
    heading->set_color(0x806080);
    heading->set_scale(1.3f, 1.3f);
    func_004C6190(unk10, heading);
    return 1;
}


ItemCreationClass1875B0::~ItemCreationClass1875B0()
{
}

/**
 * @brief Refresh the choice labels, selection marker, and current status text.
 * @param object Three-choice window.
 */
extern "C" void func_00368370(ItemCreationClass1876B0* object)
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
                func_0023B9B0(object->unkb0, (s16)index, func_4C69B0(widget)->unk08);
                static_cast<LibClass178600*>(static_cast<void*>(object->unkb0))->unk3f = 1;
                widget->unk94 = ITEM_CREATION_COLOR_SELECTED;
                widget->unk3c = 1;
                if (!object->unkb4 && index == 2)
                {
                    widget->unk94 = ITEM_CREATION_COLOR_DIM;
                    widget->unk3c = 1;
                    static_cast<LibClass178600*>(static_cast<void*>(object->unkb0))->unk3f = 0;
                }
                FieldClass15AE70* text =
                    static_cast<FieldClass15AE70*>(static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C90());
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

struct ItemCreationAssignedRecord
{
    u8 unk00[0x30];
    u16 unk30;
    u8 unk32;
    u8 unk33;
};

/** Partial word in the resident state section copied during initialization. */
struct RuntimeStateSection58
{
    u8 unk00[0x1B4];
    s32 unk1b4;
};

struct ItemCreationTransformState
{
    u8 unk00[0x30];
    float unk30[4];
    u8 unk40[0x10];
    u8 unk50;
};

/** One sixteen-byte option group stored in a runtime record. */
typedef struct ItemCreationRuntimeOptions
{
    u8 options[3];
    u8 marker;
    u8 unk04[0xC];
} ItemCreationRuntimeOptions;

typedef struct ItemCreationRuntimeRecord
{
    ItemCreationRuntimeOptions groups[3];
    u16 unk30;
    u8 unk32[2];
} ItemCreationRuntimeRecord;

/** Twelve-byte runtime option record with its availability byte. */
struct RuntimeOptionRecord
{
    u8 unk00[8];
    u8 unk08;
    u8 unk09[3];
};

typedef struct ItemCreationRuntimeRecordState
{
    u8 unk00[0x10D88];
    RuntimeOptionRecord unk10d88[38];
    ItemCreationRuntimeRecord unk10f50[12];
} ItemCreationRuntimeRecordState;


typedef struct ItemCreationRuntimeRoot ItemCreationRuntimeRoot;
typedef struct ItemCreationRuntimeDirectory ItemCreationRuntimeDirectory;
typedef struct ItemCreationRuntimeFlags
{
    u8 unk00[0x7A];
    u8 unk7a;
    u8 unk7b;
} ItemCreationRuntimeFlags;

typedef struct ItemCreationListDisplay
{
    u8 unk00[0x2C];
    ItemCreationList unk2c;
    u8 unk30[0x78];
    ItemCreationSelectedDisplayState* unka8;
} ItemCreationListDisplay;

typedef struct ItemCreationThreeSlotDisplay
{
    u8 unk00[0x120];
    ItemCreationSelectedDisplayState* unk120;
    u8 unk124;
    u8 unk125;
    u8 unk126[2];
    ItemCreationColorDisplay* unk128[3];
    ItemCreationColorDisplay* unk134[3];
} ItemCreationThreeSlotDisplay;


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


// Resident interfaces are scoped here because the shared declarations belong to another overlay.
extern "C"
{
    ItemCreationRuntimeRoot* func_10D8E0(void);
    ItemCreationRuntimeDirectory* func_101290(ItemCreationRuntimeRoot* root);
    ItemCreationRuntimeFlags* func_101440(ItemCreationRuntimeDirectory* directory, s32 key);


    extern u8 D_50CD30[];
}

/**
 * @brief Convert an option code to its runtime index.
 * @param value Option code.
 * @return Zero for an empty code, or the code minus 31.
 */
static inline u32 runtime_option_index(u8 value);

/**
 * @brief Test a one-based runtime record index.
 * @param index Record index.
 * @return True for indices one through twelve.
 */
static inline bool runtime_record_valid(u8 index);

/**
 * @brief Test a nonzero runtime option index.
 * @param index Option index.
 * @return True for indices one through thirty-eight.
 */
static inline bool runtime_record_option_valid(u8 index);

/**
 * @brief Test a nonzero runtime marker.
 * @param index Marker value.
 * @return True for values one through nine.
 */
static inline bool runtime_marker_valid(u8 index);

/**
 * @brief Store an option group whose supplied indices are valid.
 * @param state Runtime records.
 * @param record One-based record index.
 * @param group Group index.
 * @param first First option.
 * @param second Second option.
 * @param third Third option.
 * @param marker Marker value.
 */
static inline void store_runtime_options(ItemCreationRuntimeRecordState* state, u8 record, u8 group, u8 first, u8 second, u8 third, u8 marker);

static inline void enable_record_flag(ItemCreationSelectedDisplayState* object, u16 mask)
{
    if (object->unk134 != 0)
    {
        object->unk134->unk30 |= mask;
    }
}

/**
 * @brief Convert an option code to its runtime index.
 * @param value Option code.
 * @return Zero for an empty code, or the code minus 31.
 */
static inline u32 runtime_option_index(u8 value)
{
    if (value == 0)
    {
        return 0;
    }
    return value - 31;
}

/**
 * @brief Test a one-based runtime record index.
 * @param index Record index.
 * @return True for indices one through twelve.
 */
static inline bool runtime_record_valid(u8 index)
{
    return index > 0 && index < 13;
}

/**
 * @brief Test a nonzero runtime option index.
 * @param index Option index.
 * @return True for indices one through thirty-eight.
 */
static inline bool runtime_record_option_valid(u8 index)
{
    return index >= 1 && index < 39;
}

/**
 * @brief Test a nonzero runtime marker.
 * @param index Marker value.
 * @return True for values one through nine.
 */
static inline bool runtime_marker_valid(u8 index)
{
    return index >= 1 && index < 10;
}

/**
 * @brief Store an option group whose supplied indices are valid.
 * @param state Runtime records.
 * @param record One-based record index.
 * @param group Group index.
 * @param first First option.
 * @param second Second option.
 * @param third Third option.
 * @param marker Marker value.
 */
static inline void store_runtime_options(ItemCreationRuntimeRecordState* state, u8 record, u8 group, u8 first, u8 second, u8 third, u8 marker)
{
    if (!runtime_record_valid(record) || (s32)group < 0 || (s32)group >= 3)
    {
        return;
    }
    if (first > 0 && !runtime_record_option_valid(first))
    {
        return;
    }
    if (second > 0 && !runtime_record_option_valid(second))
    {
        return;
    }
    if (third > 0 && !runtime_record_option_valid(third))
    {
        return;
    }
    if (marker > 0 && !runtime_marker_valid(marker))
    {
        return;
    }
    ItemCreationRuntimeRecord* selected = &state->unk10f50[record - 1];
    ItemCreationRuntimeOptions* options = &selected->groups[group];
    options->options[0] = first;
    options->options[1] = second;
    options->options[2] = third;
    options->marker = marker;
}

/** @brief Move the selector in its second direction and refresh the choice labels. */
void ItemCreationClass1876B0::func_slot6c()
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
void ItemCreationClass1876B0::func_slot68()
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
s32 ItemCreationClass1876B0::func_slotb4()
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
s32 ItemCreationClass1876B0::func_slotb0()
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
        static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14);
    if (!state)
    {
        return 0;
    }
    switch (selector->unk114)
    {
    case 0:
        state->unk47 = 1;
        func_0027CB50(static_cast<ItemCreationRecordDirectory6430*>(static_cast<void*>(D_001B6430))->unk00->unk58,
                     state->unk1f0, 0, 0);
        break;
    case 1:
        {
            set_selector_depth(selector, &FieldClass151C50::unk30, &LibClass174610::unkae, 64.0f);
            ItemCreationClass1872B0* panel = static_cast<ItemCreationClass1872B0*>(func_slot4c());
            if (panel)
            {
                if (panel->unkdc)
                {
                    func_0023CEA0(panel->unkdc, 1);
                }
                panel->func_slot20(1);
                static_cast<ItemCreationResourceDirectory*>(static_cast<void*>(D_001B643C))->unk10->unk14->func_00263C70(panel);
            }
            break;
        }
    case 2:
        if (!unkb4)
        {
            return 3;
        }
        state->unk47 = 3;
        func_0027CB50(static_cast<ItemCreationRecordDirectory6430*>(static_cast<void*>(D_001B6430))->unk00->unk58,
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
s32 ItemCreationClass1876B0::func_slotf4(void* associated)
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
    bool outside_first_group = unka8->unk4d >= 6;
    if (unka8->unk19b != 0 && !outside_first_group)
    {
        unkb4 = 1;
    }
    else
    {
        ItemCreationListNode* node = func_0036F230(reinterpret_cast<ItemCreationList*>(&unk2c), 2);
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
    FieldObject23BE00* marker = static_cast<FieldObject23BE00*>(func_00100AC0(0x6C, 0));
    if (marker != 0)
    {
        marker = func_0023BE00(marker);
    }
    unkb0 = marker;
    func_0023BB20(unkb0, reinterpret_cast<FieldObject23CEB0*>(unkac), 0x288080, 22.0f, 18.0f, 215.99998f, 1.0f);
    func_4C6190(unk10, static_cast<LibClass178600*>(static_cast<void*>(unkb0)));
    func_0036EFB0(&unk8c, unkb0);
    func_00368370(this);
    return 1;
}

/** @brief Destroy the choice window through its Field base. */
ItemCreationClass1876B0::~ItemCreationClass1876B0()
{
}

/**
 * @brief Set a status message and reset its timed scroll.
 * @param text_key Absolute text key from 0x32CB through 0x32D2, or a signed relative index.
 */
void ItemCreationClass1877B0::func_slot60(s32 text_key)
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

void func_00368BD0(ItemCreationScrollState* object)
{
    ItemCreationScrollPosition* position = object->unkac;
    float x = position->unk18;
    float y = position->unk1c;
    float z = position->unk20;
    float w = position->unk24;
    float start;
    if (object->unkba == 0)
    {
        position->unk18 = object->unkc0;
        position->unk1c = y;
        position->unk20 = z;
        position->unk24 = w;
        position->unk3c = 1;
        object->unkb8++;
        if (!((float)object->unkb8 <= 120.0f))
        {
            object->unkb8 = 0;
            object->unkba = 1;
        }
        return;
    }
    start = object->unkc4;
    x -= 108.0f * D_001B6690;
    if (x < start - (float)object->unkb0)
    {
        x = start + object->unkc8 + 2.0f;
    }
    position->unk18 = x;
    position->unk1c = y;
    position->unk20 = z;
    position->unk24 = w;
    position->unk3c = 1;
}

/**
 * @brief Create the heading, list, value and footer displays and lay out the two columns.
 * @param associated Text source associated with the window.
 * @return Zero when an allocation failed, otherwise one.
 */
s32 ItemCreationClass1877B0::func_slotf4(void* associated)
{
    func_002CE760(this, associated, 0, 9, 1400, 16.0f, 16.0f, 0.0f);
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
ItemCreationClass1877B0::~ItemCreationClass1877B0()
{
}

/**
 * @brief Create and position the three resource displays.
 * @param associated Source associated with the window's nested container.
 * @return Always one.
 */
s32 ItemCreationClass1878B0::func_slotf4(void* associated)
{
    func_002CE760(this, associated, 0, 9, 1200, 16.0f, 16.0f, 0.0f);
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
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unka8)), record, 0.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 6);
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unkac)), record, 256.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 7);
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unkb0)), record, 512.0f, 0.0f);
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
ItemCreationClass1878B0::~ItemCreationClass1878B0()
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
            object->unk60[5] = 0;
            object->unk60[6] = 0;
            object->unk60[7] = 0;
            object->unk60[8] = 0;
            object->unk60[9] = 0;
            object->unk60[10] = 0;
            object->unk60[11] = 0;
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

void func_003698E0(ItemCreationSelectedDisplayState* object, u8 group)
{
    u8 index = group;
    if (object->unk1c0[index] != 0 && object->unk1c3[index] != 0)
    {
        u8 first = runtime_option_index(object->unk68[index * 3]);
        u8 second = runtime_option_index(object->unk68[index * 3 + 1]);
        u8 third = runtime_option_index(object->unk68[index * 3 + 2]);
        ::operator delete(object->unk1b4[index]);
        object->unk1b4[index] = 0;
        u8 result = 0;
        switch (object->unk1c3[index])
        {
        case 1:
            object->unk1b4[index] = new (0) FieldClass15BB30;
            result = func_002FAF50(static_cast<FieldClass15BB30*>(object->unk1b4[index]), object->unk4d, group,
                                  first, second, third, object->unk1c0[index]);
            break;
        case 2:
            object->unk1b4[index] = new (0) FieldClass15BB50;
            result = func_002FC310(static_cast<FieldClass15BB50*>(object->unk1b4[index]), object->unk4d, group,
                                  first, second, third, object->unk1c0[index], object->unk1e2[index][0]);
            break;
        case 3:
            object->unk1b4[index] = new (0) FieldClass15BB70;
            result = func_002FCC50(static_cast<FieldClass15BB70*>(object->unk1b4[index]), object->unk4d, group,
                                  first, second, third, object->unk1e2[index][0], object->unk1e2[index][1]);
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

void func_00369B80(ItemCreationSelectedDisplayState* object, s32 value)
{
    ItemCreationSelection* selection;
    ItemCreationFlagResetOwner* owner;
    s32 selected;
    switch (object->unk129)
    {
    case 0:
        if (value == -1)
        {
            object->unk129 = 0;
            object->unk12a = 0;
            object->unk12b = 0;
            object->unk12c = 0;
            object->unk12d = 0;
        }
        else
        {
            object->unk12a = value;
            object->unk129 = 1;
        }
        break;
    case 1:
        if (value == -1)
        {
            object->unk12b = 0;
            object->unk129 = 0;
        }
        else
        {
            object->unk12b = value;
            object->unk129 = 2;
        }
        break;
    case 2:
        if (value == -1)
        {
            object->unk12c = 0;
            object->unk129 = 1;
        }
        else
        {
            object->unk12c = value;
            object->unk129 = 3;
        }
        break;
    case 3:
        if (value == -1)
        {
            object->unk12d = 0;
            object->unk129 = 2;
            break;
        }
        object->unk12d = value;
        if (object->unk12b != 0)
        {
            u8 code = object->unk12c == 0 ? 0 : object->unk12c + 1;
            if (object->unk40 != 0)
            {
                object->unk40->unk188[object->unk12b] = code;
            }
        }
        if (object->unk12d != 0)
        {
            u8 code = object->unk12a == 0 ? 0 : object->unk12a + 1;
            if (object->unk40 != 0)
            {
                object->unk40->unk188[object->unk12d] = code;
            }
        }
        selected = object->unk12a;
        if (object->unkf8 != 0)
        {
            func_0036A780(object, selected, 1);
            func_0034D340(reinterpret_cast<ItemCreationOptionDisplay*>(object->unkf8));
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
        owner = reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4);
        if (owner != 0)
        {
            const float* position;
            ItemCreationTransferDisplay* display;
            float x;
            float y;
            owner->unk160->unk6c = selected;
            selection = owner->unk160;
            if ((u8)selected <= 0)
            {
                position = 0;
            }
            else if ((u8)selected > 12)
            {
                position = 0;
            }
            else
            {
                position = selection->unk00[(u8)selected - 1].unk00;
            }
            display = owner->unk15c;
            x = position[0];
            y = position[1];
            display->unk50 = x;
            display->unk54 = y;
            display->unk75 = 1;
            display->unk3c = 1;
            owner = reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4);
            switch (owner->unk164->unk129)
            {
            case 0:
                owner->unk16c->unk3f = 0;
                owner->unk15c->unk3f = 1;
                break;
            case 1:
                break;
            case 2:
                owner->unk15c->unk3f = 1;
                break;
            case 3:
                break;
            }
            func_0034DA30(reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4));
            func_0034DB00(reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4), selected);
        }
        if (object->unkfc != 0)
        {
            object->unk77[0] = 0;
            object->unk77[1] = 0;
            object->unk77[2] = 0;
            object->unk77[3] = 0;
            object->unk77[4] = 0;
            object->unk77[5] = 0;
            func_0034D340(reinterpret_cast<ItemCreationOptionDisplay*>(object->unkfc));
            if (object->unkfc->unkc8 != 0)
            {
                func_0023CEA0(object->unkfc->unkc8, 0);
            }
        }
        break;
    }
}

void func_00369EB0(ItemCreationRuntimeRecordSelection* object)
{
    object->unk7e[0] = static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8))->unk10f50[0].unk30;
    object->unk7e[1] = static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8))->unk10f50[1].unk30;
    object->unk7e[2] = static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8))->unk10f50[2].unk30;
    object->unk7e[3] = static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8))->unk10f50[3].unk30;
    object->unk7e[4] = static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8))->unk10f50[4].unk30;
}

u16 func_00369F20(void* object, u8 value)
{
    u16 group = 0;

    switch (value)
    {
    case 35:
    case 45:
    case 54:
    case 58:
        group = 1;
        break;
    case 33:
    case 39:
    case 49:
    case 50:
        group = 2;
        break;
    case 34:
    case 41:
    case 48:
    case 52:
        group = 5;
        break;
    case 43:
    case 51:
    case 53:
    case 56:
        group = 4;
        break;
    case 36:
    case 46:
    case 55:
    case 57:
        group = 7;
        break;
    case 38:
    case 44:
    case 47:
    case 59:
        group = 3;
        break;
    case 32:
    case 37:
    case 40:
    case 42:
        group = 6;
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
        group = 0;
        break;
    }
    return group + 0x3457;
}

u16 func_00369FA0(void* object, u8 value)
{
    u16 mask = 0;

    switch (value)
    {
    case 35:
    case 45:
    case 54:
    case 58:
        mask |= 0x1;
        break;
    case 33:
    case 39:
    case 49:
    case 50:
        mask |= 0x2;
        break;
    case 34:
    case 41:
    case 48:
    case 52:
        mask |= 0x10;
        break;
    case 43:
    case 51:
    case 53:
    case 56:
        mask |= 0x8;
        break;
    case 36:
    case 46:
    case 55:
    case 57:
        mask |= 0x40;
        break;
    case 38:
    case 44:
    case 47:
    case 59:
        mask |= 0x4;
        break;
    case 32:
    case 37:
    case 40:
    case 42:
        mask |= 0x20;
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
        mask |= 0x1ff;
        break;
    }
    return mask;
}

void func_0036A050(ItemCreationSelectedDisplayState* object, void* selected, s16 index)
{
    switch (object->unk128)
    {
    case 0:
        if (index == -1)
        {
            object->unk120 = 0;
            object->unk11c = 0;
            object->unk126 = -1;
            object->unk124 = -1;
            object->unk128 = 0;
        }
        else
        {
            object->unk11c = selected;
            object->unk120 = 0;
            object->unk124 = index;
            object->unk128 = 1;
        }
        break;
    case 1:
        if (index == -1)
        {
            object->unk120 = 0;
            object->unk11c = 0;
            object->unk126 = -1;
            object->unk124 = -1;
            object->unk128 = 0;
        }
        else
        {
            object->unk120 = selected;
            object->unk126 = index;
            object->unk128 = 2;
        }
        break;
    }
    if (object->unk11c != 0 && object->unk120 != 0 && object->unk128 == 2)
    {
        void* first = object->unk11c;
        void* second = object->unk120;
        u8 first_value = 0;
        u8 second_value = 0;
        ItemCreationFourteenSlotView* fourteen;
        ItemCreationClass1870B0* nine;

        if (first == object->unkb8)
        {
            first_value = object->unk5a[(u16)object->unk124];
        }
        else if (first == object->unkbc)
        {
            first_value = object->unk68[(u16)object->unk124];
        }
        if (second == object->unkb8)
        {
            second_value = object->unk5a[(u16)object->unk126];
        }
        else if (second == object->unkbc)
        {
            second_value = object->unk68[(u16)object->unk126];
        }
        if (first == object->unkb8)
        {
            object->unk5a[(u16)object->unk124] = second_value;
        }
        else if (first == object->unkbc)
        {
            object->unk68[(u16)object->unk124] = second_value;
        }
        if (object->unk120 == object->unkb8)
        {
            s32 marker;
            object->unk5a[(u16)object->unk126] = first_value;
            fourteen = reinterpret_cast<ItemCreationFourteenSlotView*>(object->unkb8);
            if (fourteen->unkb4 != 0)
            {
                s32 active = fourteen->unkb4->unk114;
                for (marker = 0; marker < 14; marker++)
                {
                    if (active == marker)
                    {
                        fourteen->unkb8[marker]->unk3f = 1;
                    }
                    else
                    {
                        fourteen->unkb8[marker]->unk3f = 0;
                    }
                }
            }
        }
        else if (object->unk120 == object->unkbc)
        {
            object->unk68[(u16)object->unk126] = first_value;
            func_00361220(object->unkbc);
        }
        func_00364D20(reinterpret_cast<ItemCreationFourteenSlotView*>(object->unkb8));
        func_003614B0(object->unkbc);
        first = object->unk11c;
        fourteen = reinterpret_cast<ItemCreationFourteenSlotView*>(object->unkb8);
        if (fourteen == first)
        {
            FieldObject23CEA0* restore;
            FieldObject23CEA0* display = fourteen->unkb4;
            if (display == fourteen->unkb0)
            {
                s16 selected_index = display->unk114;
                float x;
                float y;
                restore = fourteen->unkac;
                restore->FieldClass151C50::unk30 = 128.0f;
                restore->unkae = 1;
                x = display->unk10;
                y = display->unk14;
                restore = fourteen->unkac;
                restore->unk10 = x;
                restore->unk14 = y;
                restore->unk35 = 1;
                restore->unkae = 1;
                restore = fourteen->unkac;
                restore->index = selected_index;
                func_0023CB30(restore);
                func_0023C7B0(fourteen->unkac);
                func_0023CEA0(fourteen->unkb0, 0);
                fourteen->unkb4 = fourteen->unkac;
            }
            func_00364090(reinterpret_cast<ItemCreationFourteenSlotView*>(object->unkb8), 0);
            if (object->unkb8 == object->unk120)
            {
                func_00364090(reinterpret_cast<ItemCreationFourteenSlotView*>(object->unkb8), 1);
            }
            else if (object->unkbc == object->unk120)
            {
                func_00360E60(object->unkbc, 1);
                func_003698E0(object, (u8)(object->unk126 / 3));
            }
        }
        else
        {
            nine = object->unkbc;
            if (nine == first)
            {
                FieldObject23CEA0* restore;
                FieldObject23CEA0* display = nine->unkb4;
                if (display == nine->unkb0)
                {
                    s16 selected_index = display->unk114;
                    float x;
                    float y;
                        restore = nine->unkac;
                    restore->FieldClass151C50::unk30 = 128.0f;
                    restore->unkae = 1;
                    x = display->unk10;
                    y = display->unk14;
                    restore = nine->unkac;
                    restore->unk10 = x;
                    restore->unk14 = y;
                    restore->unk35 = 1;
                    restore->unkae = 1;
                    restore = nine->unkac;
                    restore->index = selected_index;
                    func_0023CB30(restore);
                    func_0023C7B0(nine->unkac);
                    func_0023CEA0(nine->unkb0, 0);
                    nine->unkb4 = nine->unkac;
                }
                func_00360E60(object->unkbc, 0);
                if (object->unkb8 == object->unk120)
                {
                    func_00364090(reinterpret_cast<ItemCreationFourteenSlotView*>(object->unkb8), 1);
                    func_003698E0(object, (u8)(object->unk124 / 3));
                }
                else if (object->unkbc == object->unk120)
                {
                    func_00360E60(object->unkbc, 1);
                    func_003698E0(object, (u8)(object->unk124 / 3));
                    func_003698E0(object, (u8)(object->unk126 / 3));
                }
            }
        }
        func_0036A500(object, object->unk120, object->unk126);
        object->unk120 = 0;
        object->unk11c = 0;
        object->unk126 = -1;
        object->unk124 = -1;
        object->unk128 = 0;
    }
}

void func_0036A500(ItemCreationSelectedDisplayState* object, void* selected, s16 index)
{
    if (selected != 0 && object->unkb8 != 0 && object->unkbc != 0 && object->unkc0 != 0)
    {
        u8 value = 0;
        ItemCreationClass186970* display;
        object->unk118 = selected;
        if (object->unk118 == object->unkb8)
        {
            value = object->unk5a[(u16)index];
        }
        else if (object->unk118 == object->unkbc)
        {
            value = object->unk68[(u16)index];
        }
        display = object->unkc0;
        display->unk101 = value;
        if (display->unka8 != 0)
        {
            display->unk102 = 0;
            display->unk102 = func_00369FA0(display->unka8, display->unk101);
        }
        display->func_00358850();
        object->unk118 = 0;
    }
}

void func_0036A5D0(ItemCreationSelectedDisplayState* object, u8 mode)
{
    switch (mode)
    {
    case 1:
        if (object->unka8 != 0)
        {
            ItemCreationListDisplay* display = reinterpret_cast<ItemCreationListDisplay*>(object->unka8);
            if (display->unka8 != 0)
            {
                s32 index;
                for (index = 0; index < 8; index++)
                {
                    ItemCreationListNode* node = func_0036F230(&display->unk2c, index);
                    ItemCreationColorDisplay* view = (ItemCreationColorDisplay*)node->unk00;
                    if (view != 0)
                    {
                        u8 slot = index + 1;
                        if (display->unka8->category_enabled[slot - 1] != 0)
                        {
                            view->unk94 = 0x808080;
                            view->unk3c = 1;
                        }
                        else
                        {
                            view->unk94 = 0x505050;
                            view->unk3c = 1;
                        }
                    }
                }
            }
        }
        if (object->unkb0 != 0)
        {
            ItemCreationThreeSlotDisplay* display = static_cast<ItemCreationThreeSlotDisplay*>(static_cast<void*>(object->unkb0));
            s32 index;
            display->unk125 = display->unk120->unk57;
            for (index = 0; index < 3; index++)
            {
                if (index < display->unk125)
                {
                    ItemCreationColorDisplay* view = display->unk128[index];
                    view->unk94 = 0x1E8CFF;
                    view->unk3c = 1;
                    view = display->unk134[index];
                    view->unk94 = 0x1E8CFF;
                    view->unk3c = 1;
                }
                else
                {
                    ItemCreationColorDisplay* view = display->unk128[index];
                    view->unk94 = 0x505050;
                    view->unk3c = 1;
                    view = display->unk134[index];
                    view->unk94 = 0x505050;
                    view->unk3c = 1;
                }
            }
        }
        break;
    case 6:
        if (object->unkf8 != 0)
        {
            func_0034D340(reinterpret_cast<ItemCreationOptionDisplay*>(object->unkf8));
        }
        break;
    case 7:
        if (object->unkfc != 0)
        {
            func_0034D340(reinterpret_cast<ItemCreationOptionDisplay*>(object->unkfc));
        }
        break;
    }
}

void func_0036A780(ItemCreationOptionState* object, u16 option, u8 list)
{
    s32 clear_index;
    u16 count;
    s32 index;
    u8 selected;

    if (object->unk40 != 0 && (option == 0 ? 0 : option + 1) > 1 && (option == 0 ? 0 : option + 1) < 13)
    {
        clear_index = 0;
        do
        {
            switch (list)
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
        selected = 0;
        switch (list)
        {
        case 1:
            object->unk58 = option;
            selected = object->unk58;
            break;
        case 2:
            object->unk59 = option;
            selected = object->unk59;
            break;
        }
        count = 0;
        index = 32;
        do
        {
            s32 code = object->unk40->unk188[index];
            if (code > 1 && code == (selected == 0 ? 0 : selected + 1))
            {
                switch (list)
                {
                case 1:
                    object->unk71[count++] = index;
                    break;
                case 2:
                    object->unk77[count++] = index;
                    break;
                }
            }
            index++;
        } while (index <= 59);
    }
}

/**
 * @brief Store the displayed option groups in the selected runtime record.
 * @param object Selected display state.
 */
void func_0036A8F0(ItemCreationSelectedDisplayState* object)
{
    for (s32 index = 0; index < object->unk57; index++)
    {
        store_runtime_options(static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8)), object->unk134->unk32, index,
            runtime_option_index(object->unk68[index * 3]),
            runtime_option_index(object->unk68[index * 3 + 1]),
            runtime_option_index(object->unk68[index * 3 + 2]), object->unk1c0[index]);
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0036AAA0);

/**
 * @brief Restore category flags from the saved record and enable the ninth entry.
 * @param object Selection state with an optional assigned-item record.
 */
void item_creation_restore_category_flags(ItemCreationSelectedDisplayState* object)
{
    if (object->unk134 != 0)
    {
        object->unk130 = object->unk134->unk30;
        if (object->unk130 & ITEM_CREATION_CATEGORY_FLAG_COOK)
        {
            enable_record_flag(object, ITEM_CREATION_CATEGORY_FLAG_COOK);
            object->category_enabled[0] = 1;
        }
        if (object->unk130 & ITEM_CREATION_CATEGORY_FLAG_ALCH)
        {
            enable_record_flag(object, ITEM_CREATION_CATEGORY_FLAG_ALCH);
            object->category_enabled[1] = 1;
        }
        if (object->unk130 & ITEM_CREATION_CATEGORY_FLAG_CRFT)
        {
            enable_record_flag(object, ITEM_CREATION_CATEGORY_FLAG_CRFT);
            object->category_enabled[2] = 1;
        }
        if (object->unk130 & ITEM_CREATION_CATEGORY_FLAG_CMPD)
        {
            enable_record_flag(object, ITEM_CREATION_CATEGORY_FLAG_CMPD);
            object->category_enabled[3] = 1;
        }
        if (object->unk130 & ITEM_CREATION_CATEGORY_FLAG_SMTH)
        {
            enable_record_flag(object, ITEM_CREATION_CATEGORY_FLAG_SMTH);
            object->category_enabled[4] = 1;
        }
        if (object->unk130 & ITEM_CREATION_CATEGORY_FLAG_WRIT)
        {
            enable_record_flag(object, ITEM_CREATION_CATEGORY_FLAG_WRIT);
            object->category_enabled[5] = 1;
        }
        if (object->unk130 & ITEM_CREATION_CATEGORY_FLAG_ENG)
        {
            enable_record_flag(object, ITEM_CREATION_CATEGORY_FLAG_ENG);
            object->category_enabled[6] = 1;
        }
        if (object->unk130 & ITEM_CREATION_CATEGORY_FLAG_SYTH)
        {
            enable_record_flag(object, ITEM_CREATION_CATEGORY_FLAG_SYTH);
            object->category_enabled[7] = 1;
        }
        enable_record_flag(object, ITEM_CREATION_FLAG_8);
        object->category_enabled[8] = 1;
    }
}

u8 func_0036AFE0(ItemCreationSelectedDisplayState* object)
{
    u8 code;
    switch (D_001B6430->context->unk08->unkb8)
    {
    case 31:
        code = 1;
        break;
    case 32:
        code = 2;
        break;
    case 94:
        code = 3;
        break;
    case 113:
        code = 4;
        break;
    case 142:
        code = 5;
        break;
    case 499:
        code = 6;
        break;
    case 575:
        code = 7;
        break;
    case 602:
        code = 8;
        break;
    case 652:
        code = 9;
        break;
    case 664:
        code = 10;
        break;
    case 805:
        code = 11;
        break;
    case 1135:
        code = 12;
        break;
    default:
        code = 0;
        break;
    }
    return code;
}

u32 func_0036B0E0(void* object)
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
 * @brief Find the position for a one-based option in the selection grid.
 * @param selection Grid containing twelve positions.
 * @param index One-based option index.
 * @return Position, or null for an invalid index.
 */
static inline const float* selection_position(ItemCreationSelection* selection, s32 index)
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
 * @brief Move the transfer display and mark its position for refresh.
 * @param display Transfer display to move.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
static inline void transfer_position(ItemCreationTransferDisplay* display, float x, float y)
{
    display->unk50 = x;
    display->unk54 = y;
    display->unk75 = 1;
    display->unk3c = 1;
}
/**
 * @brief Refresh the option windows and enable or disable their selection controls.
 * @param object State owning the selection and detail windows.
 * @param enabled Full-word control flag; nonzero also restores the selected item and status message.
 */
extern "C" void func_0036B1E0(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    if (reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4) != 0)
    {
        if (enabled != 0)
        {
            func_0034DA30(reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4));
            func_0034DB00(reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4), object->unk4d);
            func_0034D980(reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4), object->unk4d);
            ItemCreationFlagResetOwner* owner = reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4);
            s32 selected = object->unk4d;
            owner->unk160->unk6c = selected;
            const float* position = selection_position(owner->unk160, selected);
            transfer_position(owner->unk15c, position[0], position[1]);
            object->func_00263C70(reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4));
        }
        static_cast<FieldClass15AE70*>(static_cast<void*>(reinterpret_cast<ItemCreationFlagResetOwner*>(object->unkf4)))->func_slot20(enabled);
    }
    if (object->unkf8 != 0)
    {
        static_cast<FieldClass15AE70*>(static_cast<void*>(object->unkf8))->func_slot20(enabled);
        if (enabled != 0)
        {
            func_0034D340(reinterpret_cast<ItemCreationOptionDisplay*>(object->unkf8));
        }
    }
    if (object->unkfc != 0)
    {
        static_cast<FieldClass15AE70*>(static_cast<void*>(object->unkfc))->func_slot20(enabled);
        if (enabled != 0)
        {
            func_0034D340(reinterpret_cast<ItemCreationOptionDisplay*>(object->unkfc));
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
            func_00356FD0(static_cast<ItemCreationNineResourceView*>(static_cast<void*>(object->unkd8)));
            func_00356160(static_cast<ItemCreationNineResourceView*>(static_cast<void*>(object->unkd8)));
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
            func_0036C1C0(object);
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
    ItemCreationClass186070* actor = object->unke0;
    if (actor != 0)
    {
        actor->func_slot20(0);
        actor->unke8->unkab = 0;
    }
    ItemCreationClass186670* colors = object->unkdc;
    if (colors != 0)
    {
        colors->func_slot20(0);
        func_0023B280(static_cast<FieldObject23B280*>(static_cast<void*>(colors->unkac)), 1);
        if (colors->unkac != 0)
        {
            for (s32 index = 0; index < 2; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(
                    func_0036F230(reinterpret_cast<ItemCreationList*>(&colors->unk2c), index)->unk00);
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
    ItemCreationClass1877B0* message = object->unk9c;
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
 * @brief Activate the available-item windows and update their selected display flags.
 * @param object State owning the selection, detail, and message windows.
 * @param enabled Full-word activation flag; zero disables the group.
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
        func_00364E00(static_cast<ItemCreationClass1871B0*>(static_cast<void*>(object->unkb8)), enabled);
        if (enabled != 0)
        {
            func_00364090(reinterpret_cast<ItemCreationFourteenSlotView*>(object->unkb8), 1);
            if (object->unkb8->unkb4 != 0)
            {
                func_0023C550(object->unkb8->unkb4, 0);
            }
            func_00364D20(reinterpret_cast<ItemCreationFourteenSlotView*>(object->unkb8));
            ItemCreationClass1871B0* window = static_cast<ItemCreationClass1871B0*>(static_cast<void*>(object->unkb8));
            if (window->unkb4 != 0)
            {
                s32 index;
                s32 selected = window->unkb4->unk114;
                for (index = 0; index < 14; index++)
                {
                    if (selected == index)
                    {
                        window->unkb8[index]->unk3f = 1;
                    }
                    else
                    {
                        window->unkb8[index]->unk3f = 0;
                    }
                }
            }
            object->func_00263C70(object->unkb8);
        }
    }
    ItemCreationClass186970* detail = object->unkc0;
    if (detail != 0)
    {
        detail->func_slot20(0);
        detail->unk100 = 0;
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
    ItemCreationClass1877B0* message = object->unk9c;
    if (message != 0 && enabled != 0)
    {
        if (message->unka8 != 0)
        {
            func_4C6DF0(message->unka8, message->func_slot54(), 0x32C9, 0);
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
        object->unk9c->func_slot60(0x32D2);
    }
}

/**
 * @brief Activate the assigned-item windows and configure their status message.
 * @param object State owning the windows and assigned-item flags.
 * @param enabled Full-word activation flag; zero disables the group.
 */
extern "C" void func_0036BA10(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    ItemCreationClass1876B0* choice = object->unka0;
    if (choice != 0)
    {
        if (choice->unkac != 0)
        {
            func_0023CEA0(choice->unkac, enabled);
        }
        choice->func_slot20(enabled);
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
        static_cast<FieldClass15AE70*>(static_cast<void*>(object->unka8))->func_slot20(enabled);
    }
    ItemCreationClass1872B0* panel = object->unkac;
    if (panel != 0)
    {
        if (panel->unkdc != 0)
        {
            func_0023CEA0(panel->unkdc, 0);
        }
        panel->func_slot20(0);
    }
    if (object->unkb0 != 0)
    {
        object->unkb0->func_slot20(enabled);
        if (enabled != 0)
        {
            func_00366F10(static_cast<ItemCreationAvailableResourceView*>(static_cast<void*>(object->unkb0)));
        }
    }
    if (object->unka4 != 0)
    {
        object->unka4->func_slot20(enabled);
    }
    ItemCreationClass1877B0* message = object->unk9c;
    if (message != 0 && enabled != 0)
    {
        if (message->unka8 != 0)
        {
            func_4C6DF0(message->unka8, message->func_slot54(), 0x32C8, 0);
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
        object->unk9c->func_slot60(0x32CB);
        if (object->unk45 == 0 && object->unka0 != 0)
        {
            s16 index = object->unka0->unkac != 0 ? object->unka0->unkac->unk114 : -1;
            if (index == 2)
            {
                object->unk9c->func_slot60(0x32CD);
            }
        }
    }
}

/**
 * @brief Select the active option window group and reset transfer state.
 * @param object State owning the option windows and transfer fields.
 * @param mode Window group byte; four leaves the groups unchanged.
 */
extern "C" void func_0036BC90(ItemCreationSelectedDisplayState* object, u8 mode)
{
    if (object->unk19c != 0)
    {
        func_002FD940(object->unk19c);
        object->unk1a8 = 1;
    }
    object->unk1a4 = 0;
    object->unk1a0 = 0;
    object->unk1ac = 0;
    switch (mode)
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
        func_0036A8F0(object);
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
            if (func_0040CF90(static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8)), records, (u16)category) != 0)
            {
                func_0040C9F0(static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8)), func_0040D890(records[0]));
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

void func_0036C1C0(ItemCreationSelectedDisplayState* object)
{
    if (object->unk1b1[0] == 0 || object->unk1b1[1] == 0 || object->unk1b1[2] == 0)
    {
        s32 index;
        s32 group;
        s32 value;
        for (;;)
        {
            index = func_0010CF80() % 9;
            group = index / 3;
            if (object->unk1b4[group] == 0)
            {
                continue;
            }
            if (object->unk1b1[group] != 0)
            {
                continue;
            }
            if (func_002FB510(object->unk1b4[group], index % 3) == 3)
            {
                continue;
            }
            value = object->unk68[index];
            if (value > 0)
            {
                break;
            }
        }
        if (value >= 32 && value < 60)
        {
            s32 resource = value + 596;
            if (object->unk19c != 0)
            {
                func_002FD940(object->unk19c);
                object->unk1a8 = 1;
            }
            object->unk1a0 = resource;
            object->unk1a4 = 0;
        }
        else
        {
            s32 resource = (value - 60) * 9 + 538;
            s32 code = object->unk1c0[group];
            if (object->unk19c != 0)
            {
                func_002FD940(object->unk19c);
                object->unk1a8 = 1;
            }
            object->unk1a0 = resource;
            if (code != 0)
            {
                object->unk1a4 = resource + code;
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
    unk98 = new (0) ItemCreationClass1878B0;
    unk9c = new (0) ItemCreationClass1877B0;
    unk98->func_slotf4(unk34);
    FieldClass153E30::func_00263FD0(unk98);
    unk98->func_slot40(0);
    unk9c->func_slotf4(unk34);
    FieldClass153E30::func_00263FD0(unk9c);
    unk24 = unk9c;
    unk9c->func_slot40(unk98);
    if (unk45 == 0)
    {
        unka0 = new (0) ItemCreationClass1876B0(this);
        unka4 = new (0) ItemCreationClass1875B0(this);
        unka8 = new (0) ItemCreationClass1874B0;
        unkac = new (0) ItemCreationClass1872B0;
        unkb0 = new (0) ItemCreationClass1873B0;
        unkb4 = new (0) ItemCreationClass186A70;
        unkb8 = new (0) ItemCreationClass1871B0;
        unkbc = new (0) ItemCreationClass1870B0;
        unkc0 = new (0) ItemCreationClass186970;
        unkc4 = new (0) ItemCreationClass186FB0(this);
        unkc8 = new (0) ItemCreationClass186EB0(this);
        unkcc = new (0) ItemCreationClass186870(this);
        unkd0 = new (0) ItemCreationClass186DB0(this);
        unkd4 = new (0) ItemCreationClass186C90(this);
        unkd8 = new (0) ItemCreationClass186770;
        unkdc = new (0) ItemCreationClass186670;
        unke0 = new (0) ItemCreationClass186070(this);
        unke4 = new (0) ItemCreationClass185C60;
        unke8 = new (0) ItemCreationClass185E60;
        unkec = new (0) ItemCreationClass185D60;
        unkf0 = new (0) ItemCreationClass185B60(this);
        unkf4 = new (0) ItemCreationClass185960;
        unkf8 = new (0) ItemCreationClass185760;
        unkfc = new (0) ItemCreationClass185660;
        unka0->func_slot48(unkac);
        unka0->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unka0);
        unka4->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unka4);
        unka8->unka8 = this;
        unka8->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unka8);
        unkac->unka8 = this;
        unkac->unkac = unk4d;
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
        ItemCreationClass186FB0* category_window;
        ItemCreationClass186C90* category_list;
        category_list = unkd4;
        category_window = unkc4;
        category_window->unke0 = unkd0;
        category_window->unke4 = category_list;
        unkc4->func_slot40(unkbc);
        unkc4->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unkc4);
        ItemCreationClass186EB0* mode_window;
        ItemCreationClass186C90* mode_list;
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
        unkf4->unk164 = this;
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
        func_0036BC90(this, 0);
        unk20 = unka0;
    }
    else if (unk45 == 1)
    {
        unk114 = new (0) ItemCreationClass185560;
        unk104 = new (0) ItemCreationClass185360;
        unk108 = new (0) ItemCreationClass185260;
        unk10c = new (0) ItemCreationClass185160;
        unk110 = new (0) ItemCreationClass185060;
        unk100 = new (0) ItemCreationClass185460;
        unk114->unka8 = this;
        unk114->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unk114);
        unk104->unka8 = this;
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
        unk100->unk1a4 = unk110;
        unk100->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(unk100);
        unk10c->func_slot40(unk100);
        unk110->func_slot40(unk100);
        unk9c->func_slot60(0x32CF);
        func_0036BC90(this, 4);
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

/** Partial Field runtime reached through D_001B657C. */
struct FieldRuntime
{
    u8 unk00[0x514];
    void* unk514;
    u32 unk518;
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

void func_0036DEA0(ItemCreationSelectedDisplayState* object)
{
    func_0036A8F0(object);
    func_0011ED90(D_001B65F4, object);
}

/** @brief Find a one-based assigned record. @param index Record index. @return Record, or null outside the table. */
static inline ItemCreationAssignedRecord* assigned_record(u8 index)
{
    ItemCreationRuntimeRecordState* records = static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8));
    if (runtime_record_valid(index))
    {
        return reinterpret_cast<ItemCreationAssignedRecord*>(&records->unk10f50[index - 1]);
    }
    return 0;
}
/** @brief Find a one-based option record. @param index Record index. @return Record, or null outside the table. */
static inline RuntimeOptionRecord* option_record(u8 index)
{
    ItemCreationRuntimeRecordState* records = static_cast<ItemCreationRuntimeRecordState*>(static_cast<void*>(D_001B64F8));
    if (runtime_record_option_valid(index))
    {
        return &records->unk10d88[index - 1];
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
        unk4d = func_0036AFE0(this);
    }
    if (unk45 == 0)
    {
        unk12e[0] = unk4d;
        unk134 = assigned_record(unk12e[0]);
        unk57 = unk134->unk33;
    }
    unk1f0 = reinterpret_cast<RuntimeStateSection58*>(D_001B6430->context->unk58)->unk1b4;
    func_0036AAA0(this);
    item_creation_restore_category_flags(this);
    func_00369EB0(reinterpret_cast<ItemCreationRuntimeRecordSelection*>(this));
    for (s32 index = 1; index < 28; index++)
    {
        RuntimeOptionRecord* record = option_record(index);
        if (record && record->unk08 == 2)
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
    unk4d = 0;
    unk57 = 0;
    unk58 = 0;
    unk59 = 0;
    unk140 = 130.0f;
    for (s32 index = 0; index < 9; index++)
    {
        category_enabled[index] = 0;
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
        unk7e[index] = 0;
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
    unk130 = 0;
    unk134 = 0;
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

void func_0036E570(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_0036E590(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x20) = *value;
}

void func_0036E5B0(u8* object, float x, float y, float z)
{
    object[0x50] = 1;
    *(float*)(object + 0x20) = x;
    *(float*)(object + 0x24) = y;
    *(float*)(object + 0x28) = z;
    *(float*)(object + 0x2C) = 1.0f;
}

void func_0036E5D0(u8* object, float x, float y, float z, float w)
{
    object[0x50] = 1;
    *(float*)(object + 0x30) = x;
    *(float*)(object + 0x34) = y;
    *(float*)(object + 0x38) = z;
    *(float*)(object + 0x3C) = w;
}

void func_0036E5F0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

void func_0036E610(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x30) = *value;
}

void func_0036E630(ItemCreationTransformState* object, const float* input)
{
    object->unk50 = 1;
    func_004CE4C0(object->unk30, input);
}

void func_0036E660(ItemCreationTransformState* object, const float* input)
{
    object->unk50 = 1;
    func_004CE4C0(object->unk30, input);
}

void func_0036E690(u8* object, float x, float y, float z)
{
    ItemCreationTransformState* transform = (ItemCreationTransformState*)object;
    float value[4];
    transform->unk50 = 1;
    value[0] = x;
    value[1] = y;
    value[2] = z;
    value[3] = 1.0f;
    func_004CE4C0(transform->unk30, value);
}

void func_0036E6D0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

void func_0036E6F0(u8* object, const unsigned __int128* value)
{
    object[0x50] = 1;
    *(unsigned __int128*)(object + 0x40) = *value;
}

void func_0036E710(u8* object, float x, float y, float z)
{
    object[0x50] = 1;
    *(float*)(object + 0x40) = x;
    *(float*)(object + 0x44) = y;
    *(float*)(object + 0x48) = z;
}

s32 func_0036E730(void* object)
{
    return 0;
}

s32 func_0036E740(void* object, float value)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

u8* func_0036E760(void)
{
    return D_50CD30;
}

s32 func_0036E770(void* object)
{
    return 0;
}

void func_0036E780(void* object)
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

void func_0036E7C0(void* object)
{
}

void func_0036E7D0(u8* object)
{
    object[0x60] = object[0xA8];
}

void func_0036E7E0(void* object)
{
}

float func_0036E7F0(void* object)
{
    return 0.0f;
}

void func_0036E800(void* object)
{
}

void func_0036E810(void* object)
{
}

void func_0036E820(void* object)
{
}

void func_0036E830(void* object)
{
}

s32 func_0036E840(void* object)
{
    return 0;
}

s32 func_0036E850(void* object)
{
    return 0;
}

/** @brief Destroy the four embedded text widgets and their row interface. */
ItemCreationClass186050::~ItemCreationClass186050()
{
}

/** @brief Destroy the popup Field window base. */
ItemCreationClass186170::~ItemCreationClass186170()
{
}

/**
 * @brief Destroy the popup through its Field window base.
 */
ItemCreationClass186270::~ItemCreationClass186270()
{
}

/**
 * @brief Destroy the result window through its Field base.
 */
ItemCreationClass186370::~ItemCreationClass186370()
{
}

/**
 * @brief Destroy the result prompt window and release its Field base.
 */
ItemCreationClass186470::~ItemCreationClass186470()
{
}

/**
 * @brief Destroy the selected item prompt window through its Field base.
 */
ItemCreationClass186570::~ItemCreationClass186570()
{
}

/** @brief Release the embedded list and destroy the Field window. */
ItemCreationClass186C90::~ItemCreationClass186C90()
{
}

/** @brief Destroy the selection window through its Field window base. */
ItemCreationClass1872B0::~ItemCreationClass1872B0()
{
}

u8 func_0036EBC0(void* object)
{
    return *(u8*)((u8*)object + 0x38);
}

s32 func_0036EBD0(void* object)
{
    return 4;
}

void func_0036EBE0(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x24) = value;
}

void func_0036EBF0(void* object, u8 value)
{
    *(u8*)((u8*)object + 0x28) = value;
}

s8 func_0036EC00(void* object)
{
    return *(s8*)((u8*)object + 0x28);
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

void func_0036EDB0(ItemCreationCountedList* object, void* record)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
    if (node != 0)
    {
        ItemCreationListNode* tail;
        ItemCreationListNode* next;
        node->unk00 = record;
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

void func_0036EE40(ItemCreationCountedList* object, ItemCreationListNode* after, void* const* record)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
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

ItemCreationListNode* func_0036EF70(ItemCreationCountedList* object, s32 index)
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

void func_0036EFB0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
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
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
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
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
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

void* func_0036F160(u8* object, s32 index)
{
    u8* node = *(u8**)object;
    s32 current = 0;
    node = *(u8**)(node + 4);
    for (current = 0; current < index; current++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = *(u8**)(node + 4);
    }
    return node;
}

void func_0036F1A0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
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

ItemCreationListNode* func_0036F230(ItemCreationList* object, s32 index)
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
    ItemCreationListNode* node = (ItemCreationListNode*)func_00100AC0(sizeof(ItemCreationListNode), 0);
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
