#include "include_asm.h"
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
        struct { u16 value : 10; u16 other : 6; } bits;
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
extern "C" void func_0034F2A0(EquipListState* state, FieldRecord* record, EquipResourceTextRecord* resource, s8 slot);
extern "C" void func_003F9890(FieldRecord* record, EquipResourceTextRecord* resource, u32 flag, s32 index);
extern "C" void func_0034D4C0(EquipClass182990* object);
extern "C" void func_0034B3D0(EquipClass182890* window, s16 selected);
extern "C" void func_0034C540(EquipClass182990* object, s16 identifier);
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
/** @brief Queue a nonnull window on the menu context. @param context Menu context. @param window Window to queue. */

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
    if (resource->unkf0 != (resource->unk10c ^ ((resource->unk10[1] + resource->unk10[2]) ^ (resource->unk10[3] + resource->unk10[0]))))
    {
        return 0;
    }
    if (index < 0)
    {
        return 0;
    }
    if ((resource->unk0e ^ 0x7E93) < index)
    {
        return 0;
    }
    return static_cast<s16>(resource->unk10[index] ^ 0x7E93);
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
/** @brief Decode a field record display code after validating its check word. @param record Selected field record. @return Decoded code, or one when validation fails. */
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
static inline void equip_refresh_record_display(EquipClass182C90* associated)
{
    if (associated->unkac != 0)
    {
        LibObject175140* text = associated->unkb0;
        text->unkfc = reinterpret_cast<const char*>(static_cast<EquipResourceTextRecord*>(associated->unkac->unk04)[associated->unkac->current].unk20);
        text->unk3c = 1;
        FieldRecord* record = &associated->unkac->records[associated->unkac->current];
        s32 result = equip_record_value(record);
        LibObject174F20* number = associated->unkb8;
        number->numeric_value = result;
        number->unk3c = 1;
        associated->refresh_slot_marker();
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
        valid = true;
    if (valid)
        return &base->item_types[index - 1];
    return 0;
}

struct EquipCategoryNode
{
    EquipCategoryRecord* value;
    EquipCategoryNode* next;
};


typedef struct EquipLinkedNode
{
    u16 value;
    u8 pad_02[2];
    struct EquipLinkedNode* next;
    /** @brief Destroy the node without releasing its stored value. */
    ~EquipLinkedNode()
    {
    }
} EquipLinkedNode;

typedef struct EquipWordNode
{
    ItemCreationCategoryRecord* value;
    struct EquipWordNode* next;
    /** @brief Destroy the node without releasing its stored value. */
    ~EquipWordNode()
    {
    }
} EquipWordNode;


static inline void equip_set_position(LibClass178600* target, float x, float y, float z, float w);


/**
 * @brief Copy the scalar position and mark the display receiver for refresh.
 * @param target Display receiver to update.
 * @param x Horizontal position component.
 * @param y Vertical position component.
 * @param z Third position component.
 * @param w Fourth position component.
 */
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
/** @brief Decode one of the first four protected statistics. @param record Character record statistics. @param index Statistic index. @return Decoded value, or zero for an invalid checksum. */
static inline u32 stat_value(const EquipRecordStats* record, s32 index)
{
    u32 value = record->unk34[index][1];
    if (record->unk94[index] != (record->unka8 ^ (record->unk34[index][2] ^ (record->unk34[index][0] + value))))
    {
        return 0;
    }
    return value ^ 0x7DE3F7E3;
}
/** @brief Decode the final statistic using the fourth statistic checksum. @param record Character record statistics. @return Decoded value, or zero for an invalid checksum. */
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

void EquipClass182220::func_slotf4(s16 selected)
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

void EquipClass182220::func_slot5c()
{
    if (reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14)->func_00261150() == this)
    {
        func_slotf4(unka8->unk114);
    }
}

/** @brief Return the stored window pointer. @return Stored pointer. */
void* FieldClass153E30::func_00261150()
{
    return unk20;
}

void EquipClass182220::func_slot6c()
{
    if (static_cast<s16>(unka8->process_direction(1)) == 1)
    {
        return;
    }
}

void EquipClass182220::func_slot68()
{
    if (static_cast<s16>(unka8->process_direction(0)) == 1)
    {
        return;
    }
}

u8 EquipClass182220::func_slotb4()
{
    FieldClass15AE70::func_slot18(0, 0x7F);
    EquipListState* state = reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14);
    state->func_00263C70(func_slot44());
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    return 2;
}

/** @brief Store the window pointer. @param value Pointer to store. */
void FieldClass153E30::func_00263C70(void* value)
{
    unk20 = value;
}

u8 EquipClass182220::func_slotb0()
{
    unkac = unka8->unk114;
    u8 result = 0;
    if (unkac == 0)
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

s32 EquipClass182220::func_slot10(u32 associated, float x, float y, s32 code)
{
    FieldClass15AE70::func_slot10(associated, x, y, code);
    LibClass178630* frame = new (0) LibClass178630;
    if (frame == 0)
    {
        return 0;
    }
    lib_panel_init_rectangle(frame, 1, 0.0f, 0.0f, 240.0f, 160.0f, 88.0f);
    lib_container_attach_widget(unk10, frame);
    func_00351E40(&unk14, frame);
    LibObject178750* first = new (0) LibObject178750;
    LibObject178750* second = new (0) LibObject178750;
    LibObject178750* title = new (0) LibObject178750;
    unka8 = new (0) FieldObject23CEA0;
    if (first == 0 || second == 0 || title == 0 || unka8 == 0)
    {
        return 0;
    }
    first->init_resource_rectangle(84.0f, 84.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x7E8, 0);
    second->init_resource_rectangle(84.0f, 120.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x7E9, 0);
    title->init_resource_rectangle(24.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0xFAC, 0);
    lib_container_attach_widget(unk10, first);
    lib_container_attach_widget(unk10, second);
    lib_container_attach_widget(unk10, title);
    func_00351D20(&unk2c, first);
    func_00351D20(&unk2c, second);
    func_00351D20(&unk2c, title);
    unka8->func_0023CE80(1, 2);
    unka8->func_0023CE60(0.0f, 36.0f);
    unka8->unkF2 = 0;
    unka8->func_0023CF50(1, 84.0f + x, 16.0f + (84.0f + y));
    func_00351B70(&unk74, unka8);
    return 1;
}

EquipClass182220::~EquipClass182220()
{
}

void EquipClass182350::func_slot5c()
{
    LibClass178600* target = unka8;
    float x = target->unk18.unk00;
    float y = target->unk18.unk04;
    float z = target->unk18.unk08;
    float w = target->unk18.unk0c;
    if (unkb4 == 0)
    {
        equip_set_position(target, unkbc, y, z, w);
        unkb2++;
        if (!((float)unkb2 <= 120.0f))
        {
            unkb2 = 0;
            unkb4 = 1;
        }
        return;
    }
    x -= 108.0f * D_001B6690;
    if (x < unkc0 - (float)unkac)
    {
        x = 2.0f + (unkc0 + unkc4);
    }
    equip_set_position(target, x, y, z, w);
}

void EquipClass182350::func_slot60(s32 text_key)
{
    if (text_key >= 0xFAE && text_key < 0xFAF)
    {
        unkb2 = 0;
        unkb4 = 0;
        lib_text_set_resource(unka8, func_slot54(), text_key, 1);
        unkac = static_cast<s32>(lib_text_measure_bounds(unka8)->unk08) + 6;
    }
}

s32 EquipClass182350::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 19);
    unka8 = new (0) LibObject178750;
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* overlay = new (0) ItemCreationClass1746A0;
    if (unka8 == 0 || frame == 0 || overlay == 0)
    {
        return 0;
    }
    LibObject178750* title = new (0) LibObject178750;
    title->init_resource_rectangle(16.0f, 6.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0xFA0, 0);
    lib_container_attach_widget(unk10, title);
    func_00351D20(&unk2c, title);
    LibObject178750* label = new (0) LibObject178750;
    label->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0xFAF, 0);
    label->set_scale(0.65f, 0.65f);
    lib_container_attach_widget(unk10, label);
    func_00351D20(&unk2c, label);
    unkb8 = lib_text_measure_bounds(title)->unk08;
    unkc0 = 18.0f + unkb8;
    float right_margin = 32.0f;
    unkc4 = 640.0f - (16.0f + (unkc0 + right_margin));
    unkbc = 24.0f + unkb8;
    lib_scissor_init_rectangle(frame, unkc0, 0.0f, unkc4, 56.0f);
    lib_container_attach_widget(unk10, frame);
    func_00351DB0(&unk20, frame);
    unka8->init_resource_rectangle(unkbc, 6.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0xFAE, 0);
    lib_container_attach_widget(unk10, unka8);
    func_00351D20(&unk2c, unka8);
    lib_scissor_init_reset(overlay, 1);
    lib_container_attach_widget(unk10, overlay);
    func_00351DB0(&unk20, overlay);
    func_slot60(0xFAE);
    return 1;
}

EquipClass182350::~EquipClass182350()
{
}

s32 EquipClass182450::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 20);
    unka8 = new (0) ItemCreationOptionResourceDisplay;
    unkac = new (0) ItemCreationOptionResourceDisplay;
    unkb0 = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = field_get_aligned_allocation(D_001B643C->unk20, 11);
    unka8->unkcc = allocation;
    unkac->unkcc = allocation;
    unkb0->unkcc = allocation;
    unka8->unkd0 = 11;
    unkac->unkd0 = 11;
    unkb0->unkd0 = 11;
    unka8->func_002D6440(field_find_resource_record(D_001B643C->unk20, 5), 0.0f, 0.0f);
    unkac->func_002D6440(field_find_resource_record(D_001B643C->unk20, 6), 256.0f, 0.0f);
    unkb0->func_002D6440(field_find_resource_record(D_001B643C->unk20, 7), 512.0f, 0.0f);
    lib_container_attach_widget(unk10, unka8);
    lib_container_attach_widget(unk10, unkac);
    lib_container_attach_widget(unk10, unkb0);
    return 1;
}

ItemCreationClass175110::~ItemCreationClass175110()
{
}

EquipClass182450::~EquipClass182450()
{
}

/** @brief Write a stored display flag. @param display Display to update. @param flag Low-byte flag to store. */
static inline void set_visibility(LibClass178600* display, const u8& flag)
{
    display->unk3f = flag;
}
void EquipClass182550::func_slot10c(u32 value, u32 enabled)
{
    s32 index;
    u8 flag = value;
    for (index = 0; index < 9; index++)
    {
        set_visibility(unk15c[index], flag);
        set_visibility(unk138[index], flag);
    }
    if (unk180 != 0)
    {
        set_visibility(unk180, flag);
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
u8 EquipClass182550::func_slotb8()
{
    return 0;
}

/** @brief Toggle the linked display flag. @return One. */
u8 EquipClass182550::func_slotbc()
{
    EquipClass182B90* target = unk188->unk54;
    target->unkf0 = !target->unkf0;
    return 1;
}

u8 EquipClass182550::func_slotb4()
{
    unk188->remove_child(this);
    FieldClass15AD40* associated = static_cast<FieldClass15AD40*>(func_slot44());
    associated->func_slot10c(1, 1);
    reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(associated);
    func_0034B3D0(unk188->unk48, 0);
    func_004E97A0(unk18c);
    return 2;
}

u8 EquipClass182550::func_slotb0()
{
    ItemCreationAllocationRecord* records[100];
    if (FieldClass15AE60::unk88 == 0)
    {
        return 3;
    }
    s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, static_cast<u16>(unk188->unk64));
    s32 selected = FieldStateCE420::unk24;
    if (count != 0 && selected >= 0)
    {
        if (unk18c != 0)
        {
            func_004E97A0(unk18c);
        }
        FieldClass15AE70* first = unk188->unk44;
        FieldClass15AE70* second = unk188->unk48;
        func_0034C540(static_cast<EquipClass182990*>(first), lib_allocation_get_identifier(records[selected]));
        first->func_slot20(1);
        first->func_slot64();
        reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(first);
        func_0034B3D0(static_cast<EquipClass182890*>(second), 0);
        second->func_slot20(0);
        FieldClass15AD40* associated = static_cast<FieldClass15AD40*>(func_slot44());
        associated->func_slot108(static_cast<u8>(unk188->unk60));
        associated->func_slot10c(0, 0);
        unk188->remove_child(this);
        func_004E97A0(unk18c);
    }
    else
    {
        return 3;
    }
    return 1;
}

void EquipClass182550::func_slot5c()
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
        s32 count = lib_collect_unequipped_allocations(D_001B64F8, records, static_cast<u16>(unk188->unk64));
        s32 selected = FieldStateCE420::unk24;
        EquipClass182890* detail = unk188->unk48;
        if (count != 0 && selected >= 0)
        {
            func_0034B3D0(detail, lib_allocation_get_identifier(records[selected]));
            LibObject172410* icon = unk15c[FieldStateCE420::unk28];
            set_selection_marker(icon, icon->unk94);
            const LibUiRect16* position = &unk15c[FieldStateCE420::unk28]->unk18;
            s32 x = static_cast<s32>(283.0f + position->unk00);
            s32 y = static_cast<s32>(224.0f + (30.0f + position->unk04));
            bool active = reinterpret_cast<FieldState23B3A0*>(FieldStateCE420::unk04)->unk75 != 0 && FieldClass15AE60::pad29[1] == 0;
            if (active)
            {
                if (unk190 != lib_allocation_get_identifier(records[selected]))
                {
                    unk190 = lib_allocation_get_identifier(records[selected]);
                    func_004E97A0(unk18c);
                }
                func_004E97B0(unk18c, static_cast<float>(x), static_cast<float>(y), 18.0f, lib_allocation_get_identifier(records[selected]), 0);
            }
            else
            {
                func_004E97A0(unk18c);
            }
        }
        else
        {
            func_0034B3D0(detail, 0);
            set_selection_marker(0, 0x808080);
        }
    }
}

void EquipClass182550::set_scroll_position(float offset)
{
    float position = (16.0f + offset) - 4.0f;
    s32 index = 0;
    do
    {
        LibClass178600* target_third;
        LibClass178600* target_second;
        target_third = unk15c[index];
        target_third->unk18.unk04 = position;
        target_third->unk3c = 1;
        target_second = unk138[index];
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
void EquipClass182550::refresh_rows(s32 start)
{
    ItemCreationAllocationRecord* records[100];
    s32 category = unk188->unk64;
    for (s32 index = 99; index >= 0; index--)
    {
        records[index] = 0;
    }
    FieldClass15AE60::unk88 = lib_collect_unequipped_allocations(D_001B64F8, records, category);
    for (s32 row = 0; row < 9; row++)
    {
        if (records[start + row] == 0)
        {
            unk15c[row]->unk3d = 0;
            unk138[row]->unk3d = 0;
        }
        else
        {
            set_equipment_icon(unk15c[row], category,
                               records[start + row]->modification_number);
            s32 count = 0;
            for (s32 index = 0; index < 8; index++)
            {
                u16 value = func_0040D930(records[start + row], index);
                if (value != 0 && value != 700)
                {
                    count++;
                }
            }
            unk138[row]->func_002D5CF0(unk184,
                         field_find_resource_record(D_001B643C->unk20, count + 60), 14);
            unk15c[row]->unk3d = 1;
            unk138[row]->unk3d = 1;
        }
    }
}

void EquipClass182550::func_00349D50()
{
    ItemCreationAllocationRecord* records[100];
    FieldClass15AE60::unk88 = 0;
    FieldClass15AE60::unk88 = lib_collect_unequipped_allocations(D_001B64F8, records, static_cast<u16>(reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14)->unk64));
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
s32 EquipClass182550::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 283.0f, 224.0f, 8);
    FieldStateCE420::unk3c = 1;
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* overlay = new (0) ItemCreationClass1746A0;
    unk180 = new (0) LibClass178630;
    lib_panel_init_rectangle(unk180, 1, 0.0f, 0.0f, 340.0f, 248.0f, 88.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, unk180);
    lib_scissor_init_rectangle(frame, 8.0f, 10.0f, 302.0f, 224.0f);
    lib_container_attach_widget(FieldClass15AE70::unk10, frame);
    unk184 = field_get_aligned_allocation(D_001B643C->unk20, 14);
    for (s32 index = 0; index < 9; index++)
    {
        unk15c[index] = new (0) LibObject172410;
        float y = 12.0f + 28.0f * static_cast<float>(index);
        lib_item_code_init_rectangle(unk15c[index], 34.0f, y, 302.0f, 21.599998f, 0, 0, 0);
        unk15c[index]->set_scale(0.9f, 0.9f);
        equip_set_icon_enabled(unk15c[index], 1);
        set_display_depth(unk15c[index], -1.0f);
        lib_container_attach_widget(FieldClass15AE70::unk10, unk15c[index]);
        unk138[index] = new (0) ItemCreationOptionResourceDisplay;
        FieldResourceRecord* record = field_find_resource_record(D_001B643C->unk20, 60);
        void* allocation = unk184;
        unk138[index]->unkcc = allocation;
        unk138[index]->unkd0 = 14;
        unk138[index]->func_002D6440(record, 13.0f, y);
        set_resource_scale(unk138[index], 0.9f, 0.9f);
        lib_container_attach_widget(FieldClass15AE70::unk10, unk138[index]);
        unk138[index]->unk3f = 0;
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
    func_00349D50();
    return 1;
}

/** @brief Store the selection byte at offset 0x84. @param value Byte to store. */
void FieldClass15AD40::func_slot110(u8 value)
{
    FieldClass15AE60::unk84 = value;
}

EquipClass182550::EquipClass182550(EquipListState* state)
{
    for (s32 index = 0; index < 9; index++)
    {
        unk48[index] = 0;
        unk15c[index] = 0;
        unk138[index] = 0;
    }
    unk188 = state;
    unk180 = 0;
    unk184 = 0;
    FieldClass15AD40();
    unk18c = 0;
    unk18c = state->unk68;
    unk190 = 0;
}

/** @brief Toggle the linked display flag. @return One. */
u8 EquipClass182670::func_slotbc()
{
    EquipClass182B90* target = unk180->unk54;
    target->unkf0 = !target->unkf0;
    return 1;
}

u8 EquipClass182670::func_slotb4()
{
    func_slot10c(0, 0);
    FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(func_slot44());
    if (associated != 0)
    {
        associated->func_slot20(1);
        associated->func_slot64();
        reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(associated);
    }
    FieldClass15AE70* other = unk1a4;
    if (other != 0)
    {
        other->func_slot20(0);
    }
    return 2;
}

u8 EquipClass182670::func_slotb0()
{
    if (FieldClass15AE60::unk88 == 0)
    {
        return 3;
    }
    if (unk180 == 0)
    {
        return 0;
    }
    if (FieldStateCE420::unk24 == 0)
    {
        FieldClass15AE70* associated = static_cast<FieldClass15AE70*>(func_slot44());
        if (associated != 0)
        {
            func_0034C540(static_cast<EquipClass182990*>(associated), 0);
            associated->func_slot20(1);
            associated->func_slot64();
            FieldStateCE420::unk04->unk3f = 0;
            reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(associated);
            refresh_rows(FieldStateCE420::unk22);
        }
        if (unk1a4 != 0)
        {
            unk1a4->func_slot20(0);
        }
        return 1;
    }
    if (FieldClass15AE60::unk88 != 0)
    {
        EquipClass182550* window = new (0) EquipClass182550(unk180);
        u32 associated = unk180->get_resource_slot();
        window->func_slot104(associated);
        window->func_slot40(this);
        unk180->add_child(window);
        unk180->func_00263C70(window);
    }
    else
    {
        return 3;
    }
    FieldStateCE420::unk04->unk3f = 0;
    return 1;
}

/** @brief Return the loaded resource slot. @return Resource slot. */
u32 EquipListState::get_resource_slot()
{
    return unk34;
}

/**
 * @brief Set the optional control's flag and opacity.
 * @param unused Unused first word.
 * @param value Value tested for zero and stored in the control's low-byte flag.
 */
void EquipClass182670::func_slot10c(u32 unused, u32 value)
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

void EquipClass182670::set_scroll_position(float offset)
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
        target_second = unk138[index];
        target_second->unk18.unk04 = position;
        target_second->unk3c = 1;
        target_third = unk15c[index];
        target_third->unk18.unk04 = position;
        target_third->unk3c = 1;
        position += 28.0f;
        index++;
    } while (index < 9);
}

void EquipClass182670::refresh_rows(s32 start)
{
    if (unk180 != 0)
    {
        EquipCategoryNode* node = static_cast<EquipCategoryNode*>(func_00351B30(&unk188, start));
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
                    u16 count = static_cast<u16>(unk198.count);
                    index = 0;
                    category = static_cast<u16>(record->unk02 + 1);
                    s32 key = category + 50000;
                    for (; index < count; index++)
                    {
                        if (category == *static_cast<u16*>(func_003518E0(&unk198, index)))
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
                    LibObject174F20* image = unk15c[row];
                    image->numeric_value = record->unk08;
                    image->unk3c = 1;
                    FieldClass15AE60::unk48[row]->unk3d = 1;
                    unk138[row]->unk3d = 1;
                    unk15c[row]->unk3d = 1;
                }
                else
                {
                    static_cast<LibClass174EF0*>(FieldClass15AE60::unk48[row])->set_color(0x808080);
                    lib_text_set_resource(static_cast<LibObject178750*>(FieldClass15AE60::unk48[row]), func_slot54(), 0xFBA, 0);
                    FieldClass15AE60::unk48[row]->unk3d = 1;
                    unk138[row]->unk3d = 0;
                    unk15c[row]->unk3d = 0;
                }
                node = node->next;
            }
            else
            {
                FieldClass15AE60::unk48[row]->unk3d = 0;
                unk138[row]->unk3d = 0;
                unk15c[row]->unk3d = 0;
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

void EquipClass182670::func_slot108(u8 category)
{
    s32 index;
    ItemCreationAllocationRecord* records[100];
    func_00351AB0(&unk188);
    func_00351860(&unk198);
    FieldClass15AE60::unk88 = 1;
    func_00351A20(&unk188, 0);
    FieldRecordSelection* selection = unk180->selected_records();
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
                        func_003517D0(&unk198, identifier);
                        break;
                    }
                }
                func_00351A20(&unk188, entry);
                FieldClass15AE60::unk88++;
            }
        }
    }
    s32 rows = FieldClass15AE60::unk88 >= 8 ? 8 : FieldClass15AE60::unk88;
    func_002CE420(&static_cast<FieldStateCE420&>(*this), 1, rows, 312, 28);
    FieldClass15AE60::configure_selection(FieldClass15AE60::unk88, 0, 0);
}

/** @brief Return the State's record selection. @return Record selection. */
FieldRecordSelection* EquipListState::selected_records()
{
    return unk38;
}

void EquipClass182670::func_slot5c()
{
    if (reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00261150() == this)
    {
        FieldClass15AD40::func_slot5c();
        EquipCategoryRecord** selected = reinterpret_cast<EquipCategoryRecord**>(func_00351B30(&unk188, FieldStateCE420::unk24));
        if (selected != 0)
        {
            if (*selected != 0)
            {
                unk180->unk64 = static_cast<u16>((*selected)->unk02 + 1);
            }
            else
            {
                unk180->unk64 = 0;
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
        func_0034B3D0(unk180->unk48, 0);
    }
    else
    {
        set_selection_marker(0, 0x808080);
    }
}

s32 EquipClass182670::func_slot104(u32 associated)
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
        unk138[index] = new (0) LibObject178750;
        unk15c[index] = new (0) LibObject174F20;
        float y = 16.0f + 28.0f * static_cast<float>(index);
        static_cast<LibObject178750*>(unk48[index])->init_resource_rectangle(13.0f, y, 0.0f, 0.0f, static_cast<s32>(associated), 50000, 0);
        unk138[index]->init_resource_rectangle(268.0f, y - 4.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x7E4, 1);
        unk15c[index]->init_numeric_resource_rectangle(276.0f, y, 28.0f, 24.0f, index, 0, 0);
        set_display_depth(static_cast<LibObject178750*>(unk48[index]), -1.0f);
        static_cast<LibObject178750*>(unk48[index])->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(FieldClass15AE70::unk10, unk48[index]);
        lib_container_attach_widget(FieldClass15AE70::unk10, unk138[index]);
        lib_container_attach_widget(FieldClass15AE70::unk10, unk15c[index]);
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

EquipClass182670::EquipClass182670(EquipListState* state)
{
    for (s32 index = 0; index < 9; index++)
    {
        unk48[index] = 0;
        unk138[index] = 0;
        unk15c[index] = 0;
    }
    unk180 = 0;
    unk180 = state;
    FieldClass15AD40();
    unk184 = 0;
    unk194 = 0;
    unk1a4 = 0;
}

s32 EquipClass182790::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 283.0f, 224.0f, 10);
    LibClass178630* widget = new (0) LibClass178630;
    lib_panel_init_rectangle(widget, 1, 0.0f, 0.0f, 340.0f, 248.0f, 88.0f);
    lib_container_attach_widget(unk10, widget);
    return 1;
}

EquipClass182790::~EquipClass182790()
{
}

/** @brief Test one protected statistic's check word. @param record Character record statistics. @param index Statistic index. @return True when the check word differs. */
static inline bool invalid_comparison_statistic(const EquipRecordStats* record, s32 index)
{
    return record->unk94[index] != (record->unka8 ^ (record->unk34[index][2] ^ (record->unk34[index][0] + record->unk34[index][1])));
}
/** @brief Decode one of the first four protected statistics for the comparison. @param record Character record statistics. @param index Statistic index. @return Decoded value, or zero for an invalid checksum. */
static inline u32 comparison_stat_value(const EquipRecordStats* record, s32 index)
{
    if (invalid_comparison_statistic(record, index))
    {
        return 0;
    }
    return record->unk34[index][1] ^ 0x7DE3F7E3;
}
/** @brief Decode the final statistic for the comparison using the fourth statistic check word. @param record Character record statistics. @return Decoded value, or zero for an invalid checksum. */
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
    if (resource.unkf0 == (resource.unk10c ^ ((resource.unk10[1] + resource.unk10[2]) ^ (resource.unk10[3] + resource.unk10[0]))) && slot >= 0 && slot <= (resource.unk0e ^ 0x7E93))
    {
        resource.unk10[slot] = item ^ 0x7E93;
        resource.unkf0 = (resource.unk10c ^ ((resource.unk10[1] + resource.unk10[2]) ^ (resource.unk10[3] + resource.unk10[0])));
    }
}
/**
 * @brief Copy the selected character record with the item equipped in the category slot.
 * @param window Item comparison window.
 * @param selected Record index to equip.
 * @return Original character record.
 */
static inline FieldRecord* copy_comparison_context(EquipClass182890* window, const s16& selected)
{
    func_0013A678(&window->unkb4, 0, 0xC4);
    func_0013A678(&window->unk178, 0, 0x114);
    window->unkb0 = selected;
    FieldRecordSelection* selection = window->unka8->selected_records();
    FieldRecord* original = &selection->records[selection->current];
    EquipResourceTextRecord* resource = &static_cast<EquipResourceTextRecord*>(selection->unk04)[selection->current];
    func_0013A4C0(&window->unkb4, original, 0xC4);
    func_0013A4C0(&window->unk178, resource, 0x114);
    set_comparison_entry(window->unk178, window->unkac, window->unkb0);
    func_003F9890(&window->unkb4, reinterpret_cast<EquipResourceTextRecord*>(&window->unk178), 0, -1);
    return original;
}

/**
 * @brief Show the statistics with a record equipped next to the current ones.
 * @param window Item comparison window.
 * @param selected Record index to compare, or zero to hide the comparison.
 */
extern "C" void func_0034B3D0(EquipClass182890* window, s16 selected)
{
    if (selected == 0)
    {
        window->unk2e4[0]->unk3f = 0;
        window->unk2e4[1]->unk3f = 0;
        window->unk2e4[2]->unk3f = 0;
        window->unk2e4[3]->unk3f = 0;
        window->unk2e4[4]->unk3f = 0;
        return;
    }
    FieldRecord* original = copy_comparison_context(window, selected);
    s32 value0 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(&window->unkb4), 0);
    s32 value1 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(&window->unkb4), 1);
    s32 value2 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(&window->unkb4), 2);
    s32 value3 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(&window->unkb4), 3);
    s32 value4 = comparison_final_value(reinterpret_cast<EquipRecordStats*>(&window->unkb4));
    s32 previous0 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(original), 0);
    s32 previous1 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(original), 1);
    s32 previous2 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(original), 2);
    s32 previous3 = comparison_stat_value(reinterpret_cast<EquipRecordStats*>(original), 3);
    s32 previous4 = comparison_final_value(reinterpret_cast<EquipRecordStats*>(original));
    set_comparison_number(window->unk2e4[0], value0, previous0);
    set_comparison_number(window->unk2e4[1], value1, previous1);
    set_comparison_number(window->unk2e4[2], value2, previous2);
    set_comparison_number(window->unk2e4[3], value3, previous3);
    set_comparison_number(window->unk2e4[4], value4, previous4);
    window->unk2e4[0]->unk3f = 1;
    window->unk2e4[1]->unk3f = 1;
    window->unk2e4[2]->unk3f = 1;
    window->unk2e4[3]->unk3f = 1;
    window->unk2e4[4]->unk3f = 1;
}

void EquipClass182890::refresh_item_details(u8 category, s16 selected)
{
    unkac = category;
    lib_text_set_resource(unk28c, func_slot54(), unkac + 0xFA1, 0);
    unkae = selected;
    if (unkae != 0)
    {
        EquipPackedRecord* item = packed_record(unkae);
        u16 code = packed_record_code(item);
        u8 variant = item->unk0c & 0x7F;
        set_equipment_icon(unk290, code + 1, variant);
        unk290->unk3f = 1;
    }
    else
    {
        unk290->unk3f = 0;
    }
    FieldRecordSelection* selection = unka8->selected_records();
    const EquipRecordStats* record = reinterpret_cast<const EquipRecordStats*>(&selection->records[selection->current]);
    if (record != 0)
    {
        set_number(unk2d0[0], stat_value(record, 0));
        set_number(unk2d0[1], stat_value(record, 1));
        set_number(unk2d0[2], stat_value(record, 2));
        set_number(unk2d0[3], stat_value(record, 3));
        set_number(unk2d0[4], final_stat_value(record));
        set_number(unk2e4[0], stat_value(record, 0));
        set_number(unk2e4[1], stat_value(record, 1));
        set_number(unk2e4[2], stat_value(record, 2));
        set_number(unk2e4[3], stat_value(record, 3));
        set_number(unk2e4[4], final_stat_value(record));
    }
}

s32 EquipClass182890::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 220.0f, 18);
    unk28c  =  new (0) LibObject178750;
    unk28c->init_resource_rectangle(14.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0xFA1, 1);
    lib_container_attach_widget(unk10, unk28c);
    unk28c->set_scale(0.8f, 0.8f);
    unk28c->set_color(0x806080);
    unk290  =  new (0) LibObject172410;
    lib_item_code_init_rectangle(unk290, 12.0f, 38.0f, 244.0f, 24.0f, 0, 0, 0);
    equip_set_icon_enabled(unk290, 1);
    unk290->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, unk290);
    for (s32 index  =  0; index < 5; index++)
    {
        float y  =  78.0f + 32.0f * static_cast<float>(index);
        unk294[index] = new(0) LibObject178750;
        unk294[index]->init_resource_rectangle(28.0f, y-2.0f, 0.0f, 0.0f, static_cast<s32>(associated), index+0x81A, 0);
        unk294[index]->set_color(0x805050);
        lib_container_attach_widget(unk10, unk294[index]);
        unk2a8[index] = new(0) LibObject178750;
        unk2a8[index]->init_resource_rectangle(73.0f, y, 0.0f, 0.0f, static_cast<s32>(associated), 0x7E4, 0);
        unk2a8[index]->set_color(0x805050);
        lib_container_attach_widget(unk10, unk2a8[index]);
        unk2d0[index] = new(0) LibObject174F20;
        unk2d0[index]->init_numeric_resource_rectangle(92.0f, y, 48.0f, 22.8f, 9999, 0, 0);
        unk2d0[index]->set_scale(0.95f, 0.95f);
        lib_container_attach_widget(unk10, unk2d0[index]);
        unk2bc[index] = new(0) LibObject178750;
        unk2bc[index]->init_resource_rectangle(158.0f, y, 0.0f, 0.0f, static_cast<s32>(associated), 0xFB7, 0);
        unk2bc[index]->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(unk10, unk2bc[index]);
        unk2e4[index] = new(0) LibObject174F20;
        unk2e4[index]->init_numeric_resource_rectangle(196.0f, y, 48.0f, 22.8f, 9999, 0, 0);
        unk2e4[index]->set_scale(0.95f, 0.95f);
        unk2e4[index]->unk3f = 0;
        lib_container_attach_widget(unk10, unk2e4[index]);
    }
    func_slot20(0);
    return 1;
}

EquipClass182890::~EquipClass182890()
{
}

EquipClass182890::EquipClass182890(EquipListState* state)
{
    unka8 = 0;
    unka8 = state;
    unkac = 0xFF;
    unkae = 0;
    unkb0 = 0;
    unkb2 = 0;
    func_0013A678(&unkb4, 0, sizeof(unkb4));
    func_0013A678(&unk178, 0, sizeof(unk178));
    unk28c = 0;
    unk290 = 0;
    unk294[0] = 0;
    unk2bc[0] = 0;
    unk2d0[0] = 0;
    unk2e4[0] = 0;
    for (s32 i = 1; i < 5; i++)
    {
        unk294[i] = 0;
        unk2bc[i] = 0;
        unk2d0[i] = 0;
        unk2e4[i] = 0;
    }
}

/**
 * @brief Store the category window's selected protected equipment entry and refresh the check word.
 * @param resource Resource record.
 * @param owner Category window holding the selected slot.
 * @param value Record index to store.
 */
static inline void set_protected_equipment_entry(EquipResourceEquipment* resource, const EquipClass182990* owner, s32 value)
{
    s32 index = owner->unk108;
    if (resource->unkf0 != (resource->unk10c ^ ((resource->unk10[1] + resource->unk10[2]) ^ (resource->unk10[3] + resource->unk10[0]))))
    {
        return;
    }
    if (index < 0)
    {
        return;
    }
    if (index <= (resource->unk0e ^ 0x7E93))
    {
        resource->unk10[index] = static_cast<s16>(value) ^ 0x7E93;
        resource->unkf0 = resource->unk10c ^ ((resource->unk10[1] + resource->unk10[2]) ^ (resource->unk10[3] + resource->unk10[0]));
    }
}

/**
 * @brief Equip a record in the category window's selected slot.
 * @param window Category window.
 * @param identifier Record index to equip, or zero to clear the slot.
 */
extern "C" void func_0034C540(EquipClass182990* window, s16 identifier)
{
    if (window->unkac != 0)
    {
        func_0040C7E0(D_001B64F8, protected_equipment_entry(&static_cast<EquipResourceEquipment*>(window->unkac->unk04)[window->unkac->current], window->unk108), 0);
        if (identifier)
        {
            func_0040C7E0(D_001B64F8, identifier, window->unkac->slots[window->unkac->current]);
            set_protected_equipment_entry(&static_cast<EquipResourceEquipment*>(window->unkac->unk04)[window->unkac->current], window, identifier);
        }
        else
        {
            set_protected_equipment_entry(&static_cast<EquipResourceEquipment*>(window->unkac->unk04)[window->unkac->current], window, 0);
        }
        FieldRecordSelection* selection = window->unka8->selected_records();
        func_003F9890(&selection->records[selection->current], &static_cast<EquipResourceTextRecord*>(selection->unk04)[selection->current], 0, -1);
    }
    func_0034D4C0(window);
    s32 category = window->unk108;
    if (category >= 3)
    {
        category = 2;
    }
    window->unk104->func_slot108(category);
}

void EquipClass182990::func_slot6c()
{
    if (static_cast<s16>(func_0023B3B0(equipment_slot_selector, 1)) != 1)
    {
        s16 category = func_0023B3A0(equipment_slot_selector);
        unk104 = static_cast<FieldClass15AD40*>(func_slot4c());
        switch (category)
        {
            case 0:
                unk104->func_slot108(0);
                unka8->unk60 = 0;
                break;
            case 1:
                unk104->func_slot108(1);
                unka8->unk60 = 1;
                break;
            case 2:
            case 3:
                unk104->func_slot108(2);
                unka8->unk60 = 2;
                break;
        }
    }
}

void EquipClass182990::func_slot68()
{
    if (static_cast<s16>(func_0023B3B0(equipment_slot_selector, 0)) != 1)
    {
        s16 category = func_0023B3A0(equipment_slot_selector);
        unk104 = static_cast<FieldClass15AD40*>(func_slot4c());
        switch (category)
        {
            case 0:
                unk104->func_slot108(0);
                unka8->unk60 = 0;
                break;
            case 1:
                unk104->func_slot108(1);
                unka8->unk60 = 1;
                break;
            case 2:
            case 3:
                unk104->func_slot108(2);
                unka8->unk60 = 2;
                break;
        }
    }
}

u8 EquipClass182990::func_slotb0()
{
    s32 category = static_cast<u16>(func_0023B3A0(equipment_slot_selector));
    if (unkc0 < category)
    {
        return 3;
    }
    if (unk100 != 0)
    {
        static_cast<EquipClass182890*>(unk100)->refresh_item_details(category, unkb8[category]);
        unk100->func_slot20(1);
    }
    EquipClass182C90* associated = static_cast<EquipClass182C90*>(func_slot44());
    if (associated->unkbc != 0)
    {
        associated->unkbc->unk3f = 0;
    }
    if (associated->unkc0 != 0)
    {
        associated->unkc0->unk3f = 0;
    }
    unk104 = static_cast<FieldClass15AD40*>(func_slot4c());
    if (unk108 != category)
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
        unk104->func_slot108(next_category);
    }
    unk104->func_slot110(1);
    unk104->func_slot10c(1, 1);
    reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14)->func_00263C70(unk104);
    unk108 = category;
    FieldClass153130* selector = reinterpret_cast<FieldClass153130*>(equipment_slot_selector);
    selector->ItemCreationClass185050::unk30 = 64.0f;
    selector->LibClass178600::unk3c = 1;
    func_slot20(0);
    func_004E97A0(unka8->unk68);
    return 1;
}

u8 EquipClass182990::func_slotb4()
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
        EquipClass182220* window = new (0) EquipClass182220;
        if (window == 0)
        {
            return 0;
        }
        window->func_slot10(func_slot54(), 200.0f, 160.0f, 13);
        window->func_slot40(this);
        reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->add_child(window);
        reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14)->func_00263C70(window);
    }
    func_004E97A0(unka8->unk68);
    return 2;
}

void EquipClass182990::func_slot64()
{
    EquipClass182C90* associated = static_cast<EquipClass182C90*>(func_slot44());
    if (associated->unkbc != 0)
    {
        associated->unkbc->unk3f = 1;
    }
    if (associated->unkc0 != 0)
    {
        associated->unkc0->unk3f = 1;
    }
    equip_refresh_record_display(associated);
    FieldClass153130* selector = reinterpret_cast<FieldClass153130*>(equipment_slot_selector);
    selector->ItemCreationClass185050::unk30 = 128.0f;
    selector->LibClass178600::unk3c = 1;
}

u8 EquipClass182990::func_slotb8()
{
    EquipClass182C90* associated = static_cast<EquipClass182C90*>(func_slot44());
    if (associated->unkbc != 0)
    {
        associated->unkbc->unk3f = 0;
    }
    if (associated->unkc0 != 0)
    {
        associated->unkc0->unk3f = 0;
    }
    FieldRecord* record = &unkac->records[unkac->current];
    EquipResourceTextRecord* resource = &static_cast<EquipResourceTextRecord*>(unkac->unk04)[unkac->current];
    func_0034F2A0(unka8, record, resource, unkac->slots[unkac->current]);
    func_003F9890(record, resource, 0, -1);
    func_004E97A0(unka8->unk68);
    func_0034D4C0(this);
    s32 category = static_cast<u16>(func_0023B3A0(equipment_slot_selector));
    if (category == 0 || category == 1)
    {
        func_slot44();
        unk104 = static_cast<FieldClass15AD40*>(func_slot4c());
        unk104->func_slot108(category);
        unk104->func_slot110(1);
    }
    if (associated->unkbc != 0)
    {
        associated->unkbc->unk3f = 1;
    }
    if (associated->unkc0 != 0)
    {
        associated->unkc0->unk3f = 1;
    }
    return 1;
}

u8 EquipClass182990::func_slotbc()
{
    EquipClass182B90* target = unka8->unk54;
    target->unkf0 = !target->unkf0;
    return 1;
}

/** @brief Test whether a selector is inactive. @param selector Selector state. @return One when its control byte is clear. */
static inline u8 selector_inactive(FieldState23B3A0* selector)
{
    return !(selector->unk75 != 0);
}

void EquipClass182990::func_slot5c()
{
    if (reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14)->func_00261150() == this)
    {
        u16 selected = func_0023B3A0(equipment_slot_selector);
        EquipPackedRecord* record = packed_record(unkb8[selected]);
        if (record != 0)
        {
            unka8->unk64 = static_cast<u16>(packed_record_code(record) + 1);
            const LibUiRect16* position = &unkd4[selected]->unk18;
            s32 x = static_cast<s32>(16.0f + position->unk00);
            s32 y = static_cast<s32>(220.0f + (29.0f + position->unk04));
            u8 inactive = selector_inactive(equipment_slot_selector);
            if (inactive == 0)
            {
                void* tooltip = unka8->unk68;
                func_004E97B0(tooltip, static_cast<float>(x), static_cast<float>(y), 18.0f,
                              lib_allocation_get_identifier(reinterpret_cast<ItemCreationAllocationRecord*>(record)), 0);
            }
            else
            {
                func_004E97A0(unka8->unk68);
            }
        }
        else
        {
            unka8->unk64 = 0;
            func_004E97A0(unka8->unk68);
        }
    }
}

s32 EquipClass182990::func_slotdc()
{
    if (unkac == 0)
    {
        return 0;
    }
    func_004E97A0(unka8->unk68);
    if (unkac->count > 1)
    {
        EquipListState* state = reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14);
        if (state->unk38 != 0)
        {
            state->unk38->active = 0;
            func_0028E2B0(state->unk38, 1);
            equip_refresh_record_display(state->unk40);
            func_0034D4C0(state->unk44);
            state->unk50->func_slot108(static_cast<u8>(state->unk60));
        }
        return 4;
    }
    return 0;
}

s32 EquipClass182990::func_slotd8()
{
    if (unkac == 0)
    {
        return 0;
    }
    func_004E97A0(unka8->unk68);
    if (unkac->count > 1)
    {
        EquipListState* state = reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14);
        if (state->unk38 != 0)
        {
            state->unk38->active = 0;
            func_0028E2B0(state->unk38, 0);
            equip_refresh_record_display(state->unk40);
            func_0034D4C0(state->unk44);
            state->unk50->func_slot108(static_cast<u8>(state->unk60));
        }
        return 4;
    }
    return 0;
}

/**
 * @brief Refresh the category window's equipment rows from the selected resource record.
 * @param object Category window.
 */
extern "C" void func_0034D4C0(EquipClass182990* object)
{
    object->unkc0 = static_cast<EquipResourceEquipment*>(object->unkac->unk04)[object->unkac->current].unk0c ^ 0x7E93;
    if (object->unkc0 >= 4)
    {
        object->unkc0 = 4;
    }
    for (s32 index = 0; index < 4; index++)
    {
        object->unkb8[index] = 0;
        object->unkc4[index]->set_color(0x505050);
    }
    for (s32 index = 0; index < object->unkc0; index++)
    {
        object->unkc4[index]->set_color(0x806080);
    }
    for (s32 index = 0; index < object->unkc0; index++)
    {
        object->unkd4[index]->unk3f = 0;
        object->unkb8[index] = protected_equipment_entry(&static_cast<EquipResourceEquipment*>(object->unkac->unk04)[object->unkac->current], index);
        if (object->unkb8[index] != 0)
        {
            object->unkb4 = packed_record(object->unkb8[index]);
            u16 code = packed_record_code(object->unkb4);
            u8 variant = object->unkb4->unk0c & 0x7F;
            set_equipment_icon(object->unkd4[index], static_cast<u16>(code) + 1, variant);
            object->unkd4[index]->unk3f = 1;
            object->unke4[index]->unk3f = 0;
        }
        else
        {
            object->unke4[index]->unk3f = 1;
        }
    }
}

s32 EquipClass182990::func_slotf4(u32 associated)
{
    if (unkac == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 16.0f, 220.0f, 18);
    ItemCreationClass1746A0* frame = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* overlay = new (0) ItemCreationClass1746A0;
    lib_scissor_init_rectangle(frame, 12.0f, 12.0f, 270.0f, 224.0f);
    lib_container_attach_widget(unk10, frame);
    unkb0 = 58.0f;
    for (s32 index = 0; index < 4; index++)
    {
        float y = 16.0f + static_cast<float>(index) * unkb0;
        unkc4[index] = new (0) LibObject178750;
        lib_text_init_resource_rectangle(static_cast<LibObject178750*>(unkc4[index]), static_cast<s32>(associated), index + 0xFA1, 1, 14.0f, y, 0.0f, 0.0f);
        lib_container_attach_widget(unk10, unkc4[index]);
        unkc4[index]->set_scale(0.8f, 0.8f);
        unkc4[index]->set_color(0x806080);
        unkd4[index] = new (0) LibObject172410;
        lib_item_code_init_rectangle(unkd4[index], 12.0f, 38.0f + unkb0 * static_cast<float>(index), 244.0f, 24.0f, 0, 0, 0);
        equip_set_icon_enabled(unkd4[index], 1);
        unkd4[index]->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(unk10, unkd4[index]);
        unke4[index] = new (0) LibObject178750;
        lib_text_init_resource_rectangle(static_cast<LibObject178750*>(unke4[index]), static_cast<s32>(associated), 0xFBA, 0, 12.0f, 38.0f + unkb0 * static_cast<float>(index), 284.0f, 24.0f);
        unke4[index]->set_scale(0.9f, 0.9f);
        unke4[index]->unk3f = 0;
        lib_container_attach_widget(unk10, unke4[index]);
    }
    lib_scissor_init_reset(overlay, 1);
    lib_container_attach_widget(unk10, overlay);
    equipment_slot_selector = reinterpret_cast<FieldState23B3A0*>(new (0) FieldClass153130);
    reinterpret_cast<FieldClass153130*>(equipment_slot_selector)->func_0023B530(1, 4, 1, 0, 1, 12.0f, 50.0f, 0.0f, unkb0);
    lib_container_attach_widget(unk10, reinterpret_cast<FieldClass153130*>(equipment_slot_selector));
    func_0034D4C0(this);
    return 1;
}

EquipClass182990::EquipClass182990(EquipListState* state)
{
    unka8 = 0;
    unka8 = state;
    unkf4 = 0;
    for(s32 index = 0; index < 4; index++)
    {
        unkc4[index] = 0;
        unkd4[index] = 0;
        unkb8[index] = 0;
    }
    unkb0 = 0;
    unkac = 0;
    unkac = reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14)->selected_records();
    equipment_slot_selector = 0;
    unkf8 = 0;
    unkb4 = 0;
    unkc0 = 0;
    unk100 = 0;
    unk108 = 0;
    unk104 = 0;
}

s32 EquipClass182A90::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 224.0f, 19);
    LibClass178630* widget = new (0) LibClass178630;
    lib_panel_init_rectangle(widget, 0, 0.0f, 0.0f, 270.0f, 248.0f, 88.0f);
    lib_container_attach_widget(unk10, widget);
    return 1;
}

EquipClass182A90::~EquipClass182A90()
{
}

extern "C" void func_0040D2E0(ItemCreationAllocationRecord* record, u16 item_code, u8 modification_number, const u16* factors, bool new_item, bool suppress_allocation_id);

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

void EquipClass182B90::func_slot5c()
{
    EquipListState* state = reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14);
    if (state->unk64 > 0)
    {
        if (unkf0 != 0)
        {
            unka8->unk3f = 0;
            unkac->unk3f = 1;
            ItemCreationAllocationRecord preview __attribute__((aligned(16)));
            preview.reset(0);
            ItemCreationCategoryRecord* item_record = equip_category_record(state->unk64);
            initialize_equip_allocation(&preview, item_record, 0);
            set_number(unkd8[0], D_001B64F0[preview.definition_index()].attack);
            set_number(unkd8[1], D_001B64F0[preview.definition_index()].hit);
            set_number(unkd8[2], D_001B64F0[preview.definition_index()].defense);
            set_number(unkd8[3], D_001B64F0[preview.definition_index()].agility);
            set_number(unkd8[4], D_001B64F0[preview.definition_index()].intelligence);
            for (s32 row = 0; row < 5; row++)
            {
                unkb0[row]->unk3f = 1;
                unkc4[row]->unk3f = 1;
                unkd8[row]->unk3f = 1;
            }
        }
        else
        {
            s32 key = state->unk64 + 0x12924;
            if (key != unkec)
            {
                unka8->unk3f = 1;
                lib_multiline_text_set_resource(unka8, func_slot54(), key, 8, 1);
                LibObject174D90* description = unka8;
                description->unk80 = 0.8f;
                description->unk84 = 0.8f;
                description->unk3c = 1;
            }
            for (s32 row = 0; row < 5; row++)
            {
                unkb0[row]->unk3f = 0;
                unkc4[row]->unk3f = 0;
                unkd8[row]->unk3f = 0;
            }
            unkac->unk3f = 0;
        }
    }
    else
    {
        unkac->unk3f = 0;
        unka8->unk3f = 0;
        for (s32 row = 0; row < 5; row++)
        {
            unkb0[row]->unk3f = 0;
            unkc4[row]->unk3f = 0;
            unkd8[row]->unk3f = 0;
        }
    }
}

/** @brief Clear the multiline display scroll offsets. @param display Multiline text display. */
static inline void reset_scroll(LibObject174D90* display)
{
    display->unk52c = 0.0f;
    display->unk524 = 0.0f;
}
s32 EquipClass182B90::func_slotf4(u32 associated)
{
    if (associated == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot10(associated, 220.0f, 80.0f, 18);
    LibClass178630* panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 404.0f, 145.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    unka8 = new (0) LibObject174D90;
    unka8->init_multiline_resource_rectangle(32.0f, 13.0f, 362.0f, 140.0f, static_cast<s32>(associated), 0xFAE, 8, 0);
    reset_scroll(unka8);
    lib_container_attach_widget(unk10, unka8);
    unka8->unk3f = 0;
    unkac = new (0) LibObject178750;
    unkac->init_resource_rectangle(40.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0xFBB, 0);
    unkac->set_color(0x806080);
    unkac->set_scale(0.75f, 0.75f);
    lib_container_attach_widget(unk10, unkac);
    unkac->unk3f = 0;
    for (s32 index = 0; index < 5; index++)
    {
        unkb0[index] = new (0) LibObject178750;
        float y = 42.0f + 28 * (index / 2);
        unkb0[index]->init_resource_rectangle(50.0f + 190 * (index % 2), y, 0.0f, 0.0f, static_cast<s32>(associated), 0xFBC + index, 0);
        unkb0[index]->set_color(0x805050);
        lib_container_attach_widget(unk10, unkb0[index]);
        unkb0[index]->unk3f = 0;
        unkc4[index] = new (0) LibObject178750;
        unkc4[index]->init_resource_rectangle(100.0f + 190 * (index % 2), y, 0.0f, 0.0f, static_cast<s32>(associated), 0x7E4, 0);
        unkc4[index]->set_color(0x805050);
        lib_container_attach_widget(unk10, unkc4[index]);
        unkc4[index]->unk3f = 0;
        unkd8[index] = new (0) LibObject174F20;
        unkd8[index]->init_numeric_resource_rectangle(90.0f + 190 * (index % 2), y, 80.0f, 30.0f, 0, static_cast<s32>(associated), 1);
        lib_container_attach_widget(unk10, unkd8[index]);
        unkd8[index]->unk3f = 0;
    }
    return 1;
}

void EquipClass182C90::refresh_slot_marker()
{
    s32 selected = 0;
    s32 clear_index = 0;
    FieldRecordSelection* selection = unkac;
    u16 slot = selection->slots[selection->current];
    for (; clear_index < 8; clear_index++)
    {
        if (unkc4[clear_index])
        {
            unkc4[clear_index]->unk3f = 0;
        }
    }
    for (s32 i = 0; i < 8; i++)
    {
        if (slot == unke4[i])
        {
            break;
        }
        selected++;
    }
    if (unkc4[selected])
    {
        unkc4[selected]->unk3f = 1;
    }
}

void EquipClass182C90::func_slot5c()
{
    EquipListState* state = reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14);
    FieldClass15AE70* window = state->unk44;
    if (state->func_00261150() == window)
    {
        unkec->unk3f = 1;
    }
    else
    {
        unkec->unk3f = 0;
    }
}

/** @brief Update a resource display string. @param display String display. @param text String to display. */
static inline void set_resource_text(LibObject175140* display, const char* text)
{
    display->unkfc = text;
    display->unk3c = 1;
}
s32 EquipClass182C90::func_slotf4(u32 associated)
{
    if (unkac == 0)
    {
        return 0;
    }
    unka8 = unkac->slots[unkac->current];
    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 17);
    LibClass178630* panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 232.0f, 144.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    func_00351E40(&unk14, panel);
    unkb0 = new (0) LibObject175140;
    const char* text = reinterpret_cast<const char*>(static_cast<EquipResourceTextRecord*>(unkac->unk04)[unkac->current].unk20);
    unkb0->func_00467AD0(40.0f, 24.0f, 0.0f, 0.0f, text, 0);
    lib_container_attach_widget(unk10, unkb0);
    func_00351C00(&unk44, unkb0);
    unkb0->set_scale(0.8f, 0.8f);
    unkb4 = new (0) LibObject178750;
    unkb8 = new (0) LibObject174F20;
    unkb4->init_resource_rectangle(120.0f, 48.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0xFA9, 0);
    unkb8->init_numeric_resource_rectangle(170.0f, 48.0f, 42.0f, 24.0f, equip_record_value(&unkac->records[unkac->current]), 0, 0);
    lib_container_attach_widget(unk10, unkb4);
    func_00351D20(&unk2c, unkb4);
    unkb4->set_color(0x806080);
    lib_container_attach_widget(unk10, unkb8);
    func_00351C90(&unk38, unkb8);
    unkb8->set_scale(0.9f, 0.9f);
    unkec = new (0) LibObject178750;
    unkec->init_resource_rectangle(105.0f, 80.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0xFB6, 0);
    unkec->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, unkec);
    unkf0 = new (0) LibObject178750;
    unkf0->init_resource_rectangle(105.0f, 110.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0xFB5, 0);
    unkf0->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, unkf0);
    if (unkac->count > 1)
    {
        unkbc = new (0) ItemCreationClass174C40;
        unkc0 = new (0) ItemCreationClass174C40;
        lib_indexed_resource_init(unkbc, 10, 8.0f, 8.0f);
        lib_indexed_resource_init(unkc0, 11, 196.0f, 8.0f);
        unkbc->set_scale(0.9f, 0.9f);
        unkc0->set_scale(0.9f, 0.9f);
        lib_container_attach_widget(unk10, unkbc);
        lib_container_attach_widget(unk10, unkc0);
    }
    FieldListNode* node = unk2c.head->next;
    while (node != 0)
    {
        static_cast<LibObject178750*>(node->value)->set_scale(0.9f, 0.9f);
        node = node->next;
    }
    for (s32 index = 0; index < 8; index++)
    {
        u16 slot = static_cast<u16>(unkac->slots[static_cast<s16>(index)]);
        if (slot != 0)
        {
            unke4[index] = slot;
            unkc4[index] = new (0) ItemCreationOptionResourceDisplay;
            void* allocation = field_get_aligned_allocation(D_001B643C->unk20, static_cast<u8>(slot));
            FieldResourceRecord* record = field_find_resource_record(D_001B643C->unk20, 4);
            unkc4[index]->unkcc = allocation;
            unkc4[index]->unkd0 = slot;
            unkc4[index]->func_002D6440(record, 20.0f, 50.0f);
            unkc4[index]->unk3f = 0;
            lib_container_attach_widget(unk10, unkc4[index]);
        }
    }
    if (unkac != 0)
    {
        set_resource_text(unkb0, reinterpret_cast<const char*>(static_cast<EquipResourceTextRecord*>(unkac->unk04)[unkac->current].unk20));
        set_number(unkb8, equip_record_value(&unkac->records[unkac->current]));
        refresh_slot_marker();
    }
    return 1;
}

EquipClass182C90::EquipClass182C90()
{
    unka8 = 0;
    unkac = 0;
    unkac = reinterpret_cast<EquipListState*>(D_001B643C->unk10->unk14)->selected_records();
    unkb4 = 0;
    unkb8 = 0;
    unkbc = 0;
    unkc0 = 0;
    for (s32 i = 0; i < 8; i++)
    {
        unkc4[i] = 0;
        unke4[i] = 0;
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
        valid = true;
    if (valid)
        return reinterpret_cast<ItemCreationAllocationRecord*>(reinterpret_cast<u8*>(base) + (index - 1) * 16);
    return 0;
}
/** @brief Decode a protected statistic after validating its check word. @param first First summand. @param second Second summand. @param value Encoded
 * statistic. @param check Stored check word. @param salt Record salt. @return Decoded statistic, or zero for an invalid check word. */
static inline s32 equip_checked_statistic(s32 first, s32 second, s32 value, s32 check, s32 salt)
{
    if (check != (salt ^ (value ^ (first + second))))
        return 0;
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
        return 0;
    if (!equip_valid_equipment_index(index, r->count ^ 0x7E93))
        return 0;
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
/** @brief Select available allocations that improve the first two protected statistics. @param state Unused state receiver. @param record Field record used for each trial. @param resource
 * Resource equipment identifiers to update. @param slot Equipment selection slot. */
extern "C" void func_0034F2A0(EquipListState* state, FieldRecord* record, EquipResourceTextRecord* resource, s8 slot)
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

void EquipListState::func_slot5c()
{
    LibObject178660* tooltip = static_cast<LibObject178660*>(unk68);
    if (tooltip != 0)
    {
        static_cast<LibClass174610&>(*tooltip).func_003EF740();
    }
    if (unk34 != 0)
    {
        lib_release_resource_slot(D_001B657C, unk34);
    }
    lib_object_detach_owner(this);
    func_001DD7B0();
}

/** @brief Submit the State to the resident object queue. */
void EquipListState::func_001DD7B0()
{
    resident_enqueue_object(D_001B65F4, this);
}

/** @brief Default update handler that performs no work. */
void FieldListObject::update()
{
}

/** @brief Attach the detail and comparison windows. @param object Category window. @param detail Category detail window. @param comparison Item comparison window. */
static inline void attach_comparison(EquipClass182990* object, EquipClass182B90* detail, EquipClass182890* comparison)
{
    object->unkf8 = detail;
    object->unk100 = comparison;
}

s32 EquipListState::init_windows()
{
    EquipRuntimeResource* runtime = reinterpret_cast<EquipRuntimeResource*>(D_001B657C);
    runtime->unk51c = unk34;
    runtime->unk520 = 0x11171;
    unk68 = new (0) EquipClass1796F0;
    if (unk68 != 0)
    {
        func_004E9BC0(static_cast<EquipClass1796F0*>(unk68));
        lib_queue_display_object(D_001B657C, static_cast<EquipClass1796F0*>(unk68));
    }
    EquipClass182450* options = new (0) EquipClass182450;
    EquipClass182350* scrolling = new (0) EquipClass182350;
    unk40 = new (0) EquipClass182C90;
    unk54 = new (0) EquipClass182B90;
    unk44 = new (0) EquipClass182990(this);
    EquipClass182A90* panel = new (0) EquipClass182A90;
    unk48 = new (0) EquipClass182890(this);
    unk4c = new (0) EquipClass182790;
    unk50 = new (0) EquipClass182670(this);
    options->func_slotf4(unk34);
    FieldClass153E30::add_child(options);
    options->func_slot40(scrolling);
    scrolling->func_slotf4(unk34);
    FieldClass153E30::add_child(scrolling);
    scrolling->func_slot40(0);
    panel->func_slotf4(unk34);
    FieldClass153E30::add_child(panel);
    unk54->func_slotf4(unk34);
    FieldClass153E30::add_child(unk54);
    unk40->func_slotf4(unk34);
    FieldClass153E30::add_child(unk40);
    attach_comparison(unk44, unk54, unk48);
    unk44->func_slot48(unk50);
    unk44->func_slotf4(unk34);
    FieldClass153E30::add_child(unk44);
    unk44->func_slot40(unk40);
    unk48->func_slotf4(unk34);
    FieldClass153E30::add_child(unk48);
    unk4c->func_slotf4(unk34);
    FieldClass153E30::add_child(unk4c);
    unk50->func_slot40(unk44);
    unk50->unk1a4 = unk48;
    unk50->func_slot104(unk34);
    FieldClass153E30::add_child(unk50);
    unk20 = unk44;
    unk3c_active = 1;
    return 1;
}

EquipClass1797B0::~EquipClass1797B0()
{
}

LibClass178A70::~LibClass178A70()
{
}

s32 EquipListState::on_resource_loaded(void* buffer)
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
    unk34 = lib_load_resource_slot(D_001B657C, aligned);
    resident_exchange_allocation_heap(saved_heap);
    EquipRuntimeResource* runtime = reinterpret_cast<EquipRuntimeResource*>(D_001B657C);
    runtime->unk514 = unk34;
    runtime->unk518 = 0xC351;
    return init_windows();
}

/**
 * @brief Allocate and initialize the State's record selection.
 * @return One when a selection exists and initialization succeeds; otherwise zero.
 */
u8 EquipListState::func_00264110()
{
    unk38 = new (0) FieldRecordSelection;
    u8 result = func_0028E3D0(unk38);
    if (unk38 == 0 || result == 0)
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
EquipListState::~EquipListState()
{
    if (unk38 != 0)
    {
        release_owned(unk38);
    }
}

/** @brief Initialize the equipment State and its resource table entries. */
EquipListState::EquipListState()
{
    unk34 = 0;
    unk38 = 0;
    unk3c_active = 0;
    unk40 = 0;
    unk44 = 0;
    unk4c = 0;
    unk48 = 0;
    unk50 = 0;
    unk54 = 0;
    unk64 = 0;
    unk58 = 0;
    unk5c = 0;
    void* table = resident_get_entry_table(resident_get_runtime_owner());
    unk58 = resident_find_entry(table, 2);
    unk5c = resident_find_entry(table, 3);
    unk60 = 0;
    unk68 = 0;
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

EquipClass182550::~EquipClass182550()
{
}

EquipClass182670::~EquipClass182670()
{
}

EquipClass182990::~EquipClass182990()
{
}

EquipClass182B90::~EquipClass182B90()
{
}

EquipClass182C90::~EquipClass182C90()
{
}

/** @brief Report whether window setup finished. @return Setup flag. */
u8 EquipListState::windows_ready()
{
    return unk3c_active;
}

/** @brief Report this object's default list kind. @return Four. */
s32 EquipListState::get_default_list_kind()
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

EquipLinkedList::EquipLinkedList()
{
    head = new (0) EquipLinkedNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

EquipLinkedList::~EquipLinkedList()
{
    func_00351860(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_003517D0(EquipLinkedList* list, u16 value)
{
    EquipLinkedNode* node;
    EquipLinkedNode* cursor;
    node = new (0) EquipLinkedNode;
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

void func_00351860(EquipLinkedList* list)
{
    EquipLinkedNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        EquipLinkedNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

void* func_003518E0(void* object, s32 count)
{
    EquipLinkedNode* node = ((EquipLinkedList*)object)->head->next;
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

EquipWordList::EquipWordList()
{
    head = new (0) EquipWordNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

EquipWordList::~EquipWordList()
{
    func_00351AB0(this);
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
void func_00351A20(EquipWordList* list, ItemCreationCategoryRecord* value)
{
    EquipWordNode* node;
    EquipWordNode* cursor;
    node = new (0) EquipWordNode;
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

void func_00351AB0(EquipWordList* list)
{
    EquipWordNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        EquipWordNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

void* func_00351B30(void* object, s32 count)
{
    EquipWordNode* node = ((EquipWordList*)object)->head->next;
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

void func_00351B70(FieldCountedList* list, void* value)
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

void func_00351C00(FieldCountedList* list, void* value)
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

void func_00351C90(FieldCountedList* list, void* value)
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

void func_00351D20(FieldCountedList* list, void* value)
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

void func_00351DB0(FieldCountedList* list, void* value)
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

void func_00351E40(FieldCountedList* list, void* value)
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

