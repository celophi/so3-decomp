#ifndef SO3_OVERLAYS_BOOT_RESIDENT_H
#define SO3_OVERLAYS_BOOT_RESIDENT_H

#include "overlays/boot/boot.h"
#include "overlays/boot/new_game_settings.h"
#include "overlays/boot/title_menu.h"
#include "overlays/boot/init.h"
#include "overlays/lib/text_0045AD10.h"
#include "sdk/main/libkernl_00121940.h"

/** Partial resident display state D_001B6624 that points back at the display manager. */
struct BootDisplay6624
{
    u8 unk00[0x360];
    LibDisplayManager* manager;
};

extern LibRenderer* g_renderer;
extern BootDisplay6624* D_001B6624;

/** Seconds since the last frame. */
extern float g_frame_ticks;

extern float g_frame_seconds;

// Lib functions boot calls with its own scene and model types, or (lib_draw_buffer_end) with a u8 mode.
extern "C" {
void func_455BD0(LibDrawBuffer* buffer, u8 mode, float distance, s32 flag);
void lib_scene_use_data(BootScene* scene, u8* data);
void lib_scene_load_data(BootScene* scene, ResidentResourceHeader* source);
void lib_scene_release_entries(BootScene* scene);
/**
 * @brief Create the runtime objects for a loaded scene's entries and hook them up to the display, lists and renderer.
 * @param scene Scene whose data is loaded.
 * @param display Display the scene draws to.
 * @param list Update list the objects join.
 * @param state Resident display state.
 * @param manager Display manager.
 * @param renderer Renderer.
 * @param flag Boot always passes one.
 */
void lib_scene_build_objects(BootScene* scene, LibCameraContext* display, LibUpdateList* list, BootDisplay6624* state, LibDisplayManager* manager,
                 LibRenderer* renderer, s32 flag);
BootClass170F30* lib_find_renderable_entry(LibListObject* models, const char* name);
BootClass170F30* lib_find_next_renderable_entry(LibListObject* models, BootClass170F30* model);
void* lib_find_named_entry(LibListObject* models, const char* name);
LibTransformOwner* lib_find_transform_entry(LibListObject* models, const char* name);
void* lib_find_camera_entry(LibListObject* models, const char* name);
}

/**
 * @brief Hang when the main executable's code no longer matches the copy in the program image.
 */
static inline void check_main_code()
{
    // Uncached cursor; the code it checks starts 0x400000 bytes (0x80000 words) below it.
    u64* code = (u64*)(UNCACHED_SEGMENT | 0x500000);
    u64* copy = (u64*)(g_boot_program.image->code_offset + (u32)g_boot_program.image);
    s32 index;

    for (index = 0; index < 0x8760; index++, code++, copy++)
    {
        if (code[-0x80000] != *copy)
        {
            ResidentSystem* system = resident_get_system();

            *system->status = RESIDENT_STATUS_TAMPERED;
            for (;;)
            {
            }
        }
    }
}

/** @brief Clear the screen to the blue-violet background behind the boot submenus. */
static inline void clear_to_menu_background()
{
    g_boot_program.display->set_clear_color(0x49, 0x47, 0x9D, 0x7F);
}

/** @brief Clear the screen to black, as boot does whenever it leaves a submenu. */
static inline void clear_to_black()
{
    g_boot_program.display->set_clear_color(0, 0, 0, 0x7F);
}

/** @brief Queue a fade-out over the current screen. */
static inline void queue_fade()
{
    BootScreenFade* fade = new (0) BootScreenFade(g_boot_program.display);
    fade->fade_speed = 2.0f;
    g_renderer->append_node(fade, -1);
}

#endif
