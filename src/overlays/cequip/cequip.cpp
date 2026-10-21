#include "overlays/cequip/cequip.h"
#include "main/resident_data.h"
#include "main/resident_0010A0E0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "main/resident_001001E0.h"
#include "main/resident_00101260.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"
#include "overlays/lib/list_indicator_inlines.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/lib/item_allocation.h"

enum EquipMessageKey
{
    EQUIP_MSG_LABEL_SEPARATOR = 0x7E4,
    EQUIP_MSG_YES = 0x7E8,
    EQUIP_MSG_NO = 0x7E9,
    EQUIP_MSG_STAT_NAME_BASE = 0x81A,
    EQUIP_MSG_TITLE = 0xFA0,
    EQUIP_MSG_SLOT_NAME_BASE = 0xFA1,
    EQUIP_MSG_LEVEL = 0xFA9,
    EQUIP_MSG_CONFIRM_EXIT = 0xFAC,
    EQUIP_MSG_HELP_FIRST = 0xFAE,
    EQUIP_MSG_CHANGE_HELP = 0xFAE,
    EQUIP_MSG_HELP_END = 0xFAF,
    EQUIP_MSG_MENU_LABEL = 0xFAF,
    EQUIP_MSG_SWITCH_PROMPT = 0xFB5,
    EQUIP_MSG_OPTIMIZE_PROMPT = 0xFB6,
    EQUIP_MSG_ARROW = 0xFB7,
    EQUIP_MSG_NONE = 0xFBA,
    EQUIP_MSG_PARAMETER_CHANGES = 0xFBB,
    EQUIP_MSG_PARAMETER_NAME_BASE = 0xFBC,
    EQUIP_MSG_ITEM_NAME_BASE = 50000,
    EQUIP_MSG_ITEM_DESCRIPTION_BASE = 0x12924
};

/** Partial aligned resource header, with its payload size at offset 0x40. */
struct EquipAlignedResource
{
    u8 unk00[0x40];

    s32 unk40;
};

/** Partial runtime storage for the loaded resource slot and equipment resource keys. */
struct EquipRuntimeResource
{
    u8 unk00[0x514];

    s32 unk514;

    u32 unk518;

    s32 unk51c;

    u32 unk520;
};

/** @brief Align a resource buffer to the next 128-byte boundary. @param buffer Resource buffer. @return Aligned resource header. */
static inline EquipAlignedResource* aligned_resource(void* buffer)
{
    return reinterpret_cast<EquipAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}

/** Packed 16-byte item allocation record with a ten-bit code and checksum key. */
struct EquipPackedRecord
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

    u8 unk0d_key : 2;

    u8 unk0d_high : 3;

    u16 unk0e;
};

/** Partial 0xC4-byte character record containing protected statistic triples, checksums and salt. */
struct EquipRecordStats
{
    u8 unk00[0x34];

    u32 unk34[5][3];

    u8 unk70[0x24];

    u32 unk94[4];

    u8 unka4[4];

    u32 unka8;

    u8 unkac[0x18];
};

struct EquipRuntimeMenuState;

struct EquipRuntimeMenuContext
{
    u8 unk00[0x14];

    EquipRuntimeMenuState* unk14;
};

/** Partial menu flags read by alternate-window activation. */
struct EquipRuntimeMenuFlags
{
    u8 unk00[0x2D];

    u8 unk2d;
};

struct EquipRuntimeMenuRoot
{
    u8 unk00[0xC];

    EquipRuntimeMenuFlags* unk0c;

    EquipRuntimeMenuContext* unk10;

    u8 unk14[0xC];

    FieldBufferSlots* unk20;
};

extern EquipRuntimeMenuRoot* D_001B643C;

extern ResidentObject1B64F8* D_001B64F8;

struct EquipResourceTextRecord;

extern "C" void optimize_equipment(EquipController* state, FieldRecord* record, EquipResourceTextRecord* resource, s8 slot);

extern "C" void func_003F9890(FieldRecord* record, EquipResourceTextRecord* resource, u32 flag, s32 index);

extern "C" void refresh_equipment_slots(EquipSlotWindow* object);

extern "C" void preview_item_stats(EquipStatComparisonWindow* window, s16 selected);

extern "C" void equip_item_in_active_slot(EquipSlotWindow* object, s16 identifier);

extern "C" s32 func_0040C7E0(void* state, s16 identifier, s32 mode);

extern "C" void func_004E97A0(void* object);

extern "C" void func_004E97B0(void* object, float x, float y, float z, s16 identifier, u32 flag);

/** @brief Initialize the embedded tooltip displays. @param object Tooltip container. @return One after initialization, otherwise zero. */
extern "C" s32 func_004E9BC0(EquipClass1796F0* object);

/** @brief Set the item icon's mode flag and mark its display dirty. @param icon Item icon. @param enabled Mode flag. */
static inline void equip_set_icon_enabled(LibObject172410* icon, u8 enabled)
{
    icon->unkfa = enabled;
    icon->unk3c = 1;
}

/** @brief Cycle the selector in the supplied direction. @param object Selector. @param direction Direction code. @return Selector result code. */
extern "C" u8 func_0023B3B0(FieldState23B3A0* object, u16 direction);

/** Resource text record with its displayed payload beginning at offset 0x20. */
struct EquipResourceTextRecord
{
    u8 unk00[0x20];

    u8 unk20[0xF4];
};

/**
 * @brief Decode one protected equipment entry after validating its check word.
 * @param resource Resource record.
 * @param index Entry index.
 * @return Decoded record index, or zero when invalid or out of range.
 */
static inline s16 protected_equipment_entry(const EquipResourceEquipment* resource, s32 index)
{
    if (resource->check_word !=
        (resource->check_salt ^ ((resource->encoded_items[1] + resource->encoded_items[2]) ^ (resource->encoded_items[3] + resource->encoded_items[0]))))
    {
        return 0;
    }

    if (index < 0)
    {
        return 0;
    }

    if ((resource->encoded_last_slot ^ 0x7E93) < index)
    {
        return 0;
    }

    return static_cast<s16>(resource->encoded_items[index] ^ 0x7E93);
}

/** Partial view of a 0xC4-byte field record containing the protected display code. */
struct EquipRecordDetails
{
    u8 unk00[4];

    s16 unk04;

    s16 unk06;

    u8 unk08[0x7C];

    s32 unk84;

    u8 unk88[0x20];

    s32 unka8;
};

/**
 * @brief Decode a field record display code after validating its check word.
 * @param record Selected field record.
 * @return Decoded code, or one when validation fails.
 */
static inline s32 equip_record_value(const FieldRecord* record)
{
    const EquipRecordDetails* details = reinterpret_cast<const EquipRecordDetails*>(record);

    if (details->unk84 != (details->unka8 ^ (details->unk04 ^ (details->unk06 + details->unka8))))
    {
        return 1;
    }

    return details->unk04 ^ 0x7E93;
}

/** @brief Refresh the selected record description, code, and active display widgets. @param associated Record display window. */
static inline void equip_refresh_record_display(EquipCharacterWindow* associated)
{
    if (associated->selection != 0)
    {
        LibObject175140* text = associated->name_text;
        text->unkfc = reinterpret_cast<const char*>(static_cast<EquipResourceTextRecord*>(associated->selection->unk04)[associated->selection->current].unk20);
        text->unk3c = 1;
        FieldRecord* record = &associated->selection->records[associated->selection->current];
        s32 result = equip_record_value(record);
        LibObject174F20* number = associated->level_value;
        number->numeric_value = result;
        number->unk3c = 1;
        associated->show_current_portrait();
    }
}

struct EquipCategoryRecord
{
    u16 unk00;

    u16 unk02;

    u8 unk04[4];

    u8 unk08;
};

/** Catalog prefix containing the equipment mode and ten-bit slot mask. */
struct EquipCategoryMaskView
{
    u8 pad[0xB];

    u8 low : 4;

    u8 mode : 3;

    u8 high : 1;

    u32 unused : 14;

    u32 mask : 10;

    u32 rest : 8;
};

/** @brief Find a category in resident storage. @param value One-based category index. @return Category, or null outside one through seven hundred fifty. */
static inline ItemCreationCategoryRecord* equip_category_record(s32 value)
{
    ResidentObject1B64F8* base = D_001B64F8;
    u16 index = value;
    bool valid = false;

    if (index > 0 && index <= 750)
    {
        valid = true;
    }

    if (valid)
    {
        return &base->item_types[index - 1];
    }

    return 0;
}

struct EquipCategoryNode
{
    EquipCategoryRecord* value;

    EquipCategoryNode* next;
};

class EquipNewItemTypeNode
{
public:
    u16 value;

    u8 pad_02[2];

    EquipNewItemTypeNode* next;

    /** @brief Destroy the node without releasing its stored value. */
    ~EquipNewItemTypeNode()
    {
    }
};

class EquipItemTypeNode
{
public:
    ItemCreationCategoryRecord* value;

    EquipItemTypeNode* next;

    /** @brief Destroy the node without releasing its stored value. */
    ~EquipItemTypeNode()
    {
    }
};

/** @brief Check the one-based packed record index. @param index Record index. @return True for indices from one through 3000. */
static inline bool valid_record_index(s16 index)
{
    return index > 0 && index <= 3000;
}

/** @brief Find a packed record by its signed index. @param value Record index before narrowing. @return Record pointer, or null for an invalid index. */
static inline EquipPackedRecord* packed_record(s32 value)
{
    EquipPackedRecord* records = reinterpret_cast<EquipPackedRecord*>(D_001B64F8);
    s16 index = value;

    if (valid_record_index(index))
    {
        return &records[index - 1];
    }

    return 0;
}

/** @brief Read one halfword of a packed record. @param record Packed record. @param index Halfword index. @return Stored halfword. */
static inline u16 packed_word(EquipPackedRecord* const& record, s32 index)
{
    return reinterpret_cast<const u16*>(record)[index];
}

/** @brief Validate the packed record checksum. @param record Packed record. @return True when the checksum differs. */
static inline bool invalid_packed_record(EquipPackedRecord* const& record)
{
    return record->unk0e != static_cast<u16>((0x83CF << record->unk0d_key) ^ ((packed_word(record, 4) + (packed_word(record, 0) + packed_word(record, 2))) ^
                                                                              (packed_word(record, 1) + (packed_word(record, 3) + packed_word(record, 5)))));
}

/** @brief Decode a validated packed record code. @param record Packed record. @return Code, or zero for an invalid checksum. */
static inline u16 packed_record_code(EquipPackedRecord* const& record)
{
    if (invalid_packed_record(record))
    {
        return 0;
    }

    return record->unk00.bits.value;
}

/**
 * @brief Decode one of the first four protected statistics.
 * @param record Character record statistics.
 * @param index Statistic index.
 * @return Decoded value, or zero for an invalid checksum.
 */
static inline u32 stat_value(const EquipRecordStats* record, s32 index)
{
    u32 value = record->unk34[index][1];

    if (record->unk94[index] != (record->unka8 ^ (record->unk34[index][2] ^ (record->unk34[index][0] + value))))
    {
        return 0;
    }

    return value ^ 0x7DE3F7E3;
}

/**
 * @brief Decode the final statistic using the fourth statistic checksum.
 * @param record Character record statistics.
 * @return Decoded value, or zero for an invalid checksum.
 */
static inline u32 final_stat_value(const EquipRecordStats* record)
{
    if (record->unk94[3] != (record->unka8 ^ (record->unk34[3][2] ^ (record->unk34[3][0] + record->unk34[3][1]))))
    {
        return 0;
    }

    return record->unk34[4][1] ^ 0x7DE3F7E3;
}

/** @brief Set a numeric widget value and mark it dirty. @param widget Numeric widget. @param value Display value. */
static inline void set_number(LibObject174F20* widget, u32 value)
{
    widget->numeric_value = value;
    widget->unk3c = 1;
}

/**
 * @brief Copy the scalar position and mark the display receiver for refresh.
 * @param target Display receiver to update.
 * @param x Horizontal position component.
 * @param y Vertical position component.
 * @param z Third position component.
 * @param w Fourth position component.
 */
static inline void equip_set_position(LibClass178600* target, float x, float y, float z, float w)
{
    target->unk18.unk00 = x;
    target->unk18.unk04 = y;
    target->unk18.unk08 = z;
    target->unk18.unk0c = w;
    target->unk3c = 1;
}

/** @brief Store the window byte at offset 0xC. @param value Unsigned byte to store. */
void FieldClass15AE70::func_slot24(u8 value)
{
    unk0c = value;
}

/** @brief Read the window byte at offset 0xC. @return Stored unsigned byte. */
u8 FieldClass15AE70::func_slot28()
{
    return unk0c;
}

/** @brief Store the window byte at offset 0x8. @param value Unsigned byte to store. */
void FieldClass15AE70::func_slot2c(u8 value)
{
    unk08 = value;
}

/** @brief Read the window byte at offset 0x8. @return Stored unsigned byte. */
u8 FieldClass15AE70::func_slot30()
{
    return unk08;
}

/** @brief Store the window halfword at offset 0xA. @param value Unsigned halfword to store. */
void FieldClass15AE70::func_slot34(u16 value)
{
    unk0a = value;
}

/** @brief Read the window halfword at offset 0xA. @return Stored unsigned halfword. */
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

/** @brief Store the resource source word. @param value Word to store. */
void FieldClass15AE70::func_slot50(u32 value)
{
    unk04 = value;
}

/** @brief Return the resource source word. @return Stored word. */
u32 FieldClass15AE70::func_slot54()
{
    return unk04;
}

/** @brief Return the nested display container. @return Stored container. */
LibObject178660* FieldClass15AE70::func_slot58()
{
    return unk10;
}

void FieldClass15AE70::func_slot60(s32 text_key)
{
}

void FieldClass15AE70::func_slot64()
{
}

void FieldClass15AE70::func_slot70()
{
}

void FieldClass15AE70::func_slot74()
{
}

void FieldClass15AE70::func_slot78()
{
}

void FieldClass15AE70::func_slot7c()
{
}

void FieldClass15AE70::func_slot80()
{
}

void FieldClass15AE70::func_slot84()
{
}

void FieldClass15AE70::func_slot88()
{
}

void FieldClass15AE70::func_slot8c()
{
}

void FieldClass15AE70::func_slot90()
{
}

void FieldClass15AE70::func_slot94()
{
}

void FieldClass15AE70::func_slot98()
{
}

void FieldClass15AE70::func_slot9c()
{
}

void FieldClass15AE70::func_slota0()
{
}

void FieldClass15AE70::func_slota4()
{
}

void FieldClass15AE70::func_slota8()
{
}

void FieldClass15AE70::func_slotac()
{
}

u8 FieldClass15AE70::func_slotb8()
{
    return 0;
}

u8 FieldClass15AE70::func_slotbc()
{
    return 0;
}

s32 FieldClass15AE70::func_slotc0()
{
    return 0;
}

s32 FieldClass15AE70::func_slotc4()
{
    return 0;
}

s32 FieldClass15AE70::func_slotc8()
{
    return 0;
}

s32 FieldClass15AE70::func_slotcc()
{
    return 0;
}

s32 FieldClass15AE70::func_slotd0()
{
    return 0;
}

s32 FieldClass15AE70::func_slotd4()
{
    return 0;
}

s32 FieldClass15AE70::func_slotd8()
{
    return 0;
}

s32 FieldClass15AE70::func_slotdc()
{
    return 0;
}

void FieldClass15AE70::func_slote0()
{
}

void FieldClass15AE70::func_slote4()
{
}

/** @brief Read the window byte at offset 0xD. @return Stored unsigned byte. */
u8 FieldClass15AE70::func_slote8()
{
    return unk0d;
}

/** @brief Store the window byte at offset 0xD. @param value Unsigned byte to store. */
void FieldClass15AE70::func_slotec(u8 value)
{
    unk0d = value;
}

void FieldClass15AE70::func_slotf0()
{
}

void EquipExitConfirmWindow::func_slotf4(s16 selected)
{
    s32 index = 0;
    FieldListNode* node = unk2c.head->next;

    if (node != 0)
    {
        do
        {
            LibClass174EF0* icon = static_cast<LibClass174EF0*>(node->value);

            if (index == selected)
            {
                icon->set_color(0x288080);
            }
            else
            {
                icon->set_color(0x808080);
            }

            node = node->next;
            index++;
        } while (node != 0);
    }
}

void EquipExitConfirmWindow::func_slot5c()
{
    if (reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14)->func_00261150() == this)
    {
        func_slotf4(grid->unk114);
    }
}

/** @brief Return the stored window pointer. @return Stored pointer. */
void* FieldClass153E30::func_00261150()
{
    return unk20;
}

void EquipExitConfirmWindow::func_slot6c()
{
    if (static_cast<s16>(grid->process_direction(1)) == 1)
    {
        return;
    }
}

void EquipExitConfirmWindow::func_slot68()
{
    if (static_cast<s16>(grid->process_direction(0)) == 1)
    {
        return;
    }
}

u8 EquipExitConfirmWindow::func_slotb4()
{
    FieldClass15AE70::func_slot18(0, 0x7F);
    EquipController* state = reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14);
    state->func_00263C70(func_slot44());
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    return 2;
}

/** @brief Store the window pointer. @param value Pointer to store. */
void FieldClass153E30::func_00263C70(void* value)
{
    unk20 = value;
}

u8 EquipExitConfirmWindow::func_slotb0()
{
    selected = grid->unk114;
    u8 result = 0;

    if (selected == 0)
    {
        set_state(0xFF, 0x80);
    }
    else
    {
        result = func_slotb4();
    }

    u8 status;

    if (result == 0)
    {
        status = 1;
    }
    else
    {
        status = 2;
    }

    return status;
}

s32 EquipExitConfirmWindow::func_slot10(u32 associated, float x, float y, s32 code)
{
    FieldClass15AE70::func_slot10(associated, x, y, code);
    LibClass178630* frame = new (0) LibClass178630;

    if (frame == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(frame, 1, 0.0f, 0.0f, 240.0f, 160.0f, 88.0f);
    lib_container_attach_widget(unk10, frame);
    append_panel_widget_node(&unk14, frame);
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    LibObject178750* title = new (0) LibObject178750;
    grid = new (0) FieldObject23CEA0;

    if (first == 0 || second == 0 || title == 0 || grid == 0)
    {
        return 0;
    }

    first->init_resource_rectangle(84.0f, 84.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_YES, 0);
    second->init_resource_rectangle(84.0f, 120.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_NO, 0);
    title->init_resource_rectangle(24.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_CONFIRM_EXIT, 0);
    lib_container_attach_widget(unk10, first);
    lib_container_attach_widget(unk10, second);
    lib_container_attach_widget(unk10, title);
    append_text_widget_node(&unk2c, first);
    append_text_widget_node(&unk2c, second);
    append_text_widget_node(&unk2c, title);
    grid->func_0023CE80(1, 2);
    grid->func_0023CE60(0.0f, 36.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(1, 84.0f + x, 16.0f + (84.0f + y));
    append_grid_widget_node(&unk74, grid);
    return 1;
}

EquipExitConfirmWindow::~EquipExitConfirmWindow()
{
}

void EquipHelpWindow::func_slot5c()
{
    LibClass178600* target = text;
    float x = target->unk18.unk00;
    float y = target->unk18.unk04;
    float z = target->unk18.unk08;
    float w = target->unk18.unk0c;

    if (scroll_phase == 0)
    {
        equip_set_position(target, initial_text_x, y, z, w);
        initial_pause_frames++;

        if (!((float)initial_pause_frames <= 120.0f))
        {
            initial_pause_frames = 0;
            scroll_phase = 1;
        }

        return;
    }

    x -= 108.0f * D_001B6690;

    if (x < clip_x - (float)scroll_span)
    {
        x = 2.0f + (clip_x + clip_width);
    }

    equip_set_position(target, x, y, z, w);
}

void EquipHelpWindow::func_slot60(s32 text_key)
{
    if (text_key >= EQUIP_MSG_HELP_FIRST && text_key < EQUIP_MSG_HELP_END)
    {
        initial_pause_frames = 0;
        scroll_phase = 0;
        lib_text_set_resource(text, func_slot54(), text_key, 1);
        scroll_span = static_cast<s32>(lib_text_measure_bounds(text)->unk08) + 6;
    }
}

s32 EquipHelpWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 19);
    text = new (0) LibObject178750;
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* overlay = new (0) ItemCreationClass1746A0;

    if (text == 0 || frame == 0 || overlay == 0)
    {
        return 0;
    }

    LibObject178750* title = new (0) LibObject178750;
    title->init_resource_rectangle(16.0f, 6.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_TITLE, 0);
    lib_container_attach_widget(unk10, title);
    append_text_widget_node(&unk2c, title);
    LibObject178750* label = new (0) LibObject178750;
    label->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_MENU_LABEL, 0);
    label->set_scale(0.65f, 0.65f);
    lib_container_attach_widget(unk10, label);
    append_text_widget_node(&unk2c, label);
    label_right_edge = lib_text_measure_bounds(title)->unk08;
    clip_x = 18.0f + label_right_edge;
    float right_margin = 32.0f;
    clip_width = 640.0f - (16.0f + (clip_x + right_margin));
    initial_text_x = 24.0f + label_right_edge;
    lib_scissor_init_rectangle(frame, clip_x, 0.0f, clip_width, 56.0f);
    lib_container_attach_widget(unk10, frame);
    append_clip_widget_node(&unk20, frame);
    text->init_resource_rectangle(initial_text_x, 6.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_CHANGE_HELP, 0);
    lib_container_attach_widget(unk10, text);
    append_text_widget_node(&unk2c, text);
    lib_scissor_init_reset(overlay, 1);
    lib_container_attach_widget(unk10, overlay);
    append_clip_widget_node(&unk20, overlay);
    func_slot60(EQUIP_MSG_CHANGE_HELP);
    return 1;
}

EquipHelpWindow::~EquipHelpWindow()
{
}

s32 EquipResourceWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 20);
    left_tile = new (0) ItemCreationOptionResourceDisplay;
    middle_tile = new (0) ItemCreationOptionResourceDisplay;
    right_tile = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = field_get_aligned_allocation(D_001B643C->unk20, 11);
    left_tile->unkcc = allocation;
    middle_tile->unkcc = allocation;
    right_tile->unkcc = allocation;
    left_tile->unkd0 = 11;
    middle_tile->unkd0 = 11;
    right_tile->unkd0 = 11;
    left_tile->func_002D6440(field_find_resource_record(D_001B643C->unk20, 5), 0.0f, 0.0f);
    middle_tile->func_002D6440(field_find_resource_record(D_001B643C->unk20, 6), 256.0f, 0.0f);
    right_tile->func_002D6440(field_find_resource_record(D_001B643C->unk20, 7), 512.0f, 0.0f);
    lib_container_attach_widget(unk10, left_tile);
    lib_container_attach_widget(unk10, middle_tile);
    lib_container_attach_widget(unk10, right_tile);
    return 1;
}

ItemCreationClass175110::~ItemCreationClass175110()
{
}

EquipResourceWindow::~EquipResourceWindow()
{
}

/** @brief Write a stored display flag. @param display Display to update. @param flag Low-byte flag to store. */
static inline void set_visibility(LibClass178600* display, const u8& flag)
{
    display->unk3f = flag;
}

void EquipItemInstanceListWindow::func_slot10c(u32 value, u32 enabled)
{
    s32 index;
    u8 flag = value;

    for (index = 0; index < 9; index++)
    {
        set_visibility(item_icons[index], flag);
        set_visibility(factor_marks[index], flag);
    }

    if (panel != 0)
    {
        set_visibility(panel, flag);
    }

    if (FieldStateCE420::unk04 != 0)
    {
        FieldStateCE420::unk04->unk3f = enabled;

        if (enabled != 0)
        {
            ItemCreationClass175030* nested = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            nested->ItemCreationClass185050::unk30 = 128.0f;
            nested->unk3c = 1;
        }
        else
        {
            ItemCreationClass175030* nested = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            nested->ItemCreationClass185050::unk30 = 64.0f;
            nested->unk3c = 1;
        }
    }

    if (FieldStateCE420::unk00 != 0)
    {
        FieldStateCE420::unk00->unk3f = enabled;
    }
}

/** @brief Return the empty equipment selection result. @return Zero. */
u8 EquipItemInstanceListWindow::func_slotb8()
{
    return 0;
}

/** @brief Toggle the linked display flag. @return One. */
u8 EquipItemInstanceListWindow::func_slotbc()
{
    EquipParameterWindow* target = controller->parameter_window;
    target->show_parameters = !target->show_parameters;
    return 1;
}

u8 EquipItemInstanceListWindow::func_slotb4()
{
    controller->remove_child(this);
    FieldClass15AD40* associated = static_cast<FieldClass15AD40*>(func_slot44());
    associated->func_slot10c(1, 1);
    reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(associated);
    preview_item_stats(controller->comparison_window, 0);
    func_004E97A0(tooltip);
    return 2;
}

u8 EquipItemInstanceListWindow::func_slotb0()
{
    ItemCreationAllocationRecord* records[100];

    if (FieldClass15AE60::unk88 == 0)
    {
        return 3;
    }

    s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, static_cast<u16>(controller->selected_item_type));
    s32 selected = FieldStateCE420::unk24;

    if (count != 0 && selected >= 0)
    {
        if (tooltip != 0)
        {
            func_004E97A0(tooltip);
        }

        FieldClass15AE70* first = controller->slot_window;
        FieldClass15AE70* second = controller->comparison_window;
        equip_item_in_active_slot(static_cast<EquipSlotWindow*>(first), lib_allocation_get_identifier(records[selected]));
        first->func_slot20(1);
        first->func_slot64();
        reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(first);
        preview_item_stats(static_cast<EquipStatComparisonWindow*>(second), 0);
        second->func_slot20(0);
        FieldClass15AD40* associated = static_cast<FieldClass15AD40*>(func_slot44());
        associated->func_slot108(static_cast<u8>(controller->selected_slot));
        associated->func_slot10c(0, 0);
        controller->remove_child(this);
        func_004E97A0(tooltip);
    }
    else
    {
        return 3;
    }

    return 1;
}

void EquipItemInstanceListWindow::func_slot5c()
{
    ItemCreationAllocationRecord* records[100];

    if (reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00261150() == this)
    {
        FieldClass15AD40::func_slot5c();

        if (reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00261150() == this)
        {
            ItemCreationClass175030* nested = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            nested->ItemCreationClass185050::unk30 = 128.0f;
            nested->unk3c = 1;
        }
        else
        {
            ItemCreationClass175030* nested = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            nested->ItemCreationClass185050::unk30 = 64.0f;
            nested->unk3c = 1;
        }

        s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, static_cast<u16>(controller->selected_item_type));
        s32 selected = FieldStateCE420::unk24;
        EquipStatComparisonWindow* detail = controller->comparison_window;

        if (count != 0 && selected >= 0)
        {
            preview_item_stats(detail, lib_allocation_get_identifier(records[selected]));
            LibObject172410* icon = item_icons[FieldStateCE420::unk28];
            set_selection_marker(icon, icon->unk94);
            const LibUiRect16* position = &item_icons[FieldStateCE420::unk28]->unk18;
            s32 x = static_cast<s32>(283.0f + position->unk00);
            s32 y = static_cast<s32>(224.0f + (30.0f + position->unk04));
            bool active = reinterpret_cast<FieldState23B3A0*>(FieldStateCE420::unk04)->unk75 != 0 && FieldClass15AE60::pad29[1] == 0;

            if (active)
            {
                if (tooltip_item != lib_allocation_get_identifier(records[selected]))
                {
                    tooltip_item = lib_allocation_get_identifier(records[selected]);
                    func_004E97A0(tooltip);
                }

                func_004E97B0(tooltip, static_cast<float>(x), static_cast<float>(y), 18.0f, lib_allocation_get_identifier(records[selected]), 0);
            }
            else
            {
                func_004E97A0(tooltip);
            }
        }
        else
        {
            preview_item_stats(detail, 0);
            set_selection_marker(0, 0x808080);
        }
    }
}

void EquipItemInstanceListWindow::set_scroll_position(float offset)
{
    float position = (16.0f + offset) - 4.0f;
    s32 index = 0;

    do
    {
        LibClass178600* target_third;
        LibClass178600* target_second;
        target_third = item_icons[index];
        target_third->unk18.unk04 = position;
        target_third->unk3c = 1;
        target_second = factor_marks[index];
        target_second->unk18.unk04 = position;
        target_second->unk3c = 1;
        position += 28.0f;
        index++;
    } while (index < 9);
}

/** @brief Select the displayed item code. @param icon Code widget. @param category Category identifier. @param variant Packed record variant. */
static inline void set_equipment_icon(LibObject172410* icon, s32 category, u8 variant)
{
    icon->unkfc = category;
    icon->unkfe = variant;
    icon->unk3c = 1;
}

void EquipItemInstanceListWindow::refresh_rows(s32 start)
{
    ItemCreationAllocationRecord* records[100];
    s32 category = controller->selected_item_type;

    for (s32 index = 99; index >= 0; index--)
    {
        records[index] = 0;
    }

    FieldClass15AE60::unk88 = lib_collect_unequipped_allocations(D_001B64F8, records, category);

    for (s32 row = 0; row < 9; row++)
    {
        if (records[start + row] == 0)
        {
            item_icons[row]->unk3d = 0;
            factor_marks[row]->unk3d = 0;
        }
        else
        {
            set_equipment_icon(item_icons[row], category, records[start + row]->modification_number);
            s32 count = 0;

            for (s32 index = 0; index < 8; index++)
            {
                u16 value = func_0040D930(records[start + row], index);

                if (value != 0 && value != 700)
                {
                    count++;
                }
            }

            factor_marks[row]->func_002D5CF0(mark_allocation, field_find_resource_record(D_001B643C->unk20, count + 60), 14);
            item_icons[row]->unk3d = 1;
            factor_marks[row]->unk3d = 1;
        }
    }
}

void EquipItemInstanceListWindow::recount_rows()
{
    ItemCreationAllocationRecord* records[100];
    FieldClass15AE60::unk88 = 0;
    FieldClass15AE60::unk88 = lib_collect_unequipped_allocations(
        D_001B64F8, records, static_cast<u16>(reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14)->selected_item_type));
    s32 count = FieldClass15AE60::unk88;

    if (count >= 8)
    {
        count = 8;
    }

    s32 start = FieldStateCE420::unk22;

    if (FieldClass15AE60::unk88 < start + 8)
    {
        start = FieldClass15AE60::unk88 - 8;
    }

    if (start < 0)
    {
        start = 0;
    }

    s32 row = FieldStateCE420::unk28;

    if (row >= count)
    {
        row = count - 1;
    }

    if (row < 0)
    {
        row = 0;
    }

    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, count, 312, 28);
    FieldClass15AE60::configure_selection(FieldClass15AE60::unk88, start, row);
}

/** @brief Set the drawing depth and mark the display dirty. @param icon Drawing widget. @param depth Drawing depth. */
static inline void set_display_depth(LibClass174EF0* icon, float depth)
{
    icon->unk88 = depth;
    icon->unk3c = 1;
}

/** @brief Set both resource drawing scales and mark the display dirty. @param display Resource display. @param x Horizontal scale. @param y Vertical scale. */
static inline void set_resource_scale(ItemCreationOptionResourceDisplay* display, float x, float y)
{
    display->unk50.unk34 = y;
    display->unk50.unk30 = x;
    display->unk3c = 1;
}

s32 EquipItemInstanceListWindow::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 283.0f, 224.0f, 8);
    FieldStateCE420::unk3c = 1;
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* overlay = new (0) ItemCreationClass1746A0;
    panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 1, 0.0f, 0.0f, 340.0f, 248.0f, 88.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, panel);
    lib_scissor_init_rectangle(frame, 8.0f, 10.0f, 302.0f, 224.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, frame);
    mark_allocation = field_get_aligned_allocation(D_001B643C->unk20, 14);

    for (s32 index = 0; index < 9; index++)
    {
        item_icons[index] = new (0) LibObject172410;
        float y = 12.0f + 28.0f * static_cast<float>(index);
        lib_item_code_init_rectangle(item_icons[index], 34.0f, y, 302.0f, 21.599998f, 0, 0, 0);
        item_icons[index]->set_scale(0.9f, 0.9f);
        equip_set_icon_enabled(item_icons[index], 1);
        set_display_depth(item_icons[index], -1.0f);
        lib_container_attach_widget(FieldClass15AE70::unk10, item_icons[index]);
        factor_marks[index] = new (0) ItemCreationOptionResourceDisplay;
        FieldResourceRecord* record = field_find_resource_record(D_001B643C->unk20, 60);
        void* allocation = mark_allocation;
        factor_marks[index]->unkcc = allocation;
        factor_marks[index]->unkd0 = 14;
        factor_marks[index]->func_002D6440(record, 13.0f, y);
        set_resource_scale(factor_marks[index], 0.9f, 0.9f);
        lib_container_attach_widget(FieldClass15AE70::unk10, factor_marks[index]);
        factor_marks[index]->unk3f = 0;
    }

    lib_scissor_init_reset(overlay, 1);
    lib_container_attach_widget(FieldClass15AE70::unk10, overlay);
    FieldStateCE420::unk34 = 8.0f;
    FieldStateCE420::unk38 = 24.0f;
    FieldStateCE420::unk04 = new (0) ItemCreationClass175030;
    lib_moving_widget_init_position(static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04), 10.0f, 24.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, FieldStateCE420::unk04);
    FieldStateCE420::unk04->unk3f = 0;
    FieldStateCE420::unk00 = new (0) ItemCreationClass1725D0;
    lib_list_indicator_init(static_cast<ItemCreationClass1725D0*>(FieldStateCE420::unk00), 314.0f, 12.0f, 224.0f, 10.0f, 0);
    lib_container_attach_widget(FieldClass15AE70::unk10, FieldStateCE420::unk00);
    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, 8, 312, 28);
    FieldStateCE420::unk2b = 3;
    unk85 = 0;
    func_slot110(1);
    func_slot10c(1, 1);
    recount_rows();
    return 1;
}

/** @brief Store the selection byte at offset 0x84. @param value Byte to store. */
void FieldClass15AD40::func_slot110(u8 value)
{
    FieldClass15AE60::unk84 = value;
}

EquipItemInstanceListWindow::EquipItemInstanceListWindow(EquipController* state)
{
    for (s32 index = 0; index < 9; index++)
    {
        unk48[index] = 0;
        item_icons[index] = 0;
        factor_marks[index] = 0;
    }

    controller = state;
    panel = 0;
    mark_allocation = 0;
    FieldClass15AD40();
    tooltip = 0;
    tooltip = state->tooltip;
    tooltip_item = 0;
}

/** @brief Toggle the linked display flag. @return One. */
u8 EquipItemListWindow::func_slotbc()
{
    EquipParameterWindow* target = controller->parameter_window;
    target->show_parameters = !target->show_parameters;
    return 1;
}

u8 EquipItemListWindow::func_slotb4()
{
    func_slot10c(0, 0);
    FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(func_slot44());

    if (associated != 0)
    {
        associated->func_slot20(1);
        associated->func_slot64();
        reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(associated);
    }

    FieldClass15AE70* other = comparison_window;

    if (other != 0)
    {
        other->func_slot20(0);
    }

    return 2;
}

u8 EquipItemListWindow::func_slotb0()
{
    if (FieldClass15AE60::unk88 == 0)
    {
        return 3;
    }

    if (controller == 0)
    {
        return 0;
    }

    if (FieldStateCE420::unk24 == 0)
    {
        FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(func_slot44());

        if (associated != 0)
        {
            equip_item_in_active_slot(static_cast<EquipSlotWindow*>(associated), 0);
            associated->func_slot20(1);
            associated->func_slot64();
            FieldStateCE420::unk04->unk3f = 0;
            reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(associated);
            refresh_rows(FieldStateCE420::unk22);
        }

        if (comparison_window != 0)
        {
            comparison_window->func_slot20(0);
        }

        return 1;
    }

    if (FieldClass15AE60::unk88 != 0)
    {
        EquipItemInstanceListWindow* window = new (0) EquipItemInstanceListWindow(controller);
        u32 associated = controller->get_resource_slot();
        window->func_slot104(associated);
        window->func_slot40(this);
        controller->add_child(window);
        controller->func_00263C70(window);
    }
    else
    {
        return 3;
    }

    FieldStateCE420::unk04->unk3f = 0;
    return 1;
}

/** @brief Return the loaded resource slot. @return Resource slot. */
u32 EquipController::get_resource_slot()
{
    return resource_slot;
}

/**
 * @brief Set the optional control's flag and opacity.
 * @param unused Unused first word.
 * @param value Value tested for zero and stored in the control's low-byte flag.
 */
void EquipItemListWindow::func_slot10c(u32 unused, u32 value)
{
    if (FieldStateCE420::unk04 != 0)
    {
        FieldStateCE420::unk04->unk3f = value;

        if (value != 0)
        {
            ItemCreationClass175030* nested = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            nested->ItemCreationClass185050::unk30 = 128.0f;
            nested->unk3c = 1;
        }
        else
        {
            ItemCreationClass175030* nested = static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04);
            nested->ItemCreationClass185050::unk30 = 64.0f;
            nested->unk3c = 1;
        }
    }
}

void EquipItemListWindow::set_scroll_position(float offset)
{
    float position = 16.0f + offset;
    s32 index;
    index = 0;

    do
    {
        LibClass178600* target_first;
        LibClass178600* target_second;
        LibClass178600* target_third;
        target_first = unk48[index];
        target_first->unk18.unk04 = position;
        target_first->unk3c = 1;
        target_second = separators[index];
        target_second->unk18.unk04 = position;
        target_second->unk3c = 1;
        target_third = counts[index];
        target_third->unk18.unk04 = position;
        target_third->unk3c = 1;
        position += 28.0f;
        index++;
    } while (index < 9);
}

void EquipItemListWindow::refresh_rows(s32 start)
{
    if (controller != 0)
    {
        EquipCategoryNode* node = static_cast<EquipCategoryNode*>(get_item_type_node(&item_types, start));

        for (s32 row = 0; row < 9; row++)
        {
            if (node != 0)
            {
                s32 category;
                bool found;
                s32 index;
                EquipCategoryRecord* record = node->value;

                if (record != 0)
                {
                    found = false;
                    u16 count = static_cast<u16>(new_item_types.count);
                    index = 0;
                    category = static_cast<u16>(record->unk02 + 1);
                    s32 key = category + EQUIP_MSG_ITEM_NAME_BASE;

                    for (; index < count; index++)
                    {
                        if (category == *static_cast<u16*>(get_new_item_type_node(&new_item_types, index)))
                        {
                            found = true;
                            break;
                        }
                    }

                    if (found)
                    {
                        static_cast<LibClass174EF0*>(FieldClass15AE60::unk48[row])->set_color(0x508050);
                    }
                    else
                    {
                        static_cast<LibClass174EF0*>(FieldClass15AE60::unk48[row])->set_color(0x808080);
                    }

                    lib_text_set_resource(static_cast<LibObject178750*>(FieldClass15AE60::unk48[row]), func_slot54(), key, 0);
                    LibObject174F20* image = counts[row];
                    image->numeric_value = record->unk08;
                    image->unk3c = 1;
                    FieldClass15AE60::unk48[row]->unk3d = 1;
                    separators[row]->unk3d = 1;
                    counts[row]->unk3d = 1;
                }
                else
                {
                    static_cast<LibClass174EF0*>(FieldClass15AE60::unk48[row])->set_color(0x808080);
                    lib_text_set_resource(static_cast<LibObject178750*>(FieldClass15AE60::unk48[row]), func_slot54(), EQUIP_MSG_NONE, 0);
                    FieldClass15AE60::unk48[row]->unk3d = 1;
                    separators[row]->unk3d = 0;
                    counts[row]->unk3d = 0;
                }

                node = node->next;
            }
            else
            {
                FieldClass15AE60::unk48[row]->unk3d = 0;
                separators[row]->unk3d = 0;
                counts[row]->unk3d = 0;
            }
        }
    }
}

/**
 * @brief Collect a category's unequipped allocations.
 * @param category Category record, or null.
 * @param records Receives the allocation records.
 * @param identifier Receives the one-based catalog identifier, or zero.
 * @return Number of records collected.
 */
static inline s32 equip_category_allocations(ItemCreationCategoryRecord* category, ItemCreationAllocationRecord** records, u16& identifier)
{
    identifier = 0;
    s32 count = 0;

    if (category != 0)
    {
        u16 id = category->catalog_index + 1;
        identifier = id;
        count = lib_collect_unequipped_allocations(D_001B64F8, records, id);
    }

    return count;
}

void EquipItemListWindow::func_slot108(u8 category)
{
    s32 index;
    ItemCreationAllocationRecord* records[100];
    clear_item_types(&item_types);
    clear_new_item_types(&new_item_types);
    FieldClass15AE60::unk88 = 1;
    append_item_type(&item_types, 0);
    FieldRecordSelection* selection = controller->selected_records();
    u8 slot = selection->slots[selection->current];

    if (category >= 3)
    {
        category = 2;
    }

    for (index = 1; index <= 750; index++)
    {
        ItemCreationCategoryRecord* entry = equip_category_record(index);

        if (entry != 0)
        {
            const EquipCategoryMaskView* definition =
                reinterpret_cast<const EquipCategoryMaskView*>(reinterpret_cast<const u8*>(D_001B64F0) + entry->catalog_index * 32);

            if ((static_cast<u16>(definition->mask) & (1 << (slot - 1))) != 0 && category == static_cast<u8>(definition->mode) && entry->inventory_count != 0)
            {
                u16 identifier;
                s32 count = equip_category_allocations(entry, records, identifier);

                for (s32 record_index = 0; record_index < count; record_index++)
                {
                    if (records[record_index]->new_item)
                    {
                        append_new_item_type(&new_item_types, identifier);
                        break;
                    }
                }

                append_item_type(&item_types, entry);
                FieldClass15AE60::unk88++;
            }
        }
    }

    s32 rows = FieldClass15AE60::unk88 >= 8 ? 8 : FieldClass15AE60::unk88;
    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, rows, 312, 28);
    FieldClass15AE60::configure_selection(FieldClass15AE60::unk88, 0, 0);
}

/** @brief Return the State's record selection. @return Record selection. */
FieldRecordSelection* EquipController::selected_records()
{
    return selection;
}

void EquipItemListWindow::func_slot5c()
{
    if (reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00261150() == this)
    {
        FieldClass15AD40::func_slot5c();
        EquipCategoryRecord** selected = reinterpret_cast<EquipCategoryRecord**>(get_item_type_node(&item_types, FieldStateCE420::unk24));

        if (selected != 0)
        {
            if (*selected != 0)
            {
                controller->selected_item_type = static_cast<u16>((*selected)->unk02 + 1);
            }
            else
            {
                controller->selected_item_type = 0;
            }
        }

        if (FieldStateCE420::unk24 >= 0 && FieldClass15AE60::unk88 != 0)
        {
            LibClass174EF0* display = static_cast<LibClass174EF0*>(FieldClass15AE60::unk48[FieldStateCE420::unk28]);
            set_selection_marker(display, display->unk94);
        }
        else
        {
            set_selection_marker(0, 0x808080);
        }

        preview_item_stats(controller->comparison_window, 0);
    }
    else
    {
        set_selection_marker(0, 0x808080);
    }
}

s32 EquipItemListWindow::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 283.0f, 224.0f, 9);
    FieldStateCE420::unk3c = 1;
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* overlay = new (0) ItemCreationClass1746A0;
    lib_scissor_init_rectangle(frame, 10.0f, 10.0f, 312.0f, 224.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, frame);

    for (s32 index = 0; index < 9; index++)
    {
        unk48[index] = new (0) LibObject178750;
        separators[index] = new (0) LibObject178750;
        counts[index] = new (0) LibObject174F20;
        float y = 16.0f + 28.0f * static_cast<float>(index);
        static_cast<LibObject178750*>(unk48[index])->init_resource_rectangle(13.0f, y, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_ITEM_NAME_BASE, 0);
        separators[index]->init_resource_rectangle(268.0f, y - 4.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_LABEL_SEPARATOR, 1);
        counts[index]->init_numeric_resource_rectangle(276.0f, y, 28.0f, 24.0f, index, 0, 0);
        set_display_depth(static_cast<LibObject178750*>(unk48[index]), -1.0f);
        static_cast<LibObject178750*>(unk48[index])->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(FieldClass15AE70::unk10, unk48[index]);
        lib_container_attach_widget(FieldClass15AE70::unk10, separators[index]);
        lib_container_attach_widget(FieldClass15AE70::unk10, counts[index]);
    }

    lib_scissor_init_reset(overlay, 1);
    lib_container_attach_widget(FieldClass15AE70::unk10, overlay);
    FieldStateCE420::unk34 = 8.0f;
    FieldStateCE420::unk38 = 28.0f;
    FieldStateCE420::unk04 = new (0) ItemCreationClass175030;
    lib_moving_widget_init_position(static_cast<ItemCreationClass175030*>(FieldStateCE420::unk04), 8.0f, 28.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, FieldStateCE420::unk04);
    FieldStateCE420::unk04->unk3f = 0;
    FieldStateCE420::unk00 = new (0) ItemCreationClass1725D0;
    lib_list_indicator_init(static_cast<ItemCreationClass1725D0*>(FieldStateCE420::unk00), 314.0f, 16.0f, 220.0f, 10.0f, 0.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, FieldStateCE420::unk00);
    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, 8, 312, 28);
    FieldStateCE420::unk2b = 3;
    unk84 = 0;
    unk85 = 0;
    func_slot10c(1, 0);
    func_slot108(0);
    return 1;
}

EquipItemListWindow::EquipItemListWindow(EquipController* state)
{
    for (s32 index = 0; index < 9; index++)
    {
        unk48[index] = 0;
        separators[index] = 0;
        counts[index] = 0;
    }

    controller = 0;
    controller = state;
    FieldClass15AD40();
    unk184 = 0;
    unk194 = 0;
    comparison_window = 0;
}

s32 EquipItemListPanel::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 283.0f, 224.0f, 10);
    LibClass178630* widget = new (0) LibClass178630;
    lib_panel_init_rectangle(widget, 1, 0.0f, 0.0f, 340.0f, 248.0f, 88.0f);
    lib_container_attach_widget(unk10, widget);
    return 1;
}

EquipItemListPanel::~EquipItemListPanel()
{
}

/**
 * @brief Test one protected statistic's check word.
 * @param record Character record statistics.
 * @param index Statistic index.
 * @return True when the check word differs.
 */
static inline bool invalid_comparison_statistic(const EquipRecordStats* record, s32 index)
{
    return record->unk94[index] != (record->unka8 ^ (record->unk34[index][2] ^ (record->unk34[index][0] + record->unk34[index][1])));
}

/**
 * @brief Decode one of the first four protected statistics for the comparison.
 * @param record Character record statistics.
 * @param index Statistic index.
 * @return Decoded value, or zero for an invalid checksum.
 */
static inline u32 comparison_stat_value(const EquipRecordStats* record, s32 index)
{
    if (invalid_comparison_statistic(record, index))
    {
        return 0;
    }

    return record->unk34[index][1] ^ 0x7DE3F7E3;
}

/**
 * @brief Decode the final statistic for the comparison using the fourth statistic check word.
 * @param record Character record statistics.
 * @return Decoded value, or zero for an invalid checksum.
 */
static inline u32 comparison_final_value(const EquipRecordStats* record)
{
    if (invalid_comparison_statistic(record, 3))
    {
        return 0;
    }

    return record->unk34[4][1] ^ 0x7DE3F7E3;
}

/**
 * @brief Show a comparison value colored by whether it rises or falls.
 * @param widget Numeric widget.
 * @param value Value with the selected item equipped.
 * @param previous Current value.
 */
static inline void set_comparison_number(LibObject174F20*& widget, s32 value, s32 previous)
{
    if (value == previous)
    {
        set_number(widget, value);
        widget->set_color(0x808080);
    }
    else if (value > previous)
    {
        set_number(widget, value);
        widget->set_color(0x508050);
    }
    else if (value < previous)
    {
        set_number(widget, value);
        widget->set_color(0x505080);
    }
}

/**
 * @brief Store one protected equipment entry in a resource copy and refresh its check word.
 * @param resource Resource record copy.
 * @param slot Entry index.
 * @param item Record index to store.
 */
static inline void set_comparison_entry(EquipResourceEquipment& resource, s32 slot, s16 item)
{
    if (resource.check_word ==
            (resource.check_salt ^ ((resource.encoded_items[1] + resource.encoded_items[2]) ^ (resource.encoded_items[3] + resource.encoded_items[0]))) &&
        slot >= 0 && slot <= (resource.encoded_last_slot ^ 0x7E93))
    {
        resource.encoded_items[slot] = item ^ 0x7E93;
        resource.check_word =
            (resource.check_salt ^ ((resource.encoded_items[1] + resource.encoded_items[2]) ^ (resource.encoded_items[3] + resource.encoded_items[0])));
    }
}

/**
 * @brief Copy the selected character record with the item equipped in the category slot.
 * @param window Item comparison window.
 * @param selected Record index to equip.
 * @return Original character record.
 */
static inline FieldRecord* copy_comparison_context(EquipStatComparisonWindow* window, const s16& selected)
{
    func_0013A678(&window->preview_record, 0, 0xC4);
    func_0013A678(&window->preview_equipment, 0, 0x114);
    window->preview_item = selected;
    FieldRecordSelection* selection = window->controller->selected_records();
    FieldRecord* original = &selection->records[selection->current];
    EquipResourceTextRecord* resource = &static_cast<EquipResourceTextRecord*>(selection->unk04)[selection->current];
    func_0013A4C0(&window->preview_record, original, 0xC4);
    func_0013A4C0(&window->preview_equipment, resource, 0x114);
    set_comparison_entry(window->preview_equipment, window->slot, window->preview_item);
    func_003F9890(&window->preview_record, reinterpret_cast<EquipResourceTextRecord*>(&window->preview_equipment), 0, -1);
    return original;
}

/**
 * @brief Show the statistics with a record equipped next to the current ones.
 * @param window Item comparison window.
 * @param selected Record index to compare, or zero to hide the comparison.
 */
extern "C" void preview_item_stats(EquipStatComparisonWindow* window, s16 selected)
{
    if (selected == 0)
    {
        window->preview_values[0]->unk3f = 0;
        window->preview_values[1]->unk3f = 0;
        window->preview_values[2]->unk3f = 0;
        window->preview_values[3]->unk3f = 0;
        window->preview_values[4]->unk3f = 0;
        return;
    }

    FieldRecord* original = copy_comparison_context(window, selected);
    s32 value0 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(&window->preview_record), 0);
    s32 value1 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(&window->preview_record), 1);
    s32 value2 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(&window->preview_record), 2);
    s32 value3 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(&window->preview_record), 3);
    s32 value4 = comparison_final_value(reinterpret_cast<EquipRecordStats*>(&window->preview_record));
    s32 previous0 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(original), 0);
    s32 previous1 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(original), 1);
    s32 previous2 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(original), 2);
    s32 previous3 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(original), 3);
    s32 previous4 = comparison_final_value(reinterpret_cast<EquipRecordStats*>(original));
    set_comparison_number(window->preview_values[0], value0, previous0);
    set_comparison_number(window->preview_values[1], value1, previous1);
    set_comparison_number(window->preview_values[2], value2, previous2);
    set_comparison_number(window->preview_values[3], value3, previous3);
    set_comparison_number(window->preview_values[4], value4, previous4);
    window->preview_values[0]->unk3f = 1;
    window->preview_values[1]->unk3f = 1;
    window->preview_values[2]->unk3f = 1;
    window->preview_values[3]->unk3f = 1;
    window->preview_values[4]->unk3f = 1;
}

void EquipStatComparisonWindow::refresh_item_details(u8 category, s16 selected)
{
    slot = category;
    lib_text_set_resource(slot_label, func_slot54(), slot + EQUIP_MSG_SLOT_NAME_BASE, 0);
    item = selected;

    if (item != 0)
    {
        EquipPackedRecord* packed = packed_record(item);
        u16 code = packed_record_code(packed);
        u8 variant = packed->unk0c & 0x7F;
        set_equipment_icon(item_icon, code + 1, variant);
        item_icon->unk3f = 1;
    }
    else
    {
        item_icon->unk3f = 0;
    }

    FieldRecordSelection* selection = controller->selected_records();
    const EquipRecordStats* record = reinterpret_cast<const EquipRecordStats*>(&selection->records[selection->current]);

    if (record != 0)
    {
        set_number(current_values[0], stat_value(record, 0));
        set_number(current_values[1], stat_value(record, 1));
        set_number(current_values[2], stat_value(record, 2));
        set_number(current_values[3], stat_value(record, 3));
        set_number(current_values[4], final_stat_value(record));
        set_number(preview_values[0], stat_value(record, 0));
        set_number(preview_values[1], stat_value(record, 1));
        set_number(preview_values[2], stat_value(record, 2));
        set_number(preview_values[3], stat_value(record, 3));
        set_number(preview_values[4], final_stat_value(record));
    }
}

s32 EquipStatComparisonWindow::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 220.0f, 18);
    slot_label = new (0) LibObject178750;
    slot_label->init_resource_rectangle(14.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_SLOT_NAME_BASE, 1);
    lib_container_attach_widget(unk10, slot_label);
    slot_label->set_scale(0.8f, 0.8f);
    slot_label->set_color(0x806080);
    item_icon = new (0) LibObject172410;
    lib_item_code_init_rectangle(item_icon, 12.0f, 38.0f, 244.0f, 24.0f, 0, 0, 0);
    equip_set_icon_enabled(item_icon, 1);
    item_icon->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, item_icon);

    for (s32 index = 0; index < 5; index++)
    {
        float y = 78.0f + 32.0f * static_cast<float>(index);
        stat_labels[index] = new (0) LibObject178750;
        stat_labels[index]->init_resource_rectangle(28.0f, y - 2.0f, 0.0f, 0.0f, static_cast<s32>(associated), index + EQUIP_MSG_STAT_NAME_BASE, 0);
        stat_labels[index]->set_color(0x805050);
        lib_container_attach_widget(unk10, stat_labels[index]);
        separators[index] = new (0) LibObject178750;
        separators[index]->init_resource_rectangle(73.0f, y, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_LABEL_SEPARATOR, 0);
        separators[index]->set_color(0x805050);
        lib_container_attach_widget(unk10, separators[index]);
        current_values[index] = new (0) LibObject174F20;
        current_values[index]->init_numeric_resource_rectangle(92.0f, y, 48.0f, 22.8f, 9999, 0, 0);
        current_values[index]->set_scale(0.95f, 0.95f);
        lib_container_attach_widget(unk10, current_values[index]);
        arrows[index] = new (0) LibObject178750;
        arrows[index]->init_resource_rectangle(158.0f, y, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_ARROW, 0);
        arrows[index]->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(unk10, arrows[index]);
        preview_values[index] = new (0) LibObject174F20;
        preview_values[index]->init_numeric_resource_rectangle(196.0f, y, 48.0f, 22.8f, 9999, 0, 0);
        preview_values[index]->set_scale(0.95f, 0.95f);
        preview_values[index]->unk3f = 0;
        lib_container_attach_widget(unk10, preview_values[index]);
    }

    func_slot20(0);
    return 1;
}

EquipStatComparisonWindow::~EquipStatComparisonWindow()
{
}

EquipStatComparisonWindow::EquipStatComparisonWindow(EquipController* state)
{
    controller = 0;
    controller = state;
    slot = 0xFF;
    item = 0;
    preview_item = 0;
    unkb2 = 0;
    func_0013A678(&preview_record, 0, sizeof(preview_record));
    func_0013A678(&preview_equipment, 0, sizeof(preview_equipment));
    slot_label = 0;
    item_icon = 0;
    stat_labels[0] = 0;
    arrows[0] = 0;
    current_values[0] = 0;
    preview_values[0] = 0;

    for (s32 i = 1; i < 5; i++)
    {
        stat_labels[i] = 0;
        arrows[i] = 0;
        current_values[i] = 0;
        preview_values[i] = 0;
    }
}

/**
 * @brief Store the category window's selected protected equipment entry and refresh the check word.
 * @param resource Resource record.
 * @param owner Category window holding the selected slot.
 * @param value Record index to store.
 */
static inline void set_protected_equipment_entry(EquipResourceEquipment* resource, const EquipSlotWindow* owner, s32 value)
{
    s32 index = owner->active_slot;

    if (resource->check_word !=
        (resource->check_salt ^ ((resource->encoded_items[1] + resource->encoded_items[2]) ^ (resource->encoded_items[3] + resource->encoded_items[0]))))
    {
        return;
    }

    if (index < 0)
    {
        return;
    }

    if (index <= (resource->encoded_last_slot ^ 0x7E93))
    {
        resource->encoded_items[index] = static_cast<s16>(value) ^ 0x7E93;
        resource->check_word =
            resource->check_salt ^ ((resource->encoded_items[1] + resource->encoded_items[2]) ^ (resource->encoded_items[3] + resource->encoded_items[0]));
    }
}

/**
 * @brief Equip a record in the category window's selected slot.
 * @param window Category window.
 * @param identifier Record index to equip, or zero to clear the slot.
 */
extern "C" void equip_item_in_active_slot(EquipSlotWindow* window, s16 identifier)
{
    if (window->selection != 0)
    {
        func_0040C7E0(
            D_001B64F8,
            protected_equipment_entry(&static_cast<EquipResourceEquipment*>(window->selection->unk04)[window->selection->current], window->active_slot), 0);

        if (identifier)
        {
            func_0040C7E0(D_001B64F8, identifier, window->selection->slots[window->selection->current]);
            set_protected_equipment_entry(&static_cast<EquipResourceEquipment*>(window->selection->unk04)[window->selection->current], window, identifier);
        }
        else
        {
            set_protected_equipment_entry(&static_cast<EquipResourceEquipment*>(window->selection->unk04)[window->selection->current], window, 0);
        }

        FieldRecordSelection* selection = window->controller->selected_records();
        func_003F9890(&selection->records[selection->current], &static_cast<EquipResourceTextRecord*>(selection->unk04)[selection->current], 0, -1);
    }

    refresh_equipment_slots(window);
    s32 category = window->active_slot;

    if (category >= 3)
    {
        category = 2;
    }

    window->item_list->func_slot108(category);
}

void EquipSlotWindow::func_slot6c()
{
    if (static_cast<s16>(func_0023B3B0(equipment_slot_selector, 1)) != 1)
    {
        s16 category = func_0023B3A0(equipment_slot_selector);
        item_list = static_cast<FieldClass15AD40*>(func_slot4c());

        switch (category)
        {
            case 0:
                item_list->func_slot108(0);
                controller->selected_slot = 0;
                break;
            case 1:
                item_list->func_slot108(1);
                controller->selected_slot = 1;
                break;
            case 2:
            case 3:
                item_list->func_slot108(2);
                controller->selected_slot = 2;
                break;
        }
    }
}

void EquipSlotWindow::func_slot68()
{
    if (static_cast<s16>(func_0023B3B0(equipment_slot_selector, 0)) != 1)
    {
        s16 category = func_0023B3A0(equipment_slot_selector);
        item_list = static_cast<FieldClass15AD40*>(func_slot4c());

        switch (category)
        {
            case 0:
                item_list->func_slot108(0);
                controller->selected_slot = 0;
                break;
            case 1:
                item_list->func_slot108(1);
                controller->selected_slot = 1;
                break;
            case 2:
            case 3:
                item_list->func_slot108(2);
                controller->selected_slot = 2;
                break;
        }
    }
}

u8 EquipSlotWindow::func_slotb0()
{
    s32 category = static_cast<u16>(func_0023B3A0(equipment_slot_selector));

    if (usable_slot_count < category)
    {
        return 3;
    }

    if (comparison_window != 0)
    {
        static_cast<EquipStatComparisonWindow*>(comparison_window)->refresh_item_details(category, equipped_items[category]);
        comparison_window->func_slot20(1);
    }

    EquipCharacterWindow* associated = static_cast<EquipCharacterWindow*>(func_slot44());

    if (associated->left_indicator != 0)
    {
        associated->left_indicator->unk3f = 0;
    }

    if (associated->right_indicator != 0)
    {
        associated->right_indicator->unk3f = 0;
    }

    item_list = static_cast<FieldClass15AD40*>(func_slot4c());

    if (active_slot != category)
    {
        s32 next_category = static_cast<u16>(category);

        switch (category)
        {
            case 0:
            case 1:
                break;
            case 2:
            case 3:
                next_category = 2;
                break;
        }

        item_list->func_slot108(next_category);
    }

    item_list->func_slot110(1);
    item_list->func_slot10c(1, 1);
    reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14)->func_00263C70(item_list);
    active_slot = category;
    FieldClass153130* selector = reinterpret_cast<FieldClass153130*>(equipment_slot_selector);
    selector->ItemCreationClass185050::unk30 = 64.0f;
    selector->LibClass178600::unk3c = 1;
    func_slot20(0);
    func_004E97A0(controller->tooltip);
    return 1;
}

u8 EquipSlotWindow::func_slotb4()
{
    if (D_001B643C->unk0c == 0)
    {
        return 0;
    }

    bool active = D_001B643C->unk0c->unk2d != 0;

    if (active == 1)
    {
        set_state(1, 0x80);
    }
    else
    {
        EquipExitConfirmWindow* window = new (0) EquipExitConfirmWindow;

        if (window == 0)
        {
            return 0;
        }

        window->func_slot10(func_slot54(), 200.0f, 160.0f, 13);
        window->func_slot40(this);
        reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->add_child(window);
        reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(window);
    }

    func_004E97A0(controller->tooltip);
    return 2;
}

void EquipSlotWindow::func_slot64()
{
    EquipCharacterWindow* associated = static_cast<EquipCharacterWindow*>(func_slot44());

    if (associated->left_indicator != 0)
    {
        associated->left_indicator->unk3f = 1;
    }

    if (associated->right_indicator != 0)
    {
        associated->right_indicator->unk3f = 1;
    }

    equip_refresh_record_display(associated);
    FieldClass153130* selector = reinterpret_cast<FieldClass153130*>(equipment_slot_selector);
    selector->ItemCreationClass185050::unk30 = 128.0f;
    selector->LibClass178600::unk3c = 1;
}

u8 EquipSlotWindow::func_slotb8()
{
    EquipCharacterWindow* associated = static_cast<EquipCharacterWindow*>(func_slot44());

    if (associated->left_indicator != 0)
    {
        associated->left_indicator->unk3f = 0;
    }

    if (associated->right_indicator != 0)
    {
        associated->right_indicator->unk3f = 0;
    }

    FieldRecord* record = &selection->records[selection->current];
    EquipResourceTextRecord* resource = &static_cast<EquipResourceTextRecord*>(selection->unk04)[selection->current];
    optimize_equipment(controller, record, resource, selection->slots[selection->current]);
    func_003F9890(record, resource, 0, -1);
    func_004E97A0(controller->tooltip);
    refresh_equipment_slots(this);
    s32 category = static_cast<u16>(func_0023B3A0(equipment_slot_selector));

    if (category == 0 || category == 1)
    {
        func_slot44();
        item_list = static_cast<FieldClass15AD40*>(func_slot4c());
        item_list->func_slot108(category);
        item_list->func_slot110(1);
    }

    if (associated->left_indicator != 0)
    {
        associated->left_indicator->unk3f = 1;
    }

    if (associated->right_indicator != 0)
    {
        associated->right_indicator->unk3f = 1;
    }

    return 1;
}

u8 EquipSlotWindow::func_slotbc()
{
    EquipParameterWindow* target = controller->parameter_window;
    target->show_parameters = !target->show_parameters;
    return 1;
}

/** @brief Test whether a selector is inactive. @param selector Selector state. @return One when its control byte is clear. */
static inline u8 selector_inactive(FieldState23B3A0* selector)
{
    return !(selector->unk75 != 0);
}

void EquipSlotWindow::func_slot5c()
{
    if (reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14)->func_00261150() == this)
    {
        u16 selected = func_0023B3A0(equipment_slot_selector);
        EquipPackedRecord* record = packed_record(equipped_items[selected]);

        if (record != 0)
        {
            controller->selected_item_type = static_cast<u16>(packed_record_code(record) + 1);
            const LibUiRect16* position = &item_icons[selected]->unk18;
            s32 x = static_cast<s32>(16.0f + position->unk00);
            s32 y = static_cast<s32>(220.0f + (29.0f + position->unk04));
            u8 inactive = selector_inactive(equipment_slot_selector);

            if (inactive == 0)
            {
                void* tooltip = controller->tooltip;
                func_004E97B0(tooltip, static_cast<float>(x), static_cast<float>(y), 18.0f,
                              lib_allocation_get_identifier(reinterpret_cast<ItemCreationAllocationRecord*>(record)), 0);
            }
            else
            {
                func_004E97A0(controller->tooltip);
            }
        }
        else
        {
            controller->selected_item_type = 0;
            func_004E97A0(controller->tooltip);
        }
    }
}

s32 EquipSlotWindow::func_slotdc()
{
    if (selection == 0)
    {
        return 0;
    }

    func_004E97A0(controller->tooltip);

    if (selection->count > 1)
    {
        EquipController* state = reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14);

        if (state->selection != 0)
        {
            state->selection->active = 0;
            func_0028E2B0(state->selection, 1);
            equip_refresh_record_display(state->character_window);
            refresh_equipment_slots(state->slot_window);
            state->item_list_window->func_slot108(static_cast<u8>(state->selected_slot));
        }

        return 4;
    }

    return 0;
}

s32 EquipSlotWindow::func_slotd8()
{
    if (selection == 0)
    {
        return 0;
    }

    func_004E97A0(controller->tooltip);

    if (selection->count > 1)
    {
        EquipController* state = reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14);

        if (state->selection != 0)
        {
            state->selection->active = 0;
            func_0028E2B0(state->selection, 0);
            equip_refresh_record_display(state->character_window);
            refresh_equipment_slots(state->slot_window);
            state->item_list_window->func_slot108(static_cast<u8>(state->selected_slot));
        }

        return 4;
    }

    return 0;
}

/**
 * @brief Refresh the category window's equipment rows from the selected resource record.
 * @param object Category window.
 */
extern "C" void refresh_equipment_slots(EquipSlotWindow* object)
{
    object->usable_slot_count = static_cast<EquipResourceEquipment*>(object->selection->unk04)[object->selection->current].encoded_slot_count ^ 0x7E93;

    if (object->usable_slot_count >= 4)
    {
        object->usable_slot_count = 4;
    }

    for (s32 index = 0; index < 4; index++)
    {
        object->equipped_items[index] = 0;
        object->slot_labels[index]->set_color(0x505050);
    }

    for (s32 index = 0; index < object->usable_slot_count; index++)
    {
        object->slot_labels[index]->set_color(0x806080);
    }

    for (s32 index = 0; index < object->usable_slot_count; index++)
    {
        object->item_icons[index]->unk3f = 0;
        object->equipped_items[index] =
            protected_equipment_entry(&static_cast<EquipResourceEquipment*>(object->selection->unk04)[object->selection->current], index);

        if (object->equipped_items[index] != 0)
        {
            object->current_item = packed_record(object->equipped_items[index]);
            u16 code = packed_record_code(object->current_item);
            u8 variant = object->current_item->unk0c & 0x7F;
            set_equipment_icon(object->item_icons[index], static_cast<u16>(code) + 1, variant);
            object->item_icons[index]->unk3f = 1;
            object->empty_labels[index]->unk3f = 0;
        }
        else
        {
            object->empty_labels[index]->unk3f = 1;
        }
    }
}

s32 EquipSlotWindow::func_slotf4(u32 associated)
{
    if (selection == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 16.0f, 220.0f, 18);
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* overlay = new (0) ItemCreationClass1746A0;
    lib_scissor_init_rectangle(frame, 12.0f, 12.0f, 270.0f, 224.0f);
    lib_container_attach_widget(unk10, frame);
    row_spacing = 58.0f;

    for (s32 index = 0; index < 4; index++)
    {
        float y = 16.0f + static_cast<float>(index) * row_spacing;
        slot_labels[index] = new (0) LibObject178750;
        lib_text_init_resource_rectangle(static_cast<LibObject178750*>(slot_labels[index]), static_cast<s32>(associated), index + EQUIP_MSG_SLOT_NAME_BASE, 1,
                                         14.0f, y, 0.0f, 0.0f);
        lib_container_attach_widget(unk10, slot_labels[index]);
        slot_labels[index]->set_scale(0.8f, 0.8f);
        slot_labels[index]->set_color(0x806080);
        item_icons[index] = new (0) LibObject172410;
        lib_item_code_init_rectangle(item_icons[index], 12.0f, 38.0f + row_spacing * static_cast<float>(index), 244.0f, 24.0f, 0, 0, 0);
        equip_set_icon_enabled(item_icons[index], 1);
        item_icons[index]->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(unk10, item_icons[index]);
        empty_labels[index] = new (0) LibObject178750;
        lib_text_init_resource_rectangle(static_cast<LibObject178750*>(empty_labels[index]), static_cast<s32>(associated), EQUIP_MSG_NONE, 0, 12.0f,
                                         38.0f + row_spacing * static_cast<float>(index), 284.0f, 24.0f);
        empty_labels[index]->set_scale(0.9f, 0.9f);
        empty_labels[index]->unk3f = 0;
        lib_container_attach_widget(unk10, empty_labels[index]);
    }

    lib_scissor_init_reset(overlay, 1);
    lib_container_attach_widget(unk10, overlay);
    equipment_slot_selector = reinterpret_cast<FieldState23B3A0*>(new (0) FieldClass153130);
    reinterpret_cast<FieldClass153130*>(equipment_slot_selector)->func_0023B530(1, 4, 1, 0, 1, 12.0f, 50.0f, 0.0f, row_spacing);
    lib_container_attach_widget(unk10, reinterpret_cast<FieldClass153130*>(equipment_slot_selector));
    refresh_equipment_slots(this);
    return 1;
}

EquipSlotWindow::EquipSlotWindow(EquipController* state)
{
    controller = 0;
    controller = state;
    unkf4 = 0;

    for (s32 index = 0; index < 4; index++)
    {
        slot_labels[index] = 0;
        item_icons[index] = 0;
        equipped_items[index] = 0;
    }

    row_spacing = 0;
    selection = 0;
    selection = reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14)->selected_records();
    equipment_slot_selector = 0;
    parameter_window = 0;
    current_item = 0;
    usable_slot_count = 0;
    comparison_window = 0;
    active_slot = 0;
    item_list = 0;
}

s32 EquipSlotPanel::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 224.0f, 19);
    LibClass178630* widget = new (0) LibClass178630;
    lib_panel_init_rectangle(widget, 0, 0.0f, 0.0f, 270.0f, 248.0f, 88.0f);
    lib_container_attach_widget(unk10, widget);
    return 1;
}

EquipSlotPanel::~EquipSlotPanel()
{
}

extern "C" void func_0040D2E0(ItemCreationAllocationRecord* record, u16 item_code, u8 modification_number, const u16* factors, bool new_item,
                              bool suppress_allocation_id);

/**
 * @brief Reset a temporary allocation and initialize it from a category record.
 * @param allocation Allocation record to initialize.
 * @param item Category record supplying the catalog index.
 * @param factors Eight factor codes, or null for catalog defaults.
 */
static inline void initialize_equip_allocation(ItemCreationAllocationRecord* allocation, const ItemCreationCategoryRecord* item, const u16* factors)
{
    allocation->reset(0);
    func_0040D2E0(allocation, item->catalog_index + 1, 0, factors, false, true);
}

void EquipParameterWindow::func_slot5c()
{
    EquipController* state = reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14);

    if (state->selected_item_type > 0)
    {
        if (show_parameters != 0)
        {
            description->unk3f = 0;
            title->unk3f = 1;
            ItemCreationAllocationRecord preview __attribute__((aligned(16)));
            preview.reset(0);
            ItemCreationCategoryRecord* item_record = equip_category_record(state->selected_item_type);
            initialize_equip_allocation(&preview, item_record, 0);
            set_number(parameter_values[0], D_001B64F0[preview.definition_index()].attack);
            set_number(parameter_values[1], D_001B64F0[preview.definition_index()].hit);
            set_number(parameter_values[2], D_001B64F0[preview.definition_index()].defense);
            set_number(parameter_values[3], D_001B64F0[preview.definition_index()].agility);
            set_number(parameter_values[4], D_001B64F0[preview.definition_index()].intelligence);

            for (s32 row = 0; row < 5; row++)
            {
                parameter_labels[row]->unk3f = 1;
                separators[row]->unk3f = 1;
                parameter_values[row]->unk3f = 1;
            }
        }
        else
        {
            s32 key = state->selected_item_type + EQUIP_MSG_ITEM_DESCRIPTION_BASE;

            if (key != description_key)
            {
                description->unk3f = 1;
                lib_multiline_text_set_resource(description, func_slot54(), key, 8, 1);
                LibObject174D90* text = description;
                text->unk80 = 0.8f;
                text->unk84 = 0.8f;
                text->unk3c = 1;
            }

            for (s32 row = 0; row < 5; row++)
            {
                parameter_labels[row]->unk3f = 0;
                separators[row]->unk3f = 0;
                parameter_values[row]->unk3f = 0;
            }

            title->unk3f = 0;
        }
    }
    else
    {
        title->unk3f = 0;
        description->unk3f = 0;

        for (s32 row = 0; row < 5; row++)
        {
            parameter_labels[row]->unk3f = 0;
            separators[row]->unk3f = 0;
            parameter_values[row]->unk3f = 0;
        }
    }
}

/** @brief Clear the multiline display scroll offsets. @param display Multiline text display. */
static inline void reset_scroll(LibObject174D90* display)
{
    display->unk52c = 0.0f;
    display->unk524 = 0.0f;
}

s32 EquipParameterWindow::func_slotf4(u32 associated)
{
    if (associated == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 220.0f, 80.0f, 18);
    LibClass178630* panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 404.0f, 145.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    description = new (0) LibObject174D90;
    description->init_multiline_resource_rectangle(32.0f, 13.0f, 362.0f, 140.0f, static_cast<s32>(associated), EQUIP_MSG_CHANGE_HELP, 8, 0);
    reset_scroll(description);
    lib_container_attach_widget(unk10, description);
    description->unk3f = 0;
    title = new (0) LibObject178750;
    title->init_resource_rectangle(40.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_PARAMETER_CHANGES, 0);
    title->set_color(0x806080);
    title->set_scale(0.75f, 0.75f);
    lib_container_attach_widget(unk10, title);
    title->unk3f = 0;

    for (s32 index = 0; index < 5; index++)
    {
        parameter_labels[index] = new (0) LibObject178750;
        float y = 42.0f + 28 * (index / 2);
        parameter_labels[index]->init_resource_rectangle(50.0f + 190 * (index % 2), y, 0.0f, 0.0f, static_cast<s32>(associated),
                                                         EQUIP_MSG_PARAMETER_NAME_BASE + index, 0);
        parameter_labels[index]->set_color(0x805050);
        lib_container_attach_widget(unk10, parameter_labels[index]);
        parameter_labels[index]->unk3f = 0;
        separators[index] = new (0) LibObject178750;
        separators[index]->init_resource_rectangle(100.0f + 190 * (index % 2), y, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_LABEL_SEPARATOR, 0);
        separators[index]->set_color(0x805050);
        lib_container_attach_widget(unk10, separators[index]);
        separators[index]->unk3f = 0;
        parameter_values[index] = new (0) LibObject174F20;
        parameter_values[index]->init_numeric_resource_rectangle(90.0f + 190 * (index % 2), y, 80.0f, 30.0f, 0, static_cast<s32>(associated), 1);
        lib_container_attach_widget(unk10, parameter_values[index]);
        parameter_values[index]->unk3f = 0;
    }

    return 1;
}

void EquipCharacterWindow::show_current_portrait()
{
    s32 selected = 0;
    s32 clear_index = 0;
    FieldRecordSelection* records = selection;
    u16 slot = records->slots[records->current];

    for (; clear_index < 8; clear_index++)
    {
        if (portraits[clear_index])
        {
            portraits[clear_index]->unk3f = 0;
        }
    }

    for (s32 i = 0; i < 8; i++)
    {
        if (slot == portrait_slots[i])
        {
            break;
        }

        selected++;
    }

    if (portraits[selected])
    {
        portraits[selected]->unk3f = 1;
    }
}

void EquipCharacterWindow::func_slot5c()
{
    EquipController* state = reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14);
    FieldClass15AE70* window = state->slot_window;

    if (state->func_00261150() == window)
    {
        optimize_prompt->unk3f = 1;
    }
    else
    {
        optimize_prompt->unk3f = 0;
    }
}

/** @brief Update a resource display string. @param display String display. @param text String to display. */
static inline void set_resource_text(LibObject175140* display, const char* text)
{
    display->unkfc = text;
    display->unk3c = 1;
}

s32 EquipCharacterWindow::func_slotf4(u32 associated)
{
    if (selection == 0)
    {
        return 0;
    }

    character_slot = selection->slots[selection->current];
    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    LibClass178630* panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 232.0f, 144.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    append_panel_widget_node(&unk14, panel);
    name_text = new (0) LibObject175140;
    const char* text = reinterpret_cast<const char*>(static_cast<EquipResourceTextRecord*>(selection->unk04)[selection->current].unk20);
    name_text->func_00467AD0(40.0f, 24.0f, 0.0f, 0.0f, text, 0);
    lib_container_attach_widget(unk10, name_text);
    append_icon_widget_node(&unk44, name_text);
    name_text->set_scale(0.8f, 0.8f);
    level_label = new (0) LibObject178750;
    level_value = new (0) LibObject174F20;
    level_label->init_resource_rectangle(120.0f, 48.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_LEVEL, 0);
    level_value->init_numeric_resource_rectangle(170.0f, 48.0f, 42.0f, 24.0f, equip_record_value(&selection->records[selection->current]), 0, 0);
    lib_container_attach_widget(unk10, level_label);
    append_text_widget_node(&unk2c, level_label);
    level_label->set_color(0x806080);
    lib_container_attach_widget(unk10, level_value);
    append_stat_value_node(&unk38, level_value);
    level_value->set_scale(0.9f, 0.9f);
    optimize_prompt = new (0) LibObject178750;
    optimize_prompt->init_resource_rectangle(105.0f, 80.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_OPTIMIZE_PROMPT, 0);
    optimize_prompt->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, optimize_prompt);
    switch_prompt = new (0) LibObject178750;
    switch_prompt->init_resource_rectangle(105.0f, 110.0f, 0.0f, 0.0f, static_cast<s32>(associated), EQUIP_MSG_SWITCH_PROMPT, 0);
    switch_prompt->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, switch_prompt);

    if (selection->count > 1)
    {
        left_indicator = new (0) ItemCreationClass174C40;
        right_indicator = new (0) ItemCreationClass174C40;
        lib_indexed_resource_init(left_indicator, 10, 8.0f, 8.0f);
        lib_indexed_resource_init(right_indicator, 11, 196.0f, 8.0f);
        left_indicator->set_scale(0.9f, 0.9f);
        right_indicator->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(unk10, left_indicator);
        lib_container_attach_widget(unk10, right_indicator);
    }

    FieldListNode* node = unk2c.head->next;

    while (node != 0)
    {
        static_cast<LibObject178750*>(node->value)->set_scale(0.9f, 0.9f);
        node = node->next;
    }

    for (s32 index = 0; index < 8; index++)
    {
        u16 slot = static_cast<u16>(selection->slots[static_cast<s16>(index)]);

        if (slot != 0)
        {
            portrait_slots[index] = slot;
            portraits[index] = new (0) ItemCreationOptionResourceDisplay;
            void* allocation = field_get_aligned_allocation(D_001B643C->unk20, static_cast<u8>(slot));
            FieldResourceRecord* record = field_find_resource_record(D_001B643C->unk20, 4);
            portraits[index]->unkcc = allocation;
            portraits[index]->unkd0 = slot;
            portraits[index]->func_002D6440(record, 20.0f, 50.0f);
            portraits[index]->unk3f = 0;
            lib_container_attach_widget(unk10, portraits[index]);
        }
    }

    if (selection != 0)
    {
        set_resource_text(name_text, reinterpret_cast<const char*>(static_cast<EquipResourceTextRecord*>(selection->unk04)[selection->current].unk20));
        set_number(level_value, equip_record_value(&selection->records[selection->current]));
        show_current_portrait();
    }

    return 1;
}

EquipCharacterWindow::EquipCharacterWindow()
{
    character_slot = 0;
    selection = 0;
    selection = reinterpret_cast<EquipController*>(D_001B643C->unk10->unk14)->selected_records();
    level_label = 0;
    level_value = 0;
    left_indicator = 0;
    right_indicator = 0;

    for (s32 i = 0; i < 8; i++)
    {
        portraits[i] = 0;
        portrait_slots[i] = 0;
    }
}

/** @brief Set an allocation record selection and update its category. @param state Resident allocation storage. @param identifier One-based record identifier.
 * @param mode Selection value whose low four bits are stored. @return One when the record was updated, or zero for an invalid record. */

/** Field record copy layout, with scalar statistics followed by a fifteen-word array. */
struct EquipRecordCopyView
{
    s16 unk00;

    s16 unk02;

    s16 unk04;

    s16 unk06;

    s32 unk08;

    s32 unk0c;

    s32 unk10;

    s32 unk14;

    s32 unk18;

    s32 unk1c;

    s32 unk20;

    s32 unk24;

    float unk28;

    float unk2c;

    float unk30;

    s32 unk34;

    s32 unk38;

    s32 unk3c;

    s32 unk40;

    s32 unk44;

    s32 unk48;

    s32 unk4c;

    s32 unk50;

    s32 unk54;

    s32 unk58;

    s32 unk5c;

    s32 unk60;

    s32 unk64;

    s32 unk68;

    s32 unk6c;

    s16 unk70;

    s16 unk72;

    s16 unk74;

    s16 unk76;

    s16 unk78;

    s16 unk7a;

    s16 unk7c;

    s16 unk7e;

    s16 unk80;

    s32 unk84[15];

    s32 unkc0;
};

/** Two signed bytes copied together in a resource array. */
struct EquipBytePair
{
    s8 a, b;
};

/** Two signed halfwords copied together in a resource array. */
struct EquipShortPair
{
    s16 a, b;
};

/** Four protected equipment identifiers stored consecutively. */
struct EquipShortFour
{
    s16 a, b, c, d;
};

/** Four byte values copied as one resource field. */
struct EquipByteFour
{
    u8 a, b, c, d;
};

/** Ten floats copied as one resource field; checksum views also read two words. */
struct EquipFloatTen
{
    float a, b, c, d, e, f, g, h, i, j;
};

/** Resource copy layout containing equipment identifiers, paired arrays, and float values. */
struct EquipResourceCopyView
{
    s16 unk00, unk02, unk04, unk06, unk08, unk0a, unk0c, unk0e;

    EquipShortFour unk10;

    s16 unk18, unk1a;

    s32 unk1c;

    EquipBytePair unk20[12];

    u8 unk38, unk39, unk3a, unk3b;

    s8 unk3c[5];

    EquipBytePair unk41[3];

    s8 unk47[7];

    EquipShortPair unk4e[16], unk8e[21];

    EquipByteFour unke2;

    u8 unke6, unke7;

    EquipFloatTen unke8;

    s32 unk110;
};

/** @brief Find an allocation record in resident storage. @param value Signed halfword record index. @return Record, or null outside one through three thousand.
 */
static inline ItemCreationAllocationRecord* equip_allocation_record(s32 value)
{
    ResidentObject1B64F8* base = D_001B64F8;
    s16 index = value;
    bool valid = false;

    if (index > 0 && index <= 3000)
    {
        valid = true;
    }

    if (valid)
    {
        return reinterpret_cast<ItemCreationAllocationRecord*>(reinterpret_cast<u8*>(base) + (index - 1) * 16);
    }

    return 0;
}

/** @brief Decode a protected statistic after validating its check word. @param first First summand. @param second Second summand. @param value Encoded
 * statistic. @param check Stored check word. @param salt Record salt. @return Decoded statistic, or zero for an invalid check word. */
static inline s32 equip_checked_statistic(s32 first, s32 second, s32 value, s32 check, s32 salt)
{
    if (check != (salt ^ (value ^ (first + second))))
    {
        return 0;
    }

    return value ^ 0x7DE3F7E3;
}

/** @brief Read the first protected statistic. @param r Copied field record. @return Decoded value, or zero for an invalid check word. */
static inline s32 equip_first_statistic(const EquipRecordCopyView& r)
{
    return equip_checked_statistic(r.unk34, r.unk38, r.unk3c, r.unk84[4], r.unk84[9]);
}

/** @brief Read the second protected statistic. @param r Copied field record. @return Decoded value, or zero for an invalid check word. */
static inline s32 equip_second_statistic(const EquipRecordCopyView& r)
{
    return equip_checked_statistic(r.unk40, r.unk44, r.unk48, r.unk84[5], r.unk84[9]);
}

/** Integer view of the resource equipment identifiers, bound, check word, and salt. */
struct EquipProtectedResourceView
{
    u8 unk00[0xE];

    s16 count;

    EquipShortFour values;

    u8 unk18[0xD8];

    u32 check;

    u8 unkf4[0x18];

    u32 salt;
};

/** @brief Calculate the equipment identifier check word. @param object Resource record. @return Check word calculated from its four identifiers and salt. */
static inline s32 equip_resource_checksum(const void* object)
{
    const EquipProtectedResourceView* r = static_cast<const EquipProtectedResourceView*>(object);
    return r->salt ^ ((r->values.b + r->values.c) ^ (r->values.d + r->values.a));
}

/** @brief Check a resource equipment index. @param index Requested index. @param count Decoded inclusive bound. @return True when the index is within the
 * bound. */
static inline bool equip_valid_equipment_index(s32 index, s32 count)
{
    return index >= 0 && index <= count;
}

/** @brief Validate the equipment identifier check word. @param r Resource record view. @return True when its check word agrees with its identifiers and salt.
 */
static inline bool equip_resource_valid(const EquipProtectedResourceView* r)
{
    return r->check == (r->salt ^ ((r->values.b + r->values.c) ^ (r->values.d + r->values.a)));
}

/** @brief Read a protected equipment identifier. @param object Resource record. @param index Equipment index. @return Decoded identifier, or zero for an
 * invalid checksum or index. */
static inline s16 equip_equipped(const void* object, s32 index)
{
    const EquipProtectedResourceView* r = static_cast<const EquipProtectedResourceView*>(object);

    if (!equip_resource_valid(r))
    {
        return 0;
    }

    if (!equip_valid_equipment_index(index, r->count ^ 0x7E93))
    {
        return 0;
    }

    return reinterpret_cast<const s16*>(&r->values)[index] ^ 0x7E93;
}

/** @brief Update a valid protected equipment identifier and its check word. @param object Resource record. @param index Equipment index. @param value
 * Replacement identifier. */
static inline void equip_set_equipped(void* object, s32 index, s16 value)
{
    EquipProtectedResourceView* r = static_cast<EquipProtectedResourceView*>(object);

    if (equip_resource_valid(r) && equip_valid_equipment_index(index, r->count ^ 0x7E93))
    {
        reinterpret_cast<s16*>(&r->values)[index] = value ^ 0x7E93;
        r->check = equip_resource_checksum(r);
    }
}

/** @brief Select available allocations that improve the first two protected statistics. @param state Unused state receiver. @param record Field record used for
 * each trial. @param resource Resource equipment identifiers to update. @param slot Equipment selection slot. */
extern "C" void optimize_equipment(EquipController* state, FieldRecord* record, EquipResourceTextRecord* resource, s8 slot)
{
    const EquipRecordCopyView* original = reinterpret_cast<const EquipRecordCopyView*>(record);
    EquipResourceCopyView* original_resource = reinterpret_cast<EquipResourceCopyView*>(resource);
    ItemCreationAllocationRecord* candidates[100];
    EquipRecordCopyView copy;
    EquipResourceCopyView copy_resource;
    ItemCreationAllocationRecord* best_first = 0;
    ItemCreationAllocationRecord* best_second = 0;
    s32 max_first = 0;
    s32 max_second = 0;
    s32 category;
    s32 count_first;
    s32 index_first;
    s32 count_second;
    s32 index_second;
    s32 mask = 1 << (slot - 1);

    for (category = 1; category <= 750; ++category)
    {
        ItemCreationCategoryRecord* entry = equip_category_record(category);

        if (entry && entry->inventory_count > 0)
        {
            const EquipCategoryMaskView* definition =
                reinterpret_cast<const EquipCategoryMaskView*>(reinterpret_cast<const u8*>(D_001B64F0) + entry->catalog_index * 32);

            if (mask & static_cast<u16>(definition->mask))
            {
                switch (static_cast<u8>(definition->mode))
                {
                    case 0:
                    {
                        count_first = lib_collect_unequipped_allocations(D_001B64F8, candidates, category);

                        for (index_first = 0; index_first < count_first; ++index_first)
                        {
                            copy = *original;
                            copy_resource = *original_resource;
                            func_003F9890(reinterpret_cast<FieldRecord*>(&copy), reinterpret_cast<EquipResourceTextRecord*>(&copy_resource),
                                          reinterpret_cast<u32>(candidates[index_first]), 0);

                            if (!best_first || max_first < equip_first_statistic(copy))
                            {
                                best_first = candidates[index_first];
                                max_first = equip_first_statistic(copy);
                            }
                        }

                        break;
                    }
                    case 1:
                    {
                        count_second = lib_collect_unequipped_allocations(D_001B64F8, candidates, category);

                        for (index_second = 0; index_second < count_second; ++index_second)
                        {
                            copy = *original;
                            copy_resource = *original_resource;
                            func_003F9890(reinterpret_cast<FieldRecord*>(&copy), reinterpret_cast<EquipResourceTextRecord*>(&copy_resource),
                                          reinterpret_cast<u32>(candidates[index_second]), 1);

                            if (!best_second || max_second < equip_second_statistic(copy))
                            {
                                best_second = candidates[index_second];
                                max_second = equip_second_statistic(copy);
                            }
                        }

                        break;
                    }
                }
            }
        }
    }

    copy = *original;
    copy_resource = *original_resource;
    func_003F9890(reinterpret_cast<FieldRecord*>(&copy), reinterpret_cast<EquipResourceTextRecord*>(&copy_resource), 0, -1);

    if (best_first)
    {
        s16 current = equip_equipped(original_resource, 0);

        if (current)
        {
            if (equip_allocation_record(current) && equip_first_statistic(copy) < max_first)
            {
                func_0040C7E0(D_001B64F8, current, 0);
                func_0040C7E0(D_001B64F8, lib_allocation_get_identifier(best_first), slot);
                equip_set_equipped(original_resource, 0, lib_allocation_get_identifier(best_first));
            }
        }
        else
        {
            func_0040C7E0(D_001B64F8, lib_allocation_get_identifier(best_first), slot);
            equip_set_equipped(original_resource, 0, lib_allocation_get_identifier(best_first));
        }
    }

    if (best_second)
    {
        s16 current = equip_equipped(original_resource, 1);

        if (current)
        {
            if (equip_allocation_record(current) && equip_second_statistic(copy) < max_second)
            {
                func_0040C7E0(D_001B64F8, current, 0);
                func_0040C7E0(D_001B64F8, lib_allocation_get_identifier(best_second), slot);
                equip_set_equipped(original_resource, 1, lib_allocation_get_identifier(best_second));
            }
        }
        else
        {
            func_0040C7E0(D_001B64F8, lib_allocation_get_identifier(best_second), slot);
            equip_set_equipped(original_resource, 1, lib_allocation_get_identifier(best_second));
        }
    }
}

void EquipController::func_slot5c()
{
    LibObject178660* container = static_cast<LibObject178660*>(tooltip);

    if (container != 0)
    {
        static_cast<LibClass174610&>(*container).func_003EF740();
    }

    if (resource_slot != 0)
    {
        lib_release_resource_slot(D_001B657C, resource_slot);
    }

    lib_object_detach_owner(this);
    func_001DD7B0();
}

/** @brief Submit the State to the resident object queue. */
void EquipController::func_001DD7B0()
{
    resident_enqueue_object(D_001B65F4, this);
}

/** @brief Default update handler that performs no work. */
void FieldListObject::update()
{
}

/**
 * @brief Attach the detail and comparison windows.
 * @param object Category window.
 * @param detail Category detail window.
 * @param comparison Item comparison window.
 */
static inline void attach_comparison(EquipSlotWindow* object, EquipParameterWindow* detail, EquipStatComparisonWindow* comparison)
{
    object->parameter_window = detail;
    object->comparison_window = comparison;
}

s32 EquipController::init_windows()
{
    EquipRuntimeResource* runtime = reinterpret_cast<EquipRuntimeResource*>(D_001B657C);
    runtime->unk51c = resource_slot;
    runtime->unk520 = 0x11171;
    tooltip = new (0) EquipClass1796F0;

    if (tooltip != 0)
    {
        func_004E9BC0(static_cast<EquipClass1796F0*>(tooltip));
        lib_queue_display_object(D_001B657C, static_cast<EquipClass1796F0*>(tooltip));
    }

    EquipResourceWindow* options = new (0) EquipResourceWindow;
    EquipHelpWindow* scrolling = new (0) EquipHelpWindow;
    character_window = new (0) EquipCharacterWindow;
    parameter_window = new (0) EquipParameterWindow;
    slot_window = new (0) EquipSlotWindow(this);
    EquipSlotPanel* panel = new (0) EquipSlotPanel;
    comparison_window = new (0) EquipStatComparisonWindow(this);
    item_list_panel = new (0) EquipItemListPanel;
    item_list_window = new (0) EquipItemListWindow(this);
    options->func_slotf4(resource_slot);
    FieldClass153E30::add_child(options);
    options->func_slot40(scrolling);
    scrolling->func_slotf4(resource_slot);
    FieldClass153E30::add_child(scrolling);
    scrolling->func_slot40(0);
    panel->func_slotf4(resource_slot);
    FieldClass153E30::add_child(panel);
    parameter_window->func_slotf4(resource_slot);
    FieldClass153E30::add_child(parameter_window);
    character_window->func_slotf4(resource_slot);
    FieldClass153E30::add_child(character_window);
    attach_comparison(slot_window, parameter_window, comparison_window);
    slot_window->func_slot48(item_list_window);
    slot_window->func_slotf4(resource_slot);
    FieldClass153E30::add_child(slot_window);
    slot_window->func_slot40(character_window);
    comparison_window->func_slotf4(resource_slot);
    FieldClass153E30::add_child(comparison_window);
    item_list_panel->func_slotf4(resource_slot);
    FieldClass153E30::add_child(item_list_panel);
    item_list_window->func_slot40(slot_window);
    item_list_window->comparison_window = comparison_window;
    item_list_window->func_slot104(resource_slot);
    FieldClass153E30::add_child(item_list_window);
    unk20 = slot_window;
    windows_initialized = 1;
    return 1;
}

EquipClass1797B0::~EquipClass1797B0()
{
}

LibClass178A70::~LibClass178A70()
{
}

s32 EquipController::on_resource_loaded(void* buffer)
{
    if (buffer == 0)
    {
        return 0;
    }

    EquipAlignedResource* aligned = aligned_resource(buffer);
    s32 size = aligned->unk40 + 0x80;
    void* saved_heap = resident_get_allocation_heap();
    void* heap = D_001B6430->context->unk70;
    void* memory = resident_heap_allocate(heap, size);

    if (memory != 0)
    {
        resident_heap_release(memory);
        resident_exchange_allocation_heap(heap);
    }

    resource_slot = lib_load_resource_slot(D_001B657C, aligned);
    resident_exchange_allocation_heap(saved_heap);
    EquipRuntimeResource* runtime = reinterpret_cast<EquipRuntimeResource*>(D_001B657C);
    runtime->unk514 = resource_slot;
    runtime->unk518 = 0xC351;
    return init_windows();
}

/**
 * @brief Allocate and initialize the State's record selection.
 * @return One when a selection exists and initialization succeeds; otherwise zero.
 */
u8 EquipController::func_00264110()
{
    selection = new (0) FieldRecordSelection;
    u8 result = func_0028E3D0(selection);

    if (selection == 0 || result == 0)
    {
        return 0;
    }

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

/** @brief Release the record selection before destroying the Field list base. */
EquipController::~EquipController()
{
    if (selection != 0)
    {
        release_owned(selection);
    }
}

/** @brief Initialize the equipment State and its resource table entries. */
EquipController::EquipController()
{
    resource_slot = 0;
    selection = 0;
    windows_initialized = 0;
    character_window = 0;
    slot_window = 0;
    item_list_panel = 0;
    comparison_window = 0;
    item_list_window = 0;
    parameter_window = 0;
    selected_item_type = 0;
    unk58 = 0;
    unk5c = 0;
    void* table = resident_get_entry_table(resident_get_runtime_owner());
    unk58 = resident_find_entry(table, 2);
    unk5c = resident_find_entry(table, 3);
    selected_slot = 0;
    tooltip = 0;
}

/** @brief Default handler that performs no work. */
void FieldListObject::func_001DD410()
{
}

void ItemCreationClass185050::func_slot0c()
{
}

void FieldClass15AE70::func_slot68()
{
}

void FieldClass15AE70::func_slot6c()
{
}

u8 FieldClass15AE70::func_slotb0()
{
    return 0;
}

u8 FieldClass15AE70::func_slotb4()
{
    return 0;
}

void FieldClass15AE70::func_slot5c()
{
}

EquipItemInstanceListWindow::~EquipItemInstanceListWindow()
{
}

EquipItemListWindow::~EquipItemListWindow()
{
}

EquipSlotWindow::~EquipSlotWindow()
{
}

EquipParameterWindow::~EquipParameterWindow()
{
}

EquipCharacterWindow::~EquipCharacterWindow()
{
}

/** @brief Report whether window setup finished. @return Setup flag. */
u8 EquipController::windows_ready()
{
    return windows_initialized;
}

/** @brief Report this object's default list kind. @return Four. */
s32 EquipController::get_default_list_kind()
{
    return 4;
}

/** @brief Store the alternate associated object. @param value Object to store. */
void FieldClass153E30::func_00263C80(void* value)
{
    unk24 = value;
}

/** @brief Return the alternate associated object. @return Stored object. */
void* FieldClass153E30::func_00263C90()
{
    return unk24;
}

/** @brief Store the receiver state byte. @param value State byte. */
void FieldClass153E30::func_00263CA0(s8 value)
{
    unk28 = value;
}

/** @brief Return the receiver state byte. @return State byte. */
s8 FieldClass153E30::func_00263CB0()
{
    return unk28;
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot60()
{
    return 0;
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot64()
{
    return 0;
}

/** @brief Run the empty receiver hook. */
void FieldClass153E30::func_slot68()
{
}

/** @brief Run the empty receiver hook. */
void FieldClass153E30::func_slot70()
{
}

/** @brief Run the empty receiver hook. */
void FieldClass153E30::func_slot74()
{
}

/** @brief Run the empty receiver hook. */
void FieldClass153E30::func_slot78()
{
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot7c()
{
    return 0;
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot80()
{
    return 0;
}

/** @brief Return the default receiver result. @return Zero. */
s32 FieldClass153E30::func_slot84()
{
    return 0;
}

EquipNewItemTypeList::EquipNewItemTypeList()
{
    head = new (0) EquipNewItemTypeNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

EquipNewItemTypeList::~EquipNewItemTypeList()
{
    clear_new_item_types(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void append_new_item_type(EquipNewItemTypeList* list, u16 value)
{
    EquipNewItemTypeNode* node;
    EquipNewItemTypeNode* cursor;
    node = new (0) EquipNewItemTypeNode;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;

        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }

        cursor->next = node;
        list->count++;
    }
}

void clear_new_item_types(EquipNewItemTypeList* list)
{
    EquipNewItemTypeNode* node = list->head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        EquipNewItemTypeNode* next = node->next;
        delete node;
        node = next;
    }

    list->head->next = 0;
    list->count = 0;
}

void* get_new_item_type_node(void* object, s32 count)
{
    EquipNewItemTypeNode* node = ((EquipNewItemTypeList*)object)->head->next;
    s32 index = 0;

    while (index < count)
    {
        if (node == 0)
        {
            return 0;
        }

        index++;
        node = node->next;
    }

    return node;
}

EquipItemTypeList::EquipItemTypeList()
{
    head = new (0) EquipItemTypeNode;

    if (head == 0)
    {
        throw;
    }

    head->next = 0;
    count = 0;
}

EquipItemTypeList::~EquipItemTypeList()
{
    clear_item_types(this);

    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

/**
 * @brief Append a category-record pointer to the list.
 * @param list List to update.
 * @param value Category-record pointer, which may be null.
 */
void append_item_type(EquipItemTypeList* list, ItemCreationCategoryRecord* value)
{
    EquipItemTypeNode* node;
    EquipItemTypeNode* cursor;
    node = new (0) EquipItemTypeNode;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;

        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }

        cursor->next = node;
        list->count++;
    }
}

void clear_item_types(EquipItemTypeList* list)
{
    EquipItemTypeNode* node = list->head->next;

    if (node == 0)
    {
        return;
    }

    while (node != 0)
    {
        EquipItemTypeNode* next = node->next;
        delete node;
        node = next;
    }

    list->head->next = 0;
    list->count = 0;
}

void* get_item_type_node(void* object, s32 count)
{
    EquipItemTypeNode* node = ((EquipItemTypeList*)object)->head->next;
    s32 index = 0;

    while (index < count)
    {
        if (node == 0)
        {
            return 0;
        }

        index++;
        node = node->next;
    }

    return node;
}

void append_grid_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node;
    FieldListNode* cursor;
    node = new (0) FieldListNode;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;

        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }

        cursor->next = node;
        list->count++;
    }
}

void append_icon_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node;
    FieldListNode* cursor;
    node = new (0) FieldListNode;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;

        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }

        cursor->next = node;
        list->count++;
    }
}

void append_stat_value_node(FieldCountedList* list, void* value)
{
    FieldListNode* node;
    FieldListNode* cursor;
    node = new (0) FieldListNode;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;

        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }

        cursor->next = node;
        list->count++;
    }
}

void append_text_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node;
    FieldListNode* cursor;
    node = new (0) FieldListNode;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;

        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }

        cursor->next = node;
        list->count++;
    }
}

void append_clip_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node;
    FieldListNode* cursor;
    node = new (0) FieldListNode;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;

        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }

        cursor->next = node;
        list->count++;
    }
}

void append_panel_widget_node(FieldCountedList* list, void* value)
{
    FieldListNode* node;
    FieldListNode* cursor;
    node = new (0) FieldListNode;

    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        cursor = list->head;

        while (cursor->next != 0)
        {
            cursor = cursor->next;
        }

        cursor->next = node;
        list->count++;
    }
}
