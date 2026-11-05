#include "include_asm.h"
#include "overlays/boot/text_001F6010.h"
#include "overlays/boot/installer.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/text_001FB220.h"
#include "overlays/boot/text_001FF9D0.h"
#include "overlays/boot/resident.h"
#include "overlays/lib/render_buffer.h"
#include "overlays/lib/text_004095C0.h"

extern "C" {

// Boot calls lib_draw_buffer_end through its own prototype, with a u8 mode.
void func_455BD0(LibDrawBuffer* buffer, u8 mode, float distance, s32 flag);
extern LibDisplayManager* g_scene_display_manager;

extern const char g_new_game_node_name[];
extern const char g_continue_node_name[];
extern const char g_battle_collection_node_name[];
extern const char g_install_node_name[];
extern const char g_title_camera_node_name[];
void lib_scene_load_data(BootScene* scene, ResidentResourceHeader* source);
void lib_scene_release_entries(BootScene* scene);

}

/** Title screen stages, including the hand-off for each menu choice. */
enum BootTitleStep
{
    BOOT_TITLE_LOAD_SCENE = 0,
    BOOT_TITLE_START_MUSIC = 1,
    BOOT_TITLE_BROWSE = 2,
    BOOT_TITLE_START_NEW_GAME = 3,
    BOOT_TITLE_REPLAY_OPENING = 4,
    BOOT_TITLE_CONTINUE_GAME = 5,
    BOOT_TITLE_OPEN_INSTALLER = 6,
    BOOT_TITLE_OPEN_BATTLE_TROPHIES = 7
};

/** Idle time before the title screen replays the opening movie. */
#define BOOT_TITLE_IDLE_MOVIE_SECONDS 45.0f

/** Progress bar fill is computed in thousandths of its inner width. */
enum BootProgressBarConstants
{
    BOOT_PROGRESS_BAR_SCALE = 1000
};

/** The captured 640-pixel display is split into ten 64-pixel strips for the fade. */
enum BootFadeStripConstants
{
    BOOT_FADE_STRIP_COUNT = 10,
    BOOT_FADE_STRIP_WIDTH = 64,
    BOOT_FADE_STRIP_HEIGHT = 448,
    /** PSMCT24 occupies four bytes per pixel in VRAM. */
    BOOT_FADE_STRIP_VRAM_SIZE = BOOT_FADE_STRIP_WIDTH * BOOT_FADE_STRIP_HEIGHT * 4
};

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
    case BOOT_TITLE_ITEM_NEW_GAME:
        node = lib_find_renderable_entry(menu->scene, g_new_game_node_name);
        break;
    case BOOT_TITLE_ITEM_CONTINUE:
        node = lib_find_renderable_entry(menu->scene, g_continue_node_name);
        break;
    case BOOT_TITLE_ITEM_BATTLE_TROPHIES:
        node = lib_find_renderable_entry(menu->scene, g_battle_collection_node_name);
        break;
    case BOOT_TITLE_ITEM_INSTALL:
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
            LibVector4 value;
            copy_vector(&value, &node->scale);

            if (value.x < 1.08f && !snap)
            {
                value.x += 0.02f * g_frame_ticks;
                value.y += 0.02f * g_frame_ticks;
                value.z += 0.02f * g_frame_ticks;
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
                    value.x -= 0.01f * g_frame_ticks;
                    value.y -= 0.005f * g_frame_ticks;

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
                    value.x += 0.01f * g_frame_ticks;
                    value.y += 0.005f * g_frame_ticks;

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
            LibVector4 value;
            copy_vector(&value, &node->scale);

            if (value.x > 1.05f)
            {
                value.x -= 0.05f * g_frame_ticks;
                value.y -= 0.05f * g_frame_ticks;
                value.z -= 0.05f * g_frame_ticks;
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
                value.x += 0.025f * g_frame_ticks;
                value.y += 0.05f * g_frame_ticks;

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
    LibSystemSettings* settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);
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

    float screen_x = node->base_transform.m[0][3];
    float screen_y = node->base_transform.m[1][3];

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

    if (selected == BOOT_TITLE_ITEM_CONTINUE)
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

    LibVector4 color;
    copy_vector(&color, &collection_node->base_color_factor);

    if (first == BOOT_TROPHY_FILE_PRESENT || second == BOOT_TROPHY_FILE_PRESENT)
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

    if (slot1 == BOOT_CARD_STATUS_SAVE_PRESENT || slot2 == BOOT_CARD_STATUS_SAVE_PRESENT)
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
    LibSystemSettings* settings;
    BootInput* input = g_boot_program.input;
    settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    switch (step)
    {
    case BOOT_TITLE_LOAD_SCENE:
    {
        if (resident_poll_resource_queue(g_resource_queue) == 0)
        {
            break;
        }

        if (RESIDENT_ALIGN_RESOURCE(g_boot_program.message_block) == 0)
        {
            break;
        }

        check_main_code();
        scene = new (0) BootScene;
        lib_scene_load_data(scene, (ResidentResourceHeader*)scene_data);
        func_474010(scene, g_boot_program.display, g_update_list, D_001B6624, g_display_manager, g_renderer, 1);
        delete[] scene_data;
        scene_data = 0;
        lib_reset_game_state(game_data);
        delete[] game_data;
        game_data = 0;
        camera = lib_find_camera_entry(scene, g_title_camera_node_name);
        g_display_manager->current_display = static_cast<LibListObject*>(camera);

        if (initial_item != BOOT_TITLE_ITEM_AUTO)
        {
            selected = initial_item;
        }
        else if (input->slot1_state == BOOT_CARD_STATUS_SAVE_PRESENT || input->slot2_state == BOOT_CARD_STATUS_SAVE_PRESENT)
        {
            selected = BOOT_TITLE_ITEM_CONTINUE;
        }
        else
        {
            selected = BOOT_TITLE_ITEM_NEW_GAME;
        }

        animate_items(1);
        g_renderer->prepend_node(new (0) LibColorFade, -1);
        float x;
        float y;
        get_cursor_position(&x, &y);
        cursor = new (0) LibSelectionCursor;
        cursor->init(1, 0, 0, x, y, 0.0f);
        lib_queue_display_object(g_field_runtime, reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(cursor)));
        step++;
        break;
    }
    case BOOT_TITLE_START_MUSIC:
        if (resident_sound_play_music(g_sound, 2, 1, 0, 0) == 0)
        {
            break;
        }

        check_main_code();
        step++;
        idle_time = 0.0f;
        break;
    case BOOT_TITLE_BROWSE:
    {
        check_main_code();

        if (input->repeated == BOOT_BUTTON_LEFT && cursor->arrived)
        {
            selected--;

            if (selected > BOOT_TITLE_ITEM_BATTLE_TROPHIES)
            {
                selected = BOOT_TITLE_ITEM_BATTLE_TROPHIES;
            }

            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->set_move_target(x, y, 0.05f);
            pulse_up = 0;
            resident_sound_play(g_sound, 0, 0, 0, 0x7F, 0x40, 0);
        }

        if (input->repeated == BOOT_BUTTON_RIGHT && cursor->arrived)
        {
            selected++;

            if (selected > BOOT_TITLE_ITEM_BATTLE_TROPHIES)
            {
                selected = BOOT_TITLE_ITEM_NEW_GAME;
            }

            float x;
            float y;
            get_cursor_position(&x, &y);
            cursor->set_move_target(x, y, 0.05f);
            resident_sound_play(g_sound, 0, 0, 0, 0x7F, 0x40, 0);
        }

        idle_time += g_frame_seconds;

        if (input->pressed & settings->confirm_buttons)
        {
            u8 accepted = 0;

            if (selected == BOOT_TITLE_ITEM_NEW_GAME)
            {
                step++;
                accepted = 1;
            }

            if (selected == BOOT_TITLE_ITEM_CONTINUE && continue_ready)
            {
                settings->continue_selected = 1;
                accepted = 1;
                step = BOOT_TITLE_CONTINUE_GAME;
            }

            if (selected == BOOT_TITLE_ITEM_BATTLE_TROPHIES && collection_ready)
            {
                accepted = 1;
                step = BOOT_TITLE_OPEN_BATTLE_TROPHIES;
            }

            if (selected == BOOT_TITLE_ITEM_INSTALL && install_ready)
            {
                accepted = 1;
                step = BOOT_TITLE_OPEN_INSTALLER;
            }

            if (accepted)
            {
                queue_fade();
                resident_sound_stop_music(g_sound, 0x1E, -1);
                resident_sound_play(g_sound, 1, 0, 0, 0x7F, 0x40, 0);
            }
            else
            {
                resident_sound_play(g_sound, 3, 0, 0, 0x7F, 0x40, 0);
            }
        }
        else if (!(idle_time < BOOT_TITLE_IDLE_MOVIE_SECONDS) && resident_sound_is_music_playing(g_sound, -1) == 0 && resident_archive_has_resource(g_resource_archive, 1) == 1)
        {
            queue_fade();
            resident_sound_stop_music(g_sound, 0x1E, -1);
            step = BOOT_TITLE_REPLAY_OPENING;
        }

        break;
    }
    case BOOT_TITLE_START_NEW_GAME:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        lib_scene_release_entries(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        g_update_list->append_node(new (0) BootNewGameSettings, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case BOOT_TITLE_REPLAY_OPENING:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        lib_scene_release_entries(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        resident_sound_stop_music(g_sound, 0, -1);
        g_update_list->append_node(new (0) BootOpeningMovie, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case BOOT_TITLE_CONTINUE_GAME:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        lib_scene_release_entries(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        g_update_list->append_node(new (0) BootGameLauncher, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case BOOT_TITLE_OPEN_INSTALLER:
        check_main_code();
        g_boot_program.select_projection();
        step++;
        lib_scene_release_entries(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        g_update_list->append_node(new (0) BootInstaller, -1);
        lib_object_detach_owner(this);
        destroy();
        break;
    case BOOT_TITLE_OPEN_BATTLE_TROPHIES:
    {
        check_main_code();
        g_boot_program.select_projection();
        step++;
        lib_scene_release_entries(scene);
        scene->destroy();
        scene = 0;
        cursor->destroy();
        cursor = 0;
        u8* block = new (0) u8[resident_rand()];
        g_update_list->append_node(new (0) BootBattleTrophyViewer, -1);
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
    step = BOOT_TITLE_LOAD_SCENE;
    scene_data = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_RES_TITLE_SCENE));
    resident_queue_resource_request(g_resource_queue, BOOT_RES_TITLE_SCENE, scene_data, BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
    game_data = (u8*)memalign(0x40, resident_get_resource_size(g_resource_archive, BOOT_RES_GAME_DATA));
    resident_queue_resource_request(g_resource_queue, BOOT_RES_GAME_DATA, game_data, BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, 0, 0, BOOT_RESOURCE_READ);
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
    LibDrawSettings settings;
    s32 fill;

    lib_draw_buffer_begin(bar->draw_buffer, 0, 1);
    init_draw_settings(&settings);
    settings.prim = 0xC;
    settings.blend_mode = 0;
    settings.unk05 = 1;
    settings.unk06 = 0;
    FieldVec4A normal(0.0f, 0.0f, -1.0f, 1.0f);

    if (total < done)
    {
        done = total;
    }

    if (total > BOOT_PROGRESS_BAR_SCALE - 1)
    {
        fill = done / (total / BOOT_PROGRESS_BAR_SCALE);
    }
    else
    {
        fill = done * BOOT_PROGRESS_BAR_SCALE / total;
    }

    lib_draw_buffer_apply_settings(bar->draw_buffer, &settings);
    s32 width = bar->width;
    s32 height = bar->height;
    u32 color = bar->color;
    s32 depth = bar->mode;
    lib_draw_buffer_begin_primitive(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(-2.0f, -1.0f, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(bar->draw_buffer, FieldVec4A(2.0f + width, -1.0f, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(bar->draw_buffer, FieldVec4A(-2.0f, 1.0f + height, (float)depth, 1.0f), normal, 0, 0x80301004);
    add_vertex(bar->draw_buffer, FieldVec4A(2.0f + width, 1.0f + height, (float)depth, 1.0f), normal, 0, 0x80301004);
    lib_draw_buffer_begin_primitive(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, 1.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, 1.0f, (float)depth, 1.0f), normal, 0, color);
    lib_draw_buffer_begin_primitive(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, height - 1.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, height - 1.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(0.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A((float)width, (float)height, (float)depth, 1.0f), normal, 0, color);
    lib_draw_buffer_begin_primitive(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(-1.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(-1.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    lib_draw_buffer_begin_primitive(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(width - 1.0f, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f + width, 0.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(width - 1.0f, (float)height, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(1.0f + width, (float)height, (float)depth, 1.0f), normal, 0, color);
    lib_draw_buffer_begin_primitive(bar->draw_buffer, 4);
    add_vertex(bar->draw_buffer, FieldVec4A(3.0f, 3.0f, (float)depth, 1.0f), normal, 0, color);
    float right = 3.0f + ((width - 6.0f) * fill) / (float)BOOT_PROGRESS_BAR_SCALE;
    add_vertex(bar->draw_buffer, FieldVec4A(right, 3.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(3.0f, height - 3.0f, (float)depth, 1.0f), normal, 0, color);
    add_vertex(bar->draw_buffer, FieldVec4A(right, height - 3.0f, (float)depth, 1.0f), normal, 0, color);
    func_455BD0(bar->draw_buffer, 0, 1.0f, 0);
}

/**
 * @brief Initialize the settings record to its default values.
 * @param settings Settings record to initialize.
 */
void init_draw_settings(LibDrawSettings* settings)
{
    settings->prim = 0xC;
    settings->texture_index = 0;
    settings->blend_mode = 0;
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
    bar->model = new (0) LibModel;
    bar->draw_buffer->allocate_storage(2, 0x600, 1, 8);
    bar->width = width;
    bar->height = height;
    bar->color = color;
    bar->mode = mode;
    progress_bar_draw(bar, 0, 1);
    bar->model->attach_draw_buffer(bar->draw_buffer);
    bar->model->display_manager = g_scene_display_manager;
    bar->model->draw_flags |= LIB_DRAW_FLAG_0400;
    g_renderer->append_node(bar->model, -1);
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
    alpha -= fade_speed * g_frame_seconds;

    if (alpha <= 0.0f)
    {
        for (s32 i = 0; i < BOOT_FADE_STRIP_COUNT; i++)
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
 * @brief Mark the fade inactive and finish its packet.
 * @param value Unused.
 */
void BootScreenFade::on_packet_complete(u32 value)
{
    dma_pending = 0;
    lib_finish_packet(this);
}

/** @brief Mark the fade active and submit its packet. */
void BootScreenFade::render()
{
    dma_pending = 1;
    resident_packet_queue_pending(packet, static_cast<LibDmaCallbacks*>(this));
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

    resident_packet_rewind(packet);
    BootFadeStripPacket* strip = reinterpret_cast<BootFadeStripPacket*>(resident_packet_reserve(packet, 0));
    LibTextureRequest request;
    request.width = BOOT_FADE_STRIP_WIDTH;
    request.height = BOOT_FADE_STRIP_HEIGHT;
    request.size = BOOT_FADE_STRIP_VRAM_SIZE;
    request.psm = 1;
    request.width_log2 = 6;
    request.height_log2 = 10;
    u32 address = g_texture_cache->find_texture(&request, 0x54744664, 1, 0, 0, 1, 0);

    if (address != 0)
    {
        u32 base = address >> 6;
        float top = 1824.0f;
        float bottom = 2272.0f;
        float left = 1728.0f;
        float width = 64.0f;

        for (s32 i = 0; i < BOOT_FADE_STRIP_COUNT; i++)
        {
            u8* image = buffer + BOOT_FADE_STRIP_HEIGHT * (i * BOOT_FADE_STRIP_WIDTH) * 3 / 16 * 16;
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
        resident_packet_align_cursor(packet, reinterpret_cast<u8*>(strip) + 0x10);
        unk63 = 1;
    }
}

/** @brief Destroy the strips, the copy buffer and the packet. */
BootScreenFade::~BootScreenFade()
{
    for (s32 i = 0; i < BOOT_FADE_STRIP_COUNT; i++)
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
BootScreenFade::BootScreenFade(LibCameraContext* display)
{
    s32 width;
    s32 height;
    s32 i;
    this->display = display;
    width = display->display_area.width / 2 + display->display_area.width / 2;
    height = display->display_area.height / 2 + display->display_area.height / 2;
    buffer = new (0) u8[width * height * 3 / 16 * 16];

    for (i = 0; i < BOOT_FADE_STRIP_COUNT; i++)
    {
        images[i] = new (0) LibImageCapture;
        images[i]->unk65 = 1;
        lib_image_capture_store(images[i], buffer + height * (i * BOOT_FADE_STRIP_WIDTH) * 3 / 16 * 16,
                                display->buffers[0].environment.context1.frame.base_pointer << 5, width / BOOT_FADE_STRIP_WIDTH, GS_PSMCT24,
                                i * BOOT_FADE_STRIP_WIDTH, 0, BOOT_FADE_STRIP_WIDTH, height);
        g_renderer->append_node(images[i], -1);
    }

    set_type_id(0x4000);
    unk65 = 1;
    set_draw_flags(LIB_DRAW_FLAG_0400);
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
    LibDrawSettings settings;

    lib_draw_buffer_begin(image->draw_buffer, 1, 1);
    init_draw_settings(&settings);
    settings.unk06 = 0;
    settings.blend_mode = 2;
    settings.prim = 0x5C;
    settings.unk05 = 1;
    FieldVec4A normal(0.0f, 0.0f, -1.0f, 1.0f);
    lib_draw_buffer_apply_settings(image->draw_buffer, &settings);
    lib_draw_buffer_begin_primitive(image->draw_buffer, 4);

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
        // Shift the right edge in place so the addition and shift share a register.
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
        lib_draw_buffer_apply_settings(image->draw_buffer, &settings);
        lib_draw_buffer_begin_primitive(image->draw_buffer, 4);

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
    image->model->attach_draw_buffer(image->draw_buffer);
    image->model->display_manager = g_scene_display_manager;
    image->model->draw_flags |= LIB_DRAW_FLAG_0400;
    g_renderer->append_node(image->model, -1);
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
    LibDrawSettings settings;

    lib_draw_buffer_begin(draw_buffer, 0, 1);
    init_draw_settings(&settings);
    settings.unk06 = 0;
    settings.blend_mode = 2;
    settings.prim = 0x5C;
    settings.unk05 = 1;
    lib_draw_buffer_apply_settings(draw_buffer, &settings);
    lib_draw_buffer_begin_primitive(draw_buffer, 4);
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
    model->attach_draw_buffer(draw_buffer);
    model->display_manager = g_scene_display_manager;
    model->draw_flags |= LIB_DRAW_FLAG_0400;
    g_renderer->append_node(model, -1);
}

/**
 * @brief Recreate the image's draw buffer and model and upload a texture and optional palette.
 * @param texture Texture resource.
 * @param palette Palette resource, or null.
 */
void BootImage::set_texture(const LibImageResource* texture, const LibImageResource* palette)
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
    model = new (0) LibModel;
    draw_buffer->allocate_storage(1, 0x600, 2, 8);
    lib_draw_buffer_add_texture(draw_buffer, texture);

    if (palette != 0)
    {
        lib_draw_buffer_add_texture(draw_buffer, palette);
    }

    const LibImageInfo* info = lib_image_info(texture);
    texture_width = 1 << info->width_log2;
    texture_height = 1 << info->height_log2;

    if (palette != 0)
    {
        info = lib_image_info(palette);
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
