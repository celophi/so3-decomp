#ifndef SO3_OVERLAYS_BOOT_RESIDENT_H
#define SO3_OVERLAYS_BOOT_RESIDENT_H

#include "overlays/boot/text_001E0900.h"
#include "overlays/boot/init.h"

/** Partial resident root whose word at 0x15CC0 points to the status byte. */
struct BootResidentRoot15CC0
{
    u8 unk00[0x15CC0];
    u8* status;
};

/** Partial resident display state D_001B6624 that points back at the display manager. */
struct BootDisplay6624
{
    u8 unk00[0x360];
    BootDisplayManager* manager;
};

/** Partial resident object whose display pointer is at offset 0x8C. */
struct BootDisplayUser8C
{
    u8 unk00[0x8C];
    BootDimensionsACD0* display;
};

/** Partial resident object whose display pointer is at offset 0x94. */
struct BootDisplayUser94
{
    u8 unk00[0x94];
    BootDimensionsACD0* display;
};

/** Partial resident object whose display pointer is at offset 0x128. */
struct BootDisplayUser128
{
    u8 unk00[0x128];
    BootDimensionsACD0* display;
};

/** Partial resident manager D_001B661C and the objects that draw through the display. */
struct BootDisplayLinks661C : public BootUpdateList
{
    u8 unk14[0x406C];
    BootDisplayUser8C* unk4080;
    void* unk4084;
    BootDimensionsACD0* unk4088;
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

s32 resident_random_below(s32 upper);
s32 resident_random_range(s32 lower, s32 upper);
u32 resident_rand(void);
void resident_sound_set_volume_scale(ResidentSound* sound, s32 value);
void resident_sound_stop_music(ResidentSound* sound, s32 first, s32 second);
s32 resident_sound_play_music(ResidentSound* sound, s32 music, s32 first, s32 second, s32 third);
u32 func_113930(BootResident113E40* heap, u32 size);
s32 func_115270(ResidentArchive* archive, s32 slot);
void FlushCache(s32 value);
void func_419A70(BootMoviePlayer* player, s32 first, s32 second);
void func_41A210(BootMoviePlayer* player);
// TODO: Lib's lib_queue_display_object, which takes FieldRuntime and LibClass178A90; boot still has its own
// mirrors of those classes.
s32 func_465B20(BootRuntime1B657C* runtime, BootTransformOwner* object);
void func_467570(BootSelectionCursor* object, s32 first, s32 second, s32 third, float x, float y, float z);
void func_479190(BootScene* scene, void* data);
void func_474010(BootScene* scene, BootDimensionsACD0* display, BootUpdateList* list, BootDisplay6624* state, BootDisplayManager* manager,
                 BootDisplayLinks661C* links, s32 flag);
BootClass170F30* lib_find_renderable_entry(BootListObject* models, const char* name);
void* lib_find_camera_entry(BootListObject* models, const char* name);
void func_4DF6E0(BootDimensionsACD0* display, s32 red, s32 green, s32 blue, s32 alpha);
}

/**
 * @brief Hang when the main executable's code no longer matches the copy in the program image.
 */
static inline void check_main_code()
{
    // Uncached cursor; the code it checks starts 0x400000 bytes (0x80000 words) below it.
    u64* code = (u64*)(0x20000000 | 0x500000);
    u64* copy = (u64*)(g_boot_program.image->code_offset + (u32)g_boot_program.image);
    s32 index;

    for (index = 0; index < 0x8760; index++, code++, copy++)
    {
        if (code[-0x80000] != *copy)
        {
            BootResidentRoot15CC0* root = (BootResidentRoot15CC0*)resident_get_runtime_owner();

            *root->status = 0x67;
            for (;;)
            {
            }
        }
    }
}

/** @brief Queue a fade-out over the current screen. */
static inline void queue_fade()
{
    BootScreenFade* fade = new (0) BootScreenFade(g_boot_program.display);
    fade->fade_speed = 2.0f;
    D_001B661C->append_node(fade, -1);
}

#endif
