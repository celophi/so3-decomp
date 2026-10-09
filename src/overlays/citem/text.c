#include "include_asm.h"
#include "overlays/citem/text.h"
#include "main/resident_001001E0.h"
#include "main/resident_data.h"
#include "overlays/lib/ui_object.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/1067-00/text_0028E240.h"
#include "main/resident_00101260.h"
#include "main/resident_0011EE70.h"

#include "overlays/lib/text_004095C0.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/1067-00/text_002D5260.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "overlays/lib/text_0045AD10.h"

#define ANGLE_STEP_RADIANS 0.008726646f
#define ANGLE_LIMIT_RADIANS 0.5235988f

struct ItemListOwner
{
    ItemListNode* head;
    u32 count;
};

/** Native D_184280 window with a Field base, widget lists and a two-column grid. */
struct ItemRecord
{
    void* methods;
    u32 unk04;
    u8 unk08;
    u8 unk09;
    u16 unk0a;
    u8 unk0c;
    u8 unk0d;
    u8 unk0e[2];
    u32 unk10;
    ItemListOwner panels;
    u8 unk1c[4];
    u32 unk20;
    u8 unk24[0x50];
    ItemListOwner grids;
    u8 unk7c[0x1C];
    u32 unk98;
    u32 unk9c;
    u8 unka0[8];
    FieldObject23CEA0* grid;
    LibObject178750* first_text;
    LibObject178750* second_text;
};

struct StatusRecord
{
    u8 unk00[0x24];
    u32 unk24;
    s8 unk28;
    u8 unk29[0x13];
    u8 unk3c;
};

struct DisplayRecord
{
    void* methods;
    u8 unk04[0x5C];
    u8 unk60;
    u8 unk61[0x47];
    u8 unka8;
};

struct Record00349190
{
    u8 unk00[0x20];
    u32 unk20;
    u32 unk24;
    u32 unk28;
    float unk2c;
    u8 unk30[0x3C];
    u16 unk6c;
    u8 unk6e[0x46];
    u32 unkb4;
    u32 unkb8;
};

/** Partial transform receiver with MAIN table D_184400, a packet, and a release flag. */
struct Record00349250
{
    void* methods;
    u8 unk04[0x60];
    u8 dma_pending;
    u8 unk65[0x2B];
    void* notification_table;
    u8 unk94[0x34];
    ResidentPacket* packet;
    u8 unkcc[0x38];
    u8 release_pending;
};

struct Record00349C50
{
    u8 unk00[0x38];
    u32 unk38;
};

struct Record0034C800
{
    u8 unk00[0x40];
    u32 unk40;
};

struct Record00349BF0
{
    u8 unk00[0x2C];
    void* unk2c;
};

struct Record0034C7A0
{
    u8 unk00[0x38];
    void* unk38;
};

struct Record0034C6A0
{
    void* methods;
    u8 unk04[0x3C];
    u8 unk40;
};

/** Partial item window containing its coordinate selector. */
struct Record0034B770
{
    void* methods;
    u8 unk04[0xA8];
    FieldObject23B1D0* selection;
};

/** Partial item window with a coordinate selector and an owned display list. */
struct Record0034E7E0
{
    void* methods;
    u8 unk04[0xA8];
    FieldObject23B1D0* selection;
};

struct Record00350BD0
{
    u8 unk00[0x12C];
    u8 unk12c;
};

/** Counted payload list with a sentinel head and a method table. */
struct Record003540E0
{
    ItemListNode* head;
    u32 count;
    void* methods;
};

struct Record003542F0
{
    void* head;
    u32 count;
    void* methods;
};

/** Counted coordinate list with a sentinel head and a method table. */
struct Record00354740
{
    FieldNode23D310* head;
    u32 count;
    void* methods;
};

struct Record00353EF0
{
    void* methods;
    u8 unk04[0xE4];
    void* unke8;
    u8 unkec[0xC0];
    Record003542F0 embedded;
};

struct Record00350C20
{
    void* methods;
    u8 unk04[0xE4];
    void* unke8;
    u8 unkec[0x88];
    void* unk174;
};

struct SlotRecord
{
    u8 unk00[0x18];
    float unk18;
    float unk1c;
    u8 unk20[0x1C];
    u8 unk3c;
};

struct Record00350FC0
{
    u8 unk00[0xF0];
    struct SlotRecord* first[14];
    u8 unk128[0x10];
    struct SlotRecord* second[14];
    struct SlotRecord* third[14];
};

struct TransformRecord
{
    u8 unk00[0x20];
    Vector4 unk20;
    Vector4 unk30;
    Vector4 unk40;
    u8 unk50;
};

struct ScreenRecord
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[0x33];
    float unk70;
};

/** Observed C prefix of the native 0x90-byte LibClass178630 panel widget. */
typedef struct CitemPanelState
{
    void* methods;
    u8 unk04[0x34];
    u8 unk38;
    u8 unk39[7];
    void* allocation;
    u8 unk44[0xC];
    LibUiRect16 unk50;
    void* unk60;
} CitemPanelState;

/** Partial native D_1849F0 window, allocated with its 0xA8-byte Field base. */
struct Record00351F50
{
    void* methods;
    u8 unk04[0xC];
    LibObject178660* container;
};

struct ScreenOwner
{
    void* methods;
    u8 unk04[0xA4];
    struct ScreenRecord* unka8;
};

/** Observed prefix of native D_184DF0, with a Field base at four and an owned selection. */
struct Record00353850
{
    void* methods;
    u8 unk04[0x3C];
    FieldRecordSelection* selection;
    u8 unk44[0x70];
    s32 unkb4;
    u32 category;
};

struct Record00353A50
{
    void* methods;
};

struct Record00352960
{
    void* methods;
};

/** Observed C prefix of the native 0x114-byte LibObject178750 text widget. */
struct CitemTextDisplay
{
    void* methods;
    u8 unk04[0x14];
    LibUiRect16 rectangle;
    u8 unk28[0x10];
    u8 unk38;
    u8 unk39[3];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x40];
    float scale_x;
    float scale_y;
    u8 unk88[0xC];
    u32 color;
    u8 unk98[4];
    u32 mode;
};

/** Native D_1844B0 window with a 0xA8-byte Field base and three text widgets. */
struct Record00353E40
{
    void* methods;
    u8 unk04[0xC];
    LibObject178660* container;
    u8 unk14[0x94];
    LibObject178750* text[3];
    float width;
    float height;
    float scale;
    float unkc0;
    float row_spacing;
    float text_x;
    float text_y;
    float unkd0;
};

/** Partial item window with a delayed horizontal text scroller. */
struct Record00352EE0
{
    void* methods;
    u8 unk04[0xA4];
    struct CitemTextDisplay* text_display;
    s32 scroll_extent;
    s16 delay_frames;
    u8 scrolling;
    u8 unkb3[5];
    float start_x;
    float left_edge;
    float visible_width;
};

struct Record003531B0
{
    void* methods;
};

struct ItemListNode
{
    void* value;
    struct ItemListNode* next;
};

typedef struct ItemSortRecord
{
    u8 unk00[2];
    u16 table_index;
} ItemSortRecord;

typedef ItemCreationCategoryDefinition ItemSortDefinition;


struct AngleState
{
    u8 unk00[0x6C];
    float unk6c;
};

struct AngleOwner
{
    u8 unk00[0x1B0];
    u8 unk1b0;
    u8 unk1b1[7];
    struct AngleState* unk1b8;
};

struct ControlScreen
{
    u8 unk00[0x3C];
    u8 unk3c;
    u8 unk3d[2];
    u8 unk3f;
    u8 unk40[0x30];
    float unk70;
};

struct ControlOwner
{
    u8 unk00[0xAC];
    struct ControlScreen* unkac;
};

/** Prefix of the native D_15B020 controller produced by Field002D1550. */
typedef struct CitemWindowController
{
    u8 unk00[0x14];
    struct FieldClass153E30* selected;
} CitemWindowController;

/** Prefix of native D_153D40 runtime storage produced by Field002630F0. */
typedef struct CitemRuntime643C
{
    u8 unk00[0x10];
    CitemWindowController* controller;
    u8 unk14[0xC];
    FieldBufferSlots* buffers;
} CitemRuntime643C;

/** The allocation helper receives this resident storage opaquely. */
extern ResidentObject1B64F8* D_001B64F8;
extern CitemRuntime643C* D_001B643C;

/** Observed prefix of the native 0x100-byte LibObject172410 item-code widget. */
typedef struct CitemAllocationDisplay
{
    void* methods;
    u8 unk04[0x38];
    u8 update;
    u8 unk3d;
    u8 unk3e[0xBE];
    u16 code;
    u8 unkfe;
    u8 unkff;
} CitemAllocationDisplay;

/** Observed prefix of the native 0x128-byte ItemCreationOptionResourceDisplay widget. */
typedef struct CitemResourceDisplay
{
    u8 unk00[0x3D];
    u8 unk3d;
} CitemResourceDisplay;


/** Byte prefix of the actual packed 16-byte allocation record. */
typedef struct CitemAllocationRecord
{
    u8 unk00[0xC];
    u8 unk0c;
} CitemAllocationRecord;

/** Observed prefix of the native 0x1C0-byte D_1847B0 window, with six pairs of code and resource widgets. */
struct Record0034E8B0
{
    void* methods;
    u8 unk04[0xA4];
    struct ControlScreen* unka8;
    struct ControlScreen* unkac;
    u8 unkb0[0x80];
    s32 record_count;
    u8 unk134[4];
    struct ControlScreen* first[6];
    u8 unk150[0x24];
    struct ControlScreen* unk174;
    u8 unk178[8];
    struct ControlScreen* second[6];
};

extern u8 D_184280[];
extern u8 D_184390[];
extern u8 D_1844B0[];
extern u8 D_1849F0[];
extern u8 D_184AF0[];
extern u8 D_184BF0[];
extern u8 D_184CF0[];
extern u8 D_1844A0[];
extern u8 D_1843F0[];
extern u8 D_175110[];
extern u8 D_1848D0[];
extern u8 D_1849C4[];
extern u8 D_1847B0[];
extern u8 D_1848A4[];
extern u8 D_184ED8[];
extern u8 D_184EC8[];
extern u8 D_184EB8[];
extern u8 D_50CD30[];
extern LibWidgetColors4C5590 D_354C40;
extern void func_2CEAF0(void* object, s32 flags);
extern void func_100B40(void* object);
extern void func_4CE4C0(Vector4* destination, const Vector4* source);
extern void func_2BC410(Record00349BF0* record, s32 flag);
extern void func_4618F0(void* record, s32 flag);
extern void func_4C48B0(void* record, s32 flag);
extern void func_003541F0(Record003540E0* record);
extern void func_00354400(Record003542F0* record);
extern void func_003547C0(Record00354740* record);
extern void func_2CD9F0(void* record, s32 flag);
extern void func_4C4A90(void* object);
extern void func_44B110(void* object, s32 arg1, s32 arg2, void* arg3, float value, s32 flag);

/** @brief Allocate and construct the native panel widget. @return The panel storage, or null. */
static inline LibClass178630* allocate_panel(void)
{
    void* storage = func_00100AC0(0x90, 0);
    LibClass178630* panel = (LibClass178630*)storage;
    if (storage != 0)
    {
        CitemPanelState* state = (CitemPanelState*)panel;
        func_004C4960((LibClass178600*)panel);
        state->methods = D_178630;
        state->allocation = 0;
        state->unk50.unk0c = 0.0f;
        state->unk50.unk08 = 0.0f;
        state->unk50.unk04 = 0.0f;
        state->unk50.unk00 = 0.0f;
        state->unk38 = 1;
        state->unk60 = 0;
    }
    return panel;
}

/** @brief Allocate the native text widget with an empty rectangle. @return The text-widget storage, or null. */
static inline LibObject178750* allocate_text_widget(void)
{
    void* storage = func_00100AC0(0x114, 0);
    LibObject178750* widget = (LibObject178750*)storage;
    if (storage != 0)
    {
        struct CitemTextDisplay* state = (struct CitemTextDisplay*)widget;
        func_00464B10((LibClass174EF0*)widget);
        state->methods = D_178750;
        state->unk38 = 11;
        func_004C7FB0(widget, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    return widget;
}

/** @brief Set the text mode and mark the widget for update. @param widget Text widget. @param mode Text mode. */
static inline void set_text_mode(LibObject178750* widget, u32 mode)
{
    struct CitemTextDisplay* text = (struct CitemTextDisplay*)widget;
    text->mode = mode;
    text->unk3c = 1;
}

/** @brief Set the packed text color and mark the widget for update. @param widget Text widget. @param color Packed color. */
static inline void set_text_color(LibObject178750* widget, u32 color)
{
    struct CitemTextDisplay* text = (struct CitemTextDisplay*)widget;
    text->color = color;
    text->unk3c = 1;
}

/** @brief Apply the window scale to one text widget. @param object Text window. @param index Text-widget index. */
static inline void scale_window_text(Record00353E40* object, u32 index)
{
    struct CitemTextDisplay* text = (struct CitemTextDisplay*)object->text[index];
    float scale = object->scale;
    text->scale_y = scale;
    text->scale_x = scale;
    text->unk3c = 1;
}

/**
 * @brief Allocate and populate a missing record selection.
 * @param object Receiver that owns the selection.
 * @return One after successful population, or zero if already present or initialization fails.
 */
static inline u8 create_record_selection(Record00353850* object)
{
    FieldRecordSelection* selection;
    if (object->selection != 0)
    {
        return 0;
    }
    selection = (FieldRecordSelection*)func_00100AC0(sizeof(FieldRecordSelection), 0);
    if (selection != 0)
    {
        selection = func_0028E4D0(selection);
    }
    object->selection = selection;
    if (object->selection == 0)
    {
        return 0;
    }
    if ((u8)func_0028E3D0(object->selection) == 0)
    {
        return 0;
    }
    return 1;
}

/**
 * @brief View the transform receiver through its native secondary DMA interface.
 * @param object Complete transform receiver.
 * @return Interface at offset 0x90, or null for a null receiver.
 */
static inline struct LibClass171FF0* transform_notification(Record00349250* object)
{
    void* notification = object;

    if (object != 0)
    {
        notification = (u8*)notification + 0x90;
    }
    return (struct LibClass171FF0*)notification;
}

/**
 * @brief Allocate a coordinate node with its scalar values initially clear.
 * @return Allocated node, or null.
 */
static inline FieldNode23D310* allocate_coordinate_node(void)
{
    FieldNode23D310* node = func_00100AC0(sizeof(FieldNode23D310), 0);

    if (node != 0)
    {
        node->y = 0.0f;
        node->x = 0.0f;
    }
    return node;
}

/**
 * @brief Store display bounds and mark them changed.
 * @param display Display to update.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Display width.
 * @param height Display height.
 */
static inline void set_text_bounds(struct CitemTextDisplay* display, float x, float y, float width, float height)
{
    display->rectangle.unk00 = x;
    display->rectangle.unk04 = y;
    display->rectangle.unk08 = width;
    display->rectangle.unk0c = height;
    display->unk3c = 1;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003483C0);

ItemRecord* func_00348400(ItemRecord* item, s16 flag)
{
    if (item != 0)
    {
        item->methods = D_184280;
        func_2CEAF0(item, 0);
        if (flag > 0)
        {
            func_100B40(item);
        }
    }
    return item;
}

void func_00348460(ItemRecord* item, u8 value)
{
    item->unk0c = value;
}

u8 func_00348470(ItemRecord* item)
{
    return item->unk0c;
}

void func_00348480(ItemRecord* item, u8 value)
{
    item->unk08 = value;
}

u8 func_00348490(ItemRecord* item)
{
    return item->unk08;
}

void func_003484A0(ItemRecord* item, u16 value)
{
    item->unk0a = value;
}

u16 func_003484B0(ItemRecord* item)
{
    return item->unk0a;
}

void func_003484C0(ItemRecord* item, u32 value)
{
    item->unk98 = value;
}

u32 func_003484D0(ItemRecord* item)
{
    return item->unk98;
}

void func_003484E0(ItemRecord* item, u32 value)
{
    item->unk9c = value;
}

u32 func_003484F0(ItemRecord* item)
{
    return item->unk9c;
}

void func_00348500(ItemRecord* item, u32 value)
{
    item->unk04 = value;
}

u32 func_00348510(ItemRecord* item)
{
    return item->unk04;
}

u32 func_00348520(ItemRecord* item)
{
    return item->unk10;
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

void func_003486F0(void* object)
{
}

void func_00348700(void* object)
{
}

u8 func_00348710(ItemRecord* item)
{
    return item->unk0d;
}

void func_00348720(ItemRecord* item, u8 value)
{
    item->unk0d = value;
}

void func_00348730(void* object)
{
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00348740);

u32 func_003487B0(ItemRecord* item)
{
    return item->unk20;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003487C0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00348880);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00348940);

void func_003489F0(ItemRecord* item, u32 value)
{
    item->unk20 = value;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00348A00);

s32 item_initialize_choice_window(ItemRecord* object, u32 associated)
{
    LibClass178630* panel;
    LibObject178750* text;
    FieldObject23CEA0* grid;
    LibWidgetColors4C5590 colors;
    func_002CE8D0((FieldObjectCE8D0*)object, associated, 145.0f, 170.0f, 13);
    panel = allocate_panel();
    func_004C5A80(panel, 0, 0.0f, 0.0f, 350.0f, 176.0f, 88.0f);
    func_004C6190((LibObject178660*)object->unk10, (LibClass178600*)panel);
    func_003546B0(&object->panels, panel);
    panel = allocate_panel();
    func_004C5A80(panel, 0, 0.0f, 0.0f, 350.0f, 48.0f, 88.0f);
    func_004C6190((LibObject178660*)object->unk10, (LibClass178600*)panel);
    colors = D_354C40;
    func_4C5590(panel, &colors);
    func_003546B0(&object->panels, panel);
    text = allocate_text_widget();
    func_004C7FE0(text, associated, 0x1BA1, 0, 0.0f, 12.0f, 350.0f, 48.0f);
    set_text_mode(text, 1);
    func_004C6190((LibObject178660*)object->unk10, (LibClass178600*)text);
    text = allocate_text_widget();
    func_004C7FE0(text, associated, 0x1BA2, 0, 0.0f, 64.0f, 350.0f, 64.0f);
    set_text_mode(text, 1);
    func_004C6190((LibObject178660*)object->unk10, (LibClass178600*)text);
    object->first_text = allocate_text_widget();
    object->second_text = allocate_text_widget();
    func_004C7FE0(object->first_text, associated, 0x1BA3, 0, 122.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190((LibObject178660*)object->unk10, (LibClass178600*)object->first_text);
    func_004C7FE0(object->second_text, associated, 0x1BA4, 0, 212.0f, 132.0f, 0.0f, 0.0f);
    func_004C6190((LibObject178660*)object->unk10, (LibClass178600*)object->second_text);
    grid = (FieldObject23CEA0*)func_00100AC0(0x130, 0);
    if (grid != 0)
    {
        grid = func_0023D170(grid);
    }
    object->grid = grid;
    func_0023CE80((FieldObject23CE80*)object->grid, 2, 1);
    func_0023CE60((FieldObject23CE80*)object->grid, 80.0f, 0.0f);
    object->grid->unkF2 = 0;
    func_0023CF50((FieldObject23CEB0*)object->grid, 1, 265.0f, 302.0f);
    object->grid->unkAD = 0;
    func_003544C0(&object->grids, object->grid);
    if (object->grid->unk114 != 0)
    {
        set_text_color(object->first_text, 0x808080);
        set_text_color(object->second_text, 0x288080);
    }
    else
    {
        set_text_color(object->first_text, 0x288080);
        set_text_color(object->second_text, 0x808080);
    }
    return 1;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003490F0);

s32 func_00349190(Record00349190* record, s32 arg1, s32 arg2, void* arg3, float first, float second, float third)
{
    record->unk6c = 0x6006;
    record->unk20 = 0;
    record->unk24 = 0;
    record->unk28 = 0;
    record->unk2c = 1.0f;
    func_44B110(record, arg1, arg2, arg3, third, 0);
    record->unkb4 = 0;
    record->unkb8 = 0;
    return 1;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003491F0);

void item_submit_transform_packet(Record00349250* object)
{
    object->dma_pending = 1;
    if (object->packet != 0)
    {
        func_0011F770(object->packet, transform_notification(object));
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349250);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003492F0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349B90);

Record00349BF0* func_00349BF0(Record00349BF0* record, s16 flag)
{
    if (record != 0)
    {
        record->unk2c = D_1844A0;
        func_2BC410(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u32 func_00349C50(Record00349C50* record)
{
    return record->unk38;
}

/**
 * @brief Initialize a panel with three positioned and scaled text widgets.
 * @param object Text-window receiver.
 * @param associated Associated resource source word.
 * @return One after initialization.
 */
s32 item_initialize_text_panel(Record00353E40* object, u32 associated)
{
    LibClass178630* panel;
    object->width = 192.0f;
    object->height = 104.0f;
    func_002CE760((FieldClass15AE70*)object, associated, 0, 9, 0x578, 16.0f, 360.0f, 0.0f);
    panel = allocate_panel();
    func_004C5A80(panel, 0, 0.0f, 0.0f, object->width, object->height, 88.0f);
    func_004C6190(object->container, (LibClass178600*)panel);
    object->text[0] = allocate_text_widget();
    object->text[1] = allocate_text_widget();
    object->text[2] = allocate_text_widget();
    object->scale = 0.85f;
    object->unkc0 = 14.0f;
    object->row_spacing = 28.0f;
    object->text_x = 16.0f;
    object->text_y = object->height / 3.0f - object->row_spacing / 2.0f;
    object->unkd0 = 3.0f;
    func_004C7FE0(object->text[0], associated, 0x1B80, 0, object->text_x, object->text_y, 0.0f, 0.0f);
    func_004C7FE0(object->text[1], associated, 0x1B7D, 0, object->text_x, object->text_y + object->row_spacing, 0.0f, 0.0f);
    func_004C7FE0(object->text[2], associated, 0x1B7E, 0, 80.0f + object->text_x, object->text_y + object->row_spacing, 0.0f, 0.0f);
    scale_window_text(object, 0);
    scale_window_text(object, 1);
    scale_window_text(object, 2);
    func_004C6190(object->container, (LibClass178600*)object->text[0]);
    func_004C6190(object->container, (LibClass178600*)object->text[1]);
    func_004C6190(object->container, (LibClass178600*)object->text[2]);
    ((struct CitemTextDisplay*)object->text[0])->unk3f = 0;
    return 1;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00349F80);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034AD00);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034AE60);

/**
 * @brief Test whether the coordinate selector's control byte is clear.
 * @param selection Coordinate selector to inspect.
 * @return One when the control byte is zero, otherwise zero.
 */
static inline s32 item_selection_control_is_clear(FieldObject23B1D0* selection)
{
    if (selection->flag75)
    {
        return 0;
    }
    return 1;
}

void item_select_previous_entry(Record0034B770* owner)
{
    FieldObject23B1D0* selection = owner->selection;
    s32 index;
    if (item_selection_control_is_clear(selection))
    {
        return;
    }
    index = selection->selected - 1;
    if (index < 0)
    {
        index = 7;
    }
    func_0023B1D0(selection, index, 0);
}

void item_select_next_entry(Record0034B770* owner)
{
    FieldObject23B1D0* selection = owner->selection;
    s32 index;
    if (item_selection_control_is_clear(selection))
    {
        return;
    }
    index = selection->selected + 1;
    if (index >= 8)
    {
        index = 0;
    }
    func_0023B1D0(selection, index, 0);
}

void item_select_second_row(Record0034B770* owner)
{
    FieldObject23B1D0* selection = owner->selection;
    s32 index;
    if (item_selection_control_is_clear(selection))
    {
        return;
    }
    switch (selection->selected)
    {
    case 0:
        index = 3;
        break;
    case 1:
        index = 5;
        break;
    case 2:
        index = 6;
        break;
    default:
        return;
    }
    func_0023B1D0(selection, index, 0);
}

void item_select_first_row(Record0034B770* owner)
{
    FieldObject23B1D0* selection = owner->selection;
    s32 index;
    if (item_selection_control_is_clear(selection))
    {
        return;
    }
    switch (selection->selected)
    {
    case 3:
        index = 0;
        break;
    case 4:
        index = 1;
        break;
    case 5:
        index = 1;
        break;
    case 6:
        index = 2;
        break;
    case 7:
        index = 2;
        break;
    default:
        return;
    }
    func_0023B1D0(selection, index, 0);
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034B060);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034B1B0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034B770);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034B830);

Record0034C6A0* func_0034C6A0(Record0034C6A0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_175110;
        func_4618F0(&record->unk40, -1);
        func_4C48B0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034C710);

Record0034C7A0* func_0034C7A0(Record0034C7A0* record, s16 flag)
{
    if (record != 0)
    {
        record->unk38 = D_1843F0;
        func_4618F0(record, -1);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

u32 func_0034C800(Record0034C800* record)
{
    return record->unk40;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034C810);

void item_list_select_previous_entry(Record0034E7E0* owner)
{
    FieldObject23B1D0* selection = owner->selection;
    s32 index;
    if (item_selection_control_is_clear(selection))
    {
        return;
    }
    index = selection->selected - 1;
    if (index < 0)
    {
        index = 7;
    }
    func_0023B1D0(selection, index, 0);
}

void item_list_select_next_entry(Record0034E7E0* owner)
{
    FieldObject23B1D0* selection = owner->selection;
    s32 index;
    if (item_selection_control_is_clear(selection))
    {
        return;
    }
    index = selection->selected + 1;
    if (index >= 8)
    {
        index = 0;
    }
    func_0023B1D0(selection, index, 0);
}

void item_list_select_second_row(Record0034E7E0* owner)
{
    FieldObject23B1D0* selection = owner->selection;
    s32 index;
    if (item_selection_control_is_clear(selection))
    {
        return;
    }
    switch (selection->selected)
    {
    case 0:
        index = 3;
        break;
    case 1:
        index = 5;
        break;
    case 2:
        index = 6;
        break;
    default:
        return;
    }
    func_0023B1D0(selection, index, 0);
}

void item_list_select_first_row(Record0034E7E0* owner)
{
    FieldObject23B1D0* selection = owner->selection;
    s32 index;
    if (item_selection_control_is_clear(selection))
    {
        return;
    }
    switch (selection->selected)
    {
    case 3:
        index = 0;
        break;
    case 4:
        index = 1;
        break;
    case 5:
        index = 1;
        break;
    case 6:
        index = 2;
        break;
    case 7:
        index = 2;
        break;
    default:
        return;
    }
    func_0023B1D0(selection, index, 0);
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034CEE0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034D030);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034D170);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034E740);

void item_queue_transform_release(Record00349250* object)
{
    object->release_pending = 1;
    func_0044B210((LibClass174610*)object);
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034E7E0);

void func_0034E8B0(Record0034E8B0* record, u8 flag, s32 control_flag)
{
    record->first[0]->unk3f = flag;
    record->second[0]->unk3f = flag;
    record->first[1]->unk3f = flag;
    record->second[1]->unk3f = flag;
    record->first[2]->unk3f = flag;
    record->second[2]->unk3f = flag;
    record->first[3]->unk3f = flag;
    record->second[3]->unk3f = flag;
    record->first[4]->unk3f = flag;
    record->second[4]->unk3f = flag;
    record->first[5]->unk3f = flag;
    record->second[5]->unk3f = flag;
    if (record->unk174 != 0)
    {
        record->unk174->unk3f = 1;
    }
    if (record->unkac != 0)
    {
        record->unkac->unk3f = control_flag;
        if (control_flag != 0)
        {
            struct ControlScreen* screen = record->unkac;
            screen->unk70 = 128.0f;
            screen->unk3c = 1;
        }
        else
        {
            struct ControlScreen* screen = record->unkac;
            screen->unk70 = 64.0f;
            screen->unk3c = 1;
        }
    }
    if (record->unka8 != 0)
    {
        record->unka8->unk3f = control_flag;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034E980);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034EB40);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034EE60);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034EF40);

void func_0034F2E0(AngleOwner* owner)
{
    if (owner->unk1b0 != 0)
    {
        struct AngleState* angle = owner->unk1b8;
        if (angle != 0)
        {
            float value = angle->unk6c;
            value -= ANGLE_STEP_RADIANS;
            if (value < 0.0f)
            {
                value = 0.0f;
            }
            angle->unk6c = value;
        }
    }
}

void func_0034F340(AngleOwner* owner)
{
    if (owner->unk1b0 != 0)
    {
        struct AngleState* angle = owner->unk1b8;
        if (angle != 0)
        {
            float value = angle->unk6c;
            value += ANGLE_STEP_RADIANS;
            if (value > ANGLE_LIMIT_RADIANS)
            {
                value = ANGLE_LIMIT_RADIANS;
            }
            angle->unk6c = value;
        }
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034F3A0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034F970);

void item_update_allocation_page(Record0034E8B0* object, s32 first_index)
{
    ItemCreationAllocationRecord* records[99];
    Record00353850* selected = (Record00353850*)D_001B643C->controller->selected;
    if (selected != 0)
    {
        selected = (Record00353850*)((u8*)selected - 4);
    }
    if (selected->unkb4 != 7)
    {
        u32 category = selected->category;
        s32 index;
        func_0013A678(records, 0, sizeof(records));
        object->record_count = func_0040CF90(D_001B64F8, records, (u16)category);
        for (index = 0; index < 6; index++)
        {
            if (records[first_index + index] != 0)
            {
                CitemAllocationDisplay* display = (CitemAllocationDisplay*)object->first[index];
                u8 value_byte = ((CitemAllocationRecord*)records[first_index + index])->unk0c & 0x7F;
                s32 count = 0;
                s32 detail;
                void* allocation;
                FieldResourceRecord* record;
                display->code = category;
                display->unkfe = value_byte;
                display->update = 1;
                for (detail = 0; detail < 8; detail++)
                {
                    u16 value = func_0040D930(records[first_index + index], detail);
                    if (value != 0 && value != 700)
                    {
                        count++;
                    }
                }
                allocation = func_002D3D80(D_001B643C->buffers, 14);
                record = func_002D3CC0(D_001B643C->buffers, count + 60);
                func_002D5CF0((ItemCreationOptionResourceDisplay*)object->second[index], allocation, record, 14);
                ((CitemAllocationDisplay*)object->first[index])->unk3d = 1;
                ((CitemResourceDisplay*)object->second[index])->unk3d = 1;
            }
            else
            {
                ((CitemAllocationDisplay*)object->first[index])->unk3d = 0;
                ((CitemResourceDisplay*)object->second[index])->unk3d = 0;
            }
        }
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034FB80);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_0034FE70);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350B60);

void func_00350BD0(Record00350BD0* record, u8 value)
{
    record->unk12c = value;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350BE0);

Record00350C20* func_00350C20(Record00350C20* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_1847B0;
        record->unke8 = D_1848A4;
        if (record->unk174 != 0)
        {
            func_4C4A90(record->unk174);
        }
        func_2CD9F0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350CB0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350D50);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00350DD0);

void func_00350F70(ControlOwner* owner, s32 ignored, s32 flag)
{
    if (owner->unkac != 0)
    {
        owner->unkac->unk3f = flag;
        if (flag != 0)
        {
            struct ControlScreen* screen = owner->unkac;
            screen->unk70 = 128.0f;
            screen->unk3c = 1;
        }
        else
        {
            struct ControlScreen* screen = owner->unkac;
            screen->unk70 = 64.0f;
            screen->unk3c = 1;
        }
    }
}

void func_00350FC0(Record00350FC0* owner, float start)
{
    s32 index;
    float value = start + 16.0f;
    for (index = 0; index < 14; index++)
    {
        struct SlotRecord* slot = owner->first[index];
        slot->unk18 = 24.0f;
        slot->unk1c = value;
        slot->unk3c = 1;
        slot = owner->second[index];
        slot->unk18 = 326.0f;
        slot->unk1c = value;
        slot->unk3c = 1;
        slot = owner->third[index];
        slot->unk18 = 334.0f;
        slot->unk1c = value;
        slot->unk3c = 1;
        value += 28.0f;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00351040);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003512C0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00351770);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003518B0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00351D50);

s32 func_00351E40(const ItemListNode* left, const ItemListNode* right)
{
    const ItemSortRecord* first = (const ItemSortRecord*)left->value;
    const ItemSortRecord* second = (const ItemSortRecord*)right->value;
    const ItemSortDefinition* first_definition = &D_001B64F0[first->table_index];
    const ItemSortDefinition* second_definition = &D_001B64F0[second->table_index];
    return (first_definition->sort_key_bits & 0x3FF) - (second_definition->sort_key_bits & 0x3FF);
}

s32 item_initialize_panel(Record00351F50* object, u32 associated)
{
    LibClass178630* panel;
    func_002CE760((FieldClass15AE70*)object, associated, 0, 9, 0x578, 204.0f, 72.0f, 0.0f);
    panel = allocate_panel();
    func_004C5A80(panel, 1, 0.0f, 0.0f, 412.0f, 396.0f, 88.0f);
    func_004C6190(object->container, (LibClass178600*)panel);
    return 1;
}

ScreenOwner* func_00351F50(ScreenOwner* owner, s16 flag)
{
    if (owner != 0)
    {
        owner->methods = D_1849F0;
        func_2CEAF0(owner, 0);
        if (flag > 0)
        {
            func_100B40(owner);
        }
    }
    return owner;
}

void func_00351FB0(ScreenOwner* owner)
{
    struct ScreenRecord* screen = owner->unka8;
    if (screen != 0)
    {
        screen->unk70 = 128.0f;
        screen->unk3c = 1;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00351FE0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352010);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003521D0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352340);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003524B0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352540);

Record00352960* func_00352960(Record00352960* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184AF0;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

/**
 * @brief Hold the text at its starting position, then scroll and wrap it horizontally.
 * @param record Window storing the display, delay and scrolling bounds.
 */
void item_update_horizontal_scroll(Record00352EE0* record)
{
    struct CitemTextDisplay* display = record->text_display;
    float x = display->rectangle.unk00;
    float y = display->rectangle.unk04;
    float width = display->rectangle.unk08;
    float height = display->rectangle.unk0c;

    if (record->scrolling == 0)
    {
        set_text_bounds(display, record->start_x, y, width, height);
        record->delay_frames++;
        if (!((float)record->delay_frames <= 120.0f))
        {
            record->delay_frames = 0;
            record->scrolling = 1;
        }
        return;
    }
    {
        float left = record->left_edge;
        x -= 108.0f * D_001B6690;
        if (x < left - (float)record->scroll_extent)
        {
            x = 2.0f + (left + record->visible_width);
        }
        set_text_bounds(display, x, y, width, height);
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352AB0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352B40);

Record00352EE0* func_00352EE0(Record00352EE0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184BF0;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00352F40);

Record003531B0* func_003531B0(Record003531B0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184CF0;
        func_2CEAF0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353210);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353270);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353620);

s32 item_initialize_record_selection(Record00353850* object)
{
    u8 created = create_record_selection(object);
    if (created == 0)
    {
        return 0;
    }
    func_00101440(func_00101290(func_0010D8E0()), 4);
    return 1;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003537D0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353850);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353910);

void func_00353A30(void* object)
{
}

void func_00353A40(void* object)
{
}

Record00353A50* func_00353A50(Record00353A50* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184390;
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353AA0);

s32 func_00353B00(void* object)
{
    return 3;
}

void func_00353B10(void* object)
{
}

void func_00353B20(void* object)
{
}

void func_00353B30(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk20 = *value;
}

void func_00353B50(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk20 = *value;
}

void func_00353B70(TransformRecord* record, float x, float y, float z)
{
    record->unk50 = 1;
    record->unk20.x = x;
    record->unk20.y = y;
    record->unk20.z = z;
    record->unk20.w = 1.0f;
}

void func_00353B90(TransformRecord* record, float x, float y, float z, float w)
{
    record->unk50 = 1;
    record->unk30.x = x;
    record->unk30.y = y;
    record->unk30.z = z;
    record->unk30.w = w;
}

void func_00353BB0(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk30 = *value;
}

void func_00353BD0(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk30 = *value;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353BF0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353C20);

void func_00353C50(TransformRecord* record, float x, float y, float z)
{
    Vector4 value;
    record->unk50 = 1;
    value.x = x;
    value.y = y;
    value.z = z;
    value.w = 1.0f;
    func_4CE4C0(&record->unk30, &value);
}

void func_00353C90(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk40 = *value;
}

void func_00353CB0(TransformRecord* record, const Vector4* value)
{
    record->unk50 = 1;
    record->unk40 = *value;
}

void func_00353CD0(TransformRecord* record, float x, float y, float z)
{
    record->unk50 = 1;
    record->unk40.x = x;
    record->unk40.y = y;
    record->unk40.z = z;
}

s32 func_00353CF0(void* object)
{
    return 0;
}

s32 func_00353D00(float value)
{
    return value < 0.0f;
}

u8* func_00353D20(void)
{
    return D_50CD30;
}

s32 func_00353D30(void* object)
{
    return 0;
}

void func_00353D40(void* object)
{
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00353D50);

void func_00353E10(void* object)
{
}

s32 func_00353E20(void* object)
{
    return 14;
}

void func_00353E30(DisplayRecord* display)
{
    display->unk60 = display->unka8;
}

DisplayRecord* func_00353E40(DisplayRecord* display, s16 flag)
{
    if (display != 0)
    {
        display->methods = D_1844B0;
        func_2CEAF0(display, 0);
        if (flag > 0)
        {
            func_100B40(display);
        }
    }
    return display;
}

void func_00353EA0(void* object)
{
}

void func_00353EB0(void* object)
{
}

void func_00353EC0(void* object)
{
}

s32 func_00353ED0(void* object)
{
    return 0;
}

s32 func_00353EE0(void* object)
{
    return 0;
}

Record00353EF0* func_00353EF0(Record00353EF0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_1848D0;
        record->unke8 = D_1849C4;
        func_003542F0(&record->embedded, -1);
        func_2CD9F0(record, 0);
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

void func_00353F70(StatusRecord* state, u32 value)
{
    state->unk24 = value;
}

u32 func_00353F80(StatusRecord* state)
{
    return state->unk24;
}

void func_00353F90(StatusRecord* state, s8 value)
{
    state->unk28 = value;
}

s8 func_00353FA0(StatusRecord* state)
{
    return state->unk28;
}

s32 func_00353FB0(void* object)
{
    return 0;
}

s32 func_00353FC0(void* object)
{
    return 0;
}

void func_00353FD0(void* object)
{
}

void func_00353FE0(void* object)
{
}

void func_00353FF0(void* object)
{
}

void func_00354000(void* object)
{
}

s32 func_00354010(void* object)
{
    return 0;
}

s32 func_00354020(void* object)
{
    return 0;
}

s32 func_00354030(void* object)
{
    return 0;
}

s32 func_00354040(void* object)
{
    return 4;
}

u32 func_00354050(StatusRecord* state)
{
    return state->unk3c & 1;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354060);

Record003540E0* func_003540E0(Record003540E0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184ED8;
        func_003541F0(record);
        if (record->head != 0)
        {
            func_100B40(record->head);
            record->head = 0;
        }
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

void item_append_list_value(Record003540E0* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003541F0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354270);

Record003542F0* func_003542F0(Record003542F0* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184EC8;
        func_00354400(record);
        if (record->head != 0)
        {
            func_100B40(record->head);
            record->head = 0;
        }
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

void func_00354370(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354400);

ItemListNode* func_00354480(ItemListOwner* owner, s32 index)
{
    ItemListNode* node = owner->head->next;
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

void func_003544C0(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

void func_00354550(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

ItemListNode* func_003545E0(ItemListOwner* owner, s32 index)
{
    ItemListNode* node = owner->head->next;
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

void func_00354620(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

void func_003546B0(ItemListOwner* owner, void* value)
{
    ItemListNode* node = (ItemListNode*)func_00100AC0(sizeof(ItemListNode), 0);
    if (node != 0)
    {
        ItemListNode* tail;
        node->value = value;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

Record00354740* func_00354740(Record00354740* record, s16 flag)
{
    if (record != 0)
    {
        record->methods = D_184EB8;
        func_003547C0(record);
        if (record->head != 0)
        {
            func_100B40(record->head);
            record->head = 0;
        }
        if (flag > 0)
        {
            func_100B40(record);
        }
    }
    return record;
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003547C0);

void item_append_selector_coordinate(Record00354740* owner, CitemCoordinate2 value)
{
    FieldNode23D310* node = allocate_coordinate_node();

    if (node != 0)
    {
        FieldNode23D310* tail;

        node->x = value.x;
        node->y = value.y;
        node->next = 0;
        tail = owner->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        owner->count++;
    }
}

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_003548F0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354980);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AA0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AB0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AC0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AD0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AE0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354AF0);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B00);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B10);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B20);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B30);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B40);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B50);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B60);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B70);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B80);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354B90);

INCLUDE_ASM("build/overlays/citem/asm/nonmatchings/text", func_00354BA0);
