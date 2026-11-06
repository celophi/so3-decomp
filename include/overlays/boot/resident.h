#ifndef SO3_OVERLAYS_BOOT_RESIDENT_H
#define SO3_OVERLAYS_BOOT_RESIDENT_H

#include "overlays/boot/boot.h"
#include "overlays/boot/new_game_settings.h"
#include "overlays/boot/title_menu.h"
#include "overlays/boot/init.h"
#include "overlays/lib/text_0045AD10.h"
#include "sdk/main/libkernl_00121940.h"

extern LibRenderer* g_renderer;

/** Seconds since the last frame. */
extern float g_frame_ticks;

extern float g_frame_seconds;

/**
 * @brief Finish a draw buffer's commands (Lib's definition takes an s32 mode; the image code's prototype has a u8).
 * @param buffer Draw buffer.
 * @param mode Nonzero stores the setup packet's size at its offset 0x04 too.
 * @param distance Stored in the setup packet at 0x18.
 * @param flag Stored in the setup packet at 0x3F.
 */
extern "C" void lib_draw_buffer_end(LibDrawBuffer* buffer, u8 mode, float distance, s32 flag);

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
