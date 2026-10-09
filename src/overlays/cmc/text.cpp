#include "include_asm.h"
#include "overlays/cmc/text.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/1067-00/field_duration.h"
#include "overlays/1067-00/text_001E1590.h"

/** Drawing parameter prefix consumed by the library packet builder. */
struct CmcDrawParameters
{
    u16 primitive_flags;
    u8 unk02;
    u8 unk03;
    u8 unk04;
    u8 unk05;
    u8 unk06;
    u8 unk07;
    float unk08;
    float unk0c;
    float unk10;
    float unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1a;
    u8 unk1b;
    u8 unk1c;
};

/** Partial aligned resource storage consumed by the runtime slot binder. */
struct CmcResourceBuffer
{
    u8 unk00[0x40];
    u32 byte_count;
};

/** Active window receiver directory reached through the Field runtime. */
struct FieldWindowCallbacks
{
    u8 unk00[0x14];
    FieldClass153E30* unk14;
    u8 unk18[2];
    u16 unk1a;
};

/** Field runtime prefix containing the active window directory. */
struct FieldWindowRuntime
{
    u8 unk00[0x10];
    FieldWindowCallbacks* unk10;
};

extern "C" FieldWindowRuntime* D_001B643C;
extern "C" void func_002CFE10(FieldWindowCallbacks* directory, FieldClass15AE70* window);

/** Partial containing row list, with its resource source word at offset 0x4B0. */
struct CmcRowList
{
    u8 unk00[0x4B0];
    u32 resource_source;
};

/** Partial row record returned by the containing list lookup. */
struct CmcRowRecord
{
    u8 unk00[0x10];
    char display_text;
    u8 unk11[0x27];
    u32 elapsed_seconds;
    u8 unk3c[4];
    u32 text_resource_key;
    u8 unk44[0x39];
    u8 unk7d;
};

extern "C" CmcRowRecord* func_0034BB50(CmcRowList* owner, u16 index);


struct Overlay0072Object00349670
{
    u8 unknown_0[0x4];
    s32 field_4;
};

struct Overlay0072Object00349AB0
{
    u8 unknown_0[0xC];
    u8 field_C;
};

struct Overlay0072Object0034A1D0
{
    u8 unknown_0[0xC];
    u8 field_C;
    u8 unknown_D[0x13];
    s32 field_20;
};

struct Overlay0072Object0034A690
{
    u8 unknown_0[0x38];
    s32 field_38;
};

struct Overlay0072Object0034BB10
{
    u8 unknown_0[0x20];
    s32 field_20;
    s32 field_24;
    u8 unknown_28[0x70];
    s32 field_98;
};

struct Overlay0072Object0034CF80
{
    u8 unknown_0[0x6C];
    u16 field_6C;
};

struct Overlay0072Object003494F0
{
    u8 unknown_0[0x20];
    unsigned __int128 field_20;
    u8 unknown_30[0x20];
    u8 field_50;
};

struct Overlay0072Object00358FC0
{
    u8 unknown_0[0x20];
    unsigned __int128 field_20;
    u8 unknown_30[0x20];
    u8 field_50;
};

struct Overlay0072Object00359000
{
    u8 unknown_0[0x30];
    unsigned __int128 field_30;
    u8 unknown_40[0x10];
    u8 field_50;
};

struct Overlay0072Object003590E0
{
    u8 unknown_0[0x40];
    unsigned __int128 field_40;
    u8 field_50;
};

struct Overlay0072Object00353710
{
    u8 unknown_0[0x20];
    float field_20;
    float field_24;
    float field_28;
    float field_2C;
    u8 unknown_30[0x20];
    u8 field_50;
};

struct Overlay0072Object00358FE0
{
    u8 unknown_0[0x30];
    float field_30;
    float field_34;
    float field_38;
    float field_3C;
    u8 unknown_40[0x10];
    u8 field_50;
};

struct Overlay0072Object00359210
{
    u8 unknown_0[0x4];
    s32 field_4;
    u8 field_8;
    u8 unknown_9[0x1];
    u16 field_A;
    u8 unknown_C[0x4];
    s32 field_10;
    u8 unknown_14[0x2C];
    float field_40;
    float field_44;
    float field_48;
    u8 unknown_4C[0x4];
    u8 field_50;
    u8 unknown_51[0xF];
    u8 field_60;
    u8 unknown_61[0x3B];
    s32 field_9C;
    u8 unknown_A0[0x8];
    u8 field_A8;
};

struct Overlay0072Object003594A0
{
    u8 unknown_0[0xD];
    u8 field_D;
};

struct Overlay0072Object00359600
{
    u8 unknown_0[0x24];
    s32 field_24;
    s8 field_28;
    u8 unknown_29[0xB];
    s32 field_34;
    u8 unknown_38[0x4];
    s32 field_3C;
    u8 field_40;
};

typedef struct
{
    u8 unknown_0[0x48];
    s32 field_48;
    s32 field_4C;
    s32 field_50;
    u8 unknown_54[0xAC];
} Overlay0072Record0035AF80;

typedef struct
{
    u8 unknown_0[0x14];
    Overlay0072Record0035AF80* field_14;
} Overlay0072Inner0035AF80;

struct Overlay0072Object0035AFC0
{
    u8 unknown_0[0x14];
    Overlay0072Inner0035AF80* field_14;
    u8 unknown_18[0x4];
    s16 field_1C;
    s16 field_1E;
    s16 field_20;
    s16 field_22;
    u8 unknown_24[0xC];
    s32 field_30;
    u8 field_34;
    u8 unknown_35[0x4];
    u8 field_39;
};

struct Overlay0072Nested00359C10
{
    u8 unknown_0[0x28];
    u8 field_28;
};

struct Overlay0072Nested00359C20
{
    u8 unknown_0[0x1250];
    s32 field_1250;
};

struct Overlay0072Object00359C10
{
    u8 unknown_0[0x14];
    struct Overlay0072Nested00359C10* field_14;
    struct Overlay0072Nested00359C20* field_18;
};

struct Overlay0072CtorObject0034D0E0
{
    void* table;
    u8 unknown_4[0x34];
    u8 state;
    u8 unknown_39[7];
    s32 field_40;
};

struct Overlay0072ListNode
{
    void* value;
    Overlay0072ListNode* next;
};

struct Overlay0072List
{
    Overlay0072ListNode* head;
    s32 count;
};

extern "C" {
extern u8 D_50CD30[];
extern void* func_100AC0(s32 size, s32 flags);
extern void func_4C4960(void* object);
/** Native table anchors used by the retained constructor entry points. */
extern u8 __vt__23ItemCreationClass172870[];
extern u8 __vt__23ItemCreationClass172600[];
extern u8 __vt__23ItemCreationClass1725D0[];
extern u8 __vt__23ItemCreationClass1746A0[];
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003483C0);

s32 func_00348400(void* object)
{
    return 3;
}

void func_00348410(void* object)
{
}

void func_00348420(void* object)
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00348430);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003484A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00348520);

/**
 * @brief Initialize the drawing parameters to their defaults.
 * @param parameters Drawing parameters to initialize.
 */
void cmc_initialize_drawing_parameters(CmcDrawParameters* parameters)
{
    parameters->primitive_flags = 0xC;
    parameters->unk03 = 0;
    parameters->unk02 = 0;
    parameters->unk04 = 0;
    parameters->unk05 = 0;
    parameters->unk06 = 1;
    parameters->unk07 = 1;
    parameters->unk08 = 1.0f;
    parameters->unk0c = 1.0f;
    parameters->unk10 = 0.5f;
    parameters->unk18 = 0;
    parameters->unk19 = 0;
    parameters->unk1a = 0;
    parameters->unk1b = 0;
    parameters->unk1c = 0;
    parameters->unk14 = 0.0f;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003492E0);

void func_003494F0(Overlay0072Object003494F0* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_20 = *value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349510);

/** @brief Destroy the root dispatch state. */
inline CmcClass188ED0::~CmcClass188ED0()
{
}

/** @brief Destroy the intermediate object and its root. */
CmcClass188EE0::~CmcClass188EE0()
{
}

s32 func_00349670(Overlay0072Object00349670* object)
{
    return object->field_4;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349680);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003496E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349840);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003498A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349950);

void func_00349AB0(Overlay0072Object00349AB0* object, u8 value)
{
    object->field_C = value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349AC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349B80);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349C40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00349FA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A000);

u8 func_0034A1D0(Overlay0072Object0034A1D0* object)
{
    return object->field_C;
}

s32 func_0034A1E0(Overlay0072Object0034A1D0* object)
{
    return object->field_20;
}

/** @brief Move the child selector forward. */
void CmcClass189110::func_slot6c()
{
    selector->func_0023B3B0(1);
}

/** @brief Move the child selector backward. */
void CmcClass189110::func_slot68()
{
    selector->func_0023B3B0(0);
}

/**
 * @brief Request the controller action, hide this window's nested display, and return status two.
 * @return Two.
 */
s32 CmcClass189110::func_slotb4()
{
    CmcClass18AF20* controller = unka8;
    if (controller != 0)
    {
        controller->unk54 = 0x7A;
        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }
    func_slot20(0);
    return 2;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A290);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A3C0);

s32 func_0034A690(Overlay0072Object0034A690* object)
{
    return object->field_38;
}

/** @brief Destroy the window and its Field parent. */
CmcClass189110::~CmcClass189110()
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A700);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A760);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A8C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A920);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034A9A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034AAB0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034AB70);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034AC30);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034AFB0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B010);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B070);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B1D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B230);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B2E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B440);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B4A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B660);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B800);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B860);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B8C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034B920);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BAA0);

void func_0034BB00(void* object)
{
}

s32 func_0034BB10(Overlay0072Object0034BB10* object)
{
    return object->field_24;
}

void func_0034BB20(Overlay0072Object0034BB10* object, s32 value)
{
    object->field_20 = value;
}

void func_0034BB30(Overlay0072Object0034BB10* object, s32 value)
{
    object->field_98 = value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BB50);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BC40);

void func_0034BD60(void* object)
{
}

void func_0034BD70(void* object)
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BD80);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034BE20);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034C010);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034C460);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034C5D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034C970);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CA60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CAF0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CBA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CCA0);

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass1746A0::~ItemCreationClass1746A0()
{
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass1725D0::~ItemCreationClass1725D0()
{
}

/** @brief Release the movement storage and destroy the widget base. */
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

void func_0034CF80(Overlay0072Object0034CF80* object, u16 value)
{
    object->field_6C = value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034CF90);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D070);

Overlay0072CtorObject0034D0E0* func_0034D0E0(Overlay0072CtorObject0034D0E0* object)
{
    func_4C4960(object);
    object->table = __vt__23ItemCreationClass172870;
    object->field_40 = 0;
    object->state = 6;
    return object;
}

Overlay0072CtorObject0034D0E0* func_0034D120(Overlay0072CtorObject0034D0E0* object)
{
    func_4C4960(object);
    object->table = __vt__23ItemCreationClass172600;
    object->field_40 = 0;
    object->state = 5;
    return object;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D160);

Overlay0072CtorObject0034D0E0* func_0034D230(Overlay0072CtorObject0034D0E0* object)
{
    func_4C4960(object);
    object->table = __vt__23ItemCreationClass1725D0;
    object->field_40 = 0;
    object->state = 3;
    return object;
}

Overlay0072CtorObject0034D0E0* func_0034D270(Overlay0072CtorObject0034D0E0* object)
{
    func_4C4960(object);
    object->table = __vt__23ItemCreationClass1746A0;
    object->field_40 = 0;
    object->state = 4;
    return object;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034D2B0);

/**
 * @brief Position the row panel, text widgets, and numeric widgets.
 * @param owner Unused containing list owner.
 * @param x Horizontal row origin.
 * @param y Vertical row origin.
 */
void CmcClass189900::position_row(void* owner, float x, float y)
{
    float number_y;
    float first_number_x;
    float second_number_x;
    float third_number_x;
    float fourth_number_x;
    float fifth_number_x;
    float first_array_x;
    float array_y;
    float second_array_x;
    float value_x;
    float text_y;

    panel.unk18.unk00 = x;
    panel.unk18.unk04 = y;
    panel.unk18.unk08 = 560.0f;
    panel.unk18.unk0c = 64.0f;
    panel.unk3c = 1;
    first_text.unk18.unk00 = 22.0f + x;
    text_y = 8.0f + y;
    first_text.unk18.unk04 = text_y;
    first_text.unk3c = 1;
    value_x = 160.0f + x;
    string_widget.unk18.unk00 = value_x;
    string_widget.unk18.unk04 = text_y;
    string_widget.unk3c = 1;
    number_y = 32.0f + y;
    first_number_x = 382.0f + x;
    second_number_x = 454.0f + x;
    third_number_x = 466.0f + x;
    fourth_number_x = 490.0f + x;
    fifth_number_x = 502.0f + x;
    for (s32 i = 0; i < 5; i++)
    {
        switch (i)
        {
        case 0:
            numbers[0].unk18.unk00 = first_number_x;
            numbers[0].unk18.unk04 = number_y;
            numbers[0].unk3c = 1;
            break;
        case 1:
            numbers[1].unk18.unk00 = second_number_x;
            numbers[1].unk18.unk04 = number_y;
            numbers[1].unk3c = 1;
            break;
        case 2:
            numbers[2].unk18.unk00 = third_number_x;
            numbers[2].unk18.unk04 = number_y;
            numbers[2].unk3c = 1;
            break;
        case 3:
            numbers[3].unk18.unk00 = fourth_number_x;
            numbers[3].unk18.unk04 = number_y;
            numbers[3].unk3c = 1;
            break;
        case 4:
            numbers[4].unk18.unk00 = fifth_number_x;
            numbers[4].unk18.unk04 = number_y;
            numbers[4].unk3c = 1;
            break;
        }
    }
    s32 array_index = 0;
    first_array_x = 458.0f + x;
    array_y = 30.0f + y;
    second_array_x = 495.0f + x;
    do
    {
        switch (array_index)
        {
        case 0:
            array_text[0].unk18.unk00 = first_array_x;
            array_text[0].unk18.unk04 = array_y;
            array_text[0].unk3c = 1;
            break;
        case 1:
            array_text[1].unk18.unk00 = second_array_x;
            array_text[1].unk18.unk04 = array_y;
            array_text[1].unk3c = 1;
            break;
        }
        array_index++;
    } while (array_index < 2);
    second_text.unk18.unk00 = value_x;
    second_text.unk18.unk04 = number_y;
    second_text.unk3c = 1;
    fourth_text.unk18.unk00 = 140.0f + x;
    fourth_text.unk18.unk04 = text_y;
    fourth_text.unk3c = 1;
    third_text.unk18.unk00 = 472.0f + x;
    third_text.unk18.unk04 = text_y;
    third_text.unk3c = 1;
}

/**
 * @brief Refresh the row text, duration digits, colors, and visibility flags.
 * @param owner Containing row list.
 * @param index Signed row index.
 */
void CmcClass189900::refresh_row(void* owner, s32 index)
{
    FieldDuration duration;
    CmcRowList* list = static_cast<CmcRowList*>(owner);
    CmcRowRecord* record;
    u32 source = list->resource_source;
    func_4C6DF0(&first_text, source, index + 2801, 0);
    record = func_0034BB50(list, static_cast<u16>(index));

    if (unk04 == 3)
    {
        string_widget.unkfc = &record->display_text;
        string_widget.unk3c = 1;
        duration.set_seconds(record->elapsed_seconds);
        numbers[0].numeric_value = duration.hour_digit(0);
        numbers[0].unk3c = 1;
        numbers[1].numeric_value = duration.minute_digit(2);
        numbers[1].unk3c = 1;
        numbers[2].numeric_value = duration.minute_digit(1);
        numbers[2].unk3c = 1;
        numbers[3].numeric_value = duration.second_digit(2);
        numbers[3].unk3c = 1;
        numbers[4].numeric_value = duration.second_digit(1);
        numbers[4].unk3c = 1;
        func_4C6DF0(&second_text, source, record->text_resource_key + 1, 0);
        if (record->unk7d == 1)
        {
            third_text.unk3d = 1;
        }
    }
    else if (unk04 == 5)
    {
        func_4C6DF0(&fourth_text, source, 9021, 0);
        fourth_text.unk94 = 0x505050;
        fourth_text.unk3c = 1;
    }
    else if (unk04 == 6)
    {
        func_4C6DF0(&fourth_text, source, 9022, 0);
        fourth_text.unk94 = 0x505050;
        fourth_text.unk3c = 1;
    }
    else if (unk04 == 2)
    {
        func_4C6DF0(&fourth_text, source, 9023, 0);
        if (unk05)
        {
            fourth_text.unk94 = 0x808080;
            fourth_text.unk3c = 1;
        }
        else
        {
            fourth_text.unk94 = 0x505050;
            fourth_text.unk3c = 1;
        }
    }

    first_text.unk3d = 1;
    if (unk04 == 3)
    {
        string_widget.unk3d = 1;
        numbers[0].unk3d = 1;
        numbers[1].unk3d = 1;
        numbers[2].unk3d = 1;
        numbers[3].unk3d = 1;
        numbers[4].unk3d = 1;
        array_text[0].unk3d = 1;
        array_text[1].unk3d = 1;
        second_text.unk3d = 1;
        if (record->unk7d == 1)
        {
            third_text.unk3d = 1;
        }
        else
        {
            third_text.unk3d = 0;
        }
        fourth_text.unk3d = 0;
    }
    else
    {
        string_widget.unk3d = 0;
        numbers[0].unk3d = 0;
        numbers[1].unk3d = 0;
        numbers[2].unk3d = 0;
        numbers[3].unk3d = 0;
        numbers[4].unk3d = 0;
        array_text[0].unk3d = 0;
        array_text[1].unk3d = 0;
        second_text.unk3d = 0;
        third_text.unk3d = 0;
        fourth_text.unk3d = 1;
    }
}

void func_0034D880(u8* object, void* unused, u8 value)
{
    object[0x45] = value;
    object[0xD5] = value;
    object[0x1E9] = value;
    object[0x3FD] = value;
    object[0x4FD] = value;
    object[0x5FD] = value;
    object[0x6FD] = value;
    object[0x7FD] = value;
    object[0x8FD] = value;
    object[0xA11] = value;
    object[0x2E9] = value;
    object[0xC39] = value;
    object[0xB25] = value;
}

/** @brief Construct the panel, text widgets, and numeric widgets for this row. */
CmcClass189900::CmcClass189900()
{
    unk04 = 6;
    unk05 = 0;
}

/** @brief Destroy the string widget and its drawing-widget base. */
inline LibObject175140::~LibObject175140()
{
}

/** @brief Destroy the numeric widget and its drawing-widget base. */
inline LibObject174F20::~LibObject174F20()
{
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
s32 CmcClass189920::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
s32 CmcClass189920::func_slotb0()
{
    FieldClass15AE70::func_slot18(0, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    func_002CFE10(D_001B643C->unk10, this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DD40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034DED0);

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
s32 CmcClass189A20::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
s32 CmcClass189A20::func_slotb0()
{
    func_slot18(0, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    func_002CFE10(D_001B643C->unk10, this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E040);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E1D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E230);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E3B0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E6D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E820);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E860);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E8A0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034E980);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034EBC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F280);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F310);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F370);

/**
 * @brief Release nested window displays and unregister the window.
 */
void CmcClass189C20::func_slot0c()
{
    FieldClass15AE70::func_slot0c();
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F3F0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F550);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F760);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F7D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034F830);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0034FA90);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350070);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350200);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350260);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003504F0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003509D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350B60);

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
s32 CmcClass189F20::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
s32 CmcClass189F20::func_slotb0()
{
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    FieldClass15AE70::func_slot18(0, 0x7F);
    func_002CFE10(D_001B643C->unk10, this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350CC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350E40);

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
s32 CmcClass18A020::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
s32 CmcClass18A020::func_slotb0()
{
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    FieldClass15AE70::func_slot18(0, 0x7F);
    func_002CFE10(D_001B643C->unk10, this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00350FA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351130);

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
s32 CmcClass18A120::func_slotb4()
{
    func_slotb0();
    return 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003511C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351470);

/** @brief Destroy the window and its Field parent. */
CmcClass18A120::~CmcClass18A120()
{
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
s32 CmcClass18A220::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
s32 CmcClass18A220::func_slotb0()
{
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    FieldClass15AE70::func_slot18(0, 0x7F);
    func_002CFE10(D_001B643C->unk10, this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003517C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351950);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003519B0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351C60);

/**
 * @brief Run the window action when its guard byte is clear.
 * @return Zero when guarded, otherwise one after running the action.
 */
s32 CmcClass18A320::func_slotb4()
{
    if (unkac != 0)
    {
        return 0;
    }
    func_slotb0();
    return 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00351D40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352010);

/** @brief Destroy the window and its Field parent. */
CmcClass18A320::~CmcClass18A320()
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352230);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352440);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352A80);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352CE0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352D40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00352F10);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003533C0);

void func_00353710(Overlay0072Object00353710* object, float x, float y, float z)
{
    object->field_50 = 1;
    object->field_20 = x;
    object->field_24 = y;
    object->field_28 = z;
    object->field_2C = 1.0f;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353730);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003537D0);

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
s32 CmcClass18A620::func_slotb4()
{
    func_slotb0();
    return 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353840);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353970);

/** @brief Destroy the window and its Field parent. */
CmcClass18A620::~CmcClass18A620()
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353B60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353D00);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00353EC0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354080);

void func_003540E0(void* object)
{
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
s32 CmcClass18A820::func_slotb4()
{
    func_slotb0();
    return 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354120);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003542B0);

/** @brief Destroy the window and its Field parent. */
CmcClass18A820::~CmcClass18A820()
{
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003545C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003547D0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003548E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354920);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354960);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354A50);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00354C20);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355020);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355080);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355240);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355410);

/**
 * @brief Set display flags on the selected window lists.
 * @param flag Flag word forwarded to grids; its low byte updates other displays.
 * @param list_mask List groups selected by bits 0 through 6.
 */
void CmcClass18AA20::func_slot18(u32 flag, u32 list_mask)
{
    FieldClass15AE70::func_slot18(flag, list_mask);
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355D70);

/** @brief Destroy the window and its Field parent. */
CmcClass18AA20::~CmcClass18AA20()
{
}

/**
 * @brief Set display flags on the selected window lists.
 * @param flag Flag word forwarded to grids; its low byte updates other displays.
 * @param list_mask List groups selected by bits 0 through 6.
 */
void CmcClass18AB20::func_slot18(u32 flag, u32 list_mask)
{
    FieldClass15AE70::func_slot18(flag, list_mask);
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00355FF0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003560E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003561D0);

/** @brief Destroy the window and its Field parent. */
CmcClass18AB20::~CmcClass18AB20()
{
}

/**
 * @brief Find the final window in the associated-window chain.
 * @return Last window, including the input window when it has no association.
 */
void* CmcClass18AC20::func_slot3c()
{
    return FieldClass15AE70::func_slot3c();
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356400);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356460);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003564C0);

/**
 * @brief Set the window control byte to one and return status two.
 * @return Two.
 */
s32 CmcClass18AC20::func_slotb4()
{
    func_slot24(1);
    return 2;
}

/**
 * @brief Set list flags and the target display byte flag when the low flag byte is one.
 * @param flag Display flag word.
 * @param list_mask List groups selected by bits 0 through 6.
 */
void CmcClass18AC20::func_slot18(u32 flag, u32 list_mask)
{
    FieldClass15AE70::func_slot18(flag, list_mask);
    if (target_display != 0 && (u8)flag == 1)
    {
        target_display->flag3F = 1;
    }
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003568C0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356A40);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00356BF0);

/** @brief Destroy the window and its Field parent. */
CmcClass18AC20::~CmcClass18AC20()
{
}

/** @brief Update widget state and advance the text rectangle animation. */
void CmcClass18AD20::func_slot5c()
{
    if (D_001B643C->unk10->unk1a & 8)
    {
        func_slot60(0x232F);
    }
    if (unkB9 == 1)
    {
        switch (unkB8)
        {
        case 0:
            unkAc->unk3f = 1;
            unkD0->unk3f = 1;
            break;
        case 1:
            unkB0->unk3f = 1;
            unkD0->unk3f = 1;
            break;
        default:
            unkAc->unk3f = 0;
            unkB0->unk3f = 0;
            unkD0->unk3f = 0;
            break;
        }
        unkB9 = 0;
    }
    LibObject178750* widget = unkA8;
    LibUiRect16* rectangle = &widget->unk18;
    float x;
    float y;
    float width;
    float height;
    x = rectangle->unk00;
    if (unkD4)
    {
        y = 1.0f;
    }
    else
    {
        y = 6.0f;
    }
    width = rectangle->unk08;
    height = rectangle->unk0c;
    if (unkBa == 0)
    {
        widget->unk18.unk00 = unkC4;
        widget->unk18.unk04 = y;
        widget->unk18.unk08 = width;
        widget->unk18.unk0c = height;
        widget->unk3c = 1;
        ++unkBc;
        if (!(static_cast<float>(unkBc) <= 120.0f))
        {
            unkBc = 0;
            unkBa = 1;
        }
        return;
    }
    x -= 108.0f * D_001B6690;
    if (x < unkC8 - static_cast<float>(unkB4))
    {
        x = (unkC8 + unkCc) + 2.0f;
    }
    widget->unk18.unk00 = x;
    widget->unk18.unk04 = y;
    widget->unk18.unk08 = width;
    widget->unk18.unk0c = height;
    widget->unk3c = 1;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357190);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357320);

/** @brief Destroy the window and its Field parent. */
CmcClass18AD20::~CmcClass18AD20()
{
}

/** @brief Initialize the window, retained widgets, and animation state. */
CmcClass18AD20::CmcClass18AD20()
{
    unkA8 = 0;
    unkAc = 0;
    unkB0 = 0;
    unkB4 = 0;
    unkB8 = -1;
    unkB9 = 0;
    unkBa = 0;
    unkBc = 0;
    unkBe = -1;
    unkC0 = 0.0f;
    unkC4 = 0.0f;
    unkC8 = 0.0f;
    unkCc = 0.0f;
    unkD0 = 0;
    unkD4 = 0;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357CA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00357F60);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", dispatch_window_request__14CmcClass18AF20Fv);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003583B0);

void func_003585A0(void* object)
{
}

/** @brief Release the retained resource slot, detach the controller, and queue it. */
void CmcClass18AF20::release_resources()
{
    if (resource_slot)
    {
        func_00465430(D_001B657C, resource_slot);
    }
    func_004D65C0(this);
    func_001DD7B0();
}

/** @brief Add this object to the resident queue. */
void CmcClass18AF20::func_001DD7B0()
{
    func_0011ED90(D_001B65F4, this);
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00358620);

/**
 * @brief Bind a completed resource buffer and finish controller setup.
 * @param buffer Completed buffer, aligned to 128 bytes before use.
 * @return Setup result, or zero when the buffer is null.
 */
s32 CmcClass18AF20::func_001E1820(void* buffer)
{
    CmcResourceBuffer* resource = static_cast<CmcResourceBuffer*>(buffer);
    if (!resource)
    {
        return 0;
    }
    resource = reinterpret_cast<CmcResourceBuffer*>((reinterpret_cast<u32>(resource) + 0x7F) & ~0x7F);
    s32 allocation_size = resource->byte_count + 0x80;
    void* previous_heap = func_00100C90();
    void* resource_heap = D_001B6430->context->unk70;
    void* allocation = func_00113710(resource_heap, allocation_size);
    if (allocation)
    {
        func_001134C0(allocation);
        func_00100C80(resource_heap);
    }
    resource_slot = func_004656B0(D_001B657C, resource);
    func_00100C80(previous_heap);
    return func_00263CD0();
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00358D50);

/** @brief Detach and release the linked object, then destroy the Field parent. */
CmcClass18AF20::~CmcClass18AF20()
{
    if (linked_object != 0)
    {
        func_004D65C0(linked_object);
        linked_object->func_00358F90();
    }
}

/** @brief Initialize the callback controller and its retained object pointers. */
CmcClass18AF20::CmcClass18AF20()
{
    resource_slot = 0;
    linked_object = 0;
    unk3c = 0;
    unk40 = 0;
    unk44 = 0;
    unk48 = 0;
    unk4c = 0;
    unk50 = 0;
    unk52 = 0;
    unk54 = 0;
    unk58 = 0;
    unk5c = 0;
    unk60 = 0;
    unk64 = 0;
    unk68 = 0;
    unk6c = 0;
    unk70 = 0;
    unk74 = 0;
    unk78 = 0;
    unk7c = 0;
    unk80 = 0;
}

/** @brief Destroy this linked object through its virtual destructor. */
void CmcClass188EF0::func_00358F90()
{
    delete this;
}

void func_00358FC0(Overlay0072Object00358FC0* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_20 = *value;
}

void func_00358FE0(Overlay0072Object00358FE0* object, float x, float y, float z, float w)
{
    object->field_50 = 1;
    object->field_30 = x;
    object->field_34 = y;
    object->field_38 = z;
    object->field_3C = w;
}

void func_00359000(Overlay0072Object00359000* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_30 = *value;
}

void func_00359020(Overlay0072Object00359000* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_30 = *value;
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

void func_003590E0(Overlay0072Object003590E0* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_40 = *value;
}

void func_00359100(Overlay0072Object003590E0* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_40 = *value;
}

void func_00359120(Overlay0072Object00359210* object, float x, float y, float z)
{
    object->field_50 = 1;
    object->field_40 = x;
    object->field_44 = y;
    object->field_48 = z;
}

s32 func_00359140(void* object)
{
    return 0;
}

s32 func_00359150(float value)
{
    s32 result = 1;
    if (!(value < 0.0f))
    {
        result = 0;
    }
    return result;
}

u8* func_00359170(void* object)
{
    return D_50CD30;
}

s32 func_00359180(void* object)
{
    return 0;
}

void func_00359190(void* object)
{
}

/** @brief Perform no work. */
void ItemCreationClass185050::func_slot0c()
{
}

void func_003591B0(void* object)
{
}

void func_003591C0(void* object)
{
}

float func_003591D0(void* object)
{
    return 0.0f;
}

void func_003591E0(void* object)
{
}

void func_003591F0(Overlay0072Object00359210* object)
{
    object->field_60 = object->field_A8;
}

void func_00359200(void* object)
{
}

void func_00359210(Overlay0072Object00359210* object, u8 value)
{
    object->field_8 = value;
}

u8 func_00359220(Overlay0072Object00359210* object)
{
    return object->field_8;
}

void func_00359230(Overlay0072Object00359210* object, u16 value)
{
    object->field_A = value;
}

u16 func_00359240(Overlay0072Object00359210* object)
{
    return object->field_A;
}

void func_00359250(Overlay0072Object00359210* object, s32 value)
{
    object->field_9C = value;
}

s32 func_00359260(Overlay0072Object00359210* object)
{
    return object->field_9C;
}

void func_00359270(Overlay0072Object00359210* object, s32 value)
{
    object->field_4 = value;
}

s32 func_00359280(Overlay0072Object00359210* object)
{
    return object->field_10;
}

void func_00359290(void* object)
{
}

void func_003592A0(void* object)
{
}

void func_003592B0(void* object)
{
}

void func_003592C0(void* object)
{
}

void func_003592D0(void* object)
{
}

void func_003592E0(void* object)
{
}

void func_003592F0(void* object)
{
}

void func_00359300(void* object)
{
}

void func_00359310(void* object)
{
}

void func_00359320(void* object)
{
}

void func_00359330(void* object)
{
}

void func_00359340(void* object)
{
}

void func_00359350(void* object)
{
}

void func_00359360(void* object)
{
}

void func_00359370(void* object)
{
}

void func_00359380(void* object)
{
}

void func_00359390(void* object)
{
}

void func_003593A0(void* object)
{
}

void func_003593B0(void* object)
{
}

void func_003593C0(void* object)
{
}

s32 func_003593D0(void* object)
{
    return 0;
}

s32 func_003593E0(void* object)
{
    return 0;
}

s32 func_003593F0(void* object)
{
    return 0;
}

s32 func_00359400(void* object)
{
    return 0;
}

s32 func_00359410(void* object)
{
    return 0;
}

s32 func_00359420(void* object)
{
    return 0;
}

s32 func_00359430(void* object)
{
    return 0;
}

s32 func_00359440(void* object)
{
    return 0;
}

s32 func_00359450(void* object)
{
    return 0;
}

s32 func_00359460(void* object)
{
    return 0;
}

s32 func_00359470(void* object)
{
    return 0;
}

void func_00359480(void* object)
{
}

void func_00359490(void* object)
{
}

u8 func_003594A0(Overlay0072Object003594A0* object)
{
    return object->field_D;
}

void func_003594B0(Overlay0072Object003594A0* object, u8 value)
{
    object->field_D = value;
}

void func_003594C0(void* object)
{
}

s32 func_003594D0(void* object)
{
    return 0;
}

/** @brief Destroy the embedded widgets in reverse construction order. */
CmcClass189900::~CmcClass189900()
{
}

s32 func_00359600(Overlay0072Object00359600* object)
{
    return object->field_34;
}

u8 func_00359610(Overlay0072Object00359600* object)
{
    return object->field_40;
}

s32 func_00359620(Overlay0072Object00359600* object)
{
    return object->field_3C;
}

s32 func_00359630(void* object)
{
    return 4;
}

void func_00359640(Overlay0072Object00359600* object, s32 value)
{
    object->field_24 = value;
}

void func_00359650(Overlay0072Object00359600* object, u8 value)
{
    object->field_28 = value;
}

s8 func_00359660(Overlay0072Object00359600* object)
{
    return object->field_28;
}

void func_00359670(void* object)
{
}

s32 func_00359680(void* object)
{
    return 0;
}

void func_00359690(void* object)
{
}

void func_003596A0(void* object)
{
}

void func_003596B0(void* object)
{
}

s32 func_003596C0(void* object)
{
    return 0;
}

s32 func_003596D0(void* object)
{
    return 0;
}

s32 func_003596E0(void* object)
{
    return 0;
}

void func_003596F0(Overlay0072List* list, void* value)
{
    Overlay0072ListNode* node = (Overlay0072ListNode*)func_100AC0(8, 0);
    Overlay0072ListNode* cursor;

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

void func_00359780(Overlay0072List* list, void* value)
{
    Overlay0072ListNode* node = (Overlay0072ListNode*)func_100AC0(8, 0);
    Overlay0072ListNode* cursor;

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

Overlay0072ListNode* func_00359810(Overlay0072List* list, s32 index)
{
    Overlay0072ListNode* node = list->head->next;
    s32 i;

    for (i = 0; i < index; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void func_00359850(Overlay0072List* list, void* value)
{
    Overlay0072ListNode* node = (Overlay0072ListNode*)func_100AC0(8, 0);
    Overlay0072ListNode* cursor;

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

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003598E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_003598F0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359900);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359910);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359920);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359930);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359940);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359950);

s32 func_00359960(void* object)
{
    return 2;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359970);

u8 func_00359C10(Overlay0072Object00359C10* object)
{
    return object->field_14->field_28;
}

s32 func_00359C20(Overlay0072Object00359C10* object)
{
    s32 value = object->field_18->field_1250;
    if (value > 0)
    {
        return value;
    }
    return 0;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359C50);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_00359DA0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035A010);

void func_0035ADA0(Overlay0072Object0035AFC0* object, u8 value, u8 other)
{
    if (value == 1)
    {
        object->field_1E = 0;
    }
    object->field_39 = other;
    object->field_34 = value;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035ADD0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035AE70);

void func_0035AF60(Overlay0072Object0035AFC0* object, s16 value)
{
    object->field_20 = 0;
    object->field_1E = value;
    object->field_22 = 0;
    object->field_39 = 0;
    object->field_34 = 0;
    object->field_30 = -1;
}

s32 func_0035AF80(Overlay0072Object0035AFC0* object)
{
    return object->field_14->field_14[object->field_1C].field_50;
}

s32 func_0035AFA0(Overlay0072Object0035AFC0* object)
{
    return object->field_14->field_14[object->field_1C].field_4C;
}

s16 func_0035AFC0(Overlay0072Object0035AFC0* object)
{
    return object->field_22;
}

s32 func_0035AFD0(Overlay0072Object0035AFC0* object, s16 index)
{
    return object->field_14->field_14[index].field_48;
}

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035AFF0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035B0E0);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035B170);

INCLUDE_ASM("build/overlays/cmc/asm/nonmatchings/text", func_0035B200);
