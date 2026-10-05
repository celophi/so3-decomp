#include "include_asm.h"
#include "overlays/citemcreation/text_003483C0.h"
#include "overlays/citemcreation/text_00358440.h"
#include "overlays/citemcreation/text_003684D0.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_001E1590.h"

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

typedef struct ItemCreationColorRecordState
{
    u8 unk00[0x10F50];
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

typedef struct ItemCreationOptionResourceDisplay
{
    FieldResourceDisplay2D5CF0 base;
    u8 unk40[0x90];
    u8 unkd0;
} ItemCreationOptionResourceDisplay;

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

// These external interfaces are scoped here because their owning code is in other overlays.
extern ItemCreationColorRecordState* D_001B64F8;
extern ItemCreationRuntime643C* D_001B643C;
extern "C" void func_466E40(void* point, float x, float y, float scale);
extern "C" s32 func_002CFE40(void* object, s16 index);
extern "C" u16 func_23B3A0(FieldState23B3A0* object);
extern "C" u32 func_23B3B0(FieldState23B3A0* object, u16 direction);

/**
 * @brief Read the low byte of the selected grid index.
 * @param display Six-slot index display.
 * @return The byte-sized selected index.
 */
/** @brief Return the selected position pair, or null for an invalid index. */
static inline const float* option_selection_position(ItemCreationSelection* selection, s32 index);
/** @brief Position and enable a transfer display. */
static inline void set_transfer_position(ItemCreationTransferDisplay* display, float x, float y);

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

u32 func_003484C0(void* object)
{
    return *(u32*)((u8*)object + 0x10);
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034C4B0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034C5F0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034C700);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034C7F0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034C870);

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
            func_002D5CF0(&object->unkac[index]->base, allocation, record, 0);
        }
    }
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_slotf4__23ItemCreationClass185860FPv);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034E670);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034E840);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034E9C0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034FA70);

s32 func_0034FD50(ItemCreationFlagResetOwner* object, void* associated)
{
    func_002CE8D0((FieldObjectCE8D0*)object, associated, 16.0f, 72.0f, 17);
    return 1;
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034FE00);

u32 func_0034FF60(void* object)
{
    return *(u32*)((u8*)object + 0x34);
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_0034FF70);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003500D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003501B0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003507C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003508E0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00350FA0);

/**
 * @brief Destroy the window through its Field base.
 */
ItemCreationClass185D60::~ItemCreationClass185D60()
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003513E0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00351510);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00351680);

/**
 * @brief Destroy the window through its Field base.
 */
ItemCreationClass185E60::~ItemCreationClass185E60()
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00351B10);

void func_00351C30(void* object)
{
}

void func_00351C40(void* object)
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00351C50);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00351CF0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00351DC0);

/** @brief Destroy the receiver. */
ItemCreationClass185030::~ItemCreationClass185030()
{
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00352020);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003522B0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00352340);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003523E0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003527D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003528B0);

/** @brief Initialize the widget storage and select kind 6. */
ItemCreationClass172870::ItemCreationClass172870()
{
    unk38 = 6;
}

/** @brief Initialize the widget storage and select kind 5. */
ItemCreationClass172600::ItemCreationClass172600()
{
    unk38 = 5;
}

/** @brief Initialize the widget and select kind 9. */
ItemCreationClass175030::ItemCreationClass175030()
{
    unk38 = 9;
}

/** @brief Initialize the widget storage and select kind 3. */
ItemCreationClass1725D0::ItemCreationClass1725D0()
{
    unk38 = 3;
}

/** @brief Initialize the widget storage and select kind 4. */
ItemCreationClass1746A0::ItemCreationClass1746A0()
{
    unk38 = 4;
}

/** @brief Initialize the widget and select kind 2. */
ItemCreationClass184F30::ItemCreationClass184F30()
{
    unk38 = 2;
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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00352DE0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003534D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003537A0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00354010);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00354050);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003540D0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00354180);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00354220);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00354520);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003545B0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003548A0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00354A30);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00354D30);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00354EA0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00355240);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003552D0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00355810);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00355930);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00355BD0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00356250);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00356330);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003564C0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003565A0);

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

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003568B0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003568D0);

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
    func_0023CE80(object->unk10c, 1, object->unk1bc);
    func_00356780((ItemCreationFlagGroups*)object, 0);
}

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00357120);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00357E40);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00357F90);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_003580B0);

INCLUDE_ASM("build/overlays/citemcreation/asm/nonmatchings/text_003483C0", func_00358190);

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
