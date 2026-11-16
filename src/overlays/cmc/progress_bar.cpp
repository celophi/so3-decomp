#include "include_asm.h"
#include "overlays/cmc/cmc.h"
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

extern "C" {
extern void lib_draw_buffer_end(LibDrawBuffer* buffer, u8 mode, float distance, s32 flag);

extern LibDisplayManager* g_scene_display_manager;
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
void CardProgressBar::destroy()
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
void CardProgressBar::func_00348520(s32 done, s32 total)
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
void CardProgressBar::func_003492E0(s32 width, s32 height, u32 color, s32 mode)
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

void LibOrientedTransform::set_translation_vector(const LibVector4* value)
{
    transform_dirty = 1;
    copy_vector(&translation, value);
}

/** @brief Destroy the child and the object. */
CardProgressBar::~CardProgressBar()
{
    if (model != 0)
    {
        // TODO: called through LibListObject so LibModelBase's inline destroy isn't emitted here
        static_cast<LibListObject*>(model)->destroy();
    }
}
