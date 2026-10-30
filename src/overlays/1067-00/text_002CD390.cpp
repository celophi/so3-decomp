#include "include_asm.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/1067-00/text_marker.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0045AD10.h"

extern "C" void func_420D20(ItemCreationClass172870* object, u32 color);

extern "C" s32 func_002CF190(FieldCountedList* list, void** object);
extern "C" s32 func_002CEFA0(FieldCountedList* list, void** object);
extern "C" void func_002CDB20(FieldClass15AE60* object);
extern "C" void func_002CE010(FieldClass15AE60* object);
struct FieldListInputFlags
{
    u16 unk00;
    u16 unk02;
};
struct FieldListInputRuntime
{
    u8 pad00[0x554];
    FieldListInputFlags* flags;
    u8 pad558[0x9A];
    u16 mask;
};


/** Partial receiver with a float at 0x14 and a state bit at 0x604. */
struct FieldStateCD390
{
    u8 pad00[0x14];
    float value;
    u8 pad18[0x5EC];
    u8 enabled : 1;
    u8 other : 7;
};


struct FieldTable14
{
    u8 pad[0x14];
    u8* entries;
};

struct FieldGrid20
{
    u8 pad[0x10];
    u32 rows;
    u8 pad14[0xC];
    u8* entries;
};

struct FieldWord1C
{
    u8 pad[0x1C];
    u32 value;
};

struct FieldWord0C
{
    u8 pad[0xC];
    u32 value;
};

struct FieldWord10
{
    u8 pad[0x10];
    u32 value;
};

struct FieldWord14
{
    u8 pad[0x14];
    u32 value;
};

struct FieldFlags1C
{
    u8 pad[0x1C];
    u32 flags;
};

struct FieldByteCB
{
    u8 pad[0xCB];
    u8 value;
};

struct FieldBytePtr10
{
    u8 pad[0x10];
    FieldByteCB* target;
};

struct FieldBitFlags1C
{
    u8 pad[0x1C];
    u8 active : 1;
    u8 reserved : 7;
};

struct FieldInputBlock
{
    u8 pad[0x2C];
    const u8* data;
    s32 count;
    u8 unk34;
};

struct FieldEntry90
{
    u8 data[0x90];
};

struct FieldCollection90
{
    u8 pad[0x14];
    FieldEntry90* entries;
};

struct FieldCell40
{
    u8 data[0x40];
};

struct FieldGrid40
{
    u8 pad[0x10];
    s32 width;
    u8 pad14[0xC];
    FieldCell40* cells;
};

struct FieldSignedWord1C
{
    u8 pad[0x1C];
    s32 value;
};

struct FieldSignedWord0C
{
    u8 pad[0xC];
    s32 value;
};

struct FieldSignedWord10
{
    u8 pad[0x10];
    s32 value;
};

struct FieldPointer14
{
    u8 pad[0x14];
    void* value;
};

struct FieldState100
{
    u8 pad[0x3B];
    u8 unk3b;
    u8 pad3c[0x34];
    s32 unk70;
    u8 pad74[0x44];
    s32 unkB8;
    u8 padBC[0x44];
    s32 unk100;
};

struct FieldFloat2C
{
    u8 pad[0x2C];
    float value;
};

struct FieldEntry50
{
    u8 data[0x50];
};

struct FieldCollection50
{
    u8 pad[0x14];
    FieldEntry50* entries;
};
extern "C" void func_113EA0();
extern "C" void func_4C74E0(FieldState100* state);
extern "C" void func_462320(FieldState100* state, s32, s32);

struct FieldWord28
{
    u8 pad[0x28];
    u32 value;
};

struct FieldInputState
{
    u8 pad[0x2C];
    u8* input;
    u32 unk30;
    u8 mode;
};

struct FieldCollection
{
    u8 pad00[0xC];
    s32 unk0C;
    s32 unk10;
    char* unk14;
    u8 pad18[4];
    s32 unk1C;
    char* unk20;
};

struct FieldThing
{
    u8 pad00[0x45];
    s8 unk45;
};

struct FieldPair
{
    u8 pad00[0x40];
    FieldThing* first;
    FieldThing* second;
    u8 pad48[5];
    u8 flag0 : 1;
    u8 flag1 : 1;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 flag6 : 1;
    u8 flag7 : 1;
};

struct FieldMotion
{
    u8 pad00[0x28];
    s32 unk28;
    u8 pad2C[4];
    float unk30;
    u8 pad34[8];
    s16 unk3C;
    s16 unk3E;
    u8 unk40;
    u8 unk41;
    u8 pad42[4];
    u8 unk46;
    u8 flag0 : 1;
    u8 flag1 : 1;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 flag6 : 1;
    u8 flag7 : 1;
};

struct FieldNode
{
    u8 pad00[8];
    FieldNode* next;
    u8 pad0C[0x10];
    u32 flags;
    u8 pad20[0x44];
    u8 unk64;
};

struct FieldList
{
    u8 pad00[0x20];
    FieldNode sentinel;
    u8 pad88[0x9E];
    u8 unk126;
};

struct FieldState28
{
    u8 pad00[0x28];
    s32 unk28;
};

struct FieldSelector
{
    u8 pad00[0x2C];
    const u8* unk2C;
    void* unk30;
    u8 unk34;
};
extern "C" s8 D_30EAFC[];

extern "C" s32 func_002CD390(FieldStateCD390* object)
{
    if (object->enabled)
    {
        object->value = 1.0f;
        return 0;
    }
    return 1;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CD390", func_002CD3C0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CD390", func_002CD440);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CD390", func_002CD740);

extern "C" void func_002CD780(void* object) {}

extern "C" void func_002CD790(void* object) {}

extern "C" void func_002CD7A0(void* object) {}

extern "C" void func_002CD7B0(void* object) {}

void FieldClass15AD40::func_slot5c()
{
    if (this->FieldClass15AE60::unk2c)
    {
        this->FieldClass15AE60::unk2c--;
    }
    if (this->FieldClass15AE60::unk84)
    {
        s32 active = ((FieldState23B3A0*)this->FieldClass15AE60::unk04)->unk75 != 0;
        active = active ? this->FieldClass15AE60::pad29[1] == 0 : active;
        if (active)
        {
            this->FieldClass15AE60::unk24 = this->FieldClass15AE60::unk28 + this->FieldClass15AE60::unk22 * this->FieldClass15AE60::unk26;
            FieldListInputRuntime* runtime = (FieldListInputRuntime*)D_001B657C;
            FieldListInputFlags* flags = runtime->flags;
            u16 mask = runtime->mask;
            if (!(mask & flags->unk00) && (mask & flags->unk02))
            {
                this->FieldClass15AE60::unk24 = -1;
            }
            func_002CDB20(&static_cast<FieldClass15AE60&>(*this));
        }
        func_002CE010(&static_cast<FieldClass15AE60&>(*this));
    }
    else if (this->FieldClass15AE60::unk85)
    {
        this->refresh_rows(this->FieldClass15AE60::unk22);
        this->FieldClass15AE60::unk85 = 0;
    }
}

void FieldClass15AD40::set_selection_marker(LibClass174EF0* target, u32 color)
{
    if (!this->selection_marker)
    {
        this->selection_marker = new (0) FieldClass153170;
        func_0023B850((FieldObject23B850*)this->selection_marker, (FieldTarget23B850*)target, color);
        lib_container_attach_widget(this->FieldClass15AE70::unk10, this->selection_marker);
        if (this->FieldClass15AE60::unk3c)
        {
            this->selection_marker->unk5c = 1;
        }
    }
    if (target)
    {
        if (this->FieldClass15AE60::pad29[1] == 0 || this->FieldClass15AE60::unk3c)
        {
            this->selection_marker->unk3f = 1;
            if (this->FieldClass15AE60::unk3c && this->FieldClass15AE60::pad29[1] == 2 && (s8)this->FieldClass15AE60::pad29[0] > 0)
            {
                this->selection_marker->unk3f = 0;
            }
            func_0023B7E0((FieldObject23B950*)this->selection_marker, (FieldTarget23B850*)target);
            func_420D20(this->selection_marker, color);
            func_0023B780((FieldObject23B950*)this->selection_marker);
        }
    }
    else
    {
        this->selection_marker->unk3f = 0;
    }
}

extern "C" int func_002CD9E0(void* object) { return 1; }

/** @brief Release the list window and its base display lists. */
FieldClass15AD40::~FieldClass15AD40()
{
}

/** @brief Initialize the list window and its display slots. */
FieldClass15AD40::FieldClass15AD40()
{
    FieldClass15AE60::unk04 = 0;
    FieldClass15AE60::unk00 = 0;
    selection_marker = 0;
    unk88 = 0;
    FieldClass15AE60::unk2b = 0;
    FieldClass15AE60::pad30[0] = 0;
    unk84 = 0;
    unk85 = 0;
    FieldClass15AE60::unk8c = 0xFF;
    for (s32 i = 0; i <= 14; i++)
    {
        unk48[i] = 0;
    }
    FieldClass15AE70();
    FieldClass15AE60::unk3c = 0;
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CD390", func_002CDB20);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CD390", func_002CDFB0);

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CD390", func_002CE010);

/**
 * @brief Store the selector coordinates and enable position updates.
 * @param selector Selector widget to update.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
static inline void set_selector_position(ItemCreationClass175030* selector, float x, float y)
{
    selector->ItemCreationClass185050::unk10 = x;
    selector->ItemCreationClass185050::unk14 = y;
    selector->unk35 = 1;
    selector->unk3c = 1;
}
void FieldClass15AE60::configure_selection(s32 count, s32 start, s32 selected)
{
    this->unk18 = count;
    this->unk1e = (this->unk18 + this->unk26 - 1) / this->unk26;
    this->unk20 = this->unk1e - this->unk27;
    if (this->unk20 < 0)
    {
        this->unk20 = 0;
    }
    this->unk22 = start;
    this->refresh_rows(this->unk22);
    this->unk14 = 0.0f;
    this->unk10 = 0.0f;
    this->pad29[1] = 0;
    this->set_scroll_position(this->unk10);
    this->unk28 = selected;
    ItemCreationClass175030* selector = (ItemCreationClass175030*)this->unk04;
    set_selector_position(selector,
                          this->unk08 + (float)(this->unk1a * (this->unk28 % this->unk26)),
                          this->unk0c + (float)(this->unk1c * (this->unk28 / this->unk26)));
    this->unk04->unk3c = 1;
    ItemCreationClass1725D0* indicator = (ItemCreationClass1725D0*)this->unk00;
    indicator->unk50 = 100.0f * (u32)this->unk27 / (u32)this->unk1e;
    indicator->unk3c = 1;
    indicator = (ItemCreationClass1725D0*)this->unk00;
    indicator->unk54 = 100.0f * (this->unk14 + (float)(this->unk22 * this->unk1c)) / (float)(this->unk1e * this->unk1c);
    indicator->unk3c = 1;
}

extern "C" void func_002CE420(FieldStateCE420* object, u8 first, u32 second, u16 third, u16 fourth)
{
    object->unk26 = first;
    object->unk27 = second;
    object->unk1a = third;
    object->unk1c = fourth;
    object->unk08 = object->unk34;
    object->unk0c = object->unk38;
    object->unk22 = 0;
    object->unk28 = 0;
    object->unk2c = 0;
}

/**
 * @brief Find the final window in the associated-window chain.
 * @return Last window, including this window when it has no association.
 */
void* FieldClass15AE70::func_slot3c()
{
    FieldClass15AE70* window = this;
    if (window->func_slot44())
    {
        do
        {
            window = (FieldClass15AE70*)window->func_slot44();
        } while (window->func_slot44());
    }
    return window;
}

/**
 * @brief Enable window control and store the state code and flags.
 * @param code Byte state code.
 * @param flags Halfword state flags.
 */
void FieldClass15AE70::set_state(u8 code, u16 flags)
{
    func_slot24(1);
    unk08 = code;
    unk0a = flags;
}

/**
 * @brief Store the low byte of the activation value in the nested display.
 * @param object Receiver containing the display.
 * @param value Activation value.
 */
extern "C" void func_002CE510(FieldBytePtr10* object, u32 value)
{
    if (object->target)
    {
        object->target->value = value;
    }
}

INCLUDE_ASM("build/overlays/1067-00/asm/nonmatchings/text_002CD390", func_002CE530);

/** @brief Queue a constructed container. @param container Container to queue. @return Zero for a null container, otherwise one. */
static inline u8 queue_container(LibObject178660* container)
{
    if (!container)
    {
        return 0;
    }
    lib_queue_display_object(D_001B657C, container);
    return 1;
}

/** @brief Allocate and queue the container, configure its transform, and associate it with the window. */
s32 FieldClass15AE70::func_slot14(u32 associated, s32 first, s32 second, s32 third, float x, float y, float z)
{
    unk10 = new (0) LibObject178660;
    if (queue_container(unk10) == 0 || !associated)
    {
        return 0;
    }
    lib_container_init(unk10, first, x, y, second, z, third);
    func_slot50(associated);
    unka0 = x;
    unka4 = y;
    return 1;
}

/** @brief Allocate and queue the container with default mode words and zero depth. */
s32 FieldClass15AE70::func_slot10(u32 associated, float x, float y, s32 code)
{
    unk10 = new (0) LibObject178660;
    if (queue_container(unk10) == 0 || !associated)
    {
        return 0;
    }
    lib_container_init(unk10, code, x, y, 0, 0.0f, 0);
    func_slot50(associated);
    unka0 = x;
    unka4 = y;
    return 1;
}

void FieldClass15AE70::func_slot0c()
{
    void* first = 0;
    while (func_002CF190(&unk74, &first))
    {
        ((LibClass171EA0*)first)->func_003EF740();
    }
    void* second = 0;
    while (func_002CEFA0(&unk80, &second))
    {
        ((LibClass171EA0*)second)->func_003EF740();
    }
    if (unk10)
    {
        static_cast<LibClass174610&>(*unk10).func_003EF740();
    }
    resident_enqueue_object(g_resident_release_queues, this);
}
