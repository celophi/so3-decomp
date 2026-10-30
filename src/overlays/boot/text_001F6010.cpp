#include "include_asm.h"
#include "overlays/boot/text_001F6010.h"
#include "overlays/boot/text_001FB220.h"
#include "overlays/boot/text_001FF9D0.h"
#include "overlays/boot/resident.h"
#include "overlays/lib/render_buffer.h"

/** GIF register descriptors and GS register addresses the fade packet uses. */
enum
{
    GIF_REGISTER_AD = 0xE,
    GIF_REGISTER_UV = 0x3,
    GIF_REGISTER_XYZ2 = 0x5,
    GS_REGISTER_PRIM = 0x00,
    GS_REGISTER_RGBAQ = 0x01,
    GS_REGISTER_TEX0_2 = 0x07,
    GS_REGISTER_TEXFLUSH = 0x3F,
    GS_REGISTER_BITBLTBUF = 0x50,
    GS_REGISTER_TRXPOS = 0x51,
    GS_REGISTER_TRXREG = 0x52,
    GS_REGISTER_TRXDIR = 0x53
};

extern "C" {
extern void* D_001B663C;
u32 func_4D93A0(void* heap, BootVramRequest* request, u32 tag, s32 count, s32 unk4, s32 unk5, s32 unk6, s32 unk7);
u8* func_11F860(ResidentPacket* packet, s32 quadwords);
u8* func_11F830(ResidentPacket* packet, u8* cursor);

extern void func_4D00B0(void* object);
void func_4D6430(BootModel* model, LibDrawBuffer* buffer);
extern void* D_001B6630;
void func_4333A0(BootImageStrip* image, u8* data, s16 address, s16 width, s32 first, s16 x, s32 second, s32 strip_width, s16 height);

extern const char g_new_game_node_name[];
extern const char g_continue_node_name[];
extern const char g_battle_collection_node_name[];
extern const char g_install_node_name[];
extern const char g_title_camera_node_name[];
void func_455DF0(LibDrawBuffer* buffer, s32 first, s32 second);
void func_455040(LibDrawBuffer* buffer, const BootTextureResource* resource);
void func_455150(LibDrawBuffer* buffer, BootDrawSettings* settings);
void func_4550F0(LibDrawBuffer* buffer, s32 count);
void func_455BD0(LibDrawBuffer* buffer, u8 mode, float distance, s32 flag);
void func_4791F0(BootScene* scene, u8* data);
void func_40B3A0(u8* data);
void func_473AA0(BootScene* scene);
s32 func_112610(BootSound1B65F8* sound, s32 key);

void func_11F510(void* owner, void* object);
}

/**
 * @brief Find the scene node of a title menu item.
 * @param menu Title menu.
 * @param item Item number, from 0 to 3.
 * @return The item's node, or null if the scene has none.
 */
static inline BootClass170F30* find_menu_item(BootTitleMenu* menu, s32 item)
{
    BootClass170F30* node;

    switch (item)
    {
    case 0:
        node = lib_find_renderable_entry(menu->scene, g_new_game_node_name);
        break;
    case 1:
        node = lib_find_renderable_entry(menu->scene, g_continue_node_name);
        break;
    case 2:
        node = lib_find_renderable_entry(menu->scene, g_battle_collection_node_name);
        break;
    case 3:
        node = lib_find_renderable_entry(menu->scene, g_install_node_name);
        break;
    }

    return node;
}

/**
 * @brief Grow and pulse the selected item and ease the others back to normal.
 * @param snap Nonzero to put the selected item straight at full size.
 */
void BootTitleMenu::animate_items(u8 snap)
{
    if (scene == 0)
    {
        return;
    }

    for (s32 item = 0; item < 4; item++)
    {
        BootClass170F30* node = find_menu_item(this, item);

        if (node == 0)
        {
            continue;
        }

        if (item == selected)
        {
            BootVector4DDAA0 value;
            copy_vector(&value, &node->scale);

            if (value.x < 1.08f && !snap)
            {
                value.x += 0.02f * D_001B6688;
                value.y += 0.02f * D_001B6688;
                value.z += 0.02f * D_001B6688;
            }
            else
            {
                value.x = 1.1f;
                value.y = 1.1f;
                value.z = 1.1f;
            }

            node->set_scale_vector(&value);
            copy_vector(&value, &node->base_color_factor);

            if (value.w > 0.9f)
            {
                if (!pulse_up)
                {
                    value.x -= 0.01f * D_001B6688;
                    value.y -= 0.005f * D_001B6688;

                    if (value.y < 0.5f)
                    {
                        value.y = 0.5f;
                    }

                    if (value.x < 0.5f)
                    {
                        value.x = 0.5f;
                        pulse_up = 1;
                    }
                }
                else if (pulse_up)
                {
                    value.x += 0.01f * D_001B6688;
                    value.y += 0.005f * D_001B6688;

                    if (value.y > 1.0f)
                    {
                        value.y = 1.0f;
                    }

                    if (value.x > 1.0f)
                    {
                        value.x = 1.0f;
                        pulse_up = 0;
                    }
                }

                copy_vector(&node->base_color_factor, &value);
                node->update_combined_color_factor();
            }
        }
        else
        {
            BootVector4DDAA0 value;
            copy_vector(&value, &node->scale);

            if (value.x > 1.05f)
            {
                value.x -= 0.05f * D_001B6688;
                value.y -= 0.05f * D_001B6688;
                value.z -= 0.05f * D_001B6688;
            }
            else
            {
                value.x = 1.0f;
                value.y = 1.0f;
                value.z = 1.0f;
            }

            node->set_scale_vector(&value);
            copy_vector(&value, &node->base_color_factor);

            if (value.x < 1.0f)
            {
                value.x += 0.025f * D_001B6688;
                value.y += 0.05f * D_001B6688;

                if (value.x > 1.0f)
                {
                    value.x = 1.0f;
                }

                if (value.y > 1.0f)
                {
                    value.y = 1.0f;
                }
            }

            copy_vector(&node->base_color_factor, &value);
            node->update_combined_color_factor();
        }
    }
}

/**
 * @brief Work out the screen position of the cursor beside the selected item.
 * @param x Receives the horizontal position, or zero if the item has no node.
 * @param y Receives the vertical position, or zero if the item has no node.
 */
void BootTitleMenu::get_cursor_position(float* x, float* y)
{
    BootSystemSettings* settings = (BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1);
    BootClass170F30* node = find_menu_item(this, selected);

    if (node == 0)
    {
        *x = 0.0f;
        *y = 0.0f;
        return;
    }

    if (!node->matrix_ready)
    {
        node->update_transform_matrix();
    }

    float screen_x = node->unkD0.vectors[0].w;
    float screen_y = node->unkD0.vectors[1].w;

    if (settings->widescreen)
    {
        *x = 319.0f + 0.75f * screen_x;
        *y = 224.0f + screen_y;
    }
    else
    {
        *x = 320.0f + screen_x;
        *y = 224.0f + screen_y;
    }

    if (selected == 1)
    {
        *x -= 6.0f;
    }

    if (selected < 4)
    {
        *y += 24.0f;
    }
}

/** @brief Dim Continue and Battle Collection unless a memory card holds the data they need. */
void BootTitleMenu::update_item_availability()
{
    if (scene == 0)
    {
        return;
    }

    BootClass170F30* continue_node;
    BootInput* input = g_boot_program.input;
    u32 slot1 = input->slot1_state;
    u32 slot2 = input->slot2_state;
    u32 first = input->slot1_raw_state;
    u32 second = input->slot2_raw_state;
    continue_node = lib_find_renderable_entry(scene, g_continue_node_name);

    if (continue_node == 0)
    {
        return;
    }

    BootClass170F30* collection_node = lib_find_renderable_entry(scene, g_battle_collection_node_name);

    if (collection_node == 0)
    {
        return;
    }

    BootVector4DDAA0 color;
    copy_vector(&color, &collection_node->base_color_factor);

    if (first == 5 || second == 5)
    {
        color.w = 1.0f;
        collection_ready = 1;
        copy_vector(&collection_node->base_color_factor, &color);
        collection_node->update_combined_color_factor();
    }
    else
    {
        color.x = 1.0f;
        color.y = 1.0f;
        color.z = 1.0f;
        color.w = 0.5f;
        collection_ready = 0;
        copy_vector(&collection_node->base_color_factor, &color);
        collection_node->update_combined_color_factor();
    }

    copy_vector(&color, &continue_node->base_color_factor);

    if (slot1 == 0x11 || slot2 == 0x11)
    {
        color.w = 1.0f;
        continue_ready = 1;
        copy_vector(&continue_node->base_color_factor, &color);
        continue_node->update_combined_color_factor();
    }
    else
    {
        color.x = 1.0f;
        color.y = 1.0f;
        color.z = 1.0f;
        color.w = 0.5f;
        continue_ready = 0;
        copy_vector(&continue_node->base_color_factor, &color);
        continue_node->update_combined_color_factor();
    }
}

/** @brief Run the menu state machine. */
void BootTitleMenu::update()
{
    BootSystemSettings* settings;
    BootInput* input = g_boot_program.input;
    settings = (BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1);

    switch (step)
    {
    case 0:
    {
        if (func_102D00(D_001B65E8) == 0)
        {
            break;
        }

        if ((((u32)g_boot_program.message_block + 0x7F) & ~0x7F) == 0)
        {
            break;
        }

        check_main_code();
        scene = new (0) BootScene;
        func_4791F0(scene, scene_data);
        func_474010(scene, g_boot_program.display, D_001B6614, D_001B6624, D_001B6628, D_001B661C, 1);
        delete[] scene_data;
        scene_data = 0;
        func_40B3A0(game_data);
        delete[] game_data;
        game_data = 0;
        camera = lib_find_camera_entry(scene, g_title_camera_node_name);
        D_001B6628->current_display = camera;

        if (initial_item != -1)
        {
            selected = initial_item;
        }
        else if (input->slot1_state == 0x11 || input->slot2_state == 0x11)
        {
            selected = 1;
        }
        else
        {
            selected = 0;
        }

        animate_items(1);
        D_001B661C->prepend_node(new (0) BootClass179150, -1);
        float x;
        float y;
        get_cursor_position(&x, &y);
        cursor = new (0) BootSelectionCursor;
        func_467570(cursor, 1, 0, 0, x, y, 0.0f);
        func_465B20(D_001B657C, cursor);
        step++;
        break;
    }
    case 1:
        if (func_112990(D_001B65F8, 2, 1, 0, 0) == 0)
        {
            break;
        }

        check_main_code();
        step++;
        idle_time = 0.0f;
        break;
    case 2:
    {
        check_main_code();

        if (input->repeated == 0x80 && cursor->unk35)
        {
            selected--;

            if (selected > 2)
            {
                selected = 2;
            }

            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->func_00466E40(x, y, 0.05f);
            pulse_up = 0;
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
        }

        if (input->repeated == 0x20 && cursor->unk35)
        {
            selected++;

            if (selected > 2)
            {
                selected = 0;
            }

            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->func_00466E40(x, y, 0.05f);
            func_112400(D_001B65F8, 0, 0, 0, 0x7F, 0x40, 0);
        }

        idle_time += D_001B6690;

        if (input->pressed & settings->confirm_buttons)
        {
            u8 accepted = 0;

            if (selected == 0)
            {
                step++;
                accepted = 1;
            }

            if (selected == 1 && continue_ready)
            {
                settings->continue_selected = 1;
                accepted = 1;
                step = 5;
            }

            if (selected == 2 && collection_ready)
            {
                accepted = 1;
                step = 7;
            }

            if (selected == 3 && install_ready)
            {
                accepted = 1;
                step = 6;
            }

            if (accepted)
            {
                queue_fade();
                func_10F000(D_001B65F8, 0x1E, -1);
                func_112400(D_001B65F8, 1, 0, 0, 0x7F, 0x40, 0);
            }
            else
            {
                func_112400(D_001B65F8, 3, 0, 0, 0x7F, 0x40, 0);
            }
        }
        else if (!(idle_time < 45.0f) && func_112610(D_001B65F8, -1) == 0 && func_115270(D_001B65E4, 1) == 1)
        {
            queue_fade();
            func_10F000(D_001B65F8, 0x1E, -1);
            step = 4;
        }

        break;
    }
    case 3:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        D_001B6614->append_node(new (0) BootNewGameSettings, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case 4:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        func_10F000(D_001B65F8, 0, -1);
        D_001B6614->append_node(new (0) BootOpeningMovie, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case 5:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        D_001B6614->append_node(new (0) BootGameLauncher, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case 6:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        D_001B6614->append_node(new (0) BootInstaller, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case 7:
    {
        check_main_code();
        g_boot_program.select_projection();
        step++;
        func_473AA0(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        u8* block = new (0) u8[func_10CE00()];
        D_001B6614->append_node(new (0) BootBattleTrophyViewer, -1);
        delete block;
        lib_object_detach_owner(this);
        destroy();
        break;
    }
    }

    update_item_availability();
    animate_items(0);

    if (step > 0)
    {
        check_main_code();
    }
}

/** @brief Free the resource buffers, then destroy the scene and its model. */
BootTitleMenu::~BootTitleMenu()
{
    delete[] scene_data;
    delete[] game_data;

    if (scene != 0)
    {
        scene->destroy();
    }

    if (cursor != 0)
    {
        cursor->destroy();
    }
}

/**
 * @brief Queue the scene resources and remember the item to start on.
 * @param initial_item Item to select first, or -1 to pick Continue when a card holds a save.
 */
BootTitleMenu::BootTitleMenu(s32 initial_item)
{
    step = 0;
    scene_data = func_139700(0x40, func_11C8C0(D_001B65E4, 0x27));
    func_103E70(D_001B65E8, 0x27, scene_data, 1, 0x34BC0, 0, 0, 0, 1);
    game_data = func_139700(0x40, func_11C8C0(D_001B65E4, 0xA));
    func_103E70(D_001B65E8, 0xA, game_data, 1, 0x34BC0, 0, 0, 0, 1);
    scene = 0;
    cursor = 0;
    pulse_up = 0;
    continue_ready = 0;
    install_ready = 0;
    collection_ready = 0;
    this->initial_item = initial_item;
    g_boot_program.trophy_card->set_mode(2);
}

/** @brief Detach the bar and its model, destroy the model and delete the bar. */
void BootProgressBar::destroy()
{
    lib_object_detach_owner(this);

    if (model != 0)
    {
        lib_object_detach_owner(this);
        model->destroy();
    }

    model = 0;
    delete this;
}

/**
 * @brief Append one vertex to a draw buffer's streams.
 * @param buffer Draw buffer.
 * @param position Vertex position.
 * @param unk Value for the second vector stream.
 * @param texcoord Packed texture coordinates.
 * @param color Vertex color.
 */
static inline void add_vertex(LibDrawBuffer* buffer, const FieldVec4A& position, const FieldVec4A& unk, u32 texcoord, u32 color)
{
    *buffer->positions = position;
    buffer->positions++;
    *buffer->unk4c = unk;
    buffer->unk4c++;
    *buffer->texcoords++ = texcoord;
    *buffer->colors++ = color;
    buffer->vertex_count++;
}

/**
 * @brief Draw a progress bar: a dark border, the bar outline and a fill proportional to done / total.
 * @param bar Progress bar to draw.
 * @param done Completed amount; clamped to total.
 * @param total Total amount.
 */
void progress_bar_draw(BootProgressBar* bar, s32 done, s32 total)
{
    BootDrawSettings settings;
    s32 fill;

    func_455DF0(bar->draw_buffer, 0, 1);
    init_draw_settings(&settings);
    settings.prim = 0xC;
    settings.unk02 = 0;
    settings.unk05 = 1;
    settings.unk06 = 0;
    FieldVec4A normal(0.0f, 0.0f, -1.0f, 1.0f);

    if (total < done)
    {
        done = total;
    }

    if (total > 999)
    {
        fill = done / (total / 1000);
    }
    else
    {
        fill = done * 1000 / total;
    }

    func_455150(bar->draw_buffer, &settings);
    s32 width = bar->width;
    s32 height = bar->height;
    u32 color = bar->color;
    s32 depth = bar->mode;
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(-2.0f, -1.0f, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(bar->draw_buffer, FieldVec4A(2.0f + width, -1.0f, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(bar->draw_buffer, FieldVec4A(-2.0f, 1.0f + height, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(bar->draw_buffer, FieldVec4A(2.0f + width, 1.0f + height, (float)depth, 1.0f), normal, 0, 0x80301004);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, 1.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, 1.0f, (float)depth, 1.0f), normal, 0, color);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, height - 1.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, height - 1.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, (float)height, (float)depth, 1.0f), normal, 0, color);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(-1.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(-1.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(width - 1.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f + width, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(width - 1.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f + width, (float)height, (float)depth, 1.0f), normal, 0, color);
    func_4550F0(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(3.0f, 3.0f, (float)depth, 1.0f), normal, 0, color);
    float right = 3.0f + ((width - 6.0f) * fill) / 1000.0f;
    add_vertex(bar->draw_buffer, FieldVec4A(right, 3.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(3.0f, height - 3.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(right, height - 3.0f, (float)depth, 1.0f), normal, 0, color);
    func_455BD0(bar->draw_buffer, 0, 1.0f, 0);
}

/**
 * @brief Initialize the settings record to its default values.
 * @param settings Settings record to initialize.
 */
void init_draw_settings(BootDrawSettings* settings)
{
    settings->prim = 0xC;
    settings->texture_index = 0;
    settings->unk02 = 0;
    settings->unk04 = 0;
    settings->unk05 = 0;
    settings->unk06 = 1;
    settings->unk07 = 1;
    settings->unk08 = 1.0f;
    settings->unk0C = 1.0f;
    settings->unk10 = 0.5f;
    settings->unk18 = 0;
    settings->unk19 = 0;
    settings->unk1A = 0;
    settings->unk1B = 0;
    settings->unk1C = 0;
    settings->unk14 = 0.0f;
}

/**
 * @brief Recreate the bar's draw buffer and model, then draw it empty and show it.
 * @param bar Progress bar.
 * @param width Bar width.
 * @param height Bar height.
 * @param color Bar color.
 * @param mode Draw mode.
 */
void progress_bar_reset(BootProgressBar* bar, s32 width, s32 height, u32 color, s32 mode)
{
    if (bar->draw_buffer != 0)
    {
        delete bar->draw_buffer;
    }

    if (bar->model != 0)
    {
        bar->model->destroy();
    }

    bar->draw_buffer = new (0) LibDrawBuffer;
    bar->model = new (0) BootModel;
    bar->draw_buffer->allocate_storage(2, 0x600, 1, 8);
    bar->width = width;
    bar->height = height;
    bar->color = color;
    bar->mode = mode;
    progress_bar_draw(bar, 0, 1);
    func_4D6430(bar->model, bar->draw_buffer);
    bar->model->unk80 = D_001B6630;
    bar->model->draw_flags |= BOOT_DRAW_FLAG_0400;
    D_001B661C->append_node(bar->model, -1);
}

/** @brief Destroy the bar's model, then the bar. */
BootProgressBar::~BootProgressBar()
{
    if (model != 0)
    {
        model->destroy();
    }
}

/** @brief Clear the bar's model and state. */
BootProgressBar::BootProgressBar()
{
    draw_buffer = 0;
    model = 0;
}

/** @brief Fade out; once transparent, destroy the strips and the fade. */
void BootScreenFade::update()
{
    alpha -= fade_speed * D_001B6690;

    if (alpha <= 0.0f)
    {
        for (s32 i = 0; i < 10; i++)
        {
            if (images[i] != 0)
            {
                lib_object_detach_owner(images[i]);
                images[i]->destroy();
                images[i] = 0;
            }
        }

        lib_object_detach_owner(this);
        destroy();
    }
}

/**
 * @brief Mark the fade inactive and run the Lib release helper.
 * @param value Unused.
 */
void BootScreenFade::on_packet_complete(u32 value)
{
    dma_pending = 0;
    func_4D00B0(this);
}

/** @brief Mark the fade active and submit its packet. */
void BootScreenFade::render()
{
    dma_pending = 1;
    func_11F510(packet, static_cast<BootDmaCallbacks*>(this));
}

/**
 * @brief Build the fade's GS packet: upload each of the ten strips to VRAM and draw it as a sprite at the fade's
 * alpha. The first call only arms the fade.
 * @param matrix Matrix supplied by the caller; unused.
 * @param context Opaque caller context; unused.
 */
void BootScreenFade::build_packet(const void* matrix, void* context)
{
    if (!armed)
    {
        armed = 1;
        return;
    }

    BootPacketBuffer* buffer_packet = packet;
    buffer_packet->unk08 = buffer_packet->unk00 + 0x40;
    buffer_packet->unk0c = buffer_packet->unk08;
    BootFadeStripPacket* strip = reinterpret_cast<BootFadeStripPacket*>(func_11F860(packet, 0));
    BootVramRequest request;
    request.width = 64;
    request.height = 448;
    request.size = 0x1C000;
    request.psm = 1;
    request.width_log2 = 6;
    request.height_log2 = 10;
    u32 address = func_4D93A0(D_001B663C, &request, 0x54744664, 1, 0, 0, 1, 0);

    if (address != 0)
    {
        u32 base = address >> 6;
        float top = 1824.0f;
        float bottom = 2272.0f;
        float left = 1728.0f;
        float width = 64.0f;

        for (s32 i = 0; i < 10; i++)
        {
            u8* image = buffer + 448 * (i * 64) * 3 / 16 * 16;
            strip->transfer_dma = 0x10000006;
            strip->transfer_tag.tag = 0x1000000000000004ULL;
            strip->transfer_tag.registers = 0;
            strip->transfer_tag.fields.register0 = GIF_REGISTER_AD;
            strip->bitbltbuf = ((u64)base << 32) | 0x0101000000000000ULL;
            strip->bitbltbuf_register = GS_REGISTER_BITBLTBUF;
            strip->trxpos = 1;
            strip->trxpos_register = GS_REGISTER_TRXPOS;
            strip->trxreg = 0x000001C000000040ULL;
            strip->trxreg_register = GS_REGISTER_TRXREG;
            strip->trxdir = 0;
            strip->trxdir_register = GS_REGISTER_TRXDIR;
            strip->image_tag = 0x1800000000001500ULL;
            strip->image_dma = ((u64)(u32)image << 32) | 0x30001500;
            strip->draw_dma = 0x10000008;
            strip->draw_tag.tag = 0x1000000000008004ULL;
            strip->draw_tag.registers = 0;
            strip->draw_tag.fields.register0 = GIF_REGISTER_AD;
            strip->texflush = 0;
            strip->texflush_register = GS_REGISTER_TEXFLUSH;
            strip->tex0 = base | 0x0000000298104000ULL;
            strip->tex0_register = GS_REGISTER_TEX0_2;
            strip->prim = 0x356;
            strip->prim_register = GS_REGISTER_PRIM;
            u32 color = 0x808080;
            color |= (s32)(128.0f * alpha) << 24;
            strip->rgbaq = color;
            strip->rgbaq_register = GS_REGISTER_RGBAQ;
            strip->sprite_tag.tag = 0x4400000000008001ULL;
            strip->sprite_tag.registers = 0;
            strip->sprite_tag.fields.register0 = GIF_REGISTER_UV;
            strip->sprite_tag.fields.register1 = GIF_REGISTER_XYZ2;
            strip->sprite_tag.fields.register2 = GIF_REGISTER_UV;
            strip->sprite_tag.fields.register3 = GIF_REGISTER_XYZ2;
            strip->uv0 = 0x80008;
            strip->xyz0 = ((u64)(s32)(top * 16.0f) << 16) | (u64)((s32)(left + i * width) << 4) | ((u64)0xFFFFFF << 32);
            strip->uv1 = 0x1C080408;
            strip->xyz1 = ((u64)(s32)(bottom * 16.0f) << 16) | (u64)((s32)(left + (1.0f + i) * width) << 4) | ((u64)0xFFFFFF << 32);
            strip++;
        }

        *reinterpret_cast<u64*>(strip) = 0x70000000;
        func_11F830(packet, reinterpret_cast<u8*>(strip) + 0x10);
        unk63 = 1;
    }
}

/** @brief Destroy the strips, the copy buffer and the packet. */
BootScreenFade::~BootScreenFade()
{
    for (s32 i = 0; i < 10; i++)
    {
        if (images[i] != 0)
        {
            lib_object_detach_owner(images[i]);
            images[i]->destroy();
        }
    }

    delete[] buffer;
    delete packet;
}

/** @brief Release the packet storage unless it is external. */
BootPacketBuffer::~BootPacketBuffer()
{
    if (!unk14)
    {
        delete unk04;
    }
}

#include "overlays/boot/transform_inlines.h"

/**
 * @brief Copy the display into ten strips and show them, fully opaque.
 * @param display Display to copy.
 */
BootScreenFade::BootScreenFade(BootDimensionsACD0* display)
{
    s32 width;
    s32 height;
    s32 i;
    this->display = display;
    width = display->unk3C60.width / 2 + display->unk3C60.width / 2;
    height = display->unk3C60.height / 2 + display->unk3C60.height / 2;
    buffer = new (0) u8[width * height * 3 / 16 * 16];

    for (i = 0; i < 10; i++)
    {
        images[i] = new (0) BootImageStrip;
        images[i]->unk65 = 1;
        func_4333A0(images[i], buffer + height * (i * 64) * 3 / 16 * 16, (display->unk160 & 0x1FF) << 5, width / 64, 1, i * 64, 0, 0x40, height);
        D_001B661C->append_node(images[i], -1);
    }

    set_type_id(0x4000);
    unk65 = 1;
    set_draw_flags(BOOT_DRAW_FLAG_0400);
    packet = new (0) BootPacketBuffer(0x400);
    alpha = 1.0f;
    fade_speed = 1.0f;
    armed = 0;
}

/** @brief Detach the image and its model, destroy the model and delete the image. */
void BootImage::destroy()
{
    lib_object_detach_owner(this);

    if (model != 0)
    {
        lib_object_detach_owner(this);
        model->destroy();
    }

    model = 0;
    delete this;
}

/**
 * @brief Build an image's quad from a rectangle of its texture and a rectangle of its palette, and queue the
 * model for drawing.
 * @param image Image to build.
 * @param x Left edge of the texture rectangle, in texels.
 * @param y Top edge of the texture rectangle.
 * @param width Rectangle width, which is also the quad's width.
 * @param height Rectangle height, which is also the quad's height.
 * @param palette_x Left edge of the palette rectangle.
 * @param palette_y Top edge of the palette rectangle.
 * @param palette_width Palette rectangle width.
 * @param palette_height Palette rectangle height.
 * @param color Vertex color.
 * @param depth Z position of the quad.
 */
void image_set_rectangle_with_palette(BootImage* image, s32 x, s32 y, s32 width, s32 height, s32 palette_x, s32 palette_y, s32 palette_width,
                                      s32 palette_height, u32 color, s32 depth)
{
    BootDrawSettings settings;

    func_455DF0(image->draw_buffer, 1, 1);
    init_draw_settings(&settings);
    settings.unk06 = 0;
    settings.unk02 = 2;
    settings.prim = 0x5C;
    settings.unk05 = 1;
    FieldVec4A normal(0.0f, 0.0f, -1.0f, 1.0f);
    func_455150(image->draw_buffer, &settings);
    func_4550F0(image->draw_buffer, 4);

    if (image->centered)
    {
        float half_width = 0.5f * (float)width;
        float half_height = 0.5f * (float)height;
        add_vertex(image->draw_buffer, FieldVec4A(-half_width, -half_height, (float)depth, 1.0f), normal,
                   ((x << 12) / image->texture_width) | (((y << 12) / image->texture_height) << 16), color);
        add_vertex(image->draw_buffer, FieldVec4A(half_width, -half_height, (float)depth, 1.0f), normal,
                   (((y << 12) / image->texture_height) << 16) | (((x + width) << 12) / image->texture_width), color);
        add_vertex(image->draw_buffer, FieldVec4A(-half_width, half_height, (float)depth, 1.0f), normal,
                   ((x << 12) / image->texture_width) | ((((y + height) << 12) / image->texture_height) << 16), color);
        add_vertex(image->draw_buffer, FieldVec4A(half_width, half_height, (float)depth, 1.0f), normal,
                   (((x + width) << 12) / image->texture_width) | ((((y + height) << 12) / image->texture_height) << 16), color);
    }
    else
    {
        add_vertex(image->draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal,
                   ((x << 12) / image->texture_width) | (((y << 12) / image->texture_height) << 16), color);
        // TODO: right as its own variable shifted in place is a guess; it's what gets the
        // sum and its shift to share a register like the original.
        s32 right = x + width;
        right = (u32)right << 12;
        add_vertex(image->draw_buffer, FieldVec4A((float)width, 0.0f, (float)depth, 1.0f), normal,
                   (((y << 12) / image->texture_height) << 16) | (right / image->texture_width), color);
        add_vertex(image->draw_buffer, FieldVec4A(0.0f, (float)height, (float)depth, 1.0f), normal,
                   ((x << 12) / image->texture_width) | ((((y + height) << 12) / image->texture_height) << 16), color);
        add_vertex(image->draw_buffer, FieldVec4A((float)width, (float)height, (float)depth, 1.0f), normal,
                   (right / image->texture_width) | ((((y + height) << 12) / image->texture_height) << 16), color);
    }

    if (image->has_palette)
    {
        settings.unk05 = 0;
        settings.texture_index = 1;
        func_455150(image->draw_buffer, &settings);
        func_4550F0(image->draw_buffer, 4);

        if (image->centered)
        {
            float half_width = 0.5f * (float)palette_width;
            float half_height = 0.5f * (float)palette_height;
            add_vertex(image->draw_buffer, FieldVec4A(-half_width, -half_height, (float)depth, 1.0f), normal,
                       (((palette_y << 12) / image->palette_height) << 16) | (((palette_x + palette_width) << 12) / image->palette_width), color);
            add_vertex(image->draw_buffer, FieldVec4A(half_width, -half_height, (float)depth, 1.0f), normal,
                       ((palette_x << 12) / image->palette_width) | (((palette_y << 12) / image->palette_height) << 16), color);
            add_vertex(image->draw_buffer, FieldVec4A(-half_width, half_height, (float)depth, 1.0f), normal,
                       (((palette_x + palette_width) << 12) / image->palette_width) | ((((palette_y + palette_height) << 12) / image->palette_height) << 16),
                       color);
            add_vertex(image->draw_buffer, FieldVec4A(half_width, half_height, (float)depth, 1.0f), normal,
                       ((palette_x << 12) / image->palette_width) | ((((palette_y + palette_height) << 12) / image->palette_height) << 16), color);
        }
        else
        {
            add_vertex(image->draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal,
                       (((palette_y << 12) / image->palette_height) << 16) | (((palette_x + palette_width) << 12) / image->texture_width), color);
            add_vertex(image->draw_buffer, FieldVec4A((float)palette_width, 0.0f, (float)depth, 1.0f), normal,
                       ((palette_x << 12) / image->texture_width) | (((palette_y << 12) / image->texture_height) << 16), color);
            add_vertex(image->draw_buffer, FieldVec4A(0.0f, (float)palette_height, (float)depth, 1.0f), normal,
                       (((palette_x + palette_width) << 12) / image->texture_width) | ((((palette_y + palette_height) << 12) / image->texture_height) << 16),
                       color);
            add_vertex(image->draw_buffer, FieldVec4A((float)palette_width, (float)palette_height, (float)depth, 1.0f), normal,
                       ((palette_x << 12) / image->texture_width) | ((((palette_y + palette_height) << 12) / image->palette_height) << 16), color);
        }
    }

    func_455BD0(image->draw_buffer, image->unk2c, 500.0f, 0);
    func_4D6430(image->model, image->draw_buffer);
    image->model->unk80 = D_001B6630;
    image->model->draw_flags |= BOOT_DRAW_FLAG_0400;
    D_001B661C->append_node(image->model, -1);
}

/**
 * @brief Build the image's quad from a rectangle of its texture and queue the model for drawing.
 * @param x Left edge of the rectangle in the texture, in texels.
 * @param y Top edge of the rectangle in the texture.
 * @param width Rectangle width, which is also the quad's width.
 * @param height Rectangle height, which is also the quad's height.
 * @param color Vertex color.
 * @param depth Z position of the quad.
 */
void BootImage::set_rectangle(s32 x, s32 y, s32 width, s32 height, u32 color, s32 depth)
{
    BootDrawSettings settings;

    func_455DF0(draw_buffer, 0, 1);
    init_draw_settings(&settings);
    settings.unk06 = 0;
    settings.unk02 = 2;
    settings.prim = 0x5C;
    settings.unk05 = 1;
    func_455150(draw_buffer, &settings);
    func_4550F0(draw_buffer, 4);
    FieldVec4A normal(0.0f, 0.0f, -1.0f, 1.0f);

    if (centered)
    {
        float half_width = 0.5f * (float)width;
        float half_height = 0.5f * (float)height;
        add_vertex(draw_buffer, FieldVec4A(-half_width, -half_height, (float)depth, 1.0f), normal,
                   ((x << 12) / texture_width) | (((y << 12) / texture_height) << 16), color);
        add_vertex(draw_buffer, FieldVec4A(half_width, -half_height, (float)depth, 1.0f), normal,
                   (((y << 12) / texture_height) << 16) | (((x + width) << 12) / texture_width), color);
        add_vertex(draw_buffer, FieldVec4A(-half_width, half_height, (float)depth, 1.0f), normal,
                   ((x << 12) / texture_width) | ((((y + height) << 12) / texture_height) << 16), color);
        add_vertex(draw_buffer, FieldVec4A(half_width, half_height, (float)depth, 1.0f), normal,
                   (((x + width) << 12) / texture_width) | ((((y + height) << 12) / texture_height) << 16), color);
    }
    else
    {
        add_vertex(draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal, ((x << 12) / texture_width) | (((y << 12) / texture_height) << 16), color);
        add_vertex(draw_buffer, FieldVec4A((float)width, 0.0f, (float)depth, 1.0f), normal,
                   (((y << 12) / texture_height) << 16) | (((x + width) << 12) / texture_width), color);
        add_vertex(draw_buffer, FieldVec4A(0.0f, (float)height, (float)depth, 1.0f), normal,
                   ((x << 12) / texture_width) | ((((y + height) << 12) / texture_height) << 16), color);
        add_vertex(draw_buffer, FieldVec4A((float)width, (float)height, (float)depth, 1.0f), normal,
                   (((x + width) << 12) / texture_width) | ((((y + height) << 12) / texture_height) << 16), color);
    }

    func_455BD0(draw_buffer, unk2c, 500.0f, 0);
    func_4D6430(model, draw_buffer);
    model->unk80 = D_001B6630;
    model->draw_flags |= BOOT_DRAW_FLAG_0400;
    D_001B661C->append_node(model, -1);
}

/**
 * @brief Recreate the image's draw buffer and model and upload a texture and optional palette.
 * @param texture Texture resource.
 * @param palette Palette resource, or null.
 */
void BootImage::set_texture(const BootTextureResource* texture, const BootTextureResource* palette)
{
    if (draw_buffer != 0)
    {
        delete draw_buffer;
    }

    if (model != 0)
    {
        model->destroy();
    }

    draw_buffer = new (0) LibDrawBuffer;
    model = new (0) BootModel;
    draw_buffer->allocate_storage(1, 0x600, 2, 8);
    func_455040(draw_buffer, texture);

    if (palette != 0)
    {
        func_455040(draw_buffer, palette);
    }

    const BootTextureImage* info = texture_image(texture);
    texture_width = 1 << info->width_log2;
    texture_height = 1 << info->height_log2;

    if (palette != 0)
    {
        info = texture_image(palette);
        palette_width = 1 << info->width_log2;
        palette_height = 1 << info->height_log2;
        has_palette = 1;
    }
}

/** @brief Destroy the image's model, then the image. */
BootImage::~BootImage()
{
    if (model != 0)
    {
        model->destroy();
    }
}

/** @brief Clear the image's model and state. */
BootImage::BootImage()
{
    draw_buffer = 0;
    model = 0;
    centered = 0;
    has_palette = 0;
    unk2c = 0;
}

/** @brief Draw in bucket 10 instead of the main list. */
void BootScreenFade::set_default_draw_bucket()
{
    draw_bucket = 10;
}

/** @brief Run the launch steps: seed, movie, load, hand over. */
void BootGameLauncher::update()
{
    BootSystemSettings* settings;
    BootInput* input = g_boot_program.input;
    settings = (BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1);
    u32 previous;

    switch (step)
    {
    case 0:
        previous = resident_next_random_word();

        while (previous == resident_next_random_word())
        {
        }

        previous = func_10CE00();

        while (previous == func_10CE00())
        {
        }

        previous = func_10CAA0(1000);

        while (previous == func_10CAA0(1000))
        {
        }

        previous = func_10CC40(0, 1000);

        while (previous == func_10CC40(0, 1000))
        {
        }

        if ((u8)settings->continue_selected == 0)
        {
            BootSealedRecord* record = &settings->sealed_record;
            func_13A678(record, 0, sizeof(BootSealedRecord));
            seal_record(record);
            BootTrophyFlags* bits = &settings->trophy_flags;
            s32 size = bits->size;

            for (s32 i = 0; i < size; i++)
            {
                bits->flag_bytes[i] = 0;
            }

            bits->trophy_key = resident_next_random_word();
            func_457520(bits);
        }

        if ((u8)settings->continue_selected == 0 && settings->sound_output == 2)
        {
            step++;
            timer = 0;
        }
        else
        {
            step = 5;
            timer = 0;
        }

        break;
    case 1:
        if (++timer > 60)
        {
            if (func_115430(D_001B65E4) == 0 && func_115670(D_001B65E4) != 0 && func_115650(D_001B65E4) != 0)
            {
                break;
            }

            movie_heap = new (0) BootResident113E40;
            movie_heap->unk2C = 0x40;
            func_113930(movie_heap, 0x579F2C);
            void* heap = resident_exchange_allocation_heap(movie_heap);
            player = new (0) BootMoviePlayer(640, 448);
            resident_exchange_allocation_heap(heap);
            player->state->set_scale(1.0f, 1.0f);
            player->state->set_words(0x800, 0x800, 1);

            if (((BootSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_runtime_owner()), 1))->widescreen)
            {
                player->state->unk80D8 = 1;
            }

            func_419A70(player, 13, 1);
            step++;
        }
        else if (input->held & 8)
        {
            step = 5;
        }

        break;
    case 2:
        timer++;

        if ((input->held & 8) || !player->is_playing)
        {
            step++;
        }

        break;
    case 3:
        func_41A210(player);
        player->destroy();
        player = 0;
        step++;
        break;
    case 4:
        delete movie_heap;
        movie_heap = 0;
        step++;
        break;
    case 5:
        program = func_139700(0x40, func_11C8C0(D_001B65E4, 0x42B));
        func_103E70(D_001B65E8, 0x42B, program, 1, 0x34BC0, 0, 0, 0, 1);
        step++;
        break;
    case 6:
        if (func_102D00(D_001B65E8) != 0 && ++timer > 40)
        {
            lib_object_detach_owner(this);
            destroy();
            g_boot_program.next_program = program;
            return;
        }

        break;
    }
}

/**
 * @brief Encode a saved record and seal it with a fresh checksum; a damaged record is wiped instead.
 * @param record Record to seal; an already sealed record is left alone.
 */
void seal_record(BootSealedRecord* record)
{
    s32 i;

    if (record->sealed == 0)
    {
        record->sealed = BOOT_RECORD_SEALED;
        record->unk00 ^= 0xD7;
        record->unk02 ^= 0xF393;
        record->unk04 ^= 0x7CE3C7F7;
        record->unk08 ^= 0x7CE3C7F7;
        record->unk0C ^= 0x7CE3C7F7;
        record->unk10 ^= 0x7CE3C7F7;
        record->unk14 ^= 0x7CE3C7F7;
        record->unk18 ^= 0x7CE3C7F7;
        record->unk1C ^= 0x7CE3C7F7;
        record->unk20 ^= 0x7CE3C7F7;
        record->unk24 ^= 0x7CE3C7F7;
        record->unk28 ^= 0x7CE3C7F7;
        record->unk2C ^= 0x7CE3C7F7;
        record->unk30 ^= 0x7CE3C7F7;
        record->unk34 ^= 0x7CE3C7F7;
        record->unk38 ^= 0x7CE3C7F7;
        record->unk3C ^= 0x7CE3C7F7;
        record->unk40 ^= 0x7CE3C7F7;
        record->unk44 ^= 0x7CE3C7F7;
        record->unk48 ^= 0x7CE3C7F7;
        record->unk4C ^= 0x7CE3C7F7;
        record->unk50 ^= 0x7CE3C7F7;
        record->unk54 ^= 0x7CE3C7F7;
        record->unk58 ^= 0x7CE3C7F7;

        for (i = 0; i < 76; i++)
        {
            record->unk64[i] ^= 0xD7;
        }

        record->key = resident_next_random_word();
        record->checksum = func_457470(record->key * 37, record, (u8*)&record->checksum - (u8*)record);
    }
    else if (record->sealed != BOOT_RECORD_SEALED)
    {
        func_13A678(record, 0, sizeof(BootSealedRecord));
    }
}

/** @brief Release the player, its heap and the work buffer. */
BootGameLauncher::~BootGameLauncher()
{
    if (player != 0)
    {
        player->destroy();
    }

    delete movie_heap;
    delete buffer;
}

/** @brief Clear the state and allocate the 0x12000-byte work buffer. */
BootGameLauncher::BootGameLauncher()
{
    program = 0;
    step = 0;
    buffer = func_139700(0x40, 0x12000);
    movie_heap = 0;
    player = 0;
}
