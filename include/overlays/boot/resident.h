#ifndef SO3_OVERLAYS_BOOT_RESIDENT_H
#define SO3_OVERLAYS_BOOT_RESIDENT_H

#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/init.h"
#include "overlays/lib/text_0045AD10.h"

/** Partial resident display state D_001B6624 that points back at the display manager. */
struct BootDisplay6624
{
    u8 unk00[0x360];
    LibDisplayManager* manager;
};

/** Partial resident object whose display pointer is at offset 0x8C. */
struct BootDisplayUser8C
{
    u8 unk00[0x8C];
    LibCameraContext* display;
};

/** Partial resident object whose display pointer is at offset 0x94. */
struct BootDisplayUser94
{
    u8 unk00[0x94];
    LibCameraContext* display;
};

/** Partial resident object whose display pointer is at offset 0x128. */
struct BootDisplayUser128
{
    u8 unk00[0x128];
    LibCameraContext* display;
};

/** Partial resident manager D_001B661C and the objects that draw through the display. */
struct BootDisplayLinks661C : public LibUpdateList
{
    u8 unk78[0x4008];
    BootDisplayUser8C* unk4080;
    void* unk4084;
    LibCameraContext* unk4088;
    u8 unk408C[0x42];
    u8 unk40CE;
    u8 unk40CF[0x389];
    BootDisplayUser94* unk4458;
    u8 unk445C[4];
    BootDisplayUser94* unk4460;
    BootDisplayUser94* unk4464;
    BootDisplayUser94* unk4468;
    BootDisplayUser128* unk446C;
};

extern "C" {
extern BootDisplayLinks661C* D_001B661C;
extern BootDisplay6624* D_001B6624;

/** Seconds since the last frame. */
extern float g_frame_ticks;

extern float g_frame_seconds;

void FlushCache(s32 value);
void lib_scene_use_data(BootScene* scene, u8* data);
void func_474010(BootScene* scene, LibCameraContext* display, LibUpdateList* list, BootDisplay6624* state, LibDisplayManager* manager,
                 BootDisplayLinks661C* links, s32 flag);
BootClass170F30* lib_find_renderable_entry(LibListObject* models, const char* name);
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
    D_001B661C->append_node(fade, -1);
}

#endif
