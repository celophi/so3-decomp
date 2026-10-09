#include "include_asm.h"
#include "overlays/cstatus/text.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_0013C948.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_0028E240.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/1067-00/field_runtime.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/text_003F90C0.h"
#include "overlays/lib/text_004095C0.h"

/** Partial 0x114-byte record with display data at offset 0x20. */
struct StatusDisplayRecord
{
    u8 unk00[0x20];
    char data[0xF4];
};
/** Partial 0x114-byte detail with six encoded entries and their checksum. */
struct StatusProtectedEntries
{
    u8 unk00[0x41];
    u8 values[6];
    u8 unk47[0xBD];
    u32 checksum;
    u8 unk108[0xC];
};
/**
 * @brief Read one encoded entry when its six-byte checksum is valid.
 * @param record Detail record containing the protected entries.
 * @param index Signed entry index, from zero through five.
 * @return Decoded entry, or zero for an invalid checksum or index.
 */
static inline s32 status_protected_entry(StatusProtectedEntries* record, s32 index)
{
    u32 checksum = 0x8D3C43F9;
    for (s32 entry = 0; entry < 6; entry++)
    {
        checksum ^= record->values[entry];
        checksum = checksum * 2 + 0x31;
    }
    if (record->checksum != checksum)
    {
        return 0;
    }
    if (index < 0)
    {
        return 0;
    }
    if (static_cast<u32>(index) >= 6)
    {
        return 0;
    }
    return record->values[index] ^ 0x77;
}

/** Saved section containing the ten fixed-width character names. */
struct StatusNameSection
{
    u8 unk00[0xC6B0];
    s8 names[10][24];
};
/** Typed display payload and forward link in a status list. */
struct StatusDisplayNode
{
    LibClass178600* value;
    StatusDisplayNode* next;
};
/** Partial 0x114-byte status record containing the selected variant. */
struct StatusVariantRecord
{
    u8 unk00[0xE7];
    u8 variant;
    u8 unke8[0x2C];
};

/** Saved section flag selecting the nested status display geometry. */
struct StatusWindowSection
{
    u8 unk00[0x18C];
    u8 enabled;
};

/** Partial saved section containing variant limits and their checksum. */
struct StatusVariantSection
{
    u8 unk00[0x1A0];
    u8 values[4];
    u16 checksum;
    u16 seed;
};

/** Resource descriptor with its signed size at offset 0x40. */
struct StatusAlignedResource
{
    u8 unk00[0x40];
    s32 size;
};
/** Partial Field runtime containing the active resource and request code. */
struct StatusRuntimeResource
{
    u8 unk00[0x514];
    s32 resource;
    u32 code;
};
/** Partial status window holding a Lib container at offset 0xE0. */
struct StatusContainerWindow : public FieldClass15AE70
{
    u8 unka8[0x38];
    LibObject178660* container;
};

/** Partial status resource state with resident vtable at 0x188CC0. */
struct StatusResourceState : public FieldClass153E30
{
    s32 resource;
    u8 flag_38 : 1;
    u8 unknown_38 : 7;
    u8 unknown_39[3];
    FieldRecordSelection* selection;
    u16 field_40;
    u16 field_42;
    StatusScrollState* scroll;
};

struct StatusRuntimeCallbacks;

/** Partial resident runtime view used by this overlay. */
struct StatusRuntime
{
    u8 unk00[0xC];
    void* unk0c;
    StatusRuntimeCallbacks* unk10;
    u8 unk14[8];
    void* unk1c;
    FieldBufferSlots* slots;
};

struct StatusObject
{
    void* methods;
    u8 unknown_04[0x30];
    u32 field_34;
    u8 flag_38 : 1;
    u8 unknown_38 : 7;
    u8 unknown_39[3];
    u32 field_3C;
    u16 field_40;
    u16 field_42;
    u32 field_44;
};

/** Partial resident callback state used by status transitions. */
struct StatusRuntimeCallbacks
{
    u8 unk00[0x14];
    StatusResourceState* unk14;
    u8 unk18[0x48];
    u8 unk60;
};

typedef struct OverlayNode
{
    void* value;
    struct OverlayNode* next;
    /** @brief Release the link without destroying its payload. */
    ~OverlayNode()
    {
    }
} OverlayNode;

struct OverlayList
{
    OverlayNode* head;
    s32 count;
    void* methods;
};

extern StatusRuntime* D_001B643C;
extern "C" s32 func_002CFE40(void* object, s16 index);

extern u8 D_1889C0[];
extern u8 D_188CC0[];
extern u8 D_1888B0[];
extern u8 D_1888C0[];
extern u8 D_175110[];

extern "C" void func_2642D0(void* object);
extern "C" void func_4618F0(void* object, s32 flags);
extern "C" void func_2CEAF0(void* object, s32 flags);
extern "C" void* func_100AC0(s32 size, s32 flags);
extern "C" void func_4C48B0(void* object, s32 flags);
extern "C" void func_28E2B0(void* object, s32 flags);
extern "C" void func_2CEBE0(void* object);
extern "C" void func_00351020(void* list);
extern "C" void func_00350E10(void* list);
extern "C" void func_00350B70(void* list);

static inline void close_status_selection(StatusSelectionWindow* object);
static inline void set_status_record_rectangle(LibObject178750* target, float x, float y, float width, float height);
static inline void set_status_widget_position(LibClass178600* widget, float x, float y);
template <class List>
static inline void move_status_display_list(List* list, StatusScrollState* object);
static inline void set_status_resource_scale(LibClass175110* display, float x, float y);
static inline StatusAlignedResource* aligned_status_resource(void* buffer);
static inline void status_set_position(LibObject178750* target, float x, float y, float z, float w);

/**
 * @brief Set the record caption rectangle and mark it for refresh.
 * @param target Caption widget.
 * @param x Horizontal origin.
 * @param y Vertical origin.
 * @param width Caption width.
 * @param height Caption height.
 */
static inline void set_status_record_rectangle(LibObject178750* target, float x, float y, float width, float height)
{
    target->unk18.unk00 = x;
    target->unk18.unk04 = y;
    target->unk18.unk08 = width;
    target->unk18.unk0c = height;
    target->unk3c = 1;
}

/**
 * @brief Initialize a resource display.
 * @param display Resource display to initialize.
 * @param record Resource record to display.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
static inline void initialize_status_resource(ItemCreationOptionResourceDisplay* display, FieldResourceRecord* record, float x, float y)
{
    func_002D6440(display, record, x, y);
}

/** @brief Set widget coordinates and request refresh. @param widget Display widget. @param x Horizontal coordinate. @param y Vertical coordinate. */
static inline void set_status_widget_position(LibClass178600* widget, float x, float y)
{
    widget->unk18.unk00 = x;
    widget->unk18.unk04 = y;
    widget->unk3c = 1;
}
/** @brief Move each non-null display by the current scroll delta. @param list Display list to move. @param object Window supplying the delta. */
template <class List>
static inline void move_status_display_list(List* list, StatusScrollState* object)
{
    OverlayNode* node = list->head->next;
    while (node != 0)
    {
        LibClass178600* widget = static_cast<LibClass178600*>(node->value);
        if (widget != 0)
        {
            set_status_widget_position(widget, widget->unk18.unk00,
                                       widget->unk18.unk04 + object->delta);
        }
        node = node->next;
    }
}

/** @brief Set resource display scales and request refresh. @param display Resource display. @param x Horizontal scale. @param y Vertical scale. */
static inline void set_status_resource_scale(LibClass175110* display, float x, float y)
{
    display->unk50.unk34 = y;
    display->unk50.unk30 = x;
    display->unk3c = 1;
}

/** @brief Align a resource descriptor to 128 bytes. @param buffer Raw resource buffer. @return Aligned resource descriptor. */
static inline StatusAlignedResource* aligned_status_resource(void* buffer)
{
    return reinterpret_cast<StatusAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}

/**
 * @brief Store the display position and mark it for refresh.
 * @param target Display receiver to update.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Third position component.
 * @param w Fourth position component.
 */
static inline void status_set_position(LibObject178750* target, float x, float y, float z, float w)
{
    target->unk18.unk00 = x;
    target->unk18.unk04 = y;
    target->unk18.unk08 = z;
    target->unk18.unk0c = w;
    target->unk3c = 1;
}

void func_00348400(void* object, u8 value)
{
    ((u8*)object)[0xC] = value;
}

u8 func_00348410(void* object)
{
    return ((u8*)object)[0xC];
}

void func_00348420(void* object, u8 value)
{
    ((u8*)object)[0x8] = value;
}

u8 func_00348430(void* object)
{
    return ((u8*)object)[0x8];
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
    *(u32*)((u8*)object + 4) = value;
}

u32 func_003484B0(void* object)
{
    return *(u32*)((u8*)object + 4);
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
    return ((u8*)object)[0xD];
}

void func_003486C0(void* object, u8 value)
{
    ((u8*)object)[0xD] = value;
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

void func_00348700(StatusSelectionWindow* object)
{
    func_0013A678(object->map290, 0, 90);
    func_0013A678(object->map2ea, 0, 90);
    func_0013A678(object->map344, 0, 80);
    StatusGlyphMap90 first = D_00351380;
    for (s32 i = 0; i < 90; ++i)
    {
        object->map290[i] = first.values[i];
    }
    StatusGlyphMap90 second = D_003513E0;
    for (s32 i = 0; i < 90; ++i)
    {
        object->map2ea[i] = second.values[i];
    }
    StatusGlyphMap80 third = D_00351440;
    for (s32 i = 0; i < 80; ++i)
    {
        object->map344[i] = third.values[i];
    }
}

void func_00348960(StatusSelectionWindow* object, s16 code)
{
    if (object->grid_mode == 0)
    {
        if ((code >= 15 && code <= 24) || (code >= 40 && code <= 44) || (code >= 60 && code <= 64))
        {
            object->entries[object->last_entry++] = 0xDE;
        }
        if (code >= 25 && code <= 29)
        {
            object->entries[object->last_entry++] = 0xDF;
        }
    }
    else if (object->grid_mode == 1)
    {
        if ((code >= 15 && code <= 24) || (code >= 40 && code <= 44) || (code >= 60 && code <= 64))
        {
            ++object->last_entry;
            object->entries[object->last_entry] = 0xDE;
        }
        if (code >= 25 && code <= 29)
        {
            ++object->last_entry;
            object->entries[object->last_entry] = 0xDF;
        }
        if (code == 75)
        {
            ++object->last_entry;
            object->entries[object->last_entry] = 0xDE;
        }
    }
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00348AE0);

void func_00348C10(StatusSelectionWindow* object)
{
    object->selected = func_004679B0(object->text);
    for (s32 i = object->first_marker; i < object->first_marker + 7; ++i)
    {
        StatusDisplayNode* node = static_cast<StatusDisplayNode*>(func_00351230(&object->unk2c, i));
        LibClass178600* marker = node->value;
        marker->unk3f = 0;
        if (i == object->first_marker + object->selected)
        {
            marker->unk3f = 1;
        }
    }
    if (object->selected >= 6)
    {
        StatusDisplayNode* node = static_cast<StatusDisplayNode*>(func_00351230(&object->unk2c, object->first_marker + 6));
        node->value->unk3f = 1;
    }
    if (object->selected <= 0)
    {
        StatusDisplayNode* node = static_cast<StatusDisplayNode*>(func_00351230(&object->unk2c, object->first_marker));
        node->value->unk3f = 1;
    }
}

void func_00348D00(StatusSelectionWindow* object)
{
    s32 empty = object->entries[0] == 0;
    if (empty == 0)
    {
        LibObject175140* text = object->text;
        text->unkfc = reinterpret_cast<const char*>(object->entries);
        text->unk3c = 1;
        object->text->unk3f = 0;
    }
    func_00348E50(object);
    for (s32 i = 0; i < 7; ++i)
    {
        object->displays[i]->unk3f = 0;
    }
    for (s32 i = 0; i < 7; ++i)
    {
        u16 key = object->glyphs[i];
        if (key != 0)
        {
            u32 source = object->func_slot54();
            func_4C6DF0(object->displays[i], source, key, 0);
            object->displays[i]->unk3f = 1;
        }
        else
        {
            u32 source = object->func_slot54();
            func_4C6DF0(object->displays[i], source, 0x13C8, 0);
            object->displays[i]->unk3f = 1;
        }
    }
}

void func_00348E50(StatusSelectionWindow* object)
{
    for (s32 i = 0; i < 7; ++i)
    {
        object->glyphs[i] = 0;
    }
    u16 position = 0;
    u16 output = 0;
    u8 alternate = 0;
    for (;;)
    {
        if (position >= 24 || output >= 8)
        {
            break;
        }
        u8 value = object->entries[position];
        if (value == 0)
        {
            break;
        }
        if (value == 0x7E)
        {
            alternate = alternate != 1;
            ++position;
            continue;
        }
        if (value == 0xDE)
        {
            u16* destination = object->glyphs + output;
            u16& previous = destination[-1];
            if (previous == 0x15E2)
            {
                previous += 0x49;
            }
            else
            {
                previous += 10;
            }
        }
        else if (value == 0xDF)
        {
            object->glyphs[output - 1] += 20;
        }
        else if (value == 0x20)
        {
            object->glyphs[output++] = 0x13C8;
        }
        else if (alternate == 1)
        {
            for (s32 i = 0; i < 90; ++i)
            {
                if (value == object->map290[i])
                {
                    object->glyphs[output++] = i + 0x157C;
                    break;
                }
            }
        }
        else
        {
            for (s32 i = 0; i < 90; ++i)
            {
                if (value == object->map2ea[i])
                {
                    object->glyphs[output++] = i + 0x15E0;
                    break;
                }
            }
            for (s32 i = 0; i < 80; ++i)
            {
                if (value == object->map344[i])
                {
                    object->glyphs[output++] = i + 0x170C;
                    break;
                }
            }
        }
        ++position;
    }
}

void func_00349070(StatusSelectionWindow* object, u8 mode)
{
    if (object->last_entry < 24)
    {
        u8 full = func_004679B0(object->text) >= 7;
        if (full == 1)
        {
            return;
        }
        ++object->last_entry;
        s16 code = object->grid_selected % 11 + 10 * (object->grid_selected / 11) - 1;
        if (object->grid_mode == 0)
        {
            if (object->last_entry > 0 && object->entries[object->last_entry - 1] == 0x7E)
            {
                --object->last_entry;
                object->entries[object->last_entry++] = object->map290[code];
                func_00348960(object, code);
                object->entries[object->last_entry] = 0x7E;
            }
            else
            {
                object->entries[object->last_entry++] = 0x7E;
                object->entries[object->last_entry++] = object->map290[code];
                func_00348960(object, code);
                object->entries[object->last_entry] = 0x7E;
            }
        }
        else if (object->grid_mode == 1)
        {
            object->entries[object->last_entry] = object->map2ea[code];
            func_00348960(object, code);
        }
        else
        {
            if (code >= 80)
            {
                object->entries[object->last_entry] = 0x20;
            }
            else
            {
                object->entries[object->last_entry] = object->map344[code];
            }
        }
        func_00348C10(object);
        func_00348D00(object);
    }
}

extern "C" void func_00349260(StatusSelectionWindow* object)
{
    object->grid_mode = 2;
    for (s32 i = 0; i < 12; ++i)
    {
        StatusDisplayNode* node = static_cast<StatusDisplayNode*>(func_00351230(&object->unk2c, i));
        LibClass178600* display = node->value;
        display->unk3f = 0;
        switch (object->grid_mode)
        {
        case 0:
            switch (i)
            {
            case 0:
            case 1:
            case 2:
                display->unk3f = 1;
                break;
            }
            break;
        case 1:
            switch (i)
            {
            case 3:
                display->unk3f = 1;
                break;
            case 4:
            case 5:
                display->unk3f = 0;
                break;
            }
            break;
        case 2:
            switch (i)
            {
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                display->unk3f = 1;
                if (object->unk28c != 0)
                {
                    object->unk28c->unk3f = 1;
                }
                break;
            }
            break;
        }
    }
}

void StatusSelectionWindow::func_slot5c()
{
    FieldClass153E30* receiver = reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14);
    if (receiver->func_00261150() == this)
    {
        if (this->selected < 0)
        {
            this->selected = 0;
        }
        if (this->selected >= 6)
        {
            this->selected = 6;
        }
        LibClass178600* cursor = this->cursor;
        float x = this->x + 36.0f * this->selected;
        float y = this->y;
        cursor->unk18.unk00 = x;
        cursor->unk18.unk04 = y;
        cursor->unk3c = 1;
    }
}

void func_00349440(StatusSelectionWindow* object, s32 value)
{
    LibClass175030* marker = object->grid_marker;
    LibMovementState& movement = *marker;
    if (movement.unk35 != 0)
    {
        if (value < 0)
        {
            value = 98;
        }
        if (value > 98)
        {
            value = 0;
        }
        s32 row = value / 11;
        s32 column = value % 11;
        float x;
        if (column == 0)
        {
            x = object->left - 6.0f;
        }
        else if (column < 6)
        {
            x = (155.0f + 34.0f * column) - 4.0f;
        }
        else
        {
            x = 48.0f + (155.0f + 34.0f * column);
        }
        func_00466E40(&movement, x, 16.0f + (110.0f + 28.0f * row), 1.0f / 15.0f);
        object->grid_selected = value;
        func_002CFE40(D_001B643C->unk10, 0);
    }
}

void StatusSelectionWindow::func_slot74()
{
    s32 value = this->grid_selected;
    s32 quotient = value / 11;
    s32 remainder = value % 11;
    if (remainder == 10)
    {
        func_00349440(this, quotient * 11);
    }
    else
    {
        func_00349440(this, value + 1);
    }
}

void StatusSelectionWindow::func_slot70()
{
    s32 value = this->grid_selected;
    s32 quotient = value / 11;
    s32 remainder = value % 11;
    if (remainder == 0)
    {
        func_00349440(this, quotient * 11 + 10);
    }
    else
    {
        func_00349440(this, value - 1);
    }
}

void StatusSelectionWindow::func_slot6c()
{
    s32 value = this->grid_selected;
    if (value / 11 == 8)
    {
        func_00349440(this, value % 11);
    }
    else
    {
        func_00349440(this, value + 11);
    }
}

void StatusSelectionWindow::func_slot68()
{
    s32 value = this->grid_selected;
    if (value / 11 == 0)
    {
        func_00349440(this, value % 11 + 88);
    }
    else
    {
        func_00349440(this, value - 11);
    }
}

void StatusSelectionWindow::func_slote4()
{
    s8* row = this->rows[this->selection->slots[this->selection->current] - 1];
    for (s32 i = 0; i < 24; ++i)
    {
        this->entries[i] = 0;
    }
    for (s32 i = 0; i < 24; ++i)
    {
        s8 value = row[i];
        if (value == 0)
        {
            break;
        }
        this->entries[i] = value;
    }
    this->last_entry = 0;
    s8 last;
    for (;;)
    {
        last = this->last_entry;
        if (this->entries[last] == 0)
        {
            break;
        }
        this->last_entry = last + 1;
    }
    if (last > 0)
    {
        this->last_entry = last - 1;
    }
    func_00348C10(this);
    func_00348D00(this);
    func_002CFE40(D_001B643C->unk10, 1);
}

void StatusSelectionWindow::func_slote0()
{
    func_00349440(this, 88);
}

s32 StatusSelectionWindow::func_slotc4()
{
    return 0;
}

s32 StatusSelectionWindow::func_slotc0()
{
    return 0;
}

s32 StatusSelectionWindow::func_slotb4()
{
    func_00348AE0(this);
    return 2;
}

/** @brief Restore the scroll window after a selection command. @param object Selection window to detach. */
static inline void close_status_selection(StatusSelectionWindow* object)
{
    StatusResourceState* target = D_001B643C->unk10->unk14;
    target->func_00263F50(object);
    target->field_40 = 0;
    target->scroll->func_slot20(0);
    target->func_00263C70(target->scroll);
    target->field_42 = 1;
    D_001B643C->unk10->unk60 = 0;
}
s32 StatusSelectionWindow::func_slotb0()
{
    u8 result = 0;
    switch (grid_selected)
    {
    case 0:
    case 11:
    case 22:
        return 0;
    case 33:
        result = func_00348AE0(this);
        break;
    case 44:
    {
        s8* row = rows[selection->slots[selection->current] - 1];
        for (s32 i = 0; i < 24; ++i)
        {
            entries[i] = 0;
        }
        for (s32 i = 0; i < 24; ++i)
        {
            s8 value = row[i];
            if (value == 0)
            {
                break;
            }
            entries[i] = value;
        }
        last_entry = 0;
        s8 last;
        for (;;)
        {
            last = last_entry;
            if (entries[last] == 0)
            {
                break;
            }
            last_entry = last + 1;
        }
        if (last > 0)
        {
            last_entry = last - 1;
        }
        func_00348C10(this);
        func_00348D00(this);
        break;
    }
    case 55:
        close_status_selection(this);
        return 2;
    case 66:
    case 77:
        return 0;
    case 88:
    {
        u8 empty = entries[0] == 0;
        if (empty == 1)
        {
            return 3;
        }
        u8 blank = 1;
        for (s32 i = 0; i < 24; ++i)
        {
            u8 value = entries[i];
            if (value != 32 && value != 0 && value != 126)
            {
                blank = 0;
            }
        }
        if (blank == 0)
        {
            s8* destination = reinterpret_cast<s8*>(static_cast<StatusDisplayRecord*>(selection->unk04)[selection->current].data);
            const s8* source = reinterpret_cast<const s8*>(entries);
            do
            {
            } while ((*destination++ = *source++) != 0);
            StatusNameSection* section = static_cast<StatusNameSection*>(func_101440(func_101290(func_10D8E0()), 4));
            func_0013A4C0(section->names[selection->slots[selection->current] - 1], entries, 24);
            close_status_selection(this);
        }
        else
        {
            return 3;
        }
        break;
    }
    default:
        u8 full = func_004679B0(text) >= 7;
        if (full)
        {
            return 3;
        }
        func_00349070(this, grid_mode);
        break;
    }
    return result == 0 ? 1 : 2;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_slotf4__21StatusSelectionWindowFPv);

void* func_0034AC90(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)((u8*)object + 0x38) = D_1888B0;
        func_4618F0(object, -1);
        if ((s16)flags > 0)
        {
            ::operator delete(object);
        }
    }
    return object;
}

ItemCreationClass175110::~ItemCreationClass175110()
{
}

StatusSelectionWindow::StatusSelectionWindow()
{
    selection = 0;
    caption = 0;
    text = 0;
    displays[0] = 0;
    displays[1] = 0;
    displays[2] = 0;
    displays[3] = 0;
    displays[4] = 0;
    displays[5] = 0;
    displays[6] = 0;
    first_marker = 0;
    selected = 0;
    last_entry = 0;
    for (s32 i = 0; i < 24; ++i)
    {
        entries[i] = 0;
    }
    glyphs[0] = 0;
    glyphs[1] = 0;
    glyphs[2] = 0;
    glyphs[3] = 0;
    glyphs[4] = 0;
    glyphs[5] = 0;
    glyphs[6] = 0;
    func_00348700(this);
    cursor = 0;
    x = 0;
    y = 0;
    unk116 = 0;
    left = 0;
    unk11c = 0;
    unk120 = 0;
    unk124 = 0;
    func_0013C948(reinterpret_cast<char*>(rows[0]), D_00351500);
    func_0013C948(reinterpret_cast<char*>(rows[1]), D_00351508);
    func_0013C948(reinterpret_cast<char*>(rows[2]), D_00351510);
    func_0013C948(reinterpret_cast<char*>(rows[3]), D_00351518);
    func_0013C948(reinterpret_cast<char*>(rows[4]), D_00351520);
    func_0013C948(reinterpret_cast<char*>(rows[5]), D_00351528);
    func_0013C948(reinterpret_cast<char*>(rows[6]), D_00351530);
    func_0013C948(reinterpret_cast<char*>(rows[7]), D_00351538);
    func_0013C948(reinterpret_cast<char*>(rows[8]), D_00351540);
    func_0013C948(reinterpret_cast<char*>(rows[9]), D_00351548);
    unk284 = 0;
    unk288 = 0;
    grid_selected = 33;
    grid_mode = 2;
    unk28c = 0;
}

void func_0034AF00(StatusScrollState* object)
{
    if (object->active == 0)
    {
        return;
    }
    if (object->active == 1)
    {
        move_status_display_list(&object->first, object);
        move_status_display_list(&object->second, object);
        move_status_display_list(&object->third, object);
        object->timer += 1.0f;
        if (object->timer >= 4.0f)
        {
            object->active = 0;
        }
        if (object->delta >= 0.0f)
        {
            object->position -= object->extent / 4.0f;
        }
        else
        {
            object->position += object->extent / 4.0f;
        }
        LibClass1725D0* marker = object->scroll_marker;
        marker->unk54 = object->position;
        marker->unk3c = 1;
    }
}

void func_0034B0A0(StatusScrollState* object, u16 mode)
{
    if (object->active == 0 && (mode != 0 || object->mode != 0) && (mode != 1 || object->mode != 1))
    {
        object->mode++;
        if (object->mode >= 2)
        {
            object->mode = 0;
        }
        if (mode == 0)
        {
            object->delta = object->step;
        }
        else if (mode == 1)
        {
            object->delta = -object->step;
        }
        if (object->active == 0)
        {
            object->active = 1;
            object->timer = 0.0f;
        }
        func_002CFE40(D_001B643C->unk10, 0);
    }
}

void StatusScrollState::func_slot6c()
{
    func_0034B0A0(this, 1);
}

void StatusScrollState::func_slot68()
{
    func_0034B0A0(this, 0);
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_0034B1B0);

void StatusScrollState::func_slot64()
{
    LibObject175140* record = this->record;
    record->unkfc = static_cast<StatusDisplayRecord*>(this->selection->unk04)[this->selection->current].data;
    record->unk3c = 1;
    this->selected_slot = this->selection->slots[this->selection->current];
    LibBounds4C69B0* record_bounds = func_00467950(this->record);
    u32 source = this->func_slot54();
    func_4C6DF0(this->caption, source, this->selected_slot + 0x13BB, 0);
    LibBounds4C69B0* caption_bounds = func_004C69B0(this->caption);
    set_status_record_rectangle(this->caption, this->x + record_bounds->unk08,
                                this->y, caption_bounds->unk08, 24.0f);
    this->marker->unk3f = 1;
    this->other_marker->unk3f = 1;
    this->unk10->unkab = 1;
}

/**
 * @brief Update nested-display cancellation and status-window transitions.
 */
void StatusScrollState::func_slot5c()
{
    if (this->unk1d8 != 0 && func_002FD480(this->unk1d4))
    {
        if (this->unk1d4 != 0)
        {
            this->unk1d4->func_001DD7B0();
            this->unk1d4 = 0;
        }
        if (this->unk1d9 != 0)
        {
            func_0034C130(this);
            this->unk1d9 = 0;
        }
        else
        {
            this->display->unk3f = 1;
            func_4C6DF0(this->variant_text, this->func_slot54(), 0x13CC, 0);
        }
        this->unk1d8 = 0;
    }
    FieldClass153E30* receiver = reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14);
    if (receiver->func_00261150() != this)
    {
        if (this->unk1d4 != 0)
        {
            func_002FD940(this->unk1d4);
            this->unk1d8 = 1;
        }
        return;
    }
    func_0034AF00(this);
    if (this->record_active == 1 && this->selection->active == 1)
    {
        func_0034B1B0(this);
        this->record_active = 0;
    }
    if (this->unk1da != 0 && this->unk1d4 == 0)
    {
        this->func_slot1c(1, 0x80);
    }
}

s32 StatusScrollState::func_slotdc()
{
    if (record_active == 1)
    {
        return 0;
    }
    if (selection->count < 2)
    {
        return 0;
    }
    record_active = 1;
    selection->active = 0;
    func_0028E2B0(selection, 1);
    if (unk1d4 != 0)
    {
        func_002FD940(unk1d4);
        unk1d8 = 1;
    }
    return 4;
}

s32 StatusScrollState::func_slotd8()
{
    if (record_active == 1)
    {
        return 0;
    }
    if (selection->count < 2)
    {
        return 0;
    }
    record_active = 1;
    selection->active = 0;
    func_0028E2B0(selection, 0);
    if (unk1d4 != 0)
    {
        func_002FD940(unk1d4);
        unk1d8 = 1;
    }
    return 4;
}

/**
 * @brief Create and attach the nested status display when needed.
 * @param object Status state containing the optional nested display.
 */
void func_0034C130(StatusScrollState* object)
{
    if (object->unk1d4 == 0)
    {
        object->unk1d4 = new (0) FieldClass15BB90;
        FieldRecordSelection* selection = object->selection;
        u16 identifier = selection->slots[selection->current];
        u16 variant = static_cast<StatusVariantRecord*>(selection->unk04)[selection->current].variant;
        if (variant >= 4)
        {
            variant = 3;
        }
        func_002FDC00(object->unk1d4, 0x290 + 4 * (identifier - 1) + (u16)variant);
        object->unk1d4->unk5b = 1;
        func_002FD220(object->unk1d4, D_001B643C->unk1c);
        func_002FD1D0(object->unk1d4);
        if (static_cast<StatusWindowSection*>(func_101440(func_101290(func_10D8E0()), 1))->enabled != 0)
        {
            func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(object->unk1d4), 0.5235988f, 750.0f, 0.0f, 140.0f, 115.0f);
        }
        else
        {
            func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(object->unk1d4), 0.5235988f, 480.0f, 0.0f, 90.0f, 110.0f);
        }
        D_001B6614->func_004D74F0(object->unk1d4, reinterpret_cast<void*>(-1));
    }
}

s32 StatusScrollState::func_slotb8()
{
    if (this->variant_text == 0)
    {
        return 0;
    }
    if (this->unk1d4 != 0)
    {
        func_002FD940(this->unk1d4);
        this->unk1d8 = 1;
        FieldRecordSelection* selection = this->selection;
        s32 next = static_cast<StatusVariantRecord*>(selection->unk04)[selection->current].variant + 1;
        StatusVariantSection* section = static_cast<StatusVariantSection*>(func_101440(func_101290(func_10D8E0()), 1));
        u16 checksum = section->checksum;
        const u8* begin = section->values;
        const u8* end = reinterpret_cast<const u8*>(&section->checksum);
        u8 maximum;
        if (checksum != func_00457470(section->seed, begin, end - begin))
        {
            maximum = 0;
        }
        else
        {
            maximum = section->values[3];
        }
        next %= maximum + 1;
        selection = this->selection;
        static_cast<StatusVariantRecord*>(selection->unk04)[selection->current].variant = next;
        this->unk1d9 = 1;
        return 1;
    }
    func_0034C130(this);
    this->display->unk3f = 0;
    func_4C6DF0(this->variant_text, this->func_slot54(), 0x13CD, 0);
    return 1;
}

s32 StatusScrollState::func_slotb4()
{
    if (D_001B643C->unk0c == 0)
    {
        return 0;
    }
    if (this->unk1d4 != 0)
    {
        func_002FD940(this->unk1d4);
        this->unk1d8 = 1;
    }
    this->unk1da = 1;
    return 2;
}

s32 StatusScrollState::func_slotb0()
{
    this->unk10->unkab = 0;
    StatusResourceState* target = D_001B643C->unk10->unk14;
    if (target != 0)
    {
        target->field_40 = 1;
        target->field_42 = 1;
        D_001B643C->unk10->unk60 = 0;
    }
    if (this->unk1d4 != 0)
    {
        func_002FD940(this->unk1d4);
        this->unk1d8 = 1;
    }
    return 1;
}

void func_0034C500(StatusScrollState* object)
{
    u16 selected = object->selection->slots[object->selection->current];
    for (s32 index = 0; index < 8; index++)
    {
        if (selected == object->resource_slots[index])
        {
            break;
        }
    }
    u16 key;
    if (object->alternate != 0)
    {
        key = selected + 14;
    }
    else if (selected == 1 || selected == 2)
    {
        key = selected + 58;
    }
    else
    {
        key = selected + 14;
    }
    void* allocation = func_002D3D80(D_001B643C->slots, key & 0xFF);
    FieldResourceRecord* record = func_002D3CC0(D_001B643C->slots, 0);
    if (object->display != 0)
    {
        set_status_resource_scale(object->display, 1.3f, 1.3f);
    }
    LibClass175110* display = object->display;
    if (display != 0 && record != 0)
    {
        set_status_widget_position(display, object->resource_x, object->resource_y);
        func_002D5CF0(object->display, allocation, record, static_cast<u8>(key));
    }
}

void func_0034C640(StatusScrollState* object)
{
    s32 kind, value, result_index, remainder;
    s32 first, second, third, fourth, fifth;
    if (object->selection != 0)
    {
        object->option_total = 0;
        FieldRecordSelection* selection = object->selection;
        StatusProtectedEntries* record = &static_cast<StatusProtectedEntries*>(selection->unk04)[selection->current];
        if (record != 0)
        {
            for (s32 index = 0; index < 6; index++)
            {
                object->keys[index] = 0x822;
                s32 entry = status_protected_entry(record, index);
                if (entry > 0)
                {
                    selection = object->selection;
                    func_00408850(&static_cast<StatusProtectedEntries*>(selection->unk04)[selection->current], selection->slots[selection->current], entry - 1,
                                  &kind, &value, &result_index, &remainder);
                    selection = object->selection;
                    func_004095C0(kind, &selection->records[selection->current], &static_cast<StatusProtectedEntries*>(selection->unk04)[selection->current],
                                  &first, &second, &third, &fourth, &fifth, 0, 0, 0);
                    object->option_total += third;
                    object->keys[index] = kind + 0x18FF;
                }
                else
                {
                    object->keys[index] = 0x822;
                }
            }
        }
    }
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_slotf4__17StatusScrollStateFUi);

LibClass178A70::~LibClass178A70()
{
}

void StatusScrollState::func_slot0c()
{
    container->func_003EF740();
    FieldClass15AE70::func_slot0c();
}

/** @brief Release the owned display lists and window base. */
StatusScrollState::~StatusScrollState()
{
}

/** @brief Initialize the record window and its three owned lists. */
StatusScrollState::StatusScrollState()
{
    selection = 0;
    record_active = 0;
    record = 0;
    unk108 = 0;
    unk10c = 0;
    unk110 = 0;
    unk114 = 0;
    unk118 = 0;
    unk11c = 0;
    unk120 = 0;
    unk124 = 0;
    unk128 = 0;
    unk12c = 0;
    unk130 = 0;
    unk134 = 0;
    unk13c = 0;
    unk140 = 0;
    unk144 = 0;
    unk148 = 0;
    unk14c = 0;
    unk150 = 0;
    unk154 = 0;
    unk158 = 0;
    unk15c = 0;
    unk160 = 0;
    unk164 = 0;
    unk168 = 0;
    unk16c = 0;
    unk170 = 0;
    unk174 = 0;
    unk178 = 0;
    unk17c = 0;
    unk180 = 0;
    unk184 = 0;
    unk188 = 0;
    unk18c = 0;
    unk190 = 0;
    unk194 = 0;
    variant_text = 0;
    keys[0] = 0x822;
    keys[1] = 0x822;
    keys[2] = 0x822;
    keys[3] = 0x822;
    keys[4] = 0x822;
    keys[5] = 0x822;
    option_total = 0;
    caption = 0;
    other_marker = 0;
    selected_slot = 0;
    x = 0;
    y = 0;
    resource_slots[0] = 0;
    resource_slots[1] = 0;
    resource_slots[2] = 0;
    resource_slots[3] = 0;
    resource_slots[4] = 0;
    resource_slots[5] = 0;
    resource_slots[6] = 0;
    resource_slots[7] = 0;
    resource_x = 0;
    resource_y = 0;
    display = 0;
    mode = 0;
    active = 0;
    scroll_marker = 0;
    extent = 50.0f;
    position = 0;
    step = 98.0f;
    alternate = 0;
    unk1d4 = 0;
    unk1d8 = 0;
    unk1d9 = 0;
    unk1da = 0;
    first_tail[0] = 0;
    second_tail[0] = 0;
    first_tail[1] = 0;
    second_tail[1] = 0;
    first_tail[2] = 0;
    second_tail[2] = 0;
    first_tail[3] = 0;
    second_tail[3] = 0;
}

/** @brief Hold the caption until its timer expires, then scroll and wrap it. */
void StatusTextWindow::func_slot5c()
{
    StatusTextWindow* object = this;
    LibObject178750* target = object->target;
    float x = target->unk18.unk00;
    float y = target->unk18.unk04;
    float z = target->unk18.unk08;
    float w = target->unk18.unk0c;
    if (object->state == 0)
    {
        status_set_position(target, object->initial_x, y, z, w);
        object->timer++;
        if (!((float)object->timer <= 120.0f))
        {
            object->timer = 0;
            object->state = 1;
        }
        return;
    }
    x -= 108.0f * D_001B6690;
    if (x < object->base_x - (float)object->distance)
    {
        x = 2.0f + (object->base_x + object->width);
    }
    status_set_position(target, x, y, z, w);
}

/**
 * @brief Select caption keys 5002 and 5003 and reset the scroll timer.
 * @param key Requested caption key.
 */
void StatusTextWindow::func_slot60(s32 key)
{
    StatusTextWindow* object = this;
    if (key >= 5002 && key < 5004)
    {
        object->timer = 0;
        object->state = 0;
        func_4C6DF0(object->target, object->func_slot54(), key, 1);
        object->distance = (s32)func_004C69B0(object->target)->unk08 + 6;
    }
}

/**
 * @brief Create the captions, scrolling text, and frame geometry.
 * @param associated Full resource source word.
 * @return One when the text and both frames are present, otherwise zero.
 */
s32 StatusTextWindow::func_slotf4(u32 associated)
{
    StatusTextWindow* object = this;
    object->FieldClass15AE70::func_slot14(associated, 0, 9, 1400, 16.0f, 16.0f, 0.0f);
    LibObject178750* label = new (0) LibObject178750;
    func_004C7FE0(label, static_cast<s32>(associated), 0x1388, 0, 16.0f, 6.0f, 0.0f, 0.0f);
    func_004C6190(object->unk10, label);
    func_00351120(reinterpret_cast<OverlayList*>(&object->unk2c), label);
    LibObject178750* caption = new (0) LibObject178750;
    func_004C7FE0(caption, static_cast<s32>(associated), 0x13C9, 0, 36.0f, 40.0f, 0.0f, 0.0f);
    caption->set_scale(0.65f, 0.65f);
    func_004C6190(object->unk10, caption);
    func_00351120(reinterpret_cast<OverlayList*>(&object->unk2c), caption);
    object->target = new (0) LibObject178750;
    LibClass1746A0* frame = new (0) LibClass1746A0;
    LibClass1746A0* background = new (0) LibClass1746A0;
    if (object->target == 0 || frame == 0 || background == 0)
    {
        return 0;
    }
    object->label_width = func_004C69B0(label)->unk08;
    object->base_x = 18.0f + object->label_width;
    float frame_padding = 32.0f;
    object->width = 640.0f - (16.0f + (object->base_x + frame_padding));
    object->initial_x = 24.0f + object->label_width;
    func_44B570(frame, object->base_x, 0.0f, object->width, 56.0f);
    func_004C6190(object->unk10, frame);
    func_00351270(reinterpret_cast<OverlayList*>(&object->unk20), frame);
    func_004C7FE0(object->target, static_cast<s32>(associated), 0x138A, 0, object->initial_x, 6.0f, 0.0f, 0.0f);
    func_004C6190(object->unk10, object->target);
    func_00351120(reinterpret_cast<OverlayList*>(&object->unk2c), object->target);
    func_44B510(background, 1);
    func_004C6190(object->unk10, background);
    func_00351270(reinterpret_cast<OverlayList*>(&object->unk20), background);
    object->func_slot60(0x138A);
    return 1;
}

/** @brief Destroy the caption window base. */
StatusTextWindow::~StatusTextWindow()
{
}

/**
 * @brief Create and attach the three status resource displays.
 * @param associated Full resource source word.
 * @return One after the displays are initialized.
 */
s32 StatusBackgroundWindow::func_slotf4(u32 associated)
{
    StatusBackgroundWindow* object = this;
    object->FieldClass15AE70::func_slot14(associated, 0, 9, 1200, 16.0f, 16.0f, 0.0f);
    ItemCreationOptionResourceDisplay* first = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* second = new (0) ItemCreationOptionResourceDisplay;
    ItemCreationOptionResourceDisplay* third = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = func_002D3D80(D_001B643C->slots, 11);
    first->unkcc = allocation;
    second->unkcc = allocation;
    third->unkcc = allocation;
    first->unkd0 = 11;
    second->unkd0 = 11;
    third->unkd0 = 11;
    initialize_status_resource(first, func_002D3CC0(D_001B643C->slots, 5), 0.0f, 0.0f);
    initialize_status_resource(second, func_002D3CC0(D_001B643C->slots, 6), 256.0f, 0.0f);
    initialize_status_resource(third, func_002D3CC0(D_001B643C->slots, 7), 512.0f, 0.0f);
    func_004C6190(object->unk10, first);
    func_004C6190(object->unk10, second);
    func_004C6190(object->unk10, third);
    return 1;
}

/** @brief Destroy the background window base. */
StatusBackgroundWindow::~StatusBackgroundWindow()
{
}

void func_00350160(StatusResourceState* object)
{
    if (object->resource != 0)
    {
        func_00465430(D_001B657C, object->resource);
    }
    func_004D65C0(object);
    object->func_001DD7B0();
    FieldBufferSlots* slots = D_001B643C->slots;
    for (s32 index = 15; index <= 22; index++)
    {
        func_002D3DC0(slots, (u8)index);
    }
    func_002D3DC0(slots, 59);
    func_002D3DC0(slots, 60);
}

void func_00350200(void* object)
{
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_00350220);

u32 func_00350530(void* object)
{
    return *(u32*)((u8*)object + 0x24);
}

/**
 * @brief Create and attach the status windows and record selection.
 * @param object Status resource state.
 * @return One after record selection and window setup succeed, or zero otherwise.
 */
s32 func_00350540(StatusResourceState* object)
{
    StatusBackgroundWindow* background = new (0) StatusBackgroundWindow;
    StatusTextWindow* text = new (0) StatusTextWindow;
    object->scroll = new (0) StatusScrollState;
    object->selection = new (0) FieldRecordSelection;
    if ((u8)func_0028E3D0(object->selection) == 0)
    {
        return 0;
    }
    object->unk20 = object->scroll;
    background->func_slotf4(object->resource);
    object->FieldClass153E30::func_00263FD0(background);
    background->func_slot40(0);
    text->func_slotf4(object->resource);
    object->FieldClass153E30::func_00263FD0(text);
    object->unk24 = text;
    text->func_slot40(background);
    object->scroll->func_slotf4(object->resource);
    object->FieldClass153E30::func_00263FD0(object->scroll);
    object->flag_38 = 1;
    return 1;
}

s32 func_00350700(StatusResourceState* object, void* buffer)
{
    if (buffer == 0)
    {
        return 0;
    }
    StatusAlignedResource* aligned = aligned_status_resource(buffer);
    s32 size = aligned->size + 0x80;
    void* saved_heap = func_00100C90();
    void* heap = D_001B6430->context->unk70;
    void* memory = func_00113710(heap, size);
    if (memory != 0)
    {
        func_001134C0(memory);
        func_00100C80(heap);
    }
    object->resource = func_004656B0(D_001B657C, aligned);
    func_00100C80(saved_heap);
    StatusRuntimeResource* runtime = reinterpret_cast<StatusRuntimeResource*>(D_001B657C);
    runtime->resource = object->resource;
    runtime->code = 0xC351;
    return object->func_00263CD0();
}

s32 func_003507E0(void* object)
{
    return 1;
}

INCLUDE_ASM("build/overlays/cstatus/asm/nonmatchings/text", func_003507F0);

StatusObject* func_00350890(StatusObject* object)
{
    func_2642D0(object);
    object->methods = D_188CC0;
    object->field_34 = 0;
    object->flag_38 = 0;
    object->field_3C = 0;
    object->field_44 = 0;
    object->field_40 = 0;
    object->field_42 = 0;
    return object;
}

void func_003509A0(void* object)
{
}

void func_003509B0(void* object)
{
}

StatusSelectionWindow::~StatusSelectionWindow()
{
}

/** @brief Leave the base window unchanged. */
void FieldClass15AE70::func_slot68()
{
}

/** @brief Leave the base window unchanged. */
void FieldClass15AE70::func_slot6c()
{
}

/** @brief Report the default window callback result. @return Zero. */
s32 FieldClass15AE70::func_slotb0()
{
    return 0;
}

/** @brief Report the default window callback result. @return Zero. */
s32 FieldClass15AE70::func_slotb4()
{
    return 0;
}

/** @brief Leave the base window unchanged. */
void FieldClass15AE70::func_slot5c()
{
}

u32 func_00350A70(void* object)
{
    return ((u8*)object)[0x38] & 1;
}

u32 func_00350A80(void* object)
{
    return *(u32*)((u8*)object + 0x34);
}

s32 func_00350A90(void* object)
{
    return 4;
}

u32 func_00350AA0(void* object)
{
    return *(u32*)((u8*)object + 0x3C);
}

void func_00350AB0(void* object, u32 value)
{
    *(u32*)((u8*)object + 0x24) = value;
}

void func_00350AC0(void* object, u8 value)
{
    ((u8*)object)[0x28] = value;
}

s8 func_00350AD0(void* object)
{
    return ((s8*)object)[0x28];
}

s32 func_00350AE0(void* object)
{
    return 0;
}

s32 func_00350AF0(void* object)
{
    return 0;
}

void func_00350B00(void* object)
{
}

void func_00350B10(void* object)
{
}

void func_00350B20(void* object)
{
}

void func_00350B30(void* object)
{
}

s32 func_00350B40(void* object)
{
    return 0;
}

s32 func_00350B50(void* object)
{
    return 0;
}

s32 func_00350B60(void* object)
{
    return 0;
}

/** @brief Allocate the sentinel and initialize the empty list. */
StatusList188D70::StatusList188D70()
{
    head = new (0) OverlayNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

/** @brief Release the list nodes and sentinel storage. */
StatusList188D70::~StatusList188D70()
{
    func_00350D00(reinterpret_cast<OverlayList*>(this));
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00350C70(OverlayList* list, void* value)
{
    OverlayNode* node = (OverlayNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

void func_00350D00(OverlayList* list)
{
    OverlayNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        OverlayNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

void func_00350D80(OverlayList* list, void* value)
{
    OverlayNode* node = (OverlayNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

/** @brief Allocate the sentinel and initialize the empty list. */
StatusList188D60::StatusList188D60()
{
    head = new (0) OverlayNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

/** @brief Release the list nodes and sentinel storage. */
StatusList188D60::~StatusList188D60()
{
    func_00350FA0(reinterpret_cast<OverlayList*>(this));
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00350F10(OverlayList* list, void* value)
{
    OverlayNode* node = (OverlayNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

void func_00350FA0(OverlayList* list)
{
    OverlayNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        OverlayNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

/** @brief Allocate the sentinel and initialize the empty list. */
StatusList188D50::StatusList188D50()
{
    head = new (0) OverlayNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

/** @brief Release the list nodes and sentinel storage. */
StatusList188D50::~StatusList188D50()
{
    func_003511B0(reinterpret_cast<OverlayList*>(this));
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00351120(OverlayList* list, void* value)
{
    OverlayNode* node = (OverlayNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}

void func_003511B0(OverlayList* list)
{
    OverlayNode* node = list->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        OverlayNode* next = node->next;
        delete node;
        node = next;
    }
    list->head->next = 0;
    list->count = 0;
}

void* func_00351230(void* list, s32 count)
{
    OverlayNode* node = (*(OverlayNode**)list)->next;
    s32 i;

    for (i = 0; i < count; i++)
    {
        if (node == 0)
        {
            return 0;
        }
        node = node->next;
    }
    return node;
}

void func_00351270(OverlayList* list, void* value)
{
    OverlayNode* node = (OverlayNode*)func_100AC0(8, 0);
    if (node != 0)
    {
        OverlayNode* tail;
        node->value = value;
        node->next = 0;
        tail = list->head;
        while (tail->next != 0)
        {
            tail = tail->next;
        }
        tail->next = node;
        list->count++;
    }
}
