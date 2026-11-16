#include "include_asm.h"
#include "sdk/main/libc_0013CA60.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libc_guess_0013C948.h"
#include "overlays/cmc/text.h"
#include "main/resident_data.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/1067-00/field_duration.h"
#include "overlays/1067-00/text_001E1590.h"
#include "overlays/1067-00/text_002CEAF0.h"
#include "overlays/1067-00/field_runtime.h"
#include "overlays/1067-00/text_002D3BD0.h"
#include "overlays/1067-00/text_0020E4B0.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/1067-00/text_002F9C90.h"
#include "overlays/lib/model.h"

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
/** Partial menu state the card windows signal when they close. */
struct CmcMenuState
{
    /**
     * @brief Check whether the menu is closing.
     * @return True when the closing flag is set.
     */
    bool is_closing()
    {
        return unk2d != 0;
    }

    u8 unk00[0x2D];
    u8 unk2d;
    u8 unk2e[0x6D];
    u8 unk9b;
    u8 unk9c;
    u8 unk9d;
    u8 unk9e;
};

/** Partial system record holding the last save's identifier. */
struct CmcSystemRecord
{
    u8 unk000[0x188];
    u32 unk188;
};

struct FieldWindowRuntime
{
    ResidentCheckedRecord* unk00;
    u8 unk04[8];
    CmcMenuState* unk0c;
    FieldWindowCallbacks* unk10;
    u8 unk14[0xC];
    FieldBufferSlots* slots;
};

extern "C" FieldWindowRuntime* D_001B643C;

/**
 * @brief Return the field object that owns the screen effects.
 * @return Field display object.
 */
static inline FieldClass1516A0* field_display()
{
    return reinterpret_cast<FieldClass1516A0*>(D_001B6430->context->unk38);
}

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

extern "C" {
extern u8 g_default_bounding_sphere[];

extern void lib_draw_buffer_end(LibDrawBuffer* buffer, u8 mode, float distance, s32 flag);

extern const char D_35B380[];
extern const char D_35B390[];
extern LibDisplayManager* g_scene_display_manager;

extern void func_4C4960(void* object);

extern void func_420D20(ItemCreationClass172870* object, u32 color);

extern void func_002F2890(FieldClass15B9C0* object);

extern CmcRowRecord* func_002EEDA0(FieldClass15B9C0* object, s16 index);

extern void func_002EEE20(FieldClass15B9C0* object, s16 value, u8 flag);

extern s32 func_002EE9C0(FieldClass15B9C0* object, void* value);

extern u8 func_002EFFF0(FieldClass15B9C0* object);

extern LibCardFileRequest* func_002EF000(FieldClass15B9C0* object);

extern u8 func_002EF6B0(FieldClass15B9C0* object);

extern void func_002EF030(FieldClass15B9C0* object, s16 slot);

extern u8 func_002F1E60(FieldClass15B9C0* object);

extern u8 func_002F1B20(FieldClass15B9C0* object);

extern void func_00432710(LibMemoryCard* card, u32 flags);

extern void func_002EEE00(FieldClass15B9C0* object, CmcRowRecord* entry);

extern u8 func_002EEE90(FieldClass15B9C0* object, s16 index);

extern void func_002F0D90(FieldClass15B9C0* object, FieldClass15B9C0Record* record);

extern void func_002EDEC0(FieldClass15B9C0* object, FieldClass15B9C0Record* record);

extern void func_002EDFA0(FieldClass15B9C0* object);

extern void func_002F23E0(FieldClass15B9C0* object, const char* game, const char* suffix);

extern void func_002EF010(FieldClass15B9C0* object, s16 value);

extern u8 func_002EF520(FieldClass15B9C0* object);

extern u8 func_002EED90(FieldClass15B9C0* object);

extern u8 func_002EEC90(FieldClass15B9C0* object);

extern s32 func_002EEB30(FieldClass15B9C0* object);

extern void func_002EE9E0(FieldClass15B9C0* object);

extern void func_431770(LibMemoryCard* card, s32 value);

extern const char D_35B3A0[];
extern const char D_35B3A8[];

extern u16 func_002EE9B0(FieldClass15B9C0* object);

extern const char D_35B300[];

extern u8 func_002F2470(FieldClass15B9C0* object, s32 mode);

extern LibUpdateList* g_update_list;

extern u8 func_4135D0(LibClass1723F0* aggregate);

extern s32 func_413460(LibClass1723F0* aggregate);

extern void func_413750(LibClass1723F0* aggregate);

extern void func_413C00(LibClass1723F0* object, s32 count, s32 columns, s32 rows, float width, float row_height, float timing);

extern void func_4138E0(LibClass1723F0* object, s32 first, s32 second, s32 count);
}

/**
 * @brief Return the list kind the object goes into by default.
 * @return Three.
 */
s32 LibListObject::get_default_list_kind()
{
    return 3;
}

/** @brief Update the object; the base does nothing. */
void LibListObject::update()
{
}

/** @brief Render the object; the base does nothing. */
void LibListObject::render()
{
}

/** @brief Detach from the owner, detach and destroy the model, then delete the bar. */
void CmcClass188D80::destroy()
{
    lib_object_detach_owner(this);

    if (model != 0)
    {
        lib_object_detach_owner(model);
        // TODO: called through LibListObject so LibModelBase's inline destroy isn't emitted here
        static_cast<LibListObject*>(model)->destroy();
        model = 0;
    }

    delete this;
}

/**
 * @brief Append one vertex to a draw buffer's streams.
 * @param buffer Draw buffer.
 * @param position Vertex position.
 * @param normal Vertex normal.
 * @param texcoord Packed texture coordinates.
 * @param color Vertex color.
 */
static inline void add_vertex(LibDrawBuffer* buffer, const FieldVec4A& position, const FieldVec4A& normal, u32 texcoord, u32 color)
{
    *buffer->positions = position;
    buffer->positions++;
    *buffer->normals = normal;
    buffer->normals++;
    *buffer->texcoords++ = texcoord;
    *buffer->colors++ = color;
    buffer->vertex_count++;
}

/**
 * @brief Draw the bar's border, outline and a fill proportional to done / total.
 * @param done Completed amount.
 * @param total Total amount.
 */
void CmcClass188D80::func_00348520(s32 done, s32 total)
{
    CmcDrawParameters settings;

    lib_draw_buffer_begin(draw_buffer, 6, 1);
    cmc_initialize_drawing_parameters(&settings);
    settings.primitive_flags = 0xC;
    settings.unk02 = 0;
    settings.unk05 = 1;
    settings.unk06 = 0;
    FieldVec4A normal(0.0f, 0.0f, -1.0f, 1.0f);

    if (total < done)
    {
        done = total;
    }

    lib_draw_buffer_apply_settings(draw_buffer, reinterpret_cast<LibDrawSettings*>(&settings));
    s32 bar_width = width;
    s32 bar_height = height;
    u32 bar_color = color;
    s32 depth = mode;
    lib_draw_buffer_begin_primitive(draw_buffer, 4);
    add_vertex(draw_buffer, FieldVec4A(-2.0f, -1.0f, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(draw_buffer, FieldVec4A(2.0f + bar_width, -1.0f, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(draw_buffer, FieldVec4A(-2.0f, 1.0f + bar_height, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(draw_buffer, FieldVec4A(2.0f + bar_width, 1.0f + bar_height, (float)depth, 1.0f), normal, 0, 0x80301004);
    lib_draw_buffer_begin_primitive(draw_buffer, 4);
    add_vertex(draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A((float)bar_width, 0.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(0.0f, 1.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A((float)bar_width, 1.0f, (float)depth, 1.0f), normal, 0, bar_color);
    lib_draw_buffer_begin_primitive(draw_buffer, 4);
    add_vertex(draw_buffer, FieldVec4A(0.0f, bar_height - 1.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A((float)bar_width, bar_height - 1.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(0.0f, (float)bar_height, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A((float)bar_width, (float)bar_height, (float)depth, 1.0f), normal, 0, bar_color);
    lib_draw_buffer_begin_primitive(draw_buffer, 4);
    add_vertex(draw_buffer, FieldVec4A(-1.0f, 0.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(1.0f, 0.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(-1.0f, (float)bar_height, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(1.0f, (float)bar_height, (float)depth, 1.0f), normal, 0, bar_color);
    lib_draw_buffer_begin_primitive(draw_buffer, 4);
    add_vertex(draw_buffer, FieldVec4A(bar_width - 1.0f, 0.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(1.0f + bar_width, 0.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(bar_width - 1.0f, (float)bar_height, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(1.0f + bar_width, (float)bar_height, (float)depth, 1.0f), normal, 0, bar_color);
    lib_draw_buffer_begin_primitive(draw_buffer, 4);
    s32 fill = done * 1000 / total;
    add_vertex(draw_buffer, FieldVec4A(3.0f, 3.0f, (float)depth, 1.0f), normal, 0, bar_color);
    float right = 3.0f + ((bar_width - 6.0f) * fill) / 1000.0f;
    add_vertex(draw_buffer, FieldVec4A(right, 3.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(3.0f, bar_height - 3.0f, (float)depth, 1.0f), normal, 0, bar_color);
    add_vertex(draw_buffer, FieldVec4A(right, bar_height - 3.0f, (float)depth, 1.0f), normal, 0, bar_color);
    lib_draw_buffer_end(draw_buffer, 1, 50000.0f, 1);
    LibModel* shown = model;

    if (shown->unk793 < 4)
    {
        shown->unk793++;
    }

    shown->unk795 = 1;

    for (s32 index = 0; index < 0x20; index++)
    {
        shown->unk728[index] = 0;
    }

    shown->unk797_1 = 1;
}

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

/**
 * @brief Recreate the bar's draw buffer and model, set the model up, draw the bar empty and show it.
 * @param width Bar width.
 * @param height Bar height.
 * @param color Bar color.
 * @param mode Draw mode.
 */
void CmcClass188D80::func_003492E0(s32 width, s32 height, u32 color, s32 mode)
{
    if (draw_buffer != 0)
    {
        delete draw_buffer;
    }

    if (model != 0)
    {
        // TODO: called through LibListObject so LibModelBase's inline destroy isn't emitted here
        static_cast<LibListObject*>(model)->destroy();
    }

    draw_buffer = new (0) LibDrawBuffer;
    model = new (0) LibModel;
    LibVector4 sphere;
    set_vector(&sphere, 0.0f, 0.0f, 0.0f, 100000.0f);
    copy_vector(&model->bounding_sphere, &sphere);
    LibVector4 position;
    set_vector(&position, 0.0f, 0.0f, 0.0f, 1.0f);
    model->set_translation_vector(&position);
    LibModel* offset_model = model;
    set_vector(&offset_model->offset_translation, 0.0f, 0.0f, 0.0f, 1.0f);
    lib_rebuild_offset_transform(offset_model);
    offset_model->transform_dirty = 1;
    LibVector4 white;
    set_vector(&white, 1.0f, 1.0f, 1.0f, 1.0f);
    LibModel* color_model = model;
    copy_vector(&color_model->color_modulation, &white);
    color_model->update_combined_color_factor();
    model->light_mask = 0;
    model->display_manager = g_scene_display_manager;
    model->draw_flags |= LIB_DRAW_FLAG_0400;
    draw_buffer->allocate_storage(2, 0x600, 1, 8);
    this->width = width;
    this->height = height;
    this->color = color;
    this->mode = mode;
    func_00348520(0, 1);
    model->attach_draw_buffer(draw_buffer);
    static_cast<LibUpdateList*>(g_renderer)->append_node(model, -1);
}

void func_003494F0(Overlay0072Object003494F0* object, const unsigned __int128* value)
{
    object->field_50 = 1;
    object->field_20 = *value;
}

/** @brief Destroy the child and the object. */
CmcClass188D80::~CmcClass188D80()
{
    if (model != 0)
    {
        // TODO: called through LibListObject so LibModelBase's inline destroy isn't emitted here
        static_cast<LibListObject*>(model)->destroy();
    }
}

s32 func_00349670(Overlay0072Object00349670* object)
{
    return object->field_4;
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 CmcClass188F10::func_slotb0()
{
    CmcClass18AF20* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return One.
 */
s32 CmcClass188F10::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 56.0f, 200.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 528.0f, 128.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x234A, 0, 16.0f, 16.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
CmcClass188F10::~CmcClass188F10()
{
}

/**
 * @brief Request controller action 0x79, hide the nested display, and select the second choice.
 * @return Two.
 */
u8 CmcClass189010::func_slotb4()
{
    CmcClass18AF20* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    selector->func_0023B280(1);
    unkb0->set_tint(0x808080);
    unkb4->set_tint(0x288080);
    marker->func_0023B7E0(unkb4);
    return 2;
}

/**
 * @brief Confirm the first choice, or behave like func_slotb4 for the second.
 * @return Zero while the selector is still moving, otherwise one.
 */
u8 CmcClass189010::func_slotb0()
{
    if (selector->is_moving())
    {
        return 0;
    }

    if (selector->func_0023B3A0() == 0)
    {
        func_slot24(1);
        set_state(0xFF, 0x40);
        unka8->unk54 = 0;
        ResidentCheckedRecord* record = static_cast<ResidentCheckedRecord*>(func_101440(func_101290(resident_get_system()), 1));

        if (record != 0)
        {
            record->unk25_6 = 0;
        }

        unka8->func_003583B0();
    }
    else
    {
        CmcClass18AF20* controller = unka8;

        if (controller != 0)
        {
            controller->unk54 = 0x79;

            if (controller->unk54 != 0)
            {
                controller->dispatch_window_request();
            }
        }
    }

    func_slot20(0);
    selector->func_0023B280(1);
    unkb0->set_tint(0x808080);
    unkb4->set_tint(0x288080);
    marker->func_0023B7E0(unkb4);
    return 1;
}

void func_00349AB0(Overlay0072Object00349AB0* object, u8 value)
{
    object->field_C = value;
}

/** @brief Move the selector in direction two and recolour the choices. */
void CmcClass189010::func_slot74()
{
    if (selector->func_0023B3B0(2) != 1)
    {
        u16 selected = selector->func_0023B3A0();

        for (s32 index = 0; index < 2; index++)
        {
            LibTextWidget* text = static_cast<LibTextWidget*>(unk2c.at(index)->value);

            if (index == selected)
            {
                text->set_tint(0x288080);
                marker->func_0023B7E0(text);
            }
            else
            {
                text->set_tint(0x808080);
            }
        }
    }
}

/** @brief Move the selector in direction three and recolour the choices. */
void CmcClass189010::func_slot70()
{
    if (selector->func_0023B3B0(3) != 1)
    {
        u16 selected = selector->func_0023B3A0();

        for (s32 index = 0; index < 2; index++)
        {
            LibTextWidget* text = static_cast<LibTextWidget*>(unk2c.at(index)->value);

            if (index == selected)
            {
                text->set_tint(0x288080);
                marker->func_0023B7E0(text);
            }
            else
            {
                text->set_tint(0x808080);
            }
        }
    }
}

/**
 * @brief Create the panel, the question and both choices, the selector, and its marker.
 * @param associated Full resource source word.
 * @return One.
 */
s32 CmcClass189010::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 20.0f, 180.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    unkb0 = new (0) LibTextWidget;
    unkb4 = new (0) LibTextWidget;
    selector = new (0) FieldClass153130;
    marker = new (0) FieldClass153170;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 600.0f, 164.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2349, 0, 16.0f, 16.0f, 568.0f, 120.0f);
    lib_text_init_resource_rectangle(unkb0, static_cast<s32>(associated), 0x7E8, 0, 188.0f, 128.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(unkb4, static_cast<s32>(associated), 0x7E9, 0, 328.0f, 128.0f, 0.0f, 0.0f);
    unkac->set_horizontal_align(1);
    lib_container_attach_widget(unk10, unkac);
    lib_container_attach_widget(unk10, unkb0);
    lib_container_attach_widget(unk10, unkb4);
    unk2c.append(unkb0);
    unk2c.append(unkb4);
    selector->func_0023B530(2, 1, 1, 1, 1, 188.0f, 140.0f, 140.0f, 0.0f);
    lib_container_attach_widget(unk10, selector);
    marker->func_0023B850(unkb4, 0x288080);
    lib_container_attach_widget(unk10, marker);
    unkb4->set_tint(0x288080);
    marker->func_0023B7E0(unkb4);
    return 1;
}

/** @brief Destroy the dialog. */
CmcClass189010::~CmcClass189010()
{
}

/** @brief While this is the focused window, colour each choice by its record state and move the marker. */
void CmcClass189110::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (func_slot28())
    {
        return;
    }

    u16 selected = selector->func_0023B3A0();

    if (linked->func_0035AFD0(0) == 2)
    {
        first_text->set_tint(0x288080);

        if (marker != 0 && selected == 0)
        {
            marker->func_0023B7E0(first_text);
            func_420D20(marker, 0x288080);
        }
    }
    else
    {
        first_text->set_tint(0x505050);

        if (marker != 0 && selected == 0)
        {
            marker->func_0023B7E0(first_text);
            func_420D20(marker, 0x505050);
        }
    }

    if (linked->func_0035AFD0(1) == 2)
    {
        second_text->set_tint(0x288080);

        if (marker != 0 && selected == 1)
        {
            marker->func_0023B7E0(second_text);
            func_420D20(marker, 0x288080);
        }
    }
    else
    {
        second_text->set_tint(0x505050);

        if (marker != 0 && selected == 1)
        {
            marker->func_0023B7E0(second_text);
            func_420D20(marker, 0x505050);
        }
    }
}

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
u8 CmcClass189110::func_slotb4()
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

/**
 * @brief Pick the selected record when its state is two, or request controller window 0x6C otherwise.
 * @return Zero while the selector is still moving, three when the record isn't ready, otherwise one.
 */
u8 CmcClass189110::func_slotb0()
{
    if (selector->is_moving())
    {
        return 0;
    }

    u16 selected = selector->func_0023B3A0();
    u16 state = linked->func_0035AFD0(selected);
    g_field_runtime->message_arguments[1] = static_cast<s16>(selected + 1);

    if (state != 2)
    {
        unka8->request_window(0x6C);
        return 3;
    }

    unka8->request_window(0x73);
    linked->unk5c = -1;
    linked->func_0035ADD0(selected, 1);

    if (unka8 != 0)
    {
        CmcClass18AD20* window = unka8->unk4c;
        window->unkB8 = selected;
        window->unkB9 = 1;
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the panel, the two choices and their selector and marker.
 * @param associated Full resource source word.
 * @return Zero when the controller has no linked object, otherwise one.
 */
s32 CmcClass189110::func_slotf4(u32 associated)
{
    linked = reinterpret_cast<CmcClass18AFB0*>(unka8->func_slot60());

    if (linked == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 140.0f, 212.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    first_text = new (0) LibTextWidget;
    second_text = new (0) LibTextWidget;
    selector = new (0) FieldClass153130;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 360.0f, 112.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    unk14.append(panel);
    lib_text_init_resource_rectangle(first_text, static_cast<s32>(associated), 0x513, 0, 70.0f, 24.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(second_text, static_cast<s32>(associated), 0x514, 0, 70.0f, 64.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, first_text);
    lib_container_attach_widget(unk10, second_text);
    selector->func_0023B530(1, 2, 1, 0, 1, 70.0f, 36.0f, 0.0f, 40.0f);
    lib_container_attach_widget(unk10, selector);
    marker = new (0) FieldClass153170;
    marker->func_0023B850(first_text, 0x288080);
    lib_container_attach_widget(unk10, marker);
    return 1;
}

s32 func_0034A690(Overlay0072Object0034A690* object)
{
    return object->field_38;
}

/** @brief Destroy the window and its Field parent. */
CmcClass189110::~CmcClass189110()
{
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 CmcClass189210::func_slotb0()
{
    CmcClass18AF20* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return One.
 */
s32 CmcClass189210::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 78.0f, 180.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 486.0f, 164.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2348, 0, 16.0f, 16.0f, 454.0f, 120.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189210::~CmcClass189210()
{
}

/**
 * @brief Request controller action 0x79 and hide the nested display once the selector stops.
 * @return Zero while the selector is still moving, otherwise one.
 */
u8 CmcClass189310::func_slotb4()
{
    if (selector->is_moving())
    {
        return 0;
    }

    CmcClass18AF20* controller = unka8;
    controller->unk54 = 0x79;

    if (controller->unk54 != 0)
    {
        controller->dispatch_window_request();
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Confirm the first choice, or request controller action 0x79 for the second.
 * @return Zero while the selector is still moving, otherwise one.
 */
u8 CmcClass189310::func_slotb0()
{
    if (selector->is_moving())
    {
        return 0;
    }

    if (selector->func_0023B3A0() == 0)
    {
        func_slot24(1);
        set_state(0xFF, 0x40);
        unka8->unk54 = 0;
        ResidentCheckedRecord* record = static_cast<ResidentCheckedRecord*>(func_101440(func_101290(resident_get_system()), 1));

        if (record != 0)
        {
            record->unk25_6 = 0;
        }

        unka8->func_003583B0();
    }
    else
    {
        CmcClass18AF20* controller = unka8;
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/** @brief Move the selector in direction two and recolour the choices. */
void CmcClass189310::func_slot74()
{
    if (selector->func_0023B3B0(2) != 1)
    {
        u16 selected = selector->func_0023B3A0();

        for (s32 index = 0; index < 2; index++)
        {
            LibTextWidget* text = static_cast<LibTextWidget*>(unk2c.at(index)->value);

            if (index == selected)
            {
                text->set_tint(0x288080);
                marker->func_0023B7E0(text);
            }
            else
            {
                text->set_tint(0x808080);
            }
        }
    }
}

/** @brief Move the selector in direction three and recolour the choices. */
void CmcClass189310::func_slot70()
{
    if (selector->func_0023B3B0(3) != 1)
    {
        u16 selected = selector->func_0023B3A0();

        for (s32 index = 0; index < 2; index++)
        {
            LibTextWidget* text = static_cast<LibTextWidget*>(unk2c.at(index)->value);

            if (index == selected)
            {
                text->set_tint(0x288080);
                marker->func_0023B7E0(text);
            }
            else
            {
                text->set_tint(0x808080);
            }
        }
    }
}

/**
 * @brief Create the panel, the question and both choices, the selector, and its marker.
 * @param associated Full resource source word.
 * @return One.
 */
s32 CmcClass189310::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 52.0f, 158.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    unkb0 = new (0) LibTextWidget;
    unkb4 = new (0) LibTextWidget;
    selector = new (0) FieldClass153130;
    marker = new (0) FieldClass153170;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 520.0f, 232.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2345, 0, 16.0f, 40.0f, 488.0f, 120.0f);
    lib_text_init_resource_rectangle(unkb0, static_cast<s32>(associated), 0x7E8, 0, 168.0f, 196.0f, 0.0f, 0.0f);
    lib_text_init_resource_rectangle(unkb4, static_cast<s32>(associated), 0x7E9, 0, 288.0f, 196.0f, 0.0f, 0.0f);
    unkac->set_horizontal_align(1);
    unkac->set_vertical_align(1);
    lib_container_attach_widget(unk10, unkac);
    lib_container_attach_widget(unk10, unkb0);
    lib_container_attach_widget(unk10, unkb4);
    unk2c.append(unkb0);
    unk2c.append(unkb4);
    selector->func_0023B530(2, 1, 1, 1, 1, 168.0f, 208.0f, 120.0f, 0.0f);
    lib_container_attach_widget(unk10, selector);
    marker->func_0023B850(unkb4, 0x288080);
    lib_container_attach_widget(unk10, marker);
    unkb4->set_tint(0x288080);
    marker->func_0023B7E0(unkb4);
    marker->unk5c = 1;
    return 1;
}

/** @brief Destroy the dialog. */
CmcClass189310::~CmcClass189310()
{
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 CmcClass189410::func_slotb0()
{
    CmcClass18AF20* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return One.
 */
s32 CmcClass189410::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 98.0f, 208.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 444.0f, 112.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2344, 0, 16.0f, 16.0f, 412.0f, 120.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189410::~CmcClass189410()
{
}

/**
 * @brief Set bit 6 of the checked record's byte 0x25, lock the window, and run the controller's closing step.
 * @return One.
 */
u8 CmcClass189510::func_slotb0()
{
    func_slot24(1);
    set_state(0xFF, 0x40);
    unka8->unk54 = 0;
    ResidentCheckedRecord* record = static_cast<ResidentCheckedRecord*>(func_101440(func_101290(resident_get_system()), 1));

    if (record != 0)
    {
        record->unk25_6 = 1;
    }

    unka8->func_003583B0();
    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return One.
 */
s32 CmcClass189510::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 98.0f, 208.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 444.0f, 112.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x2343, 0, 16.0f, 16.0f, 412.0f, 120.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189510::~CmcClass189510()
{
}

/** @brief Once this is the focused window and the linked object has finished, hide the window and request the follow-up window its result codes select. */
void CmcClass189610::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() == this)
    {
        CmcClass18AFB0* result = unkac;

        if (result->unk34 != 0)
        {
            s32 first = result->unk30;
            s32 second = result->unk4c;
            func_slot20(0);

            if (first < 0)
            {
                if (first == -2)
                {
                    unka8->request_window(0x7B);
                    return;
                }
                else
                {
                    unka8->request_window(0x75);
                    return;
                }
            }
            else if (first == 0 && second == 0)
            {
                unka8->request_window(0x74);
                return;
            }
            else if (second == 0x81)
            {
                unka8->request_window(0x7B);
                return;
            }
            else if (second == 0x83)
            {
                unka8->request_window(0x78);
                return;
            }
            else if (second == 0x86)
            {
                unka8->request_window(0x75);
                return;
            }
        }
    }
}

/**
 * @brief Take the controller's linked object, then create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when the controller has no linked object, otherwise one.
 */
s32 CmcClass189610::func_slotf4(u32 associated)
{
    unkac = reinterpret_cast<CmcClass18AFB0*>(unka8->func_slot60());

    if (unkac == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 100.0f, 202.0f, 13);
    LibPanel* panel = new (0) LibPanel;
    unkb0 = new (0) LibTextWidget;
    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 440.0f, 164.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkb0, static_cast<s32>(associated), 0x2342, 0, 16.0f, 16.0f, 408.0f, 120.0f);
    lib_container_attach_widget(unk10, unkb0);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189610::~CmcClass189610()
{
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 CmcClass189710::func_slotb4()
{
    CmcClass18AF20* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Request controller action 0x79 and hide the nested display.
 * @return One.
 */
u8 CmcClass189710::func_slotb0()
{
    CmcClass18AF20* controller = unka8;

    if (controller != 0)
    {
        controller->unk54 = 0x79;

        if (controller->unk54 != 0)
        {
            controller->dispatch_window_request();
        }
    }

    func_slot20(0);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when either widget couldn't be allocated, otherwise one.
 */
s32 CmcClass189710::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 52.0f, 208.0f, 14);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;

    if (panel == 0 || unkac == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 540.0f, 120.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x519, 0, 24.0f, 24.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, unkac);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189710::~CmcClass189710()
{
}

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

/**
 * @brief Find the save entry for a slot number among the card's entries.
 * @param slot Slot number, counting from zero.
 * @return The entry, or null when no entry has that slot.
 */
CmcRowRecord* CmcClass189810::func_0034BB50(u16 slot)
{
    s32 wanted = slot;
    u8 matched = 0;
    found = 0;

    for (s32 index = 0; index < unk4c0; index++)
    {
        found = func_002EEDA0(card->unk18, index);

        if (found != 0)
        {
            if (found->unk4c != 0x65)
            {
                if (found->slot > 0 && found->slot < 0x2E)
                {
                    found = 0;
                }
            }
            else if (wanted == found->slot - 1)
            {
                matched = 1;
                break;
            }
        }
    }

    if (matched == 1)
    {
        return found;
    }

    return 0;
}

/**
 * @brief While a selection runs, finish it with the chosen index or a cancel, otherwise apply a pending index.
 * @param first First update flag, unused here.
 * @param second Second update flag, unused here.
 * @param third Third update flag, unused here.
 */
void CmcClass189810::func_00412C40(u32 first, u32 second, u32 third)
{
    if (unk4a4 != 0)
    {
        if (func_4135D0(&static_cast<LibClass1723F0&>(*this)))
        {
            s32 result = func_413460(&static_cast<LibClass1723F0&>(*this));

            if (result > 0)
            {
                notify_index(unk30c);
            }
            else if (result < 0)
            {
                resident_sound_play(g_sound, 2, 0, 0, 127, 64, 0);
                notify_cancel();
            }

            if (result != 0)
            {
                unk4a4 = 0;
                return;
            }

            func_00413020();
            unk5d5 = 1;
        }
        else
        {
            unk5d5 = 0;
        }

        func_413750(&static_cast<LibClass1723F0&>(*this));
        return;
    }

    if (unk318 != 0)
    {
        func_00412C10(unk304);
        unk318 = 0;
    }
}

/**
 * @brief Set a row's display state from the slot list's card state for that index.
 * @param list Slot list.
 * @param row Row to update.
 * @param index Slot index the row shows.
 */
static inline void cmc_set_row_state(CmcClass189810* list, CmcClass188DA0* row, s32 index)
{
    if (list->unk4c0 != 0)
    {
        u8 state = list->unk4c6[index];

        if (state == 3)
        {
            row->unk04 = 3;
        }
        else if (state == 5)
        {
            row->unk04 = 5;
        }
        else if (state == 6)
        {
            row->unk04 = 6;
        }
        else if (state == 2)
        {
            row->unk04 = 2;
        }
    }
    else if (index >= list->unk4c4)
    {
        row->unk04 = 6;
    }
    else
    {
        row->unk04 = 2;
    }
}

/** @brief Called when the selection is cancelled; does nothing here. */
void CmcClass189810::notify_cancel()
{
}

/**
 * @brief Called when the selected index changes; does nothing here.
 * @param index Selected index.
 */
void CmcClass189810::notify_index(s32 index)
{
}

/**
 * @brief Move every row to x zero, 64 apart vertically starting at the given y.
 * @param value Vertical position of the first row.
 */
void CmcClass189810::func_00412C20(float value)
{
    for (s32 index = 0; index < unk4a0; index++)
    {
        static_cast<CmcClass188DA0*>(rows[index])->position_row(this, 0.0f, value);
        value += 64.0f;
    }
}

/**
 * @brief Refresh the visible rows for the slots starting at an index.
 * @param index Slot shown in the first row.
 */
void CmcClass189810::func_00412C10(s32 index)
{
    for (s32 row_index = 0; row_index < unk4a0; index++, row_index++)
    {
        CmcClass188DA0* row = static_cast<CmcClass188DA0*>(rows[row_index]);

        if (index < unk2f8)
        {
            if (unk4c2 != 0)
            {
                row->unk05 = 1;
                cmc_set_row_state(this, row, index);
            }
            else
            {
                row->unk05 = 0;
                cmc_set_row_state(this, row, index);
            }

            row->refresh_row(this, index);
        }
        else
        {
            row->func_003591A0(this, 0);
        }
    }
}

/**
 * @brief Create a save slot row and its panel, texts, name, play-time digits and separators.
 * @param index Row index, unused here.
 * @return The new row, or null when it or one of its widgets couldn't be set up.
 */
void* CmcClass189810::create_row(s32 index)
{
    s32 digit;
    s32 separator;
    CmcClass189900* row = new (0) CmcClass189900;

    if (row == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(&row->panel, 1, 0.0f, 0.0f, 560.0f, 64.0f, 88.0f);
    lib_container_attach_widget(this, &row->panel);

    if (!row->first_text.init_resource_rectangle(22.0f, 0.0f, 0.0f, 0.0f, resource_source, 0xAF0, 0))
    {
        return 0;
    }

    lib_container_attach_widget(this, &row->first_text);

    if (!row->string_widget.init_text_rectangle(160.0f, 8.0f, 0.0f, 0.0f, D_35B380, 0))
    {
        return 0;
    }

    lib_container_attach_widget(this, &row->string_widget);

    for (digit = 0; digit < 5; digit++)
    {
        switch (digit)
        {
        case 0:
            row->numbers[0].init_numeric_resource_rectangle(382.0f, 32.0f, 72.0f, 24.0f, 8, resource_source, 0);
            break;
        case 1:
            row->numbers[1].init_numeric_resource_rectangle(454.0f, 32.0f, 24.0f, 24.0f, 6, resource_source, 0);
            break;
        case 2:
            row->numbers[2].init_numeric_resource_rectangle(466.0f, 32.0f, 24.0f, 24.0f, 4, resource_source, 0);
            break;
        case 3:
            row->numbers[3].init_numeric_resource_rectangle(490.0f, 32.0f, 24.0f, 24.0f, 2, resource_source, 0);
            break;
        case 4:
            row->numbers[4].init_numeric_resource_rectangle(502.0f, 32.0f, 24.0f, 24.0f, 0, resource_source, 0);
            break;
        }

        lib_container_attach_widget(this, &row->numbers[digit]);
    }

    for (separator = 0; separator < 2; separator++)
    {
        switch (separator)
        {
        case 0:
            row->array_text[0].init_resource_rectangle(458.0f, 30.0f, 0.0f, 0.0f, resource_source, 0x7E4, 0);
            break;
        case 1:
            row->array_text[1].init_resource_rectangle(495.0f, 30.0f, 0.0f, 0.0f, resource_source, 0x7E4, 0);
            break;
        }

        lib_container_attach_widget(this, &row->array_text[separator]);
    }

    if (!row->second_text.init_resource_rectangle(160.0f, 32.0f, 0.0f, 0.0f, resource_source, 0x2340, 0))
    {
        return 0;
    }

    lib_container_attach_widget(this, &row->second_text);

    if (!row->fourth_text.init_resource_rectangle(140.0f, 8.0f, 0.0f, 0.0f, resource_source, 0x233D, 0))
    {
        return 0;
    }

    row->fourth_text.set_glyph_spacing(-1.0f);
    lib_container_attach_widget(this, &row->fourth_text);

    if (!row->third_text.init_resource_rectangle(472.0f, 8.0f, 0.0f, 0.0f, resource_source, 0x234C, 0))
    {
        return 0;
    }

    lib_container_attach_widget(this, &row->third_text);
    return row;
}

/**
 * @brief Rebuild the slot states from the card's save entries and refresh the rows.
 * @return One.
 */
s32 CmcClass189810::func_0034C460()
{
    unk4c0 = controller->unk48;

    for (s32 index = 0; index < unk4c0; index++)
    {
        found = func_002EEDA0(card->unk18, index);

        if (found != 0)
        {
            if (found->unk4c != 0x65)
            {
                s32 slot = found->slot;

                if (slot > 0 && slot < 0x2E)
                {
                    unk4c6[slot - 1] = 5;
                    entries[slot - 1] = 0;
                    unk5a8[index] = slot;
                }
            }
            else
            {
                s32 slot = found->slot;
                unk4c6[slot - 1] = 3;
                entries[slot - 1] = found;
                unk5a8[index] = slot;
            }
        }
    }

    s32 remaining = unk4c4 - unk4c0;

    for (s32 index = 0; index < 45; index++)
    {
        u8* state = &unk4c6[index];

        if (*state != 3 && *state != 5)
        {
            if (remaining > 0)
            {
                *state = 2;
                remaining--;
            }
            else
            {
                *state = 6;
            }
        }
    }

    func_00412C10(unk304);
    return 1;
}

/**
 * @brief Set the list up under the runtime's controller, create its rows and widgets and select the card's slot.
 * @param associated Full resource source word.
 * @param count Number of slots.
 * @param unused Unused.
 * @return One on success, or zero when something is missing or fails.
 */
s32 CmcClass189810::func_0034C5D0(u32 associated, s32 count, s32 unused)
{
    controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

    if (controller == 0)
    {
        return 0;
    }

    if (card == 0)
    {
        return 0;
    }

    resource_source = associated;
    lib_container_init(this, 0x12, 40.0f, 140.0f, 0, 0.0f, 0);
    type_id = 0x6FF6;
    unk490 = 40.0f;
    unk494 = 140.0f;
    unk498 = 574.0f;
    unk49c = 256.0f;
    s32 visible_rows = unk49c / 64.0f;
    unk4a0 = visible_rows + 2;

    if (unk4a0 <= 0 || unk4a0 > 0x2D)
    {
        return 0;
    }

    if (!lib_scissor_init_rectangle(&unk90, 0.0f, 0.0f, 574.0f, 256.0f))
    {
        return 0;
    }

    lib_container_attach_widget(this, &unk90);

    for (s32 index = 0; index < 32; index++)
    {
        rows[index] = 0;
    }

    for (s32 index = 0; index < unk4a0; index++)
    {
        void* row = create_row(index);

        if (!row)
        {
            return 0;
        }

        rows[index] = row;
    }

    if (!lib_scissor_init_reset(&unke4, 1))
    {
        return 0;
    }

    lib_container_attach_widget(this, &unke4);

    if (!lib_list_indicator_init(&unk138, 560.0f, 0.0f, 256.0f, 100.0f, 0.0f))
    {
        return 0;
    }

    lib_container_attach_widget(this, &unk138);

    if (!lib_moving_widget_init_position(&unk190, 24.0f, 20.0f))
    {
        return 0;
    }

    lib_container_attach_widget(this, &unk190);
    func_413C00(&static_cast<LibClass1723F0&>(*this), count, 1, visible_rows, 560.0f, 64.0f, 3.0f);

    if (card != 0)
    {
        u16 selected = card->unk54;

        if (selected == 0)
        {
            func_4138E0(&static_cast<LibClass1723F0&>(*this), 0, 0, unk2f8);
        }
        else if (0 < selected && selected < 5)
        {
            func_4138E0(&static_cast<LibClass1723F0&>(*this), 0, selected - 1, unk2f8);
        }
        else if (4 < selected && selected < 0x2A)
        {
            func_4138E0(&static_cast<LibClass1723F0&>(*this), selected - 2, 1, unk2f8);
        }
        else
        {
            func_4138E0(&static_cast<LibClass1723F0&>(*this), 0x29, selected - 0x2A, unk2f8);
        }
    }
    else
    {
        func_4138E0(&static_cast<LibClass1723F0&>(*this), 0, 0, unk2f8);
    }

    unk4a4 = 3;
    func_0034C460();
    return 1;
}

/** @brief Clear the list state and the 45 slot entries. */
void CmcClass189810::func_0034C970()
{
    resource_source = 0;
    controller = 0;
    card = 0;
    found = 0;
    unk4c0 = 0;
    unk4c2 = 0;
    unk4c4 = 0;

    for (s32 index = 0; index < 45; index++)
    {
        unk4c6[index] = 6;
        entries[index] = 0;
        unk5a8[index] = -1;
    }

    unk5d5 = 0;
    unk5d6 = 0;
}

/** @brief Destroy the slot list. */
CmcClass189810::~CmcClass189810()
{
}

/** @brief Initialize the container and set its transform type. */
inline LibClass1721F0::LibClass1721F0()
{
    func_0034CF80(&static_cast<LibCallbackTransform&>(*this), 0x6FF6);
}

/**
 * @brief Create the slot list for a memory card handler.
 * @param card Memory card handler the list shows.
 */
CmcClass189810::CmcClass189810(CmcClass18AFB0* card)
{
    func_0034C970();
    this->card = card;
}

/** @brief Destroy the aggregate and the container. */
LibClass172320::~LibClass172320()
{
}

/** @brief Destroy the panel. */
LibClass1722E0::~LibClass1722E0()
{
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass1746A0::~ItemCreationClass1746A0()
{
}

/** @brief Release the widget storage and destroy its base. */
LibListIndicator::~LibListIndicator()
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

/**
 * @brief Store the transform receiver's halfword code.
 * @param object Transform receiver.
 * @param value Code to store.
 */
void func_0034CF80(LibCallbackTransform* object, u16 value)
{
    object->type_id = value;
}

/** @brief Initialize the container and the widget aggregate. */
LibClass172320::LibClass172320()
{
}

/** @brief Destroy the list head node and list receiver. */
LibListReceiver::~LibListReceiver()
{
}

#include "overlays/lib/marker_widget_inlines.h"
#include "overlays/lib/scalar_indicator_inlines.h"
#include "overlays/lib/movement_widget_inlines.h"
#include "overlays/lib/list_indicator_inlines.h"
#include "overlays/lib/resource_widget_inlines.h"

/** @brief Initialize the panel. */
LibClass1722E0::LibClass1722E0()
{
    unk38 = 2;
}

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
    panel.needs_redraw = 1;
    first_text.unk18.unk00 = 22.0f + x;
    text_y = 8.0f + y;
    first_text.unk18.unk04 = text_y;
    first_text.needs_redraw = 1;
    value_x = 160.0f + x;
    string_widget.unk18.unk00 = value_x;
    string_widget.unk18.unk04 = text_y;
    string_widget.needs_redraw = 1;
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
            numbers[0].needs_redraw = 1;
            break;
        case 1:
            numbers[1].unk18.unk00 = second_number_x;
            numbers[1].unk18.unk04 = number_y;
            numbers[1].needs_redraw = 1;
            break;
        case 2:
            numbers[2].unk18.unk00 = third_number_x;
            numbers[2].unk18.unk04 = number_y;
            numbers[2].needs_redraw = 1;
            break;
        case 3:
            numbers[3].unk18.unk00 = fourth_number_x;
            numbers[3].unk18.unk04 = number_y;
            numbers[3].needs_redraw = 1;
            break;
        case 4:
            numbers[4].unk18.unk00 = fifth_number_x;
            numbers[4].unk18.unk04 = number_y;
            numbers[4].needs_redraw = 1;
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
            array_text[0].needs_redraw = 1;
            break;
        case 1:
            array_text[1].unk18.unk00 = second_array_x;
            array_text[1].unk18.unk04 = array_y;
            array_text[1].needs_redraw = 1;
            break;
        }

        array_index++;
    } while (array_index < 2);

    second_text.unk18.unk00 = value_x;
    second_text.unk18.unk04 = number_y;
    second_text.needs_redraw = 1;
    fourth_text.unk18.unk00 = 140.0f + x;
    fourth_text.unk18.unk04 = text_y;
    fourth_text.needs_redraw = 1;
    third_text.unk18.unk00 = 472.0f + x;
    third_text.unk18.unk04 = text_y;
    third_text.needs_redraw = 1;
}

/**
 * @brief Refresh the row text, duration digits, colors, and visibility flags.
 * @param owner Containing row list.
 * @param index Signed row index.
 */
void CmcClass189900::refresh_row(void* owner, s32 index)
{
    FieldDuration duration;
    CmcClass189810* list = static_cast<CmcClass189810*>(owner);
    CmcRowRecord* record;
    u32 source = list->resource_source;
    lib_text_set_resource(&first_text, source, index + 2801, 0);
    record = list->func_0034BB50(static_cast<u16>(index));

    if (unk04 == 3)
    {
        string_widget.text = &record->display_text;
        string_widget.needs_redraw = 1;
        duration.set_seconds(record->elapsed_seconds);
        numbers[0].numeric_value = duration.hour_digit(0);
        numbers[0].needs_redraw = 1;
        numbers[1].numeric_value = duration.minute_digit(2);
        numbers[1].needs_redraw = 1;
        numbers[2].numeric_value = duration.minute_digit(1);
        numbers[2].needs_redraw = 1;
        numbers[3].numeric_value = duration.second_digit(2);
        numbers[3].needs_redraw = 1;
        numbers[4].numeric_value = duration.second_digit(1);
        numbers[4].needs_redraw = 1;
        lib_text_set_resource(&second_text, source, record->text_resource_key + 1, 0);

        if (record->unk7d == 1)
        {
            third_text.unk3d = 1;
        }
    }
    else if (unk04 == 5)
    {
        lib_text_set_resource(&fourth_text, source, 9021, 0);
        fourth_text.tint = 0x505050;
        fourth_text.needs_redraw = 1;
    }
    else if (unk04 == 6)
    {
        lib_text_set_resource(&fourth_text, source, 9022, 0);
        fourth_text.tint = 0x505050;
        fourth_text.needs_redraw = 1;
    }
    else if (unk04 == 2)
    {
        lib_text_set_resource(&fourth_text, source, 9023, 0);

        if (unk05)
        {
            fourth_text.tint = 0x808080;
            fourth_text.needs_redraw = 1;
        }
        else
        {
            fourth_text.tint = 0x505050;
            fourth_text.needs_redraw = 1;
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
inline LibStringLabel::~LibStringLabel()
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
u8 CmcClass189920::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
u8 CmcClass189920::func_slotb0()
{
    FieldClass15AE70::func_slot18(0, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when either widget couldn't be allocated, otherwise one.
 */
s32 CmcClass189920::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 60.0f, 216.0f, 5);
    LibPanel* panel = new (0) LibPanel;
    unkac = new (0) LibTextWidget;

    if (panel == 0 || unkac == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 552.0f, 112.0f, 88.0f);
    unk14.append(panel);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(unkac, static_cast<s32>(associated), 0x535, 0, 20.0f, 20.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, unkac);
    unk2c.append(unkac);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189920::~CmcClass189920()
{
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
u8 CmcClass189A20::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
u8 CmcClass189A20::func_slotb0()
{
    func_slot18(0, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when either widget couldn't be allocated, otherwise one.
 */
s32 CmcClass189A20::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 56.0f, 220.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 528.0f, 144.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    unk14.append(panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x50F, 0, 20.0f, 20.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189A20::~CmcClass189A20()
{
}

/** @brief Open the save window for the selected slot and restart the card handler with the slot and card kind. */
void CmcClass189B20::func_0034E230()
{
    CmcClass18A520* window = new (0) CmcClass18A520;

    if (window == 0)
    {
        return;
    }

    window->func_slotf4(func_slot54());
    window->func_slot40(func_slot44());
    D_001B643C->unk10->unk14->add_child(window);
    D_001B643C->unk10->unk14->func_00263C70(window);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232C);

    if (unka8 != 0)
    {
        unka8->unk18->unk1008 = 0;
        func_002EEE20(unka8->unk18, slot, kind);
        unka8->unk48 = unkd0;
        unka8->func_0035AF60(0x40);
        unka8->func_0035ADA0(0, 1);
    }
}

/**
 * @brief Open the result window for the selected card slot, close the slot list for card kinds two to four and close this window.
 * @return Zero when the result window couldn't be allocated, otherwise one.
 */
s32 CmcClass189B20::func_0034E3B0()
{
    CmcClass189920* window = new (0) CmcClass189920;

    if (window == 0)
    {
        return 0;
    }

    s16 selected = unka8->selected;
    window->func_slotf4(func_slot54());
    window->unka8 = selected;

    if (window->unkac != 0)
    {
        switch (window->unka8)
        {
        case 0:
            lib_text_set_resource(window->unkac, window->func_slot54(), 0x535, 0);
            break;
        case 1:
            lib_text_set_resource(window->unkac, window->func_slot54(), 0x536, 0);
            break;
        }

        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
    }

    window->func_slot40(static_cast<FieldClass15AE70*>(func_slot44())->func_slot44());
    D_001B643C->unk10->unk14->func_00263C70(window);
    D_001B643C->unk10->unk14->add_child(window);
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(0, 0x7F);

    switch (kind)
    {
    case 2:
    case 3:
    {
        // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
        CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

        if (parent->list != 0)
        {
            parent->list->unkab = 0;
            static_cast<LibCallbackTransform&>(*parent->list).destroy();
            parent->list = 0;
        }

        break;
    }
    case 4:
    {
        CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

        if (parent->list != 0)
        {
            parent->list->unkab = 0;
            static_cast<LibCallbackTransform&>(*parent->list).destroy();
            parent->list = 0;
        }

        break;
    }
    }

    FieldWindowRemovalContext* context = reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10);
    field_queue_window_removal(context, static_cast<FieldClass15AE70*>(func_slot44()));
    CmcClass18AF20* controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

    if (controller != 0)
    {
        controller->unk44->func_slot20(0);
    }

    func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    return 1;
}

/** @brief Once this is the focused window, recolour the choices for the grid's cursor and finish when the card handler is done. */
void CmcClass189B20::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (unka8 == 0)
    {
        return;
    }

    switch (grid->unk114)
    {
    case 0:
        first_text->set_tint(0x288080);
        second_text->set_tint(0x808080);

        if (marker != 0)
        {
            marker->func_0023B7E0(first_text);
        }

        break;
    case 1:
        first_text->set_tint(0x808080);
        second_text->set_tint(0x288080);

        if (marker != 0)
        {
            marker->func_0023B7E0(second_text);
        }

        break;
    default:
        first_text->set_tint(0x808080);
        second_text->set_tint(0x808080);
        break;
    }

    if (unka8->unk38 == 1)
    {
        unkdc = 1;
        func_0034E3B0();
    }
}

/** @brief Move the grid in direction two. */
void CmcClass189B20::func_slot74()
{
    if (grid->process_direction(2) != 1)
    {
        return;
    }
}

/** @brief Move the grid in direction three. */
void CmcClass189B20::func_slot70()
{
    if (grid->process_direction(3) != 1)
    {
        return;
    }
}

/**
 * @brief Close the window, restore its parent and set the alternate window's text unless input is locked.
 * @return Zero while locked, otherwise two.
 */
u8 CmcClass189B20::func_slotb4()
{
    if (unkdc == 1)
    {
        return 0;
    }

    func_slot18(0, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232B);
    unka8->func_0035ADA0(0, 1);
    return 2;
}

/** @brief Start with no card handler and the runtime's controller. */
inline CmcClass18A420::CmcClass18A420() : unka8(0), unkac(0)
{
    unkac = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);
}

/**
 * @brief On the first choice act for the window's mode and restart the card handler, otherwise act like func_slotb4.
 * @return Zero without a handler or while locked, two when func_slotb4 handled it, otherwise one.
 */
u8 CmcClass189B20::func_slotb0()
{
    if (unka8 == 0)
    {
        return 0;
    }

    if (unkdc == 1)
    {
        return 0;
    }

    s32 result = 0;

    if (grid->unk114 == 0)
    {
        switch (mode)
        {
        case 0:
            func_0034E230();
            break;
        case 1:
        {
            CmcClass18A420* window = new (0) CmcClass18A420;

            if (window == 0)
            {
                break;
            }

            window->func_slotf4(func_slot54());
            window->func_slot40(func_slot44());
            D_001B643C->unk10->unk14->add_child(window);
            D_001B643C->unk10->unk14->func_00263C70(window);
            static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232D);

            if (unka8 != 0)
            {
                func_002EF030(unka8->unk18, slot);
                unka8->unk18->unk1009 = 0;
                unka8->func_0035AF60(0x30);
                unka8->func_0035ADA0(0, 1);
            }

            break;
        }
        }

        func_slot18(0, 0x7F);
        field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    }
    else
    {
        result = func_slotb4();
    }

    unka8->func_0035ADA0(0, 1);
    u8 status;

    if (static_cast<u8>(result) == 0)
    {
        status = 1;
    }
    else
    {
        status = 2;
    }

    return status;
}

/**
 * @brief Create the panels, texts and the choice grid.
 * @param associated Full resource source word.
 * @return One on success.
 */
s32 CmcClass189B20::func_slotf8(u32 associated)
{
    unka8 = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (mode == 5 || kind == 5 || unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 160.0f, 160.0f, 15);
    LibPanel* header = new (0) LibPanel;
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* title = new (0) LibTextWidget;
    LibTextWidget* message = new (0) LibTextWidget;
    first_text = new (0) LibTextWidget;
    second_text = new (0) LibTextWidget;
    grid = new (0) FieldObject23CEA0;

    if (header == 0 || panel == 0 || title == 0 || message == 0 || first_text == 0 || second_text == 0 || grid == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 320.0f, 216.0f, 88.0f);
    unk14.append(panel);
    lib_container_attach_widget(unk10, panel);
    lib_panel_init_rectangle(header, 0, 0.0f, 0.0f, 320.0f, 56.0f, 88.0f);
    lib_panel_set_colors(header, &colors);
    unk14.append(header);
    lib_container_attach_widget(unk10, header);

    switch (mode)
    {
    case 0:
        title->init_resource_rectangle(0.0f, 16.0f, 320.0f, 24.0f, associated, 0x52D, 1);
        title->set_horizontal_align(1);
        break;
    case 1:
        title->init_resource_rectangle(0.0f, 16.0f, 320.0f, 24.0f, associated, 0x52E, 1);
        title->set_horizontal_align(1);
        break;
    }

    lib_container_attach_widget(unk10, title);
    unk2c.append(title);
    unkd0 = 0;

    switch (kind)
    {
    case 2:
        message->init_resource_rectangle(0.0f, 80.0f, 320.0f, 24.0f, associated, 0x52A, 0);
        message->set_horizontal_align(1);
        unkd0 = 1;
        break;
    case 3:
        message->init_resource_rectangle(80.0f, 72.0f, 0.0f, 0.0f, associated, 0x52B, 0);
        break;
    case 4:
        message->init_resource_rectangle(0.0f, 80.0f, 320.0f, 24.0f, associated, 0x52C, 0);
        message->set_horizontal_align(1);
        break;
    }

    lib_container_attach_widget(unk10, message);
    unk2c.append(message);
    first_text->init_resource_rectangle(84.0f, 168.0f, 0.0f, 0.0f, associated, 0x52F, 0);
    second_text->init_resource_rectangle(196.0f, 168.0f, 0.0f, 0.0f, associated, 0x530, 0);
    lib_container_attach_widget(unk10, first_text);
    unk2c.append(first_text);
    first_text->set_tint(0x808080);
    lib_container_attach_widget(unk10, second_text);
    unk2c.append(second_text);
    // TODO: the game tints first_text a second time here; second_text was probably meant
    first_text->set_tint(0x808080);
    grid->func_0023CE80(2, 1);
    grid->func_0023CE60(112.0f, 0.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(1, 244.0f, 328.0f);
    unk74.append(grid);
    marker = new (0) FieldClass153170;
    marker->func_0023B850(second_text, 0x288080);
    lib_container_attach_widget(unk10, marker);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2337);
    return 1;
}

/**
 * @brief Check whether a kind value is one of the card kinds two to four.
 * @param kind Kind value.
 * @return One for kinds two to four, otherwise zero.
 */
static inline u8 cmc_is_card_kind(s8 kind)
{
    switch (kind)
    {
    case 2:
    case 3:
    case 4:
        return 1;
    }

    return 0;
}

/**
 * @brief Store the mode and card kind, then create the window.
 * @param associated Full resource source word.
 * @param mode Window mode.
 * @param kind Card kind; anything outside two to four becomes five.
 * @return func_slotf8's result.
 */
s32 CmcClass189B20::func_slotf4(u32 associated, u8 mode, s8 kind)
{
    this->mode = mode;

    if (cmc_is_card_kind(kind) == 1)
    {
        this->kind = kind;
    }
    else
    {
        this->kind = 5;
    }

    return func_slotf8(associated);
}

/** @brief Clear the window's state and set its default mode, card kind and colours. */
void CmcClass189B20::func_0034F310()
{
    unka8 = 0;
    grid = 0;
    mode = 1;
    unkb2 = -1;
    slot = -1;
    kind = 5;
    first_text = 0;
    second_text = 0;
    colors.values[0] = 0x101080;
    colors.values[1] = 0x101080;
    colors.values[2] = 0x101080;
    colors.values[3] = 0x101080;
    unkd0 = 0;
    unkd4 = 0;
    marker = 0;
    unkdc = 0;
}

/** @brief Destroy the window. */
CmcClass189B20::~CmcClass189B20()
{
}

/**
 * @brief Release nested window displays and unregister the window.
 */
void CmcClass189C20::func_slot0c()
{
    FieldClass15AE70::func_slot0c();
}

/**
 * @brief Hide the eight displays, then show one per nonzero code in a save entry's code list.
 * @param codes Eight resource codes; zero entries are skipped.
 * @param show Zero to only hide the displays.
 * @return Zero when showing without a code list, otherwise one.
 */
s32 CmcClass189C20::func_0034F3F0(const u8* codes, u8 show)
{
    for (s32 index = 0; index < 8; index++)
    {
        if (displays[index] != 0)
        {
            displays[index]->visible = 0;
        }
    }

    if (show == 0)
    {
        return 1;
    }

    if (codes == 0)
    {
        return 0;
    }

    s32 code_index;
    s32 shown;

    for (code_index = 0, shown = 0; shown < 8; code_index++)
    {
        if (code_index == 8)
        {
            break;
        }

        s32 code = codes[code_index];

        if (code != 0)
        {
            void* allocation;

            if (code < 0x10)
            {
                allocation = field_get_aligned_allocation(D_001B643C->slots, code);
            }
            else
            {
                code = static_cast<u8>(code + 0x20);
                allocation = field_get_aligned_allocation(D_001B643C->slots, code);
            }

            FieldResourceRecord* record = static_cast<FieldResourceRecord*>(field_get_builtin_resource_data(D_001B643C->slots, static_cast<u8>(code)));
            displays[shown]->func_002D5CF0(allocation, record, code);
            displays[shown]->visible = 1;
            shown++;
        }
    }

    return 1;
}

/**
 * @brief Create the eight option resource displays in a row and the resource text below them.
 * @param associated Full resource source word.
 * @return One.
 */
s32 CmcClass189C20::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 40.0f, 76.0f, 17);
    void* allocation = field_get_aligned_allocation(D_001B643C->slots, 1);
    FieldResourceRecord* record = static_cast<FieldResourceRecord*>(field_get_builtin_resource_data(D_001B643C->slots, 1));

    for (s32 index = 0; index < 8; index++)
    {
        displays[index] = new (0) ItemCreationOptionResourceDisplay;
        displays[index]->unkcc = allocation;
        displays[index]->unkd0 = 1;
        displays[index]->func_002D6440(72.0f * index - 8.0f, 326.0f, record);
        displays[index]->visible = 0;
        lib_container_attach_widget(unk10, displays[index]);
    }

    unkc8 = new (0) LibTextWidget;
    lib_text_init_resource_rectangle(unkc8, static_cast<s32>(associated), 0x510, 0, 128.0f, 480.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, unkc8);
    unkc8->visible = 0;
    return 1;
}

/** @brief Release the widget storage and destroy its base. */
ItemCreationClass175110::~ItemCreationClass175110()
{
}

/** @brief Destroy the window. */
CmcClass189C20::~CmcClass189C20()
{
}

/** @brief Close the slot list and this window and open the result window for the selected card slot. */
void CmcClass189D20::func_0034F830()
{
    if (list != 0)
    {
        list->unkab = 0;
        static_cast<LibCallbackTransform&>(*list).destroy();
        list = 0;
    }

    func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
    CmcClass189920* window = new (0) CmcClass189920;

    if (window == 0)
    {
        return;
    }

    window->func_slotf4(func_slot54());
    window->func_slot40(func_slot44());
    window->unka8 = unkac->selected;

    if (window->unkac != 0)
    {
        switch (window->unka8)
        {
        case 0:
            lib_text_set_resource(window->unkac, window->func_slot54(), 0x535, 0);
            break;
        case 1:
            lib_text_set_resource(window->unkac, window->func_slot54(), 0x536, 0);
            break;
        }

        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
    }

    D_001B643C->unk10->unk14->func_00263C70(window);
    D_001B643C->unk10->unk14->add_child(window);

    if (unka8 != 0 && unka8->unk44 != 0)
    {
        unka8->unk44->func_slot20(0);
    }

    unkb6 = 3;
    unkc0 = 1;
}

/** @brief Once this is the focused window, follow the memory card handler's progress. */
void CmcClass189D20::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (unkb6 == 3)
    {
        return;
    }

    if (unkc1 != 0)
    {
        if (list != 0)
        {
            list->cancel();
        }

        unkc1 = 0;
    }

    if (unkac->unk38 == 1 && unkc0 == 0)
    {
        func_0034F830();
        return;
    }

    switch (unkb6)
    {
    case 0:
        break;
    case 1:
    {
        if (list == 0)
        {
            unkb6 = 3;
            break;
        }

        u8 state;
        s32 position = list->cursor();
        s32 index = position - 1;

        if (unkbc != index && list->unk5d5 != 0)
        {
            CmcClass189C20* codes = static_cast<CmcClass189C20*>(unkb8);

            if (codes != 0 && list != 0)
            {
                CmcRowRecord* record = list->entry(static_cast<u16>(index));

                if (record != 0)
                {
                    codes->func_0034F3F0(record->codes, 1);
                }
                else
                {
                    codes->func_0034F3F0(0, 0);
                }
            }

            unkbc = index;
        }

        bool idle = list->in_state(0);

        if (idle)
        {
            if (list->unk30c > 0)
            {
                CmcClass188DA0* row = static_cast<CmcClass188DA0*>(list->rows[static_cast<u16>(static_cast<u16>(index) - static_cast<u16>(list->unk304))]);
                state = 6;

                if (row != 0)
                {
                    state = row->unk04;
                }

                switch (state)
                {
                case 5:
                case 6:
                    resident_sound_play(g_sound, 3, 0, 0, 0x7F, 0x40, 0);
                    list->cancel();
                    break;
                case 3:
                case 2:
                {
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                    unkc1 = 1;

                    if (unkac->func_0035AF80() == 0)
                    {
                        CmcClass18A920* window = new (0) CmcClass18A920;

                        if (window == 0)
                        {
                            break;
                        }

                        window->unkb8 = position;
                        window->func_slotf4(func_slot54());
                        window->func_slot40(this);
                        D_001B643C->unk10->unk14->func_00263C70(window);
                        D_001B643C->unk10->unk14->add_child(window);
                        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2337);
                        unkac->func_0035ADA0(0, 1);
                        break;
                    }

                    CmcClass189B20* window = new (0) CmcClass189B20;
                    u8 created;

                    // TODO: the cast stops the compare reusing the switch's value
                    if (static_cast<u8>(state) == 2)
                    {
                        created = window->func_slotf4(func_slot54(), 0, 2);
                        window->slot = position;
                    }
                    else
                    {
                        created = window->func_slotf4(func_slot54(), 0, 3);
                        window->slot = position;
                    }

                    if (window != 0 && created != 0)
                    {
                        window->func_slot40(this);
                        D_001B643C->unk10->unk14->add_child(window);
                        D_001B643C->unk10->unk14->func_00263C70(window);
                    }

                    break;
                }
                }
            }
            else
            {
                list->unkab = 0;
                static_cast<LibCallbackTransform&>(*list).destroy();
                list = 0;
                unkb6 = 2;
            }
        }

        break;
    }
    case 2:
        if (unkb8 != 0)
        {
            unkb8->func_slot20(0);
        }

        unka8->unk4c->unkD5 = 0;
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2329);
        static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
        FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
        callbacks->func_00263C70(func_slot44());
        field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
        unkb6 = 3;
        break;
    case 3:
        break;
    }
}

/**
 * @brief Create the save slot list for the card handler, show the controller's slot window and open the frame.
 * @param associated Full resource source word.
 * @return Zero when something is missing or the list already exists, otherwise one.
 */
s32 CmcClass189D20::func_slotf4(u32 associated)
{
    unka8 = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

    if (unka8 == 0)
    {
        return 0;
    }

    unkac = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (unkac == 0)
    {
        return 0;
    }

    if (unkb4 < 0)
    {
        return 0;
    }

    unkb8 = unka8->unk44;

    if (unkb8 != 0)
    {
        unkb8->func_slot20(1);
    }

    if (unkb6 == 0 && list == 0)
    {
        list = new (0) CmcClass189810(unkac);
        list->unk4c2 = 1;
        list->set_slot_limit(unkb4, unkc2);
        list->func_0034C5D0(associated, 0x2D, 0);
        lib_queue_display_object(g_field_runtime, list);
        unkb6 = 1;
    }
    else
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 64.0f, 64.0f, 20);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189D20::~CmcClass189D20()
{
}

/** @brief Close the slot list and this window and open the result window for the selected card slot. */
void CmcClass189E20::func_00350260()
{
    if (list != 0)
    {
        list->unkab = 0;
        static_cast<LibCallbackTransform&>(*list).destroy();
        list = 0;
    }

    func_slot20(0);
    func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);

    if (unka8 != 0 && unka8->unk44 != 0)
    {
        unka8->unk44->func_slot20(0);
    }

    CmcClass189920* window = new (0) CmcClass189920;

    if (window == 0)
    {
        return;
    }

    s16 selected = unkac->selected;
    window->func_slotf4(func_slot54());
    window->unka8 = selected;

    if (window->unkac != 0)
    {
        switch (window->unka8)
        {
        case 0:
            lib_text_set_resource(window->unkac, window->func_slot54(), 0x535, 0);
            break;
        case 1:
            lib_text_set_resource(window->unkac, window->func_slot54(), 0x536, 0);
            break;
        }

        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
    }

    window->func_slot40(func_slot44());
    D_001B643C->unk10->unk14->func_00263C70(window);
    D_001B643C->unk10->unk14->add_child(window);
    unkb6 = 3;
    unkc0 = 1;
}

/** @brief Once this is the focused window, follow the memory card handler's progress. */
void CmcClass189E20::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (unkb6 == 3)
    {
        return;
    }

    if (unkc1 != 0 && unkb6 == 1)
    {
        if (list != 0)
        {
            list->cancel();
        }

        unkc1 = 0;
    }

    if (unkac->unk38 == 1 && unkc0 == 0)
    {
        func_00350260();
        return;
    }

    switch (unkb6)
    {
    case 0:
        break;
    case 1:
    {
        if (list == 0)
        {
            unkb6 = 3;
            break;
        }

        s16 found;
        u8 state;
        s32 position = list->cursor();
        s32 index = position - 1;

        if (unkbc != index && list->unk5d5 != 0)
        {
            CmcClass189C20* codes = static_cast<CmcClass189C20*>(unkb8);

            if (codes != 0 && list != 0)
            {
                CmcRowRecord* record = list->entry(static_cast<u16>(index));

                if (record != 0)
                {
                    codes->func_0034F3F0(record->codes, 1);
                }
                else
                {
                    codes->func_0034F3F0(0, 0);
                }
            }

            unkbc = index;
        }

        bool idle = list->in_state(0);

        if (idle)
        {
            if (list->unk30c > 0)
            {
                CmcClass188DA0* row = static_cast<CmcClass188DA0*>(list->rows[static_cast<u16>(static_cast<u16>(index) - static_cast<u16>(list->unk304))]);
                state = 6;

                if (row != 0)
                {
                    state = row->unk04;
                }

                switch (state)
                {
                case 5:
                case 6:
                case 2:
                    resident_sound_play(g_sound, 3, 0, 0, 0x7F, 0x40, 0);
                    list->cancel();
                    break;
                case 3:
                {
                    resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
                    unkc1 = 1;
                    index = 0;
                    CmcClass189810* slots = list;
                    s32 wanted = static_cast<u16>(position);
                    s32 result = -1;

                    for (; index < 0x2D; index++)
                    {
                        if (slots->unk5a8[index] == wanted)
                        {
                            result = index;
                            break;
                        }
                    }

                    found = static_cast<s8>(result);

                    if (static_cast<u8>(state) == 3 && found != -1)
                    {
                        CmcClass189B20* window = new (0) CmcClass189B20;
                        u8 created = window->func_slotf4(func_slot54(), 1, 4);

                        if (window != 0 && created != 0)
                        {
                            window->func_slot40(this);
                            window->slot = found;
                            D_001B643C->unk10->unk14->add_child(window);
                            D_001B643C->unk10->unk14->func_00263C70(window);
                        }
                    }

                    break;
                }
                }
            }
            else
            {
                list->unkab = 0;
                static_cast<LibCallbackTransform&>(*list).destroy();
                list = 0;
                unkb6 = 2;
            }
        }

        break;
    }
    case 2:
        if (unkb8 != 0)
        {
            unkb8->func_slot20(0);
        }

        unka8->unk4c->unkD5 = 0;
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2329);
        static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
        FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
        callbacks->func_00263C70(func_slot44());
        field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
        unkb6 = 3;
        break;
    case 3:
        break;
    }
}

/**
 * @brief Create the save slot list for the card handler, show the controller's slot window and open the frame.
 * @param associated Full resource source word.
 * @return Zero when something is missing or the list already exists, otherwise one.
 */
s32 CmcClass189E20::func_slotf4(u32 associated)
{
    unka8 = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

    if (unka8 == 0)
    {
        return 0;
    }

    unkac = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (unkac == 0)
    {
        return 0;
    }

    if (unkb4 < 0)
    {
        return 0;
    }

    unkb8 = unka8->unk44;

    if (unkb8 != 0)
    {
        unkb8->func_slot20(1);
    }

    if (unkb6 == 0 && list == 0)
    {
        list = new (0) CmcClass189810(unkac);
        list->unk4c2 = 0;
        list->set_slot_limit(unkb4, unkc2);
        list->func_0034C5D0(associated, 0x2D, 0);
        lib_queue_display_object(g_field_runtime, list);
        unkb6 = 1;
    }
    else
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 64.0f, 64.0f, 20);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189E20::~CmcClass189E20()
{
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
u8 CmcClass189F20::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
u8 CmcClass189F20::func_slotb0()
{
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when either widget couldn't be allocated, otherwise one.
 */
s32 CmcClass189F20::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 48.0f, 200.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 532.0f, 102.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x527, 0, 16.0f, 18.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text);
    return 1;
}

/** @brief Destroy the window. */
CmcClass189F20::~CmcClass189F20()
{
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
u8 CmcClass18A020::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
u8 CmcClass18A020::func_slotb0()
{
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when either widget couldn't be allocated, otherwise one.
 */
s32 CmcClass18A020::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 60.0f, 216.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 520.0f, 120.0f, 88.0f);
    unk14.append(panel);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x511, 0, 24.0f, 24.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    return 1;
}

/** @brief Destroy the window. */
CmcClass18A020::~CmcClass18A020()
{
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
u8 CmcClass18A120::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Close this window, then either finish the card menu or reopen the slot window's request after closing the parent's slot list.
 * @return One.
 */
u8 CmcClass18A120::func_slotb0()
{
    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2335);

    if (unka8->unk54 == 0)
    {
        // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
        CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

        if (parent->list != 0)
        {
            parent->list->unkab = 0;
            static_cast<LibCallbackTransform&>(*parent->list).destroy();
            parent->list = 0;
        }

        parent->func_slot24(1);
        parent->set_state(0xFF, 0x40);
        parent->func_slot20(0);
        parent->unkb6 = 3;
        D_001B643C->unk10->unk14->func_00263C70(parent);
        CmcClass18AF20* controller = unka8;

        if (controller != 0)
        {
            if (controller->unk50 == 0)
            {
                controller->func_003583B0();
            }
            else
            {
                func_0020F230(field_display(), 0, 0, 0x80000000, 0, 0, 0, 10.0f, 0.0f, 0.0f);
                FieldScreenTransition* transition;
                (transition = field_display()->effects.transition)->depth = D_001B6694;
                transition->unkf0 = 10;
                CmcMenuState* menu = D_001B643C->unk0c;
                menu->unk9d = 0;
                menu->unk9e = 1;
            }
        }
    }
    else
    {
        // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
        CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

        if (parent->list != 0)
        {
            parent->list->unkab = 0;
            static_cast<LibCallbackTransform&>(*parent->list).destroy();
            parent->list = 0;
        }

        parent->func_slot20(0);
        parent->unkb6 = 3;
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2332);
        unka8->dispatch_window_request();
    }

    if (unka8 != 0 && unka8->unk4c != 0)
    {
        CmcClass18AD20* display = unka8->unk4c;

        if (display->unkAc != 0)
        {
            display->unkAc->visible = 0;
        }

        if (display->unkB0 != 0)
        {
            display->unkB0->visible = 0;
        }

        if (display->unkD0 != 0)
        {
            display->unkD0->visible = 0;
        }
    }

    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when a required object is missing, otherwise one.
 */
s32 CmcClass18A120::func_slotf4(u32 associated)
{
    unka8 = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);
    unkac = reinterpret_cast<void*>(D_001B643C->unk10->unk14->func_slot64());

    if (unkac == 0 || unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 168.0f, 236.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 304.0f, 76.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    unk14.append(panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x2341, 0, 0.0f, 24.0f, 304.0f, 24.0f);
    text->set_horizontal_align(1);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    return 1;
}

/** @brief Destroy the window and its Field parent. */
CmcClass18A120::~CmcClass18A120()
{
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
u8 CmcClass18A220::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, queue this window, and set the alternate window text key.
 * @return One.
 */
u8 CmcClass18A220::func_slotb0()
{
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(9001);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when either widget couldn't be allocated, otherwise one.
 */
s32 CmcClass18A220::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 60.0f, 216.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 520.0f, 120.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    unk14.append(panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x510, 0, 24.0f, 24.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    return 1;
}

/** @brief Destroy the window. */
CmcClass18A220::~CmcClass18A220()
{
}

/** @brief Open the result window for the selected card slot, then close the slot list and its window and this window. */
void CmcClass18A320::func_003519B0()
{
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;

    if (callbacks != 0)
    {
        CmcClass189920* window = new (0) CmcClass189920;

        if (window != 0)
        {
            window->func_slotf4(func_slot54());
            window->unka8 = reinterpret_cast<CmcClass18AFB0*>(callbacks->func_slot60())->selected;

            if (window->unkac != 0)
            {
                switch (window->unka8)
                {
                case 0:
                    lib_text_set_resource(window->unkac, window->func_slot54(), 0x535, 0);
                    break;
                case 1:
                    lib_text_set_resource(window->unkac, window->func_slot54(), 0x536, 0);
                    break;
                }

                static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
            }

            window->func_slot40(static_cast<FieldClass15AE70*>(func_slot44())->func_slot44());
            D_001B643C->unk10->unk14->add_child(window);
            static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
            D_001B643C->unk10->unk14->func_00263C70(window);
        }
    }

    // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
    CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

    if (parent->unkb8 != 0)
    {
        parent->unkb8->func_slot20(0);
    }

    if (parent->list != 0)
    {
        parent->list->unkab = 0;
        static_cast<LibCallbackTransform&>(*parent->list).destroy();
        parent->list = 0;
    }

    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), parent);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
}

/** @brief Once this is the focused window and the card handler finished, lock the window and finish it. */
void CmcClass18A320::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60())->unk38 == 1)
    {
        unkac = 1;
        func_003519B0();
        return;
    }
}

/**
 * @brief Run the window action when its guard byte is clear.
 * @return Zero when guarded, otherwise one after running the action.
 */
u8 CmcClass18A320::func_slotb4()
{
    if (unkac != 0)
    {
        return 0;
    }

    func_slotb0();
    return 1;
}

/**
 * @brief Unless locked, store the card's record back into the Field object, refresh the slot list, restore the parent, and close the parent too when the controller asks for it.
 * @return Zero while locked, otherwise one.
 */
u8 CmcClass18A320::func_slotb0()
{
    if (unkac != 0)
    {
        return 0;
    }

    CmcClass18AFB0* card = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());
    FieldClass15B9C0* field = 0;

    if (card != 0)
    {
        field = card->unk18;
        card->func_0035ADA0(0, 1);
    }

    if (field != 0)
    {
        FieldClass15B9C0Record* copy;
        FieldClass15B9C0Record* record = field->unk180;

        if (record != 0)
        {
            func_002F0D90(field, record);
            copy = new (0) FieldClass15B9C0Record;
            memset_guess(copy, 0, 0x80);
            memcpy_guess(copy, record, 0x80);
            func_002EDEC0(field, copy);
            func_002EDFA0(field);
            unka8->unk48 = func_002EE9B0(field);
            // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
            static_cast<CmcClass189D20*>(func_slot44())->list->func_0034C460();
        }
    }

    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    u8 closed = 0;

    if (unka8 != 0 && unka8->unk80 == 1)
    {
        // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
        CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

        if (parent->list != 0)
        {
            parent->list->unkab = 0;
            static_cast<LibCallbackTransform&>(*parent->list).destroy();
            parent->list = 0;
        }

        if (parent->unkb8 != 0)
        {
            parent->unkb8->func_slot20(0);
        }

        parent->unka8->unk4c->unkD5 = 0;
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2329);
        static_cast<FieldClass15AE70*>(parent->func_slot44())->func_slot18(1, 0x7F);
        FieldClass153E30* parent_callbacks = D_001B643C->unk10->unk14;
        parent_callbacks->func_00263C70(parent->func_slot44());
        field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), parent);
        parent->unkb6 = 3;
        closed = 1;
    }

    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);

    if (closed == 0)
    {
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232B);
    }

    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when a required object is missing, otherwise one.
 */
s32 CmcClass18A320::func_slotf4(u32 associated)
{
    unka8 = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

    if (unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 160.0f, 240.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 320.0f, 72.0f, 88.0f);
    unk14.append(panel);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x517, 0, 0.0f, 24.0f, 320.0f, 24.0f);
    text->set_horizontal_align(1);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    return 1;
}

/** @brief Destroy the window and its Field parent. */
CmcClass18A320::~CmcClass18A320()
{
}

/**
 * @brief Open the save result window, optionally closing the parent's slot list, and close this window.
 * @param close_parent One to close the parent window and its slot list and attach to the controller's slot window.
 * @return One.
 */
s32 CmcClass18A420::func_00352230(u8 close_parent)
{
    CmcClass18A020* window = new (0) CmcClass18A020;
    CmcClass18AF20* controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

    if (close_parent == 1)
    {
        // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
        CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

        if (parent != 0)
        {
            if (parent->list != 0)
            {
                parent->list->unkab = 0;
                static_cast<LibCallbackTransform&>(*parent->list).destroy();
                parent->list = 0;
            }

            parent->func_slot20(0);
            parent->unkb6 = 3;
            field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), parent);
        }

        if (controller != 0)
        {
            window->func_slot40(controller->unk7c);
        }
    }
    else
    {
        window->func_slot40(func_slot44());
    }

    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    window->func_slotf4(func_slot54());
    D_001B643C->unk10->unk14->add_child(window);
    D_001B643C->unk10->unk14->func_00263C70(window);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);

    if (controller != 0)
    {
        controller->unk44->func_slot20(0);
    }

    return 1;
}

/** @brief Once this is the focused window, act on the memory card handler's result. */
void CmcClass18A420::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (unka8 == 0)
    {
        return;
    }

    CmcClass18AFB0* card;
    s32 code;
    s32 result;
    s32 first;
    s32 second;
    u8 closing = unkac->get_unk50();

    if (unka8->unk38 == 1)
    {
        s32 first_result = unka8->unk58;
        s32 second_result = unka8->unk5c;

        if (first_result == -1)
        {
            func_00352230(1);
            return;
        }

        if (second_result == -1)
        {
            CmcClass18A120* window = new (0) CmcClass18A120;

            if (window != 0)
            {
                window->func_slotf4(func_slot54());
                window->func_slot40(func_slot44());
                static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);
                D_001B643C->unk10->unk14->add_child(window);
                D_001B643C->unk10->unk14->func_00263C70(window);
                FieldClass15AE70::func_slot18(0, 0x7F);
                field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
                CmcClass18AF20* controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

                if (controller != 0)
                {
                    controller->unk44->func_slot20(0);
                }
            }

            if (closing == 0)
            {
                unkac->unk54 = 0x75;
            }

            return;
        }
    }

    card = unka8;

    if (card->unk34 == 0)
    {
        return;
    }

    code = card->unk4c;
    result = card->unk30;
    first = card->unk58;
    second = card->get_unk5c();

    if (result == 0)
    {
        if (first == -1)
        {
            func_00352230(0);
            return;
        }

        CmcClass18A120* window = new (0) CmcClass18A120;

        if (window != 0)
        {
            window->func_slotf4(func_slot54());
            window->func_slot40(func_slot44());
            static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);
            D_001B643C->unk10->unk14->add_child(window);
            D_001B643C->unk10->unk14->func_00263C70(window);
            FieldClass15AE70::func_slot18(0, 0x7F);
            field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
            CmcClass18AF20* controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

            if (controller != 0)
            {
                controller->unk44->func_slot20(0);
            }
        }

        if (closing == 0)
        {
            request_error_window(code);
        }
    }
    else
    {
        if (first == -1)
        {
            func_00352230(1);
            return;
        }

            CmcClass18A120* window = new (0) CmcClass18A120;

            if (window != 0)
            {
                window->func_slotf4(func_slot54());
                window->func_slot40(func_slot44());
                static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);
                D_001B643C->unk10->unk14->add_child(window);
                D_001B643C->unk10->unk14->func_00263C70(window);
                FieldClass15AE70::func_slot18(0, 0x7F);
                field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
                CmcClass18AF20* controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

                if (controller != 0)
                {
                    controller->unk44->func_slot20(0);
                }
            }

        if (second == -1)
        {
            if (closing == 0)
            {
                unkac->unk54 = 0x75;
            }

            return;
        }

        if (closing == 0)
        {
            request_error_window(code);
        }

        return;
    }
}

/**
 * @brief Take the card handler, then create the frame, its panel and two resource texts.
 * @param associated Full resource source word.
 * @return Zero when the handler or a widget is missing, otherwise one.
 */
s32 CmcClass18A420::func_slotf4(u32 associated)
{
    unka8 = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 60.0f, 188.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* first = new (0) LibTextWidget;
    LibTextWidget* second = new (0) LibTextWidget;

    if (panel == 0 || first == 0 || second == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 532.0f, 164.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    first->init_resource_rectangle(16.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x532, 0);
    second->init_resource_rectangle(16.0f, 42.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x545, 0);
    lib_container_attach_widget(unk10, first);
    lib_container_attach_widget(unk10, second);
    unk2c.append(first);
    unk2c.append(second);
    return 1;
}

/** @brief Destroy the window. */
CmcClass18A420::~CmcClass18A420()
{
}

/** @brief Open the save confirmation window under the controller's slot window, close the parent's slot list and this window. */
void CmcClass18A520::func_00352D40()
{
    CmcClass18A220* window = new (0) CmcClass18A220;
    window->func_slotf4(func_slot54());
    CmcClass18AF20* controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);
    FieldClass15AE70* slots = 0;

    if (controller != 0)
    {
        slots = controller->unk7c;
        controller->unk44->func_slot20(0);
    }

    window->func_slot40(slots);
    D_001B643C->unk10->unk14->add_child(window);
    D_001B643C->unk10->unk14->func_00263C70(window);
    // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
    CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

    if (parent != 0)
    {
        if (parent->list != 0)
        {
            parent->list->unkab = 0;
            static_cast<LibCallbackTransform&>(*parent->list).destroy();
            parent->list = 0;
        }

        field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), parent);
    }

    lib_panel_detach(unkac);

    if (unkb0 != 0)
    {
        lib_object_detach_owner(unkb0);
        unkb0->destroy();
        unkb0 = 0;
    }

    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);
}

/** @brief Once this is the focused window, follow the memory card handler's progress. */
void CmcClass18A520::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (unka8 == 0)
    {
        return;
    }

    s32 size = func_00359C20(reinterpret_cast<Overlay0072Object00359C10*>(unka8));

    if (size != 0 && unkc0 == 0)
    {
        unkbc = 150.0f + static_cast<float>(60.0 * (3.75 * (size / 512.0f) / 100.0));
        unkc0 = 1;
    }

    unkb4 += g_frame_ticks;

    if (!(unkb4 <= unkbc))
    {
        unkb4 = unkbc;
    }

    if (func_00359C10(reinterpret_cast<Overlay0072Object00359C10*>(unka8)) == 0)
    {
        unkb0->func_00348520(static_cast<s32>(unkb4), static_cast<s32>(unkbc));
    }
    else
    {
        unkb0->func_00348520(static_cast<s32>(unkbc), static_cast<s32>(unkbc));
    }

    if (unka8->unk38 == 1)
    {
        func_00352D40();
        return;
    }

    if (unka8->unk34 == 0)
    {
        return;
    }

    if (unka8->unk30 == 0)
    {
        if (!(unkb4 <= unkbc))
        {
            unkb4 = unkbc;
        }

        unkb0->func_00348520(static_cast<s32>(unkbc), static_cast<s32>(unkbc));
        CmcClass18A320* window = new (0) CmcClass18A320;

        if (window == 0)
        {
            return;
        }

        window->func_slotf4(func_slot54());
        window->func_slot40(func_slot44());
        D_001B643C->unk10->unk14->add_child(window);
        D_001B643C->unk10->unk14->func_00263C70(window);
        unka8->func_0035ADA0(0, 1);
        lib_panel_detach(unkac);

        if (unkb0 != 0)
        {
            lib_object_detach_owner(unkb0);
            unkb0->destroy();
            unkb0 = 0;
        }

        FieldClass15AE70::func_slot18(0, 0x7F);
        field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);
    }
    else if (unka8->unk30 < 0)
    {
        func_00352D40();
    }
    else
    {
        CmcClass18A220* window = new (0) CmcClass18A220;

        if (window == 0)
        {
            return;
        }

        window->func_slotf4(func_slot54());
        window->func_slot40(func_slot44());
        D_001B643C->unk10->unk14->add_child(window);
        D_001B643C->unk10->unk14->func_00263C70(window);
        lib_panel_detach(unkac);

        if (unkb0 != 0)
        {
            lib_object_detach_owner(unkb0);
            unkb0->destroy();
            unkb0 = 0;
        }

        FieldClass15AE70::func_slot18(0, 0x7F);
        field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);
    }
}

/**
 * @brief Create the window's panel, its two texts and the progress bar.
 * @param associated Full resource source word.
 * @return Zero when the card handler or a widget is missing, otherwise one.
 */
s32 CmcClass18A520::func_slotf4(u32 associated)
{
    unka8 = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 60.0f, 164.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* title = new (0) LibTextWidget;
    LibTextWidget* message = new (0) LibTextWidget;

    if (panel == 0 || title == 0 || message == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 532.0f, 204.0f, 88.0f);
    lib_panel_init_transform(panel, 16700000.0f);
    unkac = panel;
    lib_container_attach_widget(unk10, panel);
    title->init_resource_rectangle(16.0f, 16.0f, 0.0f, 0.0f, associated, 0x531, 0);
    message->init_resource_rectangle(16.0f, 42.0f, 0.0f, 0.0f, associated, 0x545, 0);
    lib_container_attach_widget(unk10, title);
    lib_container_attach_widget(unk10, message);
    unk2c.append(title);
    unk2c.append(message);

    if (unkb0 != 0)
    {
        lib_object_detach_owner(unkb0);
        unkb0->destroy();
        unkb0 = 0;
    }

    unkb0 = new (0) CmcClass188D80;
    unkb0->func_003492E0(0x100, 0x18, 0x80FFFFFF, 0);
    unkb0->model->set_translation(-130.0f, 80.0f, 0.0f);
    unkb4 = 0;
    return 1;
}

void func_00353710(Overlay0072Object00353710* object, float x, float y, float z)
{
    object->field_50 = 1;
    object->field_20 = x;
    object->field_24 = y;
    object->field_28 = z;
    object->field_2C = 1.0f;
}

/** @brief Release the window's list object and destroy the window. */
CmcClass18A520::~CmcClass18A520()
{
    if (unkb0 != 0)
    {
        lib_object_detach_owner(unkb0);
        unkb0->destroy();
        unkb0 = 0;
    }
}

/** @brief Check whether this is the focused window; nothing else happens either way. */
void CmcClass18A620::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
u8 CmcClass18A620::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the controller's slot window, close the parent's slot list and both windows.
 * @return One.
 */
u8 CmcClass18A620::func_slotb0()
{
    CmcClass18AF20* controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

    if (controller != 0)
    {
        FieldClass15AE70* window = controller->unk7c;

        if (window != 0)
        {
            window->func_slot18(1, 0x7F);
            D_001B643C->unk10->unk14->func_00263C70(window);
            static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2329);
        }
    }

    // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
    CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

    if (parent->unkb8 != 0)
    {
        parent->unkb8->func_slot20(0);
    }

    if (parent->list != 0)
    {
        parent->list->unkab = 0;
        static_cast<LibCallbackTransform&>(*parent->list).destroy();
        parent->list = 0;
    }

    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), parent);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when either widget couldn't be allocated, otherwise one.
 */
s32 CmcClass18A620::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 40.0f, 216.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 560.0f, 120.0f, 88.0f);
    unk14.append(panel);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x523, 0, 24.0f, 24.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    return 1;
}

/** @brief Destroy the window and its Field parent. */
CmcClass18A620::~CmcClass18A620()
{
}

/** @brief Open the save window for the selected slot and restart the card handler. */
void CmcClass18A720::func_00353B60()
{
    CmcClass18A520* window = new (0) CmcClass18A520;

    if (window == 0)
    {
        return;
    }

    window->func_slotf4(func_slot54());
    window->func_slot40(func_slot44());
    D_001B643C->unk10->unk14->add_child(window);
    D_001B643C->unk10->unk14->func_00263C70(window);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232C);

    if (unka8 != 0)
    {
        unka8->unk18->unk1008 = 0;
        func_002EEE20(unka8->unk18, unkac, 2);
        unka8->unk48 = 1;
        unka8->func_0035AF60(0x40);
    }

    func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
}

/** @brief Once this is the focused window, act on the memory card handler's result. */
void CmcClass18A720::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    s16 state = unka8->func_0035AFC0();

    if (state == 0)
    {
        return;
    }

    if (state == 1)
    {
        func_00353B60();
        return;
    }

    CmcClass18A620* window = new (0) CmcClass18A620;

    if (window == 0)
    {
        return;
    }

    window->func_slotf4(func_slot54());
    window->func_slot40(func_slot44());
    D_001B643C->unk10->unk14->add_child(window);
    D_001B643C->unk10->unk14->func_00263C70(window);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);
    // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
    CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());
    CmcClass189810* list = parent->list;
    parent->func_slot18(0, 0x7F);
    list->unkab = 0;
    func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when a required object is missing, otherwise one.
 */
s32 CmcClass18A720::func_slotf4(u32 associated)
{
    unka8 = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 52.0f, 176.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 536.0f, 192.0f, 88.0f);
    unk14.append(panel);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x515, 0, 16.0f, 16.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    return 1;
}

/** @brief Destroy the window. */
CmcClass18A720::~CmcClass18A720()
{
}

void func_003540E0(void* object)
{
}

/**
 * @brief Run the window action and return status one.
 * @return One.
 */
u8 CmcClass18A820::func_slotb4()
{
    func_slotb0();
    return 1;
}

/**
 * @brief Restore the parent window, clear the main window's byte 0xD5, set the alternate text for the window's key and close it.
 * @return One.
 */
u8 CmcClass18A820::func_slotb0()
{
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    CmcClass18AF20* controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

    if (controller != 0)
    {
        controller->unk4c->unkD5 = 0;
    }

    switch (text_key)
    {
    case 0x2329:
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2329);
        break;
    case 0x232A:
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232A);
        break;
    case 0x232B:
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232B);
        break;
    }

    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    return 1;
}

/**
 * @brief Take the card handler, then create the frame, its panel and its resource text.
 * @param associated Full resource source word.
 * @return Zero when the handler or a widget is missing, otherwise one.
 */
s32 CmcClass18A820::func_slotf4(u32 associated)
{
    unka8 = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 80.0f, 152.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* first = new (0) LibTextWidget;
    LibTextWidget* second = new (0) LibTextWidget;
    LibTextWidget* third = new (0) LibTextWidget;
    LibObject174F20* number = new (0) LibObject174F20;

    if (panel == 0 || first == 0 || second == 0 || third == 0 || number == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 496.0f, 232.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    first->init_resource_rectangle(16.0f, 16.0f, 0.0f, 0.0f, static_cast<s32>(associated), 0x50E, 0);
    lib_container_attach_widget(unk10, first);
    return 1;
}

/** @brief Destroy the window and its Field parent. */
CmcClass18A820::~CmcClass18A820()
{
}

/** @brief Close the slot list and its window, dim the top window's choices and open the follow-up window. */
void CmcClass18A920::func_003545C0()
{
    static_cast<FieldClass15AE70*>(static_cast<FieldClass15AE70*>(func_slot44())->func_slot44())->func_slot18(1, 3);
    CmcClass18AC20* top = static_cast<CmcClass18AC20*>(static_cast<FieldClass15AE70*>(func_slot44())->func_slot44());
    top->unkb0->set_tint(0x505050);
    top->unkb4->set_tint(0x505050);
    // TODO: the parent could be CmcClass189E20 as well; both keep their slot list at 0xB0.
    CmcClass189D20* parent = static_cast<CmcClass189D20*>(func_slot44());

    if (parent->list != 0)
    {
        parent->list->unkab = 0;
        static_cast<LibCallbackTransform&>(*parent->list).destroy();
        parent->list = 0;
    }

    CmcClass18AB20* window = new (0) CmcClass18AB20;

    if (window == 0)
    {
        return;
    }

    window->func_slotf4(func_slot54());
    window->func_slot40(static_cast<FieldClass15AE70*>(func_slot44())->func_slot44());
    D_001B643C->unk10->unk14->add_child(window);
    D_001B643C->unk10->unk14->func_00263C70(window);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    FieldWindowRemovalContext* context = reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10);
    field_queue_window_removal(context, static_cast<FieldClass15AE70*>(func_slot44()));
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
}

/** @brief Once this is the focused window, lock it when the card handler finished, otherwise recolour the choices for the grid's cursor. */
void CmcClass18A920::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (unka8->unk38 == 1)
    {
        locked = 1;
        func_003545C0();
        return;
    }

    if (grid->unk114 == 0)
    {
        first_text->set_tint(0x288080);
        second_text->set_tint(0x808080);

        if (marker != 0)
        {
            marker->func_0023B7E0(first_text);
        }
    }
    else
    {
        first_text->set_tint(0x808080);
        second_text->set_tint(0x288080);

        if (marker != 0)
        {
            marker->func_0023B7E0(second_text);
        }
    }
}

/** @brief Move the grid in direction two. */
void CmcClass18A920::func_slot74()
{
    if (grid->process_direction(2) != 1)
    {
        return;
    }
}

/** @brief Move the grid in direction three. */
void CmcClass18A920::func_slot70()
{
    if (grid->process_direction(3) != 1)
    {
        return;
    }
}

/**
 * @brief Restore the parent window, close this one and set the alternate window's text unless it's locked.
 * @return Zero while locked, otherwise two.
 */
u8 CmcClass18A920::func_slotb4()
{
    if (locked != 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot18(0, 0x7F);
    FieldClass153E30* callbacks = D_001B643C->unk10->unk14;
    callbacks->func_00263C70(func_slot44());
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(1, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232B);
    return 2;
}

/**
 * @brief On the first choice open the result window for the card handler, otherwise act like func_slotb4.
 * @return Zero while locked or without a handler, two when func_slotb4 handled it, otherwise one.
 */
u8 CmcClass18A920::func_slotb0()
{
    s32 result = 0;

    if (unka8 == 0)
    {
        return 0;
    }

    if (locked == 1)
    {
        return 0;
    }

    if (grid->unk114 == 0)
    {
        if (unka8 != 0)
        {
            unka8->func_0035AF60(0x20);
        }

        CmcClass18A720* window = new (0) CmcClass18A720;

        if (window == 0)
        {
            return 0;
        }

        window->unkac = unkb8;
        window->func_slotf4(func_slot54());
        window->func_slot40(func_slot44());
        D_001B643C->unk10->unk14->add_child(window);
        D_001B643C->unk10->unk14->func_00263C70(window);
        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2330);
        func_slot18(0, 0x7F);
        field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    }
    else
    {
        result = func_slotb4();
    }

    u8 status;

    if (static_cast<u8>(result) == 0)
    {
        status = 1;
    }
    else
    {
        status = 2;
    }

    return status;
}

/**
 * @brief Create the window's panels, texts, grid and marker.
 * @param associated Full resource source word.
 * @return One on success.
 */
s32 CmcClass18A920::func_slotf4(u32 associated)
{
    unka8 = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 56.0f, 184.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;
    first_text = new (0) LibTextWidget;
    second_text = new (0) LibTextWidget;
    grid = new (0) FieldObject23CEA0;

    if (panel == 0 || text == 0 || first_text == 0 || second_text == 0 || grid == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 528.0f, 176.0f, 88.0f);
    unk14.append(panel);
    lib_container_attach_widget(unk10, panel);
    text->init_resource_rectangle(32.0f, 16.0f, 0.0f, 0.0f, associated, 0x50D, 0);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    first_text->init_resource_rectangle(144.0f, 128.0f, 0.0f, 0.0f, associated, 0x521, 0);
    first_text->set_tint(0x808080);
    lib_container_attach_widget(unk10, first_text);
    unk2c.append(first_text);
    second_text->init_resource_rectangle(328.0f, 128.0f, 0.0f, 0.0f, associated, 0x522, 0);
    second_text->set_tint(0x288080);
    lib_container_attach_widget(unk10, second_text);
    unk2c.append(second_text);
    grid->func_0023CE80(2, 1);
    grid->func_0023CE60(184.0f, 0.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(1, 200.0f, 312.0f);
    unk74.append(grid);
    marker = new (0) FieldClass153170;
    marker->func_0023B850(second_text, 0x288080);
    lib_container_attach_widget(unk10, marker);
    return 1;
}

/** @brief Destroy the window. */
CmcClass18A920::~CmcClass18A920()
{
}

/**
 * @brief Open the save slot list window for the card handler and close this window.
 * @param count Number of slots shown as available, used when it's a valid slot count.
 * @param flag Slot list flag stored with the count.
 */
void CmcClass18AA20::func_00355080(s32 count, u8 flag)
{
    CmcClass189E20* window = new (0) CmcClass189E20;

    if (window == 0)
    {
        return;
    }

    if (count >= 0 && count < 0x2E)
    {
        window->unkb4 = count;
        window->unkc2 = flag;
    }

    window->func_slotf4(func_slot54());
    window->func_slot40(func_slot44());
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(0, 0x7F);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232B);
    D_001B643C->unk10->unk14->add_child(window);
    D_001B643C->unk10->unk14->func_00263C70(window);
    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    unka8->func_0035ADA0(0, 1);
}

/**
 * @brief Open the card progress window for the card handler and close this window.
 * @param count Number of slots shown as available, used when it's a valid slot count.
 * @param flag Slot list flag stored with the count.
 */
void CmcClass18AA20::func_00355240(s32 count, u8 flag)
{
    CmcClass189D20* window = new (0) CmcClass189D20;

    if (window == 0)
    {
        return;
    }

    if (count >= 0 && count < 0x2E)
    {
        window->unkb4 = count;
        window->unkc2 = flag;
    }

    u8 created = window->func_slotf4(func_slot54());

    if (created == 0)
    {
        return;
    }

    D_001B643C->unk10->unk14->add_child(window);
    D_001B643C->unk10->unk14->func_00263C70(window);
    window->func_slot40(func_slot44());
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232B);
    static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(0, 0x7F);
    FieldClass15AE70::func_slot18(0, 0x7F);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    unka8->func_0035ADA0(0, 1);
}

/** @brief Once this is the focused window, act on the memory card handler's result and open the window that follows it. */
void CmcClass18AA20::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    if (unka8->unk38 == 1)
    {
        FieldClass153E30* callbacks = D_001B643C->unk10->unk14;

        if (callbacks != 0)
        {
            CmcClass189920* window = new (0) CmcClass189920;

            if (window != 0)
            {
                window->func_slotf4(func_slot54());
                window->unka8 = reinterpret_cast<CmcClass18AFB0*>(callbacks->func_slot60())->selected;

                if (window->unkac != 0)
                {
                    switch (window->unka8)
                    {
                    case 0:
                        lib_text_set_resource(window->unkac, window->func_slot54(), 0x535, 0);
                        break;
                    case 1:
                        lib_text_set_resource(window->unkac, window->func_slot54(), 0x536, 0);
                        break;
                    }

                    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
                }

                window->func_slot40(func_slot44());
                D_001B643C->unk10->unk14->add_child(window);
                static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
                D_001B643C->unk10->unk14->func_00263C70(window);
            }
        }

        field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
        return;
    }

    if (unka8->unk34 == 0)
    {
        return;
    }

    s16 slot = unka8->func_0035AFC0();

    if (slot < 0)
    {
        if (unka8->unk30 < -10)
        {
            FieldClass153E30* callbacks = D_001B643C->unk10->unk14;

            if (callbacks != 0)
            {
                CmcClass189920* window = new (0) CmcClass189920;

                if (window != 0)
                {
                    window->func_slotf4(func_slot54());
                    window->unka8 = reinterpret_cast<CmcClass18AFB0*>(callbacks->func_slot60())->selected;

                    if (window->unkac != 0)
                    {
                        switch (window->unka8)
                        {
                        case 0:
                            lib_text_set_resource(window->unkac, window->func_slot54(), 0x535, 0);
                            break;
                        case 1:
                            lib_text_set_resource(window->unkac, window->func_slot54(), 0x536, 0);
                            break;
                        }

                        static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
                    }

                    window->func_slot40(func_slot44());
                    D_001B643C->unk10->unk14->add_child(window);
                    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
                    D_001B643C->unk10->unk14->func_00263C70(window);
                }
            }

            field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
            return;
        }
        else
        {
            CmcClass189A20* window = new (0) CmcClass189A20;

            if (window != 0)
            {
                window->func_slotf4(func_slot54());
                window->func_slot40(func_slot44());
                D_001B643C->unk10->unk14->func_00263C70(window);
                D_001B643C->unk10->unk14->add_child(window);
                FieldClass15AE70::func_slot18(0, 3);
                static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(0, 0x7F);
                field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
            }
        }

        return;
    }

    if (unkb0 == 1)
    {
        return;
    }

    s32 used = unka8->func_0035AFA0();
    s32 count;
    u8 busy = unka8->unk40;
    s32 slots_used = used / 175;
    u8 full = 1;

    if (used < 175)
    {
        full = 0;
    }

    count = slot + slots_used;
    CmcClass18AF20* controller = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);
    controller->unk48 = slot;

    if (0x2D < count)
    {
        count = 0x2D;
    }

    controller->unk80 = 0;

    if (unkac == 1)
    {
        controller->unk80 = 1;
    }

    switch (unkac)
    {
    case 1:
        if (slot == 0)
        {
            if (unka8->func_0035AF80() == 0)
            {
                func_00355240(0x2D, 1);
                unkb0 = 1;
                return;
            }

            if (used < 175 && busy == 0)
            {
                CmcClass18A820* window = new (0) CmcClass18A820;

                if (window == 0)
                {
                    break;
                }

                window->func_slotf4(func_slot54());
                window->func_slot40(func_slot44());
                window->text_key = 0x2329;
                D_001B643C->unk10->unk14->func_00263C70(window);
                D_001B643C->unk10->unk14->add_child(window);
                static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(0, 0x7F);
                FieldClass15AE70::func_slot18(0, 3);
                field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
                static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);
                unka8->func_0035ADA0(0, 1);
                break;
            }

            func_00355240(count, 1);
        }
        else
        {
            func_00355240(count, full);
        }

        break;
    case 2:
    {
        if (slot == 0)
        {
            CmcClass189F20* window = new (0) CmcClass189F20;

            if (window != 0)
            {
                window->func_slotf4(func_slot54());
                window->func_slot40(func_slot44());
                D_001B643C->unk10->unk14->add_child(window);
                D_001B643C->unk10->unk14->func_00263C70(window);
                static_cast<FieldClass15AE70*>(func_slot44())->func_slot18(0, 0x7F);
                FieldClass15AE70::func_slot18(0, 0x7F);
                field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
                static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2336);
            }

            unkb0 = 1;
            return;
        }
        else
        {
            func_00355080(count, full);
        }

        break;
    }
    }

    unkb0 = 1;
}

/**
 * @brief Set display flags on the selected window lists.
 * @param flag Flag word forwarded to grids; its low byte updates other displays.
 * @param list_mask List groups selected by bits 0 through 6.
 */
void CmcClass18AA20::func_slot18(u32 flag, u32 list_mask)
{
    FieldClass15AE70::func_slot18(flag, list_mask);
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when a required object is missing, otherwise one.
 */
s32 CmcClass18AA20::func_slotf4(u32 associated)
{
    unka8 = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 48.0f, 180.0f, 14);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 544.0f, 172.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    unk14.append(panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x51A, 0, 24.0f, 24.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    unkac = D_001B643C->unk10->unk1a;

    if (unkac & 1)
    {
        unkac = 1;
    }

    if (unkac & 2)
    {
        unkac = 2;
    }

    return 1;
}

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

/**
 * @brief Restore the parent window, dim its two choices, close this window and set the alternate text.
 * @return Two.
 */
u8 CmcClass18AB20::func_slotb4()
{
    FieldClass15AE70::func_slot18(0, 3);
    CmcClass18AC20* parent = static_cast<CmcClass18AC20*>(func_slot44());
    D_001B643C->unk10->unk14->func_00263C70(parent);
    parent->func_slot18(1, 0x7F);
    parent->unkb0->set_tint(0x505050);
    parent->unkb4->set_tint(0x505050);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2329);
    return 2;
}

/**
 * @brief Restore the parent window, dim its two choices, close this window and set the alternate text.
 * @return One.
 */
u8 CmcClass18AB20::func_slotb0()
{
    FieldClass15AE70::func_slot18(0, 3);
    CmcClass18AC20* parent = static_cast<CmcClass18AC20*>(func_slot44());
    D_001B643C->unk10->unk14->func_00263C70(parent);
    parent->func_slot18(1, 0x7F);
    parent->unkb0->set_tint(0x505050);
    parent->unkb4->set_tint(0x505050);
    field_queue_window_removal(reinterpret_cast<FieldWindowRemovalContext*>(D_001B643C->unk10), this);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x2329);
    return 1;
}

/**
 * @brief Create the window frame, its panel, and its resource text.
 * @param associated Full resource source word.
 * @return Zero when a required object is missing, otherwise one.
 */
s32 CmcClass18AB20::func_slotf4(u32 associated)
{
    unka8 = static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14);

    if (unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 52.0f, 208.0f, 14);
    LibPanel* panel = new (0) LibPanel;
    LibTextWidget* text = new (0) LibTextWidget;

    if (panel == 0 || text == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 536.0f, 120.0f, 88.0f);
    unk14.append(panel);
    lib_container_attach_widget(unk10, panel);
    lib_text_init_resource_rectangle(text, static_cast<s32>(associated), 0x519, 0, 24.0f, 24.0f, 0.0f, 0.0f);
    lib_container_attach_widget(unk10, text);
    unk2c.append(text);
    return 1;
}

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

/** @brief Move the grid in direction one while the window is unlocked and the grid is enabled. */
void CmcClass18AC20::func_slot6c()
{
    if (func_slot28())
    {
        return;
    }

    if (unkb8 == 0)
    {
        return;
    }

    if (grid->process_direction(1) != 1)
    {
        return;
    }
}

/** @brief Move the grid in direction zero while the window is unlocked and the grid is enabled. */
void CmcClass18AC20::func_slot68()
{
    if (func_slot28())
    {
        return;
    }

    if (unkb8 == 0)
    {
        return;
    }

    if (grid->process_direction(0) != 1)
    {
        return;
    }
}

/** @brief While this is the focused window, colour both card slots by readiness, move the marker, and close the menu once confirmed. */
void CmcClass18AC20::func_slot5c()
{
    if (D_001B643C->unk10->unk14->func_00261150() != this)
    {
        return;
    }

    CmcClass18AD20* parent = static_cast<CmcClass18AD20*>(func_slot44());

    if (parent != 0)
    {
        if (parent->unkAc != 0)
        {
            parent->unkAc->visible = 0;
        }

        if (parent->unkB0 != 0)
        {
            parent->unkB0->visible = 0;
        }

        if (parent->unkD0 != 0)
        {
            parent->unkD0->visible = 0;
        }
    }

    if (unkb8 == 0)
    {
        unkb0->set_tint(0x505050);
        unkb4->set_tint(0x505050);
    }
    else
    {
        if (unka8->func_0035AFD0(0) == 2)
        {
            unkb0->set_tint(0x288080);
            unkb9[0] = 1;
        }
        else
        {
            unkb0->set_tint(0x505050);
            unkb9[0] = 0;
        }

        if (unka8->func_0035AFD0(1) == 2)
        {
            unkb4->set_tint(0x288080);
            unkb9[1] = 1;
        }
        else
        {
            unkb4->set_tint(0x505050);
            unkb9[1] = 0;
        }
    }

    if (marker != 0 && grid != 0 && grid->is_moving() == false)
    {
        if (grid->unk114 == 0)
        {
            marker->func_0023B7E0(unkb0);

            if (unkb9[0] != 0)
            {
                func_420D20(marker, 0x288080);
            }
            else
            {
                func_420D20(marker, 0x505050);
            }
        }
        else if (grid->unk114 == 1)
        {
            marker->func_0023B7E0(unkb4);

            if (unkb9[1] != 0)
            {
                func_420D20(marker, 0x288080);
            }
            else
            {
                func_420D20(marker, 0x505050);
            }
        }
    }

    if (!func_slot28())
    {
        return;
    }

    if (grid->is_moving() != false)
    {
        return;
    }

    CmcMenuState* menu = D_001B643C->unk0c;

    if (menu == 0)
    {
        return;
    }

    if (menu->is_closing() == true)
    {
        set_state(1, 0x80);
        return;
    }

    if (static_cast<CmcClass18AF20*>(D_001B643C->unk10->unk14)->unk50 != 0)
    {
        set_state(0xFF, 0x80);
        func_0020F230(field_display(), 0, 0, 0x80000000, 0, 0, 0, 10.0f, 0.0f, 0.0f);
        FieldScreenTransition* transition;
        (transition = field_display()->effects.transition)->depth = D_001B6694;
        transition->unkf0 = 10;
        CmcMenuState* closing = D_001B643C->unk0c;
        closing->unk9d = 1;
        closing->unk9e = 1;
    }
    else
    {
        set_state(0xFF, 0x80);
        D_001B643C->unk0c->unk9c = 1;
    }
}

/**
 * @brief Set the window control byte to one and return status two.
 * @return Two.
 */
u8 CmcClass18AC20::func_slotb4()
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

    if (marker != 0 && (u8)flag == 1)
    {
        marker->visible = 1;
    }
}

/**
 * @brief Select a card slot and open the slot window under this one.
 * @param slot Card slot.
 */
void CmcClass18AC20::func_003568C0(s16 slot)
{
    unka8->func_0035ADD0(slot, 0);
    CmcClass18AA20* window = new (0) CmcClass18AA20;

    if (window == 0)
    {
        return;
    }

    func_slot18(0, 0x7F);
    window->func_slotf4(func_slot54());
    window->func_slot40(this);
    D_001B643C->unk10->unk14->add_child(window);
    D_001B643C->unk10->unk14->func_00263C70(window);
    static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232A);
    CmcClass18AD20* parent = static_cast<CmcClass18AD20*>(func_slot44());
    parent->unkB8 = slot;
    parent->unkB9 = 1;

    if (marker != 0)
    {
        marker->visible = 0;
    }

    unka8->unk60 = 1;
    unka8->func_0035ADA0(0, 1);
}

/**
 * @brief Confirm the grid's card slot: open the slot window when it's ready, otherwise the card error window.
 * @return Zero while locked or disabled, three after opening the error window, otherwise one.
 */
u8 CmcClass18AC20::func_slotb0()
{
    if (func_slot28())
    {
        return 0;
    }

    if (unkb8 == 0)
    {
        return 0;
    }

    grid->unkad = 0;
    s16 slot = grid->unk114;

    if (slot == 0 || slot == 1)
    {
        g_field_runtime->message_arguments[1] = slot + 1;

        if (unka8->func_0035AFD0(slot) == 2 && unkb9[slot] == 1)
        {
            func_003568C0(slot);
        }
        else
        {
            CmcClass18AB20* window = new (0) CmcClass18AB20;

            if (window != 0)
            {
                window->func_slotf4(func_slot54());
                window->func_slot40(this);
                D_001B643C->unk10->unk14->add_child(window);
                D_001B643C->unk10->unk14->func_00263C70(window);
                static_cast<FieldClass15AE70*>(D_001B643C->unk10->unk14->func_00263C90())->func_slot60(0x232E);
            }

            return 3;
        }
    }

    return 1;
}

/**
 * @brief Create the card slot window's panel, both slot texts, the grid and its marker.
 * @param associated Full resource source word.
 * @return Zero when the card handler or a widget is missing, otherwise one.
 */
s32 CmcClass18AC20::func_slotf4(u32 associated)
{
    unka8 = reinterpret_cast<CmcClass18AFB0*>(D_001B643C->unk10->unk14->func_slot60());

    if (unka8 == 0)
    {
        return 0;
    }

    FieldClass15AE70::func_slot10(associated, 140.0f, 212.0f, 16);
    LibPanel* panel = new (0) LibPanel;
    unkb0 = new (0) LibTextWidget;
    unkb4 = new (0) LibTextWidget;
    grid = new (0) FieldObject23CEA0;

    if (panel == 0 || unkb0 == 0 || unkb4 == 0 || grid == 0)
    {
        return 0;
    }

    lib_panel_init_rectangle(panel, 0, 0.0f, 0.0f, 360.0f, 112.0f, 88.0f);
    lib_container_attach_widget(unk10, panel);
    unk14.append(panel);
    unkb0->init_resource_rectangle(70.0f, 24.0f, 0.0f, 0.0f, associated, 0x513, 0);
    unkb4->init_resource_rectangle(70.0f, 64.0f, 0.0f, 0.0f, associated, 0x514, 0);
    lib_container_attach_widget(unk10, unkb0);
    lib_container_attach_widget(unk10, unkb4);
    unk2c.append(unkb0);
    unk2c.append(unkb4);
    unkb0->set_tint(0x505050);
    unkb4->set_tint(0x505050);
    grid->func_0023CE80(1, 2);
    grid->func_0023CE60(0.0f, 40.0f);
    grid->unkF2 = 0;
    grid->func_0023CF50(0, 210.0f, 236.0f);
    unk74.append(grid);
    marker = new (0) FieldClass153170;
    marker->func_0023B850(unkb0, 0x288080);
    lib_container_attach_widget(unk10, marker);

    if (D_001B643C->unk10->unk1a & 8)
    {
        unkb8 = 0;
    }

    return 1;
}

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
            unkAc->visible = 1;
            unkD0->visible = 1;
            break;
        case 1:
            unkB0->visible = 1;
            unkD0->visible = 1;
            break;
        default:
            unkAc->visible = 0;
            unkB0->visible = 0;
            unkD0->visible = 0;
            break;
        }

        unkB9 = 0;
    }

    LibTextWidget* widget = unkA8;
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
        widget->needs_redraw = 1;
        ++unkBc;

        if (!(static_cast<float>(unkBc) <= 120.0f))
        {
            unkBc = 0;
            unkBa = 1;
        }

        return;
    }

    x -= 108.0f * g_frame_seconds;

    if (x < unkC8 - static_cast<float>(unkB4))
    {
        x = (unkC8 + unkCc) + 2.0f;
    }

    widget->unk18.unk00 = x;
    widget->unk18.unk04 = y;
    widget->unk18.unk08 = width;
    widget->unk18.unk0c = height;
    widget->needs_redraw = 1;
}

/**
 * @brief Set the window message.
 * @param text_key Message key.
 */
void CmcClass18AD20::func_slot60(s32 text_key)
{
    if (text_key < 0x2329)
    {
        return;
    }

    if (0x2338 < text_key)
    {
        return;
    }

    unkBa = 0;
    unkBc = 0;

    if (text_key == 0x2329 && (unkBe & 0x10))
    {
        text_key = 0x2331;
    }

    if (text_key == 0x2335)
    {
        unkA8->set_rect(unkC4, 6.0f, unkA8->unk18.unk08, unkA8->unk18.unk0c);
    }

    lib_text_set_resource(unkA8, func_slot54(), text_key, 1);
    unkB4 = static_cast<s32>(lib_text_measure_bounds(unkA8)->width) + 6;

    if (text_key == 0x232E || text_key == 0x2334)
    {
        // TODO: both arms store zero, but the 0x2334 compare only survives when this value isn't a plain constant
        unkD4 = text_key - text_key;
    }
    else
    {
        unkD4 = 0;
    }

    if (text_key == 0x232E)
    {
        unkD5 = 0;
    }

    if (text_key == 0x2334)
    {
        unkD5 = 0;
    }

    switch (text_key)
    {
    case 0x2329:
    case 0x232E:
    case 0x2332:
    case 0x2334:
        if (unkD5 == 0)
        {
            unkB8 = -1;
            unkB9 = 1;
        }

        break;
    }

    if (unkD5 == 1)
    {
        unkD5 = 0;
    }
}

/**
 * @brief Return a coordinate shifted by an offset.
 * @param origin Coordinate to shift.
 * @param offset Horizontal offset.
 * @return Shifted coordinate.
 */
static inline float shifted_position(const float& origin, float offset)
{
    return origin + offset;
}

/**
 * @brief Create the window's panel, message text and option displays.
 * @param associated Full resource source word.
 * @return One on success.
 */
s32 CmcClass18AD20::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 19);
    unkA8 = new (0) LibTextWidget;
    unkAc = new (0) LibTextWidget;
    unkB0 = new (0) LibTextWidget;
    LibClass1746A0* clip = new (0) LibClass1746A0;
    LibClass1746A0* reset = new (0) LibClass1746A0;

    if (unkA8 == 0 || clip == 0 || reset == 0 || unkAc == 0 || unkB0 == 0)
    {
        return 0;
    }

    u16 flags = D_001B643C->unk10->unk1a;

    if (flags & 1)
    {
        unkBe = 1;
    }
    else if (flags & 2)
    {
        unkBe = 2;
    }
    else
    {
        unkBe = -1;
    }

    if (flags & 0x10)
    {
        unkBe = 0x10;
    }

    LibTextWidget* label = new (0) LibTextWidget;
    LibTextWidget* caption = new (0) LibTextWidget;

    switch (unkBe)
    {
    case 1:
        label->init_resource_rectangle(16.0f, 6.0f, 0.0f, 0.0f, associated, 0x2339, 0);
        caption->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, associated, 0x539, 0);
        break;
    case 0x10:
        label->init_resource_rectangle(16.0f, 6.0f, 0.0f, 0.0f, associated, 0x233B, 0);
        caption->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, associated, 0x53A, 0);
        break;
    case 2:
        label->init_resource_rectangle(16.0f, 6.0f, 0.0f, 0.0f, associated, 0x233A, 0);
        caption->init_resource_rectangle(36.0f, 40.0f, 0.0f, 0.0f, associated, 0x53A, 0);
        break;
    default:
        label->init_resource_rectangle(16.0f, 6.0f, 0.0f, 0.0f, associated, 0x2328, 0);
        break;
    }

    lib_container_attach_widget(unk10, label);
    label->set_glyph_spacing(-1.0f);
    caption->set_scale(0.65f, 0.65f);
    lib_container_attach_widget(unk10, caption);
    unkC0 = lib_text_measure_bounds(label)->width;
    // TODO: the game adds 0.0f to these positions; the const-reference helper keeps the adds and their order
    unkC8 = shifted_position(18.0f + (16.0f + unkC0), 0.0f);
    unkCc = 636.0f - (16.0f + shifted_position(unkC8, 32.0f));
    unkC4 = 24.0f + shifted_position(16.0f + unkC0, 0.0f);
    unkAc->init_resource_rectangle(202.0f, 76.0f, 0.0f, 0.0f, associated, 0x513, 0);
    unkB0->init_resource_rectangle(202.0f, 76.0f, 0.0f, 0.0f, associated, 0x514, 0);
    lib_container_attach_widget(unk10, unkAc);
    lib_container_attach_widget(unk10, unkB0);
    unkAc->set_glyph_spacing(-1.0f);
    unkB0->set_glyph_spacing(-1.0f);
    unkAc->visible = 0;
    unkB0->visible = 0;
    lib_scissor_init_rectangle(clip, unkC8, 0.0f, unkCc, 56.0f);
    lib_container_attach_widget(unk10, clip);
    unkA8->init_resource_rectangle(unkC4, 6.0f, 0.0f, 0.0f, associated, 0x2329, 0);
    lib_container_attach_widget(unk10, unkA8);
    lib_scissor_init_reset(reset, 1);
    lib_container_attach_widget(unk10, reset);
    ItemCreationClass172870* top = new (0) ItemCreationClass172870;
    ItemCreationClass172870* bottom = new (0) ItemCreationClass172870;
    // TODO: -16.0f is negated at run time in the game, which a plain literal doesn't do
    float margin = 16.0f;
    lib_marker_init_rectangle(top, -margin, 56.0f, 640.0f, 2.25f);
    lib_marker_init_rectangle(bottom, -margin, 381.0f, 640.0f, 2.25f);
    top->unk50 = 0x886644;
    top->needs_redraw = 1;
    bottom->unk50 = 0x886644;
    bottom->needs_redraw = 1;
    lib_container_attach_widget(unk10, top);
    lib_container_attach_widget(unk10, bottom);
    ItemCreationClass172870* middle = new (0) ItemCreationClass172870;
    lib_marker_init_rectangle(middle, -margin, 120.0f, 640.0f, 2.25f);
    middle->unk50 = 0x886644;
    middle->needs_redraw = 1;
    lib_container_attach_widget(unk10, middle);
    float width = lib_text_measure_bounds(unkB0)->width;
    unkD0 = new (0) ItemCreationClass172870;
    lib_marker_init_rectangle(unkD0, 202.0f, 102.0f, width, 4.0f);
    ItemCreationClass172870* underline = unkD0;
    underline->unk50 = 0x666666;
    underline->needs_redraw = 1;
    unkD0->visible = 0;
    lib_container_attach_widget(unk10, unkD0);

    if (unkBe & 0x10)
    {
        func_slot60(0x2331);
    }
    else
    {
        func_slot60(0x2329);
    }

    return 1;
}

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

/**
 * @brief Create the three option resource displays and pick the mode from the runtime's window flags.
 * @param associated Full resource source word.
 * @return One.
 */
s32 CmcClass18AE20::func_slotf4(u32 associated)
{
    FieldClass15AE70::func_slot10(associated, 16.0f, 16.0f, 20);
    unkac = new (0) ItemCreationOptionResourceDisplay;
    unkb0 = new (0) ItemCreationOptionResourceDisplay;
    unkb4 = new (0) ItemCreationOptionResourceDisplay;
    void* allocation = field_get_aligned_allocation(D_001B643C->slots, 11);
    unkac->unkcc = allocation;
    unkb0->unkcc = allocation;
    unkb4->unkcc = allocation;
    unkac->unkd0 = 11;
    unkb0->unkd0 = 11;
    unkb4->unkd0 = 11;
    unkac->func_002D6440(0.0f, 0.0f, field_find_resource_record(D_001B643C->slots, 5));
    unkb0->func_002D6440(256.0f, 0.0f, field_find_resource_record(D_001B643C->slots, 6));
    unkb4->func_002D6440(512.0f, 0.0f, field_find_resource_record(D_001B643C->slots, 7));
    lib_container_attach_widget(unk10, unkac);
    lib_container_attach_widget(unk10, unkb0);
    lib_container_attach_widget(unk10, unkb4);
    u16 flags = D_001B643C->unk10->unk1a;

    if (flags & 1)
    {
        unka8 = 1;
    }
    else if (flags & 2)
    {
        unka8 = 2;
    }
    else if (flags & 0x10)
    {
        unka8 = 0x10;
    }
    else
    {
        unka8 = -1;
    }

    return 1;
}

/** @brief Destroy the window. */
CmcClass18AE20::~CmcClass18AE20()
{
}

/** @brief Show the window for the pending request and set the alternate window's text for it. */
void CmcClass18AF20::dispatch_window_request()
{
    switch (unk54)
    {
    case 0x6C:
    {
        CmcClass189710* window = unk70;
        lib_text_set_resource(window->unkac, window->func_slot54(), 0x519, 0);
        unk4c->func_slot60(0x232E);
        D_001B643C->unk10->unk14->func_00263C70(unk70);
        unk70->func_slot20(1);
        break;
    }
    case 0x73:
        unk4c->func_slot60(0x2338);
        D_001B643C->unk10->unk14->func_00263C70(unk58);
        unk58->func_slot20(1);
        break;
    case 0x74:
        unk4c->func_slot60(0x2336);
        D_001B643C->unk10->unk14->func_00263C70(unk5c);
        unk5c->func_slot20(1);
        break;
    case 0x75:
        unk4c->func_slot60(0x2336);
        D_001B643C->unk10->unk14->func_00263C70(unk60);
        unk60->func_slot20(1);
        break;
    case 0x76:
        unk4c->func_slot60(0x2332);
        D_001B643C->unk10->unk14->func_00263C70(unk64);
        unk64->func_slot20(1);
        break;
    case 0x78:
        unk4c->func_slot60(0x2336);
        D_001B643C->unk10->unk14->func_00263C70(unk68);
        unk68->func_slot20(1);
        break;
    case 0x79:
        unk4c->func_slot60(0x2334);
        D_001B643C->unk10->unk14->func_00263C70(unk6c);
        unk6c->func_slot20(1);
        break;
    case 0x7A:
    {
        unk4c->func_slot60(0x2332);
        D_001B643C->unk10->unk14->func_00263C70(unk74);
        CmcClass189010* dialog = unk74;
        dialog->func_slot20(1);
        dialog->unkb4->set_tint(0x288080);
        dialog->marker->func_0023B7E0(dialog->unkb4);
        dialog->marker->unk5c = 1;
        break;
    }
    case 0x7B:
    {
        unk4c->func_slot60(0x2336);
        D_001B643C->unk10->unk14->func_00263C70(unk78);
        CmcClass188F10* window = unk78;

        if (window->unkac != 0)
        {
            lib_text_set_resource(window->unkac, window->func_slot54(), 0x234A, 0);
        }

        window->func_slot20(1);
        break;
    }
    }
}

/** @brief With no window request pending, fade the screen out and hand the field back to a camera facing the field object's heading. */
void CmcClass18AF20::func_003583B0()
{
    if (unk54 != 0)
    {
        return;
    }

    func_0020F230(field_display(), 0, 0, 0x80000000, 0, 0, 0, 10.0f, 0.0f, 0.0f);
    FieldScreenTransition* transition;
    (transition = field_display()->effects.transition)->depth = D_001B6694;
    transition->unkf0 = 10;
    FieldClass15B9C0* field = unk3c;
    float angle = 360.0f * field->unk1090 / 2.0f / 3.1415927f;

    if (angle < 0.0f)
    {
        angle += 360.0f;
    }

    FieldVec4A* position = &field->unk1080;
    float height = field->unk1094;
    FieldClass15BBB0* camera = new (0) FieldClass15BBB0;

    if (camera == 0)
    {
        return;
    }

    field = unk3c;
    s32 value = field->unk1098;
    camera->unk9c0 = field->unk1070;
    camera->unk9d0 = *position;
    camera->unk9e0 = angle;
    camera->unk9e4 = height;
    camera->unk9e8 = value;
    strcpy_guess(camera->name, D_35B390);
    camera->unk9fd_0 = 1;
    camera->unk9ca = static_cast<ResidentCheckedRecord*>(func_101440(func_101290(resident_get_system()), 1))->unk23;
    static_cast<LibUpdateList*>(g_renderer)->append_node(camera, -1);
    D_001B643C->unk0c->unk9b = 1;
    LibProtectedValues* values = static_cast<LibProtectedValues*>(func_101440(func_101290(resident_get_system()), 7));

    if (values != 0)
    {
        values->reset();
    }
}

void func_003585A0(void* object)
{
}

/** @brief Release the retained resource slot, detach the controller, and queue it. */
void CmcClass18AF20::func_slot5c()
{
    if (resource_slot)
    {
        lib_release_resource_slot(g_field_runtime, resource_slot);
    }

    lib_object_detach_owner(this);
    func_001DD7B0();
}

/** @brief Add this object to the resident queue. */
void CmcClass18AF20::func_001DD7B0()
{
    resident_enqueue_object(g_resident_release_queues, this);
}

/**
 * @brief Create the card menu's windows, set each up and register it with the controller.
 * @return One.
 */
s32 CmcClass18AF20::init_windows()
{
    CmcClass18AE20* options = new (0) CmcClass18AE20;
    CmcClass18AD20* message = new (0) CmcClass18AD20;
    unk7c = new (0) CmcClass18AC20;
    unk44 = new (0) CmcClass189C20;
    unk70 = new (0) CmcClass189710(this);
    unk64 = new (0) CmcClass189310(this);
    unk58 = new (0) CmcClass189610(this);
    unk5c = new (0) CmcClass189510(this);
    unk60 = new (0) CmcClass189410(this);
    unk68 = new (0) CmcClass189210(this);
    unk6c = new (0) CmcClass189110(this);
    unk74 = new (0) CmcClass189010(this);
    unk78 = new (0) CmcClass188F10(this);
    options->func_slotf4(resource_slot);
    FieldClass153E30::add_child(options);
    options->func_slot40(0);
    unk4c = message;
    message->func_slotf4(resource_slot);
    message->func_slot40(options);
    FieldClass153E30::add_child(message);
    unk24 = message;
    unk7c->func_slotf4(resource_slot);
    unk7c->func_slot40(message);
    FieldClass153E30::add_child(unk7c);
    unk44->func_slotf4(resource_slot);
    FieldClass153E30::add_child(unk44);
    D_001B643C->unk10->unk14->func_00263C70(unk7c);
    unk70->func_slotf4(resource_slot);
    unk70->func_slot20(0);
    FieldClass153E30::add_child(unk70);
    unk64->func_slotf4(resource_slot);
    unk64->func_slot20(0);
    FieldClass153E30::add_child(unk64);
    unk58->func_slotf4(resource_slot);
    unk58->func_slot20(0);
    FieldClass153E30::add_child(unk58);
    unk5c->func_slotf4(resource_slot);
    unk5c->func_slot20(0);
    FieldClass153E30::add_child(unk5c);
    unk60->func_slotf4(resource_slot);
    unk60->func_slot20(0);
    FieldClass153E30::add_child(unk60);
    unk68->func_slotf4(resource_slot);
    unk68->func_slot20(0);
    FieldClass153E30::add_child(unk68);
    unk6c->func_slotf4(resource_slot);
    unk6c->func_slot20(0);
    FieldClass153E30::add_child(unk6c);
    unk74->func_slotf4(resource_slot);
    CmcClass189010* dialog = unk74;
    dialog->func_slot20(0);
    dialog->selector->func_0023B280(1);
    dialog->unkb0->set_tint(0x808080);
    dialog->unkb4->set_tint(0x288080);
    dialog->marker->func_0023B7E0(dialog->unkb4);
    FieldClass153E30::add_child(unk74);
    unk78->func_slotf4(resource_slot);
    unk78->func_slot20(0);
    FieldClass153E30::add_child(unk78);
    unk40 = 1;
    return 1;
}

/**
 * @brief Bind a completed resource buffer and finish controller setup.
 * @param buffer Completed buffer, aligned to 128 bytes before use.
 * @return Setup result, or zero when the buffer is null.
 */
s32 CmcClass18AF20::on_resource_loaded(void* buffer)
{
    CmcResourceBuffer* resource = static_cast<CmcResourceBuffer*>(buffer);

    if (!resource)
    {
        return 0;
    }

    resource = reinterpret_cast<CmcResourceBuffer*>((reinterpret_cast<u32>(resource) + 0x7F) & ~0x7F);
    s32 allocation_size = resource->byte_count + 0x80;
    void* previous_heap = resident_get_allocation_heap();
    void* resource_heap = D_001B6430->context->unk70;
    void* allocation = resident_heap_allocate(resource_heap, allocation_size);

    if (allocation)
    {
        resident_heap_release(allocation);
        resident_exchange_allocation_heap(resource_heap);
    }

    resource_slot = lib_load_resource_slot(g_field_runtime, resource);
    resident_exchange_allocation_heap(previous_heap);
    return init_windows();
}

/**
 * @brief Create the memory card handler, add it to the update list and link its Field object to the controller.
 * @return One on success, or zero when the handler or its Field object couldn't be set up.
 */
u8 CmcClass18AF20::func_00264110()
{
    g_field_runtime->message_arguments[0] = 0xAF;
    unk50 = 0;

    if (D_001B643C->unk10->unk1a & 0x10)
    {
        unk50 = 1;
    }

    linked_object = new (0) CmcClass18AFB0;

    if (linked_object == 0)
    {
        return 0;
    }

    if (linked_object->func_0035AFF0() == 0)
    {
        return 0;
    }

    g_update_list->append_node(linked_object, LibUpdateList::DEFAULT_NODE_KIND);
    linked_object->unk49 = unk50;
    unk3c = linked_object->unk18;

    if (unk3c == 0)
    {
        return 0;
    }

    unk3c->unk124d = unk50;
    func_002EE9C0(unk3c, this);
    return 1;
}

/** @brief Detach and release the linked object, then destroy the Field parent. */
CmcClass18AF20::~CmcClass18AF20()
{
    if (linked_object != 0)
    {
        lib_object_detach_owner(linked_object);
        linked_object->destroy();
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

/** @brief Delete the object through its virtual destructor. */
void LibListObject::destroy()
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
void LibOrientedTransform::convert_rotation(const LibVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value->x);
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param value Source vector.
 */
void LibOrientedTransform::set_rotation_vector(const LibVector4* value)
{
    transform_dirty = 1;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), &value->x);
}

/**
 * @brief Update the transform components and mark the transform dirty.
 * @param x Component value.
 * @param y Component value.
 * @param z Component value.
 */
void LibOrientedTransform::set_rotation(float x, float y, float z)
{
    float value[4];
    transform_dirty = 1;
    value[0] = x;
    value[1] = y;
    value[2] = z;
    value[3] = 1.0f;
    lib_quaternion_from_euler(reinterpret_cast<FieldVec4B*>(&orientation), value);
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
    return g_default_bounding_sphere;
}

s32 func_00359180(void* object)
{
    return 0;
}

void func_00359190(void* object)
{
}

/** @brief Called once the position reaches the target; the base version does nothing. */
void LibMovementState::on_arrived()
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

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param value Pointer stored in the node. The caller owns it.
 */
void FieldClass15AFE8::append(void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node != 0)
    {
        FieldListNode* tail;
        node->value = value;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param value Pointer stored in the node. The caller owns it.
 */
void FieldClass15AF88::append(void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node != 0)
    {
        FieldListNode* tail;
        node->value = value;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/**
 * @brief Return the node at `index`. Index zero is the first node after the sentinel.
 * @param index Zero-based index among the value nodes.
 * @return The node at that index, or null if the list ends first.
 */
FieldListNode* FieldClass15AF88::at(s32 index)
{
    FieldListNode* node = head->next;
    s32 step;

    for (step = 0; step < index; step++)
    {
        if (node == 0)
        {
            return 0;
        }

        node = node->next;
    }

    return node;
}

/**
 * @brief Add a node holding `value` to the end of the list.
 * @param value Pointer stored in the node. The caller owns it.
 */
void FieldClass15AF68::append(void* value)
{
    FieldListNode* node = new (0) FieldListNode;

    if (node != 0)
    {
        FieldListNode* tail;
        node->value = value;
        node->next = 0;
        tail = head;

        while (tail->next != 0)
        {
            tail = tail->next;
        }

        tail->next = node;
        count++;
    }
}

/**
 * @brief Return the handler's list kind.
 * @return Two.
 */
s32 CmcClass18AFB0::get_default_list_kind()
{
    return 2;
}

/**
 * @brief Parse five hexadecimal digits; anything that isn't a hex digit counts as zero.
 * @param text Text holding the digits.
 * @param offset Offset of the first digit.
 * @return The parsed value.
 */
static inline s32 cmc_parse_hex5(const char* text, s32 offset)
{
    char digits[6];
    digits[5] = 0;
    digits[4] = 0;
    digits[3] = 0;
    digits[2] = 0;
    digits[1] = 0;
    digits[0] = 0;

    for (s32 index = 0; index < 5; index++)
    {
        digits[index] = text[index + offset];
    }

    s32 value = 0;

    for (s32 index = 0; index < 5; index++)
    {
        s32 digit = digits[index];

        if (digit >= '0' && digit <= '9')
        {
            digit -= '0';
        }
        else if (digit >= 'a' && digit <= 'f')
        {
            digit -= 'a' - 10;
        }
        else if (digit >= 'A' && digit <= 'F')
        {
            digit -= 'A' - 10;
        }
        else
        {
            digit = 0;
        }

        value = value * 16 + digit;
    }

    return value;
}

/**
 * @brief Record the file just read as a save entry, then start reading the next file or finish.
 * @param skip Nonzero to skip recording the entry.
 */
void CmcClass18AFB0::func_00359970(s32 skip)
{
    if (static_cast<u8>(skip) == 0)
    {
        CmcRowRecord* entry = static_cast<CmcRowRecord*>(operator new(0x80, 0));
        memset_guess(entry, 0, 0x80);
        s32 value = cmc_parse_hex5(unk18->unk100b, strlen(D_35B300) + 1);

        if (0 < value && value < 0x2E)
        {
            entry->slot = value;
        }
        else
        {
            entry->slot = 0;
        }

        func_002EEE00(unk18, entry);
    }

    func_00431730(card);
    func_004317B0(card, 3);
    unk36++;

    if (unk36 == unk18->unk105a)
    {
        unk22 = unk36;
        unk1e = 0;
        unk39 = 1;
        unk34 = 1;
        unk1e = 0;
        return;
    }

    unk20 = 0;
    unk1e = 4;
    unk22 = 0;
    unk39 = 0;
    unk34 = 0;
    unk30 = -1;

    if (func_002EEE90(unk18, unk36) == 0)
    {
        unk22 = -1;
        unk1e = 0;
        unk39 = 0;
        unk34 = 1;
        unk1e = 0;
        return;
    }

    if (lib_memory_card_start_transfer(card, selected, func_002EF000(unk18)) == 0)
    {
        unk20 = 0;
        unk1e = 4;
        unk22 = 0;
        unk39 = 0;
        unk34 = 0;
        unk30 = -1;
        return;
    }

    unk22 = -1;
    unk1e = 0;
    unk39 = 0;
    unk34 = 1;
    unk1e = 0;
}

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

/**
 * @brief Run one step of saving the Field object's data to the selected card slot.
 * @return Zero while the save runs, one once it finished, or -1 when the data isn't ready.
 */
s32 CmcClass18AFB0::func_00359C50()
{
    s32 result = 0;

    switch (unk20)
    {
    case 0:
        if (unk18->unk1009 == 0)
        {
            result = func_002EFFF0(unk18);
        }

        if (result == 0)
        {
            return -1;
        }

        result = lib_memory_card_start_transfer(card, selected, func_002EF000(unk18));

        if (result == 0)
        {
            unk20++;
            unk58 = -1;
            unk5c = -1;
        }

        break;
    case 1:
        if (lib_memory_card_get_result(card, selected, &unk30) != 0)
        {
            unk20++;
            result = 1;

            if (unk30 >= 0)
            {
                if (func_002EF6B0(unk18) == 0)
                {
                    unk30 = -1;
                    unk58 = -1;
                }
                else
                {
                    unk58 = result;
                }
            }
            else
            {
                unk58 = -1;
                unk5c = -1;
            }
        }

        break;
    case 2:
        break;
    }

    return result;
}

/**
 * @brief Run one step of loading the selected card slot into the Field object.
 * @return Zero while the load runs, one once a step finished, or -1 when the Field object isn't ready.
 */
s32 CmcClass18AFB0::func_00359DA0()
{
    s32 result = 0;

    switch (unk20)
    {
    case 0:
        if (unk18->unk1008 == 0)
        {
            if (unk48 != 0)
            {
                func_00432710(card, 0x202);
                unk18->unk1244 = 1;
            }
            else
            {
                func_00432710(card, 2);
                unk18->unk1244 = 0;
            }

            result = func_002F1E60(unk18);
        }

        if (result == 0)
        {
            return -1;
        }

        card->unk28 = 0;
        result = func_004324D0(card, selected, func_002EF000(unk18));

        if (result == 0)
        {
            unk20++;
        }

        break;
    case 1:
        result = lib_memory_card_get_result(card, selected, &unk30);

        if (result != 0 && result == 1)
        {
            if (unk48 != 0)
            {
                if (unk30 >= 0)
                {
                    unk20++;
                    result = 0;
                    func_00432710(card, 2);
                }
                else
                {
                    unk20 += 4;
                    func_00432710(card, 0x202);
                }
            }
            else
            {
                unk20 += 4;
                func_00432710(card, 0x202);
            }
        }

        break;
    case 2:
        if (unk48 != 0)
        {
            if (func_002F1B20(unk18) == 0)
            {
                return -1;
            }

            result = func_004324D0(card, selected, func_002EF000(unk18));

            if (result == 0)
            {
                unk20++;
            }
        }

        break;
    case 3:
        if (unk48 != 0)
        {
            result = lib_memory_card_get_result(card, selected, &unk30);

            if (result != 0 && result == 1)
            {
                unk20++;
                func_00432710(card, 0x202);
            }
        }

        break;
    }

    return result;
}

/** @brief Run the selected memory card operation one frame further. */
void CmcClass18AFB0::update()
{
    if (card == 0 || unk18 == 0)
    {
        return;
    }

    if (func_002F2880(unk18) == 0)
    {
        return;
    }

    s16 previous = unk24;
    s32 state = previous;

    if (unk34 == 0)
    {
        state = selected < 0 ? -1 : card->slots[selected].card_state;

        if (state != previous)
        {
            unk24 = state;

            if (mode == 0)
            {
                unk1e = 1;

                if (unk60 != 0)
                {
                    unk60 = 0;
                    return;
                }
            }
            else if (unk44 == 0)
            {
                unk1e = 5;
            }
            else
            {
                unk1e = 9;
            }

            if (unk39 == 1)
            {
                unk38 = 1;
                unk1e = 0;
            }

            return;
        }
    }

    s32 result = 0;

    switch (unk1e)
    {
    case 0:
        break;
    case 1:
        if (state != 2)
        {
            stop(0);
            unk22 = -1;
            unk30 = -12;
            unk1e = 0;
            break;
        }

        unk22 = 0;
        unk28 = card->slots[selected].formatted;

        if (unk28 == 0)
        {
            stop(1);
            break;
        }

        unk2c = card->slots[selected].free_space;

        if (unk64 > 0)
        {
            unk64--;
            break;
        }

        unk1e = 2;
        unk39 = 0;
        break;
    case 2:
        func_002F23E0(unk18, D_35B300, D_35B3A0);

        if (lib_memory_card_probe_file(card, selected, unk18->unk100b, 0, 0x32, unk18->unkF7C) != -1)
        {
            func_002F2890(unk18);
            unk1e = 3;
        }

        break;
    case 3:
    {
        s32 status = lib_memory_card_get_result(card, selected, &result);

        if (status == 0 || status != 1)
        {
            break;
        }

        if (result > 0)
        {
            func_002EF010(unk18, result);
            unk36 = 0;
            unk54 = 0;
            unk50 = 0;
            unk69 = 0;
            func_002F2890(unk18);
            func_00431730(card);
            func_004317B0(card, 3);
        }

        if (result == 0)
        {
            unk22 = 0;
            stop(1);
            unk1e = 0;
        }
        else if (result > 0)
        {
            unk20 = 0;
            unk1e = 4;
            unk22 = 0;
            unk39 = 0;
            unk34 = 0;
            unk30 = -1;

            if (func_002EEE90(unk18, unk36) == 0)
            {
                unk22 = -1;
                stop(0);
                unk1e = 0;
            }
            else if (lib_memory_card_start_transfer(card, selected, func_002EF000(unk18)) == 0)
            {
                unk20 = 0;
                unk1e = 4;
                unk22 = 0;
                unk39 = 0;
                unk34 = 0;
                unk30 = -1;
            }
            else
            {
                unk22 = -1;
                stop(0);
                unk1e = 0;
            }
        }
        else if (result < -10)
        {
            unk22 = -1;
            stop(0);
            unk1e = 0;
            unk30 = result;
        }
        else
        {
            func_00359970(0);
        }

        break;
    }
    case 4:
    {
        s32 status = lib_memory_card_get_result(card, selected, &result);

        if (status == 0 || status != 1)
        {
            break;
        }

        if (result == 0)
        {
            unk46 = selected;

            if (func_002EF520(unk18) != 0)
            {
                unk40 = 1;
            }

            CmcRowRecord* copy = new (0) CmcRowRecord;
            memset_guess(copy, 0, 0x80);
            memcpy_guess(copy, unk18->unkF8C, 0x80);

            if (unk50 < copy->unk3c && unk69 == 0 && 0 < static_cast<u16>(copy->slot) && static_cast<u16>(copy->slot) < 0x2E)
            {
                unk50 = copy->unk3c;
                unk54 = copy->slot;
            }

            CmcSystemRecord* system = static_cast<CmcSystemRecord*>(func_101440(func_101290(resident_get_system()), 1));

            if (system->unk188 != 0 && copy->unk58 == system->unk188 && 0 < static_cast<u16>(copy->slot) && static_cast<u16>(copy->slot) < 0x2E)
            {
                unk50 = copy->unk3c;
                unk54 = copy->slot;
                unk69 = 1;
            }

            func_431770(card, 3);
            s32 value = cmc_parse_hex5(unk18->unk100b, strlen(D_35B300) + 1);

            if (0 < value && value < 0x2E)
            {
                copy->slot = value;
            }
            else
            {
                copy->slot = 0;
            }

            func_002EEE00(unk18, copy);
            func_00359970(1);
        }
        else if (result < -10)
        {
            unk22 = -1;
            stop(0);
            unk1e = 0;
            unk30 = result;
        }
        else
        {
            func_00359970(0);
        }

        break;
    }
    case 5:
        if (state != 2)
        {
            unk42[selected] = 0x81;
        }
        else
        {
            unk28 = card->slots[selected].formatted;

            if (unk28 == 0)
            {
                unk42[selected] = 0x81;
            }
        }

        unk1e = 6;
        break;
    case 6:
        if (unk42[selected] != 0x81)
        {
            func_002F23E0(unk18, D_35B300, D_35B3A8);

            if (lib_memory_card_probe_file(card, selected, unk18->unk100b, 0, 1, unk18->unkF7C) != -1)
            {
                unk1e = 7;
            }
        }
        else
        {
            unk1e = 7;
        }

        break;
    case 7:
        if (unk42[selected] != 0x81)
        {
            s32 status = lib_memory_card_get_result(card, selected, &result);

            if (status == 0 || status != 1)
            {
                break;
            }

            if (result == 0)
            {
                unk42[selected] = 0x81;
            }
            else if (result > 0)
            {
                unk42[selected] = 0x82;
            }

            if (selected == 0)
            {
                selected = 1;
                unk1e = 5;
            }
            else
            {
                unk1e = 8;
            }
        }
        else if (selected == 0)
        {
            unk1e = 5;
            selected = 1;
        }
        else
        {
            unk1e = 8;
        }

        break;
    case 8:
        if (unk42[0] == 0x81 && unk42[1] == 0x81)
        {
            if (static_cast<u8>(D_001B643C->unk00->unk25_6) == 1)
            {
                unk30 = 0;
                unk4c = 0x81;
            }
            else
            {
                unk30 = 0;
                unk4c = 0;
            }

            stop(0);
        }
        else if (unk42[0] == 0x82 && unk42[1] == 0x81)
        {
            selected = 0;
            unk1e = 9;
        }
        else if (unk42[0] == 0x81 && unk42[1] == 0x82)
        {
            selected = 1;
            unk1e = 9;
        }
        else
        {
            unk30 = 0;
            unk4c = 0x85;
            stop(0);
        }

        unk44 = 1;
        break;
    case 9:
        if (state != 2)
        {
            unk22 = -1;
            stop(0);
            unk1e = 0;
            unk5c = -1;
            unk4c = 0x86;
            break;
        }

        unk28 = card->slots[selected].formatted;

        if (unk28 == 0 && unk44 == 1)
        {
            unk4c = 0x81;
            unk30 = -2;
            stop(0);
            break;
        }

        unk1e = 0xA;
        break;
    case 0xA:
        func_002F23E0(unk18, D_35B300, D_35B3A8);

        if (lib_memory_card_probe_file(card, selected, unk18->unk100b, 0, 1, unk18->unkF7C) != -1)
        {
            unk1e = 0xB;
        }

        break;
    case 0xB:
    {
        s32 status = lib_memory_card_get_result(card, selected, &result);

        if (status == 0)
        {
            break;
        }

        if (status == 1)
        {
            if (result == 0)
            {
                unk30 = result;
                unk4c = 0x81;
                stop(0);
                break;
            }

            if (result > 0)
            {
                unk30 = result;

                if (func_002EED90(unk18) == 0)
                {
                    status = func_002EEC90(unk18);
                }

                if (status == 0)
                {
                    unk22 = -1;
                    stop(0);
                    unk1e = 0;
                    break;
                }

                if (lib_memory_card_start_transfer(card, selected, func_002EF000(unk18)) == 0)
                {
                    unk1e = 0xC;
                }

                break;
            }

            stop(0);
            unk30 = result;

            if (result < -10)
            {
                unk22 = result;
                unk4c = 0x81;
            }
            else
            {
                unk22 = -1;
                unk4c = 0x86;
            }

            unk1e = 0;
            unk5c = -1;
            break;
        }

        unk30 = result;
        unk22 = -1;
        stop(0);
        unk1e = 0;
        break;
    }
    case 0xC:
    {
        s32 status = lib_memory_card_get_result(card, selected, &unk30);

        if (status == 0)
        {
            break;
        }

        if (status == 1)
        {
            if (unk30 >= 0)
            {
                if (func_002EEB30(unk18) != 0)
                {
                    func_002EE9E0(unk18);
                    unk4c = 0;
                    stop(0);
                    unk1e = 0;
                    unk5c = 1;
                }
                else
                {
                    unk4c = 0x83;
                    stop(0);
                    unk1e = 0;
                    unk5c = -1;
                }
            }
            else
            {
                unk22 = unk30;
                stop(0);
                unk1e = 0;
                unk4c = 0x86;
                unk5c = -1;
            }

            break;
        }

        unk22 = -1;
        stop(0);
        unk1e = 0;
        break;
    }
    case 0x20:
    {
        s32 status = func_0035AE70();

        if (status != 0)
        {
            unk22 = status;
            unk1e = 0;
        }

        break;
    }
    case 0x40:
        if (func_00359DA0() != 0)
        {
            stop(0);
        }

        break;
    case 0x30:
        if (func_00359C50() == 0)
        {
            break;
        }

        if (unk30 < 0)
        {
            stop(0);
            break;
        }

        if (unk49 == 0)
        {
            unk39 = 0;
            mode = 1;
            unk1e = 5;
            selected = 0;
            break;
        }

        stop(0);
        break;
    }
}

/**
 * @brief Set the state and the companion byte, clearing unk1e when the state is one.
 * @param value New state.
 * @param other New companion byte.
 */
void CmcClass18AFB0::func_0035ADA0(u8 value, u8 other)
{
    if (value == 1)
    {
        unk1e = 0;
    }

    unk39 = other;
    unk34 = value;
}

/**
 * @brief Select a record and reset the run state for the given mode.
 * @param index Record index to select.
 * @param mode Run mode; mode one skips the colour defaults.
 */
void CmcClass18AFB0::func_0035ADD0(s16 index, u8 mode)
{
    selected = index;
    unk24 = -1;
    unk39 = 0;
    unk38 = 0;
    unk22 = 0;
    unk39 = 0;
    unk34 = 0;
    unk3c = 0;
    unk40 = 0;
    this->mode = mode;

    if (this->mode == 1)
    {
        unk34 = 0;
    }
    else
    {
        unk44 = 0;
        unk42[0] = 0x80;
        unk42[1] = 0x80;
    }

    if (unk18 != 0)
    {
        func_002F2890(unk18);
    }

    unk64 = 4;
}

/**
 * @brief Run one step of the selected card slot's two-step check.
 * @return Zero while the check runs, one once it passed, or -1 on failure.
 */
s32 CmcClass18AFB0::func_0035AE70()
{
    s32 result = 0;
    s32 failed = 0;

    switch (unk20)
    {
    case 0:
        if (func_004325A0(card, selected) == -1)
        {
            result = -1;
        }
        else
        {
            unk20++;
        }

        break;
    case 1:
        result = lib_memory_card_get_result(card, selected, &failed);

        if (result == 0)
        {
            if (failed != 0)
            {
                result = -1;
            }
        }
        else if (result == 1)
        {
            if (failed == 0)
            {
                result = 1;
            }
            else
            {
                result = -1;
            }

            unk20++;
        }

        break;
    }

    return result;
}

/**
 * @brief Reset the state for a new run starting at unk1e = value.
 * @param value Starting value for unk1e.
 */
void CmcClass18AFB0::func_0035AF60(s16 value)
{
    unk20 = 0;
    unk1e = value;
    unk22 = 0;
    unk39 = 0;
    unk34 = 0;
    unk30 = -1;
}

/**
 * @brief Read the selected card slot's formatted flag.
 * @return Formatted flag.
 */
s32 CmcClass18AFB0::func_0035AF80()
{
    return card->slots[selected].formatted;
}

/**
 * @brief Read the selected card slot's free space.
 * @return Free space.
 */
s32 CmcClass18AFB0::func_0035AFA0()
{
    return card->slots[selected].free_space;
}

/**
 * @brief Read unk22.
 * @return Stored value.
 */
s16 CmcClass18AFB0::func_0035AFC0()
{
    return unk22;
}

/**
 * @brief Read a card slot's state.
 * @param index Card slot.
 * @return Card state.
 */
s32 CmcClass18AFB0::func_0035AFD0(s16 index)
{
    return card->slots[index].card_state;
}

/**
 * @brief Create the memory card and the Field object and open both card slots.
 * @return One on success, or zero when an allocation or the Field object's setup fails.
 */
u8 CmcClass18AFB0::func_0035AFF0()
{
    card = new (0) LibMemoryCard;

    if (card == 0)
    {
        return 0;
    }

    lib_memory_card_init(card, g_update_list);
    lib_memory_card_open_slot(card, 0, 0, 0);
    lib_memory_card_open_slot(card, 1, 1, 0);
    unk18 = new (0) FieldClass15B9C0;

    if (unk18 == 0)
    {
        return 0;
    }

    if (func_002F2470(unk18, 0) == 0)
    {
        return 0;
    }

    unk1e = 0;
    return 1;
}

/** @brief Release the Field object and the memory card, then queue the handler for release. */
void CmcClass18AFB0::destroy()
{
    if (unk18 != 0)
    {
        if (unk18 != 0)
        {
            delete unk18;
            unk18 = 0;
        }
    }

    if (card != 0)
    {
        card->destroy();
    }

    resident_enqueue_object(g_resident_release_queues, this);
}

/** @brief Destroy the handler. */
CmcClass18AFB0::~CmcClass18AFB0()
{
}

/** @brief Initialize the handler with nothing selected. */
CmcClass18AFB0::CmcClass18AFB0()
{
    card = 0;
    unk18 = 0;
    unk22 = 0;
    unk1e = -1;
    unk20 = 0;
    selected = -1;
    unk24 = -1;
    unk28 = 0;
    unk2c = 0;
    unk34 = 0;
    unk36 = 0;
    unk38 = 0;
    unk39 = 0;
    unk3c = 0;
    unk40 = 0;
    unk48 = 0;
    mode = 0;
    unk44 = 0;
    unk42[0] = 0x80;
    unk42[1] = 0x80;
    unk46 = 0;
    unk49 = 0;
    unk4c = 0;
    unk50 = 0;
    unk54 = 0;
    unk30 = -1;
    unk60 = 0;
    unk58 = -1;
    unk5c = -1;
    unk64 = 0;
    unk69 = 0;
}
