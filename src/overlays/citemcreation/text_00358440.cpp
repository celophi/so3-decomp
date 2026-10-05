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

/** Partial parent containing the Field selection marker. */
struct ItemCreationTwoColorReturnParent
{
    u8 unk00[0xB4];
    FieldObject23CEA0* unkb4;
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

/** Partial resident directory containing the current checked record. */
typedef struct ItemCreationRecordDirectory6430
{
    u8 unk00[4];
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
/** Six-byte category record containing an icon and its channel. */
struct ItemCreationSingleIconRecord
{
    u8 unk00[2];
    u8 unk02;
    u8 unk03;
    u8 unk04[2];
};
/** Thirteen-byte category record containing eight channel icons. */
struct ItemCreationIconRecord
{
    u8 icons[8];
    u8 unk08[5];
};

// These external interfaces are scoped here because their owning code is in other overlays.
extern "C"
{
    extern ItemCreationAllocationRecord* D_001B64F8;
    extern ResidentRequest112400* D_001B65F8;
    extern ItemCreationCategoryDefinition* D_001B64F0;
    extern ItemCreationResourceDirectory* D_001B643C;
    extern const char D_0036F738[];
    extern const ItemCreationSingleIconRecord D_501DA0[];
    extern const ItemCreationIconRecord D_501E50[];
    extern ItemCreationRecordDirectory6430* D_001B6430;
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
 * @brief Initialize the frame widget's drawing storage.
 * @param object Frame widget.
 * @param value Supplied frame value; unused by this implementation.
 * @return One on success, or zero if its storage could not be initialized.
 */
s32 func_44B510(ItemCreationClass1746A0* object, u32 value);
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
 * @brief Configure the list position marker's coordinates and storage.
 * @param object List position marker.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @return Initialization status.
 */
s32 func_467360(ItemCreationClass175030* object, float x, float y);
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
    ItemCreationDetailRecords* table = static_cast<ItemCreationDetailRecords*>(static_cast<void*>(D_001B64F8));
    u8 index = value;
    if (valid_detail_index(index))
    {
        return &table->records[index - 1];
    }
    return 0;
}
/**
 * @brief Test whether a category uses the eight-channel icon table.
 * @param category Detail category.
 * @return One for categories from twenty-nine onward, otherwise zero.
 */
static inline u8 has_extended_icons(u8 category)
{
    return category >= 29;
}
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
    u32 resource = (u8)item_resource_index(unk101);
    void* allocation = func_002D3D80(D_001B643C->unk20, resource);
    FieldResourceRecord* source = func_002D3CC0(D_001B643C->unk20, 81);
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
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
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
        s32 count = func_0040CF90(D_001B64F8, records, (u16)unk1bc);
        s32 selected = unk24;
        if (count != 0 && selected >= 0)
        {
            s32 message = (u16)D_001B64F0[allocation_value(records[selected])].unk10_code + 0x88;
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
    ItemCreationSelectedDisplayState* state = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035AB80);

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
        s32 count = func_0040CF90(D_001B64F8, records, (u16)category);
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
    unk88 = func_0040CF90(D_001B64F8, records, (u16)category);
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
    void* allocation = func_002D3D80(D_001B643C->unk20, 14);
    for (s32 index = 0; index < 6; index++)
    {
        FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 60);
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
    unk1b4 = static_cast<ItemCreationSelectedDisplayState*>(D_001B643C->unk10->unk14);
    FieldClass15AE60::unk88 = 0;
    FieldClass15AE60::unk88 = func_0040CF90(D_001B64F8, records, unk1bc);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035C6A0);

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

/** @brief Refresh the active mode list and its selection cursor. */
void ItemCreationClass186C90::func_slot5c()
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

/** Set the selection marker depth and mark the widget for refresh. */
static inline void set_selector_depth(FieldClass153130* widget, float depth)
{
    if (widget != 0)
    {
        widget->ItemCreationClass185050::unk30 = depth;
        widget->unk3c = 1;
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
        D_001B643C->unk10->unk14->func_00263C70(parent);
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
    set_selector_depth(selector, 64.0f);
    func_23B3A0(reinterpret_cast<FieldState23B3A0*>(unkac));
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035E770);

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
                D_001B643C->unk10->unk14->func_00263C70(unka8);
            }
            break;
        }
    }
    return 2;
}

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_0035FCA0);

/**
 * @brief Reset the option selection and handle the current return mode.
 * @return Always two.
 */
s32 ItemCreationClass186FB0::func_slotb4()
{
    func_slot20(0);
    func_0023B310(reinterpret_cast<FieldObject23B280*>(unkd4));
    func_0035FCA0(reinterpret_cast<u8*>(this), 0);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_00358440", func_003600E0);

/**
 * @brief Refresh the option display after selection movement.
 */
void ItemCreationClass186FB0::func_slot6c()
{
    if (unkd4 != 0 && (u8)func_23B3B0(reinterpret_cast<FieldState23B3A0*>(unkd4), 1) != 1)
    {
        u16 selected = func_23B3A0(reinterpret_cast<FieldState23B3A0*>(unkd4));
        func_0035FCA0(reinterpret_cast<u8*>(this), selected);
    }
}
/**
 * @brief Refresh the option display after selection movement.
 */
void ItemCreationClass186FB0::func_slot68()
{
    if (unkd4 != 0 && (u8)func_23B3B0(reinterpret_cast<FieldState23B3A0*>(unkd4), 0) != 1)
    {
        u16 selected = func_23B3A0(reinterpret_cast<FieldState23B3A0*>(unkd4));
        func_0035FCA0(reinterpret_cast<u8*>(this), selected);
    }
}
/**
 * @brief Create eight option displays and their selection widgets.
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
    unkb0 = new (0) LibClass178630;
    func_004C5A80(unkb0, 0, 0.0f, 0.0f, 96.0f, 248.0f, 88.0f);
    func_004C6190(unk10, unkb0);
    for (s32 index = 0; index < 8; index++)
    {
        unkb4[index] = new (0) LibObject178750;
        unkb4[index]->func_004C7FE0(20.0f, 12.0f + 28.0f * index, 0.0f, 0.0f, (s32)associated, index + 0x3458, 0);
        func_004C6190(unk10, unkb4[index]);
        if (unka8->unk4e[(u8)(index + 1) - 1] != 0)
        {
            unkb4[index]->set_color(0x808080);
        }
        else
        {
            unkb4[index]->set_color(0x505050);
        }
    }
    unkd4 = new (0) FieldClass153130;
    unkd4->func_0023B530(1, 8, 1, 0, 1, 16.0f, 24.0f, 0.0f, 28.0f);
    func_004C6190(unk10, unkd4);
    unkd8 = new (0) FieldClass153170;
    unkd8->func_0023B850(unkb4[0], 0x288080);
    func_004C6190(unk10, unkd8);
    func_0035FCA0(reinterpret_cast<u8*>(this), 0);
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
    unkb0 = 0;
    unkb4[0] = 0;
    unkb4[1] = 0;
    unkb4[2] = 0;
    unkb4[3] = 0;
    unkb4[4] = 0;
    unkb4[5] = 0;
    unkb4[6] = 0;
    unkb4[7] = 0;
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
