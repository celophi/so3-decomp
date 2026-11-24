#include "angle.h"
#include "include_asm.h"
#include "overlays/lib/vector_inlines.h"
#include "overlays/lib/transform_owner_inlines.h"
#include "overlays/lib/look_at_transform_inlines.h"
#include "overlays/lib/text_004DD440.h"
#include "overlays/lib/camera_vu0.h"
#include "overlays/lib/light_vu0.h"
#include "overlays/lib/model.h"
#include "overlays/lib/height_grid.h"
#include "overlays/lib/tracks.h"
#include "overlays/lib/tooltip_frame.h"
#include "overlays/lib/item_allocation.h"
#include "overlays/lib/text_004095C0.h"
#include "overlays/lib/text_0044ABE0.h"
#include "overlays/lib/dma_callbacks_inlines.h"
#include "overlays/lib/display_manager_inlines.h"
#include "overlays/lib/text_00419A70.h"
#include "overlays/lib/text_00429B00.h"
#include "overlays/lib/text_0049B820.h"
#include "main/debug.h"
#include "sdk/main/libc_guess_0013A4C0.h"
#include "sdk/main/libgraph_0012EAC8.h"
#include "sdk/main/libkernl_00121940.h"
#include "sdk/main/libm_guess_0013F3E0.h"
#include "vu0.h"
#include "ee.h"
#include "main/resident_data.h"

extern "C" {
extern LibResidentUpdateList* D_001B6660;
extern LibListObject* D_001B665C;
extern LibListObject* g_image_registry;
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
extern LibClass173080 D_507C40;
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

/**
 * @brief Read the matrix translation into a position vector.
 * @param result Destination vector.
 * @param object Transform source.
 */
static inline void lib_get_transform_translation(FieldVec4B& result, const LibTransform& object)
{
    result.x = object.transform.m[0][3];
    result.y = object.transform.m[1][3];
    result.z = object.transform.m[2][3];
    result.w = 1.0f;
}

/**
 * @brief Compute the xyz vector length.
 * @param vector Vector to measure.
 * @return Vector length.
 */
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

    if (display_area.scaled)
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

/**
 * @brief Check whether a screen shows the other field.
 * @param screen Screen.
 * @param field Field being drawn.
 * @return True when the screen's field differs.
 */
static inline bool lib_screen_off_field(const LibDisplayScreen* screen, s32 field)
{
    return !(screen->field == field);
}

/**
 * @brief Finish a render iteration: send its draw packets to the queue and pick the buffers to show.
 * @param frame Render iteration.
 * @param queue Packet queue the frame's packets go to.
 */
void LibCameraContext::flip(s32 frame, LibPacketQueue* queue)
{
    s32 field;

    packet_queue = queue;

    if (display_area.scaled)
    {
        unk3E6A = 0;
        unk3E6B = 0;
        field = resident_input_wait_vblank(resident_system_get_input(&g_system), -1);

        if (resident_get_system()->progressive)
        {
            field = 0;
        }

        if (unk3E67)
        {
            func_004DC4F0(queue, 4, 0, &buffers[1], 0, 0);
            func_004DC4F0(queue, 2, 0, packets[packet_set][field] + 0x40, packet_sizes[packet_set][field], 0);

            if (unk3E78)
            {
                for (s32 i = 0; i < unk3E78; i++)
                {
                    s32 slot = field + i * 2 + 6;

                    func_004DC4F0(queue, 2, 0, packets[unk3E7A][slot] + 0x40, packet_sizes[unk3E7A][slot], 0);
                }
            }

            if (unk3E48)
            {
                func_004DC4F0(queue, 2, 0, unk3E34, unk3E3C, 0);
            }
        }

        if (list_buffers[0] != 0)
        {
            send_list_set = unk3E18;
            send_list_count = unk3E14;
            send_packet_list(field, false);
        }

        sceGsPutDispEnv(&display_environments[0]);

        if (unk3E67)
        {
            for (s32 i = 0; i < LIB_DISPLAY_SCREEN_COUNT; i++)
            {
                if (screens[i].enabled && screens[i].circuit2 && lib_screen_off_field(&screens[i], field))
                {
                    func_004DC4F0(queue, 4, 0, &screens[i].buffers[0], 0, 0);
                    func_004DC4F0(queue, 2, 0, packets[packet_set][i + 2] + 0x40, packet_sizes[packet_set][i + 2], 0);

                    if (unk3E78)
                    {
                        for (s32 j = 0; j < unk3E78; j++)
                        {
                            s32 slot = (field ^ 1) + j * 2 + 6;

                            func_004DC4F0(queue, 2, 0, packets[unk3E7A][slot] + 0x40, packet_sizes[unk3E7A][slot], 0);
                        }
                    }

                    if (unk3E48)
                    {
                        func_004DC4F0(queue, 2, 0, unk3E34, unk3E3C, 0);
                    }

                    screens[i].unkA57 = 1;
                }
                else
                {
                    screens[i].unkA57 = 0;
                }
            }
        }
        else
        {
            for (s32 i = 0; i < LIB_DISPLAY_SCREEN_COUNT; i++)
            {
                if (screens[i].enabled && screens[i].circuit2 && lib_screen_off_field(&screens[i], field))
                {
                    screens[i].unkA57 = 1;
                }
                else
                {
                    screens[i].unkA57 = 0;
                }
            }
        }

        if (list_buffers[0] != 0)
        {
            if (unk3E30 == 1)
            {
                send_packet_list(field ^ 1, true);
            }

            unk3E18 ^= 1;
            unk3E14 = 0;
            unk3E20 = list_buffers[unk3E18 * 2] + 0x40;
            unk3E24 = list_buffers[unk3E18 * 2 + 1] + 0x40;

            for (s32 i = 0; i < unk3E10; i++)
            {
                list_sizes[unk3E18 * 2][i] = 0;
                list_sizes[unk3E18 * 2 + 1][i] = 0;
            }
        }

        func_004DC4F0(queue, 4, 0, &buffers[0], 0, 0);
        current_buffer = 0;

        for (s32 i = 0; i < LIB_DISPLAY_SCREEN_COUNT; i++)
        {
            if (screens[i].enabled && screens[i].field == field && screens[i].unkA51)
            {
                GS_DISPFB1 = *(u64*)&screens[i].display_environment.framebuffer;
                GS_DISPLAY1 = *(u64*)&screens[i].display_environment.display;
            }
        }

        return;
    }

    FlushCache(0);

    if (frame_buffer_count == 2)
    {
        if (frame & 1)
        {
            current_buffer = 1;
            sceGsPutDrawEnv(&buffers[1].environment.gif_tag);

            if (!unk3E65)
            {
                sceGsPutDispEnv(&display_environments[1]);
            }
        }
        else
        {
            current_buffer = 0;
            sceGsPutDrawEnv(&buffers[0].environment.gif_tag);

            if (!unk3E65)
            {
                sceGsPutDispEnv(&display_environments[0]);
            }
        }
    }
    else
    {
        s32 index = frame % 3;

        if (unk3E65)
        {
            switch (index)
            {
                case 0:
                    sceGsPutDrawEnv(&buffers[0].environment.gif_tag);
                    break;
                case 1:
                    sceGsPutDrawEnv(&buffers[1].environment.gif_tag);
                    break;
                case 2:
                    sceGsPutDrawEnv(&buffers[2].environment.gif_tag);
                    break;
            }
        }
        else if (unk3E66 && !unk3E68)
        {
            switch (index)
            {
                case 0:
                    if (unk3E64)
                    {
                        GS_DISPFB1 = blend_registers[0].framebuffer;
                        GS_DISPLAY1 = blend_registers[0].display;
                    }

                    sceGsPutDispEnv(&blend_environments[0]);
                    sceGsPutDrawEnv(&buffers[1].environment.gif_tag);
                    break;
                case 1:
                    if (unk3E64)
                    {
                        GS_DISPFB1 = blend_registers[1].framebuffer;
                        GS_DISPLAY1 = blend_registers[1].display;
                    }

                    sceGsPutDispEnv(&blend_environments[1]);
                    sceGsPutDrawEnv(&buffers[2].environment.gif_tag);
                    break;
                case 2:
                    if (unk3E64)
                    {
                        GS_DISPFB1 = blend_registers[2].framebuffer;
                        GS_DISPLAY1 = blend_registers[2].display;
                    }

                    sceGsPutDispEnv(&blend_environments[2]);
                    sceGsPutDrawEnv(&buffers[0].environment.gif_tag);
                    break;
            }
        }
        else
        {
            switch (index)
            {
                case 0:
                    if (unk3E64)
                    {
                        GS_DISPFB1 = circuit1_registers[2].framebuffer;
                        GS_DISPLAY1 = circuit1_registers[2].display;
                    }

                    sceGsPutDispEnv(&display_environments[0]);
                    sceGsPutDrawEnv(&buffers[1].environment.gif_tag);
                    break;
                case 1:
                    if (unk3E64)
                    {
                        GS_DISPFB1 = circuit1_registers[0].framebuffer;
                        GS_DISPLAY1 = circuit1_registers[0].display;
                    }

                    sceGsPutDispEnv(&display_environments[1]);
                    sceGsPutDrawEnv(&buffers[2].environment.gif_tag);
                    break;
                case 2:
                    if (unk3E64)
                    {
                        GS_DISPFB1 = circuit1_registers[1].framebuffer;
                        GS_DISPLAY1 = circuit1_registers[1].display;
                    }

                    sceGsPutDispEnv(&display_environments[2]);
                    sceGsPutDrawEnv(&buffers[0].environment.gif_tag);
                    break;
            }
        }
    }
}

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

/** @brief Build the packets that draw the scaled draw area onto each screen. */
void LibCameraContext::build_scaled_packets()
{
    s32 set = packet_set ^ 1;
    u32 depth_mask = 0xFFFF;

    if (display_area.depth_format == 0x30)
    {
        depth_mask = 0xFFFFFFFF;
    }
    else if (display_area.depth_format == 0x31)
    {
        depth_mask = 0xFFFFFF;
    }

    for (s32 i = 0; i < 2; i++)
    {
        packet_sizes[set][i] = func_004DEA70(
            this, packets[set][i] + 0x40, i != 0, buffers[0].environment.context2.frame.base_pointer,
            display_area.unk10, display_area.width, display_area.height, display_area.base_width,
            display_area.base_height, depth_mask, blend_enabled, (s32)(128.0f * blend_alpha), 0, 0, 0, 1, 0, 0, -1, -1);
    }

    for (s32 i = 0; i < LIB_DISPLAY_SCREEN_COUNT; i++)
    {
        LibDisplayScreen* screen = &screens[i];

        if (!screen->enabled)
        {
            continue;
        }

        u8* packet = packets[set][i + 2] + 0x40;

        if (screen->unkA53)
        {
            packet_sizes[set][i + 2] = func_004DEA70(
                this, packet, screen->field,
                screen->buffers[1].environment.context2.frame.base_pointer, screen->pixel_format, screen->view_width,
                screen->view_height, screen->width, screen->height, depth_mask, blend_enabled,
                (s32)(128.0f * blend_alpha), 0, 0, 0, 1, 0, 0, -1, -1);
        }
        else
        {
            packet_sizes[set][i + 2] = func_004DEA70(
                this, packet, screen->field, buffers[0].environment.context2.frame.base_pointer,
                display_area.unk10, screen->view_width, screen->view_height, screen->width, screen->height,
                depth_mask, blend_enabled, (s32)(128.0f * blend_alpha), 0, 0, 0, 1, 0, 0, -1, -1);
        }
    }

    FlushCache(0);
    packet_set ^= 1;
}

/** Packet head of func_004DF270: the context-2 setup and the sprite strips' GIF tag. */
struct LibAlphaFillHead
{
    GsGifTag setup_tag;
    GsRegisterValue frame;
    GsRegisterValue frame_alpha;
    GsRegisterValue test;
    GsRegisterValue depth_buffer;
    GsRegisterValue primitive;
    GsRegisterValue color;
    GsGifTag strip_tag;
};

/** Packet tail of func_004DF270: restores context 2's frame and depth buffers. */
struct LibAlphaFillTail
{
    GsGifTag tag;
    GsRegisterValue frame;
    GsRegisterValue depth_buffer;
};

extern "C" u32 func_004DF270(LibCameraContext* display, LibAlphaFillHead* head, s32 width, s32 height, s32 alpha,
                             u32 depth);

/**
 * @brief Build the display effect's packet in the next effect buffer: for each level, an alpha fill and a copy of the
 * frame offset around a circle, a first pass and an optional second pass with its own depths.
 * @param display Display.
 */
extern "C" void func_004DE500(LibCameraContext* display)
{
    if (!display->effect_enabled && display->effect_level != 0)
    {
        return;
    }

    display->unk3CB0 ^= 1;
    display->unk3C90[display->unk3CB0] = 0;
    u8* packet = display->effect_buffers[display->unk3CB0];

    if (packet == 0)
    {
        return;
    }

    u32 size = 0;
    u32 depth_mask = 0xFFFF;

    if (display->display_area.depth_format == GS_PSMZ32)
    {
        depth_mask = 0xFFFFFFFF;
    }
    else if (display->display_area.depth_format == GS_PSMZ24)
    {
        depth_mask = 0xFFFFFF;
    }

    if (display->effect_first_flag)
    {
        u32 count = func_004DF270(display, reinterpret_cast<LibAlphaFillHead*>(packet), display->display_area.width,
                                  display->display_area.height, 0, depth_mask);
        packet += count * 16;
        size += count;
    }

    for (s32 i = 0; i < display->effect_level; i++)
    {
        float radius = display->effect_first_scale +
            i * (display->effect_second_scale - display->effect_first_scale) / (display->effect_level - 1);
        float angle = TWO_PI * i;
        s32 x = radius * (16.0f * cosf_guess(angle / display->effect_level));
        s32 y = radius * (16.0f * sinf_guess(angle / display->effect_level));
        u32 count;

        if (display->effect_first_flag)
        {
            count = func_004DF270(display, reinterpret_cast<LibAlphaFillHead*>(packet), display->display_area.width,
                                  display->display_area.height, i + 0x40, display->effect_first_depths[i]);
            packet += count * 16;
            size += count;
            count = func_004DEA70(display, packet, 0, display->buffers[0].environment.context2.frame.base_pointer,
                                  display->display_area.unk10, display->display_area.width, display->display_area.height,
                                  display->display_area.width, display->display_area.height,
                                  display->effect_first_depths[i], 1, 0x80, x, y, i + 0x40,
                                  i == display->effect_level - 1 && !display->effect_second_flag, 0, 0, -1, -1);
        }
        else
        {
            count = func_004DEA70(display, packet, 0, display->buffers[0].environment.context2.frame.base_pointer,
                                  display->display_area.unk10, display->display_area.width, display->display_area.height,
                                  display->display_area.width, display->display_area.height,
                                  display->effect_first_depths[i], 1, 0x40, x, y, 0,
                                  i == display->effect_level - 1 && !display->effect_second_flag, 0, 0, -1, -1);
        }

        packet += count * 16;
        size += count;
    }

    if (display->effect_second_flag)
    {
        u32 count = func_004DF270(display, reinterpret_cast<LibAlphaFillHead*>(packet), display->display_area.width,
                                  display->display_area.height, 0x80, display->effect_mask);
        packet += count * 16;
        size += count;
        float alpha = 0.75f;

        for (s32 i = 0; i < display->effect_level; i++)
        {
            float radius = display->effect_first_scale +
                i * (display->effect_second_scale - display->effect_first_scale) / (display->effect_level - 1);
            float angle = TWO_PI * i;
            s32 x = radius * (24.0f * lib_cosine_degree9(angle / display->effect_level));
            s32 y = radius * (24.0f * lib_sine_degree9(angle / display->effect_level));
            count = func_004DF270(display, reinterpret_cast<LibAlphaFillHead*>(packet), display->display_area.width,
                                  display->display_area.height, 0, display->effect_second_depths[i]);
            packet += count * 16;
            size += count;
            count = func_004DEA70(display, packet, 0, display->buffers[0].environment.context2.frame.base_pointer,
                                  display->display_area.unk10, display->display_area.width, display->display_area.height,
                                  display->display_area.width, display->display_area.height, depth_mask, 1,
                                  (s32)(128.0f * alpha), x, y, 1, i == display->effect_level - 1 ? 1 : 0, 0, 0, -1, -1);
            packet += count * 16;
            size += count;
        }
    }

    display->unk3CA8[display->unk3CB0] = display->effect_buffers[display->unk3CB0];
    display->unk3C90[display->unk3CB0] = size;
    FlushCache(0);
}

INCLUDE_ASM("build/overlays/lib/asm/nonmatchings/text_004DD440", func_004DEA70);

/**
 * @brief Build a packet that writes an alpha value into the frame buffer wherever the depth test against a depth
 * passes, with sprites 64 pixels wide over a centred area. Only the alpha channel and no depth are written.
 * @param display Display whose first buffer's frame and depth buffer context 2 uses.
 * @param head Packet to build.
 * @param width Area width in pixels.
 * @param height Area height in pixels.
 * @param alpha Alpha value to write.
 * @param depth Depth the sprites are drawn at.
 * @return Packet size in quadwords.
 */
extern "C" u32 func_004DF270(LibCameraContext* display, LibAlphaFillHead* head, s32 width, s32 height, s32 alpha,
                             u32 depth)
{
    u64* vertex = reinterpret_cast<u64*>(head);
    head->setup_tag.tag = GIF_TAG_NREG(1) | 6;
    head->setup_tag.registers = 0;
    head->setup_tag.fields.register0 = GIF_REGISTER_AD;
    head->frame.data =
        *reinterpret_cast<const u64*>(&display->buffers[0].environment.context1.frame) | ((u64)0xFFFFFF << 32);
    head->frame.address = GS_REGISTER_FRAME_2;
    head->frame_alpha.data = 0;
    head->frame_alpha.address = GS_REGISTER_FBA_2;
    head->test.data = 0x50000;
    head->test.address = GS_REGISTER_TEST_2;
    head->depth_buffer.data =
        *reinterpret_cast<const u32*>(&display->buffers[0].environment.context1.depth_buffer) | ((u64)1 << 32);
    head->depth_buffer.address = GS_REGISTER_ZBUF_2;
    head->primitive.data = 0x206;
    head->primitive.address = GS_REGISTER_PRIM;
    head->color.data = (u32)((alpha << 24) | 0x10101);
    head->color.address = GS_REGISTER_RGBAQ;
    s32 left = (GS_COORDINATE_CENTRE - (width >> 1)) * 16;
    s32 top = (GS_COORDINATE_CENTRE - (height >> 1)) * 16;
    head->strip_tag.tag = (width + 63) / 64 | GIF_TAG_NREG(2) | GIF_TAG_FLG_REGLIST;
    head->strip_tag.registers = 0;
    head->strip_tag.fields.register0 = GIF_REGISTER_XYZ2;
    head->strip_tag.fields.register1 = GIF_REGISTER_XYZ2;
    vertex += sizeof(LibAlphaFillHead) / sizeof(u64);

    for (s32 x = 0; x < width; x += 64)
    {
        vertex[0] = (s64)(left + x * 16) | (s64)top << 16 | (u64)depth << 32;
        vertex[1] = (s64)(left + (x + 64) * 16) | (s64)(top + height * 16) << 16 | (u64)depth << 32;
        vertex += 2;
    }

    LibAlphaFillTail* tail = reinterpret_cast<LibAlphaFillTail*>(vertex);
    tail->tag.tag = GIF_TAG_NREG(1) | 2;
    tail->tag.registers = 0;
    tail->tag.fields.register0 = GIF_REGISTER_AD;
    tail->frame.data = *reinterpret_cast<const u64*>(&display->buffers[0].environment.context1.frame);
    tail->frame.address = GS_REGISTER_FRAME_2;
    tail->depth_buffer.data = *reinterpret_cast<const u32*>(&display->buffers[0].environment.context1.depth_buffer);
    tail->depth_buffer.address = GS_REGISTER_ZBUF_2;
    return (u32)((u8*)(tail + 1) - (u8*)head) >> 4;
}

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
    display_area.depth_test = depth_test;
    display_area.depth_format = depth_format;

    if (display_area.unk10 == -1)
    {
        display_area.unk10 = pixel_format;
    }

    resize_display_area();

    if (display_area.scaled)
    {
        sceGsSetDefDrawEnv(&buffers[0].environment.context1, display_area.unk10, display_area.width, display_area.height, depth_test, depth_format);
        sceGsSetDefDrawEnv2(&buffers[0].environment.context2, display_area.unk10, display_area.width, display_area.height, depth_test, depth_format);
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

    if (display_area.scaled)
    {
        buffers[1].environment.context1.depth_buffer.base_pointer = buffers[1].environment.context2.depth_buffer.base_pointer =
            buffers[0].environment.context1.depth_buffer.base_pointer = buffers[0].environment.context2.depth_buffer.base_pointer = vram_base_page;
        // TODO: This is overwritten before anything reads it, but the target still tests the area's format here.
        depth_bytes = display_area.unk10 == GS_PSMCT16 || display_area.unk10 == GS_PSMCT16S ? 2 : 4;
    }
    else
    {
        buffers[2].environment.context1.depth_buffer.base_pointer = buffers[2].environment.context2.depth_buffer.base_pointer =
            buffers[1].environment.context1.depth_buffer.base_pointer = buffers[1].environment.context2.depth_buffer.base_pointer =
                buffers[0].environment.context1.depth_buffer.base_pointer = buffers[0].environment.context2.depth_buffer.base_pointer = vram_base_page;
    }

    depth_bytes = depth_format == GS_PSMZ16 || depth_format == GS_PSMZ16S ? 2 : 4;

    if (display_area.scaled)
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
                         lib_buffer_pages(display_area.unk10, display_area.width, display_area.height);

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

/**
 * @brief Show only read circuit 1 with a fixed output alpha in every display environment, and keep the alpha.
 * @param display Camera context.
 * @param alpha Alpha from zero to one.
 */
extern "C" void func_004E02C0(LibCameraContext* display, float alpha)
{
    s32 value = (s32)(255.0f * alpha);

    if (value < 0)
    {
        value = 0;
    }

    if (value > 255)
    {
        value = 255;
    }

    for (s32 i = 0; i < LIB_DISPLAY_BUFFER_COUNT; i++)
    {
        display->display_environments[i].pmode.circuit1 = 1;
        display->display_environments[i].pmode.fixed_alpha = 1;
        display->display_environments[i].pmode.blend_background = 0;
        display->display_environments[i].pmode.alpha = value;
    }

    display->blend_field_alpha = value;
    display->unk3E64 = 1;
}

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

    if (display_area.scaled)
    {
        sceGsSetDefDrawEnv(&buffers[1].environment.context1, pixel_format, display_area.base_width, display_area.base_height, display_area.depth_test, display_area.depth_format);
        sceGsSetDefDrawEnv2(&buffers[1].environment.context2, pixel_format, display_area.base_width, display_area.base_height, display_area.depth_test, display_area.depth_format);
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
    display_area.scaled = !(scale_x == 1.0f && scale_y == 1.0f);
    display_area.unk17 = unk3C77;
    unk3E65 = 0;
    unk3E66 = 0;
    unk3E68 = 0;
    display_area.unk10 = unk3C70;

    if (display_area.scaled)
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

/**
 * @brief Give an allocation back through the system's release queues, when there is one.
 * @param allocation Allocation, or null.
 */
static inline void lib_release_allocation(void* allocation)
{
    if (allocation != 0)
    {
        resident_queue_allocation_release(resident_system_get_release_queues(resident_get_system()), allocation);
    }
}

/** @brief Destroy the display. */
LibCameraContext::~LibCameraContext()
{
    for (s32 i = 0; i < LIB_DISPLAY_PACKET_COUNT; i++)
    {
        delete packets[0][i];
        delete packets[1][i];
    }

    for (s32 i = 0; i < LIB_DISPLAY_PACKET_LIST_COUNT; i++)
    {
        delete list_buffers[i];
        delete list_packets[i];
        delete list_sizes[i];
    }

    for (s32 i = 0; i < LIB_DISPLAY_PACKET_SET_COUNT; i++)
    {
        delete unk3E08[i];
    }

    lib_release_allocation(effect_buffers[0]);
    lib_release_allocation(effect_buffers[1]);
    delete unk3E34;
}

/** @brief Initialize the display. */
LibCameraContext::LibCameraContext()
{
    display_area.unk10 = -1;
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
    effect_enabled = 0;
    effect_buffers[0] = 0;
    effect_buffers[1] = 0;
    ready_packets[0] = 0;
    ready_packets[1] = 0;
    unk3CA8[0] = 0;
    unk3CA8[1] = 0;
    unk3E67 = 1;
}

/**
 * @brief Return the shared bounding sphere every object of this class uses.
 * @return Bounding sphere.
 */
const LibVector4* LibClass178FC0::get_bounding_sphere()
{
    return reinterpret_cast<const LibVector4*>(D_0050CD80);
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

/**
 * @brief Clear the packet-in-flight flag and finish the packet.
 * @param value Notification value.
 */
void LibClass178FC0::on_packet_complete(u32 value)
{
    dma_pending = 0;
    lib_finish_packet(this);
}

/** @brief Mark the packet in flight and submit the packet buffer, notifying this object when it's sent. */
void LibClass178FC0::render()
{
    dma_pending = 1;
    resident_packet_submit(unk114, static_cast<LibDmaCallbacks*>(this));
}

/** @brief Update the listed nodes. */
void LibClass178FC0::update()
{
    update_nodes();
}

/**
 * @brief Allocate the packet buffer.
 * @param size Size in quadwords.
 * @return One on success, zero when the allocation failed.
 */
s32 LibClass178FC0::func_004E10B0(s32 size)
{
    unk114 = new (0) LibPacketBuffer(size);

    if (unk114 == 0)
    {
        return 0;
    }

    return 1;
}

/** Node of LibClass178FC0's list; slot 0x28 writes into the owner's packet. */
class LibPacketListNode : public LibListObject
{
public:
    virtual void func_slot1C();

    virtual void func_slot20();

    virtual void func_slot24();

    /**
     * @brief Add the node's data to a packet.
     * @param packet Packet being built.
     */
    virtual void write_packet(LibPacketBuffer* packet);
};

/**
 * @brief Build the packet for a camera: load its screen matrix, reset the packet, set register 0x4F and let every
 *        listed node add its data.
 * @param matrix Camera.
 * @param context Context kept for the nodes.
 */
void LibClass178FC0::build_packet(const void* matrix, void* context)
{
    camera = static_cast<const LibCamera*>(matrix);
    this->context = context;
    func_004D9AB0(D_001B65FC, 0);
    func_004D99B0(D_001B65FC);
    const LibMatrix44Value& view = camera->view_matrix;
    LibMatrix44Value screen;
    screen = func_004CF7C0(camera->projection_matrix, view);
    vu0_start_microprogram_1f0_vf5_vf8(&screen);
    LibListSentinel* node = &sentinel;
    const LibCameraPacket5C0* packet = &camera->unk5c0;
    resident_packet_rewind(unk114);
    resident_packet_add_register(unk114, 0x4F, packet->unk120);

    for (;;)
    {
        node = node->next;

        if (at_list_end(&sentinel, node))
        {
            break;
        }

        static_cast<LibPacketListNode*>(node)->write_packet(unk114);
    }

    unk63 = 1;
}

/** @brief Delete the packet buffer. */
LibClass178FC0::~LibClass178FC0()
{
    delete unk114;
}

/** @brief Forget the packet buffer without deleting it. */
void LibClass178FC0::func_004E13D0()
{
    unk114 = 0;
}

/** @brief Start with type ID 0x200 and no packet buffer. */
LibClass178FC0::LibClass178FC0()
{
    type_id = 0x200;
    unk114 = 0;
}



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

/**
 * @brief Initialize viewport bounds and default projection settings.
 * @param context Resident viewport context.
 */
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
    centre_x = 2048.0f;
    centre_y = 2048.0f;
    pixel_aspect = (1.3333334f * (1.0714285f * context->display_area.height)) / context->display_area.width;
    width_scale = 1.0f;
    unk270 = 1.0f;
}

/** @brief Upload the camera's clip geometry into VU0 data memory. */
void LibCamera::upload_clip_geometry() const
{
    vu0_upload_clip_geometry(clip_points, clip_normals);
}

/**
 * @brief Load the camera's transform into VU0 (microprogram 0x1F0) and build its screen clip data.
 * @param camera Camera to upload.
 */
extern "C" void func_004E1670(LibCamera* camera)
{
    vu0_start_microprogram_1f0_vf5_vf8(&camera->transform);
    FieldVec4B points[10];
    float inverse_aspect = 1.0f / camera->pixel_aspect;
    float half_width = 0.5f * (camera->screen_max.x - camera->screen_min.x);
    float half_height = inverse_aspect * (0.5f * (camera->screen_max.y - camera->screen_min.y));
    float edge = 2040.0f * inverse_aspect;

    points[0].x = -half_width;
    points[0].y = -half_height;
    points[0].z = camera->projection_distance;
    points[1].x = half_width;
    points[1].y = -half_height;
    points[1].z = camera->projection_distance;
    points[2].x = half_width;
    points[2].y = half_height;
    points[2].z = camera->projection_distance;
    points[3].x = -half_width;
    points[3].y = half_height;
    points[3].z = camera->projection_distance;
    points[4].set(points[0]);
    points[4].z = camera->screen_min.z;
    points[5].x = 0.0f;
    points[5].y = 0.0f;
    points[5].z = camera->screen_max.z;
    points[6].x = -2040.0f;
    points[6].y = -edge;
    points[6].z = camera->projection_distance;
    points[7].x = 2040.0f;
    points[7].y = -edge;
    points[7].z = camera->projection_distance;
    points[8].x = 2040.0f;
    points[8].y = edge;
    points[8].z = camera->projection_distance;
    points[9].x = -2040.0f;
    points[9].y = edge;
    points[9].z = camera->projection_distance;
    vu0_transform_clip_points(points);
    vu0_store_clip_points(camera->clip_points);
    vu0_build_side_clip_normals(camera->clip_normals);
    vu0_build_end_clip_normals(camera->clip_normals);
}

/**
 * @brief Build the local perspective volume for visibility tests.
 * @param volume Destination volume.
 */
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

/**
 * @brief Set the near fog-distance fraction and recompute fog coefficients.
 * @param fraction Fraction of the configured distance range.
 */
void LibCamera::set_near_fog_fraction(float fraction)
{
    near_fog_fraction = fraction;
    update_fog_coefficients(far_fog_factor, near_fog_factor);
}

/**
 * @brief Set the far fog-distance fraction and recompute fog coefficients.
 * @param fraction Fraction of the configured distance range.
 */
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

/** @brief Store unk530 in the packet at unk558 and queue the packet at unk860 for VIF1 DMA. */
void LibCamera::func_004E1E70()
{
    *reinterpret_cast<u64*>(unk558 + 0x90) = fog_color;
    ee_sync();
    resident_dma_queue_push(g_vif1_dma_queue, unk860);
}

/**
 * @brief Copy camera settings, the attached transform and inherited transform state.
 * @param source Camera to copy.
 */
void LibCamera::copy_camera(const LibCamera* source)
{
    copy_view_and_fog(source);
    look_at_target = source->look_at_target;
    LibTransform::copy_offset_transform_state(source);
}

/**
 * @brief Copy the camera's view and fog settings.
 * @param source Camera to copy.
 */
void LibCamera::copy_view_and_fog(const LibCamera* source)
{
    unk3c8 = source->unk3c8;
    unk3cc = source->unk3cc;
    pixel_aspect = source->pixel_aspect;
    screen_min = source->screen_min;
    screen_max = source->screen_max;
    centre_x = source->centre_x;
    centre_y = source->centre_y;
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

/**
 * @brief Submit the camera's DMA chain.
 * @param channel DMA channel number.
 */
void LibCamera::submit_dma(u32 channel)
{
    DmaChannel* dma = sceDmaGetChan(channel);
    dma->chcr.tag_transfer_enable = 0;
    sceDmaSend(dma, &dma_chain);
}

/**
 * @brief Complete the camera transfer.
 * @param channel DMA channel number; unused.
 */
void LibCamera::complete_dma(u32 channel)
{
}

/**
 * @brief Queue the camera for VIF1 DMA.
 * @return 1 on success, 0 when the queue is full.
 */
s32 LibCamera::enqueue_submission()
{
    return resident_dma_queue_push(g_vif1_dma_queue, this);
}

/** @brief Write the camera's matrices into its uncached packet. */
void LibCamera::func_004E2120()
{
    LibVector4 angles;
    LibCameraPacket5C0* packet = (LibCameraPacket5C0*)((u32)&unk5c0 | UNCACHED_SEGMENT);

    ((unsigned __int128*)&packet->view)[0] = ((const unsigned __int128*)&view_matrix)[0];
    ((unsigned __int128*)&packet->view)[1] = ((const unsigned __int128*)&view_matrix)[1];
    ((unsigned __int128*)&packet->view)[2] = ((const unsigned __int128*)&view_matrix)[2];
    ((unsigned __int128*)&packet->view)[3] = ((const unsigned __int128*)&view_matrix)[3];
    ee_transpose_matrix(&packet->unk090, &unk340);
    ee_transpose_matrix(&packet->projection, &projection_matrix);
    packet->distance = projection_distance;
    packet->scaled_distance = 1.4142135f * projection_distance;
    packet->centre_depth = centre_depth;
    ((unsigned __int128*)&packet->unk0e0)[0] = ((const unsigned __int128*)&unk380)[0];
    ((unsigned __int128*)&packet->unk0e0)[1] = ((const unsigned __int128*)&unk380)[1];
    ((unsigned __int128*)&packet->unk0e0)[2] = ((const unsigned __int128*)&unk380)[2];
    ((unsigned __int128*)&packet->unk0e0)[3] = ((const unsigned __int128*)&unk380)[3];
    const LibVector4* rotation = &orientation;
    func_004CDA40(&angles, rotation);
    float z = -angles.z;
    packet->roll = z;
    roll = z;
    packet->fog_offset = fog_offset;
    packet->fog_scale = fog_reciprocal_scale;

    if (!unk3d1)
    {
        *reinterpret_cast<u64*>(unk558 + 0x90) = fog_color;
        ee_sync();
        resident_dma_queue_push(g_vif1_dma_queue, unk860);
    }
}

/**
 * @brief Build the projection and clip matrices for a screen grown by a step, keeping its aspect, and write the
 * camera's projection and clip matrices into its uncached step packet.
 * @param camera Camera.
 * @param step Pixels added to the screen width.
 * @param projection Receives the stepped projection matrix, converted by func_004CECD0.
 * @param clip Receives the stepped clip matrix, converted by func_004CECD0.
 */
extern "C" void func_004E22B0(LibCamera* camera, s32 step, LibMatrix44Value* projection, LibMatrix44Value* clip)
{
    s32 width = camera->unk3c8 + step;
    s32 height = (s64)camera->unk3cc * width / camera->unk3c8;
    LibMatrix44Value matrix;
    func_004CFD80(&matrix, camera->projection_distance, camera->pixel_aspect, camera->centre_x - camera->unk3e0,
                  camera->centre_y - camera->unk3e4, width, height, camera->screen_min.z, camera->screen_max.z);
    *projection = func_004CECD0(matrix);
    func_004CFA30(&matrix, reinterpret_cast<const FieldVec4A*>(&camera->screen_min),
                  reinterpret_cast<const FieldVec4A*>(&camera->screen_max), camera->projection_distance,
                  camera->pixel_aspect, camera->centre_x - camera->unk3e0, camera->centre_y - camera->unk3e4, width, height);
    *clip = func_004CECD0(matrix);
    LibCameraStepPacket* packet = (LibCameraStepPacket*)((u32)&camera->unk5c0.step | EE_UNCACHED_ACCELERATED);
    ee_transpose_matrix(&packet->projection, &camera->projection_matrix);
    ((unsigned __int128*)&packet->clip)[0] = ((const unsigned __int128*)&camera->unk380)[0];
    ((unsigned __int128*)&packet->clip)[1] = ((const unsigned __int128*)&camera->unk380)[1];
    ((unsigned __int128*)&packet->clip)[2] = ((const unsigned __int128*)&camera->unk380)[2];
    ((unsigned __int128*)&packet->clip)[3] = ((const unsigned __int128*)&camera->unk380)[3];
}

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

    func_004CFD80(&projection_matrix, projection_distance, pixel_aspect, centre_x - unk3e0, centre_y - unk3e4, unk3c8, unk3cc, screen_min.z,
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
    func_004CFA30(&clip, &low, &high, projection_distance, pixel_aspect, centre_x - unk3e0, centre_y - unk3e4, unk3c8, unk3cc);
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

// TODO: The camera's destructor inlines its base's, which text_0046AE20 and other modules keep out of line, so the
// base destructor is only inline in this unit.
inline LibLookAtTransform::~LibLookAtTransform()
{
}

/** @brief Delete the camera's VIF1 packet, then destroy the transform base. */
LibCamera::~LibCamera()
{
    delete unk860;
}

/** Camera packet that resets the context-1 drawing state, sent on VIF1. */
struct LibCameraSetupPacket
{
    u64 dma_tag;
    union
    {
        u64 vif;
        u32 vif_codes[2];
    };
    GsGifTag tag;
    GsRegisterValue registers[9];
};

/**
 * @brief Initialize the camera from the resident context.
 * @param context Resident context.
 */
LibCamera::LibCamera(void* context)
{
    const LibCameraContext* display = static_cast<const LibCameraContext*>(context);
    LibCameraSetupPacket* packet;

    centre_y = 0.0f;
    centre_x = 0.0f;
    set_type_id(4);
    unk248 = 1.0f;
    unk24c = 11.0f;
    unk240 = 64.0f;
    unk244 = 1000.0f;
    unk270 = 1.0f;
    unk3d3 = 1;
    unk3d2 = 0;
    unk260 = 1.0f;
    unk264 = 1.0f;
    unk268 = 1.0f;
    unk26c = 1.0f;
    far_fog_fraction = 1.0f;
    near_fog_fraction = 0.0f;
    far_fog_distance = 10000.0f;
    near_fog_distance = 1000.0f;
    near_fog_factor = 255.0f;
    near_fog_distance = 255.0f;
    roll = 0.0f;
    unk3d1 = 0;
    width_scale = 1.0f;
    unk254 = 1.0f;
    unk270 = 1.0f;
    set_centre(2048.0f, 2048.0f);
    unk5c0.unk090.set_identity();
    unk5c0.unk120 = *reinterpret_cast<const u32*>(&display->buffers[0].environment.context1.depth_buffer);
    unk5c0.unk124 = 0;
    unk5c0.unk128 = GS_REGISTER_ZBUF_1;
    unk5c0.unk12c = 0;
    unk5c0.unk130 = *reinterpret_cast<const u32*>(&display->buffers[0].environment.context1.depth_buffer);
    unk5c0.unk134 = 1;
    unk5c0.unk138 = GS_REGISTER_ZBUF_1;
    unk5c0.unk13c = 0;
    unk5c0.vif[0] = VIF_FLUSH;
    unk5c0.vif[1] = 0;
    unk5c0.vif[2] = 0;
    unk5c0.vif[3] = VIF_UNPACK(VIF_UNPACK_V4_32, 0x1B, 0x30);
    unk5c0.unk140.tag = GIF_TAG_NREG(1) | GIF_TAG_EOP | 1;
    unk5c0.unk140.registers = GIF_REGISTER_AD;
    unk5c0.unk160.tag = GIF_TAG_NREG(1) | GIF_TAG_EOP | 2;
    unk5c0.unk160.registers = GIF_REGISTER_AD;
    unk5c0.unk170.data = 0xFFFFFFF0ULL;
    unk5c0.unk170.address = GS_REGISTER_CLAMP_1;
    unk5c0.unk180.data = 0xFFFFFFFF5ULL;
    unk5c0.unk180.address = GS_REGISTER_CLAMP_1;
    dma_chain.control = (u64)(u32)&unk5c0 << 32 | 0x1C;
    unk5c0.step.projection_vif[0] = VIF_FLUSH;
    unk5c0.step.projection_vif[1] = 0;
    unk5c0.step.projection_vif[2] = 0;
    unk5c0.step.projection_vif[3] = VIF_UNPACK(VIF_UNPACK_V4_32, 4, 0x34);
    unk5c0.step.clip_vif[0] = VIF_FLUSH;
    unk5c0.step.clip_vif[1] = 0;
    unk5c0.step.clip_vif[2] = 0;
    unk5c0.step.clip_vif[3] = VIF_UNPACK(VIF_UNPACK_V4_32, 4, 0x3D);
    test = 0x5000D;
    unk3e0 = 0.0f;
    unk3e4 = 0.0f;
    *reinterpret_cast<u32*>(&unk3e8[0]) = 0;
    *reinterpret_cast<u32*>(&unk3e8[4]) = 0;
    fog_color = 0;
    fog_enabled = 0;
    mode = 0;
    anchor = 0;

    unk860 = new (0) LibClass179130;
    resident_packet_rewind(unk860->packet);
    packet = reinterpret_cast<LibCameraSetupPacket*>(resident_packet_reserve(unk860->packet, 0));
    packet->dma_tag = 0;
    packet->vif = 0;
    unk558 = reinterpret_cast<u8*>(&packet->tag);
    packet->tag.tag = GIF_TAG_NREG(1) | GIF_TAG_EOP | 9;
    packet->tag.registers = 0;
    packet->tag.fields.register0 = GIF_REGISTER_AD;
    packet->registers[0].data = 4;
    packet->registers[0].address = GS_REGISTER_TEXCLUT;
    packet->registers[1].data = 0x61;
    packet->registers[1].address = GS_REGISTER_TEX1_1;
    packet->registers[2].data = GS_ALPHA_NORMAL;
    packet->registers[2].address = GS_REGISTER_ALPHA_1;
    packet->registers[3].data = test;
    packet->registers[3].address = GS_REGISTER_TEST_1;
    packet->registers[4].data = 0;
    packet->registers[4].address = GS_REGISTER_PABE;
    packet->registers[5].data = 1;
    packet->registers[5].address = GS_REGISTER_PRMODECONT;
    packet->registers[6].data = 0x8000008080ULL;
    packet->registers[6].address = GS_REGISTER_TEXA;
    packet->registers[7].data = 0xFFFFFFF0ULL;
    packet->registers[7].address = GS_REGISTER_CLAMP_1;
    packet->registers[8].address = GS_REGISTER_FOGCOL;
    resident_packet_align_cursor(unk860->packet, reinterpret_cast<u8*>(packet + 1));
    unk860->qwc = resident_packet_end(unk860->packet);
    packet->vif_codes[1] = VIF_DIRECTHL(unk860->qwc - 1);
}

/**
 * @brief Send the packet on VIF1 in normal mode.
 * @param channel DMA channel; unused.
 */
void LibClass179130::submit_dma(u32 channel)
{
    *D1_QWC = qwc;
    *D1_MADR = resident_packet_get_address(packet);
    *D_STAT = D_STAT_CIS1;
    *D1_CHCR = DMA_CHCR_START | DMA_CHCR_DIR_FROM_MEMORY;
}

/**
 * @brief Do nothing when the transfer ends.
 * @param channel DMA channel; unused.
 */
void LibClass179130::complete_dma(u32 channel)
{
}

/** @brief Delete the packet. */
LibClass179130::~LibClass179130()
{
    delete packet;
}

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
    resident_packet_set_alpha_2(packet, D_004ED330[0]);
    g_display->get_area_scale(&scale_x, &scale_y);
    resident_packet_add_rectangle(packet, rect.x, rect.y, (s32)(rect.width * scale_x) + 1, (s32)(rect.height * scale_y) + 1, depth, color);
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
    lib_detach(*g_image_registry);
    delete g_screen_text;
    ::operator delete(D_001B6644);
    g_image_registry->destroy();

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
    g_image_registry = 0;
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
    g_update_list->set_next_list(0);
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

        u32 parity;
};

/**
 * @brief Create Lib's global objects, link them into the update lists and set up the scene camera.
 * @param display Display Lib draws to.
 * @param depth_far Integer depth at the scene camera's far plane.
 * @param texture_cache_size Texture cache size in bytes.
 * @param texture_cache_blocks Texture cache block count.
 * @param node_count Node pointers the temporary node buffer holds.
 * @param first First extra renderer argument; with second, both nonzero turn the extra renderer state on.
 * @param second Second extra renderer argument.
 */
extern "C" void lib_initialize(LibCameraContext* display, s32 depth_far, s32 texture_cache_size, s32 texture_cache_blocks,
                               s32 node_count, s32 first, s32 second)
{
    ResidentSystem* system = resident_get_system();
    g_resource_archive = resident_get_archive(system);
    g_resident_resource_decoder = resident_system_get_decoder(system);
    g_input_system = resident_system_get_input(system);
    g_resident_release_queues = resident_system_get_release_queues(system);
    g_resource_queue = resident_system_get_resource_queue(system);
    g_sound = resident_system_get_sound(system);
    system->unk15C80 = reinterpret_cast<u32>(g_display_callbacks = new (0) LibDebugListener(display));
    g_display = display;
    resident_display_set_hook(display);
    *(volatile u32*)0x1000E000 = 0x503;
    g_update_list = new (0) LibUpdateList;
    func_004D66F0(g_update_list);
    D_001B6604 = new (0) ResidentDmaQueue(8);
    D_001B6608 = new (0) ResidentDmaQueue(9);
    D_001B660C = new (0) ResidentDmaQueue(0);
    g_vif1_dma_queue = new (0) ResidentDmaQueue(1);
    D_001B65FC = reinterpret_cast<LibBusyObject*>(new (0) LibVif0Channel);
    g_microcode_loader = new (0) LibMicrocodeLoader;
    g_microcode_loader->start_upload();
    func_004D9AB0(D_001B65FC, 0);
    g_packet_queue = new (0) LibPacketQueue(0x400);
    g_vram_allocator = new (0) LibVramAllocator(0x20, 0x20);
    func_004D99B0(D_001B65FC);
    g_renderer = new (0) LibRenderer(display);
    lib_vram_reset(g_vram_allocator, display->vram_free_page);
    D_001B6620 = new (0) LibClass178C90(static_cast<LibRenderer*>(g_renderer));
    g_light_list = new (0) LibLightList;
    g_display_manager = g_default_display_manager = reinterpret_cast<LibDisplayManager*>(new (0) LibClass178F30);
    g_scene_display_manager = reinterpret_cast<LibDisplayManager*>(new (0) LibClass178F30);
    D_001B6648 = new (0) LibClass177940;
    D_001B664C = new (0) LibClass1791E0;
    g_scene_camera = new (0) LibCamera(display);
    D_001B6634 = new (0) LibClass174D70;
    D_001B665C = new (0) LibClass174570;
    D_001B6660 = new (0) LibResidentUpdateList;
    g_sound->unk0c = static_cast<ResidentSoundRenderer*>(g_renderer);
    g_float_track_pool = new (0) LibTrackPool<LibPooledFloatTrack>;
    g_vector_track_pool = new (0) LibTrackPool<LibPooledVectorTrack>;
    g_slerp_quaternion_track_pool = new (0) LibTrackPool<LibPooledSlerpQuaternionTrack>;
    g_float_curve_track_pool = new (0) LibTrackPool<LibPooledFloatCurveTrack>;
    g_vector_curve_track_pool = new (0) LibTrackPool<LibPooledVectorCurveTrack>;
    g_float_quaternion_track_pool = new (0) LibTrackPool<LibPooledFloatQuaternionTrack>;
    g_quaternion_curve_track_pool = new (0) LibTrackPool<LibPooledQuaternionCurveTrack>;
    g_quaternion_track_pool = new (0) LibTrackPool<LibPooledQuaternionTrack>;
    g_field_allocation_heap = 0;
    static_cast<LibCamera*>(g_scene_camera)->horizontal_fov = 1.5707964f;
    s32 half_width = display->display_area.width / 2;
    s32 half_height = display->display_area.height / 2;
    LibVector4 position;
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = -320.0f;
    position.w = 1.0f;
    static_cast<LibCamera*>(g_scene_camera)->set_translation_vector(&position);
    LibCamera* camera = static_cast<LibCamera*>(g_scene_camera);
    camera->screen_min.x = 0x800 - half_width;
    camera->screen_min.y = 0x800 - half_height;
    camera->screen_min.z = 100.0f;
    camera->screen_min.w = 1.0f;
    camera->screen_max.x = 0x800 + half_width;
    camera->screen_max.y = 0x800 + half_height;
    camera->screen_max.z = 1800.0f;
    camera->screen_max.w = 1.0f;
    static_cast<LibCamera*>(g_scene_camera)->set_depth_range(depth_far - 100, depth_far);
    static_cast<LibCamera*>(g_scene_camera)->pixel_aspect = 1.3333334f * (1.0714285f * display->display_area.height) / display->display_area.width;
    static_cast<LibCamera*>(g_scene_camera)->unk3d1 = 1;
    g_scene_display_manager->append_node(g_scene_camera, -1);
    g_scene_display_manager->current_display = g_scene_camera;
    static_cast<LibClass174D70*>(D_001B6634)->managers[0] = g_display_manager;
    static_cast<LibClass177940*>(D_001B6648)->renderer = static_cast<LibRenderer*>(g_renderer);
    g_update_list->set_next_list(g_renderer);
    g_update_list->append_node(static_cast<LibListObject*>(g_light_list), -1);
    g_update_list->append_node(static_cast<LibListObject*>(g_display_manager), -1);
    g_update_list->append_node(static_cast<LibListObject*>(g_scene_display_manager), -1);
    g_update_list->append_node(D_001B6648, -1);
    g_update_list->append_node(D_001B6620, -1);
    g_update_list->append_node(D_001B664C, -1);
    g_update_list->append_node(D_001B6634, -1);
    g_update_list->append_node(g_resource_queue, -1);
    g_update_list->append_node(static_cast<LibListObject*>(D_001B6660), -1);
    g_update_list->append_node(static_cast<LibListObject*>(&D_507C40), -1);
    static_cast<LibRenderer*>(g_renderer)->append_node(D_001B665C, -1);
    g_texture_cache = new (0) LibTextureCache(texture_cache_size, texture_cache_blocks);
    D_001B6638 = 0;
    g_image_registry = new (0) LibImageRegistry(node_count);
    D_001B6644 = new (0) LibPacketRing;
    static_cast<LibClass174570*>(D_001B665C)->manager = g_display_manager;
    g_update_list->append_node(g_image_registry, -1);
    static_cast<LibRenderer*>(g_renderer)->manager = g_display_manager;

    if (first && second)
    {
        LibRendererExtra* extra = static_cast<LibRenderer*>(g_renderer)->extra;
        func_004209C0(reinterpret_cast<LibClass1727E0*>(extra), first, second);
        extra->enabled = 1;
        D_001B6550 = 1;
    }
    else
    {
        static_cast<LibRenderer*>(g_renderer)->extra->enabled = 0;
        D_001B6550 = 0;
    }

    g_screen_text = new (0) LibScreenText;
    g_screen_text->unk18 = 1;
    g_screen_text->load_font();
    lib_upload_default_palette();
    g_frame_seconds = 0.016666668f;
    g_frame_ticks = 1.0f;
    func_0045F5E0();
    lib_set_color_fade_area(LibScreenRect(0, 0, 0x280, 0xE0), 0xFFFF);
}

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

void float_track_pool_release(LibTrackPool<LibPooledFloatTrack>* pool);

void vector_track_pool_release(LibTrackPool<LibPooledVectorTrack>* pool);

void slerp_quaternion_track_pool_release(LibTrackPool<LibPooledSlerpQuaternionTrack>* pool);

void float_curve_track_pool_release(LibTrackPool<LibPooledFloatCurveTrack>* pool);

void vector_curve_track_pool_release(LibTrackPool<LibPooledVectorCurveTrack>* pool);

void float_quaternion_track_pool_release(LibTrackPool<LibPooledFloatQuaternionTrack>* pool);

void quaternion_curve_track_pool_release(LibTrackPool<LibPooledQuaternionCurveTrack>* pool);

void quaternion_track_pool_release(LibTrackPool<LibPooledQuaternionTrack>* pool);

/** @brief Release the pool's tracks and storage. */
template <> LibTrackPool<LibPooledFloatTrack>::~LibTrackPool()
{
    float_track_pool_release(this);
}

/** @brief Start with no tracks and no slot bits. */
template <> LibTrackPool<LibPooledFloatTrack>::LibTrackPool()
{
    items = 0;
    count = 0;
}

/** @brief Release the pool's tracks and storage. */
template <> LibTrackPool<LibPooledVectorTrack>::~LibTrackPool()
{
    vector_track_pool_release(this);
}

/** @brief Start with no tracks and no slot bits. */
template <> LibTrackPool<LibPooledVectorTrack>::LibTrackPool()
{
    items = 0;
    count = 0;
}

/** @brief Release the pool's tracks and storage. */
template <> LibTrackPool<LibPooledSlerpQuaternionTrack>::~LibTrackPool()
{
    slerp_quaternion_track_pool_release(this);
}

/** @brief Start with no tracks and no slot bits. */
template <> LibTrackPool<LibPooledSlerpQuaternionTrack>::LibTrackPool()
{
    items = 0;
    count = 0;
}

/** @brief Release the pool's tracks and storage. */
template <> LibTrackPool<LibPooledFloatCurveTrack>::~LibTrackPool()
{
    float_curve_track_pool_release(this);
}

/** @brief Start with no tracks and no slot bits. */
template <> LibTrackPool<LibPooledFloatCurveTrack>::LibTrackPool()
{
    items = 0;
    count = 0;
}

/** @brief Release the pool's tracks and storage. */
template <> LibTrackPool<LibPooledVectorCurveTrack>::~LibTrackPool()
{
    vector_curve_track_pool_release(this);
}

/** @brief Start with no tracks and no slot bits. */
template <> LibTrackPool<LibPooledVectorCurveTrack>::LibTrackPool()
{
    items = 0;
    count = 0;
}

/** @brief Release the pool's tracks and storage. */
template <> LibTrackPool<LibPooledFloatQuaternionTrack>::~LibTrackPool()
{
    float_quaternion_track_pool_release(this);
}

/** @brief Start with no tracks and no slot bits. */
template <> LibTrackPool<LibPooledFloatQuaternionTrack>::LibTrackPool()
{
    items = 0;
    count = 0;
}

/** @brief Release the pool's tracks and storage. */
template <> LibTrackPool<LibPooledQuaternionCurveTrack>::~LibTrackPool()
{
    quaternion_curve_track_pool_release(this);
}

/** @brief Start with no tracks and no slot bits. */
template <> LibTrackPool<LibPooledQuaternionCurveTrack>::LibTrackPool()
{
    items = 0;
    count = 0;
}

/** @brief Release the pool's tracks and storage. */
template <> LibTrackPool<LibPooledQuaternionTrack>::~LibTrackPool()
{
    quaternion_track_pool_release(this);
}

/** @brief Start with no tracks and no slot bits. */
template <> LibTrackPool<LibPooledQuaternionTrack>::LibTrackPool()
{
    items = 0;
    count = 0;
}

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
bool LibVectorCurveTrack::append_curve_key(const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent, float key)
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
bool LibVectorCurveTrack::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
bool LibVectorCurveTrack::replace_curve_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* in_tangent, const FieldVec4A* out_tangent)
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
bool LibVectorCurveTrack::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
bool LibVectorKeyTrack::on_append_key(const FieldVec4A* value, float key)
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
bool LibVectorKeyTrack::on_replace_key(s32 index, float key, const FieldVec4A* value)
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
bool LibVectorCurveTrackBase::on_append_key(const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second, float key)
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
bool LibVectorCurveTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value, const FieldVec4A* first, const FieldVec4A* second)
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
bool LibVectorTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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
bool LibVectorTrackBase::on_replace_key(s32 index, float key, const FieldVec4A* value)
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
bool LibVectorTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
{
    return on_append_key(static_cast<const FieldVec4A*>(value), key);
}

/**
 * @brief Ignore the keyframe; the tracks that store keys override this.
 * @param value Keyframe value.
 * @param key Sort key.
 * @return Zero.
 */
bool LibVectorTrackBase::on_append_key(const FieldVec4A* value, float key)
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
bool LibVectorCurveTrackBase::append_key(const void* value, const void* in_tangent, const void* out_tangent, float key)
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
bool LibVectorCurveTrackBase::replace_key(s32 index, float key, const void* value, const void* in_tangent, const void* out_tangent)
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

LibLightList::~LibLightList()
{
}

/**
 * @brief Return the list's kind.
 * @return Eight.
 */
s32 LibLightList::get_default_list_kind()
{
    return 8;
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

/** @brief Update the listed nodes. */
void LibLightList::update()
{
    update_nodes();
}

// LibLightList's per-frame light update; the intensity test's abs.s is still coloured differently.
/**
 * @brief Light step run before the renderer tests its models: refresh the list's light matrices and sort its lights.
 * @param lights Light list.
 */
extern "C" void func_004E9290(LibLightList* lights)
{
    func_004CFF80(&lights->unk90);
    func_004CFF80(&lights->unkd0);
    LibCamera* camera = static_cast<LibCamera*>(lights->manager->current_display);

    if (camera == 0)
    {
        return;
    }

    float scale = 1.0f;
    float red = camera->unk260 * scale;
    float green = camera->unk264 * scale;
    float blue = camera->unk268 * scale;
    LibListSentinel* node = &lights->sentinel;
    bool dirty = false;
    lights->unk37e = 1;
    lights->has_local_lights = 0;
    lights->light_count = 0;
    lights->unk364_count = 0;

    for (;;)
    {
        node = node->next;

        if (at_list_end(&lights->sentinel, node))
        {
            break;
        }

        LibLight* light = static_cast<LibLight*>(node);

        float brightness = light->color.w;

        if (ee_abs(brightness) < 0.0001f)
        {
            light->enabled = 0;
            continue;
        }

        light->enabled = 1;
        light->update_frame();
        LibVector4 tinted;
        tinted.x = red * light->color.x;
        tinted.y = green * light->color.y;
        tinted.z = blue * light->color.z;
        copy_vector(&light->tinted_color, &tinted);

        if (light->kind & LIB_LIGHT_LOCAL)
        {
            lights->has_local_lights = 1;

            if (!light->unk28e)
            {
                continue;
            }
        }

        lights->light_count++;

        if (dirty)
        {
            continue;
        }

        if ((light->unk28b && light->unk289) || light->unk288)
        {
            dirty = true;
        }

        if (light->unk28e)
        {
            dirty = true;
        }

        if (light->unk290)
        {
            dirty = true;
        }
    }

    if (!dirty && lights->light_count <= 4)
    {
        func_004CFF80((LibMatrix44Value*)lights->directions);
        func_004CFF80((LibMatrix44Value*)lights->colors);
        lights->unk37e = 0;
        lights->mask = -1;
        s32 count = 0;
        LibListSentinel* packed = &lights->sentinel;

        for (;;)
        {
            packed = packed->next;

            if (at_list_end(&lights->sentinel, packed))
            {
                break;
            }

            LibLight* light = static_cast<LibLight*>(packed);

            if (!light->enabled || (light->kind & LIB_LIGHT_LOCAL))
            {
                continue;
            }

            LibVector4 direction;
            lib_light_get_direction(&direction, light);
            lights->directions[count].x = -direction.x;
            lights->directions[count].y = -direction.y;
            lights->directions[count].z = -direction.z;
            float intensity = light->color.w;
            float* reds = lights->colors[0];
            float* greens = lights->colors[1];
            float* blues = lights->colors[2];
            reds[count] = light->tinted_color.x * intensity;
            greens[count] = light->tinted_color.y * intensity;
            blues[count] = light->tinted_color.z * intensity;

            if (light->unk28c)
            {
                lights->unk364[lights->unk364_count++] = light;
            }

            u32 light_mask = light->mask;
            lights->mask &= light_mask;
            count++;
            light->packed_intensity = intensity;

            if (count == 4)
            {
                break;
            }
        }
    }

    vu0_multiply_xyzw(&lights->unk340, &lights->unk320, &lights->unk330);
}

/** @brief Start with no lights, a (0, 0, 0, 1) ambient colour and white light scales. */
LibLightList::LibLightList()
{
    unk310 = FieldVec4A(0.0f, 0.0f, 0.0f, 1.0f);
    unk320 = FieldVec4A(1.0f, 1.0f, 1.0f, 1.0f);
    unk330 = FieldVec4A(1.0f, 1.0f, 1.0f, 1.0f);
    unk382 = 1;
}

// TODO: The game inlines the frame's destructor into the tooltip's, though the frame's copy is out of line too; a
// scoped auto_inline on its definition, placed first, is the only way I've found to get both.
#pragma push
#pragma auto_inline on
/** @brief Destroy the tooltip and its drawing storage. */
EquipTooltipFrame::~EquipTooltipFrame()
{
}
#pragma pop

/** @brief Destroy the text array, tooltip, and container bases. */
EquipFactorTooltip::~EquipFactorTooltip()
{
}

extern "C" void lib_factor_tooltip_hide(void* object)
{
    ByteClearOwnertext_004DD440* receiver = static_cast<ByteClearOwnertext_004DD440*>(object);
    receiver->unkcb = 0;
}

extern "C" ResidentObject1B64F8* D_001B64F8;

/**
 * @brief Show the factors of an allocation in the tooltip at a position, unless it's already showing; an invalid
 * allocation, one without the factor flag or one without factors hides it.
 * @param object Factor tooltip.
 * @param identifier One-based allocation ID.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Depth.
 */
extern "C" void lib_factor_tooltip_show(EquipFactorTooltip* object, s16 identifier, float x, float y, float z)
{
    if (object->unkab)
    {
        return;
    }

    LibGameState* state = reinterpret_cast<LibGameState*>(D_001B64F8);
    bool valid = false;

    if (identifier > 0 && identifier <= LIB_ALLOCATION_COUNT)
    {
        valid = true;
    }

    ItemCreationAllocationRecord* record;

    if (valid)
    {
        record = reinterpret_cast<ItemCreationAllocationRecord*>(&state->allocations[identifier - 1]);
    }
    else
    {
        record = 0;
    }

    if (record == 0 || !record->allocated)
    {
        object->unkab = 0;
        return;
    }

    u16 factors[8];
    s32 count = 0;
    u16* factor = factors;

    for (s32 i = 0; i < 8; i++)
    {
        u16 value = func_0040D930(record, i);

        if (value > 0 && value != 700)
        {
            *factor++ = value;
            count++;
        }
    }

    if (count == 0)
    {
        object->unkab = 0;
        return;
    }

    u32 base = g_field_runtime->text_banks[1].base_key;
    u16* name = factors;
    s32* id = object->factor_ids;

    for (s32 i = 0; i < 8; i++)
    {
        *id = i < count ? *name - 1 + base : 0;
        name++;
        id++;
    }

    object->position_x = x;
    object->position_y = y;
    object->position_z = z;
    object->unka0c = 1;
    object->unkab = 1;
}

/**
 * @brief Lay the tooltip out on the step after it was shown: size the factor texts to its depth, fit the frame around
 * them and keep it on screen; then fade it in.
 * @param first Unused.
 * @param second Unused.
 * @param third Unused.
 */
void EquipFactorTooltip::func_00412C40(bool first, bool second, bool third)
{
    switch (unka0c)
    {
    case 1:
    {
        s32 slot = g_field_runtime->text_banks[1].resource_slot;
        float width = 0.0f;
        float height = width;
        float scale = position_z / 24.0f;
        float spacing = 2.0f * scale;
        float step = position_z + spacing;
        float y = 6.0f;
        LibTextWidget* text = factor_texts;

        for (s32 i = 0; i < 8; i++, text++)
        {
            if (factor_ids[i])
            {
                lib_text_set_resource(text, slot, factor_ids[i], 0);
                text->unk18.unk04 = y;
                text->unk8c = spacing;
                text->draw_scale_y = scale;
                text->draw_scale = scale;
                text->unk3d = 1;
                LibTextExtent* extent = lib_text_measure_bounds(text);

                if (!(extent->width <= width))
                {
                    width = extent->width;
                }

                height += extent->height + spacing;
            }
            else
            {
                text->unk3d = 0;
            }

            y += step;
        }

        width += 12.0f;
        height += 12.0f;
        frame.unk18.unk08 = width;
        frame.unk18.unk0c = height;
        frame.needs_redraw = 1;
        float x = position_x;
        float top = position_y;
        float right = x + width + 16.0f;

        if (!(right <= g_field_runtime->unk524))
        {
            x -= right - g_field_runtime->unk524;
        }

        float bottom = top + height + 16.0f;

        if (!(bottom <= g_field_runtime->unk528))
        {
            top -= bottom - g_field_runtime->unk528;
        }

        if (top < position_y)
        {
            float above = position_y - 37.0f;

            if (!(above - 16.0f < height))
            {
                top = above - height;
            }
        }

        set_position(x, top);
        unkE0 = 0.0f;
        unka0c++;
        break;
    }

    case 2:
        unkE0 += 32.0f * field_rate(g_field_runtime);

        if (!(unkE0 < 128.0f))
        {
            unkE0 = 128.0f;
            unka0c = 0;
        }

        geometry_dirty = 1;
        break;
    }
}

/**
 * @brief Allocate the frame's drawing storage and mark it ready.
 * @param frame Tooltip frame.
 * @return Whether the storage was allocated.
 */
static inline bool lib_tooltip_frame_init(EquipTooltipFrame* frame)
{
    if (!lib_allocate_drawing_storage(&frame->unk40, 0x12))
    {
        return false;
    }

    frame->unk39 = 1;
    return true;
}

/**
 * @brief Set the tooltip up: an empty container with its frame and eight factor texts, hidden.
 * @param object Factor tooltip.
 * @return One, or zero when a drawing storage can't be allocated.
 */
extern "C" s32 lib_factor_tooltip_init(EquipFactorTooltip* object)
{
    lib_container_init(object, 1, 0.0f, 0.0f, 0, 0.0f, 0);

    if (!lib_tooltip_frame_init(&object->frame))
    {
        return 0;
    }

    lib_container_attach_widget(object, &object->frame);

    LibTextWidget* text = object->factor_texts;

    for (s32 i = 0; i < 8; i++, text++)
    {
        if (!lib_text_init_resource_rectangle(text, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f))
        {
            return 0;
        }

        text->unk18.unk00 = 6.0f;
        text->tint = 0;
        text->unkf9 = 0;
        lib_container_attach_widget(object, text);
    }

    object->unka0c = 0;
    object->unkab = 0;
    return 1;
}

/**
 * @brief Read a container's alpha, which scales its widgets' alpha.
 * @param container Container.
 * @return Alpha, 128 for opaque.
 */
static inline float lib_container_alpha(const LibContainer* container)
{
    return container->unkE0;
}

/**
 * @brief Pack an XYZ2 value.
 * @param x Horizontal position.
 * @param y Vertical position.
 * @param z Depth.
 * @return XYZ2 register value.
 */
static inline u64 lib_frame_xyz(s32 x, s32 y, s32 z)
{
    return (u64)z << 32 | ((u64)x | (u64)y << 16);
}

/** @brief Build the packet once: a background inset by two pixels, then a two-pixel border on each side. */
void EquipTooltipFrame::draw()
{
    if (!unk3b)
    {
        LibContainer* owner = container;
        LibCallbackTransform& transform = *owner;
        float alpha = (draw_alpha * lib_container_alpha(owner)) / 128.0f;
        float left = transform.translation.x + unk18.unk00;
        float top = transform.translation.y + unk18.unk04;
        s32 depth = transform.unka4;
        FieldRuntime* runtime = g_field_runtime;
        float scale_x = runtime->screen_scale_x;
        float offset_x = runtime->screen_offset_x;
        float scale_y = runtime->screen_scale_y;
        float offset_y = runtime->screen_offset_y;
        float right = left + unk18.unk08;
        float bottom = top + unk18.unk0c;
        u64 color = (u32)alpha << 24;
        u64* cursor = reinterpret_cast<u64*>(unk40.dma_address);
        packet = packet_tag = cursor;
        cursor[0] = 0x70000008;
        cursor[2] = GIF_TAG_NREG(14) | GIF_TAG_FLG_REGLIST | GIF_TAG_EOP | 1;
        cursor[3] = 0x00F5555555515510;
        cursor[4] = 0x246;
        cursor[5] = color | 0xA0D0D0;
        s32 inner_top = (s32)(offset_y + (2.0f + top) * scale_y);
        s32 outer_top = (s32)(offset_y + top * scale_y);
        s32 inner_left = (s32)(offset_x + (2.0f + left) * scale_x);
        s32 outer_left = (s32)(offset_x + left * scale_x);
        s32 inner_bottom = (s32)(offset_y + scale_y * (bottom - 2.0f));
        s32 outer_bottom = (s32)(offset_y + scale_y * bottom);
        s32 inner_right = (s32)(offset_x + scale_x * (right - 2.0f));
        s32 outer_right = (s32)(offset_x + scale_x * right);
        cursor[6] = lib_frame_xyz(inner_left, inner_top, depth);
        cursor[7] = lib_frame_xyz(inner_right, inner_bottom, depth);
        cursor[8] = color | 0x80808;
        cursor[9] = lib_frame_xyz(outer_left, outer_top, depth);
        cursor[10] = lib_frame_xyz(outer_right, inner_top, depth);
        cursor[11] = lib_frame_xyz(outer_left, inner_top, depth);
        cursor[12] = lib_frame_xyz(inner_left, inner_bottom, depth);
        cursor[13] = lib_frame_xyz(inner_right, inner_top, depth);
        cursor[14] = lib_frame_xyz(outer_right, inner_bottom, depth);
        cursor[15] = lib_frame_xyz(outer_left, inner_bottom, depth);
        cursor[16] = lib_frame_xyz(outer_right, outer_bottom, depth);
        cursor[17] = 0;
        unk3b = 1;
    }
}


