#include "overlays/1067-00/field_runtime.h"
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
    /** Text source forwarded to inventor status rows. */
    u32 text_source;
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
/**
 * @brief Configure the frame widget's rectangle.
 * @param object Frame widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Rectangle width.
 * @param height Rectangle height.
 * @return One on success, or zero if its storage could not be initialized.
 */
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
    /** @brief Random two-bit shift used in the record checksum. */
    u8 checksum_shift : 2;
    u8 unk0d_high : 2;
    u8 unk0d_flag : 1;
    /** @brief Checksum of the six halfwords at offsets 00 through 0A. */
    u16 checksum;
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

struct ItemCreationControlState;
typedef struct ItemCreationRuntime643C
{
    ResidentCheckedRecord* unk00;
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
 * @param suppress_allocation_id Suppress the resident allocation identifier when the record checksum is valid.
 */
extern "C" void func_40D2E0(ItemCreationAllocationRecord* record, u16 value, u8 channel,
                          const u16* values, bool flag, bool suppress_allocation_id);

/**
 * @brief Set horizontal glyph spacing and mark the widget for redraw.
 * @param object Text widget.
 * @param value Spacing added between glyphs before horizontal scaling.
 */
static inline void set_text_spacing(LibClass174EF0* object, float value)
{
    object->unk88 = value;
    object->unk3c = 1;
}
/**
 * @brief Set horizontal text scale and mark the widget for redraw.
 * @param object Text widget.
 * @param value Horizontal scale factor.
 */
static inline void set_text_horizontal_scale(LibClass174EF0* object, float value)
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

/** @brief Return the map position for a one-based workshop ID, or null if invalid. */
static inline const float* workshop_map_position(ItemCreationSelection* selection, s32 workshop_id);
/**
 * @brief Read the raw selection flag for a one-based workshop ID.
 * @param selection Workshop selection containing the flags.
 * @param workshop_id One-based workshop ID.
 * @return Stored workshop selection flag.
 */
static inline u8 workshop_selection_flag(ItemCreationSelection* selection, u8 workshop_id);
/** @brief Set the transfer display position and mark it for refresh. */
static inline void set_transfer_position(LibClass175030* display, float x, float y);

/**
 * @brief Read the low byte of the selected grid index.
 * @param display Six-slot index display.
 * @return The byte-sized selected index.
 */
static inline u8 selected_option_index(FieldObject23CEA0* display);

/**
 * @brief Read an inventor option code from either transfer list.
 * @param state State containing the source and destination transfer lists.
 * @param list List selector, one or two.
 * @param index Selected list position.
 * @return Stored option code, or zero when the list or index check fails.
 */
static inline u32 transfer_inventor_option_code(ItemCreationSelectedDisplayState* state, u8 list, s32 index);

/**
 * @brief Convert an inventor option code to an inventor ID.
 * @param value Inventor option code, or zero for an empty entry.
 * @return Inventor ID, or zero for an empty entry.
 */
static inline u32 option_list_index(u8 value);

/**
 * @brief Store the selected inventor ID for a transfer list.
 * @param object Inventor transfer window.
 * @param list One selects the source list; two selects the destination list.
 * @param inventor_id Inventor ID to store.
 */
static inline void set_transfer_inventor_id(InventorTransferWindow* object, u8 list, u8 inventor_id);

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
 * @brief Convert an inventor option code to its resource slot.
 * @param inventor_option_code Inventor option code, or zero for an empty entry.
 * @return Resource slot corresponding to the option code.
 */
static inline u32 inventor_resource_index(u8 inventor_option_code);

/**
 * @brief Read the selected creation skill for a development line.
 * @param state Current selection state.
 * @param line_index Development-line index, zero through two.
 * @return Selected skill ID, or zero when none is selected.
 */
static inline u8 line_skill_id(const ItemCreationSelectedDisplayState* state, u16 line_index);

/**
 * @brief Store the selected creation skill for a development line.
 * @param state Current selection state.
 * @param line_index Development-line index, zero through two.
 * @param skill_id Selected skill ID, or zero to clear it.
 */
static inline void set_line_skill_id(ItemCreationSelectedDisplayState* state, u8 line_index, u8 skill_id);

/**
 * @brief Read the stored plan mode for a development line.
 * @param state Current selection state.
 * @param line_index Development-line index, zero through two.
 * @return Stored plan mode, or zero when no plan is selected.
 */
static inline u8 line_plan_mode(const ItemCreationSelectedDisplayState* state, u16 line_index);

/**
 * @brief Store the plan mode for a development line.
 * @param state Current selection state.
 * @param line_index Development-line index, zero through two.
 * @param mode Plan mode to store, or zero to clear it.
 */
static inline void set_line_plan_mode(ItemCreationSelectedDisplayState* state, u8 line_index, u8 mode);

/**
 * @brief Encode a workshop ID as an inventor location code.
 * @param workshop_id Workshop ID, or zero for no workshop.
 * @return Zero for no workshop, otherwise the workshop ID plus one.
 */
static inline s32 workshop_location_code(u16 workshop_id);

/**
 * @brief Read the stored Fol after validating its checksum.
 * @param record Checked resident record containing the encoded amount.
 * @return Decoded Fol, or zero when the checksum is invalid.
 */
static inline u32 checked_fol(ResidentCheckedRecord* record);

/**
 * @brief Find an allocation record by its one-based index.
 * @param allocation_index Index narrowed to a signed halfword before validation.
 * @return Record, or null when the narrowed index is outside one through three thousand.
 */
static inline ItemCreationAllocationRecord* allocation_record(s32 allocation_index);

/**
 * @brief Test the signed one-based allocation index.
 * @param index Allocation index.
 * @return True for indices from one through three thousand.
 */
static inline bool valid_allocation_index(s16 index);

/**
 * @brief Test whether the packed allocation checksum differs.
 * @param record Allocation record to validate.
 * @return True when the stored checksum differs.
 */
static inline bool allocation_invalid(ItemCreationAllocationRecord* record);

/**
 * @brief Read the ten-bit allocation value from a valid record.
 * @param record Allocation record to validate.
 * @return Packed value, or zero when the checksum differs.
 */
static inline u16 allocation_value(ItemCreationAllocationRecord* record);

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

static inline u32 inventor_resource_index(u8 inventor_option_code)
{
    if (inventor_option_code == 0)
    {
        return 0;
    }
    return inventor_option_code - 11;
}

/** @brief Store the window byte at offset 0x0C. @param value Value to store. */
void FieldClass15AE70::func_slot24(u8 value)
{
    unk0c = value;
}

/** @brief Read the window byte at offset 0x0C. @return Stored byte. */
u8 FieldClass15AE70::func_slot28()
{
    return unk0c;
}

/** @brief Store the window byte at offset 0x08. @param value Value to store. */
void FieldClass15AE70::func_slot2c(u8 value)
{
    unk08 = value;
}

/** @brief Read the window byte at offset 0x08. @return Current field value. */
u8 FieldClass15AE70::func_slot30()
{
    return unk08;
}

/** @brief Store the window halfword at offset 0x0A. @param value Value to store. */
void FieldClass15AE70::func_slot34(u16 value)
{
    unk0a = value;
}

/** @brief Read the window halfword at offset 0x0A. @return Current field value. */
u16 FieldClass15AE70::func_slot38()
{
    return unk0a;
}

/** @brief Store the alternate associated pointer. @param associated Pointer to store. */
void FieldClass15AE70::func_slot48(void* associated)
{
    unk9c = associated;
}

/** @brief Read the alternate associated pointer. @return Stored pointer. */
void* FieldClass15AE70::func_slot4c()
{
    return unk9c;
}

/** @brief Store the opaque source word. @param value Word to store. */
void FieldClass15AE70::func_slot50(u32 value)
{
    unk04 = value;
}

/** @brief Return the stored resource source word. @return Stored word. */
u32 FieldClass15AE70::func_slot54()
{
    return unk04;
}

/** @brief Return the window's nested display container. @return Stored container. */
LibObject178660* FieldClass15AE70::func_slot58()
{
    return unk10;
}

/** @brief Leave the default window message unchanged. @param text_key Message key; unused. */
void FieldClass15AE70::func_slot60(s32 text_key)
{
}

/** @brief Perform the default window hook at slot 0x64. */
void FieldClass15AE70::func_slot64()
{
}

/** @brief Perform the default window hook at slot 0x68. */
void FieldClass15AE70::func_slot68()
{
}

/** @brief Perform the default window hook at slot 0x6C. */
void FieldClass15AE70::func_slot6c()
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

/** @brief Perform the default window hook at slot 0xA0. */
void FieldClass15AE70::func_slota0()
{
}

/** @brief Perform the default window hook at slot 0xA4. */
void FieldClass15AE70::func_slota4()
{
}

/** @brief Perform the default window hook at slot 0xA8. */
void FieldClass15AE70::func_slota8()
{
}

/** @brief Perform the default window hook at slot 0xAC. */
void FieldClass15AE70::func_slotac()
{
}

/** @brief Perform the default window action at slot 0xB8. @return Zero. */
s32 FieldClass15AE70::func_slotb8()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xBC. @return Zero. */
s32 FieldClass15AE70::func_slotbc()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xC0. @return Zero. */
s32 FieldClass15AE70::func_slotc0()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xC4. @return Zero. */
s32 FieldClass15AE70::func_slotc4()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xC8. @return Zero. */
s32 FieldClass15AE70::func_slotc8()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xCC. @return Zero. */
s32 FieldClass15AE70::func_slotcc()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xD0. @return Zero. */
s32 FieldClass15AE70::func_slotd0()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xD4. @return Zero. */
s32 FieldClass15AE70::func_slotd4()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xD8. @return Zero. */
s32 FieldClass15AE70::func_slotd8()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xDC. @return Zero. */
s32 FieldClass15AE70::func_slotdc()
{
    return 0;
}

/** @brief Perform the default window action at slot 0xE0. */
void FieldClass15AE70::func_slote0()
{
}

/** @brief Perform the default window action at slot 0xE4. */
void FieldClass15AE70::func_slote4()
{
}

/** @brief Read the window byte at offset 0x0D. @return Stored unsigned byte. */
u8 FieldClass15AE70::func_slote8()
{
    return unk0d;
}

/** @brief Store the window byte at offset 0x0D. @param value Unsigned byte to store. */
void FieldClass15AE70::func_slotec(u8 value)
{
    unk0d = value;
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
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 WorkshopFullDialog::func_slotf4(u32 associated)
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

/**
 * @brief Refresh the assignment confirmation Yes and No colors from the grid selection.
 * @param object Assignment confirmation dialog.
 */
static inline void update_assignment_choice_colors(AssignInventorDialog* object)
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
            update_assignment_choice_colors(object);
        }
        break;
    case 0:
        object->func_slot20(0);
        if (object->unka8 != 0)
        {
            func_0023C550(object->unka8, 1);
            func_0023CEA0(object->unka8, 0);
            update_assignment_choice_colors(object);
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
            update_assignment_choice_colors(this);
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
            update_assignment_choice_colors(this);
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
 * @brief Store an inventor's location code when the option table is present.
 * @param state Selection state with its optional option table.
 * @param inventor_option_code Inventor slot in the option table.
 * @param location_code Location code to store.
 */
static inline void store_inventor_location_code(ItemCreationSelectedDisplayState* state, u8 inventor_option_code, u8 location_code)
{
    if (state->unk40 != 0)
    {
        state->unk40->unk188[inventor_option_code] = location_code;
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
        store_inventor_location_code(state, index, code);
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
 * @param associated Full resource source word.
 * @return Zero without an option code, or one after setup.
 */
s32 AssignInventorDialog::func_slotf4(u32 associated)
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
    update_assignment_choice_colors(this);
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
static inline u16 inventor_location_code(FieldRuntimeValues* table, u8 inventor_option_code)
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
        LibClass175030* workshop_display = object->workshop_selection_display;
        if (workshop_display != 0)
        {
            workshop_display->unk30 = 128.0f;
            workshop_display->unk3c = 1;
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
        LibClass175030* workshop_display = object->workshop_selection_display;
        if (workshop_display != 0)
        {
            workshop_display->unk30 = 64.0f;
            workshop_display->unk3c = 1;
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
 * @brief Set the display opacity and mark it for drawing.
 * @param display Drawing display.
 * @param opacity Opacity value.
 */
static inline void set_display_opacity(LibClass175030* display, float opacity)
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
    set_display_opacity(this->workshop_selection_display, 64.0f);
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

    if (this->workshop_selection_display != 0 && this->workshop_selection_display->unk35 != 0)
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
            position = selection->workshop_map_positions[index - 1].unk00;
        }
        this->workshop_selection_display->func_00466E40(position[0], position[1], 0.05f);
        func_002CFE40(D_001B643C->unk10, 0);
    }
    selected = this->workshop_selection->selected_workshop_id;
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
 * @brief Find an NPC inventor's talent record.
 * @param index Inventor ID minus one.
 * @return Record at that index.
 */
static inline const ItemCreationInventorTalent* inventor_talent_record(s32 index)
{
    return &D_501DA0[index];
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
        const ItemCreationInventorTalent* record = inventor_talent_record(inventor_id - 1);
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
 * @brief Find a runtime inventor record by its one-based index.
 * @param state State containing the runtime inventor records.
 * @param record_index One-based inventor record index.
 * @return Selected inventor record, or null for an index outside one through thirty-eight.
 */
static inline ItemCreationInventorRecord* runtime_inventor_record(ItemCreationRuntimeData* state, u8 record_index)
{
    u8 valid = record_index >= 1 && record_index < 39;
    if (valid)
    {
        return &state->inventors[record_index - 1];
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
    display->numeric_value = talent;
    display->unk3c = 1;
}

/**
 * @brief Show an inventor's talent for one skill.
 * @param object Inventor talents window.
 * @param record Selected inventor record.
 * @param index Skill index from zero through seven.
 */
static inline void show_inventor_skill(InventorTalentsWindow* object, ItemCreationInventorRecord* record, u8 index)
{
    object->skill_labels[index]->set_color(0x808080);
    u8 talent = inventor_talent(record->inventor_id, index);
    LibObject174F20* value_display = object->skill_values[index];
    set_talent_value(value_display, talent);
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
        ItemCreationInventorRecord* record = runtime_inventor_record(D_001B64F8, code);

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
 * @param associated Full resource source word.
 * @return One after setup completes.
 */
s32 InventorTalentsWindow::func_slotf4(u32 associated)
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
        skill_values[index]->func_00464D90(x, y + 21.0f, 38.4f, 19.2f, 99, (s32)associated, 1);
        skill_values[index]->set_mode(1);
        set_text_horizontal_scale(skill_labels[index], 0.6f);
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

static inline u32 transfer_inventor_option_code(ItemCreationSelectedDisplayState* state, u8 list, s32 index)
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
        return state->source_transfer_inventor_option_codes[index];
    case 2:
        return state->destination_transfer_inventor_option_codes[index];
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

static inline void set_transfer_inventor_id(InventorTransferWindow* object, u8 list, u8 inventor_id)
{
    switch (list)
    {
    case 1:
        object->source_inventor_id = inventor_id;
        break;
    case 2:
        object->destination_inventor_id = inventor_id;
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
            u32 value = transfer_inventor_option_code(state, list, selected_option_index(unkc8));
            u8 result = value;
            if (value != 0)
            {
                result = option_list_index(value);
            }
            set_transfer_inventor_id(target, list, result);
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
    unkc4->inventor_transfer_stage = 2;
    InventorTransferWindow* target = static_cast<InventorTransferWindow*>(func_slot44());
    if (target != 0)
    {
        switch (target->selection_state->inventor_transfer_stage)
        {
        case 0:
            target->unk16c->unk3f = 0;
            target->workshop_selection_display->unk3f = 1;
            break;
        case 1:
            break;
        case 2:
            target->workshop_selection_display->unk3f = 1;
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
        u8 value = transfer_inventor_option_code(unkc4, list, selected_option_index(unkc8));
        item_creation_advance_inventor_transfer(unkc4, value);
    }
    return 1;
}

/**
 * @brief Set up the option window and recover its associated display.
 * @param associated Full resource source word.
 * @return Zero when no option state is attached, or one after setup.
 */
s32 DestinationInventorStrip::func_slotf4(u32 associated)
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
            u32 value = transfer_inventor_option_code(state, list, selected_option_index(unkc8));
            u8 result = value;
            if (value != 0)
            {
                result = option_list_index(value);
            }
            set_transfer_inventor_id(target, list, result);
            func_0034DB00(target, 0xFF);
        }
    }
}

/**
 * @brief Read the raw selection flag for a one-based workshop ID.
 * @param selection Workshop selection containing the flags.
 * @param workshop_id One-based workshop ID.
 * @return Stored workshop selection flag.
 */
static inline u8 workshop_selection_flag(ItemCreationSelection* selection, u8 workshop_id)
{
    return selection->workshop_selection_flags[workshop_id - 1];
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
    return selection->workshop_map_positions[workshop_id - 1].unk00;
}

/**
 * @brief Set the transfer display position and mark it for refresh.
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
    unkc4->inventor_transfer_stage = 0;
    InventorTransferWindow* target = static_cast<InventorTransferWindow*>(func_slot44());
    if (target != 0)
    {
        u8 selected = unka9;
        target->workshop_selection->selected_workshop_id = selected;
        const float* position = workshop_map_position(target->workshop_selection, selected);
        set_transfer_position(target->workshop_selection_display, position[0], position[1]);
        switch (target->selection_state->inventor_transfer_stage)
        {
        case 0:
            target->unk16c->unk3f = 0;
            target->workshop_selection_display->unk3f = 1;
            break;
        case 1:
            break;
        case 2:
            target->workshop_selection_display->unk3f = 1;
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
        u8 value = transfer_inventor_option_code(unkc4, unka8, selected_option_index(unkc8));
        item_creation_advance_inventor_transfer(unkc4, value);
    }
    InventorTransferWindow* target = static_cast<InventorTransferWindow*>(func_slot44());
    if (target != 0)
    {
        switch (target->selection_state->inventor_transfer_stage)
        {
        case 0:
            target->unk16c->unk3f = 0;
            target->workshop_selection_display->unk3f = 1;
            break;
        case 1:
            break;
        case 2:
            target->workshop_selection_display->unk3f = 1;
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
 * @param associated Full resource source word.
 * @return Zero when no option state is attached, or one after setup.
 */
s32 SourceInventorStrip::func_slotf4(u32 associated)
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
        status = state->inventor_transfer_stage;
        if (list == 1)
        {
            switch (status)
            {
        case 1:
        case 2:
        case 3:
                value = transfer_inventor_option_code(state, list, selected_option_index(unkc8));
                result = value;
                if (value != 0)
                {
                    result = option_list_index(value);
                }
                set_transfer_inventor_id(target, list, result);
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
                value = transfer_inventor_option_code(unkc4, list, selected_option_index(unkc8));
                result = value;
                if (value != 0)
                {
                    result = option_list_index(value);
                }
                target = unkcc;
                set_transfer_inventor_id(target, list, result);
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
            u32 value = transfer_inventor_option_code(state, list, selected_option_index(unkc8));
            u8 result = value;
            if (value != 0)
            {
                result = option_list_index(value);
            }
            set_transfer_inventor_id(target, list, result);
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
        u8 value = transfer_inventor_option_code(unkc4, list, selected_option_index(unkc8));
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
            count = object->unkc4->source_transfer_workshop_id;
        }
        else
        {
            count = object->unkc4->destination_transfer_workshop_id;
        }
        object->unka9 = count;
        slot = 0;
        selected = object->unkc4->source_transfer_workshop_id;
        status = object->unkc4->inventor_transfer_stage;
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
                u8 value = transfer_inventor_option_code(object->unkc4, list, (u16)index);
                if (value == 0)
                {
                    allocation = func_002D3D80(D_001B643C->unk20, 0);
                    record = func_002D3CC0(D_001B643C->unk20, 16);
                }
                else
                {
                    u32 resource_index = inventor_resource_index(value);
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
            option = object->workshop_selection->selected_workshop_id;
        }
        switch (object->selection_state->inventor_transfer_stage)
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
        u32 associated = object->func_slot54();
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
/**
 * @brief Test the accepted one-based skill-code range.
 * @param skill_code Skill code.
 * @return Whether it is one through nine.
 */
static inline u8 skill_code_in_range(u8 skill_code)
{
    return skill_code > 0 && skill_code < 10;
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
        ItemCreationInventorRecord* record = runtime_inventor_record(D_001B64F8, selected_inventor_id);
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
                    const ItemCreationInventorTalent* single = inventor_talent_record(inventor_id - 1);
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
            u32 associated = object->func_slot54();
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
            u32 associated = object->func_slot54();
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
        option = object->workshop_selection->selected_workshop_id;
    }
    u32 stage = object->selection_state->inventor_transfer_stage;
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

    if (workshop_selection_display != 0 && workshop_selection_display->unk35 != 0)
    {
        selection = &unkdc;
        index = func_003696B0(selection, direction);
        position = workshop_map_position(selection, index);
        workshop_selection_display->func_00466E40(position[0], position[1], 0.05f);
        func_002CFE40(D_001B643C->unk10, 0);
    }
    selected = workshop_selection->selected_workshop_id;
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
    switch (state->inventor_transfer_stage)
    {
    case 0:
    {
        item_creation_restore_workshop_assignments(state);
        ItemCreationSelectedDisplayState* count_state = selection_state;
        for (s32 index = 1; index < 28; index++)
        {
            ItemCreationInventorRecord* record = runtime_inventor_record(D_001B64F8, index);
            if (record != 0 && record->contract_status == 2)
            {
                count_state->contracted_inventor_tally++;
            }
        }
        item_creation_advance_inventor_transfer(selection_state, -1);
        state = selection_state;
        state->requested_window_group = 0;
        func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
        state = selection_state;
        state->func_00263C70(state->main_menu);
        break;
    }
    case 1:
        break;
    case 2:
    {
        state->inventor_transfer_stage = 1;
        TransferInventorStrip* window = static_cast<TransferInventorStrip*>(func_slot44());
        if (window->unkc8 != 0)
        {
            func_0023CEA0(window->unkc8, 1);
        }
        D_001B643C->unk10->unk14->func_00263C70(window);
        item_creation_refresh_team_and_transfer_windows(selection_state, 7);
        workshop_selection_display->unk3f = 0;
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
    switch (selection_state->inventor_transfer_stage)
    {
    case 0:
    {
        ItemCreationSelection* selection = workshop_selection;
        const float* position = selection->workshop_map_positions[selection->selected_workshop_id - 1].unk00;
        set_transfer_position(unk16c, position[0], position[1]);
        unk16c->unk3f = 1;
        workshop_selection_display->unk3f = 0;
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
        if (destination_workshop_id == selection_state->pending_transfer_source_workshop_id)
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

    if (workshop_selection_display != 0 && workshop_selection_display->unk35 != 0)
    {
        selection = &unkdc;
        index = func_003696B0(selection, direction);
        position = workshop_map_position(selection, index);
        workshop_selection_display->func_00466E40(position[0], position[1], 0.05f);
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
        u8 enabled = workshop_selection_flag(&object->unkdc, code);
        const float* position = workshop_map_position(&object->unkdc, code);
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

/**
 * @brief Initialize the base selection window at its fixed coordinates.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 ItemCreationClass185A60::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    return 1;
}

/**
 * @brief Test whether any line's stopped flag is clear for the current run.
 * @param state Selection state.
 * @return Whether at least one line's stopped flag is clear.
 */
static inline bool any_line_not_stopped(const ItemCreationSelectedDisplayState* state)
{
    if (state->line_stopped[0] != 0 && state->line_stopped[1] != 0 && state->line_stopped[2] != 0)
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
    ItemCreationSelectedDisplayState* state = selection_state;
    if (state != 0)
    {
        if (any_line_not_stopped(state) == false)
        {
            DevelopmentCompleteDialog* window = new (0) DevelopmentCompleteDialog;
            state = selection_state;
            window->func_slotf4(state->func_00263CC0());
            state = selection_state;
            state->func_00263FD0(window);
            state = selection_state;
            state->func_00263C70(window);
            func_00112400(D_001B65F8, 8, 0, 0, 127, 64, 0);
        }
        else
        {
            state->development_processing_enabled = 1;
        }
    }
    return 1;
}

/**
 * @brief Return the selection state's resource source word.
 * @param object Selection state.
 * @return Stored word.
 */
u32 func_0034FF60(ItemCreationSelectedDisplayState* object)
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
    ItemCreationSelectedDisplayState* state = selection_state;
    if (state != 0)
    {
        if (any_line_not_stopped(state) == false)
        {
            DevelopmentCompleteDialog* window = new (0) DevelopmentCompleteDialog;
            state = selection_state;
            window->func_slotf4(state->func_00263CC0());
            state = selection_state;
            state->func_00263FD0(window);
            state = selection_state;
            state->func_00263C70(window);
            func_00112400(D_001B65F8, 8, 0, 0, 127, 64, 0);
        }
        else
        {
            state->development_processing_enabled = 1;
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
    if (object->line_label != 0)
    {
        object->line_index = mode;
        switch (object->line_index)
        {
        case 0:
            func_4C6DF0(object->line_label, object->func_slot54(), 0x15FD7, 0);
            break;
        case 1:
            func_4C6DF0(object->line_label, object->func_slot54(), 0x15FD8, 0);
            break;
        case 2:
            func_4C6DF0(object->line_label, object->func_slot54(), 0x15FD9, 0);
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
    if (choice_selector != 0)
    {
        choice_selector->func_0023B280(2);
        if (choice_selector != 0)
        {
            for (s32 index = 0; index < 3; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(
                    func_0036F230(&unk2c, index)->unk00);
                if (index == 2)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    selection_marker->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    ItemCreationNineResourceView* parent = state->development_lines_window;
    FieldObject23CEA0* marker = parent->unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 128.0f;
        marker->unkae = 1;
        parent->unka8->development_processing_enabled = 1;
    }
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 2;
}

/**
 * @brief Read the stored plan mode for a development line.
 * @param state Current selection state.
 * @param line_index Development-line index, zero through two.
 * @return Stored plan mode, or zero when no plan is selected.
 */
static inline u8 line_plan_mode(const ItemCreationSelectedDisplayState* state, u16 line_index)
{
    return state->line_plan_modes[line_index];
}
/**
 * @brief Read the selected creation skill for a development line.
 * @param state Current selection state.
 * @param line_index Development-line index, zero through two.
 * @return Selected skill ID, or zero when none is selected.
 */
static inline u8 line_skill_id(const ItemCreationSelectedDisplayState* state, u16 line_index)
{
    return state->line_skill_ids[line_index];
}
/**
 * @brief Store the plan mode for a development line.
 * @param state Current selection state.
 * @param line_index Development-line index, zero through two.
 * @param mode Plan mode to store, or zero to clear it.
 */
static inline void set_line_plan_mode(ItemCreationSelectedDisplayState* state, u8 line_index, u8 mode)
{
    state->line_plan_modes[line_index] = mode;
}
/**
 * @brief Store the selected creation skill for a development line.
 * @param state Current selection state.
 * @param line_index Development-line index, zero through two.
 * @param skill_id Selected skill ID, or zero to clear it.
 */
static inline void set_line_skill_id(ItemCreationSelectedDisplayState* state, u8 line_index, u8 skill_id)
{
    state->line_skill_ids[line_index] = skill_id;
}

/**
 * @brief Apply the selected abort choice.
 * @return Callback result selected by the current action.
 */
s32 AbortDevelopmentDialog::func_slotb0()
{
    if (choice_selector == 0)
    {
        return 0;
    }
    switch (choice_selector->func_0023B3A0())
    {
    case 0:
        func_slot20(0);
        if (choice_selector != 0)
        {
            choice_selector->func_0023B280(2);
            if (choice_selector != 0)
            {
                for (s32 index = 0; index < 3; index++)
                {
                    LibObject178750* display = static_cast<LibObject178750*>(
                        func_0036F230(&unk2c, index)->unk00);
                    if (index == 2)
                    {
                        display->set_color(ITEM_CREATION_COLOR_SELECTED);
                        selection_marker->func_0023B7E0(display);
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
            ItemCreationSelectedDisplayState* state = selection_state;
            state->line_stopped[(u8)slot] = 1;
            ItemCreationClass184EF0* target = state->line_targets[(u8)slot];
            if (target != 0)
            {
                target->func_slot10();
            }
            if (any_line_not_stopped(selection_state) == false)
            {
                for (s32 group = 0; group < 3; group++)
                {
                    selection_state->line_item_ids[(u16)group][0] = 0;
                    selection_state->line_item_ids[(u16)group][1] = 0;
                    if (line_plan_mode(selection_state, group) != 0)
                    {
                        set_line_plan_mode(selection_state, group, 1);
                    }
                    if (line_skill_id(selection_state, group) == 8)
                    {
                        set_line_skill_id(selection_state, group, 0);
                        set_line_plan_mode(selection_state, group, 0);
                    }
                }
                state = selection_state;
                state->requested_window_group = 1;
                func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
                if (selection_state->line_targets[0] != 0)
                {
                    item_creation_rebuild_line_target(selection_state, 0);
                }
                if (selection_state->line_targets[1] != 0)
                {
                    item_creation_rebuild_line_target(selection_state, 1);
                }
                if (selection_state->line_targets[2] != 0)
                {
                    item_creation_rebuild_line_target(selection_state, 2);
                }
                selection_state->development_processing_enabled = 0;
            }
        }
        break;
    case 1:
    {
        ItemCreationSelectedDisplayState* state = selection_state;
        u8 selected_slot = state->dialog_line_index;
        if (selected_slot != 0xFF)
        {
            state->line_stopped[selected_slot] = 1;
            ItemCreationClass184EF0* target = state->line_targets[selected_slot];
            if (target != 0)
            {
                target->func_slot10();
            }
            selection_state->dialog_line_index = 0xFF;
            func_slot20(0);
            if (choice_selector != 0)
            {
                choice_selector->func_0023B280(2);
                if (choice_selector != 0)
                {
                    for (s32 index = 0; index < 3; index++)
                    {
                        LibObject178750* display = static_cast<LibObject178750*>(
                            func_0036F230(&unk2c, index)->unk00);
                        if (index == 2)
                        {
                            display->set_color(ITEM_CREATION_COLOR_SELECTED);
                            selection_marker->func_0023B7E0(display);
                        }
                        else
                        {
                            display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                        }
                    }
                }
            }
            if (any_line_not_stopped(selection_state) == false)
            {
                DevelopmentCompleteDialog* window = new (0) DevelopmentCompleteDialog;
                window->func_slotf4(selection_state->func_00263CC0());
                selection_state->func_00263FD0(window);
                selection_state->func_00263C70(window);
                func_00112400(D_001B65F8, 8, 0, 0, 127, 64, 0);
                return 0;
            }
            state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
            ItemCreationNineResourceView* parent = state->development_lines_window;
            FieldObject23CEA0* marker = parent->unk10c;
            if (marker != 0)
            {
                marker->FieldClass151C50::unk30 = 128.0f;
                marker->unkae = 1;
                parent->unka8->development_processing_enabled = 1;
            }
            D_001B643C->unk10->unk14->func_00263C70(parent);
        }
        break;
    }
    case 2:
        selection_state->dialog_line_index = 0xFF;
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
    if (choice_selector != 0 && (u8)choice_selector->func_0023B3B0(1) != 1)
    {
        u16 selected = choice_selector->func_0023B3A0();
        if (choice_selector != 0)
        {
            s32 index;
            for (index = 0; index < 3; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    selection_marker->func_0023B7E0(display);
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
    if (choice_selector != 0 && (u8)choice_selector->func_0023B3B0(0) != 1)
    {
        u16 selected = choice_selector->func_0023B3A0();
        if (choice_selector != 0)
        {
            s32 index;
            for (index = 0; index < 3; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    selection_marker->func_0023B7E0(display);
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
 * @brief Test whether the inventor status list has no pending action.
 * @param container Inventor status list.
 * @return One when the inherited action mode is zero.
 */
static inline u8 inventor_status_list_idle(InventorStatusList* container)
{
    return container->unk4a4 == 0;
}

/** @brief Finish or cancel the inventor status list's pending action while this window is current. */
void InventorStatusWindow::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }
    InventorStatusList* child = status_list;
    if (child == 0)
    {
        return;
    }
    switch (unkbc)
    {
    case 0:
        break;
    case 1:
        if (inventor_status_list_idle(child))
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
                status_list = 0;
                func_slot20(0);
                ItemCreationClass186770* window = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14)->development_lines_window;
                FieldObject23CEA0* grid = window->unk10c;
                if (grid != 0)
                {
                    grid->FieldClass151C50::unk30 = 128.0f;
                    grid->unkae = 1;
                    window->unka8->development_processing_enabled = 1;
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
 * @brief Create and queue the inventor status list, or reset its active flag.
 * @param object Inventor status window receiving the list.
 * @param mode One creates the list when absent and inactive; zero resets the flag.
 */
extern "C" void func_00351510(InventorStatusWindow* object, u8 mode)
{
    s32 count = 0;
    switch (mode)
    {
    case 1:
        if (object->status_list == 0 && object->unkbc == 0)
        {
            InventorStatusList* container = new (0) InventorStatusList;
            object->status_list = container;
            for (s32 index = 0; index < 28; index++)
            {
                if (runtime_inventor_record(D_001B64F8, static_cast<u8>(index + 1))->contract_status != 0)
                {
                    count++;
                }
            }
            func_00352020(object->status_list, object->func_slot54(), count);
            func_00465B20(D_001B657C, object->status_list);
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
 * @param associated Full resource source word.
 * @return One after setup completes.
 */
s32 WorkshopInventorStrip::func_slotf4(u32 associated)
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
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 DevelopmentControlPanel::func_slotf4(u32 associated)
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
 * @brief Create the abort confirmation and its three choices.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 AbortDevelopmentDialog::func_slotf4(u32 associated)
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
    choice_selector = new (0) FieldClass153130;
    choice_selector->func_0023B530(1, 3, 1, 2, 1, 164.0f, 94.0f, 0.0f, 30.0f);
    func_004C6190(unk10, choice_selector);
    LibObject178750* target = static_cast<LibObject178750*>(func_0036F230(&unk2c, 2)->unk00);
    selection_marker = new (0) FieldClass153170;
    selection_marker->func_0023B850(target, ITEM_CREATION_COLOR_SELECTED);
    func_004C6190(unk10, selection_marker);
    choice_selector->func_0023B280(2);
    if (choice_selector != 0)
    {
        for (s32 index = 0; index < 3; index++)
        {
            LibObject178750* display = static_cast<LibObject178750*>(
                func_0036F230(&unk2c, index)->unk00);
            if (index == 2)
            {
                display->set_color(ITEM_CREATION_COLOR_SELECTED);
                selection_marker->func_0023B7E0(display);
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
 * @brief Create and attach the inventor status window panel, headings, and frame.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 InventorStatusWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 64.0f, 84.0f, 15);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 520.0f, 372.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* text0 = new (0) LibObject178750;
    text0->func_004C7FE0(12.0f, 12.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x15FB2, 1);
    set_text_spacing(text0, -1.0f);
    set_text_horizontal_scale(text0, 0.9f);
    text0->set_color(ITEM_CREATION_COLOR_ASSIGNED);
    func_004C6190(unk10, text0);
    LibObject178750* text1 = new (0) LibObject178750;
    text1->func_004C7FE0(225.0f, 12.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x15FB5, 1);
    set_text_spacing(text1, -1.0f);
    set_text_horizontal_scale(text1, 0.9f);
    text1->set_color(ITEM_CREATION_COLOR_ASSIGNED);
    func_004C6190(unk10, text1);
    LibObject178750* text2 = new (0) LibObject178750;
    text2->func_004C7FE0(340.0f, 12.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x15FB3, 1);
    set_text_spacing(text2, -1.0f);
    set_text_horizontal_scale(text2, 0.9f);
    text2->set_color(ITEM_CREATION_COLOR_ASSIGNED);
    func_004C6190(unk10, text2);
    LibObject178750* text3 = new (0) LibObject178750;
    text3->func_004C7FE0(413.0f, 12.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x15FB4, 1);
    set_text_spacing(text3, -1.0f);
    set_text_horizontal_scale(text3, 0.9f);
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
    display->inventor_name.func_004C7FE0(0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    func_004C6190(this, &display->inventor_name);
    display->contract_status_label.func_004C7FE0(0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    func_004C6190(this, &display->contract_status_label);
    display->skill_label.func_004C7FE0(0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    func_004C6190(this, &display->skill_label);
    display->work_status_label.func_004C7FE0(0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    func_004C6190(this, &display->work_status_label);
    return display;
}

/**
 * @brief Configure the option container and create its visible rows.
 * @param object Option container to configure.
 * @param associated Full resource source word.
 * @param count Number of selectable options.
 * @return One on success, or zero when configuration or allocation fails.
 */
extern "C" s32 func_00352020(InventorStatusList* object, u32 associated, s32 count)
{
    object->text_source = associated;
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
    text_source = 0;
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
        workshop_selection_display = new (0) ItemCreationClass175030;
        if (workshop_selection_display == 0)
        {
            display_created = 0;
        }
        else
        {
            func_00467360(workshop_selection_display, x, y);
            func_004C6190(unk10, workshop_selection_display);
            display_created = 1;
        }
    }
    return display_created;
}

/**
 * @brief Create the workshop selector, facility labels and assignment controls.
 * @param associated Full resource source word.
 * @return Whether the displays were created.
 */
s32 WorkshopSelectionWindow::func_slotf4(u32 associated)
{
    this->FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    this->workshop_selection->unk79 = 2;
    this->workshop_selection->selected_workshop_id = 1;
    float x;
    float initial_y;
    initial_y = this->workshop_selection->workshop_map_positions[0].unk00[1];
    x = this->workshop_selection->workshop_map_positions[0].unk00[0];
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
    set_text_spacing(this->workshop_name, -1.0f);
    this->workshop_name->set_scale(0.8f, 0.8f);
    func_004C6190(this->unk10, this->workshop_name);
    LibObject178750* option_heading = new (0) LibObject178750;
    option_heading->func_004C7FE0(448.0f, 84.0f, 160.0f, 24.0f, (s32)associated, 0x32D7, 1);
    option_heading->set_mode(1);
    option_heading->set_vertical_alignment(1);
    option_heading->set_scale(0.8f, 0.8f);
    option_heading->set_color(0x808050);
    set_text_horizontal_scale(option_heading, 0.5f);
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
        set_text_horizontal_scale(this->facility_labels[index], 0.6f);
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
 * @param associated Full resource source word.
 * @return Whether the window was created.
 */
s32 InventorTransferWindow::func_slotf4(u32 associated)
{
    if (selection_state == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    workshop_selection->unk79 = 1;
    current_workshop_id = selection_state->workshop_id;
    workshop_selection->selected_workshop_id = current_workshop_id;
    const float* position = workshop_map_position(workshop_selection, current_workshop_id);
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
    set_display_opacity(unk16c, 80.0f);
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
    static_cast<LibObject174F20*>(source_inventor_widgets[2])->func_00464D90(528.0f, y, 38.4f, 19.2f, 99, (s32)associated, 1);
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
    static_cast<LibObject174F20*>(destination_inventor_widgets[2])->func_00464D90(528.0f, y, 38.4f, 19.2f, 99, (s32)associated, 1);
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
    inventor_name.unk18.unk00 = shifted_position(x, 12.0f);
    inventor_name.unk18.unk04 = y;
    inventor_name.unk3c = 1;
    contract_status_label.unk18.unk00 = shifted_position(x, 240.0f) - 20.0f;
    contract_status_label.unk18.unk04 = y;
    contract_status_label.unk3c = 1;
    skill_label.unk18.unk00 = shifted_position(x, 345.0f) - 8.0f;
    skill_label.unk18.unk04 = y;
    skill_label.unk3c = 1;
    work_status_label.unk18.unk00 = shifted_position(x, 412.0f);
    work_status_label.unk18.unk04 = y;
    work_status_label.unk3c = 1;
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
    u32 text_source = static_cast<InventorStatusList*>(source)->text_source;
    ItemCreationInventorRecord* records[28];
    s32 count = 0;
    for (s32 position = 0; position < 28; position++)
    {
        ItemCreationInventorRecord* record = runtime_inventor_record(D_001B64F8, static_cast<u8>(position + 1));
        if (record->contract_status != 0)
        {
            records[count++] = record;
        }
    }
    ItemCreationInventorRecord** selected = &records[index];
    func_4C6DF0(&inventor_name, text_source, (*selected)->inventor_id + 0x3584, 0);
    func_4C6DF0(&contract_status_label, text_source, (*selected)->contract_status + 0x15FB7, 0);
    if ((*selected)->contract_status == 2)
    {
        contract_status_label.set_color(0x505080);
    }
    else
    {
        contract_status_label.set_color(0x805050);
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
    func_4C6DF0(&skill_label, text_source, skill_index + ITEM_CREATION_SKILL_LABEL_BASE, 0);
    func_4C6DF0(&work_status_label, text_source, ((*selected)->working != 0) + 0x15FB6, 0);
}

/**
 * @brief Store the row display flag on each text widget.
 * @param source Owning row collection; unused.
 * @param value Flag byte to store.
 */
void InventorStatusRow::func_slot0c(LibClass1721F0* source, u8 value)
{
    inventor_name.unk3d = value;
    contract_status_label.unk3d = value;
    skill_label.unk3d = value;
    work_status_label.unk3d = value;
}

/**
 * @brief Calculate the packed allocation checksum.
 * @param record Allocation record to read.
 * @return Calculated checksum.
 */
static inline u16 allocation_checksum(ItemCreationAllocationRecord* record)
{
    return (0x83CF << record->checksum_shift) ^
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
    return record->checksum != (u16)((0x83CF << record->checksum_shift) ^
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
static inline void reset_allocation_record(ItemCreationAllocationRecord* record)
{
    *(unsigned __int128*)record = 0;
    record->checksum_shift = func_0010CF80() & 3;
    record->checksum = allocation_checksum(record);
}
/**
 * @brief Reset an allocation record and initialize it from an item-type record.
 * @param record Allocation record to initialize.
 * @param item_type Runtime item-type record supplying the catalog index.
 */
static inline void initialize_allocation_from_item_type(ItemCreationAllocationRecord* record, const ItemCreationCategoryRecord* item_type)
{
    reset_allocation_record(record);
    func_40D2E0(record, item_type->catalog_index + 1, 0, 0, false, true);
}

/**
 * @brief Test the signed one-based allocation index.
 * @param index Allocation index.
 * @return True for indices from one through three thousand.
 */
static inline bool valid_allocation_index(s16 index)
{
    return index > 0 && index <= 3000;
}
/**
 * @brief Find an allocation record by its one-based index.
 * @param allocation_index Index narrowed to a signed halfword before validation.
 * @return Record, or null when the narrowed index is outside one through three thousand.
 */
static inline ItemCreationAllocationRecord* allocation_record(s32 allocation_index)
{
    ItemCreationRuntimeData* records = D_001B64F8;
    s16 index = allocation_index;
    if (valid_allocation_index(index))
    {
        return &records->records[index - 1];
    }
    return 0;
}
/**
 * @brief Test the one-based runtime item-type index.
 * @param index One-based runtime item-type index.
 * @return True for indices from one through seven hundred fifty.
 */
static inline u8 valid_item_type_index(u16 index)
{
    return index > 0 && index <= 750;
}
/**
 * @brief Find a runtime item-type record by its one-based index.
 * @param index One-based runtime item-type index.
 * @return Record, or null for an invalid index.
 */
static inline ItemCreationCategoryRecord* item_type_record(u16 index)
{
    ItemCreationRuntimeData* records = D_001B64F8;
    if (valid_item_type_index(index))
    {
        return &records->item_types[index - 1];
    }
    return 0;
}

/**
 * @brief Set the item-name code and optional numeric suffix, marking the widget for refresh.
 * @param display Code widget.
 * @param value One-based item-name code.
 * @param suffix_number Decimal suffix, or zero to omit it.
 */
static inline void set_item_name_code(LibObject172410* display, u16 value, u8 suffix_number)
{
    display->unkfc = value;
    display->unkfe = suffix_number;
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
    ItemCreationClass184EF0* target = state->line_targets[(s8)state->dialog_line_index];
    ItemCreationAllocationRecord temporary __attribute__((aligned(16)));
    ItemCreationAllocationRecord* record = 0;
    switch (target->unk83)
    {
        case 1:
        {
            FieldClass15BB30* category_target = static_cast<FieldClass15BB30*>(target);
            ItemCreationCategoryRecord* category = item_type_record(category_target->unk3c8);
            reset_allocation_record(&temporary);
            initialize_allocation_from_item_type(&temporary, category);
            record = &temporary;
            object->unkb4->unk3f = 1;
            object->unke4->unk3f = 1;
            LibObject174F20* value = object->unkb4;
            value->numeric_value = category_target->unk3b0;
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
    set_item_name_code(object->unkb0, allocation_value(record) + 1, record->unk0c & 0x7F);
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
    if (state->resource_window != 0)
    {
        func_002FD940(state->resource_window);
        state->resource_window_release_pending = 1;
    }
    state->pending_resource_key = message;
    state->pending_secondary_resource_key = 0;
    state = object->unka8;
    state->background->func_slot58()->func_0044B110(0, 9, 1200, 0, 0.0f);
    state->status_banner->func_slot58()->func_0044B110(0, 9, 1400, 0, 0.0f);
    state->control_help->func_slot58()->func_0044B110(0, 9, 1800, 0, 0.0f);
    state->development_control_panel->func_slot58()->func_0044B110(0, 9, 1800, 0, 0.0f);
    state->development_lines_window->func_slot58()->func_0044B110(0, 9, 2000, 0, 0.0f);
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
    state->background->func_slot58()->func_0044B110(20, 0, 0, 0, 0.0f);
    state->status_banner->func_slot58()->func_0044B110(19, 0, 0, 0, 0.0f);
    state->control_help->func_slot58()->func_0044B110(18, 0, 0, 0, 0.0f);
    state->development_control_panel->func_slot58()->func_0044B110(18, 0, 0, 0, 0.0f);
    state->development_lines_window->func_slot58()->func_0044B110(17, 0, 0, 0, 0.0f);
    state = unka8;
    if (state->resource_window != 0)
    {
        func_002FD940(state->resource_window);
        state->resource_window_release_pending = 1;
    }
    state->pending_secondary_resource_key = 0;
    state->pending_resource_key = 0;
    state->inventor_resource_countdown = 0;
    ItemCreationNineResourceView* window = static_cast<ItemCreationNineResourceView*>(func_slot44());
    FieldObject23CEA0* grid = window->unk10c;
    if (grid != 0)
    {
        grid->FieldClass151C50::unk30 = 128.0f;
        grid->unkae = 1;
        window->unka8->development_processing_enabled = 1;
    }
    D_001B643C->unk10->unk14->func_00263C70(window);
    if (any_line_not_stopped(unka8) == false)
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
 * @param associated Full resource source word.
 * @param first First container configuration value.
 * @param second Second container configuration value.
 * @param third Third container configuration value.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param z Third coordinate.
 * @return One when the container is present and the source word is nonzero, otherwise zero.
 */
extern "C" s32 func_002CE760(FieldClass15AE70* object, u32 associated, s32 first, s32 second, s32 third, float x, float y, float z);
/** @brief Attach a widget to its container. @param object Container. @param child Widget to attach. */
extern "C" void func_4C6190(LibObject178660* object, LibClass178600* child);
/** Partial Field runtime reached through D_001B657C. */
struct FieldRuntime
{
    u8 unk00[0x514];
    u32 unk514;
    u32 unk518;
    u32 unk51c;
    u32 unk520;
};

/**
 * @brief Create the window's panels, text and value displays and register its runtime callback.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 ItemDetailsWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 0xA28, 28.0f, 82.0f, 0.0f);
    unke8 = new (0) LibObject178660;
    func_004C6510(unke8, 5, 0, 0, 28.0f, 82.0f, 0.0f);
    func_00465B20(D_001B657C, static_cast<LibClass174610*>(unke8));
    unkf8 = new (0) LibClass178630;
    func_004C5A80(unkf8, 1, 0.0f, 0.0f, 584.0f, 374.0f, 88.0f);
    func_4C6190(unk10, unkf8);
    func_004C4AB0(unkf8, 1500.0f);
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
    set_text_spacing(unkac, -1.0f);
    unkac->set_scale(0.8f, 0.8f);
    unkac->set_color(0x805050);
    func_4C6190(unk10, unkac);
    func_413F70(unkb0, 24.0f, 34.0f, 0.0f, 0.0f, (u16)(s32)associated, unkee + 0xC350, 0);
    set_text_spacing(unkb0, -1.0f);
    unkb0->set_scale(1.2f, 1.2f);
    func_4C6190(unk10, unkb0);
    unkb4->func_00464D90(430.0f, 16.0f, 100.0f, 30.0f, 99, 0, 0);
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
    set_text_spacing(unkbc, -1.0f);
    unkbc->set_scale(0.9f, 0.9f);
    func_4C6190(unke8, unkbc);
    unkc0->func_004C7FE0(16.0f, 155.0f, 0.0f, 0.0f, (s32)associated, 0x15FE0, 0);
    unkc0->set_scale(0.8f, 0.8f);
    unkc0->set_color(0x805050);
    set_text_spacing(unkc0, -1.0f);
    func_4C6190(unk10, unkc0);
    FieldRuntime* runtime = D_001B657C;
    runtime->unk51c = associated;
    runtime->unk520 = 0x11171;
    for (s32 index = 0; index < 8; index++)
    {
        func_4143F0(unkc4[index], 0, 1, 0, 26.0f, 178.0f + 24.0f * index, 0.0f, 0.0f);
        set_text_spacing(unkc4[index], -1.0f);
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

/** @brief Create the popup display and attach its widgets. @param associated Full resource source word. @return Always one. */
s32 MissingMaterialsDialog::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 90.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 436.0f, 160.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x1B6C, 1);
    func_004C6190(unk10, heading);
    LibObject178750* description = new (0) LibObject178750;
    description->func_004C7FE0(36.0f, 40.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x1B6F, 0);
    func_004C6190(unk10, description);
    ItemCreationClass172870* frame = new (0) ItemCreationClass172870;
    func_421170(frame, 12.0f, 100.0f, 411.0f, 4.0f);
    frame->unk50 = 0x606060;
    frame->unk3c = 1;
    func_004C6190(unk10, frame);
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(315.0f, 115.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x1B73, 0);
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
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 InsufficientFolDialog::func_slotf4(u32 associated)
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
 * @brief Clear both selected item IDs for one development line.
 * @param state Current selection state.
 * @param line_index Development-line index, zero through two.
 */
static inline void clear_line_item_ids(ItemCreationSelectedDisplayState* state, u16 line_index)
{
    s16* pair = state->line_item_ids[line_index];
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
    ItemCreationNineResourceView* window = state->development_lines_window;
    FieldObject23CEA0* grid = window->unk10c;
    if (grid != 0)
    {
        grid->FieldClass151C50::unk30 = 128.0f;
        grid->unkae = 1;
        window->unka8->development_processing_enabled = 1;
    }
    state->func_00263C70(window);
    if (any_line_not_stopped(state) == false)
    {
        for (s32 index = 0; index < 3; index++)
        {
            clear_line_item_ids(state, index);
            if (line_plan_mode(state, index) != 0)
            {
                set_line_plan_mode(state, index, 1);
            }
            if (line_skill_id(state, index) == 8)
            {
                set_line_skill_id(state, index, 0);
                set_line_plan_mode(state, index, 0);
            }
        }
        state->requested_window_group = 1;
        func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
        if (state->line_targets[0] != 0)
        {
            item_creation_rebuild_line_target(state, 0);
        }
        if (state->line_targets[1] != 0)
        {
            item_creation_rebuild_line_target(state, 1);
        }
        if (state->line_targets[2] != 0)
        {
            item_creation_rebuild_line_target(state, 2);
        }
        state->development_processing_enabled = 0;
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
    ItemCreationNineResourceView* window = state->development_lines_window;
    FieldObject23CEA0* grid = window->unk10c;
    if (grid != 0)
    {
        grid->FieldClass151C50::unk30 = 128.0f;
        grid->unkae = 1;
        window->unka8->development_processing_enabled = 1;
    }
    state->func_00263C70(window);
    if (any_line_not_stopped(state) == false)
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
    ItemDetailsWindow* window = state->item_details_window;
    func_00352DE0(window);
    window->func_slot20(1);
    window->unke8->unkab = 1;
    D_001B643C->unk10->unk14->func_00263C70(window);
    return 1;
}

/** @brief Advance the dialog choices and refresh their colors and target. */
void ItemSubmissionDialog::func_slot6c()
{
    if (choice_selector != 0 && (u8)choice_selector->func_0023B3B0(1) != 1)
    {
        u16 selected = choice_selector->func_0023B3A0();
        if (choice_selector != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    selection_marker->func_0023B7E0(display);
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
    if (choice_selector != 0 && (u8)choice_selector->func_0023B3B0(0) != 1)
    {
        u16 selected = choice_selector->func_0023B3A0();
        if (choice_selector != 0)
        {
            s32 index;
            for (index = 0; index < 2; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
                if (index == selected)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    selection_marker->func_0023B7E0(display);
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
    choice_selector->func_0023B280(1);
    if (choice_selector != 0)
    {
        s32 index;
        for (index = 0; index < 2; index++)
        {
            LibObject178750* display = static_cast<LibObject178750*>(
                func_0036F230(&unk2c, index)->unk00);
            if (index == 1)
            {
                display->set_color(0x288080);
                selection_marker->func_0023B7E0(display);
            }
            else
            {
                display->set_color(0x808080);
            }
        }
    }
    if (selection_state != 0 && selection_state->control_help != 0)
    {
        static_cast<ItemCreationControlHelp*>(selection_state->control_help)->func_003598E0(3, 1);
    }
    ItemCreationNineResourceView* parent = static_cast<ItemCreationNineResourceView*>(func_slot44());
    FieldObject23CEA0* marker = parent->unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 128.0f;
        marker->unkae = 1;
        parent->unka8->development_processing_enabled = 1;
    }
    D_001B643C->unk10->unk14->func_00263C70(parent);
    return 2;
}

/** @brief Apply the selected action or restore the resource window. @return Action status. */
s32 ItemSubmissionDialog::func_slotb0()
{
    if (choice_selector == 0)
    {
        return 0;
    }
    switch (choice_selector->func_0023B3A0())
    {
        case 0:
        {
            func_slot20(0);
            choice_selector->func_0023B280(1);
            if (choice_selector != 0)
            {
                s32 index;
                for (index = 0; index < 2; index++)
                {
                    LibObject178750* display = static_cast<LibObject178750*>(
                        func_0036F230(&unk2c, index)->unk00);
                    if (index == 1)
                    {
                        display->set_color(0x288080);
                        selection_marker->func_0023B7E0(display);
                    }
                    else
                    {
                        display->set_color(0x808080);
                    }
                }
            }
            ItemCreationSelectedDisplayState* state = selection_state;
            u8 index = state->dialog_line_index;
            state->line_stopped[index] = 1;
            ItemCreationClass184EF0* target = state->line_targets[index];
            if (target != 0)
            {
                target->func_slot0c();
            }
            target = selection_state->line_targets[(s8)selection_state->dialog_line_index];
            if (target->unk83 == 1 && static_cast<FieldClass15BB30*>(target)->unk3b0 == 0)
            {
                LineFailureDialog* next = new (0) LineFailureDialog;
                next->func_slotf4(selection_state->func_00263CC0());
                selection_state->func_00263FD0(next);
                selection_state->func_00263C70(next);
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

/** @brief Create the two-option display, selector, and marker. @param associated Full resource source word. @return Always one. */
s32 ItemSubmissionDialog::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 112.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 416.0f, 156.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FCA, 1);
    func_004C6190(unk10, heading);
    line_label = new (0) LibObject178750;
    line_label->func_004C7FE0(158.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FD7, 1);
    func_004C6190(unk10, line_label);
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
    choice_selector = new (0) FieldClass153130;
    choice_selector->func_0023B530(1, 2, 1, 1, 1, 172.0f, 92.0f, 0.0f, 28.0f);
    func_004C6190(unk10, choice_selector);
    LibObject178750* target = static_cast<LibObject178750*>(func_0036F230(&unk2c, 1)->unk00);
    selection_marker = new (0) FieldClass153170;
    selection_marker->func_0023B850(target, 0x288080);
    func_004C6190(unk10, selection_marker);
    if (choice_selector != 0)
    {
        s32 index;
        for (index = 0; index < 2; index++)
        {
            LibObject178750* display = static_cast<LibObject178750*>(func_0036F230(&unk2c, index)->unk00);
            if (index == 1)
            {
                display->set_color(0x288080);
                selection_marker->func_0023B7E0(display);
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
        value = object->unka8->assigned_inventor_option_codes[(u16)index];
        if (value != 0)
        {
            resource = (u8)inventor_resource_index(value);
            allocation = func_002D3D80(D_001B643C->unk20, resource);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            object->unkdc[index]->func_002D5CF0(allocation, record, resource);
            object->unkdc[index]->unk3f = 1;
            object->unk109++;
        }
        else
        {
            object->unkdc[index]->unk3f = 0;
        }
    }
}

/**
 * @brief Restore the resource marker and reopen its option window.
 * @return Zero when inactive, otherwise one.
 */
s32 ItemCreationClass186770::func_slotb8()
{
    if (unka8->development_processing_enabled == 0)
    {
        return 0;
    }
    FieldObject23CEA0* marker = unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 64.0f;
        marker->unkae = 1;
        unka8->development_processing_enabled = 0;
        ItemCreationSelectedDisplayState* state = unka8;
        if (state->resource_window != 0)
        {
            func_002FD940(state->resource_window);
            state->resource_window_release_pending = 1;
        }
        state->pending_secondary_resource_key = 0;
        state->pending_resource_key = 0;
        state->inventor_resource_countdown = 0;
    }
    InventorStatusWindow* next = unka8->inventor_status_window;
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
    if (unka8->development_processing_enabled == 0)
    {
        return 0;
    }
    u16 index = static_cast<u16>(unk10c->unk114);
    if (unka8->line_stopped[index] != 0)
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
        unka8->dialog_line_index = static_cast<u8>(static_cast<u16>(unk10c->unk114));
    }
    unk110->func_slot20(1);
    ItemSubmissionDialog* next = unk110;
    if (next->line_label != 0)
    {
        func_4C6DF0(next->line_label, next->func_slot54(), 0x15FD7 + index, 0);
    }
    D_001B643C->unk10->unk14->func_00263C70(unk110);
    FieldObject23CEA0* marker = unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 64.0f;
        marker->unkae = 1;
        unka8->development_processing_enabled = 0;
        ItemCreationSelectedDisplayState* state = unka8;
        if (state->resource_window != 0)
        {
            func_002FD940(state->resource_window);
            state->resource_window_release_pending = 1;
        }
        state->pending_secondary_resource_key = 0;
        state->pending_resource_key = 0;
        state->inventor_resource_countdown = 0;
    }
    return 1;
}

/**
 * @brief Restore the marker and reopen the associated window.
 * @return Zero when inactive, otherwise two.
 */
s32 ItemCreationClass186770::func_slotb4()
{
    if (unka8->development_processing_enabled == 0)
    {
        return 0;
    }
    unka8->dialog_line_index = static_cast<u8>(static_cast<u16>(unk10c->unk114));
    FieldObject23CEA0* marker = unk10c;
    if (marker != 0)
    {
        marker->FieldClass151C50::unk30 = 64.0f;
        marker->unkae = 1;
        unka8->development_processing_enabled = 0;
        ItemCreationSelectedDisplayState* state = unka8;
        if (state->resource_window != 0)
        {
            func_002FD940(state->resource_window);
            state->resource_window_release_pending = 1;
        }
        state->pending_secondary_resource_key = 0;
        state->pending_resource_key = 0;
        state->inventor_resource_countdown = 0;
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
    if (object->unka8->development_processing_enabled == 0)
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
        func_00356780(object, static_cast<u16>(object->unk10c->unk114));
    }
}

/**
 * @brief Clear the option display flags and enable the selected group of four.
 * @param object Resource window owning the option displays.
 * @param group Group to enable; values outside zero through two leave all flags clear.
 */
void func_00356780(ItemCreationClass186770* object, u16 group)
{
    s32 index;
    for (index = 0; index < 12; index++)
    {
        ItemCreationOptionResourceDisplay* node = object->unk174[index];
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
        object->unkdc[index]->unk3f = 0;
    }
    else
    {
        resource = (u8)inventor_resource_index(object->unka8->assigned_inventor_option_codes[(u16)index]);
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
        object->unkdc[index]->func_002D5CF0(allocation, record, resource);
    }
}

/**
 * @brief Test whether a resource group's duration has finished.
 * @param state Selection state.
 * @param index Resource group.
 * @return Nonzero when the group's finished flag is set.
 */
static inline u32 group_finished(ItemCreationSelectedDisplayState* state, u16 index)
{
    return state->line_stopped[index] != 0;
}


/**
 * @brief Test whether any resource group is still running.
 * @param state Selection state.
 * @return False when all three groups have finished.
 */
static inline bool groups_pending(ItemCreationSelectedDisplayState* state)
{
    if (state->line_stopped[0] != 0 && state->line_stopped[1] != 0 && state->line_stopped[2] != 0)
    {
        return false;
    }
    return true;
}

/**
 * @brief Reread the window's selection state.
 * @param window Resource window.
 * @return Selection state.
 */
// TODO: volatile is only known to match (keeps this load ahead of the slot index); find the real cause.
static inline ItemCreationSelectedDisplayState* reread_state(ItemCreationClass186770* window)
{
    return *const_cast<ItemCreationSelectedDisplayState* volatile*>(&window->unka8);
}

/** @brief Refresh the resource meters and handle groups whose duration has run out. */
void ItemCreationClass186770::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() == this && this->unka8 != 0)
    {
        for (s32 group = 0; group < 3; group++)
        {
            ItemCreationSelectedDisplayState* state = this->unka8;
            if (state->line_targets[static_cast<s8>(group)] != 0 && state->line_development_enabled[group] != 0 &&
            !group_finished(state, static_cast<u16>(group)))
            {
                s32 index = static_cast<u8>(group);
                FieldClass15B200* meter = this->unk128[index];
                float amount = state->line_time_meter_widths[group];
                if (meter != 0)
                {
                    func_002D5260(meter, amount, 8.0f);
                }
                for (s32 entry = 0; entry < 3; entry++)
                {
                    state = reread_state(this);
                    u8 code = state->line_inventor_states[group][entry];
                    func_003568F0(this, static_cast<u8>(group * 3 + entry), code, 1);
                }
                this->unk164[group]->unk3f = 1;
                LibClass178600* marker = static_cast<LibClass178600*>(this->unk11c[group]->unk30);
                if (marker != 0)
                {
                    marker->unk3f = 1;
                }
                marker = static_cast<LibClass178600*>(this->unk128[group]->unk30);
                if (marker != 0)
                {
                    marker->unk3f = 1;
                }
                bool active = true;
                float value = this->unka8->line_quality_percentages[group];
                if (this->unk11c[index] != 0)
                {
                    float width = 256.0f * (value / 100.0f);
                    if (width <= 0.0f)
                    {
                        width = 0.0f;
                        active = false;
                    }
                    func_002D5260(this->unk11c[index], width, 8.0f);
                }
                if (active == 0)
                {
                    this->unka8->development_processing_enabled = 0;
                    func_0036C080(this->unka8, group, 0);
                    if (this->unk128[index] != 0)
                    {
                        func_002D5260(this->unk128[index], 0.0f, 8.0f);
                    }
                    for (s32 entry = 0; entry < 3; entry++)
                    {
                        func_003568F0(this, static_cast<u8>(group * 3 + entry), 0, 0);
                    }
                    state = this->unka8;
                    state->line_stopped[index] = 1;
                    ItemCreationClass184EF0* target = state->line_targets[index];
                    if (target != 0)
                    {
                        target->func_slot10();
                    }
                    state = this->unka8;
                    if (state->resource_window != 0)
                    {
                        func_002FD940(state->resource_window);
                        state->resource_window_release_pending = 1;
                    }
                    state->pending_secondary_resource_key = 0;
                    state->pending_resource_key = 0;
                    state->inventor_resource_countdown = 0;
                    if (this->unk118 != 0)
                    {
                        func_003500D0(this->unk118, static_cast<u8>(group));
                        this->unk118->func_slot20(1);
                        D_001B643C->unk10->unk14->func_00263C70(this->unk118);
                    }
                    FieldObject23CEA0* grid = this->unk10c;
                    if (grid != 0)
                    {
                        grid->FieldClass151C50::unk30 = 64.0f;
                        grid->unkae = 1;
                        this->unka8->development_processing_enabled = 0;
                        state = this->unka8;
                        if (state->resource_window != 0)
                        {
                            func_002FD940(state->resource_window);
                            state->resource_window_release_pending = 1;
                        }
                        state->pending_secondary_resource_key = 0;
                        state->pending_resource_key = 0;
                        state->inventor_resource_countdown = 0;
                    }
                    func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
                    return;
                }
            }
            else
            {
                s32 index = static_cast<u8>(group);
                if (this->unk128[index] != 0)
                {
                    func_002D5260(this->unk128[index], 0.0f, 8.0f);
                }
                if (this->unk11c[index] != 0)
                {
                    func_002D5260(this->unk11c[index], 0.0f, 8.0f);
                }
                for (s32 entry = 0; entry < 3; entry++)
                {
                    func_003568F0(this, static_cast<u8>(group * 3 + entry), 0, 0);
                }
                LibObject178750* display = this->unk134[group];
                display->unk94 = 0x505050;
                display->unk3c = 1;
                display = this->unk140[group];
                display->unk94 = 0x505050;
                display->unk3c = 1;
                display = this->unk14c[group];
                display->unk94 = 0x505050;
                display->unk3c = 1;
                display = this->unk158[group];
                display->unk94 = 0x505050;
                display->unk3c = 1;
                this->unk164[group]->unk3f = 0;
            }
        }
        if (groups_pending(this->unka8))
        {
            FieldObject23CEA0* grid = this->unk10c;
            u16 index = static_cast<u16>(grid->unk114);
            if (this->unk134[index]->unk94 == 0x505050UL)
            {
                switch (index)
                {
                case 0:
                    if (this->unk134[1]->unk94 == 0x505050UL)
                    {
                        if (this->unk134[2]->unk94 == 0x505050UL)
                        {
                            return;
                        }
                        index = 2;
                    }
                    else
                    {
                        index = 1;
                    }
                    break;
                case 1:
                    if (this->unk134[2]->unk94 == 0x505050UL)
                    {
                        if (this->unk134[0]->unk94 == 0x505050UL)
                        {
                            return;
                        }
                        index = 0;
                    }
                    else
                    {
                        index = 2;
                    }
                    break;
                case 2:
                    if (this->unk134[0]->unk94 == 0x505050UL)
                    {
                        if (this->unk134[1]->unk94 == 0x505050UL)
                        {
                            return;
                        }
                        index = 2;
                    }
                    else
                    {
                        index = 0;
                    }
                    break;
                }
                func_0023C550(grid, static_cast<u8>(index));
            }
            func_00356780(this, index);
        }
    }
}

void func_00356FD0(ItemCreationNineResourceView* object)
{
    s32 index;

    object->unk1bc = object->unka8->line_count;
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
            value->numeric_value = object->unka8->line_fol_costs[index];
            value->unk3c = 1;
        }
        else
        {
            LibClass178600* marker;
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
            marker = object->unk11c[index]->unk30;
            if (marker != 0)
            {
                marker->unk3f = 0;
            }
            marker = object->unk128[index]->unk30;
            if (marker != 0)
            {
                marker->unk3f = 0;
            }
        }
    }
    object->unk10c->func_0023CE80(1, object->unk1bc);
    func_00356780(object, 0);
}

/**
 * @brief Create the resource grid, its meters and labels, and the selection displays.
 * @param associated Associated source passed to the Field setup and the labels.
 * @return Zero without a selected state, otherwise one.
 */
s32 ItemCreationClass186770::func_slotf4(u32 associated)
{
    if (unka8 == 0)
    {
        return 0;
    }
    unk1bc = unka8->line_count;
    FieldClass15AE70::func_slot10(associated, 16.0f, 251.4f, 17);
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
            LibClass178600* child = resource->unk30;
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
        LibClass178600* child = unk11c[row]->unk30;
        if (child)
        {
            child->unk28 = 100.0f;
            child->unk3c = 1;
        }
        func_002D5260(unk11c[row], 0.0f, 8.0f);
    }
    colors.values[0] = 0x1EAA32;
    colors.values[1] = 0x19A028;
    colors.values[2] = 0x46D7E6;
    colors.values[3] = 0x32C3D2;
    for (s32 row = 0; row < 3; row++)
    {
        unk128[row] = new (0) FieldClass15B200(unk10, 0);
        func_002D5290(unk128[row], 0, 0, &colors, 228.0f, 17.5f + (35.0f + rows[row]), 0.0f, 8.0f);
        LibClass178600* child = unk128[row]->unk30;
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
        u8 code = unka8->assigned_inventor_option_codes[(u16)index];
        FieldResourceRecord* record;
        if (code == 0)
        {
            allocation = func_002D3D80(D_001B643C->unk20, 0);
            record = func_002D3CC0(D_001B643C->unk20, 0x20);
            slot = 0;
        }
        else
        {
            slot = (u8)inventor_resource_index(code);
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
        display->func_002D6440(record, 10.0f + 72.0f * (index % 3), y);
        display->unk50.unk34 = 1.0f;
        display->unk50.unk30 = 1.0f;
        display->unk3c = 1;
        display->unk34 = 3;
        func_004C6190(unk10, display);
        unkdc[index] = display;
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
                display->func_002D6440(func_002D3CC0(D_001B643C->unk20, 0x53), 4.0f, y1);
                break;
            case 1:
                display->func_002D6440(func_002D3CC0(D_001B643C->unk20, 0x54), 4.0f, y2);
                break;
            case 2:
                display->func_002D6440(func_002D3CC0(D_001B643C->unk20, 0x55), 187.0f, y1);
                break;
            case 3:
                display->func_002D6440(func_002D3CC0(D_001B643C->unk20, 0x56), 187.0f, y2);
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
    func_00356780(this, 0);
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
        choice_selector->func_0023B280(1);
        yes_label->set_color(ITEM_CREATION_COLOR_BRIGHT);
        no_label->set_color(ITEM_CREATION_COLOR_SELECTED);
        selection_marker->func_0023B7E0(no_label);
        func_slot20(0);
        if (parent->unkb4 != 0)
        {
            parent->unkb4->unkad = 1;
        }
        D_001B643C->unk10->unk14->func_00263C70(parent);
    }
    line_development_requests[0] = 0;
    line_development_requests[1] = 0;
    line_development_requests[2] = 0;
    return 2;
}

s32 StartInventingDialog::func_slotb0()
{
    FieldClass153130* selector = choice_selector;
    if (selector->func_0023B3A0() == 0)
    {
        selection_state->func_0036BF30(0, line_development_requests[0]);
        selection_state->func_0036BF30(1, line_development_requests[1]);
        selection_state->func_0036BF30(2, line_development_requests[2]);
        selection_state->requested_window_group = 2;
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
    if (choice_selector != 0 && !selector_moving(choice_selector) && (u8)choice_selector->func_0023B3B0(1) != 1)
    {
        u16 selected = choice_selector->func_0023B3A0();
        switch (selected)
        {
        case 0:
        {
            yes_label->set_color(ITEM_CREATION_COLOR_SELECTED);
            no_label->set_color(ITEM_CREATION_COLOR_BRIGHT);
            selection_marker->func_0023B7E0(yes_label);
            break;
        }
        case 1:
        {
            yes_label->set_color(ITEM_CREATION_COLOR_BRIGHT);
            no_label->set_color(ITEM_CREATION_COLOR_SELECTED);
            selection_marker->func_0023B7E0(no_label);
            break;
        }
        }
    }
}

void StartInventingDialog::func_slot68()
{
    if (choice_selector != 0 && !selector_moving(choice_selector) && (u8)choice_selector->func_0023B3B0(0) != 1)
    {
        u16 selected = choice_selector->func_0023B3A0();
        switch (selected)
        {
        case 0:
        {
            yes_label->set_color(ITEM_CREATION_COLOR_SELECTED);
            no_label->set_color(ITEM_CREATION_COLOR_BRIGHT);
            selection_marker->func_0023B7E0(yes_label);
            break;
        }
        case 1:
        {
            yes_label->set_color(ITEM_CREATION_COLOR_BRIGHT);
            no_label->set_color(ITEM_CREATION_COLOR_SELECTED);
            selection_marker->func_0023B7E0(no_label);
            break;
        }
        }
    }
}

/**
 * @brief Create the option window's frame, resource widgets, and selection grid.
 * @param associated Full resource source word; unused.
 * @return One when the required window state is present, or zero otherwise.
 */
s32 TransferInventorStrip::func_slotf4(u32 associated)
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
 * @param associated Full resource source word.
 * @return Always one.
 */
extern "C" s32 func_003501B0(InadequateLineDialog* object, u32 associated)
{
    object->FieldClass15AE70::func_slot10(associated, 95.0f, 188.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 455.0f, 160.0f, 88.0f);
    func_004C6190(object->unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x1B6C, 1);
    func_004C6190(object->unk10, heading);
    object->line_label = new (0) LibObject178750;
    object->line_label->func_004C7FE0(210.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FD7, 1);
    func_004C6190(object->unk10, object->line_label);
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
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 DevelopmentCompleteDialog::func_slotf4(u32 associated)
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
    static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14)->development_processing_enabled = 0;
    return 1;
}

/**
 * @brief Create and attach the result prompt display.
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 LineFailureDialog::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 85.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 470.0f, 160.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x1B6C, 1);
    func_004C6190(unk10, heading);
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    line_label = new (0) LibObject178750;
    line_label->func_004C7FE0(210.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FD7 + state->dialog_line_index, 1);
    func_004C6190(unk10, line_label);
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
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 InventionSuccessDialog::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 112.0f, 196.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 416.0f, 140.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* heading = new (0) LibObject178750;
    heading->func_004C7FE0(36.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FC1, 1);
    func_004C6190(unk10, heading);
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    line_label = new (0) LibObject178750;
    line_label->func_004C7FE0(210.0f, 12.0f, 0.0f, 0.0f, (s32)associated, 0x15FD7 + state->dialog_line_index, 1);
    func_004C6190(unk10, line_label);
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

#include "main/resident_0012F0F8.h"
#include "main/resident_001001E0.h"
#include "overlays/1067-00/text_0028E240.h"

/** Partial controls containing the mode-list activation flag. */
struct ItemCreationControlState
{
    u8 unk00[0x9A];
    u8 unk9a;
};

/**
 * @brief Read the stored Fol after validating its checksum.
 * @param record Checked resident record containing the encoded amount.
 * @return Decoded Fol, or zero when the checksum is invalid.
 */
static inline u32 checked_fol(ResidentCheckedRecord* record)
{
    const u8* end = (const u8*)&record->checksum;
    u16 checksum = record->checksum;
    u32 value;
    if (checksum != func_00457470(record->checksum_seed, ((u8*)record + 0x26),
        end - ((const u8*)record + 0x26)))
    {
        value = 0;
    }
    else
    {
        value = record->encoded_fol ^ 0x7CE3C7F7;
    }
    return value;
}

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
    /**
     * @brief Update the Field list count, selected index, and display bounds.
     * @param object List parameter and callback receiver.
     * @param count List entry count.
     * @param index Selected entry index.
     * @param row Visible row index.
     */
    void func_002CE220(FieldStateCE420* object, s32 count, s32 index, u8 row);
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

/**
 * @brief Convert an inventor option code to a team portrait resource index.
 * @param inventor_option_code Inventor option code; zero denotes an empty slot.
 * @return Zero for an empty slot, or the option code minus eleven.
 */
static inline u32 team_inventor_resource_index(u16 inventor_option_code);
/**
 * @brief Set the panel size and mark its rectangle for refresh.
 * @param panel Panel widget.
 * @param width Rectangle width.
 * @param height Rectangle height.
 */
static inline void set_panel_size(LibClass178630* panel, float width, float height);

/**
 * @brief Convert an inventor option code to a team portrait resource index.
 * @param inventor_option_code Inventor option code; zero denotes an empty slot.
 * @return Zero for an empty slot, or the option code minus eleven.
 */
static inline u32 team_inventor_resource_index(u16 inventor_option_code)
{
    if (inventor_option_code == 0)
    {
        return 0;
    }
    return inventor_option_code - 11;
}

/**
 * @brief Find the runtime inventor record after narrowing its index to a byte.
 * @param value One-based inventor record index to narrow.
 * @return Selected inventor record, or null when the narrowed index is outside one through thirty-eight.
 */
static inline ItemCreationInventorRecord* detail_record(s32 value)
{
    return runtime_inventor_record(D_001B64F8, static_cast<u8>(value));
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

#pragma push
#pragma opt_strength_reduction off
/**
 * @brief Build the inventor detail window for the first placed inventor.
 * @param associated Associated source passed to the Field setup and the labels.
 * @return One.
 */
s32 PendingInventorSummary::func_slotf4(u32 associated)
{
    unkb8 = first_placed_inventor(unka8);
    FieldClass15AE70::func_slot10(associated, 16.0f, 384.0f, 17);
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
    display->func_002D6440(resource_record, 8.0f, 9.0f);
    func_004C6190(unk10, display);
    unkb0 = new (0) LibObject178750;
    unkb0->func_004C7FE0(78.0f, 9.0f, 0.0f, 0.0f, (s32)associated, unkb8 + 0x3584, 0);
    func_004C6190(unk10, unkb0);
    unkb4 = new (0) LibObject178750;
    unkb4->func_004C7FE0(78.0f, 48.0f, 0.0f, 0.0f, (s32)associated, unkb8 + 0x35E8, 0);
    set_text_spacing(unkb4, -1.0f);
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
    if (object->skill_mask & (1 << index))
    {
        if (index != 0)
        {
            object->skill_labels[index]->unk3d = 1;
        }
        u8 talent = inventor_talent(record->inventor_id, index);
        LibObject174F20* value_widget = object->talent_displays[index];
        set_talent_value(value_widget, talent);
        object->talent_displays[index]->unk3d = 1;
        object->skill_labels[index]->set_color(0x808080);
        object->talent_displays[index]->set_color(0x808080);
    }
    else
    {
        object->skill_labels[index]->set_color(0x505050);
    }
}

s32 StartInventingDialog::func_slotf4(u32 associated)
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
    yes_label = new (0) LibObject178750;
    no_label = new (0) LibObject178750;
    yes_label->func_004C7FE0(168.0f, 56.0f, 396.0f, 24.0f, (s32)associated, 0x15FCC, 0);
    no_label->func_004C7FE0(168.0f, 86.0f, 396.0f, 24.0f, (s32)associated, 0x15FCD, 0);
    yes_label->set_vertical_alignment(1);
    yes_label->set_mode(0);
    no_label->set_vertical_alignment(1);
    no_label->set_mode(0);
    func_004C6190(unk10, yes_label);
    func_004C6190(unk10, no_label);
    choice_selector = new (0) FieldClass153130;
    choice_selector->func_0023B530(1, 2, 1, 1, 1, 168.0f, 68.0f, 0.0f, 30.0f);
    func_004C6190(unk10, choice_selector);
    selection_marker = new (0) FieldClass153170;
    selection_marker->func_0023B850(no_label, 0x288080);
    func_004C6190(unk10, selection_marker);
    yes_label->set_color(0x808080);
    no_label->set_color(0x288080);
    selection_marker->func_0023B7E0(no_label);
    return 1;
}

StartInventingDialog::~StartInventingDialog()
{
}

void InventorInformationWindow::func_00358850()
{
    if (inventor_option_code == 0)
    {
        portrait_display->unk3d = 0;
        name_text_display->unk3d = 0;
        name_message_display->unk3d = 0;
        for (s32 index = 0; index < 8; index++)
        {
            skill_labels[index]->unk3d = 0;
            talent_displays[index]->unk3d = 0;
        }
        return;
    }
    FieldRecordSelection* selection = selection_state->record_selection;
    u32 resource = (u8)inventor_resource_index(inventor_option_code);
    void* allocation = func_002D3D80(D_001B643C->unk20, resource);
    FieldResourceRecord* source = func_002D3CC0(D_001B643C->unk20, 81);
    portrait_display->func_002D5CF0(allocation, source, resource);
    portrait_display->unk3d = 1;
    if ((u8)resource > 59)
    {
        s8 index = func_0028E240(selection, inventor_option_code - 59);
        ItemCreationStringRecord* strings = static_cast<ItemCreationStringRecord*>(selection->unk04);
        LibObject175140* display = name_text_display;
        display->unkfc = &strings[index].unk20;
        display->unk3c = 1;
        name_text_display->unk3d = 1;
        name_message_display->unk3d = 0;
    }
    else
    {
        name_text_display->unk3d = 0;
        s32 index = option_list_index(inventor_option_code);
        func_4C6DF0(name_message_display, func_slot54(), index + 0x3584, 1);
        name_message_display->unk3d = 1;
    }
    for (s32 index = 0; index < 8; index++)
    {
        skill_labels[index]->unk3d = 1;
        talent_displays[index]->unk3d = 0;
    }
    ItemCreationInventorRecord* record = detail_record(option_list_index(inventor_option_code));
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

s32 InventorInformationWindow::func_slotf4(u32 associated)
{
    if (selection_state == 0)
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
    portrait_display = new (0) ItemCreationOptionResourceDisplay;
    portrait_display->unkcc = allocation;
    portrait_display->unkd0 = 49;
    portrait_display->func_002D6440(record, 22.0f, 18.0f);
    ItemCreationOptionResourceDisplay* resource = portrait_display;
    resource->unk50.unk34 = 1.0f;
    resource->unk50.unk30 = 1.0f;
    resource->unk3c = 1;
    func_004C6190(unk10, portrait_display);
    portrait_display->unk3d = 0;
    name_text_display = new (0) LibObject175140;
    name_text_display->func_00467AD0(96.0f, 42.0f, 0.0f, 0.0f, D_0036F738, 1);
    func_004C6190(unk10, name_text_display);
    name_text_display->unk3d = 0;
    name_message_display = new (0) LibObject178750;
    name_message_display->func_004C7FE0(96.0f, 42.0f, 0.0f, 0.0f, (s32)associated, 0x3584, 1);
    func_004C6190(unk10, name_message_display);
    name_message_display->unk3d = 0;
    for (s32 index = 0; index < 8; index++)
    {
        skill_labels[index] = new (0) LibObject178750;
        talent_displays[index] = new (0) LibObject174F20;
        float y = 88.0f + 36.0f * (index / 3);
        float x = 22.0f + 122.0f * (index % 3);
        skill_labels[index]->func_004C7FE0(x, y, 0.0f, 0.0f, (s32)associated, ITEM_CREATION_SKILL_LABEL_BASE + index, 1);
        talent_displays[index]->func_00464D90(x + 62.0f, y, 28.0f, 24.0f, 99, 0, 0);
        func_004C6190(unk10, skill_labels[index]);
        func_004C6190(unk10, talent_displays[index]);
        skill_labels[index]->unk3d = 0;
        talent_displays[index]->unk3d = 0;
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
    selection_state = 0;
    portrait_display = 0;
    name_text_display = 0;
    name_message_display = 0;
    for (s32 i = 0; i < 9; i++)
    {
        skill_labels[i] = 0;
        talent_displays[i] = 0;
    }
    toggle_state = 0;
    inventor_option_code = 0;
    skill_mask = 0;
}

static inline void set_panel_size(LibClass178630* panel, float width, float height)
{
    panel->unk18.unk08 = width;
    set_height(panel, height);
}

void ItemCreationControlHelp::func_003598E0(u16 mode, u32 unused)
{
    primary_control_label->unk3f = 0;
    primary_action_label->unk3f = 0;
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
        set_panel_size(panel, panel_width, unke0);
        func_4C6DF0(primary_control_label, func_slot54(), 0x32D9, 0);
        func_4C6DF0(primary_action_label, func_slot54(), 0x32DE, 0);
        func_4C6DF0(unkb8, func_slot54(), 0x32DA, 0);
        func_4C6DF0(unkb4, func_slot54(), 0x32DF, 0);
        func_4C6DF0(unkc0, func_slot54(), 0x32DB, 0);
        func_4C6DF0(unkbc, func_slot54(), 0x32E0, 0);
        func_4C6DF0(unkc8, func_slot54(), 0x32DC, 0);
        func_4C6DF0(unkc4, func_slot54(), 0x32E1, 0);
        primary_control_label->unk3f = 1;
        primary_action_label->unk3f = 1;
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
        set_panel_size(panel, panel_width, unke4);
        func_4C6DF0(primary_control_label, func_slot54(), 0x32D9, 0);
        func_4C6DF0(primary_action_label, func_slot54(), 0x15FC5, 0);
        func_4C6DF0(unkb8, func_slot54(), 0x32DB, 0);
        func_4C6DF0(unkb4, func_slot54(), 0x15FA9, 0);
        func_4C6DF0(unkc0, func_slot54(), 0x32DA, 0);
        func_4C6DF0(unkbc, func_slot54(), 0x15FAB, 0);
        primary_control_label->unk3f = 1;
        primary_action_label->unk3f = 1;
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
        LibObject174F20* display;
        u32 value = checked_fol(D_001B6430->unk04);
        display = this->unkd0;
        display->numeric_value = value;
        display->unk3c = 1;
    }
    if (this->unkd8 != 0)
    {
        LibObject174F20* display;
        u32 value = checked_fol(D_001B6430->unk04);
        display = this->unkd8;
        display->numeric_value = value;
        display->unk3c = 1;
    }
}

s32 ItemCreationControlHelp::func_slotf4(u32 associated)
{
    panel_width = 168.0f;
    unke0 = 160.0f;
    unke4 = 176.0f;
    FieldClass15AE70::func_slot14(associated, 0, 9, 1800, 460.0f, 72.0f, 0.0f);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, panel_width, unke0, 88.0f);
    func_004C6190(unk10, panel);
    primary_control_label = new (0) LibObject178750;
    primary_action_label = new (0) LibObject178750;
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
    primary_control_label->func_004C7FE0(8.0f, 6.0f, 0.0f, 0.0f, (s32)associated, 0x32D9, 0);
    primary_action_label->func_004C7FE0(40.0f, 10.0f, 0.0f, 0.0f, (s32)associated, 0x32DE, 0);
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
        u32 value = checked_fol(D_001B6430->unk04);
        unkd0->func_00464D90(32.0f, 126.0f, 126.0f, 24.0f, value, (s32)associated, 0);
        unkd0->set_color(0x288080);
    }
    unkd4->unkcc = data;
    unkd4->unkd0 = 0;
    unkd4->func_002D6440(func_002D3CC0(D_001B643C->unk20, 25), 5.0f, 140.0f);
    {
        u32 value = checked_fol(D_001B6430->unk04);
        unkd8->func_00464D90(32.0f, 140.0f, 126.0f, 24.0f, value, (s32)associated, 0);
        unkd8->set_color(0x288080);
    }
    func_004C6190(unk10, primary_action_label);
    func_004C6190(unk10, primary_control_label);
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
    panel = 0;
    primary_action_label = 0;
    primary_control_label = 0;
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
    panel_width = 0;
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
    if (item_group_index == 7)
    {
        return 0;
    }
    if (preview_mode != 0)
    {
        if (state->resource_window != 0)
        {
            func_002FD940(state->resource_window);
            state->resource_window_release_pending = 1;
        }
        state->pending_secondary_resource_key = 0;
        state->pending_resource_key = 0;
        state->inventor_resource_countdown = 0;
        preview_mode = 0;
        preview_switch_label->unk3f = 1;
        func_4C6DF0(preview_switch_label, state->func_00263CC0(), 0x1B75, 0);
        LibObject178750* display = action_controls_label;
        display->unk18.unk00 = 428.0f;
        display->unk18.unk04 = 330.0f;
        display->unk3c = 1;
        func_4C6DF0(action_controls_label, state->func_00263CC0(), 0x1B76, 0);
        func_00112400(D_001B65F8, 2, 0, 0, 127, 64, 0);
    }
    else
    {
        s32 count = func_0040CF90(D_001B64F8->records, records, (u16)item_type_id);
        s32 selected = unk24;
        if (count != 0 && selected >= 0)
        {
            s32 message = (u16)D_001B64F0[allocation_value(records[selected])].unk10_code + 0x88;
            if (state->resource_window != 0)
            {
                func_002FD940(state->resource_window);
                state->resource_window_release_pending = 1;
            }
            state->pending_resource_key = message;
            state->pending_secondary_resource_key = 0;
            preview_mode = 1;
            preview_switch_label->unk3f = 0;
            func_4C6DF0(preview_switch_label, state->func_00263CC0(), 0x1B75, 0);
            LibObject178750* display = action_controls_label;
            display->unk18.unk00 = 405.0f;
            display->unk18.unk04 = 337.0f;
            display->unk3c = 1;
            func_4C6DF0(action_controls_label, state->func_00263CC0(), 0x1B77, 0);
            func_00112400(D_001B65F8, 1, 0, 0, 127, 64, 0);
        }
    }
    return 0;
}

/**
 * @brief Close the inventory item list and clear its pending resource preview.
 * @param state Current selection state.
 * @param window Inventory item list to close.
 */
static inline void close_inventory_item_list(ItemCreationSelectedDisplayState* state, InventoryItemInstanceList* window)
{
    state->func_00263F50(window);
    if (state->resource_window != 0)
    {
        func_002FD940(state->resource_window);
        state->resource_window_release_pending = 1;
    }
    state->pending_secondary_resource_key = 0;
    state->pending_resource_key = 0;
    state->inventor_resource_countdown = 0;
}

s32 InventoryItemInstanceList::func_slotb4()
{
    ItemCreationSelectedDisplayState* state =
        static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    if (preview_mode != 0)
    {
        if (state->resource_window != 0)
        {
            func_002FD940(state->resource_window);
            state->resource_window_release_pending = 1;
        }
        state->pending_secondary_resource_key = 0;
        state->pending_resource_key = 0;
        state->inventor_resource_countdown = 0;
        preview_mode = 0;
        preview_switch_label->unk3f = 1;
        func_4C6DF0(preview_switch_label, state->func_00263CC0(), 0x1B75, 0);
        LibObject178750* display = action_controls_label;
        display->unk18.unk00 = 428.0f;
        display->unk18.unk04 = 330.0f;
        display->unk3c = 1;
        func_4C6DF0(action_controls_label, state->func_00263CC0(), 0x1B76, 0);
        return 2;
    }
    else
    {
        close_inventory_item_list(state, this);
        FieldClass15AD40* parent = static_cast<FieldClass15AD40*>(func_slot44());
        parent->func_slot10c(1, 1);
        D_001B643C->unk10->unk14->func_00263C70(parent);
        return 2;
    }
}

/**
 * @brief Apply the selected category record and restore its parent display.
 * @return Zero while preview is active, three for an unavailable selection, or one for a valid selection.
 */
s32 InventoryItemInstanceList::func_slotb0()
{
    ItemCreationAllocationRecord* records[99];
    if (preview_mode != 0)
    {
        return 0;
    }
    ItemCreationSelectedDisplayState* active = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    s32 count = func_0040CF90(D_001B64F8->records, records, (u16)item_type_id);
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
    AssignedInventorGrid* parent = selection_state->assigned_inventor_grid;
    u8 group;
    PlanItemGroupWindow* mode = selection_state->plan_item_group_window;
    group = parent->unk1f0;
    if (mode != 0)
    {
        if (mode->unk14c == 0)
        {
            close_inventory_item_list(active, this);
            func_0035E150(mode, identifier, -1, 0);
            func_0035D7C0(mode, 1);
            D_001B643C->unk10->unk14->func_00263C70(mode);
            selection_state->line_item_ids[(u8)group][0] = identifier;
        }
        else if (mode->unk14c == 1)
        {
            close_inventory_item_list(active, this);
            ItemCreationSelectedDisplayState* state = selection_state;
            if (state->plan_item_group_window != 0)
            {
                state->plan_item_group_window->func_slot20(0);
            }
            if (state->inventory_item_type_list != 0)
            {
                state->inventory_item_type_list->func_slot20(0);
            }
            selection_state->line_skill_ids[(u8)group] = 8;
            set_line_plan_mode(selection_state, (u8)group, 3);
            selection_state->line_item_ids[(u8)group][1] = identifier;
            item_creation_rebuild_line_target(selection_state, group);
            parent = selection_state->assigned_inventor_grid;
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
            close_inventory_item_list(active, this);
            ItemCreationSelectedDisplayState* state = selection_state;
            if (state->plan_item_group_window != 0)
            {
                state->plan_item_group_window->func_slot20(0);
            }
            if (state->inventory_item_type_list != 0)
            {
                state->inventory_item_type_list->func_slot20(0);
            }
            set_line_plan_mode(selection_state, (u8)group, 2);
            selection_state->line_item_ids[(u8)group][0] = identifier;
            selection_state->line_item_ids[(u8)group][1] = 0;
            item_creation_rebuild_line_target(selection_state, parent->unk1f0);
            parent = selection_state->assigned_inventor_grid;
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

/** @brief Perform no work for the window hook at slot 0x6C. */
void InventoryItemInstanceList::func_slot6c()
{
}

/** @brief Perform no work for the window hook at slot 0x68. */
void InventoryItemInstanceList::func_slot68()
{
}

/** @brief Update the category rows and selected item preview. */
void InventoryItemInstanceList::func_slot5c()
{
    ItemCreationAllocationRecord* records[99];
    if (D_001B643C->unk10->unk14->func_00261150() == this && preview_mode == 0)
    {
        func_002CD7C0(this);
    }
    else if (preview_mode == 0)
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
    s32 category = item_type_id;
    if (item_group_index != 7)
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
    for (s32 index = 0; index < 6; index++)
    {
        unk138[index]->unk3f = 0;
        unk150[index]->unk3f = 0;
    }
    if (preview_mode != 0)
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
        for (s32 index = 0; index < 6; index++)
        {
            unk138[index]->unk3f = 1;
            unk150[index]->unk3f = 1;
        }
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
    switch (object->selection_state->plan_item_group_window->unk14c)
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
        if (object->selection_state->line_item_ids[(u16)index][0] == func_0040D890(record))
        {
            result = true;
        }
        if (object->selection_state->line_item_ids[(u16)index][1] == func_0040D890(record))
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
    s32 category = item_type_id;
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
            unk150[row]->func_002D5CF0(allocation, resource, 14);
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
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 InventoryItemInstanceList::func_slot104(u32 associated)
{
    ItemCreationAllocationRecord* records[99];
    FieldClass15AE70::func_slot14(associated, 0, 9, 2600, 25.0f, 83.0f, 0.0f);
    FieldStateCE420::unk3c = 1;
    detail_container = new (0) LibObject178660;
    func_004C6510(detail_container, 5, 0, 0, 25.0f, 83.0f, 0.0f);
    func_00465B20(D_001B657C, detail_container);
    unk18c = new (0) LibClass178630;
    func_004C5A80(unk18c, 1, 0.0f, 0.0f, 590.0f, 370.0f, 88.0f);
    func_004C6190(unk10, unk18c);
    func_004C4AB0(unk18c, 1500.0f);
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
        set_text_spacing(unk138[index], -1.0f);
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
        func_004C6190(detail_container, unk168[index]);
    }
    unk198 = new (0) LibObject178750;
    unk198->func_004C7FE0(16.0f, 12.0f, 0.0f, 0.0f, (s32)associated, item_group_index + 0x1B62, 0);
    set_text_spacing(unk198, -1.0f);
    unk198->set_scale(0.8f, 0.8f);
    unk198->set_color(0x805050);
    unk198->unk3f = 0;
    func_004C6190(unk10, unk198);
    unk1a8 = new (0) LibObject172410;
    func_413F70(unk1a8, 24.0f, 34.0f, 561.6f, 31.199999f, 0, 0, 0);
    LibObject172410* category_display = unk1a8;
    category_display->unkfc = item_type_id;
    category_display->unkfe = 0;
    category_display->unk3c = 1;
    unk1a8->set_scale(1.3f, 1.3f);
    unk1a8->unk3f = 0;
    func_004C6190(unk10, unk1a8);
    if (item_group_index == 7)
    {
        LibObject178750* title = new (0) LibObject178750;
        title->func_004C7FE0(24.0f, 34.0f, 0.0f, 0.0f, (s32)associated, item_type_id + 0x124F9, 0);
        title->set_scale(1.3f, 1.3f);
        func_004C6190(unk10, title);
        unk1a0 = new (0) LibObject178750;
        unk1a0->func_004C7FE0(24.0f, 76.0f, 534.0f, 66.0f, (s32)associated, item_type_id + 0x128E1, 0);
    }
    else
    {
        unk1a0 = new (0) LibObject178750;
        unk1a0->func_004C7FE0(24.0f, 76.0f, 534.0f, 66.0f, (s32)associated, item_type_id + 0xD6D8, 0);
    }
    unk1a0->set_mode(0);
    unk1a0->set_vertical_alignment(1);
    set_text_spacing(unk1a0, -1.0f);
    unk1a0->set_scale(0.9f, 0.9f);
    unk1a0->unk3f = 0;
    func_004C6190(detail_container, unk1a0);
    unk1a4 = new (0) LibObject178750;
    unk1a4->func_004C7FE0(16.0f, 150.0f, 0.0f, 0.0f, (s32)associated, 0x15FE0, 0);
    unk1a4->set_scale(0.8f, 0.8f);
    unk1a4->set_color(0x805050);
    set_text_spacing(unk1a4, -1.0f);
    unk1a4->unk3f = 0;
    func_004C6190(unk10, unk1a4);
    preview_switch_label = new (0) LibObject178750;
    preview_switch_label->func_004C7FE0(460.0f, 295.0f, 0.0f, 0.0f, (s32)associated, 0x1B75, 0);
    func_004C6190(unk10, preview_switch_label);
    action_controls_label = new (0) LibObject178750;
    action_controls_label->func_004C7FE0(428.0f, 330.0f, 0.0f, 0.0f, (s32)associated, 0x1B76, 0);
    func_004C6190(detail_container, action_controls_label);
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
    selection_state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    FieldClass15AE60::unk88 = 0;
    FieldClass15AE60::unk88 = func_0040CF90(D_001B64F8->records, records, item_type_id);
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

/** @brief Release the detail container and its base window contents. */
void InventoryItemInstanceList::func_slot0c()
{
    detail_container->func_003EF740();
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
 * @brief Set the item-type list marker visibility and depth.
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

/** @brief Return to the item-group window or restore its parent selection. @return Always two. */
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
                    if (state->plan_item_group_window != 0)
                    {
                        state->plan_item_group_window->func_slot20(0);
                    }
                    if (state->inventory_item_type_list != 0)
                    {
                        state->inventory_item_type_list->func_slot20(0);
                    }
                    state = unk1a0;
                    u8 group = parent->unk1f0;
                    state->line_item_ids[group][0] = state->saved_first_plan_item_id;
                    state->line_item_ids[group][1] = state->saved_second_plan_item_id;
                    state->saved_second_plan_item_id = 0;
                    state->saved_first_plan_item_id = 0;
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
 * @brief Return the item-type record at the selected list index.
 * @param self Item-type list.
 * @return Record stored in the selected list node.
 */
static inline ItemCreationCategoryRecord* selected_item_type_record(InventoryItemTypeList* self)
{
    return static_cast<ItemCreationCategoryRecord*>(func_0036EF70(&self->unk1a8, self->unk24)->unk00);
}
/** @brief Open the selected item type's instance list. @return One on activation, three on rejection, or zero when unavailable. */
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
    ItemCreationCategoryRecord* record = selected_item_type_record(this);
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
    InventoryItemInstanceList* instances = new (0) InventoryItemInstanceList;
    u16 item_type_id = record->catalog_index + 1;
    instances->item_group_index = unk1a4;
    instances->item_type_id = item_type_id;
    instances->func_slot104(unk1a0->func_00263CC0());
    instances->func_slot40(this);
    unk1a0->func_00263FD0(instances);
    unk1a0->func_00263C70(instances);
    ItemCreationClass175030* marker = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
    if (marker != 0)
    {
        marker->ItemCreationClass185050::unk30 = 64.0f;
        marker->unk3c = 1;
    }
    return 1;
}

/** @brief Position the item-type list rows. @param start Base vertical coordinate. */
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

/** @brief Refresh twelve item-type rows beginning at the list index. @param start First list index. */
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
                    identifier = static_cast<u16>(record->catalog_index + 1);
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
                    value->numeric_value = record->unk08;
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
        if (selected->line_skill_ids[(u16)selected->selected_line_index] != (u8)D_001B64F0[category->catalog_index].unk1e_value)
        {
            result = true;
        }
        else
        {
            count = func_0040CF90(D_001B64F8->records, records, category->catalog_index + 1);
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
        if ((u8)D_001B64F0[category->catalog_index].unk0b_mode != 0)
        {
            result = true;
        }
        else
        {
            count = func_0040CF90(D_001B64F8->records, records, category->catalog_index + 1);
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
        if ((u8)D_001B64F0[category->catalog_index].unk1b_flag == 0)
        {
            result = true;
        }
        else
        {
            count = func_0040CF90(D_001B64F8->records, records, category->catalog_index + 1);
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

/** @brief Refresh the item-type list's selection cursor. */
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

/** @brief Resize the item-type list and rebuild its rows. @param object Item-type list. @param mode Compact display mode. */
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

/** @brief Create the item-type list widgets and initialize its selection. @param associated Full resource source word. @return Always one. */
s32 InventoryItemTypeList::func_slot104(u32 associated)
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
        static_cast<LibObject178750*>(unk48[index])->func_004C7FE0(22.0f, y, 0.0f, 0.0f, static_cast<s32>(associated), 50000, 0);
        unk138[index]->func_004C7FE0(326.0f, y - 4.0f, 0.0f, 0.0f, static_cast<s32>(associated), 2020, 1);
        unk168[index]->func_00464D90(334.0f, y, 28.0f, 24.0f, index, static_cast<s32>(associated), 1);
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
 * @brief Initialize the item-type list and retain its selection state.
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
        ItemCreationAllocationRecord* record = allocation_record(object->unk10c);
        u16 decoded = allocation_value(record);
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
            quantity_display->numeric_value = quantity;
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
 * @brief Set the selector opacity and request a refresh when present.
 * @param selector Selection widget to update, or null.
 * @param opacity Opacity value.
 */
static inline void set_selector_opacity(FieldClass153130* selector, float opacity)
{
    if (selector != 0)
    {
        set_display_opacity(selector, opacity);
    }
}

/**
 * @brief Set the grid opacity and request a refresh when present.
 * @param selector Grid to update, or null.
 * @param opacity Opacity value.
 */
static inline void set_selector_opacity(FieldObject23CEA0* selector, float opacity)
{
    if (selector != 0)
    {
        selector->FieldClass151C50::unk30 = opacity;
        selector->LibClass174610::unkae = 1;
    }
}

/** @brief Restore the group selector opacity and request its redraw. */
void PlanItemGroupWindow::func_slot64()
{
    set_selector_opacity(unkac, 128.0f);
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
            if (state->plan_item_group_window != 0)
            {
                state->plan_item_group_window->func_slot20(0);
            }
            if (state->inventory_item_type_list != 0)
            {
                state->inventory_item_type_list->func_slot20(0);
            }
            state = unka8;
            u8 group = parent->unk1f0;
            state->line_item_ids[group][0] = state->saved_first_plan_item_id;
            state->line_item_ids[group][1] = state->saved_second_plan_item_id;
            state->saved_second_plan_item_id = 0;
            state->saved_first_plan_item_id = 0;
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
    set_selector_opacity(selector, 64.0f);
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
 * @param associated Full resource source word.
 * @return Zero without a parent, otherwise one.
 */
s32 InventionPolicyWindow::func_slotf4(u32 associated)
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

/** @brief Initialize the invention choices for their selection state. @param state Owning selection state. */
InventionPolicyWindow::InventionPolicyWindow(ItemCreationSelectedDisplayState* state)
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
    selection_state = 0;
    selection_state = state;
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
        ItemCreationSelectedDisplayState* state = object->selection_state;
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
 * @param associated Full resource source word.
 * @return Zero without a parent, otherwise one.
 */
s32 CreationSkillWindow::func_slotf4(u32 associated)
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
        if (selection_state->workshop_skill_enabled[(u8)(index + 1) - 1] != 0)
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

/**
 * @brief Initialize the creation-skill window for its selection state.
 * @param state Owning selection state.
 */
CreationSkillWindow::CreationSkillWindow(ItemCreationSelectedDisplayState* state)
{
    selection_state = 0;
    selection_state = state;
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

/**
 * @brief Return the creation-skill channels an inventor can be assigned to.
 * @param inventor_id Inventor ID.
 * @return All nine channels for a party inventor, otherwise the NPC's one skill channel.
 */
static inline u16 inventor_channel_mask(u8 inventor_id)
{
    if (is_party_inventor(inventor_id))
    {
        return 0x1FF;
    }
    return (u16)(1 << (inventor_talent_record(inventor_id - 1)->skill - 1));
}
/**
 * @brief Restrict the permitted channels by an assigned inventor.
 * @param mask Channel mask to narrow.
 * @param value Inventor option code, or zero for an empty slot.
 */
static inline void restrict_channels(u32& mask, u8 value)
{
    if (value > 0)
    {
        ItemCreationInventorRecord* record = detail_record(option_list_index(value));
        if (record)
        {
            mask &= inventor_channel_mask(record->inventor_id);
        }
    }
}

/** @brief Refresh the selected groups and clear assignments outside their permitted channels. */
void AssignedInventorGrid::func_slot5c()
{
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    for (s32 index = 0; index < state->line_count; index++)
    {
        u8* channel = &state->line_skill_ids[(u16)index];
        if (*channel > 0)
        {
            u32 mask = 0;
            u32 first = state->assigned_inventor_option_codes[(u16)(index * 3)];
            if (first != 0 || state->assigned_inventor_option_codes[(u16)(index * 3 + 1)] != 0 || state->assigned_inventor_option_codes[(u16)(index * 3 + 2)] != 0)
            {
                for (s32 slot = 0; slot < 8; slot++)
                {
                    if (this->unka8->workshop_skill_enabled[(u8)(slot + 1) - 1])
                    {
                        mask |= 1 << slot;
                    }
                }
                restrict_channels(mask, first);
                restrict_channels(mask, state->assigned_inventor_option_codes[(u16)(index * 3 + 1)]);
                restrict_channels(mask, state->assigned_inventor_option_codes[(u16)(index * 3 + 2)]);
            }
            if (mask == 0 || !(mask & (1 << (*channel - 1))))
            {
                state->line_skill_ids[(u8)index] = 0;
                state->line_plan_modes[(u8)index] = 0;
                state->line_item_ids[(u16)index][0] = 0;
                state->line_item_ids[(u16)index][1] = 0;
                state->line_fol_costs[index] = 0;
                item_creation_rebuild_line_target(state, index);
            }
        }
        u16 selected = *channel;
        u16 status = state->line_plan_modes[(u16)index];
        if (selected)
        {
            this->unk1fc[index] = selected + 0x3457;
            func_4C6DF0(this->unk194[index], this->func_slot54(), this->unk1fc[index], 0);
        }
        else
        {
            this->unk1fc[index] = 0x15FDD;
            func_4C6DF0(this->unk194[index], this->func_slot54(), this->unk1fc[index], 0);
        }
        if (selected == 8)
        {
            this->unk208[index] = 0x15FD6;
            func_4C6DF0(this->unk1a0[index], this->func_slot54(), this->unk208[index], 0);
            this->unk1a0[index]->set_color(0x505050);
        }
        else if (status)
        {
            this->unk208[index] = status + 0x15FD3;
            func_4C6DF0(this->unk1a0[index], this->func_slot54(), this->unk208[index], 0);
            this->unk1a0[index]->set_color(0x808080);
        }
        else
        {
            this->unk208[index] = 0x15FDD;
            func_4C6DF0(this->unk1a0[index], this->func_slot54(), this->unk208[index], 0);
            this->unk1a0[index]->set_color(0x808080);
        }
        LibObject174F20* image = this->unk1ac[index];
        image->numeric_value = state->line_fol_costs[index];
        image->unk3c = 1;
    }
}

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
        if (object->unka8->inventor_swap_stage != 1)
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
            InventorInformationWindow* details = object->unka8->inventor_information_window;
            if (details != 0)
            {
                details->func_slot20(0);
                details->toggle_state = 0;
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
        if (object->unka8->line_count != 0 && object->unkb4->unkad != 0)
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
        inventor_option_code = object->unka8->assigned_inventor_option_codes[(u16)slot_index];
        if (inventor_option_code != 0)
        {
            portrait_index = (u8)inventor_resource_index(inventor_option_code);
            allocation = func_002D3D80(D_001B643C->unk20, portrait_index);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            object->unk13c[slot_index]->func_002D5CF0(allocation, record, portrait_index);
            object->unk13c[slot_index]->unk3f = 1;
            object->unk190++;
            object->unk1f2[slot_index] = option_list_index(inventor_option_code);
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
    if (unka8->requested_window_group != 1)
    {
        return 0;
    }
    if (unka8->inventor_swap_stage == 1)
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
        if ((s32)unka8->line_fol_costs[index] > 0)
        {
            break;
        }
    }
    if (index == 3)
    {
        return 3;
    }
    u32 value = checked_fol(D_001B643C->unk00);
    ItemCreationSelectedDisplayState* state = unka8;
    if (value < state->line_fol_costs[2] + (state->line_fol_costs[0] + state->line_fol_costs[1]))
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
        child->line_development_requests[index] = 0;
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
                    reset->line_development_requests[flag] = 0;
                }
                return 3;
            }
            if (unk218[part] == 1 && unk21b[part] == 1)
            {
                unk214->line_development_requests[part] = 1;
            }
        }
    }
    if (unkb4 != 0)
    {
        unkb4->unkad = 0;
    }
    child = unk214;
    child->func_slot20(1);
    LibObject178750* first = child->yes_label;
    first->unk94 = ITEM_CREATION_COLOR_BRIGHT;
    first->unk3c = 1;
    LibObject178750* second = child->no_label;
    second->unk94 = ITEM_CREATION_COLOR_SELECTED;
    second->unk3c = 1;
    child->selection_marker->func_0023B7E0(child->no_label);
    child->choice_selector->func_0023B280(1);
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
    InventorInformationWindow* details = unka8->inventor_information_window;
    if (details != 0)
    {
        active = !details->toggle_state;
        details->func_slot20(active);
        details->toggle_state = active;
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
    if (state->requested_window_group != 1)
    {
        return 0;
    }
    if (state->inventor_swap_stage == 1 && state->swap_source_grid != this)
    {
        AvailableInventorGrid* other = state->available_inventor_grid;
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
            state->requested_window_group = 0;
            func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
            state = unka8;
            state->swap_destination_grid = 0;
            state->swap_source_grid = 0;
            state->swap_destination_slot_index = -1;
            state->swap_source_slot_index = -1;
            state->inventor_swap_stage = 0;
        }
    }
    return 2;
}

/** @brief Read the creation-skill bits for an assigned inventor. @param inventor_id One-based runtime inventor record ID. @return Skill bits. */
static inline u32 assigned_inventor_skill_mask(s32 inventor_id)
{
    return inventor_skill_mask(runtime_inventor_record(D_001B64F8, static_cast<u8>(inventor_id))->inventor_id);
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
    if (state->requested_window_group != 1)
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
            static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14)->selected_line_index = this->unk1f0;
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
            static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14)->selected_line_index = this->unk1f0;
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
    if (this->unka8->inventor_swap_stage == 1)
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
    if (unkb4 == unkb0 || unka8->inventor_swap_stage == 1)
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
    if (unkb4 == unkb0 || unka8->inventor_swap_stage == 1)
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
    object->unk1f1 = object->unka8->line_count;
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

/** @brief Initialize the assigned-inventor selection window and clear its owned arrays. */
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
        if (object->unka8->inventor_swap_stage != 1)
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
    if (state->requested_window_group != 1)
    {
        return 0;
    }
    if (state->inventor_swap_stage == 1 && state->swap_source_grid != this)
    {
        AssignedInventorGrid* other = state->assigned_inventor_grid;
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
            state->requested_window_group = 0;
            func_0027CB50(D_001B6430->context->unk58, state->unk1f0, 0, 0);
            state = unka8;
            state->swap_destination_grid = 0;
            state->swap_source_grid = 0;
            state->swap_destination_slot_index = -1;
            state->swap_source_slot_index = -1;
            state->inventor_swap_stage = 0;
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
    if (state->requested_window_group != 1)
    {
        return 0;
    }
    index = display->unk114;
    position = &display->unk10;
    item_creation_select_inventor_for_swap(state, object, (s16)index);
    if (object->unka8->inventor_swap_stage == 1)
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
    InventorInformationWindow* display = unka8->inventor_information_window;
    if (display)
    {
        flag = !display->toggle_state;
        display->func_slot20(flag);
        display->toggle_state = flag;
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
    if (state->line_count && index >= 7 && index < 14)
    {
        u16 selected = related_row(index);
        if (state->inventor_swap_stage == 1 && index >= 10)
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
    u8 row_count = unka8->line_count;
    if (row_count && index >= 0 && index < 7)
    {
        u16 selected = upper_related_row(row_count, index);
        if (unka8->inventor_swap_stage == 1 && index >= 3 && index < 7)
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
        inventor_option_code = object->unka8->available_inventor_option_codes[(u16)slot_index];
        if (inventor_option_code != 0)
        {
            portrait_index = (u8)inventor_resource_index(inventor_option_code);
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
 * @param associated Full resource source word.
 * @return Zero without a selected state, one after setup.
 */
s32 AvailableInventorGrid::func_slotf4(u32 associated)
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
    LibClass178600* child = this->unk128->unk30;
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
        u8 value = this->unka8->available_inventor_option_codes[(u16)index];
        if (value == 0)
        {
            allocation = func_002D3D80(D_001B643C->unk20, 0);
            record = func_002D3CC0(D_001B643C->unk20, 0x20);
            resource = 0;
        }
        else
        {
            resource = inventor_resource_index(value);
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
        FieldObject23CEA0* marker = parent->choice_selector;
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

/**
 * @brief Refresh expansion availability, prices, and the checked Fol display.
 * @param object Expansion window to refresh.
 */
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
                        object->unk10d = object->unka8->line_count;
                        if (object->unk10d < 3)
                        {
                            LibObject174F20* valueDisplay = object->unk120;
                            valueDisplay->numeric_value = object->additional_line_costs[object->unk10d];
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
                LibObject174F20* display;
                u32 value = checked_fol(D_001B643C->unk00);
                display = object->unke4;
                display->numeric_value = value;
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
 * @param associated Full resource source word.
 * @return One after setup, or zero without a selected workshop state or workshop id.
 */
s32 WorkshopExpansionWindow::func_slotf4(u32 associated)
{
    if (unka8 == 0)
    {
        return 0;
    }
    if (workshop_id == 0)
    {
        return 0;
    }
    unk10d = unka8->line_count;
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
    u32 value = checked_fol(D_001B643C->unk00);
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

/** @brief Refresh the displayed Fol after validating the stored amount. */
void WorkshopExpansionWindow::func_slot5c()
{
    if (this->unke4 != 0)
    {
        LibObject174F20* display;
        u32 value = checked_fol(D_001B6430->unk04);
        display = this->unke4;
        display->numeric_value = value;
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
        if (index < state->line_count)
        {
            u16 code = state->line_skill_ids[(u16)index];
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
        if (object->unk120->record_selection != 0)
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
                    u8 value = object->unk120->available_inventor_option_codes[(u16)index];
                    if (value != 0)
                    {
                        resource = team_inventor_resource_index(value);
                        void* allocation = func_002D3D80(D_001B643C->unk20, (u8)resource);
                        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 0x51);
                        object->unkcc[slot]->unkd0 = resource;
                        object->unkcc[slot]->func_002D5CF0(allocation, record, 0);
                        object->unkcc[slot]->unk3f = 1;
                        slot++;
                    }
                }
                for (s32 index = 0; index < 9; index++)
                {
                    u8 value = object->unk120->assigned_inventor_option_codes[(u16)index];
                    if (value != 0)
                    {
                        resource = team_inventor_resource_index(value);
                        void* allocation = func_002D3D80(D_001B643C->unk20, (u8)resource);
                        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 0x51);
                        object->unka8[index]->unkd0 = resource;
                        object->unka8[index]->func_002D5CF0(allocation, record, 0);
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
    LibClass178600* child = resource->unk30;
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
s32 DevelopmentTeamsWindow::func_slotf4(u32 associated)
{
    if (unk120 == 0)
    {
        return 0;
    }
    unk125 = unk120->line_count;
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
        display->func_002D6440(record, inset + 66.0f * (index % 3), 4.0f + 75.0f * (index / 3));
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
        display->func_002D6440(record, inset + 44.57f * (index % columns), 236.0f + 78.0f * (index / columns));
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
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 WorkshopFacilitiesWindow::func_slotf4(u32 associated)
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
    if (selection_state)
    {
        for (s32 skill_index = 0; skill_index < 8; skill_index++)
        {
            ItemCreationListNode* node = func_0036F230(&unk2c, skill_index);
            LibObject178750* skill_label = static_cast<LibObject178750*>(node->unk00);
            if (skill_label)
            {
                if (selection_state->workshop_skill_enabled[(u8)(skill_index + 1) - 1])
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
 * @param associated Full resource source word.
 * @return Zero without the selection state, otherwise one.
 */
s32 WorkshopNameWindow::func_slotf4(u32 associated)
{
    if (selection_state == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 220.0f, 17);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 266.0f, 64.0f, 88.0f);
    func_004C6190(unk10, panel);
    u32 workshop_name_key = 0x3520;
    if (selection_state)
    {
        workshop_name_key = item_creation_current_workshop_name_key(selection_state);
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
    if (object->choice_selector)
    {
        s16 selected = object->choice_selector->unk114;
        s32 index = 0;
        ItemCreationListNode* node = object->unk2c.unk00->unk04;
        while (node)
        {
            LibObject178750* widget = static_cast<LibObject178750*>(node->unk00);
            if (index == selected)
            {
                object->selection_marker->func_0023B9B0(func_4C69B0(widget)->unk08, (s16)index);
                object->selection_marker->unk3f = 1;
                widget->unk94 = ITEM_CREATION_COLOR_SELECTED;
                widget->unk3c = 1;
                if (!object->transfer_available && index == 2)
                {
                    widget->unk94 = ITEM_CREATION_COLOR_DIM;
                    widget->unk3c = 1;
                    object->selection_marker->unk3f = 0;
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
                if (!object->transfer_available && index == 2)
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

#include "overlays/lib/text_004CD3A0.h"

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

/**
 * @brief Create and configure the Field window's nested display container.
 * @param object Field window receiver.
 * @param associated Full resource source word.
 * @param first First container configuration value.
 * @param second Second container configuration value.
 * @param third Third container configuration value.
 * @param x Horizontal coordinate.
 * @param y Vertical coordinate.
 * @param z Third coordinate.
 * @return One when the container is present and the source word is nonzero, otherwise zero.
 */
extern "C" s32 func_002CE760(FieldClass15AE70* object, u32 associated, s32 first, s32 second, s32 third, float x, float y, float z);
extern "C"
{
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

/**
 * @brief Set the requested bits in the saved workshop facility mask.
 * @param object Selection state with its optional saved workshop record.
 * @param mask Facility-mask bits to set.
 */
static inline void set_workshop_facility_flags(ItemCreationSelectedDisplayState* object, u16 mask)
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
        if (choice_selector->func_0023CDB0(1) != 1)
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
        if (choice_selector->func_0023CDB0(0) != 1)
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
    FieldObject23CEA0* selector = choice_selector;
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
        state->requested_window_group = 1;
        func_0027CB50(D_001B6430->context->unk58,
                     state->unk1f0, 0, 0);
        break;
    case 1:
        {
            set_selector_opacity(selector, 64.0f);
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
        if (!transfer_available)
        {
            return 3;
        }
        state->requested_window_group = 3;
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
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 ItemCreationMainMenu::func_slotf4(u32 associated)
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
    bool outside_first_group = selection_state->workshop_id >= 6;
    if (selection_state->contracted_inventor_tally != 0 && !outside_first_group)
    {
        transfer_available = 1;
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
    choice_selector = new (0) FieldObject23CEA0;
    choice_selector->func_0023CE80(1, 3);
    choice_selector->func_0023CE60(0.0f, 34.0f);
    choice_selector->unkF2 = 0;
    choice_selector->func_0023CF50(0, 38.0f, 98.0f);
    func_0036F040(&unk74, choice_selector);
    FieldObject23BE00* marker = new (0) FieldObject23BE00;
    selection_marker = marker;
    selection_marker->func_0023BB20(22.0f, 18.0f, 215.99998f, 1.0f, choice_selector, 0x288080);
    func_4C6190(unk10, selection_marker);
    func_0036EFB0(&unk8c, selection_marker);
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
        scroll_started = 0;
        message_hold_count = 0;
        u32 associated = func_slot54();
        func_4C6DF0(message_text, associated, key, 1);
        LibBounds4C69B0* bounds = func_4C69B0(message_text);
        message_scroll_span = (s32)bounds->unk08 + 6;
    }
}

/** @brief Hold, then advance and wrap the horizontal status message. */
void ItemCreationStatusBanner::func_slot5c()
{
    LibObject178750* position = message_text;
    float x = position->unk18.unk00;
    float y = position->unk18.unk04;
    float z = position->unk18.unk08;
    float w = position->unk18.unk0c;
    float start;
    if (this->scroll_started == 0)
    {
        position->unk18.unk00 = this->message_start_x;
        position->unk18.unk04 = y;
        position->unk18.unk08 = z;
        position->unk18.unk0c = w;
        position->unk3c = 1;
        this->message_hold_count++;
        if (!((float)this->message_hold_count <= 120.0f))
        {
            this->message_hold_count = 0;
            this->scroll_started = 1;
        }
        return;
    }
    start = this->message_frame_x;
    x -= 108.0f * D_001B6690;
    if (x < start - (float)this->message_scroll_span)
    {
        x = start + this->message_frame_width + 2.0f;
    }
    position->unk18.unk00 = x;
    position->unk18.unk04 = y;
    position->unk18.unk08 = z;
    position->unk18.unk0c = w;
    position->unk3c = 1;
}

/**
 * @brief Create the heading, scrolling message, footer, and frame widgets.
 * @param associated Full resource source word.
 * @return Zero when an allocation failed, otherwise one.
 */
s32 ItemCreationStatusBanner::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1400, 16.0f, 16.0f, 0.0f);
    message_text = new (0) LibObject178750;
    LibObject178750* footer = new (0) LibObject178750;
    message_frame = new (0) ItemCreationClass1746A0;
    unkd0 = new (0) ItemCreationClass1746A0;
    if (message_text == 0 || message_frame == 0 || unkd0 == 0)
    {
        return 0;
    }
    heading_text = new (0) LibObject178750;
    func_004C7FE0(heading_text, (s32)associated, 0x32C8, 0, 16.0f, 6.0f, 0.0f, 0.0f);
    LibObject178750* heading = heading_text;
    heading->unk88 = -1.0f;
    heading->unk3c = 1;
    func_4C6190(unk10, heading_text);
    LibBounds4C69B0* bounds = func_4C69B0(heading_text);
    heading_width = bounds->unk08;
    message_frame_x = 18.0f + heading_width;
    message_frame_width = 640.0f - (16.0f + shifted_position(message_frame_x, 32.0f));
    message_start_x = 24.0f + heading_width;
    func_44B570(message_frame, message_frame_x, 0.0f, message_frame_width, 56.0f);
    func_4C6190(unk10, message_frame);
    func_0036F270(&unk20, message_frame);
    func_004C7FE0(message_text, (s32)associated, 0x32CB, 0, message_start_x, 6.0f, 0.0f, 0.0f);
    func_4C6190(unk10, message_text);
    func_0036F1A0(&unk2c, message_text);
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
 * @param associated Full resource source word.
 * @return Always one.
 */
s32 ItemCreationBackground::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1200, 16.0f, 16.0f, 0.0f);
    left_display = new (0) ItemCreationOptionResourceDisplay;
    middle_display = new (0) ItemCreationOptionResourceDisplay;
    right_display = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = func_002D3D80(D_001B643C->unk20, 11);
    left_display->unkcc = allocation;
    middle_display->unkcc = allocation;
    right_display->unkcc = allocation;
    left_display->unkd0 = 11;
    middle_display->unkd0 = 11;
    right_display->unkd0 = 11;
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 5);
    left_display->func_002D6440(record, 0.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 6);
    middle_display->func_002D6440(record, 256.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 7);
    right_display->func_002D6440(record, 512.0f, 0.0f);
    ItemCreationOptionResourceDisplay* display = left_display;
    display->unk50.unk44 = 200.0f;
    display->unk50.unk48 = 200.0f;
    display->unk50.unk4c = 200.0f;
    display->unk3c = 1;
    display = middle_display;
    display->unk50.unk44 = 200.0f;
    display->unk50.unk48 = 200.0f;
    display->unk50.unk4c = 200.0f;
    display->unk3c = 1;
    display = right_display;
    display->unk50.unk44 = 200.0f;
    display->unk50.unk48 = 200.0f;
    display->unk50.unk4c = 200.0f;
    display->unk3c = 1;
    display = left_display;
    display->unk28 = 80.0f;
    display->unk3c = 1;
    display = middle_display;
    display->unk28 = 80.0f;
    display->unk3c = 1;
    display = right_display;
    display->unk28 = 80.0f;
    display->unk3c = 1;
    func_4C6190(unk10, left_display);
    func_4C6190(unk10, middle_display);
    func_4C6190(unk10, right_display);
    return 1;
}

/** @brief Destroy the resource window through its Field base. */
ItemCreationBackground::~ItemCreationBackground()
{
}

/** @brief Initialize the twelve float pairs and their selection order. */
void ItemCreationSelection::func_slot10()
{
    workshop_map_positions[0].unk00[0] = 136.0f;
    workshop_map_positions[0].unk00[1] = 164.0f;
    workshop_map_positions[1].unk00[0] = 136.0f;
    workshop_map_positions[1].unk00[1] = 180.0f;
    workshop_map_positions[2].unk00[0] = 60.0f;
    workshop_map_positions[2].unk00[1] = 168.0f;
    workshop_map_positions[3].unk00[0] = 348.0f;
    workshop_map_positions[3].unk00[1] = 44.0f;
    workshop_map_positions[4].unk00[0] = 340.0f;
    workshop_map_positions[4].unk00[1] = 92.0f;
    workshop_map_positions[5].unk00[0] = 212.0f;
    workshop_map_positions[5].unk00[1] = 196.0f;
    workshop_map_positions[6].unk00[0] = 160.0f;
    workshop_map_positions[6].unk00[1] = 96.0f;
    workshop_map_positions[7].unk00[0] = 96.0f;
    workshop_map_positions[7].unk00[1] = 80.0f;
    workshop_map_positions[8].unk00[0] = 108.0f;
    workshop_map_positions[8].unk00[1] = 56.0f;
    workshop_map_positions[9].unk00[0] = 60.0f;
    workshop_map_positions[9].unk00[1] = 16.0f;
    workshop_map_positions[10].unk00[0] = 380.0f;
    workshop_map_positions[10].unk00[1] = 20.0f;
    workshop_map_positions[11].unk00[0] = 16.0f;
    workshop_map_positions[11].unk00[1] = 198.0f;
    workshop_navigation_indices[0] = 1;
    workshop_navigation_indices[1] = 2;
    workshop_navigation_indices[2] = 0;
    workshop_navigation_indices[3] = 5;
    workshop_navigation_indices[4] = 4;
    workshop_navigation_indices[5] = 3;
    workshop_navigation_indices[6] = 10;
    workshop_navigation_indices[7] = 9;
    workshop_navigation_indices[8] = 8;
    workshop_navigation_indices[9] = 7;
    workshop_navigation_indices[10] = 6;
    workshop_navigation_indices[11] = 11;
}

void func_00369510(ItemCreationSelection* object)
{
    s32 enabled;
    FieldRuntimeValues* flags = static_cast<FieldRuntimeValues*>(func_101440(func_101290(func_10D8E0()), 4));
    if (flags != 0)
    {
        enabled = (flags->unk04[118] & ITEM_CREATION_FLAG_4) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[0] = 1;
        }
        enabled = (flags->unk04[118] & ITEM_CREATION_FLAG_5) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[1] = 1;
        }
        enabled = (flags->unk04[118] & ITEM_CREATION_FLAG_6) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[2] = 1;
        }
        enabled = (flags->unk04[118] & ITEM_CREATION_FLAG_7) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[3] = 1;
        }
        enabled = (flags->unk04[119] & ITEM_CREATION_FLAG_0) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[4] = 1;
        }
        enabled = (flags->unk04[119] & ITEM_CREATION_FLAG_1) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[5] = 1;
        }
        enabled = (flags->unk04[119] & ITEM_CREATION_FLAG_2) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[6] = 1;
        }
        enabled = (flags->unk04[119] & ITEM_CREATION_FLAG_3) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[7] = 1;
        }
        enabled = (flags->unk04[119] & ITEM_CREATION_FLAG_4) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[8] = 1;
        }
        enabled = (flags->unk04[119] & ITEM_CREATION_FLAG_5) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[9] = 1;
        }
        enabled = (flags->unk04[119] & ITEM_CREATION_FLAG_6) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[10] = 1;
        }
        enabled = (flags->unk04[119] & ITEM_CREATION_FLAG_7) != 0;
        if (enabled)
        {
            object->workshop_selection_flags[11] = 1;
        }
        if (object->unk79 == 1 || object->unk79 == 2)
        {
            for (s32 index = 5; index < 12; index++)
            {
                object->workshop_selection_flags[index] = 0;
            }
        }
    }
}

u8 func_003696B0(ItemCreationSelection* object, u16 direction)
{
    s32 selected = object->workshop_navigation_indices[object->selected_workshop_id - 1];
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
            if (selected == object->workshop_navigation_indices[index])
            {
                slot = index + 1;
                break;
            }
        }
    } while (!object->workshop_selection_flags[slot - 1]);
    object->selected_workshop_id = slot;
    return object->selected_workshop_id;
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
        workshop_map_positions[index].unk00[0] = 0.0f;
        workshop_map_positions[index].unk00[1] = 0.0f;
        workshop_selection_flags[index] = 0;
        workshop_navigation_indices[index] = 0;
    }
    selected_workshop_id = 0;
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
    if (object->line_skill_ids[index] != 0 && object->line_plan_modes[index] != 0)
    {
        u8 first_inventor_id = inventor_id_from_option_code(object->assigned_inventor_option_codes[index * 3]);
        u8 second_inventor_id = inventor_id_from_option_code(object->assigned_inventor_option_codes[index * 3 + 1]);
        u8 third_inventor_id = inventor_id_from_option_code(object->assigned_inventor_option_codes[index * 3 + 2]);
        ::operator delete(object->line_targets[index]);
        object->line_targets[index] = 0;
        u8 result = 0;
        switch (object->line_plan_modes[index])
        {
        case 1:
            object->line_targets[index] = new (0) FieldClass15BB30;
            result = func_002FAF50(static_cast<FieldClass15BB30*>(object->line_targets[index]), object->workshop_id, line_index,
                                  first_inventor_id, second_inventor_id, third_inventor_id, object->line_skill_ids[index]);
            break;
        case 2:
            object->line_targets[index] = new (0) FieldClass15BB50;
            result = func_002FC310(static_cast<FieldClass15BB50*>(object->line_targets[index]), object->workshop_id, line_index,
                                  first_inventor_id, second_inventor_id, third_inventor_id, object->line_skill_ids[index], object->line_item_ids[index][0]);
            break;
        case 3:
            object->line_targets[index] = new (0) FieldClass15BB70;
            result = func_002FCC50(static_cast<FieldClass15BB70*>(object->line_targets[index]), object->workshop_id, line_index,
                                  first_inventor_id, second_inventor_id, third_inventor_id, object->line_item_ids[index][0], object->line_item_ids[index][1]);
            break;
        }
        if (result == 1)
        {
            object->line_fol_costs[index] = object->line_targets[index]->unk78;
        }
        else
        {
            object->line_fol_costs[index] = 0;
        }
    }
    else
    {
        object->line_fol_costs[index] = 0;
        ::operator delete(object->line_targets[index]);
        object->line_targets[index] = 0;
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
    switch (object->inventor_transfer_stage)
    {
    case 0:
        if (selection_value == -1)
        {
            object->inventor_transfer_stage = 0;
            object->pending_transfer_source_workshop_id = 0;
            object->pending_transfer_source_inventor_option_code = 0;
            object->pending_transfer_destination_workshop_id = 0;
            object->pending_transfer_destination_inventor_option_code = 0;
        }
        else
        {
            object->pending_transfer_source_workshop_id = selection_value;
            object->inventor_transfer_stage = 1;
        }
        break;
    case 1:
        if (selection_value == -1)
        {
            object->pending_transfer_source_inventor_option_code = 0;
            object->inventor_transfer_stage = 0;
        }
        else
        {
            object->pending_transfer_source_inventor_option_code = selection_value;
            object->inventor_transfer_stage = 2;
        }
        break;
    case 2:
        if (selection_value == -1)
        {
            object->pending_transfer_destination_workshop_id = 0;
            object->inventor_transfer_stage = 1;
        }
        else
        {
            object->pending_transfer_destination_workshop_id = selection_value;
            object->inventor_transfer_stage = 3;
        }
        break;
    case 3:
        if (selection_value == -1)
        {
            object->pending_transfer_destination_inventor_option_code = 0;
            object->inventor_transfer_stage = 2;
            break;
        }
        object->pending_transfer_destination_inventor_option_code = selection_value;
        if (object->pending_transfer_source_inventor_option_code != 0)
        {
            u8 placement_code = object->pending_transfer_destination_workshop_id == 0 ? 0 : object->pending_transfer_destination_workshop_id + 1;
            if (object->unk40 != 0)
            {
                object->unk40->unk188[object->pending_transfer_source_inventor_option_code] = placement_code;
            }
        }
        if (object->pending_transfer_destination_inventor_option_code != 0)
        {
            u8 placement_code = object->pending_transfer_source_workshop_id == 0 ? 0 : object->pending_transfer_source_workshop_id + 1;
            if (object->unk40 != 0)
            {
                object->unk40->unk188[object->pending_transfer_destination_inventor_option_code] = placement_code;
            }
        }
        source_workshop_id = object->pending_transfer_source_workshop_id;
        if (object->source_inventor_strip != 0)
        {
            item_creation_build_transfer_inventor_list(object, source_workshop_id, 1);
            func_0034D340(object->source_inventor_strip);
            if (object->source_inventor_strip->unkc8 != 0)
            {
                func_0023CEA0(object->source_inventor_strip->unkc8, 0);
            }
        }
        object->inventor_transfer_stage = 0;
        object->pending_transfer_source_workshop_id = 0;
        object->pending_transfer_source_inventor_option_code = 0;
        object->pending_transfer_destination_workshop_id = 0;
        object->pending_transfer_destination_inventor_option_code = 0;
        transfer_window = object->inventor_transfer_window;
        if (transfer_window != 0)
        {
            const float* position;
            LibClass175030* display;
            float x;
            float y;
            transfer_window->workshop_selection->selected_workshop_id = source_workshop_id;
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
                position = selection->workshop_map_positions[(u8)source_workshop_id - 1].unk00;
            }
            display = transfer_window->workshop_selection_display;
            x = position[0];
            y = position[1];
            display->unk10 = x;
            display->unk14 = y;
            display->unk35 = 1;
            display->unk3c = 1;
            transfer_window = object->inventor_transfer_window;
            switch (transfer_window->selection_state->inventor_transfer_stage)
            {
            case 0:
                transfer_window->unk16c->unk3f = 0;
                transfer_window->workshop_selection_display->unk3f = 1;
                break;
            case 1:
                break;
            case 2:
                transfer_window->workshop_selection_display->unk3f = 1;
                break;
            case 3:
                break;
            }
            func_0034DA30(object->inventor_transfer_window);
            func_0034DB00(object->inventor_transfer_window, source_workshop_id);
        }
        if (object->destination_inventor_strip != 0)
        {
            object->destination_transfer_inventor_option_codes[0] = 0;
            object->destination_transfer_inventor_option_codes[1] = 0;
            object->destination_transfer_inventor_option_codes[2] = 0;
            object->destination_transfer_inventor_option_codes[3] = 0;
            object->destination_transfer_inventor_option_codes[4] = 0;
            object->destination_transfer_inventor_option_codes[5] = 0;
            func_0034D340(object->destination_inventor_strip);
            if (object->destination_inventor_strip->unkc8 != 0)
            {
                func_0023CEA0(object->destination_inventor_strip->unkc8, 0);
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
    switch (object->inventor_swap_stage)
    {
    case 0:
        if (slot_index == -1)
        {
            object->swap_destination_grid = 0;
            object->swap_source_grid = 0;
            object->swap_destination_slot_index = -1;
            object->swap_source_slot_index = -1;
            object->inventor_swap_stage = 0;
        }
        else
        {
            object->swap_source_grid = grid;
            object->swap_destination_grid = 0;
            object->swap_source_slot_index = slot_index;
            object->inventor_swap_stage = 1;
        }
        break;
    case 1:
        if (slot_index == -1)
        {
            object->swap_destination_grid = 0;
            object->swap_source_grid = 0;
            object->swap_destination_slot_index = -1;
            object->swap_source_slot_index = -1;
            object->inventor_swap_stage = 0;
        }
        else
        {
            object->swap_destination_grid = grid;
            object->swap_destination_slot_index = slot_index;
            object->inventor_swap_stage = 2;
        }
        break;
    }
    if (object->swap_source_grid != 0 && object->swap_destination_grid != 0 && object->inventor_swap_stage == 2)
    {
        void* source_grid = object->swap_source_grid;
        void* destination_grid = object->swap_destination_grid;
        u8 source_inventor_code = 0;
        u8 destination_inventor_code = 0;
        AvailableInventorGrid* available_grid;
        AssignedInventorGrid* assigned_grid;

        if (source_grid == object->available_inventor_grid)
        {
            source_inventor_code = object->available_inventor_option_codes[(u16)object->swap_source_slot_index];
        }
        else if (source_grid == object->assigned_inventor_grid)
        {
            source_inventor_code = object->assigned_inventor_option_codes[(u16)object->swap_source_slot_index];
        }
        if (destination_grid == object->available_inventor_grid)
        {
            destination_inventor_code = object->available_inventor_option_codes[(u16)object->swap_destination_slot_index];
        }
        else if (destination_grid == object->assigned_inventor_grid)
        {
            destination_inventor_code = object->assigned_inventor_option_codes[(u16)object->swap_destination_slot_index];
        }
        if (source_grid == object->available_inventor_grid)
        {
            object->available_inventor_option_codes[(u16)object->swap_source_slot_index] = destination_inventor_code;
        }
        else if (source_grid == object->assigned_inventor_grid)
        {
            object->assigned_inventor_option_codes[(u16)object->swap_source_slot_index] = destination_inventor_code;
        }
        if (object->swap_destination_grid == object->available_inventor_grid)
        {
            s32 marker_index;
            object->available_inventor_option_codes[(u16)object->swap_destination_slot_index] = source_inventor_code;
            available_grid = object->available_inventor_grid;
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
        else if (object->swap_destination_grid == object->assigned_inventor_grid)
        {
            object->assigned_inventor_option_codes[(u16)object->swap_destination_slot_index] = source_inventor_code;
            func_00361220(object->assigned_inventor_grid);
        }
        func_00364D20(object->available_inventor_grid);
        func_003614B0(object->assigned_inventor_grid);
        source_grid = object->swap_source_grid;
        available_grid = object->available_inventor_grid;
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
            func_00364090(object->available_inventor_grid, 0);
            if (object->available_inventor_grid == object->swap_destination_grid)
            {
                func_00364090(object->available_inventor_grid, 1);
            }
            else if (object->assigned_inventor_grid == object->swap_destination_grid)
            {
                func_00360E60(object->assigned_inventor_grid, 1);
                item_creation_rebuild_line_target(object, (u8)(object->swap_destination_slot_index / 3));
            }
        }
        else
        {
            assigned_grid = object->assigned_inventor_grid;
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
                func_00360E60(object->assigned_inventor_grid, 0);
                if (object->available_inventor_grid == object->swap_destination_grid)
                {
                    func_00364090(object->available_inventor_grid, 1);
                    item_creation_rebuild_line_target(object, (u8)(object->swap_source_slot_index / 3));
                }
                else if (object->assigned_inventor_grid == object->swap_destination_grid)
                {
                    func_00360E60(object->assigned_inventor_grid, 1);
                    item_creation_rebuild_line_target(object, (u8)(object->swap_source_slot_index / 3));
                    item_creation_rebuild_line_target(object, (u8)(object->swap_destination_slot_index / 3));
                }
            }
        }
        item_creation_show_inventor_information(object, object->swap_destination_grid, object->swap_destination_slot_index);
        object->swap_destination_grid = 0;
        object->swap_source_grid = 0;
        object->swap_destination_slot_index = -1;
        object->swap_source_slot_index = -1;
        object->inventor_swap_stage = 0;
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
    if (grid != 0 && object->available_inventor_grid != 0 && object->assigned_inventor_grid != 0 && object->inventor_information_window != 0)
    {
        u8 inventor_option_code = 0;
        InventorInformationWindow* information_window;
        object->inventor_information_grid = grid;
        if (object->inventor_information_grid == object->available_inventor_grid)
        {
            inventor_option_code = object->available_inventor_option_codes[(u16)slot_index];
        }
        else if (object->inventor_information_grid == object->assigned_inventor_grid)
        {
            inventor_option_code = object->assigned_inventor_option_codes[(u16)slot_index];
        }
        information_window = object->inventor_information_window;
        information_window->inventor_option_code = inventor_option_code;
        if (information_window->selection_state != 0)
        {
            information_window->skill_mask = 0;
            information_window->skill_mask = item_creation_inventor_skill_mask(information_window->selection_state, information_window->inventor_option_code);
        }
        information_window->func_00358850();
        object->inventor_information_grid = 0;
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
        if (object->workshop_facilities_window != 0)
        {
            WorkshopFacilitiesWindow* display = object->workshop_facilities_window;
            if (display->selection_state != 0)
            {
                s32 index;
                for (index = 0; index < 8; index++)
                {
                    ItemCreationListNode* node = func_0036F230(&display->unk2c, index);
                    LibObject178750* label = static_cast<LibObject178750*>(node->unk00);
                    if (label != 0)
                    {
                        u8 skill_id = index + 1;
                        if (display->selection_state->workshop_skill_enabled[skill_id - 1] != 0)
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
        if (object->development_teams_window != 0)
        {
            DevelopmentTeamsWindow* display = object->development_teams_window;
            s32 index;
            display->unk125 = display->unk120->line_count;
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
        if (object->source_inventor_strip != 0)
        {
            func_0034D340(object->source_inventor_strip);
        }
        break;
    case 7:
        if (object->destination_inventor_strip != 0)
        {
            func_0034D340(object->destination_inventor_strip);
        }
        break;
    }
}

/**
 * @brief Encode a workshop ID as an inventor location code.
 * @param workshop_id Workshop ID, or zero for no workshop.
 * @return Zero for no workshop, otherwise the workshop ID plus one.
 */
static inline s32 workshop_location_code(u16 workshop_id)
{
    return workshop_id == 0 ? 0 : workshop_id + 1;
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

    if (object->unk40 != 0 && workshop_location_code(workshop_id) > 1 && workshop_location_code(workshop_id) < 13)
    {
        clear_index = 0;
        do
        {
            switch (transfer_list)
            {
            case 1:
                object->source_transfer_inventor_option_codes[clear_index] = 0;
                break;
            case 2:
                object->destination_transfer_inventor_option_codes[clear_index] = 0;
                break;
            }
            clear_index++;
        } while (clear_index < 6);
        selected_workshop_id = 0;
        switch (transfer_list)
        {
        case 1:
            object->source_transfer_workshop_id = workshop_id;
            selected_workshop_id = object->source_transfer_workshop_id;
            break;
        case 2:
            object->destination_transfer_workshop_id = workshop_id;
            selected_workshop_id = object->destination_transfer_workshop_id;
            break;
        }
        inventor_count = 0;
        inventor_option_code = 32;
        do
        {
            s32 placement_code = object->unk40->unk188[inventor_option_code];
            if (placement_code > 1 && placement_code == workshop_location_code(selected_workshop_id))
            {
                switch (transfer_list)
                {
                case 1:
                    object->source_transfer_inventor_option_codes[inventor_count++] = inventor_option_code;
                    break;
                case 2:
                    object->destination_transfer_inventor_option_codes[inventor_count++] = inventor_option_code;
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
    for (s32 index = 0; index < object->line_count; index++)
    {
        store_workshop_line(D_001B64F8, object->workshop->workshop_id, index,
            inventor_id_from_option_code(object->assigned_inventor_option_codes[index * 3]),
            inventor_id_from_option_code(object->assigned_inventor_option_codes[index * 3 + 1]),
            inventor_id_from_option_code(object->assigned_inventor_option_codes[index * 3 + 2]), object->line_skill_ids[index]);
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
            set_workshop_facility_flags(object, ITEM_CREATION_FACILITY_COOK);
            object->workshop_skill_enabled[0] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_ALCH)
        {
            set_workshop_facility_flags(object, ITEM_CREATION_FACILITY_ALCH);
            object->workshop_skill_enabled[1] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_CRFT)
        {
            set_workshop_facility_flags(object, ITEM_CREATION_FACILITY_CRFT);
            object->workshop_skill_enabled[2] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_CMPD)
        {
            set_workshop_facility_flags(object, ITEM_CREATION_FACILITY_CMPD);
            object->workshop_skill_enabled[3] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_SMTH)
        {
            set_workshop_facility_flags(object, ITEM_CREATION_FACILITY_SMTH);
            object->workshop_skill_enabled[4] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_WRIT)
        {
            set_workshop_facility_flags(object, ITEM_CREATION_FACILITY_WRIT);
            object->workshop_skill_enabled[5] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_ENG)
        {
            set_workshop_facility_flags(object, ITEM_CREATION_FACILITY_ENG);
            object->workshop_skill_enabled[6] = 1;
        }
        if (object->facility_mask & ITEM_CREATION_FACILITY_SYTH)
        {
            set_workshop_facility_flags(object, ITEM_CREATION_FACILITY_SYTH);
            object->workshop_skill_enabled[7] = 1;
        }
        set_workshop_facility_flags(object, ITEM_CREATION_FLAG_8);
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
 * @brief Enable or disable the inventor transfer windows and restore the selected workshop.
 * @param object State owning the transfer window and source/destination inventor strips.
 * @param enabled Full-word control flag; nonzero refreshes the workshop selections and inventor strips.
 */
extern "C" void func_0036B1E0(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    if (object->inventor_transfer_window != 0)
    {
        if (enabled != 0)
        {
            func_0034DA30(object->inventor_transfer_window);
            func_0034DB00(object->inventor_transfer_window, object->workshop_id);
            func_0034D980(object->inventor_transfer_window, object->workshop_id);
            InventorTransferWindow* transfer_window = object->inventor_transfer_window;
            s32 selected_workshop_id = object->workshop_id;
            transfer_window->workshop_selection->selected_workshop_id = selected_workshop_id;
            const float* workshop_position = workshop_map_position(transfer_window->workshop_selection, selected_workshop_id);
            set_transfer_position(transfer_window->workshop_selection_display, workshop_position[0], workshop_position[1]);
            object->func_00263C70(object->inventor_transfer_window);
        }
        object->inventor_transfer_window->func_slot20(enabled);
    }
    if (object->source_inventor_strip != 0)
    {
        object->source_inventor_strip->func_slot20(enabled);
        if (enabled != 0)
        {
            func_0034D340(object->source_inventor_strip);
        }
    }
    if (object->destination_inventor_strip != 0)
    {
        object->destination_inventor_strip->func_slot20(enabled);
        if (enabled != 0)
        {
            func_0034D340(object->destination_inventor_strip);
        }
    }
    if (object->status_banner != 0 && enabled != 0)
    {
        object->status_banner->func_slot60(0x32CD);
    }
}

/**
 * @brief Activate the resource window and reset the related selection displays.
 * @param object State owning the resource, option, and message windows.
 * @param enabled Full-word activation flag; zero disables the resource window.
 */
extern "C" void func_0036B360(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    ItemCreationClass186770* resource = object->development_lines_window;
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
            func_00356FD0(object->development_lines_window);
            func_00356160(object->development_lines_window);
            object->func_00263C70(object->development_lines_window);
            for (s32 index = 0; index < 3; index++)
            {
                u8 value = object->line_development_enabled[index];
                func_0036C080(object, index, value);
                if (value == 0)
                {
                    object->line_stopped[index] = 1;
                }
            }
            item_creation_schedule_inventor_resource(object);
        }
    }
    if (object->development_control_panel != 0)
    {
        object->development_control_panel->func_slot20(enabled);
    }
    if (object->control_help != 0)
    {
        if (enabled != 0)
        {
            object->control_help->func_003598E0(3, enabled);
        }
        object->control_help->func_slot20(enabled);
    }
    if (object->inventor_status_window != 0)
    {
        object->inventor_status_window->func_slot20(0);
    }
    if (object->abort_development_dialog != 0)
    {
        object->abort_development_dialog->func_slot20(0);
    }
    ItemDetailsWindow* actor = object->item_details_window;
    if (actor != 0)
    {
        actor->func_slot20(0);
        actor->unke8->unkab = 0;
    }
    ItemSubmissionDialog* colors = object->item_submission_dialog;
    if (colors != 0)
    {
        colors->func_slot20(0);
        colors->choice_selector->func_0023B280(1);
        if (colors->choice_selector != 0)
        {
            for (s32 index = 0; index < 2; index++)
            {
                LibObject178750* display = static_cast<LibObject178750*>(
                    func_0036F230(&colors->unk2c, index)->unk00);
                if (index == 1)
                {
                    display->set_color(ITEM_CREATION_COLOR_SELECTED);
                    colors->selection_marker->func_0023B7E0(display);
                }
                else
                {
                    display->set_color(ITEM_CREATION_COLOR_BRIGHT);
                }
            }
        }
    }
    if (object->inadequate_line_dialog != 0)
    {
        object->inadequate_line_dialog->func_slot20(0);
    }
    ItemCreationStatusBanner* message = object->status_banner;
    if (message != 0 && enabled != 0)
    {
        if (message->heading_text != 0)
        {
            func_4C6DF0(message->heading_text, message->func_slot54(), 0x1B89, 0);
            float heading_width = func_4C69B0(message->heading_text)->unk08;
            message->heading_width = heading_width;
            message->message_frame_x = 18.0f + heading_width;
            message->message_frame_width = 640.0f - (16.0f + (32.0f + message->message_frame_x));
            message->message_start_x = 24.0f + message->heading_width;
            float width = message->message_frame_width;
            ItemCreationClass1746A0* frame = message->message_frame;
            frame->unk18.unk00 = message->message_frame_x;
            frame->unk18.unk04 = 0.0f;
            frame->unk18.unk08 = width;
            frame->unk18.unk0c = 56.0f;
            frame->unk50 = 0;
            frame->unk3c = 1;
        }
        object->status_banner->func_slot60(0x32D0);
    }
}

/**
 * @brief Enable or disable inventor team selection and reset its subsidiary windows.
 * @param object State owning the assigned/available inventor grids and their detail windows.
 * @param enabled Full-word control flag; nonzero refreshes the inventor grids and team-selection prompt.
 */
extern "C" void func_0036B6E0(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    if (object->control_help != 0)
    {
        if (enabled != 0)
        {
            object->control_help->func_003598E0(2, enabled);
        }
        object->control_help->func_slot20(enabled);
    }
    if (object->assigned_inventor_grid != 0)
    {
        if (enabled != 0)
        {
            func_00363D20(object->assigned_inventor_grid);
            if (object->assigned_inventor_grid->unkb4 != 0)
            {
                func_0023C550(object->assigned_inventor_grid->unkb4, 0);
            }
            func_00361220(object->assigned_inventor_grid);
            func_003614B0(object->assigned_inventor_grid);
        }
        func_003610D0(object->assigned_inventor_grid, enabled);
    }
    if (object->available_inventor_grid != 0)
    {
        func_00364E00(object->available_inventor_grid, enabled);
        if (enabled != 0)
        {
            func_00364090(object->available_inventor_grid, 1);
            if (object->available_inventor_grid->unkb4 != 0)
            {
                func_0023C550(object->available_inventor_grid->unkb4, 0);
            }
            func_00364D20(object->available_inventor_grid);
            AvailableInventorGrid* available_grid = object->available_inventor_grid;
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
            object->func_00263C70(object->available_inventor_grid);
        }
    }
    InventorInformationWindow* inventor_information = object->inventor_information_window;
    if (inventor_information != 0)
    {
        inventor_information->func_slot20(0);
        inventor_information->toggle_state = 0;
    }
    if (object->creation_skill_window != 0)
    {
        object->creation_skill_window->func_slot20(0);
    }
    if (object->invention_policy_window != 0)
    {
        object->invention_policy_window->func_slot20(0);
    }
    if (object->start_inventing_dialog != 0)
    {
        object->start_inventing_dialog->func_slot20(0);
    }
    if (object->plan_item_group_window != 0)
    {
        object->plan_item_group_window->func_slot20(0);
    }
    if (object->inventory_item_type_list != 0)
    {
        object->inventory_item_type_list->func_slot20(0);
    }
    ItemCreationStatusBanner* status_banner = object->status_banner;
    if (status_banner != 0 && enabled != 0)
    {
        if (status_banner->heading_text != 0)
        {
            func_4C6DF0(status_banner->heading_text, status_banner->func_slot54(), 0x32C9, 0);
            float title_width = func_4C69B0(status_banner->heading_text)->unk08;
            status_banner->heading_width = title_width;
            status_banner->message_frame_x = 18.0f + title_width;
            status_banner->message_frame_width = 640.0f - (16.0f + (32.0f + status_banner->message_frame_x));
            status_banner->message_start_x = 24.0f + status_banner->heading_width;
            float message_frame_width = status_banner->message_frame_width;
            ItemCreationClass1746A0* message_frame = status_banner->message_frame;
            message_frame->unk18.unk00 = status_banner->message_frame_x;
            message_frame->unk18.unk04 = 0.0f;
            message_frame->unk18.unk08 = message_frame_width;
            message_frame->unk18.unk0c = 56.0f;
            message_frame->unk50 = 0;
            message_frame->unk3c = 1;
        }
        object->status_banner->func_slot60(0x32D2);
    }
}

/**
 * @brief Enable or disable the main menu and workshop summary windows.
 * @param object State owning the main menu, facilities, workshop name and development-team summary.
 * @param enabled Full-word control flag; nonzero selects the main menu as active receiver when present and restores its status prompt.
 */
extern "C" void func_0036BA10(ItemCreationSelectedDisplayState* object, u32 enabled)
{
    ItemCreationMainMenu* main_menu = object->main_menu;
    if (main_menu != 0)
    {
        if (main_menu->choice_selector != 0)
        {
            func_0023CEA0(main_menu->choice_selector, enabled);
        }
        main_menu->func_slot20(enabled);
        if (enabled != 0)
        {
            object->func_00263C70(object->main_menu);
            object->line_stopped[0] = 0;
            object->line_stopped[1] = 0;
            object->line_stopped[2] = 0;
        }
    }
    if (object->workshop_facilities_window != 0)
    {
        object->workshop_facilities_window->func_slot20(enabled);
    }
    WorkshopExpansionWindow* expansion_window = object->workshop_expansion_window;
    if (expansion_window != 0)
    {
        if (expansion_window->unkdc != 0)
        {
            func_0023CEA0(expansion_window->unkdc, 0);
        }
        expansion_window->func_slot20(0);
    }
    if (object->development_teams_window != 0)
    {
        object->development_teams_window->func_slot20(enabled);
        if (enabled != 0)
        {
            func_00366F10(object->development_teams_window);
        }
    }
    if (object->workshop_name_window != 0)
    {
        object->workshop_name_window->func_slot20(enabled);
    }
    ItemCreationStatusBanner* status_banner = object->status_banner;
    if (status_banner != 0 && enabled != 0)
    {
        if (status_banner->heading_text != 0)
        {
            func_4C6DF0(status_banner->heading_text, status_banner->func_slot54(), 0x32C8, 0);
            float title_width = func_4C69B0(status_banner->heading_text)->unk08;
            status_banner->heading_width = title_width;
            status_banner->message_frame_x = 18.0f + title_width;
            status_banner->message_frame_width = 640.0f - (16.0f + (32.0f + status_banner->message_frame_x));
            status_banner->message_start_x = 24.0f + status_banner->heading_width;
            float message_frame_width = status_banner->message_frame_width;
            ItemCreationClass1746A0* message_frame = status_banner->message_frame;
            message_frame->unk18.unk00 = status_banner->message_frame_x;
            message_frame->unk18.unk04 = 0.0f;
            message_frame->unk18.unk08 = message_frame_width;
            message_frame->unk18.unk0c = 56.0f;
            message_frame->unk50 = 0;
            message_frame->unk3c = 1;
        }
        object->status_banner->func_slot60(0x32CB);
        if (object->entry_mode == 0 && object->main_menu != 0)
        {
            s16 menu_index = object->main_menu->choice_selector != 0 ? object->main_menu->choice_selector->unk114 : -1;
            if (menu_index == 2)
            {
                object->status_banner->func_slot60(0x32CD);
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
    if (object->resource_window != 0)
    {
        func_002FD940(object->resource_window);
        object->resource_window_release_pending = 1;
    }
    object->pending_secondary_resource_key = 0;
    object->pending_resource_key = 0;
    object->inventor_resource_countdown = 0;
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
        object->background->func_slot58()->func_0044B110(0, 9, 1200, 0, 0.0f);
        object->status_banner->func_slot58()->func_0044B110(0, 9, 1400, 0, 0.0f);
        object->control_help->func_slot58()->func_0044B110(0, 9, 1800, 0, 0.0f);
        break;
    case 2:
        func_0036BA10(object, 0);
        func_0036B6E0(object, 0);
        func_0036B1E0(object, 0);
        func_0036B360(object, 1);
        object->background->func_slot58()->func_0044B110(20, 0, 0, 0, 0.0f);
        object->status_banner->func_slot58()->func_0044B110(19, 0, 0, 0, 0.0f);
        object->control_help->func_slot58()->func_0044B110(18, 0, 0, 0, 0.0f);
        object->runtime_data_update_countdown = 360;
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
    object->window_group_snapshot = object->requested_window_group;
}

void ItemCreationSelectedDisplayState::func_0036BF30(s32 index, bool enabled)
{
    ItemCreationAllocationRecord* records[100];
    line_development_enabled[index] = enabled;
    line_stopped[index] = 0;
    if (line_targets[index] == 0)
    {
        line_stopped[index] = 1;
        line_development_enabled[index] = 0;
    }
    if (enabled && line_targets[index] != 0)
    {
        s32 category = 0;
        if (line_plan_modes[index] >= 2)
        {
            switch (line_skill_ids[index])
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
    line_inventor_states[index][0] = 0;
    line_inventor_states[index][1] = 0;
    line_inventor_states[index][2] = 0;
    unk191[index][0] = 1;
    unk191[index][1] = 1;
    unk191[index][2] = 1;
}

/** @brief Return a random integer in a range. @param lower Lower bound. @param upper Upper bound. @return Random value. */
extern "C" s32 func_10CC40(s32 lower, s32 upper);

void func_0036C080(ItemCreationSelectedDisplayState* object, s32 index, u32 value)
{
    object->line_development_enabled[index] = value;
    if (value != 0)
    {
        if (object->line_targets[index] != 0)
        {
            object->line_target_update_intervals[index] = 360.0f * (1.0f + object->line_targets[index]->unk7c / 100.0f);
        }
        else
        {
            object->line_target_update_intervals[index] = 360.0f;
        }
        object->unk170[index] = func_10CC40(1, 5);
        object->line_target_update_countdowns[index] = object->line_target_update_intervals[index];
        object->line_quality_percentages[index] = 100.0f;
        object->line_target_update_results[index] = 0;
        object->line_time_meter_widths[index] = 0.0f;
        if (object->line_targets[index] == 0)
        {
            object->line_stopped[index] = 1;
        }
    }
    else
    {
        object->line_quality_percentages[index] = 0.0f;
    }
    if (value != 0)
    {
        object->development_processing_enabled = 1;
    }
}

/**
 * @brief Choose an eligible assigned inventor and schedule the corresponding display resources.
 * @param object Selection state containing development lines and assigned inventor codes.
 */
void item_creation_schedule_inventor_resource(ItemCreationSelectedDisplayState* object)
{
    if (object->line_stopped[0] == 0 || object->line_stopped[1] == 0 || object->line_stopped[2] == 0)
    {
        s32 slot_index;
        s32 line_index;
        s32 inventor_option_code;
        for (;;)
        {
            slot_index = func_0010CF80() % 9;
            line_index = slot_index / 3;
            if (object->line_targets[line_index] == 0)
            {
                continue;
            }
            if (object->line_stopped[line_index] != 0)
            {
                continue;
            }
            if (func_002FB510(object->line_targets[line_index], slot_index % 3) == 3)
            {
                continue;
            }
            inventor_option_code = object->assigned_inventor_option_codes[slot_index];
            if (inventor_option_code > 0)
            {
                break;
            }
        }
        if (inventor_option_code >= 32 && inventor_option_code < 60)
        {
            s32 resource_key = inventor_option_code + 596;
            if (object->resource_window != 0)
            {
                func_002FD940(object->resource_window);
                object->resource_window_release_pending = 1;
            }
            object->pending_resource_key = resource_key;
            object->pending_secondary_resource_key = 0;
        }
        else
        {
            s32 resource_key = (inventor_option_code - 60) * 9 + 538;
            s32 skill_id = object->line_skill_ids[line_index];
            if (object->resource_window != 0)
            {
                func_002FD940(object->resource_window);
                object->resource_window_release_pending = 1;
            }
            object->pending_resource_key = resource_key;
            if (skill_id != 0)
            {
                object->pending_secondary_resource_key = resource_key + skill_id;
            }
            else
            {
                object->pending_secondary_resource_key = 0;
            }
        }
    }
}

/** Partial native animation (only the attachment fields used here). */
struct ItemCreationRuntimeAnimation
{
    u8 unk00[0xC0];
    void* unkc0;
    u8 unkc4[0x2C];
    u8 unkf0;
};
/** Partial resident animation owner reached through the field context's object 0x38. */
struct ItemCreationAnimationOwner
{
    u8 unk00[0x5A4];
    ItemCreationRuntimeAnimation* unk5a4;
};
/** Partial runtime section 1: the wide-screen flag at 0x18C. */
struct ItemCreationRuntimeSection1
{
    u8 unk00[0x18C];
    u8 unk18c;
};
/** Partial view of D_001B643C's geometry receiver at 0x1C. */
struct ItemCreationRuntime643CGeometry
{
    u8 unk00[0x1C];
    LibClass171EC0* unk1c;
};
extern "C"
{
    /** Attachment for the window-group animation. */
    // TODO: volatile is only known to match (keeps the attach argument a separate temp); find the real cause.
    extern void* volatile D_001B6694;
    extern s16 D_0036F400[][2];
    extern s16 D_0036F402[][2];
    s32 func_002FDA70(FieldClass15BB90* object, s32 first, s32 second);
    void func_002FD2E0(FieldClass15BB90* object, float first, float second, float third, float fourth, float fifth);
    void func_002FB560(FieldStateTargets* object);
    void func_40B7E0(ItemCreationRuntimeData* records);
    ItemCreationRuntimeAnimation* func_0020F230(ItemCreationAnimationOwner* owner, u32 index, s32 first, s32 second,
                                                float duration, float angle, float distance, u32 mode, u32 extra, u32 flags);
    s32 func_0022A160(ItemCreationRuntimeAnimation* animation);
}
/** @brief View a status window as its float-state block. @param object Status window. @return Same object. */
static inline FieldFloatState5C* window_float_state(FieldClass15BB90* object)
{
    return reinterpret_cast<FieldFloatState5C*>(object);
}
/** @brief Find the resident animation owner through the field context. @return Animation owner. */
static inline ItemCreationAnimationOwner* animation_owner()
{
    return reinterpret_cast<ItemCreationAnimationOwner*>(D_001B6430->context->unk38);
}

/** @brief Read a line target's kind. @param target Line target. @return Kind byte. */
static inline u32 target_kind(const FieldStateTargets* target)
{
    return target->unk83;
}
/**
 * @brief Fill a four-component vector.
 * @param vector Vector to fill.
 * @param x First component.
 * @param y Second component.
 * @param z Third component.
 * @param w Fourth component.
 */
static inline void initialize_vector(LibVector4* vector, float x, float y, float z, float w)
{
    vector->components[0] = x;
    vector->components[1] = y;
    vector->components[2] = z;
    vector->components[3] = w;
}

/** @brief Set the status window's five geometry floats. @param window Status window. @param a Angle. @param b Distance. @param c Pitch. @param d Height. @param e Offset. */
static inline void set_window_geometry(FieldClass15BB90* window, float a, float b, float c, float d, float e)
{
    func_002FD1B0(window_float_state(window), a, b, c, d, e);
}
/**
 * @brief Attach an object to the owner's current animation.
 * @param owner Animation owner.
 * @param attachment Object to attach.
 * @param phase Animation phase.
 */
static inline void attach_animation(ItemCreationAnimationOwner* owner, void* attachment, u8 phase)
{
    ItemCreationRuntimeAnimation* animation = owner->unk5a4;
    animation->unkc0 = attachment;
    animation->unkf0 = phase;
}

/** @brief Advance display transitions and active target animation. */
void ItemCreationSelectedDisplayState::func_001DF360()
{
    if (resource_window_release_pending)
    {
        if (resource_window && func_002FD480(resource_window))
        {
            if (resource_window)
            {
                resource_window->func_001DD7B0();
                resource_window = 0;
            }
            resource_window_release_pending = 0;
        }
    }
    if (pending_resource_key > 0 && !resource_window)
    {
        resource_window = new(0) FieldClass15BB90;
        LibVector4 vector;
        initialize_vector(&vector, 400.0f, -400.0f, 500.0f, 1.0f);
        reinterpret_cast<ItemCreationRuntime643CGeometry*>(D_001B643C)->unk1c->func_003EF780(&vector);
        resource_window->unk5b = 1;
        func_002FD220(resource_window, reinterpret_cast<ItemCreationRuntime643CGeometry*>(D_001B643C)->unk1c);
        func_002FD1D0(resource_window);
        ItemCreationRuntimeSection1* section = static_cast<ItemCreationRuntimeSection1*>(func_101440(func_101290(func_10D8E0()), 1));
        if (pending_resource_key > 487)
        {
            if (pending_secondary_resource_key)
            {
                func_002FDA70(resource_window, pending_resource_key, pending_secondary_resource_key);
            }
            else
            {
                func_002FDC00(resource_window, pending_resource_key);
            }
            s32 difference = 0;
            if (pending_secondary_resource_key)
            {
                difference = pending_secondary_resource_key - pending_resource_key;
            }
            if (section->unk18c)
            {
                resource_placement_offset = 0.6f * D_0036F402[pending_resource_key - 538 + difference][0];
                resource_placement_radius = 510.0f;
                resource_motion_offset = 360.0f;
            }
            else
            {
                resource_placement_offset = D_0036F400[pending_resource_key - 538 + difference][0];
                resource_placement_radius = 450.0f;
                resource_motion_offset = 320.0f;
            }
        }
        else
        {
            func_002FDC00(resource_window, pending_resource_key);
            if (section->unk18c)
            {
                set_window_geometry(resource_window, 0.5235988f, 600.0f, 0.34906584f, 120.0f, 35.0f);
            }
            else
            {
                set_window_geometry(resource_window, 0.5235988f, 500.0f, 0.34906584f, 90.0f, 50.0f);
            }
        }
        D_001B6614->func_004D74F0(resource_window, (void*)-1);
        if (section->unk18c)
        {
            inventor_resource_countdown = 750;
        }
        else
        {
            inventor_resource_countdown = 650;
        }
        pending_secondary_resource_key = 0;
        pending_resource_key = 0;
    }
    switch (update_phase)
    {
    case 0:
        if (!window_setup_ready)
        {
            break;
        }
        update_phase = 1;
        break;
    case 1:
        update_phase = 2;
        return;
    case 2:
        if (requested_window_group == 2)
        {
            if (development_processing_enabled)
            {
                for (s32 index = 0; index < 3; index++)
                {
                    if (line_development_enabled[index] && !line_stopped[index])
                    {
                        line_time_meter_widths[index] += 256.0f / line_target_update_intervals[index];
                        if (!(line_time_meter_widths[index] <= 256.0f))
                        {
                            line_time_meter_widths[index] = 0.0f;
                        }
                        if (unk191[index][0] > 0)
                        {
                            if (--unk191[index][0] <= 0)
                            {
                                func_002FB560(line_targets[index]);
                                for (s32 column = 0; column < 3; column++)
                                {
                                    if (assigned_inventor_option_codes[index * 3 + column])
                                    {
                                        line_inventor_states[index][column] = func_002FB510(line_targets[index], column);
                                    }
                                }
                            }
                        }
                        line_target_update_countdowns[index] -= 1.0f;
                        if (line_target_update_countdowns[index] <= 0.0f && line_target_update_results[index] != 2)
                        {
                            line_target_update_countdowns[index] = line_target_update_intervals[index];
                            line_time_meter_widths[index] = 0.0f;
                            line_target_update_results[index] = line_targets[index]->func_slot08();
                            ItemCreationClass184EF0* target = line_targets[index];
                            if (target_kind(target) != 1 && line_target_update_results[index] == 2)
                            {
                                development_processing_enabled = 0;
                                line_stopped[(u8)index] = 1;
                                ItemCreationClass184EF0* selected = line_targets[(u8)index];
                                if (selected)
                                {
                                    selected->func_slot0c();
                                }
                                dialog_line_index = index;
                                if (resource_window)
                                {
                                    func_002FD940(resource_window);
                                    resource_window_release_pending = 1;
                                }
                                pending_secondary_resource_key = 0;
                                pending_resource_key = 0;
                                inventor_resource_countdown = 0;
                                InventionSuccessDialog* popup = new(0) InventionSuccessDialog;
                                popup->func_slotf4(func_00263CC0());
                                FieldClass153E30::func_00263FD0(popup);
                                FieldClass153E30::unk20 = popup;
                                func_00112400(D_001B65F8, 18, 0, 0, 127, 64, 0);
                                break;
                            }
                            else if (target->unk88[2])
                            {
                                development_processing_enabled = 0;
                                line_stopped[(u8)index] = 1;
                                ItemCreationClass184EF0* selected = line_targets[(u8)index];
                                if (selected)
                                {
                                    selected->func_slot10();
                                }
                                func_0036C080(this, index, 0);
                                dialog_line_index = index;
                                if (resource_window)
                                {
                                    func_002FD940(resource_window);
                                    resource_window_release_pending = 1;
                                }
                                pending_secondary_resource_key = 0;
                                pending_resource_key = 0;
                                inventor_resource_countdown = 0;
                                func_003500D0(inadequate_line_dialog, (u8)index);
                                inadequate_line_dialog->func_slot20(1);
                                FieldClass153E30::unk20 = inadequate_line_dialog;
                                func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
                                break;
                            }
                            else
                            {
                                float percent;
                                if (target->unk83 == 3)
                                {
                                    percent = 100.0f;
                                }
                                else
                                {
                                    percent = 100.0f * ((float)target->unk68 / (float)target->unk64);
                                }
                                line_quality_percentages[index] = percent;
                                for (s32 column = 0; column < 3; column++)
                                {
                                    if (assigned_inventor_option_codes[index * 3 + column])
                                    {
                                        line_inventor_states[index][column] = func_002FB510(line_targets[index], column);
                                    }
                                }
                                unk191[index][0] = 90;
                                s32 value = checked_fol(D_001B643C->unk00);
                                if (value < 0)
                                {
                                    value = 0;
                                }
                                ItemCreationControlHelp* display = control_help;
                                if (display)
                                {
                                    if (display->unkd0)
                                    {
                                        LibObject174F20* quantity = display->unkd0;
                                        quantity->numeric_value = value;
                                        quantity->unk3c = 1;
                                    }
                                    if (display->unkd8)
                                    {
                                        LibObject174F20* quantity = display->unkd8;
                                        quantity->numeric_value = value;
                                        quantity->unk3c = 1;
                                    }
                                }
                            }
                        }
                    }
                }
                if (development_processing_enabled)
                {
                    if (--inventor_resource_countdown < 0)
                    {
                        item_creation_schedule_inventor_resource(this);
                    }
                    if (resource_window)
                    {
                        resource_motion_offset -= 0.9f;
                        func_002FD2E0(resource_window, resource_placement_radius, 0.34906584f, 1.5707964f, resource_motion_offset, 0.75f * resource_placement_offset);
                    }
                    s32 previous = runtime_data_update_countdown--;
                    if (previous < 0)
                    {
                        func_40B7E0(D_001B64F8);
                        runtime_data_update_countdown = 360;
                    }
                }
            }
        }
        if (window_group_snapshot != requested_window_group)
        {
            window_group_change_pending = 1;
            func_0020F230(animation_owner(), 0, 0, (s32)0x80000000, 4.0f, 0.0f, 0.0f, 0, 0, 0);
            attach_animation(animation_owner(), D_001B6694, 10);
            update_phase = 3;
        }
        break;
    case 3:
    {
        ItemCreationRuntimeAnimation* animation = animation_owner()->unk5a4;
        if (!animation || !(func_0022A160(animation) & 0xFF))
        {
            if (!resource_window_release_pending || !resource_window || (func_002FD480(resource_window) & 0xFF))
            {
                if (window_group_change_pending)
                {
                    update_phase = 4;
                }
                else
                {
                    update_phase = 2;
                }
            }
        }
        break;
    }
    case 4:
    {
        item_creation_activate_window_group(this, requested_window_group);
        window_group_change_pending = 0;
        func_0020F230(animation_owner(), 0, (s32)0x80000000, 0, 4.0f, 0.0f, 0.0f, 0, 0, 0);
        attach_animation(animation_owner(), D_001B6694, 10);
        update_phase = 3;
        break;
    }
    }
}

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
    if (object->record_selection != 0)
    {
        release_owned(object->record_selection);
    }
    if (object->unk34 != 0)
    {
        func_00465430(D_001B657C, static_cast<s32>(object->unk34));
    }
    func_004D65C0(object);
    object->func_001DD7B0();
    object->update_phase = 5;
}

/**
 * @brief Allocate and configure the windows for the selected display mode.
 * @return Always one.
 */
s32 ItemCreationSelectedDisplayState::func_00263CD0()
{
    background = new (0) ItemCreationBackground;
    status_banner = new (0) ItemCreationStatusBanner;
    background->func_slotf4(unk34);
    FieldClass153E30::func_00263FD0(background);
    background->func_slot40(0);
    status_banner->func_slotf4(unk34);
    FieldClass153E30::func_00263FD0(status_banner);
    unk24 = status_banner;
    status_banner->func_slot40(background);
    if (entry_mode == 0)
    {
        main_menu = new (0) ItemCreationMainMenu(this);
        workshop_name_window = new (0) WorkshopNameWindow(this);
        workshop_facilities_window = new (0) WorkshopFacilitiesWindow;
        workshop_expansion_window = new (0) WorkshopExpansionWindow;
        development_teams_window = new (0) DevelopmentTeamsWindow;
        control_help = new (0) ItemCreationControlHelp;
        available_inventor_grid = new (0) AvailableInventorGrid;
        assigned_inventor_grid = new (0) AssignedInventorGrid;
        inventor_information_window = new (0) InventorInformationWindow;
        creation_skill_window = new (0) CreationSkillWindow(this);
        invention_policy_window = new (0) InventionPolicyWindow(this);
        start_inventing_dialog = new (0) StartInventingDialog(this);
        plan_item_group_window = new (0) PlanItemGroupWindow(this);
        inventory_item_type_list = new (0) InventoryItemTypeList(this);
        development_lines_window = new (0) ItemCreationClass186770;
        item_submission_dialog = new (0) ItemSubmissionDialog;
        item_details_window = new (0) ItemDetailsWindow(this);
        development_control_panel = new (0) DevelopmentControlPanel;
        inventor_status_window = new (0) InventorStatusWindow;
        abort_development_dialog = new (0) AbortDevelopmentDialog;
        inadequate_line_dialog = new (0) InadequateLineDialog(this);
        inventor_transfer_window = new (0) InventorTransferWindow;
        source_inventor_strip = new (0) SourceInventorStrip;
        destination_inventor_strip = new (0) DestinationInventorStrip;
        main_menu->func_slot48(workshop_expansion_window);
        main_menu->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(main_menu);
        workshop_name_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(workshop_name_window);
        workshop_facilities_window->selection_state = this;
        workshop_facilities_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(workshop_facilities_window);
        workshop_expansion_window->unka8 = this;
        workshop_expansion_window->workshop_id = workshop_id;
        workshop_expansion_window->func_slot40(main_menu);
        workshop_expansion_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(workshop_expansion_window);
        development_teams_window->unk120 = this;
        development_teams_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(development_teams_window);
        control_help->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(control_help);
        available_inventor_grid->unka8 = this;
        available_inventor_grid->func_slot40(assigned_inventor_grid);
        available_inventor_grid->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(available_inventor_grid);
        assigned_inventor_grid->unka8 = this;
        assigned_inventor_grid->func_slot40(available_inventor_grid);
        assigned_inventor_grid->unk1e8 = creation_skill_window;
        assigned_inventor_grid->unk1ec = invention_policy_window;
        assigned_inventor_grid->unk214 = start_inventing_dialog;
        assigned_inventor_grid->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(assigned_inventor_grid);
        inventor_information_window->selection_state = this;
        inventor_information_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(inventor_information_window);
        CreationSkillWindow* skill_window;
        InventoryItemTypeList* skill_item_types;
        skill_item_types = inventory_item_type_list;
        skill_window = creation_skill_window;
        skill_window->unke0 = plan_item_group_window;
        skill_window->unke4 = skill_item_types;
        creation_skill_window->func_slot40(assigned_inventor_grid);
        creation_skill_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(creation_skill_window);
        InventionPolicyWindow* policy_window;
        InventoryItemTypeList* policy_item_types;
        policy_item_types = inventory_item_type_list;
        policy_window = invention_policy_window;
        policy_window->unkdc = plan_item_group_window;
        policy_window->unke0 = policy_item_types;
        invention_policy_window->func_slot40(assigned_inventor_grid);
        invention_policy_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(invention_policy_window);
        start_inventing_dialog->func_slot40(assigned_inventor_grid);
        start_inventing_dialog->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(start_inventing_dialog);
        plan_item_group_window->func_slot40(assigned_inventor_grid);
        plan_item_group_window->unk150 = inventory_item_type_list;
        plan_item_group_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(plan_item_group_window);
        inventory_item_type_list->func_slot40(plan_item_group_window);
        inventory_item_type_list->unk21c = plan_item_group_window;
        inventory_item_type_list->func_slot104(unk34);
        FieldClass153E30::func_00263FD0(inventory_item_type_list);
        development_lines_window->unka8 = this;
        development_lines_window->func_slot40(control_help);
        development_lines_window->unk110 = item_submission_dialog;
        development_lines_window->unk114 = item_details_window;
        development_lines_window->unk118 = inadequate_line_dialog;
        development_lines_window->unk1c0 = abort_development_dialog;
        development_lines_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(development_lines_window);
        item_submission_dialog->selection_state = this;
        item_submission_dialog->func_slot40(development_lines_window);
        item_submission_dialog->func_slot48(item_details_window);
        item_submission_dialog->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(item_submission_dialog);
        item_details_window->unka8 = this;
        item_details_window->func_slot40(development_lines_window);
        item_details_window->func_slot48(control_help);
        item_details_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(item_details_window);
        development_control_panel->unka8 = this;
        development_control_panel->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(development_control_panel);
        inventor_status_window->selection_state = this;
        inventor_status_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(inventor_status_window);
        abort_development_dialog->selection_state = this;
        abort_development_dialog->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(abort_development_dialog);
        inadequate_line_dialog->func_slot40(development_lines_window);
        inadequate_line_dialog->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(inadequate_line_dialog);
        inventor_transfer_window->selection_state = this;
        inventor_transfer_window->func_slot40(source_inventor_strip);
        inventor_transfer_window->func_slot48(destination_inventor_strip);
        inventor_transfer_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(inventor_transfer_window);
        source_inventor_strip->unkc4 = this;
        source_inventor_strip->unka8 = 1;
        source_inventor_strip->func_slot40(inventor_transfer_window);
        source_inventor_strip->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(source_inventor_strip);
        destination_inventor_strip->unkc4 = this;
        destination_inventor_strip->unka8 = 2;
        destination_inventor_strip->func_slot40(inventor_transfer_window);
        destination_inventor_strip->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(destination_inventor_strip);
        item_creation_activate_window_group(this, 0);
        unk20 = main_menu;
    }
    else if (entry_mode == 1)
    {
        inventor_talents_window = new (0) InventorTalentsWindow;
        workshop_inventor_strip = new (0) WorkshopInventorStrip;
        pending_inventor_summary = new (0) PendingInventorSummary;
        assign_inventor_dialog = new (0) AssignInventorDialog;
        workshop_full_dialog = new (0) WorkshopFullDialog;
        workshop_selection_window = new (0) WorkshopSelectionWindow;
        inventor_talents_window->selection_state = this;
        inventor_talents_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(inventor_talents_window);
        workshop_inventor_strip->selection_state = this;
        workshop_inventor_strip->func_slotf4(unk34);
        workshop_inventor_strip->func_slot48(inventor_talents_window);
        workshop_inventor_strip->func_slot40(workshop_selection_window);
        FieldClass153E30::func_00263FD0(workshop_inventor_strip);
        pending_inventor_summary->unka8 = this;
        pending_inventor_summary->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(pending_inventor_summary);
        assign_inventor_dialog->unkc4 = pending_inventor_summary->unkb8;
        assign_inventor_dialog->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(assign_inventor_dialog);
        assign_inventor_dialog->func_slot20(0);
        workshop_full_dialog->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(workshop_full_dialog);
        workshop_full_dialog->func_slot20(0);
        workshop_selection_window->func_slot40(assign_inventor_dialog);
        workshop_selection_window->func_slot48(workshop_inventor_strip);
        workshop_selection_window->workshop_full_dialog = workshop_full_dialog;
        workshop_selection_window->func_slotf4(unk34);
        FieldClass153E30::func_00263FD0(workshop_selection_window);
        assign_inventor_dialog->func_slot40(workshop_selection_window);
        workshop_full_dialog->func_slot40(workshop_selection_window);
        status_banner->func_slot60(0x32CF);
        item_creation_activate_window_group(this, 4);
        unk20 = workshop_selection_window;
    }
    window_setup_ready = 1;
    return 1;
}

/** Partial header of a loaded resource. */
struct ItemCreationBufferHeader
{
    u8 unk00[0x40];
    /** Loaded resource size in bytes, including the header. */
    s32 resource_size;
};

// Resident and Lib interfaces linked under this overlay's short names.
extern "C"
{
    void* func_100C90(void);
    void* func_113710(void* heap, s32 size);
    void func_1134C0(void* memory);
    void* func_100C80(void* heap);
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
    s32 size = buffer_header(buffer)->resource_size + 0x80;
    void* previous_heap = func_100C90();
    void* heap = D_001B6430->context->unk70;
    void* memory = func_113710(heap, size);
    if (memory)
    {
        func_1134C0(memory);
        func_100C80(heap);
    }
    unk34 = func_004656B0(D_001B657C, buffer_header(buffer));
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
 * @brief Initialize workshop assignments and tally contracted inventors.
 * @return One on success, zero when required runtime data is missing.
 */
u8 ItemCreationSelectedDisplayState::func_00264110()
{
    unk40 = static_cast<FieldRuntimeValues*>(func_101440(func_101290(func_10D8E0()), 4));
    if (!unk40)
    {
        return 0;
    }
    record_selection = new(0) FieldRecordSelection;
    if (!record_selection)
    {
        return 0;
    }
    if (!(func_0028E3D0(record_selection) & 0xFF))
    {
        return 0;
    }
    if (entry_mode == 0)
    {
        workshop_id = item_creation_current_workshop_id(this);
    }
    if (entry_mode == 0)
    {
        unk12e[0] = workshop_id;
        workshop = saved_workshop_record(unk12e[0]);
        line_count = workshop->line_count;
    }
    unk1f0 = D_001B6430->context->unk58->unk1b4;
    item_creation_restore_workshop_assignments(this);
    item_creation_restore_workshop_skill_flags(this);
    func_00369EB0(this);
    for (s32 index = 1; index < 28; index++)
    {
        ItemCreationInventorRecord* record = saved_inventor_record(index);
        if (record && record->contract_status == 2)
        {
            contracted_inventor_tally++;
        }
    }
    return 1;
}

/** @brief Release the assigned target storage and selection-state base. */
ItemCreationSelectedDisplayState::~ItemCreationSelectedDisplayState()
{
    for (s32 index = 0; index < 3; index++)
    {
        operator delete(line_targets[index]);
        line_targets[index] = 0;
    }
}

/** @brief Initialize the selected-display windows and resource state. */
ItemCreationSelectedDisplayState::ItemCreationSelectedDisplayState()
{
    unk34 = 0;
    window_setup_ready = 0;
    resource_buffer_slots = 0;
    resource_buffer_slots = D_001B643C->unk20;
    unk40 = 0;
    update_phase = 0;
    entry_mode = 0;
    requested_window_group = 0;
    window_group_snapshot = 0;
    entry_mode = D_001B643C->unk10->unk1a;
    record_selection = 0;
    window_group_change_pending = 0;
    workshop_id = 0;
    line_count = 0;
    source_transfer_workshop_id = 0;
    destination_transfer_workshop_id = 0;
    resource_placement_offset = 130.0f;
    for (s32 index = 0; index < 9; index++)
    {
        workshop_skill_enabled[index] = 0;
    }
    for (s32 index = 0; index < 14; index++)
    {
        available_inventor_option_codes[index] = 0;
    }
    for (s32 index = 0; index < 9; index++)
    {
        assigned_inventor_option_codes[index] = 0;
    }
    for (s32 index = 0; index < 6; index++)
    {
        source_transfer_inventor_option_codes[index] = 0;
        destination_transfer_inventor_option_codes[index] = 0;
    }
    for (s32 index = 0; index < 12; index++)
    {
        workshop_facility_masks[index] = 0;
    }
    saved_second_plan_item_id = 0;
    saved_first_plan_item_id = 0;
    for (s32 index = 0; index < 3; index++)
    {
        for (s32 column = 0; column < 2; column++)
        {
            line_item_ids[index][column] = 0;
        }
    }
    background = 0;
    status_banner = 0;
    main_menu = 0;
    workshop_name_window = 0;
    workshop_facilities_window = 0;
    workshop_expansion_window = 0;
    development_teams_window = 0;
    control_help = 0;
    available_inventor_grid = 0;
    assigned_inventor_grid = 0;
    inventor_information_window = 0;
    creation_skill_window = 0;
    invention_policy_window = 0;
    start_inventing_dialog = 0;
    plan_item_group_window = 0;
    inventory_item_type_list = 0;
    development_lines_window = 0;
    item_submission_dialog = 0;
    item_details_window = 0;
    development_control_panel = 0;
    inventor_status_window = 0;
    abort_development_dialog = 0;
    inadequate_line_dialog = 0;
    inventor_transfer_window = 0;
    source_inventor_strip = 0;
    destination_inventor_strip = 0;
    workshop_selection_window = 0;
    workshop_inventor_strip = 0;
    pending_inventor_summary = 0;
    assign_inventor_dialog = 0;
    workshop_full_dialog = 0;
    inventor_talents_window = 0;
    inventor_information_grid = 0;
    swap_source_grid = 0;
    swap_destination_grid = 0;
    swap_source_slot_index = -1;
    swap_destination_slot_index = -1;
    inventor_swap_stage = 0;
    inventor_transfer_stage = 0;
    pending_transfer_source_workshop_id = 0;
    pending_transfer_source_inventor_option_code = 0;
    pending_transfer_destination_workshop_id = 0;
    pending_transfer_destination_inventor_option_code = 0;
    unk12e[0] = 0;
    facility_mask = 0;
    workshop = 0;
    unk138 = 0;
    for (s32 index = 0; index < 3; index++)
    {
        line_target_update_countdowns[index] = 0.0f;
        line_quality_percentages[index] = 0.0f;
        line_target_update_intervals[index] = 0.0f;
        unk170[index] = 0.0f;
        line_time_meter_widths[index] = 0.0f;
        line_inventor_states[index][0] = 0;
        line_inventor_states[index][1] = 0;
        line_inventor_states[index][2] = 0;
        unk191[index][0] = 1;
        unk191[index][1] = 1;
        unk191[index][2] = 1;
    }
    development_processing_enabled = 0;
    contracted_inventor_tally = 0;
    resource_window = 0;
    inventor_resource_countdown = 0;
    dialog_line_index = 0xFF;
    resource_window = 0;
    resource_window_release_pending = 0;
    pending_secondary_resource_key = 0;
    pending_resource_key = 0;
    line_stopped[0] = 0;
    line_stopped[1] = 0;
    line_stopped[2] = 0;
    for (s32 index = 0; index < 3; index++)
    {
        line_targets[index] = 0;
        line_stopped[index] = 0;
        line_skill_ids[index] = 0;
        line_plan_modes[index] = 0;
        line_fol_costs[index] = 0;
        line_target_update_results[index] = 0;
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
    return window_setup_ready;
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
        ::operator delete(unk00);
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

/**
 * @brief Insert a record pointer after a node, or append it when no node is supplied.
 * @param object List containing a valid sentinel.
 * @param after Node to insert after, or null to append.
 * @param record Pointer to the record pointer stored by the new node.
 */
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
        while (tail->unk04)
        {
            tail = tail->unk04;
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
        delete node;
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

/**
 * @brief Append a value to the sentinel-based list.
 * @param object List containing a valid sentinel.
 * @param value Value stored by the new node.
 */
void func_0036EFB0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        node->unk00 = value;
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

/**
 * @brief Append a value to the sentinel-based list.
 * @param object List containing a valid sentinel.
 * @param value Value stored by the new node.
 */
void func_0036F040(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        node->unk00 = value;
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

/**
 * @brief Append a value to the sentinel-based list.
 * @param object List containing a valid sentinel.
 * @param value Value stored by the new node.
 */
void func_0036F0D0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        node->unk00 = value;
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

/**
 * @brief Append a value to the sentinel-based list.
 * @param object List containing a valid sentinel.
 * @param value Value stored by the new node.
 */
void func_0036F1A0(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        node->unk00 = value;
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

/**
 * @brief Find the data node at a list index.
 * @param object List containing a valid sentinel.
 * @param index Data-node index; nonpositive values select the first node.
 * @return Selected node, or null when the list ends first.
 */
ItemCreationListNode* func_0036F230(FieldCountedList* object, s32 index)
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

/**
 * @brief Append a value to the sentinel-based list.
 * @param object List containing a valid sentinel.
 * @param value Value stored by the new node.
 */
void func_0036F270(ItemCreationCountedList* object, void* value)
{
    ItemCreationListNode* node = new (0) ItemCreationListNode;
    if (node != 0)
    {
        ItemCreationListNode* tail;
        node->unk00 = value;
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
