#include "include_asm.h"
#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/init.h"
#include "overlays/boot/resident.h"
#include "main/resident_001001E0.h"
#include "main/resident_0010A0E0.h"
#include "main/resident_00101550.h"
#include "main/resident_0011EE70.h"
#include "main/resident_00121860.h"
#include "sdk/main/libc_0013C6D0.h"
#include "sdk/main/libc_0013CA60.h"
#include "vu0.h"
#include "ee.h"
#include "overlays/lib/text_0045AD10.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_004AB8B0.h"

extern LibScreenText* g_screen_text;
extern BootResidentDisplay* g_display_callbacks;
extern LibCameraContext* D_001B6520;
extern u8 D_001B6420;
extern BootTrackPool<BootPooledFloatTrack>* g_float_track_pool;
extern BootTrackPool<BootPooledVectorTrack>* g_vector_track_pool;
extern BootTrackPool<BootClass177EE0>* D_001B666C;
extern BootTrackPool<BootPooledFloatCurveTrack>* g_float_curve_track_pool;
extern BootTrackPool<BootPooledVectorCurveTrack>* g_vector_curve_track_pool;
extern BootTrackPool<BootPooledFloatQuaternionTrack>* g_float_quaternion_track_pool;
extern BootTrackPool<BootPooledQuaternionCurveTrack>* g_quaternion_curve_track_pool;
extern BootTrackPool<BootPooledQuaternionTrack>* g_quaternion_track_pool;
extern struct LibPacketQueue* g_packet_queue;
extern const struct BootCaption g_opening_captions[];

/** Timebase used to convert frame ticks to seconds. */
#define BOOT_FRAME_TICKS_PER_SECOND 60.0f

/** Display width in pixels. */
#define BOOT_SCREEN_WIDTH 640

/** Height of one interlaced field, half the 448-line frame. */
#define BOOT_FIELD_HEIGHT 224

/** Reverb the settings screen plays under (studio A). */
#define BOOT_SETTINGS_REVERB_PRESET 2

/** One timed caption of the opening movie; the list ends with a frame of -1. */
struct BootCaption
{
    /** Movie frame the caption is centred on. */
    s16 frame;

    /** Screen corner, or zero for the centre. */
    s16 anchor;

    /** Nonzero for a message, zero for a picture from the third resource block. */
    s16 is_text;

    /** Picture x, or the message key. */
    s16 x;

    s16 y;
    s16 width;
    s16 height;
};

enum BootCaptionAnchor
{
    BOOT_CAPTION_CENTER,
    BOOT_CAPTION_TOP_LEFT,
    BOOT_CAPTION_TOP_RIGHT,
    BOOT_CAPTION_BOTTOM_LEFT,
    BOOT_CAPTION_BOTTOM_RIGHT
};

enum BootCaptionTiming
{
    BOOT_CAPTION_FADE_FRAMES = 30,
    BOOT_CAPTION_HOLD_END = 90,
    BOOT_CAPTION_DISPLAY_END = 120
};

/** Screen rectangle for the colour fade area; unlike LibScreenRect it has no constructor. */
struct BootScreenRect
{
    s32 x;
    s32 y;
    s32 width;
    s32 height;
};

/** @brief Destroy the object. */
BootInput::~BootInput()
{
}

/**
 * @brief Virtual slot 0x1C; nothing in boot, main or Lib calls it, so its purpose is unknown.
 * @return Zero.
 */
s32 BootInput::func_slot1c()
{
    return 0;
}

/** @brief Forget the memory card states so the next query starts fresh. */
void BootInput::clear_card_states()
{
    slot1_state = 0;
    slot2_state = 0;
    slot1_raw_state = 0;
    slot2_raw_state = 0;
    slot1_ready = 0;
    slot2_ready = 0;
}

/** @brief Sample the first pad, then keep the latest nonzero state of each memory card slot. */
void BootInput::update()
{
    BootBattleTrophyCard* trophy_card;
    u16 slot1;
    u16 slot2;
    u16 third;
    u16 fourth;
    u16 ready;
    held = resident_pad_get_held(g_input_system, 0);
    pressed = resident_pad_get_pressed(g_input_system, 0);
    held_any = resident_pad_get_held_since_clear(g_input_system, 0);
    repeated = resident_pad_get_repeated(g_input_system, 0);
    resident_pad_clear_latched(g_input_system, 0);
    trophy_card = g_boot_program.trophy_card;

    if (card_query_enabled != 0)
    {
        slot1 = trophy_card->get_slot_state(0, 1);
        slot2 = trophy_card->get_slot_state(1, 1);
        third = trophy_card->get_slot_state(0, 2);
        fourth = trophy_card->get_slot_state(1, 2);
        ready = trophy_card->get_ready_slots();

        if (slot1 != 0)
        {
            slot1_state = slot1;
        }

        if (slot2 != 0)
        {
            slot2_state = slot2;
        }

        if (third != 0)
        {
            slot1_raw_state = third;
        }

        if (fourth != 0)
        {
            slot2_raw_state = fourth;
        }

        if (ready & 1)
        {
            slot1_ready = 1;
        }
        else
        {
            slot1_ready = 0;
        }

        if (ready & 2)
        {
            slot2_ready = 1;
        }
        else
        {
            slot2_ready = 0;
        }
    }
}

/** @brief Clear the card states and start querying the cards. */
BootInput::BootInput()
{
    slot1_state = 0;
    slot2_state = 0;
    slot1_raw_state = 0;
    slot2_raw_state = 0;
    slot1_ready = 0;
    slot2_ready = 0;
    card_query_enabled = 1;
}

/** @brief Play the opening movie with its timed captions until it ends or the player skips it. */
void BootOpeningMovie::update()
{
    s32 offset;
    s32 fade;
    s32 is_text;
    s32 x;
    s32 y;
    BootInput* input = g_boot_program.input;
    LibSystemSettings* settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);
    s32 width;
    s32 height;
    s32 anchor;

    switch (step)
    {
    case BOOT_MOVIE_PREPARE:
        if ((input->held & BOOT_BUTTON_START) || resident_archive_has_resource(g_resource_archive, 1) != 1)
        {
            step = BOOT_MOVIE_STOP;
            break;
        }

        if (RESIDENT_ALIGN_RESOURCE(g_boot_program.image_block) == 0)
        {
            break;
        }

        container = new (0) LibContainer(9, 0.0f, 0.0f, 0.0f);
        lib_queue_display_object(g_field_runtime, reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
        lib_movie_play(player, 12, 1);
        caption = 0;
        caption_phase = BOOT_CAPTION_HIDDEN;
        step++;
        caption_image_loaded = 0;
        break;
    case BOOT_MOVIE_CAPTIONS:
        fade = 0;
        offset = player->state->current_frame - g_opening_captions[caption].frame;

        if (g_opening_captions[caption].frame == -1)
        {
            step++;
            break;
        }

        if (input->held & BOOT_BUTTON_START)
        {
            step = BOOT_MOVIE_STOP;
            g_renderer->append_node(new (0) BootScreenFade(g_boot_program.display), -1);
        }

        is_text = g_opening_captions[caption].is_text;

        if (offset >= -BOOT_CAPTION_FADE_FRAMES && offset < 0)
        {
            fade = -offset;
            caption_phase = BOOT_CAPTION_FADE_IN;
        }

        if (offset >= 0 && offset < BOOT_CAPTION_HOLD_END)
        {
            fade = offset;
            caption_phase = BOOT_CAPTION_SHOWN;
        }

        if (offset >= BOOT_CAPTION_HOLD_END && offset < BOOT_CAPTION_DISPLAY_END)
        {
            fade = offset - BOOT_CAPTION_HOLD_END;
            caption_phase = BOOT_CAPTION_FADE_OUT;
        }

        if (offset >= BOOT_CAPTION_DISPLAY_END)
        {
            caption_phase = BOOT_CAPTION_HIDDEN;
            caption++;

            if (is_text == 0)
            {
                if (caption_image != 0)
                {
                    caption_image->destroy();
                    caption_image = 0;
                }

                caption_image_loaded = 0;
            }
            else
            {
                caption_text->destroy();
                caption_text = 0;
            }

            if (caption >= 18)
            {
                break;
            }
        }

        if (caption_phase <= BOOT_CAPTION_HIDDEN)
        {
            break;
        }

        if (is_text == 0)
        {
            width = g_opening_captions[caption].width;
            height = g_opening_captions[caption].height;

            if (caption_image_loaded == 0)
            {
                caption_image = new (0) BootImage;
                caption_image->set_texture((const LibImageResource*)RESIDENT_ALIGN_RESOURCE(g_boot_program.image_block), 0);
                caption_image->set_rectangle(g_opening_captions[caption].x, g_opening_captions[caption].y, width, height, 0x80808080, 0);
                caption_image_loaded = 1;
            }
        }
        else
        {
            if (caption_text == 0)
            {
                if (settings->widescreen)
                {
                    caption_text = new (0) LibTextWidget(g_boot_program.captions, g_opening_captions[caption].x, 1, 32.0f, 32.0f, 576.0f, 400.0f);
                    caption_text->set_scale(0.75f);
                }
                else
                {
                    caption_text = new (0) LibTextWidget(g_boot_program.captions, g_opening_captions[caption].x, 1, 32.0f, 32.0f, 576.0f, 400.0f);
                }

                lib_container_attach_widget(container, caption_text);
            }

            const LibTextExtent* extent = lib_text_measure_bounds(caption_text);
            width = (s32)extent->width;
            height = (s32)extent->height;
        }

        anchor = g_opening_captions[caption].anchor;

        if (is_text == 0)
        {
            switch (anchor)
            {
            case BOOT_CAPTION_CENTER:
                x = 288 - width / 2;
                y = 192 - height / 2;
                break;
            case BOOT_CAPTION_TOP_LEFT:
                x = 0;
                y = 0;
                break;
            case BOOT_CAPTION_TOP_RIGHT:
                x = 576 - width;
                y = 0;
                break;
            case BOOT_CAPTION_BOTTOM_LEFT:
                x = 0;
                y = 384 - height;
                break;
            case BOOT_CAPTION_BOTTOM_RIGHT:
                x = 576 - width;
                y = 384 - height;
                break;
            }
        }
        else
        {
            switch (anchor)
            {
            case BOOT_CAPTION_CENTER:
                caption_text->set_horizontal_align(1);
                caption_text->set_vertical_align(1);
                break;
            case BOOT_CAPTION_TOP_LEFT:
                caption_text->set_horizontal_align(0);
                caption_text->set_vertical_align(0);
                break;
            case BOOT_CAPTION_TOP_RIGHT:
                caption_text->set_horizontal_align(2);
                caption_text->set_vertical_align(0);
                break;
            case BOOT_CAPTION_BOTTOM_LEFT:
                caption_text->set_horizontal_align(0);
                caption_text->set_vertical_align(2);
                break;
            case BOOT_CAPTION_BOTTOM_RIGHT:
                caption_text->set_horizontal_align(2);
                caption_text->set_vertical_align(2);
                break;
            }
        }

        if (is_text == 0)
        {
            caption_image->model->set_translation((float)x - 288.0f, (float)y - 192.0f, 0.0f);

            switch (caption_phase)
            {
            case BOOT_CAPTION_FADE_IN:
            {
                float alpha = ((float)BOOT_CAPTION_FADE_FRAMES - (float)fade) / (float)BOOT_CAPTION_FADE_FRAMES;
                caption_image->model->draw_flags &= ~LIB_DRAW_HIDDEN;
                LibVector4 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = alpha;
                LibModel* model = caption_image->model;
                copy_vector(&model->base_color_factor, &color);
                model->update_combined_color_factor();
                break;
            }
            case BOOT_CAPTION_SHOWN:
            {
                LibVector4 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = 1.0f;
                LibModel* model = caption_image->model;
                copy_vector(&model->base_color_factor, &color);
                model->update_combined_color_factor();
                break;
            }
            case BOOT_CAPTION_FADE_OUT:
            {
                LibVector4 color;
                color.x = 1.0f;
                color.y = 1.0f;
                color.z = 1.0f;
                color.w = ((float)BOOT_CAPTION_FADE_FRAMES - (float)fade) / (float)BOOT_CAPTION_FADE_FRAMES;
                LibModel* model = caption_image->model;
                copy_vector(&model->base_color_factor, &color);
                model->update_combined_color_factor();
                break;
            }
            }
        }
        else
        {
            switch (caption_phase)
            {
            case BOOT_CAPTION_FADE_IN:
            case BOOT_CAPTION_FADE_OUT:
                caption_text->set_alpha(128.0f * ((float)BOOT_CAPTION_FADE_FRAMES - (float)fade) / (float)BOOT_CAPTION_FADE_FRAMES);
                break;
            case BOOT_CAPTION_SHOWN:
                caption_text->set_alpha(128.0f);
                break;
            }
        }

        break;
    case BOOT_MOVIE_WAIT_FOR_END:
        if ((input->held & BOOT_BUTTON_START) || !player->is_playing)
        {
            g_renderer->append_node(new (0) BootScreenFade(g_boot_program.display), -1);
            step = BOOT_MOVIE_STOP;
        }

        break;
    case BOOT_MOVIE_STOP:
        lib_movie_stop(player);

        if (caption_image != 0)
        {
            caption_image->destroy();
            caption_image = 0;
        }

        if (container != 0)
        {
            container->destroy();
            container = 0;
        }

        if (caption_text != 0)
        {
            caption_text->destroy();
            caption_text = 0;
        }

        if (player != 0)
        {
            player->destroy();
            player = 0;
        }

        step++;
        break;
    case BOOT_MOVIE_OPEN_TITLE:
        lib_object_detach_owner(this);
        destroy();
        g_update_list->append_node(new (0) BootTitleMenu(BOOT_TITLE_ITEM_AUTO), -1);
        return;
    }
}

/** @brief Release the caption objects, the player and its heap. */
BootOpeningMovie::~BootOpeningMovie()
{
    if (caption_image != 0)
    {
        caption_image->destroy();
    }

    if (container != 0)
    {
        container->destroy();
    }

    if (caption_text != 0)
    {
        caption_text->destroy();
    }

    if (player != 0)
    {
        player->destroy();
    }

    delete movie_heap;
}

/** @brief Create the movie player in its own heap, set up for 4:3 or widescreen. */
BootOpeningMovie::BootOpeningMovie()
{
    void* heap;
    LibSystemSettings* resource;
    step = BOOT_MOVIE_PREPARE;
    movie_heap = new (0) ResidentHeap;
    movie_heap->alignment = 0x40;
    resident_heap_create_memory(movie_heap, BOOT_MOVIE_HEAP_SIZE);
    heap = resident_exchange_allocation_heap(movie_heap);
    player = new (0) LibMoviePlayer(BOOT_MOVIE_FRAME_WIDTH, BOOT_MOVIE_FRAME_HEIGHT);
    resident_exchange_allocation_heap(heap);
    player->state->set_scale(1.0f, 1.0f);
    player->state->set_words(0x800, 0x800, 1);
    resource = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    if (resource->widescreen != 0)
    {
        player->state->unk80D8 = 1;
        g_scene_camera->pixel_aspect =
            (1.7777778f * ((1.3333334f * (1.0714285f * (float)g_boot_program.display->display_area.height)) / (float)g_boot_program.display->display_area.width)) /
            1.3333334f;
        g_scene_camera->horizontal_fov = 1.8325958f;
    }

    container = 0;
    caption_text = 0;
    caption_image = 0;
}

/** @brief Show the popup while the loader reports a BB Unit error, and remove it once the error clears. */
void BootUnitErrorPopup::update()
{
    if (enabled == 0)
    {
        return;
    }

    if (resident_archive_has_unit_error(g_resource_archive))
    {
        if (container == 0 && RESIDENT_ALIGN_RESOURCE(program->message_block) != 0)
        {
            container = new (0) LibContainer(8, 0.0f, 0.0f, 0.0f);
            lib_queue_display_object(g_field_runtime,
                                     reinterpret_cast<LibTransformOwner*>(static_cast<LibTransformOwner*>(container)));
            panel = new (0) LibPanel(0, 64.0f, 160.0f, 520.0f, 160.0f, 88.0f);
            lib_container_attach_widget(container, panel);
            text = new (0) LibTextWidget(program->messages, BOOT_MSG_UNIT_FIX, 0, 80.0f, 176.0f, 576.0f, 320.0f);
            lib_container_attach_widget(container, text);
        }
    }
    else if (container != 0)
    {
        if (panel != 0)
        {
            panel->destroy();
            panel = 0;
        }

        if (text != 0)
        {
            text->destroy();
            text = 0;
        }

        if (container != 0)
        {
            container->destroy();
            container = 0;
        }
    }
}

/** @brief Destroy the object. */
BootUnitErrorPopup::~BootUnitErrorPopup()
{
}

/** @brief Release the owned objects, then queue this object for deletion. */
void BootUnitErrorPopup::destroy()
{
    if (panel != 0)
    {
        panel->destroy();
        panel = 0;
    }

    if (text != 0)
    {
        text->destroy();
        text = 0;
    }

    if (container != 0)
    {
        container->destroy();
        container = 0;
    }

    resident_enqueue_object(g_resident_release_queues, this);
}

/**
 * @brief Replace the display and, on a full rebuild, the scratch heap.
 * @param full Nonzero to also recreate the scratch heap and rebind the display.
 */
void BootProgram::rebuild_display(u8 full)
{
    LibDisplayArea* area;
    delete display;
    display = new (0) LibCameraContext;
    display->initialize(2);
    display->set_scale(1, 1.0f, 2.0f, -1);
    display->configure_screen(0, 1, 0, 0, 1, 0, 0, 1, BOOT_SCREEN_WIDTH, BOOT_FIELD_HEIGHT);
    display->configure_screen(1, 1, 0, 0, 1, 1, 1, 1, BOOT_SCREEN_WIDTH, BOOT_FIELD_HEIGHT);
    display->configure_buffers(GS_PSMCT32, BOOT_SCREEN_WIDTH, BOOT_FIELD_HEIGHT, GS_DEPTH_TEST_GEQUAL, GS_PSMZ24);
    display->configure_display(GS_PSMCT24, BOOT_SCREEN_WIDTH, BOOT_FIELD_HEIGHT);
    display->set_clear_color(0, 0, 0, 0x81);
    area = &display->display_area;
    display->set_screen_view(0, 0, 0, area->width, area->height);
    display->set_screen_view(1, 0, 0, area->width, area->height);
    display->refresh_scaled_packets();

    if (full)
    {
        if (g_texture_cache != reinterpret_cast<LibTextureCache*>(EE_SCRATCHPAD))
        {
            ::operator delete(g_texture_cache);
        }

        lib_vram_reset(g_vram_allocator, display->vram_free_page);
        g_texture_cache = new (0) LibTextureCache(0x20000, 0x20);
        g_screen_text->load_font();
        lib_upload_default_palette();
        resident_input_attach_display(g_input_system, display, 1);
        g_display_callbacks->display = display;
    }

    frame = 0;
}

/** @brief Make the boot projection the display manager's current display. */
void BootProgram::select_projection()
{
    g_display_manager->current_display = projection;
}

/** @brief Set the projections' aspect and field of view for the 4:3 or widescreen setting. */
inline void BootProgram::apply_projection_aspect()
{
    LibSystemSettings* resource = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);
    LibCameraContext* dimensions;

    if (resource->widescreen != 0)
    {
        dimensions = g_boot_program.display;
        projection->pixel_aspect = (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->display_area.height)) / (float)dimensions->display_area.width)) / 1.3333334f;
        projection->unk250 = 0.75f;
        dimensions = g_boot_program.display;
        g_scene_camera->pixel_aspect = (1.7777778f * ((1.3333334f * (1.0714285f * (float)dimensions->display_area.height)) / (float)dimensions->display_area.width)) / 1.3333334f;
        g_scene_camera->horizontal_fov = 1.8325958f;
    }
    else
    {
        dimensions = g_boot_program.display;
        projection->pixel_aspect = (1.3333334f * (1.0714285f * (float)dimensions->display_area.height)) / (float)dimensions->display_area.width;
        projection->unk250 = 1.0f;
        dimensions = g_boot_program.display;
        g_scene_camera->pixel_aspect = (1.3333334f * (1.0714285f * (float)dimensions->display_area.height)) / (float)dimensions->display_area.width;
        g_scene_camera->horizontal_fov = 1.5707964f;
    }
}

/** @brief Set the projections' aspect and field of view for the 4:3 or widescreen setting. */
void BootProgram::update_projection_aspect()
{
    apply_projection_aspect();
}

/**
 * @brief Switch progressive output on or off, then rebuild the display and rebind it everywhere.
 * @param progressive Nonzero for progressive (525p) output.
 */
void BootProgram::set_progressive(u8 progressive)
{
    LibCameraContext* rebuilt;
    LibRenderer* renderer;

    if (progressive)
    {
        display->set_output(false, false);
        resident_system_set_progressive(resident_get_system(), 1);
    }
    else
    {
        display->set_output(false, false);
        resident_system_set_progressive(resident_get_system(), 0);
    }

    rebuild_display(1);
    rebuilt = display;
    renderer = g_renderer;
    renderer->display = rebuilt;
    g_display = rebuilt;

    if (renderer->manager != 0)
    {
        renderer->manager->effect_display = rebuilt;
    }

    renderer->unk4458->display = rebuilt;
    renderer->unk4460->display = rebuilt;
    renderer->unk4464->display = rebuilt;
    renderer->unk4468->display = rebuilt;
    renderer->extra->display = rebuilt;
    D_001B6520 = rebuilt;
    apply_projection_aspect();
}

/** @brief Decode the next of the program's three resource blocks, then destroy this object after the last. */
void BootResourceLoader::update()
{
    u8* buffer;
    u8* aligned;

    if (resident_poll_resource_queue(g_resource_queue) != 0)
    {
        if (block >= BOOT_COMMON_UI_BLOCK_COUNT)
        {
            delete[] data;
            lib_object_detach_owner(this);
            destroy();
            return;
        }

        buffer = resident_allocate_decode_buffer(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(data), block, 1);
        aligned = (u8*)RESIDENT_ALIGN_RESOURCE(buffer);
        resident_decode_resource_block(g_resident_resource_decoder, reinterpret_cast<ResidentResourceHeader*>(data), aligned, block);

        switch (block)
        {
        case BOOT_COMMON_UI_MESSAGES:
            program->message_block = buffer;
            program->messages = lib_load_resource_slot(g_field_runtime, aligned);
            break;
        case BOOT_COMMON_UI_CAPTIONS:
            program->caption_block = buffer;
            program->captions = lib_load_resource_slot(g_field_runtime, aligned);
            break;
        case BOOT_COMMON_UI_IMAGES:
            program->image_block = buffer;
            break;
        }

        block++;
    }
}

/** @brief Fill the track pools, then create and register the projection. */
void BootProgram::create_pools_and_projection()
{
    lib_load_shared_font(0, 0);
    float_track_pool_allocate(g_float_track_pool, 500);
    vector_track_pool_allocate(g_vector_track_pool, 500);
    track_1718C0_pool_allocate(D_001B666C, 500);
    float_curve_track_pool_allocate(g_float_curve_track_pool, 2000);
    vector_curve_track_pool_allocate(g_vector_curve_track_pool, 2000);
    float_quaternion_track_pool_allocate(g_float_quaternion_track_pool, 2000);
    quaternion_curve_track_pool_allocate(g_quaternion_curve_track_pool, 1000);
    quaternion_track_pool_allocate(g_quaternion_track_pool, 1000);
    projection = new (0) LibClass179080(display);
    projection->initialize_projection(display);
    projection->set_translation(0.0f, 0.0f, -500.0f);
    g_display_manager->append_node(projection, -1);
    g_display_manager->current_display = projection;
    g_display_manager->set_display_effect(display, false, true, false, 2, 0xFFFFFF);
    g_renderer->unk4084 = D_001B6624;
    D_001B6624->manager = g_display_manager;
}

/** @brief Run the boot program. */
void BootProgram::run()
{
    ResidentClock clock;
    BootScreenRect rect;
    u8* buffer;
    s32 size;
    s32 count;
    s32 index;
    bool fresh;
    s32 previous;
    LibSystemSettings* settings;
    BootResourceLoader* loader;

    if (resident_get_system()->status == 0)
    {
        resident_system_create_status(resident_get_system());
    }

    resident_archive_get_clock(resident_get_archive(resident_get_system()), &clock);
    count = (u8)(TIMER0_COUNT + (clock.hour + (clock.second + clock.minute)));

    for (index = 0; index < count; index++)
    {
        resident_next_random_word();
    }

    projection = 0;
    input = 0;
    message_block = 0;
    display = 0;
    image_block = 0;
    trophy_card = 0;
    caption_block = 0;
    unk2C = 0;
    next_program = 0;
    error_popup = 0;
    image = 0;
    messages = 0;
    captions = 0;
    unit_data_deleted = 0;

    buffer = new (0) u8[resident_rand() + 0x40];
    size = resident_get_resource_size(resident_get_archive(resident_get_system()), BOOT_PROGRAM_MAIN_CODE_RESOURCE);

    if (size > BOOT_PROGRAM_MAIN_CODE_MAX_SIZE)
    {
        size = BOOT_PROGRAM_MAIN_CODE_MAX_SIZE;
    }

    image = (BootProgramImage*)memalign(0x40, size);
    // Leaving the u32 conversion implicit moves the clamp's copy of size; the explicit cast keeps it.
    resident_queue_resource_request(resident_system_get_resource_queue(resident_get_system()), BOOT_PROGRAM_MAIN_CODE_RESOURCE, image,
                                    BOOT_RESOURCE_TAG, BOOT_RESOURCE_PRIORITY, 0, (u32)size, 0, BOOT_RESOURCE_READ);
    delete[] buffer;

    saved_widescreen = BOOT_SAVED_WIDESCREEN_UNSET;
    fresh = true;

    if (resident_find_entry(resident_get_entry_table(resident_get_system()), 1) != 0)
    {
        saved_widescreen = ((LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1))->widescreen;
        lib_free_system_data();
        fresh = false;
    }

    if (g_update_list != 0)
    {
        lib_release_shared_font();
        lib_shutdown();
        resident_drain_release_queues(g_resident_release_queues);
        resident_drain_release_queues(g_resident_release_queues);
    }

    lib_clear_vram();
    rebuild_display(0);
    func_00121890(display);
    lib_initialize(display, 0xA0013BA, 0x20000, 0x20, 0x200, 0, 0);
    rect.x = 0;
    rect.y = 0;
    rect.width = BOOT_SCREEN_WIDTH;
    rect.height = BOOT_FIELD_HEIGHT;
    lib_set_color_fade_area(reinterpret_cast<const LibScreenRect*>(&rect), GS_DEPTH_NEAREST);
    g_screen_text->depth = GS_DEPTH_NEAREST;
    resident_input_attach_display(g_input_system, display, 1);

    while (!resident_poll_resource_queue(g_resource_queue))
    {
    }

    check_main_code();
    lib_allocate_system_data();
    create_pools_and_projection();
    settings = (LibSystemSettings*)resident_find_entry(resident_get_entry_table(resident_get_system()), 1);

    if (saved_widescreen != BOOT_SAVED_WIDESCREEN_UNSET)
    {
        settings->widescreen = saved_widescreen != 0;
    }

    g_field_runtime = new (0) FieldRuntime(640.0f, 480.0f, 0, 0, 1.8f);
    trophy_card = new (0) BootBattleTrophyCard;
    g_update_list->append_node(trophy_card, -1);
    trophy_card->initialize();
    error_popup = new (0) BootUnitErrorPopup(this);
    g_update_list->append_node(error_popup, -1);
    input = new (0) BootInput;
    g_update_list->append_node(input, -1);
    loader = new (0) BootResourceLoader(this);
    g_update_list->append_node(loader, -1);

    if (fresh)
    {
        g_update_list->append_node(new (0) BootStartupChecks, -1);
    }
    else
    {
        g_update_list->append_node(new (0) BootTitleMenu(BOOT_TITLE_ITEM_AUTO), -1);
    }

    D_001B6420 = 1;
    apply_projection_aspect();
    frame = 0;
    g_renderer->unk40ce = 0;
    D_001B6420 = 1;

    while (next_program == 0)
    {
        display->flip(frame++, g_packet_queue);
        lib_begin_frame_packet();
        g_screen_text->begin(16, 16);
        g_renderer->begin_frame();
        g_update_list->update_nodes();
        resident_packet_submit(g_screen_text->packet, 0);
        resident_drain_release_queues(g_resident_release_queues);
        display->wait_for_field(frame);

        if (frame > 1)
        {
            display->set_output(true, false);
        }

        g_frame_ticks = (float)resident_input_take_vblank_count(g_input_system);
        g_frame_seconds = g_frame_ticks / BOOT_FRAME_TICKS_PER_SECOND;
        TIMER0_COUNT = 0;
    }

    g_renderer->unk40ce = 1;
    resident_drain_release_queues(g_resident_release_queues);
    g_boot_program.release_resources();
    resident_drain_release_queues(g_resident_release_queues);
    resident_drain_release_queues(g_resident_release_queues);

    previous = resident_next_random_word();

    while (previous == resident_next_random_word())
    {
    }

    previous = resident_rand();

    while (previous == resident_rand())
    {
    }

    previous = resident_random_below(BOOT_RANDOM_WARMUP_RANGE);

    while (previous == resident_random_below(BOOT_RANDOM_WARMUP_RANGE))
    {
    }

    previous = resident_random_range(0, BOOT_RANDOM_WARMUP_RANGE);

    while (previous == resident_random_range(0, BOOT_RANDOM_WARMUP_RANGE))
    {
    }

    resident_system_switch_program(resident_get_system(), (ResidentResourceHeader*)next_program, 1);
}

/** @brief Release the track pools and every object, resource and buffer the program owns. */
void BootProgram::release_resources()
{
    resident_input_attach_display(g_input_system, 0, 0);
    D_001B6420 = 0;
    float_track_pool_release(g_float_track_pool);
    vector_track_pool_release(g_vector_track_pool);
    track_1718C0_pool_release(D_001B666C);
    float_curve_track_pool_release(g_float_curve_track_pool);
    vector_curve_track_pool_release(g_vector_curve_track_pool);
    float_quaternion_track_pool_release(g_float_quaternion_track_pool);
    quaternion_curve_track_pool_release(g_quaternion_curve_track_pool);
    quaternion_track_pool_release(g_quaternion_track_pool);
    delete image;
    image = 0;

    if (error_popup != 0)
    {
        lib_object_detach_owner(error_popup);
        error_popup->destroy();
        error_popup = 0;
    }

    if (messages != 0)
    {
        lib_release_resource_slot(g_field_runtime, messages);
    }

    if (captions != 0)
    {
        lib_release_resource_slot(g_field_runtime, captions);
    }

    delete g_field_runtime;
    g_field_runtime = 0;

    if (input != 0)
    {
        lib_object_detach_owner(input);
        input->destroy();
        input = 0;
    }

    if (trophy_card != 0)
    {
        trophy_card->destroy();
        trophy_card = 0;
    }

    projection->destroy();
    projection = 0;
    delete message_block;
    message_block = 0;
    delete caption_block;
    caption_block = 0;
    delete image_block;
    image_block = 0;
    delete display;
    display = 0;
}

/** @brief Release the program's objects, resources, and buffers. */
BootProgram::~BootProgram()
{
    if (input != 0)
    {
        lib_object_detach_owner(input);
        input->destroy();
    }

    if (trophy_card != 0)
    {
        trophy_card->destroy();
    }

    if (projection != 0)
    {
        projection->destroy();
    }

    delete message_block;
    delete caption_block;
    delete image_block;
    delete image;
}

/** @brief Destroy the object. */
BootResourceLoader::~BootResourceLoader()
{
}

#include "overlays/boot/transform_inlines.h"
