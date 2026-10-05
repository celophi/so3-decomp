#include "include_asm.h"
#include "overlays/lib/text_004095C0.h"
#include "main/resident_0012F0F8.h"
#include "main/resident_001001E0.h"
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/citemcreation/text_003483C0.h"
#include "overlays/citemcreation/text_003684D0.h"
#include "overlays/1067-00/text_0023B1D0.h"
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

/** Field selection widget with primary vtable at 0x153130. */
class FieldClass153130 : public ItemCreationClass175030
{
public:
    /** @brief Initialize the Field selection widget. */
    FieldClass153130();
    /** @brief Destroy the Field selection widget. */
    virtual ~FieldClass153130();
    /**
     * @brief Configure the selection widget and its drawing dimensions.
     * @param first First selection code.
     * @param second Second selection code.
     * @param third Third selection code.
     * @param value Selection value.
     * @param flag Selection flag.
     * @param x Horizontal position.
     * @param y Vertical position.
     * @param z Third drawing coordinate.
     * @param extent Drawing extent.
     * @return Configuration status.
     */
    s32 func_0023B530(u8 first, u8 second, u8 third, u16 value, u8 flag,
                     float x, float y, float z, float extent);
    u8 unk7c;
    u8 unk7d;
    float unk80;
    float unk84;
    float unk88;
    float unk8c;
    u16 unk90;
    u8 unk92;
    u8 unk93;
    u16 unk94;
};

/** Field text marker with primary vtable at 0x153170. */
class FieldClass153170 : public ItemCreationClass172870
{
public:
    /** @brief Initialize the Field target marker. */
    FieldClass153170();
    /** @brief Destroy the Field target marker. */
    virtual ~FieldClass153170();
    /**
     * @brief Configure the marker for a text display.
     * @param target Text display used for the marker bounds.
     * @param color Packed marker color.
     */
    void func_0023B850(LibObject178750* target, u32 color);
    /** @brief Update the marker bounds. @param target Text display to follow. */
    void func_0023B7E0(LibObject178750* target);
    void* unk58;
    u8 unk5c;
};

enum
{
    ITEM_CREATION_COLOR_DIM = 0x505050,
    ITEM_CREATION_COLOR_ASSIGNED = 0x1E8CFF,
    ITEM_CREATION_COLOR_BRIGHT = 0x808080,
    ITEM_CREATION_COLOR_SELECTED = 0x288080
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

/** Twelve-byte category entry containing its list head and catalog index. */
struct ItemCreationCategoryRecord
{
    s16 unk00;
    u16 unk02;
    u8 unk04[8];
};

/** Thirty-two-byte catalog entry containing the three mode-selection fields. */
struct ItemCreationCategoryDefinition
{
    u8 unk00[0xB];
    u8 unk0b_low : 4;
    u8 unk0b_mode : 3;
    u8 unk0b_high : 1;
    u8 unk0c[0xF];
    u8 unk1b_low : 6;
    u8 unk1b_flag : 1;
    u8 unk1b_high : 1;
    u8 unk1c[2];
    u8 unk1e_low : 1;
    u8 unk1e_value : 3;
    u8 unk1e_high : 4;
    u8 unk1f;
};

/** Partial row display containing its color, record code, and update markers. */
struct ItemCreationRowDisplay
{
    u8 unk00[0x3C];
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
    u8 unk00[0x3C];
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

/** Partial resident directory containing the item-resource buffers. */
typedef struct ItemCreationResourceDirectory
{
    struct ItemCreationCheckedRecord* unk00;
    u8 unk04[0x1C];
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

/** Partial resident directory containing the current checked record. */
typedef struct ItemCreationRecordDirectory6430
{
    u8 unk00[4];
    ItemCreationCheckedRecord* unk04;
} ItemCreationRecordDirectory6430;

// These external interfaces are scoped here because their owning code is in other overlays.
extern "C"
{
    extern ItemCreationAllocationRecord* D_001B64F8;
    extern ItemCreationCategoryDefinition* D_001B64F0;
    extern ItemCreationResourceDirectory* D_001B643C;
    extern const char D_0036F738[];
    extern ItemCreationRecordDirectory6430* D_001B6430;
    u16 func_457470(u16 seed, const u8* buffer, s32 length);
    u32 func_23B3B0(FieldState23B3A0* item, u16 flag);
    u16 func_23B3A0(FieldState23B3A0* item);
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

static inline bool valid_record_index(s16 index);
static inline ItemCreationAllocationRecord* allocation_record(s32 value);
static inline bool allocation_invalid(ItemCreationAllocationRecord* record);
static inline u16 allocation_value(ItemCreationAllocationRecord* record);
static inline u32 item_resource_index(u8 value);
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
static inline bool valid_record_index(s16 index)
{
    return index > 0 && index <= 3000;
}

/**
 * @brief Find an allocation record using the signed halfword item index.
 * @param value Item index to narrow to a signed halfword.
 * @return Allocation record, or null when the index is outside the table.
 */
static inline ItemCreationAllocationRecord* allocation_record(s32 value)
{
    ItemCreationAllocationRecord* records = D_001B64F8;
    s16 index = value;
    if (valid_record_index(index))
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
static inline bool allocation_invalid(ItemCreationAllocationRecord* record)
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
static inline u16 allocation_value(ItemCreationAllocationRecord* record)
{
    if (allocation_invalid(record))
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
static inline u32 item_resource_index(u8 value)
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00358850);

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
    void* allocation = func_002D3D80(D_001B643C->unk20, 49);
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 81);
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
        unkb8[index]->func_004C7FE0(x, y, 0.0f, 0.0f, (s32)associated, 0x3458 + index, 1);
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
        ItemCreationCheckedRecord* record = D_001B6430->unk04;
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
        ItemCreationCheckedRecord* record = D_001B6430->unk04;
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
    void* data = func_002D3D80(D_001B643C->unk20, 0);
    unkcc->unkcc = data;
    unkcc->unkd0 = 0;
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unkcc)), func_002D3CC0(D_001B643C->unk20, 25), 5.0f, 126.0f);
    {
        ItemCreationCheckedRecord* record = D_001B6430->unk04;
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
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(unkd4)), func_002D3CC0(D_001B643C->unk20, 25), 5.0f, 140.0f);
    {
        ItemCreationCheckedRecord* record = D_001B6430->unk04;
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

void func_0035A6A0(ItemCreationPairOwner* object, u32 value, u32 alternate)
{
    s32 index;
    ItemCreationNested* nested;

    for (index = 0; index < 6; index++)
    {
        object->unk138[index]->unk3f = value;
        object->unk150[index]->unk3f = value;
    }
    nested = object->unk18c;
    if (nested != 0)
    {
        nested->unk3f = 1;
    }
    nested = object->unkac;
    if (nested != 0)
    {
        nested->unk3f = alternate;
        if (alternate != 0)
        {
            nested = object->unkac;
            nested->unk70 = 128.0f;
            nested->unk3c = 1;
        }
        else
        {
            nested = object->unkac;
            nested->unk70 = 64.0f;
            nested->unk3c = 1;
        }
    }
    nested = object->unka8;
    if (nested != 0)
    {
        nested->unk3f = alternate;
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035A770);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035AA10);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035AB80);

void func_0035AF70(void* object)
{
}

void func_0035AF80(void* object)
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035AF90);

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

void func_0035B480(u8* object, float start)
{
    s32 index;
    float value = start + 16.0f;
    index = 0;
    do
    {
        u8* first;
        u8* second;
        first = *(u8**)(object + 0x138);
        *(float*)(first + 0x1C) = value;
        first[0x3C] = 1;
        second = *(u8**)(object + 0x150);
        *(float*)(second + 0x1C) = value;
        second[0x3C] = 1;
        object += 4;
        value += 28.0f;
        index++;
    } while (index < 6);
}

void func_0035B4E0(ItemCreationIdentifierOwner* object, s32 start)
{
    ItemCreationAllocationRecord* records[99];
    s32 category = object->unk1bc;
    func_0013A678(records, 0, sizeof(records));
    object->unk130 = func_0040CF90(D_001B64F8, records, (u16)category);
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
            if (func_0035B310(object, record))
            {
                ItemCreationRowDisplay* display = object->unk138[row];
                display->unk94 = ITEM_CREATION_COLOR_DIM;
                display->unk3c = 1;
            }
            else if (record->unk0d_flag)
            {
                ItemCreationRowDisplay* display = object->unk138[row];
                display->unk94 = 0x508050;
                display->unk3c = 1;
            }
            else
            {
                ItemCreationRowDisplay* display = object->unk138[row];
                display->unk94 = ITEM_CREATION_COLOR_BRIGHT;
                display->unk3c = 1;
            }
            ItemCreationRowDisplay* display = object->unk138[row];
            u8 value = records[start + row]->unk0c & 0x7F;
            display->unkfc = category;
            display->unkfe = value;
            display->unk3c = 1;
            void* allocation = func_002D3D80(D_001B643C->unk20, 14);
            FieldResourceRecord* resource = func_002D3CC0(D_001B643C->unk20, count + 60);
            func_002D5CF0((FieldResourceDisplay2D5CF0*)object->unk150[row], allocation, resource, 14);
            object->unk138[row]->unk3d = 1;
            object->unk150[row]->unk3d = 1;
        }
        else
        {
            object->unk138[row]->unk3d = 0;
            object->unk150[row]->unk3d = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035B6E0);

void func_0035C3F0(void* object, u8 value)
{
    *(u8*)((u8*)object + 0x12C) = value;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C400);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C440);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C520);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C6A0);

void func_0035C890(u8* object, float start)
{
    s32 index;
    float value = start + 16.0f;
    index = 0;
    do
    {
        u8* first;
        u8* second;
        u8* third;
        first = *(u8**)(object + 0xF0);
        *(float*)(first + 0x18) = 24.0f;
        *(float*)(first + 0x1C) = value;
        first[0x3C] = 1;
        second = *(u8**)(object + 0x138);
        *(float*)(second + 0x18) = 326.0f;
        *(float*)(second + 0x1C) = value;
        second[0x3C] = 1;
        third = *(u8**)(object + 0x168);
        *(float*)(third + 0x18) = 334.0f;
        *(float*)(third + 0x1C) = value;
        third[0x3C] = 1;
        object += 4;
        value += 28.0f;
        index++;
    } while (index < 12);
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C910);

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
            count = func_0040CF90(D_001B64F8, records, category->unk02 + 1);
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
            count = func_0040CF90(D_001B64F8, records, category->unk02 + 1);
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
            count = func_0040CF90(D_001B64F8, records, category->unk02 + 1);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035CD00);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D000);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D0C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D1B0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D6D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035D7C0);

void func_0035E150(ItemCreationCheckedAllocationView* object, s16 value, s32 quantity, s8 index)
{
    object->unk10c = value;
    if (object->unk10c != 0)
    {
        ItemCreationAllocationRecord* record = allocation_record(object->unk10c);
        u16 decoded = allocation_value(record);
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

void func_0035E2D0(u8* object)
{
    u8* nested = *(u8**)(object + 0xAC);
    if (nested != 0)
    {
        *(float*)(nested + 0x70) = 128.0f;
        nested[0x3C] = 1;
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E300);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E430);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E510);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E640);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E770);

ItemCreationClass186DB0::~ItemCreationClass186DB0()
{
}

ItemCreationClass186DB0::ItemCreationClass186DB0(void* object)
{
    unka8 = 0;
    unka8 = object;
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035F1C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035F2D0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035F8D0);

ItemCreationClass186EB0::~ItemCreationClass186EB0()
{
}

ItemCreationClass186EB0::ItemCreationClass186EB0(void* object)
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
    unkd8 = object;
    unkdc = 0;
    unke0 = 0;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035FCA0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00360020);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003600E0);

void func_00360440(u8* object)
{
    FieldState23B3A0* item = *(FieldState23B3A0**)(object + 0xD4);
    if (item != 0 && (u8)func_23B3B0(item, 1) != 1)
    {
        u16 value = (u16)func_23B3A0(*(FieldState23B3A0**)(object + 0xD4));
        func_0035FCA0(object, value);
    }
}

void func_003604A0(u8* object)
{
    FieldState23B3A0* item = *(FieldState23B3A0**)(object + 0xD4);
    if (item != 0 && (u8)func_23B3B0(item, 0) != 1)
    {
        u16 value = (u16)func_23B3A0(*(FieldState23B3A0**)(object + 0xD4));
        func_0035FCA0(object, value);
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00360500);

ItemCreationClass186FB0::~ItemCreationClass186FB0()
{
}

ItemCreationClass186FB0::ItemCreationClass186FB0(void* object)
{
    unka8 = 0;
    unka8 = object;
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
    unke8 = 0;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003608C0);

void func_00360E60(ItemCreationNineSlotView* object, u16 mode)
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00360FD0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003610D0);

void func_00361220(ItemCreationNineSlotView* object)
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

void func_003614B0(ItemCreationNineSlotView* object)
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
            resource = (u8)item_resource_index(value);
            allocation = func_002D3D80(D_001B643C->unk20, resource);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            func_002D5CF0(object->unk13c[index], allocation, record, resource);
            object->unk13c[index]->unk3F = 1;
            object->unk190++;
            object->unk1f2[index] = item_assigned_code(value);
        }
        else
        {
            object->unk13c[index]->unk3F = 0;
            object->unk1f2[index] = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003615C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003619D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00361AB0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00361D40);

u8 func_003623C0(ItemCreationTripleState* object, u8 index)
{
    u8 present;
    u8 first = 0;
    u8 second = 0;
    u8 third = 0;
    switch (index)
    {
    case 0:
        first = object->unk1f2[0][0];
        second = object->unk1f2[0][1];
        third = object->unk1f2[0][2];
        break;
    case 1:
        first = object->unk1f2[1][0];
        second = object->unk1f2[1][1];
        third = object->unk1f2[1][2];
        break;
    case 2:
        first = object->unk1f2[2][0];
        second = object->unk1f2[2][1];
        third = object->unk1f2[2][2];
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362460);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003625E0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362760);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362990);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00362BA0);

void func_00363D20(ItemCreationNineSlotView* object)
{
    s32 index;
    object->unk1f1 = object->unka8->unk57;
    for (index = 0; index < 3; index++)
    {
        if (index < object->unk1f1)
        {
            ItemCreationColorDisplay* display1;
            ItemCreationColorDisplay* display2;
            ItemCreationColorDisplay* display3;
            ItemCreationColorDisplay* display4;
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
            ItemCreationColorDisplay* display1;
            ItemCreationColorDisplay* display2;
            ItemCreationColorDisplay* display3;
            ItemCreationColorDisplay* display4;
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", __dt__23ItemCreationClass1870B0Fv);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00363F10);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364200);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364610);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003646D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003647A0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364870);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364A40);

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
            resource = (u8)item_resource_index(value);
            allocation = func_002D3D80(D_001B643C->unk20, resource);
            record = func_002D3CC0(D_001B643C->unk20, 0x51);
            func_002D5CF0(object->unkf0[index], allocation, record, resource);
            object->unkf0[index]->unk3F = 1;
        }
        else
        {
            object->unkf0[index]->unk3F = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364E00);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00364F50);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", __dt__23ItemCreationClass1871B0Fv);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365600);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365A50);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365AC0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365B30);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365BF0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00365F20);

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
                            if (object->unka8->unk4e[object->unkd0[index] - 1] == 0)
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
                ItemCreationCheckedRecord* record = D_001B643C->unk00;
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003661F0);

void func_00366CB0(ItemCreationCheckedValueOwner* object)
{
    if (object->unke4 != 0)
    {
        ItemCreationCheckedRecord* record = D_001B6430->unk04;
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00366E10);

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
                        void* allocation = func_002D3D80(D_001B643C->unk20, resource);
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
                        void* allocation = func_002D3D80(D_001B643C->unk20, resource);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00367100);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00367BD0);

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
        unk128[i].unk00 = 0;
    }
    for (s32 i = 0; i < 3; i++)
    {
        unk128[i].unk04 = 0;
    }
    for (s32 i = 0; i < 3; i++)
    {
        unk128[i].unk08 = 0;
    }
    unk120 = 0;
    unk124 = 0;
    unk125 = 0;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00367D80);

ItemCreationClass1874B0::~ItemCreationClass1874B0()
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00368150);

ItemCreationClass1875B0::~ItemCreationClass1875B0()
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_00368370);
