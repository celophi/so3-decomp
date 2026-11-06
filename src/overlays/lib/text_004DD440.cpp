#include "include_asm.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/camera_vu0.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "vu0.h"
#include "ee.h"
#include "main/resident_data.h"

/** Track pool built by func_004E4590 and its siblings; its data comes before the vptr. */
class LibTrackPool
{
    public:
        u8 unk00[0x20];

        /** @brief Free the pool. */
        virtual ~LibTrackPool();
};

extern "C" {
extern LibDisplayManager* D_001B6660;
extern LibListObject* D_001B665C;
extern LibListObject* D_001B6640;
extern LibScreenText* g_screen_text;
extern void* D_001B6644;
extern void* D_001B6638;
extern ResidentDmaQueue* D_001B660C;
extern ResidentDmaQueue* D_001B6608;
extern ResidentDmaQueue* D_001B6604;
extern LibListObject* g_scene_camera;
extern LibListObject* D_001B664C;
extern LibListObject* D_001B6620;
extern LibListObject* D_001B6648;
extern LibUpdateList* g_update_list;
extern LibDisplayManager* g_scene_display_manager;
extern LibDisplayManager* g_default_display_manager;
extern LibListObject* D_001B6634;
extern LibListObject D_00507CB8;
extern LibTrackPool* g_float_track_pool;
extern LibTrackPool* g_vector_track_pool;
extern LibTrackPool* g_slerp_quaternion_track_pool;
extern LibTrackPool* g_float_curve_track_pool;
extern LibTrackPool* g_vector_curve_track_pool;
extern LibTrackPool* g_float_quaternion_track_pool;
extern LibTrackPool* g_quaternion_curve_track_pool;
extern LibTrackPool* g_quaternion_track_pool;
extern void* g_display_callbacks;
}
extern "C" void func_004E6690(void* object);
extern "C" void func_004E6B30(void* owner, void* object);
extern "C" void func_004E6A90(void* object);
extern "C" void func_004E6AE0(void* owner, void* object);

extern "C" u8 D_00179270[];
extern "C" u8 D_00179260[];
extern "C" u8 D_00179250[];
extern "C" u8 D_00179240[];
extern "C" u8 D_00179230[];
extern "C" u8 D_00179220[];
extern "C" u8 D_00179210[];
extern "C" u8 D_00179200[];
extern "C" u8 D_00173F58[];

typedef struct FieldArgumentInitializerState
{
    u32 unk00;
    u8 pad04[4];
    u32 unk08;
    u8 pad0c[8];
    u32 unk14;
    u8 unk18;
    u8 pad19[3];
    u32 unk1c;
    u32 unk20;
} FieldArgumentInitializerState;

#define DEFINE_FIELD_ARGUMENT_INITIALIZER(name, first_global) \
    void* name(void* object) \
    { \
        FieldArgumentInitializerState* state = (FieldArgumentInitializerState*)object; \
        state->unk20 = (u32)first_global; \
        state->unk1c = (u32)D_00173F58; \
        state->unk14 = 0; \
        state->unk18 = 0; \
        state->unk08 = 0; \
        state->unk00 = 0; \
        return object; \
    }

typedef struct ByteClearOwnertext_004DD440
{
    u8 unk00[0xCB];
    u8 unkcb;
} ByteClearOwnertext_004DD440;

typedef struct ByteClear64Ownertext_004DD440
{
    u8 unk00[0x64];
    u8 unk64;
} ByteClear64Ownertext_004DD440;

typedef struct WordClearOwnertext_004DD440
{
    u8 unk00[0x114];
    u32 unk114;
} WordClearOwnertext_004DD440;

extern "C" u8 D_0050CD80[];

typedef struct HalfwordGetterOwnertext_004DD440
{
    u8 unk00[0x28];
    s16 unk28;
    s16 unk2a;
    u8 unk2c[0x1C];
    s16 unk48;
    s16 unk4a;
} HalfwordGetterOwnertext_004DD440;



typedef struct WordGetterOwnertext_004DD440
{
    u8 unk00[0x4];
    u32 unk04;
} WordGetterOwnertext_004DD440;


static inline void lib_get_transform_translation(FieldVec4B& result, const LibTransform& object);
static inline float lib_vector_length(const FieldVec4B& vector);

/** @brief Read the matrix translation into a position vector. @param result Destination vector. @param object Transform source. */
static inline void lib_get_transform_translation(FieldVec4B& result, const LibTransform& object)
{
    result.x = object.transform.m[0][3];
    result.y = object.transform.m[1][3];
    result.z = object.transform.m[2][3];
    result.w = 1.0f;
}

/** @brief Compute the xyz vector length. @param vector Vector to measure. @return Vector length. */
static inline float lib_vector_length(const FieldVec4B& vector)
{
    FieldVec4A result;
    vu0_length_xyz(&result, &vector);
    return result.x;
}

/**
 * @brief Subtract the first three components of one vector from another.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return The difference, with left's w.
 */
static inline FieldVec4B lib_vector_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4B value(left);
    return value.subtract(right);
}

typedef struct FourWordClearOwnertext_004DD440 { u32 words[4]; } FourWordClearOwnertext_004DD440;

typedef struct PackedModePair
{
    u8 lowMode : 4;
    u8 highMode : 4;
    u8 hasModeFour : 1;
    u8 unk01_1_7 : 7;
} PackedModePair;

typedef struct PackedModesOwner
{
    u8 unk00[0x32];
    PackedModePair at32;
    u8 unk34[0x1E];
    PackedModePair at52;
} PackedModesOwner;

typedef struct FloatKeyScanEntry_text_004DD440_10
{
    float key00;
    u8 unk04[0x8];
    float key0c;
} FloatKeyScanEntry_text_004DD440_10;

typedef struct FloatKeyScanOwner_text_004DD440_10
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004DD440_10* entries;
    u8 unk08[0x20];
    s16 count28;
    u8 unk2a[0x1E];
    s16 count48;
} FloatKeyScanOwner_text_004DD440_10;

typedef struct FloatKeyScanEntry_text_004DD440_30
{
    float key00;
    u8 unk04[0x8];
    float key0c;
    u8 unk10[0x20];
} FloatKeyScanEntry_text_004DD440_30;

typedef struct FloatKeyScanOwner_text_004DD440_30
{
    u8 unk00[0x4];
    FloatKeyScanEntry_text_004DD440_30* entries;
    u8 unk08[0x20];
    s16 count28;
    u8 unk2a[0x1E];
    s16 count48;
} FloatKeyScanOwner_text_004DD440_30;

/** Number of A+D register writes that fill an object after its GIF tag. */
#define LIB_AD_WRITE_COUNT(type) ((sizeof(type) - sizeof(GsGifTag)) / sizeof(unsigned __int128))

/**
 * @brief Start an A+D register list that ends the transfer.
 * @param tag Tag to fill.
 * @param count Number of register writes after the tag.
 */
static inline void lib_start_register_list(GsGifTag* tag, u32 count)
{
    gs_clear_gif_tag(tag);
    tag->tag = GIF_TAG_NREG(1) | GIF_TAG_EOP | count;
    tag->fields.register0 = GIF_REGISTER_AD;
}

/**
 * @brief Count the VRAM pages a buffer takes.
 * @param bytes Bytes per pixel.
 * @param width Width in pixels.
 * @param height Height in pixels.
 * @return Pages, rounded down.
 */
static inline s32 lib_vram_pages(s32 bytes, s16 width, s16 height)
{
    return height * (bytes * width) / GS_VRAM_PAGE_BYTES;
}

/**
 * @brief Count the VRAM pages a frame buffer takes. 16-bit formats take two bytes a pixel, the rest four.
 * @param pixel_format GS pixel format.
 * @param width Width in pixels.
 * @param height Height in pixels.
 * @return Pages, rounded down.
 */
static inline s32 lib_buffer_pages(s16 pixel_format, s16 width, s16 height)
{
    return lib_vram_pages(pixel_format == GS_PSMCT16 || pixel_format == GS_PSMCT16S ? 2 : 4, width, height);
}

/**
 * @brief Configure one of the display's screens. Progressive output has no second read circuit, so a circuit-2
 *        screen is left alone there.
 * @param index Screen index.
 * @param enabled Nonzero to show the screen.
 * @param unk3 Stored at 0xA53.
 * @param circuit1 Show the screen on read circuit 1.
 * @param circuit2 Show the screen on read circuit 2.
 * @param unk6 Stored at 0xA56.
 * @param field Interlaced field the screen is shown in.
 * @param pixel_format Pixel format of the screen's buffers.
 * @param width Screen width in pixels.
 * @param height Screen height in pixels.
 */
void LibCameraContext::configure_screen(s32 index, u8 enabled, u8 unk3, u8 circuit1, u8 circuit2, u8 unk6, u8 field, s16 pixel_format, s16 width, s16 height)
{
    if (resident_get_system()->progressive && circuit2)
    {
        return;
    }

    screens[index].unkA51 = 0;
    screens[index].unkA57 = 0;
    screens[index].enabled = enabled;
    screens[index].unkA53 = unk3;
    screens[index].circuit1 = circuit1;
    screens[index].circuit2 = circuit2;
    screens[index].unkA56 = unk6;
    screens[index].pixel_format = pixel_format;
    screens[index].width = width;
    screens[index].height = height;
    screens[index].field = field;
}

/**
 * @brief Show the field that's starting: point the read circuits at the screens drawn for it and, when the display
 *        is scaled and no screen is on circuit 2, send the packets that draw the scaled area.
 * @param field Interlaced field (0 or 1) from GS CSR.
 */
void LibCameraContext::vblank(s32 field)
{
    bool circuit2_screen;
    s32 i;
    LibDisplayRegisters* registers;

    if (resident_get_system()->progressive)
    {
        return;
    }

    if (scaled)
    {
        circuit2_screen = false;

        for (i = 0; i < LIB_DISPLAY_SCREEN_COUNT; i++)
        {
            if (screens[i].enabled && screens[i].circuit2)
            {
                circuit2_screen = true;

                if (screens[i].field == field)
                {
                    if (screens[i].unkA57)
                    {
                        GS_DISPFB2 = *(u64*)&screens[i].display_environment.framebuffer;
                        GS_DISPLAY2 = *(u64*)&screens[i].display_environment.display;
                    }
                    else
                    {
                        GS_DISPFB2 = *(u64*)&display_environments[0].framebuffer;
                        GS_DISPLAY2 = *(u64*)&display_environments[0].display;
                    }
                }
            }

            if (screens[i].enabled && screens[i].field == field && screens[i].unkA51 && screens[i].circuit1)
            {
                GS_DISPFB1 = *(u64*)&screens[i].display_environment.framebuffer;
                GS_DISPLAY1 = *(u64*)&screens[i].display_environment.display;
            }
        }

        if (!unk3E6B && unk3E6A && packet_queue != 0 && !circuit2_screen && !func_004DBD80(packet_queue) && packet_queue->enabled)
        {
            func_004DC4F0(packet_queue, 4, 0, &buffers[1], 0, 0);
            func_004DC4F0(packet_queue, 2, 0, packets[packet_set][field] + 0x40, packet_sizes[packet_set][field], 0);

            if (unk3E48)
            {
                func_004DC4F0(packet_queue, 2, 0, unk3E34, unk3E3C, 0);
            }

            if (unk3E30 == 2)
            {
                send_packet_list(field, false);
            }
        }
    }
    else if (unk3E66 && !unk3E68)
    {
        blend_environments[shown_buffers[0]].pmode.alpha = field ? (u8)(blend_field_alpha + 0x80) : blend_field_alpha;
        sceGsPutDispEnv(&blend_environments[shown_buffers[0]]);

        if (unk3E64)
        {
            registers = &blend_registers[shown_buffers[0]];
            GS_DISPFB1 = registers->framebuffer;
            GS_DISPLAY1 = registers->display;
        }
    }
    else
    {
        sceGsPutDispEnv(&display_environments[shown_buffers[field]]);

        if (unk3E64)
        {
            registers = &circuit1_registers[shown_buffers[field ^ 1]];
            GS_DISPFB1 = registers->framebuffer;
            GS_DISPLAY1 = registers->display;
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", flip__16LibCameraContextFiP14LibPacketQueue);

/**
 * @brief Send one field's packet list from send_list_set. Entries flagged in unk3E08 are drawn with
 *        environments[0]; the draw environment is put back when the flagged run ends.
 * @param field Interlaced field whose list is sent.
 * @param per_screen Put back the environments of the field's circuit-2 screens instead of buffers[1]'s.
 */
void LibCameraContext::send_packet_list(s32 field, bool per_screen)
{
    s32 list = send_list_set * 2 + field;
    s32 count;
    s32 i;
    s32 j;
    bool alternate;

    if (list_buffers[list] == 0)
    {
        return;
    }

    count = send_list_count;
    alternate = false;

    for (i = 0; i < count; i++)
    {
        if (unk3E08[send_list_set][i] != 0)
        {
            if (!alternate)
            {
                func_004DC4F0(packet_queue, 2, 0, environments, sizeof(LibDrawEnvironment) / sizeof(unsigned __int128), 0);
                alternate = true;
            }
        }
        else if (alternate)
        {
            if (per_screen)
            {
                for (j = 0; j < LIB_DISPLAY_SCREEN_COUNT; j++)
                {
                    if (screens[j].enabled && screens[j].circuit2 && screens[j].field == field)
                    {
                        func_004DC4F0(packet_queue, 4, 0, &screens[j].buffers[0], 0, 0);
                    }
                }
            }
            else
            {
                func_004DC4F0(packet_queue, 4, 0, &buffers[1], 0, 0);
            }

            alternate = false;
        }

        func_004DC4F0(packet_queue, 2, 0, list_packets[list][i], list_sizes[list][i], 0);
    }
}

/** @brief Send the ready packet, once, if there is one and a packet queue to send it to. */
void LibCameraContext::send_ready_packet()
{
    if (packet_queue != 0 && ready_sizes[ready_index] != 0 && ready_packets[ready_index] != 0)
    {
        func_004DC4F0(packet_queue, 2, 0, ready_packets[ready_index], ready_sizes[ready_index], 0);
        ready_packets[ready_index] = 0;
    }
}

/**
 * @brief Set the rectangle of a screen that is drawn to.
 * @param index Screen index.
 * @param x Left edge.
 * @param y Top edge.
 * @param width Width in pixels.
 * @param height Height in pixels.
 */
void LibCameraContext::set_screen_view(s32 index, s32 x, s32 y, s32 width, s32 height)
{
    screens[index].view_x = x;
    screens[index].view_y = y;
    screens[index].view_width = width;
    screens[index].view_height = height;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", build_scaled_packets__16LibCameraContextFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DE500);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DEA70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DF270);

/**
 * @brief Set the colour every draw buffer is cleared to.
 * @param red Red component.
 * @param green Green component.
 * @param blue Blue component.
 * @param alpha Alpha component.
 */
void LibCameraContext::set_clear_color(u8 red, u8 green, u8 blue, u8 alpha)
{
    s32 width = buffers[0].environment.context1.scissor.x1 + 1;
    s32 height = buffers[0].environment.context1.scissor.y1 + 1;
    s32 depth_method = buffers[1].environment.context1.test.depth_method;
    s32 y = GS_COORDINATE_CENTRE - (height >> 1);
    s32 x = GS_COORDINATE_CENTRE - (width >> 1);

    build_clear(&buffers[0].clear, depth_method, x, y, width, height, red, green, blue, alpha, 0);
    build_clear(&buffers[1].clear, depth_method, x, y, width, height, red, green, blue, alpha, 0);
    build_clear(&buffers[2].clear, depth_method, x, y, width, height, red, green, blue, alpha, 0);
    clear_color = red | (green << 8) | (blue << 16) | (alpha << 24);
}

/**
 * @brief Set up the draw buffers for a frame size and lay out VRAM: the depth buffer at vram_base_page, then the
 *        frame buffers. A scaled display also places the draw area and each enabled screen's buffers after them.
 * @param pixel_format Frame buffer pixel format.
 * @param width Frame width in pixels.
 * @param height Frame height in pixels (one field when interlaced).
 * @param depth_test Depth test method; 0 for no depth buffer.
 * @param depth_format Depth buffer pixel format.
 */
void LibCameraContext::configure_buffers(s16 pixel_format, s16 width, s16 height, s16 depth_test, s16 depth_format)
{
    s16 y;
    s32 fields;
    s32 field_height;
    s32 depth_bytes;
    s32 pages;
    s32 i;

    if (height > 256)
    {
        y = (448 - height) / 2;
    }
    else
    {
        y = 224 - height;
    }

    fields = 1;

    if (resident_get_system()->progressive)
    {
        fields = 2;
    }

    display_area.base_width = width;
    field_height = height * fields;
    display_area.base_height = field_height;
    this->depth_test = depth_test;
    this->depth_format = depth_format;

    if (unk3C70 == -1)
    {
        unk3C70 = pixel_format;
    }

    resize_display_area();

    if (scaled)
    {
        sceGsSetDefDrawEnv(&buffers[0].environment.context1, unk3C70, display_area.width, display_area.height, depth_test, depth_format);
        sceGsSetDefDrawEnv2(&buffers[0].environment.context2, unk3C70, display_area.width, display_area.height, depth_test, depth_format);
    }
    else
    {
        sceGsSetDefDrawEnv(&buffers[0].environment.context1, pixel_format, width, height, depth_test, depth_format);
        sceGsSetDefDrawEnv2(&buffers[0].environment.context2, pixel_format, width, height, depth_test, depth_format);
    }

    sceGsSetDefDrawEnv(&buffers[1].environment.context1, pixel_format, width, height, depth_test, depth_format);
    sceGsSetDefDrawEnv2(&buffers[1].environment.context2, pixel_format, width, height, depth_test, depth_format);
    sceGsSetDefDrawEnv(&buffers[2].environment.context1, pixel_format, width, height, depth_test, depth_format);
    sceGsSetDefDrawEnv2(&buffers[2].environment.context2, pixel_format, width, height, depth_test, depth_format);

    if (scaled)
    {
        buffers[1].environment.context1.depth_buffer.base_pointer = buffers[1].environment.context2.depth_buffer.base_pointer =
            buffers[0].environment.context1.depth_buffer.base_pointer = buffers[0].environment.context2.depth_buffer.base_pointer = vram_base_page;
        // TODO: This is overwritten before anything reads it, but the target still tests the area's format here.
        depth_bytes = unk3C70 == GS_PSMCT16 || unk3C70 == GS_PSMCT16S ? 2 : 4;
    }
    else
    {
        buffers[2].environment.context1.depth_buffer.base_pointer = buffers[2].environment.context2.depth_buffer.base_pointer =
            buffers[1].environment.context1.depth_buffer.base_pointer = buffers[1].environment.context2.depth_buffer.base_pointer =
                buffers[0].environment.context1.depth_buffer.base_pointer = buffers[0].environment.context2.depth_buffer.base_pointer = vram_base_page;
    }

    depth_bytes = depth_format == GS_PSMZ16 || depth_format == GS_PSMZ16S ? 2 : 4;

    if (scaled)
    {
        if (depth_test == 0)
        {
            pages = 0;
        }
        else
        {
            pages = display_area.height * (depth_bytes * display_area.width) / GS_VRAM_PAGE_BYTES;
        }

        depth_buffer_pages = pages;

        vram_free_page = vram_base_page + depth_buffer_pages + lib_buffer_pages(pixel_format, width, field_height) +
                         lib_buffer_pages(unk3C70, display_area.width, display_area.height);

        for (i = 0; i < LIB_DISPLAY_SCREEN_COUNT; i++)
        {
            if (screens[i].enabled)
            {
                sceGsSetDefDispEnv(&screens[i].display_environment, screens[i].pixel_format, screens[i].width, screens[i].height, 0, y);
                screens[i].display_environment.framebuffer.base_pointer = vram_free_page;
                lib_start_register_list(&screens[i].buffers[0].environment.gif_tag, LIB_AD_WRITE_COUNT(LibDrawEnvironment));
                lib_start_register_list(&screens[i].buffers[1].environment.gif_tag, LIB_AD_WRITE_COUNT(LibDrawEnvironment));
                sceGsSetDefDrawEnv(&screens[i].buffers[0].environment.context1, screens[i].pixel_format, screens[i].width, screens[i].height, depth_test,
                                   depth_format);
                sceGsSetDefDrawEnv2(&screens[i].buffers[0].environment.context2, screens[i].pixel_format, screens[i].width, screens[i].height, depth_test,
                                    depth_format);
                sceGsSetDefDrawEnv(&screens[i].buffers[1].environment.context1, screens[i].pixel_format, screens[i].view_width, screens[i].view_height,
                                   depth_test, depth_format);
                sceGsSetDefDrawEnv2(&screens[i].buffers[1].environment.context2, screens[i].pixel_format, screens[i].view_width, screens[i].view_height,
                                    depth_test, depth_format);
                screens[i].buffers[0].environment.context1.depth_buffer.base_pointer = screens[i].buffers[0].environment.context2.depth_buffer.base_pointer =
                    buffers[0].environment.context1.depth_buffer.base_pointer;
                screens[i].buffers[0].environment.context1.frame.base_pointer = screens[i].buffers[0].environment.context2.frame.base_pointer = vram_free_page;
                screens[i].buffers[1].environment.context1.depth_buffer.base_pointer = screens[i].buffers[1].environment.context2.depth_buffer.base_pointer =
                    buffers[0].environment.context1.depth_buffer.base_pointer;
                screens[i].buffers[1].environment.context1.frame.base_pointer = screens[i].buffers[1].environment.context2.frame.base_pointer =
                    vram_base_page + depth_buffer_pages + lib_buffer_pages(pixel_format, width, height);
                if (screens[i].unkA56)
                {
                    vram_free_page += lib_buffer_pages(screens[i].pixel_format, screens[i].width, screens[i].height);
                }
            }
        }
    }
    else
    {
        if (depth_test == 0)
        {
            pages = 0;
        }
        else
        {
            pages = height * (depth_bytes * width) / GS_VRAM_PAGE_BYTES;
        }

        depth_buffer_pages = pages;

        vram_free_page = vram_base_page + depth_buffer_pages + frame_buffer_count * lib_buffer_pages(pixel_format, width, field_height);
    }

    if (frame_buffer_count == 2)
    {
        buffers[0].environment.context2.frame.base_pointer = buffers[0].environment.context1.frame.base_pointer =
            vram_base_page + depth_buffer_pages + lib_buffer_pages(pixel_format, width, field_height);
        buffers[1].environment.context2.frame.base_pointer = buffers[1].environment.context1.frame.base_pointer = vram_base_page + depth_buffer_pages;
    }
    else
    {
        buffers[0].environment.context2.frame.base_pointer = buffers[0].environment.context1.frame.base_pointer = vram_base_page + depth_buffer_pages;
        buffers[1].environment.context2.frame.base_pointer = buffers[1].environment.context1.frame.base_pointer =
            vram_base_page + depth_buffer_pages + lib_buffer_pages(pixel_format, width, field_height);
        buffers[2].environment.context2.frame.base_pointer = buffers[2].environment.context1.frame.base_pointer =
            vram_base_page + depth_buffer_pages + lib_buffer_pages(pixel_format, width, field_height) * 2;
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E02C0);

/**
 * @brief Set up the display environments for a frame size. The three frame buffers follow the depth buffer; each
 *        gets circuit-1 registers and a copy that blends both circuits.
 * @param pixel_format Frame buffer pixel format.
 * @param width Frame width in pixels.
 * @param height Frame height in pixels.
 */
void LibCameraContext::configure_display(s16 pixel_format, s16 width, s16 height)
{
    s16 y;
    s32 i;

    if (height > 256)
    {
        y = (448 - height) / 2;
    }
    else
    {
        y = 224 - height;
    }

    if (resident_get_system()->progressive)
    {
        height *= 2;
        y += 16;
    }

    sceGsSetDefDispEnv(&display_environments[0], pixel_format, width, height, 0, y);
    sceGsSetDefDispEnv(&display_environments[1], pixel_format, width, height, 0, y);
    sceGsSetDefDispEnv(&display_environments[2], pixel_format, width, height, 0, y);
    display_environments[2].framebuffer.base_pointer = vram_base_page + depth_buffer_pages + lib_buffer_pages(pixel_format, width, height) * 2;
    display_environments[1].framebuffer.base_pointer = vram_base_page + depth_buffer_pages + lib_buffer_pages(pixel_format, width, height);
    display_environments[0].framebuffer.base_pointer = vram_base_page + depth_buffer_pages;

    for (i = 0; i < LIB_DISPLAY_BUFFER_COUNT; i++)
    {
        circuit1_registers[i].framebuffer = *(u64*)&display_environments[i].framebuffer;
        circuit1_registers[i].display = *(u64*)&display_environments[i].display;
    }

    for (i = 0; i < LIB_DISPLAY_BUFFER_COUNT; i++)
    {
        blend_environments[i] = display_environments[i];
        blend_registers[i] = circuit1_registers[i];
        blend_registers[i].display = (blend_registers[i].display & ~GS_DISPLAY_Y_MASK) | (49 << GS_DISPLAY_Y_SHIFT);
        blend_environments[i].pmode.circuit1 = 1;
        blend_environments[i].pmode.fixed_alpha = 1;
        blend_environments[i].pmode.blend_background = 0;
    }

    blend_field_alpha = 0;

    if (scaled)
    {
        sceGsSetDefDrawEnv(&buffers[1].environment.context1, pixel_format, display_area.base_width, display_area.base_height, depth_test, depth_format);
        sceGsSetDefDrawEnv2(&buffers[1].environment.context2, pixel_format, display_area.base_width, display_area.base_height, depth_test, depth_format);
        buffers[1].environment.context1.depth_buffer.base_pointer = buffers[1].environment.context2.depth_buffer.base_pointer =
            buffers[0].environment.context1.depth_buffer.base_pointer;
        buffers[1].environment.context2.frame.base_pointer = buffers[1].environment.context1.frame.base_pointer = vram_base_page + depth_buffer_pages;
    }

    environments[0].context1 = buffers[0].environment.context1;
    environments[0].context2 = buffers[0].environment.context2;
    environments[1].context1 = buffers[1].environment.context1;
    environments[1].context2 = buffers[1].environment.context2;
}

/**
 * @brief Body of set_scale, which initialize also inlines.
 * @param unk3C77 Stored at 0x3C77.
 * @param scale_x Horizontal scale.
 * @param scale_y Vertical scale.
 * @param unk3C70 Stored at 0x3C70.
 */
inline void LibCameraContext::apply_scale(u8 unk3C77, float scale_x, float scale_y, s16 unk3C70)
{
    display_area.scale_x = scale_x;
    display_area.scale_y = scale_y;
    scaled = !(scale_x == 1.0f && scale_y == 1.0f);
    this->unk3C77 = unk3C77;
    unk3E65 = 0;
    unk3E66 = 0;
    unk3E68 = 0;
    this->unk3C70 = unk3C70;

    if (scaled)
    {
        lib_start_register_list(&buffers[1].environment.gif_tag, LIB_AD_WRITE_COUNT(LibDrawEnvironment));
    }

    resize_display_area();
}

/**
 * @brief Set up the display's GIF tags and default state, size the draw area and allocate its buffers.
 * @param frame_buffer_count Frame buffers the display cycles through.
 */
void LibCameraContext::initialize(s32 frame_buffer_count)
{
    s32 i;

    lib_start_register_list(&buffers[0].environment.gif_tag, LIB_AD_WRITE_COUNT(LibDisplayBuffer));
    lib_start_register_list(&buffers[1].environment.gif_tag, LIB_AD_WRITE_COUNT(LibDisplayBuffer));
    lib_start_register_list(&buffers[2].environment.gif_tag, LIB_AD_WRITE_COUNT(LibDisplayBuffer));
    lib_start_register_list(&environments[0].gif_tag, LIB_AD_WRITE_COUNT(LibDrawEnvironment));
    lib_start_register_list(&environments[1].gif_tag, LIB_AD_WRITE_COUNT(LibDrawEnvironment));
    this->frame_buffer_count = frame_buffer_count;
    vram_base_page = 0;
    unk3E64 = 0;
    shown_buffers[0] = 0;
    shown_buffers[1] = 0;
    unk3E4C = 0;
    unk3E69 = 0;
    unk3E50 = 0;
    unk3E78 = 0;
    unk3E7A = 0;
    apply_scale(0, 1.0f, 1.0f, -1);

    for (i = 0; i < LIB_DISPLAY_PACKET_COUNT; i++)
    {
        packets[0][i] = new (0) u8[0x530];
        packets[1][i] = new (0) u8[0x530];
    }

    FlushCache(0);
}

/**
 * @brief Set the draw area's scale and resize it. A scaled display draws its second buffer's environment on its own.
 * @param unk3C77 Stored at 0x3C77.
 * @param scale_x Horizontal scale.
 * @param scale_y Vertical scale.
 * @param unk3C70 Stored at 0x3C70.
 */
void LibCameraContext::set_scale(u8 unk3C77, float scale_x, float scale_y, s16 unk3C70)
{
    apply_scale(unk3C77, scale_x, scale_y, unk3C70);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E0D20);

/** @brief Initialize the display. */
LibCameraContext::LibCameraContext()
{
    unk3C70 = -1;
    unk3E6A = 0;
    unk3E6B = 0;
    packet_queue = 0;

    for (s32 i = 0; i < LIB_DISPLAY_SCREEN_COUNT; i++)
    {
        memset_guess(&screens[i], 0, sizeof(LibDisplayScreen));
    }

    current_buffer = 0;

    for (s32 i = 0; i < LIB_DISPLAY_PACKET_COUNT; i++)
    {
        packets[0][i] = 0;
        packets[1][i] = 0;
    }

    for (s32 i = 0; i < LIB_DISPLAY_PACKET_LIST_COUNT; i++)
    {
        list_buffers[i] = 0;
        list_packets[i] = 0;
        list_sizes[i] = 0;
    }

    for (s32 i = 0; i < LIB_DISPLAY_PACKET_SET_COUNT; i++)
    {
        unk3E08[i] = 0;
    }

    unk3E34 = 0;
    unk3E48 = 0;
    unk3E10 = 0;
    blend_enabled = 0;
    packet_set = 0;
    unk3CB0 = 0;
    ready_index = 0;
    unk3E7C = 0;
    unk3C88[0] = 0;
    unk3C88[1] = 0;
    ready_packets[0] = 0;
    ready_packets[1] = 0;
    unk3CA8[0] = 0;
    unk3CA8[1] = 0;
    unk3E67 = 1;
}

const void* func_004E0FB0(void)
{
    return D_0050CD80;
}

/** @brief Initialize an identity orientation and unit scale, and mark the transform dirty. */
LibOrientedTransform::LibOrientedTransform()
{
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    scale.w = 1.0f;
    transform_dirty = 1;
    unk51 = 1;
    clear_vector(&orientation);
    orientation.w = 1.0f;
}

extern "C" void func_004E1020(void* object)
{
    ((ByteClear64Ownertext_004DD440*)object)->unk64 = 0;
    lib_finish_packet(static_cast<LibTransformOwner*>(object));
}

struct N50Owner114_004DD440
{
        u8 pad00[0x64];
        u8 active;
        u8 pad65[0xAF];
        ResidentPacket* owner;
};

void func_004E1040(N50Owner114_004DD440* object)
{
    object->active = 1;
    void* adjusted = object;
    if (object != 0)
    {
        adjusted = (u8*)adjusted + 0x108;
    }
    resident_packet_submit(object->owner, adjusted);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1080);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E10B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1140);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1280);

extern "C" void func_004E13D0(void* object)
{
    WordClearOwnertext_004DD440* receiver = static_cast<WordClearOwnertext_004DD440*>(object);
    receiver->unk114 = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E13E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1450);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1460);

/** @brief Clear the manager camera reference, then detach and queue the transform. */
void LibClass179080::destroy()
{
    LibDisplayManager* manager = static_cast<LibDisplayManager*>(owner);
    if (manager != 0 && manager->current_display == this)
    {
        manager->current_display = 0;
    }
    LibTransformOwner::destroy();
}

/** @brief Initialize viewport bounds and default projection settings. @param context Resident viewport context. */
void LibClass179080::initialize_projection(const LibCameraContext* context)
{
    horizontal_fov = 0.7853982f;
    s32 half_height = context->display_area.height / 2;
    s32 half_width = context->display_area.width / 2;
    screen_min.x = GS_COORDINATE_CENTRE - half_width;
    screen_min.y = GS_COORDINATE_CENTRE - half_height;
    screen_min.z = 100.0f;
    screen_min.w = 1.0f;
    screen_max.x = GS_COORDINATE_CENTRE + half_width;
    screen_max.y = GS_COORDINATE_CENTRE + half_height;
    screen_max.z = 16770000.0f;
    screen_max.w = 1.0f;
    unk3c8 = 10;
    unk3cc = 16770000;
    unk3d2 = 1;
    unk280 = 2048.0f;
    unk284 = 2048.0f;
    pixel_aspect = (1.3333334f * (1.0714285f * context->display_area.height)) / context->display_area.width;
    width_scale = 1.0f;
    unk270 = 1.0f;
}

/** @brief Upload the camera's clip geometry into VU0 data memory. */
void LibClass179080::upload_clip_geometry() const
{
    vu0_upload_clip_geometry(clip_points, clip_normals);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1670);

/** @brief Build the local perspective volume for visibility tests. @param volume Destination volume. */
void LibClass179080::build_projection_volume(LibProjectionVolume* volume) const
{
    FieldVec4A transverse_axis;
    FieldVec4A depth_axis;
    volume->origin = FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
    transverse_axis.x = -1.0f;
    transverse_axis.y = 0.0f;
    transverse_axis.z = 0.0f;
    transverse_axis.w = 1.0f;
    volume->near_half_width = (screen_min.z * (0.5f * (screen_max.x - screen_min.x))) / projection_distance;
    volume->x_axis = transverse_axis;
    float inverse_aspect = 1.0f / pixel_aspect;
    transverse_axis.x = 0.0f;
    transverse_axis.y = -1.0f;
    transverse_axis.z = 0.0f;
    transverse_axis.w = 1.0f;
    volume->near_half_height = (screen_min.z * (inverse_aspect * (0.5f * (screen_max.y - screen_min.y)))) /
                             projection_distance;
    volume->y_axis = transverse_axis;
    depth_axis.x = 0.0f;
    depth_axis.y = 0.0f;
    depth_axis.z = 1.0f;
    depth_axis.w = 1.0f;
    volume->z_axis = depth_axis;
    volume->near_distance = screen_min.z;
    volume->far_distance = screen_max.z;
    volume->update_coefficients();
}

/**
 * @brief Read the configured far and near fog factors.
 * @param far_factor Receives the far fog factor.
 * @param near_factor Receives the near fog factor.
 */
void LibClass179080::get_fog_factors(float* far_factor, float* near_factor) const
{
    *far_factor = far_fog_factor;
    *near_factor = near_fog_factor;
}

/** @brief Update the transform and extract its rotation components. */
void LibClass179080::update_transform_matrix()
{
    LibLookAtTransform::update_transform_matrix();
    func_004CEBA0(rotation_angles, get_transform_matrix());
}

/** @brief Update camera state and its attached-transform distance. */
void LibClass179080::update()
{
    unk63 = 0;
    LibTransform::update();
    transform_dirty = 1;
    if (static_cast<LibDisplayManager*>(owner)->current_display == this)
    {
        update_projection();
    }
    if (look_at_target != 0 && unk3d3 != 0)
    {
        FieldVec4B attached_position;
        FieldVec4B difference;
        lib_get_transform_translation(attached_position, *look_at_target);
        lib_get_transform_translation(difference, *this);
        difference -= attached_position;
        unk244 = lib_vector_length(difference);
    }
}

/**
 * @brief Set the perspective fog mapping coefficients directly.
 * @param offset Constant fog coefficient.
 * @param reciprocal_scale Reciprocal-distance fog coefficient.
 */
void LibClass179080::set_fog_coefficients(float offset, float reciprocal_scale)
{
    fog_offset = offset;
    fog_reciprocal_scale = reciprocal_scale;
}

/**
 * @brief Read the perspective fog mapping coefficients.
 * @param offset Receives the constant fog coefficient.
 * @param reciprocal_scale Receives the reciprocal-distance fog coefficient.
 */
void LibClass179080::get_fog_coefficients(float* offset, float* reciprocal_scale) const
{
    *offset = fog_offset;
    *reciprocal_scale = fog_reciprocal_scale;
}

/** @brief Set the near fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
void LibClass179080::set_near_fog_fraction(float fraction)
{
    near_fog_fraction = fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
}

/** @brief Set the far fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
void LibClass179080::set_far_fog_fraction(float fraction)
{
    far_fog_fraction = fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
}

/**
 * @brief Set the fog color, factors and distance range, then recompute the perspective coefficients.
 * @param color Packed RGB fog color.
 * @param far_factor Fog factor at the far distance.
 * @param near_factor Fog factor at the near distance.
 * @param near_distance Near fog distance.
 * @param far_distance Far fog distance.
 */
void LibClass179080::set_fog(u32 color, float far_factor, float near_factor, float near_distance, float far_distance)
{
    fog_color = color;
    far_fog_factor = far_factor;
    near_fog_factor = near_factor;
    far_fog_distance = far_distance;
    near_fog_distance = near_distance;
    update_fog_coefficients(far_factor, near_factor);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1E70__14LibClass179080Fv);

/** @brief Copy camera settings, the attached transform and inherited transform state. @param source Camera to copy. */
void LibClass179080::copy_camera(const LibClass179080* source)
{
    copy_view_and_fog(source);
    look_at_target = source->look_at_target;
    LibTransform::copy_offset_transform_state(source);
}

/** @brief Copy the camera's view and fog settings. @param source Camera to copy. */
void LibClass179080::copy_view_and_fog(const LibClass179080* source)
{
    unk3c8 = source->unk3c8;
    unk3cc = source->unk3cc;
    pixel_aspect = source->pixel_aspect;
    screen_min = source->screen_min;
    screen_max = source->screen_max;
    unk280 = source->unk280;
    unk284 = source->unk284;
    unk3d2 = source->unk3d2;
    width_scale = source->width_scale;
    unk254 = source->unk254;
    unk270 = source->unk270;
    unk3d1 = source->unk3d1;
    horizontal_fov = source->horizontal_fov;
    unk3d3 = source->unk3d3;
    unk244 = source->unk244;
    unk24c = source->unk24c;
    mode = source->mode;
    anchor = source->anchor;
    unk260 = source->unk260;
    unk264 = source->unk264;
    unk268 = source->unk268;
    unk26c = source->unk26c;
    fog_color = source->fog_color;
    float near_factor = source->near_fog_factor;
    float far_factor = source->far_fog_factor;
    far_fog_factor = far_factor;
    near_fog_factor = near_factor;
    near_fog_distance = source->near_fog_distance;
    far_fog_distance = source->far_fog_distance;
    near_fog_fraction = source->near_fog_fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
    far_fog_fraction = source->far_fog_fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
    fog_enabled = source->fog_enabled;
}

/** @brief Submit the camera's DMA chain. @param channel DMA channel number. */
void LibClass179080::submit_dma(u32 channel)
{
    DmaChannel* dma = sceDmaGetChan(channel);
    dma->chcr.tag_transfer_enable = 0;
    sceDmaSend(dma, &dma_chain);
}

/** @brief Complete the camera transfer. @param channel DMA channel number; unused. */
void LibClass179080::complete_dma(u32 channel)
{
}

/** @brief Queue the camera for VIF1 DMA. @return 1 on success, 0 when the queue is full. */
s32 LibClass179080::enqueue_submission()
{
    return func_00114100(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2120__14LibClass179080Fv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E22B0);

/** Field of view the camera uses while it faces the current camera (90 degrees). */
#define LIB_FACE_CAMERA_FOV 1.5707964f

/** @brief Rebuild the view and projection matrices and upload the projection to VU0. */
void LibClass179080::update_projection()
{
    switch (mode)
    {
    case LIB_CAMERA_MODE_FACE_CURRENT_CAMERA:
        horizontal_fov = LIB_FACE_CAMERA_FOV;
        set_translation_vector(&anchor->translation);
        LibClass179080* camera = static_cast<LibClass179080*>(g_display_manager->current_display);

        if (camera == 0)
        {
            return;
        }

        if (!camera->matrix_ready)
        {
            camera->update_projection();
        }

        update_transform_matrix();
        LibMatrix44Value look;
        FieldVec4B target;
        FieldVec4B position;
        FieldVec4B rotation;
        lib_get_transform_translation(position, *this);
        lib_get_transform_translation(target, *camera);
        target = lib_vector_difference(target, position);
        lib_matrix_look_at(&look, &position, &target, 0.0f);
        lib_matrix_to_quaternion(&rotation, &look);
        set_orientation(reinterpret_cast<const LibVector4*>(&rotation));
        break;
    }

    update_transform_matrix();
    view_matrix = func_004CF0B0(*get_transform_matrix());
    float half_width = (unk254 * width_scale) * (screen_max.x - screen_min.x) / 2.0f;
    projection_distance = half_width / func_00141EC0(horizontal_fov / 2.0f);

    if (unk3d2)
    {
        screen_min.z = projection_distance / 16.0f;
    }

    func_004CFD80(&projection_matrix, projection_distance, pixel_aspect, unk280 - unk3e0, unk284 - unk3e4, unk3c8, unk3cc, screen_min.z,
                  screen_max.z);
    vu0_start_microprogram_1f0_vf5_vf8(&projection_matrix);
    FieldVec4A centre(0.0f, 0.0f, projection_distance * unk270, 1.0f);
    vu0_start_microprogram_vf5(&centre);
    FieldVec4A low(screen_min.x, screen_min.y, screen_min.z, 1.0f);
    FieldVec4A high(screen_max.x, screen_max.y, screen_max.z, 1.0f);
    func_004CF930(&unk340, &low, &high, projection_distance, pixel_aspect);
    vu0_wait_microprogram();
    vu0_read_vf6(&centre);
    centre_depth = centre.z;
    LibMatrix44Value clip;
    func_004CFA30(&clip, &low, &high, projection_distance, pixel_aspect, unk280 - unk3e0, unk284 - unk3e4, unk3c8, unk3cc);
    unk380 = func_004CECD0(clip);
    func_004E1670(this);
}

/**
 * @brief Calculate the scaled screen-plane distance from the horizontal field of view.
 * @return Perspective projection distance.
 */
float LibClass179080::compute_projection_distance() const
{
    float half_width = (unk254 * width_scale) * (screen_max.x - screen_min.x) / 2.0f;
    return half_width / func_00141EC0(horizontal_fov / 2.0f);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E29E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2DE0);

void func_004E2E30(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2E40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2EC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2ED0);

/** @brief Draw in bucket 10. */
void LibColorFade::set_default_draw_bucket()
{
    draw_bucket = 10;
}

/**
 * @brief Return the list a colour fade goes in.
 * @return List kind 3.
 */
s32 LibColorFade::get_default_list_kind()
{
    return 3;
}

/**
 * @brief Finish the fade's drawing packet.
 * @param value Notification word.
 */
void LibColorFade::on_packet_complete(u32 value)
{
    lib_finish_packet(this);
}

/** @brief Mark the fade pending and submit its packet. */
void LibColorFade::render()
{
    dma_pending = 1;
    resident_packet_submit(packet, static_cast<LibDmaCallbacks*>(this));
}

/**
 * @brief Build the packet: one sprite over the rectangle, scaled to the display.
 * @param matrix Matrix supplied by the caller; unused.
 * @param context Opaque caller context; unused.
 */
void LibColorFade::build_packet(const void* matrix, void* context)
{
    float scale_x;
    float scale_y;

    resident_packet_rewind(packet);
    packet->unk15 = 1;
    func_0011F140(packet, D_4ED330[0]);
    g_display->get_area_scale(&scale_x, &scale_y);
    func_0011F1D0(packet, rect.x, rect.y, (s32)(rect.width * scale_x) + 1, (s32)(rect.height * scale_y) + 1, depth, color);
    unk63 = 1;
}

/** @brief Blend the colour for the time so far; once the fade is over, destroy it. */
void LibColorFade::update()
{
    s32 shift;

    color = 0;

    for (shift = 0; shift < 32; shift += 8)
    {
        s32 from = (start_color >> shift) & 0xFF;
        s32 to = (end_color >> shift) & 0xFF;
        color |= (s32)(from + elapsed * (to - from) / duration) << shift;
    }

    elapsed += g_frame_ticks;

    if (elapsed >= duration)
    {
        destroy();
        return;
    }
}

/** @brief Release the packet. */
LibColorFade::~LibColorFade()
{
    delete packet;
}

/** @brief Clear the colour and time, take the default area and depth, and allocate the packet. */
void LibColorFade::reset()
{
    color = 0;
    elapsed = 0.0f;
    rect = D_0050CD40;
    depth = D_001B6694;
    packet = new (0) LibPacketBuffer(16);
}

/**
 * @brief Detach a list object from its owner.
 * @param object Object to detach.
 */
static inline void lib_detach(LibListObject& object)
{
    lib_object_detach_owner(&object);
}

/** @brief Destroy Lib's global objects, free their storage and clear the pointers. */
extern "C" void lib_shutdown(void)
{
    lib_detach(*D_001B6660);
    D_001B6660->destroy();
    D_001B6660 = 0;
    lib_detach(*D_001B665C);
    D_001B665C->destroy();
    D_001B665C = 0;
    lib_detach(*D_001B6640);
    delete g_screen_text;
    ::operator delete(D_001B6644);
    D_001B6640->destroy();

    if (D_001B6638 != (void*)EE_SCRATCHPAD)
    {
        ::operator delete(D_001B6638);
    }

    if (g_texture_cache != (void*)EE_SCRATCHPAD)
    {
        ::operator delete(g_texture_cache);
    }

    delete g_vif1_dma_queue;
    delete D_001B660C;
    delete D_001B6608;
    delete D_001B6604;
    ::operator delete(g_microcode_loader);
    delete D_001B65FC;
    g_screen_text = 0;
    D_001B6644 = 0;
    D_001B6640 = 0;
    D_001B6638 = 0;
    g_texture_cache = 0;
    g_vif1_dma_queue = 0;
    D_001B660C = 0;
    D_001B6608 = 0;
    D_001B6604 = 0;
    g_microcode_loader = 0;
    D_001B65FC = 0;

    lib_detach(*g_scene_camera);
    lib_detach(*D_001B664C);
    lib_detach(*D_001B6620);
    lib_detach(*D_001B6648);
    g_update_list->func_004295B0(0);
    lib_detach(*g_display_manager);
    lib_detach(*g_scene_display_manager);
    lib_detach(*D_001B6624);
    g_scene_camera->destroy();
    D_001B6634->destroy();
    lib_object_detach_owner(g_resource_queue);
    lib_detach(D_00507CB8);
    g_scene_camera = 0;
    D_001B6634 = 0;

    delete g_quaternion_track_pool;
    delete g_quaternion_curve_track_pool;
    delete g_float_track_pool;
    delete g_vector_track_pool;
    delete g_slerp_quaternion_track_pool;
    delete g_float_curve_track_pool;
    delete g_vector_curve_track_pool;
    delete g_float_quaternion_track_pool;
    g_quaternion_track_pool = 0;
    g_quaternion_curve_track_pool = 0;
    g_float_track_pool = 0;
    g_vector_track_pool = 0;
    g_slerp_quaternion_track_pool = 0;
    g_float_curve_track_pool = 0;
    g_vector_curve_track_pool = 0;
    g_float_quaternion_track_pool = 0;

    D_001B664C->destroy();
    D_001B6648->destroy();
    g_default_display_manager->destroy();
    g_scene_display_manager->destroy();
    D_001B6624->destroy();
    D_001B6620->destroy();
    delete static_cast<LibRenderer*>(g_renderer);
    delete g_vram_allocator;
    delete g_packet_queue;
    delete g_update_list;
    ::operator delete(g_display_callbacks);
    resident_get_system()->unk15C80 = 0;
    D_001B664C = 0;
    D_001B6648 = 0;
    g_default_display_manager = 0;
    g_scene_display_manager = 0;
    D_001B6624 = 0;
    D_001B6620 = 0;
    g_renderer = 0;
    g_vram_allocator = 0;
    g_packet_queue = 0;
    g_update_list = 0;
    g_display_callbacks = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", lib_initialize);

/** List object with vtable D_1791E0 in main data; its update flips a parity flag every frame. */
class LibClass1791E0 : public LibListObject
{
    public:
        /** @brief Start with the parity clear. */
        LibClass1791E0() : parity(0)
        {
        }

        /** @brief Destroy the object. */
        virtual ~LibClass1791E0();

        /**
         * @brief Return the list the object goes in.
         * @return List kind 16.
         */
        virtual s32 get_default_list_kind();

        /** @brief Flip the parity flag. */
        virtual void update();

        /** Flips between 0 and 1 on every update. */
        u32 parity;
};

/** @brief Destroy the object. */
LibClass1791E0::~LibClass1791E0()
{
}

/**
 * @brief Return the list the object goes in.
 * @return List kind 16.
 */
s32 LibClass1791E0::get_default_list_kind()
{
    return 16;
}

/** @brief Flip the parity flag. */
void LibClass1791E0::update()
{
    parity ^= 1;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4500);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4590, D_00179270)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E45C0);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4650, D_00179260)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4680);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4710, D_00179250)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4740);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E47D0, D_00179240)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4800);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4890, D_00179230)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E48C0);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4950, D_00179220)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4980);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4A10, D_00179210)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4A40);

DEFINE_FIELD_ARGUMENT_INITIALIZER(func_004E4AD0, D_00179200)

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4B00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4CA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4E40);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E4EC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5060);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E53A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5410);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E55A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5740);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E58E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5940);

void func_004E59A0(void* object)
{
    func_004E6690(object);
    func_004E6B30(g_vector_curve_track_pool, object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E59D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5A30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5AA0);

void func_004E5B00(void* object)
{
    func_004E6A90(object);
    func_004E6AE0(g_vector_track_pool, object);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5C10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5C80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5D30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5DA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5E10);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5E80);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5F60);

extern "C" void func_004E5FA0(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xC0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E5FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6040);

extern "C" void func_004E60B0(const void* object, FieldVec4B* output)
{
    *output = *(const FieldVec4A*)((const u8*)object + 0xA0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E60D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6170);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6200);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6280);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E62F0);

/** Set the low packed mode at 0x52 and record whether either mode equals four. */
void func_004E6340(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.lowMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Set the high packed mode at 0x52 and record whether either mode equals four. */
void func_004E63A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at52.highMode = mode;
    receiver->at52.hasModeFour = receiver->at52.lowMode == 4 || receiver->at52.highMode == 4;
}

/** Return the signed halfword at receiver offset 0x48. */
s16 func_004E6400(const void* object)
{
    const HalfwordGetterOwnertext_004DD440* receiver = static_cast<const HalfwordGetterOwnertext_004DD440*>(object);
    return receiver->unk48;
}

/** Return the signed halfword at receiver offset 0x4A. */
s16 func_004E6410(const void* object)
{
    const HalfwordGetterOwnertext_004DD440* receiver = static_cast<const HalfwordGetterOwnertext_004DD440*>(object);
    return receiver->unk4a;
}

s32 func_004E6420(void* object)
{
    return 0;
}

s32 func_004E6430(void* object)
{
    return 0;
}

s32 func_004E6440(void* object)
{
    return 0;
}

void func_004E6450(void* object)
{
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004E6460(void* object, float key)
{
    FloatKeyScanOwner_text_004DD440_30* receiver = static_cast<FloatKeyScanOwner_text_004DD440_30*>(object);
    s16 count = receiver->count48;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_004E64B0(void* object)
{
    FourWordClearOwnertext_004DD440* receiver = (FourWordClearOwnertext_004DD440*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E64D0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6520);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6590);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E65E0);

/** Return the word at receiver offset 0x4. */
u32 func_004E6680(const void* object)
{
    const WordGetterOwnertext_004DD440* receiver = static_cast<const WordGetterOwnertext_004DD440*>(object);
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6690);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E66E0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6750);

/** Set the low packed mode at 0x32 and record whether either mode equals four. */
void func_004E67A0(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at32.lowMode = mode;
    receiver->at32.hasModeFour = receiver->at32.lowMode == 4 || receiver->at32.highMode == 4;
}

/** Set the high packed mode at 0x32 and record whether either mode equals four. */
void func_004E6800(void* object, u8 mode)
{
    PackedModesOwner* receiver = static_cast<PackedModesOwner*>(object);
    receiver->at32.highMode = mode;
    receiver->at32.hasModeFour = receiver->at32.lowMode == 4 || receiver->at32.highMode == 4;
}

/** Return the signed halfword at receiver offset 0x28. */
s16 func_004E6860(const void* object)
{
    const HalfwordGetterOwnertext_004DD440* receiver = static_cast<const HalfwordGetterOwnertext_004DD440*>(object);
    return receiver->unk28;
}

/** Return the signed halfword at receiver offset 0x2A. */
s16 func_004E6870(const void* object)
{
    const HalfwordGetterOwnertext_004DD440* receiver = static_cast<const HalfwordGetterOwnertext_004DD440*>(object);
    return receiver->unk2a;
}

/** Find a key in the receiver's fixed-size entry array. */
/** Find a key in the receiver's fixed-size entry array. */
s32 func_004E6880(void* object, float key)
{
    FloatKeyScanOwner_text_004DD440_10* receiver = static_cast<FloatKeyScanOwner_text_004DD440_10*>(object);
    s16 count = receiver->count28;
    s32 index;
    for (index = 0; index < count; index++)
    {
        if (key == receiver->entries[index].key0c)
        {
            return 1;
        }
    }
    return 0;
}

void func_004E68D0(void* object)
{
    FourWordClearOwnertext_004DD440* receiver = (FourWordClearOwnertext_004DD440*)object;
    receiver->words[0] = 0;
    receiver->words[1] = 0;
    receiver->words[2] = 0;
    receiver->words[3] = 0;
}

/** Return the key span between the first and last entries. */
float func_004E68F0(void* object)
{
    const FloatKeyScanOwner_text_004DD440_10* receiver = static_cast<const FloatKeyScanOwner_text_004DD440_10*>(object);
    s32 count = receiver->count28;
    if (count < 2)
    {
        return 0.0f;
    }
    const FloatKeyScanEntry_text_004DD440_10* entries = receiver->entries;
    const FloatKeyScanEntry_text_004DD440_10* lastEntry = entries + --count;
    float first = entries[0].key0c;
    float last = lastEntry->key0c;
    return last - first;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E69A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E69F0);

/** Return the word at receiver offset 0x4. */
u32 func_004E6A80(const void* object)
{
    const WordGetterOwnertext_004DD440* receiver = static_cast<const WordGetterOwnertext_004DD440*>(object);
    return receiver->unk04;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6A90);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6AE0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6B30);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6B80);

void func_004E6BB0(void* object)
{
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6BC0);

s32 func_004E6BF0(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6C00);

s32 func_004E6C30(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6C40);

s32 func_004E6C70(void* object)
{
    return 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6C80);

void* func_004E6D30(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6D40);

void* func_004E6DF0(void* value)
{
    return value;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6E00);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6E60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6F60);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E6FC0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7050);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7190);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E71C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E71F0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7220);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7770);

s32 func_004E7820(void* object)
{
    return 8;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7830);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E8510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9260);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9290);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E95C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E96A0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E96B0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E96C0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E96D0);

extern "C" void lib_factor_tooltip_hide(void* object)
{
    ByteClearOwnertext_004DD440* receiver = static_cast<ByteClearOwnertext_004DD440*>(object);
    receiver->unkcb = 0;
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", lib_factor_tooltip_show);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9940);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", lib_factor_tooltip_init);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9CD0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9F70);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9FE0);
