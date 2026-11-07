#include "include_asm.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/camera_vu0.h"
#include "overlays/lib/light_vu0.h"
#include "overlays/lib/model.h"
#include "overlays/lib/tracks.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "vu0.h"
#include "ee.h"
#include "main/resident_data.h"

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
extern LibTrackPool<LibPooledFloatTrack>* g_float_track_pool;
extern LibTrackPool<LibPooledVectorTrack>* g_vector_track_pool;
extern LibTrackPool<LibPooledSlerpQuaternionTrack>* g_slerp_quaternion_track_pool;
extern LibTrackPool<LibPooledFloatCurveTrack>* g_float_curve_track_pool;
extern LibTrackPool<LibPooledVectorCurveTrack>* g_vector_curve_track_pool;
extern LibTrackPool<LibPooledFloatQuaternionTrack>* g_float_quaternion_track_pool;
extern LibTrackPool<LibPooledQuaternionCurveTrack>* g_quaternion_curve_track_pool;
extern LibTrackPool<LibPooledQuaternionTrack>* g_quaternion_track_pool;
extern void* g_display_callbacks;
}

/**
 * @brief Mark a track's g_vector_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_track_pool_free(LibTrackPool<LibPooledVectorTrack>* pool, LibPooledVectorTrack* track);

/**
 * @brief Mark a track's g_vector_curve_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_curve_track_pool_free(LibTrackPool<LibPooledVectorCurveTrack>* pool, LibPooledVectorCurveTrack* track);

/**
 * @brief Return a vector, or a zeroed fallback when it is missing.
 * @param vector Optional vector.
 * @param zero Storage for the zero vector.
 * @return The vector, or zero after clearing it.
 */
static inline const FieldVec4A* track_vector(const FieldVec4A* vector, FieldVec4A* zero)
{
    if (!vector)
    {
        zero->x = 0.0f;
        zero->y = 0.0f;
        zero->z = 0.0f;
        zero->w = 0.0f;
        return zero;
    }

    return vector;
}

/**
 * @brief Subtract the first three components.
 * @param left Vector to subtract from.
 * @param right Vector to subtract.
 * @return Difference, keeping the left vector's fourth component.
 */
static inline FieldVec4A sequence_difference(const FieldVec4B& left, const FieldVec4B& right)
{
    FieldVec4A value;
    *(unsigned __int128*)&value = *(const unsigned __int128*)&left;
    value.x -= right.x;
    value.y -= right.y;
    value.z -= right.z;
    return value;
}

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
void LibCamera::destroy()
{
    LibDisplayManager* manager = static_cast<LibDisplayManager*>(owner);
    if (manager != 0 && manager->current_display == this)
    {
        manager->current_display = 0;
    }
    LibTransformOwner::destroy();
}

/** @brief Initialize viewport bounds and default projection settings. @param context Resident viewport context. */
void LibCamera::initialize_projection(const LibCameraContext* context)
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
void LibCamera::upload_clip_geometry() const
{
    vu0_upload_clip_geometry(clip_points, clip_normals);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1670);

/** @brief Build the local perspective volume for visibility tests. @param volume Destination volume. */
void LibCamera::build_projection_volume(LibProjectionVolume* volume) const
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
void LibCamera::get_fog_factors(float* far_factor, float* near_factor) const
{
    *far_factor = far_fog_factor;
    *near_factor = near_fog_factor;
}

/** @brief Update the transform and extract its rotation components. */
void LibCamera::update_transform_matrix()
{
    LibLookAtTransform::update_transform_matrix();
    func_004CEBA0(rotation_angles, get_transform_matrix());
}

/** @brief Update camera state and its attached-transform distance. */
void LibCamera::update()
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
void LibCamera::set_fog_coefficients(float offset, float reciprocal_scale)
{
    fog_offset = offset;
    fog_reciprocal_scale = reciprocal_scale;
}

/**
 * @brief Read the perspective fog mapping coefficients.
 * @param offset Receives the constant fog coefficient.
 * @param reciprocal_scale Receives the reciprocal-distance fog coefficient.
 */
void LibCamera::get_fog_coefficients(float* offset, float* reciprocal_scale) const
{
    *offset = fog_offset;
    *reciprocal_scale = fog_reciprocal_scale;
}

/** @brief Set the near fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
void LibCamera::set_near_fog_fraction(float fraction)
{
    near_fog_fraction = fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
}

/** @brief Set the far fog-distance fraction and recompute fog coefficients. @param fraction Fraction of the configured distance range. */
void LibCamera::set_far_fog_fraction(float fraction)
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
void LibCamera::set_fog(u32 color, float far_factor, float near_factor, float near_distance, float far_distance)
{
    fog_color = color;
    far_fog_factor = far_factor;
    near_fog_factor = near_factor;
    far_fog_distance = far_distance;
    near_fog_distance = near_distance;
    update_fog_coefficients(far_factor, near_factor);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E1E70__9LibCameraFv);

/** @brief Copy camera settings, the attached transform and inherited transform state. @param source Camera to copy. */
void LibCamera::copy_camera(const LibCamera* source)
{
    copy_view_and_fog(source);
    look_at_target = source->look_at_target;
    LibTransform::copy_offset_transform_state(source);
}

/** @brief Copy the camera's view and fog settings. @param source Camera to copy. */
void LibCamera::copy_view_and_fog(const LibCamera* source)
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
void LibCamera::submit_dma(u32 channel)
{
    DmaChannel* dma = sceDmaGetChan(channel);
    dma->chcr.tag_transfer_enable = 0;
    sceDmaSend(dma, &dma_chain);
}

/** @brief Complete the camera transfer. @param channel DMA channel number; unused. */
void LibCamera::complete_dma(u32 channel)
{
}

/** @brief Queue the camera for VIF1 DMA. @return 1 on success, 0 when the queue is full. */
s32 LibCamera::enqueue_submission()
{
    return func_00114100(g_vif1_dma_queue, this);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E2120__9LibCameraFv);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E22B0);

/** Field of view the camera uses while it faces the current camera (90 degrees). */
#define LIB_FACE_CAMERA_FOV 1.5707964f

/** @brief Rebuild the view and projection matrices and upload the projection to VU0. */
void LibCamera::update_projection()
{
    switch (mode)
    {
    case LIB_CAMERA_MODE_FACE_CURRENT_CAMERA:
        horizontal_fov = LIB_FACE_CAMERA_FOV;
        set_translation_vector(&anchor->translation);
        LibCamera* camera = static_cast<LibCamera*>(g_display_manager->current_display);

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
float LibCamera::compute_projection_distance() const
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
    lib_detach(*g_light_list);
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
    g_light_list->destroy();
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
    g_light_list = 0;
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

/**
 * @brief Release every track in g_float_track_pool and its storage.
 * @param pool Pool to clear.
 */
void float_track_pool_release(LibTrackPool<LibPooledFloatTrack>* pool)
{
    pool->release();
}

/**
 * @brief Release every track in g_vector_track_pool and its storage.
 * @param pool Pool to clear.
 */
void vector_track_pool_release(LibTrackPool<LibPooledVectorTrack>* pool)
{
    pool->release();
}

/** @brief Destroy the track. */
LibPooledVectorTrack::~LibPooledVectorTrack()
{
}

/**
 * @brief Release every track in g_slerp_quaternion_track_pool and its storage.
 * @param pool Pool to clear.
 */
void slerp_quaternion_track_pool_release(LibTrackPool<LibPooledSlerpQuaternionTrack>* pool)
{
    pool->release();
}

/**
 * @brief Release every track in g_float_curve_track_pool and its storage.
 * @param pool Pool to clear.
 */
void float_curve_track_pool_release(LibTrackPool<LibPooledFloatCurveTrack>* pool)
{
    pool->release();
}

/**
 * @brief Release every track in g_vector_curve_track_pool and its storage.
 * @param pool Pool to clear.
 */
void vector_curve_track_pool_release(LibTrackPool<LibPooledVectorCurveTrack>* pool)
{
    pool->release();
}

/** @brief Destroy the track. */
LibPooledVectorCurveTrack::~LibPooledVectorCurveTrack()
{
}

/**
 * @brief Release every track in g_float_quaternion_track_pool and its storage.
 * @param pool Pool to clear.
 */
void float_quaternion_track_pool_release(LibTrackPool<LibPooledFloatQuaternionTrack>* pool)
{
    pool->release();
}

/**
 * @brief Release every track in g_quaternion_curve_track_pool and its storage.
 * @param pool Pool to clear.
 */
void quaternion_curve_track_pool_release(LibTrackPool<LibPooledQuaternionCurveTrack>* pool)
{
    pool->release();
}

/**
 * @brief Release every track in g_quaternion_track_pool and its storage.
 * @param pool Pool to clear.
 */
void quaternion_track_pool_release(LibTrackPool<LibPooledQuaternionTrack>* pool)
{
    pool->release();
}

/** @brief Return a pooled track to its pool, or delete an ordinary track. */
void LibPooledVectorCurveTrack::release()
{
    if (this != 0)
    {
        if (state.pooled)
        {
            return_to_pool();
        }
        else
        {
            delete this;
        }
    }
}

/**
 * @brief Free a pooled track's keys and give the track back to its pool.
 */
void LibPooledVectorCurveTrack::return_to_pool()
{
    free_keys();
    vector_curve_track_pool_free(g_vector_curve_track_pool, this);
}

/** @brief Return a pooled track to its pool, or delete an ordinary track. */
void LibPooledVectorTrack::release()
{
    if (this != 0)
    {
        if (state.pooled)
        {
            return_to_pool();
        }
        else
        {
            delete this;
        }
    }
}

/** @brief Free the keys and give the track back to g_vector_track_pool. */
void LibPooledVectorTrack::return_to_pool()
{
    free_keys();
    vector_track_pool_free(g_vector_track_pool, this);
}

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorCurveTrack::append_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    static_cast<LibVectorCurveTrackKey*>(key_array)[state.key_count].value = *value;
    static_cast<LibVectorCurveTrackKey*>(key_array)[state.key_count].in_tangent = *in_tangent;
    static_cast<LibVectorCurveTrackKey*>(key_array)[state.key_count].out_tangent = *out_tangent;
    static_cast<LibVectorCurveTrackKey*>(key_array)[state.key_count].value.w = key;
    state.span = key - static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w;
    state.key_count++;
    return 1;
}

/**
 * @brief Append a keyframe, using zero vectors for missing auxiliary vectors.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorCurveTrack::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    out_tangent = track_vector(static_cast<const FieldVec4A*>(out_tangent), &zero_second);
    in_tangent = track_vector(static_cast<const FieldVec4A*>(in_tangent), &zero_first);
    return append_curve_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorCurveTrack::replace_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    static_cast<LibVectorCurveTrackKey*>(key_array)[index].value = *value;
    static_cast<LibVectorCurveTrackKey*>(key_array)[index].in_tangent = *in_tangent;
    static_cast<LibVectorCurveTrackKey*>(key_array)[index].out_tangent = *out_tangent;
    static_cast<LibVectorCurveTrackKey*>(key_array)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w;
    }

    return 1;
}

/**
 * @brief Replace an indexed keyframe, using zero vectors for missing auxiliary vectors.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorCurveTrack::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    out_tangent = track_vector(static_cast<const FieldVec4A*>(out_tangent), &zero_second);
    in_tangent = track_vector(static_cast<const FieldVec4A*>(in_tangent), &zero_first);
    return replace_curve_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Insert a keyframe, using zero vectors for missing auxiliary vectors.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorCurveTrack::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    out_tangent = track_vector(static_cast<const FieldVec4A*>(out_tangent), &zero_second);
    in_tangent = track_vector(static_cast<const FieldVec4A*>(in_tangent), &zero_first);
    return insert_curve_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Store a single keyframe, using zero vectors for missing auxiliary vectors.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void LibVectorCurveTrack::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    FieldVec4A zero_first;
    FieldVec4A zero_second;
    out_tangent = track_vector(static_cast<const FieldVec4A*>(out_tangent), &zero_second);
    in_tangent = track_vector(static_cast<const FieldVec4A*>(in_tangent), &zero_first);
    set_single_curve_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key.
 * @param value Receives the value.
 * @param first Receives the first auxiliary vector.
 * @param second Receives the second auxiliary vector.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 LibVectorCurveTrack::read_key(s32 index, float* key, void* value, void* first, void* second) const
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = static_cast<const LibVectorCurveTrackKey*>(key_array)[index].value.w;
    }

    if (value)
    {
        *static_cast<FieldVec4B*>(value) = static_cast<const LibVectorCurveTrackKey*>(key_array)[index].value;
    }

    if (first)
    {
        *static_cast<FieldVec4B*>(first) = static_cast<const LibVectorCurveTrackKey*>(key_array)[index].in_tangent;
    }

    if (second)
    {
        *static_cast<FieldVec4B*>(second) = static_cast<const LibVectorCurveTrackKey*>(key_array)[index].out_tangent;
    }

    return 1;
}

/** @brief Reset to a single zero keyframe at key zero. */
void LibVectorCurveTrack::reset_keys()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    set_single_key(&zero, &zero, &zero, 0.0f);
}

/**
 * @brief Return how fast the value changed at the last sample, per second.
 * @param output Receives the rate.
 */
void LibVectorCurveTrack::get_value_rate(void* output) const
{
    *static_cast<FieldVec4B*>(output) = *reinterpret_cast<const FieldVec4A*>(&value_rate);
}

/**
 * @brief Return the difference between the endpoint vectors.
 * @param output Receives the difference.
 */
void LibVectorCurveTrack::get_end_delta(void* output) const
{
    if (key_array != 0)
    {
        *static_cast<FieldVec4B*>(output) = sequence_difference(static_cast<const LibVectorCurveTrackKey*>(key_array)[state.key_count - 1].value,
                                      static_cast<const LibVectorCurveTrackKey*>(key_array)[0].value);
    }
}

/**
 * @brief Write the difference between the last and first key values.
 * @param output Receives the difference.
 */
void LibVectorTrack::get_end_delta(void* output) const
{
    if (key_array != 0)
    {
        *static_cast<FieldVec4B*>(output) = sequence_difference(static_cast<const LibVectorTrackKey*>(key_array)[state.key_count - 1].value,
                                                                 static_cast<const LibVectorTrackKey*>(key_array)[0].value);
    }
}

/**
 * @brief Write how fast the value changed at the last sample, per second.
 * @param output Receives the rate.
 */
void LibVectorTrack::get_value_rate(void* output) const
{
    *static_cast<FieldVec4B*>(output) = *reinterpret_cast<const FieldVec4A*>(&value_rate);
}

/**
 * @brief Append a keyframe.
 * @param value Keyframe value.
 * @param key Sort key, stored in the value's w.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorKeyTrack::on_append_key(const FieldVec4A* value, float key)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (state.key_count >= state.key_capacity)
    {
        return 0;
    }

    static_cast<LibVectorTrackKey*>(key_array)[state.key_count].value = *value;
    static_cast<LibVectorTrackKey*>(key_array)[state.key_count].value.w = key;
    state.span = key - static_cast<LibVectorTrackKey*>(key_array)[0].value.w;
    state.segment_lower = -1;
    state.segment_upper = -1;
    state.key_count++;
    return 1;
}

/**
 * @brief Replace an indexed keyframe.
 * @param index Keyframe index.
 * @param key Sort key, stored in the value's w.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorKeyTrack::on_replace_key(s32 index, float key, const FieldVec4A* value)
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    static_cast<LibVectorTrackKey*>(key_array)[index].value = *value;
    static_cast<LibVectorTrackKey*>(key_array)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<LibVectorTrackKey*>(key_array)[0].value.w;
    }

    state.segment_lower = -1;
    state.segment_upper = -1;
    return 1;
}

/**
 * @brief Read an indexed keyframe.
 * @param index Keyframe index.
 * @param key Receives the sort key, or null.
 * @param value Receives the value, or null.
 * @param first Unused; these keys have no tangents.
 * @param second Unused; these keys have no tangents.
 * @return One when the index is within the capacity, otherwise zero.
 */
s32 LibVectorKeyTrack::read_key(s32 index, float* key, void* value, void* first, void* second) const
{
    if (key_array == 0)
    {
        return 0;
    }

    if (index >= state.key_capacity)
    {
        return 0;
    }

    if (key)
    {
        *key = static_cast<const LibVectorTrackKey*>(key_array)[index].value.w;
    }

    if (value)
    {
        *static_cast<FieldVec4B*>(value) = static_cast<const LibVectorTrackKey*>(key_array)[index].value;
    }

    return 1;
}

/** @brief Release the keyframe storage. */
LibVectorCurveTrackBase::~LibVectorCurveTrackBase()
{
    free_keys();
}

/**
 * @brief Bind external 48-byte records and cache their first-to-last key span.
 * @param count Positive entry count representable in the receiver count fields.
 * @param keys External storage containing the specified number of entries.
 */
void LibVectorCurveTrackBase::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    LibVectorCurveTrackKey* last;
    state.external_keys = 1;
    key_array = static_cast<LibVectorCurveTrackKey*>(keys);
    state.key_capacity = count;
    state.key_count = count;
    last = static_cast<LibVectorCurveTrackKey*>(key_array) + last_index;
    state.span = last->value.w - static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w;
}

/**
 * @brief Set the low packed value and flag whether either packed value is 4.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibVectorCurveTrackBase::set_before_mode(u32 mode)
{
    state.before_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the high packed value and flag whether either packed value is 4.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibVectorCurveTrackBase::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibVectorCurveTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibVectorCurveTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 * @return Zero.
 */
s32 LibVectorCurveTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 LibVectorCurveTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @return Zero.
 */
s32 LibVectorCurveTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
{
    return 0;
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Key value.
 * @param first First auxiliary vector.
 * @param second Second auxiliary vector.
 * @param key Key the keyframe sits at.
 */
void LibVectorCurveTrackBase::on_set_single_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
{
}

/**
 * @brief Test whether the 48-byte record array contains an exactly equal key.
 * @param key Scalar key to find.
 * @return One for an equal key, or zero when none is present.
 */
s32 LibVectorCurveTrackBase::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == static_cast<LibVectorCurveTrackKey*>(key_array)[index].value.w)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Return a zero vector; the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A LibVectorCurveTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Return the last-to-first key difference, or zero below two records.
 * @return Difference between the last and first scalar keys, or zero.
 */
float LibVectorCurveTrackBase::get_key_span() const
{
    s32 last_index;
    LibVectorCurveTrackKey* last_entry;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last_index = state.key_count - 1;
    last_entry = static_cast<LibVectorCurveTrackKey*>(key_array) + last_index;
    return last_entry->value.w - static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w;
}

/**
 * @brief Read the vector value associated with the first exactly equal key.
 * @param key Key to find.
 * @return Associated value, or a zero vector when no key matches.
 */
FieldVec4A LibVectorCurveTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == static_cast<LibVectorCurveTrackKey*>(key_array)[index].value.w)
        {
            LibVectorCurveTrackKey* entry = static_cast<LibVectorCurveTrackKey*>(key_array) + index;
            return *reinterpret_cast<const FieldVec4A*>(entry);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void LibVectorCurveTrackBase::evaluate(float key, void* output)
{
    *static_cast<FieldVec4B*>(output) = sample(key);
}

/**
 * @brief Adjust a scalar key by whole spans determined from the endpoint records.
 * @param key Scalar key whose normalized span quotient must fit in a signed word.
 * @return Key minus the computed number of endpoint spans, or the key for zero spans.
 */
float LibVectorCurveTrackBase::wrap_key(float key) const
{
    s32 last_index = state.key_count - 1;
    LibVectorCurveTrackKey* entries = static_cast<LibVectorCurveTrackKey*>(key_array);
    LibVectorCurveTrackKey* last = entries + last_index;
    float first = entries[0].value.w;
    float span = last->value.w - first;
    float quotient = (key - first) / span;
    s32 periods;

    if (quotient < 0.0f)
    {
        quotient -= 1.0f;
    }

    periods = quotient;

    if (periods != 0)
    {
        return key - (float)periods * span;
    }

    return key;
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
void* LibVectorCurveTrackBase::get_keys()
{
    return static_cast<LibVectorCurveTrackKey*>(key_array);
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibVectorCurveTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] static_cast<LibVectorCurveTrackKey*>(key_array);
    }

    key_array = 0;
}

/** @brief Release the keyframe storage. */
LibVectorTrackBase::~LibVectorTrackBase()
{
    free_keys();
}

/**
 * @brief Bind an external keyframe array and cache its first-to-last key span.
 * @param count Keyframe count.
 * @param keys External keyframe storage.
 */
void LibVectorTrackBase::bind_keys(s32 count, void* keys)
{
    s32 last_index = count - 1;
    LibVectorTrackKey* last;
    state.external_keys = 1;
    key_array = static_cast<LibVectorTrackKey*>(keys);
    state.key_capacity = count;
    state.key_count = count;
    last = key_array + last_index;
    state.span = last->value.w - key_array[0].value.w;
}

/**
 * @brief Set the end mode used before the first key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibVectorTrackBase::set_before_mode(u32 mode)
{
    state.before_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Set the end mode used after the last key, and note whether either end extends its segment.
 * @param mode LIB_TRACK_END_* mode.
 */
void LibVectorTrackBase::set_after_mode(u32 mode)
{
    state.after_mode = mode;
    state.extends_segment = state.before_mode == LIB_TRACK_END_EXTEND_SEGMENT || state.after_mode == LIB_TRACK_END_EXTEND_SEGMENT;
}

/**
 * @brief Return the number of stored keys.
 * @return Key count.
 */
s16 LibVectorTrackBase::get_key_count() const
{
    return state.key_count;
}

/**
 * @brief Return the number of keys the storage can hold.
 * @return Key capacity.
 */
s16 LibVectorTrackBase::get_key_capacity()
{
    return state.key_capacity;
}

/**
 * @brief Test whether a key is stored exactly.
 * @param key Key to find.
 * @return One when a key equals it, otherwise zero.
 */
s32 LibVectorTrackBase::has_key(float key) const
{
    s16 count = state.key_count;
    s32 index;

    for (index = 0; index < count; index++)
    {
        if (key == key_array[index].value.w)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Return the zero vector, the track's value when it has no keys.
 * @return Zero vector.
 */
FieldVec4A LibVectorTrackBase::get_zero_value() const
{
    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Compute the span between the last and first keys.
 * @return Key span, or zero when fewer than two keys are stored.
 */
float LibVectorTrackBase::get_key_span() const
{
    LibVectorTrackKey* last;

    if (state.key_count < 2)
    {
        return 0.0f;
    }

    last = key_array + (state.key_count - 1);
    return last->value.w - key_array[0].value.w;
}

/**
 * @brief Return the value of the first keyframe at exactly a key.
 * @param key Key to find.
 * @return Keyframe value, or a zero vector when no key matches.
 */
FieldVec4A LibVectorTrackBase::find_key_value(float key)
{
    s32 index;

    for (index = 0; index < state.key_count; index++)
    {
        if (key == key_array[index].value.w)
        {
            LibVectorTrackKey* entry = key_array + index;
            return *reinterpret_cast<const FieldVec4A*>(entry);
        }
    }

    return FieldVec4A(0.0f, 0.0f, 0.0f, 0.0f);
}

/**
 * @brief Evaluate the track at a key.
 * @param key Evaluation key.
 * @param output Receives the evaluated value.
 */
void LibVectorTrackBase::evaluate(float key, void* output)
{
    *static_cast<FieldVec4B*>(output) = sample(key);
}

/**
 * @brief Wrap a key by the first-to-last key span.
 * @param key Key to wrap.
 * @return Key with the whole spans it is past the first key removed.
 */
float LibVectorTrackBase::wrap_key(float key) const
{
    LibVectorTrackKey* last = key_array + (state.key_count - 1);
    float first = key_array[0].value.w;
    float span = last->value.w - first;
    float position = (key - first) / span;
    s32 cycles;

    if (position < 0.0f)
    {
        position -= 1.0f;
    }

    cycles = (s32)position;

    if (cycles != 0)
    {
        return key - cycles * span;
    }

    return key;
}

/**
 * @brief Return the key storage.
 * @return Key array, or null.
 */
void* LibVectorTrackBase::get_keys()
{
    return key_array;
}

/** @brief Delete the key storage unless it is external, and clear the key pointer. */
void LibVectorTrackBase::free_keys()
{
    if (!state.external_keys)
    {
        delete[] key_array;
    }

    key_array = 0;
}

/**
 * @brief Mark a track's g_vector_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_track_pool_free(LibTrackPool<LibPooledVectorTrack>* pool, LibPooledVectorTrack* track)
{
    pool->free(track);
}

/**
 * @brief Mark a track's g_vector_curve_track_pool slot as free.
 * @param pool Pool that owns the track.
 * @param track Track to release.
 */
void vector_curve_track_pool_free(LibTrackPool<LibPooledVectorCurveTrack>* pool, LibPooledVectorCurveTrack* track)
{
    pool->free(track);
}

/**
 * @brief Store a single keyframe through on_set_single_key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @param key Sort key.
 */
void LibVectorTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const FieldVec4A*>(value), key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Keyframe value.
 * @param key Sort key.
 */
void LibVectorTrackBase::on_set_single_key(const FieldVec4A* value, float key)
{
}

/**
 * @brief Insert a keyframe through on_insert_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorTrackBase::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, static_cast<const FieldVec4A*>(value));
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Zero.
 */
s32 LibVectorTrackBase::on_insert_key(s32 index, float key, const FieldVec4A* value)
{
    return 0;
}

/**
 * @brief Replace a keyframe through on_replace_key.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, static_cast<const FieldVec4A*>(value));
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @return Zero.
 */
s32 LibVectorTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value)
{
    return 0;
}

/**
 * @brief Append a keyframe through on_append_key.
 * @param value Keyframe value.
 * @param in_tangent Unused.
 * @param out_tangent Unused.
 * @param key Sort key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const FieldVec4A*>(value), key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Keyframe value.
 * @param key Sort key.
 * @return Zero.
 */
s32 LibVectorTrackBase::on_append_key(const FieldVec4A* value, float key)
{
    return 0;
}

/**
 * @brief Allocate storage for a number of keyframes, dropping any keys the track owned.
 * @param count Keyframes to hold.
 */
void LibVectorTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] key_array;
    key_array = new (0) LibVectorTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/**
 * @brief Allocate storage for the requested keyframe count.
 * @param count Requested keyframe count.
 */
void LibVectorCurveTrackBase::allocate_keys(s32 count)
{
    state.external_keys = 0;
    delete[] static_cast<LibVectorCurveTrackKey*>(key_array);
    key_array = new (0) LibVectorCurveTrackKey[count];
    state.key_capacity = count;

    if (!key_array)
    {
        state.key_capacity = 0;
    }
}

/**
 * @brief Store a single keyframe in the cached key, and use it before the first key.
 * @param value Keyframe value.
 * @param key Sort key, stored in the value's w.
 */
void LibVectorKeyTrack::on_set_single_key(const FieldVec4A* value, float key)
{
    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
    single_key.value = *value;
    single_key.value.w = key;
}

/**
 * @brief Insert a keyframe at an index, moving the later keys up.
 * @param index Keyframe index.
 * @param key Sort key, stored in the value's w.
 * @param value Keyframe value.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorKeyTrack::on_insert_key(s32 index, float key, const FieldVec4A* value)
{
    s32 count;
    s32 i;

    if (key_array == 0)
    {
        return 0;
    }

    count = state.key_count;

    if (index >= count)
    {
        return 0;
    }

    if (count >= state.key_capacity)
    {
        return 0;
    }

    for (i = count; i > index; i--)
    {
        static_cast<LibVectorTrackKey*>(key_array)[i] = static_cast<LibVectorTrackKey*>(key_array)[i - 1];
    }

    static_cast<LibVectorTrackKey*>(key_array)[index].value = *value;
    static_cast<LibVectorTrackKey*>(key_array)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<LibVectorTrackKey*>(key_array)[0].value.w;
    }

    state.segment_lower = -1;
    state.segment_upper = -1;
    state.key_count++;
    return 1;
}

/** @brief Reset to a single zero keyframe at key zero, then select the cycle end mode. */
void LibVectorTrack::reset_keys()
{
    FieldVec4A zero(0.0f, 0.0f, 0.0f, 0.0f);
    on_set_single_key(&zero, 0.0f);
    set_before_mode(LIB_TRACK_END_CYCLE);
}

/**
 * @brief Store a single keyframe in the cached vectors.
 * @param value Keyframe value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key, stored in the value's fourth component.
 */
void LibVectorCurveTrack::set_single_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key)
{
    set_before_mode(LIB_TRACK_END_USE_PRE_START_KEY);
    single_key.value = *value;
    single_key.in_tangent = *in_tangent;
    single_key.out_tangent = *out_tangent;
    single_key.value.w = key;
}

/**
 * @brief Insert a keyframe at an index.
 * @param index Keyframe index.
 * @param key Sort key.
 * @param value Keyframe value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorCurveTrack::insert_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent)
{
    s32 count;
    s32 i;

    if (key_array == 0)
    {
        return 0;
    }

    count = state.key_count;

    if (index >= count)
    {
        return 0;
    }

    if (count >= state.key_capacity)
    {
        return 0;
    }

    for (i = count; i > index; i--)
    {
        static_cast<LibVectorCurveTrackKey*>(key_array)[i] = static_cast<LibVectorCurveTrackKey*>(key_array)[i - 1];
    }

    static_cast<LibVectorCurveTrackKey*>(key_array)[index].value = *value;
    static_cast<LibVectorCurveTrackKey*>(key_array)[index].in_tangent = *in_tangent;
    static_cast<LibVectorCurveTrackKey*>(key_array)[index].out_tangent = *out_tangent;
    static_cast<LibVectorCurveTrackKey*>(key_array)[index].value.w = key;

    if (index == state.key_count - 1)
    {
        state.span = key - static_cast<LibVectorCurveTrackKey*>(key_array)[0].value.w;
    }

    state.key_count++;
    return 1;
}

/**
 * @brief Forward to slot 0x68.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorCurveTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

/**
 * @brief Forward to slot 0x6C.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorCurveTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_replace_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Forward to slot 0x70.
 * @param index Key index.
 * @param key Key the keyframe sits at.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @return Nonzero when the keyframe was stored.
 */
s32 LibVectorCurveTrackBase::insert_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
{
    return on_insert_key(index, key, static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent));
}

/**
 * @brief Forward to slot 0x74.
 * @param value Key value.
 * @param in_tangent Tangent arriving at the key.
 * @param out_tangent Tangent leaving the key.
 * @param key Key the keyframe sits at.
 */
void LibVectorCurveTrackBase::set_single_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    on_set_single_key(static_cast<const FieldVec4A*>(value), static_cast<const FieldVec4A*>(in_tangent), static_cast<const FieldVec4A*>(out_tangent), key);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7250);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7770);

s32 func_004E7820(void* object)
{
    return 8;
}

/**
 * @brief Test whether a list walk has come back to the list.
 * @param list List sentinel.
 * @param node Current node.
 * @return Whether node is the sentinel.
 */
static inline bool at_list_end(const LibListSentinel* list, const LibListSentinel* node)
{
    if (list == node)
    {
        return true;
    }

    return false;
}

/**
 * @brief Give each enabled spotlight its own bit (8 up to 31) in its mask, then set that bit on every model in the
 * renderer that shares one of the light's groups and whose bounding sphere reaches into the light's cone.
 * @param renderer Renderer whose models are tested.
 */
void LibLightList::assign_spot_lights(LibRenderer* renderer)
{
    if (unk382 != 0)
    {
        u32 bit = 0x100;
        LibListSentinel* node = &sentinel;

        for (;;)
        {
            node = node->next;

            if (at_list_end(&sentinel, node))
            {
                break;
            }

            LibLight* light = static_cast<LibLight*>(node);

            if (light->enabled && light->kind == LIB_LIGHT_KIND_SPOT)
            {
                u32 groups = light->mask;
                LibVector4 frame[3];
                light->mask = bit | (groups & 0xFF);
                lib_spot_light_get_frame(light, frame);
                vu0_spot_light_load(frame);
                LibListSentinel* other = &renderer->sentinel;

                for (;;)
                {
                    other = other->next;

                    if (at_list_end(&renderer->sentinel, other))
                    {
                        break;
                    }

                    LibColorModel* model = static_cast<LibColorModel*>(other);

                    if (model->draw_flags & 0x59)
                    {
                        continue;
                    }

                    u32 type = model->type_id;

                    if ((type >> 8) != 1 && type != 0x400)
                    {
                        continue;
                    }

                    u32 old_lights = model->light_mask;
                    model->light_mask = ~bit & old_lights;

                    if (!(groups & model->light_mask))
                    {
                        continue;
                    }

                    LibVector4 terms[2];
                    vu0_spot_light_measure(model->get_bounding_sphere());
                    vu0_spot_light_store_distance(terms);

                    if (!(terms[0].x <= terms[0].w))
                    {
                        vu0_spot_light_axis_terms();
                        vu0_spot_light_store_axis_terms(terms);

                        if (terms[0].y < terms[1].x || terms[1].y < 0.0f)
                        {
                            vu0_spot_light_edge_terms();
                            vu0_spot_light_store_edge_terms(terms);

                            if (terms[0].y < 0.0f || terms[1].y < 0.0f)
                            {
                                continue;
                            }
                        }
                    }

                    u32 lights = model->light_mask;
                    model->light_mask = bit | lights;
                }

                bit <<= 1;

                if (!(bit & ~0xFF))
                {
                    break;
                }
            }
        }
    }
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E7AA0);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E8510);

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004E9260);

// LibLightList's per-frame light update; the intensity test's abs.s is still coloured differently.
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
