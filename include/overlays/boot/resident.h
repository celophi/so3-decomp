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
    BootClass178F30* manager;
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
struct BootDisplayLinks661C : public BootClass178DD0
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
extern void* D_001B65F4;
extern BootDisplayLinks661C* D_001B661C;
extern BootDisplay6624* D_001B6624;

/** Seconds since the last frame. */
extern float D_001B6688;

extern float D_001B6690;

s32 func_103640(void* queue, s32 id, s32 first, s32 second, s32 third, s32 fourth);
void func_103B20(void* queue, s32 id, s32 first, s32 second, s32 third, s32 fourth);
s32 func_10CAA0(s32 upper);
s32 func_10CC40(s32 lower, s32 upper);
u32 func_10CE00(void);
void func_10DB10(BootSound1B65F8* sound, s32 value);
void func_10F000(void* request, s32 first, s32 second);
void func_112400(void* request, s32 sound, s32 first, s32 second, s32 volume, s32 pan, s32 third);
s32 func_112990(void* request, s32 sound, s32 first, s32 second, s32 third);
u32 func_113930(BootResident113E40* heap, u32 size);
s32 func_115270(BootResident1B65E4* object, s32 slot);
s32 func_115430(BootResident1B65E4* object);
s32 func_115650(BootResident1B65E4* object);
s32 func_115670(BootResident1B65E4* object);
void func_11EE00(void* queue, void* allocation);
void func_121FE0(s32 value);
void func_419A70(BootClass172500* player, s32 first, s32 second);
void func_41A210(BootClass172500* player);
s32 func_465B20(BootRuntime1B657C* runtime, BootClass178A90* object);
void func_467570(BootClass175070* object, s32 first, s32 second, s32 third, float x, float y, float z);
void func_479190(BootClass175320* scene, void* data);
void func_474010(BootClass175320* scene, BootDimensionsACD0* display, BootClass178DD0* list, BootDisplay6624* state, BootClass178F30* manager,
                 BootDisplayLinks661C* links, s32 flag);
BootClass170F30* func_473940(BootClass170E90* models, const char* name);
void* func_473680(BootClass170E90* models, const char* name);
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
            BootResidentRoot15CC0* root = (BootResidentRoot15CC0*)func_10D8E0();

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
    BootClass171C00* fade = new (0) BootClass171C00(g_boot_program.display);
    fade->unkd0 = 2.0f;
    D_001B661C->append_node(fade, -1);
}

#endif
