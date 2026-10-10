#include "include_asm.h"
#include "overlays/cshop/text.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"
#include "overlays/lib/list_indicator_inlines.h"
#include "overlays/lib/marker_widget_inlines.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_00101260.h"
#include "main/resident_001001E0.h"
#include "main/resident_data.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_001E1590.h"

extern "C" u8 func_28E3D0(void* object);


/** Partial aligned resource header with the payload size. */
struct ShopAlignedResource
{
    u8 unk00[0x40];
    s32 unk40;
};

struct ObjectField20
{
    u8 unknown_0[0x20];
    u32 field_20;
};

struct ObjectField34
{
    u8 unknown_0[0x34];
    u32 field_34;
};

struct ObjectStatusFields
{
    u8 unknown_0[0x24];
    u32 field_24;
    s8 field_28;
    u8 unknown_29[0xF];
    u8 field_38;
};

/** Packed sixteen-byte allocation record checked before displaying its value. */
struct ItemCreationAllocationRecord
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

    /**
     * @brief Calculate the checksum of the six halfwords for a given shift.
     * @param shift Two-bit shift applied to the checksum key.
     * @return Calculated checksum.
     */
    u16 calculate_checksum(u32 shift) const
    {
        return (0x83CF << shift) ^ ((unk08 + (unk00.raw + unk04)) ^ (unk02 + (unk06 + unk0a)));
    }
    /**
     * @brief Calculate the checksum of the six halfwords with the stored shift.
     * @return Calculated checksum.
     */
    u16 calculate_checksum() const
    {
        return (0x83CF << checksum_shift) ^ ((unk08 + (unk00.raw + unk04)) ^ (unk02 + (unk06 + unk0a)));
    }
    /**
     * @brief Clear the record, choose its checksum shift and store the checksum.
     * @param key Fixed shift to use instead of a random one, or null.
     */
    void reset(const u8* key)
    {
        *(unsigned __int128*)this = 0;
        checksum_shift = func_0010CF80() & 3;
        if (key != 0)
        {
            checksum_shift = *key;
        }
        checksum = calculate_checksum(checksum_shift);
    }
    /**
     * @brief Test whether the stored checksum differs from the record contents.
     * @return True when the checksum differs.
     */
    bool invalid() const
    {
        return checksum != calculate_checksum();
    }
    /**
     * @brief Read the ten-bit allocation value from a valid record.
     * @return Packed value, or zero when the checksum differs.
     */
    u16 value()
    {
        if (invalid())
        {
            return 0;
        }
        return unk00.bits.value;
    }
};


/** Twelve-byte category record used by the runtime catalog. */
struct ShopRuntimeRecord
{
    u16 unk00;
    u16 unk02;
    u8 unk04[4];
    u8 unk08;
    u8 unk09[2];
    u8 flags;
};

/** Partial runtime catalog containing category records. */
struct ShopRecordState
{
    u8 unk00[0xEA60];
    ShopRuntimeRecord records[750];
};

/** Four packed panel colors copied as one aligned block. */
union ShopPanelColors
{
    unsigned __int128 packed;
    LibWidgetColors4C5590 colors;
} __attribute__((aligned(16)));
extern "C" const ShopPanelColors D_00351FA0;
extern "C" const ShopPanelColors D_00351FB0;
extern "C" const ShopPanelColors D_00351FC0;

/** Partial resource runtime containing the selected slot and display code. */
struct FieldRuntime
{
    u8 unk00[0x514];
    s32 unk514;
    u32 unk518;
    s32 unk51c;
    u32 unk520;
};

struct ShopRuntimeFlags
{
    u8 unk00[0x81];
    u8 unk81;
    u8 unk82[0x13E];
    s32 unk1c0;
};

typedef struct ShopCallbacks
{
    u8 unk00[0x14];
    ShopState* unk14;
} ShopCallbacks;
typedef struct ShopRuntime
{
    ResidentCheckedRecord* unk00;
    u8 unk04[0xC];
    ShopCallbacks* unk10;
    u8 unk14[0x8];
    void* unk1c;
    FieldBufferSlots* unk20;
} ShopRuntime;
/**
 * @brief Remove the window from its runtime context.
 * @param context Runtime window context.
 * @param window Window to remove.
 */
extern "C" void func_002CFE10(ShopCallbacks* context, FieldClass15AE70* window);
// Resident runtime interface, scoped to this overlay.
extern ShopRuntime* D_001B643C;
extern ResidentObjectQueue* D_001B65F4;
extern float D_001B6690;
extern ShopRecordState* D_001B64F8;

// This Field overlay interface has no recovered declaration in its owning header.
extern "C" void func_002CE220(FieldStateCE420* object, s32 count, s32 offset, s32 selected);
extern "C" s32 func_002FA620(FieldHalfwordBuckets* buckets, s16 identifier);
extern "C" s32 func_002FAB70(FieldHalfwordBuckets* buckets, u8 category, u8 value);
extern "C" s32 func_002F9C90(FieldHalfwordBuckets* buckets, s16 identifier);
extern "C" void func_002F9FD0(FieldHalfwordBuckets* buckets);

/**
 * @brief Return the saved runtime section containing the shop flags.
 * @return Runtime flag section selected by directory key 4.
 */
static inline ShopRuntimeFlags* shop_runtime_flags()
{
    return reinterpret_cast<ShopRuntimeFlags*>(func_00101440(func_00101290(func_0010D8E0()), 4));
}

/**
 * @brief Read a masked runtime flag as a byte-valued truth value.
 * @param mask Flag bits to test.
 * @return One when any requested bit is set, zero otherwise.
 */
static inline u8 shop_runtime_flag(u8 mask)
{
    return (shop_runtime_flags()->unk81 & mask) != 0;
}

/**
 * @brief Clear selected bits in the runtime flag byte.
 * @param mask Flag bits to clear.
 */
static inline void clear_shop_runtime_flag(u32 mask)
{
    ShopRuntimeFlags* flags = shop_runtime_flags();
    flags->unk81 = flags->unk81 & ~mask;
}


/**
 * @brief Find the runtime catalog record for a one-based code.
 * @param state Runtime catalog.
 * @param code One-based category code.
 * @return Selected record, or null when the code is out of range.
 */
static inline ShopRuntimeRecord* shop_record(ShopRecordState* state, u16 code)
{
    u8 valid = code > 0 && code < 751;
    if (valid)
    {
        return &state->records[code - 1];
    }
    return 0;
}

/**
 * @brief Set the numeric widget value and mark it for redraw.
 * @param object Numeric widget.
 * @param number Value to display.
 */
static inline void set_shop_number(LibObject174F20* object, s32 number)
{
    object->numeric_value = number;
    object->unk3c = 1;
}

// These Field bucket interfaces have no declarations in their owning header.
/** @brief Add the encoded record to the buckets. @param object Bucket storage. @param code Encoded value whose low halfword selects the record. @return One on success, or zero when the record cannot be added. */
extern "C" s32 func_002FA3B0(FieldHalfwordBuckets* object, u32 code);
/** @brief Remove the encoded record from the buckets. @param object Bucket storage. @param code Encoded value whose low halfword selects the record. @return One on success, or zero when the record cannot be removed. */
extern "C" s32 func_002FA2A0(FieldHalfwordBuckets* object, u32 code);

// These Field list interfaces have no declarations in their owning header.
extern "C" void func_002CD7C0(void* object);
extern "C" void func_002CD8B0(void* object, void* element, u32 color);
ShopClass187A70::~ShopClass187A70()
{
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

/**
 * @brief Store the opaque source word.
 * @param value Word to store.
 */
void FieldClass15AE70::func_slot50(u32 value)
{
    unk04 = value;
}

/**
 * @brief Return the stored resource source word.
 * @return Stored word.
 */
u32 FieldClass15AE70::func_slot54()
{
    return unk04;
}

/** @brief Return the nested display container. @return Stored container. */
LibObject178660* FieldClass15AE70::func_slot58()
{
    return unk10;
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

void func_00348610(void* object)
{
}

void func_00348620(void* object)
{
}

void func_00348630(void* object)
{
}

void func_00348640(void* object)
{
}

void func_00348650(void* object)
{
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

s32 func_003486D0(void* object)
{
    return 0;
}

s32 func_003486E0(void* object)
{
    return 0;
}

s32 func_003486F0(void* object)
{
    return 0;
}

void func_00348700(void* object)
{
}

void func_00348710(void* object)
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

void func_00348740(void* object)
{
}

void ShopClass187A70::func_slot74()
{
    if (func_slot28())
    {
        return;
    }
    if (unka8->func_0023CDB0(2) == 1)
    {
        return;
    }
    if (unka8->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
}

void ShopClass187A70::func_slot70()
{
    if (func_slot28())
    {
        return;
    }
    if (unka8->func_0023CDB0(3) == 1)
    {
        return;
    }
    if (unka8->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
}

s32 func_003488D0(void* receiver)
{
    FieldClass15AE70* object = static_cast<FieldClass15AE70*>(receiver);
    if (object->func_slot28())
    {
        return 0;
    }
    ShopState* state = D_001B643C->unk10->unk14;
    state->func_00263F50(object);
    state->func_00263C70(object->func_slot44());
    return 2;
}

void func_00348960(ObjectField20* object, u32 value)
{
    object->field_20 = value;
}

/**
 * @brief Apply the selected category records and return to the list.
 * @return Zero while locked, the alternate action result, or one after applying the choice.
 */
s32 ShopClass187A70::func_slotb0()
{
    ItemCreationAllocationRecord* records[100];
    if (func_slot28())
    {
        return 0;
    }
    if (unka8 != 0 && unka8->unk114 != 0)
    {
        return func_slotb4();
    }
    ShopState* state = D_001B643C->unk10->unk14;
    FieldHalfwordBuckets* buckets = &state->buckets;
    s32 count = func_0040CF90(D_001B64F8, records, state->unk326c);
    for (s32 i = 0; i < count; i++)
    {
        func_002F9C90(buckets, func_0040D890(records[i]));
    }
    func_00112400(D_001B65F8, 6, 0, 0, 127, 64, 0);
    func_0034A640(static_cast<ShopClass187DA0*>(func_slot44()));
    state->func_00263F50(this);
    state->func_00263F50(func_slot44());
    func_00350D00(state, 3);
    state->unk327c = 0;
    return 1;
}

/**
 * @brief Create the paired-choice window and its displays.
 * @param associated Full resource source word.
 * @return One after creating the displays.
 */
s32 ShopClass187A70::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 120.0f, 170.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 370.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_00351E80(&unk14, panel);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 370.0f, 48.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopPanelColors colors = D_00351FC0;
    func_4C5590(panel, &colors.colors);
    func_00351E80(&unk14, panel);
    LibObject178750* text = new (0) LibObject178750;
    text->func_004C7FE0(0.0f, 12.0f, 370.0f, 24.0f, static_cast<s32>(associated), 0x2EEE, 0);
    text->set_mode(1);
    func_004C6190(unk10, text);
    text = new (0) LibObject178750;
    text->func_004C7FE0(0.0f, 64.0f, 370.0f, 48.0f, static_cast<s32>(associated), 0x2EF0, 0);
    text->set_mode(1);
    func_004C6190(unk10, text);
    yes_label = new (0) LibObject178750;
    no_label = new (0) LibObject178750;
    yes_label->func_004C7FE0(115.0f, 132.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2EF1, 0);
    func_004C6190(unk10, yes_label);
    no_label->func_004C7FE0(210.0f, 132.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2EF2, 0);
    func_004C6190(unk10, no_label);
    unka8 = new (0) FieldObject23CEA0;
    unka8->func_0023CE80(2, 1);
    unka8->func_0023CE60(93.0f, 0.0f);
    unka8->unkF2 = 0;
    unka8->func_0023CF50(1, 222.0f, 302.0f);
    func_00351CD0(&unk74, unka8);
    if (unka8->unk114 != 0)
    {
        yes_label->set_color(0x808080);
        no_label->set_color(0x288080);
    }
    else
    {
        yes_label->set_color(0x288080);
        no_label->set_color(0x808080);
    }
    return 1;
}

void ShopClass187BA0::func_slot74()
{
    if (func_slot28())
    {
        return;
    }
    if (unka8->func_0023CDB0(2) == 1)
    {
        return;
    }
    if (unka8->unk114 != 0)
    {
        unkac->set_color(0x808080);
        unkb0->set_color(0x288080);
    }
    else
    {
        unkac->set_color(0x288080);
        unkb0->set_color(0x808080);
    }
}

void ShopClass187BA0::func_slot70()
{
    if (func_slot28())
    {
        return;
    }
    if (unka8->func_0023CDB0(3) == 1)
    {
        return;
    }
    if (unka8->unk114 != 0)
    {
        unkac->set_color(0x808080);
        unkb0->set_color(0x288080);
    }
    else
    {
        unkac->set_color(0x288080);
        unkb0->set_color(0x808080);
    }
}

s32 func_00349110(void* receiver)
{
    FieldClass15AE70* object = static_cast<FieldClass15AE70*>(receiver);
    if (object->func_slot28())
    {
        return 0;
    }
    ShopState* state = D_001B643C->unk10->unk14;
    state->func_00263F50(object);
    state->func_00263C70(object->func_slot44());
    return 2;
}

/**
 * @brief Apply the selected record and update the remaining choices.
 * @return Zero while locked, the alternate action result, or one after applying the choice.
 */
s32 ShopClass187BA0::func_slotb0()
{
    ItemCreationAllocationRecord* records[100];
    if (func_slot28())
    {
        return 0;
    }
    if (unka8 != 0 && unka8->unk114 != 0)
    {
        return func_slotb4();
    }
    ShopState* state = D_001B643C->unk10->unk14;
    func_002F9C90(&state->buckets, func_0040D890(state->unk327c));
    func_00112400(D_001B65F8, 6, 0, 0, 127, 64, 0);
    func_0034A640(static_cast<ShopClass187DA0*>(func_slot44()));
    state->func_00263F50(this);
    state->unk327c = 0;
    if (func_0040CF90(D_001B64F8, records, state->unk326c) == 0)
    {
        state->func_00263F50(func_slot44());
        func_00350D00(state, 3);
    }
    else
    {
        state->func_00263C70(func_slot44());
    }
    return 1;
}

/**
 * @brief Create the two-option choice window and its displays.
 * @param associated Full resource source word.
 * @return One after creating the displays.
 */
s32 ShopClass187BA0::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 140.0f, 170.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_00351E80(&unk14, panel);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 48.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopPanelColors colors = D_00351FB0;
    func_4C5590(panel, &colors.colors);
    func_00351E80(&unk14, panel);
    LibObject178750* text = new (0) LibObject178750;
    func_004C7FE0(text, static_cast<s32>(associated), 0x2EEE, 0, 0.0f, 12.0f, 320.0f, 24.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    text = new (0) LibObject178750;
    func_004C7FE0(text, static_cast<s32>(associated), 0x2EEF, 0, 0.0f, 64.0f, 320.0f, 48.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    unkac = new (0) LibObject178750;
    unkb0 = new (0) LibObject178750;
    func_004C7FE0(unkac, static_cast<s32>(associated), 0x2EF1, 0, 82.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkac);
    func_004C7FE0(unkb0, static_cast<s32>(associated), 0x2EF2, 0, 172.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkb0);
    unka8 = new (0) FieldObject23CEA0;
    unka8->func_0023CE80(2, 1);
    unka8->func_0023CE60(90.0f, 0.0f);
    unka8->unkF2 = 0;
    unka8->func_0023CF50(1, 212.0f, 302.0f);
    func_00351CD0(&unk74, unka8);
    if (unka8->unk114 != 0)
    {
        unkac->set_color(0x808080);
        unkb0->set_color(0x288080);
    }
    else
    {
        unkac->set_color(0x288080);
        unkb0->set_color(0x808080);
    }
    return 1;
}

void ShopClass187CA0::func_slot5c()
{
    ShopState* state = D_001B643C->unk10->unk14;
    func_0023CEA0(unka8, state->func_00261150() == this);
    D_001B643C->unk10->unk14->func_00261150();
}

u32 func_00349820(ObjectField20* object)
{
    return object->field_20;
}

void ShopClass187CA0::func_slot74()
{
    if (func_slot28())
    {
        return;
    }
    if (unka8->func_0023CDB0(2) == 1)
    {
        return;
    }
    if (unka8->unk114 != 0)
    {
        unkac->set_color(0x808080);
        unkb0->set_color(0x288080);
    }
    else
    {
        unkac->set_color(0x288080);
        unkb0->set_color(0x808080);
    }
}

void ShopClass187CA0::func_slot70()
{
    if (func_slot28())
    {
        return;
    }
    if (unka8->func_0023CDB0(3) == 1)
    {
        return;
    }
    if (unka8->unk114 != 0)
    {
        unkac->set_color(0x808080);
        unkb0->set_color(0x288080);
    }
    else
    {
        unkac->set_color(0x288080);
        unkb0->set_color(0x808080);
    }
}

s32 func_003499B0(void* receiver)
{
    FieldClass15AE70* object = static_cast<FieldClass15AE70*>(receiver);
    if (object->func_slot28())
    {
        return 0;
    }
    ShopState* state = D_001B643C->unk10->unk14;
    state->func_00263F50(object);
    state->func_00263C70(object->func_slot44());
    return 2;
}

/**
 * @brief Clear the selected bucket records and refresh the associated list.
 * @return Zero while locked, the alternate action result, or one after applying the choice.
 */
s32 ShopClass187CA0::func_slotb0()
{
    if (func_slot28())
    {
        return 0;
    }
    if (unka8 != 0 && unka8->unk114 != 0)
    {
        return func_slotb4();
    }
    ShopState* state = D_001B643C->unk10->unk14;
    func_002F9FD0(&state->buckets);
    func_00112400(D_001B65F8, 6, 0, 0, 127, 64, 0);
    state->func_00263F50(this);
    void* window = func_slot44();
    func_0034CE00(window, 0);
    state->func_00263C70(window);
    return 1;
}

/**
 * @brief Create the focus-sensitive choice window and its displays.
 * @param associated Full resource source word.
 * @return One after creating the displays.
 */
s32 ShopClass187CA0::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 160.0f, 170.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_00351E80(&unk14, panel);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 48.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopPanelColors colors = D_00351FA0;
    func_4C5590(panel, &colors.colors);
    func_00351E80(&unk14, panel);
    LibObject178750* text = new (0) LibObject178750;
    func_004C7FE0(text, static_cast<s32>(associated), 0x2EEC, 0, 0.0f, 12.0f, 320.0f, 24.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    text = new (0) LibObject178750;
    func_004C7FE0(text, static_cast<s32>(associated), 0x2EED, 0, 0.0f, 64.0f, 320.0f, 48.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    unkac = new (0) LibObject178750;
    unkb0 = new (0) LibObject178750;
    func_004C7FE0(unkac, static_cast<s32>(associated), 0x2EF1, 0, 82.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkac);
    func_004C7FE0(unkb0, static_cast<s32>(associated), 0x2EF2, 0, 172.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkb0);
    unka8 = new (0) FieldObject23CEA0;
    unka8->func_0023CE80(2, 1);
    unka8->func_0023CE60(80.0f, 0.0f);
    unka8->unkF2 = 0;
    unka8->func_0023CF50(0, 232.0f, 302.0f);
    unka8->unkad = 0;
    func_00351CD0(&unk74, unka8);
    if (unka8->unk114 != 0)
    {
        unkac->set_color(0x808080);
        unkb0->set_color(0x288080);
    }
    else
    {
        unkac->set_color(0x288080);
        unkb0->set_color(0x808080);
    }
    return 1;
}

/**
 * @brief Update the first four display pairs and the optional list controls.
 * @param value Value stored in the display flags using its low byte.
 * @param selected Value tested for zero and stored in the optional control flags.
 */
void ShopClass187DA0::func_slot10c(u32 value, u32 selected)
{
    first[0]->unk3f = value;
    second[0]->unk3f = value;
    first[1]->unk3f = value;
    second[1]->unk3f = value;
    first[2]->unk3f = value;
    second[2]->unk3f = value;
    first[3]->unk3f = value;
    second[3]->unk3f = value;
    if (extra != 0)
    {
        extra->unk3f = 1;
    }
    if (FieldClass15AE60::unk04 != 0)
    {
        FieldClass15AE60::unk04->unk3f = selected;
        if (selected != 0)
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->LibMovementState::unk30 = 128.0f;
            control->unk3c = 1;
        }
        else
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->LibMovementState::unk30 = 64.0f;
            control->unk3c = 1;
        }
    }
    if (FieldClass15AE60::unk00 != 0)
    {
        FieldClass15AE60::unk00->unk3f = selected;
    }
}

s32 func_0034A0A0(void* object)
{
    ShopState* state = D_001B643C->unk10->unk14;
    state->func_00263F50(object);
    func_00350D00(state, 3);
    return 2;
}

s32 func_0034A0F0(void* receiver)
{
    ShopState* state = D_001B643C->unk10->unk14;
    if (state->unk327c != 0)
    {
        ShopClass187A70* window = new (0) ShopClass187A70;
        window->func_slotf4(state->func_00263CC0());
        window->func_slot40(receiver);
        state->func_00263FD0(window);
        state->func_00263C70(window);
    }
    return 1;
}

u32 func_0034A1D0(ObjectField34* object)
{
    return object->field_34;
}

s32 func_0034A1E0(void* receiver)
{
    ShopState* state = D_001B643C->unk10->unk14;
    if (state->unk327c != 0)
    {
        ShopClass187BA0* window = new (0) ShopClass187BA0;
        window->func_slotf4(state->func_00263CC0());
        window->func_slot40(receiver);
        state->func_00263FD0(window);
        state->func_00263C70(window);
    }
    return 1;
}

/**
 * @brief Resize the selection control for focus and show the selected allocation's detail values.
 */
void ShopClass187DA0::func_slot5c()
{
    ItemCreationAllocationRecord* records[100];
    if (D_001B643C->unk10->unk14->func_00261150() == this)
    {
        LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        control->LibMovementState::unk30 = 128.0f;
        control->unk3c = 1;
    }
    else
    {
        LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        control->LibMovementState::unk30 = 64.0f;
        control->unk3c = 1;
        return;
    }
    func_002CD7C0(this);
    ShopState* state = D_001B643C->unk10->unk14;
    s32 count = func_0040CF90(D_001B64F8, records, state->unk326c);
    s32 selection = FieldClass15AE60::unk24;
    if (count != 0 && selection >= 0)
    {
        s32 filled = 0;
        for (s32 i = 0; i < 8; i++)
        {
            u16 identifier = func_0040D930(records[selection], i);
            if (identifier != 0 && identifier != 700)
            {
                LibObject172440* number = third[filled];
                number->unkfc = identifier;
                number->unk3c = 1;
                third[filled]->unk3f = 1;
                filled++;
            }
        }
        for (; filled < 8; filled++)
        {
            third[filled]->unk3f = 0;
        }
        state->unk327c = records[selection];
        LibObject172410* icon = first[FieldClass15AE60::unk28];
        func_002CD8B0(this, icon, icon->unk94);
    }
    else
    {
        state->unk327c = 0;
        func_002CD8B0(this, 0, 0x808080);
    }
}

/**
 * @brief Set the positions and active flags of five display pairs.
 * @param position Base position before the first offset.
 */
void ShopClass187DA0::set_scroll_position(float position)
{
    s32 i = 0;
    float current = position + 16.0f;
    do
    {
        LibClass178600* first;
        LibClass178600* second;
        first = this->first[i];
        first->unk18.unk04 = current;
        first->unk3c = 1;
        second = this->second[i];
        second->unk18.unk04 = current;
        second->unk3c = 1;
        current += 28.0f;
        i++;
    } while (i < 5);
}

/**
 * @brief Populate five icon and number rows from the current category records.
 * @param offset First record to display.
 */
void ShopClass187DA0::refresh_rows(s32 offset)
{
    ItemCreationAllocationRecord* records[100];
    ShopState* state = D_001B643C->unk10->unk14;
    FieldHalfwordBuckets* buckets = &state->buckets;
    s32 category = state->unk326c;
    for (s32 i = 99; i >= 0; i--)
    {
        records[i] = 0;
    }
    this->FieldClass15AE60::unk88 = func_0040CF90(D_001B64F8, records, category);
    for (s32 i = 0; i < 5; i++)
    {
        if (records[offset + i] == 0)
        {
            this->first[i]->unk3d = 0;
            this->second[i]->unk3d = 0;
        }
        else
        {
            u16 identifier = category;
            u8 variant = records[offset + i]->unk0c & 0x7F;
            LibObject172410* icon = this->first[i];
            icon->unkfc = identifier;
            icon->unkfe = variant;
            icon->unk3c = 1;
            set_shop_number(this->second[i], func_002FA620(buckets, func_0040D890(records[offset + i])));
            this->first[i]->unk3d = 1;
            this->second[i]->unk3d = 1;
        }
    }
}

void func_0034A640(ShopClass187DA0* object)
{
    ItemCreationAllocationRecord* records[100];
    object->FieldClass15AE60::unk88 = 0;
    ShopState* state = D_001B643C->unk10->unk14;
    object->FieldClass15AE60::unk88 = func_0040CF90(D_001B64F8, records, state->unk326c);
    s32 count = object->FieldClass15AE60::unk88;
    s32 visible = count;
    if (visible >= 4)
    {
        visible = 4;
    }
    s32 offset = object->FieldClass15AE60::unk22;
    if (count < offset + 4)
    {
        offset = count - 4;
    }
    if (offset < 0)
    {
        offset = 0;
    }
    s32 selected = object->FieldClass15AE60::unk28;
    if (selected >= visible)
    {
        selected = visible - 1;
    }
    if (selected < 0)
    {
        selected = 0;
    }
    func_002CE420(&static_cast<FieldClass15AE60&>(*object), 1, visible, 378, 28);
    func_002CE220(&static_cast<FieldClass15AE60&>(*object), object->FieldClass15AE60::unk88, offset, selected);
}

/**
 * @brief Configure an item-code widget and its display rectangle.
 * @param object Item-code widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Display width.
 * @param height Display height.
 * @param code Encoded item code stored in the widget.
 * @param variation Encoded variation stored in the widget.
 * @param flag Display flag.
 * @return One on success, or zero if initialization fails.
 */
extern "C" s32 func_00413F70(LibObject172410* object, float x, float y, float width, float height, u16 code, u8 variation, u8 flag);
/**
 * @brief Set the icon flag and request a refresh.
 * @param object Item-code widget.
 * @param flag Flag to store.
 */
static inline void set_shop_icon_flag(LibObject172410* object, u8 flag)
{
    object->unkfa = flag;
    object->unk3c = 1;
}
/**
 * @brief Set the icon scalar and request a refresh.
 * @param object Item-code widget.
 * @param value Scalar to store.
 */
static inline void set_shop_icon_scalar(LibObject172410* object, float value)
{
    object->unk88 = value;
    object->unk3c = 1;
}
/**
 * @brief Configure the separator's display rectangle.
 * @param object Separator widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Display width.
 * @param height Display height.
 * @return One on success, or zero if its storage cannot be initialized.
 */
extern "C" s32 func_421170(ItemCreationClass172870* object, float x, float y, float width, float height);
/**
 * @brief Configure a detail-code widget and its display rectangle.
 * @param object Detail-code widget.
 * @param code Code to store.
 * @param variation Variation to store.
 * @param flag Display flag.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Display width.
 * @param height Display height.
 * @return One on success, or zero if initialization fails.
 */
extern "C" s32 func_4143F0(LibObject172440* object, u16 code, u8 variation, u8 flag, float x, float y, float width, float height);
s32 ShopClass187DA0::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 36.0f, 88.0f, 15);
    FieldClass15AE60::unk3c = 1;
    LibClass1746A0* frame = new (0) LibClass1746A0;
    LibClass1746A0* second_frame = new (0) LibClass1746A0;
    extra = new (0) LibClass178630;
    func_004C5A80(extra, 1, 0.0f, 0.0f, 568.0f, 340.0f, 88.0f);
    func_004C6190(unk10, extra);
    func_44B570(frame, 16.0f, 16.0f, 560.0f, 110.0f);
    func_004C6190(unk10, frame);
    for (s32 i = 0; i < 5; i++)
    {
        first[i] = new (0) LibObject172410;
        func_00413F70(first[i], 30.0f, 16.0f + 28.0f * i, 323.999969482421875f, 21.599998474121094f, 100, 0, 0);
        first[i]->set_scale(0.9f, 0.9f);
        set_shop_icon_flag(first[i], 1);
        set_shop_icon_scalar(first[i], -1.0f);
        first[i]->unk3f = 1;
        func_004C6190(unk10, first[i]);
        second[i] = new (0) LibObject174F20;
        second[i]->func_00464D90(490.0f, 12.0f + 30.0f * i, 28.0f, 24.0f, 0, 0, 1);
        func_004C6190(unk10, second[i]);
    }
    func_44B510(second_frame, 1);
    func_004C6190(unk10, second_frame);
    unk180 = new (0) ItemCreationClass172870;
    func_421170(unk180, 24.0f, 135.0f, 520.0f, 4.0f);
    ItemCreationClass172870* separator = unk180;
    separator->unk50 = 0xDC6464;
    separator->unk3c = 1;
    func_004C6190(unk10, unk180);
    FieldRuntime* runtime = D_001B657C;
    runtime->unk51c = static_cast<s32>(associated);
    runtime->unk520 = 0x11171;
    for (s32 i = 0; i < 8; i++)
    {
        third[i] = new (0) LibObject172440;
        func_4143F0(third[i], 0, 1, 0, 24.0f, 148 + 22 * i, 0.0f, 0.0f);
        LibObject172440* detail = third[i];
        detail->unk80 = 0.8f;
        detail->unk84 = 0.8f;
        detail->unk3c = 1;
        third[i]->unk3f = 0;
        func_004C6190(unk10, third[i]);
    }
    LibObject178750* first_label = new (0) LibObject178750;
    first_label->func_004C7FE0(435.0f, 270.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2F0A, 0);
    func_004C6190(unk10, first_label);
    LibObject178750* second_label = new (0) LibObject178750;
    second_label->func_004C7FE0(415.0f, 300.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2F0B, 0);
    func_004C6190(unk10, second_label);
    FieldClass15AE60::unk34 = 28.0f;
    FieldClass15AE60::unk38 = 28.0f;
    LibClass175030* movement = new (0) LibClass175030;
    FieldClass15AE60::unk04 = movement;
    func_00467360(static_cast<LibClass175030*>(FieldClass15AE60::unk04), 28.0f, 28.0f);
    func_004C6190(unk10, FieldClass15AE60::unk04);
    FieldClass15AE60::unk04->unk3f = 0;
    LibClass1725D0* indicator = new (0) LibClass1725D0;
    FieldClass15AE60::unk00 = indicator;
    func_41A930(static_cast<LibClass1725D0*>(FieldClass15AE60::unk00), 540.0f, 14.0f, 110.0f, 10.0f, 0.0f);
    FieldClass15AE60::unk00->unk3f = 0;
    func_004C6190(unk10, FieldClass15AE60::unk00);
    func_002CE420(&static_cast<FieldClass15AE60&>(*this), 1, 4, 378, 28);
    FieldClass15AE60::unk2b = 3;
    FieldClass15AE60::unk84 = 0;
    FieldClass15AE60::unk85 = 0;
    func_slot110(1);
    func_slot10c(1, 1);
    func_0034A640(this);
    return 1;
}

/** @brief Store the list byte at offset 0x12C. @param value Unsigned byte to store. */
void FieldClass15AD40::func_slot110(u8 value)
{
    FieldClass15AE60::unk84 = value;
}

/**
 * @brief Update the first five display pairs and the optional list controls.
 * @param value Value stored in the display flags using its low byte.
 * @param selected Value tested for zero and stored in the optional control flags.
 */
void ShopClass187EC0::func_slot10c(u32 value, u32 selected)
{
    first[0]->unk3f = value;
    second[0]->unk3f = value;
    first[1]->unk3f = value;
    second[1]->unk3f = value;
    first[2]->unk3f = value;
    second[2]->unk3f = value;
    first[3]->unk3f = value;
    second[3]->unk3f = value;
    first[4]->unk3f = value;
    second[4]->unk3f = value;
    if (extra != 0)
    {
        extra->unk3f = 1;
    }
    if (FieldClass15AE60::unk04 != 0)
    {
        FieldClass15AE60::unk04->unk3f = selected;
        if (selected != 0)
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->LibMovementState::unk30 = 128.0f;
            control->unk3c = 1;
        }
        else
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->LibMovementState::unk30 = 64.0f;
            control->unk3c = 1;
        }
    }
    if (FieldClass15AE60::unk00 != 0)
    {
        FieldClass15AE60::unk00->unk3f = selected;
    }
}

s32 func_0034AF50(void* object)
{
    func_00350B30(D_001B643C->unk10->unk14, 1);
    func_0034B3C0(object, 1);
    return 1;
}

s32 func_0034AFA0(void* object)
{
    func_00350B30(D_001B643C->unk10->unk14, -1);
    func_0034B3C0(object, 1);
    return 1;
}

s32 func_0034AFF0(void* object)
{
    ShopClass188400* toggle = D_001B643C->unk10->unk14->unk40;
    toggle->unkf8 = !toggle->unkf8;
    return 1;
}

s32 func_0034B020(void* object)
{
    func_00350D00(D_001B643C->unk10->unk14, 1);
    return 2;
}

s32 ShopClass187EC0::func_slotb0()
{
    ShopState* state = D_001B643C->unk10->unk14;
    if (FieldClass15AE60::unk88 != 0)
    {
        ShopClass187DA0* window = new (0) ShopClass187DA0;
        window->func_slot104(state->func_00263CC0());
        state->func_00263FD0(window);
        state->func_00263C70(window);
    }
    else
    {
        return 3;
    }
    return 1;
}

/** @brief Update the current catalog selection and its highlight. */
void ShopClass187EC0::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() == this)
    {
        LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        control->LibMovementState::unk30 = 128.0f;
        control->unk3c = 1;
    }
    else
    {
        LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        control->LibMovementState::unk30 = 64.0f;
        control->unk3c = 1;
        return;
    }
    func_002CD7C0(this);
    ShopState* state = D_001B643C->unk10->unk14;
    if (FieldClass15AE60::unk88 != 0)
    {
        state->unk326c = codes[FieldClass15AE60::unk24];
        LibObject172410* icon = first[FieldClass15AE60::unk28];
        func_002CD8B0(this, icon, icon->unk94);
    }
    else
    {
        state->unk326c = -1;
        func_002CD8B0(this, 0, 0x808080);
    }
}

/**
 * @brief Set the positions and active flags of six display pairs.
 * @param position Base position before the first offset.
 */
void ShopClass187EC0::set_scroll_position(float position)
{
    s32 i = 0;
    float current = position + 16.0f;
    do
    {
        LibClass178600* first;
        LibClass178600* second;
        first = this->first[i];
        first->unk18.unk04 = current;
        first->unk3c = 1;
        second = this->second[i];
        second->unk18.unk04 = current;
        second->unk3c = 1;
        current += 28.0f;
        i++;
    } while (i < 6);
}

/**
 * @brief Populate six catalog icon and number rows from the stored codes.
 * @param offset First stored code to display.
 */
void ShopClass187EC0::refresh_rows(s32 offset)
{
    for (s32 i = 0; i < 6; i++)
    {
        this->first[i]->unk3d = 0;
        this->second[i]->unk3d = 0;
        s32 code = this->codes[offset + i];
        if (code != 0)
        {
            u16 identifier = code;
            ShopRuntimeRecord* record = shop_record(D_001B64F8, identifier);
            if (record != 0)
            {
                u8 dimmed = record->flags & 0x04;
                u32 color = 0x808080;
                if (dimmed)
                {
                    color = 0x805050;
                }
                LibObject172410* icon = this->first[i];
                icon->unkfc = identifier;
                icon->unkfe = 0;
                icon->unk3c = 1;
                this->first[i]->set_color(color);
                this->first[i]->unk3d = 1;
                set_shop_number(this->second[i], record->unk08);
                this->second[i]->unk3d = 1;
            }
        }
    }
}

/**
 * @brief Find the catalog definition for a runtime category record.
 * @param record Runtime category record.
 * @return Definition selected by the record's catalog index.
 */
static inline ItemCreationCategoryDefinition* shop_category(const ShopRuntimeRecord* record)
{
    return &D_001B64F0[record->unk02];
}

/**
 * @brief Read a catalog definition's three-bit mode field.
 * @param record Catalog definition.
 * @return Mode stored in bits 4 through 6 of byte 0xB.
 */
static inline u8 shop_record_mode(const ItemCreationCategoryDefinition* record)
{
    return record->unk0b_mode;
}

void func_0034B3C0(void* receiver, u8 reset)
{
    ShopClass187EC0* object = static_cast<ShopClass187EC0*>(receiver);
    object->FieldClass15AE60::unk88 = 0;
    ShopState* state = D_001B643C->unk10->unk14;
    s32 count = 0;
    for (s32 code = 1; code <= 750; code++)
    {
        ShopRuntimeRecord* record = shop_record(D_001B64F8, code);
        if (record == 0)
        {
            continue;
        }
        ItemCreationCategoryDefinition* definition = shop_category(record);
        if (definition->unk17_flag || record->unk08 == 0)
        {
            continue;
        }
        if (state->unk3270 == 7)
        {
            object->codes[count++] = code;
        }
        else
        {
            u8 mode = shop_record_mode(definition);
            if (mode == state->unk3270)
            {
                object->codes[count++] = code;
            }
        }
    }
    object->FieldClass15AE60::unk88 = count;
    for (; count < 750; count++)
    {
        object->codes[count] = 0;
    }
    count = object->FieldClass15AE60::unk88;
    s32 visible = count >= 5 ? 5 : count;
    s32 offset = object->FieldClass15AE60::unk22;
    if (count < offset + 5)
    {
        offset = count - 5;
    }
    if (offset < 0)
    {
        offset = 0;
    }
    s32 selected = object->FieldClass15AE60::unk28;
    if (selected >= visible)
    {
        selected = visible - 1;
    }
    if (selected < 0)
    {
        selected = 0;
    }
    if (reset)
    {
        selected = 0;
        offset = 0;
    }
    func_002CE420(&static_cast<FieldClass15AE60&>(*object), 1, visible, 378, 28);
    func_002CE220(&static_cast<FieldClass15AE60&>(*object), object->FieldClass15AE60::unk88, offset, selected);
}

s32 ShopClass187EC0::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1800, 16.0f, 260.0f, 0.0f);
    FieldClass15AE60::unk3c = 1;
    LibClass1746A0* frame = new (0) LibClass1746A0;
    LibClass1746A0* second_frame = new (0) LibClass1746A0;
    extra = new (0) LibClass178630;
    func_004C5A80(extra, 1, 0.0f, 0.0f, 608.0f, 178.0f, 88.0f);
    func_004C6190(unk10, extra);
    func_44B570(frame, 16.0f, 16.0f, 580.0f, 140.0f);
    func_004C6190(unk10, frame);
    for (s32 i = 0; i < 6; i++)
    {
        first[i] = new (0) LibObject172410;
        func_00413F70(first[i], 30.0f, 16.0f + 28.0f * i, 323.999969482421875f, 21.599998474121094f, 100, 0, 0);
        first[i]->set_scale(0.9f, 0.9f);
        set_shop_icon_flag(first[i], 1);
        set_shop_icon_scalar(first[i], -1.0f);
        first[i]->unk3f = 1;
        func_004C6190(unk10, first[i]);
        second[i] = new (0) LibObject174F20;
        second[i]->func_00464D90(544.0f, 12.0f + 30.0f * i, 28.0f, 24.0f, 0, 0, 1);
        func_004C6190(unk10, second[i]);
    }
    func_44B510(second_frame, 1);
    func_004C6190(unk10, second_frame);
    FieldClass15AE60::unk34 = 28.0f;
    FieldClass15AE60::unk38 = 28.0f;
    LibClass175030* movement = new (0) LibClass175030;
    FieldClass15AE60::unk04 = movement;
    func_00467360(static_cast<LibClass175030*>(FieldClass15AE60::unk04), 28.0f, 28.0f);
    FieldClass15AE60::unk04->unk3f = 0;
    func_004C6190(unk10, FieldClass15AE60::unk04);
    LibClass1725D0* indicator = new (0) LibClass1725D0;
    FieldClass15AE60::unk00 = indicator;
    func_41A930(static_cast<LibClass1725D0*>(FieldClass15AE60::unk00), 580.0f, 14.0f, 145.0f, 10.0f, 0.0f);
    func_004C6190(unk10, FieldClass15AE60::unk00);
    FieldClass15AE60::unk00->unk3f = 0;
    func_002CE420(&static_cast<FieldClass15AE60&>(*this), 1, 5, 378, 28);
    FieldClass15AE60::unk2b = 3;
    FieldClass15AE60::unk84 = 0;
    FieldClass15AE60::unk85 = 0;
    func_slot10c(0, 0);
    return 1;
}

void ShopClass187FE0::func_slot5c()
{
    if (unke8 != 0 && func_002FD480(unke4))
    {
        if (unke4 != 0)
        {
            unke4->func_001DD7B0();
            unke4 = 0;
        }
        func_002CFE10(D_001B643C->unk10, this);
        func_00350D00(D_001B643C->unk10->unk14, 2);
        unke8 = 0;
    }
}

/**
 * @brief Request cancellation of the attached status window when present.
 * @return Always two.
 */
s32 ShopClass187FE0::func_slotb4()
{
    if (unke4 != 0)
    {
        func_002FD940(unke4);
        unke8 = 1;
    }
    return 2;
}

/**
 * @brief Configure the packed allocation record and its detail values.
 * @param record Allocation record to configure.
 * @param value Ten-bit allocation value.
 * @param channel Channel identifier.
 * @param values Eight detail values, or null for catalog defaults.
 * @param flag Packed record flag.
 * @param suppress_allocation_id Suppress the resident allocation identifier when the record checksum is valid.
 */
extern "C" void func_0040D2E0(ItemCreationAllocationRecord* record, u16 value, u8 channel,
                              const u16* values, bool flag, bool suppress_allocation_id);

/**
 * @brief Load a text resource into the multiline text widget.
 * @param object Multiline text widget.
 * @param slot Resource slot index.
 * @param key Resource key.
 * @param mode Drawing mode mask.
 * @param flag Flag whose low byte is stored by the widget.
 * @return Setup status.
 */
extern "C" s32 func_0045F690(LibObject174D90* object, u32 slot, s32 key, u32 mode, u32 flag);

/**
 * @brief Reset an allocation record and initialize it from a catalog record.
 * @param allocation Allocation record to initialize.
 * @param item Catalog record supplying the allocation value.
 * @param values Eight detail values, or null for catalog defaults.
 */
static inline void initialize_allocation(ItemCreationAllocationRecord* allocation, const ShopRuntimeRecord* item,
                                         const u16* values)
{
    allocation->reset(0);
    // TODO: The body of this check is a guess. The code only shows a compiled-out test on values.
    if (values != 0)
    {
        allocation->unk04 = values[0];
    }
    func_0040D2E0(allocation, item->unk02 + 1, 0, values, false, true);
}

/** Five vertical row positions; the last places the detail window footer. */
struct ShopFooterPositions
{
    float values[5];
};
extern "C" ShopFooterPositions D_00351F80;

/** Partial section record with the flag that selects the status window framing. */
struct ShopWindowSection
{
    u8 unk00[0x18C];
    u8 enabled;
};

/**
 * @brief Read the selected shop category.
 * @return Category index from the shop state.
 */
static inline s32 shop_selected_category()
{
    return D_001B643C->unk10->unk14->unk326c;
}

/**
 * @brief Store an item icon's code and request a refresh.
 * @param object Item icon widget.
 * @param code Item code to display.
 */
static inline void set_shop_icon_code(LibObject172410* object, u16 code)
{
    object->unkfc = code;
    object->unkfe = 0;
    object->unk3c = 1;
}

/**
 * @brief Create the item detail window's text, icon, value rows and status window.
 * @param associated Resource source word.
 * @return Always one.
 */
s32 ShopClass187FE0::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 2200, 28.0f, 87.0f, 0.0f);
    unke0 = new (0) LibObject178660;
    func_004C6510(unke0, 5, 0, 0, 28.0f, 87.0f, 0.0f);
    func_00465B20(D_001B657C, unke0);
    unkdc = new (0) LibClass178630;
    func_004C5A80(unkdc, 1, 0.0f, 0.0f, 584.0f, 369.0f, 88.0f);
    func_004C6190(unk10, unkdc);
    func_004C4AB0(unkdc, 1500.0f);
    s32 category = shop_selected_category();
    ItemCreationAllocationRecord allocation __attribute__((aligned(16)));
    allocation.reset(0);
    ShopRuntimeRecord* record = shop_record(D_001B64F8, category);
    initialize_allocation(&allocation, record, 0);
    unka8 = new (0) LibObject178750;
    unka8->func_004C7FE0(16.0f, 12.0f, 0.0f, 0.0f, associated, shop_record_mode(&D_001B64F0[allocation.value()]) + 0x2EF6, 0);
    LibObject178750* heading = unka8;
    heading->unk88 = -1.0f;
    heading->unk3c = 1;
    unka8->set_scale(0.8f, 0.8f);
    unka8->set_color(0x805050);
    unka8->set_mode(0);
    func_004C6190(unk10, unka8);
    unkac = new (0) LibObject172410;
    func_00413F70(unkac, 24.0f, 34.0f, 0.0f, 0.0f, associated, category + 50000, 0);
    set_shop_icon_scalar(unkac, -1.0f);
    unkac->set_scale(1.2f, 1.2f);
    set_shop_icon_code(unkac, allocation.value() + 1);
    func_004C6190(unk10, unkac);
    unkb0 = new (0) ItemCreationClass172870;
    func_421170(unkb0, 8.0f, 66.0f, 568.0f, 3.0f);
    ItemCreationClass172870* separator = unkb0;
    separator->unk50 = 0x606060;
    separator->unk3c = 1;
    func_004C6190(unk10, unkb0);
    unkb4 = new (0) LibObject178750;
    unkb4->func_004C7FE0(24.0f, 78.0f, 534.0f, 66.0f, static_cast<s32>(associated), category + 55000, 0);
    unkb4->set_mode(0);
    unkb4->set_vertical_alignment(1);
    LibObject178750* description = unkb4;
    description->unk88 = -1.0f;
    description->unk3c = 1;
    unkb4->set_scale(0.9f, 0.9f);
    func_004C6190(unke0, unkb4);
    unkb8 = new (0) LibObject178750;
    unkb8->func_004C7FE0(16.0f, 150.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2F0D, 0);
    unkb8->set_scale(0.8f, 0.8f);
    unkb8->set_color(0x805050);
    LibObject178750* values_heading = unkb8;
    values_heading->unk88 = -1.0f;
    values_heading->unk3c = 1;
    func_004C6190(unk10, unkb8);
    FieldRuntime* runtime = D_001B657C;
    runtime->unk51c = static_cast<s32>(associated);
    runtime->unk520 = 0x11171;
    for (s32 i = 0; i < 8; i++)
    {
        unkbc[i] = new (0) LibObject172440;
        func_4143F0(unkbc[i], 0, 1, 0, 26.0f, 172.0f + 23 * i, 0.0f, 0.0f);
        LibObject172440* value = unkbc[i];
        value->unk88 = -1.0f;
        value->unk3c = 1;
        unkbc[i]->set_scale(0.8f, 0.8f);
        unkbc[i]->unk3f = 0;
        func_004C6190(unke0, unkbc[i]);
    }
    s32 filled = 0;
    for (s32 i = 0; i < 8; i++)
    {
        u16 value = func_0040D930(&allocation, i);
        if (value != 0 && value != 700)
        {
            LibObject172440* number = unkbc[filled];
            number->unkfc = value;
            number->unk3c = 1;
            unkbc[filled]->unk3f = 1;
            filled++;
        }
    }
    ShopFooterPositions positions = D_00351F80;
    LibObject178750* footer = new (0) LibObject178750;
    footer->func_004C7FE0(12.0f, positions.values[4] - 8.0f, 560.0f, 24.0f, static_cast<s32>(associated), 0x2F0C, 0);
    footer->set_mode(2);
    func_004C6190(unke0, footer);
    s32 key = static_cast<u16>(D_001B64F0[record->unk02].unk10_code) + 0x88;
    unke8 = 0;
    unke4 = new (0) FieldClass15BB90;
    func_002FDC00(unke4, key);
    unke4->unk5b = 1;
    func_002FD220(unke4, D_001B643C->unk1c);
    func_002FD1D0(unke4);
    if (reinterpret_cast<ShopWindowSection*>(func_00101440(func_00101290(func_0010D8E0()), 1))->enabled != 0)
    {
        func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(unke4), 0.5235988f, 600.0f, 0.34906584f, 120.0f, 35.0f);
    }
    else
    {
        func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(unke4), 0.5235988f, 500.0f, 0.34906584f, 90.0f, 50.0f);
    }
    D_001B6614->func_004D74F0(unke4, reinterpret_cast<void*>(-1));
    return 1;
}

/** @brief Destroy the list receiver and its contained sentinel. */
LibClass178A70::~LibClass178A70()
{
}

void ShopClass187FE0::func_slot0c()
{
    unke0->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

ShopClass187FE0::~ShopClass187FE0()
{
    if (unkdc != 0)
    {
        func_004C4A90(unkdc);
    }
}

ShopClass187FE0::ShopClass187FE0()
{
    unka8 = 0;
    unkac = 0;
    unkb0 = 0;
    unkb4 = 0;
    unkb8 = 0;
    unkbc[0] = 0;
    unkbc[1] = 0;
    unkbc[2] = 0;
    unkbc[3] = 0;
    unkbc[4] = 0;
    unkbc[5] = 0;
    unkbc[6] = 0;
    unkbc[7] = 0;
    unkdc = 0;
    FieldClass15AE70();
}

/**
 * @brief Update the first five rows of six display columns and the optional controls.
 * @param value Value stored in the display flags using its low byte.
 * @param selected Value tested for zero and stored in the optional control flags.
 */
void ShopClass1880E0::func_slot10c(u32 value, u32 selected)
{
    s32 i = 0;
    value &= 0xFF;
    for (; i < 5; i++)
    {
        first[i]->unk3f = value;
        second[i]->unk3f = value;
        third[i]->unk3f = value;
        fourth[i]->unk3f = value;
        fifth[i]->unk3f = value;
        sixth[i]->unk3f = value;
    }
    if (extra != 0)
    {
        extra->unk3f = 1;
    }
    if (FieldClass15AE60::unk04 != 0)
    {
        FieldClass15AE60::unk04->unk3f = selected;
        if (selected != 0)
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->LibMovementState::unk30 = 128.0f;
            control->unk3c = 1;
        }
        else
        {
            LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
            control->LibMovementState::unk30 = 64.0f;
            control->unk3c = 1;
        }
    }
    if (FieldClass15AE60::unk00 != 0)
    {
        FieldClass15AE60::unk00->unk3f = selected;
    }
}

void ShopClass1880E0::func_slot74()
{
    ShopState* state = D_001B643C->unk10->unk14;
    FieldHalfwordBuckets* buckets = &state->buckets;
    if (func_002FA3B0(buckets, func_002FAB20(buckets, state->unk3270, FieldClass15AE60::unk24)))
    {
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
        refresh_rows(FieldClass15AE60::unk22);
    }
    else if (countdown < 0)
    {
        func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
        countdown = 30;
    }
}

void ShopClass1880E0::func_slot70()
{
    ShopState* state = D_001B643C->unk10->unk14;
    FieldHalfwordBuckets* buckets = &state->buckets;
    if (func_002FA2A0(buckets, func_002FAB20(buckets, state->unk3270, FieldClass15AE60::unk24)))
    {
        func_00112400(D_001B65F8, 0, 0, 0, 127, 64, 0);
        refresh_rows(FieldClass15AE60::unk22);
    }
    else if (countdown < 0)
    {
        func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
        countdown = 30;
    }
}

s32 func_0034CA50(void* object)
{
    func_00350B30(D_001B643C->unk10->unk14, 1);
    func_0034CE00(object, 0);
    return 1;
}

s32 func_0034CAA0(void* object)
{
    func_00350B30(D_001B643C->unk10->unk14, -1);
    func_0034CE00(object, 0);
    return 1;
}

s32 func_0034CAF0(void* object)
{
    ShopClass188400* toggle = D_001B643C->unk10->unk14->unk40;
    toggle->unkf8 = !toggle->unkf8;
    return 1;
}

s32 func_0034CB20(void)
{
    ShopState* state = D_001B643C->unk10->unk14;
    ShopClass187FE0* window = new (0) ShopClass187FE0;
    window->func_slotf4(state->func_00263CC0());
    state->func_00263FD0(window);
    state->func_00263C70(window);
    return 1;
}

s32 func_0034CBD0(void* object)
{
    ShopState* state = D_001B643C->unk10->unk14;
    func_002FA210(&state->buckets);
    func_00350D00(state, 1);
    return 2;
}

s32 func_0034CC10(void* receiver)
{
    ShopState* state = D_001B643C->unk10->unk14;
    if ((u16)(state->buckets.unk2f08 + state->buckets.unk2f0a))
    {
        ShopClass187CA0* window = new (0) ShopClass187CA0;
        window->func_slotf4(state->func_00263CC0());
        window->func_slot40(receiver);
        state->func_00263FD0(window);
        state->func_00263C70(window);
    }
    else
    {
        return 3;
    }
    return 1;
}

/** @brief Update the current bucket selection, highlight, and countdown. */
void ShopClass1880E0::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() == this)
    {
        LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        control->LibMovementState::unk30 = 128.0f;
        control->unk3c = 1;
    }
    else
    {
        LibClass175030* control = static_cast<LibClass175030*>(FieldClass15AE60::unk04);
        control->LibMovementState::unk30 = 64.0f;
        control->unk3c = 1;
        return;
    }
    func_002CD7C0(this);
    ShopState* state = D_001B643C->unk10->unk14;
    state->unk326c = func_002FAB20(&state->buckets, state->unk3270, FieldClass15AE60::unk24);
    if (FieldClass15AE60::unk24 >= 0)
    {
        LibObject172410* icon = first[FieldClass15AE60::unk28];
        func_002CD8B0(this, icon, icon->unk94);
    }
    if (countdown >= 0)
    {
        countdown--;
    }
}

/**
 * @brief Read the entry count for a valid bucket.
 * @param buckets Bucket storage.
 * @param category Bucket index.
 * @return Entry count, or zero when the index is out of range.
 */
static inline s32 shop_bucket_count(FieldHalfwordBuckets* buckets, u8 category)
{
    if (category < 8)
    {
        return buckets->buckets[category].count;
    }
    return 0;
}

void func_0034CE00(void* receiver, u8 reset)
{
    ShopClass1880E0* object = static_cast<ShopClass1880E0*>(receiver);
    object->FieldClass15AE60::unk88 = 0;
    ShopState* state = D_001B643C->unk10->unk14;
    FieldHalfwordBuckets* buckets = &state->buckets;
    object->FieldClass15AE60::unk88 = shop_bucket_count(buckets, state->unk3270);
    s32 count = object->FieldClass15AE60::unk88;
    s32 visible = count >= 5 ? 5 : count;
    s32 offset = object->FieldClass15AE60::unk22;
    if (count < offset + 5)
    {
        offset = count - 5;
    }
    if (offset < 0)
    {
        offset = 0;
    }
    s32 selected = object->FieldClass15AE60::unk28;
    if (selected >= visible)
    {
        selected = visible - 1;
    }
    if (selected < 0)
    {
        selected = 0;
    }
    if (reset)
    {
        selected = 0;
        offset = 0;
    }
    func_002CE420(&static_cast<FieldClass15AE60&>(*object), 1, visible, 378, 28);
    func_002CE220(&static_cast<FieldClass15AE60&>(*object), object->FieldClass15AE60::unk88, offset, selected);
}

/**
 * @brief Set the positions and active flags of six display columns.
 * @param position Base position before the first offset.
 */
void ShopClass1880E0::set_scroll_position(float position)
{
    s32 i = 0;
    float current = position + 16.0f;
    do
    {
        LibClass178600* element;
        element = this->first[i];
        element->unk18.unk04 = current;
        element->unk3c = 1;
        element = this->second[i];
        element->unk18.unk04 = current;
        element->unk3c = 1;
        element = this->third[i];
        element->unk18.unk04 = current;
        element->unk3c = 1;
        element = this->fourth[i];
        element->unk18.unk04 = current;
        element->unk3c = 1;
        element = this->fifth[i];
        element->unk18.unk04 = current;
        element->unk3c = 1;
        element = this->sixth[i];
        element->unk18.unk04 = current;
        element->unk3c = 1;
        current += 28.0f;
        i++;
    } while (i < 6);
}

// Resident bucket accessors are not yet declared by their owning header.
extern "C" s32 func_002FA870(FieldHalfwordBuckets* object, u16 code);
extern "C" s32 func_002FA7B0(FieldHalfwordBuckets* object, u16 code);

/**
 * @brief Read the stored byte for a one-based code.
 * @param buckets Bucket storage.
 * @param code One-based entry code.
 * @return Stored value, or zero when the code is out of range.
 */
static inline u8 shop_bucket_value(FieldHalfwordBuckets* buckets, s32 code)
{
    u8 result;
    u8 valid = code >= 1 && code < 751;
    if (valid)
    {
        result = buckets->unk2f0c[code - 1];
    }
    else
    {
        result = 0;
    }
    return result;
}

/**
 * @brief Refresh six rows of bucket icons and numeric values.
 * @param offset First bucket entry to display.
 */
void ShopClass1880E0::refresh_rows(s32 offset)
{
    ShopState* state = D_001B643C->unk10->unk14;
    FieldHalfwordBuckets* buckets = &state->buckets;
    for (s32 i = 0; i < 6; i++)
    {
        this->first[i]->unk3d = 0;
        this->second[i]->unk3d = 0;
        this->fourth[i]->unk3d = 0;
        this->third[i]->unk3d = 0;
        this->fifth[i]->unk3d = 0;
        this->sixth[i]->unk3d = 0;
        if (offset + i < shop_bucket_count(buckets, state->unk3270))
        {
            s32 code = func_002FAB20(buckets, state->unk3270, offset + i);
            ShopRuntimeRecord* record = shop_record(D_001B64F8, code);
            if (record != 0)
            {
                u8 dimmed = record->flags & 0x04;
                u32 color = 0x808080;
                if (dimmed)
                {
                    color = 0x808050;
                }
                LibObject172410* icon = this->first[i];
                icon->unkfc = code;
                icon->unkfe = 0;
                icon->unk3c = 1;
                this->first[i]->set_color(color);
                set_shop_number(this->second[i], func_002FA870(buckets, code));
                set_shop_number(this->fourth[i], shop_bucket_value(buckets, code));
                set_shop_number(this->sixth[i], func_002FA7B0(buckets, code));
                this->first[i]->unk3d = 1;
                this->second[i]->unk3d = 1;
                this->fourth[i]->unk3d = 1;
                this->fifth[i]->unk3d = 1;
                this->third[i]->unk3d = 1;
                this->sixth[i]->unk3d = 1;
            }
        }
    }
}

s32 ShopClass1880E0::func_slot104(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1800, 16.0f, 260.0f, 0.0f);
    FieldClass15AE60::unk3c = 1;
    LibClass1746A0* frame = new (0) LibClass1746A0;
    LibClass1746A0* second_frame = new (0) LibClass1746A0;
    extra = new (0) LibClass178630;
    func_004C5A80(extra, 1, 0.0f, 0.0f, 608.0f, 168.0f, 88.0f);
    func_004C6190(unk10, extra);
    func_44B570(frame, 16.0f, 16.0f, 580.0f, 140.0f);
    func_004C6190(unk10, frame);
    for (s32 i = 0; i < 6; i++)
    {
        first[i] = new (0) LibObject172410;
        func_00413F70(first[i], 30.0f, 16.0f + 28.0f * i, 323.999969482421875f, 21.599998474121094f, 100, 0, 0);
        first[i]->set_scale(0.9f, 0.9f);
        set_shop_icon_flag(first[i], 1);
        set_shop_icon_scalar(first[i], -1.0f);
        first[i]->unk3f = 1;
        func_004C6190(unk10, first[i]);
        second[i] = new (0) LibObject174F20;
        float y = 12.0f + 30.0f * i;
        second[i]->func_00464D90(360.0f, y, 126.0f, 24.0f, 0, 0, 0);
        func_004C6190(unk10, second[i]);
        third[i] = new (0) LibObject178750;
        third[i]->func_004C7FE0(486.0f, y, 0.0f, 0.0f, static_cast<s32>(associated), 0x2EEA, 1);
        func_004C6190(unk10, third[i]);
        fourth[i] = new (0) LibObject174F20;
        fourth[i]->func_00464D90(506.0f, y, 28.0f, 24.0f, 0, 0, 0);
        func_004C6190(unk10, fourth[i]);
        fifth[i] = new (0) LibObject178750;
        fifth[i]->func_004C7FE0(534.0f, y, 0.0f, 0.0f, static_cast<s32>(associated), 0x7E7, 1);
        func_004C6190(unk10, fifth[i]);
        sixth[i] = new (0) LibObject174F20;
        sixth[i]->func_00464D90(544.0f, y, 28.0f, 24.0f, 0, 0, 1);
        func_004C6190(unk10, sixth[i]);
    }
    func_44B510(second_frame, 1);
    func_004C6190(unk10, second_frame);
    FieldClass15AE60::unk34 = 28.0f;
    FieldClass15AE60::unk38 = 28.0f;
    LibClass175030* movement = new (0) LibClass175030;
    FieldClass15AE60::unk04 = movement;
    func_00467360(static_cast<LibClass175030*>(FieldClass15AE60::unk04), 28.0f, 28.0f);
    func_004C6190(unk10, FieldClass15AE60::unk04);
    FieldClass15AE60::unk04->unk3f = 0;
    LibClass1725D0* indicator = new (0) LibClass1725D0;
    FieldClass15AE60::unk00 = indicator;
    func_41A930(static_cast<LibClass1725D0*>(FieldClass15AE60::unk00), 580.0f, 14.0f, 145.0f, 10.0f, 0.0f);
    func_004C6190(unk10, FieldClass15AE60::unk00);
    FieldClass15AE60::unk00->unk3f = 0;
    func_002CE420(&static_cast<FieldClass15AE60&>(*this), 1, 5, 378, 28);
    FieldClass15AE60::unk2b = 3;
    FieldClass15AE60::unk84 = 0;
    FieldClass15AE60::unk85 = 0;
    func_slot10c(0, 0);
    return 1;
}

ShopClass1880E0::ShopClass1880E0()
{
    for (s32 i = 0; i < 6; i++)
    {
        first[i] = 0;
        second[i] = 0;
        fourth[i] = 0;
        sixth[i] = 0;
    }
    countdown = 0;
    FieldClass15AD40();
}

void func_0034D920(ShopValueDisplay* object)
{
    s32 value;
    ShopState* state = D_001B643C->unk10->unk14;
    ResidentCheckedRecord* record = D_001B643C->unk00;
    FieldHalfwordBuckets* buckets = &state->buckets;
    ItemCreationAllocationRecord* allocation = state->unk327c;
    u16 checksum = record->checksum;
    const u8* end = (const u8*)&record->checksum;
    if (checksum != func_00457470(record->checksum_seed, (u8*)record + 0x26, end - ((const u8*)record + 0x26)))
    {
        value = 0;
    }
    else
    {
        value = record->encoded_fol ^ 0x7CE3C7F7;
    }
    if (allocation != 0)
    {
        s32 count = func_002FA620(buckets, func_0040D890(allocation));
        s32 total = value + count;
        set_shop_number(object->second, count);
        if (total > 99999999)
        {
            total = 99999999;
        }
        set_shop_number(object->third, total);
    }
    else
    {
        s32 count = buckets->unk2f04;
        s32 total = value - count;
        set_shop_number(object->second, count);
        if (total < 0)
        {
            total = 0;
        }
        set_shop_number(object->third, total);
    }
    set_shop_number(object->first, value);
}


s32 ShopClass188200::func_slotf4(u32 associated)
{
    if (associated == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot14(associated, 0, 9, 2000, 16.0f, 428.0f, 0.0f);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 608.0f, 40.0f, 88.0f);
    func_004C6190(unk10, panel);
    LibObject178750* label = new (0) LibObject178750;
    label->func_004C7FE0(24.0f, 8.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2EE7, 1);
    func_004C6190(unk10, label);
    label = new (0) LibObject178750;
    label->func_004C7FE0(204.0f, 8.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2EE8, 1);
    func_004C6190(unk10, label);
    label = new (0) LibObject178750;
    label->func_004C7FE0(396.0f, 8.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2EE9, 1);
    func_004C6190(unk10, label);
    first = new (0) LibObject174F20;
    second = new (0) LibObject174F20;
    third = new (0) LibObject174F20;
    first->func_00464D90(64.0f, 8.0f, 126.0f, 24.0f, 0, 0, 0);
    func_004C6190(unk10, first);
    second->func_00464D90(260.0f, 8.0f, 126.0f, 24.0f, 0, 0, 0);
    func_004C6190(unk10, second);
    third->func_00464D90(464.0f, 8.0f, 126.0f, 24.0f, 0, 0, 0);
    func_004C6190(unk10, third);
    return 1;
}

void ShopClass188300::func_slot74()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(2) == 1)
    {
        return;
    }
}

void ShopClass188300::func_slot70()
{
    if (func_slot28())
    {
        return;
    }
    if (choice->func_0023CDB0(3) == 1)
    {
        return;
    }
}

s32 func_0034DEF0(void* receiver)
{
    FieldClass15AE70* object = static_cast<FieldClass15AE70*>(receiver);
    if (object->func_slot28())
    {
        return 0;
    }
    object->func_slot1c(255, 128);
    return 2;
}

s32 func_0034DF50(void* receiver)
{
    ShopClass188300* object = static_cast<ShopClass188300*>(receiver);
    if (object->func_slot28())
    {
        return 0;
    }
    func_00350D00(D_001B643C->unk10->unk14, object->choice->unk114 != 0 ? 3 : 2);
    return 1;
}

/**
 * @brief Set the choice grid height and mark its transform for update.
 * @param choice Choice grid.
 * @param height Height to store.
 */
static inline void set_shop_choice_height(FieldObject23CEA0* choice, float height)
{
    choice->FieldClass151C50::unk30 = height;
    choice->unkae = 1;
}
void ShopClass188300::func_slot5c()
{
    ShopState* state = D_001B643C->unk10->unk14;
    if (state->func_00261150() == this)
    {
        set_shop_choice_height(choice, 128.0f);
    }
    else
    {
        set_shop_choice_height(choice, 64.0f);
    }
    state->unk3278 = choice->unk114;
    if (choice != 0)
    {
        s16 selected = choice->unk114;
        if (first != 0)
        {
            if (selected == 0)
            {
                first->set_color(0x288080);
            }
            else
            {
                first->set_color(0x808080);
            }
        }
        if (second != 0)
        {
            if (selected == 1)
            {
                second->set_color(0x288080);
            }
            else
            {
                second->set_color(0x808080);
            }
        }
    }
    func_4C6DF0(text, state->func_00263CC0(), state->unk3270 + 0x2EF6, 0);
}

s32 ShopClass188300::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 2000, 16.0f, 220.0f, 0.0f);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 250.0f, 40.0f, 88.0f);
    func_004C6190(unk10, panel);
    first = new (0) LibObject178750;
    second = new (0) LibObject178750;
    func_004C7FE0(first, static_cast<s32>(associated), 0x2EE4, 1, 34.0f, 8.0f, 0.0f, 0.0f);
    func_004C7FE0(second, static_cast<s32>(associated), 0x2EE5, 1, 142.0f, 8.0f, 0.0f, 0.0f);
    func_004C6190(unk10, first);
    func_004C6190(unk10, second);
    choice = new (0) FieldObject23CEA0;
    choice->func_0023CE80(2, 1);
    choice->func_0023CE60(108.0f, 0.0f);
    choice->unkF2 = 0;
    choice->func_0023CF50(0, 40.0f, 224.0f);
    choice->func_0044B110(0, 9, 2000, 0, 0.0f);
    func_00351CD0(&unk74, choice);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 250.0f, 0.0f, 358.0f, 40.0f, 88.0f);
    func_004C6190(unk10, panel);
    unkb8 = new (0) LibClass174C40;
    func_4530E0(unkb8, 10, 280.0f, 3.0f);
    func_004C6190(unk10, unkb8);
    text = new (0) LibObject178750;
    func_004C7FE0(text, static_cast<s32>(associated), 0x2EF6, 1, 274.0f, 8.0f, 310.0f, 8.0f);
    text->set_color(0x508050);
    text->set_mode(1);
    func_004C6190(unk10, text);
    unkbc = new (0) LibClass174C40;
    func_4530E0(unkbc, 11, 554.0f, 3.0f);
    func_004C6190(unk10, unkbc);
    return 1;
}

ItemCreationClass175110::~ItemCreationClass175110()
{
}

void ShopClass188400::func_slot5c()
{
    ShopState* state = D_001B643C->unk10->unk14;
    if (state->unk326c >= 0)
    {
        if (unkf8 != 0)
        {
            unkac->unk3f = 0;
            unka8->unk3f = 0;
            unkb4->unk3f = 1;
            ItemCreationAllocationRecord allocation __attribute__((aligned(16)));
            allocation.reset(0);
            ShopRuntimeRecord* record = shop_record(D_001B64F8, state->unk326c);
            initialize_allocation(&allocation, record, 0);
            set_shop_number(numbers[0], D_001B64F0[allocation.value()].unk04_low);
            set_shop_number(numbers[1], D_001B64F0[allocation.value()].unk04_high);
            set_shop_number(numbers[2], D_001B64F0[allocation.value()].unk08_high);
            set_shop_number(numbers[3], D_001B64F0[allocation.value()].unk08_low);
            set_shop_number(numbers[4], D_001B64F0[allocation.value()].unk0c_low);
            for (s32 i = 0; i < 5; i++)
            {
                first[i]->unk3f = 1;
                second[i]->unk3f = 1;
                numbers[i]->unk3f = 1;
            }
        }
        else
        {
            s32 key = state->unk326c + 0x1294E;
            if (key != unkf4)
            {
                unkac->unk3f = 0;
                unka8->unk3f = 1;
                func_0045F690(unka8, func_slot54(), key, 8, 1);
                LibObject174D90* message = unka8;
                message->unk80 = 0.8f;
                message->unk84 = 0.8f;
                message->unk3c = 1;
            }
            for (s32 i = 0; i < 5; i++)
            {
                first[i]->unk3f = 0;
                second[i]->unk3f = 0;
                numbers[i]->unk3f = 0;
            }
            unkb4->unk3f = 0;
        }
        unkb0->unk3f = 1;
    }
    else
    {
        unkac->unk3f = 1;
        unka8->unk3f = 0;
        unkb0->unk3f = 0;
        unkb4->unk3f = 0;
        for (s32 i = 0; i < 5; i++)
        {
            first[i]->unk3f = 0;
            second[i]->unk3f = 0;
            numbers[i]->unk3f = 0;
        }
    }
}

s32 ShopClass188400::func_slotf4(u32 associated)
{
    if (associated == 0)
    {
        return 0;
    }
    FieldClass15AE70::func_slot14(associated, 0, 9, 1800, 220.0f, 80.0f, 0.0f);
    unk10->func_0044B110(0, 9, 1800, 100, 0.0f);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 404.0f, 140.0f, 88.0f);
    func_004C6190(unk10, panel);
    unka8 = new (0) LibObject174D90;
    unka8->func_00461720(32.0f, 13.0f, 362.0f, 140.0f, static_cast<s32>(associated), 0x2F08, 8, 0);
    LibObject174D90* multiline = unka8;
    multiline->unk52c = 0.0f;
    multiline->unk524 = 0.0f;
    func_004C6190(unk10, unka8);
    unka8->unk3f = 0;
    unkac = new (0) LibObject178750;
    unkac->func_004C7FE0(40.0f, 13.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2F08, 0);
    func_004C6190(unk10, unkac);
    unkac->unk3f = 0;
    unkb4 = new (0) LibObject178750;
    unkb4->func_004C7FE0(40.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2F0F, 0);
    unkb4->set_color(0x806080);
    unkb4->set_scale(0.75f, 0.75f);
    func_004C6190(unk10, unkb4);
    unkb4->unk3f = 0;
    for (s32 i = 0; i < 5; i++)
    {
        first[i] = new (0) LibObject178750;
        float y = 42.0f + static_cast<float>(28 * (i / 2));
        first[i]->func_004C7FE0(50.0f + static_cast<float>(190 * (i % 2)), y, 0.0f, 0.0f, static_cast<s32>(associated), 0x2F02 + i, 0);
        first[i]->set_color(0x805050);
        func_004C6190(unk10, first[i]);
        first[i]->unk3f = 0;
        second[i] = new (0) LibObject178750;
        second[i]->func_004C7FE0(100.0f + static_cast<float>(190 * (i % 2)), y, 0.0f, 0.0f, static_cast<s32>(associated), 0x2F07, 0);
        second[i]->set_color(0x805050);
        func_004C6190(unk10, second[i]);
        second[i]->unk3f = 0;
        numbers[i] = new (0) LibObject174F20;
        numbers[i]->func_00464D90(90.0f + static_cast<float>(190 * (i % 2)), y, 80.0f, 30.0f, 0, static_cast<s32>(associated), 1);
        func_004C6190(unk10, numbers[i]);
        numbers[i]->unk3f = 0;
    }
    unkb0 = new (0) LibObject178750;
    unkb0->func_004C7FE0(285.0f, 104.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x2F0E, 0);
    func_004C6190(unk10, unkb0);
    return 1;
}

/** Field record copy layout, with scalar statistics followed by a fifteen-word array. */
struct ShopRecordCopyView
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

/** Resource copy layout with the protected equipment identifiers, bound, check word and salt. */
struct ShopResourceCopyView
{
    u8 unk00[0xE];
    s16 count;
    s16 values[4];
    u8 unk18[0xD8];
    u32 check;
    u8 unkf4[0x18];
    u32 salt;
    u32 unk110;
};

/**
 * @brief Apply an allocation to copied record and resource data.
 * @param record Record copy to update.
 * @param resource Resource copy to update.
 * @param allocation Allocation record to apply.
 * @param index Statistic group to apply.
 */
extern "C" void func_003F9890(ShopRecordCopyView* record, ShopResourceCopyView* resource,
                              ItemCreationAllocationRecord* allocation, s32 index);

/**
 * @brief Decode a record's first protected statistic.
 * @param r Field record.
 * @return Decoded statistic, or zero when its check word is invalid.
 */
static inline s32 shop_first_statistic(const ShopRecordCopyView& r)
{
    if (r.unk84[4] != (r.unk84[9] ^ (r.unk3c ^ (r.unk34 + r.unk38))))
        return 0;
    return r.unk3c ^ 0x7DE3F7E3;
}

/**
 * @brief Decode a record's second protected statistic.
 * @param r Field record.
 * @return Decoded statistic, or zero when its check word is invalid.
 */
static inline s32 shop_second_statistic(const ShopRecordCopyView& r)
{
    if (r.unk84[5] != (r.unk84[9] ^ (r.unk48 ^ (r.unk40 + r.unk44))))
        return 0;
    return r.unk48 ^ 0x7DE3F7E3;
}

/**
 * @brief Validate the equipment identifier check word.
 * @param r Resource record.
 * @return True when the check word agrees with the identifiers and salt.
 */
static inline bool shop_resource_valid(const ShopResourceCopyView* r)
{
    return r->check == (r->salt ^ ((r->values[1] + r->values[2]) ^ (r->values[3] + r->values[0])));
}

/**
 * @brief Read a protected equipment identifier.
 * @param r Resource record.
 * @param index Equipment index.
 * @return Decoded identifier, or zero for an invalid check word or index.
 */
static inline s16 shop_equipped(const ShopResourceCopyView* r, s32 index)
{
    if (!shop_resource_valid(r))
        return 0;
    if (index < 0)
        return 0;
    if (index > (r->count ^ 0x7E93))
        return 0;
    return r->values[index] ^ 0x7E93;
}

/**
 * @brief Find an allocation record in resident storage.
 * @param index One-based allocation index.
 * @return Allocation record, or null outside one through three thousand.
 */
static inline ItemCreationAllocationRecord* shop_allocation_record(s16 index)
{
    ShopRecordState* base = D_001B64F8;
    u8 valid = index >= 1 && index <= 3000;
    if (valid)
        return reinterpret_cast<ItemCreationAllocationRecord*>(reinterpret_cast<u8*>(base) + (index - 1) * 16);
    return 0;
}

/**
 * @brief Set a resource widget's colour scale and request a redraw.
 * @param object Resource widget.
 * @param value Scale for all three colour channels.
 */
static inline void set_shop_resource_brightness(ItemCreationOptionResourceDisplay* object, float value)
{
    object->unk50.unk44 = value;
    object->unk50.unk48 = value;
    object->unk50.unk4c = value;
    object->unk3c = 1;
}

/**
 * @brief Calculate an allocation record's checksum for a given shift.
 * @param record Allocation record.
 * @param shift Two-bit shift applied to the checksum key.
 * @return Calculated checksum.
 */
static inline u16 shop_allocation_checksum(ItemCreationAllocationRecord* record, u32 shift)
{
    return (0x83CF << shift) ^
        ((record->unk08 + (record->unk00.raw + record->unk04)) ^ (record->unk02 + (record->unk06 + record->unk0a)));
}

/**
 * @brief Clear an allocation record, choose its checksum shift and store the checksum.
 * @param record Allocation record to reset.
 * @param key Fixed shift to use instead of a random one, or null.
 */
static inline void reset_shop_allocation(ItemCreationAllocationRecord* record, const u8* key)
{
    *(unsigned __int128*)record = 0;
    record->checksum_shift = func_0010CF80() & 3;
    if (key != 0)
    {
        record->checksum_shift = *key;
    }
    record->checksum = shop_allocation_checksum(record, record->checksum_shift);
}

/**
 * @brief Reset an allocation record and initialize it from a catalog record.
 * @param allocation Allocation record to initialize.
 * @param item Catalog record supplying the allocation value.
 */
static inline void initialize_shop_allocation(ItemCreationAllocationRecord* allocation, const ShopRuntimeRecord* item)
{
    reset_shop_allocation(allocation, 0);
    func_0040D2E0(allocation, item->unk02 + 1, 0, 0, false, true);
}

/**
 * @brief Get the shop state's record selection.
 * @param state Shop state.
 * @return Record selection.
 */
static inline FieldRecordSelection* shop_record_selection(ShopState* state)
{
    return &state->selection;
}

/**
 * @brief Read the ten-bit allocation value from a valid record.
 * @param record Allocation record.
 * @return Packed value, or zero when the checksum differs.
 */
static inline u16 shop_allocation_value(const ItemCreationAllocationRecord& record)
{
    u16 value = record.unk00.bits.value;
    if (record.checksum != (u16)((0x83CF << record.checksum_shift) ^
        ((record.unk08 + (*(u16*)&record + record.unk04)) ^ (record.unk02 + (record.unk06 + record.unk0a)))))
    {
        return 0;
    }
    return value;
}

/**
 * @brief Refresh the resource slot highlights and compare each member's statistic with the selected allocation applied.
 */
void ShopClass188500::func_slot5c()
{
    ShopState* state = D_001B643C->unk10->unk14;
    for (s32 i = 0; i < 8; i++)
    {
        ItemCreationOptionResourceDisplay* resource = resources[i];
        if (resource != 0)
        {
            set_shop_resource_brightness(resource, 128.0f);
        }
        labels[i]->unk3f = 0;
    }
    unkec += unkf0;
    if (unkec > 18)
    {
        unkf0 = -1;
    }
    if (unkec < 0)
    {
        unkf0 = 1;
    }
    if (state->unk326c >= 0)
    {
        const ShopRuntimeRecord* record = shop_record(D_001B64F8, state->unk326c);
        if (shop_record_mode(shop_category(record)) != 0 && shop_record_mode(shop_category(record)) != 1 &&
            shop_record_mode(shop_category(record)) != 2)
        {
            return;
        }
        ItemCreationAllocationRecord allocation __attribute__((aligned(16)));
        reset_shop_allocation(&allocation, 0);
        initialize_shop_allocation(&allocation, record);
        for (s32 i = 0; i < 8; i++)
        {
            bool found;
            s32 k;
            FieldRecordSelection* selection = shop_record_selection(state);
            FieldRecord* member = &selection->records[static_cast<s16>(i)];
            s8 slot = selection->slots[static_cast<s16>(i)];
            const ShopResourceCopyView* entry =
                &static_cast<const ShopResourceCopyView*>(selection->unk04)[static_cast<s16>(i)];
            if (slot <= 0)
            {
                continue;
            }
            s32 bit = 1 << (slot - 1);
            u16 mask = shop_category(record)->unk0c_mask;
            if (mask & bit)
            {
                found = false;
                for (k = 0; k < 4; k++)
                {
                    s16 identifier = shop_equipped(entry, k);
                    if (identifier > 0)
                    {
                        ItemCreationAllocationRecord* candidate = shop_allocation_record(identifier);
                        if (candidate != 0 &&
                            static_cast<u16>(candidate->value() + 1) == static_cast<u16>(shop_allocation_value(allocation) + 1))
                        {
                            found = true;
                            break;
                        }
                    }
                }
                if (found)
                {
                    func_4C6DF0(labels[i], state->func_00263CC0(), 0x2EFE, 0);
                    labels[i]->set_color(0xFF8028);
                    labels[i]->unk3f = 1;
                    continue;
                }
            }
            else
            {
                set_shop_resource_brightness(resources[i], 50.0f);
                labels[i]->unk3f = 0;
                continue;
            }
            const ShopRecordCopyView* original = reinterpret_cast<const ShopRecordCopyView*>(member);
            ShopRecordCopyView copy = *original;
            ShopResourceCopyView copy_entry = *entry;
            switch (shop_record_mode(shop_category(record)))
            {
            case 0:
                func_003F9890(&copy, &copy_entry, &allocation, 0);
                labels[i]->unk3f = 1;
                if (shop_first_statistic(copy) > shop_first_statistic(*original))
                {
                    func_4C6DF0(labels[i], state->func_00263CC0(), 0x2EFF, 0);
                    labels[i]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * unkec))) |
                    (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * unkec))) << 8) |
                    (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * unkec))) << 16));
                }
                else if (shop_first_statistic(copy) == shop_first_statistic(*original))
                {
                    func_4C6DF0(labels[i], state->func_00263CC0(), 0x2F01, 0);
                }
                else
                {
                    func_4C6DF0(labels[i], state->func_00263CC0(), 0x2F00, 0);
                    labels[i]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * unkec))) |
                    (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * unkec))) << 8) |
                    (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * unkec))) << 16));
                }
                break;
            case 1:
                func_003F9890(&copy, &copy_entry, &allocation, 1);
                labels[i]->unk3f = 1;
                if (shop_second_statistic(copy) > shop_second_statistic(*original))
                {
                    func_4C6DF0(labels[i], state->func_00263CC0(), 0x2EFF, 0);
                    labels[i]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * unkec))) |
                    (static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * unkec))) << 8) |
                    (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * unkec))) << 16));
                }
                else if (shop_second_statistic(copy) == shop_second_statistic(*original))
                {
                    func_4C6DF0(labels[i], state->func_00263CC0(), 0x2F01, 0);
                }
                else
                {
                    func_4C6DF0(labels[i], state->func_00263CC0(), 0x2F00, 0);
                    labels[i]->set_color(static_cast<u64>(static_cast<u8>(static_cast<s32>(80.0f + 2.6666667f * unkec))) |
                    (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * unkec))) << 8) |
                    (static_cast<u64>(static_cast<u8>(static_cast<s32>(40.0f + 2.2222223f * unkec))) << 16));
                }
                break;
            case 2:
                labels[i]->unk3f = 0;
                break;
            }
        }
    }
}

/**
 * @brief Create the window's resource slots and their labels for the selected records.
 * @param associated Resource source word.
 * @return One on success, or zero when no source word is given.
 */
s32 ShopClass188500::func_slotf4(u32 associated)
{
    if (associated == 0)
    {
        return 0;
    }
    unkec = 0;
    unkf0 = 1;
    FieldClass15AE70::func_slot14(associated, 0, 9, 2000, 16.0f, 68.0f, 0.0f);
    unk10->LibClass174610::func_0044B110(0, 9, 2000, 200, 0.0f);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 232.0f, 152.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopState* state = D_001B643C->unk10->unk14;
    FieldRecordSelection* selection;
    s32 resource;
    u16 column;
    u16 row;
    for (s32 i = 0; i < 8; i++)
    {
        selection = &state->selection;
        resource = static_cast<u16>(selection->slots[static_cast<s16>(i)]);
        // TODO: Unused read that only makes this match; look for the real source shape.
        FieldRecord* unused_record = &selection->records[static_cast<s16>(i)];
        column = i % 4;
        row = i / 4;
        if (resource != 0)
        {
            resources[i] = new (0) ItemCreationOptionResourceDisplay;
            void* allocation = func_002D3D80(D_001B643C->unk20, static_cast<u8>(resource));
            FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 4);
            resources[i]->unkcc = allocation;
            resources[i]->unkd0 = resource;
            resources[i]->func_002D6440(record, 20.0f + 50.0f * column, 12.0f + 68.0f * row);
            ItemCreationOptionResourceDisplay* widget = resources[i];
            widget->unk50.unk30 = 0.62f;
            widget->unk50.unk34 = 0.72f;
            widget->unk3c = 1;
            resources[i]->unk34 = 3;
            func_004C6190(unk10, resources[i]);
        }
        else
        {
            resources[i] = 0;
        }
        labels[i] = new (0) LibObject178750;
        labels[i]->func_004C7FE0(20.0f + 50.0f * column, 43.0f + (12.0f + 68.0f * row), 0.0f, 0.0f,
            static_cast<s32>(associated), 0x2EFE, 0);
        LibObject178750* label = labels[i];
        label->unk84 = 0.8f;
        label->unk80 = 0.8f;
        label->unk3c = 1;
        labels[i]->unk3f = 0;
        func_004C6190(unk10, labels[i]);
    }
    return 1;
}

void func_00350360(ShopScrollingWindow* object, s32 key)
{
    object->scrolling = 0;
    object->timer = 0;
    func_4C6DF0(object->text, object->func_slot54(), key + 0x2EE1, 1);
    object->width = (s32)func_004C69B0(object->text)->unk08 + 6;
    object->key = key;
}

void func_003503E0(ShopScrollingWindow* object)
{
    ShopState* state = D_001B643C->unk10->unk14;
    object->text->unk3d = 1;
    if (object->key != state->unk3278)
    {
        object->func_slot60(state->unk3278);
    }
    LibObject178750* text = object->text;
    float x = text->unk18.unk00;
    float y = text->unk18.unk04;
    float width = text->unk18.unk08;
    float height = text->unk18.unk0c;
    if (object->scrolling == 0)
    {
        text->unk18.unk00 = object->origin;
        text->unk18.unk04 = y;
        text->unk18.unk08 = width;
        text->unk18.unk0c = height;
        text->unk3c = 1;
        object->timer++;
        if (!((float)object->timer <= 120.0f))
        {
            object->timer = 0;
            object->scrolling = 1;
        }
        return;
    }
    float bound = object->bound;
    x -= 108.0f * D_001B6690;
    if (x < bound - (float)object->width)
    {
        x = 2.0f + (bound + object->extra);
    }
    text->unk18.unk00 = x;
    text->unk18.unk04 = y;
    text->unk18.unk08 = width;
    text->unk18.unk0c = height;
    text->unk3c = 1;
}

s32 ShopClass188600::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1400, 16.0f, 16.0f, 0.0f);
    text = new (0) LibObject178750;
    LibObject178750* caption = new (0) LibObject178750;
    LibClass1746A0* frame = new (0) LibClass1746A0;
    LibClass1746A0* second_frame = new (0) LibClass1746A0;
    if (text == 0 || frame == 0 || second_frame == 0)
    {
        return 0;
    }
    LibObject178750* label = new (0) LibObject178750;
    label->func_004C7FE0(16.0f, 6.0f, 0.0f, 0.0f, static_cast<s32>(associated), D_001B643C->unk10->unk14->unk3274 + 0x12924, 0);
    func_004C6190(unk10, label);
    label_width = func_004C69B0(label)->unk08;
    bound = 18.0f + label_width;
    float frame_padding = 32.0f;
    extra = 640.0f - (16.0f + (bound + frame_padding));
    origin = 24.0f + label_width;
    func_44B570(frame, bound, 0.0f, extra, 56.0f);
    func_004C6190(unk10, frame);
    func_00351DF0(&unk20, frame);
    func_004C7FE0(text, static_cast<s32>(associated), 0x2EE1, 0, bound, 6.0f, 0.0f, 0.0f);
    func_004C6190(unk10, text);
    text->unk3d = 0;
    func_00351D60(&unk2c, text);
    func_44B510(second_frame, 1);
    func_004C6190(unk10, second_frame);
    func_00351DF0(&unk20, second_frame);
    func_004C7FE0(caption, static_cast<s32>(associated), 0x2EE0, 0, 36.0f, 39.0f, 0.0f, 0.0f);
    caption->set_scale(0.65f, 0.65f);
    func_004C6190(unk10, caption);
    func_slot60(0);
    return 1;
}

s32 ShopClass188700::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 1200, 16.0f, 16.0f, 0.0f);
    ItemCreationOptionResourceDisplay* first = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* second = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* third = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = func_002D3D80(D_001B643C->unk20, 11);
    first->unkcc = allocation;
    second->unkcc = allocation;
    third->unkcc = allocation;
    first->unkd0 = 11;
    second->unkd0 = 11;
    third->unkd0 = 11;
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->unk20, 5);
    first->func_002D6440(record, 0.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 6);
    second->func_002D6440(record, 256.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 7);
    third->func_002D6440(record, 512.0f, 0.0f);
    func_004C6190(unk10, first);
    func_004C6190(unk10, second);
    func_004C6190(unk10, third);
    return 1;
}

void func_00350B30(ShopState* object, s32 direction)
{
    switch (object->unk3280)
    {
        case 2:
        {
            s32 attempts = 0;
            for (;;)
            {
                object->unk3270 += direction;
                if (object->unk3270 < 0)
                {
                    object->unk3270 = 7;
                }
                if (object->unk3270 >= 8)
                {
                    object->unk3270 = 0;
                }
                if (attempts >= 9)
                {
                    break;
                }
                if (shop_bucket_count(&object->buckets, object->unk3270) != 0)
                {
                    break;
                }
                attempts++;
            }
            break;
        }
        case 3:
        {
            s32 attempts = 0;
            for (;;)
            {
                object->unk3270 += direction;
                if (object->unk3270 < 0)
                {
                    object->unk3270 = 7;
                }
                if (object->unk3270 >= 8)
                {
                    object->unk3270 = 0;
                }
                if (attempts > 8)
                {
                    object->unk3270 = 7;
                    break;
                }
                s32 code;
                for (code = 1; code <= 750; code++)
                {
                    ShopRuntimeRecord* record = shop_record(D_001B64F8, code);
                    if (record != 0 && record->unk08 != 0 &&
                        (object->unk3270 == 7 || object->unk3270 == shop_record_mode(&D_001B64F0[record->unk02])))
                    {
                        break;
                    }
                }
                if (code <= 750)
                {
                    break;
                }
                attempts++;
            }
            break;
        }
        default:
            object->unk3270 = 7;
            break;
    }
}

void func_00350D00(ShopState* object, u32 mode)
{
    s32 previous = object->unk3280;
    object->unk3280 = mode;
    switch (object->unk3280)
    {
        case 1:
            object->unk48->func_slot20(0);
            object->unk4c->func_slot20(0);
            object->func_00263C70(object->unk44);
            object->unk326c = -1;
            object->unk3270 = 7;
            break;
        case 2:
            object->unk4c->func_slot20(0);
            object->unk48->func_slot20(1);
            object->unk48->func_slot110(1);
            object->unk48->func_slot10c(1, 1);
            func_0034CE00(object->unk48, previous != object->unk3280);
            object->func_00263C70(object->unk48);
            break;
        case 3:
            object->unk48->func_slot20(0);
            object->unk4c->func_slot20(1);
            object->unk4c->func_slot110(1);
            object->unk4c->func_slot10c(1, 1);
            func_0034B3C0(object->unk4c, previous != object->unk3280);
            object->func_00263C70(object->unk4c);
            break;
    }
}

void func_00350EC0(ShopState* object, u16 category)
{
    object->unk3274 = category;
    s32 value = 0;
    if (shop_runtime_flag(2))
    {
        value = 10;
    }
    if (shop_runtime_flag(4))
    {
        value = 20;
    }
    if (shop_runtime_flag(8))
    {
        value = 30;
    }
    if (shop_runtime_flags()->unk1c0 > 0)
    {
        value = 100;
    }
    func_002FAB70(&object->buckets, object->unk3274, value);
}

void func_00350FE0(ShopState* object)
{
    if (object->unk34 != 0)
    {
        func_00465430(D_001B657C, object->unk34);
    }
    func_004D65C0(object);
    object->func_001DD7B0();
    clear_shop_runtime_flag(2);
    clear_shop_runtime_flag(4);
    clear_shop_runtime_flag(8);
}

void func_003510B0(void* object)
{
    func_0011ED90(D_001B65F4, object);
}

s32 func_003510D0(void* receiver)
{
    ShopState* object = static_cast<ShopState*>(receiver);
    ShopClass188700* title = new (0) ShopClass188700;
    ShopClass188600* message = new (0) ShopClass188600;
    object->unk3c = new (0) ShopClass188500;
    object->unk40 = new (0) ShopClass188400;
    object->unk44 = new (0) ShopClass188300;
    object->unk48 = new (0) ShopClass1880E0;
    object->unk4c = new (0) ShopClass187EC0;
    object->unk50 = new (0) ShopClass188200;
    title->func_slotf4(object->unk34);
    object->FieldClass153E30::func_00263FD0(title);
    message->func_slotf4(object->unk34);
    object->FieldClass153E30::func_00263FD0(message);
    object->unk24 = message;
    message->func_slot40(title);
    object->unk3c->func_slotf4(object->unk34);
    object->FieldClass153E30::func_00263FD0(object->unk3c);
    object->unk40->func_slotf4(object->unk34);
    object->FieldClass153E30::func_00263FD0(object->unk40);
    object->unk44->func_slotf4(object->unk34);
    object->FieldClass153E30::func_00263FD0(object->unk44);
    object->unk48->func_slot104(object->unk34);
    object->FieldClass153E30::func_00263FD0(object->unk48);
    object->unk48->func_slot20(0);
    object->unk4c->func_slot104(object->unk34);
    object->FieldClass153E30::func_00263FD0(object->unk4c);
    object->unk4c->func_slot20(0);
    object->unk50->func_slotf4(object->unk34);
    object->FieldClass153E30::func_00263FD0(object->unk50);
    object->unk20 = object->unk44;
    object->unk38 = 1;
    func_00350D00(object, 1);
    return 1;
}

/** @brief Align a packed resource buffer. @param buffer Resource buffer. @return Aligned resource header. */
static inline ShopAlignedResource* aligned_shop_resource(void* buffer)
{
    return reinterpret_cast<ShopAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}
s32 func_00351460(void* receiver, void* buffer)
{
    ShopState* object = static_cast<ShopState*>(receiver);
    if (buffer == 0)
    {
        return 0;
    }
    ShopAlignedResource* aligned = aligned_shop_resource(buffer);
    s32 size = aligned->unk40 + 0x80;
    void* saved_heap = func_00100C90();
    void* heap = D_001B6430->context->unk70;
    void* memory = func_00113710(heap, size);
    if (memory != 0)
    {
        func_001134C0(memory);
        func_00100C80(heap);
    }
    object->unk34 = func_004656B0(D_001B657C, aligned);
    func_00100C80(saved_heap);
    FieldRuntime* runtime = D_001B657C;
    runtime->unk514 = object->unk34;
    runtime->unk518 = 0xC351;
    return object->func_00263CD0();
}

s32 func_00351540(u8* object)
{
    return func_28E3D0(object + 0x54) != 0;
}

/** @brief Initialize the shop controller and its record selection. */
ShopState::ShopState()
{
    unk34 = 0;
    unk38 = 0;
    unk3c = 0;
    unk40 = 0;
    unk44 = 0;
    unk48 = 0;
    unk4c = 0;
    unk50 = 0;
    unk326c = -1;
    unk3274 = -1;
    unk3278 = 0;
    unk327c = 0;
    unk3280 = 0;
    unk3270 = 7;
}

void func_003516A0(void* object)
{
}

void func_003516B0(void* object)
{
}

void func_003516C0(void* object)
{
}

ShopClass187BA0::~ShopClass187BA0()
{
}

ShopClass187CA0::~ShopClass187CA0()
{
}

ShopClass187DA0::~ShopClass187DA0()
{
}

void func_00351800(void* object)
{
}

void func_00351810(void* object)
{
}

ShopClass187EC0::~ShopClass187EC0()
{
}

s32 func_00351890(void* object)
{
    return 0;
}

ShopClass1880E0::~ShopClass1880E0()
{
}

ShopClass188200::~ShopClass188200()
{
}

s32 func_00351970(void* object)
{
    return 0;
}

ShopClass188300::~ShopClass188300()
{
}

ShopClass188400::~ShopClass188400()
{
}

ShopClass188500::~ShopClass188500()
{
}

ShopClass188600::~ShopClass188600()
{
}

ShopClass188700::~ShopClass188700()
{
}

/** @brief Destroy the record selection and Field controller base. */
ShopState::~ShopState()
{
}

u8 func_00351BD0(ObjectStatusFields* object)
{
    return object->field_38;
}

s32 func_00351BE0(void* object)
{
    return 4;
}

void func_00351BF0(ObjectStatusFields* object, u32 value)
{
    object->field_24 = value;
}

u32 func_00351C00(ObjectStatusFields* object)
{
    return object->field_24;
}

void func_00351C10(ObjectStatusFields* object, s8 value)
{
    object->field_28 = value;
}

s8 func_00351C20(ObjectStatusFields* object)
{
    return object->field_28;
}

s32 func_00351C30(void* object)
{
    return 0;
}

s32 func_00351C40(void* object)
{
    return 0;
}

void func_00351C50(void* object)
{
}

s32 func_00351C60(void* object)
{
    return 0;
}

void func_00351C70(void* object)
{
}

void func_00351C80(void* object)
{
}

void func_00351C90(void* object)
{
}

s32 func_00351CA0(void* object)
{
    return 0;
}

s32 func_00351CB0(void* object)
{
    return 0;
}

s32 func_00351CC0(void* object)
{
    return 0;
}

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void func_00351CD0(FieldCountedList* list, void* value)
{
    FieldListNode* node = static_cast<FieldListNode*>(func_00100AC0(sizeof(FieldListNode), 0));
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* tail = list->unk00;
        while (tail->unk04 != 0)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        list->unk04++;
    }
}

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void func_00351D60(FieldCountedList* list, void* value)
{
    FieldListNode* node = static_cast<FieldListNode*>(func_00100AC0(sizeof(FieldListNode), 0));
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* tail = list->unk00;
        while (tail->unk04 != 0)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        list->unk04++;
    }
}

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void func_00351DF0(FieldCountedList* list, void* value)
{
    FieldListNode* node = static_cast<FieldListNode*>(func_00100AC0(sizeof(FieldListNode), 0));
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* tail = list->unk00;
        while (tail->unk04 != 0)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        list->unk04++;
    }
}

/**
 * @brief Append a value after the list's sentinel node.
 * @param list List containing an existing sentinel and element count.
 * @param value Object pointer to append.
 */
void func_00351E80(FieldCountedList* list, void* value)
{
    FieldListNode* node = static_cast<FieldListNode*>(func_00100AC0(sizeof(FieldListNode), 0));
    if (node != 0)
    {
        node->unk00 = value;
        node->unk04 = 0;
        FieldListNode* tail = list->unk00;
        while (tail->unk04 != 0)
        {
            tail = tail->unk04;
        }
        tail->unk04 = node;
        list->unk04++;
    }
}
