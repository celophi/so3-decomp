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
extern "C" void func_2FD940(void* pointer);


/** Partial aligned resource header with the payload size. */
struct ShopAlignedResource
{
    u8 unk00[0x40];
    s32 unk40;
};

struct ObjectFields
{
    u8 unknown_0[0x4];
    u32 field_4;
    u8 field_8;
    u8 unknown_9;
    u16 field_a;
    u8 field_c;
    u8 field_d;
    u8 unknown_e[0x2];
    u32 field_10;
    u8 unknown_14[0x84];
    u32 field_98;
    u32 field_9c;
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

struct ObjectField12C
{
    u8 unknown_0[0x12C];
    u8 field_12c;
};

struct ObjectStatusFields
{
    u8 unknown_0[0x24];
    u32 field_24;
    s8 field_28;
    u8 unknown_29[0xF];
    u8 field_38;
};

typedef struct ObjectElement
{
    u8 unknown_0[0x1C];
    float position;
    u8 unknown_20[0x1C];
    u8 active;
    u8 visible;
    u8 unknown_3e;
    u8 field_3f;
    u8 unknown_40[0x30];
    float field_70;
} ObjectElement;

/** Partial icon display extending the common element fields. */
struct ShopIconElement : ObjectElement
{
    u8 unk74[0x20];
    u32 color;
    u8 unk98[0x64];
    u16 identifier;
    u8 variant;
};

/** Partial numeric display extending the common element fields. */
struct ShopNumberElement : ObjectElement
{
    u8 unk74[0x88];
    s32 number;
};

/** Partial allocation record containing the packed variant byte. */
struct ItemCreationAllocationRecord
{
    u8 unk00[0xC];
    u8 unk0c;
};

struct ObjectCleanup
{
    u8 unknown_0[0xE4];
    void* field_e4;
    u8 field_e8;
};

struct ObjectElements5
{
    u8 unknown_0[0xA8];
    FieldStateCE420 list;
    u8 unke8[0x48];
    s32 count;
    u8 unk134[4];
    ShopIconElement* first[5];
    ShopNumberElement* second[5];
};

struct ObjectElements6
{
    u8 unk00[0xA8];
    ObjectElement* control_a8;
    ObjectElement* control_ac;
    u8 unkb0[0x1C];
    s16 selection;
    u8 unkce[2];
    u8 row;
    u8 unkd1[0x5F];
    s32 count;
    u8 unk134[4];
    ShopIconElement* first[6];
    ShopNumberElement* second[6];
    u8 unk168[4];
    u16 codes[750];
};

struct ObjectElementsGrid6
{
    u8 unk00[0xA8];
    ObjectElement* control_a8;
    ObjectElement* control_ac;
    u8 unkb0[0x1C];
    s16 selection;
    u8 unkce[2];
    u8 row;
    u8 unkd1[0x67];
    ShopIconElement* first[6];
    ShopNumberElement* second[6];
    ShopNumberElement* third[6];
    ShopNumberElement* fourth[6];
    ShopNumberElement* fifth[6];
    ShopNumberElement* sixth[6];
    u8 unk1c8[4];
    s32 countdown;
};

struct ObjectToggleFields4
{
    u8 unknown_0[0xA8];
    ObjectElement* field_a8;
    ObjectElement* field_ac;
    u8 unknown_b0[0x88];
    ObjectElement* first[5];
    ObjectElement* second[5];
    u8 unknown_160[0x24];
    ObjectElement* extra;
};

struct ObjectToggleFields
{
    u8 unknown_0[0xA8];
    ObjectElement* field_a8;
    ObjectElement* field_ac;
    u8 unknown_b0[0x88];
    ObjectElement* first[6];
    ObjectElement* second[6];
    ObjectElement* third[6];
    ObjectElement* fourth[6];
    ObjectElement* fifth[6];
    ObjectElement* sixth[6];
    ObjectElement* seventh[6];
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

struct ShopListNode
{
    void* value;
    ShopListNode* next;
};
struct ShopList
{
    ShopListNode* head;
    s32 count;
};
/** Partial current shop state. */
struct ShopState : FieldClass153E30
{
    s32 unk34;
    u8 unk38;
    u8 unk39[3];
    ShopClass188500* unk3c;
    ShopClass188400* unk40;
    ShopClass188300* unk44;
    ShopClass1880E0* unk48;
    ShopClass187EC0* unk4c;
    ShopClass188200* unk50;
    u8 unk54[0x18];
    FieldHalfwordBuckets buckets;
    u8 unk3268[4];
    s32 unk326c;
    s32 unk3270;
    s32 unk3274;
    s32 unk3278;
    ItemCreationAllocationRecord* unk327c;
    u8 unk3280;
};
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
/** Partial resident record with an encoded value and checksum. */
struct ShopCheckedRecord
{
    u8 unk00[0x34];
    u32 unk34;
    u8 unk38[0x6C];
    u16 unka4;
    u16 unka6;
};

typedef struct ShopRuntime
{
    ShopCheckedRecord* unk00;
    u8 unk04[0xC];
    ShopCallbacks* unk10;
    u8 unk14[0xC];
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
 * @brief Set an icon's category and variant and mark it for redraw.
 * @param object Icon display.
 * @param identifier Category identifier.
 * @param variant Packed icon variant.
 */
static inline void set_shop_icon(ShopIconElement* object, u16 identifier, u8 variant)
{
    object->identifier = identifier;
    object->variant = variant;
    object->active = 1;
}
/**
 * @brief Set a numeric display's value and mark it for redraw.
 * @param object Numeric display.
 * @param number Number to display.
 */
static inline void set_shop_number(ShopNumberElement* object, s32 number)
{
    object->number = number;
    object->active = 1;
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
 * @brief Set an icon's color and mark it for redraw.
 * @param object Icon display.
 * @param color Packed color value.
 */
static inline void set_shop_color(ShopIconElement* object, u32 color)
{
    object->color = color;
    object->active = 1;
}

/**
 * @brief Set the numeric widget value and mark it for redraw.
 * @param object Numeric widget.
 * @param number Value to display.
 */
static inline void set_shop_number(LibObject174F20* object, s32 number)
{
    object->unkfc = number;
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
/**
 * @brief Set the list control height and mark it for redraw.
 * @param object List control display.
 * @param height Height to store.
 */
static inline void set_shop_height(ObjectElement* object, float height)
{
    object->field_70 = height;
    object->active = 1;
}

ShopClass187A70::~ShopClass187A70()
{
}

void func_00348460(ObjectFields* object, u8 value)
{
    object->field_c = value;
}

u8 func_00348470(ObjectFields* object)
{
    return object->field_c;
}

void func_00348480(ObjectFields* object, u8 value)
{
    object->field_8 = value;
}

u8 func_00348490(ObjectFields* object)
{
    return object->field_8;
}

void func_003484A0(ObjectFields* object, u16 value)
{
    object->field_a = value;
}

u16 func_003484B0(ObjectFields* object)
{
    return object->field_a;
}

void func_003484E0(ObjectFields* object, u32 value)
{
    object->field_9c = value;
}

u32 func_003484F0(ObjectFields* object)
{
    return object->field_9c;
}

void func_00348500(ObjectFields* object, u32 value)
{
    object->field_4 = value;
}

u32 func_00348510(ObjectFields* object)
{
    return object->field_4;
}

u32 func_00348520(ObjectFields* object)
{
    return object->field_10;
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

u8 func_00348720(ObjectFields* object)
{
    return object->field_d;
}

void func_00348730(ObjectFields* object, u8 value)
{
    object->field_d = value;
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
        unkac->set_color(0x808080);
        unkb0->set_color(0x288080);
    }
    else
    {
        unkac->set_color(0x288080);
        unkb0->set_color(0x808080);
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
        unkac->set_color(0x808080);
        unkb0->set_color(0x288080);
    }
    else
    {
        unkac->set_color(0x288080);
        unkb0->set_color(0x808080);
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
 * @param associated Associated resource handle.
 * @return One after creating the displays.
 */
s32 ShopClass187A70::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 120.0f, 170.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 370.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_00351E80(reinterpret_cast<ShopList*>(unk14), panel);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 370.0f, 48.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopPanelColors colors = D_00351FC0;
    func_4C5590(panel, &colors.colors);
    func_00351E80(reinterpret_cast<ShopList*>(unk14), panel);
    LibObject178750* text = new (0) LibObject178750;
    func_004C7FE0(text, reinterpret_cast<s32>(associated), 0x2EEE, 0, 0.0f, 12.0f, 370.0f, 24.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    text = new (0) LibObject178750;
    func_004C7FE0(text, reinterpret_cast<s32>(associated), 0x2EF0, 0, 0.0f, 64.0f, 370.0f, 48.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    unkac = new (0) LibObject178750;
    unkb0 = new (0) LibObject178750;
    func_004C7FE0(unkac, reinterpret_cast<s32>(associated), 0x2EF1, 0, 115.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkac);
    func_004C7FE0(unkb0, reinterpret_cast<s32>(associated), 0x2EF2, 0, 210.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkb0);
    unka8 = new (0) FieldObject23CEA0;
    unka8->func_0023CE80(2, 1);
    unka8->func_0023CE60(93.0f, 0.0f);
    unka8->unkF2 = 0;
    unka8->func_0023CF50(1, 222.0f, 302.0f);
    func_00351CD0(reinterpret_cast<ShopList*>(&unk74), unka8);
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
 * @param associated Associated resource handle.
 * @return One after creating the displays.
 */
s32 ShopClass187BA0::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 140.0f, 170.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_00351E80(reinterpret_cast<ShopList*>(unk14), panel);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 48.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopPanelColors colors = D_00351FB0;
    func_4C5590(panel, &colors.colors);
    func_00351E80(reinterpret_cast<ShopList*>(unk14), panel);
    LibObject178750* text = new (0) LibObject178750;
    func_004C7FE0(text, reinterpret_cast<s32>(associated), 0x2EEE, 0, 0.0f, 12.0f, 320.0f, 24.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    text = new (0) LibObject178750;
    func_004C7FE0(text, reinterpret_cast<s32>(associated), 0x2EEF, 0, 0.0f, 64.0f, 320.0f, 48.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    unkac = new (0) LibObject178750;
    unkb0 = new (0) LibObject178750;
    func_004C7FE0(unkac, reinterpret_cast<s32>(associated), 0x2EF1, 0, 82.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkac);
    func_004C7FE0(unkb0, reinterpret_cast<s32>(associated), 0x2EF2, 0, 172.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkb0);
    unka8 = new (0) FieldObject23CEA0;
    unka8->func_0023CE80(2, 1);
    unka8->func_0023CE60(90.0f, 0.0f);
    unka8->unkF2 = 0;
    unka8->func_0023CF50(1, 212.0f, 302.0f);
    func_00351CD0(reinterpret_cast<ShopList*>(&unk74), unka8);
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
 * @param associated Associated resource handle.
 * @return One after creating the displays.
 */
s32 ShopClass187CA0::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 160.0f, 170.0f, 14);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 176.0f, 88.0f);
    func_004C6190(unk10, panel);
    func_00351E80(reinterpret_cast<ShopList*>(unk14), panel);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 320.0f, 48.0f, 88.0f);
    func_004C6190(unk10, panel);
    ShopPanelColors colors = D_00351FA0;
    func_4C5590(panel, &colors.colors);
    func_00351E80(reinterpret_cast<ShopList*>(unk14), panel);
    LibObject178750* text = new (0) LibObject178750;
    func_004C7FE0(text, reinterpret_cast<s32>(associated), 0x2EEC, 0, 0.0f, 12.0f, 320.0f, 24.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    text = new (0) LibObject178750;
    func_004C7FE0(text, reinterpret_cast<s32>(associated), 0x2EED, 0, 0.0f, 64.0f, 320.0f, 48.0f);
    text->set_mode(1);
    func_004C6190(unk10, text);
    unkac = new (0) LibObject178750;
    unkb0 = new (0) LibObject178750;
    func_004C7FE0(unkac, reinterpret_cast<s32>(associated), 0x2EF1, 0, 82.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkac);
    func_004C7FE0(unkb0, reinterpret_cast<s32>(associated), 0x2EF2, 0, 172.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190(unk10, unkb0);
    unka8 = new (0) FieldObject23CEA0;
    unka8->func_0023CE80(2, 1);
    unka8->func_0023CE60(80.0f, 0.0f);
    unka8->unkF2 = 0;
    unka8->func_0023CF50(0, 232.0f, 302.0f);
    unka8->unkad = 0;
    func_00351CD0(reinterpret_cast<ShopList*>(&unk74), unka8);
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

void func_00349FF0(ObjectToggleFields4* object, u8 value, s32 selected)
{
    object->first[0]->field_3f = value;
    object->second[0]->field_3f = value;
    object->first[1]->field_3f = value;
    object->second[1]->field_3f = value;
    object->first[2]->field_3f = value;
    object->second[2]->field_3f = value;
    object->first[3]->field_3f = value;
    object->second[3]->field_3f = value;
    if (object->extra != 0)
    {
        object->extra->field_3f = 1;
    }
    if (object->field_ac != 0)
    {
        object->field_ac->field_3f = selected;
        if (selected != 0)
        {
            ObjectElement* control = object->field_ac;
            control->field_70 = 128.0f;
            control->active = 1;
        }
        else
        {
            ObjectElement* control = object->field_ac;
            control->field_70 = 64.0f;
            control->active = 1;
        }
    }
    if (object->field_a8 != 0)
    {
        object->field_a8->field_3f = selected;
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

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_0034A2C0);

void func_0034A480(ObjectElements5* object, float position)
{
    s32 i = 0;
    float current = position + 16.0f;
    do
    {
        ObjectElement* first;
        ObjectElement* second;
        first = object->first[i];
        first->position = current;
        first->active = 1;
        second = object->second[i];
        second->position = current;
        second->active = 1;
        current += 28.0f;
        i++;
    } while (i < 5);
}

void func_0034A4E0(ObjectElements5* object, s32 offset)
{
    ItemCreationAllocationRecord* records[100];
    ShopState* state = D_001B643C->unk10->unk14;
    FieldHalfwordBuckets* buckets = &state->buckets;
    s32 category = state->unk326c;
    for (s32 i = 99; i >= 0; i--)
    {
        records[i] = 0;
    }
    object->count = func_0040CF90(D_001B64F8, records, category);
    for (s32 i = 0; i < 5; i++)
    {
        if (records[offset + i] == 0)
        {
            object->first[i]->visible = 0;
            object->second[i]->visible = 0;
        }
        else
        {
            set_shop_icon(object->first[i], category, records[offset + i]->unk0c & 0x7F);
            set_shop_number(object->second[i], func_002FA620(buckets, func_0040D890(records[offset + i])));
            object->first[i]->visible = 1;
            object->second[i]->visible = 1;
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
 * @param code Encoded item code stored in the widget.
 * @param variation Encoded variation stored in the widget.
 * @param flag Display flag.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Display width.
 * @param height Display height.
 * @return One on success, or zero if initialization fails.
 */
extern "C" s32 func_00413F70(LibObject172410* object, u32 code, u32 variation, u8 flag, float x, float y, float width, float height);
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
s32 ShopClass187DA0::func_slot104(void* associated)
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
        func_00413F70(first[i], 100, 0, 0, 30.0f, 16.0f + 28.0f * i, 323.999969482421875f, 21.599998474121094f);
        first[i]->set_scale(0.9f, 0.9f);
        set_shop_icon_flag(first[i], 1);
        set_shop_icon_scalar(first[i], -1.0f);
        first[i]->unk3f = 1;
        func_004C6190(unk10, first[i]);
        second[i] = new (0) LibObject174F20;
        func_00464D90(second[i], 0, 0, 1, 490.0f, 12.0f + 30.0f * i, 28.0f, 24.0f);
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
    runtime->unk51c = reinterpret_cast<s32>(associated);
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
    first_label->func_004C7FE0(435.0f, 270.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2F0A, 0);
    func_004C6190(unk10, first_label);
    LibObject178750* second_label = new (0) LibObject178750;
    second_label->func_004C7FE0(415.0f, 300.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2F0B, 0);
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

void func_0034AE80(ObjectField12C* object, u8 value)
{
    object->field_12c = value;
}

void func_0034AE90(ObjectToggleFields* object, u8 value, s32 selected)
{
    object->first[0]->field_3f = value;
    object->second[0]->field_3f = value;
    object->first[1]->field_3f = value;
    object->second[1]->field_3f = value;
    object->first[2]->field_3f = value;
    object->second[2]->field_3f = value;
    object->first[3]->field_3f = value;
    object->second[3]->field_3f = value;
    object->first[4]->field_3f = value;
    object->second[4]->field_3f = value;
    if (object->third[0] != 0)
    {
        object->third[0]->field_3f = 1;
    }
    if (object->field_ac != 0)
    {
        object->field_ac->field_3f = selected;
        if (selected != 0)
        {
            ObjectElement* control = object->field_ac;
            control->field_70 = 128.0f;
            control->active = 1;
        }
        else
        {
            ObjectElement* control = object->field_ac;
            control->field_70 = 64.0f;
            control->active = 1;
        }
    }
    if (object->field_a8 != 0)
    {
        object->field_a8->field_3f = selected;
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

void func_0034B170(ObjectElements6* object)
{
    if (D_001B643C->unk10->unk14->func_00261150() == object)
    {
        set_shop_height(object->control_ac, 128.0f);
    }
    else
    {
        set_shop_height(object->control_ac, 64.0f);
        return;
    }
    func_002CD7C0(object);
    ShopState* state = D_001B643C->unk10->unk14;
    if (object->count != 0)
    {
        state->unk326c = object->codes[object->selection];
        ShopIconElement* icon = object->first[object->row];
        func_002CD8B0(object, icon, icon->color);
    }
    else
    {
        state->unk326c = -1;
        func_002CD8B0(object, 0, 0x808080);
    }
}

void func_0034B260(ObjectElements6* object, float position)
{
    s32 i = 0;
    float current = position + 16.0f;
    do
    {
        ObjectElement* first;
        ObjectElement* second;
        first = object->first[i];
        first->position = current;
        first->active = 1;
        second = object->second[i];
        second->position = current;
        second->active = 1;
        current += 28.0f;
        i++;
    } while (i < 6);
}

void func_0034B2C0(ObjectElements6* object, s32 offset)
{
    for (s32 i = 0; i < 6; i++)
    {
        object->first[i]->visible = 0;
        object->second[i]->visible = 0;
        s32 code = object->codes[offset + i];
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
                set_shop_icon(object->first[i], identifier, 0);
                set_shop_color(object->first[i], color);
                object->first[i]->visible = 1;
                set_shop_number(object->second[i], record->unk08);
                object->second[i]->visible = 1;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_0034B3C0);

s32 ShopClass187EC0::func_slot104(void* associated)
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
        func_00413F70(first[i], 100, 0, 0, 30.0f, 16.0f + 28.0f * i, 323.999969482421875f, 21.599998474121094f);
        first[i]->set_scale(0.9f, 0.9f);
        set_shop_icon_flag(first[i], 1);
        set_shop_icon_scalar(first[i], -1.0f);
        first[i]->unk3f = 1;
        func_004C6190(unk10, first[i]);
        second[i] = new (0) LibObject174F20;
        func_00464D90(second[i], 0, 0, 1, 544.0f, 12.0f + 30.0f * i, 28.0f, 24.0f);
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
    if (unke8 != 0 && func_002FD480(reinterpret_cast<const FieldStatus14*>(unke4)))
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

s32 func_0034BAB0(ObjectCleanup* object)
{
    if (object->field_e4 != 0)
    {
        func_2FD940(object->field_e4);
        object->field_e8 = 1;
    }
    return 2;
}

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_0034BB00);

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
    unkbc = 0;
    unkc0 = 0;
    unkc4 = 0;
    unkc8 = 0;
    unkcc = 0;
    unkd0 = 0;
    unkd4 = 0;
    unkd8 = 0;
    unkdc = 0;
    FieldClass15AE70();
}

void func_0034C7D0(ObjectToggleFields* object, s32 value, s32 selected)
{
    s32 i = 0;
    value &= 0xFF;
    for (; i < 5; i++)
    {
        object->first[i]->field_3f = value;
        object->second[i]->field_3f = value;
        object->third[i]->field_3f = value;
        object->fourth[i]->field_3f = value;
        object->fifth[i]->field_3f = value;
        object->sixth[i]->field_3f = value;
    }
    if (object->seventh[0] != 0)
    {
        object->seventh[0]->field_3f = 1;
    }
    if (object->field_ac != 0)
    {
        object->field_ac->field_3f = selected;
        if (selected != 0)
        {
            ObjectElement* control = object->field_ac;
            control->field_70 = 128.0f;
            control->active = 1;
        }
        else
        {
            ObjectElement* control = object->field_ac;
            control->field_70 = 64.0f;
            control->active = 1;
        }
    }
    if (object->field_a8 != 0)
    {
        object->field_a8->field_3f = selected;
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

void func_0034CD10(ObjectElementsGrid6* object)
{
    if (D_001B643C->unk10->unk14->func_00261150() == object)
    {
        set_shop_height(object->control_ac, 128.0f);
    }
    else
    {
        set_shop_height(object->control_ac, 64.0f);
        return;
    }
    func_002CD7C0(object);
    ShopState* state = D_001B643C->unk10->unk14;
    state->unk326c = func_002FAB20(&state->buckets, state->unk3270, object->selection);
    if (object->selection >= 0)
    {
        ShopIconElement* icon = object->first[object->row];
        func_002CD8B0(object, icon, icon->color);
    }
    if (object->countdown >= 0)
    {
        object->countdown--;
    }
}

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_0034CE00);

void func_0034CF20(ObjectElementsGrid6* object, float position)
{
    s32 i = 0;
    float current = position + 16.0f;
    do
    {
        ObjectElement* element;
        element = object->first[i];
        element->position = current;
        element->active = 1;
        element = object->second[i];
        element->position = current;
        element->active = 1;
        element = object->third[i];
        element->position = current;
        element->active = 1;
        element = object->fourth[i];
        element->position = current;
        element->active = 1;
        element = object->fifth[i];
        element->position = current;
        element->active = 1;
        element = object->sixth[i];
        element->position = current;
        element->active = 1;
        current += 28.0f;
        i++;
    } while (i < 6);
}

// Resident bucket accessors are not yet declared by their owning header.
extern "C" s32 func_002FA870(FieldHalfwordBuckets* object, u16 code);
extern "C" s32 func_002FA7B0(FieldHalfwordBuckets* object, u16 code);

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

void func_0034CFB0(ObjectElementsGrid6* object, s32 offset)
{
    ShopState* state = D_001B643C->unk10->unk14;
    FieldHalfwordBuckets* buckets = &state->buckets;
    for (s32 i = 0; i < 6; i++)
    {
        object->first[i]->visible = 0;
        object->second[i]->visible = 0;
        object->fourth[i]->visible = 0;
        object->third[i]->visible = 0;
        object->fifth[i]->visible = 0;
        object->sixth[i]->visible = 0;
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
                set_shop_icon(object->first[i], code, 0);
                set_shop_color(object->first[i], color);
                set_shop_number(object->second[i], func_002FA870(buckets, code));
                set_shop_number(object->fourth[i], shop_bucket_value(buckets, code));
                set_shop_number(object->sixth[i], func_002FA7B0(buckets, code));
                object->first[i]->visible = 1;
                object->second[i]->visible = 1;
                object->fourth[i]->visible = 1;
                object->fifth[i]->visible = 1;
                object->third[i]->visible = 1;
                object->sixth[i]->visible = 1;
            }
        }
    }
}

s32 ShopClass1880E0::func_slot104(void* associated)
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
        func_00413F70(first[i], 100, 0, 0, 30.0f, 16.0f + 28.0f * i, 323.999969482421875f, 21.599998474121094f);
        first[i]->set_scale(0.9f, 0.9f);
        set_shop_icon_flag(first[i], 1);
        set_shop_icon_scalar(first[i], -1.0f);
        first[i]->unk3f = 1;
        func_004C6190(unk10, first[i]);
        second[i] = new (0) LibObject174F20;
        float y = 12.0f + 30.0f * i;
        func_00464D90(second[i], 0, 0, 0, 360.0f, y, 126.0f, 24.0f);
        func_004C6190(unk10, second[i]);
        third[i] = new (0) LibObject178750;
        third[i]->func_004C7FE0(486.0f, y, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2EEA, 1);
        func_004C6190(unk10, third[i]);
        fourth[i] = new (0) LibObject174F20;
        func_00464D90(fourth[i], 0, 0, 0, 506.0f, y, 28.0f, 24.0f);
        func_004C6190(unk10, fourth[i]);
        fifth[i] = new (0) LibObject178750;
        fifth[i]->func_004C7FE0(534.0f, y, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x7E7, 1);
        func_004C6190(unk10, fifth[i]);
        sixth[i] = new (0) LibObject174F20;
        func_00464D90(sixth[i], 0, 0, 1, 544.0f, y, 28.0f, 24.0f);
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
    ShopCheckedRecord* record = D_001B643C->unk00;
    FieldHalfwordBuckets* buckets = &state->buckets;
    ItemCreationAllocationRecord* allocation = state->unk327c;
    u16 checksum = record->unka4;
    const u8* end = (const u8*)&record->unka4;
    if (checksum != func_00457470(record->unka6, (u8*)record + 0x26, end - ((const u8*)record + 0x26)))
    {
        value = 0;
    }
    else
    {
        value = record->unk34 ^ 0x7CE3C7F7;
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


s32 ShopClass188200::func_slotf4(void* associated)
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
    label->func_004C7FE0(24.0f, 8.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2EE7, 1);
    func_004C6190(unk10, label);
    label = new (0) LibObject178750;
    label->func_004C7FE0(204.0f, 8.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2EE8, 1);
    func_004C6190(unk10, label);
    label = new (0) LibObject178750;
    label->func_004C7FE0(396.0f, 8.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2EE9, 1);
    func_004C6190(unk10, label);
    first = new (0) LibObject174F20;
    second = new (0) LibObject174F20;
    third = new (0) LibObject174F20;
    func_00464D90(first, 0, 0, 0, 64.0f, 8.0f, 126.0f, 24.0f);
    func_004C6190(unk10, first);
    func_00464D90(second, 0, 0, 0, 260.0f, 8.0f, 126.0f, 24.0f);
    func_004C6190(unk10, second);
    func_00464D90(third, 0, 0, 0, 464.0f, 8.0f, 126.0f, 24.0f);
    func_004C6190(unk10, third);
    return 1;
}

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_0034DE30);

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_0034DE90);

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

s32 ShopClass188300::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot14(associated, 0, 9, 2000, 16.0f, 220.0f, 0.0f);
    LibClass178630* panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 0.0f, 0.0f, 250.0f, 40.0f, 88.0f);
    func_004C6190(unk10, panel);
    first = new (0) LibObject178750;
    second = new (0) LibObject178750;
    func_004C7FE0(first, reinterpret_cast<s32>(associated), 0x2EE4, 1, 34.0f, 8.0f, 0.0f, 0.0f);
    func_004C7FE0(second, reinterpret_cast<s32>(associated), 0x2EE5, 1, 142.0f, 8.0f, 0.0f, 0.0f);
    func_004C6190(unk10, first);
    func_004C6190(unk10, second);
    choice = new (0) FieldObject23CEA0;
    choice->func_0023CE80(2, 1);
    choice->func_0023CE60(108.0f, 0.0f);
    choice->unkF2 = 0;
    choice->func_0023CF50(0, 40.0f, 224.0f);
    choice->func_0044B110(0, 9, 2000, 0, 0.0f);
    func_00351CD0(reinterpret_cast<ShopList*>(&unk74), choice);
    panel = new (0) LibClass178630;
    func_004C5A80(panel, 0, 250.0f, 0.0f, 358.0f, 40.0f, 88.0f);
    func_004C6190(unk10, panel);
    unkb8 = new (0) LibClass174C40;
    func_4530E0(unkb8, 10, 280.0f, 3.0f);
    func_004C6190(unk10, unkb8);
    text = new (0) LibObject178750;
    func_004C7FE0(text, reinterpret_cast<s32>(associated), 0x2EF6, 1, 274.0f, 8.0f, 310.0f, 8.0f);
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

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_0034E630);

s32 ShopClass188400::func_slotf4(void* associated)
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
    unka8->func_00461720(32.0f, 13.0f, 362.0f, 140.0f, reinterpret_cast<s32>(associated), 0x2F08, 8, 0);
    LibObject174D90* multiline = unka8;
    multiline->unk52c = 0.0f;
    multiline->unk524 = 0.0f;
    func_004C6190(unk10, unka8);
    unka8->unk3f = 0;
    unkac = new (0) LibObject178750;
    unkac->func_004C7FE0(40.0f, 13.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2F08, 0);
    func_004C6190(unk10, unkac);
    unkac->unk3f = 0;
    unkb4 = new (0) LibObject178750;
    unkb4->func_004C7FE0(40.0f, 16.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2F0F, 0);
    unkb4->set_color(0x806080);
    unkb4->set_scale(0.75f, 0.75f);
    func_004C6190(unk10, unkb4);
    unkb4->unk3f = 0;
    for (s32 i = 0; i < 5; i++)
    {
        first[i] = new (0) LibObject178750;
        float y = 42.0f + static_cast<float>(28 * (i / 2));
        first[i]->func_004C7FE0(50.0f + static_cast<float>(190 * (i % 2)), y, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2F02 + i, 0);
        first[i]->set_color(0x805050);
        func_004C6190(unk10, first[i]);
        first[i]->unk3f = 0;
        second[i] = new (0) LibObject178750;
        second[i]->func_004C7FE0(100.0f + static_cast<float>(190 * (i % 2)), y, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2F07, 0);
        second[i]->set_color(0x805050);
        func_004C6190(unk10, second[i]);
        second[i]->unk3f = 0;
        numbers[i] = new (0) LibObject174F20;
        func_00464D90(numbers[i], 0, reinterpret_cast<s32>(associated), 1, 90.0f + static_cast<float>(190 * (i % 2)), y, 80.0f, 30.0f);
        func_004C6190(unk10, numbers[i]);
        numbers[i]->unk3f = 0;
    }
    unkb0 = new (0) LibObject178750;
    unkb0->func_004C7FE0(285.0f, 104.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2F0E, 0);
    func_004C6190(unk10, unkb0);
    return 1;
}

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_0034F350);

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_0034FEE0);

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

s32 ShopClass188600::func_slotf4(void* associated)
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
    label->func_004C7FE0(16.0f, 6.0f, 0.0f, 0.0f, reinterpret_cast<s32>(associated), D_001B643C->unk10->unk14->unk3274 + 0x12924, 0);
    func_004C6190(unk10, label);
    label_width = func_004C69B0(label)->unk08;
    bound = 18.0f + label_width;
    float frame_padding = 32.0f;
    extra = 640.0f - (16.0f + (bound + frame_padding));
    origin = 24.0f + label_width;
    func_44B570(frame, bound, 0.0f, extra, 56.0f);
    func_004C6190(unk10, frame);
    func_00351DF0(reinterpret_cast<ShopList*>(&unk20), frame);
    func_004C7FE0(text, reinterpret_cast<s32>(associated), 0x2EE1, 0, bound, 6.0f, 0.0f, 0.0f);
    func_004C6190(unk10, text);
    text->unk3d = 0;
    func_00351D60(reinterpret_cast<ShopList*>(&unk2c), text);
    func_44B510(second_frame, 1);
    func_004C6190(unk10, second_frame);
    func_00351DF0(reinterpret_cast<ShopList*>(&unk20), second_frame);
    func_004C7FE0(caption, reinterpret_cast<s32>(associated), 0x2EE0, 0, 36.0f, 39.0f, 0.0f, 0.0f);
    caption->set_scale(0.65f, 0.65f);
    func_004C6190(unk10, caption);
    func_slot60(0);
    return 1;
}

s32 ShopClass188700::func_slotf4(void* associated)
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
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(first)), record, 0.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 6);
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(second)), record, 256.0f, 0.0f);
    record = func_002D3CC0(D_001B643C->unk20, 7);
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(third)), record, 512.0f, 0.0f);
    func_004C6190(unk10, first);
    func_004C6190(unk10, second);
    func_004C6190(unk10, third);
    return 1;
}

static inline u8 shop_record_mode(const ItemCreationCategoryDefinition* record)
{
    return record->unk0b_mode;
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
    title->func_slotf4(reinterpret_cast<void*>(object->unk34));
    object->FieldClass153E30::func_00263FD0(title);
    message->func_slotf4(reinterpret_cast<void*>(object->unk34));
    object->FieldClass153E30::func_00263FD0(message);
    object->unk24 = message;
    message->func_slot40(title);
    object->unk3c->func_slotf4(reinterpret_cast<void*>(object->unk34));
    object->FieldClass153E30::func_00263FD0(object->unk3c);
    object->unk40->func_slotf4(reinterpret_cast<void*>(object->unk34));
    object->FieldClass153E30::func_00263FD0(object->unk40);
    object->unk44->func_slotf4(reinterpret_cast<void*>(object->unk34));
    object->FieldClass153E30::func_00263FD0(object->unk44);
    object->unk48->func_slot104(reinterpret_cast<void*>(object->unk34));
    object->FieldClass153E30::func_00263FD0(object->unk48);
    object->unk48->func_slot20(0);
    object->unk4c->func_slot104(reinterpret_cast<void*>(object->unk34));
    object->FieldClass153E30::func_00263FD0(object->unk4c);
    object->unk4c->func_slot20(0);
    object->unk50->func_slotf4(reinterpret_cast<void*>(object->unk34));
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

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_00351570);

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

INCLUDE_ASM("build/overlays/cshop/asm/nonmatchings/text", func_00351B60);

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

void func_00351CD0(ShopList* list, void* value)
{
    ShopListNode* node = static_cast<ShopListNode*>(func_00100AC0(sizeof(ShopListNode), 0));
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        ShopListNode* tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

void func_00351D60(ShopList* list, void* value)
{
    ShopListNode* node = static_cast<ShopListNode*>(func_00100AC0(sizeof(ShopListNode), 0));
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        ShopListNode* tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

void func_00351DF0(ShopList* list, void* value)
{
    ShopListNode* node = static_cast<ShopListNode*>(func_00100AC0(sizeof(ShopListNode), 0));
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        ShopListNode* tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

void func_00351E80(ShopList* list, void* value)
{
    ShopListNode* node = static_cast<ShopListNode*>(func_00100AC0(sizeof(ShopListNode), 0));
    if (node != 0)
    {
        node->value = value;
        node->next = 0;
        ShopListNode* tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}
