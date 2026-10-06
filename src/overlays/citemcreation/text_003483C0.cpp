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
    /** @brief Destroy the aggregate and object bases. */
    virtual ~LibClass172320();
};
/** Resident owner of 32 interface rows and the collection state. */
class LibClass1721F0 : public LibClass172320
{
public:
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
    ITEM_CREATION_COLOR_ASSIGNED = 0x1E8CFF,
    ITEM_CREATION_RECORD_FLAG_0 = 0x1,
    ITEM_CREATION_RECORD_FLAG_1 = 0x2,
    ITEM_CREATION_RECORD_FLAG_2 = 0x4,
    ITEM_CREATION_RECORD_FLAG_3 = 0x8,
    ITEM_CREATION_RECORD_FLAG_4 = 0x10,
    ITEM_CREATION_RECORD_FLAG_5 = 0x20,
    ITEM_CREATION_RECORD_FLAG_6 = 0x40,
    ITEM_CREATION_RECORD_FLAG_7 = 0x80
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
    u8 unk09[3];
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
};
class FieldClass15BB70 : public ItemCreationClass184EF0
{
public:
    u8 unk90[0x50];
    s16 unke0;
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

void func_00348400(void* object, u8 value)
{
    *(u8*)((u8*)object + 0xC) = value;
}

u8 func_00348410(void* object)
{
    return *(u8*)((u8*)object + 0xC);
}

void func_00348420(void* object, u8 value)
{
    *(u8*)((u8*)object + 0x8) = value;
}

u8 func_00348430(void* object)
{
    return *(u8*)((u8*)object + 0x8);
}

void func_00348440(void* object, u16 value)
{
    *(u16*)((u8*)object + 0xA) = value;
}

u16 func_00348450(void* object)
{
    return *(u16*)((u8*)object + 0xA);
}

void func_00348480(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x9C) = value;
}

u32 func_00348490(void* object)
{
    return *(u32*)((u8*)object + 0x9C);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00348700);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00348770);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003487E0);

/**
 * @brief Destroy the window through its Field base.
 */
ItemCreationClass185060::~ItemCreationClass185060()
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00348B60);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00348CF0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00348DB0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00348E70);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00348EE0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00348FC0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00349DE0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034A040);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034A0D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034A160);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034A1E0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034A2C0);

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
        if (flags & ITEM_CREATION_RECORD_FLAG_0)
        {
            ItemCreationColorDisplay* display = object->unk168[0];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_RECORD_FLAG_1)
        {
            ItemCreationColorDisplay* display = object->unk168[1];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_RECORD_FLAG_2)
        {
            ItemCreationColorDisplay* display = object->unk168[2];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_RECORD_FLAG_3)
        {
            ItemCreationColorDisplay* display = object->unk168[3];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_RECORD_FLAG_4)
        {
            ItemCreationColorDisplay* display = object->unk168[4];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_RECORD_FLAG_5)
        {
            ItemCreationColorDisplay* display = object->unk168[5];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_RECORD_FLAG_6)
        {
            ItemCreationColorDisplay* display = object->unk168[6];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
        if (flags & ITEM_CREATION_RECORD_FLAG_7)
        {
            ItemCreationColorDisplay* display = object->unk168[7];
            display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
            display->unk3c = 1;
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034A9A0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034AA10);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034AB20);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034AD60);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034B970);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034C080);

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
                    allocation = func_002D3D80(D_001B643C->unk20, resource_index);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034DB00);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00350590);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003513E0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00352340);

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
        (static_cast<LibObject178750*>(unk180[index]))->func_004C7FE0(458.0f + 50.0f * (index % 3), y + 22.0f * (index / 3), 0.0f, 0.0f, (s32)associated, index + 0x3458, 1);
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
    (static_cast<LibObject178750*>(unk1a4[1]))->func_004C7FE0(490.0f, y, 0.0f, 0.0f, (s32)associated, 0x3458, 1);
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
        (static_cast<LibObject178750*>(unk1b8[index]))->func_004C7FE0(458.0f + 50.0f * (index % 3), y + 22.0f * (index / 3), 0.0f, 0.0f, (s32)associated, index + 0x3458, 1);
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
    (static_cast<LibObject178750*>(unk1dc[1]))->func_004C7FE0(490.0f, y, 0.0f, 0.0f, (s32)associated, 0x3458, 1);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00352B90);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003568F0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00356A40);

void func_00356FD0(ItemCreationNineResourceView* object)
{
    s32 index;

    object->unk1bc = object->unka8->unk57;
    for (index = 0; index < 3; index++)
    {
        if (index < object->unk1bc)
        {
            ItemCreationValueDisplay* value;
            ItemCreationColorDisplay* display1;
            ItemCreationColorDisplay* display2;
            ItemCreationColorDisplay* display3;
            ItemCreationColorDisplay* display4;

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
            ItemCreationColorDisplay* display1;
            ItemCreationColorDisplay* display2;
            ItemCreationColorDisplay* display3;
            ItemCreationColorDisplay* display4;

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
 * @brief Delete an owned resource and clear its pointer.
 * @param resource Nullable owned resource pointer.
 */
static inline void release_resource(FieldClass15B200*& resource)
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
            release_resource(unk11c[index]);
        }
        if (unk128[index] != 0)
        {
            release_resource(unk128[index]);
        }
    }
    for (s32 index = 0; index < 12; index++)
    {
        if (unkac[index] != 0)
        {
            release_resource(unkac[index]);
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
        ItemCreationSelectedDisplayState* state = unka8;
        state->func_0036BF30(0, unkbc[0]);
        state = unka8;
        state->func_0036BF30(1, unkbc[1]);
        state = unka8;
        state->func_0036BF30(2, unkbc[2]);
        state = unka8;
        state->unk47 = 2;
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
