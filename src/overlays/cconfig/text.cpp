#include "include_asm.h"
#include "overlays/cconfig/text.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/1067-00/text_002CD390.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/1067-00/text_0023B1D0.h"
#include "overlays/1067-00/text_002D5260.h"
#include "overlays/1067-00/text_0020E4B0.h"
#include "overlays/1067-00/field_runtime.h"

#include "overlays/lib/text_004BD360.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_004CD3A0.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/list_indicator_inlines.h"
#include "overlays/lib/scalar_indicator_inlines.h"
#include "overlays/lib/resource_widget_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"

/** Partial configuration callback receiver with its resource slot at offset 0x34. */
struct ConfigControlReceiver : public FieldClass153E30
{
    s32 resource;
};

/** Resource descriptor containing its signed allocation size. */
struct ConfigAlignedResource
{
    u8 unk00[0x40];
    s32 size;
};

/** Runtime callback directory exposing the active Field callback receiver. */
struct ConfigRuntimeCallbacks
{
    u8 unk00[0x14];
    FieldClass153E30* unk14;
};
/**
 * @brief Process the supplied window when it is present.
 * @param callbacks Runtime callback directory.
 * @param object Window to process.
 */
extern "C" void func_002CFE10(ConfigRuntimeCallbacks* callbacks, FieldClass15AE70* object);

/** Partial settings storage containing the protected option flags and checksums. */
struct ConfigSettings
{
    u16 bindings[4];
    u8 unk08[0x1C];
    u8 unk24_low : 2;
    u8 unk24 : 2;
    u8 unk24_bit4 : 1;
    u8 unk24_bit5 : 1;
    u8 unk24_bit6 : 1;
    u8 unk24_bit7 : 1;
    u8 unk25_low : 1;
    u8 unk25_bit1 : 1;
    u8 unk25_mode : 2;
    u8 unk25_mid : 2;
    u8 flag : 1;
    u8 high : 1;
    u8 unk26;
    u8 mode;
    u8 enabled;
    u8 unk29[0x7B];
    u16 checksum;
    u16 key;
    u8 unka8[0xE5];
    u8 unk18d;
    u8 unk18e;
    u8 unk18f[0x11];
    u8 extra;
    u8 unk1a1[3];
    u16 extra_checksum;
    u16 extra_key;
};

struct ConfigRuntime
{
    ConfigSettings* settings;
    u8 unk04[0xC];
    ConfigRuntimeCallbacks* unk10;
    u8 unk14[0xC];
    FieldBufferSlots* resources;
};

/** Configuration preview window, its resource widgets, and saved display flag. */
struct ConfigPreviewWindow : public FieldClass15AE70
{
    ItemCreationOptionResourceDisplay* resources[3];
    ItemCreationOptionResourceDisplay* display;
};
struct ConfigPreviewState : public FieldClass153E30
{
    u8 unk34[0xC];
    ConfigPreviewWindow* window;
};
struct ConfigPreviewSection
{
    u8 unk00[0x18C];
    u8 flag;
};

/** Partial configuration text window with its message state and bounds. */
struct ConfigMessageWindow : public FieldClass15AE70
{
    void* source;
    LibObject178750* text;
    s16 unkb0;
    u8 unkb2;
    u8 unkb3;
    u8 unkb4[0x10];
    s32 key;
    float extent;
    u8 active;
};

/** Partial configuration window containing its panel widget. */
struct ConfigFrameWindow : public FieldClass15AE70
{
    LibClass178630* frame;
};

/** Partial configuration selector window with a signed grid selection. */
struct ConfigGridWindow : public FieldClass15AE70
{
    /** @brief Update the row highlights. @param selected Selected row index. */
    virtual void func_slotf4(s16 selected);
    s16 selected;
    u8 unkaa[2];
    FieldObject23CEA0* grid;
};

/** Partial binding selector with its grid, four codes, and associated entries. */
struct ConfigBindingWindow : public FieldClass15AE70
{
    u8 unka8[4];
    FieldObject23CEA0* grid;
    u8 unkb0[2];
    u16 values[4];
    u8 unkba[2];
    LibObject178750* entries[4];
    u8 dirty;
    u8 unkcd[3];
    float spacing;
    float x;
};

/** Partial color selector and its selected component. */
struct ConfigColorSelection
{
    u8 unk00[0xE5];
    u8 unke5;
    u8 unke6[0x2E];
    s16 selected;
};
struct ConfigColorOwner
{
    u8 unk00[0xB4];
    ConfigColorSelection* selection;
};


typedef struct
{
    u8 pad_00[4];
    u32 field_04;
    u8 field_08;
    u8 pad_09;
    u16 field_0a;
    u8 field_0c;
    u8 field_0d;
    u8 pad_0e[2];
    u32 field_10;
    u8 pad_14[0xC];
    u32 field_20;
    u8 pad_24[0x74];
    u32 field_98;
    u32 field_9c;
} ConfigObjectFields;

typedef struct
{
    u8 pad_00[0x24];
    u32 field_24;
} ConfigValue24;

typedef struct
{
    u8 pad_00[0x34];
    u32 field_34;
} ConfigValue34;

typedef struct
{
    u8 pad_00[0x24];
    u32 field_24;
    s8 field_28;
    u8 pad_29[0xF];
    u8 field_38;
} ConfigInputFields;

typedef struct
{
    u8 pad_00[0xAE];
    u8 flag_ae;
    u8 pad_af[0x31];
    float value_e0;
} ConfigDisplay;

typedef struct
{
    u8 pad_00[0xAC];
    ConfigDisplay* display;
} ConfigDisplayOwner;

typedef struct
{
    u8 pad_00[0x3C];
    u8 active;
    u8 pad_3d[0x57];
    u32 color;
} ConfigIcon;

typedef struct ConfigIconNode
{
    ConfigIcon* icon;
    struct ConfigIconNode* next;
} ConfigIconNode;

typedef struct
{
    u8 pad_00[4];
    ConfigIconNode* next;
} ConfigIconList;

typedef struct
{
    u8 pad_00[0x2C];
    ConfigIconList* list;
} ConfigIconOwner;

extern ConfigRuntime* D_001B643C;
extern "C" s32 func_002CFE40(void* object, s16 index);

extern "C" void func_2642D0(void* object);
extern u8 D_182170[];

extern "C" void func_264230(void* object, s32 flags);
extern "C" void func_2CEAF0(void* object, s32 flags);
extern u8 D_181960[];
extern u8 D_181A70[];
extern u8 D_181B70[];
extern u8 D_181C70[];
extern u8 D_181E70[];
extern u8 D_181F70[];
extern u8 D_182070[];

/**
 * @brief Read the extra-row flag when its protected bytes pass the checksum.
 * @param settings Configuration settings.
 * @return Extra-row flag, or zero when the checksum fails.
 */
static inline u8 config_extra(ConfigSettings* settings)
{
    u8* data = &settings->extra;
    if (settings->extra_checksum != func_00457470(settings->extra_key, data,
        reinterpret_cast<u8*>(&settings->extra_checksum) - data))
    {
        return 0;
    }
    return settings->extra;
}
/**
 * @brief Read the mode when its protected bytes pass the checksum.
 * @param settings Configuration settings.
 * @return Mode byte, or zero when the checksum fails.
 */
static inline u8 config_mode(ConfigSettings* settings)
{
    if (settings->checksum != func_00457470(settings->key, &settings->unk26,
        reinterpret_cast<u8*>(&settings->checksum) - &settings->unk26))
    {
        return 0;
    }
    return settings->mode;
}
/**
 * @brief Read the enabled flag when its protected bytes pass the checksum.
 * @param settings Configuration settings.
 * @return Enabled flag, or zero when the checksum fails.
 */
static inline u8 config_enabled(ConfigSettings* settings)
{
    if (settings->checksum != func_00457470(settings->key, &settings->unk26,
        reinterpret_cast<u8*>(&settings->checksum) - &settings->unk26))
    {
        return 0;
    }
    return settings->enabled;
}

/**
 * @brief Read the feature bit as an unsigned byte flag.
 * @param settings Configuration settings.
 * @return Feature bit as zero or one.
 */
static inline u8 config_flag(ConfigSettings* settings)
{
    u32 flag = settings->flag;
    return flag;
}

/**
 * @brief Set the protected mode and regenerate its key and checksum when the stored checksum is valid.
 * @param settings Configuration settings.
 * @param mode New mode byte.
 */
static inline void config_set_mode(ConfigSettings* settings, u8 mode)
{
    s32 length = reinterpret_cast<u8*>(&settings->checksum) - &settings->unk26;
    if (settings->checksum == func_00457470(settings->key, &settings->unk26, length))
    {
        settings->mode = mode;
        settings->key = func_0010CF80();
        settings->checksum = func_00457470(settings->key, &settings->unk26, length);
    }
}

/**
 * @brief Read bit six of settings byte 0x24 as an unsigned byte flag.
 * @param settings Configuration settings.
 * @return Stored bit as zero or one.
 */
static inline u8 config_bit6(ConfigSettings* settings)
{
    u32 flag = settings->unk24_bit6;
    return flag;
}

/**
 * @brief Read the two-bit setting used by option row one.
 * @param settings Configuration settings.
 * @return Stored mode.
 */
static inline u8 config_four_mode(ConfigSettings* settings)
{
    u32 value = settings->unk25_mode;
    return value;
}

/** @brief Initialize a resource widget through its Field resource view. */
static inline void initialize_preview_resource(ItemCreationOptionResourceDisplay* display, FieldResourceRecord* record, float x, float y)
{
    func_002D6440(static_cast<FieldState2D6410*>(static_cast<void*>(display)), record, x, y);
}
/** @brief Set an option icon's packed color and mark it active. */
static inline void set_option_color(ConfigIcon* object, u32 color)
{
    object->color = color;
    object->active = 1;
}

/**
 * @brief Align a resource buffer to its 128-byte payload boundary.
 * @param buffer Resource buffer.
 * @return Aligned resource descriptor.
 */
static inline ConfigAlignedResource* aligned_config_resource(void* buffer)
{
    return reinterpret_cast<ConfigAlignedResource*>((reinterpret_cast<u32>(buffer) + 0x7F) & ~0x7F);
}

/** @brief Set the preview drawing origin and mark its state dirty. */
static inline void set_preview_origin(ItemCreationOptionResourceDisplay* display, float x, float y)
{
    display->unk50.unk20 = x;
    display->unk50.unk24 = y;
    display->unk3c = 1;
}
/**
 * @brief Set the widget rectangle position and mark its state dirty.
 * @param display Widget to update.
 * @param x Horizontal position.
 * @param y Vertical position.
 */
static inline void set_widget_position(LibClass178600* display, float x, float y)
{
    display->unk18.unk00 = x;
    display->unk18.unk04 = y;
    display->unk3c = 1;
}
/** @brief Set the preview drawing scale and mark its state dirty. */
static inline void set_preview_scale(ItemCreationOptionResourceDisplay* display, float x, float y)
{
    display->unk50.unk30 = x;
    display->unk50.unk34 = y;
    display->unk3c = 1;
}

/**
 * @brief Report whether the color selector is inactive.
 * @param selection Color selector whose activity byte is tested.
 * @return One when inactive, or zero when active.
 */
static inline u8 config_selection_inactive(const ConfigColorSelection* selection)
{
    return !selection->unke5;
}


/**
 * @brief Set the resource display level and mark its drawing state dirty.
 * @param display Resource display widget.
 * @param level Drawing level.
 */
static inline void set_resource_level(ItemCreationOptionResourceDisplay* display, float level)
{
    display->unk28 = level;
    display->unk3c = 1;
}


/**
 * @brief Read the two-bit setting used by option row four.
 * @param settings Configuration settings.
 * @return Stored mode.
 */
static inline u8 config_pair_mode(ConfigSettings* settings)
{
    u32 value = settings->unk24;
    return value;
}
/**
 * @brief Resolve the message key for option row four.
 * @param settings Configuration settings.
 * @return Message key for the active choice.
 */
static inline s32 config_pair_key(ConfigSettings* settings)
{
    if (config_pair_mode(settings) == 0)
    {
        return 0x1fae;
    }
    return 0x1faf;
}

void func_00348400(void* object, u8 value)
{
    ((ConfigObjectFields*)object)->field_0c = value;
}

u8 func_00348410(void* object)
{
    return ((ConfigObjectFields*)object)->field_0c;
}

void func_00348420(void* object, u8 value)
{
    ((ConfigObjectFields*)object)->field_08 = value;
}

u8 func_00348430(void* object)
{
    return ((ConfigObjectFields*)object)->field_08;
}

void func_00348440(void* object, u16 value)
{
    ((ConfigObjectFields*)object)->field_0a = value;
}

u16 func_00348450(void* object)
{
    return ((ConfigObjectFields*)object)->field_0a;
}

void func_00348480(void* object, u32 value)
{
    ((ConfigObjectFields*)object)->field_9c = value;
}

u32 func_00348490(void* object)
{
    return ((ConfigObjectFields*)object)->field_9c;
}

void func_003484A0(void* object, u32 value)
{
    ((ConfigObjectFields*)object)->field_04 = value;
}

u32 func_003484B0(void* object)
{
    return ((ConfigObjectFields*)object)->field_04;
}

u32 func_003484C0(void* object)
{
    return ((ConfigObjectFields*)object)->field_10;
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
    return ((ConfigObjectFields*)object)->field_0d;
}

void func_003486C0(void* object, u8 value)
{
    ((ConfigObjectFields*)object)->field_0d = value;
}

void func_003486D0(void* object)
{
}

void func_003486E0(void* object, s16 selected)
{
    s32 index = 0;
    ConfigIconNode* node = ((ConfigIconOwner*)object)->list->next;
    if (node != 0)
    {
        do
        {
            ConfigIcon* icon = node->icon;
            if (index == selected)
            {
                icon->color = 0x288080;
                icon->active = 1;
            }
            else
            {
                icon->color = 0x808080;
                icon->active = 1;
            }
            node = node->next;
            index++;
        } while (node != 0);
    }
}

void func_00348750(ConfigGridWindow* object)
{
    if (D_001B643C->unk10->unk14->func_00261150() == object)
        object->func_slotf4(object->grid->unk114);
}

u32 func_003487B0(void* object)
{
    return ((ConfigObjectFields*)object)->field_20;
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_003487C0);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00348800);

s32 func_00348840(FieldClass15AE70* object)
{
    object->FieldClass15AE70::func_slot18(0, 0x7F);
    FieldClass153E30* state = D_001B643C->unk10->unk14;
    state->func_00263C70(object->func_slot44());
    func_002CFE10(D_001B643C->unk10, object);
    return 2;
}

void func_003488C0(void* object, u32 value)
{
    ((ConfigObjectFields*)object)->field_20 = value;
}

s32 func_003488D0(ConfigGridWindow* object)
{
    u8 handled = 0;
    object->selected = object->grid->unk114;
    if (object->selected == 0)
    {
        object->func_slot1c(0xFF, 0x80);
    }
    else
    {
        handled = object->func_slotb4();
    }
    return handled == 0 ? 1 : 2;
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00348950);

void* func_00348CC0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181960;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            ::operator delete(object);
        }
    }
    return object;
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00348D20);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00348E60);

void func_00348FE0(ConfigColorOwner* object)
{
    if (config_selection_inactive(object->selection) != 1)
    {
        func_00348E60(object, object->selection->selected, 5);
    }
}

void func_00349030(ConfigColorOwner* object)
{
    if (config_selection_inactive(object->selection) != 1)
    {
        func_00348E60(object, object->selection->selected, 1);
    }
}

void func_00349070(ConfigColorOwner* object)
{
    if (config_selection_inactive(object->selection) != 1)
    {
        func_00348E60(object, object->selection->selected, -5);
    }
}

void func_003490C0(ConfigColorOwner* object)
{
    if (config_selection_inactive(object->selection) != 1)
    {
        func_00348E60(object, object->selection->selected, -1);
    }
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00349110);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00349150);

s32 func_00349190(FieldClass15AE70* object)
{
    object->FieldClass15AE70::func_slot18(0, 0x7F);
    FieldClass153E30* state = D_001B643C->unk10->unk14;
    state->func_00263C70(object->func_slot44());
    func_002CFE10(D_001B643C->unk10, object);
    static_cast<FieldClass15AE70*>(object->func_slot44())->func_slot64();
    return 2;
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00349230);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00349320);

void* func_00349790(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181A70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            ::operator delete(object);
        }
    }
    return object;
}

void func_003497F0(void* object)
{
    ConfigDisplay* display = ((ConfigDisplayOwner*)object)->display;
    display->value_e0 = 128.0f;
    display->flag_ae = 1;
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00349810);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00349850);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00349890);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_003498D0);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00349910);

s32 func_00349950(FieldClass15AE70* object)
{
    object->FieldClass15AE70::func_slot18(0, 0x7F);
    FieldClass153E30* state = D_001B643C->unk10->unk14;
    state->func_00263C70(object->func_slot44());
    func_002CFE10(D_001B643C->unk10, object);
    static_cast<FieldClass15AE70*>(object->func_slot44())->func_slot64();
    return 2;
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_003499F0);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00349C70);

void* func_0034A080(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181B70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            ::operator delete(object);
        }
    }
    return object;
}

void func_0034A0E0(ConfigBindingWindow* object)
{
    if (D_001B643C->unk10->unk14->func_00261150() == object)
    {
        u16 mask = D_001B6430->context->input->mask;
        if (mask & 0x2000)
        {
            func_0034A270(object, 0x2000);
        }
        else if (mask & 0x4000)
        {
            func_0034A270(object, 0x4000);
        }
        else if (mask & 0x1000)
        {
            func_0034A270(object, 0x1000);
        }
        else if (mask & 0x8000)
        {
            func_0034A270(object, 0x8000);
        }
        if (object->dirty == 1)
        {
            for (s32 i = 0; i < 4; i++)
            {
                LibObject178750* entry = object->entries[i];
                float y = 16.0f + object->spacing * i;
                entry->unk18.unk00 = object->x;
                entry->unk18.unk04 = y;
                entry->unk3c = 1;
            }
            object->dirty = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_0034A270);

void func_0034A300(ConfigBindingWindow* object)
{
    D_001B643C->unk10->unk14->func_00263F50(object);
    FieldClass153E30* state = D_001B643C->unk10->unk14;
    state->func_00263C70(object->func_slot44());
    static_cast<FieldClass15AE70*>(object->func_slot44())->func_slot64();
    D_001B643C->settings->bindings[0] = object->values[0];
    D_001B643C->settings->bindings[1] = object->values[1];
    D_001B643C->settings->bindings[2] = object->values[2];
    D_001B643C->settings->bindings[3] = object->values[3];
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x1FBC);
    func_002CFE40(D_001B643C->unk10, 2);
}

u32 func_0034A420(void* object)
{
    return ((ConfigValue24*)object)->field_24;
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_0034A430);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_0034A470);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_0034A4B0);

void* func_0034AC80(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181C70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            ::operator delete(object);
        }
    }
    return object;
}

void ConfigOptions::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() == this)
    {
        func_0034AD30(this);
    }
}

void func_0034AD30(ConfigOptions* object)
{
    if (object->unk288 == 0)
    {
        return;
    }
    if (object->unk288 == 1)
    {
        for (ConfigNode* node = object->list0_first.head->next; node != 0; node = node->next)
        {
            LibClass178600* widget = static_cast<LibClass178600*>(node->value);
            if (widget != 0)
            {
                set_widget_position(widget,widget->unk18.unk00,widget->unk18.unk04 + object->unk29c);
            }
        }
        for (ConfigNode* node = object->list0_second.head->next; node != 0; node = node->next)
        {
            LibClass178600* widget = static_cast<LibClass178600*>(node->value);
            if (widget != 0)
            {
                set_widget_position(widget,widget->unk18.unk00,widget->unk18.unk04 + object->unk29c);
            }
        }
        ItemCreationOptionResourceDisplay* display = object->unkf4;
        if (display != 0)
        {
            set_widget_position(display,display->unk18.unk00,display->unk18.unk04 + object->unk29c);
        }
        object->unk298 += 1.0f;
        if (!(object->unk298 < 4.0f))
        {
            object->unk288 = 0;
        }
        if (!(object->unk29c < 0.0f))
        {
            object->unk294 -= object->unk290 / 4.0f;
        }
        else
        {
            object->unk294 += object->unk290 / 4.0f;
        }
        ItemCreationClass1725D0* indicator = object->unk28c;
        indicator->unk54 = object->unk294;
        indicator->unk3c = 1;
    }
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_0034AEC0);

void func_0034B180(ConfigOptions* object, u16 selected)
{
    s32 index;
    for (index = 0; index <= object->last_index; index++)
    {
        ConfigNode* node = func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list), index);
        if (node == 0)
        {
            break;
        }
        ConfigIcon* display = static_cast<ConfigIcon*>(node->value);
        if (display == 0)
        {
            break;
        }
        if (object->unk101 == 0 && index == 12)
        {
            set_option_color(display, 0x505050);
        }
        else if (index == selected)
        {
            set_option_color(display, 0x505080);
        }
        else
        {
            set_option_color(display, 0x806080);
        }
    }
}

void ConfigOptions::func_slota4()
{
    if (!func_slot28())
    {
        if (selected == 11)
        {
            if (unk101 != 0)
            {
                func_0034AEC0(this, 1, 1);
            }
            else
            {
                if (unk100 != 0)
                {
                    func_0034AEC0(this, 1, 2);
                }
                else
                {
                    return;
                }
            }
        }
        else if (selected == 12)
        {
            if (unk100 != 0)
            {
                func_0034AEC0(this, 1, 1);
            }
            else
            {
                return;
            }
        }
        else
        {
            func_0034AEC0(this, 1, 1);
        }
    }
}

void ConfigOptions::func_slota0()
{
    if (!func_slot28())
    {
        if (selected == 13)
        {
            if (unk101 != 0)
            {
                func_0034AEC0(this, 0, 1);
            }
            else
            {
                func_0034AEC0(this, 0, 2);
            }
        }
        else
        {
            func_0034AEC0(this, 0, 1);
        }
    }
}

void ConfigOptions::func_slot6c()
{
    func_slota4();
}

void ConfigOptions::func_slot68()
{
    func_slota0();
}

void func_0034B430(ConfigOptions* object, u16 row)
{
    s32 key = func_00350270(object, row);
    switch (row)
    {
    case 0:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list1_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list1_second), 1)->value);
        if (key == 0x1fa4)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 1:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list2_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list2_second), 1)->value);
        LibClass172600* third = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list2_second), 2)->value);
        LibClass172600* fourth = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list2_second), 3)->value);
        if (key == 0x1fa6)
        {
            first->unk3f = 1;
            second->unk3f = 0;
            third->unk3f = 0;
            fourth->unk3f = 0;
        }
        else if (key == 0x1fa7)
        {
            first->unk3f = 0;
            second->unk3f = 1;
            third->unk3f = 0;
            fourth->unk3f = 0;
        }
        else if (key == 0x1fa8)
        {
            first->unk3f = 0;
            second->unk3f = 0;
            third->unk3f = 1;
            fourth->unk3f = 0;
        }
        else if (key == 0x1fa9)
        {
            first->unk3f = 0;
            second->unk3f = 0;
            third->unk3f = 0;
            fourth->unk3f = 1;
        }
        break;
    }
    case 2:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list3_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list3_second), 1)->value);
        if (key == 0x1faa)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 3:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list4_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list4_second), 1)->value);
        if (key == 0x1fac)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 5:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list6_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list6_second), 1)->value);
        if (key == 0x1fb0)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 6:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list7_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list7_second), 1)->value);
        if (key == 0x1fb2)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 7:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list8_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list8_second), 1)->value);
        if (key == 0x1fb4)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 8:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list9_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list9_second), 1)->value);
        LibClass172600* third = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list9_second), 2)->value);
        LibClass172600* fourth = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list9_second), 3)->value);
        if (key == 0x1fb6)
        {
            first->unk3f = 1;
            second->unk3f = 0;
            third->unk3f = 0;
            fourth->unk3f = 0;
            if (object->unkf4 != 0)
            {
                set_resource_level(object->unkf4, 48.0f);
            }
        }
        else if (key == 0x1fb7)
        {
            first->unk3f = 0;
            second->unk3f = 1;
            third->unk3f = 0;
            fourth->unk3f = 0;
            if (object->unkf4 != 0)
            {
                set_resource_level(object->unkf4, 48.0f);
            }
        }
        else if (key == 0x1fb9)
        {
            first->unk3f = 0;
            second->unk3f = 0;
            third->unk3f = 1;
            fourth->unk3f = 0;
            if (object->unkf4 != 0)
            {
                set_resource_level(object->unkf4, 48.0f);
            }
        }
        else if (key == 0x1fb8)
        {
            first->unk3f = 0;
            second->unk3f = 0;
            third->unk3f = 0;
            fourth->unk3f = 1;
            if (object->unkf4 != 0)
            {
                set_resource_level(object->unkf4, 128.0f);
            }
        }
        break;
    }
    case 9:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list10_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list10_second), 1)->value);
        if (key == 0x1fbb)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 10:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list11_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list11_second), 1)->value);
        if (key == 0x1fbd)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 11:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list12_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list12_second), 1)->value);
        if (key == 0x1fbf)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 12:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list13_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list13_second), 1)->value);
        if (key == 0)
        {
            first->unk3f = 0;
            second->unk3f = 0;
        }
        else if (key == 0x1fc1)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 13:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list14_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list14_second), 1)->value);
        if (key == 0x1fc5)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    case 4:
    {
        LibClass172600* first = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list5_second), 0)->value);
        LibClass172600* second = static_cast<LibClass172600*>(func_003528E0(reinterpret_cast<ConfigListOwner*>(&object->list5_second), 1)->value);
        if (key == 0x1fae)
        {
            first->unk3f = 1;
            second->unk3f = 0;
        }
        else
        {
            first->unk3f = 0;
            second->unk3f = 1;
        }
        break;
    }
    }
}

void func_0034BA10(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list5_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list5_first), 1)->value);
    ConfigSettings* settings = D_001B643C->settings;
    s32 key = config_pair_key(settings);
    bool selected = false;
    if (input == 0x80)
    {
        if (key == 0x1fae)
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
    if (input == 0x20)
    {
        if (key == 0x1faf)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }
    }
    if (selected)
    {
        settings->unk24 = 1;
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
    else
    {
        settings->unk24 = 0;
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
}

void func_0034BB60(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list14_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list14_first), 1)->value);
    s32 key;
    if (config_extra(D_001B643C->settings) == 0)
    {
        key = 0;
    }
    else
    {
        key = config_mode(D_001B643C->settings) == 1 ? 0x1fc5 : 0x1fc6;
    }
    if (key == 0x1fc5)
    {
        config_set_mode(D_001B643C->settings, 0);
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
    else
    {
        config_set_mode(D_001B643C->settings, 1);
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
}

void func_0034BD70(ConfigOptions* object, u16 input)
{
    s32 key;
    ConfigSettings* settings = D_001B643C->settings;
    if (config_flag(settings) == 0 || config_enabled(settings) == 0)
    {
        object->unk101 = 0;
        key = 0;
    }
    else
    {
        object->unk101 = 1;
        key = D_001B643C->settings->unk18d ? 0x1fc1 : 0x1fc2;
    }
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list13_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list13_first), 1)->value);
    if (key == 0)
    {
        first->set_color(0x505050);
        second->set_color(0x505050);
    }
    else
    {
        bool selected = false;
        if (input == 0x80)
        {
            if (key == 0x1fc1)
            {
                selected = true;
            }
            else
            {
                selected = false;
            }
        }
        if (input == 0x20)
        {
            if (key == 0x1fc2)
            {
                selected = false;
            }
            else
            {
                selected = true;
            }
        }
        if (selected)
        {
            D_001B643C->settings->unk18d = 0;
            first->set_color(0x505050);
            second->set_color(0x808080);
        }
        else
        {
            D_001B643C->settings->unk18d = 1;
            first->set_color(0x808080);
            second->set_color(0x505050);
        }
    }
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_0034BF40);

void func_0034C140(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list11_first), 0)->value);
    bool selected;
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list11_first), 1)->value);
    selected = false;
    if (input == 0x80)
    {
        if (object->unkf8 == 0x1fbd)
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
    if (input == 0x20)
    {
        if (object->unkf8 == 0x1fbe)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }
    }
    if (selected)
    {
        object->unkf8 = 0x1fbe;
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
    else
    {
        object->unkf8 = 0x1fbd;
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
}

void func_0034C260(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list10_first), 0)->value);
    bool selected;
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list10_first), 1)->value);
    selected = false;
    if (input == 0x80)
    {
        if (object->unkfc == 0x1fbb)
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
    if (input == 0x20)
    {
        if (object->unkfc == 0x1fbc)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }
    }
    if (selected)
    {
        object->unkfc = 0x1fbc;
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
    else
    {
        object->unkfc = 0x1fbb;
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
}

void func_0034C380(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list9_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list9_first), 1)->value);
    LibObject178750* third = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list9_first), 2)->value);
    LibObject178750* fourth = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list9_first), 3)->value);
    ConfigSettings* settings = D_001B643C->settings;
    s32 key = 0;
    switch (settings->unk18e)
    {
    case 0:
        key = 0x1fb6;
        break;
    case 1:
        key = 0x1fb7;
        break;
    case 2:
        key = 0x1fb8;
        break;
    case 3:
        key = 0x1fb9;
        break;
    }
    s32 selected = -1;
    if (input == 0x80)
    {
        switch (key)
        {
        case 0x1fb6:
            settings->unk18e = 2;
            selected = 3;
            break;
        case 0x1fb7:
            settings->unk18e = 0;
            selected = 0;
            break;
        case 0x1fb9:
            settings->unk18e = 1;
            selected = 1;
            break;
        case 0x1fb8:
            settings->unk18e = 3;
            selected = 2;
            break;
        }
    }
    else
    {
        switch (key)
        {
        case 0x1fb6:
            settings->unk18e = 1;
            selected = 1;
            break;
        case 0x1fb7:
            settings->unk18e = 3;
            selected = 2;
            break;
        case 0x1fb9:
            settings->unk18e = 2;
            selected = 3;
            break;
        case 0x1fb8:
            settings->unk18e = 0;
            selected = 0;
            break;
        }
    }
    first->set_color(0x505050);
    second->set_color(0x505050);
    third->set_color(0x505050);
    fourth->set_color(0x505050);
    switch (selected)
    {
    case 0:
        first->set_color(0x808080);
        break;
    case 1:
        second->set_color(0x808080);
        break;
    case 2:
        third->set_color(0x808080);
        break;
    case 3:
        fourth->set_color(0x808080);
        break;
    }
    func_004587C0(settings);
}

void func_0034C600(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list8_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list8_first), 1)->value);
    ConfigSettings* settings = D_001B643C->settings;
    s32 key = settings->unk24_bit5 ? 0x1fb4 : 0x1fb5;
    bool selected = false;
    if (input == 0x80)
    {
        if (key == 0x1fb4)
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
    if (input == 0x20)
    {
        if (key == 0x1fb5)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }
    }
    if (selected)
    {
        settings->unk24_bit5 = 0;
        func_0011E030(D_001B65F0, 0, 0);
        func_0011E030(D_001B65F0, 1, 0);
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
    else
    {
        settings->unk24_bit5 = 1;
        func_0011E030(D_001B65F0, 0, 1);
        func_0011E030(D_001B65F0, 1, 1);
        func_0020F110(D_001B6430->context->unk38, 1, 128, 10.0f, 5.0f);
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
}

void func_0034C7C0(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list7_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list7_first), 1)->value);
    ConfigSettings* settings = D_001B643C->settings;
    s32 key = settings->unk25_bit1 ? 0x1fb3 : 0x1fb2;
    bool selected = false;
    if (input == 0x80)
    {
        if (key == 0x1fb2)
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
    if (input == 0x20)
    {
        if (key == 0x1fb3)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }
    }
    if (selected)
    {
        settings->unk25_bit1 = 1;
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
    else
    {
        settings->unk25_bit1 = 0;
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
}

void func_0034C900(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list6_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list6_first), 1)->value);
    ConfigSettings* settings = D_001B643C->settings;
    s32 key = settings->unk24_bit4 ? 0x1fb0 : 0x1fb1;
    bool selected = false;
    if (input == 0x80)
    {
        if (key == 0x1fb1)
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
    if (input == 0x20)
    {
        if (key == 0x1fb0)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }
    }
    if (selected)
    {
        settings->unk24_bit4 = 1;
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
    else
    {
        settings->unk24_bit4 = 0;
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
}

void func_0034CA40(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list4_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list4_first), 1)->value);
    ConfigSettings* settings = D_001B643C->settings;
    bool selected;
    s32 key = -1;
    switch (settings->unk24_low)
    {
    case 0:
        key = 0x1fac;
        break;
    case 1:
        key = 0x1fad;
        break;
    }
    selected = false;
    if (input == 0x80)
    {
        if (key == 0x1fad)
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
    if (input == 0x20)
    {
        if (key == 0x1fac)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }
    }
    if (selected)
    {
        settings->unk24_low = 0;
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
    else
    {
        settings->unk24_low = 1;
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
}

void func_0034CBB0(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list3_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list3_first), 1)->value);
    ConfigSettings* settings = D_001B643C->settings;
    s32 key = config_bit6(settings) == 0 ? 0x1faa : 0x1fab;
    bool selected = false;
    if (input == 0x80)
    {
        if (key == 0x1fab)
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
    if (input == 0x20)
    {
        if (key == 0x1faa)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }
    }
    if (selected)
    {
        settings->unk24_bit6 = 0;
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
    else
    {
        settings->unk24_bit6 = 1;
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
}

void func_0034CD00(ConfigOptions* object, u16 input)
{
    ConfigNode* first_node = func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list2_first), 0);
    ConfigNode* second_node = func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list2_first), 1);
    ConfigNode* third_node = func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list2_first), 2);
    ConfigNode* fourth_node = func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list2_first), 3);
    s32 selected;
    s32 key;
    LibObject178750* first = static_cast<LibObject178750*>(first_node->value);
    LibObject178750* second = static_cast<LibObject178750*>(second_node->value);
    LibObject178750* third = static_cast<LibObject178750*>(third_node->value);
    LibObject178750* fourth = static_cast<LibObject178750*>(fourth_node->value);
    ConfigSettings* settings = D_001B643C->settings;
    key = -1;
    switch (config_four_mode(settings))
    {
    case 0:
        key = 0x1fa6;
        break;
    case 2:
        key = 0x1fa7;
        break;
    case 1:
        key = 0x1fa8;
        break;
    case 3:
        key = 0x1fa9;
        break;
    }
    selected = -1;
    switch (input)
    {
    case 0x80:
        switch (key)
        {
        case 0x1fa6:
            settings->unk25_mode = 3;
            selected = 3;
            break;
        case 0x1fa7:
            settings->unk25_mode = 0;
            selected = 0;
            break;
        case 0x1fa8:
            settings->unk25_mode = 2;
            selected = 1;
            break;
        case 0x1fa9:
            settings->unk25_mode = 1;
            selected = 2;
            break;
        }
        break;
    case 0x20:
        switch (key)
        {
        case 0x1fa6:
            settings->unk25_mode = 2;
            selected = 1;
            break;
        case 0x1fa7:
            settings->unk25_mode = 1;
            selected = 2;
            break;
        case 0x1fa8:
            settings->unk25_mode = 3;
            selected = 3;
            break;
        case 0x1fa9:
            settings->unk25_mode = 0;
            selected = 0;
            break;
        }
        break;
    }
    first->set_color(0x505050);
    second->set_color(0x505050);
    third->set_color(0x505050);
    fourth->set_color(0x505050);
    switch (selected)
    {
    case 0:
        first->set_color(0x808080);
        break;
    case 1:
        second->set_color(0x808080);
        break;
    case 2:
        third->set_color(0x808080);
        break;
    case 3:
        fourth->set_color(0x808080);
        break;
    }
}

void func_0034D040(ConfigOptions* object, u16 input)
{
    LibObject178750* first = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list1_first), 0)->value);
    LibObject178750* second = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&object->list1_first), 1)->value);
    ConfigSettings* settings = D_001B643C->settings;
    s32 key = settings->unk24_bit7 ? 0x1fa4 : 0x1fa5;
    bool selected = false;
    if (input == 0x80)
    {
        if (key == 0x1fa5)
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
    if (input == 0x20)
    {
        if (key == 0x1fa4)
        {
            selected = false;
        }
        else
        {
            selected = true;
        }
    }
    if (selected)
    {
        settings->unk24_bit7 = 1;
        first->set_color(0x808080);
        second->set_color(0x505050);
    }
    else
    {
        settings->unk24_bit7 = 0;
        first->set_color(0x505050);
        second->set_color(0x808080);
    }
}

void func_0034D180(ConfigOptions* object, u32 index, u16 bits)
{
    switch (index)
    {
    case 0:
        func_0034D040(object, bits);
        break;
    case 1:
        func_0034CD00(object, bits);
        break;
    case 2:
        func_0034CBB0(object, bits);
        break;
    case 3:
        func_0034CA40(object, bits);
        break;
    case 5:
        func_0034C900(object, bits);
        break;
    case 6:
        func_0034C7C0(object, bits);
        break;
    case 7:
        func_0034C600(object, bits);
        break;
    case 8:
        func_0034C380(object, bits);
        break;
    case 9:
        func_0034C260(object, bits);
        break;
    case 10:
        func_0034C140(object, bits);
        break;
    case 11:
        func_0034BF40(object, bits);
        break;
    case 12:
        func_0034BD70(object, bits);
        break;
    case 13:
        func_0034BB60(object, bits);
        break;
    case 4:
        func_0034BA10(object, bits);
        break;
    }
    func_0034B430(object, index);
    if (object->unkb2 != index)
    {
        object->unkb2 = index;
    }
    s32 key = func_00350270(object, object->selected);
    if (key != object->unkb8)
    {
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(key);
        object->unkb8 = key;
    }
}

void ConfigOptions::func_slotac()
{
    if (!func_slot28() && unk288 == 0)
    {
        s32 selected = this->selected;
        if (selected == 12 && unk101 == 0)
        {
            func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
        }
        else
        {
            func_0034D180(this, static_cast<u8>(selected), 0x20);
            func_002CFE40(D_001B643C->unk10, 0);
        }
    }
}

void ConfigOptions::func_slota8()
{
    if (!func_slot28() && unk288 == 0)
    {
        s32 selected = this->selected;
        if (selected == 12 && unk101 == 0)
        {
            func_00112400(D_001B65F8, 3, 0, 0, 127, 64, 0);
        }
        else
        {
            func_0034D180(this, static_cast<u8>(selected), 0x80);
            func_002CFE40(D_001B643C->unk10, 0);
        }
    }
}

void ConfigOptions::func_slot64()
{
    LibClass175030* widget = scroll;
    widget->unk30 = 128.0f;
    widget->unk3c = 1;
    s32 key = func_00350270(this, selected);
    if (key != unkb8)
    {
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(key);
        unkb8 = key;
    }
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_slotb0__13ConfigOptionsFv);

u32 func_0034D8A0(void* object)
{
    return ((ConfigValue34*)object)->field_34;
}

s32 func_0034D8B0(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[13];
    s32 key = func_00350270(object, 13);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2037, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fc5)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2038, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fc6)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list14_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list14_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034DB50(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[12];
    s32 key = func_00350270(object, 12);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2033, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fc1)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2034, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fc2)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list13_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list13_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034DDF0(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[11];
    s32 key = func_00350270(object, 11);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2031, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fbf)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2032, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fc0)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list12_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list12_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034E090(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[10];
    s32 key = func_00350270(object, 10);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x202f, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fbd)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2030, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fbe)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list11_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list11_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034E330(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[9];
    s32 key = func_00350270(object, 9);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x202d, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fbb)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x202e, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fbc)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list10_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list10_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}


s32 func_0034E5D0(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[8];
    s32 key = func_00350270(object, 8);
    for (s32 i = 0; i < 4; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        text->unk88 = -1.0f;
        text->unk3c = 1;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2029, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1FB6)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x202A, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1FB7)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 2:
        {
            float x = object->unk104;
            object->unka4 += object->unk10c;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x202C, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1FB9)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 3:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x202B, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            object->unkf4 = new (0) ItemCreationOptionResourceDisplay;
            void* allocation = func_002D3D80(D_001B643C->resources, 0);
            FieldResourceRecord* record = func_002D3CC0(D_001B643C->resources, 13);
            object->unkf4->unkcc = allocation;
            object->unkf4->unkd0 = 0;
            initialize_preview_resource(object->unkf4, record, x, object->unka4);
            func_004C6190(object->unk10, object->unkf4);
            if (key == 0x1FB8)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
                set_resource_level(object->unkf4, 128.0f);
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
                set_resource_level(object->unkf4, 48.0f);
            }
            object->unkf4->unk3d = 0;
            text->unk3f = 1;
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list9_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list9_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

ItemCreationClass175110::~ItemCreationClass175110()
{
}

s32 func_0034EB40(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[7];
    s32 key = func_00350270(object, 7);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2027, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fb4)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2028, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fb5)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list8_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list8_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034EDE0(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[6];
    s32 key = func_00350270(object, 6);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2025, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 32.0f);
            if (key == 0x1FB2)
            {
                text->set_color(0x808080);
                text->unk88 = -1.0f;
                text->unk3c = 1;
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = 264.0f + object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2026, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 32.0f);
            if (key == 0x1FB3)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list7_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list7_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034F0A0(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[5];
    s32 key = func_00350270(object, 5);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2023, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fb0)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2024, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fb1)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list6_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list6_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034F340(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[3];
    s32 key = func_00350270(object, 3);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x201f, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fac)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2020, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fad)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list4_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list4_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034F5E0(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[2];
    s32 key = func_00350270(object, 2);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x201d, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1faa)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x201e, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fab)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list3_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list3_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034F880(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[1];
    s32 key = func_00350270(object, 1);
    for (s32 i = 0; i < 4; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2019, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1FA6)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x201A, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1FA7)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 2:
        {
            float x = object->unk104;
            object->unka4 += object->unk10c;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x201B, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1FA8)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 3:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x201C, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1FA9)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list2_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list2_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034FC70(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[0];
    s32 key = func_00350270(object, 0);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2017, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fa4)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2018, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fa5)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list1_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list1_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

s32 func_0034FF10(ConfigOptions* object, void* associated)
{
    if (associated == 0)
    {
        return 0;
    }
    object->unka4 = 0.0f;
    object->unka4 = object->positions[4];
    s32 key = func_00350270(object, 4);
    for (s32 i = 0; i < 2; i++)
    {
        LibObject178750* text = new (0) LibObject178750;
        LibClass172600* marker = new (0) LibClass172600;
        switch (i)
        {
        case 0:
        {
            float x = object->unk104;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2021, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1fae)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        case 1:
        {
            float x = object->unk104 + object->unk108;
            text->func_004C7FE0(x, object->unka4, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2022, 0);
            func_0041AD10(marker, x, object->unka4, func_004C69B0(text)->unk08, 24.0f);
            if (key == 0x1faf)
            {
                text->set_color(0x808080);
                marker->unk3f = 1;
            }
            else
            {
                text->set_color(0x505050);
                marker->unk3f = 0;
            }
            break;
        }
        }
        func_004C6190(object->unk10, text);
        func_004C6190(object->unk10, marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list5_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list5_second), marker);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&object->list0_first), text);
        func_003527D0(reinterpret_cast<ConfigListOwner*>(&object->list0_second), marker);
    }
    return 1;
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_003501B0);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00350270);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_slotb4__13ConfigOptionsFv);

/**
 * @brief Configure the frame bounds.
 * @param object Frame widget.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param width Frame width.
 * @param height Frame height.
 */
extern "C" void func_0044B570(LibClass1746A0* object, float x, float y, float width, float height);
/**
 * @brief Set the frame display flag.
 * @param object Frame widget.
 * @param flag Display flag.
 */
extern "C" void func_0044B510(LibClass1746A0* object, u32 flag);

s32 ConfigOptions::func_slotf4(void* associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 72.0f, 11);
    unk28c = new (0) LibClass1725D0;
    func_41A930(unk28c, 586.0f, 16.0f, 368.0f, unk290, unk294);
    func_004C6190(unk10, unk28c);
    LibClass1746A0* frame = new (0) LibClass1746A0;
    LibClass1746A0* cover = new (0) LibClass1746A0;
    func_0044B570(frame, 8.0f, 8.0f, 576.0f, 384.0f);
    func_004C6190(unk10, frame);
    last_index = 13;
    s32 extra_key;
    if (config_extra(D_001B643C->settings) == 0)
    {
        extra_key = 0;
    }
    else
    {
        extra_key = config_mode(D_001B643C->settings) == 1 ? 0x1FC5 : 0x1FC6;
    }
    if (extra_key == 0)
    {
        unk100 = 0;
    }
    else
    {
        unk100 = 1;
    }
    if (extra_key == 0)
    {
        unkb6 = last_index - 1;
    }
    else
    {
        unkb6 = last_index;
    }
    unk10c = 28.0f;
    s32 position = 0;
    float spacing = 22.0f;
    for (s32 i = 0; i < 8; i++, position++)
    {
        LibObject178750* text = new (0) LibObject178750;
        switch (i)
        {
        case 0:
            positions[position] = 16.0f;
            break;
        case 2:
            positions[position] = 50.0 + positions[i - 1] + spacing;
            break;
        default:
            positions[position] = 22.0f + positions[i - 1] + spacing;
            break;
        }
        text->func_004C7FE0(24.0f, positions[position], 0.0f, 0.0f, reinterpret_cast<s32>(associated), i + 0x2008, 1);
        text->set_color(0x806080);
        text->unk88 = -1.0f;
        text->unk3c = 1;
        func_004C6190(unk10, text);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&list0_first), text);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&list), text);
    }
    for (s32 i = 0; i < 6; i++, position++)
    {
        if (i == 5 && unk100 == 0)
        {
            break;
        }
        LibObject178750* text = new (0) LibObject178750;
        switch (i)
        {
        case 0:
            positions[position] = 416.0f;
            break;
        case 1:
            positions[position] = 22.0f + (42.0f + (positions[position - 1] + unk10c));
            break;
        case 6:
            positions[position] = (22.0f + (positions[position - 1] + unk10c)) - 6.0f;
            break;
        default:
            positions[position] = 22.0f + (positions[position - 1] + unk10c);
            break;
        }
        float y = positions[position];
        if (i == 5)
        {
            text->func_004C7FE0(24.0f, y, 0.0f, 0.0f, reinterpret_cast<s32>(associated), 0x2016, 1);
        }
        else
        {
            text->func_004C7FE0(24.0f, y, 0.0f, 0.0f, reinterpret_cast<s32>(associated), i + 0x2010, 1);
        }
        text->set_color(0x806080);
        text->unk88 = -1.0f;
        text->unk3c = 1;
        func_004C6190(unk10, text);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&list0_first), text);
        func_00352AF0(reinterpret_cast<ConfigListOwner*>(&list), text);
    }
    s32 enabled_key;
    ConfigSettings* settings = D_001B643C->settings;
    if (config_flag(settings) == 0 || config_enabled(settings) == 0)
    {
        unk101 = 0;
        enabled_key = 0;
    }
    else
    {
        unk101 = 1;
        enabled_key = D_001B643C->settings->unk18d != 0 ? 0x1FC1 : 0x1FC2;
    }
    if (enabled_key == 0)
    {
        LibObject178750* text = static_cast<LibObject178750*>(func_00352C00(reinterpret_cast<ConfigListOwner*>(&list), 11)->value);
        text->set_color(0x505050);
    }
    func_0034FC70(this, associated);
    func_0034F880(this, associated);
    func_0034F5E0(this, associated);
    func_0034F340(this, associated);
    func_0034FF10(this, associated);
    func_0034F0A0(this, associated);
    func_0034EDE0(this, associated);
    func_0034EB40(this, associated);
    func_0034E5D0(this, associated);
    func_0034E330(this, associated);
    func_0034E090(this, associated);
    func_0034DDF0(this, associated);
    func_0034DB50(this, associated);
    if (unk100 != 0)
    {
        func_0034D8B0(this, associated);
    }
    func_0044B510(cover, 1);
    func_004C6190(unk10, cover);
    unk110 = 24.0f;
    scroll = new (0) LibClass175030;
    func_00467360(scroll, unk110, 12.0f + positions[0]);
    func_004C6190(unk10, scroll);
    func_0034B180(this, 0);
    s32 key = func_00350270(this, selected);
    if (key != unkb8)
    {
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(key);
        unkb8 = key;
    }
    if (unka8 != 0)
    {
        func_00351FD0(static_cast<ConfigPreviewState*>(unka8));
    }
    return 1;
}

ConfigOptions::~ConfigOptions()
{
}

ConfigOptions::ConfigOptions()
{
    func_slotec(1);
    unka8 = 0;
    scroll = 0;
    unkb0 = 0;
    last_index = 0;
    unkb6 = 0;
    s32 index;
    for (index = 0; index < 14; index++)
    {
        positions[index] = 0;
    }
    unkf4 = 0;
    unkf8 = -1;
    unkfc = -1;
    unk100 = 0;
    unkb8 = 0;
    unk104 = 218.0f;
    unk108 = 172.0f;
    unk10c = 0.0f;
    unk110 = 0.0f;
    selected = 0;
    unkb2 = 1;
    unk288 = 0;
    unk28c = 0;
    unk290 = 50.0f;
    unk294 = 0.0f;
    unk298 = 0.0f;
    unk29c = 0.0f;
    unk2a0 = 100.0f;
    unk101 = 0;
}

s32 func_003514E0(ConfigFrameWindow* object, void* associated)
{
    func_002CE8D0(reinterpret_cast<FieldObjectCE8D0*>(object), associated, 16.0f, 72.0f, 11);
    object->frame = new (0) LibClass178630;
    func_004C5A80(object->frame, 0, 0.0f, 0.0f, 608.0f, 400.0f, 88.0f);
    func_004C6190(object->unk10, object->frame);
    return 1;
}

void* func_003515B0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181E70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            ::operator delete(object);
        }
    }
    return object;
}

void func_00351610(ConfigMessageWindow* object, s32 key)
{
    if (key >= 0x1FA4 && key < 0x1FC8)
    {
        object->unkb2 = 0;
        object->unkb0 = 0;
        func_4C6DF0(object->text, object->source, key, 1);
        object->extent = func_004C69B0(object->text)->unk08;
        if (key == 0x1FB8 || key == 0x1FBA)
        {
            object->key = key;
            object->active = 1;
        }
        else
        {
            object->active = 0;
        }
    }
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_003516B0);

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00351820);

void* func_00351BD0(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_181F70;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            ::operator delete(object);
        }
    }
    return object;
}

s32 func_00351C30(ConfigPreviewWindow* object, void* associated)
{
    func_002CE8D0(reinterpret_cast<FieldObjectCE8D0*>(object), associated, 16.0f, 16.0f, 20);
    object->resources[0] = new (0) ItemCreationOptionResourceDisplay;
    object->resources[1] = new (0) ItemCreationOptionResourceDisplay;
    object->resources[2] = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = func_002D3D80(D_001B643C->resources, 11);
    object->resources[0]->unkcc = allocation;
    object->resources[1]->unkcc = allocation;
    object->resources[2]->unkcc = allocation;
    object->resources[0]->unkd0 = 11;
    object->resources[1]->unkd0 = 11;
    object->resources[2]->unkd0 = 11;
    initialize_preview_resource(object->resources[0], func_002D3CC0(D_001B643C->resources, 5), 0.0f, 0.0f);
    initialize_preview_resource(object->resources[1], func_002D3CC0(D_001B643C->resources, 6), 256.0f, 0.0f);
    initialize_preview_resource(object->resources[2], func_002D3CC0(D_001B643C->resources, 7), 512.0f, 0.0f);
    func_004C6190(object->unk10, object->resources[0]);
    func_004C6190(object->unk10, object->resources[1]);
    func_004C6190(object->unk10, object->resources[2]);
    object->display = new (0) ItemCreationOptionResourceDisplay;
    object->display->unkcc = func_002D3D80(D_001B643C->resources, 12);
    object->display->unkd0 = 12;
    initialize_preview_resource(object->display, func_002D3CC0(D_001B643C->resources, 0), 120.0f, 104.0f);
    ItemCreationOptionResourceDisplay* display = object->display;
    display->unk50.unk34 = 1.4f;
    display->unk50.unk30 = 1.4f;
    display->unk3c = 1;
    func_004C6190(object->unk10, object->display);
    return 1;
}

void* func_00351F70(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_182070;
        func_2CEAF0(object, 0);
        if ((s16)flags > 0)
        {
            ::operator delete(object);
        }
    }
    return object;
}

void func_00351FD0(ConfigPreviewState* object)
{
    ConfigPreviewWindow* window = object->window;
    if (window != 0)
    {
        s32 flag = 0;
        FieldRuntimeSections* sections = func_101290(func_10D8E0());
        if (sections != 0)
        {
            ConfigPreviewSection* values = static_cast<ConfigPreviewSection*>(func_101440(sections, 1));
            if (values != 0)
            {
                flag = values->flag;
            }
        }
        if (window->display != 0)
        {
            set_preview_origin(window->display, 128.0f, 128.0f);
            set_widget_position(window->display, 320.0f, 240.0f);
            if (flag != 0)
            {
                set_preview_scale(window->display, 1.05f, 1.4f);
            }
            else
            {
                set_preview_scale(window->display, 1.4f, 1.4f);
            }
        }
    }
}

void func_003520B0(void* object)
{
}

void func_003520C0(ConfigControlReceiver* object)
{
    if (object->resource)
    {
        func_00465430(D_001B657C, object->resource);
    }
    func_004D65C0(object);
    object->func_001DD7B0();
}

void func_00352110(void* object)
{
    func_0011ED90(D_001B65F4, object);
}

INCLUDE_ASM("build/overlays/cconfig/asm/nonmatchings/text", func_00352130);

s32 func_00352330(ConfigControlReceiver* object, void* buffer)
{
    if (buffer == 0)
    {
        return 0;
    }
    ConfigAlignedResource* aligned = aligned_config_resource(buffer);
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
    return object->func_00263CD0();
}

s32 func_003523F0(void* object)
{
    return 1;
}

void* func_00352400(void* object, s32 flags)
{
    if (object != 0)
    {
        *(void**)object = D_182170;
        func_264230(object, 0);
        if ((s16)flags > 0)
        {
            ::operator delete(object);
        }
    }
    return object;
}

ConfigControl* func_00352460(ConfigControl* object)
{
    func_2642D0(object);
    object->methods = D_182170;
    object->field_34 = 0;
    object->field_38 = 0;
    object->field_40 = 0;
    return object;
}

void ItemCreationClass185050::func_slot0c()
{
}

s32 func_003524B0(void* object)
{
    return 0;
}

s32 func_003524C0(void* object)
{
    return 0;
}

void func_003524D0(void* object)
{
}

void func_003524E0(void* object)
{
}

void func_003524F0(void* object)
{
}

s32 func_00352500(void* object)
{
    return 4;
}

u8 func_00352510(void* object)
{
    return ((ConfigInputFields*)object)->field_38;
}

void func_00352520(void* object, u32 value)
{
    ((ConfigInputFields*)object)->field_24 = value;
}

void func_00352530(void* object, s8 value)
{
    ((ConfigInputFields*)object)->field_28 = value;
}

s8 func_00352540(void* object)
{
    return ((ConfigInputFields*)object)->field_28;
}

s32 func_00352550(void* object)
{
    return 0;
}

s32 func_00352560(void* object)
{
    return 0;
}

void func_00352570(void* object)
{
}

s32 func_00352580(void* object)
{
    return 0;
}

void func_00352590(void* object)
{
}

void func_003525A0(void* object)
{
}

void func_003525B0(void* object)
{
}

s32 func_003525C0(void* object)
{
    return 0;
}

s32 func_003525D0(void* object)
{
    return 0;
}

s32 func_003525E0(void* object)
{
    return 0;
}

void func_003525F0(void* object)
{
}

void func_00352600(ConfigListOwner* list, void* value)
{
    ConfigNode* node = new (0) ConfigNode;
    if (node != 0)
    {
        ConfigNode* tail;
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

ConfigNode* func_00352690(ConfigListOwner* owner, s32 index)
{
    ConfigNode* node = owner->head->next;
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

ConfigList182210::ConfigList182210()
{
    head = new (0) ConfigNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

ConfigList182210::~ConfigList182210()
{
    func_00352860(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_003527D0(ConfigListOwner* list, void* value)
{
    ConfigNode* node = new (0) ConfigNode;
    if (node != 0)
    {
        ConfigNode* tail;
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

void func_00352860(ConfigList182210* object)
{
    ConfigNode* node = object->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        ConfigNode* next = node->next;
        delete node;
        node = next;
    }
    object->head->next = 0;
    object->count = 0;
}

ConfigNode* func_003528E0(ConfigListOwner* owner, s32 index)
{
    ConfigNode* node = owner->head->next;
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

void func_00352920(ConfigListOwner* list, void* value)
{
    ConfigNode* node = new (0) ConfigNode;
    if (node != 0)
    {
        ConfigNode* tail;
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

ConfigNode* func_003529B0(ConfigListOwner* owner, s32 index)
{
    ConfigNode* node = owner->head->next;
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

ConfigList182200::ConfigList182200()
{
    head = new (0) ConfigNode;
    if (head == 0)
    {
        throw;
    }
    head->next = 0;
    count = 0;
}

ConfigList182200::~ConfigList182200()
{
    func_00352B80(this);
    if (head != 0)
    {
        ::operator delete(head);
        head = 0;
    }
}

void func_00352AF0(ConfigListOwner* list, void* value)
{
    ConfigNode* node = new (0) ConfigNode;
    if (node != 0)
    {
        ConfigNode* tail;
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

void func_00352B80(ConfigList182200* object)
{
    ConfigNode* node = object->head->next;
    if (node == 0)
    {
        return;
    }
    while (node != 0)
    {
        ConfigNode* next = node->next;
        delete node;
        node = next;
    }
    object->head->next = 0;
    object->count = 0;
}

ConfigNode* func_00352C00(ConfigListOwner* owner, s32 index)
{
    ConfigNode* node = owner->head->next;
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

void func_00352C40(ConfigListOwner* list, void* value)
{
    ConfigNode* node = new (0) ConfigNode;
    if (node != 0)
    {
        ConfigNode* tail;
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

void func_00352CD0(ConfigListOwner* list, void* value)
{
    ConfigNode* node = new (0) ConfigNode;
    if (node != 0)
    {
        ConfigNode* tail;
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
