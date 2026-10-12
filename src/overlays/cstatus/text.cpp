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
#include "overlays/lib/marker_widget_inlines.h"
#include "overlays/lib/list_indicator_inlines.h"
#include "overlays/lib/scalar_indicator_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"
#include "overlays/lib/text_003F90C0.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/item_allocation.h"

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

/** Status resource receiver with its resident vtable at 0x188CC0. */
struct StatusResourceState : public FieldClass153E30
{
    /** @brief Initialize the resource handle, selection, and transition state. */
    StatusResourceState();
    /** @brief Destroy the owned record selection and the Field receiver base. */
    virtual ~StatusResourceState();
    /** @brief Report the status receiver type. @return Four. */
    virtual s32 func_001DF3D0();
    /** @brief Submit this receiver to the resident object queue. */
    virtual void func_001DD7B0();
    /** @brief Switch between record and name windows through a timed transition. */
    virtual void func_001DF360();
    /** @brief Leave the status receiver unchanged. */
    virtual void func_001DD410();
    /** @brief Report the receiver state. @return One. */
    virtual u8 func_00264110();
    /** @brief Set the active window. @param value Window pointer to store. */
    virtual void func_00263C70(void* value);
    /** @brief Get the active window. @return Stored window pointer. */
    virtual void* func_00261150();
    /** @brief Set the text window. @param value Window pointer to store. */
    virtual void func_00263C80(void* value);
    /** @brief Get the text window. @return Stored text window pointer. */
    virtual void* func_00263C90();
    /** @brief Set the receiver byte. @param value Signed byte to store. */
    virtual void func_00263CA0(s8 value);
    /** @brief Get the receiver byte. @return Stored signed byte. */
    virtual s8 func_00263CB0();
    /** @brief Get the loaded resource handle. @return Resource handle. */
    virtual u32 func_00263CC0();
    /** @brief Report whether window setup finished. @return Setup flag. */
    virtual u8 func_00261D20();
    /**
     * @brief Load the completed status resource and finish receiver setup.
     * @param buffer Completed resource buffer, or null.
     * @return Zero without a buffer, otherwise the receiver setup result.
     */
    virtual s32 func_001E1820(void* buffer);
    /**
     * @brief Create and attach the status windows and record selection.
     * @return One after setup succeeds, or zero otherwise.
     */
    virtual s32 func_00263CD0();
    /** @brief Release the status resource, queue this receiver, and clear its allocation slots. */
    virtual void func_slot5c();
    /** @brief Report the default command result. @return Zero. */
    virtual s32 func_slot60();
    /** @brief Report the default command result. @return Zero. */
    virtual s32 func_slot64();
    /** @brief Leave the resource state unchanged. */
    virtual void func_slot68();
    /** @brief Get the record selection. @return Owned record selection. */
    virtual FieldRecordSelection* selected_records();
    s32 resource;
    u8 flag_38 : 1;
    u8 unknown_38 : 7;
    u8 unknown_39[3];
    FieldRecordSelection* selection;
    u16 field_40;
    u16 field_42;
    StatusScrollState* scroll;
};

/** Partial effect with transition value and display mode. */
struct StatusTransitionEffect
{
    u8 unk00[0xC0];
    s32 value;
    u8 unkc4[0x2C];
    u8 mode;
};
/** Partial Field context receiver holding the active transition effect. */
struct StatusTransitionOwner
{
    u8 unk00[0x5A4];
    StatusTransitionEffect* effect;
};
extern "C" void* func_0020F230(ResidentContextObject38* state, u32 index, u32 first, u32 second, s32 mode, u32 third, u32 flags, float duration, float x, float y);
extern "C" s32 func_0022A160(void* object);
extern "C" void func_004DCEA0(void* object, s32 enabled, s32 other);
extern "C" void* D_001B6650;
extern "C" s32 D_001B6694;


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
extern u8 D_1888B0[];
extern u8 D_1888C0[];
extern u8 D_175110[];

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

/** @brief Get the active window. @return Stored window pointer. */
void* StatusResourceState::func_00261150()
{
    return unk20;
}

/** @brief Set the active window. @param value Window pointer to store. */
void StatusResourceState::func_00263C70(void* value)
{
    unk20 = value;
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

s32 status_remove_last_name_entry(StatusSelectionWindow* object)
{
    if (object->last_entry < 0)
    {
        return 3;
    }
    u8 marker = 0;
    while (1)
    {
        u8* entry = &object->entries[object->last_entry];
        if (*entry == 0x7E)
        {
            *entry = 0;
            marker = 1;
            object->last_entry--;
            continue;
        }
        if (*entry == 0xDE)
        {
            *entry = 0;
            object->last_entry--;
            continue;
        }
        if (*entry == 0xDF)
        {
            *entry = 0;
            object->last_entry--;
            continue;
        }
        break;
    }
    object->entries[object->last_entry] = 0;
    object->last_entry--;
    if (marker == 1)
    {
        if (object->entries[object->last_entry] == 0x7E)
        {
            object->entries[object->last_entry] = 0;
            object->last_entry--;
        }
        else
        {
            object->last_entry++;
            object->entries[object->last_entry] = 0x7E;
        }
    }
    func_00348C10(object);
    func_00348D00(object);
    return 2;
}

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
            lib_text_set_resource(object->displays[i], source, key, 0);
            object->displays[i]->unk3f = 1;
        }
        else
        {
            u32 source = object->func_slot54();
            lib_text_set_resource(object->displays[i], source, 0x13C8, 0);
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

extern "C" void func_00349260(StatusSelectionWindow* object, u8 mode)
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
    status_remove_last_name_entry(this);
    return 2;
}

/** @brief Restore the scroll window after a selection command. @param object Selection window to detach. */
static inline void close_status_selection(StatusSelectionWindow* object)
{
    StatusResourceState* target = D_001B643C->unk10->unk14;
    target->remove_child(object);
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
        result = status_remove_last_name_entry(this);
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

static inline void set_label_spacing_x(LibObject178750* label, float value)
{
    label->unk88 = value;
    label->unk3c = 1;
}
static inline void set_label_spacing_y(LibObject178750* label, float value)
{
    label->unk8c = value;
    label->unk3c = 1;
}

s32 StatusSelectionWindow::func_slotf4(void* associated)
{
    selection = D_001B643C->unk10->unk14->selected_records();
    unk116 = selection->slots[selection->current];
    FieldClass15AE70::func_slot10(reinterpret_cast<u32>(associated), 16.0f, 72.0f, 16);
    LibClass178630* panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 110.0f, 608.0f, 268.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    for (s32 index = 0; index < 12; index++)
    {
        LibObject178750* label = new (0) LibObject178750;
        if (label == 0)
        {
            return 0;
        }
        switch (index)
        {
        case 0:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5039, 0, 184.0f, 118.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 10.0f);
            set_label_spacing_y(label, 4.0f);
            break;
        case 1:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5040, 0, 406.0f, 230.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 44.0f);
            set_label_spacing_y(label, 32.0f);
            break;
        case 2:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5041, 0, 542.0f, 314.0f, 0.0f, 0.0f);
            break;
        case 3:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5042, 0, 184.0f, 118.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 10.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case 4:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5043, 0, 406.0f, 230.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 44.0f);
            set_label_spacing_y(label, 32.0f);
            label->unk3f = 0;
            break;
        case 5:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5044, 0, 406.0f, 314.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 112.0f);
            label->unk3f = 0;
            break;
        case 6:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5045, 0, 184.0f, 118.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 22.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case 7:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5046, 0, 406.0f, 118.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 22.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case 8:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5047, 0, 184.0f, 146.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 18.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case 9:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5048, 0, 406.0f, 146.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 18.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case 10:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5049, 0, 184.0f, 230.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 26.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        case 11:
            lib_text_init_resource_rectangle(label, reinterpret_cast<s32>(associated), 5050, 0, 406.0f, 230.0f, 0.0f, 0.0f);
            set_label_spacing_x(label, 26.0f);
            set_label_spacing_y(label, 4.0f);
            label->unk3f = 0;
            break;
        }
        lib_container_attach_widget(unk10, label);
        func_00351120(reinterpret_cast<OverlayList*>(&unk2c), label);
        if (0 <= index && index < 6)
        {
            label->unk3d = 0;
        }
        if (8 <= index && index < 12)
        {
            label->unk3d = 0;
        }
    }
    unk28c = new (0) LibObject178750;
    lib_text_init_resource_rectangle(unk28c, reinterpret_cast<s32>(associated), 5851, 0, 184.0f, 146.0f, 0.0f, 0.0f);
    set_label_spacing_y(unk28c, 4.0f);
    unk28c->unk3f = 0;
    lib_container_attach_widget(unk10, unk28c);
    left = 32.0f;
    row_height = 28.0f;
    glyph_scale = 0.86f;
    glyph_width = 24.0f * glyph_scale;
    for (s32 index = 0; index < 6; index++)
    {
        command_labels[index] = new (0) LibObject178750;
        lib_text_init_resource_rectangle(command_labels[index], reinterpret_cast<s32>(associated), index + 5032, 1,
                                         left, 9.0f + (110.0f + row_height * index), 0.0f, 0.0f);
        LibObject178750* label = command_labels[index];
        label->set_scale(glyph_scale, glyph_scale);
        lib_container_attach_widget(unk10, command_labels[index]);
        func_00351120(reinterpret_cast<OverlayList*>(&unk2c), command_labels[index]);
        if (0 <= index && index < 3)
        {
            command_labels[index]->unk3d = 0;
        }
    }
    command_labels[6] = new (0) LibObject178750;
    lib_text_init_resource_rectangle(command_labels[6], reinterpret_cast<s32>(associated), 5038, 1, left, 334.0f, 0.0f, 0.0f);
    command_labels[6]->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, command_labels[6]);
    func_00351120(reinterpret_cast<OverlayList*>(&unk2c), command_labels[6]);
    panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 608.0f, 110.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    caption = new (0) LibObject178750;
    lib_text_init_resource_rectangle(caption, reinterpret_cast<s32>(associated), selection->slots[selection->current] + 5051, 0,
                                     404.0f, 43.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, caption);
    func_00351120(reinterpret_cast<OverlayList*>(&unk2c), caption);
    for (s32 index = 0; index < 7; index++)
    {
        LibObject178750* marker = new (0) LibObject178750;
        lib_text_init_resource_rectangle(marker, reinterpret_cast<s32>(associated), 5062, 0,
                                         (152.0f + 36.0f * index) - 2.0f, 57.0f, 0.0f, 0.0f);
        if (first_marker == 0)
        {
            first_marker = unk2c.unk04;
        }
        lib_container_attach_widget(unk10, marker);
        func_00351120(reinterpret_cast<OverlayList*>(&unk2c), marker);
        marker->set_color(0x288080);
        marker->set_scale(1.2f, 1.2f);
        marker->unk80 = 3.6f;
        marker->unk3c = 1;
    }
    for (s32 index = 0; index < 7; index++)
    {
        LibObject178750* marker = new (0) LibObject178750;
        lib_text_init_resource_rectangle(marker, reinterpret_cast<s32>(associated), 5063, 0, 152.0f + 36.0f * index, 59.0f, 0.0f, 0.0f);
        marker->unk80 = 1.8f;
        marker->unk3c = 1;
        lib_container_attach_widget(unk10, marker);
        func_00351120(reinterpret_cast<OverlayList*>(&unk2c), marker);
        marker->set_color(0x505050);
    }
    x = 152.0f;
    y = 43.0f;
    for (s32 index = 0; index < 7; index++)
    {
        displays[index] = new (0) LibObject178750;
        lib_text_init_resource_rectangle(displays[index], reinterpret_cast<s32>(associated), 5064, 0, x + 36.0f * index, y, 0.0f, 0.0f);
        lib_container_attach_widget(unk10, displays[index]);
        func_00351120(reinterpret_cast<OverlayList*>(&unk2c), displays[index]);
        displays[index]->unk3f = 0;
    }
    text = new (0) LibObject175140;
    const char* name = static_cast<StatusDisplayRecord*>(selection->unk04)[selection->current].data;
    text->func_00467AD0(x, y, 0.0f, 0.0f, name, 0);
    lib_container_attach_widget(unk10, text);
    func_00350D80(reinterpret_cast<OverlayList*>(&unk44), text);
    set_label_spacing_x(reinterpret_cast<LibObject178750*>(text), 8.0f);
    cursor = new (0) ItemCreationClass172600;
    func_0041AD10(static_cast<ItemCreationClass172600*>(cursor), x + 36.0f * selected, y, 24.0f, 24.0f);
    lib_container_attach_widget(unk10, cursor);
    unk288 = selection->slots[selection->current];
    character_display = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = func_002D3D80(D_001B643C->slots, unk288);
    FieldResourceRecord* resource = static_cast<FieldResourceRecord*>(func_002D3EB0(D_001B643C->slots, unk288));
    character_display->unkcc = allocation;
    character_display->unkd0 = unk288;
    character_display->func_002D6440(resource, 40.0f, 15.0f);
    lib_container_attach_widget(unk10, character_display);
    character_display->unk34 = 3;
    grid_marker = new (0) LibClass175030;
    lib_moving_widget_init_position(grid_marker, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, grid_marker);
    grid_marker->func_00466E40(left - 6.0f, 214.0f, 0.1f);
    func_00349260(this, grid_mode);
    lib_text_set_resource(caption, func_slot54(), selection->slots[selection->current] + 5051, 0);
    const s8* saved = reinterpret_cast<const s8*>(static_cast<StatusDisplayRecord*>(selection->unk04)[selection->current].data);
    for (s32 index = 0; index < 24; index++)
    {
        entries[index] = 0;
    }
    for (s32 index = 0; index < 24; index++)
    {
        s8 value = saved[index];
        if (value == 0)
        {
            break;
        }
        entries[index] = value;
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
    func_00348D00(this);
    func_00348C10(this);
    return 1;
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
    row_height = 0;
    glyph_scale = 0;
    glyph_width = 0;
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
    character_display = 0;
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

/** Checksum-protected 0xC4-byte character statistics. */
struct StatusCharacterRecord
{
    s16 character_id;
    /** Selects the clamping rules used by the character stat setters. */
    s16 stat_limit_type;
    s16 encoded_level;
    s16 unk06;
    s32 encoded_flags;
    s32 encoded_experience;
    s32 encoded_base_hp;
    s32 encoded_max_hp;
    s32 encoded_hp;
    s32 encoded_base_mp;
    s32 encoded_max_mp;
    s32 encoded_mp;
    float unk28;
    /** Fury is stored at sixteen times its displayed amount. */
    float scaled_max_fury;
    float scaled_fury;
    s32 encoded_base_attack;
    s32 encoded_effective_attack;
    s32 encoded_attack;
    s32 encoded_base_defense;
    s32 encoded_effective_defense;
    s32 encoded_defense;
    s32 encoded_base_agility;
    s32 encoded_effective_agility;
    s32 encoded_agility;
    s32 encoded_base_hit;
    s32 encoded_effective_hit;
    s32 encoded_hit;
    /** The resident INT helpers validate these values through the HIT checksum. */
    s32 encoded_base_intelligence;
    s32 encoded_effective_intelligence;
    s32 encoded_intelligence;
    s16 encoded_base_knockback_power;
    s16 encoded_effective_knockback_power;
    s16 encoded_knockback_power;
    s16 encoded_base_knockback_resistance;
    s16 encoded_effective_knockback_resistance;
    s16 encoded_knockback_resistance;
    s16 encoded_base_critical_rate;
    s16 encoded_effective_critical_rate;
    s16 encoded_critical_rate;
    s32 level_checksum;
    s32 flags_experience_checksum;
    s32 hp_checksum;
    s32 mp_checksum;
    s32 attack_checksum;
    s32 defense_checksum;
    s32 agility_checksum;
    s32 hit_checksum;
    s32 knockback_power_checksum;
    s32 checksum_salt;
    s32 critical_rate_checksum;
    s32 knockback_resistance_checksum;
    s32 unkb4[3];
    s32 unkc0;

    /** @brief Decode current HP, marking valid flags when the HP checksum fails. @return Current HP, or zero for corruption. */
    u32 get_hp()
    {
        u32 value = encoded_hp;
        if (hp_checksum != ((encoded_base_hp + encoded_max_hp) ^ encoded_hp ^ checksum_salt))
        {
            u32 flags = encoded_flags;
            s32 flag_salt = encoded_experience;
            if (flags_experience_checksum == ((flags + checksum_salt) ^ flag_salt ^ checksum_salt))
            {
                encoded_flags = ((flags ^ 0x7DE3F7E3) | 1) ^ 0x7DE3F7E3;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }
            return 0;
        }
        return value ^ 0x7DE3F7E3;
    }
    /** @brief Decode maximum HP, marking valid flags when the HP checksum fails. @return Maximum HP, or zero for corruption. */
    u32 get_max_hp()
    {
        u32 value = encoded_max_hp;
        if (hp_checksum != ((encoded_base_hp + encoded_max_hp) ^ encoded_hp ^ checksum_salt))
        {
            u32 flags = encoded_flags;
            s32 flag_salt = encoded_experience;
            if (flags_experience_checksum == ((flags + checksum_salt) ^ flag_salt ^ checksum_salt))
            {
                encoded_flags = ((flags ^ 0x7DE3F7E3) | 1) ^ 0x7DE3F7E3;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }
            return 0;
        }
        return value ^ 0x7DE3F7E3;
    }
    /** @brief Decode current MP, marking valid flags when the MP checksum fails. @return Current MP, or zero for corruption. */
    u32 get_mp()
    {
        u32 value = encoded_mp;
        if (mp_checksum != ((encoded_base_mp + encoded_max_mp) ^ encoded_mp ^ checksum_salt))
        {
            u32 flags = encoded_flags;
            s32 flag_salt = encoded_experience;
            if (flags_experience_checksum == ((flags + checksum_salt) ^ flag_salt ^ checksum_salt))
            {
                encoded_flags = ((flags ^ 0x7DE3F7E3) | 1) ^ 0x7DE3F7E3;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }
            return 0;
        }
        return value ^ 0x7DE3F7E3;
    }
    /** @brief Decode maximum MP, marking valid flags when the MP checksum fails. @return Maximum MP, or zero for corruption. */
    u32 get_max_mp()
    {
        u32 value = encoded_max_mp;
        if (mp_checksum != ((encoded_base_mp + encoded_max_mp) ^ encoded_mp ^ checksum_salt))
        {
            u32 flags = encoded_flags;
            s32 flag_salt = encoded_experience;
            if (flags_experience_checksum == ((flags + checksum_salt) ^ flag_salt ^ checksum_salt))
            {
                encoded_flags = ((flags ^ 0x7DE3F7E3) | 1) ^ 0x7DE3F7E3;
                s32 current_key = checksum_salt;
                flags = encoded_flags;
                s32 current_experience = encoded_experience;
                flags_experience_checksum = current_key ^ (current_experience ^ (flags + current_key));
            }
            return 0;
        }
        return value ^ 0x7DE3F7E3;
    }
    /** @brief Decode the protected level. @return Level, or one for an invalid checksum. */
    s32 get_level() const
    {
        if (level_checksum != (checksum_salt ^ (encoded_level ^ (unk06 + checksum_salt))))
        {
            return 1;
        }
        return encoded_level ^ 0x7E93;
    }
    /** @brief Decode the protected experience. @return Experience, or zero for an invalid checksum. */
    s32 get_experience() const
    {
        if (flags_experience_checksum != (checksum_salt ^ (encoded_experience ^ (encoded_flags + checksum_salt))))
        {
            return 0;
        }
        return encoded_experience ^ 0x7DE3F7E3;
    }
    /** @brief Decode the protected attack value. @return Attack, or zero for an invalid checksum. */
    s32 get_attack() const
    {
        if (attack_checksum != (checksum_salt ^ (encoded_attack ^ (encoded_base_attack + encoded_effective_attack))))
        {
            return 0;
        }
        return encoded_attack ^ 0x7DE3F7E3;
    }
    /** @brief Decode the protected defense value. @return Defense, or zero for an invalid checksum. */
    s32 get_defense() const
    {
        if (defense_checksum != (checksum_salt ^ (encoded_defense ^ (encoded_base_defense + encoded_effective_defense))))
        {
            return 0;
        }
        return encoded_defense ^ 0x7DE3F7E3;
    }
    /** @brief Decode the protected agility value. @return Agility, or zero for an invalid checksum. */
    s32 get_agility() const
    {
        if (agility_checksum != (checksum_salt ^ (encoded_agility ^ (encoded_base_agility + encoded_effective_agility))))
        {
            return 0;
        }
        return encoded_agility ^ 0x7DE3F7E3;
    }
    /** @brief Decode the protected HIT value. @return HIT, or zero for an invalid checksum. */
    s32 get_hit() const
    {
        if (hit_checksum != (checksum_salt ^ (encoded_hit ^ (encoded_base_hit + encoded_effective_hit))))
        {
            return 0;
        }
        return encoded_hit ^ 0x7DE3F7E3;
    }
    /** @brief Decode INT after validating the HIT checksum. @return INT, or zero when the HIT checksum is invalid. */
    s32 get_intelligence() const
    {
        if (hit_checksum != (checksum_salt ^ (encoded_hit ^ (encoded_base_hit + encoded_effective_hit))))
        {
            return 0;
        }
        return encoded_intelligence ^ 0x7DE3F7E3;
    }
};

/** Checksum-protected 0x114-byte character equipment and skill data. */
struct StatusCharacterEquipment
{
    s16 encoded_base_luck;
    s16 encoded_effective_luck;
    s16 encoded_luck;
    s16 encoded_base_stamina;
    s16 encoded_effective_stamina;
    s16 encoded_stamina;
    s16 encoded_equipment_slot_count;
    s16 encoded_slot_limit;
    s16 encoded_equipment_ids[4];
    s16 encoded_sp;
    s16 encoded_cp;
    u8 unk1c[4];
    char character_name[24];
    u8 battle_strategy;
    /** Strategy saved when the tactics selection window opens. */
    u8 previous_battle_strategy;
    u8 unk3a;
    u8 encoded_anti_attack_aura_mask;
    u8 encoded_status_skill_levels[5];
    u8 encoded_battle_skill_indices[6];
    u8 encoded_tactical_skill_states[7];
    s16 encoded_symbology_mastery[32];
    s16 encoded_battle_skill_mastery[42];
    /** Damage responses in earth, water, fire, wind order. */
    u8 elemental_damage_responses[4];
    u8 attack_element_mask;
    /** Variant index used with character-specific resource groups. */
    u8 character_resource_variant;
    u32 luck_checksum;
    u32 stamina_checksum;
    u32 equipment_checksum;
    u32 sp_cp_checksum;
    u32 symbology_mastery_checksum;
    u32 battle_skill_mastery_checksum;
    u32 tactical_skill_states_checksum;
    u32 battle_skill_indices_checksum;
    u32 status_skill_levels_checksum;
    u32 checksum_salt;
    u32 unk110;
    /** @brief Decode a protected equipment allocation ID. @param index Signed equipment slot index. @return Allocation ID, or zero for an invalid checksum or index. */
    s16 get_allocation_id(s32 index) const
    {
        if (equipment_checksum != (checksum_salt ^ ((encoded_equipment_ids[1] + encoded_equipment_ids[2]) ^ (encoded_equipment_ids[3] + encoded_equipment_ids[0]))))
        {
            return 0;
        }
        if (index < 0)
        {
            return 0;
        }
        if ((encoded_slot_limit ^ 0x7E93) < index)
        {
            return 0;
        }
        return encoded_equipment_ids[index] ^ 0x7E93;
    }
    /** @brief Decode protected SP. @return SP, or zero for an invalid checksum. */
    s32 get_sp() const
    {
        s32 salt = checksum_salt;
        s16 value = encoded_sp;
        if (sp_cp_checksum != (salt ^ (value ^ (encoded_cp + salt))))
        {
            return 0;
        }
        return value ^ 0x7E93;
    }
    /** @brief Decode protected CP. @return CP, or zero for an invalid checksum. */
    s32 get_cp() const
    {
        s32 salt = checksum_salt;
        s16 value = encoded_cp;
        if (sp_cp_checksum != (salt ^ (encoded_sp ^ (value + salt))))
        {
            return 0;
        }
        return value ^ 0x7E93;
    }
};

/** Opaque 0x508-byte table initialized by the Lib experience-table constructor. */
struct StatusExperienceTable
{
    u8 unknown[0x508];
    /** @brief Initialize the experience table and its encoded table offset. */
    StatusExperienceTable();
};
/** @brief Apply an allocation to character statistics and equipment. */
extern "C" s32 func_003F9890(StatusCharacterRecord*, StatusCharacterEquipment*, ItemCreationAllocationRecord*, s32);
/** @brief Compute the experience remaining for the requested level and optionally return its threshold. */
extern "C" s32 func_004028C0(StatusExperienceTable*, s32, StatusCharacterRecord*, s32*);
extern "C" ItemCreationAllocationRecord* D_001B64F8;
/** @brief Get the current character record. @param selection Current record selection. @return Selected character record. */
static inline StatusCharacterRecord* status_character(FieldRecordSelection* selection)
{
    return &reinterpret_cast<StatusCharacterRecord*>(selection->records)[selection->current];
}
/** @brief Get the signed current record index. @param selection Current record selection. @return Signed record index. */
static inline s8 status_selected_index(FieldRecordSelection* selection)
{
    return selection->current;
}
/** @brief Get the character-record table. @param selection Current record selection. @return Record table. */
static inline FieldRecord* status_record_table(FieldRecordSelection* selection)
{
    return selection->records;
}
/** @brief Get the current character equipment. @param selection Current record selection. @return Selected equipment record. */
static inline StatusCharacterEquipment* status_equipment(FieldRecordSelection* selection)
{
    return &static_cast<StatusCharacterEquipment*>(selection->unk04)[selection->current];
}
/** @brief Update a numeric display and mark it dirty. @param widget Numeric display. @param value Display value. */
static inline void status_set_numeric(void* widget, u32 value)
{
    LibObject174F20* number = static_cast<LibObject174F20*>(widget);
    number->numeric_value = value;
    number->unk3c = 1;
}
/** @brief Find a one-based item allocation. @param index Signed allocation ID. @return Allocation record, or null outside one through three thousand. */
static inline ItemCreationAllocationRecord* status_allocation(s16 index)
{
    ItemCreationAllocationRecord* base = D_001B64F8;
    u8 valid = index >= 1 && index <= 3000;
    if (valid)
    {
        return &base[index - 1];
    }
    return 0;
}
/** @brief Update an equipment display and mark it dirty. @param widget Equipment display. @param item Display item code. @param modification Item modification number. */
static inline void status_set_item(LibObject172410* widget, u16 item, u8 modification)
{
    widget->unkfc = item;
    widget->unkfe = modification;
    widget->unk3c = 1;
}
/**
 * @brief Refresh the selected character's name, statistics, equipment, and status captions.
 * @param object Status record window.
 */
extern "C" void status_refresh_character_display(StatusScrollState* object)
{
    FieldRecordSelection* selection = object->selection;
    s8 current = selection->current;
    func_003F9890(&reinterpret_cast<StatusCharacterRecord*>(selection->records)[current],
                 &static_cast<StatusCharacterEquipment*>(selection->unk04)[current], 0, -1);
    LibObject175140* record = object->record;
    record->unkfc = status_equipment(object->selection)->character_name;
    record->unk3c = 1;
    status_set_numeric(object->unk108, status_character(object->selection)->get_hp());
    status_set_numeric(object->unk10c, status_character(object->selection)->get_max_hp());
    status_set_numeric(object->unk110, status_character(object->selection)->get_mp());
    status_set_numeric(object->unk114, status_character(object->selection)->get_max_mp());
    status_set_numeric(object->unk118, status_character(object->selection)->get_level());
    status_set_numeric(object->unk11c, status_character(object->selection)->get_experience());
    StatusCharacterRecord* character = &reinterpret_cast<StatusCharacterRecord*>(status_record_table(object->selection))[status_selected_index(object->selection)];
    if (character->get_level() < 255)
    {
        s32 total = 0;
        s32 level = character->get_level();
        StatusExperienceTable* experience = new (0) StatusExperienceTable;
        status_set_numeric(object->unk120, func_004028C0(experience, level + 1, character, &total));
        if (experience != 0)
        {
            delete experience;
        }
        static_cast<LibObject174F20*>(object->unk120)->unk3f = 1;
        object->unk138->unk3f = 0;
    }
    else
    {
        static_cast<LibObject174F20*>(object->unk120)->unk3f = 0;
        object->unk138->unk3f = 1;
    }
    status_set_numeric(object->unk124, status_character(object->selection)->get_attack());
    status_set_numeric(object->unk128, status_character(object->selection)->get_defense());
    status_set_numeric(object->unk12c, status_character(object->selection)->get_agility());
    status_set_numeric(object->unk130, status_character(object->selection)->get_hit());
    status_set_numeric(object->unk134, status_character(object->selection)->get_intelligence());
    for (s32 index = 0; index < 4; index++)
    {
        s16 identifier = status_equipment(object->selection)->get_allocation_id(index);
        if (identifier == 0)
        {
            object->first_tail[index]->unk3f = 0;
            object->second_tail[index]->unk3f = 1;
        }
        else
        {
            ItemCreationAllocationRecord* allocation = status_allocation(identifier);
            if (allocation == 0)
            {
                object->first_tail[index]->unk3f = 0;
                object->second_tail[index]->unk3f = 1;
            }
            else
            {
                u16 item = allocation->definition_index();
                u8 modification = allocation->modification_number;
                status_set_item(object->first_tail[index], item + 1, modification);
                object->first_tail[index]->unk3f = 1;
                object->second_tail[index]->unk3f = 0;
            }
        }
    }
    object->selected_slot = object->selection->slots[object->selection->current];
    LibBounds4C69B0* record_bounds = func_00467950(object->record);
    LibBounds4C69B0* caption_bounds = lib_text_measure_bounds(object->caption);
    set_status_record_rectangle(object->caption, object->x + record_bounds->unk08, object->y, caption_bounds->unk08, 24.0f);
    lib_text_set_resource(object->caption, object->func_slot54(), object->selected_slot + 0x13BB, 0);
    func_0034C500(object);
    func_0034C640(object);
    status_set_numeric(object->unk148, status_equipment(object->selection)->get_sp());
    status_set_numeric(object->unk14c, object->option_total);
    status_set_numeric(object->unk154, status_equipment(object->selection)->get_cp());
    u32 source0 = object->func_slot54();
    lib_text_set_resource(object->unk188, source0, object->keys[0], 0);
    u32 source1 = object->func_slot54();
    lib_text_set_resource(object->unk18c, source1, object->keys[1], 0);
    u32 source2 = object->func_slot54();
    lib_text_set_resource(object->unk190, source2, object->keys[2], 0);
    u32 source3 = object->func_slot54();
    lib_text_set_resource(object->unk194, source3, object->keys[3], 0);
    u32 source4 = object->func_slot54();
    lib_text_set_resource(object->unk17c, source4, object->keys[4], 0);
    u32 source5 = object->func_slot54();
    lib_text_set_resource(object->unk184, source5, object->keys[5], 0);
}

void StatusScrollState::func_slot64()
{
    LibObject175140* record = this->record;
    record->unkfc = static_cast<StatusDisplayRecord*>(this->selection->unk04)[this->selection->current].data;
    record->unk3c = 1;
    this->selected_slot = this->selection->slots[this->selection->current];
    LibBounds4C69B0* record_bounds = func_00467950(this->record);
    u32 source = this->func_slot54();
    lib_text_set_resource(this->caption, source, this->selected_slot + 0x13BB, 0);
    LibBounds4C69B0* caption_bounds = lib_text_measure_bounds(this->caption);
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
            lib_text_set_resource(this->variant_text, this->func_slot54(), 0x13CC, 0);
        }
        this->unk1d8 = 0;
    }
    FieldClass153E30* receiver = reinterpret_cast<FieldClass153E30*>(D_001B643C->unk10->unk14);
    if (receiver->func_00261150() != this)
    {
        if (this->unk1d4 != 0)
        {
            field_cancel_model_request(this->unk1d4);
            this->unk1d8 = 1;
        }
        return;
    }
    func_0034AF00(this);
    if (this->record_active == 1 && this->selection->active == 1)
    {
        status_refresh_character_display(this);
        this->record_active = 0;
    }
    if (this->unk1da != 0 && this->unk1d4 == 0)
    {
        this->set_state(1, 0x80);
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
        field_cancel_model_request(unk1d4);
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
        field_cancel_model_request(unk1d4);
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
        field_request_model_resource(object->unk1d4, 0x290 + 4 * (identifier - 1) + (u16)variant);
        object->unk1d4->unk5b = 1;
        field_replace_model_camera(object->unk1d4, D_001B643C->unk1c);
        field_attach_model_display(object->unk1d4);
        if (static_cast<StatusWindowSection*>(func_101440(func_101290(func_10D8E0()), 1))->enabled != 0)
        {
            func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(object->unk1d4), 0.5235988f, 750.0f, 0.0f, 140.0f, 115.0f);
        }
        else
        {
            func_002FD1B0(reinterpret_cast<FieldFloatState5C*>(object->unk1d4), 0.5235988f, 480.0f, 0.0f, 90.0f, 110.0f);
        }
        D_001B6614->func_004D74F0(object->unk1d4, -1);
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
        field_cancel_model_request(this->unk1d4);
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
    lib_text_set_resource(this->variant_text, this->func_slot54(), 0x13CD, 0);
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
        field_cancel_model_request(this->unk1d4);
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
        field_cancel_model_request(this->unk1d4);
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

/** @brief Persistent status flags from save section four. */
struct StatusFlagsSection
{
    u8 unknown[0x22];
    u8 flags;
};

/** @brief Set text spacing and mark the widget dirty. @param widget Text widget. @param spacing Character spacing. */
static inline void status_set_spacing(LibClass174EF0* widget, float spacing)
{
    widget->unk88 = spacing;
    widget->unk3c = 1;
}
/** @brief Set a divider color and mark the widget dirty. @param widget Divider widget. @param color Packed color. */
static inline void status_set_marker_color(ItemCreationClass172870* widget, u32 color)
{
    widget->unk50 = color;
    widget->unk3c = 1;
}
/** @brief Set the item display flag and mark the widget dirty. @param widget Item widget. @param flag Display flag. */
static inline void status_set_item_flag(LibObject172410* widget, u8 flag)
{
    widget->unkfa = flag;
    widget->unk3c = 1;
}
/** @brief Find a stat row position. @param origin First row position. @param row Row index. @return Row position. */
static inline float status_row_y(float origin, s32 row)
{
    return origin + 24.0f * static_cast<float>(row);
}
/**
 * @brief Create the selected character's portrait, stat rows, equipment, and scrolling displays.
 * @param associated Full resource source word.
 * @return One on completion, or zero if selection or a stat label is unavailable.
 */
s32 StatusScrollState::func_slotf4(u32 associated)
{
    StatusFlagsSection* flags = static_cast<StatusFlagsSection*>(func_101440(func_101290(func_10D8E0()), 4));
    if (flags != 0)
    {
        alternate = (flags->flags & 0x10) != 0;
    }
    selection = D_001B643C->unk10->unk14->selected_records();
    if (selection == 0)
    {
        return 0;
    }
    selected_slot = selection->slots[selection->current];
    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 14);
    container = new (0) LibObject178660;
    lib_container_init(container, 0, 16.0f, 72.0f, 9, 0.0f, 0x898);
    lib_queue_display_object(D_001B657C, container);
    LibClass178630* panel = new (0) LibClass178630;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 608.0f, 392.0f, 88.0f);
    lib_container_attach_widget(container, panel);
    x = 12.0f;
    y = 12.0f;
    record = new (0) LibObject175140;
    caption = new (0) LibObject178750;
    other_marker = new (0) ItemCreationClass172870;
    record->func_00467AD0(x, y, 0.0f, 0.0f, status_equipment(selection)->character_name, 0);
    lib_container_attach_widget(unk10, record);
    func_00350D80(reinterpret_cast<OverlayList*>(&unk44), record);
    LibBounds4C69B0* bounds = func_00467950(record);
    lib_text_init_resource_rectangle(caption, associated, selected_slot + 0x13BB, 0, x + bounds->unk08, y, 0.0f, 0.0f);
    status_set_spacing(caption, -1.0f);
    lib_container_attach_widget(unk10, caption);
    lib_text_measure_bounds(caption);
    float divider_y = 26.0f + y;
    lib_marker_init_rectangle(other_marker, 12.0f, divider_y, 584.0f, 3.0f);
    status_set_marker_color(other_marker, 0x888888);
    lib_container_attach_widget(unk10, other_marker);
    if (selection->count > 1)
    {
        LibObject178750* hint = new (0) LibObject178750;
        hint->init_resource_rectangle(384.0f, y, 0.0f, 0.0f, associated, 0x13CA, 0);
        lib_container_attach_widget(unk10, hint);
    }
    marker = new (0) LibObject178750;
    lib_text_init_resource_rectangle(marker, associated, 0x13CB, 0, 520.0f, y, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, marker);
    ItemCreationClass1746A0* scissor = new (0) ItemCreationClass1746A0;
    ItemCreationClass1746A0* reset = new (0) ItemCreationClass1746A0;
    lib_scissor_init_rectangle(scissor, 8.0f, 48.0f, 580.0f, 336.0f);
    lib_container_attach_widget(unk10, scissor);
    resource_x = 316.0f;
    resource_y = 52.0f;
    display = new (0) ItemCreationOptionResourceDisplay;
    u16 resource_key;
    if (alternate)
    {
        resource_key = selected_slot + 14;
    }
    else if (selected_slot == 1 || selected_slot == 2)
    {
        resource_key = selected_slot + 58;
    }
    else
    {
        resource_key = selected_slot + 14;
    }
    display->unkcc = func_002D3D80(D_001B643C->slots, resource_key & 0xFF);
    display->unkd0 = resource_key;
    display->func_002D6440(func_002D3CC0(D_001B643C->slots, 0), resource_x, resource_y);
    display->unk34 = 3;
    lib_container_attach_widget(unk10, display);
    StatusVariantSection* variants = static_cast<StatusVariantSection*>(func_101440(func_101290(func_10D8E0()), 1));
    u8* variant_begin = variants->values;
    u8* variant_end = reinterpret_cast<u8*>(&variants->checksum);
    u8 variant;
    if (variants->checksum != func_00457470(variants->seed, variant_begin, variant_end - variant_begin))
    {
        variant = 0;
    }
    else
    {
        variant = variants->values[3];
    }
    if (variant > 0)
    {
        variant_text = new (0) LibObject178750;
        lib_text_init_resource_rectangle(variant_text, associated, 0x13CC, 0, 467.0f, 350.0f, 0.0f, 0.0f);
        lib_container_attach_widget(unk10, variant_text);
    }
    float base_y = resource_y;
    for (s32 index = 0; index < 8; index++)
    {
        u16 identifier = selection->slots[static_cast<s16>(index)];
        if (identifier != 0)
        {
            resource_slots[index] = identifier;
        }
    }
    unk108 = new (0) LibObject174F20;
    unk10c = new (0) LibObject174F20;
    unk110 = new (0) LibObject174F20;
    unk114 = new (0) LibObject174F20;
    unk118 = new (0) LibObject174F20;
    unk11c = new (0) LibObject174F20;
    unk120 = new (0) LibObject174F20;
    unk138 = new (0) LibObject178750;
    unk124 = new (0) LibObject174F20;
    unk128 = new (0) LibObject174F20;
    unk12c = new (0) LibObject174F20;
    unk130 = new (0) LibObject174F20;
    unk134 = new (0) LibObject174F20;
    unk148 = new (0) LibObject174F20;
    unk14c = new (0) LibObject174F20;
    unk154 = new (0) LibObject174F20;
    unk13c = new (0) LibObject178750;
    unk140 = new (0) LibObject178750;
    unk144 = new (0) LibObject178750;
    unk150 = new (0) LibObject178750;
    unk158 = new (0) LibObject178750;
    unk15c = new (0) LibObject178750;
    unk160 = new (0) LibObject178750;
    unk164 = new (0) LibObject178750;
    unk168 = new (0) LibObject178750;
    unk16c = new (0) LibObject178750;
    unk170 = new (0) LibObject178750;
    unk174 = new (0) LibObject178750;
    unk178 = new (0) LibObject178750;
    unk17c = new (0) LibObject178750;
    unk180 = new (0) LibObject178750;
    unk184 = new (0) LibObject178750;
    unk188 = new (0) LibObject178750;
    unk18c = new (0) LibObject178750;
    unk190 = new (0) LibObject178750;
    unk194 = new (0) LibObject178750;
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk108);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk10c);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk110);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk114);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk118);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk11c);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk120);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk124);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk128);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk12c);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk130);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk134);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk148);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk14c);
    func_00350F10(reinterpret_cast<OverlayList*>(&second), unk154);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk13c);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk140);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk144);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk150);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk158);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk15c);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk160);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk164);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk168);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk16c);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk170);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk174);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk178);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk17c);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk180);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk184);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk188);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk18c);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk190);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk194);
    for (s32 index = 0; index <= 4; index++)
    {
        LibObject178750* label = new (0) LibObject178750;
        lib_text_init_resource_rectangle(label, associated, 0x138D + index, 1, 16.0f, base_y + 24.0f * static_cast<float>(index), 0.0f, 0.0f);
        label->set_color(0x806080);
        label->set_scale(0.85f, 0.85f);
        lib_container_attach_widget(unk10, label);
        func_00351120(reinterpret_cast<OverlayList*>(&first), label);
    }
    FieldRecordSelection* selected = selection;
    s8 current = selected->current;
    StatusCharacterRecord* character = &reinterpret_cast<StatusCharacterRecord*>(selected->records)[current];
    func_003F9890(character, &static_cast<StatusCharacterEquipment*>(selected->unk04)[current], 0, -1);
    s32 hp = status_character(selection)->get_hp();
    s32 mp = status_character(selection)->get_mp();
    s32 maximum_hp = status_character(selection)->get_max_hp();
    s32 maximum_mp = status_character(selection)->get_max_mp();
    character = &reinterpret_cast<StatusCharacterRecord*>(status_record_table(selection))[status_selected_index(selection)];
    s32 level = character->get_level();
    s32 experience = character->get_experience();
    unk108->init_numeric_resource_rectangle(58.0f, base_y, 60.0f, 24.0f, hp, 0, 0);
    lib_container_attach_widget(unk10, unk108);
    unk108->set_scale(0.9f, 0.9f);
    float mp_y = 24.0f + base_y;
    unk110->init_numeric_resource_rectangle(58.0f, mp_y, 60.0f, 24.0f, mp, 0, 0);
    lib_container_attach_widget(unk10, unk110);
    unk110->set_scale(0.9f, 0.9f);
    unk10c->init_numeric_resource_rectangle(142.0f, base_y, 60.0f, 24.0f, maximum_hp, 0, 0);
    lib_container_attach_widget(unk10, unk10c);
    unk10c->set_scale(0.9f, 0.9f);
    unk114->init_numeric_resource_rectangle(142.0f, mp_y, 60.0f, 24.0f, maximum_mp, 0, 0);
    lib_container_attach_widget(unk10, unk114);
    unk114->set_scale(0.9f, 0.9f);
    unk118->init_numeric_resource_rectangle(142.0f, 48.0f + base_y, 60.0f, 24.0f, level, 0, 0);
    lib_container_attach_widget(unk10, unk118);
    unk118->set_scale(0.9f, 0.9f);
    unk11c->init_numeric_resource_rectangle(142.0f, 72.0f + base_y, 60.0f, 24.0f, experience, 0, 0);
    lib_container_attach_widget(unk10, unk11c);
    unk11c->set_scale(0.9f, 0.9f);
    character = status_character(selection);
    s32 total = 0;
    level = character->get_level();
    StatusExperienceTable* table = new (0) StatusExperienceTable;
    s32 remaining_experience = func_004028C0(table, level + 1, character, &total);
    float next_y = 96.0f + base_y;
    unk120->init_numeric_resource_rectangle(142.0f, next_y, 60.0f, 24.0f, remaining_experience, 0, 0);
    lib_container_attach_widget(unk10, unk120);
    unk120->set_scale(0.9f, 0.9f);
    if (table != 0)
    {
        delete table;
    }
    lib_text_init_resource_rectangle(unk138, associated, 0x1398, 0, 158.0f, next_y, 0.0f, 0.0f);
    unk138->set_scale(0.9f, 0.9f);
    unk138->set_color(0x508050);
    lib_container_attach_widget(unk10, unk138);
    func_00351120(reinterpret_cast<OverlayList*>(&first), unk138);
    for (s32 index = 0; index < 2; index++)
    {
        LibObject178750* separator = new (0) LibObject178750;
        lib_text_init_resource_rectangle(separator, associated, 0x7E7, 0, 128.0f, base_y + 24.0f * static_cast<float>(index), 0.0f, 0.0f);
        separator->set_color(0x806080);
        separator->set_scale(0.85f, 0.85f);
        lib_container_attach_widget(unk10, separator);
        func_00351120(reinterpret_cast<OverlayList*>(&first), separator);
    }
    for (s32 key = 0x1393; key <= 0x139C; key++)
    {
        LibObject178750* label = new (0) LibObject178750;
        if (label == 0)
        {
            return 0;
        }
        switch (key)
        {
        case 0x1393:
        case 0x1394:
        case 0x1395:
        case 0x1396:
        case 0x1397:
            lib_text_init_resource_rectangle(label, associated, key, 1, 234.0f, base_y + 24.0f * static_cast<float>(key - 0x1393), 0.0f, 0.0f);
            label->set_scale(0.85f, 0.85f);
            break;
        case 0x1399:
        case 0x139A:
        case 0x139B:
        case 0x139C:
            lib_text_init_resource_rectangle(label, associated, key, 1, 16.0f, 2.0f + (180.0f + 48.0f * static_cast<float>(key - 0x1399)), 0.0f, 0.0f);
            label->set_scale(0.75f, 0.75f);
            break;
        }
        label->set_color(0x806080);
        lib_container_attach_widget(unk10, label);
        func_00351120(reinterpret_cast<OverlayList*>(&first), label);
    }
    unk124->init_numeric_resource_rectangle(294.0f, base_y, 48.0f, 24.0f, status_character(selection)->get_attack(), 0, 0);
    lib_container_attach_widget(unk10, unk124);
    unk124->set_scale(0.9f, 0.9f);
    s32 defense = status_character(selection)->get_defense();
    unk128->init_numeric_resource_rectangle(294.0f, status_row_y(base_y, 1), 48.0f, 24.0f, defense, 0, 0);
    lib_container_attach_widget(unk10, unk128);
    unk128->set_scale(0.9f, 0.9f);
    s32 agility = status_character(selection)->get_agility();
    unk12c->init_numeric_resource_rectangle(294.0f, status_row_y(base_y, 2), 48.0f, 24.0f, agility, 0, 0);
    lib_container_attach_widget(unk10, unk12c);
    unk12c->set_scale(0.9f, 0.9f);
    s32 hit = status_character(selection)->get_hit();
    unk130->init_numeric_resource_rectangle(294.0f, status_row_y(base_y, 3), 48.0f, 24.0f, hit, 0, 0);
    lib_container_attach_widget(unk10, unk130);
    unk130->set_scale(0.9f, 0.9f);
    s32 intelligence = status_character(selection)->get_intelligence();
    unk134->init_numeric_resource_rectangle(294.0f, status_row_y(base_y, 4), 48.0f, 24.0f, intelligence, 0, 0);
    lib_container_attach_widget(unk10, unk134);
    unk134->set_scale(0.9f, 0.9f);
    for (s32 index = 0; index < 4; index++)
    {
        first_tail[index] = new (0) LibObject172410;
        second_tail[index] = new (0) LibObject178750;
        func_00350C70(reinterpret_cast<OverlayList*>(&third), first_tail[index]);
        func_00351120(reinterpret_cast<OverlayList*>(&first), second_tail[index]);
    }
    for (s32 index = 0; index < 4; index++)
    {
        float item_y = 204.0f + 48.0f * static_cast<float>(index);
        lib_item_code_init_rectangle(first_tail[index], 32.0f, item_y, 306.000030517578125f, 20.40000152587890625f, 0, 0, 0);
        first_tail[index]->set_scale(0.85f, 0.85f);
        status_set_item_flag(first_tail[index], 1);
        lib_container_attach_widget(unk10, first_tail[index]);
        lib_text_init_resource_rectangle(second_tail[index], associated, 0x822, 0, 32.0f, item_y, 0.0f, 0.0f);
        second_tail[index]->set_scale(0.85f, 0.85f);
        lib_container_attach_widget(unk10, second_tail[index]);
    }
    func_0034C640(this);
    float lower_y = 392.0f + base_y;
    lib_text_init_resource_rectangle(unk13c, associated, 0x139D, 1, 16.0f, lower_y, 0.0f, 0.0f);
    unk13c->set_color(0x806080);
    unk13c->set_scale(0.85f, 0.85f);
    lib_container_attach_widget(unk10, unk13c);
    lib_text_init_resource_rectangle(unk140, associated, 0x139E, 1, 16.0f, lower_y + 24.0f, 0.0f, 0.0f);
    unk140->set_color(0x806080);
    unk140->set_scale(0.85f, 0.85f);
    lib_container_attach_widget(unk10, unk140);
    lib_text_init_resource_rectangle(unk144, associated, 0x139F, 1, 16.0f, lower_y + 48.0f, 0.0f, 0.0f);
    unk144->set_color(0x806080);
    unk144->set_scale(0.85f, 0.85f);
    lib_container_attach_widget(unk10, unk144);
    unk148->init_numeric_resource_rectangle(158.0f, lower_y + 24.0f, 48.0f, 24.0f, 8888, 0, 0);
    unk148->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, unk148);
    unk14c->init_numeric_resource_rectangle(70.0f, lower_y + 48.0f, 48.0f, 24.0f, 8888, 1, 0);
    unk14c->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, unk14c);
    unk150->init_resource_rectangle(130.0f, lower_y + 48.0f, 0.0f, 0.0f, associated, 0x7E7, 1);
    unk150->set_scale(0.85f, 0.85f);
    lib_container_attach_widget(unk10, unk150);
    unk154->init_numeric_resource_rectangle(158.0f, lower_y + 48.0f, 48.0f, 24.0f, status_equipment(selection)->get_cp(), 0, 0);
    unk154->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, unk154);
    lib_text_init_resource_rectangle(unk158, associated, 0x80A, 0, 16.0f, 553.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(unk15c, associated, 0x13A0, 1, 46.0f, 556.0f, 96.0f, 24.0f);
    unk188->init_resource_rectangle(124.0f, 556.0f, 0.0f, 0.0f, associated, keys[0], 0);
    unk158->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, unk158);
    unk15c->set_scale(0.8f, 0.8f);
    unk15c->set_color(0x806080);
    unk15c->set_mode(0);
    unk15c->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, unk15c);
    unk188->set_scale(0.9f, 0.9f);
    status_set_spacing(unk188, -1.0f);
    lib_container_attach_widget(unk10, unk188);
    lib_text_init_resource_rectangle(unk160, associated, 0x80A, 0, 16.0f, 591.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(unk164, associated, 0x13A1, 1, 46.0f, 594.0f, 96.0f, 24.0f);
    unk18c->init_resource_rectangle(124.0f, 594.0f, 0.0f, 0.0f, associated, keys[1], 0);
    unk160->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, unk160);
    unk164->set_scale(0.8f, 0.8f);
    unk164->set_color(0x806080);
    unk164->set_mode(0);
    unk164->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, unk164);
    unk18c->set_scale(0.9f, 0.9f);
    status_set_spacing(unk18c, -1.0f);
    lib_container_attach_widget(unk10, unk18c);
    lib_text_init_resource_rectangle(unk168, associated, 0x80B, 0, 16.0f, 629.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(unk16c, associated, 0x13A0, 1, 46.0f, 632.0f, 96.0f, 24.0f);
    unk190->init_resource_rectangle(124.0f, 632.0f, 0.0f, 0.0f, associated, keys[2], 0);
    unk168->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, unk168);
    unk16c->set_scale(0.8f, 0.8f);
    unk16c->set_color(0x806080);
    unk16c->set_mode(0);
    unk16c->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, unk16c);
    unk190->set_scale(0.9f, 0.9f);
    status_set_spacing(unk190, -1.0f);
    lib_container_attach_widget(unk10, unk190);
    lib_text_init_resource_rectangle(unk170, associated, 0x80B, 0, 16.0f, 667.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(unk174, associated, 0x13A1, 1, 46.0f, 670.0f, 96.0f, 24.0f);
    unk194->init_resource_rectangle(124.0f, 670.0f, 0.0f, 0.0f, associated, keys[3], 0);
    unk170->set_scale(0.8f, 0.8f);
    lib_container_attach_widget(unk10, unk170);
    unk174->set_scale(0.8f, 0.8f);
    unk174->set_color(0x806080);
    unk174->set_mode(0);
    unk174->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, unk174);
    unk194->set_scale(0.9f, 0.9f);
    status_set_spacing(unk194, -1.0f);
    lib_container_attach_widget(unk10, unk194);
    lib_text_init_resource_rectangle(unk178, associated, 0x13A2, 1, 16.0f, 708.0f, 96.0f, 24.0f);
    unk178->set_scale(0.8f, 0.8f);
    unk178->set_color(0x806080);
    unk178->set_mode(0);
    unk178->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, unk178);
    unk17c->init_resource_rectangle(124.0f, 708.0f, 0.0f, 0.0f, associated, keys[4], 0);
    unk17c->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, unk17c);
    lib_text_init_resource_rectangle(unk180, associated, 0x13A3, 1, 16.0f, 746.0f, 96.0f, 24.0f);
    unk180->set_scale(0.8f, 0.8f);
    unk180->set_color(0x806080);
    unk180->set_mode(0);
    unk180->set_vertical_alignment(1);
    lib_container_attach_widget(unk10, unk180);
    unk184->init_resource_rectangle(124.0f, 746.0f, 0.0f, 0.0f, associated, keys[5], 0);
    unk184->set_scale(0.9f, 0.9f);
    lib_container_attach_widget(unk10, unk184);
    lib_scissor_init_reset(reset, 1);
    lib_container_attach_widget(unk10, reset);
    scroll_marker = new (0) ItemCreationClass1725D0;
    lib_list_indicator_init(scroll_marker, 588.0f, 8.0f + divider_y, (392.0f - divider_y) - 16.0f, extent, position);
    lib_container_attach_widget(unk10, scroll_marker);
    status_refresh_character_display(this);
    return 1;
}

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
        lib_text_set_resource(object->target, object->func_slot54(), key, 1);
        object->distance = (s32)lib_text_measure_bounds(object->target)->unk08 + 6;
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
    lib_text_init_resource_rectangle(label, static_cast<s32>(associated), 0x1388, 0, 16.0f, 6.0f, 0.0f, 0.0f);
    lib_container_attach_widget(object->unk10, label);
    func_00351120(reinterpret_cast<OverlayList*>(&object->unk2c), label);
    LibObject178750* caption = new (0) LibObject178750;
    lib_text_init_resource_rectangle(caption, static_cast<s32>(associated), 0x13C9, 0, 36.0f, 40.0f, 0.0f, 0.0f);
    caption->set_scale(0.65f, 0.65f);
    lib_container_attach_widget(object->unk10, caption);
    func_00351120(reinterpret_cast<OverlayList*>(&object->unk2c), caption);
    object->target = new (0) LibObject178750;
    LibClass1746A0* frame = new (0) LibClass1746A0;
    LibClass1746A0* background = new (0) LibClass1746A0;
    if (object->target == 0 || frame == 0 || background == 0)
    {
        return 0;
    }
    object->label_width = lib_text_measure_bounds(label)->unk08;
    object->base_x = 18.0f + object->label_width;
    float frame_padding = 32.0f;
    object->width = 640.0f - (16.0f + (object->base_x + frame_padding));
    object->initial_x = 24.0f + object->label_width;
    lib_scissor_init_rectangle(frame, object->base_x, 0.0f, object->width, 56.0f);
    lib_container_attach_widget(object->unk10, frame);
    func_00351270(reinterpret_cast<OverlayList*>(&object->unk20), frame);
    lib_text_init_resource_rectangle(object->target, static_cast<s32>(associated), 0x138A, 0, object->initial_x, 6.0f, 0.0f, 0.0f);
    lib_container_attach_widget(object->unk10, object->target);
    func_00351120(reinterpret_cast<OverlayList*>(&object->unk2c), object->target);
    lib_scissor_init_reset(background, 1);
    lib_container_attach_widget(object->unk10, background);
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
    lib_container_attach_widget(object->unk10, first);
    lib_container_attach_widget(object->unk10, second);
    lib_container_attach_widget(object->unk10, third);
    return 1;
}

/** @brief Destroy the background window base. */
StatusBackgroundWindow::~StatusBackgroundWindow()
{
}

/** @brief Release the status resource, queue this receiver, and clear its allocation slots. */
void StatusResourceState::func_slot5c()
{
    StatusResourceState* object = this;
    if (object->resource != 0)
    {
        lib_release_resource_slot(D_001B657C, object->resource);
    }
    lib_object_detach_owner(object);
    object->func_001DD7B0();
    FieldBufferSlots* slots = D_001B643C->slots;
    for (s32 index = 15; index <= 22; index++)
    {
        func_002D3DC0(slots, (u8)index);
    }
    func_002D3DC0(slots, 59);
    func_002D3DC0(slots, 60);
}

/** @brief Submit this receiver to the resident object queue. */
void StatusResourceState::func_001DD7B0()
{
    resident_enqueue_object(D_001B65F4, this);
}

/** @brief Switch between record and name windows through a timed transition. */
void StatusResourceState::func_001DF360()
{
    StatusResourceState* object = this;
    switch (object->field_42)
    {
    case 0:
        break;
    case 1:
    {
        func_0020F230(D_001B6430->context->unk38, 0, 0, 0x80000000, 0, 0, 0, 10.0f, 0.0f, 0.0f);
        StatusTransitionEffect* effect;
        (effect = reinterpret_cast<StatusTransitionOwner*>(D_001B6430->context->unk38)->effect)->value = D_001B6694;
        effect->mode = 10;
        object->field_42 = 2;
        break;
    }
    case 2:
    {
        if ((u8)func_0022A160(reinterpret_cast<StatusTransitionOwner*>(D_001B6430->context->unk38)->effect) != 0)
        {
            return;
        }
        func_004DCEA0(D_001B6650, 0, 0);
        switch (object->field_40)
        {
        case 0:
            static_cast<StatusTextWindow*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(5002);
            D_001B643C->unk10->unk14->func_00263C70(object->scroll);
            object->scroll->func_slot64();
            object->scroll->func_slot18(1, 127);
            object->scroll->func_slot20(1);
            break;
        case 1:
        {
            static_cast<StatusTextWindow*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(5003);
            StatusSelectionWindow* window = new (0) StatusSelectionWindow;
            window->func_slotf4((void*)object->resource);
            window->func_slot40(object->scroll);
            object->FieldClass153E30::add_child(window);
            D_001B643C->unk10->unk14->func_00263C70(window);
            break;
        }
        }
        func_0020F230(D_001B6430->context->unk38, 0, 0x80000000, 0, 0, 0, 0, 10.0f, 0.0f, 0.0f);
        StatusTransitionEffect* effect;
        (effect = reinterpret_cast<StatusTransitionOwner*>(D_001B6430->context->unk38)->effect)->value = D_001B6694;
        effect->mode = 10;
        object->field_42 = 3;
        func_004DCEA0(D_001B6650, 1, 0);
        break;
    }
    case 3:
        if ((u8)func_0022A160(reinterpret_cast<StatusTransitionOwner*>(D_001B6430->context->unk38)->effect) == 0)
        {
            object->field_42 = 0;
            D_001B643C->unk10->unk60 = 1;
        }
        break;
    }
}

/** @brief Get the text window. @return Stored text window pointer. */
void* StatusResourceState::func_00263C90()
{
    return unk24;
}

/**
 * @brief Create and attach the status windows and record selection.
 * @return One after setup succeeds, or zero otherwise.
 */
s32 StatusResourceState::func_00263CD0()
{
    StatusResourceState* object = this;
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
    object->FieldClass153E30::add_child(background);
    background->func_slot40(0);
    text->func_slotf4(object->resource);
    object->FieldClass153E30::add_child(text);
    object->unk24 = text;
    text->func_slot40(background);
    object->scroll->func_slotf4(object->resource);
    object->FieldClass153E30::add_child(object->scroll);
    object->flag_38 = 1;
    return 1;
}

/**
 * @brief Load the completed status resource and finish receiver setup.
 * @param buffer Completed resource buffer, or null.
 * @return Zero without a buffer, otherwise the receiver setup result.
 */
s32 StatusResourceState::func_001E1820(void* buffer)
{
    StatusResourceState* object = this;
    if (buffer == 0)
    {
        return 0;
    }
    StatusAlignedResource* aligned = aligned_status_resource(buffer);
    s32 size = aligned->size + 0x80;
    void* saved_heap = resident_get_allocation_heap();
    void* heap = D_001B6430->context->unk70;
    void* memory = resident_heap_allocate(heap, size);
    if (memory != 0)
    {
        resident_heap_release(memory);
        resident_exchange_allocation_heap(heap);
    }
    object->resource = lib_load_resource_slot(D_001B657C, aligned);
    resident_exchange_allocation_heap(saved_heap);
    StatusRuntimeResource* runtime = reinterpret_cast<StatusRuntimeResource*>(D_001B657C);
    runtime->resource = object->resource;
    runtime->code = 0xC351;
    return object->func_00263CD0();
}

/** @brief Report the receiver state. @return One. */
u8 StatusResourceState::func_00264110()
{
    return 1;
}

/**
 * @brief Destroy an owned object and clear its pointer.
 * @param pointer Owned pointer to release and clear.
 */
template <class T>
static inline void status_delete_owned(T*& pointer)
{
    if (pointer != 0)
    {
        delete pointer;
        pointer = 0;
    }
}

/** @brief Destroy the owned record selection and the Field receiver base. */
StatusResourceState::~StatusResourceState()
{
    if (selection != 0)
    {
        status_delete_owned(selection);
    }
}

/** @brief Initialize the resource handle, selection, and transition state. */
StatusResourceState::StatusResourceState()
{
    resource = 0;
    flag_38 = 0;
    selection = 0;
    scroll = 0;
    field_40 = 0;
    field_42 = 0;
}

/** @brief Leave the status receiver unchanged. */
void StatusResourceState::func_001DD410()
{
}

void ItemCreationClass185050::func_slot0c()
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

/** @brief Report whether window setup finished. @return Setup flag. */
u8 StatusResourceState::func_00261D20()
{
    return flag_38;
}

/** @brief Get the loaded resource handle. @return Resource handle. */
u32 StatusResourceState::func_00263CC0()
{
    return resource;
}

/** @brief Report the status receiver type. @return Four. */
s32 StatusResourceState::func_001DF3D0()
{
    return 4;
}

/** @brief Get the record selection. @return Owned record selection. */
FieldRecordSelection* StatusResourceState::selected_records()
{
    return selection;
}

/** @brief Set the text window. @param value Window pointer to store. */
void StatusResourceState::func_00263C80(void* value)
{
    unk24 = value;
}

/** @brief Set the receiver byte. @param value Signed byte to store. */
void StatusResourceState::func_00263CA0(s8 value)
{
    unk28 = value;
}

/** @brief Get the receiver byte. @return Stored signed byte. */
s8 StatusResourceState::func_00263CB0()
{
    return unk28;
}

/** @brief Report the default command result. @return Zero. */
s32 StatusResourceState::func_slot60()
{
    return 0;
}

/** @brief Report the default command result. @return Zero. */
s32 StatusResourceState::func_slot64()
{
    return 0;
}

/** @brief Leave the resource state unchanged. */
void StatusResourceState::func_slot68()
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
